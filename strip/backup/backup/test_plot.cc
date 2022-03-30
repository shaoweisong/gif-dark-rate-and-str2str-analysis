//#include "TROOT.h"
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

const int n4mean = 35;
const int lastPoints = 10;
double frMin = 100;
double frMax = 1000;
TF1 * fit(TGraphErrors * graph, double mean, int& status){    
    double maxX, maxY;
    graph->GetPoint(graph->GetN()-1, maxX, maxY);
    //TF1 * ff = new TF1("ff","[0]+[1]*exp(x*[2])+[3]*exp(x*[4])+[5]*exp(x*[6])", 100, maxX*0.5);
    TF1 * ff = new TF1("ff","[0]+[1]*exp(x*[2])+[3]*exp(x*[4])",frMin, frMax);
    //std::cout << graph->GetTitle() << " " << mean << std::endl;
    ///TBD all par inivalues and limits to be written in out file
    ff->SetParameter(0,mean);
    ff->SetParLimits(0, 0.01*mean, 10*mean);
    ff->SetParameter(1,100);
    ff->SetParLimits(1, 0, 100000);
    ff->SetParameter(2,-0.01);                        
    ff->SetParLimits(2, -100, 0);
    ff->SetParameter(3,10);
    ff->SetParLimits(3, 0, 100000);
    ff->SetParameter(4,-0.001);
    ff->SetParLimits(4, -100, 0);
    //ff->SetParameter(5,0.1);
    //ff->SetParLimits(3, 0, 100)
    //ff->SetParameter(6,-0.1);
    //ff->SetParLimits(4, -10, 0)
    ff->SetLineColor(4);
    status = graph->Fit(ff,"SREQ");
    return ff;
};

TGraphErrors * createGraph(std::vector<int> * troot, std::vector<double> * current, TString * title, double& mean, double& rms){
    TGraphErrors * g = new TGraphErrors();
    g->SetTitle(title->Data());
    int nX = troot->size();
    int nY = current->size();
    //std::cout << "data size x,y = " << nX << ", " << nY << std::endl; 
    if( (nX == nY) && (nX>=n4mean) ){
        mean = 0;
        int ii = nX-n4mean-lastPoints;
        for (unsigned int i=0; i<nX-lastPoints; i++){
            g->SetPoint(i, troot->at(i), current->at(i));
            g->SetPointError(i, 1, 10); // error on current - 10 pA
            if(i>=ii){
              mean+=current->at(i);  
            };
        };
        mean/=n4mean;
        rms = 0;
        for (unsigned int i=ii; i<nX-lastPoints; i++){
            double d=current->at(i)-mean;
            //std::cout << i << "\t" << d << "\t" << current->at(i) << std::endl;
            rms+=d*d;
        };rms = TMath::Sqrt(rms);
    }else{
        std::cout << "different sizes of X and Y vectors, or too few points; don't know what to do... Data:  " << title << std::endl;
    };
    return g;
};


void test_plot(const char * dirnameChar, const char * fnameTChar, const char * ext){
   //setTDRStyle();
   //gROOT->ProcessLine(".L ./tdrstyle.C");
   //gROOT->ProcessLine("setTDRStyle()");
   gStyle->SetOptFit(1);
   //gStyle->SetPadRightMargin(0.01);
   //gStyle->SetPadLeftMargin(0.01);
   //gStyle->SetLineWidth(2);
   TString dirname = TString(dirnameChar);   
   TString filename = TString(fnameTChar);
   TString fileform = TString(ext);
   ifstream myfile;
   ofstream ofile(dirname+"_new.txt");
   TString pdfFName = dirname+"_new.pdf";
   dirname+="/";
   TString suffix[10] = {"layer1_strips12", "layer1_strips23", "layer2_strips12", "layer2_strips23", "layer3_strips12", "layer3_strips23", "layer4_strips12", "layer4_strips23", "layer5_strips12", "layer5_strips23"};
    TGraphErrors * dataGr[10][3];
    TCanvas * canv[5];
    std::cout << dirname << std::endl;
    ofile << n4mean-lastPoints << "\t" << frMin << "\t" << frMax << "\n";
    for(int j = 0; j < 10 ; j++) {
        int canvN = j/2;
        int padN  = 1;
        if(canvN*2==j){
            TString title = "canv["; title+=canvN; title+="]";
            canv[canvN] = new TCanvas(title.Data(),title.Data(),1000,1000);
            canv[canvN]->Divide(2,2);
        }else{
          padN=3;  
        };
        myfile.open(dirname+filename+suffix[j]+fileform);
        double data_points = - 999;
        double voltage= -1;
        std::vector<int> vecX1(0);
        std::vector<double> vecY1(0);
        std::vector<int> vecX_300(0);
        std::vector<double> vecY_300(0);
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
        if (myfile.is_open()){                        
            while (!myfile.eof()){
                myfile >>str1>>str2>>str3>>voltage>> data_points;
                //!!! TBD - check channels here (str1)
                TString tmps = str2; tmps+=" "; tmps+=str3;
                int t = TDatime(tmps.Data()).Convert();
                //std::cout << tmps << " => " << t << " => ";
                data_points*=1e12;//pA
                //std::cout << data_points << std::endl;
                if (voltage==0){
                    if (beginning){
                        setT0(startSeria[0], t0[0], t);
                        vecX1.push_back(t);
                        vecY1.push_back(data_points);
                    }else{
                        setT0(startSeria[1], t0[1], t);                        
                        vecX2.push_back(t);
                        vecY2.push_back(data_points);                        
                    }
                } else if (voltage==300){
                    beginning = false;
                    setT0(startSeria[2], t0[2], t);
                    vecX_300.push_back(t);
                    vecY_300.push_back(data_points);         
                };
                //std::cout << t << std::endl;                
            };
            /*
            if(vecX2.size()>0 && vecY2.size()>0){
              vecX2.pop_back();
              vecY2.pop_back();
            };
            */
            myfile.close();          

            double mean[3] = {0,0,0};
            double rms[3]  = {0,0,0};     
            double xmax = vX[2]->at(vX[2]->size()-1);
            for(int i = 0; i<3; i++){
                dataGr[j][i] = createGraph(vX[i], vY[i], &suffix[j], mean[i], rms[i]);                        
            };
            canv[canvN]->cd(padN);
            //!!!TBD - histo of standard min-max
            for(int i=0; i<3; i++){
                if(i!=1){
                    dataGr[j][0]->SetMarkerStyle(20);
                    dataGr[j][0]->SetMarkerColor(1);
                }else{
                    dataGr[j][1]->SetMarkerStyle(20);
                    dataGr[j][1]->SetMarkerColor(4);                
                };
            };
            dataGr[j][1]->Draw("AP");
            dataGr[j][0]->Draw("Psames");
            
            canv[canvN]->cd(padN+1);
            dataGr[j][2]->Draw("AP");
            
            int status=-1;
            TF1 *ff =fit(dataGr[j][2],mean[2],status);
            TF1 *ff1 = new TF1("ff1","[0]+[1]*exp(x*[2])+[3]*exp(x*[4])",0, 1500);
            for( int i=0; i<5; i++)
                ff1->SetParameter(i,ff->GetParameter(i));
            ff1->Draw("sames");
            
            std::cout << dataGr[j][2]->GetTitle() << "\t"<< xmax << "\t\t" << mean[2] << " " << rms[2]/TMath::Sqrt(n4mean) << "\t";
            std::cout << status << "\t" << ff->GetParameter(0) << " " << ff->GetParError(0) << std::endl;
            ofile << dataGr[j][2]->GetTitle() << "\t"<< xmax << "\t\t" << mean[2] << " " << rms[2]/TMath::Sqrt(n4mean-lastPoints) << "\t";
            ofile << status << "\t" << ff->GetParameter(0) << " " << ff->GetParError(0) << "\n";
            
        }else{
                std::cout << "can't open file " << (dirname+filename+suffix[j]) << std::endl;            
        };  
        
        
     /* 
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
   
   return;
   */
    }
    for(int canvN=0; canvN<5; canvN++){
            if(canvN==0){
                canv[canvN]->Print(pdfFName+"(","pdf");
            }else if (canvN==4){
                canv[canvN]->Print(pdfFName+")","pdf");
            }else{
                canv[canvN]->Print(pdfFName,"pdf");
            };
    }
    ofile.close(); 
    
}

