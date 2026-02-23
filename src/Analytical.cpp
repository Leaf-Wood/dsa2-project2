#include "Analytical.hpp"

void analytical(double lambda, double mu, int M) {
    double P0;
    double L;
    double Lq;
    double W;
    double Wq;
    double rho;

    rho = lambda / (M * mu);

    // compute (lambda/mu)^i / i!
    double a = lambda / mu;
    double sum = 0.0;
    double term = 1.0; // i = 0 term
    sum += term;       // i = 0
    for (int i = 1; i <= M - 1; ++i) {
        term *= a / i; // term = (a^i)/i!
        sum += term;
    }
    // compute the last term for i = M: (a^M)/M!
    term *= a / M; // now term = (a^M)/M!

    // Compute P0
    P0 = 1.0 / (sum + term * ( (double)M * mu / ( (double)M * mu - lambda ) ));

    // Lq = (lambda * mu * (a^M)) / ( (M-1)! * (M*mu - lambda)^2 ) * P0
    Lq = (lambda * mu * (term * M) / std::pow((double)M * mu - lambda, 2.0)) * P0;

    // L = Lq + lambda/mu
    L = Lq + a;

    // W = L / lambda
    W = L / lambda;
    // Wq = Lq / lambda
    Wq = Lq / lambda;

    std::cout << "Analytical Model:\n";
    std::cout << "P0 = " << P0 << "\n";
    std::cout << "L  = " << L << "\n";
    std::cout << "W  = " << W << "\n";
    std::cout << "Lq = " << Lq << "\n";
    std::cout << "Wq = " << Wq << "\n";
    std::cout << "rho= " << rho << "\n";
}
