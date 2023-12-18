#include "MonteCarlo.hpp"

MonteCarlo::MonteCarlo(Option *opt, Model *mod, PnlRng *rng)
{
  m_opt = opt;
  m_mod = mod;
  m_rng = rng;
}

void MonteCarlo::run(double &prix, double &std_dev, long long nSamples, int nTimeSteps)
{
  prix = 0.;
  std_dev = 0.;
  // To be completed

}