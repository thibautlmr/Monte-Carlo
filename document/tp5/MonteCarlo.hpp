// vim: set sw=4 ts=4 sts=4:
#pragma once

#include "Call.hpp"
#include "pnl/pnl_random.h"

class MonteCarlo
{
private:
    // Une instance de BSCall
    Call &m_product;
    // nombre de tirages
    size_t m_samples;

public:
    MonteCarlo(Call &product, size_t samples);
    double delta_df(PnlRng *rng, double S0, double sigma, double r, double T, double K);
    double delta_likelihood(PnlRng *rng, double S0, double sigma, double r, double T, double K);
};
