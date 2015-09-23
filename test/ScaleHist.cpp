// [] .L ScaleHists.cpp+
// [] run()
// Jim Dolen 2015

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

TH1D * scaleHistsFromPtHatRootFilesReturnHist( string , vector <TFile* > & );

void run(){
  // gROOT->ProcessLine(".L /Users/jdolen/Dropbox/Code/MyAnalysisRootFunctions_NEW.C");
  // gROOT->ProcessLine(".L /Users/jdolen/Dropbox/Code/JMAR/TopTagging/MyFunctions_TopTag.C");

  TFile *out = new TFile("ModMass_2015_09_22.root","RECREATE");

  // TFile *F_qcdpt170   = new TFile("ntuples/ntuple_QCD_Pt_170to300_RunIISpring15DR74-Asympt50ns_2015_09_22.root");
  TFile *F_qcdpt300   = new TFile("ntuples/ntuple_QCD_Pt_300to470_RunIISpring15DR74-Asympt50ns_2015_09_22c.root");
  TFile *F_qcdpt470   = new TFile("ntuples/ntuple_QCD_Pt_470to600_RunIISpring15DR74-Asympt50ns_2015_09_22.root");
  TFile *F_qcdpt600   = new TFile("ntuples/ntuple_QCD_Pt_600to800_RunIISpring15DR74-Asympt50ns_2015_09_22c.root");
  TFile *F_qcdpt800   = new TFile("ntuples/ntuple_QCD_Pt_800to1000_RunIISpring15DR74-Asympt50ns_2015_09_22b.root");
  TFile *F_qcdpt1000  = new TFile("ntuples/ntuple_QCD_Pt_1000to1400_RunIISpring15DR74-Asympt50ns_2015_09_22.root");
  TFile *F_qcdpt1400  = new TFile("ntuples/ntuple_QCD_Pt_1400to1800_RunIISpring15DR74-Asympt50ns_2015_09_22.root");
  TFile *F_qcdpt1800  = new TFile("ntuples/ntuple_QCD_Pt_1800to2400_RunIISpring15DR74-Asympt50ns_2015_09_22.root");
  TFile *F_qcdpt2400  = new TFile("ntuples/ntuple_QCD_Pt_2400to3200_RunIISpring15DR74-Asympt50ns_2015_09_22.root");
  TFile *F_qcdpt3200  = new TFile("ntuples/ntuple_QCD_Pt_3200toInf_RunIISpring15DR74-Asympt50ns_2015_09_22.root");
 

  std::vector <TFile* > rootFiles;
  // rootFiles.push_back( F_qcdpt170  );
  // rootFiles.push_back( F_qcdpt300  );
  rootFiles.push_back( F_qcdpt470  );
  rootFiles.push_back( F_qcdpt600  );
  rootFiles.push_back( F_qcdpt800  );
  rootFiles.push_back( F_qcdpt1000 );
  rootFiles.push_back( F_qcdpt1400 );
  rootFiles.push_back( F_qcdpt1800 );
  rootFiles.push_back( F_qcdpt2400 );
  rootFiles.push_back( F_qcdpt3200 );

  // for (unsigned int i=0; i<rootFiles.size(); i++){
  //   TH1D * h1 = (TH1D*)  rootFiles[i] -> Get( "h_mAK8_ModMass" );
  //   cout<<h1->Integral()<<endl;
  // }

  vector <string> histnames;
  histnames.push_back("h_mAK8_ModMass");           
  histnames.push_back("h_mSDropAK8_ModMass");      
  histnames.push_back("h_mAK8_ModMass_jet0");      
  histnames.push_back("h_mSDropAK8_ModMass_jet0"); 
  histnames.push_back("h_mAK8_ModMass_jet1");      
  histnames.push_back("h_mSDropAK8_ModMass_jet1"); 

  out->cd();
  for (unsigned int i=0; i<histnames.size(); i++){
    TH1D  * hist = scaleHistsFromPtHatRootFilesReturnHist( histnames[i].c_str(), rootFiles) ;
    hist->SetName(histnames[i].c_str());
    hist->Write();
  }
  out->Write();
  out->Close();
}



TH1D * scaleHistsFromPtHatRootFilesReturnHist( string histname, vector <TFile* > &rootFiles )
{
  const double lumi = 40.03 ; // pb-1
  vector <double> mcscales;
  // mcscales.push_back(  117276.          / 3468514. * lumi);  // xs / nevents * lumi
  // mcscales.push_back(    7823.          / 2936644. * lumi);
  mcscales.push_back(     648.2         / 1971800. * lumi);
  mcscales.push_back(     186.9         / 1981608. * lumi);
  mcscales.push_back(      32.293       / 1990208. * lumi);
  mcscales.push_back(       9.4183      / 1487712. * lumi);
  mcscales.push_back(       0.84265     /  197959. * lumi);
  mcscales.push_back(       0.114943    /  194924. * lumi);
  mcscales.push_back(       0.00682981  /  198383. * lumi);
  mcscales.push_back(       0.000165445 /  194528. * lumi);

  TH1D * htemp = (TH1D*)  rootFiles[0] -> Get( histname.c_str() );
  TH1D * h_sum = (TH1D*)htemp->Clone(); 
  h_sum->Reset();
  h_sum->Sumw2();

  for (unsigned int i=0; i<rootFiles.size(); i++){
    TH1D * h1 = (TH1D*)  rootFiles[i] -> Get( histname.c_str() );
    // h1->Sumw2();
    h1->Scale(mcscales[i]);
    h_sum->Add(h1);
    // cout<<mcscales[i]<<"  "<<h1->Integral()<<endl;
  }
  return h_sum;
}
