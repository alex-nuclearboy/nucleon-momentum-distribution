#include "include/deuteron/momentum_distribution.h"
#include "include/deuteron/plot_generator_deuteron.h"
#include "include/deuteron/json.hpp"
#include "include/helium/momentum_data_loader.h"
#include "include/helium/plot_generator_helium.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using json = nlohmann::json;

int main() {

    #ifdef DEUTERON
    // Load model parameters from the JSON file
    std::ifstream json_file("src/deuteron/models_config.json");
    if (!json_file.is_open()) {
        std::cerr << "Error: Failed to open JSON file for reading." << std::endl;
        return -1;
    }
    json model_params;
    json_file >> model_params;
    json_file.close();

    MomentumDistributionCalculator calculator;
    PlotGeneratorDeuteron generator_d;
    

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
        calculator.CalculateDistribution(out_file, alpha, m_0, c, d);
        out_file.close();

        // Generate a plot for the current model's distribution.
        generator_d.GenerateSinglePlot(model_name, "data/" + model_name + "_momentum_distribution.txt", "plots/" + model_name + "_distribution.png");
    }

    // Generate a combined plot for all models.
    generator_d.GenerateCombinedPlot(model_params["models"], "plots/combined_distribution_deuteron.png");

    #endif // DEUTERON

    #ifdef HELIUM

    // Paths to data files
    std::vector<std::string> file_paths = {               
        "input/mom_distr_resonance_3he_e33.txt",
        "input/mom_distr_resonance_3he_e53.txt",
        "input/mom_distr_resonance_3he_e74.txt",
        "input/mom_distr_nucleon_3he.txt",
        "input/mom_distr_nucleon_3he_nogga.txt", 
    };

    std::vector<std::string> output_file_paths = {
        "data/mom_distr_resonance_3he_e33_converted.txt",
        "data/mom_distr_resonance_3he_e53_converted.txt",
        "data/mom_distr_resonance_3he_e74_converted.txt",
        "data/mom_distr_nucleon_3he_converted.txt",
        "data/mom_distr_nucleon_3he_nogga_converted.txt"
    };

    // Визначення, чи вимірювання імпульсів у fm^-1 і чи нормалізовані ймовірності
    std::vector<bool> is_momentum_in_fm = {true, false, true, true, false};
    std::vector<bool> is_prob_normalized = {true, false, true, true, false};

    // Instantiate the loader and generator
    MomentumDataLoader loader;
    PlotGeneratorHelium generator_he;

    // Vector to hold all datasets
    std::vector<std::pair<std::vector<float>, std::vector<float>>> all_data_sets;

    // Використання циклу для обробки кожного файлу
    for (size_t i = 0; i < file_paths.size(); ++i) {
        loader.LoadAndProcessData(file_paths[i], output_file_paths[i], is_momentum_in_fm[i], is_prob_normalized[i]);
        std::cout << "Processed and saved: " << output_file_paths[i] << std::endl;

        // Завантаження оброблених даних для генерації графіку
        auto processed_data = loader.LoadData(output_file_paths[i]);
        
        std::vector<float> momenta, probabilities;
        for (const auto& dp : processed_data) {
            momenta.push_back(dp.first);
            probabilities.push_back(dp.second);
        }
        
        all_data_sets.push_back({momenta, probabilities});
    }

    std::string output_file_path = "plots/combined_momentum_distribution_helium.png";
    generator_he.GenerateCombinedPlot(all_data_sets, output_file_path);

    #endif // HELIUM

    return 0;
}
