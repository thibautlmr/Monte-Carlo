// vim: set sw=4 ts=4 sts=4:
#include <iostream>
#include <cmath>
#include <algorithm>
#include "Call.hpp"

Call::Call(int nbTimeSteps)
{
    m_underlyingTrajectory = pnl_vect_create(m_nbTimeSteps + 1);
    m_brownianVect = pnl_vect_create(m_nbTimeSteps + 1);
}

double Call::payoff(double S0, double sigma, double r, double T, double K, double g)
{
    double ST = S0 * exp((r - sigma * sigma / 2) * T + sigma * sqrt(T) * g);
    return std::max(ST - K, 0.) * exp(-r * T);
}

double Call::asset(double S0, double sigma, double r, double T, double K, double g)
{
    return S0 * exp((r - sigma * sigma / 2) * T + sigma * sqrt(T) * g);
}

void Call::delta_df()
{
}