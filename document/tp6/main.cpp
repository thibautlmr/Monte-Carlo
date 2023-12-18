// vim: set sw=4 ts=4 sts=4:

#include <iostream>
#include <ctime>
#include <cmath>
#include "BSScheme.hpp"
#include "pnl/pnl_random.h"

int main()
{
    int N = 100;

    // Simulation du brownien
    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, std::time(NULL));
    PnlVect *G = pnl_vect_create(101);
    LET(G, 0) = pnl_rng_normal(rng);
    for (int i = 1; i <= N; i++)
    {
        LET(G, i) = GET(G, i - 1) + pnl_rng_normal(rng);
    }

    PnlVect *exactPath = pnl_vect_create(N + 1);
    LET(exactPath, 0) = 100;
    BSEuler euler(2., 0.2, 0.03, 100.);
    BSMilshtein milshtein(2., 0.2, 0.03, 100.);
    PnlVect *eulerPath = pnl_vect_create_from_double(N + 1, 0);
    PnlVect *milshteinPath = pnl_vect_create_from_double(N + 1, 0);
    double eulerError, milshteinError;

    euler.simulExact(exactPath, G, 100);

    euler.simul(eulerPath, G, 100);
    for (int i = 0; i <= N; i++)
    {
        eulerError += (GET(eulerPath, i) - GET(exactPath, i)) * (GET(eulerPath, i) - GET(exactPath, i));
    }
    eulerError = sqrt(eulerError) / N;
    std::cout << "Erreur de simulation du schéma d'Euler: " << eulerError << std::endl;

    milshtein.simul(milshteinPath, G, 100);
    for (int i = 0; i <= N; i++)
    {
        milshteinError += (GET(milshteinPath, i) - GET(exactPath, i)) * (GET(milshteinPath, i) - GET(exactPath, i));
    }
    milshteinError = sqrt(milshteinError) / N;
    std::cout << "Erreur de simulation du schéma de Milshtein: " << milshteinError << std::endl;
    pnl_rng_free(&rng);
    exit(0);
}
