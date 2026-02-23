#ifndef PRIORITYHEAP_HPP
#define PRIORITYHEAP_HPP

#include "Event.hpp"

class PriorityHeap {
    private:
        Event heap[200];
        int size;
        int capacity;
        void percolateUp(int index);
        void percolateDown(int index);
        void swap(int first, int second);
    public:
        PriorityHeap();
        bool isEmpty() const;
        void insert(const Event& e);
        Event removeMin();
};

#endif