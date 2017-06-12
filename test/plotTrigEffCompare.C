// .L plotTrigEffCompare.C+  
// plotTrigEffCompare(bool plot1D = 1, bool plot2D = 1)

#include <cstdlib>
#include "TClonesArray.h"
#include "TLorentzVector.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TFile.h"
#include "TF1.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include "TChain.h"
#include "TLatex.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TColor.h"
#include "TStyle.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TString.h"
#include <vector>
#include <algorithm>
#include "TROOT.h"
// #include "CMS_lumi.C"

void plotEffMixed_AddOn(string, string, string, string, string, bool, bool);

void plotTrigEffCompare(bool plot1D = 1, bool plot2D = 1){
  //function definitions: 
  //void plotEffMixed_AddOn(string inFile, string inFileLabel, string runLabel, string runLabelOutFile, string date)

  string date = "20170608";
  //plotEffMixed_AddOn("outRunTrigEff_20170320_b2gtreeV5_JetHT_Run2016BtoG-03Feb2017_JSONfinal.root", "outRunTrigEff_20170320_b2gtreeV5_JetHT_Run2016H-03Feb2017_JSONfinal.root", "36 fb^{-1} (13 TeV)", "RunsBtoHdata", date);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_JetHT_Run2016BtoH-03Feb2017_JSONfinal.root",date.c_str()), "Runs B-H", "36 fb^{-1} (13 TeV)", "RunsBtoHdata", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root",date.c_str()), "t#bar{t}", "13 TeV", "_TT", date, plot1D, plot2D);

  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_ZprimeToTT_M-1000_W-10_RunIISummer16MiniAODv2.root",date.c_str()), "1 TeV Z' (#Gamma = 1%)", "13 TeV", "_ZprimeToTT_M-1000_W-10", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_ZprimeToTT_M-1000_W-100_RunIISummer16MiniAODv2.root",date.c_str()), "1 TeV Z' (#Gamma = 10%)", "13 TeV", "_ZprimeToTT_M-1000_W-100", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_ZprimeToTT_M-1000_W-300_RunIISummer16MiniAODv2.root",date.c_str()), "1 TeV Z' (#Gamma = 30%)", "13 TeV", "_ZprimeToTT_M-1000_W-300", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_ZprimeToTT_M-1250_W-12p5_RunIISummer16MiniAODv2.root",date.c_str()), "1.25 TeV Z' (#Gamma = 1%)", "13 TeV", "_ZprimeToTT_M-1250_W-12p5", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_ZprimeToTT_M-1250_W-125_RunIISummer16MiniAODv2.root",date.c_str()), "1.25 TeV Z' (#Gamma = 10%)", "13 TeV", "_ZprimeToTT_M-1250_W-125", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_ZprimeToTT_M-1500_W-15_RunIISummer16MiniAODv2.root",date.c_str()), "1.5 TeV Z' (#Gamma = 1%)", "13 TeV", "_ZprimeToTT_M-1500_W-15", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_ZprimeToTT_M-1500_W-150_RunIISummer16MiniAODv2.root",date.c_str()), "1.5 TeV Z' (#Gamma = 10%)", "13 TeV", "_ZprimeToTT_M-1500_W-150", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_ZprimeToTT_M-2000_W-20_RunIISummer16MiniAODv2.root",date.c_str()), "2 TeV Z' (#Gamma = 1%)", "13 TeV", "_ZprimeToTT_M-2000_W-20", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_ZprimeToTT_M-2000_W-200_RunIISummer16MiniAODv2.root",date.c_str()), "2 TeV Z' (#Gamma = 10%)", "13 TeV", "_ZprimeToTT_M-2000_W-200", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_ZprimeToTT_M-2000_W-600_RunIISummer16MiniAODv2.root",date.c_str()), "2 TeV Z' (#Gamma = 30%)", "13 TeV", "_ZprimeToTT_M-2000_W-600", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_ZprimeToTT_M-3000_W-30_RunIISummer16MiniAODv2.root",date.c_str()), "3 TeV Z' (#Gamma = 1%)", "13 TeV", "_ZprimeToTT_M-3000_W-30", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_ZprimeToTT_M-3000_W-300_RunIISummer16MiniAODv2.root",date.c_str()), "3 TeV Z' (#Gamma = 10%)", "13 TeV", "_ZprimeToTT_M-3000_W-300", date, plot1D, plot2D);
  //plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_ZprimeToTT_M-3000_W-900_RunIISummer16MiniAODv2.root",date.c_str()), "3 TeV Z' (#Gamma = 30%)", "13 TeV", "_ZprimeToTT_M-3000_W-900", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_ZprimeToTT_M-4000_W-40_RunIISummer16MiniAODv2.root",date.c_str()), "4 TeV Z' (#Gamma = 1%)", "13 TeV", "_ZprimeToTT_M-4000_W-40", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_ZprimeToTT_M-4000_W-400_RunIISummer16MiniAODv2.root",date.c_str()), "4 TeV Z' (#Gamma = 10%)", "13 TeV", "_ZprimeToTT_M-4000_W-400", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_ZprimeToTT_M-4000_W-1200_RunIISummer16MiniAODv2.root",date.c_str()), "4 TeV Z' (#Gamma = 30%)", "13 TeV", "_ZprimeToTT_M-4000_W-1200", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_ZprimeToTT_M-5000_W-50_RunIISummer16MiniAODv2.root",date.c_str()), "5 TeV Z' (#Gamma = 1%)", "13 TeV", "_ZprimeToTT_M-5000_W-50", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_ZprimeToTT_M-5000_W-500_RunIISummer16MiniAODv2.root",date.c_str()), "5 TeV Z' (#Gamma = 10%)", "13 TeV", "_ZprimeToTT_M-5000_W-500", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_ZprimeToTT_M-5000_W-1500_RunIISummer16MiniAODv2.root",date.c_str()), "5 TeV Z' (#Gamma = 30%)", "13 TeV", "_ZprimeToTT_M-5000_W-1500", date, plot1D, plot2D);

  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_RSGluonToTT_M-1000_RunIISummer16MiniAODv2.root",date.c_str()), "1 TeV RS KK Gluon", "13 TeV", "_RSGluonToTT_M-1000", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_RSGluonToTT_M-1250_RunIISummer16MiniAODv2.root",date.c_str()), "1.25 TeV RS KK Gluon", "13 TeV", "_RSGluonToTT_M-1250", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_RSGluonToTT_M-1500_RunIISummer16MiniAODv2.root",date.c_str()), "1.5 TeV RS KK Gluon", "13 TeV", "_RSGluonToTT_M-1500", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_RSGluonToTT_M-2000_RunIISummer16MiniAODv2.root",date.c_str()), "2 TeV RS KK Gluon", "13 TeV", "_RSGluonToTT_M-2000", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_RSGluonToTT_M-2500_RunIISummer16MiniAODv2.root",date.c_str()), "2.5 TeV RS KK Gluon", "13 TeV", "_RSGluonToTT_M-2500", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_RSGluonToTT_M-3000_RunIISummer16MiniAODv2.root",date.c_str()), "3 TeV RS KK Gluon", "13 TeV", "_RSGluonToTT_M-3000", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_RSGluonToTT_M-3500_RunIISummer16MiniAODv2.root",date.c_str()), "3.5 TeV RS KK Gluon", "13 TeV", "_RSGluonToTT_M-3500", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_RSGluonToTT_M-4000_RunIISummer16MiniAODv2.root",date.c_str()), "4 TeV RS KK Gluon", "13 TeV", "_RSGluonToTT_M-4000", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_RSGluonToTT_M-4500_RunIISummer16MiniAODv2.root",date.c_str()), "4.5 TeV RS KK Gluon", "13 TeV", "_RSGluonToTT_M-4500", date, plot1D, plot2D);
  plotEffMixed_AddOn(Form("outRunTrigEff_%s_b2gtreeV5_RSGluonToTT_M-5000_RunIISummer16MiniAODv2.root",date.c_str()), "5 TeV RS KK Gluon", "13 TeV", "_RSGluonToTT_M-5000", date, plot1D, plot2D);
}

void plotEffMixed_AddOn(string inFile, string inFileLabel, string runLabel, string runLabelOutFile, string date, bool plot1D, bool plot2D){
  gStyle->SetOptStat(0);
  gROOT->UseCurrentStyle();
  gROOT->ForceStyle();

  gROOT->Reset();
  gROOT->ForceStyle(); 
  TCanvas *c1237= new TCanvas("c1237","",1,1,745,640);
  TCanvas* c2 = new TCanvas();
  TLegend * legLeft;
  TLegend * legRight;

  // TCanvas *c1 = new TCanvas("c1", "c1",1,1,745,701);
  gStyle->SetOptFit(1);
  gStyle->SetOptStat(0);
  c1237->SetHighLightColor(2);
  c1237->Range(0,0,1,1);
  c1237->SetFillColor(0);
  c1237->SetBorderMode(0);
  c1237->SetBorderSize(2);
  c1237->SetTickx(1);
  c1237->SetTicky(1);
  c1237->SetLeftMargin(0.1);
  c1237->SetRightMargin(0.11);
  c1237->SetTopMargin(0.08);
  c1237->SetBottomMargin(0.1);
  c1237->SetFrameFillStyle(0);
  c1237->SetFrameBorderMode(0);

  inFile = "trigEffStudies/run"+date+"/"+inFile;
  TFile * F_data =  new TFile( inFile.c_str());
  cout << "Opening " << inFile << endl;

  vector <string> numOrVec;
  vector <string> numOrPave;
  vector <Color_t> histColorVec;

  vector <string> xVarVec;
  vector <string> xTitleVec;
  vector <double> xMin;
  vector <double> xMax;

  vector <string> x2DVarVec;
  vector <string> x2DTitleVec;
  vector <string> y2DVarVec;
  vector <string> y2DTitleVec;

  vector <string> ptCutVec;
  vector <string> ptCutPaveVec;
  vector <string> cutVec;
  vector <double> cutPaveVecY;

  string PFHTmainTrigger = "PFHT800orPFHT900";
  numOrVec.push_back("PFHT800orPFHT900");  numOrPave.push_back("PFHT800 or PFHT900"); histColorVec.push_back(kBlack);
  numOrVec.push_back("PFHT800orPFHT900orPFHT700TrimMass50");  numOrPave.push_back("#splitline{PFHT800 or PFHT900}{or PFHT700TrimMass50}");histColorVec.push_back(kRed);
  numOrVec.push_back("PFHT800orPFHT900orAK8PFJet450");  numOrPave.push_back("#splitline{PFHT800 or PFHT900}{or AK8PFJet450}"); histColorVec.push_back(kGreen+2);
  numOrVec.push_back("PFHT800orPFHT900orPFJet360TrimMass30");  numOrPave.push_back("#splitline{PFHT800 or PFHT900}{or PFJet360TrimMass30}"); histColorVec.push_back(kBlue);
  numOrVec.push_back("PFHT800orPFHT900orPFHT700TrimMass50orAK8PFJet450");  numOrPave.push_back("#splitline{PFHT800 or PFHT900}{#splitline{or PFHT700TrimMass50}{or AK8PFJet450}}"); histColorVec.push_back(kMagenta+3);
  numOrVec.push_back("PFHT800orPFHT900orPFHT700TrimMass50orPFJet360TrimMass30");  numOrPave.push_back("#splitline{PFHT800 or PFHT900}{#splitline{or PFHT700TrimMass50}{or PFJet360TrimMass30}}"); histColorVec.push_back(kOrange-3);
  numOrVec.push_back("PFHT800orPFHT900orAK8PFJet450orPFJet360TrimMass30");  numOrPave.push_back("#splitline{PFHT800 or PFHT900}{#splitline{or AK8PFJet450}{or PFJet360TrimMass30}}"); histColorVec.push_back(kCyan+2);
  numOrVec.push_back("PFHT800orPFHT900orPFHT700TrimMass50orAK8PFJet450orPFJet360TrimMass30");  numOrPave.push_back("#splitline{#splitline{PFHT800 or PFHT900}{or PFHT700TrimMass50}}{#splitline{or AK8PFJet450}{or PFJet360TrimMass30}}"); histColorVec.push_back(kViolet+2);

  xVarVec.push_back("sumJetPt"); xTitleVec.push_back("Jet 0 p_{T} + Jet 1 p_{T} [GeV]"); xMin.push_back(200.); xMax.push_back(2200.);
  xVarVec.push_back("HT"); xTitleVec.push_back("H_{T} [GeV]"); xMin.push_back(200.); xMax.push_back(2200.);
  xVarVec.push_back("Jet0Pt"); xTitleVec.push_back("Jet 0 p_{T} [GeV]"); xMin.push_back(200.); xMax.push_back(1000.);
  xVarVec.push_back("Jet1Pt"); xTitleVec.push_back("Jet 1 p_{T} [GeV]"); xMin.push_back(200.); xMax.push_back(1000.);
  xVarVec.push_back("Jet0PUPPISoftDropMass"); xTitleVec.push_back("Jet 0 PUPPI Soft Drop Mass [GeV]"); xMin.push_back(0.); xMax.push_back(250.);
  xVarVec.push_back("Jet1PUPPISoftDropMass"); xTitleVec.push_back("Jet 1 PUPPI Soft Drop Mass [GeV]"); xMin.push_back(0.); xMax.push_back(250.);
  xVarVec.push_back("JetPUPPISoftDropMass"); xTitleVec.push_back("Jet PUPPI Soft Drop Mass [GeV]"); xMin.push_back(0.); xMax.push_back(250.);

  x2DVarVec.push_back("sumJetPt"); x2DTitleVec.push_back("Jet 0 p_{T} + Jet 1 p_{T} [GeV]");
  x2DVarVec.push_back("HT"); x2DTitleVec.push_back("H_{T} [GeV]");

  y2DVarVec.push_back("Jet0PUPPISoftDropMass"); y2DTitleVec.push_back("Jet 0 PUPPI Soft Drop Mass [GeV]");
  y2DVarVec.push_back("Jet1PUPPISoftDropMass"); y2DTitleVec.push_back("Jet 1 PUPPI Soft Drop Mass [GeV]");
  y2DVarVec.push_back("JetPUPPISoftDropMass"); y2DTitleVec.push_back("Jet PUPPI Soft Drop Mass [GeV]");

  ptCutVec.push_back("_minpt400"); ptCutPaveVec.push_back("p_{T} > 400 GeV");
  ptCutVec.push_back("_minpt450"); ptCutPaveVec.push_back("p_{T} > 450 GeV");
  ptCutVec.push_back("_minpt500"); ptCutPaveVec.push_back("p_{T} > 500 GeV");
  
  cutVec.push_back(""); cutPaveVecY.push_back(0.77);
  cutVec.push_back("_1tagPUPPImass_jet0"); cutPaveVecY.push_back(0.71); 
  cutVec.push_back("_1tagPUPPItau32_jet0"); cutPaveVecY.push_back(0.71);
  cutVec.push_back("_1tagPUPPItoptag_jet0"); cutPaveVecY.push_back(0.65);
  cutVec.push_back("_1tagPUPPImass_jet1"); cutPaveVecY.push_back(0.71);
  cutVec.push_back("_1tagPUPPItau32_jet1"); cutPaveVecY.push_back(0.71);
  cutVec.push_back("_1tagPUPPItoptag_jet1"); cutPaveVecY.push_back(0.65);
  cutVec.push_back("_1tagPUPPImass_jets"); cutPaveVecY.push_back(0.71);
  cutVec.push_back("_1tagPUPPItau32_jets"); cutPaveVecY.push_back(0.71);
  cutVec.push_back("_1tagPUPPItoptag_jets"); cutPaveVecY.push_back(0.65);

  TH1D *h_dataDenom;
  TH1D *h_dataNum[numOrVec.size()];

  TH2D *h_dataDenom2D;
  TH2D *h_dataNum2D;
	
  for (unsigned int i_ptCutVec=0; i_ptCutVec<ptCutVec.size(); i_ptCutVec++){    

    vector <string> cutPaveVec;
    cutPaveVec.push_back(Form("AK8 jets, |#Delta#phi| > 2.1, %s",ptCutPaveVec[i_ptCutVec].c_str()));
    cutPaveVec.push_back(Form("#splitline{AK8 jets, |#Delta#phi| > 2.1, %s,}{Jet 0: 105 < M_{PUPPI + SD} < 210 GeV}",ptCutPaveVec[i_ptCutVec].c_str()));
    cutPaveVec.push_back(Form("#splitline{AK8 jets, |#Delta#phi| > 2.1, %s,}{Jet 0: #tau_{32}^{PUPPI} < 0.65}",ptCutPaveVec[i_ptCutVec].c_str()));
    cutPaveVec.push_back(Form("#splitline{AK8 jets, |#Delta#phi| > 2.1, %s,}{#splitline{Jet 0: 105 < M_{PUPPI + SD} < 210 GeV,}{#tau_{32}^{PUPPI} < 0.65}}",ptCutPaveVec[i_ptCutVec].c_str()));
    cutPaveVec.push_back(Form("#splitline{AK8 jets, |#Delta#phi| > 2.1, %s,}{Jet 1: 105 < M_{PUPPI + SD} < 210 GeV}",ptCutPaveVec[i_ptCutVec].c_str()));
    cutPaveVec.push_back(Form("#splitline{AK8 jets, |#Delta#phi| > 2.1, %s,}{Jet 1: #tau_{32}^{PUPPI} < 0.65}",ptCutPaveVec[i_ptCutVec].c_str()));
    cutPaveVec.push_back(Form("#splitline{AK8 jets, |#Delta#phi| > 2.1, %s,}{#splitline{Jet 1: 105 < M_{PUPPI + SD} < 210 GeV,}{#tau_{32}^{PUPPI} < 0.65}}",ptCutPaveVec[i_ptCutVec].c_str()));
    cutPaveVec.push_back(Form("#splitline{AK8 jets, |#Delta#phi| > 2.1, %s,}{1+ jet: 105 < M_{PUPPI + SD} < 210 GeV}",ptCutPaveVec[i_ptCutVec].c_str()));
    cutPaveVec.push_back(Form("#splitline{AK8 jets, |#Delta#phi| > 2.1, %s,}{1+ jet: #tau_{32}^{PUPPI} < 0.65}",ptCutPaveVec[i_ptCutVec].c_str()));
    cutPaveVec.push_back(Form("#splitline{AK8 jets, |#Delta#phi| > 2.1, %s,}{#splitline{1+ jet: 105 < M_{PUPPI + SD} < 210 GeV,}{#tau_{32}^{PUPPI} < 0.65}}",ptCutPaveVec[i_ptCutVec].c_str()));
    
    for (unsigned int i_cutVec=0; i_cutVec<cutVec.size(); i_cutVec++){    
      //cout << cutVec[i_cutVec] << endl;
      if (plot1D){
	for (unsigned int i_xVarVec=0; i_xVarVec<xVarVec.size(); i_xVarVec++){    
	  //cout << xVarVec[i_xVarVec] << endl;
	  if (i_cutVec == 0 && i_xVarVec == 0){
	    c2->cd();

	    legLeft = new TLegend(0.06, 0.06, 0.5, 0.94); //0.51, 0.18,0.87, cutPaveVecY[i_cutVec] - 0.05 //0.51, 0.66,0.84, 0.83
	    legLeft->SetBorderSize(0);
	    legLeft->SetFillColor(0);
	    legLeft->SetFillStyle(4000);
	    legLeft->SetTextSize(0.032);
	    legLeft->AddEntry((TObject*)0,"Triggers","");
	    legLeft->AddEntry((TObject*)0,"Denominator: Mu50 or IsoMu24","");
	    legLeft->AddEntry((TObject*)0,"Numerator: ","");

	    legRight = new TLegend(0.52, 0.06, 0.94, 0.94); //0.51, 0.18,0.87, cutPaveVecY[i_cutVec] - 0.05 //0.51, 0.66,0.84, 0.83
	    legRight->SetBorderSize(0);
	    legRight->SetFillColor(0);
	    legRight->SetFillStyle(4000);
	    legRight->SetTextSize(0.032);
	    legRight->AddEntry((TObject*)0,"","");
	    legRight->AddEntry((TObject*)0,"","");
	    legRight->AddEntry((TObject*)0,"","");

	    c1237->cd();
	  }//end if for legend

	  //denominator histogram
	  string endHistName = "Mu50orIsoMu24denom" + ptCutVec[i_ptCutVec] + cutVec[i_cutVec] + "_" + xVarVec[i_xVarVec];
	  string denomHistName = "h_pass" + endHistName;
	  h_dataDenom = (TH1D*)F_data ->Get(denomHistName.c_str());

	  h_dataDenom->Sumw2();
	  h_dataDenom->Rebin(2);

	  for (unsigned int i_numOrVec=0; i_numOrVec<numOrVec.size(); i_numOrVec++){    
	    string numHistName = "h_pass" + numOrVec[i_numOrVec] + "num" + endHistName;

	    h_dataNum[i_numOrVec] = (TH1D*)F_data ->Get(numHistName.c_str());
	    h_dataNum[i_numOrVec]->Sumw2();
	    //cout << "Numerator histograms, " + numHistName1 + ", acquired!" << endl;

	    h_dataNum[i_numOrVec]->Rebin(2);
	    h_dataNum[i_numOrVec]->Divide(h_dataNum[i_numOrVec], h_dataDenom, 1, 1, "B");
	    //cout << "Efficiency histogram created!" << endl;

	    h_dataNum[i_numOrVec]->SetLineWidth(2);
	    h_dataNum[i_numOrVec]->SetLineColor(histColorVec[i_numOrVec]);
	  
	    if (i_numOrVec == 0) h_dataNum[i_numOrVec]->Draw("EP");
	    else h_dataNum[i_numOrVec]->Draw("EPsame");

	    if (i_cutVec == 0 && i_xVarVec == 0){
	      c2->cd();
	      if (i_numOrVec < (numOrVec.size()/2)) legLeft->AddEntry( h_dataNum[i_numOrVec]   , numOrPave[i_numOrVec].c_str() , "LP" );
	      else legRight->AddEntry( h_dataNum[i_numOrVec]   , numOrPave[i_numOrVec].c_str() , "LP" );
	      c1237->cd();
	    }//end if for legend
	  }//end numerator loop

	  if (i_cutVec == 0 && i_xVarVec == 0){
	    c2->cd();
	    legLeft->Draw();
	    legRight->Draw("Same");
	    string legsavename = "trigEffStudies/run" + date + "/plots/1Dlegend";
	    c2->SaveAs(Form("%s.pdf",legsavename.c_str()));    
	    legLeft->Delete();
	    legRight->Delete();
	    c1237->cd();
	  }//end if for legend

	  string title = ";" + xTitleVec[i_xVarVec] + ";Trigger Efficiency";
	  h_dataNum[0]->SetTitle(title.c_str());
	  h_dataNum[0]->GetXaxis()->SetNoExponent();
	  h_dataNum[0]->GetXaxis()->SetMoreLogLabels();
	  
	  h_dataNum[0]->GetXaxis()->SetTitleOffset(1.15);
	  h_dataNum[0]->GetXaxis()->SetTitleFont(42);
	  h_dataNum[0]->GetXaxis()->SetRangeUser(xMin[i_xVarVec],xMax[i_xVarVec]);

	  h_dataNum[0]->GetXaxis()->SetNoExponent();
	  h_dataNum[0]->GetXaxis()->SetMoreLogLabels();

	  h_dataNum[0]->GetYaxis()->SetTitleOffset(1.25);
	  h_dataNum[0]->GetYaxis()->SetTitleFont(42);
	  h_dataNum[0]->GetYaxis()->SetRangeUser(0.0,1.5);

	  h_dataNum[0]->Draw("EPsame");
	
	  gPad->RedrawAxis();

	  TLatex *   tex = new TLatex(0.12,0.83,"#font[62]{CMS} #font[52]{Preliminary}");
	  tex->SetNDC();
	  tex->SetTextFont(42);
	  tex->SetTextSize(0.0625);
	  tex->SetLineWidth(2);
	  tex->Draw();

	  tex = new TLatex(0.89,0.936, runLabel.c_str());
	  tex->SetNDC();
	  tex->SetTextAlign(31);
	  tex->SetTextFont(42);
	  // tex->SetTextSize(0.0625);
	  tex->SetTextSize(0.0575);
	  tex->SetLineWidth(2);
	  tex->Draw();
		  
	  tex = new TLatex(0.51,0.87,inFileLabel.c_str());
	  tex->SetNDC();
	  tex->SetTextAlign(13);
	  tex->SetTextFont(42);
	  tex->SetTextSize(0.032);
	  tex->SetLineWidth(2);
	  tex->Draw();

	  tex = new TLatex(0.51,0.82,cutPaveVec[i_cutVec].c_str());
	  tex->SetNDC();
	  tex->SetTextAlign(13);
	  tex->SetTextFont(42);
	  tex->SetTextSize(0.032);
	  tex->SetLineWidth(2);
	  tex->Draw();

	  //cout << "Cut vector drawn!" << endl;

	  string savename = "trigEffStudies/run" + date + "/plots/" + PFHTmainTrigger + "numsCompareMu50orIsoMu24denom_trigEff_" + xVarVec[i_xVarVec] + cutVec[i_cutVec] + ptCutVec[i_ptCutVec] + runLabelOutFile;
	  c1237->SaveAs(Form("%s.pdf",savename.c_str()));    
	  
	  h_dataNum[0]->GetYaxis()->SetRangeUser(0.9,1.05);
	  c1237->SaveAs(Form("%s_zoomYaxis.pdf",savename.c_str()));    

	  h_dataNum[0]->GetYaxis()->SetRangeUser(0.98,1.01);
	  c1237->SaveAs(Form("%s_extraZoomYaxis.pdf",savename.c_str()));    

	  for (unsigned int i_numOrVec=0; i_numOrVec<numOrVec.size(); i_numOrVec++){
	    h_dataNum[i_numOrVec]->Delete();
	  }//end numerator loop
	  h_dataDenom->Delete();
	  //cout << "Nums deleted!" << endl;
	  //cout << "Denoms deleted!" << endl;
	}//end x variable loop
      }//end plot 1D if
      if (plot2D){
	for (unsigned int i_y2DVarVec=0; i_y2DVarVec<y2DVarVec.size(); i_y2DVarVec++){    
	  //cout << y2DVarVec[i_y2DVarVec] << endl;
	  for (unsigned int i_x2DVarVec=0; i_x2DVarVec<x2DVarVec.size(); i_x2DVarVec++){    

	    //cout << x2DVarVec[i_x2DVarVec] << endl;

	    //denominator histograms
	    string endHistName = "Mu50orIsoMu24denom" + ptCutVec[i_ptCutVec] + cutVec[i_cutVec] + "_" + y2DVarVec[i_y2DVarVec] + "vs" + x2DVarVec[i_x2DVarVec];
	    string denomHistName = "h_pass" + endHistName;
	    h_dataDenom2D = (TH2D*)F_data ->Get(denomHistName.c_str());

	    h_dataDenom2D->Sumw2();
	    h_dataDenom2D->Rebin2D(2,2);

	    for (unsigned int i_numOrVec=0; i_numOrVec<numOrVec.size(); i_numOrVec++){    
	      string numHistName = "h_pass" + numOrVec[i_numOrVec] + "num" + endHistName;

	      h_dataNum2D = (TH2D*)F_data ->Get(numHistName.c_str());
	      h_dataNum2D->Sumw2();
	      //cout << "Numerator histograms, " + numHistName1 + ", acquired!" << endl;

	      h_dataNum2D->Rebin2D(2,2);
	      h_dataNum2D->Divide(h_dataNum2D, h_dataDenom2D, 1, 1, "B");

	      //cout << "Efficiency histogram created!" << endl;

	      string title = ";" + x2DTitleVec[i_x2DVarVec] + ";" + y2DTitleVec[i_y2DVarVec] + ";Trigger Efficiency";
	      h_dataNum2D->SetTitle(title.c_str());
	      h_dataNum2D->GetXaxis()->SetNoExponent();
	      h_dataNum2D->GetXaxis()->SetMoreLogLabels();
	  
	      h_dataNum2D->GetXaxis()->SetTitleOffset(1.15);
	      h_dataNum2D->GetXaxis()->SetTitleFont(42);
	      h_dataNum2D->GetXaxis()->SetRangeUser(200,2200);

	      h_dataNum2D->GetXaxis()->SetNoExponent();
	      h_dataNum2D->GetXaxis()->SetMoreLogLabels();

	      h_dataNum2D->GetYaxis()->SetTitleOffset(1.25);//0.9);
	      h_dataNum2D->GetYaxis()->SetTitleFont(42);
	      h_dataNum2D->GetYaxis()->SetRangeUser(0,400);

	      h_dataNum2D->GetZaxis()->SetTitleOffset(0.7);
	      h_dataNum2D->GetZaxis()->SetTitleFont(42);
	      h_dataNum2D->GetZaxis()->SetRangeUser(0.1,1.0);
	  
	      h_dataNum2D->Draw("colz");
      
	      TLatex *   tex = new TLatex(0.12,0.83,"#font[62]{CMS} #font[52]{Preliminary}");
	      tex->SetNDC();
	      tex->SetTextFont(42);
	      tex->SetTextSize(0.0625);
	      tex->SetLineWidth(2);
	      tex->Draw();

	      tex = new TLatex(0.89,0.936, runLabel.c_str());
	      tex->SetNDC();
	      tex->SetTextAlign(31);
	      tex->SetTextFont(42);
	      // tex->SetTextSize(0.0625);
	      tex->SetTextSize(0.0575);
	      tex->SetLineWidth(2);
	      tex->Draw();
		  
	      tex = new TLatex(0.51,0.87,inFileLabel.c_str());
	      tex->SetNDC();
	      tex->SetTextAlign(13);
	      tex->SetTextFont(42);
	      tex->SetTextSize(0.032);
	      tex->SetLineWidth(2);
	      tex->Draw();

	      tex = new TLatex(0.51,0.82,cutPaveVec[i_cutVec].c_str());
	      tex->SetNDC();
	      tex->SetTextAlign(13);
	      tex->SetTextFont(42);
	      tex->SetTextSize(0.032);
	      tex->SetLineWidth(2);
	      tex->Draw();

	      //cout << "Cut vector drawn!" << endl;

	      string trigVec = "#splitline{" + numOrPave[i_numOrVec] + "}{over Mu50 or IsoMu24}";
	      //cout << "Trigger label," + trigVec;

	      tex = new TLatex(0.51,cutPaveVecY[i_cutVec],trigVec.c_str());//0.51,0.82
	      tex->SetNDC();
	      tex->SetTextAlign(13);
	      tex->SetTextFont(42);
	      tex->SetTextSize(0.032);
	      tex->SetLineWidth(2);
	      tex->Draw();

	      //cout << ", drawn." << endl;

	      gPad->RedrawAxis();
		  
	      c1237->SetLogz();

	      string savename = "trigEffStudies/run" + date + "/plots/" + numOrVec[i_numOrVec] + "numsMu50orIsoMu24denom_trigEff_" + y2DVarVec[i_y2DVarVec] + "vs" + x2DVarVec[i_x2DVarVec] + cutVec[i_cutVec] + ptCutVec[i_ptCutVec] + runLabelOutFile;
	      c1237->SaveAs(Form("%s.pdf",savename.c_str()));    
	  
	      h_dataNum2D->GetZaxis()->SetRangeUser(0.5,1.0);
	      c1237->SaveAs(Form("%s_zoomZaxis.pdf",savename.c_str()));    

	      h_dataNum2D->GetXaxis()->SetRangeUser(800,1100);
	      h_dataNum2D->GetYaxis()->SetRangeUser(0,250);
	      h_dataNum2D->GetZaxis()->SetRangeUser(0.89,1.0);
	      //h_dataNum2D->SetNdivisions(519,"Z");
	      //gPad->RedrawAxis();
	      c1237->SaveAs(Form("%s_zoom.pdf",savename.c_str()));    

	      h_dataNum2D->GetZaxis()->SetRangeUser(0.98,1.0);
	      c1237->SaveAs(Form("%s_zoomXYandExtraZ.pdf",savename.c_str()));    

	      h_dataNum2D->Delete();
	      //cout << "Nums deleted!" << endl;
	    }//end numerator loop
	    h_dataDenom2D->Delete();
	    //cout << "Denoms deleted!" << endl;
	  }//end 2D x variable loop
	}//end 2D y variable loop
      }//end plot 2D loop
    }//end tagging cut loop
  }//end pt cut loop
}//end plotEffMixed2D function

