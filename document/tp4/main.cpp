// vim: set sw=4 ts=4 sts=4:

#include <iostream>
#include <ctime>
#include "MonteCarlo.hpp"
#include "AsianCall.hpp"

int main()
{
    double prix, stddev;
    AsianCall product(2., 0.25, 0.02, 100., 90, 24);
    MonteCarlo pricer(product, 50000);
    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, std::time(NULL));
    pricer.mc(prix, stddev, rng);
    std::cout << "Monte-Carlo classique : \n";
    std::cout << "prix : " << prix << " (IC = " << stddev * 1.96 << ")\n";
    std::cout << "stdDev : " << stddev << "\n";
    std::cout << "\n";

    pricer.mcControleY(prix, stddev, rng);
    std::cout << "Monte-Carlo avec variable de contôle Y : \n";
    std::cout << "prix : " << prix << " (IC = " << stddev * 1.96 << ")\n";
    std::cout << "stdDev : " << stddev << "\n";
    std::cout << "\n";

    pricer.mcControleZ(prix, stddev, rng);
    std::cout << "Monte-Carlo avec variable de contôle Z : \n";
    std::cout << "prix : " << prix << " (IC = " << stddev * 1.96 << ")\n";
    std::cout << "stdDev : " << stddev << "\n";
    std::cout << "\n";
    pnl_rng_free(&rng);
    exit(0);
}
