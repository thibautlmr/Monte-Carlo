// vim: set sw=4 ts=4 sts=4:
#pragma once

#include "AsianCall.hpp"
#include "pnl/pnl_random.h"

class MonteCarlo
{
private:
    // Une instance de BSCall
    AsianCall &m_product;
    // nombre de tirages
    size_t m_samples;

public:
    MonteCarlo(AsianCall &product, size_t samples);
    void mc(double &prix, double &stddev, PnlRng *rng);
    void mcControleY(double &prix, double &stddev, PnlRng *rng);
    void mcControleZ(double &prix, double &stddev, PnlRng *rng);
};
