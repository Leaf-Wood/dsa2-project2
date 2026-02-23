#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

struct Customer {
    double arrivalTime;
    double startOfServiceTime;
    double departureTime;
    double pqTime; // time placed into PQ
    Customer * nextCust; // for linked FIFO

    Customer(double arrival = 0.0)
      : arrivalTime(arrival),
        startOfServiceTime(-1.0),
        departureTime(-1.0),
        pqTime(-1.0),
        nextCust(nullptr) {}
};

#endif