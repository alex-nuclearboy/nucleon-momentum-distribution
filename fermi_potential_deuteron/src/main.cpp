// main.cpp
#include "fermi_distribution_calculator.h"
#include <iostream>
#include <fstream>
#include <vector>

int main() {

    FermiDistributionCalculator calculator;

    std::ofstream out_file_paris("data/paris_momentum_distribution.txt");
    if (!out_file_paris.is_open()) {
        std::cerr << "Failed to open output file for writing." << std::endl;
        return -1;
    }

    std::ofstream out_file_cdbonn("data/cdbonn_momentum_distribution.txt");
    if (!out_file_paris.is_open()) {
        std::cerr << "Failed to open output file for writing." << std::endl;
        return -1;
    }

    const double alpha_paris = 0.23162461; // Parameter alpha for the Paris model
    const double alpha_cdbonn = 0.2315380; // Parameter alpha for the CDBonn model

    std::vector<double> c_p(13), d_p(13);
    std::vector<double> c_c(11), d_c(11);

    // Initialize c coefficients
    c_p = {0.88688076e0, -0.34717093e0, -0.30502380e1, 0.56207766e2,
          -0.74957334e3, 0.53365279e4, -0.22706863e5, 0.60434469e5,
          -0.10292058e6, 0.11223357e6, -0.75925226e5, 0.29059715e5, 0.};
            
    // Initialize d coefficients
    d_p = {0.23135193e-1, -0.85604572e0, 0.56068193e1, -0.69462922e2,
           0.41631118e3, -0.12546621e4, 0.12387830e4, 0.33739172e4,
          -0.13041151e5, 0.19512524e5, 0., 0., 0.};

    // Initialize c coefficients
    c_c = {0.88472985e0, -0.26408759e0, -0.44114404e-1, -0.14397512e2,
          0.85591256e2,  -0.31876761e3, 0.70336701e3, -0.90049586e3,
          0.66145441e3,  -0.25958894e3, 0.};
            
    // Initialize d coefficients
    d_c = {0.22623762e-1, -0.50471056e0, 0.56278897e0, -0.16079764e2,
           0.11126803e3,  -0.44667490e3, 0.10985907e4,  -0.16114995e4,
           0., 0., 0.};

    calculator.calculate(out_file_paris, alpha_paris, c_p, d_p);
    out_file_paris.close();

    calculator.calculate(out_file_cdbonn, alpha_cdbonn, c_c, d_c);
    out_file_paris.close();

    calculator.generate_plot();

    return 0;
}
