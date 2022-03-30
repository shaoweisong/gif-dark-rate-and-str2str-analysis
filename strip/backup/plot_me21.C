#include "TGraph.h"
#include "TLatex.h"
#include "TString.h"
#include "TCanvas.h"
#include "TLegend.h"

void plot_me21() {
 
//   setTDRStyle();

   TCanvas *c1 = new TCanvas("c1","A Simple Graph",10,10,700,500);
   c1->Divide(2,3);
   TCanvas *c2 = new TCanvas("c2","A Simple Graph",10,10,700,500);
   c2->Divide(2,3);

   TString extraText   = "CSC ME2/1, I vs Dose";
   TString extraText2   = "CSC ME2/1, R vs Dose";
   TLatex latex;
   latex.SetNDC();
   latex.SetTextFont(42);
   latex.SetTextColor(kBlack);

   const int n11 = 9, n12 = 9, n21 = 9, n22 = 8, n31 = 7, n32 = 5, n41 = 9, n42 = 7, n51 = 6, n52 = 7;
   double ch11[n11] = {0.29, 17.95, 50.21, 80.48, 108.06, 178.52, 191.84, 197.36, 211.80};
   double l1I1[n11] = {50.2164, 85.7767, 23.1398, 363.663, 16238.8, 150.734, 1485.22, 56.3293, 671.375};
   double l1R1[n11];
   for(int i=0; i<n11; i++) l1R1[i] = 300/l1I1[i];

   double ch12[n12] = {0.29, 17.95, 50.21, 80.48, 108.06, 124.68, 178.52, 197.36, 211.80};
   double l1I2[n12] = {62.3635, 88.4985, 27.177, 327.159, 815.123, 996.744, 257.97, 80.9199, 855.293};
   double l1R2[n12];
   for(int i=0; i<n12; i++) l1R2[i] = 300/l1I2[i];

   double ch21[n21] = {0.29, 17.95, 50.21, 80.48, 108.06, 178.52, 191.84, 197.36, 211.80};
   double l2I1[n21] = {14.4276, 30.8359, 0.335646, 103.495, 1492.48, 182.639, 997.963, 46.242, 894.029};
   double l2R1[n21];
   for(int i=0; i<n21; i++) l2R1[i] = 300/l2I1[i];

   double ch22[n22] = {0.29, 17.95, 50.21, 80.48, 108.06, 178.52, 197.36, 211.80};
   double l2I2[n22] = {16.0995, 33.7227, 0.388169, 161.933, 1226.7, 209.413, 43.5858, 910.281};
   double l2R2[n22];
   for(int i=0; i<n22; i++) l2R2[i] = 300/l2I2[i];

   double ch31[n31] = {0.29, 50.21, 80.48, 108.06, 124.68, 197.36, 211.80};
   double l3I1[n31] = {68.2443, 674.57, 7108.8, 10694.8, 8149.75, 698.961, 6125.93};
   double l3R1[n31];
   for(int i=0; i<n31; i++) l3R1[i] = 300/l3I1[i];

   double ch32[n32] = {0.29, 50.21, 80.48, 178.52, 211.80};
   double l3I2[n32] = {60.495, 1144.64, 10268.2, 9121.75, 9906.25};
   double l3R2[n32];
   for(int i=0; i<n32; i++) l3R2[i] = 300/l3I2[i];

   double ch41[n41] = {0.29, 50.21, 80.48, 108.06, 124.68, 178.52, 191.84, 197.36, 211.80};
   double l4I1[n41] = {16.085, 4.5594, 100.621, 379.425, 487.964, 292.559, 700.226, 111.935, 449.137};
   double l4R1[n41];
   for(int i=0; i<n41; i++) l4R1[i] = 300/l4I1[i];

   double ch42[n42] = {50.21, 80.48, 108.06, 124.68, 178.52, 197.36, 211.80};
   double l4I2[n42] = {3.31637, 151.936, 404.611, 639.664, 290.471, 106.25, 710.147};
   double l4R2[n42];
   for(int i=0; i<n42; i++) l4R2[i] = 300/l4I2[i];

   double ch51[n51] = {0.29, 80.48, 108.06, 178.52, 197.36, 211.80};
   double l5I1[n51] = {63.5923, 5371.6, 8495.84, 6160.98, 1002.01, 7916.29};
   double l5R1[n51];
   for(int i=0; i<n51; i++) l5R1[i] = 300/l5I1[i];

   double ch52[n52] = {0.29, 50.21, 80.48, 108.06, 178.52, 197.36, 211.80};
   double l5I2[n52] = {98.8959, 611.28, 6137.6, 9708.91, 7086.08, 1083.12, 9181.95};
   double l5R2[n52];
   for(int i=0; i<n52; i++) l5R2[i] = 300/l5I2[i];


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
   c1->cd(6);
   latex.DrawLatex(0.5, 0.8, extraText);
   TLegend *leg1 = new TLegend(0.18, 0.68 ,0.48, 0.88);
   leg1->AddEntry(gI11, "strip12", "p");
   leg1->AddEntry(gI12, "strip23", "p");
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
   c2->cd(6);
   latex.DrawLatex(0.5, 0.8, extraText2);
   TLegend *leg6 = new TLegend(0.18, 0.68 ,0.48, 0.88);
   leg6->AddEntry(gR11, "strip12", "p");
   leg6->AddEntry(gR12, "strip23", "p");
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


c1->SaveAs("me21I.root");  
c2->SaveAs("me21R.root");
//c1->SaveAs("me11.eps");
}
