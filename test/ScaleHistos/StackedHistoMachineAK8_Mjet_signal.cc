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


void callHistos();
void StackedHistoMachineAK8_Mjet_signal();
void plotter( TString Histo );

TString CalledHisto;

void StackedHistoMachineAK8_Mjet_signal(){
    callHistos ();
}

void callHistos ( ){  
    cout << "Histogram to plot (e.g. h_ptAK4)" << endl; 
    cin >> CalledHisto;
    plotter( CalledHisto );
}


void plotter(TString Histo){
  
  THStack *hs = new THStack();
  TString InFile1;
  TString InFile2;
  TString InFile3;
  TString InFile4;
  TString InFile5;
  TString InFile6;
  TString InFile7;

  cout << "Name of t #bar{t}->Jets Semi-Leptonic root file " << endl; 
  cin >> InFile1;
  cout <<"Name of W->Jets+l+nu Semi-Leptonic root file"<< endl;
  cin >> InFile2;
  cout << "Name of t #bar{t}->Jets Fully-Leptonic root file " << endl; 
  cin >> InFile3;
  cout <<"Name of Single Top t-channel Semi-Leptonic root file "<< endl;
  cin >> InFile4;
//  cout <<"Name of Z->Jets+l+nu Semi-Leptonic root file"<< endl;
//  cin >> InFile5;
//  cout <<"Name of DATA file Z'-> t #bar{t} Semi-Leptonic root file "<< endl;
//  cin >> InFile6;
  cout <<"Name of Signal MC, Z'-> t #bar{t} Semi-Leptonic, root file "<< endl;
  cin >> InFile7;

  TFile *PlotFile1 = TFile::Open("../"+InFile1+".root");       
  TFile *PlotFile2 = TFile::Open("../"+InFile2+".root");   
  TFile *PlotFile3 = TFile::Open("../"+InFile3+".root");       
  TFile *PlotFile4 = TFile::Open("../"+InFile4+".root");  
//  TFile *PlotFile5 = TFile::Open("../"+InFile5+".root");       
//  TFile *PlotFile6 = TFile::Open("../"+InFile6+".root");  
  TFile *PlotFile7 = TFile::Open("../"+InFile7+".root"); 

  TH1F* histo1;
  TH1F* histo2;
  TH1F* histo3;
  TH1F* histo4;
  TH1F* histo5;
  TH1F* histo6;
  TH1F* histo7;

//  TString Plot = Histo;
  histo1 = (TH1F*) PlotFile1->Get(Histo);
  histo2 = (TH1F*) PlotFile2->Get(Histo);
  histo3 = (TH1F*) PlotFile3->Get(Histo);
  histo4 = (TH1F*) PlotFile4->Get(Histo);
//  histo5 = (TH1F*) PlotFile5->Get(Histo);
//  histo6 = (TH1F*) PlotFile6->Get(Histo);
  histo7 = (TH1F*) PlotFile7->Get(Histo);

  Double_t n_events1 = 4994250 ; // TTJets
  Double_t n_events2 = 24089991 ; // W->l+nu+Jets
  Double_t n_events3 = 4994250 ; // TTJets
  Double_t n_events4 = 3900814 ; // Single top
  Double_t n_events5 = 1 ; // Drell Yan
  Double_t n_events6 = 1 ; // Data
  Double_t n_events7 = 103854 ; // Z'-> t tbar 2TeV


  Double_t lum = 1000 ;
  Double_t xsTT = 831.76; // for 13 TeV from https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO used top mass as 172.5, uncertainties on twiki	
  Double_t xsW = 20508.9;   // inclusive W  https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeV
  Double_t xsST = 136.02 ;   // t channel top at 13 TeV https://twiki.cern.ch/twiki/bin/viewauth/CMS/SingleTopSigma
 // Double_t xsZ = 3205.6 ; // inclusive Z production https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeV
  Double_t xsZprime = 10 ; // arbitrarily set

  TString xAxisTitle;
    cout << "X Axis Title for this histogram (e.g. \"Jet P_{T}\0GeV)\" )" << endl; 
    cin  >> xAxisTitle;
//    cin >> noskipws >> xAxisTitle;
//    cout << xAxisTitle << endl;

  TCanvas *canvas= new TCanvas("canvas","Plots",900,700);

  canvas->cd(1);
  canvas->SetFillColor(0);
  canvas->GetFrame()->SetFillColor(0);
  canvas->GetFrame()->SetBorderSize(12);

  
  histo1->Scale( xsTT * lum / n_events1 );  
//  histo1->SetLineWidth(1);
  //histo1->SetMarkerColor(4);
 // histo1->SetFillStyle(3006);
 // histo1->SetLineColor(4);
  histo1->SetFillColor(kRed+1);


  histo2->Scale( xsW * lum / n_events2 ); 
//  histo2->SetLineWidth(1);
//  histo2->SetMarkerColor(6);
 // histo2->SetFillStyle(3007);
//  histo2->SetLineColor(6); 
  histo2->SetFillColor(kGreen+1); 

  histo3->Scale( xsTT * lum / n_events3 ); 
  histo3->SetFillColor(kRed-7); 

  histo4->Scale( xsST * lum / n_events4 ); 
  histo4->SetFillColor(kMagenta+1); 

//  histo5->Scale( xsZ * lum / n_events5 ); 
//  histo5->SetFillColor(kBlue-4);  

//  histo6->Scale( xsZprime * lum / n_events6 ); 
//  histo6->SetMarkerStyle(8); 
//  histo6->SetBinError();  // https://root.cern.ch/root/html/TH1.html#TH1:SetBinError

  histo7->Scale( xsZprime * lum / n_events7 ); 
  histo7->SetLineWidth(2); 

//  hs->Add(histo6);
  hs->Add(histo4);
//  hs->Add(histo5);
  hs->Add(histo2);
  hs->Add(histo3);
  hs->Add(histo1);

  hs->Draw();
  hs->GetXaxis()->SetLabelSize(0.042);
  hs->GetYaxis()->SetLabelSize(0.042);

  hs->GetXaxis()->SetTitle(xAxisTitle);
  hs->GetXaxis()->SetTitleOffset(0.78);
  hs->GetXaxis()->SetTitleSize(0.054);

  hs->GetYaxis()->SetTitle("Events");
  hs->GetYaxis()->SetTitleOffset(0.9);
  hs->GetYaxis()->SetTitleSize(0.055);

  hs->GetXaxis()->SetLimits(-50,450);
  canvas->Modified();

  histo7->Draw("same");
  canvas->Modified();

  TLatex *tlx = new TLatex();
//  canvas->cd(1);
  tlx->SetNDC();
  tlx->SetTextFont(42);
  tlx->SetTextSize(0.057);
  tlx->DrawLatex(0.131, 0.905, "CMS Preliminary #sqrt{s}=13 TeV, 1 fb^{-1}");
 // tlx->DrawLatex(0.77, 0.86, "#bf{CMS}");
 // tlx->DrawLatex(0.72, 0.83, "#it{very preliminary}");
  tlx->SetTextSize(0.030);
// For./Input/AK8minmass-TTJet_WJetLNu-TTJet-ST.txt - move x below to 0.131 was 0.1 by default 
  tlx->DrawLatex(0.131, 0.868, "#bf{CMS Top Tagger}"); // same for AK4 and AK8 
  tlx->DrawLatex(0.131, 0.826, "#bf{Madgraph}"); // same for AK4 and AK8                   
  tlx->DrawLatex(0.131, 0.789, "#bf{AK R= 0.8}"); // same for AK4 and AK8
  tlx->DrawLatex(0.131, 0.755, "#bf{|#eta| < 2.4 }"); // > 400 for AK8 and > 30 for AK4
  tlx->DrawLatex(0.131, 0.712, "#bf{P_{T} > 400 GeV}");
  tlx->DrawLatex(0.131, 0.676, "#bf{50 ns}"); 
  canvas->Update();

  TLegend *legend=new TLegend(0.520759, 0.350595, 0.870536, 0.651488 ); //0.690759, 0.350595, 0.870536, 0.651488
  canvas->cd(1);
  legend->SetTextFont(42);
  legend->SetTextSize(0.0395);
  legend->SetBorderSize(0.);
//  legend->SetEntrySeparation(9.0);
  legend->SetMargin(0.3); //0.2
//  legend->AddEntry(histo6,"Data", "p");
  legend->AddEntry(histo7,"Z' 2 TeV #sigma = 10 pb");
  legend->AddEntry(histo1," t#bar{t}", "f"); // Be sure to check 
//  legend->AddEntry(histo3,"Fully-Leptonic t#bar{t}", "f");
  legend->AddEntry(histo2,"W + Jets", "f");// change with input .root files
//  legend->AddEntry(histo5,"Z + Jets", "f");
  legend->AddEntry(histo4,"Single Top", "f");
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
  canvas->Print("./Stacked/"+InFile1+"-"+InFile2+"-"+InFile3+"-"+InFile4+"-"+CalledHisto+"-"+day+"_"+month+"_"+year+".png");

}
