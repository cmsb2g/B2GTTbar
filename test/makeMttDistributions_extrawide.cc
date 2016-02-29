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

void makeMttDistributions_extrawide(){

  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0000000000); //this clears all the boxes and crap 

  cout << names::NUM_PROCS << endl;

  int numProcs = names::NUM_PROCS;

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

  TString files[100];
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

  files[names::ZPN10] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_020516_nom.root";
  files[names::ZPN12p5] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_020516_nom.root";                          
  files[names::ZPN15] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_020516_nom.root";                          
  files[names::ZPN20] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_020516_nom.root";
  files[names::ZPN25] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_020516_nom.root";                          
  files[names::ZPN30] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_020516_nom.root";
  files[names::ZPN35] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_020516_nom.root";                         
  files[names::ZPN40] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_020516_nom.root";

  files[names::ZPN10_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_020516_jec_up.root";
  files[names::ZPN12p5_SCALEUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_020516_jec_up.root";               
  files[names::ZPN15_SCALEUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_020516_jec_up.root";               
  files[names::ZPN20_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_020516_jec_up.root";
  files[names::ZPN25_SCALEUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_020516_jec_up.root";               
  files[names::ZPN30_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_020516_jec_up.root";
  files[names::ZPN35_SCALEUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_020516_jec_up.root";              
  files[names::ZPN40_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_020516_jec_up.root";
  files[names::ZPN10_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_020516_jec_dn.root";
  files[names::ZPN12p5_SCALEDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_020516_jec_dn.root";               
  files[names::ZPN15_SCALEDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_020516_jec_dn.root";               
  files[names::ZPN20_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_020516_jec_dn.root";
  files[names::ZPN25_SCALEDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_020516_jec_dn.root";               
  files[names::ZPN30_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_020516_jec_dn.root";
  files[names::ZPN35_SCALEDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_020516_jec_dn.root";              
  files[names::ZPN40_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_020516_jec_dn.root";

  files[names::ZPN10_JERUP] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_020516_jer_up.root";
  files[names::ZPN12p5_JERUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_020516_jer_up.root";                 
  files[names::ZPN15_JERUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_020516_jer_up.root";                 
  files[names::ZPN20_JERUP] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_020516_jer_up.root";
  files[names::ZPN25_JERUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_020516_jer_up.root";                 
  files[names::ZPN30_JERUP] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_020516_jer_up.root";
  files[names::ZPN35_JERUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_020516_jer_up.root";                
  files[names::ZPN40_JERUP] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_020516_jer_up.root";
  files[names::ZPN10_JERDN] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_020516_jer_dn.root";
  files[names::ZPN12p5_JERDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_020516_jer_dn.root";                 
  files[names::ZPN15_JERDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_020516_jer_dn.root";                 
  files[names::ZPN20_JERDN] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_020516_jer_dn.root";
  files[names::ZPN25_JERDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_020516_jer_dn.root";                 
  files[names::ZPN30_JERDN] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_020516_jer_dn.root";
  files[names::ZPN35_JERDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_020516_jer_dn.root";                
  files[names::ZPN40_JERDN] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_020516_jer_dn.root";

  files[names::ZPN10_BTAGUP] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_020516_bTag_up.root";
  files[names::ZPN12p5_BTAGUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_020516_bTag_up.root";               
  files[names::ZPN15_BTAGUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_020516_bTag_up.root";               
  files[names::ZPN20_BTAGUP] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_020516_bTag_up.root";
  files[names::ZPN25_BTAGUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_020516_bTag_up.root";               
  files[names::ZPN30_BTAGUP] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_020516_bTag_up.root";
  files[names::ZPN35_BTAGUP] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_020516_bTag_up.root";              
  files[names::ZPN40_BTAGUP] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_020516_bTag_up.root";
  files[names::ZPN10_BTAGDN] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_020516_bTag_dn.root";
  files[names::ZPN12p5_BTAGDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_020516_bTag_dn.root";               
  files[names::ZPN15_BTAGDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_020516_bTag_dn.root";               
  files[names::ZPN20_BTAGDN] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_020516_bTag_dn.root";
  files[names::ZPN25_BTAGDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_020516_bTag_dn.root";               
  files[names::ZPN30_BTAGDN] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_020516_bTag_dn.root";
  files[names::ZPN35_BTAGDN] = files[names::ZPN10];//dir +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_020516_bTag_dn.root";              
  files[names::ZPN40_BTAGDN] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_020516_bTag_dn.root";

  files[names::ZPN10_PDFUP] = dir1 +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_021616_pdf_up.root";
  files[names::ZPN12p5_PDFUP] = files[names::ZPN10];//dir1 +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_021616_pdf_up.root";                 
  files[names::ZPN15_PDFUP] = files[names::ZPN10];//dir1 +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_021616_pdf_up.root";                 
  files[names::ZPN20_PDFUP] = dir1 +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_021616_pdf_up.root";
  files[names::ZPN25_PDFUP] = files[names::ZPN10];//dir1 +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_021616_pdf_up.root";                 
  files[names::ZPN30_PDFUP] = dir1 +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_021616_pdf_up.root";
  files[names::ZPN35_PDFUP] = files[names::ZPN10];//dir1 +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_021616_pdf_up.root";                
  files[names::ZPN40_PDFUP] = dir1 +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_021616_pdf_up.root";
  files[names::ZPN10_PDFDN] = dir1 +  "outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e_021616_pdf_dn.root";
  files[names::ZPN12p5_PDFDN] = files[names::ZPN10];//dir1 +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_021616_pdf_dn.root";                 
  files[names::ZPN15_PDFDN] = files[names::ZPN10];//dir1 +  "outBkgdEst_ZprimeToTT_M-1500_W-450_B2Gv8p4_reader603e_021616_pdf_dn.root";                 
  files[names::ZPN20_PDFDN] = dir1 +  "outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e_021616_pdf_dn.root";
  files[names::ZPN25_PDFDN] = files[names::ZPN10];//dir1 +  "outBkgdEst_ZprimeToTT_M-2500_W-750_B2Gv8p4_reader603e_021616_pdf_dn.root";                 
  files[names::ZPN30_PDFDN] = dir1 +  "outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e_021616_pdf_dn.root";
  files[names::ZPN35_PDFDN] = files[names::ZPN10];//dir1 +  "outBkgdEst_ZprimeToTT_M-3500_W-1050_B2Gv8p4_reader603e_021616_pdf_dn.root";                
  files[names::ZPN40_PDFDN] = dir1 +  "outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e_021616_pdf_dn.root";

  for (int proc = 0; proc < names::NUM_PROCS; proc++){

    TFile *infile = new TFile(files[proc], "READ");

    cout << "Processing " << labels[proc] << endl;

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

    int rebin_factor = 5;

    histos[proc][0]->Rebin(rebin_factor);
    histos[proc][1]->Rebin(rebin_factor);
    histos[proc][2]->Rebin(rebin_factor);
    histos[proc][3]->Rebin(rebin_factor);
    histos[proc][4]->Rebin(rebin_factor);
    histos[proc][5]->Rebin(rebin_factor);
    histos[proc][6]->Rebin(rebin_factor);

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


    //ttbar subtraction
    histos[names::QCD][tag]->Add(histos[names::TT_SUBTRACT][tag],-1);
    histos[names::QCD_SYST][tag]->Add(histos[names::TT_SUBTRACTSYST][tag],-1);
    
    histos[names::DATA][tag]->SetMaximum(1.4 * histos[names::DATA][tag]->GetMaximum() );
    histos[names::DATA][tag]->SetMarkerStyle(20);
    histos[names::DATA][tag]->GetYaxis()->SetTitle("Events");
    histos[names::DATA][tag]->Draw("E");  

    THStack *stack = new THStack();
    stack->Add(histos[names::TT][tag]);
    stack->Add(histos[names::QCD][tag]);
    stack->Draw("hist same");
    histos[names::DATA][tag]->SetMarkerStyle(21);
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

    //errors
    TH1F *totalH = (TH1F *) histos[names::QCD][tag]->Clone("totalH");
    totalH->Add(histos[names::TT][tag]);

    int n_xbins = totalH->GetNbinsX();
    float xsErr_top = 0.15;
    float lumiErr = 0.027;
    float topTagErr = 2*(0.09/0.89);

    for (int i_bin = 0; i_bin < n_xbins; i_bin++){
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
      float qcdSystErr = 0.5*abs( histos[names::QCD][tag]->GetBinContent(i_bin) - histos[names::QCD_SYST][tag]->GetBinContent(i_bin) );

      float diffClose = 0.0;
      if (histos[names::QCDMC][tag]->GetBinContent(i_bin) != 0){
        diffClose = abs( histos[names::QCDMC][tag]->GetBinContent(i_bin) - histos[names::QCDMC_SYST][tag]->GetBinContent(i_bin) )/(histos[names::QCDMC][tag]->GetBinContent(i_bin));
      }
      float closeErr = diffClose*(histos[names::QCD][tag]->GetBinContent(i_bin));

      float TOTALErr = sqrt(statErr*statErr + scaleErr*scaleErr + jerErr*jerErr + pdfErr*pdfErr + q2Err*q2Err + btagErr*btagErr + qcdSystErr*qcdSystErr + xsErr_top*xsErr_top + lumiErr*lumiErr + topTagErr*topTagErr + closeErr*closeErr);
      totalH->SetBinError(i_bin,TOTALErr);
    }
    
    totalH->SetFillStyle(3004);
    totalH->SetFillColor(kBlack);
    totalH->Draw("E2 same");

    TLatex *cmsLabel = new TLatex();
    cmsLabel->SetNDC();
    cmsLabel->DrawLatex(0.1,0.91, "CMS Preliminary, #sqrt{s} = 13 TeV, 2.59 fb^{-1}");

    if (tag == 0) cmsLabel->DrawLatex(0.7, 0.85, "0 b-tags, |#Deltay| < 1.0");
    if (tag == 1) cmsLabel->DrawLatex(0.7, 0.85, "1 b-tags, |#Deltay| < 1.0");
    if (tag == 2) cmsLabel->DrawLatex(0.7, 0.85, "2 b-tags, |#Deltay| < 1.0");
    if (tag == 3) cmsLabel->DrawLatex(0.7, 0.85, "0 b-tags, |#Deltay| > 1.0");
    if (tag == 4) cmsLabel->DrawLatex(0.7, 0.85, "1 b-tags, |#Deltay| > 1.0");
    if (tag == 5) cmsLabel->DrawLatex(0.7, 0.85, "2 b-tags, |#Deltay| > 1.0");
    if (tag == 6) cmsLabel->DrawLatex(0.7, 0.85, "All Signal Regions");



    gPad->RedrawAxis();
    
    TLegend *leg = new TLegend(0.7, 0.4, 0.94, 0.8);
    leg->AddEntry(histos[names::DATA][tag], "Data", "lp");
    leg->AddEntry(histos[names::QCD][tag], "NTMJ", "f");
    leg->AddEntry(histos[names::TT][tag], "Top", "f");
    leg->AddEntry(histos[names::ZPN10][tag], "1 TeV Extra Wide Z'", "l");
    leg->AddEntry(histos[names::ZPN20][tag], "2 TeV Extra Wide Z'", "l");
    leg->AddEntry(histos[names::ZPN30][tag], "3 TeV Extra Wide Z'", "l");
    leg->AddEntry(histos[names::ZPN40][tag], "4 TeV Extra Wide Z'", "l");
    leg->SetFillColor(0);
    leg->SetLineColor(0);
    leg->Draw("same");


    TH1F *ratioH = new TH1F();
    ratioH = (TH1F*) histos[names::DATA][tag]->Clone("ratio");
    ratioH->Sumw2();
    ratioH->Divide(ratioH, totalH, 1, 1, "B");


    c1_1->cd();
    c1_1->SetTopMargin(0.01);
    c1_1->SetBottomMargin(0.3);
    c1_1->SetRightMargin(0.05);
    c1_1->SetLeftMargin(0.1);
    c1_1->SetFillStyle(0);

    ratioH->GetYaxis()->SetRangeUser(0.,2.);
    ratioH->GetYaxis()->SetTitle("Data / BG Ratio");
    ratioH->GetYaxis()->SetTitleOffset(0.4);
    ratioH->GetYaxis()->SetTitleSize(0.11);
    ratioH->GetXaxis()->SetLabelSize(0.11);
    ratioH->GetXaxis()->SetTitleSize(0.11);
    ratioH->GetXaxis()->SetTitle( "t#bar{t} Invariant Mass [GeV]");
    ratioH->Draw("E");
    

    TF1 *line = new TF1("line", "1", 0, 5000);
    line->SetLineColor(kBlack);
    line->Draw("same");
    
    gPad->RedrawAxis();


    c1->SaveAs("Distributions/ZPXW_errors"+tagLabels[tag]+".pdf");
    c1->SaveAs("Distributions/ZPXW_errors"+tagLabels[tag]+".png");
    c1_2->SetLogy(1);
    c1->SaveAs("Distributions/ZPXW_errors"+tagLabels[tag]+"_log.pdf");
    c1->SaveAs("Distributions/ZPXW_errors"+tagLabels[tag]+"_log.png");

    cout<<"end of loop"<<endl;
  } 

return 0;

}
