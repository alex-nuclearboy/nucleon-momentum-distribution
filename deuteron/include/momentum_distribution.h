#ifndef DEUTERON_MOMENTUM_DISTRIBUTION_H_
#define DEUTERON_MOMENTUM_DISTRIBUTION_H_

#include <fstream>
#include <vector>
#include <string>
#include "json.hpp"

/**
 * @class MomentumDistributionCalculator
 * @brief Class to calculate nucleon momentum distributions inside deuteron 
 *        for various N-N potential models.
 */
class MomentumDistributionCalculator {
public:
    /**
     * @brief Constructs a new MomentumDistributionCalculator object.
     * 
     * Initializes a new instance of the MomentumDistributionCalculator class.
     */
    MomentumDistributionCalculator();
    
    /**
     * @brief Calculates the momentum distribution and writes the result to a file.
     * 
     * @param out_file Output file stream to write the distribution data.
     * @param alpha Alpha parameter for the potential model.
     * @param m_0 Mass coefficient.
     * @param c Vector of c coefficients.
     * @param d Vector of d coefficients.
     */
    void CalculateDistribution(std::ofstream& out_file, double alpha, double m_0, std::vector<double>& c, std::vector<double>& d);

private:
    const double sqrtpi2 = 0.7978845608; // Square root of 2/PI    
    const double conversion = 0.19732697;  // Conversion factor for momentum (GeV/c to fm^-1)
    const int steps = 400; // Number of steps in the momentum distribution
    const double max_momentum = 0.4; // [GeV/c] - maximum momentum
    double alpha;
    double m_0;

    /**
     * @brief Normalizes the coefficients for the momentum distribution calculation.
     * 
     * @param c Vector of c coefficients to be normalized.
     * @param d Vector of d coefficients to be normalized.
     * @param m2 Vector of squared mass coefficients.
     */
    void NormalizeCoefficients(std::vector<double>& c, std::vector<double>& d, std::vector<double>& m2);
};

#endif // DEUTERON_MOMENTUM_DISTRIBUTION_H_
