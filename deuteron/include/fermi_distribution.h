// fermi_distribution.h
#ifndef FERMI_DISTRIBUTION_H
#define FERMI_DISTRIBUTION_H

#include <fstream>
#include <vector>
#include <string>
#include "json.hpp"

/**
 * @brief Class to calculate Fermi nucleon momentum distributions for various models.
 * 
 * This class provides functionality to normalize coefficients, calculate momentum distributions,
 * and generate plots for individual models as well as a combined plot for all models.
 */

class FermiDistributionCalculator {
public:
    /**
     * @brief Constructs a new Fermi Distribution Calculator object.
     */
    FermiDistributionCalculator();

    /**
     * @brief Normalizes the coefficients for the momentum distribution calculation.
     * 
     * @param c Vector of c coefficients to be normalized.
     * @param d Vector of d coefficients to be normalized.
     * @param m2 Vector of squared mass coefficients.
     */
    void normalizeCoefficients(std::vector<double>& c, std::vector<double>& d, std::vector<double>& m2);

    /**
     * @brief Calculates the momentum distribution and writes the result to a file.
     * 
     * @param out_file Output file stream to write the distribution data.
     * @param alpha Alpha parameter for the model.
     * @param m_0 Mass coefficient.
     * @param c Vector of c coefficients.
     * @param d Vector of d coefficients.
     */
    void calculate(std::ofstream& out_file, double alpha, double m_0, std::vector<double>& c, std::vector<double>& d);

    /**
     * @brief Generates a plot for a single model's momentum distribution.
     * 
     * @param model_name Name of the model.
     * @param data_file Filename of the data used for plotting.
     * @param plot_file Filename for the output plot.
     */
    void generate_plot(const std::string& model_name, const std::string& data_file, const std::string& plot_file);

    /**
     * @brief Generates a combined plot for all models' momentum distributions.
     * 
     * @param models JSON object containing the models data.
     * @param combined_plot_file Filename for the combined output plot.
     */
    void generate_combined_plot(const nlohmann::json& models, const std::string& combined_plot_file);

private:
    const double sqrtpi2 = 0.7978845608; // Square root of 2/PI    
    const double conversion = 0.197327;  // Conversion factor for momentum (GeV/c to fm^-1)
    const int steps = 400; // Number of steps from 0 to 0.4 GeV/c
    const double max_momentum = 0.4; // Maximum momentum
    double alpha;
    double m_0;    
};

#endif // FERMI_DISTRIBUTION_H
