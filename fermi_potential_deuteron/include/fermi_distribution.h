// fermi_distribution.h
#ifndef FERMI_DISTRIBUTION_H
#define FERMI_DISTRIBUTION_H

#include <fstream>
#include <vector>
#include <string>
#include "json.hpp"


class FermiDistributionCalculator {
public:
    FermiDistributionCalculator();
    void normalizeCoefficients(std::vector<double>& c, std::vector<double>& d, std::vector<double>& m2);    
    void calculate(std::ofstream& out_file, double alpha, double m_0, std::vector<double>& c, std::vector<double>& d);
    void generate_plot(const std::string& model_name, const std::string& data_file, const std::string& plot_file);
    void generate_combined_plot(const nlohmann::json& models, const std::string& combined_plot_file);

private:
    double alpha;
    std::vector<double> coefficients;
};

#endif // FERMI_DISTRIBUTION_H
