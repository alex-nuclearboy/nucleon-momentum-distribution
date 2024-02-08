/**
 * @file plot_generator_deuteron.cpp
 * @author AK <alex.nuclearboy@gmail.com>
 * @brief Implementation of the PlotGeneratorDeuteron class for visualization of momentum distributions.
 * 
 * @details
 * The PlotGeneratorDeuteron class generates graphical representations to visualize
 * the momentum distribution of nucleons within a deuteron, using various
 * nucleon-nucleon potential models. This class supports both the creation of individual
 * plots for specific models and combined plots that merge the momentum distributions
 * from multiple models.
 *  
 * @version 2.0
 * @date 2024-02-07
 * @note Last updated on 2024-02-08
 * 
 * @remark Licensed under the GNU General Public License version 3.0 (GPLv3).
 */
#include "../include/deuteron/plot_generator_deuteron.h"
#include <vector>
#include <fstream>
#include <iostream>
#include "TGraph.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TMultiGraph.h"

PlotGeneratorDeuteron::PlotGeneratorDeuteron() {}

/**
 * Generates a plot for the momentum distribution of a single potential model.
 * This function reads momentum and probability density data from a file, creating a plot
 * that visualizes the nucleon momentum distribution under a specified potential.
 */
void PlotGeneratorDeuteron::GenerateSinglePlot(
    const std::string& model_name, const std::string& data_file, 
    const std::string& plot_file)
{
    std::ifstream in_file(data_file);
    if (!in_file.is_open()) {
        std::cerr << "Error: Failed to open the data file for reading: " 
                  << data_file << std::endl;
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
    std::string title = "Nucleon Momentum Distribution (" + model_name +
                        " potential);Momentum (GeV/c);Probability Density";
    graph->SetTitle(title.c_str());
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

/**
 * Combines momentum distribution data from multiple potential models into a single
 * plot. This function facilitates the visual comparison of nucleon momentum 
 * distributions calculated using different nucleon-nucleon potentials.
 */
void PlotGeneratorDeuteron::GenerateCombinedPlot(
    const nlohmann::json& models, const std::string& combined_plot_file)
{
    TMultiGraph *mg = new TMultiGraph();
    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);

    for (const auto& model : models) {
        std::string model_name = model["name"];
        std::string data_file = "data/" + model_name 
                              + "_momentum_distribution.txt";

        std::ifstream in_file(data_file);
        if (!in_file.is_open()) {
            std::cerr << "Error: Failed to open the data file for reading: " 
                      << data_file << std::endl;
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

        TGraph* graph = new TGraph(
            momentum.size(), momentum.data(), density.data()
        );
        graph->SetTitle(model_name.c_str());        
        graph->SetLineWidth(2);
        graph->SetLineStyle(1 + &model - &models[0]); // Different line style for each model
        graph->SetLineColor(1 + &model - &models[0]); // Different line color for each model
        mg->Add(graph);
        legend->AddEntry(graph, (model_name + " potential").c_str(), "lp");
    }

    TCanvas *canvas = new TCanvas(
        "c2", "Combined Fermi Momentum Distribution", 800, 600
    );
    mg->GetXaxis()->SetRangeUser(0., 0.4);
    mg->GetYaxis()->SetRangeUser(0., 0.012);
    mg->Draw("ALP");
    std::string title = "Fermi Momentum Distribution;Momentum (GeV/c);"
                        "Probability Density (c/GeV)";
    mg->SetTitle(title.c_str());
    legend->Draw();

    canvas->SaveAs(combined_plot_file.c_str());
    delete canvas; // Clean up
}
