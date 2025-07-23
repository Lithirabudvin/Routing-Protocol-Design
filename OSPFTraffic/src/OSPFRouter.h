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

#ifndef __OSPFTRAFFIC_OSPFROUTER_H_
#define __OSPFTRAFFIC_OSPFROUTER_H_

#include <omnetpp.h>
#include <map>
#include <vector>
#include <limits>
#include <queue>
#include <utility>
#include "OSPFPacket_m.h"

using namespace omnetpp;
using namespace ospftraffic;

struct LinkInfo {
    int neighborId;
    double delay;
    int traffic;
};

class OSPFRouter : public cSimpleModule {
  private:
    int routerId;
    std::map<int, int> neighborIdToGateIndex;
    static std::map<int, std::vector<LinkInfo>> globalGraph;
    static std::map<std::pair<int, int>, int> trafficMatrix;
    std::map<int, int> routingTable;

    // Timers
    cMessage *sendRandomPacketEvent = nullptr;

    int getGateIndexForRouter(int nextHopRouterId);
    void buildGraph();
    void runDijkstra(double a, double b);
    void sendPacketTo(OSPFPacket *pkt, int nextHop);
    void logTrafficMatrix();

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual ~OSPFRouter(); // Mark as virtual for inheritance safety

    SimTime routeInterval;
    SimTime sendInterval;
};

#endif


