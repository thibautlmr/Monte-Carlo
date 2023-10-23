// vim: set sw=4 ts=4 sts=4:
#include <iostream>
#include <cmath>
#include "MonteCarlo.hpp"

MonteCarlo::MonteCarlo(BSCall &product, size_t samples)
    : m_product(product), m_samples(samples)
{
}

void MonteCarlo::mc(double &prix, double &stddev, PnlRng *rng)
{
    double sum = 0.;
    double var = 0.;
    for (size_t i = 0; i < m_samples; i++)
    {
        m_product.assetEven(rng);
        double flowEven = m_product.payoff() * std::exp(-m_product.m_maturity * m_product.m_interest_rate);
        sum += flowEven;
        var += flowEven * flowEven;
    }
    prix = sum / m_samples;
    var = var / m_samples - prix * prix;
    stddev = std::sqrt(var / m_samples);
}

void MonteCarlo::mcAnti(double &prix, double &stddev, PnlRng *rng)
{
    double sum = 0.;
    double var = 0.;
    for (size_t i = 0; i < m_samples; i++)
    {
        m_product.assetEven(rng);
        double flowEven = m_product.payoff() * std::exp(-m_product.m_maturity * m_product.m_interest_rate);
        m_product.assetOdd();
        double flowOdd = m_product.payoff() * std::exp(-m_product.m_maturity * m_product.m_interest_rate);
        double flow = 0.5 * flowEven + 0.5 * flowOdd;
        sum += flow;
        var += flow * flow;
    }
    prix = sum / m_samples;
    var = var / m_samples - prix * prix;
    stddev = std::sqrt(var / m_samples);
}

void MonteCarlo::mcControle(double &prix, double &stddev, PnlRng *rng)
{
    double sum = 0.;
    double var = 0.;
    PnlVect *mcControleVect = pnl_vect_create(m_samples);
    PnlVect *flowEvenVect = pnl_vect_create(m_samples);
    for (size_t i = 0; i < m_samples; i++)
    {
        m_product.assetEven(rng);
        pnl_vect_set(mcControleVect, i, std::exp(-m_product.m_maturity * m_product.m_interest_rate) - pnl_vect_get(m_product.m_underlyingTrajectory, m_product.m_nbTimeSteps) + m_product.m_spot * std::exp(m_product.m_interest_rate * m_product.m_maturity));
        pnl_vect_set(flowEvenVect, i, m_product.payoff());
    }
    double meanControle = pnl_vect_sum(mcControleVect) / m_samples;
    sum = pnl_vect_sum(flowEvenVect);
    prix = (sum - m_samples * meanControle) / m_samples;
    for (int i = 0; i < m_samples; i++)
    {
        var += (pnl_vect_get(flowEvenVect, i) - meanControle) * (pnl_vect_get(flowEvenVect, i) - meanControle);
    }
    var = var / m_samples - prix * prix;
    stddev = std::sqrt(var / m_samples);
}
