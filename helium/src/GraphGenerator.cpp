#include "GraphGenerator.h"
#include <TCanvas.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TLegend.h>
#include <iostream>

void GraphGenerator::generateCombinedGraph(const std::vector<std::pair<std::vector<float>, std::vector<float>>>& dataSets, const std::string& outputFilePath) {
    auto* canvas = new TCanvas("canvas", "Momentum Distribution", 800, 600);
    TLegend legend(0.7, 0.7, 0.9, 0.9);

    for (size_t i = 0; i < dataSets.size(); ++i) {
        TGraph* graph = new TGraph(dataSets[i].first.size(), dataSets[i].first.data(), dataSets[i].second.data());
        

        // Customize each graph's appearance as needed
        graph->SetLineColor(i + 1); // Change line color for each graph
        graph->GetXaxis()->SetRangeUser(0., 0.4);
        graph->Draw(i == 0 ? "AL" : "L"); // Draw the first graph with axis, subsequent graphs on top
        
        legend.AddEntry(graph, ("DataSet " + std::to_string(i)).c_str(), "l");
    }

    legend.Draw();
    canvas->SaveAs(outputFilePath.c_str());

    delete canvas; // Clean up to prevent memory leaks
}
