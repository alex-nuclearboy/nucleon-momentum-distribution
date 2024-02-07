/**
 * @file main.cpp
 * @author AK <alex.nuclearboy@gmail.com>
 * @brief Main program entry point for loading and plotting N* resonance 
 *        momentum distribution data.
 * 
 * @details
 * This program is designed as the central utility for visualizing the momentum 
 * distribution of N* resonance within an N*-deuteron system in the ^3He nucleus,
 * as well as the momentum distribution of the proton within the ^3He nucleus.
 * It reads predefined data files representing different conditions, extracts 
 * momentum and probability data for both the N* resonance and the proton, and 
 * generates a combined plot to illustrate the momentum distributions across 
 * these datasets.
 * The process involves:
 * - Loading data from specified file paths in a predefined list.
 * - Extracting momentum and probability values from these files.
 * - Generating a combined plot that visually represents these distributions.
 * 
 * @version 1.1
 * @date 2024-02-06
 * @note Last updated on 2024-02-07
 * 
 * @remark This code is licensed under the GNU General Public License version 3.0 (GPLv3).
 * 
 * Ensure the files with prepared datasets are present in the specified 
 * directory paths before running the program. The generated plot will be saved 
 * to the specified output file path, providing a visual representation
 * of the momentum distributions across the datasets.
 */

#include "momentum_data_loader.h"
#include "plot_generator.h"
#include <vector>
#include <string>

int main() {
    // Paths to data files
    std::vector<std::string> file_paths = {               
        "data/mom_distr_resonance_3he_e33_converted.txt",
        "data/mom_distr_resonance_3he_e53_converted.txt",
        "data/mom_distr_resonance_3he_e74_converted.txt",
        "data/mom_distr_nucleon_3he_converted.txt",
        "data/mom_distr_nucleon_3he_nogga_converted.txt", 
    };

    // Instantiate the loader and generator
    MomentumDataLoader loader;
    PlotGenerator generator;

    // Vector to hold all datasets
    std::vector<std::pair<std::vector<float>, std::vector<float>>> all_data_sets;

    for (const auto& path : file_paths) {
        auto data = loader.LoadData(path); // Load data for each file

        std::vector<float> momenta;
        std::vector<float> probabilities;
        
        for (const auto& dp : data) {            
            momenta.push_back(dp.first);
            probabilities.push_back(dp.second);
        }

        all_data_sets.push_back(std::make_pair(momenta, probabilities));
    }

    std::string output_file_path = "plots/combined_momentum_distribution.png";
    generator.GenerateCombinedPlot(all_data_sets, output_file_path);

    return 0;
}
