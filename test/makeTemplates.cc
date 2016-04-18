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

#include "names.C"
#include "CMS_lumi.C"

using namespace std;
using namespace names;

int makeTemplates(int signal = 0, bool forTHETA = 1){
//signal: 0 = ZPN, 1 = ZPW, 2 = ZPXW, 3 = RSG

  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0000000000); //this clears all the boxes and crap 

  cout << names::NUM_PROCS << endl;

  int numProcs = names::NUM_PROCS;

  string file = "templates_narrow.root";//ZPN
  if (signal == 1) file = "templates_wide.root";
  else if (signal == 2) file = "templates_extrawide.root";
  else if (signal == 3) file = "templates_RSGluon.root";

  TFile *outFile = new TFile(Form("%s",file.c_str()),"RECREATE");

  TString labels[150];
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

  //TString dir = "/uscms_data/d3/maral87/ttbarResonances/B2GAnaFW/CMSSW_7_4_12/src/Analysis/B2GTTbar/test/runs/run_020516/";
  TString dir1 = "/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/runs/";
  //TString dir2="/uscms_data/d3/maral87/ttbarResonances/B2GAnaFW/CMSSW_7_4_12/src/Analysis/B2GTTbar/test/runs/run_022316/";
  TString dir2 = "/uscms_data/d3/maral87/ttbarResonances/B2GAnaFW/CMSSW_7_4_12/src/Analysis/B2GTTbar/test/runs/run_030716/";
  TString dir3 = "/uscms_data/d3/maral87/ttbarResonances/B2GAnaFW/CMSSW_7_4_12/src/Analysis/B2GTTbar/test/runs/run_032916/";
  TString dir4 = "/uscms_data/d3/pilot/MINIAOD/CMSSW_7_4_1/src/B2GTTbar/test/";

  TString files[150];
  files[names::DATA]          = dir3 +  "outBkgdEst_JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65_032916_nom.root";
  files[names::QCD]           = files[names::DATA];
  files[names::QCD_SYST]      = files[names::DATA];
  files[names::QCDMC]         = dir2 + "outBkgdEst_QCD_HT700toInf_B2Gv8p4_reader603e_notrig_pDep_030716_nom_scaled.root";//FIX!!!!!s
  files[names::QCDMC_SYST]    = files[names::QCDMC];
  files[names::TT]            = dir3 +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_032916_nom.root";
  files[names::TT_SUBTRACT]   = dir3 +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_032916_nom.root";
  files[names::TT_SUBTRACTSYST]   = dir3 +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_032916_nom.root";
  files[names::TT_JERUP]      = dir3 +   "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_032916_jer_up.root";
  files[names::TT_JERDN]      = dir3 +   "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_032916_jer_dn.root";
  files[names::TT_SCALEUP]    = dir3 +   "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_032916_jec_up.root";
  files[names::TT_SCALEDN]    = dir3 +   "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_032916_jec_dn.root";
  files[names::TT_PDFUP]      = dir3 +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_032916_pdf_up.root";
  files[names::TT_PDFDN]      = dir3 +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_032916_pdf_dn.root";
  files[names::TT_PSHUP]      = dir4 +  "outBkgdEst_TT_PSup_03162016_nom.root";
  files[names::TT_PSHDN]      = dir4 +  "outBkgdEst_TT_PSdown_03162016_nom.root";
  files[names::TT_Q2UP]       = dir3 +   "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_032916_q2_up.root";
  files[names::TT_Q2DN]       = dir3 +   "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_032916_q2_dn.root";
  files[names::TT_BTAGUP]     = dir3 +   "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_032916_bTag_up.root";
  files[names::TT_BTAGDN]     = dir3 +   "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_032916_bTag_dn.root";
  files[names::TT_PUUP]     = dir3 +   "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_040516_PU_up.root";
  files[names::TT_PUDN]     = dir3 +   "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_040516_PU_dn.root";

  if (signal == 0){//ZPN
    files[names::ZPN10]         = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_032916_nom.root";
    files[names::ZPN12p5]       = dir3 +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_032916_nom.root";
    files[names::ZPN15]         = dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_032916_nom.root";
    files[names::ZPN20]         = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_032916_nom.root";
    files[names::ZPN25]         = dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_032916_nom.root";
    files[names::ZPN30]         = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_032916_nom.root";
    files[names::ZPN35]         = dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_032916_nom.root";
    files[names::ZPN40]         = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_032916_nom.root";
    
    files[names::ZPN10_SCALEUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN12p5_SCALEUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN15_SCALEUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN20_SCALEUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN25_SCALEUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN30_SCALEUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN35_SCALEUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN40_SCALEUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN10_SCALEDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_032916_jec_dn.root";
    files[names::ZPN12p5_SCALEDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_032916_jec_dn.root";
    files[names::ZPN15_SCALEDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_032916_jec_dn.root";
    files[names::ZPN20_SCALEDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_032916_jec_dn.root";
    files[names::ZPN25_SCALEDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_032916_jec_dn.root";
    files[names::ZPN30_SCALEDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_032916_jec_dn.root";
    files[names::ZPN35_SCALEDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_032916_jec_dn.root";
    files[names::ZPN40_SCALEDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_032916_jec_dn.root";
  
    files[names::ZPN10_JERUP]   = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN12p5_JERUP]   = dir3 +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN15_JERUP]   = dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN20_JERUP]   = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN25_JERUP]   = dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN30_JERUP]   = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN35_JERUP]   = dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN40_JERUP]   = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN10_JERDN]   = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_032916_jer_dn.root";
    files[names::ZPN12p5_JERDN]   = dir3 +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_032916_jer_dn.root";
    files[names::ZPN15_JERDN]   = dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_032916_jer_dn.root";
    files[names::ZPN20_JERDN]   = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_032916_jer_dn.root";
    files[names::ZPN25_JERDN]   = dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_032916_jer_dn.root";
    files[names::ZPN30_JERDN]   = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_032916_jer_dn.root";
    files[names::ZPN35_JERDN]   = dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_032916_jer_dn.root";
    files[names::ZPN40_JERDN]   = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_032916_jer_dn.root";

    files[names::ZPN10_PDFUP]   = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN12p5_PDFUP]   = dir3 +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN15_PDFUP]   = dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN20_PDFUP]   = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN25_PDFUP]   = dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN30_PDFUP]   = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN35_PDFUP]   = dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN40_PDFUP]   = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN10_PDFDN]   = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_032916_pdf_dn.root";
    files[names::ZPN12p5_PDFDN]   = dir3 +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_032916_pdf_dn.root";
    files[names::ZPN15_PDFDN]   = dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_032916_pdf_dn.root";
    files[names::ZPN20_PDFDN]   = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_032916_pdf_dn.root";
    files[names::ZPN25_PDFDN]   = dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_032916_pdf_dn.root";
    files[names::ZPN30_PDFDN]   = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_032916_pdf_dn.root";
    files[names::ZPN35_PDFDN]   = dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_032916_pdf_dn.root";
    files[names::ZPN40_PDFDN]   = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_032916_pdf_dn.root";
    
    files[names::ZPN10_BTAGUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN12p5_BTAGUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN15_BTAGUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN20_BTAGUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN25_BTAGUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN30_BTAGUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN35_BTAGUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN40_BTAGUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN10_BTAGDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_032916_bTag_dn.root";
    files[names::ZPN12p5_BTAGDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_032916_bTag_dn.root";
    files[names::ZPN15_BTAGDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_032916_bTag_dn.root";
    files[names::ZPN20_BTAGDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_032916_bTag_dn.root";
    files[names::ZPN25_BTAGDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_032916_bTag_dn.root";
    files[names::ZPN30_BTAGDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_032916_bTag_dn.root";
    files[names::ZPN35_BTAGDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_032916_bTag_dn.root";
    files[names::ZPN40_BTAGDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_032916_bTag_dn.root";

    files[names::ZPN10_PUUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN12p5_PUUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN15_PUUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN20_PUUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN25_PUUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN30_PUUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN35_PUUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN40_PUUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN10_PUDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_040516_PU_dn.root";
    files[names::ZPN12p5_PUDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_040516_PU_dn.root";
    files[names::ZPN15_PUDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_040516_PU_dn.root";
    files[names::ZPN20_PUDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_040516_PU_dn.root";
    files[names::ZPN25_PUDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_040516_PU_dn.root";
    files[names::ZPN30_PUDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_040516_PU_dn.root";
    files[names::ZPN35_PUDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_040516_PU_dn.root";
    files[names::ZPN40_PUDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_040516_PU_dn.root";
  }//ZPN, signal = 0
  else if (signal == 1){//ZPW                                                                                                                
    files[names::ZPN10] = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e_032916_nom.root";
    files[names::ZPN12p5] = dir3 +  "outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e_032916_nom.root";
    files[names::ZPN15] = dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e_032916_nom.root";
    files[names::ZPN20] = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e_032916_nom.root";
    files[names::ZPN25] = dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e_032916_nom.root";
    files[names::ZPN30] = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e_032916_nom.root";
    files[names::ZPN35] = dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e_032916_nom.root";
    files[names::ZPN40] = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e_032916_nom.root";

    files[names::ZPN10_SCALEUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN12p5_SCALEUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN15_SCALEUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN20_SCALEUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN25_SCALEUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN30_SCALEUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN35_SCALEUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN40_SCALEUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN10_SCALEDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e_032916_jec_dn.root";
    files[names::ZPN12p5_SCALEDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e_032916_jec_dn.root";
    files[names::ZPN15_SCALEDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e_032916_jec_dn.root";
    files[names::ZPN20_SCALEDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e_032916_jec_dn.root";
    files[names::ZPN25_SCALEDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e_032916_jec_dn.root";
    files[names::ZPN30_SCALEDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e_032916_jec_dn.root";
    files[names::ZPN35_SCALEDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e_032916_jec_dn.root";
    files[names::ZPN40_SCALEDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e_032916_jec_dn.root";

    files[names::ZPN10_JERUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN12p5_JERUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN15_JERUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN20_JERUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN25_JERUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN30_JERUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN35_JERUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN40_JERUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN10_JERDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e_032916_jer_dn.root";
    files[names::ZPN12p5_JERDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e_032916_jer_dn.root";
    files[names::ZPN15_JERDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e_032916_jer_dn.root";
    files[names::ZPN20_JERDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e_032916_jer_dn.root";
    files[names::ZPN25_JERDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e_032916_jer_dn.root";
    files[names::ZPN30_JERDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e_032916_jer_dn.root";
    files[names::ZPN35_JERDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e_032916_jer_dn.root";
    files[names::ZPN40_JERDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e_032916_jer_dn.root";

    files[names::ZPN10_BTAGUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN12p5_BTAGUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN15_BTAGUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN20_BTAGUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN25_BTAGUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN30_BTAGUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN35_BTAGUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN40_BTAGUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN10_BTAGDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e_032916_bTag_dn.root";
    files[names::ZPN12p5_BTAGDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e_032916_bTag_dn.root";
    files[names::ZPN15_BTAGDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e_032916_bTag_dn.root";
    files[names::ZPN20_BTAGDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e_032916_bTag_dn.root";
    files[names::ZPN25_BTAGDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e_032916_bTag_dn.root";
    files[names::ZPN30_BTAGDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e_032916_bTag_dn.root";
    files[names::ZPN35_BTAGDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e_032916_bTag_dn.root";
    files[names::ZPN40_BTAGDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e_032916_bTag_dn.root";

    files[names::ZPN10_PDFUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN12p5_PDFUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN15_PDFUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN20_PDFUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN25_PDFUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN30_PDFUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN35_PDFUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN40_PDFUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN10_PDFDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e_032916_pdf_dn.root";
    files[names::ZPN12p5_PDFDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e_032916_pdf_dn.root";
    files[names::ZPN15_PDFDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e_032916_pdf_dn.root";
    files[names::ZPN20_PDFDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e_032916_pdf_dn.root";
    files[names::ZPN25_PDFDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e_032916_pdf_dn.root";
    files[names::ZPN30_PDFDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e_032916_pdf_dn.root";
    files[names::ZPN35_PDFDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e_032916_pdf_dn.root";
    files[names::ZPN40_PDFDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e_032916_pdf_dn.root";
    

    files[names::ZPN10_PUUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN12p5_PUUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN15_PUUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN20_PUUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN25_PUUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN30_PUUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN35_PUUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN40_PUUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN10_PUDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e_040516_PU_dn.root";
    files[names::ZPN12p5_PUDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e_040516_PU_dn.root";
    files[names::ZPN15_PUDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e_040516_PU_dn.root";
    files[names::ZPN20_PUDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e_040516_PU_dn.root";
    files[names::ZPN25_PUDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e_040516_PU_dn.root";
    files[names::ZPN30_PUDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e_040516_PU_dn.root";
    files[names::ZPN35_PUDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e_040516_PU_dn.root";
    files[names::ZPN40_PUDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e_040516_PU_dn.root";
  }//ZPW, signal = 1                                                                                                                         
  else if (signal == 2){//ZPXW                                                                                                               
    files[names::ZPN10] = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_032916_nom.root";
    files[names::ZPN12p5] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_032916_nom.root";            
    files[names::ZPN15] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_032916_nom.root";              
    files[names::ZPN20] = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_032916_nom.root";
    files[names::ZPN25] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_032916_nom.root";              
    files[names::ZPN30] = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_032916_nom.root";
    files[names::ZPN35] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_032916_nom.root";             
    files[names::ZPN40] = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_032916_nom.root";

    files[names::ZPN10_SCALEUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN12p5_SCALEUP] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN15_SCALEUP] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_032916_jec_up.root";   
    files[names::ZPN20_SCALEUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN25_SCALEUP] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_032916_jec_up.root";   
    files[names::ZPN30_SCALEUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN35_SCALEUP] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_032916_jec_up.root";  
    files[names::ZPN40_SCALEUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN10_SCALEDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_032916_jec_dn.root";
    files[names::ZPN12p5_SCALEDN] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_032916_jec_dn.root";
    files[names::ZPN15_SCALEDN] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_032916_jec_dn.root";   
    files[names::ZPN20_SCALEDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_032916_jec_dn.root";
    files[names::ZPN25_SCALEDN] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_032916_jec_dn.root";   
    files[names::ZPN30_SCALEDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_032916_jec_dn.root";
    files[names::ZPN35_SCALEDN] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_032916_jec_dn.root";  
    files[names::ZPN40_SCALEDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_032916_jec_dn.root";

    files[names::ZPN10_JERUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN12p5_JERUP] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_032916_jer_up.root";   
    files[names::ZPN15_JERUP] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_032916_jer_up.root";     
    files[names::ZPN20_JERUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN25_JERUP] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_032916_jer_up.root";     
    files[names::ZPN30_JERUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN35_JERUP] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_032916_jer_up.root";    
    files[names::ZPN40_JERUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN10_JERDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_032916_jer_dn.root";
    files[names::ZPN12p5_JERDN] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_032916_jer_dn.root";   
    files[names::ZPN15_JERDN] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_032916_jer_dn.root";     
    files[names::ZPN20_JERDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_032916_jer_dn.root";
    files[names::ZPN25_JERDN] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_032916_jer_dn.root";     
    files[names::ZPN30_JERDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_032916_jer_dn.root";
    files[names::ZPN35_JERDN] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_032916_jer_dn.root";    
    files[names::ZPN40_JERDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_032916_jer_dn.root";

    files[names::ZPN10_BTAGUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN12p5_BTAGUP] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN15_BTAGUP] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_032916_bTag_up.root";   
    files[names::ZPN20_BTAGUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN25_BTAGUP] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_032916_bTag_up.root";   
    files[names::ZPN30_BTAGUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN35_BTAGUP] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_032916_bTag_up.root";  
    files[names::ZPN40_BTAGUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN10_BTAGDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_032916_bTag_dn.root";
    files[names::ZPN12p5_BTAGDN] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_032916_bTag_dn.root";
    files[names::ZPN15_BTAGDN] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_032916_bTag_dn.root";  
    files[names::ZPN20_BTAGDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_032916_bTag_dn.root";
    files[names::ZPN25_BTAGDN] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_032916_bTag_dn.root";  
    files[names::ZPN30_BTAGDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_032916_bTag_dn.root";
    files[names::ZPN35_BTAGDN] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_032916_bTag_dn.root";  
    files[names::ZPN40_BTAGDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_032916_bTag_dn.root";

    files[names::ZPN10_PDFUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN12p5_PDFUP] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_032916_pdf_up.root"; 
    files[names::ZPN15_PDFUP] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_032916_pdf_up.root";   
    files[names::ZPN20_PDFUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN25_PDFUP] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_032916_pdf_up.root";   
    files[names::ZPN30_PDFUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN35_PDFUP] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_032916_pdf_up.root";  
    files[names::ZPN40_PDFUP] = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN10_PDFDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_032916_pdf_dn.root";
    files[names::ZPN12p5_PDFDN] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_032916_pdf_dn.root"; 
    files[names::ZPN15_PDFDN] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_032916_pdf_dn.root";    
    files[names::ZPN20_PDFDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_032916_pdf_dn.root";
    files[names::ZPN25_PDFDN] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_032916_pdf_dn.root";    
    files[names::ZPN30_PDFDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_032916_pdf_dn.root";
    files[names::ZPN35_PDFDN] = files[names::ZPN10];//dir3 +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_032916_pdf_dn.root"    
    files[names::ZPN40_PDFDN] = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_032916_pdf_dn.root";
    
    files[names::ZPN10_PUUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN12p5_PUUP]  = files[names::ZPN10];
    files[names::ZPN15_PUUP]  = files[names::ZPN10];
    files[names::ZPN20_PUUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN25_PUUP]  = files[names::ZPN10];
    files[names::ZPN30_PUUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN35_PUUP]  = files[names::ZPN10];
    files[names::ZPN40_PUUP]  = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN10_PUDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_040516_PU_dn.root";
    files[names::ZPN12p5_PUDN]  = files[names::ZPN10];
    files[names::ZPN15_PUDN]  = files[names::ZPN10];
    files[names::ZPN20_PUDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_040516_PU_dn.root";
    files[names::ZPN25_PUDN]  = files[names::ZPN10];
    files[names::ZPN30_PUDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_040516_PU_dn.root";
    files[names::ZPN35_PUDN]  = files[names::ZPN10]; 
    files[names::ZPN40_PUDN]  = dir3 +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_040516_PU_dn.root";
  }//ZPXW, signal = 2
  else if (signal == 3){//RSG                                                                                                                
    files[names::ZPN10]         = dir3 +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_032916_nom.root";
    files[names::ZPN12p5]       = dir3 +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_032916_nom.root";
    files[names::ZPN15]         = dir3 +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_032916_nom.root";
    files[names::ZPN20]         = dir3 +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_032916_nom.root";
    files[names::ZPN25]         = dir3 +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_032916_nom.root";
    files[names::ZPN30]         = dir3 +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_032916_nom.root";
    files[names::ZPN35]         = dir3 +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_032916_nom.root";
    files[names::ZPN40]         = dir3 +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_041216_nom.root";

    files[names::ZPN10_SCALEUP] = dir3 +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN12p5_SCALEUP] = dir3 +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN15_SCALEUP] = dir3 +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN20_SCALEUP] = dir3 +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN25_SCALEUP] = dir3 +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN30_SCALEUP] = dir3 +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN35_SCALEUP] = dir3 +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_032916_jec_up.root";
    files[names::ZPN40_SCALEUP] = dir3 +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_041216_jec_up.root";
    files[names::ZPN10_SCALEDN] = dir3 +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_032916_jec_dn.root";
    files[names::ZPN12p5_SCALEDN] = dir3 +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_032916_jec_dn.root";
    files[names::ZPN15_SCALEDN] = dir3 +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_032916_jec_dn.root";
    files[names::ZPN20_SCALEDN] = dir3 +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_032916_jec_dn.root";
    files[names::ZPN25_SCALEDN] = dir3 +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_032916_jec_dn.root";
    files[names::ZPN30_SCALEDN] = dir3 +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_032916_jec_dn.root";
    files[names::ZPN35_SCALEDN] = dir3 +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_032916_jec_dn.root";
    files[names::ZPN40_SCALEDN] = dir3 +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_041216_jec_dn.root";

    files[names::ZPN10_JERUP]   = dir3 +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN12p5_JERUP]   = dir3 +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN15_JERUP]   = dir3 +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN20_JERUP]   = dir3 +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN25_JERUP]   = dir3 +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN30_JERUP]   = dir3 +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN35_JERUP]   = dir3 +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_032916_jer_up.root";
    files[names::ZPN40_JERUP]   = dir3 +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_041216_jer_up.root";
    files[names::ZPN10_JERDN]   = dir3 +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_032916_jer_dn.root";
    files[names::ZPN12p5_JERDN]   = dir3 +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_032916_jer_dn.root";
    files[names::ZPN15_JERDN]   = dir3 +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_032916_jer_dn.root";
    files[names::ZPN20_JERDN]   = dir3 +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_032916_jer_dn.root";
    files[names::ZPN25_JERDN]   = dir3 +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_032916_jer_dn.root";
    files[names::ZPN30_JERDN]   = dir3 +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_032916_jer_dn.root";
    files[names::ZPN35_JERDN]   = dir3 +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_032916_jer_dn.root";
    files[names::ZPN40_JERDN]   = dir3 +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_041216_jer_dn.root";

    files[names::ZPN10_PDFUP]   = dir3+  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN12p5_PDFUP]   = dir3+  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN15_PDFUP]   = dir3+  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN20_PDFUP]   = dir3+  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN25_PDFUP]   = dir3+  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN30_PDFUP]   = dir3+  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN35_PDFUP]   = dir3+  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_032916_pdf_up.root";
    files[names::ZPN40_PDFUP]   = dir3 +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_041216_pdf_up.root";
    files[names::ZPN10_PDFDN]   = dir3+  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_032916_pdf_dn.root";
    files[names::ZPN12p5_PDFDN]   = dir3+  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_032916_pdf_dn.root";
    files[names::ZPN15_PDFDN]   = dir3+  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_032916_pdf_dn.root";
    files[names::ZPN20_PDFDN]   = dir3+  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_032916_pdf_dn.root";
    files[names::ZPN25_PDFDN]   = dir3+  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_032916_pdf_dn.root";
    files[names::ZPN30_PDFDN]   = dir3+  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_032916_pdf_dn.root";
    files[names::ZPN35_PDFDN]   = dir3+  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_032916_pdf_dn.root";
    files[names::ZPN40_PDFDN]   = dir3 +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_041216_pdf_dn.root";

    files[names::ZPN10_BTAGUP]  = dir3 +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN12p5_BTAGUP]  = dir3 +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN15_BTAGUP]  = dir3 +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN20_BTAGUP]  = dir3 +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN25_BTAGUP]  = dir3 +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN30_BTAGUP]  = dir3 +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN35_BTAGUP]  = dir3 +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_032916_bTag_up.root";
    files[names::ZPN40_BTAGUP]  = dir3 +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_041216_bTag_up.root";
    files[names::ZPN10_BTAGDN]  = dir3 +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_032916_bTag_dn.root";
    files[names::ZPN12p5_BTAGDN]  = dir3 +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_032916_bTag_dn.root";
    files[names::ZPN15_BTAGDN]  = dir3 +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_032916_bTag_dn.root";
    files[names::ZPN20_BTAGDN]  = dir3 +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_032916_bTag_dn.root";
    files[names::ZPN25_BTAGDN]  = dir3 +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_032916_bTag_dn.root";
    files[names::ZPN30_BTAGDN]  = dir3 +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_032916_bTag_dn.root";
    files[names::ZPN35_BTAGDN]  = dir3 +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_032916_bTag_dn.root";
    files[names::ZPN40_BTAGDN]  = dir3 +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_041216_bTag_dn.root";
    

    files[names::ZPN10_PUUP]  = dir3 +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN12p5_PUUP]  = dir3 +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN15_PUUP]  = dir3 +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN20_PUUP]  = dir3 +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN25_PUUP]  = dir3 +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN30_PUUP]  = dir3 +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN35_PUUP]  = dir3 +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_040516_PU_up.root";
    files[names::ZPN40_PUUP]  = dir3 +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_041216_PU_up.root";
    files[names::ZPN10_PUDN]  = dir3 +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_040516_PU_dn.root";
    files[names::ZPN12p5_PUDN]  = dir3 +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_040516_PU_dn.root";
    files[names::ZPN15_PUDN]  = dir3 +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_040516_PU_dn.root";
    files[names::ZPN20_PUDN]  = dir3 +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_040516_PU_dn.root";
    files[names::ZPN25_PUDN]  = dir3 +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_040516_PU_dn.root";
    files[names::ZPN30_PUDN]  = dir3 +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_040516_PU_dn.root";
    files[names::ZPN35_PUDN]  = dir3 +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_040516_PU_dn.root";
    files[names::ZPN40_PUDN]  = dir3 +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_041216_PU_dn.root";
    }//RSG, signal = 3 */

  int rebin_factor = 50;

  for (int proc = 0; proc < names::NUM_PROCS; proc++){


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
      /*Double_t xbins[257]  = {   0,  10,  20,  30,  40,  50,  60,  70,  80,  90,

                                 200, 210, 220, 230, 240, 250, 260, 270, 280, 290,

                                 300, 310, 320, 330, 340, 350, 360, 370, 380, 390,

                                 400, 410, 420, 430, 440, 450, 460, 470, 480, 490,

                                 500, 510, 520, 530, 540, 550, 560, 570, 580, 590,

                                 600, 610, 620, 630, 640, 650, 660, 670, 680, 690,

                                 700, 710, 720, 730, 740, 750, 760, 770, 780, 790,

                                 800, 810, 820, 830, 840, 850, 860, 870, 880, 890,

                                 900, 910, 920, 930, 940, 950, 960, 970, 980, 990,

                                 1000, 1010, 1020, 1030, 1040, 1050, 1060, 1070, 1080, 1090,

				 1100, 1110, 1120, 1130, 1140, 1150, 1160, 1170, 1180, 1190,
				 
				 1200, 1210, 1220, 1230, 1240, 1250, 1260, 1270, 1280, 1290,
				 
				 1300, 1310, 1320, 1330, 1340, 1350, 1360, 1370, 1380, 1390,
				 
				 1400, 1410, 1420, 1430, 1440, 1450, 1460, 1470, 1480, 1490,
				 
				 1500, 1510, 1520, 1530, 1540, 1550, 1560, 1570, 1580, 1590,
				 
				 1600, 1610, 1620, 1630, 1640, 1650, 1660, 1670, 1680, 1690,
				 
				 1700, 1710, 1720, 1730, 1740, 1750, 1760, 1770, 1780, 1790,
				 
				 1800, 1810, 1820, 1830, 1840, 1850, 1860, 1870, 1880, 1890,

				 1900, 1910, 1920, 1930, 1940, 1950, 1960, 1970, 1980, 1990,

				 2000, 2010, 2020, 2030, 2040, 2050, 2060, 2070, 2080, 2090,

				 2100, 2110, 2120, 2130, 2140, 2150, 2160, 2170, 2180, 2190,

				 2200, 2210, 2220, 2230, 2240, 2250, 2260, 2270, 2280, 2290,

				 2300, 2310, 2320, 2330, 2340, 2350, 2360, 2370, 2380, 2390,

				 2400, 2410, 2420, 2430, 2440, 2450, 2460, 2470, 2480, 2490,

				 2500, 2510, 2520, 2530, 2540, 2550, 2560, 2570, 2580, 2590,

				 2600, 2800, 3000, 3500, 4000, 5000, 7000 };

      histos[proc][0] = (TH1F *) histos[proc][0]->Rebin(256, "h0", xbins);//rebin_factor);
      histos[proc][1] = (TH1F *) histos[proc][1]->Rebin(256, "h1", xbins);//rebin_factor);
      histos[proc][2] = (TH1F *) histos[proc][2]->Rebin(256, "h2", xbins);//rebin_factor);
      histos[proc][3] = (TH1F *) histos[proc][3]->Rebin(256, "h3", xbins);//rebin_factor);
      histos[proc][4] = (TH1F *) histos[proc][4]->Rebin(256, "h4", xbins);//rebin_factor);
      histos[proc][5] = (TH1F *) histos[proc][5]->Rebin(256, "h5", xbins);//rebin_factor);
      histos[proc][6] = (TH1F *) histos[proc][6]->Rebin(256, "h6", xbins);//rebin_factor);*/

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
    histos[h][0]->Sumw2();
    histos[h][1]->Sumw2();
    histos[h][2]->Sumw2();
    histos[h][3]->Sumw2();
    histos[h][4]->Sumw2();
    histos[h][5]->Sumw2();
    histos[h][6]->Sumw2();
  }



  float lumi = 2592.3;
  float nttbar = 96834559.;//19665194.;
  float kfactor = 0.94;
  float ttSF = 0.89*0.89;

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

      //calculating the number of new bins
      for (int i_bin = 0; i_bin < (nBinsOriginal-1); i_bin++){
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

      //setting the bin array
      Double_t xbins[nBinsNew+1];
      xbins[0]=0.0;
      xbins[nBinsNew]=7000.;
      lastBinLowEdge = 7000.;
      totalBinContent = 0.0;
      totalStatErr = 0.0;
      int binCount = 0;
      for (int i_bin = 0; i_bin < (nBinsOriginal-1); i_bin++){
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
      
      //rebinning the tail
      /*int nBins = 20;
	if (tag == 0) nBins = 20;
	else if (tag == 1) nBins = 13;
	else if (tag == 2) nBins = 6;
	else if (tag == 3) nBins = 42;
	else if (tag == 4) nBins = 20;
	else if (tag == 5) nBins = 4;
	
	Double_t xbins_btag0[21] = {0.,800.,900.,1000.,1100.,1200.,1300.,1400.,1500.,1600.,1700.,1800.,1900.,2000.,2100.,2200.,2300.,2400.,2600.,3500.,7000.};
	Double_t xbins_btag1[14] = {0.,800.,900.,1000.,1100.,1200.,1300.,1400.,1500.,1600.,1700.,1900.,3050.,7000.};
	Double_t xbins_btag2[7] = {0.,900.,1100.,1200.,1300.,2650.,7000.};
	Double_t xbins_btag3[43] = {0.,900.,1000.,1100.,1200.,1300.,1400.,1500.,1600.,1700.,1800.,1900.,2000.,2100.,2200.,2300.,2400.,2500.,2600.,2700.,2800.,2900.,3000.,3100.,3200.,3300.,3400.,3500.,3600.,3700.,3800.,3900.,4000.,4100.,4300.,4400.,4500.,4700.,4900.,5100.,5400.,6200.,7000.};
	Double_t xbins_btag4[21] = {0.,1100.,1200.,1300.,1400.,1500.,1600.,1700.,1800.,1900.,2000.,2100.,2200.,2300.,2400.,2600.,2800.,3100.,3600.,4000.,7000.};
	Double_t xbins_btag5[5] = {0.,1300.,1600.,2800.,7000.};
      */
      for (int proc = 0; proc < names::NUM_PROCS; proc++){
	if (proc != names::TT_SUBTRACT && proc != names::TT_SUBTRACTSYST && proc != names::QCDMC && proc != names::QCDMC_SYST){
	  cout << "Processing " << labels[proc] << endl;
	  /*if (tag == 0) histos[proc][tag] = (TH1F *) histos[proc][tag]->Rebin(nBins, "h", xbins_btag0);
	  else if (tag == 1) histos[proc][tag] = (TH1F *) histos[proc][tag]->Rebin(nBins, "h", xbins_btag1);
	  else if (tag == 2) histos[proc][tag] = (TH1F *) histos[proc][tag]->Rebin(nBins, "h", xbins_btag2);
	  else if (tag == 3) histos[proc][tag] = (TH1F *) histos[proc][tag]->Rebin(nBins, "h", xbins_btag3);
	  else if (tag == 4) histos[proc][tag] = (TH1F *) histos[proc][tag]->Rebin(nBins, "h", xbins_btag4);
	  else if (tag == 5) histos[proc][tag] = (TH1F *) histos[proc][tag]->Rebin(nBins, "h", xbins_btag5);*/
	  histos[proc][tag] = (TH1F *) histos[proc][tag]->Rebin(nBinsNew, "h", xbins);
	  cout << histos[proc][tag]->GetNbinsX() << endl;
	}
      }

      TH1F *h_TTstat = (TH1F *) histos[names::TT][tag]->Clone("h_TTstat");
      TH1F *h_ZPN15stat = (TH1F *) histos[names::ZPN15][tag]->Clone("h_ZPN15stat");
      TH1F *h_ZPN35stat = (TH1F *) histos[names::ZPN35][tag]->Clone("h_ZPN35stat");

      //changing QCD statistical error to sqrt(N) up to 2500 GeV
      int nbinsQCD = histos[names::QCD][tag]->GetNbinsX();
      cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
      cout<<"btag "<<tag<<endl;
      for (int i_qcd = 1; i_qcd < (nbinsQCD+1); i_qcd++){
	//histos[names::QCD][tag]->SetBinError(i_qcd,0.0);
	float TTbinContent = abs(histos[names::TT][tag]->GetBinContent(i_qcd)); 
	float TTbinError = abs(histos[names::TT][tag]->GetBinError(i_qcd)); 
	if (TTbinContent == 0) h_TTstat->SetBinContent(i_qcd,0.0);
	else h_TTstat->SetBinContent(i_qcd,(TTbinError/TTbinContent));
	cout<<""<<endl;
	cout<<"t#bar{t} Bin " << i_qcd << " Percent Error: " <<  h_TTstat->GetBinContent(i_qcd)<<endl;
	cout<<"t#bar{t} Bin Error: "<<histos[names::TT][tag]->GetBinError(i_qcd)<<endl;
	cout<<"t#bar{t} Bin Content: "<<histos[names::TT][tag]->GetBinContent(i_qcd)<<endl;
	//cout<<"t#bar{t} Poisson Bin Error: "<<sqrt(TTbinContent)<<endl;

	float ZPN15binContent = abs(histos[names::ZPN15][tag]->GetBinContent(i_qcd)); 
	float ZPN15binError = abs(histos[names::ZPN15][tag]->GetBinError(i_qcd)); 
	if (ZPN15binContent == 0) h_ZPN15stat->SetBinContent(i_qcd,0.0);
	else h_ZPN15stat->SetBinContent(i_qcd,(ZPN15binError/ZPN15binContent));
	cout<<""<<endl;
	cout<<"ZPN 15 Bin " << i_qcd << " Percent Error: " <<  h_ZPN15stat->GetBinContent(i_qcd)<<endl;
	cout<<"ZPN 15 Bin Error: "<<histos[names::ZPN15][tag]->GetBinError(i_qcd)<<endl;
	cout<<"ZPN 15 Bin Content: "<<histos[names::ZPN15][tag]->GetBinContent(i_qcd)<<endl;
	//cout<<"ZPN 15 Poisson Bin Error: "<<sqrt(ZPN15binContent)<<endl;

	float ZPN35binContent = abs(histos[names::ZPN35][tag]->GetBinContent(i_qcd)); 
	float ZPN35binError = abs(histos[names::ZPN35][tag]->GetBinError(i_qcd)); 
	if (ZPN35binContent == 0) h_ZPN35stat->SetBinContent(i_qcd,0.0);
	else h_ZPN35stat->SetBinContent(i_qcd,(ZPN35binError/ZPN35binContent));
	cout<<""<<endl;
	cout<<"ZPN 35 Bin " << i_qcd << " Percent Error: " <<  h_ZPN35stat->GetBinContent(i_qcd)<<endl;
	cout<<"ZPN 35 Bin Error: "<<histos[names::ZPN35][tag]->GetBinError(i_qcd)<<endl;
	cout<<"ZPN 35 Bin Content: "<<histos[names::ZPN35][tag]->GetBinContent(i_qcd)<<endl;
	//cout<<"ZPN 35 Poisson Bin Error: "<<sqrt(ZPN35binContent)<<endl;

	histos[names::TT][tag]->SetBinError(i_qcd,0.0);
	histos[names::ZPN10][tag]->SetBinError(i_qcd,0.0);
	histos[names::ZPN12p5][tag]->SetBinError(i_qcd,0.0);
	histos[names::ZPN15][tag]->SetBinError(i_qcd,0.0);
	histos[names::ZPN20][tag]->SetBinError(i_qcd,0.0);
	histos[names::ZPN25][tag]->SetBinError(i_qcd,0.0);
	histos[names::ZPN30][tag]->SetBinError(i_qcd,0.0);
	histos[names::ZPN35][tag]->SetBinError(i_qcd,0.0);
	histos[names::ZPN40][tag]->SetBinError(i_qcd,0.0);
	
	/*float QCDbinLowEdge = histos[names::QCD][tag]->GetBinLowEdge(i_qcd);
	cout<<"Bin "<<i_qcd<<", Low Edge = "<<QCDbinLowEdge<<endl;
	if (QCDbinLowEdge >= 2500.){
	  cout<<"Adjusting Bin Error!"<<endl;
	  cout<<"Old Bin Error: "<<histos[names::QCD][tag]->GetBinError(i_qcd)<<endl;
	  cout<<"Bin Content: "<<histos[names::QCD][tag]->GetBinContent(i_qcd)<<endl;
	  float QCDbinContent = abs(histos[names::QCD][tag]->GetBinContent(i_qcd));
	  histos[names::QCD][tag]->SetBinError(i_qcd,sqrt(QCDbinContent));
	  cout<<"New Bin Error: "<<histos[names::QCD][tag]->GetBinError(i_qcd)<<endl;
	  }*/
      }
      cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;

      TCanvas *cStat = new TCanvas();
      h_TTstat->SetLineColor(kRed);
      h_ZPN15stat->SetLineColor(kBlue);
      h_ZPN35stat->SetLineColor(kViolet);
      h_ZPN35stat->SetLineWidth(2);
      h_TTstat->SetLineWidth(2);
      h_ZPN35stat->SetLineWidth(2);

      h_ZPN35stat->Draw("hist");
      h_TTstat->Draw("histSAME");
      h_ZPN15stat->Draw("histSAME");

      TLegend *legStat = new TLegend(0.7, 0.4, 0.94, 0.83);
      legStat->AddEntry(h_TTstat, "Top", "L");
      legStat->AddEntry(h_ZPN15stat, "1.5 TeV Narrow Z'", "L");
      legStat->AddEntry(h_ZPN35stat, "3.5 TeV Narrow Z'", "L");

      legStat->SetFillColor(0);
      legStat->SetLineColor(0);
      legStat->Draw("same");

      cStat->SaveAs("ZPN_statPercentError_30pRebin0329Files_"+tagLabels[tag]+".pdf");
      cStat->SaveAs("ZPN_statPercentError_30pRebin0329Files_"+tagLabels[tag]+".root");
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
    histos[names::DATA][tag]->GetYaxis()->SetTitle("Events");
    //histos[names::DATA][tag]->GetYaxis()->SetTitleSize(1.2);                                                                               
    histos[names::DATA][tag]->GetYaxis()->SetTitleOffset(1.1);
    if (!forTHETA){
      if (tag == 2 or tag == 5) histos[names::DATA][tag]->GetXaxis()->SetRangeUser(600.,4600.);
      else histos[names::DATA][tag]->GetXaxis()->SetRangeUser(600.,6000.);
    }
    histos[names::DATA][tag]->Draw("E");

    THStack *stack = new THStack();
    stack->Add(histos[names::TT][tag]);
    stack->Add(histos[names::QCD][tag]);
    stack->Draw("hist same");
    histos[names::DATA][tag]->SetMarkerStyle(20);
    histos[names::DATA][tag]->SetMarkerSize(0.5);
    histos[names::DATA][tag]->SetLineColor(kBlack);
    histos[names::DATA][tag]->SetTitle("");

    //errors                                                                                                                                
    float xsErr_top = 0.15;
    float lumiErr_top = 0.027;
    float topTagErr_top = 2*(0.09/0.89);

    TH1F *totalH = (TH1F *) histos[names::QCD][tag]->Clone("totalH");
    totalH->Add(histos[names::TT][tag]);

    int n_xbins = totalH->GetNbinsX();

    for (int i_bin = 1; i_bin < (n_xbins+1); i_bin++){

      float statErr = totalH->GetBinError(i_bin);
      float scaleErrUp = abs(histos[names::TT][tag]->GetBinContent(i_bin) - histos[names::TT_SCALEUP][tag]->GetBinContent(i_bin));
      float scaleErrDn = abs(histos[names::TT][tag]->GetBinContent(i_bin) - histos[names::TT_SCALEDN][tag]->GetBinContent(i_bin));
      float scaleErr = max(scaleErrUp,scaleErrDn);
      float jerErrUp = abs(histos[names::TT][tag]->GetBinContent(i_bin) - histos[names::TT_JERUP][tag]->GetBinContent(i_bin));
      float jerErrDn = abs(histos[names::TT][tag]->GetBinContent(i_bin) - histos[names::TT_JERDN][tag]->GetBinContent(i_bin));
      float jerErr = max(jerErrUp,jerErrDn);
      float pdfErrUp = abs(histos[names::TT][tag]->GetBinContent(i_bin) - histos[names::TT_PDFUP][tag]->GetBinContent(i_bin));
      float pdfErrDn = abs(histos[names::TT][tag]->GetBinContent(i_bin) - histos[names::TT_PDFDN][tag]->GetBinContent(i_bin));
      float pdfErr = max(pdfErrUp,pdfErrDn);
      float q2ErrUp = abs(histos[names::TT][tag]->GetBinContent(i_bin) - histos[names::TT_Q2UP][tag]->GetBinContent(i_bin));
      float q2ErrDn = abs(histos[names::TT][tag]->GetBinContent(i_bin) - histos[names::TT_Q2DN][tag]->GetBinContent(i_bin));
      float q2Err = max(q2ErrUp,q2ErrDn);
      float btagErrUp = abs(histos[names::TT][tag]->GetBinContent(i_bin) - histos[names::TT_BTAGUP][tag]->GetBinContent(i_bin));
      float btagErrDn = abs(histos[names::TT][tag]->GetBinContent(i_bin) - histos[names::TT_BTAGDN][tag]->GetBinContent(i_bin));
      float btagErr = max(btagErrUp,btagErrDn);
      float PUErrUp = abs(histos[names::TT][tag]->GetBinContent(i_bin) - histos[names::TT_PUUP][tag]->GetBinContent(i_bin));
      float PUErrDn = abs(histos[names::TT][tag]->GetBinContent(i_bin) - histos[names::TT_PUDN][tag]->GetBinContent(i_bin));
      float PUErr = max(PUErrUp,PUErrDn);
      float qcdSystErr = 0.5*abs( histos[names::QCD][tag]->GetBinContent(i_bin) - histos[names::QCD_SYST][tag]->GetBinContent(i_bin) );
      float xsErr = xsErr_top*(histos[names::TT][tag]->GetBinContent(i_bin));
      float lumiErr = lumiErr_top*(histos[names::TT][tag]->GetBinContent(i_bin));
      float topTagErr = topTagErr_top*(histos[names::TT][tag]->GetBinContent(i_bin));

      float diffClose = 0.0;
      float QCDcenter = histos[names::QCD][tag]->GetBinCenter(i_bin);
      int j_bin = histos[names::QCDMC][tag]->GetXaxis()->FindBin(QCDcenter);
      if (histos[names::QCDMC][tag]->GetBinContent(j_bin) != 0){
	diffClose = abs( histos[names::QCDMC][tag]->GetBinContent(j_bin) - histos[names::QCDMC_SYST][tag]->GetBinContent(j_bin) )/(histos[names::QCDMC][tag]->GetBinContent(j_bin));
      }
      float closeErr = diffClose*(histos[names::QCD][tag]->GetBinContent(i_bin));

      float TOTALErr = sqrt(statErr*statErr + scaleErr*scaleErr + jerErr*jerErr + pdfErr*pdfErr + q2Err*q2Err + btagErr*btagErr + qcdSystErr*qcdSystErr + xsErr*xsErr + lumiErr*lumiErr + topTagErr*topTagErr + closeErr*closeErr + PUErr+PUErr);
      totalH->SetBinError(i_bin,TOTALErr);
      //cout << "Bin " << i_bin << ": Content = " << totalH->GetBinContent(i_bin) << ", Error = " << TOTALErr << ", Percent Error = " << TOTALErr/(totalH->GetBinContent(i_bin)) << endl;
    }

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
    if (tag == 1) categoryLabel->DrawLatex(0.7, 0.85, "1 b-tags, |#Deltay| < 1.0");
    if (tag == 2) categoryLabel->DrawLatex(0.7, 0.85, "2 b-tags, |#Deltay| < 1.0");
    if (tag == 3) categoryLabel->DrawLatex(0.7, 0.85, "0 b-tags, |#Deltay| > 1.0");
    if (tag == 4) categoryLabel->DrawLatex(0.7, 0.85, "1 b-tags, |#Deltay| > 1.0");
    if (tag == 5) categoryLabel->DrawLatex(0.7, 0.85, "2 b-tags, |#Deltay| > 1.0");
    if (tag == 6) categoryLabel->DrawLatex(0.7, 0.85, "All Signal Regions");

    CMS_lumi(c1_2, 4, 10);

    gPad->RedrawAxis();

    TLegend *leg = new TLegend(0.7, 0.4, 0.94, 0.83);
    leg->AddEntry(histos[names::DATA][tag], "Data", "lp");
    leg->AddEntry(histos[names::QCD][tag], "Non-Top Multijet", "f");
    leg->AddEntry(histos[names::TT][tag], "Top", "f");
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
    ratioH->GetYaxis()->SetTitle("Data / BG Ratio");
    ratioH->GetYaxis()->SetTitleOffset(0.4);
    ratioH->GetYaxis()->SetTitleSize(0.11);
    ratioH->GetYaxis()->SetNdivisions(205);
    ratioH->GetYaxis()->SetLabelSize(0.11);
    ratioH->GetXaxis()->SetLabelSize(0.11);
    ratioH->GetXaxis()->SetTitleSize(0.11);
    ratioH->GetXaxis()->SetTitle( "t#bar{t} Invariant Mass [GeV]");
    ratioH->Draw("E");

    ratioErrH->SetFillStyle(1001);
    ratioErrH->SetFillColor(kGray);
    ratioErrH->Draw("E2 same");

    TF1 *line = new TF1("line", "1", 0, 7000);
    line->SetLineColor(kBlack);
    line->Draw("same");
    ratioH->Draw("E same");

    gPad->RedrawAxis();

    string outEnd = "_forTHETA.";
    if (!forTHETA)  outEnd = ".";

    if (signal == 0){//ZPN                                                                                                                   
      c1->SaveAs("Distributions/ZPN_errors"+tagLabels[tag]+outEnd+"pdf");
      c1->SaveAs("Distributions/ZPN_errors"+tagLabels[tag]+outEnd+"png");
      c1_2->cd();
      histos[names::DATA][tag]->SetMaximum(100.0 * histos[names::DATA][tag]->GetMaximum() );
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

    qcdShapeSyst_Up->Write( Form("btag%d__qcd__modMass__plus", tag) );
    qcdShapeSyst_Dn->Write( Form("btag%d__qcd__modMass__minus", tag) );

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

    qcdClosureSyst_Up->Write( Form("btag%d__qcd__closure__plus", tag) );
    qcdClosureSyst_Dn->Write( Form("btag%d__qcd__closure__minus", tag) );

    histos[names::DATA][tag]->Write( Form("btag%d__DATA", tag) );
    histos[names::QCD][tag]->Write( Form("btag%d__qcd", tag) );
    histos[names::TT][tag]->Write( Form("btag%d__ttbar", tag) );
    histos[names::TT_SCALEUP][tag]->Write( Form("btag%d__ttbar__jec__plus", tag) );
    histos[names::TT_SCALEDN][tag]->Write( Form("btag%d__ttbar__jec__minus", tag) );
    histos[names::TT_JERUP][tag]->Write( Form("btag%d__ttbar__jer__plus", tag) );
    histos[names::TT_JERDN][tag]->Write( Form("btag%d__ttbar__jer__minus", tag) );
    histos[names::TT_PDFUP][tag]->Write( Form("btag%d__ttbar__pdf__plus", tag) );
    histos[names::TT_PDFDN][tag]->Write( Form("btag%d__ttbar__pdf__minus", tag) );
    histos[names::TT_PSHUP][tag]->Write( Form("btag%d__ttbar__parSho__plus", tag) );
    histos[names::TT_PSHDN][tag]->Write( Form("btag%d__ttbar__parSho__minus", tag) );
    histos[names::TT_BTAGUP][tag]->Write( Form("btag%d__ttbar__btag__plus", tag) );
    histos[names::TT_BTAGDN][tag]->Write( Form("btag%d__ttbar__btag__minus", tag) );
    histos[names::TT_PUUP][tag]->Write( Form("btag%d__ttbar__pileup__plus", tag) );
    histos[names::TT_PUDN][tag]->Write( Form("btag%d__ttbar__pileup__minus", tag) );
    histos[names::TT_Q2UP][tag]->Write( Form("btag%d__ttbar__q2__plus", tag) );
    histos[names::TT_Q2DN][tag]->Write( Form("btag%d__ttbar__q2__minus", tag) );
    

    histos[names::ZPN10][tag]->Write( Form("btag%d__Zprime1000", tag));
    if (signal != 2) histos[names::ZPN12p5][tag]->Write( Form("btag%d__Zprime1250", tag));
    if (signal != 2) histos[names::ZPN15][tag]->Write( Form("btag%d__Zprime1500", tag) );
    histos[names::ZPN20][tag]->Write( Form("btag%d__Zprime2000", tag) );
    if (signal != 2) histos[names::ZPN25][tag]->Write( Form("btag%d__Zprime2500", tag) );
    histos[names::ZPN30][tag]->Write( Form("btag%d__Zprime3000", tag) );
    if (signal != 2) histos[names::ZPN35][tag]->Write( Form("btag%d__Zprime3500", tag) );  
    histos[names::ZPN40][tag]->Write( Form("btag%d__Zprime4000", tag) );  

    histos[names::ZPN10_SCALEUP][tag]->Write( Form("btag%d__Zprime1000__jec__plus", tag));
    if (signal != 2) histos[names::ZPN12p5_SCALEUP][tag]->Write( Form("btag%d__Zprime1250__jec__plus", tag));
    if (signal != 2) histos[names::ZPN15_SCALEUP][tag]->Write( Form("btag%d__Zprime1500__jec__plus", tag) );
    histos[names::ZPN20_SCALEUP][tag]->Write( Form("btag%d__Zprime2000__jec__plus", tag) );
    if (signal != 2) histos[names::ZPN25_SCALEUP][tag]->Write( Form("btag%d__Zprime2500__jec__plus", tag) );
    histos[names::ZPN30_SCALEUP][tag]->Write( Form("btag%d__Zprime3000__jec__plus", tag) );
    if (signal != 2) histos[names::ZPN35_SCALEUP][tag]->Write( Form("btag%d__Zprime3500__jec__plus", tag) ); 
    histos[names::ZPN40_SCALEUP][tag]->Write( Form("btag%d__Zprime4000__jec__plus", tag) ); 
    histos[names::ZPN10_SCALEDN][tag]->Write( Form("btag%d__Zprime1000__jec__minus", tag));
    if (signal != 2) histos[names::ZPN12p5_SCALEDN][tag]->Write( Form("btag%d__Zprime1250__jec__minus", tag));
    if (signal != 2) histos[names::ZPN15_SCALEDN][tag]->Write( Form("btag%d__Zprime1500__jec__minus", tag) );
    histos[names::ZPN20_SCALEDN][tag]->Write( Form("btag%d__Zprime2000__jec__minus", tag) );
    if (signal != 2) histos[names::ZPN25_SCALEDN][tag]->Write( Form("btag%d__Zprime2500__jec__minus", tag) );
    histos[names::ZPN30_SCALEDN][tag]->Write( Form("btag%d__Zprime3000__jec__minus", tag) );
    if (signal != 2) histos[names::ZPN35_SCALEDN][tag]->Write( Form("btag%d__Zprime3500__jec__minus", tag) );  
    histos[names::ZPN40_SCALEDN][tag]->Write( Form("btag%d__Zprime4000__jec__minus", tag) );  

    histos[names::ZPN10_JERUP][tag]->Write( Form("btag%d__Zprime1000__jer__plus", tag));
    if (signal != 2) histos[names::ZPN12p5_JERUP][tag]->Write( Form("btag%d__Zprime1250__jer__plus", tag));
    if (signal != 2) histos[names::ZPN15_JERUP][tag]->Write( Form("btag%d__Zprime1500__jer__plus", tag) );
    histos[names::ZPN20_JERUP][tag]->Write( Form("btag%d__Zprime2000__jer__plus", tag) );
    if (signal != 2) histos[names::ZPN25_JERUP][tag]->Write( Form("btag%d__Zprime2500__jer__plus", tag) );
    histos[names::ZPN30_JERUP][tag]->Write( Form("btag%d__Zprime3000__jer__plus", tag) );
    if (signal != 2) histos[names::ZPN35_JERUP][tag]->Write( Form("btag%d__Zprime3500__jer__plus", tag) ); 
    histos[names::ZPN40_JERUP][tag]->Write( Form("btag%d__Zprime4000__jer__plus", tag) ); 
    histos[names::ZPN10_JERDN][tag]->Write( Form("btag%d__Zprime1000__jer__minus", tag));
    if (signal != 2) histos[names::ZPN12p5_JERDN][tag]->Write( Form("btag%d__Zprime1250__jer__minus", tag));
    if (signal != 2) histos[names::ZPN15_JERDN][tag]->Write( Form("btag%d__Zprime1500__jer__minus", tag) );
    histos[names::ZPN20_JERDN][tag]->Write( Form("btag%d__Zprime2000__jer__minus", tag) );
    if (signal != 2) histos[names::ZPN25_JERDN][tag]->Write( Form("btag%d__Zprime2500__jer__minus", tag) );
    histos[names::ZPN30_JERDN][tag]->Write( Form("btag%d__Zprime3000__jer__minus", tag) );
    if (signal != 2) histos[names::ZPN35_JERDN][tag]->Write( Form("btag%d__Zprime3500__jer__minus", tag) );  
    histos[names::ZPN40_JERDN][tag]->Write( Form("btag%d__Zprime4000__jer__minus", tag) );  

    histos[names::ZPN10_PDFUP][tag]->Write( Form("btag%d__Zprime1000__pdf__plus", tag));
    if (signal != 2) histos[names::ZPN12p5_PDFUP][tag]->Write( Form("btag%d__Zprime1250__pdf__plus", tag));
    if (signal != 2) histos[names::ZPN15_PDFUP][tag]->Write( Form("btag%d__Zprime1500__pdf__plus", tag) );
    histos[names::ZPN20_PDFUP][tag]->Write( Form("btag%d__Zprime2000__pdf__plus", tag) );
    if (signal != 2) histos[names::ZPN25_PDFUP][tag]->Write( Form("btag%d__Zprime2500__pdf__plus", tag) );
    histos[names::ZPN30_PDFUP][tag]->Write( Form("btag%d__Zprime3000__pdf__plus", tag) );
    if (signal != 2) histos[names::ZPN35_PDFUP][tag]->Write( Form("btag%d__Zprime3500__pdf__plus", tag) ); 
    histos[names::ZPN40_PDFUP][tag]->Write( Form("btag%d__Zprime4000__pdf__plus", tag) ); 
    histos[names::ZPN10_PDFDN][tag]->Write( Form("btag%d__Zprime1000__pdf__minus", tag));
    if (signal != 2) histos[names::ZPN12p5_PDFDN][tag]->Write( Form("btag%d__Zprime1250__pdf__minus", tag));
    if (signal != 2) histos[names::ZPN15_PDFDN][tag]->Write( Form("btag%d__Zprime1500__pdf__minus", tag) );
    histos[names::ZPN20_PDFDN][tag]->Write( Form("btag%d__Zprime2000__pdf__minus", tag) );
    if (signal != 2) histos[names::ZPN25_PDFDN][tag]->Write( Form("btag%d__Zprime2500__pdf__minus", tag) );
    histos[names::ZPN30_PDFDN][tag]->Write( Form("btag%d__Zprime3000__pdf__minus", tag) );
    if (signal != 2) histos[names::ZPN35_PDFDN][tag]->Write( Form("btag%d__Zprime3500__pdf__minus", tag) );  
    histos[names::ZPN40_PDFDN][tag]->Write( Form("btag%d__Zprime4000__pdf__minus", tag) );  

    histos[names::ZPN10_BTAGUP][tag]->Write( Form("btag%d__Zprime1000__btag__plus", tag));
    if (signal != 2) histos[names::ZPN12p5_BTAGUP][tag]->Write( Form("btag%d__Zprime1250__btag__plus", tag));
    if (signal != 2) histos[names::ZPN15_BTAGUP][tag]->Write( Form("btag%d__Zprime1500__btag__plus", tag) );
    histos[names::ZPN20_BTAGUP][tag]->Write( Form("btag%d__Zprime2000__btag__plus", tag) );
    if (signal != 2) histos[names::ZPN25_BTAGUP][tag]->Write( Form("btag%d__Zprime2500__btag__plus", tag) );
    histos[names::ZPN30_BTAGUP][tag]->Write( Form("btag%d__Zprime3000__btag__plus", tag) );
    if (signal != 2) histos[names::ZPN35_BTAGUP][tag]->Write( Form("btag%d__Zprime3500__btag__plus", tag) ); 
    histos[names::ZPN40_BTAGUP][tag]->Write( Form("btag%d__Zprime4000__btag__plus", tag) ); 
    histos[names::ZPN10_BTAGDN][tag]->Write( Form("btag%d__Zprime1000__btag__minus", tag));
    if (signal != 2) histos[names::ZPN12p5_BTAGDN][tag]->Write( Form("btag%d__Zprime1250__btag__minus", tag));
    if (signal != 2) histos[names::ZPN15_BTAGDN][tag]->Write( Form("btag%d__Zprime1500__btag__minus", tag) );
    histos[names::ZPN20_BTAGDN][tag]->Write( Form("btag%d__Zprime2000__btag__minus", tag) );
    if (signal != 2) histos[names::ZPN25_BTAGDN][tag]->Write( Form("btag%d__Zprime2500__btag__minus", tag) );
    histos[names::ZPN30_BTAGDN][tag]->Write( Form("btag%d__Zprime3000__btag__minus", tag) );
    if (signal != 2) histos[names::ZPN35_BTAGDN][tag]->Write( Form("btag%d__Zprime3500__btag__minus", tag) );  
    histos[names::ZPN40_BTAGDN][tag]->Write( Form("btag%d__Zprime4000__btag__minus", tag) );  
    
    histos[names::ZPN10_PUUP][tag]->Write( Form("btag%d__Zprime1000__pileup__plus", tag));
    if (signal != 2) histos[names::ZPN12p5_PUUP][tag]->Write( Form("btag%d__Zprime1250__pileup__plus", tag));
    if (signal != 2) histos[names::ZPN15_PUUP][tag]->Write( Form("btag%d__Zprime1500__pileup__plus", tag) );
    histos[names::ZPN20_PUUP][tag]->Write( Form("btag%d__Zprime2000__pileup__plus", tag) );
    if (signal != 2) histos[names::ZPN25_PUUP][tag]->Write( Form("btag%d__Zprime2500__pileup__plus", tag) );
    histos[names::ZPN30_PUUP][tag]->Write( Form("btag%d__Zprime3000__pileup__plus", tag) );
    if (signal != 2) histos[names::ZPN35_PUUP][tag]->Write( Form("btag%d__Zprime3500__pileup__plus", tag) ); 
    histos[names::ZPN40_PUUP][tag]->Write( Form("btag%d__Zprime4000__pileup__plus", tag) ); 
    histos[names::ZPN10_PUDN][tag]->Write( Form("btag%d__Zprime1000__pileup__minus", tag));
    if (signal != 2) histos[names::ZPN12p5_PUDN][tag]->Write( Form("btag%d__Zprime1250__pileup__minus", tag));
    if (signal != 2) histos[names::ZPN15_PUDN][tag]->Write( Form("btag%d__Zprime1500__pileup__minus", tag) );
    histos[names::ZPN20_PUDN][tag]->Write( Form("btag%d__Zprime2000__pileup__minus", tag) );
    if (signal != 2) histos[names::ZPN25_PUDN][tag]->Write( Form("btag%d__Zprime2500__pileup__minus", tag) );
    histos[names::ZPN30_PUDN][tag]->Write( Form("btag%d__Zprime3000__pileup__minus", tag) );
    if (signal != 2) histos[names::ZPN35_PUDN][tag]->Write( Form("btag%d__Zprime3500__pileup__minus", tag) );  
    histos[names::ZPN40_PUDN][tag]->Write( Form("btag%d__Zprime4000__pileup__minus", tag) );  



  }



outFile->Close();
return 0;

}
