#include "TROOT.h"
#include "TFrame.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TString.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TText.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TF1.h"
#include "TH1.h"
#include "tdrstyle_mod.C"
#include <iostream>
#include <fstream>

using namespace std;

void test_plot(){
   setTDRStyle();
   //gROOT->ProcessLine(".L ./tdrstyle.C");
   //gROOT->ProcessLine("setTDRStyle()");
   gStyle->SetOptStat(1111);
   //gStyle->SetPadRightMargin(0.01);
   //gStyle->SetPadLeftMargin(0.01);
   //gStyle->SetLineWidth(2);
   TString dirname =  "strip_to_strip_ME21_23_11_2016";
   TString filename = "/ClosedCircuit_ShortCables_WithBox_300V_";
   ifstream myfile;
   ofstream ofile(dirname+"_new.txt");
   TString suffix[10] = {"layer1_strips12", "layer1_strips23", "layer2_strips12", "layer2_strips23", "layer3_strips12", "layer3_strips23", "layer4_strips12", "layer4_strips23", "layer5_strips12", "layer5_strips23"};

   for(int j = 0; j < 10 ; j++) {
      myfile.open(dirname+filename+suffix[j]);
      double data_points = - 999;
      double voltage= -1;
      vector<double> vecX(0);
      vector<double> vecY(0);
      vector<double> vecX_300(0);
      vector<double> vecY_300(0);
      char str1[100];
      char str2[100];
      char str3[100];

      int i=0, max_1 =0, max_2=0 ;
      if (myfile.is_open()){
         while (!myfile.eof()){
	    myfile >>str1>>str2>>str3>>voltage>> data_points;
	    if (voltage==0){
	       vecX.push_back(max_1);
	       vecY.push_back(data_points);
	       max_1++;}
	    else if (voltage==300){
	       vecX_300.push_back(max_2);
	       vecY_300.push_back(data_points);
	       max_2++;}
	 }
      }
      myfile.close();
      double *arrX=new double [vecX.size()];
      double *arrY=new double [vecY.size()];
      double *arrX_300= new double[vecX_300.size()];
      double *arrY_300 = new double[vecY_300.size()];
      double *eX= new double [vecX.size()];
      double *eY= new double[vecY.size()];
      double *eX_300 = new double[vecX_300.size()];
      double *eY_300 = new double[vecY_300.size()];

      for (i=0;i<max_1-1; ++i){
         arrX[i]=vecX[i];
	 arrY[i]=vecY[i];
	 eX[i]=0;
	 eY[i]=0.01E-9;
	 //cout <<i<<arrX[i]<<arrY[i]<<endl;
      }
      //cout<<endl;
      for (i=0; i<max_2-1; ++i){
	 arrX_300[i]=vecX_300[i];
	 arrY_300[i]=vecY_300[i];
	 eX_300[i]=0;
	 eY_300[i]=0.1E-10;
	 //cout <<i<<arrX_300[i]<<arrY_300[i]<<endl;
      }
      //cout<<endl;
      //cout<<arrY_300[0]<<"\t"<< arrY[(max_1)/2]<<"\t"<< arrY[max_1-2]<<max_1 <<endl;
      //cout<<arrY_300[0]<<"\t"<< arrY_300[(max_2)/2]<<"\t"<< arrY_300[max_2-2]<<max_2<< endl;
      TGraphErrors *g1 = new TGraphErrors(vecX.size()-1,arrX,arrY,eX,eY);
      TGraphErrors *g2 = new TGraphErrors(vecX_300.size()-1,arrX_300,arrY_300,eX_300,eY_300);
      g1->SetMarkerStyle(1);
      g2->SetMarkerStyle(1);
      g1->SetLineWidth(1);
      g2->SetLineWidth(1);
      g1->SetLineColor(4);
      g2->SetLineColor(4);
      //g1->SetTitle("Plot of Current vs Time at 0V");
      g1->GetYaxis()->SetLimits(-2.0E-9,2.0E-9);
      g1->GetXaxis()->SetTitle("Time [s]");
      g1->GetYaxis()->SetTitle("Current [A]");
      g1->GetXaxis()->CenterTitle();
      g1->GetYaxis()->CenterTitle();
      g1->GetXaxis()->SetNdivisions(505,kTRUE);
      //g1->GetYaxis()->SetNoExponent(kTRUE);
      g2->GetYaxis()->SetLimits(0,2.0E-9);
      g2->GetXaxis()->SetNdivisions(505,kTRUE);
      //g2->SetTitle("Plot of Current vs Time at 300V");
      g2->GetXaxis()->SetTitle("Time [s]");
      g2->GetYaxis()->SetTitle("Current [A]");
      g2->GetXaxis()->CenterTitle();
      g2->GetYaxis()->CenterTitle();
      //g2->GetYaxis()->SetNoExponent(kTRUE);
      g1->SetFillColor(2);
      g1->SetFillStyle(3004);
      g2->SetFillColor(2);
      g2->SetFillStyle(3004);

      TCanvas *c1 = new TCanvas("c1","The Exponential Fit", 1000, 700);
      c1->Divide(2,1);
      c1->SetGrid();
      c1->GetFrame()->SetFillColor(21);
      c1->GetFrame()->SetBorderMode(-1);
      c1->GetFrame()->SetBorderSize(5);
      TF1 *fit_exp_0= new TF1("fit_exp_0","[0]+[1]*exp(-[2]*x)",80.0,max_1);
      TF1 *fit_exp_300 = new TF1("fit_exp_300","[0]+[1]*exp(-[2]*x)",80.0,max_2);
      fit_exp_0->SetParameters(1.0E-9,2.0E-9,0.026);
      fit_exp_300->SetParameters(1.0E-9,2.0E-9,0.026);
      fit_exp_0->SetLineWidth(2);
      fit_exp_300->SetLineWidth(2);
      fit_exp_0->SetLineColor(1);
      fit_exp_300->SetLineColor(1);
      c1->cd(1);
      g1->Fit(fit_exp_0,"MR");
      g1->Draw("al4");
      double mean_0 = fit_exp_0->GetParameter(0);
      double sigma_0 = fit_exp_0->GetParError(0);
      c1->cd(2);
      g2->Fit(fit_exp_300,"RM");
      g2->Draw("al4");
      double mean_300 = fit_exp_300->GetParameter(0);
      double sigma_300 = fit_exp_300->GetParError(0);

      double R = 300./(mean_300-mean_0);
      double eR = R*(sqrt(sigma_0*sigma_0+sigma_300*sigma_300))/(mean_300-mean_0);

      ofile<<suffix[j]<<" : "<<R<<"\t "<<eR<<endl;
      c1->Modified();
      c1->Update();
      c1->SaveAs("ME11_"+suffix[j]+".png");

   }
   ofile.close();
   return;
}

