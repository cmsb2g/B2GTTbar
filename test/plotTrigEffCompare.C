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

void plotTrigEffCompare(){
  //function definition: plotEff(string dataFile, string runLabel, string runLabelOutFile, string date, string PFHTmainTrigger, string denom)
  string date = "20161216";
  plotEff("outRunTrigEff_20161216_b2gtreeV4_JetHT_Run2016H-PromptReco_JSONnov14_all.root", "Run H Data (13 TeV)", "RunHdata", date,"PFHT900","Mu50orIsoMu24");
  plotEff("outRunTrigEff_20161216_b2gtreeV4_JetHT_Run2016BtoG-23Sep2016-v1_JSONnov14.root", "Runs B-G Data (13 TeV)", "RunsBtoGdata", date,"PFHT800","Mu50orIsoMu24");
  plotEff("outRunTrigEff_20161216_b2gtreeV4_JetHT_Run2016BtoG-23Sep2016-v1_JSONnov14.root", "Runs B-G Data (13 TeV)", "RunsBtoGdata", date,"PFHT900","Mu50orIsoMu24");
  plotEff("outRunTrigEff_20161216_b2gtreeV4_JetHT_JSONnov14_all.root", "36.2 fb^{-1}", "RunsBtoHdata", date, "PFHT900","Mu50orIsoMu24");
  plotEff("outRunTrigEff_20161216_b2gtreeV4_ZprimeToTT_M-3000_W-30_RunIISpring16MiniAODv2_reHLT.root", "Narrow 3 TeV Z'", "ZPN3", date, "PFHT800","Mu50orIsoMu24");
  plotEff("outRunTrigEff_20161216_b2gtreeV4_ZprimeToTT_M-3000_W-30_RunIISpring16MiniAODv2_reHLT.root", "Narrow 3 TeV Z'", "ZPN3", date, "PFHT900","Mu50orIsoMu24");
  /*plotEff("outRunTrigEff_20161206_b2gtreeV4_JetHT_Run2016H-PromptReco_JSONnov14_all.root", "Run H Data (13 TeV)", "RunHdata", date,"PFHT900","PFHT650");
  plotEff("outRunTrigEff_20161206_b2gtreeV4_JetHT_Run2016BtoG-23Sep2016-v1_JSONnov14.root", "Runs B-G Data (13 TeV)", "RunsBtoGdata", date,"PFHT900","PFHT650");
  plotEff("outRunTrigEff_20161206_b2gtreeV4_JetHT_Run2016BtoG-23Sep2016-v1_JSONnov14.root", "Runs B-G Data (13 TeV)", "RunsBtoGdata", date,"PFHT800","PFHT650");*/
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
  c1237->SetLeftMargin(0.14);
  c1237->SetRightMargin(0.04);
  c1237->SetTopMargin(0.08);
  c1237->SetBottomMargin(0.15);
  c1237->SetFrameFillStyle(0);
  c1237->SetFrameBorderMode(0);

  dataFile = "trigEffStudies/run"+date+"/"+dataFile;
  TFile * F_data =  new TFile( dataFile.c_str());

  //loop over numerators and denominators
  vector <string> numVec;
  vector <string> denomVec;  
  vector <string> numDenomPaveVec;
  vector <Color_t> histColorVec;

  numVec.push_back(Form("%sorPFJet450",PFHTmainTrigger.c_str()));  denomVec.push_back(denom.c_str()); numDenomPaveVec.push_back(Form("#splitline{PFJet450 or}{%s over %s}",PFHTmainTrigger.c_str(),denom.c_str())); histColorVec.push_back(kOrange-3);
  numVec.push_back(Form("%sorAK8PFJet450",PFHTmainTrigger.c_str()));  denomVec.push_back(denom.c_str()); numDenomPaveVec.push_back(Form("#splitline{AK8PFJet450 or}{%s over %s}",PFHTmainTrigger.c_str(),denom.c_str())); histColorVec.push_back(kRed);
  numVec.push_back(Form("%sorPFJet360TrimMass30",PFHTmainTrigger.c_str()));  denomVec.push_back(denom.c_str()); numDenomPaveVec.push_back(Form("#splitline{PFJet360TrimMass30 or}{%s over %s}",PFHTmainTrigger.c_str(),denom.c_str())); histColorVec.push_back(kGreen+2);
  numVec.push_back(Form("%sorAK8DiPFJet280_200_TrimMass30",PFHTmainTrigger.c_str()));  denomVec.push_back(denom.c_str()); numDenomPaveVec.push_back(Form("#splitline{AK8DiPFJet280_200_Trim30}{or %s over %s}",PFHTmainTrigger.c_str(),denom.c_str())); histColorVec.push_back(kBlue);
  numVec.push_back(PFHTmainTrigger.c_str());  denomVec.push_back(denom.c_str()); numDenomPaveVec.push_back(Form("%s over %s",PFHTmainTrigger.c_str(),denom.c_str())); histColorVec.push_back(kMagenta+3);

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
  ptCutVec.push_back("minpt300_"); ptCutPaveVec.push_back("p_{T} > 300 GeV");
  ptCutVec.push_back("minpt400_"); ptCutPaveVec.push_back("p_{T} > 400 GeV");
  ptCutVec.push_back("minpt450_"); ptCutPaveVec.push_back("p_{T} > 450 GeV");
  ptCutVec.push_back("minpt500_"); ptCutPaveVec.push_back("p_{T} > 500 GeV");

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
