#ifndef PLOT_GENERATOR_DEUTERON_H
#define PLOT_GENERATOR_DEUTERON_H

#include <vector>
#include <string>
#include <utility>  // For std::pair
#include "json.hpp" // For handling JSON data.

/**
 * @class PlotGeneratorDeuteron
 * @brief Facilitates the creation of plots to visualize momentum distributions 
 *        of nucleons within a deuteron.
 *
 * This class is designed to generate graphical representations for the momentum 
 * distributions of nucleons inside a deuteron, based on various nucleon-nucleon 
 * potential models.
 */
class PlotGeneratorDeuteron {
public:
    /**
     * Default constructor for initializing the PlotGeneratorDeuteron object.
     */
    PlotGeneratorDeuteron();
    
    /**
     * @brief Generates a plot for the momentum distribution of a single potential model.
     * 
     * @param model_name Name of the potential model being visualized.
     * @param data_file Path to the data file containing the momentum distribution.
     * @param plot_file Path where the generated plot will be saved.
     */
    void GenerateSinglePlot(
        const std::string& model_name, 
        const std::string& data_file, 
        const std::string& plot_file);

    /**
     * @brief Creates a combined plot for the momentum distributions derived 
     *        from all specified models.
     * 
     * @param models JSON object containing data for each model to be included in the plot.
     * @param combined_plot_file Path where the combined plot will be saved.
     */
    void GenerateCombinedPlot(
        const nlohmann::json& models, 
        const std::string& combined_plot_file);

};

#endif // DEUTERON_PLOT_GENERATOR_H