//Script to make templates for shape analysis using Theta
//
//
//
//

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

int makeTemplates(int signal = 0, bool forTHETA = 1, bool pt500 = 1, bool postFit = 0){
//signal: 0 = ZPN, 1 = ZPW, 2 = ZPXW, 3 = RSG

  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0000000000); //this clears all the boxes and crap 

  cout << names::NUM_PROCS << endl;

  int numProcs = names::NUM_PROCS;

  string outEnd = "_forTHETA.";
  if (!forTHETA)  outEnd = ".";
  if (pt500) outEnd = Form("_pt500%s",outEnd.c_str());
  if (postFit) outEnd = Form("_postFit%s",outEnd.c_str());

  string file = Form("templates_narrow%sroot", outEnd.c_str());//ZPN
  if (signal == 1) file = Form("templates_wide%sroot", outEnd.c_str());
  else if (signal == 2) file = Form("templates_extrawide%sroot", outEnd.c_str());
  else if (signal == 3) file = Form("templates_RSGluon%sroot", outEnd.c_str());

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
  labels[names::TT_Q2UP] = "ttbar_q2_up";
  labels[names::TT_Q2DN] = "ttbar_q2_dn";
  labels[names::TT_PDFUP] = "ttbar_pdf_up";
  labels[names::TT_PDFDN] = "ttbar_pdf_dn";
  labels[names::TT_PSHUP] = "ttbar_psh_up";
  labels[names::TT_PSHDN] = "ttbar_psh_dn";
  labels[names::TT_PUUP] = "ttbar_PU_up";
  labels[names::TT_PUDN] = "ttbar_PU_dn";
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
  int nTagCats = 7;

  TString tagLabels[7];
  tagLabels[0] = "btag0";
  tagLabels[1] = "btag1";
  tagLabels[2] = "btag2";
  tagLabels[3] = "btag0_hiDY";  
  tagLabels[4] = "btag1_hiDY";  
  tagLabels[5] = "btag2_hiDY";  
  tagLabels[6] = "all";

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

  TString dir = "/uscms_data/d3/camclean/CMSSW_7_4_1/src/B2GTTbar/test/runs/run20160706/";
  TString pt = "500.0";
  TString histFileDate = "20160706";
  TString ZPNFileDate  = "20160706";
  if (!pt500){
    dir = "/uscms_data/d2/jdolen/B2GAnaFW/CMSSW_7_4_16_patch2/src/Analysis/B2GTTbar/test/runs052016/";    
    pt = "400.0";
    histFileDate = "052016b";
    ZPNFileDate  = "052016f";
  }

  TString files[200];
  files[names::DATA]          = dir +  "outBkgdEst_JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65_"+histFileDate+"_nom_pt"+pt+".root";
  files[names::QCD]           = files[names::DATA];
  files[names::QCD_SYST]      = files[names::DATA];
  files[names::QCDMC]         = dir + "outBkgdEst_QCD_HT700toInf_B2Gv8p4_reader603e_notrig_20160706_nom_pt500_scaled.root";//FIX!!!!!s
  if (!pt500) files[names::QCDMC] = "/uscms_data/d3/maral87/ttbarResonances/B2GAnaFW/CMSSW_7_4_12/src/Analysis/B2GTTbar/test/runs/run_030716/outBkgdEst_QCD_HT700toInf_B2Gv8p4_reader603e_notrig_pDep_030716_nom_scaled.root";
  files[names::QCDMC_SYST]    = files[names::QCDMC];
  files[names::TT]            = dir +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_"+histFileDate+"_nom_pt"+pt+".root";
  files[names::TT_SUBTRACT]       = dir +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_"+histFileDate+"_nom_pt"+pt+".root";
  files[names::TT_SUBTRACTSYST]   = dir +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_"+histFileDate+"_nom_pt"+pt+".root";
  files[names::TT_JERUP]      = dir +   "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_"+histFileDate+"_jer_up_pt"+pt+".root";
  files[names::TT_JERDN]      = dir +   "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_"+histFileDate+"_jer_dn_pt"+pt+".root";
  files[names::TT_SCALEUP]    = dir +   "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_"+histFileDate+"_jec_up_pt"+pt+".root";
  files[names::TT_SCALEDN]    = dir +   "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_"+histFileDate+"_jec_dn_pt"+pt+".root";
  files[names::TT_PDFUP]      = dir +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_"+histFileDate+"_pdf_up_pt"+pt+".root";
  files[names::TT_PDFDN]      = dir +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_"+histFileDate+"_pdf_dn_pt"+pt+".root";
  files[names::TT_PSHUP]      = "/uscms/home/pilot/data/MINIAOD/CMSSW_7_4_1/src/B2GTTbar/test/outBkgdEst_TT_PSup.root_20160711_nom_pt500.0.root";
  files[names::TT_PSHDN]      = "/uscms/home/pilot/data/MINIAOD/CMSSW_7_4_1/src/B2GTTbar/test/outBkgdEst_TT_PSdown.root_20160711_nom_pt500.0.root";
  if (!pt500){
    files[names::TT_PSHUP]      = dir +  "TT_PSup_FromJustinsArea.root_"+histFileDate+"_nom_pt"+pt+".root";
    files[names::TT_PSHDN]      = dir +  "TT_PSdown_FromJustinsArea.root_"+histFileDate+"_nom_pt"+pt+".root";
  }
  files[names::TT_Q2UP]       = dir +   "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_"+histFileDate+"_q2_up_pt"+pt+".root";
  files[names::TT_Q2DN]       = dir +   "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_"+histFileDate+"_q2_dn_pt"+pt+".root";
  files[names::TT_BTAGUP]     = dir +   "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_"+histFileDate+"_bTag_up_pt"+pt+".root";
  files[names::TT_BTAGDN]     = dir +   "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_"+histFileDate+"_bTag_dn_pt"+pt+".root";
  files[names::TT_PUUP]     = dir +   "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_"+histFileDate+"_PU_up_pt"+pt+".root";
  files[names::TT_PUDN]     = dir +   "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_"+histFileDate+"_PU_dn_pt"+pt+".root";

  if (signal == 0){//ZPN
    files[names::ZPN10]         = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_"+ZPNFileDate+"_nom_pt"+pt+".root";
    files[names::ZPN12p5]       = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_"+ZPNFileDate+"_nom_pt"+pt+".root";
    files[names::ZPN15]         = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_"+ZPNFileDate+"_nom_pt"+pt+".root";
    files[names::ZPN20]         = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_"+ZPNFileDate+"_nom_pt"+pt+".root";
    files[names::ZPN25]         = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_"+ZPNFileDate+"_nom_pt"+pt+".root";
    files[names::ZPN30]         = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_"+ZPNFileDate+"_nom_pt"+pt+".root";
    files[names::ZPN35]         = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_"+ZPNFileDate+"_nom_pt"+pt+".root";
    files[names::ZPN40]         = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_"+ZPNFileDate+"_nom_pt"+pt+".root";
    
    files[names::ZPN10_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN12p5_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN15_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN20_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN25_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN30_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN35_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN40_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN10_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_dn_pt"+pt+".root";
    files[names::ZPN12p5_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_dn_pt"+pt+".root";
    files[names::ZPN15_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_dn_pt"+pt+".root";
    files[names::ZPN20_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_dn_pt"+pt+".root";
    files[names::ZPN25_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_dn_pt"+pt+".root";
    files[names::ZPN30_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_dn_pt"+pt+".root";
    files[names::ZPN35_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_dn_pt"+pt+".root";
    files[names::ZPN40_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_dn_pt"+pt+".root";
  
    files[names::ZPN10_JERUP]   = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN12p5_JERUP]   = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN15_JERUP]   = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN20_JERUP]   = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN25_JERUP]   = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN30_JERUP]   = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN35_JERUP]   = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN40_JERUP]   = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN10_JERDN]   = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_dn_pt"+pt+".root";
    files[names::ZPN12p5_JERDN]   = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_dn_pt"+pt+".root";
    files[names::ZPN15_JERDN]   = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_dn_pt"+pt+".root";
    files[names::ZPN20_JERDN]   = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_dn_pt"+pt+".root";
    files[names::ZPN25_JERDN]   = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_dn_pt"+pt+".root";
    files[names::ZPN30_JERDN]   = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_dn_pt"+pt+".root";
    files[names::ZPN35_JERDN]   = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_dn_pt"+pt+".root";
    files[names::ZPN40_JERDN]   = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_dn_pt"+pt+".root";

    files[names::ZPN10_PDFUP]   = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN12p5_PDFUP]   = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN15_PDFUP]   = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN20_PDFUP]   = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN25_PDFUP]   = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN30_PDFUP]   = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN35_PDFUP]   = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN40_PDFUP]   = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN10_PDFDN]   = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_dn_pt"+pt+".root";
    files[names::ZPN12p5_PDFDN]   = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_dn_pt"+pt+".root";
    files[names::ZPN15_PDFDN]   = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_dn_pt"+pt+".root";
    files[names::ZPN20_PDFDN]   = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_dn_pt"+pt+".root";
    files[names::ZPN25_PDFDN]   = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_dn_pt"+pt+".root";
    files[names::ZPN30_PDFDN]   = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_dn_pt"+pt+".root";
    files[names::ZPN35_PDFDN]   = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_dn_pt"+pt+".root";
    files[names::ZPN40_PDFDN]   = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_dn_pt"+pt+".root";
    
    files[names::ZPN10_BTAGUP]  = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN12p5_BTAGUP]  = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN15_BTAGUP]  = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN20_BTAGUP]  = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN25_BTAGUP]  = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN30_BTAGUP]  = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN35_BTAGUP]  = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN40_BTAGUP]  = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN10_BTAGDN]  = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_dn_pt"+pt+".root";
    files[names::ZPN12p5_BTAGDN]  = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_dn_pt"+pt+".root";
    files[names::ZPN15_BTAGDN]  = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_dn_pt"+pt+".root";
    files[names::ZPN20_BTAGDN]  = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_dn_pt"+pt+".root";
    files[names::ZPN25_BTAGDN]  = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_dn_pt"+pt+".root";
    files[names::ZPN30_BTAGDN]  = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_dn_pt"+pt+".root";
    files[names::ZPN35_BTAGDN]  = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_dn_pt"+pt+".root";
    files[names::ZPN40_BTAGDN]  = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_dn_pt"+pt+".root";

    files[names::ZPN10_PUUP]  = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN12p5_PUUP]  = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN15_PUUP]  = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN20_PUUP]  = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN25_PUUP]  = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN30_PUUP]  = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN35_PUUP]  = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN40_PUUP]  = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN10_PUDN]  = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
    files[names::ZPN12p5_PUDN]  = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
    files[names::ZPN15_PUDN]  = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
    files[names::ZPN20_PUDN]  = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
    files[names::ZPN25_PUDN]  = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
    files[names::ZPN30_PUDN]  = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
    files[names::ZPN35_PUDN]  = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
    files[names::ZPN40_PUDN]  = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
  }//ZPN, signal = 0
  else if (signal == 1){//ZPW                                                                                                                
    files[names::ZPN10] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e_"+ZPNFileDate+"_nom_pt"+pt+".root";
    files[names::ZPN12p5] = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e_"+ZPNFileDate+"_nom_pt"+pt+".root";
    files[names::ZPN15] = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e_"+ZPNFileDate+"_nom_pt"+pt+".root";
    files[names::ZPN20] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e_"+ZPNFileDate+"_nom_pt"+pt+".root";
    files[names::ZPN25] = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e_"+ZPNFileDate+"_nom_pt"+pt+".root";
    files[names::ZPN30] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e_"+ZPNFileDate+"_nom_pt"+pt+".root";
    files[names::ZPN35] = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e_"+ZPNFileDate+"_nom_pt"+pt+".root";
    files[names::ZPN40] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e_"+ZPNFileDate+"_nom_pt"+pt+".root";

    files[names::ZPN10_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN12p5_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN15_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN20_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN25_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN30_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN35_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN40_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN10_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_dn_pt"+pt+".root";
    files[names::ZPN12p5_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_dn_pt"+pt+".root";
    files[names::ZPN15_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_dn_pt"+pt+".root";
    files[names::ZPN20_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_dn_pt"+pt+".root";
    files[names::ZPN25_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_dn_pt"+pt+".root";
    files[names::ZPN30_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_dn_pt"+pt+".root";
    files[names::ZPN35_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_dn_pt"+pt+".root";
    files[names::ZPN40_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_dn_pt"+pt+".root";

    files[names::ZPN10_JERUP] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN12p5_JERUP] = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN15_JERUP] = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN20_JERUP] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN25_JERUP] = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN30_JERUP] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN35_JERUP] = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN40_JERUP] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN10_JERDN] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_dn_pt"+pt+".root";
    files[names::ZPN12p5_JERDN] = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_dn_pt"+pt+".root";
    files[names::ZPN15_JERDN] = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_dn_pt"+pt+".root";
    files[names::ZPN20_JERDN] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_dn_pt"+pt+".root";
    files[names::ZPN25_JERDN] = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_dn_pt"+pt+".root";
    files[names::ZPN30_JERDN] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_dn_pt"+pt+".root";
    files[names::ZPN35_JERDN] = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_dn_pt"+pt+".root";
    files[names::ZPN40_JERDN] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_dn_pt"+pt+".root";

    files[names::ZPN10_BTAGUP] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN12p5_BTAGUP] = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN15_BTAGUP] = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN20_BTAGUP] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN25_BTAGUP] = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN30_BTAGUP] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN35_BTAGUP] = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN40_BTAGUP] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN10_BTAGDN] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_dn_pt"+pt+".root";
    files[names::ZPN12p5_BTAGDN] = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_dn_pt"+pt+".root";
    files[names::ZPN15_BTAGDN] = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_dn_pt"+pt+".root";
    files[names::ZPN20_BTAGDN] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_dn_pt"+pt+".root";
    files[names::ZPN25_BTAGDN] = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_dn_pt"+pt+".root";
    files[names::ZPN30_BTAGDN] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_dn_pt"+pt+".root";
    files[names::ZPN35_BTAGDN] = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_dn_pt"+pt+".root";
    files[names::ZPN40_BTAGDN] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_dn_pt"+pt+".root";

    files[names::ZPN10_PDFUP] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN12p5_PDFUP] = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN15_PDFUP] = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN20_PDFUP] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN25_PDFUP] = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN30_PDFUP] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN35_PDFUP] = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN40_PDFUP] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN10_PDFDN] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_dn_pt"+pt+".root";
    files[names::ZPN12p5_PDFDN] = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_dn_pt"+pt+".root";
    files[names::ZPN15_PDFDN] = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_dn_pt"+pt+".root";
    files[names::ZPN20_PDFDN] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_dn_pt"+pt+".root";
    files[names::ZPN25_PDFDN] = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_dn_pt"+pt+".root";
    files[names::ZPN30_PDFDN] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_dn_pt"+pt+".root";
    files[names::ZPN35_PDFDN] = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_dn_pt"+pt+".root";
    files[names::ZPN40_PDFDN] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_dn_pt"+pt+".root";
    

    files[names::ZPN10_PUUP]  = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN12p5_PUUP]  = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN15_PUUP]  = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN20_PUUP]  = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN25_PUUP]  = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN30_PUUP]  = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN35_PUUP]  = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN40_PUUP]  = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN10_PUDN]  = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
    files[names::ZPN12p5_PUDN]  = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
    files[names::ZPN15_PUDN]  = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
    files[names::ZPN20_PUDN]  = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
    files[names::ZPN25_PUDN]  = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
    files[names::ZPN30_PUDN]  = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
    files[names::ZPN35_PUDN]  = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
    files[names::ZPN40_PUDN]  = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
  }//ZPW, signal = 1                                                                                                                         
  else if (signal == 2){//ZPXW                                                                                                               
    files[names::ZPN10] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_"+ZPNFileDate+"_nom_pt"+pt+".root";
    files[names::ZPN12p5] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_"+ZPNFileDate+"_nom_pt"+pt+".root";            
    files[names::ZPN15] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_"+ZPNFileDate+"_nom_pt"+pt+".root";              
    files[names::ZPN20] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_"+ZPNFileDate+"_nom_pt"+pt+".root";
    files[names::ZPN25] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_"+ZPNFileDate+"_nom_pt"+pt+".root";              
    files[names::ZPN30] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_"+ZPNFileDate+"_nom_pt"+pt+".root";
    files[names::ZPN35] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_"+ZPNFileDate+"_nom_pt"+pt+".root";             
    files[names::ZPN40] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_"+ZPNFileDate+"_nom_pt"+pt+".root";

    files[names::ZPN10_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN12p5_SCALEUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN15_SCALEUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_up_pt"+pt+".root";   
    files[names::ZPN20_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN25_SCALEUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_up_pt"+pt+".root";   
    files[names::ZPN30_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN35_SCALEUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_up_pt"+pt+".root";  
    files[names::ZPN40_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN10_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_dn_pt"+pt+".root";
    files[names::ZPN12p5_SCALEDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_dn_pt"+pt+".root";
    files[names::ZPN15_SCALEDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_dn_pt"+pt+".root";   
    files[names::ZPN20_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_dn_pt"+pt+".root";
    files[names::ZPN25_SCALEDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_dn_pt"+pt+".root";   
    files[names::ZPN30_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_dn_pt"+pt+".root";
    files[names::ZPN35_SCALEDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_dn_pt"+pt+".root";  
    files[names::ZPN40_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_"+ZPNFileDate+"_jec_dn_pt"+pt+".root";

    files[names::ZPN10_JERUP] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN12p5_JERUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_up_pt"+pt+".root";   
    files[names::ZPN15_JERUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_up_pt"+pt+".root";     
    files[names::ZPN20_JERUP] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN25_JERUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_up_pt"+pt+".root";     
    files[names::ZPN30_JERUP] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN35_JERUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_up_pt"+pt+".root";    
    files[names::ZPN40_JERUP] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN10_JERDN] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_dn_pt"+pt+".root";
    files[names::ZPN12p5_JERDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_dn_pt"+pt+".root";   
    files[names::ZPN15_JERDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_dn_pt"+pt+".root";     
    files[names::ZPN20_JERDN] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_dn_pt"+pt+".root";
    files[names::ZPN25_JERDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_dn_pt"+pt+".root";     
    files[names::ZPN30_JERDN] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_dn_pt"+pt+".root";
    files[names::ZPN35_JERDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_dn_pt"+pt+".root";    
    files[names::ZPN40_JERDN] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_"+ZPNFileDate+"_jer_dn_pt"+pt+".root";

    files[names::ZPN10_BTAGUP] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN12p5_BTAGUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN15_BTAGUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_up_pt"+pt+".root";   
    files[names::ZPN20_BTAGUP] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN25_BTAGUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_up_pt"+pt+".root";   
    files[names::ZPN30_BTAGUP] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN35_BTAGUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_up_pt"+pt+".root";  
    files[names::ZPN40_BTAGUP] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN10_BTAGDN] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_dn_pt"+pt+".root";
    files[names::ZPN12p5_BTAGDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_dn_pt"+pt+".root";
    files[names::ZPN15_BTAGDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_dn_pt"+pt+".root";  
    files[names::ZPN20_BTAGDN] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_dn_pt"+pt+".root";
    files[names::ZPN25_BTAGDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_dn_pt"+pt+".root";  
    files[names::ZPN30_BTAGDN] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_dn_pt"+pt+".root";
    files[names::ZPN35_BTAGDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_dn_pt"+pt+".root";  
    files[names::ZPN40_BTAGDN] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_"+ZPNFileDate+"_bTag_dn_pt"+pt+".root";

    files[names::ZPN10_PDFUP] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN12p5_PDFUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_up_pt"+pt+".root"; 
    files[names::ZPN15_PDFUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_up_pt"+pt+".root";   
    files[names::ZPN20_PDFUP] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN25_PDFUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_up_pt"+pt+".root";   
    files[names::ZPN30_PDFUP] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN35_PDFUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_up_pt"+pt+".root";  
    files[names::ZPN40_PDFUP] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN10_PDFDN] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_dn_pt"+pt+".root";
    files[names::ZPN12p5_PDFDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_dn_pt"+pt+".root"; 
    files[names::ZPN15_PDFDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_dn_pt"+pt+".root";    
    files[names::ZPN20_PDFDN] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_dn_pt"+pt+".root";
    files[names::ZPN25_PDFDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_dn_pt"+pt+".root";    
    files[names::ZPN30_PDFDN] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_dn_pt"+pt+".root";
    files[names::ZPN35_PDFDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_dn_pt"+pt+".root"    
    files[names::ZPN40_PDFDN] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_"+ZPNFileDate+"_pdf_dn_pt"+pt+".root";
    
    files[names::ZPN10_PUUP]  = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN12p5_PUUP]  = files[names::ZPN10];
    files[names::ZPN15_PUUP]  = files[names::ZPN10];
    files[names::ZPN20_PUUP]  = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN25_PUUP]  = files[names::ZPN10];
    files[names::ZPN30_PUUP]  = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN35_PUUP]  = files[names::ZPN10];
    files[names::ZPN40_PUUP]  = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN10_PUDN]  = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
    files[names::ZPN12p5_PUDN]  = files[names::ZPN10];
    files[names::ZPN15_PUDN]  = files[names::ZPN10];
    files[names::ZPN20_PUDN]  = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
    files[names::ZPN25_PUDN]  = files[names::ZPN10];
    files[names::ZPN30_PUDN]  = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
    files[names::ZPN35_PUDN]  = files[names::ZPN10]; 
    files[names::ZPN40_PUDN]  = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
  }//ZPXW, signal = 2
  else if (signal == 3){//RSG                                                                                                                
    files[names::ZPN10]         = dir +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_"+histFileDate+"_nom_pt"+pt+".root";
    files[names::ZPN12p5]       = dir +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_"+histFileDate+"_nom_pt"+pt+".root";
    files[names::ZPN15]         = dir +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_"+histFileDate+"_nom_pt"+pt+".root";
    files[names::ZPN20]         = dir +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_"+histFileDate+"_nom_pt"+pt+".root";
    files[names::ZPN25]         = dir +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_"+histFileDate+"_nom_pt"+pt+".root";
    files[names::ZPN30]         = dir +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_"+histFileDate+"_nom_pt"+pt+".root";
    files[names::ZPN35]         = dir +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_"+histFileDate+"_nom_pt"+pt+".root";
    files[names::ZPN40]         = dir +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_"+histFileDate+"_nom_pt"+pt+".root";

    files[names::ZPN10_SCALEUP] = dir +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_"+histFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN12p5_SCALEUP] = dir +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_"+histFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN15_SCALEUP] = dir +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_"+histFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN20_SCALEUP] = dir +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_"+histFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN25_SCALEUP] = dir +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_"+histFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN30_SCALEUP] = dir +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_"+histFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN35_SCALEUP] = dir +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_"+histFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN40_SCALEUP] = dir +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_"+histFileDate+"_jec_up_pt"+pt+".root";
    files[names::ZPN10_SCALEDN] = dir +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_"+histFileDate+"_jec_dn_pt"+pt+".root";
    files[names::ZPN12p5_SCALEDN] = dir +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_"+histFileDate+"_jec_dn_pt"+pt+".root";
    files[names::ZPN15_SCALEDN] = dir +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_"+histFileDate+"_jec_dn_pt"+pt+".root";
    files[names::ZPN20_SCALEDN] = dir +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_"+histFileDate+"_jec_dn_pt"+pt+".root";
    files[names::ZPN25_SCALEDN] = dir +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_"+histFileDate+"_jec_dn_pt"+pt+".root";
    files[names::ZPN30_SCALEDN] = dir +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_"+histFileDate+"_jec_dn_pt"+pt+".root";
    files[names::ZPN35_SCALEDN] = dir +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_"+histFileDate+"_jec_dn_pt"+pt+".root";
    files[names::ZPN40_SCALEDN] = dir +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_"+histFileDate+"_jec_dn_pt"+pt+".root";

    files[names::ZPN10_JERUP]   = dir +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_"+histFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN12p5_JERUP]   = dir +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_"+histFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN15_JERUP]   = dir +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_"+histFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN20_JERUP]   = dir +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_"+histFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN25_JERUP]   = dir +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_"+histFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN30_JERUP]   = dir +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_"+histFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN35_JERUP]   = dir +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_"+histFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN40_JERUP]   = dir +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_"+histFileDate+"_jer_up_pt"+pt+".root";
    files[names::ZPN10_JERDN]   = dir +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_"+histFileDate+"_jer_dn_pt"+pt+".root";
    files[names::ZPN12p5_JERDN]   = dir +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_"+histFileDate+"_jer_dn_pt"+pt+".root";
    files[names::ZPN15_JERDN]   = dir +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_"+histFileDate+"_jer_dn_pt"+pt+".root";
    files[names::ZPN20_JERDN]   = dir +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_"+histFileDate+"_jer_dn_pt"+pt+".root";
    files[names::ZPN25_JERDN]   = dir +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_"+histFileDate+"_jer_dn_pt"+pt+".root";
    files[names::ZPN30_JERDN]   = dir +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_"+histFileDate+"_jer_dn_pt"+pt+".root";
    files[names::ZPN35_JERDN]   = dir +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_"+histFileDate+"_jer_dn_pt"+pt+".root";
    files[names::ZPN40_JERDN]   = dir +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_"+histFileDate+"_jer_dn_pt"+pt+".root";

    files[names::ZPN10_PDFUP]   = dir+  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_"+histFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN12p5_PDFUP]   = dir+  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_"+histFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN15_PDFUP]   = dir+  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_"+histFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN20_PDFUP]   = dir+  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_"+histFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN25_PDFUP]   = dir+  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_"+histFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN30_PDFUP]   = dir+  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_"+histFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN35_PDFUP]   = dir+  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_"+histFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN40_PDFUP]   = dir +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_"+histFileDate+"_pdf_up_pt"+pt+".root";
    files[names::ZPN10_PDFDN]   = dir+  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_"+histFileDate+"_pdf_dn_pt"+pt+".root";
    files[names::ZPN12p5_PDFDN]   = dir+  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_"+histFileDate+"_pdf_dn_pt"+pt+".root";
    files[names::ZPN15_PDFDN]   = dir+  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_"+histFileDate+"_pdf_dn_pt"+pt+".root";
    files[names::ZPN20_PDFDN]   = dir+  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_"+histFileDate+"_pdf_dn_pt"+pt+".root";
    files[names::ZPN25_PDFDN]   = dir+  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_"+histFileDate+"_pdf_dn_pt"+pt+".root";
    files[names::ZPN30_PDFDN]   = dir+  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_"+histFileDate+"_pdf_dn_pt"+pt+".root";
    files[names::ZPN35_PDFDN]   = dir+  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_"+histFileDate+"_pdf_dn_pt"+pt+".root";
    files[names::ZPN40_PDFDN]   = dir +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_"+histFileDate+"_pdf_dn_pt"+pt+".root";

    files[names::ZPN10_BTAGUP]  = dir +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_"+histFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN12p5_BTAGUP]  = dir +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_"+histFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN15_BTAGUP]  = dir +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_"+histFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN20_BTAGUP]  = dir +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_"+histFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN25_BTAGUP]  = dir +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_"+histFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN30_BTAGUP]  = dir +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_"+histFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN35_BTAGUP]  = dir +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_"+histFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN40_BTAGUP]  = dir +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_"+histFileDate+"_bTag_up_pt"+pt+".root";
    files[names::ZPN10_BTAGDN]  = dir +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_"+histFileDate+"_bTag_dn_pt"+pt+".root";
    files[names::ZPN12p5_BTAGDN]  = dir +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_"+histFileDate+"_bTag_dn_pt"+pt+".root";
    files[names::ZPN15_BTAGDN]  = dir +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_"+histFileDate+"_bTag_dn_pt"+pt+".root";
    files[names::ZPN20_BTAGDN]  = dir +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_"+histFileDate+"_bTag_dn_pt"+pt+".root";
    files[names::ZPN25_BTAGDN]  = dir +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_"+histFileDate+"_bTag_dn_pt"+pt+".root";
    files[names::ZPN30_BTAGDN]  = dir +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_"+histFileDate+"_bTag_dn_pt"+pt+".root";
    files[names::ZPN35_BTAGDN]  = dir +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_"+histFileDate+"_bTag_dn_pt"+pt+".root";
    files[names::ZPN40_BTAGDN]  = dir +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_"+histFileDate+"_bTag_dn_pt"+pt+".root";
    


    files[names::ZPN10_PUUP]  = dir +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_"+histFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN12p5_PUUP]  = dir +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_"+histFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN15_PUUP]  = dir +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_"+histFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN20_PUUP]  = dir +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_"+histFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN25_PUUP]  = dir +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_"+histFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN30_PUUP]  = dir +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_"+histFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN35_PUUP]  = dir +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_"+histFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN40_PUUP]  = dir +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_"+histFileDate+"_PU_up_pt"+pt+".root";
    files[names::ZPN10_PUDN]  = dir +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_"+histFileDate+"_PU_dn_pt"+pt+".root";
    files[names::ZPN12p5_PUDN]  = dir +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_"+histFileDate+"_PU_dn_pt"+pt+".root";
    files[names::ZPN15_PUDN]  = dir +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_"+histFileDate+"_PU_dn_pt"+pt+".root";
    files[names::ZPN20_PUDN]  = dir +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_"+histFileDate+"_PU_dn_pt"+pt+".root";
    files[names::ZPN25_PUDN]  = dir +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_"+histFileDate+"_PU_dn_pt"+pt+".root";
    files[names::ZPN30_PUDN]  = dir +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_"+histFileDate+"_PU_dn_pt"+pt+".root";
    files[names::ZPN35_PUDN]  = dir +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_"+histFileDate+"_PU_dn_pt"+pt+".root";
    files[names::ZPN40_PUDN]  = dir +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_"+histFileDate+"_PU_dn_pt"+pt+".root";

//    files[names::ZPN10_PUUP]  = dir +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
//    files[names::ZPN12p5_PUUP]  = dir +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
//    files[names::ZPN15_PUUP]  = dir +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
//    files[names::ZPN20_PUUP]  = dir +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
//    files[names::ZPN25_PUUP]  = dir +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
//    files[names::ZPN30_PUUP]  = dir +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
//    files[names::ZPN35_PUUP]  = dir +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_up_pt"+pt+".root";
//    files[names::ZPN40_PUUP]  = dir +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_041216_PU_up_pt"+pt+".root";
//    files[names::ZPN10_PUDN]  = dir +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
//    files[names::ZPN12p5_PUDN]  = dir +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
//    files[names::ZPN15_PUDN]  = dir +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
//    files[names::ZPN20_PUDN]  = dir +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
//    files[names::ZPN25_PUDN]  = dir +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
//    files[names::ZPN30_PUDN]  = dir +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
//    files[names::ZPN35_PUDN]  = dir +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_"+ZPNFileDate+"_PU_dn_pt"+pt+".root";
//    files[names::ZPN40_PUDN]  = dir +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_041216_PU_dn_pt"+pt+".root";
    }//RSG, signal = 3 */

  int rebin_factor = 50;

  for (int proc = 0; proc < names::NUM_PROCS; proc++) {


    cout << "Processing " << labels[proc] << endl;

    TFile *infile = new TFile(files[proc], "READ");

    if (proc == names::QCD or proc == names::TT_SUBTRACT or proc == names::QCDMC_SYST){
      
      histos[proc][0] = (TH1F *) infile->Get("mttPredDist2_modMass_tagMassSDTau32_dRapLo_0btag_pred");
      histos[proc][1] = (TH1F *) infile->Get("mttPredDist2_modMass_tagMassSDTau32_dRapLo_1btag_pred");
      histos[proc][2] = (TH1F *) infile->Get("mttPredDist2_modMass_tagMassSDTau32_dRapLo_2btag_pred");
      histos[proc][3] = (TH1F *) infile->Get("mttPredDist2_modMass_tagMassSDTau32_dRapHi_0btag_pred");
      histos[proc][4] = (TH1F *) infile->Get("mttPredDist2_modMass_tagMassSDTau32_dRapHi_1btag_pred");
      histos[proc][5] = (TH1F *) infile->Get("mttPredDist2_modMass_tagMassSDTau32_dRapHi_2btag_pred");
      histos[proc][6] = (TH1F *) infile->Get("mttPredDist2_modMass_tagMassSDTau32_dRapIn_inclusive_pred");
    }

    else if (proc == names::QCD_SYST or proc == names::TT_SUBTRACTSYST){
      
      histos[proc][0] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_0btag_pred");
      histos[proc][1] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_1btag_pred");
      histos[proc][2] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_2btag_pred");
      histos[proc][3] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_0btag_pred");
      histos[proc][4] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_1btag_pred");
      histos[proc][5] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_2btag_pred");
      histos[proc][6] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_inclusive_pred");
    }

    else if (proc == names::TT_PSHUP or proc == names::TT_PSHDN){
      histos[proc][0] = (TH1F *) infile->Get("h_mttMass_tagMassSDTau32_dRapLo_0btag");
      histos[proc][1] = (TH1F *) infile->Get("h_mttMass_tagMassSDTau32_dRapLo_1btag");
      histos[proc][2] = (TH1F *) infile->Get("h_mttMass_tagMassSDTau32_dRapLo_2btag");
      histos[proc][3] = (TH1F *) infile->Get("h_mttMass_tagMassSDTau32_dRapHi_0btag");
      histos[proc][4] = (TH1F *) infile->Get("h_mttMass_tagMassSDTau32_dRapHi_1btag");
      histos[proc][5] = (TH1F *) infile->Get("h_mttMass_tagMassSDTau32_dRapHi_2btag");
      histos[proc][6] = (TH1F *) infile->Get("h_mttMass_tagMassSDTau32_dRapLo_inclusive");
      TH1F* histHI = new TH1F();
      histHI = (TH1F *) infile->Get("h_mttMass_tagMassSDTau32_dRapHi_inclusive");
      histos[proc][6]->Add(histHI);
    }

    else {
    
      histos[proc][0] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_0btag");
      histos[proc][1] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_1btag");
      histos[proc][2] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_2btag");
      histos[proc][3] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_0btag");
      histos[proc][4] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_1btag");
      histos[proc][5] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_2btag");
      histos[proc][6] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_inclusive");
    }

    cout << histos[proc][0]->Integral() << endl;
    cout << histos[proc][0]->GetNbinsX() << endl;

    if (proc == names::QCDMC or proc == names::QCDMC_SYST){

      histos[proc][0]->Rebin(rebin_factor);
      histos[proc][1]->Rebin(rebin_factor);
      histos[proc][2]->Rebin(rebin_factor);
      histos[proc][3]->Rebin(rebin_factor);
      histos[proc][4]->Rebin(rebin_factor);
      histos[proc][5]->Rebin(rebin_factor);
      histos[proc][6]->Rebin(rebin_factor);
    }
    else{

      histos[proc][0]->Rebin(10);
      histos[proc][1]->Rebin(10);
      histos[proc][2]->Rebin(10);
      histos[proc][3]->Rebin(10);
      histos[proc][4]->Rebin(10);
      histos[proc][5]->Rebin(10);
      histos[proc][6]->Rebin(10);

    }
    cout << histos[proc][0]->GetNbinsX() << endl;
  
  }

  for (int h = 0; h < names::NUM_PROCS; h++){
    if (h == names::DATA){
      histos[h][0]->Sumw2(kFALSE);
      histos[h][1]->Sumw2(kFALSE);
      histos[h][2]->Sumw2(kFALSE);
      histos[h][3]->Sumw2(kFALSE);
      histos[h][4]->Sumw2(kFALSE);
      histos[h][5]->Sumw2(kFALSE);
      histos[h][6]->Sumw2(kFALSE);
    }
    else{
      histos[h][0]->Sumw2();
      histos[h][1]->Sumw2();
      histos[h][2]->Sumw2();
      histos[h][3]->Sumw2();
      histos[h][4]->Sumw2();
      histos[h][5]->Sumw2();
      histos[h][6]->Sumw2();
      }
  }

  float lumi = 2592.3;
  float nttbar = 96834559.;//19665194.;

  float kfactor = 1.0;
  float ttSF = 1.0;
  
  if (!pt500){
    kfactor = 0.94;
    ttSF = 0.89*0.89;
  }

  cout << kfactor << " " << ttSF << endl;


  for (int tag = 0; tag < nTagCats; tag++){
    cout<<"start of loop"<<endl;
    histos[names::QCD][tag]->SetMarkerSize(0);
    histos[names::TT_SCALEUP][tag] ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT_SCALEDN][tag] ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT_JERUP][tag]   ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT_JERDN][tag]   ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT_PDFUP][tag]   ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT_PDFDN][tag]   ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT_PSHUP][tag]   ->Scale( 831.76 * ttSF * lumi * kfactor / 9921174. );
    histos[names::TT_PSHDN][tag]   ->Scale( 831.76 * ttSF * lumi * kfactor / 9860774. );
    histos[names::TT_Q2UP][tag]    ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT_Q2DN][tag]    ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT_BTAGUP][tag]  ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT_BTAGDN][tag]  ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT_PUUP][tag]  ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT_PUDN][tag]  ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT][tag]         ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT_SUBTRACT][tag]->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT_SUBTRACTSYST][tag]->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    if (signal == 0){//ZPN
      histos[names::ZPN10][tag]->Scale( 1. * ttSF * lumi / 122204. ); 
      histos[names::ZPN12p5][tag]->Scale( 1. * ttSF * lumi / 114611. ); 
      histos[names::ZPN15][tag]->Scale( 1. * ttSF * lumi / 108916. ); 
      histos[names::ZPN20][tag]->Scale( 1. * ttSF * lumi / 202573. ); 
      histos[names::ZPN25][tag]->Scale( 1. * ttSF * lumi / 118319. ); 
      histos[names::ZPN30][tag]->Scale( 1. * ttSF * lumi / 117069. ); 
      histos[names::ZPN35][tag]->Scale( 1. * ttSF * lumi / 113527. );
      histos[names::ZPN40][tag]->Scale( 1. * ttSF * lumi / 111625. );
      histos[names::ZPN10_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 122204. ); 
      histos[names::ZPN12p5_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 114611. ); 
      histos[names::ZPN15_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 108916. ); 
      histos[names::ZPN20_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 202573. ); 
      histos[names::ZPN25_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 118319. ); 
      histos[names::ZPN30_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 117069. ); 
      histos[names::ZPN35_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 113527. );
      histos[names::ZPN40_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 111625. );
      histos[names::ZPN10_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 122204. ); 
      histos[names::ZPN12p5_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 114611. ); 
      histos[names::ZPN15_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 108916. ); 
      histos[names::ZPN20_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 202573. ); 
      histos[names::ZPN25_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 118319. ); 
      histos[names::ZPN30_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 117069. ); 
      histos[names::ZPN35_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 113527. );
      histos[names::ZPN40_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 111625. );
      histos[names::ZPN10_JERUP][tag]  ->Scale( 1. * ttSF * lumi / 122204. ); 
      histos[names::ZPN12p5_JERUP][tag]  ->Scale( 1. * ttSF * lumi / 114611. ); 
      histos[names::ZPN15_JERUP][tag]  ->Scale( 1. * ttSF * lumi / 108916. ); 
      histos[names::ZPN20_JERUP][tag]  ->Scale( 1. * ttSF * lumi / 202573. ); 
      histos[names::ZPN25_JERUP][tag]  ->Scale( 1. * ttSF * lumi / 118319. ); 
      histos[names::ZPN30_JERUP][tag]  ->Scale( 1. * ttSF * lumi / 117069. ); 
      histos[names::ZPN35_JERUP][tag]  ->Scale( 1. * ttSF * lumi / 113527. );
      histos[names::ZPN40_JERUP][tag]  ->Scale( 1. * ttSF * lumi / 111625. );
      histos[names::ZPN10_JERDN][tag]  ->Scale( 1. * ttSF * lumi / 122204. ); 
      histos[names::ZPN12p5_JERDN][tag]  ->Scale( 1. * ttSF * lumi / 114611. ); 
      histos[names::ZPN15_JERDN][tag]  ->Scale( 1. * ttSF * lumi / 108916. ); 
      histos[names::ZPN20_JERDN][tag]  ->Scale( 1. * ttSF * lumi / 202573. ); 
      histos[names::ZPN25_JERDN][tag]  ->Scale( 1. * ttSF * lumi / 118319. ); 
      histos[names::ZPN30_JERDN][tag]  ->Scale( 1. * ttSF * lumi / 117069. ); 
      histos[names::ZPN35_JERDN][tag]  ->Scale( 1. * ttSF * lumi / 113527. );
      histos[names::ZPN40_JERDN][tag]  ->Scale( 1. * ttSF * lumi / 111625. );
      histos[names::ZPN10_PDFUP][tag]  ->Scale( 1. * ttSF * lumi / 122204. ); 
      histos[names::ZPN12p5_PDFUP][tag]  ->Scale( 1. * ttSF * lumi / 114611. ); 
      histos[names::ZPN15_PDFUP][tag]  ->Scale( 1. * ttSF * lumi / 108916. ); 
      histos[names::ZPN20_PDFUP][tag]  ->Scale( 1. * ttSF * lumi / 202573. ); 
      histos[names::ZPN25_PDFUP][tag]  ->Scale( 1. * ttSF * lumi / 118319. ); 
      histos[names::ZPN30_PDFUP][tag]  ->Scale( 1. * ttSF * lumi / 117069. ); 
      histos[names::ZPN35_PDFUP][tag]  ->Scale( 1. * ttSF * lumi / 113527. );
      histos[names::ZPN40_PDFUP][tag]  ->Scale( 1. * ttSF * lumi / 111625. );
      histos[names::ZPN10_PDFDN][tag]  ->Scale( 1. * ttSF * lumi / 122204. ); 
      histos[names::ZPN12p5_PDFDN][tag]  ->Scale( 1. * ttSF * lumi / 114611. ); 
      histos[names::ZPN15_PDFDN][tag]  ->Scale( 1. * ttSF * lumi / 108916. ); 
      histos[names::ZPN20_PDFDN][tag]  ->Scale( 1. * ttSF * lumi / 202573. ); 
      histos[names::ZPN25_PDFDN][tag]  ->Scale( 1. * ttSF * lumi / 118319. ); 
      histos[names::ZPN30_PDFDN][tag]  ->Scale( 1. * ttSF * lumi / 117069. ); 
      histos[names::ZPN35_PDFDN][tag]  ->Scale( 1. * ttSF * lumi / 113527. );
      histos[names::ZPN40_PDFDN][tag]  ->Scale( 1. * ttSF * lumi / 111625. );
      histos[names::ZPN10_BTAGUP][tag] ->Scale( 1. * ttSF * lumi / 122204. ); 
      histos[names::ZPN12p5_BTAGUP][tag] ->Scale( 1. * ttSF * lumi / 114611. ); 
      histos[names::ZPN15_BTAGUP][tag] ->Scale( 1. * ttSF * lumi / 108916. ); 
      histos[names::ZPN20_BTAGUP][tag] ->Scale( 1. * ttSF * lumi / 202573. ); 
      histos[names::ZPN25_BTAGUP][tag] ->Scale( 1. * ttSF * lumi / 118319. ); 
      histos[names::ZPN30_BTAGUP][tag] ->Scale( 1. * ttSF * lumi / 117069. ); 
      histos[names::ZPN35_BTAGUP][tag] ->Scale( 1. * ttSF * lumi / 113527. );
      histos[names::ZPN40_BTAGUP][tag] ->Scale( 1. * ttSF * lumi / 111625. );
      histos[names::ZPN10_BTAGDN][tag] ->Scale( 1. * ttSF * lumi / 122204. ); 
      histos[names::ZPN12p5_BTAGDN][tag] ->Scale( 1. * ttSF * lumi / 114611. ); 
      histos[names::ZPN15_BTAGDN][tag] ->Scale( 1. * ttSF * lumi / 108916. ); 
      histos[names::ZPN20_BTAGDN][tag] ->Scale( 1. * ttSF * lumi / 202573. ); 
      histos[names::ZPN25_BTAGDN][tag] ->Scale( 1. * ttSF * lumi / 118319. ); 
      histos[names::ZPN30_BTAGDN][tag] ->Scale( 1. * ttSF * lumi / 117069. ); 
      histos[names::ZPN35_BTAGDN][tag] ->Scale( 1. * ttSF * lumi / 113527. );
      histos[names::ZPN40_BTAGDN][tag] ->Scale( 1. * ttSF * lumi / 111625. );
      histos[names::ZPN10_PUUP][tag] ->Scale( 1. * ttSF * lumi / 122204. ); 
      histos[names::ZPN12p5_PUUP][tag] ->Scale( 1. * ttSF * lumi / 114611. ); 
      histos[names::ZPN15_PUUP][tag] ->Scale( 1. * ttSF * lumi / 108916. ); 
      histos[names::ZPN20_PUUP][tag] ->Scale( 1. * ttSF * lumi / 202573. ); 
      histos[names::ZPN25_PUUP][tag] ->Scale( 1. * ttSF * lumi / 118319. ); 
      histos[names::ZPN30_PUUP][tag] ->Scale( 1. * ttSF * lumi / 117069. ); 
      histos[names::ZPN35_PUUP][tag] ->Scale( 1. * ttSF * lumi / 113527. );
      histos[names::ZPN40_PUUP][tag] ->Scale( 1. * ttSF * lumi / 111625. );
      histos[names::ZPN10_PUDN][tag] ->Scale( 1. * ttSF * lumi / 122204. ); 
      histos[names::ZPN12p5_PUDN][tag] ->Scale( 1. * ttSF * lumi / 114611. ); 
      histos[names::ZPN15_PUDN][tag] ->Scale( 1. * ttSF * lumi / 108916. ); 
      histos[names::ZPN20_PUDN][tag] ->Scale( 1. * ttSF * lumi / 202573. ); 
      histos[names::ZPN25_PUDN][tag] ->Scale( 1. * ttSF * lumi / 118319. ); 
      histos[names::ZPN30_PUDN][tag] ->Scale( 1. * ttSF * lumi / 117069. ); 
      histos[names::ZPN35_PUDN][tag] ->Scale( 1. * ttSF * lumi / 113527. );
      histos[names::ZPN40_PUDN][tag] ->Scale( 1. * ttSF * lumi / 111625. );
    }//ZPN, signal = 0                                                                                                                       
    else if (signal == 1){//ZPW                                                                                                              
      histos[names::ZPN10][tag]->Scale( 1. * ttSF * lumi / 124293. );
      histos[names::ZPN12p5][tag]->Scale( 1. * ttSF * lumi / 114786. );
      histos[names::ZPN15][tag]->Scale( 1. * ttSF * lumi / 110747. );
      histos[names::ZPN20][tag]->Scale( 1. * ttSF * lumi / 103854. );
      histos[names::ZPN25][tag]->Scale( 1. * ttSF * lumi / 118093. );
      histos[names::ZPN30][tag]->Scale( 1. * ttSF * lumi / 246767. );
      histos[names::ZPN35][tag]->Scale( 1. * ttSF * lumi / 126158. );
      histos[names::ZPN40][tag]->Scale( 1. * ttSF * lumi / 126264. );
      histos[names::ZPN10_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 124293. );
      histos[names::ZPN12p5_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 114786. );
      histos[names::ZPN15_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 110747. );
      histos[names::ZPN20_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 103854. );
      histos[names::ZPN25_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 118093. );
      histos[names::ZPN30_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 246767. );
      histos[names::ZPN35_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 126158. );
      histos[names::ZPN40_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 126264. );
      histos[names::ZPN10_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 124293. );
      histos[names::ZPN12p5_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 114786. );
      histos[names::ZPN15_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 110747. );
      histos[names::ZPN20_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 103854. );
      histos[names::ZPN25_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 118093. );
      histos[names::ZPN30_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 246767. );
      histos[names::ZPN35_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 126158. );
      histos[names::ZPN40_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 126264. );
      histos[names::ZPN10_JERUP][tag]->Scale( 1. * ttSF * lumi / 124293. );
      histos[names::ZPN12p5_JERUP][tag]->Scale( 1. * ttSF * lumi / 114786. );
      histos[names::ZPN15_JERUP][tag]->Scale( 1. * ttSF * lumi / 110747. );
      histos[names::ZPN20_JERUP][tag]->Scale( 1. * ttSF * lumi / 103854. );
      histos[names::ZPN25_JERUP][tag]->Scale( 1. * ttSF * lumi / 118093. );
      histos[names::ZPN30_JERUP][tag]->Scale( 1. * ttSF * lumi / 246767. );
      histos[names::ZPN35_JERUP][tag]->Scale( 1. * ttSF * lumi / 126158. );
      histos[names::ZPN40_JERUP][tag]->Scale( 1. * ttSF * lumi / 126264. );
      histos[names::ZPN10_JERDN][tag]->Scale( 1. * ttSF * lumi / 124293. );
      histos[names::ZPN12p5_JERDN][tag]->Scale( 1. * ttSF * lumi / 114786. );
      histos[names::ZPN15_JERDN][tag]->Scale( 1. * ttSF * lumi / 110747. );
      histos[names::ZPN20_JERDN][tag]->Scale( 1. * ttSF * lumi / 103854. );
      histos[names::ZPN25_JERDN][tag]->Scale( 1. * ttSF * lumi / 118093. );
      histos[names::ZPN30_JERDN][tag]->Scale( 1. * ttSF * lumi / 246767. );
      histos[names::ZPN35_JERDN][tag]->Scale( 1. * ttSF * lumi / 126158. );
      histos[names::ZPN40_JERDN][tag]->Scale( 1. * ttSF * lumi / 126264. );
      histos[names::ZPN10_BTAGUP][tag]->Scale( 1. * ttSF * lumi / 124293. );
      histos[names::ZPN12p5_BTAGUP][tag]->Scale( 1. * ttSF * lumi / 114786. );
      histos[names::ZPN15_BTAGUP][tag]->Scale( 1. * ttSF * lumi / 110747. );
      histos[names::ZPN20_BTAGUP][tag]->Scale( 1. * ttSF * lumi / 103854. );
      histos[names::ZPN25_BTAGUP][tag]->Scale( 1. * ttSF * lumi / 118093. );
      histos[names::ZPN30_BTAGUP][tag]->Scale( 1. * ttSF * lumi / 246767. );
      histos[names::ZPN35_BTAGUP][tag]->Scale( 1. * ttSF * lumi / 126158. );
      histos[names::ZPN40_BTAGUP][tag]->Scale( 1. * ttSF * lumi / 126264. );
      histos[names::ZPN10_BTAGDN][tag]->Scale( 1. * ttSF * lumi / 124293. );
      histos[names::ZPN12p5_BTAGDN][tag]->Scale( 1. * ttSF * lumi / 114786. );
      histos[names::ZPN15_BTAGDN][tag]->Scale( 1. * ttSF * lumi / 110747. );
      histos[names::ZPN20_BTAGDN][tag]->Scale( 1. * ttSF * lumi / 103854. );
      histos[names::ZPN25_BTAGDN][tag]->Scale( 1. * ttSF * lumi / 118093. );
      histos[names::ZPN30_BTAGDN][tag]->Scale( 1. * ttSF * lumi / 246767. );
      histos[names::ZPN35_BTAGDN][tag]->Scale( 1. * ttSF * lumi / 126158. );
      histos[names::ZPN40_BTAGDN][tag]->Scale( 1. * ttSF * lumi / 126264. );
      histos[names::ZPN10_PDFUP][tag]->Scale( 1. * ttSF * lumi / 124293. );
      histos[names::ZPN12p5_PDFUP][tag]->Scale( 1. * ttSF * lumi / 114786. );
      histos[names::ZPN15_PDFUP][tag]->Scale( 1. * ttSF * lumi / 110747. );
      histos[names::ZPN20_PDFUP][tag]->Scale( 1. * ttSF * lumi / 103854. );
      histos[names::ZPN25_PDFUP][tag]->Scale( 1. * ttSF * lumi / 118093. );
      histos[names::ZPN30_PDFUP][tag]->Scale( 1. * ttSF * lumi / 246767. );
      histos[names::ZPN35_PDFUP][tag]->Scale( 1. * ttSF * lumi / 126158. );
      histos[names::ZPN40_PDFUP][tag]->Scale( 1. * ttSF * lumi / 126264. );
      histos[names::ZPN10_PDFDN][tag]->Scale( 1. * ttSF * lumi / 124293. );
      histos[names::ZPN12p5_PDFDN][tag]->Scale( 1. * ttSF * lumi / 114786. );
      histos[names::ZPN15_PDFDN][tag]->Scale( 1. * ttSF * lumi / 110747. );
      histos[names::ZPN20_PDFDN][tag]->Scale( 1. * ttSF * lumi / 103854. );
      histos[names::ZPN25_PDFDN][tag]->Scale( 1. * ttSF * lumi / 118093. );
      histos[names::ZPN30_PDFDN][tag]->Scale( 1. * ttSF * lumi / 246767. );
      histos[names::ZPN35_PDFDN][tag]->Scale( 1. * ttSF * lumi / 126158. );
      histos[names::ZPN40_PDFDN][tag]->Scale( 1. * ttSF * lumi / 126264. );
      histos[names::ZPN10_PUUP][tag]->Scale( 1. * ttSF * lumi / 124293. );
      histos[names::ZPN12p5_PUUP][tag]->Scale( 1. * ttSF * lumi / 114786. );
      histos[names::ZPN15_PUUP][tag]->Scale( 1. * ttSF * lumi / 110747. );
      histos[names::ZPN20_PUUP][tag]->Scale( 1. * ttSF * lumi / 103854. );
      histos[names::ZPN25_PUUP][tag]->Scale( 1. * ttSF * lumi / 118093. );
      histos[names::ZPN30_PUUP][tag]->Scale( 1. * ttSF * lumi / 246767. );
      histos[names::ZPN35_PUUP][tag]->Scale( 1. * ttSF * lumi / 126158. );
      histos[names::ZPN40_PUUP][tag]->Scale( 1. * ttSF * lumi / 126264. );
      histos[names::ZPN10_PUDN][tag]->Scale( 1. * ttSF * lumi / 124293. );
      histos[names::ZPN12p5_PUDN][tag]->Scale( 1. * ttSF * lumi / 114786. );
      histos[names::ZPN15_PUDN][tag]->Scale( 1. * ttSF * lumi / 110747. );
      histos[names::ZPN20_PUDN][tag]->Scale( 1. * ttSF * lumi / 103854. );
      histos[names::ZPN25_PUDN][tag]->Scale( 1. * ttSF * lumi / 118093. );
      histos[names::ZPN30_PUDN][tag]->Scale( 1. * ttSF * lumi / 246767. );
      histos[names::ZPN35_PUDN][tag]->Scale( 1. * ttSF * lumi / 126158. );
      histos[names::ZPN40_PUDN][tag]->Scale( 1. * ttSF * lumi / 126264. );
    }//ZPW, signal = 1                                                                                                                       
    else if (signal == 2){//ZPXW                                                                                                             
      histos[names::ZPN10][tag]->Scale( 1. * ttSF * lumi / 125837. );
      histos[names::ZPN15][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN20][tag]->Scale( 1. * ttSF * lumi / 136191. );
      histos[names::ZPN25][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN30][tag]->Scale( 1. * ttSF * lumi / 106338. );
      histos[names::ZPN35][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN40][tag]->Scale( 1. * ttSF * lumi / 107643. );
      histos[names::ZPN10_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 125837. );
      histos[names::ZPN15_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN20_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 136191. );
      histos[names::ZPN25_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN30_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 106338. );
      histos[names::ZPN35_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN40_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 107643. );
      histos[names::ZPN10_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 125837. );
      histos[names::ZPN15_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN20_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 136191. );
      histos[names::ZPN25_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN30_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 106338. );
      histos[names::ZPN35_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN40_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 107643. );
      histos[names::ZPN10_JERUP][tag]->Scale( 1. * ttSF * lumi / 125837. );
      histos[names::ZPN15_JERUP][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN20_JERUP][tag]->Scale( 1. * ttSF * lumi / 136191. );
      histos[names::ZPN25_JERUP][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN30_JERUP][tag]->Scale( 1. * ttSF * lumi / 106338. );
      histos[names::ZPN35_JERUP][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN40_JERUP][tag]->Scale( 1. * ttSF * lumi / 107643. );
      histos[names::ZPN10_JERDN][tag]->Scale( 1. * ttSF * lumi / 125837. );
      histos[names::ZPN15_JERDN][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN20_JERDN][tag]->Scale( 1. * ttSF * lumi / 136191. );
      histos[names::ZPN25_JERDN][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN30_JERDN][tag]->Scale( 1. * ttSF * lumi / 106338. );
      histos[names::ZPN35_JERDN][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN40_JERDN][tag]->Scale( 1. * ttSF * lumi / 107643. );
      histos[names::ZPN10_BTAGUP][tag]->Scale( 1. * ttSF * lumi / 125837. );
      histos[names::ZPN15_BTAGUP][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN20_BTAGUP][tag]->Scale( 1. * ttSF * lumi / 136191. );
      histos[names::ZPN25_BTAGUP][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN30_BTAGUP][tag]->Scale( 1. * ttSF * lumi / 106338. );
      histos[names::ZPN35_BTAGUP][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN40_BTAGUP][tag]->Scale( 1. * ttSF * lumi / 107643. );
      histos[names::ZPN10_BTAGDN][tag]->Scale( 1. * ttSF * lumi / 125837. );
      histos[names::ZPN15_BTAGDN][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN20_BTAGDN][tag]->Scale( 1. * ttSF * lumi / 136191. );
      histos[names::ZPN25_BTAGDN][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN30_BTAGDN][tag]->Scale( 1. * ttSF * lumi / 106338. );
      histos[names::ZPN35_BTAGDN][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN40_BTAGDN][tag]->Scale( 1. * ttSF * lumi / 107643. );
      histos[names::ZPN10_PDFUP][tag]->Scale( 1. * ttSF * lumi / 125837. );
      histos[names::ZPN15_PDFUP][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN20_PDFUP][tag]->Scale( 1. * ttSF * lumi / 136191. );
      histos[names::ZPN25_PDFUP][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN30_PDFUP][tag]->Scale( 1. * ttSF * lumi / 106338. );
      histos[names::ZPN35_PDFUP][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN40_PDFUP][tag]->Scale( 1. * ttSF * lumi / 107643. );
      histos[names::ZPN10_PDFDN][tag]->Scale( 1. * ttSF * lumi / 125837. );
      histos[names::ZPN15_PDFDN][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN20_PDFDN][tag]->Scale( 1. * ttSF * lumi / 136191. );
      histos[names::ZPN25_PDFDN][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN30_PDFDN][tag]->Scale( 1. * ttSF * lumi / 106338. );
      histos[names::ZPN35_PDFDN][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN40_PDFDN][tag]->Scale( 1. * ttSF * lumi / 107643. );
      histos[names::ZPN10_PUUP][tag]->Scale( 1. * ttSF * lumi / 125837. );
      histos[names::ZPN15_PUUP][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN20_PUUP][tag]->Scale( 1. * ttSF * lumi / 136191. );
      histos[names::ZPN25_PUUP][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN30_PUUP][tag]->Scale( 1. * ttSF * lumi / 106338. );
      histos[names::ZPN35_PUUP][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN40_PUUP][tag]->Scale( 1. * ttSF * lumi / 107643. );
      histos[names::ZPN10_PUDN][tag]->Scale( 1. * ttSF * lumi / 125837. );
      histos[names::ZPN15_PUDN][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN20_PUDN][tag]->Scale( 1. * ttSF * lumi / 136191. );
      histos[names::ZPN25_PUDN][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN30_PUDN][tag]->Scale( 1. * ttSF * lumi / 106338. );
      histos[names::ZPN35_PUDN][tag]->Scale( 1. * ttSF * lumi / 1. );
      histos[names::ZPN40_PUDN][tag]->Scale( 1. * ttSF * lumi / 107643. );
    }//ZPXW, signal = 2 
    else if (signal == 3){//RSG                                                                                                              
      histos[names::ZPN10][tag]->Scale( 1.  * ttSF * lumi / 98560. );
      histos[names::ZPN12p5][tag]->Scale( 1.  * ttSF * lumi / 95730. );
      histos[names::ZPN15][tag]->Scale( 1.  * ttSF * lumi / 97696. );
      histos[names::ZPN20][tag]->Scale( 1.  * ttSF * lumi / 97600. );
      histos[names::ZPN25][tag]->Scale( 1.  * ttSF * lumi / 99800. );
      histos[names::ZPN30][tag]->Scale( 1.  * ttSF * lumi / 98668. );
      histos[names::ZPN35][tag]->Scale( 1.  * ttSF * lumi / 97104. );
      histos[names::ZPN40][tag]->Scale( 1.  * ttSF * lumi / 99554. );
      histos[names::ZPN10_SCALEUP][tag]->Scale( 1.  * ttSF * lumi / 98560. );
      histos[names::ZPN12p5_SCALEUP][tag]->Scale( 1.  * ttSF * lumi / 95730. );
      histos[names::ZPN15_SCALEUP][tag]->Scale( 1.  * ttSF * lumi / 97696. );
      histos[names::ZPN20_SCALEUP][tag]->Scale( 1.  * ttSF * lumi / 97600. );
      histos[names::ZPN25_SCALEUP][tag]->Scale( 1.  * ttSF * lumi / 99800. );
      histos[names::ZPN30_SCALEUP][tag]->Scale( 1.  * ttSF * lumi / 98668. );
      histos[names::ZPN35_SCALEUP][tag]->Scale( 1.  * ttSF * lumi / 97104. );
      histos[names::ZPN40_SCALEUP][tag]->Scale( 1.  * ttSF * lumi / 99554. );
      histos[names::ZPN10_SCALEDN][tag]->Scale( 1.  * ttSF * lumi / 98560. );
      histos[names::ZPN12p5_SCALEDN][tag]->Scale( 1.  * ttSF * lumi / 95730. );
      histos[names::ZPN15_SCALEDN][tag]->Scale( 1.  * ttSF * lumi / 97696. );
      histos[names::ZPN20_SCALEDN][tag]->Scale( 1.  * ttSF * lumi / 97600. );
      histos[names::ZPN25_SCALEDN][tag]->Scale( 1.  * ttSF * lumi / 99800. );
      histos[names::ZPN30_SCALEDN][tag]->Scale( 1.  * ttSF * lumi / 98668. );
      histos[names::ZPN35_SCALEDN][tag]->Scale( 1.  * ttSF * lumi / 97104. );
      histos[names::ZPN40_SCALEDN][tag]->Scale( 1.  * ttSF * lumi / 99554. );
      histos[names::ZPN10_JERUP][tag]  ->Scale( 1.  * ttSF * lumi / 98560. );
      histos[names::ZPN12p5_JERUP][tag]  ->Scale( 1.  * ttSF * lumi / 95730. );
      histos[names::ZPN15_JERUP][tag]  ->Scale( 1.  * ttSF * lumi / 97696. );
      histos[names::ZPN20_JERUP][tag]  ->Scale( 1.  * ttSF * lumi / 97600. );
      histos[names::ZPN25_JERUP][tag]  ->Scale( 1.  * ttSF * lumi / 99800. );
      histos[names::ZPN30_JERUP][tag]  ->Scale( 1.  * ttSF * lumi / 98668. );
      histos[names::ZPN35_JERUP][tag]  ->Scale( 1.  * ttSF * lumi / 97104. );
      histos[names::ZPN40_JERUP][tag]  ->Scale( 1.  * ttSF * lumi / 99554. );
      histos[names::ZPN10_JERDN][tag]  ->Scale( 1.  * ttSF * lumi / 98560. );
      histos[names::ZPN12p5_JERDN][tag]  ->Scale( 1.  * ttSF * lumi / 95730. );
      histos[names::ZPN15_JERDN][tag]  ->Scale( 1.  * ttSF * lumi / 97696. );
      histos[names::ZPN20_JERDN][tag]  ->Scale( 1.  * ttSF * lumi / 97600. );
      histos[names::ZPN25_JERDN][tag]  ->Scale( 1.  * ttSF * lumi / 99800. );
      histos[names::ZPN30_JERDN][tag]  ->Scale( 1.  * ttSF * lumi / 98668. );
      histos[names::ZPN35_JERDN][tag]  ->Scale( 1.  * ttSF * lumi / 97104. );
      histos[names::ZPN40_JERDN][tag]  ->Scale( 1.  * ttSF * lumi / 99554. );
      histos[names::ZPN10_PDFUP][tag]  ->Scale( 1.  * ttSF * lumi / 98560. );
      histos[names::ZPN12p5_PDFUP][tag]  ->Scale( 1.  * ttSF * lumi / 95730. );
      histos[names::ZPN15_PDFUP][tag]  ->Scale( 1.  * ttSF * lumi / 97696. );
      histos[names::ZPN20_PDFUP][tag]  ->Scale( 1.  * ttSF * lumi / 97600. );
      histos[names::ZPN25_PDFUP][tag]  ->Scale( 1.  * ttSF * lumi / 99800. );
      histos[names::ZPN30_PDFUP][tag]  ->Scale( 1.  * ttSF * lumi / 98668. );
      histos[names::ZPN35_PDFUP][tag]  ->Scale( 1.  * ttSF * lumi / 97104. );
      histos[names::ZPN40_PDFUP][tag]  ->Scale( 1.  * ttSF * lumi / 99554. );
      histos[names::ZPN10_PDFDN][tag]  ->Scale( 1.  * ttSF * lumi / 98560. );
      histos[names::ZPN12p5_PDFDN][tag]  ->Scale( 1.  * ttSF * lumi / 95730. );
      histos[names::ZPN15_PDFDN][tag]  ->Scale( 1.  * ttSF * lumi / 97696. );
      histos[names::ZPN20_PDFDN][tag]  ->Scale( 1.  * ttSF * lumi / 97600. );
      histos[names::ZPN25_PDFDN][tag]  ->Scale( 1.  * ttSF * lumi / 99800. );
      histos[names::ZPN30_PDFDN][tag]  ->Scale( 1.  * ttSF * lumi / 98668. );
      histos[names::ZPN35_PDFDN][tag]  ->Scale( 1.  * ttSF * lumi / 97104. );
      histos[names::ZPN40_PDFDN][tag]  ->Scale( 1.  * ttSF * lumi / 99554. );
      histos[names::ZPN10_BTAGUP][tag] ->Scale( 1.  * ttSF * lumi / 98560. );
      histos[names::ZPN12p5_BTAGUP][tag] ->Scale( 1.  * ttSF * lumi / 95730. );
      histos[names::ZPN15_BTAGUP][tag] ->Scale( 1.  * ttSF * lumi / 97696. );
      histos[names::ZPN20_BTAGUP][tag] ->Scale( 1.  * ttSF * lumi / 97600. );
      histos[names::ZPN25_BTAGUP][tag] ->Scale( 1.  * ttSF * lumi / 99800. );
      histos[names::ZPN30_BTAGUP][tag] ->Scale( 1.  * ttSF * lumi / 98668. );
      histos[names::ZPN35_BTAGUP][tag] ->Scale( 1.  * ttSF * lumi / 97104. );
      histos[names::ZPN40_BTAGUP][tag] ->Scale( 1.  * ttSF * lumi / 99554. );
      histos[names::ZPN10_BTAGDN][tag] ->Scale( 1.  * ttSF * lumi / 98560. );
      histos[names::ZPN12p5_BTAGDN][tag] ->Scale( 1.  * ttSF * lumi / 95730. );
      histos[names::ZPN15_BTAGDN][tag] ->Scale( 1.  * ttSF * lumi / 97696. );
      histos[names::ZPN20_BTAGDN][tag] ->Scale( 1.  * ttSF * lumi / 97600. );
      histos[names::ZPN25_BTAGDN][tag] ->Scale( 1.  * ttSF * lumi / 99800. );
      histos[names::ZPN30_BTAGDN][tag] ->Scale( 1.  * ttSF * lumi / 98668. );
      histos[names::ZPN35_BTAGDN][tag] ->Scale( 1.  * ttSF * lumi / 97104. );
      histos[names::ZPN40_BTAGDN][tag] ->Scale( 1.  * ttSF * lumi / 99554. );
      histos[names::ZPN10_PUUP][tag] ->Scale( 1.  * ttSF * lumi / 98560. );
      histos[names::ZPN12p5_PUUP][tag] ->Scale( 1.  * ttSF * lumi / 95730. );
      histos[names::ZPN15_PUUP][tag] ->Scale( 1.  * ttSF * lumi / 97696. );
      histos[names::ZPN20_PUUP][tag] ->Scale( 1.  * ttSF * lumi / 97600. );
      histos[names::ZPN25_PUUP][tag] ->Scale( 1.  * ttSF * lumi / 99800. );
      histos[names::ZPN30_PUUP][tag] ->Scale( 1.  * ttSF * lumi / 98668. );
      histos[names::ZPN35_PUUP][tag] ->Scale( 1.  * ttSF * lumi / 97104. );
      histos[names::ZPN40_PUUP][tag] ->Scale( 1.  * ttSF * lumi / 99554. );
      histos[names::ZPN10_PUDN][tag] ->Scale( 1.  * ttSF * lumi / 98560. );
      histos[names::ZPN12p5_PUDN][tag] ->Scale( 1.  * ttSF * lumi / 95730. );
      histos[names::ZPN15_PUDN][tag] ->Scale( 1.  * ttSF * lumi / 97696. );
      histos[names::ZPN20_PUDN][tag] ->Scale( 1.  * ttSF * lumi / 97600. );
      histos[names::ZPN25_PUDN][tag] ->Scale( 1.  * ttSF * lumi / 99800. );
      histos[names::ZPN30_PUDN][tag] ->Scale( 1.  * ttSF * lumi / 98668. );
      histos[names::ZPN35_PUDN][tag] ->Scale( 1.  * ttSF * lumi / 97104. );
      histos[names::ZPN40_PUDN][tag] ->Scale( 1.  * ttSF * lumi / 99554. );
    }//RSG, signal = 3
    cout<<"end of loop"<<endl;
  } 

  
  for (int tag = 0; tag < 6; tag++){
    cout << "TAG CATEGORY " << tag << endl;

    //ttbar subtraction
    histos[names::QCD][tag]->Add(histos[names::TT_SUBTRACT][tag],-1);
    histos[names::QCD_SYST][tag]->Add(histos[names::TT_SUBTRACTSYST][tag],-1);

    //rebinning in bins of 30% background error
    if (forTHETA){

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
	cout << "StatErr: " << statErr << endl;
	float binContent = h_background->GetBinContent(j_bin);
	//float binEntries = h_background->GetBinEntries(j_bin);
	cout << "non sumw2 Error: " << sqrt(binContent) <<endl;
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
        }
      }
      
      for (int proc = 0; proc < names::NUM_PROCS; proc++){
	if (proc != names::TT_SUBTRACT && proc != names::TT_SUBTRACTSYST && proc != names::QCDMC && proc != names::QCDMC_SYST){
	  cout << "Processing " << labels[proc] << endl;
	  histos[proc][tag] = (TH1F *) histos[proc][tag]->Rebin(nBinsNew, "h", xbins);
	  cout << histos[proc][tag]->GetNbinsX() << endl;
	}
      }
    }

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

    if (tag == 2 or tag == 5) histos[names::DATA][tag]->SetMaximum(3.0 * histos[names::DATA][tag]->GetMaximum() );
    else histos[names::DATA][tag]->SetMaximum(2.0 * histos[names::DATA][tag]->GetMaximum() );
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

    
    //errors and post-fit scaling
    float totalTopErr = 0.0;
    float totalQCDErr = 0.0;
    float totalHistErr = 0.0;
    
    float lumiErr_top = 0.027;
    float xsErr_top = 0.15;
    float topTagErr_top = 2*(0.09/0.89);
    if (postFit){
      xsErr_top = 0.08;
      topTagErr_top = 0.50;
    }

    for (int i_bin = 1; i_bin < (n_xbins+1); i_bin++){
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
      float PUErrUp = abs(TTbinContent - histos[names::TT_PUUP][tag]->GetBinContent(i_bin));
      float PUErrDn = abs(TTbinContent - histos[names::TT_PUDN][tag]->GetBinContent(i_bin));
      float PUErr = max(PUErrUp,PUErrDn);
      float PSHErrUp = abs(TTbinContent - histos[names::TT_PSHUP][tag]->GetBinContent(i_bin));
      float PSHErrDn = abs(TTbinContent - histos[names::TT_PSHDN][tag]->GetBinContent(i_bin));
      float PSHErr = max(PSHErrUp,PSHErrDn);
      float qcdSystErr = 0.5*abs( QCDbinContent - histos[names::QCD_SYST][tag]->GetBinContent(i_bin) );
      float xsErr = xsErr_top*(TTbinContent);
      float lumiErr = lumiErr_top*(TTbinContent);
      float topTagErr = topTagErr_top*(TTbinContent);

      float diffClose = 0.0;
      float QCDcenter = histos[names::QCD][tag]->GetBinCenter(i_bin);
      int j_bin = histos[names::QCDMC][tag]->GetXaxis()->FindBin(QCDcenter);
      if (histos[names::QCDMC][tag]->GetBinContent(j_bin) != 0){
	diffClose = abs( histos[names::QCDMC][tag]->GetBinContent(j_bin) - histos[names::QCDMC_SYST][tag]->GetBinContent(j_bin) )/(histos[names::QCDMC][tag]->GetBinContent(j_bin));
      }
      float closeErr = diffClose*(QCDbinContent);

      //adjusting the background bin contents and errors with the postfit nuisance parameters - from https://indico.cern.ch/event/557452/contributions/2246868/attachments/1311279/1962238/update_july18.pdf
      if (postFit){
	float QCDpostFitBinContent = QCDbinContent + (qcdSystErr*-1.13659365675) + (closeErr*-0.220031592593);
	histos[names::QCD][tag]->SetBinContent(i_bin, QCDpostFitBinContent);
	float TTpostFitBinContent = TTbinContent + (scaleErr*0.439112914571) + (jerErr*-0.0895863766889) + (pdfErr*-0.134026920264) + (q2Err*-0.217576290897) + (btagErr*0.0675294259315) + (xsErr*-0.378266575878) + (lumiErr*0.78020704204) + (topTagErr*-0.0166162168857) + (PUErr*0.307540317129) + (PSHErr*-0.347530433585);
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
	PSHErr *= 0.113155942116;

	float QCDbinErr = sqrt(statErr_QCD*statErr_QCD + qcdSystErr*qcdSystErr + closeErr*closeErr);
	histos[names::QCD][tag]->SetBinError(i_bin, QCDbinErr);
	float TTbinErr = sqrt(statErr_top*statErr_top + scaleErr*scaleErr + jerErr*jerErr + pdfErr*pdfErr + q2Err*q2Err + btagErr*btagErr + xsErr*xsErr + lumiErr*lumiErr + topTagErr*topTagErr + PUErr+PUErr + PSHErr*PSHErr);
	histos[names::TT][tag]->SetBinError(i_bin, TTbinErr);
      }

      float TOTALErr = sqrt(statErr*statErr + scaleErr*scaleErr + jerErr*jerErr + pdfErr*pdfErr + q2Err*q2Err + btagErr*btagErr + qcdSystErr*qcdSystErr + xsErr*xsErr + lumiErr*lumiErr + topTagErr*topTagErr + closeErr*closeErr + PUErr+PUErr + PSHErr*PSHErr);
      
      totalQCDErr = sqrt(statErr_QCD*statErr_QCD + qcdSystErr*qcdSystErr + closeErr*closeErr + totalQCDErr*totalQCDErr);
      totalTopErr = sqrt(statErr_top*statErr_top + scaleErr*scaleErr + jerErr*jerErr + pdfErr*pdfErr + q2Err*q2Err + btagErr*btagErr + xsErr*xsErr + lumiErr*lumiErr + topTagErr*topTagErr + PUErr+PUErr + PSHErr*PSHErr + totalTopErr*totalTopErr);
      totalHistErr = sqrt(TOTALErr*TOTALErr + totalHistErr*totalHistErr);
      //cout << "Bin " << i_bin << ": Content = " << totalH->GetBinContent(i_bin) << ", Error = " << TOTALErr << ", Percent Error = " << TOTALErr/(totalH->GetBinContent(i_bin)) << endl;
    }

    cout << "Region " << tag << " Total QCD: " << histos[names::QCD][tag]->Integral() << " +/- " << totalQCDErr <<endl;
    cout << "Region " << tag << " Total ttbar: " << histos[names::TT][tag]->Integral() << " +/- " << totalTopErr <<endl;

    THStack *stack = new THStack();
    stack->Add(histos[names::TT][tag]);
    stack->Add(histos[names::QCD][tag]);
    
    stack->Draw("hist same");
    histos[names::DATA][tag]->SetMarkerStyle(20);
    histos[names::DATA][tag]->SetMarkerSize(0.5);
    histos[names::DATA][tag]->SetLineColor(kBlack);
    histos[names::DATA][tag]->SetTitle("");

    TH1F *totalH = (TH1F *) histos[names::QCD][tag]->Clone("totalH");
    totalH->Add(histos[names::TT][tag]);
    totalH->SetFillStyle(3001);
    totalH->SetFillColor(kGray+1);
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
    leg->AddEntry(histos[names::DATA][tag], "Data", "lp");
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
    ratioH = (TH1F*) histos[names::DATA][tag]->Clone("ratio");
    ratioH->Sumw2();
    ratioH->Divide(ratioH, totalH);

    TH1F *ratioErrH = new TH1F();
    ratioErrH = (TH1F*) totalH->Clone("ratioErr");
    ratioErrH->Sumw2();
    ratioErrH->Divide(ratioErrH, totalH);

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
    ratioErrH->Draw("E2 same");

    TF1 *line = new TF1("line", "1", 0, 7000);
    line->SetLineColor(kBlack);
    line->Draw("same");
    ratioH->Draw("E0 same");

    gPad->RedrawAxis();

    
    if (signal == 0){//ZPN                                                                                                                   
      c1->SaveAs("Distributions/ZPN_errors"+tagLabels[tag]+outEnd+"pdf");
      c1->SaveAs("Distributions/ZPN_errors"+tagLabels[tag]+outEnd+"png");
      c1_2->cd();
      histos[names::DATA][tag]->SetMaximum(100.0 * histos[names::DATA][tag]->GetMaximum() );
      if (tag == 0 || tag == 1 || tag == 2 || tag == 5) histos[names::DATA][tag]->SetMaximum(50.0 * histos[names::DATA][tag]->GetMaximum() );
      c1_2->SetLogy(1);
      c1->SaveAs("Distributions/ZPN_errors"+tagLabels[tag]+"_log"+outEnd+"pdf");
      c1->SaveAs("Distributions/ZPN_errors"+tagLabels[tag]+"_log"+outEnd+"png");
    }//ZPN, signal = 0                                                                                                                       
    else if (signal == 1){//ZPW                                                                                                              
      c1->SaveAs("Distributions/ZPW_errors"+tagLabels[tag]+outEnd+"pdf");
      c1->SaveAs("Distributions/ZPW_errors"+tagLabels[tag]+outEnd+"png");
      c1_2->cd();
      histos[names::DATA][tag]->SetMaximum(100.0 * histos[names::DATA][tag]->GetMaximum() );
      c1_2->SetLogy(1);
      c1->SaveAs("Distributions/ZPW_errors"+tagLabels[tag]+"_log"+outEnd+"pdf");
      c1->SaveAs("Distributions/ZPW_errors"+tagLabels[tag]+"_log"+outEnd+"png");
    }//ZPW, signal = 1
    else if (signal == 2){//ZPXW                                                                                                             
      c1->SaveAs("Distributions/ZPXW_errors"+tagLabels[tag]+outEnd+"pdf");
      c1->SaveAs("Distributions/ZPXW_errors"+tagLabels[tag]+outEnd+"png");
      c1_2->cd();
      histos[names::DATA][tag]->SetMaximum(100.0 * histos[names::DATA][tag]->GetMaximum() );
      c1_2->SetLogy(1);
      c1->SaveAs("Distributions/ZPXW_errors"+tagLabels[tag]+"_log"+outEnd+"pdf");
      c1->SaveAs("Distributions/ZPXW_errors"+tagLabels[tag]+"_log"+outEnd+"png");
    }//ZPXW, signal = 2                                                                                                                      
    else if (signal == 3){//RSG                                                                                                              
      c1->SaveAs("Distributions/RSG_errors"+tagLabels[tag]+outEnd+"pdf");
      c1->SaveAs("Distributions/RSG_errors"+tagLabels[tag]+outEnd+"png");
      c1_2->cd();
      histos[names::DATA][tag]->SetMaximum(100.0 * histos[names::DATA][tag]->GetMaximum() );
      c1_2->SetLogy(1);
      c1->SaveAs("Distributions/RSG_errors"+tagLabels[tag]+"_log"+outEnd+"pdf");
      c1->SaveAs("Distributions/RSG_errors"+tagLabels[tag]+"_log"+outEnd+"png");
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

    histos[names::DATA][tag]->Write( Form("btag%d__DATA", tag) );
    histos[names::QCD][tag]->Write( Form("btag%d__qcd", tag) );
    histos[names::TT][tag]->Write( Form("btag%d__ttbar", tag) );
    histos[names::TT_SCALEUP][tag]->Write( Form("btag%d__ttbar__jec__up", tag) );
    histos[names::TT_SCALEDN][tag]->Write( Form("btag%d__ttbar__jec__down", tag) );
    histos[names::TT_JERUP][tag]->Write( Form("btag%d__ttbar__jer__up", tag) );
    histos[names::TT_JERDN][tag]->Write( Form("btag%d__ttbar__jer__down", tag) );
    histos[names::TT_PDFUP][tag]->Write( Form("btag%d__ttbar__pdf__up", tag) );
    histos[names::TT_PDFDN][tag]->Write( Form("btag%d__ttbar__pdf__down", tag) );
    histos[names::TT_PSHUP][tag]->Write( Form("btag%d__ttbar__parSho__up", tag) );
    histos[names::TT_PSHDN][tag]->Write( Form("btag%d__ttbar__parSho__down", tag) );
    histos[names::TT_BTAGUP][tag]->Write( Form("btag%d__ttbar__btag__up", tag) );
    histos[names::TT_BTAGDN][tag]->Write( Form("btag%d__ttbar__btag__down", tag) );
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

    histos[names::ZPN10_SCALEUP][tag]->Write( Form("btag%d__Zprime1000__jec__up", tag));
    if (signal != 2) histos[names::ZPN12p5_SCALEUP][tag]->Write( Form("btag%d__Zprime1250__jec__up", tag));
    if (signal != 2) histos[names::ZPN15_SCALEUP][tag]->Write( Form("btag%d__Zprime1500__jec__up", tag) );
    histos[names::ZPN20_SCALEUP][tag]->Write( Form("btag%d__Zprime2000__jec__up", tag) );
    if (signal != 2) histos[names::ZPN25_SCALEUP][tag]->Write( Form("btag%d__Zprime2500__jec__up", tag) );
    histos[names::ZPN30_SCALEUP][tag]->Write( Form("btag%d__Zprime3000__jec__up", tag) );
    if (signal != 2) histos[names::ZPN35_SCALEUP][tag]->Write( Form("btag%d__Zprime3500__jec__up", tag) ); 
    histos[names::ZPN40_SCALEUP][tag]->Write( Form("btag%d__Zprime4000__jec__up", tag) ); 
    histos[names::ZPN10_SCALEDN][tag]->Write( Form("btag%d__Zprime1000__jec__down", tag));
    if (signal != 2) histos[names::ZPN12p5_SCALEDN][tag]->Write( Form("btag%d__Zprime1250__jec__down", tag));
    if (signal != 2) histos[names::ZPN15_SCALEDN][tag]->Write( Form("btag%d__Zprime1500__jec__down", tag) );
    histos[names::ZPN20_SCALEDN][tag]->Write( Form("btag%d__Zprime2000__jec__down", tag) );
    if (signal != 2) histos[names::ZPN25_SCALEDN][tag]->Write( Form("btag%d__Zprime2500__jec__down", tag) );
    histos[names::ZPN30_SCALEDN][tag]->Write( Form("btag%d__Zprime3000__jec__down", tag) );
    if (signal != 2) histos[names::ZPN35_SCALEDN][tag]->Write( Form("btag%d__Zprime3500__jec__down", tag) );  
    histos[names::ZPN40_SCALEDN][tag]->Write( Form("btag%d__Zprime4000__jec__down", tag) );  

    histos[names::ZPN10_JERUP][tag]->Write( Form("btag%d__Zprime1000__jer__up", tag));
    if (signal != 2) histos[names::ZPN12p5_JERUP][tag]->Write( Form("btag%d__Zprime1250__jer__up", tag));
    if (signal != 2) histos[names::ZPN15_JERUP][tag]->Write( Form("btag%d__Zprime1500__jer__up", tag) );
    histos[names::ZPN20_JERUP][tag]->Write( Form("btag%d__Zprime2000__jer__up", tag) );
    if (signal != 2) histos[names::ZPN25_JERUP][tag]->Write( Form("btag%d__Zprime2500__jer__up", tag) );
    histos[names::ZPN30_JERUP][tag]->Write( Form("btag%d__Zprime3000__jer__up", tag) );
    if (signal != 2) histos[names::ZPN35_JERUP][tag]->Write( Form("btag%d__Zprime3500__jer__up", tag) ); 
    histos[names::ZPN40_JERUP][tag]->Write( Form("btag%d__Zprime4000__jer__up", tag) ); 
    histos[names::ZPN10_JERDN][tag]->Write( Form("btag%d__Zprime1000__jer__down", tag));
    if (signal != 2) histos[names::ZPN12p5_JERDN][tag]->Write( Form("btag%d__Zprime1250__jer__down", tag));
    if (signal != 2) histos[names::ZPN15_JERDN][tag]->Write( Form("btag%d__Zprime1500__jer__down", tag) );
    histos[names::ZPN20_JERDN][tag]->Write( Form("btag%d__Zprime2000__jer__down", tag) );
    if (signal != 2) histos[names::ZPN25_JERDN][tag]->Write( Form("btag%d__Zprime2500__jer__down", tag) );
    histos[names::ZPN30_JERDN][tag]->Write( Form("btag%d__Zprime3000__jer__down", tag) );
    if (signal != 2) histos[names::ZPN35_JERDN][tag]->Write( Form("btag%d__Zprime3500__jer__down", tag) );  
    histos[names::ZPN40_JERDN][tag]->Write( Form("btag%d__Zprime4000__jer__down", tag) );  

    histos[names::ZPN10_PDFUP][tag]->Write( Form("btag%d__Zprime1000__pdf__up", tag));
    if (signal != 2) histos[names::ZPN12p5_PDFUP][tag]->Write( Form("btag%d__Zprime1250__pdf__up", tag));
    if (signal != 2) histos[names::ZPN15_PDFUP][tag]->Write( Form("btag%d__Zprime1500__pdf__up", tag) );
    histos[names::ZPN20_PDFUP][tag]->Write( Form("btag%d__Zprime2000__pdf__up", tag) );
    if (signal != 2) histos[names::ZPN25_PDFUP][tag]->Write( Form("btag%d__Zprime2500__pdf__up", tag) );
    histos[names::ZPN30_PDFUP][tag]->Write( Form("btag%d__Zprime3000__pdf__up", tag) );
    if (signal != 2) histos[names::ZPN35_PDFUP][tag]->Write( Form("btag%d__Zprime3500__pdf__up", tag) ); 
    histos[names::ZPN40_PDFUP][tag]->Write( Form("btag%d__Zprime4000__pdf__up", tag) ); 
    histos[names::ZPN10_PDFDN][tag]->Write( Form("btag%d__Zprime1000__pdf__down", tag));
    if (signal != 2) histos[names::ZPN12p5_PDFDN][tag]->Write( Form("btag%d__Zprime1250__pdf__down", tag));
    if (signal != 2) histos[names::ZPN15_PDFDN][tag]->Write( Form("btag%d__Zprime1500__pdf__down", tag) );
    histos[names::ZPN20_PDFDN][tag]->Write( Form("btag%d__Zprime2000__pdf__down", tag) );
    if (signal != 2) histos[names::ZPN25_PDFDN][tag]->Write( Form("btag%d__Zprime2500__pdf__down", tag) );
    histos[names::ZPN30_PDFDN][tag]->Write( Form("btag%d__Zprime3000__pdf__down", tag) );
    if (signal != 2) histos[names::ZPN35_PDFDN][tag]->Write( Form("btag%d__Zprime3500__pdf__down", tag) );  
    histos[names::ZPN40_PDFDN][tag]->Write( Form("btag%d__Zprime4000__pdf__down", tag) );  

    histos[names::ZPN10_BTAGUP][tag]->Write( Form("btag%d__Zprime1000__btag__up", tag));
    if (signal != 2) histos[names::ZPN12p5_BTAGUP][tag]->Write( Form("btag%d__Zprime1250__btag__up", tag));
    if (signal != 2) histos[names::ZPN15_BTAGUP][tag]->Write( Form("btag%d__Zprime1500__btag__up", tag) );
    histos[names::ZPN20_BTAGUP][tag]->Write( Form("btag%d__Zprime2000__btag__up", tag) );
    if (signal != 2) histos[names::ZPN25_BTAGUP][tag]->Write( Form("btag%d__Zprime2500__btag__up", tag) );
    histos[names::ZPN30_BTAGUP][tag]->Write( Form("btag%d__Zprime3000__btag__up", tag) );
    if (signal != 2) histos[names::ZPN35_BTAGUP][tag]->Write( Form("btag%d__Zprime3500__btag__up", tag) ); 
    histos[names::ZPN40_BTAGUP][tag]->Write( Form("btag%d__Zprime4000__btag__up", tag) ); 
    histos[names::ZPN10_BTAGDN][tag]->Write( Form("btag%d__Zprime1000__btag__down", tag));
    if (signal != 2) histos[names::ZPN12p5_BTAGDN][tag]->Write( Form("btag%d__Zprime1250__btag__down", tag));
    if (signal != 2) histos[names::ZPN15_BTAGDN][tag]->Write( Form("btag%d__Zprime1500__btag__down", tag) );
    histos[names::ZPN20_BTAGDN][tag]->Write( Form("btag%d__Zprime2000__btag__down", tag) );
    if (signal != 2) histos[names::ZPN25_BTAGDN][tag]->Write( Form("btag%d__Zprime2500__btag__down", tag) );
    histos[names::ZPN30_BTAGDN][tag]->Write( Form("btag%d__Zprime3000__btag__down", tag) );
    if (signal != 2) histos[names::ZPN35_BTAGDN][tag]->Write( Form("btag%d__Zprime3500__btag__down", tag) );  
    histos[names::ZPN40_BTAGDN][tag]->Write( Form("btag%d__Zprime4000__btag__down", tag) );  
    
    histos[names::ZPN10_PUUP][tag]->Write( Form("btag%d__Zprime1000__pileup__up", tag));
    if (signal != 2) histos[names::ZPN12p5_PUUP][tag]->Write( Form("btag%d__Zprime1250__pileup__up", tag));
    if (signal != 2) histos[names::ZPN15_PUUP][tag]->Write( Form("btag%d__Zprime1500__pileup__up", tag) );
    histos[names::ZPN20_PUUP][tag]->Write( Form("btag%d__Zprime2000__pileup__up", tag) );
    if (signal != 2) histos[names::ZPN25_PUUP][tag]->Write( Form("btag%d__Zprime2500__pileup__up", tag) );
    histos[names::ZPN30_PUUP][tag]->Write( Form("btag%d__Zprime3000__pileup__up", tag) );
    if (signal != 2) histos[names::ZPN35_PUUP][tag]->Write( Form("btag%d__Zprime3500__pileup__up", tag) ); 
    histos[names::ZPN40_PUUP][tag]->Write( Form("btag%d__Zprime4000__pileup__up", tag) ); 
    histos[names::ZPN10_PUDN][tag]->Write( Form("btag%d__Zprime1000__pileup__down", tag));
    if (signal != 2) histos[names::ZPN12p5_PUDN][tag]->Write( Form("btag%d__Zprime1250__pileup__down", tag));
    if (signal != 2) histos[names::ZPN15_PUDN][tag]->Write( Form("btag%d__Zprime1500__pileup__down", tag) );
    histos[names::ZPN20_PUDN][tag]->Write( Form("btag%d__Zprime2000__pileup__down", tag) );
    if (signal != 2) histos[names::ZPN25_PUDN][tag]->Write( Form("btag%d__Zprime2500__pileup__down", tag) );
    histos[names::ZPN30_PUDN][tag]->Write( Form("btag%d__Zprime3000__pileup__down", tag) );
    if (signal != 2) histos[names::ZPN35_PUDN][tag]->Write( Form("btag%d__Zprime3500__pileup__down", tag) );  
    histos[names::ZPN40_PUDN][tag]->Write( Form("btag%d__Zprime4000__pileup__down", tag) );  


  }



  if (!postFit) outFile->Close();
  return 0;

}
