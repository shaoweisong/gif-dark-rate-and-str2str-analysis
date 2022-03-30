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
//#include "tdrstyle_mod.C"
#include <iostream>
#include <fstream>

void setT0(bool& startSeria, int& t0, int& t){
    if(startSeria){
        t0 = t;
        startSeria=false;
    };
    t-=t0;
}

// The number of final trailing data points over which the mean is taken (since for large t, time dependance decreases we are effectively estimating that the final 35 points are time independant, taking the mean, and comparing that to what the asymptote of our fit looks like)
const int n4mean = 35;
// Last points subtracted off due to crazy behavior at the end
const int lastPoints = 15;
//const int lastPoints = 0;
// excluding the first 5 points to account for eccentric nonlinear behavior at time of switch on or off of HV (results in much better fit convergence)
// Set to 10 points - ramping behavior very close to changing voltage are less of interest to us than asymptotic behavior
const int firstPoints = 5;
//const int firstPoints = 0;
double frMin = 100;
double frMax = 1000;

bool err[12] = {true};
bool canverr[6] = {true};

//Plot potential over time data

TGraphErrors * createGraph(std::vector<int> troot, std::vector<double> current, TString * title, double& mean, double& rms, bool& isErr){
    int nX = troot.size();
    int nY = current.size();
    TGraphErrors * g = new TGraphErrors(nX-lastPoints-firstPoints);
    if( (nX == nY) && (nX>=n4mean) ){
        int ii = nX-n4mean-lastPoints;
        //std::cout << title->Data() << " From vector of points:" << std::endl;
        //to prevent memory leaking we are trying to make sure our graph doesn't have any more points than needed (i.e. not having potentially empty points for firstpoints and lastpoints)
        g->SetTitle(title->Data());
        g->GetXaxis()->SetTitle("Time (s)");
        g->GetXaxis()->SetTitleSize(0.03);
        g->GetXaxis()->SetTitleOffset(1);
        g->GetYaxis()->SetTitle("I (pA)");
        g->GetYaxis()->SetTitleSize(0.04);
        g->GetYaxis()->SetTitleOffset(0.8);
        //std::cout << "data size x,y = " << nX << ", " << nY << std::endl; 
        for (unsigned int i=firstPoints; i<nX-lastPoints; i++){
            if (troot.at(i) < 0 or troot.at(i) > 10000) {continue;}
            //std::cout << i << " " << troot->at(i) << " " << current->at(i) << std::endl;
            g->SetPoint(i-firstPoints, troot.at(i), current.at(i));
            g->SetPointError(i-firstPoints, 1, 0.1); // error on current - 0.1 pA
            if(i>=ii){
              mean+=current.at(i);  
            };
        };
        //std::cout << g->GetTitle() << " Written to graph:" << std::endl;
        //for (unsigned int i=0; i<nX-lastPoints-firstPoints; i++) {
        //    std::cout << i << " " << g->GetX()[i] << " " << g->GetY()[i] << std::endl;
        //    }
        mean/=n4mean;
        rms = 0;
        for (unsigned int i=ii; i<nX-lastPoints; i++){
            double d=current.at(i)-mean;
            //std::cout << i << "\t" << d << "\t" << current->at(i) << std::endl;
            rms+=d*d;
        };rms = TMath::Sqrt(rms);
    }else{
        std::cout << "different sizes of X and Y vectors, or too few points; don't know what to do... Data:  " << title << std::endl;
        isErr = false;
    };
    return g;
};

float ave(std::vector<double> vec){
    float tmp = 0;
    for(int i=0; i<vec.size(); i++) 
        tmp += vec[i];
    return tmp/vec.size();
}

void plotWithoutFit(const char * dirnameChar, const char * fnameTChar="ClosedCircuit_ShortCables_WithBox_0-300V_", const char * ext=".txt"){
   //setTDRStyle();
   //gROOT->ProcessLine(".L ./tdrstyle.C");
   //gROOT->ProcessLine("setTDRStyle()");
   gStyle->SetOptFit(1);
   gStyle->SetOptTitle(1);
   gStyle->SetTitleSize(10);
   //gStyle->SetPadRightMargin(0.01);
   //gStyle->SetPadLeftMargin(0.01);
   //gStyle->SetLineWidth(2);
   TString dirname = TString(dirnameChar);   
   TString filename = TString(fnameTChar);
   ifstream myfile;
    //ofile is essentially a log file of the fitting process which stores some fit parameters including most importantly  the constant offset of the fit, which is to say the baseline current between the two strips
   ofstream ofile(dirname+".txt");
   TString pdfFName = dirname+".pdf";
   ////saving output canvases to a root file to more easily see their format params
   //TString rootFName = dirname+".root";
   dirname+="/";
   TString suffix[12] = {"layer1_strips12", "layer1_strips23", "layer2_strips12", "layer2_strips23", "layer3_strips12", "layer3_strips23", "layer4_strips12", "layer4_strips23", "layer5_strips12", "layer5_strips23", "layer6_strips12", "layer6_strips23"};
    TGraphErrors * dataGr[12];
    //Create 6 TCanvases in a vector
    TCanvas * canv[6];
    std::cout << dirname << std::endl;
    ofile << "Effective N of Points" << "\t" << "frMin" << "frMax" << "\n";
    ofile << n4mean-lastPoints << "\t" << frMin << "\t" << frMax << "\n";
    ofile << "Title" << "\t" << "I_max" << "\t" << "I_meas" << "\t" << "dI_stat" << "\t" << "dI_sys" << "\t" << "dI_tot" << "\t" << "status" <<  "\n";
    for(int j = 0; j < 12 ; j++) {
        //if (j == 2) {break;}
    //Generate Canvases for each Layer
        int canvN = j/2;
        int padN  = 1;
        if(canvN*2==j){
            TString title = "Layer "; title+=canvN+1;
            canv[canvN] = new TCanvas(title.Data(),title.Data(),1000,1000);
            canv[canvN]->Divide(1,2);
        }else{
          padN=2;  
        };
        myfile.open(dirname+filename+suffix[j]+TString(ext));
        double data_points = - 999;
        double voltage= -1;
        // Read in the data
        std::vector<int> vX(0);
        std::vector<double> vY(0);
        char str1[100];
        char str2[100];
        char str3[100];

        int i=0, max_1 =0, max_2=0 ;
        bool startSeria = true;
        int t0          = 0;
        int q1 = 0;
        int q2 = 0;

        if (myfile.is_open()){                        
            //each column of input data becomes a vector
            //splitting datasets into 0V (X/Y1 beginning & 2 end) and 300V (X/Y_300)
            while (!myfile.eof()){
                myfile >>str1>>str2>>str3>>voltage>> data_points;
                TString tmps = str2; tmps+=" "; tmps+=str3;
                int t = TDatime(tmps.Data()).Convert();
                data_points*=1e12;//pA
                // issue where this code is double filling some points, this is a quickfix
                setT0(startSeria, t0, t);
                if ( vX.size() < 1 ) {
                    vX.push_back(t);
                    vY.push_back(data_points);
                    }
                else if ( t != vX.at(vX.size()-1) ) {
                    vX.push_back(t);
                    vY.push_back(data_points);
                    }
                };
            };
            myfile.close();          

            double mean = 0;
            double rms = 0;     
            //we are only interested in measurements for which both a 0 and a 300 was taken
            // if there is no 0V data for the charge down period check in the pre 300V period just in case
            if (vX.size() == 0) {err[j] = true; continue;}
            // find current at final time
            double xmax = vX.at(vX.size()-1);
            
            TString voltinfo;
            TString plottitle;
            //plot data
            plottitle = suffix[j] + voltinfo;
            std::cout << plottitle << std::endl;
            // the i-1 is here because we are not plotting the 0V windup, so for mean and graph 0 is 0v and 1 is 300v
            dataGr[j] = createGraph(vX, vY, &plottitle, mean, rms, err[j]);                        
            //draw canvas
            canv[canvN]->cd(padN);
            dataGr[j]->SetMarkerStyle(20);
            dataGr[j]->SetMarkerColor(4);                
            // A - Without Axis, P - draw current marker at each bin except empty bins
            dataGr[j]->Draw("AP");

        };  

    for(int canvN=0; canvN<6; canvN++){
            if(canvN==0){
                canv[canvN]->Print(pdfFName+"(","pdf");
            }else if (canvN==5){
                canv[canvN]->Print(pdfFName+")","pdf");
            }else{
                canv[canvN]->Print(pdfFName,"pdf");
            };
            //canv[canvN]->Close();
    }
    cout << "Canvases saved to output pdf file" << endl;
    ofile.close();

}
