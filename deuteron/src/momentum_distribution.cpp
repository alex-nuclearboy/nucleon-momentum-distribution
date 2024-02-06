#include "../include/momentum_distribution.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include "TGraph.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TMultiGraph.h"

DistributionCalculator::DistributionCalculator() {}

void DistributionCalculator::NormalizeCoefficients(std::vector<double>& c, std::vector<double>& d, std::vector<double>& m2) 
{
    int n = c.size();

    // Calculate the last 'c' coefficient
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
    
    // Loop to calculate the last three 'd' coefficients
    for (int i = 0; i < 3; ++i) {
        // Normalize the current d coefficient
        d[n2] = -m2[n1] * m2[n0] * sum1 + (m2[n1] + m2[n0]) * sum2 - sum3;
        d[n2] *= m2[n2] / ((m2[n0] - m2[n2]) * (m2[n1] - m2[n2]));
        
        // Cycle the indices for the next iteration
        std::swap(n0, n1);
        std::swap(n1, n2);
    }
}

void DistributionCalculator::CalculateDistribution(std::ofstream& out_file, double alpha, double m_0, std::vector<double>& c, std::vector<double>& d) 
{
    const double dp = max_momentum / steps; // Increment in momentum per step
    double p[steps + 1], r[steps + 1], f_p[steps + 1]; // Arrays for momentum, reduced momentum, and momentum distribution
    double norm = 0; // Normalization constant
    
    int n = c.size();

    std::vector<double> m(n), m2(n);
        for (int i = 0; i < n; i++) {
            m[i] = alpha + i * m_0;            
            m2[i] = m[i] * m[i];
        }

    NormalizeCoefficients(c, d, m2);

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
    
    std::cout << "Momentum distribution calculation completed and saved to file." << std::endl;

}

void DistributionCalculator::GenerateSinglePlot(const std::string& model_name, const std::string& data_file, const std::string& plot_file) 
{
    std::ifstream in_file(data_file);
    if (!in_file.is_open()) {
        std::cerr << "Error: Failed to open the data file for reading: " << data_file << std::endl;
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
    TGraph* graph = new TGraph(momentum.size(), &momentum[0], &density[0]);
    graph->SetTitle(("Nucleon Momentum Distribution (" + model_name + " potential);Momentum (GeV/c);Probability Density").c_str());
    graph->SetMarkerStyle(20);
    graph->SetMarkerSize(0.7);
    graph->SetDrawOption("AP");
    
    // Create a TCanvas and draw the TGraph
    TCanvas* canvas = new TCanvas("c1", model_name.c_str(), 800, 600);
    graph->Draw("APL");
    
    // Save the plot
    canvas->SaveAs(plot_file.c_str());
    delete canvas; // Clean up
}

void DistributionCalculator::GenerateCombinedPlot(const nlohmann::json& models, const std::string& combined_plot_file) 
{
    TMultiGraph *mg = new TMultiGraph();
    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);

    for (const auto& model : models) {
        std::string model_name = model["name"];
        std::string data_file = "data/" + model_name + "_momentum_distribution.txt";

        std::ifstream in_file(data_file);
        if (!in_file.is_open()) {
            std::cerr << "Error: Failed to open the data file for reading: " << data_file << std::endl;
            continue; // Skip this model if the file can't be opened
        }

        std::vector<double> momentum;
        std::vector<double> density;
        double p, d;
        while (in_file >> p >> d) {
            momentum.push_back(p);
            density.push_back(d);
        }
        in_file.close();

        TGraph* graph = new TGraph(momentum.size(), momentum.data(), density.data());
        graph->SetTitle(model_name.c_str());
        graph->SetLineColor(1 + &model - &models[0]); // Different marker for each model
        //graph->SetMarkerStyle(1 + &model - &models[0]); // Different marker for each model
        mg->Add(graph);
        legend->AddEntry(graph, (model_name + " potential").c_str(), "lp");
    }

    TCanvas *canvas = new TCanvas("c2", "Combined Fermi Momentum Distribution", 800, 600);
    mg->Draw("ALP");
    mg->SetTitle("Fermi Momentum Distribution;Momentum (GeV/c);Probability Density");
    legend->Draw();

    canvas->SaveAs(combined_plot_file.c_str());
    delete canvas; // Clean up
}
