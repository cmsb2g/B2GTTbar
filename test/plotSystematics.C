#include "TROOT.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH1.h"
#include "THStack.h"
#include "TH2.h"
#include "TF1.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TMath.h"
#include <TStyle.h>

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <cmath>

using namespace std;

void plotterSyst(
  string histname, 
  string histtitle, 
  string pave, 
  string pave2, 
  string samplelabel,
  string sample,
  string systLabel,
  TH1D* hNom1, TH1D* hUp1, TH1D* hDn1, 
  bool legswitch, 
  bool invert, 
  double xmax, 
  double yscale,
  int rebin,
  string savefolder );

void plotterSyst_ttW(
  string histname, 
  string histtitle, 
  string pave, 
  string samplelabel,
  string sample,
  string systLabel,
  TH1D* hNom1, TH1D* hUp1, 
  bool legswitch, 
  bool invert, 
  double xmin, 
  double xmax, 
  double yscale,
  int rebin,
  string savefolder );

void run(){

	TCanvas *c1237= new TCanvas("c1237","",1,1,745,640);
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


	//gStyle->SetLegendFont(42);
	gStyle->SetOptStat(0);
	gROOT->SetBatch(); 
	gROOT->UseCurrentStyle();
	gROOT->ForceStyle();


	string savefolder = "./plots_Systematic_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw/";
	// string infolder = "/Users/jdolen/NoBackup/B2G2016/V5/runs/";
    string infolder = "/uscms_data/d2/jdolen/B2G2016/CMSSW_8_0_26_patch2/src/Analysis/B2GTTbar/test/runs/";

	string runlabel = "20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw";

	vector<string> sample;
	vector<string> endstring;
	vector<string> samplelabel;
	vector<double> dijet_xmax;


	sample.push_back("RSGluonToTT_M-1500");  endstring.push_back(""); samplelabel.push_back("RS Gluon (1500 GeV)" );  dijet_xmax.push_back(3000);
	sample.push_back("RSGluonToTT_M-3000");  endstring.push_back(""); samplelabel.push_back("RS Gluon (3000 GeV)" );  dijet_xmax.push_back(5000);

	sample.push_back("ZprimeToTT_M-1500_W-15");  endstring.push_back(""); samplelabel.push_back("Z` (1500 GeV narrow)" );  dijet_xmax.push_back(3000);
	sample.push_back("ZprimeToTT_M-3000_W-30");  endstring.push_back("");  samplelabel.push_back("Z` (3000 GeV narrow)" );  dijet_xmax.push_back(5000);
	sample.push_back("ZprimeToTT_M-5000_W-50");  endstring.push_back("");  samplelabel.push_back("Z` (5000 GeV narrow)" );  dijet_xmax.push_back(8000);
	sample.push_back("ZprimeToTT_M-1500_W-150"); endstring.push_back("");  samplelabel.push_back("Z` (1500 GeV wide)" );  dijet_xmax.push_back(3000);
	sample.push_back("ZprimeToTT_M-3000_W-300"); endstring.push_back("");  samplelabel.push_back("Z` (3000 GeV wide)" );  dijet_xmax.push_back(5000);
	sample.push_back("ZprimeToTT_M-5000_W-500"); endstring.push_back("");  samplelabel.push_back("Z` (5000 GeV wide)" );  dijet_xmax.push_back(8000);
	// sample.push_back("ZprimeToTT_M-4000_W-400"); endstring.push_back("");  samplelabel.push_back("Z` (4000 GeV wide)" );  dijet_xmax.push_back(5000); 
	sample.push_back("TT_TuneCUETP8M2T4_13TeV-powheg-pythia8"); endstring.push_back("_orig_and_backup_missing2");  samplelabel.push_back("t#bar{t}" );  dijet_xmax.push_back(4000); 

	for (unsigned int is=0; is< sample.size(); is++ ){
	// TFile * f_nom      = new TFile( ( infolder+"histsKinemat_"+runlabel+"_nom_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root"     ).c_str()    );        
	// TFile * f_PU_dn    = new TFile( ( infolder+"histsKinemat_"+runlabel+"_PU_dn_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root"   ).c_str()    );              
	// TFile * f_PU_up    = new TFile( ( infolder+"histsKinemat_"+runlabel+"_PU_up_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root"   ).c_str()    );              
	// TFile * f_bTag_dn  = new TFile( ( infolder+"histsKinemat_"+runlabel+"_bTag_dn_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root" ).c_str()    );                
	// TFile * f_bTag_up  = new TFile( ( infolder+"histsKinemat_"+runlabel+"_bTag_up_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root" ).c_str()    );                
	// TFile * f_jec_dn   = new TFile( ( infolder+"histsKinemat_"+runlabel+"_jec_dn_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root"  ).c_str()    );               
	// TFile * f_jec_up   = new TFile( ( infolder+"histsKinemat_"+runlabel+"_jec_up_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root"  ).c_str()    );               
	// TFile * f_jer_dn   = new TFile( ( infolder+"histsKinemat_"+runlabel+"_jer_dn_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root"  ).c_str()    );               
	// TFile * f_jer_up   = new TFile( ( infolder+"histsKinemat_"+runlabel+"_jer_up_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root"  ).c_str()    );               
	// TFile * f_pdf_dn   = new TFile( ( infolder+"histsKinemat_"+runlabel+"_pdf_dn_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root"  ).c_str()    );               
	// TFile * f_pdf_up   = new TFile( ( infolder+"histsKinemat_"+runlabel+"_pdf_up_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root"  ).c_str()    );               
	// TFile * f_q2_dn    = new TFile( ( infolder+"histsKinemat_"+runlabel+"_q2_dn_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root"   ).c_str()    );              
	// TFile * f_q2_up    = new TFile( ( infolder+"histsKinemat_"+runlabel+"_q2_up_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root"   ).c_str()    );              

	TFile * f_nom      = new TFile( ( infolder+"histsBkgdEst_"+runlabel+"_nom_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root"     ).c_str()    );        
	TFile * f_PU_dn    = new TFile( ( infolder+"histsBkgdEst_"+runlabel+"_PU_dn_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root"   ).c_str()    );              
	TFile * f_PU_up    = new TFile( ( infolder+"histsBkgdEst_"+runlabel+"_PU_up_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root"   ).c_str()    );              
	TFile * f_bTag_dn  = new TFile( ( infolder+"histsBkgdEst_"+runlabel+"_bTag_dn_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root" ).c_str()    );                
	TFile * f_bTag_up  = new TFile( ( infolder+"histsBkgdEst_"+runlabel+"_bTag_up_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root" ).c_str()    );                
	TFile * f_jec_dn   = new TFile( ( infolder+"histsBkgdEst_"+runlabel+"_jec_dn_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root"  ).c_str()    );               
	TFile * f_jec_up   = new TFile( ( infolder+"histsBkgdEst_"+runlabel+"_jec_up_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root"  ).c_str()    );               
	TFile * f_jer_dn   = new TFile( ( infolder+"histsBkgdEst_"+runlabel+"_jer_dn_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root"  ).c_str()    );               
	TFile * f_jer_up   = new TFile( ( infolder+"histsBkgdEst_"+runlabel+"_jer_up_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root"  ).c_str()    );               
	TFile * f_pdf_dn   = new TFile( ( infolder+"histsBkgdEst_"+runlabel+"_pdf_dn_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root"  ).c_str()    );               
	TFile * f_pdf_up   = new TFile( ( infolder+"histsBkgdEst_"+runlabel+"_pdf_up_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root"  ).c_str()    );               
	TFile * f_q2_dn    = new TFile( ( infolder+"histsBkgdEst_"+runlabel+"_q2_dn_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root"   ).c_str()    );              
	TFile * f_q2_up    = new TFile( ( infolder+"histsBkgdEst_"+runlabel+"_q2_up_b2gtreeV5_"+sample[is]+"_RunIISummer16MiniAODv2"+endstring[is]+".root"   ).c_str()    );              





	vector<string> histnames;
	vector<string> histtitle;
	vector<string> pave2     ;
	vector<int>    rebin    ;
	vector<int>    xmin    ;
	vector<int>    xmax    ;

	// histnames.push_back("h_DijetMass"                                  ); histtitle.push_back("DijetMass"                                  ); rebin.push_back( 4 );                     
	// histnames.push_back("h_DijetMassPuppi"                             ); histtitle.push_back("DijetMassPuppi"                             ); rebin.push_back( 4 );                     

	// histnames.push_back("h_CutFlow"                                    ); histtitle.push_back("CutFlow"                                    ); rebin.push_back( 1 );  xmax.push_back( -1 );  
	// histnames.push_back("h_JetSDmass"                                  ); histtitle.push_back("JetSDmass"                                  ); rebin.push_back( 2 );  xmax.push_back( -1 );  
	// histnames.push_back("h_BtagCategoriesPostSF"                       ); histtitle.push_back("BtagCategoriesPostSF"                       ); rebin.push_back( 1 );  xmax.push_back( -1 );  
	// histnames.push_back("h_DoublePupTag_BtagCategoriesPostSF"          ); histtitle.push_back("DoublePupTag_BtagCategoriesPostSF"          ); rebin.push_back( 1 );  xmax.push_back( -1 );  
	// histnames.push_back("h_DijetMass_dRapIn"                           ); histtitle.push_back("DijetMass_dRapIn"                           ); rebin.push_back( 4 );  xmax.push_back(dijet_xmax[is]);  
	// histnames.push_back("h_DijetMass_dRapHi"                           ); histtitle.push_back("DijetMass_dRapHi"                           ); rebin.push_back( 4 );  xmax.push_back(dijet_xmax[is]);  
	// histnames.push_back("h_DijetMass_dRapLo"                           ); histtitle.push_back("DijetMass_dRapLo"                           ); rebin.push_back( 4 );  xmax.push_back(dijet_xmax[is]);  
	// histnames.push_back("h_Jet0Pt"                                     ); histtitle.push_back("Jet0Pt"                                     ); rebin.push_back( 10 );  xmax.push_back( 2000 );  
	// histnames.push_back("h_Jet0SDmass_matchedTop"                      ); histtitle.push_back("Jet0SDmass_matchedTop"                      ); rebin.push_back( 4 );  xmax.push_back( -1 );  
	// histnames.push_back("h_Jet0SDmass_matchedTop_topDist"              ); histtitle.push_back("Jet0SDmass_matchedTop_topDist"              ); rebin.push_back( 4 );  xmax.push_back( -1 );  
	// histnames.push_back("h_Jet0SDmass_Pt1400_all"                      ); histtitle.push_back("Jet0SDmass_Pt1400_all"                      ); rebin.push_back( 4 );  xmax.push_back( -1 );  
	// histnames.push_back("h_Jet0SDmass_TauTag_all"                      ); histtitle.push_back("Jet0SDmass_TauTag_all"                      ); rebin.push_back( 4 );  xmax.push_back( -1 );  
	// histnames.push_back("h_pup_JetSDmass"                              ); histtitle.push_back("pup_JetSDmass"                              ); rebin.push_back( 4 );  xmax.push_back( -1 );  
	// histnames.push_back("h_pup_JetSDmass_JetTag_b"                     ); histtitle.push_back("pup_JetSDmass_JetTag_b"                     ); rebin.push_back( 4 );  xmax.push_back( -1 );  
	// histnames.push_back("h_pup_JetSDmass_JetTag_tau32"                 ); histtitle.push_back("pup_JetSDmass_JetTag_tau32"                 ); rebin.push_back( 4 );  xmax.push_back( -1 );  
	// histnames.push_back("h_pup_JetSDmass_JetTag_b_tau32"               ); histtitle.push_back("pup_JetSDmass_JetTag_b_tau32"               ); rebin.push_back( 4 );  xmax.push_back( -1 );  
	// histnames.push_back("h_DijetMass_masspuptag"                       ); histtitle.push_back("DijetMass_masspuptag"                       ); rebin.push_back( 4 );  xmax.push_back(dijet_xmax[is]);                          
	// histnames.push_back("h_DijetMass_masspuptag_puppitau32_lt0p80"     ); histtitle.push_back("DijetMass_masspuptag_puppitau32_lt0p80"     ); rebin.push_back( 4 );  xmax.push_back(dijet_xmax[is]);                                            
	// histnames.push_back("h_DijetMass_1btag_masspuptag"                 ); histtitle.push_back("DijetMass_1btag_masspuptag"                 ); rebin.push_back( 4 );  xmax.push_back(dijet_xmax[is]);                                
	// histnames.push_back("h_DijetMass_2btag_masspuptag"                 ); histtitle.push_back("DijetMass_2btag_masspuptag"                 ); rebin.push_back( 4 );  xmax.push_back(dijet_xmax[is]);                                
	// histnames.push_back("h_DijetMass_0btag_masspuptag"                 ); histtitle.push_back("DijetMass_0btag_masspuptag"                 ); rebin.push_back( 4 );  xmax.push_back(dijet_xmax[is]);                                
	// histnames.push_back("h_2ttag_inclu_dRapIn_DijetMass"               ); histtitle.push_back("2ttag_inclu_dRapIn_DijetMass"               ); rebin.push_back( 4 );  xmax.push_back(dijet_xmax[is]);                                  
	// histnames.push_back("h_2ttag_0btag_dRapIn_DijetMass"               ); histtitle.push_back("2ttag_0btag_dRapIn_DijetMass"               ); rebin.push_back( 4 );  xmax.push_back(dijet_xmax[is]);                                  
	// histnames.push_back("h_2ttag_1btag_dRapIn_DijetMass"               ); histtitle.push_back("2ttag_1btag_dRapIn_DijetMass"               ); rebin.push_back( 4 );  xmax.push_back(dijet_xmax[is]);                                  
	// histnames.push_back("h_2ttag_2btag_dRapIn_DijetMass"               ); histtitle.push_back("2ttag_2btag_dRapIn_DijetMass"               ); rebin.push_back( 4 );  xmax.push_back(dijet_xmax[is]);                                  
	// histnames.push_back("h_2ttag_inclu_dRapLo_DijetMass"               ); histtitle.push_back("2ttag_inclu_dRapLo_DijetMass"               ); rebin.push_back( 4 );  xmax.push_back(dijet_xmax[is]);                                  
	// histnames.push_back("h_2ttag_0btag_dRapLo_DijetMass"               ); histtitle.push_back("2ttag_0btag_dRapLo_DijetMass"               ); rebin.push_back( 4 );  xmax.push_back(dijet_xmax[is]);                                  
	// histnames.push_back("h_2ttag_1btag_dRapLo_DijetMass"               ); histtitle.push_back("2ttag_1btag_dRapLo_DijetMass"               ); rebin.push_back( 4 );  xmax.push_back(dijet_xmax[is]);                                  
	// histnames.push_back("h_2ttag_2btag_dRapLo_DijetMass"               ); histtitle.push_back("2ttag_2btag_dRapLo_DijetMass"               ); rebin.push_back( 4 );  xmax.push_back(dijet_xmax[is]);                                  
	// histnames.push_back("h_2ttag_inclu_dRapHi_DijetMass"               ); histtitle.push_back("2ttag_inclu_dRapHi_DijetMass"               ); rebin.push_back( 4 );  xmax.push_back(dijet_xmax[is]);                                  
	// histnames.push_back("h_2ttag_0btag_dRapHi_DijetMass"               ); histtitle.push_back("2ttag_0btag_dRapHi_DijetMass"               ); rebin.push_back( 4 );  xmax.push_back(dijet_xmax[is]);                                  
	// histnames.push_back("h_2ttag_1btag_dRapHi_DijetMass"               ); histtitle.push_back("2ttag_1btag_dRapHi_DijetMass"               ); rebin.push_back( 4 );  xmax.push_back(dijet_xmax[is]);                                  
	// histnames.push_back("h_2ttag_2btag_dRapHi_DijetMass"               ); histtitle.push_back("2ttag_2btag_dRapHi_DijetMass"               ); rebin.push_back( 4 );  xmax.push_back(dijet_xmax[is]);                                  
	// histnames.push_back("h_2btag_DijetMass"                            ); histtitle.push_back("2btag_DijetMass"                            ); rebin.push_back( 1 );  xmax.push_back( -1 );                     

	histnames.push_back("predDist_Puppi_SR_dRapHi_0btag_DijetMass"        ); histtitle.push_back("Dijet mass [GeV]"   ); pave2.push_back("#DeltaY>1.0, 0 b-tag"); rebin.push_back( 20 );  xmax.push_back( dijet_xmax[is] ); 
	histnames.push_back("predDist_Puppi_SR_dRapHi_1btag_DijetMass"        ); histtitle.push_back("Dijet mass [GeV]"   ); pave2.push_back("#DeltaY>1.0, 1 b-tag"); rebin.push_back( 20 );  xmax.push_back( dijet_xmax[is] ); 
	histnames.push_back("predDist_Puppi_SR_dRapHi_2btag_DijetMass"        ); histtitle.push_back("Dijet mass [GeV]"   ); pave2.push_back("#DeltaY>1.0, 2 b-tag"); rebin.push_back( 20 );  xmax.push_back( dijet_xmax[is] ); 
	histnames.push_back("predDist_Puppi_SR_dRapLo_0btag_DijetMass"        ); histtitle.push_back("Dijet mass [GeV]"   ); pave2.push_back("#DeltaY<1.0, 0 b-tag"); rebin.push_back( 20 );  xmax.push_back( dijet_xmax[is] ); 
	histnames.push_back("predDist_Puppi_SR_dRapLo_1btag_DijetMass"        ); histtitle.push_back("Dijet mass [GeV]"   ); pave2.push_back("#DeltaY<1.0, 1 b-tag"); rebin.push_back( 20 );  xmax.push_back( dijet_xmax[is] ); 
	histnames.push_back("predDist_Puppi_SR_dRapLo_2btag_DijetMass"        ); histtitle.push_back("Dijet mass [GeV]"   ); pave2.push_back("#DeltaY<1.0, 2 b-tag"); rebin.push_back( 20 );  xmax.push_back( dijet_xmax[is] ); 


	// htitle.push_back("Jet softdrop mass [GeV]"                            );  hrebin.push_back(5);   legs.push_back(false);  QCDonTop.push_back(false);   xmax.push_back( -1); yscale.push_back(1.5);  pave.push_back("H_{T} > 1000 GeV, p_{T} > 500 GeV, |#eta|<2.4");
           

	for (unsigned int i=0; i< histnames.size(); i++ ){

		TH1D * h_nom      = (TH1D*) f_nom     ->Get( histnames[i].c_str() ); 
		TH1D * h_PU_dn    = (TH1D*) f_PU_dn   ->Get( histnames[i].c_str() ); 
		TH1D * h_PU_up    = (TH1D*) f_PU_up   ->Get( histnames[i].c_str() ); 
		TH1D * h_bTag_dn  = (TH1D*) f_bTag_dn ->Get( histnames[i].c_str() ); 
		TH1D * h_bTag_up  = (TH1D*) f_bTag_up ->Get( histnames[i].c_str() ); 
		TH1D * h_jec_dn   = (TH1D*) f_jec_dn  ->Get( histnames[i].c_str() ); 
		TH1D * h_jec_up   = (TH1D*) f_jec_up  ->Get( histnames[i].c_str() ); 
		TH1D * h_jer_dn   = (TH1D*) f_jer_dn  ->Get( histnames[i].c_str() ); 
		TH1D * h_jer_up   = (TH1D*) f_jer_up  ->Get( histnames[i].c_str() ); 
		TH1D * h_pdf_dn   = (TH1D*) f_pdf_dn  ->Get( histnames[i].c_str() ); 
		TH1D * h_pdf_up   = (TH1D*) f_pdf_up  ->Get( histnames[i].c_str() ); 
		TH1D * h_q2_dn    = (TH1D*) f_q2_dn   ->Get( histnames[i].c_str() ); 
		TH1D * h_q2_up    = (TH1D*) f_q2_up   ->Get( histnames[i].c_str() ); 


		h_nom      ->SetLineWidth(2);
		h_PU_dn    ->SetLineWidth(2);
		h_PU_up    ->SetLineWidth(2);
		h_bTag_dn  ->SetLineWidth(2);
		h_bTag_up  ->SetLineWidth(2);
		h_jec_dn   ->SetLineWidth(2);
		h_jec_up   ->SetLineWidth(2);
		h_jer_dn   ->SetLineWidth(2);
		h_jer_up   ->SetLineWidth(2);
		h_pdf_dn   ->SetLineWidth(2);
		h_pdf_up   ->SetLineWidth(2);
		h_q2_dn    ->SetLineWidth(2);
		h_q2_up    ->SetLineWidth(2);

		h_nom      ->SetLineColor(1);
		h_PU_dn    ->SetLineColor(2);
		h_PU_up    ->SetLineColor(4);
		h_bTag_dn  ->SetLineColor(2);
		h_bTag_up  ->SetLineColor(4);
		h_jec_dn   ->SetLineColor(2);
		h_jec_up   ->SetLineColor(4);
		h_jer_dn   ->SetLineColor(2);
		h_jer_up   ->SetLineColor(4);
		h_pdf_dn   ->SetLineColor(2);
		h_pdf_up   ->SetLineColor(4);
		h_q2_dn    ->SetLineColor(2);
		h_q2_up    ->SetLineColor(4);

		// h_nom   ->Draw("HIST");
		// h_PU_dn ->Draw("HISTsame");
		// h_PU_up ->Draw("HISTsame");

		plotterSyst(
			histnames[i], 
			histtitle[i], 
			"PU systematic variations", 
			pave2[i], 
			samplelabel[is],
			sample[is],
			"PU",
			h_nom, h_PU_up, h_PU_dn, 
			false, //bool legswitch, 
			false, //bool invert, 
			xmax[i], //double xmax, 
			1.3, // yscale,
			rebin[i],
			savefolder 
		);

		// string savename = savefolder+"h_"+sample[is]+"_syst_PU_"+histnames[i] +".pdf";
		// c1237->SaveAs( savename.c_str() );

		// h_nom     ->Draw("HIST");
		// h_bTag_dn ->Draw("HISTsame");
		// h_bTag_up ->Draw("HISTsame");

		plotterSyst(
			histnames[i], 
			histtitle[i], 
			"b-tag systematic variations", 
			pave2[i], 
			samplelabel[is],
			sample[is],
			"bTag",
			h_nom, h_bTag_up, h_bTag_dn, 
			false, //bool legswitch, 
			false, //bool invert, 
			xmax[i], //double xmax, 
			1.3, // yscale,
			rebin[i],
			savefolder 
		);

		// savename = savefolder+"h_"+sample[is]+"_syst_bTag_"+histnames[i] +".pdf";
		// c1237->SaveAs( savename.c_str() );
		
		// h_nom    ->Draw("HIST");
		// h_jec_dn ->Draw("HISTsame");
		// h_jec_up ->Draw("HISTsame");

		plotterSyst(
			histnames[i], 
			histtitle[i], 
			"JEC systematic variations",
			pave2[i], 
			samplelabel[is],
			sample[is],
			"jec",
			h_nom, h_jec_up, h_jec_dn, 
			false, //bool legswitch, 
			false, //bool invert, 
			xmax[i], //double xmax, 
			1.3, // yscale,
			rebin[i],
			savefolder 
		);

		// savename = savefolder+"h_"+sample[is]+"_syst_jec_"+histnames[i] +".pdf";
		// c1237->SaveAs( savename.c_str() );
		
		// h_nom    ->Draw("HIST");
		// h_jer_dn ->Draw("HISTsame");
		// h_jer_up ->Draw("HISTsame");

		plotterSyst(
			histnames[i], 
			histtitle[i], 
			"JER systematic variations", 
			pave2[i],
			samplelabel[is],
			sample[is],
			"jer",
			h_nom, h_jer_up, h_jer_dn, 
			false, //bool legswitch, 
			false, //bool invert, 
			xmax[i], //double xmax, 
			1.3, // yscale,
			rebin[i],
			savefolder 
		);

		// savename = savefolder+"h_"+sample[is]+"_syst_jer_"+histnames[i] +".pdf";
		// c1237->SaveAs( savename.c_str() );
		
		plotterSyst(
			histnames[i], 
			histtitle[i], 
			"PDF systematic variations",
			pave2[i],
			samplelabel[is], 
			sample[is],
			"pdf",
			h_nom, h_pdf_up, h_pdf_dn, 
			false, //bool legswitch, 
			false, //bool invert, 
			xmax[i], //double xmax, 
			1.3, // yscale,
			rebin[i],
			savefolder 
		);

		// h_nom    ->Draw("HIST");
		// h_pdf_dn ->Draw("HISTsame");
		// h_pdf_up ->Draw("HISTsame");

		// savename = savefolder+"h_"+sample[is]+"_syst_pdf_"+histnames[i] +".pdf";
		// c1237->SaveAs( savename.c_str() );

		plotterSyst(
			histnames[i], 
			histtitle[i], 
			"Q^{2} systematic variations",
			pave2[i],
			samplelabel[is], 
			sample[is],
			"q2",
			h_nom, h_q2_up, h_q2_dn, 
			false, //bool legswitch, 
			false, //bool invert, 
			xmax[i], //double xmax, 
			1.3, // yscale,
			rebin[i],
			savefolder 
		);

		// h_nom    ->Draw("HIST");
		// h_q2_dn  ->Draw("HISTsame");
		// h_q2_up  ->Draw("HISTsame");

		// savename = savefolder+"h_"+sample[is]+"_syst_q2_"+histnames[i] +".pdf";
		// c1237->SaveAs( savename.c_str() );
	}
}
	
}


void runTTw(){


	TCanvas *c1237= new TCanvas("c1237","",1,1,745,640);
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


	//gStyle->SetLegendFont(42);
	gStyle->SetOptStat(0);
	gROOT->SetBatch(); 
	gROOT->UseCurrentStyle();
	gROOT->ForceStyle();


	string savefolder = "plots_Systematic_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw/";
	// string infolder = "/Users/jdolen/NoBackup/B2G2016/V5/runs/";
    string infolder = "/uscms_data/d2/jdolen/B2G2016/CMSSW_8_0_26_patch2/src/Analysis/B2GTTbar/test/runs/";

	string runlabel = "20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw";


	double dijet_xmax = 4000;
	TFile * f_noTTw     = new TFile( ( infolder+"histsKinemat_"+runlabel+"_noTTw_nom_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root"     ).c_str()    );        
	TFile * f_TTw       = new TFile( ( infolder+"histsKinemat_"+runlabel+"_TTw_nom_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root" ).c_str()     );  



	vector<string> histnames;
	vector<string> histtitle;
	vector<string> label;
	vector<int>    rebin    ;
	vector<int>    xmin    ;
	vector<int>    xmax    ;

	// histnames.push_back("h_DijetMass"                                  ); histtitle.push_back("DijetMass"                                  ); rebin.push_back( 4 );                     
	// histnames.push_back("h_DijetMassPuppi"                             ); histtitle.push_back("DijetMassPuppi"                             ); rebin.push_back( 4 );                     

	// histnames.push_back("h_CutFlow"                                    ); histtitle.push_back("CutFlow"                                    ); label.push_back(""); rebin.push_back( 1 ); xmin.push_back(-1); xmax.push_back( -1 );  
	// histnames.push_back("h_JetSDmass"                                  ); histtitle.push_back("JetSDmass"                                  ); label.push_back(""); rebin.push_back( 2 ); xmin.push_back(-1); xmax.push_back( -1 );  
	// histnames.push_back("h_BtagCategoriesPostSF"                       ); histtitle.push_back("BtagCategoriesPostSF"                       ); label.push_back(""); rebin.push_back( 1 ); xmin.push_back(-1); xmax.push_back( -1 );  
	// histnames.push_back("h_DoublePupTag_BtagCategoriesPostSF"          ); histtitle.push_back("DoublePupTag_BtagCategoriesPostSF"          ); label.push_back(""); rebin.push_back( 1 ); xmin.push_back(-1); xmax.push_back( -1 );  
	// histnames.push_back("h_DijetMass_dRapIn"                           ); histtitle.push_back("Dijet mass [GeV]"                           ); label.push_back("#DeltaY inclusive"); rebin.push_back( 4 ); xmin.push_back(500); xmax.push_back(dijet_xmax);  
	// histnames.push_back("h_DijetMass_dRapHi"                           ); histtitle.push_back("Dijet mass [GeV]"                           ); label.push_back("#DeltaY > 1.0"); rebin.push_back( 4 ); xmin.push_back(500); xmax.push_back(dijet_xmax);  
	// histnames.push_back("h_DijetMass_dRapLo"                           ); histtitle.push_back("Dijet mass [GeV]"                           ); label.push_back("#DeltaY < 1.0"); rebin.push_back( 4 ); xmin.push_back(500); xmax.push_back(dijet_xmax);  
	histnames.push_back("h_Jet0Pt"                                     ); histtitle.push_back("Jet 0 p_{T} [GeV]"                                     ); label.push_back(""); rebin.push_back( 10); xmin.push_back(500); xmax.push_back( 2000 );  
	// histnames.push_back("h_Jet0SDmass_matchedTop"                      ); histtitle.push_back("Jet0SDmass_matchedTop"                      ); label.push_back(""); rebin.push_back( 4 ); xmin.push_back(-1); xmax.push_back( -1 );  
	// histnames.push_back("h_Jet0SDmass_matchedTop_topDist"              ); histtitle.push_back("Jet0SDmass_matchedTop_topDist"              ); label.push_back(""); rebin.push_back( 4 ); xmin.push_back(-1); xmax.push_back( -1 );  
	// histnames.push_back("h_Jet0SDmass_Pt1400_all"                      ); histtitle.push_back("Jet0SDmass_Pt1400_all"                      ); label.push_back(""); rebin.push_back( 4 ); xmin.push_back(-1); xmax.push_back( -1 );  
	// histnames.push_back("h_Jet0SDmass_TauTag_all"                      ); histtitle.push_back("Jet0SDmass_TauTag_all"                      ); label.push_back(""); rebin.push_back( 4 ); xmin.push_back(-1); xmax.push_back( -1 );  
	histnames.push_back("h_pup_JetSDmass"                              ); histtitle.push_back("Jet PUPPI SD mass [GeV]"                    ); label.push_back(""); rebin.push_back( 4 ); xmin.push_back(-1); xmax.push_back( -1 );  
	// histnames.push_back("h_pup_JetSDmass_JetTag_b"                     ); histtitle.push_back("Jet PUPPI SD mass [GeV]"                     ); label.push_back("Jet b-tagged"); rebin.push_back( 4 ); xmin.push_back(-1); xmax.push_back( -1 );  
	histnames.push_back("h_pup_JetSDmass_JetTag_tau32"                 ); histtitle.push_back("Jet PUPPI SD mass [GeV]"                 ); label.push_back("Jet #tau_{32} tagged"); rebin.push_back( 4 ); xmin.push_back(-1); xmax.push_back( -1 );  
	// histnames.push_back("h_pup_JetSDmass_JetTag_b_tau32"               ); histtitle.push_back("Jet PUPPI SD mass [GeV]"               ); label.push_back("Jet #tau_{32} tagged and b-tagged"); rebin.push_back( 4 ); xmin.push_back(-1); xmax.push_back( -1 );  
	// histnames.push_back("h_DijetMass_masspuptag"                       ); histtitle.push_back("Dijet mass [GeV]"               ); label.push_back(""); rebin.push_back( 4 ); xmin.push_back(500); xmax.push_back(dijet_xmax);                          
	// histnames.push_back("h_DijetMass_masspuptag_puppitau32_lt0p80"     ); histtitle.push_back("Dijet mass [GeV]"               ); label.push_back(""); rebin.push_back( 4 ); xmin.push_back(500); xmax.push_back(dijet_xmax);                                            
	// histnames.push_back("h_DijetMass_1btag_masspuptag"                 ); histtitle.push_back("Dijet mass [GeV]"               ); label.push_back(""); rebin.push_back( 4 ); xmin.push_back(500); xmax.push_back(dijet_xmax);                                
	// histnames.push_back("h_DijetMass_2btag_masspuptag"                 ); histtitle.push_back("Dijet mass [GeV]"               ); label.push_back(""); rebin.push_back( 4 ); xmin.push_back(500); xmax.push_back(dijet_xmax);                                
	// histnames.push_back("h_DijetMass_0btag_masspuptag"                 ); histtitle.push_back("Dijet mass [GeV]"               ); label.push_back(""); rebin.push_back( 4 ); xmin.push_back(500); xmax.push_back(dijet_xmax);                                
	// histnames.push_back("h_2ttag_inclu_dRapIn_DijetMass"               ); histtitle.push_back("Dijet mass [GeV]"               ); label.push_back("#DeltaY inclusive, b-tag inclusive"); rebin.push_back( 4 ); xmin.push_back(500); xmax.push_back(dijet_xmax);                                  
	// histnames.push_back("h_2ttag_0btag_dRapIn_DijetMass"               ); histtitle.push_back("Dijet mass [GeV]"               ); label.push_back("#DeltaY inclusive, 0 b-tag"        ); rebin.push_back( 4 ); xmin.push_back(500); xmax.push_back(dijet_xmax);                                  
	// histnames.push_back("h_2ttag_1btag_dRapIn_DijetMass"               ); histtitle.push_back("Dijet mass [GeV]"               ); label.push_back("#DeltaY inclusive, 1 b-tag"        ); rebin.push_back( 4 ); xmin.push_back(500); xmax.push_back(dijet_xmax);                                  
	// histnames.push_back("h_2ttag_2btag_dRapIn_DijetMass"               ); histtitle.push_back("Dijet mass [GeV]"               ); label.push_back("#DeltaY inclusive, 2 b-tag"        ); rebin.push_back( 4 ); xmin.push_back(500); xmax.push_back(dijet_xmax);                                  
	// histnames.push_back("h_2ttag_inclu_dRapLo_DijetMass"               ); histtitle.push_back("Dijet mass [GeV]"               ); label.push_back("#DeltaY < 1.0, b-tag inclusive"); rebin.push_back( 4 ); xmin.push_back(500); xmax.push_back(dijet_xmax);                                  
	histnames.push_back("h_2ttag_0btag_dRapLo_DijetMass"               ); histtitle.push_back("Dijet mass [GeV]"               ); label.push_back("#DeltaY < 1.0, 0 b-tag"        ); rebin.push_back( 10 ); xmin.push_back(500); xmax.push_back(dijet_xmax);                                  
	histnames.push_back("h_2ttag_1btag_dRapLo_DijetMass"               ); histtitle.push_back("Dijet mass [GeV]"               ); label.push_back("#DeltaY < 1.0, 1 b-tag"        ); rebin.push_back( 10 ); xmin.push_back(500); xmax.push_back(dijet_xmax);                                  
	histnames.push_back("h_2ttag_2btag_dRapLo_DijetMass"               ); histtitle.push_back("Dijet mass [GeV]"               ); label.push_back("#DeltaY < 1.0, 2 b-tag"        ); rebin.push_back( 10 ); xmin.push_back(500); xmax.push_back(dijet_xmax);                                  
	// histnames.push_back("h_2ttag_inclu_dRapHi_DijetMass"               ); histtitle.push_back("Dijet mass [GeV]"               ); label.push_back("#DeltaY > 1.0, b-tag inclusive"); rebin.push_back( 4 ); xmin.push_back(500); xmax.push_back(dijet_xmax);                                  
	histnames.push_back("h_2ttag_0btag_dRapHi_DijetMass"               ); histtitle.push_back("Dijet mass [GeV]"               ); label.push_back("#DeltaY > 1.0, 0 b-tag"        ); rebin.push_back( 10 ); xmin.push_back(500); xmax.push_back(dijet_xmax);                                  
	histnames.push_back("h_2ttag_1btag_dRapHi_DijetMass"               ); histtitle.push_back("Dijet mass [GeV]"               ); label.push_back("#DeltaY > 1.0, 1 b-tag"        ); rebin.push_back( 10 ); xmin.push_back(500); xmax.push_back(dijet_xmax);                                  
	histnames.push_back("h_2ttag_2btag_dRapHi_DijetMass"               ); histtitle.push_back("Dijet mass [GeV]"               ); label.push_back("#DeltaY > 1.0, 2 b-tag"        ); rebin.push_back( 10 ); xmin.push_back(500); xmax.push_back(dijet_xmax);                                  
	// histnames.push_back("h_2btag_DijetMass"                            ); histtitle.push_back("Dijet mass [GeV]"                           ); label.push_back(""        ); rebin.push_back( 1 ); xmin.push_back(-1); xmax.push_back( -1 );                     

	histnames.push_back("h_pup_JetTau32"                               ); histtitle.push_back("PUPPI #tau_{32}"      ); label.push_back(""                                     ); rebin.push_back( 5 ); xmin.push_back(-1); xmax.push_back( -1 );                     
	// histnames.push_back("h_pup_JetTau32_JetTag_b"                      ); histtitle.push_back("PUPPI #tau_{32}"      ); label.push_back("Jet b-tagged"                         ); rebin.push_back( 5 ); xmin.push_back(-1); xmax.push_back( -1 );                     
	histnames.push_back("h_pup_JetTau32_JetTag_mass"                   ); histtitle.push_back("PUPPI #tau_{32}"      ); label.push_back("Jet SD mass tagged"                   ); rebin.push_back( 5 ); xmin.push_back(-1); xmax.push_back( -1 );                     
	// histnames.push_back("h_pup_JetTau32_JetTag_b_mass"                 ); histtitle.push_back("PUPPI #tau_{32}"      ); label.push_back("Jet b-tagged and SD mass tagged"      ); rebin.push_back( 5 ); xmin.push_back(-1); xmax.push_back( -1 );                     










	for (unsigned int i=0; i< histnames.size(); i++ ){
		TH1D * h_noTTw    = (TH1D*)f_noTTw       ->Get( histnames[i].c_str() ); 
		TH1D * h_TTw      = (TH1D*)f_TTw         ->Get( histnames[i].c_str() ); 


		float lumi = 35922;//35867 ;  //36220;//27220;
		float nttbar;
		nttbar =  77229341 + 78006311 ; // nom + backup  // 70452080;//;92925926;//92925926; //96834559.;//19665194.;
		float kfactor = 1 ;//0.94;//0.7;//0.94;//1;//0.94;
		float ttSF = 1;//0.89*0.89;
		

		h_noTTw   ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
		h_TTw     ->Scale( 831.76 * ttSF * lumi * kfactor / ( nttbar * 0.82)  ); 



			plotterSyst_ttW(
			histnames[i], 
			histtitle[i], 
			label[i], 
			"t#bar{t} MC - p_{T} weight comparison",
			"TT",
			"ttw",
			h_noTTw, h_TTw, 
			false, //bool legswitch, 
			false, //bool invert, 
			xmin[i], //double xmin, 
			xmax[i], //double xmax, 
			1.3, // yscale,
			rebin[i],
			savefolder 
		);
	}



}


void plotterSyst(
  string histname, 
  string histtitle, 
  string pave, 
  string pave2,
  string samplelabel,
  string sample,
  string systLabel,
  TH1D* hNom1, TH1D* hUp1, TH1D* hDn1, 
  bool legswitch, 
  bool invert, 
  double xmax, 
  double yscale,
  int rebin,
  string savefolder )
{
	cout<<"plotterSyst("<<histname<<endl;
	
	//--- Canvas ---

	TCanvas *c1 = new TCanvas("c1", "c1",1,1,745,701);
	// gStyle->SetOptFit(1);
	gStyle->SetOptFit(0);
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

	//--- Pad ---

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

	//--- Histogram ---

	TH1F *hNom  = new TH1F();
	TH1F *hUp   = new TH1F();
	TH1F *hDn   = new TH1F();
	hNom = (TH1F*) hNom1->Clone("hNom");
	hUp  = (TH1F*)  hUp1->Clone("hUp");
	hDn  = (TH1F*)  hDn1->Clone("hDn");

	hNom ->Rebin(rebin);  
	hUp  ->Rebin(rebin); 
	hDn  ->Rebin(rebin); 

	if (xmax>0) hNom->GetXaxis()->SetRangeUser(0, xmax);
	if (xmax>0) hUp ->GetXaxis()->SetRangeUser(0, xmax);
	if (xmax>0) hDn ->GetXaxis()->SetRangeUser(0, xmax);


	hNom->SetMaximum(yscale * hNom->GetMaximum() );
	hNom->SetMinimum(0.0001 );
	hNom->GetYaxis()->SetTitle("Events");
	hNom->GetYaxis()->SetTitleSize(0.065);
	hNom->GetYaxis()->SetTitleOffset(0.9); // 0.7);
	hNom->GetYaxis()->SetLabelSize(0.06);
	// hNom->SetMarkerStyle(20);
	// hNom->SetMarkerSize(0.8);
	// hNom->SetLineColor(kBlack);
	hNom->SetTitle("");
	hNom->SetLineColor(1);
	hNom->SetFillColor(1);
	hNom->SetFillStyle(0);
	hNom->SetLineWidth(2);
	hNom->SetMarkerStyle(20);
	hNom->SetMarkerSize(0.8);

	hNom->GetXaxis()->SetNdivisions(506);
	hNom->GetXaxis()->SetLabelFont(42);
	hNom->GetXaxis()->SetLabelSize(0);
	hNom->GetXaxis()->SetTitleSize(0.0475);
	hNom->GetXaxis()->SetTickLength(0.045);
	hNom->GetXaxis()->SetTitleOffset(1.15);
	hNom->GetXaxis()->SetTitleFont(42);
	hNom->GetYaxis()->SetTitle("Events");
	hNom->GetYaxis()->SetNdivisions(506);
	hNom->GetYaxis()->SetLabelFont(42);
	hNom->GetYaxis()->SetLabelSize(0.06375);
	hNom->GetYaxis()->SetTitleSize(0.07125);
	hNom->GetYaxis()->SetTitleOffset(0.9);
	hNom->GetYaxis()->SetTitleFont(42);
	hNom->GetZaxis()->SetLabelFont(42);
	hNom->GetZaxis()->SetLabelSize(0.0425);
	hNom->GetZaxis()->SetTitleSize(0.0475);
	hNom->GetZaxis()->SetTitleFont(42);


	hUp->SetLineColor(3);
	hUp->SetLineWidth(2);

	hDn->SetLineColor(2);
	hDn->SetLineWidth(2);

	//--- Draw ---

	hNom->Draw("HIST");
	hUp ->Draw("HISTsame");
	hDn ->Draw("HISTsame");



	// //--- TLatex ---

	// TLatex *   tex = new TLatex(0.14,0.916,"#font[62]{CMS} #font[52]{Preliminary}");
	// tex->SetNDC();
	// tex->SetTextFont(42);
	// tex->SetTextSize(0.0825);
	// tex->SetLineWidth(2);
	// tex->Draw();
	// tex = new TLatex(0.96,0.916,"36 fb^{-1} (13 TeV)");
	// tex->SetNDC();
	// tex->SetTextAlign(31);
	// tex->SetTextFont(42);
	// tex->SetTextSize(0.0825);
	// tex->SetLineWidth(2);
	// tex->Draw();
	TLatex *  tex = new TLatex(0.181,0.82225,samplelabel.c_str());
	tex->SetNDC();
	tex->SetTextAlign(13);
	tex->SetTextFont(42);
	// tex->SetTextSize(0.045);
	tex->SetTextSize(0.041);
	tex->SetLineWidth(2);
	tex->Draw();

	TLatex *  tex2 = new TLatex(0.181,0.76225,pave.c_str());
	tex2->SetNDC();
	tex2->SetTextAlign(13);
	tex2->SetTextFont(42);
	// tex->SetTextSize(0.045);
	tex2->SetTextSize(0.041);
	tex2->SetLineWidth(2);
	tex2->Draw();

	TLatex *  tex3 = new TLatex(0.181,0.70225,pave2.c_str());
	tex3->SetNDC();
	tex3->SetTextAlign(13);
	tex3->SetTextFont(42);
	// tex->SetTextSize(0.045);
	tex3->SetTextSize(0.041);
	tex3->SetLineWidth(2);
	tex3->Draw();
	//--- Legend ---

	// Top-right of plot
	// double leg1 =0.6; double leg2 =0.66; double leg3 =0.89; double leg4 =0.84; // double leg1 =0.5; double leg2 =0.49; double leg3 =0.85; double leg4 =0.8;
	double leg1 =0.7; double leg2 =0.63; double leg3 =0.89; double leg4 =0.84; // double leg1 =0.5; double leg2 =0.49; double leg3 =0.85; double leg4 =0.8;
	TLegend *leg = new TLegend(leg1, leg2, leg3, leg4);
	leg->SetTextSize(0.043);
	leg->AddEntry(hNom, "Nominal", "L");
	leg->AddEntry(hUp , "Up", "L");
	leg->AddEntry(hDn , "Down", "L");
	leg->SetFillColor(0);
	leg->SetLineColor(0);
	leg->Draw("same");
	gPad->RedrawAxis();

	pad1->Modified();
	c1->cd();



	//---------------- Ratio plot ------------------

	//--- Pad ---

	TPad *pad2 = new TPad("pad2", "pad2",0,0,1,0.3333333);
	pad2->Draw();
	pad2->cd();
	// pad2->Range(-0.1792683,-1.570091,1.10122,1.899);
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

	//--- Calculate ratio ---

	// Data / (tt + QCD1)


	TH1F *ratioUp = new TH1F();
	TH1F *ratioDn = new TH1F();
	ratioUp = (TH1F*) hNom->Clone("ratioUp ");
	ratioDn = (TH1F*) hNom->Clone("ratioDn ");
	ratioUp->Sumw2();
	ratioDn->Sumw2();
	ratioUp->Divide(hUp, hNom);
	ratioDn->Divide(hDn, hNom);

	
	//--- Draw ratio ---
	ratioUp->GetYaxis()->SetRangeUser(0.49,1.59);

	// ratioUp->GetYaxis()->SetRangeUser(0.07,1.3);
	// ratioUp->GetYaxis()->SetTitle("Data / Bkgd");
	// ratioUp->GetYaxis()->SetTitleOffset(0.3);
	// ratioUp->GetYaxis()->SetTitleSize(0.17);
	// ratioUp->GetYaxis()->SetNdivisions(205);
	// ratioUp->GetYaxis()->SetLabelSize(0.11);
	// ratioUp->GetXaxis()->SetLabelSize(0.11);
	// ratioUp->GetXaxis()->SetTitleSize(0.17);
	ratioUp->GetXaxis()->SetTitle( histtitle.c_str() );
	ratioUp->SetStats(0);
	ratioUp->SetFillColor(1);
	ratioUp->SetFillStyle(0);
	ratioUp->SetLineWidth(2);
	ratioUp->SetLineColor(3);
	ratioUp->SetMarkerColor(3);
	ratioUp->SetMarkerStyle(20);
	ratioUp->SetMarkerSize(0.8);
	ratioUp->GetXaxis()->SetNdivisions(506);
	ratioUp->GetXaxis()->SetLabelFont(42);
	ratioUp->GetXaxis()->SetLabelOffset(0.015);
	ratioUp->GetXaxis()->SetLabelSize(0.1275);
	ratioUp->GetXaxis()->SetTitleSize(0.1425);
	ratioUp->GetXaxis()->SetTickLength(0.09);
	ratioUp->GetXaxis()->SetTitleOffset(1.15);
	ratioUp->GetXaxis()->SetTitleFont(42);
	ratioUp->GetYaxis()->SetTitle("Syst/nom");
	ratioUp->GetYaxis()->CenterTitle(true);
	ratioUp->GetYaxis()->SetNdivisions(304);
	ratioUp->GetYaxis()->SetLabelFont(42);
	ratioUp->GetYaxis()->SetLabelSize(0.1275);
	ratioUp->GetYaxis()->SetTitleSize(0.1425);
	ratioUp->GetYaxis()->SetTickLength(0.045);
	ratioUp->GetYaxis()->SetTitleOffset(0.45);
	ratioUp->GetYaxis()->SetTitleFont(42);
	ratioUp->GetZaxis()->SetLabelFont(42);
	ratioUp->GetZaxis()->SetLabelSize(0.0425);
	ratioUp->GetZaxis()->SetTitleSize(0.0475);	
	ratioUp->GetZaxis()->SetTitleFont(42);
	// ratioUp->Draw("lepe0");
	ratioUp->GetYaxis()->SetRangeUser(0.07,1.3);
	ratioUp->GetYaxis()->SetLimits(0.07,1.3) ;
	TAxis *yaxis1 =ratioUp->GetYaxis();
	yaxis1 ->SetRangeUser(0.07,1.3);
	ratioUp->Draw("HIST");
	yaxis1 ->SetRangeUser(0.07,1.3);


	TF1 *line = new TF1("line", "1", -7000, 7000);
	line->SetLineColor(kBlack);
	line->SetLineStyle(2);
	line->SetLineWidth(2);
	line->Draw("same");



	// TF1 *line3 = new TF1("line3", "1.3",0, 500);
	// line3->SetLineColor(kOrange);
	// line3->SetLineStyle(2);
	// line3->SetLineWidth(3);
	// line3->Draw("same");

	// ratioUp->Draw("E0 same");
	ratioUp->GetYaxis()->SetRangeUser(0.07,1.3);
	ratioUp->GetYaxis()->SetLimits(0.07,1.3) ;
		ratioUp->SetLineColor(3);
	ratioUp->SetMarkerColor(3);
	ratioUp->Draw("HISTsame");

	// ratioDn->GetYaxis()->SetRangeUser(0.01,1.99);
	ratioDn->GetYaxis()->SetRangeUser(0.49,1.59);
	// ratioDn->GetYaxis()->SetLimits(0.07,1.3) ;
	ratioDn->SetStats(0);
	ratioDn->SetFillColor(0);
	ratioDn->SetFillStyle(0);
	ratioDn->SetLineWidth(2);
	ratioDn->SetLineColor(2);
	ratioDn->SetMarkerColor(2);
	ratioDn->SetMarkerStyle(20);
	ratioDn->SetMarkerSize(0.8);


	ratioDn->GetXaxis()->SetTitle( histtitle.c_str() );
	ratioDn->SetStats(0);
	ratioDn->SetFillColor(1);
	ratioDn->SetFillStyle(0);
	ratioDn->SetLineWidth(2);

	ratioDn->SetMarkerStyle(20);
	ratioDn->SetMarkerSize(0.8);
	ratioDn->GetXaxis()->SetNdivisions(506);
	ratioDn->GetXaxis()->SetLabelFont(42);
	ratioDn->GetXaxis()->SetLabelOffset(0.015);
	ratioDn->GetXaxis()->SetLabelSize(0.1275);
	ratioDn->GetXaxis()->SetTitleSize(0.1425);
	ratioDn->GetXaxis()->SetTickLength(0.09);
	ratioDn->GetXaxis()->SetTitleOffset(1.15);
	ratioDn->GetXaxis()->SetTitleFont(42);
	ratioDn->GetYaxis()->SetTitle("Syst/nom");
	ratioDn->GetYaxis()->CenterTitle(true);
	ratioDn->GetYaxis()->SetNdivisions(304);
	ratioDn->GetYaxis()->SetLabelFont(42);
	ratioDn->GetYaxis()->SetLabelSize(0.1275);
	ratioDn->GetYaxis()->SetTitleSize(0.1425);
	ratioDn->GetYaxis()->SetTickLength(0.045);
	ratioDn->GetYaxis()->SetTitleOffset(0.45);
	ratioDn->GetYaxis()->SetTitleFont(42);
	ratioDn->GetZaxis()->SetLabelFont(42);
	ratioDn->GetZaxis()->SetLabelSize(0.0425);
	ratioDn->GetZaxis()->SetTitleSize(0.0475);	
	ratioDn->GetZaxis()->SetTitleFont(42);



	for (int bin=1; bin<=ratioDn->GetNbinsX();++bin){
			ratioDn->SetBinError(bin,0);
			ratioUp->SetBinError(bin,0);
			if (ratioDn->GetBinContent(bin)<0.00001 ) ratioDn->SetBinContent(bin,1);
			if (ratioUp->GetBinContent(bin)<0.00001 ) ratioUp->SetBinContent(bin,1);
	}
	// gStyle->SetErrorX(500);

	ratioDn ->Draw("HIST"    );
	line    ->Draw("same" );
	ratioDn ->Draw("HISTsame");
	ratioUp ->Draw("HISTsame");
	ratioDn ->Draw("HISTsame");


	gPad->RedrawAxis();
	 
	pad2->Modified();
	c1->cd();
	c1->Modified();
	c1->cd();
	c1->SetSelected(c1);     

	// histname = histname+"_2QCD";
	// if (invert) histname = histname+"_QCDonTop";
	// c1->SaveAs(savefolder+histname+".pdf");
	// c1->SaveAs(savefolder+histname+".png");
	// // c1->SaveAs("runs/run20161010/kinPlots/Jetpt600HT1000_"+histname+".png");
	// pad1->cd();
	// hNom->SetMaximum(30.0 * hNom->GetMaximum() );
	// pad1->SetLogy(1);
	// c1->SaveAs(savefolder+histname+"_log.pdf");
	// c1->SaveAs(savefolder+histname+"_log.png");
	// // c1->SaveAs("runs/run20161010/kinPlots/Jetpt600HT1000_"+histname+"_log.png");


	string savename = savefolder+"hsyst_"+sample+"_"+systLabel+"_"+histname+".pdf";
	c1->SaveAs(savename.c_str());





	delete pad1;
	delete pad2;
	delete c1;

}



void plotterSyst_ttW(
  string histname, 
  string histtitle, 
  string pave, 
  string samplelabel,
  string sample,
  string systLabel,
  TH1D* hNom1, TH1D* hUp1, 
  bool legswitch, 
  bool invert, 
  double xmin, 
  double xmax, 
  double yscale,
  int rebin,
  string savefolder )
{
	cout<<"plotterSyst("<<histname<<endl;
	
	//--- Canvas ---

	TCanvas *c1 = new TCanvas("c1", "c1",1,1,745,701);
	// gStyle->SetOptFit(1);
	gStyle->SetOptFit(0);
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

	//--- Pad ---

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

	//--- Histogram ---

	TH1F *hNom  = new TH1F();
	TH1F *hUp   = new TH1F();
	// TH1F *hDn   = new TH1F();
	hNom = (TH1F*) hNom1->Clone("hNom");
	hUp  = (TH1F*)  hUp1->Clone("hUp");
	// hDn  = (TH1F*)  hDn1->Clone("hDn");

	hNom ->Rebin(rebin);  
	hUp  ->Rebin(rebin); 
	// hDn  ->Rebin(rebin); 

	if (xmax>0 && xmin<0) hNom->GetXaxis()->SetRangeUser(0, xmax);
	if (xmax>0 && xmin<0) hUp ->GetXaxis()->SetRangeUser(0, xmax);

	if (xmax>0 && xmin>0) hNom->GetXaxis()->SetRangeUser(xmin, xmax);
	if (xmax>0 && xmin>0) hUp ->GetXaxis()->SetRangeUser(xmin, xmax);
	// if (xmax>0) hDn ->GetXaxis()->SetRangeUser(0, xmax);


	hNom->SetMaximum(yscale * hNom->GetMaximum() );
	hNom->SetMinimum(0.0001 );
	hNom->GetYaxis()->SetTitle("Events");
	hNom->GetYaxis()->SetTitleSize(0.065);
	hNom->GetYaxis()->SetTitleOffset(0.9); // 0.7);
	hNom->GetYaxis()->SetLabelSize(0.06);
	// hNom->SetMarkerStyle(20);
	// hNom->SetMarkerSize(0.8);
	// hNom->SetLineColor(kBlack);
	hNom->SetTitle("");
	hNom->SetLineColor(1);
	hNom->SetFillColor(1);
	hNom->SetFillStyle(0);
	hNom->SetLineWidth(2);
	hNom->SetMarkerStyle(20);
	hNom->SetMarkerSize(0.8);

	hNom->GetXaxis()->SetNdivisions(506);
	hNom->GetXaxis()->SetLabelFont(42);
	hNom->GetXaxis()->SetLabelSize(0);
	hNom->GetXaxis()->SetTitleSize(0.0475);
	hNom->GetXaxis()->SetTickLength(0.045);
	hNom->GetXaxis()->SetTitleOffset(1.15);
	hNom->GetXaxis()->SetTitleFont(42);
	hNom->GetYaxis()->SetTitle("Events");
	hNom->GetYaxis()->SetNdivisions(506);
	hNom->GetYaxis()->SetLabelFont(42);
	hNom->GetYaxis()->SetLabelSize(0.06375);
	hNom->GetYaxis()->SetTitleSize(0.07125);
	hNom->GetYaxis()->SetTitleOffset(0.9);
	hNom->GetYaxis()->SetTitleFont(42);
	hNom->GetZaxis()->SetLabelFont(42);
	hNom->GetZaxis()->SetLabelSize(0.0425);
	hNom->GetZaxis()->SetTitleSize(0.0475);
	hNom->GetZaxis()->SetTitleFont(42);


	hUp->SetLineColor(3);
	hUp->SetLineWidth(2);

	// hDn->SetLineColor(2);
	// hDn->SetLineWidth(2);

	//--- Draw ---

	hNom->Draw("HIST");
	hUp ->Draw("HISTsame");
	// hDn ->Draw("HISTsame");



	// //--- TLatex ---

	// TLatex *   tex = new TLatex(0.14,0.916,"#font[62]{CMS} #font[52]{Preliminary}");
	// tex->SetNDC();
	// tex->SetTextFont(42);
	// tex->SetTextSize(0.0825);
	// tex->SetLineWidth(2);
	// tex->Draw();
	// tex = new TLatex(0.96,0.916,"36 fb^{-1} (13 TeV)");
	// tex->SetNDC();
	// tex->SetTextAlign(31);
	// tex->SetTextFont(42);
	// tex->SetTextSize(0.0825);
	// tex->SetLineWidth(2);
	// tex->Draw();
	TLatex *  tex = new TLatex(0.181,0.82225,samplelabel.c_str());
	tex->SetNDC();
	tex->SetTextAlign(13);
	tex->SetTextFont(42);
	// tex->SetTextSize(0.045);
	tex->SetTextSize(0.041);
	tex->SetLineWidth(2);
	tex->Draw();

	TLatex *  tex2 = new TLatex(0.181,0.76225,pave.c_str());
	tex2->SetNDC();
	tex2->SetTextAlign(13);
	tex2->SetTextFont(42);
	// tex->SetTextSize(0.045);
	tex2->SetTextSize(0.041);
	tex2->SetLineWidth(2);
	tex2->Draw();

	//--- Legend ---

	// Top-right of plot
	// double leg1 =0.6; double leg2 =0.66; double leg3 =0.89; double leg4 =0.84; // double leg1 =0.5; double leg2 =0.49; double leg3 =0.85; double leg4 =0.8;
	double leg1 =0.7; double leg2 =0.63; double leg3 =0.89; double leg4 =0.84; // double leg1 =0.5; double leg2 =0.49; double leg3 =0.85; double leg4 =0.8;
	TLegend *leg = new TLegend(leg1, leg2, leg3, leg4);
	leg->SetTextSize(0.043);
	leg->AddEntry(hNom, "Nominal", "L");
	leg->AddEntry(hUp , "tt weight", "L");
	// leg->AddEntry(hUp , "Down", "L");
	leg->SetFillColor(0);
	leg->SetLineColor(0);
	leg->Draw("same");
	gPad->RedrawAxis();

	pad1->Modified();
	c1->cd();



	//---------------- Ratio plot ------------------

	//--- Pad ---

	TPad *pad2 = new TPad("pad2", "pad2",0,0,1,0.3333333);
	pad2->Draw();
	pad2->cd();
	// pad2->Range(-0.1792683,-1.570091,1.10122,1.899);
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

	//--- Calculate ratio ---

	// Data / (tt + QCD1)


	TH1F *ratioUp = new TH1F();
	TH1F *ratioDn = new TH1F();
	ratioUp = (TH1F*) hNom->Clone("ratioUp ");
	// ratioDn = (TH1F*) hNom->Clone("ratioDn ");
	ratioUp->Sumw2();
	// ratioDn->Sumw2();
	ratioUp->Divide(hUp, hNom);
	// ratioDn->Divide(hDn, hNom);

	
	//--- Draw ratio ---

	// ratioUp->GetYaxis()->SetRangeUser(0.07,1.3);
	// ratioUp->GetYaxis()->SetTitle("Data / Bkgd");
	// ratioUp->GetYaxis()->SetTitleOffset(0.3);
	// ratioUp->GetYaxis()->SetTitleSize(0.17);
	// ratioUp->GetYaxis()->SetNdivisions(205);
	// ratioUp->GetYaxis()->SetLabelSize(0.11);
	// ratioUp->GetXaxis()->SetLabelSize(0.11);
	// ratioUp->GetXaxis()->SetTitleSize(0.17);
	ratioUp->GetXaxis()->SetTitle( histtitle.c_str() );
	ratioUp->SetStats(0);
	ratioUp->SetFillColor(1);
	ratioUp->SetFillStyle(0);
	ratioUp->SetLineWidth(2);
	ratioUp->SetLineColor(3);
	ratioUp->SetMarkerColor(3);
	ratioUp->SetMarkerStyle(20);
	ratioUp->SetMarkerSize(0.8);
	ratioUp->GetXaxis()->SetNdivisions(506);
	ratioUp->GetXaxis()->SetLabelFont(42);
	ratioUp->GetXaxis()->SetLabelOffset(0.015);
	ratioUp->GetXaxis()->SetLabelSize(0.1275);
	ratioUp->GetXaxis()->SetTitleSize(0.1425);
	ratioUp->GetXaxis()->SetTickLength(0.09);
	ratioUp->GetXaxis()->SetTitleOffset(1.15);
	ratioUp->GetXaxis()->SetTitleFont(42);
	ratioUp->GetYaxis()->SetTitle("Weight/nom");
	ratioUp->GetYaxis()->CenterTitle(true);
	ratioUp->GetYaxis()->SetNdivisions(304);
	ratioUp->GetYaxis()->SetLabelFont(42);
	ratioUp->GetYaxis()->SetLabelSize(0.1275);
	ratioUp->GetYaxis()->SetTitleSize(0.1025);
	ratioUp->GetYaxis()->SetTickLength(0.045);
	ratioUp->GetYaxis()->SetTitleOffset(0.45);
	ratioUp->GetYaxis()->SetTitleFont(42);
	ratioUp->GetZaxis()->SetLabelFont(42);
	ratioUp->GetZaxis()->SetLabelSize(0.0425);
	ratioUp->GetZaxis()->SetTitleSize(0.0475);	
	ratioUp->GetZaxis()->SetTitleFont(42);
	// ratioUp->Draw("lepe0");
	// ratioUp->GetYaxis()->SetRangeUser(0.07,1.3);
	// ratioUp->GetYaxis()->SetLimits(0.07,1.3) ;


	TAxis *yaxis1 =ratioUp->GetYaxis();
	ratioUp->GetYaxis()->SetRangeUser(0.49,1.59);

	// yaxis1 ->SetRangeUser(0.07,1.3);
	ratioUp->Draw("HIST");
	// yaxis1 ->SetRangeUser(0.07,1.3);


	TF1 *line = new TF1("line", "1", -7000, 7000);
	line->SetLineColor(kBlack);
	line->SetLineStyle(2);
	line->SetLineWidth(2);
	line->Draw("same");



	// TF1 *line3 = new TF1("line3", "1.3",0, 500);
	// line3->SetLineColor(kOrange);
	// line3->SetLineStyle(2);
	// line3->SetLineWidth(3);
	// line3->Draw("same");

	// ratioUp->Draw("E0 same");
	// ratioUp->GetYaxis()->SetRangeUser(0.07,1.3);
	// ratioUp->GetYaxis()->SetLimits(0.07,1.3) ;
		ratioUp->SetLineColor(3);
	ratioUp->SetMarkerColor(3);
	ratioUp->Draw("HISTsame");

	// // ratioDn->GetYaxis()->SetRangeUser(0.01,1.99);
	// ratioDn->GetYaxis()->SetRangeUser(0.49,1.59);
	// // ratioDn->GetYaxis()->SetLimits(0.07,1.3) ;
	// ratioDn->SetStats(0);
	// ratioDn->SetFillColor(0);
	// ratioDn->SetFillStyle(0);
	// ratioDn->SetLineWidth(2);
	// ratioDn->SetLineColor(2);
	// ratioDn->SetMarkerColor(2);
	// ratioDn->SetMarkerStyle(20);
	// ratioDn->SetMarkerSize(0.8);


	// ratioDn->GetXaxis()->SetTitle( histtitle.c_str() );
	// ratioDn->SetStats(0);
	// ratioDn->SetFillColor(1);
	// ratioDn->SetFillStyle(0);
	// ratioDn->SetLineWidth(2);

	// ratioDn->SetMarkerStyle(20);
	// ratioDn->SetMarkerSize(0.8);
	// ratioDn->GetXaxis()->SetNdivisions(506);
	// ratioDn->GetXaxis()->SetLabelFont(42);
	// ratioDn->GetXaxis()->SetLabelOffset(0.015);
	// ratioDn->GetXaxis()->SetLabelSize(0.1275);
	// ratioDn->GetXaxis()->SetTitleSize(0.1425);
	// ratioDn->GetXaxis()->SetTickLength(0.09);
	// ratioDn->GetXaxis()->SetTitleOffset(1.15);
	// ratioDn->GetXaxis()->SetTitleFont(42);
	// ratioDn->GetYaxis()->SetTitle("Syst/nom");
	// ratioDn->GetYaxis()->CenterTitle(true);
	// ratioDn->GetYaxis()->SetNdivisions(304);
	// ratioDn->GetYaxis()->SetLabelFont(42);
	// ratioDn->GetYaxis()->SetLabelSize(0.1275);
	// ratioDn->GetYaxis()->SetTitleSize(0.1425);
	// ratioDn->GetYaxis()->SetTickLength(0.045);
	// ratioDn->GetYaxis()->SetTitleOffset(0.45);
	// ratioDn->GetYaxis()->SetTitleFont(42);
	// ratioDn->GetZaxis()->SetLabelFont(42);
	// ratioDn->GetZaxis()->SetLabelSize(0.0425);
	// ratioDn->GetZaxis()->SetTitleSize(0.0475);	
	// ratioDn->GetZaxis()->SetTitleFont(42);



	for (int bin=1; bin<=ratioDn->GetNbinsX();++bin){
			// ratioDn->SetBinError(bin,0);
			ratioUp->SetBinError(bin,0);
			// if (ratioDn->GetBinContent(bin)<0.00001 ) ratioDn->SetBinContent(bin,1);
			if (ratioUp->GetBinContent(bin)<0.00001 ) ratioUp->SetBinContent(bin,1);
	}
	// gStyle->SetErrorX(500);

	ratioUp ->Draw("HIST"    );
	line    ->Draw("same" );
	// ratioDn ->Draw("HISTsame");
	ratioUp ->Draw("HISTsame");
	// ratioDn ->Draw("HISTsame");


	gPad->RedrawAxis();
	 
	pad2->Modified();
	c1->cd();
	c1->Modified();
	c1->cd();
	c1->SetSelected(c1);     

	// histname = histname+"_2QCD";
	// if (invert) histname = histname+"_QCDonTop";
	// c1->SaveAs(savefolder+histname+".pdf");
	// c1->SaveAs(savefolder+histname+".png");
	// // c1->SaveAs("runs/run20161010/kinPlots/Jetpt600HT1000_"+histname+".png");
	// pad1->cd();
	// hNom->SetMaximum(30.0 * hNom->GetMaximum() );
	// pad1->SetLogy(1);
	// c1->SaveAs(savefolder+histname+"_log.pdf");
	// c1->SaveAs(savefolder+histname+"_log.png");
	// // c1->SaveAs("runs/run20161010/kinPlots/Jetpt600HT1000_"+histname+"_log.png");


	string savename = savefolder+"hsyst_"+sample+"_"+systLabel+"_"+histname+".pdf";
	c1->SaveAs(savename.c_str());





	delete pad1;
	delete pad2;
	delete c1;

}

