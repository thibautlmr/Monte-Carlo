#include "Brownian.hpp"

Brownian::Brownian(double maturity, int N, PnlRng *rng)
    : maturity_(maturity),
      brownian_(pnl_vect_create(N)),
      N_(N),
      rng_(rng)
{
}

void Brownian::simu()
{
    pnl_vect_set(brownian_, 0, 0.0);
    for (int k = 1; k < N_; k++)
    {
        pnl_vect_set(brownian_, k, pnl_vect_get(brownian_, k - 1) + sqrt(maturity_ / N_) * pnl_rng_normal(rng_));
    }
}

double Brownian::getTauA(double a)
{
    if (a > 0)
    {
        for (int t = 1; t < brownian_->size; t++)
        {
            if (PNL_GET(brownian_, t) >= a)
                return t * maturity_ / N_;
        }
    }
    else
    {
        for (int t = 1; t < brownian_->size; t++)
        {
            if (PNL_GET(brownian_, t) <= a)
                return t * maturity_ / N_;
        }
    }
    return maturity_;
}

double Brownian::getTauABrownianBridge(double a)
{
    brownianBridge((int)(getTauA(a) * N_ / maturity_), (int)(getTauA(a) * N_ / maturity_) + 1);
    if (a > 0)
    {
        for (int t = 1; t < brownian_->size; t++)
        {
            if (PNL_GET(brownian_, t) >= a)
                return t * maturity_ / N_;
        }
    }
    else
    {
        for (int t = 1; t < brownian_->size; t++)
        {
            if (PNL_GET(brownian_, t) <= a)
                return t * maturity_ / N_;
        }
    }
    return maturity_;
}

void Brownian::brownianBridge(int s, int t)
{
    double Bs = pnl_vect_get(brownian_, s);
    double Bt = pnl_vect_get(brownian_, t);
    pnl_vect_set(brownian_, 0, Bs);
    pnl_vect_set(brownian_, brownian_->size - 1, Bt);
    for (int u = 1; u < N_; u++)
    {
        pnl_vect_set(brownian_, u, (t - u) / (t - s) * Bs + (u - s) / (t - s) * Bt + sqrt((u - s) * (t - u) / (t - s)) * pnl_rng_normal(rng_));
    }
}
