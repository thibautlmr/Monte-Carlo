// vim: set sw=4 ts=4 sts=4:
#include <iostream>
#include <cmath>
#include "BSScheme.hpp"

BSScheme::BSScheme(double maturity, double volatility, double interest_rate, double spot)
    : m_maturity(maturity), m_volatility(volatility), m_interest_rate(interest_rate),
      m_spot(spot)
{
}

void BSScheme::simulExact(PnlVect *path, const PnlVect *G, int n) const
{
    pnl_vect_resize(path, n + 1);
    LET(path, 0) = m_spot;
    for (int i = 1; i <= n; i++)
    {
        LET(path, i) = m_spot * exp((m_interest_rate - m_volatility * m_volatility / 2.) * i * m_maturity / n + m_volatility * GET(G, i) * sqrt(m_maturity / n));
    }
}

BSEuler::BSEuler(double maturity, double volatility, double interest_rate, double spot)
    : BSScheme(maturity, volatility, interest_rate, spot)
{
}

void BSEuler::simul(PnlVect *path, const PnlVect *G, int n) const
{
    pnl_vect_resize(path, n + 1);
    LET(path, 0) = m_spot;
    for (int i = 1; i <= n; i++)
    {
        LET(path, i) = GET(path, i - 1) * (1 + m_interest_rate * m_maturity / n + m_volatility * sqrt(m_maturity / n) * (GET(G, i) - GET(G, i - 1)));
    }
}

BSMilshtein::BSMilshtein(double maturity, double volatility, double interest_rate, double spot)
    : BSScheme(maturity, volatility, interest_rate, spot)
{
}

void BSMilshtein::simul(PnlVect *path, const PnlVect *G, int n) const
{
    pnl_vect_resize(path, n + 1);
    LET(path, 0) = m_spot;
    for (int i = 1; i <= n; i++)
    {
        LET(path, i) = GET(path, i - 1) * (1 + m_interest_rate * m_maturity / n + m_volatility * sqrt(m_maturity / n) * (GET(G, i) - GET(G, i - 1))) + 0.5 * m_volatility * m_volatility * (std::pow(GET(G, i) - GET(G, i - 1), 2) * m_maturity / n - m_maturity / n);
    }
}
