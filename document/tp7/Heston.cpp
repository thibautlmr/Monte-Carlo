#include "Heston.hpp"

#include <cmath>

HestonModel::HestonModel(double r, double spot, double initVol, double sigma, double kappa, double theta, double rho)
  : Model(2, r)
  , m_spot(spot)
  , m_initVol(initVol)
  , m_sigma(sigma)
  , m_kappa(kappa)
  , m_theta(theta)
  , m_rho(rho)
{}

void HestonModel::simul(PnlVect *path, double maturity, double nTimeSteps, PnlMat *G)
{
  pnl_vect_resize(path, nTimeSteps + 1);
  // To be completed
}