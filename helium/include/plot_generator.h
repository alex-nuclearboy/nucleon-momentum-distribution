#ifndef HELIUM_PLOT_GENERATOR_H
#define HELIUM_PLOT_GENERATOR_H

#include <vector>
#include <string>
#include <utility> // For std::pair

/**
 * @class PlotGenerator
 * @brief Class for creating plots to visually represent the momentum 
 *        distribution of N* resonance inside the helium nucleus. 
 */

class PlotGenerator {
public:
    /**
     * @brief Construct a new PlotGenerator object.
     */
    PlotGenerator() = default;

    /**
     * @brief Generates a combined plot from multiple data sets.
     * 
     * This method takes multiple sets of momentum and probability density data,
     * combines them into a single plot, and saves the result to the specified
     * output file path.
     * 
     * @param data_sets A vector of pairs, each containing vectors of momentum
     *                  values and their corresponding probability densities.
     * @param output_file_path The path where the generated plot should be saved.
     */
    void GenerateCombinedPlot(const std::vector<std::pair<std::vector<float>, std::vector<float>>>& data_sets, const std::string& output_file_path);

private:
    /**
     * @brief Customizes the appearance of the plot.
     * 
     * Applies a set of predefined styling options to the plot to enhance
     * readability and visual appeal.
     */
    void CustomizePlotAppearance();
};

#endif // HELIUM_PLOT_GENERATOR_H
