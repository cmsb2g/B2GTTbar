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


void plotter(string, string, string, string, string, string, string, int, float, float, string, string, string, bool);

void plot_topTag_WPeff(){
	
  /*
    Z', QCD, and ttbar efficiencies
    x-axis: gen pt & jet pt, gen eta & jet eta
    QCD: all qcd & split into flavors
    WPs: - new 800 - 1000 GeV & new 600 - 800 GeV 
         - old WPs
   */

  vector<string> file_names;
  vector<string> pt_cutsLow;
  vector<string> pt_cutsHigh;
  vector<bool> plotpt;
  vector<string> extraCut;
  vector<string> samplePaveLabel;
	

    
  file_names.push_back("topTag_b2gtreeV5_ZprimeToTT_M-1000_W-10_RunIISummer16MiniAODv2");     pt_cutsLow.push_back("300"); pt_cutsHigh.push_back("470");   plotpt.push_back(1); extraCut.push_back("1"); samplePaveLabel.push_back("1 TeV Z', #Gamma = 1%");
  file_names.push_back("topTag_b2gtreeV5_ZprimeToTT_M-1250_W-12p5_RunIISummer16MiniAODv2");     pt_cutsLow.push_back("470"); pt_cutsHigh.push_back("600"); plotpt.push_back(1); extraCut.push_back("1"); samplePaveLabel.push_back("1.25 TeV Z', #Gamma = 1%");
  file_names.push_back("topTag_b2gtreeV5_ZprimeToTT_M-2000_low_W-20_RunIISummer16MiniAODv2_all"); pt_cutsLow.push_back("600"); pt_cutsHigh.push_back("800");   plotpt.push_back(1); extraCut.push_back("1"); samplePaveLabel.push_back("2 TeV Z', #Gamma = 1%");
  file_names.push_back("topTag_b2gtreeV5_ZprimeToTT_M-2000_W-20_RunIISummer16MiniAODv2_all");     pt_cutsLow.push_back("800"); pt_cutsHigh.push_back("1000");   plotpt.push_back(1); extraCut.push_back("1"); samplePaveLabel.push_back("2 TeV Z', #Gamma = 1%");
  file_names.push_back("topTag_b2gtreeV5_ZprimeToTT_M-2500_W-25_RunIISummer16MiniAODv2_all");     pt_cutsLow.push_back("1000"); pt_cutsHigh.push_back("1400");   plotpt.push_back(1); extraCut.push_back("1"); samplePaveLabel.push_back("2.5 TeV Z', #Gamma = 1%");
  file_names.push_back("topTag_b2gtreeV5_ZprimeToTT_M-3000_W-30_RunIISummer16MiniAODv2");     pt_cutsLow.push_back("1000"); pt_cutsHigh.push_back("1400");  plotpt.push_back(1); extraCut.push_back("1"); samplePaveLabel.push_back("3 TeV Z', #Gamma = 1%");
  file_names.push_back("topTag_b2gtreeV5_ZprimeToTT_M-3000_W-300_RunIISummer16MiniAODv2");    pt_cutsLow.push_back("1000"); pt_cutsHigh.push_back("1400");  plotpt.push_back(1); extraCut.push_back("1"); samplePaveLabel.push_back("3 TeV Z', #Gamma = 10%");
  file_names.push_back("topTag_b2gtreeV5_ZprimeToTT_M-3500_W-35_RunIISummer16MiniAODv2");     pt_cutsLow.push_back("1400"); pt_cutsHigh.push_back("1800");  plotpt.push_back(1); extraCut.push_back("1"); samplePaveLabel.push_back("3.5 TeV Z', #Gamma = 1%");
  file_names.push_back("topTag_b2gtreeV5_ZprimeToTT_M-4000_W-40_RunIISummer16MiniAODv2");     pt_cutsLow.push_back("1400"); pt_cutsHigh.push_back("1800");  plotpt.push_back(1); extraCut.push_back("1"); samplePaveLabel.push_back("4 TeV Z', #Gamma = 1%");
  file_names.push_back("topTag_b2gtreeV5_ZprimeToTT_M-4000_W-400_RunIISummer16MiniAODv2");    pt_cutsLow.push_back("400"); pt_cutsHigh.push_back("2100");   plotpt.push_back(1); extraCut.push_back("1"); samplePaveLabel.push_back("4 TeV Z', #Gamma = 10%");

  file_names.push_back("topTag_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2");    pt_cutsLow.push_back("300"); pt_cutsHigh.push_back("2100");   plotpt.push_back(1); extraCut.push_back("1"); samplePaveLabel.push_back("t#bar{t}");

  file_names.push_back("topTag_b2gtreeV5_QCD_Pt_300to470_pythia8_RunIISummer16MiniAODv2_withExt");      pt_cutsLow.push_back("300"); pt_cutsHigh.push_back("470"); plotpt.push_back(0); extraCut.push_back("1"); samplePaveLabel.push_back("QCD");
  file_names.push_back("topTag_b2gtreeV5_QCD_Pt_470to600_pythia8_RunIISummer16MiniAODv2_withExt");      pt_cutsLow.push_back("470"); pt_cutsHigh.push_back("600"); plotpt.push_back(0); extraCut.push_back("1"); samplePaveLabel.push_back("QCD");
  file_names.push_back("topTag_b2gtreeV5_QCD_Pt_600to800_pythia8_RunIISummer16MiniAODv2_withExt");      pt_cutsLow.push_back("600"); pt_cutsHigh.push_back("800");   plotpt.push_back(0); extraCut.push_back("1"); samplePaveLabel.push_back("QCD");
  file_names.push_back("topTag_b2gtreeV5_QCD_Pt_800to1000_pythia8_RunIISummer16MiniAODv2_withExt");     pt_cutsLow.push_back("800"); pt_cutsHigh.push_back("1000");   plotpt.push_back(0); extraCut.push_back("1"); samplePaveLabel.push_back("QCD");
  file_names.push_back("topTag_b2gtreeV5_QCD_Pt_1000to1400_pythia8_RunIISummer16MiniAODv2_withExt");    pt_cutsLow.push_back("1000"); pt_cutsHigh.push_back("1400"); plotpt.push_back(0); extraCut.push_back("1"); samplePaveLabel.push_back("QCD");
  file_names.push_back("topTag_b2gtreeV5_QCD_Pt_1400to1800_pythia8_RunIISummer16MiniAODv2_withExt");    pt_cutsLow.push_back("1400"); pt_cutsHigh.push_back("1800");  plotpt.push_back(0); extraCut.push_back("1"); samplePaveLabel.push_back("QCD");
  file_names.push_back("topTag_b2gtreeV5_QCD_Pt_300to2400_pythia8_RunIISummer16MiniAODv2_withExt");     pt_cutsLow.push_back("400"); pt_cutsHigh.push_back("2100");   plotpt.push_back(1); extraCut.push_back("weight_qcdSample"); samplePaveLabel.push_back("QCD");  

  for (unsigned int i=0; i< file_names.size(); i++ ){
    vector<string> xVars;
    vector<string> xVars_pretty;
    vector<int> nbinsx;
    vector<float> xmin;
    vector <float> xmax;
    vector <bool> jetVar;//plot ak8 variable

    xVars.push_back("npv"); xVars_pretty.push_back("Number of Pileup Vertices"); nbinsx.push_back(100); xmin.push_back(0); xmax.push_back(70);
    xVars.push_back("eta"); xVars_pretty.push_back("#eta"); nbinsx.push_back(100); xmin.push_back(-2.5); xmax.push_back(2.5); jetVar.push_back(1);
    if (plotpt[i]){ xVars.push_back("pt"); xVars_pretty.push_back("p_{T}"); nbinsx.push_back(45); xmin.push_back(300); xmax.push_back(2100); jetVar.push_back(1); }
    
    vector<string> WPtau32cut;
    vector<string> WPlabel;
    vector<string> WPfileLabel;
    
    //WPtau32cut.push_back("0.40"); WPlabel.push_back("#splitline{105 < m_{SD}^{PUPPI} < 210, #tau_{32}^{PUPPI} < 0.40}{#varepsilon_{B} = 0.1%, #varepsilon_{S} = 14%}"); WPfileLabel.push_back("WP80X_800to1000_0p1EffBkg");
    //WPtau32cut.push_back("0.46"); WPlabel.push_back("#splitline{105 < m_{SD}^{PUPPI} < 210, #tau_{32}^{PUPPI} < 0.46}{#varepsilon_{B} = 0.3%, #varepsilon_{S} = 25%}"); WPfileLabel.push_back("WP80X_800to1000_0p3EffBkg_WP76X_0p1EffBkg");
    //WPtau32cut.push_back("0.54"); WPlabel.push_back("#splitline{105 < m_{SD}^{PUPPI} < 210, #tau_{32}^{PUPPI} < 0.54}{#varepsilon_{B} = 1%, #varepsilon_{S} = 43%}"); WPfileLabel.push_back("WP80X_800to1000_1pEffBkg_WP76X_0p3EffBkg");
    WPtau32cut.push_back("0.65"); WPlabel.push_back("#splitline{105 < m_{SD}^{PUPPI} < 210, #tau_{32}^{PUPPI} < 0.65}{#varepsilon_{B} = 3%, #varepsilon_{S} = 61%}"); WPfileLabel.push_back("WP80X_800to1000_3pEffBkg_WP76X_1pEffBkg");
    WPtau32cut.push_back("0.80"); WPlabel.push_back("#splitline{105 < m_{SD}^{PUPPI} < 210, #tau_{32}^{PUPPI} < 0.80}{#varepsilon_{B} = 10%, #varepsilon_{S} = 79%}"); WPfileLabel.push_back("WP80X_800to1000_10pEffBkg_WP76X_3pEffBkg");

    for (unsigned int j=0; j< xVars.size(); j++){
      for (unsigned int k=0; k<WPtau32cut.size(); k++)	plotter(file_names[i], pt_cutsLow[i], pt_cutsHigh[i], extraCut[i], samplePaveLabel[i], xVars[j], xVars_pretty[j], nbinsx[j], xmin[j], xmax[j], WPtau32cut[k], WPlabel[k], WPfileLabel[k], 1);
    }
  }
}

void plotter(string fileName, string ptBinLow, string ptBinHigh, string extraCut, string sampleLabel, string xAxisVar, string xAxisVar_pretty, int nbinsx, float xmin, float xmax, string tau32max, string tau32label, string tau32fileLabel, bool legswitch ){
  gStyle->SetOptStat(0);
  gROOT->UseCurrentStyle();
  gROOT->ForceStyle();


  gROOT->Reset();
  gROOT->ForceStyle(); 
  gROOT->SetBatch(); 


  string dir = "topTagStudies/v5/";
  string in_end = ".root";

  TFile *infile = new TFile(Form("%s%s%s",dir.c_str(),fileName.c_str(),in_end.c_str()),"READ");
  TTree *T_topTag = (TTree*) infile->Get("tree_topTag");

  cout << "Opened " << dir << fileName << in_end << endl;

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
  
  cout << xAxisVar << endl;
  
  std::size_t foundNPV  = xAxisVar.find( "npv"  );
  std::size_t foundPT  = xAxisVar.find( "pt"  );

  TH1D* num_histgen = new TH1D("num_histgen","",nbinsx,xmin,xmax);
  TH1D* num_histgen_btag = new TH1D("num_histgen_btag","",nbinsx,xmin,xmax);
  TH1D* num_histjet = new TH1D("num_histjet","",nbinsx,xmin,xmax);
  TH1D* num_histjet_btag = new TH1D("num_histjet_btag","",nbinsx,xmin,xmax);
  
  TH1D* denom_histgen = new TH1D("denom_histgen","",nbinsx,xmin,xmax);
  TH1D* denom_histjet = new TH1D("denom_histjet","",nbinsx,xmin,xmax);

  string ptCutLow = ptBinLow;
  string ptCutHigh = ptBinHigh;
  if ( foundPT != std::string::npos ){
    ptCutLow = "0";
    ptCutHigh = "3000";
  }

  //gen numerator hists
  T_topTag->Draw(Form("%s>>num_histgen",xAxisVar.c_str()),Form("(pt>%s&&pt<%s&&ak08Puppisoftdropz10b00_mass>105&&ak08Puppisoftdropz10b00_mass<210&&top_size<0.6&&ak08Puppi_tau32<%s)*%s",ptCutLow.c_str(),ptCutHigh.c_str(),tau32max.c_str(),extraCut.c_str()));
  T_topTag->Draw(Form("%s>>num_histgen_btag",xAxisVar.c_str()),Form("(pt>%s&&pt<%s&&ak08Puppisoftdropz10b00_mass>105&&ak08Puppisoftdropz10b00_mass<210&&top_size<0.6&&ak08Puppi_tau32<%s&&ak08Puppisoftdropz10b00_btag>0.8)*%s",ptCutLow.c_str(),ptCutHigh.c_str(),tau32max.c_str(),extraCut.c_str()));
  
  num_histgen->Sumw2();
  num_histgen_btag->Sumw2();

  //gen denominator hist
  T_topTag->Draw(Form("%s>>denom_histgen",xAxisVar.c_str()),Form("(pt>%s&&pt<%s&&top_size<0.6)*%s",ptCutLow.c_str(),ptCutHigh.c_str(),extraCut.c_str()));
  
  denom_histgen->Sumw2();

  //dividing num and denom hists
  num_histgen->Divide(num_histgen,denom_histgen,1,1,"B");
  num_histgen_btag->Divide(num_histgen_btag,denom_histgen,1,1,"B");
  
  //drawing jet eta or pt
  if ( foundNPV   == std::string::npos ) {
    //jet numerator hists
    T_topTag->Draw(Form("ak08_%s>>num_histjet",xAxisVar.c_str()),Form("(ak08_pt>%s&&ak08_pt<%s&&ak08Puppisoftdropz10b00_mass>105&&ak08Puppisoftdropz10b00_mass<210&&top_size<0.6&&ak08Puppi_tau32<%s)*%s",ptCutLow.c_str(),ptCutHigh.c_str(),tau32max.c_str(),extraCut.c_str()));
    T_topTag->Draw(Form("ak08_%s>>num_histjet_btag",xAxisVar.c_str()),Form("(ak08_pt>%s&&ak08_pt<%s&&ak08Puppisoftdropz10b00_mass>105&&ak08Puppisoftdropz10b00_mass<210&&top_size<0.6&&ak08Puppi_tau32<%s&&ak08Puppisoftdropz10b00_btag>0.8)*%s",ptCutLow.c_str(),ptCutHigh.c_str(),tau32max.c_str(),extraCut.c_str()));
  
    num_histjet->Sumw2();
    num_histjet_btag->Sumw2();

    //jet denominator hist
    T_topTag->Draw(Form("ak08_%s>>denom_histjet",xAxisVar.c_str()),Form("(ak08_pt>%s&&ak08_pt<%s&&top_size<0.6)*%s",ptCutLow.c_str(),ptCutHigh.c_str(),extraCut.c_str()));
  
    denom_histjet->Sumw2();

    //dividing num and denom hists
    num_histjet->Divide(num_histjet,denom_histjet,1,1,"B");
    num_histjet_btag->Divide(num_histjet_btag,denom_histjet,1,1,"B");

    num_histjet->SetLineWidth(2);
    num_histjet->SetLineColor(4);
    num_histjet_btag->SetLineWidth(2);
    num_histjet_btag->SetLineColor(kGreen+2);
  }

    num_histgen->SetLineWidth(2);
    num_histgen->SetLineColor(1);

    num_histgen->GetXaxis()->SetTitle(xAxisVar_pretty.c_str());
    num_histgen->GetYaxis()->SetTitle("Efficiency");
    
    num_histgen->SetMaximum((num_histgen->GetMaximum())*1.5);
    num_histgen->SetMinimum(0.0);

    num_histgen_btag->SetLineWidth(2);
    num_histgen_btag->SetLineColor(2);
    
    num_histgen->Draw("EP");
    num_histgen_btag->Draw("EPSAME");
    if ( foundNPV   == std::string::npos ) {   
      num_histjet->Draw("EPSAME");
      num_histjet_btag->Draw("EPSAME");
    }

    double leg1 =0.67; double leg2 =0.6; double leg3 =0.91; double leg4 =0.83;
    double peg1 =0.12; double peg2 =0.6; double peg3 =0.45; double peg4 =0.82;
    TLegend *leg = new TLegend(leg1, leg2, leg3, leg4);
    if ( foundNPV   == std::string::npos ) {
      leg->AddEntry(num_histgen,Form("Parton %s",xAxisVar_pretty.c_str()),"lp");
      leg->AddEntry(num_histgen_btag,Form("Parton %s (Medium b-tag)",xAxisVar_pretty.c_str()),"lp");
      leg->AddEntry(num_histjet,Form("Reco %s",xAxisVar_pretty.c_str()),"lp");
      leg->AddEntry(num_histjet_btag,Form("Reco %s (Medium b-tag)",xAxisVar_pretty.c_str()),"lp");
    }
    else{
      leg->AddEntry(num_histgen,Form("%s",xAxisVar_pretty.c_str()),"lp");
      leg->AddEntry(num_histgen_btag,Form("%s (Medium b-tag)",xAxisVar_pretty.c_str()),"lp");
    }
    leg->SetFillColor(0);
    leg->SetLineColor(0);

    TLegend *peg = new TLegend(peg1, peg2, peg3, peg4);
    if ( foundNPV   == std::string::npos ) {
      peg->AddEntry(num_histgen,Form("Parton %s",xAxisVar_pretty.c_str()),"lp");
      peg->AddEntry(num_histgen_btag,Form("Parton %s (Medium b-tag)",xAxisVar_pretty.c_str()),"lp");
      peg->AddEntry(num_histjet,Form("Reco %s",xAxisVar_pretty.c_str()),"lp");
      peg->AddEntry(num_histjet_btag,Form("Reco %s (Medium b-tag)",xAxisVar_pretty.c_str()),"lp");
    }
    else{
      peg->AddEntry(num_histgen,Form("%s",xAxisVar_pretty.c_str()),"lp");
      peg->AddEntry(num_histgen_btag,Form("%s (Medium b-tag)",xAxisVar_pretty.c_str()),"lp");
    }
    peg->SetFillColor(0);
    peg->SetLineColor(0);
    
    if (legswitch)  peg->Draw("same");
    if (!legswitch) leg->Draw("same");

    TLatex *   tex = new TLatex(0.12,0.83,"#font[62]{CMS} #font[52]{Preliminary}");
    tex->SetNDC();
    tex->SetTextFont(42);
    tex->SetTextSize(0.0625);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(0.89,0.936, "13 TeV");
    tex->SetNDC();
    tex->SetTextAlign(31);
    tex->SetTextFont(42);
    // tex->SetTextSize(0.0625);                                                                                           
    tex->SetTextSize(0.0575);
    tex->SetLineWidth(2);
    tex->Draw();

    tex = new TLatex(0.57,0.87, Form("%s",sampleLabel.c_str()));
    tex->SetNDC();
    tex->SetTextAlign(13);
    tex->SetTextFont(42);
    tex->SetTextSize(0.032);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(0.57,0.82, Form("%s",tau32label.c_str()));
    tex->SetNDC();
    tex->SetTextAlign(13);
    tex->SetTextFont(42);
    tex->SetTextSize(0.032);
    tex->SetLineWidth(2);
    tex->Draw();
    if ( foundPT   == std::string::npos ) {
      tex = new TLatex(0.57,0.73, Form("%s GeV < p_{T} < %s GeV",ptBinLow.c_str(),ptBinHigh.c_str()));
      tex->SetNDC();
      tex->SetTextAlign(13);
      tex->SetTextFont(42);
      tex->SetTextSize(0.032);
      tex->SetLineWidth(2);
      tex->Draw();
    }

    c1->SaveAs(Form("%splots/%s_%s_%s.pdf",dir.c_str(),fileName.c_str(),xAxisVar.c_str(),tau32fileLabel.c_str()));
}
