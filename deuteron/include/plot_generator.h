#ifndef DEUTERON_PLOT_GENERATOR_H_
#define DEUTERON_PLOT_GENERATOR_H_

#include <string>
#include "json.hpp"

/**
 * @class PlotGenerator
 * @brief Class for creating plots to visually represent the momentum 
 *        distribution of nucleons inside a deuteron 
 */

class PlotGenerator {
public:
    /**
     * @brief Constructs a new PlotGenerator object.
     * 
     * Initializes a new instance of the PlotGenerator class.
     */
    PlotGenerator();
    
    /**
     * @brief Generates a plot for a single model's momentum distribution.
     * 
     * @param model_name Name of the potential model.
     * @param data_file Filename of the data used for plotting.
     * @param plot_file Filename for the output plot.
     */
    void GenerateSinglePlot(const std::string& model_name, const std::string& data_file, const std::string& plot_file);

    /**
     * @brief Generates a combined plot for all models' momentum distributions.
     * 
     * @param models JSON object containing the models data.
     * @param combined_plot_file Filename for the combined output plot.
     */
    void GenerateCombinedPlot(const nlohmann::json& models, const std::string& combined_plot_file);

};

#endif // DEUTERON_PLOT_GENERATOR_H_