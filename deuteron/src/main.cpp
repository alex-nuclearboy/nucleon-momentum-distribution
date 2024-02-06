/**
 * @file main.cpp
 * @brief Main program entry point for calculation of momentum distribution 
 *        of nucleons inside a deuteron. 
 * 
 * This file loads potential model parameters from a JSON configuration file,
 * calculates the nucleon momentum distribution for each model,
 * and generates output files and plots for each.
 *
 * @author Aleksander Khreptak
 * @email aleksander.khreptak@alumni.uj.edu.pl
 * @date 02 Feb 2024
 * @last_updated 06 Feb 2024
 *
 * @license This code is licensed under the GNU General Public License version 3.0.
 */

#include "../include/momentum_distribution.h"
#include "../include/json.hpp"
#include <fstream>
#include <iostream>
#include <vector>

using json = nlohmann::json;

int main() {

    // Load model parameters from the JSON file
    std::ifstream json_file("src/models_config.json");
    if (!json_file.is_open()) {
        std::cerr << "Error: Failed to open JSON file for reading." << std::endl;
        return -1;
    }
    json model_params;
    json_file >> model_params;
    json_file.close();

    MomentumDistributionCalculator distribution;

    // Process each model defined in the JSON configuration.
    for (const auto& model : model_params["models"]) {
        std::string model_name = model["name"];
        double alpha = model["alpha"];
        double m_0 = model["m_0"];
        std::vector<double> c = model["parameters"]["c"];
        std::vector<double> d = model["parameters"]["d"];

        // Construct output filename based on the model name.
        std::ofstream out_file("data/" + model_name + "_momentum_distribution.txt");
        if (!out_file.is_open()) {
            std::cerr << "Error: Failed to open output file for writing for " << model_name << " model." << std::endl;
            continue; // Skip this model if the file can't be opened
        }

        // Perform the calculation and generate output.        
        distribution.CalculateDistribution(out_file, alpha, m_0, c, d);
        out_file.close();

        // Generate a plot for the current model's distribution.
        distribution.GenerateSinglePlot(model_name, "data/" + model_name + "_momentum_distribution.txt", "plots/" + model_name + "_distribution.png");
    }

    // Generate a combined plot for all models.
    distribution.GenerateCombinedPlot(model_params["models"], "plots/combined_distribution.png");

    return 0;
}
