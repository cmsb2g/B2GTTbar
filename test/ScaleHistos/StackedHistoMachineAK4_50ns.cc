#include <TH1F.h>
#include <TH2F.h>
#include <iostream>
#include <ctime>
#include <string>
#include "TFile.h"
#include "TBranch.h"
#include "TTree.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TString.h"
#include "TFrame.h"
#include "THStack.h"
#include "TColor.h"
using namespace std;

// SEARCH
//'change with histo' :to find differences btw each plot


void callHistos();
void StackedHistoMachineAK4_50ns();
void plotter( TString Histo );

TString xxx;
TString CalledHisto;

void StackedHistoMachineAK4_50ns(){
    callHistos ();
}

void callHistos ( ){  
    cout << "Histogram to plot: 'h_'+ X where options are:  h_mAK4, h_ptAK4, h_bdiscAK4, h_ptLep. (e.g. I want h_mAK4 so I enter mAK4 etc...) " << endl;  
    cin >> xxx ;
    CalledHisto = "h_"+xxx;
    cout << CalledHisto << endl;
    plotter( CalledHisto );
}

void plotter(TString Histo){


TString xAxisTitle;  
int minX;
int maxX;
double xInfo;
double yInfoTop;
double legendLocation [4];

/*
    TString xAxisTitle = "M_{jet}\0(GeV)"; 
        minX = 10;
        maxX = 550; 
               xInfo = 0.301; //  location of plot description in normalized coordinates
               yInfoTop = 0.868;
    double legendLocation [4] = {0.440759, 0.320595, 0.750536, 0.611488 }; // {x1, y1, x2, y2} location of legend in normalized coordinates
*/
int histo = 0;

if (Histo == "h_mAK4")
	histo =1;

if (Histo == "h_ptAK4")
	histo =2;

if (Histo == "h_bdiscAK4")
	histo =3;

if (Histo == "h_ptLep")
	histo =4;

switch (histo)
{
    case 1 :{
    xAxisTitle = "M_{jet} (GeV)"; 
    minX = 0;
    maxX = 80; 
    xInfo = 0.301; //  location of plot description in normalized coordinates
    yInfoTop = 0.868;
    legendLocation[0] = 0.38058;
    legendLocation[1] = 0.377976;
    legendLocation[2] = 0.700893;
    legendLocation[3] = 0.668155;
    cout << "This histo is h_mAK4 " << endl;
  //  return xAxisTitle, minX, maxX, xInfo, yInfoTop, legendLocation [4];
    break;
    }
    case 2 :{ 
    xAxisTitle = "P_{T} of Jet (GeV)"; 
    minX = 0;
    maxX = 240; 
    xInfo = 0.251; //  location of plot description in normalized coordinates
    yInfoTop = 0.868;
    legendLocation[0] = 0.370759;
    legendLocation[1] = 0.320595;
    legendLocation[2] = 0.650536;
    legendLocation[3] = 0.611488;
    cout << "This histo is h_ptAK4 " << endl;
    break;
    }
    case 3 :{
    xAxisTitle = "B Discriminator";
    minX = 0;
    maxX = 1; 
    xInfo = 0.341; //  location of plot description in normalized coordinates
    yInfoTop = 0.868;
    legendLocation[0] = 0.520759;
    legendLocation[1] = 0.650595;
    legendLocation[2] = 0.870536;
    legendLocation[3] = 0.851488;
    break;
    }
    case 4 :{
    xAxisTitle = "P_{T} of Lepton (GeV)";
    minX = 0;
    maxX = 200; 
    xInfo = 0.341; //  location of plot description in normalized coordinates
    yInfoTop = 0.868;
    legendLocation[0] = 0.520759;
    legendLocation[1] = 0.650595;
    legendLocation[2] = 0.870536;
    legendLocation[3] = 0.851488;
    break;
    }
    case 0 :{
    cout << "Invalid Histogram" << endl;
    break;
    }
}//end switch

  THStack *hs = new THStack();

//  @ set the Infile names (.root assumed)
  TString InFile1 = "July10-TTJets-50ns-sel1";  // TT Jets
  TString InFile2 = "July10-WJets-50ns-sel1";  // W + Jets                                                    
  TString InFile3 = "July10-ST-50ns-sel1";  // Single Top
  TString InFile4 = "July10-ZJets-50ns-sel1";  // Drell- Yan
//  TString InFile5 = ;  //Data
  TString InFile6 = "July10-Z-200-50ns-sel1"; // Z' W= 200
  TString InFile7 = "July10-Z-20-50ns-sel1"; // Z' W = 20

/*
  cout << "Name of t #bar{t}->Jets Semi-Leptonic root file " << endl; 
  cin >> InFile1;
  cout <<"Name of W->Jets+l+nu Semi-Leptonic root file"<< endl;
  cin >> InFile2;
  cout <<"Name of Single Top t-channel Semi-Leptonic root file "<< endl;
  cin >> InFile3;
  cout <<"Name of Z->Jets+l+nu Semi-Leptonic root file"<< endl;
  cin >> InFile4;
//  cout <<"Name of DATA file Z'-> t #bar{t} Semi-Leptonic root file "<< endl;
//  cin >> InFile5;
  cout <<"Name of Signal MC, Z'-> t #bar{t} Semi-Leptonic W =200, root file "<< endl;
  cin >> InFile6;
  cout <<"Name of Signal MC, Z'-> t #bar{t} Semi-Leptonic W =20, root file "<< endl;
  cin >> InFile7;
*/

  TFile *PlotFile1 = TFile::Open("../"+InFile1+".root");       
  TFile *PlotFile2 = TFile::Open("../"+InFile2+".root");   
  TFile *PlotFile3 = TFile::Open("../"+InFile3+".root");       
  TFile *PlotFile4 = TFile::Open("../"+InFile4+".root");  
//  TFile *PlotFile5 = TFile::Open("../"+InFile5+".root");       
  TFile *PlotFile6 = TFile::Open("../"+InFile6+".root");  
  TFile *PlotFile7 = TFile::Open("../"+InFile7+".root"); 

  TH1F* histo1;
  TH1F* histo2;
  TH1F* histo3;
  TH1F* histo4;
//  TH1F* histo5;
  TH1F* histo6;
  TH1F* histo7;

//  TString Plot = Histo;
  histo1 = (TH1F*) PlotFile1->Get(Histo);
  histo2 = (TH1F*) PlotFile2->Get(Histo);
  histo3 = (TH1F*) PlotFile3->Get(Histo);
  histo4 = (TH1F*) PlotFile4->Get(Histo);
//  histo5 = (TH1F*) PlotFile5->Get(Histo);
  histo6 = (TH1F*) PlotFile6->Get(Histo);
  histo7 = (TH1F*) PlotFile7->Get(Histo);

// @ set correct event numbers

  Double_t n_events1 = 4994250 ; // TTJets                     
  Double_t n_events2 = 24089991 ; // W->l+nu+Jets
  Double_t n_events3 = 3900814 ; // Single top
  Double_t n_events4 = 19925500 ; // Drell Yan
//  Double_t n_events5 =  ; // Data
  Double_t n_events6 = 103854 ; //  Z'-> t tbar 2TeV W = 200
  Double_t n_events7 =  202573 ; //Z'-> t tbar 2TeV W = 20


  Double_t lum = 1000 ; // Arbitrary
  Double_t xsTT = 831.76; // for 13 TeV from https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO used top mass as 172.5, uncertainties on twiki	
  Double_t xsW = 20508.9;   // inclusive W  https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeV
  Double_t xsST = 136.02 ;   // t channel top at 13 TeV https://twiki.cern.ch/twiki/bin/viewauth/CMS/SingleTopSigma
  Double_t xsZ = 3205.6 ; // inclusive Z production https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeV
  Double_t xsZprime = 10 ; // Arbitrary



  TCanvas *canvas= new TCanvas("canvas","Plots",900,700);

  canvas->cd(1);
  canvas->SetFillColor(0);
  canvas->GetFrame()->SetFillColor(0);
  canvas->GetFrame()->SetBorderSize(12);

  
  histo1->Scale( xsTT * lum / n_events1 );  
  histo1->SetFillColor(kRed+1);


  histo2->Scale( xsW * lum / n_events2 ); 
  histo2->SetFillColor(kGreen+1); 

  histo3->Scale( xsST * lum / n_events3 ); 
  histo3->SetFillColor(kMagenta+1);  

  histo4->Scale( xsZ * lum / n_events4 ); 
  histo4->SetFillColor(kBlue-4);  

//  histo5->Scale( xsZprime * lum / n_events5 ); 
//  histo5->SetMarkerStyle(8); 
//  histo5->SetBinError();  // https://root.cern.ch/root/html/TH1.html#TH1:SetBinError

  histo6->Scale( xsZprime * lum / n_events6 ); 
  histo6->SetLineWidth(2); 
  histo6->SetLineColor(kGray+1);

  histo7->Scale( xsZprime * lum / n_events7 ); 
  histo7->SetLineWidth(2);
  histo7->SetLineColor(kBlack);

  hs->Add(histo3);
  hs->Add(histo4);
  hs->Add(histo2);
  hs->Add(histo1);

  hs->Draw();
  hs->GetXaxis()->SetLabelSize(0.042);
  hs->GetYaxis()->SetLabelSize(0.042);

  hs->GetXaxis()->SetTitle(xAxisTitle); // change with histo
  hs->GetXaxis()->CenterTitle();
  hs->GetXaxis()->SetTitleOffset(1.);
  hs->GetXaxis()->SetTitleSize(0.044);

  hs->GetYaxis()->SetTitle("Events");
  hs->GetYaxis()->SetTitleOffset(1.);
  hs->GetYaxis()->SetTitleSize(0.044);

//  hs->SetMaximum(800);
  hs->GetXaxis()->SetLimits(minX, maxX); // change with histo
  canvas->Modified();

//  histo5->Draw("same");
  histo6->Draw("same");
  histo7->Draw("same");
  canvas->Modified();

  TLatex *tlx = new TLatex();
  tlx->SetNDC();
  tlx->SetTextFont(42);
  tlx->SetTextSize(0.057);
  tlx->DrawLatex(0.231, 0.905, "CMS Preliminary #sqrt{s}=13 TeV, 1 fb^{-1}");
 // tlx->DrawLatex(0.77, 0.86, "#bf{CMS}");
 // tlx->DrawLatex(0.72, 0.83, "#it{very preliminary}");
  tlx->SetTextSize(0.025);

  double yInfo2 = yInfoTop-0.042;
  double yInfo3 = yInfo2-0.042;
  double yInfo4 = yInfo3-0.042;
  double yInfo5 = yInfo4-0.042;
  double yInfo6 = yInfo5-0.042;
  tlx->DrawLatex(xInfo, yInfoTop, "#bf{CMS Top Tagger}"); // same for AK4 and AK8
  tlx->DrawLatex(xInfo, yInfo2 , "#bf{Madgraph}"); // same for AK4 and AK8                   
  tlx->DrawLatex(xInfo, yInfo3, "#bf{AK R= 0.4}"); // 0.8 or 0.4 for AK8 and AK4              change with histo
  tlx->DrawLatex(xInfo, yInfo4, "#bf{|#eta| < 2.4 }");  // same for AK4 and AK8
  tlx->DrawLatex(xInfo, yInfo5, "#bf{P_{T} > 30 GeV}");// > 400 for AK8 and > 30 for AK4     change with histo
  tlx->DrawLatex(xInfo, yInfo6, "#bf{50 ns}");  // change with 25 or 50 ns bunchcrossings     change with root files
  canvas->Update();


  TLegend *legend=new TLegend(legendLocation[0], legendLocation[1],legendLocation[2], legendLocation[3] ); 
  canvas->cd(1);
  legend->SetTextFont(42);
  legend->SetTextSize(0.0395);
  legend->SetBorderSize(0.0);
  legend->SetMargin(0.3); 
//  legend->AddEntry(histo5,"Data", "p");
  legend->AddEntry(histo7,"Z' 2 TeV #sigma = 10 pb, W = 20 GeV", "l");
  legend->AddEntry(histo6,"Z' 2 TeV #sigma = 10 pb, W = 200 GeV", "l");
  legend->AddEntry(histo1," t#bar{t}", "f");  
  legend->AddEntry(histo2,"W + Jets", "f");
  legend->AddEntry(histo4,"Z + Jets", "f");
  legend->AddEntry(histo3,"Single Top", "f");
  legend->Draw();  

  // Get date for output file naming
  time_t now = time(0);
  tm *ltm = localtime(&now);
  int mon = 1 + ltm->tm_mon;
  string month = to_string(mon) ;
  string day = to_string(ltm->tm_mday) ;
  string year = to_string(1900 + ltm->tm_year) ;
 
  canvas->Update();
  canvas->Modified();
 // Name the stacked histogram
  canvas->Print("./Stacked/QualityCuts_50ns_"+CalledHisto+"_"+day+"_"+month+"_"+year+".png");

}



