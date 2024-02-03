// fermi_distribution_calculator.cpp
#include "fermi_distribution_calculator.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include "TGraph.h"
#include "TCanvas.h"
#include "TAxis.h"

FermiDistributionCalculator::FermiDistributionCalculator() {}

void FermiDistributionCalculator::normalizeCoefficients(std::vector<double>& c, std::vector<double>& d, std::vector<double>& m2) {

    int n = c.size();

    for (int i = 0; i < n - 1; i++) {c[n - 1] -= c[i];}

    int n2 = n - 3;
    int n1 = n2 + 1;
    int n0 = n1 + 1;

    double sum1 = 0., sum2 = 0., sum3 = 0.;
    
    // Summation for the normalization of d coefficients
    for (int j = 0; j <= n - 3; ++j) {
        sum1 += d[j] / m2[j];
        sum2 += d[j];
        sum3 += d[j] * m2[j];
    }
    
    // Loop to calculate the last three coefficients
    for (int i = 0; i < 3; ++i) {
        // Normalize the current d coefficient
        d[n2] = -m2[n1] * m2[n0] * sum1 + (m2[n1] + m2[n0]) * sum2 - sum3;
        d[n2] *= m2[n2] / ((m2[n0] - m2[n2]) * (m2[n1] - m2[n2]));
        
        // Cycle the indices for the next iteration
        std::swap(n0, n1);
        std::swap(n1, n2);
    }
}

void FermiDistributionCalculator::calculate(std::ofstream& out_file, double alpha, std::vector<double>& c, std::vector<double>& d) {
    // Adapted to use params.alpha and params.coefficients in calculations
    const double sqrtpi2 = 0.7978845608; // Square root of 2/PI
    
    const double conversion = 0.197327;  // Conversion factor for momentum (GeV/c to fm^-1)
    const int steps = 400; // Number of steps from 0 to 0.4 GeV/c
    const double dp = 0.4 / steps; // Increment in momentum per step
    double p[401], r[401], f_p[401]; // Arrays for momentum, reduced momentum, and momentum distribution
    double norm = 0; // Normalization constant
    
    int n = c.size();

    std::vector<double> m(n), m2(n);
        for (int i = 0; i < n; i++) {
            m[i] = alpha + i;
            m2[i] = m[i] * m[i];
        }

    normalizeCoefficients(c, d, m2);

    for (int j = 0; j <= steps; ++j) {

        p[j] = j * dp; // Calculate momentum in GeV/c
        r[j] = p[j] / conversion; // Convert momentum to reduced momentum (GeV/c to fm^-1)

        
        // Calculation for the Paris potential
        double U = 0., W = 0.;
        for (int i = 0; i < n; i++) {
            U += c[i] / (r[j] * r[j] + m2[i]);
            W += d[i] / (r[j] * r[j] + m2[i]);
        }
        
        U *= sqrtpi2; // s wave contribution
        W *= sqrtpi2; // d wave contribution
        
        // Calculate momentum distribution and accumulate normalization
        f_p[j] = r[j] * r[j] * (U * U + W * W);
        norm += f_p[j];
    }
    
    // Normalize and output the momentum distribution
    for (int i = 0; i <= steps; i++) {
        f_p[i] /= norm;
        out_file << p[i] << "\t" << f_p[i] << std::endl;
    }
    
    std::cout << "Momentum distribution calculation completed and saved." << std::endl;

}

void FermiDistributionCalculator::generate_plot() {
    // Plotting implementation using ROOT as in the provided content
    // Load data from the file
    std::ifstream in_file("data/cdbonn_momentum_distribution.txt");
    if (!in_file.is_open()) {
        std::cerr << "Failed to open the data file for reading." << std::endl;
        return;
    }
    
    std::vector<double> momentum;
    std::vector<double> density;
    double p, d;
    
    while (in_file >> p >> d) {
        momentum.push_back(p);
        density.push_back(d);
    }
    in_file.close();
    
    // Prepare the TGraph
    int n_points = momentum.size();
    TGraph* graph = new TGraph(n_points, &momentum[0], &density[0]);
    graph->SetTitle("Fermi Momentum Distribution (Paris model);Momentum (GeV/c);Probability Density (normalized)");
    graph->SetMarkerStyle(20);
    graph->SetDrawOption("AP");
    
    // Create a TCanvas and draw the TGraph
    TCanvas* canvas = new TCanvas("c1", "Fermi Momentum Distribution", 800, 600);
    graph->Draw("APL");
    
    // Save the plot
    canvas->SaveAs("plots/distribution.root"); // For ROOT file
    canvas->SaveAs("plots/distribution.png");  // For PNG file
}
