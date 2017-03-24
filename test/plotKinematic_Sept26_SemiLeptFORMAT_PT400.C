// .L plotKinematic.C+
// run()

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
// #include "names.C"
#include "CMS_lumi.C"



void plotter(TString, TString, TString, bool, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, bool, double, double, string);

void run(){
  gStyle->SetOptStat(0);
  gROOT->UseCurrentStyle();
  gROOT->ForceStyle();

  gROOT->Reset();
  gROOT->ForceStyle(); 
  // gROOT->SetBatch(); 
	  
  TFile * fData = new TFile("/uscms_data/d1/jdolen/B2GAnaFW/CMSSW_7_4_16_patch2/src/Analysis/B2GTTbar6/test/JetHT_Kinematic_060716_nom_pt400.0.root");
  TFile * fQCD  = new TFile("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/runs/run20160607/QCD_HTall_Kinematic_060716_nom_pt400.0_fixed.root");
  TFile * fTT   = new TFile("/uscms_data/d1/jdolen/B2GAnaFW/CMSSW_7_4_16_patch2/src/Analysis/B2GTTbar6/test/TT_Kinematic_060716_nom_pt400.0.root");
  TFile * fZp10 = new TFile("/uscms_data/d1/jdolen/B2GAnaFW/CMSSW_7_4_16_patch2/src/Analysis/B2GTTbar6/test/Z1n_Kinematic_060716_nom_pt400.0.root");
  TFile * fZp20 = new TFile("/uscms_data/d1/jdolen/B2GAnaFW/CMSSW_7_4_16_patch2/src/Analysis/B2GTTbar6/test/Z2n_Kinematic_060716_nom_pt400.0.root");
  TFile * fZp30 = new TFile("/uscms_data/d1/jdolen/B2GAnaFW/CMSSW_7_4_16_patch2/src/Analysis/B2GTTbar6/test/Z3n_Kinematic_060716_nom_pt400.0.root");
  TFile * fZp40 = new TFile("/uscms_data/d1/jdolen/B2GAnaFW/CMSSW_7_4_16_patch2/src/Analysis/B2GTTbar6/test/Z4n_Kinematic_060716_nom_pt400.0.root");

  // outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e_20160706_nom_pt500.0.root
  // outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_20160706_nom_pt500.0.root
  // outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_20160706_nom_pt500.0.root
 
  /*TFile * fData = new TFile("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/runs/run20160706/outBkgdEst_JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65_20160706_nom_pt500.0.root");
    TFile * fQCD  = new TFile("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/runs/run20160706/outBkgdEst_QCD_HT700toInf_B2Gv8p4_reader603e_notrig_20160706_nom_pt500_scaled.root");
    TFile * fTT   = new TFile("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/runs/run20160706/outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_20160706_nom_pt500.0.root");
    TFile * fZp10 = new TFile("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/runs/run20160706/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_20160706_nom_pt500.0.root");
    TFile * fZp20 = new TFile("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/runs/run20160706/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_20160706_nom_pt500.0.root");
    TFile * fZp30 = new TFile("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/runs/run20160706/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_20160706_nom_pt500.0.root");
    TFile * fZp40 = new TFile("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/runs/run20160706/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_20160706_nom_pt500.0.root");*/

  vector<TString> hists_names;
  vector<TString> hists_names2;
  vector<TString> combo_hist_label;
  vector<TString> combo_hist_label2;
  vector<TString> hists_title;
  vector<double> hists_rebin;
  vector<bool> legs;
  vector<TString> pave;
  vector <bool> paveSplitLine;
  vector<double> x_max_scale;
  vector<double> y_max_scale;
  vector<string> yAxisLabel;

  hists_names.push_back("h_2btag_jet1ttag_jet0tautag_jet0massSD");   pave.push_back("AK8 jets with p_{T} > 400 GeV, |#eta| < 2.4, subjet b-tag, #tau_{32} < 0.69");  paveSplitLine.push_back(false); hists_title.push_back("Jet soft-drop mass [GeV]");             hists_rebin.push_back(12);    legs.push_back(true);           x_max_scale.push_back(300); y_max_scale.push_back(1.4);      yAxisLabel.push_back("Events/10 GeV");
  hists_names.push_back("h_2btag_jet1ttag_jet0masstag_jet0tau32");   pave.push_back("#splitline{AK8 jets with p_{T} > 400 GeV, |#eta| < 2.4,}{subjet b-tag, 110 < M_{SD} < 210 GeV}");  paveSplitLine.push_back(true);  hists_title.push_back("Jet #tau_{32}");               hists_rebin.push_back(10 );   legs.push_back(true);  x_max_scale.push_back(1);  y_max_scale.push_back(2.5);     yAxisLabel.push_back("Events/bin");
  hists_names2.push_back("h_2btag_jet0ttag_jet1tautag_jet1massSD");
  hists_names2.push_back("h_2btag_jet0ttag_jet1masstag_jet1tau32");
  combo_hist_label.push_back("h_2btag_1ttag_Nm1_jetmassSD");
  combo_hist_label.push_back("h_2btag_1ttag_Nm1_jettau32");
  combo_hist_label2.push_back("h_2btag_1ttag_Nm1_jetmassSD_smooth");
  combo_hist_label2.push_back("h_2btag_1ttag_Nm1_jettau32_smooth");

  for (unsigned int i=0; i< hists_names.size(); i++ ){
    TH1D * hData = (TH1D*) fData ->Get( hists_names[i] ); 
    TH1D * hQCD  = (TH1D*) fQCD  ->Get( hists_names[i] ); 
    TH1D * hTT   = (TH1D*) fTT   ->Get( hists_names[i] ); 
    TH1D * hZp10 = (TH1D*) fZp10 ->Get( hists_names[i] ); 
    TH1D * hZp20 = (TH1D*) fZp20 ->Get( hists_names[i] ); 
    TH1D * hZp30 = (TH1D*) fZp30 ->Get( hists_names[i] ); 
    TH1D * hZp40 = (TH1D*) fZp40 ->Get( hists_names[i] ); 

    TH1D * hhData = (TH1D*) fData ->Get( hists_names2[i] ); 
    TH1D * hhQCD  = (TH1D*) fQCD  ->Get( hists_names2[i] ); 
    TH1D * hhTT   = (TH1D*) fTT   ->Get( hists_names2[i] ); 
    TH1D * hhZp10 = (TH1D*) fZp10 ->Get( hists_names2[i] ); 
    TH1D * hhZp20 = (TH1D*) fZp20 ->Get( hists_names2[i] ); 
    TH1D * hhZp30 = (TH1D*) fZp30 ->Get( hists_names2[i] ); 
    TH1D * hhZp40 = (TH1D*) fZp40 ->Get( hists_names2[i] ); 



    cout<<"debug1"<<endl;
    TH1D * h2Data = (TH1D *) hData ->Clone("h2Data");
    TH1D * h2QCD  = (TH1D *) hQCD  ->Clone("h2QCD");
    TH1D * h2TT   = (TH1D *) hTT   ->Clone("h2TT");
    TH1D * h2Zp10 = (TH1D *) hZp10 ->Clone("h2Zp10");
    TH1D * h2Zp20 = (TH1D *) hZp20 ->Clone("h2Zp20");
    TH1D * h2Zp30 = (TH1D *) hZp30 ->Clone("h2Zp30");
    TH1D * h2Zp40 = (TH1D *) hZp40 ->Clone("h2Zp40");
    cout<<"debug1a"<<endl;


    cout<<"hhData "<<hhData->Integral()<<endl;
    cout<<"hhQCD  "<<hhQCD ->Integral()<<endl;
    cout<<"hhTT   "<<hhTT  ->Integral()<<endl;
    cout<<"hhZp10 "<<hhZp10->Integral()<<endl;
    cout<<"hhZp20 "<<hhZp20->Integral()<<endl;
    cout<<"hhZp30 "<<hhZp30->Integral()<<endl;
    cout<<"hhZp40 "<<hhZp40->Integral()<<endl;


    h2Data->Add(hhData);
    h2QCD ->Add(hhQCD );
    h2TT  ->Add(hhTT  );
    h2Zp10->Add(hhZp10);
    h2Zp20->Add(hhZp20);
    h2Zp30->Add(hhZp30);
    h2Zp40->Add(hhZp40);
    cout<<"debug2"<<endl;


    float lumi = 2592.3;
    float nttbar = 96834559.;//19665194.;
    float kfactor = 0.94;
    float ttSF = 0.996*0.886;//0.89*0.89;
    float qcdscale = 0.9;  //  mistag rate data/bkgd

    double xs_zp30 = 1; // set to 1 to match semilept
    hQCD ->Scale( qcdscale );
    hTT  ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    hZp10->Scale( 1. * ttSF * lumi / 122204. ); 
    hZp20->Scale( 1. * ttSF * lumi / 202573. ); 
    hZp30->Scale( xs_zp30 * 0.89 * lumi / 117069. ); 
    hZp40->Scale( 1. * ttSF * lumi / 111625. );
		
    hhQCD ->Scale( qcdscale );
    hhTT  ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    hhZp10->Scale( 1. * ttSF * lumi / 122204. ); 
    hhZp20->Scale( 1. * ttSF * lumi / 202573. ); 
    hhZp30->Scale( xs_zp30 * 0.89 * lumi / 117069. ); 
    hhZp40->Scale( 1. * ttSF * lumi / 111625. );

    h2QCD ->Scale( qcdscale );
    h2TT  ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    h2Zp10->Scale( 1. * ttSF * lumi / 122204. ); 
    h2Zp20->Scale( 1. * ttSF * lumi / 202573. ); 
    h2Zp30->Scale( xs_zp30 * 0.89 * lumi / 117069. ); 
    h2Zp40->Scale( 1. * ttSF * lumi / 111625. );
    cout<<"debug3"<<endl;


    double rebin = hists_rebin[i];
    hData  ->Rebin(rebin); 
    hQCD   ->Rebin(rebin);
    hTT    ->Rebin(rebin); 
    hZp10  ->Rebin(rebin); 
    hZp20  ->Rebin(rebin); 
    hZp30  ->Rebin(rebin); 
    hZp40  ->Rebin(rebin); 

    hhData  ->Rebin(rebin); 
    hhQCD   ->Rebin(rebin);
    hhTT    ->Rebin(rebin); 
    hhZp10  ->Rebin(rebin); 
    hhZp20  ->Rebin(rebin); 
    hhZp30  ->Rebin(rebin); 
    hhZp40  ->Rebin(rebin); 


    h2Data  ->Rebin(rebin); 
    h2QCD   ->Rebin(rebin);
    h2TT    ->Rebin(rebin); 
    h2Zp10  ->Rebin(rebin); 
    h2Zp20  ->Rebin(rebin); 
    h2Zp30  ->Rebin(rebin); 
    h2Zp40  ->Rebin(rebin); 

    TH1D * hSmooth2Data = (TH1D *) h2Data ->Clone("hSmooth2Data");
    TH1D * hSmooth2QCD  = (TH1D *) h2QCD  ->Clone("hSmooth2QCD");
    TH1D * hSmooth2TT   = (TH1D *) h2TT   ->Clone("hSmooth2TT");
    TH1D * hSmooth2Zp10 = (TH1D *) h2Zp10 ->Clone("hSmooth2Zp10");
    TH1D * hSmooth2Zp20 = (TH1D *) h2Zp20 ->Clone("hSmooth2Zp20");
    TH1D * hSmooth2Zp30 = (TH1D *) h2Zp30 ->Clone("hSmooth2Zp30");
    TH1D * hSmooth2Zp40 = (TH1D *) h2Zp40 ->Clone("hSmooth2Zp40");

    hSmooth2QCD ->Smooth(1);

    // if (i==2) plotter(hists_names[i], hists_title[i], pave[i], hData, hTT, hQCD, hZp10, hZp20, hZp30, hZp40, legs[i], x_max_scale[i], y_max_scale[i] );
    // else{
    // plotter(hists_names[i], hists_title[i], pave[i], hData, hTT, hQCD, hZp10, hZp20, hZp30, hZp40, legs[i], x_max_scale[i], y_max_scale[i] );
    // plotter(hists_names2[i], hists_title[i], pave[i], hhData, hhTT, hhQCD, hhZp10, hhZp20, hhZp30, hhZp40, legs[i], x_max_scale[i], y_max_scale[i] );
    plotter(combo_hist_label[i], hists_title[i], pave[i], paveSplitLine[i], h2Data, h2TT, h2QCD, h2Zp10, h2Zp20, h2Zp30, h2Zp40, legs[i], x_max_scale[i], y_max_scale[i], yAxisLabel[i] );
    plotter(combo_hist_label2[i], hists_title[i], pave[i], paveSplitLine[i], hSmooth2Data, hSmooth2TT, hSmooth2QCD, hSmooth2Zp10, hSmooth2Zp20, hSmooth2Zp30, hSmooth2Zp40, legs[i], x_max_scale[i], y_max_scale[i], yAxisLabel[i] );
    // }
  }
}
void plotter(TString histname, TString histtitle, TString pave, bool paveSplitLine, TH1D* hData, TH1D * hTT, TH1D* hQCD, TH1D * hZp10, TH1D * hZp20, TH1D * hZp30, TH1D * hZp40, bool legswitch, double x_max_scale, double y_max_scale, string yAxisLabel ){

  //Int_t ci;      // for color index setting
  //TColor *color; // for color definition with alpha
  //ci = TColor::GetColor("#cc3333");
  hTT ->SetFillColor(kOrange+8);
  //ci = TColor::GetColor("#660000");
  hTT ->SetLineWidth(0);
  //hTT ->SetLineColor(ci);
  //hQCD->SetLineColor(kYellow+2);
  hQCD->SetLineWidth(0);
  hQCD->SetFillColor(kOrange-4);

  // TCanvas *c1 = new TCanvas("c1", "c1",0,0,550,500);
  // TCanvas *c1 = new TCanvas("c1", "c1",0,0,600,650);
  // TCanvas *c1 = new TCanvas("c1", "c1",1,1,800,701);
  TCanvas *c1 = new TCanvas("c1", "c1",1,1,745,701);
  gStyle->SetOptFit(1);
  gStyle->SetOptStat(0);
  c1->SetHighLightColor(2);
  c1->Range(0,0,1,1);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetTickx(1);
  c1->SetTicky(1);
  c1->SetLeftMargin(0.14);
  c1->SetRightMargin(0.04);
  c1->SetTopMargin(0.08);
  c1->SetBottomMargin(0.15);
  c1->SetFrameFillStyle(0);
  c1->SetFrameBorderMode(0);


  TPad *pad1 = new TPad("pad1", "pad1",0,0.3333333,1,1);
  pad1->Draw();
  pad1->cd();
  // pad1->Range(-0.1792683,-2.983224,1.10122,146.183);
  pad1->SetFillColor(0);
  pad1->SetBorderMode(0);
  pad1->SetBorderSize(2);
  pad1->SetTickx(1);
  pad1->SetTicky(1);
  pad1->SetLeftMargin(0.14);
  pad1->SetRightMargin(0.04);
  pad1->SetTopMargin(0.12);
  pad1->SetBottomMargin(0.02);
  pad1->SetFrameFillStyle(0);
  pad1->SetFrameBorderMode(0);
  pad1->SetFrameFillStyle(0);
  pad1->SetFrameBorderMode(0);


  //   	c1->Range(0,0,1,1);
  // c1->Draw();

  // TPad *c1_1 = new TPad("c1_1", "newpad",0.01,0.01,0.99,0.25);
  // c1_1->Draw();
  // TPad *c1_2 = new TPad("c1_2", "newpad",0.01,0.25,0.99,0.99);
  // c1_2->Draw();

  // c1->cd();
  // c1_2->cd();
  // c1_2->SetTopMargin(0.1);
  // c1_2->SetBottomMargin(0.1);
  // c1_2->SetRightMargin(0.05);
  // c1_2->SetLeftMargin(0.15);
  // c1_2->SetFillStyle(0);
  // hData->GetXaxis()->SetRangeUser(1,y_max_scale * hData->GetMaximum());

  hData->GetXaxis()->SetRangeUser(0, x_max_scale);
  hData->SetMaximum(y_max_scale * hData->GetMaximum() + 20);
  hData->SetMinimum(0.0001 );
  hData->GetYaxis()->SetTitle(yAxisLabel.c_str());
  hData->GetYaxis()->SetTitleSize(0.065);
  hData->GetYaxis()->SetTitleOffset(0.9); // 0.7);
  hData->GetYaxis()->SetLabelSize(0.06);
  // hData->SetMarkerStyle(20);
  // hData->SetMarkerSize(1.0);
  // hData->SetLineColor(kBlack);
  hData->SetTitle("");


  hData->SetLineColor(1);
  hData->SetFillColor(1);
  hData->SetFillStyle(0);
  hData->SetLineWidth(2);
  hData->SetMarkerStyle(20);
  hData->SetMarkerSize(1.5);

  hData->GetXaxis()->SetNdivisions(506);
  hData->GetXaxis()->SetLabelFont(42);
  hData->GetXaxis()->SetLabelSize(0);
  hData->GetXaxis()->SetTitleSize(0.0475);
  hData->GetXaxis()->SetTickLength(0.045);
  hData->GetXaxis()->SetTitleOffset(1.15);
  hData->GetXaxis()->SetTitleFont(42);
  hData->GetYaxis()->SetTitle(yAxisLabel.c_str());
  hData->GetYaxis()->SetNdivisions(506);
  hData->GetYaxis()->SetLabelFont(42);
  hData->GetYaxis()->SetLabelSize(0.06375);
  hData->GetYaxis()->SetTitleSize(0.07125);
  hData->GetYaxis()->SetTitleOffset(0.9);
  hData->GetYaxis()->SetTitleFont(42);
  hData->GetZaxis()->SetLabelFont(42);
  hData->GetZaxis()->SetLabelSize(0.0425);
  hData->GetZaxis()->SetTitleSize(0.0475);
  hData->GetZaxis()->SetTitleFont(42);

  // hData->GetXaxis()->SetRange(1,120);
  // hData->GetXaxis()->SetLabelFont(42);
  // hData->GetXaxis()->SetLabelSize(0.0425);
  // hData->GetXaxis()->SetTitleSize(0.0475);
  // hData->GetXaxis()->SetTitleOffset(1.15);
  // hData->GetXaxis()->SetTitleFont(42);
  // hData->GetYaxis()->SetLabelFont(42);
  // hData->GetYaxis()->SetLabelSize(0.0425);
  // hData->GetYaxis()->SetTitleSize(0.0475);
  // hData->GetYaxis()->SetTitleOffset(1.35);
  // hData->GetYaxis()->SetTitleFont(42);
  // hData->GetZaxis()->SetLabelFont(42);
  // hData->GetZaxis()->SetLabelSize(0.0425);
  // hData->GetZaxis()->SetTitleSize(0.0475);
  // hData->GetZaxis()->SetTitleFont(42);

  // hData->SetBinErrorOption(TH1::kPoisson);
  // if (legswitch) hData->GetYaxis()->SetRangeUser(1,hData->GetMaximum()*2.2);
  hData->Draw("lepx0");//E0");

  THStack *stack = new THStack();
  stack->Add(hQCD );
  stack->Add( hTT );
  stack->Draw("hist same");




  hData->Draw("lepsamex0");

  //errors                                                                                                                                
  float xsErr_top = 0.15;
  float lumiErr_top = 0.027;
  float topTagErr_top = 2*(0.09/0.89);
  float totalTopErr = 0.0;
  float totalQCDErr = 0.0;
  float totalHistErr = 0.0;

  TH1F *totalH = (TH1F *) hQCD->Clone("totalH");
  totalH->Add(hTT);

  totalH->SetFillColor(202);
  totalH->SetFillStyle(3254);

  //    totalH->SetFillStyle(3001);
  //    totalH->SetFillColor(kGray+1);
  totalH->Draw("E2 same");

	
  hZp30->SetFillStyle(0);
  hZp30->SetLineColor(1);
  hZp30->SetLineStyle(2);
  hZp30->SetLineWidth(2);
  hZp30->Draw("samehist");

  hData->Draw("lepsamex0");

  // hZp10->SetLineColor(kBlue);
  // hZp20->SetLineColor(kGreen+1);
  // hZp30->SetLineColor(kViolet);
  // hZp40->SetLineColor(7);
  // hZp10->SetLineWidth(2);
  // hZp20->SetLineWidth(2);
  // hZp30->SetLineWidth(2);
  // hZp40->SetLineWidth(2);



  TLatex *   tex = new TLatex(0.181,0.77,"#font[62]{CMS}");//" #font[52]{Preliminary}");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.0825);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(0.96,0.895,"2.6 fb^{-1} (13 TeV)");
  tex->SetNDC();
  tex->SetTextAlign(31);
  tex->SetTextFont(42);
  tex->SetTextSize(0.0575);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(0.181,0.71225,pave);
  tex->SetNDC();
  tex->SetTextAlign(13);
  tex->SetTextFont(42);
  tex->SetTextSize(0.045);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(0.14,0.895,"fully hadronic");
  tex->SetNDC();
  tex->SetTextAlign(11);
  tex->SetTextFont(42);
  tex->SetTextSize(0.0575);
  tex->SetLineWidth(2);
  tex->Draw();
  

  // double leg1 =0.6; double leg2 =0.49; double leg3 =0.91; double leg4 =0.8;
  double leg1 =0.5; double leg2 =0.49; double leg3 =0.85; double leg4 =0.8;
  TLegend *leg = new TLegend(leg1, leg2, leg3, leg4);
  leg->SetTextSize(0.057);
  leg->AddEntry(hData, "Data", "ep");
  leg->AddEntry(hQCD, "QCD", "f");
  leg->AddEntry(hTT, "t#bar{t}", "f");
  //    leg->AddEntry(hZp20, "2 TeV Narrow Z'", "l");
  // leg->AddEntry(hZp30, "3 TeV Narrow Z'", "l");
  // leg->AddEntry(hZp40, "4 TeV Narrow Z'", "l");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
	
  // TLegend *leg = new TLegend(0.181,0.4642,0.468,0.7414,NULL,"brNDC");
	
  //double peg1 =0.181; double peg2 =0.27335; double peg3 =0.468; double peg4 =0.55055;
  double peg1 =0.181; double peg2 =0.3542; double peg3 =0.468; double peg4 =0.6314;
  // double peg1 =0.14; double peg2 =0.51; double peg3 =0.38; double peg4 =0.77;
  // double peg1 =0.14; double peg2 =0.47; double peg3 =0.38; double peg4 =0.73;
  // double peg1 =0.3; double peg2 =0.49; double peg3 =0.7; double peg4 =0.8;
  if (paveSplitLine){
    peg2 = 0.28335;
    peg4 = 0.56055;
  }
  TLegend *peg = new TLegend(peg1, peg2, peg3, peg4,NULL,"brNDC");
  peg->SetBorderSize(0);
  peg->SetLineColor(1);
  peg->SetLineStyle(1);
  peg->SetLineWidth(1);
  peg->SetFillColor(0);
  peg->SetFillStyle(1001);
	
  peg->SetTextSize(0.045);
  peg->AddEntry(hData, "Data", "ep");
  peg->AddEntry(hTT, "t#bar{t}", "f");

  peg->AddEntry(hQCD, "QCD", "f");
  peg->AddEntry(hZp30,"Z' 3 TeV (#sigma=1 pb)","L");

  //    peg->AddEntry(hZp20, "2 TeV Narrow Z'", "l");
  // peg->AddEntry(hZp30, "3 TeV Narrow Z'", "l");
  // peg->AddEntry(hZp40, "4 TeV Narrow Z'", "l");
  peg->SetFillColor(0);
  peg->SetLineColor(0);
    
  if (legswitch)  peg->Draw("same");
  if (!legswitch) leg->Draw("same");
	
  gPad->RedrawAxis();


  pad1->Modified();
  c1->cd();

  // hZp10->Draw("hist same");
  // hZp20->Draw("hist same");
  // hZp30->Draw("hist same");
  // hZp40->Draw("hist same");

  // TLatex *categoryLabel = new TLatex();
  // categoryLabel->SetNDC();
  // categoryLabel->SetTextFont(62);
  // categoryLabel->SetTextSizePixels(20);

  // // categoryLabel->DrawLatex(0.7, 0.85, pave);
  // categoryLabel->DrawLatex(0.6, 0.85, pave);


  // TPaveText *textbox1 = new TPaveText(0.54,0.85,0.93,0.89,"NDC");
  // textbox1->SetFillColor(0);
  // textbox1->SetLineColor(0);
  // TText *line1 = textbox1->AddText(pave);
  // line1->SetTextColor(1);
  // // line1->SetTextSize(23);
  // line1->SetTextFont(62);//43);
  // line1->SetTextSizePixels(26);//43);
  // line1->SetTextAlign(33); //first number = horizontal alignment (1 left, 2 center, 3 right). second number =vertical alignment (1 top, 2 center, 3 bottom)
  // textbox1->Draw("same");


  // if (tag == 0) categoryLabel->DrawLatex(0.7, 0.85, "0 b-tags, |#Deltay| < 1.0");
  // if (tag == 1) categoryLabel->DrawLatex(0.7, 0.85, "1 b-tag, |#Deltay| < 1.0");
  // if (tag == 2) categoryLabel->DrawLatex(0.7, 0.85, "2 b-tags, |#Deltay| < 1.0");
  // if (tag == 3) categoryLabel->DrawLatex(0.7, 0.85, "0 b-tags, |#Deltay| > 1.0");
  // if (tag == 4) categoryLabel->DrawLatex(0.7, 0.85, "1 b-tag, |#Deltay| > 1.0");
  // if (tag == 5) categoryLabel->DrawLatex(0.7, 0.85, "2 b-tags, |#Deltay| > 1.0");
  // if (tag == 6) categoryLabel->DrawLatex(0.7, 0.85, "All Signal Regions");

  // CMS_lumi(pad1, 4, 10);


   


  TPad *pad2 = new TPad("pad2", "pad2",0,0,1,0.3333333);
  pad2->Draw();
  pad2->cd();
  // pad2->Range(-0.1792683,-1.370091,1.10122,1.899);
  pad2->SetFillColor(0);
  pad2->SetBorderMode(0);
  pad2->SetBorderSize(2);
  pad2->SetTickx(1);
  pad2->SetTicky(1);
  pad2->SetLeftMargin(0.14);
  pad2->SetRightMargin(0.04);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.45);
  pad2->SetFrameFillStyle(0);
  pad2->SetFrameBorderMode(0);
  pad2->SetFrameFillStyle(0);
  pad2->SetFrameBorderMode(0);
   
  TH1F *ratioH = new TH1F();
  ratioH = (TH1F*) hData->Clone("ratio");
  ratioH->Sumw2();
  ratioH->Divide(ratioH, totalH);
   
  TH1F *ratioErrH = new TH1F();
  ratioErrH = (TH1F*) totalH->Clone("ratioErr");
  ratioErrH->Sumw2();
  ratioErrH->Divide(ratioErrH, totalH);

  ratioH->GetYaxis()->SetRangeUser(0.01,1.99);
  // ratioH->GetYaxis()->SetTitle("Data / Bkgd");
  // ratioH->GetYaxis()->SetTitleOffset(0.3);
  // ratioH->GetYaxis()->SetTitleSize(0.17);
  // ratioH->GetYaxis()->SetNdivisions(205);
  // ratioH->GetYaxis()->SetLabelSize(0.11);
  // ratioH->GetXaxis()->SetLabelSize(0.11);
  // ratioH->GetXaxis()->SetTitleSize(0.17);
  ratioH->GetXaxis()->SetTitle( histtitle );

  ratioH->SetStats(0);
  ratioH->SetFillColor(1);
  ratioH->SetFillStyle(0);
  ratioH->SetLineWidth(2);
  ratioH->SetLineColor(1);
  ratioH->SetMarkerStyle(20);
  ratioH->SetMarkerSize(1.5);
  ratioH->GetXaxis()->SetNdivisions(506);
  ratioH->GetXaxis()->SetLabelFont(42);
  ratioH->GetXaxis()->SetLabelOffset(0.015);
  ratioH->GetXaxis()->SetLabelSize(0.1275);
  ratioH->GetXaxis()->SetTitleSize(0.1425);
  ratioH->GetXaxis()->SetTickLength(0.09);
  ratioH->GetXaxis()->SetTitleOffset(1.15);
  ratioH->GetXaxis()->SetTitleFont(42);
  ratioH->GetYaxis()->SetTitle("Data/bkg");
  ratioH->GetYaxis()->CenterTitle(true);
  ratioH->GetYaxis()->SetNdivisions(304);
  ratioH->GetYaxis()->SetLabelFont(42);
  ratioH->GetYaxis()->SetLabelSize(0.1275);
  ratioH->GetYaxis()->SetTitleSize(0.1425);
  ratioH->GetYaxis()->SetTickLength(0.045);
  ratioH->GetYaxis()->SetTitleOffset(0.45);
  ratioH->GetYaxis()->SetTitleFont(42);
  ratioH->GetZaxis()->SetLabelFont(42);
  ratioH->GetZaxis()->SetLabelSize(0.0425);
  ratioH->GetZaxis()->SetTitleSize(0.0475);
  ratioH->GetZaxis()->SetTitleFont(42);

  ratioH->Draw("lepe0x0");

  //remove large error bars from bins with no data
  int n_xbins = totalH->GetNbinsX() + 1;
  for (int i_bin=1;i_bin<n_xbins;i_bin++){
    if(hData->GetBinContent(i_bin) == 0.0) ratioErrH->SetBinContent(i_bin,0.0);
  }

  ratioErrH->SetFillStyle(1001);
  ratioErrH->SetFillColor(kGray);

  ratioErrH->Draw("E2 same");

  TF1 *line = new TF1("line", "1", -7000, 7000);
  line->SetLineColor(kBlack);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw("same");
  ratioH->Draw("E0X0 same");

  gPad->RedrawAxis();
     
  pad2->Modified();
  c1->cd();
  c1->Modified();
  c1->cd();
  c1->SetSelected(c1);     

  c1->SaveAs("plots_74X/plotsKinematic/"+histname+"_pt400.pdf");
  c1->SaveAs("plots_74X/plotsKinematic/pngcopy_"+histname+"_pt400.png");
  
  //c1->SetGrayscale();
  //c1->SaveAs("plots_74X/plotsKinematic/grayscale_"+histname+"_pt400.pdf");

  pad1->cd();
  hData->SetMaximum(100.0 * hData->GetMaximum() );
  pad1->SetLogy(1);
  c1->SaveAs("plots_74X/plotsKinematic/"+histname+"_pt400_log.pdf");
  c1->SaveAs("plots_74X/plotsKinematic/pngcopy_"+histname+"_pt400_log.png");

}
