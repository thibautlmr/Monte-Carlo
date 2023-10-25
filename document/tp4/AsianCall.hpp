// vim: set sw=4 ts=4 sts=4:
#include "pnl/pnl_random.h"
#include "pnl/pnl_cdf.h"
#pragma once

class AsianCall
{
public:
    AsianCall(double maturity, double volatility, double interest_rate, double spot, double strike, int nbTimeSteps);
    double m_maturity;
    double m_volatility;
    double m_interest_rate;
    double m_spot;
    double m_strike;
    int m_nbTimeSteps;
    PnlVect *m_underlyingTrajectory;
    PnlVect *m_brownianVect;
    /// Calculer les trajectoires
    void asset(PnlRng *rng);

    /// Calculer le payoff
    double payoff();

    double trapezoid();

    double logTrapezoid();

    double variableControleY();

    double variableControleZ();
};
