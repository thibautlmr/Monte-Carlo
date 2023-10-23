// vim: set sw=4 ts=4 sts=4:
#include "pnl/pnl_random.h"
#pragma once

class BSCall
{
public:
    BSCall(double maturity, double volatility, double interest_rate, double spot, double strike, int nbTimeSteps);
    double m_maturity;
    double m_volatility;
    double m_interest_rate;
    double m_spot;
    double m_strike;
    int m_nbTimeSteps;
    PnlVect *m_underlyingTrajectory;
    PnlVect *m_brownianVect;
    /// Calculer les trajectoires
    void assetEven(PnlRng *rng);
    void assetOdd();

    /// Calculer le payoff
    double payoff();
};
