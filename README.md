# TA-OSPF: Traffic-Aware OSPF Protocol for OMNeT++

Welcome to the implementation of **Traffic-Aware OSPF (TA-OSPF)**—an innovative extension of the standard OSPF protocol designed for OMNeT++. This project integrates dynamic, traffic-based metrics into OSPF to enable intelligent, adaptive data routing in networks with fluctuating traffic loads.

## Table of Contents

- [Project Overview](#project-overview)
- [Key Features](#key-features)
- [Background](#background)
- [TA-OSPF Protocol Design](#ta-ospf-protocol-design)
- [Simulation Details](#simulation-details)
- [Project Structure](#project-structure)
- [How to Run the Simulation](#how-to-run-the-simulation)
- [Customization & Parameters](#customization--parameters)
- [Performance Highlights](#performance-highlights)
- [References](#references)
- [License](#license)
- [Acknowledgements](#acknowledgements)

## Project Overview

This project implements a **traffic-aware routing protocol** based on OSPF for OMNeT++ 6.1. By integrating real-time link traffic information into routing metrics, TA-OSPF achieves improved load balancing, congestion avoidance, and network throughput, particularly in dynamic and large-scale environments.

## Key Features

- Real-time traffic awareness in routing decisions
- Composite link metric: combines link delay with current traffic load
- Periodic route recalculation for adaptive path selection
- Improved congestion management and overall network efficiency
- Proactive avoidance of overloaded links
- Full OMNeT++ simulation with custom module implementation

## Background

Standard OSPF computes shortest paths using static link costs (often based on bandwidth) and is widely deployed in enterprise and service provider networks. However, these metrics do not adapt to changing traffic conditions, causing bottlenecks and inefficient resource usage. TA-OSPF addresses this by incorporating **dynamic, traffic-dependent metrics** into OSPF route calculation.

## TA-OSPF Protocol Design

### Design Objectives

- Eliminate static link metrics—routing decisions leverage *real-time traffic load*
- Achieve intelligent load balancing and minimize congestion
- Preserve compatibility with existing OSPF architectures

### Routing Metric

Each link’s cost is calculated as:

Cost = a × Delay + b × (Traffic Load)^2


- **Delay**: Link propagation delay
- **Traffic Load**: Number of packets sent over the link (monitored in real time)
- **a, b**: Tunable weight parameters (`a=1.0`, `b=100.0` by default)

The **quadratic penalty** on traffic load strongly discourages heavily congested links.

### Control Message Format

TA-OSPF extends the standard OSPF packet by including:

- `srcId/destId`: Source and destination router IDs
- `payload`: Data or control content
- `hopTrace[]`: Records the full path for monitoring and debugging

### Router State Information

Each router maintains:

- **Global Topology Map:** Static structure with nodes, neighbors, and link delays
- **Traffic Matrix:** Dynamic, tracks packet counts between router pairs in real time
- **Dynamic Routing Table:** Computes and updates best next-hop routes
- **Neighbor-to-Gate Mapping:** Relates neighbors to routing outputs

### Adaptive Dijkstra’s Algorithm

- Cost function includes both delay and current traffic metrics
- Runs periodically (every 0.5s) for up-to-date route decisions
- Prevents route oscillation with a quadratic congestion penalty

### Improvements Over Standard OSPF

- Adapts route selection to real-time traffic
- Dynamically balances load across multiple viable paths
- Significantly reduces the likelihood and impact of link congestion

## Simulation Details

- **Simulator:** OMNeT++ 6.1
- **Language:** C++
- **Duration per Scenario:** 30 seconds
- **Network Topology:** 7-router hybrid ring/star with redundant paths
- **Link Parameters:** 10ms delay, 100Mbps rate

## Project Structure

/
│
├── src/
│ ├── OSPFRouter.h # Router module header
│ ├── OSPFRouter.cc # Router module implementation
│ └── OSPFPacket.msg # Custom packet format (TA-OSPF)
│
├── simulations/
│ └── OSPFNetwork.ned # Simulated network topology
│
├── README.md # This documentation
└── ... (Other OMNeT++ project files)


## How to Run the Simulation

1. **Install OMNeT++ 6.1** (or compatible version) on your system.
2. **Clone or copy this repository** into your OMNeT++ workspace.
3. **Import the project** into OMNeT++ IDE or use the `opp_makemake`/`make` tools if building via the command line.
4. **Build the project** using the OMNeT++ build system.
5. Run the simulation scenario found in `simulations/OSPFNetwork.ned`.



6. **Examine logs/statistics** for link utilization, path selection, and performance metrics.

## Customization & Parameters

- **Metric Weights:** Adjust values of `a` and `b` in `runDijkstra(a, b)` for desired sensitivity to congestion delays.
- **Route Update Frequency:** Change `routeInterval` in the router module for how often routing decisions are updated.
- **Topology:** Modify the `.ned` file for different network structures.
- **Simulation Duration:** Configure scenario run time in the simulation settings.

## Performance Highlights

- **Adaptive Load Balancing:** TA-OSPF minimizes bottlenecks by routing flows away from congested links.
- **Proactive Congestion Avoidance:** The protocol redirects traffic before congestion becomes critical.
- **Stable Convergence:** Periodic route updates and quadratic penalties maintain efficient and stable routing.


## Visualizing Packet Routing

To illustrate the benefits of TA-OSPF, we compare typical packet paths from router R1 to R7 under different network conditions for both standard OSPF and TA-OSPF. These images highlight how TA-OSPF dynamically adapts to traffic congestion to select more efficient routes.

### Standard OSPF Routing (R1 to R7)

*(Assuming a scenario where the "shortest path" for standard OSPF becomes congested)*

![Standard OSPF Routing from R1 to R7](images/standard_ospf_r1_r7.png)
*Figure 1: Packet path from R1 to R7 using standard OSPF. Note that this path might become congested under heavy traffic, as standard OSPF does not consider real-time load.*

### TA-OSPF Routing (R1 to R7)

*(Assuming a scenario where TA-OSPF avoids the congested path taken by standard OSPF and finds an alternate, less congested route)*

![TA-OSPF Routing from R1 to R7](images/ta_ospf_r1_r7.png)
*Figure 2: Packet path from R1 to R7 using Traffic-Aware OSPF (TA-OSPF). TA-OSPF dynamically reroutes traffic away from congested links, selecting a path that might be longer but offers better performance by avoiding bottlenecks.*


## References

- Kurose, J. F., & Ross, K. W. (2020). *Computer Networking: A Top-Down Approach*.
- RFC 2328: OSPF Version 2
- RFC 2453: Routing Information Protocol (RIP) Version 2

## License

This project is provided for academic and research purposes.

## Acknowledgements

Developed as part of EN2150 - Communication Network Engineering, University of Moratuwa, Sri Lanka.

