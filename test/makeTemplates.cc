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

int makeTemplates(bool ZPNflag, bool ZPWflag, bool ZPXWflag, bool RSGflag){



  cout << names::NUM_PROCS << endl;

  int numProcs = names::NUM_PROCS;


  TFile *outFile = new TFile("templates.root", "RECREATE");



  TString labels[100];
  labels[names::DATA] = "data";
  labels[names::QCD]  = "qcd";
  labels[names::QCD_SYST]  = "qcdsyst";
  labels[names::TT] = "ttbar";
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

  TString dir = "/uscms_data/d3/maral87/ttbarResonances/B2GAnaFW/CMSSW_7_4_12/src/Analysis/B2GTTbar/test/runs/run_012716/run_012716_2/";

  TString files[100];
  files[names::DATA]          = dir +  "outBkgdEst_JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65_012716_nom.root";
  files[names::QCD]           = files[names::DATA];
  files[names::QCD_SYST]      = files[names::DATA];
  files[names::TT]            = dir +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_012716_nom.root";
  files[names::TT_JERUP]      = dir +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_012716_jer_up.root";
  files[names::TT_JERDN]      = dir +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_012716_jer_dn.root";
  files[names::TT_SCALEUP]    = dir +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_012716_jec_up.root";
  files[names::TT_SCALEDN]    = dir +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_012716_jec_dn.root";
  files[names::TT_PDFUP]      = dir +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_012716_pdf_up.root";
  files[names::TT_PDFDN]      = dir +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_012716_pdf_dn.root";
  files[names::TT_Q2UP]       = dir +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_012716_q2_up.root";
  files[names::TT_Q2DN]       = dir +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_012716_q2_dn.root";
  files[names::TT_BTAGUP]     = dir +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_012716_bTag_up.root";
  files[names::TT_BTAGDN]     = dir +  "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_012716_bTag_dn.root";

  files[names::ZPN10]         = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_012716_nom.root";
  files[names::ZPN12p5]         = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_012716_nom.root";
  files[names::ZPN15]         = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_012716_nom.root";
  files[names::ZPN20]         = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_012716_nom.root";
  files[names::ZPN25]         = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_012716_nom.root";
  files[names::ZPN30]         = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_012716_nom.root";
  files[names::ZPN35]         = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_012716_nom.root";
  files[names::ZPN40]         = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_012716_nom.root";
  
  files[names::ZPN10_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_012716_jec_up.root";
  files[names::ZPN12p5_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_012716_jec_up.root";
  files[names::ZPN15_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_012716_jec_up.root";
  files[names::ZPN20_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_012716_jec_up.root";
  files[names::ZPN25_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_012716_jec_up.root";
  files[names::ZPN30_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_012716_jec_up.root";
  files[names::ZPN35_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_012716_jec_up.root";
  files[names::ZPN40_SCALEUP] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_012716_jec_up.root";
  files[names::ZPN10_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_012716_jec_dn.root";
  files[names::ZPN12p5_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_012716_jec_dn.root";
  files[names::ZPN15_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_012716_jec_dn.root";
  files[names::ZPN20_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_012716_jec_dn.root";
  files[names::ZPN25_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_012716_jec_dn.root";
  files[names::ZPN30_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_012716_jec_dn.root";
  files[names::ZPN35_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_012716_jec_dn.root";
  files[names::ZPN40_SCALEDN] = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_012716_jec_dn.root";
  
  files[names::ZPN10_JERUP]   = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_012716_jer_up.root";
  files[names::ZPN12p5_JERUP]   = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_012716_jer_up.root";
  files[names::ZPN15_JERUP]   = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_012716_jer_up.root";
  files[names::ZPN20_JERUP]   = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_012716_jer_up.root";
  files[names::ZPN25_JERUP]   = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_012716_jer_up.root";
  files[names::ZPN30_JERUP]   = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_012716_jer_up.root";
  files[names::ZPN35_JERUP]   = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_012716_jer_up.root";
  files[names::ZPN40_JERUP]   = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_012716_jer_up.root";
  files[names::ZPN10_JERDN]   = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_012716_jer_dn.root";
  files[names::ZPN12p5_JERDN]   = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_012716_jer_dn.root";
  files[names::ZPN15_JERDN]   = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_012716_jer_dn.root";
  files[names::ZPN20_JERDN]   = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_012716_jer_dn.root";
  files[names::ZPN25_JERDN]   = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_012716_jer_dn.root";
  files[names::ZPN30_JERDN]   = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_012716_jer_dn.root";
  files[names::ZPN35_JERDN]   = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_012716_jer_dn.root";
  files[names::ZPN40_JERDN]   = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_012716_jer_dn.root";

  files[names::ZPN10_PDFUP]   = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_012716_pdf_up.root";
  files[names::ZPN12p5_PDFUP]   = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_012716_pdf_up.root";
  files[names::ZPN15_PDFUP]   = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_012716_pdf_up.root";
  files[names::ZPN20_PDFUP]   = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_012716_pdf_up.root";
  files[names::ZPN25_PDFUP]   = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_012716_pdf_up.root";
  files[names::ZPN30_PDFUP]   = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_012716_pdf_up.root";
  files[names::ZPN35_PDFUP]   = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_012716_pdf_up.root";
  files[names::ZPN40_PDFUP]   = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_012716_pdf_up.root";
  files[names::ZPN10_PDFDN]   = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_012716_pdf_dn.root";
  files[names::ZPN12p5_PDFDN]   = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_012716_pdf_dn.root";
  files[names::ZPN15_PDFDN]   = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_012716_pdf_dn.root";
  files[names::ZPN20_PDFDN]   = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_012716_pdf_dn.root";
  files[names::ZPN25_PDFDN]   = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_012716_pdf_dn.root";
  files[names::ZPN30_PDFDN]   = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_012716_pdf_dn.root";
  files[names::ZPN35_PDFDN]   = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_012716_pdf_dn.root";
  files[names::ZPN40_PDFDN]   = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_012716_pdf_dn.root";
 
  /*files[names::ZPN10_Q2UP]    = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_012716_q2_up.root";
  files[names::ZPN12p5_Q2UP]    = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_012716_q2_up.root";
  files[names::ZPN15_Q2UP]    = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_012716_q2_up.root";
  files[names::ZPN20_Q2UP]    = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_012716_q2_up.root";
  files[names::ZPN25_Q2UP]    = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_012716_q2_up.root";
  files[names::ZPN30_Q2UP]    = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_012716_q2_up.root";
  files[names::ZPN35_Q2UP]    = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_012716_q2_up.root";
  files[names::ZPN40_Q2UP]    = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_012716_q2_up.root";
  files[names::ZPN10_Q2DN]    = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_012716_q2_dn.root";
  files[names::ZPN12p5_Q2DN]    = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_012716_q2_dn.root";
  files[names::ZPN15_Q2DN]    = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_012716_q2_dn.root";
  files[names::ZPN20_Q2DN]    = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_012716_q2_dn.root";
  files[names::ZPN25_Q2DN]    = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_012716_q2_dn.root";
  files[names::ZPN30_Q2DN]    = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_012716_q2_dn.root";
  files[names::ZPN35_Q2DN]    = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_012716_q2_dn.root";
  files[names::ZPN40_Q2DN]    = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_012716_q2_dn.root";*/
   
  files[names::ZPN10_BTAGUP]  = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_012716_bTag_up.root";
  files[names::ZPN12p5_BTAGUP]  = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_012716_bTag_up.root";
  files[names::ZPN15_BTAGUP]  = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_012716_bTag_up.root";
  files[names::ZPN20_BTAGUP]  = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_012716_bTag_up.root";
  files[names::ZPN25_BTAGUP]  = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_012716_bTag_up.root";
  files[names::ZPN30_BTAGUP]  = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_012716_bTag_up.root";
  files[names::ZPN35_BTAGUP]  = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_012716_bTag_up.root";
  files[names::ZPN40_BTAGUP]  = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_012716_bTag_up.root";
  files[names::ZPN10_BTAGDN]  = dir +  "outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e_012716_bTag_dn.root";
  files[names::ZPN12p5_BTAGDN]  = dir +  "outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e_012716_bTag_dn.root";
  files[names::ZPN15_BTAGDN]  = dir +  "outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e_012716_bTag_dn.root";
  files[names::ZPN20_BTAGDN]  = dir +  "outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e_012716_bTag_dn.root";
  files[names::ZPN25_BTAGDN]  = dir +  "outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e_012716_bTag_dn.root";
  files[names::ZPN30_BTAGDN]  = dir +  "outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e_012716_bTag_dn.root";
  files[names::ZPN35_BTAGDN]  = dir +  "outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e_012716_bTag_dn.root";
  files[names::ZPN40_BTAGDN]  = dir +  "outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e_012716_bTag_dn.root";

  for (int proc = 0; proc < names::NUM_PROCS; proc++){


    cout << "Processing " << labels[proc] << endl;

    TFile *infile = new TFile(files[proc], "READ");


    histos[proc][0] = (TH1F *) infile->Get("h_mttMass_tagMassSDTau32_dRapLo_0btag");
    histos[proc][1] = (TH1F *) infile->Get("h_mttMass_tagMassSDTau32_dRapLo_1btag");
    histos[proc][2] = (TH1F *) infile->Get("h_mttMass_tagMassSDTau32_dRapLo_2btag");
    histos[proc][3] = (TH1F *) infile->Get("h_mttMass_tagMassSDTau32_dRapHi_0btag");
    histos[proc][4] = (TH1F *) infile->Get("h_mttMass_tagMassSDTau32_dRapHi_1btag");
    histos[proc][5] = (TH1F *) infile->Get("h_mttMass_tagMassSDTau32_dRapHi_2btag");
    histos[proc][6] = (TH1F *) infile->Get("h_mttMass_tagMassSDTau32_dRapLo_inclusive");

    if (proc == names::QCD){
      
      histos[proc][0] = (TH1F *) infile->Get("h_bkgdEst_modMass_tagMassSDTau32_dRapLo_0btag");      //"mttPredDist_modMass_tagMassSDTau32_dRapLo_0btag_pred");     //"h_bkgdEst_tagMassSDTau32_dRapLo_0btag");
      histos[proc][1] = (TH1F *) infile->Get("h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag");      //"mttPredDist_modMass_tagMassSDTau32_dRapLo_1btag_pred");     //"h_bkgdEst_tagMassSDTau32_dRapLo_1btag");
      histos[proc][2] = (TH1F *) infile->Get("h_bkgdEst_modMass_tagMassSDTau32_dRapLo_2btag");      //"mttPredDist_modMass_tagMassSDTau32_dRapLo_2btag_pred");     //"h_bkgdEst_tagMassSDTau32_dRapLo_2btag");
      histos[proc][3] = (TH1F *) infile->Get("h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag");      //"mttPredDist_modMass_tagMassSDTau32_dRapHi_0btag_pred");     //"h_bkgdEst_tagMassSDTau32_dRapHi_0btag");
      histos[proc][4] = (TH1F *) infile->Get("h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag");      //"mttPredDist_modMass_tagMassSDTau32_dRapHi_1btag_pred");     //"h_bkgdEst_tagMassSDTau32_dRapHi_1btag");
      histos[proc][5] = (TH1F *) infile->Get("h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag");      //"mttPredDist_modMass_tagMassSDTau32_dRapHi_2btag_pred");     //"h_bkgdEst_tagMassSDTau32_dRapHi_2btag");
      histos[proc][6] = (TH1F *) infile->Get("h_bkgdEst_modMass_tagMassSDTau32_dRapLo_inclusive");  //"mttPredDist_modMass_tagMassSDTau32_dRapLo_inclusive_pred"); //"h_bkgdEst_tagMassSDTau32_dRapLo_inclusive");
    }

    if (proc == names::QCD_SYST){
      
      histos[proc][0] = (TH1F *) infile->Get("h_bkgdEst_tagMassSDTau32_dRapLo_0btag");      //Get("mttPredDist_tagMassSDTau32_dRapLo_0btag_pred");     //"h_bkgdEst_tagMassSDTau32_dRapLo_0btag");
      histos[proc][1] = (TH1F *) infile->Get("h_bkgdEst_tagMassSDTau32_dRapLo_1btag");      //Get("mttPredDist_tagMassSDTau32_dRapLo_1btag_pred");     //"h_bkgdEst_tagMassSDTau32_dRapLo_1btag");
      histos[proc][2] = (TH1F *) infile->Get("h_bkgdEst_tagMassSDTau32_dRapLo_2btag");      //Get("mttPredDist_tagMassSDTau32_dRapLo_2btag_pred");     //"h_bkgdEst_tagMassSDTau32_dRapLo_2btag");
      histos[proc][3] = (TH1F *) infile->Get("h_bkgdEst_tagMassSDTau32_dRapHi_0btag");      //Get("mttPredDist_tagMassSDTau32_dRapHi_0btag_pred");     //"h_bkgdEst_tagMassSDTau32_dRapHi_0btag");
      histos[proc][4] = (TH1F *) infile->Get("h_bkgdEst_tagMassSDTau32_dRapHi_1btag");      //Get("mttPredDist_tagMassSDTau32_dRapHi_1btag_pred");     //"h_bkgdEst_tagMassSDTau32_dRapHi_1btag");
      histos[proc][5] = (TH1F *) infile->Get("h_bkgdEst_tagMassSDTau32_dRapHi_2btag");      //Get("mttPredDist_tagMassSDTau32_dRapHi_2btag_pred");     //"h_bkgdEst_tagMassSDTau32_dRapHi_2btag");
      histos[proc][6] = (TH1F *) infile->Get("h_bkgdEst_tagMassSDTau32_dRapLo_inclusive");  //Get("mttPredDist_tagMassSDTau32_dRapLo_inclusive_pred"); //"h_bkgdEst_tagMassSDTau32_dRapLo_inclusive");

    }

   
    cout << histos[proc][0]->Integral() << endl;
  

    int rebin_factor = 5;
  
    histos[proc][0]->Rebin(rebin_factor);
    histos[proc][1]->Rebin(rebin_factor);
    histos[proc][2]->Rebin(rebin_factor);
    histos[proc][3]->Rebin(rebin_factor);
    histos[proc][4]->Rebin(rebin_factor);
    histos[proc][5]->Rebin(rebin_factor);
    histos[proc][6]->Rebin(rebin_factor);


    
  }


  float lumi = 2564.649;
  float nttbar = 96834559.;//19665194.;
  float kfactor = 0.8;


  for (int tag = 0; tag < nTagCats; tag++){
    cout<<"start of loop"<<endl;
    histos[names::QCD][tag]->SetMarkerSize(0);
    histos[names::TT_SCALEUP][tag]->Scale( 831.76 * lumi * kfactor / nttbar );
    histos[names::TT_SCALEDN][tag]->Scale( 831.76 * lumi * kfactor / nttbar );
    histos[names::TT_JERUP][tag]  ->Scale( 831.76 * lumi * kfactor / nttbar );
    histos[names::TT_JERDN][tag]  ->Scale( 831.76 * lumi * kfactor / nttbar );
    histos[names::TT_PDFUP][tag]  ->Scale( 831.76 * lumi * kfactor / nttbar );
    histos[names::TT_PDFDN][tag]  ->Scale( 831.76 * lumi * kfactor / nttbar );
    histos[names::TT_Q2UP][tag]   ->Scale( 831.76 * lumi * kfactor / nttbar );
    histos[names::TT_Q2DN][tag]   ->Scale( 831.76 * lumi * kfactor / nttbar );
    histos[names::TT_BTAGUP][tag] ->Scale( 831.76 * lumi * kfactor / nttbar );
    histos[names::TT_BTAGDN][tag] ->Scale( 831.76 * lumi * kfactor / nttbar );
    histos[names::TT][tag]        ->Scale( 831.76 * lumi * kfactor / nttbar );

    histos[names::ZPN10][tag]->Scale( 1. * lumi / 122204. ); 
    histos[names::ZPN12p5][tag]->Scale( 1. * lumi / 114611. ); 
    histos[names::ZPN15][tag]->Scale( 1. * lumi / 108916. ); 
    histos[names::ZPN20][tag]->Scale( 1. * lumi / 202573. ); 
    histos[names::ZPN25][tag]->Scale( 1. * lumi / 118319. ); 
    histos[names::ZPN30][tag]->Scale( 1. * lumi / 117069. ); 
    histos[names::ZPN35][tag]->Scale( 1. * lumi / 113527. );
    histos[names::ZPN40][tag]->Scale( 1. * lumi / 111625. );
    histos[names::ZPN10_SCALEUP][tag]->Scale( 1. * lumi / 122204. ); 
    histos[names::ZPN12p5_SCALEUP][tag]->Scale( 1. * lumi / 114611. ); 
    histos[names::ZPN15_SCALEUP][tag]->Scale( 1. * lumi / 108916. ); 
    histos[names::ZPN20_SCALEUP][tag]->Scale( 1. * lumi / 202573. ); 
    histos[names::ZPN25_SCALEUP][tag]->Scale( 1. * lumi / 118319. ); 
    histos[names::ZPN30_SCALEUP][tag]->Scale( 1. * lumi / 117069. ); 
    histos[names::ZPN35_SCALEUP][tag]->Scale( 1. * lumi / 113527. );
    histos[names::ZPN40_SCALEUP][tag]->Scale( 1. * lumi / 111625. );
    histos[names::ZPN10_SCALEDN][tag]->Scale( 1. * lumi / 122204. ); 
    histos[names::ZPN12p5_SCALEDN][tag]->Scale( 1. * lumi / 114611. ); 
    histos[names::ZPN15_SCALEDN][tag]->Scale( 1. * lumi / 108916. ); 
    histos[names::ZPN20_SCALEDN][tag]->Scale( 1. * lumi / 202573. ); 
    histos[names::ZPN25_SCALEDN][tag]->Scale( 1. * lumi / 118319. ); 
    histos[names::ZPN30_SCALEDN][tag]->Scale( 1. * lumi / 117069. ); 
    histos[names::ZPN35_SCALEDN][tag]->Scale( 1. * lumi / 113527. );
    histos[names::ZPN40_SCALEDN][tag]->Scale( 1. * lumi / 111625. );
    histos[names::ZPN10_JERUP][tag]  ->Scale( 1. * lumi / 122204. ); 
    histos[names::ZPN12p5_JERUP][tag]  ->Scale( 1. * lumi / 114611. ); 
    histos[names::ZPN15_JERUP][tag]  ->Scale( 1. * lumi / 108916. ); 
    histos[names::ZPN20_JERUP][tag]  ->Scale( 1. * lumi / 202573. ); 
    histos[names::ZPN25_JERUP][tag]  ->Scale( 1. * lumi / 118319. ); 
    histos[names::ZPN30_JERUP][tag]  ->Scale( 1. * lumi / 117069. ); 
    histos[names::ZPN35_JERUP][tag]  ->Scale( 1. * lumi / 113527. );
    histos[names::ZPN40_JERUP][tag]  ->Scale( 1. * lumi / 111625. );
    histos[names::ZPN10_JERDN][tag]  ->Scale( 1. * lumi / 122204. ); 
    histos[names::ZPN12p5_JERDN][tag]  ->Scale( 1. * lumi / 114611. ); 
    histos[names::ZPN15_JERDN][tag]  ->Scale( 1. * lumi / 108916. ); 
    histos[names::ZPN20_JERDN][tag]  ->Scale( 1. * lumi / 202573. ); 
    histos[names::ZPN25_JERDN][tag]  ->Scale( 1. * lumi / 118319. ); 
    histos[names::ZPN30_JERDN][tag]  ->Scale( 1. * lumi / 117069. ); 
    histos[names::ZPN35_JERDN][tag]  ->Scale( 1. * lumi / 113527. );
    histos[names::ZPN40_JERDN][tag]  ->Scale( 1. * lumi / 111625. );
    histos[names::ZPN10_PDFUP][tag]  ->Scale( 1. * lumi / 122204. ); 
    histos[names::ZPN12p5_PDFUP][tag]  ->Scale( 1. * lumi / 114611. ); 
    histos[names::ZPN15_PDFUP][tag]  ->Scale( 1. * lumi / 108916. ); 
    histos[names::ZPN20_PDFUP][tag]  ->Scale( 1. * lumi / 202573. ); 
    histos[names::ZPN25_PDFUP][tag]  ->Scale( 1. * lumi / 118319. ); 
    histos[names::ZPN30_PDFUP][tag]  ->Scale( 1. * lumi / 117069. ); 
    histos[names::ZPN35_PDFUP][tag]  ->Scale( 1. * lumi / 113527. );
    histos[names::ZPN40_PDFUP][tag]  ->Scale( 1. * lumi / 111625. );
    histos[names::ZPN10_PDFDN][tag]  ->Scale( 1. * lumi / 122204. ); 
    histos[names::ZPN12p5_PDFDN][tag]  ->Scale( 1. * lumi / 114611. ); 
    histos[names::ZPN15_PDFDN][tag]  ->Scale( 1. * lumi / 108916. ); 
    histos[names::ZPN20_PDFDN][tag]  ->Scale( 1. * lumi / 202573. ); 
    histos[names::ZPN25_PDFDN][tag]  ->Scale( 1. * lumi / 118319. ); 
    histos[names::ZPN30_PDFDN][tag]  ->Scale( 1. * lumi / 117069. ); 
    histos[names::ZPN35_PDFDN][tag]  ->Scale( 1. * lumi / 113527. );
    histos[names::ZPN40_PDFDN][tag]  ->Scale( 1. * lumi / 111625. );
    /*histos[names::ZPN10_Q2UP][tag]   ->Scale( 1. * lumi / 122204. ); 
    histos[names::ZPN12p5_Q2UP][tag]   ->Scale( 1. * lumi / 114611. ); 
    histos[names::ZPN15_Q2UP][tag]   ->Scale( 1. * lumi / 108916. ); 
    histos[names::ZPN20_Q2UP][tag]   ->Scale( 1. * lumi / 202573. ); 
    histos[names::ZPN25_Q2UP][tag]   ->Scale( 1. * lumi / 118319. ); 
    histos[names::ZPN30_Q2UP][tag]   ->Scale( 1. * lumi / 117069. ); 
    histos[names::ZPN35_Q2UP][tag]   ->Scale( 1. * lumi / 113527. );
    histos[names::ZPN40_Q2UP][tag]   ->Scale( 1. * lumi / 111625. );
    histos[names::ZPN10_Q2DN][tag]   ->Scale( 1. * lumi / 122204. ); 
    histos[names::ZPN12p5_Q2DN][tag]   ->Scale( 1. * lumi / 114611. ); 
    histos[names::ZPN15_Q2DN][tag]   ->Scale( 1. * lumi / 108916. ); 
    histos[names::ZPN20_Q2DN][tag]   ->Scale( 1. * lumi / 202573. ); 
    histos[names::ZPN25_Q2DN][tag]   ->Scale( 1. * lumi / 118319. ); 
    histos[names::ZPN30_Q2DN][tag]   ->Scale( 1. * lumi / 117069. ); 
    histos[names::ZPN35_Q2DN][tag]   ->Scale( 1. * lumi / 113527. );
    histos[names::ZPN40_Q2DN][tag]   ->Scale( 1. * lumi / 111625. );*/
    histos[names::ZPN10_BTAGUP][tag] ->Scale( 1. * lumi / 122204. ); 
    histos[names::ZPN12p5_BTAGUP][tag] ->Scale( 1. * lumi / 114611. ); 
    histos[names::ZPN15_BTAGUP][tag] ->Scale( 1. * lumi / 108916. ); 
    histos[names::ZPN20_BTAGUP][tag] ->Scale( 1. * lumi / 202573. ); 
    histos[names::ZPN25_BTAGUP][tag] ->Scale( 1. * lumi / 118319. ); 
    histos[names::ZPN30_BTAGUP][tag] ->Scale( 1. * lumi / 117069. ); 
    histos[names::ZPN35_BTAGUP][tag] ->Scale( 1. * lumi / 113527. );
    histos[names::ZPN40_BTAGUP][tag] ->Scale( 1. * lumi / 111625. );
    histos[names::ZPN10_BTAGDN][tag] ->Scale( 1. * lumi / 122204. ); 
    histos[names::ZPN12p5_BTAGDN][tag] ->Scale( 1. * lumi / 114611. ); 
    histos[names::ZPN15_BTAGDN][tag] ->Scale( 1. * lumi / 108916. ); 
    histos[names::ZPN20_BTAGDN][tag] ->Scale( 1. * lumi / 202573. ); 
    histos[names::ZPN25_BTAGDN][tag] ->Scale( 1. * lumi / 118319. ); 
    histos[names::ZPN30_BTAGDN][tag] ->Scale( 1. * lumi / 117069. ); 
    histos[names::ZPN35_BTAGDN][tag] ->Scale( 1. * lumi / 113527. );
    histos[names::ZPN40_BTAGDN][tag] ->Scale( 1. * lumi / 111625. );

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
    histos[names::ZPN10][tag]->SetLineWidth(2);
    histos[names::ZPN20][tag]->SetLineWidth(2);
    histos[names::ZPN30][tag]->SetLineWidth(2);

    histos[names::ZPN10][tag]->Draw("hist same");
    histos[names::ZPN20][tag]->Draw("hist same");
    histos[names::ZPN30][tag]->Draw("hist same");


    TH1F *totalH = (TH1F *) histos[names::QCD][tag]->Clone("totalH");
    totalH->Add(histos[names::TT][tag]);
    totalH->SetFillStyle(3004);
        totalH->SetFillColor(kBlack);
        totalH->Draw("same E2");


    TLatex *cmsLabel = new TLatex();
    cmsLabel->SetNDC();
    cmsLabel->DrawLatex(0.1,0.91, "CMS Preliminary, #sqrt{s} = 13 TeV, 2.56 fb^{-1}");

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
    leg->AddEntry(histos[names::ZPN10][tag], "1 TeV Narrow Z'", "l");
    leg->AddEntry(histos[names::ZPN20][tag], "2 TeV Narrow Z'", "l");
    leg->AddEntry(histos[names::ZPN30][tag], "3 TeV Narrow Z'", "l");
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


    c1->SaveAs("errors"+tagLabels[tag]+".pdf");
    c1->SaveAs("errors"+tagLabels[tag]+".png");
    c1_2->SetLogy(1);
    c1->SaveAs("errors"+tagLabels[tag]+"_log.pdf");
    c1->SaveAs("errors"+tagLabels[tag]+"_log.png");

    cout<<"end of loop"<<endl;
  } 


  for (int tag = 0; tag < 6; tag++){


    outFile->cd();
    cout << "TAG CATEGORY " << tag << endl;

    histos[names::QCD][tag]->Write( Form("btag%d__qcd", tag) );
    histos[names::QCD_SYST][tag]->Write( Form("btag%d__qcdsyst", tag) );
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
    

    bool writeZPN = ZPNflag;
    if (writeZPN){
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


  }



outFile->Close();
return 0;

}
