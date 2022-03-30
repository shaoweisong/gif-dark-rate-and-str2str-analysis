{
 
//   setTDRStyle();

   TCanvas *c1 = new TCanvas("c1","A Simple Graph",10,10,700,500);
   c1->Divide(3,2);
//   TCanvas *c2 = new TCanvas("c2","A Simple Graph",10,10,700,500);
//   c2->Divide(2,2);

//   TString extraText   = "R1: Resistance between strip1 and strip2 of layer1";
//   TString extraText2   = "CSC ME2/1, R/R1 vs Dose";
//   TLatex latex;
//   latex.SetNDC();
//   latex.SetTextFont(42);
//   latex.SetTextColor(kBlack);

   const int n11 = 13, n12 = 13, n21 = 13, n22 = 13, n31 = 13, n32 = 13, n41 = 13, n42 = 13, n51 = 13, n52 = 13;
   double ch11[n11] = {0.29, 50.21,  80.48, 108.06, 178.52, 197.36, 211.80, 233.97, 249.59, 279.56, 306.86, 315.10, 332.99};
   double l1I1[n11] = {59.5469, 25.1602, 366.869, 1623.88, 140.401, 75.3954, 698.683, 1134.78, 495.521, 171.638, 4266.44, 4855.91, 6986.95};
   double R1[n11], l1R1[n11], average=0;
   for(int i=0; i<n11; i++) {R1[i] = 300.0/l1I1[i]; average += R1[i];}
   average /= n11;
   for(int i=0; i<n11; i++) l1R1[i] = 300.0/l1I1[i];

   double ch12[n12] = {0.29, 50.21,  80.48, 108.06, 178.52, 197.36, 211.80, 233.97, 249.59, 279.56, 306.86, 315.10, 332.99};
   double l1I2[n12] = {61.8946, 28.1749, 331.152, 818.352, 287.237, 90.0263, 865.84, 1427.83, 563.831, 203.56, 5438.92, 4879.78, 6371.34};
   double l1R2[n12];
   for(int i=0; i<n12; i++) l1R2[i] = 300.0/l1I2[i];

   double ch21[n21] = {0.29, 50.21,  80.48, 108.06, 178.52, 197.36, 211.80, 233.97, 249.59, 279.56, 306.86, 315.10, 332.99};
   double l2I1[n21] = {19.3006, 1.16296, 110.361, 1602.83, 167.448, 78.759, 896.508, 1317.72, 483.934, 155.229, 4878.38, 4869.41, 5987.58};
   double l2R1[n21];
   for(int i=0; i<n21; i++) l2R1[i] = 300.0/l2I1[i];

   double ch22[n22] = {0.29, 50.21,  80.48, 108.06, 178.52, 197.36, 211.80, 233.97, 249.59, 279.56, 306.86, 315.10, 332.99};
   double l2I2[n22] = {18.0672, 1.04145, 162.827, 1163.9, 186.32, 60.9819, 1000.22, 1412.24, 693.8, 153.514, 5060.66, 6531.57, 5980.24};
   double l2R2[n22];
   for(int i=0; i<n22; i++) l2R2[i] = 300.0/l2I2[i];

   double ch31[n31] = {0.29, 50.21,  80.48, 108.06, 178.52, 197.36, 211.80, 233.97, 249.59, 279.56, 306.86, 315.10, 332.99};
   double l3I1[n31] = {67.9935, 674.59, 7163.94, 10707.7, 5802.09, 695.095, 6310.42, 12034.6, 14154.2, 11122.7, 12971.1, 14854.7, 14589.3};
   double l3R1[n31];
   for(int i=0; i<n31; i++) l3R1[i] = 300.0/l3I1[i];

   double ch32[n32] = {0.29, 50.21,  80.48, 108.06, 178.52, 197.36, 211.80, 233.97, 249.59, 279.56, 306.86, 315.10, 332.99};
   double l3I2[n32] = {59.5346, 1144.53, 10325.2, 15253.1, 9154.39, 964.278, 10013.4, 18678.4, 22293.2, 17314.4, 19187.8, 22221.9, 20595.3};
   double l3R2[n32];
   for(int i=0; i<n32; i++) l3R2[i] = 300.0/l3I2[i];

   double ch41[n41] = {0.29, 50.21,  80.48, 108.06, 178.52, 197.36, 211.80, 233.97, 249.59, 279.56, 306.86, 315.10, 332.99};
   double l4I1[n41] = {19.8606, 4.40432, 108.036, 374.51, 255.413, 126.047, 506.506, 523.87, 436.014, 257.497, 2613.93, 3555.8, 5253.27};
   double l4R1[n41];
   for(int i=0; i<n41; i++) l4R1[i] = 300.0/l4I1[i];

   double ch42[n42] = {0.29, 50.21,  80.48, 108.06, 178.52, 197.36, 211.80, 233.97, 249.59, 279.56, 306.86, 315.10, 332.99};
   double l4I2[n42] = {29.9802, 3.23759, 158.902, 894.079, 264.763, 109.638, 692.704, 1315.91, 872.612, 229.495, 3435.48, 4524.69, 5714.19};
   double l4R2[n42];
   for(int i=0; i<n42; i++) l4R2[i] = 300.0/l4I2[i];

   double ch51[n51] = {0.29, 50.21,  80.48, 108.06, 178.52, 197.36, 211.80, 233.97, 249.59, 279.56, 306.86, 315.10, 332.99};
   double l5I1[n51] = {74.3524, 453.139, 5379.47, 8496.2, 6130.93, 1007.87, 7945.78, 16816, 19848, 16953.1, 18945.1, 21454.5, 20130.6};
   double l5R1[n51];
   for(int i=0; i<n51; i++) l5R1[i] = 300.0/l5I1[i];

   double ch52[n52] = {0.29, 50.21,  80.48, 108.06, 178.52, 197.36, 211.80, 233.97, 249.59, 279.56, 306.86, 315.10, 332.99};
   double l5I2[n52] = {100.684, 612.652, 6134.01, 9693.66, 7043.27, 1101.31, 9303.26, 19039.5, 22488.9, 18747.4, 21526.7, 24541.4, 23666.4};
   double l5R2[n52];
   for(int i=0; i<n52; i++) l5R2[i] = 300.0/l5I2[i];

/*
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
*/
//   TGraph *gR1 = new TGraph(n11, ch11, R1);
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

/*
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
*/

   c1->cd(1);   gPad->SetLogy();
   gR11->SetTitle("layer1; Accumulated charge [mC/cm]; R [T#Omega]");
   gR11->SetMinimum(0.001);
   gR11->SetMaximum(1000);
   gR11->SetMarkerColor(kGreen+3);
   gR11->SetMarkerStyle(24);
   gR11->Draw("AP");
   gR12->SetMarkerColor(kRed);
   gR12->SetMarkerStyle(22);
   gR12->Draw("P same");
//   c1->cd(1);
//   latex.DrawLatex(0.15, 0.4, extraText);
//   latex.DrawLatex(0.15, 0.5, extraText2);
   TLegend *leg1 = new TLegend(0.58, 0.68 ,0.88, 0.88);
   leg1->AddEntry(gR11, "strips 1&2", "p");
   leg1->AddEntry(gR12, "strips 2&3", "p");
   leg1->Draw();
/*
   c1->cd(2);   gPad->SetLogy();
   gR1->SetTitle("layer1; Accumulated charge [mC/cm]; R1 [T#Omega]");
   gR1->SetMinimum(0.001);
   gR1->SetMaximum(1000);
   gR1->SetMarkerColor(kRed);
   gR1->SetMarkerStyle(22);
   gR1->Draw("ALP");
*/
   c1->cd(2);   gPad->SetLogy();
   gR22->SetTitle("layer2; Accumulated charge [mC/cm]; R [T#Omega]");
   gR22->SetMinimum(0.001);
   gR22->SetMaximum(1000);
   gR22->SetMarkerColor(kGreen+3);
   gR22->SetMarkerStyle(22);
   gR22->Draw("AP");
   gR21->SetMarkerColor(kRed);
   gR21->SetMarkerStyle(24);
   gR21->Draw("P same");

   c1->cd(3);   gPad->SetLogy();
   gR31->SetTitle("layer3; Accumulated charge [mC/cm]; R [T#Omega]");
   gR31->SetMinimum(0.001);
   gR31->SetMaximum(1000);
   gR31->SetMarkerColor(kGreen+3);
   gR31->SetMarkerStyle(24);
   gR31->Draw("AP");
   gR32->SetMarkerColor(kRed);
   gR32->SetMarkerStyle(22);
   gR32->Draw("P same");
//   c2->cd(1);
//   latex.DrawLatex(0.15, 0.4, extraText);
//   latex.DrawLatex(0.15, 0.5, extraText2);
//   TLegend *leg2 = new TLegend(0.18, 0.68 ,0.48, 0.88);
//   leg2->AddEntry(gR31, "strips 1&2", "p");
//   leg2->AddEntry(gR32, "strips 2&3", "p");
//   leg2->Draw();

   c1->cd(4);   gPad->SetLogy();
   gR41->SetTitle("layer4; Accumulated charge [mC/cm]; R [T#Omega]");
   gR41->SetMinimum(0.001);
   gR41->SetMaximum(1000);
   gR41->SetMarkerColor(kGreen+3);
   gR41->SetMarkerStyle(24);
   gR41->Draw("AP");
   gR42->SetMarkerColor(kRed);
   gR42->SetMarkerStyle(22);
   gR42->Draw("P same");

   c1->cd(5);   gPad->SetLogy();
   gR51->SetTitle("layer5; Accumulated charge [mC/cm]; R [T#Omega]");
   gR51->SetMinimum(0.001);
   gR51->SetMaximum(1000);
   gR51->SetMarkerColor(kGreen+3);
   gR51->SetMarkerStyle(24);
   gR51->Draw("AP");
   gR52->SetMarkerColor(kRed);
   gR52->SetMarkerStyle(22);
   gR52->Draw("P same");


//c1->SaveAs("me21I.root");  
c1->SaveAs("me21R.root");
}
