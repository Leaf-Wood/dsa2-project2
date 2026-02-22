#ifndef EVENT_HPP
#define EVENT_HPP

enum EventType {ARRIVAL, DEPARTURE};

struct Event {
    float time;
    EventType type;
};

#endif