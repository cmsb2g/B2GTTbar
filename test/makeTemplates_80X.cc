//Script to make templates for shape analysis using Theta
//to do: set up for extra wide, 4.5 TeV Z' narrow and RSG, and 5 TeV RSG samples
//add boolean for blinded/unblinded
//
//root -l
//.L makeTemplates_80X.cc
//makeTemplates_80X(int signal = 0, bool forTHETA = 1, bool postFit = 0, bool ttReweighting = 1, bool forCombo = 1, string dateLabel = "ApplybTagSFbySubjetPuppiEffTest20170625_ht950_pt400_WPB_alt40_alt260_bM_PUw")

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
#include "TString.h"
#include <vector> 
#include <algorithm>
#include "TROOT.h"
#include "names.C"
#include "CMS_lumi.C"

using namespace std;
using namespace names;

int makeTemplates_80X(int signal = 0, bool forTHETA = 1, bool postFit = 0, bool ttReweighting = 1, bool forCombo = 0, int blinding = 1, string dateLabel = "FixedBtagSFandSyst20180406_ht950_pt400_WPB_alt40_alt260_bM_PUw",string xVar="DijetMass", int rebin_factor = 10){
//signal: 0 = ZPN, 1 = ZPW, 2 = ZPXW, 3 = RSG
//blinding: 0 = unblinded, 1 = blinded above 2 TeV, 2 = fully blinded

  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0000000000); //this clears all the boxes and crap 

  cout << names::NUM_PROCS << endl;
  cout << rebin_factor << endl;

  int numProcs = names::NUM_PROCS;

  //determining working point
  std::size_t foundWPA = dateLabel.find("WPA");//tau32 < 0.80
  std::size_t foundWPB = dateLabel.find("WPB");//tau32 < 0.65
  std::size_t foundWPC = dateLabel.find("WPC");//tau32 < 0.54

  string dateLabel_TTw = Form("%s_TTw",dateLabel.c_str());
  string dateLabel_noTTw = Form("%s_noTTw",dateLabel.c_str());

  //determining whether or not dijet mass is being plotted
  std::size_t foundDijetMass = xVar.find("DijetMass");

  //naming output file
  string outEnd = Form("%s_%s",xVar.c_str(),dateLabel_TTw.c_str());
  if (!ttReweighting) outEnd = Form("%s_%s",xVar.c_str(),dateLabel_noTTw.c_str());
  if (forTHETA) outEnd = Form("%s_forTHETA",outEnd.c_str());
  if (forCombo) outEnd = Form("%s_forCombo",outEnd.c_str());
  if (postFit) outEnd = Form("%s_postFit",outEnd.c_str());

  if (blinding == 1) outEnd = Form("%s_partiallyBlinded",outEnd.c_str());
  if (blinding == 2) outEnd = Form("%s_fullyBlinded",outEnd.c_str());

  string file = Form("templates_narrow_%s.root", outEnd.c_str());//ZPN
  if (signal == 1) file = Form("templates_wide_%s.root", outEnd.c_str());
  else if (signal == 2) file = Form("templates_extrawide_%s.root", outEnd.c_str());
  else if (signal == 3) file = Form("templates_RSGluon_%s.root", outEnd.c_str());

  TFile *outFile;
  if (!postFit) outFile = new TFile(Form("%s",file.c_str()),"RECREATE");

  TString labels[200];
  labels[names::DATA] = "data";
  labels[names::QCD]  = "qcd";
  labels[names::QCD_SYST]  = "qcdsyst";
  labels[names::QCDMC]  = "qcdmc";
  labels[names::QCDMC_SYST]  = "qcdmcsyst";
  labels[names::TT] = "ttbar";
  labels[names::TT_SUBTRACT] = "ttbar_subtract";
  labels[names::TT_SUBTRACTSYST] = "ttbar_subtractsyst";
  labels[names::TT_SCALEUP] = "ttbar_jes_up";
  labels[names::TT_SCALEDN] = "ttbar_jes_dn";
  labels[names::TT_JERUP] = "ttbar_jer_up";
  labels[names::TT_JERDN] = "ttbar_jer_dn";
  labels[names::TT_BTAGUP] = "ttbar_bTag_up";
  labels[names::TT_BTAGDN] = "ttbar_bTag_dn";
  labels[names::TT_BMISTAGUP] = "ttbar_bmisTag_up";
  labels[names::TT_BMISTAGDN] = "ttbar_bmisTag_dn";
  labels[names::TT_Q2UP] = "ttbar_q2_up";
  labels[names::TT_Q2DN] = "ttbar_q2_dn";
  labels[names::TT_PDFUP] = "ttbar_pdf_up";
  labels[names::TT_PDFDN] = "ttbar_pdf_dn";
  labels[names::TT_PUUP] = "ttbar_PU_up";
  labels[names::TT_PUDN] = "ttbar_PU_dn";
  labels[names::TT_WEIGHTSYST] = "ttbar_weightsyst";
  labels[names::ZPN10] = "ZpN10";
  labels[names::ZPN12p5] = "ZpN12p5";
  labels[names::ZPN15] = "ZpN15";
  labels[names::ZPN20] = "ZpN20";
  labels[names::ZPN25] = "ZpN25";
  labels[names::ZPN30] = "ZpN30";
  labels[names::ZPN35] = "ZpN35";
  labels[names::ZPN40] = "ZpN40";
  labels[names::ZPN10_SCALEUP] = "ZpN10_jes_up" ;
  labels[names::ZPN12p5_SCALEUP] = "ZpN12p5_jes_up" ;
  labels[names::ZPN15_SCALEUP] = "ZpN15_jes_up" ;
  labels[names::ZPN20_SCALEUP] = "ZpN20_jes_up" ;
  labels[names::ZPN25_SCALEUP] = "ZpN25_jes_up" ;
  labels[names::ZPN30_SCALEUP] = "ZpN30_jes_up" ;
  labels[names::ZPN35_SCALEUP] = "ZpN35_jes_up" ;
  labels[names::ZPN40_SCALEUP] = "ZpN40_jes_up" ;
  labels[names::ZPN10_SCALEDN] = "ZpN10_jes_dn" ;
  labels[names::ZPN12p5_SCALEDN] = "ZpN12p5_jes_dn" ;
  labels[names::ZPN15_SCALEDN] = "ZpN15_jes_dn" ;
  labels[names::ZPN20_SCALEDN] = "ZpN20_jes_dn" ;
  labels[names::ZPN25_SCALEDN] = "ZpN25_jes_dn" ;
  labels[names::ZPN30_SCALEDN] = "ZpN30_jes_dn" ;
  labels[names::ZPN35_SCALEDN] = "ZpN35_jes_dn" ;
  labels[names::ZPN40_SCALEDN] = "ZpN40_jes_dn" ;
  labels[names::ZPN10_JERUP]   = "ZpN10_jer_up" ;
  labels[names::ZPN12p5_JERUP]   = "ZpN12p5_jer_up" ;
  labels[names::ZPN15_JERUP]   = "ZpN15_jer_up" ;
  labels[names::ZPN20_JERUP]   = "ZpN20_jer_up" ;
  labels[names::ZPN25_JERUP]   = "ZpN25_jer_up" ;
  labels[names::ZPN30_JERUP]   = "ZpN30_jer_up" ;
  labels[names::ZPN35_JERUP]   = "ZpN35_jer_up" ;
  labels[names::ZPN40_JERUP]   = "ZpN40_jer_up" ;
  labels[names::ZPN10_JERDN]   = "ZpN10_jer_dn" ;
  labels[names::ZPN12p5_JERDN]   = "ZpN12p5_jer_dn" ;
  labels[names::ZPN15_JERDN]   = "ZpN15_jer_dn" ;
  labels[names::ZPN20_JERDN]   = "ZpN20_jer_dn" ;
  labels[names::ZPN25_JERDN]   = "ZpN25_jer_dn" ;
  labels[names::ZPN30_JERDN]   = "ZpN30_jer_dn" ;
  labels[names::ZPN35_JERDN]   = "ZpN35_jer_dn" ;
  labels[names::ZPN40_JERDN]   = "ZpN40_jer_dn" ;
  labels[names::ZPN10_PDFUP]  = "ZpN10_pdf_up";
  labels[names::ZPN12p5_PDFUP]  = "ZpN12p5_pdf_up";
  labels[names::ZPN15_PDFUP]  = "ZpN15_pdf_up";
  labels[names::ZPN20_PDFUP]  = "ZpN20_pdf_up";
  labels[names::ZPN25_PDFUP]  = "ZpN25_pdf_up";
  labels[names::ZPN30_PDFUP]  = "ZpN30_pdf_up";
  labels[names::ZPN35_PDFUP]  = "ZpN35_pdf_up";
  labels[names::ZPN40_PDFUP]  = "ZpN40_pdf_up";
  labels[names::ZPN10_PDFDN]  = "ZpN10_pdf_dn";
  labels[names::ZPN12p5_PDFDN]  = "ZpN12p5_pdf_dn";
  labels[names::ZPN15_PDFDN]  = "ZpN15_pdf_dn";
  labels[names::ZPN20_PDFDN]  = "ZpN20_pdf_dn";
  labels[names::ZPN25_PDFDN]  = "ZpN25_pdf_dn";
  labels[names::ZPN30_PDFDN]  = "ZpN30_pdf_dn";
  labels[names::ZPN35_PDFDN]  = "ZpN35_pdf_dn";
  labels[names::ZPN40_PDFDN]  = "ZpN40_pdf_dn"; 
  labels[names::ZPN10_BTAGUP]  = "ZpN10_bTag_up";
  labels[names::ZPN12p5_BTAGUP]  = "ZpN12p5_bTag_up";
  labels[names::ZPN15_BTAGUP]  = "ZpN15_bTag_up";
  labels[names::ZPN20_BTAGUP]  = "ZpN20_bTag_up";
  labels[names::ZPN25_BTAGUP]  = "ZpN25_bTag_up";
  labels[names::ZPN30_BTAGUP]  = "ZpN30_bTag_up";
  labels[names::ZPN35_BTAGUP]  = "ZpN35_bTag_up";
  labels[names::ZPN40_BTAGUP]  = "ZpN40_bTag_up";
  labels[names::ZPN10_BTAGDN]  = "ZpN10_bTag_dn";
  labels[names::ZPN12p5_BTAGDN]  = "ZpN12p5_bTag_dn";
  labels[names::ZPN15_BTAGDN]  = "ZpN15_bTag_dn";
  labels[names::ZPN20_BTAGDN]  = "ZpN20_bTag_dn";
  labels[names::ZPN25_BTAGDN]  = "ZpN25_bTag_dn";
  labels[names::ZPN30_BTAGDN]  = "ZpN30_bTag_dn";
  labels[names::ZPN35_BTAGDN]  = "ZpN35_bTag_dn";
  labels[names::ZPN40_BTAGDN]  = "ZpN40_bTag_dn";
  labels[names::ZPN10_BMISTAGUP]  = "ZpN10_bMistag_up";
  labels[names::ZPN12p5_BMISTAGUP]  = "ZpN12p5_bMistag_up";
  labels[names::ZPN15_BMISTAGUP]  = "ZpN15_bMistag_up";
  labels[names::ZPN20_BMISTAGUP]  = "ZpN20_bMistag_up";
  labels[names::ZPN25_BMISTAGUP]  = "ZpN25_bMistag_up";
  labels[names::ZPN30_BMISTAGUP]  = "ZpN30_bMistag_up";
  labels[names::ZPN35_BMISTAGUP]  = "ZpN35_bMistag_up";
  labels[names::ZPN40_BMISTAGUP]  = "ZpN40_bMistag_up";
  labels[names::ZPN10_BMISTAGDN]  = "ZpN10_bMistag_dn";
  labels[names::ZPN12p5_BMISTAGDN]  = "ZpN12p5_bMistag_dn";
  labels[names::ZPN15_BMISTAGDN]  = "ZpN15_bMistag_dn";
  labels[names::ZPN20_BMISTAGDN]  = "ZpN20_bMistag_dn";
  labels[names::ZPN25_BMISTAGDN]  = "ZpN25_bMistag_dn";
  labels[names::ZPN30_BMISTAGDN]  = "ZpN30_bMistag_dn";
  labels[names::ZPN35_BMISTAGDN]  = "ZpN35_bMistag_dn";
  labels[names::ZPN40_BMISTAGDN]  = "ZpN40_bMistag_dn";
  labels[names::ZPN10_PUUP]  = "ZpN10_PU_up";
  labels[names::ZPN12p5_PUUP]  = "ZpN12p5_PU_up";
  labels[names::ZPN15_PUUP]  = "ZpN15_PU_up";
  labels[names::ZPN20_PUUP]  = "ZpN20_PU_up";
  labels[names::ZPN25_PUUP]  = "ZpN25_PU_up";
  labels[names::ZPN30_PUUP]  = "ZpN30_PU_up";
  labels[names::ZPN35_PUUP]  = "ZpN35_PU_up";
  labels[names::ZPN40_PUUP]  = "ZpN40_PU_up";
  labels[names::ZPN10_PUDN]  = "ZpN10_PU_dn";
  labels[names::ZPN12p5_PUDN]  = "ZpN12p5_PU_dn";
  labels[names::ZPN15_PUDN]  = "ZpN15_PU_dn";
  labels[names::ZPN20_PUDN]  = "ZpN20_PU_dn";
  labels[names::ZPN25_PUDN]  = "ZpN25_PU_dn";
  labels[names::ZPN30_PUDN]  = "ZpN30_PU_dn";
  labels[names::ZPN35_PUDN]  = "ZpN35_PU_dn";
  labels[names::ZPN40_PUDN]  = "ZpN40_PU_dn";
  labels[names::ZPN45] = "ZpN45";
  labels[names::ZPN50] = "ZpN50";
  labels[names::ZPN45_SCALEUP] = "ZpN45_jes_up" ;
  labels[names::ZPN50_SCALEUP] = "ZpN50_jes_up" ;
  labels[names::ZPN45_SCALEDN] = "ZpN45_jes_dn" ;
  labels[names::ZPN50_SCALEDN] = "ZpN50_jes_dn" ;
  labels[names::ZPN45_JERUP]   = "ZpN45_jer_up" ;
  labels[names::ZPN50_JERUP]   = "ZpN50_jer_up" ;
  labels[names::ZPN45_JERDN]   = "ZpN45_jer_dn" ;
  labels[names::ZPN50_JERDN]   = "ZpN50_jer_dn" ;
  labels[names::ZPN45_PDFUP]  = "ZpN45_pdf_up";
  labels[names::ZPN50_PDFUP]  = "ZpN50_pdf_up";
  labels[names::ZPN45_PDFDN]  = "ZpN45_pdf_dn";
  labels[names::ZPN50_PDFDN]  = "ZpN50_pdf_dn"; 
  labels[names::ZPN45_BTAGUP]  = "ZpN45_bTag_up";
  labels[names::ZPN50_BTAGUP]  = "ZpN50_bTag_up";
  labels[names::ZPN45_BTAGDN]  = "ZpN45_bTag_dn";
  labels[names::ZPN50_BTAGDN]  = "ZpN50_bTag_dn";
  labels[names::ZPN45_BMISTAGUP]  = "ZpN45_bMistag_up";
  labels[names::ZPN50_BMISTAGUP]  = "ZpN50_bMistag_up";
  labels[names::ZPN45_BMISTAGDN]  = "ZpN45_bMistag_dn";
  labels[names::ZPN50_BMISTAGDN]  = "ZpN50_bMistag_dn";
  labels[names::ZPN45_PUUP]  = "ZpN45_PU_up";
  labels[names::ZPN50_PUUP]  = "ZpN50_PU_up";
  labels[names::ZPN45_PUDN]  = "ZpN45_PU_dn";
  labels[names::ZPN50_PUDN]  = "ZpN50_PU_dn";
  labels[names::ZPN60] = "ZpN60";
  labels[names::ZPN60_SCALEUP] = "ZpN60_jes_up" ;
  labels[names::ZPN60_SCALEDN] = "ZpN60_jes_dn" ;
  labels[names::ZPN60_JERUP]   = "ZpN60_jer_up" ;
  labels[names::ZPN60_JERDN]   = "ZpN60_jer_dn" ;
  labels[names::ZPN60_PDFUP]  = "ZpN60_pdf_up";
  labels[names::ZPN60_PDFDN]  = "ZpN60_pdf_dn"; 
  labels[names::ZPN60_BTAGUP]  = "ZpN60_bTag_up";
  labels[names::ZPN60_BTAGDN]  = "ZpN60_bTag_dn";
  labels[names::ZPN60_BMISTAGUP]  = "ZpN60_bMistag_up";
  labels[names::ZPN60_BMISTAGDN]  = "ZpN60_bMistag_dn";
  labels[names::ZPN60_PUUP]  = "ZpN60_PU_up";
  labels[names::ZPN60_PUDN]  = "ZpN60_PU_dn";
  labels[names::ZPN65] = "ZpN65";
  labels[names::ZPN70] = "ZpN70";
  labels[names::ZPN65_SCALEUP] = "ZpN65_jes_up" ;
  labels[names::ZPN70_SCALEUP] = "ZpN70_jes_up" ;
  labels[names::ZPN65_SCALEDN] = "ZpN65_jes_dn" ;
  labels[names::ZPN70_SCALEDN] = "ZpN70_jes_dn" ;
  labels[names::ZPN65_JERUP]   = "ZpN65_jer_up" ;
  labels[names::ZPN70_JERUP]   = "ZpN70_jer_up" ;
  labels[names::ZPN65_JERDN]   = "ZpN65_jer_dn" ;
  labels[names::ZPN70_JERDN]   = "ZpN70_jer_dn" ;
  labels[names::ZPN65_PDFUP]  = "ZpN65_pdf_up";
  labels[names::ZPN70_PDFUP]  = "ZpN70_pdf_up";
  labels[names::ZPN65_PDFDN]  = "ZpN65_pdf_dn";
  labels[names::ZPN70_PDFDN]  = "ZpN70_pdf_dn"; 
  labels[names::ZPN65_BTAGUP]  = "ZpN65_bTag_up";
  labels[names::ZPN70_BTAGUP]  = "ZpN70_bTag_up";
  labels[names::ZPN65_BTAGDN]  = "ZpN65_bTag_dn";
  labels[names::ZPN70_BTAGDN]  = "ZpN70_bTag_dn";
  labels[names::ZPN65_BMISTAGUP]  = "ZpN65_bMistag_up";
  labels[names::ZPN70_BMISTAGUP]  = "ZpN70_bMistag_up";
  labels[names::ZPN65_BMISTAGDN]  = "ZpN65_bMistag_dn";
  labels[names::ZPN70_BMISTAGDN]  = "ZpN70_bMistag_dn";
  labels[names::ZPN65_PUUP]  = "ZpN65_PU_up";
  labels[names::ZPN70_PUUP]  = "ZpN70_PU_up";
  labels[names::ZPN65_PUDN]  = "ZpN65_PU_dn";
  labels[names::ZPN70_PUDN]  = "ZpN70_PU_dn";
  int nTagCats = 7;

  TString tagLabels[7];
  tagLabels[0] = "btag0_loDY_";
  tagLabels[1] = "btag1_loDY_";
  tagLabels[2] = "btag2_loDY_";
  tagLabels[3] = "btag0_hiDY_";  
  tagLabels[4] = "btag1_hiDY_";  
  tagLabels[5] = "btag2_hiDY_";  
  tagLabels[6] = "all_";

  TH1F *histos[names::NUM_PROCS][nTagCats];
  for (int h = 0; h < names::NUM_PROCS; h++){
    histos[h][0] = new TH1F();
    histos[h][1] = new TH1F();
    histos[h][2] = new TH1F();
    histos[h][3] = new TH1F();
    histos[h][4] = new TH1F();
    histos[h][5] = new TH1F();
    histos[h][6] = new TH1F();
  }

  //for yield table
  float TTerr[nTagCats];
  float QCDerr[nTagCats];
  float BKGerr[nTagCats];
  
  //TString dir = "/uscmst1b_scratch/lpc1/lpcphys/jdolen/B2G2016/V5/runs/histsBkgdEst_";
  TString dir = "/uscms/home/camclean/nobackup/B2G2016/CMSSW_8_0_26/src/Analysis/B2GTTbar/test/runs/histsBkgdEst_";
  TString infileBegin = dir + (TString) dateLabel_TTw + "_";
  TString ZP6plusFileBegin = dir + "bTagPuppiEffMeasurement20170623_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_";
  TString ttWeightSystfileBegin = dir + (TString) dateLabel_noTTw + "_";
  if (!ttReweighting){
    infileBegin = dir + (TString) dateLabel_noTTw;
    ttWeightSystfileBegin = dir + (TString) dateLabel_TTw;
  }
  TString ttFileBegin = dir + "ForDeltaRapPlots20180425_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_";
  ttWeightSystfileBegin = dir + "ForDeltaRapPlots20180425_ht950_pt400_WPB_alt40_alt260_bM_PUw_noTTw_";
  //TString TTend = "_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2";
  TString TTend = "_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2";
  TString sigEnd = "RunIISummer16MiniAODv2";

  TString files[200];
  //files[names::DATA]          = infileBegin + "nom_b2gtreeV5_JetHT_all.root";
  files[names::DATA]          = dir + "ForDeltaRapPlots20180425_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_JetHT_all.root";
  files[names::QCD]           = files[names::DATA];
  files[names::QCD_SYST]      = files[names::DATA];
  files[names::QCDMC]         = dir + "forQCDclosure_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_QCD_Ptscaled.root";
  files[names::QCDMC_SYST]    = files[names::QCDMC];
  files[names::TT]            = ttFileBegin + "nom" + TTend + ".root";
  files[names::TT_WEIGHTSYST] = ttWeightSystfileBegin + "nom" + TTend + ".root";
  files[names::TT_SUBTRACT]   = ttFileBegin + "nom" + TTend + ".root";
  files[names::TT_SUBTRACTSYST]   = ttFileBegin + "nom" + TTend + ".root";
  files[names::TT_JERUP]      = ttFileBegin + "jer_up" + TTend + ".root";
  files[names::TT_JERDN]      = ttFileBegin + "jer_dn" + TTend + ".root";
  files[names::TT_SCALEUP]    = ttFileBegin + "jec_up" + TTend + ".root";
  files[names::TT_SCALEDN]    = ttFileBegin + "jec_dn" + TTend + ".root";
  files[names::TT_PDFUP]      = ttFileBegin + "pdf_up" + TTend + ".root";
  files[names::TT_PDFDN]      = ttFileBegin + "pdf_dn" + TTend + ".root";
  files[names::TT_Q2UP]       = ttFileBegin + "q2_up" + TTend + ".root";
  files[names::TT_Q2DN]       = ttFileBegin + "q2_dn" + TTend + ".root";
  files[names::TT_BTAGUP]     = ttFileBegin + "bTag_up" + TTend + ".root";
  files[names::TT_BTAGDN]     = ttFileBegin + "bTag_dn" + TTend + ".root";
  files[names::TT_BMISTAGUP]     = ttFileBegin + "bMistag_up" + TTend + ".root";
  files[names::TT_BMISTAGDN]     = ttFileBegin + "bMistag_dn" + TTend + ".root";
  files[names::TT_PUUP]     = ttFileBegin + "PU_up" + TTend + ".root";
  files[names::TT_PUDN]     = ttFileBegin + "PU_dn" + TTend + ".root";

  TString systLabel = "nom";

  if (signal == 0){//ZPN
    files[names::ZPN10]         = infileBegin + systLabel + "_ZprimeToTT_M-1000_W-10_" + sigEnd; //+ ".root";
    files[names::ZPN12p5]       = infileBegin + systLabel + "_ZprimeToTT_M-1250_W-12p5_" + sigEnd; //+ ".root";
    files[names::ZPN15]         = infileBegin + systLabel + "_ZprimeToTT_M-1500_W-15_" + sigEnd + "_all"; //+ ".root";
    files[names::ZPN20]         = infileBegin + systLabel + "_ZprimeToTT_M-2000_W-20_" + sigEnd; //+ ".root";
    files[names::ZPN25]         = infileBegin + systLabel + "_ZprimeToTT_M-2500_W-25_" + sigEnd; //+ ".root";
    files[names::ZPN30]         = infileBegin + systLabel + "_ZprimeToTT_M-3000_W-30_" + sigEnd; //+ ".root";
    files[names::ZPN35]         = infileBegin + systLabel + "_ZprimeToTT_M-3500_W-35_" + sigEnd; //+ ".root";
    files[names::ZPN40]         = infileBegin + systLabel + "_ZprimeToTT_M-4000_W-40_" + sigEnd; //+ ".root";
    files[names::ZPN45]         = infileBegin + systLabel + "_ZprimeToTT_M-4500_W-45_" + sigEnd; //+ ".root";
    files[names::ZPN50]         = infileBegin + systLabel + "_ZprimeToTT_M-5000_W-50_" + sigEnd; //+ ".root";
    files[names::ZPN60]         = files[names::ZPN50]; //ZP6plusFileBegin + systLabel + "_ZprimeToTT_M-6000_W-60_" + sigEnd + ".root";
    files[names::ZPN65]         = ZP6plusFileBegin + systLabel + "_ZprimeToTT_M-6500_W-65_" + sigEnd + ".root";
    files[names::ZPN70]         = ZP6plusFileBegin + systLabel + "_ZprimeToTT_M-7000_W-70_" + sigEnd + ".root";

    systLabel = "jec";
    files[names::ZPN10_SCALEUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1000_W-10_" + sigEnd; //+ ".root";
    files[names::ZPN12p5_SCALEUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1250_W-12p5_" + sigEnd; //+ ".root";
    files[names::ZPN15_SCALEUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1500_W-15_" + sigEnd + "_all"; //+ ".root";
    files[names::ZPN20_SCALEUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2000_W-20_" + sigEnd; //+ ".root";
    files[names::ZPN25_SCALEUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2500_W-25_" + sigEnd; //+ ".root";
    files[names::ZPN30_SCALEUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3000_W-30_" + sigEnd; //+ ".root";
    files[names::ZPN35_SCALEUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3500_W-35_" + sigEnd; //+ ".root";
    files[names::ZPN40_SCALEUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4000_W-40_" + sigEnd; //+ ".root";
    files[names::ZPN45_SCALEUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4500_W-45_" + sigEnd; //+ ".root";
    files[names::ZPN50_SCALEUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-5000_W-50_" + sigEnd; //+ ".root";
    files[names::ZPN60_SCALEUP]         = files[names::ZPN50]; //ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6000_W-60_" + sigEnd + ".root";
    files[names::ZPN65_SCALEUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6500_W-65_" + sigEnd + ".root";
    files[names::ZPN70_SCALEUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-7000_W-70_" + sigEnd + ".root";

    files[names::ZPN10_SCALEDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1000_W-10_" + sigEnd; //+ ".root";
    files[names::ZPN12p5_SCALEDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1250_W-12p5_" + sigEnd; //+ ".root";
    files[names::ZPN15_SCALEDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1500_W-15_" + sigEnd + "_all"; //+ ".root";
    files[names::ZPN20_SCALEDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2000_W-20_" + sigEnd; //+ ".root";
    files[names::ZPN25_SCALEDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2500_W-25_" + sigEnd; //+ ".root";
    files[names::ZPN30_SCALEDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3000_W-30_" + sigEnd; //+ ".root";
    files[names::ZPN35_SCALEDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3500_W-35_" + sigEnd; //+ ".root";
    files[names::ZPN40_SCALEDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4000_W-40_" + sigEnd; //+ ".root";
    files[names::ZPN45_SCALEDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4500_W-45_" + sigEnd; //+ ".root";
    files[names::ZPN50_SCALEDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-5000_W-50_" + sigEnd; //+ ".root";
    files[names::ZPN60_SCALEDN]         = files[names::ZPN50]; //ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6000_W-60_" + sigEnd + ".root";
    files[names::ZPN65_SCALEDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6500_W-65_" + sigEnd + ".root";
    files[names::ZPN70_SCALEDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-7000_W-70_" + sigEnd + ".root";
  
    systLabel = "jer";
    files[names::ZPN10_JERUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1000_W-10_" + sigEnd; //+ ".root";
    files[names::ZPN12p5_JERUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1250_W-12p5_" + sigEnd; //+ ".root";
    files[names::ZPN15_JERUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1500_W-15_" + sigEnd + "_all"; //+ ".root";
    files[names::ZPN20_JERUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2000_W-20_" + sigEnd; //+ ".root";
    files[names::ZPN25_JERUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2500_W-25_" + sigEnd; //+ ".root";
    files[names::ZPN30_JERUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3000_W-30_" + sigEnd; //+ ".root";
    files[names::ZPN35_JERUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3500_W-35_" + sigEnd; //+ ".root";
    files[names::ZPN40_JERUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4000_W-40_" + sigEnd; //+ ".root";
    files[names::ZPN45_JERUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4500_W-45_" + sigEnd; //+ ".root";
    files[names::ZPN50_JERUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-5000_W-50_" + sigEnd; //+ ".root";
    files[names::ZPN60_JERUP]         = files[names::ZPN50]; //ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6000_W-60_" + sigEnd + ".root";
    files[names::ZPN65_JERUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6500_W-65_" + sigEnd + ".root";
    files[names::ZPN70_JERUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-7000_W-70_" + sigEnd + ".root";

    files[names::ZPN10_JERDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1000_W-10_" + sigEnd; //+ ".root";
    files[names::ZPN12p5_JERDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1250_W-12p5_" + sigEnd; //+ ".root";
    files[names::ZPN15_JERDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1500_W-15_" + sigEnd + "_all"; //+ ".root";
    files[names::ZPN20_JERDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2000_W-20_" + sigEnd; //+ ".root";
    files[names::ZPN25_JERDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2500_W-25_" + sigEnd; //+ ".root";
    files[names::ZPN30_JERDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3000_W-30_" + sigEnd; //+ ".root";
    files[names::ZPN35_JERDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3500_W-35_" + sigEnd; //+ ".root";
    files[names::ZPN40_JERDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4000_W-40_" + sigEnd; //+ ".root";
    files[names::ZPN45_JERDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4500_W-45_" + sigEnd; //+ ".root";
    files[names::ZPN50_JERDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-5000_W-50_" + sigEnd; //+ ".root";
    files[names::ZPN60_JERDN]         = files[names::ZPN50]; //ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6000_W-60_" + sigEnd + ".root";
    files[names::ZPN65_JERDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6500_W-65_" + sigEnd + ".root";
    files[names::ZPN70_JERDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-7000_W-70_" + sigEnd + ".root";

    systLabel = "pdf";
    files[names::ZPN10_PDFUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1000_W-10_" + sigEnd; //+ ".root";
    files[names::ZPN12p5_PDFUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1250_W-12p5_" + sigEnd; //+ ".root";
    files[names::ZPN15_PDFUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1500_W-15_" + sigEnd + "_all"; //+ ".root";
    files[names::ZPN20_PDFUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2000_W-20_" + sigEnd; //+ ".root";
    files[names::ZPN25_PDFUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2500_W-25_" + sigEnd; //+ ".root";
    files[names::ZPN30_PDFUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3000_W-30_" + sigEnd; //+ ".root";
    files[names::ZPN35_PDFUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3500_W-35_" + sigEnd; //+ ".root";
    files[names::ZPN40_PDFUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4000_W-40_" + sigEnd; //+ ".root";
    files[names::ZPN45_PDFUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4500_W-45_" + sigEnd; //+ ".root";
    files[names::ZPN50_PDFUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-5000_W-50_" + sigEnd; //+ ".root";
    files[names::ZPN60_PDFUP]         = files[names::ZPN50]; //ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6000_W-60_" + sigEnd + ".root";
    files[names::ZPN65_PDFUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6500_W-65_" + sigEnd + ".root";
    files[names::ZPN70_PDFUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-7000_W-70_" + sigEnd + ".root";

    files[names::ZPN10_PDFDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1000_W-10_" + sigEnd; //+ ".root";
    files[names::ZPN12p5_PDFDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1250_W-12p5_" + sigEnd; //+ ".root";
    files[names::ZPN15_PDFDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1500_W-15_" + sigEnd + "_all"; //+ ".root";
    files[names::ZPN20_PDFDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2000_W-20_" + sigEnd; //+ ".root";
    files[names::ZPN25_PDFDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2500_W-25_" + sigEnd; //+ ".root";
    files[names::ZPN30_PDFDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3000_W-30_" + sigEnd; //+ ".root";
    files[names::ZPN35_PDFDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3500_W-35_" + sigEnd; //+ ".root";
    files[names::ZPN40_PDFDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4000_W-40_" + sigEnd; //+ ".root";
    files[names::ZPN45_PDFDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4500_W-45_" + sigEnd; //+ ".root";
    files[names::ZPN50_PDFDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-5000_W-50_" + sigEnd; //+ ".root";
    files[names::ZPN60_PDFDN]         = files[names::ZPN50]; //ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6000_W-60_" + sigEnd + ".root";
    files[names::ZPN65_PDFDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6500_W-65_" + sigEnd + ".root";
    files[names::ZPN70_PDFDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-7000_W-70_" + sigEnd + ".root";
    
    systLabel = "bTag";
    files[names::ZPN10_BTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1000_W-10_" + sigEnd; //+ ".root";
    files[names::ZPN12p5_BTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1250_W-12p5_" + sigEnd; //+ ".root";
    files[names::ZPN15_BTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1500_W-15_" + sigEnd + "_all"; //+ ".root";
    files[names::ZPN20_BTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2000_W-20_" + sigEnd; //+ ".root";
    files[names::ZPN25_BTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2500_W-25_" + sigEnd; //+ ".root";
    files[names::ZPN30_BTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3000_W-30_" + sigEnd; //+ ".root";
    files[names::ZPN35_BTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3500_W-35_" + sigEnd; //+ ".root";
    files[names::ZPN40_BTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4000_W-40_" + sigEnd; //+ ".root";
    files[names::ZPN45_BTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4500_W-45_" + sigEnd; //+ ".root";
    files[names::ZPN50_BTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-5000_W-50_" + sigEnd; //+ ".root";
    files[names::ZPN60_BTAGUP]         = files[names::ZPN50]; //ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6000_W-60_" + sigEnd + ".root";
    files[names::ZPN65_BTAGUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6500_W-65_" + sigEnd + ".root";
    files[names::ZPN70_BTAGUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-7000_W-70_" + sigEnd + ".root";

    files[names::ZPN10_BTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1000_W-10_" + sigEnd; //+ ".root";
    files[names::ZPN12p5_BTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1250_W-12p5_" + sigEnd; //+ ".root";
    files[names::ZPN15_BTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1500_W-15_" + sigEnd + "_all"; //+ ".root";
    files[names::ZPN20_BTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2000_W-20_" + sigEnd; //+ ".root";
    files[names::ZPN25_BTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2500_W-25_" + sigEnd; //+ ".root";
    files[names::ZPN30_BTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3000_W-30_" + sigEnd; //+ ".root";
    files[names::ZPN35_BTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3500_W-35_" + sigEnd; //+ ".root";
    files[names::ZPN40_BTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4000_W-40_" + sigEnd; //+ ".root";
    files[names::ZPN45_BTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4500_W-45_" + sigEnd; //+ ".root";
    files[names::ZPN50_BTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-5000_W-50_" + sigEnd; //+ ".root";
    files[names::ZPN60_BTAGDN]         = files[names::ZPN50]; //ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6000_W-60_" + sigEnd + ".root";
    files[names::ZPN65_BTAGDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6500_W-65_" + sigEnd + ".root";
    files[names::ZPN70_BTAGDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-7000_W-70_" + sigEnd + ".root";

    systLabel = "bMistag";
    files[names::ZPN10_BMISTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1000_W-10_" + sigEnd; //+ ".root";
    files[names::ZPN12p5_BMISTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1250_W-12p5_" + sigEnd; //+ ".root";
    files[names::ZPN15_BMISTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1500_W-15_" + sigEnd + "_all"; //+ ".root";
    files[names::ZPN20_BMISTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2000_W-20_" + sigEnd; //+ ".root";
    files[names::ZPN25_BMISTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2500_W-25_" + sigEnd; //+ ".root";
    files[names::ZPN30_BMISTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3000_W-30_" + sigEnd; //+ ".root";
    files[names::ZPN35_BMISTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3500_W-35_" + sigEnd; //+ ".root";
    files[names::ZPN40_BMISTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4000_W-40_" + sigEnd; //+ ".root";
    files[names::ZPN45_BMISTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4500_W-45_" + sigEnd; //+ ".root";
    files[names::ZPN50_BMISTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-5000_W-50_" + sigEnd; //+ ".root";
    files[names::ZPN60_BMISTAGUP]         = files[names::ZPN50]; //ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6000_W-60_" + sigEnd + ".root";
    files[names::ZPN65_BMISTAGUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6500_W-65_" + sigEnd + ".root";
    files[names::ZPN70_BMISTAGUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-7000_W-70_" + sigEnd + ".root";

    files[names::ZPN10_BMISTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1000_W-10_" + sigEnd; //+ ".root";
    files[names::ZPN12p5_BMISTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1250_W-12p5_" + sigEnd; //+ ".root";
    files[names::ZPN15_BMISTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1500_W-15_" + sigEnd + "_all"; //+ ".root";
    files[names::ZPN20_BMISTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2000_W-20_" + sigEnd; //+ ".root";
    files[names::ZPN25_BMISTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2500_W-25_" + sigEnd; //+ ".root";
    files[names::ZPN30_BMISTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3000_W-30_" + sigEnd; //+ ".root";
    files[names::ZPN35_BMISTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3500_W-35_" + sigEnd; //+ ".root";
    files[names::ZPN40_BMISTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4000_W-40_" + sigEnd; //+ ".root";
    files[names::ZPN45_BMISTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4500_W-45_" + sigEnd; //+ ".root";
    files[names::ZPN50_BMISTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-5000_W-50_" + sigEnd; //+ ".root";
    files[names::ZPN60_BMISTAGDN]         = files[names::ZPN50]; //ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6000_W-60_" + sigEnd + ".root";
    files[names::ZPN65_BMISTAGDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6500_W-65_" + sigEnd + ".root";
    files[names::ZPN70_BMISTAGDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-7000_W-70_" + sigEnd + ".root";

    systLabel = "PU";
    files[names::ZPN10_PUUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1000_W-10_" + sigEnd; //+ ".root";
    files[names::ZPN12p5_PUUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1250_W-12p5_" + sigEnd; //+ ".root";
    files[names::ZPN15_PUUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1500_W-15_" + sigEnd + "_all"; //+ ".root";
    files[names::ZPN20_PUUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2000_W-20_" + sigEnd; //+ ".root";
    files[names::ZPN25_PUUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2500_W-25_" + sigEnd; //+ ".root";
    files[names::ZPN30_PUUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3000_W-30_" + sigEnd; //+ ".root";
    files[names::ZPN35_PUUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3500_W-35_" + sigEnd; //+ ".root";
    files[names::ZPN40_PUUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4000_W-40_" + sigEnd; //+ ".root";
    files[names::ZPN45_PUUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4500_W-45_" + sigEnd; //+ ".root";
    files[names::ZPN50_PUUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-5000_W-50_" + sigEnd; //+ ".root";
    files[names::ZPN60_PUUP]         = files[names::ZPN50]; //ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6000_W-60_" + sigEnd + ".root";
    files[names::ZPN65_PUUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6500_W-65_" + sigEnd + ".root";
    files[names::ZPN70_PUUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-7000_W-70_" + sigEnd + ".root";

    files[names::ZPN10_PUDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1000_W-10_" + sigEnd; //+ ".root";
    files[names::ZPN12p5_PUDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1250_W-12p5_" + sigEnd; //+ ".root";
    files[names::ZPN15_PUDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1500_W-15_" + sigEnd + "_all"; //+ ".root";
    files[names::ZPN20_PUDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2000_W-20_" + sigEnd; //+ ".root";
    files[names::ZPN25_PUDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2500_W-25_" + sigEnd; //+ ".root";
    files[names::ZPN30_PUDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3000_W-30_" + sigEnd; //+ ".root";
    files[names::ZPN35_PUDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3500_W-35_" + sigEnd; //+ ".root";
    files[names::ZPN40_PUDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4000_W-40_" + sigEnd; //+ ".root";
    files[names::ZPN45_PUDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4500_W-45_" + sigEnd; //+ ".root";
    files[names::ZPN50_PUDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-5000_W-50_" + sigEnd; //+ ".root";
    files[names::ZPN60_PUDN]         = files[names::ZPN50]; //ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6000_W-60_" + sigEnd + ".root";
    files[names::ZPN65_PUDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6500_W-65_" + sigEnd + ".root";
    files[names::ZPN70_PUDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-7000_W-70_" + sigEnd + ".root";
  }//ZPN, signal = 0
  else if (signal == 1) {//ZPW                                                                                                                
    files[names::ZPN10] = infileBegin + systLabel + "_ZprimeToTT_M-1000_W-100_" + sigEnd; // + ".root";
    files[names::ZPN12p5] = infileBegin + systLabel + "_ZprimeToTT_M-1250_W-125_" + sigEnd; // + ".root";
    files[names::ZPN15] = infileBegin + systLabel + "_ZprimeToTT_M-1500_W-150_" + sigEnd; // + ".root";
    files[names::ZPN20] = infileBegin + systLabel + "_ZprimeToTT_M-2000_W-200_" + sigEnd; // + ".root";
    files[names::ZPN25] = infileBegin + systLabel + "_ZprimeToTT_M-2500_W-250_" + sigEnd; // + ".root";
    files[names::ZPN30] = infileBegin + systLabel + "_ZprimeToTT_M-3000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN35] = infileBegin + systLabel + "_ZprimeToTT_M-3500_W-350_" + sigEnd; // + ".root";
    files[names::ZPN40] = infileBegin + systLabel + "_ZprimeToTT_M-4000_W-400_" + sigEnd; // + ".root";
    files[names::ZPN45] = infileBegin + systLabel + "_ZprimeToTT_M-4500_W-450_" + sigEnd; // + ".root";
    files[names::ZPN50] = infileBegin + systLabel + "_ZprimeToTT_M-5000_W-500_" + sigEnd; // + ".root";
    files[names::ZPN60]         = ZP6plusFileBegin + systLabel + "_ZprimeToTT_M-6000_W-600_" + sigEnd + ".root";
    files[names::ZPN65]         = ZP6plusFileBegin + systLabel + "_ZprimeToTT_M-6500_W-650_" + sigEnd + ".root";
    files[names::ZPN70]         = ZP6plusFileBegin + systLabel + "_ZprimeToTT_M-7000_W-700_" + sigEnd + ".root";

    systLabel = "jec";
    files[names::ZPN10_SCALEUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1000_W-100_" + sigEnd; // + ".root";
    files[names::ZPN12p5_SCALEUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1250_W-125_" + sigEnd; // + ".root";
    files[names::ZPN15_SCALEUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1500_W-150_" + sigEnd; // + ".root";
    files[names::ZPN20_SCALEUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2000_W-200_" + sigEnd; // + ".root";
    files[names::ZPN25_SCALEUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2500_W-250_" + sigEnd; // + ".root";
    files[names::ZPN30_SCALEUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN35_SCALEUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3500_W-350_" + sigEnd; // + ".root";
    files[names::ZPN40_SCALEUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4000_W-400_" + sigEnd; // + ".root";
    files[names::ZPN45_SCALEUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4500_W-450_" + sigEnd; // + ".root";
    files[names::ZPN50_SCALEUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-5000_W-500_" + sigEnd; // + ".root";
    files[names::ZPN60_SCALEUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6000_W-600_" + sigEnd + ".root";
    files[names::ZPN65_SCALEUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6500_W-650_" + sigEnd + ".root";
    files[names::ZPN70_SCALEUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-7000_W-700_" + sigEnd + ".root";

    files[names::ZPN10_SCALEDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1000_W-100_" + sigEnd; // + ".root";
    files[names::ZPN12p5_SCALEDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1250_W-125_" + sigEnd; // + ".root";
    files[names::ZPN15_SCALEDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1500_W-150_" + sigEnd; // + ".root";
    files[names::ZPN20_SCALEDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2000_W-200_" + sigEnd; // + ".root";
    files[names::ZPN25_SCALEDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2500_W-250_" + sigEnd; // + ".root";
    files[names::ZPN30_SCALEDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN35_SCALEDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3500_W-350_" + sigEnd; // + ".root";
    files[names::ZPN40_SCALEDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4000_W-400_" + sigEnd; // + ".root";
    files[names::ZPN45_SCALEDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4500_W-450_" + sigEnd; // + ".root";
    files[names::ZPN50_SCALEDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-5000_W-500_" + sigEnd; // + ".root";
    files[names::ZPN60_SCALEDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6000_W-600_" + sigEnd + ".root";
    files[names::ZPN65_SCALEDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6500_W-650_" + sigEnd + ".root";
    files[names::ZPN70_SCALEDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-7000_W-700_" + sigEnd + ".root";

    systLabel = "jer";
    files[names::ZPN10_JERUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1000_W-100_" + sigEnd; // + ".root";
    files[names::ZPN12p5_JERUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1250_W-125_" + sigEnd; // + ".root";
    files[names::ZPN15_JERUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1500_W-150_" + sigEnd; // + ".root";
    files[names::ZPN20_JERUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2000_W-200_" + sigEnd; // + ".root";
    files[names::ZPN25_JERUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2500_W-250_" + sigEnd; // + ".root";
    files[names::ZPN30_JERUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN35_JERUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3500_W-350_" + sigEnd; // + ".root";
    files[names::ZPN40_JERUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4000_W-400_" + sigEnd; // + ".root";
    files[names::ZPN45_JERUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4500_W-450_" + sigEnd; // + ".root";
    files[names::ZPN50_JERUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-5000_W-500_" + sigEnd; // + ".root";
    files[names::ZPN60_JERUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6000_W-600_" + sigEnd + ".root";
    files[names::ZPN65_JERUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6500_W-650_" + sigEnd + ".root";
    files[names::ZPN70_JERUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-7000_W-700_" + sigEnd + ".root";

    files[names::ZPN10_JERDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1000_W-100_" + sigEnd; // + ".root";
    files[names::ZPN12p5_JERDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1250_W-125_" + sigEnd; // + ".root";
    files[names::ZPN15_JERDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1500_W-150_" + sigEnd; // + ".root";
    files[names::ZPN20_JERDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2000_W-200_" + sigEnd; // + ".root";
    files[names::ZPN25_JERDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2500_W-250_" + sigEnd; // + ".root";
    files[names::ZPN30_JERDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN35_JERDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3500_W-350_" + sigEnd; // + ".root";
    files[names::ZPN40_JERDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4000_W-400_" + sigEnd; // + ".root";
    files[names::ZPN45_JERDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4500_W-450_" + sigEnd; // + ".root";
    files[names::ZPN50_JERDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-5000_W-500_" + sigEnd; // + ".root";
    files[names::ZPN60_JERDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6000_W-600_" + sigEnd + ".root";
    files[names::ZPN65_JERDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6500_W-650_" + sigEnd + ".root";
    files[names::ZPN70_JERDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-7000_W-700_" + sigEnd + ".root";
    
    systLabel = "bTag";
    files[names::ZPN10_BTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1000_W-100_" + sigEnd; // + ".root";
    files[names::ZPN12p5_BTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1250_W-125_" + sigEnd; // + ".root";
    files[names::ZPN15_BTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1500_W-150_" + sigEnd; // + ".root";
    files[names::ZPN20_BTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2000_W-200_" + sigEnd; // + ".root";
    files[names::ZPN25_BTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2500_W-250_" + sigEnd; // + ".root";
    files[names::ZPN30_BTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN35_BTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3500_W-350_" + sigEnd; // + ".root";
    files[names::ZPN40_BTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4000_W-400_" + sigEnd; // + ".root";
    files[names::ZPN45_BTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4500_W-450_" + sigEnd; // + ".root";
    files[names::ZPN50_BTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-5000_W-500_" + sigEnd; // + ".root";
    files[names::ZPN60_BTAGUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6000_W-600_" + sigEnd + ".root";
    files[names::ZPN65_BTAGUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6500_W-650_" + sigEnd + ".root";
    files[names::ZPN70_BTAGUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-7000_W-700_" + sigEnd + ".root";

    files[names::ZPN10_BTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1000_W-100_" + sigEnd; // + ".root";
    files[names::ZPN12p5_BTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1250_W-125_" + sigEnd; // + ".root";
    files[names::ZPN15_BTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1500_W-150_" + sigEnd; // + ".root";
    files[names::ZPN20_BTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2000_W-200_" + sigEnd; // + ".root";
    files[names::ZPN25_BTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2500_W-250_" + sigEnd; // + ".root";
    files[names::ZPN30_BTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN35_BTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3500_W-350_" + sigEnd; // + ".root";
    files[names::ZPN40_BTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4000_W-400_" + sigEnd; // + ".root";
    files[names::ZPN45_BTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4500_W-450_" + sigEnd; // + ".root";
    files[names::ZPN50_BTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-5000_W-500_" + sigEnd; // + ".root";
    files[names::ZPN60_BTAGDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6000_W-600_" + sigEnd + ".root";
    files[names::ZPN65_BTAGDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6500_W-650_" + sigEnd + ".root";
    files[names::ZPN70_BTAGDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-7000_W-700_" + sigEnd + ".root";

    systLabel = "bMistag";
    files[names::ZPN10_BMISTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1000_W-100_" + sigEnd; // + ".root";
    files[names::ZPN12p5_BMISTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1250_W-125_" + sigEnd; // + ".root";
    files[names::ZPN15_BMISTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1500_W-150_" + sigEnd; // + ".root";
    files[names::ZPN20_BMISTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2000_W-200_" + sigEnd; // + ".root";
    files[names::ZPN25_BMISTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2500_W-250_" + sigEnd; // + ".root";
    files[names::ZPN30_BMISTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN35_BMISTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3500_W-350_" + sigEnd; // + ".root";
    files[names::ZPN40_BMISTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4000_W-400_" + sigEnd; // + ".root";
    files[names::ZPN45_BMISTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4500_W-450_" + sigEnd; // + ".root";
    files[names::ZPN50_BMISTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-5000_W-500_" + sigEnd; // + ".root";
    files[names::ZPN60_BMISTAGUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6000_W-600_" + sigEnd + ".root";
    files[names::ZPN65_BMISTAGUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6500_W-650_" + sigEnd + ".root";
    files[names::ZPN70_BMISTAGUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-7000_W-700_" + sigEnd + ".root";

    files[names::ZPN10_BMISTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1000_W-100_" + sigEnd; // + ".root";
    files[names::ZPN12p5_BMISTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1250_W-125_" + sigEnd; // + ".root";
    files[names::ZPN15_BMISTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1500_W-150_" + sigEnd; // + ".root";
    files[names::ZPN20_BMISTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2000_W-200_" + sigEnd; // + ".root";
    files[names::ZPN25_BMISTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2500_W-250_" + sigEnd; // + ".root";
    files[names::ZPN30_BMISTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN35_BMISTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3500_W-350_" + sigEnd; // + ".root";
    files[names::ZPN40_BMISTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4000_W-400_" + sigEnd; // + ".root";
    files[names::ZPN45_BMISTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4500_W-450_" + sigEnd; // + ".root";
    files[names::ZPN50_BMISTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-5000_W-500_" + sigEnd; // + ".root";
    files[names::ZPN60_BMISTAGDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6000_W-600_" + sigEnd + ".root";
    files[names::ZPN65_BMISTAGDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6500_W-650_" + sigEnd + ".root";
    files[names::ZPN70_BMISTAGDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-7000_W-700_" + sigEnd + ".root";

    systLabel = "pdf";
    files[names::ZPN10_PDFUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1000_W-100_" + sigEnd; // + ".root";
    files[names::ZPN12p5_PDFUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1250_W-125_" + sigEnd; // + ".root";
    files[names::ZPN15_PDFUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1500_W-150_" + sigEnd; // + ".root";
    files[names::ZPN20_PDFUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2000_W-200_" + sigEnd; // + ".root";
    files[names::ZPN25_PDFUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2500_W-250_" + sigEnd; // + ".root";
    files[names::ZPN30_PDFUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN35_PDFUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3500_W-350_" + sigEnd; // + ".root";
    files[names::ZPN40_PDFUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4000_W-400_" + sigEnd; // + ".root";
    files[names::ZPN45_PDFUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4500_W-450_" + sigEnd; // + ".root";
    files[names::ZPN50_PDFUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-5000_W-500_" + sigEnd; // + ".root";
    files[names::ZPN60_PDFUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6000_W-600_" + sigEnd + ".root";
    files[names::ZPN65_PDFUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6500_W-650_" + sigEnd + ".root";
    files[names::ZPN70_PDFUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-7000_W-700_" + sigEnd + ".root";

    files[names::ZPN10_PDFDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1000_W-100_" + sigEnd; // + ".root";
    files[names::ZPN12p5_PDFDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1250_W-125_" + sigEnd; // + ".root";
    files[names::ZPN15_PDFDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1500_W-150_" + sigEnd; // + ".root";
    files[names::ZPN20_PDFDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2000_W-200_" + sigEnd; // + ".root";
    files[names::ZPN25_PDFDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2500_W-250_" + sigEnd; // + ".root";
    files[names::ZPN30_PDFDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN35_PDFDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3500_W-350_" + sigEnd; // + ".root";
    files[names::ZPN40_PDFDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4000_W-400_" + sigEnd; // + ".root";
    files[names::ZPN45_PDFDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4500_W-450_" + sigEnd; // + ".root";
    files[names::ZPN50_PDFDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-5000_W-500_" + sigEnd; // + ".root";
    files[names::ZPN60_PDFDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6000_W-600_" + sigEnd + ".root";
    files[names::ZPN65_PDFDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6500_W-650_" + sigEnd + ".root";
    files[names::ZPN70_PDFDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-7000_W-700_" + sigEnd + ".root";
    
    systLabel = "PU";
    files[names::ZPN10_PUUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1000_W-100_" + sigEnd; // + ".root";
    files[names::ZPN12p5_PUUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1250_W-125_" + sigEnd; // + ".root";
    files[names::ZPN15_PUUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1500_W-150_" + sigEnd; // + ".root";
    files[names::ZPN20_PUUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2000_W-200_" + sigEnd; // + ".root";
    files[names::ZPN25_PUUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2500_W-250_" + sigEnd; // + ".root";
    files[names::ZPN30_PUUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN35_PUUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3500_W-350_" + sigEnd; // + ".root";
    files[names::ZPN40_PUUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4000_W-400_" + sigEnd; // + ".root";
    files[names::ZPN45_PUUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4500_W-450_" + sigEnd; // + ".root";
    files[names::ZPN50_PUUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-5000_W-500_" + sigEnd; // + ".root";
    files[names::ZPN60_PUUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6000_W-600_" + sigEnd + ".root";
    files[names::ZPN65_PUUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6500_W-650_" + sigEnd + ".root";
    files[names::ZPN70_PUUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-7000_W-700_" + sigEnd + ".root";

    files[names::ZPN10_PUDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1000_W-100_" + sigEnd; // + ".root";
    files[names::ZPN12p5_PUDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1250_W-125_" + sigEnd; // + ".root";
    files[names::ZPN15_PUDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1500_W-150_" + sigEnd; // + ".root";
    files[names::ZPN20_PUDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2000_W-200_" + sigEnd; // + ".root";
    files[names::ZPN25_PUDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2500_W-250_" + sigEnd; // + ".root";
    files[names::ZPN30_PUDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN35_PUDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3500_W-350_" + sigEnd; // + ".root";
    files[names::ZPN40_PUDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4000_W-400_" + sigEnd; // + ".root";
    files[names::ZPN45_PUDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4500_W-450_" + sigEnd; // + ".root";
    files[names::ZPN50_PUDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-5000_W-500_" + sigEnd; // + ".root";
    files[names::ZPN60_PUDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6000_W-600_" + sigEnd + ".root";
    files[names::ZPN65_PUDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6500_W-650_" + sigEnd + ".root";
    files[names::ZPN70_PUDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-7000_W-700_" + sigEnd + ".root";
  }//ZPW, signal = 1                                                                                                                         
  else if (signal == 2) {//ZPXW                                                                                                               
    files[names::ZPN10] = infileBegin + systLabel + "_ZprimeToTT_M-1000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN12p5] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-1500_W-450_" + sigEnd; // + ".root";            
    files[names::ZPN15] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-1500_W-450_" + sigEnd; // + ".root";              
    files[names::ZPN20] = infileBegin + systLabel + "_ZprimeToTT_M-2000_W-600_" + sigEnd; // + ".root";
    files[names::ZPN25] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-2500_W-750_" + sigEnd; // + ".root";              
    files[names::ZPN30] = infileBegin + systLabel + "_ZprimeToTT_M-3000_W-900_" + sigEnd; // + ".root";
    files[names::ZPN35] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-3500_W-1050_" + sigEnd; // + ".root";             
    files[names::ZPN40] = infileBegin + systLabel + "_ZprimeToTT_M-4000_W-1200_" + sigEnd; // + ".root";
    files[names::ZPN45] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-4500_W-1350_" + sigEnd; // + ".root";             
    files[names::ZPN50] = infileBegin + systLabel + "_ZprimeToTT_M-5000_W-1500_" + sigEnd + ".root";
    files[names::ZPN60]         = ZP6plusFileBegin + systLabel + "_ZprimeToTT_M-6000_W-1800_" + sigEnd + ".root";
    files[names::ZPN65]         = ZP6plusFileBegin + systLabel + "_ZprimeToTT_M-6500_W-1950_" + sigEnd + ".root";
    files[names::ZPN70]         = ZP6plusFileBegin + systLabel + "_ZprimeToTT_M-7000_W-2100_" + sigEnd + ".root";

    systLabel = "jec";
    files[names::ZPN10_SCALEUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN12p5_SCALEUP] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-1500_W-450_" + sigEnd; // + ".root";
    files[names::ZPN15_SCALEUP] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-1500_W-450_" + sigEnd; // + ".root";   
    files[names::ZPN20_SCALEUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2000_W-600_" + sigEnd; // + ".root";
    files[names::ZPN25_SCALEUP] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-2500_W-750_" + sigEnd; // + ".root";   
    files[names::ZPN30_SCALEUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3000_W-900_" + sigEnd; // + ".root";
    files[names::ZPN35_SCALEUP] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-3500_W-1050_" + sigEnd; // + ".root";  
    files[names::ZPN40_SCALEUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4000_W-1200_" + sigEnd; // + ".root";
    files[names::ZPN45_SCALEUP] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-4500_W-1350_" + sigEnd; // + ".root";  
    files[names::ZPN50_SCALEUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-5000_W-1500_" + sigEnd + ".root";
    files[names::ZPN60_SCALEUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6000_W-1800_" + sigEnd + ".root";
    files[names::ZPN65_SCALEUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6500_W-1950_" + sigEnd + ".root";
    files[names::ZPN70_SCALEUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-7000_W-2100_" + sigEnd + ".root";

    files[names::ZPN10_SCALEDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN12p5_SCALEDN] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-1500_W-450_" + sigEnd; // + ".root";
    files[names::ZPN15_SCALEDN] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-1500_W-450_" + sigEnd; // + ".root";   
    files[names::ZPN20_SCALEDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2000_W-600_" + sigEnd; // + ".root";
    files[names::ZPN25_SCALEDN] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-2500_W-750_" + sigEnd; // + ".root";   
    files[names::ZPN30_SCALEDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3000_W-900_" + sigEnd; // + ".root";
    files[names::ZPN35_SCALEDN] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-3500_W-1050_" + sigEnd; // + ".root";  
    files[names::ZPN40_SCALEDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4000_W-1200_" + sigEnd; // + ".root";
    files[names::ZPN45_SCALEDN] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-4500_W-1350_" + sigEnd; // + ".root";  
    files[names::ZPN50_SCALEDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-5000_W-1500_" + sigEnd + ".root";
    files[names::ZPN60_SCALEDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6000_W-1800_" + sigEnd + ".root";
    files[names::ZPN65_SCALEDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6500_W-1950_" + sigEnd + ".root";
    files[names::ZPN70_SCALEDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-7000_W-2100_" + sigEnd + ".root";

    systLabel = "jer";
    files[names::ZPN10_JERUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN12p5_JERUP] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-1500_W-450_" + sigEnd; // + ".root";   
    files[names::ZPN15_JERUP] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-1500_W-450_" + sigEnd; // + ".root";     
    files[names::ZPN20_JERUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2000_W-600_" + sigEnd; // + ".root";
    files[names::ZPN25_JERUP] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-2500_W-750_" + sigEnd; // + ".root";     
    files[names::ZPN30_JERUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3000_W-900_" + sigEnd; // + ".root";
    files[names::ZPN35_JERUP] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-3500_W-1050_" + sigEnd; // + ".root";    
    files[names::ZPN40_JERUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4000_W-1200_" + sigEnd; // + ".root";
    files[names::ZPN45_JERUP] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-4500_W-1350_" + sigEnd; // + ".root";    
    files[names::ZPN50_JERUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-5000_W-1500_" + sigEnd + ".root";
    files[names::ZPN60_JERUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6000_W-1800_" + sigEnd + ".root";
    files[names::ZPN65_JERUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6500_W-1950_" + sigEnd + ".root";
    files[names::ZPN70_JERUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-7000_W-2100_" + sigEnd + ".root";

    files[names::ZPN10_JERDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN12p5_JERDN] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-1500_W-450_" + sigEnd; // + ".root";   
    files[names::ZPN15_JERDN] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-1500_W-450_" + sigEnd; // + ".root";     
    files[names::ZPN20_JERDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2000_W-600_" + sigEnd; // + ".root";
    files[names::ZPN25_JERDN] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-2500_W-750_" + sigEnd; // + ".root";     
    files[names::ZPN30_JERDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3000_W-900_" + sigEnd; // + ".root";
    files[names::ZPN35_JERDN] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-3500_W-1050_" + sigEnd; // + ".root";    
    files[names::ZPN40_JERDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4000_W-1200_" + sigEnd; // + ".root";
    files[names::ZPN45_JERDN] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-4500_W-1350_" + sigEnd; // + ".root";    
    files[names::ZPN50_JERDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-5000_W-1500_" + sigEnd + ".root";
    files[names::ZPN60_JERDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6000_W-1800_" + sigEnd + ".root";
    files[names::ZPN65_JERDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6500_W-1950_" + sigEnd + ".root";
    files[names::ZPN70_JERDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-7000_W-2100_" + sigEnd + ".root";

    systLabel = "bTag";
    files[names::ZPN10_BTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN12p5_BTAGUP] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-1500_W-450_" + sigEnd; // + ".root";
    files[names::ZPN15_BTAGUP] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-1500_W-450_" + sigEnd; // + ".root";   
    files[names::ZPN20_BTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2000_W-600_" + sigEnd; // + ".root";
    files[names::ZPN25_BTAGUP] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-2500_W-750_" + sigEnd; // + ".root";   
    files[names::ZPN30_BTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3000_W-900_" + sigEnd; // + ".root";
    files[names::ZPN35_BTAGUP] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-3500_W-1050_" + sigEnd; // + ".root";  
    files[names::ZPN40_BTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4000_W-1200_" + sigEnd; // + ".root";
    files[names::ZPN45_BTAGUP] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-4500_W-1350_" + sigEnd; // + ".root";  
    files[names::ZPN50_BTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-5000_W-1500_" + sigEnd + ".root";
    files[names::ZPN60_BTAGUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6000_W-1800_" + sigEnd + ".root";
    files[names::ZPN65_BTAGUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6500_W-1950_" + sigEnd + ".root";
    files[names::ZPN70_BTAGUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-7000_W-2100_" + sigEnd + ".root";

    files[names::ZPN10_BTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN12p5_BTAGDN] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-1500_W-450_" + sigEnd; // + ".root";
    files[names::ZPN15_BTAGDN] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-1500_W-450_" + sigEnd; // + ".root";  
    files[names::ZPN20_BTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2000_W-600_" + sigEnd; // + ".root";
    files[names::ZPN25_BTAGDN] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-2500_W-750_" + sigEnd; // + ".root";  
    files[names::ZPN30_BTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3000_W-900_" + sigEnd; // + ".root";
    files[names::ZPN35_BTAGDN] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-3500_W-1050_" + sigEnd; // + ".root";  
    files[names::ZPN40_BTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4000_W-1200_" + sigEnd; // + ".root";
    files[names::ZPN45_BTAGDN] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-4500_W-1350_" + sigEnd; // + ".root";  
    files[names::ZPN50_BTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-5000_W-1500_" + sigEnd + ".root";
    files[names::ZPN60_BTAGDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6000_W-1800_" + sigEnd + ".root";
    files[names::ZPN65_BTAGDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6500_W-1950_" + sigEnd + ".root";
    files[names::ZPN70_BTAGDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-7000_W-2100_" + sigEnd + ".root";

    systLabel = "bMistag";
    files[names::ZPN10_BMISTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN12p5_BMISTAGUP] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-1500_W-450_" + sigEnd; // + ".root";
    files[names::ZPN15_BMISTAGUP] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-1500_W-450_" + sigEnd; // + ".root";   
    files[names::ZPN20_BMISTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2000_W-600_" + sigEnd; // + ".root";
    files[names::ZPN25_BMISTAGUP] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-2500_W-750_" + sigEnd; // + ".root";   
    files[names::ZPN30_BMISTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3000_W-900_" + sigEnd; // + ".root";
    files[names::ZPN35_BMISTAGUP] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-3500_W-1050_" + sigEnd; // + ".root";  
    files[names::ZPN40_BMISTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4000_W-1200_" + sigEnd; // + ".root";
    files[names::ZPN45_BMISTAGUP] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-4500_W-1350_" + sigEnd; // + ".root";  
    files[names::ZPN50_BMISTAGUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-5000_W-1500_" + sigEnd + ".root";
    files[names::ZPN60_BMISTAGUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6000_W-1800_" + sigEnd + ".root";
    files[names::ZPN65_BMISTAGUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6500_W-1950_" + sigEnd + ".root";
    files[names::ZPN70_BMISTAGUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-7000_W-2100_" + sigEnd + ".root";

    files[names::ZPN10_BMISTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN12p5_BMISTAGDN] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-1500_W-450_" + sigEnd; // + ".root";
    files[names::ZPN15_BMISTAGDN] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-1500_W-450_" + sigEnd; // + ".root";  
    files[names::ZPN20_BMISTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2000_W-600_" + sigEnd; // + ".root";
    files[names::ZPN25_BMISTAGDN] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-2500_W-750_" + sigEnd; // + ".root";  
    files[names::ZPN30_BMISTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3000_W-900_" + sigEnd; // + ".root";
    files[names::ZPN35_BMISTAGDN] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-3500_W-1050_" + sigEnd; // + ".root";  
    files[names::ZPN40_BMISTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4000_W-1200_" + sigEnd; // + ".root";
    files[names::ZPN45_BMISTAGDN] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-4500_W-1350_" + sigEnd; // + ".root";  
    files[names::ZPN50_BMISTAGDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-5000_W-1500_" + sigEnd + ".root";
    files[names::ZPN60_BMISTAGDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6000_W-1800_" + sigEnd + ".root";
    files[names::ZPN65_BMISTAGDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6500_W-1950_" + sigEnd + ".root";
    files[names::ZPN70_BMISTAGDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-7000_W-2100_" + sigEnd + ".root";

    systLabel = "pdf";
    files[names::ZPN10_PDFUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN12p5_PDFUP] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-1500_W-450_" + sigEnd; // + ".root"; 
    files[names::ZPN15_PDFUP] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-1500_W-450_" + sigEnd; // + ".root";   
    files[names::ZPN20_PDFUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2000_W-600_" + sigEnd; // + ".root";
    files[names::ZPN25_PDFUP] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-2500_W-750_" + sigEnd; // + ".root";   
    files[names::ZPN30_PDFUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3000_W-900_" + sigEnd; // + ".root";
    files[names::ZPN35_PDFUP] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-3500_W-1050_" + sigEnd; // + ".root";  
    files[names::ZPN40_PDFUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4000_W-1200_" + sigEnd; // + ".root";
    files[names::ZPN45_PDFUP] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-4500_W-1350_" + sigEnd; // + ".root";  
    files[names::ZPN50_PDFUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-5000_W-1500_" + sigEnd + ".root";
    files[names::ZPN60_PDFUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6000_W-1800_" + sigEnd + ".root";
    files[names::ZPN65_PDFUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6500_W-1950_" + sigEnd + ".root";
    files[names::ZPN70_PDFUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-7000_W-2100_" + sigEnd + ".root";

    files[names::ZPN10_PDFDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN12p5_PDFDN] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-1500_W-450_" + sigEnd; // + ".root"; 
    files[names::ZPN15_PDFDN] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-1500_W-450_" + sigEnd; // + ".root";    
    files[names::ZPN20_PDFDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2000_W-600_" + sigEnd; // + ".root";
    files[names::ZPN25_PDFDN] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-2500_W-750_" + sigEnd; // + ".root";    
    files[names::ZPN30_PDFDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3000_W-900_" + sigEnd; // + ".root";
    files[names::ZPN35_PDFDN] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-3500_W-1050_" + sigEnd + ".root"    
    files[names::ZPN40_PDFDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4000_W-1200_" + sigEnd; // + ".root";
    files[names::ZPN45_PDFDN] = files[names::ZPN10];//infileBegin + systLabel + "_ZprimeToTT_M-4500_W-1350_" + sigEnd + ".root"    
    files[names::ZPN50_PDFDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-5000_W-1500_" + sigEnd + ".root";
    files[names::ZPN60_PDFDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6000_W-1800_" + sigEnd + ".root";
    files[names::ZPN65_PDFDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6500_W-1950_" + sigEnd + ".root";
    files[names::ZPN70_PDFDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-7000_W-2100_" + sigEnd + ".root";
    
    systLabel = "PU";
    files[names::ZPN10_PUUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-1000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN12p5_PUUP]  = files[names::ZPN10];
    files[names::ZPN15_PUUP]  = files[names::ZPN10];
    files[names::ZPN20_PUUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-2000_W-600_" + sigEnd; // + ".root";
    files[names::ZPN25_PUUP]  = files[names::ZPN10];
    files[names::ZPN30_PUUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-3000_W-900_" + sigEnd; // + ".root";
    files[names::ZPN35_PUUP]  = files[names::ZPN10];
    files[names::ZPN40_PUUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-4000_W-1200_" + sigEnd; // + ".root";
    files[names::ZPN45_PUUP]  = files[names::ZPN10];
    files[names::ZPN50_PUUP] = infileBegin + systLabel + "_up_ZprimeToTT_M-5000_W-1500_" + sigEnd + ".root";
    files[names::ZPN60_PUUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6000_W-1800_" + sigEnd + ".root";
    files[names::ZPN65_PUUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-6500_W-1950_" + sigEnd + ".root";
    files[names::ZPN70_PUUP]         = ZP6plusFileBegin + systLabel + "_up_ZprimeToTT_M-7000_W-2100_" + sigEnd + ".root";

    files[names::ZPN10_PUDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-1000_W-300_" + sigEnd; // + ".root";
    files[names::ZPN12p5_PUDN]  = files[names::ZPN10];
    files[names::ZPN15_PUDN]  = files[names::ZPN10];
    files[names::ZPN20_PUDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-2000_W-600_" + sigEnd; // + ".root";
    files[names::ZPN25_PUDN]  = files[names::ZPN10];
    files[names::ZPN30_PUDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-3000_W-900_" + sigEnd; // + ".root";
    files[names::ZPN35_PUDN]  = files[names::ZPN10]; 
    files[names::ZPN40_PUDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-4000_W-1200_" + sigEnd; // + ".root";
    files[names::ZPN45_PUDN]  = files[names::ZPN10]; 
    files[names::ZPN50_PUDN] = infileBegin + systLabel + "_dn_ZprimeToTT_M-5000_W-1500_" + sigEnd + ".root";
    files[names::ZPN60_PUDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6000_W-1800_" + sigEnd + ".root";
    files[names::ZPN65_PUDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-6500_W-1950_" + sigEnd + ".root";
    files[names::ZPN70_PUDN]         = ZP6plusFileBegin + systLabel + "_dn_ZprimeToTT_M-7000_W-2100_" + sigEnd + ".root";
  }//ZPXW, signal = 2
  else if (signal == 3) {//RSG                                                                                                                
    files[names::ZPN10]         = infileBegin + systLabel + "_RSGluonToTT_M-1000_" + sigEnd; // + ".root";
    files[names::ZPN12p5]       = infileBegin + systLabel + "_RSGluonToTT_M-1250_" + sigEnd; // + ".root";
    files[names::ZPN15]         = infileBegin + systLabel + "_RSGluonToTT_M-1500_" + sigEnd; // + ".root";
    files[names::ZPN20]         = infileBegin + systLabel + "_RSGluonToTT_M-2000_" + sigEnd; // + ".root";
    files[names::ZPN25]         = infileBegin + systLabel + "_RSGluonToTT_M-2500_" + sigEnd; // + ".root";
    files[names::ZPN30]         = infileBegin + systLabel + "_RSGluonToTT_M-3000_" + sigEnd; // + ".root";
    files[names::ZPN35]         = infileBegin + systLabel + "_RSGluonToTT_M-3500_" + sigEnd; // + ".root";
    files[names::ZPN40]         = infileBegin + systLabel + "_RSGluonToTT_M-4000_" + sigEnd; // + ".root";
    files[names::ZPN45]         = infileBegin + systLabel + "_RSGluonToTT_M-4500_" + sigEnd; // + ".root";
    files[names::ZPN50]         = infileBegin + systLabel + "_RSGluonToTT_M-5000_" + sigEnd; // + ".root";
    files[names::ZPN60]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_RSGluonToTT_M-6000_" + sigEnd + ".root";
    files[names::ZPN65]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_RSGluonToTT_M-6500_" + sigEnd + ".root";
    files[names::ZPN70]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_RSGluonToTT_M-7000_" + sigEnd + ".root";


    systLabel = "jec";
    files[names::ZPN10_SCALEUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-1000_" + sigEnd; // + ".root";
    files[names::ZPN12p5_SCALEUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-1250_" + sigEnd; // + ".root";
    files[names::ZPN15_SCALEUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-1500_" + sigEnd; // + ".root";
    files[names::ZPN20_SCALEUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-2000_" + sigEnd; // + ".root";
    files[names::ZPN25_SCALEUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-2500_" + sigEnd; // + ".root";
    files[names::ZPN30_SCALEUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-3000_" + sigEnd; // + ".root";
    files[names::ZPN35_SCALEUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-3500_" + sigEnd; // + ".root";
    files[names::ZPN40_SCALEUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-4000_" + sigEnd; // + ".root";
    files[names::ZPN45_SCALEUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-4500_" + sigEnd; // + ".root";
    files[names::ZPN50_SCALEUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-5000_" + sigEnd; // + ".root";
    files[names::ZPN60_SCALEUP]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_up_RSGluonToTT_M-6000_" + sigEnd + ".root";
    files[names::ZPN65_SCALEUP]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_up_RSGluonToTT_M-6500_" + sigEnd + ".root";
    files[names::ZPN70_SCALEUP]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_up_RSGluonToTT_M-7000_" + sigEnd + ".root";

    files[names::ZPN10_SCALEDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-1000_" + sigEnd; // + ".root";
    files[names::ZPN12p5_SCALEDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-1250_" + sigEnd; // + ".root";
    files[names::ZPN15_SCALEDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-1500_" + sigEnd; // + ".root";
    files[names::ZPN20_SCALEDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-2000_" + sigEnd; // + ".root";
    files[names::ZPN25_SCALEDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-2500_" + sigEnd; // + ".root";
    files[names::ZPN30_SCALEDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-3000_" + sigEnd; // + ".root";
    files[names::ZPN35_SCALEDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-3500_" + sigEnd; // + ".root";
    files[names::ZPN40_SCALEDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-4000_" + sigEnd; // + ".root";
    files[names::ZPN45_SCALEDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-4500_" + sigEnd; // + ".root";
    files[names::ZPN50_SCALEDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-5000_" + sigEnd; // + ".root";
    files[names::ZPN60_SCALEDN]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_dn_RSGluonToTT_M-6000_" + sigEnd + ".root";
    files[names::ZPN65_SCALEDN]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_dn_RSGluonToTT_M-6500_" + sigEnd + ".root";
    files[names::ZPN70_SCALEDN]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_dn_RSGluonToTT_M-7000_" + sigEnd + ".root";

    systLabel = "jer";
    files[names::ZPN10_JERUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-1000_" + sigEnd; // + ".root";
    files[names::ZPN12p5_JERUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-1250_" + sigEnd; // + ".root";
    files[names::ZPN15_JERUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-1500_" + sigEnd; // + ".root";
    files[names::ZPN20_JERUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-2000_" + sigEnd; // + ".root";
    files[names::ZPN25_JERUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-2500_" + sigEnd; // + ".root";
    files[names::ZPN30_JERUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-3000_" + sigEnd; // + ".root";
    files[names::ZPN35_JERUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-3500_" + sigEnd; // + ".root";
    files[names::ZPN40_JERUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-4000_" + sigEnd; // + ".root";
    files[names::ZPN45_JERUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-4500_" + sigEnd; // + ".root";
    files[names::ZPN50_JERUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-5000_" + sigEnd; // + ".root";
    files[names::ZPN60_JERUP]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_up_RSGluonToTT_M-6000_" + sigEnd + ".root";
    files[names::ZPN65_JERUP]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_up_RSGluonToTT_M-6500_" + sigEnd + ".root";
    files[names::ZPN70_JERUP]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_up_RSGluonToTT_M-7000_" + sigEnd + ".root";

    files[names::ZPN10_JERDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-1000_" + sigEnd; // + ".root";
    files[names::ZPN12p5_JERDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-1250_" + sigEnd; // + ".root";
    files[names::ZPN15_JERDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-1500_" + sigEnd; // + ".root";
    files[names::ZPN20_JERDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-2000_" + sigEnd; // + ".root";
    files[names::ZPN25_JERDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-2500_" + sigEnd; // + ".root";
    files[names::ZPN30_JERDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-3000_" + sigEnd; // + ".root";
    files[names::ZPN35_JERDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-3500_" + sigEnd; // + ".root";
    files[names::ZPN40_JERDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-4000_" + sigEnd; // + ".root";
    files[names::ZPN45_JERDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-4500_" + sigEnd; // + ".root";
    files[names::ZPN50_JERDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-5000_" + sigEnd; // + ".root"
    files[names::ZPN60_JERDN]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_dn_RSGluonToTT_M-6000_" + sigEnd + ".root";
    files[names::ZPN65_JERDN]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_dn_RSGluonToTT_M-6500_" + sigEnd + ".root";
    files[names::ZPN70_JERDN]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_dn_RSGluonToTT_M-7000_" + sigEnd + ".root";

    systLabel = "pdf";
    files[names::ZPN10_PDFUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-1000_" + sigEnd; // + ".root";
    files[names::ZPN12p5_PDFUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-1250_" + sigEnd; // + ".root";
    files[names::ZPN15_PDFUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-1500_" + sigEnd; // + ".root";
    files[names::ZPN20_PDFUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-2000_" + sigEnd; // + ".root";
    files[names::ZPN25_PDFUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-2500_" + sigEnd; // + ".root";
    files[names::ZPN30_PDFUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-3000_" + sigEnd; // + ".root";
    files[names::ZPN35_PDFUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-3500_" + sigEnd; // + ".root";
    files[names::ZPN40_PDFUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-4000_" + sigEnd; // + ".root";
    files[names::ZPN45_PDFUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-4500_" + sigEnd; // + ".root";
    files[names::ZPN50_PDFUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-5000_" + sigEnd; // + ".root";
    files[names::ZPN60_PDFUP]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_up_RSGluonToTT_M-6000_" + sigEnd + ".root";
    files[names::ZPN65_PDFUP]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_up_RSGluonToTT_M-6500_" + sigEnd + ".root";
    files[names::ZPN70_PDFUP]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_up_RSGluonToTT_M-7000_" + sigEnd + ".root";

    files[names::ZPN10_PDFDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-1000_" + sigEnd; // + ".root";
    files[names::ZPN12p5_PDFDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-1250_" + sigEnd; // + ".root";
    files[names::ZPN15_PDFDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-1500_" + sigEnd; // + ".root";
    files[names::ZPN20_PDFDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-2000_" + sigEnd; // + ".root";
    files[names::ZPN25_PDFDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-2500_" + sigEnd; // + ".root";
    files[names::ZPN30_PDFDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-3000_" + sigEnd; // + ".root";
    files[names::ZPN35_PDFDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-3500_" + sigEnd; // + ".root";
    files[names::ZPN40_PDFDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-4000_" + sigEnd; // + ".root";
    files[names::ZPN45_PDFDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-4500_" + sigEnd; // + ".root";
    files[names::ZPN50_PDFDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-5000_" + sigEnd; // + ".root";
    files[names::ZPN60_PDFDN]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_dn_RSGluonToTT_M-6000_" + sigEnd + ".root";
    files[names::ZPN65_PDFDN]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_dn_RSGluonToTT_M-6500_" + sigEnd + ".root";
    files[names::ZPN70_PDFDN]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_dn_RSGluonToTT_M-7000_" + sigEnd + ".root";

    systLabel = "bTag";
    files[names::ZPN10_BTAGUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-1000_" + sigEnd; // + ".root";
    files[names::ZPN12p5_BTAGUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-1250_" + sigEnd; // + ".root";
    files[names::ZPN15_BTAGUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-1500_" + sigEnd; // + ".root";
    files[names::ZPN20_BTAGUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-2000_" + sigEnd; // + ".root";
    files[names::ZPN25_BTAGUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-2500_" + sigEnd; // + ".root";
    files[names::ZPN30_BTAGUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-3000_" + sigEnd; // + ".root";
    files[names::ZPN35_BTAGUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-3500_" + sigEnd; // + ".root";
    files[names::ZPN40_BTAGUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-4000_" + sigEnd; // + ".root";
    files[names::ZPN45_BTAGUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-4500_" + sigEnd; // + ".root";
    files[names::ZPN50_BTAGUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-5000_" + sigEnd; // + ".root";
    files[names::ZPN60_BTAGUP]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_up_RSGluonToTT_M-6000_" + sigEnd + ".root";
    files[names::ZPN65_BTAGUP]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_up_RSGluonToTT_M-6500_" + sigEnd + ".root";
    files[names::ZPN70_BTAGUP]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_up_RSGluonToTT_M-7000_" + sigEnd + ".root";

    files[names::ZPN10_BTAGDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-1000_" + sigEnd; // + ".root";
    files[names::ZPN12p5_BTAGDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-1250_" + sigEnd; // + ".root";
    files[names::ZPN15_BTAGDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-1500_" + sigEnd; // + ".root";
    files[names::ZPN20_BTAGDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-2000_" + sigEnd; // + ".root";
    files[names::ZPN25_BTAGDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-2500_" + sigEnd; // + ".root";
    files[names::ZPN30_BTAGDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-3000_" + sigEnd; // + ".root";
    files[names::ZPN35_BTAGDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-3500_" + sigEnd; // + ".root";
    files[names::ZPN40_BTAGDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-4000_" + sigEnd; // + ".root";
    files[names::ZPN45_BTAGDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-4500_" + sigEnd; // + ".root";
    files[names::ZPN50_BTAGDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-5000_" + sigEnd; // + ".root";
    files[names::ZPN60_BTAGDN]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_dn_RSGluonToTT_M-6000_" + sigEnd + ".root";
    files[names::ZPN65_BTAGDN]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_dn_RSGluonToTT_M-6500_" + sigEnd + ".root";
    files[names::ZPN70_BTAGDN]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_dn_RSGluonToTT_M-7000_" + sigEnd + ".root";
    
    systLabel = "bMistag";
    files[names::ZPN10_BMISTAGUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-1000_" + sigEnd; // + ".root";
    files[names::ZPN12p5_BMISTAGUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-1250_" + sigEnd; // + ".root";
    files[names::ZPN15_BMISTAGUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-1500_" + sigEnd; // + ".root";
    files[names::ZPN20_BMISTAGUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-2000_" + sigEnd; // + ".root";
    files[names::ZPN25_BMISTAGUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-2500_" + sigEnd; // + ".root";
    files[names::ZPN30_BMISTAGUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-3000_" + sigEnd; // + ".root";
    files[names::ZPN35_BMISTAGUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-3500_" + sigEnd; // + ".root";
    files[names::ZPN40_BMISTAGUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-4000_" + sigEnd; // + ".root";
    files[names::ZPN45_BMISTAGUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-4500_" + sigEnd; // + ".root";
    files[names::ZPN50_BMISTAGUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-5000_" + sigEnd; // + ".root";
    files[names::ZPN60_BMISTAGUP]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_up_RSGluonToTT_M-6000_" + sigEnd + ".root";
    files[names::ZPN65_BMISTAGUP]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_up_RSGluonToTT_M-6500_" + sigEnd + ".root";
    files[names::ZPN70_BMISTAGUP]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_up_RSGluonToTT_M-7000_" + sigEnd + ".root";

    files[names::ZPN10_BMISTAGDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-1000_" + sigEnd; // + ".root";
    files[names::ZPN12p5_BMISTAGDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-1250_" + sigEnd; // + ".root";
    files[names::ZPN15_BMISTAGDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-1500_" + sigEnd; // + ".root";
    files[names::ZPN20_BMISTAGDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-2000_" + sigEnd; // + ".root";
    files[names::ZPN25_BMISTAGDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-2500_" + sigEnd; // + ".root";
    files[names::ZPN30_BMISTAGDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-3000_" + sigEnd; // + ".root";
    files[names::ZPN35_BMISTAGDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-3500_" + sigEnd; // + ".root";
    files[names::ZPN40_BMISTAGDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-4000_" + sigEnd; // + ".root";
    files[names::ZPN45_BMISTAGDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-4500_" + sigEnd; // + ".root";
    files[names::ZPN50_BMISTAGDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-5000_" + sigEnd; // + ".root";
    files[names::ZPN60_BMISTAGDN]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_dn_RSGluonToTT_M-6000_" + sigEnd + ".root";
    files[names::ZPN65_BMISTAGDN]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_dn_RSGluonToTT_M-6500_" + sigEnd + ".root";
    files[names::ZPN70_BMISTAGDN]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_dn_RSGluonToTT_M-7000_" + sigEnd + ".root";
    
    systLabel = "PU";
    files[names::ZPN10_PUUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-1000_" + sigEnd; // + ".root";
    files[names::ZPN12p5_PUUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-1250_" + sigEnd; // + ".root";
    files[names::ZPN15_PUUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-1500_" + sigEnd; // + ".root";
    files[names::ZPN20_PUUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-2000_" + sigEnd; // + ".root";
    files[names::ZPN25_PUUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-2500_" + sigEnd; // + ".root";
    files[names::ZPN30_PUUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-3000_" + sigEnd; // + ".root";
    files[names::ZPN35_PUUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-3500_" + sigEnd; // + ".root";
    files[names::ZPN40_PUUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-4000_" + sigEnd; // + ".root";
    files[names::ZPN45_PUUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-4500_" + sigEnd; // + ".root";
    files[names::ZPN50_PUUP] = infileBegin + systLabel + "_up_RSGluonToTT_M-5000_" + sigEnd; // + ".root";
    files[names::ZPN60_PUUP]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_up_RSGluonToTT_M-6000_" + sigEnd + ".root";
    files[names::ZPN65_PUUP]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_up_RSGluonToTT_M-6500_" + sigEnd + ".root";
    files[names::ZPN70_PUUP]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_up_RSGluonToTT_M-7000_" + sigEnd + ".root";

    files[names::ZPN10_PUDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-1000_" + sigEnd; // + ".root";
    files[names::ZPN12p5_PUDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-1250_" + sigEnd; // + ".root";
    files[names::ZPN15_PUDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-1500_" + sigEnd; // + ".root";
    files[names::ZPN20_PUDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-2000_" + sigEnd; // + ".root";
    files[names::ZPN25_PUDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-2500_" + sigEnd; // + ".root";
    files[names::ZPN30_PUDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-3000_" + sigEnd; // + ".root";
    files[names::ZPN35_PUDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-3500_" + sigEnd; // + ".root";
    files[names::ZPN40_PUDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-4000_" + sigEnd; // + ".root";
    files[names::ZPN45_PUDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-4500_" + sigEnd; // + ".root";
    files[names::ZPN50_PUDN] = infileBegin + systLabel + "_dn_RSGluonToTT_M-5000_" + sigEnd; // + ".root";
    files[names::ZPN60_PUDN]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_dn_RSGluonToTT_M-6000_" + sigEnd + ".root";
    files[names::ZPN65_PUDN]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_dn_RSGluonToTT_M-6500_" + sigEnd + ".root";
    files[names::ZPN70_PUDN]         = files[names::ZPN10]; //ZP6plusFileBegin + systLabel + "_dn_RSGluonToTT_M-7000_" + sigEnd + ".root";
  }//RSG, signal = 3

  //int rebin_factor = 50;

  for (int proc = 0; proc < names::NUM_PROCS; proc++) {


    //cout << "Processing " << labels[proc] << endl;

    TFile *infile = new TFile(files[proc], "READ");

    //QCD from data, ttbar to subtract from it, and QCD MC "data estimate" for closure test systematic
    if ( (proc == names::QCD || proc == names::QCDMC_SYST || proc == names::TT_SUBTRACT) && ( foundDijetMass   !=std::string::npos ) ) {
      histos[proc][0] = (TH1F *) infile->Get("predDist_Puppi_SR_dRapLo_0btag_DijetMassMod_pred");
      histos[proc][1] = (TH1F *) infile->Get("predDist_Puppi_SR_dRapLo_1btag_DijetMassMod_pred");
      histos[proc][2] = (TH1F *) infile->Get("predDist_Puppi_SR_dRapLo_2btag_DijetMassMod_pred");
      histos[proc][3] = (TH1F *) infile->Get("predDist_Puppi_SR_dRapHi_0btag_DijetMassMod_pred");
      histos[proc][4] = (TH1F *) infile->Get("predDist_Puppi_SR_dRapHi_1btag_DijetMassMod_pred");
      histos[proc][5] = (TH1F *) infile->Get("predDist_Puppi_SR_dRapHi_2btag_DijetMassMod_pred");
      // histos[proc][6] = (TH1F *) infile->Get("predDist_Puppi_SR_dRapLo_0btag_DijetMassMod_pred");
    }

    //QCD and ttbar estimate w/o modmass
    else if ( proc == names::QCD_SYST || proc == names::TT_SUBTRACTSYST || ( (foundDijetMass   ==std::string::npos) && (proc == names::QCD || proc == names::TT_SUBTRACT) ) ) {
      histos[proc][0] = (TH1F *) infile->Get(Form("predDist_Puppi_SR_dRapLo_0btag_%s_pred",xVar.c_str()));
      histos[proc][1] = (TH1F *) infile->Get(Form("predDist_Puppi_SR_dRapLo_1btag_%s_pred",xVar.c_str()));
      histos[proc][2] = (TH1F *) infile->Get(Form("predDist_Puppi_SR_dRapLo_2btag_%s_pred",xVar.c_str()));
      histos[proc][3] = (TH1F *) infile->Get(Form("predDist_Puppi_SR_dRapHi_0btag_%s_pred",xVar.c_str()));
      histos[proc][4] = (TH1F *) infile->Get(Form("predDist_Puppi_SR_dRapHi_1btag_%s_pred",xVar.c_str()));
      histos[proc][5] = (TH1F *) infile->Get(Form("predDist_Puppi_SR_dRapHi_2btag_%s_pred",xVar.c_str()));
      //histos[proc][6] = (TH1F *) infile->Get(Form("predDist_Puppi_SR_dRapLo_0btag_%s_pred",xVar.c_str()));
    }
    
    //signal, ttbar, data, and QCD MC for closure test systematic
    else {
      histos[proc][0] = (TH1F *) infile->Get(Form("predDist_Puppi_SR_dRapLo_0btag_%s",xVar.c_str()));
      histos[proc][1] = (TH1F *) infile->Get(Form("predDist_Puppi_SR_dRapLo_1btag_%s",xVar.c_str()));
      histos[proc][2] = (TH1F *) infile->Get(Form("predDist_Puppi_SR_dRapLo_2btag_%s",xVar.c_str()));
      histos[proc][3] = (TH1F *) infile->Get(Form("predDist_Puppi_SR_dRapHi_0btag_%s",xVar.c_str()));
      histos[proc][4] = (TH1F *) infile->Get(Form("predDist_Puppi_SR_dRapHi_1btag_%s",xVar.c_str()));
      histos[proc][5] = (TH1F *) infile->Get(Form("predDist_Puppi_SR_dRapHi_2btag_%s",xVar.c_str()));
      //histos[proc][6] = (TH1F *) infile->Get(Form("predDist_Puppi_SR_dRapLo_0btag_%s",xVar.c_str()));
    }

    //cout << histos[proc][0]->Integral() << endl;
    //cout << histos[proc][0]->GetNbinsX() << endl;

    /*if (proc == names::QCDMC or proc == names::QCDMC_SYST){

      histos[proc][0]->Rebin(rebin_factor);
      histos[proc][1]->Rebin(rebin_factor);
      histos[proc][2]->Rebin(rebin_factor);
      histos[proc][3]->Rebin(rebin_factor);
      histos[proc][4]->Rebin(rebin_factor);
      histos[proc][5]->Rebin(rebin_factor);
      histos[proc][6]->Rebin(rebin_factor);
      }
      else{
    */
    histos[proc][0]->Rebin(rebin_factor);
    histos[proc][1]->Rebin(rebin_factor);
    histos[proc][2]->Rebin(rebin_factor);
    histos[proc][3]->Rebin(rebin_factor);
    histos[proc][4]->Rebin(rebin_factor);
    histos[proc][5]->Rebin(rebin_factor);
    //histos[proc][6]->Rebin(rebin_factor);

    //}
    //cout << histos[proc][0]->GetNbinsX() << endl;
  
  }

  for (int h = 0; h < names::NUM_PROCS; h++) {
    if (h == names::DATA) {
      histos[h][0]->Sumw2(kFALSE);
      histos[h][1]->Sumw2(kFALSE);
      histos[h][2]->Sumw2(kFALSE);
      histos[h][3]->Sumw2(kFALSE);
      histos[h][4]->Sumw2(kFALSE);
      histos[h][5]->Sumw2(kFALSE);
      //histos[h][6]->Sumw2(kFALSE);
    }
    else {
      histos[h][0]->Sumw2();
      histos[h][1]->Sumw2();
      histos[h][2]->Sumw2();
      histos[h][3]->Sumw2();
      histos[h][4]->Sumw2();
      histos[h][5]->Sumw2();
      //histos[h][6]->Sumw2();
    }

    //inclusive in b-tag and rapidity plots
    histos[h][6] = (TH1F *) histos[h][0]->Clone("hist_dRapIn_btagAll");
    for (int tag = 1; tag < (nTagCats - 1); tag++) {
      histos[h][6]->Add(histos[h][tag]);
    }
  }

  //data luminosity
  float lumi = 35922;
  
  //Number of sample events
  float nttbar = 77229341 + 78006311;

  //Z' narrow
  float N_Zp10 = 103785.;
  float N_Zp12 = 102833.;
  float N_Zp15 = 99690.;
  float N_Zp20 = 202556.;
  float N_Zp25 = 100288.;
  float N_Zp30 = 91004.;
  float N_Zp35 = 91004.;
  float N_Zp40 = 107914.; 
  float N_Zp45 = 100306.;
  float N_Zp50 = 112042.;
  float N_Zp60 = 93777.;
  float N_Zp65 = 99576.;
  float N_Zp70 = 96206.;
 
  //Z' wide
  if (signal == 1) {
    N_Zp10 = 101056.;
    N_Zp12 = 96845.;
    N_Zp15 = 111108.;
    N_Zp20 = 104119.;
    N_Zp25 = 96077.;
    N_Zp30 = 189164.;
    N_Zp35 = 101022.;
    N_Zp40 = 102411.;
    N_Zp45 = 84504.;
    N_Zp50 = 107156.;
    N_Zp60 = 96244.;
    N_Zp65 = 98990.;
    N_Zp70 = 98614.;
  }

  //Z' extra wide
  else if ( signal == 2) {
    N_Zp10 = 79477.;
    //N_Zp12 = .;
    //N_Zp15 = .;
    N_Zp20 = 114009.;
    //N_Zp25 = .;
    N_Zp30 = 89125.;
    //N_Zp35 = .;
    N_Zp40 = 88039.; 
    //N_Zp45 = .;
    N_Zp50 = 91038.;
    N_Zp60 = 82789.;
    N_Zp65 = 88454.;
    N_Zp70 = 94755.;
  }

  //RS Gluon
  else if ( signal == 3) {
    N_Zp10 = 98560.;
    N_Zp12 = 100000.;
    N_Zp15 = 100000.;
    N_Zp20 = 100000.;
    N_Zp25 = 100000.;
    N_Zp30 = 99755.;
    N_Zp35 = 99508.;
    N_Zp40 = 99136.; 
    N_Zp45 = 99597.;
    N_Zp50 = 98413.;
  }
  
  float kfactor = 1.0;
  /*float kfactor = 0.9;
  float kfactor_tt_pt_weight_syst = 0.7;
  if (!ttReweighting){ kfactor = 0.7; kfactor_tt_pt_weight_syst = 0.9;}*/

  float average_tt_pt_weight = 1.0;
  float average_tt_pt_weight_syst = 1.0;//for ttbar pt reweighting systematic
  //if (!ttReweighting) { average_tt_pt_weight = 1.0; average_tt_pt_weight_syst = 0.82;}

  //tt scale factors - https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetTopTagging#13_TeV_working_points_CMSSW_8_0
  //    Working point A  tau32 < 0.80    SF 1.07    +0.10 -0.04
  //    Working point B  tau32 < 0.65    SF 1.09    +0.13 -0.05
  //    Working point C  tau32 < 0.54    SF 1.09    +0.10 -0.05

  float ttSF     = 1.0;
  if (!forCombo){
    if ( foundWPA   !=std::string::npos ) ttSF = 1.07;
    if ( foundWPB   !=std::string::npos ) ttSF = 1.09;
    if ( foundWPC   !=std::string::npos ) ttSF = 1.09;
  }
  cout << dateLabel << " " << kfactor << " " << ttSF << " " << average_tt_pt_weight << endl;

  for (int tag = 0; tag < (nTagCats); tag++) { 
    //cout<<"start of loop"<<endl;
    histos[names::QCD][tag]->SetMarkerSize(0);
    histos[names::TT_SCALEUP][tag] ->Scale( 831.76 * ttSF * ttSF * lumi * kfactor / ( nttbar * average_tt_pt_weight ) );
    histos[names::TT_SCALEDN][tag] ->Scale( 831.76 * ttSF * ttSF * lumi * kfactor / ( nttbar * average_tt_pt_weight ) );
    histos[names::TT_JERUP][tag]   ->Scale( 831.76 * ttSF * ttSF * lumi * kfactor / ( nttbar * average_tt_pt_weight ) );
    histos[names::TT_JERDN][tag]   ->Scale( 831.76 * ttSF * ttSF * lumi * kfactor / ( nttbar * average_tt_pt_weight ) );
    histos[names::TT_PDFUP][tag]   ->Scale( 831.76 * ttSF * ttSF * lumi * kfactor / ( nttbar * average_tt_pt_weight ) );
    histos[names::TT_PDFDN][tag]   ->Scale( 831.76 * ttSF * ttSF * lumi * kfactor / ( nttbar * average_tt_pt_weight ) );
    histos[names::TT_Q2UP][tag]    ->Scale( 831.76 * ttSF * ttSF * lumi * kfactor / ( nttbar * average_tt_pt_weight ) );
    histos[names::TT_Q2DN][tag]    ->Scale( 831.76 * ttSF * ttSF * lumi * kfactor / ( nttbar * average_tt_pt_weight ) );
    histos[names::TT_BTAGUP][tag]  ->Scale( 831.76 * ttSF * ttSF * lumi * kfactor / ( nttbar * average_tt_pt_weight ) );
    histos[names::TT_BTAGDN][tag]  ->Scale( 831.76 * ttSF * ttSF * lumi * kfactor / ( nttbar * average_tt_pt_weight ) );
    histos[names::TT_BMISTAGUP][tag]  ->Scale( 831.76 * ttSF * ttSF * lumi * kfactor / ( nttbar * average_tt_pt_weight ) );
    histos[names::TT_BMISTAGDN][tag]  ->Scale( 831.76 * ttSF * ttSF * lumi * kfactor / ( nttbar * average_tt_pt_weight ) );
    histos[names::TT_PUUP][tag]  ->Scale( 831.76 * ttSF * ttSF * lumi * kfactor / ( nttbar * average_tt_pt_weight ) );
    histos[names::TT_PUDN][tag]  ->Scale( 831.76 * ttSF * ttSF * lumi * kfactor / ( nttbar * average_tt_pt_weight ) );
    histos[names::TT][tag]         ->Scale( 831.76 * ttSF * ttSF * lumi * kfactor / ( nttbar * average_tt_pt_weight ) );
    histos[names::TT_SUBTRACT][tag]->Scale( 831.76 * ttSF * ttSF * lumi * kfactor / ( nttbar * average_tt_pt_weight ) );
    histos[names::TT_SUBTRACTSYST][tag]->Scale( 831.76 * ttSF * ttSF * lumi * kfactor / ( nttbar * average_tt_pt_weight ) );
    histos[names::TT_WEIGHTSYST][tag]->Scale( 831.76 * ttSF * ttSF * lumi * kfactor / ( nttbar * average_tt_pt_weight_syst ) );

    histos[names::ZPN10][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp10 );
    histos[names::ZPN12p5][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp12 );
    histos[names::ZPN15][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp15 );
    histos[names::ZPN20][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp20 );
    histos[names::ZPN25][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp25 );
    histos[names::ZPN30][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp30 );
    histos[names::ZPN35][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp35 );
    histos[names::ZPN40][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp40 );
    histos[names::ZPN45][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp45 );
    histos[names::ZPN50][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp50 );
    histos[names::ZPN10_SCALEUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp10 );
    histos[names::ZPN12p5_SCALEUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp12 );
    histos[names::ZPN15_SCALEUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp15 );
    histos[names::ZPN20_SCALEUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp20 );
    histos[names::ZPN25_SCALEUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp25 );
    histos[names::ZPN30_SCALEUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp30 );
    histos[names::ZPN35_SCALEUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp35 );
    histos[names::ZPN40_SCALEUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp40 );
    histos[names::ZPN45_SCALEUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp45 );
    histos[names::ZPN50_SCALEUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp50 );
    histos[names::ZPN60_SCALEUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp60 );
    histos[names::ZPN65_SCALEUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp65 );
    histos[names::ZPN70_SCALEUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp70 );
    histos[names::ZPN10_SCALEDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp10 );
    histos[names::ZPN12p5_SCALEDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp12 );
    histos[names::ZPN15_SCALEDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp15 );
    histos[names::ZPN20_SCALEDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp20 );
    histos[names::ZPN25_SCALEDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp25 );
    histos[names::ZPN30_SCALEDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp30 );
    histos[names::ZPN35_SCALEDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp35 );
    histos[names::ZPN40_SCALEDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp40 );
    histos[names::ZPN45_SCALEDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp45 );
    histos[names::ZPN50_SCALEDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp50 );
    histos[names::ZPN60_SCALEDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp60 );
    histos[names::ZPN65_SCALEDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp65 );
    histos[names::ZPN70_SCALEDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp70 );
    histos[names::ZPN10_JERUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp10 );
    histos[names::ZPN12p5_JERUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp12 );
    histos[names::ZPN15_JERUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp15 );
    histos[names::ZPN20_JERUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp20 );
    histos[names::ZPN25_JERUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp25 );
    histos[names::ZPN30_JERUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp30 );
    histos[names::ZPN35_JERUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp35 );
    histos[names::ZPN40_JERUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp40 );
    histos[names::ZPN45_JERUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp45 );
    histos[names::ZPN50_JERUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp50 );
    histos[names::ZPN60_JERUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp60 );
    histos[names::ZPN65_JERUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp65 );
    histos[names::ZPN70_JERUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp70 );
    histos[names::ZPN10_JERDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp10 );
    histos[names::ZPN12p5_JERDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp12 );
    histos[names::ZPN15_JERDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp15 );
    histos[names::ZPN20_JERDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp20 );
    histos[names::ZPN25_JERDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp25 );
    histos[names::ZPN30_JERDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp30 );
    histos[names::ZPN35_JERDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp35 );
    histos[names::ZPN40_JERDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp40 );
    histos[names::ZPN45_JERDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp45 );
    histos[names::ZPN50_JERDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp50 );
    histos[names::ZPN60_JERDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp60 );
    histos[names::ZPN65_JERDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp65 );
    histos[names::ZPN70_JERDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp70 );
    histos[names::ZPN10_BTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp10 );
    histos[names::ZPN12p5_BTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp12 );
    histos[names::ZPN15_BTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp15 );
    histos[names::ZPN20_BTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp20 );
    histos[names::ZPN25_BTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp25 );
    histos[names::ZPN30_BTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp30 );
    histos[names::ZPN35_BTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp35 );
    histos[names::ZPN40_BTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp40 );
    histos[names::ZPN45_BTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp45 );
    histos[names::ZPN50_BTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp50 );
    histos[names::ZPN60_BTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp60 );
    histos[names::ZPN65_BTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp65 );
    histos[names::ZPN70_BTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp70 );
    histos[names::ZPN10_BTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp10 );
    histos[names::ZPN12p5_BTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp12 );
    histos[names::ZPN15_BTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp15 );
    histos[names::ZPN20_BTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp20 );
    histos[names::ZPN25_BTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp25 );
    histos[names::ZPN30_BTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp30 );
    histos[names::ZPN35_BTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp35 );
    histos[names::ZPN40_BTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp40 );
    histos[names::ZPN45_BTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp45 );
    histos[names::ZPN50_BTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp50 );
    histos[names::ZPN60_BTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp60 );
    histos[names::ZPN65_BTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp65 );
    histos[names::ZPN70_BTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp70 );
    histos[names::ZPN10_BMISTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp10 );
    histos[names::ZPN12p5_BMISTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp12 );
    histos[names::ZPN15_BMISTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp15 );
    histos[names::ZPN20_BMISTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp20 );
    histos[names::ZPN25_BMISTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp25 );
    histos[names::ZPN30_BMISTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp30 );
    histos[names::ZPN35_BMISTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp35 );
    histos[names::ZPN40_BMISTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp40 );
    histos[names::ZPN45_BMISTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp45 );
    histos[names::ZPN50_BMISTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp50 );
    histos[names::ZPN60_BMISTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp60 );
    histos[names::ZPN65_BMISTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp65 );
    histos[names::ZPN70_BMISTAGUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp70 );
    histos[names::ZPN10_BMISTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp10 );
    histos[names::ZPN12p5_BMISTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp12 );
    histos[names::ZPN15_BMISTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp15 );
    histos[names::ZPN20_BMISTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp20 );
    histos[names::ZPN25_BMISTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp25 );
    histos[names::ZPN30_BMISTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp30 );
    histos[names::ZPN35_BMISTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp35 );
    histos[names::ZPN40_BMISTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp40 );
    histos[names::ZPN45_BMISTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp45 );
    histos[names::ZPN50_BMISTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp50 );
    histos[names::ZPN60_BMISTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp60 );
    histos[names::ZPN65_BMISTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp65 );
    histos[names::ZPN70_BMISTAGDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp70 );
    histos[names::ZPN10_PDFUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp10 );
    histos[names::ZPN12p5_PDFUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp12 );
    histos[names::ZPN15_PDFUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp15 );
    histos[names::ZPN20_PDFUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp20 );
    histos[names::ZPN25_PDFUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp25 );
    histos[names::ZPN30_PDFUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp30 );
    histos[names::ZPN35_PDFUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp35 );
    histos[names::ZPN40_PDFUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp40 );
    histos[names::ZPN45_PDFUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp45 );
    histos[names::ZPN50_PDFUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp50 );
    histos[names::ZPN60_PDFUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp60 );
    histos[names::ZPN65_PDFUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp65 );
    histos[names::ZPN70_PDFUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp70 );
    histos[names::ZPN10_PDFDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp10 );
    histos[names::ZPN12p5_PDFDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp12 );
    histos[names::ZPN15_PDFDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp15 );
    histos[names::ZPN20_PDFDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp20 );
    histos[names::ZPN25_PDFDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp25 );
    histos[names::ZPN30_PDFDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp30 );
    histos[names::ZPN35_PDFDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp35 );
    histos[names::ZPN40_PDFDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp40 );
    histos[names::ZPN45_PDFDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp45 );
    histos[names::ZPN50_PDFDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp50 );
    histos[names::ZPN60_PDFDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp60 );
    histos[names::ZPN65_PDFDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp65 );
    histos[names::ZPN70_PDFDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp70 );
    histos[names::ZPN10_PUUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp10 );
    histos[names::ZPN12p5_PUUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp12 );
    histos[names::ZPN15_PUUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp15 );
    histos[names::ZPN20_PUUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp20 );
    histos[names::ZPN25_PUUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp25 );
    histos[names::ZPN30_PUUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp30 );
    histos[names::ZPN35_PUUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp35 );
    histos[names::ZPN40_PUUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp40 );
    histos[names::ZPN45_PUUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp45 );
    histos[names::ZPN50_PUUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp50 );
    histos[names::ZPN60_PUUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp60 );
    histos[names::ZPN65_PUUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp65 );
    histos[names::ZPN70_PUUP][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp70 );
    histos[names::ZPN10_PUDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp10 );
    histos[names::ZPN12p5_PUDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp12 );
    histos[names::ZPN15_PUDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp15 );
    histos[names::ZPN20_PUDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp20 );
    histos[names::ZPN25_PUDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp25 );
    histos[names::ZPN30_PUDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp30 );
    histos[names::ZPN35_PUDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp35 );
    histos[names::ZPN40_PUDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp40 );
    histos[names::ZPN45_PUDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp45 );
    histos[names::ZPN50_PUDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp50 );
    histos[names::ZPN60_PUDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp60 );
    histos[names::ZPN65_PUDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp65 );
    histos[names::ZPN70_PUDN][tag]->Scale( 1. * ttSF * ttSF * lumi / N_Zp70 );

    //cout<<"end of loop"<<endl;
  } 

  int nTagCatsToWrite = nTagCats;
  if ( foundDijetMass   !=std::string::npos ) nTagCatsToWrite = nTagCats - 1;

  for (int tag = 0; tag < nTagCatsToWrite; tag++) {
    cout << "TAG CATEGORY " << tag << endl;

    float qcdInt = histos[names::QCD][tag]->Integral();
    float ttsubInt = histos[names::TT_SUBTRACT][tag]->Integral();
    float ttsub_percent = ttsubInt/qcdInt*100;

    cout << "QCD: " << qcdInt << " events, TTBAR CONTAMINATION: " << ttsubInt << " events (" << ttsub_percent << "\% )" << endl;

    //ttbar subtraction
    histos[names::QCD][tag]->Add(histos[names::TT_SUBTRACT][tag],-1);
    histos[names::QCD_SYST][tag]->Add(histos[names::TT_SUBTRACTSYST][tag],-1);

    //rebinning in bins of 30% background error
    if (forTHETA) {

      TH1F *h_background = (TH1F *) histos[names::QCD][tag]->Clone("h_background");    
      h_background->Add(histos[names::TT][tag]);

      int nBinsOriginal = h_background->GetNbinsX();
      int nBinsNew = 1.;
      float lastBinLowEdge =  7000.;
      float totalBinContent = 0.0;
      float totalStatErr = 0.0;

      //calculating the number of new bins; x_min = 900
      for (int i_bin = 0; i_bin < (nBinsOriginal-9); i_bin++){
	int j_bin = nBinsOriginal - i_bin;
	float statErr = h_background->GetBinError(j_bin);
	//cout << "StatErr: " << statErr << endl;
	float binContent = h_background->GetBinContent(j_bin);
	//float binEntries = h_background->GetBinEntries(j_bin);
	//cout << "non sumw2 Error: " << sqrt(binContent) <<endl;
	//cout <<"sumw2 Error: " << sqrt(binEntries)<<endl;
	totalStatErr = sqrt(totalStatErr*totalStatErr + statErr*statErr);

	totalBinContent = totalBinContent + h_background->GetBinContent(j_bin);
	float binErrFrac = 100.0;
	if (totalBinContent != 0) binErrFrac = abs(totalStatErr/totalBinContent);
	//cout << "Bin " << j_bin << ": Cumulative Content = " << totalBinContent << ", Cumulative Error = " << totalStatErr << ", Percent Error = " << binErrFrac << endl;
	
        if (binErrFrac <= 0.3){ // or (lastBinLowEdge - h_background->GetBinLowEdge(j_bin) >= 2500.)){
	  //cout << "******* New Bin From " << lastBinLowEdge << " to " << h_background->GetBinLowEdge(j_bin) << endl;
          totalStatErr = 0.0;
	  totalBinContent = 0.0;
	  lastBinLowEdge = h_background->GetBinLowEdge(j_bin);
          nBinsNew++;
        }
      }

      cout << "New Bin Count: " << nBinsNew << endl;

      //setting the bin array; x_min = 900
      Double_t xbins[nBinsNew+1];
      xbins[0]=800.0;
      xbins[nBinsNew]=7000.;
      lastBinLowEdge = 7000.;
      totalBinContent = 0.0;
      totalStatErr = 0.0;
      int binCount = 0;
      for (int i_bin = 0; i_bin < (nBinsOriginal-9); i_bin++){
	int j_bin = nBinsOriginal - i_bin;
	float statErr = h_background->GetBinError(j_bin);
	totalStatErr = sqrt(totalStatErr*totalStatErr + statErr*statErr);

	totalBinContent = totalBinContent + h_background->GetBinContent(j_bin);
	float binErrFrac = 100.0;
	if (totalBinContent != 0) binErrFrac = abs(totalStatErr/totalBinContent);
	//cout << "Bin " << j_bin << ": Cumulative Content = " << totalBinContent << ", Cumulative Error = " << totalStatErr << ", Percent Error = " << binErrFrac << endl;

        if (binErrFrac <= 0.3){ // or (lastBinLowEdge - h_background->GetBinLowEdge(j_bin) >= 2500.)){
          totalStatErr = 0.0;
	  totalBinContent = 0.0;
	  binCount++;
          lastBinLowEdge = h_background->GetBinLowEdge(j_bin);
	  xbins[nBinsNew-binCount] = lastBinLowEdge;
	  //cout << "Bin "<< nBinsNew-binCount<< " Low Edge: " << h_background->GetBinLowEdge(j_bin) << endl;
        }//end new bin if
      }//end bin for loop
      
      for (int proc = 0; proc < names::NUM_PROCS; proc++){
	if (proc != names::TT_SUBTRACT && proc != names::TT_SUBTRACTSYST && proc != names::QCDMC && proc != names::QCDMC_SYST){
	  //cout << "Processing " << labels[proc] << endl;
	  histos[proc][tag] = (TH1F *) histos[proc][tag]->Rebin(nBinsNew, "h", xbins);
	  //cout << histos[proc][tag]->GetNbinsX() << endl;
	  
	  //blinding procedure
	  if (blinding == 1 || blinding == 2){
	    bool firstblindedbin = 1;
	    float binLo = -1.0;
	    for (int i_bin=0; i_bin <= histos[proc][tag]->GetNbinsX(); i_bin++){
	      binLo = histos[proc][tag]->GetBinLowEdge(i_bin);
	      if (blinding == 1 && binLo >= 2000.){//blinding data below 2 TeV
		histos[proc][tag]->SetBinContent(i_bin,0.0);
		histos[proc][tag]->SetBinError(i_bin,0.0);
		if (firstblindedbin){
		  cout << "The first blinded bin is bin " << i_bin << ", with a low edge of " << binLo << endl;
		  firstblindedbin = 0;
		}//end first blinded bin if
	      }//end blinding below 2 TeV if
	      if (blinding == 2 && proc == names::DATA){//fully blinding data
		histos[proc][tag]->SetBinContent(i_bin,0.0);
		histos[proc][tag]->SetBinError(i_bin,0.0);
	      }//end full blinding if
	    }//end blinding for loop 
	  }//end blinding below 2 TeV if
	}//end QCD MC syst if
      }//end rebin for loop
    }//end for theta loop

    //Mtt plots
    histos[names::TT][tag]->SetFillColor(kRed);
    histos[names::QCD][tag]->SetFillColor(kYellow);

    TCanvas *c1 = new TCanvas("c1", "c1",0,0,600,500);
    c1->Range(0,0,1,1);
    c1->Draw();

    TPad *c1_1 = new TPad("c1_1", "newpad",0.01,0.01,0.99,0.25);
    c1_1->Draw();
    TPad *c1_2 = new TPad("c1_2", "newpad",0.01,0.25,0.99,0.99);
    c1_2->Draw();

    c1->cd();
    c1_2->cd();
    c1_2->SetTopMargin(0.1);
    c1_2->SetBottomMargin(0.1);
    c1_2->SetRightMargin(0.05);
    c1_2->SetLeftMargin(0.1);
    c1_2->SetFillStyle(0);

    if (blinding != 2){
      if (tag == 2 or tag == 5) histos[names::DATA][tag]->SetMaximum(3.0 * histos[names::DATA][tag]->GetMaximum() );
      else histos[names::DATA][tag]->SetMaximum(2.0 * histos[names::DATA][tag]->GetMaximum() );
    }

    //histos[names::DATA][tag]->SetMaximum(10.0 * histos[names::DATA][tag]->GetMaximum() );
    histos[names::DATA][tag]->GetYaxis()->SetTitle("Events");
    histos[names::DATA][tag]->GetYaxis()->SetTitleSize(0.042);
    //histos[names::DATA][tag]->GetYaxis()->SetTitleSize(1.2);                                                                               
    histos[names::DATA][tag]->GetYaxis()->SetTitleOffset(0.95);
    if (!forTHETA){
      if (tag == 2 or tag == 5) histos[names::DATA][tag]->GetXaxis()->SetRangeUser(600.,4600.);
      else histos[names::DATA][tag]->GetXaxis()->SetRangeUser(600.,6000.);
    }
    histos[names::DATA][tag]->SetBinErrorOption(TH1::kPoisson);
    histos[names::DATA][tag]->Draw("E");
    
    int n_xbins = histos[names::DATA][tag]->GetNbinsX();
    
    /*if (topTagSFset == 1 && tWP=="A") ttSF +=0.10;
    if (topTagSFset == 1 && tWP=="B") ttSF +=0.13;
    if (topTagSFset == 1 && tWP=="C") ttSF +=0.10;
    if (topTagSFset ==-1 && tWP=="A") ttSF -=0.04;
    if (topTagSFset ==-1 && tWP=="B") ttSF -=0.05;
    if (topTagSFset ==-1 && tWP=="C") ttSF -=0.05;*/

    //errors and post-fit scaling
    float totalTopErr = 0.0;
    float totalQCDErr = 0.0;
    float totalHistErr = 0.0;
    
    float ttSF_up     = 0.0;
    float ttSF_dn     = 0.0;
    
    if (!forCombo){
      if ( foundWPA   !=std::string::npos ){ ttSF_up = 0.10; ttSF_dn = 0.04;} //    Working point A  tau32 < 0.80    SF 1.07    +0.10 -0.04
      if ( foundWPB   !=std::string::npos ){ ttSF_up = 0.13; ttSF_dn = 0.05;} //    Working point B  tau32 < 0.65    SF 1.09    +0.13 -0.05
      if ( foundWPC   !=std::string::npos ){ ttSF_up = 0.10; ttSF_dn = 0.05;} //    Working point C  tau32 < 0.54    SF 1.09    +0.10 -0.05
    }

    float lumiErr_top = 0.025;
    float xsErr_top = 0.08;
    float topTagErr_top_up = abs(2*(((ttSF + ttSF_up)/ttSF) - 1));
    float topTagErr_top_dn = abs(2*(((ttSF - ttSF_dn)/ttSF) - 1));
    if (postFit){
      xsErr_top = 0.08;
      //topTagErr_top = 0.50;
    }


    TH1F *totalHallerr = (TH1F *) histos[names::QCD][tag]->Clone("totalHallerr");
    totalHallerr->Add(histos[names::TT][tag]);

    for (int i_bin = 1; i_bin < (n_xbins+1); i_bin++) {
      float QCDbinContent = histos[names::QCD][tag]->GetBinContent(i_bin);
      float TTbinContent = histos[names::TT][tag]->GetBinContent(i_bin);
      float statErr_QCD = histos[names::QCD][tag]->GetBinError(i_bin);
      float statErr_top = histos[names::TT][tag]->GetBinError(i_bin);
      float statErr = sqrt(statErr_QCD*statErr_QCD + statErr_top*statErr_top);
      float scaleErrUp = abs(TTbinContent - histos[names::TT_SCALEUP][tag]->GetBinContent(i_bin));
      float scaleErrDn = abs(TTbinContent - histos[names::TT_SCALEDN][tag]->GetBinContent(i_bin));
      float scaleErr = max(scaleErrUp,scaleErrDn);
      float jerErrUp = abs(TTbinContent - histos[names::TT_JERUP][tag]->GetBinContent(i_bin));
      float jerErrDn = abs(TTbinContent - histos[names::TT_JERDN][tag]->GetBinContent(i_bin));
      float jerErr = max(jerErrUp,jerErrDn);
      float pdfErrUp = abs(TTbinContent - histos[names::TT_PDFUP][tag]->GetBinContent(i_bin));
      float pdfErrDn = abs(TTbinContent - histos[names::TT_PDFDN][tag]->GetBinContent(i_bin));
      float pdfErr = max(pdfErrUp,pdfErrDn);
      float q2ErrUp = abs(TTbinContent - histos[names::TT_Q2UP][tag]->GetBinContent(i_bin));
      float q2ErrDn = abs(TTbinContent - histos[names::TT_Q2DN][tag]->GetBinContent(i_bin));
      float q2Err = max(q2ErrUp,q2ErrDn);
      float btagErrUp = abs(TTbinContent - histos[names::TT_BTAGUP][tag]->GetBinContent(i_bin));
      float btagErrDn = abs(TTbinContent - histos[names::TT_BTAGDN][tag]->GetBinContent(i_bin));
      float btagErr = max(btagErrUp,btagErrDn);
      float bmistagErrUp = abs(TTbinContent - histos[names::TT_BMISTAGUP][tag]->GetBinContent(i_bin));
      float bmistagErrDn = abs(TTbinContent - histos[names::TT_BMISTAGDN][tag]->GetBinContent(i_bin));
      float bmistagErr = max(bmistagErrUp,bmistagErrDn);
      float PUErrUp = abs(TTbinContent - histos[names::TT_PUUP][tag]->GetBinContent(i_bin));
      float PUErrDn = abs(TTbinContent - histos[names::TT_PUDN][tag]->GetBinContent(i_bin));
      float PUErr = max(PUErrUp,PUErrDn);
      float TTweightErr = abs(TTbinContent - histos[names::TT_WEIGHTSYST][tag]->GetBinContent(i_bin));
      float qcdSystErr = 0.5*abs( QCDbinContent - histos[names::QCD_SYST][tag]->GetBinContent(i_bin) );
      float xsErr = xsErr_top*(TTbinContent);
      float lumiErr = lumiErr_top*(TTbinContent);
      float topTagErrUp = topTagErr_top_up*(TTbinContent);
      float topTagErrDn = topTagErr_top_dn*(TTbinContent);
      float topTagErr = max(topTagErrUp,topTagErrDn);

      float diffClose = 0.0;
      float QCDcenter = histos[names::QCD][tag]->GetBinCenter(i_bin);
      int j_bin = histos[names::QCDMC][tag]->GetXaxis()->FindBin(QCDcenter);
      if (histos[names::QCDMC][tag]->GetBinContent(j_bin) != 0){
	diffClose = abs( histos[names::QCDMC][tag]->GetBinContent(j_bin) - histos[names::QCDMC_SYST][tag]->GetBinContent(j_bin) )/(histos[names::QCDMC][tag]->GetBinContent(j_bin));
      }
      float closeErr = diffClose*(QCDbinContent);

      //adjusting the background bin contents and errors with the postfit nuisance parameters - from https://indico.cern.ch/event/557452/contributions/2246868/attachments/1311279/1962238/update_july18.pdf
      /*if (postFit){
	float QCDpostFitBinContent = QCDbinContent + (qcdSystErr*-1.13659365675) + (closeErr*-0.220031592593);
	histos[names::QCD][tag]->SetBinContent(i_bin, QCDpostFitBinContent);
	float TTpostFitBinContent = TTbinContent + (scaleErr*0.439112914571) + (jerErr*-0.0895863766889) + (pdfErr*-0.134026920264) + (q2Err*-0.217576290897) + (btagErr*0.0675294259315) + (xsErr*-0.378266575878) + (lumiErr*0.78020704204) + (topTagErr*-0.0166162168857) + (PUErr*0.307540317129);
	histos[names::TT][tag]->SetBinContent(i_bin, TTpostFitBinContent);

	scaleErr *= 0.2417384116;
	jerErr *= 0.298777526289;
	pdfErr *= 0.419586463033;
	q2Err *= 0.184708538631;
	btagErr *= 0.321500972597;
	qcdSystErr *=0.478811424822;
	xsErr *= 0.77424517359;
	lumiErr *= 0.943095783913;
	topTagErr *= 0.264334867765;
	closeErr *= 0.232111904652;
	PUErr *= 0.498250450121;

	float QCDbinErr = sqrt(statErr_QCD*statErr_QCD + qcdSystErr*qcdSystErr); //+ closeErr*closeErr);
	histos[names::QCD][tag]->SetBinError(i_bin, QCDbinErr);
	float TTbinErr = sqrt(statErr_top*statErr_top + scaleErr*scaleErr + jerErr*jerErr + pdfErr*pdfErr + q2Err*q2Err + btagErr*btagErr + xsErr*xsErr + lumiErr*lumiErr + topTagErr*topTagErr + PUErr+PUErr);
	histos[names::TT][tag]->SetBinError(i_bin, TTbinErr);
      }*/

      float TOTALErr = sqrt(statErr*statErr + scaleErr*scaleErr + jerErr*jerErr + pdfErr*pdfErr + q2Err*q2Err + btagErr*btagErr + bmistagErr*bmistagErr + qcdSystErr*qcdSystErr + xsErr*xsErr + lumiErr*lumiErr + PUErr*PUErr + TTweightErr*TTweightErr + topTagErr*topTagErr + closeErr*closeErr);

      totalHallerr->SetBinError(i_bin,TOTALErr);

      totalQCDErr = sqrt(statErr_QCD*statErr_QCD + qcdSystErr*qcdSystErr + totalQCDErr*totalQCDErr + closeErr*closeErr); 
      totalTopErr = sqrt(statErr_top*statErr_top + scaleErr*scaleErr + jerErr*jerErr + pdfErr*pdfErr + q2Err*q2Err + btagErr*btagErr + bmistagErr*bmistagErr + xsErr*xsErr + lumiErr*lumiErr + PUErr*PUErr + totalTopErr*totalTopErr + TTweightErr*TTweightErr + topTagErr*topTagErr);
      totalHistErr = sqrt(TOTALErr*TOTALErr + totalHistErr*totalHistErr);
      //cout << "Bin " << i_bin << ": Content = " << totalH->GetBinContent(i_bin) << ", Error = " << TOTALErr << ", Percent Error = " << TOTALErr/(totalH->GetBinContent(i_bin)) << endl;
    }

    cout << "Region " << tag << " Total QCD: " << histos[names::QCD][tag]->Integral() << " +/- " << totalQCDErr <<endl;
    cout << "Region " << tag << " Total ttbar: " << histos[names::TT][tag]->Integral() << " +/- " << totalTopErr <<endl;

    TTerr[tag] = totalTopErr;
    QCDerr[tag] = totalQCDErr;
    BKGerr[tag] = totalHistErr;

    THStack *stack = new THStack();
    stack->Add(histos[names::TT][tag]);
    stack->Add(histos[names::QCD][tag]);

    
    stack->Draw("hist same");

    if (blinding == 2){
      if (tag == 2 or tag == 5) histos[names::DATA][tag]->SetMaximum(3.0 * stack->GetMaximum() );
      else histos[names::DATA][tag]->SetMaximum(2.0 * stack->GetMaximum() );
    }


    histos[names::DATA][tag]->SetMarkerStyle(20);
    histos[names::DATA][tag]->SetMarkerSize(0.5);
    histos[names::DATA][tag]->SetLineColor(kBlack);
    histos[names::DATA][tag]->SetTitle("");

    TH1F *totalH = (TH1F *) histos[names::QCD][tag]->Clone("totalH");
    totalH->Add(histos[names::TT][tag]);
    totalH->SetFillStyle(3001);
    totalH->SetFillColor(kGray+1);

    totalHallerr->SetFillStyle(3001);
    totalHallerr->SetFillColor(kGray+2);
    totalHallerr->Draw("E2 same");
    totalH->Draw("E2 same");

    //totalH->Draw("E2");
    if (tag == 2 or tag == 5) histos[names::DATA][tag]->SetMaximum(3.0 * totalH->GetMaximum() );
    else histos[names::DATA][tag]->SetMaximum(2.0 * totalH->GetMaximum() );
    //without data
    stack->Draw("histsame");
    totalHallerr->Draw("E2 same");
    totalH->Draw("E2 same"); 
    
    histos[names::DATA][tag]->Draw("E same");

    histos[names::ZPN10][tag]->SetLineColor(kBlue);
    histos[names::ZPN20][tag]->SetLineColor(kGreen+1);
    histos[names::ZPN30][tag]->SetLineColor(kViolet);
    histos[names::ZPN40][tag]->SetLineColor(7);
    histos[names::ZPN10][tag]->SetLineWidth(2);
    histos[names::ZPN20][tag]->SetLineWidth(2);
    histos[names::ZPN30][tag]->SetLineWidth(2);
    histos[names::ZPN40][tag]->SetLineWidth(2);

    histos[names::ZPN10][tag]->Draw("hist same");
    histos[names::ZPN20][tag]->Draw("hist same");
    histos[names::ZPN30][tag]->Draw("hist same");
    histos[names::ZPN40][tag]->Draw("hist same");

    TLatex *categoryLabel = new TLatex();
    categoryLabel->SetNDC();
    categoryLabel->SetTextFont(62);

    if (tag == 0) categoryLabel->DrawLatex(0.7, 0.85, "0 b-tags, |#Deltay| < 1.0");
    if (tag == 1) categoryLabel->DrawLatex(0.7, 0.85, "1 b-tag, |#Deltay| < 1.0");
    if (tag == 2) categoryLabel->DrawLatex(0.7, 0.85, "2 b-tags, |#Deltay| < 1.0");
    if (tag == 3) categoryLabel->DrawLatex(0.7, 0.85, "0 b-tags, |#Deltay| > 1.0");
    if (tag == 4) categoryLabel->DrawLatex(0.7, 0.85, "1 b-tag, |#Deltay| > 1.0");
    if (tag == 5) categoryLabel->DrawLatex(0.7, 0.85, "2 b-tags, |#Deltay| > 1.0");
    if (tag == 6) categoryLabel->DrawLatex(0.7, 0.85, "All Signal Regions");

    CMS_lumi(c1_2, 4, 10);

    gPad->RedrawAxis();

    TLegend *leg = new TLegend(0.7, 0.4, 0.94, 0.83);
    //leg->AddEntry(histos[names::DATA][tag], "Data", "lp");
    leg->AddEntry(histos[names::QCD][tag], "Non-Top Multijet", "f");
    leg->AddEntry(histos[names::TT][tag], "SM t#bar{t}", "f");
    if (signal == 0){//ZPN                                                                                                                   
      leg->AddEntry(histos[names::ZPN10][tag], "1 TeV Narrow Z'", "l");
      leg->AddEntry(histos[names::ZPN20][tag], "2 TeV Narrow Z'", "l");
      leg->AddEntry(histos[names::ZPN30][tag], "3 TeV Narrow Z'", "l");
      leg->AddEntry(histos[names::ZPN40][tag], "4 TeV Narrow Z'", "l");
    }
    if (signal == 1){//ZPW                                                                                                                   
      leg->AddEntry(histos[names::ZPN10][tag], "1 TeV Wide Z'", "l");
      leg->AddEntry(histos[names::ZPN20][tag], "2 TeV Wide Z'", "l");
      leg->AddEntry(histos[names::ZPN30][tag], "3 TeV Wide Z'", "l");
      leg->AddEntry(histos[names::ZPN40][tag], "4 TeV Wide Z'", "l");
    }
    if (signal == 2){//ZPXW                                                                                                                  
      leg->AddEntry(histos[names::ZPN10][tag], "1 TeV Extra Wide Z'", "l");
      leg->AddEntry(histos[names::ZPN20][tag], "2 TeV Extra Wide Z'", "l");
      leg->AddEntry(histos[names::ZPN30][tag], "3 TeV Extra Wide Z'", "l");
      leg->AddEntry(histos[names::ZPN40][tag], "4 TeV Extra Wide Z'", "l");
    }
    if (signal == 3){//RSG                                                                                                                   
      leg->AddEntry(histos[names::ZPN10][tag], "1 TeV RS Gluon", "l");
      leg->AddEntry(histos[names::ZPN20][tag], "2 TeV RS Gluon", "l");
      leg->AddEntry(histos[names::ZPN30][tag], "3 TeV RS Gluon", "l");
      leg->AddEntry(histos[names::ZPN40][tag], "4 TeV RS Gluon", "l");
    }
    leg->SetFillColor(0);
    leg->SetLineColor(0);
    leg->Draw("same");

    TH1F *ratioH = new TH1F();
    ratioH = (TH1F*) histos[names::DATA][tag]->Clone("ratioH");
    ratioH->Sumw2();
    ratioH->Divide(ratioH, totalH);

    TH1F *ratioErrH = new TH1F();
    ratioErrH = (TH1F*) totalH->Clone("ratioErrH");
    ratioErrH->Sumw2();
    ratioErrH->Divide(ratioErrH, totalH);

    TH1F *ratioHallerr = new TH1F();
    ratioHallerr = (TH1F*) histos[names::DATA][tag]->Clone("ratioHallerr");
    ratioHallerr->Sumw2();
    ratioHallerr->Divide(ratioHallerr, totalHallerr);

    TH1F *ratioErrHallerr = new TH1F();
    ratioErrHallerr = (TH1F*) totalHallerr->Clone("ratioErrHallerr");
    ratioErrHallerr->Sumw2();
    ratioErrHallerr->Divide(ratioErrHallerr, totalHallerr);

    c1_1->cd();
    c1_1->SetTopMargin(0.01);
    c1_1->SetBottomMargin(0.3);
    c1_1->SetRightMargin(0.05);
    c1_1->SetLeftMargin(0.1);
    c1_1->SetFillStyle(0);

    ratioH->GetYaxis()->SetRangeUser(0.01,1.99);
    ratioH->GetYaxis()->SetTitle("Data / BG");
    ratioH->GetYaxis()->SetTitleOffset(0.3);
    ratioH->GetYaxis()->SetTitleSize(0.13);
    ratioH->GetYaxis()->SetNdivisions(205);
    ratioH->GetYaxis()->SetLabelSize(0.11);
    ratioH->GetXaxis()->SetLabelSize(0.11);
    ratioH->GetXaxis()->SetTitleSize(0.13);
    ratioH->GetXaxis()->SetTitle( "t#bar{t} Invariant Mass [GeV]");
    ratioH->Draw("E0");

    ratioErrH->SetFillStyle(1001);
    ratioErrH->SetFillColor(kGray);

    ratioErrHallerr->SetFillStyle(1001);
    ratioErrHallerr->SetFillColor(kGray+1);
    ratioErrHallerr->Draw("E2 same");
    ratioErrH->Draw("E2 same");

    TF1 *line = new TF1("line", "1", 0, 7000);
    line->SetLineColor(kBlack);
    //line->Draw("");
    line->Draw("same");
    ratioH->Draw("E0 same");
    ratioErrH->Draw("E0 same");

    gPad->RedrawAxis();
    
    if (signal == 0){//ZPN                                                                                                                   
      c1->SaveAs("Distributions/V5/ZPN_errors"+tagLabels[tag]+outEnd+"_noClosurenoTopTagErr.pdf");
      //c1->SaveAs("Distributions/V5/ZPN_errors"+tagLabels[tag]+outEnd+".png");
      c1_2->cd();
      histos[names::DATA][tag]->SetMaximum(10000.0 * totalH->GetMaximum() );
      histos[names::DATA][tag]->SetMinimum(0.01);
      if (tag == 2 || tag == 5) histos[names::DATA][tag]->SetMaximum(100.0 * histos[names::DATA][tag]->GetMaximum() );
      c1_2->SetLogy(1);
      c1->SaveAs("Distributions/V5/ZPN_errors"+tagLabels[tag]+"log_"+outEnd+"_noClosurenoTopTagErr.pdf");
      //c1->SaveAs("Distributions/V5/ZPN_errors"+tagLabels[tag]+"log_"+outEnd+".png");
    }//ZPN, signal = 0                                                                                                                       
    else if (signal == 1){//ZPW                                                                                                              
      c1->SaveAs("Distributions/V5/ZPW_errors"+tagLabels[tag]+outEnd+".pdf");
      //c1->SaveAs("Distributions/V5/ZPW_errors"+tagLabels[tag]+outEnd+".png");
      c1_2->cd();
      totalH->SetMaximum(1000.0 * totalH->GetMaximum() );
      totalH->SetMinimum(0.01);
      c1_2->SetLogy(1);
      c1->SaveAs("Distributions/V5/ZPW_errors"+tagLabels[tag]+"log_"+outEnd+".pdf");
      //c1->SaveAs("Distributions/V5/ZPW_errors"+tagLabels[tag]+"log_"+outEnd+".png");
    }//ZPW, signal = 1
    else if (signal == 2){//ZPXW                                                                                                             
      c1->SaveAs("Distributions/V5/ZPXW_errors"+tagLabels[tag]+outEnd+".pdf");
      //c1->SaveAs("Distributions/V5/ZPXW_errors"+tagLabels[tag]+outEnd+".png");
      c1_2->cd();
      totalH->SetMaximum(1000.0 * totalH->GetMaximum() );
      totalH->SetMinimum(0.01);
      c1_2->SetLogy(1);
      c1->SaveAs("Distributions/V5/ZPXW_errors"+tagLabels[tag]+"log_"+outEnd+".pdf");
      //c1->SaveAs("Distributions/V5/ZPXW_errors"+tagLabels[tag]+"log_"+outEnd+".png");
    }//ZPXW, signal = 2                                                                                                                      
    else if (signal == 3){//RSG                                                                                                              
      c1->SaveAs("Distributions/V5/RSG_errors"+tagLabels[tag]+outEnd+".pdf");
      //c1->SaveAs("Distributions/V5/RSG_errors"+tagLabels[tag]+outEnd+".png");
      c1_2->cd();
      totalH->SetMaximum(1000.0 * totalH->GetMaximum() );
      totalH->SetMinimum(0.01);
      c1_2->SetLogy(1);
      c1->SaveAs("Distributions/V5/RSG_errors"+tagLabels[tag]+"log_"+outEnd+".pdf");
      //c1->SaveAs("Distributions/V5/RSG_errors"+tagLabels[tag]+"log_"+outEnd+".png");
    }//RSG, signal = 3  

    if (postFit) continue;

    outFile->cd();

    //Modmass Systematics
    TH1F *qcdShapeSyst_Up = (TH1F *) histos[names::QCD][tag]->Clone("qcdSystUp");
    TH1F *qcdShapeSyst_Dn = (TH1F *) histos[names::QCD][tag]->Clone("qcdSystDn");

    for (int i = 0; i < histos[names::QCD][tag]->GetNbinsX(); i++){

      float diff = 0.5*abs( histos[names::QCD][tag]->GetBinContent(i) - histos[names::QCD_SYST][tag]->GetBinContent(i) );
      qcdShapeSyst_Up->AddBinContent(i, diff);
      qcdShapeSyst_Dn->AddBinContent(i, -1*diff);
      if (qcdShapeSyst_Dn->GetBinContent(i) < 0.0){
	qcdShapeSyst_Dn->SetBinContent(i,0.0);
      }
      if (qcdShapeSyst_Up->GetBinContent(i) < 0.0){
	qcdShapeSyst_Up->SetBinContent(i,0.0);
      }
    }

    qcdShapeSyst_Up->Write( Form("btag%d__qcd__modMass__up", tag) );
    qcdShapeSyst_Dn->Write( Form("btag%d__qcd__modMass__down", tag) );

    //Closure Test Systematic
    TH1F *qcdClosureSyst_Up = (TH1F *) histos[names::QCD][tag]->Clone("qcdClosureSystUp");
    TH1F *qcdClosureSyst_Dn = (TH1F *) histos[names::QCD][tag]->Clone("qcdClosureSystDn");

    for (int i = 0; i < histos[names::QCDMC][tag]->GetNbinsX(); i++){
      
      float diffClose = 0.0;
      if (histos[names::QCDMC][tag]->GetBinContent(i) != 0){
	diffClose = abs( histos[names::QCDMC][tag]->GetBinContent(i) - histos[names::QCDMC_SYST][tag]->GetBinContent(i) )/(histos[names::QCDMC][tag]->GetBinContent(i));
      }

      float loEdge = histos[names::QCDMC][tag]->GetBinLowEdge(i);
      float hiEdge = histos[names::QCDMC][tag]->GetBinLowEdge(i+1);
      int loBin = histos[names::QCD][tag]->GetXaxis()->FindBin(loEdge);
      int hiBin = histos[names::QCD][tag]->GetXaxis()->FindBin(hiEdge);
      
      for (int j = loBin; j < hiBin; j++){
	if (j < histos[names::QCD][tag]->GetNbinsX()){
	  qcdClosureSyst_Up->AddBinContent(j, diffClose*(histos[names::QCD][tag]->GetBinContent(j)));
	  qcdClosureSyst_Dn->AddBinContent(j, -1*diffClose*(histos[names::QCD][tag]->GetBinContent(j)));
	  if (qcdClosureSyst_Dn->GetBinContent(j) < 0.0){
	    qcdClosureSyst_Dn->SetBinContent(j,0.0);
	  }
	  if (qcdClosureSyst_Up->GetBinContent(j) < 0.0){
	    qcdClosureSyst_Up->SetBinContent(j,0.0);
	  }
	}
      }
    }

    qcdClosureSyst_Up->Write( Form("btag%d__qcd__closure__up", tag) );
    qcdClosureSyst_Dn->Write( Form("btag%d__qcd__closure__down", tag) );

    //Top pt reweighting Systematics
    TH1F *TTweightSyst_Up = (TH1F *) histos[names::TT][tag]->Clone("TTweightSyst_Up");
    TH1F *TTweightSyst_Dn = (TH1F *) histos[names::TT][tag]->Clone("TTweightSyst_Dn");

    for (int i = 0; i < histos[names::TT][tag]->GetNbinsX(); i++){

      float diff = abs( histos[names::TT][tag]->GetBinContent(i) - histos[names::TT_WEIGHTSYST][tag]->GetBinContent(i) );
      TTweightSyst_Up->AddBinContent(i, diff);
      TTweightSyst_Dn->AddBinContent(i, -1*diff);
      if (TTweightSyst_Dn->GetBinContent(i) < 0.0){
	TTweightSyst_Dn->SetBinContent(i,0.0);
      }
      if (TTweightSyst_Up->GetBinContent(i) < 0.0){
	TTweightSyst_Up->SetBinContent(i,0.0);
      }
    }

    TTweightSyst_Up->Write( Form("btag%d__ttbar__ttweight__up", tag) );
    TTweightSyst_Dn->Write( Form("btag%d__ttbar__ttweight__down", tag) );

    if (blinding != 2) histos[names::DATA][tag]->Write( Form("btag%d__DATA", tag) );
    histos[names::QCD][tag]->Write( Form("btag%d__qcd", tag) );
    histos[names::TT][tag]->Write( Form("btag%d__ttbar", tag) );
    histos[names::TT_SCALEUP][tag]->Write( Form("btag%d__ttbar__jec__up", tag) );
    histos[names::TT_SCALEDN][tag]->Write( Form("btag%d__ttbar__jec__down", tag) );
    histos[names::TT_JERUP][tag]->Write( Form("btag%d__ttbar__jer__up", tag) );
    histos[names::TT_JERDN][tag]->Write( Form("btag%d__ttbar__jer__down", tag) );
    histos[names::TT_PDFUP][tag]->Write( Form("btag%d__ttbar__pdf__up", tag) );
    histos[names::TT_PDFDN][tag]->Write( Form("btag%d__ttbar__pdf__down", tag) );
    histos[names::TT_BTAGUP][tag]->Write( Form("btag%d__ttbar__btag__up", tag) );
    histos[names::TT_BTAGDN][tag]->Write( Form("btag%d__ttbar__btag__down", tag) );
    histos[names::TT_BMISTAGUP][tag]->Write( Form("btag%d__ttbar__bmistag__up", tag) );
    histos[names::TT_BMISTAGDN][tag]->Write( Form("btag%d__ttbar__bmistag__down", tag) );
    histos[names::TT_PUUP][tag]->Write( Form("btag%d__ttbar__pileup__up", tag) );
    histos[names::TT_PUDN][tag]->Write( Form("btag%d__ttbar__pileup__down", tag) );
    histos[names::TT_Q2UP][tag]->Write( Form("btag%d__ttbar__q2__up", tag) );
    histos[names::TT_Q2DN][tag]->Write( Form("btag%d__ttbar__q2__down", tag) );
    
    histos[names::ZPN10][tag]->Write( Form("btag%d__Zprime1000", tag));
    if (signal != 2) histos[names::ZPN12p5][tag]->Write( Form("btag%d__Zprime1250", tag));
    if (signal != 2) histos[names::ZPN15][tag]->Write( Form("btag%d__Zprime1500", tag) );
    histos[names::ZPN20][tag]->Write( Form("btag%d__Zprime2000", tag) );
    if (signal != 2) histos[names::ZPN25][tag]->Write( Form("btag%d__Zprime2500", tag) );
    histos[names::ZPN30][tag]->Write( Form("btag%d__Zprime3000", tag) );
    if (signal != 2) histos[names::ZPN35][tag]->Write( Form("btag%d__Zprime3500", tag) );  
    histos[names::ZPN40][tag]->Write( Form("btag%d__Zprime4000", tag) );  
    if (signal != 2) histos[names::ZPN45][tag]->Write( Form("btag%d__Zprime4500", tag) );  
    histos[names::ZPN50][tag]->Write( Form("btag%d__Zprime5000", tag) );  
    histos[names::ZPN40][tag]->Write( Form("btag%d__Zprime4000", tag) );  
    if (signal != 2) histos[names::ZPN45][tag]->Write( Form("btag%d__Zprime4500", tag) );  
    histos[names::ZPN50][tag]->Write( Form("btag%d__Zprime5000", tag) );  
 
    histos[names::ZPN10_SCALEUP][tag]->Write( Form("btag%d__Zprime1000__jec__up", tag));
    if (signal != 2) histos[names::ZPN12p5_SCALEUP][tag]->Write( Form("btag%d__Zprime1250__jec__up", tag));
    if (signal != 2) histos[names::ZPN15_SCALEUP][tag]->Write( Form("btag%d__Zprime1500__jec__up", tag) );
    histos[names::ZPN20_SCALEUP][tag]->Write( Form("btag%d__Zprime2000__jec__up", tag) );
    if (signal != 2) histos[names::ZPN25_SCALEUP][tag]->Write( Form("btag%d__Zprime2500__jec__up", tag) );
    histos[names::ZPN30_SCALEUP][tag]->Write( Form("btag%d__Zprime3000__jec__up", tag) );
    if (signal != 2) histos[names::ZPN35_SCALEUP][tag]->Write( Form("btag%d__Zprime3500__jec__up", tag) ); 
    histos[names::ZPN40_SCALEUP][tag]->Write( Form("btag%d__Zprime4000__jec__up", tag) ); 
    if (signal != 2) histos[names::ZPN45_SCALEUP][tag]->Write( Form("btag%d__Zprime4500__jec__up", tag) ); 
    histos[names::ZPN50_SCALEUP][tag]->Write( Form("btag%d__Zprime5000__jec__up", tag) ); 
    histos[names::ZPN10_SCALEDN][tag]->Write( Form("btag%d__Zprime1000__jec__down", tag));
    if (signal != 2) histos[names::ZPN12p5_SCALEDN][tag]->Write( Form("btag%d__Zprime1250__jec__down", tag));
    if (signal != 2) histos[names::ZPN15_SCALEDN][tag]->Write( Form("btag%d__Zprime1500__jec__down", tag) );
    histos[names::ZPN20_SCALEDN][tag]->Write( Form("btag%d__Zprime2000__jec__down", tag) );
    if (signal != 2) histos[names::ZPN25_SCALEDN][tag]->Write( Form("btag%d__Zprime2500__jec__down", tag) );
    histos[names::ZPN30_SCALEDN][tag]->Write( Form("btag%d__Zprime3000__jec__down", tag) );
    if (signal != 2) histos[names::ZPN35_SCALEDN][tag]->Write( Form("btag%d__Zprime3500__jec__down", tag) );  
    histos[names::ZPN40_SCALEDN][tag]->Write( Form("btag%d__Zprime4000__jec__down", tag) );  
    if (signal != 2) histos[names::ZPN45_SCALEDN][tag]->Write( Form("btag%d__Zprime4500__jec__down", tag) );  
    histos[names::ZPN50_SCALEDN][tag]->Write( Form("btag%d__Zprime5000__jec__down", tag) );  
  
    histos[names::ZPN10_JERUP][tag]->Write( Form("btag%d__Zprime1000__jer__up", tag));
    if (signal != 2) histos[names::ZPN12p5_JERUP][tag]->Write( Form("btag%d__Zprime1250__jer__up", tag));
    if (signal != 2) histos[names::ZPN15_JERUP][tag]->Write( Form("btag%d__Zprime1500__jer__up", tag) );
    histos[names::ZPN20_JERUP][tag]->Write( Form("btag%d__Zprime2000__jer__up", tag) );
    if (signal != 2) histos[names::ZPN25_JERUP][tag]->Write( Form("btag%d__Zprime2500__jer__up", tag) );
    histos[names::ZPN30_JERUP][tag]->Write( Form("btag%d__Zprime3000__jer__up", tag) );
    if (signal != 2) histos[names::ZPN35_JERUP][tag]->Write( Form("btag%d__Zprime3500__jer__up", tag) ); 
    histos[names::ZPN40_JERUP][tag]->Write( Form("btag%d__Zprime4000__jer__up", tag) ); 
    if (signal != 2) histos[names::ZPN45_JERUP][tag]->Write( Form("btag%d__Zprime4500__jer__up", tag) ); 
    histos[names::ZPN50_JERUP][tag]->Write( Form("btag%d__Zprime5000__jer__up", tag) ); 
    histos[names::ZPN10_JERDN][tag]->Write( Form("btag%d__Zprime1000__jer__down", tag));
    if (signal != 2) histos[names::ZPN12p5_JERDN][tag]->Write( Form("btag%d__Zprime1250__jer__down", tag));
    if (signal != 2) histos[names::ZPN15_JERDN][tag]->Write( Form("btag%d__Zprime1500__jer__down", tag) );
    histos[names::ZPN20_JERDN][tag]->Write( Form("btag%d__Zprime2000__jer__down", tag) );
    if (signal != 2) histos[names::ZPN25_JERDN][tag]->Write( Form("btag%d__Zprime2500__jer__down", tag) );
    histos[names::ZPN30_JERDN][tag]->Write( Form("btag%d__Zprime3000__jer__down", tag) );
    if (signal != 2) histos[names::ZPN35_JERDN][tag]->Write( Form("btag%d__Zprime3500__jer__down", tag) );  
    histos[names::ZPN40_JERDN][tag]->Write( Form("btag%d__Zprime4000__jer__down", tag) );  
    if (signal != 2) histos[names::ZPN45_JERDN][tag]->Write( Form("btag%d__Zprime4500__jer__down", tag) );  
    histos[names::ZPN50_JERDN][tag]->Write( Form("btag%d__Zprime5000__jer__down", tag) );  

    histos[names::ZPN10_PDFUP][tag]->Write( Form("btag%d__Zprime1000__pdf__up", tag));
    if (signal != 2) histos[names::ZPN12p5_PDFUP][tag]->Write( Form("btag%d__Zprime1250__pdf__up", tag));
    if (signal != 2) histos[names::ZPN15_PDFUP][tag]->Write( Form("btag%d__Zprime1500__pdf__up", tag) );
    histos[names::ZPN20_PDFUP][tag]->Write( Form("btag%d__Zprime2000__pdf__up", tag) );
    if (signal != 2) histos[names::ZPN25_PDFUP][tag]->Write( Form("btag%d__Zprime2500__pdf__up", tag) );
    histos[names::ZPN30_PDFUP][tag]->Write( Form("btag%d__Zprime3000__pdf__up", tag) );
    if (signal != 2) histos[names::ZPN35_PDFUP][tag]->Write( Form("btag%d__Zprime3500__pdf__up", tag) ); 
    histos[names::ZPN40_PDFUP][tag]->Write( Form("btag%d__Zprime4000__pdf__up", tag) ); 
    if (signal != 2) histos[names::ZPN45_PDFUP][tag]->Write( Form("btag%d__Zprime4500__pdf__up", tag) ); 
    histos[names::ZPN50_PDFUP][tag]->Write( Form("btag%d__Zprime5000__pdf__up", tag) ); 
    histos[names::ZPN10_PDFDN][tag]->Write( Form("btag%d__Zprime1000__pdf__down", tag));
    if (signal != 2) histos[names::ZPN12p5_PDFDN][tag]->Write( Form("btag%d__Zprime1250__pdf__down", tag));
    if (signal != 2) histos[names::ZPN15_PDFDN][tag]->Write( Form("btag%d__Zprime1500__pdf__down", tag) );
    histos[names::ZPN20_PDFDN][tag]->Write( Form("btag%d__Zprime2000__pdf__down", tag) );
    if (signal != 2) histos[names::ZPN25_PDFDN][tag]->Write( Form("btag%d__Zprime2500__pdf__down", tag) );
    histos[names::ZPN30_PDFDN][tag]->Write( Form("btag%d__Zprime3000__pdf__down", tag) );
    if (signal != 2) histos[names::ZPN35_PDFDN][tag]->Write( Form("btag%d__Zprime3500__pdf__down", tag) );  
    histos[names::ZPN40_PDFDN][tag]->Write( Form("btag%d__Zprime4000__pdf__down", tag) );  
    if (signal != 2) histos[names::ZPN45_PDFDN][tag]->Write( Form("btag%d__Zprime4500__pdf__down", tag) );  
    histos[names::ZPN50_PDFDN][tag]->Write( Form("btag%d__Zprime5000__pdf__down", tag) );  

    histos[names::ZPN10_BTAGUP][tag]->Write( Form("btag%d__Zprime1000__btag__up", tag));
    if (signal != 2) histos[names::ZPN12p5_BTAGUP][tag]->Write( Form("btag%d__Zprime1250__btag__up", tag));
    if (signal != 2) histos[names::ZPN15_BTAGUP][tag]->Write( Form("btag%d__Zprime1500__btag__up", tag) );
    histos[names::ZPN20_BTAGUP][tag]->Write( Form("btag%d__Zprime2000__btag__up", tag) );
    if (signal != 2) histos[names::ZPN25_BTAGUP][tag]->Write( Form("btag%d__Zprime2500__btag__up", tag) );
    histos[names::ZPN30_BTAGUP][tag]->Write( Form("btag%d__Zprime3000__btag__up", tag) );
    if (signal != 2) histos[names::ZPN35_BTAGUP][tag]->Write( Form("btag%d__Zprime3500__btag__up", tag) ); 
    histos[names::ZPN40_BTAGUP][tag]->Write( Form("btag%d__Zprime4000__btag__up", tag) ); 
    if (signal != 2) histos[names::ZPN45_BTAGUP][tag]->Write( Form("btag%d__Zprime4500__btag__up", tag) ); 
    histos[names::ZPN50_BTAGUP][tag]->Write( Form("btag%d__Zprime5000__btag__up", tag) ); 
    histos[names::ZPN10_BTAGDN][tag]->Write( Form("btag%d__Zprime1000__btag__down", tag));
    if (signal != 2) histos[names::ZPN12p5_BTAGDN][tag]->Write( Form("btag%d__Zprime1250__btag__down", tag));
    if (signal != 2) histos[names::ZPN15_BTAGDN][tag]->Write( Form("btag%d__Zprime1500__btag__down", tag) );
    histos[names::ZPN20_BTAGDN][tag]->Write( Form("btag%d__Zprime2000__btag__down", tag) );
    if (signal != 2) histos[names::ZPN25_BTAGDN][tag]->Write( Form("btag%d__Zprime2500__btag__down", tag) );
    histos[names::ZPN30_BTAGDN][tag]->Write( Form("btag%d__Zprime3000__btag__down", tag) );
    if (signal != 2) histos[names::ZPN35_BTAGDN][tag]->Write( Form("btag%d__Zprime3500__btag__down", tag) );
    histos[names::ZPN40_BTAGDN][tag]->Write( Form("btag%d__Zprime4000__btag__down", tag) );  
    if (signal != 2) histos[names::ZPN45_BTAGDN][tag]->Write( Form("btag%d__Zprime4500__btag__down", tag) );
    histos[names::ZPN50_BTAGDN][tag]->Write( Form("btag%d__Zprime5000__btag__down", tag) );  

    histos[names::ZPN10_BMISTAGUP][tag]->Write( Form("btag%d__Zprime1000__bmistag__up", tag));
    if (signal != 2) histos[names::ZPN12p5_BMISTAGUP][tag]->Write( Form("btag%d__Zprime1250__bmistag__up", tag));
    if (signal != 2) histos[names::ZPN15_BMISTAGUP][tag]->Write( Form("btag%d__Zprime1500__bmistag__up", tag) );
    histos[names::ZPN20_BMISTAGUP][tag]->Write( Form("btag%d__Zprime2000__bmistag__up", tag) );
    if (signal != 2) histos[names::ZPN25_BMISTAGUP][tag]->Write( Form("btag%d__Zprime2500__bmistag__up", tag) );
    histos[names::ZPN30_BMISTAGUP][tag]->Write( Form("btag%d__Zprime3000__bmistag__up", tag) );
    if (signal != 2) histos[names::ZPN35_BMISTAGUP][tag]->Write( Form("btag%d__Zprime3500__bmistag__up", tag) ); 
    histos[names::ZPN40_BMISTAGUP][tag]->Write( Form("btag%d__Zprime4000__bmistag__up", tag) ); 
    if (signal != 2) histos[names::ZPN45_BMISTAGUP][tag]->Write( Form("btag%d__Zprime4500__bmistag__up", tag) ); 
    histos[names::ZPN50_BMISTAGUP][tag]->Write( Form("btag%d__Zprime5000__bmistag__up", tag) ); 
    histos[names::ZPN10_BMISTAGDN][tag]->Write( Form("btag%d__Zprime1000__bmistag__down", tag));
    if (signal != 2) histos[names::ZPN12p5_BMISTAGDN][tag]->Write( Form("btag%d__Zprime1250__bmistag__down", tag));
    if (signal != 2) histos[names::ZPN15_BMISTAGDN][tag]->Write( Form("btag%d__Zprime1500__bmistag__down", tag) );
    histos[names::ZPN20_BMISTAGDN][tag]->Write( Form("btag%d__Zprime2000__bmistag__down", tag) );
    if (signal != 2) histos[names::ZPN25_BMISTAGDN][tag]->Write( Form("btag%d__Zprime2500__bmistag__down", tag) );
    histos[names::ZPN30_BMISTAGDN][tag]->Write( Form("btag%d__Zprime3000__bmistag__down", tag) );
    if (signal != 2) histos[names::ZPN35_BMISTAGDN][tag]->Write( Form("btag%d__Zprime3500__bmistag__down", tag) );
    histos[names::ZPN40_BMISTAGDN][tag]->Write( Form("btag%d__Zprime4000__bmistag__down", tag) );  
    if (signal != 2) histos[names::ZPN45_BMISTAGDN][tag]->Write( Form("btag%d__Zprime4500__bmistag__down", tag) );
    histos[names::ZPN50_BMISTAGDN][tag]->Write( Form("btag%d__Zprime5000__bmistag__down", tag) );  
    
    histos[names::ZPN10_PUUP][tag]->Write( Form("btag%d__Zprime1000__pileup__up", tag));
    if (signal != 2) histos[names::ZPN12p5_PUUP][tag]->Write( Form("btag%d__Zprime1250__pileup__up", tag));
    if (signal != 2) histos[names::ZPN15_PUUP][tag]->Write( Form("btag%d__Zprime1500__pileup__up", tag) );
    histos[names::ZPN20_PUUP][tag]->Write( Form("btag%d__Zprime2000__pileup__up", tag) );
    if (signal != 2) histos[names::ZPN25_PUUP][tag]->Write( Form("btag%d__Zprime2500__pileup__up", tag) );
    histos[names::ZPN30_PUUP][tag]->Write( Form("btag%d__Zprime3000__pileup__up", tag) );
    if (signal != 2) histos[names::ZPN35_PUUP][tag]->Write( Form("btag%d__Zprime3500__pileup__up", tag) ); 
    histos[names::ZPN40_PUUP][tag]->Write( Form("btag%d__Zprime4000__pileup__up", tag) ); 
    if (signal != 2) histos[names::ZPN45_PUUP][tag]->Write( Form("btag%d__Zprime4500__pileup__up", tag) ); 
    histos[names::ZPN50_PUUP][tag]->Write( Form("btag%d__Zprime5000__pileup__up", tag) ); 
    histos[names::ZPN10_PUDN][tag]->Write( Form("btag%d__Zprime1000__pileup__down", tag));
    if (signal != 2) histos[names::ZPN12p5_PUDN][tag]->Write( Form("btag%d__Zprime1250__pileup__down", tag));
    if (signal != 2) histos[names::ZPN15_PUDN][tag]->Write( Form("btag%d__Zprime1500__pileup__down", tag) );
    histos[names::ZPN20_PUDN][tag]->Write( Form("btag%d__Zprime2000__pileup__down", tag) );
    if (signal != 2) histos[names::ZPN25_PUDN][tag]->Write( Form("btag%d__Zprime2500__pileup__down", tag) );
    histos[names::ZPN30_PUDN][tag]->Write( Form("btag%d__Zprime3000__pileup__down", tag) );
    if (signal != 2) histos[names::ZPN35_PUDN][tag]->Write( Form("btag%d__Zprime3500__pileup__down", tag) );  
    histos[names::ZPN40_PUDN][tag]->Write( Form("btag%d__Zprime4000__pileup__down", tag) );  
    if (signal != 2) histos[names::ZPN45_PUDN][tag]->Write( Form("btag%d__Zprime4500__pileup__down", tag) );  
    histos[names::ZPN50_PUDN][tag]->Write( Form("btag%d__Zprime5000__pileup__down", tag) );  

    if (signal == 1) histos[names::ZPN60][tag]->Write( Form("btag%d__Zprime6000", tag) );
    if (signal == 1) histos[names::ZPN60_SCALEUP][tag]->Write( Form("btag%d__Zprime6000__jec__up", tag) );
    if (signal == 1) histos[names::ZPN60_SCALEDN][tag]->Write( Form("btag%d__Zprime6000__jec__down", tag) );
    if (signal == 1) histos[names::ZPN60_JERUP][tag]->Write( Form("btag%d__Zprime6000__jer__up", tag) );
    if (signal == 1) histos[names::ZPN60_JERDN][tag]->Write( Form("btag%d__Zprime6000__jer__down", tag) );
    if (signal == 1) histos[names::ZPN60_PDFUP][tag]->Write( Form("btag%d__Zprime6000__pdf__up", tag) );
    if (signal == 1) histos[names::ZPN60_PDFDN][tag]->Write( Form("btag%d__Zprime6000__pdf__down", tag) );
    if (signal == 1) histos[names::ZPN60_BTAGUP][tag]->Write( Form("btag%d__Zprime6000__btag__up", tag) );
    if (signal == 1) histos[names::ZPN60_BTAGDN][tag]->Write( Form("btag%d__Zprime6000__btag__down", tag) );
    if (signal == 1) histos[names::ZPN60_BMISTAGUP][tag]->Write( Form("btag%d__Zprime6000__bmistag__up", tag) );
    if (signal == 1) histos[names::ZPN60_BMISTAGDN][tag]->Write( Form("btag%d__Zprime6000__bmistag__down", tag) );
    if (signal == 1) histos[names::ZPN60_PUUP][tag]->Write( Form("btag%d__Zprime6000__pileup__up", tag) );
    if (signal == 1) histos[names::ZPN60_PUDN][tag]->Write( Form("btag%d__Zprime6000__pileup__down", tag) );

    if (signal < 3) histos[names::ZPN65][tag]->Write( Form("btag%d__Zprime6500", tag) );
    if (signal < 3) histos[names::ZPN65_SCALEUP][tag]->Write( Form("btag%d__Zprime6500__jec__up", tag) );
    if (signal < 3) histos[names::ZPN65_SCALEDN][tag]->Write( Form("btag%d__Zprime6500__jec__down", tag) );
    if (signal < 3) histos[names::ZPN65_JERUP][tag]->Write( Form("btag%d__Zprime6500__jer__up", tag) );
    if (signal < 3) histos[names::ZPN65_JERDN][tag]->Write( Form("btag%d__Zprime6500__jer__down", tag) );
    if (signal < 3) histos[names::ZPN65_PDFUP][tag]->Write( Form("btag%d__Zprime6500__pdf__up", tag) );
    if (signal < 3) histos[names::ZPN65_PDFDN][tag]->Write( Form("btag%d__Zprime6500__pdf__down", tag) );
    if (signal < 3) histos[names::ZPN65_BTAGUP][tag]->Write( Form("btag%d__Zprime6500__btag__up", tag) );
    if (signal < 3) histos[names::ZPN65_BTAGDN][tag]->Write( Form("btag%d__Zprime6500__btag__down", tag) );
    if (signal < 3) histos[names::ZPN65_BMISTAGUP][tag]->Write( Form("btag%d__Zprime6500__bmistag__up", tag) );
    if (signal < 3) histos[names::ZPN65_BMISTAGDN][tag]->Write( Form("btag%d__Zprime6500__bmistag__down", tag) );
    if (signal < 3) histos[names::ZPN65_PUUP][tag]->Write( Form("btag%d__Zprime6500__pileup__up", tag) );
    if (signal < 3) histos[names::ZPN65_PUDN][tag]->Write( Form("btag%d__Zprime6500__pileup__down", tag) );

    if (signal < 3) histos[names::ZPN70][tag]->Write( Form("btag%d__Zprime7000", tag) );
    if (signal < 3) histos[names::ZPN70_SCALEUP][tag]->Write( Form("btag%d__Zprime7000__jec__up", tag) );
    if (signal < 3) histos[names::ZPN70_SCALEDN][tag]->Write( Form("btag%d__Zprime7000__jec__down", tag) );
    if (signal < 3) histos[names::ZPN70_JERUP][tag]->Write( Form("btag%d__Zprime7000__jer__up", tag) );
    if (signal < 3) histos[names::ZPN70_JERDN][tag]->Write( Form("btag%d__Zprime7000__jer__down", tag) );
    if (signal < 3) histos[names::ZPN70_PDFUP][tag]->Write( Form("btag%d__Zprime7000__pdf__up", tag) );
    if (signal < 3) histos[names::ZPN70_PDFDN][tag]->Write( Form("btag%d__Zprime7000__pdf__down", tag) );
    if (signal < 3) histos[names::ZPN70_BTAGUP][tag]->Write( Form("btag%d__Zprime7000__btag__up", tag) );
    if (signal < 3) histos[names::ZPN70_BTAGDN][tag]->Write( Form("btag%d__Zprime7000__btag__down", tag) );
    if (signal < 3) histos[names::ZPN70_BMISTAGUP][tag]->Write( Form("btag%d__Zprime7000__bmistag__up", tag) );
    if (signal < 3) histos[names::ZPN70_BMISTAGDN][tag]->Write( Form("btag%d__Zprime7000__bmistag__down", tag) );
    if (signal < 3) histos[names::ZPN70_PUUP][tag]->Write( Form("btag%d__Zprime7000__pileup__up", tag) );
    if (signal < 3) histos[names::ZPN70_PUDN][tag]->Write( Form("btag%d__Zprime7000__pileup__down", tag) );
  }  

  //yields tables for AN
  cout << "High delta y" <<endl;
  cout << "NTMJ                & $ " << (int) histos[names::QCD][3]->Integral() << " #pm " << (int) QCDerr[3] << " $ & $ " << (int) histos[names::QCD][4]->Integral() << " #pm " << (int) QCDerr[4] << " $ & $ " << (int) histos[names::QCD][5]->Integral() << " #pm " << (int) QCDerr[5] << " $ ##" <<endl;
  cout << "SM #ttbar           & $ " << (int) histos[names::TT][3]->Integral() << " #pm " << (int) TTerr[3] << " $ & $ " << (int) histos[names::TT][4]->Integral() << " #pm " << (int) TTerr[4] << " $ & $ " << (int) histos[names::TT][5]->Integral() << " #pm " << (int) TTerr[5] << " $ ##" <<endl;
  cout <<"#hline"<<endl;
  cout <<""<<endl;
  cout << "Total Background    & $ " << (int) histos[names::TT][3]->Integral() + (int) histos[names::QCD][3]->Integral() << " #pm " << (int) BKGerr[3] << " $ & $ " << (int) histos[names::QCD][4]->Integral() + (int) histos[names::TT][4]->Integral()<< " #pm " << (int) BKGerr[4] << " $ & $ " << (int) histos[names::TT][5]->Integral() + (int) histos[names::QCD][5]->Integral() << " #pm " << (int) BKGerr[5] << " $ ##" <<endl;
  cout << "Observed DATA                & $ " << (int) histos[names::DATA][3]->Integral() << " $ & $ " << (int) histos[names::DATA][4]->Integral() << " $ & $ " << (int) histos[names::DATA][5]->Integral() << " $ ##" <<endl;

  cout <<""<<endl;
  cout << "Low delta y" <<endl;
  cout << "NTMJ                & $ " << (int) histos[names::QCD][0]->Integral() << " #pm " << (int) QCDerr[0] << " $ & $ " << (int) histos[names::QCD][1]->Integral() << " #pm " << (int) QCDerr[1] << " $ & $ " << (int) histos[names::QCD][2]->Integral() << " #pm " << (int) QCDerr[2] << " $ ##" <<endl;
  cout << "SM #ttbar           & $ " << (int) histos[names::TT][0]->Integral() << " #pm " << (int) TTerr[0] << " $ & $ " << (int) histos[names::TT][1]->Integral() << " #pm " << (int) TTerr[1] << " $ & $ " << (int) histos[names::TT][2]->Integral() << " #pm " << (int) TTerr[2] << " $ ##" <<endl;
  cout <<"#hline"<<endl;
  cout <<""<<endl;
  cout << "Total Background    & $ " << (int) histos[names::TT][0]->Integral() + (int) histos[names::QCD][0]->Integral() << " #pm " << (int) BKGerr[0] << " $ & $ " << (int) histos[names::QCD][1]->Integral() + (int) histos[names::TT][1]->Integral()<< " #pm " << (int) BKGerr[1] << " $ & $ " << (int) histos[names::TT][2]->Integral() + (int) histos[names::QCD][2]->Integral() << " #pm " << (int) BKGerr[2] << " $ ##" <<endl;
  cout << "Observed DATA                & $ " << (int) histos[names::DATA][0]->Integral() << " $ & $ " << (int) histos[names::DATA][1]->Integral() << " $ & $ " << (int) histos[names::DATA][2]->Integral() << " $ ##" <<endl;


  if (!postFit) outFile->Close();
  return 0;

}
