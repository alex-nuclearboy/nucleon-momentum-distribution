// main.cpp
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
        std::cerr << "Failed to open JSON file for reading." << std::endl;
        return -1;
    }
    json model_params;
    json_file >> model_params;
    json_file.close();

    FermiDistributionCalculator calculator;

    for (const auto& model : model_params["models"]) {
        std::string model_name = model["name"];
        double alpha = model["alpha"];
        double m_0 = model["m_0"];
        std::vector<double> c = model["parameters"]["c"];
        std::vector<double> d = model["parameters"]["d"];

        std::ofstream out_file("data/" + model_name + "_momentum_distribution.txt");
        if (!out_file.is_open()) {
            std::cerr << "Failed to open output file for writing for " << model_name << " model." << std::endl;
            continue; // Skip this model if the file can't be opened
        }
        
        calculator.calculate(out_file, alpha, m_0, c, d);
        out_file.close();

        calculator.generate_plot(model_name, "data/" + model_name + "_momentum_distribution.txt", "plots/" + model_name + "_distribution.png");
    }

    calculator.generate_combined_plot(model_params["models"], "plots/combined_distribution.png");

    return 0;
}
