#ifndef HELIUM_MOMENTUM_DATA_LOADER_H
#define HELIUM_MOMENTUM_DATA_LOADER_H

#include <vector>
#include <string>

/**
 * @class MomentumDataLoader
 * @brief Class for loading momentum distribution data from text files. 
 */

class MomentumDataLoader {
public:
    /**
     * @brief Constructor for a new MomentumDataLoader object
     * 
     * Initializes a new instance of the MomentumDataLoader class.
     */
    MomentumDataLoader() = default;

    /**
     * @brief Load data from a specified file path.
     * 
     * Reads a text file from the given file path, parsing each line as a
     * pair of momentum and probability density values.
     * 
     * @param file_path The path to the text file containing the data.
     * @return A vector of <momentum, probability density> pairs.
     */
    std::vector<std::pair<float, float>> LoadData(const std::string& file_path);

private:
    /**
     * @brief Parse a line of text into momentum and probability density values.
     * 
     * Takes a single line of text and extracts a pair of floating-point numbers:
     * the momentum and its corresponding probability density.
     * 
     * @param line A string representing a line of text from the data file.
     * @return A pair representing momentum (GeV/c) and probability density. 
     */
    std::pair<float, float> ParseLine(const std::string& line);
};

#endif // HELIUM_MOMENTUM_DATA_LOADER_H
