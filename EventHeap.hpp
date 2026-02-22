#ifndef EVENTHEAP_HPP
#define EVENTHEAP_HPP

#include "Event.hpp"

class EventHeap {
    private:
        Event heap[200];
        int size;
        int capacity;
        void percolateUp(int index);
        void percolateDown(int index);
        void swap(int first, int second);
    public:
        EventHeap();
        bool isEmpty() const;
        void insert(const Event& e);
        Event removeMin();
};

#endif