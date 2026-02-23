#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "PriorityHeap.hpp"
#include "FIFOQueue.hpp"
#include "Event.hpp"
#include "Customer.hpp"

class Simulation {
    private:
        const int lambda;
        const int mu;
        const int M;
        const int numEvents;

        int availableServers;
        double currentTime;
        double nextArrivalTime;

        double totalWaitTime;
        double totalServiceTime;
        double emptyTime;
        double emptyStartTime;
        int customerWaitedCount;
        int totalCustomersProcessed;
        int arrivalCount;

        double areaNumInSystem;
        double areaNumInQueue;
        double areaBusyServers;
        double lastEventTime;
        
        PriorityHeap pq;
        FIFOQueue fifo;

        void processNextEvent();
        void processStatistics(Customer* c);
    public:
        Simulation(int lambda, int mu, int M, int numEvents);
        void initialize();
        void run();
};

#endif