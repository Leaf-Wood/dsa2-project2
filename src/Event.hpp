#ifndef EVENT_HPP
#define EVENT_HPP

#include "Customer.hpp"

enum EventType {ARRIVAL, DEPARTURE};

struct Event {
    double time;
    EventType type;
    Customer* cust;

    Event() : time(0.0), type(ARRIVAL), cust(nullptr) {}
    Event(double t, EventType ty, Customer* c = nullptr) : time(t), type(ty), cust(c) {}
};

#endif