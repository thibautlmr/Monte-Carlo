// vim: set sw=4 ts=4 sts=4:
#include <iostream>
#include <fstream> // Inclure la bibliothèque pour travailler avec les fichiers
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
        double g = pnl_rng_normal(rng);
        double flow = m_product.payoff(g);
        sum += flow;
        var += flow * flow;
    }
    prix = sum / m_samples;
    var = var / m_samples - prix * prix;
    stddev = std::sqrt(var / m_samples);
}

double MonteCarlo::U(double G, double theta)
{
    double a = m_product.d_weight_plus(G, theta);
    double c = m_product.payoff(G);
    double b = pow(c, 2);
    return a * b;
}

void MonteCarlo::is(PnlVect *theta, double gamma, int n, PnlRng *rng)
{
    double G = pnl_rng_normal(rng);
    int alpha = 0;
    double beta = 0.75;
    double theta_i = 0.;
    double theta_i_and_half;
    double gamma_i_plus_1;
    for (int i = 1; i < n; i++)
    {
        gamma_i_plus_1 = gamma / pow(i + 2, beta);
        double u = U(G, theta_i);
        theta_i_and_half = theta_i - gamma_i_plus_1 * U(G, theta_i);
        if (theta_i_and_half * theta_i_and_half <= log(alpha + 1))
        {
            theta_i = theta_i_and_half;
        }
        else
        {
            theta_i = 0;
            alpha += 1;
        }
        pnl_vect_set(theta, i - 1, theta_i);
        G = pnl_rng_normal(rng);
    }

    // Déclarer le nom du fichier
    std::string nomFichier = "theta.txt";

    // Ouvrir le fichier en mode écriture (cette opération créera le fichier s'il n'existe pas)
    std::ofstream fichier(nomFichier);

    for (int i = 0; i <= n - 2; i++)
    {
        fichier << pnl_vect_get(theta, i) << std::endl;
    }

    // Fermer le fichier
    fichier.close();
}

void MonteCarlo::mcis(double &prix, double &stddev, double theta_n, PnlRng *rng)
{
    double sum = 0.;
    double var = 0.;
    for (size_t i = 0; i < m_samples; i++)
    {
        double g = pnl_rng_normal(rng);
        double flow = m_product.payoff(g, theta_n);
        sum += flow;
        var += flow * flow;
    }
    prix = sum / m_samples;
    var = var / m_samples - prix * prix;
    stddev = std::sqrt(var / m_samples);
}