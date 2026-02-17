#include "FIFOQueue.hpp"

FIFOQueue::FIFOQueue() {
    front = nullptr;
    back = nullptr;
};

bool FIFOQueue::isEmpty() const {
    return front == nullptr;
};

void FIFOQueue::enqueue(Customer* customer) {
    customer->nextCust = nullptr;
    if(isEmpty()) {
        front = customer;
        back = customer;
    } else {
        back->nextCust = customer;
        back = customer;
    }
};

Customer* FIFOQueue::dequeue() {
    if(isEmpty()) {return nullptr;}
    Customer* next = front;
    front = front->nextCust;
    if(front == nullptr) {back = nullptr;}
    return next;
};