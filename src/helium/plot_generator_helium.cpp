/**
 * @file plot_generator.cpp
 * @author AK <alex.nuclearboy@gmail.com> * 
 * @brief Implementation of the PlotGeneratorHelium class for visualizing momentum distributions.
 * 
 * @details
 * This class facilitates the visualization of momentum distributions for N* resonance
 * within the ^3He nucleus, considering this nucleus as the bound N*-deuteron system. 
 * Additionally, it includes the visualization of proton momentum distribution 
 * within the ^3He nucleus. The class offers functionalities to create combined 
 * plot that visually represent these distributions for various binding energies.
 *  
 * @version 2.0
 * @date 2024-02-06
 * @note Last updated on 2024-02-08
 * 
 * @remark Licensed under the GNU General Public License version 3.0 (GPLv3).
 */

#include "../include/helium/plot_generator_helium.h"
#include <iostream>
#include <TCanvas.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TLegend.h>

/**
 * Generates a plot that combines multiple datasets to depict both the N* resonance 
 * and proton momentum distributions within the helium nucleus.
 */
void PlotGeneratorHelium::GenerateCombinedPlot(
    const std::vector<std::pair<std::vector<float>, 
    std::vector<float>>>& data_sets, 
    const std::string& output_file_path) 
{
    auto* canvas = new TCanvas("canvas", "Momentum Distribution", 800, 600);
    TLegend legend(0.7, 0.7, 0.9, 0.9);

    for (size_t i = 0; i < data_sets.size(); ++i) {
        TGraph* graph = new TGraph(data_sets[i].first.size(), 
                                   data_sets[i].first.data(), 
                                   data_sets[i].second.data()
        );

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
