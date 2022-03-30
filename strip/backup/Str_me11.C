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
#include "TDatime.h"
#include <iostream>
#include <fstream>

{
// need to set n to the number of lines in stripcharges.txt or stripdates.txt, C++ wont let you initialize objects of variable size.
const int n = 16;
char dirs[100];
std::vector<TString> dirnames;
double q;
int ich;

ifstream dirnamesfile;
dirnamesfile.open("../test1/stripdates.txt");
ifstream chargefile;
chargefile.open("../test1/stripcharges.txt");
TString layerstripstrlist[12] = {"layer1_strips12_300V", "layer1_strips23_300V", "layer2_strips12_300V", "layer2_strips23_300V", "layer3_strips12_300V", "layer3_strips23_300V", "layer4_strips12_300V", "layer4_strips23_300V", "layer5_strips12_300V", "layer5_strips23_300V", "layer6_strips12_300V", "layer6_strips23_300V"};


if (dirnamesfile.is_open()) {
     while (!dirnamesfile.eof()){
         dirnamesfile >> dirs;
         TString tmp = dirs;
         dirnames.push_back(tmp);
         }
     }
dirnamesfile.close();

class Current {
    std::vector<double> I;
    std::vector<double> dI;
} layerstripIs[12];

double GetR( double I ) {
    return 300.0/TMath::Abs(I);
}

double GetdR( double I , double dI ) {
    return 300.0/TMath::Power(I, 2) * TMath::Abs(dI);
}
class Resistance {
    std::vector<double> R;
    std::vector<double> dR;
} 

class Chamber {
    std::vector<Resistance> Res[6];
    std::vector<Current> Curr[6];
} 

LayerStripR GetLayerStripR ( Current current ) {
    Resistance output = new Resistance()
    std::transform(current.I.begin(), current.I.end(), std::back_inserter(output.R), GetR());
    std::transform(current.I.begin(), current.I.end(), current.dI.begin(), std::back_inserter(output.dR), GetdR());
    return output;
}

TGraphErrors * MakeGraph( Resistance resistances, std::vector<double> charges) {

}

//n = dirnames.size();
//std::vector<double> l1R1(0);
//std::vector<double> l1R2(0);
//std::vector<double> l2R1(0);
//std::vector<double> l2R2(0);
//std::vector<double> l3R1(0);
//std::vector<double> l3R2(0);
//std::vector<double> l4R1(0);
//std::vector<double> l4R2(0);
//std::vector<double> l5R1(0);
//std::vector<double> l5R2(0);
//std::vector<double> l6R1(0);
//std::vector<double> l6R2(0);
//std::vector<double> l1dR1(0);
//std::vector<double> l1dR2(0);
//std::vector<double> l2dR1(0);
//std::vector<double> l2dR2(0);
//std::vector<double> l3dR1(0);
//std::vector<double> l3dR2(0);
//std::vector<double> l4dR1(0);
//std::vector<double> l4dR2(0);
//std::vector<double> l5dR1(0);
//std::vector<double> l5dR2(0);
//std::vector<double> l6dR1(0);
//std::vector<double> l6dR2(0);
//std::vector<double> * layerstrip_r[12] ={&l1R1, &l1R2, &l2R1, &l2R2, &l3R1, &l3R2, &l4R1, &l4R2, &l5R1, &l5R2, &l6R1, &l6R2};
//std::vector<double> * layerstrip_dr[12] ={&l1dR1, &l1dR2, &l2dR1, &l2dR2, &l3dR1, &l3dR2, &l4dR1, &l4dR2, &l5dR1, &l5dR2, &l6dR1, &l6dR2};
q = 0;
std::vector<double> ch(0);
ich = 0;
if (chargefile.is_open()) {
     while (!chargefile.eof()){
         chargefile >> q;
         ch.push_back(q);
         ich += 1;
         }
     }
chargefile.close();


//Go through each current file WIP
for(int j = 0; j < n; j++) {
     ifstream currentfile;
     currentfile.open(dirnames.at(j) + ".txt");
     char title[100]; double imax = 0; double i0 = 0; double distat = 0; double disys = 0; double ditot = 0; int status;
     int ilinenum = 0;
     bool titlematched[12] = {false};
     while (!currentfile.eof()){
         if (ilinenum < 3) {ilinenum +=1; continue;}
         currentfile >> title >> imax >> i0 >> distat >> disys >> ditot >> status;
         for (int channelnum = 0; channelnum <12; channelnum++) {
             if (titlematched[ilinenum - 3]) {continue;}
             else if (title == layerstripstrlist[channelnum]) {
                 titlematched[ilinenum - 3] = true;
                 layerstrip_r->at(channelnum).push_back(300.0/TMath::Abs(i0));
                 layerstrip_dr->at(channelnum).push_back(300.0/TMath::Power(TMath::Abs(i0),2) * TMath::Abs(ditot));
                 }
             }
         ilinenum += 1;
         }
         for (int channelnum = 0; channelnum <12; channelnum++) {
            if (!titlematched[ilinenum]) {
                (layerstrip_r->at(channelnum)).push_back(-1);
                (layerstrip_dr->at(channelnum)).push_back(0);
                
                }
            }
     }
 
//   setTDRStyle();

   TCanvas *c1 = new TCanvas("me11RvC","A Simple Graph",10,10,700,500);
   c1->Divide(3,2);
//   TCanvas *c2 = new TCanvas("c2","A Simple Graph",10,10,700,500);
//   c2->Divide(2,2);
 

//   TString extraText   = "R1: Resist,ance between strip1 and strip2 of layer1";
//   TString extraText2   = "CSC ME1/1, R/R1 vs Dose";
//   TLatex latex;
//   latex.SetNDC();
//   latex.SetTextFont(42);
//   latex.SetTextColor(kBlack);

// get integrated charges from: http://pnpi-cms-l1.cern.ch:8080/CSCdose/
// these data are from sept 10, 2017 onwards
//double ch[n] = {0.28, 9.31, 21.59, 27.54, 31.38, 32.44, 34.84, 76.03, 97.65, 110.26, 121.71, 133.31, 151.31, 271.76, 282.48, 323.16, 371.21};

////I is the difference p0_300V - p0_0V
//double l1I1[n] = {753.384, 418.221, 606.075, 59.0782,42.9908, 97.7029, 15.4353, 484.413, 2956.56, 954.266, 1019.03, 1156.8, 1112.55, 1.51673, 1.51673, 4.4176, 0.753189};
////Systematic uncertainty in fit: difference between I obtained from fit and I obtained from average of last 100 points
////add errors in quadrature
//double l1dI1[n] = {8.27328, 0.493865, 5.77018, 4.17477, 3.91023, 4.06764, 7.93007, 5.12788, 3.07917, 11.2011, 12.2766, 19.0657, 208.039, 0.965083, 0.965083, 6.48287 ,10.6815};
//double l1R1[n], l1dR1[n];
//for(int i=0; i<n; i++){ l1R1[i] = 300.0/l1I1[i]; l1dR1[i] = l1R1[i] * l1dI1[i] / l1I1[i]; 						}

//double l1I2[n] = {645.014, 443.666, 626.007, 75.654, 44.4104, 116.468, 47.1175, 543.059, 2520.8, 898.795, 1085.22, 1127.29, 1243.9, 1.79979, 1.79979, 4.56577, 25.5065};
//double l1dI2[n] = {9.61797, 0.477274, 6.89056, 2.5727, 5.86982, 1.847, 6.01701, 6.3851, 30.0908, 8.76041, 33.8403, 32.2943, 36.8611, 3.28681, 3.28681, 6.67267, 16.2072};
//double l1R2[n], l1dR2[n];
//for(int i=0; i<n; i++){ l1R2[i] = 300.0/l1I2[i]; l1dR2[i] = l1R2[i] * l1dI2[i] / l1I2[i]; 						}

//double l2I1[n] = {830.274, 705.772, 774.185, 127.556, 91.428, 176.109, 33.769, 620.23, 2657.2, 963.228, 982.565, 1144.44, 867.887, 5.44631, 5.44631, 21.5351, 25.6536};
//double l2dI1[n] = {5.64593, 0.600856, 4.12977, 130.062, 3.90197, 5.17359, 3.77832, 39.1865, 0.976129, 42.5635, 12.1415, 44.3954, 43.0005, 3.39583, 3.39583, 14.6373, 16.2072};
//double l2R1[n], l2dR1[n];
//for(int i=0; i<n; i++){ l2R1[i] = 300.0/l2I1[i]; l2dR1[i] = l2R1[i] * l2dI1[i] / l2I1[i]; 						}

//double l2I2[n] = {984.29, 891.889, 837.267, 130.062, 57.879, 274.12, 55.0098, 603.493, 2795.71, 985.938, 1006.95, 1211.22, 1066, 1.33702, 1.33702, 16.083, 43.2245};
//double l2dI2[n] = {2.98183, 7.99278, 5.50193, 0.821996, 6.27973, 8.64202, 4.1072, 62.5986, 1.41264, 27.4198, 12.0508, 29.9167, 51.9108, 1.41527, 1.41527, 11.0, 11.0711 };
//double l2R2[n], l2dR2[n];
//for(int i=0; i<n; i++){ l2R2[i] = 300.0/l2I2[i]; l2dR2[i] = l2R2[i] * l2dI2[i] / l2I2[i]; 						}

//double l3I1[n] = {748.006, 662.907, 647.936, 172.737, 129.188, 174.169, 82.352, 543.769, 2805.32, 902.145, 1426.91, 1112.4, 1104.77, 17.8925, 17.8925, 28.8401, 163.41};
//double l3dI1[n] = {5.04452, 13.1403, 9.192, 5.54266, 3.96988, 5.89939, 7.70914, 14.9416, 9.48261, 60.4631, 44.5422, 29.3307, 43.9394, 5.37911, 5.37911, 12.8304, 7.58339};
//double l3R1[n], l3dR1[n];
//for(int i=0; i<n; i++){ l3R1[i] = 300.0/l3I1[i]; l3dR1[i] = l3R1[i] * l3dI1[i] / l3I1[i]; 						}

//double l3I2[n] = {1278.45, 968.257, 960.063, 211.882, 128.084, 270.468, 82.2385, 676.55, 2571.92, 811.649, 1664.89, 1122.61, 1066.82, 37.9974, 37.9974, 37.9974, 76.4354};
//double l3dI2[n] = {9.86347, 4.47059, 7.83072, 8.31893, 3.81357, 3.35587, 9.06439, 66.8107, 58.3963, 13.981, 38.1525, 18.8844, 36.0468, 27.3018, 27.3018, 27.3018, 25.7207};
//double l3R2[n], l3dR2[n];
//for(int i=0; i<n; i++){ l3R2[i] = 300.0/l3I2[i]; l3dR2[i] = l3R2[i] * l3dI2[i] / l3I2[i]; 						}

//double l4I1[n] = {1015.97, 1070.43, 966.642, 671.846, 715.607, 259.985, 279.538, 486.734, 2533.72, 787.718, 1428.98, 1025.65, 976.828, 0.0358992, 0.0358992,  0.0358992, 4.03998};
//double l4dI1[n] = {11.3784, 87.7802, 7.71406, 4.23883, 3.5705, 3.29101, 58.4248, 57.0645, 66.0779, 73.1981, 29.2329, 36.3346, 85.5429, 0, 0, 0, 3.15569};
//double l4R1[n], l4dR1[n];
//for(int i=0; i<n; i++){ l4R1[i] = 300.0/l4I1[i]; l4dR1[i] = l4R1[i] * l4dI1[i] / l4I1[i]; 						}

//double l4I2[n] = {1827.27, 1727.2, 1603.38, 1079, 1383.41, 220.34, 135.35, 511.282, 2628.76, 808.608, 2043.42, 987.397, 1014.91, .109952, .109952, 0.109952, 20.0297};
//double l4dI2[n] = {12.807, 7.48286, 8.57966, 0.949158, 9.1549, 6.54901, 7.15828, 63.1971, 51.921, 39.3841, 78.953, 35.4018, 51.3772, 0.0362742, 0.0362742, 0.0362742, 4.12381};
//double l4R2[n], l4dR2[n];
//for(int i=0; i<n; i++){ l4R2[i] = 300.0/l4I2[i]; l4dR2[i] = l4R2[i] * l4dI2[i] / l4I2[i]; 						}

//double l5I1[n] = {798.448, 722.844, 691.28, 285.903, 261.512, 202.076, 164.575, 497.383, 2407.3, 801.582, 1347.7, 1057.95, 1060.01, 41.7468, 41.7468, 41.7468, 199.137};
//double l5dI1[n] = {5.65986, 5.6266, 12.8704, 6.12553, 6.21402, 9.0245, 10.2345, 39.6446, 46.319, 70.6573, 100.07, 45.9663, 39.1183, 7.8364, 7.8364, 7.8364, 2.24654};
//double l5R1[n], l5dR1[n];
//for(int i=0; i<n; i++){ l5R1[i] = 300.0/l5I1[i]; l5dR1[i] = l5R1[i] * l5dI1[i] / l5I1[i]; 						}

//double l5I2[n] = {1152.62, 924.305, 876.389, 312.386, 261.353, 270.94, 159.928, 570.958, 2345.49, 941.234, 1464.21, 1127.41, 1055.38, 35.8635, 35.8635, 35.8635, 205.983};
//double l5dI2[n] = {15.1662, 8.19836, 5.56926, 3.03334, 3.32657, 6.49953, 11.6477, 67.5256, 37.6918, 36.0093, 108.661, 32.3762, 51.0821, 1.19728, 1.19728, 1.19728, 69.8911};
//double l5R2[n], l5dR2[n];
//for(int i=0; i<n; i++){ l5R2[i] = 300.0/l5I2[i]; l5dR2[i] = l5R2[i] * l5dI2[i] / l5I2[i]; 						}

//double l6I1[n] = {610.895, 493.575, 486.359, 178.992, 153.463, 141.035, 98.8689, 367.823, 2897.2, 799.869, 1310.09, 1329.46, 1197.25, 20.0559, 20.0559, 20.0559, 94.5718};
//double l6dI1[n] = {9.52592, 6.48149, 5.47521, 4.69237, 5.95875, 5.16116, 6.02588, 55.8165, 0.986366, 64.3301, 30.0406, 49.0517, 102.123, 4.66738, 4.66738, 4.66738, 38.5238};
//double l6R1[n], l6dR1[n];
//for(int i=0; i<n; i++){ l6R1[i] = 300.0/l6I1[i]; l6dR1[i] = l6R1[i] * l6dI1[i] / l6I1[i]; 						}

//double l6I2[n] = {644.582, 541.044, 508.782, 179.488, 158.563, 165.202, 100.654, 391.443, 2743.04, 820.733, 1194.08, 804.374, 1103.19, 213.599, 213.599, 213.599, 213.599};
//double l6dI2[n] = {6.23948, 6.23811, 10.9047, 7.78846, 3.74703, 5.62804, 4.21433, 40.5557, 1.11115, 36.4967, 102.525, 17.7675, 45.3946, 31.1555, 31.1555, 31.1555, 31.1555};
//double l6R2[n], l6dR2[n];
//for(int i=0; i<n; i++){ l6R2[i] = 300.0/l6I2[i]; l6dR2[i] = l6R2[i] * l6dI2[i] / l6I2[i]; 						}

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
   TGraph *gI61 = new TGraph(n61, ch61, l6I1);
   TGraph *gI62 = new TGraph(n62, ch62, l6I2);
*/
//   TGraph *gR1 = new TGraph(n11, ch11, R1);
//TGraphErrors *gR11 = new TGraphErrors(n, ch, l1R1,0, l1dR1);
TGraphErrors *gR11 = new TGraphErrors(n);
TGraphErrors *gR12 = new TGraphErrors(n);
TGraphErrors *gR21 = new TGraphErrors(n);
TGraphErrors *gR22 = new TGraphErrors(n);
TGraphErrors *gR31 = new TGraphErrors(n);
TGraphErrors *gR32 = new TGraphErrors(n);
TGraphErrors *gR41 = new TGraphErrors(n);
TGraphErrors *gR42 = new TGraphErrors(n);
TGraphErrors *gR51 = new TGraphErrors(n);
TGraphErrors *gR52 = new TGraphErrors(n);
TGraphErrors *gR61 = new TGraphErrors(n);
TGraphErrors *gR62 = new TGraphErrors(n);
for (unsigned int i=0; i<n; i++) {
    gr11->SetPoint(i, ch.at(i), l1R1.at(i));
    gr11->SetPointError(i, 0, l1dR1.at(i));
    gr12->SetPoint(i, ch.at(i), l1R2.at(i));
    gr12->SetPointError(i, 0, l1dR2.at(i));
    gr21->SetPoint(i, ch.at(i), l2R1.at(i));
    gr21->SetPointError(i, 0, l2dR1.at(i));
    gr22->SetPoint(i, ch.at(i), l2R1.at(i));
    gr22->SetPointError(i, 0, l2dR1.at(i));
    gr31->SetPoint(i, ch.at(i), l3R1.at(i));
    gr31->SetPointError(i, 0, l1dR1.at(i));
    gr32->SetPoint(i, ch.at(i), l1R1.at(i));
    gr32->SetPointError(i, 0, l1dR1.at(i));
    gr41->SetPoint(i, ch.at(i), l1R1.at(i));
    gr41->SetPointError(i, 0, l1dR1.at(i));
    gr42->SetPoint(i, ch.at(i), l1R1.at(i));
    gr42->SetPointError(i, 0, l1dR1.at(i));
    gr51->SetPoint(i, ch.at(i), l1R1.at(i));
    gr51->SetPointError(i, 0, l1dR1.at(i));
    gr52->SetPoint(i, ch.at(i), l1R1.at(i));
    gr52->SetPointError(i, 0, l1dR1.at(i));
    gr61->SetPoint(i, ch.at(i), l1R1.at(i));
    gr61->SetPointError(i, 0, l1dR1.at(i));
    gr62->SetPoint(i, ch.at(i), l1R1.at(i));
    gr62->SetPointError(i, 0, l1dR1.at(i));

    }

/*
   c1->cd(1);
   gI11->SetTitle("layer1; Accumulated charge [mC/cm]; I [pA]");
   gI11->SetMarkerColor(kRed);
   gI11->SetMinimum(0.05);
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
   gI22->SetMinimum(0.05);
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
   gI31->SetMinimum(0.05);
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
   gI41->SetMinimum(0.05);
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
   gI51->SetMinimum(0.05);
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
   gI61->SetMinimum(0.05);
   gI61->SetMaximum(3500);
   gI61->SetMarkerColor(kRed);
   gI61->SetMarkerStyle(22);
   gI61->Draw("ALP");
   gI62->SetMarkerColor(kGreen+3);
   gI62->SetMarkerStyle(24);
   gI62->Draw("LP same");
*/
/*
   c1->cd(1);   gPad->SetLogy();
   gR1->SetTitle("layer1; Accumulated charge [mC/cm]; R [T#Omega]");
   gR1->SetMinimum(0.1.001);
   gR1->SetMaximum(100000);
   gR1->SetMarkerColor(kRed);
   gR1->SetMarkerStyle(22);
   gR1->Draw("ALP");
*/
   c1->cd(1);   gPad->SetLogy();
   gR11->SetTitle("layer1; Accumulated charge [mC/cm]; R [T#Omega]");
   gR11->SetMinimum(0.05);
   gR11->SetMaximum(100);
   gR11->SetMarkerColor(kGreen+3);
   gR11->SetMarkerStyle(24);
   gR11->Draw("AP");
   gR12->SetMarkerColor(kRed);
   gR12->SetMarkerStyle(22);
   gR12->Draw("P same");
//   c1->cd(1);
//   latex.DrawLatex(0.15, 0.4, extraText);
//   latex.DrawLatex(0.15, 0.5, extraText2);
   TLegend *leg1 = new TLegend(0.18, 0.58 ,0.48, 0.88);
   leg1->AddEntry(gR11, "strips 1&2", "p");
   leg1->AddEntry(gR12, "strips 2&3", "p");
   leg1->Draw();

   c1->cd(2);   gPad->SetLogy();
   gR21->SetTitle("layer2; Accumulated charge [mC/cm]; R [T#Omega]");
   gR21->SetMinimum(0.05);
   gR21->SetMaximum(100);
   gR21->SetMarkerColor(kRed);
   gR21->SetMarkerStyle(22);
   gR21->Draw("AP");
   gR22->SetMarkerColor(kGreen+3);
   gR22->SetMarkerStyle(24);
   gR22->Draw("P same");

   c1->cd(3);   gPad->SetLogy();
   gR31->SetTitle("layer3; Accumulated charge [mC/cm]; R [T#Omega]");
   gR31->SetMinimum(0.05);
   gR31->SetMaximum(100);
   gR31->SetMarkerColor(kRed);
   gR31->SetMarkerStyle(22);
   gR31->Draw("AP");
   gR32->SetMarkerColor(kGreen+3);
   gR32->SetMarkerStyle(24);
   gR32->Draw("P same");

   c1->cd(4);   gPad->SetLogy();
   gR42->SetTitle("layer4; Accumulated charge [mC/cm]; R [T#Omega]");
   gR42->SetMinimum(0.05);
   gR42->SetMaximum(100);
   gR42->SetMarkerColor(kGreen+3);
   gR42->SetMarkerStyle(24);
   gR42->Draw("AP");
   gR41->SetMarkerColor(kRed);
   gR41->SetMarkerStyle(22);
   gR41->Draw("P same");

   c1->cd(5);   gPad->SetLogy();
   gR52->SetTitle("layer5; Accumulated charge [mC/cm]; R [T#Omega]");
   gR52->SetMinimum(0.05);
   gR52->SetMaximum(100);
   gR52->SetMarkerColor(kGreen+3);
   gR52->SetMarkerStyle(24);
   gR52->Draw("AP");
   gR51->SetMarkerColor(kRed);
   gR51->SetMarkerStyle(22);
   gR51->Draw("P same");

   c1->cd(6);   gPad->SetLogy();
   gR61->SetTitle("layer6; Accumulated charge [mC/cm]; R [T#Omega]");
   gR61->SetMinimum(0.05);
   gR61->SetMaximum(100);
   gR61->SetMarkerColor(kRed);
   gR61->SetMarkerStyle(22);
   gR61->Draw("AP");
   gR62->SetMarkerColor(kGreen+3);
   gR62->SetMarkerStyle(24);
   gR62->Draw("P same");


//c1->SaveAs("me11I.root");  
c1->SaveAs("me11RvC.pdf");
}
