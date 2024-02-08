/**
 * @file momentum_distribution.cpp
 * @author AK <alex.nuclearboy@gmail.com>
 * @brief Implemention MomentumDistributionCalculator class for calculations of 
 *        nucleon momentum distribution inside a deuteron based on various 
 *        nucleon-nucleon potential models.
 * 
 * @details
 * The MomentumDistributionCalculator class calculates the momentum distribution 
 * of nucleons within a deuteron, considering various nucleon-nucleon potential models. 
 * The class uses potential model parameters specified in a JSON configuration file, 
 * performing calculations that are then output to data files for further analysis 
 * and visualization.
 *
 * @version 2.0
 * @date 2024-02-02
 * @note Last updated on 2024-02-08
 * @remark Licensed under the GNU General Public License version 3.0 (GPLv3).
 */

#include "../include/deuteron/momentum_distribution.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>

MomentumDistributionCalculator::MomentumDistributionCalculator() {}

/**
 * Normalizes the coefficients used in the momentum distribution calculation.
*/
void MomentumDistributionCalculator::NormalizeCoefficients(
    std::vector<double>& c, std::vector<double>& d, std::vector<double>& m2) 
{
    int n = c.size();

    // Calculate the last 'c' coefficient
    for (int i = 0; i < n - 1; i++) {c[n - 1] -= c[i];}

    int n2 = n - 3;
    int n1 = n2 + 1;
    int n0 = n1 + 1;

    double sum1 = 0., sum2 = 0., sum3 = 0.;
    
    // Summation for the normalization of d coefficients
    for (int j = 0; j <= n - 3; ++j) {
        sum1 += d[j] / m2[j];
        sum2 += d[j];
        sum3 += d[j] * m2[j];
    }
    
    // Loop to calculate the last three 'd' coefficients
    for (int i = 0; i < 3; ++i) {
        // Normalize the current d coefficient
        d[n2] = -m2[n1] * m2[n0] * sum1 + (m2[n1] + m2[n0]) * sum2 - sum3;
        d[n2] *= m2[n2] / ((m2[n0] - m2[n2]) * (m2[n1] - m2[n2]));
        
        // Cycle the indices for the next iteration
        std::swap(n0, n1);
        std::swap(n1, n2);
    }
}

/**
 * Calculates the momentum distribution of nucleons within a deuteron for a given 
 * potential model. This function computes the distribution by applying the specified 
 * model parameters, including the 'c' and 'd' coefficients that have been normalized 
 * by `NormalizeCoefficients`. It then outputs the calculated distribution to a file.
 */
void MomentumDistributionCalculator::CalculateDistribution(
    std::ofstream& out_file, double alpha, double m_0, 
    std::vector<double>& c, std::vector<double>& d) 
{
    const double dp = max_momentum / steps; // Increment in momentum per step
    double p[steps + 1], r[steps + 1], f_p[steps + 1]; // Arrays for momentum, reduced momentum, and momentum distribution
    double norm = 0; // Normalization constant
    
    int n = c.size();

    std::vector<double> m(n), m2(n);
        for (int i = 0; i < n; i++) {
            m[i] = alpha + i * m_0;            
            m2[i] = m[i] * m[i];
        }

    NormalizeCoefficients(c, d, m2);

    for (int j = 0; j <= steps; ++j) {

        p[j] = j * dp; // Calculate momentum in GeV/c
        r[j] = p[j] / conversion; // Convert momentum to reduced momentum (GeV/c to fm^-1)

        
        // Calculation for the Paris potential
        double U = 0., W = 0.;
        for (int i = 0; i < n; i++) {
            U += c[i] / (r[j] * r[j] + m2[i]);
            W += d[i] / (r[j] * r[j] + m2[i]);
        }
        
        U *= sqrtpi2; // s wave contribution
        W *= sqrtpi2; // d wave contribution
        
        // Calculate momentum distribution and accumulate normalization
        f_p[j] = r[j] * r[j] * (U * U + W * W);
        norm += f_p[j];
    }
    
    // Normalize and output the momentum distribution
    for (int i = 0; i <= steps; i++) {
        f_p[i] /= norm;
        out_file << p[i] << "\t" << f_p[i] << std::endl;
    }
    
    std::cout << "Momentum distribution calculation completed and saved to file." 
              << std::endl;

}
