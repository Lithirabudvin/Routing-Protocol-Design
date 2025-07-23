#ifndef OSPFROUTER_H_
#define OSPFROUTER_H_

#include <omnetpp.h>
#include <map>
#include <vector>
#include <set>
#include "OSPFPacket_m_m.h"

using namespace omnetpp;

struct Link {
    int neighborId;
    double distance;
    double traffic;
    int gateIndex;
};

class OSPFRouter : public cSimpleModule
{
  private:
    int routerId;
    std::map<int, std::vector<Link>> networkGraph;
    std::map<int, int> routingTable;
    std::map<std::pair<int, int>, double> trafficMap;

    double a = 1.0; // distance weight
    double b = 2.0; // traffic weight

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

    void initializeGraph();
    void runDijkstraWithCustomCost();
    void sendDataPacket(int destId, const char* payload);
};

#endif
