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
void StackedHistoMachineAK4();
void plotter( TString Histo );

TString CalledHisto;

void StackedHistoMachineAK4(){
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
  cout << "Name of input root file 1 (e.g. TTJetpyth850nsSel1ALL-NoNtuple_70 )" << endl; 
  cin >> InFile1;
  cout <<"Name of input root file 2 (e.g. WJetsToLNupyth850nsSel1ALL )"<< endl;
  cin >> InFile2;

  TFile *PlotFile1 = TFile::Open(InFile1+".root");       
  TFile *PlotFile2 = TFile::Open(InFile2+".root");   
 
  TH1F* histo1;
  TH1F* histo2;
//  TString Plot = Histo;
  histo1 = (TH1F*) PlotFile1->Get(Histo);
  histo2 = (TH1F*) PlotFile2->Get(Histo);

  Double_t n_events1 = 4992231; // Be sure to check 
  Double_t n_events2 = 24079971; // change with input .root files
  Double_t lum = 1000 ;
  Double_t xs = 831.76; // for 13 TeV from https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO used top mass as 172.5, uncertainties on twiki	
 
  TString xAxisTitle;
    cout << "X Axis Title for this histogram (e.g. \"AK4 Jet P_{T} (GeV)\" )" << endl; 
    cin >> noskipws >> xAxisTitle;
    cout << xAxisTitle << endl;

  TCanvas *canvas= new TCanvas("canvas","Plots",900,700);

  canvas->cd(1);
  canvas->SetFillColor(0);
  canvas->GetFrame()->SetFillColor(0);
  canvas->GetFrame()->SetBorderSize(12);

  
  histo1->Scale( xs * lum / n_events1 );  
//  histo1->SetLineWidth(1);
  //histo1->SetMarkerColor(4);
 // histo1->SetFillStyle(3006);
 // histo1->SetLineColor(4);
  histo1->SetFillColor(kRed+1);


  histo2->Scale( xs * lum / n_events2 ); 
//  histo2->SetLineWidth(1);
//  histo2->SetMarkerColor(6);
 // histo2->SetFillStyle(3007);
//  histo2->SetLineColor(6); 
  histo2->SetFillColor(kGreen+1); 



 
  hs->Add(histo1);
  hs->Add(histo2);
  hs->Draw();
  hs->GetXaxis()->SetLabelSize(0.038);
  hs->GetYaxis()->SetLabelSize(0.038);

  hs->GetXaxis()->SetTitle(xAxisTitle);
  hs->GetXaxis()->SetTitleOffset(0.945);
  hs->GetXaxis()->SetTitleSize(0.045);

  hs->GetYaxis()->SetTitle("Events");
  hs->GetYaxis()->SetTitleOffset(1.03);
  hs->GetYaxis()->SetTitleSize(0.045);

  hs->GetXaxis()->SetLimits(0,100);

  canvas->Modified();




  TLatex *tlx = new TLatex();
//  canvas->cd(1);
  tlx->SetNDC();
  tlx->SetTextFont(42);
  tlx->SetTextSize(0.035);
  tlx->DrawLatex(5.7, 0.89, "#sqrt{s}=13 TeV, ? fb^{-1}, bx=50 ns");
  tlx->DrawLatex(0.77, 0.86, "#bf{CMS}");
  tlx->DrawLatex(0.72, 0.83, "#it{very preliminary}");
  tlx->DrawLatex(0.2, 0.846, "#bf{Madgraph}"); // same for AK4 and AK8
  tlx->DrawLatex(0.2, 0.809, "#bf{AK R= 0.4 , |#eta| < 2.4}"); // same for AK4 and AK8
  tlx->DrawLatex(0.2, 0.775, "#bf{P_{T} > 30 GeV/c   }"); // > 400 for AK8 and > 30 for AK4
  canvas->Update();

  TLegend *legend=new TLegend(0.670759, 0.550595, 0.870536, 0.651488 ); //0.751488
  canvas->cd(1);
  legend->SetTextFont(52);
  legend->SetTextSize(0.0345);
  legend->SetBorderSize(0.);
  legend->SetMargin(0.2);
  legend->AddEntry(histo1,"Semi-Leptonic t#bar{t}", "f"); // Be sure to check 
  legend->AddEntry(histo2,"W + Jets", "f");// change with input .root files
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
  canvas->Print("./Stacked/"+InFile1+"-"+InFile2+"-"+CalledHisto+"-"+day+"_"+month+"_"+year+".png");

}
