#ifndef MOMENTUMDATALOADER_H
#define MOMENTUMDATALOADER_H

#include <vector>
#include <string>

class MomentumDataLoader {
public:
    MomentumDataLoader() = default;
    std::vector<std::pair<float, float>> loadData(const std::string& filePath);

private:
    std::pair<float, float> parseLine(const std::string& line);
};

#endif // MOMENTUMDATALOADER_H
