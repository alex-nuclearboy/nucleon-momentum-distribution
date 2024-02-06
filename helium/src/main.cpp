#include "MomentumDataLoader.h"
#include "GraphGenerator.h"
#include <vector>
#include <string>
#include "TMath.h"

int main() {
    // Paths to data files
    std::vector<std::string> filePaths = {
        //"data/mom_distr_nucleon_3he_nogga.txt",        
        "data/mom_distr_resonance_3he_e33.txt",
        "data/mom_distr_resonance_3he_e53.txt",
        "data/mom_distr_resonance_3he_e74.txt",
        "data/mom_distr_nucleon_3he.txt"
    };

    // Instantiate the loader and generator
    MomentumDataLoader loader;
    GraphGenerator generator;

    // Vector to hold all datasets
    std::vector<std::pair<std::vector<float>, std::vector<float>>> allDataSets;

    for (const auto& path : filePaths) {
        auto data = loader.loadData(path); // Load data for each file

        std::vector<float> momentums;
        std::vector<float> probabilities;
        
        for (const auto& dp : data) { // Now 'data' is in the correct scope
            float correctedMomentum = dp.first * 0.1973; // Adjust momentum if necessary
            float correctedProbability = (dp.second / 0.1973) * 4 * TMath::Pi(); // Calculate probability density
            momentums.push_back(correctedMomentum);
            probabilities.push_back(correctedProbability);
        }

        allDataSets.push_back(std::make_pair(momentums, probabilities));
    }

    std::string outputFilePath = "plots/combinedMomentumDistribution.png";
    generator.generateCombinedGraph(allDataSets, outputFilePath);

    return 0;
}