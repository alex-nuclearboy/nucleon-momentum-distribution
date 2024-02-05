/**
 * File:         main.cpp
 * Author:       Aleksander Khreptak <aleksander.khreptak@alumni.uj.edu.pl>
 * Created:      02 Feb 2024
 * Last updated: 05 Feb 2024
 * 
 * Description:
 * Main program entry point.
 * Loads model parameters from a JSON configuration file,
 * calculates the Fermi nucleon momentum distribution for each model,
 * and generates output files and plots for each.
 */

#include "fermi_distribution.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "json.hpp"

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

    FermiDistributionCalculator calculator;

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
        calculator.calculate(out_file, alpha, m_0, c, d);
        out_file.close();

        // Generate a plot for the current model's distribution.
        calculator.generate_plot(model_name, "data/" + model_name + "_momentum_distribution.txt", "plots/" + model_name + "_distribution.png");
    }

    // Generate a combined plot for all models.
    calculator.generate_combined_plot(model_params["models"], "plots/combined_distribution.png");

    return 0;
}
