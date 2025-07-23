//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "OSPFRouter.h"
#include "OSPFPacket_m.h"

using namespace ospftraffic;
#include <algorithm>

Define_Module(OSPFRouter);

std::map<int, std::vector<LinkInfo>> OSPFRouter::globalGraph;
std::map<std::pair<int, int>, int> OSPFRouter::trafficMatrix;

void OSPFRouter::initialize() {
    routerId = par("routerId");
    EV << getFullName() << " has routerId = " << routerId << endl;

    if (routerId == 1) {
        globalGraph.clear();
        trafficMatrix.clear();
        // Now preload, after clearing and after routerId is set!
        OSPFRouter::trafficMatrix[{1,3}] = 20;
        OSPFRouter::trafficMatrix[{3,5}] = 20;
        OSPFRouter::trafficMatrix[{5,7}] = 20;
        OSPFRouter::trafficMatrix[{3,6}] = 20;
        OSPFRouter::trafficMatrix[{6,7}] = 20;
    }

    routeInterval = SimTime(3, SIMTIME_S); // Faster route updates for demo
    sendInterval = SimTime(0.2, SIMTIME_S); // r1→r7 traffic rate


    buildGraph();

    // Timer for periodic routing table computation
    scheduleAt(simTime() + 0.5, new cMessage("computeRoutes"));

    // Only r1 sends demo traffic to r7
    if (routerId == 1) {
        scheduleAt(simTime() + 1.0, new cMessage("sendPacket"));
    }

    // Timer for random background traffic from every router
    sendRandomPacketEvent = new cMessage("sendRandomPacket");
    scheduleAt(simTime() + uniform(0.1, 0.2), sendRandomPacketEvent); // Fast background traffic
}

void OSPFRouter::handleMessage(cMessage *msg) {
    if (strcmp(msg->getName(), "computeRoutes") == 0) {
        runDijkstra(1.0, 5.0); // Large b to emphasize congestion
        for (auto &entry : routingTable) {
            EV << "[Routing] r" << routerId << " -> r" << entry.first
               << " via next hop router: r" << entry.second << endl;
        }
        logTrafficMatrix();
        scheduleAt(simTime() + routeInterval, msg);
    }

    else if (strcmp(msg->getName(), "sendPacket") == 0) {
        OSPFPacket *pkt = new OSPFPacket("data");
        pkt->setSrcId(routerId);
        pkt->setDestId(7);
        pkt->setPayload("Hello from r1 to r7");
        pkt->appendHopTrace(getFullName());



        auto it = routingTable.find(pkt->getDestId());
        if (it != routingTable.end()) {
            int nextHopRouterId = it->second;
            sendPacketTo(pkt, nextHopRouterId);
        } else {
            EV << "No route to destination r" << pkt->getDestId() << ". Dropping packet.\n";
            delete pkt;
        }

        scheduleAt(simTime() + sendInterval, msg);
    }

    else if (msg == sendRandomPacketEvent) {
        // Pick a random destination router (not self)
        int destId;
        do {
            destId = intuniform(1, 7); // assuming 7 routers
        } while (destId == routerId);

        OSPFPacket *pkt = new OSPFPacket("randomData");
        pkt->setSrcId(routerId);
        pkt->setDestId(destId);
        pkt->setPayload("Random traffic");
        pkt->appendHopTrace(getFullName());

        auto it = routingTable.find(pkt->getDestId());
        if (it != routingTable.end()) {
            int nextHopRouterId = it->second;
            sendPacketTo(pkt, nextHopRouterId);
        } else {
            delete pkt;
        }

        // Schedule next random packet
        scheduleAt(simTime() + uniform(0.1, 0.2), sendRandomPacketEvent);
    }

    else if (auto pkt = dynamic_cast<OSPFPacket *>(msg)) {
        EV << getFullName() << " received packet from " << pkt->getSrcId()
           << " to " << pkt->getDestId() << "\n";

        pkt->appendHopTrace(getFullName());

        if (pkt->getDestId() == routerId) {
            EV << getFullName() << " is destination. Payload: " << pkt->getPayload() << "\n";
            EV << "Hop Trace: ";
            for (size_t i = 0; i < pkt->getHopTraceArraySize(); ++i)
                EV << pkt->getHopTrace(i) << (i + 1 < pkt->getHopTraceArraySize() ? " -> " : "\n");
            delete pkt;
        } else {
            auto it = routingTable.find(pkt->getDestId());
            if (it != routingTable.end()) {
                int nextHopRouterId = it->second;
                trafficMatrix[{routerId, nextHopRouterId}]++;

                double delay = 0;
                for (const auto& link : globalGraph[routerId]) {
                    if (link.neighborId == nextHopRouterId) {
                        delay = link.delay;
                        break;
                    }
                }
                double cost = 1.0 * delay + 100.0 * trafficMatrix[{routerId, nextHopRouterId}];
                EV << "[TrafficMatrix] Cost from r" << routerId << " to r" << nextHopRouterId
                   << " = delay: " << delay
                   << ", traffic: " << trafficMatrix[{routerId, nextHopRouterId}]
                   << ", total cost: " << cost << "\n";

                sendPacketTo(pkt, nextHopRouterId);
            } else {
                EV << "No route to destination r" << pkt->getDestId() << ". Dropping packet.\n";
                delete pkt;
            }
        }
    }

    else {
        delete msg;
    }
}

void OSPFRouter::sendPacketTo(OSPFPacket *pkt, int nextHopRouterId) {
    auto it = neighborIdToGateIndex.find(nextHopRouterId);
    if (it != neighborIdToGateIndex.end()) {
        int gateIndex = it->second;
        send(pkt, "out", gateIndex);
    } else {
        EV << "No valid gate to nextHop router ID=" << nextHopRouterId << "\n";
        delete pkt;
    }
}

int OSPFRouter::getGateIndexForRouter(int nextHopRouterId) {
    for (int i = 0; i < gateSize("out"); ++i) {
        cGate *g = gate("out", i);
        if (g->isConnected()) {
            cModule *target = g->getNextGate()->getOwnerModule();
            if (target->par("routerId").intValue() == nextHopRouterId) {
                return i;
            }
        }
    }
    return -1;
}

void OSPFRouter::buildGraph() {
    neighborIdToGateIndex.clear();

    for (int i = 0; i < gateSize("out"); ++i) {
        cGate *outGate = gate("out", i);
        if (outGate->isConnected()) {
            cChannel *ch = outGate->getChannel();
            cGate *nextGate = outGate->getNextGate();
            cModule *neighbor = nextGate->getOwnerModule();

            int neighborId = neighbor->par("routerId").intValue();
            double delay = ch->par("delay").doubleValue();

            globalGraph[routerId].push_back({neighborId, delay, 0});
            neighborIdToGateIndex[neighborId] = i;

            EV << "[Routing] " << getFullName() << " -> " << neighbor->getFullName()
               << " via gate index: " << i << " neighborId: " << neighborId << "\n";
        }
    }
}

void OSPFRouter::runDijkstra(double a, double b) {
    std::map<int, double> dist;
    std::map<int, int> prev;
    std::set<int> visited;

    dist[routerId] = 0;
    using P = std::pair<double, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.push({0.0, routerId});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (visited.count(u)) continue;
        visited.insert(u);

        for (const auto &edge : globalGraph[u]) {
            double cost = a * edge.delay + b * pow(trafficMatrix[{u, edge.neighborId}], 2);
            if (!dist.count(edge.neighborId) || dist[u] + cost < dist[edge.neighborId]) {
                dist[edge.neighborId] = dist[u] + cost;
                prev[edge.neighborId] = u;
                pq.push({dist[edge.neighborId], edge.neighborId});
            }
        }
    }

    for (const auto &[dest, _] : dist) {
        int curr = dest;
        while (prev.count(curr) && prev[curr] != routerId)
            curr = prev[curr];
        if (prev.count(curr))
            routingTable[dest] = curr;  // nextHop routerId
    }
}

void OSPFRouter::logTrafficMatrix() {
    EV << "\n=== Traffic Matrix at time " << simTime() << " ===\n";
    for (const auto& entry : trafficMatrix) {
        int from = entry.first.first;
        int to = entry.first.second;
        int count = entry.second;
        EV << "Traffic from r" << from << " to r" << to << " = " << count << endl;
    }
    EV << "===============================\n";
}

OSPFRouter::~OSPFRouter() {
    if (sendRandomPacketEvent)
        cancelAndDelete(sendRandomPacketEvent);
}






