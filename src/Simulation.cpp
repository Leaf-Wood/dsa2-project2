#include "Simulation.hpp"
#include <iostream>
#include <cmath>
#include <random>

static double getNextRandomInterval(int avg) {
    double u = (double)(std::rand()) / (RAND_MAX + 1.0);
    if (u <= 0.0) u = 1.0/(RAND_MAX + 1.0);
    return -(1.0 / avg) * std::log(u);
}

Simulation::Simulation(int lambda, int mu, int M, int numEvents)
    : lambda(lambda), mu(mu), M(M), numEvents(numEvents), 
      availableServers(M), currentTime(0.0), nextArrivalTime(0.0), 
      totalWaitTime(0.0), totalServiceTime(0.0), emptyTime(0.0), emptyStartTime(-1.0),
      customerWaitedCount(0), totalCustomersProcessed(0),
      arrivalCount(0), areaNumInSystem(0.0), areaNumInQueue(0.0),
      areaBusyServers(0.0), lastEventTime(0.0) {}

void Simulation::initialize() {
    nextArrivalTime = getNextRandomInterval(lambda);

    Customer* c = new Customer(nextArrivalTime);
    Event e(nextArrivalTime, ARRIVAL, c);
    pq.insert(e);
    arrivalCount++;
}

void Simulation::run() {
    while(!pq.isEmpty() && totalCustomersProcessed < numEvents) {
        while (arrivalCount <= M + 1) {
            nextArrivalTime += getNextRandomInterval(lambda);
            Customer* c = new Customer(nextArrivalTime);
            Event e(nextArrivalTime, ARRIVAL, c);
            pq.insert(e);
            arrivalCount++;
        }
        processNextEvent();
    }

    double totalSimTime = currentTime;
    double L  = areaNumInSystem / totalSimTime;
    double Lq = areaNumInQueue  / totalSimTime;
    double rho = areaBusyServers / (M * totalSimTime);

    // If simulation ended while system was empty, include the remaining empty time
    if (emptyStartTime >= 0.0) {
        emptyTime += totalSimTime - emptyStartTime;
        emptyStartTime = -1.0;
    }
    double P0 = 0.0;
    if (totalSimTime > 0.0) {
        P0 = emptyTime / totalSimTime;
    }

    std::cout << "Simulation Results:\n";
    std::cout << "Total customers processed: " << totalCustomersProcessed << "\n";
    std::cout << "Average service time: " << totalServiceTime / totalCustomersProcessed << "\n";
    std::cout << "Probability a customer waited: " << (double)customerWaitedCount / totalCustomersProcessed << "\n";
    std::cout << "P0 = " << P0 << "\n";
    std::cout << "L  = " << L << "\n";
    std::cout << "W  = " << L/lambda << "\n";
    std::cout << "Lq = " << Lq << "\n";
    std::cout << "Wq = " << totalWaitTime / totalCustomersProcessed << "\n";
    std::cout << "rho= " << rho << "\n\n";
}

void Simulation::processNextEvent() {
    Event e = pq.removeMin();
    currentTime = e.time;
    
    // delta t
    double delta = currentTime - lastEventTime;
    // compute old state
    int busyServers = M - availableServers;
    int inQueue = fifo.getSize();
    int inSystem = busyServers + inQueue;
    // accumulate areas
    areaNumInSystem += inSystem * delta;
    areaNumInQueue  += inQueue  * delta;
    areaBusyServers += busyServers * delta;
    // update last event time
    lastEventTime = currentTime;
    
    if(e.type == ARRIVAL) {
        if (emptyStartTime >= 0.0) {
            emptyTime += currentTime - emptyStartTime;
            emptyStartTime = -1.0;
        }

        Customer* c = e.cust;
        arrivalCount--;
        if(availableServers > 0) {
            availableServers--;

            c->startOfServiceTime = currentTime;
            double interval = getNextRandomInterval(mu);
            c->departureTime = currentTime + interval;

            Event depEvent(c->departureTime, DEPARTURE, c);
            pq.insert(depEvent);
        } else {
            fifo.enqueue(c);
        }
    } else {
        availableServers++;
        processStatistics(e.cust);
        delete e.cust;

        // compute new inSystem after this departure
        int busyServersNow = M - availableServers;
        int inQueueNow = fifo.getSize();
        int inSystemNow = busyServersNow + inQueueNow;
        if (inSystemNow == 0) {
            // system just became empty at currentTime
            emptyStartTime = currentTime;
        }

        if(!fifo.isEmpty()) {
            Customer* c = fifo.dequeue();
            availableServers--;

            c->startOfServiceTime = currentTime;
            double interval = getNextRandomInterval(mu);
            c->departureTime = currentTime + interval;

            Event depEvent(c->departureTime, DEPARTURE, c);
            pq.insert(depEvent);
        }
    }
}

void Simulation::processStatistics(Customer* c) {
    double wait = c->startOfServiceTime - c->arrivalTime;
    double service = c->departureTime - c->startOfServiceTime;

    totalWaitTime += wait;
    totalServiceTime += service;

    if(wait > 0) {customerWaitedCount++;}
    totalCustomersProcessed++;
}
