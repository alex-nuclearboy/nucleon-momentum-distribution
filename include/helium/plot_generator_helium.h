#ifndef PLOT_GENERATOR_HELIUM_H
#define PLOT_GENERATOR_HELIUM_H

#include <vector>
#include <string>
#include <utility> // For std::pair

/**
 * @class PlotGeneratorHelium
 * @brief Generates plots for visualizing the momentum distribution 
 *        of N* resonance within a ^3He nucleus.
 */
class PlotGeneratorHelium {
public:
    /**
     * @brief Default constructor for PlotGeneratorHelium.
     * 
     * Initializes a new instance of the PlotGeneratorHelium class.
     */
    PlotGeneratorHelium() = default;

    /**
     * @brief Generates a plot combining multiple datasets.
     * 
     * Takes several sets of momentum and probability density data, merges them 
     * into a single plot, and saves the visual representation to a specified path.
     *
     * @param data_sets Vector of pairs, each containing vectors of momentum and 
     *                  corresponding probability densities.
     * @param output_file_path Path for saving the generated plot.
     */
    void GenerateCombinedPlot(
        const std::vector<std::pair<std::vector<float>,
        std::vector<float>>>& data_sets,
        const std::string& output_file_path);

private:
    /**
     * @brief Customizes the appearance of the plot.
     * 
     * Applies predefined styling options to the plot to improve its readability 
     * and aesthetic appeal.
     */
    void CustomizePlotAppearance();
};

#endif // HELIUM_PLOT_GENERATOR_H
