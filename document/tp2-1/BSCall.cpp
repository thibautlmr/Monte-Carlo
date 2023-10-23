// vim: set sw=4 ts=4 sts=4:
#include <iostream>
#include <cmath>
#include <algorithm>
#include "BSCall.hpp"

BSCall::BSCall(double maturity, double volatility, double interest_rate, double spot, double strike, int nbTimeSteps)
    : m_maturity(maturity), m_volatility(volatility), m_interest_rate(interest_rate),
      m_spot(spot), m_strike(strike), m_nbTimeSteps(nbTimeSteps)
{
    m_underlyingTrajectory = pnl_vect_create(m_nbTimeSteps + 1);
    m_brownianVect = pnl_vect_create(m_nbTimeSteps + 1);
}

void BSCall::assetEven(PnlRng *rng)
{
    pnl_vect_set(m_underlyingTrajectory, 0, m_spot);
    double brownian = 0;
    pnl_vect_set(m_brownianVect, 0, 0.);
    for (int i = 1; i <= m_nbTimeSteps; i++)
    {
        brownian += sqrt(m_maturity / m_nbTimeSteps) * pnl_rng_normal(rng);
        pnl_vect_set(m_brownianVect, i, brownian);
        pnl_vect_set(m_underlyingTrajectory, i, m_spot * std::exp((m_interest_rate - m_volatility * m_volatility / 2.) * i * m_maturity / m_nbTimeSteps + m_volatility * brownian));
    }
}

void BSCall::assetOdd()
{
    pnl_vect_set(m_underlyingTrajectory, 0, m_spot);
    for (int i = 1; i <= m_nbTimeSteps; i++)
    {
        pnl_vect_set(m_underlyingTrajectory, i, m_spot * std::exp((m_interest_rate - m_volatility * m_volatility / 2.) * i * m_maturity / m_nbTimeSteps + m_volatility * (-pnl_vect_get(m_brownianVect, i))));
    }
}

double BSCall::payoff()
{
    return std::max(m_strike * pnl_vect_max(m_underlyingTrajectory) - pnl_vect_get(m_underlyingTrajectory, m_nbTimeSteps), 0.);
}
