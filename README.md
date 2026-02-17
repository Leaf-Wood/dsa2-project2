# A Queue Simulation
Data Structures and Algorithms II - Programming Project 2 - A Queue Simulation

Simulate customers passing through the system by using BOTH a priority queue and a standard FIFO queue.

The customers will arrive randomly with times following the Poisson distribution. 
- Suppose a store averages 10 arrivals per hour. The Poisson distribution can be used to determine the probability of no arrivals, 1 arrival, 5 arrivals, 15 arrivals, etc., given that average. 
- The Poisson distribution can be transformed into a continuous probability distribution called a negative exponential distribution (which we will use) which produces random time intervals which, when run in large numbers, will yield an appropriate average time. For instance, if average arrivals are 3 per time unit (which we will NOT specify, could be milli-seconds, seconds, or hours), the average of all the time intervals would be .333.

Use a priority queue prioritized by the time of the events in the simulation. At any point in the simulation, the next event will be either:
- a customer arrives for service (an arrival event)
- a customer's service is complete (a departure event)

Upon arrival, we check for an available service channel. If one exists, the customer immediately commences service. We compute a completion time, and that time goes into the priority queue as a future event. If all service channels are in use, the customer goes into the FIFO queue to wait for a server to become available. We know the time the customer leaves the FIFO queue to get service because that is exactly the time when service was completed for the prior customer (the simulation just processed a departure event).

**Note:** You will need a priority queue. You must implement a heap as described in class. You are NOT to use FIFO queue you implement with modified insert() to maintain priority or the STL version of priority_queue.

**Program Execution**
Your simulation will NOT be interactive. Your program should read and process two files, each holding values for lambda, mu, M, and the number of events to simulate

You will keep the priority queue small, of length 200. So long as more arrivals remain, you can easily add arrivals in O(lgn) time. You will do so when the number of events (arrivals and departures) in the PQ gets to M+1. You will carry out the simulation by placing the first group of arrivals into the priority queue and then entering the event loop processing arrivals and departures. If the event is an arrival, you first check for an available server. If one is present, you can generate the departure time and add it to the priority queue, and note that the server is busy. If no servers are available, the customer goes into the FIFO queue. Eventually a departure will occur. The departure frees a server that can process the next arrival OR a customer waiting in the FIFO queue. You must tally statistics as customers' service is completed. These are the amount of time waiting for service and the amount of time actually getting service.

**Computing Arrival and Service Time Intervals** – These times will be modeled by a negative exponential distribution. The following pseudocode contains an algorithm for computing a time interval between events with random distribution from an infinite population given the average number of events (avg) per unit time:
```
GetNextRandomInterval(avg)
    Generate a random float f on the interval (0..1]
    Compute intervalTime as -1 * (1.0/avg) * ln(f) //natural logarithm of f
    return intervalTime
```

Note that the parameter (avg) could be either the average number of arrivals (lambda) or the average number of customers that can be provided service (mu) in unit time. That is why it is generically named avg.

**Simulation Measures to compute**
From your simulation, you are to determine simulated values for items determined analytically by formulas 1, 3, 5, and 6. Additionally, you will report the probability of having to wait for service (the number of customers who had to wait/total customers).

To get the simulated value of Po, accumulate all the time after a departure of the last customer being served (leaving no one in the system) until the next arrival. To simulate rho, compute the total time servers were available (M * total simulation time) and divide it into the total amount of service time.

Your output (to the console) will display the analytical model and simulation measures in such a way that you can compare them so that you can see how well your simulation results matched predicted values.

**Example input and results:**
The analytical model should produce these results for the following inputs:
- lambda (l) = 2
- mu (m) = 3
- M = 2

Po = 0.5
L = 0.75
W = 0.375
Lq = 0.083
Wq = 0.0417

**Output**

All output will be to the console. You will display all the measures in the analytical model and the specified measures from the simulation.

**Deliverables:**

You must include the following in your submission to the dropbox:
- Your UML diagram in its own file entitled "UMLDiagram." (a .pdf or .jpg Export from Dia if you use that program)
- A user’s manual in its own file entitled "UsersManual"  (a Word doc or .pdf)
- Source code
- The two specified input files test1.txt and test2.txt
- A makefile