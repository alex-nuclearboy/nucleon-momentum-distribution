/**
 * @file convert.cpp
 * @author AK <alex.nuclearboy@gmail.com>
 * @brief Momentum Conversion and Probability Normalization Tool
 * 
 * @details
 * This utility is designed to convert momentum values of the N* resonance 
 * within a bound N*-deuteron system in an excited ^3He nucleus for 
 * various binding energies. The tool also processes the momentum of a proton 
 * within the ^3He nucleus according to two different theoretical models.
 * 
 * Momentum values provided in the datasets can be in either fm^-1 or GeV/c. 
 * The program automatically converts momentum units from fm^-1 to GeV/c where 
 * necessary, ensuring that all data conforms to a single unit system. 
 * Additionally, the normalization of probability densities is adjusted 
 * to achieve consistent normalization to 1 across all datasets.
 *
 * @version 1.0
 * @date 2024-02-07
 * 
 * @remark This code is licensed under the GNU General Public License version 3.0 (GPLv3).
 * 
 * ## Usage
 * 
 * Compile with:
 * ```bash
 * g++ -o convert convert.cpp
 * ```
 * 
 * Run with:
 * ```bash
 * ./convert
 * ```
 * 
 * Ensure that the input files are in the correct format and accessible at the specified path.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip> // for std::setprecision

const double PI = 3.14159265358979323846;
const double FM_TO_GEV = 0.19732697; ///< Conversion factor from fm^-1 to GeV/c for momentum.

/**
 * @brief Converts momenta and normalizes probabilities for a given dataset.
 * 
 * @param input_file The path to the input file containing the dataset.
 * @param output_file The path for the output file where processed data will be saved.
 * @param is_momentum_in_fm A boolean flag indicating if the momentum values 
 *                          in the input file are in fm^-1 (true) or GeV/c (false).
 * @param is_prob_normalized A boolean flag indicating if the probability values 
 *                           in the input file are normalized.
 */
void ConvertAndNormalize(const std::string& input_file, 
                         const std::string& output_file, 
                         bool is_momentum_in_fm, bool is_prob_normalized) {
    std::ifstream fin(input_file);
    if (!fin) {
        std::cerr << "Error opening input file: " << input_file << std::endl;
        return;
    }
    
    std::ofstream fout(output_file);
    if (!fout) {
        std::cerr << "Error creating output file: " << output_file << std::endl;
        return;
    }
    
    std::string line;
    double momentum_convers_factor = is_momentum_in_fm ? FM_TO_GEV : 1.0;
    double probability_normaliz_factor = is_prob_normalized 
                                            ? (4.0 * PI) / FM_TO_GEV 
                                            : (1.0 * PI) / FM_TO_GEV;

    while (getline(fin, line)) {
        std::istringstream iss(line);
        double momentum, probability;
        iss >> momentum >> probability;

        // Convert momentum if necessary
        momentum *= momentum_convers_factor;

        // Normalize probability if necessary
        probability *= probability_normaliz_factor;

        // Write converted and normalized data to the output file        
        fout << std::fixed << std::setprecision(10) << momentum << "\t" 
             << std::setprecision(10) << probability << std::endl;
    }
}

int main() {    
    std::vector<std::string> input_files = {
        "mom_distr_resonance_3he_e33.txt", 
        "mom_distr_resonance_3he_e53.txt", 
        "mom_distr_resonance_3he_e74.txt", 
        "mom_distr_nucleon_3he.txt", 
        "mom_distr_nucleon_3he_nogga.txt"
    };
    std::vector<std::string> output_files = {
        "mom_distr_resonance_3he_e33_converted.txt", 
        "mom_distr_resonance_3he_e53_converted.txt", 
        "mom_distr_resonance_3he_e74_converted.txt", 
        "mom_distr_nucleon_3he_converted.txt", 
        "mom_distr_nucleon_3he_nogga_converted.txt"
    };
    std::vector<bool> is_momentum_in_fm = {true, false, true, true, false};
    std::vector<bool> is_prob_normalized = {true, false, true, true, false};

    for (size_t i = 0; i < input_files.size(); ++i) {
        ConvertAndNormalize(input_files[i], output_files[i], 
                            is_momentum_in_fm[i], is_prob_normalized[i]);
        std::cout << "Successfully processed file: " << input_files[i] << std::endl;
    }

    return 0;
}
