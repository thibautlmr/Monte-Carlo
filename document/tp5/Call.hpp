// vim: set sw=4 ts=4 sts=4:
#include "pnl/pnl_random.h"
#pragma once

class Call
{
public:
    Call(int nbTimeSteps);
    double m_strike;
    int m_nbTimeSteps;
    PnlVect *m_underlyingTrajectory;
    PnlVect *m_brownianVect;
    /// Calculer les trajectoires
    double asset(double S0, double sigma, double r, double T, double K, double g);
    /// Calculer le payoff
    double payoff(double S0, double sigma, double r, double T, double K, double g);
    void delta_df();
};
