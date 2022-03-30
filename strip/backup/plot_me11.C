#include "TGraph.h"
#include "TLatex.h"
#include "TString.h"
#include "TCanvas.h"
#include "TLegend.h"

void plot_me11() {
 
//   setTDRStyle();

   TCanvas *c1 = new TCanvas("c1","A Simple Graph",10,10,700,500);
   c1->Divide(2,4);
   TCanvas *c2 = new TCanvas("c2","A Simple Graph",10,10,700,500);
   c2->Divide(2,4);


   TString extraText   = "CSC ME1/1, I vs Dose";
   TString extraText2   = "CSC ME1/1, R vs Dose";
   TLatex latex;
   latex.SetNDC();
   latex.SetTextFont(42);
   latex.SetTextColor(kBlack);

   const int n11 = 9, n12 = 7, n21 = 6, n22 = 6, n31 = 5, n32 = 5, n41 = 8, n42 = 9, n51 = 6, n52 = 6, n61 = 3, n62 = 3;
   double ch11[n11] = {0.08, 0.35, 11.01, 32.64, 113.27, 120.90, 152.13, 180.46, 193.55};
   double l1I1[n11] = {27.7478,9.93577,60.9106,20.9693,1164.79,735.889,3394.08,136.06,23.3796};
   double l1R1[n11];
   for(int i=0; i<n11; i++) l1R1[i] = 300/l1I1[i];

   double ch12[n12] = {0.35, 32.64, 47.68, 83.10, 113.27, 152.13, 180.46};
   double l1I2[n12] = {24.639,17.895,11.1501,1819.15,787.668,574.107,258.337};
   double l1R2[n12];
   for(int i=0; i<n12; i++) l1R2[i] = 300/l1I2[i];

   double ch21[n21] = {0.08, 0.35, 11.01, 32.64, 113.27, 120.90};
   double l2I1[n21] = {58.9516,38.6293,28.2228,66.0255,1238.83,755.245};
   double l2R1[n21];
   for(int i=0; i<n21; i++) l2R1[i] = 300/l2I1[i];

   double ch22[n22] = {0.08, 32.64, 83.10, 113.27, 180.46, 193.55};
   double l2I2[n22] = {72.8668,83.2893,1415.18,1310.68,197.621,54.0916};
   double l2R2[n22];
   for(int i=0; i<n22; i++) l2R2[i] = 300/l2I2[i];

   double ch31[n31] = {0.08, 32.64, 47.68, 152.13, 180.46};
   double l3I1[n31] = {61.317,41.7656,23.6035,2945.31,482.414};
   double l3R1[n31];
   for(int i=0; i<n31; i++) l3R1[i] = 300/l3I1[i];

   double ch32[n32] = {0.35, 11.01, 32.64, 113.27, 193.55};
   double l3I2[n32] = {8.37325,5119.22,48.6934,1301.18,106.665};
   double l3R2[n32];
   for(int i=0; i<n32; i++) l3R2[i] = 300/l3I2[i];

   double ch41[n41] = {0.08, 0.35, 32.64, 47.68, 83.10, 120.90, 152.13, 180.46};
   double l4I1[n41] = {4831.92,5986.41,1254.22,1159.46,1369.18,1396.84,2551.73,1157};
   double l4R1[n41];
   for(int i=0; i<n41; i++) l4R1[i] = 300/l4I1[i];

   double ch42[n42] = {0.08, 11.01, 32.64, 47.68, 83.10, 113.27, 120.90, 152.13, 180.46};
   double l4I2[n42] = {8788.52,2285.21,2283.84,2679.38,2654.67,2279.43,3032.61,1748.55};
   double l4R2[n42];
   for(int i=0; i<n42; i++) l4R2[i] = 300/l4I2[i];

   double ch51[n51] = {32.64, 47.68, 113.27, 152.13, 180.46, 193.55};
   double l5I1[n51] = {41.1564,40.1973,749.42,2488.07,605.576,183.644};
   double l5R1[n51];
   for(int i=0; i<n51; i++) l5R1[i] = 300/l5I1[i];

   double ch52[n52] = {0.08, 0.35, 32.64, 47.68, 83.10, 193.55};
   double l5I2[n52] = {62.8957,17.6732,47.6446,34.0241,438.731,155.048};
   double l5R2[n52];
   for(int i=0; i<n52; i++) l5R2[i] = 300/l5I2[i];

   double ch61[n61] = {0.08, 180.46, 193.55};
   double l6I1[n61] = {6.11943, 253.694, 71.446};
   double l6R1[n61];
   for(int i=0; i<n61; i++) l6R1[i] = 300/l6I1[i];

   double ch62[n62] = {120.90, 180.46, 193.55};
   double l6I2[n62] = {704.812, 326.381, 99.025};
   double l6R2[n62];
   for(int i=0; i<n62; i++) l6R2[i] = 300/l6I2[i];


   TGraph *gI11 = new TGraph(n11, ch11, l1I1);
   TGraph *gI12 = new TGraph(n12, ch12, l1I2);
   TGraph *gI21 = new TGraph(n21, ch21, l2I1);
   TGraph *gI22 = new TGraph(n22, ch22, l2I2);
   TGraph *gI31 = new TGraph(n31, ch31, l3I1);
   TGraph *gI32 = new TGraph(n32, ch32, l3I2);
   TGraph *gI41 = new TGraph(n41, ch41, l4I1);
   TGraph *gI42 = new TGraph(n42, ch42, l4I2);
   TGraph *gI51 = new TGraph(n51, ch51, l5I1);
   TGraph *gI52 = new TGraph(n52, ch52, l5I2);
   TGraph *gI61 = new TGraph(n61, ch61, l6I1);
   TGraph *gI62 = new TGraph(n62, ch62, l6I2);

   TGraph *gR11 = new TGraph(n11, ch11, l1R1);
   TGraph *gR12 = new TGraph(n12, ch12, l1R2);
   TGraph *gR21 = new TGraph(n21, ch21, l2R1);
   TGraph *gR22 = new TGraph(n22, ch22, l2R2);
   TGraph *gR31 = new TGraph(n31, ch31, l3R1);
   TGraph *gR32 = new TGraph(n32, ch32, l3R2);
   TGraph *gR41 = new TGraph(n41, ch41, l4R1);
   TGraph *gR42 = new TGraph(n42, ch42, l4R2);
   TGraph *gR51 = new TGraph(n51, ch51, l5R1);
   TGraph *gR52 = new TGraph(n52, ch52, l5R2);
   TGraph *gR61 = new TGraph(n61, ch61, l6R1);
   TGraph *gR62 = new TGraph(n62, ch62, l6R2);


   c1->cd(1);
   gI11->SetTitle("layer1; Accumulated charge [mC/cm]; I [pA]");
   gI11->SetMarkerColor(kRed);
   gI11->SetMinimum(0);
   gI11->SetMaximum(3500);
   gI11->SetMarkerColor(kRed);
   gI11->SetMarkerStyle(22);
   gI11->Draw("ALP");
   gI12->SetMarkerColor(kGreen+3);
   gI12->SetMarkerStyle(24);
   gI12->Draw("LP same");
   c1->cd(7);
   latex.DrawLatex(0.5, 0.8, extraText);
   TLegend *leg1 = new TLegend(0.18, 0.68 ,0.48, 0.88);
   leg1->AddEntry(gI11, "strip11", "p");
   leg1->AddEntry(gI12, "strip12", "p");
   leg1->Draw();

   c1->cd(2);
   gI22->SetTitle("layer2; Accumulated charge [mC/cm]; I [pA]");
   gI22->SetMarkerColor(kGreen+3);
   gI22->SetMinimum(0);
   gI22->SetMaximum(3500);
   gI22->SetMarkerColor(kGreen+3);
   gI22->SetMarkerStyle(24);
   gI22->Draw("ALP");
   gI21->SetMarkerColor(kRed);
   gI21->SetMarkerStyle(22);
   gI21->Draw("LP same");

   c1->cd(3);
   gI31->SetTitle("layer3; Accumulated charge [mC/cm]; I [pA]");
   gI31->SetMarkerColor(kRed);
   gI31->SetMinimum(0);
   gI31->SetMaximum(3500);
   gI31->SetMarkerColor(kRed);
   gI31->SetMarkerStyle(22);
   gI31->Draw("ALP");
   gI32->SetMarkerColor(kGreen+3);
   gI32->SetMarkerStyle(24);
   gI32->Draw("LP same");

   c1->cd(4);
   gI41->SetTitle("layer4; Accumulated charge [mC/cm]; I [pA]");
   gI41->SetMarkerColor(kRed);
   gI41->SetMinimum(0);
   gI41->SetMaximum(3500);
   gI41->SetMarkerColor(kRed);
   gI41->SetMarkerStyle(22);
   gI41->Draw("ALP");
   gI42->SetMarkerColor(kGreen+3);
   gI42->SetMarkerStyle(24);
   gI42->Draw("LP same");

   c1->cd(5);
   gI51->SetTitle("layer5; Accumulated charge [mC/cm]; I [pA]");
   gI51->SetMarkerColor(kRed);
   gI51->SetMinimum(0);
   gI51->SetMaximum(3500);
   gI51->SetMarkerColor(kRed);
   gI51->SetMarkerStyle(22);
   gI51->Draw("ALP");
   gI52->SetMarkerColor(kGreen+3);
   gI52->SetMarkerStyle(24);
   gI52->Draw("LP same");

   c1->cd(6);
   gI61->SetTitle("layer5; Accumulated charge [mC/cm]; I [pA]");
   gI61->SetMarkerColor(kRed);
   gI61->SetMinimum(0);
   gI61->SetMaximum(3500);
   gI61->SetMarkerColor(kRed);
   gI61->SetMarkerStyle(22);
   gI61->Draw("ALP");
   gI62->SetMarkerColor(kGreen+3);
   gI62->SetMarkerStyle(24);
   gI62->Draw("LP same");


   c2->cd(1);
   gR11->SetTitle("layer1; Accumulated charge [mC/cm]; R [V/pA]");
   gR11->SetMarkerColor(kRed);
   gR11->SetMinimum(0);
   gR11->SetMaximum(30);
   gR11->SetMarkerColor(kRed);
   gR11->SetMarkerStyle(22);
   gR11->Draw("ALP");
   gR12->SetMarkerColor(kGreen+3);
   gR12->SetMarkerStyle(24);
   gR12->Draw("LP same");
   c2->cd(7);
   latex.DrawLatex(0.5, 0.8, extraText2);
   TLegend *leg6 = new TLegend(0.18, 0.68 ,0.48, 0.88);
   leg6->AddEntry(gR11, "strip11", "p");
   leg6->AddEntry(gR12, "strip12", "p");
   leg6->Draw();

   c2->cd(2);
   gR22->SetTitle("layer1; Accumulated charge [mC/cm]; R [V/pA]");
   gR22->SetMarkerColor(kGreen+3);
   gR22->SetMinimum(0);
   gR22->SetMaximum(30);
   gR22->SetMarkerColor(kGreen+3);
   gR22->SetMarkerStyle(24);
   gR22->Draw("ALP");
   gR21->SetMarkerColor(kRed);
   gR21->SetMarkerStyle(22);
   gR21->Draw("LP same");

   c2->cd(3);
   gR31->SetTitle("layer1; Accumulated charge [mC/cm]; R [V/pA]");
   gR31->SetMarkerColor(kRed);
   gR31->SetMinimum(0);
   gR31->SetMaximum(30);
   gR31->SetMarkerColor(kRed);
   gR31->SetMarkerStyle(22);
   gR31->Draw("ALP");
   gR32->SetMarkerColor(kGreen+3);
   gR32->SetMarkerStyle(24);
   gR32->Draw("LP same");

   c2->cd(4);
   gR41->SetTitle("layer1; Accumulated charge [mC/cm]; R [V/pA]");
   gR41->SetMarkerColor(kRed);
   gR41->SetMinimum(0);
   //gR41->SetMaximum(3);
   gR41->SetMarkerColor(kRed);
   gR41->SetMarkerStyle(22);
   gR41->Draw("ALP");
   gR42->SetMarkerColor(kGreen+3);
   gR42->SetMarkerStyle(24);
   gR42->Draw("LP same");

   c2->cd(5);
   gR51->SetTitle("layer1; Accumulated charge [mC/cm]; R [V/pA]");
   gR51->SetMarkerColor(kRed);
   gR51->SetMinimum(0);
   gR51->SetMaximum(30);
   gR51->SetMarkerColor(kRed);
   gR51->SetMarkerStyle(22);
   gR51->Draw("ALP");
   gR52->SetMarkerColor(kGreen+3);
   gR52->SetMarkerStyle(24);
   gR52->Draw("LP same");

   c2->cd(6);
   gR61->SetTitle("layer1; Accumulated charge [mC/cm]; R [V/pA]");
   gR61->SetMarkerColor(kRed);
   gR61->SetMinimum(0);
   gR61->SetMaximum(30);
   gR61->SetMarkerColor(kRed);
   gR61->SetMarkerStyle(22);
   gR61->Draw("ALP");
   gR62->SetMarkerColor(kGreen+3);
   gR62->SetMarkerStyle(24);
   gR62->Draw("LP same");


c1->SaveAs("me11I.root");  
c2->SaveAs("me11R.root");
//c1->SaveAs("me11.eps");
}
