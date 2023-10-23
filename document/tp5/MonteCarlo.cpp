// vim: set sw=4 ts=4 sts=4:
#include <iostream>
#include <cmath>
#include "MonteCarlo.hpp"

MonteCarlo::MonteCarlo(Call &product, size_t samples)
    : m_product(product), m_samples(samples)
{
}

double MonteCarlo::delta_df(PnlRng *rng, double S0, double sigma, double r, double T, double K)
{
    double sumMinus = 0.;
    double sumPlus = 0.;
    double payoff, payoffMCPlus, payoffMCMinus;
    double epsilonn = pow(m_samples, -1 / 5);
    for (size_t i = 0; i < m_samples; i++)
    {
        double g = pnl_rng_normal(rng);
        sumPlus += m_product.payoff(S0 + epsilonn, sigma, r, T, K, g);
        sumMinus += m_product.payoff(S0 - epsilonn, sigma, r, T, K, g);
    }
    return (sumPlus - sumMinus) / (2 * m_samples * epsilonn);
}

double MonteCarlo::delta_likelihood(PnlRng *rng, double S0, double sigma, double r, double T, double K)
{
    double sum = 0.;
    double payoff;
    for (size_t i = 0; i < m_samples; i++)
    {
        double g = pnl_rng_normal(rng);
        sum += m_product.payoff(S0, sigma, r, T, K, g) * sqrt(T) * g / (sigma * T * S0);
    }
    return sum / m_samples;
}
