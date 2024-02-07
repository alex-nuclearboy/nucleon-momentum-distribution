/**
 * @file plot_generator.cpp
 * @author AK <alex.nuclearboy@gmail.com>
 * @brief Implementation for the PlotGenerator class.
 * 
 * @details
 * This class is responsible for generating graphical plots to visually 
 * represent the momentum distribution of nucleons inside a deuteron 
 * for different nucleon-nucleon potentials.
 *  
 * @version 1.0
 * @date 2024-02-07
 * 
 * @remark This code is licensed under the GNU General Public License version 3.0 (GPLv3).
 */

#include "../include/plot_generator.h"
#include <vector>
#include <fstream>
#include <iostream>
#include "TGraph.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TMultiGraph.h"

PlotGenerator::PlotGenerator() {}

void PlotGenerator::GenerateSinglePlot(const std::string& model_name, const std::string& data_file, const std::string& plot_file) 
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

void PlotGenerator::GenerateCombinedPlot(const nlohmann::json& models, const std::string& combined_plot_file) 
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
        graph->SetLineWidth(2);
        graph->SetLineStyle(1 + &model - &models[0]); // Different line style for each model
        graph->SetLineColor(1 + &model - &models[0]); // Different line color for each model
        mg->Add(graph);
        legend->AddEntry(graph, (model_name + " potential").c_str(), "lp");
    }

    TCanvas *canvas = new TCanvas("c2", "Combined Fermi Momentum Distribution", 800, 600);
    mg->GetXaxis()->SetRangeUser(0., 0.4);
    mg->GetYaxis()->SetRangeUser(0., 0.012);
    mg->Draw("ALP");
    mg->SetTitle("Fermi Momentum Distribution;Momentum (GeV/c);Probability Density (c/GeV)");
    legend->Draw();

    canvas->SaveAs(combined_plot_file.c_str());
    delete canvas; // Clean up
}
