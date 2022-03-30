#include "TROOT.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TString.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TText.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1.h"
#include <iostream>
#include <fstream>
using namespace std;
// parameters: data output file name, save/don't save plot, min range on the X axis for fit, max range on the X axis for fit, nbins for fit histo, min range on Y axis for fit, max range on Y axis for fit
void plotOne(TString filename, bool SavePlot = false, TString Voltage="", double range_min = -1, double range_max = -1, int histo_bins = 100, double histo_min = -1, double histo_max = -1){
  gROOT->ProcessLine(".L ./tdrstyle.C");
  gROOT->ProcessLine("setTDRStyle()");
  gStyle->SetOptStat(1111);
  TString dir = "./";
  ifstream myfile;
  myfile.open(dir+filename+".txt");

  char str1[100];
  char str2[100];
  char str3[100];
  char str4[100];
  double resistance = -999;
  vector<double> vecX(0);
  vector<double> vecY(0);
  if (myfile.is_open()) {
    int i = 0;
    while (!myfile.eof()) {
      myfile >> str1>>str2>>str3>>str4>>resistance;
      //cout<<str1<<"\t"<<str2<<"\t"<<resistance<<endl;
      vecX.push_back(i);
      vecY.push_back(resistance);
      i++;
    }
  }
  myfile.close();

  double arrX[vecX.size()];
  double arrY[vecY.size()];

  TH1D *histo = new TH1D("histo", filename+Voltage+";current [A]; entries", histo_bins, histo_min, histo_max);
   for(uint i=0; i< vecX.size(); ++i){
    arrX[i] = vecX[i];
    arrY[i] = vecY[i];
    if(i >= range_min && i <= range_max){histo->Fill(vecY[i]);}
  }

  TCanvas *c1 = new TCanvas("c1");
  TCanvas *c2 = new TCanvas("c2");
  TGraph *gr = new TGraph(vecX.size(), arrX, arrY); 
  //gr->GetYaxis()->SetTitle("Resistance [#Omega]");
  //gr->SetTitle(";entry;Resistance [#Omega]");
  gr->SetTitle(";entry;Current [A]");
  gr->GetXaxis()->CenterTitle();
  gr->GetYaxis()->CenterTitle();
  gr->SetMarkerStyle(20);
  c1->cd();
  gr->Draw("AC");// P for point, C for curve

  cout<<"Mean = "<<(double)gr->GetMean(2)<<endl;
  cout<<"RMS = "<<(double)gr->GetRMS(2)<<endl;


  TLegend *leg = new TLegend(0.272613,0.938811,0.994975,0.993007,NULL,"brNDC");
  leg->SetHeader(filename+Voltage);
  leg->SetBorderSize(0);
  leg->SetTextAlign(32);
  leg->Draw();

  c2->cd();
  histo->Fit("gaus");
  histo->Draw();
  if(SavePlot){
    c1->SaveAs("/afs/cern.ch/work/a/ashriniv/scratch8/CMSSW_7_2_0/src/img/"+filename+Voltage+".png");
    c2->SaveAs("/afs/cern.ch/work/a/ashriniv/scratch8/CMSSW_7_2_0/src/img/"+filename+Voltage+"_h.png");
  }

  return;
}
