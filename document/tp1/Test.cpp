#include <iostream>
#include "MonteCarlo.hpp"

using namespace std;

int main()
{
    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, time(NULL));
    double maturity[] = {1, 2, 3, 4, 5};
    int N[] = {100, 250, 500, 1000};
    int nbSamples = 50000;
    double a = 2;
    Brownian *brownian;
    MonteCarlo *monteCarlo;
    double theo, expec, bias, proporBias;
    for (int T = 0; T < 5; T++)
    {
        for (int n = 0; n < 4; n++)
        {
            brownian = new Brownian(maturity[T], N[n], rng);
            monteCarlo = new MonteCarlo(brownian, nbSamples, a);
            theo = monteCarlo->theoricalValue();
            expec = monteCarlo->expectedValue();
            bias = abs(theo - expec);
            proporBias = bias * sqrt(N[n]);
            std::cout << "Theorical value (T=" << maturity[T] << ") : " << theo << std::endl;
            std::cout << "Expected value by Monte-Carlo Simulation : (T=" << maturity[T] << "; N=" << N[n] << ") : " << expec << std::endl;
            std::cout << "Bias (T=" << maturity[T] << "; N=" << N[n] << ") : " << bias << std::endl;
            std::cout << "Bias in N^(1/2) (T=" << maturity[T] << "; N=" << N[n] << ") : " << proporBias << std::endl;
            std::cout << std::endl;
        }
    }
    return 0;
}