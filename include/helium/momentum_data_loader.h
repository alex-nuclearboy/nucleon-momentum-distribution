#ifndef HELIUM_MOMENTUM_DATA_LOADER_H
#define HELIUM_MOMENTUM_DATA_LOADER_H

#include <vector>
#include <string>

/**
 * @class MomentumDataLoader
 * @brief Class for loading momentum distribution data from text files.
 * 
 * Class for loading and processing momentum distribution data from text files, 
 * specifically for analyzing N* resonance within a ^3He nucleus. It supports 
 * converting momentum units from fm^-1 to GeV/c and normalizing probability densities.
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
     * @brief Loads data from a specified input file path, processes it by 
     *        converting momentum units from fm^-1 to GeV/c and normalizing 
     *        the probability densities, then saves the processed data to an output file.
     * 
     * @param input_file_path Path to the input file containing raw data.
     * @param output_file_path Path where processed data should be saved.
     * @param is_momentum_in_fm Flag indicating if the momentum values are in fm^-1.
     * @param is_prob_normalized Flag indicating if the probability values are already normalized.
     */
    void LoadAndProcessData(
        const std::string& input_file_path,
        const std::string& output_file_path,
        bool is_momentum_in_fm,
        bool is_prob_normalized);

    /**
     * @brief Loads data from a specified file path, parsing each line as 
     *        a pair of momentum and probability density values.
     * 
     * @param file_path The path to the text file containing the data.
     * @return A vector of <momentum, probability density> pairs.
     */
    std::vector<std::pair<float, float>> LoadData(const std::string& file_path);

private:
    /**
     * @brief Parses and processes a single line of input data, converting 
     * momentum units from fm^-1 to GeV/c and normalizing probability densities.
     * 
     * @param line A string representing a line of text from the data file.
     * @param is_momentum_in_fm Flag indicating if the momentum values are in fm^-1.
     * @param is_prob_normalized Flag indicating if the probability values are already normalized.
     * @return A pair containing the momentum (in GeV/c) and its normalized probability density.
     */
    
    std::pair<float, float> ParseAndProcessLine(
        const std::string& line, bool is_momentum_in_fm, bool is_prob_normalized);

    /**
     * @brief Parses a single line of text to extract momentum and probability density values.
     * 
     * @param line A string representing a line of text from the data file.
     * @return A pair representing momentum (GeV/c) and probability density. 
     */
    std::pair<float, float> ParseLine(const std::string& line);
    
};

#endif // HELIUM_MOMENTUM_DATA_LOADER_H
