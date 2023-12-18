// vim: set sw=4 ts=4 sts=4:

#include <iostream>
#include <ctime>
#include "MonteCarlo.hpp"
#include "BSCall.hpp"

int main()
{
    double prix, stddev;
    BSCall product(2., 0.25, 0.02, 100., 0.95, 24);
    MonteCarlo pricer(product, 50000);
    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, std::time(NULL));
    pricer.mc(prix, stddev, rng);
    std::cout << "prix : " << prix << " (IC = " << stddev * 1.96 << ")\n";
    std::cout << "stdDev : " << stddev << "\n";
    std::cout << "\n";
    pricer.mcAnti(prix, stddev, rng);
    std::cout << "prix Anti : " << prix << " (IC = " << stddev * 1.96 << ")\n";
    std::cout << "stdDev Anti : " << stddev << "\n";
    std::cout << "\n";
    pricer.mcControle(prix, stddev, rng);
    std::cout << "prix Controle : " << prix << " (IC = " << stddev * 1.96 << ")\n";
    std::cout << "stdDev Controle : " << stddev << "\n";
    std::cout << "\n";

    pnl_rng_free(&rng);
    exit(0);
}
