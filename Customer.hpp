#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

struct Customer {
    float arrivalTime;
    float startOfServiceTime;
    float departureTime;
    Customer * nextCust; // for linked FIFO
};

#endif