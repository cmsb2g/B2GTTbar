//---------------------
// ScaleQCD.cpp
// Scale and add histograms for HT and pT binned QCD samples
// J. Dolen
//---------------------
// How to run:
//---------------------
// [] .L ScaleQCD.cpp+
// [] run(int j, string datelabel)  ## j== 0 kinematic, 1 mistag, 2 bkgd est
//---------------------
// example: run(0, "20170309btag_nom_PUw")
// example: run(1, "misMar20_nom_PUw")
//---------------------

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



  // if (j==0)     { cout<<"Scaling kinematic QCD plots"<<endl;                  }     
  // else if (j==1){ cout<<"Scaling mistag QCD plots"<<endl;                     }  
  // else if (j==2){ cout<<"Scaling bkgd QCD plots"<<endl;                       }
  // else if (j==3){ cout<<"Scaling modmass QCD plots"<<endl;                    }
  // else if (j==4){ cout<<"Scaling 2D kinematic"<<endl;                    }
  // else { cout<<"Please enter 0 kinematic, 1 mistag, 2 bkgd est, 3 modmass, 4 2D kinematic"<<endl; return;}


//-----------------------------------------------------------

void run(int j, string datelabel);
void runHT(vector<string>, int, string);
void runPt(vector<string>, int, string);
TH1D * scaleHists_QCD_PTbinned_ReturnHist(string, vector <TFile* > &, vector <TFile* > &, double, vector <bool>  );
TH1D * scaleHists_QCD_HTbinned_ReturnHist(string, vector <TFile* > &, vector <TFile* > &, double, vector <bool>, vector <bool>  );
 

//-----------------------------------------------------------

void runHT(vector<string> histnames, int type, string datelabel){

  cout<<"runHT( ,"<<type<<", "<<datelabel<<")"<<endl;

  gROOT->SetBatch(); 

  string typelabel;
  if (type == 0) typelabel = "histsKinemat";
  if (type == 1) typelabel = "histsAntiTag";
  if (type == 2) typelabel = "histsBkgdEst";
  if (type == 3) typelabel = "histsModMass";
  if (type == 4) typelabel = "histsKinemat";

  string outname = "runs/" + typelabel+"_"+datelabel+"_b2gtreeV5_QCD_HTscaled.root";
  if (type == 4)  outname = "runs/" + typelabel+"_2D_"+datelabel+"_b2gtreeV5_QCD_HTscaled.root";
  TFile *out = new TFile(outname.c_str(),"RECREATE");

  double lumi = 1;
  string file_location = "/uscms/home/camclean/nobackup/B2G2016/CMSSW_8_0_26/src/Analysis/B2GTTbar/test/runs/";
  //string file_location = "/uscms_data/d2/jdolen/B2G2016/CMSSW_8_0_26_patch2/src/Analysis/B2GTTbar/test/runs/";///Users/jdolen/Nobackup/B2G2016/V5/runs/";
  // string file_location = "/Users/jdolen/NoBackup/B2G2016/V5/runs/";//"/Users/jdolen/Code/GitHub/B2GTTbar/test/runs/";

  // string s1 = typelabel+"_"+datelabel+"b2gtreeV5_QCD_HT300to500_RunIISummer16MiniAODv2_all.root";
  // string s2 = typelabel+"_"+datelabel+"b2gtreeV5_QCD_HT300to500_RunIISummer16MiniAODv2_all.root";
  // string s3 = typelabel+"_"+datelabel+"b2gtreeV5_QCD_HT300to500_RunIISummer16MiniAODv2_all.root";
  // string s4 = typelabel+"_"+datelabel+"b2gtreeV5_QCD_HT500to700_RunIISummer16MiniAODv2.root";
  // string s5 = typelabel+"_"+datelabel+"b2gtreeV5_QCD_HT700to1000_RunIISummer16MiniAODv2.root";
  // string s6 = typelabel+"_"+datelabel+"b2gtreeV5_QCD_HT1000to1500_RunIISummer16MiniAODv2_try2_all.root";
  // string s7 = typelabel+"_"+datelabel+"b2gtreeV5_QCD_HT1500to2000_RunIISummer16MiniAODv2_all.root";
  // string s8 = typelabel+"_"+datelabel+"b2gtreeV5_QCD_HT2000toInf_RunIISummer16MiniAODv2.root";

  // string sa1 = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_HT300to500_RunIISummer16MiniAODv2_all.root";
  string sa2 = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_HT300to500_RunIISummer16MiniAODv2_all.root";
  string sa3 = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_HT300to500_RunIISummer16MiniAODv2_all.root";
  string sa4 = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_HT500to700_RunIISummer16MiniAODv2.root";
  string sa5 = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_HT700to1000_RunIISummer16MiniAODv2.root";
  string sa6 = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_HT1000to1500_RunIISummer16MiniAODv2_try2_all.root";
  string sa7 = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_HT1500to2000_RunIISummer16MiniAODv2_all.root";
  string sa8 = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_HT2000toInf_RunIISummer16MiniAODv2.root";

  // string sb1 = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_HT200to300_RunIISummer16MiniAODv2_ext1.root";
  string sb2 = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_HT200to300_RunIISummer16MiniAODv2_ext1.root";
  string sb3 = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_HT300to500_RunIISummer16MiniAODv2_ext1.root";
  string sb4 = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_HT500to700_RunIISummer16MiniAODv2_ext1_try2.root";
  string sb5 = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_HT700to1000_RunIISummer16MiniAODv2_ext1_missing230.root";
  string sb6 = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_HT1000to1500_RunIISummer16MiniAODv2_ext1.root";
  string sb7 = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_HT1500to2000_RunIISummer16MiniAODv2_ext1.root";
  string sb8 = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_HT2000toInf_RunIISummer16MiniAODv2_ext1.root";
  
  TFile * Fa_HT200to300   = new TFile( (file_location+sa2).c_str() );
  TFile * Fa_HT300to500   = new TFile( (file_location+sa3).c_str() );
  TFile * Fa_HT500to700   = new TFile( (file_location+sa4).c_str() );
  TFile * Fa_HT700to1000  = new TFile( (file_location+sa5).c_str() );
  TFile * Fa_HT1000to1500 = new TFile( (file_location+sa6).c_str() );
  TFile * Fa_HT1500to2000 = new TFile( (file_location+sa7).c_str() );
  TFile * Fa_HT2000toInf  = new TFile( (file_location+sa8).c_str() );

  TFile * Fb_HT200to300   = new TFile( (file_location+sb2).c_str() );
  TFile * Fb_HT300to500   = new TFile( (file_location+sb3).c_str() );
  TFile * Fb_HT500to700   = new TFile( (file_location+sb4).c_str() );
  TFile * Fb_HT700to1000  = new TFile( (file_location+sb5).c_str() );
  TFile * Fb_HT1000to1500 = new TFile( (file_location+sb6).c_str() );
  TFile * Fb_HT1500to2000 = new TFile( (file_location+sb7).c_str() );
  TFile * Fb_HT2000toInf  = new TFile( (file_location+sb8).c_str() );

  if (Fa_HT200to300   ->IsZombie() ){ cout<<"Fa_HT200to300  ->IsZombie()"<<endl; delete Fa_HT200to300  ; Fa_HT200to300   = 0;}
  if (Fa_HT300to500   ->IsZombie() ){ cout<<"Fa_HT300to500  ->IsZombie()"<<endl; delete Fa_HT300to500  ; Fa_HT300to500   = 0;}
  if (Fa_HT500to700   ->IsZombie() ){ cout<<"Fa_HT500to700  ->IsZombie()"<<endl; delete Fa_HT500to700  ; Fa_HT500to700   = 0;}
  if (Fa_HT700to1000  ->IsZombie() ){ cout<<"Fa_HT700to1000 ->IsZombie()"<<endl; delete Fa_HT700to1000 ; Fa_HT700to1000  = 0;}
  if (Fa_HT1000to1500 ->IsZombie() ){ cout<<"Fa_HT1000to1500->IsZombie()"<<endl; delete Fa_HT1000to1500; Fa_HT1000to1500 = 0;}
  if (Fa_HT1500to2000 ->IsZombie() ){ cout<<"Fa_HT1500to2000->IsZombie()"<<endl; delete Fa_HT1500to2000; Fa_HT1500to2000 = 0;}
  if (Fa_HT2000toInf  ->IsZombie() ){ cout<<"Fa_HT2000toInf ->IsZombie()"<<endl; delete Fa_HT2000toInf ; Fa_HT2000toInf  = 0;}
  
  if (Fb_HT200to300   ->IsZombie() ){ cout<<"Fb_HT200to300  ->IsZombie()"<<endl; delete Fb_HT200to300  ; Fb_HT200to300   = 0;}
  if (Fb_HT300to500   ->IsZombie() ){ cout<<"Fb_HT300to500  ->IsZombie()"<<endl; delete Fb_HT300to500  ; Fb_HT300to500   = 0;}
  if (Fb_HT500to700   ->IsZombie() ){ cout<<"Fb_HT500to700  ->IsZombie()"<<endl; delete Fb_HT500to700  ; Fb_HT500to700   = 0;}
  if (Fb_HT700to1000  ->IsZombie() ){ cout<<"Fb_HT700to1000 ->IsZombie()"<<endl; delete Fb_HT700to1000 ; Fb_HT700to1000  = 0;}
  if (Fb_HT1000to1500 ->IsZombie() ){ cout<<"Fb_HT1000to1500->IsZombie()"<<endl; delete Fb_HT1000to1500; Fb_HT1000to1500 = 0;}
  if (Fb_HT1500to2000 ->IsZombie() ){ cout<<"Fb_HT1500to2000->IsZombie()"<<endl; delete Fb_HT1500to2000; Fb_HT1500to2000 = 0;}
  if (Fb_HT2000toInf  ->IsZombie() ){ cout<<"Fb_HT2000toInf ->IsZombie()"<<endl; delete Fb_HT2000toInf ; Fb_HT2000toInf  = 0;}

  if (Fa_HT200to300  ==0) { cout<<"Did not open Fa_HT200to300  "<<endl; return;} else {cout<<"Opened "<<file_location + sa2 <<endl; }
  if (Fa_HT300to500  ==0) { cout<<"Did not open Fa_HT300to500  "<<endl; return;} else {cout<<"Opened "<<file_location + sa3 <<endl; }
  if (Fa_HT500to700  ==0) { cout<<"Did not open Fa_HT500to700  "<<endl; return;} else {cout<<"Opened "<<file_location + sa4 <<endl; }
  if (Fa_HT700to1000 ==0) { cout<<"Did not open Fa_HT700to1000 "<<endl; return;} else {cout<<"Opened "<<file_location + sa5 <<endl; }
  if (Fa_HT1000to1500==0) { cout<<"Did not open Fa_HT1000to1500"<<endl; return;} else {cout<<"Opened "<<file_location + sa6 <<endl; }
  if (Fa_HT1500to2000==0) { cout<<"Did not open Fa_HT1500to2000"<<endl; return;} else {cout<<"Opened "<<file_location + sa7 <<endl; }
  if (Fa_HT2000toInf ==0) { cout<<"Did not open Fa_HT2000toInf "<<endl; return;} else {cout<<"Opened "<<file_location + sa8 <<endl; }

  if (Fb_HT200to300  ==0) { cout<<"Did not open Fb_HT200to300  "<<endl; return;} else {cout<<"Opened "<<file_location + sb2 <<endl; }
  if (Fb_HT300to500  ==0) { cout<<"Did not open Fb_HT300to500  "<<endl; return;} else {cout<<"Opened "<<file_location + sb3 <<endl; }
  if (Fb_HT500to700  ==0) { cout<<"Did not open Fb_HT500to700  "<<endl; return;} else {cout<<"Opened "<<file_location + sb4 <<endl; }
  if (Fb_HT700to1000 ==0) { cout<<"Did not open Fb_HT700to1000 "<<endl; return;} else {cout<<"Opened "<<file_location + sb5 <<endl; }
  if (Fb_HT1000to1500==0) { cout<<"Did not open Fb_HT1000to1500"<<endl; return;} else {cout<<"Opened "<<file_location + sb6 <<endl; }
  if (Fb_HT1500to2000==0) { cout<<"Did not open Fb_HT1500to2000"<<endl; return;} else {cout<<"Opened "<<file_location + sb7 <<endl; }
  if (Fb_HT2000toInf ==0) { cout<<"Did not open Fb_HT2000toInf "<<endl; return;} else {cout<<"Opened "<<file_location + sb8 <<endl; }


  std::vector <TFile* > rootFilesA;
  std::vector <TFile* > rootFilesB;

  rootFilesA.push_back( Fb_HT200to300   ); // nominal   HT100to200   // THIS IS A HACK 
  rootFilesA.push_back( Fb_HT200to300   ); // nominal   HT200to300   // THIS IS A HACK 
  rootFilesA.push_back( Fa_HT300to500   ); // nominal   HT300to500   
  rootFilesA.push_back( Fa_HT500to700   ); // nominal   HT500to700   
  rootFilesA.push_back( Fa_HT700to1000  ); // nominal   HT700to1000  
  rootFilesA.push_back( Fa_HT1000to1500 ); // nominal   HT1000to1500 
  rootFilesA.push_back( Fa_HT1500to2000 ); // nominal   HT1500to2000 
  rootFilesA.push_back( Fa_HT2000toInf  ); // nominal   HT2000toInf  
  
  rootFilesB.push_back( Fb_HT200to300   ); // extension HT100to200   // THIS IS A HACK  
  rootFilesB.push_back( Fb_HT200to300   ); // extension HT200to300   
  rootFilesB.push_back( Fb_HT300to500   ); // extension HT300to500   
  rootFilesB.push_back( Fb_HT500to700   ); // extension HT500to700   
  rootFilesB.push_back( Fb_HT700to1000  ); // extension HT700to1000  
  rootFilesB.push_back( Fb_HT1000to1500 ); // extension HT1000to1500 
  rootFilesB.push_back( Fb_HT1500to2000 ); // extension HT1500to2000 
  rootFilesB.push_back( Fb_HT2000toInf  ); // extension HT2000toInf  

  std::vector <bool > use_nominal;
  use_nominal.push_back( false  ); // extension HT100to200   
  use_nominal.push_back( false  ); // extension HT200to300   
  use_nominal.push_back( true  ); // extension HT300to500   
  use_nominal.push_back( true  ); // extension HT500to700   
  use_nominal.push_back( true  ); // extension HT700to1000  
  use_nominal.push_back( true  ); // extension HT1000to1500 
  use_nominal.push_back( true  ); // extension HT1500to2000 
  use_nominal.push_back( true  ); // extension HT2000toInf  

  std::vector <bool > use_extensions;
  use_extensions.push_back( false ); // extension HT100to200   
  use_extensions.push_back( true  ); // extension HT200to300   
  use_extensions.push_back( true  ); // extension HT300to500   
  use_extensions.push_back( true  ); // extension HT500to700   
  use_extensions.push_back( true  ); // extension HT700to1000  
  use_extensions.push_back( true  ); // extension HT1000to1500 
  use_extensions.push_back( true  ); // extension HT1500to2000 
  use_extensions.push_back( true  ); // extension HT2000toInf  

      
                                                             
  out->cd();
  for (unsigned int i=0; i<histnames.size(); i++){
    cout<<"Getting "<<histnames[i]<<endl;
    TH1D  * hist = scaleHists_QCD_HTbinned_ReturnHist( histnames[i].c_str(), rootFilesA, rootFilesB, lumi, use_nominal, use_extensions) ;
    cout<<"Got"<<endl;
    hist->SetName(histnames[i].c_str()); cout<<"d"<<endl;
    hist->Write(); cout<<"d"<<endl;

    // TH1D  * hist = scaleHists_QCD_PTbinned_ReturnHist( histnames[i].c_str(), rootFiles, lumi) ;
    // hist->SetName(histnames[i].c_str());
    // hist->Write();

  }
  cout<<"Writing"<<endl;
  out->Write();
  out->Close();

  Fa_HT300to500    ->Close();
  Fa_HT300to500    ->Close();
  Fa_HT300to500    ->Close();
  Fa_HT500to700    ->Close();
  Fa_HT700to1000   ->Close();
  Fa_HT1000to1500  ->Close();
  Fa_HT1500to2000  ->Close();
  Fa_HT2000toInf   ->Close();
  Fb_HT200to300    ->Close();
  Fb_HT200to300    ->Close();
  Fb_HT300to500    ->Close();
  Fb_HT500to700    ->Close();
  Fb_HT700to1000   ->Close();
  Fb_HT1000to1500  ->Close();
  Fb_HT1500to2000  ->Close();
  Fb_HT2000toInf   ->Close();

}

void runPt(vector<string> histnames, int type, string datelabel){

  cout<<"runPt( ,"<<type<<", "<<datelabel<<")"<<endl;

  gROOT->SetBatch(); 

  string typelabel;
  if (type == 0) typelabel = "histsKinemat";
  if (type == 1) typelabel = "histsAntiTag";
  if (type == 2) typelabel = "histsBkgdEst";
  if (type == 3) typelabel = "histsModMass";
  if (type == 4) typelabel = "histsKinemat";


  string outname = "runs/" + typelabel+"_"+datelabel+"_b2gtreeV5_QCD_Ptscaled.root";
  if (type == 4)  outname = "runs/" + typelabel+"_2D_"+datelabel+"_b2gtreeV5_QCD_Ptscaled.root";

  TFile *out = new TFile(outname.c_str(),"RECREATE");

  double lumi = 1;
  string file_location = "/uscms/home/camclean/nobackup/B2G2016/CMSSW_8_0_26/src/Analysis/B2GTTbar/test/runs/";
  //string file_location = "/uscms_data/d2/jdolen/B2G2016/CMSSW_8_0_26_patch2/src/Analysis/B2GTTbar/test/runs/";///Users/jdolen/Nobackup/B2G2016/V5/runs/";
  // string file_location = "/Users/jdolen/NoBackup/B2G2016/V5/runs/";//"/Users/jdolen/Code/GitHub/B2GTTbar/test/runs/";



  // string s1  = "histsKinemat_20170309btag_nom_PUw_b2gtreeV5_QCD_Pt_120to170_pythia8_RunIISummer16MiniAODv2.root";
  // string s2  = "histsKinemat_20170309btag_nom_PUw_b2gtreeV5_QCD_Pt_170to300_pythia8_RunIISummer16MiniAODv2.root";
  // string s3  = "histsKinemat_20170309btag_nom_PUw_b2gtreeV5_QCD_Pt_300to470_pythia8_RunIISummer16MiniAODv2.root";
  // string s4  = "histsKinemat_20170309btag_nom_PUw_b2gtreeV5_QCD_Pt_470to600_pythia8_RunIISummer16MiniAODv2.root";
  // string s5  = "histsKinemat_20170309btag_nom_PUw_b2gtreeV5_QCD_Pt_600to800_pythia8_RunIISummer16MiniAODv2.root";
  // string s6  = "histsKinemat_20170309btag_nom_PUw_b2gtreeV5_QCD_Pt_800to1000_pythia8_RunIISummer16MiniAODv2_try3.root";
  // string s7  = "histsKinemat_20170309btag_nom_PUw_b2gtreeV5_QCD_Pt_1000to1400_pythia8_RunIISummer16MiniAODv2.root";
  // string s8  = "histsKinemat_20170309btag_nom_PUw_b2gtreeV5_QCD_Pt_1400to1800_pythia8_RunIISummer16MiniAODv2.root";
  // string s9  = "histsKinemat_20170309btag_nom_PUw_b2gtreeV5_QCD_Pt_1800to2400_pythia8_RunIISummer16MiniAODv2.root";
  // string s10 = "histsKinemat_20170309btag_nom_PUw_b2gtreeV5_QCD_Pt_2400to3200_pythia8_RunIISummer16MiniAODv2.root";
  // string s11 = "histsKinemat_20170309btag_nom_PUw_b2gtreeV5_QCD_Pt_3200toInf_pythia8_RunIISummer16MiniAODv2_try3.root";

  // Primary samples
  string sa1  = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_Pt_120to170_pythia8_RunIISummer16MiniAODv2.root";
  string sa2  = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_Pt_170to300_pythia8_RunIISummer16MiniAODv2.root";
  string sa3  = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_Pt_300to470_pythia8_RunIISummer16MiniAODv2.root";
  string sa4  = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_Pt_470to600_pythia8_RunIISummer16MiniAODv2_try2.root";
  string sa5  = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_Pt_600to800_pythia8_RunIISummer16MiniAODv2.root";
  string sa6  = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_Pt_800to1000_pythia8_RunIISummer16MiniAODv2_try3.root";
  string sa7  = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_Pt_1000to1400_pythia8_RunIISummer16MiniAODv2.root";
  string sa8  = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_Pt_1400to1800_pythia8_RunIISummer16MiniAODv2.root";
  string sa9  = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_Pt_1800to2400_pythia8_RunIISummer16MiniAODv2.root";
  string sa10 = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_Pt_2400to3200_pythia8_RunIISummer16MiniAODv2.root";
  string sa11 = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_Pt_3200toInf_pythia8_RunIISummer16MiniAODv2_try3.root";

  // Extension samples
  string sb1  = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_Pt_2400to3200_pythia8_RunIISummer16MiniAODv2_ext1.root";
  string sb2  = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_Pt_2400to3200_pythia8_RunIISummer16MiniAODv2_ext1.root";
  string sb3  = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_Pt_300to470_pythia8_RunIISummer16MiniAODv2_ext1.root";
  string sb4  = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_Pt_470to600_pythia8_RunIISummer16MiniAODv2_backup.root";
  string sb5  = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_Pt_600to800_pythia8_RunIISummer16MiniAODv2_ext1.root";
  string sb6  = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_Pt_800to1000_pythia8_RunIISummer16MiniAODv2_ext1.root";
  string sb7  = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_Pt_1000to1400_pythia8_RunIISummer16MiniAODv2_ext1.root";
  string sb8  = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_Pt_1400to1800_pythia8_RunIISummer16MiniAODv2_ext1.root";
  string sb9  = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_Pt_1800to2400_pythia8_RunIISummer16MiniAODv2_ext1.root";
  string sb10 = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_Pt_2400to3200_pythia8_RunIISummer16MiniAODv2_ext1.root";
  string sb11 = typelabel+"_"+datelabel+"_b2gtreeV5_QCD_Pt_2400to3200_pythia8_RunIISummer16MiniAODv2_ext1.root";

  TFile *Fa_qcdpt120   = new TFile(  ( file_location + sa1  ).c_str()  );
  TFile *Fa_qcdpt170   = new TFile(  ( file_location + sa2  ).c_str()  );
  TFile *Fa_qcdpt300   = new TFile(  ( file_location + sa3  ).c_str()  );
  TFile *Fa_qcdpt470   = new TFile(  ( file_location + sa4  ).c_str()  );
  TFile *Fa_qcdpt600   = new TFile(  ( file_location + sa5  ).c_str()  );
  TFile *Fa_qcdpt800   = new TFile(  ( file_location + sa6  ).c_str()  );
  TFile *Fa_qcdpt1000  = new TFile(  ( file_location + sa7  ).c_str()  );
  TFile *Fa_qcdpt1400  = new TFile(  ( file_location + sa8  ).c_str()  );
  TFile *Fa_qcdpt1800  = new TFile(  ( file_location + sa9  ).c_str()  );
  TFile *Fa_qcdpt2400  = new TFile(  ( file_location + sa10 ).c_str()  );
  TFile *Fa_qcdpt3200  = new TFile(  ( file_location + sa11 ).c_str()  );
 
  TFile *Fb_qcdpt120   = new TFile(  ( file_location + sb1  ).c_str()  );
  TFile *Fb_qcdpt170   = new TFile(  ( file_location + sb2  ).c_str()  );
  TFile *Fb_qcdpt300   = new TFile(  ( file_location + sb3  ).c_str()  );
  TFile *Fb_qcdpt470   = new TFile(  ( file_location + sb4  ).c_str()  );
  TFile *Fb_qcdpt600   = new TFile(  ( file_location + sb5  ).c_str()  );
  TFile *Fb_qcdpt800   = new TFile(  ( file_location + sb6  ).c_str()  );
  TFile *Fb_qcdpt1000  = new TFile(  ( file_location + sb7  ).c_str()  );
  TFile *Fb_qcdpt1400  = new TFile(  ( file_location + sb8  ).c_str()  );
  TFile *Fb_qcdpt1800  = new TFile(  ( file_location + sb9  ).c_str()  );
  TFile *Fb_qcdpt2400  = new TFile(  ( file_location + sb10 ).c_str()  );
  TFile *Fb_qcdpt3200  = new TFile(  ( file_location + sb11 ).c_str()  );
 
 
  if (Fa_qcdpt120    ->IsZombie() ){ cout<<"Fa_qcdpt120   ->IsZombie()"<<endl; delete Fa_qcdpt120   ; Fa_qcdpt120    = 0;}
  if (Fa_qcdpt170    ->IsZombie() ){ cout<<"Fa_qcdpt170   ->IsZombie()"<<endl; delete Fa_qcdpt170   ; Fa_qcdpt170    = 0;}
  if (Fa_qcdpt300    ->IsZombie() ){ cout<<"Fa_qcdpt300   ->IsZombie()"<<endl; delete Fa_qcdpt300   ; Fa_qcdpt300    = 0;}
  if (Fa_qcdpt470    ->IsZombie() ){ cout<<"Fa_qcdpt470   ->IsZombie()"<<endl; delete Fa_qcdpt470   ; Fa_qcdpt470    = 0;}
  if (Fa_qcdpt600    ->IsZombie() ){ cout<<"Fa_qcdpt600   ->IsZombie()"<<endl; delete Fa_qcdpt600   ; Fa_qcdpt600    = 0;}
  if (Fa_qcdpt800    ->IsZombie() ){ cout<<"Fa_qcdpt800   ->IsZombie()"<<endl; delete Fa_qcdpt800   ; Fa_qcdpt800    = 0;}
  if (Fa_qcdpt1000   ->IsZombie() ){ cout<<"Fa_qcdpt1000  ->IsZombie()"<<endl; delete Fa_qcdpt1000  ; Fa_qcdpt1000   = 0;}
  if (Fa_qcdpt1400   ->IsZombie() ){ cout<<"Fa_qcdpt1400  ->IsZombie()"<<endl; delete Fa_qcdpt1400  ; Fa_qcdpt1400   = 0;}
  if (Fa_qcdpt1800   ->IsZombie() ){ cout<<"Fa_qcdpt1800  ->IsZombie()"<<endl; delete Fa_qcdpt1800  ; Fa_qcdpt1800   = 0;}
  if (Fa_qcdpt2400   ->IsZombie() ){ cout<<"Fa_qcdpt2400  ->IsZombie()"<<endl; delete Fa_qcdpt2400  ; Fa_qcdpt2400   = 0;}
  if (Fa_qcdpt3200   ->IsZombie() ){ cout<<"Fa_qcdpt3200  ->IsZombie()"<<endl; delete Fa_qcdpt3200  ; Fa_qcdpt3200   = 0;}

  if (Fa_qcdpt120   ==0) { cout<<"Did not open Fa_qcdpt120   "<<endl; return; } else {cout<<"Opened "<<file_location + sa1 <<endl; }
  if (Fa_qcdpt170   ==0) { cout<<"Did not open Fa_qcdpt170   "<<endl; return; } else {cout<<"Opened "<<file_location + sa2 <<endl; }
  if (Fa_qcdpt300   ==0) { cout<<"Did not open Fa_qcdpt300   "<<endl; return; } else {cout<<"Opened "<<file_location + sa3 <<endl; }
  if (Fa_qcdpt470   ==0) { cout<<"Did not open Fa_qcdpt470   "<<endl; return; } else {cout<<"Opened "<<file_location + sa4 <<endl; }
  if (Fa_qcdpt600   ==0) { cout<<"Did not open Fa_qcdpt600   "<<endl; return; } else {cout<<"Opened "<<file_location + sa5 <<endl; }
  if (Fa_qcdpt800   ==0) { cout<<"Did not open Fa_qcdpt800   "<<endl; return; } else {cout<<"Opened "<<file_location + sa6 <<endl; }
  if (Fa_qcdpt1000  ==0) { cout<<"Did not open Fa_qcdpt1000  "<<endl; return; } else {cout<<"Opened "<<file_location + sa7 <<endl; }
  if (Fa_qcdpt1400  ==0) { cout<<"Did not open Fa_qcdpt1400  "<<endl; return; } else {cout<<"Opened "<<file_location + sa8 <<endl; }
  if (Fa_qcdpt1800  ==0) { cout<<"Did not open Fa_qcdpt1800  "<<endl; return; } else {cout<<"Opened "<<file_location + sa9 <<endl; }
  if (Fa_qcdpt2400  ==0) { cout<<"Did not open Fa_qcdpt2400  "<<endl; return; } else {cout<<"Opened "<<file_location + sa10<<endl; }
  if (Fa_qcdpt3200  ==0) { cout<<"Did not open Fa_qcdpt3200  "<<endl; return; } else {cout<<"Opened "<<file_location + sa11<<endl; }

  if (Fb_qcdpt120    ->IsZombie() ){ cout<<"Fb_qcdpt120   ->IsZombie()"<<endl; delete Fb_qcdpt120   ; Fb_qcdpt120    = 0;}
  if (Fb_qcdpt170    ->IsZombie() ){ cout<<"Fb_qcdpt170   ->IsZombie()"<<endl; delete Fb_qcdpt170   ; Fb_qcdpt170    = 0;}
  if (Fb_qcdpt300    ->IsZombie() ){ cout<<"Fb_qcdpt300   ->IsZombie()"<<endl; delete Fb_qcdpt300   ; Fb_qcdpt300    = 0;}
  if (Fb_qcdpt470    ->IsZombie() ){ cout<<"Fb_qcdpt470   ->IsZombie()"<<endl; delete Fb_qcdpt470   ; Fb_qcdpt470    = 0;}
  if (Fb_qcdpt600    ->IsZombie() ){ cout<<"Fb_qcdpt600   ->IsZombie()"<<endl; delete Fb_qcdpt600   ; Fb_qcdpt600    = 0;}
  if (Fb_qcdpt800    ->IsZombie() ){ cout<<"Fb_qcdpt800   ->IsZombie()"<<endl; delete Fb_qcdpt800   ; Fb_qcdpt800    = 0;}
  if (Fb_qcdpt1000   ->IsZombie() ){ cout<<"Fb_qcdpt1000  ->IsZombie()"<<endl; delete Fb_qcdpt1000  ; Fb_qcdpt1000   = 0;}
  if (Fb_qcdpt1400   ->IsZombie() ){ cout<<"Fb_qcdpt1400  ->IsZombie()"<<endl; delete Fb_qcdpt1400  ; Fb_qcdpt1400   = 0;}
  if (Fb_qcdpt1800   ->IsZombie() ){ cout<<"Fb_qcdpt1800  ->IsZombie()"<<endl; delete Fb_qcdpt1800  ; Fb_qcdpt1800   = 0;}
  if (Fb_qcdpt2400   ->IsZombie() ){ cout<<"Fb_qcdpt2400  ->IsZombie()"<<endl; delete Fb_qcdpt2400  ; Fb_qcdpt2400   = 0;}
  if (Fb_qcdpt3200   ->IsZombie() ){ cout<<"Fb_qcdpt3200  ->IsZombie()"<<endl; delete Fb_qcdpt3200  ; Fb_qcdpt3200   = 0;}

  if (Fb_qcdpt120   ==0) { cout<<"Did not open Fb_qcdpt120   "<<endl; return; } else {cout<<"Opened "<<file_location + sb1 <<endl; }
  if (Fb_qcdpt170   ==0) { cout<<"Did not open Fb_qcdpt170   "<<endl; return; } else {cout<<"Opened "<<file_location + sb2 <<endl; }
  if (Fb_qcdpt300   ==0) { cout<<"Did not open Fb_qcdpt300   "<<endl; return; } else {cout<<"Opened "<<file_location + sb3 <<endl; }
  if (Fb_qcdpt470   ==0) { cout<<"Did not open Fb_qcdpt470   "<<endl; return; } else {cout<<"Opened "<<file_location + sb4 <<endl; }
  if (Fb_qcdpt600   ==0) { cout<<"Did not open Fb_qcdpt600   "<<endl; return; } else {cout<<"Opened "<<file_location + sb5 <<endl; }
  if (Fb_qcdpt800   ==0) { cout<<"Did not open Fb_qcdpt800   "<<endl; return; } else {cout<<"Opened "<<file_location + sb6 <<endl; }
  if (Fb_qcdpt1000  ==0) { cout<<"Did not open Fb_qcdpt1000  "<<endl; return; } else {cout<<"Opened "<<file_location + sb7 <<endl; }
  if (Fb_qcdpt1400  ==0) { cout<<"Did not open Fb_qcdpt1400  "<<endl; return; } else {cout<<"Opened "<<file_location + sb8 <<endl; }
  if (Fb_qcdpt1800  ==0) { cout<<"Did not open Fb_qcdpt1800  "<<endl; return; } else {cout<<"Opened "<<file_location + sb9 <<endl; }
  if (Fb_qcdpt2400  ==0) { cout<<"Did not open Fb_qcdpt2400  "<<endl; return; } else {cout<<"Opened "<<file_location + sb10<<endl; }
  if (Fb_qcdpt3200  ==0) { cout<<"Did not open Fb_qcdpt3200  "<<endl; return; } else {cout<<"Opened "<<file_location + sb11<<endl; }



  std::vector <TFile* > rootFilesA;
  rootFilesA.push_back( Fa_qcdpt120  );
  rootFilesA.push_back( Fa_qcdpt170  );
  rootFilesA.push_back( Fa_qcdpt300  );
  rootFilesA.push_back( Fa_qcdpt470  );
  rootFilesA.push_back( Fa_qcdpt600  );
  rootFilesA.push_back( Fa_qcdpt800  );
  rootFilesA.push_back( Fa_qcdpt1000 );
  rootFilesA.push_back( Fa_qcdpt1400 );
  rootFilesA.push_back( Fa_qcdpt1800 );
  rootFilesA.push_back( Fa_qcdpt2400 );
  rootFilesA.push_back( Fa_qcdpt3200 );
 
  std::vector <TFile* > rootFilesB;
  rootFilesB.push_back( Fb_qcdpt120  );
  rootFilesB.push_back( Fb_qcdpt170  );
  rootFilesB.push_back( Fb_qcdpt300  );
  rootFilesB.push_back( Fb_qcdpt470  );
  rootFilesB.push_back( Fb_qcdpt600  );
  rootFilesB.push_back( Fb_qcdpt800  );
  rootFilesB.push_back( Fb_qcdpt1000 );
  rootFilesB.push_back( Fb_qcdpt1400 );
  rootFilesB.push_back( Fb_qcdpt1800 );
  rootFilesB.push_back( Fb_qcdpt2400 );
  rootFilesB.push_back( Fb_qcdpt3200 ); 

  std::vector <bool > use_extensions;
  use_extensions.push_back( false );
  use_extensions.push_back( false );
  use_extensions.push_back( true  );
  use_extensions.push_back( true  );
  use_extensions.push_back( true  );
  use_extensions.push_back( true  );
  use_extensions.push_back( true  );
  use_extensions.push_back( true  );
  use_extensions.push_back( true  );
  use_extensions.push_back( true  );
  use_extensions.push_back( false ); 

  cout<<"histnames.size() "<<histnames.size()<<endl;

  out->cd();

  for (unsigned int i=0; i<histnames.size(); i++){
    cout<<"Getting "<<histnames[i]<<endl;
    TH1D  * hist = scaleHists_QCD_PTbinned_ReturnHist( histnames[i].c_str(), rootFilesA, rootFilesB, lumi, use_extensions ) ;
    cout<<"Got"<<endl;
    hist->SetName(histnames[i].c_str()); 
    hist->Write();
  }
  out->Write();
  out->Close();
  Fa_qcdpt120  ->Close();
  Fa_qcdpt170  ->Close();
  Fa_qcdpt300  ->Close();
  Fa_qcdpt470  ->Close();
  Fa_qcdpt600  ->Close();
  Fa_qcdpt800  ->Close();
  Fa_qcdpt1000 ->Close();
  Fa_qcdpt1400 ->Close();
  Fa_qcdpt1800 ->Close();
  Fa_qcdpt2400 ->Close();
  Fa_qcdpt3200 ->Close();

  // Fb_qcdpt120  ->Close();
  // Fb_qcdpt170  ->Close();
  Fb_qcdpt300  ->Close();
  Fb_qcdpt470  ->Close();
  Fb_qcdpt600  ->Close();
  Fb_qcdpt800  ->Close();
  Fb_qcdpt1000 ->Close();
  Fb_qcdpt1400 ->Close();
  Fb_qcdpt1800 ->Close();
  Fb_qcdpt2400 ->Close();
  // Fb_qcdpt3200 ->Close();

}



TH1D * scaleHists_QCD_PTbinned_ReturnHist(  string histname, vector <TFile* > &rootFilesA, vector <TFile* > &rootFilesB, double lumi, vector<bool> use_extensions )
{
  
  // Cross sections for PT binned QCD samples        
  double xsec_120to170    = 471100.          ;
  double xsec_170to300    = 117276.          ;
  double xsec_300to470    =   7823.          ;
  double xsec_470to600    =    648.2         ;
  double xsec_600to800    =    186.9         ;
  double xsec_800to1000   =     32.293       ;
  double xsec_1000to1400  =      9.4183      ;
  double xsec_1400to1800  =      0.84265     ;
  double xsec_1800to2400  =      0.114943    ;
  double xsec_2400to3200  =      0.00682981  ;
  double xsec_3200toInf   =      0.000165445 ;

  // Number of events in main samples
  double na1  =  6708572  ; // 120to170  
  double na2  =  5881386  ; // 170to300  
  double na3  =  2482816  ; // 300to470  
  double na4  =  3959986  ; // 470to600  
  double na5  =  3896412  ; // 600to800  
  double na6  =  3992112  ; // 800to1000 
  double na7  =  2999069  ; // 1000to1400
  double na8  =   396409  ; // 1400to1800
  double na9  =   397660  ; // 1800to2400
  double na10 =   399226  ; // 2400to3200
  double na11 =   391735  ; // 3200toInf 

  // Number of events in extension samples
  double nb1  =        0  ; // 120to170  
  double nb2  =        0  ; // 170to300  
  double nb3  = 15282856  ; // 300to470  
  double nb4  = 15458074  ; // 470to600  
  double nb5  =  9622896  ; // 600to800  
  double nb6  = 15194720  ; // 800to1000 
  double nb7  =  6229840  ; // 1000to1400
  double nb8  =  2304684  ; // 1400to1800
  double nb9  =  1552064  ; // 1800to2400
  double nb10 =   596904  ; // 2400to3200
  double nb11 =        0  ; // 3200toInf 
  
  // Number of total
  double n1   =  na1 ;  
  double n2   =  na2 ;   
  double n3   =  na3 ;      
  double n4   =  na4 ;      
  double n5   =  na5 ;  
  double n6   =  na6 ;  
  double n7   =  na7 ;  
  double n8   =  na8 ;  
  double n9   =  na9 ;  
  double n10  =  na10;  
  double n11  =  na11;  
 
  if (use_extensions[0]  )  n1   += nb1 ;  
  if (use_extensions[1]  )  n2   += nb2 ;   
  if (use_extensions[2]  )  n3   += nb3 ;      
  if (use_extensions[3]  )  n4   += nb4 ;      
  if (use_extensions[4]  )  n5   += nb5 ;  
  if (use_extensions[5]  )  n6   += nb6 ;  
  if (use_extensions[6]  )  n7   += nb7 ;  
  if (use_extensions[7]  )  n8   += nb8 ;  
  if (use_extensions[8]  )  n9   += nb9 ;  
  if (use_extensions[9]  )  n10  += nb10;  
  if (use_extensions[10] )  n11  += nb11;  
  
    
  // Scale N = L sigma
  double s1   =  0  ;  
  double s2   =  0  ;   
  double s3   =  0  ;      
  double s4   =  0  ;      
  double s5   =  0  ;  
  double s6   =  0  ;  
  double s7   =  0  ;  
  double s8   =  0  ;  
  double s9   =  0  ;  
  double s10  =  0  ;  
  double s11  =  0  ;  
    
  // xs / nevents * lumi
  if(n1>0.1) s1   =  ( xsec_120to170    * lumi  ) / n1   ;  
  if(n2>0.1) s2   =  ( xsec_170to300    * lumi  ) / n2   ;   
  if(n3>0.1) s3   =  ( xsec_300to470    * lumi  ) / n3   ;      
  if(n4>0.1) s4   =  ( xsec_470to600    * lumi  ) / n4   ;      
  if(n5>0.1) s5   =  ( xsec_600to800    * lumi  ) / n5   ;  
  if(n6>0.1) s6   =  ( xsec_800to1000   * lumi  ) / n6   ;  
  if(n7>0.1) s7   =  ( xsec_1000to1400  * lumi  ) / n7   ;  
  if(n8>0.1) s8   =  ( xsec_1400to1800  * lumi  ) / n8   ;  
  if(n8>0.1) s9   =  ( xsec_1800to2400  * lumi  ) / n9   ;  
  if(n8>0.1) s10  =  ( xsec_2400to3200  * lumi  ) / n10  ;  
  if(n8>0.1) s11  =  ( xsec_3200toInf   * lumi  ) / n11  ;  
    


  vector <double> mcscales;

  mcscales.push_back(  s1   );        
  mcscales.push_back(  s2   );              
  mcscales.push_back(  s3   );                
  mcscales.push_back(  s4   );                             
  mcscales.push_back(  s5   );                          
  mcscales.push_back(  s6   );                         
  mcscales.push_back(  s7   );                         
  mcscales.push_back(  s8   );    
  mcscales.push_back(  s9   );    
  mcscales.push_back(  s10  );    
  mcscales.push_back(  s11  );    

  vector <string> binnames;      
  binnames.push_back(  "120to170"   );      
  binnames.push_back(  "170to300"   );       
  binnames.push_back(  "300to470"   );        
  binnames.push_back(  "470to600"   );        
  binnames.push_back(  "600to800"    );
  binnames.push_back(  "800to1000"   ); 
  binnames.push_back(  "1000to1400"  );  
  binnames.push_back(  "1400to1800"  );  
  binnames.push_back(  "1800to2400"  );  
  binnames.push_back(  "2400to3200"  );  
  binnames.push_back(  "3200toInf"   ); 

  // QCD_Pt_5to10_TuneCUETP8M1_13TeV_pythia8           61018300000
  // QCD_Pt_10to15_TuneCUETP8M1_13TeV_pythia8           5887580000
  // QCD_Pt_15to30_TuneCUETP8M1_13TeV_pythia8           1837410000
  // QCD_Pt_30to50_TuneCUETP8M1_13TeV_pythia8            140932000
  // QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8             19204300
  // QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8             2762530
  // QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8             471100
  // QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8             117276
  // QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8               7823
  // QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8                648.2
  // QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8                186.9
  // QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8                32.293
  // QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8                9.4183
  // QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8                0.84265
  // QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8                0.12163
  // QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8                0.00682981
  // QCD_Pt_3200toInf_TuneCUETP8M1_13TeV_pythia8                 0.000165445

  TCanvas *c1 = new TCanvas("c1","",900,700);

  TH1D * htemp = (TH1D*)  rootFilesA[rootFilesA.size()-1] -> Get( histname.c_str() );
  TH1D * h_sum = (TH1D*)htemp->Clone(); 
  h_sum->Reset();
  h_sum->Sumw2();

  THStack *h_stack = new THStack("h_stack","");
  TH1D * htemp2 = (TH1D*)  rootFilesA[rootFilesA.size()-4] -> Get( histname.c_str() );
  TH1D * h1st = (TH1D*)htemp2->Clone(); 
  h1st->Reset();
  h_stack->Add(h1st);


  TLegend * leg;
  leg  = new TLegend(0.7,0.54,0.95,0.89);
  leg ->SetBorderSize(0);
  leg ->SetFillColor(0);
  leg ->SetFillStyle(0);
  leg ->SetMargin(0.15);

  TH1D * h1 ;
  TH1D * h2 ;
  double si = 0.0;
  cout<<"rootFilesA.size() "<<rootFilesA.size()<<endl;
  cout<<"rootFilesB.size() "<<rootFilesB.size()<<endl;
  cout<<"use_extensions.size() "<<use_extensions.size()<<endl;

  for (unsigned int i=0; i<rootFilesA.size(); i++){
    unsigned int j = rootFilesA.size()-1-i;

    cout<<setw(10)<<binnames[j];

    h1 = (TH1D*)  rootFilesA[j] -> Get( histname.c_str() );
    h1->Sumw2();
    cout<<" h1 "<<setw(12)<<h1->Integral();

    if (use_extensions[j]){
      h2 = (TH1D*)  rootFilesB[j] -> Get( histname.c_str() );
      h2->Sumw2();
      cout<<" h2 "<<setw(13)<<h2->Integral();
      h1->Add(h2);
    }
    else cout<<" h2 "<<setw(13)<<si;
    cout<<" add "<<setw(13)<<h1->Integral()<<" SF "<<setw(12)<<mcscales[j];
    
    h1->Scale(mcscales[j]);
    h_sum->Add(h1);

    // Draw THStack to make sure everything worked as expected
    h1->SetFillColor(99-4*i);
    h1->SetLineColor(99-4*i);
    leg ->AddEntry(h1, binnames[j].c_str(), "F");
    
    TH1D * h1A = (TH1D*)h1->Clone();  // Not sure why i have to do this but it avoids a weird THStack bug
    h_stack->Add(h1A); 
    cout<<" ScaledH "<<setw(12)<<h1->Integral()<<"  SUM "<<setw(12)<<h_sum->Integral()<<" MAX "<<setw(12)<<h_sum->GetMaximum() <<"  Stack "<<h_stack->GetMaximum()<<endl;//<<"  "<<h1A->Integral() <<endl;

    h1->Reset();
    if (use_extensions[j]) h2->Reset();
  }
  cout<<"h_stack->GetMaximum(nostack) " <<h_stack->GetMaximum("nostack")<<endl;
  cout<<"h_stack->GetMaximum()        " <<h_stack->GetMaximum()<<endl;
  cout<<"h_stack->GetMinimum()        " <<h_stack->GetMinimum()<<endl;

  cout<<"debug1"<<endl;  h_sum      ->SetMinimum(0.00001);
  cout<<"debug2"<<endl;  h_stack    ->SetMinimum(0.00001);
  cout<<"debug3"<<endl;  h_sum ->Draw("P");
  cout<<"debug4"<<endl;  h_stack    ->Draw("HISTsame");
  cout<<"debug5"<<endl;  h_sum ->Draw("Psame");
  cout<<"debug6"<<endl;  leg   ->Draw("same");
  cout<<"debug7"<<endl;
  cout<<"debug8"<<endl;  string savename  = "testScalePt/testStack_"+histname+".pdf";
  cout<<"debug9"<<endl;  string savename2 = "testScalePt/testStack_"+histname+"_log.pdf";
  cout<<"debug10"<<endl;  c1->SaveAs(savename.c_str() );
  cout<<"debug11"<<endl;  c1->SetLogy();
  cout<<"debug12"<<endl;  c1->SaveAs(savename2.c_str() );
  cout<<"debug13"<<endl;  c1->SetLogy(0);
  cout<<"debug14"<<endl;  delete c1;
  cout<<"debug15"<<endl; 
  return h_sum;
}




TH1D * scaleHists_QCD_HTbinned_ReturnHist(  string histname, vector <TFile* > &rootFilesA, vector <TFile* > &rootFilesB, double lumi, vector<bool> use_nominal, vector<bool> use_extensions )
{
  cout<<"Scaling "<<histname<<endl;
  vector <double> mcscales; 
       
  // Cross sections for HT binned QCD samples        
  double xsec_100to200    =   27990000.0   ;      
  double xsec_200to300    =    1712000.0   ;       
  double xsec_300to500    =     347700.0   ;          
  double xsec_500to700    =      32100.0   ;          
  double xsec_700to1000   =       6831.0   ;
  double xsec_1000to1500  =       1207.0   ;
  double xsec_1500to2000  =        119.9   ;
  double xsec_2000toInf   =         25.24  ;
 
  // Number of events in main samples
  double na1  =    0         ;  // HT 100to200        
  double na2  =    0         ;  // HT 200to300         
  double na3  =    16914727  ;  // HT 300to500            
  double na4  =    18929951  ;  // HT 500to700            
  double na5  =    15629253  ;  // HT 700to1000 
  double na6  =    4767100   ;  // HT 1000to1500
  double na7  =    3970819   ;  // HT 1500to2000
  double na8  =    1991645   ;  // HT 2000toInf 
 
  // Number of events in extension samples
  double nb1  =   0         ;  // HT 100to200        
  double nb2  =   38857977  ;  // HT 200to300         
  double nb3  =   37502012  ;  // HT 300to500            
  double nb4  =   43341392  ;  // HT 500to700            
  double nb5  =   29697035  ;  // HT 700to1000 
  double nb6  =   10360193  ;  // HT 1000to1500
  double nb7  =   7855883   ;  // HT 1500to2000
  double nb8  =   4047360   ;  // HT 2000toInf 

  // Number of total
  double n1  = 0;  
  double n2  = 0;  
  double n3  = 0;     
  double n4  = 0;     
  double n5  = 0;  
  double n6  = 0;  
  double n7  = 0;  
  double n8  = 0;  

  if (use_nominal[0]  )   n1  += na1;  
  if (use_nominal[1]  )   n2  += na2;   
  if (use_nominal[2]  )   n3  += na3;      
  if (use_nominal[3]  )   n4  += na4;      
  if (use_nominal[4]  )   n5  += na5;  
  if (use_nominal[5]  )   n6  += na6;  
  if (use_nominal[6]  )   n7  += na7;  
  if (use_nominal[7]  )   n8  += na8;  
  
  if (use_extensions[0]  )   n1  += nb1;  
  if (use_extensions[1]  )   n2  += nb2;   
  if (use_extensions[2]  )   n3  += nb3;      
  if (use_extensions[3]  )   n4  += nb4;      
  if (use_extensions[4]  )   n5  += nb5;  
  if (use_extensions[5]  )   n6  += nb6;  
  if (use_extensions[6]  )   n7  += nb7;  
  if (use_extensions[7]  )   n8  += nb8;  
  

  // Scale N = L sigma
  double s1  =  0  ;  
  double s2  =  0  ;   
  double s3  =  0  ;      
  double s4  =  0  ;      
  double s5  =  0  ;  
  double s6  =  0  ;  
  double s7  =  0  ;  
  double s8  =  0  ;  

  if(n1>0.1) s1  =  ( xsec_100to200    * lumi  ) / n1  ;  
  if(n2>0.1) s2  =  ( xsec_200to300    * lumi  ) / n2  ;   
  if(n3>0.1) s3  =  ( xsec_300to500    * lumi  ) / n3  ;      
  if(n4>0.1) s4  =  ( xsec_500to700    * lumi  ) / n4  ;      
  if(n5>0.1) s5  =  ( xsec_700to1000   * lumi  ) / n5  ;  
  if(n6>0.1) s6  =  ( xsec_1000to1500  * lumi  ) / n6  ;  
  if(n7>0.1) s7  =  ( xsec_1500to2000  * lumi  ) / n7  ;  
  if(n8>0.1) s8  =  ( xsec_2000toInf   * lumi  ) / n8  ;  

  mcscales.push_back(  s1  );        
  mcscales.push_back(  s2  );              
  mcscales.push_back(  s3  );                
  mcscales.push_back(  s4  );                             
  mcscales.push_back(  s5  );                          
  mcscales.push_back(  s6  );                         
  mcscales.push_back(  s7  );                         
  mcscales.push_back(  s8  );                   

  vector <string> binnames;
  binnames.push_back(  "100to200"    );     // 100to200        
  binnames.push_back(  "200to300"    );     // 200to300        
  binnames.push_back(  "300to500"    );     // 300to500       
  binnames.push_back(  "500to700"    );     // 500to700        
  binnames.push_back(  "700to1000"   );     // 700to1000        
  binnames.push_back(  "1000to1500"  );     // 1000to1500       
  binnames.push_back(  "1500to2000"  );     // 1500to2000       
  binnames.push_back(  "2000toInf"   );     // 2000toInf       

  TCanvas *c1 = new TCanvas("c1","",900,700);

  TH1D * htemp = (TH1D*)  rootFilesA[rootFilesA.size()-1] -> Get( histname.c_str() );  
  TH1D * h_sum = (TH1D*)htemp->Clone();
  h_sum->Reset();  
  h_sum->Sumw2();

  THStack *h_stack = new THStack("h_stack","");
  TH1D * htemp2 = (TH1D*)  rootFilesA[rootFilesA.size()-4] -> Get( histname.c_str() );
  TH1D * h1st = (TH1D*)htemp2->Clone(); 
  h1st->Reset();
  h_stack->Add(h1st);

  TLegend * leg;
  leg  = new TLegend(0.7,0.54,0.95,0.89);
  leg ->SetBorderSize(0);
  leg ->SetFillColor(0);
  leg ->SetFillStyle(0);
  leg ->SetMargin(0.15);

  TH1D * h1 ;
  TH1D * h2 ;
  double si = 0.0;
  cout<<"rootFilesA.size() "<<rootFilesA.size()<<endl;
  cout<<"rootFilesB.size() "<<rootFilesB.size()<<endl;
  cout<<"use_nominal.size() "<<use_nominal.size()<<endl;
  cout<<"use_extensions.size() "<<use_extensions.size()<<endl;

  for (unsigned int i=0; i<rootFilesA.size(); i++)
  {
    unsigned int j = rootFilesA.size()-1-i;

    cout<<setw(10)<<binnames[j]<<" "<<use_nominal[j]<<" "<<use_extensions[j];

    h1 = (TH1D*)  rootFilesA[j] -> Get( histname.c_str() );
    h1->Sumw2();
    if (!use_nominal[j] ) h1->Reset();
    cout<<" h1 "<<setw(12)<<h1->Integral();

    if (use_extensions[j]){
      h2 = (TH1D*)  rootFilesB[j] -> Get( histname.c_str() );
      h2->Sumw2();
      cout<<" h2 "<<setw(13)<<h2->Integral();
      h1->Add(h2);
    }
    else cout<<" h2 "<<setw(13)<<si;
    cout<<" add "<<setw(13)<<h1->Integral()<<" SF "<<setw(12)<<mcscales[j];
    
    h1->Scale(mcscales[j]);
    h_sum->Add(h1);

    // Draw THStack to make sure everything worked as expected
    h1->SetFillColor(99-4*i);
    h1->SetLineColor(99-4*i);
    leg ->AddEntry(h1, binnames[j].c_str(), "F");
    
    TH1D * h1A = (TH1D*)h1->Clone();  // Not sure why i have to do this but it avoids a weird THStack bug
    h_stack->Add(h1A); 
    cout<<" ScaledH "<<setw(12)<<h1->Integral()<<"  SUM "<<setw(12)<<h_sum->Integral()<<" MAX "<<setw(12)<<h_sum->GetMaximum() <<"  Stack "<<h_stack->GetMaximum()<<endl;//<<"  "<<h1A->Integral() <<endl;

    if (use_nominal[j])   h1->Reset();
    if (use_extensions[j]) h2->Reset();
  }      

  cout<<"h_stack->GetMaximum(nostack) " <<h_stack->GetMaximum("nostack")<<endl;
  cout<<"h_stack->GetMaximum()        " <<h_stack->GetMaximum()<<endl;
  cout<<"h_stack->GetMinimum()        " <<h_stack->GetMinimum()<<endl;

  h_sum      ->SetMinimum(0.00001);
  h_stack    ->SetMinimum(0.00001);
  h_sum ->Draw("P");
  h_stack    ->Draw("HISTsame");
  h_sum ->Draw("Psame");
  leg   ->Draw("same");

  string savename  = "testScaleHT/testStack_"+histname+".pdf";
  string savename2 = "testScaleHT/testStack_"+histname+"_log.pdf";
  c1->SaveAs(savename.c_str() );
  c1->SetLogy();
  c1->SaveAs(savename2.c_str() );
  c1->SetLogy(0);

  return h_sum;
}


void run(int j, string datelabel){   // j== 0 kinematic, 1 mistag, 2 bkgd est, 3 modmass

  if (j==0)     { cout<<"Scaling kinematic QCD plots"<<endl;                  }     
  else if (j==1){ cout<<"Scaling mistag QCD plots"<<endl;                     }  
  else if (j==2){ cout<<"Scaling bkgd QCD plots"<<endl;                       }
  else if (j==3){ cout<<"Scaling modmass QCD plots"<<endl;                    }
  else if (j==4){ cout<<"Scaling 2D kinematic"<<endl;                    }
  else { cout<<"Please enter 0 kinematic, 1 mistag, 2 bkgd est, 3 modmass, 4 2D kinematic"<<endl; return;}

  cout<<"run("<<j<<","<<datelabel<<")"<<endl;

  vector <string> histnames;
  
  // 2D Kinematic plots
  if (j==4){
       
    histnames.push_back("h_BeforeBtag_lightHad_Jet0_SubjetMaxB_Eta_Pt"     );   
    histnames.push_back("h_BeforeBtag_cHad_Jet0_SubjetMaxB_Eta_Pt"         );   
    histnames.push_back("h_BeforeBtag_bHad_Jet0_SubjetMaxB_Eta_Pt"         );   
    histnames.push_back("h_AfterBtag_lightHad_Jet0_SubjetMaxB_Eta_Pt"      );   
    histnames.push_back("h_AfterBtag_cHad_Jet0_SubjetMaxB_Eta_Pt"          );   
    histnames.push_back("h_AfterBtag_bHad_Jet0_SubjetMaxB_Eta_Pt"          );   
    histnames.push_back("h_BeforeBtag_lightHad_Jet1_SubjetMaxB_Eta_Pt"     );   
    histnames.push_back("h_BeforeBtag_cHad_Jet1_SubjetMaxB_Eta_Pt"         );   
    histnames.push_back("h_BeforeBtag_bHad_Jet1_SubjetMaxB_Eta_Pt"         );   
    histnames.push_back("h_AfterBtag_lightHad_Jet1_SubjetMaxB_Eta_Pt"      );   
    histnames.push_back("h_AfterBtag_cHad_Jet1_SubjetMaxB_Eta_Pt"          );   
    histnames.push_back("h_AfterBtag_bHad_Jet1_SubjetMaxB_Eta_Pt"          );   
              

    histnames.push_back("h2_pup_Jet0Pt_Jet0SDmass"                                                    );                                                 
    histnames.push_back("h2_pup_Jet0Pt_Jet0SDmass_JetTag_b"                                           );                                             
    histnames.push_back("h2_pup_Jet0Pt_Jet0SDmass_JetTag_tau32"                                       );                                             
    histnames.push_back("h2_pup_Jet0Pt_Jet0SDmass_JetTag_b_tau32"                                     );                                             
    histnames.push_back("h2_pup_Jet0Pt_Jet0SDmass_OppositeJetTag_t_b"                                 );                                             
    histnames.push_back("h2_pup_Jet0Pt_Jet0SDmass_OppositeJetTag_t_b_JetTag_b"                        );                                             
    histnames.push_back("h2_pup_Jet0Pt_Jet0SDmass_OppositeJetTag_t_b_JetTag_b_tau32"                  );                                             
    histnames.push_back("h2_pup_Jet0P_Jet0SDmass"                                                     );                                             
    histnames.push_back("h2_pup_Jet0P_Jet0SDmass_JetTag_b"                                            );                                             
    histnames.push_back("h2_pup_Jet0P_Jet0SDmass_JetTag_tau32"                                        );                                             
    histnames.push_back("h2_pup_Jet0P_Jet0SDmass_JetTag_b_tau32"                                      );                                             
    histnames.push_back("h2_pup_Jet0P_Jet0SDmass_OppositeJetTag_t_b"                                  );                                             
    histnames.push_back("h2_pup_Jet0P_Jet0SDmass_OppositeJetTag_t_b_JetTag_b"                         );                                             
    histnames.push_back("h2_pup_Jet0P_Jet0SDmass_OppositeJetTag_t_b_JetTag_b_tau32"                   );                                             
    histnames.push_back("h2_pup_match_Jet0Pt_Jet0SDmass"                                              );                                             
    histnames.push_back("h2_pup_match_Jet0Pt_Jet0SDmass_JetTag_b"                                     );                                             
    histnames.push_back("h2_pup_match_Jet0Pt_Jet0SDmass_JetTag_tau32"                                 );                                             
    histnames.push_back("h2_pup_match_Jet0Pt_Jet0SDmass_JetTag_b_tau32"                               );                                             
    histnames.push_back("h2_pup_match_Jet0Pt_Jet0SDmass_OppositeJetTag_t_b"                           );                                             
    histnames.push_back("h2_pup_match_Jet0Pt_Jet0SDmass_OppositeJetTag_t_b_JetTag_b"                  );                                             
    histnames.push_back("h2_pup_match_Jet0Pt_Jet0SDmass_OppositeJetTag_t_b_JetTag_b_tau32"            );                                             
    histnames.push_back("h2_pup_match_Jet0P_Jet0SDmass"                                               );                                             
    histnames.push_back("h2_pup_match_Jet0P_Jet0SDmass_JetTag_b"                                      );                                             
    histnames.push_back("h2_pup_match_Jet0P_Jet0SDmass_JetTag_tau32"                                  );                                             
    histnames.push_back("h2_pup_match_Jet0P_Jet0SDmass_JetTag_b_tau32"                                );                                             
    histnames.push_back("h2_pup_match_Jet0P_Jet0SDmass_OppositeJetTag_t_b"                            );                                             
    histnames.push_back("h2_pup_match_Jet0P_Jet0SDmass_OppositeJetTag_t_b_JetTag_b"                   );                                             
    histnames.push_back("h2_pup_match_Jet0P_Jet0SDmass_OppositeJetTag_t_b_JetTag_b_tau32"             );                                             
    histnames.push_back("h2_pup_match_col_Jet0Pt_Jet0SDmass"                                          );                                             
    histnames.push_back("h2_pup_match_col_Jet0Pt_Jet0SDmass_JetTag_b"                                 );                                             
    histnames.push_back("h2_pup_match_col_Jet0Pt_Jet0SDmass_JetTag_tau32"                             );                                             
    histnames.push_back("h2_pup_match_col_Jet0Pt_Jet0SDmass_JetTag_b_tau32"                           );                                             
    histnames.push_back("h2_pup_match_col_Jet0Pt_Jet0SDmass_OppositeJetTag_t_b"                       );                                             
    histnames.push_back("h2_pup_match_col_Jet0Pt_Jet0SDmass_OppositeJetTag_t_b_JetTag_b"              );                                             
    histnames.push_back("h2_pup_match_col_Jet0Pt_Jet0SDmass_OppositeJetTag_t_b_JetTag_b_tau32"        );                                             
    histnames.push_back("h2_pup_match_col_Jet0P_Jet0SDmass"                                           );                                             
    histnames.push_back("h2_pup_match_col_Jet0P_Jet0SDmass_JetTag_b"                                  );                                             
    histnames.push_back("h2_pup_match_col_Jet0P_Jet0SDmass_JetTag_tau32"                              );                                             
    histnames.push_back("h2_pup_match_col_Jet0P_Jet0SDmass_JetTag_b_tau32"                            );                                             
    histnames.push_back("h2_pup_match_col_Jet0P_Jet0SDmass_OppositeJetTag_t_b"                        );                                             
    histnames.push_back("h2_pup_match_col_Jet0P_Jet0SDmass_OppositeJetTag_t_b_JetTag_b"               );                                             
    histnames.push_back("h2_pup_match_col_Jet0P_Jet0SDmass_OppositeJetTag_t_b_JetTag_b_tau32"         );                                             
    histnames.push_back("h2_pup_Jet1Pt_Jet1SDmass"                                                    );                                             
    histnames.push_back("h2_pup_Jet1Pt_Jet1SDmass_JetTag_b"                                           );                                             
    histnames.push_back("h2_pup_Jet1Pt_Jet1SDmass_JetTag_tau32"                                       );                                             
    histnames.push_back("h2_pup_Jet1Pt_Jet1SDmass_JetTag_b_tau32"                                     );                                             
    histnames.push_back("h2_pup_Jet1Pt_Jet1SDmass_OppositeJetTag_t_b"                                 );                                             
    histnames.push_back("h2_pup_Jet1Pt_Jet1SDmass_OppositeJetTag_t_b_JetTag_b"                        );                                             
    histnames.push_back("h2_pup_Jet1Pt_Jet1SDmass_OppositeJetTag_t_b_JetTag_b_tau32"                  );                                             
    histnames.push_back("h2_pup_Jet1P_Jet1SDmass"                                                     );                                             
    histnames.push_back("h2_pup_Jet1P_Jet1SDmass_JetTag_b"                                            );                                             
    histnames.push_back("h2_pup_Jet1P_Jet1SDmass_JetTag_tau32"                                        );                                             
    histnames.push_back("h2_pup_Jet1P_Jet1SDmass_JetTag_b_tau32"                                      );                                             
    histnames.push_back("h2_pup_Jet1P_Jet1SDmass_OppositeJetTag_t_b"                                  );                                             
    histnames.push_back("h2_pup_Jet1P_Jet1SDmass_OppositeJetTag_t_b_JetTag_b"                         );                                             
    histnames.push_back("h2_pup_Jet1P_Jet1SDmass_OppositeJetTag_t_b_JetTag_b_tau32"                   );                                             
    histnames.push_back("h2_pup_match_Jet1Pt_Jet1SDmass"                                              );                                             
    histnames.push_back("h2_pup_match_Jet1Pt_Jet1SDmass_JetTag_b"                                     );                                             
    histnames.push_back("h2_pup_match_Jet1Pt_Jet1SDmass_JetTag_tau32"                                 );                                             
    histnames.push_back("h2_pup_match_Jet1Pt_Jet1SDmass_JetTag_b_tau32"                               );                                             
    histnames.push_back("h2_pup_match_Jet1Pt_Jet1SDmass_OppositeJetTag_t_b"                           );                                             
    histnames.push_back("h2_pup_match_Jet1Pt_Jet1SDmass_OppositeJetTag_t_b_JetTag_b"                  );                                             
    histnames.push_back("h2_pup_match_Jet1Pt_Jet1SDmass_OppositeJetTag_t_b_JetTag_b_tau32"            );                                             
    histnames.push_back("h2_pup_match_Jet1P_Jet1SDmass"                                               );                                             
    histnames.push_back("h2_pup_match_Jet1P_Jet1SDmass_JetTag_b"                                      );                                             
    histnames.push_back("h2_pup_match_Jet1P_Jet1SDmass_JetTag_tau32"                                  );                                             
    histnames.push_back("h2_pup_match_Jet1P_Jet1SDmass_JetTag_b_tau32"                                );                                             
    histnames.push_back("h2_pup_match_Jet1P_Jet1SDmass_OppositeJetTag_t_b"                            );                                             
    histnames.push_back("h2_pup_match_Jet1P_Jet1SDmass_OppositeJetTag_t_b_JetTag_b"                   );                                             
    histnames.push_back("h2_pup_match_Jet1P_Jet1SDmass_OppositeJetTag_t_b_JetTag_b_tau32"             );                                             
    histnames.push_back("h2_pup_match_col_Jet1Pt_Jet1SDmass"                                          );                                             
    histnames.push_back("h2_pup_match_col_Jet1Pt_Jet1SDmass_JetTag_b"                                 );                                             
    histnames.push_back("h2_pup_match_col_Jet1Pt_Jet1SDmass_JetTag_tau32"                             );                                             
    histnames.push_back("h2_pup_match_col_Jet1Pt_Jet1SDmass_JetTag_b_tau32"                           );                                             
    histnames.push_back("h2_pup_match_col_Jet1Pt_Jet1SDmass_OppositeJetTag_t_b"                       );                                             
    histnames.push_back("h2_pup_match_col_Jet1Pt_Jet1SDmass_OppositeJetTag_t_b_JetTag_b"              );                                             
    histnames.push_back("h2_pup_match_col_Jet1Pt_Jet1SDmass_OppositeJetTag_t_b_JetTag_b_tau32"        );                                             
    histnames.push_back("h2_pup_match_col_Jet1P_Jet1SDmass"                                           );                                             
    histnames.push_back("h2_pup_match_col_Jet1P_Jet1SDmass_JetTag_b"                                  );                                             
    histnames.push_back("h2_pup_match_col_Jet1P_Jet1SDmass_JetTag_tau32"                              );                                             
    histnames.push_back("h2_pup_match_col_Jet1P_Jet1SDmass_JetTag_b_tau32"                            );                                             
    histnames.push_back("h2_pup_match_col_Jet1P_Jet1SDmass_OppositeJetTag_t_b"                        );                                             
    histnames.push_back("h2_pup_match_col_Jet1P_Jet1SDmass_OppositeJetTag_t_b_JetTag_b"               );                                             
    histnames.push_back("h2_pup_match_col_Jet1P_Jet1SDmass_OppositeJetTag_t_b_JetTag_b_tau32"         );                                             
                                                 
    histnames.push_back("h_GenJet0Pt_GenJet0Mass"                                                     );        
    histnames.push_back("h_Jet0Pt_GenJet0Mass"                                                        );        
    histnames.push_back("h_Jet0P_GenJet0Mass"                                                         );        
    histnames.push_back("h_Jet0Pt_Jet0Mass"                                                           );        
    histnames.push_back("h_Jet0Pt_Jet0SDmass"                                                         );        
    histnames.push_back("h_Jet0Pt_Jet0Tau32"                                                          );        
    histnames.push_back("h_Jet0Pt_Jet0PuppiMass"                                                      );        
    histnames.push_back("h_Jet0Pt_Jet0PuppiSDmass"                                                    );        
    histnames.push_back("h_Jet0Pt_Jet0PuppiTau32"                                                     );        
    histnames.push_back("h_Jet0P_Jet0Mass"                                                            );        
    histnames.push_back("h_Jet0P_Jet0SDmass"                                                          );        
    histnames.push_back("h_Jet0P_Jet0Tau32"                                                           );        
    histnames.push_back("h_Jet0P_Jet0PuppiMass"                                                       );        
    histnames.push_back("h_Jet0P_Jet0PuppiSDmass"                                                     );        
    histnames.push_back("h_Jet0P_Jet0PuppiTau32"                                                      );        
    histnames.push_back("h_Jet0Mass_Jet0Tau32"                                                        );        
    histnames.push_back("h_Jet0SDmass_Jet0Tau32"                                                      );        
    histnames.push_back("h_Jet0PuppiSDmass_Jet0PuppiTau32"                                            );        
    histnames.push_back("h_Jet0Y_Jet0Mass"                                                            );        
    histnames.push_back("h_Jet0Y_Jet0SDmass"                                                          );        
    histnames.push_back("h_Jet0Y_Jet0Tau32"                                                           );        
    histnames.push_back("h_Jet0Y_Jet0PuppiMass"                                                       );        
    histnames.push_back("h_Jet0Y_Jet0PuppiSDmass"                                                     );        
    histnames.push_back("h_Jet0Y_Jet0PuppiTau32"                                                      );        
    histnames.push_back("h_Pt500to520_Jet0Y_Jet0Mass"                                                 );        
    histnames.push_back("h_Pt500to520_Jet0Y_Jet0SDmass"                                               );        
    histnames.push_back("h_Pt500to520_Jet0Y_Jet0Tau32"                                                );        
    histnames.push_back("h_Pt500to520_Jet0Y_Jet0PuppiMass"                                            );        
    histnames.push_back("h_Pt500to520_Jet0Y_Jet0PuppiSDmass"                                          );        
    histnames.push_back("h_Pt500to520_Jet0Y_Jet0PuppiTau32"                                           );        
    histnames.push_back("h_Jet0Y_Jet1Y"                                                               );        
    histnames.push_back("h_Jet0SDmass_Jet1SDmass"                                                     );        
    histnames.push_back("h_Jet0PuppiSDmass_Jet1PuppiSDmass"                                           );        
    histnames.push_back("h_Jet0Tau32_Jet1Tau32"                                                       );        
    histnames.push_back("h_Jet0PuppiTau32_Jet1PuppiTau32"                                             );        
    histnames.push_back("h_Jet0PuppiTau1_Jet1PuppiTau1"                                               );        
    histnames.push_back("h_Jet0PuppiTau2_Jet1PuppiTau2"                                               );        
    histnames.push_back("h_Jet0PuppiTau3_Jet1PuppiTau3"                                               );        
    histnames.push_back("h_Asym_Jet0SDmass"                                                           );        
    histnames.push_back("h_DeltaRap_Jet0SDmass"                                                       );        
    histnames.push_back("h_jet0_tau32_rhoRatio"                                                       );          
    histnames.push_back("h_jet0_tau32_rhoRatioPrime"                                                  );          
    histnames.push_back("h_jet0_tau32_rhoRatioPmag"                                                   );          
    // histnames.push_back("h_jet0_tau32_rhoRatioPmagPrime"                                              );          
    // histnames.push_back("h_jet0_tau32_rhoRatioPuppi"                                                  );          
    // histnames.push_back("h_jet0_tau32_rhoRatioPuppiPrime"                                             );          
    // histnames.push_back("h_jet0_tau32_rhoRatioPuppiPmag"                                              );          
    // histnames.push_back("h_jet0_tau32_rhoRatioPuppiPmagPrime"                                         );          
    // histnames.push_back("h_jet1_tau32_rhoRatio"                                                       );          
    // histnames.push_back("h_jet1_tau32_rhoRatioPrime"                                                  );          
    // histnames.push_back("h_jet1_tau32_rhoRatioPmag"                                                   );          
    // histnames.push_back("h_jet1_tau32_rhoRatioPmagPrime"                                              );          
    // histnames.push_back("h_jet1_tau32_rhoRatioPuppi"                                                  );          
    // histnames.push_back("h_jet1_tau32_rhoRatioPuppiPrime"                                             );          
    // histnames.push_back("h_jet1_tau32_rhoRatioPuppiPmag"                                              );          
    // histnames.push_back("h_jet1_tau32_rhoRatioPuppiPmagPrime"                                         );          
    histnames.push_back("h_jet0_tau21_rhoRatio"                                                       );          
    histnames.push_back("h_jet0_tau21_rhoRatioPrime"                                                  );          
    histnames.push_back("h_jet0_tau21_rhoRatioPmag"                                                   );          
    histnames.push_back("h_jet0_tau21_rhoRatioPmagPrime"                                              );          
    histnames.push_back("h_jet0_tau21_rhoRatioPuppi"                                                  );          
    histnames.push_back("h_jet0_tau21_rhoRatioPuppiPrime"                                             );          
    histnames.push_back("h_jet0_tau21_rhoRatioPuppiPmag"                                              );          
    histnames.push_back("h_jet0_tau21_rhoRatioPuppiPmagPrime"                                         );          
    // histnames.push_back("h_jet1_tau21_rhoRatio"                                                       );          
    // histnames.push_back("h_jet1_tau21_rhoRatioPrime"                                                  );          
    // histnames.push_back("h_jet1_tau21_rhoRatioPmag"                                                   );          
    // histnames.push_back("h_jet1_tau21_rhoRatioPmagPrime"                                              );          
    // histnames.push_back("h_jet1_tau21_rhoRatioPuppi"                                                  );          
    // histnames.push_back("h_jet1_tau21_rhoRatioPuppiPrime"                                             );          
    // histnames.push_back("h_jet1_tau21_rhoRatioPuppiPmag"                                              );          
    // histnames.push_back("h_jet1_tau21_rhoRatioPuppiPmagPrime"                                         );          
    // histnames.push_back("h_jet0_tau42_rhoRatio"                                                       );          
    // histnames.push_back("h_jet0_tau42_rhoRatioPrime"                                                  );          
    // histnames.push_back("h_jet0_tau42_rhoRatioPmag"                                                   );          
    // histnames.push_back("h_jet0_tau42_rhoRatioPmagPrime"                                              );          
    // histnames.push_back("h_jet0_tau42_rhoRatioPuppi"                                                  );          
    // histnames.push_back("h_jet0_tau42_rhoRatioPuppiPrime"                                             );          
    // histnames.push_back("h_jet0_tau42_rhoRatioPuppiPmag"                                              );          
    // histnames.push_back("h_jet0_tau42_rhoRatioPuppiPmagPrime"                                         );          
    // histnames.push_back("h_jet1_tau42_rhoRatio"                                                       );          
    // histnames.push_back("h_jet1_tau42_rhoRatioPrime"                                                  );          
    // histnames.push_back("h_jet1_tau42_rhoRatioPmag"                                                   );          
    // histnames.push_back("h_jet1_tau42_rhoRatioPmagPrime"                                              );          
    // histnames.push_back("h_jet1_tau42_rhoRatioPuppi"                                                  );          
    // histnames.push_back("h_jet1_tau42_rhoRatioPuppiPrime"                                             );          
    // histnames.push_back("h_jet1_tau42_rhoRatioPuppiPmag"                                              );          
    // histnames.push_back("h_jet1_tau42_rhoRatioPuppiPmagPrime"                                         );          
                                                 
    histnames.push_back("h_2btag_jet0subjet0mass_jet0subjet1mass"                                     );              
    histnames.push_back("h_2btag_jet0subjet0bdisc_jet0subjet1bdisc"                                   );              
    histnames.push_back("h_2btag_jet1ttag_jet0subjet0mass_jet0subjet1mass"                            );                          
    histnames.push_back("h_2btag_jet1ttag_jet0subjet0bdisc_jet0subjet1bdisc"                          );                          
    histnames.push_back("h_2btag_jet0ttag_jet1subjet0mass_jet1subjet1mass"                            );                           
    histnames.push_back("h_2btag_jet0ttag_jet1subjet0bdisc_jet1subjet1bdisc"                          );                           
    histnames.push_back("h_topTag_jet0pt_jet0subjet0pt"                                               );                   
    histnames.push_back("h_topTag_jet0pt_jet0subjet1pt"                                               );                   
    histnames.push_back("h_topTag_jet0subjet0pt_jet0subjet1pt"                                        );                   
    histnames.push_back("h_topTag_jet0subjet0mass_jet0subjet1mass"                                    );                   
    histnames.push_back("h_topTag_jet0subjet0bdisc_jet0subjet1bdisc"                                  );                   
    histnames.push_back("h_topTag_jet0subjet0flav_jet0subjet1flav"                                    );                   
    histnames.push_back("h_topTagbTag_jet0pt_jet0subjet0pt"                                           );                    
    histnames.push_back("h_topTagbTag_jet0pt_jet0subjet1pt"                                           );                    
    histnames.push_back("h_topTagbTag_jet0subjet0pt_jet0subjet1pt"                                    );                    
    histnames.push_back("h_topTagbTag_jet0subjet0mass_jet0subjet1mass"                                );                    
    histnames.push_back("h_topTagbTag_jet0subjet0bdisc_jet0subjet1bdisc"                              );                    
    histnames.push_back("h_topTagbTag_jet0subjet0flav_jet0subjet1flav"                                );                    
                                                 
    // histnames.push_back("h_BeforeBtag_lightHad_Jet0_SubjetMaxB_Eta_Pt"                                );                                
    // histnames.push_back("h_BeforeBtag_cHad_Jet0_SubjetMaxB_Eta_Pt"                                    );                                
    // histnames.push_back("h_BeforeBtag_bHad_Jet0_SubjetMaxB_Eta_Pt"                                    );                                
    // histnames.push_back("h_AfterBtag_lightHad_Jet0_SubjetMaxB_Eta_Pt"                                 );                                
    // histnames.push_back("h_AfterBtag_cHad_Jet0_SubjetMaxB_Eta_Pt"                                     );                                
    // histnames.push_back("h_AfterBtag_bHad_Jet0_SubjetMaxB_Eta_Pt"                                     );                                
    // histnames.push_back("h_BeforeBtag_lightHad_Jet1_SubjetMaxB_Eta_Pt"                                );                                
    // histnames.push_back("h_BeforeBtag_cHad_Jet1_SubjetMaxB_Eta_Pt"                                    );                                
    // histnames.push_back("h_BeforeBtag_bHad_Jet1_SubjetMaxB_Eta_Pt"                                    );                                
    // histnames.push_back("h_AfterBtag_lightHad_Jet1_SubjetMaxB_Eta_Pt"                                 );                                
    // histnames.push_back("h_AfterBtag_cHad_Jet1_SubjetMaxB_Eta_Pt"                                     );                                
    // histnames.push_back("h_AfterBtag_bHad_Jet1_SubjetMaxB_Eta_Pt"                                     );                                
                                                 
    // histnames.push_back("h_2btag_jet0subjet0mass_jet0subjet1mass"                       );
    // histnames.push_back("h_2btag_jet0subjet0bdisc_jet0subjet1bdisc"                     );
    // histnames.push_back("h_2btag_jet1subjet0mass_jet1subjet1mass"                       );
    // histnames.push_back("h_2btag_jet1subjet0bdisc_jet1subjet1bdisc"                     );
    // histnames.push_back("h_2btag_jet1ttag_jet0subjet0mass_jet0subjet1mass"              );
    // histnames.push_back("h_2btag_jet1ttag_jet0subjet0bdisc_jet0subjet1bdisc"            );
    // histnames.push_back("h_2btag_jet0ttag_jet1subjet0mass_jet1subjet1mass"              );
    // histnames.push_back("h_2btag_jet0ttag_jet1subjet0bdisc_jet1subjet1bdisc"            );
    // histnames.push_back("h_topTagbTag_jet0subjet0pt"                                    );
    // histnames.push_back("h_topTagbTag_jet0subjet1pt"                                    );
    // histnames.push_back("h_topTagbTag_jet0pt"                                           );
    // histnames.push_back("h_topTagbTag_jet0pt_jet0subjet0pt"                             );
    // histnames.push_back("h_topTagbTag_jet0pt_jet0subjet1pt"                             );
    // histnames.push_back("h_topTagbTag_jet0subjet0pt_jet0subjet1pt"                      );
    // histnames.push_back("h_topTagbTag_jet0subjet0mass_jet0subjet1mass"                  );
    // histnames.push_back("h_topTagbTag_jet0subjet0bdisc_jet0subjet1bdisc"                );
    // histnames.push_back("h_topTagbTag_jet0subjet0flav_jet0subjet1flav"                  );
  }

  // Kinematic plots
  if (j==0){

    histnames.push_back("h_check_Jet0SDmaxbdisc"                           );
    histnames.push_back("h_check_Jet0SDmaxbdiscflavParton"                 );
    histnames.push_back("h_check_Jet0SDsubjet0bdisc"                       );
    histnames.push_back("h_check_Jet0SDsubjet0flavParton"                  );
    histnames.push_back("h_check_Jet0SDsubjet1bdisc"                       );
    histnames.push_back("h_check_Jet0SDsubjet1flavParton"                  );
    histnames.push_back("h_check_Jet0PuppiSDmaxbdisc"                      );
    histnames.push_back("h_check_Jet0PuppiSDmaxbdiscflavParton"            );
    histnames.push_back("h_check_Jet0PuppiSDsubjet0bdisc"                  );
    histnames.push_back("h_check_Jet0PuppiSDsubjet0flavParton"             );
    histnames.push_back("h_check_Jet0PuppiSDsubjet1bdisc"                  );
    histnames.push_back("h_check_Jet0PuppiSDsubjet1flavParton"             );
    histnames.push_back("h_check_Jet0GenMatched_partonPt"                  );
    histnames.push_back("h_check_Jet0GenMatched_partonID"                  );
    histnames.push_back("h_BeforeBtag_Inclusive_Jet0Pt"                    );
    histnames.push_back("h_BeforeBtag_Inclusive_Jet0P"                     );
    histnames.push_back("h_BeforeBtag_Inclusive_Jet0Rap"                   );
    histnames.push_back("h_BeforeBtag_light_Jet0Pt"                        );
    histnames.push_back("h_BeforeBtag_light_Jet0P"                         );
    histnames.push_back("h_BeforeBtag_light_Jet0Rap"                       );
    histnames.push_back("h_BeforeBtag_c_Jet0Pt"                            );
    histnames.push_back("h_BeforeBtag_c_Jet0P"                             );
    histnames.push_back("h_BeforeBtag_c_Jet0Rap"                           );
    histnames.push_back("h_BeforeBtag_b_Jet0Pt"                            );
    histnames.push_back("h_BeforeBtag_b_Jet0P"                             );
    histnames.push_back("h_BeforeBtag_b_Jet0Rap"                           );
    histnames.push_back("h_BeforeBtag_g_Jet0Pt"                            );
    histnames.push_back("h_BeforeBtag_g_Jet0P"                             );
    histnames.push_back("h_BeforeBtag_g_Jet0Rap"                           );      
    histnames.push_back("h_BeforeBtag_lightHad_Jet0Pt"                     );      
    histnames.push_back("h_BeforeBtag_lightHad_Jet0P"                      );      
    histnames.push_back("h_BeforeBtag_lightHad_Jet0Rap"                    );      
    histnames.push_back("h_BeforeBtag_cHad_Jet0Pt"                         );      
    histnames.push_back("h_BeforeBtag_cHad_Jet0P"                          );      
    histnames.push_back("h_BeforeBtag_cHad_Jet0Rap"                        );      
    histnames.push_back("h_BeforeBtag_bHad_Jet0Pt"                         );      
    histnames.push_back("h_BeforeBtag_bHad_Jet0P"                          );      
    histnames.push_back("h_BeforeBtag_bHad_Jet0Rap"                        );      
    histnames.push_back("h_AfterBtag_Inclusive_Jet0Pt"                     );     
    histnames.push_back("h_AfterBtag_Inclusive_Jet0P"                      );     
    histnames.push_back("h_AfterBtag_Inclusive_Jet0Rap"                    );     
    histnames.push_back("h_AfterBtag_light_Jet0Pt"                         );     
    histnames.push_back("h_AfterBtag_light_Jet0P"                          );     
    histnames.push_back("h_AfterBtag_light_Jet0Rap"                        );     
    histnames.push_back("h_AfterBtag_c_Jet0Pt"                             );     
    histnames.push_back("h_AfterBtag_c_Jet0P"                              );     
    histnames.push_back("h_AfterBtag_c_Jet0Rap"                            );     
    histnames.push_back("h_AfterBtag_b_Jet0Pt"                             );     
    histnames.push_back("h_AfterBtag_b_Jet0P"                              );     
    histnames.push_back("h_AfterBtag_b_Jet0Rap"                            );     
    histnames.push_back("h_AfterBtag_g_Jet0Pt"                             );     
    histnames.push_back("h_AfterBtag_g_Jet0P"                              );     
    histnames.push_back("h_AfterBtag_g_Jet0Rap"                            );     
    histnames.push_back("h_AfterBtag_lightHad_Jet0Pt"                      );      
    histnames.push_back("h_AfterBtag_lightHad_Jet0P"                       );      
    histnames.push_back("h_AfterBtag_lightHad_Jet0Rap"                     );      
    histnames.push_back("h_AfterBtag_cHad_Jet0Pt"                          );      
    histnames.push_back("h_AfterBtag_cHad_Jet0P"                           );      
    histnames.push_back("h_AfterBtag_cHad_Jet0Rap"                         );      
    histnames.push_back("h_AfterBtag_bHad_Jet0Pt"                          );      
    histnames.push_back("h_AfterBtag_bHad_Jet0P"                           );      
    histnames.push_back("h_AfterBtag_bHad_Jet0Rap"                         );      
    histnames.push_back("h_check_Jet1SDmaxbdisc"                           );      
    histnames.push_back("h_check_Jet1SDmaxbdiscflavParton"                 );
    histnames.push_back("h_check_Jet1SDsubjet0bdisc"                       );
    histnames.push_back("h_check_Jet1SDsubjet0flavParton"                  );
    histnames.push_back("h_check_Jet1SDsubjet1bdisc"                       );
    histnames.push_back("h_check_Jet1SDsubjet1flavParton"                  );
    histnames.push_back("h_check_Jet1PuppiSDmaxbdisc"                      );
    histnames.push_back("h_check_Jet1PuppiSDmaxbdiscflavParton"            );
    histnames.push_back("h_check_Jet1PuppiSDsubjet0bdisc"                  );
    histnames.push_back("h_check_Jet1PuppiSDsubjet0flavParton"             );
    histnames.push_back("h_check_Jet1PuppiSDsubjet1bdisc"                  );
    histnames.push_back("h_check_Jet1PuppiSDsubjet1flavParton"             );
    histnames.push_back("h_check_Jet1GenMatched_partonPt"                  );
    histnames.push_back("h_check_Jet1GenMatched_partonID"                  );
    histnames.push_back("h_BeforeBtag_Inclusive_Jet1Pt"                    );
    histnames.push_back("h_BeforeBtag_Inclusive_Jet1P"                     );
    histnames.push_back("h_BeforeBtag_Inclusive_Jet1Rap"                   );
    histnames.push_back("h_BeforeBtag_light_Jet1Pt"                        );
    histnames.push_back("h_BeforeBtag_light_Jet1P"                         );
    histnames.push_back("h_BeforeBtag_light_Jet1Rap"                       );
    histnames.push_back("h_BeforeBtag_c_Jet1Pt"                            );
    histnames.push_back("h_BeforeBtag_c_Jet1P"                             );
    histnames.push_back("h_BeforeBtag_c_Jet1Rap"                           );
    histnames.push_back("h_BeforeBtag_b_Jet1Pt"                            );
    histnames.push_back("h_BeforeBtag_b_Jet1P"                             );
    histnames.push_back("h_BeforeBtag_b_Jet1Rap"                           );
    histnames.push_back("h_BeforeBtag_g_Jet1Pt"                            );             
    histnames.push_back("h_BeforeBtag_g_Jet1P"                             );       
    histnames.push_back("h_BeforeBtag_g_Jet1Rap"                           );       
    histnames.push_back("h_BeforeBtag_lightHad_Jet1Pt"                     );       
    histnames.push_back("h_BeforeBtag_lightHad_Jet1P"                      );       
    histnames.push_back("h_BeforeBtag_lightHad_Jet1Rap"                    );       
    histnames.push_back("h_BeforeBtag_cHad_Jet1Pt"                         );       
    histnames.push_back("h_BeforeBtag_cHad_Jet1P"                          );       
    histnames.push_back("h_BeforeBtag_cHad_Jet1Rap"                        );       
    histnames.push_back("h_BeforeBtag_bHad_Jet1Pt"                         );       
    histnames.push_back("h_BeforeBtag_bHad_Jet1P"                          );       
    histnames.push_back("h_BeforeBtag_bHad_Jet1Rap"                        );       
    histnames.push_back("h_AfterBtag_Inclusive_Jet1Pt"                     );      
    histnames.push_back("h_AfterBtag_Inclusive_Jet1P"                      );      
    histnames.push_back("h_AfterBtag_Inclusive_Jet1Rap"                    );      
    histnames.push_back("h_AfterBtag_light_Jet1Pt"                         );      
    histnames.push_back("h_AfterBtag_light_Jet1P"                          );      
    histnames.push_back("h_AfterBtag_light_Jet1Rap"                        );      
    histnames.push_back("h_AfterBtag_c_Jet1Pt"                             );      
    histnames.push_back("h_AfterBtag_c_Jet1P"                              );      
    histnames.push_back("h_AfterBtag_c_Jet1Rap"                            );      
    histnames.push_back("h_AfterBtag_b_Jet1Pt"                             );      
    histnames.push_back("h_AfterBtag_b_Jet1P"                              );      
    histnames.push_back("h_AfterBtag_b_Jet1Rap"                            );      
    histnames.push_back("h_AfterBtag_g_Jet1Pt"                             );      
    histnames.push_back("h_AfterBtag_g_Jet1P"                              );      
    histnames.push_back("h_AfterBtag_g_Jet1Rap"                            );      
    histnames.push_back("h_AfterBtag_lightHad_Jet1Pt"                      );       
    histnames.push_back("h_AfterBtag_lightHad_Jet1P"                       );       
    histnames.push_back("h_AfterBtag_lightHad_Jet1Rap"                     );       
    histnames.push_back("h_AfterBtag_cHad_Jet1Pt"                          );       
    histnames.push_back("h_AfterBtag_cHad_Jet1P"                           );       
    histnames.push_back("h_AfterBtag_cHad_Jet1Rap"                         );       
    histnames.push_back("h_AfterBtag_bHad_Jet1Pt"                          );       
    histnames.push_back("h_AfterBtag_bHad_Jet1P"                           );       
    histnames.push_back("h_AfterBtag_bHad_Jet1Rap"                         );       
    histnames.push_back("h_BeforeBtag_lightHad_Jet0_DeltaRsubjets"         );   
    histnames.push_back("h_BeforeBtag_lightHad_Jet0_SubjetMaxB_Eta"        );   
    histnames.push_back("h_BeforeBtag_lightHad_Jet0_SubjetMaxB_Pt"         );   
    histnames.push_back("h_BeforeBtag_cHad_Jet0_DeltaRsubjets"             );   
    histnames.push_back("h_BeforeBtag_cHad_Jet0_SubjetMaxB_Eta"            );   
    histnames.push_back("h_BeforeBtag_cHad_Jet0_SubjetMaxB_Pt"             );   
    histnames.push_back("h_BeforeBtag_bHad_Jet0_DeltaRsubjets"             );   
    histnames.push_back("h_BeforeBtag_bHad_Jet0_SubjetMaxB_Eta"            );   
    histnames.push_back("h_BeforeBtag_bHad_Jet0_SubjetMaxB_Pt"             );   
    histnames.push_back("h_AfterBtag_lightHad_Jet0_DeltaRsubjets"          );   
    histnames.push_back("h_AfterBtag_lightHad_Jet0_SubjetMaxB_Eta"         );   
    histnames.push_back("h_AfterBtag_lightHad_Jet0_SubjetMaxB_Pt"          );   
    histnames.push_back("h_AfterBtag_cHad_Jet0_DeltaRsubjets"              );   
    histnames.push_back("h_AfterBtag_cHad_Jet0_SubjetMaxB_Eta"             );   
    histnames.push_back("h_AfterBtag_cHad_Jet0_SubjetMaxB_Pt"              );   
    histnames.push_back("h_AfterBtag_bHad_Jet0_DeltaRsubjets"              );   
    histnames.push_back("h_AfterBtag_bHad_Jet0_SubjetMaxB_Eta"             );   
    histnames.push_back("h_AfterBtag_bHad_Jet0_SubjetMaxB_Pt"              );   
    histnames.push_back("h_BeforeBtag_lightHad_Jet1_DeltaRsubjets"         );   
    histnames.push_back("h_BeforeBtag_lightHad_Jet1_SubjetMaxB_Eta"        );   
    histnames.push_back("h_BeforeBtag_lightHad_Jet1_SubjetMaxB_Pt"         );   
    histnames.push_back("h_BeforeBtag_cHad_Jet1_DeltaRsubjets"             );   
    histnames.push_back("h_BeforeBtag_cHad_Jet1_SubjetMaxB_Eta"            );   
    histnames.push_back("h_BeforeBtag_cHad_Jet1_SubjetMaxB_Pt"             );   
    histnames.push_back("h_BeforeBtag_bHad_Jet1_DeltaRsubjets"             );   
    histnames.push_back("h_BeforeBtag_bHad_Jet1_SubjetMaxB_Eta"            );   
    histnames.push_back("h_BeforeBtag_bHad_Jet1_SubjetMaxB_Pt"             );   
    histnames.push_back("h_AfterBtag_lightHad_Jet1_DeltaRsubjets"          );   
    histnames.push_back("h_AfterBtag_lightHad_Jet1_SubjetMaxB_Eta"         );   
    histnames.push_back("h_AfterBtag_lightHad_Jet1_SubjetMaxB_Pt"          );   
    histnames.push_back("h_AfterBtag_cHad_Jet1_DeltaRsubjets"              );   
    histnames.push_back("h_AfterBtag_cHad_Jet1_SubjetMaxB_Eta"             );   
    histnames.push_back("h_AfterBtag_cHad_Jet1_SubjetMaxB_Pt"              );   
    histnames.push_back("h_AfterBtag_bHad_Jet1_DeltaRsubjets"              );   
    histnames.push_back("h_AfterBtag_bHad_Jet1_SubjetMaxB_Eta"             );   
    histnames.push_back("h_AfterBtag_bHad_Jet1_SubjetMaxB_Pt"              );   

    histnames.push_back("h_deltaR_Jet0_sub0_sub1"                          );  
    histnames.push_back("h_deltaR_Jet1_sub0_sub1"                          );  
    histnames.push_back("h_deltaR_Jet0_pup0_pup1"                          );  
    histnames.push_back("h_deltaR_Jet1_pup0_pup1"                          );  
    histnames.push_back("h_deltaR_Jet0_sub0_pup0"                          );  
    histnames.push_back("h_deltaR_Jet0_sub1_pup1"                          );  
    histnames.push_back("h_deltaR_Jet1_sub0_pup0"                          );  
    histnames.push_back("h_deltaR_Jet1_sub1_pup1"                          );  

    // histnames.push_back("h_BeforeBtag_lightHad_Jet0_SubjetMaxB_Eta_Pt"     );   
    // histnames.push_back("h_BeforeBtag_cHad_Jet0_SubjetMaxB_Eta_Pt"         );   
    // histnames.push_back("h_BeforeBtag_bHad_Jet0_SubjetMaxB_Eta_Pt"         );   
    // histnames.push_back("h_AfterBtag_lightHad_Jet0_SubjetMaxB_Eta_Pt"      );   
    // histnames.push_back("h_AfterBtag_cHad_Jet0_SubjetMaxB_Eta_Pt"          );   
    // histnames.push_back("h_AfterBtag_bHad_Jet0_SubjetMaxB_Eta_Pt"          );   
    // histnames.push_back("h_BeforeBtag_lightHad_Jet1_SubjetMaxB_Eta_Pt"     );   
    // histnames.push_back("h_BeforeBtag_cHad_Jet1_SubjetMaxB_Eta_Pt"         );   
    // histnames.push_back("h_BeforeBtag_bHad_Jet1_SubjetMaxB_Eta_Pt"         );   
    // histnames.push_back("h_AfterBtag_lightHad_Jet1_SubjetMaxB_Eta_Pt"      );   
    // histnames.push_back("h_AfterBtag_cHad_Jet1_SubjetMaxB_Eta_Pt"          );   
    // histnames.push_back("h_AfterBtag_bHad_Jet1_SubjetMaxB_Eta_Pt"          );   


    histnames.push_back("h_CutFlow"                                              );
    histnames.push_back("h_EventWeight"                                          );         
    histnames.push_back("h_BtagCategoriesPreSF"                                  ); 
    histnames.push_back("h_BtagCategoriesPostSF"                                 );

    histnames.push_back("h_DoubleTopTag_BtagCategoriesPreSF"   );
    histnames.push_back("h_DoubleTopTag_BtagCategoriesPostSF"  );
    histnames.push_back("h_DoublePupTag_BtagCategoriesPreSF"   );
    histnames.push_back("h_DoublePupTag_BtagCategoriesPostSF"  );

    histnames.push_back("h_BtagCategoriesPuppiPreSF"              );
    histnames.push_back("h_BtagCategoriesPuppiPostSF"             );
    histnames.push_back("h_DoublePupTag_BtagCategoriesPuppiPreSF" );
    histnames.push_back("h_DoublePupTag_BtagCategoriesPuppiPostSF");


    histnames.push_back("h_DijetMass_dRapIn"                                     ); 
    histnames.push_back("h_DijetMass_dRapLo"                                     ); 
    histnames.push_back("h_DijetMass_dRapHi"                                     ); 
    histnames.push_back("h_DijetMassPlusNeighbor_dRapIn"                         ); 
    histnames.push_back("h_DijetMassPlusNeighbor_dRapLo"                         ); 
    histnames.push_back("h_DijetMassPlusNeighbor_dRapHi"                         ); 
    histnames.push_back("h_DeltaRap_mTTgt1"                                      ); 
    histnames.push_back("h_DeltaRap_mTTgt2"                                      ); 
    histnames.push_back("h_DeltaRap_mTTgt3"                                      ); 



    histnames.push_back("h_topTag_jet0subjet0pt"                                 ); 
    histnames.push_back("h_topTag_jet0subjet1pt"                                 ); 
    histnames.push_back("h_topTag_jet0pt"                                        ); 
    histnames.push_back("h_topTag_jet0subjet0mass"                               ); 
    histnames.push_back("h_topTag_jet0subjet1mass"                               ); 
    histnames.push_back("h_topTag_jet0subjet0bdisc"                              ); 
    histnames.push_back("h_topTag_jet0subjet1bdisc"                              ); 
    histnames.push_back("h_topTag_jet0maxBdisc"                                  ); 
    histnames.push_back("h_topTagbTag_jet0subjet0pt"                             ); 
    histnames.push_back("h_topTagbTag_jet0subjet1pt"                             ); 
    histnames.push_back("h_topTagbTag_jet0pt"                                    ); 
    histnames.push_back("h_topTagbTag_jet0subjet0mass"                           ); 
    histnames.push_back("h_topTagbTag_jet0subjet1mass"                           ); 
    histnames.push_back("h_topTagbTag_jet0subjet0bdisc"                          ); 
    histnames.push_back("h_topTagbTag_jet0subjet1bdisc"                          ); 
    histnames.push_back("h_topTagbTag_jet0maxBdisc"                              ); 
    histnames.push_back("h_DeltaRap"                                             ); 
    histnames.push_back("h_DeltaPhi"                                             ); 
    histnames.push_back("h_DeltaPhi_PreCut"                                      ); 
    histnames.push_back("h_HT"                                                   ); 
    histnames.push_back("h_MET"                                                  ); 
    histnames.push_back("h_METphi"                                               ); 
    histnames.push_back("h_Nvtx"                                                 ); 
    histnames.push_back("h_Jet0P"                                                ); 
    histnames.push_back("h_Jet0Pt"                                               ); 
    histnames.push_back("h_Jet0Phi"                                              ); 
    histnames.push_back("h_Jet0Rap"                                              ); 
    histnames.push_back("h_Jet0sdmass"                                           ); 
    histnames.push_back("h_Jet0Tau1"                                             ); 
    histnames.push_back("h_Jet0Tau2"                                             ); 
    histnames.push_back("h_Jet0Tau3"                                             ); 
    histnames.push_back("h_Jet0Tau4"                                             ); 
    histnames.push_back("h_Jet0SDmaxbdisc"                                       ); 
    histnames.push_back("h_Jet0SDsubjet0pt"                                      ); 
    histnames.push_back("h_Jet0SDsubjet0mass"                                    ); 
    histnames.push_back("h_Jet0SDsubjet0tau1"                                    ); 
    histnames.push_back("h_Jet0SDsubjet0tau2"                                    ); 
    histnames.push_back("h_Jet0SDsubjet0tau3"                                    ); 
    histnames.push_back("h_Jet0SDsubjet0bdisc"                                   ); 
    histnames.push_back("h_Jet0SDsubjet1pt"                                      ); 
    histnames.push_back("h_Jet0SDsubjet1mass"                                    ); 
    histnames.push_back("h_Jet0SDsubjet1tau1"                                    ); 
    histnames.push_back("h_Jet0SDsubjet1tau2"                                    ); 
    histnames.push_back("h_Jet0SDsubjet1tau3"                                    ); 
    histnames.push_back("h_Jet0SDsubjet1bdisc"                                   ); 
    histnames.push_back("h_Jet0PuppiPt"                                          ); 
    histnames.push_back("h_Jet0PuppiMass"                                        ); 
    histnames.push_back("h_Jet0PuppiSDpt"                                        ); 
    histnames.push_back("h_Jet0PuppiTau1"                                        ); 
    histnames.push_back("h_Jet0PuppiTau2"                                        ); 
    histnames.push_back("h_Jet0PuppiTau3"                                        ); 
    histnames.push_back("h_Jet0PuppiTau4"                                        ); 
    histnames.push_back("h_Jet0PuppiTau32"                                       ); 
    histnames.push_back("h_Jet0PuppiTau21"                                       ); 
    histnames.push_back("h_Jet0PuppiSDmaxbdisc"                                  ); 
    histnames.push_back("h_Jet0PuppiSDsubjet0pt"                                 ); 
    histnames.push_back("h_Jet0PuppiSDsubjet0mass"                               ); 
    histnames.push_back("h_Jet0PuppiSDsubjet0tau1"                               ); 
    histnames.push_back("h_Jet0PuppiSDsubjet0tau2"                               ); 
    histnames.push_back("h_Jet0PuppiSDsubjet0tau3"                               ); 
    histnames.push_back("h_Jet0PuppiSDsubjet0tau21"                               ); 
    histnames.push_back("h_Jet0PuppiSDsubjet0bdisc"                              ); 
    histnames.push_back("h_Jet0PuppiSDsubjet1pt"                                 ); 
    histnames.push_back("h_Jet0PuppiSDsubjet1mass"                               ); 
    histnames.push_back("h_Jet0PuppiSDsubjet1tau1"                               ); 
    histnames.push_back("h_Jet0PuppiSDsubjet1tau2"                               ); 
    histnames.push_back("h_Jet0PuppiSDsubjet1tau3"                               ); 
    histnames.push_back("h_Jet0PuppiSDsubjet1tau21"                               ); 
    histnames.push_back("h_Jet0PuppiSDsubjet1bdisc"                              ); 
    histnames.push_back("h_Jet0CHF"                                              ); 
    histnames.push_back("h_Jet0NHF"                                              ); 
    histnames.push_back("h_Jet0CM"                                               ); 
    histnames.push_back("h_Jet0NM"                                               ); 
    histnames.push_back("h_Jet0NEF"                                              ); 
    histnames.push_back("h_Jet0CEF"                                              ); 
    histnames.push_back("h_Jet0MF"                                               ); 
    histnames.push_back("h_Jet0Mult"                                             ); 
    histnames.push_back("h_Jet0PuppiCHF"                                         ); 
    histnames.push_back("h_Jet0PuppiNHF"                                         ); 
    histnames.push_back("h_Jet0PuppiCM"                                          ); 
    histnames.push_back("h_Jet0PuppiNM"                                          ); 
    histnames.push_back("h_Jet0PuppiNEF"                                         ); 
    histnames.push_back("h_Jet0PuppiCEF"                                         ); 
    histnames.push_back("h_Jet0PuppiMF"                                          ); 
    histnames.push_back("h_Jet0PuppiMult"                                        ); 
    histnames.push_back("h_Jet0puppisdmass"                                      ); 
    histnames.push_back("h_Jet0NsubjetsSDPuppi"                                  ); 


    histnames.push_back("h_Jet1P"                                                ); 
    histnames.push_back("h_Jet1Pt"                                               ); 
    histnames.push_back("h_Jet1Phi"                                              ); 
    histnames.push_back("h_Jet1Rap"                                              ); 
    histnames.push_back("h_Jet1sdmass"                                           ); 
    histnames.push_back("h_Jet1Tau1"                                             ); 
    histnames.push_back("h_Jet1Tau2"                                             ); 
    histnames.push_back("h_Jet1Tau3"                                             ); 
    histnames.push_back("h_Jet1Tau4"                                             ); 
    histnames.push_back("h_Jet1SDmaxbdisc"                                       ); 
    histnames.push_back("h_Jet1SDsubjet0pt"                                      ); 
    histnames.push_back("h_Jet1SDsubjet0mass"                                    ); 
    histnames.push_back("h_Jet1SDsubjet0tau1"                                    ); 
    histnames.push_back("h_Jet1SDsubjet0tau2"                                    ); 
    histnames.push_back("h_Jet1SDsubjet0tau3"                                    ); 
    histnames.push_back("h_Jet1SDsubjet0bdisc"                                   ); 
    histnames.push_back("h_Jet1SDsubjet1pt"                                      ); 
    histnames.push_back("h_Jet1SDsubjet1mass"                                    ); 
    histnames.push_back("h_Jet1SDsubjet1tau1"                                    ); 
    histnames.push_back("h_Jet1SDsubjet1tau2"                                    ); 
    histnames.push_back("h_Jet1SDsubjet1tau3"                                    ); 
    histnames.push_back("h_Jet1SDsubjet1bdisc"                                   ); 
    histnames.push_back("h_Jet1PuppiPt"                                          ); 
    histnames.push_back("h_Jet1PuppiMass"                                        ); 
    histnames.push_back("h_Jet1PuppiSDpt"                                        ); 
    histnames.push_back("h_Jet1PuppiTau1"                                        ); 
    histnames.push_back("h_Jet1PuppiTau2"                                        ); 
    histnames.push_back("h_Jet1PuppiTau3"                                        ); 
    histnames.push_back("h_Jet1PuppiTau4"                                        ); 
    histnames.push_back("h_Jet1PuppiTau32"                                       ); 
    histnames.push_back("h_Jet1PuppiTau21"                                       ); 
    histnames.push_back("h_Jet1PuppiSDmaxbdisc"                                  ); 
    histnames.push_back("h_Jet1PuppiSDsubjet0pt"                                 ); 
    histnames.push_back("h_Jet1PuppiSDsubjet0mass"                               ); 
    histnames.push_back("h_Jet1PuppiSDsubjet0tau1"                               ); 
    histnames.push_back("h_Jet1PuppiSDsubjet0tau2"                               ); 
    histnames.push_back("h_Jet1PuppiSDsubjet0tau3"                               ); 
    histnames.push_back("h_Jet1PuppiSDsubjet0tau21"                               ); 
    histnames.push_back("h_Jet1PuppiSDsubjet0bdisc"                              ); 
    histnames.push_back("h_Jet1PuppiSDsubjet1pt"                                 ); 
    histnames.push_back("h_Jet1PuppiSDsubjet1mass"                               ); 
    histnames.push_back("h_Jet1PuppiSDsubjet1tau1"                               ); 
    histnames.push_back("h_Jet1PuppiSDsubjet1tau2"                               ); 
    histnames.push_back("h_Jet1PuppiSDsubjet1tau3"                               ); 
    histnames.push_back("h_Jet1PuppiSDsubjet1tau21"                               ); 
    histnames.push_back("h_Jet1PuppiSDsubjet1bdisc"                              ); 
    histnames.push_back("h_Jet1CHF"                                              ); 
    histnames.push_back("h_Jet1NHF"                                              ); 
    histnames.push_back("h_Jet1CM"                                               ); 
    histnames.push_back("h_Jet1NM"                                               ); 
    histnames.push_back("h_Jet1NEF"                                              ); 
    histnames.push_back("h_Jet1CEF"                                              ); 
    histnames.push_back("h_Jet1MF"                                               ); 
    histnames.push_back("h_Jet1Mult"                                             ); 
    histnames.push_back("h_Jet1PuppiCHF"                                         ); 
    histnames.push_back("h_Jet1PuppiNHF"                                         ); 
    histnames.push_back("h_Jet1PuppiCM"                                          ); 
    histnames.push_back("h_Jet1PuppiNM"                                          ); 
    histnames.push_back("h_Jet1PuppiNEF"                                         ); 
    histnames.push_back("h_Jet1PuppiCEF"                                         ); 
    histnames.push_back("h_Jet1PuppiMF"                                          ); 
    histnames.push_back("h_Jet1PuppiMult"                                        ); 
    histnames.push_back("h_Jet1puppisdmass"                                      ); 
    // histnames.push_back("h_Jet1NsubjetsSDPuppi"                                  ); 


    // histnames.push_back("h_Jet1Pt"                                               ); 
    // histnames.push_back("h_Jet1Rap"                                              ); 
    // histnames.push_back("h_Jet1sdmass"                                           ); 
    // histnames.push_back("h_Jet1puppisdmass"                                      ); 
    // histnames.push_back("h_Jet0puppisdmass"                                      ); 
    // histnames.push_back("h_Jet0puppisdmassOfficialCorr"                          ); 
    // histnames.push_back("h_Jet0puppisdmassNoSmear"                               ); 
    // histnames.push_back("h_DijetMass_masstag"                                    ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_lt0p30"                       ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_lt0p35"                       ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_lt0p40"                       ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_lt0p45"                       ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_lt0p48"                       ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_lt0p50"                       ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_lt0p53"                       ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_lt0p55"                       ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_lt0p58"                       ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_lt0p60"                       ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_lt0p63"                       ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_lt0p65"                       ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_lt0p68"                       ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_lt0p70"                       ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_lt0p72"                       ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_lt0p75"                       ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_lt0p80"                       ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_gt0p50"                       ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_gt0p55"                       ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_gt0p60"                       ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_gt0p65"                       ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_gt0p68"                       ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_gt0p70"                       ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_gt0p72"                       ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_gt0p75"                       ); 
    // histnames.push_back("h_DijetMass_masstag_tau32_gt0p80"                       ); 
    histnames.push_back("h_DijetMass_masspuptag"                                 ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_lt0p30"               ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_lt0p35"               ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_lt0p40"               ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_lt0p45"               ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_lt0p48"               ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_lt0p50"               ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_lt0p53"               ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_lt0p55"               ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_lt0p58"               ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_lt0p60"               ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_lt0p63"               ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_lt0p65"               ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_lt0p68"               ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_lt0p70"               ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_lt0p72"               ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_lt0p75"               ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_lt0p80"               ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_gt0p50"               ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_gt0p55"               ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_gt0p60"               ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_gt0p65"               ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_gt0p68"               ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_gt0p70"               ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_gt0p72"               ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_gt0p75"               ); 
    histnames.push_back("h_DijetMass_masspuptag_puppitau32_gt0p80"               ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag"                        ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_lt0p30"           ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_lt0p35"           ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_lt0p40"           ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_lt0p45"           ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_lt0p48"           ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_lt0p50"           ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_lt0p53"           ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_lt0p55"           ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_lt0p58"           ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_lt0p60"           ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_lt0p63"           ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_lt0p65"           ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_lt0p68"           ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_lt0p70"           ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_lt0p72"           ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_lt0p75"           ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_lt0p80"           ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_gt0p50"           ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_gt0p55"           ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_gt0p60"           ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_gt0p65"           ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_gt0p68"           ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_gt0p70"           ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_gt0p72"           ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_gt0p75"           ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_masstag_tau32_gt0p80"           ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag"                             ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_lt0p30"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_lt0p35"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_lt0p40"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_lt0p45"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_lt0p48"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_lt0p50"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_lt0p53"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_lt0p55"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_lt0p58"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_lt0p60"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_lt0p63"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_lt0p65"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_lt0p68"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_lt0p70"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_lt0p72"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_lt0p75"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_lt0p80"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_gt0p50"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_gt0p55"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_gt0p60"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_gt0p65"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_gt0p68"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_gt0p70"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_gt0p72"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_gt0p75"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masstag_tau32_gt0p80"                ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag"                          ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_lt0p30"        ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_lt0p35"        ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_lt0p40"        ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_lt0p45"        ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_lt0p48"        ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_lt0p50"        ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_lt0p53"        ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_lt0p55"        ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_lt0p58"        ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_lt0p60"        ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_lt0p63"        ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_lt0p65"        ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_lt0p68"        ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_lt0p70"        ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_lt0p72"        ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_lt0p75"        ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_lt0p80"        ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_gt0p50"        ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_gt0p55"        ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_gt0p60"        ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_gt0p65"        ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_gt0p68"        ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_gt0p70"        ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_gt0p72"        ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_gt0p75"        ); 
    // histnames.push_back("h_DijetMass_2btagL_masspuptag_puppitau32_gt0p80"        ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag"                 ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_lt0p30"    ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_lt0p35"    ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_lt0p40"    ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_lt0p45"    ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_lt0p48"    ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_lt0p50"    ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_lt0p53"    ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_lt0p55"    ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_lt0p58"    ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_lt0p60"    ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_lt0p63"    ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_lt0p65"    ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_lt0p68"    ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_lt0p70"    ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_lt0p72"    ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_lt0p75"    ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_lt0p80"    ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_gt0p50"    ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_gt0p55"    ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_gt0p60"    ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_gt0p65"    ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_gt0p68"    ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_gt0p70"    ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_gt0p72"    ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_gt0p75"    ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btagL_masstag_tau32_gt0p80"    ); 
    // histnames.push_back("h_DijetMass_2btag_masstag"                              ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_lt0p30"                 ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_lt0p35"                 ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_lt0p40"                 ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_lt0p45"                 ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_lt0p48"                 ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_lt0p50"                 ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_lt0p53"                 ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_lt0p55"                 ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_lt0p58"                 ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_lt0p60"                 ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_lt0p63"                 ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_lt0p65"                 ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_lt0p68"                 ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_lt0p70"                 ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_lt0p72"                 ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_lt0p75"                 ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_lt0p80"                 ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_gt0p50"                 ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_gt0p55"                 ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_gt0p60"                 ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_gt0p65"                 ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_gt0p68"                 ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_gt0p70"                 ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_gt0p72"                 ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_gt0p75"                 ); 
    // histnames.push_back("h_DijetMass_2btag_masstag_tau32_gt0p80"                 ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag"                           ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_lt0p30"         ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_lt0p35"         ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_lt0p40"         ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_lt0p45"         ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_lt0p48"         ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_lt0p50"         ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_lt0p53"         ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_lt0p55"         ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_lt0p58"         ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_lt0p60"         ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_lt0p63"         ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_lt0p65"         ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_lt0p68"         ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_lt0p70"         ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_lt0p72"         ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_lt0p75"         ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_lt0p80"         ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_gt0p50"         ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_gt0p55"         ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_gt0p60"         ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_gt0p65"         ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_gt0p68"         ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_gt0p70"         ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_gt0p72"         ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_gt0p75"         ); 
    histnames.push_back("h_DijetMass_2btag_masspuptag_puppitau32_gt0p80"         ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag"                  ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_lt0p30"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_lt0p35"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_lt0p40"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_lt0p45"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_lt0p48"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_lt0p50"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_lt0p53"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_lt0p55"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_lt0p58"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_lt0p60"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_lt0p63"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_lt0p65"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_lt0p68"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_lt0p70"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_lt0p72"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_lt0p75"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_lt0p80"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_gt0p50"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_gt0p55"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_gt0p60"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_gt0p65"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_gt0p68"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_gt0p70"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_gt0p72"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_gt0p75"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_2btag_masstag_tau32_gt0p80"     ); 
    // histnames.push_back("h_DijetMass_1btag_masstag"                              ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_lt0p30"                 ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_lt0p35"                 ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_lt0p40"                 ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_lt0p45"                 ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_lt0p48"                 ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_lt0p50"                 ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_lt0p53"                 ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_lt0p55"                 ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_lt0p58"                 ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_lt0p60"                 ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_lt0p63"                 ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_lt0p65"                 ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_lt0p68"                 ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_lt0p70"                 ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_lt0p72"                 ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_lt0p75"                 ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_lt0p80"                 ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_gt0p50"                 ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_gt0p55"                 ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_gt0p60"                 ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_gt0p65"                 ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_gt0p68"                 ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_gt0p70"                 ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_gt0p72"                 ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_gt0p75"                 ); 
    // histnames.push_back("h_DijetMass_1btag_masstag_tau32_gt0p80"                 ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag"                           ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_lt0p30"         ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_lt0p35"         ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_lt0p40"         ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_lt0p45"         ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_lt0p48"         ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_lt0p50"         ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_lt0p53"         ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_lt0p55"         ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_lt0p58"         ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_lt0p60"         ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_lt0p63"         ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_lt0p65"         ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_lt0p68"         ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_lt0p70"         ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_lt0p72"         ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_lt0p75"         ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_lt0p80"         ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_gt0p50"         ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_gt0p55"         ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_gt0p60"         ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_gt0p65"         ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_gt0p68"         ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_gt0p70"         ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_gt0p72"         ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_gt0p75"         ); 
    histnames.push_back("h_DijetMass_1btag_masspuptag_puppitau32_gt0p80"         ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag"                  ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_lt0p30"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_lt0p35"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_lt0p40"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_lt0p45"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_lt0p48"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_lt0p50"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_lt0p53"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_lt0p55"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_lt0p58"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_lt0p60"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_lt0p63"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_lt0p65"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_lt0p68"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_lt0p70"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_lt0p72"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_lt0p75"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_lt0p80"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_gt0p50"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_gt0p55"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_gt0p60"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_gt0p65"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_gt0p68"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_gt0p70"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_gt0p72"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_gt0p75"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_1btag_masstag_tau32_gt0p80"     ); 
    // histnames.push_back("h_DijetMass_0btag_masstag"                              ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_lt0p30"                 ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_lt0p35"                 ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_lt0p40"                 ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_lt0p45"                 ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_lt0p48"                 ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_lt0p50"                 ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_lt0p53"                 ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_lt0p55"                 ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_lt0p58"                 ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_lt0p60"                 ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_lt0p63"                 ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_lt0p65"                 ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_lt0p68"                 ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_lt0p70"                 ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_lt0p72"                 ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_lt0p75"                 ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_lt0p80"                 ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_gt0p50"                 ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_gt0p55"                 ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_gt0p60"                 ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_gt0p65"                 ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_gt0p68"                 ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_gt0p70"                 ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_gt0p72"                 ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_gt0p75"                 ); 
    // histnames.push_back("h_DijetMass_0btag_masstag_tau32_gt0p80"                 ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag"                           ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_lt0p30"         ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_lt0p35"         ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_lt0p40"         ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_lt0p45"         ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_lt0p48"         ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_lt0p50"         ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_lt0p53"         ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_lt0p55"         ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_lt0p58"         ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_lt0p60"         ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_lt0p63"         ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_lt0p65"         ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_lt0p68"         ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_lt0p70"         ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_lt0p72"         ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_lt0p75"         ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_lt0p80"         ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_gt0p50"         ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_gt0p55"         ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_gt0p60"         ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_gt0p65"         ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_gt0p68"         ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_gt0p70"         ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_gt0p72"         ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_gt0p75"         ); 
    histnames.push_back("h_DijetMass_0btag_masspuptag_puppitau32_gt0p80"         ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag"                  ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_lt0p30"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_lt0p35"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_lt0p40"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_lt0p45"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_lt0p48"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_lt0p50"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_lt0p53"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_lt0p55"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_lt0p58"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_lt0p60"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_lt0p63"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_lt0p65"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_lt0p68"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_lt0p70"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_lt0p72"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_lt0p75"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_lt0p80"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_gt0p50"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_gt0p55"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_gt0p60"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_gt0p65"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_gt0p68"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_gt0p70"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_gt0p72"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_gt0p75"     ); 
    // histnames.push_back("h_DijetMassPlusNeighbor_0btag_masstag_tau32_gt0p80"     ); 
    histnames.push_back("h_Jet0SDmass"                                           ); 
    histnames.push_back("h_Jet0SDmass_JetTag_b"                                  ); 
    histnames.push_back("h_Jet0SDmass_JetTag_tau32"                              ); 
    histnames.push_back("h_Jet0SDmass_JetTag_b_tau32"                            ); 
    histnames.push_back("h_Jet0SDmass_OppositeJetTag_t_b"                        ); 
    histnames.push_back("h_Jet0SDmass_OppositeJetTag_t_b_JetTag_b"               ); 
    histnames.push_back("h_Jet0SDmass_OppositeJetTag_t_b_JetTag_b_tau32"         ); 
    histnames.push_back("h_Jet1SDmass"                                           ); 
    histnames.push_back("h_Jet1SDmass_JetTag_b"                                  ); 
    histnames.push_back("h_Jet1SDmass_JetTag_tau32"                              ); 
    histnames.push_back("h_Jet1SDmass_JetTag_b_tau32"                            ); 
    histnames.push_back("h_Jet1SDmass_OppositeJetTag_t_b"                        ); 
    histnames.push_back("h_Jet1SDmass_OppositeJetTag_t_b_JetTag_b"               ); 
    histnames.push_back("h_Jet1SDmass_OppositeJetTag_t_b_JetTag_b_tau32"         ); 
    histnames.push_back("h_JetSDmass"                                            ); 
    histnames.push_back("h_JetSDmass_JetTag_b"                                   ); 
    histnames.push_back("h_JetSDmass_JetTag_tau32"                               ); 
    histnames.push_back("h_JetSDmass_JetTag_b_tau32"                             ); 
    histnames.push_back("h_JetSDmass_OppositeJetTag_t_b"                         ); 
    histnames.push_back("h_JetSDmass_OppositeJetTag_t_b_JetTag_b"                ); 
    histnames.push_back("h_JetSDmass_OppositeJetTag_t_b_JetTag_b_tau32"          ); 
    histnames.push_back("h_Jet0Tau32"                                            ); 
    histnames.push_back("h_Jet0Tau32_JetTag_b"                                   ); 
    histnames.push_back("h_Jet0Tau32_JetTag_mass"                                ); 
    histnames.push_back("h_Jet0Tau32_JetTag_b_mass"                              ); 
    histnames.push_back("h_Jet0Tau32_OppositeJetTag_t_b"                         ); 
    histnames.push_back("h_Jet0Tau32_OppositeJetTag_t_b_JetTag_b"                ); 
    histnames.push_back("h_Jet0Tau32_OppositeJetTag_t_b_JetTag_b_mass"           ); 
    histnames.push_back("h_Jet1Tau32"                                            ); 
    histnames.push_back("h_Jet1Tau32_JetTag_b"                                   ); 
    histnames.push_back("h_Jet1Tau32_JetTag_mass"                                ); 
    histnames.push_back("h_Jet1Tau32_JetTag_b_mass"                              ); 
    histnames.push_back("h_Jet1Tau32_OppositeJetTag_t_b"                         ); 
    histnames.push_back("h_Jet1Tau32_OppositeJetTag_t_b_JetTag_b"                ); 
    histnames.push_back("h_Jet1Tau32_OppositeJetTag_t_b_JetTag_b_mass"           ); 
    histnames.push_back("h_JetTau32"                                             ); 
    histnames.push_back("h_JetTau32_JetTag_b"                                    ); 
    histnames.push_back("h_JetTau32_JetTag_mass"                                 ); 
    histnames.push_back("h_JetTau32_JetTag_b_mass"                               ); 
    histnames.push_back("h_JetTau32_OppositeJetTag_t_b"                          ); 
    histnames.push_back("h_JetTau32_OppositeJetTag_t_b_JetTag_b"                 ); 
    histnames.push_back("h_JetTau32_OppositeJetTag_t_b_JetTag_b_mass"            ); 

    histnames.push_back("h_pup_Jet0SDmass"                                       );
    histnames.push_back("h_pup_Jet0SDmass_JetTag_b"                              );
    histnames.push_back("h_pup_Jet0SDmass_JetTag_tau32"                          );
    histnames.push_back("h_pup_Jet0SDmass_JetTag_b_tau32"                        );
    histnames.push_back("h_pup_Jet0SDmass_OppositeJetTag_t_b"                    );
    histnames.push_back("h_pup_Jet0SDmass_OppositeJetTag_t_b_JetTag_b"           );
    histnames.push_back("h_pup_Jet0SDmass_OppositeJetTag_t_b_JetTag_b_tau32"     );

    histnames.push_back("h_pupSubjetCorr_Jet0SDmass"                                   );
    histnames.push_back("h_pupSubjetCorr_Jet0SDmass_JetTag_b"                          );
    histnames.push_back("h_pupSubjetCorr_Jet0SDmass_JetTag_tau32"                      );
    histnames.push_back("h_pupSubjetCorr_Jet0SDmass_JetTag_b_tau32"                    );
    histnames.push_back("h_pupSubjetCorr_Jet0SDmass_OppositeJetTag_t_b"                );
    histnames.push_back("h_pupSubjetCorr_Jet0SDmass_OppositeJetTag_t_b_JetTag_b"       );
    histnames.push_back("h_pupSubjetCorr_Jet0SDmass_OppositeJetTag_t_b_JetTag_b_tau32" );


    histnames.push_back("h_pup_Jet1SDmass"                                       );
    histnames.push_back("h_pup_Jet1SDmass_JetTag_b"                              );
    histnames.push_back("h_pup_Jet1SDmass_JetTag_tau32"                          );
    histnames.push_back("h_pup_Jet1SDmass_JetTag_b_tau32"                        );
    histnames.push_back("h_pup_Jet1SDmass_OppositeJetTag_t_b"                    );
    histnames.push_back("h_pup_Jet1SDmass_OppositeJetTag_t_b_JetTag_b"           );
    histnames.push_back("h_pup_Jet1SDmass_OppositeJetTag_t_b_JetTag_b_tau32"     );
    histnames.push_back("h_pup_JetSDmass"                                        );
    histnames.push_back("h_pup_JetSDmass_JetTag_b"                               );
    histnames.push_back("h_pup_JetSDmass_JetTag_tau32"                           );
    histnames.push_back("h_pup_JetSDmass_JetTag_b_tau32"                         );
    histnames.push_back("h_pup_JetSDmass_OppositeJetTag_t_b"                     );
    histnames.push_back("h_pup_JetSDmass_OppositeJetTag_t_b_JetTag_b"            );
    histnames.push_back("h_pup_JetSDmass_OppositeJetTag_t_b_JetTag_b_tau32"      );
    histnames.push_back("h_pup_Jet0Tau32"                                        );
    histnames.push_back("h_pup_Jet0Tau32_JetTag_b"                               );
    histnames.push_back("h_pup_Jet0Tau32_JetTag_mass"                            );
    histnames.push_back("h_pup_Jet0Tau32_JetTag_b_mass"                          );
    histnames.push_back("h_pup_Jet0Tau32_OppositeJetTag_t_b"                     );
    histnames.push_back("h_pup_Jet0Tau32_OppositeJetTag_t_b_JetTag_b"            );
    histnames.push_back("h_pup_Jet0Tau32_OppositeJetTag_t_b_JetTag_b_mass"       );
    histnames.push_back("h_pup_Jet1Tau32"                                        );
    histnames.push_back("h_pup_Jet1Tau32_JetTag_b"                               );
    histnames.push_back("h_pup_Jet1Tau32_JetTag_mass"                            );
    histnames.push_back("h_pup_Jet1Tau32_JetTag_b_mass"                          );
    histnames.push_back("h_pup_Jet1Tau32_OppositeJetTag_t_b"                     );
    histnames.push_back("h_pup_Jet1Tau32_OppositeJetTag_t_b_JetTag_b"            );
    histnames.push_back("h_pup_Jet1Tau32_OppositeJetTag_t_b_JetTag_b_mass"       );
    histnames.push_back("h_pup_JetTau32"                                         );
    histnames.push_back("h_pup_JetTau32_JetTag_b"                                );
    histnames.push_back("h_pup_JetTau32_JetTag_mass"                             );
    histnames.push_back("h_pup_JetTau32_JetTag_b_mass"                           );
    histnames.push_back("h_pup_JetTau32_OppositeJetTag_t_b"                      );
    histnames.push_back("h_pup_JetTau32_OppositeJetTag_t_b_JetTag_b"             );
    histnames.push_back("h_pup_JetTau32_OppositeJetTag_t_b_JetTag_b_mass"        );
    histnames.push_back("h_pup_JetTrimMass"                                       );
    histnames.push_back("h_pup_JetTrimMass_JetTag_b"                              );
    histnames.push_back("h_pup_JetTrimMass_JetTag_tau32"                          );
    histnames.push_back("h_pup_JetTrimMass_JetTag_b_tau32"                        );
    histnames.push_back("h_pup_JetTrimMass_OppositeJetTag_t_b"                    );
    histnames.push_back("h_pup_JetTrimMass_OppositeJetTag_t_b_JetTag_b"           );
    histnames.push_back("h_pup_JetTrimMass_OppositeJetTag_t_b_JetTag_b_tau32"     );
    histnames.push_back("h_pup_JetPruneMass"                                     );
    histnames.push_back("h_pup_JetPruneMass_JetTag_b"                            );
    histnames.push_back("h_pup_JetPruneMass_JetTag_tau32"                        );
    histnames.push_back("h_pup_JetPruneMass_JetTag_b_tau32"                      );
    histnames.push_back("h_pup_JetPruneMass_OppositeJetTag_t_b"                  );
    histnames.push_back("h_pup_JetPruneMass_OppositeJetTag_t_b_JetTag_b"         );
    histnames.push_back("h_pup_JetPruneMass_OppositeJetTag_t_b_JetTag_b_tau32"   );
    histnames.push_back("h_pup_Subjet0Mass"                                      );
    histnames.push_back("h_pup_Subjet0Mass_JetTag_b"                             );
    histnames.push_back("h_pup_Subjet0Mass_JetTag_mass"                          );
    histnames.push_back("h_pup_Subjet0Mass_JetTag_b_mass"                        );
    histnames.push_back("h_pup_Subjet0Mass_OppositeJetTag_t_b"                   );
    histnames.push_back("h_pup_Subjet0Mass_OppositeJetTag_t_b_JetTag_b"          );
    histnames.push_back("h_pup_Subjet0Mass_OppositeJetTag_t_b_JetTag_b_mass"     );
    histnames.push_back("h_pup_Subjet0Mass_OppositeJetTag_t_b_JetTag_b_t"        );
    histnames.push_back("h_pup_Subjet0Tau21"                                     );
    histnames.push_back("h_pup_Subjet0Tau21_JetTag_b"                            );
    histnames.push_back("h_pup_Subjet0Tau21_JetTag_mass"                         );
    histnames.push_back("h_pup_Subjet0Tau21_JetTag_b_mass"                       );
    histnames.push_back("h_pup_Subjet0Tau21_OppositeJetTag_t_b"                  );
    histnames.push_back("h_pup_Subjet0Tau21_OppositeJetTag_t_b_JetTag_b"         );
    histnames.push_back("h_pup_Subjet0Tau21_OppositeJetTag_t_b_JetTag_b_mass"    );
    histnames.push_back("h_pup_Subjet0Tau21_OppositeJetTag_t_b_JetTag_b_t"       );
    histnames.push_back("h_pup_MaxSubjetb"                                       );
    histnames.push_back("h_pup_MaxSubjetb_JetTag_b"                              );
    histnames.push_back("h_pup_MaxSubjetb_JetTag_mass"                           );
    histnames.push_back("h_pup_MaxSubjetb_JetTag_b_mass"                         );
    histnames.push_back("h_pup_MaxSubjetb_OppositeJetTag_t_b"                    );
    histnames.push_back("h_pup_MaxSubjetb_OppositeJetTag_t_b_JetTag_b"           );
    histnames.push_back("h_pup_MaxSubjetb_OppositeJetTag_t_b_JetTag_b_mass"      );
    histnames.push_back("h_pup_MaxSubjetb_OppositeJetTag_t_b_JetTag_t"           );
    histnames.push_back("h_pup_MaxSubjetb_OppositeJetTag_t_b_JetTag_b_t"         );
    histnames.push_back("h_pup_MinSubjetb"                                       );
    histnames.push_back("h_pup_MinSubjetb_JetTag_b"                              );
    histnames.push_back("h_pup_MinSubjetb_JetTag_mass"                           );
    histnames.push_back("h_pup_MinSubjetb_JetTag_b_mass"                         );
    histnames.push_back("h_pup_MinSubjetb_OppositeJetTag_t_b"                    );
    histnames.push_back("h_pup_MinSubjetb_OppositeJetTag_t_b_JetTag_b"           );
    histnames.push_back("h_pup_MinSubjetb_OppositeJetTag_t_b_JetTag_b_mass"      );
    histnames.push_back("h_pup_MinSubjetb_OppositeJetTag_t_b_JetTag_t"           );
    histnames.push_back("h_pup_MinSubjetb_OppositeJetTag_t_b_JetTag_b_t"         );

    histnames.push_back("h_2ttag_inclu_dRapIn_DijetMass"                         );
    histnames.push_back("h_2ttag_0btag_dRapIn_DijetMass"                         );
    histnames.push_back("h_2ttag_1btag_dRapIn_DijetMass"                         );
    histnames.push_back("h_2ttag_2btag_dRapIn_DijetMass"                         );
    histnames.push_back("h_2ttag_inclu_dRapLo_DijetMass"                         );
    histnames.push_back("h_2ttag_0btag_dRapLo_DijetMass"                         );
    histnames.push_back("h_2ttag_1btag_dRapLo_DijetMass"                         );
    histnames.push_back("h_2ttag_2btag_dRapLo_DijetMass"                         );
    histnames.push_back("h_2ttag_inclu_dRapHi_DijetMass"                         );
    histnames.push_back("h_2ttag_0btag_dRapHi_DijetMass"                         );
    histnames.push_back("h_2ttag_1btag_dRapHi_DijetMass"                         );
    histnames.push_back("h_2ttag_2btag_dRapHi_DijetMass"                         );
    histnames.push_back("h_2ttag_inclu_dRapIn_DijetMassPlusNeighbor"             );
    histnames.push_back("h_2ttag_0btag_dRapIn_DijetMassPlusNeighbor"             );
    histnames.push_back("h_2ttag_1btag_dRapIn_DijetMassPlusNeighbor"             );
    histnames.push_back("h_2ttag_2btag_dRapIn_DijetMassPlusNeighbor"             );
    histnames.push_back("h_2ttag_inclu_dRapLo_DijetMassPlusNeighbor"             );
    histnames.push_back("h_2ttag_0btag_dRapLo_DijetMassPlusNeighbor"             );
    histnames.push_back("h_2ttag_1btag_dRapLo_DijetMassPlusNeighbor"             );
    histnames.push_back("h_2ttag_2btag_dRapLo_DijetMassPlusNeighbor"             );
    histnames.push_back("h_2ttag_inclu_dRapHi_DijetMassPlusNeighbor"             );
    histnames.push_back("h_2ttag_0btag_dRapHi_DijetMassPlusNeighbor"             );
    histnames.push_back("h_2ttag_1btag_dRapHi_DijetMassPlusNeighbor"             );
    histnames.push_back("h_2ttag_2btag_dRapHi_DijetMassPlusNeighbor"             );

    histnames.push_back("h_2ttag_inclu_DeltaRap"                                       );
    histnames.push_back("h_2ttag_0btag_DeltaRap"                                       );
    histnames.push_back("h_2ttag_1btag_DeltaRap"                                       );
    histnames.push_back("h_2ttag_2btag_DeltaRap"                                       );
    histnames.push_back("h_2ttag_inclu_DeltaRap_mTTgt1"                                );    
    histnames.push_back("h_2ttag_inclu_DeltaRap_mTTgt2"                                );    
    histnames.push_back("h_2ttag_inclu_DeltaRap_mTTgt3"                                );    
    histnames.push_back("h_2ttag_0btag_DeltaRap_mTTgt1"                                );    
    histnames.push_back("h_2ttag_0btag_DeltaRap_mTTgt2"                                );    
    histnames.push_back("h_2ttag_0btag_DeltaRap_mTTgt3"                                );    
    histnames.push_back("h_2ttag_1btag_DeltaRap_mTTgt1"                                );    
    histnames.push_back("h_2ttag_1btag_DeltaRap_mTTgt2"                                );    
    histnames.push_back("h_2ttag_1btag_DeltaRap_mTTgt3"                                );    
    histnames.push_back("h_2ttag_2btag_DeltaRap_mTTgt1"                                );    
    histnames.push_back("h_2ttag_2btag_DeltaRap_mTTgt2"                                );    
    histnames.push_back("h_2ttag_2btag_DeltaRap_mTTgt3"                                );    


    histnames.push_back("h_2ttag_inclu_DeltaPhi"                                       );
    histnames.push_back("h_2ttag_0btag_DeltaPhi"                                       );
    histnames.push_back("h_2ttag_1btag_DeltaPhi"                                       );
    histnames.push_back("h_2ttag_2btag_DeltaPhi"                                       );
    histnames.push_back("h_2ttag_inclu_HT"                                             );
    histnames.push_back("h_2ttag_0btag_HT"                                             );
    histnames.push_back("h_2ttag_1btag_HT"                                             );
    histnames.push_back("h_2ttag_2btag_HT"                                             );
    histnames.push_back("h_2ttag_inclu_MET"                                            );
    histnames.push_back("h_2ttag_0btag_MET"                                            );
    histnames.push_back("h_2ttag_1btag_MET"                                            );
    histnames.push_back("h_2ttag_2btag_MET"                                            );
    histnames.push_back("h_2ttag_inclu_METphi"                                         );
    histnames.push_back("h_2ttag_0btag_METphi"                                         );
    histnames.push_back("h_2ttag_1btag_METphi"                                         );
    histnames.push_back("h_2ttag_2btag_METphi"                                         );
    histnames.push_back("h_2ttag_inclu_Nvtx"                                           );
    histnames.push_back("h_2ttag_0btag_Nvtx"                                           );
    histnames.push_back("h_2ttag_1btag_Nvtx"                                           );
    histnames.push_back("h_2ttag_2btag_Nvtx"                                           );
    histnames.push_back("h_2ttag_inclu_Jet0P"                                          );
    histnames.push_back("h_2ttag_inclu_Jet0Pt"                                         );
    histnames.push_back("h_2ttag_inclu_Jet0Phi"                                        );
    histnames.push_back("h_2ttag_inclu_Jet0Rap"                                        );
    histnames.push_back("h_2ttag_inclu_Jet0SDmass"                                     );
    histnames.push_back("h_2ttag_inclu_Jet0SDmassCorrL23"                              );
    histnames.push_back("h_2ttag_inclu_Jet0SDmassCorrL23Up"                            );
    histnames.push_back("h_2ttag_inclu_Jet0Tau1"                                       );
    histnames.push_back("h_2ttag_inclu_Jet0Tau2"                                       );
    histnames.push_back("h_2ttag_inclu_Jet0Tau3"                                       );
    histnames.push_back("h_2ttag_inclu_Jet0Tau4"                                       );
    histnames.push_back("h_2ttag_inclu_Jet0SDmaxbdisc"                                 );
    histnames.push_back("h_2ttag_inclu_Jet0SDsubjet0pt"                                );
    histnames.push_back("h_2ttag_inclu_Jet0SDsubjet0mass"                              );
    histnames.push_back("h_2ttag_inclu_Jet0SDsubjet0tau1"                              );
    histnames.push_back("h_2ttag_inclu_Jet0SDsubjet0tau2"                              );
    histnames.push_back("h_2ttag_inclu_Jet0SDsubjet0tau3"                              );
    histnames.push_back("h_2ttag_inclu_Jet0SDsubjet0bdisc"                             );
    histnames.push_back("h_2ttag_inclu_Jet0SDsubjet1pt"                                );
    histnames.push_back("h_2ttag_inclu_Jet0SDsubjet1mass"                              );
    histnames.push_back("h_2ttag_inclu_Jet0SDsubjet1tau1"                              );
    histnames.push_back("h_2ttag_inclu_Jet0SDsubjet1tau2"                              );
    histnames.push_back("h_2ttag_inclu_Jet0SDsubjet1tau3"                              );
    histnames.push_back("h_2ttag_inclu_Jet0SDsubjet1bdisc"                             );
    
    histnames.push_back("h_2ttag_inclu_Jet0PuppiPt"                                    );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiSDmass"                                );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiSDpt"                                  );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiTau1"                                  );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiTau2"                                  );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiTau3"                                  );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiTau4"                                  );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiTau32"                                 );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiSDmaxbdisc"                            );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet0pt"                           );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet0mass"                         );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet0tau1"                         );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet0tau2"                         );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet0tau3"                         );
    // histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet0tau21"                         );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet0bdisc"                        );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet1pt"                           );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet1mass"                         );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet1tau1"                         );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet1tau2"                         );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet1tau3"                         );
    // histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet1tau21"                         );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet1bdisc"                        );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiCHF"                                   );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiNHF"                                   );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiCM"                                    );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiNM"                                    );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiNEF"                                   );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiCEF"                                   );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiMF"                                    );
    histnames.push_back("h_2ttag_inclu_Jet0PuppiMult"                                  );
    
    histnames.push_back("h_2ttag_inclu_Jet1PuppiPt"                                    );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiSDmass"                                );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiSDpt"                                  );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiTau1"                                  );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiTau2"                                  );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiTau3"                                  );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiTau4"                                  );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiTau32"                                 );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiSDmaxbdisc"                            );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiSDsubjet0pt"                           );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiSDsubjet0mass"                         );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiSDsubjet0tau1"                         );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiSDsubjet0tau2"                         );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiSDsubjet0tau3"                         );
    // histnames.push_back("h_2ttag_inclu_Jet1PuppiSDsubjet0tau21"                         );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiSDsubjet0bdisc"                        );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiSDsubjet1pt"                           );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiSDsubjet1mass"                         );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiSDsubjet1tau1"                         );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiSDsubjet1tau2"                         );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiSDsubjet1tau3"                         );
    // histnames.push_back("h_2ttag_inclu_Jet1PuppiSDsubjet1tau21"                         );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiSDsubjet1bdisc"                        );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiCHF"                                   );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiNHF"                                   );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiCM"                                    );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiNM"                                    );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiNEF"                                   );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiCEF"                                   );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiMF"                                    );
    histnames.push_back("h_2ttag_inclu_Jet1PuppiMult"                                  );
    

    histnames.push_back("h_2ttag_inclu_Jet0CHF"                                        );
    histnames.push_back("h_2ttag_inclu_Jet0NHF"                                        );
    histnames.push_back("h_2ttag_inclu_Jet0CM"                                         );
    histnames.push_back("h_2ttag_inclu_Jet0NM"                                         );
    histnames.push_back("h_2ttag_inclu_Jet0NEF"                                        );
    histnames.push_back("h_2ttag_inclu_Jet0CEF"                                        );
    histnames.push_back("h_2ttag_inclu_Jet0MF"                                         );
    histnames.push_back("h_2ttag_inclu_Jet0Mult"                                       );
    histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet0pt"                           );
    histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet0mass"                         );
    histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet0tau1"                         );
    histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet0tau2"                         );
    histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet0tau3"                         );
    // histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet0tau21"                         );
    histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet0bdisc"                        );
    histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet1pt"                           );
    histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet1mass"                         );
    histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet1tau1"                         );
    histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet1tau2"                         );
    histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet1tau3"                         );
    // histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet1tau21"                         );
    histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet1bdisc"                        );
    histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet0pt"                           );
    histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet0mass"                         );
    histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet0tau1"                         );
    histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet0tau2"                         );
    histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet0tau3"                         );
    // histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet0tau21"                         );
    histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet0bdisc"                        );
    histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet1pt"                           );
    histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet1mass"                         );
    histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet1tau1"                         );
    histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet1tau2"                         );
    histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet1tau3"                         );
    // histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet1tau21"                         );
    histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet1bdisc"                        );
    histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet0pt"                           );
    histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet0mass"                         );
    histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet0tau1"                         );
    histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet0tau2"                         );
    histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet0tau3"                         );
    // histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet0tau21"                         );
    histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet0bdisc"                        );
    histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet1pt"                           );
    histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet1mass"                         );
    histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet1tau1"                         );
    histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet1tau2"                         );
    histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet1tau3"                         );
    // histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet1tau21"                         );
    histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet1bdisc"                        );
    histnames.push_back("h_2btag_DijetMass"                                             );
    histnames.push_back("h_2btag_DeltaRap"                                              );
    histnames.push_back("h_2btag_jet0massSD"                                            );
    histnames.push_back("h_2btag_jet0massSDpuppi"                                            );
    histnames.push_back("h_2btag_jet0tau32"                                             );
    histnames.push_back("h_2btag_jet0tau21"                                             );
    histnames.push_back("h_2btag_jet0tau1"                                              );
    histnames.push_back("h_2btag_jet0tau2"                                              );
    histnames.push_back("h_2btag_jet0tau3"                                              );
    histnames.push_back("h_2btag_jet0subjet0mass"                                       );
    histnames.push_back("h_2btag_jet0subjet1mass"                                       );
    // histnames.push_back("h_2btag_jet0subjet0mass_jet0subjet1mass"                       );
    // histnames.push_back("h_2btag_jet0subjet0bdisc_jet0subjet1bdisc"                     );
    histnames.push_back("h_2btag_jet1massSD"                                            );
    histnames.push_back("h_2btag_jet1massSDpuppi"                                            );
    histnames.push_back("h_2btag_jet1tau32"                                             );
    histnames.push_back("h_2btag_jet1tau21"                                             );
    histnames.push_back("h_2btag_jet1tau1"                                              );
    histnames.push_back("h_2btag_jet1tau2"                                              );
    histnames.push_back("h_2btag_jet1tau3"                                              );
    histnames.push_back("h_2btag_jet1subjet0mass"                                       );
    histnames.push_back("h_2btag_jet1subjet1mass"                                       );
    // histnames.push_back("h_2btag_jet1subjet0mass_jet1subjet1mass"                       );
    // histnames.push_back("h_2btag_jet1subjet0bdisc_jet1subjet1bdisc"                     );
    histnames.push_back("h_2btag_jet1ttag_jet0massSD"                                   );
    histnames.push_back("h_2btag_jet1ttag_jet0tau32"                                    );
    histnames.push_back("h_2btag_jet1ttag_jet0tau21"                                    );
    histnames.push_back("h_2btag_jet1ttag_jet0tau1"                                     );
    histnames.push_back("h_2btag_jet1ttag_jet0tau2"                                     );
    histnames.push_back("h_2btag_jet1ttag_jet0tau3"                                     );
    histnames.push_back("h_2btag_jet1ttag_jet0subjet0mass"                              );
    histnames.push_back("h_2btag_jet1ttag_jet0subjet1mass"                              );
    // histnames.push_back("h_2btag_jet1ttag_jet0subjet0mass_jet0subjet1mass"              );
    // histnames.push_back("h_2btag_jet1ttag_jet0subjet0bdisc_jet0subjet1bdisc"            );
    histnames.push_back("h_2btag_jet0ttag_jet1massSD"                                   );
    histnames.push_back("h_2btag_jet0ttag_jet1tau32"                                    );
    histnames.push_back("h_2btag_jet0ttag_jet1tau21"                                    );
    histnames.push_back("h_2btag_jet0ttag_jet1tau1"                                     );
    histnames.push_back("h_2btag_jet0ttag_jet1tau2"                                     );
    histnames.push_back("h_2btag_jet0ttag_jet1tau3"                                     );
    histnames.push_back("h_2btag_jet0ttag_jet1subjet0mass"                              );
    histnames.push_back("h_2btag_jet0ttag_jet1subjet1mass"                              );
    // histnames.push_back("h_2btag_jet0ttag_jet1subjet0mass_jet1subjet1mass"              );
    // histnames.push_back("h_2btag_jet0ttag_jet1subjet0bdisc_jet1subjet1bdisc"            );
    histnames.push_back("h_2btag_jet1ttag_jet0tautag_jet0massSD"                        );
    histnames.push_back("h_2btag_jet1ttag_jet0masstag_jet0tau32"                        );
    histnames.push_back("h_2btag_jet1ttag_jet0masstag_jet0tau21"                        );
    histnames.push_back("h_2btag_jet1ttag_jet0masstag_jet0tau1"                         );
    histnames.push_back("h_2btag_jet1ttag_jet0masstag_jet0tau2"                         );
    histnames.push_back("h_2btag_jet1ttag_jet0masstag_jet0tau3"                         );
    histnames.push_back("h_2btag_jet0ttag_jet1tautag_jet1massSD"                        );
    histnames.push_back("h_2btag_jet0ttag_jet1masstag_jet1tau32"                        );
    histnames.push_back("h_2btag_jet0ttag_jet1masstag_jet1tau21"                        );
    histnames.push_back("h_2btag_jet0ttag_jet1masstag_jet1tau1"                         );
    histnames.push_back("h_2btag_jet0ttag_jet1masstag_jet1tau2"                         );
    histnames.push_back("h_2btag_jet0ttag_jet1masstag_jet1tau3"                         );
    histnames.push_back("h_topTag_jet0subjet0pt"                                       );
    histnames.push_back("h_topTag_jet0subjet1pt"                                       );
    histnames.push_back("h_topTag_jet0pt"                                              );
    // histnames.push_back("h_topTag_jet0pt_jet0subjet0pt"                                );
    // histnames.push_back("h_topTag_jet0pt_jet0subjet1pt"                                );
    // histnames.push_back("h_topTag_jet0subjet0pt_jet0subjet1pt"                         );
    // histnames.push_back("h_topTag_jet0subjet0mass_jet0subjet1mass"                     );
    // histnames.push_back("h_topTag_jet0subjet0bdisc_jet0subjet1bdisc"                   );
    // histnames.push_back("h_topTag_jet0subjet0flav_jet0subjet1flav"                     );
    // histnames.push_back("h_topTag_jet0subjet0mass"                                     );
    // histnames.push_back("h_topTag_jet0subjet1mass"                                     );
    // histnames.push_back("h_topTag_jet0subjet0bdisc"                                    );
    // histnames.push_back("h_topTag_jet0subjet1bdisc"                                    );
    // histnames.push_back("h_topTag_jet0subjet0flav"                                     );
    // histnames.push_back("h_topTag_jet0subjet1flav"                                     );
    // histnames.push_back("h_topTag_jet0maxBdisc"                                        );
    // histnames.push_back("h_topTag_jet0maxBdiscflav"                                    );
    // histnames.push_back("h_topTagbTag_jet0subjet0pt"                                   );
    // histnames.push_back("h_topTagbTag_jet0subjet1pt"                                   );
    // histnames.push_back("h_topTagbTag_jet0pt"                                          );
    // // histnames.push_back("h_topTagbTag_jet0pt_jet0subjet0pt"                            );
    // // histnames.push_back("h_topTagbTag_jet0pt_jet0subjet1pt"                            );
    // // histnames.push_back("h_topTagbTag_jet0subjet0pt_jet0subjet1pt"                     );
    // // histnames.push_back("h_topTagbTag_jet0subjet0mass_jet0subjet1mass"                 );
    // // histnames.push_back("h_topTagbTag_jet0subjet0bdisc_jet0subjet1bdisc"               );
    // // histnames.push_back("h_topTagbTag_jet0subjet0flav_jet0subjet1flav"                 );
    // histnames.push_back("h_topTagbTag_jet0subjet0mass"                                 );
    // histnames.push_back("h_topTagbTag_jet0subjet1mass"                                 );
    // histnames.push_back("h_topTagbTag_jet0subjet0bdisc"                                );
    // histnames.push_back("h_topTagbTag_jet0subjet1bdisc"                                );
    // histnames.push_back("h_topTagbTag_jet0subjet0flav"                                 );
    // histnames.push_back("h_topTagbTag_jet0subjet1flav"                                 );
    // histnames.push_back("h_topTagbTag_jet0maxBdisc"                                    );
    // histnames.push_back("h_topTagbTag_jet0maxBdiscflav"                                );


  }

  // Antitag plots
  if (j==1){
    histnames.push_back("h_AntiTagCHS_Probe_jetP_dRapIn_inclusive"                        );  
    histnames.push_back("h_AntiTagCHS_Probe_jetP_dRapIn_0btag"                            );  
    histnames.push_back("h_AntiTagCHS_Probe_jetP_dRapIn_1btag"                            );  
    histnames.push_back("h_AntiTagCHS_Probe_jetP_dRapIn_2btag"                            );  
    histnames.push_back("h_AntiTagCHS_Probe_jetP_dRapHi_inclusive"                        );  
    histnames.push_back("h_AntiTagCHS_Probe_jetP_dRapHi_0btag"                            );  
    histnames.push_back("h_AntiTagCHS_Probe_jetP_dRapHi_1btag"                            );  
    histnames.push_back("h_AntiTagCHS_Probe_jetP_dRapHi_2btag"                            );  
    histnames.push_back("h_AntiTagCHS_Probe_jetP_dRapLo_inclusive"                        );  
    histnames.push_back("h_AntiTagCHS_Probe_jetP_dRapLo_0btag"                            );  
    histnames.push_back("h_AntiTagCHS_Probe_jetP_dRapLo_1btag"                            );  
    histnames.push_back("h_AntiTagCHS_Probe_jetP_dRapLo_2btag"                            );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclusive"               );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag"                   );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag"                   );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag"                   );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclusive"               );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag"                   );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag"                   );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag"                   );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclusive"               );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag"                   );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag"                   );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag"                   );  
    histnames.push_back("h_AntiTagPuppi_Probe_jetP_dRapIn_inclusive"                      );  
    histnames.push_back("h_AntiTagPuppi_Probe_jetP_dRapIn_0btag"                          );  
    histnames.push_back("h_AntiTagPuppi_Probe_jetP_dRapIn_1btag"                          );  
    histnames.push_back("h_AntiTagPuppi_Probe_jetP_dRapIn_2btag"                          );  
    histnames.push_back("h_AntiTagPuppi_Probe_jetP_dRapHi_inclusive"                      );  
    histnames.push_back("h_AntiTagPuppi_Probe_jetP_dRapHi_0btag"                          );  
    histnames.push_back("h_AntiTagPuppi_Probe_jetP_dRapHi_1btag"                          );  
    histnames.push_back("h_AntiTagPuppi_Probe_jetP_dRapHi_2btag"                          );  
    histnames.push_back("h_AntiTagPuppi_Probe_jetP_dRapLo_inclusive"                      );  
    histnames.push_back("h_AntiTagPuppi_Probe_jetP_dRapLo_0btag"                          );  
    histnames.push_back("h_AntiTagPuppi_Probe_jetP_dRapLo_1btag"                          );  
    histnames.push_back("h_AntiTagPuppi_Probe_jetP_dRapLo_2btag"                          );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_inclusive"             );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_0btag"                 );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_1btag"                 );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_2btag"                 );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_inclusive"             );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_0btag"                 );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_1btag"                 );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_2btag"                 );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_inclusive"             );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_0btag"                 );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_1btag"                 );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_2btag"                 ); 

    histnames.push_back("h_AntiTagPuppi_TagMassSD_jetP_dRapIn_inclusive"                  );         
    histnames.push_back("h_AntiTagPuppi_TagMassSD_jetP_dRapIn_0btag"                      );         
    histnames.push_back("h_AntiTagPuppi_TagMassSD_jetP_dRapIn_1btag"                      );         
    histnames.push_back("h_AntiTagPuppi_TagMassSD_jetP_dRapIn_2btag"                      );         
    histnames.push_back("h_AntiTagPuppi_TagTau32_jetP_dRapIn_inclusive"                   );         
    histnames.push_back("h_AntiTagPuppi_TagTau32_jetP_dRapIn_0btag"                       );         
    histnames.push_back("h_AntiTagPuppi_TagTau32_jetP_dRapIn_1btag"                       );         
    histnames.push_back("h_AntiTagPuppi_TagTau32_jetP_dRapIn_2btag"                       );         

    histnames.push_back("h_alt_AntiTagCHS_Probe_jetP_dRapIn_inclusive"                    );  
    histnames.push_back("h_alt_AntiTagCHS_Probe_jetP_dRapIn_0btag"                        );  
    histnames.push_back("h_alt_AntiTagCHS_Probe_jetP_dRapIn_1btag"                        );  
    histnames.push_back("h_alt_AntiTagCHS_Probe_jetP_dRapIn_2btag"                        );  
    histnames.push_back("h_alt_AntiTagCHS_Probe_jetP_dRapHi_inclusive"                    );  
    histnames.push_back("h_alt_AntiTagCHS_Probe_jetP_dRapHi_0btag"                        );  
    histnames.push_back("h_alt_AntiTagCHS_Probe_jetP_dRapHi_1btag"                        );  
    histnames.push_back("h_alt_AntiTagCHS_Probe_jetP_dRapHi_2btag"                        );  
    histnames.push_back("h_alt_AntiTagCHS_Probe_jetP_dRapLo_inclusive"                    );  
    histnames.push_back("h_alt_AntiTagCHS_Probe_jetP_dRapLo_0btag"                        );  
    histnames.push_back("h_alt_AntiTagCHS_Probe_jetP_dRapLo_1btag"                        );  
    histnames.push_back("h_alt_AntiTagCHS_Probe_jetP_dRapLo_2btag"                        );  
    histnames.push_back("h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclusive"           );  
    histnames.push_back("h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag"               );  
    histnames.push_back("h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag"               );  
    histnames.push_back("h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag"               );  
    histnames.push_back("h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclusive"           );  
    histnames.push_back("h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag"               );  
    histnames.push_back("h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag"               );  
    histnames.push_back("h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag"               );  
    histnames.push_back("h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclusive"           );  
    histnames.push_back("h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag"               );  
    histnames.push_back("h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag"               );  
    histnames.push_back("h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag"               );  
    histnames.push_back("h_alt2_AntiTagCHS_Probe_jetP_dRapIn_inclusive"                   );  
    histnames.push_back("h_alt2_AntiTagCHS_Probe_jetP_dRapIn_0btag"                       );  
    histnames.push_back("h_alt2_AntiTagCHS_Probe_jetP_dRapIn_1btag"                       );  
    histnames.push_back("h_alt2_AntiTagCHS_Probe_jetP_dRapIn_2btag"                       );  
    histnames.push_back("h_alt2_AntiTagCHS_Probe_jetP_dRapHi_inclusive"                   );  
    histnames.push_back("h_alt2_AntiTagCHS_Probe_jetP_dRapHi_0btag"                       );  
    histnames.push_back("h_alt2_AntiTagCHS_Probe_jetP_dRapHi_1btag"                       );  
    histnames.push_back("h_alt2_AntiTagCHS_Probe_jetP_dRapHi_2btag"                       );  
    histnames.push_back("h_alt2_AntiTagCHS_Probe_jetP_dRapLo_inclusive"                   );  
    histnames.push_back("h_alt2_AntiTagCHS_Probe_jetP_dRapLo_0btag"                       );  
    histnames.push_back("h_alt2_AntiTagCHS_Probe_jetP_dRapLo_1btag"                       );  
    histnames.push_back("h_alt2_AntiTagCHS_Probe_jetP_dRapLo_2btag"                       );  
    histnames.push_back("h_alt2_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclusive"          );  
    histnames.push_back("h_alt2_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag"              );  
    histnames.push_back("h_alt2_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag"              );  
    histnames.push_back("h_alt2_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag"              );  
    histnames.push_back("h_alt2_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclusive"          );  
    histnames.push_back("h_alt2_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag"              );  
    histnames.push_back("h_alt2_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag"              );  
    histnames.push_back("h_alt2_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag"              );  
    histnames.push_back("h_alt2_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclusive"          );  
    histnames.push_back("h_alt2_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag"              );  
    histnames.push_back("h_alt2_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag"              );  
    histnames.push_back("h_alt2_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag"              );  
    histnames.push_back("h_alt_AntiTagPuppi_Probe_jetP_dRapIn_inclusive"                  );  
    histnames.push_back("h_alt_AntiTagPuppi_Probe_jetP_dRapIn_0btag"                      );  
    histnames.push_back("h_alt_AntiTagPuppi_Probe_jetP_dRapIn_1btag"                      );  
    histnames.push_back("h_alt_AntiTagPuppi_Probe_jetP_dRapIn_2btag"                      );  
    histnames.push_back("h_alt_AntiTagPuppi_Probe_jetP_dRapHi_inclusive"                  );  
    histnames.push_back("h_alt_AntiTagPuppi_Probe_jetP_dRapHi_0btag"                      );  
    histnames.push_back("h_alt_AntiTagPuppi_Probe_jetP_dRapHi_1btag"                      );  
    histnames.push_back("h_alt_AntiTagPuppi_Probe_jetP_dRapHi_2btag"                      );  
    histnames.push_back("h_alt_AntiTagPuppi_Probe_jetP_dRapLo_inclusive"                  );  
    histnames.push_back("h_alt_AntiTagPuppi_Probe_jetP_dRapLo_0btag"                      );  
    histnames.push_back("h_alt_AntiTagPuppi_Probe_jetP_dRapLo_1btag"                      );  
    histnames.push_back("h_alt_AntiTagPuppi_Probe_jetP_dRapLo_2btag"                      );  
    histnames.push_back("h_alt_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_inclusive"         );  
    histnames.push_back("h_alt_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_0btag"             );  
    histnames.push_back("h_alt_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_1btag"             );  
    histnames.push_back("h_alt_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_2btag"             );  
    histnames.push_back("h_alt_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_inclusive"         );  
    histnames.push_back("h_alt_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_0btag"             );  
    histnames.push_back("h_alt_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_1btag"             );  
    histnames.push_back("h_alt_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_2btag"             );  
    histnames.push_back("h_alt_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_inclusive"         );  
    histnames.push_back("h_alt_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_0btag"             );  
    histnames.push_back("h_alt_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_1btag"             );  
    histnames.push_back("h_alt_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_2btag"             );  
    histnames.push_back("h_alt2_AntiTagPuppi_Probe_jetP_dRapIn_inclusive"                 );  
    histnames.push_back("h_alt2_AntiTagPuppi_Probe_jetP_dRapIn_0btag"                     );  
    histnames.push_back("h_alt2_AntiTagPuppi_Probe_jetP_dRapIn_1btag"                     );  
    histnames.push_back("h_alt2_AntiTagPuppi_Probe_jetP_dRapIn_2btag"                     );  
    histnames.push_back("h_alt2_AntiTagPuppi_Probe_jetP_dRapHi_inclusive"                 );  
    histnames.push_back("h_alt2_AntiTagPuppi_Probe_jetP_dRapHi_0btag"                     );  
    histnames.push_back("h_alt2_AntiTagPuppi_Probe_jetP_dRapHi_1btag"                     );  
    histnames.push_back("h_alt2_AntiTagPuppi_Probe_jetP_dRapHi_2btag"                     );  
    histnames.push_back("h_alt2_AntiTagPuppi_Probe_jetP_dRapLo_inclusive"                 );  
    histnames.push_back("h_alt2_AntiTagPuppi_Probe_jetP_dRapLo_0btag"                     );  
    histnames.push_back("h_alt2_AntiTagPuppi_Probe_jetP_dRapLo_1btag"                     );  
    histnames.push_back("h_alt2_AntiTagPuppi_Probe_jetP_dRapLo_2btag"                     );  
    histnames.push_back("h_alt2_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_inclusive"        );  
    histnames.push_back("h_alt2_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_0btag"            );  
    histnames.push_back("h_alt2_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_1btag"            );  
    histnames.push_back("h_alt2_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_2btag"            );  
    histnames.push_back("h_alt2_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_inclusive"        );  
    histnames.push_back("h_alt2_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_0btag"            );  
    histnames.push_back("h_alt2_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_1btag"            );  
    histnames.push_back("h_alt2_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_2btag"            );  
    histnames.push_back("h_alt2_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_inclusive"        );  
    histnames.push_back("h_alt2_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_0btag"            );  
    histnames.push_back("h_alt2_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_1btag"            );  
    histnames.push_back("h_alt2_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_2btag"            );  
    histnames.push_back("h_AntiTagCHS40to60_Probe_jetP_dRapIn_inclusive"                  );  
    histnames.push_back("h_AntiTagCHS60to80_Probe_jetP_dRapIn_inclusive"                  );  
    histnames.push_back("h_AntiTagCHS80to110_Probe_jetP_dRapIn_inclusive"                 );  
    histnames.push_back("h_AntiTagCHS100to120_Probe_jetP_dRapIn_inclusive"                );  
    histnames.push_back("h_AntiTagCHS120to140_Probe_jetP_dRapIn_inclusive"                );  
    histnames.push_back("h_AntiTagCHS140to180_Probe_jetP_dRapIn_inclusive"                );  
    histnames.push_back("h_AntiTagCHS180to220_Probe_jetP_dRapIn_inclusive"                );  
    histnames.push_back("h_AntiTagCHS220to300_Probe_jetP_dRapIn_inclusive"                );  
    histnames.push_back("h_AntiTagCHS40to60_TagMassSDTau32_jetP_dRapIn_inclusive"         );  
    histnames.push_back("h_AntiTagCHS60to80_TagMassSDTau32_jetP_dRapIn_inclusive"         );  
    histnames.push_back("h_AntiTagCHS80to110_TagMassSDTau32_jetP_dRapIn_inclusive"        );  
    histnames.push_back("h_AntiTagCHS100to120_TagMassSDTau32_jetP_dRapIn_inclusive"       );  
    histnames.push_back("h_AntiTagCHS120to140_TagMassSDTau32_jetP_dRapIn_inclusive"       );  
    histnames.push_back("h_AntiTagCHS140to180_TagMassSDTau32_jetP_dRapIn_inclusive"       );  
    histnames.push_back("h_AntiTagCHS180to220_TagMassSDTau32_jetP_dRapIn_inclusive"       );  
    histnames.push_back("h_AntiTagCHS220to300_TagMassSDTau32_jetP_dRapIn_inclusive"       );  

    histnames.push_back("h_AntiTagCHS_Probe_Nvtx_dRapIn_inclusive"                        );  
    histnames.push_back("h_AntiTagCHS_Probe_Nvtx_dRapIn_0btag"                            );  
    histnames.push_back("h_AntiTagCHS_Probe_Nvtx_dRapIn_1btag"                            );  
    histnames.push_back("h_AntiTagCHS_Probe_Nvtx_dRapIn_2btag"                            );  
    histnames.push_back("h_AntiTagCHS_Probe_Nvtx_dRapHi_inclusive"                        );  
    histnames.push_back("h_AntiTagCHS_Probe_Nvtx_dRapHi_0btag"                            );  
    histnames.push_back("h_AntiTagCHS_Probe_Nvtx_dRapHi_1btag"                            );  
    histnames.push_back("h_AntiTagCHS_Probe_Nvtx_dRapHi_2btag"                            );  
    histnames.push_back("h_AntiTagCHS_Probe_Nvtx_dRapLo_inclusive"                        );  
    histnames.push_back("h_AntiTagCHS_Probe_Nvtx_dRapLo_0btag"                            );  
    histnames.push_back("h_AntiTagCHS_Probe_Nvtx_dRapLo_1btag"                            );  
    histnames.push_back("h_AntiTagCHS_Probe_Nvtx_dRapLo_2btag"                            );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_Nvtx_dRapIn_inclusive"               );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_Nvtx_dRapIn_0btag"                   );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_Nvtx_dRapIn_1btag"                   );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_Nvtx_dRapIn_2btag"                   );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_Nvtx_dRapHi_inclusive"               );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_Nvtx_dRapHi_0btag"                   );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_Nvtx_dRapHi_1btag"                   );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_Nvtx_dRapHi_2btag"                   );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_Nvtx_dRapLo_inclusive"               );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_Nvtx_dRapLo_0btag"                   );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_Nvtx_dRapLo_1btag"                   );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_Nvtx_dRapLo_2btag"                   );  
    histnames.push_back("h_AntiTagPuppi_Probe_Nvtx_dRapIn_inclusive"                      );  
    histnames.push_back("h_AntiTagPuppi_Probe_Nvtx_dRapIn_0btag"                          );  
    histnames.push_back("h_AntiTagPuppi_Probe_Nvtx_dRapIn_1btag"                          );  
    histnames.push_back("h_AntiTagPuppi_Probe_Nvtx_dRapIn_2btag"                          );  
    histnames.push_back("h_AntiTagPuppi_Probe_Nvtx_dRapHi_inclusive"                      );  
    histnames.push_back("h_AntiTagPuppi_Probe_Nvtx_dRapHi_0btag"                          );  
    histnames.push_back("h_AntiTagPuppi_Probe_Nvtx_dRapHi_1btag"                          );  
    histnames.push_back("h_AntiTagPuppi_Probe_Nvtx_dRapHi_2btag"                          );  
    histnames.push_back("h_AntiTagPuppi_Probe_Nvtx_dRapLo_inclusive"                      );  
    histnames.push_back("h_AntiTagPuppi_Probe_Nvtx_dRapLo_0btag"                          );  
    histnames.push_back("h_AntiTagPuppi_Probe_Nvtx_dRapLo_1btag"                          );  
    histnames.push_back("h_AntiTagPuppi_Probe_Nvtx_dRapLo_2btag"                          );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_Nvtx_dRapIn_inclusive"             );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_Nvtx_dRapIn_0btag"                 );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_Nvtx_dRapIn_1btag"                 );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_Nvtx_dRapIn_2btag"                 );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_Nvtx_dRapHi_inclusive"             );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_Nvtx_dRapHi_0btag"                 );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_Nvtx_dRapHi_1btag"                 );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_Nvtx_dRapHi_2btag"                 );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_Nvtx_dRapLo_inclusive"             );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_Nvtx_dRapLo_0btag"                 );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_Nvtx_dRapLo_1btag"                 );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_Nvtx_dRapLo_2btag"                 );  
    histnames.push_back("h_AntiTagPuppi_TagMassSD_Nvtx_dRapIn_inclusive"                  );      
    histnames.push_back("h_AntiTagPuppi_TagMassSD_Nvtx_dRapIn_0btag"                      );      
    histnames.push_back("h_AntiTagPuppi_TagMassSD_Nvtx_dRapIn_1btag"                      );      
    histnames.push_back("h_AntiTagPuppi_TagMassSD_Nvtx_dRapIn_2btag"                      );      
    histnames.push_back("h_AntiTagPuppi_TagTau32_Nvtx_dRapIn_inclusive"                   );      
    histnames.push_back("h_AntiTagPuppi_TagTau32_Nvtx_dRapIn_0btag"                       );      
    histnames.push_back("h_AntiTagPuppi_TagTau32_Nvtx_dRapIn_1btag"                       );      
    histnames.push_back("h_AntiTagPuppi_TagTau32_Nvtx_dRapIn_2btag"                       );      


    histnames.push_back("h_AntiTagCHS_Probe_jetY_dRapIn_inclusive"                        );  
    histnames.push_back("h_AntiTagCHS_Probe_jetY_dRapIn_0btag"                            );  
    histnames.push_back("h_AntiTagCHS_Probe_jetY_dRapIn_1btag"                            );  
    histnames.push_back("h_AntiTagCHS_Probe_jetY_dRapIn_2btag"                            );  
    histnames.push_back("h_AntiTagCHS_Probe_jetY_dRapHi_inclusive"                        );  
    histnames.push_back("h_AntiTagCHS_Probe_jetY_dRapHi_0btag"                            );  
    histnames.push_back("h_AntiTagCHS_Probe_jetY_dRapHi_1btag"                            );  
    histnames.push_back("h_AntiTagCHS_Probe_jetY_dRapHi_2btag"                            );  
    histnames.push_back("h_AntiTagCHS_Probe_jetY_dRapLo_inclusive"                        );  
    histnames.push_back("h_AntiTagCHS_Probe_jetY_dRapLo_0btag"                            );  
    histnames.push_back("h_AntiTagCHS_Probe_jetY_dRapLo_1btag"                            );  
    histnames.push_back("h_AntiTagCHS_Probe_jetY_dRapLo_2btag"                            );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_jetY_dRapIn_inclusive"               );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_jetY_dRapIn_0btag"                   );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_jetY_dRapIn_1btag"                   );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_jetY_dRapIn_2btag"                   );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_jetY_dRapHi_inclusive"               );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_jetY_dRapHi_0btag"                   );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_jetY_dRapHi_1btag"                   );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_jetY_dRapHi_2btag"                   );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_jetY_dRapLo_inclusive"               );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_jetY_dRapLo_0btag"                   );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_jetY_dRapLo_1btag"                   );  
    histnames.push_back("h_AntiTagCHS_TagMassSDTau32_jetY_dRapLo_2btag"                   );  
    histnames.push_back("h_AntiTagPuppi_Probe_jetY_dRapIn_inclusive"                      );  
    histnames.push_back("h_AntiTagPuppi_Probe_jetY_dRapIn_0btag"                          );  
    histnames.push_back("h_AntiTagPuppi_Probe_jetY_dRapIn_1btag"                          );  
    histnames.push_back("h_AntiTagPuppi_Probe_jetY_dRapIn_2btag"                          );  
    histnames.push_back("h_AntiTagPuppi_Probe_jetY_dRapHi_inclusive"                      );  
    histnames.push_back("h_AntiTagPuppi_Probe_jetY_dRapHi_0btag"                          );  
    histnames.push_back("h_AntiTagPuppi_Probe_jetY_dRapHi_1btag"                          );  
    histnames.push_back("h_AntiTagPuppi_Probe_jetY_dRapHi_2btag"                          );  
    histnames.push_back("h_AntiTagPuppi_Probe_jetY_dRapLo_inclusive"                      );  
    histnames.push_back("h_AntiTagPuppi_Probe_jetY_dRapLo_0btag"                          );  
    histnames.push_back("h_AntiTagPuppi_Probe_jetY_dRapLo_1btag"                          );  
    histnames.push_back("h_AntiTagPuppi_Probe_jetY_dRapLo_2btag"                          );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_jetY_dRapIn_inclusive"             );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_jetY_dRapIn_0btag"                 );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_jetY_dRapIn_1btag"                 );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_jetY_dRapIn_2btag"                 );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_jetY_dRapHi_inclusive"             );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_jetY_dRapHi_0btag"                 );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_jetY_dRapHi_1btag"                 );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_jetY_dRapHi_2btag"                 );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_jetY_dRapLo_inclusive"             );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_jetY_dRapLo_0btag"                 );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_jetY_dRapLo_1btag"                 );  
    histnames.push_back("h_AntiTagPuppi_TagMassSDTau32_jetY_dRapLo_2btag"                 );  

    histnames.push_back("h_AntiTagPuppi_TagMassSD_jetY_dRapIn_inclusive"                  ); 
    histnames.push_back("h_AntiTagPuppi_TagMassSD_jetY_dRapIn_0btag"                      ); 
    histnames.push_back("h_AntiTagPuppi_TagMassSD_jetY_dRapIn_1btag"                      ); 
    histnames.push_back("h_AntiTagPuppi_TagMassSD_jetY_dRapIn_2btag"                      ); 
    histnames.push_back("h_AntiTagPuppi_TagTau32_jetY_dRapIn_inclusive"                   ); 
    histnames.push_back("h_AntiTagPuppi_TagTau32_jetY_dRapIn_0btag"                       ); 
    histnames.push_back("h_AntiTagPuppi_TagTau32_jetY_dRapIn_1btag"                       ); 
    histnames.push_back("h_AntiTagPuppi_TagTau32_jetY_dRapIn_2btag"                       ); 

    // histnames.push_back("h2_AntiTagPuppi_Probe_jetP_jetY_dRapIn_inclusive"               );
    // histnames.push_back("h2_AntiTagPuppi_Probe_jetP_jetY_dRapIn_0btag"                   );
    // histnames.push_back("h2_AntiTagPuppi_Probe_jetP_jetY_dRapIn_1btag"                   );
    // histnames.push_back("h2_AntiTagPuppi_Probe_jetP_jetY_dRapIn_2btag"                   );
    // histnames.push_back("h2_AntiTagPuppi_Probe_jetP_jetY_dRapHi_inclusive"               );
    // histnames.push_back("h2_AntiTagPuppi_Probe_jetP_jetY_dRapHi_0btag"                   );
    // histnames.push_back("h2_AntiTagPuppi_Probe_jetP_jetY_dRapHi_1btag"                   );
    // histnames.push_back("h2_AntiTagPuppi_Probe_jetP_jetY_dRapHi_2btag"                   );
    // histnames.push_back("h2_AntiTagPuppi_Probe_jetP_jetY_dRapLo_inclusive"               );
    // histnames.push_back("h2_AntiTagPuppi_Probe_jetP_jetY_dRapLo_0btag"                   );
    // histnames.push_back("h2_AntiTagPuppi_Probe_jetP_jetY_dRapLo_1btag"                   );
    // histnames.push_back("h2_AntiTagPuppi_Probe_jetP_jetY_dRapLo_2btag"                   );
    // histnames.push_back("h2_AntiTagPuppi_TagMassSDTau32_jetP_jetY_dRapIn_inclusive"      );
    // histnames.push_back("h2_AntiTagPuppi_TagMassSDTau32_jetP_jetY_dRapIn_0btag"          );
    // histnames.push_back("h2_AntiTagPuppi_TagMassSDTau32_jetP_jetY_dRapIn_1btag"          );
    // histnames.push_back("h2_AntiTagPuppi_TagMassSDTau32_jetP_jetY_dRapIn_2btag"          );
    // histnames.push_back("h2_AntiTagPuppi_TagMassSDTau32_jetP_jetY_dRapHi_inclusive"      );
    // histnames.push_back("h2_AntiTagPuppi_TagMassSDTau32_jetP_jetY_dRapHi_0btag"          );
    // histnames.push_back("h2_AntiTagPuppi_TagMassSDTau32_jetP_jetY_dRapHi_1btag"          );
    // histnames.push_back("h2_AntiTagPuppi_TagMassSDTau32_jetP_jetY_dRapHi_2btag"          );
    // histnames.push_back("h2_AntiTagPuppi_TagMassSDTau32_jetP_jetY_dRapLo_inclusive"      );
    // histnames.push_back("h2_AntiTagPuppi_TagMassSDTau32_jetP_jetY_dRapLo_0btag"          ); 
    // histnames.push_back("h2_AntiTagPuppi_TagMassSDTau32_jetP_jetY_dRapLo_1btag"          ); 
    // histnames.push_back("h2_AntiTagPuppi_TagMassSDTau32_jetP_jetY_dRapLo_2btag"          );



  }

  // Bkgd Est plots
  if (j==2){
    // histnames.push_back("predDist_CHS_SR_dRapHi_0btag_DijetMass"    );
    // histnames.push_back("predDist_CHS_SR_dRapHi_0btag_DijetMassMod" );
    // histnames.push_back("predDist_CHS_SR_dRapHi_0btag_HT"           );
    // histnames.push_back("predDist_CHS_SR_dRapHi_0btag_DeltaRap"     );
    // histnames.push_back("predDist_CHS_SR_dRapHi_0btag_JetP"         );
    // histnames.push_back("predDist_CHS_SR_dRapHi_0btag_JetPt"        );
    // histnames.push_back("predDist_CHS_SR_dRapHi_0btag_JetY"         );
    // histnames.push_back("predDist_CHS_SR_dRapHi_0btag_JetSDmass"    );
    // histnames.push_back("predDist_CHS_SR_dRapHi_0btag_JetTau32"     );
    // histnames.push_back("predDist_CHS_SR_dRapHi_0btag_maxbdisc"     );
    // histnames.push_back("predDist_CHS_SR_dRapHi_1btag_DijetMass"    );
    // histnames.push_back("predDist_CHS_SR_dRapHi_1btag_DijetMassMod" );
    // histnames.push_back("predDist_CHS_SR_dRapHi_1btag_HT"           );
    // histnames.push_back("predDist_CHS_SR_dRapHi_1btag_DeltaRap"     );
    // histnames.push_back("predDist_CHS_SR_dRapHi_1btag_JetP"         );
    // histnames.push_back("predDist_CHS_SR_dRapHi_1btag_JetPt"        );
    // histnames.push_back("predDist_CHS_SR_dRapHi_1btag_JetY"         );
    // histnames.push_back("predDist_CHS_SR_dRapHi_1btag_JetSDmass"    );
    // histnames.push_back("predDist_CHS_SR_dRapHi_1btag_JetTau32"     );
    // histnames.push_back("predDist_CHS_SR_dRapHi_1btag_maxbdisc"     );
    // histnames.push_back("predDist_CHS_SR_dRapHi_2btag_DijetMass"    );
    // histnames.push_back("predDist_CHS_SR_dRapHi_2btag_DijetMassMod" );
    // histnames.push_back("predDist_CHS_SR_dRapHi_2btag_HT"           );
    // histnames.push_back("predDist_CHS_SR_dRapHi_2btag_DeltaRap"     );
    // histnames.push_back("predDist_CHS_SR_dRapHi_2btag_JetP"         );
    // histnames.push_back("predDist_CHS_SR_dRapHi_2btag_JetPt"        );
    // histnames.push_back("predDist_CHS_SR_dRapHi_2btag_JetY"         );
    // histnames.push_back("predDist_CHS_SR_dRapHi_2btag_JetSDmass"    );
    // histnames.push_back("predDist_CHS_SR_dRapHi_2btag_JetTau32"     );
    // histnames.push_back("predDist_CHS_SR_dRapHi_2btag_maxbdisc"     );
    // histnames.push_back("predDist_CHS_SR_dRapHi_inclu_DijetMass"    );
    // histnames.push_back("predDist_CHS_SR_dRapHi_inclu_DijetMassMod" );
    // histnames.push_back("predDist_CHS_SR_dRapHi_inclu_HT"           );
    // histnames.push_back("predDist_CHS_SR_dRapHi_inclu_DeltaRap"     );
    // histnames.push_back("predDist_CHS_SR_dRapHi_inclu_JetP"         );
    // histnames.push_back("predDist_CHS_SR_dRapHi_inclu_JetPt"        );
    // histnames.push_back("predDist_CHS_SR_dRapHi_inclu_JetY"         );
    // histnames.push_back("predDist_CHS_SR_dRapHi_inclu_JetSDmass"    );
    // histnames.push_back("predDist_CHS_SR_dRapHi_inclu_JetTau32"     );
    // histnames.push_back("predDist_CHS_SR_dRapHi_inclu_maxbdisc"     );
    // histnames.push_back("predDist_CHS_SR_dRapLo_0btag_DijetMass"    );
    // histnames.push_back("predDist_CHS_SR_dRapLo_0btag_DijetMassMod" );
    // histnames.push_back("predDist_CHS_SR_dRapLo_0btag_HT"           );
    // histnames.push_back("predDist_CHS_SR_dRapLo_0btag_DeltaRap"     );
    // histnames.push_back("predDist_CHS_SR_dRapLo_0btag_JetP"         );
    // histnames.push_back("predDist_CHS_SR_dRapLo_0btag_JetPt"        );
    // histnames.push_back("predDist_CHS_SR_dRapLo_0btag_JetY"         );
    // histnames.push_back("predDist_CHS_SR_dRapLo_0btag_JetSDmass"    );
    // histnames.push_back("predDist_CHS_SR_dRapLo_0btag_JetTau32"     );
    // histnames.push_back("predDist_CHS_SR_dRapLo_0btag_maxbdisc"     );
    // histnames.push_back("predDist_CHS_SR_dRapLo_1btag_DijetMass"    );
    // histnames.push_back("predDist_CHS_SR_dRapLo_1btag_DijetMassMod" );
    // histnames.push_back("predDist_CHS_SR_dRapLo_1btag_HT"           );
    // histnames.push_back("predDist_CHS_SR_dRapLo_1btag_DeltaRap"     );
    // histnames.push_back("predDist_CHS_SR_dRapLo_1btag_JetP"         );
    // histnames.push_back("predDist_CHS_SR_dRapLo_1btag_JetPt"        );
    // histnames.push_back("predDist_CHS_SR_dRapLo_1btag_JetY"         );
    // histnames.push_back("predDist_CHS_SR_dRapLo_1btag_JetSDmass"    );
    // histnames.push_back("predDist_CHS_SR_dRapLo_1btag_JetTau32"     );
    // histnames.push_back("predDist_CHS_SR_dRapLo_1btag_maxbdisc"     );
    // histnames.push_back("predDist_CHS_SR_dRapLo_2btag_DijetMass"    );
    // histnames.push_back("predDist_CHS_SR_dRapLo_2btag_DijetMassMod" );
    // histnames.push_back("predDist_CHS_SR_dRapLo_2btag_HT"           );
    // histnames.push_back("predDist_CHS_SR_dRapLo_2btag_DeltaRap"     );
    // histnames.push_back("predDist_CHS_SR_dRapLo_2btag_JetP"         );
    // histnames.push_back("predDist_CHS_SR_dRapLo_2btag_JetPt"        );
    // histnames.push_back("predDist_CHS_SR_dRapLo_2btag_JetY"         );
    // histnames.push_back("predDist_CHS_SR_dRapLo_2btag_JetSDmass"    );
    // histnames.push_back("predDist_CHS_SR_dRapLo_2btag_JetTau32"     );
    // histnames.push_back("predDist_CHS_SR_dRapLo_2btag_maxbdisc"     );
    // histnames.push_back("predDist_CHS_SR_dRapLo_inclu_DijetMass"    );
    // histnames.push_back("predDist_CHS_SR_dRapLo_inclu_DijetMassMod" );
    // histnames.push_back("predDist_CHS_SR_dRapLo_inclu_HT"           );
    // histnames.push_back("predDist_CHS_SR_dRapLo_inclu_DeltaRap"     );
    // histnames.push_back("predDist_CHS_SR_dRapLo_inclu_JetP"         );
    // histnames.push_back("predDist_CHS_SR_dRapLo_inclu_JetPt"        );
    // histnames.push_back("predDist_CHS_SR_dRapLo_inclu_JetY"         );
    // histnames.push_back("predDist_CHS_SR_dRapLo_inclu_JetSDmass"    );
    // histnames.push_back("predDist_CHS_SR_dRapLo_inclu_JetTau32"     );
    // histnames.push_back("predDist_CHS_SR_dRapLo_inclu_maxbdisc"     );
    // histnames.push_back("predDist_CHS_SR_dRapIn_0btag_DijetMass"    );
    // histnames.push_back("predDist_CHS_SR_dRapIn_0btag_DijetMassMod" );
    // histnames.push_back("predDist_CHS_SR_dRapIn_0btag_HT"           );
    // histnames.push_back("predDist_CHS_SR_dRapIn_0btag_DeltaRap"     );
    // histnames.push_back("predDist_CHS_SR_dRapIn_0btag_JetP"         );
    // histnames.push_back("predDist_CHS_SR_dRapIn_0btag_JetPt"        );
    // histnames.push_back("predDist_CHS_SR_dRapIn_0btag_JetY"         );
    // histnames.push_back("predDist_CHS_SR_dRapIn_0btag_JetSDmass"    );
    // histnames.push_back("predDist_CHS_SR_dRapIn_0btag_JetTau32"     );
    // histnames.push_back("predDist_CHS_SR_dRapIn_0btag_maxbdisc"     );
    // histnames.push_back("predDist_CHS_SR_dRapIn_1btag_DijetMass"    );
    // histnames.push_back("predDist_CHS_SR_dRapIn_1btag_DijetMassMod" );
    // histnames.push_back("predDist_CHS_SR_dRapIn_1btag_HT"           );
    // histnames.push_back("predDist_CHS_SR_dRapIn_1btag_DeltaRap"     );
    // histnames.push_back("predDist_CHS_SR_dRapIn_1btag_JetP"         );
    // histnames.push_back("predDist_CHS_SR_dRapIn_1btag_JetPt"        );
    // histnames.push_back("predDist_CHS_SR_dRapIn_1btag_JetY"         );
    // histnames.push_back("predDist_CHS_SR_dRapIn_1btag_JetSDmass"    );
    // histnames.push_back("predDist_CHS_SR_dRapIn_1btag_JetTau32"     );
    // histnames.push_back("predDist_CHS_SR_dRapIn_1btag_maxbdisc"     );
    // histnames.push_back("predDist_CHS_SR_dRapIn_2btag_DijetMass"    );
    // histnames.push_back("predDist_CHS_SR_dRapIn_2btag_DijetMassMod" );
    // histnames.push_back("predDist_CHS_SR_dRapIn_2btag_HT"           );
    // histnames.push_back("predDist_CHS_SR_dRapIn_2btag_DeltaRap"     );
    // histnames.push_back("predDist_CHS_SR_dRapIn_2btag_JetP"         );
    // histnames.push_back("predDist_CHS_SR_dRapIn_2btag_JetPt"        );
    // histnames.push_back("predDist_CHS_SR_dRapIn_2btag_JetY"         );
    // histnames.push_back("predDist_CHS_SR_dRapIn_2btag_JetSDmass"    );
    // histnames.push_back("predDist_CHS_SR_dRapIn_2btag_JetTau32"     );
    // histnames.push_back("predDist_CHS_SR_dRapIn_2btag_maxbdisc"     );
    // histnames.push_back("predDist_CHS_SR_dRapIn_inclu_DijetMass"    );
    // histnames.push_back("predDist_CHS_SR_dRapIn_inclu_DijetMassMod" );
    // histnames.push_back("predDist_CHS_SR_dRapIn_inclu_HT"           );
    // histnames.push_back("predDist_CHS_SR_dRapIn_inclu_DeltaRap"     );
    // histnames.push_back("predDist_CHS_SR_dRapIn_inclu_JetP"         );
    // histnames.push_back("predDist_CHS_SR_dRapIn_inclu_JetPt"        );
    // histnames.push_back("predDist_CHS_SR_dRapIn_inclu_JetY"         );
    // histnames.push_back("predDist_CHS_SR_dRapIn_inclu_JetSDmass"    );
    // histnames.push_back("predDist_CHS_SR_dRapIn_inclu_JetTau32"     );
    // histnames.push_back("predDist_CHS_SR_dRapIn_inclu_maxbdisc"     );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_0btag_DijetMass"    );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_0btag_DijetMassMod" );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_0btag_HT"           );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_0btag_DeltaRap"     );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_0btag_JetP"         );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_0btag_JetPt"        );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_0btag_JetY"         );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_0btag_JetSDmass"    );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_0btag_JetTau32"     );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_0btag_maxbdisc"     );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_1btag_DijetMass"    );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_1btag_DijetMassMod" );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_1btag_HT"           );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_1btag_DeltaRap"     );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_1btag_JetP"         );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_1btag_JetPt"        );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_1btag_JetY"         );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_1btag_JetSDmass"    );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_1btag_JetTau32"     );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_1btag_maxbdisc"     );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_2btag_DijetMass"    );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_2btag_DijetMassMod" );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_2btag_HT"           );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_2btag_DeltaRap"     );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_2btag_JetP"         );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_2btag_JetPt"        );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_2btag_JetY"         );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_2btag_JetSDmass"    );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_2btag_JetTau32"     );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_2btag_maxbdisc"     );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_inclu_DijetMass"    );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_inclu_DijetMassMod" );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_inclu_HT"           );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_inclu_DeltaRap"     );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_inclu_JetP"         );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_inclu_JetPt"        );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_inclu_JetY"         );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_inclu_JetSDmass"    );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_inclu_JetTau32"     );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_inclu_maxbdisc"     );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_0btag_DijetMass"    );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_0btag_DijetMassMod" );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_0btag_HT"           );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_0btag_DeltaRap"     );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_0btag_JetP"         );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_0btag_JetPt"        );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_0btag_JetY"         );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_0btag_JetSDmass"    );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_0btag_JetTau32"     );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_0btag_maxbdisc"     );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_1btag_DijetMass"    );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_1btag_DijetMassMod" );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_1btag_HT"           );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_1btag_DeltaRap"     );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_1btag_JetP"         );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_1btag_JetPt"        );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_1btag_JetY"         );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_1btag_JetSDmass"    );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_1btag_JetTau32"     );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_1btag_maxbdisc"     );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_2btag_DijetMass"    );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_2btag_DijetMassMod" );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_2btag_HT"           );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_2btag_DeltaRap"     );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_2btag_JetP"         );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_2btag_JetPt"        );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_2btag_JetY"         );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_2btag_JetSDmass"    );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_2btag_JetTau32"     );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_2btag_maxbdisc"     );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_inclu_DijetMass"    );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_inclu_DijetMassMod" );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_inclu_HT"           );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_inclu_DeltaRap"     );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_inclu_JetP"         );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_inclu_JetPt"        );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_inclu_JetY"         );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_inclu_JetSDmass"    );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_inclu_JetTau32"     );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_inclu_maxbdisc"     );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_0btag_DijetMass"    );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_0btag_DijetMassMod" );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_0btag_HT"           );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_0btag_DeltaRap"     );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_0btag_JetP"         );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_0btag_JetPt"        );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_0btag_JetY"         );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_0btag_JetSDmass"    );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_0btag_JetTau32"     );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_0btag_maxbdisc"     );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_1btag_DijetMass"    );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_1btag_DijetMassMod" );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_1btag_HT"           );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_1btag_DeltaRap"     );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_1btag_JetP"         );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_1btag_JetPt"        );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_1btag_JetY"         );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_1btag_JetSDmass"    );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_1btag_JetTau32"     );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_1btag_maxbdisc"     );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_2btag_DijetMass"    );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_2btag_DijetMassMod" );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_2btag_HT"           );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_2btag_DeltaRap"     );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_2btag_JetP"         );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_2btag_JetPt"        );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_2btag_JetY"         );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_2btag_JetSDmass"    );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_2btag_JetTau32"     );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_2btag_maxbdisc"     );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_inclu_DijetMass"    );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_inclu_DijetMassMod" );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_inclu_HT"           );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_inclu_DeltaRap"     );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_inclu_JetP"         );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_inclu_JetPt"        );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_inclu_JetY"         );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_inclu_JetSDmass"    );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_inclu_JetTau32"     );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_inclu_maxbdisc"     );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_0btag_DijetMass"     );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_0btag_DijetMassMod"  );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_0btag_HT"            );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_0btag_DeltaRap"      );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_0btag_JetP"          );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_0btag_JetPt"         );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_0btag_JetY"          );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_0btag_JetSDmass"     );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_0btag_JetTau32"      );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_0btag_maxbdisc"      );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_1btag_DijetMass"     );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_1btag_DijetMassMod"  );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_1btag_HT"            );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_1btag_DeltaRap"      );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_1btag_JetP"          );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_1btag_JetPt"         );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_1btag_JetY"          );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_1btag_JetSDmass"     );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_1btag_JetTau32"      );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_1btag_maxbdisc"      );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_2btag_DijetMass"     );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_2btag_DijetMassMod"  );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_2btag_HT"            );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_2btag_DeltaRap"      );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_2btag_JetP"          );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_2btag_JetPt"         );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_2btag_JetY"          );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_2btag_JetSDmass"     );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_2btag_JetTau32"      );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_2btag_maxbdisc"      );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_inclu_DijetMass"     );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_inclu_DijetMassMod"  );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_inclu_HT"            );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_inclu_DeltaRap"      );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_inclu_JetP"          );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_inclu_JetPt"         );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_inclu_JetY"          );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_inclu_JetSDmass"     );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_inclu_JetTau32"      );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_inclu_maxbdisc"      );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_0btag_DijetMass"     );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_0btag_DijetMassMod"  );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_0btag_HT"            );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_0btag_DeltaRap"      );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_0btag_JetP"          );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_0btag_JetPt"         );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_0btag_JetY"          );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_0btag_JetSDmass"     );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_0btag_JetTau32"      );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_0btag_maxbdisc"      );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_1btag_DijetMass"     );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_1btag_DijetMassMod"  );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_1btag_HT"            );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_1btag_DeltaRap"      );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_1btag_JetP"          );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_1btag_JetPt"         );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_1btag_JetY"          );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_1btag_JetSDmass"     );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_1btag_JetTau32"      );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_1btag_maxbdisc"      );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_2btag_DijetMass"     );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_2btag_DijetMassMod"  );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_2btag_HT"            );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_2btag_DeltaRap"      );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_2btag_JetP"          );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_2btag_JetPt"         );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_2btag_JetY"          );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_2btag_JetSDmass"     );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_2btag_JetTau32"      );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_2btag_maxbdisc"      );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_inclu_DijetMass"     );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_inclu_DijetMassMod"  );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_inclu_HT"            );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_inclu_DeltaRap"      );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_inclu_JetP"          );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_inclu_JetPt"         );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_inclu_JetY"          );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_inclu_JetSDmass"     );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_inclu_JetTau32"      );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_inclu_maxbdisc"      );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_0btag_DijetMass"     );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_0btag_DijetMassMod"  );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_0btag_HT"            );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_0btag_DeltaRap"      );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_0btag_JetP"          );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_0btag_JetPt"         );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_0btag_JetY"          );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_0btag_JetSDmass"     );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_0btag_JetTau32"      );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_0btag_maxbdisc"      );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_1btag_DijetMass"     );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_1btag_DijetMassMod"  );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_1btag_HT"            );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_1btag_DeltaRap"      );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_1btag_JetP"          );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_1btag_JetPt"         );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_1btag_JetY"          );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_1btag_JetSDmass"     );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_1btag_JetTau32"      );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_1btag_maxbdisc"      );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_2btag_DijetMass"     );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_2btag_DijetMassMod"  );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_2btag_HT"            );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_2btag_DeltaRap"      );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_2btag_JetP"          );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_2btag_JetPt"         );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_2btag_JetY"          );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_2btag_JetSDmass"     );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_2btag_JetTau32"      );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_2btag_maxbdisc"      );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_inclu_DijetMass"     );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_inclu_DijetMassMod"  );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_inclu_HT"            );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_inclu_DeltaRap"      );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_inclu_JetP"          );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_inclu_JetPt"         );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_inclu_JetY"          );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_inclu_JetSDmass"     );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_inclu_JetTau32"      );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_inclu_maxbdisc"      );
    histnames.push_back("predDist_Puppi_SR_dRapHi_0btag_DijetMass"    );
    histnames.push_back("predDist_Puppi_SR_dRapHi_0btag_DijetMassMod" );
    histnames.push_back("predDist_Puppi_SR_dRapHi_0btag_HT"           );
    histnames.push_back("predDist_Puppi_SR_dRapHi_0btag_DeltaRap"     );
    histnames.push_back("predDist_Puppi_SR_dRapHi_0btag_JetP"         );
    histnames.push_back("predDist_Puppi_SR_dRapHi_0btag_JetPt"        );
    histnames.push_back("predDist_Puppi_SR_dRapHi_0btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SR_dRapHi_0btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SR_dRapHi_0btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SR_dRapHi_0btag_maxbdisc"     );
    histnames.push_back("predDist_Puppi_SR_dRapHi_1btag_DijetMass"    );
    histnames.push_back("predDist_Puppi_SR_dRapHi_1btag_DijetMassMod" );
    histnames.push_back("predDist_Puppi_SR_dRapHi_1btag_HT"           );
    histnames.push_back("predDist_Puppi_SR_dRapHi_1btag_DeltaRap"     );
    histnames.push_back("predDist_Puppi_SR_dRapHi_1btag_JetP"         );
    histnames.push_back("predDist_Puppi_SR_dRapHi_1btag_JetPt"        );
    histnames.push_back("predDist_Puppi_SR_dRapHi_1btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SR_dRapHi_1btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SR_dRapHi_1btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SR_dRapHi_1btag_maxbdisc"     );
    histnames.push_back("predDist_Puppi_SR_dRapHi_2btag_DijetMass"    );
    histnames.push_back("predDist_Puppi_SR_dRapHi_2btag_DijetMassMod" );
    histnames.push_back("predDist_Puppi_SR_dRapHi_2btag_HT"           );
    histnames.push_back("predDist_Puppi_SR_dRapHi_2btag_DeltaRap"     );
    histnames.push_back("predDist_Puppi_SR_dRapHi_2btag_JetP"         );
    histnames.push_back("predDist_Puppi_SR_dRapHi_2btag_JetPt"        );
    histnames.push_back("predDist_Puppi_SR_dRapHi_2btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SR_dRapHi_2btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SR_dRapHi_2btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SR_dRapHi_2btag_maxbdisc"     );
    histnames.push_back("predDist_Puppi_SR_dRapHi_inclu_DijetMass"    );
    histnames.push_back("predDist_Puppi_SR_dRapHi_inclu_DijetMassMod" );
    histnames.push_back("predDist_Puppi_SR_dRapHi_inclu_HT"           );
    histnames.push_back("predDist_Puppi_SR_dRapHi_inclu_DeltaRap"     );
    histnames.push_back("predDist_Puppi_SR_dRapHi_inclu_JetP"         );
    histnames.push_back("predDist_Puppi_SR_dRapHi_inclu_JetPt"        );
    histnames.push_back("predDist_Puppi_SR_dRapHi_inclu_JetY"         );
    // histnames.push_back("predDist_Puppi_SR_dRapHi_inclu_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SR_dRapHi_inclu_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SR_dRapHi_inclu_maxbdisc"     );
    histnames.push_back("predDist_Puppi_SR_dRapLo_0btag_DijetMass"    );
    histnames.push_back("predDist_Puppi_SR_dRapLo_0btag_DijetMassMod" );
    histnames.push_back("predDist_Puppi_SR_dRapLo_0btag_HT"           );
    histnames.push_back("predDist_Puppi_SR_dRapLo_0btag_DeltaRap"     );
    histnames.push_back("predDist_Puppi_SR_dRapLo_0btag_JetP"         );
    histnames.push_back("predDist_Puppi_SR_dRapLo_0btag_JetPt"        );
    histnames.push_back("predDist_Puppi_SR_dRapLo_0btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SR_dRapLo_0btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SR_dRapLo_0btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SR_dRapLo_0btag_maxbdisc"     );
    histnames.push_back("predDist_Puppi_SR_dRapLo_1btag_DijetMass"    );
    histnames.push_back("predDist_Puppi_SR_dRapLo_1btag_DijetMassMod" );
    histnames.push_back("predDist_Puppi_SR_dRapLo_1btag_HT"           );
    histnames.push_back("predDist_Puppi_SR_dRapLo_1btag_DeltaRap"     );
    histnames.push_back("predDist_Puppi_SR_dRapLo_1btag_JetP"         );
    histnames.push_back("predDist_Puppi_SR_dRapLo_1btag_JetPt"        );
    histnames.push_back("predDist_Puppi_SR_dRapLo_1btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SR_dRapLo_1btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SR_dRapLo_1btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SR_dRapLo_1btag_maxbdisc"     );
    histnames.push_back("predDist_Puppi_SR_dRapLo_2btag_DijetMass"    );
    histnames.push_back("predDist_Puppi_SR_dRapLo_2btag_DijetMassMod" );
    histnames.push_back("predDist_Puppi_SR_dRapLo_2btag_HT"           );
    histnames.push_back("predDist_Puppi_SR_dRapLo_2btag_DeltaRap"     );
    histnames.push_back("predDist_Puppi_SR_dRapLo_2btag_JetP"         );
    histnames.push_back("predDist_Puppi_SR_dRapLo_2btag_JetPt"        );
    histnames.push_back("predDist_Puppi_SR_dRapLo_2btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SR_dRapLo_2btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SR_dRapLo_2btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SR_dRapLo_2btag_maxbdisc"     );
    histnames.push_back("predDist_Puppi_SR_dRapLo_inclu_DijetMass"    );
    histnames.push_back("predDist_Puppi_SR_dRapLo_inclu_DijetMassMod" );
    histnames.push_back("predDist_Puppi_SR_dRapLo_inclu_HT"           );
    histnames.push_back("predDist_Puppi_SR_dRapLo_inclu_DeltaRap"     );
    histnames.push_back("predDist_Puppi_SR_dRapLo_inclu_JetP"         );
    histnames.push_back("predDist_Puppi_SR_dRapLo_inclu_JetPt"        );
    histnames.push_back("predDist_Puppi_SR_dRapLo_inclu_JetY"         );
    // histnames.push_back("predDist_Puppi_SR_dRapLo_inclu_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SR_dRapLo_inclu_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SR_dRapLo_inclu_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_0btag_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_0btag_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_0btag_HT"           );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_0btag_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_0btag_JetP"         );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_0btag_JetPt"        );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_0btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_0btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_0btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_0btag_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_1btag_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_1btag_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_1btag_HT"           );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_1btag_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_1btag_JetP"         );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_1btag_JetPt"        );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_1btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_1btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_1btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_1btag_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_2btag_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_2btag_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_2btag_HT"           );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_2btag_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_2btag_JetP"         );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_2btag_JetPt"        );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_2btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_2btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_2btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_2btag_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_inclu_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_inclu_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_inclu_HT"           );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_inclu_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_inclu_JetP"         );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_inclu_JetPt"        );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_inclu_JetY"         );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_inclu_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_inclu_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SR_dRapIn_inclu_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_0btag_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_0btag_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_0btag_HT"           );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_0btag_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_0btag_JetP"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_0btag_JetPt"        );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_0btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_0btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_0btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_0btag_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_1btag_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_1btag_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_1btag_HT"           );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_1btag_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_1btag_JetP"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_1btag_JetPt"        );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_1btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_1btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_1btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_1btag_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_2btag_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_2btag_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_2btag_HT"           );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_2btag_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_2btag_JetP"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_2btag_JetPt"        );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_2btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_2btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_2btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_2btag_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_inclu_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_inclu_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_inclu_HT"           );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_inclu_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_inclu_JetP"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_inclu_JetPt"        );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_inclu_JetY"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_inclu_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_inclu_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_inclu_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_0btag_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_0btag_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_0btag_HT"           );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_0btag_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_0btag_JetP"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_0btag_JetPt"        );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_0btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_0btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_0btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_0btag_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_1btag_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_1btag_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_1btag_HT"           );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_1btag_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_1btag_JetP"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_1btag_JetPt"        );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_1btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_1btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_1btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_1btag_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_2btag_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_2btag_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_2btag_HT"           );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_2btag_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_2btag_JetP"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_2btag_JetPt"        );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_2btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_2btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_2btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_2btag_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_inclu_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_inclu_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_inclu_HT"           );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_inclu_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_inclu_JetP"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_inclu_JetPt"        );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_inclu_JetY"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_inclu_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_inclu_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_inclu_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_0btag_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_0btag_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_0btag_HT"           );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_0btag_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_0btag_JetP"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_0btag_JetPt"        );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_0btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_0btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_0btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_0btag_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_1btag_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_1btag_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_1btag_HT"           );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_1btag_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_1btag_JetP"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_1btag_JetPt"        );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_1btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_1btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_1btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_1btag_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_2btag_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_2btag_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_2btag_HT"           );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_2btag_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_2btag_JetP"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_2btag_JetPt"        );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_2btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_2btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_2btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_2btag_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_inclu_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_inclu_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_inclu_HT"           );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_inclu_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_inclu_JetP"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_inclu_JetPt"        );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_inclu_JetY"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_inclu_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_inclu_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_inclu_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_0btag_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_0btag_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_0btag_HT"           );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_0btag_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_0btag_JetP"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_0btag_JetPt"        );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_0btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_0btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_0btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_0btag_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_1btag_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_1btag_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_1btag_HT"           );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_1btag_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_1btag_JetP"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_1btag_JetPt"        );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_1btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_1btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_1btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_1btag_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_2btag_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_2btag_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_2btag_HT"           );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_2btag_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_2btag_JetP"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_2btag_JetPt"        );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_2btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_2btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_2btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_2btag_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_inclu_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_inclu_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_inclu_HT"           );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_inclu_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_inclu_JetP"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_inclu_JetPt"        );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_inclu_JetY"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_inclu_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_inclu_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_inclu_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_0btag_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_0btag_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_0btag_HT"           );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_0btag_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_0btag_JetP"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_0btag_JetPt"        );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_0btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_0btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_0btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_0btag_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_1btag_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_1btag_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_1btag_HT"           );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_1btag_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_1btag_JetP"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_1btag_JetPt"        );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_1btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_1btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_1btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_1btag_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_2btag_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_2btag_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_2btag_HT"           );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_2btag_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_2btag_JetP"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_2btag_JetPt"        );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_2btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_2btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_2btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_2btag_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_inclu_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_inclu_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_inclu_HT"           );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_inclu_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_inclu_JetP"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_inclu_JetPt"        );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_inclu_JetY"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_inclu_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_inclu_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_inclu_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_0btag_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_0btag_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_0btag_HT"           );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_0btag_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_0btag_JetP"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_0btag_JetPt"        );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_0btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_0btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_0btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_0btag_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_1btag_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_1btag_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_1btag_HT"           );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_1btag_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_1btag_JetP"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_1btag_JetPt"        );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_1btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_1btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_1btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_1btag_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_2btag_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_2btag_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_2btag_HT"           );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_2btag_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_2btag_JetP"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_2btag_JetPt"        );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_2btag_JetY"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_2btag_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_2btag_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_2btag_maxbdisc"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_inclu_DijetMass"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_inclu_DijetMassMod" );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_inclu_HT"           );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_inclu_DeltaRap"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_inclu_JetP"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_inclu_JetPt"        );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_inclu_JetY"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_inclu_JetSDmass"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_inclu_JetTau32"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_inclu_maxbdisc"        );
    // histnames.push_back("predDist_CHS_SR_dRapHi_0btag_DijetMass_pred"    );
    // histnames.push_back("predDist_CHS_SR_dRapHi_0btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_CHS_SR_dRapHi_0btag_HT_pred"           );
    // histnames.push_back("predDist_CHS_SR_dRapHi_0btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapHi_0btag_JetP_pred"         );
    // histnames.push_back("predDist_CHS_SR_dRapHi_0btag_JetPt_pred"        );
    // histnames.push_back("predDist_CHS_SR_dRapHi_0btag_JetY_pred"         );
    // histnames.push_back("predDist_CHS_SR_dRapHi_0btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_CHS_SR_dRapHi_0btag_JetTau32_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapHi_0btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapHi_1btag_DijetMass_pred"    );
    // histnames.push_back("predDist_CHS_SR_dRapHi_1btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_CHS_SR_dRapHi_1btag_HT_pred"           );
    // histnames.push_back("predDist_CHS_SR_dRapHi_1btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapHi_1btag_JetP_pred"         );
    // histnames.push_back("predDist_CHS_SR_dRapHi_1btag_JetPt_pred"        );
    // histnames.push_back("predDist_CHS_SR_dRapHi_1btag_JetY_pred"         );
    // histnames.push_back("predDist_CHS_SR_dRapHi_1btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_CHS_SR_dRapHi_1btag_JetTau32_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapHi_1btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapHi_2btag_DijetMass_pred"    );
    // histnames.push_back("predDist_CHS_SR_dRapHi_2btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_CHS_SR_dRapHi_2btag_HT_pred"           );
    // histnames.push_back("predDist_CHS_SR_dRapHi_2btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapHi_2btag_JetP_pred"         );
    // histnames.push_back("predDist_CHS_SR_dRapHi_2btag_JetPt_pred"        );
    // histnames.push_back("predDist_CHS_SR_dRapHi_2btag_JetY_pred"         );
    // histnames.push_back("predDist_CHS_SR_dRapHi_2btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_CHS_SR_dRapHi_2btag_JetTau32_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapHi_2btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapHi_inclu_DijetMass_pred"    );
    // histnames.push_back("predDist_CHS_SR_dRapHi_inclu_DijetMassMod_pred" );
    // histnames.push_back("predDist_CHS_SR_dRapHi_inclu_HT_pred"           );
    // histnames.push_back("predDist_CHS_SR_dRapHi_inclu_DeltaRap_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapHi_inclu_JetP_pred"         );
    // histnames.push_back("predDist_CHS_SR_dRapHi_inclu_JetPt_pred"        );
    // histnames.push_back("predDist_CHS_SR_dRapHi_inclu_JetY_pred"         );
    // histnames.push_back("predDist_CHS_SR_dRapHi_inclu_JetSDmass_pred"    );
    // histnames.push_back("predDist_CHS_SR_dRapHi_inclu_JetTau32_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapHi_inclu_maxbdisc_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapLo_0btag_DijetMass_pred"    );
    // histnames.push_back("predDist_CHS_SR_dRapLo_0btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_CHS_SR_dRapLo_0btag_HT_pred"           );
    // histnames.push_back("predDist_CHS_SR_dRapLo_0btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapLo_0btag_JetP_pred"         );
    // histnames.push_back("predDist_CHS_SR_dRapLo_0btag_JetPt_pred"        );
    // histnames.push_back("predDist_CHS_SR_dRapLo_0btag_JetY_pred"         );
    // histnames.push_back("predDist_CHS_SR_dRapLo_0btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_CHS_SR_dRapLo_0btag_JetTau32_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapLo_0btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapLo_1btag_DijetMass_pred"    );
    // histnames.push_back("predDist_CHS_SR_dRapLo_1btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_CHS_SR_dRapLo_1btag_HT_pred"           );
    // histnames.push_back("predDist_CHS_SR_dRapLo_1btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapLo_1btag_JetP_pred"         );
    // histnames.push_back("predDist_CHS_SR_dRapLo_1btag_JetPt_pred"        );
    // histnames.push_back("predDist_CHS_SR_dRapLo_1btag_JetY_pred"         );
    // histnames.push_back("predDist_CHS_SR_dRapLo_1btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_CHS_SR_dRapLo_1btag_JetTau32_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapLo_1btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapLo_2btag_DijetMass_pred"    );
    // histnames.push_back("predDist_CHS_SR_dRapLo_2btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_CHS_SR_dRapLo_2btag_HT_pred"           );
    // histnames.push_back("predDist_CHS_SR_dRapLo_2btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapLo_2btag_JetP_pred"         );
    // histnames.push_back("predDist_CHS_SR_dRapLo_2btag_JetPt_pred"        );
    // histnames.push_back("predDist_CHS_SR_dRapLo_2btag_JetY_pred"         );
    // histnames.push_back("predDist_CHS_SR_dRapLo_2btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_CHS_SR_dRapLo_2btag_JetTau32_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapLo_2btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapLo_inclu_DijetMass_pred"    );
    // histnames.push_back("predDist_CHS_SR_dRapLo_inclu_DijetMassMod_pred" );
    // histnames.push_back("predDist_CHS_SR_dRapLo_inclu_HT_pred"           );
    // histnames.push_back("predDist_CHS_SR_dRapLo_inclu_DeltaRap_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapLo_inclu_JetP_pred"         );
    // histnames.push_back("predDist_CHS_SR_dRapLo_inclu_JetPt_pred"        );
    // histnames.push_back("predDist_CHS_SR_dRapLo_inclu_JetY_pred"         );
    // histnames.push_back("predDist_CHS_SR_dRapLo_inclu_JetSDmass_pred"    );
    // histnames.push_back("predDist_CHS_SR_dRapLo_inclu_JetTau32_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapLo_inclu_maxbdisc_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapIn_0btag_DijetMass_pred"    );
    // histnames.push_back("predDist_CHS_SR_dRapIn_0btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_CHS_SR_dRapIn_0btag_HT_pred"           );
    // histnames.push_back("predDist_CHS_SR_dRapIn_0btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapIn_0btag_JetP_pred"         );
    // histnames.push_back("predDist_CHS_SR_dRapIn_0btag_JetPt_pred"        );
    // histnames.push_back("predDist_CHS_SR_dRapIn_0btag_JetY_pred"         );
    // histnames.push_back("predDist_CHS_SR_dRapIn_0btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_CHS_SR_dRapIn_0btag_JetTau32_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapIn_0btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapIn_1btag_DijetMass_pred"    );
    // histnames.push_back("predDist_CHS_SR_dRapIn_1btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_CHS_SR_dRapIn_1btag_HT_pred"           );
    // histnames.push_back("predDist_CHS_SR_dRapIn_1btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapIn_1btag_JetP_pred"         );
    // histnames.push_back("predDist_CHS_SR_dRapIn_1btag_JetPt_pred"        );
    // histnames.push_back("predDist_CHS_SR_dRapIn_1btag_JetY_pred"         );
    // histnames.push_back("predDist_CHS_SR_dRapIn_1btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_CHS_SR_dRapIn_1btag_JetTau32_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapIn_1btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapIn_2btag_DijetMass_pred"    );
    // histnames.push_back("predDist_CHS_SR_dRapIn_2btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_CHS_SR_dRapIn_2btag_HT_pred"           );
    // histnames.push_back("predDist_CHS_SR_dRapIn_2btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapIn_2btag_JetP_pred"         );
    // histnames.push_back("predDist_CHS_SR_dRapIn_2btag_JetPt_pred"        );
    // histnames.push_back("predDist_CHS_SR_dRapIn_2btag_JetY_pred"         );
    // histnames.push_back("predDist_CHS_SR_dRapIn_2btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_CHS_SR_dRapIn_2btag_JetTau32_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapIn_2btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapIn_inclu_DijetMass_pred"    );
    // histnames.push_back("predDist_CHS_SR_dRapIn_inclu_DijetMassMod_pred" );
    // histnames.push_back("predDist_CHS_SR_dRapIn_inclu_HT_pred"           );
    // histnames.push_back("predDist_CHS_SR_dRapIn_inclu_DeltaRap_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapIn_inclu_JetP_pred"         );
    // histnames.push_back("predDist_CHS_SR_dRapIn_inclu_JetPt_pred"        );
    // histnames.push_back("predDist_CHS_SR_dRapIn_inclu_JetY_pred"         );
    // histnames.push_back("predDist_CHS_SR_dRapIn_inclu_JetSDmass_pred"    );
    // histnames.push_back("predDist_CHS_SR_dRapIn_inclu_JetTau32_pred"     );
    // histnames.push_back("predDist_CHS_SR_dRapIn_inclu_maxbdisc_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_0btag_DijetMass_pred"    );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_0btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_0btag_HT_pred"           );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_0btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_0btag_JetP_pred"         );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_0btag_JetPt_pred"        );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_0btag_JetY_pred"         );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_0btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_0btag_JetTau32_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_0btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_1btag_DijetMass_pred"    );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_1btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_1btag_HT_pred"           );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_1btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_1btag_JetP_pred"         );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_1btag_JetPt_pred"        );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_1btag_JetY_pred"         );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_1btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_1btag_JetTau32_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_1btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_2btag_DijetMass_pred"    );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_2btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_2btag_HT_pred"           );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_2btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_2btag_JetP_pred"         );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_2btag_JetPt_pred"        );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_2btag_JetY_pred"         );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_2btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_2btag_JetTau32_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_2btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_inclu_DijetMass_pred"    );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_inclu_DijetMassMod_pred" );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_inclu_HT_pred"           );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_inclu_DeltaRap_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_inclu_JetP_pred"         );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_inclu_JetPt_pred"        );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_inclu_JetY_pred"         );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_inclu_JetSDmass_pred"    );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_inclu_JetTau32_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapHi_inclu_maxbdisc_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_0btag_DijetMass_pred"    );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_0btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_0btag_HT_pred"           );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_0btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_0btag_JetP_pred"         );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_0btag_JetPt_pred"        );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_0btag_JetY_pred"         );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_0btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_0btag_JetTau32_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_0btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_1btag_DijetMass_pred"    );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_1btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_1btag_HT_pred"           );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_1btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_1btag_JetP_pred"         );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_1btag_JetPt_pred"        );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_1btag_JetY_pred"         );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_1btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_1btag_JetTau32_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_1btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_2btag_DijetMass_pred"    );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_2btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_2btag_HT_pred"           );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_2btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_2btag_JetP_pred"         );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_2btag_JetPt_pred"        );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_2btag_JetY_pred"         );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_2btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_2btag_JetTau32_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_2btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_inclu_DijetMass_pred"    );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_inclu_DijetMassMod_pred" );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_inclu_HT_pred"           );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_inclu_DeltaRap_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_inclu_JetP_pred"         );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_inclu_JetPt_pred"        );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_inclu_JetY_pred"         );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_inclu_JetSDmass_pred"    );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_inclu_JetTau32_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapLo_inclu_maxbdisc_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_0btag_DijetMass_pred"    );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_0btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_0btag_HT_pred"           );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_0btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_0btag_JetP_pred"         );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_0btag_JetPt_pred"        );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_0btag_JetY_pred"         );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_0btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_0btag_JetTau32_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_0btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_1btag_DijetMass_pred"    );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_1btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_1btag_HT_pred"           );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_1btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_1btag_JetP_pred"         );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_1btag_JetPt_pred"        );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_1btag_JetY_pred"         );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_1btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_1btag_JetTau32_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_1btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_2btag_DijetMass_pred"    );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_2btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_2btag_HT_pred"           );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_2btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_2btag_JetP_pred"         );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_2btag_JetPt_pred"        );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_2btag_JetY_pred"         );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_2btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_2btag_JetTau32_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_2btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_inclu_DijetMass_pred"    );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_inclu_DijetMassMod_pred" );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_inclu_HT_pred"           );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_inclu_DeltaRap_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_inclu_JetP_pred"         );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_inclu_JetPt_pred"        );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_inclu_JetY_pred"         );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_inclu_JetSDmass_pred"    );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_inclu_JetTau32_pred"     );
    // histnames.push_back("predDist_CHS_SB1_dRapIn_inclu_maxbdisc_pred"     );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_0btag_DijetMass_pred"     );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_0btag_DijetMassMod_pred"  );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_0btag_HT_pred"            );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_0btag_DeltaRap_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_0btag_JetP_pred"          );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_0btag_JetPt_pred"         );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_0btag_JetY_pred"          );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_0btag_JetSDmass_pred"     );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_0btag_JetTau32_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_0btag_maxbdisc_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_1btag_DijetMass_pred"     );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_1btag_DijetMassMod_pred"  );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_1btag_HT_pred"            );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_1btag_DeltaRap_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_1btag_JetP_pred"          );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_1btag_JetPt_pred"         );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_1btag_JetY_pred"          );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_1btag_JetSDmass_pred"     );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_1btag_JetTau32_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_1btag_maxbdisc_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_2btag_DijetMass_pred"     );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_2btag_DijetMassMod_pred"  );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_2btag_HT_pred"            );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_2btag_DeltaRap_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_2btag_JetP_pred"          );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_2btag_JetPt_pred"         );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_2btag_JetY_pred"          );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_2btag_JetSDmass_pred"     );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_2btag_JetTau32_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_2btag_maxbdisc_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_inclu_DijetMass_pred"     );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_inclu_DijetMassMod_pred"  );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_inclu_HT_pred"            );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_inclu_DeltaRap_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_inclu_JetP_pred"          );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_inclu_JetPt_pred"         );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_inclu_JetY_pred"          );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_inclu_JetSDmass_pred"     );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_inclu_JetTau32_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapHi_inclu_maxbdisc_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_0btag_DijetMass_pred"     );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_0btag_DijetMassMod_pred"  );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_0btag_HT_pred"            );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_0btag_DeltaRap_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_0btag_JetP_pred"          );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_0btag_JetPt_pred"         );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_0btag_JetY_pred"          );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_0btag_JetSDmass_pred"     );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_0btag_JetTau32_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_0btag_maxbdisc_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_1btag_DijetMass_pred"     );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_1btag_DijetMassMod_pred"  );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_1btag_HT_pred"            );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_1btag_DeltaRap_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_1btag_JetP_pred"          );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_1btag_JetPt_pred"         );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_1btag_JetY_pred"          );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_1btag_JetSDmass_pred"     );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_1btag_JetTau32_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_1btag_maxbdisc_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_2btag_DijetMass_pred"     );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_2btag_DijetMassMod_pred"  );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_2btag_HT_pred"            );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_2btag_DeltaRap_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_2btag_JetP_pred"          );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_2btag_JetPt_pred"         );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_2btag_JetY_pred"          );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_2btag_JetSDmass_pred"     );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_2btag_JetTau32_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_2btag_maxbdisc_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_inclu_DijetMass_pred"     );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_inclu_DijetMassMod_pred"  );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_inclu_HT_pred"            );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_inclu_DeltaRap_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_inclu_JetP_pred"          );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_inclu_JetPt_pred"         );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_inclu_JetY_pred"          );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_inclu_JetSDmass_pred"     );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_inclu_JetTau32_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapLo_inclu_maxbdisc_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_0btag_DijetMass_pred"     );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_0btag_DijetMassMod_pred"  );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_0btag_HT_pred"            );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_0btag_DeltaRap_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_0btag_JetP_pred"          );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_0btag_JetPt_pred"         );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_0btag_JetY_pred"          );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_0btag_JetSDmass_pred"     );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_0btag_JetTau32_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_0btag_maxbdisc_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_1btag_DijetMass_pred"     );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_1btag_DijetMassMod_pred"  );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_1btag_HT_pred"            );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_1btag_DeltaRap_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_1btag_JetP_pred"          );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_1btag_JetPt_pred"         );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_1btag_JetY_pred"          );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_1btag_JetSDmass_pred"     );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_1btag_JetTau32_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_1btag_maxbdisc_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_2btag_DijetMass_pred"     );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_2btag_DijetMassMod_pred"  );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_2btag_HT_pred"            );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_2btag_DeltaRap_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_2btag_JetP_pred"          );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_2btag_JetPt_pred"         );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_2btag_JetY_pred"          );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_2btag_JetSDmass_pred"     );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_2btag_JetTau32_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_2btag_maxbdisc_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_inclu_DijetMass_pred"     );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_inclu_DijetMassMod_pred"  );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_inclu_HT_pred"            );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_inclu_DeltaRap_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_inclu_JetP_pred"          );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_inclu_JetPt_pred"         );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_inclu_JetY_pred"          );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_inclu_JetSDmass_pred"     );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_inclu_JetTau32_pred"      );
    // histnames.push_back("predDist_CHS_SB2_dRapIn_inclu_maxbdisc_pred"      );
    histnames.push_back("predDist_Puppi_SR_dRapHi_0btag_DijetMass_pred"    );
    histnames.push_back("predDist_Puppi_SR_dRapHi_0btag_DijetMassMod_pred" );
    histnames.push_back("predDist_Puppi_SR_dRapHi_0btag_HT_pred"           );
    histnames.push_back("predDist_Puppi_SR_dRapHi_0btag_DeltaRap_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapHi_0btag_JetP_pred"         );
    histnames.push_back("predDist_Puppi_SR_dRapHi_0btag_JetPt_pred"        );
    histnames.push_back("predDist_Puppi_SR_dRapHi_0btag_JetY_pred"         );
    histnames.push_back("predDist_Puppi_SR_dRapHi_0btag_JetSDmass_pred"    );
    histnames.push_back("predDist_Puppi_SR_dRapHi_0btag_JetTau32_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapHi_0btag_maxbdisc_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapHi_1btag_DijetMass_pred"    );
    histnames.push_back("predDist_Puppi_SR_dRapHi_1btag_DijetMassMod_pred" );
    histnames.push_back("predDist_Puppi_SR_dRapHi_1btag_HT_pred"           );
    histnames.push_back("predDist_Puppi_SR_dRapHi_1btag_DeltaRap_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapHi_1btag_JetP_pred"         );
    histnames.push_back("predDist_Puppi_SR_dRapHi_1btag_JetPt_pred"        );
    histnames.push_back("predDist_Puppi_SR_dRapHi_1btag_JetY_pred"         );
    histnames.push_back("predDist_Puppi_SR_dRapHi_1btag_JetSDmass_pred"    );
    histnames.push_back("predDist_Puppi_SR_dRapHi_1btag_JetTau32_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapHi_1btag_maxbdisc_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapHi_2btag_DijetMass_pred"    );
    histnames.push_back("predDist_Puppi_SR_dRapHi_2btag_DijetMassMod_pred" );
    histnames.push_back("predDist_Puppi_SR_dRapHi_2btag_HT_pred"           );
    histnames.push_back("predDist_Puppi_SR_dRapHi_2btag_DeltaRap_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapHi_2btag_JetP_pred"         );
    histnames.push_back("predDist_Puppi_SR_dRapHi_2btag_JetPt_pred"        );
    histnames.push_back("predDist_Puppi_SR_dRapHi_2btag_JetY_pred"         );
    histnames.push_back("predDist_Puppi_SR_dRapHi_2btag_JetSDmass_pred"    );
    histnames.push_back("predDist_Puppi_SR_dRapHi_2btag_JetTau32_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapHi_2btag_maxbdisc_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapHi_inclu_DijetMass_pred"    );
    histnames.push_back("predDist_Puppi_SR_dRapHi_inclu_DijetMassMod_pred" );
    histnames.push_back("predDist_Puppi_SR_dRapHi_inclu_HT_pred"           );
    histnames.push_back("predDist_Puppi_SR_dRapHi_inclu_DeltaRap_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapHi_inclu_JetP_pred"         );
    histnames.push_back("predDist_Puppi_SR_dRapHi_inclu_JetPt_pred"        );
    histnames.push_back("predDist_Puppi_SR_dRapHi_inclu_JetY_pred"         );
    histnames.push_back("predDist_Puppi_SR_dRapHi_inclu_JetSDmass_pred"    );
    histnames.push_back("predDist_Puppi_SR_dRapHi_inclu_JetTau32_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapHi_inclu_maxbdisc_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapLo_0btag_DijetMass_pred"    );
    histnames.push_back("predDist_Puppi_SR_dRapLo_0btag_DijetMassMod_pred" );
    histnames.push_back("predDist_Puppi_SR_dRapLo_0btag_HT_pred"           );
    histnames.push_back("predDist_Puppi_SR_dRapLo_0btag_DeltaRap_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapLo_0btag_JetP_pred"         );
    histnames.push_back("predDist_Puppi_SR_dRapLo_0btag_JetPt_pred"        );
    histnames.push_back("predDist_Puppi_SR_dRapLo_0btag_JetY_pred"         );
    histnames.push_back("predDist_Puppi_SR_dRapLo_0btag_JetSDmass_pred"    );
    histnames.push_back("predDist_Puppi_SR_dRapLo_0btag_JetTau32_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapLo_0btag_maxbdisc_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapLo_1btag_DijetMass_pred"    );
    histnames.push_back("predDist_Puppi_SR_dRapLo_1btag_DijetMassMod_pred" );
    histnames.push_back("predDist_Puppi_SR_dRapLo_1btag_HT_pred"           );
    histnames.push_back("predDist_Puppi_SR_dRapLo_1btag_DeltaRap_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapLo_1btag_JetP_pred"         );
    histnames.push_back("predDist_Puppi_SR_dRapLo_1btag_JetPt_pred"        );
    histnames.push_back("predDist_Puppi_SR_dRapLo_1btag_JetY_pred"         );
    histnames.push_back("predDist_Puppi_SR_dRapLo_1btag_JetSDmass_pred"    );
    histnames.push_back("predDist_Puppi_SR_dRapLo_1btag_JetTau32_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapLo_1btag_maxbdisc_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapLo_2btag_DijetMass_pred"    );
    histnames.push_back("predDist_Puppi_SR_dRapLo_2btag_DijetMassMod_pred" );
    histnames.push_back("predDist_Puppi_SR_dRapLo_2btag_HT_pred"           );
    histnames.push_back("predDist_Puppi_SR_dRapLo_2btag_DeltaRap_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapLo_2btag_JetP_pred"         );
    histnames.push_back("predDist_Puppi_SR_dRapLo_2btag_JetPt_pred"        );
    histnames.push_back("predDist_Puppi_SR_dRapLo_2btag_JetY_pred"         );
    histnames.push_back("predDist_Puppi_SR_dRapLo_2btag_JetSDmass_pred"    );
    histnames.push_back("predDist_Puppi_SR_dRapLo_2btag_JetTau32_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapLo_2btag_maxbdisc_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapLo_inclu_DijetMass_pred"    );
    histnames.push_back("predDist_Puppi_SR_dRapLo_inclu_DijetMassMod_pred" );
    histnames.push_back("predDist_Puppi_SR_dRapLo_inclu_HT_pred"           );
    histnames.push_back("predDist_Puppi_SR_dRapLo_inclu_DeltaRap_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapLo_inclu_JetP_pred"         );
    histnames.push_back("predDist_Puppi_SR_dRapLo_inclu_JetPt_pred"        );
    histnames.push_back("predDist_Puppi_SR_dRapLo_inclu_JetY_pred"         );
    histnames.push_back("predDist_Puppi_SR_dRapLo_inclu_JetSDmass_pred"    );
    histnames.push_back("predDist_Puppi_SR_dRapLo_inclu_JetTau32_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapLo_inclu_maxbdisc_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapIn_0btag_DijetMass_pred"    );
    histnames.push_back("predDist_Puppi_SR_dRapIn_0btag_DijetMassMod_pred" );
    histnames.push_back("predDist_Puppi_SR_dRapIn_0btag_HT_pred"           );
    histnames.push_back("predDist_Puppi_SR_dRapIn_0btag_DeltaRap_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapIn_0btag_JetP_pred"         );
    histnames.push_back("predDist_Puppi_SR_dRapIn_0btag_JetPt_pred"        );
    histnames.push_back("predDist_Puppi_SR_dRapIn_0btag_JetY_pred"         );
    histnames.push_back("predDist_Puppi_SR_dRapIn_0btag_JetSDmass_pred"    );
    histnames.push_back("predDist_Puppi_SR_dRapIn_0btag_JetTau32_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapIn_0btag_maxbdisc_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapIn_1btag_DijetMass_pred"    );
    histnames.push_back("predDist_Puppi_SR_dRapIn_1btag_DijetMassMod_pred" );
    histnames.push_back("predDist_Puppi_SR_dRapIn_1btag_HT_pred"           );
    histnames.push_back("predDist_Puppi_SR_dRapIn_1btag_DeltaRap_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapIn_1btag_JetP_pred"         );
    histnames.push_back("predDist_Puppi_SR_dRapIn_1btag_JetPt_pred"        );
    histnames.push_back("predDist_Puppi_SR_dRapIn_1btag_JetY_pred"         );
    histnames.push_back("predDist_Puppi_SR_dRapIn_1btag_JetSDmass_pred"    );
    histnames.push_back("predDist_Puppi_SR_dRapIn_1btag_JetTau32_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapIn_1btag_maxbdisc_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapIn_2btag_DijetMass_pred"    );
    histnames.push_back("predDist_Puppi_SR_dRapIn_2btag_DijetMassMod_pred" );
    histnames.push_back("predDist_Puppi_SR_dRapIn_2btag_HT_pred"           );
    histnames.push_back("predDist_Puppi_SR_dRapIn_2btag_DeltaRap_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapIn_2btag_JetP_pred"         );
    histnames.push_back("predDist_Puppi_SR_dRapIn_2btag_JetPt_pred"        );
    histnames.push_back("predDist_Puppi_SR_dRapIn_2btag_JetY_pred"         );
    histnames.push_back("predDist_Puppi_SR_dRapIn_2btag_JetSDmass_pred"    );
    histnames.push_back("predDist_Puppi_SR_dRapIn_2btag_JetTau32_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapIn_2btag_maxbdisc_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapIn_inclu_DijetMass_pred"    );
    histnames.push_back("predDist_Puppi_SR_dRapIn_inclu_DijetMassMod_pred" );
    histnames.push_back("predDist_Puppi_SR_dRapIn_inclu_HT_pred"           );
    histnames.push_back("predDist_Puppi_SR_dRapIn_inclu_DeltaRap_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapIn_inclu_JetP_pred"         );
    histnames.push_back("predDist_Puppi_SR_dRapIn_inclu_JetPt_pred"        );
    histnames.push_back("predDist_Puppi_SR_dRapIn_inclu_JetY_pred"         );
    histnames.push_back("predDist_Puppi_SR_dRapIn_inclu_JetSDmass_pred"    );
    histnames.push_back("predDist_Puppi_SR_dRapIn_inclu_JetTau32_pred"     );
    histnames.push_back("predDist_Puppi_SR_dRapIn_inclu_maxbdisc_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_0btag_DijetMass_pred"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_0btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_0btag_HT_pred"           );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_0btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_0btag_JetP_pred"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_0btag_JetPt_pred"        );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_0btag_JetY_pred"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_0btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_0btag_JetTau32_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_0btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_1btag_DijetMass_pred"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_1btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_1btag_HT_pred"           );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_1btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_1btag_JetP_pred"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_1btag_JetPt_pred"        );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_1btag_JetY_pred"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_1btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_1btag_JetTau32_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_1btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_2btag_DijetMass_pred"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_2btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_2btag_HT_pred"           );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_2btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_2btag_JetP_pred"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_2btag_JetPt_pred"        );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_2btag_JetY_pred"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_2btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_2btag_JetTau32_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_2btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_inclu_DijetMass_pred"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_inclu_DijetMassMod_pred" );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_inclu_HT_pred"           );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_inclu_DeltaRap_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_inclu_JetP_pred"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_inclu_JetPt_pred"        );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_inclu_JetY_pred"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_inclu_JetSDmass_pred"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_inclu_JetTau32_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapHi_inclu_maxbdisc_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_0btag_DijetMass_pred"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_0btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_0btag_HT_pred"           );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_0btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_0btag_JetP_pred"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_0btag_JetPt_pred"        );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_0btag_JetY_pred"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_0btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_0btag_JetTau32_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_0btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_1btag_DijetMass_pred"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_1btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_1btag_HT_pred"           );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_1btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_1btag_JetP_pred"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_1btag_JetPt_pred"        );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_1btag_JetY_pred"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_1btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_1btag_JetTau32_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_1btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_2btag_DijetMass_pred"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_2btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_2btag_HT_pred"           );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_2btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_2btag_JetP_pred"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_2btag_JetPt_pred"        );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_2btag_JetY_pred"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_2btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_2btag_JetTau32_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_2btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_inclu_DijetMass_pred"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_inclu_DijetMassMod_pred" );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_inclu_HT_pred"           );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_inclu_DeltaRap_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_inclu_JetP_pred"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_inclu_JetPt_pred"        );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_inclu_JetY_pred"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_inclu_JetSDmass_pred"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_inclu_JetTau32_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapLo_inclu_maxbdisc_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_0btag_DijetMass_pred"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_0btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_0btag_HT_pred"           );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_0btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_0btag_JetP_pred"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_0btag_JetPt_pred"        );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_0btag_JetY_pred"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_0btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_0btag_JetTau32_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_0btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_1btag_DijetMass_pred"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_1btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_1btag_HT_pred"           );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_1btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_1btag_JetP_pred"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_1btag_JetPt_pred"        );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_1btag_JetY_pred"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_1btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_1btag_JetTau32_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_1btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_2btag_DijetMass_pred"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_2btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_2btag_HT_pred"           );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_2btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_2btag_JetP_pred"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_2btag_JetPt_pred"        );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_2btag_JetY_pred"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_2btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_2btag_JetTau32_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_2btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_inclu_DijetMass_pred"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_inclu_DijetMassMod_pred" );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_inclu_HT_pred"           );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_inclu_DeltaRap_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_inclu_JetP_pred"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_inclu_JetPt_pred"        );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_inclu_JetY_pred"         );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_inclu_JetSDmass_pred"    );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_inclu_JetTau32_pred"     );
    // histnames.push_back("predDist_Puppi_SB1_dRapIn_inclu_maxbdisc_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_0btag_DijetMass_pred"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_0btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_0btag_HT_pred"           );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_0btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_0btag_JetP_pred"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_0btag_JetPt_pred"        );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_0btag_JetY_pred"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_0btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_0btag_JetTau32_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_0btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_1btag_DijetMass_pred"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_1btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_1btag_HT_pred"           );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_1btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_1btag_JetP_pred"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_1btag_JetPt_pred"        );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_1btag_JetY_pred"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_1btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_1btag_JetTau32_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_1btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_2btag_DijetMass_pred"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_2btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_2btag_HT_pred"           );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_2btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_2btag_JetP_pred"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_2btag_JetPt_pred"        );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_2btag_JetY_pred"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_2btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_2btag_JetTau32_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_2btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_inclu_DijetMass_pred"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_inclu_DijetMassMod_pred" );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_inclu_HT_pred"           );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_inclu_DeltaRap_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_inclu_JetP_pred"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_inclu_JetPt_pred"        );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_inclu_JetY_pred"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_inclu_JetSDmass_pred"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_inclu_JetTau32_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapHi_inclu_maxbdisc_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_0btag_DijetMass_pred"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_0btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_0btag_HT_pred"           );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_0btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_0btag_JetP_pred"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_0btag_JetPt_pred"        );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_0btag_JetY_pred"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_0btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_0btag_JetTau32_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_0btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_1btag_DijetMass_pred"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_1btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_1btag_HT_pred"           );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_1btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_1btag_JetP_pred"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_1btag_JetPt_pred"        );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_1btag_JetY_pred"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_1btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_1btag_JetTau32_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_1btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_2btag_DijetMass_pred"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_2btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_2btag_HT_pred"           );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_2btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_2btag_JetP_pred"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_2btag_JetPt_pred"        );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_2btag_JetY_pred"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_2btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_2btag_JetTau32_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_2btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_inclu_DijetMass_pred"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_inclu_DijetMassMod_pred" );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_inclu_HT_pred"           );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_inclu_DeltaRap_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_inclu_JetP_pred"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_inclu_JetPt_pred"        );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_inclu_JetY_pred"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_inclu_JetSDmass_pred"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_inclu_JetTau32_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapLo_inclu_maxbdisc_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_0btag_DijetMass_pred"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_0btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_0btag_HT_pred"           );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_0btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_0btag_JetP_pred"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_0btag_JetPt_pred"        );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_0btag_JetY_pred"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_0btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_0btag_JetTau32_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_0btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_1btag_DijetMass_pred"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_1btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_1btag_HT_pred"           );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_1btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_1btag_JetP_pred"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_1btag_JetPt_pred"        );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_1btag_JetY_pred"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_1btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_1btag_JetTau32_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_1btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_2btag_DijetMass_pred"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_2btag_DijetMassMod_pred" );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_2btag_HT_pred"           );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_2btag_DeltaRap_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_2btag_JetP_pred"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_2btag_JetPt_pred"        );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_2btag_JetY_pred"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_2btag_JetSDmass_pred"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_2btag_JetTau32_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_2btag_maxbdisc_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_inclu_DijetMass_pred"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_inclu_DijetMassMod_pred" );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_inclu_HT_pred"           );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_inclu_DeltaRap_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_inclu_JetP_pred"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_inclu_JetPt_pred"        );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_inclu_JetY_pred"         );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_inclu_JetSDmass_pred"    );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_inclu_JetTau32_pred"     );
    // histnames.push_back("predDist_Puppi_SB2_dRapIn_inclu_maxbdisc_pred"     );      


  }

  // ModMass plots
  if (j==3){
    histnames.push_back("h_mAK8_ModMass");
    histnames.push_back("h_mAK8_ModMass_jet0");
    histnames.push_back("h_mAK8_ModMass_jet1");
    histnames.push_back("h_mSDropAK8_ModMass");
    histnames.push_back("h_mSDropAK8_ModMass_jet0");
    histnames.push_back("h_mSDropAK8_ModMass_jet1");
    histnames.push_back("h_mSDropAK8_AltTag_ModMass");       
    histnames.push_back("h_mSDropAK8_AltTag_ModMass_jet0");  
    histnames.push_back("h_mSDropAK8_AltTag_ModMass_jet1");  
    histnames.push_back("h_mSDropAK8_AltTag2_ModMass");       
    histnames.push_back("h_mSDropAK8_AltTag2_ModMass_jet0");  
    histnames.push_back("h_mSDropAK8_AltTag2_ModMass_jet1");  
    histnames.push_back("h_mPuppiSDropAK8_ModMass");
    histnames.push_back("h_mPuppiSDropAK8_ModMass_jet0");
    histnames.push_back("h_mPuppiSDropAK8_ModMass_jet1");
    histnames.push_back("h_mPuppiSDropAK8_AltTag_ModMass");
    histnames.push_back("h_mPuppiSDropAK8_AltTag_ModMass_jet0");
    histnames.push_back("h_mPuppiSDropAK8_AltTag_ModMass_jet1");
    histnames.push_back("h_mPuppiSDropAK8_AltTag2_ModMass");
    histnames.push_back("h_mPuppiSDropAK8_AltTag2_ModMass_jet0");
    histnames.push_back("h_mPuppiSDropAK8_AltTag2_ModMass_jet1");
    // histnames.push_back("h_pT_mSDropAK8_ModMass");               
    // histnames.push_back("h_pT_mSDropAK8_ModMass_jet0");          
    // histnames.push_back("h_pT_mSDropAK8_ModMass_jet1");          
    // histnames.push_back("h_pT_mSDropAK8_AltTag_ModMass");        
    // histnames.push_back("h_pT_mSDropAK8_AltTag_ModMass_jet0");   
    // histnames.push_back("h_pT_mSDropAK8_AltTag_ModMass_jet1");   
    histnames.push_back("h_pT_mPuppiSDropAK8_ModMass");          
    histnames.push_back("h_pT_mPuppiSDropAK8_ModMass_jet0");     
    histnames.push_back("h_pT_mPuppiSDropAK8_ModMass_jet1");           
    histnames.push_back("h_pT_mPuppiSDropAK8_AltTag_ModMass");          
    histnames.push_back("h_pT_mPuppiSDropAK8_AltTag_ModMass_jet0");     
    histnames.push_back("h_pT_mPuppiSDropAK8_AltTag_ModMass_jet1");     
    histnames.push_back("h_pT_mPuppiSDropAK8_AltTag2_ModMass");         
    histnames.push_back("h_pT_mPuppiSDropAK8_AltTag2_ModMass_jet0");    
    histnames.push_back("h_pT_mPuppiSDropAK8_AltTag2_ModMass_jet1");    
    histnames.push_back("h_p_mPuppiSDropAK8_ModMass");                 
    histnames.push_back("h_p_mPuppiSDropAK8_ModMass_jet0");            
    histnames.push_back("h_p_mPuppiSDropAK8_ModMass_jet1");                  
    histnames.push_back("h_p_mPuppiSDropAK8_AltTag_ModMass");            
    histnames.push_back("h_p_mPuppiSDropAK8_AltTag_ModMass_jet0");       
    histnames.push_back("h_p_mPuppiSDropAK8_AltTag_ModMass_jet1");       
    histnames.push_back("h_p_mPuppiSDropAK8_AltTag2_ModMass");           
    histnames.push_back("h_p_mPuppiSDropAK8_AltTag2_ModMass_jet0");      
    histnames.push_back("h_p_mPuppiSDropAK8_AltTag2_ModMass_jet1");      


  }

  //runPt(histnames, j, datelabel);
  runHT(histnames, j, datelabel);
  cout<<"exit"<<endl;
  return;
}


