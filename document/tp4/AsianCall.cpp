// vim: set sw=4 ts=4 sts=4:
#include <iostream>
#include <cmath>
#include <algorithm>
#include "AsianCall.hpp"

AsianCall::AsianCall(double maturity, double volatility, double interest_rate, double spot, double strike, int nbTimeSteps)
    : m_maturity(maturity), m_volatility(volatility), m_interest_rate(interest_rate),
      m_spot(spot), m_strike(strike), m_nbTimeSteps(nbTimeSteps)
{
    m_underlyingTrajectory = pnl_vect_create(m_nbTimeSteps + 1);
    m_brownianVect = pnl_vect_create(m_nbTimeSteps + 1);
}

void AsianCall::asset(PnlRng *rng)
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

double AsianCall::payoff()
{
    return std::exp(-m_maturity * m_interest_rate) * std::max(trapezoid() - m_strike, 0.);
}

double AsianCall::trapezoid()
{
    double res = 0.;
    for (int i = 0; i < m_underlyingTrajectory->size - 1; i++)
    {
        res += m_maturity / (m_underlyingTrajectory->size - 1) * (pnl_vect_get(m_underlyingTrajectory, i) + pnl_vect_get(m_underlyingTrajectory, i + 1)) / 2;
    }
    return 1 / m_maturity * res;
}

double AsianCall::logTrapezoid()
{
    double res = 0.;
    for (int i = 0; i < m_underlyingTrajectory->size - 1; i++)
    {
        res += m_maturity / (m_underlyingTrajectory->size - 1) * (std::log(pnl_vect_get(m_underlyingTrajectory, i)) + std::log(pnl_vect_get(m_underlyingTrajectory, i + 1))) / 2;
    }
    return 1 / m_maturity * res;
}

double AsianCall::variableControleY()
{
    double Y = std::exp(logTrapezoid());
    double expectedY = pnl_vect_get(m_underlyingTrajectory, 0) * std::exp(m_interest_rate * m_maturity / 2 - m_volatility * m_volatility * m_maturity / 12);
    return Y - expectedY;
}

double AsianCall::variableControleZ()
{
    double Z = std::exp(-m_interest_rate * m_maturity) * std::max(std::exp(logTrapezoid()) - m_strike, 0.);
    double d = 1 / m_volatility * sqrt(3 / m_maturity) * (std::log(m_strike / pnl_vect_get(m_underlyingTrajectory, 0)) - (m_interest_rate - m_volatility * m_volatility / 2) * m_maturity / 2);
    double expectedZ = std::exp(-m_interest_rate * m_maturity) * (-m_strike * pnl_cdfnor(-d) + pnl_vect_get(m_underlyingTrajectory, 0) * std::exp((m_interest_rate - m_volatility * m_volatility / 6) * m_maturity / 2) * pnl_cdfnor(-d + m_volatility * sqrt(m_maturity / 3)));
    return Z - expectedZ;
}