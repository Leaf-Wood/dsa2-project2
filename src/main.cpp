#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "Simulation.hpp"
#include "Analytical.hpp"

int main() {
    std::string INPUT_FILE = "test1.txt";
    std::ifstream infile("tests/" + INPUT_FILE);

    if (!infile) {
        std::cout << "Could not open input file.\n";
        return 1;
    }

    std::srand(std::time(0));
    int lambda, mu, M, numEvents;
    infile >> lambda >> mu >> M >> numEvents;

    Simulation sim(lambda, mu, M, numEvents);
    sim.initialize();
    sim.run();

    analytical(lambda, mu, M);
}