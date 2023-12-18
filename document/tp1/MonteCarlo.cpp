#include "MonteCarlo.hpp"
#include "iostream"

using namespace std;

MonteCarlo::MonteCarlo(Brownian *brownian, int nbSamples, double a)
    : brownian_(brownian),
      nbSamples_(nbSamples),
      a_(a)
{
}

double MonteCarlo::expectedValue()
{
    double sum = 0;
    for (int i = 0; i < nbSamples_; i++)
    {
        brownian_->simu();
        if (brownian_->getTauA(a_) == brownian_->maturity_)
        {
            sum += brownian_->getTauA(a_);
        }
        else
        {
            sum += brownian_->getTauABrownianBridge(a_);
        }
    }
    return (sum / nbSamples_);
}

double MonteCarlo::theoricalValue()
{
    double firstMember = brownian_->maturity_ * (1 - (pnl_sf_gamma_inc(0.5, (a_ * a_) / (2 * brownian_->maturity_)) / sqrt(M_PI)));
    double secondMember = (a_ * a_) / (2 * sqrt(M_PI)) * pnl_sf_gamma_inc(-0.5, (a_ * a_) / (2 * brownian_->maturity_));
    return firstMember + secondMember;
}
