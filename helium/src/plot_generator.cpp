/**
 * @file plot_generator.cpp
 * @author AK <alex.nuclearboy@gmail.com> * 
 * @brief Implements the PlotGenerator class for visualizing momentum distributions.
 *
 * This class generates graphical plots to represent the distribution 
 * of relative momentum for the N* resonance within the N*-deuteron system 
 * embedded in the helium-3 nucleus across various binding energies.
 *  
 * @version 1.1
 * @date 06 Feb 2024
 * @last_updated 07 Feb 2024
 * 
 * @license This code is licensed under the GNU General Public License version 3.0.
 */

#include "plot_generator.h"
#include <iostream>
#include <TCanvas.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TLegend.h>

void PlotGenerator::GenerateCombinedPlot(const std::vector<std::pair<std::vector<float>, std::vector<float>>>& data_sets, const std::string& output_file_path) {
    auto* canvas = new TCanvas("canvas", "Momentum Distribution", 800, 600);
    TLegend legend(0.7, 0.7, 0.9, 0.9);

    for (size_t i = 0; i < data_sets.size(); ++i) {
        TGraph* graph = new TGraph(data_sets[i].first.size(), data_sets[i].first.data(), data_sets[i].second.data());

        // Customize each graph's appearance
        graph->SetLineColor(i + 1); // Change line color for each graph
        graph->GetXaxis()->SetRangeUser(0., 0.4);
        graph->Draw(i == 0 ? "AL" : "L"); // Draw the first graph with axis, subsequent graphs on top
        
        legend.AddEntry(graph, ("DataSet " + std::to_string(i)).c_str(), "l");
    }

    legend.Draw();
    canvas->SaveAs(output_file_path.c_str());

    delete canvas; // Clean up
}
