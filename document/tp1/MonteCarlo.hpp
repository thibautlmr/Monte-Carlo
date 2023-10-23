#include "Brownian.hpp"

class MonteCarlo
{
public:
    Brownian *brownian_;
    PnlRng *rng_;
    int nbSamples_;
    double a_;
    MonteCarlo(Brownian *brownian, int nbSamples, double a);
    double expectedValue();
    double theoricalValue();
};