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


using namespace std;
using namespace names;

int makeTemplates_RSGluon(bool constantBinning = 0){



  cout << names::NUM_PROCS << endl;

  int numProcs = names::NUM_PROCS;


  string file = "templates_RSGluon.root";
  if (constantBinning) file = "templates_RSGluon_constantBinning.root";
  TFile *outFile = new TFile(Form("%s",file.c_str()),"RECREATE");


  TString labels[100];
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
  /*labels[names::ZPN10_Q2UP]  = "ZpN10_q2_up";
  labels[names::ZPN15_Q2UP]  = "ZpN15_q2_up";
  labels[names::ZPN20_Q2UP]  = "ZpN20_q2_up";
  labels[names::ZPN25_Q2UP]  = "ZpN25_q2_up";
  labels[names::ZPN30_Q2UP]  = "ZpN30_q2_up";
  labels[names::ZPN35_Q2UP]  = "ZpN35_q2_up";
  labels[names::ZPN40_Q2UP]  = "ZpN40_q2_up";
  labels[names::ZPN10_Q2DN]  = "ZpN10_q2_dn";
  labels[names::ZPN12p5_Q2DN]  = "ZpN12p5_q2_dn";
  labels[names::ZPN15_Q2DN]  = "ZpN15_q2_dn";
  labels[names::ZPN20_Q2DN]  = "ZpN20_q2_dn";
  labels[names::ZPN25_Q2DN]  = "ZpN25_q2_dn";
  labels[names::ZPN30_Q2DN]  = "ZpN30_q2_dn";
  labels[names::ZPN35_Q2DN]  = "ZpN35_q2_dn";
  labels[names::ZPN40_Q2DN]  = "ZpN40_q2_dn";*/
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
    histos[h][0]->Sumw2();
    histos[h][1] = new TH1F();
    histos[h][1]->Sumw2();
    histos[h][2] = new TH1F();
    histos[h][2]->Sumw2();
    histos[h][3] = new TH1F();
    histos[h][3]->Sumw2();
    histos[h][4] = new TH1F();
    histos[h][4]->Sumw2();
    histos[h][5] = new TH1F();
    histos[h][5]->Sumw2();
    histos[h][6] = new TH1F();
    histos[h][6]->Sumw2();
  }

  TString dir = "/uscms_data/d3/maral87/ttbarResonances/B2GAnaFW/CMSSW_7_4_12/src/Analysis/B2GTTbar/test/runs/run_020516/";
  TString dir1 = "/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/runs/";
  TString dir2="/uscms_data/d3/maral87/ttbarResonances/B2GAnaFW/CMSSW_7_4_12/src/Analysis/B2GTTbar/test/runs/run_022316/";

  TString files[150];
  files[names::DATA]          = dir2 +  "outBkgdEst_JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65_022316_nom.root";
  files[names::QCD]           = files[names::DATA];
  files[names::QCD_SYST]      = files[names::DATA];
  files[names::QCDMC]         = dir1 + "outBkgdEst_QCD_HT700toInf_B2Gv8p4_reader603e_notrig_021816_nom_scaled.root";
  files[names::QCDMC_SYST]    = files[names::QCDMC];
  files[names::TT]            = dir +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_020516_nom.root";
  files[names::TT_SUBTRACT]   = dir2 +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_022316_nom.root";
  files[names::TT_SUBTRACTSYST]   = dir2 +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_022316_nom.root";
  files[names::TT_JERUP]      = dir +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_020516_jer_up.root";
  files[names::TT_JERDN]      = dir +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_020516_jer_dn.root";
  files[names::TT_SCALEUP]    = dir +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_020516_jec_up.root";
  files[names::TT_SCALEDN]    = dir +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_020516_jec_dn.root";
  files[names::TT_PDFUP]      = dir1 +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_021816_pdf_up.root";
  files[names::TT_PDFDN]      = dir1 +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_021816_pdf_dn.root";
  files[names::TT_Q2UP]       = dir +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_020516_q2_up.root";
  files[names::TT_Q2DN]       = dir +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_020516_q2_dn.root";
  files[names::TT_BTAGUP]     = dir +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_020516_bTag_up.root";
  files[names::TT_BTAGDN]     = dir +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_020516_bTag_dn.root";

  files[names::ZPN10]         = dir +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_020516_nom.root";
  files[names::ZPN12p5]       = dir +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_020516_nom.root";
  files[names::ZPN15]         = dir +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_020516_nom.root";
  files[names::ZPN20]         = dir +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_020516_nom.root";
  files[names::ZPN25]         = dir +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_020516_nom.root";
  files[names::ZPN30]         = dir +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_020516_nom.root";
  files[names::ZPN35]         = dir +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_020516_nom.root";
  files[names::ZPN40]         = dir1 +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_020816_nom.root";

  files[names::ZPN10_SCALEUP] = dir +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_020516_jec_up.root";
  files[names::ZPN12p5_SCALEUP] = dir +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_020516_jec_up.root";
  files[names::ZPN15_SCALEUP] = dir +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_020516_jec_up.root";
  files[names::ZPN20_SCALEUP] = dir +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_020516_jec_up.root";
  files[names::ZPN25_SCALEUP] = dir +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_020516_jec_up.root";
  files[names::ZPN30_SCALEUP] = dir +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_020516_jec_up.root";
  files[names::ZPN35_SCALEUP] = dir +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_020516_jec_up.root";
  files[names::ZPN40_SCALEUP] = dir1 +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_020816_jec_up.root";
  files[names::ZPN10_SCALEDN] = dir +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_020516_jec_dn.root";
  files[names::ZPN12p5_SCALEDN] = dir +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_020516_jec_dn.root";
  files[names::ZPN15_SCALEDN] = dir +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_020516_jec_dn.root";
  files[names::ZPN20_SCALEDN] = dir +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_020516_jec_dn.root";
  files[names::ZPN25_SCALEDN] = dir +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_020516_jec_dn.root";
  files[names::ZPN30_SCALEDN] = dir +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_020516_jec_dn.root";
  files[names::ZPN35_SCALEDN] = dir +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_020516_jec_dn.root";
  files[names::ZPN40_SCALEDN] = dir1 +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_020816_jec_dn.root";

  files[names::ZPN10_JERUP]   = dir +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_020516_jer_up.root";
  files[names::ZPN12p5_JERUP]   = dir +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_020516_jer_up.root";
  files[names::ZPN15_JERUP]   = dir +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_020516_jer_up.root";
  files[names::ZPN20_JERUP]   = dir +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_020516_jer_up.root";
  files[names::ZPN25_JERUP]   = dir +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_020516_jer_up.root";
  files[names::ZPN30_JERUP]   = dir +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_020516_jer_up.root";
  files[names::ZPN35_JERUP]   = dir +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_020516_jer_up.root";
  files[names::ZPN40_JERUP]   = dir1 +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_020816_jer_up.root";
  files[names::ZPN10_JERDN]   = dir +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_020516_jer_dn.root";
  files[names::ZPN12p5_JERDN]   = dir +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_020516_jer_dn.root";
  files[names::ZPN15_JERDN]   = dir +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_020516_jer_dn.root";
  files[names::ZPN20_JERDN]   = dir +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_020516_jer_dn.root";
  files[names::ZPN25_JERDN]   = dir +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_020516_jer_dn.root";
  files[names::ZPN30_JERDN]   = dir +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_020516_jer_dn.root";
  files[names::ZPN35_JERDN]   = dir +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_020516_jer_dn.root";
  files[names::ZPN40_JERDN]   = dir1 +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_020816_jer_dn.root";

  files[names::ZPN10_PDFUP]   = dir1+  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_021816_pdf_up.root";
  files[names::ZPN12p5_PDFUP]   = dir1+  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_022216_pdf_up.root";
  files[names::ZPN15_PDFUP]   = dir1+  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_021816_pdf_up.root";
  files[names::ZPN20_PDFUP]   = dir1+  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_021816_pdf_up.root";
  files[names::ZPN25_PDFUP]   = dir1+  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_021816_pdf_up.root";
  files[names::ZPN30_PDFUP]   = dir1+  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_021816_pdf_up.root";
  files[names::ZPN35_PDFUP]   = dir1+  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_021816_pdf_up.root";
  files[names::ZPN40_PDFUP]   = dir1 +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_021816_pdf_up.root";
  files[names::ZPN10_PDFDN]   = dir1+  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_021816_pdf_dn.root";
  files[names::ZPN12p5_PDFDN]   = dir1+  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_022216_pdf_dn.root";
  files[names::ZPN15_PDFDN]   = dir1+  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_021816_pdf_dn.root";
  files[names::ZPN20_PDFDN]   = dir1+  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_021816_pdf_dn.root";
  files[names::ZPN25_PDFDN]   = dir1+  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_021816_pdf_dn.root";
  files[names::ZPN30_PDFDN]   = dir1+  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_021816_pdf_dn.root";
  files[names::ZPN35_PDFDN]   = dir1+  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_021816_pdf_dn.root";
  files[names::ZPN40_PDFDN]   = dir1 +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_021816_pdf_dn.root";

  files[names::ZPN10_BTAGUP]  = dir +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_020516_bTag_up.root";
  files[names::ZPN12p5_BTAGUP]  = dir +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_020516_bTag_up.root";
  files[names::ZPN15_BTAGUP]  = dir +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_020516_bTag_up.root";
  files[names::ZPN20_BTAGUP]  = dir +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_020516_bTag_up.root";
  files[names::ZPN25_BTAGUP]  = dir +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_020516_bTag_up.root";
  files[names::ZPN30_BTAGUP]  = dir +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_020516_bTag_up.root";
  files[names::ZPN35_BTAGUP]  = dir +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_020516_bTag_up.root";
  files[names::ZPN40_BTAGUP]  = dir1 +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_020816_bTag_up.root";
  files[names::ZPN10_BTAGDN]  = dir +  "outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e_020516_bTag_dn.root";
  files[names::ZPN12p5_BTAGDN]  = dir +  "outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e_020516_bTag_dn.root";
  files[names::ZPN15_BTAGDN]  = dir +  "outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e_020516_bTag_dn.root";
  files[names::ZPN20_BTAGDN]  = dir +  "outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e_020516_bTag_dn.root";
  files[names::ZPN25_BTAGDN]  = dir +  "outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e_020516_bTag_dn.root";
  files[names::ZPN30_BTAGDN]  = dir +  "outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e_020516_bTag_dn.root";
  files[names::ZPN35_BTAGDN]  = dir +  "outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e_020516_bTag_dn.root";
  files[names::ZPN40_BTAGDN]  = dir1 +  "outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e_020816_bTag_dn.root";

  int rebin_factor = 50;

  for (int proc = 0; proc < names::NUM_PROCS; proc++){


    cout << "Processing " << labels[proc] << endl;

    TFile *infile = new TFile(files[proc], "READ");

    if (proc != names::DATA && proc != names::QCD && proc != names::QCD_SYST && proc != names::TT_SUBTRACT && proc != names::TT_SUBTRACTSYST && proc != names::QCDMC && proc != names::QCDMC_SYST){
      histos[proc][0] = (TH1F *) infile->Get("h_mttMass_tagMassSDTau32_dRapLo_0btag");
      histos[proc][1] = (TH1F *) infile->Get("h_mttMass_tagMassSDTau32_dRapLo_1btag");
      histos[proc][2] = (TH1F *) infile->Get("h_mttMass_tagMassSDTau32_dRapLo_2btag");
      histos[proc][3] = (TH1F *) infile->Get("h_mttMass_tagMassSDTau32_dRapHi_0btag");
      histos[proc][4] = (TH1F *) infile->Get("h_mttMass_tagMassSDTau32_dRapHi_1btag");
      histos[proc][5] = (TH1F *) infile->Get("h_mttMass_tagMassSDTau32_dRapHi_2btag");
      histos[proc][6] = (TH1F *) infile->Get("h_mttMass_tagMassSDTau32_dRapLo_inclusive");
    }

    else if (proc == names::DATA or proc == names::QCDMC){

      histos[proc][0] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_0btag");
      histos[proc][1] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_1btag");
      histos[proc][2] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_2btag");
      histos[proc][3] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_0btag");
      histos[proc][4] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_1btag");
      histos[proc][5] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_2btag");
      histos[proc][6] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_inclusive");

    }

    else if (proc == names::QCD or proc == names::TT_SUBTRACT or proc == names::QCDMC_SYST){

      histos[proc][0] = (TH1F *) infile->Get("mttPredDist2_modMass_tagMassSDTau32_dRapLo_0btag_pred");
      histos[proc][1] = (TH1F *) infile->Get("mttPredDist2_modMass_tagMassSDTau32_dRapLo_1btag_pred");
      histos[proc][2] = (TH1F *) infile->Get("mttPredDist2_modMass_tagMassSDTau32_dRapLo_2btag_pred");
      histos[proc][3] = (TH1F *) infile->Get("mttPredDist2_modMass_tagMassSDTau32_dRapHi_0btag_pred");
      histos[proc][4] = (TH1F *) infile->Get("mttPredDist2_modMass_tagMassSDTau32_dRapHi_1btag_pred");
      histos[proc][5] = (TH1F *) infile->Get("mttPredDist2_modMass_tagMassSDTau32_dRapHi_2btag_pred");
      histos[proc][6] = (TH1F *) infile->Get("mttPredDist2_modMass_tagMassSDTau32_dRapLo_inclusive_pred");
    }

    else if (proc == names::QCD_SYST or proc == names::TT_SUBTRACTSYST){

      histos[proc][0] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_0btag_pred");
      histos[proc][1] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_1btag_pred");
      histos[proc][2] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_2btag_pred");
      histos[proc][3] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_0btag_pred");
      histos[proc][4] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_1btag_pred");
      histos[proc][5] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_2btag_pred");
      histos[proc][6] = (TH1F *) infile->Get("mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_inclusive_pred");
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

    else if (!constantBinning){
      Double_t xbins[257]  = {   0,  10,  20,  30,  40,  50,  60,  70,  80,  90,

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
      histos[proc][6] = (TH1F *) histos[proc][6]->Rebin(256, "h6", xbins);//rebin_factor);

    }

    else if (constantBinning){
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

  float lumi = 2592.3;
  float nttbar = 96834559.;//19665194.;
  float kfactor = 0.94;
  float ttSF = 0.89*0.89;

  for (int tag = 0; tag < nTagCats; tag++){
    cout<<"start of loop"<<endl;
    histos[names::QCD][tag]->SetMarkerSize(0);
    histos[names::TT_SCALEUP][tag]->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT_SCALEDN][tag]->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT_JERUP][tag]  ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT_JERDN][tag]  ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT_PDFUP][tag]  ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT_PDFDN][tag]  ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT_Q2UP][tag]   ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT_Q2DN][tag]   ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT_BTAGUP][tag] ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT_BTAGDN][tag] ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT][tag]        ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT_SUBTRACT][tag]->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
    histos[names::TT_SUBTRACTSYST][tag]->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );

    histos[names::ZPN10][tag]->Scale( 1. * ttSF * lumi / 98560. );
    histos[names::ZPN12p5][tag]->Scale( 1. * ttSF * lumi / 95730. );
    histos[names::ZPN15][tag]->Scale( 1. * ttSF * lumi / 97696. );
    histos[names::ZPN20][tag]->Scale( 1. * ttSF * lumi / 97600. );
    histos[names::ZPN25][tag]->Scale( 1. * ttSF * lumi / 99800. );
    histos[names::ZPN30][tag]->Scale( 1. * ttSF * lumi / 98668. );
    histos[names::ZPN35][tag]->Scale( 1. * ttSF * lumi / 97104. );
    histos[names::ZPN40][tag]->Scale( 1. * ttSF * lumi / 99554. );
    histos[names::ZPN10_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 98560. );
    histos[names::ZPN12p5_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 95730. );
    histos[names::ZPN15_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 97696. );
    histos[names::ZPN20_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 97600. );
    histos[names::ZPN25_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 99800. );
    histos[names::ZPN30_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 98668. );
    histos[names::ZPN35_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 97104. );
    histos[names::ZPN40_SCALEUP][tag]->Scale( 1. * ttSF * lumi / 99554. );
    histos[names::ZPN10_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 98560. );
    histos[names::ZPN12p5_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 95730. );
    histos[names::ZPN15_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 97696. );
    histos[names::ZPN20_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 97600. );
    histos[names::ZPN25_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 99800. );
    histos[names::ZPN30_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 98668. );
    histos[names::ZPN35_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 97104. );
    histos[names::ZPN40_SCALEDN][tag]->Scale( 1. * ttSF * lumi / 99554. );
    histos[names::ZPN10_JERUP][tag]  ->Scale( 1. * ttSF * lumi / 98560. );
    histos[names::ZPN12p5_JERUP][tag]  ->Scale( 1. * ttSF * lumi / 95730. );
    histos[names::ZPN15_JERUP][tag]  ->Scale( 1. * ttSF * lumi / 97696. );
    histos[names::ZPN20_JERUP][tag]  ->Scale( 1. * ttSF * lumi / 97600. );
    histos[names::ZPN25_JERUP][tag]  ->Scale( 1. * ttSF * lumi / 99800. );
    histos[names::ZPN30_JERUP][tag]  ->Scale( 1. * ttSF * lumi / 98668. );
    histos[names::ZPN35_JERUP][tag]  ->Scale( 1. * ttSF * lumi / 97104. );
    histos[names::ZPN40_JERUP][tag]  ->Scale( 1. * ttSF * lumi / 99554. );
    histos[names::ZPN10_JERDN][tag]  ->Scale( 1. * ttSF * lumi / 98560. );
    histos[names::ZPN12p5_JERDN][tag]  ->Scale( 1. * ttSF * lumi / 95730. );
    histos[names::ZPN15_JERDN][tag]  ->Scale( 1. * ttSF * lumi / 97696. );
    histos[names::ZPN20_JERDN][tag]  ->Scale( 1. * ttSF * lumi / 97600. );
    histos[names::ZPN25_JERDN][tag]  ->Scale( 1. * ttSF * lumi / 99800. );
    histos[names::ZPN30_JERDN][tag]  ->Scale( 1. * ttSF * lumi / 98668. );
    histos[names::ZPN35_JERDN][tag]  ->Scale( 1. * ttSF * lumi / 97104. );
    histos[names::ZPN40_JERDN][tag]  ->Scale( 1. * ttSF * lumi / 99554. );
    histos[names::ZPN10_PDFUP][tag]  ->Scale( 1. * ttSF * lumi / 98560. );
    histos[names::ZPN12p5_PDFUP][tag]  ->Scale( 1. * ttSF * lumi / 95730. );
    histos[names::ZPN15_PDFUP][tag]  ->Scale( 1. * ttSF * lumi / 97696. );
    histos[names::ZPN20_PDFUP][tag]  ->Scale( 1. * ttSF * lumi / 97600. );
    histos[names::ZPN25_PDFUP][tag]  ->Scale( 1. * ttSF * lumi / 99800. );
    histos[names::ZPN30_PDFUP][tag]  ->Scale( 1. * ttSF * lumi / 98668. );
    histos[names::ZPN35_PDFUP][tag]  ->Scale( 1. * ttSF * lumi / 97104. );
    histos[names::ZPN40_PDFUP][tag]  ->Scale( 1. * ttSF * lumi / 99554. );
    histos[names::ZPN10_PDFDN][tag]  ->Scale( 1. * ttSF * lumi / 98560. );
    histos[names::ZPN12p5_PDFDN][tag]  ->Scale( 1. * ttSF * lumi / 95730. );
    histos[names::ZPN15_PDFDN][tag]  ->Scale( 1. * ttSF * lumi / 97696. );
    histos[names::ZPN20_PDFDN][tag]  ->Scale( 1. * ttSF * lumi / 97600. );
    histos[names::ZPN25_PDFDN][tag]  ->Scale( 1. * ttSF * lumi / 99800. );
    histos[names::ZPN30_PDFDN][tag]  ->Scale( 1. * ttSF * lumi / 98668. );
    histos[names::ZPN35_PDFDN][tag]  ->Scale( 1. * ttSF * lumi / 97104. );
    histos[names::ZPN40_PDFDN][tag]  ->Scale( 1. * ttSF * lumi / 99554. );
    histos[names::ZPN10_BTAGUP][tag] ->Scale( 1. * ttSF * lumi / 98560. );
    histos[names::ZPN12p5_BTAGUP][tag] ->Scale( 1. * ttSF * lumi / 95730. );
    histos[names::ZPN15_BTAGUP][tag] ->Scale( 1. * ttSF * lumi / 97696. );
    histos[names::ZPN20_BTAGUP][tag] ->Scale( 1. * ttSF * lumi / 97600. );
    histos[names::ZPN25_BTAGUP][tag] ->Scale( 1. * ttSF * lumi / 99800. );
    histos[names::ZPN30_BTAGUP][tag] ->Scale( 1. * ttSF * lumi / 98668. );
    histos[names::ZPN35_BTAGUP][tag] ->Scale( 1. * ttSF * lumi / 97104. );
    histos[names::ZPN40_BTAGUP][tag] ->Scale( 1. * ttSF * lumi / 99554. );
    histos[names::ZPN10_BTAGDN][tag] ->Scale( 1. * ttSF * lumi / 98560. );
    histos[names::ZPN12p5_BTAGDN][tag] ->Scale( 1. * ttSF * lumi / 95730. );
    histos[names::ZPN15_BTAGDN][tag] ->Scale( 1. * ttSF * lumi / 97696. );
    histos[names::ZPN20_BTAGDN][tag] ->Scale( 1. * ttSF * lumi / 97600. );
    histos[names::ZPN25_BTAGDN][tag] ->Scale( 1. * ttSF * lumi / 99800. );
    histos[names::ZPN30_BTAGDN][tag] ->Scale( 1. * ttSF * lumi / 98668. );
    histos[names::ZPN35_BTAGDN][tag] ->Scale( 1. * ttSF * lumi / 97104. );
    histos[names::ZPN40_BTAGDN][tag] ->Scale( 1. * ttSF * lumi / 99554. );

    cout<<"end of loop"<<endl;
  } 


  for (int tag = 0; tag < 6; tag++){


    outFile->cd();
    cout << "TAG CATEGORY " << tag << endl;

    //ttbar subtraction
    histos[names::QCD][tag]->Add(histos[names::TT_SUBTRACT][tag],-1);
    histos[names::QCD_SYST][tag]->Add(histos[names::TT_SUBTRACTSYST][tag],-1);

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
    histos[names::TT_BTAGUP][tag]->Write( Form("btag%d__ttbar__btag__plus", tag) );
    histos[names::TT_BTAGDN][tag]->Write( Form("btag%d__ttbar__btag__minus", tag) );
    histos[names::TT_Q2UP][tag]->Write( Form("btag%d__ttbar__q2__plus", tag) );
    histos[names::TT_Q2DN][tag]->Write( Form("btag%d__ttbar__q2__minus", tag) );
    

    histos[names::ZPN10][tag]->Write( Form("btag%d__Zprime1000", tag));
    histos[names::ZPN12p5][tag]->Write( Form("btag%d__Zprime1250", tag));
    histos[names::ZPN15][tag]->Write( Form("btag%d__Zprime1500", tag) );
    histos[names::ZPN20][tag]->Write( Form("btag%d__Zprime2000", tag) );
    histos[names::ZPN25][tag]->Write( Form("btag%d__Zprime2500", tag) );
    histos[names::ZPN30][tag]->Write( Form("btag%d__Zprime3000", tag) );
    histos[names::ZPN35][tag]->Write( Form("btag%d__Zprime3500", tag) );  
    histos[names::ZPN40][tag]->Write( Form("btag%d__Zprime4000", tag) );  

    histos[names::ZPN10_SCALEUP][tag]->Write( Form("btag%d__Zprime1000__jec__plus", tag));
    histos[names::ZPN12p5_SCALEUP][tag]->Write( Form("btag%d__Zprime1250__jec__plus", tag));
    histos[names::ZPN15_SCALEUP][tag]->Write( Form("btag%d__Zprime1500__jec__plus", tag) );
    histos[names::ZPN20_SCALEUP][tag]->Write( Form("btag%d__Zprime2000__jec__plus", tag) );
    histos[names::ZPN25_SCALEUP][tag]->Write( Form("btag%d__Zprime2500__jec__plus", tag) );
    histos[names::ZPN30_SCALEUP][tag]->Write( Form("btag%d__Zprime3000__jec__plus", tag) );
    histos[names::ZPN35_SCALEUP][tag]->Write( Form("btag%d__Zprime3500__jec__plus", tag) ); 
    histos[names::ZPN40_SCALEUP][tag]->Write( Form("btag%d__Zprime4000__jec__plus", tag) ); 
    histos[names::ZPN10_SCALEDN][tag]->Write( Form("btag%d__Zprime1000__jec__minus", tag));
    histos[names::ZPN12p5_SCALEDN][tag]->Write( Form("btag%d__Zprime1250__jec__minus", tag));
    histos[names::ZPN15_SCALEDN][tag]->Write( Form("btag%d__Zprime1500__jec__minus", tag) );
    histos[names::ZPN20_SCALEDN][tag]->Write( Form("btag%d__Zprime2000__jec__minus", tag) );
    histos[names::ZPN25_SCALEDN][tag]->Write( Form("btag%d__Zprime2500__jec__minus", tag) );
    histos[names::ZPN30_SCALEDN][tag]->Write( Form("btag%d__Zprime3000__jec__minus", tag) );
    histos[names::ZPN35_SCALEDN][tag]->Write( Form("btag%d__Zprime3500__jec__minus", tag) );  
    histos[names::ZPN40_SCALEDN][tag]->Write( Form("btag%d__Zprime4000__jec__minus", tag) );  

    histos[names::ZPN10_JERUP][tag]->Write( Form("btag%d__Zprime1000__jer__plus", tag));
    histos[names::ZPN12p5_JERUP][tag]->Write( Form("btag%d__Zprime1250__jer__plus", tag));
    histos[names::ZPN15_JERUP][tag]->Write( Form("btag%d__Zprime1500__jer__plus", tag) );
    histos[names::ZPN20_JERUP][tag]->Write( Form("btag%d__Zprime2000__jer__plus", tag) );
    histos[names::ZPN25_JERUP][tag]->Write( Form("btag%d__Zprime2500__jer__plus", tag) );
    histos[names::ZPN30_JERUP][tag]->Write( Form("btag%d__Zprime3000__jer__plus", tag) );
    histos[names::ZPN35_JERUP][tag]->Write( Form("btag%d__Zprime3500__jer__plus", tag) ); 
    histos[names::ZPN40_JERUP][tag]->Write( Form("btag%d__Zprime4000__jer__plus", tag) ); 
    histos[names::ZPN10_JERDN][tag]->Write( Form("btag%d__Zprime1000__jer__minus", tag));
    histos[names::ZPN12p5_JERDN][tag]->Write( Form("btag%d__Zprime1250__jer__minus", tag));
    histos[names::ZPN15_JERDN][tag]->Write( Form("btag%d__Zprime1500__jer__minus", tag) );
    histos[names::ZPN20_JERDN][tag]->Write( Form("btag%d__Zprime2000__jer__minus", tag) );
    histos[names::ZPN25_JERDN][tag]->Write( Form("btag%d__Zprime2500__jer__minus", tag) );
    histos[names::ZPN30_JERDN][tag]->Write( Form("btag%d__Zprime3000__jer__minus", tag) );
    histos[names::ZPN35_JERDN][tag]->Write( Form("btag%d__Zprime3500__jer__minus", tag) );  
    histos[names::ZPN40_JERDN][tag]->Write( Form("btag%d__Zprime4000__jer__minus", tag) );  

    histos[names::ZPN10_PDFUP][tag]->Write( Form("btag%d__Zprime1000__pdf__plus", tag));
    histos[names::ZPN12p5_PDFUP][tag]->Write( Form("btag%d__Zprime1250__pdf__plus", tag));
    histos[names::ZPN15_PDFUP][tag]->Write( Form("btag%d__Zprime1500__pdf__plus", tag) );
    histos[names::ZPN20_PDFUP][tag]->Write( Form("btag%d__Zprime2000__pdf__plus", tag) );
    histos[names::ZPN25_PDFUP][tag]->Write( Form("btag%d__Zprime2500__pdf__plus", tag) );
    histos[names::ZPN30_PDFUP][tag]->Write( Form("btag%d__Zprime3000__pdf__plus", tag) );
    histos[names::ZPN35_PDFUP][tag]->Write( Form("btag%d__Zprime3500__pdf__plus", tag) ); 
    histos[names::ZPN40_PDFUP][tag]->Write( Form("btag%d__Zprime4000__pdf__plus", tag) ); 
    histos[names::ZPN10_PDFDN][tag]->Write( Form("btag%d__Zprime1000__pdf__minus", tag));
    histos[names::ZPN12p5_PDFDN][tag]->Write( Form("btag%d__Zprime1250__pdf__minus", tag));
    histos[names::ZPN15_PDFDN][tag]->Write( Form("btag%d__Zprime1500__pdf__minus", tag) );
    histos[names::ZPN20_PDFDN][tag]->Write( Form("btag%d__Zprime2000__pdf__minus", tag) );
    histos[names::ZPN25_PDFDN][tag]->Write( Form("btag%d__Zprime2500__pdf__minus", tag) );
    histos[names::ZPN30_PDFDN][tag]->Write( Form("btag%d__Zprime3000__pdf__minus", tag) );
    histos[names::ZPN35_PDFDN][tag]->Write( Form("btag%d__Zprime3500__pdf__minus", tag) );  
    histos[names::ZPN40_PDFDN][tag]->Write( Form("btag%d__Zprime4000__pdf__minus", tag) );  

    /*histos[names::ZPN10_Q2UP][tag]->Write( Form("btag%d__Zprime1000__q2__plus", tag));
    histos[names::ZPN12p5_Q2UP][tag]->Write( Form("btag%d__Zprime1250__q2__plus", tag));
    histos[names::ZPN15_Q2UP][tag]->Write( Form("btag%d__Zprime1500__q2__plus", tag) );
    histos[names::ZPN20_Q2UP][tag]->Write( Form("btag%d__Zprime2000__q2__plus", tag) );
    histos[names::ZPN25_Q2UP][tag]->Write( Form("btag%d__Zprime2500__q2__plus", tag) );
    histos[names::ZPN30_Q2UP][tag]->Write( Form("btag%d__Zprime3000__q2__plus", tag) );
    histos[names::ZPN35_Q2UP][tag]->Write( Form("btag%d__Zprime3500__q2__plus", tag) ); 
    histos[names::ZPN40_Q2UP][tag]->Write( Form("btag%d__Zprime4000__q2__plus", tag) ); 
    histos[names::ZPN10_Q2DN][tag]->Write( Form("btag%d__Zprime1000__q2__minus", tag));
    histos[names::ZPN12p5_Q2DN][tag]->Write( Form("btag%d__Zprime1250__q2__minus", tag));
    histos[names::ZPN15_Q2DN][tag]->Write( Form("btag%d__Zprime1500__q2__minus", tag) );
    histos[names::ZPN20_Q2DN][tag]->Write( Form("btag%d__Zprime2000__q2__minus", tag) );
    histos[names::ZPN25_Q2DN][tag]->Write( Form("btag%d__Zprime2500__q2__minus", tag) );
    histos[names::ZPN30_Q2DN][tag]->Write( Form("btag%d__Zprime3000__q2__minus", tag) );
    histos[names::ZPN35_Q2DN][tag]->Write( Form("btag%d__Zprime3500__q2__minus", tag) );  
    histos[names::ZPN40_Q2DN][tag]->Write( Form("btag%d__Zprime4000__q2__minus", tag) );  */

    histos[names::ZPN10_BTAGUP][tag]->Write( Form("btag%d__Zprime1000__btag__plus", tag));
    histos[names::ZPN12p5_BTAGUP][tag]->Write( Form("btag%d__Zprime1250__btag__plus", tag));
    histos[names::ZPN15_BTAGUP][tag]->Write( Form("btag%d__Zprime1500__btag__plus", tag) );
    histos[names::ZPN20_BTAGUP][tag]->Write( Form("btag%d__Zprime2000__btag__plus", tag) );
    histos[names::ZPN25_BTAGUP][tag]->Write( Form("btag%d__Zprime2500__btag__plus", tag) );
    histos[names::ZPN30_BTAGUP][tag]->Write( Form("btag%d__Zprime3000__btag__plus", tag) );
    histos[names::ZPN35_BTAGUP][tag]->Write( Form("btag%d__Zprime3500__btag__plus", tag) ); 
    histos[names::ZPN40_BTAGUP][tag]->Write( Form("btag%d__Zprime4000__btag__plus", tag) ); 
    histos[names::ZPN10_BTAGDN][tag]->Write( Form("btag%d__Zprime1000__btag__minus", tag));
    histos[names::ZPN12p5_BTAGDN][tag]->Write( Form("btag%d__Zprime1250__btag__minus", tag));
    histos[names::ZPN15_BTAGDN][tag]->Write( Form("btag%d__Zprime1500__btag__minus", tag) );
    histos[names::ZPN20_BTAGDN][tag]->Write( Form("btag%d__Zprime2000__btag__minus", tag) );
    histos[names::ZPN25_BTAGDN][tag]->Write( Form("btag%d__Zprime2500__btag__minus", tag) );
    histos[names::ZPN30_BTAGDN][tag]->Write( Form("btag%d__Zprime3000__btag__minus", tag) );
    histos[names::ZPN35_BTAGDN][tag]->Write( Form("btag%d__Zprime3500__btag__minus", tag) );  
    histos[names::ZPN40_BTAGDN][tag]->Write( Form("btag%d__Zprime4000__btag__minus", tag) );  


  }



outFile->Close();
return 0;

}
