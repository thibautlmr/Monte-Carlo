#include "MultiLevelMonteCarlo.hpp"

MultiLevelMonteCarlo::MultiLevelMonteCarlo(Option *opt, Model *mod, PnlRng *rng)
{
  m_opt = opt;
  m_mod = mod;
  m_rng = rng;
}

long long MultiLevelMonteCarlo::nSamples(int level, int m, int L)
{
  return 0;
}


void MultiLevelMonteCarlo::collapse(PnlMat *Gcrude, PnlMat *Gfine, int m)
{
  // To be completed.
}

void MultiLevelMonteCarlo::run(double &prix, double &std_dev, int m, int L)
{
  PnlVect *pathCrude = pnl_vect_new();
  PnlVect *pathFine = pnl_vect_new();
  PnlMat *Gcrude = pnl_mat_new();
  PnlMat *Gfine = pnl_mat_new();
  // Treat Level 0

  // Loop on all the levels > 0
  for (int l = 1; l < L; l++) {
    long long Nl = nSamples(l, m, L);
    int ml = pnl_pow_i(m, l);
    double sum = 0.;
    for (int i = 0; i < Nl; i++) {
      pnl_mat_rng_normal(Gfine, ml, 2, m_rng);

      // Simulation of the fine model
      m_mod->simul(pathFine, m_opt->m_maturity, ml, Gfine);
      sum += m_opt->payoff(pathFine);

      // Simulation of the crude model
      collapse(Gcrude, Gfine, m);
      m_mod->simul(pathCrude, m_opt->m_maturity, ml / m, Gcrude);
      sum -= m_opt->payoff(pathCrude);
    }
    sum /= Nl;
  }

  pnl_mat_free(&Gcrude);
  pnl_mat_free(&Gfine);
  pnl_vect_free(&pathCrude);
  pnl_vect_free(&pathFine);
}
