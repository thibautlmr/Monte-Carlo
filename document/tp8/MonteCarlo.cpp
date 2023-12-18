#include <cmath>
#include "MonteCarlo.hpp"

MonteCarlo::MonteCarlo(Option *opt, BlackScholesModel *mod, PnlRng *rng)
{
  m_opt = opt;
  m_mod = mod;
  m_rng = rng;
}

void MonteCarlo::run(double &prix, double &std_dev, long long nSamples, int nTimeSteps)
{
  PnlVect *G = pnl_vect_new();
  PnlVect *path = pnl_vect_new();
  double sum = 0.;
  double sum_sq = 0.;
  for (int n = 0; n < nSamples; n++)
  {
    pnl_vect_rng_normal(G, nTimeSteps, m_rng);
    m_mod->simul(path, m_opt->m_maturity, nTimeSteps, G);
    double payoff = m_opt->payoff(path);
    sum += payoff;
    sum_sq += payoff * payoff;
  }
  prix = std::exp(-m_mod->m_r * m_opt->m_maturity) * sum / nSamples;
  std_dev = std::sqrt((std::exp(-2 * m_mod->m_r * m_opt->m_maturity) * sum_sq / nSamples - prix * prix) / nSamples);
}

void MonteCarlo::runImbrique(double &prix, double &std_dev, long long nbSamples, int nTimeSteps, double alpha)
{
  for (int m = 0; m < nbSamples; m++)
  {
    run(prix, std_dev, nbSamples, nTimeSteps);
  }
}