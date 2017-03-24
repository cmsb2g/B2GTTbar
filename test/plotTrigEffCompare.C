// .L plotTrigEff.C+  
// plotTrigEff()

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

void plotEff(string, string, string, string, string, string);
void plotEffMixed(string, string, string, string, string, string, string, string, string, string);
void plotEffMixed2D(string, string, string, string, string, string, string);

void plotTrigEffCompare(){
  //function definitions: 
  //plotEff(string dataFile, string runLabel, string runLabelOutFile, string date, string PFHTmainTrigger, string denom)
  //void plotEffMixed(string dataFile1, string dataFile2, string fileLabel1, string fileLabel2, string runLabel, string runLabelOutFile, string date, string PFHTmainTrigger1, string PFHTmainTrigger2, string denom)
  //void plotEffMixed2D(string dataFile1, string dataFile2, string fileLabel1, string fileLabel2, string runLabel, string runLabelOutFile, string date){

  string date = "20170320";
  /*plotEff("outRunTrigEff_20161216_b2gtreeV4_JetHT_Run2016H-PromptReco_JSONnov14_all.root", "Run H Data (13 TeV)", "RunHdata", date,"PFHT900","Mu50orIsoMu24");
  plotEff("outRunTrigEff_20161216_b2gtreeV4_JetHT_Run2016BtoG-23Sep2016-v1_JSONnov14.root", "Runs B-G Data (13 TeV)", "RunsBtoGdata", date,"PFHT800","Mu50orIsoMu24");
  plotEff("outRunTrigEff_20161216_b2gtreeV4_JetHT_Run2016BtoG-23Sep2016-v1_JSONnov14.root", "Runs B-G Data (13 TeV)", "RunsBtoGdata", date,"PFHT900","Mu50orIsoMu24");
  plotEff("outRunTrigEff_20161216_b2gtreeV4_JetHT_JSONnov14_all.root", "36.2 fb^{-1}", "RunsBtoHdata", date, "PFHT900","Mu50orIsoMu24");
  plotEff("outRunTrigEff_20161216_b2gtreeV4_ZprimeToTT_M-3000_W-30_RunIISpring16MiniAODv2_reHLT.root", "Narrow 3 TeV Z'", "ZPN3", date, "PFHT800","Mu50orIsoMu24");
  plotEff("outRunTrigEff_20161216_b2gtreeV4_ZprimeToTT_M-3000_W-30_RunIISpring16MiniAODv2_reHLT.root", "Narrow 3 TeV Z'", "ZPN3", date, "PFHT900","Mu50orIsoMu24");
  plotEff("outRunTrigEff_20161206_b2gtreeV4_JetHT_Run2016H-PromptReco_JSONnov14_all.root", "Run H Data (13 TeV)", "RunHdata", date,"PFHT900","PFHT650");
  plotEff("outRunTrigEff_20161206_b2gtreeV4_JetHT_Run2016BtoG-23Sep2016-v1_JSONnov14.root", "Runs B-G Data (13 TeV)", "RunsBtoGdata", date,"PFHT900","PFHT650");
  plotEff("outRunTrigEff_20161206_b2gtreeV4_JetHT_Run2016BtoG-23Sep2016-v1_JSONnov14.root", "Runs B-G Data (13 TeV)", "RunsBtoGdata", date,"PFHT800","PFHT650");*/
  //plotEffMixed("outRunTrigEff_20161216_b2gtreeV4_JetHT_Run2016BtoG-23Sep2016-v1_JSONnov14.root", "outRunTrigEff_20161216_b2gtreeV4_JetHT_Run2016H-PromptReco_JSONnov14_all.root", "B-G", "H", "36.2 fb^{-1} (13 TeV)", "RunsBtoHdata", date, "PFHT800", "PFHT900", "Mu50orIsoMu24");
  //plotEffMixed("outRunTrigEff_20170313_b2gtreeV5_JetHT_Run2016BtoG-03Feb2017_JSONfinal.root", "outRunTrigEff_20170313_b2gtreeV5_JetHT_Run2016H-03Feb2017_JSONfinal.root", "B-G", "H", "36 fb^{-1} (13 TeV)", "RunsBtoHdata", date, "PFHT800", "PFHT900", "Mu50orIsoMu24");
  plotEffMixed2D("outRunTrigEff_20170320_b2gtreeV5_JetHT_Run2016BtoG-03Feb2017_JSONfinal.root", "outRunTrigEff_20170320_b2gtreeV5_JetHT_Run2016H-03Feb2017_JSONfinal.root", "B-G", "H", "36 fb^{-1} (13 TeV)", "RunsBtoHdata", date);
}
void plotEff(string dataFile, string runLabel, string runLabelOutFile, string date, string PFHTmainTrigger, string denom){
  gStyle->SetOptStat(0);
  gROOT->UseCurrentStyle();
  gROOT->ForceStyle();


  gROOT->Reset();
  gROOT->ForceStyle(); 
  TCanvas *c1237= new TCanvas("c1237","",1,1,745,640);

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
  c1237->SetRightMargin(0.1);
  c1237->SetTopMargin(0.08);
  c1237->SetBottomMargin(0.1);
  c1237->SetFrameFillStyle(0);
  c1237->SetFrameBorderMode(0);

  dataFile = "trigEffStudies/run"+date+"/"+dataFile;
  TFile * F_data =  new TFile( dataFile.c_str());

  //loop over numerators and denominators
  vector <string> numVec;
  vector <string> numDenomPaveVec;
  vector <Color_t> histColorVec;

  numVec.push_back(Form("%sorPFJet450",PFHTmainTrigger.c_str()));  numDenomPaveVec.push_back(Form("#splitline{PFJet450 or}{%s over %s}",PFHTmainTrigger.c_str(),denom.c_str())); histColorVec.push_back(kOrange-3);
  numVec.push_back(Form("%sorAK8PFJet450",PFHTmainTrigger.c_str()));  numDenomPaveVec.push_back(Form("#splitline{AK8PFJet450 or}{%s over %s}",PFHTmainTrigger.c_str(),denom.c_str())); histColorVec.push_back(kRed);
  numVec.push_back(Form("%sorPFJet360TrimMass30",PFHTmainTrigger.c_str()));  numDenomPaveVec.push_back(Form("#splitline{PFJet360TrimMass30 or}{%s over %s}",PFHTmainTrigger.c_str(),denom.c_str())); histColorVec.push_back(kGreen+2);
  numVec.push_back(Form("%sorAK8DiPFJet280_200_TrimMass30",PFHTmainTrigger.c_str()));  numDenomPaveVec.push_back(Form("#splitline{AK8DiPFJet280_200_Trim30}{or %s over %s}",PFHTmainTrigger.c_str(),denom.c_str())); histColorVec.push_back(kBlue);
  numVec.push_back(PFHTmainTrigger.c_str());  numDenomPaveVec.push_back(Form("%s over %s",PFHTmainTrigger.c_str(),denom.c_str())); histColorVec.push_back(kMagenta+3);

  TH1D *h_dataNum[numVec.size()];
  TH1D *h_dataDenom;

  //loop over x-axis Variables
  vector <string> xVarVec;
  vector <string> xTitleVec;
  xVarVec.push_back("sumJetPt"); xTitleVec.push_back("Jet 0 p_{T} + Jet 1 p_{T} [GeV]");
  xVarVec.push_back("HT"); xTitleVec.push_back("H_{T} [GeV]");

  //loop over min pt
  vector <string> ptCutVec;
  vector <string> ptCutPaveVec;
  ptCutVec.push_back("_minpt300"); ptCutPaveVec.push_back("p_{T} > 300 GeV");
  ptCutVec.push_back("_minpt400"); ptCutPaveVec.push_back("p_{T} > 400 GeV");
  ptCutVec.push_back("_minpt450"); ptCutPaveVec.push_back("p_{T} > 450 GeV");
  ptCutVec.push_back("_minpt500"); ptCutPaveVec.push_back("p_{T} > 500 GeV");

  //loop over cuts
  vector <string> cutVec;
  vector <string> cutPaveVec;
  cutVec.push_back("");
  cutVec.push_back("_2tagMass");
  cutVec.push_back("_2tagMass_2tagTau32");

  for (unsigned int l=0; l<ptCutVec.size(); l++ ){
    cutPaveVec.push_back(Form("AK8 jets, |#Delta#phi| > 2.1, %s",ptCutPaveVec[l].c_str()));
    cutPaveVec.push_back(Form("#splitline{AK8 jets, |#Delta#phi| > 2.1, %s,}{110 < M_{SD} < 210 GeV}",ptCutPaveVec[l].c_str()));
    cutPaveVec.push_back(Form("#splitline{AK8 jets, |#Delta#phi| > 2.1, %s,}{#splitline{110 < M_{SD} < 210 GeV,}{#tau_{32} < 0.69}}",ptCutPaveVec[l].c_str()));
      
    for (unsigned int j=0; j<xVarVec.size(); j++ ){
      for (unsigned int k=0; k<cutVec.size(); k++ ){	
	TLegend * leg;
	leg = new TLegend( 0.54, 0.18,0.58, 0.58); //0.51, 0.66,0.84, 0.83
	leg->SetBorderSize(0);
	leg->SetFillColor(0);
	leg->SetFillStyle(4000);
	leg->SetTextSize(0.032);      

	string denomHistName = "h_pass" + denom + "denom" + ptCutVec[l] + cutVec[k] + "_" + xVarVec[j];
	h_dataDenom = (TH1D*)F_data ->Get(denomHistName.c_str());
	cout << denomHistName << endl;
	h_dataDenom->Sumw2();
	
	for (unsigned int i=0; i<numVec.size(); i++ ){
 
	  string numHistName = "h_pass" + numVec[i] + "num" + denom + "denom" + ptCutVec[l] + cutVec[k] + "_" + xVarVec[j];
	  h_dataNum[i] = (TH1D*)F_data ->Get(numHistName.c_str());
	  cout << numHistName << endl;
	  h_dataNum[i]->Sumw2();
	  
	  h_dataNum[i]->Divide(h_dataNum[i], h_dataDenom, 1, 1, "B");
	  
	  string title = ";" + xTitleVec[j]  + ";Trigger Efficiency";
	  h_dataNum[i]->SetTitle(title.c_str());
	  h_dataNum[i]->GetXaxis()->SetNoExponent();
	  h_dataNum[i]->GetXaxis()->SetMoreLogLabels();
	  
	  h_dataNum[i]->GetXaxis()->SetTitleOffset(1.15);
	  h_dataNum[i]->GetXaxis()->SetTitleFont(42);
	  h_dataNum[i]->GetXaxis()->SetRangeUser(200,2200);

	  h_dataNum[i]->GetYaxis()->SetTitleOffset(1.17);//0.9);
	  h_dataNum[i]->GetYaxis()->SetTitleFont(42);
	  h_dataNum[i]->GetYaxis()->SetRangeUser(0,1.25);
	  
	  h_dataNum[i]->GetZaxis()->SetLabelFont(42);
	  h_dataNum[i]->GetZaxis()->SetLabelSize(0.0425);
	  h_dataNum[i]->GetZaxis()->SetTitleSize(0.0475);
	  h_dataNum[i]->GetZaxis()->SetTitleFont(42);
	  
	  h_dataNum[i]->SetLineWidth(2);
	  h_dataNum[i]->SetLineColor(histColorVec[i]);
	  
	  if (i==0) h_dataNum[i]->Draw("EP");
	  else h_dataNum[i]->Draw("EPSAME");

	  leg->AddEntry( h_dataNum[i]   , numDenomPaveVec[i].c_str() , "LP" );
	}

	leg->Draw("same");
      
	TLatex *   tex = new TLatex(0.18,0.83,"#font[62]{CMS} #font[52]{Preliminary}");
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.0625);
	tex->SetLineWidth(2);
	tex->Draw();
	tex = new TLatex(0.96,0.936, runLabel.c_str());
	tex->SetNDC();
	tex->SetTextAlign(31);
	tex->SetTextFont(42);
	// tex->SetTextSize(0.0625);
	tex->SetTextSize(0.0575);
	tex->SetLineWidth(2);
	tex->Draw();
	/*tex = new TLatex(0.64,0.64, "Data");
	  tex->SetNDC();
	  tex->SetTextAlign(13);
	  tex->SetTextFont(42);
	  tex->SetTextSize(0.032);
	  tex->SetLineWidth(2);
	  tex->Draw();
	  tex = new TLatex(0.64,0.41, numDenomPaveVec2[i].c_str());
	  tex->SetNDC();
	  tex->SetTextAlign(13);
	  tex->SetTextFont(42);
	  tex->SetTextSize(0.032);
	  tex->SetLineWidth(2);
	  tex->Draw();*/
	tex = new TLatex(0.57,0.87, cutPaveVec[k].c_str());
	tex->SetNDC();
	tex->SetTextAlign(13);
	tex->SetTextFont(42);
	tex->SetTextSize(0.032);
	tex->SetLineWidth(2);
	tex->Draw();
	
	gPad->RedrawAxis();
	
	string savename = "trigEffStudies/run" + date + "/" + PFHTmainTrigger + "nums" + denom + "denom_trigEffvs" + xVarVec[j] + cutVec[k] + "_" + ptCutVec[l] + runLabelOutFile + ".pdf";
	string savenameRoot = "trigEffStudies/run" + date + "/" + PFHTmainTrigger + "nums" + denom + "denom_trigEffvs" + xVarVec[j] + cutVec[k] + "_" + ptCutVec[l] + runLabelOutFile + ".root";
	c1237->SaveAs(savename.c_str());    
	c1237->SaveAs(savenameRoot.c_str());

	savename = "trigEffStudies/run" + date + "/" + PFHTmainTrigger + "nums" + denom + "denom_trigEffvs" + xVarVec[j] + cutVec[k] + "_" + ptCutVec[l] + runLabelOutFile + "_zoom.pdf";
	h_dataNum[0]->GetXaxis()->SetRangeUser(900,1200);
	h_dataNum[0]->GetYaxis()->SetRangeUser(0.8,1.1);
	leg->Delete();
	c1237->SaveAs(savename.c_str());    

	for (unsigned int i=0; i<numVec.size(); i++ ) h_dataNum[i]->Delete();
	h_dataDenom->Delete();
      }
    }
    cutPaveVec.clear();
  }
}

void plotEffMixed(string dataFile1, string dataFile2, string fileLabel1, string fileLabel2, string runLabel, string runLabelOutFile, string date, string PFHTmainTrigger1, string PFHTmainTrigger2, string denom){
  gStyle->SetOptStat(0);
  gROOT->UseCurrentStyle();
  gROOT->ForceStyle();


  gROOT->Reset();
  gROOT->ForceStyle(); 
  TCanvas *c1237= new TCanvas("c1237","",1,1,745,640);

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
  c1237->SetLeftMargin(0.14);
  c1237->SetRightMargin(0.04);
  c1237->SetTopMargin(0.08);
  c1237->SetBottomMargin(0.15);
  c1237->SetFrameFillStyle(0);
  c1237->SetFrameBorderMode(0);

  dataFile1 = "trigEffStudies/run"+date+"/"+dataFile1;
  TFile * F_data1 =  new TFile( dataFile1.c_str());
  dataFile2 = "trigEffStudies/run"+date+"/"+dataFile2;
  TFile * F_data2 =  new TFile( dataFile2.c_str());

  //loop over numerators and denominators
  vector <string> numVec1;
  vector <string> numVec2;
  vector <string> numDenomPaveVec;
  vector <Color_t> histColorVec;

  //numVec1.push_back(Form("%sorPFJet450",PFHTmainTrigger1.c_str())); numVec2.push_back(Form("%sorPFJet450",PFHTmainTrigger2.c_str())); numDenomPaveVec.push_back(Form("#splitline{PFJet450 or %s (%s)}{for Runs %s (Run %s) over %s}",PFHTmainTrigger1.c_str(),PFHTmainTrigger2.c_str(),fileLabel1.c_str(),fileLabel2.c_str(),denom.c_str())); histColorVec.push_back(kOrange-3);
  numVec1.push_back(PFHTmainTrigger1.c_str()); numVec2.push_back(Form("%sorAK8PFJet450",PFHTmainTrigger2.c_str())); numDenomPaveVec.push_back(Form("#splitline{[%s] (AK8PFJet450 or %s)}{over %s for [Runs %s] (Run %s)}",PFHTmainTrigger1.c_str(),PFHTmainTrigger2.c_str(),denom.c_str(),fileLabel1.c_str(),fileLabel2.c_str())); histColorVec.push_back(kBlue);
  numVec1.push_back(Form("%sorAK8PFJet450",PFHTmainTrigger1.c_str())); numVec2.push_back(Form("%sorAK8PFJet450",PFHTmainTrigger2.c_str())); numDenomPaveVec.push_back(Form("#splitline{AK8PFJet450 or [%s] (%s)}{over %s for [Runs %s] (Run %s)}",PFHTmainTrigger1.c_str(),PFHTmainTrigger2.c_str(),denom.c_str(),fileLabel1.c_str(),fileLabel2.c_str())); histColorVec.push_back(kRed);
  //numVec1.push_back(Form("%sorAK8DiPFJet280_200_TrimMass30",PFHTmainTrigger1.c_str())); numVec2.push_back(Form("%sorAK8PFJet450",PFHTmainTrigger2.c_str())); numDenomPaveVec.push_back(Form("#splitline{#splitline{[AK8DiPFJet280_200_TrimMass30 or %s]}{(AK8PFJet450 or %s)}}{over %s for [Runs %s] (Run %s)}",PFHTmainTrigger1.c_str(),PFHTmainTrigger2.c_str(),denom.c_str(),fileLabel1.c_str(),fileLabel2.c_str())); histColorVec.push_back(kOrange-3);
  //numVec1.push_back(Form("%sorPFJet360TrimMass30",PFHTmainTrigger1.c_str())); numVec2.push_back(Form("%sorPFJet360TrimMass30",PFHTmainTrigger2.c_str())); numDenomPaveVec.push_back(Form("#splitline{PFJet360TrimMass30 or %s (%s)}{for Runs %s (Run %s) over %s}",PFHTmainTrigger1.c_str(),PFHTmainTrigger2.c_str(),fileLabel1.c_str(),fileLabel2.c_str(),denom.c_str())); histColorVec.push_back(kGreen+2);
  //numVec1.push_back(PFHTmainTrigger1.c_str()); numVec2.push_back(Form("%sorAK8DiPFJet280_200_TrimMass30",PFHTmainTrigger2.c_str())); numDenomPaveVec.push_back(Form("#splitline{[%s] (AK8DiPFJet280_200_TrimMass30 or %s)}{over %s for [Runs %s] (Run %s)}",PFHTmainTrigger1.c_str(),PFHTmainTrigger2.c_str(),denom.c_str(),fileLabel1.c_str(),fileLabel2.c_str())); histColorVec.push_back(kMagenta+3);
  //numVec1.push_back(Form("%sorAK8DiPFJet280_200_TrimMass30",PFHTmainTrigger1.c_str())); numVec2.push_back(Form("%sorAK8DiPFJet280_200_TrimMass30",PFHTmainTrigger2.c_str())); numDenomPaveVec.push_back(Form("#splitline{AK8DiPFJet280_200_TrimMass30 or [%s] (%s)}{over %s for [Runs %s] (Run %s)}",PFHTmainTrigger1.c_str(),PFHTmainTrigger2.c_str(),denom.c_str(),fileLabel1.c_str(),fileLabel2.c_str())); histColorVec.push_back(kBlue);
  //numVec1.push_back(Form("%sorAK8PFJet450",PFHTmainTrigger1.c_str())); numVec2.push_back(Form("%sorAK8DiPFJet280_200_TrimMass30",PFHTmainTrigger2.c_str())); numDenomPaveVec.push_back(Form("#splitline{#splitline{[AK8PFJet450 or %s]}{(AK8DiPFJet280_200_Trim30 or %s)}}{over %s for [Runs %s] (Run %s)}",PFHTmainTrigger1.c_str(),PFHTmainTrigger2.c_str(),denom.c_str(),fileLabel1.c_str(),fileLabel2.c_str())); histColorVec.push_back(kCyan+2);
    //numVec1.push_back(PFHTmainTrigger1.c_str()); numVec2.push_back(PFHTmainTrigger2.c_str()); numDenomPaveVec.push_back(Form("#splitline{%s (%s)}{for Runs %s (Run %s) over %s}",PFHTmainTrigger1.c_str(),PFHTmainTrigger2.c_str(),fileLabel1.c_str(),fileLabel2.c_str(),denom.c_str())); histColorVec.push_back(kMagenta+3);

  TH1D *h_dataNum[numVec1.size()];
  TH1D *h_dataDenom1;
  TH1D *h_dataDenom2;

  //loop over x-axis Variables
  vector <string> xVarVec;
  vector <string> xTitleVec;
  xVarVec.push_back("sumJetPt"); xTitleVec.push_back("Jet 0 p_{T} + Jet 1 p_{T} [GeV]");
  xVarVec.push_back("HT"); xTitleVec.push_back("H_{T} [GeV]");

  //loop over min pt
  vector <string> ptCutVec;
  vector <string> ptCutPaveVec;
  ptCutVec.push_back("_minpt300"); ptCutPaveVec.push_back("p_{T} > 300 GeV");
  ptCutVec.push_back("_minpt400"); ptCutPaveVec.push_back("p_{T} > 400 GeV");
  ptCutVec.push_back("_minpt450"); ptCutPaveVec.push_back("p_{T} > 450 GeV");
  ptCutVec.push_back("_minpt500"); ptCutPaveVec.push_back("p_{T} > 500 GeV");

  //loop over cuts
  vector <string> cutVec;
  vector <string> cutPaveVec;
  cutVec.push_back("");
  cutVec.push_back("_1tagMass");
  cutVec.push_back("_2tagMass");
  //cutVec.push_back("_2tagMass_2tagTau32");

  for (unsigned int l=0; l<ptCutVec.size(); l++ ){
    cutPaveVec.push_back(Form("AK8 jets, |#Delta#phi| > 2.1, %s",ptCutPaveVec[l].c_str()));
    cutPaveVec.push_back(Form("#splitline{AK8 jets, |#Delta#phi| > 2.1, %s,}{1+ jet: 110 < M_{SD} < 210 GeV}",ptCutPaveVec[l].c_str()));
    cutPaveVec.push_back(Form("#splitline{AK8 jets, |#Delta#phi| > 2.1, %s,}{Both jets: 110 < M_{SD} < 210 GeV}",ptCutPaveVec[l].c_str()));
    //cutPaveVec.push_back(Form("#splitline{AK8 jets, |#Delta#phi| > 2.1, %s,}{#splitline{110 < M_{SD} < 210 GeV,}{#tau_{32} < 0.69}}",ptCutPaveVec[l].c_str()));
      
    for (unsigned int j=0; j<xVarVec.size(); j++ ){
      for (unsigned int k=0; k<cutVec.size(); k++ ){	
	TLegend * leg;
	leg = new TLegend( 0.37, 0.18,0.55, 0.63); //0.51, 0.66,0.84, 0.83
	leg->SetBorderSize(0);
	leg->SetFillColor(0);
	leg->SetFillStyle(4000);
	leg->SetTextSize(0.032);      

	//denominator histograms
	string denomHistName = "h_pass" + denom + "denom" + ptCutVec[l] + cutVec[k] + "_" + xVarVec[j];
	
	h_dataDenom1 = (TH1D*)F_data1 ->Get(denomHistName.c_str());
	h_dataDenom2 = (TH1D*)F_data2 ->Get(denomHistName.c_str());
	h_dataDenom1->Sumw2();
	h_dataDenom2->Sumw2();

	h_dataDenom1->Add(h_dataDenom2);

	for (unsigned int i=0; i<numVec1.size(); i++ ){
 
	  string numHistName1 = "h_pass" + numVec1[i] + "num" + denom + "denom" + ptCutVec[l] + cutVec[k] + "_" + xVarVec[j];
	  cout << numHistName1 << endl;
	  TH1D *h_dataNum1 = (TH1D*)F_data1 ->Get(numHistName1.c_str());
	  h_dataNum1->Sumw2();

	  string numHistName2 = "h_pass" + numVec2[i] + "num" + denom + "denom" + ptCutVec[l] + cutVec[k] + "_" + xVarVec[j];
	  cout << numHistName2 << endl;
	  TH1D *h_dataNum2 = (TH1D*)F_data2 ->Get(numHistName2.c_str());
	  h_dataNum2->Sumw2();
	  
	  h_dataNum2->Add(h_dataNum1);
	  h_dataNum2->Divide(h_dataNum2, h_dataDenom1, 1, 1, "B");

	  string numHistName = "h_pass" + numVec1[i] + "num" + numVec2[i] + "num" + denom + "denom" + ptCutVec[l] + cutVec[k] + "_" + xVarVec[j];
	  h_dataNum[i] = (TH1D*) h_dataNum2->Clone(numHistName.c_str());

	  string title = ";" + xTitleVec[j]  + ";Trigger Efficiency";
	  h_dataNum[i]->SetTitle(title.c_str());
	  h_dataNum[i]->GetXaxis()->SetNoExponent();
	  h_dataNum[i]->GetXaxis()->SetMoreLogLabels();
	  
	  h_dataNum[i]->GetXaxis()->SetTitleOffset(1.15);
	  h_dataNum[i]->GetXaxis()->SetTitleFont(42);
	  h_dataNum[i]->GetXaxis()->SetRangeUser(200,2200);

	  h_dataNum[i]->GetYaxis()->SetTitleOffset(1.17);//0.9);
	  h_dataNum[i]->GetYaxis()->SetTitleFont(42);
	  h_dataNum[i]->GetYaxis()->SetRangeUser(0,1.25);
	  
	  h_dataNum[i]->GetZaxis()->SetLabelFont(42);
	  h_dataNum[i]->GetZaxis()->SetLabelSize(0.0425);
	  h_dataNum[i]->GetZaxis()->SetTitleSize(0.0475);
	  h_dataNum[i]->GetZaxis()->SetTitleFont(42);
	  
	  h_dataNum[i]->SetLineWidth(2);
	  h_dataNum[i]->SetLineColor(histColorVec[i]);
	  
	  if (i==0) h_dataNum[i]->Draw("EP");
	  else h_dataNum[i]->Draw("EPSAME");

	  leg->AddEntry( h_dataNum[i]   , numDenomPaveVec[i].c_str() , "LP" );

	  h_dataNum1->Delete();
	  h_dataNum2->Delete();
	}

	leg->Draw("same");
      
	TLatex *   tex = new TLatex(0.18,0.83,"#font[62]{CMS} #font[52]{Preliminary}");
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.0625);
	tex->SetLineWidth(2);
	tex->Draw();
	tex = new TLatex(0.96,0.936, runLabel.c_str());
	tex->SetNDC();
	tex->SetTextAlign(31);
	tex->SetTextFont(42);
	// tex->SetTextSize(0.0625);
	tex->SetTextSize(0.0575);
	tex->SetLineWidth(2);
	tex->Draw();
	/*tex = new TLatex(0.64,0.64, "Data");
	  tex->SetNDC();
	  tex->SetTextAlign(13);
	  tex->SetTextFont(42);
	  tex->SetTextSize(0.032);
	  tex->SetLineWidth(2);
	  tex->Draw();
	  tex = new TLatex(0.64,0.41, numDenomPaveVec2[i].c_str());
	  tex->SetNDC();
	  tex->SetTextAlign(13);
	  tex->SetTextFont(42);
	  tex->SetTextSize(0.032);
	  tex->SetLineWidth(2);
	  tex->Draw();*/
	tex = new TLatex(0.57,0.87, cutPaveVec[k].c_str());
	tex->SetNDC();
	tex->SetTextAlign(13);
	tex->SetTextFont(42);
	tex->SetTextSize(0.032);
	tex->SetLineWidth(2);
	tex->Draw();
	
	gPad->RedrawAxis();
	
	string savename = "trigEffStudies/run" + date + "/Runs" + fileLabel1 + PFHTmainTrigger1 + "numsRun" + fileLabel2 + PFHTmainTrigger2 + "nums" + denom + "denom_trigEffvs" + xVarVec[j] + cutVec[k] + ptCutVec[l] + runLabelOutFile + ".pdf";
	string savenameRoot = "trigEffStudies/run" + date + "/Runs" + fileLabel1 + PFHTmainTrigger1 + "numsRun" + fileLabel2 + PFHTmainTrigger2 + "nums" + denom + "denom_trigEffvs" + xVarVec[j] + cutVec[k] + ptCutVec[l] + runLabelOutFile + ".root";
	c1237->SaveAs(savename.c_str());    
	c1237->SaveAs(savenameRoot.c_str());

	savename = "trigEffStudies/run" + date + "/Runs" + fileLabel1 + PFHTmainTrigger1 + "numsRun" + fileLabel2 + PFHTmainTrigger2 + "nums" + denom + "denom_trigEffvs" + xVarVec[j] + cutVec[k] + ptCutVec[l] + runLabelOutFile + "_zoom.pdf";
	h_dataNum[0]->GetXaxis()->SetRangeUser(800,1100);
	h_dataNum[0]->GetYaxis()->SetRangeUser(0.7,1.1);
	//leg->Delete();
	c1237->SaveAs(savename.c_str());    

	for (unsigned int i=0; i<numVec2.size(); i++ ) h_dataNum[i]->Delete();

	h_dataDenom1->Delete();
	h_dataDenom2->Delete();

	//cout<<"Finishing iteration "<<k<<" of cutvec loop"<<endl;
      }
    }
    cutPaveVec.clear();
  }
}
void plotEffMixed2D(string dataFile1, string dataFile2, string fileLabel1, string fileLabel2, string runLabel, string runLabelOutFile, string date){
  gStyle->SetOptStat(0);
  gROOT->UseCurrentStyle();
  gROOT->ForceStyle();


  gROOT->Reset();
  gROOT->ForceStyle(); 
  TCanvas *c1237= new TCanvas("c1237","",1,1,745,640);

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

  dataFile1 = "trigEffStudies/run"+date+"/"+dataFile1;
  TFile * F_data1 =  new TFile( dataFile1.c_str());
  dataFile2 = "trigEffStudies/run"+date+"/"+dataFile2;
  TFile * F_data2 =  new TFile( dataFile2.c_str());

  vector <string> numVecBtoG;
  vector <string> numVecH;
  vector <string> numOrVec;

  vector <string> xVarVec;
  vector <string> xTitleVec;
  vector <string> yVarVec;
  vector <string> yTitleVec;

  vector <string> ptCutVec;
  vector <string> ptCutPaveVec;
  vector <string> cutVec;

  numVecBtoG.push_back("PFHT700TrimMass50");
  numVecBtoG.push_back("PFHT800");

  numVecH.push_back("PFHT700TrimMass50");
  numVecH.push_back("PFHT900");

  numOrVec.push_back("AK8PFJet450");
  numOrVec.push_back("PFJet360TrimMass30");

  //xVarVec.push_back("sumJetPt"); xTitleVec.push_back("Jet 0 p_{T} + Jet 1 p_{T} [GeV]");
  xVarVec.push_back("HT"); xTitleVec.push_back("H_{T} [GeV]");

  //yVarVec.push_back("JetMass"); yTitleVec.push_back("Ungroomed Jet Mass [GeV]");
  yVarVec.push_back("JetSoftDropMass"); yTitleVec.push_back("CHS Soft Drop Mass [GeV]");
  yVarVec.push_back("JetPUPPISoftDropMass"); yTitleVec.push_back("PUPPI Soft Drop Mass [GeV]");

  ptCutVec.push_back("_minpt400"); ptCutPaveVec.push_back("p_{T} > 400 GeV");
  ptCutVec.push_back("_minpt450"); ptCutPaveVec.push_back("p_{T} > 450 GeV");
  ptCutVec.push_back("_minpt500"); ptCutPaveVec.push_back("p_{T} > 500 GeV");
  
  cutVec.push_back("");
  cutVec.push_back("_1tagMass");
  //cutVec.push_back("_2tagMass");
  cutVec.push_back("_1tagPUPPIMass");
  //cutVec.push_back("_2tagPUPPIMass");

  unsigned int numOrVecSize = numOrVec.size() + 1;
  TH2D *h_dataDenom1;
  TH2D *h_dataDenom2;
  TH2D *h_dataNum1;
  TH2D *h_dataNum2;
	
  for (unsigned int i_ptCutVec=0; i_ptCutVec<ptCutVec.size(); i_ptCutVec++){    

    vector <string> cutPaveVec;
    cutPaveVec.push_back(Form("AK8 jets, |#Delta#phi| > 2.1, %s",ptCutPaveVec[i_ptCutVec].c_str()));
    cutPaveVec.push_back(Form("#splitline{AK8 jets, |#Delta#phi| > 2.1, %s,}{1+ jet: 110 < M_{SD} < 210 GeV}",ptCutPaveVec[i_ptCutVec].c_str()));
    //cutPaveVec.push_back(Form("#splitline{AK8 jets, |#Delta#phi| > 2.1, %s,}{Both jets: 110 < M_{SD} < 210 GeV}",ptCutPaveVec[i_ptCutVec].c_str()));
    cutPaveVec.push_back(Form("#splitline{AK8 jets, |#Delta#phi| > 2.1, %s,}{1+ jet: 110 < M_{PUPPI + SD} < 210 GeV}",ptCutPaveVec[i_ptCutVec].c_str()));
    //cutPaveVec.push_back(Form("#splitline{AK8 jets, |#Delta#phi| > 2.1, %s,}{Both jets: 110 < M_{PUPPI + SD} < 210 GeV}",ptCutPaveVec[i_ptCutVec].c_str()));
    
    for (unsigned int i_cutVec=0; i_cutVec<cutVec.size(); i_cutVec++){    
      for (unsigned int i_yVarVec=0; i_yVarVec<yVarVec.size(); i_yVarVec++){    
	for (unsigned int i_xVarVec=0; i_xVarVec<xVarVec.size(); i_xVarVec++){    

	  //denominator histograms
	  string endHistName = "Mu50orIsoMu24denom" + ptCutVec[i_ptCutVec] + cutVec[i_cutVec] + "_" + yVarVec[i_yVarVec] + "vs" + xVarVec[i_xVarVec];
	  string denomHistName = "h_pass" + endHistName;
	  h_dataDenom1 = (TH2D*)F_data1 ->Get(denomHistName.c_str());
	  h_dataDenom2 = (TH2D*)F_data2 ->Get(denomHistName.c_str());

	  h_dataDenom1->Sumw2();
	  h_dataDenom2->Sumw2();
	  h_dataDenom1->Add(h_dataDenom2);

	  for (unsigned int i_numVecBtoG=0; i_numVecBtoG<numVecBtoG.size(); i_numVecBtoG++){    
	    for (unsigned int i_numOrVecBtoG=0; i_numOrVecBtoG<numOrVecSize; i_numOrVecBtoG++){    

	      string PFHTmainTrigger1;
	      string trigVec1;
	      if (i_numOrVecBtoG == numOrVec.size()){
		PFHTmainTrigger1 = numVecBtoG[i_numVecBtoG];
		trigVec1 = numVecBtoG[i_numVecBtoG];
	      }
	      else{
		PFHTmainTrigger1 = numVecBtoG[i_numVecBtoG] + "or" + numOrVec[i_numOrVecBtoG];
		trigVec1 = numVecBtoG[i_numVecBtoG] + " or " + numOrVec[i_numOrVecBtoG];
	      }
	      string numHistName1 = "h_pass" + PFHTmainTrigger1 + "num" + endHistName;

	      h_dataNum1 = (TH2D*)F_data1 ->Get(numHistName1.c_str());
	      h_dataNum1->Sumw2();
 
	      for (unsigned int i_numVecH=0; i_numVecH<numVecH.size(); i_numVecH++){
		for (unsigned int i_numOrVecH=0; i_numOrVecH<numOrVecSize; i_numOrVecH++){

		  string PFHTmainTrigger2;
		  string trigVec2;
		  if (i_numOrVecH == numOrVec.size()){
		    PFHTmainTrigger2 = numVecH[i_numVecH];
		    trigVec2 = numVecH[i_numVecH];
		  }
		  else{
		    PFHTmainTrigger2 = numVecH[i_numVecH] + "or" + numOrVec[i_numOrVecH];
		    trigVec2 = numVecH[i_numVecH] + " or " + numOrVec[i_numOrVecH];
		  }
		  string numHistName2 = "h_pass" + PFHTmainTrigger2 + "num" + endHistName;

		  h_dataNum2 = (TH2D*)F_data2 ->Get(numHistName2.c_str());
		  h_dataNum2->Sumw2();

		  h_dataNum2->Add(h_dataNum1);
		  h_dataNum2->Divide(h_dataNum2, h_dataDenom1, 1, 1, "B");

		  string title = ";" + xTitleVec[i_xVarVec] + ";" + yTitleVec[i_yVarVec] + ";Trigger Efficiency";
		  h_dataNum2->SetTitle(title.c_str());
		  h_dataNum2->GetXaxis()->SetNoExponent();
		  h_dataNum2->GetXaxis()->SetMoreLogLabels();
	  
		  h_dataNum2->GetXaxis()->SetTitleOffset(1.15);
		  h_dataNum2->GetXaxis()->SetTitleFont(42);
		  h_dataNum2->GetXaxis()->SetRangeUser(200,2200);

		  h_dataNum2->GetXaxis()->SetNoExponent();
		  h_dataNum2->GetXaxis()->SetMoreLogLabels();

		  h_dataNum2->GetYaxis()->SetTitleOffset(1.25);//0.9);
		  h_dataNum2->GetYaxis()->SetTitleFont(42);
		  h_dataNum2->GetYaxis()->SetRangeUser(0,400);

		  h_dataNum2->GetZaxis()->SetTitleOffset(0.7);
		  h_dataNum2->GetZaxis()->SetTitleFont(42);
		  h_dataNum2->GetZaxis()->SetRangeUser(0.1,1.0);
	  
		  h_dataNum2->Draw("colz");
      
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
		  
		  tex = new TLatex(0.51,0.87,cutPaveVec[i_cutVec].c_str());
		  tex->SetNDC();
		  tex->SetTextAlign(13);
		  tex->SetTextFont(42);
		  tex->SetTextSize(0.032);
		  tex->SetLineWidth(2);
		  tex->Draw();

		  string trigVec = "#splitline{#splitline{[" + trigVec1 + "]}{(" + trigVec2 + ")}}{#splitline{over Mu50 or IsoMu24}{for [Runs " + fileLabel1 + "] (Run " + fileLabel2 + ")}}";
		  tex = new TLatex(0.51,0.82,trigVec.c_str());
		  tex->SetNDC();
		  tex->SetTextAlign(13);
		  tex->SetTextFont(42);
		  tex->SetTextSize(0.032);
		  tex->SetLineWidth(2);
		  tex->Draw();

		  gPad->RedrawAxis();
		  
		  c1237->SetLogz();

		  string savename = "trigEffStudies/run" + date + "/Runs" + fileLabel1 + PFHTmainTrigger1 + "Run" + fileLabel2 + PFHTmainTrigger2 + "numsMu50orIsoMu24denom_trigEff_" + yVarVec[i_yVarVec] + "vs" + xVarVec[i_xVarVec] + cutVec[i_cutVec] + ptCutVec[i_ptCutVec] + runLabelOutFile + ".pdf";
		  string savenameRoot = "trigEffStudies/run" + date + "/Runs" + fileLabel1 + PFHTmainTrigger1 + "Run" + fileLabel2 + PFHTmainTrigger2 + "numsMu50orIsoMu24denom_trigEff_" + yVarVec[i_yVarVec] + "vs" + xVarVec[i_xVarVec] + cutVec[i_cutVec] + ptCutVec[i_ptCutVec] + runLabelOutFile + ".root";
		  c1237->SaveAs(savename.c_str());    
		  c1237->SaveAs(savenameRoot.c_str());

		  savename = "trigEffStudies/run" + date + "/Runs" + fileLabel1 + PFHTmainTrigger1 + "Run" + fileLabel2 + PFHTmainTrigger2 + "numsMu50orIsoMu24denom_trigEff_" + yVarVec[i_yVarVec] + "vs" + xVarVec[i_xVarVec] + cutVec[i_cutVec] + ptCutVec[i_ptCutVec] + runLabelOutFile + "_zoom.pdf";
		  h_dataNum2->GetXaxis()->SetRangeUser(800,1100);
		  h_dataNum2->GetYaxis()->SetRangeUser(0,250);
		  h_dataNum2->GetZaxis()->SetRangeUser(0.89,1.0);
		  //leg->Delete();
		  c1237->SaveAs(savename.c_str());    

		  h_dataNum2->Delete();
		}//end Run H secondary numerator loop
	      }//end Run H primary numerator loop
	      h_dataNum1->Delete();
	    }//end Runs B-G secondary numerator loop 
	  }//end Runs B-G primary numerator loop
	  h_dataDenom1->Delete();
	  h_dataDenom2->Delete();
	}//end x variable loop
      }//end y variable loop
    }//end mass cut loop
  }//end pt cut loop
}//end plotEffMixed2D function

