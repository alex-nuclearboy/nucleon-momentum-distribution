#ifndef GRAPHGENERATOR_H
#define GRAPHGENERATOR_H

#include <vector>
#include <string>
#include <utility> // For std::pair

class GraphGenerator {
public:
    GraphGenerator() = default;
    void generateCombinedGraph(const std::vector<std::pair<std::vector<float>, std::vector<float>>>& dataSets, const std::string& outputFilePath);

private:
    void customizeGraphAppearance(); // Implement as needed for graph customization
};

#endif // GRAPHGENERATOR_H
