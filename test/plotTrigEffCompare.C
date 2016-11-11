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


void plotTrigEffCompare(){
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

  string ZPN2File = "trigEffStudies/run20161031/outRunTrigEff_20161031ZprimeToTT_M-2000_W-20_RunIISpring16MiniAODv2_reHLT_V3.root";
  string ZPN3File = "trigEffStudies/run20161031/outRunTrigEff_20161031ZprimeToTT_M-3000_W-30_RunIISpring16MiniAODv2_reHLT_V3.root";
  string dataFile = "trigEffStudies/run20161031/outRunTrigEff_20161031_JetHT_combined.root";
  
  TFile * F_ZPN2                 = new TFile( ZPN2File.c_str()         );
  TFile * F_ZPN3                 = new TFile( ZPN3File.c_str()         );
  TFile * F_data                   = new TFile( dataFile.c_str()           );

  TPaveText *textbox1 = new TPaveText(0.54,0.87,0.89,0.93,"NDC");
  textbox1->SetFillColor(0);
  textbox1->SetLineColor(0);
  TText *line1 = textbox1->AddText("27.2 fb^{-1} (13 TeV)");
  line1->SetTextColor(1);
  line1->SetTextSize(23);
  line1->SetTextFont(42);
  line1->SetTextAlign(33); //first number = horizontal alignment (1 left, 2 center, 3 right). second number =vertical alignment (1 top, 2 center, 3 bottom)
  
  //loop over numerators and denominators
  vector <string> numVec;
  vector <string> denomVec;  
  vector <string> numDenomPaveVec;
  vector <string> numVec2;
  vector <string> denomVec2;  
  vector <string> numDenomPaveVec2;
  numVec.push_back("PFHT700TrimMass50");  denomVec.push_back("PFHT650"); numDenomPaveVec.push_back("PFHT700TrimMass50 over PFHT650");
  numVec2.push_back("PFHT700TrimMass50orPFJet360TrimMass30");  denomVec2.push_back("PFHT650"); numDenomPaveVec2.push_back("#splitline{PFJet360TrimMass30 or}{PFHT700TrimMass50 over PFHT650}");
  //numVec.push_back("PFHT700TrimMass50orPFJet360TrimMass30");  denomVec.push_back("PFJet320"); numDenomPaveVec.push_back("PFHT700TrimMass50 or PFJet360TrimMass30 over PFJet320");
  numVec.push_back("PFHT800");  denomVec.push_back("PFHT650"); numDenomPaveVec.push_back("PFHT800 over PFHT650");
  numVec2.push_back("PFHT800orPFJet360TrimMass30");  denomVec2.push_back("PFHT650"); numDenomPaveVec2.push_back("#splitline{PFJet360TrimMass30 or}{PFHT800 over PFHT650}");
  //numVec.push_back("PFHT800orPFJet360TrimMass30");  denomVec.push_back("PFJet320"); numDenomPaveVec.push_back("PFHT800 or PFJet360TrimMass30 over PFJet320");
  //numVec.push_back("PFHT800");  denomVec.push_back("PFHT400"); numDenomPaveVec.push_back("PFHT800 over PFHT400");
  //numVec.push_back("PFHT800");  denomVec.push_back("PFJet450"); numDenomPaveVec.push_back("PFHT800 over PFJet450");
  numVec.push_back("PFHT900");  denomVec.push_back("PFHT650"); numDenomPaveVec.push_back("PFHT900 over PFHT650");
  numVec2.push_back("PFHT900orPFJet360TrimMass30");  denomVec2.push_back("PFHT650"); numDenomPaveVec2.push_back("#splitline{PFJet360TrimMass30 or}{PFHT900 over PFHT650}");
  /*numVec.push_back("PFHT900orPFJet360TrimMass30");  denomVec.push_back("PFJet320"); numDenomPaveVec.push_back("PFHT900 or PFJet360TrimMass30 over PFJet320");
  numVec.push_back("PFHT900");  denomVec.push_back("PFHT650"); numDenomPaveVec.push_back("PFHT900 over PFHT650");
  numVec.push_back("PFHT900");  denomVec.push_back("PFHT400"); numDenomPaveVec.push_back("PFHT900 over PFHT400");
  numVec.push_back("PFHT900");  denomVec.push_back("PFJet450"); numDenomPaveVec.push_back("PFHT900 over PFJet450");
  numVec.push_back("PFJet500"); denomVec.push_back("PFJet320"); numDenomPaveVec.push_back("PFJet500 over PFJet320");*/

  //loop over x-axis Variables
  vector <string> xVarVec;
  vector <string> xTitleVec;
  xVarVec.push_back("sumJetPt"); xTitleVec.push_back("Jet 0 p_{T} + Jet 1 p_{T} [GeV]");
  xVarVec.push_back("Jet0Pt"); xTitleVec.push_back("Jet 0 p_{T} [GeV]");
  xVarVec.push_back("Jet0Mass"); xTitleVec.push_back("Jet 0 Mass [GeV]");

  //loop over cuts
  vector <string> cutVec;
  vector <string> cutPaveVec;
  cutVec.push_back(""); cutPaveVec.push_back("AK8 jets, p_{T} > 250 GeV");
  cutVec.push_back("_2tagMass"); cutPaveVec.push_back("#splitline{AK8 jets, p_{T} > 250 GeV}{110 < M_{SD} < 210 GeV}");
  cutVec.push_back("_2tagMass_2tagTau32"); cutPaveVec.push_back("#splitline{AK8 jets, p_{T} > 250 GeV}{110 < M_{SD} < 210 GeV, #tau_{32} < 0.69}");

  for (unsigned int i=0; i<numVec.size(); i++ ){
    for (unsigned int j=0; j<xVarVec.size(); j++ ){
      for (unsigned int k=0; k<cutVec.size(); k++ ){
 
	string numHistName = "h_pass" + numVec[i] + "num" + denomVec[i] + "denom" + cutVec[k] + "_" + xVarVec[j];
	string denomHistName = "h_pass" + denomVec[i] + "denom" + cutVec[k] + "_" + xVarVec[j];
	cout << numHistName << endl;
	cout << denomHistName << endl;

	string numHistName2 = "h_pass" + numVec2[i] + "num" + denomVec2[i] + "denom" + cutVec[k] + "_" + xVarVec[j];
	string denomHistName2 = "h_pass" + denomVec2[i] + "denom" + cutVec[k] + "_" + xVarVec[j];
	cout << numHistName2 << endl;
	cout << denomHistName2 << endl;

	TH1D *h_dataNum = (TH1D*)F_data ->Get(numHistName.c_str());
	TH1D *h_dataDenom = (TH1D*)F_data ->Get(denomHistName.c_str());
	TH1D *h_ZPN2Num = (TH1D*)F_ZPN2 ->Get(numHistName.c_str());
	TH1D *h_ZPN2Denom = (TH1D*)F_ZPN2 ->Get(denomHistName.c_str());
	TH1D *h_ZPN3Num = (TH1D*)F_ZPN3 ->Get(numHistName.c_str());
	TH1D *h_ZPN3Denom = (TH1D*)F_ZPN3 ->Get(denomHistName.c_str());
	
	h_dataNum->Sumw2();
	h_dataDenom->Sumw2();
	h_ZPN2Num->Sumw2();
	h_ZPN2Denom->Sumw2();
	h_ZPN3Num->Sumw2();
	h_ZPN3Denom->Sumw2();

	TH1D *h_dataNum2 = (TH1D*)F_data ->Get(numHistName2.c_str());
	TH1D *h_dataDenom2 = (TH1D*)F_data ->Get(denomHistName2.c_str());
	TH1D *h_ZPN2Num2 = (TH1D*)F_ZPN2 ->Get(numHistName2.c_str());
	TH1D *h_ZPN2Denom2 = (TH1D*)F_ZPN2 ->Get(denomHistName2.c_str());
	TH1D *h_ZPN3Num2 = (TH1D*)F_ZPN3 ->Get(numHistName2.c_str());
	TH1D *h_ZPN3Denom2 = (TH1D*)F_ZPN3 ->Get(denomHistName2.c_str());
	
	h_dataNum2->Sumw2();
	h_dataDenom2->Sumw2();
	h_ZPN2Num2->Sumw2();
	h_ZPN2Denom2->Sumw2();
	h_ZPN3Num2->Sumw2();
	h_ZPN3Denom2->Sumw2();

	/*h_dataNum->Rebin(5);
	h_dataDenom->Rebin(5);
	h_ZPN2Num->Rebin(5);
	h_ZPN2Denom->Rebin(5);
	h_ZPN3Num->Rebin(5);
	h_ZPN3Denom->Rebin(5);*/

	h_dataNum->Divide(h_dataNum, h_dataDenom, 1, 1, "B");
	h_ZPN2Num->Divide(h_ZPN2Num, h_ZPN2Denom, 1, 1, "B");
	h_ZPN3Num->Divide(h_ZPN3Num, h_ZPN3Denom, 1, 1, "B");
      
	h_dataNum2->Divide(h_dataNum2, h_dataDenom2, 1, 1, "B");
	h_ZPN2Num2->Divide(h_ZPN2Num2, h_ZPN2Denom2, 1, 1, "B");
	h_ZPN3Num2->Divide(h_ZPN3Num2, h_ZPN3Denom2, 1, 1, "B");
      
	string title = ";" + xTitleVec[j]  + ";Trigger Efficiency";
	h_dataNum->SetTitle(title.c_str());
	h_dataNum->GetXaxis()->SetNoExponent();
	h_dataNum->GetXaxis()->SetMoreLogLabels();
	h_ZPN2Num->SetTitle(title.c_str());
	h_ZPN2Num->GetXaxis()->SetNoExponent();
	h_ZPN2Num->GetXaxis()->SetMoreLogLabels();
	h_ZPN3Num->SetTitle(title.c_str());
	h_ZPN3Num->GetXaxis()->SetNoExponent();
	h_ZPN3Num->GetXaxis()->SetMoreLogLabels();
	h_dataNum2->SetTitle(title.c_str());
	h_dataNum2->GetXaxis()->SetNoExponent();
	h_dataNum2->GetXaxis()->SetMoreLogLabels();
	h_ZPN2Num2->SetTitle(title.c_str());
	h_ZPN2Num2->GetXaxis()->SetNoExponent();
	h_ZPN2Num2->GetXaxis()->SetMoreLogLabels();
	h_ZPN3Num2->SetTitle(title.c_str());
	h_ZPN3Num2->GetXaxis()->SetNoExponent();
	h_ZPN3Num2->GetXaxis()->SetMoreLogLabels();
	
	/*h_dataNum->GetXaxis()->SetNdivisions(506);
	h_dataNum->GetXaxis()->SetLabelFont(42);
	h_dataNum->GetXaxis()->SetLabelSize(0.05);
	h_dataNum->GetXaxis()->SetTitleSize(0.056);
	h_dataNum->GetXaxis()->SetTickLength(0.045);*/
	h_dataNum->GetXaxis()->SetTitleOffset(1.15);
	h_dataNum->GetXaxis()->SetTitleFont(42);
	h_dataNum->GetXaxis()->SetRangeUser(0,3000);

	/*h_dataNum->GetYaxis()->SetNdivisions(506);
	h_dataNum->GetYaxis()->SetLabelFont(42);
	h_dataNum->GetYaxis()->SetLabelSize(0.05);//  //0.04375);//0.06375);
	h_dataNum->GetYaxis()->SetTitleSize(0.06125);//0.07125);*/
	h_dataNum->GetYaxis()->SetTitleOffset(1.17);//0.9);
	h_dataNum->GetYaxis()->SetTitleFont(42);
	h_dataNum->GetYaxis()->SetRangeUser(0,1.5);
	
	h_dataNum->GetZaxis()->SetLabelFont(42);
	h_dataNum->GetZaxis()->SetLabelSize(0.0425);
	h_dataNum->GetZaxis()->SetTitleSize(0.0475);
	h_dataNum->GetZaxis()->SetTitleFont(42);

	h_dataNum->SetLineWidth(2);
	h_dataNum->SetLineColor(kGreen);
	h_dataNum->Draw("EP");

	h_ZPN2Num->SetLineWidth(2);
	h_ZPN2Num->SetLineColor(kRed-7);
	h_ZPN2Num->Draw("EPsame");

	h_ZPN3Num->SetLineWidth(2);
	h_ZPN3Num->SetLineColor(kCyan);
	h_ZPN3Num->Draw("EPsame");

	h_dataNum2->SetLineWidth(2);
	h_dataNum2->SetLineColor(kGreen+3);
	h_dataNum2->Draw("EPsame");

	h_ZPN2Num2->SetLineWidth(2);
	h_ZPN2Num2->SetLineColor(kRed+2);
	h_ZPN2Num2->Draw("EPsame");

	h_ZPN3Num2->SetLineWidth(2);
	h_ZPN3Num2->SetLineColor(kBlue+2);
	h_ZPN3Num2->Draw("EPsame");

	TLegend * leg;
	leg = new TLegend( 0.65, 0.45,0.77, 0.59); //0.51, 0.66,0.84, 0.83
	leg->SetBorderSize(0);
	leg->SetFillColor(0);
	leg->SetFillStyle(4000);
	leg->SetTextSize(0.042);
	leg->AddEntry( h_dataNum   , "Data" , "LP" );
	leg->AddEntry( h_ZPN2Num  , "Narrow 2 TeV Z'"  , "LP" );
	leg->AddEntry( h_ZPN3Num  , "Narrow 3 TeV Z'"  , "LP" );
 	leg->Draw("same");

	TLegend * leg2;
	leg2 = new TLegend( 0.65, 0.20,0.77, 0.34); //0.51, 0.66,0.84, 0.83
	leg2->SetBorderSize(0);
	leg2->SetFillColor(0);
	leg2->SetFillStyle(4000);
	leg2->SetTextSize(0.042);
	leg2->AddEntry( h_dataNum2   , "Data" , "LP" );
	leg2->AddEntry( h_ZPN2Num2  , "Narrow 2 TeV Z'"  , "LP" );
	leg2->AddEntry( h_ZPN3Num2  , "Narrow 3 TeV Z'"  , "LP" );
	leg2->Draw("same");

	TLatex *   tex = new TLatex(0.18,0.83,"#font[62]{CMS} #font[52]{Preliminary}");
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.0625);
	tex->SetLineWidth(2);
	tex->Draw();
	tex = new TLatex(0.96,0.936,"27.2 fb^{-1} (13 TeV)");
	tex->SetNDC();
	tex->SetTextAlign(31);
	tex->SetTextFont(42);
	// tex->SetTextSize(0.0625);
	tex->SetTextSize(0.0575);
	tex->SetLineWidth(2);
	tex->Draw();
	tex = new TLatex(0.64,0.64, numDenomPaveVec[i].c_str());
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
	tex->Draw();
	tex = new TLatex(0.65,0.87, cutPaveVec[k].c_str());
	tex->SetNDC();
	tex->SetTextAlign(13);
	tex->SetTextFont(42);
	tex->SetTextSize(0.032);
	tex->SetLineWidth(2);
	tex->Draw();
      
	gPad->RedrawAxis();
	
	string savename = "trigEffStudies/run20161031/trigEffCompare_" + numVec[i] + "over" +  denomVec[i] + "_and_" + numVec2[i] + "over" +  denomVec2[i] + "_vs" + xVarVec[j] + cutVec[k] + ".pdf";
	cout<<savename<<endl;
	c1237->SaveAs(savename.c_str());    

	h_dataNum->Delete();
	h_dataDenom->Delete();
	h_ZPN2Num->Delete();
	h_ZPN2Denom->Delete();
	h_ZPN3Num->Delete();
	h_ZPN3Denom->Delete();
      }
    }
  }
}
