//plot_topTag_flatPtAndEta.C

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
#include "TStyle.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TString.h"
#include <vector> 
#include <algorithm>
#include "TROOT.h"
// #include "names.C"
#include "CMS_lumi.C"
#include "QCDcrosssections.C"
#include "QCDcrosssections.h"


void plotter(string, string, string, string, bool, bool);

void plot_topTag_flatPtAndEta(){
	
  vector<string> file_names;
  vector<string> pt_cutsLow;
  vector<string> pt_cutsHigh;
  vector<bool> topSize_cut;
  vector<string> extraCut;
	

    
  file_names.push_back("topTag_b2gtreeV5_ZprimeToTT_M-1000_W-10_RunIISummer16MiniAODv2");     pt_cutsLow.push_back("301"); pt_cutsHigh.push_back("469");   topSize_cut.push_back(1); extraCut.push_back("1");
  file_names.push_back("topTag_b2gtreeV5_ZprimeToTT_M-1250_W-12p5_RunIISummer16MiniAODv2");     pt_cutsLow.push_back("471"); pt_cutsHigh.push_back("599"); topSize_cut.push_back(1); extraCut.push_back("1");
  file_names.push_back("topTag_b2gtreeV5_ZprimeToTT_M-2000_low_W-20_RunIISummer16MiniAODv2_all"); pt_cutsLow.push_back("601"); pt_cutsHigh.push_back("799");   topSize_cut.push_back(1); extraCut.push_back("1");
  file_names.push_back("topTag_b2gtreeV5_ZprimeToTT_M-2000_W-20_RunIISummer16MiniAODv2_all");     pt_cutsLow.push_back("801"); pt_cutsHigh.push_back("999");   topSize_cut.push_back(1); extraCut.push_back("1");
  file_names.push_back("topTag_b2gtreeV5_ZprimeToTT_M-2500_W-25_RunIISummer16MiniAODv2_all");     pt_cutsLow.push_back("1001"); pt_cutsHigh.push_back("1399");   topSize_cut.push_back(1); extraCut.push_back("1");
  file_names.push_back("topTag_b2gtreeV5_ZprimeToTT_M-3000_W-30_RunIISummer16MiniAODv2");     pt_cutsLow.push_back("1001"); pt_cutsHigh.push_back("1399");  topSize_cut.push_back(1); extraCut.push_back("1");
  file_names.push_back("topTag_b2gtreeV5_ZprimeToTT_M-3000_W-300_RunIISummer16MiniAODv2");    pt_cutsLow.push_back("1001"); pt_cutsHigh.push_back("1399");  topSize_cut.push_back(1); extraCut.push_back("1");
  file_names.push_back("topTag_b2gtreeV5_ZprimeToTT_M-3500_W-35_RunIISummer16MiniAODv2");     pt_cutsLow.push_back("1401"); pt_cutsHigh.push_back("1799");  topSize_cut.push_back(1); extraCut.push_back("1");
  file_names.push_back("topTag_b2gtreeV5_ZprimeToTT_M-4000_W-40_RunIISummer16MiniAODv2");     pt_cutsLow.push_back("1401"); pt_cutsHigh.push_back("1799");  topSize_cut.push_back(1); extraCut.push_back("1");
  file_names.push_back("topTag_b2gtreeV5_ZprimeToTT_M-4000_W-400_RunIISummer16MiniAODv2");    pt_cutsLow.push_back("401"); pt_cutsHigh.push_back("2099");   topSize_cut.push_back(1); extraCut.push_back("1");

  file_names.push_back("topTag_b2gtreeV5_QCD_Pt_300to470_pythia8_RunIISummer16MiniAODv2_withExt");      pt_cutsLow.push_back("301"); pt_cutsHigh.push_back("469"); topSize_cut.push_back(0); extraCut.push_back("1");
  file_names.push_back("topTag_b2gtreeV5_QCD_Pt_470to600_pythia8_RunIISummer16MiniAODv2_withExt");      pt_cutsLow.push_back("471"); pt_cutsHigh.push_back("599"); topSize_cut.push_back(0); extraCut.push_back("1");
  file_names.push_back("topTag_b2gtreeV5_QCD_Pt_600to800_pythia8_RunIISummer16MiniAODv2_withExt");      pt_cutsLow.push_back("601"); pt_cutsHigh.push_back("799");   topSize_cut.push_back(0); extraCut.push_back("1");
  file_names.push_back("topTag_b2gtreeV5_QCD_Pt_800to1000_pythia8_RunIISummer16MiniAODv2_withExt");     pt_cutsLow.push_back("801"); pt_cutsHigh.push_back("999");   topSize_cut.push_back(0); extraCut.push_back("1");
  file_names.push_back("topTag_b2gtreeV5_QCD_Pt_1000to1400_pythia8_RunIISummer16MiniAODv2_withExt");    pt_cutsLow.push_back("1001"); pt_cutsHigh.push_back("1399"); topSize_cut.push_back(0); extraCut.push_back("1");
  file_names.push_back("topTag_b2gtreeV5_QCD_Pt_1400to1800_pythia8_RunIISummer16MiniAODv2_withExt");    pt_cutsLow.push_back("1401"); pt_cutsHigh.push_back("1799");  topSize_cut.push_back(0); extraCut.push_back("1");
  file_names.push_back("topTag_b2gtreeV5_QCD_Pt_300to2400_pythia8_RunIISummer16MiniAODv2_withExt");     pt_cutsLow.push_back("401"); pt_cutsHigh.push_back("2099");   topSize_cut.push_back(0); extraCut.push_back("weight_qcdSample");
	   
  for (unsigned int i=0; i< file_names.size(); i++ ){
    plotter(file_names[i], pt_cutsLow[i], pt_cutsHigh[i], extraCut[i], topSize_cut[i], 1);
  }
}

void plotter(string fileName, string ptBinLow, string ptBinHigh, string extraCut, bool topSizeCut, bool legswitch ){
  gStyle->SetOptStat(0);
  gROOT->UseCurrentStyle();
  gROOT->ForceStyle();


  gROOT->Reset();
  gROOT->ForceStyle(); 
  gROOT->SetBatch(); 


  string dir = "topTagStudies/v5/";
  string in_end = "-weighted.root";

  TFile *infile = new TFile(Form("%s%s%s",dir.c_str(),fileName.c_str(),in_end.c_str()),"READ");
  TTree *T_topTag = (TTree*) infile->Get("tree_topTag");

  cout << "Opened " << dir << fileName << in_end << endl;

  vector<string> xVars;
  vector<string> xVars_pretty;
  
  xVars.push_back("pt"); xVars_pretty.push_back("p_{T}");
  xVars.push_back("eta"); xVars_pretty.push_back("#eta");

  vector<int> nbinsx;
  vector<float> xmin;
  vector <float> xmax;

  float xmin_pt = (std::stof(ptBinLow)) - 1.0;
  float xmax_pt = (std::stof(ptBinHigh)) + 1.0;
  int nbinsx_pt = 0.5*((int) (xmax_pt-xmin_pt));

  nbinsx.push_back(nbinsx_pt); xmin.push_back(xmin_pt); xmax.push_back(xmax_pt);
  nbinsx.push_back(100); xmin.push_back(-2.5); xmax.push_back(2.5);
  
  for (unsigned int i_vars = 0; i_vars<xVars.size(); i_vars++){

    TCanvas *c1 = new TCanvas("c1","",1,1,745,640);
    gStyle->SetOptFit(1);
    gStyle->SetOptStat(0);
    c1->SetHighLightColor(2);
    c1->Range(0,0,1,1);
    c1->SetFillColor(0);
    c1->SetBorderMode(0);
    c1->SetBorderSize(2);
    c1->SetTickx(1);
    c1->SetTicky(1);
    c1->SetLeftMargin(0.1);
    c1->SetRightMargin(0.1);
    c1->SetTopMargin(0.08);
    c1->SetBottomMargin(0.1);
    c1->SetFrameFillStyle(0);
    c1->SetFrameBorderMode(0);

    TH1D* hist = new TH1D("hist","",nbinsx[i_vars],xmin[i_vars],xmax[i_vars]);
    TH1D* hist_varWeight = new TH1D("hist_varWeight","",nbinsx[i_vars],xmin[i_vars],xmax[i_vars]);
    TH1D* hist_weight = new TH1D("hist_weight","",nbinsx[i_vars],xmin[i_vars],xmax[i_vars]);
  
    cout << xVars[i_vars] << endl;

    if (topSizeCut){
      T_topTag->Draw(Form("%s>>hist_weight",xVars[i_vars].c_str()),Form("weight*(pt>%s&&pt<%s&&top_size<0.6)*%s",ptBinLow.c_str(),ptBinHigh.c_str(),extraCut.c_str()));
      T_topTag->Draw(Form("%s>>hist",xVars[i_vars].c_str()),Form("(pt>%s&&pt<%s&&top_size<0.6)*%s",ptBinLow.c_str(),ptBinHigh.c_str(),extraCut.c_str()),"same");
      T_topTag->Draw(Form("%s>>hist_varWeight",xVars[i_vars].c_str()),Form("weight_%s*(pt>%s&&pt<%s&&top_size<0.6)*%s",xVars[i_vars].c_str(),ptBinLow.c_str(),ptBinHigh.c_str(),extraCut.c_str()),"same");
    }
    else{
      T_topTag->Draw(Form("%s>>hist_weight",xVars[i_vars].c_str()),Form("weight*(pt>%s&&pt<%s)*%s",ptBinLow.c_str(),ptBinHigh.c_str(),extraCut.c_str()));
      T_topTag->Draw(Form("%s>>hist",xVars[i_vars].c_str()),Form("(pt>%s&&pt<%s)*%s",ptBinLow.c_str(),ptBinHigh.c_str(),extraCut.c_str()),"same");
      T_topTag->Draw(Form("%s>>hist_varWeight",xVars[i_vars].c_str()),Form("weight_%s*(pt>%s&&pt<%s)*%s",xVars[i_vars].c_str(),ptBinLow.c_str(),ptBinHigh.c_str(),extraCut.c_str()),"same");
    }

    hist_weight->SetLineWidth(2);
    hist_weight->SetLineColor(1);
    hist_weight->GetXaxis()->SetTitle(xVars_pretty[i_vars].c_str());
    hist_weight->GetYaxis()->SetTitle("Events");
    hist_weight->SetMinimum(1.0);
    
    float ymax = hist_weight->GetMaximum();
    if (ymax < hist->GetMaximum()) ymax = hist->GetMaximum();
    if (ymax < hist_varWeight->GetMaximum()) ymax = hist_varWeight->GetMaximum();
    hist_weight->SetMaximum(ymax*1000);
    
    hist_varWeight->SetLineWidth(2);
    hist_varWeight->SetLineColor(2);
    hist->SetLineWidth(2);
    hist->SetLineColor(4);
    
    hist_weight->Draw();
    hist_varWeight->Draw("SAME");
    hist->Draw("SAME");

    double leg1 =0.67; double leg2 =0.6; double leg3 =0.91; double leg4 =0.83;
    double peg1 =0.14; double peg2 =0.6; double peg3 =0.38; double peg4 =0.83;
    TLegend *leg = new TLegend(leg1, leg2, leg3, leg4);
    leg->AddEntry(hist,"No Weight","l");
    leg->AddEntry(hist_varWeight,Form("Flat %s weight",xVars_pretty[i_vars].c_str()),"l");
    leg->AddEntry(hist_weight,"Flat p_{T} and #eta weights","l");
    leg->SetFillColor(0);
    leg->SetLineColor(0);
    
    TLegend *peg = new TLegend(peg1, peg2, peg3, peg4);
    peg->AddEntry(hist,"No Weight","l");
    peg->AddEntry(hist_varWeight,Form("Flat %s weight",xVars_pretty[i_vars].c_str()),"l");
    peg->AddEntry(hist_weight,"Flat p_{T} and #eta weights","l");
    peg->SetFillColor(0);
    peg->SetLineColor(0);
    
    if (legswitch)  peg->Draw("same");
    if (!legswitch) leg->Draw("same");

    TLatex *   tex = new TLatex(0.18,0.83,"#font[62]{CMS} #font[52]{Preliminary}");
    tex->SetNDC();
    tex->SetTextFont(42);
    tex->SetTextSize(0.0625);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(0.96,0.936, "13 TeV");
    tex->SetNDC();
    tex->SetTextAlign(31);
    tex->SetTextFont(42);
    // tex->SetTextSize(0.0625);                                                                                           
    tex->SetTextSize(0.0575);
    tex->SetLineWidth(2);
    tex->Draw();

    tex = new TLatex(0.57,0.87, Form("#splitline{%s GeV < p_{T} < %s GeV}{top size < 0.6}",ptBinLow.c_str(),ptBinHigh.c_str()));
    if (!topSizeCut) tex = new TLatex(0.57,0.87, Form("%s GeV < p_{T} < %s GeV",ptBinLow.c_str(),ptBinHigh.c_str()));
    tex->SetNDC();
    tex->SetTextAlign(13);
    tex->SetTextFont(42);
    tex->SetTextSize(0.032);
    tex->SetLineWidth(2);
    tex->Draw();


    c1->SetLogy();
    c1->SaveAs(Form("%splots/%s_%s.pdf",dir.c_str(),fileName.c_str(),xVars[i_vars].c_str()));
    c1->SaveAs(Form("%splots/%s_%s.root",dir.c_str(),fileName.c_str(),xVars[i_vars].c_str()));

    hist_weight->Delete();
    hist_varWeight->Delete();
    hist->Delete();
  }
}
