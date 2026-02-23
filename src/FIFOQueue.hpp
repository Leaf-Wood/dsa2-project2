#ifndef FIFOQUEUE_HPP
#define FIFOQUEUE_HPP

#include "Customer.hpp"

class FIFOQueue {
    private:
        Customer* front;
        Customer* back;
        int size;
    public:
        FIFOQueue();
        bool isEmpty() const;
        void enqueue(Customer* customer);
        Customer* dequeue();
        int getSize() const;
};

#endif