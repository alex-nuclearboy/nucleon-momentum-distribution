/**
 * @file momentum_data_loader.cpp
 * @author AK <alex.nuclearboy@gmail.com>
 * @brief Implementation of the MomentumDataLoader class for loading, processing, 
 *        and plotting N* resonance momentum distribution data.
 * 
 * @details
 * The MomentumDataLoader class is designed for investigating momentum 
 * distributions of the N*(1535) resonance within the context of the excited ^3He nucleus, 
 * interpreted as a system of the N* and a deuteron. This class simplifies the 
 * tasks of loading, processing, and visualizing data across different binding 
 * energies, specifically for E_{N*-d} = -0.33 MeV, -0.53 MeV, and -0.74 MeV. 
 * Additionally, it processes proton momentum data within the ^3He nucleus 
 * based on two theoretical models.
 * 
 * The class streamlines the analysis workflow by:
 * - Loading data from text files for varied binding energies.
 * - Converting momentum from fm^-1 to GeV/c, ensuring dataset consistency.
 * - Normalizing probability densities for uniform comparison and analysis.
 * - Storing processed data in output files for further analysis.
 * - Creating a combined plot for all datasets, illustrating the momentum 
 *   distributions of both the N* resonance and the proton within the ^3He nucleus.
 * 
 * @version 2.0
 * @date 2024-02-06
 * @note Last updated on 2024-02-08
 * 
 * @remark Licensed under the GNU General Public License version 3.0 (GPLv3). 
 */

#include "../include/helium/momentum_data_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip> // for std::setprecision

const double PI = 3.14159265358979323846;
const double FM_TO_GEV = 0.19732697; // Conversion factor from fm^-1 to GeV/c

/**
 * Loads and processes data from a specified input file, converting momentum units and 
 * normalizing probability densities, and saves the processed data to an output file.
 */
void MomentumDataLoader::LoadAndProcessData(
    const std::string& input_file_path,
    const std::string& output_file_path,
    bool is_momentum_in_fm,
    bool is_prob_normalized) 
{
    std::ifstream input_file(input_file_path);
    std::ofstream output_file(output_file_path, std::ios::out);

    if (!input_file.is_open()) {
        std::cerr << "Error: Could not open input file: " << input_file_path 
                  << std::endl;
        return;
    }
    if (!output_file.is_open()) {
        std::cerr << "Error: Could not open output file: " << output_file_path 
                  << std::endl;
        return;
    }

    std::string line;
    while (std::getline(input_file, line)) {
        auto [momentum, probability] = ParseAndProcessLine(
            line, is_momentum_in_fm, is_prob_normalized);
        output_file << std::fixed << std::setprecision(10) << momentum << "\t" 
                    << std::setprecision(10) << probability << std::endl;
    }
}

/**
 * Parses and processes a single line of input data, converting momentum units 
 * from fm^-1 to GeV/c and normalizing probability densities if specified.
 */
std::pair<float, float> MomentumDataLoader::ParseAndProcessLine(
    const std::string& line, bool is_momentum_in_fm, bool is_prob_normalized) 
{
    std::istringstream iss(line);
    float momentum, probability;
    if (!(iss >> momentum >> probability)) {
        return {0.0f, 0.0f}; // Return zeros if parsing fails
    }

    double momentum_convers_factor = is_momentum_in_fm ? FM_TO_GEV : 1.0;
    double prob_normaliz_factor = is_prob_normalized 
                                            ? (4.0 * PI) / FM_TO_GEV 
                                            : (1.0 * PI) / FM_TO_GEV;
    
    momentum *= momentum_convers_factor;    // Convert momentum if necessary
    probability *= prob_normaliz_factor;    // Normalize probability

    return {momentum, probability};
    
}

/**
 * Loads data from a specified file path, parsing each line as a pair 
 * of momentum and probability density values.
 */
std::vector<std::pair<float, float>> MomentumDataLoader::LoadData(
    const std::string& file_path) 
{
    std::vector<std::pair<float, float>> data;
    std::ifstream file(file_path);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Could not open file: " << file_path << std::endl;
        return data; // Return empty data if file can't be opened
    }

    while (std::getline(file, line)) {
        auto [momentum, probability] = ParseLine(line);
        data.push_back({momentum, probability});
    }

    file.close();
    return data;
}

/**
 * Parses a single line of text to extract momentum and probability density values.
 */
std::pair<float, float> MomentumDataLoader::ParseLine(const std::string& line) 
{
    std::istringstream iss(line);
    float momentum, probability;
    if (!(iss >> momentum >> probability)) {
        return {0.0f, 0.0f}; // Return zeros if parsing fails
    }
    return {momentum, probability};
}
