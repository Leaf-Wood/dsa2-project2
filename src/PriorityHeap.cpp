#include "PriorityHeap.hpp"

PriorityHeap::PriorityHeap() {
    size = 0;
    capacity = 199;
}

bool PriorityHeap::isEmpty() const {
    return size == 0;
}

void PriorityHeap::insert(const Event& e) {
    if(size >= capacity) {return;}
    heap[++size] = e;
    percolateUp(size);
}

Event PriorityHeap::removeMin() {
    if (isEmpty()) {return Event();}
    Event min = heap[1];
    heap[1] = heap[size--];
    percolateDown(1);
    return min;
}

void PriorityHeap::percolateUp(int index) {
    if(index == 1) {return;}
    int parent = index/2;
    if(heap[parent].time > heap[index].time) {
        swap(parent, index);
        percolateUp(parent);
    }
}

void PriorityHeap::percolateDown(int index){
    int left = index*2;
    int right = index*2 + 1;
    if(left > size) {return;} // no children

    //find smaller child
    int smaller = left;
    if(right <= size && heap[right].time < heap[left].time) {
        smaller = right;
    }
    //check if current is already smaller
    if(heap[index].time <= heap[smaller].time) {return;}
    
    swap(index, smaller);
    percolateDown(smaller);
}

void PriorityHeap::swap(int first, int second) {
    Event temp = heap[first];
    heap[first] = heap[second];
    heap[second] = temp;
}