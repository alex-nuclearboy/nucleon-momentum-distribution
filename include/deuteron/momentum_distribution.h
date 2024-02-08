#ifndef DEUTERON_MOMENTUM_DISTRIBUTION_H
#define DEUTERON_MOMENTUM_DISTRIBUTION_H

#include <fstream>
#include <vector>
#include <string>
#include "json.hpp" // For reading potential model configurations.

/**
 * @class MomentumDistributionCalculator
 * @brief Calculates the momentum distribution of nucleons within a deuteron 
 *        for using various nucleon-nucleon potential models.
 * 
 * This class provides the functionality to calculate and analyze the momentum 
 * distribution of nucleons inside a deuteron. It supports multiple potential models, 
 * allowing for an in-depth comparison of theoretical predictions.
 */
class MomentumDistributionCalculator {
public:
    /**
     * @brief Default constructor for initializing the MomentumDistributionCalculator object.
     */
    MomentumDistributionCalculator();
    
    /**
     * @brief Calculates the momentum distribution for nucleons inside 
     *        a deuteron and outputs the results to a specified file.
     * 
     * @param out_file Reference to an ofstream object for writing the distribution data.
     * @param alpha Alpha parameter defining the baseline mass scale for the potential model.
     * @param m_0 Mass coefficient for the model.
     * @param c Vector containing coefficients 'c' for the potential model calculation.
     * @param d Vector containing coefficients 'd' for the potential model calculation.
     */
    void CalculateDistribution(
        std::ofstream& out_file, double alpha, double m_0, 
        std::vector<double>& c, std::vector<double>& d);

private:
    const double sqrtpi2 = 0.7978845608;    // Pre-calculated sqrt(2/PI) for normalization.
    const double conversion = 0.19732697;   // Conversion factor from GeV/c to fm^-1 for momentum.
    const int steps = 400;  // Number of steps for discretizing the momentum distribution
    const double max_momentum = 0.4;    // Maximum momentum considered in GeV/c.
    
    /**
     * @brief Normalizes the coefficients 'c' and 'd' for the momentum distribution 
     *        calculation, ensuring the total probability is conserved and 
     *        the distribution accurately reflects the deuteron's structure.
     * 
     * @param c Reference to a vector of 'c' coefficients to be normalized.
     * @param d Reference to a vector of 'd' coefficients to be normalized.
     * @param m2 Reference to a vector of squared masses used in the normalization process.
     */
    void NormalizeCoefficients(
        std::vector<double>& c, std::vector<double>& d,
        std::vector<double>& m2);
};

#endif // DEUTERON_MOMENTUM_DISTRIBUTION_H
