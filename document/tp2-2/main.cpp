// vim: set sw=4 ts=4 sts=4:

#include <iostream>
#include <ctime>
#include "MonteCarlo.hpp"
#include "BSCall.hpp"

int main()
{
    int n = 500;
    double prix, stddev;
    BSCall product(2., 0.2, 0.03, 100., 120.);
    MonteCarlo pricer(product, 50000);
    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, std::time(NULL));
    pricer.mc(prix, stddev, rng);
    std::cout << "MC : \n";
    std::cout << "prix : " << prix << " (IC = " << stddev * 1.96 << ")\n";
    double gammas[] = {50, 5, 0.5, 0.05, 0.01};
    PnlVect *theta = pnl_vect_create(n - 1);
    // for (double gamma : gammas)
    // {
    //     pricer.is(theta, gamma, 100, rng);
    //     std::cout << "gamma : " << gamma << " (IC = " << stddev * 1.96 << ")\n";
    // }
    pricer.is(theta, 0.5, n, rng);
    double theta_n = pnl_vect_get(theta, n - 2);
    pricer.mcis(prix, stddev, theta_n, rng);
    std::cout << "MCIS : \n";

    std::cout << "prix : " << prix << " (IC = " << stddev * 1.96 << ")\n";
    pnl_rng_free(&rng);
    exit(0);
}
