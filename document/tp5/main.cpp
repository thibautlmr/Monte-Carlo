// vim: set sw=4 ts=4 sts=4:

#include <iostream>
#include <ctime>
#include "MonteCarlo.hpp"
#include "Call.hpp"
#include "pnl/pnl_finance.h"

int main()
{
    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    double S0 = 100;
    double sigma = 0.25;
    double r = 0.02;
    double T = 2;
    double K = 120;
    pnl_rng_sseed(rng, std::time(NULL));
    Call call(1000);
    MonteCarlo monteCarlo(call, 50000);
    double realDelta;
    double realPrice;
    int test = pnl_cf_call_bs(S0, K, T, r, 0., sigma, &realPrice, &realDelta);
    std::cout << "Delta réel : " << realDelta << "\n";
    std::cout << "Delta par méthode des différences finies : " << monteCarlo.delta_df(rng, S0, sigma, r, T, K) << "\n";
    std::cout << "Delta par méthode du rapport de vraisemblance : " << monteCarlo.delta_likelihood(rng, S0, sigma, r, T, K) << "\n";
    pnl_rng_free(&rng);
    exit(0);
}
