// vim: set sw=4 ts=4 sts=4:
#pragma once

#include "BSCall.hpp"
#include "pnl/pnl_random.h"

class MonteCarlo
{
private:
    // Une instance de BSCall
    BSCall &m_product;
    // nombre de tirages
    size_t m_samples;

public:
    MonteCarlo(BSCall &product, size_t samples);
    void mc(double &prix, double &stddev, PnlRng *rng);
    void mcAnti(double &prix, double &stddev, PnlRng *rng);
    void mcControle(double &prix, double &stddev, PnlRng *rng);
};
