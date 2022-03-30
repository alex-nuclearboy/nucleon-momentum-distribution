/***********************************************
* Software developement for WASA-at-COSY
* (c) 2005-2021 The WASA-at-COSY Collaboration
* Aleksander K.                 2018-09
* This software is distributed under the terms
  of the GNU General Public Licence v3.0
*
* Modified 2021-03
***********************************************/

#include <TH1F.h>
#include <TH2F.h>
#include <TH1D.h>
#include <TF1.h>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TClonesArray.h>
#include <TPaveLabel.h>
#include <TFrame.h>
#include <TSystem.h>
#include <TNtuple.h>
#include <TPaveText.h>
#include <TInterpreter.h>
#include <TStyle.h>
#include <TAxis.h>
#include <Riostream.h>
#include <TLegend.h>
#include <TLine.h>
#include <TROOT.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <stdio.h>

void drawMacro() {

  TGraph *MomentumDistribition[8];
  FILE *MomDistFile[8];

  Float_t Momentum[8];
  Float_t Probability[8];

  MomDistFile[0] = fopen("output/files/FermiMomDistr_PARIS.dat","r");
  //MomDistFile[1] = fopen("output/files/FermiMomDistr_CDBONN.dat","r");
  MomDistFile[1] = fopen("input/FermiMomDistr_CDBONN_Sk.dat","r");
  MomDistFile[2] = fopen("input/FermiMomDistr_chiral.dat","r");

  MomDistFile[3] = fopen("input/MomentumDistr_N_3He_Eb33.dat","r");
  MomDistFile[4] = fopen("input/MomentumDistr_N_3He_Eb53.dat","r");
  MomDistFile[5] = fopen("input/MomentumDistr_N_3He_Eb74.dat","r");
  MomDistFile[6] = fopen("input/MomentumDistr_proton_3He.dat","r");
  //MomDistFile[6] = fopen("input/MomentumDistr_proton_3He_Nogga.dat","r");

  //nucleons inside deuteron
  MomentumDistribition[0] = new TGraph(); //PARIS
  Int_t i=-1;
  while (!feof(MomDistFile[0])) {
    i++;
    fscanf(MomDistFile[0],"%f %f\n",&Momentum[0],&Probability[0]);
    //MomentumDistribition[0]->SetPoint(i,Momentum[0],Probability[0]*4*TMath::Pi());
    MomentumDistribition[0]->SetPoint(i,Momentum[0],Probability[0]);
  }

  MomentumDistribition[1] = new TGraph(); //CDBonn
  Int_t j=-1;
  while (!feof(MomDistFile[1])) {
    j++;
    fscanf(MomDistFile[1],"%f %f\n",&Momentum[1],&Probability[1]);
    //MomentumDistribition[1]->SetPoint(j,Momentum[1],Probability[1]*4*TMath::Pi());
    MomentumDistribition[1]->SetPoint(j,Momentum[1],Probability[1]);
  }

  MomentumDistribition[2] = new TGraph(); //Chiral
  Int_t k=-1;
  while (!feof(MomDistFile[2])) {
    k++;
    fscanf(MomDistFile[2],"%f %f\n",&Momentum[2],&Probability[2]);
    //MomentumDistribition[2]->SetPoint(k,Momentum[2],Probability[2]*4*TMath::Pi());
    MomentumDistribition[2]->SetPoint(k,Momentum[2],Probability[2]);
  }

  //N* inside 3He
  MomentumDistribition[3] = new TGraph(); //-0.33 MeV
  Int_t l=-1;
  while (!feof(MomDistFile[3])) {
    l++;
    fscanf(MomDistFile[3],"%f %f\n",&Momentum[3],&Probability[3]);
    MomentumDistribition[3]->SetPoint(l,Momentum[3]*0.1973,Probability[3]/0.1973*4*TMath::Pi());
  }

  MomentumDistribition[4] = new TGraph(); //-0.53 MeV
  Int_t m=-1;
  while (!feof(MomDistFile[4])) {
    m++;
    fscanf(MomDistFile[4],"%f %f\n",&Momentum[4],&Probability[4]);
    MomentumDistribition[4]->SetPoint(m,Momentum[4],Probability[4]/0.1973*TMath::Pi());
  }

  MomentumDistribition[5] = new TGraph(); //-0.74 MeV
  Int_t n=-1;
  while (!feof(MomDistFile[5])) {
    n++;
    fscanf(MomDistFile[5],"%f %f\n",&Momentum[5],&Probability[5]);
    MomentumDistribition[5]->SetPoint(n,Momentum[5]*0.1973,Probability[5]/0.1973*4*TMath::Pi());
  }

  MomentumDistribition[6] = new TGraph(); //proton inside 3He
  Int_t p=-1;
  while (!feof(MomDistFile[6])) {
    p++;
    fscanf(MomDistFile[6],"%f %f\n",&Momentum[6],&Probability[6]);
    MomentumDistribition[6]->SetPoint(p,Momentum[6]*0.1973,Probability[6]/0.1973*4*TMath::Pi());
    //MomentumDistribition[6]->SetPoint(p,Momentum[6],Probability[6]/0.1973*TMath::Pi());
  }

  gStyle->SetOptStat(kFALSE);
  gStyle->SetPalette(1,0);
  gStyle->SetOptStat(kFALSE);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.1);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadTopMargin(0.1);

  TCanvas *MyCanvas[4];
  TLegend *MyLegend[4];

  MyCanvas[0] = new TCanvas;

  //MomentumDistribition[0]->SetTitle("Fermi Momentum Distribition of Nucleons inside the Deuteron");
  MomentumDistribition[0]->GetXaxis()->SetTitle("p_{F} [GeV/c]");
  MomentumDistribition[0]->GetXaxis()->SetTitleSize(0.06);
  MomentumDistribition[0]->GetXaxis()->SetTitleOffset(1.0);
  MomentumDistribition[0]->GetXaxis()->SetLabelSize(0.05);
  MomentumDistribition[0]->GetXaxis()->SetRangeUser(0.,0.4);
  //MomentumDistribition[0]->GetYaxis()->SetTitle("probability density, c/GeV");
  MomentumDistribition[0]->GetYaxis()->SetTitle("4#piT(p_{F}) [c/GeV]");
  MomentumDistribition[0]->GetYaxis()->SetTitleSize(0.06);
  MomentumDistribition[0]->GetYaxis()->SetTitleOffset(1.2);
  MomentumDistribition[0]->GetYaxis()->SetLabelSize(0.05);
  MomentumDistribition[0]->GetYaxis()->SetRangeUser(0.,0.012);

  MomentumDistribition[0]->SetLineStyle(1);
  MomentumDistribition[0]->SetLineWidth(2);
  MomentumDistribition[0]->SetLineColor(kRed+1);
  MomentumDistribition[0]->Draw("");

  MomentumDistribition[1]->SetLineStyle(3);
  MomentumDistribition[1]->SetLineWidth(2);
  MomentumDistribition[1]->SetLineColor(kAzure-2);
  MomentumDistribition[1]->Draw("same");

  MomentumDistribition[2]->SetLineStyle(1);
  MomentumDistribition[2]->SetLineWidth(2);
  MomentumDistribition[2]->SetLineColor(kTeal-6);
  //MomentumDistribition[2]->Draw("same");

  MyLegend[0] = new TLegend(0.560, 0.750, 0.885, 0.885);
  MyLegend[0]->SetFillStyle(1); MyLegend[0]->SetFillColor(0); MyLegend[0]->SetLineColor(0); MyLegend[0]->SetTextSize(0.04);
  MyLegend[0]->AddEntry(MomentumDistribition[0], "Paris potential" , "l");
  MyLegend[0]->AddEntry(MomentumDistribition[1], "CDBonn potential" , "l");
  //MyLegend[0]->AddEntry(MomentumDistribition[1], "chiral potential" , "l");
  MyLegend[0]->Draw();

  MyCanvas[0]->Print("output/plots/FermiMomDistr_d.png","png");
  MyCanvas[0]->Print("output/plots/FermiMomDistr_d.eps","eps");

  //
  MyCanvas[1] = new TCanvas;

  MomentumDistribition[0]->GetXaxis()->SetTitle("p_{F} [GeV/c]");
  MomentumDistribition[0]->GetXaxis()->SetTitleSize(0.06);
  MomentumDistribition[0]->GetXaxis()->SetTitleOffset(1.0);
  MomentumDistribition[0]->GetXaxis()->SetLabelSize(0.05);
  MomentumDistribition[0]->GetXaxis()->SetRangeUser(0.,0.4);
  MomentumDistribition[0]->GetYaxis()->SetTitle("\\hbox{gęstość prawdop. [c/GeV]}");
  //MomentumDistribition[0]->GetYaxis()->SetTitle("4#piT(p_{F}), c/GeV");
  MomentumDistribition[0]->GetYaxis()->SetTitleSize(0.06);
  MomentumDistribition[0]->GetYaxis()->SetTitleOffset(1.2);
  MomentumDistribition[0]->GetYaxis()->SetLabelSize(0.05);
  MomentumDistribition[0]->GetYaxis()->SetRangeUser(0.,0.012);

  MomentumDistribition[0]->SetLineStyle(1);
  MomentumDistribition[0]->SetLineWidth(2);
  MomentumDistribition[0]->SetLineColor(kRed);
  MomentumDistribition[0]->Draw("");

  MomentumDistribition[1]->SetLineStyle(2);
  MomentumDistribition[1]->SetLineWidth(2);
  MomentumDistribition[1]->SetLineColor(kAzure-2);
  MomentumDistribition[1]->Draw("same");

  MomentumDistribition[2]->SetLineStyle(1);
  MomentumDistribition[2]->SetLineWidth(2);
  MomentumDistribition[2]->SetLineColor(kTeal-6);
  //MomentumDistribition[2]->Draw("same");

  MyLegend[1] = new TLegend(0.560, 0.750, 0.885, 0.885);
  MyLegend[1]->SetFillStyle(1001); MyLegend[1]->SetFillColor(19); MyLegend[1]->SetLineColor(1); MyLegend[1]->SetTextSize(0.04);
  MyLegend[1]->SetBorderSize(5);
  MyLegend[1]->AddEntry(MomentumDistribition[0], "\\hbox{potencjał paryski}" , "l");
  MyLegend[1]->AddEntry(MomentumDistribition[1], "\\hbox{potencjał CDBonn}" , "l");
  //MyLegend[1]->AddEntry(MomentumDistribition[2], "\\hbox{potencjał chiralny}" , "l");
  MyLegend[1]->Draw();

  TPaveText *ast = new TPaveText(0.329, -0.0188, 0.329, -0.0188,"ASTERISK");
  ast->SetTextSize(0.06);
  ast->SetFillColor(0);
  ast->SetTextColor(1);
  ast->SetTextAlign(22);
  ast->AddText("*");
  //ast->Draw("same");

  MyCanvas[1]->Print("output/plots/FermiMomDistr_d_pl.png","png");
  MyCanvas[1]->Print("output/plots/FermiMomDistr_d_pl.eps","eps");

  gStyle->SetPadLeftMargin(0.13);
  gStyle->SetPadRightMargin(0.1);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadTopMargin(0.1);

  //
  MyCanvas[2] = new TCanvas;

  //MomentumDistribition[3]->SetTitle("Fermi Momentum Distribition of N* inside ^{3}He");
  MomentumDistribition[3]->GetXaxis()->SetTitle("p_{F} [GeV/c]");
  MomentumDistribition[3]->GetXaxis()->SetTitleSize(0.06);
  MomentumDistribition[3]->GetXaxis()->SetTitleOffset(1.);
  MomentumDistribition[3]->GetXaxis()->SetLabelSize(0.05);
  MomentumDistribition[3]->GetXaxis()->SetRangeUser(0.,0.4);
  //MomentumDistribition[3]->GetYaxis()->SetTitle("probability density, c/GeV");
  MomentumDistribition[3]->GetYaxis()->SetTitle("4#piT(p_{F}) [c/GeV]");
  MomentumDistribition[3]->GetYaxis()->SetTitleSize(0.06);
  MomentumDistribition[3]->GetYaxis()->SetTitleOffset(0.8);
  MomentumDistribition[3]->GetYaxis()->SetLabelSize(0.05);
  //MomentumDistribition[3]->GetYaxis()->SetRangeUser(0.,0.012);

  MomentumDistribition[3]->SetLineStyle(1);
  MomentumDistribition[3]->SetLineWidth(2);
  MomentumDistribition[3]->SetLineColor(kRed);
  MomentumDistribition[3]->Draw("");

  MomentumDistribition[4]->SetLineStyle(9);
  MomentumDistribition[4]->SetLineWidth(2);
  MomentumDistribition[4]->SetLineColor(kTeal-6);
  MomentumDistribition[4]->Draw("same");

  MomentumDistribition[5]->SetLineStyle(1);
  MomentumDistribition[5]->SetLineWidth(2);
  MomentumDistribition[5]->SetLineColor(kMagenta+2);
  //MomentumDistribition[5]->Draw("same");

  MomentumDistribition[6]->SetLineStyle(3);
  MomentumDistribition[6]->SetLineWidth(2);
  MomentumDistribition[6]->SetLineColor(kAzure-2);
  MomentumDistribition[6]->Draw("same");

  MyLegend[2] = new TLegend(0.400, 0.640, 0.765, 0.885);
  MyLegend[2]->SetFillStyle(1); MyLegend[2]->SetFillColor(0); MyLegend[2]->SetLineColor(0); MyLegend[2]->SetTextSize(0.04);
  MyLegend[2]->AddEntry(MomentumDistribition[6], "proton inside ^{3}He (E_{p-d} #approx -5.5 MeV)" , "l");
  MyLegend[2]->AddEntry((TObject*)0, "N* in N*-d system:", "");
  //MyLegend[2]->AddEntry((TObject*)0, "\\hbox{N* w układzie N*-d:}", "");
  MyLegend[2]->AddEntry(MomentumDistribition[3], "E_{N*-d} = -0.33 MeV" , "l");
  MyLegend[2]->AddEntry(MomentumDistribition[4], "E_{N*-d} = -0.53 MeV" , "l");
  //MyLegend[2]->AddEntry(MomentumDistribition[5], "E_{N*-d} = -0.74 MeV" , "l");
  MyLegend[2]->Draw();

  MyCanvas[2]->Print("output/plots/FermiMomDistr_3He.png","png");
  MyCanvas[2]->Print("output/plots/FermiMomDistr_3He.eps","eps");

  //
  MyCanvas[3] = new TCanvas;

  MomentumDistribition[3]->GetXaxis()->SetTitle("p_{F} [GeV/c]");
  MomentumDistribition[3]->GetXaxis()->SetTitleSize(0.06);
  MomentumDistribition[3]->GetXaxis()->SetTitleOffset(1.);
  MomentumDistribition[3]->GetXaxis()->SetLabelSize(0.05);
  MomentumDistribition[3]->GetXaxis()->SetRangeUser(0.,0.4);
  MomentumDistribition[3]->GetYaxis()->SetTitle("4#piT(p_{F}) [c/GeV]");
  //MomentumDistribition[3]->GetYaxis()->SetTitle("4#piT(p_{F}), c/GeV");
  MomentumDistribition[3]->GetYaxis()->SetTitleSize(0.06);
  MomentumDistribition[3]->GetYaxis()->SetTitleOffset(0.8);
  MomentumDistribition[3]->GetYaxis()->SetLabelSize(0.05);
  //MomentumDistribition[3]->GetYaxis()->SetRangeUser(0.,0.012);

  MomentumDistribition[3]->SetLineStyle(1);
  MomentumDistribition[3]->SetLineWidth(2);
  MomentumDistribition[3]->SetLineColor(kRed);
  MomentumDistribition[3]->Draw("");

  MomentumDistribition[4]->SetLineStyle(1);
  MomentumDistribition[4]->SetLineWidth(2);
  MomentumDistribition[4]->SetLineColor(kAzure-2);
  MomentumDistribition[4]->Draw("same");

  MomentumDistribition[5]->SetLineStyle(1);
  MomentumDistribition[5]->SetLineWidth(2);
  MomentumDistribition[5]->SetLineColor(kTeal-6);
  MomentumDistribition[5]->Draw("same");

  MomentumDistribition[6]->SetLineStyle(2);
  MomentumDistribition[6]->SetLineWidth(2);
  MomentumDistribition[6]->SetLineColor(kMagenta+2);
  MomentumDistribition[6]->Draw("same");

  MyLegend[3] = new TLegend(0.400, 0.570, 0.885, 0.885);
  MyLegend[3]->SetFillStyle(1001); MyLegend[3]->SetFillColor(19); MyLegend[3]->SetLineColor(1); MyLegend[3]->SetTextSize(0.04);
  MyLegend[3]->SetBorderSize(5);
  MyLegend[3]->AddEntry(MomentumDistribition[6], "proton w ^{3}He (E_{p-d} ~ -5.5 MeV)" , "l");
  MyLegend[3]->AddEntry((TObject*)0, "\\hbox{N* w układzie N*-d:}", "");
  MyLegend[3]->AddEntry(MomentumDistribition[3], "E_{N*-d} = -0.33 MeV" , "l");
  MyLegend[3]->AddEntry(MomentumDistribition[4], "E_{N*-d} = -0.53 MeV" , "l");
  MyLegend[3]->AddEntry(MomentumDistribition[5], "E_{N*-d} = -0.74 MeV" , "l");
  MyLegend[3]->Draw();

  MyCanvas[3]->Print("output/plots/FermiMomDistr_N_p.png","png");
  MyCanvas[3]->Print("output/plots/FermiMomDistr_N_p.eps","eps");

}
