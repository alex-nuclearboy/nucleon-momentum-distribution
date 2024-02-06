#include "MomentumDataLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<std::pair<float, float>> MomentumDataLoader::loadData(const std::string& filePath) {
    std::vector<std::pair<float, float>> data;
    std::ifstream file(filePath);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filePath << std::endl;
        return data; // Return empty data if file can't be opened
    }

    while (std::getline(file, line)) {
        auto [momentum, probability] = parseLine(line);
        data.push_back({momentum, probability});
    }

    file.close();
    return data;
}

std::pair<float, float> MomentumDataLoader::parseLine(const std::string& line) {
    std::istringstream iss(line);
    float momentum, probability;
    if (!(iss >> momentum >> probability)) {
        return {0.0f, 0.0f}; // Return zeros if parsing fails
    }
    return {momentum, probability};
}
