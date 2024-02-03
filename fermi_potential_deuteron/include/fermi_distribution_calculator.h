// fermi_distribution_calculator.h
#ifndef FERMI_DISTRIBUTION_CALCULATOR_H
#define FERMI_DISTRIBUTION_CALCULATOR_H

#include <fstream>
#include <vector>

class FermiDistributionCalculator {
public:
    FermiDistributionCalculator();
    void normalizeCoefficients(std::vector<double>& c, std::vector<double>& d, std::vector<double>& m2);    
    void calculate(std::ofstream& out_file, double alpha, std::vector<double>& c, std::vector<double>& d);
    void generate_plot();

private:
    double alpha;
    std::vector<double> coefficients;    
};

#endif // FERMI_DISTRIBUTION_CALCULATOR_H
