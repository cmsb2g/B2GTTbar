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
#include "TStyle.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TString.h"
#include <vector> 
#include <algorithm>
#include "TROOT.h"
// #include "names.C"
#include "CMS_lumi.C"



void plotter(TString, TString, TString, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, bool);

void run(){
	gStyle->SetOptStat(0);
	gROOT->UseCurrentStyle();
	gROOT->ForceStyle();


	gROOT->Reset();
	gROOT->ForceStyle(); 
	gROOT->SetBatch(); 
	  

	TFile * fData = new TFile("JetHT_Kinematic_060716_nom_pt400.0.root");
	TFile * fQCD  = new TFile("QCD_HTall_Kinematic_060716_nom_pt400.0_fixed.root");
	TFile * fTT   = new TFile("TT_Kinematic_060716_nom_pt400.0.root");
	TFile * fZp10 = new TFile("Z1n_Kinematic_060716_nom_pt400.0.root");
	TFile * fZp20 = new TFile("Z2n_Kinematic_060716_nom_pt400.0.root");
	TFile * fZp30 = new TFile("Z3n_Kinematic_060716_nom_pt400.0.root");
	TFile * fZp40 = new TFile("Z4n_Kinematic_060716_nom_pt400.0.root");


    vector<TString> hists_names;
    vector<TString> hists_title;
    vector<int> hists_rebin;
    vector<bool> legs;
    vector<TString> pave;


    TString s0h = "2 t-tags, 0 b-tags, |#Deltay| > 1.0";
    TString s1h = "2 t-tags, 1 b-tag, |#Deltay| > 1.0";
    TString s2h = "2 t-tags, 2 b-tags, |#Deltay| > 1.0";
    TString sih = "2 t-tags, inclusive, |#Deltay| > 1.0";
    TString s0l = "2 t-tags, 0 b-tags, |#Deltay| < 1.0";
    TString s1l = "2 t-tags, 1 b-tag, |#Deltay| < 1.0";
    TString s2l = "2 t-tags, 2 b-tags, |#Deltay| < 1.0";
    TString sil = "2 t-tags, inclusive, |#Deltay| < 1.0";
    TString s0i = "2 t-tags, 0 b-tags, all #Deltay";
    TString s1i = "2 t-tags, 1 b-tag, all #Deltay";
    TString s2i = "2 t-tags, 2 b-tags, all #Deltay";
    TString si  = "2 t-tags, All Signal Regions";
	   
	hists_names.push_back("mttPredDist2_modMass_tagMassSDTau32_dRapHi_0btag");          pave.push_back(s0h);   hists_title.push_back("Dijet mass (GeV)");                hists_rebin.push_back(10);   legs.push_back(false);   
	hists_names.push_back("mttPredDist2_modMass_tagMassSDTau32_dRapHi_1btag");          pave.push_back(s1h);   hists_title.push_back("Dijet mass (GeV)");                hists_rebin.push_back(10);   legs.push_back(false);   
	hists_names.push_back("mttPredDist2_modMass_tagMassSDTau32_dRapHi_2btag");          pave.push_back(s2h);   hists_title.push_back("Dijet mass (GeV)");                hists_rebin.push_back(10);   legs.push_back(false);   
	hists_names.push_back("mttPredDist2_modMass_tagMassSDTau32_dRapHi_inclusive");      pave.push_back(sih);   hists_title.push_back("Dijet mass (GeV)");                hists_rebin.push_back(10);   legs.push_back(false);       
	hists_names.push_back("mttPredDist2_modMass_tagMassSDTau32_dRapLo_0btag");          pave.push_back(s0l);   hists_title.push_back("Dijet mass (GeV)");                hists_rebin.push_back(10);   legs.push_back(false);   
	hists_names.push_back("mttPredDist2_modMass_tagMassSDTau32_dRapLo_1btag");          pave.push_back(s1l);   hists_title.push_back("Dijet mass (GeV)");                hists_rebin.push_back(10);   legs.push_back(false);   
	hists_names.push_back("mttPredDist2_modMass_tagMassSDTau32_dRapLo_2btag");          pave.push_back(s2l);   hists_title.push_back("Dijet mass (GeV)");                hists_rebin.push_back(10);   legs.push_back(false);   
	hists_names.push_back("mttPredDist2_modMass_tagMassSDTau32_dRapLo_inclusive");      pave.push_back(sil);   hists_title.push_back("Dijet mass (GeV)");                hists_rebin.push_back(10);   legs.push_back(false);       
	hists_names.push_back("mttPredDist2_modMass_tagMassSDTau32_dRapIn_0btag");          pave.push_back(s0i);   hists_title.push_back("Dijet mass (GeV)");                hists_rebin.push_back(10);   legs.push_back(false);   
	hists_names.push_back("mttPredDist2_modMass_tagMassSDTau32_dRapIn_1btag");          pave.push_back(s1i);   hists_title.push_back("Dijet mass (GeV)");                hists_rebin.push_back(10);   legs.push_back(false);   
	hists_names.push_back("mttPredDist2_modMass_tagMassSDTau32_dRapIn_2btag");          pave.push_back(s2i);   hists_title.push_back("Dijet mass (GeV)");                hists_rebin.push_back(10);   legs.push_back(false);   
	hists_names.push_back("mttPredDist2_modMass_tagMassSDTau32_dRapIn_inclusive");      pave.push_back(si );   hists_title.push_back("Dijet mass (GeV)");                hists_rebin.push_back(10);   legs.push_back(false);       
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_0btag");        pave.push_back(s0h);   hists_title.push_back("Dijet mass (GeV)");                hists_rebin.push_back(10);   legs.push_back(false);     
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_JetMass_0btag");          pave.push_back(s0h);   hists_title.push_back("Jet mass (GeV)");                  hists_rebin.push_back(10);   legs.push_back(false);
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_JetPt_0btag");            pave.push_back(s0h);   hists_title.push_back("Jet p_{T} (GeV)");                 hists_rebin.push_back(10);   legs.push_back(false);
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_0btag");      pave.push_back(s0h);   hists_title.push_back("Jet rapidity");                    hists_rebin.push_back(10);   legs.push_back(false);  
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_0btag");     pave.push_back(s0h);   hists_title.push_back("SoftDrop jet mass (GeV)");         hists_rebin.push_back(10);   legs.push_back(false);               
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_Tau32_0btag");            pave.push_back(s0h);   hists_title.push_back("#tau_{3}/#tau_{2}");               hists_rebin.push_back(10);   legs.push_back(false);  
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_bDisc_0btag");            pave.push_back(s0h);   hists_title.push_back("Max subjet b-discriminant");       hists_rebin.push_back(10);   legs.push_back(false);          
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_1btag");        pave.push_back(s1h);   hists_title.push_back("Dijet mass (GeV)");                hists_rebin.push_back(10);   legs.push_back(false);              
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_JetMass_1btag");          pave.push_back(s1h);   hists_title.push_back("Jet mass (GeV)");                  hists_rebin.push_back(10);   legs.push_back(false);            
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_JetPt_1btag");            pave.push_back(s1h);   hists_title.push_back("Jet p_{T} (GeV)");                 hists_rebin.push_back(10);   legs.push_back(false);          
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_1btag");      pave.push_back(s1h);   hists_title.push_back("Jet rapidity");                    hists_rebin.push_back(10);   legs.push_back(false);                
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_1btag");     pave.push_back(s1h);   hists_title.push_back("SoftDrop jet mass (GeV)");         hists_rebin.push_back(10);   legs.push_back(false);                 
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_Tau32_1btag");            pave.push_back(s1h);   hists_title.push_back("#tau_{3}/#tau_{2}");               hists_rebin.push_back(10);   legs.push_back(false);          
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_bDisc_1btag");            pave.push_back(s1h);   hists_title.push_back("Max subjet b-discriminant");       hists_rebin.push_back(10);   legs.push_back(false);          
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_2btag");        pave.push_back(s2h);   hists_title.push_back("Dijet mass (GeV)");                hists_rebin.push_back(10);   legs.push_back(false);              
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_JetMass_2btag");          pave.push_back(s2h);   hists_title.push_back("Jet mass (GeV)");                  hists_rebin.push_back(10);   legs.push_back(false);            
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_JetPt_2btag");            pave.push_back(s2h);   hists_title.push_back("Jet p_{T} (GeV)");                 hists_rebin.push_back(10);   legs.push_back(false);          
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_2btag");      pave.push_back(s2h);   hists_title.push_back("Jet rapidity");                    hists_rebin.push_back(10);   legs.push_back(false);                
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_2btag");     pave.push_back(s2h);   hists_title.push_back("SoftDrop jet mass (GeV)");         hists_rebin.push_back(10);   legs.push_back(false);                 
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_Tau32_2btag");            pave.push_back(s2h);   hists_title.push_back("#tau_{3}/#tau_{2}");               hists_rebin.push_back(10);   legs.push_back(false);          
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_bDisc_2btag");            pave.push_back(s2h);   hists_title.push_back("Max subjet b-discriminant");       hists_rebin.push_back(10);   legs.push_back(false);          
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_inclusive");    pave.push_back(sih);   hists_title.push_back("Dijet mass (GeV)");                hists_rebin.push_back(10);   legs.push_back(false);                 
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_JetMass_inclusive");      pave.push_back(sih);   hists_title.push_back("Jet mass (GeV)");                  hists_rebin.push_back(10);   legs.push_back(false);               
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_JetPt_inclusive");        pave.push_back(sih);   hists_title.push_back("Jet p_{T} (GeV)");                 hists_rebin.push_back(10);   legs.push_back(false);             
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_inclusive");  pave.push_back(sih);   hists_title.push_back("Jet rapidity");                    hists_rebin.push_back(10);   legs.push_back(false);                   
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_inclusive"); pave.push_back(sih);   hists_title.push_back("SoftDrop jet mass (GeV)");         hists_rebin.push_back(10);   legs.push_back(false);                    
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_Tau32_inclusive");        pave.push_back(sih);   hists_title.push_back("#tau_{3}/#tau_{2}");               hists_rebin.push_back(10);   legs.push_back(false);             
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapHi_bDisc_inclusive");        pave.push_back(sih);   hists_title.push_back("Max subjet b-discriminant");       hists_rebin.push_back(10);   legs.push_back(false);             
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_0btag");        pave.push_back(s0l);   hists_title.push_back("Dijet mass (GeV)");                hists_rebin.push_back(10);   legs.push_back(false);              
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_JetMass_0btag");          pave.push_back(s0l);   hists_title.push_back("Jet mass (GeV)");                  hists_rebin.push_back(10);   legs.push_back(false);            
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_JetPt_0btag");            pave.push_back(s0l);   hists_title.push_back("Jet p_{T} (GeV)");                 hists_rebin.push_back(10);   legs.push_back(false);          
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_0btag");      pave.push_back(s0l);   hists_title.push_back("Jet rapidity");                    hists_rebin.push_back(10);   legs.push_back(false);                
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_0btag");     pave.push_back(s0l);   hists_title.push_back("SoftDrop jet mass (GeV)");         hists_rebin.push_back(10);   legs.push_back(false);                 
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_Tau32_0btag");            pave.push_back(s0l);   hists_title.push_back("#tau_{3}/#tau_{2}");               hists_rebin.push_back(10);   legs.push_back(false);          
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_bDisc_0btag");            pave.push_back(s0l);   hists_title.push_back("Max subjet b-discriminant");       hists_rebin.push_back(10);   legs.push_back(false);          
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_1btag");        pave.push_back(s1l);   hists_title.push_back("Dijet mass (GeV)");                hists_rebin.push_back(10);   legs.push_back(false);              
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_JetMass_1btag");          pave.push_back(s1l);   hists_title.push_back("Jet mass (GeV)");                  hists_rebin.push_back(10);   legs.push_back(false);            
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_JetPt_1btag");            pave.push_back(s1l);   hists_title.push_back("Jet p_{T} (GeV)");                 hists_rebin.push_back(10);   legs.push_back(false);          
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_1btag");      pave.push_back(s1l);   hists_title.push_back("Jet rapidity");                    hists_rebin.push_back(10);   legs.push_back(false);                
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_1btag");     pave.push_back(s1l);   hists_title.push_back("SoftDrop jet mass (GeV)");         hists_rebin.push_back(10);   legs.push_back(false);                 
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_Tau32_1btag");            pave.push_back(s1l);   hists_title.push_back("#tau_{3}/#tau_{2}");               hists_rebin.push_back(10);   legs.push_back(false);          
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_bDisc_1btag");            pave.push_back(s1l);   hists_title.push_back("Max subjet b-discriminant");       hists_rebin.push_back(10);   legs.push_back(false);          
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_2btag");        pave.push_back(s2l);   hists_title.push_back("Dijet mass (GeV)");                hists_rebin.push_back(10);   legs.push_back(false);             
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_JetMass_2btag");          pave.push_back(s2l);   hists_title.push_back("Jet mass (GeV)");                  hists_rebin.push_back(10);   legs.push_back(false);           
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_JetPt_2btag");            pave.push_back(s2l);   hists_title.push_back("Jet p_{T} (GeV)");                 hists_rebin.push_back(10);   legs.push_back(false);         
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_2btag");      pave.push_back(s2l);   hists_title.push_back("Jet rapidity");                    hists_rebin.push_back(10);   legs.push_back(false);               
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_2btag");     pave.push_back(s2l);   hists_title.push_back("SoftDrop jet mass (GeV)");         hists_rebin.push_back(10);   legs.push_back(false);                
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_Tau32_2btag");            pave.push_back(s2l);   hists_title.push_back("#tau_{3}/#tau_{2}");               hists_rebin.push_back(10);   legs.push_back(false);         
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_bDisc_2btag");            pave.push_back(s2l);   hists_title.push_back("Max subjet b-discriminant");       hists_rebin.push_back(10);   legs.push_back(false);         
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_inclusive");    pave.push_back(sil);   hists_title.push_back("Dijet mass (GeV)");                hists_rebin.push_back(10);   legs.push_back(false);                  
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_JetMass_inclusive");      pave.push_back(sil);   hists_title.push_back("Jet mass (GeV)");                  hists_rebin.push_back(10);   legs.push_back(false);                
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_JetPt_inclusive");        pave.push_back(sil);   hists_title.push_back("Jet p_{T} (GeV)");                 hists_rebin.push_back(10);   legs.push_back(false);              
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_inclusive");  pave.push_back(sil);   hists_title.push_back("Jet rapidity");                    hists_rebin.push_back(10);   legs.push_back(false);                    
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_inclusive"); pave.push_back(sil);   hists_title.push_back("SoftDrop jet mass (GeV)");         hists_rebin.push_back(10);   legs.push_back(false);                     
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_Tau32_inclusive");        pave.push_back(sil);   hists_title.push_back("#tau_{3}/#tau_{2}");               hists_rebin.push_back(10);   legs.push_back(false);              
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapLo_bDisc_inclusive");        pave.push_back(sil);   hists_title.push_back("Max subjet b-discriminant");       hists_rebin.push_back(10);   legs.push_back(false);              
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_0btag");        pave.push_back(s0i);   hists_title.push_back("Dijet mass (GeV)");                hists_rebin.push_back(10);   legs.push_back(false);             
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_JetMass_0btag");          pave.push_back(s0i);   hists_title.push_back("Jet mass (GeV)");                  hists_rebin.push_back(10);   legs.push_back(false);           
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_JetPt_0btag");            pave.push_back(s0i);   hists_title.push_back("Jet p_{T} (GeV)");                 hists_rebin.push_back(10);   legs.push_back(false);         
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_0btag");      pave.push_back(s0i);   hists_title.push_back("Jet rapidity");                    hists_rebin.push_back(10);   legs.push_back(false);               
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_0btag");     pave.push_back(s0i);   hists_title.push_back("SoftDrop jet mass (GeV)");         hists_rebin.push_back(10);   legs.push_back(false);                
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_Tau32_0btag");            pave.push_back(s0i);   hists_title.push_back("#tau_{3}/#tau_{2}");               hists_rebin.push_back(10);   legs.push_back(false);         
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_bDisc_0btag");            pave.push_back(s0i);   hists_title.push_back("Max subjet b-discriminant");       hists_rebin.push_back(10);   legs.push_back(false);         
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_1btag");        pave.push_back(s1i);   hists_title.push_back("Dijet mass (GeV)");                hists_rebin.push_back(10);   legs.push_back(false);              
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_JetMass_1btag");          pave.push_back(s1i);   hists_title.push_back("Jet mass (GeV)");                  hists_rebin.push_back(10);   legs.push_back(false);            
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_JetPt_1btag");            pave.push_back(s1i);   hists_title.push_back("Jet p_{T} (GeV)");                 hists_rebin.push_back(10);   legs.push_back(false);          
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_1btag");      pave.push_back(s1i);   hists_title.push_back("Jet rapidity");                    hists_rebin.push_back(10);   legs.push_back(false);                
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_1btag");     pave.push_back(s1i);   hists_title.push_back("SoftDrop jet mass (GeV)");         hists_rebin.push_back(10);   legs.push_back(false);                 
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_Tau32_1btag");            pave.push_back(s1i);   hists_title.push_back("#tau_{3}/#tau_{2}");               hists_rebin.push_back(10);   legs.push_back(false);          
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_bDisc_1btag");            pave.push_back(s1i);   hists_title.push_back("Max subjet b-discriminant");       hists_rebin.push_back(10);   legs.push_back(false);          
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_2btag");        pave.push_back(s2i);   hists_title.push_back("Dijet mass (GeV)");                hists_rebin.push_back(10);   legs.push_back(false);              
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_JetMass_2btag");          pave.push_back(s2i);   hists_title.push_back("Jet mass (GeV)");                  hists_rebin.push_back(10);   legs.push_back(false);            
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_JetPt_2btag");            pave.push_back(s2i);   hists_title.push_back("Jet p_{T} (GeV)");                 hists_rebin.push_back(10);   legs.push_back(false);          
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_2btag");      pave.push_back(s2i);   hists_title.push_back("Jet rapidity");                    hists_rebin.push_back(10);   legs.push_back(false);                
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_2btag");     pave.push_back(s2i);   hists_title.push_back("SoftDrop jet mass (GeV)");         hists_rebin.push_back(10);   legs.push_back(false);                 
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_Tau32_2btag");            pave.push_back(s2i);   hists_title.push_back("#tau_{3}/#tau_{2}");               hists_rebin.push_back(10);   legs.push_back(false);          
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_bDisc_2btag");            pave.push_back(s2i);   hists_title.push_back("Max subjet b-discriminant");       hists_rebin.push_back(10);   legs.push_back(false);          
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_inclusive");    pave.push_back(si);    hists_title.push_back("Dijet mass (GeV)");                hists_rebin.push_back(10);   legs.push_back(false);                  
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_JetMass_inclusive");      pave.push_back(si);    hists_title.push_back("Jet mass (GeV)");                  hists_rebin.push_back(10);   legs.push_back(false);                
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_JetPt_inclusive");        pave.push_back(si);    hists_title.push_back("Jet p_{T} (GeV)");                 hists_rebin.push_back(10);   legs.push_back(false);              
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_inclusive");  pave.push_back(si);    hists_title.push_back("Jet rapidity");                    hists_rebin.push_back(10);   legs.push_back(false);                    
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_inclusive"); pave.push_back(si);    hists_title.push_back("SoftDrop jet mass (GeV)");         hists_rebin.push_back(10);   legs.push_back(false);                     
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_Tau32_inclusive");        pave.push_back(si);    hists_title.push_back("#tau_{3}/#tau_{2}");               hists_rebin.push_back(10);   legs.push_back(false);              
	hists_names.push_back("mttPredDist2_tagMassSDTau32_dRapIn_bDisc_inclusive");        pave.push_back(si);    hists_title.push_back("Max subjet b-discriminant");       hists_rebin.push_back(10);   legs.push_back(false);              
                                

	hists_names.push_back("h_HT");                                     pave.push_back("Pre-selection");                          hists_title.push_back("HT");                                    hists_rebin.push_back(10);   legs.push_back(false);      
	hists_names.push_back("h_DijetMass");                              pave.push_back("Pre-selection");                          hists_title.push_back("DijetMass");                             hists_rebin.push_back(10);   legs.push_back(false);      
	hists_names.push_back("h_DeltaRap");                               pave.push_back("Pre-selection");                          hists_title.push_back("DeltaRap");                              hists_rebin.push_back(10);   legs.push_back(false);      
	hists_names.push_back("h_jet0rap");                                pave.push_back("Pre-selection");                          hists_title.push_back("Jet 0 rapidity");                        hists_rebin.push_back(10);   legs.push_back(false);      
	hists_names.push_back("h_jet0massSD");                             pave.push_back("Pre-selection");                          hists_title.push_back("Jet 0 SoftDrop mass (GeV)");             hists_rebin.push_back(10);   legs.push_back(false);      
	hists_names.push_back("h_jet0tau32");                              pave.push_back("Pre-selection");                          hists_title.push_back("Jet 0 #tau_{3}/#tau_{2}");               hists_rebin.push_back(10);   legs.push_back(true);      
	// hists_names.push_back("h_jet0tau21");                           pave.push_back("Pre-selection");                          hists_title.push_back("jet0tau21");                             hists_rebin.push_back(10);   legs.push_back(false);         
	// hists_names.push_back("h_jet0tau1");                            pave.push_back("Pre-selection");                          hists_title.push_back("jet0tau1");                              hists_rebin.push_back(10);   legs.push_back(false);         
	// hists_names.push_back("h_jet0tau2");                            pave.push_back("Pre-selection");                          hists_title.push_back("jet0tau2");                              hists_rebin.push_back(10);   legs.push_back(false);         
	// hists_names.push_back("h_jet0tau3");                            pave.push_back("Pre-selection");                          hists_title.push_back("jet0tau3");                              hists_rebin.push_back(10);   legs.push_back(false);         
	hists_names.push_back("h_jet0subjet0pt");                          pave.push_back("Pre-selection");                          hists_title.push_back("Jet 0 subjet 0 p_{T} (GeV)");            hists_rebin.push_back(10);   legs.push_back(false);      
	hists_names.push_back("h_jet0subjet1pt");                          pave.push_back("Pre-selection");                          hists_title.push_back("Jet 0 subjet 1 p_{T} (GeV)");            hists_rebin.push_back(10);   legs.push_back(false);      
	hists_names.push_back("h_jet0pt");                                 pave.push_back("Pre-selection");                          hists_title.push_back("Jet 0 p_{T} (GeV)");                     hists_rebin.push_back(10);   legs.push_back(false);              
	hists_names.push_back("h_jet0subjet0mass");                        pave.push_back("Pre-selection");                          hists_title.push_back("Jet 0 subjet 0 mass (GeV)");             hists_rebin.push_back(10);   legs.push_back(false);      
	hists_names.push_back("h_jet0subjet1mass");                        pave.push_back("Pre-selection");                          hists_title.push_back("Jet 0 subjet 1 mass (GeV)");             hists_rebin.push_back(10);   legs.push_back(false);      
	hists_names.push_back("h_jet0subjet0bdisc");                       pave.push_back("Pre-selection");                          hists_title.push_back("Jet 0 subjet 0 b-disc");                 hists_rebin.push_back(1 );   legs.push_back(false);      
	hists_names.push_back("h_jet0subjet1bdisc");                       pave.push_back("Pre-selection");                          hists_title.push_back("Jet 0 subjet 0 b-disc");                 hists_rebin.push_back(1 );   legs.push_back(false);      
	hists_names.push_back("h_jet0subjet0flav");                        pave.push_back("Pre-selection");                          hists_title.push_back("jet0subjet0flav");                       hists_rebin.push_back(1 );   legs.push_back(false);      
	hists_names.push_back("h_jet0subjet1flav");                        pave.push_back("Pre-selection");                          hists_title.push_back("jet0subjet1flav");                       hists_rebin.push_back(1 );   legs.push_back(false);      
	hists_names.push_back("h_jet0maxBdisc");                           pave.push_back("Pre-selection");                          hists_title.push_back("Jet 0 max subjet b-disc");               hists_rebin.push_back(1 );   legs.push_back(false);      
	hists_names.push_back("h_jet0maxBdiscflav");                       pave.push_back("Pre-selection");                          hists_title.push_back("jet0maxBdiscflav");                      hists_rebin.push_back(1 );   legs.push_back(false);      
	hists_names.push_back("h_jet1rap");                                pave.push_back("Pre-selection");                          hists_title.push_back("Jet 1 rapidity");                        hists_rebin.push_back(10);   legs.push_back(false);      
	hists_names.push_back("h_jet1massSD");                             pave.push_back("Pre-selection");                          hists_title.push_back("Jet 1 SoftDrop mass (GeV)");             hists_rebin.push_back(10);   legs.push_back(false);      
	hists_names.push_back("h_jet1tau32");                              pave.push_back("Pre-selection");                          hists_title.push_back("Jet 1 #tau_{3}/#tau_{2}");               hists_rebin.push_back(5 );   legs.push_back(true);      
	// hists_names.push_back("h_jet1tau21");                           pave.push_back("Pre-selection");                          hists_title.push_back("jet0tau21");                             hists_rebin.push_back(10);   legs.push_back(false);      
	// hists_names.push_back("h_jet1tau1");                            pave.push_back("Pre-selection");                          hists_title.push_back("jet0tau1");                              hists_rebin.push_back(1 );   legs.push_back(false);      
	// hists_names.push_back("h_jet1tau2");                            pave.push_back("Pre-selection");                          hists_title.push_back("jet0tau2");                              hists_rebin.push_back(1 );   legs.push_back(false);      
	// hists_names.push_back("h_jet1tau3");                            pave.push_back("Pre-selection");                          hists_title.push_back("jet0tau3");                              hists_rebin.push_back(1 );   legs.push_back(false);      
	hists_names.push_back("h_jet1subjet0pt");                          pave.push_back("Pre-selection");                          hists_title.push_back("Jet 1 subjet 0 p_{T} (GeV)");            hists_rebin.push_back(10);   legs.push_back(false);      
	hists_names.push_back("h_jet1subjet1pt");                          pave.push_back("Pre-selection");                          hists_title.push_back("Jet 1 subjet 1 p_{T} (GeV)");            hists_rebin.push_back(10);   legs.push_back(false);      
	hists_names.push_back("h_jet1pt");                                 pave.push_back("Pre-selection");                          hists_title.push_back("Jet 1 p_{T} (GeV)");                     hists_rebin.push_back(10);   legs.push_back(false);              
	hists_names.push_back("h_jet1subjet0mass");                        pave.push_back("Pre-selection");                          hists_title.push_back("Jet 1 subjet 0 mass (GeV)");             hists_rebin.push_back(10);   legs.push_back(false);      
	hists_names.push_back("h_jet1subjet1mass");                        pave.push_back("Pre-selection");                          hists_title.push_back("Jet 1 subjet 1 mass (GeV)");             hists_rebin.push_back(10);   legs.push_back(false);      
	hists_names.push_back("h_jet1subjet0bdisc");                       pave.push_back("Pre-selection");                          hists_title.push_back("Jet 1 subjet 0 b-disc");                 hists_rebin.push_back(1 );   legs.push_back(false);      
	hists_names.push_back("h_jet1subjet1bdisc");                       pave.push_back("Pre-selection");                          hists_title.push_back("Jet 1 subjet 0 b-disc");                 hists_rebin.push_back(1 );   legs.push_back(false);      
	hists_names.push_back("h_jet1subjet0flav");                        pave.push_back("Pre-selection");                          hists_title.push_back("jet1subjet0flav");                       hists_rebin.push_back(1 );   legs.push_back(false);      
	hists_names.push_back("h_jet1subjet1flav");                        pave.push_back("Pre-selection");                          hists_title.push_back("jet1subjet1flav");                       hists_rebin.push_back(1 );   legs.push_back(false);      
	hists_names.push_back("h_jet1maxBdisc");                           pave.push_back("Pre-selection");                          hists_title.push_back("Jet 1 max subjet b-disc");               hists_rebin.push_back(1 );   legs.push_back(false);      
	hists_names.push_back("h_jet1maxBdiscflav");                       pave.push_back("Pre-selection");                          hists_title.push_back("jet1maxBdiscflav");                      hists_rebin.push_back(1 );   legs.push_back(false);      
	hists_names.push_back("h_2btag_DijetMass");                        pave.push_back("2 b-tags, 0 t-tags");                     hists_title.push_back("DijetMass");                             hists_rebin.push_back(10);   legs.push_back(false);      
	hists_names.push_back("h_2btag_DeltaRap");                         pave.push_back("2 b-tags, 0 t-tags");                     hists_title.push_back("#Delta rapidity(jet 0,jet 1)");          hists_rebin.push_back(10);   legs.push_back(false);      
	hists_names.push_back("h_2btag_jet0massSD");                       pave.push_back("2 b-tags, 0 t-tags");                     hists_title.push_back("Jet 0 SoftDrop mass (GeV)");             hists_rebin.push_back(10);   legs.push_back(false);      
	hists_names.push_back("h_2btag_jet0tau32");                        pave.push_back("2 b-tags, 0 t-tags");                     hists_title.push_back("Jet 0 #tau_{3}/#tau_{2}");               hists_rebin.push_back(5 );   legs.push_back(false);      
	// hists_names.push_back("h_2btag_jet0tau21");                     pave.push_back("2 b-tags, 0 t-tags");                     hists_title.push_back("jet0tau21");                             hists_rebin.push_back(10);   legs.push_back(false);      
	// hists_names.push_back("h_2btag_jet0tau1");                      pave.push_back("2 b-tags, 0 t-tags");                     hists_title.push_back("jet0tau1");                              hists_rebin.push_back(10);   legs.push_back(false);      
	// hists_names.push_back("h_2btag_jet0tau2");                      pave.push_back("2 b-tags, 0 t-tags");                     hists_title.push_back("jet0tau2");                              hists_rebin.push_back(10);   legs.push_back(false);      
	// hists_names.push_back("h_2btag_jet0tau3");                      pave.push_back("2 b-tags, 0 t-tags");                     hists_title.push_back("jet0tau3");                              hists_rebin.push_back(10);   legs.push_back(false);      
	hists_names.push_back("h_2btag_jet0subjet0mass");                  pave.push_back("2 b-tags, 0 t-tags");                     hists_title.push_back("Jet 0 subjet 0 mass (GeV)");             hists_rebin.push_back(10);   legs.push_back(false);      
	hists_names.push_back("h_2btag_jet0subjet1mass");                  pave.push_back("2 b-tags, 0 t-tags");                     hists_title.push_back("Jet 0 subjet 1 mass (GeV)");             hists_rebin.push_back(10);   legs.push_back(false);      
	hists_names.push_back("h_2btag_jet1massSD");                       pave.push_back("2 b-tags, 0 t-tags");                     hists_title.push_back("Jet 1 SoftDrop mass (GeV)");             hists_rebin.push_back(10);   legs.push_back(false);      
	hists_names.push_back("h_2btag_jet1tau32");                        pave.push_back("2 b-tags, 0 t-tags");                     hists_title.push_back("Jet 1 #tau_{3}/#tau_{2}");               hists_rebin.push_back(5 );   legs.push_back(true);      
	// hists_names.push_back("h_2btag_jet1tau21");                     pave.push_back("2 b-tags, 0 t-tags");                     hists_title.push_back("jet1tau21");                             hists_rebin.push_back(10);   legs.push_back(false);      
	// hists_names.push_back("h_2btag_jet1tau1");                      pave.push_back("2 b-tags, 0 t-tags");                     hists_title.push_back("jet1tau1");                              hists_rebin.push_back(10);   legs.push_back(false);      
	// hists_names.push_back("h_2btag_jet1tau2");                      pave.push_back("2 b-tags, 0 t-tags");                     hists_title.push_back("jet1tau2");                              hists_rebin.push_back(10);   legs.push_back(false);      
	// hists_names.push_back("h_2btag_jet1tau3");                      pave.push_back("2 b-tags, 0 t-tags");                     hists_title.push_back("jet1tau3");                              hists_rebin.push_back(10);   legs.push_back(false);      
	hists_names.push_back("h_2btag_jet1subjet0mass");                  pave.push_back("2 b-tags, 0 t-tags");                     hists_title.push_back("Jet 1 subjet 0 mass (GeV)");             hists_rebin.push_back(10);   legs.push_back(false);      
	hists_names.push_back("h_2btag_jet1subjet1mass");                  pave.push_back("2 b-tags, 0 t-tags");                     hists_title.push_back("Jet 1 subjet 1 mass (GeV)");             hists_rebin.push_back(10);   legs.push_back(false);      
	hists_names.push_back("h_2btag_jet1ttag_jet0massSD");              pave.push_back("2 b-tags, jet 1 t-tagged");               hists_title.push_back("Jet 0 SoftDrop mass (GeV)");             hists_rebin.push_back(10);   legs.push_back(false);               
	hists_names.push_back("h_2btag_jet1ttag_jet0tau32");               pave.push_back("2 b-tags, jet 1 t-tagged");               hists_title.push_back("Jet 0 #tau_{3}/#tau_{2}");               hists_rebin.push_back(5 );   legs.push_back(true);               
	hists_names.push_back("h_2btag_jet1ttag_jet0tau21");               pave.push_back("2 b-tags, jet 1 t-tagged");               hists_title.push_back("Jet 0 #tau_{2}/#tau_{1}");               hists_rebin.push_back(5 );   legs.push_back(false);               
	hists_names.push_back("h_2btag_jet1ttag_jet0tau1");                pave.push_back("2 b-tags, jet 1 t-tagged");               hists_title.push_back("Jet 0 #tau_{1}");                        hists_rebin.push_back(5 );   legs.push_back(false);               
	hists_names.push_back("h_2btag_jet1ttag_jet0tau2");                pave.push_back("2 b-tags, jet 1 t-tagged");               hists_title.push_back("Jet 0 #tau_{2}");                        hists_rebin.push_back(5 );   legs.push_back(false);               
	hists_names.push_back("h_2btag_jet1ttag_jet0tau3");                pave.push_back("2 b-tags, jet 1 t-tagged");               hists_title.push_back("Jet 0 #tau_{3}");                        hists_rebin.push_back(5 );   legs.push_back(false);               
	hists_names.push_back("h_2btag_jet1ttag_jet0subjet0mass");         pave.push_back("2 b-tags, jet 1 t-tagged");               hists_title.push_back("Jet 0 subjet 0 mass (GeV)");             hists_rebin.push_back(10);   legs.push_back(false);               
	hists_names.push_back("h_2btag_jet1ttag_jet0subjet1mass");         pave.push_back("2 b-tags, jet 1 t-tagged");               hists_title.push_back("Jet 0 subjet 1 mass (GeV)");             hists_rebin.push_back(10);   legs.push_back(false);                
	hists_names.push_back("h_2btag_jet0ttag_jet1massSD");              pave.push_back("2 b-tags, jet 0 t-tagged");               hists_title.push_back("Jet 1 SoftDrop mass (GeV)");             hists_rebin.push_back(10);   legs.push_back(false);               
	hists_names.push_back("h_2btag_jet0ttag_jet1tau32");               pave.push_back("2 b-tags, jet 0 t-tagged");               hists_title.push_back("Jet 1 #tau_{3}/#tau_{2}");               hists_rebin.push_back(5 );   legs.push_back(true);               
	hists_names.push_back("h_2btag_jet0ttag_jet1tau21");               pave.push_back("2 b-tags, jet 0 t-tagged");               hists_title.push_back("Jet 1 #tau_{2}/#tau_{1}");               hists_rebin.push_back(5 );   legs.push_back(false);               
	hists_names.push_back("h_2btag_jet0ttag_jet1tau1");                pave.push_back("2 b-tags, jet 0 t-tagged");               hists_title.push_back("Jet 1 #tau_{1}");                        hists_rebin.push_back(5 );   legs.push_back(false);               
	hists_names.push_back("h_2btag_jet0ttag_jet1tau2");                pave.push_back("2 b-tags, jet 0 t-tagged");               hists_title.push_back("Jet 1 #tau_{2}");                        hists_rebin.push_back(5 );   legs.push_back(false);               
	hists_names.push_back("h_2btag_jet0ttag_jet1tau3");                pave.push_back("2 b-tags, jet 0 t-tagged");               hists_title.push_back("Jet 1 #tau_{3}");                        hists_rebin.push_back(5 );   legs.push_back(false);               
	hists_names.push_back("h_2btag_jet0ttag_jet1subjet0mass");         pave.push_back("2 b-tags, jet 0 t-tagged");               hists_title.push_back("Jet 1 subjet 0 mass (GeV)");             hists_rebin.push_back(10);   legs.push_back(false);               
	hists_names.push_back("h_2btag_jet0ttag_jet1subjet1mass");         pave.push_back("2 b-tags, jet 0 t-tagged");               hists_title.push_back("Jet 1 subjet 1 mass (GeV)");             hists_rebin.push_back(10);   legs.push_back(false);                 
	hists_names.push_back("h_2btag_jet1ttag_jet0tautag_jet0massSD");   pave.push_back("2 b-tags, jet 1 t-tag, jet 0 tau32 tag"); hists_title.push_back("Jet 0 SoftDrop mass (GeV)");             hists_rebin.push_back(10);   legs.push_back(false);               
	hists_names.push_back("h_2btag_jet1ttag_jet0masstag_jet0tau32");   pave.push_back("2 b-tags, jet 1 t-tag, jet 0 mass tag");  hists_title.push_back("Jet 0 #tau_{3}/#tau_{2}");               hists_rebin.push_back(5 );   legs.push_back(true);               
	hists_names.push_back("h_2btag_jet1ttag_jet0masstag_jet0tau21");   pave.push_back("2 b-tags, jet 1 t-tag, jet 0 mass tag");  hists_title.push_back("Jet 0 #tau_{2}/#tau_{1}");               hists_rebin.push_back(5 );   legs.push_back(false);               
	hists_names.push_back("h_2btag_jet1ttag_jet0masstag_jet0tau1");    pave.push_back("2 b-tags, jet 1 t-tag, jet 0 mass tag");  hists_title.push_back("Jet 0 #tau_{1}");                        hists_rebin.push_back(5 );   legs.push_back(false);               
	hists_names.push_back("h_2btag_jet1ttag_jet0masstag_jet0tau2");    pave.push_back("2 b-tags, jet 1 t-tag, jet 0 mass tag");  hists_title.push_back("Jet 0 #tau_{2}");                        hists_rebin.push_back(5 );   legs.push_back(false);               
	hists_names.push_back("h_2btag_jet1ttag_jet0masstag_jet0tau3");    pave.push_back("2 b-tags, jet 1 t-tag, jet 0 mass tag");  hists_title.push_back("Jet 0 #tau_{3}");                        hists_rebin.push_back(5 );   legs.push_back(false);               
	hists_names.push_back("h_2btag_jet0ttag_jet1tautag_jet1massSD");   pave.push_back("2 b-tags, jet 0 t-tag, jet 1 tau32 tag"); hists_title.push_back("Jet 1 SoftDrop mass (GeV)");             hists_rebin.push_back(10);   legs.push_back(false);               
	hists_names.push_back("h_2btag_jet0ttag_jet1masstag_jet1tau32");   pave.push_back("2 b-tags, jet 0 t-tag, jet 1 mass tag");  hists_title.push_back("Jet 1 #tau_{3}/#tau_{2}");               hists_rebin.push_back(5 );   legs.push_back(true);               
	hists_names.push_back("h_2btag_jet0ttag_jet1masstag_jet1tau21");   pave.push_back("2 b-tags, jet 0 t-tag, jet 1 mass tag");  hists_title.push_back("Jet 1 #tau_{2}/#tau_{1}");               hists_rebin.push_back(5 );   legs.push_back(false);               
	hists_names.push_back("h_2btag_jet0ttag_jet1masstag_jet1tau1");    pave.push_back("2 b-tags, jet 0 t-tag, jet 1 mass tag");  hists_title.push_back("Jet 1 #tau_{1}");                        hists_rebin.push_back(5 );   legs.push_back(false);               
	hists_names.push_back("h_2btag_jet0ttag_jet1masstag_jet1tau2");    pave.push_back("2 b-tags, jet 0 t-tag, jet 1 mass tag");  hists_title.push_back("Jet 1 #tau_{2}");                        hists_rebin.push_back(5 );   legs.push_back(false);               
	hists_names.push_back("h_2btag_jet0ttag_jet1masstag_jet1tau3");    pave.push_back("2 b-tags, jet 0 t-tag, jet 1 mass tag");  hists_title.push_back("Jet 1 #tau_{3}");                        hists_rebin.push_back(5 );   legs.push_back(false);               
	hists_names.push_back("h_topTag_jet0subjet0pt");                   pave.push_back("2 t-tags");                               hists_title.push_back("Jet 0 subjet 0 p_{T} (GeV)");            hists_rebin.push_back(10);   legs.push_back(false);               
	hists_names.push_back("h_topTag_jet0subjet0mass");                 pave.push_back("2 t-tags");                               hists_title.push_back("Jet 0 subjet 0 mass (GeV)");             hists_rebin.push_back(10);   legs.push_back(false);               
	hists_names.push_back("h_topTag_jet0subjet0bdisc");                pave.push_back("2 t-tags");                               hists_title.push_back("Jet 0 subjet 0 b-disc");                 hists_rebin.push_back(1 );   legs.push_back(false);               
	hists_names.push_back("h_topTag_jet0subjet0flav");                 pave.push_back("2 t-tags");                               hists_title.push_back("Jet 0 subjet 0 flavor");                 hists_rebin.push_back(1 );   legs.push_back(false);               
	hists_names.push_back("h_topTag_jet0subjet1pt");                   pave.push_back("2 t-tags");                               hists_title.push_back("Jet 0 subjet 1 p_{T} (GeV)");            hists_rebin.push_back(10);   legs.push_back(false);               
	hists_names.push_back("h_topTag_jet0subjet1mass");                 pave.push_back("2 t-tags");                               hists_title.push_back("Jet 0 subjet 1 mass (GeV)");             hists_rebin.push_back(10);   legs.push_back(false);               
	hists_names.push_back("h_topTag_jet0subjet1bdisc");                pave.push_back("2 t-tags");                               hists_title.push_back("Jet 0 subjet 1 b-disc");                 hists_rebin.push_back(1 );   legs.push_back(false);               
	hists_names.push_back("h_topTag_jet0subjet1flav");                 pave.push_back("2 t-tags");                               hists_title.push_back("Jet 0 subjet 1 flavor");                 hists_rebin.push_back(1 );   legs.push_back(false);               
	hists_names.push_back("h_topTag_jet0maxBdisc");                    pave.push_back("2 t-tags");                               hists_title.push_back("Jet 0 max subjet b-disc");               hists_rebin.push_back(1 );   legs.push_back(false);               
	hists_names.push_back("h_topTag_jet0maxBdiscflav");                pave.push_back("2 t-tags");                               hists_title.push_back("jet0maxBdiscflav");                      hists_rebin.push_back(1 );   legs.push_back(false);               
	hists_names.push_back("h_topTag_jet0pt");                          pave.push_back("2 t-tags");                               hists_title.push_back("Jet 0 p_{T} (GeV)");                     hists_rebin.push_back(10);   legs.push_back(false);                        
	hists_names.push_back("h_topTagbTag_jet0subjet0pt");               pave.push_back("2 t-tags, jet 0 b-tagged");               hists_title.push_back("Jet 0 subjet 0 p_{T} (GeV)");            hists_rebin.push_back(10);   legs.push_back(false);               
	hists_names.push_back("h_topTagbTag_jet0subjet0mass");             pave.push_back("2 t-tags, jet 0 b-tagged");               hists_title.push_back("Jet 0 subjet 0 mass (GeV)");             hists_rebin.push_back(10);   legs.push_back(false);               
	hists_names.push_back("h_topTagbTag_jet0subjet0bdisc");            pave.push_back("2 t-tags, jet 0 b-tagged");               hists_title.push_back("Jet 0 subjet 0 b-disc");                 hists_rebin.push_back(1 );   legs.push_back(false);               
	hists_names.push_back("h_topTagbTag_jet0subjet0flav");             pave.push_back("2 t-tags, jet 0 b-tagged");               hists_title.push_back("Jet 0 subjet 0 flavor");                 hists_rebin.push_back(1 );   legs.push_back(false);               
	hists_names.push_back("h_topTagbTag_jet0subjet1pt");               pave.push_back("2 t-tags, jet 0 b-tagged");               hists_title.push_back("Jet 0 subjet 1 p_{T} (GeV)");            hists_rebin.push_back(10);   legs.push_back(false);               
	hists_names.push_back("h_topTagbTag_jet0subjet1mass");             pave.push_back("2 t-tags, jet 0 b-tagged");               hists_title.push_back("Jet 0 subjet 1 mass (GeV)");             hists_rebin.push_back(10);   legs.push_back(false);               
	hists_names.push_back("h_topTagbTag_jet0subjet1bdisc");            pave.push_back("2 t-tags, jet 0 b-tagged");               hists_title.push_back("Jet 0 subjet 1 b-disc");                 hists_rebin.push_back(1 );   legs.push_back(false);               
	hists_names.push_back("h_topTagbTag_jet0subjet1flav");             pave.push_back("2 t-tags, jet 0 b-tagged");               hists_title.push_back("Jet 0 subjet 1 flavor");                 hists_rebin.push_back(1 );   legs.push_back(false);               
	hists_names.push_back("h_topTagbTag_jet0maxBdisc");                pave.push_back("2 t-tags, jet 0 b-tagged");               hists_title.push_back("Jet 0 max subjet b-disc");               hists_rebin.push_back(1 );   legs.push_back(false);               
	hists_names.push_back("h_topTagbTag_jet0maxBdiscflav");            pave.push_back("2 t-tags, jet 0 b-tagged");               hists_title.push_back("jet0maxBdiscflav");                      hists_rebin.push_back(1 );   legs.push_back(false);               
	hists_names.push_back("h_topTagbTag_jet0pt");                      pave.push_back("2 t-tags, jet 0 b-tagged");               hists_title.push_back("Jet 0 p_{T} (GeV)");                     hists_rebin.push_back(10);   legs.push_back(false);               
 

    cout<<"hists_names " <<hists_names .size() <<endl;;
    cout<<"hists_title " <<hists_title .size() <<endl;;
    cout<<"hists_rebin " <<hists_rebin .size() <<endl;;
    cout<<"legs        " <<legs        .size() <<endl;;
    cout<<"pave        " <<pave        .size() <<endl;;


	for (unsigned int i=0; i< hists_names.size(); i++ ){
		TH1D * hData = (TH1D*) fData ->Get( hists_names[i] ); 
		TH1D * hQCD  = (TH1D*) fQCD  ->Get( hists_names[i] ); 
		TH1D * hTT   = (TH1D*) fTT   ->Get( hists_names[i] ); 
		TH1D * hZp10 = (TH1D*) fZp10 ->Get( hists_names[i] ); 
		TH1D * hZp20 = (TH1D*) fZp20 ->Get( hists_names[i] ); 
		TH1D * hZp30 = (TH1D*) fZp30 ->Get( hists_names[i] ); 
		TH1D * hZp40 = (TH1D*) fZp40 ->Get( hists_names[i] ); 

		float lumi = 2592.3;
		float nttbar = 96834559.;//19665194.;
		float kfactor = 0.94;
		float ttSF = 0.89*0.89;

		hQCD ->Scale( 0.9 );
		hTT  ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
		hZp10->Scale( 1. * ttSF * lumi / 122204. ); 
	    hZp20->Scale( 1. * ttSF * lumi / 202573. ); 
	    hZp30->Scale( 1. * ttSF * lumi / 117069. ); 
	    hZp40->Scale( 1. * ttSF * lumi / 111625. );

	    double rebin = hists_rebin[i];
    	hData  ->Rebin(rebin); 
		hQCD   ->Rebin(rebin);
		hTT    ->Rebin(rebin); 
		hZp10  ->Rebin(rebin); 
		hZp20  ->Rebin(rebin); 
		hZp30  ->Rebin(rebin); 
		hZp40  ->Rebin(rebin); 


	    plotter(hists_names[i], hists_title[i], pave[i], hData, hTT, hQCD, hZp10, hZp20, hZp30, hZp40, legs[i] );
	}



    cout<<"hists_names " <<hists_names .size() <<endl;;
    cout<<"hists_title " <<hists_title .size() <<endl;;
    cout<<"hists_rebin " <<hists_rebin .size() <<endl;;
    cout<<"legs        " <<legs        .size() <<endl;;
    cout<<"pave        " <<pave        .size() <<endl;;

}
void plotter(TString histname, TString histtitle, TString pave, TH1D* hData, TH1D * hTT, TH1D* hQCD, TH1D * hZp10, TH1D * hZp20, TH1D * hZp30, TH1D * hZp40, bool legswitch ){

	hTT ->SetFillColor(kRed);
	hQCD->SetFillColor(kYellow);

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

	hData->SetMaximum(2.0 * hData->GetMaximum() );
    hData->GetYaxis()->SetTitle("Events");
    hData->GetYaxis()->SetTitleSize(0.042);
    hData->GetYaxis()->SetTitleOffset(0.95);

    // hData->SetBinErrorOption(TH1::kPoisson);
    hData->Draw("E0");

    THStack *stack = new THStack();
    stack->Add(hQCD );
    stack->Add( hTT );
    stack->Draw("hist same");
    hData->SetMarkerStyle(20);
    hData->SetMarkerSize(0.5);
    hData->SetLineColor(kBlack);
    hData->SetTitle("");

	hData->Draw("E0same");

    //errors                                                                                                                                
    float xsErr_top = 0.15;
    float lumiErr_top = 0.027;
    float topTagErr_top = 2*(0.09/0.89);
    float totalTopErr = 0.0;
    float totalQCDErr = 0.0;
    float totalHistErr = 0.0;

    TH1F *totalH = (TH1F *) hQCD->Clone("totalH");
    totalH->Add(hTT);

	totalH->SetFillStyle(3001);
    totalH->SetFillColor(kGray+1);
    totalH->Draw("E2 same");

    int n_xbins = totalH->GetNbinsX();


    hData->Draw("E0 same");

    hZp10->SetLineColor(kBlue);
    hZp20->SetLineColor(kGreen+1);
    hZp30->SetLineColor(kViolet);
    hZp40->SetLineColor(7);
    hZp10->SetLineWidth(2);
    hZp20->SetLineWidth(2);
    hZp30->SetLineWidth(2);
    hZp40->SetLineWidth(2);

    // hZp10->Draw("hist same");
    hZp20->Draw("hist same");
    hZp30->Draw("hist same");
    hZp40->Draw("hist same");

    // TLatex *categoryLabel = new TLatex();
    // categoryLabel->SetNDC();
    // categoryLabel->SetTextFont(62);
    // categoryLabel->SetTextSizePixels(20);

    // // categoryLabel->DrawLatex(0.7, 0.85, pave);
    // categoryLabel->DrawLatex(0.6, 0.85, pave);


	TPaveText *textbox1 = new TPaveText(0.6,0.85,0.93,0.89,"NDC");
	textbox1->SetFillColor(0);
	textbox1->SetLineColor(0);
	TText *line1 = textbox1->AddText(pave);
	line1->SetTextColor(1);
	// line1->SetTextSize(23);
	line1->SetTextFont(62);//43);
	line1->SetTextSizePixels(25);//43);
	line1->SetTextAlign(33); //first number = horizontal alignment (1 left, 2 center, 3 right). second number =vertical alignment (1 top, 2 center, 3 bottom)
	textbox1->Draw("same");


    // if (tag == 0) categoryLabel->DrawLatex(0.7, 0.85, "0 b-tags, |#Deltay| < 1.0");
    // if (tag == 1) categoryLabel->DrawLatex(0.7, 0.85, "1 b-tag, |#Deltay| < 1.0");
    // if (tag == 2) categoryLabel->DrawLatex(0.7, 0.85, "2 b-tags, |#Deltay| < 1.0");
    // if (tag == 3) categoryLabel->DrawLatex(0.7, 0.85, "0 b-tags, |#Deltay| > 1.0");
    // if (tag == 4) categoryLabel->DrawLatex(0.7, 0.85, "1 b-tag, |#Deltay| > 1.0");
    // if (tag == 5) categoryLabel->DrawLatex(0.7, 0.85, "2 b-tags, |#Deltay| > 1.0");
    // if (tag == 6) categoryLabel->DrawLatex(0.7, 0.85, "All Signal Regions");

    CMS_lumi(c1_2, 4, 10);

    gPad->RedrawAxis();

    double leg1 =0.67; double leg2 =0.4; double leg3 =0.91; double leg4 =0.83;
    double peg1 =0.14; double peg2 =0.4; double peg3 =0.38; double peg4 =0.83;
    TLegend *leg = new TLegend(leg1, leg2, leg3, leg4);
    leg->AddEntry(hData, "Data", "lp");
    leg->AddEntry(hQCD, "QCD simulation", "f");
    leg->AddEntry(hTT, "SM t#bar{t} simulation", "f");
    leg->AddEntry(hZp20, "2 TeV Narrow Z'", "l");
	leg->AddEntry(hZp30, "3 TeV Narrow Z'", "l");
	leg->AddEntry(hZp40, "4 TeV Narrow Z'", "l");
    leg->SetFillColor(0);
    leg->SetLineColor(0);
    
    TLegend *peg = new TLegend(peg1, peg2, peg3, peg4);
    peg->AddEntry(hData, "Data", "lp");
    peg->AddEntry(hQCD, "QCD simulation", "f");
    peg->AddEntry(hTT, "SM t#bar{t} simulation", "f");
    peg->AddEntry(hZp20, "2 TeV Narrow Z'", "l");
	peg->AddEntry(hZp30, "3 TeV Narrow Z'", "l");
	peg->AddEntry(hZp40, "4 TeV Narrow Z'", "l");
    peg->SetFillColor(0);
    peg->SetLineColor(0);
    
    if (legswitch)  peg->Draw("same");
 	if (!legswitch) leg->Draw("same");

    TH1F *ratioH = new TH1F();
    ratioH = (TH1F*) hData->Clone("ratio");
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
    ratioH->GetXaxis()->SetTitle( histtitle );
    ratioH->Draw("E0");

    ratioErrH->SetFillStyle(1001);
    ratioErrH->SetFillColor(kGray);
    ratioErrH->Draw("E2 same");

    TF1 *line = new TF1("line", "1", -7000, 7000);
    line->SetLineColor(kBlack);
    line->Draw("same");
    ratioH->Draw("E0 same");

    gPad->RedrawAxis();
                                                                                        
	c1->SaveAs("plots/"+histname+".pdf");
	c1->SaveAs("plots/"+histname+".png");
	c1_2->cd();
	hData->SetMaximum(30.0 * hData->GetMaximum() );
	c1_2->SetLogy(1);
	c1->SaveAs("plots/"+histname+"_log.pdf");
	c1->SaveAs("plots/"+histname+"_log.png");

}