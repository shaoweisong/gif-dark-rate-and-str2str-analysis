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
//fit with Positive parameters current over time
TF1 * fit(TGraphErrors * graph, double mean, int& status){    
    double maxX, maxY;
    double minX, minY;
    graph->GetPoint(graph->GetN()-1, maxX, maxY);
    graph->GetPoint(0, minX, minY);
    //TF1 * ff = new TF1("ff","[0]+[1]*exp(x*[2])+[3]*exp(x*[4])+[5]*exp(x*[6])", 100, maxX*0.5);
    TF1 * f1 = new TF1("f1","[0]+[1]*exp(x*[2])+[3]*exp(x*[4])", minX, maxX);
    //std::cout << graph->GetTitle() << " " << mean << std::endl;
    ///TBD all par inivalues and limits to be written in out file
    //Explanation of Status return values here:https://root.cern/doc/master/classTGraph.html#aa978c8ee0162e661eae795f6f3a35589
    //and here: https://root.cern/doc/master/classTMinuit.html#ab48dd4b48800edc090396e35cb465fb9
    //0 means fit ok
    //1-3 means command blank, unreadable, or unknown
    //4 means abnormal termination (i.e. from MIGRAD not converged)
    //or, migrad in the 0's place: 0 means ok, 1 - covariance was made positive defined
    //2 - hesse is invalid, 3 - edm is above max, 4 - reached call limit, 5 - other
    //minos in the tens place: 0 - ok, 1 - invalid lower error, 2 - invalid upper error, 4 - invalid because maximum number of function calls exceeded, 8 - a new minimum found, 16 - error is truncated because parameter is at lower/upper limit
    //hesse in the hundreds place: 1 - hesse failed, 2 - matrix inversion failed, 3 - matrix not positive defined
    //thousands place - not used, from IMPROVE command of TMinuit (use "M" in the fit)
    f1->SetParameter(0,mean);
    f1->SetParLimits(0, 0.01*mean, 10*mean);
    f1->SetParameter(1,100);
    f1->SetParLimits(1, 0, 100000);
    f1->SetParameter(2,-0.01);                        
    f1->SetParLimits(2, -100, 0);
    f1->SetParameter(3,10);
    f1->SetParLimits(3, 0, 100000);
    f1->SetParameter(4,-0.001);
    f1->SetParLimits(4, -100, 0);
    //f1->SetParameter(5,0.1);
    //f1->SetParLimits(3, 0, 100)
    //f1->SetParameter(6,-0.1);
    //f1->SetParLimits(4, -10, 0)
    f1->SetLineColor(2);
    // S- return result as TFitResultPtr, R - Use the range specified in the function range, E - Perform better error estimation using minos technique, Q - Quiet Mode (minimum printing)
    status = graph->Fit(f1,"SREQ");
    return f1;
};

//fit with negative parameters potential over time
TF1 * nfit(TGraphErrors * graph, double mean, int& status){
    double maxX, maxY;
    double minX, minY;
    graph->GetPoint(graph->GetN()-1, maxX, maxY);
    graph->GetPoint(0, minX, minY);
    TF1 * f2 = new TF1("f2","[0]+[1]*exp(x*[2])+[3]*exp(x*[4])", minX, maxX);
    f2->SetParameter(0,mean);
    f2->SetParLimits(0, 0.01*mean, 10*mean);
    f2->SetParameter(1,-100);
    f2->SetParLimits(1, -100000, 0);
    f2->SetParameter(2,-0.01);
    f2->SetParLimits(2, -100, 0);
    f2->SetParameter(3,-10);
    f2->SetParLimits(3, -100000, 0);
    f2->SetParameter(4,-0.001);
    f2->SetParLimits(4, -100, 0);
    f2->SetLineColor(2);
    status = graph->Fit(f2,"SREQ");
    return f2;
};

//Plot potential over time data

TGraphErrors * createGraph(std::vector<int> * troot, std::vector<double> * current, TString * title, double& mean, double& rms, bool& isErr){
    int nX = troot->size();
    int nY = current->size();
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
            if (troot->at(i) < 0 or troot->at(i) > 10000) {continue;}
            //std::cout << i << " " << troot->at(i) << " " << current->at(i) << std::endl;
            g->SetPoint(i-firstPoints, troot->at(i), current->at(i));
            g->SetPointError(i-firstPoints, 1, 0.1); // error on current - 0.1 pA
            if(i>=ii){
              mean+=current->at(i);  
            };
        };
        //std::cout << g->GetTitle() << " Written to graph:" << std::endl;
        //for (unsigned int i=0; i<nX-lastPoints-firstPoints; i++) {
        //    std::cout << i << " " << g->GetX()[i] << " " << g->GetY()[i] << std::endl;
        //    }
        mean/=n4mean;
        rms = 0;
        for (unsigned int i=ii; i<nX-lastPoints; i++){
            double d=current->at(i)-mean;
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

void test_plot(const char * dirnameChar, const char * fnameTChar="ClosedCircuit_ShortCables_WithBox_0-300V_", const char * ext=".txt"){
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
    TGraphErrors * dataGr[12][2];
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
            canv[canvN]->Divide(2,2);
        }else{
          padN=3;  
        };
        myfile.open(dirname+filename+suffix[j]+TString(ext));
        double data_points = - 999;
        double voltage= -1;
        //0 V beginning
        std::vector<int> vecX1(0);
        std::vector<double> vecY1(0);
        //300 V
        std::vector<int> vecX_300(0);
        std::vector<double> vecY_300(0);
        //0 V end
        std::vector<int> vecX2(0);
        std::vector<double> vecY2(0);
        std::vector<int> * vX[3]    = {&vecX1, &vecX2, &vecX_300};
        std::vector<double> * vY[3] = {&vecY1, &vecY2, &vecY_300};
        char str1[100];
        char str2[100];
        char str3[100];

        int i=0, max_1 =0, max_2=0 ;
        bool beginning = true;
        bool startSeria[3] = {true, true, true};
        int t0[3]          = {0,    0,    0};
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
                if (voltage==0){
                    if (beginning){
                        // issue where this code is double filling some points, this is a quickfix
                        setT0(startSeria[0], t0[0], t);
                        if ( vecX1.size() < 1 ) {
                            vecX1.push_back(t);
                            vecY1.push_back(data_points);
                            }
                        else if ( t != vecX1.at(vecX1.size()-1) ) {
                            vecX1.push_back(t);
                            vecY1.push_back(data_points);
                            }
                    }else{
                        // issue where this code is double filling some points, this is a quickfix
                        setT0(startSeria[1], t0[1], t);
                        if ( vecX2.size() < 1 ) {
                            vecX2.push_back(t);
                            vecY2.push_back(data_points);
                            }
                        else if ( t != vecX2.at(vecX2.size()-1) ) {
                            vecX2.push_back(t);
                            vecY2.push_back(data_points);                        
                            }
                    }
                } else if (voltage==300){
                    beginning = false;
                    // issue where this code is double filling some points, this is a quickfix
                    setT0(startSeria[2], t0[2], t);
                    if ( vecX_300.size() < 1 ) {
                        vecX_300.push_back(t);
                        vecY_300.push_back(data_points);
                        }
                    else if ( t != vecX_300.at(vecX_300.size()-1) ) {
                        vecX_300.push_back(t);
                        vecY_300.push_back(data_points);         
                        }
                };
            };
            myfile.close();          

            double mean[2] = {0,0};
            double rms[2]  = {0,0};     
            //we are only interested in measurements for which both a 0 and a 300 was taken
            // if there is no 0V data for the charge down period check in the pre 300V period just in case
            if (vX[2]->size() == 0) {err[j] = true; continue;}
            if (vX[1]->size() == 0) {vX[1] = vX[0];}
            if (vX[1]->size() == 0) {err[j] = true; continue;}
            // find current at final time
            double xmax = vX[2]->at(vX[2]->size()-1);
            
            TString voltinfo;
            TString plottitle;
            //plot data
            for(int i = 1; i<3; i++){
                if (i==1) {voltinfo= "_0V";} else {voltinfo="_300V";};
                plottitle = suffix[j] + voltinfo;
                std::cout << plottitle << std::endl;
                // the i-1 is here because we are not plotting the 0V windup, so for mean and graph 0 is 0v and 1 is 300v
                dataGr[j][i-1] = createGraph(vX[i], vY[i], &plottitle, mean[i-1], rms[i-1], err[j]);                        
            };
            //draw canvas
            canv[canvN]->cd(padN);
            dataGr[j][0]->SetMarkerStyle(20);
            dataGr[j][0]->SetMarkerColor(4);                
            // A - Without Axis, P - draw current marker at each bin except empty bins
            dataGr[j][0]->Draw("AP");

            int status=-1;
            //exponential decay fit on 0v
            TF1 *nf = nfit(dataGr[j][0],mean[0],status);
            nf->Draw("sames");
            double I0;
            if ( status == 0 ) {
                I0 = nf->GetParameter(0);
                }
            else {I0 = mean[0];}

            ////////////////
            
            //exponential growth fit on 300v
            canv[canvN]->cd(padN+1);
            dataGr[j][1]->Draw("AP");
            
            status=-1;
            TF1 *ff = fit(dataGr[j][1],mean[1],status);
            double I300;
            if ( status == 0 ) {
                I300 = ff->GetParameter(0);
                }
            else {I300 = mean[1];}
            ff->Draw("sames");
            
            std::cout << "name, mean, and normalized RMS: " << dataGr[j][1]->GetTitle() << "\t"<< xmax << "\t\t" << mean[1] << " " << rms[1]/TMath::Sqrt(n4mean) << "\t"<<std::endl;
            std::cout << "Fit status, final measured current, and error: " << status << "\t" << I300 - I0<< " " << ff->GetParError(0) << std::endl;
            // Title, I_max, I_meas, dI_fitStat, dI_fitSys, dI_tot, fit status
            ofile << dataGr[j][1]->GetTitle() << "\t" << xmax << "\t" << I300-I0 << "\t" << ff->GetParError(0) << "\t" << I300 -I0 - (mean[1] - mean[0])  << "\t" << TMath::Sqrt(TMath::Power(I300-I0 - (mean[1] - mean[0]), 2) + TMath::Power(ff->GetParError(0), 2)+ TMath::Power(nf->GetParError(0), 2))  << '\t' << status  << "\n";



        }else{
                std::cout << "can't open file " << (dirname+filename+suffix[j]+TString(ext)) << std::endl;            
                err[j] = true;
        };  
    }

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
