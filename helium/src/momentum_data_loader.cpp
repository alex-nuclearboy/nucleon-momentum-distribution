/**
 * @file momentum_data_loader.cpp
 * @author AK <alex.nuclearboy@gmail.com>
 * @brief Implementation for the MomentumDataLoader class.
 * 
 * This class is designed to load momentum distribution data from text files, 
 * specifically for N* resonance within a helium-3 nucleus. Each input file line 
 * should contain two floating-point numbers: N* momentum (in GeV/c) 
 * and its probability density. This class simplifies input data transformation 
 * into a graphical representation.
 * 
 * @version 1.1
 * @date 06 Feb 2024
 * @last_updated 07 Feb 2024
 * 
 * @license This code is licensed under the GNU General Public License version 3.0. * 
 */

#include "momentum_data_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<std::pair<float, float>> MomentumDataLoader::LoadData(const std::string& file_path) {
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

std::pair<float, float> MomentumDataLoader::ParseLine(const std::string& line) {
    std::istringstream iss(line);
    float momentum, probability;
    if (!(iss >> momentum >> probability)) {
        return {0.0f, 0.0f}; // Return zeros if parsing fails
    }
    return {momentum, probability};
}
