#ifndef FIFOQUEUE_HPP
#define FIFOQUEUE_HPP

#include "Customer.hpp"

class FIFOQueue {
    private:
        Customer* front;
        Customer* back;
    public:
        FIFOQueue();
        bool isEmpty() const;
        void enqueue(Customer* customer);
        Customer* dequeue();
};

#endif