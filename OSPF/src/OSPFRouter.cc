#include "OSPFRouter.h"

Define_Module(OSPFRouter);
using namespace ospf;

void OSPFRouter::initialize() {
    std::string name = getName();
    routerId = std::stoi(name.substr(1)); // e.g., "r3" → 3

    // ❗ Fix: Set gate sizes manually
    int numOut = gateSize("out");
    if (numOut == 0) {
        setGateSize("out", 5); // Match your max expected out++ usage
        setGateSize("in", 5);
    }

    initializeGraph();
    runDijkstraWithCustomCost();

    if (routerId == 1) {
        scheduleAt(simTime() + 3, new cMessage("dataTimer"));
    }
}


void OSPFRouter::initializeGraph() {
    // Static topology — this must match your NED setup
    if (routerId == 1) {
        networkGraph[1] = {
            {2, 1.0, 0.0, 0},
            {3, 2.0, 0.0, 1}
        };
    } else if (routerId == 2) {
        networkGraph[2] = {
            {1, 1.0, 0.0, 0},
            {3, 1.0, 0.0, 1},
            {4, 1.0, 0.0, 2}
        };
    } else if (routerId == 3) {
        networkGraph[3] = {
            {1, 2.0, 0.0, 0},
            {2, 1.0, 0.0, 1},
            {4, 1.0, 0.0, 2}
        };
    } else if (routerId == 4) {
        networkGraph[4] = {
            {2, 1.0, 0.0, 0},
            {3, 1.0, 0.0, 1}
        };
    }
    // Add more for r5, r6, etc.
}

void OSPFRouter::runDijkstraWithCustomCost() {
    std::map<int, double> cost;
    std::map<int, int> previous;
    std::set<int> visited;

    for (auto &pair : networkGraph) {
        cost[pair.first] = INFINITY;
    }
    cost[routerId] = 0;

    while (visited.size() < networkGraph.size()) {
        int current = -1;
        double minCost = INFINITY;
        for (auto &pair : cost) {
            if (!visited.count(pair.first) && pair.second < minCost) {
                current = pair.first;
                minCost = pair.second;
            }
        }
        if (current == -1) break;
        visited.insert(current);

        for (const Link &link : networkGraph[current]) {
            double traffic = trafficMap[{current, link.neighborId}];
            double linkCost = a * link.distance + b * traffic;
            double newCost = cost[current] + linkCost;

            if (newCost < cost[link.neighborId]) {
                cost[link.neighborId] = newCost;
                previous[link.neighborId] = current;
            }
        }
    }

    routingTable.clear();
    for (const auto &pair : cost) {
        int dest = pair.first;
        if (dest == routerId) continue;

        int hop = dest;
        while (previous[hop] != routerId) {
            hop = previous[hop];
        }

        for (const Link &link : networkGraph[routerId]) {
            if (link.neighborId == hop) {
                routingTable[dest] = link.gateIndex;
                break;
            }
        }
    }
}

void OSPFRouter::handleMessage(cMessage *msg) {
    if (strcmp(msg->getName(), "dataTimer") == 0) {
        sendDataPacket(4, "Hello from r1 to r4");  // Send to r4
        delete msg;
    }
    else if (auto pkt = dynamic_cast<DataPacket *>(msg)) {
        if (pkt->getDestId() == routerId) {
            EV << getFullPath() << " received DataPacket: " << pkt->getPayload() << "\n";
            delete pkt;
        } else {
            int nextGate = routingTable[pkt->getDestId()];
            trafficMap[{routerId, pkt->getDestId()}] += 1;  // Increase simulated traffic
            EV << getFullPath() << " forwarding packet to dest " << pkt->getDestId() << "\n";
            send(pkt, "out", nextGate);
        }
    } else {
        EV << "Unknown message, deleted\n";
        delete msg;
    }
}

void OSPFRouter::sendDataPacket(int destId, const char* payload) {
    auto *pkt = new DataPacket("DataPacket");
    pkt->setSrcId(routerId);
    pkt->setDestId(destId);
    pkt->setPayload(payload);

    int nextGate = routingTable[destId];
    trafficMap[{routerId, destId}] += 1;  // simulate usage
    send(pkt, "out", nextGate);
}
