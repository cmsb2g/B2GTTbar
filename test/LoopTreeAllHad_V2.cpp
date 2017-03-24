// ** Edit top-tag window if it has changed
// root[] .L LoopTreeAllHad_V2.cpp++
// root[] run("BCD","20161206addHist", 1, 0)  // dataset, savelabel, run looptree, run looptree_trig

//To-do:
//Update scale factors
//Update b-tag efficiency
//Update top-tag working points

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <TTree.h>
#include <TH1F.h>
#include <TH2F.h>
#include <sstream>
#include <TFile.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TROOT.h>
#include <TColor.h>
#include <TRandom3.h>
#include <cmath>
#include "TMath.h"
#include <TSystem.h>
#include <TLorentzVector.h>
#include <TVector3.h>

// --- Predicted Distribution
#include "Analysis/PredictedDistribution/interface/PredictedDistribution.h"

// --- btag SF
//#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
//#include "CondTools/BTau/interface/BTagCalibration2Reader.h"
// without CMSSW / standalone:
#include "BTagCalibrationStandalone.h"



// --- Function Declaration
// vector<string>  makeFileList  (string);
void            looptree_trig (string, string, string, string, float, float, float);
void            looptree      (string, string, string, string, float, float, float, float, float, string, bool, bool, bool, bool, bool, bool, bool, bool, bool,int, int, bool);
bool            applySF       (bool, float, float);
void            run1file      (string, bool, string);

// --- Analysis

// example: run("BCD", "20161205addHisto", 1, 1)
void run(string dataset_shortname = "none", string savelabel = "", bool runLoopTree = 1, bool runLoopTree_trig = 0)
{
  std::size_t foundB   = dataset_shortname.find( "B"   );
  std::size_t foundC   = dataset_shortname.find( "C"   );
  std::size_t foundD   = dataset_shortname.find( "D"   );
  std::size_t foundE   = dataset_shortname.find( "E"   );
  std::size_t foundF   = dataset_shortname.find( "F"   );
  std::size_t foundG   = dataset_shortname.find( "G"   );
  std::size_t foundH   = dataset_shortname.find( "H"   );
  std::size_t foundQ   = dataset_shortname.find( "Q"   );
  std::size_t foundTT1 = dataset_shortname.find( "TT1" );
  std::size_t foundTT2 = dataset_shortname.find( "TT2" );
  std::size_t foundZP  = dataset_shortname.find( "ZP"  );
  std::size_t foundNone  = dataset_shortname.find( "none"  );

  if ( foundB   !=std::string::npos ) { cout<<"JetHT_Run2016B queued"<<endl; }
  if ( foundC   !=std::string::npos ) { cout<<"JetHT_Run2016C queued"<<endl; }
  if ( foundD   !=std::string::npos ) { cout<<"JetHT_Run2016D queued"<<endl; }
  if ( foundE   !=std::string::npos ) { cout<<"JetHT_Run2016E queued"<<endl; }
  if ( foundF   !=std::string::npos ) { cout<<"JetHT_Run2016F queued"<<endl; }
  if ( foundG   !=std::string::npos ) { cout<<"JetHT_Run2016G queued"<<endl; }
  if ( foundH   !=std::string::npos ) { cout<<"JetHT_Run2016H queued"<<endl; }
  if ( foundQ   !=std::string::npos ) { cout<<"QCD queued"           <<endl; }
  if ( foundTT1 !=std::string::npos ) { cout<<"ttbar MT1 queued"     <<endl; }
  if ( foundTT2 !=std::string::npos ) { cout<<"ttbar MT2 queued"     <<endl; }
  if ( foundZP  !=std::string::npos ) { cout<<"all Zprime queued"    <<endl; }
  if ( foundNone  !=std::string::npos ) { cout<<"No input dataset provided" <<endl; return; }

  if (savelabel=="" && runLoopTree) {cout<<"please provide a unique label for the savefile. example: run(\"BCD\",\"20161201addHist\",1,0)"<<endl; return;}

  string date = "20170320";

  string folder_input_tree = "/uscmst1b_scratch/lpc1/lpcphys/jdolen/B2G2016/V5/";
  string folder_input_tree_Zprime ="root://cmseos.fnal.gov//store/user/camclean/B2GAnaFW/Trees/80X_V4/";
  string folder_mistag     = "/uscms_data/d2/jdolen/B2G2016/CMSSW_8_0_22/src/Analysis/B2GTTbar/test/";
  string folder_modMass    = "/uscms/home/camclean/nobackup/CMSSW_8_0_13/src/Analysis/B2GTTbar/test/runs/run20161010/";
  string mistag_file_data  = folder_mistag + "MistagRate_nbins_11_20161206test1_nom_data_subtract_ttbar.root";
  string mistag_file_QCD   = folder_mistag + "MistagRate_nbins_11_20161206test1_nom_QCDMC.root";
  string modmass_file      = folder_modMass+ "ModMass_Jetpt600HT1000_20161010_b2gtree_QCD_Pt_300toInf_pythia8_RunIISpring16MiniAODv2_reHLT_V3.root";


  // string savelabel = "20161206test1";
  float ttagSDwindowLo = 110. ;
  float ttagSDwindowHi = 210. ;
  float ttagTau32cut   = 0.69 ;
  float cut_pt_AK8     = 500  ;
  float cut_HT         = 1000 ; 
  
  //--- Analysis 
  vector<string> input_folder;
  vector<string> file_name_tree;
  vector<bool> file_is_data;
  vector<bool> file_is_QCDMC;

  //--- JetHT B-H
  if ( foundB   !=std::string::npos ){
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016B_03Feb2017_ver2_v2_JSONfinal_try2_0000.root");     file_is_data.push_back(true);     file_is_QCDMC.push_back(false);                      
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016B_03Feb2017_ver2_v2_JSONfinal_try2_0001.root");     file_is_data.push_back(true);     file_is_QCDMC.push_back(false);                      
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016B_03Feb2017_ver2_v2_JSONfinal_try2_0002.root");     file_is_data.push_back(true);     file_is_QCDMC.push_back(false);                      
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016B_03Feb2017_ver2_v2_JSONfinal_try2_0003.root");     file_is_data.push_back(true);     file_is_QCDMC.push_back(false);                      
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016B_03Feb2017_ver2_v2_JSONfinal_try2_0004.root");     file_is_data.push_back(true);     file_is_QCDMC.push_back(false);                      
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016B_03Feb2017_ver2_v2_JSONfinal_try2_0005.root");     file_is_data.push_back(true);     file_is_QCDMC.push_back(false);                      
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016B_03Feb2017_ver2_v2_JSONfinal_try2_0006.root");     file_is_data.push_back(true);     file_is_QCDMC.push_back(false);                      
  }
  if ( foundC   !=std::string::npos ){
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016C_03Feb2017_v1_JSONfinal_0000.root");              file_is_data.push_back(true);     file_is_QCDMC.push_back(false); 
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016C_03Feb2017_v1_JSONfinal_0001.root");              file_is_data.push_back(true);     file_is_QCDMC.push_back(false); 
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016C_03Feb2017_v1_JSONfinal_0002.root");              file_is_data.push_back(true);     file_is_QCDMC.push_back(false); 
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016C_03Feb2017_v1_JSONfinal_0003.root");              file_is_data.push_back(true);     file_is_QCDMC.push_back(false); 
  }
  if ( foundD   !=std::string::npos ){
    /*input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016D_03Feb2017_v1_JSONfinal_0000.root");             file_is_data.push_back(true);     file_is_QCDMC.push_back(false);                 
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016D_03Feb2017_v1_JSONfinal_0001.root");             file_is_data.push_back(true);     file_is_QCDMC.push_back(false);                 
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016D_03Feb2017_v1_JSONfinal_0002.root");             file_is_data.push_back(true);     file_is_QCDMC.push_back(false);                 
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016D_03Feb2017_v1_JSONfinal_0003.root");             file_is_data.push_back(true);     file_is_QCDMC.push_back(false);*/                 
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016D_03Feb2017_v1_JSONfinal_0004.root");             file_is_data.push_back(true);     file_is_QCDMC.push_back(false);                 
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016D_03Feb2017_v1_JSONfinal_0005.root");             file_is_data.push_back(true);     file_is_QCDMC.push_back(false);                 
  }
  if ( foundE   !=std::string::npos ){
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("b2gtreeV5_JetHT_Run2016E_03Feb2017_v1_JSONfinal_REDO_all.root");             file_is_data.push_back(true);     file_is_QCDMC.push_back(false); 
  }                
  if ( foundF   !=std::string::npos ){
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016F_03Feb2017_v1_JSONfinal_try2_0000.root");              file_is_data.push_back(true);     file_is_QCDMC.push_back(false);      
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016F_03Feb2017_v1_JSONfinal_try2_0001.root");              file_is_data.push_back(true);     file_is_QCDMC.push_back(false);      
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016F_03Feb2017_v1_JSONfinal_try2_0002.root");              file_is_data.push_back(true);     file_is_QCDMC.push_back(false);      
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016F_03Feb2017_v1_JSONfinal_try2_0003.root");              file_is_data.push_back(true);     file_is_QCDMC.push_back(false);      
  }           
  if ( foundG   !=std::string::npos ){
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016G_03Feb2017_v1_JSONfinal_0001.root");             file_is_data.push_back(true);     file_is_QCDMC.push_back(false);            
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016G_03Feb2017_v1_JSONfinal_0002.root");             file_is_data.push_back(true);     file_is_QCDMC.push_back(false);            
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016G_03Feb2017_v1_JSONfinal_0003.root");             file_is_data.push_back(true);     file_is_QCDMC.push_back(false);            
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016G_03Feb2017_v1_JSONfinal_0004.root");             file_is_data.push_back(true);     file_is_QCDMC.push_back(false);            
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016G_03Feb2017_v1_JSONfinal_0005.root");             file_is_data.push_back(true);     file_is_QCDMC.push_back(false);            
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016G_03Feb2017_v1_JSONfinal_0006.root");             file_is_data.push_back(true);     file_is_QCDMC.push_back(false);            
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016G_03Feb2017_v1_JSONfinal_0007.root");             file_is_data.push_back(true);     file_is_QCDMC.push_back(false);            
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016G_03Feb2017_v1_JSONfinal_0008.root");             file_is_data.push_back(true);     file_is_QCDMC.push_back(false);            
  }
  if ( foundH   !=std::string::npos ){            
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016H_03Feb2017_ver2_v1_JSONfinal_0000.root");            file_is_data.push_back(true);     file_is_QCDMC.push_back(false);               
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016H_03Feb2017_ver2_v1_JSONfinal_0001.root");            file_is_data.push_back(true);     file_is_QCDMC.push_back(false);               
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016H_03Feb2017_ver2_v1_JSONfinal_0002.root");            file_is_data.push_back(true);     file_is_QCDMC.push_back(false);               
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016H_03Feb2017_ver2_v1_JSONfinal_0003.root");            file_is_data.push_back(true);     file_is_QCDMC.push_back(false);               
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016H_03Feb2017_ver2_v1_JSONfinal_0004.root");            file_is_data.push_back(true);     file_is_QCDMC.push_back(false);               
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016H_03Feb2017_ver2_v1_JSONfinal_0005.root");            file_is_data.push_back(true);     file_is_QCDMC.push_back(false);               
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016H_03Feb2017_ver2_v1_JSONfinal_0006.root");            file_is_data.push_back(true);     file_is_QCDMC.push_back(false);               
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016H_03Feb2017_ver2_v1_JSONfinal_0007.root");            file_is_data.push_back(true);     file_is_QCDMC.push_back(false);               
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016H_03Feb2017_ver2_v1_JSONfinal_0008.root");            file_is_data.push_back(true);     file_is_QCDMC.push_back(false);               
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016H_03Feb2017_ver2_v1_JSONfinal_0009.root");            file_is_data.push_back(true);     file_is_QCDMC.push_back(false);               
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("crab_b2gtreeV5_JetHT_Run2016H_03Feb2017_ver3_v1_JSONfinal_try2_all.root");            file_is_data.push_back(true);     file_is_QCDMC.push_back(false);               
  }                           
  //--- QCD HT binned
  if ( foundQ   !=std::string::npos ){            
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("");             file_is_data.push_back(false);     file_is_QCDMC.push_back(true);                              
  }
  //--- TTbar 
  if ( foundTT1   !=std::string::npos ){            
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("");  file_is_data.push_back(false);     file_is_QCDMC.push_back(false);              
  }  
  if ( foundTT2   !=std::string::npos ){            
    input_folder.push_back(folder_input_tree); file_name_tree.push_back("");            file_is_data.push_back(false);     file_is_QCDMC.push_back(false);    
  }

  //--- Z Prime
  if (foundZP   !=std::string::npos ){
    input_folder.push_back(folder_input_tree_Zprime); file_name_tree.push_back(""); file_is_data.push_back(false);     file_is_QCDMC.push_back(false);
  }

  bool isFrozen            = true ;
  bool runAntiTag          = false  ;
  bool runKinematic        = false  ;
  bool runbkgdEst          = true  ;
  bool do_PUreweighting    = true  ;
  bool do_HTreweighting    = false ;
  bool do_ttbarReweighting = false ;

  
  // Loop over file_name_tree and make histograms for each
  for (unsigned int i=0; i<file_name_tree.size(); i++){

    if (runLoopTree){
      string mistag_file;
      if (file_is_QCDMC[i]) mistag_file = mistag_file_QCD ;
      else                  mistag_file = mistag_file_data;
      cout<<"Using Mistag File: "<<mistag_file<<endl;
      looptree( 
	       folder_input_tree, 
	       file_name_tree[i], 
	       modmass_file, mistag_file,
	       cut_pt_AK8, cut_HT, ttagSDwindowLo, ttagSDwindowHi, ttagTau32cut, 
	       savelabel            , // string insert in savefile name
	       file_is_QCDMC[i]     , // bool is QCDMC? (modMass plots)
	       file_is_data[i]      , // bool is Data? 
	       isFrozen             , // bool is Frozen?
	       runAntiTag           , // bool run antitag?
	       runKinematic         , // bool run kinematic?
	       runbkgdEst           , // bool run bkgdest?
	       do_PUreweighting     , // bool do PUreweighting    ?
	       do_HTreweighting     , // bool do HTreweighting    ?
	       do_ttbarReweighting  , // bool do ttbarReweighting ?
	       0                    , // int Systematics: 0 = nom , 1/-1 = jec_up/dn , 2/-2 = jer_up/dn , 3/-3 = btag_up/btag , 4/-4 = pdf_up/dn , 5/-5 = q2_up/dn , 6/-6 = PU_up/dn 
	       -1                   , // int Nevents (set to -1 for all events)
	       false                  // bool verbose
		);
    } // end if (runLoopTree)

    if (runLoopTree_trig){
      looptree_trig(
		    input_folder[i],
		    file_name_tree[i],
		    date,
		    "trigEffStudies/run"+date+"/",
		    ttagSDwindowLo, ttagSDwindowHi, ttagTau32cut
		    );
    } // end if (runLoopTree_trig)
  } // end file loop
}// end run()


// example: run1file("b2gtreeV4_JetHT_Run2016H-PromptReco-v3_JSONnov14_all.root", true, "20161206test4")
void run1file(string filename, bool isData, string savelabel){
  bool isQCDMC             = false ;
  bool isFrozen            = true ;
  bool runAntiTag          = true  ;
  bool runKinematic        = true  ;
  bool runbkgdEst          = false ;
  bool do_PUreweighting    = true  ;
  bool do_HTreweighting    = false ;
  bool do_ttbarReweighting = false ;

  string folder_input_tree = "/uscmst1b_scratch/lpc1/lpcphys/jdolen/B2G2016/V4/";
  string folder_mistag     = "/uscms/home/camclean/nobackup/CMSSW_8_0_13/src/Analysis/B2GTTbar/test/runs/run20161010/";
  string folder_modMass    = "/uscms/home/camclean/nobackup/CMSSW_8_0_13/src/Analysis/B2GTTbar/test/runs/run20161010/";
  string mistag_file_data  = folder_mistag + "MistagRate_nbins_092516_14_ttbar_Subtract_histsAllHad_Jetpt600HT1000_20161010_b2gtree_JetHT_combined.root";
  string mistag_file_QCD   = folder_mistag + "MistagRate_nbins_092516_14_MC_histsAllHad_Jetpt600HT1000_20161010_b2gtree_QCD_Pt_300toInf_pythia8_RunIISpring16MiniAODv2_reHLT_V3.root";
  string modmass_file      = folder_modMass+ "ModMass_Jetpt600HT1000_20161010_b2gtree_QCD_Pt_300toInf_pythia8_RunIISpring16MiniAODv2_reHLT_V3.root";

  // string savelabel = "20161206test1";
  float ttagSDwindowLo = 110. ;
  float ttagSDwindowHi = 210. ;
  float ttagTau32cut   = 0.69 ;
  float cut_pt_AK8     = 500  ;
  float cut_HT         = 1000 ; 
  
  
  looptree( 
        folder_input_tree, 
        filename, 
        modmass_file, mistag_file_data,
        cut_pt_AK8, cut_HT, ttagSDwindowLo, ttagSDwindowHi, ttagTau32cut, 
        savelabel            , // string insert in savefile name
        isQCDMC              , // bool is QCDMC? (modMass plots)
        isData               , // bool is Data? 
        isFrozen             , // bool is Frozen?
        runAntiTag           , // bool run antitag?
        runKinematic         , // bool run kinematic?
        runbkgdEst           , // bool run bkgdest?
        do_PUreweighting     , // bool do PUreweighting    ?
        do_HTreweighting     , // bool do HTreweighting    ?
        do_ttbarReweighting  , // bool do ttbarReweighting ?
        0                    , // int Systematics: 0 = nom , 1/-1 = jec_up/dn , 2/-2 = jer_up/dn , 3/-3 = btag_up/btag , 4/-4 = pdf_up/dn , 5/-5 = q2_up/dn , 6/-6 = PU_up/dn 
        -1                   , // int Nevents (set to -1 for all events)
        false                  // bool verbose
    );

}// end run1file()




void looptree_trig(
          string input_folder, 
          string input_file, 
          string date, 
          string output_folder, 
          float topTagSDwindowLo, 
          float topTagSDwindowHi, 
          float topTagTau32cut
		   )
{
  
  string file_name =  input_folder + input_file;
  cout<<"opening "<<file_name<<endl;
  TFile *F1   = TFile::Open(file_name.c_str() );

  // Get Tree entries
  Float_t Jet0SDmassRaw         ;
  Float_t Jet1SDmassRaw         ;
  Float_t Jet0PuppiSDmassRaw         ;
  Float_t Jet1PuppiSDmassRaw         ;
  Float_t Jet0MassRaw           ;
  Float_t Jet1MassRaw           ;
  Float_t Jet0PtRaw             ;
  Float_t Jet1PtRaw             ;
  Float_t Jet0EtaRaw             ;
  Float_t Jet1EtaRaw             ;
  Float_t Jet0PhiRaw             ;
  Float_t Jet1PhiRaw             ;
  
  Float_t Jet0CorrFactor;
  Float_t Jet1CorrFactor;
  Float_t Jet0MassCorrFactor;
  Float_t Jet1MassCorrFactor;
  Float_t Jet0PtSmearFactor;
  Float_t Jet1PtSmearFactor;

  Float_t Jet0PuppiCorrFactor;
  Float_t Jet1PuppiCorrFactor;
  Float_t Jet0PuppiPtSmearFactor;
  Float_t Jet1PuppiPtSmearFactor;
  
  Float_t Jet0Tau32          ;
  Float_t Jet1Tau32          ;
  Float_t HT                 ;
  std::string *AllHadTrigAcceptBits = new std::string;

  TTree *T1    = (TTree*)  F1     ->Get("ana/TreeAllHad");

  double treeNentries = T1->GetEntries();
  cout<<"treeNentries = "<< treeNentries <<endl;

  T1->SetBranchAddress("Jet0SDmassRaw"                                      , & Jet0SDmassRaw                                    );
  T1->SetBranchAddress("Jet1SDmassRaw"                                      , & Jet1SDmassRaw                                    );
  T1->SetBranchAddress("Jet0PuppiSDmassRaw"                                      , & Jet0PuppiSDmassRaw                                    );
  T1->SetBranchAddress("Jet1PuppiSDmassRaw"                                      , & Jet1PuppiSDmassRaw                                    );
  T1->SetBranchAddress("Jet0MassRaw"                                        , & Jet0MassRaw                                      );
  T1->SetBranchAddress("Jet1MassRaw"                                        , & Jet1MassRaw                                      );
  T1->SetBranchAddress("Jet0PtRaw"                                          , & Jet0PtRaw                                        );
  T1->SetBranchAddress("Jet1PtRaw"                                          , & Jet1PtRaw                                        );
  T1->SetBranchAddress("Jet0EtaRaw"                                          , & Jet0EtaRaw                                        );
  T1->SetBranchAddress("Jet1EtaRaw"                                          , & Jet1EtaRaw                                        );
  T1->SetBranchAddress("Jet0PhiRaw"                                          , & Jet0PhiRaw                                        );
  T1->SetBranchAddress("Jet1PhiRaw"                                          , & Jet1PhiRaw                                        );
  T1->SetBranchAddress("Jet0CorrFactor"                                          , & Jet0CorrFactor                                        );
  T1->SetBranchAddress("Jet1CorrFactor"                                          , & Jet1CorrFactor                                        );
  T1->SetBranchAddress("Jet0MassCorrFactor"                                          , & Jet0MassCorrFactor                                        );
  T1->SetBranchAddress("Jet1MassCorrFactor"                                          , & Jet1MassCorrFactor                                        );
  T1->SetBranchAddress("Jet0PtSmearFactor"                                          , & Jet0PtSmearFactor                                        );
  T1->SetBranchAddress("Jet1PtSmearFactor"                                          , & Jet1PtSmearFactor                                        );
  T1->SetBranchAddress("Jet0PuppiCorrFactor"                                          , & Jet0PuppiCorrFactor                                        );
  T1->SetBranchAddress("Jet1PuppiCorrFactor"                                          , & Jet1PuppiCorrFactor                                        );
  T1->SetBranchAddress("Jet0PuppiPtSmearFactor"                                          , & Jet0PuppiPtSmearFactor                                        );
  T1->SetBranchAddress("Jet1PuppiPtSmearFactor"                                          , & Jet1PuppiPtSmearFactor                                        );
  T1->SetBranchAddress("Jet0Tau32"                                       , & Jet0Tau32                                     );
  T1->SetBranchAddress("Jet1Tau32"                                       , & Jet1Tau32                                     );
  T1->SetBranchAddress("HT"                                              , & HT                                            );
  T1->SetBranchAddress("AllHadTrigAcceptBits"                            , & AllHadTrigAcceptBits                          );

  //ignore other branches                                                                                                                    
  T1->SetBranchStatus("*",0);
  T1->SetBranchStatus("Jet0SDmassRaw",1)          ;
  T1->SetBranchStatus("Jet1SDmassRaw",1)          ;
  T1->SetBranchStatus("Jet0PuppiSDmassRaw",1)          ;
  T1->SetBranchStatus("Jet1PuppiSDmassRaw",1)          ;
  T1->SetBranchStatus("Jet0MassRaw",1)            ;
  T1->SetBranchStatus("Jet1MassRaw",1)            ;
  T1->SetBranchStatus("Jet0PtRaw",1)              ;
  T1->SetBranchStatus("Jet1PtRaw",1)              ;
  T1->SetBranchStatus("Jet0EtaRaw",1)              ;
  T1->SetBranchStatus("Jet1EtaRaw",1)              ;
  T1->SetBranchStatus("Jet0PhiRaw",1)              ;
  T1->SetBranchStatus("Jet1PhiRaw",1)              ;
  T1->SetBranchStatus("Jet0CorrFactor",1)              ;
  T1->SetBranchStatus("Jet1CorrFactor",1)              ;
  T1->SetBranchStatus("Jet0MassCorrFactor",1)              ;
  T1->SetBranchStatus("Jet1MassCorrFactor",1)              ;
  T1->SetBranchStatus("Jet0PtSmearFactor",1)              ;
  T1->SetBranchStatus("Jet1PtSmearFactor",1)              ;
  T1->SetBranchStatus("Jet0PuppiCorrFactor",1)              ;
  T1->SetBranchStatus("Jet1PuppiCorrFactor",1)              ;
  T1->SetBranchStatus("Jet0PuppiPtSmearFactor",1)              ;
  T1->SetBranchStatus("Jet1PuppiPtSmearFactor",1)              ;
  T1->SetBranchStatus("Jet0Tau32",1)           ;
  T1->SetBranchStatus("Jet1Tau32",1)           ;
  T1->SetBranchStatus("HT",1)                  ;
  T1->SetBranchStatus("AllHadTrigAcceptBits",1);

  vector <string> xAxisLabels;
  vector <string> twoDxAxisLabels;
  vector <string> twoDyAxisLabels;
  vector <string> cutCats;

  vector <string> ptCutLabels;
  vector <float> ptCuts;

  vector <string> numLabels;
  vector <string> numOrLabels;
  vector <int> numTrig;
  vector <int> numOrTrig;

  vector <string> denomLabels;

  xAxisLabels.push_back("sumJetPt");
  xAxisLabels.push_back("HT");
  xAxisLabels.push_back("Jet0Pt");
  xAxisLabels.push_back("Jet0Mass");

  twoDxAxisLabels.push_back("sumJetPt");
  twoDxAxisLabels.push_back("HT");

  twoDyAxisLabels.push_back("JetMass");
  twoDyAxisLabels.push_back("JetSoftDropMass");
  twoDyAxisLabels.push_back("JetPUPPISoftDropMass");

  //adding top tag cuts
  cutCats.push_back("_");
  cutCats.push_back("_1tagMass_");
  cutCats.push_back("_2tagMass_");
  cutCats.push_back("_1tagPUPPIMass_");
  cutCats.push_back("_2tagPUPPIMass_");
  //cutCats.push_back("_2tagMass_2tagTau32_");

  //adjusting the minimum jet pt
  ptCutLabels.push_back("_minpt300"); ptCuts.push_back(300.);
  ptCutLabels.push_back("_minpt400"); ptCuts.push_back(400.);
  ptCutLabels.push_back("_minpt450"); ptCuts.push_back(450.);
  ptCutLabels.push_back("_minpt500"); ptCuts.push_back(500.);

  //trigger numerators and denominators
  //Problems with HT triggers in run H - need Or with single jet triggers                                                              
  
  numLabels.push_back("PFHT700TrimMass50"); numTrig.push_back(19);
  numLabels.push_back("PFHT800"); numTrig.push_back(6);
  numLabels.push_back("PFHT900"); numTrig.push_back(7);
  
  numOrLabels.push_back("PFJet450"); numOrTrig.push_back(13);
  numOrLabels.push_back("AK8PFJet450"); numOrTrig.push_back(15);
  numOrLabels.push_back("PFJet360TrimMass30"); numOrTrig.push_back(17);
  
  denomLabels.push_back("PFHT650");
  denomLabels.push_back("Mu50orIsoMu24");

  //denominator histograms
  TH1D *histos_denom[xAxisLabels.size()][ptCutLabels.size()][cutCats.size()][denomLabels.size()];
  TH2D *histostwoD_denom[twoDxAxisLabels.size()][twoDyAxisLabels.size()][ptCutLabels.size()][cutCats.size()][denomLabels.size()];

  //numerator histograms
  TH1D *histos_num[xAxisLabels.size()][ptCutLabels.size()][cutCats.size()][denomLabels.size()][numLabels.size()];
  TH1D *histos_numOr[xAxisLabels.size()][ptCutLabels.size()][cutCats.size()][denomLabels.size()][numLabels.size()][numOrLabels.size()];
  TH2D *histostwoD_num[twoDxAxisLabels.size()][twoDyAxisLabels.size()][ptCutLabels.size()][cutCats.size()][denomLabels.size()][numLabels.size()];
  TH2D *histostwoD_numOr[twoDxAxisLabels.size()][twoDyAxisLabels.size()][ptCutLabels.size()][cutCats.size()][denomLabels.size()][numLabels.size()][numOrLabels.size()];

  //naming histograms
  for (unsigned int i_ptCutLabels=0; i_ptCutLabels<ptCutLabels.size(); i_ptCutLabels++){ 
    for (unsigned int i_cutCats=0; i_cutCats<cutCats.size(); i_cutCats++){
      for (unsigned int i_denomLabels=0; i_denomLabels<denomLabels.size(); i_denomLabels++){
	for (unsigned int i_xAxisLabels=0; i_xAxisLabels<xAxisLabels.size(); i_xAxisLabels++){
	  histos_denom[i_xAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels] = new TH1D(Form("h_pass%sdenom%s%s%s",denomLabels[i_denomLabels].c_str(),ptCutLabels[i_ptCutLabels].c_str(),cutCats[i_cutCats].c_str(),xAxisLabels[i_xAxisLabels].c_str()),"",800, 0,  8000);
	  for (unsigned int i_numLabels=0; i_numLabels<numLabels.size(); i_numLabels++){
	    histos_num[i_xAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels][i_numLabels] = new TH1D(Form("h_pass%snum%sdenom%s%s%s",numLabels[i_numLabels].c_str(),denomLabels[i_denomLabels].c_str(),ptCutLabels[i_ptCutLabels].c_str(),cutCats[i_cutCats].c_str(),xAxisLabels[i_xAxisLabels].c_str()),"",800, 0,  8000);
	    for (unsigned int i_numOrLabels=0; i_numOrLabels<numOrLabels.size(); i_numOrLabels++) histos_numOr[i_xAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels][i_numLabels][i_numOrLabels] = new TH1D(Form("h_pass%sor%snum%sdenom%s%s%s",numLabels[i_numLabels].c_str(),numOrLabels[i_numOrLabels].c_str(),denomLabels[i_denomLabels].c_str(),ptCutLabels[i_ptCutLabels].c_str(),cutCats[i_cutCats].c_str(),xAxisLabels[i_xAxisLabels].c_str()),"",800, 0,  8000);
	  }
	}
	for (unsigned int i_twoDxAxisLabels=0; i_twoDxAxisLabels<twoDxAxisLabels.size(); i_twoDxAxisLabels++){
	  for (unsigned int i_twoDyAxisLabels=0; i_twoDyAxisLabels<twoDyAxisLabels.size(); i_twoDyAxisLabels++){
	    histostwoD_denom[i_twoDxAxisLabels][i_twoDyAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels] = new TH2D(Form("h_pass%sdenom%s%s%svs%s",denomLabels[i_denomLabels].c_str(),ptCutLabels[i_ptCutLabels].c_str(),cutCats[i_cutCats].c_str(),twoDyAxisLabels[i_twoDyAxisLabels].c_str(),twoDxAxisLabels[i_twoDxAxisLabels].c_str()),"",800, 0,  8000, 800, 0,  8000);
	    for (unsigned int i_numLabels=0; i_numLabels<numLabels.size(); i_numLabels++){
	      histostwoD_num[i_twoDxAxisLabels][i_twoDyAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels][i_numLabels] = new TH2D(Form("h_pass%snum%sdenom%s%s%svs%s",numLabels[i_numLabels].c_str(),denomLabels[i_denomLabels].c_str(),ptCutLabels[i_ptCutLabels].c_str(),cutCats[i_cutCats].c_str(),twoDyAxisLabels[i_twoDyAxisLabels].c_str(),twoDxAxisLabels[i_twoDxAxisLabels].c_str()),"",800, 0,  8000, 800, 0,  8000);
	      for (unsigned int i_numOrLabels=0; i_numOrLabels<numOrLabels.size(); i_numOrLabels++){
		histostwoD_numOr[i_twoDxAxisLabels][i_twoDyAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels][i_numLabels][i_numOrLabels] = new TH2D(Form("h_pass%sor%snum%sdenom%s%s%svs%s",numLabels[i_numLabels].c_str(),numOrLabels[i_numOrLabels].c_str(),denomLabels[i_denomLabels].c_str(),ptCutLabels[i_ptCutLabels].c_str(),cutCats[i_cutCats].c_str(),twoDyAxisLabels[i_twoDyAxisLabels].c_str(),twoDxAxisLabels[i_twoDxAxisLabels].c_str()),"",800, 0,  8000, 800, 0,  8000);
	      }
	    }
	  }
	}
      }
    }
  }

  for (int i=0; i<treeNentries; i++ ){ //entries                                                                                                  
    if (i%10000==0) cout<<i<<"  / "<<treeNentries<<endl;
    T1->GetEntry(i);

    // Jet corrections                                                                                                                      
    TLorentzVector Jet0P4Raw;
    TLorentzVector Jet1P4Raw;
    Jet0P4Raw.SetPtEtaPhiM( Jet0PtRaw, Jet0EtaRaw, Jet0PhiRaw, Jet0MassRaw);
    Jet1P4Raw.SetPtEtaPhiM( Jet1PtRaw, Jet1EtaRaw, Jet1PhiRaw, Jet1MassRaw);

    TLorentzVector Jet0P4 = Jet0P4Raw * Jet0CorrFactor * Jet0PtSmearFactor;
    TLorentzVector Jet1P4 = Jet1P4Raw * Jet1CorrFactor * Jet1PtSmearFactor;

    double Jet0Pt = Jet0P4.Perp();
    double Jet1Pt = Jet1P4.Perp();
    double Jet0Phi = Jet0P4.Phi();
    double Jet1Phi = Jet1P4.Phi();
    double Jet0Mass = Jet0P4.M();
    double Jet1Mass = Jet1P4.M();
    double Jet0SDmass = Jet0SDmassRaw * Jet0MassCorrFactor * Jet0PtSmearFactor;
    double Jet1SDmass = Jet1SDmassRaw * Jet1MassCorrFactor * Jet1PtSmearFactor;
    double Jet0PuppiSDmass = Jet0PuppiSDmassRaw * Jet0PuppiCorrFactor * Jet0PuppiPtSmearFactor;
    double Jet1PuppiSDmass = Jet1PuppiSDmassRaw * Jet1PuppiCorrFactor * Jet1PuppiPtSmearFactor;

    // Top-tagging bools
    bool j0_tag_mass  = Jet0SDmass > topTagSDwindowLo && Jet0SDmass < topTagSDwindowHi;
    bool j1_tag_mass  = Jet1SDmass > topTagSDwindowLo && Jet1SDmass < topTagSDwindowHi;
    bool j0_tag_puppimass  = Jet0PuppiSDmass > topTagSDwindowLo && Jet0PuppiSDmass < topTagSDwindowHi;
    bool j1_tag_puppimass  = Jet1PuppiSDmass > topTagSDwindowLo && Jet1PuppiSDmass < topTagSDwindowHi;
    //bool j0_tag_tau32 = Jet0Tau32 < topTagTau32cut;
    //bool j1_tag_tau32 = Jet1Tau32 < topTagTau32cut;
    bool j0orj1_tag_mass = j0_tag_mass || j1_tag_mass;
    bool jets_tag_mass = j0_tag_mass && j1_tag_mass;
    bool j0orj1_tag_puppimass = j0_tag_puppimass || j1_tag_puppimass;
    bool jets_tag_puppimass = j0_tag_puppimass && j1_tag_puppimass;
    //bool jets_top_tag = jets_tag_mass && j0_tag_tau32 && j1_tag_tau32;

    //kinematic variables
    float sumJetPt = Jet0Pt + Jet1Pt;
    float deltaPhi = abs(Jet0Phi - Jet1Phi);

    //converting string of trigger bits to long
    string trigBitsString = AllHadTrigAcceptBits->c_str();
    int trigBits = std::stol(trigBitsString,nullptr,2);

    //setting x-axis variables, fiducial cuts, and denominator trigger bits
    vector <float> xAxisVars;
    vector <float> twoDxAxisVars;
    vector <float> twoDyAxisVarsPt1;
    vector <float> twoDyAxisVarsPt2;
    vector <bool> cuts;
    vector <bool> denomTrigPass;

    xAxisVars.push_back(sumJetPt);
    xAxisVars.push_back(HT);
    xAxisVars.push_back(Jet0Pt);
    xAxisVars.push_back(Jet0Mass);

    twoDxAxisVars.push_back(sumJetPt);
    twoDxAxisVars.push_back(HT);
    
    twoDyAxisVarsPt1.push_back(Jet0Mass);
    twoDyAxisVarsPt1.push_back(Jet0SDmass);
    twoDyAxisVarsPt1.push_back(Jet0PuppiSDmass);

    twoDyAxisVarsPt2.push_back(Jet1Mass);
    twoDyAxisVarsPt2.push_back(Jet1SDmass);
    twoDyAxisVarsPt2.push_back(Jet1PuppiSDmass);

    cuts.push_back(1);
    cuts.push_back(j0orj1_tag_mass);
    cuts.push_back(jets_tag_mass);
    cuts.push_back(j0orj1_tag_puppimass);
    cuts.push_back(jets_tag_puppimass);
    //cuts.push_back(jets_top_tag);

    denomTrigPass.push_back((trigBits>>5)&1);//PFHT650
    denomTrigPass.push_back(((trigBits>>23)&1) || ((trigBits>>27)&1));//Mu50orIsoMu24 

    //make sure vector lengths are consistent
    if (xAxisVars.size() != xAxisLabels.size()){
      break;
      cout << "Incorrect length of x axis variable vector!" << endl;
    }
    if (cuts.size() != cutCats.size()){
      break;
      cout << "Incorrect length of cuts vector!" << endl;
    }
    if (denomTrigPass.size() != denomLabels.size()){
      break;
      cout << "Incorrect length of denominator vector!" << endl;
    }
    
    //filling histograms
    if (deltaPhi > 2.1){
      for (unsigned int i_ptCutLabels=0; i_ptCutLabels<ptCutLabels.size(); i_ptCutLabels++){
	if ((Jet0Pt > ptCuts[i_ptCutLabels]) && (Jet1Pt > ptCuts[i_ptCutLabels])){
	  for (unsigned int i_cutCats=0; i_cutCats<cutCats.size(); i_cutCats++){
	    if (cuts[i_cutCats]){
	      for (unsigned int i_denomLabels=0; i_denomLabels<denomLabels.size(); i_denomLabels++){
		if (denomTrigPass[i_denomLabels]){
		  for (unsigned int i_xAxisLabels=0; i_xAxisLabels<xAxisLabels.size(); i_xAxisLabels++){
		    histos_denom[i_xAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels]->Fill(xAxisVars[i_xAxisLabels]);
		    for (unsigned int i_numLabels=0; i_numLabels<numLabels.size(); i_numLabels++){
		      if ((trigBits>>numTrig[i_numLabels])&1) histos_num[i_xAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels][i_numLabels]->Fill(xAxisVars[i_xAxisLabels]);
		      for (unsigned int i_numOrLabels=0; i_numOrLabels<numOrLabels.size(); i_numOrLabels++){
			if (((trigBits>>numTrig[i_numLabels])&1) || ((trigBits>>numOrTrig[i_numOrLabels])&1)) histos_numOr[i_xAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels][i_numLabels][i_numOrLabels]->Fill(xAxisVars[i_xAxisLabels]);
		      }
		    }
		  }
		  for (unsigned int i_twoDxAxisLabels=0; i_twoDxAxisLabels<twoDxAxisLabels.size(); i_twoDxAxisLabels++){
		    for (unsigned int i_twoDyAxisLabels=0; i_twoDyAxisLabels<twoDyAxisLabels.size(); i_twoDyAxisLabels++){
		      histostwoD_denom[i_twoDxAxisLabels][i_twoDyAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels]->Fill(twoDxAxisVars[i_twoDxAxisLabels],twoDyAxisVarsPt1[i_twoDyAxisLabels]);
		      histostwoD_denom[i_twoDxAxisLabels][i_twoDyAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels]->Fill(twoDxAxisVars[i_twoDxAxisLabels],twoDyAxisVarsPt2[i_twoDyAxisLabels]);
		      for (unsigned int i_numLabels=0; i_numLabels<numLabels.size(); i_numLabels++){
			if ((trigBits>>numTrig[i_numLabels])&1){
			  histostwoD_num[i_twoDxAxisLabels][i_twoDyAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels][i_numLabels]->Fill(twoDxAxisVars[i_twoDxAxisLabels],twoDyAxisVarsPt1[i_twoDyAxisLabels]);
 histostwoD_num[i_twoDxAxisLabels][i_twoDyAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels][i_numLabels]->Fill(twoDxAxisVars[i_twoDxAxisLabels],twoDyAxisVarsPt2[i_twoDyAxisLabels]);
			}
			for (unsigned int i_numOrLabels=0; i_numOrLabels<numOrLabels.size(); i_numOrLabels++){
			  if (((trigBits>>numTrig[i_numLabels])&1) || ((trigBits>>numOrTrig[i_numOrLabels])&1)) {
			    histostwoD_numOr[i_twoDxAxisLabels][i_twoDyAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels][i_numLabels][i_numOrLabels]->Fill(twoDxAxisVars[i_twoDxAxisLabels],twoDyAxisVarsPt1[i_twoDyAxisLabels]);
			    histostwoD_numOr[i_twoDxAxisLabels][i_twoDyAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels][i_numLabels][i_numOrLabels]->Fill(twoDxAxisVars[i_twoDxAxisLabels],twoDyAxisVarsPt2[i_twoDyAxisLabels]);
			  }
			}
		      }
		    }
		  }
		}
	      }
            }
          }
        }
      }
    }
    
    xAxisVars.clear(); 
    twoDxAxisVars.clear(); 
    twoDyAxisVarsPt1.clear(); 
    twoDyAxisVarsPt2.clear(); 
    cuts.clear();
    denomTrigPass.clear();
  }

  string outName = output_folder+"outRunTrigEff_"+date+"_"+input_file;
  cout << outName << endl;
  TFile * Out = new TFile(outName.c_str(),"RECREATE");
  Out->cd();

  //writing histograms
  for (unsigned int i_ptCutLabels=0; i_ptCutLabels<ptCutLabels.size(); i_ptCutLabels++){
    for (unsigned int i_cutCats=0; i_cutCats<cutCats.size(); i_cutCats++){
      for (unsigned int i_denomLabels=0; i_denomLabels<denomLabels.size(); i_denomLabels++){
	for (unsigned int i_xAxisLabels=0; i_xAxisLabels<xAxisLabels.size(); i_xAxisLabels++){
	  histos_denom[i_xAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels]->Write();
	  for (unsigned int i_numLabels=0; i_numLabels<numLabels.size(); i_numLabels++){
	    histos_num[i_xAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels][i_numLabels]->Write();
	    for (unsigned int i_numOrLabels=0; i_numOrLabels<numOrLabels.size(); i_numOrLabels++) histos_numOr[i_xAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels][i_numLabels][i_numOrLabels]->Write();
	  }
	}
	for (unsigned int i_twoDxAxisLabels=0; i_twoDxAxisLabels<twoDxAxisLabels.size(); i_twoDxAxisLabels++){
	  for (unsigned int i_twoDyAxisLabels=0; i_twoDyAxisLabels<twoDyAxisLabels.size(); i_twoDyAxisLabels++){
	    histostwoD_denom[i_twoDxAxisLabels][i_twoDyAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels]->Write();
	    for (unsigned int i_numLabels=0; i_numLabels<numLabels.size(); i_numLabels++){
	      histostwoD_num[i_twoDxAxisLabels][i_twoDyAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels][i_numLabels]->Write();
	      for (unsigned int i_numOrLabels=0; i_numOrLabels<numOrLabels.size(); i_numOrLabels++) histostwoD_numOr[i_twoDxAxisLabels][i_twoDyAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels][i_numLabels][i_numOrLabels]->Write();
	    }
	  }
	}
      }
    }
  }

  //deleting histograms
  for (unsigned int i_ptCutLabels=0; i_ptCutLabels<ptCutLabels.size(); i_ptCutLabels++){
    for (unsigned int i_cutCats=0; i_cutCats<cutCats.size(); i_cutCats++){
      for (unsigned int i_denomLabels=0; i_denomLabels<denomLabels.size(); i_denomLabels++){
	for (unsigned int i_xAxisLabels=0; i_xAxisLabels<xAxisLabels.size(); i_xAxisLabels++){
	  histos_denom[i_xAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels]->Delete();
	  for (unsigned int i_numLabels=0; i_numLabels<numLabels.size(); i_numLabels++){
	    histos_num[i_xAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels][i_numLabels]->Delete();
	    for (unsigned int i_numOrLabels=0; i_numOrLabels<numOrLabels.size(); i_numOrLabels++) histos_numOr[i_xAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels][i_numLabels][i_numOrLabels]->Delete();
	  }
	}
	for (unsigned int i_twoDxAxisLabels=0; i_twoDxAxisLabels<twoDxAxisLabels.size(); i_twoDxAxisLabels++){
	  for (unsigned int i_twoDyAxisLabels=0; i_twoDyAxisLabels<twoDyAxisLabels.size(); i_twoDyAxisLabels++){
	    histostwoD_denom[i_twoDxAxisLabels][i_twoDyAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels]->Delete();
	    for (unsigned int i_numLabels=0; i_numLabels<numLabels.size(); i_numLabels++){
	      histostwoD_num[i_twoDxAxisLabels][i_twoDyAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels][i_numLabels]->Delete();
	      for (unsigned int i_numOrLabels=0; i_numOrLabels<numOrLabels.size(); i_numOrLabels++) histostwoD_numOr[i_twoDxAxisLabels][i_twoDyAxisLabels][i_ptCutLabels][i_cutCats][i_denomLabels][i_numLabels][i_numOrLabels]->Delete();
	    }
	  }
	}
      }
    }
  }

  xAxisLabels.clear();
  twoDxAxisLabels.clear();
  twoDyAxisLabels.clear();
  cutCats.clear();
  ptCutLabels.clear();
  ptCuts.clear();
  numLabels.clear();
  numOrLabels.clear();
  numTrig.clear();
  numOrTrig.clear();
  denomLabels.clear();

  
  Out->Close();
}

void looptree(
        string input_folder      , 
        string input_file        , 
        string modmassFile       , 
        string mistagFile        , 
        float minAK8Pt           , 
        float minHT              , 
        float topTagSDwindowLo   , 
        float topTagSDwindowHi   , 
        float topTagTau32cut     , 
        string savelabel         , 
        bool isQCDMC             , 
        bool isData              , 
        bool isFrozen            , 
        bool run_antitag         , 
        bool run_kinematic       , 
        bool run_bkgdest         , 
        bool do_PUreweighting    ,
        bool do_HTreweighting    ,
        bool do_ttbarReweighting ,
        int Syst                 , 
        int Nevents              ,
        bool verbose_
        )
{ 
  gSystem->Load("libAnalysisPredictedDistribution");
  gSystem->Load("libCondFormatsBTauObjects.so");

  // setup btag calibration + reader
  BTagCalibration calib("csvv2", "subjet_CSVv2_ichep.csv" );    // SUBJETS: "subjet_CSVv2_ichep.csv"  AK4: "CSVv2_ichep.csv"
  BTagCalibrationReader reader(BTagEntry::OP_MEDIUM,            // operating point   // OP_LOOSE, OP_MEDIUM
                               "central",                       // central sys type  
                               {"up", "down"});                 // other sys types

  reader.load(calib,                // calibration instance
              BTagEntry::FLAV_B,    // btag flavour          // FLAV_B=0 , FLAV_C=1 , FLAV_UDSG=2
              "lt");                // measurement type      // SUBJET FLAV_B = "lt" , SUBJET FLAV_light = "incl",  AK4 FLAV_B = "comb" , SUBJET FLAV_light = "incl"


  //Syst: nom = 0, jerDn = -2; jecDn = -1; jecNom = 0; jecUp = +1; jerUp = +2; bTagUp = +3; bTagDn = -3; pdfUp = +4; pdfDn = -4; q2Up = +5; q2Dn = -5; puUp = +6; puDN = -6
  string systType;
  if (Syst == 0)       systType = "nom"     ;  
  else if (Syst ==  1) systType = "jec_up"  ;
  else if (Syst == -1) systType = "jec_dn"  ;
  else if (Syst ==  2) systType = "jer_up"  ;
  else if (Syst == -2) systType = "jer_dn"  ;
  else if (Syst ==  3) systType = "bTag_up" ;
  else if (Syst == -3) systType = "bTag_dn" ;
  else if (Syst ==  4) systType = "pdf_up"  ;
  else if (Syst == -4) systType = "pdf_dn"  ;
  else if (Syst ==  5) systType = "q2_up"   ;
  else if (Syst == -5) systType = "q2_dn"   ;
  else if (Syst ==  6) systType = "PU_up"   ;
  else if (Syst == -6) systType = "PU_dn"   ;
  
  // Get intput file
  string file_name =  input_folder+input_file;
  cout<<"opening "<<file_name<<endl;
  TFile *F1   = TFile::Open(file_name.c_str() );

  // Get Tree entries
  Int_t   PassMETFilters                            ;
  Float_t Jet0PtRaw                                 ;
  Float_t Jet0EtaRaw                                ;
  Float_t Jet0PhiRaw                                ;
  Float_t Jet0MassRaw                               ;
  Float_t Jet0P                                     ;
  Float_t Jet0Pt                                    ;
  Float_t Jet0Eta                                   ;
  Float_t Jet0Phi                                   ;
  Float_t Jet0Rap                                   ;
  Float_t Jet0Energy                                ;
  Float_t Jet0Mass                                  ;
  Float_t Jet0Area                                  ;
  Float_t Jet0SDmass                                ;
  Float_t Jet0SDmassRaw                             ;
  Float_t Jet0SDmassCorrL23                         ;    
  Float_t Jet0SDmassCorrL23Up                       ;    
  Float_t Jet0SDmassCorrL23Dn                       ;     
  Float_t Jet0SDmassCorrL23Smear                    ;    
  Float_t Jet0SDmassCorrL23SmearUp                  ;    
  Float_t Jet0SDmassCorrL23SmearDn                  ;  
  Float_t Jet0SDmassCorrL123                        ;    
  Float_t Jet0SDmassCorrL123Up                      ;    
  Float_t Jet0SDmassCorrL123Dn                      ;     
  Float_t Jet0SDptRaw                               ;    
  Float_t Jet0SDptCorrL23                           ;    
  Float_t Jet0SDptCorrL23Up                         ;    
  Float_t Jet0SDptCorrL23Dn                         ;    
  Float_t Jet0SDptCorrL123                          ;    
  Float_t Jet0SDptCorrL123Up                        ;    
  Float_t Jet0SDptCorrL123Dn                        ;    
  Float_t Jet0SDptCorrL23Smear                      ;    
  Float_t Jet0SDptCorrL23SmearUp                    ;    
  Float_t Jet0SDptCorrL23SmearDn                    ;    
  Float_t Jet0SDetaRaw                              ;    
  Float_t Jet0SDphiRaw                              ;    
  Float_t Jet0MassPruned                            ;
  Float_t Jet0MassTrimmed                           ;
  Float_t Jet0Tau1                                  ;
  Float_t Jet0Tau2                                  ;
  Float_t Jet0Tau3                                  ;
  Float_t Jet0Tau4                                  ;
  Float_t Jet0Tau32                                 ;
  Float_t Jet0Tau21                                 ;
  Float_t Jet0SDsubjet0bdisc                        ;
  Float_t Jet0SDsubjet1bdisc                        ;
  Float_t Jet0SDmaxbdisc                            ;
  Float_t Jet0SDmaxbdiscflavHadron                  ;
  Float_t Jet0SDmaxbdiscflavParton                  ;
  Float_t Jet0SDsubjet0pt                           ;
  Float_t Jet0SDsubjet0mass                         ;
  Float_t Jet0SDsubjet0eta                          ;
  Float_t Jet0SDsubjet0phi                          ;
  Float_t Jet0SDsubjet0area                         ;
  Float_t Jet0SDsubjet0flavHadron                   ;
  Float_t Jet0SDsubjet0flavParton                   ;
  Float_t Jet0SDsubjet0tau1                         ;
  Float_t Jet0SDsubjet0tau2                         ;
  Float_t Jet0SDsubjet0tau3                         ;
  Float_t Jet0SDsubjet1pt                           ;
  Float_t Jet0SDsubjet1mass                         ;
  Float_t Jet0SDsubjet1eta                          ;
  Float_t Jet0SDsubjet1phi                          ;
  Float_t Jet0SDsubjet1area                         ;
  Float_t Jet0SDsubjet1flavHadron                   ;
  Float_t Jet0SDsubjet1flavParton                   ;
  Float_t Jet0SDsubjet1tau1                         ;
  Float_t Jet0SDsubjet1tau2                         ;
  Float_t Jet0SDsubjet1tau3                         ;
  Float_t Jet0PuppiPt                               ;
  Float_t Jet0PuppiEta                              ;
  Float_t Jet0PuppiPhi                              ;
  Float_t Jet0PuppiMass                             ;

  Float_t Jet0PuppiSDmass                           ;
  Float_t Jet0PuppiSDmassSubjetCorr                 ;
  Float_t Jet0PuppiSDmassSubjetCorrUp               ;
  Float_t Jet0PuppiSDmassSubjetCorrDn               ;
  // Float_t Jet0PuppiSDmassSubjetCorrL23Smear      ;
  // Float_t Jet0PuppiSDmassSubjetCorrL23SmearUp    ;
  // Float_t Jet0PuppiSDmassSubjetCorrL23SmearDn    ;
  Float_t Jet0PuppiSDpt                             ;
  Float_t Jet0PuppiSDptSubjetCorr                   ;
  Float_t Jet0PuppiSDptSubjetCorrUp                 ;
  Float_t Jet0PuppiSDptSubjetCorrDn                 ;
  // Float_t Jet0PuppiSDptSubjetCorrL23Smear        ;
  // Float_t Jet0PuppiSDptSubjetCorrL23SmearUp      ;
  // Float_t Jet0PuppiSDptSubjetCorrL23SmearDn      ;
  Float_t Jet0PuppiSDeta                                 ;
  Float_t Jet0PuppiSDphi                                 ;

  Float_t Jet0PuppiTau1                                  ;
  Float_t Jet0PuppiTau2                                  ;
  Float_t Jet0PuppiTau3                                  ;
  Float_t Jet0PuppiTau4                                  ;
  Float_t Jet0PuppiTau32                                 ;
  Float_t Jet0PuppiTau21                                 ;
  Float_t Jet0PuppiSDsubjet0bdisc                        ;
  Float_t Jet0PuppiSDsubjet1bdisc                        ;
  Float_t Jet0PuppiSDmaxbdisc                            ;
  Float_t Jet0PuppiSDmaxbdiscflavHadron                  ;
  Float_t Jet0PuppiSDmaxbdiscflavParton                  ;
  Float_t Jet0PuppiSDsubjet0pt                           ;
  Float_t Jet0PuppiSDsubjet0mass                         ;
  Float_t Jet0PuppiSDsubjet0eta                          ;
  Float_t Jet0PuppiSDsubjet0phi                          ;
  Float_t Jet0PuppiSDsubjet0area                         ;
  Float_t Jet0PuppiSDsubjet0flavHadron                   ;
  Float_t Jet0PuppiSDsubjet0flavParton                   ;
  Float_t Jet0PuppiSDsubjet0tau1                         ;
  Float_t Jet0PuppiSDsubjet0tau2                         ;
  Float_t Jet0PuppiSDsubjet0tau3                         ;
  Float_t Jet0PuppiSDsubjet1pt                           ;
  Float_t Jet0PuppiSDsubjet1mass                         ;
  Float_t Jet0PuppiSDsubjet1eta                          ;
  Float_t Jet0PuppiSDsubjet1phi                          ;
  Float_t Jet0PuppiSDsubjet1area                         ;
  Float_t Jet0PuppiSDsubjet1flavHadron                   ;
  Float_t Jet0PuppiSDsubjet1flavParton                   ;
  Float_t Jet0PuppiSDsubjet1tau1                         ;
  Float_t Jet0PuppiSDsubjet1tau2                         ;
  Float_t Jet0PuppiSDsubjet1tau3                         ;
  Float_t Jet0CHF                                        ;
  Float_t Jet0NHF                                        ;
  Float_t Jet0CM                                         ;
  Float_t Jet0NM                                         ;
  Float_t Jet0NEF                                        ;
  Float_t Jet0CEF                                        ;
  Float_t Jet0MF                                         ;
  Float_t Jet0Mult                                       ;

  Float_t Jet0PuppiCHF                                   ;
  Float_t Jet0PuppiNHF                                   ;
  Float_t Jet0PuppiCM                                    ;
  Float_t Jet0PuppiNM                                    ;
  Float_t Jet0PuppiNEF                                   ;
  Float_t Jet0PuppiCEF                                   ;
  Float_t Jet0PuppiMF                                    ;
  Float_t Jet0PuppiMult                                  ;

  Float_t Jet0MassCorrFactor                        ;
  Float_t Jet0MassCorrFactorUp                      ;
  Float_t Jet0MassCorrFactorDn                      ;
  Float_t Jet0CorrFactor                            ;
  Float_t Jet0CorrFactorUp                          ;
  Float_t Jet0CorrFactorDn                          ;
  Float_t Jet0PtSmearFactor                         ;
  Float_t Jet0PtSmearFactorUp                       ;
  Float_t Jet0PtSmearFactorDn                       ;
  Float_t Jet0PuppiMassCorrFactor                   ;
  Float_t Jet0PuppiMassCorrFactorUp                 ;
  Float_t Jet0PuppiMassCorrFactorDn                 ;
  Float_t Jet0PuppiCorrFactor                       ;
  Float_t Jet0PuppiCorrFactorUp                     ;
  Float_t Jet0PuppiCorrFactorDn                     ;
  Float_t Jet0PuppiPtSmearFactor                    ;
  Float_t Jet0PuppiPtSmearFactorUp                  ;
  Float_t Jet0PuppiPtSmearFactorDn                  ;
  // Float_t Jet0EtaScaleFactor                        ;
  // Float_t Jet0PhiScaleFactor                        ;
  // Float_t Jet0MatchedGenJetDR                       ;
  Float_t Jet0MatchedGenJetPt                       ;
  Float_t Jet0MatchedGenJetMass                     ;

  Int_t   Jet0GenMatched_TopHadronic                ;
  Float_t Jet0GenMatched_TopPt                      ;
  Float_t Jet0GenMatched_TopEta                     ;
  Float_t Jet0GenMatched_TopPhi                     ;
  Float_t Jet0GenMatched_TopMass                    ;
  Float_t Jet0GenMatched_bPt                        ;
  Float_t Jet0GenMatched_WPt                        ;
  Float_t Jet0GenMatched_Wd1Pt                      ;
  Float_t Jet0GenMatched_Wd2Pt                      ;
  Float_t Jet0GenMatched_Wd1ID                      ;
  Float_t Jet0GenMatched_Wd2ID                      ;
  Float_t Jet0GenMatched_MaxDeltaRPartonTop         ;
  Float_t Jet0GenMatched_MaxDeltaRWPartonTop        ;
  Float_t Jet0GenMatched_MaxDeltaRWPartonW          ;
  Float_t Jet0GenMatched_DeltaR_t_b                 ;
  Float_t Jet0GenMatched_DeltaR_t_W                 ;
  Float_t Jet0GenMatched_DeltaR_t_Wd1               ;
  Float_t Jet0GenMatched_DeltaR_t_Wd2               ;
  Float_t Jet0GenMatched_DeltaR_W_b1                ;
  Float_t Jet0GenMatched_DeltaR_W_Wd1               ;
  Float_t Jet0GenMatched_DeltaR_W_Wd2               ;
  Float_t Jet0GenMatched_DeltaR_Wd1_Wd2             ;
  Float_t Jet0GenMatched_DeltaR_Wd1_b               ;
  Float_t Jet0GenMatched_DeltaR_Wd2_b               ;
  Float_t Jet0GenMatched_DeltaR_jet_t               ;
  Float_t Jet0GenMatched_DeltaR_jet_W               ;
  Float_t Jet0GenMatched_DeltaR_jet_b               ;
  Float_t Jet0GenMatched_DeltaR_jet_Wd1             ;
  Float_t Jet0GenMatched_DeltaR_jet_Wd2             ;
  Float_t Jet0GenMatched_DeltaR_pup0_b              ;
  Float_t Jet0GenMatched_DeltaR_pup0_Wd1            ;
  Float_t Jet0GenMatched_DeltaR_pup0_Wd2            ;
  Float_t Jet0GenMatched_DeltaR_pup1_b              ;
  Float_t Jet0GenMatched_DeltaR_pup1_Wd1            ;
  Float_t Jet0GenMatched_DeltaR_pup1_Wd2            ;
  Float_t Jet0GenMatched_partonPt                   ;
  Float_t Jet0GenMatched_partonEta                  ;
  Float_t Jet0GenMatched_partonPhi                  ;
  Float_t Jet0GenMatched_partonMass                 ;
  Float_t Jet0GenMatched_partonID                   ;
  Float_t Jet0GenMatched_DeltaRjetParton            ;

  Float_t Jet1PtRaw                                 ;
  Float_t Jet1EtaRaw                                ;
  Float_t Jet1PhiRaw                                ;
  Float_t Jet1MassRaw                               ;
  Float_t Jet1P                                     ;
  Float_t Jet1Pt                                    ;
  Float_t Jet1Eta                                   ;
  Float_t Jet1Phi                                   ;
  Float_t Jet1Rap                                   ;
  Float_t Jet1Energy                                ;
  Float_t Jet1Mass                                  ;
  Float_t Jet1Area                                  ;
  Float_t Jet1SDmass                                ;
  Float_t Jet1SDmassRaw                             ;
  Float_t Jet1SDmassCorrL23                         ;
  Float_t Jet1SDmassCorrL23Up                       ;
  Float_t Jet1SDmassCorrL23Dn                       ;
  Float_t Jet1SDmassCorrL123                        ;
  Float_t Jet1SDmassCorrL123Up                      ;
  Float_t Jet1SDmassCorrL123Dn                      ;
  Float_t Jet1SDmassCorrL23Smear                    ;
  Float_t Jet1SDmassCorrL23SmearUp                  ;
  Float_t Jet1SDmassCorrL23SmearDn                  ;
  Float_t Jet1SDptRaw                               ;
  Float_t Jet1SDptCorrL23                           ;
  Float_t Jet1SDptCorrL23Up                         ;
  Float_t Jet1SDptCorrL23Dn                         ;
  Float_t Jet1SDptCorrL123                          ;
  Float_t Jet1SDptCorrL123Up                        ;
  Float_t Jet1SDptCorrL123Dn                        ;
  Float_t Jet1SDptCorrL23Smear                      ;
  Float_t Jet1SDptCorrL23SmearUp                    ;
  Float_t Jet1SDptCorrL23SmearDn                    ;
  Float_t Jet1SDetaRaw                              ;
  Float_t Jet1SDphiRaw                              ; 
  Float_t Jet1MassPruned                            ;
  Float_t Jet1MassTrimmed                           ;
  Float_t Jet1Tau1                                  ;
  Float_t Jet1Tau2                                  ;
  Float_t Jet1Tau3                                  ;
  Float_t Jet1Tau4                                  ;
  Float_t Jet1Tau32                                 ;
  Float_t Jet1Tau21                                 ;
  Float_t Jet1SDsubjet0bdisc                        ;
  Float_t Jet1SDsubjet1bdisc                        ;
  Float_t Jet1SDmaxbdisc                            ;
  Float_t Jet1SDmaxbdiscflavHadron                  ;
  Float_t Jet1SDmaxbdiscflavParton                  ;
  Float_t Jet1SDsubjet0pt                           ;
  Float_t Jet1SDsubjet0eta                          ;
  Float_t Jet1SDsubjet0phi                          ;
  Float_t Jet1SDsubjet0mass                         ;
  Float_t Jet1SDsubjet0area                         ;
  Float_t Jet1SDsubjet0flavHadron                   ;
  Float_t Jet1SDsubjet0flavParton                   ;
  Float_t Jet1SDsubjet0tau1                         ;
  Float_t Jet1SDsubjet0tau2                         ;
  Float_t Jet1SDsubjet0tau3                         ;
  Float_t Jet1SDsubjet1pt                           ;
  Float_t Jet1SDsubjet1eta                          ;
  Float_t Jet1SDsubjet1phi                          ;
  Float_t Jet1SDsubjet1mass                         ;
  Float_t Jet1SDsubjet1area                         ;
  Float_t Jet1SDsubjet1flavHadron                   ;
  Float_t Jet1SDsubjet1flavParton                   ;
  Float_t Jet1SDsubjet1tau1                         ;
  Float_t Jet1SDsubjet1tau2                         ;
  Float_t Jet1SDsubjet1tau3                         ;
  Float_t Jet1PuppiPt                               ;
  Float_t Jet1PuppiEta                              ;
  Float_t Jet1PuppiPhi                              ;
  Float_t Jet1PuppiMass                             ;

  Float_t Jet1PuppiSDmass                           ;
  Float_t Jet1PuppiSDmassSubjetCorr                       ;
  Float_t Jet1PuppiSDmassSubjetCorrUp                     ;
  Float_t Jet1PuppiSDmassSubjetCorrDn                     ;
  // Float_t Jet1PuppiSDmassSubjetCorrL23Smear               ;
  // Float_t Jet1PuppiSDmassSubjetCorrL23SmearUp             ;
  // Float_t Jet1PuppiSDmassSubjetCorrL23SmearDn             ;
  Float_t Jet1PuppiSDpt                             ;
  Float_t Jet1PuppiSDptSubjetCorr                         ;
  Float_t Jet1PuppiSDptSubjetCorrUp                       ;
  Float_t Jet1PuppiSDptSubjetCorrDn                       ;
  // Float_t Jet1PuppiSDptSubjetCorrL23Smear                 ;
  // Float_t Jet1PuppiSDptSubjetCorrL23SmearUp               ;
  // Float_t Jet1PuppiSDptSubjetCorrL23SmearDn               ;
  Float_t Jet1PuppiSDeta                            ;
  Float_t Jet1PuppiSDphi                            ;

  Float_t Jet1PuppiTau1                             ;
  Float_t Jet1PuppiTau2                             ;
  Float_t Jet1PuppiTau3                             ;
  Float_t Jet1PuppiTau4                             ;
  Float_t Jet1PuppiTau32                            ;
  Float_t Jet1PuppiTau21                            ;
  Float_t Jet1PuppiSDsubjet0bdisc                   ;
  Float_t Jet1PuppiSDsubjet1bdisc                   ;
  Float_t Jet1PuppiSDmaxbdisc                       ;
  Float_t Jet1PuppiSDmaxbdiscflavHadron             ;
  Float_t Jet1PuppiSDmaxbdiscflavParton             ;
  Float_t Jet1PuppiSDsubjet0pt                      ;
  Float_t Jet1PuppiSDsubjet0eta                     ;
  Float_t Jet1PuppiSDsubjet0phi                     ;
  Float_t Jet1PuppiSDsubjet0mass                    ;
  Float_t Jet1PuppiSDsubjet0area                    ;
  Float_t Jet1PuppiSDsubjet0flavHadron              ;
  Float_t Jet1PuppiSDsubjet0flavParton              ;
  Float_t Jet1PuppiSDsubjet0tau1                    ;
  Float_t Jet1PuppiSDsubjet0tau2                    ;
  Float_t Jet1PuppiSDsubjet0tau3                    ;
  Float_t Jet1PuppiSDsubjet1pt                      ;
  Float_t Jet1PuppiSDsubjet1eta                     ;
  Float_t Jet1PuppiSDsubjet1phi                     ;
  Float_t Jet1PuppiSDsubjet1mass                    ;
  Float_t Jet1PuppiSDsubjet1area                    ;
  Float_t Jet1PuppiSDsubjet1flavHadron              ;
  Float_t Jet1PuppiSDsubjet1flavParton              ;
  Float_t Jet1PuppiSDsubjet1tau1                    ;
  Float_t Jet1PuppiSDsubjet1tau2                    ;
  Float_t Jet1PuppiSDsubjet1tau3                    ;
  Float_t Jet1CHF                                   ;
  Float_t Jet1NHF                                   ;
  Float_t Jet1CM                                    ;
  Float_t Jet1NM                                    ;
  Float_t Jet1NEF                                   ;
  Float_t Jet1CEF                                   ;
  Float_t Jet1MF                                    ;
  Float_t Jet1Mult                                  ;
  Float_t Jet1MassCorrFactor                        ;
  Float_t Jet1MassCorrFactorUp                      ;
  Float_t Jet1MassCorrFactorDn                      ;
  Float_t Jet1CorrFactor                            ;
  Float_t Jet1CorrFactorUp                          ;
  Float_t Jet1CorrFactorDn                          ;
  Float_t Jet1PtSmearFactor                         ;
  Float_t Jet1PtSmearFactorUp                       ;
  Float_t Jet1PtSmearFactorDn                       ;
  Float_t Jet1PuppiMassCorrFactor                   ;
  Float_t Jet1PuppiMassCorrFactorUp                 ;
  Float_t Jet1PuppiMassCorrFactorDn                 ;
  Float_t Jet1PuppiCorrFactor                       ;
  Float_t Jet1PuppiCorrFactorUp                     ;
  Float_t Jet1PuppiCorrFactorDn                     ;
  Float_t Jet1PuppiPtSmearFactor                    ;
  Float_t Jet1PuppiPtSmearFactorUp                  ;
  Float_t Jet1PuppiPtSmearFactorDn                  ;
  // Float_t Jet1EtaScaleFactor                        ;
  // Float_t Jet1PhiScaleFactor                        ;
  // Float_t Jet1MatchedGenJetDR                       ;
  Float_t Jet1MatchedGenJetPt                       ;
  Float_t Jet1MatchedGenJetMass                     ;

  Int_t   Jet1GenMatched_TopHadronic                ;
  Float_t Jet1GenMatched_TopPt                      ;
  Float_t Jet1GenMatched_TopEta                     ;
  Float_t Jet1GenMatched_TopPhi                     ;
  Float_t Jet1GenMatched_TopMass                    ;
  Float_t Jet1GenMatched_bPt                        ;
  Float_t Jet1GenMatched_WPt                        ;
  Float_t Jet1GenMatched_Wd1Pt                      ;
  Float_t Jet1GenMatched_Wd2Pt                      ;
  Float_t Jet1GenMatched_Wd1ID                      ;
  Float_t Jet1GenMatched_Wd2ID                      ;
  Float_t Jet1GenMatched_MaxDeltaRPartonTop         ;
  Float_t Jet1GenMatched_MaxDeltaRWPartonTop        ;
  Float_t Jet1GenMatched_MaxDeltaRWPartonW          ;
  Float_t Jet1GenMatched_DeltaR_t_b                 ;
  Float_t Jet1GenMatched_DeltaR_t_W                 ;
  Float_t Jet1GenMatched_DeltaR_t_Wd1               ;
  Float_t Jet1GenMatched_DeltaR_t_Wd2               ;
  Float_t Jet1GenMatched_DeltaR_W_b1                ;
  Float_t Jet1GenMatched_DeltaR_W_Wd1               ;
  Float_t Jet1GenMatched_DeltaR_W_Wd2               ;
  Float_t Jet1GenMatched_DeltaR_Wd1_Wd2             ;
  Float_t Jet1GenMatched_DeltaR_Wd1_b               ;
  Float_t Jet1GenMatched_DeltaR_Wd2_b               ;
  Float_t Jet1GenMatched_DeltaR_jet_t               ;
  Float_t Jet1GenMatched_DeltaR_jet_W               ;
  Float_t Jet1GenMatched_DeltaR_jet_b               ;
  Float_t Jet1GenMatched_DeltaR_jet_Wd1             ;
  Float_t Jet1GenMatched_DeltaR_jet_Wd2             ;
  Float_t Jet1GenMatched_DeltaR_pup0_b              ;
  Float_t Jet1GenMatched_DeltaR_pup0_Wd1            ;
  Float_t Jet1GenMatched_DeltaR_pup0_Wd2            ;
  Float_t Jet1GenMatched_DeltaR_pup1_b              ;
  Float_t Jet1GenMatched_DeltaR_pup1_Wd1            ;
  Float_t Jet1GenMatched_DeltaR_pup1_Wd2            ;      
  Float_t Jet1GenMatched_partonPt                   ;
  Float_t Jet1GenMatched_partonEta                  ;
  Float_t Jet1GenMatched_partonPhi                  ;
  Float_t Jet1GenMatched_partonMass                 ;
  Float_t Jet1GenMatched_partonID                   ;
  Float_t Jet1GenMatched_DeltaRjetParton            ;

  Float_t AllHadMETpx                               ;           
  Float_t AllHadMETpy                               ;           
  Float_t AllHadMETpt                               ;           
  Float_t AllHadMETphi                              ;           
  Float_t AllHadMETsumET                            ;           
  Float_t AllHadNvtx                                ;      
  Float_t AllHadNvtxGood ;     
  Float_t AllHadNPUtrue                             ;           
  Float_t AllHadRho                                 ;           
  Float_t AllHadEventWeight                         ;    
  Float_t AllHadPUweight       ; 
  Float_t AllHadPUweight_MBup  ; 
  Float_t AllHadPUweight_MBdn  ;        
  Float_t DijetMass                                 ;           
  Float_t DijetMassPuppi                            ;           
  Float_t DijetDeltaR                               ;           
  Float_t DijetDeltaPhi                             ;           
  Float_t DijetDeltaRap                             ;           
  Float_t DiGenJetMass                              ;           
  Float_t GenTTmass                                 ;           
  Float_t HT                                        ;           
  Float_t HT_CorrDn                                 ;           
  Float_t HT_CorrUp                                 ;           
  Float_t HT_PtSmearNom                             ;           
  Float_t HT_PtSmearUp                              ;           
  Float_t HT_PtSmearDn                              ;           
  Float_t Q2weight_CorrDn                           ;           
  Float_t Q2weight_CorrUp                           ;           
  Float_t NNPDF3weight_CorrDn                       ;           
  Float_t NNPDF3weight_CorrUp                       ;           
  Int_t   AllHadRunNum                              ;           
  Int_t   AllHadLumiBlock                           ;           
  Int_t   AllHadEventNum                            ;    

  std::vector<std::string> *AllHadTrigNames;
  std::vector<int>         *AllHadTrigPrescales = 0;
  std::string *AllHadTrigAcceptBits = new std::string;

  TTree *T1    = (TTree*)  F1     ->Get("ana/TreeAllHad");

  double treeNentries = T1->GetEntries();
  cout<<"treeNentries = "<< treeNentries <<endl;


  // T1->SetBranchAddress("AllHadTrigNames",&AllHadTrigNames);
  // T1->SetBranchAddress("AllHadTrigPrescales",&AllHadTrigPrescales);

  T1->SetBranchAddress("PassMETFilters"                        , & PassMETFilters                      );                                  
  T1->SetBranchAddress("Jet0PtRaw"                             , & Jet0PtRaw                           );                                  
  T1->SetBranchAddress("Jet0EtaRaw"                            , & Jet0EtaRaw                          );                                   
  T1->SetBranchAddress("Jet0PhiRaw"                            , & Jet0PhiRaw                          );                                   
  T1->SetBranchAddress("Jet0MassRaw"                           , & Jet0MassRaw                         );                                    
  T1->SetBranchAddress("Jet0P"                                 , & Jet0P                               );                              
  T1->SetBranchAddress("Jet0Pt"                                , & Jet0Pt                              );                               
  T1->SetBranchAddress("Jet0Eta"                               , & Jet0Eta                             );                                
  T1->SetBranchAddress("Jet0Phi"                               , & Jet0Phi                             );                                
  T1->SetBranchAddress("Jet0Rap"                               , & Jet0Rap                             );                                
  T1->SetBranchAddress("Jet0Energy"                            , & Jet0Energy                          );                                   
  T1->SetBranchAddress("Jet0Mass"                              , & Jet0Mass                            );                                 
  T1->SetBranchAddress("Jet0Area"                              , & Jet0Area                            );                                 
  T1->SetBranchAddress("Jet0SDmass"                            , & Jet0SDmass                          );                                         
  T1->SetBranchAddress("Jet0SDmassRaw"                         , & Jet0SDmassRaw                       );                                               
  T1->SetBranchAddress("Jet0SDmassCorrL23"                     , & Jet0SDmassCorrL23                   );                                                    
  T1->SetBranchAddress("Jet0SDmassCorrL23Up"                   , & Jet0SDmassCorrL23Up                 );                                                      
  T1->SetBranchAddress("Jet0SDmassCorrL23Dn"                   , & Jet0SDmassCorrL23Dn                 );                                                      
  T1->SetBranchAddress("Jet0SDmassCorrL123"                    , & Jet0SDmassCorrL123                  );                                                      
  T1->SetBranchAddress("Jet0SDmassCorrL123Up"                  , & Jet0SDmassCorrL123Up                );                                                        
  T1->SetBranchAddress("Jet0SDmassCorrL123Dn"                  , & Jet0SDmassCorrL123Dn                );                                                        
  // T1->SetBranchAddress("Jet0SDmassCorrL23Smear"                , & Jet0SDmassCorrL23Smear              );                                                     
  // T1->SetBranchAddress("Jet0SDmassCorrL23SmearUp"              , & Jet0SDmassCorrL23SmearUp            );                                                       
  // T1->SetBranchAddress("Jet0SDmassCorrL23SmearDn"              , & Jet0SDmassCorrL23SmearDn            );   
  T1->SetBranchAddress("Jet0SDptRaw"                           , & Jet0SDptRaw                         );                                               
  T1->SetBranchAddress("Jet0SDptCorrL23"                       , & Jet0SDptCorrL23                     );                                                    
  T1->SetBranchAddress("Jet0SDptCorrL23Up"                     , & Jet0SDptCorrL23Up                   );                                                      
  T1->SetBranchAddress("Jet0SDptCorrL23Dn"                     , & Jet0SDptCorrL23Dn                   );                                                      
  T1->SetBranchAddress("Jet0SDptCorrL123"                      , & Jet0SDptCorrL123                    );                                                      
  T1->SetBranchAddress("Jet0SDptCorrL123Up"                    , & Jet0SDptCorrL123Up                  );                                                        
  T1->SetBranchAddress("Jet0SDptCorrL123Dn"                    , & Jet0SDptCorrL123Dn                  );                                                        
  // T1->SetBranchAddress("Jet0SDptCorrL23Smear"                  , & Jet0SDptCorrL23Smear                );                                                     
  // T1->SetBranchAddress("Jet0SDptCorrL23SmearUp"                , & Jet0SDptCorrL23SmearUp              );                                                       
  // T1->SetBranchAddress("Jet0SDptCorrL23SmearDn"                , & Jet0SDptCorrL23SmearDn              );                                                     
  T1->SetBranchAddress("Jet0SDetaRaw"                          , & Jet0SDetaRaw                        );                                               
  T1->SetBranchAddress("Jet0SDphiRaw"                          , & Jet0SDphiRaw                        );                                               
  T1->SetBranchAddress("Jet0MassPruned"                        , & Jet0MassPruned                      );                                       
  T1->SetBranchAddress("Jet0MassTrimmed"                       , & Jet0MassTrimmed                     );                                       
  T1->SetBranchAddress("Jet0Tau1"                              , & Jet0Tau1                            );                                 
  T1->SetBranchAddress("Jet0Tau2"                              , & Jet0Tau2                            );                                 
  T1->SetBranchAddress("Jet0Tau3"                              , & Jet0Tau3                            );                                 
  T1->SetBranchAddress("Jet0Tau4"                              , & Jet0Tau4                            );                                 
  T1->SetBranchAddress("Jet0Tau32"                             , & Jet0Tau32                           );                                  
  T1->SetBranchAddress("Jet0Tau21"                             , & Jet0Tau21                           );                                                                      
  T1->SetBranchAddress("Jet0SDmaxbdisc"                        , & Jet0SDmaxbdisc                      );                                       
  T1->SetBranchAddress("Jet0SDmaxbdiscflavHadron"              , & Jet0SDmaxbdiscflavHadron            );                                           
  T1->SetBranchAddress("Jet0SDmaxbdiscflavParton"              , & Jet0SDmaxbdiscflavParton            );                                           
  T1->SetBranchAddress("Jet0SDsubjet0pt"                       , & Jet0SDsubjet0pt                     );                                        
  T1->SetBranchAddress("Jet0SDsubjet0mass"                     , & Jet0SDsubjet0mass                   ); 
  T1->SetBranchAddress("Jet0SDsubjet0eta"                      , & Jet0SDsubjet0eta                    );
  T1->SetBranchAddress("Jet0SDsubjet0phi"                      , & Jet0SDsubjet0phi                    );                                         
  T1->SetBranchAddress("Jet0SDsubjet0area"                     , & Jet0SDsubjet0area                   );                                          
  T1->SetBranchAddress("Jet0SDsubjet0flavHadron"               , & Jet0SDsubjet0flavHadron             );                                          
  T1->SetBranchAddress("Jet0SDsubjet0flavParton"               , & Jet0SDsubjet0flavParton             ); 
  T1->SetBranchAddress("Jet0SDsubjet0tau1"                     , & Jet0SDsubjet0tau1                   );
  T1->SetBranchAddress("Jet0SDsubjet0tau2"                     , & Jet0SDsubjet0tau2                   );
  T1->SetBranchAddress("Jet0SDsubjet0tau3"                     , & Jet0SDsubjet0tau3                   ); 
  T1->SetBranchAddress("Jet0SDsubjet0bdisc"                    , & Jet0SDsubjet0bdisc                  );                                     
  T1->SetBranchAddress("Jet0SDsubjet1pt"                       , & Jet0SDsubjet1pt                     );                                        
  T1->SetBranchAddress("Jet0SDsubjet1mass"                     , & Jet0SDsubjet1mass                   );  
  T1->SetBranchAddress("Jet0SDsubjet1eta"                      , & Jet0SDsubjet1eta                    );
  T1->SetBranchAddress("Jet0SDsubjet1phi"                      , & Jet0SDsubjet1phi                    );                                        
  T1->SetBranchAddress("Jet0SDsubjet1area"                     , & Jet0SDsubjet1area                   );                                          
  T1->SetBranchAddress("Jet0SDsubjet1flavHadron"               , & Jet0SDsubjet1flavHadron             );                                          
  T1->SetBranchAddress("Jet0SDsubjet1flavParton"               , & Jet0SDsubjet1flavParton             ); 
  T1->SetBranchAddress("Jet0SDsubjet1tau1"                     , & Jet0SDsubjet1tau1                   );
  T1->SetBranchAddress("Jet0SDsubjet1tau2"                     , & Jet0SDsubjet1tau2                   );
  T1->SetBranchAddress("Jet0SDsubjet1tau3"                     , & Jet0SDsubjet1tau3                   );  
  T1->SetBranchAddress("Jet0SDsubjet1bdisc"                    , & Jet0SDsubjet1bdisc                  );                                                                                    
  T1->SetBranchAddress("Jet0PuppiPt"                           , & Jet0PuppiPt                         );                                    
  T1->SetBranchAddress("Jet0PuppiEta"                          , & Jet0PuppiEta                        );                                     
  T1->SetBranchAddress("Jet0PuppiPhi"                          , & Jet0PuppiPhi                        );                                     
  T1->SetBranchAddress("Jet0PuppiMass"                         , & Jet0PuppiMass                       );                                      

  T1->SetBranchAddress("Jet0PuppiSDmass"                       , & Jet0PuppiSDmass                     );
  T1->SetBranchAddress("Jet0PuppiSDmassSubjetCorr"                   , & Jet0PuppiSDmassSubjetCorr                 );
  T1->SetBranchAddress("Jet0PuppiSDmassSubjetCorrUp"                 , & Jet0PuppiSDmassSubjetCorrUp               );
  T1->SetBranchAddress("Jet0PuppiSDmassSubjetCorrDn"                 , & Jet0PuppiSDmassSubjetCorrDn               );
  // T1->SetBranchAddress("Jet0PuppiSDmassSubjetCorrL23Smear"           , & Jet0PuppiSDmassSubjetCorrL23Smear         );
  // T1->SetBranchAddress("Jet0PuppiSDmassSubjetCorrL23SmearUp"         , & Jet0PuppiSDmassSubjetCorrL23SmearUp       );
  // T1->SetBranchAddress("Jet0PuppiSDmassSubjetCorrL23SmearDn"         , & Jet0PuppiSDmassSubjetCorrL23SmearDn       );
  T1->SetBranchAddress("Jet0PuppiSDpt"                         , & Jet0PuppiSDpt                       );
  T1->SetBranchAddress("Jet0PuppiSDptSubjetCorr"                     , & Jet0PuppiSDptSubjetCorr                   );
  T1->SetBranchAddress("Jet0PuppiSDptSubjetCorrUp"                   , & Jet0PuppiSDptSubjetCorrUp                 );
  T1->SetBranchAddress("Jet0PuppiSDptSubjetCorrDn"                   , & Jet0PuppiSDptSubjetCorrDn                 );
  // T1->SetBranchAddress("Jet0PuppiSDptSubjetCorrL23Smear"             , & Jet0PuppiSDptSubjetCorrL23Smear           );
  // T1->SetBranchAddress("Jet0PuppiSDptSubjetCorrL23SmearUp"           , & Jet0PuppiSDptSubjetCorrL23SmearUp         );
  // T1->SetBranchAddress("Jet0PuppiSDptSubjetCorrL23SmearDn"           , & Jet0PuppiSDptSubjetCorrL23SmearDn         );
  T1->SetBranchAddress("Jet0PuppiSDeta"                        , & Jet0PuppiSDeta                      );
  T1->SetBranchAddress("Jet0PuppiSDphi"                        , & Jet0PuppiSDphi                      );
                                                         
  T1->SetBranchAddress("Jet0PuppiTau1"                         , & Jet0PuppiTau1                       );                                      
  T1->SetBranchAddress("Jet0PuppiTau2"                         , & Jet0PuppiTau2                       );                                      
  T1->SetBranchAddress("Jet0PuppiTau3"                         , & Jet0PuppiTau3                       );                                      
  T1->SetBranchAddress("Jet0PuppiTau4"                         , & Jet0PuppiTau4                       );                                      
  T1->SetBranchAddress("Jet0PuppiTau32"                        , & Jet0PuppiTau32                      );                                       
  T1->SetBranchAddress("Jet0PuppiTau21"                        , & Jet0PuppiTau21                      );                                                                                
  T1->SetBranchAddress("Jet0PuppiSDmaxbdisc"                   , & Jet0PuppiSDmaxbdisc                 );                                            
  T1->SetBranchAddress("Jet0PuppiSDmaxbdiscflavHadron"         , & Jet0PuppiSDmaxbdiscflavHadron       );                                                
  T1->SetBranchAddress("Jet0PuppiSDmaxbdiscflavParton"         , & Jet0PuppiSDmaxbdiscflavParton       );                                                
  T1->SetBranchAddress("Jet0PuppiSDsubjet0pt"                  , & Jet0PuppiSDsubjet0pt                );                                             
  T1->SetBranchAddress("Jet0PuppiSDsubjet0mass"                , & Jet0PuppiSDsubjet0mass              );    
  T1->SetBranchAddress("Jet0PuppiSDsubjet0eta"                 , & Jet0PuppiSDsubjet0eta               );
  T1->SetBranchAddress("Jet0PuppiSDsubjet0phi"                 , & Jet0PuppiSDsubjet0phi               );                                           
  T1->SetBranchAddress("Jet0PuppiSDsubjet0area"                , & Jet0PuppiSDsubjet0area              );                                               
  T1->SetBranchAddress("Jet0PuppiSDsubjet0flavHadron"          , & Jet0PuppiSDsubjet0flavHadron        );                                               
  T1->SetBranchAddress("Jet0PuppiSDsubjet0flavParton"          , & Jet0PuppiSDsubjet0flavParton        ); 
  T1->SetBranchAddress("Jet0PuppiSDsubjet0tau1"                , & Jet0PuppiSDsubjet0tau1              );
  T1->SetBranchAddress("Jet0PuppiSDsubjet0tau2"                , & Jet0PuppiSDsubjet0tau2              );
  T1->SetBranchAddress("Jet0PuppiSDsubjet0tau3"                , & Jet0PuppiSDsubjet0tau3              ); 
  T1->SetBranchAddress("Jet0PuppiSDsubjet0bdisc"               , & Jet0PuppiSDsubjet0bdisc             );                                          
  T1->SetBranchAddress("Jet0PuppiSDsubjet1pt"                  , & Jet0PuppiSDsubjet1pt                );                                             
  T1->SetBranchAddress("Jet0PuppiSDsubjet1mass"                , & Jet0PuppiSDsubjet1mass              );  
  T1->SetBranchAddress("Jet0PuppiSDsubjet1eta"                 , & Jet0PuppiSDsubjet1eta               );
  T1->SetBranchAddress("Jet0PuppiSDsubjet1phi"                 , & Jet0PuppiSDsubjet1phi               );                                             
  T1->SetBranchAddress("Jet0PuppiSDsubjet1area"                , & Jet0PuppiSDsubjet1area              );                                               
  T1->SetBranchAddress("Jet0PuppiSDsubjet1flavHadron"          , & Jet0PuppiSDsubjet1flavHadron        );                                               
  T1->SetBranchAddress("Jet0PuppiSDsubjet1flavParton"          , & Jet0PuppiSDsubjet1flavParton        );    
  T1->SetBranchAddress("Jet0PuppiSDsubjet1tau1"                , & Jet0PuppiSDsubjet1tau1              );
  T1->SetBranchAddress("Jet0PuppiSDsubjet1tau2"                , & Jet0PuppiSDsubjet1tau2              );
  T1->SetBranchAddress("Jet0PuppiSDsubjet1tau3"                , & Jet0PuppiSDsubjet1tau3              ); 
  T1->SetBranchAddress("Jet0PuppiSDsubjet1bdisc"               , & Jet0PuppiSDsubjet1bdisc             );                                                                                          
  T1->SetBranchAddress("Jet0CHF"                               , & Jet0CHF                             );                                
  T1->SetBranchAddress("Jet0NHF"                               , & Jet0NHF                             );                                
  T1->SetBranchAddress("Jet0CM"                                , & Jet0CM                              );                               
  T1->SetBranchAddress("Jet0NM"                                , & Jet0NM                              );                               
  T1->SetBranchAddress("Jet0NEF"                               , & Jet0NEF                             );                                
  T1->SetBranchAddress("Jet0CEF"                               , & Jet0CEF                             );                                
  T1->SetBranchAddress("Jet0MF"                                , & Jet0MF                              );                               
  T1->SetBranchAddress("Jet0Mult"                              , & Jet0Mult                            );  
  T1->SetBranchAddress("Jet0PuppiCHF"                               , & Jet0PuppiCHF                             );                                
  T1->SetBranchAddress("Jet0PuppiNHF"                               , & Jet0PuppiNHF                             );                                
  T1->SetBranchAddress("Jet0PuppiCM"                                , & Jet0PuppiCM                              );                               
  T1->SetBranchAddress("Jet0PuppiNM"                                , & Jet0PuppiNM                              );                               
  T1->SetBranchAddress("Jet0PuppiNEF"                               , & Jet0PuppiNEF                             );                                
  T1->SetBranchAddress("Jet0PuppiCEF"                               , & Jet0PuppiCEF                             );                                
  T1->SetBranchAddress("Jet0PuppiMF"                                , & Jet0PuppiMF                              );                               
  T1->SetBranchAddress("Jet0PuppiMult"                              , & Jet0PuppiMult                            );  

  T1->SetBranchAddress("Jet0MassCorrFactor"                    , & Jet0MassCorrFactor                  );                                           
  T1->SetBranchAddress("Jet0MassCorrFactorUp"                  , & Jet0MassCorrFactorUp                );                                             
  T1->SetBranchAddress("Jet0MassCorrFactorDn"                  , & Jet0MassCorrFactorDn                );                                             
  T1->SetBranchAddress("Jet0CorrFactor"                        , & Jet0CorrFactor                      );                                       
  T1->SetBranchAddress("Jet0CorrFactorUp"                      , & Jet0CorrFactorUp                    );                                         
  T1->SetBranchAddress("Jet0CorrFactorDn"                      , & Jet0CorrFactorDn                    );                                         
  T1->SetBranchAddress("Jet0PtSmearFactor"                     , & Jet0PtSmearFactor                   );                                          
  T1->SetBranchAddress("Jet0PtSmearFactorUp"                   , & Jet0PtSmearFactorUp                 );                                            
  T1->SetBranchAddress("Jet0PtSmearFactorDn"                   , & Jet0PtSmearFactorDn                 );                                            
  T1->SetBranchAddress("Jet0PuppiMassCorrFactor"               , & Jet0PuppiMassCorrFactor             );                                                
  T1->SetBranchAddress("Jet0PuppiMassCorrFactorUp"             , & Jet0PuppiMassCorrFactorUp           );                                                  
  T1->SetBranchAddress("Jet0PuppiMassCorrFactorDn"             , & Jet0PuppiMassCorrFactorDn           );                                                  
  T1->SetBranchAddress("Jet0PuppiCorrFactor"                   , & Jet0PuppiCorrFactor                 );                                            
  T1->SetBranchAddress("Jet0PuppiCorrFactorUp"                 , & Jet0PuppiCorrFactorUp               );                                              
  T1->SetBranchAddress("Jet0PuppiCorrFactorDn"                 , & Jet0PuppiCorrFactorDn               );                                              
  T1->SetBranchAddress("Jet0PuppiPtSmearFactor"                , & Jet0PuppiPtSmearFactor              );                                               
  T1->SetBranchAddress("Jet0PuppiPtSmearFactorUp"              , & Jet0PuppiPtSmearFactorUp            );                                                 
  T1->SetBranchAddress("Jet0PuppiPtSmearFactorDn"              , & Jet0PuppiPtSmearFactorDn            );                                                 
  // T1->SetBranchAddress("Jet0EtaScaleFactor"                    , & Jet0EtaScaleFactor                  );                                           
  // T1->SetBranchAddress("Jet0PhiScaleFactor"                    , & Jet0PhiScaleFactor                  );                                           
  //  T1->SetBranchAddress("Jet0MatchedGenJetDR"                   , & Jet0MatchedGenJetDR                 );                                            
  T1->SetBranchAddress("Jet0MatchedGenJetPt"                   , & Jet0MatchedGenJetPt                 );                                            
  T1->SetBranchAddress("Jet0MatchedGenJetMass"                 , & Jet0MatchedGenJetMass               );  

  T1->SetBranchAddress("Jet0GenMatched_TopHadronic"            , & Jet0GenMatched_TopHadronic          );      
  T1->SetBranchAddress("Jet0GenMatched_TopPt"                  , & Jet0GenMatched_TopPt                );      
  T1->SetBranchAddress("Jet0GenMatched_TopEta"                 , & Jet0GenMatched_TopEta               );      
  T1->SetBranchAddress("Jet0GenMatched_TopPhi"                 , & Jet0GenMatched_TopPhi               );      
  T1->SetBranchAddress("Jet0GenMatched_TopMass"                , & Jet0GenMatched_TopMass              );      
  T1->SetBranchAddress("Jet0GenMatched_bPt"                    , & Jet0GenMatched_bPt                  );      
  T1->SetBranchAddress("Jet0GenMatched_WPt"                    , & Jet0GenMatched_WPt                  );      
  T1->SetBranchAddress("Jet0GenMatched_Wd1Pt"                  , & Jet0GenMatched_Wd1Pt                );      
  T1->SetBranchAddress("Jet0GenMatched_Wd2Pt"                  , & Jet0GenMatched_Wd2Pt                );      
  T1->SetBranchAddress("Jet0GenMatched_Wd1ID"                  , & Jet0GenMatched_Wd1ID                );      
  T1->SetBranchAddress("Jet0GenMatched_Wd2ID"                  , & Jet0GenMatched_Wd2ID                );      
  T1->SetBranchAddress("Jet0GenMatched_MaxDeltaRPartonTop"     , & Jet0GenMatched_MaxDeltaRPartonTop   );      
  T1->SetBranchAddress("Jet0GenMatched_MaxDeltaRWPartonTop"    , & Jet0GenMatched_MaxDeltaRWPartonTop  );      
  T1->SetBranchAddress("Jet0GenMatched_MaxDeltaRWPartonW"      , & Jet0GenMatched_MaxDeltaRWPartonW    );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_t_b"             , & Jet0GenMatched_DeltaR_t_b           );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_t_W"             , & Jet0GenMatched_DeltaR_t_W           );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_t_Wd1"           , & Jet0GenMatched_DeltaR_t_Wd1         );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_t_Wd2"           , & Jet0GenMatched_DeltaR_t_Wd2         );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_W_b1"            , & Jet0GenMatched_DeltaR_W_b1          );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_W_Wd1"           , & Jet0GenMatched_DeltaR_W_Wd1         );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_W_Wd2"           , & Jet0GenMatched_DeltaR_W_Wd2         );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_Wd1_Wd2"         , & Jet0GenMatched_DeltaR_Wd1_Wd2       );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_Wd1_b"           , & Jet0GenMatched_DeltaR_Wd1_b         );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_Wd2_b"           , & Jet0GenMatched_DeltaR_Wd2_b         );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_jet_t"           , & Jet0GenMatched_DeltaR_jet_t         );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_jet_W"           , & Jet0GenMatched_DeltaR_jet_W         );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_jet_b"           , & Jet0GenMatched_DeltaR_jet_b         );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_jet_Wd1"         , & Jet0GenMatched_DeltaR_jet_Wd1       );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_jet_Wd2"         , & Jet0GenMatched_DeltaR_jet_Wd2       );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_pup0_b"          , & Jet0GenMatched_DeltaR_pup0_b        );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_pup0_Wd1"        , & Jet0GenMatched_DeltaR_pup0_Wd1      );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_pup0_Wd2"        , & Jet0GenMatched_DeltaR_pup0_Wd2      );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_pup1_b"          , & Jet0GenMatched_DeltaR_pup1_b        );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_pup1_Wd1"        , & Jet0GenMatched_DeltaR_pup1_Wd1      );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_pup1_Wd2"        , & Jet0GenMatched_DeltaR_pup1_Wd2      );               
  T1->SetBranchAddress("Jet0GenMatched_partonPt"               , & Jet0GenMatched_partonPt             );      
  T1->SetBranchAddress("Jet0GenMatched_partonEta"              , & Jet0GenMatched_partonEta            );      
  T1->SetBranchAddress("Jet0GenMatched_partonPhi"              , & Jet0GenMatched_partonPhi            );      
  T1->SetBranchAddress("Jet0GenMatched_partonMass"             , & Jet0GenMatched_partonMass           );      
  T1->SetBranchAddress("Jet0GenMatched_partonID"               , & Jet0GenMatched_partonID             );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaRjetParton"        , & Jet0GenMatched_DeltaRjetParton      );      
  std::cout<<"Setup Jet0 in tree"<<std::endl;

  T1->SetBranchAddress("Jet1PtRaw"                             , & Jet1PtRaw                           );                                  
  T1->SetBranchAddress("Jet1EtaRaw"                            , & Jet1EtaRaw                          );                                   
  T1->SetBranchAddress("Jet1PhiRaw"                            , & Jet1PhiRaw                          );                                   
  T1->SetBranchAddress("Jet1MassRaw"                           , & Jet1MassRaw                         );                                    
  T1->SetBranchAddress("Jet1P"                                 , & Jet1P                               );                              
  T1->SetBranchAddress("Jet1Pt"                                , & Jet1Pt                              );                               
  T1->SetBranchAddress("Jet1Eta"                               , & Jet1Eta                             );                                
  T1->SetBranchAddress("Jet1Phi"                               , & Jet1Phi                             );                                
  T1->SetBranchAddress("Jet1Rap"                               , & Jet1Rap                             );                                
  T1->SetBranchAddress("Jet1Energy"                            , & Jet1Energy                          );                                   
  T1->SetBranchAddress("Jet1Mass"                              , & Jet1Mass                            );                                 
  T1->SetBranchAddress("Jet1Area"                              , & Jet1Area                            );                                 
  T1->SetBranchAddress("Jet1SDmass"                            , & Jet1SDmass                          );                                         
  T1->SetBranchAddress("Jet1SDmassRaw"                         , & Jet1SDmassRaw                       );                                               
  T1->SetBranchAddress("Jet1SDmassCorrL23"                     , & Jet1SDmassCorrL23                   );                                                    
  T1->SetBranchAddress("Jet1SDmassCorrL23Up"                   , & Jet1SDmassCorrL23Up                 );                                                      
  T1->SetBranchAddress("Jet1SDmassCorrL23Dn"                   , & Jet1SDmassCorrL23Dn                 );                                                      
  T1->SetBranchAddress("Jet1SDmassCorrL123"                    , & Jet1SDmassCorrL123                  );                                                      
  T1->SetBranchAddress("Jet1SDmassCorrL123Up"                  , & Jet1SDmassCorrL123Up                );                                                        
  T1->SetBranchAddress("Jet1SDmassCorrL123Dn"                  , & Jet1SDmassCorrL123Dn                );                                                        
  T1->SetBranchAddress("Jet1SDmassCorrL23Smear"                , & Jet1SDmassCorrL23Smear                    );                                                     
  T1->SetBranchAddress("Jet1SDmassCorrL23SmearUp"              , & Jet1SDmassCorrL23SmearUp                  );                                                       
  T1->SetBranchAddress("Jet1SDmassCorrL23SmearDn"              , & Jet1SDmassCorrL23SmearDn                  );   
  T1->SetBranchAddress("Jet1SDptRaw"                           , & Jet1SDptRaw                         );                                               
  T1->SetBranchAddress("Jet1SDptCorrL23"                       , & Jet1SDptCorrL23                     );                                                    
  T1->SetBranchAddress("Jet1SDptCorrL23Up"                     , & Jet1SDptCorrL23Up                   );                                                      
  T1->SetBranchAddress("Jet1SDptCorrL23Dn"                     , & Jet1SDptCorrL23Dn                   );                                                      
  T1->SetBranchAddress("Jet1SDptCorrL123"                      , & Jet1SDptCorrL123                    );                                                      
  T1->SetBranchAddress("Jet1SDptCorrL123Up"                    , & Jet1SDptCorrL123Up                  );                                                        
  T1->SetBranchAddress("Jet1SDptCorrL123Dn"                    , & Jet1SDptCorrL123Dn                  );                                                        
  T1->SetBranchAddress("Jet1SDptCorrL23Smear"                  , & Jet1SDptCorrL23Smear                      );                                                     
  T1->SetBranchAddress("Jet1SDptCorrL23SmearUp"                , & Jet1SDptCorrL23SmearUp                    );                                                       
  T1->SetBranchAddress("Jet1SDptCorrL23SmearDn"                , & Jet1SDptCorrL23SmearDn                    );                                                     
  T1->SetBranchAddress("Jet1SDetaRaw"                          , & Jet1SDetaRaw                        );                                               
  T1->SetBranchAddress("Jet1SDphiRaw"                          , & Jet1SDphiRaw                        );  

  T1->SetBranchAddress("Jet1MassPruned"                        , & Jet1MassPruned                      );                                       
  T1->SetBranchAddress("Jet1MassTrimmed"                       , & Jet1MassTrimmed                      );                                       
  T1->SetBranchAddress("Jet1Tau1"                              , & Jet1Tau1                            );                                 
  T1->SetBranchAddress("Jet1Tau2"                              , & Jet1Tau2                            );                                 
  T1->SetBranchAddress("Jet1Tau3"                              , & Jet1Tau3                            );                                 
  T1->SetBranchAddress("Jet1Tau4"                              , & Jet1Tau4                            );                                 
  T1->SetBranchAddress("Jet1Tau32"                             , & Jet1Tau32                           );                                  
  T1->SetBranchAddress("Jet1Tau21"                             , & Jet1Tau21                           );                                                                      
  T1->SetBranchAddress("Jet1SDmaxbdisc"                        , & Jet1SDmaxbdisc                      );                                       
  T1->SetBranchAddress("Jet1SDmaxbdiscflavHadron"              , & Jet1SDmaxbdiscflavHadron            );                                           
  T1->SetBranchAddress("Jet1SDmaxbdiscflavParton"              , & Jet1SDmaxbdiscflavParton            );                                           
  T1->SetBranchAddress("Jet1SDsubjet0pt"                       , & Jet1SDsubjet0pt                     );                                        
  T1->SetBranchAddress("Jet1SDsubjet0mass"                     , & Jet1SDsubjet0mass                   ); 
  T1->SetBranchAddress("Jet1SDsubjet0eta"                      , & Jet1SDsubjet0eta                    );
  T1->SetBranchAddress("Jet1SDsubjet0phi"                      , & Jet1SDsubjet0phi                    );                                         
  T1->SetBranchAddress("Jet1SDsubjet0area"                     , & Jet1SDsubjet0area                   );                                          
  T1->SetBranchAddress("Jet1SDsubjet0flavHadron"               , & Jet1SDsubjet0flavHadron             );                                          
  T1->SetBranchAddress("Jet1SDsubjet0flavParton"               , & Jet1SDsubjet0flavParton             ); 
  T1->SetBranchAddress("Jet1SDsubjet0tau1"                     , & Jet1SDsubjet0tau1                   );
  T1->SetBranchAddress("Jet1SDsubjet0tau2"                     , & Jet1SDsubjet0tau2                   );
  T1->SetBranchAddress("Jet1SDsubjet0tau3"                     , & Jet1SDsubjet0tau3                   );
  T1->SetBranchAddress("Jet1SDsubjet0bdisc"                    , & Jet1SDsubjet0bdisc                  );                                     
  T1->SetBranchAddress("Jet1SDsubjet1pt"                       , & Jet1SDsubjet1pt                     );                                        
  T1->SetBranchAddress("Jet1SDsubjet1mass"                     , & Jet1SDsubjet1mass                   );  
  T1->SetBranchAddress("Jet1SDsubjet1eta"                      , & Jet1SDsubjet1eta                    );
  T1->SetBranchAddress("Jet1SDsubjet1phi"                      , & Jet1SDsubjet1phi                    );                                        
  T1->SetBranchAddress("Jet1SDsubjet1area"                     , & Jet1SDsubjet1area                   );                                          
  T1->SetBranchAddress("Jet1SDsubjet1flavHadron"               , & Jet1SDsubjet1flavHadron             );                                          
  T1->SetBranchAddress("Jet1SDsubjet1flavParton"               , & Jet1SDsubjet1flavParton             ); 
  T1->SetBranchAddress("Jet1SDsubjet1tau1"                     , & Jet1SDsubjet1tau1                   );
  T1->SetBranchAddress("Jet1SDsubjet1tau2"                     , & Jet1SDsubjet1tau2                   );
  T1->SetBranchAddress("Jet1SDsubjet1tau3"                     , & Jet1SDsubjet1tau3                   ); 
  T1->SetBranchAddress("Jet1SDsubjet1bdisc"                    , & Jet1SDsubjet1bdisc                  );                                                                                    
  T1->SetBranchAddress("Jet1PuppiPt"                           , & Jet1PuppiPt                         );                                    
  T1->SetBranchAddress("Jet1PuppiEta"                          , & Jet1PuppiEta                        );                                     
  T1->SetBranchAddress("Jet1PuppiPhi"                          , & Jet1PuppiPhi                        );                                     
  T1->SetBranchAddress("Jet1PuppiMass"                         , & Jet1PuppiMass                       );                                      

  T1->SetBranchAddress("Jet1PuppiSDmass"                             , & Jet1PuppiSDmass                     );
  T1->SetBranchAddress("Jet1PuppiSDmassSubjetCorr"                   , & Jet1PuppiSDmassSubjetCorr                 );
  T1->SetBranchAddress("Jet1PuppiSDmassSubjetCorrUp"                 , & Jet1PuppiSDmassSubjetCorrUp               );
  T1->SetBranchAddress("Jet1PuppiSDmassSubjetCorrDn"                 , & Jet1PuppiSDmassSubjetCorrDn               );
  // T1->SetBranchAddress("Jet1PuppiSDmassSubjetCorrL23Smear"        , & Jet1PuppiSDmassSubjetCorrL23Smear         );
  // T1->SetBranchAddress("Jet1PuppiSDmassSubjetCorrL23SmearUp"      , & Jet1PuppiSDmassSubjetCorrL23SmearUp       );
  // T1->SetBranchAddress("Jet1PuppiSDmassSubjetCorrL23SmearDn"      , & Jet1PuppiSDmassSubjetCorrL23SmearDn       );
  T1->SetBranchAddress("Jet1PuppiSDpt"                               , & Jet1PuppiSDpt                       );
  T1->SetBranchAddress("Jet1PuppiSDptSubjetCorr"                     , & Jet1PuppiSDptSubjetCorr                   );
  T1->SetBranchAddress("Jet1PuppiSDptSubjetCorrUp"                   , & Jet1PuppiSDptSubjetCorrUp                 );
  T1->SetBranchAddress("Jet1PuppiSDptSubjetCorrDn"                   , & Jet1PuppiSDptSubjetCorrDn                 );
  // T1->SetBranchAddress("Jet1PuppiSDptSubjetCorrL23Smear"          , & Jet1PuppiSDptSubjetCorrL23Smear           );
  // T1->SetBranchAddress("Jet1PuppiSDptSubjetCorrL23SmearUp"        , & Jet1PuppiSDptSubjetCorrL23SmearUp         );
  // T1->SetBranchAddress("Jet1PuppiSDptSubjetCorrL23SmearDn"        , & Jet1PuppiSDptSubjetCorrL23SmearDn         );
  T1->SetBranchAddress("Jet1PuppiSDeta"                        , & Jet1PuppiSDeta                      );
  T1->SetBranchAddress("Jet1PuppiSDphi"                        , & Jet1PuppiSDphi                      );
                       
  T1->SetBranchAddress("Jet1PuppiTau1"                         , & Jet1PuppiTau1                       );                                      
  T1->SetBranchAddress("Jet1PuppiTau2"                         , & Jet1PuppiTau2                       );                                      
  T1->SetBranchAddress("Jet1PuppiTau3"                         , & Jet1PuppiTau3                       );                                      
  T1->SetBranchAddress("Jet1PuppiTau4"                         , & Jet1PuppiTau4                       );                                      
  T1->SetBranchAddress("Jet1PuppiTau32"                        , & Jet1PuppiTau32                      );                                       
  T1->SetBranchAddress("Jet1PuppiTau21"                        , & Jet1PuppiTau21                      );                                       
  T1->SetBranchAddress("Jet1PuppiSDmaxbdisc"                   , & Jet1PuppiSDmaxbdisc                 );                                            
  T1->SetBranchAddress("Jet1PuppiSDmaxbdiscflavHadron"         , & Jet1PuppiSDmaxbdiscflavHadron       );                                                
  T1->SetBranchAddress("Jet1PuppiSDmaxbdiscflavParton"         , & Jet1PuppiSDmaxbdiscflavParton       );                                                
  T1->SetBranchAddress("Jet1PuppiSDsubjet0pt"                  , & Jet1PuppiSDsubjet0pt                );                                             
  T1->SetBranchAddress("Jet1PuppiSDsubjet0mass"                , & Jet1PuppiSDsubjet0mass              );    
  T1->SetBranchAddress("Jet1PuppiSDsubjet0eta"                 , & Jet1PuppiSDsubjet0eta               );
  T1->SetBranchAddress("Jet1PuppiSDsubjet0phi"                 , & Jet1PuppiSDsubjet0phi               );                                           
  T1->SetBranchAddress("Jet1PuppiSDsubjet0area"                , & Jet1PuppiSDsubjet0area              );                                               
  T1->SetBranchAddress("Jet1PuppiSDsubjet0flavHadron"          , & Jet1PuppiSDsubjet0flavHadron        );                                               
  T1->SetBranchAddress("Jet1PuppiSDsubjet0flavParton"          , & Jet1PuppiSDsubjet0flavParton        ); 
  T1->SetBranchAddress("Jet1PuppiSDsubjet0tau1"                , & Jet1PuppiSDsubjet0tau1              );
  T1->SetBranchAddress("Jet1PuppiSDsubjet0tau2"                , & Jet1PuppiSDsubjet0tau2              );
  T1->SetBranchAddress("Jet1PuppiSDsubjet0tau3"                , & Jet1PuppiSDsubjet0tau3              );
  T1->SetBranchAddress("Jet1PuppiSDsubjet0bdisc"               , & Jet1PuppiSDsubjet0bdisc             );                                                                                         
  T1->SetBranchAddress("Jet1PuppiSDsubjet1pt"                  , & Jet1PuppiSDsubjet1pt                );                                             
  T1->SetBranchAddress("Jet1PuppiSDsubjet1mass"                , & Jet1PuppiSDsubjet1mass              );  
  T1->SetBranchAddress("Jet1PuppiSDsubjet1eta"                 , & Jet1PuppiSDsubjet1eta               );
  T1->SetBranchAddress("Jet1PuppiSDsubjet1phi"                 , & Jet1PuppiSDsubjet1phi               );                                             
  T1->SetBranchAddress("Jet1PuppiSDsubjet1area"                , & Jet1PuppiSDsubjet1area              );                                               
  T1->SetBranchAddress("Jet1PuppiSDsubjet1flavHadron"          , & Jet1PuppiSDsubjet1flavHadron        );                                               
  T1->SetBranchAddress("Jet1PuppiSDsubjet1flavParton"          , & Jet1PuppiSDsubjet1flavParton        );    
  T1->SetBranchAddress("Jet1PuppiSDsubjet1tau1"                , & Jet1PuppiSDsubjet1tau1              );
  T1->SetBranchAddress("Jet1PuppiSDsubjet1tau2"                , & Jet1PuppiSDsubjet1tau2              );
  T1->SetBranchAddress("Jet1PuppiSDsubjet1tau3"                , & Jet1PuppiSDsubjet1tau3              ); 
  T1->SetBranchAddress("Jet1PuppiSDsubjet1bdisc"               , & Jet1PuppiSDsubjet1bdisc             );                                                                                       
  T1->SetBranchAddress("Jet1CHF"                               , & Jet1CHF                             );                                
  T1->SetBranchAddress("Jet1NHF"                               , & Jet1NHF                             );                                
  T1->SetBranchAddress("Jet1CM"                                , & Jet1CM                              );                               
  T1->SetBranchAddress("Jet1NM"                                , & Jet1NM                              );                               
  T1->SetBranchAddress("Jet1NEF"                               , & Jet1NEF                             );                                
  T1->SetBranchAddress("Jet1CEF"                               , & Jet1CEF                             );                                
  T1->SetBranchAddress("Jet1MF"                                , & Jet1MF                              );                               
  T1->SetBranchAddress("Jet1Mult"                              , & Jet1Mult                            );                                 
  T1->SetBranchAddress("Jet1MassCorrFactor"                    , & Jet1MassCorrFactor                  );                                           
  T1->SetBranchAddress("Jet1MassCorrFactorUp"                  , & Jet1MassCorrFactorUp                );                                             
  T1->SetBranchAddress("Jet1MassCorrFactorDn"                  , & Jet1MassCorrFactorDn                );                                             
  T1->SetBranchAddress("Jet1CorrFactor"                        , & Jet1CorrFactor                      );                                       
  T1->SetBranchAddress("Jet1CorrFactorUp"                      , & Jet1CorrFactorUp                    );                                         
  T1->SetBranchAddress("Jet1CorrFactorDn"                      , & Jet1CorrFactorDn                    );                                         
  T1->SetBranchAddress("Jet1PtSmearFactor"                     , & Jet1PtSmearFactor                   );                                          
  T1->SetBranchAddress("Jet1PtSmearFactorUp"                   , & Jet1PtSmearFactorUp                 );                                            
  T1->SetBranchAddress("Jet1PtSmearFactorDn"                   , & Jet1PtSmearFactorDn                 );                                            
  T1->SetBranchAddress("Jet1PuppiMassCorrFactor"               , & Jet1PuppiMassCorrFactor             );                                                
  T1->SetBranchAddress("Jet1PuppiMassCorrFactorUp"             , & Jet1PuppiMassCorrFactorUp           );                                                  
  T1->SetBranchAddress("Jet1PuppiMassCorrFactorDn"             , & Jet1PuppiMassCorrFactorDn           );                                                  
  T1->SetBranchAddress("Jet1PuppiCorrFactor"                   , & Jet1PuppiCorrFactor                 );                                            
  T1->SetBranchAddress("Jet1PuppiCorrFactorUp"                 , & Jet1PuppiCorrFactorUp               );                                              
  T1->SetBranchAddress("Jet1PuppiCorrFactorDn"                 , & Jet1PuppiCorrFactorDn               );                                              
  T1->SetBranchAddress("Jet1PuppiPtSmearFactor"                , & Jet1PuppiPtSmearFactor              );                                               
  T1->SetBranchAddress("Jet1PuppiPtSmearFactorUp"              , & Jet1PuppiPtSmearFactorUp            );                                                 
  T1->SetBranchAddress("Jet1PuppiPtSmearFactorDn"              , & Jet1PuppiPtSmearFactorDn            );                                                 
  // T1->SetBranchAddress("Jet1EtaScaleFactor"                    , & Jet1EtaScaleFactor                  );                                           
  // T1->SetBranchAddress("Jet1PhiScaleFactor"                    , & Jet1PhiScaleFactor                  );                                           
  //  T1->SetBranchAddress("Jet1MatchedGenJetDR"                   , & Jet1MatchedGenJetDR                 );                                            
  T1->SetBranchAddress("Jet1MatchedGenJetPt"                   , & Jet1MatchedGenJetPt                 );                                            
  T1->SetBranchAddress("Jet1MatchedGenJetMass"                 , & Jet1MatchedGenJetMass               ); 
                      
  T1->SetBranchAddress("Jet1GenMatched_TopHadronic"            , & Jet1GenMatched_TopHadronic          );      
  T1->SetBranchAddress("Jet1GenMatched_TopPt"                  , & Jet1GenMatched_TopPt                );      
  T1->SetBranchAddress("Jet1GenMatched_TopEta"                 , & Jet1GenMatched_TopEta               );      
  T1->SetBranchAddress("Jet1GenMatched_TopPhi"                 , & Jet1GenMatched_TopPhi               );      
  T1->SetBranchAddress("Jet1GenMatched_TopMass"                , & Jet1GenMatched_TopMass              );      
  T1->SetBranchAddress("Jet1GenMatched_bPt"                    , & Jet1GenMatched_bPt                  );      
  T1->SetBranchAddress("Jet1GenMatched_WPt"                    , & Jet1GenMatched_WPt                  );      
  T1->SetBranchAddress("Jet1GenMatched_Wd1Pt"                  , & Jet1GenMatched_Wd1Pt                );      
  T1->SetBranchAddress("Jet1GenMatched_Wd2Pt"                  , & Jet1GenMatched_Wd2Pt                );      
  T1->SetBranchAddress("Jet1GenMatched_Wd1ID"                  , & Jet1GenMatched_Wd1ID                );      
  T1->SetBranchAddress("Jet1GenMatched_Wd2ID"                  , & Jet1GenMatched_Wd2ID                );      
  T1->SetBranchAddress("Jet1GenMatched_MaxDeltaRPartonTop"     , & Jet1GenMatched_MaxDeltaRPartonTop   );      
  T1->SetBranchAddress("Jet1GenMatched_MaxDeltaRWPartonTop"    , & Jet1GenMatched_MaxDeltaRWPartonTop  );      
  T1->SetBranchAddress("Jet1GenMatched_MaxDeltaRWPartonW"      , & Jet1GenMatched_MaxDeltaRWPartonW    );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_t_b"             , & Jet1GenMatched_DeltaR_t_b           );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_t_W"             , & Jet1GenMatched_DeltaR_t_W           );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_t_Wd1"           , & Jet1GenMatched_DeltaR_t_Wd1         );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_t_Wd2"           , & Jet1GenMatched_DeltaR_t_Wd2         );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_W_b1"            , & Jet1GenMatched_DeltaR_W_b1          );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_W_Wd1"           , & Jet1GenMatched_DeltaR_W_Wd1         );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_W_Wd2"           , & Jet1GenMatched_DeltaR_W_Wd2         );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_Wd1_Wd2"         , & Jet1GenMatched_DeltaR_Wd1_Wd2       );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_Wd1_b"           , & Jet1GenMatched_DeltaR_Wd1_b         );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_Wd2_b"           , & Jet1GenMatched_DeltaR_Wd2_b         );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_jet_t"           , & Jet1GenMatched_DeltaR_jet_t         );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_jet_W"           , & Jet1GenMatched_DeltaR_jet_W         );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_jet_b"           , & Jet1GenMatched_DeltaR_jet_b         );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_jet_Wd1"         , & Jet1GenMatched_DeltaR_jet_Wd1       );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_jet_Wd2"         , & Jet1GenMatched_DeltaR_jet_Wd2       );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_pup0_b"          , & Jet1GenMatched_DeltaR_pup0_b        );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_pup0_Wd1"        , & Jet1GenMatched_DeltaR_pup0_Wd1      );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_pup0_Wd2"        , & Jet1GenMatched_DeltaR_pup0_Wd2      );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_pup1_b"          , & Jet1GenMatched_DeltaR_pup1_b        );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_pup1_Wd1"        , & Jet1GenMatched_DeltaR_pup1_Wd1      );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_pup1_Wd2"        , & Jet1GenMatched_DeltaR_pup1_Wd2      );               
  T1->SetBranchAddress("Jet1GenMatched_partonPt"               , & Jet1GenMatched_partonPt             );      
  T1->SetBranchAddress("Jet1GenMatched_partonEta"              , & Jet1GenMatched_partonEta            );      
  T1->SetBranchAddress("Jet1GenMatched_partonPhi"              , & Jet1GenMatched_partonPhi            );      
  T1->SetBranchAddress("Jet1GenMatched_partonMass"             , & Jet1GenMatched_partonMass           );      
  T1->SetBranchAddress("Jet1GenMatched_partonID"               , & Jet1GenMatched_partonID             );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaRjetParton"        , & Jet1GenMatched_DeltaRjetParton      );      

  T1->SetBranchAddress("AllHadMETpx"                           , & AllHadMETpx                         );                                    
  T1->SetBranchAddress("AllHadMETpy"                           , & AllHadMETpy                         );                                    
  T1->SetBranchAddress("AllHadMETpt"                           , & AllHadMETpt                         );                                    
  T1->SetBranchAddress("AllHadMETphi"                          , & AllHadMETphi                        );                                     
  T1->SetBranchAddress("AllHadMETsumET"                        , & AllHadMETsumET                      );                                     
  T1->SetBranchAddress("AllHadNvtx"                            , & AllHadNvtx                          );                                   
  T1->SetBranchAddress("AllHadNvtxGood"                            , & AllHadNvtxGood                          );                                   
  T1->SetBranchAddress("AllHadRho"                             , & AllHadRho                           );                                  
  T1->SetBranchAddress("AllHadEventWeight"                     , & AllHadEventWeight                   );                                          
  T1->SetBranchAddress("AllHadPUweight"                        , & AllHadPUweight                      );
  T1->SetBranchAddress("AllHadPUweight_MBup"                   , & AllHadPUweight_MBup                ); 
  T1->SetBranchAddress("AllHadPUweight_MBdn"                   , & AllHadPUweight_MBdn                ); 
     
  T1->SetBranchAddress("DijetMass"                             , & DijetMass                           );                                  
  T1->SetBranchAddress("DijetMassPuppi"                        , & DijetMassPuppi                      );                                  
  T1->SetBranchAddress("DijetDeltaR"                           , & DijetDeltaR                         );                                    
  T1->SetBranchAddress("DijetDeltaPhi"                         , & DijetDeltaPhi                       );                                      
  T1->SetBranchAddress("DijetDeltaRap"                         , & DijetDeltaRap                       ); 
  T1->SetBranchAddress("DiGenJetMass"                          , & DiGenJetMass                        ); 
  T1->SetBranchAddress("GenTTmass"                             , & GenTTmass                           );                                  
  T1->SetBranchAddress("HT"                                    , & HT                                  );                           
  T1->SetBranchAddress("HT_CorrDn"                             , & HT_CorrDn                           );                                  
  T1->SetBranchAddress("HT_CorrUp"                             , & HT_CorrUp                           );                                  
  T1->SetBranchAddress("HT_PtSmearNom"                         , & HT_PtSmearNom                       ); 
  T1->SetBranchAddress("HT_PtSmearUp"                          , & HT_PtSmearUp                        ); 
  T1->SetBranchAddress("HT_PtSmearDn"                          , & HT_PtSmearDn                        ); 
  T1->SetBranchAddress("Q2weight_CorrDn"                       , & Q2weight_CorrDn                     ); 
  T1->SetBranchAddress("Q2weight_CorrUp"                       , & Q2weight_CorrUp                     ); 
  T1->SetBranchAddress("NNPDF3weight_CorrDn"                   , & NNPDF3weight_CorrDn                 ); 
  T1->SetBranchAddress("NNPDF3weight_CorrUp"                   , & NNPDF3weight_CorrUp                 ); 
  T1->SetBranchAddress("AllHadRunNum"                          , & AllHadRunNum                        ); 
  T1->SetBranchAddress("AllHadLumiBlock"                       , & AllHadLumiBlock                     ); 
  T1->SetBranchAddress("AllHadEventNum"                        , & AllHadEventNum                      );                                       
  T1->SetBranchAddress("AllHadTrigAcceptBits"                  , & AllHadTrigAcceptBits                );

  cout<<"ignoring branches"<<endl;
  //ignore other branches                                                                                                                    
  T1->SetBranchStatus("*",0);
  T1->SetBranchStatus("PassMETFilters",1);
  T1->SetBranchStatus("Jet0PtRaw",1);
  T1->SetBranchStatus("Jet0EtaRaw",1);
  T1->SetBranchStatus("Jet0PhiRaw",1);
  T1->SetBranchStatus("Jet0MassRaw",1);
  // T1->SetBranchStatus("Jet0P",1);
  // T1->SetBranchStatus("Jet0Pt",1);
  // T1->SetBranchStatus("Jet0Eta",1);
  // T1->SetBranchStatus("Jet0Phi",1);
  // T1->SetBranchStatus("Jet0Rap",1);
  // T1->SetBranchStatus("Jet0Energy",1);
  // T1->SetBranchStatus("Jet0Mass",1);
  // T1->SetBranchStatus("Jet0Area",1);
  T1->SetBranchStatus("Jet0SDmass",1);
  T1->SetBranchStatus("Jet0SDmassRaw",1);
  if (run_kinematic) T1->SetBranchStatus("Jet0SDmassCorrL23",1); 
  if (run_kinematic) T1->SetBranchStatus("Jet0SDmassCorrL23Up",1); 
  if (run_kinematic) T1->SetBranchStatus("Jet0SDmassCorrL23Dn",1);  
  if (run_kinematic) T1->SetBranchStatus("Jet0SDmassCorrL23Smear",1); 
  if (run_kinematic) T1->SetBranchStatus("Jet0SDmassCorrL23SmearUp",1); 
  if (run_kinematic) T1->SetBranchStatus("Jet0SDmassCorrL23SmearDn",1);  
  if (run_kinematic) T1->SetBranchStatus("Jet0SDmassCorrL123",1); 
  if (run_kinematic) T1->SetBranchStatus("Jet0SDmassCorrL123Up",1); 
  if (run_kinematic) T1->SetBranchStatus("Jet0SDmassCorrL123Dn",1);  
  // T1->SetBranchStatus("Jet0SDptRaw",1); 
  // T1->SetBranchStatus("Jet0SDptCorrL23",1); 
  // T1->SetBranchStatus("Jet0SDptCorrL23Up",1); 
  // T1->SetBranchStatus("Jet0SDptCorrL23Dn",1); 
  // T1->SetBranchStatus("Jet0SDptCorrL123",1); 
  // T1->SetBranchStatus("Jet0SDptCorrL123Up",1); 
  // T1->SetBranchStatus("Jet0SDptCorrL123Dn",1); 
  // T1->SetBranchStatus("Jet0SDptCorrL23Smear",1); 
  // T1->SetBranchStatus("Jet0SDptCorrL23SmearUp",1); 
  // T1->SetBranchStatus("Jet0SDptCorrL23SmearDn",1); 
  // T1->SetBranchStatus("Jet0SDetaRaw",1); 
  // T1->SetBranchStatus("Jet0SDphiRaw",1); 
  // T1->SetBranchStatus("Jet0MassPruned",1);
  // T1->SetBranchStatus("Jet0MassTrimmed",1);
  if (run_kinematic) T1->SetBranchStatus("Jet0Tau1",1);
  if (run_kinematic) T1->SetBranchStatus("Jet0Tau2",1);
  if (run_kinematic) T1->SetBranchStatus("Jet0Tau3",1);
  if (run_kinematic) T1->SetBranchStatus("Jet0Tau4",1);
  if (run_kinematic) T1->SetBranchStatus("Jet0Tau21",1);

  T1->SetBranchStatus("Jet0Tau32",1);
  T1->SetBranchStatus("Jet0SDsubjet0bdisc",1);
  T1->SetBranchStatus("Jet0SDsubjet1bdisc",1);
  T1->SetBranchStatus("Jet0SDmaxbdisc",1);
  // T1->SetBranchStatus("Jet0SDmaxbdiscflavHadron",1);
  // T1->SetBranchStatus("Jet0SDmaxbdiscflavParton",1);
  T1->SetBranchStatus("Jet0SDsubjet0pt",1);
  T1->SetBranchStatus("Jet0SDsubjet0mass",1);
  T1->SetBranchStatus("Jet0SDsubjet0eta",1);
  T1->SetBranchStatus("Jet0SDsubjet0phi",1);
  // T1->SetBranchStatus("Jet0SDsubjet0area",1);
  // T1->SetBranchStatus("Jet0SDsubjet0flavHadron",1);
  // T1->SetBranchStatus("Jet0SDsubjet0flavParton",1);
  T1->SetBranchStatus("Jet0SDsubjet0tau1",1);
  T1->SetBranchStatus("Jet0SDsubjet0tau2",1);
  // T1->SetBranchStatus("Jet0SDsubjet0tau3",1);
  T1->SetBranchStatus("Jet0SDsubjet1pt",1);
  T1->SetBranchStatus("Jet0SDsubjet1mass",1);
  T1->SetBranchStatus("Jet0SDsubjet1eta",1);
  T1->SetBranchStatus("Jet0SDsubjet1phi",1);
  // T1->SetBranchStatus("Jet0SDsubjet1area",1);
  // T1->SetBranchStatus("Jet0SDsubjet1flavHadron",1);
  // T1->SetBranchStatus("Jet0SDsubjet1flavParton",1);
  T1->SetBranchStatus("Jet0SDsubjet1tau1",1);
  T1->SetBranchStatus("Jet0SDsubjet1tau2",1);
  // T1->SetBranchStatus("Jet0SDsubjet1tau3",1);
  T1->SetBranchStatus("Jet0PuppiPt",1);
  T1->SetBranchStatus("Jet0PuppiEta",1);
  T1->SetBranchStatus("Jet0PuppiPhi",1);
  T1->SetBranchStatus("Jet0PuppiMass",1);

  T1->SetBranchStatus("Jet0PuppiSDmass",1);
  // T1->SetBranchStatus("Jet0PuppiSDmassSubjetCorr",1);
  // T1->SetBranchStatus("Jet0PuppiSDmassSubjetCorrUp",1);
  // T1->SetBranchStatus("Jet0PuppiSDmassSubjetCorrDn",1);
  // T1->SetBranchStatus("Jet0PuppiSDmassSubjetCorrL23Smear",1);
  // T1->SetBranchStatus("Jet0PuppiSDmassSubjetCorrL23SmearUp",1);
  // T1->SetBranchStatus("Jet0PuppiSDmassSubjetCorrL23SmearDn",1);
  T1->SetBranchStatus("Jet0PuppiSDpt",1);
  // T1->SetBranchStatus("Jet0PuppiSDptSubjetCorr",1);
  // T1->SetBranchStatus("Jet0PuppiSDptSubjetCorrUp",1);
  // T1->SetBranchStatus("Jet0PuppiSDptSubjetCorrDn",1);
  // T1->SetBranchStatus("Jet0PuppiSDptSubjetCorrL23Smear",1);
  // T1->SetBranchStatus("Jet0PuppiSDptSubjetCorrL23SmearUp",1);
  // T1->SetBranchStatus("Jet0PuppiSDptSubjetCorrL23SmearDn",1);
  // T1->SetBranchStatus("Jet0PuppiSDeta",1);
  // T1->SetBranchStatus("Jet0PuppiSDphi",1);

  if (run_kinematic) T1->SetBranchStatus("Jet0PuppiTau1",1);
  if (run_kinematic) T1->SetBranchStatus("Jet0PuppiTau2",1);
  if (run_kinematic) T1->SetBranchStatus("Jet0PuppiTau3",1);
  if (run_kinematic) T1->SetBranchStatus("Jet0PuppiTau4",1);
  if (run_kinematic) T1->SetBranchStatus("Jet0PuppiTau21",1);
  T1->SetBranchStatus("Jet0PuppiTau32",1);
  T1->SetBranchStatus("Jet0PuppiSDsubjet0bdisc",1);
  T1->SetBranchStatus("Jet0PuppiSDsubjet1bdisc",1);
  T1->SetBranchStatus("Jet0PuppiSDmaxbdisc",1);
  // T1->SetBranchStatus("Jet0PuppiSDmaxbdiscflavHadron",1);
  // T1->SetBranchStatus("Jet0PuppiSDmaxbdiscflavParton",1);
  T1->SetBranchStatus("Jet0PuppiSDsubjet0pt",1);
  T1->SetBranchStatus("Jet0PuppiSDsubjet0mass",1);
  T1->SetBranchStatus("Jet0PuppiSDsubjet0eta",1);
  T1->SetBranchStatus("Jet0PuppiSDsubjet0phi",1);
  // T1->SetBranchStatus("Jet0PuppiSDsubjet0area",1);
  // T1->SetBranchStatus("Jet0PuppiSDsubjet0flavHadron",1);
  // T1->SetBranchStatus("Jet0PuppiSDsubjet0flavParton",1);
  T1->SetBranchStatus("Jet0PuppiSDsubjet0tau1",1);
  T1->SetBranchStatus("Jet0PuppiSDsubjet0tau2",1);
  // T1->SetBranchStatus("Jet0PuppiSDsubjet0tau3",1);
  T1->SetBranchStatus("Jet0PuppiSDsubjet1pt",1);
  T1->SetBranchStatus("Jet0PuppiSDsubjet1mass",1);
  T1->SetBranchStatus("Jet0PuppiSDsubjet1eta",1);
  T1->SetBranchStatus("Jet0PuppiSDsubjet1phi",1);
  // T1->SetBranchStatus("Jet0PuppiSDsubjet1area",1);
  // T1->SetBranchStatus("Jet0PuppiSDsubjet1flavHadron",1);
  // T1->SetBranchStatus("Jet0PuppiSDsubjet1flavParton",1);
  T1->SetBranchStatus("Jet0PuppiSDsubjet1tau1",1);
  T1->SetBranchStatus("Jet0PuppiSDsubjet1tau2",1);
  // T1->SetBranchStatus("Jet0PuppiSDsubjet1tau3",1);
  if (run_kinematic) T1->SetBranchStatus("Jet0CHF",1);
  if (run_kinematic) T1->SetBranchStatus("Jet0NHF",1);
  if (run_kinematic) T1->SetBranchStatus("Jet0CM",1);
  if (run_kinematic) T1->SetBranchStatus("Jet0NM",1);
  if (run_kinematic) T1->SetBranchStatus("Jet0NEF",1);
  if (run_kinematic) T1->SetBranchStatus("Jet0CEF",1);
  if (run_kinematic) T1->SetBranchStatus("Jet0MF",1);
  if (run_kinematic) T1->SetBranchStatus("Jet0Mult",1);

  if (run_kinematic) T1->SetBranchStatus("Jet0PuppiCHF",1);
  if (run_kinematic) T1->SetBranchStatus("Jet0PuppiNHF",1);
  if (run_kinematic) T1->SetBranchStatus("Jet0PuppiCM",1);
  if (run_kinematic) T1->SetBranchStatus("Jet0PuppiNM",1);
  if (run_kinematic) T1->SetBranchStatus("Jet0PuppiNEF",1);
  if (run_kinematic) T1->SetBranchStatus("Jet0PuppiCEF",1);
  if (run_kinematic) T1->SetBranchStatus("Jet0PuppiMF",1);
  if (run_kinematic) T1->SetBranchStatus("Jet0PuppiMult",1);

  T1->SetBranchStatus("Jet0MassCorrFactor",1);
  T1->SetBranchStatus("Jet0MassCorrFactorUp",1);
  T1->SetBranchStatus("Jet0MassCorrFactorDn",1);
  T1->SetBranchStatus("Jet0CorrFactor",1);
  T1->SetBranchStatus("Jet0CorrFactorUp",1);
  T1->SetBranchStatus("Jet0CorrFactorDn",1);
  T1->SetBranchStatus("Jet0PtSmearFactor",1);
  T1->SetBranchStatus("Jet0PtSmearFactorUp",1);
  T1->SetBranchStatus("Jet0PtSmearFactorDn",1);
  T1->SetBranchStatus("Jet0PuppiMassCorrFactor",1);
  T1->SetBranchStatus("Jet0PuppiMassCorrFactorUp",1);
  T1->SetBranchStatus("Jet0PuppiMassCorrFactorDn",1);
  T1->SetBranchStatus("Jet0PuppiCorrFactor",1);
  T1->SetBranchStatus("Jet0PuppiCorrFactorUp",1);
  T1->SetBranchStatus("Jet0PuppiCorrFactorDn",1);
  T1->SetBranchStatus("Jet0PuppiPtSmearFactor",1);
  T1->SetBranchStatus("Jet0PuppiPtSmearFactorUp",1);
  T1->SetBranchStatus("Jet0PuppiPtSmearFactorDn",1);
  // T1->SetBranchStatus("Jet0EtaScaleFactor",1);
  // T1->SetBranchStatus("Jet0PhiScaleFactor",1);
  // T1->SetBranchStatus("Jet0MatchedGenJetDR",1);
  T1->SetBranchStatus("Jet0MatchedGenJetPt",1);
  // T1->SetBranchStatus("Jet0MatchedGenJetMass",1);

  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet0GenMatched_TopHadronic",1);
  // T1->SetBranchStatus("Jet0GenMatched_TopPt",1);
  // T1->SetBranchStatus("Jet0GenMatched_TopEta",1);
  // T1->SetBranchStatus("Jet0GenMatched_TopPhi",1);
  // T1->SetBranchStatus("Jet0GenMatched_TopMass",1);
  // T1->SetBranchStatus("Jet0GenMatched_bPt",1);
  // T1->SetBranchStatus("Jet0GenMatched_WPt",1);
  // T1->SetBranchStatus("Jet0GenMatched_Wd1Pt",1);
  // T1->SetBranchStatus("Jet0GenMatched_Wd2Pt",1);
  // T1->SetBranchStatus("Jet0GenMatched_Wd1ID",1);
  // T1->SetBranchStatus("Jet0GenMatched_Wd2ID",1);
  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet0GenMatched_MaxDeltaRPartonTop",1);
  // T1->SetBranchStatus("Jet0GenMatched_MaxDeltaRWPartonTop",1);
  // T1->SetBranchStatus("Jet0GenMatched_MaxDeltaRWPartonW",1);
  // T1->SetBranchStatus("Jet0GenMatched_DeltaR_t_b",1);
  // T1->SetBranchStatus("Jet0GenMatched_DeltaR_t_W",1);
  // T1->SetBranchStatus("Jet0GenMatched_DeltaR_t_Wd1",1);
  // T1->SetBranchStatus("Jet0GenMatched_DeltaR_t_Wd2",1);
  // T1->SetBranchStatus("Jet0GenMatched_DeltaR_W_b1",1);
  // T1->SetBranchStatus("Jet0GenMatched_DeltaR_W_Wd1",1);
  // T1->SetBranchStatus("Jet0GenMatched_DeltaR_W_Wd2",1);
  // T1->SetBranchStatus("Jet0GenMatched_DeltaR_Wd1_Wd2",1);
  // T1->SetBranchStatus("Jet0GenMatched_DeltaR_Wd1_b",1);
  // T1->SetBranchStatus("Jet0GenMatched_DeltaR_Wd2_b",1);
  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet0GenMatched_DeltaR_jet_t",1);
  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet0GenMatched_DeltaR_jet_W",1);
  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet0GenMatched_DeltaR_jet_b",1);
  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet0GenMatched_DeltaR_jet_Wd1",1);
  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet0GenMatched_DeltaR_jet_Wd2",1);
  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet0GenMatched_DeltaR_pup0_b",1);
  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet0GenMatched_DeltaR_pup0_Wd1",1);
  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet0GenMatched_DeltaR_pup0_Wd2",1);
  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet0GenMatched_DeltaR_pup1_b",1);
  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet0GenMatched_DeltaR_pup1_Wd1",1);
  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet0GenMatched_DeltaR_pup1_Wd2",1);
  // T1->SetBranchStatus("Jet0GenMatched_partonPt",1);
  // T1->SetBranchStatus("Jet0GenMatched_partonEta",1);
  // T1->SetBranchStatus("Jet0GenMatched_partonPhi",1);
  // T1->SetBranchStatus("Jet0GenMatched_partonMass",1);
  // T1->SetBranchStatus("Jet0GenMatched_partonID",1);
  // T1->SetBranchStatus("Jet0GenMatched_DeltaRjetParton",1);

  T1->SetBranchStatus("Jet1PtRaw",1);
  T1->SetBranchStatus("Jet1EtaRaw",1);
  T1->SetBranchStatus("Jet1PhiRaw",1);
  T1->SetBranchStatus("Jet1MassRaw",1);
  // T1->SetBranchStatus("Jet1P",1);
  // T1->SetBranchStatus("Jet1Pt",1);
  // T1->SetBranchStatus("Jet1Eta",1);
  // T1->SetBranchStatus("Jet1Phi",1);
  // T1->SetBranchStatus("Jet1Rap",1);
  // T1->SetBranchStatus("Jet1Energy",1);
  // T1->SetBranchStatus("Jet1Mass",1);
  // T1->SetBranchStatus("Jet1Area",1);
  T1->SetBranchStatus("Jet1SDmass",1);
  T1->SetBranchStatus("Jet1SDmassRaw",1);
  if (run_kinematic) T1->SetBranchStatus("Jet1SDmassCorrL23",1);
  if (run_kinematic) T1->SetBranchStatus("Jet1SDmassCorrL23Up",1);
  if (run_kinematic) T1->SetBranchStatus("Jet1SDmassCorrL23Dn",1);
  if (run_kinematic) T1->SetBranchStatus("Jet1SDmassCorrL123",1);
  if (run_kinematic) T1->SetBranchStatus("Jet1SDmassCorrL123Up",1);
  if (run_kinematic) T1->SetBranchStatus("Jet1SDmassCorrL123Dn",1);
  if (run_kinematic) T1->SetBranchStatus("Jet1SDmassCorrL23Smear",1);
  if (run_kinematic) T1->SetBranchStatus("Jet1SDmassCorrL23SmearUp",1);
  if (run_kinematic) T1->SetBranchStatus("Jet1SDmassCorrL23SmearDn",1);
 T1->SetBranchStatus("Jet1SDptRaw",1);
  // T1->SetBranchStatus("Jet1SDptCorrL23",1);
  // T1->SetBranchStatus("Jet1SDptCorrL23Up",1);
  // T1->SetBranchStatus("Jet1SDptCorrL23Dn",1);
  // T1->SetBranchStatus("Jet1SDptCorrL123",1);
  // T1->SetBranchStatus("Jet1SDptCorrL123Up",1);
  // T1->SetBranchStatus("Jet1SDptCorrL123Dn",1);
  // T1->SetBranchStatus("Jet1SDptCorrL23Smear",1);
  // T1->SetBranchStatus("Jet1SDptCorrL23SmearUp",1);
  // T1->SetBranchStatus("Jet1SDptCorrL23SmearDn",1);
  // T1->SetBranchStatus("Jet1SDetaRaw",1);
  // T1->SetBranchStatus("Jet1SDphiRaw",1); 
  // T1->SetBranchStatus("Jet1MassPruned",1);
  // T1->SetBranchStatus("Jet1MassTrimmed",1);
  if (run_kinematic)  T1->SetBranchStatus("Jet1Tau1",1);
  if (run_kinematic)  T1->SetBranchStatus("Jet1Tau2",1);
  if (run_kinematic)  T1->SetBranchStatus("Jet1Tau3",1);
  if (run_kinematic)  T1->SetBranchStatus("Jet1Tau4",1);
  T1->SetBranchStatus("Jet1Tau32",1);
  // T1->SetBranchStatus("Jet1Tau21",1);
  T1->SetBranchStatus("Jet1SDsubjet0bdisc",1);
  T1->SetBranchStatus("Jet1SDsubjet1bdisc",1);
  T1->SetBranchStatus("Jet1SDmaxbdisc",1);
  // T1->SetBranchStatus("Jet1SDmaxbdiscflavHadron",1);
  // T1->SetBranchStatus("Jet1SDmaxbdiscflavParton",1);
  T1->SetBranchStatus("Jet1SDsubjet0pt",1);
  T1->SetBranchStatus("Jet1SDsubjet0eta",1);
  T1->SetBranchStatus("Jet1SDsubjet0phi",1);
  T1->SetBranchStatus("Jet1SDsubjet0mass",1);
  // T1->SetBranchStatus("Jet1SDsubjet0area",1);
  // T1->SetBranchStatus("Jet1SDsubjet0flavHadron",1);
  // T1->SetBranchStatus("Jet1SDsubjet0flavParton",1);
  T1->SetBranchStatus("Jet1SDsubjet0tau1",1);
  T1->SetBranchStatus("Jet1SDsubjet0tau2",1);
  // T1->SetBranchStatus("Jet1SDsubjet0tau3",1);
  T1->SetBranchStatus("Jet1SDsubjet1pt",1);
  T1->SetBranchStatus("Jet1SDsubjet1eta",1);
  T1->SetBranchStatus("Jet1SDsubjet1phi",1);
  T1->SetBranchStatus("Jet1SDsubjet1mass",1);
  // T1->SetBranchStatus("Jet1SDsubjet1area",1);
  // T1->SetBranchStatus("Jet1SDsubjet1flavHadron",1);
  // T1->SetBranchStatus("Jet1SDsubjet1flavParton",1);
  T1->SetBranchStatus("Jet1SDsubjet1tau1",1);
  T1->SetBranchStatus("Jet1SDsubjet1tau2",1);
  // T1->SetBranchStatus("Jet1SDsubjet1tau3",1);
  T1->SetBranchStatus("Jet1PuppiPt",1);
  T1->SetBranchStatus("Jet1PuppiEta",1);
  T1->SetBranchStatus("Jet1PuppiPhi",1);
  T1->SetBranchStatus("Jet1PuppiMass",1);

  T1->SetBranchStatus("Jet1PuppiSDmass",1);
  // T1->SetBranchStatus("Jet1PuppiSDmassSubjetCorr",1);
  // T1->SetBranchStatus("Jet1PuppiSDmassSubjetCorrUp",1);
  // T1->SetBranchStatus("Jet1PuppiSDmassSubjetCorrDn",1);
  // T1->SetBranchStatus("Jet1PuppiSDmassSubjetCorrL23Smear",1);
  // T1->SetBranchStatus("Jet1PuppiSDmassSubjetCorrL23SmearUp",1);
  // T1->SetBranchStatus("Jet1PuppiSDmassSubjetCorrL23SmearDn",1);
  // T1->SetBranchStatus("Jet1PuppiSDpt",1);
  // T1->SetBranchStatus("Jet1PuppiSDptSubjetCorr",1);
  // T1->SetBranchStatus("Jet1PuppiSDptSubjetCorrUp",1);
  // T1->SetBranchStatus("Jet1PuppiSDptSubjetCorrDn",1);
  // T1->SetBranchStatus("Jet1PuppiSDptSubjetCorrL23Smear",1);
  // T1->SetBranchStatus("Jet1PuppiSDptSubjetCorrL23SmearUp",1);
  // T1->SetBranchStatus("Jet1PuppiSDptSubjetCorrL23SmearDn",1);
  // T1->SetBranchStatus("Jet1PuppiSDeta",1);
  // T1->SetBranchStatus("Jet1PuppiSDphi",1);

  if (run_kinematic) T1->SetBranchStatus("Jet1PuppiTau1",1);
  if (run_kinematic) T1->SetBranchStatus("Jet1PuppiTau2",1);
  if (run_kinematic) T1->SetBranchStatus("Jet1PuppiTau3",1);
  if (run_kinematic) T1->SetBranchStatus("Jet1PuppiTau4",1);
  T1->SetBranchStatus("Jet1PuppiTau32",1);
  // T1->SetBranchStatus("Jet1PuppiTau21",1);
  T1->SetBranchStatus("Jet1PuppiSDsubjet0bdisc",1);
  T1->SetBranchStatus("Jet1PuppiSDsubjet1bdisc",1);
  T1->SetBranchStatus("Jet1PuppiSDmaxbdisc",1);
  // T1->SetBranchStatus("Jet1PuppiSDmaxbdiscflavHadron",1);
  // T1->SetBranchStatus("Jet1PuppiSDmaxbdiscflavParton",1);
  T1->SetBranchStatus("Jet1PuppiSDsubjet0pt",1);
  T1->SetBranchStatus("Jet1PuppiSDsubjet0eta",1);
  T1->SetBranchStatus("Jet1PuppiSDsubjet0phi",1);
  T1->SetBranchStatus("Jet1PuppiSDsubjet0mass",1);
  // T1->SetBranchStatus("Jet1PuppiSDsubjet0area",1);
  // T1->SetBranchStatus("Jet1PuppiSDsubjet0flavHadron",1);
  // T1->SetBranchStatus("Jet1PuppiSDsubjet0flavParton",1);
  T1->SetBranchStatus("Jet1PuppiSDsubjet0tau1",1);
  T1->SetBranchStatus("Jet1PuppiSDsubjet0tau2",1);
  // T1->SetBranchStatus("Jet1PuppiSDsubjet0tau3",1);
  T1->SetBranchStatus("Jet1PuppiSDsubjet1pt",1);
  T1->SetBranchStatus("Jet1PuppiSDsubjet1eta",1);
  T1->SetBranchStatus("Jet1PuppiSDsubjet1phi",1);
  T1->SetBranchStatus("Jet1PuppiSDsubjet1mass",1);
  // T1->SetBranchStatus("Jet1PuppiSDsubjet1area",1);
  // T1->SetBranchStatus("Jet1PuppiSDsubjet1flavHadron",1);
  // T1->SetBranchStatus("Jet1PuppiSDsubjet1flavParton",1);
  T1->SetBranchStatus("Jet1PuppiSDsubjet1tau1",1);
  T1->SetBranchStatus("Jet1PuppiSDsubjet1tau2",1);
  // T1->SetBranchStatus("Jet1PuppiSDsubjet1tau3",1);
  if (run_kinematic) T1->SetBranchStatus("Jet1CHF",1);
  if (run_kinematic) T1->SetBranchStatus("Jet1NHF",1);
  if (run_kinematic) T1->SetBranchStatus("Jet1CM",1);
  if (run_kinematic) T1->SetBranchStatus("Jet1NM",1);
  if (run_kinematic) T1->SetBranchStatus("Jet1NEF",1);
  if (run_kinematic) T1->SetBranchStatus("Jet1CEF",1);
  if (run_kinematic) T1->SetBranchStatus("Jet1MF",1);
  if (run_kinematic) T1->SetBranchStatus("Jet1Mult",1);
  T1->SetBranchStatus("Jet1MassCorrFactor",1);
  T1->SetBranchStatus("Jet1MassCorrFactorUp",1);
  T1->SetBranchStatus("Jet1MassCorrFactorDn",1);
  T1->SetBranchStatus("Jet1CorrFactor",1);
  T1->SetBranchStatus("Jet1CorrFactorUp",1);
  T1->SetBranchStatus("Jet1CorrFactorDn",1);
  T1->SetBranchStatus("Jet1PtSmearFactor",1);
  T1->SetBranchStatus("Jet1PtSmearFactorUp",1);
  T1->SetBranchStatus("Jet1PtSmearFactorDn",1);
  // T1->SetBranchStatus("Jet1PuppiMassCorrFactor",1);
  // T1->SetBranchStatus("Jet1PuppiMassCorrFactorUp",1);
  // T1->SetBranchStatus("Jet1PuppiMassCorrFactorDn",1);
  T1->SetBranchStatus("Jet1PuppiCorrFactor",1);
  T1->SetBranchStatus("Jet1PuppiCorrFactorUp",1);
  T1->SetBranchStatus("Jet1PuppiCorrFactorDn",1);
  T1->SetBranchStatus("Jet1PuppiPtSmearFactor",1);
  T1->SetBranchStatus("Jet1PuppiPtSmearFactorUp",1);
  T1->SetBranchStatus("Jet1PuppiPtSmearFactorDn",1);
  // T1->SetBranchStatus("Jet1EtaScaleFactor",1);
  // T1->SetBranchStatus("Jet1PhiScaleFactor",1);
  // T1->SetBranchStatus("Jet1MatchedGenJetDR",1);
  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet1MatchedGenJetPt",1);
  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet1MatchedGenJetMass",1);

  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet1GenMatched_TopHadronic",1);
  // T1->SetBranchStatus("Jet1GenMatched_TopPt",1);
  // T1->SetBranchStatus("Jet1GenMatched_TopEta",1);
  // T1->SetBranchStatus("Jet1GenMatched_TopPhi",1);
  // T1->SetBranchStatus("Jet1GenMatched_TopMass",1);
  // T1->SetBranchStatus("Jet1GenMatched_bPt",1);
  // T1->SetBranchStatus("Jet1GenMatched_WPt",1);
  // T1->SetBranchStatus("Jet1GenMatched_Wd1Pt",1);
  // T1->SetBranchStatus("Jet1GenMatched_Wd2Pt",1);
  // T1->SetBranchStatus("Jet1GenMatched_Wd1ID",1);
  // T1->SetBranchStatus("Jet1GenMatched_Wd2ID",1);
  if (run_kinematic && !isData  ) T1->SetBranchStatus("Jet1GenMatched_MaxDeltaRPartonTop",1);
  // T1->SetBranchStatus("Jet1GenMatched_MaxDeltaRWPartonTop",1);
  // T1->SetBranchStatus("Jet1GenMatched_MaxDeltaRWPartonW",1);
  // T1->SetBranchStatus("Jet1GenMatched_DeltaR_t_b",1);
  // T1->SetBranchStatus("Jet1GenMatched_DeltaR_t_W",1);
  // T1->SetBranchStatus("Jet1GenMatched_DeltaR_t_Wd1",1);
  // T1->SetBranchStatus("Jet1GenMatched_DeltaR_t_Wd2",1);
  // T1->SetBranchStatus("Jet1GenMatched_DeltaR_W_b1",1);
  // T1->SetBranchStatus("Jet1GenMatched_DeltaR_W_Wd1",1);
  // T1->SetBranchStatus("Jet1GenMatched_DeltaR_W_Wd2",1);
  // T1->SetBranchStatus("Jet1GenMatched_DeltaR_Wd1_Wd2",1);
  // T1->SetBranchStatus("Jet1GenMatched_DeltaR_Wd1_b",1);
  // T1->SetBranchStatus("Jet1GenMatched_DeltaR_Wd2_b",1);
  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet1GenMatched_DeltaR_jet_t",1);
  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet1GenMatched_DeltaR_jet_W",1);
  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet1GenMatched_DeltaR_jet_b",1);
  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet1GenMatched_DeltaR_jet_Wd1",1);
  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet1GenMatched_DeltaR_jet_Wd2",1);
  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet1GenMatched_DeltaR_pup0_b",1);
  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet1GenMatched_DeltaR_pup0_Wd1",1);
  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet1GenMatched_DeltaR_pup0_Wd2",1);
  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet1GenMatched_DeltaR_pup1_b",1);
  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet1GenMatched_DeltaR_pup1_Wd1",1);
  if (run_kinematic && !isData ) T1->SetBranchStatus("Jet1GenMatched_DeltaR_pup1_Wd2",1);
  // T1->SetBranchStatus("Jet1GenMatched_partonPt",1);
  // T1->SetBranchStatus("Jet1GenMatched_partonEta",1);
  // T1->SetBranchStatus("Jet1GenMatched_partonPhi",1);
  // T1->SetBranchStatus("Jet1GenMatched_partonMass",1);
  // T1->SetBranchStatus("Jet1GenMatched_partonID",1);
  // T1->SetBranchStatus("Jet1GenMatched_DeltaRjetParton",1);

  // T1->SetBranchStatus("AllHadMETpx",1);  
  // T1->SetBranchStatus("AllHadMETpy",1);  
  T1->SetBranchStatus("AllHadMETpt",1);  
  // T1->SetBranchStatus("AllHadMETphi",1);  
  // T1->SetBranchStatus("AllHadMETsumET",1);  
  T1->SetBranchStatus("AllHadNvtx",1);  
  T1->SetBranchStatus("AllHadNvtxGood",1);  
  // T1->SetBranchStatus("AllHadNPUtrue",1);  
  // T1->SetBranchStatus("AllHadRho",1);  
  // T1->SetBranchStatus("AllHadEventWeight",1); 
  T1->SetBranchStatus("AllHadPUweight",1); 
  T1->SetBranchStatus("AllHadPUweight_MBup",1); 
  T1->SetBranchStatus("AllHadPUweight_MBdn",1);  
  // T1->SetBranchStatus("DijetMass",1);  
  // T1->SetBranchStatus("DijetMassPuppi",1);  
  // T1->SetBranchStatus("DijetDeltaR",1);  
  T1->SetBranchStatus("DijetDeltaPhi",1);  
  T1->SetBranchStatus("DijetDeltaRap",1);  
  if (run_kinematic)T1->SetBranchStatus("DiGenJetMass",1);  
  if (run_kinematic)T1->SetBranchStatus("GenTTmass",1);  
  T1->SetBranchStatus("HT",1);  
  T1->SetBranchStatus("HT_CorrDn",1);  
  T1->SetBranchStatus("HT_CorrUp",1);  
  T1->SetBranchStatus("HT_PtSmearNom",1);  
  T1->SetBranchStatus("HT_PtSmearUp",1);  
  T1->SetBranchStatus("HT_PtSmearDn",1);  
  // T1->SetBranchStatus("Q2weight_CorrDn",1);  
  // T1->SetBranchStatus("Q2weight_CorrUp",1);  
  // T1->SetBranchStatus("NNPDF3weight_CorrDn",1);  
  // T1->SetBranchStatus("NNPDF3weight_CorrUp",1);  
  T1->SetBranchStatus("AllHadRunNum",1);  
  T1->SetBranchStatus("AllHadLumiBlock",1);  
  T1->SetBranchStatus("AllHadEventNum",1); 

  T1->SetBranchStatus("AllHadTrigNames",1);
  T1->SetBranchStatus("AllHadTrigPrescales",1);
  T1->SetBranchStatus("AllHadTrigAcceptBits",1);
  cout<<"done setting up tree"<<endl;



    // 888b     d888 d8b          888                           .d8888b.           888                      
    // 8888b   d8888 Y8P          888                          d88P  Y88b          888                      
    // 88888b.d88888              888                          Y88b.               888                      
    // 888Y88888P888 888 .d8888b  888888  8888b.   .d88b.       "Y888b.    .d88b.  888888 888  888 88888b.  
    // 888 Y888P 888 888 88K      888        "88b d88P"88b         "Y88b. d8P  Y8b 888    888  888 888 "88b 
    // 888  Y8P  888 888 "Y8888b. 888    .d888888 888  888           "888 88888888 888    888  888 888  888 
    // 888   "   888 888      X88 Y88b.  888  888 Y88b 888     Y88b  d88P Y8b.     Y88b.  Y88b 888 888 d88P 
    // 888       888 888  88888P'  "Y888 "Y888888  "Y88888      "Y8888P"   "Y8888   "Y888  "Y88888 88888P"  
    //                                                 888                                         888      
    //                                            Y8b d88P                                         888      
    //                                             "Y88P"                                          888      



  // input MISTAG
  cout<<"get mistag histograms"<<endl;
  TFile * Fmistag            = new TFile(mistagFile.c_str()); 

  // mistag rate from CHS tag defintion
  TH1D * h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag       = (TH1D *) Fmistag->Get("h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag");
  TH1D * h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag       = (TH1D *) Fmistag->Get("h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag");
  TH1D * h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag       = (TH1D *) Fmistag->Get("h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag");
  TH1D * h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclu       = (TH1D *) Fmistag->Get("h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclusive");

  TH1D * h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag       = (TH1D *) Fmistag->Get("h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag");
  TH1D * h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag       = (TH1D *) Fmistag->Get("h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag");
  TH1D * h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag       = (TH1D *) Fmistag->Get("h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag");
  TH1D * h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclu       = (TH1D *) Fmistag->Get("h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclusive");

  TH1D * h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag       = (TH1D *) Fmistag->Get("h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag");
  TH1D * h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag       = (TH1D *) Fmistag->Get("h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag");
  TH1D * h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag       = (TH1D *) Fmistag->Get("h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag");
  TH1D * h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclu       = (TH1D *) Fmistag->Get("h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclusive");

  // mistag rate for PUPPI tag definition

  TH1D * h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_0btag     = (TH1D *) Fmistag->Get("h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_0btag");
  TH1D * h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_1btag     = (TH1D *) Fmistag->Get("h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_1btag");
  TH1D * h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_2btag     = (TH1D *) Fmistag->Get("h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_2btag");
  TH1D * h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_inclu     = (TH1D *) Fmistag->Get("h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_inclusive");

  TH1D * h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_0btag     = (TH1D *) Fmistag->Get("h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_0btag");
  TH1D * h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_1btag     = (TH1D *) Fmistag->Get("h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_1btag");
  TH1D * h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_2btag     = (TH1D *) Fmistag->Get("h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_2btag");
  TH1D * h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_inclu     = (TH1D *) Fmistag->Get("h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_inclusive");

  TH1D * h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_0btag     = (TH1D *) Fmistag->Get("h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_0btag");
  TH1D * h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_1btag     = (TH1D *) Fmistag->Get("h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_1btag");
  TH1D * h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_2btag     = (TH1D *) Fmistag->Get("h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_2btag");
  TH1D * h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_inclu     = (TH1D *) Fmistag->Get("h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_inclusive");

  // sideband tag defintion for data closure test [ (jet0sdmass > 90 && jet0sdmass < 110) || (jet0sdmass > 210 && jet0sdmass < 300) ]

  TH1D * h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag     = (TH1D *) Fmistag->Get("h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag");
  TH1D * h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag     = (TH1D *) Fmistag->Get("h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag");
  TH1D * h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag     = (TH1D *) Fmistag->Get("h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag");
  TH1D * h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclu     = (TH1D *) Fmistag->Get("h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclusive");

  TH1D * h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag     = (TH1D *) Fmistag->Get("h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag");
  TH1D * h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag     = (TH1D *) Fmistag->Get("h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag");
  TH1D * h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag     = (TH1D *) Fmistag->Get("h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag");
  TH1D * h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclu     = (TH1D *) Fmistag->Get("h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclusive");

  TH1D * h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag     = (TH1D *) Fmistag->Get("h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag");
  TH1D * h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag     = (TH1D *) Fmistag->Get("h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag");
  TH1D * h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag     = (TH1D *) Fmistag->Get("h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag");
  TH1D * h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclu     = (TH1D *) Fmistag->Get("h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclusive");

  // cout<<"h_mistag_vs_jetP_TagMassSDTau32_jetP_dRapHi_0btag     "<<h_mistag_vs_jetP_TagMassSDTau32_jetP_dRapHi_0btag     ->Integral() <<endl;
  // cout<<"h_mistag_vs_jetP_TagMassSDTau32_jetP_dRapHi_1btag     "<<h_mistag_vs_jetP_TagMassSDTau32_jetP_dRapHi_1btag     ->Integral() <<endl;
  // cout<<"h_mistag_vs_jetP_TagMassSDTau32_jetP_dRapHi_2btag     "<<h_mistag_vs_jetP_TagMassSDTau32_jetP_dRapHi_2btag     ->Integral() <<endl;
  // cout<<"h_mistag_vs_jetP_TagMassSDTau32_jetP_dRapHi_inclusive "<<h_mistag_vs_jetP_TagMassSDTau32_jetP_dRapHi_inclusive ->Integral() <<endl;
  // cout<<"h_mistag_vs_jetP_TagMassSDTau32_jetP_dRapLo_0btag     "<<h_mistag_vs_jetP_TagMassSDTau32_jetP_dRapLo_0btag     ->Integral() <<endl;
  // cout<<"h_mistag_vs_jetP_TagMassSDTau32_jetP_dRapLo_1btag     "<<h_mistag_vs_jetP_TagMassSDTau32_jetP_dRapLo_1btag     ->Integral() <<endl;
  // cout<<"h_mistag_vs_jetP_TagMassSDTau32_jetP_dRapLo_2btag     "<<h_mistag_vs_jetP_TagMassSDTau32_jetP_dRapLo_2btag     ->Integral() <<endl;
  // cout<<"h_mistag_vs_jetP_TagMassSDTau32_jetP_dRapLo_inclusive "<<h_mistag_vs_jetP_TagMassSDTau32_jetP_dRapLo_inclusive ->Integral() <<endl;
  // cout<<"h_mistag_vs_jetP_TagMassSDTau32_jetP_dRapIn_0btag     "<<h_mistag_vs_jetP_TagMassSDTau32_jetP_dRapIn_0btag     ->Integral() <<endl;
  // cout<<"h_mistag_vs_jetP_TagMassSDTau32_jetP_dRapIn_1btag     "<<h_mistag_vs_jetP_TagMassSDTau32_jetP_dRapIn_1btag     ->Integral() <<endl;
  // cout<<"h_mistag_vs_jetP_TagMassSDTau32_jetP_dRapIn_2btag     "<<h_mistag_vs_jetP_TagMassSDTau32_jetP_dRapIn_2btag     ->Integral() <<endl;
  // cout<<"h_mistag_vs_jetP_TagMassSDTau32_jetP_dRapIn_inclusive "<<h_mistag_vs_jetP_TagMassSDTau32_jetP_dRapIn_inclusive ->Integral() <<endl;




  // 888b     d888               888 888b     d888                                                  888                      
  // 8888b   d8888               888 8888b   d8888                                                  888                      
  // 88888b.d88888               888 88888b.d88888                                                  888                      
  // 888Y88888P888  .d88b.   .d88888 888Y88888P888  8888b.  .d8888b  .d8888b      .d8888b   .d88b.  888888 888  888 88888b.  
  // 888 Y888P 888 d88""88b d88" 888 888 Y888P 888     "88b 88K      88K          88K      d8P  Y8b 888    888  888 888 "88b 
  // 888  Y8P  888 888  888 888  888 888  Y8P  888 .d888888 "Y8888b. "Y8888b.     "Y8888b. 88888888 888    888  888 888  888 
  // 888   "   888 Y88..88P Y88b 888 888   "   888 888  888      X88      X88          X88 Y8b.     Y88b.  Y88b 888 888 d88P 
  // 888       888  "Y88P"   "Y88888 888       888 "Y888888  88888P'  88888P'      88888P'  "Y8888   "Y888  "Y88888 88888P"  
  //                                                                                                                888      
  //                                                                                                                888      
  //                                                                                                                888      


  // If running on QCD MC, make modMass
  TH1F *  h_mAK8_ModMass                = new TH1F("h_mAK8_ModMass",                 "", 200, 110, 210);
  TH1F *  h_mAK8_ModMass_jet0           = new TH1F("h_mAK8_ModMass_jet0",            "", 200, 110, 210);
  TH1F *  h_mAK8_ModMass_jet1           = new TH1F("h_mAK8_ModMass_jet1",            "", 200, 110, 210);
  TH1F *  h_mSDropAK8_ModMass           = new TH1F("h_mSDropAK8_ModMass",            "", 200, 110, 210);
  TH1F *  h_mSDropAK8_ModMass_jet0      = new TH1F("h_mSDropAK8_ModMass_jet0",       "", 200, 110, 210);
  TH1F *  h_mSDropAK8_ModMass_jet1      = new TH1F("h_mSDropAK8_ModMass_jet1",       "", 200, 110, 210);
  TH1F *  h_mPuppiSDropAK8_ModMass      = new TH1F("h_mPuppiSDropAK8_ModMass",       "", 200, 110, 210);
  TH1F *  h_mPuppiSDropAK8_ModMass_jet0 = new TH1F("h_mPuppiSDropAK8_ModMass_jet0",  "", 200, 110, 210);
  TH1F *  h_mPuppiSDropAK8_ModMass_jet1 = new TH1F("h_mPuppiSDropAK8_ModMass_jet1",  "", 200, 110, 210);
  
  TH1F *  h_mSDropAK8_AltTag_ModMass           = new TH1F("h_mSDropAK8_AltTag_ModMass",            "", 210, 90, 300);
  TH1F *  h_mSDropAK8_AltTag_ModMass_jet0      = new TH1F("h_mSDropAK8_AltTag_ModMass_jet0",       "", 210, 90, 300);
  TH1F *  h_mSDropAK8_AltTag_ModMass_jet1      = new TH1F("h_mSDropAK8_AltTag_ModMass_jet1",       "", 210, 90, 300);

  // input MODMASS histograms from file
  cout<<"get modmass histograms"<<endl;
  TFile * FmodMass = new TFile(modmassFile.c_str());
  TH1F * h_modMass_Fat            = (TH1F *) FmodMass->Get( "h_mAK8_ModMass"           );
  TH1F * h_modMass_SD             = (TH1F *) FmodMass->Get( "h_mSDropAK8_ModMass"      );
  TH1F * h_modMass_Fat_jet0       = (TH1F *) FmodMass->Get( "h_mAK8_ModMass_jet0"      );
  TH1F * h_modMass_SD_jet0        = (TH1F *) FmodMass->Get( "h_mSDropAK8_ModMass_jet0" );
  TH1F * h_modMass_Fat_jet1       = (TH1F *) FmodMass->Get( "h_mAK8_ModMass_jet1"      );
  TH1F * h_modMass_SD_jet1        = (TH1F *) FmodMass->Get( "h_mSDropAK8_ModMass_jet1" );

  h_modMass_Fat      ->SetName("h_modMass_Fat");
  h_modMass_SD       ->SetName("h_modMass_SD");
  h_modMass_Fat_jet0 ->SetName("h_modMass_Fat_jet0");
  h_modMass_SD_jet0  ->SetName("h_modMass_SD_jet0");
  h_modMass_Fat_jet1 ->SetName("h_modMass_Fat_jet1");
  h_modMass_SD_jet1  ->SetName("h_modMass_SD_jet1");

  if (run_bkgdest){
    cout << "h_modMass_Fat      integral  " << h_modMass_Fat     ->Integral() << endl;
    cout << "h_modMass_SD       integral  " << h_modMass_SD      ->Integral() << endl;
    cout << "h_modMass_Fat_jet0 integral  " << h_modMass_Fat_jet0->Integral() << endl;
    cout << "h_modMass_SD_jet0  integral  " << h_modMass_SD_jet0 ->Integral() << endl;
    cout << "h_modMass_Fat_jet1 integral  " << h_modMass_Fat_jet1->Integral() << endl;
    cout << "h_modMass_SD_jet1  integral  " << h_modMass_SD_jet1 ->Integral() << endl;
  }

  // 888    888 d8b          888                                                              
  // 888    888 Y8P          888                                                              
  // 888    888              888                                                              
  // 8888888888 888 .d8888b  888888  .d88b.   .d88b.  888d888  8888b.  88888b.d88b.  .d8888b  
  // 888    888 888 88K      888    d88""88b d88P"88b 888P"       "88b 888 "888 "88b 88K      
  // 888    888 888 "Y8888b. 888    888  888 888  888 888     .d888888 888  888  888 "Y8888b. 
  // 888    888 888      X88 Y88b.  Y88..88P Y88b 888 888     888  888 888  888  888      X88 
  // 888    888 888  88888P'  "Y888  "Y88P"   "Y88888 888     "Y888888 888  888  888  88888P' 
  //                                              888                                         
  //                                         Y8b d88P                                         
  //                                          "Y88P"                                          
  
  cout<<"make new histograms"<<endl;

  TH1D *  h_CutFlow                                       = new TH1D("h_CutFlow"              , "", 20, 0, 20); 
  TH1D *  h_EventWeight                                   = new TH1D("h_EventWeight"          , "", 500, -100, 200);
  TH1D *  h_BtagCategoriesPreSF                           = new TH1D("h_BtagCategoriesPreSF"  , "", 3, 0, 3);
  TH1D *  h_BtagCategoriesPostSF                          = new TH1D("h_BtagCategoriesPostSF" , "", 3, 0, 3);

  // anti-tag and probe
  TH1D * h_AntiTagCHS_Probe_jetP_dRapIn_inclusive                           = new TH1D( "h_AntiTagCHS_Probe_jetP_dRapIn_inclusive"                       , "", 1400, 0, 7000 );
  TH1D * h_AntiTagCHS_Probe_jetP_dRapIn_0btag                               = new TH1D( "h_AntiTagCHS_Probe_jetP_dRapIn_0btag"                           , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagCHS_Probe_jetP_dRapIn_1btag                               = new TH1D( "h_AntiTagCHS_Probe_jetP_dRapIn_1btag"                           , "", 1400, 0, 7000 ); 
  TH1D * h_AntiTagCHS_Probe_jetP_dRapIn_2btag                               = new TH1D( "h_AntiTagCHS_Probe_jetP_dRapIn_2btag"                           , "", 1400, 0, 7000 ); 
  TH1D * h_AntiTagCHS_Probe_jetP_dRapHi_inclusive                           = new TH1D( "h_AntiTagCHS_Probe_jetP_dRapHi_inclusive"                       , "", 1400, 0, 7000 );
  TH1D * h_AntiTagCHS_Probe_jetP_dRapHi_0btag                               = new TH1D( "h_AntiTagCHS_Probe_jetP_dRapHi_0btag"                           , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagCHS_Probe_jetP_dRapHi_1btag                               = new TH1D( "h_AntiTagCHS_Probe_jetP_dRapHi_1btag"                           , "", 1400, 0, 7000 ); 
  TH1D * h_AntiTagCHS_Probe_jetP_dRapHi_2btag                               = new TH1D( "h_AntiTagCHS_Probe_jetP_dRapHi_2btag"                           , "", 1400, 0, 7000 ); 
  TH1D * h_AntiTagCHS_Probe_jetP_dRapLo_inclusive                           = new TH1D( "h_AntiTagCHS_Probe_jetP_dRapLo_inclusive"                       , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagCHS_Probe_jetP_dRapLo_0btag                               = new TH1D( "h_AntiTagCHS_Probe_jetP_dRapLo_0btag"                           , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagCHS_Probe_jetP_dRapLo_1btag                               = new TH1D( "h_AntiTagCHS_Probe_jetP_dRapLo_1btag"                           , "", 1400, 0, 7000 );   
  TH1D * h_AntiTagCHS_Probe_jetP_dRapLo_2btag                               = new TH1D( "h_AntiTagCHS_Probe_jetP_dRapLo_2btag"                           , "", 1400, 0, 7000 );
  TH1D * h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclusive                  = new TH1D( "h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclusive"              , "", 1400, 0, 7000 );
  TH1D * h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag                      = new TH1D( "h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag"                  , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag                      = new TH1D( "h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag"                  , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag                      = new TH1D( "h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag"                  , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclusive                  = new TH1D( "h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclusive"              , "", 1400, 0, 7000 );
  TH1D * h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag                      = new TH1D( "h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag"                  , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag                      = new TH1D( "h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag"                  , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag                      = new TH1D( "h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag"                  , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclusive                  = new TH1D( "h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclusive"              , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag                      = new TH1D( "h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag"                  , "", 1400, 0, 7000 );     
  TH1D * h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag                      = new TH1D( "h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag"                  , "", 1400, 0, 7000 );     
  TH1D * h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag                      = new TH1D( "h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag"                  , "", 1400, 0, 7000 );  

  TH1D * h_AntiTagPuppi_Probe_jetP_dRapIn_inclusive                         = new TH1D( "h_AntiTagPuppi_Probe_jetP_dRapIn_inclusive"                       , "", 1400, 0, 7000 );
  TH1D * h_AntiTagPuppi_Probe_jetP_dRapIn_0btag                             = new TH1D( "h_AntiTagPuppi_Probe_jetP_dRapIn_0btag"                           , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagPuppi_Probe_jetP_dRapIn_1btag                             = new TH1D( "h_AntiTagPuppi_Probe_jetP_dRapIn_1btag"                           , "", 1400, 0, 7000 ); 
  TH1D * h_AntiTagPuppi_Probe_jetP_dRapIn_2btag                             = new TH1D( "h_AntiTagPuppi_Probe_jetP_dRapIn_2btag"                           , "", 1400, 0, 7000 ); 
  TH1D * h_AntiTagPuppi_Probe_jetP_dRapHi_inclusive                         = new TH1D( "h_AntiTagPuppi_Probe_jetP_dRapHi_inclusive"                       , "", 1400, 0, 7000 );
  TH1D * h_AntiTagPuppi_Probe_jetP_dRapHi_0btag                             = new TH1D( "h_AntiTagPuppi_Probe_jetP_dRapHi_0btag"                           , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagPuppi_Probe_jetP_dRapHi_1btag                             = new TH1D( "h_AntiTagPuppi_Probe_jetP_dRapHi_1btag"                           , "", 1400, 0, 7000 ); 
  TH1D * h_AntiTagPuppi_Probe_jetP_dRapHi_2btag                             = new TH1D( "h_AntiTagPuppi_Probe_jetP_dRapHi_2btag"                           , "", 1400, 0, 7000 ); 
  TH1D * h_AntiTagPuppi_Probe_jetP_dRapLo_inclusive                         = new TH1D( "h_AntiTagPuppi_Probe_jetP_dRapLo_inclusive"                       , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagPuppi_Probe_jetP_dRapLo_0btag                             = new TH1D( "h_AntiTagPuppi_Probe_jetP_dRapLo_0btag"                           , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagPuppi_Probe_jetP_dRapLo_1btag                             = new TH1D( "h_AntiTagPuppi_Probe_jetP_dRapLo_1btag"                           , "", 1400, 0, 7000 );   
  TH1D * h_AntiTagPuppi_Probe_jetP_dRapLo_2btag                             = new TH1D( "h_AntiTagPuppi_Probe_jetP_dRapLo_2btag"                           , "", 1400, 0, 7000 );
  TH1D * h_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_inclusive                = new TH1D( "h_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_inclusive"              , "", 1400, 0, 7000 );
  TH1D * h_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_0btag                    = new TH1D( "h_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_0btag"                  , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_1btag                    = new TH1D( "h_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_1btag"                  , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_2btag                    = new TH1D( "h_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_2btag"                  , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_inclusive                = new TH1D( "h_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_inclusive"              , "", 1400, 0, 7000 );
  TH1D * h_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_0btag                    = new TH1D( "h_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_0btag"                  , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_1btag                    = new TH1D( "h_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_1btag"                  , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_2btag                    = new TH1D( "h_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_2btag"                  , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_inclusive                = new TH1D( "h_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_inclusive"              , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_0btag                    = new TH1D( "h_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_0btag"                  , "", 1400, 0, 7000 );     
  TH1D * h_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_1btag                    = new TH1D( "h_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_1btag"                  , "", 1400, 0, 7000 );     
  TH1D * h_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_2btag                    = new TH1D( "h_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_2btag"                  , "", 1400, 0, 7000 );  

  TH1D * h_alt_AntiTagCHS_Probe_jetP_dRapIn_inclusive                       = new TH1D( "h_alt_AntiTagCHS_Probe_jetP_dRapIn_inclusive"                    , "", 1400, 0, 7000 );
  TH1D * h_alt_AntiTagCHS_Probe_jetP_dRapIn_0btag                           = new TH1D( "h_alt_AntiTagCHS_Probe_jetP_dRapIn_0btag"                        , "", 1400, 0, 7000 );  
  TH1D * h_alt_AntiTagCHS_Probe_jetP_dRapIn_1btag                           = new TH1D( "h_alt_AntiTagCHS_Probe_jetP_dRapIn_1btag"                        , "", 1400, 0, 7000 ); 
  TH1D * h_alt_AntiTagCHS_Probe_jetP_dRapIn_2btag                           = new TH1D( "h_alt_AntiTagCHS_Probe_jetP_dRapIn_2btag"                        , "", 1400, 0, 7000 ); 
  TH1D * h_alt_AntiTagCHS_Probe_jetP_dRapHi_inclusive                       = new TH1D( "h_alt_AntiTagCHS_Probe_jetP_dRapHi_inclusive"                    , "", 1400, 0, 7000 );
  TH1D * h_alt_AntiTagCHS_Probe_jetP_dRapHi_0btag                           = new TH1D( "h_alt_AntiTagCHS_Probe_jetP_dRapHi_0btag"                        , "", 1400, 0, 7000 );  
  TH1D * h_alt_AntiTagCHS_Probe_jetP_dRapHi_1btag                           = new TH1D( "h_alt_AntiTagCHS_Probe_jetP_dRapHi_1btag"                        , "", 1400, 0, 7000 ); 
  TH1D * h_alt_AntiTagCHS_Probe_jetP_dRapHi_2btag                           = new TH1D( "h_alt_AntiTagCHS_Probe_jetP_dRapHi_2btag"                        , "", 1400, 0, 7000 ); 
  TH1D * h_alt_AntiTagCHS_Probe_jetP_dRapLo_inclusive                       = new TH1D( "h_alt_AntiTagCHS_Probe_jetP_dRapLo_inclusive"                    , "", 1400, 0, 7000 );  
  TH1D * h_alt_AntiTagCHS_Probe_jetP_dRapLo_0btag                           = new TH1D( "h_alt_AntiTagCHS_Probe_jetP_dRapLo_0btag"                        , "", 1400, 0, 7000 );  
  TH1D * h_alt_AntiTagCHS_Probe_jetP_dRapLo_1btag                           = new TH1D( "h_alt_AntiTagCHS_Probe_jetP_dRapLo_1btag"                        , "", 1400, 0, 7000 );   
  TH1D * h_alt_AntiTagCHS_Probe_jetP_dRapLo_2btag                           = new TH1D( "h_alt_AntiTagCHS_Probe_jetP_dRapLo_2btag"                        , "", 1400, 0, 7000 );
  TH1D * h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclusive              = new TH1D( "h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclusive"           , "", 1400, 0, 7000 );
  TH1D * h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag                  = new TH1D( "h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag"               , "", 1400, 0, 7000 );  
  TH1D * h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag                  = new TH1D( "h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag"               , "", 1400, 0, 7000 );  
  TH1D * h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag                  = new TH1D( "h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag"               , "", 1400, 0, 7000 );  
  TH1D * h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclusive              = new TH1D( "h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclusive"           , "", 1400, 0, 7000 );
  TH1D * h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag                  = new TH1D( "h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag"               , "", 1400, 0, 7000 );  
  TH1D * h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag                  = new TH1D( "h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag"               , "", 1400, 0, 7000 );  
  TH1D * h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag                  = new TH1D( "h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag"               , "", 1400, 0, 7000 );  
  TH1D * h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclusive              = new TH1D( "h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclusive"           , "", 1400, 0, 7000 );  
  TH1D * h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag                  = new TH1D( "h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag"               , "", 1400, 0, 7000 );     
  TH1D * h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag                  = new TH1D( "h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag"               , "", 1400, 0, 7000 );     
  TH1D * h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag                  = new TH1D( "h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag"               , "", 1400, 0, 7000 );  


  TH1D *   h_AntiTagCHS40to60_Probe_jetP_dRapIn_inclusive                   = new TH1D(   "h_AntiTagCHS40to60_Probe_jetP_dRapIn_inclusive"                 , "", 1400, 0, 7000);
  TH1D *   h_AntiTagCHS60to80_Probe_jetP_dRapIn_inclusive                   = new TH1D(   "h_AntiTagCHS60to80_Probe_jetP_dRapIn_inclusive"                 , "", 1400, 0, 7000);
  TH1D *  h_AntiTagCHS80to110_Probe_jetP_dRapIn_inclusive                   = new TH1D(  "h_AntiTagCHS80to110_Probe_jetP_dRapIn_inclusive"                 , "", 1400, 0, 7000); 
  TH1D * h_AntiTagCHS100to120_Probe_jetP_dRapIn_inclusive                   = new TH1D( "h_AntiTagCHS100to120_Probe_jetP_dRapIn_inclusive"                 , "", 1400, 0, 7000);  
  TH1D * h_AntiTagCHS120to140_Probe_jetP_dRapIn_inclusive                   = new TH1D( "h_AntiTagCHS120to140_Probe_jetP_dRapIn_inclusive"                 , "", 1400, 0, 7000);  
  TH1D * h_AntiTagCHS140to180_Probe_jetP_dRapIn_inclusive                   = new TH1D( "h_AntiTagCHS140to180_Probe_jetP_dRapIn_inclusive"                 , "", 1400, 0, 7000);  
  TH1D * h_AntiTagCHS180to220_Probe_jetP_dRapIn_inclusive                   = new TH1D( "h_AntiTagCHS180to220_Probe_jetP_dRapIn_inclusive"                 , "", 1400, 0, 7000);  
  TH1D * h_AntiTagCHS220to300_Probe_jetP_dRapIn_inclusive                   = new TH1D( "h_AntiTagCHS220to300_Probe_jetP_dRapIn_inclusive"                 , "", 1400, 0, 7000);  

  TH1D *   h_AntiTagCHS40to60_TagMassSDTau32_jetP_dRapIn_inclusive          = new TH1D(   "h_AntiTagCHS40to60_TagMassSDTau32_jetP_dRapIn_inclusive"        , "", 1400, 0, 7000);
  TH1D *   h_AntiTagCHS60to80_TagMassSDTau32_jetP_dRapIn_inclusive          = new TH1D(   "h_AntiTagCHS60to80_TagMassSDTau32_jetP_dRapIn_inclusive"        , "", 1400, 0, 7000);
  TH1D *  h_AntiTagCHS80to110_TagMassSDTau32_jetP_dRapIn_inclusive          = new TH1D(  "h_AntiTagCHS80to110_TagMassSDTau32_jetP_dRapIn_inclusive"        , "", 1400, 0, 7000); 
  TH1D * h_AntiTagCHS100to120_TagMassSDTau32_jetP_dRapIn_inclusive          = new TH1D( "h_AntiTagCHS100to120_TagMassSDTau32_jetP_dRapIn_inclusive"        , "", 1400, 0, 7000);  
  TH1D * h_AntiTagCHS120to140_TagMassSDTau32_jetP_dRapIn_inclusive          = new TH1D( "h_AntiTagCHS120to140_TagMassSDTau32_jetP_dRapIn_inclusive"        , "", 1400, 0, 7000);  
  TH1D * h_AntiTagCHS140to180_TagMassSDTau32_jetP_dRapIn_inclusive          = new TH1D( "h_AntiTagCHS140to180_TagMassSDTau32_jetP_dRapIn_inclusive"        , "", 1400, 0, 7000);  
  TH1D * h_AntiTagCHS180to220_TagMassSDTau32_jetP_dRapIn_inclusive          = new TH1D( "h_AntiTagCHS180to220_TagMassSDTau32_jetP_dRapIn_inclusive"        , "", 1400, 0, 7000);  
  TH1D * h_AntiTagCHS220to300_TagMassSDTau32_jetP_dRapIn_inclusive          = new TH1D( "h_AntiTagCHS220to300_TagMassSDTau32_jetP_dRapIn_inclusive"        , "", 1400, 0, 7000);  
      

  // --- Kinematic plots

  // event                        
  TH1D *  h_DijetMass_dRapIn                              = new TH1D( "h_DijetMass_dRapIn"                            , "",   400,      0,     8000  ); 
  TH1D *  h_DijetMass_dRapLo                              = new TH1D( "h_DijetMass_dRapLo"                            , "",   400,      0,     8000  ); 
  TH1D *  h_DijetMass_dRapHi                              = new TH1D( "h_DijetMass_dRapHi"                            , "",   400,      0,     8000  ); 
  TH1D *  h_DeltaRap                                      = new TH1D( "h_DeltaRap"                                    , "",   400,      0,        6  ); 
  TH1D *  h_DeltaPhi                                      = new TH1D( "h_DeltaPhi"                                    , "",   400,      0,      3.2  ); 
  TH1D *  h_HT                                            = new TH1D( "h_HT"                                          , "",   400,      0,     8000  ); 
  TH1D *  h_MET                                           = new TH1D( "h_MET"                                         , "",   400,      0,     2000  ); 
  TH1D *  h_METphi                                        = new TH1D( "h_METphi"                                      , "",   400,   -3.2,     3.2   ); 
  TH1D *  h_Nvtx                                          = new TH1D( "h_Nvtx"                                        , "",   100,      0,      100  ); 
 
  // Jet0
  TH1D *  h_Jet0P                                         = new TH1D( "h_Jet0P"                                       , "",   700,      0,     7000  ); 
  TH1D *  h_Jet0Pt                                        = new TH1D( "h_Jet0Pt"                                      , "",   500,      0,     5000  ); 
  TH1D *  h_Jet0Phi                                       = new TH1D( "h_Jet0Phi"                                     , "",   400,   -3.2,      3.2  ); 
  TH1D *  h_Jet0Rap                                       = new TH1D( "h_Jet0Rap"                                     , "",   400,     -3,        3  ); 
  TH1D *  h_Jet0sdmass                                    = new TH1D( "h_Jet0sdmass"                                  , "",   400,      0,      400  ); 
  TH1D *  h_Jet0Tau1                                      = new TH1D( "h_Jet0Tau1"                                    , "",   400,      0,        1  ); 
  TH1D *  h_Jet0Tau2                                      = new TH1D( "h_Jet0Tau2"                                    , "",   400,      0,        1  ); 
  TH1D *  h_Jet0Tau3                                      = new TH1D( "h_Jet0Tau3"                                    , "",   400,      0,        1  ); 
  TH1D *  h_Jet0Tau4                                      = new TH1D( "h_Jet0Tau4"                                    , "",   400,      0,        1  ); 
  TH1D *  h_Jet0SDmaxbdisc                                = new TH1D( "h_Jet0SDmaxbdisc"                              , "",   400,      0,        1  ); 
  TH1D *  h_Jet0SDsubjet0pt                               = new TH1D( "h_Jet0SDsubjet0pt"                             , "",   400,      0,     2000  ); 
  TH1D *  h_Jet0SDsubjet0mass                             = new TH1D( "h_Jet0SDsubjet0mass"                           , "",   400,      0,      300  ); 
  TH1D *  h_Jet0SDsubjet0tau1                             = new TH1D( "h_Jet0SDsubjet0tau1"                           , "",   400,      0,        1  ); 
  TH1D *  h_Jet0SDsubjet0tau2                             = new TH1D( "h_Jet0SDsubjet0tau2"                           , "",   400,      0,        1  ); 
  TH1D *  h_Jet0SDsubjet0tau3                             = new TH1D( "h_Jet0SDsubjet0tau3"                           , "",   400,      0,        1  ); 
  TH1D *  h_Jet0SDsubjet0bdisc                            = new TH1D( "h_Jet0SDsubjet0bdisc"                          , "",   400,      0,        1  ); 
  TH1D *  h_Jet0SDsubjet1pt                               = new TH1D( "h_Jet0SDsubjet1pt"                             , "",   400,      0,     2000  ); 
  TH1D *  h_Jet0SDsubjet1mass                             = new TH1D( "h_Jet0SDsubjet1mass"                           , "",   400,      0,      300  ); 
  TH1D *  h_Jet0SDsubjet1tau1                             = new TH1D( "h_Jet0SDsubjet1tau1"                           , "",   400,      0,        1  ); 
  TH1D *  h_Jet0SDsubjet1tau2                             = new TH1D( "h_Jet0SDsubjet1tau2"                           , "",   400,      0,        1  ); 
  TH1D *  h_Jet0SDsubjet1tau3                             = new TH1D( "h_Jet0SDsubjet1tau3"                           , "",   400,      0,        1  ); 
  TH1D *  h_Jet0SDsubjet1bdisc                            = new TH1D( "h_Jet0SDsubjet1bdisc"                          , "",   400,      0,        1  ); 
  TH1D *  h_Jet0PuppiPt                                   = new TH1D( "h_Jet0PuppiPt"                                 , "",   400,      0,     4000  ); 
  TH1D *  h_Jet0PuppiMass                                 = new TH1D( "h_Jet0PuppiMass"                               , "",   400,      0,      300  ); 
  TH1D *  h_Jet0PuppiSDpt                                 = new TH1D( "h_Jet0PuppiSDpt"                               , "",   400,      0,     4000  ); 
  TH1D *  h_Jet0PuppiTau1                                 = new TH1D( "h_Jet0PuppiTau1"                               , "",   400,      0,        1  ); 
  TH1D *  h_Jet0PuppiTau2                                 = new TH1D( "h_Jet0PuppiTau2"                               , "",   400,      0,        1  ); 
  TH1D *  h_Jet0PuppiTau3                                 = new TH1D( "h_Jet0PuppiTau3"                               , "",   400,      0,        1  ); 
  TH1D *  h_Jet0PuppiTau4                                 = new TH1D( "h_Jet0PuppiTau4"                               , "",   400,      0,        1  ); 
  TH1D *  h_Jet0PuppiSDmaxbdisc                           = new TH1D( "h_Jet0PuppiSDmaxbdisc"                         , "",   400,      0,        1  ); 
  TH1D *  h_Jet0PuppiSDsubjet0pt                          = new TH1D( "h_Jet0PuppiSDsubjet0pt"                        , "",   400,      0,     2000  ); 
  TH1D *  h_Jet0PuppiSDsubjet0mass                        = new TH1D( "h_Jet0PuppiSDsubjet0mass"                      , "",   400,      0,      300  ); 
  TH1D *  h_Jet0PuppiSDsubjet0tau1                        = new TH1D( "h_Jet0PuppiSDsubjet0tau1"                      , "",   400,      0,        1  ); 
  TH1D *  h_Jet0PuppiSDsubjet0tau2                        = new TH1D( "h_Jet0PuppiSDsubjet0tau2"                      , "",   400,      0,        1  ); 
  TH1D *  h_Jet0PuppiSDsubjet0tau3                        = new TH1D( "h_Jet0PuppiSDsubjet0tau3"                      , "",   400,      0,        1  ); 
  TH1D *  h_Jet0PuppiSDsubjet0bdisc                       = new TH1D( "h_Jet0PuppiSDsubjet0bdisc"                     , "",   400,      0,        1  ); 
  TH1D *  h_Jet0PuppiSDsubjet1pt                          = new TH1D( "h_Jet0PuppiSDsubjet1pt"                        , "",   400,      0,     2000  ); 
  TH1D *  h_Jet0PuppiSDsubjet1mass                        = new TH1D( "h_Jet0PuppiSDsubjet1mass"                      , "",   400,      0,      300  ); 
  TH1D *  h_Jet0PuppiSDsubjet1tau1                        = new TH1D( "h_Jet0PuppiSDsubjet1tau1"                      , "",   400,      0,        1  ); 
  TH1D *  h_Jet0PuppiSDsubjet1tau2                        = new TH1D( "h_Jet0PuppiSDsubjet1tau2"                      , "",   400,      0,        1  ); 
  TH1D *  h_Jet0PuppiSDsubjet1tau3                        = new TH1D( "h_Jet0PuppiSDsubjet1tau3"                      , "",   400,      0,        1  ); 
  TH1D *  h_Jet0PuppiSDsubjet1bdisc                       = new TH1D( "h_Jet0PuppiSDsubjet1bdisc"                     , "",   400,      0,        1  ); 
  TH1D *  h_Jet0CHF                                       = new TH1D( "h_Jet0CHF"                                     , "",   400,      0,        1  ); 
  TH1D *  h_Jet0NHF                                       = new TH1D( "h_Jet0NHF"                                     , "",   400,      0,        1  ); 
  TH1D *  h_Jet0CM                                        = new TH1D( "h_Jet0CM"                                      , "",   200,      0,      200  ); 
  TH1D *  h_Jet0NM                                        = new TH1D( "h_Jet0NM"                                      , "",   200,      0,      200  ); 
  TH1D *  h_Jet0NEF                                       = new TH1D( "h_Jet0NEF"                                     , "",   400,      0,        1  ); 
  TH1D *  h_Jet0CEF                                       = new TH1D( "h_Jet0CEF"                                     , "",   400,      0,        1  ); 
  TH1D *  h_Jet0MF                                        = new TH1D( "h_Jet0MF"                                      , "",    10,      0,       10  ); 
  TH1D *  h_Jet0Mult                                      = new TH1D( "h_Jet0Mult"                                    , "",   200,      0,      200  ); 
  TH1D *  h_Jet0PuppiCHF                                  = new TH1D( "h_Jet0PuppiCHF"                                , "",   400,      0,        1  ); 
  TH1D *  h_Jet0PuppiNHF                                  = new TH1D( "h_Jet0PuppiNHF"                                , "",   400,      0,        1  ); 
  TH1D *  h_Jet0PuppiCM                                   = new TH1D( "h_Jet0PuppiCM"                                 , "",   200,      0,      200  ); 
  TH1D *  h_Jet0PuppiNM                                   = new TH1D( "h_Jet0PuppiNM"                                 , "",   200,      0,      200  ); 
  TH1D *  h_Jet0PuppiNEF                                  = new TH1D( "h_Jet0PuppiNEF"                                , "",   400,      0,        1  ); 
  TH1D *  h_Jet0PuppiCEF                                  = new TH1D( "h_Jet0PuppiCEF"                                , "",   400,      0,        1  ); 
  TH1D *  h_Jet0PuppiMF                                   = new TH1D( "h_Jet0PuppiMF"                                 , "",    10,      0,       10  ); 
  TH1D *  h_Jet0PuppiMult                                 = new TH1D( "h_Jet0PuppiMult"                               , "",   200,      0,      200  ); 
 

  TH1D *  h_Jet1Pt                                        = new TH1D( "h_Jet1Pt"                   ,"", 400, 0, 4000); 
  TH1D *  h_Jet1Rap                                        = new TH1D( "h_Jet1Rap"                  ,"", 400, -5, 5);



  // N-1 histograms
  TH1D *  h_Jet0SDmass                                    = new TH1D( "h_Jet0SDmass"                                   , "", 200, 0,  500); 
  TH1D *  h_Jet0SDmass_JetTag_b                           = new TH1D( "h_Jet0SDmass_JetTag_b"                          , "", 200, 0,  500); 
  TH1D *  h_Jet0SDmass_JetTag_tau32                       = new TH1D( "h_Jet0SDmass_JetTag_tau32"                      , "", 200, 0,  500); 
  TH1D *  h_Jet0SDmass_JetTag_b_tau32                     = new TH1D( "h_Jet0SDmass_JetTag_b_tau32"                    , "", 200, 0,  500); 
  TH1D *  h_Jet0SDmass_OppositeJetTag_t_b                 = new TH1D( "h_Jet0SDmass_OppositeJetTag_t_b"                , "", 200, 0,  500); 
  TH1D *  h_Jet0SDmass_OppositeJetTag_t_b_JetTag_b        = new TH1D( "h_Jet0SDmass_OppositeJetTag_t_b_JetTag_b"       , "", 200, 0,  500); 
  TH1D *  h_Jet0SDmass_OppositeJetTag_t_b_JetTag_b_tau32  = new TH1D( "h_Jet0SDmass_OppositeJetTag_t_b_JetTag_b_tau32" , "", 200, 0,  500); 

  TH1D *  h_Jet1SDmass                                    = new TH1D( "h_Jet1SDmass"                                   , "", 200, 0,  500);
  TH1D *  h_Jet1SDmass_JetTag_b                           = new TH1D( "h_Jet1SDmass_JetTag_b"                          , "", 200, 0,  500); 
  TH1D *  h_Jet1SDmass_JetTag_tau32                       = new TH1D( "h_Jet1SDmass_JetTag_tau32"                      , "", 200, 0,  500); 
  TH1D *  h_Jet1SDmass_JetTag_b_tau32                     = new TH1D( "h_Jet1SDmass_JetTag_b_tau32"                    , "", 200, 0,  500);  
  TH1D *  h_Jet1SDmass_OppositeJetTag_t_b                 = new TH1D( "h_Jet1SDmass_OppositeJetTag_t_b"                , "", 200, 0,  500); 
  TH1D *  h_Jet1SDmass_OppositeJetTag_t_b_JetTag_b        = new TH1D( "h_Jet1SDmass_OppositeJetTag_t_b_JetTag_b"       , "", 200, 0,  500); 
  TH1D *  h_Jet1SDmass_OppositeJetTag_t_b_JetTag_b_tau32  = new TH1D( "h_Jet1SDmass_OppositeJetTag_t_b_JetTag_b_tau32" , "", 200, 0,  500); 

  TH1D *  h_JetSDmass                                     = new TH1D( "h_JetSDmass"                                    , "", 200, 0,  500);
  TH1D *  h_JetSDmass_JetTag_b                            = new TH1D( "h_JetSDmass_JetTag_b"                           , "", 200, 0,  500); 
  TH1D *  h_JetSDmass_JetTag_tau32                        = new TH1D( "h_JetSDmass_JetTag_tau32"                       , "", 200, 0,  500); 
  TH1D *  h_JetSDmass_JetTag_b_tau32                      = new TH1D( "h_JetSDmass_JetTag_b_tau32"                     , "", 200, 0,  500);  
  TH1D *  h_JetSDmass_OppositeJetTag_t_b                  = new TH1D( "h_JetSDmass_OppositeJetTag_t_b"                 , "", 200, 0,  500); 
  TH1D *  h_JetSDmass_OppositeJetTag_t_b_JetTag_b         = new TH1D( "h_JetSDmass_OppositeJetTag_t_b_JetTag_b"        , "", 200, 0,  500); 
  TH1D *  h_JetSDmass_OppositeJetTag_t_b_JetTag_b_tau32   = new TH1D( "h_JetSDmass_OppositeJetTag_t_b_JetTag_b_tau32"  , "", 200, 0,  500); 

  TH1D *  h_Jet0Tau32                                     = new TH1D( "h_Jet0Tau32"                                    , "", 200, 0,    1); 
  TH1D *  h_Jet0Tau32_JetTag_b                            = new TH1D( "h_Jet0Tau32_JetTag_b"                           , "", 200, 0,    1); 
  TH1D *  h_Jet0Tau32_JetTag_mass                         = new TH1D( "h_Jet0Tau32_JetTag_mass"                        , "", 200, 0,    1); 
  TH1D *  h_Jet0Tau32_JetTag_b_mass                       = new TH1D( "h_Jet0Tau32_JetTag_b_mass"                      , "", 200, 0,    1); 
  TH1D *  h_Jet0Tau32_OppositeJetTag_t_b                  = new TH1D( "h_Jet0Tau32_OppositeJetTag_t_b"                 , "", 200, 0,    1); 
  TH1D *  h_Jet0Tau32_OppositeJetTag_t_b_JetTag_b         = new TH1D( "h_Jet0Tau32_OppositeJetTag_t_b_JetTag_b"        , "", 200, 0,    1); 
  TH1D *  h_Jet0Tau32_OppositeJetTag_t_b_JetTag_b_mass    = new TH1D( "h_Jet0Tau32_OppositeJetTag_t_b_JetTag_b_mass"   , "", 200, 0,    1); 

  TH1D *  h_Jet1Tau32                                     = new TH1D( "h_Jet1Tau32"                                    , "", 200, 0,    1); 
  TH1D *  h_Jet1Tau32_JetTag_b                            = new TH1D( "h_Jet1Tau32_JetTag_b"                           , "", 200, 0,    1); 
  TH1D *  h_Jet1Tau32_JetTag_mass                         = new TH1D( "h_Jet1Tau32_JetTag_mass"                        , "", 200, 0,    1); 
  TH1D *  h_Jet1Tau32_JetTag_b_mass                       = new TH1D( "h_Jet1Tau32_JetTag_b_mass"                      , "", 200, 0,    1); 
  TH1D *  h_Jet1Tau32_OppositeJetTag_t_b                  = new TH1D( "h_Jet1Tau32_OppositeJetTag_t_b"                 , "", 200, 0,    1); 
  TH1D *  h_Jet1Tau32_OppositeJetTag_t_b_JetTag_b         = new TH1D( "h_Jet1Tau32_OppositeJetTag_t_b_JetTag_b"        , "", 200, 0,    1); 
  TH1D *  h_Jet1Tau32_OppositeJetTag_t_b_JetTag_b_mass    = new TH1D( "h_Jet1Tau32_OppositeJetTag_t_b_JetTag_b_mass"   , "", 200, 0,    1); 

  TH1D *  h_JetTau32                                      = new TH1D( "h_JetTau32"                                     , "", 200, 0,    1); 
  TH1D *  h_JetTau32_JetTag_b                             = new TH1D( "h_JetTau32_JetTag_b"                            , "", 200, 0,    1); 
  TH1D *  h_JetTau32_JetTag_mass                          = new TH1D( "h_JetTau32_JetTag_mass"                         , "", 200, 0,    1); 
  TH1D *  h_JetTau32_JetTag_b_mass                        = new TH1D( "h_JetTau32_JetTag_b_mass"                       , "", 200, 0,    1); 
  TH1D *  h_JetTau32_OppositeJetTag_t_b                   = new TH1D( "h_JetTau32_OppositeJetTag_t_b"                  , "", 200, 0,    1); 
  TH1D *  h_JetTau32_OppositeJetTag_t_b_JetTag_b          = new TH1D( "h_JetTau32_OppositeJetTag_t_b_JetTag_b"         , "", 200, 0,    1); 
  TH1D *  h_JetTau32_OppositeJetTag_t_b_JetTag_b_mass     = new TH1D( "h_JetTau32_OppositeJetTag_t_b_JetTag_b_mass"    , "", 200, 0,    1); 





  // 2D
  TH2D *  h_Jet0Pt_Jet0Mass                     = new TH2D("h_Jet0Pt_Jet0Mass"                      , "", 200,  0, 4000,  400,   0,   600); 
  TH2D *  h_Jet0P_Jet0Mass                      = new TH2D("h_Jet0P_Jet0Mass"                       , "", 200,  0, 4000,  400,   0,   600); 
  TH2D *  h_Jet0Pt_Jet0SDmass                   = new TH2D("h_Jet0Pt_Jet0SDmass"                    , "", 200,  0, 4000,  400,   0,   600); 
  TH2D *  h_Jet0P_Jet0SDmass                    = new TH2D("h_Jet0P_Jet0SDmass"                     , "", 200,  0, 4000,  400,   0,   600); 

  TH2D *  h_Jet0Y_Jet0Mass                      = new TH2D("h_Jet0Y_Jet0Mass"                       , "", 200, -3,    3,  400,   0,   600); 
  TH2D *  h_Jet0Y_Jet0Mass_Pt500to520           = new TH2D("h_Jet0Y_Jet0Mass_Pt500to520"            , "", 200, -3,    3,  400,   0,   600); 
  
  TH2D *  h_Jet0Y_Jet0SDmass                    = new TH2D("h_Jet0Y_Jet0SDmass"                     , "", 200, -3,    3,  400,   0,   600); 
  TH2D *  h_Jet0Y_Jet0SDmass_Pt500to520         = new TH2D("h_Jet0Y_Jet0SDmass_Pt500to520"          , "", 200, -3,    3,  400,   0,   600); 
       
  TH2D *  h_Jet0Y_Jet1Y                         = new TH2D("h_Jet0Y_Jet1Y"                          , "", 200, -3,    3,  200,  -3,     3); 
  TH2D *  h_Jet0Y_Jet1Y_Pt500to520              = new TH2D("h_Jet0Y_Jet1Y_Pt500to520"               , "", 200, -3,    3,  200,  -3,     3); 

  TH2D * h_runNumber_DijetMass                   = new TH2D("h_runNumber_DijetMass"                 , "", 20000,270000, 290000,  800, 0,   8000); 
  TH2D * h_runNumber_HT                          = new TH2D("h_runNumber_HT"                        , "", 20000,270000, 290000,  800, 0,   8000); 
  TH2D * h_runNumber_Jet0CHF                     = new TH2D("h_runNumber_Jet0CHF"                   , "", 20000,270000, 290000,  400, 0,   1); 
  TH2D * h_runNumber_Jet0NHF                     = new TH2D("h_runNumber_Jet0NHF"                   , "", 20000,270000, 290000,  400, 0,   1); 
  TH2D * h_runNumber_Jet0CM                      = new TH2D("h_runNumber_Jet0CM"                    , "", 20000,270000, 290000,  300, 0, 300); 
  TH2D * h_runNumber_Jet0NM                      = new TH2D("h_runNumber_Jet0NM"                    , "", 20000,270000, 290000,  300, 0, 300); 
  TH2D * h_runNumber_Jet0NEF                     = new TH2D("h_runNumber_Jet0NEF"                   , "", 20000,270000, 290000,  400, 0,   1); 
  TH2D * h_runNumber_Jet0CEF                     = new TH2D("h_runNumber_Jet0CEF"                   , "", 20000,270000, 290000,  400, 0,   1); 
  TH2D * h_runNumber_Jet0MF                      = new TH2D("h_runNumber_Jet0MF"                    , "", 20000,270000, 290000,   10, 0,  10); 
  TH2D * h_runNumber_Jet0Mult                    = new TH2D("h_runNumber_Jet0Mult"                  , "", 20000,270000, 290000,  300, 0, 300); 
  TH2D * h_runNumber_NvtxGood                    = new TH2D("h_runNumber_NvtxGood"                  , "", 20000,270000, 290000,  100, 0, 100);
  TH2D * h_runNumber_Jet0Pt                      = new TH2D("h_runNumber_Jet0Pt"                    , "", 20000,270000, 290000,  200, 0, 1000);
  TH2D * h_runNumber_Jet0SDmass                  = new TH2D("h_runNumber_Jet0SDmass"                , "", 20000,270000, 290000,  200, 0, 500);




  // MC study
  TH1D * h_Jet0SDmass_matchedTop                          = new TH1D( "h_Jet0SDmass_matchedTop"                        , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_matchedTop_topDist                  = new TH1D( "h_Jet0SDmass_matchedTop_topDist"                , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_outside                             = new TH1D( "h_Jet0SDmass_outside"                           , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_bq                                  = new TH1D( "h_Jet0SDmass_bq"                                , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_qq                                  = new TH1D( "h_Jet0SDmass_qq"                                , "", 200, 0, 500); 
      
  TH1D * h_Jet0SDmass_all                                 = new TH1D( "h_Jet0SDmass_all"                               , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_in_b                                = new TH1D( "h_Jet0SDmass_in_b"                              , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_in_q                                = new TH1D( "h_Jet0SDmass_in_q"                              , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_in_qq                               = new TH1D( "h_Jet0SDmass_in_qq"                             , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_in_qb                               = new TH1D( "h_Jet0SDmass_in_qb"                             , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_in_qqb                              = new TH1D( "h_Jet0SDmass_in_qqb"                            , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_unmatched                           = new TH1D( "h_Jet0SDmass_unmatched"                         , "", 200, 0, 500); 

  TH1D * h_Jet0Tau32_all                                  = new TH1D( "h_Jet0Tau32_all"                                , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_in_b                                 = new TH1D( "h_Jet0Tau32_in_b"                               , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_in_q                                 = new TH1D( "h_Jet0Tau32_in_q"                               , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_in_qq                                = new TH1D( "h_Jet0Tau32_in_qq"                              , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_in_qb                                = new TH1D( "h_Jet0Tau32_in_qb"                              , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_in_qqb                               = new TH1D( "h_Jet0Tau32_in_qqb"                             , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_unmatched                            = new TH1D( "h_Jet0Tau32_unmatched"                          , "", 200, 0,   1); 

  TH1D * h_Jet0SDmass_Pt600_all                           = new TH1D( "h_Jet0SDmass_Pt600_all"                         , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_Pt600_in_b                          = new TH1D( "h_Jet0SDmass_Pt600_in_b"                        , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_Pt600_in_q                          = new TH1D( "h_Jet0SDmass_Pt600_in_q"                        , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_Pt600_in_qq                         = new TH1D( "h_Jet0SDmass_Pt600_in_qq"                       , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_Pt600_in_qb                         = new TH1D( "h_Jet0SDmass_Pt600_in_qb"                       , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_Pt600_in_qqb                        = new TH1D( "h_Jet0SDmass_Pt600_in_qqb"                      , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_Pt600_unmatched                     = new TH1D( "h_Jet0SDmass_Pt600_unmatched"                   , "", 200, 0, 500); 

  TH1D * h_Jet0Tau32_Pt600_all                            = new TH1D( "h_Jet0Tau32_Pt600_all"                          , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_Pt600_in_b                           = new TH1D( "h_Jet0Tau32_Pt600_in_b"                         , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_Pt600_in_q                           = new TH1D( "h_Jet0Tau32_Pt600_in_q"                         , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_Pt600_in_qq                          = new TH1D( "h_Jet0Tau32_Pt600_in_qq"                        , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_Pt600_in_qb                          = new TH1D( "h_Jet0Tau32_Pt600_in_qb"                        , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_Pt600_in_qqb                         = new TH1D( "h_Jet0Tau32_Pt600_in_qqb"                       , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_Pt600_unmatched                      = new TH1D( "h_Jet0Tau32_Pt600_unmatched"                    , "", 200, 0,   1); 

  TH1D * h_Jet0SDmass_BtagM_all                           = new TH1D( "h_Jet0SDmass_BtagM_all"                         , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagM_in_b                          = new TH1D( "h_Jet0SDmass_BtagM_in_b"                        , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagM_in_q                          = new TH1D( "h_Jet0SDmass_BtagM_in_q"                        , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagM_in_qq                         = new TH1D( "h_Jet0SDmass_BtagM_in_qq"                       , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagM_in_qb                         = new TH1D( "h_Jet0SDmass_BtagM_in_qb"                       , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagM_in_qqb                        = new TH1D( "h_Jet0SDmass_BtagM_in_qqb"                      , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagM_unmatched                     = new TH1D( "h_Jet0SDmass_BtagM_unmatched"                   , "", 200, 0, 500); 

  TH1D * h_Jet0SDmass_BtagT_all                           = new TH1D( "h_Jet0SDmass_BtagT_all"                         , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagT_in_b                          = new TH1D( "h_Jet0SDmass_BtagT_in_b"                        , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagT_in_q                          = new TH1D( "h_Jet0SDmass_BtagT_in_q"                        , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagT_in_qq                         = new TH1D( "h_Jet0SDmass_BtagT_in_qq"                       , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagT_in_qb                         = new TH1D( "h_Jet0SDmass_BtagT_in_qb"                       , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagT_in_qqb                        = new TH1D( "h_Jet0SDmass_BtagT_in_qqb"                      , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagT_unmatched                     = new TH1D( "h_Jet0SDmass_BtagT_unmatched"                   , "", 200, 0, 500); 

  TH1D * h_Jet0Tau32_BtagM_all                            = new TH1D( "h_Jet0Tau32_BtagM_all"                          , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_BtagM_in_b                           = new TH1D( "h_Jet0Tau32_BtagM_in_b"                         , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_BtagM_in_q                           = new TH1D( "h_Jet0Tau32_BtagM_in_q"                         , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_BtagM_in_qq                          = new TH1D( "h_Jet0Tau32_BtagM_in_qq"                        , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_BtagM_in_qb                          = new TH1D( "h_Jet0Tau32_BtagM_in_qb"                        , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_BtagM_in_qqb                         = new TH1D( "h_Jet0Tau32_BtagM_in_qqb"                       , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_BtagM_unmatched                      = new TH1D( "h_Jet0Tau32_BtagM_unmatched"                    , "", 200, 0,   1); 

  TH1D * h_Jet0Tau32_MassTag_all                          = new TH1D( "h_Jet0Tau32_MassTag_all"                       , "", 200, 0, 1); 
  TH1D * h_Jet0Tau32_MassTag_in_b                         = new TH1D( "h_Jet0Tau32_MassTag_in_b"                      , "", 200, 0, 1); 
  TH1D * h_Jet0Tau32_MassTag_in_q                         = new TH1D( "h_Jet0Tau32_MassTag_in_q"                      , "", 200, 0, 1); 
  TH1D * h_Jet0Tau32_MassTag_in_qq                        = new TH1D( "h_Jet0Tau32_MassTag_in_qq"                     , "", 200, 0, 1); 
  TH1D * h_Jet0Tau32_MassTag_in_qb                        = new TH1D( "h_Jet0Tau32_MassTag_in_qb"                     , "", 200, 0, 1); 
  TH1D * h_Jet0Tau32_MassTag_in_qqb                       = new TH1D( "h_Jet0Tau32_MassTag_in_qqb"                    , "", 200, 0, 1); 
  TH1D * h_Jet0Tau32_MassTag_unmatched                    = new TH1D( "h_Jet0Tau32_MassTag_unmatched"                 , "", 200, 0, 1); 

  TH1D * h_Jet0Tau32_BtagM_MassTag_all                    = new TH1D( "h_Jet0Tau32_BtagM_MassTag_all"                 , "", 200, 0, 1); 
  TH1D * h_Jet0Tau32_BtagM_MassTag_in_b                   = new TH1D( "h_Jet0Tau32_BtagM_MassTag_in_b"                , "", 200, 0, 1); 
  TH1D * h_Jet0Tau32_BtagM_MassTag_in_q                   = new TH1D( "h_Jet0Tau32_BtagM_MassTag_in_q"                , "", 200, 0, 1); 
  TH1D * h_Jet0Tau32_BtagM_MassTag_in_qq                  = new TH1D( "h_Jet0Tau32_BtagM_MassTag_in_qq"               , "", 200, 0, 1); 
  TH1D * h_Jet0Tau32_BtagM_MassTag_in_qb                  = new TH1D( "h_Jet0Tau32_BtagM_MassTag_in_qb"               , "", 200, 0, 1); 
  TH1D * h_Jet0Tau32_BtagM_MassTag_in_qqb                 = new TH1D( "h_Jet0Tau32_BtagM_MassTag_in_qqb"              , "", 200, 0, 1); 
  TH1D * h_Jet0Tau32_BtagM_MassTag_unmatched              = new TH1D( "h_Jet0Tau32_BtagM_MassTag_unmatched"           , "", 200, 0, 1); 

  TH1D * h_Jet0SDmass_TauTag_all                          = new TH1D( "h_Jet0SDmass_TauTag_all"                       , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_TauTag_in_b                         = new TH1D( "h_Jet0SDmass_TauTag_in_b"                      , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_TauTag_in_q                         = new TH1D( "h_Jet0SDmass_TauTag_in_q"                      , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_TauTag_in_qq                        = new TH1D( "h_Jet0SDmass_TauTag_in_qq"                     , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_TauTag_in_qb                        = new TH1D( "h_Jet0SDmass_TauTag_in_qb"                     , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_TauTag_in_qqb                       = new TH1D( "h_Jet0SDmass_TauTag_in_qqb"                    , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_TauTag_unmatched                    = new TH1D( "h_Jet0SDmass_TauTag_unmatched"                 , "", 200, 0, 500); 

  TH1D * h_Jet0SDmass_AntiTauTag_all                      = new TH1D( "h_Jet0SDmass_AntiTauTag_all"                   , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_AntiTauTag_in_b                     = new TH1D( "h_Jet0SDmass_AntiTauTag_in_b"                  , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_AntiTauTag_in_q                     = new TH1D( "h_Jet0SDmass_AntiTauTag_in_q"                  , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_AntiTauTag_in_qq                    = new TH1D( "h_Jet0SDmass_AntiTauTag_in_qq"                 , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_AntiTauTag_in_qb                    = new TH1D( "h_Jet0SDmass_AntiTauTag_in_qb"                 , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_AntiTauTag_in_qqb                   = new TH1D( "h_Jet0SDmass_AntiTauTag_in_qqb"                , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_AntiTauTag_unmatched                = new TH1D( "h_Jet0SDmass_AntiTauTag_unmatched"             , "", 200, 0, 500); 

  TH1D * h_Jet0SDmass_BtagM_TauTag_all                    = new TH1D( "h_Jet0SDmass_BtagM_TauTag_all"                 , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagM_TauTag_in_b                   = new TH1D( "h_Jet0SDmass_BtagM_TauTag_in_b"                , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagM_TauTag_in_q                   = new TH1D( "h_Jet0SDmass_BtagM_TauTag_in_q"                , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagM_TauTag_in_qq                  = new TH1D( "h_Jet0SDmass_BtagM_TauTag_in_qq"               , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagM_TauTag_in_qb                  = new TH1D( "h_Jet0SDmass_BtagM_TauTag_in_qb"               , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagM_TauTag_in_qqb                 = new TH1D( "h_Jet0SDmass_BtagM_TauTag_in_qqb"              , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagM_TauTag_unmatched              = new TH1D( "h_Jet0SDmass_BtagM_TauTag_unmatched"           , "", 200, 0, 500); 
         

  // double tagged
  TH1D *  h_2ttag_inclu_dRapIn_DijetMass      = new TH1D( "h_2ttag_inclu_dRapIn_DijetMass"    , "", 400, 0, 8000); 
  TH1D *  h_2ttag_0btag_dRapIn_DijetMass      = new TH1D( "h_2ttag_0btag_dRapIn_DijetMass"    , "", 400, 0, 8000); 
  TH1D *  h_2ttag_1btag_dRapIn_DijetMass      = new TH1D( "h_2ttag_1btag_dRapIn_DijetMass"    , "", 400, 0, 8000); 
  TH1D *  h_2ttag_2btag_dRapIn_DijetMass      = new TH1D( "h_2ttag_2btag_dRapIn_DijetMass"    , "", 400, 0, 8000); 

  TH1D *  h_2ttag_inclu_dRapLo_DijetMass      = new TH1D( "h_2ttag_inclu_dRapLo_DijetMass"    , "", 400, 0, 8000); 
  TH1D *  h_2ttag_0btag_dRapLo_DijetMass      = new TH1D( "h_2ttag_0btag_dRapLo_DijetMass"    , "", 400, 0, 8000); 
  TH1D *  h_2ttag_1btag_dRapLo_DijetMass      = new TH1D( "h_2ttag_1btag_dRapLo_DijetMass"    , "", 400, 0, 8000); 
  TH1D *  h_2ttag_2btag_dRapLo_DijetMass      = new TH1D( "h_2ttag_2btag_dRapLo_DijetMass"    , "", 400, 0, 8000); 

  TH1D *  h_2ttag_inclu_dRapHi_DijetMass      = new TH1D( "h_2ttag_inclu_dRapHi_DijetMass"    , "", 400, 0, 8000); 
  TH1D *  h_2ttag_0btag_dRapHi_DijetMass      = new TH1D( "h_2ttag_0btag_dRapHi_DijetMass"    , "", 400, 0, 8000); 
  TH1D *  h_2ttag_1btag_dRapHi_DijetMass      = new TH1D( "h_2ttag_1btag_dRapHi_DijetMass"    , "", 400, 0, 8000); 
  TH1D *  h_2ttag_2btag_dRapHi_DijetMass      = new TH1D( "h_2ttag_2btag_dRapHi_DijetMass"    , "", 400, 0, 8000); 

  TH1D *  h_2ttag_inclu_DeltaRap              = new TH1D( "h_2ttag_inclu_DeltaRap"            , "", 400, 0,    6); 
  TH1D *  h_2ttag_0btag_DeltaRap              = new TH1D( "h_2ttag_0btag_DeltaRap"            , "", 400, 0,    6); 
  TH1D *  h_2ttag_1btag_DeltaRap              = new TH1D( "h_2ttag_1btag_DeltaRap"            , "", 400, 0,    6); 
  TH1D *  h_2ttag_2btag_DeltaRap              = new TH1D( "h_2ttag_2btag_DeltaRap"            , "", 400, 0,    6); 

  TH1D *  h_2ttag_inclu_DeltaPhi              = new TH1D( "h_2ttag_inclu_DeltaPhi"            , "", 400, 0,  3.2); 
  TH1D *  h_2ttag_0btag_DeltaPhi              = new TH1D( "h_2ttag_0btag_DeltaPhi"            , "", 400, 0,  3.2); 
  TH1D *  h_2ttag_1btag_DeltaPhi              = new TH1D( "h_2ttag_1btag_DeltaPhi"            , "", 400, 0,  3.2); 
  TH1D *  h_2ttag_2btag_DeltaPhi              = new TH1D( "h_2ttag_2btag_DeltaPhi"            , "", 400, 0,  3.2); 

  TH1D *  h_2ttag_inclu_HT                    = new TH1D( "h_2ttag_inclu_HT"                  , "", 400, 0,  8000); 
  TH1D *  h_2ttag_0btag_HT                    = new TH1D( "h_2ttag_0btag_HT"                  , "", 400, 0,  8000); 
  TH1D *  h_2ttag_1btag_HT                    = new TH1D( "h_2ttag_1btag_HT"                  , "", 400, 0,  8000); 
  TH1D *  h_2ttag_2btag_HT                    = new TH1D( "h_2ttag_2btag_HT"                  , "", 400, 0,  8000); 

  TH1D *  h_2ttag_inclu_MET                   = new TH1D( "h_2ttag_inclu_MET"                 , "", 400, 0,  2000); 
  TH1D *  h_2ttag_0btag_MET                   = new TH1D( "h_2ttag_0btag_MET"                 , "", 400, 0,  2000); 
  TH1D *  h_2ttag_1btag_MET                   = new TH1D( "h_2ttag_1btag_MET"                 , "", 400, 0,  2000); 
  TH1D *  h_2ttag_2btag_MET                   = new TH1D( "h_2ttag_2btag_MET"                 , "", 400, 0,  2000); 
 
  TH1D *  h_2ttag_inclu_METphi                = new TH1D( "h_2ttag_inclu_METphi"              , "", 400, -3.2, 3.2 ); 
  TH1D *  h_2ttag_0btag_METphi                = new TH1D( "h_2ttag_0btag_METphi"              , "", 400, -3.2, 3.2 ); 
  TH1D *  h_2ttag_1btag_METphi                = new TH1D( "h_2ttag_1btag_METphi"              , "", 400, -3.2, 3.2 ); 
  TH1D *  h_2ttag_2btag_METphi                = new TH1D( "h_2ttag_2btag_METphi"              , "", 400, -3.2, 3.2 ); 
 
  TH1D *  h_2ttag_inclu_Nvtx                  = new TH1D( "h_2ttag_inclu_Nvtx"                , "", 100, 0,  100); 
  TH1D *  h_2ttag_0btag_Nvtx                  = new TH1D( "h_2ttag_0btag_Nvtx"                , "", 100, 0,  100); 
  TH1D *  h_2ttag_1btag_Nvtx                  = new TH1D( "h_2ttag_1btag_Nvtx"                , "", 100, 0,  100); 
  TH1D *  h_2ttag_2btag_Nvtx                  = new TH1D( "h_2ttag_2btag_Nvtx"                , "", 100, 0,  100); 
  
  TH1D *  h_2ttag_inclu_Jet0P                    = new TH1D( "h_2ttag_inclu_Jet0P"                    ,"", 400, 0, 6000); 
  TH1D *  h_2ttag_inclu_Jet0Pt                   = new TH1D( "h_2ttag_inclu_Jet0Pt"                   ,"", 400, 0, 4000); 
  TH1D *  h_2ttag_inclu_Jet0Phi                  = new TH1D( "h_2ttag_inclu_Jet0Phi"                  ,"", 400, -3.2, 3.2); 
  TH1D *  h_2ttag_inclu_Jet0Rap                  = new TH1D( "h_2ttag_inclu_Jet0Rap"                  ,"", 400, -5, 5); 
  TH1D *  h_2ttag_inclu_Jet0SDmass               = new TH1D( "h_2ttag_inclu_Jet0SDmass"               ,"", 400, 0, 400); 
  TH1D *  h_2ttag_inclu_Jet0SDmassCorrL23        = new TH1D( "h_2ttag_inclu_Jet0SDmassCorrL23"        ,"", 400, 0, 400); 
  TH1D *  h_2ttag_inclu_Jet0SDmassCorrL23Up      = new TH1D( "h_2ttag_inclu_Jet0SDmassCorrL23Up"      ,"", 400, 0, 400); 
  TH1D *  h_2ttag_inclu_Jet0Tau1                 = new TH1D( "h_2ttag_inclu_Jet0Tau1"                 ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0Tau2                 = new TH1D( "h_2ttag_inclu_Jet0Tau2"                 ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0Tau3                 = new TH1D( "h_2ttag_inclu_Jet0Tau3"                 ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0Tau4                 = new TH1D( "h_2ttag_inclu_Jet0Tau4"                 ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0SDmaxbdisc           = new TH1D( "h_2ttag_inclu_Jet0SDmaxbdisc"           ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0SDsubjet0pt          = new TH1D( "h_2ttag_inclu_Jet0SDsubjet0pt"          ,"", 400, 0, 2000); 
  TH1D *  h_2ttag_inclu_Jet0SDsubjet0mass        = new TH1D( "h_2ttag_inclu_Jet0SDsubjet0mass"        ,"", 400, 0, 300); 
  TH1D *  h_2ttag_inclu_Jet0SDsubjet0tau1        = new TH1D( "h_2ttag_inclu_Jet0SDsubjet0tau1"        ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0SDsubjet0tau2        = new TH1D( "h_2ttag_inclu_Jet0SDsubjet0tau2"        ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0SDsubjet0tau3        = new TH1D( "h_2ttag_inclu_Jet0SDsubjet0tau3"        ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0SDsubjet0bdisc       = new TH1D( "h_2ttag_inclu_Jet0SDsubjet0bdisc"       ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0SDsubjet1pt          = new TH1D( "h_2ttag_inclu_Jet0SDsubjet1pt"          ,"", 400, 0, 2000); 
  TH1D *  h_2ttag_inclu_Jet0SDsubjet1mass        = new TH1D( "h_2ttag_inclu_Jet0SDsubjet1mass"        ,"", 400, 0, 300); 
  TH1D *  h_2ttag_inclu_Jet0SDsubjet1tau1        = new TH1D( "h_2ttag_inclu_Jet0SDsubjet1tau1"        ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0SDsubjet1tau2        = new TH1D( "h_2ttag_inclu_Jet0SDsubjet1tau2"        ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0SDsubjet1tau3        = new TH1D( "h_2ttag_inclu_Jet0SDsubjet1tau3"        ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0SDsubjet1bdisc       = new TH1D( "h_2ttag_inclu_Jet0SDsubjet1bdisc"       ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiPt              = new TH1D( "h_2ttag_inclu_Jet0PuppiPt"              ,"", 400, 0, 4000); 
  TH1D *  h_2ttag_inclu_Jet0PuppiMass            = new TH1D( "h_2ttag_inclu_Jet0PuppiMass"            ,"", 400, 0, 300); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDpt            = new TH1D( "h_2ttag_inclu_Jet0PuppiSDpt"            ,"", 400, 0, 4000); 
  TH1D *  h_2ttag_inclu_Jet0PuppiTau1            = new TH1D( "h_2ttag_inclu_Jet0PuppiTau1"            ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiTau2            = new TH1D( "h_2ttag_inclu_Jet0PuppiTau2"            ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiTau3            = new TH1D( "h_2ttag_inclu_Jet0PuppiTau3"            ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiTau4            = new TH1D( "h_2ttag_inclu_Jet0PuppiTau4"            ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDmaxbdisc      = new TH1D( "h_2ttag_inclu_Jet0PuppiSDmaxbdisc"      ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDsubjet0pt     = new TH1D( "h_2ttag_inclu_Jet0PuppiSDsubjet0pt"     ,"", 400, 0, 2000); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDsubjet0mass   = new TH1D( "h_2ttag_inclu_Jet0PuppiSDsubjet0mass"   ,"", 400, 0, 300); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDsubjet0tau1   = new TH1D( "h_2ttag_inclu_Jet0PuppiSDsubjet0tau1"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDsubjet0tau2   = new TH1D( "h_2ttag_inclu_Jet0PuppiSDsubjet0tau2"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDsubjet0tau3   = new TH1D( "h_2ttag_inclu_Jet0PuppiSDsubjet0tau3"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDsubjet0bdisc  = new TH1D( "h_2ttag_inclu_Jet0PuppiSDsubjet0bdisc"  ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDsubjet1pt     = new TH1D( "h_2ttag_inclu_Jet0PuppiSDsubjet1pt"     ,"", 400, 0, 2000); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDsubjet1mass   = new TH1D( "h_2ttag_inclu_Jet0PuppiSDsubjet1mass"   ,"", 400, 0, 300); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDsubjet1tau1   = new TH1D( "h_2ttag_inclu_Jet0PuppiSDsubjet1tau1"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDsubjet1tau2   = new TH1D( "h_2ttag_inclu_Jet0PuppiSDsubjet1tau2"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDsubjet1tau3   = new TH1D( "h_2ttag_inclu_Jet0PuppiSDsubjet1tau3"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDsubjet1bdisc  = new TH1D( "h_2ttag_inclu_Jet0PuppiSDsubjet1bdisc"  ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0CHF                  = new TH1D( "h_2ttag_inclu_Jet0CHF"                  ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0NHF                  = new TH1D( "h_2ttag_inclu_Jet0NHF"                  ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0CM                   = new TH1D( "h_2ttag_inclu_Jet0CM"                   ,"", 200, 0, 200); 
  TH1D *  h_2ttag_inclu_Jet0NM                   = new TH1D( "h_2ttag_inclu_Jet0NM"                   ,"", 200, 0, 200); 
  TH1D *  h_2ttag_inclu_Jet0NEF                  = new TH1D( "h_2ttag_inclu_Jet0NEF"                  ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0CEF                  = new TH1D( "h_2ttag_inclu_Jet0CEF"                  ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0MF                   = new TH1D( "h_2ttag_inclu_Jet0MF"                   ,"", 10, 0, 10); 
  TH1D *  h_2ttag_inclu_Jet0Mult                 = new TH1D( "h_2ttag_inclu_Jet0Mult"                 ,"", 200, 0, 200); 

  TH1D *  h_2ttag_2btag_Jet0PuppiSDsubjet0pt     = new TH1D( "h_2ttag_2btag_Jet0PuppiSDsubjet0pt"     ,"", 400, 0, 2000);
  TH1D *  h_2ttag_2btag_Jet0PuppiSDsubjet0mass   = new TH1D( "h_2ttag_2btag_Jet0PuppiSDsubjet0mass"   ,"", 400, 0, 300); 
  TH1D *  h_2ttag_2btag_Jet0PuppiSDsubjet0tau1   = new TH1D( "h_2ttag_2btag_Jet0PuppiSDsubjet0tau1"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_2btag_Jet0PuppiSDsubjet0tau2   = new TH1D( "h_2ttag_2btag_Jet0PuppiSDsubjet0tau2"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_2btag_Jet0PuppiSDsubjet0tau3   = new TH1D( "h_2ttag_2btag_Jet0PuppiSDsubjet0tau3"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_2btag_Jet0PuppiSDsubjet0bdisc  = new TH1D( "h_2ttag_2btag_Jet0PuppiSDsubjet0bdisc"  ,"", 400, 0, 1); 
  TH1D *  h_2ttag_2btag_Jet0PuppiSDsubjet1pt     = new TH1D( "h_2ttag_2btag_Jet0PuppiSDsubjet1pt"     ,"", 400, 0, 2000);
  TH1D *  h_2ttag_2btag_Jet0PuppiSDsubjet1mass   = new TH1D( "h_2ttag_2btag_Jet0PuppiSDsubjet1mass"   ,"", 400, 0, 300); 
  TH1D *  h_2ttag_2btag_Jet0PuppiSDsubjet1tau1   = new TH1D( "h_2ttag_2btag_Jet0PuppiSDsubjet1tau1"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_2btag_Jet0PuppiSDsubjet1tau2   = new TH1D( "h_2ttag_2btag_Jet0PuppiSDsubjet1tau2"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_2btag_Jet0PuppiSDsubjet1tau3   = new TH1D( "h_2ttag_2btag_Jet0PuppiSDsubjet1tau3"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_2btag_Jet0PuppiSDsubjet1bdisc  = new TH1D( "h_2ttag_2btag_Jet0PuppiSDsubjet1bdisc"  ,"", 400, 0, 1); 

  TH1D *  h_2ttag_1btag_Jet0PuppiSDsubjet0pt     = new TH1D( "h_2ttag_1btag_Jet0PuppiSDsubjet0pt"     ,"", 400, 0, 2000);
  TH1D *  h_2ttag_1btag_Jet0PuppiSDsubjet0mass   = new TH1D( "h_2ttag_1btag_Jet0PuppiSDsubjet0mass"   ,"", 400, 0, 300); 
  TH1D *  h_2ttag_1btag_Jet0PuppiSDsubjet0tau1   = new TH1D( "h_2ttag_1btag_Jet0PuppiSDsubjet0tau1"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_1btag_Jet0PuppiSDsubjet0tau2   = new TH1D( "h_2ttag_1btag_Jet0PuppiSDsubjet0tau2"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_1btag_Jet0PuppiSDsubjet0tau3   = new TH1D( "h_2ttag_1btag_Jet0PuppiSDsubjet0tau3"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_1btag_Jet0PuppiSDsubjet0bdisc  = new TH1D( "h_2ttag_1btag_Jet0PuppiSDsubjet0bdisc"  ,"", 400, 0, 1); 
  TH1D *  h_2ttag_1btag_Jet0PuppiSDsubjet1pt     = new TH1D( "h_2ttag_1btag_Jet0PuppiSDsubjet1pt"     ,"", 400, 0, 2000);
  TH1D *  h_2ttag_1btag_Jet0PuppiSDsubjet1mass   = new TH1D( "h_2ttag_1btag_Jet0PuppiSDsubjet1mass"   ,"", 400, 0, 300); 
  TH1D *  h_2ttag_1btag_Jet0PuppiSDsubjet1tau1   = new TH1D( "h_2ttag_1btag_Jet0PuppiSDsubjet1tau1"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_1btag_Jet0PuppiSDsubjet1tau2   = new TH1D( "h_2ttag_1btag_Jet0PuppiSDsubjet1tau2"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_1btag_Jet0PuppiSDsubjet1tau3   = new TH1D( "h_2ttag_1btag_Jet0PuppiSDsubjet1tau3"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_1btag_Jet0PuppiSDsubjet1bdisc  = new TH1D( "h_2ttag_1btag_Jet0PuppiSDsubjet1bdisc"  ,"", 400, 0, 1); 

  TH1D *  h_2ttag_0btag_Jet0PuppiSDsubjet0pt     = new TH1D( "h_2ttag_0btag_Jet0PuppiSDsubjet0pt"     ,"", 400, 0, 2000);
  TH1D *  h_2ttag_0btag_Jet0PuppiSDsubjet0mass   = new TH1D( "h_2ttag_0btag_Jet0PuppiSDsubjet0mass"   ,"", 400, 0, 300); 
  TH1D *  h_2ttag_0btag_Jet0PuppiSDsubjet0tau1   = new TH1D( "h_2ttag_0btag_Jet0PuppiSDsubjet0tau1"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_0btag_Jet0PuppiSDsubjet0tau2   = new TH1D( "h_2ttag_0btag_Jet0PuppiSDsubjet0tau2"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_0btag_Jet0PuppiSDsubjet0tau3   = new TH1D( "h_2ttag_0btag_Jet0PuppiSDsubjet0tau3"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_0btag_Jet0PuppiSDsubjet0bdisc  = new TH1D( "h_2ttag_0btag_Jet0PuppiSDsubjet0bdisc"  ,"", 400, 0, 1); 
  TH1D *  h_2ttag_0btag_Jet0PuppiSDsubjet1pt     = new TH1D( "h_2ttag_0btag_Jet0PuppiSDsubjet1pt"     ,"", 400, 0, 2000);
  TH1D *  h_2ttag_0btag_Jet0PuppiSDsubjet1mass   = new TH1D( "h_2ttag_0btag_Jet0PuppiSDsubjet1mass"   ,"", 400, 0, 300); 
  TH1D *  h_2ttag_0btag_Jet0PuppiSDsubjet1tau1   = new TH1D( "h_2ttag_0btag_Jet0PuppiSDsubjet1tau1"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_0btag_Jet0PuppiSDsubjet1tau2   = new TH1D( "h_2ttag_0btag_Jet0PuppiSDsubjet1tau2"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_0btag_Jet0PuppiSDsubjet1tau3   = new TH1D( "h_2ttag_0btag_Jet0PuppiSDsubjet1tau3"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_0btag_Jet0PuppiSDsubjet1bdisc  = new TH1D( "h_2ttag_0btag_Jet0PuppiSDsubjet1bdisc"  ,"", 400, 0, 1); 



  TH1D *  h_2btag_DijetMass                                    = new TH1D("h_2btag_DijetMass"                            , "", 700,   0, 7000 );
  TH1D *  h_2btag_DeltaRap                                     = new TH1D("h_2btag_DeltaRap"                             , "", 500,   0,    5 );
  TH1D *  h_2btag_jet0massSD                                   = new TH1D("h_2btag_jet0massSD"                           , "", 500,   0,  500 );
  TH1D *  h_2btag_jet0tau32                                    = new TH1D("h_2btag_jet0tau32"                            , "", 200,   0,    1 );
  TH1D *  h_2btag_jet0tau21                                    = new TH1D("h_2btag_jet0tau21"                            , "", 200,   0,    1 );
  TH1D *  h_2btag_jet0tau1                                     = new TH1D("h_2btag_jet0tau1"                             , "", 200,   0,    1 );
  TH1D *  h_2btag_jet0tau2                                     = new TH1D("h_2btag_jet0tau2"                             , "", 200,   0,    1 );
  TH1D *  h_2btag_jet0tau3                                     = new TH1D("h_2btag_jet0tau3"                             , "", 200,   0,    1 );
  TH1D *  h_2btag_jet0subjet0mass                              = new TH1D("h_2btag_jet0subjet0mass"                      , "", 400,   0,  400 );
  TH1D *  h_2btag_jet0subjet1mass                              = new TH1D("h_2btag_jet0subjet1mass"                      , "", 400,   0,  400 );
  TH2D *  h_2btag_jet0subjet0mass_jet0subjet1mass              = new TH2D("h_2btag_jet0subjet0mass_jet0subjet1mass"      , "", 400,   0,  400 , 400,   0,  400 );
  TH2D *  h_2btag_jet0subjet0bdisc_jet0subjet1bdisc            = new TH2D("h_2btag_jet0subjet0bdisc_jet0subjet1bdisc"    , "", 100,   0,    1 , 100,   0,    1 );
  TH1D *  h_2btag_jet1massSD                                   = new TH1D("h_2btag_jet1massSD"                           , "", 500,   0,  500 );
  TH1D *  h_2btag_jet1tau32                                    = new TH1D("h_2btag_jet1tau32"                            , "", 200,   0,    1 );
  TH1D *  h_2btag_jet1tau21                                    = new TH1D("h_2btag_jet1tau21"                            , "", 200,   0,    1 );
  TH1D *  h_2btag_jet1tau1                                     = new TH1D("h_2btag_jet1tau1"                             , "", 200,   0,    1 );
  TH1D *  h_2btag_jet1tau2                                     = new TH1D("h_2btag_jet1tau2"                             , "", 200,   0,    1 );
  TH1D *  h_2btag_jet1tau3                                     = new TH1D("h_2btag_jet1tau3"                             , "", 200,   0,    1 );
  TH1D *  h_2btag_jet1subjet0mass                              = new TH1D("h_2btag_jet1subjet0mass"                      , "", 400,   0,  400 );
  TH1D *  h_2btag_jet1subjet1mass                              = new TH1D("h_2btag_jet1subjet1mass"                      , "", 400,   0,  400 );
  TH2D *  h_2btag_jet1subjet0mass_jet1subjet1mass              = new TH2D("h_2btag_jet1subjet0mass_jet1subjet1mass"      , "", 400,   0,  400 , 400,   0,  400 );
  TH2D *  h_2btag_jet1subjet0bdisc_jet1subjet1bdisc            = new TH2D("h_2btag_jet1subjet0bdisc_jet1subjet1bdisc"    , "", 100,   0,    1 , 100,   0,    1 );

  TH1D *  h_2btag_jet1ttag_jet0massSD                          = new TH1D("h_2btag_jet1ttag_jet0massSD"                           , "", 500,   0,  500 );
  TH1D *  h_2btag_jet1ttag_jet0tau32                           = new TH1D("h_2btag_jet1ttag_jet0tau32"                            , "", 200,   0,    1 );
  TH1D *  h_2btag_jet1ttag_jet0tau21                           = new TH1D("h_2btag_jet1ttag_jet0tau21"                            , "", 200,   0,    1 );
  TH1D *  h_2btag_jet1ttag_jet0tau1                            = new TH1D("h_2btag_jet1ttag_jet0tau1"                             , "", 200,   0,    1 );
  TH1D *  h_2btag_jet1ttag_jet0tau2                            = new TH1D("h_2btag_jet1ttag_jet0tau2"                             , "", 200,   0,    1 );
  TH1D *  h_2btag_jet1ttag_jet0tau3                            = new TH1D("h_2btag_jet1ttag_jet0tau3"                             , "", 200,   0,    1 );
  TH1D *  h_2btag_jet1ttag_jet0subjet0mass                     = new TH1D("h_2btag_jet1ttag_jet0subjet0mass"                      , "", 400,   0,  400 );
  TH1D *  h_2btag_jet1ttag_jet0subjet1mass                     = new TH1D("h_2btag_jet1ttag_jet0subjet1mass"                      , "", 400,   0,  400 );
  TH2D *  h_2btag_jet1ttag_jet0subjet0mass_jet0subjet1mass     = new TH2D("h_2btag_jet1ttag_jet0subjet0mass_jet0subjet1mass"      , "", 400,   0,  400 , 400,   0,  400 );
  TH2D *  h_2btag_jet1ttag_jet0subjet0bdisc_jet0subjet1bdisc   = new TH2D("h_2btag_jet1ttag_jet0subjet0bdisc_jet0subjet1bdisc"    , "", 100,   0,    1 , 100,   0,    1 );

  TH1D *  h_2btag_jet0ttag_jet1massSD                          = new TH1D("h_2btag_jet0ttag_jet1massSD"                           , "", 500,   0,  500 );
  TH1D *  h_2btag_jet0ttag_jet1tau32                           = new TH1D("h_2btag_jet0ttag_jet1tau32"                            , "", 200,   0,    1 );
  TH1D *  h_2btag_jet0ttag_jet1tau21                           = new TH1D("h_2btag_jet0ttag_jet1tau21"                            , "", 200,   0,    1 );
  TH1D *  h_2btag_jet0ttag_jet1tau1                            = new TH1D("h_2btag_jet0ttag_jet1tau1"                             , "", 200,   0,    1 );
  TH1D *  h_2btag_jet0ttag_jet1tau2                            = new TH1D("h_2btag_jet0ttag_jet1tau2"                             , "", 200,   0,    1 );
  TH1D *  h_2btag_jet0ttag_jet1tau3                            = new TH1D("h_2btag_jet0ttag_jet1tau3"                             , "", 200,   0,    1 );
  TH1D *  h_2btag_jet0ttag_jet1subjet0mass                     = new TH1D("h_2btag_jet0ttag_jet1subjet0mass"                      , "", 400,   0,  400 );
  TH1D *  h_2btag_jet0ttag_jet1subjet1mass                     = new TH1D("h_2btag_jet0ttag_jet1subjet1mass"                      , "", 400,   0,  400 );
  TH2D *  h_2btag_jet0ttag_jet1subjet0mass_jet1subjet1mass     = new TH2D("h_2btag_jet0ttag_jet1subjet0mass_jet1subjet1mass"      , "", 400,   0,  400 , 400,   0,  400 );
  TH2D *  h_2btag_jet0ttag_jet1subjet0bdisc_jet1subjet1bdisc   = new TH2D("h_2btag_jet0ttag_jet1subjet0bdisc_jet1subjet1bdisc"    , "", 100,   0,    1 , 100,   0,    1 );

  TH1D *  h_2btag_jet1ttag_jet0tautag_jet0massSD               = new TH1D("h_2btag_jet1ttag_jet0tautag_jet0massSD"                          , "", 500,   0,  500 );
  TH1D *  h_2btag_jet1ttag_jet0masstag_jet0tau32               = new TH1D("h_2btag_jet1ttag_jet0masstag_jet0tau32"                          , "", 200,   0,    1 );
  TH1D *  h_2btag_jet1ttag_jet0masstag_jet0tau21               = new TH1D("h_2btag_jet1ttag_jet0masstag_jet0tau21"                          , "", 200,   0,    1 );
  TH1D *  h_2btag_jet1ttag_jet0masstag_jet0tau1                = new TH1D("h_2btag_jet1ttag_jet0masstag_jet0tau1"                           , "", 200,   0,    1 );
  TH1D *  h_2btag_jet1ttag_jet0masstag_jet0tau2                = new TH1D("h_2btag_jet1ttag_jet0masstag_jet0tau2"                           , "", 200,   0,    1 );
  TH1D *  h_2btag_jet1ttag_jet0masstag_jet0tau3                = new TH1D("h_2btag_jet1ttag_jet0masstag_jet0tau3"                           , "", 200,   0,    1 );
  TH1D *  h_2btag_jet0ttag_jet1tautag_jet1massSD               = new TH1D("h_2btag_jet0ttag_jet1tautag_jet1massSD"                          , "", 500,   0,  500 );
  TH1D *  h_2btag_jet0ttag_jet1masstag_jet1tau32               = new TH1D("h_2btag_jet0ttag_jet1masstag_jet1tau32"                          , "", 200,   0,    1 );
  TH1D *  h_2btag_jet0ttag_jet1masstag_jet1tau21               = new TH1D("h_2btag_jet0ttag_jet1masstag_jet1tau21"                          , "", 200,   0,    1 );
  TH1D *  h_2btag_jet0ttag_jet1masstag_jet1tau1                = new TH1D("h_2btag_jet0ttag_jet1masstag_jet1tau1"                           , "", 200,   0,    1 );
  TH1D *  h_2btag_jet0ttag_jet1masstag_jet1tau2                = new TH1D("h_2btag_jet0ttag_jet1masstag_jet1tau2"                           , "", 200,   0,    1 );
  TH1D *  h_2btag_jet0ttag_jet1masstag_jet1tau3                = new TH1D("h_2btag_jet0ttag_jet1masstag_jet1tau3"                           , "", 200,   0,    1 );

  TH1D *  h_topTag_jet0subjet0pt                               = new TH1D("h_topTag_jet0subjet0pt"                        , "", 400,   0, 2000 );
  TH1D *  h_topTag_jet0subjet1pt                               = new TH1D("h_topTag_jet0subjet1pt"                        , "", 400,   0, 2000 );
  TH1D *  h_topTag_jet0pt                                      = new TH1D("h_topTag_jet0pt"                               , "", 400, 400, 4400 );
  TH2D *  h_topTag_jet0pt_jet0subjet0pt                        = new TH2D("h_topTag_jet0pt_jet0subjet0pt"                 , "", 400, 400, 4400 , 400,   0, 2000 );
  TH2D *  h_topTag_jet0pt_jet0subjet1pt                        = new TH2D("h_topTag_jet0pt_jet0subjet1pt"                 , "", 400, 400, 4400 , 400,   0, 2000 );
  TH2D *  h_topTag_jet0subjet0pt_jet0subjet1pt                 = new TH2D("h_topTag_jet0subjet0pt_jet0subjet1pt"          , "", 400,   0, 2000 , 400,   0, 2000 );
  TH2D *  h_topTag_jet0subjet0mass_jet0subjet1mass             = new TH2D("h_topTag_jet0subjet0mass_jet0subjet1mass"      , "", 400,   0,  400 , 400,   0,  400 );
  TH2D *  h_topTag_jet0subjet0bdisc_jet0subjet1bdisc           = new TH2D("h_topTag_jet0subjet0bdisc_jet0subjet1bdisc"    , "", 100,   0,    1 , 100,   0,    1 );
  //TH2D *  h_topTag_jet0subjet0flav_jet0subjet1flav             = new TH2D("h_topTag_jet0subjet0flav_jet0subjet1flav"      , "",  30,   0,   30 ,  30,   0,   30 );                                                                     
  TH1D *  h_topTag_jet0subjet0mass                             = new TH1D("h_topTag_jet0subjet0mass"                      , "", 400,   0,  400 );
  TH1D *  h_topTag_jet0subjet1mass                             = new TH1D("h_topTag_jet0subjet1mass"                      , "", 400,   0,  400 );
  TH1D *  h_topTag_jet0subjet0bdisc                            = new TH1D("h_topTag_jet0subjet0bdisc"                     , "", 100,   0,    1 );
  TH1D *  h_topTag_jet0subjet1bdisc                            = new TH1D("h_topTag_jet0subjet1bdisc"                     , "", 100,   0,    1 );
  //TH1D *  h_topTag_jet0subjet0flav                           = new TH1D("h_topTag_jet0subjet0flav"                      , "",  30,   0,   30 );                                                                                      
  //TH1D *  h_topTag_jet0subjet1flav                           = new TH1D("h_topTag_jet0subjet1flav"                      , "",  30,   0,   30 );                                                                                      
  TH1D *  h_topTag_jet0maxBdisc                               = new TH1D("h_topTag_jet0maxBdisc"                         , "", 100,   0,    1 );
  //TH1D *  h_topTag_jet0maxBdiscflav                          = new TH1D("h_topTag_jet0maxBdiscflav"                     , "",  30,   0,   30 );

  TH1D *  h_topTagbTag_jet0subjet0pt                            = new TH1D("h_topTagbTag_jet0subjet0pt"                        , "", 400,   0, 2000 );
  TH1D *  h_topTagbTag_jet0subjet1pt                            = new TH1D("h_topTagbTag_jet0subjet1pt"                        , "", 400,   0, 2000 );
  TH1D *  h_topTagbTag_jet0pt                                   = new TH1D("h_topTagbTag_jet0pt"                               , "", 400, 400, 4400 );
  TH2D *  h_topTagbTag_jet0pt_jet0subjet0pt                     = new TH2D("h_topTagbTag_jet0pt_jet0subjet0pt"                 , "", 400, 400, 4400 , 400,   0, 2000 );
  TH2D *  h_topTagbTag_jet0pt_jet0subjet1pt                     = new TH2D("h_topTagbTag_jet0pt_jet0subjet1pt"                 , "", 400, 400, 4400 , 400,   0, 2000 );
  TH2D *  h_topTagbTag_jet0subjet0pt_jet0subjet1pt              = new TH2D("h_topTagbTag_jet0subjet0pt_jet0subjet1pt"          , "", 400,   0, 2000 , 400,   0, 2000 );
  TH2D *  h_topTagbTag_jet0subjet0mass_jet0subjet1mass          = new TH2D("h_topTagbTag_jet0subjet0mass_jet0subjet1mass"      , "", 400,   0,  400 , 400,   0,  400 );
  TH2D *  h_topTagbTag_jet0subjet0bdisc_jet0subjet1bdisc        = new TH2D("h_topTagbTag_jet0subjet0bdisc_jet0subjet1bdisc"    , "", 100,   0,    1 , 100,   0,    1 );
  //TH2D *  h_topTagbTag_jet0subjet0flav_jet0subjet1flav          = new TH2D("h_topTagbTag_jet0subjet0flav_jet0subjet1flav"      , "",  30,   0,   30 ,  30,   0,   30 );                                                             
  TH1D *  h_topTagbTag_jet0subjet0mass                          = new TH1D("h_topTagbTag_jet0subjet0mass"                      , "", 400,   0,  400 );
  TH1D *  h_topTagbTag_jet0subjet1mass                          = new TH1D("h_topTagbTag_jet0subjet1mass"                      , "", 400,   0,  400 );
  TH1D *  h_topTagbTag_jet0subjet0bdisc                         = new TH1D("h_topTagbTag_jet0subjet0bdisc"                     , "", 100,   0,    1 );
  TH1D *  h_topTagbTag_jet0subjet1bdisc                         = new TH1D("h_topTagbTag_jet0subjet1bdisc"                     , "", 100,   0,    1 );
  //TH1D *  h_topTagbTag_jet0subjet0flav                          = new TH1D("h_topTagbTag_jet0subjet0flav"                      , "",  30,   0,   30 );                                                                              
  //TH1D *  h_topTagbTag_jet0subjet1flav                          = new TH1D("h_topTagbTag_jet0subjet1flav"                      , "",  30,   0,   30 );                                                                              
  TH1D *  h_topTagbTag_jet0maxBdisc                             = new TH1D("h_topTagbTag_jet0maxBdisc"                         , "", 100,   0,    1 );
  //TH1D *  h_topTagbTag_jet0maxBdiscflav                         = new TH1D("h_topTagbTag_jet0maxBdiscflav"                     , "",  30,   0,   30 );

    

  // DDT tests
  TH1D *  h_jet0_rhoRatio                       = new TH1D("h_jet0_rhoRatio"                       , "" , 200 , -20, 10 ) ;
  TH1D *  h_jet0_rhoRatioPrime                  = new TH1D("h_jet0_rhoRatioPrime"                  , "" , 200 , -20, 10 ) ;
  TH1D *  h_jet0_rhoRatioPmag                   = new TH1D("h_jet0_rhoRatioPmag"                   , "" , 200 , -20, 10 ) ;
  TH1D *  h_jet0_rhoRatioPmagPrime              = new TH1D("h_jet0_rhoRatioPmagPrime"              , "" , 200 , -20, 10 ) ;
  TH1D *  h_jet0_rhoRatioPuppi                  = new TH1D("h_jet0_rhoRatioPuppi"                  , "" , 200 , -20, 10 ) ;
  TH1D *  h_jet0_rhoRatioPuppiPrime             = new TH1D("h_jet0_rhoRatioPuppiPrime"             , "" , 200 , -20, 10 ) ;
  TH1D *  h_jet0_rhoRatioPuppiPmag              = new TH1D("h_jet0_rhoRatioPuppiPmag"              , "" , 200 , -20, 10 ) ;
  TH1D *  h_jet0_rhoRatioPuppiPmagPrime         = new TH1D("h_jet0_rhoRatioPuppiPmagPrime"         , "" , 200 , -20, 10 ) ;
  TH1D *  h_jet1_rhoRatio                       = new TH1D("h_jet1_rhoRatio"                       , "" , 200 , -20, 10 ) ;
  TH1D *  h_jet1_rhoRatioPrime                  = new TH1D("h_jet1_rhoRatioPrime"                  , "" , 200 , -20, 10 ) ;
  TH1D *  h_jet1_rhoRatioPmag                   = new TH1D("h_jet1_rhoRatioPmag"                   , "" , 200 , -20, 10 ) ;
  TH1D *  h_jet1_rhoRatioPmagPrime              = new TH1D("h_jet1_rhoRatioPmagPrime"              , "" , 200 , -20, 10 ) ;
  TH1D *  h_jet1_rhoRatioPuppi                  = new TH1D("h_jet1_rhoRatioPuppi"                  , "" , 200 , -20, 10 ) ;
  TH1D *  h_jet1_rhoRatioPuppiPrime             = new TH1D("h_jet1_rhoRatioPuppiPrime"             , "" , 200 , -20, 10 ) ;
  TH1D *  h_jet1_rhoRatioPuppiPmag              = new TH1D("h_jet1_rhoRatioPuppiPmag"              , "" , 200 , -20, 10 ) ;
  TH1D *  h_jet1_rhoRatioPuppiPmagPrime         = new TH1D("h_jet1_rhoRatioPuppiPmagPrime"         , "" , 200 , -20, 10 ) ;
  TH2D *  h_jet0_tau32_rhoRatio                 = new TH2D("h_jet0_tau32_rhoRatio"                 , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet0_tau32_rhoRatioPrime            = new TH2D("h_jet0_tau32_rhoRatioPrime"            , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet0_tau32_rhoRatioPmag             = new TH2D("h_jet0_tau32_rhoRatioPmag"             , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet0_tau32_rhoRatioPmagPrime        = new TH2D("h_jet0_tau32_rhoRatioPmagPrime"        , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet0_tau32_rhoRatioPuppi            = new TH2D("h_jet0_tau32_rhoRatioPuppi"            , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet0_tau32_rhoRatioPuppiPrime       = new TH2D("h_jet0_tau32_rhoRatioPuppiPrime"       , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet0_tau32_rhoRatioPuppiPmag        = new TH2D("h_jet0_tau32_rhoRatioPuppiPmag"        , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet0_tau32_rhoRatioPuppiPmagPrime   = new TH2D("h_jet0_tau32_rhoRatioPuppiPmagPrime"   , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet1_tau32_rhoRatio                 = new TH2D("h_jet1_tau32_rhoRatio"                 , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet1_tau32_rhoRatioPrime            = new TH2D("h_jet1_tau32_rhoRatioPrime"            , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet1_tau32_rhoRatioPmag             = new TH2D("h_jet1_tau32_rhoRatioPmag"             , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet1_tau32_rhoRatioPmagPrime        = new TH2D("h_jet1_tau32_rhoRatioPmagPrime"        , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet1_tau32_rhoRatioPuppi            = new TH2D("h_jet1_tau32_rhoRatioPuppi"            , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet1_tau32_rhoRatioPuppiPrime       = new TH2D("h_jet1_tau32_rhoRatioPuppiPrime"       , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet1_tau32_rhoRatioPuppiPmag        = new TH2D("h_jet1_tau32_rhoRatioPuppiPmag"        , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet1_tau32_rhoRatioPuppiPmagPrime   = new TH2D("h_jet1_tau32_rhoRatioPuppiPmagPrime"   , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet0_tau21_rhoRatio                 = new TH2D("h_jet0_tau21_rhoRatio"                 , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet0_tau21_rhoRatioPrime            = new TH2D("h_jet0_tau21_rhoRatioPrime"            , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet0_tau21_rhoRatioPmag             = new TH2D("h_jet0_tau21_rhoRatioPmag"             , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet0_tau21_rhoRatioPmagPrime        = new TH2D("h_jet0_tau21_rhoRatioPmagPrime"        , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet0_tau21_rhoRatioPuppi            = new TH2D("h_jet0_tau21_rhoRatioPuppi"            , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet0_tau21_rhoRatioPuppiPrime       = new TH2D("h_jet0_tau21_rhoRatioPuppiPrime"       , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet0_tau21_rhoRatioPuppiPmag        = new TH2D("h_jet0_tau21_rhoRatioPuppiPmag"        , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet0_tau21_rhoRatioPuppiPmagPrime   = new TH2D("h_jet0_tau21_rhoRatioPuppiPmagPrime"   , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet1_tau21_rhoRatio                 = new TH2D("h_jet1_tau21_rhoRatio"                 , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet1_tau21_rhoRatioPrime            = new TH2D("h_jet1_tau21_rhoRatioPrime"            , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet1_tau21_rhoRatioPmag             = new TH2D("h_jet1_tau21_rhoRatioPmag"             , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet1_tau21_rhoRatioPmagPrime        = new TH2D("h_jet1_tau21_rhoRatioPmagPrime"        , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet1_tau21_rhoRatioPuppi            = new TH2D("h_jet1_tau21_rhoRatioPuppi"            , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet1_tau21_rhoRatioPuppiPrime       = new TH2D("h_jet1_tau21_rhoRatioPuppiPrime"       , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet1_tau21_rhoRatioPuppiPmag        = new TH2D("h_jet1_tau21_rhoRatioPuppiPmag"        , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet1_tau21_rhoRatioPuppiPmagPrime   = new TH2D("h_jet1_tau21_rhoRatioPuppiPmagPrime"   , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet0_tau42_rhoRatio                 = new TH2D("h_jet0_tau42_rhoRatio"                 , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet0_tau42_rhoRatioPrime            = new TH2D("h_jet0_tau42_rhoRatioPrime"            , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet0_tau42_rhoRatioPmag             = new TH2D("h_jet0_tau42_rhoRatioPmag"             , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet0_tau42_rhoRatioPmagPrime        = new TH2D("h_jet0_tau42_rhoRatioPmagPrime"        , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet0_tau42_rhoRatioPuppi            = new TH2D("h_jet0_tau42_rhoRatioPuppi"            , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet0_tau42_rhoRatioPuppiPrime       = new TH2D("h_jet0_tau42_rhoRatioPuppiPrime"       , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet0_tau42_rhoRatioPuppiPmag        = new TH2D("h_jet0_tau42_rhoRatioPuppiPmag"        , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet0_tau42_rhoRatioPuppiPmagPrime   = new TH2D("h_jet0_tau42_rhoRatioPuppiPmagPrime"   , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet1_tau42_rhoRatio                 = new TH2D("h_jet1_tau42_rhoRatio"                 , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet1_tau42_rhoRatioPrime            = new TH2D("h_jet1_tau42_rhoRatioPrime"            , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet1_tau42_rhoRatioPmag             = new TH2D("h_jet1_tau42_rhoRatioPmag"             , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet1_tau42_rhoRatioPmagPrime        = new TH2D("h_jet1_tau42_rhoRatioPmagPrime"        , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet1_tau42_rhoRatioPuppi            = new TH2D("h_jet1_tau42_rhoRatioPuppi"            , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet1_tau42_rhoRatioPuppiPrime       = new TH2D("h_jet1_tau42_rhoRatioPuppiPrime"       , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet1_tau42_rhoRatioPuppiPmag        = new TH2D("h_jet1_tau42_rhoRatioPuppiPmag"        , "" , 200 , -20, 10, 200, 0, 1 ) ;
  TH2D *  h_jet1_tau42_rhoRatioPuppiPmagPrime   = new TH2D("h_jet1_tau42_rhoRatioPuppiPmagPrime"   , "" , 200 , -20, 10, 200, 0, 1 ) ;

  //Hadronic mtt selection and background estimaion
  TH1D *  h_mttMass_tagMassSDTau32_dRapHi_inclusive         = new TH1D("h_mttMass_tagMassSDTau32_dRapHi_inclusive"   , "", 700, 0, 7000 );
  TH1D *  h_mttMass_tagMassSDTau32_dRapHi_0btag             = new TH1D("h_mttMass_tagMassSDTau32_dRapHi_0btag"       , "", 700, 0, 7000 );
  TH1D *  h_mttMass_tagMassSDTau32_dRapHi_1btag             = new TH1D("h_mttMass_tagMassSDTau32_dRapHi_1btag"       , "", 700, 0, 7000 );
  TH1D *  h_mttMass_tagMassSDTau32_dRapHi_2btag             = new TH1D("h_mttMass_tagMassSDTau32_dRapHi_2btag"       , "", 700, 0, 7000 );
  TH1D *  h_mttMass_tagMassSDTau32_dRapLo_inclusive         = new TH1D("h_mttMass_tagMassSDTau32_dRapLo_inclusive"   , "", 700, 0, 7000 );
  TH1D *  h_mttMass_tagMassSDTau32_dRapLo_0btag             = new TH1D("h_mttMass_tagMassSDTau32_dRapLo_0btag"       , "", 700, 0, 7000 );
  TH1D *  h_mttMass_tagMassSDTau32_dRapLo_1btag             = new TH1D("h_mttMass_tagMassSDTau32_dRapLo_1btag"       , "", 700, 0, 7000 );
  TH1D *  h_mttMass_tagMassSDTau32_dRapLo_2btag             = new TH1D("h_mttMass_tagMassSDTau32_dRapLo_2btag"       , "", 700, 0, 7000 );
  TH1D *  h_mttMass_tagMassSDTau32_dRapIn_inclusive         = new TH1D("h_mttMass_tagMassSDTau32_dRapIn_inclusive"   , "", 700, 0, 7000 );
  TH1D *  h_mttMass_tagMassSDTau32_dRapIn_0btag             = new TH1D("h_mttMass_tagMassSDTau32_dRapIn_0btag"       , "", 700, 0, 7000 );
  TH1D *  h_mttMass_tagMassSDTau32_dRapIn_1btag             = new TH1D("h_mttMass_tagMassSDTau32_dRapIn_1btag"       , "", 700, 0, 7000 );
  TH1D *  h_mttMass_tagMassSDTau32_dRapIn_2btag             = new TH1D("h_mttMass_tagMassSDTau32_dRapIn_2btag"       , "", 700, 0, 7000 );

  TH1D *  h_bkgdEst_tagMassSDTau32_dRapHi_inclusive         = new TH1D("h_bkgdEst_tagMassSDTau32_dRapHi_inclusive"    , "", 700, 0, 7000 );
  TH1D *  h_bkgdEst_tagMassSDTau32_dRapHi_0btag             = new TH1D("h_bkgdEst_tagMassSDTau32_dRapHi_0btag"        , "", 700, 0, 7000 );
  TH1D *  h_bkgdEst_tagMassSDTau32_dRapHi_1btag             = new TH1D("h_bkgdEst_tagMassSDTau32_dRapHi_1btag"        , "", 700, 0, 7000 );
  TH1D *  h_bkgdEst_tagMassSDTau32_dRapHi_2btag             = new TH1D("h_bkgdEst_tagMassSDTau32_dRapHi_2btag"        , "", 700, 0, 7000 );
  TH1D *  h_bkgdEst_tagMassSDTau32_dRapLo_inclusive         = new TH1D("h_bkgdEst_tagMassSDTau32_dRapLo_inclusive"    , "", 700, 0, 7000 );
  TH1D *  h_bkgdEst_tagMassSDTau32_dRapLo_0btag             = new TH1D("h_bkgdEst_tagMassSDTau32_dRapLo_0btag"        , "", 700, 0, 7000 );
  TH1D *  h_bkgdEst_tagMassSDTau32_dRapLo_1btag             = new TH1D("h_bkgdEst_tagMassSDTau32_dRapLo_1btag"        , "", 700, 0, 7000 );
  TH1D *  h_bkgdEst_tagMassSDTau32_dRapLo_2btag             = new TH1D("h_bkgdEst_tagMassSDTau32_dRapLo_2btag"        , "", 700, 0, 7000 );
  TH1D *  h_bkgdEst_tagMassSDTau32_dRapIn_inclusive         = new TH1D("h_bkgdEst_tagMassSDTau32_dRapIn_inclusive"    , "", 700, 0, 7000 );
  TH1D *  h_bkgdEst_tagMassSDTau32_dRapIn_0btag             = new TH1D("h_bkgdEst_tagMassSDTau32_dRapIn_0btag"        , "", 700, 0, 7000 );
  TH1D *  h_bkgdEst_tagMassSDTau32_dRapIn_1btag             = new TH1D("h_bkgdEst_tagMassSDTau32_dRapIn_1btag"        , "", 700, 0, 7000 );
  TH1D *  h_bkgdEst_tagMassSDTau32_dRapIn_2btag             = new TH1D("h_bkgdEst_tagMassSDTau32_dRapIn_2btag"        , "", 700, 0, 7000 );

  TH1D *  h_bkgdEst_modMass_tagMassSDTau32_dRapHi_inclusive = new TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapHi_inclusive"    , "", 700, 0, 7000 );
  TH1D *  h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag     = new TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag"        , "", 700, 0, 7000 );
  TH1D *  h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag     = new TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag"        , "", 700, 0, 7000 );
  TH1D *  h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag     = new TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag"        , "", 700, 0, 7000 );
  TH1D *  h_bkgdEst_modMass_tagMassSDTau32_dRapLo_inclusive = new TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapLo_inclusive"    , "", 700, 0, 7000 );
  TH1D *  h_bkgdEst_modMass_tagMassSDTau32_dRapLo_0btag     = new TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapLo_0btag"        , "", 700, 0, 7000 );
  TH1D *  h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag     = new TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag"        , "", 700, 0, 7000 );
  TH1D *  h_bkgdEst_modMass_tagMassSDTau32_dRapLo_2btag     = new TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapLo_2btag"        , "", 700, 0, 7000 );
  TH1D *  h_bkgdEst_modMass_tagMassSDTau32_dRapIn_inclusive = new TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapIn_inclusive"    , "", 700, 0, 7000 );
  TH1D *  h_bkgdEst_modMass_tagMassSDTau32_dRapIn_0btag     = new TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapIn_0btag"        , "", 700, 0, 7000 );
  TH1D *  h_bkgdEst_modMass_tagMassSDTau32_dRapIn_1btag     = new TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapIn_1btag"        , "", 700, 0, 7000 );
  TH1D *  h_bkgdEst_modMass_tagMassSDTau32_dRapIn_2btag     = new TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapIn_2btag"        , "", 700, 0, 7000 );
  

  cout<<"make bkgd est histograms"<<endl;


  //background estimate


  TH1D *  h_DijetMass_modMass_jet0                             = new TH1D( "h_DijetMass_modMass_jet0"   ,"", 400, 0, 8000); 
  TH1D *  h_DijetMass_modMass_jet1                             = new TH1D( "h_DijetMass_modMass_jet1"   ,"", 400, 0, 8000); 

   
   
   
   
   
   
   
  // 8888888b.                        888 8888888b.  d8b          888    
  // 888   Y88b                       888 888  "Y88b Y8P          888    
  // 888    888                       888 888    888              888    
  // 888   d88P 888d888  .d88b.   .d88888 888    888 888 .d8888b  888888 
  // 8888888P"  888P"   d8P  Y8b d88" 888 888    888 888 88K      888    
  // 888        888     88888888 888  888 888    888 888 "Y8888b. 888    
  // 888        888     Y8b.     Y88b 888 888  .d88P 888      X88 Y88b.  
  // 888        888      "Y8888   "Y88888 8888888P"  888  88888P'  "Y888 


  //Predicted Distribution - Background estimation
  cout<<"PredictedDistribution setup"<<endl;
  cout<<"Check mistag Integral "<<h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag ->Integral() <<endl;

  // --- CHS
  // -- dRapHi
  // - 0btag
  PredictedDistribution * predDist_CHS_dRapHi_0btag_DijetMass      = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_CHS_dRapHi_0btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapHi_0btag_DijetMassMod   = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_CHS_dRapHi_0btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapHi_0btag_HT             = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_CHS_dRapHi_0btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_CHS_dRapHi_0btag_DeltaRap       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_CHS_dRapHi_0btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_CHS_dRapHi_0btag_JetP           = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_CHS_dRapHi_0btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapHi_0btag_JetPt          = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_CHS_dRapHi_0btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapHi_0btag_JetY           = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_CHS_dRapHi_0btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_CHS_dRapHi_0btag_JetSDmass      = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_CHS_dRapHi_0btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_CHS_dRapHi_0btag_JetTau32       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_CHS_dRapHi_0btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_CHS_dRapHi_0btag_maxbdisc       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_CHS_dRapHi_0btag_maxbdisc"     , "",  200, 0,     1);
  // - 1btag
  PredictedDistribution * predDist_CHS_dRapHi_1btag_DijetMass      = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_CHS_dRapHi_1btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapHi_1btag_DijetMassMod   = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_CHS_dRapHi_1btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapHi_1btag_HT             = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_CHS_dRapHi_1btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_CHS_dRapHi_1btag_DeltaRap       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_CHS_dRapHi_1btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_CHS_dRapHi_1btag_JetP           = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_CHS_dRapHi_1btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapHi_1btag_JetPt          = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_CHS_dRapHi_1btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapHi_1btag_JetY           = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_CHS_dRapHi_1btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_CHS_dRapHi_1btag_JetSDmass      = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_CHS_dRapHi_1btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_CHS_dRapHi_1btag_JetTau32       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_CHS_dRapHi_1btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_CHS_dRapHi_1btag_maxbdisc       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_CHS_dRapHi_1btag_maxbdisc"     , "",  200, 0,     1);
  // - 2btag
  PredictedDistribution * predDist_CHS_dRapHi_2btag_DijetMass      = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_CHS_dRapHi_2btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapHi_2btag_DijetMassMod   = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_CHS_dRapHi_2btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapHi_2btag_HT             = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_CHS_dRapHi_2btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_CHS_dRapHi_2btag_DeltaRap       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_CHS_dRapHi_2btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_CHS_dRapHi_2btag_JetP           = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_CHS_dRapHi_2btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapHi_2btag_JetPt          = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_CHS_dRapHi_2btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapHi_2btag_JetY           = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_CHS_dRapHi_2btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_CHS_dRapHi_2btag_JetSDmass      = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_CHS_dRapHi_2btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_CHS_dRapHi_2btag_JetTau32       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_CHS_dRapHi_2btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_CHS_dRapHi_2btag_maxbdisc       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_CHS_dRapHi_2btag_maxbdisc"     , "",  200, 0,     1);
  // - btag inclusive
  PredictedDistribution * predDist_CHS_dRapHi_inclu_DijetMass      = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_CHS_dRapHi_inclu_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapHi_inclu_DijetMassMod   = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_CHS_dRapHi_inclu_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapHi_inclu_HT             = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_CHS_dRapHi_inclu_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_CHS_dRapHi_inclu_DeltaRap       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_CHS_dRapHi_inclu_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_CHS_dRapHi_inclu_JetP           = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_CHS_dRapHi_inclu_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapHi_inclu_JetPt          = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_CHS_dRapHi_inclu_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapHi_inclu_JetY           = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_CHS_dRapHi_inclu_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_CHS_dRapHi_inclu_JetSDmass      = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_CHS_dRapHi_inclu_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_CHS_dRapHi_inclu_JetTau32       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_CHS_dRapHi_inclu_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_CHS_dRapHi_inclu_maxbdisc       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_CHS_dRapHi_inclu_maxbdisc"     , "",  200, 0,     1);
 
  // -- dRapLo
  // - 0btag
  PredictedDistribution * predDist_CHS_dRapLo_0btag_DijetMass      = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_CHS_dRapLo_0btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapLo_0btag_DijetMassMod   = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_CHS_dRapLo_0btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapLo_0btag_HT             = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_CHS_dRapLo_0btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_CHS_dRapLo_0btag_DeltaRap       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_CHS_dRapLo_0btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_CHS_dRapLo_0btag_JetP           = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_CHS_dRapLo_0btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapLo_0btag_JetPt          = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_CHS_dRapLo_0btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapLo_0btag_JetY           = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_CHS_dRapLo_0btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_CHS_dRapLo_0btag_JetSDmass      = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_CHS_dRapLo_0btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_CHS_dRapLo_0btag_JetTau32       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_CHS_dRapLo_0btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_CHS_dRapLo_0btag_maxbdisc       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_CHS_dRapLo_0btag_maxbdisc"     , "",  200, 0,     1);
  // - 1btag
  PredictedDistribution * predDist_CHS_dRapLo_1btag_DijetMass      = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_CHS_dRapLo_1btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapLo_1btag_DijetMassMod   = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_CHS_dRapLo_1btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapLo_1btag_HT             = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_CHS_dRapLo_1btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_CHS_dRapLo_1btag_DeltaRap       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_CHS_dRapLo_1btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_CHS_dRapLo_1btag_JetP           = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_CHS_dRapLo_1btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapLo_1btag_JetPt          = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_CHS_dRapLo_1btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapLo_1btag_JetY           = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_CHS_dRapLo_1btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_CHS_dRapLo_1btag_JetSDmass      = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_CHS_dRapLo_1btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_CHS_dRapLo_1btag_JetTau32       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_CHS_dRapLo_1btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_CHS_dRapLo_1btag_maxbdisc       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_CHS_dRapLo_1btag_maxbdisc"     , "",  200, 0,     1);
  // - 2btag
  PredictedDistribution * predDist_CHS_dRapLo_2btag_DijetMass      = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_CHS_dRapLo_2btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapLo_2btag_DijetMassMod   = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_CHS_dRapLo_2btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapLo_2btag_HT             = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_CHS_dRapLo_2btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_CHS_dRapLo_2btag_DeltaRap       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_CHS_dRapLo_2btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_CHS_dRapLo_2btag_JetP           = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_CHS_dRapLo_2btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapLo_2btag_JetPt          = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_CHS_dRapLo_2btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapLo_2btag_JetY           = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_CHS_dRapLo_2btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_CHS_dRapLo_2btag_JetSDmass      = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_CHS_dRapLo_2btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_CHS_dRapLo_2btag_JetTau32       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_CHS_dRapLo_2btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_CHS_dRapLo_2btag_maxbdisc       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_CHS_dRapLo_2btag_maxbdisc"     , "",  200, 0,     1);
  // - btag inclusive
  PredictedDistribution * predDist_CHS_dRapLo_inclu_DijetMass      = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_CHS_dRapLo_inclu_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapLo_inclu_DijetMassMod   = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_CHS_dRapLo_inclu_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapLo_inclu_HT             = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_CHS_dRapLo_inclu_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_CHS_dRapLo_inclu_DeltaRap       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_CHS_dRapLo_inclu_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_CHS_dRapLo_inclu_JetP           = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_CHS_dRapLo_inclu_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapLo_inclu_JetPt          = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_CHS_dRapLo_inclu_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapLo_inclu_JetY           = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_CHS_dRapLo_inclu_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_CHS_dRapLo_inclu_JetSDmass      = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_CHS_dRapLo_inclu_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_CHS_dRapLo_inclu_JetTau32       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_CHS_dRapLo_inclu_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_CHS_dRapLo_inclu_maxbdisc       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_CHS_dRapLo_inclu_maxbdisc"     , "",  200, 0,     1);
 
  // -- dRapIn
  // - 0btag
  PredictedDistribution * predDist_CHS_dRapIn_0btag_DijetMass      = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_CHS_dRapIn_0btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapIn_0btag_DijetMassMod   = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_CHS_dRapIn_0btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapIn_0btag_HT             = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_CHS_dRapIn_0btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_CHS_dRapIn_0btag_DeltaRap       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_CHS_dRapIn_0btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_CHS_dRapIn_0btag_JetP           = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_CHS_dRapIn_0btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapIn_0btag_JetPt          = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_CHS_dRapIn_0btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapIn_0btag_JetY           = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_CHS_dRapIn_0btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_CHS_dRapIn_0btag_JetSDmass      = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_CHS_dRapIn_0btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_CHS_dRapIn_0btag_JetTau32       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_CHS_dRapIn_0btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_CHS_dRapIn_0btag_maxbdisc       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_CHS_dRapIn_0btag_maxbdisc"     , "",  200, 0,     1);
  // - 1btag
  PredictedDistribution * predDist_CHS_dRapIn_1btag_DijetMass      = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_CHS_dRapIn_1btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapIn_1btag_DijetMassMod   = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_CHS_dRapIn_1btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapIn_1btag_HT             = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_CHS_dRapIn_1btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_CHS_dRapIn_1btag_DeltaRap       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_CHS_dRapIn_1btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_CHS_dRapIn_1btag_JetP           = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_CHS_dRapIn_1btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapIn_1btag_JetPt          = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_CHS_dRapIn_1btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapIn_1btag_JetY           = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_CHS_dRapIn_1btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_CHS_dRapIn_1btag_JetSDmass      = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_CHS_dRapIn_1btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_CHS_dRapIn_1btag_JetTau32       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_CHS_dRapIn_1btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_CHS_dRapIn_1btag_maxbdisc       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_CHS_dRapIn_1btag_maxbdisc"     , "",  200, 0,     1);
  // - 2btag
  PredictedDistribution * predDist_CHS_dRapIn_2btag_DijetMass      = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_CHS_dRapIn_2btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapIn_2btag_DijetMassMod   = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_CHS_dRapIn_2btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapIn_2btag_HT             = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_CHS_dRapIn_2btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_CHS_dRapIn_2btag_DeltaRap       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_CHS_dRapIn_2btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_CHS_dRapIn_2btag_JetP           = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_CHS_dRapIn_2btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapIn_2btag_JetPt          = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_CHS_dRapIn_2btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapIn_2btag_JetY           = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_CHS_dRapIn_2btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_CHS_dRapIn_2btag_JetSDmass      = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_CHS_dRapIn_2btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_CHS_dRapIn_2btag_JetTau32       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_CHS_dRapIn_2btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_CHS_dRapIn_2btag_maxbdisc       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_CHS_dRapIn_2btag_maxbdisc"     , "",  200, 0,     1);
  // - btag inclusive
  PredictedDistribution * predDist_CHS_dRapIn_inclu_DijetMass      = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_CHS_dRapIn_inclu_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapIn_inclu_DijetMassMod   = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_CHS_dRapIn_inclu_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapIn_inclu_HT             = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_CHS_dRapIn_inclu_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_CHS_dRapIn_inclu_DeltaRap       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_CHS_dRapIn_inclu_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_CHS_dRapIn_inclu_JetP           = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_CHS_dRapIn_inclu_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapIn_inclu_JetPt          = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_CHS_dRapIn_inclu_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_CHS_dRapIn_inclu_JetY           = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_CHS_dRapIn_inclu_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_CHS_dRapIn_inclu_JetSDmass      = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_CHS_dRapIn_inclu_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_CHS_dRapIn_inclu_JetTau32       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_CHS_dRapIn_inclu_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_CHS_dRapIn_inclu_maxbdisc       = new PredictedDistribution( h_mistag_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_CHS_dRapIn_inclu_maxbdisc"     , "",  200, 0,     1);
 




  // --- Puppi
  // -- dRapHi
  // - 0btag
  PredictedDistribution * predDist_Puppi_dRapHi_0btag_DijetMass      = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_Puppi_dRapHi_0btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapHi_0btag_DijetMassMod   = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_Puppi_dRapHi_0btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapHi_0btag_HT             = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_Puppi_dRapHi_0btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_Puppi_dRapHi_0btag_DeltaRap       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_Puppi_dRapHi_0btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_Puppi_dRapHi_0btag_JetP           = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_Puppi_dRapHi_0btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapHi_0btag_JetPt          = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_Puppi_dRapHi_0btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapHi_0btag_JetY           = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_Puppi_dRapHi_0btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_Puppi_dRapHi_0btag_JetSDmass      = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_Puppi_dRapHi_0btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_Puppi_dRapHi_0btag_JetTau32       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_Puppi_dRapHi_0btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_Puppi_dRapHi_0btag_maxbdisc       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_Puppi_dRapHi_0btag_maxbdisc"     , "",  200, 0,     1);
  // - 1btag
  PredictedDistribution * predDist_Puppi_dRapHi_1btag_DijetMass      = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_Puppi_dRapHi_1btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapHi_1btag_DijetMassMod   = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_Puppi_dRapHi_1btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapHi_1btag_HT             = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_Puppi_dRapHi_1btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_Puppi_dRapHi_1btag_DeltaRap       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_Puppi_dRapHi_1btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_Puppi_dRapHi_1btag_JetP           = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_Puppi_dRapHi_1btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapHi_1btag_JetPt          = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_Puppi_dRapHi_1btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapHi_1btag_JetY           = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_Puppi_dRapHi_1btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_Puppi_dRapHi_1btag_JetSDmass      = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_Puppi_dRapHi_1btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_Puppi_dRapHi_1btag_JetTau32       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_Puppi_dRapHi_1btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_Puppi_dRapHi_1btag_maxbdisc       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_Puppi_dRapHi_1btag_maxbdisc"     , "",  200, 0,     1);
  // - 2btag
  PredictedDistribution * predDist_Puppi_dRapHi_2btag_DijetMass      = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_Puppi_dRapHi_2btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapHi_2btag_DijetMassMod   = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_Puppi_dRapHi_2btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapHi_2btag_HT             = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_Puppi_dRapHi_2btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_Puppi_dRapHi_2btag_DeltaRap       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_Puppi_dRapHi_2btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_Puppi_dRapHi_2btag_JetP           = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_Puppi_dRapHi_2btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapHi_2btag_JetPt          = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_Puppi_dRapHi_2btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapHi_2btag_JetY           = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_Puppi_dRapHi_2btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_Puppi_dRapHi_2btag_JetSDmass      = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_Puppi_dRapHi_2btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_Puppi_dRapHi_2btag_JetTau32       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_Puppi_dRapHi_2btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_Puppi_dRapHi_2btag_maxbdisc       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_Puppi_dRapHi_2btag_maxbdisc"     , "",  200, 0,     1);
  // - btag inclusive
  PredictedDistribution * predDist_Puppi_dRapHi_inclu_DijetMass      = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_Puppi_dRapHi_inclu_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapHi_inclu_DijetMassMod   = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_Puppi_dRapHi_inclu_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapHi_inclu_HT             = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_Puppi_dRapHi_inclu_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_Puppi_dRapHi_inclu_DeltaRap       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_Puppi_dRapHi_inclu_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_Puppi_dRapHi_inclu_JetP           = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_Puppi_dRapHi_inclu_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapHi_inclu_JetPt          = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_Puppi_dRapHi_inclu_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapHi_inclu_JetY           = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_Puppi_dRapHi_inclu_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_Puppi_dRapHi_inclu_JetSDmass      = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_Puppi_dRapHi_inclu_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_Puppi_dRapHi_inclu_JetTau32       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_Puppi_dRapHi_inclu_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_Puppi_dRapHi_inclu_maxbdisc       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_Puppi_dRapHi_inclu_maxbdisc"     , "",  200, 0,     1);
 
  // -- dRapLo
  // - 0btag
  PredictedDistribution * predDist_Puppi_dRapLo_0btag_DijetMass      = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_Puppi_dRapLo_0btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapLo_0btag_DijetMassMod   = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_Puppi_dRapLo_0btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapLo_0btag_HT             = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_Puppi_dRapLo_0btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_Puppi_dRapLo_0btag_DeltaRap       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_Puppi_dRapLo_0btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_Puppi_dRapLo_0btag_JetP           = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_Puppi_dRapLo_0btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapLo_0btag_JetPt          = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_Puppi_dRapLo_0btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapLo_0btag_JetY           = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_Puppi_dRapLo_0btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_Puppi_dRapLo_0btag_JetSDmass      = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_Puppi_dRapLo_0btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_Puppi_dRapLo_0btag_JetTau32       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_Puppi_dRapLo_0btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_Puppi_dRapLo_0btag_maxbdisc       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_Puppi_dRapLo_0btag_maxbdisc"     , "",  200, 0,     1);
  // - 1btag
  PredictedDistribution * predDist_Puppi_dRapLo_1btag_DijetMass      = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_Puppi_dRapLo_1btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapLo_1btag_DijetMassMod   = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_Puppi_dRapLo_1btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapLo_1btag_HT             = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_Puppi_dRapLo_1btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_Puppi_dRapLo_1btag_DeltaRap       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_Puppi_dRapLo_1btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_Puppi_dRapLo_1btag_JetP           = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_Puppi_dRapLo_1btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapLo_1btag_JetPt          = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_Puppi_dRapLo_1btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapLo_1btag_JetY           = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_Puppi_dRapLo_1btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_Puppi_dRapLo_1btag_JetSDmass      = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_Puppi_dRapLo_1btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_Puppi_dRapLo_1btag_JetTau32       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_Puppi_dRapLo_1btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_Puppi_dRapLo_1btag_maxbdisc       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_Puppi_dRapLo_1btag_maxbdisc"     , "",  200, 0,     1);
  // - 2btag
  PredictedDistribution * predDist_Puppi_dRapLo_2btag_DijetMass      = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_Puppi_dRapLo_2btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapLo_2btag_DijetMassMod   = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_Puppi_dRapLo_2btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapLo_2btag_HT             = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_Puppi_dRapLo_2btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_Puppi_dRapLo_2btag_DeltaRap       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_Puppi_dRapLo_2btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_Puppi_dRapLo_2btag_JetP           = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_Puppi_dRapLo_2btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapLo_2btag_JetPt          = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_Puppi_dRapLo_2btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapLo_2btag_JetY           = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_Puppi_dRapLo_2btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_Puppi_dRapLo_2btag_JetSDmass      = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_Puppi_dRapLo_2btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_Puppi_dRapLo_2btag_JetTau32       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_Puppi_dRapLo_2btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_Puppi_dRapLo_2btag_maxbdisc       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_Puppi_dRapLo_2btag_maxbdisc"     , "",  200, 0,     1);
  // - btag inclusive
  PredictedDistribution * predDist_Puppi_dRapLo_inclu_DijetMass      = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_Puppi_dRapLo_inclu_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapLo_inclu_DijetMassMod   = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_Puppi_dRapLo_inclu_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapLo_inclu_HT             = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_Puppi_dRapLo_inclu_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_Puppi_dRapLo_inclu_DeltaRap       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_Puppi_dRapLo_inclu_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_Puppi_dRapLo_inclu_JetP           = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_Puppi_dRapLo_inclu_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapLo_inclu_JetPt          = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_Puppi_dRapLo_inclu_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapLo_inclu_JetY           = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_Puppi_dRapLo_inclu_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_Puppi_dRapLo_inclu_JetSDmass      = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_Puppi_dRapLo_inclu_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_Puppi_dRapLo_inclu_JetTau32       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_Puppi_dRapLo_inclu_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_Puppi_dRapLo_inclu_maxbdisc       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_Puppi_dRapLo_inclu_maxbdisc"     , "",  200, 0,     1);
 
  // -- dRapIn
  // - 0btag
  PredictedDistribution * predDist_Puppi_dRapIn_0btag_DijetMass      = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_Puppi_dRapIn_0btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapIn_0btag_DijetMassMod   = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_Puppi_dRapIn_0btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapIn_0btag_HT             = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_Puppi_dRapIn_0btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_Puppi_dRapIn_0btag_DeltaRap       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_Puppi_dRapIn_0btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_Puppi_dRapIn_0btag_JetP           = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_Puppi_dRapIn_0btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapIn_0btag_JetPt          = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_Puppi_dRapIn_0btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapIn_0btag_JetY           = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_Puppi_dRapIn_0btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_Puppi_dRapIn_0btag_JetSDmass      = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_Puppi_dRapIn_0btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_Puppi_dRapIn_0btag_JetTau32       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_Puppi_dRapIn_0btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_Puppi_dRapIn_0btag_maxbdisc       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_Puppi_dRapIn_0btag_maxbdisc"     , "",  200, 0,     1);
  // - 1btag
  PredictedDistribution * predDist_Puppi_dRapIn_1btag_DijetMass      = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_Puppi_dRapIn_1btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapIn_1btag_DijetMassMod   = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_Puppi_dRapIn_1btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapIn_1btag_HT             = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_Puppi_dRapIn_1btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_Puppi_dRapIn_1btag_DeltaRap       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_Puppi_dRapIn_1btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_Puppi_dRapIn_1btag_JetP           = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_Puppi_dRapIn_1btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapIn_1btag_JetPt          = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_Puppi_dRapIn_1btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapIn_1btag_JetY           = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_Puppi_dRapIn_1btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_Puppi_dRapIn_1btag_JetSDmass      = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_Puppi_dRapIn_1btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_Puppi_dRapIn_1btag_JetTau32       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_Puppi_dRapIn_1btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_Puppi_dRapIn_1btag_maxbdisc       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_Puppi_dRapIn_1btag_maxbdisc"     , "",  200, 0,     1);
  // - 2btag
  PredictedDistribution * predDist_Puppi_dRapIn_2btag_DijetMass      = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_Puppi_dRapIn_2btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapIn_2btag_DijetMassMod   = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_Puppi_dRapIn_2btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapIn_2btag_HT             = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_Puppi_dRapIn_2btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_Puppi_dRapIn_2btag_DeltaRap       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_Puppi_dRapIn_2btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_Puppi_dRapIn_2btag_JetP           = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_Puppi_dRapIn_2btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapIn_2btag_JetPt          = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_Puppi_dRapIn_2btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapIn_2btag_JetY           = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_Puppi_dRapIn_2btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_Puppi_dRapIn_2btag_JetSDmass      = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_Puppi_dRapIn_2btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_Puppi_dRapIn_2btag_JetTau32       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_Puppi_dRapIn_2btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_Puppi_dRapIn_2btag_maxbdisc       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_Puppi_dRapIn_2btag_maxbdisc"     , "",  200, 0,     1);
  // - btag inclusive
  PredictedDistribution * predDist_Puppi_dRapIn_inclu_DijetMass      = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_Puppi_dRapIn_inclu_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapIn_inclu_DijetMassMod   = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_Puppi_dRapIn_inclu_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapIn_inclu_HT             = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_Puppi_dRapIn_inclu_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_Puppi_dRapIn_inclu_DeltaRap       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_Puppi_dRapIn_inclu_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_Puppi_dRapIn_inclu_JetP           = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_Puppi_dRapIn_inclu_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapIn_inclu_JetPt          = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_Puppi_dRapIn_inclu_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_Puppi_dRapIn_inclu_JetY           = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_Puppi_dRapIn_inclu_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_Puppi_dRapIn_inclu_JetSDmass      = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_Puppi_dRapIn_inclu_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_Puppi_dRapIn_inclu_JetTau32       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_Puppi_dRapIn_inclu_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_Puppi_dRapIn_inclu_maxbdisc       = new PredictedDistribution( h_mistag_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_Puppi_dRapIn_inclu_maxbdisc"     , "",  200, 0,     1);
 



  // --- Alternative tag definition for closur test - CHS
  // -- dRapHi
  // - 0btag
  PredictedDistribution * predDist_AltTag_dRapHi_0btag_DijetMass      = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_AltTag_dRapHi_0btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapHi_0btag_DijetMassMod   = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_AltTag_dRapHi_0btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapHi_0btag_HT             = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_AltTag_dRapHi_0btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_AltTag_dRapHi_0btag_DeltaRap       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_AltTag_dRapHi_0btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_AltTag_dRapHi_0btag_JetP           = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_AltTag_dRapHi_0btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapHi_0btag_JetPt          = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_AltTag_dRapHi_0btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapHi_0btag_JetY           = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_AltTag_dRapHi_0btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_AltTag_dRapHi_0btag_JetSDmass      = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_AltTag_dRapHi_0btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_AltTag_dRapHi_0btag_JetTau32       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_AltTag_dRapHi_0btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_AltTag_dRapHi_0btag_maxbdisc       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag     ,  "predDist_AltTag_dRapHi_0btag_maxbdisc"     , "",  200, 0,     1);
  // - 1btag
  PredictedDistribution * predDist_AltTag_dRapHi_1btag_DijetMass      = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_AltTag_dRapHi_1btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapHi_1btag_DijetMassMod   = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_AltTag_dRapHi_1btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapHi_1btag_HT             = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_AltTag_dRapHi_1btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_AltTag_dRapHi_1btag_DeltaRap       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_AltTag_dRapHi_1btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_AltTag_dRapHi_1btag_JetP           = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_AltTag_dRapHi_1btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapHi_1btag_JetPt          = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_AltTag_dRapHi_1btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapHi_1btag_JetY           = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_AltTag_dRapHi_1btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_AltTag_dRapHi_1btag_JetSDmass      = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_AltTag_dRapHi_1btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_AltTag_dRapHi_1btag_JetTau32       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_AltTag_dRapHi_1btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_AltTag_dRapHi_1btag_maxbdisc       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag     ,  "predDist_AltTag_dRapHi_1btag_maxbdisc"     , "",  200, 0,     1);
  // - 2btag
  PredictedDistribution * predDist_AltTag_dRapHi_2btag_DijetMass      = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_AltTag_dRapHi_2btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapHi_2btag_DijetMassMod   = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_AltTag_dRapHi_2btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapHi_2btag_HT             = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_AltTag_dRapHi_2btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_AltTag_dRapHi_2btag_DeltaRap       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_AltTag_dRapHi_2btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_AltTag_dRapHi_2btag_JetP           = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_AltTag_dRapHi_2btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapHi_2btag_JetPt          = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_AltTag_dRapHi_2btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapHi_2btag_JetY           = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_AltTag_dRapHi_2btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_AltTag_dRapHi_2btag_JetSDmass      = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_AltTag_dRapHi_2btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_AltTag_dRapHi_2btag_JetTau32       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_AltTag_dRapHi_2btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_AltTag_dRapHi_2btag_maxbdisc       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag     ,  "predDist_AltTag_dRapHi_2btag_maxbdisc"     , "",  200, 0,     1);
  // - btag inclusive
  PredictedDistribution * predDist_AltTag_dRapHi_inclu_DijetMass      = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_AltTag_dRapHi_inclu_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapHi_inclu_DijetMassMod   = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_AltTag_dRapHi_inclu_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapHi_inclu_HT             = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_AltTag_dRapHi_inclu_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_AltTag_dRapHi_inclu_DeltaRap       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_AltTag_dRapHi_inclu_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_AltTag_dRapHi_inclu_JetP           = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_AltTag_dRapHi_inclu_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapHi_inclu_JetPt          = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_AltTag_dRapHi_inclu_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapHi_inclu_JetY           = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_AltTag_dRapHi_inclu_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_AltTag_dRapHi_inclu_JetSDmass      = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_AltTag_dRapHi_inclu_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_AltTag_dRapHi_inclu_JetTau32       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_AltTag_dRapHi_inclu_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_AltTag_dRapHi_inclu_maxbdisc       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclu     ,  "predDist_AltTag_dRapHi_inclu_maxbdisc"     , "",  200, 0,     1);
 
  // -- dRapLo
  // - 0btag
  PredictedDistribution * predDist_AltTag_dRapLo_0btag_DijetMass      = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_AltTag_dRapLo_0btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapLo_0btag_DijetMassMod   = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_AltTag_dRapLo_0btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapLo_0btag_HT             = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_AltTag_dRapLo_0btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_AltTag_dRapLo_0btag_DeltaRap       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_AltTag_dRapLo_0btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_AltTag_dRapLo_0btag_JetP           = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_AltTag_dRapLo_0btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapLo_0btag_JetPt          = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_AltTag_dRapLo_0btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapLo_0btag_JetY           = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_AltTag_dRapLo_0btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_AltTag_dRapLo_0btag_JetSDmass      = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_AltTag_dRapLo_0btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_AltTag_dRapLo_0btag_JetTau32       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_AltTag_dRapLo_0btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_AltTag_dRapLo_0btag_maxbdisc       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag     ,  "predDist_AltTag_dRapLo_0btag_maxbdisc"     , "",  200, 0,     1);
  // - 1btag
  PredictedDistribution * predDist_AltTag_dRapLo_1btag_DijetMass      = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_AltTag_dRapLo_1btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapLo_1btag_DijetMassMod   = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_AltTag_dRapLo_1btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapLo_1btag_HT             = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_AltTag_dRapLo_1btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_AltTag_dRapLo_1btag_DeltaRap       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_AltTag_dRapLo_1btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_AltTag_dRapLo_1btag_JetP           = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_AltTag_dRapLo_1btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapLo_1btag_JetPt          = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_AltTag_dRapLo_1btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapLo_1btag_JetY           = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_AltTag_dRapLo_1btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_AltTag_dRapLo_1btag_JetSDmass      = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_AltTag_dRapLo_1btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_AltTag_dRapLo_1btag_JetTau32       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_AltTag_dRapLo_1btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_AltTag_dRapLo_1btag_maxbdisc       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag     ,  "predDist_AltTag_dRapLo_1btag_maxbdisc"     , "",  200, 0,     1);
  // - 2btag
  PredictedDistribution * predDist_AltTag_dRapLo_2btag_DijetMass      = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_AltTag_dRapLo_2btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapLo_2btag_DijetMassMod   = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_AltTag_dRapLo_2btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapLo_2btag_HT             = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_AltTag_dRapLo_2btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_AltTag_dRapLo_2btag_DeltaRap       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_AltTag_dRapLo_2btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_AltTag_dRapLo_2btag_JetP           = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_AltTag_dRapLo_2btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapLo_2btag_JetPt          = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_AltTag_dRapLo_2btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapLo_2btag_JetY           = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_AltTag_dRapLo_2btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_AltTag_dRapLo_2btag_JetSDmass      = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_AltTag_dRapLo_2btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_AltTag_dRapLo_2btag_JetTau32       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_AltTag_dRapLo_2btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_AltTag_dRapLo_2btag_maxbdisc       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag     ,  "predDist_AltTag_dRapLo_2btag_maxbdisc"     , "",  200, 0,     1);
  // - btag inclusive
  PredictedDistribution * predDist_AltTag_dRapLo_inclu_DijetMass      = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_AltTag_dRapLo_inclu_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapLo_inclu_DijetMassMod   = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_AltTag_dRapLo_inclu_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapLo_inclu_HT             = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_AltTag_dRapLo_inclu_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_AltTag_dRapLo_inclu_DeltaRap       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_AltTag_dRapLo_inclu_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_AltTag_dRapLo_inclu_JetP           = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_AltTag_dRapLo_inclu_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapLo_inclu_JetPt          = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_AltTag_dRapLo_inclu_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapLo_inclu_JetY           = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_AltTag_dRapLo_inclu_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_AltTag_dRapLo_inclu_JetSDmass      = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_AltTag_dRapLo_inclu_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_AltTag_dRapLo_inclu_JetTau32       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_AltTag_dRapLo_inclu_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_AltTag_dRapLo_inclu_maxbdisc       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclu     ,  "predDist_AltTag_dRapLo_inclu_maxbdisc"     , "",  200, 0,     1);
 
  // -- dRapIn
  // - 0btag
  PredictedDistribution * predDist_AltTag_dRapIn_0btag_DijetMass      = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_AltTag_dRapIn_0btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapIn_0btag_DijetMassMod   = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_AltTag_dRapIn_0btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapIn_0btag_HT             = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_AltTag_dRapIn_0btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_AltTag_dRapIn_0btag_DeltaRap       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_AltTag_dRapIn_0btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_AltTag_dRapIn_0btag_JetP           = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_AltTag_dRapIn_0btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapIn_0btag_JetPt          = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_AltTag_dRapIn_0btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapIn_0btag_JetY           = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_AltTag_dRapIn_0btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_AltTag_dRapIn_0btag_JetSDmass      = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_AltTag_dRapIn_0btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_AltTag_dRapIn_0btag_JetTau32       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_AltTag_dRapIn_0btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_AltTag_dRapIn_0btag_maxbdisc       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag     ,  "predDist_AltTag_dRapIn_0btag_maxbdisc"     , "",  200, 0,     1);
  // - 1btag
  PredictedDistribution * predDist_AltTag_dRapIn_1btag_DijetMass      = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_AltTag_dRapIn_1btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapIn_1btag_DijetMassMod   = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_AltTag_dRapIn_1btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapIn_1btag_HT             = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_AltTag_dRapIn_1btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_AltTag_dRapIn_1btag_DeltaRap       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_AltTag_dRapIn_1btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_AltTag_dRapIn_1btag_JetP           = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_AltTag_dRapIn_1btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapIn_1btag_JetPt          = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_AltTag_dRapIn_1btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapIn_1btag_JetY           = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_AltTag_dRapIn_1btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_AltTag_dRapIn_1btag_JetSDmass      = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_AltTag_dRapIn_1btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_AltTag_dRapIn_1btag_JetTau32       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_AltTag_dRapIn_1btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_AltTag_dRapIn_1btag_maxbdisc       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag     ,  "predDist_AltTag_dRapIn_1btag_maxbdisc"     , "",  200, 0,     1);
  // - 2btag
  PredictedDistribution * predDist_AltTag_dRapIn_2btag_DijetMass      = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_AltTag_dRapIn_2btag_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapIn_2btag_DijetMassMod   = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_AltTag_dRapIn_2btag_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapIn_2btag_HT             = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_AltTag_dRapIn_2btag_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_AltTag_dRapIn_2btag_DeltaRap       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_AltTag_dRapIn_2btag_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_AltTag_dRapIn_2btag_JetP           = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_AltTag_dRapIn_2btag_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapIn_2btag_JetPt          = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_AltTag_dRapIn_2btag_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapIn_2btag_JetY           = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_AltTag_dRapIn_2btag_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_AltTag_dRapIn_2btag_JetSDmass      = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_AltTag_dRapIn_2btag_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_AltTag_dRapIn_2btag_JetTau32       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_AltTag_dRapIn_2btag_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_AltTag_dRapIn_2btag_maxbdisc       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag     ,  "predDist_AltTag_dRapIn_2btag_maxbdisc"     , "",  200, 0,     1);
  // - btag inclusive
  PredictedDistribution * predDist_AltTag_dRapIn_inclu_DijetMass      = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_AltTag_dRapIn_inclu_DijetMass"    , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapIn_inclu_DijetMassMod   = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_AltTag_dRapIn_inclu_DijetMassMod" , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapIn_inclu_HT             = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_AltTag_dRapIn_inclu_HT"           , "", 1000, 0, 10000);
  PredictedDistribution * predDist_AltTag_dRapIn_inclu_DeltaRap       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_AltTag_dRapIn_inclu_DeltaRap"     , "",  500, 0,     5);
  PredictedDistribution * predDist_AltTag_dRapIn_inclu_JetP           = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_AltTag_dRapIn_inclu_JetP"         , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapIn_inclu_JetPt          = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_AltTag_dRapIn_inclu_JetPt"        , "",  900, 0,  9000);
  PredictedDistribution * predDist_AltTag_dRapIn_inclu_JetY           = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_AltTag_dRapIn_inclu_JetY"         , "",  300,-3,     3);
  PredictedDistribution * predDist_AltTag_dRapIn_inclu_JetSDmass      = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_AltTag_dRapIn_inclu_JetSDmass"    , "",  700, 0,   700);
  PredictedDistribution * predDist_AltTag_dRapIn_inclu_JetTau32       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_AltTag_dRapIn_inclu_JetTau32"     , "",  200, 0,     1);
  PredictedDistribution * predDist_AltTag_dRapIn_inclu_maxbdisc       = new PredictedDistribution( h_mistag_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclu     ,  "predDist_AltTag_dRapIn_inclu_maxbdisc"     , "",  200, 0,     1);
 


  cout<<"done setting up bkgdest"<<endl;

  int n_topTag0MaxBdiscM_True  = 0;
  int n_topTag0MaxBdiscM_False = 0;
  int n_topTag1MaxBdiscM_True  = 0;
  int n_topTag1MaxBdiscM_False = 0;
  int n_j0_tag_b_True  = 0;
  int n_j0_tag_b_False = 0;
  int n_j1_tag_b_True  = 0;
  int n_j1_tag_b_False = 0;

  int count_events = 0;
  int countOdd  = 0;
  int countEven = 0;

  int count_oldbtagjet0 =0;
  int count_j0_tag_b =0;
  int count_topTag1MassSDTau32=0;
  int count_newtopTag1MassSDTau32=0;

  // 8888888888                            888        888                                 
  // 888                                   888        888                                 
  // 888                                   888        888                                 
  // 8888888    888  888  .d88b.  88888b.  888888     888       .d88b.   .d88b.  88888b.  
  // 888        888  888 d8P  Y8b 888 "88b 888        888      d88""88b d88""88b 888 "88b 
  // 888        Y88  88P 88888888 888  888 888        888      888  888 888  888 888  888 
  // 888         Y8bd8P  Y8b.     888  888 Y88b.      888      Y88..88P Y88..88P 888 d88P 
  // 8888888888   Y88P    "Y8888  888  888  "Y888     88888888  "Y88P"   "Y88P"  88888P"  
  //                                                                             888      
  //                                                                             888      
  //                                                                             888      

  int nLoop = treeNentries;
  if (Nevents==-1) nLoop = treeNentries;
  else nLoop = Nevents;

  for (int i=0; i<nLoop; i++ ){ 
    if (i%10000==0) cout<<i<<"  / "<<nLoop<<"   ("<<setprecision(3)<<(float)i/(float)nLoop*100<<"%)"<<endl;

    T1->GetEntry(i);
    h_CutFlow->Fill(0);

    count_events++;
    bool evenEvent = false;
    bool oddEvent  = false;
    if (count_events % 2 == 0) evenEvent = true;
    else oddEvent = true;
    if (oddEvent)  countOdd +=1;
    if (evenEvent) countEven+=1;

    // Jet corrections
    TLorentzVector jet0P4Raw;
    TLorentzVector jet1P4Raw;
    jet0P4Raw.SetPtEtaPhiM( Jet0PtRaw, Jet0EtaRaw, Jet0PhiRaw, Jet0MassRaw);
    jet1P4Raw.SetPtEtaPhiM( Jet1PtRaw, Jet1EtaRaw, Jet1PhiRaw, Jet1MassRaw);

    TLorentzVector puppi0P4Raw;
    TLorentzVector puppi1P4Raw;
    puppi0P4Raw.SetPtEtaPhiM( Jet0PuppiPt, Jet0PuppiEta, Jet0PuppiPhi, Jet0PuppiMass);
    puppi1P4Raw.SetPtEtaPhiM( Jet1PuppiPt, Jet1PuppiEta, Jet1PuppiPhi, Jet1PuppiMass);

    double jet0_jec_corr                = 1.0; 
    double jet1_jec_corr                = 1.0; 
    double jet0_jec_groomedmass_corr    = 1.0; 
    double jet1_jec_groomedmass_corr    = 1.0; 
    double jet0_ptsmear                 = 1.0; 
    double jet1_ptsmear                 = 1.0; 
    double puppi0_jec_corr              = 1.0; 
    double puppi1_jec_corr              = 1.0; 
    double puppi0_jec_groomedmass_corr  = 1.0; 
    double puppi1_jec_groomedmass_corr  = 1.0; 
    double puppi0_ptsmear               = 1.0; 
    double puppi1_ptsmear               = 1.0; 

    double ht = 0;
    double evWeight = 1.0;


    if (isData){ 
      jet0_jec_corr               = Jet0CorrFactor     ;
      jet1_jec_corr               = Jet1CorrFactor     ; 
      jet0_jec_groomedmass_corr   = Jet0MassCorrFactor ;
      jet1_jec_groomedmass_corr   = Jet1MassCorrFactor ;
      
      puppi0_jec_corr             = Jet0PuppiCorrFactor;
      puppi1_jec_corr             = Jet1PuppiCorrFactor; 
      puppi0_jec_groomedmass_corr = Jet0PuppiCorrFactor;
      puppi1_jec_groomedmass_corr = Jet1PuppiCorrFactor;

      ht = HT;
    }

    if (!isData){ 
      //nom, pdf_up, pdf_dn, q2_up, q2_dn, pu_up, pu_dn
      if (Syst == 0 || fabs(Syst) == 4 || fabs(Syst) == 5 || fabs(Syst) == 6){
        jet0_ptsmear                = Jet0PtSmearFactor  ;
        jet1_ptsmear                = Jet1PtSmearFactor  ;
        jet0_jec_corr               = Jet0CorrFactor     ;
        jet1_jec_corr               = Jet1CorrFactor     ; 
        jet0_jec_groomedmass_corr   = Jet0MassCorrFactor ;
        jet1_jec_groomedmass_corr   = Jet1MassCorrFactor ;

        puppi0_ptsmear              = Jet0PuppiPtSmearFactor ;
        puppi1_ptsmear              = Jet1PuppiPtSmearFactor ;
        puppi0_jec_corr             = Jet0PuppiCorrFactor    ;
        puppi1_jec_corr             = Jet1PuppiCorrFactor    ; 
        puppi0_jec_groomedmass_corr = Jet0MassCorrFactor     ;
        puppi1_jec_groomedmass_corr = Jet1MassCorrFactor     ;

        ht = HT_PtSmearNom;
      }
      // jec_up
      if (Syst == 1 ){
        jet0_ptsmear                = Jet0PtSmearFactor       ;
        jet1_ptsmear                = Jet1PtSmearFactor       ;
        jet0_jec_corr               = Jet0CorrFactorUp        ;
        jet1_jec_corr               = Jet1CorrFactorUp        ; 
        jet0_jec_groomedmass_corr   = Jet0MassCorrFactorUp    ;
        jet1_jec_groomedmass_corr   = Jet1MassCorrFactorUp    ;

        puppi0_ptsmear              = Jet0PuppiPtSmearFactor  ;
        puppi1_ptsmear              = Jet1PuppiPtSmearFactor  ;
        puppi0_jec_corr             = Jet0PuppiCorrFactorUp   ;
        puppi1_jec_corr             = Jet1PuppiCorrFactorUp   ; 
        puppi0_jec_groomedmass_corr = Jet0PuppiCorrFactorUp   ;
        puppi1_jec_groomedmass_corr = Jet1PuppiCorrFactorUp   ;

        ht = HT_CorrUp;
      }
      // jec_dn
      if (Syst == -1 ){
        jet0_ptsmear                = Jet0PtSmearFactor       ;
        jet1_ptsmear                = Jet1PtSmearFactor       ;
        jet0_jec_corr               = Jet0CorrFactorDn        ;
        jet1_jec_corr               = Jet1CorrFactorDn        ; 
        jet0_jec_groomedmass_corr   = Jet0MassCorrFactorDn    ;
        jet1_jec_groomedmass_corr   = Jet1MassCorrFactorDn    ;

        puppi0_ptsmear              = Jet0PuppiPtSmearFactor  ;
        puppi1_ptsmear              = Jet1PuppiPtSmearFactor  ;
        puppi0_jec_corr             = Jet0PuppiCorrFactorDn   ;
        puppi1_jec_corr             = Jet1PuppiCorrFactorDn   ; 
        puppi0_jec_groomedmass_corr = Jet0PuppiCorrFactorDn   ;
        puppi1_jec_groomedmass_corr = Jet1PuppiCorrFactorDn   ;

        ht = HT_CorrDn;
      }
      // jer_up
      if (Syst == 2 ){
        jet0_ptsmear                = Jet0PtSmearFactorUp      ;
        jet1_ptsmear                = Jet1PtSmearFactorUp      ;
        jet0_jec_corr               = Jet0CorrFactor           ;
        jet1_jec_corr               = Jet1CorrFactor           ; 
        jet0_jec_groomedmass_corr   = Jet0MassCorrFactor       ;
        jet1_jec_groomedmass_corr   = Jet1MassCorrFactor       ;

        puppi0_ptsmear              = Jet0PuppiPtSmearFactorUp ;
        puppi1_ptsmear              = Jet1PuppiPtSmearFactorUp ;
        puppi0_jec_corr             = Jet0PuppiCorrFactor      ;
        puppi1_jec_corr             = Jet1PuppiCorrFactor      ; 
        puppi0_jec_groomedmass_corr = Jet0MassCorrFactor       ;
        puppi1_jec_groomedmass_corr = Jet1MassCorrFactor       ;

        ht = HT_PtSmearUp;
      }
      // jer_dn
      if (Syst == -2 ){
        jet0_ptsmear                = Jet0PtSmearFactorDn      ;
        jet1_ptsmear                = Jet1PtSmearFactorDn      ;
        jet0_jec_corr               = Jet0CorrFactor           ;
        jet1_jec_corr               = Jet1CorrFactor           ; 
        jet0_jec_groomedmass_corr   = Jet0MassCorrFactor       ;
        jet1_jec_groomedmass_corr   = Jet1MassCorrFactor       ;

        puppi0_ptsmear              = Jet0PuppiPtSmearFactorDn ;
        puppi1_ptsmear              = Jet1PuppiPtSmearFactorDn ;
        puppi0_jec_corr             = Jet0PuppiCorrFactor      ;
        puppi1_jec_corr             = Jet1PuppiCorrFactor      ; 
        puppi0_jec_groomedmass_corr = Jet0MassCorrFactor       ;
        puppi1_jec_groomedmass_corr = Jet1MassCorrFactor       ;

        ht = HT_PtSmearDn;
      }

      // PU reweighting
      if (!do_PUreweighting) evWeight = 1;
      else{
        evWeight = AllHadPUweight;
        if (Syst == 6) evWeight = AllHadPUweight_MBup;
        if (Syst ==-6) evWeight = AllHadPUweight_MBdn;
      }

      //pdf, Q^2, and pileup systematics (MC Only)
      if (Syst == 4)       evWeight *= NNPDF3weight_CorrUp ;
      else if (Syst == -4) evWeight *= NNPDF3weight_CorrDn ;
      else if (Syst == 5)  evWeight *= Q2weight_CorrUp     ;
      else if (Syst == -5) evWeight *= Q2weight_CorrDn     ;
      
    }

    // Jet variables (fully corrected)
    TLorentzVector jet0P4 = jet0P4Raw * jet0_jec_corr * jet0_ptsmear ;
    TLorentzVector jet1P4 = jet1P4Raw * jet1_jec_corr * jet1_ptsmear ;

    TLorentzVector puppi0P4 = puppi0P4Raw * puppi0_jec_corr * puppi0_ptsmear;
    TLorentzVector puppi1P4 = puppi1P4Raw * puppi1_jec_corr * puppi1_ptsmear;

    TLorentzVector dijetP4 = jet0P4+jet1P4;

    double jet0pt = jet0P4.Perp();
    double jet1pt = jet1P4.Perp();
    double jet0P  = jet0P4.P();
    double jet1P  = jet1P4.P();
    double jet0sdmass = Jet0SDmassRaw * jet0_jec_groomedmass_corr * puppi0_ptsmear;
    double jet1sdmass = Jet1SDmassRaw * jet1_jec_groomedmass_corr * puppi1_ptsmear;
    double jet0sdpt   = Jet0SDptRaw   * jet0_jec_groomedmass_corr * puppi0_ptsmear;
    double jet1sdpt   = Jet0SDptRaw   * jet1_jec_groomedmass_corr * puppi1_ptsmear;

    double puppi0pt     = puppi0P4.Perp();
    double puppi1pt     = puppi1P4.Perp();
    double puppi0P      = puppi0P4.P();
    double puppi1P      = puppi1P4.P();
    double puppi0sdmass = Jet0PuppiSDmass * puppi0_jec_groomedmass_corr * puppi0_ptsmear;
    double puppi1sdmass = Jet1PuppiSDmass * puppi1_jec_groomedmass_corr * puppi1_ptsmear;
    double puppi0sdpt   = Jet0PuppiSDpt   * puppi0_jec_groomedmass_corr * puppi0_ptsmear;
    double puppi1sdpt   = Jet1PuppiSDpt   * puppi1_jec_groomedmass_corr * puppi1_ptsmear;

    //---- Pre-selection ------------------------
    if (jet0pt < minAK8Pt || jet1pt < minAK8Pt) continue;   h_CutFlow->Fill(1);
    if (ht < minHT) continue;                               h_CutFlow->Fill(2);
    if (fabs(DijetDeltaPhi)<2.1) continue;                  h_CutFlow->Fill(3);
    // Reject noise events
    if (PassMETFilters==0) continue;                        h_CutFlow->Fill(4);

    //---- do b-tagging ------------------------

    // Of the 2 subjets, find the pt and eta of the one that has the max b-discriminant Use these values to calculate the SF.
    bool j0_chs_subjet0_isMax = false;
    bool j0_chs_subjet1_isMax = false;
    bool j0_pup_subjet0_isMax = false;
    bool j0_pup_subjet1_isMax = false;
    bool j1_chs_subjet0_isMax = false;
    bool j1_chs_subjet1_isMax = false;
    bool j1_pup_subjet0_isMax = false;
    bool j1_pup_subjet1_isMax = false;  

    double j0_chs_maxbtag_subjet_pt = 0;
    double j1_chs_maxbtag_subjet_pt = 0;
    double j0_pup_maxbtag_subjet_pt = 0;
    double j1_pup_maxbtag_subjet_pt = 0;
      
    double j0_chs_maxbtag_subjet_eta = 0;
    double j1_chs_maxbtag_subjet_eta = 0;
    double j0_pup_maxbtag_subjet_eta = 0;
    double j1_pup_maxbtag_subjet_eta = 0;
           
    if      ( ( Jet0SDmaxbdisc - Jet0SDsubjet0bdisc               ) <0.0001 ) { j0_chs_subjet0_isMax = true; j0_chs_maxbtag_subjet_pt = Jet0SDsubjet0pt      ;  j0_chs_maxbtag_subjet_eta = Jet0SDsubjet0eta          ;}
    else if ( ( Jet0SDmaxbdisc - Jet0SDsubjet1bdisc               ) <0.0001 ) { j0_chs_subjet1_isMax = true; j0_chs_maxbtag_subjet_pt = Jet0SDsubjet1pt      ;  j0_chs_maxbtag_subjet_eta = Jet0SDsubjet1eta          ;}
    else cout<<"CHECK THIS"<<endl;

    if      ( ( Jet0PuppiSDmaxbdisc - Jet0PuppiSDsubjet0bdisc     ) <0.0001 ) { j0_pup_subjet0_isMax = true; j0_pup_maxbtag_subjet_pt = Jet0PuppiSDsubjet0pt ;  j0_pup_maxbtag_subjet_eta = Jet0PuppiSDsubjet0eta     ;}
    else if ( ( Jet0PuppiSDmaxbdisc - Jet0PuppiSDsubjet1bdisc     ) <0.0001 ) { j0_pup_subjet1_isMax = true; j0_pup_maxbtag_subjet_pt = Jet0PuppiSDsubjet1pt ;  j0_pup_maxbtag_subjet_eta = Jet0PuppiSDsubjet1eta     ;}
    else cout<<"CHECK THIS"<<endl;

    if      ( ( Jet1SDmaxbdisc - Jet1SDsubjet0bdisc               ) <0.0001 ) { j1_chs_subjet0_isMax = true; j1_chs_maxbtag_subjet_pt = Jet1SDsubjet0pt      ;  j1_chs_maxbtag_subjet_eta = Jet1SDsubjet0eta          ;}
    else if ( ( Jet1SDmaxbdisc - Jet1SDsubjet1bdisc               ) <0.0001 ) { j1_chs_subjet1_isMax = true; j1_chs_maxbtag_subjet_pt = Jet1SDsubjet1pt      ;  j1_chs_maxbtag_subjet_eta = Jet1SDsubjet1eta          ;}
    else cout<<"CHECK THIS"<<endl;

    if      ( ( Jet1PuppiSDmaxbdisc - Jet1PuppiSDsubjet0bdisc     ) <0.0001 ) { j1_pup_subjet0_isMax = true; j1_pup_maxbtag_subjet_pt = Jet1PuppiSDsubjet0pt ;  j1_pup_maxbtag_subjet_eta = Jet1PuppiSDsubjet0eta     ;}
    else if ( ( Jet1PuppiSDmaxbdisc - Jet1PuppiSDsubjet1bdisc     ) <0.0001 ) { j1_pup_subjet1_isMax = true; j1_pup_maxbtag_subjet_pt = Jet1PuppiSDsubjet1pt ;  j1_pup_maxbtag_subjet_eta = Jet1PuppiSDsubjet1eta     ;}
    else cout<<"CHECK THIS"<<endl;


    if (verbose_){
      cout<<" Jet0SDsubjet0bdisc    "<<Jet0SDsubjet0bdisc<<endl;
      cout<<" Jet0SDsubjet1bdisc    "<<Jet0SDsubjet1bdisc<<endl;
      cout<<" Jet0SDmaxbdisc        "<<Jet0SDmaxbdisc    <<endl;
      cout<<" j0_chs_subjet0_isMax  "<<j0_chs_subjet0_isMax    <<endl;
      cout<<" j0_chs_subjet1_isMax  "<<j0_chs_subjet1_isMax    <<endl;
    }
    // btag SF
    double j0_chs_maxbtag_subjet_scalefactor = 1.0;
    double j0_pup_maxbtag_subjet_scalefactor = 1.0;
    double j1_chs_maxbtag_subjet_scalefactor = 1.0;
    double j1_pup_maxbtag_subjet_scalefactor = 1.0;

    if (!isData){

      if (Syst ==  3) {
        j0_chs_maxbtag_subjet_scalefactor = reader.eval_auto_bounds( "up"     , BTagEntry::FLAV_B, j0_chs_maxbtag_subjet_eta    , j0_chs_maxbtag_subjet_pt      );
        j0_pup_maxbtag_subjet_scalefactor = reader.eval_auto_bounds( "up"     , BTagEntry::FLAV_B, j0_pup_maxbtag_subjet_eta    , j0_pup_maxbtag_subjet_pt      ); 
        j1_chs_maxbtag_subjet_scalefactor = reader.eval_auto_bounds( "up"     , BTagEntry::FLAV_B, j1_chs_maxbtag_subjet_eta    , j1_chs_maxbtag_subjet_pt      );
        j1_pup_maxbtag_subjet_scalefactor = reader.eval_auto_bounds( "up"     , BTagEntry::FLAV_B, j1_pup_maxbtag_subjet_eta    , j1_pup_maxbtag_subjet_pt      );
      }
      else if (Syst == -3) {
        j0_chs_maxbtag_subjet_scalefactor = reader.eval_auto_bounds( "down"   , BTagEntry::FLAV_B, j0_chs_maxbtag_subjet_eta    , j0_chs_maxbtag_subjet_pt      );
        j0_pup_maxbtag_subjet_scalefactor = reader.eval_auto_bounds( "down"   , BTagEntry::FLAV_B, j0_pup_maxbtag_subjet_eta    , j0_pup_maxbtag_subjet_pt      ); 
        j1_chs_maxbtag_subjet_scalefactor = reader.eval_auto_bounds( "down"   , BTagEntry::FLAV_B, j1_chs_maxbtag_subjet_eta    , j1_chs_maxbtag_subjet_pt      );
        j1_pup_maxbtag_subjet_scalefactor = reader.eval_auto_bounds( "down"   , BTagEntry::FLAV_B, j1_pup_maxbtag_subjet_eta    , j1_pup_maxbtag_subjet_pt      );
      }
      else{
        j0_chs_maxbtag_subjet_scalefactor = reader.eval_auto_bounds( "central" , BTagEntry::FLAV_B, j0_chs_maxbtag_subjet_eta    , j0_chs_maxbtag_subjet_pt      );
        j0_pup_maxbtag_subjet_scalefactor = reader.eval_auto_bounds( "central" , BTagEntry::FLAV_B, j0_pup_maxbtag_subjet_eta    , j0_pup_maxbtag_subjet_pt      ); 
        j1_chs_maxbtag_subjet_scalefactor = reader.eval_auto_bounds( "central" , BTagEntry::FLAV_B, j1_chs_maxbtag_subjet_eta    , j1_chs_maxbtag_subjet_pt      );
        j1_pup_maxbtag_subjet_scalefactor = reader.eval_auto_bounds( "central" , BTagEntry::FLAV_B, j1_pup_maxbtag_subjet_eta    , j1_pup_maxbtag_subjet_pt      );
      }
    }
    if(verbose_){
      cout<<"j0_chs_subjet0_btag_scalefactor "<<j0_chs_maxbtag_subjet_scalefactor<<endl;
      cout<<"j1_chs_subjet1_btag_scalefactor "<<j1_chs_maxbtag_subjet_scalefactor<<endl;
      cout<<"j0_pup_subjet0_btag_scalefactor "<<j0_pup_maxbtag_subjet_scalefactor<<endl;
      cout<<"j1_pup_subjet1_btag_scalefactor "<<j1_pup_maxbtag_subjet_scalefactor<<endl;
    }
    // btag bool
    bool j0_tag_b_noSF     = Jet0SDmaxbdisc      > 0.8;
    bool j1_tag_b_noSF     = Jet1SDmaxbdisc      > 0.8;
    bool j0_puptag_b_noSF  = Jet0PuppiSDmaxbdisc > 0.8;
    bool j1_puptag_b_noSF  = Jet1PuppiSDmaxbdisc > 0.8;

    double Btag_eff = 0.69;// temporary!

    bool j0_tag_b    = false;
    bool j1_tag_b    = false;
    bool j0_puptag_b = false;
    bool j1_puptag_b = false;

    j0_tag_b    =  bool( applySF ( j0_tag_b_noSF    , j0_chs_maxbtag_subjet_scalefactor , Btag_eff) );
    j1_tag_b    =  bool( applySF ( j1_tag_b_noSF    , j1_chs_maxbtag_subjet_scalefactor , Btag_eff) );
    j0_puptag_b =  bool( applySF ( j0_puptag_b_noSF , j0_pup_maxbtag_subjet_scalefactor , Btag_eff) );
    j1_puptag_b =  bool( applySF ( j1_puptag_b_noSF , j1_pup_maxbtag_subjet_scalefactor , Btag_eff) );
     
    if ( !j0_tag_b_noSF && !j1_tag_b_noSF  )                                     h_BtagCategoriesPreSF   ->Fill(0);
    if ( (!j0_tag_b_noSF && j1_tag_b_noSF)||(j0_tag_b_noSF && !j1_tag_b_noSF)  ) h_BtagCategoriesPreSF   ->Fill(1);
    if ( j0_tag_b_noSF && j1_tag_b_noSF  )                                       h_BtagCategoriesPreSF   ->Fill(2);
    
    if ( !j0_tag_b && !j1_tag_b  )                           h_BtagCategoriesPostSF   ->Fill(0);
    if ( (!j0_tag_b && j1_tag_b)||(j0_tag_b && !j1_tag_b)  ) h_BtagCategoriesPostSF   ->Fill(1);
    if ( j0_tag_b && j1_tag_b  )                             h_BtagCategoriesPostSF   ->Fill(2);

    if(verbose_){
      cout<<"chs jet 0 btag scale - bool before/after = "<< j0_tag_b_noSF    <<" / "<< j0_tag_b    <<endl;
      cout<<"chs jet 0 btag scale - bool before/after = "<< j1_tag_b_noSF    <<" / "<< j1_tag_b    <<endl;
      cout<<"pup jet 0 btag scale - bool before/after = "<< j0_puptag_b_noSF <<" / "<< j0_puptag_b <<endl;
      cout<<"pup jet 0 btag scale - bool before/after = "<< j1_puptag_b_noSF <<" / "<< j1_puptag_b <<endl;
    }

    //---- do t-tagging ------------------------

    // Top-tagging bools
    bool j0_ungroomedtag_mass  = jet0P4.M() > topTagSDwindowLo && jet0P4.M() < topTagSDwindowHi;
    bool j1_ungroomedtag_mass  = jet1P4.M() > topTagSDwindowLo && jet1P4.M() < topTagSDwindowHi;

    bool j0_tag_mass  = jet0sdmass > topTagSDwindowLo && jet0sdmass < topTagSDwindowHi;
    bool j1_tag_mass  = jet1sdmass > topTagSDwindowLo && jet1sdmass < topTagSDwindowHi;
    bool j0_tag_tau32 = Jet0Tau32 < topTagTau32cut;
    bool j1_tag_tau32 = Jet1Tau32 < topTagTau32cut;
    bool j0_tag_t     = j0_tag_mass && j0_tag_tau32;
    bool j1_tag_t     = j1_tag_mass && j1_tag_tau32;
    bool j0_tag_t_b   = j0_tag_t && j0_tag_b ;
    bool j1_tag_t_b   = j1_tag_t && j1_tag_b ;

    bool j0_puptag_mass  = puppi0sdmass > topTagSDwindowLo && puppi0sdmass < topTagSDwindowHi;
    bool j1_puptag_mass  = puppi1sdmass > topTagSDwindowLo && puppi1sdmass < topTagSDwindowHi;
    bool j0_puptag_tau32 = Jet0PuppiTau32 < topTagTau32cut;
    bool j1_puptag_tau32 = Jet1PuppiTau32 < topTagTau32cut;
    bool j0_puptag_t     = j0_puptag_mass && j0_puptag_tau32;
    bool j1_puptag_t     = j1_puptag_mass && j1_puptag_tau32;
    bool j0_puptag_t_b   = j0_puptag_t && j0_puptag_b ;
    bool j1_puptag_t_b   = j1_puptag_t && j1_puptag_b ;
    
    bool double_tag_t                    = j0_tag_t && j1_tag_t ;           
    bool double_tag_t_b                  = j0_tag_t_b && j1_tag_t_b ;           
    bool double_tag_t_single_tag_b       = double_tag_t && ( (j0_tag_b && !j1_tag_b) || (!j0_tag_b && j1_tag_b) )  ;           
    bool double_tag_t_no_b               = double_tag_t && !j0_tag_b && !j1_tag_b ;           

    bool double_puptag_t                 = j0_puptag_t && j1_puptag_t ;           
    bool double_puptag_t_b               = j0_puptag_t_b && j1_puptag_t_b ;           
    bool double_puptag_t_single_puptag_b = double_puptag_t && ( (j0_puptag_b && !j1_puptag_b) || (!j0_puptag_b && j1_puptag_b) )  ;           
    bool double_puptag_t_no_b            = double_puptag_t && !j0_puptag_b && !j1_puptag_b ;           

    // anti-tag
    bool j0_antitag_tau32           = Jet0Tau32 > topTagTau32cut;
    bool j1_antitag_tau32           = Jet1Tau32 > topTagTau32cut;
    bool j0_antitag_tau32_tag_mass  = j0_antitag_tau32 && j0_tag_mass ;
    bool j1_antitag_tau32_tag_mass  = j1_antitag_tau32 && j1_tag_mass ;
  
    bool j0_antipuptag_tau32              = Jet0PuppiTau32 > topTagTau32cut;
    bool j1_antipuptag_tau32              = Jet1PuppiTau32 > topTagTau32cut;
    bool j0_antipuptag_tau32_puptag_mass  = j0_antipuptag_tau32 && j0_puptag_mass ;
    bool j1_antipuptag_tau32_puptag_mass  = j1_antipuptag_tau32 && j1_puptag_mass ;
  
    // Alternative tag and antitag definitions for closure test
    bool j0_tag_alt_mass  = (jet0sdmass > 90 && jet0sdmass < 110) || (jet0sdmass > 210 && jet0sdmass < 300)  ;
    bool j1_tag_alt_mass  = (jet1sdmass > 90 && jet1sdmass < 110) || (jet1sdmass > 210 && jet1sdmass < 300)  ;
    bool j0_tag_alt_t     = j0_tag_alt_mass && j0_tag_tau32;
    bool j1_tag_alt_t     = j1_tag_alt_mass && j1_tag_tau32;
    bool j0_antitag_tau32_tag_alt_mass  = j0_antitag_tau32 && j0_tag_alt_mass ;
    bool j1_antitag_tau32_tag_alt_mass  = j1_antitag_tau32 && j1_tag_alt_mass ;



    //        d8888          888    d8b        888                           .d8888b.         8888888b.                   888               
    //       d88888          888    Y8P        888                          d88P  "88b        888   Y88b                  888               
    //      d88P888          888               888                          Y88b. d88P        888    888                  888               
    //     d88P 888 88888b.  888888 888        888888  8888b.   .d88b.       "Y8888P"         888   d88P 888d888  .d88b.  88888b.   .d88b.  
    //    d88P  888 888 "88b 888    888        888        "88b d88P"88b     .d88P88K.d88P     8888888P"  888P"   d88""88b 888 "88b d8P  Y8b 
    //   d88P   888 888  888 888    888 888888 888    .d888888 888  888     888"  Y888P"      888        888     888  888 888  888 88888888 
    //  d8888888888 888  888 Y88b.  888        Y88b.  888  888 Y88b 888     Y88b .d8888b      888        888     Y88..88P 888 d88P Y8b.     
    // d88P     888 888  888  "Y888 888         "Y888 "Y888888  "Y88888      "Y8888P" Y88b    888        888      "Y88P"  88888P"   "Y8888  
    //                                                              888                                                                     
    //                                                         Y8b d88P                                                                     
    //                                                          "Y88P"                                                                      

    if (run_antitag){
      TRandom3 rand1(0);
      double rand_mistag  = rand1.Uniform(0,1.0);
      // Primary tag definition - anti-tag and probe
      if (rand_mistag < 0.5){    // 50% of the time choose jet 0 to be the anti-tag and jet 1 to be the probe
      
        //---------- (CHS JETS) - anti-tag tau32, keep jet in SD mass window 
        if (j0_antitag_tau32_tag_mass){

          h_AntiTagCHS_Probe_jetP_dRapIn_inclusive                             ->Fill( jet1P       , evWeight ); 
          if (j1_tag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclusive     ->Fill( jet1P       , evWeight );
          if (DijetDeltaRap<=1.0){
            h_AntiTagCHS_Probe_jetP_dRapLo_inclusive                           ->Fill( jet1P       , evWeight );
            if (j1_tag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclusive   ->Fill( jet1P       , evWeight );
          }
          if (DijetDeltaRap>1.0){
            h_AntiTagCHS_Probe_jetP_dRapHi_inclusive                           ->Fill( jet1P       , evWeight );
            if (j1_tag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclusive   ->Fill( jet1P       , evWeight );
          }
                   
          if (j0_tag_b && j1_tag_b){
            h_AntiTagCHS_Probe_jetP_dRapIn_2btag                             ->Fill( jet1P       , evWeight );
            if (j1_tag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag     ->Fill( jet1P       , evWeight );
            if (DijetDeltaRap<=1.0){
              h_AntiTagCHS_Probe_jetP_dRapLo_2btag                           ->Fill( jet1P       , evWeight );
              if (j1_tag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag   ->Fill( jet1P       , evWeight );
            }
            if (DijetDeltaRap>1.0){
              h_AntiTagCHS_Probe_jetP_dRapHi_2btag                           ->Fill( jet1P       , evWeight );
              if (j1_tag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag   ->Fill( jet1P       , evWeight );
            }
          }
          if ( (j0_tag_b && !j1_tag_b) || (j1_tag_b && !j0_tag_b) ){
            h_AntiTagCHS_Probe_jetP_dRapIn_1btag                             ->Fill( jet1P       , evWeight );
            if (j1_tag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag     ->Fill( jet1P       , evWeight );
            if (DijetDeltaRap<=1.0){
              h_AntiTagCHS_Probe_jetP_dRapLo_1btag                           ->Fill( jet1P       , evWeight );
              if (j1_tag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag   ->Fill( jet1P       , evWeight );
            }
            if (DijetDeltaRap>1.0){
              h_AntiTagCHS_Probe_jetP_dRapHi_1btag                           ->Fill( jet1P       , evWeight );
              if (j1_tag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag   ->Fill( jet1P       , evWeight );
            }
          }
          if (!j0_tag_b && ! j1_tag_b){
            h_AntiTagCHS_Probe_jetP_dRapIn_0btag                             ->Fill( jet1P       , evWeight );
            if (j1_tag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag     ->Fill( jet1P       , evWeight );
            if (DijetDeltaRap<=1.0){
              h_AntiTagCHS_Probe_jetP_dRapLo_0btag                           ->Fill( jet1P       , evWeight );
              if (j1_tag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag   ->Fill( jet1P       , evWeight );
            }
            if (DijetDeltaRap>1.0){
              h_AntiTagCHS_Probe_jetP_dRapHi_0btag                           ->Fill( jet1P       , evWeight );
              if (j1_tag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag   ->Fill( jet1P       , evWeight );
            }
          }
        }

        //---------- (PUPPI JETS) - anti-tag tau32, keep jet in SD mass window 
        if (j0_antipuptag_tau32_puptag_mass){
          
          // btag inclusive
          h_AntiTagPuppi_Probe_jetP_dRapIn_inclusive                                ->Fill( jet1P       , evWeight ); 
          if (j1_puptag_t)    h_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_inclusive   ->Fill( jet1P       , evWeight );
          if (DijetDeltaRap<=1.0){
            h_AntiTagPuppi_Probe_jetP_dRapLo_inclusive                              ->Fill( jet1P       , evWeight );
            if (j1_puptag_t)  h_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_inclusive   ->Fill( jet1P       , evWeight );
          }
          if (DijetDeltaRap>1.0){
            h_AntiTagPuppi_Probe_jetP_dRapHi_inclusive                              ->Fill( jet1P       , evWeight );
            if (j1_puptag_t)  h_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_inclusive   ->Fill( jet1P       , evWeight );
          }

          // 2 btag        
          if (j0_puptag_b && j1_puptag_b){
            h_AntiTagPuppi_Probe_jetP_dRapIn_2btag                                  ->Fill( jet1P       , evWeight );
            if (j1_puptag_t)  h_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_2btag       ->Fill( jet1P       , evWeight );
            if (DijetDeltaRap<=1.0){
              h_AntiTagPuppi_Probe_jetP_dRapLo_2btag                                ->Fill( jet1P       , evWeight );
              if (j1_puptag_t)  h_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_2btag     ->Fill( jet1P       , evWeight );
            }
            if (DijetDeltaRap>1.0){
              h_AntiTagPuppi_Probe_jetP_dRapHi_2btag                                ->Fill( jet1P       , evWeight );
              if (j1_puptag_t)  h_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_2btag     ->Fill( jet1P       , evWeight );
            }
          }
          
          // 1 btag
          if ( (j0_puptag_b && !j1_puptag_b) || (j1_puptag_b && !j0_puptag_b) ){
            h_AntiTagPuppi_Probe_jetP_dRapIn_1btag                                  ->Fill( jet1P       , evWeight );
            if (j1_puptag_t)  h_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_1btag       ->Fill( jet1P       , evWeight );
            if (DijetDeltaRap<=1.0){
              h_AntiTagPuppi_Probe_jetP_dRapLo_1btag                                ->Fill( jet1P       , evWeight );
              if (j1_puptag_t)  h_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_1btag     ->Fill( jet1P       , evWeight );
            }
            if (DijetDeltaRap>1.0){
              h_AntiTagPuppi_Probe_jetP_dRapHi_1btag                                ->Fill( jet1P       , evWeight );
              if (j1_puptag_t)  h_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_1btag     ->Fill( jet1P       , evWeight );
            }
          }
         
          // 0 btag
          if (!j0_puptag_b && ! j1_puptag_b){
            h_AntiTagPuppi_Probe_jetP_dRapIn_0btag                                  ->Fill( jet1P       , evWeight );
            if (j1_puptag_t)  h_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_0btag       ->Fill( jet1P       , evWeight );
            if (DijetDeltaRap<=1.0){
              h_AntiTagPuppi_Probe_jetP_dRapLo_0btag                                ->Fill( jet1P       , evWeight );
              if (j1_puptag_t)  h_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_0btag     ->Fill( jet1P       , evWeight );
            }
            if (DijetDeltaRap>1.0){
              h_AntiTagPuppi_Probe_jetP_dRapHi_0btag                                ->Fill( jet1P       , evWeight );
              if (j1_puptag_t)  h_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_0btag     ->Fill( jet1P       , evWeight );
            }
          }
        }


        // Experiment with some alterntive anti-tag definitions
        if ( jet0sdmass > 40 && jet0sdmass < 60 && j0_antitag_tau32 ){
          h_AntiTagCHS40to60_Probe_jetP_dRapIn_inclusive                              ->Fill( jet1P       , evWeight ); 
          if (j1_tag_t)  h_AntiTagCHS40to60_TagMassSDTau32_jetP_dRapIn_inclusive      ->Fill( jet1P       , evWeight );
        }
        if ( jet0sdmass > 60 && jet0sdmass < 80 && j0_antitag_tau32 ){
          h_AntiTagCHS60to80_Probe_jetP_dRapIn_inclusive                              ->Fill( jet1P       , evWeight ); 
          if (j1_tag_t)  h_AntiTagCHS60to80_TagMassSDTau32_jetP_dRapIn_inclusive      ->Fill( jet1P       , evWeight );
        }
        if ( jet0sdmass > 80 && jet0sdmass < 100 && j0_antitag_tau32 ){
          h_AntiTagCHS80to110_Probe_jetP_dRapIn_inclusive                             ->Fill( jet1P       , evWeight ); 
          if (j1_tag_t)  h_AntiTagCHS80to110_TagMassSDTau32_jetP_dRapIn_inclusive     ->Fill( jet1P       , evWeight );
        }
        if ( jet0sdmass > 100 && jet0sdmass < 120 && j0_antitag_tau32 ){
          h_AntiTagCHS100to120_Probe_jetP_dRapIn_inclusive                            ->Fill( jet1P       , evWeight ); 
          if (j1_tag_t)  h_AntiTagCHS100to120_TagMassSDTau32_jetP_dRapIn_inclusive    ->Fill( jet1P       , evWeight );
        }
        if ( jet0sdmass > 120 && jet0sdmass < 140 && j0_antitag_tau32 ){
          h_AntiTagCHS120to140_Probe_jetP_dRapIn_inclusive                            ->Fill( jet1P       , evWeight ); 
          if (j1_tag_t)  h_AntiTagCHS120to140_TagMassSDTau32_jetP_dRapIn_inclusive    ->Fill( jet1P       , evWeight );
        }
        if ( jet0sdmass > 140 && jet0sdmass < 180 && j0_antitag_tau32 ){
          h_AntiTagCHS140to180_Probe_jetP_dRapIn_inclusive                            ->Fill( jet1P       , evWeight ); 
          if (j1_tag_t)  h_AntiTagCHS140to180_TagMassSDTau32_jetP_dRapIn_inclusive    ->Fill( jet1P       , evWeight );
        }
        if ( jet0sdmass > 180 && jet0sdmass < 220 && j0_antitag_tau32 ){
          h_AntiTagCHS180to220_Probe_jetP_dRapIn_inclusive                            ->Fill( jet1P       , evWeight ); 
          if (j1_tag_t)  h_AntiTagCHS180to220_TagMassSDTau32_jetP_dRapIn_inclusive    ->Fill( jet1P       , evWeight );
        }
        if ( jet0sdmass > 220 && jet0sdmass < 300 && j0_antitag_tau32 ){
          h_AntiTagCHS220to300_Probe_jetP_dRapIn_inclusive                            ->Fill( jet1P       , evWeight ); 
          if (j1_tag_t)  h_AntiTagCHS220to300_TagMassSDTau32_jetP_dRapIn_inclusive    ->Fill( jet1P       , evWeight );
        }

      }
      else if ( rand_mistag >= 0.5 ){  // 50% of the time choose jet 1 to be the anti-tag and jet 0 to be the probe
        
        //---------- (CHS jets) anti-tag tau32, keep jet in SD mass window
        if (j1_antitag_tau32_tag_mass){
          h_AntiTagCHS_Probe_jetP_dRapIn_inclusive                             ->Fill( jet0P       , evWeight );
          if (j0_tag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclusive     ->Fill( jet0P       , evWeight );
          if (DijetDeltaRap<=1.0){
            h_AntiTagCHS_Probe_jetP_dRapLo_inclusive                           ->Fill( jet0P       , evWeight );
            if (j0_tag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclusive   ->Fill( jet0P       , evWeight );
          }
          if (DijetDeltaRap>1.0){
            h_AntiTagCHS_Probe_jetP_dRapHi_inclusive                           ->Fill( jet0P       , evWeight );
            if (j0_tag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclusive   ->Fill( jet0P       , evWeight );
          }
                   
          if (j0_tag_b && j1_tag_b){
            h_AntiTagCHS_Probe_jetP_dRapIn_2btag                                ->Fill( jet0P       , evWeight );
            if (j0_tag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag        ->Fill( jet0P       , evWeight );
            if (DijetDeltaRap<=1.0){
              h_AntiTagCHS_Probe_jetP_dRapLo_2btag                              ->Fill( jet0P       , evWeight );
              if (j0_tag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag      ->Fill( jet0P       , evWeight );
            }
            if (DijetDeltaRap>1.0){
              h_AntiTagCHS_Probe_jetP_dRapHi_2btag                              ->Fill( jet0P       , evWeight );
              if (j0_tag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag      ->Fill( jet0P       , evWeight );
            }
          }
          if ( (j0_tag_b && !j1_tag_b) || (j1_tag_b && !j0_tag_b) ){
            h_AntiTagCHS_Probe_jetP_dRapIn_1btag                                ->Fill( jet0P       , evWeight );
            if (j0_tag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag        ->Fill( jet0P       , evWeight );
            if (DijetDeltaRap<=1.0){
              h_AntiTagCHS_Probe_jetP_dRapLo_1btag                              ->Fill( jet0P       , evWeight );
              if (j0_tag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag      ->Fill( jet0P       , evWeight );
            }
            if (DijetDeltaRap>1.0){
              h_AntiTagCHS_Probe_jetP_dRapHi_1btag                              ->Fill( jet0P       , evWeight );
              if (j0_tag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag      ->Fill( jet0P       , evWeight );
            }
          }
          if (!j0_tag_b && ! j1_tag_b){
            h_AntiTagCHS_Probe_jetP_dRapIn_0btag                                ->Fill( jet0P       , evWeight );
            if (j0_tag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag        ->Fill( jet0P       , evWeight );
            if (DijetDeltaRap<=1.0){
              h_AntiTagCHS_Probe_jetP_dRapLo_0btag                              ->Fill( jet0P       , evWeight );
              if (j0_tag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag      ->Fill( jet0P       , evWeight );
            }
            if (DijetDeltaRap>1.0){
              h_AntiTagCHS_Probe_jetP_dRapHi_0btag                              ->Fill( jet0P       , evWeight );
              if (j0_tag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag      ->Fill( jet0P       , evWeight );
            }
          }
        }

        //---------- (PUPPI jets) anti-puptag tau32, keep jet in SD mass window
        if (j1_antipuptag_tau32_puptag_mass){
          h_AntiTagCHS_Probe_jetP_dRapIn_inclusive                                ->Fill( jet0P       , evWeight );
          if (j0_puptag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclusive     ->Fill( jet0P       , evWeight );
          if (DijetDeltaRap<=1.0){
            h_AntiTagCHS_Probe_jetP_dRapLo_inclusive                              ->Fill( jet0P       , evWeight );
            if (j0_puptag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclusive   ->Fill( jet0P       , evWeight );
          }
          if (DijetDeltaRap>1.0){
            h_AntiTagCHS_Probe_jetP_dRapHi_inclusive                              ->Fill( jet0P       , evWeight );
            if (j0_puptag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclusive   ->Fill( jet0P       , evWeight );
          }
                   
          if (j0_puptag_b && j1_puptag_b){
            h_AntiTagCHS_Probe_jetP_dRapIn_2btag                                  ->Fill( jet0P       , evWeight );
            if (j0_puptag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag       ->Fill( jet0P       , evWeight );
            if (DijetDeltaRap<=1.0){
              h_AntiTagCHS_Probe_jetP_dRapLo_2btag                                ->Fill( jet0P       , evWeight );
              if (j0_puptag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag     ->Fill( jet0P       , evWeight );
            }
            if (DijetDeltaRap>1.0){
              h_AntiTagCHS_Probe_jetP_dRapHi_2btag                                ->Fill( jet0P       , evWeight );
              if (j0_puptag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag     ->Fill( jet0P       , evWeight );
            }
          }
          if ( (j0_puptag_b && !j1_puptag_b) || (j1_puptag_b && !j0_puptag_b) ){
            h_AntiTagCHS_Probe_jetP_dRapIn_1btag                                  ->Fill( jet0P       , evWeight );
            if (j0_puptag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag       ->Fill( jet0P       , evWeight );
            if (DijetDeltaRap<=1.0){
              h_AntiTagCHS_Probe_jetP_dRapLo_1btag                                ->Fill( jet0P       , evWeight );
              if (j0_puptag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag     ->Fill( jet0P       , evWeight );
            }
            if (DijetDeltaRap>1.0){
              h_AntiTagCHS_Probe_jetP_dRapHi_1btag                                ->Fill( jet0P       , evWeight );
              if (j0_puptag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag     ->Fill( jet0P       , evWeight );
            }
          }
          if (!j0_puptag_b && ! j1_puptag_b){
            h_AntiTagCHS_Probe_jetP_dRapIn_0btag                                  ->Fill( jet0P       , evWeight );
            if (j0_puptag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag       ->Fill( jet0P       , evWeight );
            if (DijetDeltaRap<=1.0){
              h_AntiTagCHS_Probe_jetP_dRapLo_0btag                                ->Fill( jet0P       , evWeight );
              if (j0_puptag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag     ->Fill( jet0P       , evWeight );
            }
            if (DijetDeltaRap>1.0){
              h_AntiTagCHS_Probe_jetP_dRapHi_0btag                                ->Fill( jet0P       , evWeight );
              if (j0_puptag_t)  h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag     ->Fill( jet0P       , evWeight );
            }
          }
        }
        // Experiment with some alterntive anti-tag definitions
        if ( jet1sdmass > 40 && jet1sdmass < 60 && j1_antitag_tau32 ){
          h_AntiTagCHS40to60_Probe_jetP_dRapIn_inclusive                              ->Fill( jet0P       , evWeight ); 
          if (j0_tag_t)  h_AntiTagCHS40to60_TagMassSDTau32_jetP_dRapIn_inclusive      ->Fill( jet0P       , evWeight );
        }
        if ( jet1sdmass > 60 && jet1sdmass < 80 && j1_antitag_tau32 ){
          h_AntiTagCHS60to80_Probe_jetP_dRapIn_inclusive                              ->Fill( jet0P       , evWeight ); 
          if (j0_tag_t)  h_AntiTagCHS60to80_TagMassSDTau32_jetP_dRapIn_inclusive      ->Fill( jet0P       , evWeight );
        }
        if ( jet1sdmass > 80 && jet1sdmass < 100 && j1_antitag_tau32 ){
          h_AntiTagCHS80to110_Probe_jetP_dRapIn_inclusive                             ->Fill( jet0P       , evWeight ); 
          if (j0_tag_t)  h_AntiTagCHS80to110_TagMassSDTau32_jetP_dRapIn_inclusive     ->Fill( jet0P       , evWeight );
        }
        if ( jet1sdmass > 100 && jet1sdmass < 120 && j1_antitag_tau32 ){
          h_AntiTagCHS100to120_Probe_jetP_dRapIn_inclusive                            ->Fill( jet0P       , evWeight ); 
          if (j0_tag_t)  h_AntiTagCHS100to120_TagMassSDTau32_jetP_dRapIn_inclusive    ->Fill( jet0P       , evWeight );
        }
        if ( jet1sdmass > 120 && jet1sdmass < 140 && j1_antitag_tau32 ){
          h_AntiTagCHS120to140_Probe_jetP_dRapIn_inclusive                            ->Fill( jet0P       , evWeight ); 
          if (j0_tag_t)  h_AntiTagCHS120to140_TagMassSDTau32_jetP_dRapIn_inclusive    ->Fill( jet0P       , evWeight );
        }
        if ( jet1sdmass > 140 && jet1sdmass < 180 && j1_antitag_tau32 ){
          h_AntiTagCHS140to180_Probe_jetP_dRapIn_inclusive                            ->Fill( jet0P       , evWeight ); 
          if (j0_tag_t)  h_AntiTagCHS140to180_TagMassSDTau32_jetP_dRapIn_inclusive    ->Fill( jet0P       , evWeight );
        }
        if ( jet1sdmass > 180 && jet1sdmass < 220 && j1_antitag_tau32 ){
          h_AntiTagCHS180to220_Probe_jetP_dRapIn_inclusive                            ->Fill( jet0P       , evWeight ); 
          if (j0_tag_t)  h_AntiTagCHS180to220_TagMassSDTau32_jetP_dRapIn_inclusive    ->Fill( jet0P       , evWeight );
        }
        if ( jet1sdmass > 220 && jet1sdmass < 300 && j1_antitag_tau32 ){
          h_AntiTagCHS220to300_Probe_jetP_dRapIn_inclusive                            ->Fill( jet0P       , evWeight ); 
          if (j0_tag_t)  h_AntiTagCHS220to300_TagMassSDTau32_jetP_dRapIn_inclusive    ->Fill( jet0P       , evWeight );
        }
      }
      
      // Alternative tag definition for closure test - anti-tag and probe
      if (rand_mistag < 0.5){    // 50% of the time choose jet 0 to be the anti-tag and jet 1 to be the probe
      
        //----------anti-tag tau32, keep jet in SD mass window
        if (j0_antitag_tau32_tag_alt_mass){

          h_alt_AntiTagCHS_Probe_jetP_dRapIn_inclusive                                  ->Fill( jet1P       , evWeight ); 
          if (j1_tag_alt_t)  h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclusive     ->Fill( jet1P       , evWeight );
          if (DijetDeltaRap<=1.0){
            h_alt_AntiTagCHS_Probe_jetP_dRapLo_inclusive                                ->Fill( jet1P       , evWeight );
            if (j1_tag_alt_t)  h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclusive   ->Fill( jet1P       , evWeight );
          }
          if (DijetDeltaRap>1.0){
            h_alt_AntiTagCHS_Probe_jetP_dRapHi_inclusive                                ->Fill( jet1P       , evWeight );
            if (j1_tag_alt_t)  h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclusive   ->Fill( jet1P       , evWeight );
          }
                   
          if (j0_tag_b && j1_tag_b){
            h_alt_AntiTagCHS_Probe_jetP_dRapIn_2btag                                    ->Fill( jet1P       , evWeight );
            if (j1_tag_alt_t)  h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag       ->Fill( jet1P       , evWeight );
            if (DijetDeltaRap<=1.0){
              h_alt_AntiTagCHS_Probe_jetP_dRapLo_2btag                                  ->Fill( jet1P       , evWeight );
              if (j1_tag_alt_t)  h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag     ->Fill( jet1P       , evWeight );
            }
            if (DijetDeltaRap>1.0){
              h_alt_AntiTagCHS_Probe_jetP_dRapHi_2btag                                  ->Fill( jet1P       , evWeight );
              if (j1_tag_alt_t)  h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag     ->Fill( jet1P       , evWeight );
            }
          }
          if ( (j0_tag_b && !j1_tag_b) || (j1_tag_b && !j0_tag_b) ){
            h_alt_AntiTagCHS_Probe_jetP_dRapIn_1btag                                    ->Fill( jet1P       , evWeight );
            if (j1_tag_alt_t)  h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag       ->Fill( jet1P       , evWeight );
            if (DijetDeltaRap<=1.0){
              h_alt_AntiTagCHS_Probe_jetP_dRapLo_1btag                                  ->Fill( jet1P       , evWeight );
              if (j1_tag_alt_t)  h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag     ->Fill( jet1P       , evWeight );
            }
            if (DijetDeltaRap>1.0){
              h_alt_AntiTagCHS_Probe_jetP_dRapHi_1btag                                  ->Fill( jet1P       , evWeight );
              if (j1_tag_alt_t)  h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag     ->Fill( jet1P       , evWeight );
            }
          }
          if (!j0_tag_b && ! j1_tag_b){
            h_alt_AntiTagCHS_Probe_jetP_dRapIn_0btag                                    ->Fill( jet1P       , evWeight );
            if (j1_tag_alt_t)  h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag       ->Fill( jet1P       , evWeight );
            if (DijetDeltaRap<=1.0){
              h_alt_AntiTagCHS_Probe_jetP_dRapLo_0btag                                  ->Fill( jet1P       , evWeight );
              if (j1_tag_alt_t)  h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag     ->Fill( jet1P       , evWeight );
            }
            if (DijetDeltaRap>1.0){
              h_alt_AntiTagCHS_Probe_jetP_dRapHi_0btag                                  ->Fill( jet1P       , evWeight );
              if (j1_tag_alt_t)  h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag     ->Fill( jet1P        , evWeight );
            }
          }
        }
      }
      else if ( rand_mistag >= 0.5 ){  // 50% of the time choose jet 1 to be the anti-tag and jet 0 to be the probe
        //----------anti-tag tau32, keep jet in SD mass window
        if (j1_antitag_tau32_tag_alt_mass){
          h_alt_AntiTagCHS_Probe_jetP_dRapIn_inclusive                                  ->Fill( jet0P       , evWeight );
          if (j0_tag_alt_t)  h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclusive     ->Fill( jet0P       , evWeight );
          if (DijetDeltaRap<=1.0){
            h_alt_AntiTagCHS_Probe_jetP_dRapLo_inclusive                                ->Fill( jet0P       , evWeight );
            if (j0_tag_alt_t)  h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclusive   ->Fill( jet0P       , evWeight );
          }
          if (DijetDeltaRap>1.0){
            h_alt_AntiTagCHS_Probe_jetP_dRapHi_inclusive                                ->Fill( jet0P       , evWeight );
            if (j0_tag_alt_t)  h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclusive   ->Fill( jet0P       , evWeight );
          }
                   
          if (j0_tag_b && j1_tag_b){
            h_alt_AntiTagCHS_Probe_jetP_dRapIn_2btag                                    ->Fill( jet0P       , evWeight );
            if (j0_tag_alt_t)  h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag       ->Fill( jet0P       , evWeight );
            if (DijetDeltaRap<=1.0){
              h_alt_AntiTagCHS_Probe_jetP_dRapLo_2btag                                  ->Fill( jet0P       , evWeight );
              if (j0_tag_alt_t)  h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag     ->Fill( jet0P       , evWeight );
            }
            if (DijetDeltaRap>1.0){
              h_alt_AntiTagCHS_Probe_jetP_dRapHi_2btag                                  ->Fill( jet0P       , evWeight );
              if (j0_tag_alt_t)  h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag     ->Fill( jet0P       , evWeight );
            }
          }
          if ( (j0_tag_b && !j1_tag_b) || (j1_tag_b && !j0_tag_b) ){
            h_alt_AntiTagCHS_Probe_jetP_dRapIn_1btag                                    ->Fill( jet0P       , evWeight );
            if (j0_tag_alt_t)  h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag       ->Fill( jet0P       , evWeight );
            if (DijetDeltaRap<=1.0){
              h_alt_AntiTagCHS_Probe_jetP_dRapLo_1btag                                  ->Fill( jet0P       , evWeight );
              if (j0_tag_alt_t)  h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag     ->Fill( jet0P       , evWeight );
            }
            if (DijetDeltaRap>1.0){
              h_alt_AntiTagCHS_Probe_jetP_dRapHi_1btag                                  ->Fill( jet0P       , evWeight );
              if (j0_tag_alt_t)  h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag     ->Fill( jet0P       , evWeight );
            }
          }
          if (!j0_tag_b && ! j1_tag_b){
            h_alt_AntiTagCHS_Probe_jetP_dRapIn_0btag                                    ->Fill( jet0P       , evWeight );
            if (j0_tag_alt_t)  h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag       ->Fill( jet0P       , evWeight );
            if (DijetDeltaRap<=1.0){
              h_alt_AntiTagCHS_Probe_jetP_dRapLo_0btag                                  ->Fill( jet0P       , evWeight );
              if (j0_tag_alt_t)  h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag     ->Fill( jet0P       , evWeight );
            }
            if (DijetDeltaRap>1.0){
              h_alt_AntiTagCHS_Probe_jetP_dRapHi_0btag                                  ->Fill( jet0P       , evWeight );
              if (j0_tag_alt_t)  h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag     ->Fill( jet0P       , evWeight );
            }
          }
        }
      }

      //Fill QCD MC distributions for modmass procedure
      if (isQCDMC){
        //Ungroomed
        if (j0_ungroomedtag_mass){
          h_mAK8_ModMass_jet0 -> Fill( jet0P4.M() , evWeight );
          h_mAK8_ModMass      -> Fill( jet0P4.M() , evWeight );
        }
        if (j1_ungroomedtag_mass){
          h_mAK8_ModMass_jet1 -> Fill( jet1P4.M() , evWeight );
          h_mAK8_ModMass      -> Fill( jet1P4.M() , evWeight );
        }
        //Soft Drop
        if (j0_tag_mass){
          h_mSDropAK8_ModMass_jet0 -> Fill( jet0sdmass, evWeight );
          h_mSDropAK8_ModMass      -> Fill( jet0sdmass, evWeight );
        }
        if (j1_tag_mass){
          h_mSDropAK8_ModMass_jet1 -> Fill( jet1sdmass, evWeight );
          h_mSDropAK8_ModMass      -> Fill( jet1sdmass, evWeight );
        }
        //PUPPI Soft Drop
        if (j0_puptag_mass){
          h_mPuppiSDropAK8_ModMass_jet0 -> Fill( puppi0sdmass , evWeight );
          h_mPuppiSDropAK8_ModMass      -> Fill( puppi0sdmass, evWeight );
        }
        if (j1_puptag_mass){
          h_mPuppiSDropAK8_ModMass_jet1 -> Fill( puppi1sdmass, evWeight );
          h_mPuppiSDropAK8_ModMass      -> Fill( puppi1sdmass, evWeight );
        }
        // Alternative tag for closure test
        if (j0_tag_alt_mass){
          h_mSDropAK8_ModMass_jet0 -> Fill( jet0sdmass, evWeight );
          h_mSDropAK8_ModMass      -> Fill( jet0sdmass, evWeight );
        }
        if (j1_tag_alt_mass){
          h_mSDropAK8_ModMass_jet1 -> Fill( jet1sdmass, evWeight );
          h_mSDropAK8_ModMass      -> Fill( jet1sdmass, evWeight );
        }
      }
    }// end if antitag
    


    // 888    d8P  d8b                                          888    d8b                       888          888             
    // 888   d8P   Y8P                                          888    Y8P                       888          888             
    // 888  d8P                                                 888                              888          888             
    // 888d88K     888 88888b.   .d88b.  88888b.d88b.   8888b.  888888 888  .d8888b     88888b.  888  .d88b.  888888 .d8888b  
    // 8888888b    888 888 "88b d8P  Y8b 888 "888 "88b     "88b 888    888 d88P"        888 "88b 888 d88""88b 888    88K      
    // 888  Y88b   888 888  888 88888888 888  888  888 .d888888 888    888 888          888  888 888 888  888 888    "Y8888b. 
    // 888   Y88b  888 888  888 Y8b.     888  888  888 888  888 Y88b.  888 Y88b.        888 d88P 888 Y88..88P Y88b.       X88 
    // 888    Y88b 888 888  888  "Y8888  888  888  888 "Y888888  "Y888 888  "Y8888P     88888P"  888  "Y88P"   "Y888  88888P' 
    //                                                                                  888                                   
    //                                                                                  888                                   
    //                                                                                  888                                   

    float dijetMass = (jet0P4 + jet1P4).M();

    if (run_kinematic){
      h_DijetMass_dRapIn                         ->Fill( DijetMass                , evWeight );
      if (DijetDeltaRap  <1) h_DijetMass_dRapLo  ->Fill( DijetMass                , evWeight );
      if (DijetDeltaRap >=1) h_DijetMass_dRapHi  ->Fill( DijetMass                , evWeight );                           
                   
      h_EventWeight                              ->Fill( evWeight                            );         
      h_DeltaRap                                 ->Fill( DijetDeltaRap            , evWeight );         
      h_DeltaPhi                                 ->Fill( DijetDeltaPhi            , evWeight );        
      h_HT                                       ->Fill( ht                       , evWeight );   
      h_MET                                      ->Fill( AllHadMETpt              , evWeight );   
      h_METphi                                   ->Fill( AllHadMETphi             , evWeight );   
      h_Nvtx                                     ->Fill( AllHadNvtx               , evWeight );   
      h_Jet0P                                    ->Fill( jet0P                    , evWeight );          
      h_Jet0Pt                                   ->Fill( jet0pt                   , evWeight );          
      h_Jet0Phi                                  ->Fill( jet0P4.Phi()             , evWeight );          
      h_Jet0Rap                                  ->Fill( jet0P4.Rapidity()        , evWeight );          
      h_Jet0sdmass                               ->Fill( jet0sdmass               , evWeight );          
      h_Jet0Tau1                                 ->Fill( Jet0Tau1                 , evWeight );          
      h_Jet0Tau2                                 ->Fill( Jet0Tau2                 , evWeight );          
      h_Jet0Tau3                                 ->Fill( Jet0Tau3                 , evWeight );          
      h_Jet0Tau4                                 ->Fill( Jet0Tau4                 , evWeight );                                 
      h_Jet0SDmaxbdisc                           ->Fill( Jet0SDmaxbdisc           , evWeight );        
      h_Jet0SDsubjet0pt                          ->Fill( Jet0SDsubjet0pt          , evWeight );          
      h_Jet0SDsubjet0mass                        ->Fill( Jet0SDsubjet0mass        , evWeight );                   
      h_Jet0SDsubjet0tau1                        ->Fill( Jet0SDsubjet0tau1        , evWeight );          
      h_Jet0SDsubjet0tau2                        ->Fill( Jet0SDsubjet0tau2        , evWeight );          
      h_Jet0SDsubjet0tau3                        ->Fill( Jet0SDsubjet0tau3        , evWeight );          
      h_Jet0SDsubjet0bdisc                       ->Fill( Jet0SDsubjet0bdisc       , evWeight );          
      h_Jet0SDsubjet1pt                          ->Fill( Jet0SDsubjet1pt          , evWeight );          
      h_Jet0SDsubjet1mass                        ->Fill( Jet0SDsubjet1mass        , evWeight );                                     
      h_Jet0SDsubjet1tau1                        ->Fill( Jet0SDsubjet1tau1        , evWeight );          
      h_Jet0SDsubjet1tau2                        ->Fill( Jet0SDsubjet1tau2        , evWeight );          
      h_Jet0SDsubjet1tau3                        ->Fill( Jet0SDsubjet1tau3        , evWeight );          
      h_Jet0SDsubjet1bdisc                       ->Fill( Jet0SDsubjet1bdisc       , evWeight );          
      h_Jet0PuppiPt                              ->Fill( puppi0pt                 , evWeight );                                
      h_Jet0PuppiMass                            ->Fill( puppi0P4.M()             , evWeight );                         
      h_Jet0PuppiSDpt                            ->Fill( jet0sdpt                 , evWeight );                              
      h_Jet0PuppiTau1                            ->Fill( Jet0PuppiTau1            , evWeight );          
      h_Jet0PuppiTau2                            ->Fill( Jet0PuppiTau2            , evWeight );          
      h_Jet0PuppiTau3                            ->Fill( Jet0PuppiTau3            , evWeight );          
      h_Jet0PuppiTau4                            ->Fill( Jet0PuppiTau4            , evWeight );                              
      h_Jet0PuppiSDmaxbdisc                      ->Fill( Jet0PuppiSDmaxbdisc      , evWeight );             
      h_Jet0PuppiSDsubjet0pt                     ->Fill( Jet0PuppiSDsubjet0pt     , evWeight );          
      h_Jet0PuppiSDsubjet0mass                   ->Fill( Jet0PuppiSDsubjet0mass   , evWeight );          
      h_Jet0PuppiSDsubjet0tau1                   ->Fill( Jet0PuppiSDsubjet0tau1   , evWeight );          
      h_Jet0PuppiSDsubjet0tau2                   ->Fill( Jet0PuppiSDsubjet0tau2   , evWeight );          
      h_Jet0PuppiSDsubjet0tau3                   ->Fill( Jet0PuppiSDsubjet0tau3   , evWeight );          
      h_Jet0PuppiSDsubjet0bdisc                  ->Fill( Jet0PuppiSDsubjet0bdisc  , evWeight );          
      h_Jet0PuppiSDsubjet1pt                     ->Fill( Jet0PuppiSDsubjet1pt     , evWeight );          
      h_Jet0PuppiSDsubjet1mass                   ->Fill( Jet0PuppiSDsubjet1mass   , evWeight );          
      h_Jet0PuppiSDsubjet1tau1                   ->Fill( Jet0PuppiSDsubjet1tau1   , evWeight );          
      h_Jet0PuppiSDsubjet1tau2                   ->Fill( Jet0PuppiSDsubjet1tau2   , evWeight );          
      h_Jet0PuppiSDsubjet1tau3                   ->Fill( Jet0PuppiSDsubjet1tau3   , evWeight );          
      h_Jet0PuppiSDsubjet1bdisc                  ->Fill( Jet0PuppiSDsubjet1bdisc  , evWeight );
      h_Jet0CHF                                  ->Fill( Jet0CHF                  , evWeight );          
      h_Jet0NHF                                  ->Fill( Jet0NHF                  , evWeight );          
      h_Jet0CM                                   ->Fill( Jet0CM                   , evWeight );          
      h_Jet0NM                                   ->Fill( Jet0NM                   , evWeight );          
      h_Jet0NEF                                  ->Fill( Jet0NEF                  , evWeight );          
      h_Jet0CEF                                  ->Fill( Jet0CEF                  , evWeight );          
      h_Jet0MF                                   ->Fill( Jet0MF                   , evWeight );          
      h_Jet0Mult                                 ->Fill( Jet0Mult                 , evWeight );          
      h_Jet0PuppiCHF                             ->Fill( Jet0PuppiCHF             , evWeight );          
      h_Jet0PuppiNHF                             ->Fill( Jet0PuppiNHF             , evWeight );          
      h_Jet0PuppiCM                              ->Fill( Jet0PuppiCM              , evWeight );          
      h_Jet0PuppiNM                              ->Fill( Jet0PuppiNM              , evWeight );          
      h_Jet0PuppiNEF                             ->Fill( Jet0PuppiNEF             , evWeight );          
      h_Jet0PuppiCEF                             ->Fill( Jet0PuppiCEF             , evWeight );          
      h_Jet0PuppiMF                              ->Fill( Jet0PuppiMF              , evWeight );          
      h_Jet0PuppiMult                            ->Fill( Jet0PuppiMult            , evWeight );          



      h_Jet1Pt                                   ->Fill( Jet1Pt                   , evWeight );          
      h_Jet1Rap                                  ->Fill( Jet1Rap                   , evWeight );          


      h_runNumber_Jet0CHF    -> Fill(AllHadRunNum, Jet0CHF        , evWeight);
      h_runNumber_Jet0NHF    -> Fill(AllHadRunNum, Jet0NHF        , evWeight);
      h_runNumber_Jet0CM     -> Fill(AllHadRunNum, Jet0CM         , evWeight);
      h_runNumber_Jet0NM     -> Fill(AllHadRunNum, Jet0NM         , evWeight);
      h_runNumber_Jet0NEF    -> Fill(AllHadRunNum, Jet0NEF        , evWeight);
      h_runNumber_Jet0CEF    -> Fill(AllHadRunNum, Jet0CEF        , evWeight);
      h_runNumber_Jet0MF     -> Fill(AllHadRunNum, Jet0MF         , evWeight);
      h_runNumber_Jet0Mult   -> Fill(AllHadRunNum, Jet0Mult       , evWeight);
      h_runNumber_NvtxGood   -> Fill(AllHadRunNum, AllHadNvtxGood , evWeight);
      h_runNumber_Jet0Pt     -> Fill(AllHadRunNum, Jet0Pt         , evWeight);
      h_runNumber_Jet0SDmass -> Fill(AllHadRunNum, Jet0SDmass     , evWeight);
     
      h_runNumber_DijetMass  -> Fill(AllHadRunNum, DijetMass      , evWeight);
      h_runNumber_HT         -> Fill(AllHadRunNum, HT             , evWeight);

      h_Jet0Pt_Jet0Mass                     ->Fill( jet0P4.Perp()     ,       jet0P4.M() , evWeight );
      h_Jet0P_Jet0Mass                      ->Fill( jet0P4.P()        ,       jet0P4.M() , evWeight );
      h_Jet0Pt_Jet0SDmass                   ->Fill( jet0P4.Perp()     ,       Jet0SDmass , evWeight );
      h_Jet0P_Jet0SDmass                    ->Fill( jet0P4.P()        ,       Jet0SDmass , evWeight );
      h_Jet0Y_Jet0Mass                      ->Fill( jet0P4.Rapidity() ,       jet0P4.M() , evWeight );
      h_Jet0Y_Jet0Mass_Pt500to520           ->Fill( jet0P4.Rapidity() ,       jet0P4.M() , evWeight );
      h_Jet0Y_Jet0SDmass                    ->Fill( jet0P4.Rapidity() ,       Jet0SDmass , evWeight );
      h_Jet0Y_Jet0SDmass_Pt500to520         ->Fill( jet0P4.Rapidity() ,       Jet0SDmass , evWeight );
      h_Jet0Y_Jet1Y                         ->Fill( jet0P4.Rapidity() ,jet1P4.Rapidity() , evWeight );
      h_Jet0Y_Jet1Y_Pt500to520              ->Fill( jet0P4.Rapidity() ,jet1P4.Rapidity() , evWeight );


      double jet0_rhoRatio                 =  log( jet0sdmass * jet0sdmass / ( jet0P4.Perp() * jet0P4.Perp() ) );
      double jet0_rhoRatioPrime            =  log( jet0sdmass * jet0sdmass / ( jet0P4.Perp()                 ) );
      double jet0_rhoRatioPmag             =  log( jet0sdmass * jet0sdmass / ( jet0P4.P()    * jet0P4.P()    ) );
      double jet0_rhoRatioPmagPrime        =  log( jet0sdmass * jet0sdmass / ( jet0P4.P()                    ) );
  
      double jet0_rhoRatioPuppi            =  log( puppi0sdmass * puppi0sdmass / (puppi0P4.Perp() * puppi0P4.Perp() ) );
      double jet0_rhoRatioPuppiPrime       =  log( puppi0sdmass * puppi0sdmass / (puppi0P4.Perp()                   ) );
      double jet0_rhoRatioPuppiPmag        =  log( puppi0sdmass * puppi0sdmass / (puppi0P4.P()    * puppi0P4.P()    ) );
      double jet0_rhoRatioPuppiPmagPrime   =  log( puppi0sdmass * puppi0sdmass / (puppi0P4.P()                      ) );
  
      double jet1_rhoRatio                 =  log( jet1sdmass * jet1sdmass / ( jet1P4.Perp() * jet1P4.Perp() ) );
      double jet1_rhoRatioPrime            =  log( jet1sdmass * jet1sdmass / ( jet1P4.Perp()                 ) );
      double jet1_rhoRatioPmag             =  log( jet1sdmass * jet1sdmass / ( jet1P4.P()    * jet1P4.P()    ) );
      double jet1_rhoRatioPmagPrime        =  log( jet1sdmass * jet1sdmass / ( jet1P4.P()                    ) );
  
      double jet1_rhoRatioPuppi            =  log( puppi1sdmass * puppi1sdmass / ( puppi1P4.Perp() * puppi1P4.Perp() ) );
      double jet1_rhoRatioPuppiPrime       =  log( puppi1sdmass * puppi1sdmass / ( puppi1P4.Perp()                  ) );
      double jet1_rhoRatioPuppiPmag        =  log( puppi1sdmass * puppi1sdmass / ( puppi1P4.P()    * puppi1P4.P()   ) );
      double jet1_rhoRatioPuppiPmagPrime   =  log( puppi1sdmass * puppi1sdmass / ( puppi1P4.P()                     ) );
  
      h_jet0_rhoRatio                      ->Fill( jet0_rhoRatio                );
      h_jet0_rhoRatioPrime                 ->Fill( jet0_rhoRatioPrime           );
      h_jet0_rhoRatioPmag                  ->Fill( jet0_rhoRatioPmag            );
      h_jet0_rhoRatioPmagPrime             ->Fill( jet0_rhoRatioPmagPrime       );
      h_jet0_rhoRatioPuppi                 ->Fill( jet0_rhoRatioPuppi           );
      h_jet0_rhoRatioPuppiPrime            ->Fill( jet0_rhoRatioPuppiPrime      );
      h_jet0_rhoRatioPuppiPmag             ->Fill( jet0_rhoRatioPuppiPmag       );
      h_jet0_rhoRatioPuppiPmagPrime        ->Fill( jet0_rhoRatioPuppiPmagPrime  );
      h_jet1_rhoRatio                      ->Fill( jet1_rhoRatio                );
      h_jet1_rhoRatioPrime                 ->Fill( jet1_rhoRatioPrime           );
      h_jet1_rhoRatioPmag                  ->Fill( jet1_rhoRatioPmag            );
      h_jet1_rhoRatioPmagPrime             ->Fill( jet1_rhoRatioPmagPrime       );
      h_jet1_rhoRatioPuppi                 ->Fill( jet1_rhoRatioPuppi           );
      h_jet1_rhoRatioPuppiPrime            ->Fill( jet1_rhoRatioPuppiPrime      );
      h_jet1_rhoRatioPuppiPmag             ->Fill( jet1_rhoRatioPuppiPmag       );
      h_jet1_rhoRatioPuppiPmagPrime        ->Fill( jet1_rhoRatioPuppiPmagPrime  );

      h_jet0_tau32_rhoRatio                ->Fill( jet0_rhoRatio               ,  Jet0Tau32      );
      h_jet0_tau32_rhoRatioPrime           ->Fill( jet0_rhoRatioPrime          ,  Jet0Tau32      );
      h_jet0_tau32_rhoRatioPmag            ->Fill( jet0_rhoRatioPmag           ,  Jet0Tau32      );
      h_jet0_tau32_rhoRatioPmagPrime       ->Fill( jet0_rhoRatioPmagPrime      ,  Jet0Tau32      );
      h_jet0_tau32_rhoRatioPuppi           ->Fill( jet0_rhoRatioPuppi          ,  Jet0PuppiTau32 );
      h_jet0_tau32_rhoRatioPuppiPrime      ->Fill( jet0_rhoRatioPuppiPrime     ,  Jet0PuppiTau32 );
      h_jet0_tau32_rhoRatioPuppiPmag       ->Fill( jet0_rhoRatioPuppiPmag      ,  Jet0PuppiTau32 );
      h_jet0_tau32_rhoRatioPuppiPmagPrime  ->Fill( jet0_rhoRatioPuppiPmagPrime ,  Jet0PuppiTau32 );
      h_jet1_tau32_rhoRatio                ->Fill( jet1_rhoRatio               ,  Jet0Tau32      );
      h_jet1_tau32_rhoRatioPrime           ->Fill( jet1_rhoRatioPrime          ,  Jet0Tau32      );
      h_jet1_tau32_rhoRatioPmag            ->Fill( jet1_rhoRatioPmag           ,  Jet0Tau32      );
      h_jet1_tau32_rhoRatioPmagPrime       ->Fill( jet1_rhoRatioPmagPrime      ,  Jet0Tau32      );
      h_jet1_tau32_rhoRatioPuppi           ->Fill( jet1_rhoRatioPuppi          ,  Jet1PuppiTau32 );
      h_jet1_tau32_rhoRatioPuppiPrime      ->Fill( jet1_rhoRatioPuppiPrime     ,  Jet1PuppiTau32 );
      h_jet1_tau32_rhoRatioPuppiPmag       ->Fill( jet1_rhoRatioPuppiPmag      ,  Jet1PuppiTau32 );
      h_jet1_tau32_rhoRatioPuppiPmagPrime  ->Fill( jet1_rhoRatioPuppiPmagPrime ,  Jet1PuppiTau32 );


      h_jet0_tau21_rhoRatio                ->Fill( jet0_rhoRatio               ,  Jet0Tau21      );
      h_jet0_tau21_rhoRatioPrime           ->Fill( jet0_rhoRatioPrime          ,  Jet0Tau21      );
      h_jet0_tau21_rhoRatioPmag            ->Fill( jet0_rhoRatioPmag           ,  Jet0Tau21      );
      h_jet0_tau21_rhoRatioPmagPrime       ->Fill( jet0_rhoRatioPmagPrime      ,  Jet0Tau21      );
      h_jet0_tau21_rhoRatioPuppi           ->Fill( jet0_rhoRatioPuppi          ,  Jet0PuppiTau21 );
      h_jet0_tau21_rhoRatioPuppiPrime      ->Fill( jet0_rhoRatioPuppiPrime     ,  Jet0PuppiTau21 );
      h_jet0_tau21_rhoRatioPuppiPmag       ->Fill( jet0_rhoRatioPuppiPmag      ,  Jet0PuppiTau21 );
      h_jet0_tau21_rhoRatioPuppiPmagPrime  ->Fill( jet0_rhoRatioPuppiPmagPrime ,  Jet0PuppiTau21 );
      h_jet1_tau21_rhoRatio                ->Fill( jet1_rhoRatio               ,  Jet0Tau21      );
      h_jet1_tau21_rhoRatioPrime           ->Fill( jet1_rhoRatioPrime          ,  Jet0Tau21      );
      h_jet1_tau21_rhoRatioPmag            ->Fill( jet1_rhoRatioPmag           ,  Jet0Tau21      );
      h_jet1_tau21_rhoRatioPmagPrime       ->Fill( jet1_rhoRatioPmagPrime      ,  Jet0Tau21      );
      h_jet1_tau21_rhoRatioPuppi           ->Fill( jet1_rhoRatioPuppi          ,  Jet0PuppiTau21 );
      h_jet1_tau21_rhoRatioPuppiPrime      ->Fill( jet1_rhoRatioPuppiPrime     ,  Jet0PuppiTau21 );
      h_jet1_tau21_rhoRatioPuppiPmag       ->Fill( jet1_rhoRatioPuppiPmag      ,  Jet0PuppiTau21 );
      h_jet1_tau21_rhoRatioPuppiPmagPrime  ->Fill( jet1_rhoRatioPuppiPmagPrime ,  Jet0PuppiTau21 );

      double jet0tau42   = 99;
      double jet1tau42   = 99;
      double puppi0tau42 = 99;
      double puppi1tau42 = 99;
      if (Jet0Tau2>0)      jet0tau42   = Jet0Tau4 / Jet0Tau2;
      if (Jet1Tau2>0)      jet1tau42   = Jet1Tau4 / Jet1Tau2;
      if (Jet0PuppiTau2>0) puppi0tau42 = Jet0PuppiTau4 / Jet0PuppiTau2 ;
      if (Jet1PuppiTau2>0) puppi1tau42 = Jet1PuppiTau4 / Jet1PuppiTau2 ;

      h_jet0_tau42_rhoRatio                ->Fill( jet0_rhoRatio               ,  jet0tau42   );
      h_jet0_tau42_rhoRatioPrime           ->Fill( jet0_rhoRatioPrime          ,  jet0tau42   );
      h_jet0_tau42_rhoRatioPmag            ->Fill( jet0_rhoRatioPmag           ,  jet0tau42   );
      h_jet0_tau42_rhoRatioPmagPrime       ->Fill( jet0_rhoRatioPmagPrime      ,  jet0tau42   );
      h_jet0_tau42_rhoRatioPuppi           ->Fill( jet0_rhoRatioPuppi          ,  puppi0tau42 );
      h_jet0_tau42_rhoRatioPuppiPrime      ->Fill( jet0_rhoRatioPuppiPrime     ,  puppi0tau42 );
      h_jet0_tau42_rhoRatioPuppiPmag       ->Fill( jet0_rhoRatioPuppiPmag      ,  puppi0tau42 );
      h_jet0_tau42_rhoRatioPuppiPmagPrime  ->Fill( jet0_rhoRatioPuppiPmagPrime ,  puppi0tau42 );
      h_jet1_tau42_rhoRatio                ->Fill( jet1_rhoRatio               ,  jet1tau42   );
      h_jet1_tau42_rhoRatioPrime           ->Fill( jet1_rhoRatioPrime          ,  jet1tau42   );
      h_jet1_tau42_rhoRatioPmag            ->Fill( jet1_rhoRatioPmag           ,  jet1tau42   );
      h_jet1_tau42_rhoRatioPmagPrime       ->Fill( jet1_rhoRatioPmagPrime      ,  jet1tau42   );
      h_jet1_tau42_rhoRatioPuppi           ->Fill( jet1_rhoRatioPuppi          ,  puppi1tau42 );
      h_jet1_tau42_rhoRatioPuppiPrime      ->Fill( jet1_rhoRatioPuppiPrime     ,  puppi1tau42 );
      h_jet1_tau42_rhoRatioPuppiPmag       ->Fill( jet1_rhoRatioPuppiPmag      ,  puppi1tau42 );
      h_jet1_tau42_rhoRatioPuppiPmagPrime  ->Fill( jet1_rhoRatioPuppiPmagPrime ,  puppi1tau42 );


      // kinematics in double tagged events
      if (double_tag_t){
	
      	if (!isFrozen || !isData ){    
      	  h_2ttag_inclu_dRapIn_DijetMass                        ->Fill( DijetMass , evWeight );  
      	  if (DijetDeltaRap >=1) h_2ttag_inclu_dRapLo_DijetMass ->Fill( DijetMass , evWeight );                          
      	  if (DijetDeltaRap  <1) h_2ttag_inclu_dRapHi_DijetMass ->Fill( DijetMass , evWeight );  
      	} 
           
        h_2ttag_inclu_DeltaRap                                  ->Fill( DijetDeltaRap            , evWeight );   
        h_2ttag_inclu_DeltaPhi                                  ->Fill( DijetDeltaPhi            , evWeight );   
        h_2ttag_inclu_HT                                        ->Fill( HT                       , evWeight );   
        h_2ttag_inclu_MET                                       ->Fill( AllHadMETpt              , evWeight );   
        h_2ttag_inclu_METphi                                    ->Fill( AllHadMETphi             , evWeight );   
        h_2ttag_inclu_Nvtx                                      ->Fill( AllHadNvtx               , evWeight );                
        h_2ttag_inclu_Jet0P                                     ->Fill( jet0P                   , evWeight );          
        h_2ttag_inclu_Jet0Pt                                    ->Fill( Jet0Pt                   , evWeight );          
        h_2ttag_inclu_Jet0Phi                                   ->Fill( Jet0Phi                  , evWeight );          
        h_2ttag_inclu_Jet0Rap                                   ->Fill( Jet0Rap                  , evWeight );          
        h_2ttag_inclu_Jet0SDmass                                ->Fill( Jet0SDmass               , evWeight );                           
        h_2ttag_inclu_Jet0SDmassCorrL23                         ->Fill( Jet0SDmassCorrL23        , evWeight );          
        h_2ttag_inclu_Jet0SDmassCorrL23Up                       ->Fill( Jet0SDmassCorrL23Up      , evWeight );                        
        h_2ttag_inclu_Jet0Tau1                                  ->Fill( Jet0Tau1                 , evWeight );          
        h_2ttag_inclu_Jet0Tau2                                  ->Fill( Jet0Tau2                 , evWeight );          
        h_2ttag_inclu_Jet0Tau3                                  ->Fill( Jet0Tau3                 , evWeight );    
        h_2ttag_inclu_Jet0Tau4                                  ->Fill( Jet0Tau4                 , evWeight );
        h_2ttag_inclu_Jet0SDmaxbdisc                            ->Fill( Jet0SDmaxbdisc           , evWeight );        
        h_2ttag_inclu_Jet0SDsubjet0pt                           ->Fill( Jet0SDsubjet0pt          , evWeight );          
        h_2ttag_inclu_Jet0SDsubjet0mass                         ->Fill( Jet0SDsubjet0mass        , evWeight );                   
        h_2ttag_inclu_Jet0SDsubjet0tau1                         ->Fill( Jet0SDsubjet0tau1        , evWeight );          
        h_2ttag_inclu_Jet0SDsubjet0tau2                         ->Fill( Jet0SDsubjet0tau2        , evWeight );          
        h_2ttag_inclu_Jet0SDsubjet0tau3                         ->Fill( Jet0SDsubjet0tau3        , evWeight );          
        h_2ttag_inclu_Jet0SDsubjet0bdisc                        ->Fill( Jet0SDsubjet0bdisc       , evWeight );          
        h_2ttag_inclu_Jet0SDsubjet1pt                           ->Fill( Jet0SDsubjet1pt          , evWeight );          
        h_2ttag_inclu_Jet0SDsubjet1mass                         ->Fill( Jet0SDsubjet1mass        , evWeight );
        h_2ttag_inclu_Jet0SDsubjet1tau1                         ->Fill( Jet0SDsubjet1tau1        , evWeight );          
        h_2ttag_inclu_Jet0SDsubjet1tau2                         ->Fill( Jet0SDsubjet1tau2        , evWeight );          
        h_2ttag_inclu_Jet0SDsubjet1tau3                         ->Fill( Jet0SDsubjet1tau3        , evWeight );          
        h_2ttag_inclu_Jet0SDsubjet1bdisc                        ->Fill( Jet0SDsubjet1bdisc       , evWeight );          
        h_2ttag_inclu_Jet0PuppiPt                               ->Fill( Jet0PuppiPt              , evWeight );                                
        h_2ttag_inclu_Jet0PuppiMass                             ->Fill( Jet0PuppiMass            , evWeight );                         
        h_2ttag_inclu_Jet0PuppiSDpt                             ->Fill( Jet0PuppiSDpt            , evWeight );                              
        h_2ttag_inclu_Jet0PuppiTau1                             ->Fill( Jet0PuppiTau1            , evWeight );          
        h_2ttag_inclu_Jet0PuppiTau2                             ->Fill( Jet0PuppiTau2            , evWeight );          
        h_2ttag_inclu_Jet0PuppiTau3                             ->Fill( Jet0PuppiTau3            , evWeight );          
        h_2ttag_inclu_Jet0PuppiTau4                             ->Fill( Jet0PuppiTau4            , evWeight );                              
        h_2ttag_inclu_Jet0PuppiSDmaxbdisc                       ->Fill( Jet0PuppiSDmaxbdisc      , evWeight );             
        h_2ttag_inclu_Jet0PuppiSDsubjet0pt                      ->Fill( Jet0PuppiSDsubjet0pt     , evWeight );          
        h_2ttag_inclu_Jet0PuppiSDsubjet0mass                    ->Fill( Jet0PuppiSDsubjet0mass   , evWeight );          
        h_2ttag_inclu_Jet0PuppiSDsubjet0tau1                    ->Fill( Jet0PuppiSDsubjet0tau1   , evWeight );          
        h_2ttag_inclu_Jet0PuppiSDsubjet0tau2                    ->Fill( Jet0PuppiSDsubjet0tau2   , evWeight );          
        h_2ttag_inclu_Jet0PuppiSDsubjet0tau3                    ->Fill( Jet0PuppiSDsubjet0tau3   , evWeight );          
        h_2ttag_inclu_Jet0PuppiSDsubjet0bdisc                   ->Fill( Jet0PuppiSDsubjet0bdisc  , evWeight );          
        h_2ttag_inclu_Jet0PuppiSDsubjet1pt                      ->Fill( Jet0PuppiSDsubjet1pt     , evWeight );          
        h_2ttag_inclu_Jet0PuppiSDsubjet1mass                    ->Fill( Jet0PuppiSDsubjet1mass   , evWeight );          
        h_2ttag_inclu_Jet0PuppiSDsubjet1tau1                    ->Fill( Jet0PuppiSDsubjet1tau1   , evWeight );          
        h_2ttag_inclu_Jet0PuppiSDsubjet1tau2                    ->Fill( Jet0PuppiSDsubjet1tau2   , evWeight );          
        h_2ttag_inclu_Jet0PuppiSDsubjet1tau3                    ->Fill( Jet0PuppiSDsubjet1tau3   , evWeight );          
        h_2ttag_inclu_Jet0PuppiSDsubjet1bdisc                   ->Fill( Jet0PuppiSDsubjet1bdisc  , evWeight );
        h_2ttag_inclu_Jet0CHF                                   ->Fill( Jet0CHF                  , evWeight );          
        h_2ttag_inclu_Jet0NHF                                   ->Fill( Jet0NHF                  , evWeight );          
        h_2ttag_inclu_Jet0CM                                    ->Fill( Jet0CM                   , evWeight );          
        h_2ttag_inclu_Jet0NM                                    ->Fill( Jet0NM                   , evWeight );          
        h_2ttag_inclu_Jet0NEF                                   ->Fill( Jet0NEF                  , evWeight );          
        h_2ttag_inclu_Jet0CEF                                   ->Fill( Jet0CEF                  , evWeight );          
        h_2ttag_inclu_Jet0MF                                    ->Fill( Jet0MF                   , evWeight );          
        h_2ttag_inclu_Jet0Mult                                  ->Fill( Jet0Mult                 , evWeight );          
      }
      if (double_tag_t_b){
        if (!isFrozen || !isData ){       
          h_2ttag_2btag_dRapIn_DijetMass                        ->Fill( DijetMass                , evWeight );  
          if (DijetDeltaRap >=1) h_2ttag_2btag_dRapLo_DijetMass ->Fill( DijetMass                , evWeight );                          
          if (DijetDeltaRap  <1) h_2ttag_2btag_dRapHi_DijetMass ->Fill( DijetMass                , evWeight );  
        }              
        h_2ttag_2btag_DeltaRap                                  ->Fill( DijetDeltaRap            , evWeight );   
        h_2ttag_2btag_DeltaPhi                                  ->Fill( DijetDeltaPhi            , evWeight ); 
        h_2ttag_2btag_HT                                        ->Fill( HT                       , evWeight );   
        h_2ttag_2btag_MET                                       ->Fill( AllHadMETpt              , evWeight );   
        h_2ttag_2btag_METphi                                    ->Fill( AllHadMETphi             , evWeight );   
        h_2ttag_2btag_METphi                                    ->Fill( AllHadNvtx               , evWeight );   

        h_2ttag_2btag_Jet0PuppiSDsubjet0pt                      ->Fill( Jet0PuppiSDsubjet0pt     , evWeight );          
        h_2ttag_2btag_Jet0PuppiSDsubjet0mass                    ->Fill( Jet0PuppiSDsubjet0mass   , evWeight );          
        h_2ttag_2btag_Jet0PuppiSDsubjet0tau1                    ->Fill( Jet0PuppiSDsubjet0tau1   , evWeight );          
        h_2ttag_2btag_Jet0PuppiSDsubjet0tau2                    ->Fill( Jet0PuppiSDsubjet0tau2   , evWeight );          
        h_2ttag_2btag_Jet0PuppiSDsubjet0tau3                    ->Fill( Jet0PuppiSDsubjet0tau3   , evWeight );          
        h_2ttag_2btag_Jet0PuppiSDsubjet0bdisc                   ->Fill( Jet0PuppiSDsubjet0bdisc  , evWeight );          
        h_2ttag_2btag_Jet0PuppiSDsubjet1pt                      ->Fill( Jet0PuppiSDsubjet1pt     , evWeight );          
        h_2ttag_2btag_Jet0PuppiSDsubjet1mass                    ->Fill( Jet0PuppiSDsubjet1mass   , evWeight );          
        h_2ttag_2btag_Jet0PuppiSDsubjet1tau1                    ->Fill( Jet0PuppiSDsubjet1tau1   , evWeight );          
        h_2ttag_2btag_Jet0PuppiSDsubjet1tau2                    ->Fill( Jet0PuppiSDsubjet1tau2   , evWeight );          
        h_2ttag_2btag_Jet0PuppiSDsubjet1tau3                    ->Fill( Jet0PuppiSDsubjet1tau3   , evWeight );          
        h_2ttag_2btag_Jet0PuppiSDsubjet1bdisc                   ->Fill( Jet0PuppiSDsubjet1bdisc  , evWeight );
      }
      if (double_tag_t_single_tag_b){
        if (!isFrozen || !isData ){      
          h_2ttag_1btag_dRapIn_DijetMass                        ->Fill( DijetMass                , evWeight );  
          if (DijetDeltaRap >=1) h_2ttag_1btag_dRapLo_DijetMass ->Fill( DijetMass                , evWeight );                          
          if (DijetDeltaRap  <1) h_2ttag_1btag_dRapHi_DijetMass ->Fill( DijetMass                , evWeight ); 
        }              
        h_2ttag_1btag_DeltaRap                                  ->Fill( DijetDeltaRap            , evWeight );   
        h_2ttag_1btag_DeltaPhi                                  ->Fill( DijetDeltaPhi            , evWeight );    
        h_2ttag_1btag_HT                                        ->Fill( HT                       , evWeight );   
        h_2ttag_1btag_MET                                       ->Fill( AllHadMETpt              , evWeight );   
        h_2ttag_1btag_METphi                                    ->Fill( AllHadMETphi             , evWeight );   
        h_2ttag_1btag_METphi                                    ->Fill( AllHadNvtx               , evWeight );  


        h_2ttag_1btag_Jet0PuppiSDsubjet0pt                      ->Fill( Jet0PuppiSDsubjet0pt     , evWeight );          
        h_2ttag_1btag_Jet0PuppiSDsubjet0mass                    ->Fill( Jet0PuppiSDsubjet0mass   , evWeight );          
        h_2ttag_1btag_Jet0PuppiSDsubjet0tau1                    ->Fill( Jet0PuppiSDsubjet0tau1   , evWeight );          
        h_2ttag_1btag_Jet0PuppiSDsubjet0tau2                    ->Fill( Jet0PuppiSDsubjet0tau2   , evWeight );          
        h_2ttag_1btag_Jet0PuppiSDsubjet0tau3                    ->Fill( Jet0PuppiSDsubjet0tau3   , evWeight );          
        h_2ttag_1btag_Jet0PuppiSDsubjet0bdisc                   ->Fill( Jet0PuppiSDsubjet0bdisc  , evWeight );          
        h_2ttag_1btag_Jet0PuppiSDsubjet1pt                      ->Fill( Jet0PuppiSDsubjet1pt     , evWeight );          
        h_2ttag_1btag_Jet0PuppiSDsubjet1mass                    ->Fill( Jet0PuppiSDsubjet1mass   , evWeight );          
        h_2ttag_1btag_Jet0PuppiSDsubjet1tau1                    ->Fill( Jet0PuppiSDsubjet1tau1   , evWeight );          
        h_2ttag_1btag_Jet0PuppiSDsubjet1tau2                    ->Fill( Jet0PuppiSDsubjet1tau2   , evWeight );          
        h_2ttag_1btag_Jet0PuppiSDsubjet1tau3                    ->Fill( Jet0PuppiSDsubjet1tau3   , evWeight );          
        h_2ttag_1btag_Jet0PuppiSDsubjet1bdisc                   ->Fill( Jet0PuppiSDsubjet1bdisc  , evWeight );
      }     
      if (double_tag_t_no_b){
        if (!isFrozen || !isData ){      
          h_2ttag_0btag_dRapIn_DijetMass                        ->Fill( DijetMass                , evWeight );  
          if (DijetDeltaRap >=1) h_2ttag_0btag_dRapLo_DijetMass ->Fill( DijetMass                , evWeight );                          
          if (DijetDeltaRap  <1) h_2ttag_0btag_dRapHi_DijetMass ->Fill( DijetMass                , evWeight ); 
        }    
        h_2ttag_0btag_DeltaRap                                  ->Fill( DijetDeltaRap            , evWeight );   
        h_2ttag_0btag_DeltaPhi                                  ->Fill( DijetDeltaPhi            , evWeight );              
        h_2ttag_0btag_HT                                        ->Fill( HT                       , evWeight );   
        h_2ttag_0btag_MET                                       ->Fill( AllHadMETpt              , evWeight );   
        h_2ttag_0btag_METphi                                    ->Fill( AllHadMETphi             , evWeight );   
        h_2ttag_0btag_METphi                                    ->Fill( AllHadNvtx               , evWeight );  

        h_2ttag_0btag_Jet0PuppiSDsubjet0pt                      ->Fill( Jet0PuppiSDsubjet0pt     , evWeight );          
        h_2ttag_0btag_Jet0PuppiSDsubjet0mass                    ->Fill( Jet0PuppiSDsubjet0mass   , evWeight );          
        h_2ttag_0btag_Jet0PuppiSDsubjet0tau1                    ->Fill( Jet0PuppiSDsubjet0tau1   , evWeight );          
        h_2ttag_0btag_Jet0PuppiSDsubjet0tau2                    ->Fill( Jet0PuppiSDsubjet0tau2   , evWeight );          
        h_2ttag_0btag_Jet0PuppiSDsubjet0tau3                    ->Fill( Jet0PuppiSDsubjet0tau3   , evWeight );          
        h_2ttag_0btag_Jet0PuppiSDsubjet0bdisc                   ->Fill( Jet0PuppiSDsubjet0bdisc  , evWeight );          
        h_2ttag_0btag_Jet0PuppiSDsubjet1pt                      ->Fill( Jet0PuppiSDsubjet1pt     , evWeight );          
        h_2ttag_0btag_Jet0PuppiSDsubjet1mass                    ->Fill( Jet0PuppiSDsubjet1mass   , evWeight );          
        h_2ttag_0btag_Jet0PuppiSDsubjet1tau1                    ->Fill( Jet0PuppiSDsubjet1tau1   , evWeight );          
        h_2ttag_0btag_Jet0PuppiSDsubjet1tau2                    ->Fill( Jet0PuppiSDsubjet1tau2   , evWeight );          
        h_2ttag_0btag_Jet0PuppiSDsubjet1tau3                    ->Fill( Jet0PuppiSDsubjet1tau3   , evWeight );          
        h_2ttag_0btag_Jet0PuppiSDsubjet1bdisc                   ->Fill( Jet0PuppiSDsubjet1bdisc  , evWeight );
      }     

      // Jet mass with different tagging requirements
      h_Jet0SDmass                                    ->Fill( Jet0SDmass , evWeight );  
      if (j0_tag_b)                                  h_Jet0SDmass_JetTag_b                           ->Fill( jet0sdmass , evWeight );
      if (j0_tag_tau32)                              h_Jet0SDmass_JetTag_tau32                       ->Fill( jet0sdmass , evWeight );
      if (j0_tag_b && j0_tag_tau32)                  h_Jet0SDmass_JetTag_b_tau32                     ->Fill( jet0sdmass , evWeight );
      if (j1_tag_t_b)                                h_Jet0SDmass_OppositeJetTag_t_b                 ->Fill( jet0sdmass , evWeight );
      if (j1_tag_t_b && j0_tag_b )                   h_Jet0SDmass_OppositeJetTag_t_b_JetTag_b        ->Fill( jet0sdmass , evWeight );
      if (j1_tag_t_b && j0_tag_b && j0_tag_tau32 )   h_Jet0SDmass_OppositeJetTag_t_b_JetTag_b_tau32  ->Fill( jet0sdmass , evWeight );
      
                                                     h_Jet1SDmass                                    ->Fill( jet1sdmass , evWeight );
      if (j1_tag_b)                                  h_Jet1SDmass_JetTag_b                           ->Fill( jet1sdmass , evWeight );
      if (j1_tag_tau32)                              h_Jet1SDmass_JetTag_tau32                       ->Fill( jet1sdmass , evWeight );
      if (j1_tag_b && j1_tag_tau32)                  h_Jet1SDmass_JetTag_b_tau32                     ->Fill( jet1sdmass , evWeight );
      if (j0_tag_t_b)                                h_Jet1SDmass_OppositeJetTag_t_b                 ->Fill( jet1sdmass , evWeight );
      if (j0_tag_t_b && j1_tag_b )                   h_Jet1SDmass_OppositeJetTag_t_b_JetTag_b        ->Fill( jet1sdmass , evWeight );
      if (j0_tag_t_b && j1_tag_b && j1_tag_tau32 )   h_Jet1SDmass_OppositeJetTag_t_b_JetTag_b_tau32  ->Fill( jet1sdmass , evWeight );
      
                                                     h_JetSDmass                                     ->Fill( jet0sdmass , evWeight );
      if (j0_tag_b)                                  h_JetSDmass_JetTag_b                            ->Fill( jet0sdmass , evWeight );
      if (j0_tag_tau32)                              h_JetSDmass_JetTag_tau32                        ->Fill( jet0sdmass , evWeight );
      if (j0_tag_b && j0_tag_tau32)                  h_JetSDmass_JetTag_b_tau32                      ->Fill( jet0sdmass , evWeight );
      if (j1_tag_t_b)                                h_JetSDmass_OppositeJetTag_t_b                  ->Fill( jet0sdmass , evWeight );
      if (j1_tag_t_b && j0_tag_b )                   h_JetSDmass_OppositeJetTag_t_b_JetTag_b         ->Fill( jet0sdmass , evWeight );
      if (j1_tag_t_b && j0_tag_b && j0_tag_tau32 )   h_JetSDmass_OppositeJetTag_t_b_JetTag_b_tau32   ->Fill( jet0sdmass , evWeight );

                                                     h_JetSDmass                                     ->Fill( jet1sdmass , evWeight );
      if (j1_tag_b)                                  h_JetSDmass_JetTag_b                            ->Fill( jet1sdmass , evWeight );
      if (j1_tag_tau32)                              h_JetSDmass_JetTag_tau32                        ->Fill( jet1sdmass , evWeight );
      if (j1_tag_b && j1_tag_tau32)                  h_JetSDmass_JetTag_b_tau32                      ->Fill( jet1sdmass , evWeight );
      if (j0_tag_t_b)                                h_JetSDmass_OppositeJetTag_t_b                  ->Fill( jet1sdmass , evWeight );
      if (j0_tag_t_b && j1_tag_b )                   h_JetSDmass_OppositeJetTag_t_b_JetTag_b         ->Fill( jet1sdmass , evWeight );
      if (j0_tag_t_b && j1_tag_b && j1_tag_tau32 )   h_JetSDmass_OppositeJetTag_t_b_JetTag_b_tau32   ->Fill( jet1sdmass , evWeight );

                                                     h_Jet0Tau32                                     ->Fill(  Jet0Tau32 , evWeight );
      if (j0_tag_b)                                  h_Jet0Tau32_JetTag_b                            ->Fill(  Jet0Tau32 , evWeight );
      if (j0_tag_mass)                               h_Jet0Tau32_JetTag_mass                         ->Fill(  Jet0Tau32 , evWeight );
      if (j0_tag_b && j0_tag_mass)                   h_Jet0Tau32_JetTag_b_mass                       ->Fill(  Jet0Tau32 , evWeight );
      if (j1_tag_t_b)                                h_Jet0Tau32_OppositeJetTag_t_b                  ->Fill(  Jet0Tau32 , evWeight );
      if (j1_tag_t_b && j0_tag_b )                   h_Jet0Tau32_OppositeJetTag_t_b_JetTag_b         ->Fill(  Jet0Tau32 , evWeight );
      if (j1_tag_t_b && j0_tag_b && j0_tag_mass)     h_Jet0Tau32_OppositeJetTag_t_b_JetTag_b_mass    ->Fill(  Jet0Tau32 , evWeight );
    
                                                     h_Jet1Tau32                                     ->Fill(  Jet1Tau32 , evWeight );
      if (j1_tag_b)                                  h_Jet1Tau32_JetTag_b                            ->Fill(  Jet1Tau32 , evWeight );
      if (j1_tag_mass)                               h_Jet1Tau32_JetTag_mass                         ->Fill(  Jet1Tau32 , evWeight );
      if (j1_tag_b && j1_tag_mass)                   h_Jet1Tau32_JetTag_b_mass                       ->Fill(  Jet1Tau32 , evWeight );
      if (j0_tag_t_b)                                h_Jet1Tau32_OppositeJetTag_t_b                  ->Fill(  Jet1Tau32 , evWeight );
      if (j0_tag_t_b && j1_tag_b )                   h_Jet1Tau32_OppositeJetTag_t_b_JetTag_b         ->Fill(  Jet1Tau32 , evWeight );
      if (j0_tag_t_b && j1_tag_b && j1_tag_mass )    h_Jet1Tau32_OppositeJetTag_t_b_JetTag_b_mass    ->Fill(  Jet1Tau32 , evWeight );

                                                     h_JetTau32                                      ->Fill(  Jet0Tau32 , evWeight );
      if (j0_tag_b)                                  h_JetTau32_JetTag_b                             ->Fill(  Jet0Tau32 , evWeight );
      if (j0_tag_mass)                               h_JetTau32_JetTag_mass                          ->Fill(  Jet0Tau32 , evWeight );
      if (j0_tag_b && j0_tag_mass)                   h_JetTau32_JetTag_b_mass                        ->Fill(  Jet0Tau32 , evWeight );
      if (j1_tag_t_b)                                h_JetTau32_OppositeJetTag_t_b                   ->Fill(  Jet0Tau32 , evWeight );
      if (j1_tag_t_b && j0_tag_b )                   h_JetTau32_OppositeJetTag_t_b_JetTag_b          ->Fill(  Jet0Tau32 , evWeight );
      if (j1_tag_t_b && j0_tag_b && j0_tag_mass )    h_JetTau32_OppositeJetTag_t_b_JetTag_b_mass     ->Fill(  Jet0Tau32 , evWeight );

                                                     h_JetTau32                                      ->Fill(  Jet1Tau32 , evWeight );
      if (j1_tag_b)                                  h_JetTau32_JetTag_b                             ->Fill(  Jet1Tau32 , evWeight );
      if (j1_tag_mass)                               h_JetTau32_JetTag_mass                          ->Fill(  Jet1Tau32 , evWeight );
      if (j1_tag_b && j1_tag_mass)                   h_JetTau32_JetTag_b_mass                        ->Fill(  Jet1Tau32 , evWeight );
      if (j0_tag_t_b)                                h_JetTau32_OppositeJetTag_t_b                   ->Fill(  Jet1Tau32 , evWeight );
      if (j0_tag_t_b && j1_tag_b )                   h_JetTau32_OppositeJetTag_t_b_JetTag_b          ->Fill(  Jet1Tau32 , evWeight );
      if (j0_tag_t_b && j1_tag_b && j1_tag_mass )    h_JetTau32_OppositeJetTag_t_b_JetTag_b_mass     ->Fill(  Jet1Tau32 , evWeight );



        // double b-tagged plots
        if (j0_tag_b && j1_tag_b){
          h_2btag_DijetMass                         ->Fill( DijetMass                   , evWeight );
          h_2btag_DeltaRap                          ->Fill( DijetDeltaRap               , evWeight );
          h_2btag_jet0massSD                        ->Fill( Jet0SDmass                  , evWeight );
          h_2btag_jet0tau32                         ->Fill( Jet0Tau32                   , evWeight );
          h_2btag_jet0tau21                         ->Fill( Jet0Tau21                   , evWeight );
          h_2btag_jet0tau1                          ->Fill( Jet0Tau1                    , evWeight );
          h_2btag_jet0tau2                          ->Fill( Jet0Tau2                    , evWeight );
          h_2btag_jet0tau3                          ->Fill( Jet0Tau3                    , evWeight );
          h_2btag_jet0subjet0mass                   ->Fill( Jet0SDsubjet0mass           , evWeight );
          h_2btag_jet0subjet1mass                   ->Fill( Jet0SDsubjet1mass           , evWeight );
          h_2btag_jet0subjet0mass_jet0subjet1mass   ->Fill( Jet0SDsubjet0mass           , Jet0SDsubjet1mass  , evWeight );
          h_2btag_jet0subjet0bdisc_jet0subjet1bdisc ->Fill( Jet0SDsubjet0bdisc          , Jet0SDsubjet1bdisc , evWeight );
          h_2btag_jet1massSD                        ->Fill( Jet1SDmass                  , evWeight );
          h_2btag_jet1tau32                         ->Fill( Jet1Tau32                   , evWeight );
          h_2btag_jet1tau21                         ->Fill( Jet1Tau21                   , evWeight );
          h_2btag_jet1tau1                          ->Fill( Jet1Tau1                    , evWeight );
          h_2btag_jet1tau2                          ->Fill( Jet1Tau2                    , evWeight );
          h_2btag_jet1tau3                          ->Fill( Jet1Tau3                    , evWeight );
          h_2btag_jet1subjet0mass                   ->Fill( Jet1SDsubjet0mass           , evWeight );
          h_2btag_jet1subjet1mass                   ->Fill( Jet1SDsubjet1mass           , evWeight );
          h_2btag_jet1subjet0mass_jet1subjet1mass   ->Fill( Jet1SDsubjet0mass           , Jet1SDsubjet1mass  , evWeight );
          h_2btag_jet1subjet0bdisc_jet1subjet1bdisc ->Fill( Jet1SDsubjet0bdisc          , Jet1SDsubjet1bdisc , evWeight );

          if (j1_tag_t){
            h_2btag_jet1ttag_jet0massSD                        ->Fill( Jet0SDmass                  , evWeight );
            h_2btag_jet1ttag_jet0tau32                         ->Fill( Jet0Tau32                   , evWeight );
            h_2btag_jet1ttag_jet0tau21                         ->Fill( Jet0Tau21                   , evWeight );
            h_2btag_jet1ttag_jet0tau1                          ->Fill( Jet0Tau1                    , evWeight );
            h_2btag_jet1ttag_jet0tau2                          ->Fill( Jet0Tau2                    , evWeight );
            h_2btag_jet1ttag_jet0tau3                          ->Fill( Jet0Tau3                    , evWeight );
            h_2btag_jet1ttag_jet0subjet0mass                   ->Fill( Jet0SDsubjet0mass           , evWeight );
            h_2btag_jet1ttag_jet0subjet1mass                   ->Fill( Jet0SDsubjet1mass           , evWeight );
            h_2btag_jet1ttag_jet0subjet0mass_jet0subjet1mass   ->Fill( Jet0SDsubjet0mass       ,      Jet0SDsubjet1mass , evWeight );
            h_2btag_jet1ttag_jet0subjet0bdisc_jet0subjet1bdisc ->Fill( Jet0SDsubjet0bdisc      ,     Jet0SDsubjet1bdisc , evWeight );

            if (j0_tag_tau32) h_2btag_jet1ttag_jet0tautag_jet0massSD           ->Fill( Jet0SDmass                  , evWeight );

            if (j0_tag_mass){
              h_2btag_jet1ttag_jet0masstag_jet0tau32                         ->Fill( Jet0Tau32                   , evWeight );
              h_2btag_jet1ttag_jet0masstag_jet0tau21                         ->Fill( Jet0Tau21                   , evWeight );
              h_2btag_jet1ttag_jet0masstag_jet0tau1                          ->Fill( Jet0Tau1                    , evWeight );
              h_2btag_jet1ttag_jet0masstag_jet0tau2                          ->Fill( Jet0Tau2                    , evWeight );
              h_2btag_jet1ttag_jet0masstag_jet0tau3                          ->Fill( Jet0Tau3                    , evWeight );
            }
          }

          if (j0_tag_t){
            h_2btag_jet0ttag_jet1massSD                        ->Fill( Jet1SDmass                  , evWeight );
            h_2btag_jet0ttag_jet1tau32                         ->Fill( Jet1Tau32                   , evWeight );
            h_2btag_jet0ttag_jet1tau21                         ->Fill( Jet1Tau21                   , evWeight );
            h_2btag_jet0ttag_jet1tau1                          ->Fill( Jet1Tau1                    , evWeight );
            h_2btag_jet0ttag_jet1tau2                          ->Fill( Jet1Tau2                    , evWeight );
            h_2btag_jet0ttag_jet1tau3                          ->Fill( Jet1Tau3                    , evWeight );
            h_2btag_jet0ttag_jet1subjet0mass                   ->Fill( Jet1SDsubjet0mass                  , evWeight );
            h_2btag_jet0ttag_jet1subjet1mass                   ->Fill( Jet1SDsubjet1mass                  , evWeight );
            h_2btag_jet0ttag_jet1subjet0mass_jet1subjet1mass   ->Fill( Jet1SDsubjet0mass       ,      Jet1SDsubjet1mass , evWeight );
            h_2btag_jet0ttag_jet1subjet0bdisc_jet1subjet1bdisc ->Fill( Jet1SDsubjet0bdisc      ,     Jet1SDsubjet1bdisc , evWeight );

            if (j1_tag_tau32) h_2btag_jet0ttag_jet1tautag_jet1massSD           ->Fill( Jet1SDmass                  , evWeight );

            if (j1_tag_mass){
              h_2btag_jet0ttag_jet1masstag_jet1tau32                         ->Fill( Jet1Tau32                   , evWeight );
              h_2btag_jet0ttag_jet1masstag_jet1tau21                         ->Fill( Jet1Tau21                   , evWeight );
              h_2btag_jet0ttag_jet1masstag_jet1tau1                          ->Fill( Jet1Tau1                    , evWeight );
              h_2btag_jet0ttag_jet1masstag_jet1tau2                          ->Fill( Jet1Tau2                    , evWeight );
              h_2btag_jet0ttag_jet1masstag_jet1tau3                          ->Fill( Jet1Tau3                    , evWeight );     
            }
          }
        } // end if double b-tagged

        //fill double t-tagged dijet distributions
        if (j0_tag_t && j1_tag_t){
          if (DijetDeltaRap >= 1){
            //inclusive 
            h_mttMass_tagMassSDTau32_dRapHi_inclusive->Fill( DijetMass   , evWeight );
            if (j0_tag_b && j1_tag_b) h_mttMass_tagMassSDTau32_dRapHi_2btag->Fill( DijetMass   , evWeight );  //2btag
            if ((j0_tag_b && !j1_tag_b) || (j1_tag_b && !j0_tag_b)) h_mttMass_tagMassSDTau32_dRapHi_1btag->Fill( DijetMass   , evWeight ); //1btag 
          }                                        
          if (DijetDeltaRap < 1){
            //inclusive 
            h_mttMass_tagMassSDTau32_dRapLo_inclusive->Fill( DijetMass   , evWeight );
            if (j0_tag_b && j1_tag_b) h_mttMass_tagMassSDTau32_dRapLo_2btag->Fill( DijetMass   , evWeight );  //2btag
            if ((j0_tag_b && !j1_tag_b) || (j1_tag_b && !j0_tag_b)) h_mttMass_tagMassSDTau32_dRapLo_1btag->Fill( DijetMass   , evWeight ); //1btag 
          }                                        

          h_topTag_jet0subjet0pt                     ->Fill( Jet0SDsubjet0pt         , evWeight );
          h_topTag_jet0subjet0mass                   ->Fill( Jet0SDsubjet0mass       , evWeight );
          h_topTag_jet0subjet0bdisc                  ->Fill( Jet0SDsubjet0bdisc      , evWeight );
          //h_topTag_jet0subjet0flav                   ->Fill( abs(Jet0SDsubjet0flav)  , evWeight ); 

          h_topTag_jet0subjet1pt                     ->Fill( Jet0SDsubjet1pt         , evWeight );
          h_topTag_jet0subjet1mass                   ->Fill( Jet0SDsubjet1mass       , evWeight );
          h_topTag_jet0subjet1bdisc                  ->Fill( Jet0SDsubjet1bdisc      , evWeight );
          //h_topTag_jet0subjet1flav                   ->Fill( abs(Jet0SDsubjet1flav)  , evWeight ); 

          h_topTag_jet0maxBdisc                      ->Fill(Jet0SDmaxbdisc            , evWeight );
          //h_topTag_jet0maxBdiscflav                  ->Fill( abs(maxbdiscflav_jet0_)   , evWeight ); 

          h_topTag_jet0pt                            ->Fill( jet0P4.Perp()             , evWeight );

          h_topTag_jet0pt_jet0subjet0pt              ->Fill( jet0P4.Perp()  ,      Jet0SDsubjet0pt   , evWeight );
          h_topTag_jet0pt_jet0subjet1pt              ->Fill( jet0P4.Perp()  ,      Jet0SDsubjet1pt   , evWeight );
          h_topTag_jet0subjet0pt_jet0subjet1pt       ->Fill( Jet0SDsubjet0pt         ,      Jet0SDsubjet1pt   , evWeight );
          h_topTag_jet0subjet0mass_jet0subjet1mass   ->Fill( Jet0SDsubjet0mass       ,      Jet0SDsubjet1mass , evWeight );
          //h_topTag_jet0subjet0flav_jet0subjet1flav   ->Fill( abs(Jet0SDsubjet0flav)  , abs(Jet0SDsubjet1flav) , evWeight ); 
          h_topTag_jet0subjet0bdisc_jet0subjet1bdisc ->Fill( Jet0SDsubjet0bdisc      ,     Jet0SDsubjet1bdisc , evWeight );

          if (j0_tag_b){
            h_topTagbTag_jet0subjet0pt                     ->Fill( Jet0SDsubjet0pt         , evWeight );
            h_topTagbTag_jet0subjet0mass                   ->Fill( Jet0SDsubjet0mass       , evWeight );
            h_topTagbTag_jet0subjet0bdisc                  ->Fill( Jet0SDsubjet0bdisc      , evWeight );
            //h_topTagbTag_jet0subjet0flav                   ->Fill( abs(Jet0SDsubjet0flav)  , evWeight ); 

            h_topTagbTag_jet0subjet1pt                     ->Fill( Jet0SDsubjet1pt         , evWeight );
            h_topTagbTag_jet0subjet1mass                   ->Fill( Jet0SDsubjet1mass       , evWeight );
            h_topTagbTag_jet0subjet1bdisc                  ->Fill( Jet0SDsubjet1bdisc      , evWeight );
            //h_topTagbTag_jet0subjet1flav                   ->Fill( abs(Jet0SDsubjet1flav)  , evWeight ); 

            h_topTagbTag_jet0maxBdisc                      ->Fill(Jet0SDmaxbdisc            , evWeight );
            //h_topTagbTag_jet0maxBdiscflav                  ->Fill( abs(maxbdiscflav_jet0_)   , evWeight ); 

            h_topTagbTag_jet0pt                            ->Fill( jet0P4.Perp()             , evWeight );

            h_topTagbTag_jet0pt_jet0subjet0pt              ->Fill( jet0P4.Perp()  ,      Jet0SDsubjet0pt   , evWeight );
            h_topTagbTag_jet0pt_jet0subjet1pt              ->Fill( jet0P4.Perp()  ,      Jet0SDsubjet1pt   , evWeight );
            h_topTagbTag_jet0subjet0pt_jet0subjet1pt       ->Fill( Jet0SDsubjet0pt         ,      Jet0SDsubjet1pt   , evWeight );
            h_topTagbTag_jet0subjet0mass_jet0subjet1mass   ->Fill( Jet0SDsubjet0mass       ,      Jet0SDsubjet1mass , evWeight );
            //h_topTagbTag_jet0subjet0flav_jet0subjet1flav   ->Fill( abs(Jet0SDsubjet0flav)  , abs(Jet0SDsubjet1flav) , evWeight ); 
            h_topTagbTag_jet0subjet0bdisc_jet0subjet1bdisc ->Fill( Jet0SDsubjet0bdisc      ,     Jet0SDsubjet1bdisc , evWeight );
          }// end if jet 0 b-tagged
        } // end if double t-tagged


      // Gen Studies
      if (!isData) {
        // GenMatch bools
        double gen_match_condition = 0.8;
        bool j0_match_Wd1 = Jet0GenMatched_DeltaR_jet_Wd1 < gen_match_condition ;  
        bool j0_match_Wd2 = Jet0GenMatched_DeltaR_jet_Wd2 < gen_match_condition ;  
        bool j0_match_b   = Jet0GenMatched_DeltaR_jet_b   < gen_match_condition ; 
	
        // Old tests
        if (Jet0GenMatched_DeltaR_jet_t<0.8) h_Jet0SDmass_matchedTop->Fill( Jet0SDmass , evWeight );
        if (Jet0GenMatched_DeltaR_jet_t<0.8 && Jet0GenMatched_MaxDeltaRPartonTop < 0.8 ) h_Jet0SDmass_matchedTop_topDist->Fill( Jet0SDmass , evWeight );
        else h_Jet0SDmass_outside->Fill( Jet0SDmass , evWeight );

        // Top decay combinatorics within the jet (ttbarMC)
        h_Jet0SDmass_all ->Fill( Jet0SDmass , evWeight );
        if      (  j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_in_qqb    ->Fill( jet0sdmass , evWeight );
        else if (  j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_in_qq     ->Fill( jet0sdmass , evWeight );
        else if (  j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_in_qb     ->Fill( jet0sdmass , evWeight );
        else if ( !j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_in_qb     ->Fill( jet0sdmass , evWeight );
        else if ( !j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_in_b      ->Fill( jet0sdmass , evWeight );
        else if ( !j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_in_q      ->Fill( jet0sdmass , evWeight );
        else if (  j0_match_Wd1 && !j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_in_q      ->Fill( jet0sdmass , evWeight );
        else                                                      h_Jet0SDmass_unmatched ->Fill( jet0sdmass , evWeight );
          
        h_Jet0Tau32_all ->Fill( Jet0Tau32 , evWeight );
        if      (  j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_in_qqb     ->Fill( Jet0Tau32 , evWeight );
        else if (  j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_in_qq      ->Fill( Jet0Tau32 , evWeight );
        else if (  j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_in_qb      ->Fill( Jet0Tau32 , evWeight );
        else if ( !j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_in_qb      ->Fill( Jet0Tau32 , evWeight );
        else if ( !j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_in_b       ->Fill( Jet0Tau32 , evWeight );
        else if ( !j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_in_q       ->Fill( Jet0Tau32 , evWeight );
        else if (  j0_match_Wd1 && !j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_in_q       ->Fill( Jet0Tau32 , evWeight );
        else                                                      h_Jet0Tau32_unmatched  ->Fill( Jet0Tau32 , evWeight );
          

        if (Jet0Pt>600){
          h_Jet0SDmass_Pt600_all ->Fill( Jet0SDmass , evWeight );
          if      (  j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_Pt600_in_qqb    ->Fill( jet0sdmass , evWeight );
          else if (  j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_Pt600_in_qq     ->Fill( jet0sdmass , evWeight );
          else if (  j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_Pt600_in_qb     ->Fill( jet0sdmass , evWeight );
          else if ( !j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_Pt600_in_qb     ->Fill( jet0sdmass , evWeight );
          else if ( !j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_Pt600_in_b      ->Fill( jet0sdmass , evWeight );
          else if ( !j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_Pt600_in_q      ->Fill( jet0sdmass , evWeight );
          else if (  j0_match_Wd1 && !j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_Pt600_in_q      ->Fill( jet0sdmass , evWeight );
          else                                                      h_Jet0SDmass_Pt600_unmatched ->Fill( jet0sdmass , evWeight );
             
          h_Jet0Tau32_Pt600_all ->Fill( Jet0Tau32 , evWeight );
          if      (  j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_Pt600_in_qqb    ->Fill( Jet0Tau32 , evWeight );
          else if (  j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_Pt600_in_qq     ->Fill( Jet0Tau32 , evWeight );
          else if (  j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_Pt600_in_qb     ->Fill( Jet0Tau32 , evWeight );
          else if ( !j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_Pt600_in_qb     ->Fill( Jet0Tau32 , evWeight );
          else if ( !j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_Pt600_in_b      ->Fill( Jet0Tau32 , evWeight );
          else if ( !j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_Pt600_in_q      ->Fill( Jet0Tau32 , evWeight );
          else if (  j0_match_Wd1 && !j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_Pt600_in_q      ->Fill( Jet0Tau32 , evWeight );
          else                                                      h_Jet0Tau32_Pt600_unmatched ->Fill( Jet0Tau32 , evWeight );
        }
	
        if (j0_tag_b){
          h_Jet0SDmass_BtagM_all ->Fill( Jet0SDmass , evWeight );
          if      (  j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_BtagM_in_qqb    ->Fill( jet0sdmass , evWeight );
          else if (  j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_BtagM_in_qq     ->Fill( jet0sdmass , evWeight );
          else if (  j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_BtagM_in_qb     ->Fill( jet0sdmass , evWeight );
          else if ( !j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_BtagM_in_qb     ->Fill( jet0sdmass , evWeight );
          else if ( !j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_BtagM_in_b      ->Fill( jet0sdmass , evWeight );
          else if ( !j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_BtagM_in_q      ->Fill( jet0sdmass , evWeight );
          else if (  j0_match_Wd1 && !j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_BtagM_in_q      ->Fill( jet0sdmass , evWeight );
          else                                                      h_Jet0SDmass_BtagM_unmatched ->Fill( jet0sdmass , evWeight );
              
          h_Jet0Tau32_BtagM_all ->Fill( Jet0Tau32 , evWeight );
          if      (  j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_BtagM_in_qqb    ->Fill( Jet0Tau32 , evWeight );
          else if (  j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_BtagM_in_qq     ->Fill( Jet0Tau32 , evWeight );
          else if (  j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_BtagM_in_qb     ->Fill( Jet0Tau32 , evWeight );
          else if ( !j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_BtagM_in_qb     ->Fill( Jet0Tau32 , evWeight );
          else if ( !j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_BtagM_in_b      ->Fill( Jet0Tau32 , evWeight );
          else if ( !j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_BtagM_in_q      ->Fill( Jet0Tau32 , evWeight );
          else if (  j0_match_Wd1 && !j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_BtagM_in_q      ->Fill( Jet0Tau32 , evWeight );
          else                                                      h_Jet0Tau32_BtagM_unmatched ->Fill( Jet0Tau32 , evWeight );
        }

        if (Jet0SDmaxbdisc>0.935){
          h_Jet0SDmass_BtagT_all ->Fill( Jet0SDmass , evWeight );
          if      (  j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_BtagT_in_qqb    ->Fill( jet0sdmass , evWeight );
          else if (  j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_BtagT_in_qq     ->Fill( jet0sdmass , evWeight );
          else if (  j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_BtagT_in_qb     ->Fill( jet0sdmass , evWeight );
          else if ( !j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_BtagT_in_qb     ->Fill( jet0sdmass , evWeight );
          else if ( !j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_BtagT_in_b      ->Fill( jet0sdmass , evWeight );
          else if ( !j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_BtagT_in_q      ->Fill( jet0sdmass , evWeight );
          else if (  j0_match_Wd1 && !j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_BtagT_in_q      ->Fill( jet0sdmass , evWeight );
          else                                                      h_Jet0SDmass_BtagT_unmatched ->Fill( jet0sdmass , evWeight );
        }

        if (j0_tag_tau32){
          h_Jet0SDmass_TauTag_all ->Fill( Jet0SDmass , evWeight );
          if      (  j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_TauTag_in_qqb    ->Fill( jet0sdmass , evWeight );
          else if (  j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_TauTag_in_qq     ->Fill( jet0sdmass , evWeight );
          else if (  j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_TauTag_in_qb     ->Fill( jet0sdmass , evWeight );
          else if ( !j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_TauTag_in_qb     ->Fill( jet0sdmass , evWeight );
          else if ( !j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_TauTag_in_b      ->Fill( jet0sdmass , evWeight );
          else if ( !j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_TauTag_in_q      ->Fill( jet0sdmass , evWeight );
          else if (  j0_match_Wd1 && !j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_TauTag_in_q      ->Fill( jet0sdmass , evWeight );
          else                                                      h_Jet0SDmass_TauTag_unmatched ->Fill( jet0sdmass , evWeight );
        }

        if (!j0_tag_tau32){
          h_Jet0SDmass_AntiTauTag_all ->Fill( Jet0SDmass , evWeight );
          if      (  j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_AntiTauTag_in_qqb    ->Fill( jet0sdmass , evWeight );
          else if (  j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_AntiTauTag_in_qq     ->Fill( jet0sdmass , evWeight );
          else if (  j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_AntiTauTag_in_qb     ->Fill( jet0sdmass , evWeight );
          else if ( !j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_AntiTauTag_in_qb     ->Fill( jet0sdmass , evWeight );
          else if ( !j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_AntiTauTag_in_b      ->Fill( jet0sdmass , evWeight );
          else if ( !j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_AntiTauTag_in_q      ->Fill( jet0sdmass , evWeight );
          else if (  j0_match_Wd1 && !j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_AntiTauTag_in_q      ->Fill( jet0sdmass , evWeight );
          else                                                      h_Jet0SDmass_AntiTauTag_unmatched ->Fill( jet0sdmass , evWeight );
        }

        if (j0_tag_tau32 && j0_tag_b){
          h_Jet0SDmass_BtagM_TauTag_all ->Fill( Jet0SDmass , evWeight );
          if      (  j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_BtagM_TauTag_in_qqb    ->Fill( jet0sdmass , evWeight );
          else if (  j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_BtagM_TauTag_in_qq     ->Fill( jet0sdmass , evWeight );
          else if (  j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_BtagM_TauTag_in_qb     ->Fill( jet0sdmass , evWeight );
          else if ( !j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_BtagM_TauTag_in_qb     ->Fill( jet0sdmass , evWeight );
          else if ( !j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_BtagM_TauTag_in_b      ->Fill( jet0sdmass , evWeight );
          else if ( !j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_BtagM_TauTag_in_q      ->Fill( jet0sdmass , evWeight );
          else if (  j0_match_Wd1 && !j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_BtagM_TauTag_in_q      ->Fill( jet0sdmass , evWeight );
          else                                                      h_Jet0SDmass_BtagM_TauTag_unmatched ->Fill( jet0sdmass , evWeight );
        }

        if (j0_tag_mass ){
          h_Jet0Tau32_MassTag_all ->Fill( Jet0Tau32 , evWeight );
          if      (  j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_MassTag_in_qqb    ->Fill( Jet0Tau32 , evWeight );
          else if (  j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_MassTag_in_qq     ->Fill( Jet0Tau32 , evWeight );
          else if (  j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_MassTag_in_qb     ->Fill( Jet0Tau32 , evWeight );
          else if ( !j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_MassTag_in_qb     ->Fill( Jet0Tau32 , evWeight );
          else if ( !j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_MassTag_in_b      ->Fill( Jet0Tau32 , evWeight );
          else if ( !j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_MassTag_in_q      ->Fill( Jet0Tau32 , evWeight );
          else if (  j0_match_Wd1 && !j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_MassTag_in_q      ->Fill( Jet0Tau32 , evWeight );
          else                                                      h_Jet0Tau32_MassTag_unmatched ->Fill( Jet0Tau32 , evWeight );
        }

        if (j0_tag_b && j0_tag_mass ){
          h_Jet0Tau32_BtagM_MassTag_all ->Fill( Jet0Tau32 , evWeight );
          if      (  j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_BtagM_MassTag_in_qqb    ->Fill( Jet0Tau32 , evWeight );
          else if (  j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_BtagM_MassTag_in_qq     ->Fill( Jet0Tau32 , evWeight );
          else if (  j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_BtagM_MassTag_in_qb     ->Fill( Jet0Tau32 , evWeight );
          else if ( !j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_BtagM_MassTag_in_qb     ->Fill( Jet0Tau32 , evWeight );
          else if ( !j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_BtagM_MassTag_in_b      ->Fill( Jet0Tau32 , evWeight );
          else if ( !j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_BtagM_MassTag_in_q      ->Fill( Jet0Tau32 , evWeight );
          else if (  j0_match_Wd1 && !j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_BtagM_MassTag_in_q      ->Fill( Jet0Tau32 , evWeight );
          else                                                      h_Jet0Tau32_BtagM_MassTag_unmatched ->Fill( Jet0Tau32 , evWeight );
        }
      }
    }//End run_kinematic
  
    // 888888b.   888                    888 8888888888          888    
    // 888  "88b  888                    888 888                 888    
    // 888  .88P  888                    888 888                 888    
    // 8888888K.  888  888  .d88b.   .d88888 8888888    .d8888b  888888 
    // 888  "Y88b 888 .88P d88P"88b d88" 888 888        88K      888    
    // 888    888 888888K  888  888 888  888 888        "Y8888b. 888    
    // 888   d88P 888 "88b Y88b 888 Y88b 888 888             X88 Y88b.  
    // 8888888P"  888  888  "Y88888  "Y88888 8888888888  88888P'  "Y888 
    //                          888                                     
    //                     Y8b d88P                                     
    //                      "Y88P"                                      

    if (run_bkgdest)
    {
      
      //Modmass
      float dijetMass_modMass_jet0      = dijetMass;
      float dijetMass_modMass_jet1      = dijetMass;
      float dijetMass_modMass_flat_jet0 = dijetMass;
      float dijetMass_modMass_flat_jet1 = dijetMass;
      //----- 
      // randomly sample from QCD mass distribution in [110,210] 
      // ROOT.gRandom.SetSeed(0) // make sure =0 -> TRandom3 - Set the random generator sequence if seed is 0 (default value) a TUUID is generated and used to fill the first 8 integers of the seed                      
      TRandom3 gRandom(0);
      double randMass_QCD_Fat_jet0 = h_modMass_SD_jet0->GetRandom();
      double randMass_QCD_Fat_jet1 = h_modMass_SD_jet1->GetRandom();

      // when doing the tag+X bkgd estimate procedure, change the mass of the X jet 
      TLorentzVector jet0P4_modMass = jet0P4;
      TVector3 p_vec_jet0 ( jet0P4_modMass.Px(), jet0P4_modMass.Py(), jet0P4_modMass.Pz());
      jet0P4_modMass.SetVectM( p_vec_jet0, randMass_QCD_Fat_jet0);

      TLorentzVector jet1P4_modMass = jet1P4;
      TVector3 p_vec_jet1 ( jet1P4_modMass.Px(), jet1P4_modMass.Py(), jet1P4_modMass.Pz());
      jet1P4_modMass.SetVectM( p_vec_jet1, randMass_QCD_Fat_jet1);

      // //sample from a uniform distribution in [110,210] 
      TRandom3 rand(0);
      double rand_mass = rand.Uniform(topTagSDwindowLo,topTagSDwindowHi);

      TLorentzVector jet0P4_modMass_flat = jet0P4;
      p_vec_jet0 = TVector3( jet0P4_modMass_flat.Px(), jet0P4_modMass_flat.Py(), jet0P4_modMass_flat.Pz());
      jet0P4_modMass_flat.SetVectM( p_vec_jet0, rand_mass );

      TLorentzVector jet1P4_modMass_flat = jet1P4;
      p_vec_jet1 = TVector3( jet1P4_modMass_flat.Px(), jet1P4_modMass_flat.Py(), jet1P4_modMass_flat.Pz());
      jet1P4_modMass_flat.SetVectM( p_vec_jet1, rand_mass );

      // if jet 0 is outside of the top mass window, force it to have mass in the window 
      if (jet0sdmass < topTagSDwindowLo || jet0sdmass > topTagSDwindowHi){
        dijetMass_modMass_jet0 = (jet1P4 + jet0P4_modMass ).M();
        dijetMass_modMass_flat_jet0 = (jet1P4+ jet0P4_modMass_flat ).M();
      }
      // if jet 1 is outside of the top mass window, force it to have mass in the window 
      if (Jet1SDmass < topTagSDwindowLo || jet1sdmass > topTagSDwindowHi){
        dijetMass_modMass_jet1 = (jet0P4 + jet1P4_modMass ).M();
        dijetMass_modMass_flat_jet1 = (jet0P4+ jet1P4_modMass_flat ).M();
      }

      //Plot some variables
  
      h_DijetMass_modMass_jet0            ->Fill( dijetMass_modMass_jet0    , evWeight );
      h_DijetMass_modMass_jet1            ->Fill( dijetMass_modMass_jet1    , evWeight );


      

      

      //Fill predicted distribution
      TRandom3 rand1(0);
      double rand_bkgdest  = rand1.Uniform(0,1.0);

      //randomly select jet 0 to be the tag then fill predDist based on probability that jet 1 is mis-tagged
      if (rand_bkgdest < 0.5){
        
        // ---- CHS tag definition
        if (j0_tag_t){

          // --- dRapIn
          // -- btag inclusive
          predDist_CHS_dRapIn_inclu_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_tag_t, evWeight );
          predDist_CHS_dRapIn_inclu_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_tag_t, evWeight );
          predDist_CHS_dRapIn_inclu_HT              ->Accumulate(                     ht, jet1P4.P(), j1_tag_t, evWeight );        
          predDist_CHS_dRapIn_inclu_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_tag_t, evWeight ); 
          predDist_CHS_dRapIn_inclu_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_tag_t, evWeight ); 
          predDist_CHS_dRapIn_inclu_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_tag_t, evWeight ); 
          predDist_CHS_dRapIn_inclu_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_tag_t, evWeight ); 
          predDist_CHS_dRapIn_inclu_JetSDmass       ->Accumulate(             jet1sdmass, jet1P4.P(), j1_tag_t, evWeight );
          predDist_CHS_dRapIn_inclu_JetTau32        ->Accumulate(              Jet1Tau32, jet1P4.P(), j1_tag_t, evWeight );
          predDist_CHS_dRapIn_inclu_maxbdisc        ->Accumulate(         Jet1SDmaxbdisc, jet1P4.P(), j1_tag_t, evWeight );
          
          // -- 0btag       
          if (!j0_tag_b && !j1_tag_b){
            predDist_CHS_dRapIn_0btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_tag_t, evWeight );
            predDist_CHS_dRapIn_0btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_tag_t, evWeight );
            predDist_CHS_dRapIn_0btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_tag_t, evWeight );        
            predDist_CHS_dRapIn_0btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_tag_t, evWeight ); 
            predDist_CHS_dRapIn_0btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_tag_t, evWeight ); 
            predDist_CHS_dRapIn_0btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_tag_t, evWeight ); 
            predDist_CHS_dRapIn_0btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_tag_t, evWeight ); 
            predDist_CHS_dRapIn_0btag_JetSDmass       ->Accumulate(             jet1sdmass, jet1P4.P(), j1_tag_t, evWeight );
            predDist_CHS_dRapIn_0btag_JetTau32        ->Accumulate(              Jet1Tau32, jet1P4.P(), j1_tag_t, evWeight );
            predDist_CHS_dRapIn_0btag_maxbdisc        ->Accumulate(         Jet1SDmaxbdisc, jet1P4.P(), j1_tag_t, evWeight );
          }

          // -- 1btag       
          if ((j0_tag_b && !j1_tag_b) || (!j0_tag_b && j1_tag_b)){
            predDist_CHS_dRapIn_1btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_tag_t, evWeight );
            predDist_CHS_dRapIn_1btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_tag_t, evWeight );
            predDist_CHS_dRapIn_1btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_tag_t, evWeight );        
            predDist_CHS_dRapIn_1btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_tag_t, evWeight ); 
            predDist_CHS_dRapIn_1btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_tag_t, evWeight ); 
            predDist_CHS_dRapIn_1btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_tag_t, evWeight ); 
            predDist_CHS_dRapIn_1btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_tag_t, evWeight ); 
            predDist_CHS_dRapIn_1btag_JetSDmass       ->Accumulate(             jet1sdmass, jet1P4.P(), j1_tag_t, evWeight );
            predDist_CHS_dRapIn_1btag_JetTau32        ->Accumulate(              Jet1Tau32, jet1P4.P(), j1_tag_t, evWeight );
            predDist_CHS_dRapIn_1btag_maxbdisc        ->Accumulate(         Jet1SDmaxbdisc, jet1P4.P(), j1_tag_t, evWeight );
          }

          // -- 2btag         
          if (j0_tag_b && j1_tag_b){
            predDist_CHS_dRapIn_2btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_tag_t, evWeight );
            predDist_CHS_dRapIn_2btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_tag_t, evWeight );
            predDist_CHS_dRapIn_2btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_tag_t, evWeight );        
            predDist_CHS_dRapIn_2btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_tag_t, evWeight ); 
            predDist_CHS_dRapIn_2btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_tag_t, evWeight ); 
            predDist_CHS_dRapIn_2btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_tag_t, evWeight ); 
            predDist_CHS_dRapIn_2btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_tag_t, evWeight ); 
            predDist_CHS_dRapIn_2btag_JetSDmass       ->Accumulate(             jet1sdmass, jet1P4.P(), j1_tag_t, evWeight );
            predDist_CHS_dRapIn_2btag_JetTau32        ->Accumulate(              Jet1Tau32, jet1P4.P(), j1_tag_t, evWeight );
            predDist_CHS_dRapIn_2btag_maxbdisc        ->Accumulate(         Jet1SDmaxbdisc, jet1P4.P(), j1_tag_t, evWeight );
          }
          
          // --- dRapHi
          if (DijetDeltaRap >= 1){

            // -- btag inclusive
            predDist_CHS_dRapHi_inclu_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_tag_t, evWeight );
            predDist_CHS_dRapHi_inclu_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_tag_t, evWeight );
            predDist_CHS_dRapHi_inclu_HT              ->Accumulate(                     ht, jet1P4.P(), j1_tag_t, evWeight );        
            predDist_CHS_dRapHi_inclu_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_tag_t, evWeight ); 
            predDist_CHS_dRapHi_inclu_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_tag_t, evWeight ); 
            predDist_CHS_dRapHi_inclu_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_tag_t, evWeight ); 
            predDist_CHS_dRapHi_inclu_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_tag_t, evWeight ); 
            predDist_CHS_dRapHi_inclu_JetSDmass       ->Accumulate(             jet1sdmass, jet1P4.P(), j1_tag_t, evWeight );
            predDist_CHS_dRapHi_inclu_JetTau32        ->Accumulate(              Jet1Tau32, jet1P4.P(), j1_tag_t, evWeight );
            predDist_CHS_dRapHi_inclu_maxbdisc        ->Accumulate(         Jet1SDmaxbdisc, jet1P4.P(), j1_tag_t, evWeight );
            
            // -- 0btag       
            if (!j0_tag_b && !j1_tag_b){
              predDist_CHS_dRapHi_0btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_tag_t, evWeight );
              predDist_CHS_dRapHi_0btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_tag_t, evWeight );
              predDist_CHS_dRapHi_0btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_tag_t, evWeight );        
              predDist_CHS_dRapHi_0btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_tag_t, evWeight ); 
              predDist_CHS_dRapHi_0btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_tag_t, evWeight ); 
              predDist_CHS_dRapHi_0btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_tag_t, evWeight ); 
              predDist_CHS_dRapHi_0btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_tag_t, evWeight ); 
              predDist_CHS_dRapHi_0btag_JetSDmass       ->Accumulate(             jet1sdmass, jet1P4.P(), j1_tag_t, evWeight );
              predDist_CHS_dRapHi_0btag_JetTau32        ->Accumulate(              Jet1Tau32, jet1P4.P(), j1_tag_t, evWeight );
              predDist_CHS_dRapHi_0btag_maxbdisc        ->Accumulate(         Jet1SDmaxbdisc, jet1P4.P(), j1_tag_t, evWeight );
            }

            // -- 1btag       
            if ((j0_tag_b && !j1_tag_b) || (!j0_tag_b && j1_tag_b)){
              predDist_CHS_dRapHi_1btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_tag_t, evWeight );
              predDist_CHS_dRapHi_1btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_tag_t, evWeight );
              predDist_CHS_dRapHi_1btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_tag_t, evWeight );        
              predDist_CHS_dRapHi_1btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_tag_t, evWeight ); 
              predDist_CHS_dRapHi_1btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_tag_t, evWeight ); 
              predDist_CHS_dRapHi_1btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_tag_t, evWeight ); 
              predDist_CHS_dRapHi_1btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_tag_t, evWeight ); 
              predDist_CHS_dRapHi_1btag_JetSDmass       ->Accumulate(             jet1sdmass, jet1P4.P(), j1_tag_t, evWeight );
              predDist_CHS_dRapHi_1btag_JetTau32        ->Accumulate(              Jet1Tau32, jet1P4.P(), j1_tag_t, evWeight );
              predDist_CHS_dRapHi_1btag_maxbdisc        ->Accumulate(         Jet1SDmaxbdisc, jet1P4.P(), j1_tag_t, evWeight );
            }

            // -- 2btag         
            if (j0_tag_b && j1_tag_b){
              predDist_CHS_dRapHi_2btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_tag_t, evWeight );
              predDist_CHS_dRapHi_2btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_tag_t, evWeight );
              predDist_CHS_dRapHi_2btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_tag_t, evWeight );        
              predDist_CHS_dRapHi_2btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_tag_t, evWeight ); 
              predDist_CHS_dRapHi_2btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_tag_t, evWeight ); 
              predDist_CHS_dRapHi_2btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_tag_t, evWeight ); 
              predDist_CHS_dRapHi_2btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_tag_t, evWeight ); 
              predDist_CHS_dRapHi_2btag_JetSDmass       ->Accumulate(             jet1sdmass, jet1P4.P(), j1_tag_t, evWeight );
              predDist_CHS_dRapHi_2btag_JetTau32        ->Accumulate(              Jet1Tau32, jet1P4.P(), j1_tag_t, evWeight );
              predDist_CHS_dRapHi_2btag_maxbdisc        ->Accumulate(         Jet1SDmaxbdisc, jet1P4.P(), j1_tag_t, evWeight );
            }
          }
          // --- dRapLo
          if (DijetDeltaRap < 1){
            
            // -- btag inclusive
            predDist_CHS_dRapLo_inclu_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_tag_t, evWeight );
            predDist_CHS_dRapLo_inclu_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_tag_t, evWeight );
            predDist_CHS_dRapLo_inclu_HT              ->Accumulate(                     ht, jet1P4.P(), j1_tag_t, evWeight );        
            predDist_CHS_dRapLo_inclu_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_tag_t, evWeight ); 
            predDist_CHS_dRapLo_inclu_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_tag_t, evWeight ); 
            predDist_CHS_dRapLo_inclu_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_tag_t, evWeight ); 
            predDist_CHS_dRapLo_inclu_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_tag_t, evWeight ); 
            predDist_CHS_dRapLo_inclu_JetSDmass       ->Accumulate(             jet1sdmass, jet1P4.P(), j1_tag_t, evWeight );
            predDist_CHS_dRapLo_inclu_JetTau32        ->Accumulate(              Jet1Tau32, jet1P4.P(), j1_tag_t, evWeight );
            predDist_CHS_dRapLo_inclu_maxbdisc        ->Accumulate(         Jet1SDmaxbdisc, jet1P4.P(), j1_tag_t, evWeight );
            
            // -- 0btag       
            if (!j0_tag_b && !j1_tag_b){
              predDist_CHS_dRapLo_0btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_tag_t, evWeight );
              predDist_CHS_dRapLo_0btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_tag_t, evWeight );
              predDist_CHS_dRapLo_0btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_tag_t, evWeight );        
              predDist_CHS_dRapLo_0btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_tag_t, evWeight ); 
              predDist_CHS_dRapLo_0btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_tag_t, evWeight ); 
              predDist_CHS_dRapLo_0btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_tag_t, evWeight ); 
              predDist_CHS_dRapLo_0btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_tag_t, evWeight ); 
              predDist_CHS_dRapLo_0btag_JetSDmass       ->Accumulate(             jet1sdmass, jet1P4.P(), j1_tag_t, evWeight );
              predDist_CHS_dRapLo_0btag_JetTau32        ->Accumulate(              Jet1Tau32, jet1P4.P(), j1_tag_t, evWeight );
              predDist_CHS_dRapLo_0btag_maxbdisc        ->Accumulate(         Jet1SDmaxbdisc, jet1P4.P(), j1_tag_t, evWeight );
            }

            // -- 1btag       
            if ((j0_tag_b && !j1_tag_b) || (!j0_tag_b && j1_tag_b)){
              predDist_CHS_dRapLo_1btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_tag_t, evWeight );
              predDist_CHS_dRapLo_1btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_tag_t, evWeight );
              predDist_CHS_dRapLo_1btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_tag_t, evWeight );        
              predDist_CHS_dRapLo_1btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_tag_t, evWeight ); 
              predDist_CHS_dRapLo_1btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_tag_t, evWeight ); 
              predDist_CHS_dRapLo_1btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_tag_t, evWeight ); 
              predDist_CHS_dRapLo_1btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_tag_t, evWeight ); 
              predDist_CHS_dRapLo_1btag_JetSDmass       ->Accumulate(             jet1sdmass, jet1P4.P(), j1_tag_t, evWeight );
              predDist_CHS_dRapLo_1btag_JetTau32        ->Accumulate(              Jet1Tau32, jet1P4.P(), j1_tag_t, evWeight );
              predDist_CHS_dRapLo_1btag_maxbdisc        ->Accumulate(         Jet1SDmaxbdisc, jet1P4.P(), j1_tag_t, evWeight );
            }

            // -- 2btag         
            if (j0_tag_b && j1_tag_b){
              predDist_CHS_dRapLo_2btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_tag_t, evWeight );
              predDist_CHS_dRapLo_2btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_tag_t, evWeight );
              predDist_CHS_dRapLo_2btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_tag_t, evWeight );        
              predDist_CHS_dRapLo_2btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_tag_t, evWeight ); 
              predDist_CHS_dRapLo_2btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_tag_t, evWeight ); 
              predDist_CHS_dRapLo_2btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_tag_t, evWeight ); 
              predDist_CHS_dRapLo_2btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_tag_t, evWeight ); 
              predDist_CHS_dRapLo_2btag_JetSDmass       ->Accumulate(             jet1sdmass, jet1P4.P(), j1_tag_t, evWeight );
              predDist_CHS_dRapLo_2btag_JetTau32        ->Accumulate(              Jet1Tau32, jet1P4.P(), j1_tag_t, evWeight );
              predDist_CHS_dRapLo_2btag_maxbdisc        ->Accumulate(         Jet1SDmaxbdisc, jet1P4.P(), j1_tag_t, evWeight );
            }
          }
        } // end if chs jet 0 tagged

        // ---- Puppi tag definition
        if (j0_puptag_t){
          // --- dRapIn
          // -- btag inclusive
          predDist_Puppi_dRapIn_inclu_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_puptag_t, evWeight );
          predDist_Puppi_dRapIn_inclu_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_puptag_t, evWeight );
          predDist_Puppi_dRapIn_inclu_HT              ->Accumulate(                     ht, jet1P4.P(), j1_puptag_t, evWeight );        
          predDist_Puppi_dRapIn_inclu_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_puptag_t, evWeight ); 
          predDist_Puppi_dRapIn_inclu_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_puptag_t, evWeight ); 
          predDist_Puppi_dRapIn_inclu_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_puptag_t, evWeight ); 
          predDist_Puppi_dRapIn_inclu_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_puptag_t, evWeight ); 
          predDist_Puppi_dRapIn_inclu_JetSDmass       ->Accumulate(           puppi1sdmass, jet1P4.P(), j1_puptag_t, evWeight );
          predDist_Puppi_dRapIn_inclu_JetTau32        ->Accumulate(         Jet1PuppiTau32, jet1P4.P(), j1_puptag_t, evWeight );
          predDist_Puppi_dRapIn_inclu_maxbdisc        ->Accumulate(    Jet1PuppiSDmaxbdisc, jet1P4.P(), j1_puptag_t, evWeight );
        
          // -- 0btag       
          if (!j0_puptag_b && !j1_puptag_b){
            predDist_Puppi_dRapIn_0btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_puptag_t, evWeight );
            predDist_Puppi_dRapIn_0btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_puptag_t, evWeight );
            predDist_Puppi_dRapIn_0btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_puptag_t, evWeight );        
            predDist_Puppi_dRapIn_0btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_puptag_t, evWeight ); 
            predDist_Puppi_dRapIn_0btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_puptag_t, evWeight ); 
            predDist_Puppi_dRapIn_0btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_puptag_t, evWeight ); 
            predDist_Puppi_dRapIn_0btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_puptag_t, evWeight ); 
            predDist_Puppi_dRapIn_0btag_JetSDmass       ->Accumulate(           puppi1sdmass, jet1P4.P(), j1_puptag_t, evWeight );
            predDist_Puppi_dRapIn_0btag_JetTau32        ->Accumulate(         Jet1PuppiTau32, jet1P4.P(), j1_puptag_t, evWeight );
            predDist_Puppi_dRapIn_0btag_maxbdisc        ->Accumulate(    Jet1PuppiSDmaxbdisc, jet1P4.P(), j1_puptag_t, evWeight );
          }

          // -- 1btag       
          if ((j0_puptag_b && !j1_puptag_b) || (!j0_puptag_b && j1_puptag_b)){
            predDist_Puppi_dRapIn_1btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_puptag_t, evWeight );
            predDist_Puppi_dRapIn_1btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_puptag_t, evWeight );
            predDist_Puppi_dRapIn_1btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_puptag_t, evWeight );        
            predDist_Puppi_dRapIn_1btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_puptag_t, evWeight ); 
            predDist_Puppi_dRapIn_1btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_puptag_t, evWeight ); 
            predDist_Puppi_dRapIn_1btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_puptag_t, evWeight ); 
            predDist_Puppi_dRapIn_1btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_puptag_t, evWeight ); 
            predDist_Puppi_dRapIn_1btag_JetSDmass       ->Accumulate(           puppi1sdmass, jet1P4.P(), j1_puptag_t, evWeight );
            predDist_Puppi_dRapIn_1btag_JetTau32        ->Accumulate(         Jet1PuppiTau32, jet1P4.P(), j1_puptag_t, evWeight );
            predDist_Puppi_dRapIn_1btag_maxbdisc        ->Accumulate(    Jet1PuppiSDmaxbdisc, jet1P4.P(), j1_puptag_t, evWeight );
          }

          // -- 2btag         
          if (j0_puptag_b && j1_puptag_b){
            predDist_Puppi_dRapIn_2btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_puptag_t, evWeight );
            predDist_Puppi_dRapIn_2btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_puptag_t, evWeight );
            predDist_Puppi_dRapIn_2btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_puptag_t, evWeight );        
            predDist_Puppi_dRapIn_2btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_puptag_t, evWeight ); 
            predDist_Puppi_dRapIn_2btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_puptag_t, evWeight ); 
            predDist_Puppi_dRapIn_2btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_puptag_t, evWeight ); 
            predDist_Puppi_dRapIn_2btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_puptag_t, evWeight ); 
            predDist_Puppi_dRapIn_2btag_JetSDmass       ->Accumulate(           puppi1sdmass, jet1P4.P(), j1_puptag_t, evWeight );
            predDist_Puppi_dRapIn_2btag_JetTau32        ->Accumulate(         Jet1PuppiTau32, jet1P4.P(), j1_puptag_t, evWeight );
            predDist_Puppi_dRapIn_2btag_maxbdisc        ->Accumulate(    Jet1PuppiSDmaxbdisc, jet1P4.P(), j1_puptag_t, evWeight );
          }
          
          // --- dRapHi
          if (DijetDeltaRap >= 1){

            // -- btag inclusive
            predDist_Puppi_dRapHi_inclu_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_puptag_t, evWeight );
            predDist_Puppi_dRapHi_inclu_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_puptag_t, evWeight );
            predDist_Puppi_dRapHi_inclu_HT              ->Accumulate(                     ht, jet1P4.P(), j1_puptag_t, evWeight );        
            predDist_Puppi_dRapHi_inclu_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_puptag_t, evWeight ); 
            predDist_Puppi_dRapHi_inclu_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_puptag_t, evWeight ); 
            predDist_Puppi_dRapHi_inclu_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_puptag_t, evWeight ); 
            predDist_Puppi_dRapHi_inclu_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_puptag_t, evWeight ); 
            predDist_Puppi_dRapHi_inclu_JetSDmass       ->Accumulate(           puppi1sdmass, jet1P4.P(), j1_puptag_t, evWeight );
            predDist_Puppi_dRapHi_inclu_JetTau32        ->Accumulate(         Jet1PuppiTau32, jet1P4.P(), j1_puptag_t, evWeight );
            predDist_Puppi_dRapHi_inclu_maxbdisc        ->Accumulate(    Jet1PuppiSDmaxbdisc, jet1P4.P(), j1_puptag_t, evWeight );
            
            // -- 0btag       
            if (!j0_puptag_b && !j1_puptag_b){
              predDist_Puppi_dRapHi_0btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_puptag_t, evWeight );
              predDist_Puppi_dRapHi_0btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_puptag_t, evWeight );
              predDist_Puppi_dRapHi_0btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_puptag_t, evWeight );        
              predDist_Puppi_dRapHi_0btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_puptag_t, evWeight ); 
              predDist_Puppi_dRapHi_0btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_puptag_t, evWeight ); 
              predDist_Puppi_dRapHi_0btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_puptag_t, evWeight ); 
              predDist_Puppi_dRapHi_0btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_puptag_t, evWeight ); 
              predDist_Puppi_dRapHi_0btag_JetSDmass       ->Accumulate(           puppi1sdmass, jet1P4.P(), j1_puptag_t, evWeight );
              predDist_Puppi_dRapHi_0btag_JetTau32        ->Accumulate(         Jet1PuppiTau32, jet1P4.P(), j1_puptag_t, evWeight );
              predDist_Puppi_dRapHi_0btag_maxbdisc        ->Accumulate(    Jet1PuppiSDmaxbdisc, jet1P4.P(), j1_puptag_t, evWeight );
            }

            // -- 1btag       
            if ((j0_puptag_b && !j1_puptag_b) || (!j0_puptag_b && j1_puptag_b)){
              predDist_Puppi_dRapHi_1btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_puptag_t, evWeight );
              predDist_Puppi_dRapHi_1btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_puptag_t, evWeight );
              predDist_Puppi_dRapHi_1btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_puptag_t, evWeight );        
              predDist_Puppi_dRapHi_1btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_puptag_t, evWeight ); 
              predDist_Puppi_dRapHi_1btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_puptag_t, evWeight ); 
              predDist_Puppi_dRapHi_1btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_puptag_t, evWeight ); 
              predDist_Puppi_dRapHi_1btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_puptag_t, evWeight ); 
              predDist_Puppi_dRapHi_1btag_JetSDmass       ->Accumulate(           puppi1sdmass, jet1P4.P(), j1_puptag_t, evWeight );
              predDist_Puppi_dRapHi_1btag_JetTau32        ->Accumulate(         Jet1PuppiTau32, jet1P4.P(), j1_puptag_t, evWeight );
              predDist_Puppi_dRapHi_1btag_maxbdisc        ->Accumulate(    Jet1PuppiSDmaxbdisc, jet1P4.P(), j1_puptag_t, evWeight );
            }

            // -- 2btag         
            if (j0_puptag_b && j1_puptag_b){
              predDist_Puppi_dRapHi_2btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_puptag_t, evWeight );
              predDist_Puppi_dRapHi_2btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_puptag_t, evWeight );
              predDist_Puppi_dRapHi_2btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_puptag_t, evWeight );        
              predDist_Puppi_dRapHi_2btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_puptag_t, evWeight ); 
              predDist_Puppi_dRapHi_2btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_puptag_t, evWeight ); 
              predDist_Puppi_dRapHi_2btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_puptag_t, evWeight ); 
              predDist_Puppi_dRapHi_2btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_puptag_t, evWeight ); 
              predDist_Puppi_dRapHi_2btag_JetSDmass       ->Accumulate(           puppi1sdmass, jet1P4.P(), j1_puptag_t, evWeight );
              predDist_Puppi_dRapHi_2btag_JetTau32        ->Accumulate(         Jet1PuppiTau32, jet1P4.P(), j1_puptag_t, evWeight );
              predDist_Puppi_dRapHi_2btag_maxbdisc        ->Accumulate(    Jet1PuppiSDmaxbdisc, jet1P4.P(), j1_puptag_t, evWeight );
            }
          }
          // --- dRapLo
          if (DijetDeltaRap < 1){
            
            // -- btag inclusive
            predDist_Puppi_dRapLo_inclu_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_puptag_t, evWeight );
            predDist_Puppi_dRapLo_inclu_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_puptag_t, evWeight );
            predDist_Puppi_dRapLo_inclu_HT              ->Accumulate(                     ht, jet1P4.P(), j1_puptag_t, evWeight );        
            predDist_Puppi_dRapLo_inclu_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_puptag_t, evWeight ); 
            predDist_Puppi_dRapLo_inclu_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_puptag_t, evWeight ); 
            predDist_Puppi_dRapLo_inclu_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_puptag_t, evWeight ); 
            predDist_Puppi_dRapLo_inclu_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_puptag_t, evWeight ); 
            predDist_Puppi_dRapLo_inclu_JetSDmass       ->Accumulate(           puppi1sdmass, jet1P4.P(), j1_puptag_t, evWeight );
            predDist_Puppi_dRapLo_inclu_JetTau32        ->Accumulate(         Jet1PuppiTau32, jet1P4.P(), j1_puptag_t, evWeight );
            predDist_Puppi_dRapLo_inclu_maxbdisc        ->Accumulate(    Jet1PuppiSDmaxbdisc, jet1P4.P(), j1_puptag_t, evWeight );
            
            // -- 0btag       
            if (!j0_puptag_b && !j1_puptag_b){
              predDist_Puppi_dRapLo_0btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_puptag_t, evWeight );
              predDist_Puppi_dRapLo_0btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_puptag_t, evWeight );
              predDist_Puppi_dRapLo_0btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_puptag_t, evWeight );        
              predDist_Puppi_dRapLo_0btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_puptag_t, evWeight ); 
              predDist_Puppi_dRapLo_0btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_puptag_t, evWeight ); 
              predDist_Puppi_dRapLo_0btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_puptag_t, evWeight ); 
              predDist_Puppi_dRapLo_0btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_puptag_t, evWeight ); 
              predDist_Puppi_dRapLo_0btag_JetSDmass       ->Accumulate(           puppi1sdmass, jet1P4.P(), j1_puptag_t, evWeight );
              predDist_Puppi_dRapLo_0btag_JetTau32        ->Accumulate(         Jet1PuppiTau32, jet1P4.P(), j1_puptag_t, evWeight );
              predDist_Puppi_dRapLo_0btag_maxbdisc        ->Accumulate(    Jet1PuppiSDmaxbdisc, jet1P4.P(), j1_puptag_t, evWeight );
            }

            // -- 1btag       
            if ((j0_puptag_b && !j1_puptag_b) || (!j0_puptag_b && j1_puptag_b)){
              predDist_Puppi_dRapLo_1btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_puptag_t, evWeight );
              predDist_Puppi_dRapLo_1btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_puptag_t, evWeight );
              predDist_Puppi_dRapLo_1btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_puptag_t, evWeight );        
              predDist_Puppi_dRapLo_1btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_puptag_t, evWeight ); 
              predDist_Puppi_dRapLo_1btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_puptag_t, evWeight ); 
              predDist_Puppi_dRapLo_1btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_puptag_t, evWeight ); 
              predDist_Puppi_dRapLo_1btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_puptag_t, evWeight ); 
              predDist_Puppi_dRapLo_1btag_JetSDmass       ->Accumulate(           puppi1sdmass, jet1P4.P(), j1_puptag_t, evWeight );
              predDist_Puppi_dRapLo_1btag_JetTau32        ->Accumulate(         Jet1PuppiTau32, jet1P4.P(), j1_puptag_t, evWeight );
              predDist_Puppi_dRapLo_1btag_maxbdisc        ->Accumulate(    Jet1PuppiSDmaxbdisc, jet1P4.P(), j1_puptag_t, evWeight );
            }

            // -- 2btag         
            if (j0_puptag_b && j1_puptag_b){
              predDist_Puppi_dRapLo_2btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_puptag_t, evWeight );
              predDist_Puppi_dRapLo_2btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_puptag_t, evWeight );
              predDist_Puppi_dRapLo_2btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_puptag_t, evWeight );        
              predDist_Puppi_dRapLo_2btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_puptag_t, evWeight ); 
              predDist_Puppi_dRapLo_2btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_puptag_t, evWeight ); 
              predDist_Puppi_dRapLo_2btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_puptag_t, evWeight ); 
              predDist_Puppi_dRapLo_2btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_puptag_t, evWeight ); 
              predDist_Puppi_dRapLo_2btag_JetSDmass       ->Accumulate(           puppi1sdmass, jet1P4.P(), j1_puptag_t, evWeight );
              predDist_Puppi_dRapLo_2btag_JetTau32        ->Accumulate(         Jet1PuppiTau32, jet1P4.P(), j1_puptag_t, evWeight );
              predDist_Puppi_dRapLo_2btag_maxbdisc        ->Accumulate(    Jet1PuppiSDmaxbdisc, jet1P4.P(), j1_puptag_t, evWeight );
            }
          }
        } // end if puppi jet 0 tagged

        // ---- Closure test - alternative tag definition
        if (j0_tag_alt_t){

          // --- dRapIn
          // -- btag inclusive
          predDist_AltTag_dRapIn_inclu_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_tag_alt_t, evWeight );
          predDist_AltTag_dRapIn_inclu_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_tag_alt_t, evWeight );
          predDist_AltTag_dRapIn_inclu_HT              ->Accumulate(                     ht, jet1P4.P(), j1_tag_alt_t, evWeight );        
          predDist_AltTag_dRapIn_inclu_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_tag_alt_t, evWeight ); 
          predDist_AltTag_dRapIn_inclu_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
          predDist_AltTag_dRapIn_inclu_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
          predDist_AltTag_dRapIn_inclu_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
          predDist_AltTag_dRapIn_inclu_JetSDmass       ->Accumulate(             jet1sdmass, jet1P4.P(), j1_tag_alt_t, evWeight );
          predDist_AltTag_dRapIn_inclu_JetTau32        ->Accumulate(              Jet1Tau32, jet1P4.P(), j1_tag_alt_t, evWeight );
          predDist_AltTag_dRapIn_inclu_maxbdisc        ->Accumulate(         Jet1SDmaxbdisc, jet1P4.P(), j1_tag_alt_t, evWeight );
          
          // -- 0btag       
          if (!j0_tag_b && !j1_tag_b){
            predDist_AltTag_dRapIn_0btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_tag_alt_t, evWeight );
            predDist_AltTag_dRapIn_0btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_tag_alt_t, evWeight );
            predDist_AltTag_dRapIn_0btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_tag_alt_t, evWeight );        
            predDist_AltTag_dRapIn_0btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapIn_0btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapIn_0btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapIn_0btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapIn_0btag_JetSDmass       ->Accumulate(             jet1sdmass, jet1P4.P(), j1_tag_alt_t, evWeight );
            predDist_AltTag_dRapIn_0btag_JetTau32        ->Accumulate(              Jet1Tau32, jet1P4.P(), j1_tag_alt_t, evWeight );
            predDist_AltTag_dRapIn_0btag_maxbdisc        ->Accumulate(         Jet1SDmaxbdisc, jet1P4.P(), j1_tag_alt_t, evWeight );
          }

          // -- 1btag       
          if ((j0_tag_b && !j1_tag_b) || (!j0_tag_b && j1_tag_b)){
            predDist_AltTag_dRapIn_1btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_tag_alt_t, evWeight );
            predDist_AltTag_dRapIn_1btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_tag_alt_t, evWeight );
            predDist_AltTag_dRapIn_1btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_tag_alt_t, evWeight );        
            predDist_AltTag_dRapIn_1btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapIn_1btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapIn_1btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapIn_1btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapIn_1btag_JetSDmass       ->Accumulate(             jet1sdmass, jet1P4.P(), j1_tag_alt_t, evWeight );
            predDist_AltTag_dRapIn_1btag_JetTau32        ->Accumulate(              Jet1Tau32, jet1P4.P(), j1_tag_alt_t, evWeight );
            predDist_AltTag_dRapIn_1btag_maxbdisc        ->Accumulate(         Jet1SDmaxbdisc, jet1P4.P(), j1_tag_alt_t, evWeight );
          }

          // -- 2btag         
          if (j0_tag_b && j1_tag_b){
            predDist_AltTag_dRapIn_2btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_tag_alt_t, evWeight );
            predDist_AltTag_dRapIn_2btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_tag_alt_t, evWeight );
            predDist_AltTag_dRapIn_2btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_tag_alt_t, evWeight );        
            predDist_AltTag_dRapIn_2btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapIn_2btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapIn_2btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapIn_2btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapIn_2btag_JetSDmass       ->Accumulate(             jet1sdmass, jet1P4.P(), j1_tag_alt_t, evWeight );
            predDist_AltTag_dRapIn_2btag_JetTau32        ->Accumulate(              Jet1Tau32, jet1P4.P(), j1_tag_alt_t, evWeight );
            predDist_AltTag_dRapIn_2btag_maxbdisc        ->Accumulate(         Jet1SDmaxbdisc, jet1P4.P(), j1_tag_alt_t, evWeight );
          }
          
          // --- dRapHi
          if (DijetDeltaRap >= 1){

            // -- btag inclusive
            predDist_AltTag_dRapHi_inclu_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_tag_alt_t, evWeight );
            predDist_AltTag_dRapHi_inclu_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_tag_alt_t, evWeight );
            predDist_AltTag_dRapHi_inclu_HT              ->Accumulate(                     ht, jet1P4.P(), j1_tag_alt_t, evWeight );        
            predDist_AltTag_dRapHi_inclu_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapHi_inclu_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapHi_inclu_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapHi_inclu_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapHi_inclu_JetSDmass       ->Accumulate(             jet1sdmass, jet1P4.P(), j1_tag_alt_t, evWeight );
            predDist_AltTag_dRapHi_inclu_JetTau32        ->Accumulate(              Jet1Tau32, jet1P4.P(), j1_tag_alt_t, evWeight );
            predDist_AltTag_dRapHi_inclu_maxbdisc        ->Accumulate(         Jet1SDmaxbdisc, jet1P4.P(), j1_tag_alt_t, evWeight );
            
            // -- 0btag       
            if (!j0_tag_b && !j1_tag_b){
              predDist_AltTag_dRapHi_0btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_tag_alt_t, evWeight );
              predDist_AltTag_dRapHi_0btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_tag_alt_t, evWeight );
              predDist_AltTag_dRapHi_0btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_tag_alt_t, evWeight );        
              predDist_AltTag_dRapHi_0btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapHi_0btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapHi_0btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapHi_0btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapHi_0btag_JetSDmass       ->Accumulate(             jet1sdmass, jet1P4.P(), j1_tag_alt_t, evWeight );
              predDist_AltTag_dRapHi_0btag_JetTau32        ->Accumulate(              Jet1Tau32, jet1P4.P(), j1_tag_alt_t, evWeight );
              predDist_AltTag_dRapHi_0btag_maxbdisc        ->Accumulate(         Jet1SDmaxbdisc, jet1P4.P(), j1_tag_alt_t, evWeight );
            }

            // -- 1btag       
            if ((j0_tag_b && !j1_tag_b) || (!j0_tag_b && j1_tag_b)){
              predDist_AltTag_dRapHi_1btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_tag_alt_t, evWeight );
              predDist_AltTag_dRapHi_1btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_tag_alt_t, evWeight );
              predDist_AltTag_dRapHi_1btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_tag_alt_t, evWeight );        
              predDist_AltTag_dRapHi_1btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapHi_1btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapHi_1btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapHi_1btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapHi_1btag_JetSDmass       ->Accumulate(             jet1sdmass, jet1P4.P(), j1_tag_alt_t, evWeight );
              predDist_AltTag_dRapHi_1btag_JetTau32        ->Accumulate(              Jet1Tau32, jet1P4.P(), j1_tag_alt_t, evWeight );
              predDist_AltTag_dRapHi_1btag_maxbdisc        ->Accumulate(         Jet1SDmaxbdisc, jet1P4.P(), j1_tag_alt_t, evWeight );
            }

            // -- 2btag         
            if (j0_tag_b && j1_tag_b){
              predDist_AltTag_dRapHi_2btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_tag_alt_t, evWeight );
              predDist_AltTag_dRapHi_2btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_tag_alt_t, evWeight );
              predDist_AltTag_dRapHi_2btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_tag_alt_t, evWeight );        
              predDist_AltTag_dRapHi_2btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapHi_2btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapHi_2btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapHi_2btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapHi_2btag_JetSDmass       ->Accumulate(             jet1sdmass, jet1P4.P(), j1_tag_alt_t, evWeight );
              predDist_AltTag_dRapHi_2btag_JetTau32        ->Accumulate(              Jet1Tau32, jet1P4.P(), j1_tag_alt_t, evWeight );
              predDist_AltTag_dRapHi_2btag_maxbdisc        ->Accumulate(         Jet1SDmaxbdisc, jet1P4.P(), j1_tag_alt_t, evWeight );
            }
          }
          // --- dRapLo
          if (DijetDeltaRap < 1){
            
            // -- btag inclusive
            predDist_AltTag_dRapLo_inclu_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_tag_alt_t, evWeight );
            predDist_AltTag_dRapLo_inclu_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_tag_alt_t, evWeight );
            predDist_AltTag_dRapLo_inclu_HT              ->Accumulate(                     ht, jet1P4.P(), j1_tag_alt_t, evWeight );        
            predDist_AltTag_dRapLo_inclu_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapLo_inclu_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapLo_inclu_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapLo_inclu_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapLo_inclu_JetSDmass       ->Accumulate(             jet1sdmass, jet1P4.P(), j1_tag_alt_t, evWeight );
            predDist_AltTag_dRapLo_inclu_JetTau32        ->Accumulate(              Jet1Tau32, jet1P4.P(), j1_tag_alt_t, evWeight );
            predDist_AltTag_dRapLo_inclu_maxbdisc        ->Accumulate(         Jet1SDmaxbdisc, jet1P4.P(), j1_tag_alt_t, evWeight );
            
            // -- 0btag       
            if (!j0_tag_b && !j1_tag_b){
              predDist_AltTag_dRapLo_0btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_tag_alt_t, evWeight );
              predDist_AltTag_dRapLo_0btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_tag_alt_t, evWeight );
              predDist_AltTag_dRapLo_0btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_tag_alt_t, evWeight );        
              predDist_AltTag_dRapLo_0btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapLo_0btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapLo_0btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapLo_0btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapLo_0btag_JetSDmass       ->Accumulate(             jet1sdmass, jet1P4.P(), j1_tag_alt_t, evWeight );
              predDist_AltTag_dRapLo_0btag_JetTau32        ->Accumulate(              Jet1Tau32, jet1P4.P(), j1_tag_alt_t, evWeight );
              predDist_AltTag_dRapLo_0btag_maxbdisc        ->Accumulate(         Jet1SDmaxbdisc, jet1P4.P(), j1_tag_alt_t, evWeight );
            }

            // -- 1btag       
            if ((j0_tag_b && !j1_tag_b) || (!j0_tag_b && j1_tag_b)){
              predDist_AltTag_dRapLo_1btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_tag_alt_t, evWeight );
              predDist_AltTag_dRapLo_1btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_tag_alt_t, evWeight );
              predDist_AltTag_dRapLo_1btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_tag_alt_t, evWeight );        
              predDist_AltTag_dRapLo_1btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapLo_1btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapLo_1btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapLo_1btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapLo_1btag_JetSDmass       ->Accumulate(             jet1sdmass, jet1P4.P(), j1_tag_alt_t, evWeight );
              predDist_AltTag_dRapLo_1btag_JetTau32        ->Accumulate(              Jet1Tau32, jet1P4.P(), j1_tag_alt_t, evWeight );
              predDist_AltTag_dRapLo_1btag_maxbdisc        ->Accumulate(         Jet1SDmaxbdisc, jet1P4.P(), j1_tag_alt_t, evWeight );
            }

            // -- 2btag         
            if (j0_tag_b && j1_tag_b){
              predDist_AltTag_dRapLo_2btag_DijetMass       ->Accumulate(              dijetMass, jet1P4.P(), j1_tag_alt_t, evWeight );
              predDist_AltTag_dRapLo_2btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet1, jet1P4.P(), j1_tag_alt_t, evWeight );
              predDist_AltTag_dRapLo_2btag_HT              ->Accumulate(                     ht, jet1P4.P(), j1_tag_alt_t, evWeight );        
              predDist_AltTag_dRapLo_2btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet1P4.P(), j1_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapLo_2btag_JetP            ->Accumulate(             jet1P4.P(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapLo_2btag_JetPt           ->Accumulate(          jet1P4.Perp(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapLo_2btag_JetY            ->Accumulate(      jet1P4.Rapidity(), jet1P4.P(), j1_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapLo_2btag_JetSDmass       ->Accumulate(             jet1sdmass, jet1P4.P(), j1_tag_alt_t, evWeight );
              predDist_AltTag_dRapLo_2btag_JetTau32        ->Accumulate(              Jet1Tau32, jet1P4.P(), j1_tag_alt_t, evWeight );
              predDist_AltTag_dRapLo_2btag_maxbdisc        ->Accumulate(         Jet1SDmaxbdisc, jet1P4.P(), j1_tag_alt_t, evWeight );
            }
          }
        } // end if alternative tag (sideband) jet 0 tagged


      } // end random # < 0.5

      //randomly select jet 1 to be the tag then fill predDist based on probability that jet 0 is mis-tagged
      if (rand_bkgdest >= 0.5){
    
       
        // ---- CHS tag definition
        if (j1_tag_t){

          // --- dRapIn
          // -- btag inclusive
          predDist_CHS_dRapIn_inclu_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_tag_t, evWeight );
          predDist_CHS_dRapIn_inclu_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_tag_t, evWeight );
          predDist_CHS_dRapIn_inclu_HT              ->Accumulate(                     ht, jet0P4.P(), j0_tag_t, evWeight );        
          predDist_CHS_dRapIn_inclu_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_tag_t, evWeight ); 
          predDist_CHS_dRapIn_inclu_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_tag_t, evWeight ); 
          predDist_CHS_dRapIn_inclu_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_tag_t, evWeight ); 
          predDist_CHS_dRapIn_inclu_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_tag_t, evWeight ); 
          predDist_CHS_dRapIn_inclu_JetSDmass       ->Accumulate(             jet0sdmass, jet0P4.P(), j0_tag_t, evWeight );
          predDist_CHS_dRapIn_inclu_JetTau32        ->Accumulate(              Jet0Tau32, jet0P4.P(), j0_tag_t, evWeight );
          predDist_CHS_dRapIn_inclu_maxbdisc        ->Accumulate(         Jet0SDmaxbdisc, jet0P4.P(), j0_tag_t, evWeight );
          
          // -- 0btag       
          if (!j0_tag_b && !j1_tag_b){
            predDist_CHS_dRapIn_0btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_tag_t, evWeight );
            predDist_CHS_dRapIn_0btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_tag_t, evWeight );
            predDist_CHS_dRapIn_0btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_tag_t, evWeight );        
            predDist_CHS_dRapIn_0btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_tag_t, evWeight ); 
            predDist_CHS_dRapIn_0btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_tag_t, evWeight ); 
            predDist_CHS_dRapIn_0btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_tag_t, evWeight ); 
            predDist_CHS_dRapIn_0btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_tag_t, evWeight ); 
            predDist_CHS_dRapIn_0btag_JetSDmass       ->Accumulate(             jet0sdmass, jet0P4.P(), j0_tag_t, evWeight );
            predDist_CHS_dRapIn_0btag_JetTau32        ->Accumulate(              Jet0Tau32, jet0P4.P(), j0_tag_t, evWeight );
            predDist_CHS_dRapIn_0btag_maxbdisc        ->Accumulate(         Jet0SDmaxbdisc, jet0P4.P(), j0_tag_t, evWeight );
          }

          // -- 1btag       
          if ((j0_tag_b && !j1_tag_b) || (!j0_tag_b && j1_tag_b)){
            predDist_CHS_dRapIn_1btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_tag_t, evWeight );
            predDist_CHS_dRapIn_1btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_tag_t, evWeight );
            predDist_CHS_dRapIn_1btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_tag_t, evWeight );        
            predDist_CHS_dRapIn_1btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_tag_t, evWeight ); 
            predDist_CHS_dRapIn_1btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_tag_t, evWeight ); 
            predDist_CHS_dRapIn_1btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_tag_t, evWeight ); 
            predDist_CHS_dRapIn_1btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_tag_t, evWeight ); 
            predDist_CHS_dRapIn_1btag_JetSDmass       ->Accumulate(             jet0sdmass, jet0P4.P(), j0_tag_t, evWeight );
            predDist_CHS_dRapIn_1btag_JetTau32        ->Accumulate(              Jet0Tau32, jet0P4.P(), j0_tag_t, evWeight );
            predDist_CHS_dRapIn_1btag_maxbdisc        ->Accumulate(         Jet0SDmaxbdisc, jet0P4.P(), j0_tag_t, evWeight );
          }

          // -- 2btag         
          if (j0_tag_b && j1_tag_b){
            predDist_CHS_dRapIn_2btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_tag_t, evWeight );
            predDist_CHS_dRapIn_2btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_tag_t, evWeight );
            predDist_CHS_dRapIn_2btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_tag_t, evWeight );        
            predDist_CHS_dRapIn_2btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_tag_t, evWeight ); 
            predDist_CHS_dRapIn_2btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_tag_t, evWeight ); 
            predDist_CHS_dRapIn_2btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_tag_t, evWeight ); 
            predDist_CHS_dRapIn_2btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_tag_t, evWeight ); 
            predDist_CHS_dRapIn_2btag_JetSDmass       ->Accumulate(             jet0sdmass, jet0P4.P(), j0_tag_t, evWeight );
            predDist_CHS_dRapIn_2btag_JetTau32        ->Accumulate(              Jet0Tau32, jet0P4.P(), j0_tag_t, evWeight );
            predDist_CHS_dRapIn_2btag_maxbdisc        ->Accumulate(         Jet0SDmaxbdisc, jet0P4.P(), j0_tag_t, evWeight );
          }
          
          // --- dRapHi
          if (DijetDeltaRap >= 1){

            // -- btag inclusive
            predDist_CHS_dRapHi_inclu_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_tag_t, evWeight );
            predDist_CHS_dRapHi_inclu_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_tag_t, evWeight );
            predDist_CHS_dRapHi_inclu_HT              ->Accumulate(                     ht, jet0P4.P(), j0_tag_t, evWeight );        
            predDist_CHS_dRapHi_inclu_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_tag_t, evWeight ); 
            predDist_CHS_dRapHi_inclu_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_tag_t, evWeight ); 
            predDist_CHS_dRapHi_inclu_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_tag_t, evWeight ); 
            predDist_CHS_dRapHi_inclu_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_tag_t, evWeight ); 
            predDist_CHS_dRapHi_inclu_JetSDmass       ->Accumulate(             jet0sdmass, jet0P4.P(), j0_tag_t, evWeight );
            predDist_CHS_dRapHi_inclu_JetTau32        ->Accumulate(              Jet0Tau32, jet0P4.P(), j0_tag_t, evWeight );
            predDist_CHS_dRapHi_inclu_maxbdisc        ->Accumulate(         Jet0SDmaxbdisc, jet0P4.P(), j0_tag_t, evWeight );
            
            // -- 0btag       
            if (!j0_tag_b && !j1_tag_b){
              predDist_CHS_dRapHi_0btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_tag_t, evWeight );
              predDist_CHS_dRapHi_0btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_tag_t, evWeight );
              predDist_CHS_dRapHi_0btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_tag_t, evWeight );        
              predDist_CHS_dRapHi_0btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_tag_t, evWeight ); 
              predDist_CHS_dRapHi_0btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_tag_t, evWeight ); 
              predDist_CHS_dRapHi_0btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_tag_t, evWeight ); 
              predDist_CHS_dRapHi_0btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_tag_t, evWeight ); 
              predDist_CHS_dRapHi_0btag_JetSDmass       ->Accumulate(             jet0sdmass, jet0P4.P(), j0_tag_t, evWeight );
              predDist_CHS_dRapHi_0btag_JetTau32        ->Accumulate(              Jet0Tau32, jet0P4.P(), j0_tag_t, evWeight );
              predDist_CHS_dRapHi_0btag_maxbdisc        ->Accumulate(         Jet0SDmaxbdisc, jet0P4.P(), j0_tag_t, evWeight );
            }

            // -- 1btag       
            if ((j0_tag_b && !j1_tag_b) || (!j0_tag_b && j1_tag_b)){
              predDist_CHS_dRapHi_1btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_tag_t, evWeight );
              predDist_CHS_dRapHi_1btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_tag_t, evWeight );
              predDist_CHS_dRapHi_1btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_tag_t, evWeight );        
              predDist_CHS_dRapHi_1btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_tag_t, evWeight ); 
              predDist_CHS_dRapHi_1btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_tag_t, evWeight ); 
              predDist_CHS_dRapHi_1btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_tag_t, evWeight ); 
              predDist_CHS_dRapHi_1btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_tag_t, evWeight ); 
              predDist_CHS_dRapHi_1btag_JetSDmass       ->Accumulate(             jet0sdmass, jet0P4.P(), j0_tag_t, evWeight );
              predDist_CHS_dRapHi_1btag_JetTau32        ->Accumulate(              Jet0Tau32, jet0P4.P(), j0_tag_t, evWeight );
              predDist_CHS_dRapHi_1btag_maxbdisc        ->Accumulate(         Jet0SDmaxbdisc, jet0P4.P(), j0_tag_t, evWeight );
            }

            // -- 2btag         
            if (j0_tag_b && j1_tag_b){
              predDist_CHS_dRapHi_2btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_tag_t, evWeight );
              predDist_CHS_dRapHi_2btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_tag_t, evWeight );
              predDist_CHS_dRapHi_2btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_tag_t, evWeight );        
              predDist_CHS_dRapHi_2btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_tag_t, evWeight ); 
              predDist_CHS_dRapHi_2btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_tag_t, evWeight ); 
              predDist_CHS_dRapHi_2btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_tag_t, evWeight ); 
              predDist_CHS_dRapHi_2btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_tag_t, evWeight ); 
              predDist_CHS_dRapHi_2btag_JetSDmass       ->Accumulate(             jet0sdmass, jet0P4.P(), j0_tag_t, evWeight );
              predDist_CHS_dRapHi_2btag_JetTau32        ->Accumulate(              Jet0Tau32, jet0P4.P(), j0_tag_t, evWeight );
              predDist_CHS_dRapHi_2btag_maxbdisc        ->Accumulate(         Jet0SDmaxbdisc, jet0P4.P(), j0_tag_t, evWeight );
            }
          }
          // --- dRapLo
          if (DijetDeltaRap < 1){
            
            // -- btag inclusive
            predDist_CHS_dRapLo_inclu_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_tag_t, evWeight );
            predDist_CHS_dRapLo_inclu_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_tag_t, evWeight );
            predDist_CHS_dRapLo_inclu_HT              ->Accumulate(                     ht, jet0P4.P(), j0_tag_t, evWeight );        
            predDist_CHS_dRapLo_inclu_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_tag_t, evWeight ); 
            predDist_CHS_dRapLo_inclu_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_tag_t, evWeight ); 
            predDist_CHS_dRapLo_inclu_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_tag_t, evWeight ); 
            predDist_CHS_dRapLo_inclu_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_tag_t, evWeight ); 
            predDist_CHS_dRapLo_inclu_JetSDmass       ->Accumulate(             jet0sdmass, jet0P4.P(), j0_tag_t, evWeight );
            predDist_CHS_dRapLo_inclu_JetTau32        ->Accumulate(              Jet0Tau32, jet0P4.P(), j0_tag_t, evWeight );
            predDist_CHS_dRapLo_inclu_maxbdisc        ->Accumulate(         Jet0SDmaxbdisc, jet0P4.P(), j0_tag_t, evWeight );
            
            // -- 0btag       
            if (!j0_tag_b && !j1_tag_b){
              predDist_CHS_dRapLo_0btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_tag_t, evWeight );
              predDist_CHS_dRapLo_0btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_tag_t, evWeight );
              predDist_CHS_dRapLo_0btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_tag_t, evWeight );        
              predDist_CHS_dRapLo_0btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_tag_t, evWeight ); 
              predDist_CHS_dRapLo_0btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_tag_t, evWeight ); 
              predDist_CHS_dRapLo_0btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_tag_t, evWeight ); 
              predDist_CHS_dRapLo_0btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_tag_t, evWeight ); 
              predDist_CHS_dRapLo_0btag_JetSDmass       ->Accumulate(             jet0sdmass, jet0P4.P(), j0_tag_t, evWeight );
              predDist_CHS_dRapLo_0btag_JetTau32        ->Accumulate(              Jet0Tau32, jet0P4.P(), j0_tag_t, evWeight );
              predDist_CHS_dRapLo_0btag_maxbdisc        ->Accumulate(         Jet0SDmaxbdisc, jet0P4.P(), j0_tag_t, evWeight );
            }

            // -- 1btag       
            if ((j0_tag_b && !j1_tag_b) || (!j0_tag_b && j1_tag_b)){
              predDist_CHS_dRapLo_1btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_tag_t, evWeight );
              predDist_CHS_dRapLo_1btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_tag_t, evWeight );
              predDist_CHS_dRapLo_1btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_tag_t, evWeight );        
              predDist_CHS_dRapLo_1btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_tag_t, evWeight ); 
              predDist_CHS_dRapLo_1btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_tag_t, evWeight ); 
              predDist_CHS_dRapLo_1btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_tag_t, evWeight ); 
              predDist_CHS_dRapLo_1btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_tag_t, evWeight ); 
              predDist_CHS_dRapLo_1btag_JetSDmass       ->Accumulate(             jet0sdmass, jet0P4.P(), j0_tag_t, evWeight );
              predDist_CHS_dRapLo_1btag_JetTau32        ->Accumulate(              Jet0Tau32, jet0P4.P(), j0_tag_t, evWeight );
              predDist_CHS_dRapLo_1btag_maxbdisc        ->Accumulate(         Jet0SDmaxbdisc, jet0P4.P(), j0_tag_t, evWeight );
            }

            // -- 2btag         
            if (j0_tag_b && j1_tag_b){
              predDist_CHS_dRapLo_2btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_tag_t, evWeight );
              predDist_CHS_dRapLo_2btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_tag_t, evWeight );
              predDist_CHS_dRapLo_2btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_tag_t, evWeight );        
              predDist_CHS_dRapLo_2btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_tag_t, evWeight ); 
              predDist_CHS_dRapLo_2btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_tag_t, evWeight ); 
              predDist_CHS_dRapLo_2btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_tag_t, evWeight ); 
              predDist_CHS_dRapLo_2btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_tag_t, evWeight ); 
              predDist_CHS_dRapLo_2btag_JetSDmass       ->Accumulate(             jet0sdmass, jet0P4.P(), j0_tag_t, evWeight );
              predDist_CHS_dRapLo_2btag_JetTau32        ->Accumulate(              Jet0Tau32, jet0P4.P(), j0_tag_t, evWeight );
              predDist_CHS_dRapLo_2btag_maxbdisc        ->Accumulate(         Jet0SDmaxbdisc, jet0P4.P(), j0_tag_t, evWeight );
            }
          }
        } // end if chs jet 1 tagged

        // ---- Puppi tag definition
        if (j1_puptag_t){
          // --- dRapIn
          // -- btag inclusive
          predDist_Puppi_dRapIn_inclu_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_puptag_t, evWeight );
          predDist_Puppi_dRapIn_inclu_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_puptag_t, evWeight );
          predDist_Puppi_dRapIn_inclu_HT              ->Accumulate(                     ht, jet0P4.P(), j0_puptag_t, evWeight );        
          predDist_Puppi_dRapIn_inclu_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_puptag_t, evWeight ); 
          predDist_Puppi_dRapIn_inclu_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_puptag_t, evWeight ); 
          predDist_Puppi_dRapIn_inclu_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_puptag_t, evWeight ); 
          predDist_Puppi_dRapIn_inclu_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_puptag_t, evWeight ); 
          predDist_Puppi_dRapIn_inclu_JetSDmass       ->Accumulate(           puppi1sdmass, jet0P4.P(), j0_puptag_t, evWeight );
          predDist_Puppi_dRapIn_inclu_JetTau32        ->Accumulate(         Jet0PuppiTau32, jet0P4.P(), j0_puptag_t, evWeight );
          predDist_Puppi_dRapIn_inclu_maxbdisc        ->Accumulate(    Jet0PuppiSDmaxbdisc, jet0P4.P(), j0_puptag_t, evWeight );
         
          // -- 0btag       
          if (!j0_puptag_b && !j1_puptag_b){
            predDist_Puppi_dRapIn_0btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_puptag_t, evWeight );
            predDist_Puppi_dRapIn_0btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_puptag_t, evWeight );
            predDist_Puppi_dRapIn_0btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_puptag_t, evWeight );        
            predDist_Puppi_dRapIn_0btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_puptag_t, evWeight ); 
            predDist_Puppi_dRapIn_0btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_puptag_t, evWeight ); 
            predDist_Puppi_dRapIn_0btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_puptag_t, evWeight ); 
            predDist_Puppi_dRapIn_0btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_puptag_t, evWeight ); 
            predDist_Puppi_dRapIn_0btag_JetSDmass       ->Accumulate(           puppi1sdmass, jet0P4.P(), j0_puptag_t, evWeight );
            predDist_Puppi_dRapIn_0btag_JetTau32        ->Accumulate(         Jet0PuppiTau32, jet0P4.P(), j0_puptag_t, evWeight );
            predDist_Puppi_dRapIn_0btag_maxbdisc        ->Accumulate(    Jet0PuppiSDmaxbdisc, jet0P4.P(), j0_puptag_t, evWeight );
          }

          // -- 1btag       
          if ((j0_puptag_b && !j1_puptag_b) || (!j0_puptag_b && j1_puptag_b)){
            predDist_Puppi_dRapIn_1btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_puptag_t, evWeight );
            predDist_Puppi_dRapIn_1btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_puptag_t, evWeight );
            predDist_Puppi_dRapIn_1btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_puptag_t, evWeight );        
            predDist_Puppi_dRapIn_1btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_puptag_t, evWeight ); 
            predDist_Puppi_dRapIn_1btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_puptag_t, evWeight ); 
            predDist_Puppi_dRapIn_1btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_puptag_t, evWeight ); 
            predDist_Puppi_dRapIn_1btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_puptag_t, evWeight ); 
            predDist_Puppi_dRapIn_1btag_JetSDmass       ->Accumulate(           puppi1sdmass, jet0P4.P(), j0_puptag_t, evWeight );
            predDist_Puppi_dRapIn_1btag_JetTau32        ->Accumulate(         Jet0PuppiTau32, jet0P4.P(), j0_puptag_t, evWeight );
            predDist_Puppi_dRapIn_1btag_maxbdisc        ->Accumulate(    Jet0PuppiSDmaxbdisc, jet0P4.P(), j0_puptag_t, evWeight );
          }

          // -- 2btag         
          if (j0_puptag_b && j1_puptag_b){
            predDist_Puppi_dRapIn_2btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_puptag_t, evWeight );
            predDist_Puppi_dRapIn_2btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_puptag_t, evWeight );
            predDist_Puppi_dRapIn_2btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_puptag_t, evWeight );        
            predDist_Puppi_dRapIn_2btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_puptag_t, evWeight ); 
            predDist_Puppi_dRapIn_2btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_puptag_t, evWeight ); 
            predDist_Puppi_dRapIn_2btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_puptag_t, evWeight ); 
            predDist_Puppi_dRapIn_2btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_puptag_t, evWeight ); 
            predDist_Puppi_dRapIn_2btag_JetSDmass       ->Accumulate(           puppi1sdmass, jet0P4.P(), j0_puptag_t, evWeight );
            predDist_Puppi_dRapIn_2btag_JetTau32        ->Accumulate(         Jet0PuppiTau32, jet0P4.P(), j0_puptag_t, evWeight );
            predDist_Puppi_dRapIn_2btag_maxbdisc        ->Accumulate(    Jet0PuppiSDmaxbdisc, jet0P4.P(), j0_puptag_t, evWeight );
          }
          
          // --- dRapHi
          if (DijetDeltaRap >= 1){

            // -- btag inclusive
            predDist_Puppi_dRapHi_inclu_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_puptag_t, evWeight );
            predDist_Puppi_dRapHi_inclu_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_puptag_t, evWeight );
            predDist_Puppi_dRapHi_inclu_HT              ->Accumulate(                     ht, jet0P4.P(), j0_puptag_t, evWeight );        
            predDist_Puppi_dRapHi_inclu_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_puptag_t, evWeight ); 
            predDist_Puppi_dRapHi_inclu_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_puptag_t, evWeight ); 
            predDist_Puppi_dRapHi_inclu_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_puptag_t, evWeight ); 
            predDist_Puppi_dRapHi_inclu_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_puptag_t, evWeight ); 
            predDist_Puppi_dRapHi_inclu_JetSDmass       ->Accumulate(           puppi1sdmass, jet0P4.P(), j0_puptag_t, evWeight );
            predDist_Puppi_dRapHi_inclu_JetTau32        ->Accumulate(         Jet0PuppiTau32, jet0P4.P(), j0_puptag_t, evWeight );
            predDist_Puppi_dRapHi_inclu_maxbdisc        ->Accumulate(    Jet0PuppiSDmaxbdisc, jet0P4.P(), j0_puptag_t, evWeight );
            
            // -- 0btag       
            if (!j0_puptag_b && !j1_puptag_b){
              predDist_Puppi_dRapHi_0btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_puptag_t, evWeight );
              predDist_Puppi_dRapHi_0btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_puptag_t, evWeight );
              predDist_Puppi_dRapHi_0btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_puptag_t, evWeight );        
              predDist_Puppi_dRapHi_0btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_puptag_t, evWeight ); 
              predDist_Puppi_dRapHi_0btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_puptag_t, evWeight ); 
              predDist_Puppi_dRapHi_0btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_puptag_t, evWeight ); 
              predDist_Puppi_dRapHi_0btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_puptag_t, evWeight ); 
              predDist_Puppi_dRapHi_0btag_JetSDmass       ->Accumulate(           puppi1sdmass, jet0P4.P(), j0_puptag_t, evWeight );
              predDist_Puppi_dRapHi_0btag_JetTau32        ->Accumulate(         Jet0PuppiTau32, jet0P4.P(), j0_puptag_t, evWeight );
              predDist_Puppi_dRapHi_0btag_maxbdisc        ->Accumulate(    Jet0PuppiSDmaxbdisc, jet0P4.P(), j0_puptag_t, evWeight );
            }

            // -- 1btag       
            if ((j0_puptag_b && !j1_puptag_b) || (!j0_puptag_b && j1_puptag_b)){
              predDist_Puppi_dRapHi_1btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_puptag_t, evWeight );
              predDist_Puppi_dRapHi_1btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_puptag_t, evWeight );
              predDist_Puppi_dRapHi_1btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_puptag_t, evWeight );        
              predDist_Puppi_dRapHi_1btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_puptag_t, evWeight ); 
              predDist_Puppi_dRapHi_1btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_puptag_t, evWeight ); 
              predDist_Puppi_dRapHi_1btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_puptag_t, evWeight ); 
              predDist_Puppi_dRapHi_1btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_puptag_t, evWeight ); 
              predDist_Puppi_dRapHi_1btag_JetSDmass       ->Accumulate(           puppi1sdmass, jet0P4.P(), j0_puptag_t, evWeight );
              predDist_Puppi_dRapHi_1btag_JetTau32        ->Accumulate(         Jet0PuppiTau32, jet0P4.P(), j0_puptag_t, evWeight );
              predDist_Puppi_dRapHi_1btag_maxbdisc        ->Accumulate(    Jet0PuppiSDmaxbdisc, jet0P4.P(), j0_puptag_t, evWeight );
            }

            // -- 2btag         
            if (j0_puptag_b && j1_puptag_b){
              predDist_Puppi_dRapHi_2btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_puptag_t, evWeight );
              predDist_Puppi_dRapHi_2btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_puptag_t, evWeight );
              predDist_Puppi_dRapHi_2btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_puptag_t, evWeight );        
              predDist_Puppi_dRapHi_2btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_puptag_t, evWeight ); 
              predDist_Puppi_dRapHi_2btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_puptag_t, evWeight ); 
              predDist_Puppi_dRapHi_2btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_puptag_t, evWeight ); 
              predDist_Puppi_dRapHi_2btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_puptag_t, evWeight ); 
              predDist_Puppi_dRapHi_2btag_JetSDmass       ->Accumulate(           puppi1sdmass, jet0P4.P(), j0_puptag_t, evWeight );
              predDist_Puppi_dRapHi_2btag_JetTau32        ->Accumulate(         Jet0PuppiTau32, jet0P4.P(), j0_puptag_t, evWeight );
              predDist_Puppi_dRapHi_2btag_maxbdisc        ->Accumulate(    Jet0PuppiSDmaxbdisc, jet0P4.P(), j0_puptag_t, evWeight );
            }
          }
          // --- dRapLo
          if (DijetDeltaRap < 1){
            
            // -- btag inclusive
            predDist_Puppi_dRapLo_inclu_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_puptag_t, evWeight );
            predDist_Puppi_dRapLo_inclu_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_puptag_t, evWeight );
            predDist_Puppi_dRapLo_inclu_HT              ->Accumulate(                     ht, jet0P4.P(), j0_puptag_t, evWeight );        
            predDist_Puppi_dRapLo_inclu_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_puptag_t, evWeight ); 
            predDist_Puppi_dRapLo_inclu_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_puptag_t, evWeight ); 
            predDist_Puppi_dRapLo_inclu_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_puptag_t, evWeight ); 
            predDist_Puppi_dRapLo_inclu_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_puptag_t, evWeight ); 
            predDist_Puppi_dRapLo_inclu_JetSDmass       ->Accumulate(           puppi1sdmass, jet0P4.P(), j0_puptag_t, evWeight );
            predDist_Puppi_dRapLo_inclu_JetTau32        ->Accumulate(         Jet0PuppiTau32, jet0P4.P(), j0_puptag_t, evWeight );
            predDist_Puppi_dRapLo_inclu_maxbdisc        ->Accumulate(    Jet0PuppiSDmaxbdisc, jet0P4.P(), j0_puptag_t, evWeight );
            
            // -- 0btag       
            if (!j0_puptag_b && !j1_puptag_b){
              predDist_Puppi_dRapLo_0btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_puptag_t, evWeight );
              predDist_Puppi_dRapLo_0btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_puptag_t, evWeight );
              predDist_Puppi_dRapLo_0btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_puptag_t, evWeight );        
              predDist_Puppi_dRapLo_0btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_puptag_t, evWeight ); 
              predDist_Puppi_dRapLo_0btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_puptag_t, evWeight ); 
              predDist_Puppi_dRapLo_0btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_puptag_t, evWeight ); 
              predDist_Puppi_dRapLo_0btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_puptag_t, evWeight ); 
              predDist_Puppi_dRapLo_0btag_JetSDmass       ->Accumulate(           puppi1sdmass, jet0P4.P(), j0_puptag_t, evWeight );
              predDist_Puppi_dRapLo_0btag_JetTau32        ->Accumulate(         Jet0PuppiTau32, jet0P4.P(), j0_puptag_t, evWeight );
              predDist_Puppi_dRapLo_0btag_maxbdisc        ->Accumulate(    Jet0PuppiSDmaxbdisc, jet0P4.P(), j0_puptag_t, evWeight );
            }

            // -- 1btag       
            if ((j0_puptag_b && !j1_puptag_b) || (!j0_puptag_b && j1_puptag_b)){
              predDist_Puppi_dRapLo_1btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_puptag_t, evWeight );
              predDist_Puppi_dRapLo_1btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_puptag_t, evWeight );
              predDist_Puppi_dRapLo_1btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_puptag_t, evWeight );        
              predDist_Puppi_dRapLo_1btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_puptag_t, evWeight ); 
              predDist_Puppi_dRapLo_1btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_puptag_t, evWeight ); 
              predDist_Puppi_dRapLo_1btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_puptag_t, evWeight ); 
              predDist_Puppi_dRapLo_1btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_puptag_t, evWeight ); 
              predDist_Puppi_dRapLo_1btag_JetSDmass       ->Accumulate(           puppi1sdmass, jet0P4.P(), j0_puptag_t, evWeight );
              predDist_Puppi_dRapLo_1btag_JetTau32        ->Accumulate(         Jet0PuppiTau32, jet0P4.P(), j0_puptag_t, evWeight );
              predDist_Puppi_dRapLo_1btag_maxbdisc        ->Accumulate(    Jet0PuppiSDmaxbdisc, jet0P4.P(), j0_puptag_t, evWeight );
            }

            // -- 2btag         
            if (j0_puptag_b && j1_puptag_b){
              predDist_Puppi_dRapLo_2btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_puptag_t, evWeight );
              predDist_Puppi_dRapLo_2btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_puptag_t, evWeight );
              predDist_Puppi_dRapLo_2btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_puptag_t, evWeight );        
              predDist_Puppi_dRapLo_2btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_puptag_t, evWeight ); 
              predDist_Puppi_dRapLo_2btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_puptag_t, evWeight ); 
              predDist_Puppi_dRapLo_2btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_puptag_t, evWeight ); 
              predDist_Puppi_dRapLo_2btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_puptag_t, evWeight ); 
              predDist_Puppi_dRapLo_2btag_JetSDmass       ->Accumulate(           puppi1sdmass, jet0P4.P(), j0_puptag_t, evWeight );
              predDist_Puppi_dRapLo_2btag_JetTau32        ->Accumulate(         Jet0PuppiTau32, jet0P4.P(), j0_puptag_t, evWeight );
              predDist_Puppi_dRapLo_2btag_maxbdisc        ->Accumulate(    Jet0PuppiSDmaxbdisc, jet0P4.P(), j0_puptag_t, evWeight );
            }
          }
        } // end if puppi jet 1 tagged

        // ---- Closure test - alternative tag definition
        if (j1_tag_alt_t){

          // --- dRapIn
          // -- btag inclusive
          predDist_AltTag_dRapIn_inclu_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_tag_alt_t, evWeight );
          predDist_AltTag_dRapIn_inclu_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_tag_alt_t, evWeight );
          predDist_AltTag_dRapIn_inclu_HT              ->Accumulate(                     ht, jet0P4.P(), j0_tag_alt_t, evWeight );        
          predDist_AltTag_dRapIn_inclu_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_tag_alt_t, evWeight ); 
          predDist_AltTag_dRapIn_inclu_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
          predDist_AltTag_dRapIn_inclu_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
          predDist_AltTag_dRapIn_inclu_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
          predDist_AltTag_dRapIn_inclu_JetSDmass       ->Accumulate(             jet0sdmass, jet0P4.P(), j0_tag_alt_t, evWeight );
          predDist_AltTag_dRapIn_inclu_JetTau32        ->Accumulate(              Jet0Tau32, jet0P4.P(), j0_tag_alt_t, evWeight );
          predDist_AltTag_dRapIn_inclu_maxbdisc        ->Accumulate(         Jet0SDmaxbdisc, jet0P4.P(), j0_tag_alt_t, evWeight );
          
          // -- 0btag       
          if (!j0_tag_b && !j1_tag_b){
            predDist_AltTag_dRapIn_0btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_tag_alt_t, evWeight );
            predDist_AltTag_dRapIn_0btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_tag_alt_t, evWeight );
            predDist_AltTag_dRapIn_0btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_tag_alt_t, evWeight );        
            predDist_AltTag_dRapIn_0btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapIn_0btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapIn_0btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapIn_0btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapIn_0btag_JetSDmass       ->Accumulate(             jet0sdmass, jet0P4.P(), j0_tag_alt_t, evWeight );
            predDist_AltTag_dRapIn_0btag_JetTau32        ->Accumulate(              Jet0Tau32, jet0P4.P(), j0_tag_alt_t, evWeight );
            predDist_AltTag_dRapIn_0btag_maxbdisc        ->Accumulate(         Jet0SDmaxbdisc, jet0P4.P(), j0_tag_alt_t, evWeight );
          }

          // -- 1btag       
          if ((j0_tag_b && !j1_tag_b) || (!j0_tag_b && j1_tag_b)){
            predDist_AltTag_dRapIn_1btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_tag_alt_t, evWeight );
            predDist_AltTag_dRapIn_1btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_tag_alt_t, evWeight );
            predDist_AltTag_dRapIn_1btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_tag_alt_t, evWeight );        
            predDist_AltTag_dRapIn_1btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapIn_1btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapIn_1btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapIn_1btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapIn_1btag_JetSDmass       ->Accumulate(             jet0sdmass, jet0P4.P(), j0_tag_alt_t, evWeight );
            predDist_AltTag_dRapIn_1btag_JetTau32        ->Accumulate(              Jet0Tau32, jet0P4.P(), j0_tag_alt_t, evWeight );
            predDist_AltTag_dRapIn_1btag_maxbdisc        ->Accumulate(         Jet0SDmaxbdisc, jet0P4.P(), j0_tag_alt_t, evWeight );
          }

          // -- 2btag         
          if (j0_tag_b && j1_tag_b){
            predDist_AltTag_dRapIn_2btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_tag_alt_t, evWeight );
            predDist_AltTag_dRapIn_2btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_tag_alt_t, evWeight );
            predDist_AltTag_dRapIn_2btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_tag_alt_t, evWeight );        
            predDist_AltTag_dRapIn_2btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapIn_2btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapIn_2btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapIn_2btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapIn_2btag_JetSDmass       ->Accumulate(             jet0sdmass, jet0P4.P(), j0_tag_alt_t, evWeight );
            predDist_AltTag_dRapIn_2btag_JetTau32        ->Accumulate(              Jet0Tau32, jet0P4.P(), j0_tag_alt_t, evWeight );
            predDist_AltTag_dRapIn_2btag_maxbdisc        ->Accumulate(         Jet0SDmaxbdisc, jet0P4.P(), j0_tag_alt_t, evWeight );
          }
          
          // --- dRapHi
          if (DijetDeltaRap >= 1){

            // -- btag inclusive
            predDist_AltTag_dRapHi_inclu_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_tag_alt_t, evWeight );
            predDist_AltTag_dRapHi_inclu_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_tag_alt_t, evWeight );
            predDist_AltTag_dRapHi_inclu_HT              ->Accumulate(                     ht, jet0P4.P(), j0_tag_alt_t, evWeight );        
            predDist_AltTag_dRapHi_inclu_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapHi_inclu_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapHi_inclu_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapHi_inclu_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapHi_inclu_JetSDmass       ->Accumulate(             jet0sdmass, jet0P4.P(), j0_tag_alt_t, evWeight );
            predDist_AltTag_dRapHi_inclu_JetTau32        ->Accumulate(              Jet0Tau32, jet0P4.P(), j0_tag_alt_t, evWeight );
            predDist_AltTag_dRapHi_inclu_maxbdisc        ->Accumulate(         Jet0SDmaxbdisc, jet0P4.P(), j0_tag_alt_t, evWeight );
            
            // -- 0btag       
            if (!j0_tag_b && !j1_tag_b){
              predDist_AltTag_dRapHi_0btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_tag_alt_t, evWeight );
              predDist_AltTag_dRapHi_0btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_tag_alt_t, evWeight );
              predDist_AltTag_dRapHi_0btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_tag_alt_t, evWeight );        
              predDist_AltTag_dRapHi_0btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapHi_0btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapHi_0btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapHi_0btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapHi_0btag_JetSDmass       ->Accumulate(             jet0sdmass, jet0P4.P(), j0_tag_alt_t, evWeight );
              predDist_AltTag_dRapHi_0btag_JetTau32        ->Accumulate(              Jet0Tau32, jet0P4.P(), j0_tag_alt_t, evWeight );
              predDist_AltTag_dRapHi_0btag_maxbdisc        ->Accumulate(         Jet0SDmaxbdisc, jet0P4.P(), j0_tag_alt_t, evWeight );
            }

            // -- 1btag       
            if ((j0_tag_b && !j1_tag_b) || (!j0_tag_b && j1_tag_b)){
              predDist_AltTag_dRapHi_1btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_tag_alt_t, evWeight );
              predDist_AltTag_dRapHi_1btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_tag_alt_t, evWeight );
              predDist_AltTag_dRapHi_1btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_tag_alt_t, evWeight );        
              predDist_AltTag_dRapHi_1btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapHi_1btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapHi_1btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapHi_1btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapHi_1btag_JetSDmass       ->Accumulate(             jet0sdmass, jet0P4.P(), j0_tag_alt_t, evWeight );
              predDist_AltTag_dRapHi_1btag_JetTau32        ->Accumulate(              Jet0Tau32, jet0P4.P(), j0_tag_alt_t, evWeight );
              predDist_AltTag_dRapHi_1btag_maxbdisc        ->Accumulate(         Jet0SDmaxbdisc, jet0P4.P(), j0_tag_alt_t, evWeight );
            }

            // -- 2btag         
            if (j0_tag_b && j1_tag_b){
              predDist_AltTag_dRapHi_2btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_tag_alt_t, evWeight );
              predDist_AltTag_dRapHi_2btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_tag_alt_t, evWeight );
              predDist_AltTag_dRapHi_2btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_tag_alt_t, evWeight );        
              predDist_AltTag_dRapHi_2btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapHi_2btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapHi_2btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapHi_2btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapHi_2btag_JetSDmass       ->Accumulate(             jet0sdmass, jet0P4.P(), j0_tag_alt_t, evWeight );
              predDist_AltTag_dRapHi_2btag_JetTau32        ->Accumulate(              Jet0Tau32, jet0P4.P(), j0_tag_alt_t, evWeight );
              predDist_AltTag_dRapHi_2btag_maxbdisc        ->Accumulate(         Jet0SDmaxbdisc, jet0P4.P(), j0_tag_alt_t, evWeight );
            }
          }
          // --- dRapLo
          if (DijetDeltaRap < 1){
            
            // -- btag inclusive
            predDist_AltTag_dRapLo_inclu_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_tag_alt_t, evWeight );
            predDist_AltTag_dRapLo_inclu_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_tag_alt_t, evWeight );
            predDist_AltTag_dRapLo_inclu_HT              ->Accumulate(                     ht, jet0P4.P(), j0_tag_alt_t, evWeight );        
            predDist_AltTag_dRapLo_inclu_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapLo_inclu_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapLo_inclu_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapLo_inclu_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
            predDist_AltTag_dRapLo_inclu_JetSDmass       ->Accumulate(             jet0sdmass, jet0P4.P(), j0_tag_alt_t, evWeight );
            predDist_AltTag_dRapLo_inclu_JetTau32        ->Accumulate(              Jet0Tau32, jet0P4.P(), j0_tag_alt_t, evWeight );
            predDist_AltTag_dRapLo_inclu_maxbdisc        ->Accumulate(         Jet0SDmaxbdisc, jet0P4.P(), j0_tag_alt_t, evWeight );
            
            // -- 0btag       
            if (!j0_tag_b && !j1_tag_b){
              predDist_AltTag_dRapLo_0btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_tag_alt_t, evWeight );
              predDist_AltTag_dRapLo_0btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_tag_alt_t, evWeight );
              predDist_AltTag_dRapLo_0btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_tag_alt_t, evWeight );        
              predDist_AltTag_dRapLo_0btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapLo_0btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapLo_0btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapLo_0btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapLo_0btag_JetSDmass       ->Accumulate(             jet0sdmass, jet0P4.P(), j0_tag_alt_t, evWeight );
              predDist_AltTag_dRapLo_0btag_JetTau32        ->Accumulate(              Jet0Tau32, jet0P4.P(), j0_tag_alt_t, evWeight );
              predDist_AltTag_dRapLo_0btag_maxbdisc        ->Accumulate(         Jet0SDmaxbdisc, jet0P4.P(), j0_tag_alt_t, evWeight );
            }

            // -- 1btag       
            if ((j0_tag_b && !j1_tag_b) || (!j0_tag_b && j1_tag_b)){
              predDist_AltTag_dRapLo_1btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_tag_alt_t, evWeight );
              predDist_AltTag_dRapLo_1btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_tag_alt_t, evWeight );
              predDist_AltTag_dRapLo_1btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_tag_alt_t, evWeight );        
              predDist_AltTag_dRapLo_1btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapLo_1btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapLo_1btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapLo_1btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapLo_1btag_JetSDmass       ->Accumulate(             jet0sdmass, jet0P4.P(), j0_tag_alt_t, evWeight );
              predDist_AltTag_dRapLo_1btag_JetTau32        ->Accumulate(              Jet0Tau32, jet0P4.P(), j0_tag_alt_t, evWeight );
              predDist_AltTag_dRapLo_1btag_maxbdisc        ->Accumulate(         Jet0SDmaxbdisc, jet0P4.P(), j0_tag_alt_t, evWeight );
            }

            // -- 2btag         
            if (j0_tag_b && j1_tag_b){
              predDist_AltTag_dRapLo_2btag_DijetMass       ->Accumulate(              dijetMass, jet0P4.P(), j0_tag_alt_t, evWeight );
              predDist_AltTag_dRapLo_2btag_DijetMassMod    ->Accumulate( dijetMass_modMass_jet0, jet0P4.P(), j0_tag_alt_t, evWeight );
              predDist_AltTag_dRapLo_2btag_HT              ->Accumulate(                     ht, jet0P4.P(), j0_tag_alt_t, evWeight );        
              predDist_AltTag_dRapLo_2btag_DeltaRap        ->Accumulate(          DijetDeltaRap, jet0P4.P(), j0_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapLo_2btag_JetP            ->Accumulate(             jet0P4.P(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapLo_2btag_JetPt           ->Accumulate(          jet0P4.Perp(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapLo_2btag_JetY            ->Accumulate(      jet0P4.Rapidity(), jet0P4.P(), j0_tag_alt_t, evWeight ); 
              predDist_AltTag_dRapLo_2btag_JetSDmass       ->Accumulate(             jet0sdmass, jet0P4.P(), j0_tag_alt_t, evWeight );
              predDist_AltTag_dRapLo_2btag_JetTau32        ->Accumulate(              Jet0Tau32, jet0P4.P(), j0_tag_alt_t, evWeight );
              predDist_AltTag_dRapLo_2btag_maxbdisc        ->Accumulate(         Jet0SDmaxbdisc, jet0P4.P(), j0_tag_alt_t, evWeight );
            }
          }
        } // end if alternative tag (sideband) jet 1 tagged

      } // end random # > 0.5
    } // end background estimate
  }// end event loop




  //  .d88888b.           888    
  // d88P" "Y88b          888    
  // 888     888          888    
  // 888     888 888  888 888888 
  // 888     888 888  888 888    
  // 888     888 888  888 888    
  // Y88b. .d88P Y88b 888 Y88b.  
  //  "Y88888P"   "Y88888  "Y888 
                              
                                
                              
  //Write histograms to file
  ostringstream minAK8Pt_stringstream;
  minAK8Pt_stringstream << minAK8Pt;
  string minAK8Pt_string(minAK8Pt_stringstream.str());

  ostringstream minHT_stringstream;
  minHT_stringstream << minHT;
  string minHT_string(minHT_stringstream.str());

  ostringstream Syst_stringstream;
  Syst_stringstream << Syst;
  string Syst_string(Syst_stringstream.str());


  string PUstring = "";
  if (do_PUreweighting && !isData) PUstring = "_PUw";
  else if (isData)                 PUstring = "";
  else                             PUstring = "_noPUw";

  // "Jetpt"+minAK8Pt_string+"HT"+minHT_string+
  // "Jetpt"+minAK8Pt_string+"HT"+minHT_string+
  string out_filename_antitag    = "runs/histsAntiTag_"+savelabel+"_"+systType+PUstring+"_"+input_file;
  string out_filename_kinematic  = "runs/histsKinemat_"+savelabel+"_"+systType+PUstring+"_"+input_file;
  string out_filename_bkgdEst    = "runs/histsBkgdEst_"+savelabel+"_"+systType+PUstring+"_"+input_file;



  // anti-tag and probe
  if (run_antitag){
    cout<<"Creating OutFile: "<<out_filename_antitag<<endl;
    TFile * Out = new TFile(out_filename_antitag.c_str(), "NEW");// "RECREATE");
    Out->cd();

    h_CutFlow                                                     ->Write();                   
    h_EventWeight                                                 ->Write();                   
    h_BtagCategoriesPreSF                                         ->Write();                   
    h_BtagCategoriesPostSF                                        ->Write();                   

    h_AntiTagCHS_Probe_jetP_dRapIn_inclusive                      ->Write();
    h_AntiTagCHS_Probe_jetP_dRapIn_0btag                          ->Write();
    h_AntiTagCHS_Probe_jetP_dRapIn_1btag                          ->Write();
    h_AntiTagCHS_Probe_jetP_dRapIn_2btag                          ->Write();
    h_AntiTagCHS_Probe_jetP_dRapHi_inclusive                      ->Write();
    h_AntiTagCHS_Probe_jetP_dRapHi_0btag                          ->Write();
    h_AntiTagCHS_Probe_jetP_dRapHi_1btag                          ->Write();
    h_AntiTagCHS_Probe_jetP_dRapHi_2btag                          ->Write();
    h_AntiTagCHS_Probe_jetP_dRapLo_inclusive                      ->Write();
    h_AntiTagCHS_Probe_jetP_dRapLo_0btag                          ->Write();
    h_AntiTagCHS_Probe_jetP_dRapLo_1btag                          ->Write();
    h_AntiTagCHS_Probe_jetP_dRapLo_2btag                          ->Write();
    h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclusive             ->Write();
    h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag                 ->Write();
    h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag                 ->Write();
    h_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag                 ->Write();
    h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclusive             ->Write();
    h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag                 ->Write();
    h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag                 ->Write();
    h_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag                 ->Write();
    h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclusive             ->Write();
    h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag                 ->Write();
    h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag                 ->Write();
    h_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag                 ->Write();
    h_AntiTagPuppi_Probe_jetP_dRapIn_inclusive                    ->Write();
    h_AntiTagPuppi_Probe_jetP_dRapIn_0btag                        ->Write();
    h_AntiTagPuppi_Probe_jetP_dRapIn_1btag                        ->Write();
    h_AntiTagPuppi_Probe_jetP_dRapIn_2btag                        ->Write();
    h_AntiTagPuppi_Probe_jetP_dRapHi_inclusive                    ->Write();
    h_AntiTagPuppi_Probe_jetP_dRapHi_0btag                        ->Write();
    h_AntiTagPuppi_Probe_jetP_dRapHi_1btag                        ->Write();
    h_AntiTagPuppi_Probe_jetP_dRapHi_2btag                        ->Write();
    h_AntiTagPuppi_Probe_jetP_dRapLo_inclusive                    ->Write();
    h_AntiTagPuppi_Probe_jetP_dRapLo_0btag                        ->Write();
    h_AntiTagPuppi_Probe_jetP_dRapLo_1btag                        ->Write();
    h_AntiTagPuppi_Probe_jetP_dRapLo_2btag                        ->Write();
    h_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_inclusive           ->Write();
    h_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_0btag               ->Write();
    h_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_1btag               ->Write();
    h_AntiTagPuppi_TagMassSDTau32_jetP_dRapIn_2btag               ->Write();
    h_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_inclusive           ->Write();
    h_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_0btag               ->Write();
    h_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_1btag               ->Write();
    h_AntiTagPuppi_TagMassSDTau32_jetP_dRapHi_2btag               ->Write();
    h_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_inclusive           ->Write();
    h_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_0btag               ->Write();
    h_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_1btag               ->Write();
    h_AntiTagPuppi_TagMassSDTau32_jetP_dRapLo_2btag               ->Write();
    h_alt_AntiTagCHS_Probe_jetP_dRapIn_inclusive                  ->Write();
    h_alt_AntiTagCHS_Probe_jetP_dRapIn_0btag                      ->Write();
    h_alt_AntiTagCHS_Probe_jetP_dRapIn_1btag                      ->Write();
    h_alt_AntiTagCHS_Probe_jetP_dRapIn_2btag                      ->Write();
    h_alt_AntiTagCHS_Probe_jetP_dRapHi_inclusive                  ->Write();
    h_alt_AntiTagCHS_Probe_jetP_dRapHi_0btag                      ->Write();
    h_alt_AntiTagCHS_Probe_jetP_dRapHi_1btag                      ->Write();
    h_alt_AntiTagCHS_Probe_jetP_dRapHi_2btag                      ->Write();
    h_alt_AntiTagCHS_Probe_jetP_dRapLo_inclusive                  ->Write();
    h_alt_AntiTagCHS_Probe_jetP_dRapLo_0btag                      ->Write();
    h_alt_AntiTagCHS_Probe_jetP_dRapLo_1btag                      ->Write();
    h_alt_AntiTagCHS_Probe_jetP_dRapLo_2btag                      ->Write();
    h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_inclusive         ->Write();
    h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_0btag             ->Write();
    h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_1btag             ->Write();
    h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapIn_2btag             ->Write();
    h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_inclusive         ->Write();
    h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_0btag             ->Write();
    h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_1btag             ->Write();
    h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapHi_2btag             ->Write();
    h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_inclusive         ->Write();
    h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_0btag             ->Write();
    h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_1btag             ->Write();
    h_alt_AntiTagCHS_TagMassSDTau32_jetP_dRapLo_2btag             ->Write();
      h_AntiTagCHS40to60_Probe_jetP_dRapIn_inclusive              ->Write();
      h_AntiTagCHS60to80_Probe_jetP_dRapIn_inclusive              ->Write();
     h_AntiTagCHS80to110_Probe_jetP_dRapIn_inclusive              ->Write();
    h_AntiTagCHS100to120_Probe_jetP_dRapIn_inclusive              ->Write();
    h_AntiTagCHS120to140_Probe_jetP_dRapIn_inclusive              ->Write();
    h_AntiTagCHS140to180_Probe_jetP_dRapIn_inclusive              ->Write();
    h_AntiTagCHS180to220_Probe_jetP_dRapIn_inclusive              ->Write();
    h_AntiTagCHS220to300_Probe_jetP_dRapIn_inclusive              ->Write();
      h_AntiTagCHS40to60_TagMassSDTau32_jetP_dRapIn_inclusive     ->Write();
      h_AntiTagCHS60to80_TagMassSDTau32_jetP_dRapIn_inclusive     ->Write();
     h_AntiTagCHS80to110_TagMassSDTau32_jetP_dRapIn_inclusive     ->Write();
    h_AntiTagCHS100to120_TagMassSDTau32_jetP_dRapIn_inclusive     ->Write();
    h_AntiTagCHS120to140_TagMassSDTau32_jetP_dRapIn_inclusive     ->Write();
    h_AntiTagCHS140to180_TagMassSDTau32_jetP_dRapIn_inclusive     ->Write();
    h_AntiTagCHS180to220_TagMassSDTau32_jetP_dRapIn_inclusive     ->Write();
    h_AntiTagCHS220to300_TagMassSDTau32_jetP_dRapIn_inclusive     ->Write();
    Out->Close();
  }
  // --- Kinematic plots                                 
  if (run_kinematic){


    cout<<"Creating OutFile: "<<out_filename_kinematic<<endl;
    TFile * Out = new TFile(out_filename_kinematic.c_str(), "NEW");// "RECREATE");
    Out->cd();

    h_CutFlow                                                     ->Write();                   
    h_EventWeight                                                 ->Write();                   
    h_BtagCategoriesPreSF                                         ->Write();                   
    h_BtagCategoriesPostSF                                        ->Write();                   


    // event                                                      ->Write();   
    h_DijetMass_dRapIn                                            ->Write();                   
    h_DijetMass_dRapLo                                            ->Write();                   
    h_DijetMass_dRapHi                                            ->Write();                   
    h_DeltaRap                                                    ->Write();                   
    h_DeltaPhi                                                    ->Write();                   
    h_HT                                                          ->Write();                   
    h_MET                                                         ->Write();                   
    h_METphi                                                      ->Write();                   
    h_Nvtx                                                        ->Write();                   
    // Jet0                                 
    h_Jet0P                                                       ->Write();                   
    h_Jet0Pt                                                      ->Write();                   
    h_Jet0Phi                                                     ->Write();                   
    h_Jet0Rap                                                     ->Write();                   
    h_Jet0sdmass                                                  ->Write();                   
    h_Jet0Tau1                                                    ->Write();                   
    h_Jet0Tau2                                                    ->Write();                   
    h_Jet0Tau3                                                    ->Write();                   
    h_Jet0Tau4                                                    ->Write();                   
    h_Jet0SDmaxbdisc                                              ->Write();                   
    h_Jet0SDsubjet0pt                                             ->Write();                   
    h_Jet0SDsubjet0mass                                           ->Write();                   
    h_Jet0SDsubjet0tau1                                           ->Write();                   
    h_Jet0SDsubjet0tau2                                           ->Write();                   
    h_Jet0SDsubjet0tau3                                           ->Write();                   
    h_Jet0SDsubjet0bdisc                                          ->Write();                   
    h_Jet0SDsubjet1pt                                             ->Write();                   
    h_Jet0SDsubjet1mass                                           ->Write();                   
    h_Jet0SDsubjet1tau1                                           ->Write();                   
    h_Jet0SDsubjet1tau2                                           ->Write();                   
    h_Jet0SDsubjet1tau3                                           ->Write();                   
    h_Jet0SDsubjet1bdisc                                          ->Write();                   
    h_Jet0PuppiPt                                                 ->Write();                   
    h_Jet0PuppiMass                                               ->Write();                   
    h_Jet0PuppiSDpt                                               ->Write();                   
    h_Jet0PuppiTau1                                               ->Write();                   
    h_Jet0PuppiTau2                                               ->Write();                   
    h_Jet0PuppiTau3                                               ->Write();                   
    h_Jet0PuppiTau4                                               ->Write();                   
    h_Jet0PuppiSDmaxbdisc                                         ->Write();                   
    h_Jet0PuppiSDsubjet0pt                                        ->Write();                   
    h_Jet0PuppiSDsubjet0mass                                      ->Write();                   
    h_Jet0PuppiSDsubjet0tau1                                      ->Write();                   
    h_Jet0PuppiSDsubjet0tau2                                      ->Write();                   
    h_Jet0PuppiSDsubjet0tau3                                      ->Write();                   
    h_Jet0PuppiSDsubjet0bdisc                                     ->Write();                   
    h_Jet0PuppiSDsubjet1pt                                        ->Write();                   
    h_Jet0PuppiSDsubjet1mass                                      ->Write();                   
    h_Jet0PuppiSDsubjet1tau1                                      ->Write();                   
    h_Jet0PuppiSDsubjet1tau2                                      ->Write();                   
    h_Jet0PuppiSDsubjet1tau3                                      ->Write();                   
    h_Jet0PuppiSDsubjet1bdisc                                     ->Write();                   
    h_Jet0CHF                                                     ->Write();                   
    h_Jet0NHF                                                     ->Write();                   
    h_Jet0CM                                                      ->Write();                   
    h_Jet0NM                                                      ->Write();                   
    h_Jet0NEF                                                     ->Write();                   
    h_Jet0CEF                                                     ->Write();                   
    h_Jet0MF                                                      ->Write();                   
    h_Jet0Mult                                                    ->Write();                   
    h_Jet0PuppiCHF                                                ->Write();                   
    h_Jet0PuppiNHF                                                ->Write();                   
    h_Jet0PuppiCM                                                 ->Write();                   
    h_Jet0PuppiNM                                                 ->Write();                   
    h_Jet0PuppiNEF                                                ->Write();                   
    h_Jet0PuppiCEF                                                ->Write();                   
    h_Jet0PuppiMF                                                 ->Write();                   
    h_Jet0PuppiMult                                               ->Write();                   
    h_Jet1Pt                                                      ->Write();                   
    h_Jet1Rap                                                     ->Write();                   
    // N-1 histograms                                 
    h_Jet0SDmass                                                  ->Write();                   
    h_Jet0SDmass_JetTag_b                                         ->Write();                   
    h_Jet0SDmass_JetTag_tau32                                     ->Write();                   
    h_Jet0SDmass_JetTag_b_tau32                                   ->Write();                   
    h_Jet0SDmass_OppositeJetTag_t_b                               ->Write();                   
    h_Jet0SDmass_OppositeJetTag_t_b_JetTag_b                      ->Write();                   
    h_Jet0SDmass_OppositeJetTag_t_b_JetTag_b_tau32                ->Write();                   
    h_Jet1SDmass                                                  ->Write();                   
    h_Jet1SDmass_JetTag_b                                         ->Write();                   
    h_Jet1SDmass_JetTag_tau32                                     ->Write();                   
    h_Jet1SDmass_JetTag_b_tau32                                   ->Write();                   
    h_Jet1SDmass_OppositeJetTag_t_b                               ->Write();                   
    h_Jet1SDmass_OppositeJetTag_t_b_JetTag_b                      ->Write();                   
    h_Jet1SDmass_OppositeJetTag_t_b_JetTag_b_tau32                ->Write();                   
    h_JetSDmass                                                   ->Write();                   
    h_JetSDmass_JetTag_b                                          ->Write();                   
    h_JetSDmass_JetTag_tau32                                      ->Write();                   
    h_JetSDmass_JetTag_b_tau32                                    ->Write();                   
    h_JetSDmass_OppositeJetTag_t_b                                ->Write();                   
    h_JetSDmass_OppositeJetTag_t_b_JetTag_b                       ->Write();                   
    h_JetSDmass_OppositeJetTag_t_b_JetTag_b_tau32                 ->Write();                   
    h_Jet0Tau32                                                   ->Write();                   
    h_Jet0Tau32_JetTag_b                                          ->Write();                   
    h_Jet0Tau32_JetTag_mass                                       ->Write();                   
    h_Jet0Tau32_JetTag_b_mass                                     ->Write();                   
    h_Jet0Tau32_OppositeJetTag_t_b                                ->Write();                   
    h_Jet0Tau32_OppositeJetTag_t_b_JetTag_b                       ->Write();                   
    h_Jet0Tau32_OppositeJetTag_t_b_JetTag_b_mass                  ->Write();                   
    h_Jet1Tau32                                                   ->Write();                   
    h_Jet1Tau32_JetTag_b                                          ->Write();                   
    h_Jet1Tau32_JetTag_mass                                       ->Write();                   
    h_Jet1Tau32_JetTag_b_mass                                     ->Write();                   
    h_Jet1Tau32_OppositeJetTag_t_b                                ->Write();                   
    h_Jet1Tau32_OppositeJetTag_t_b_JetTag_b                       ->Write();                   
    h_Jet1Tau32_OppositeJetTag_t_b_JetTag_b_mass                  ->Write();                   
    h_JetTau32                                                    ->Write();                   
    h_JetTau32_JetTag_b                                           ->Write();                   
    h_JetTau32_JetTag_mass                                        ->Write();                   
    h_JetTau32_JetTag_b_mass                                      ->Write();                   
    h_JetTau32_OppositeJetTag_t_b                                 ->Write();                   
    h_JetTau32_OppositeJetTag_t_b_JetTag_b                        ->Write();                   
    h_JetTau32_OppositeJetTag_t_b_JetTag_b_mass                   ->Write();                   
                                   
    // 2D                                 
    h_Jet0Pt_Jet0Mass                                     ->Write();            
    h_Jet0P_Jet0Mass                                      ->Write();            
    h_Jet0Pt_Jet0SDmass                                   ->Write();            
    h_Jet0P_Jet0SDmass                                    ->Write();            
    h_Jet0Y_Jet0Mass                                      ->Write();            
    h_Jet0Y_Jet0Mass_Pt500to520                           ->Write();            
                                   
    h_Jet0Y_Jet0SDmass                                    ->Write();            
    h_Jet0Y_Jet0SDmass_Pt500to520                         ->Write();            
                                   
    h_Jet0Y_Jet1Y                                         ->Write();            
    h_Jet0Y_Jet1Y_Pt500to520                              ->Write();            
    h_runNumber_DijetMass                                  ->Write();            
    h_runNumber_HT                                         ->Write();            
    h_runNumber_Jet0CHF                                    ->Write();            
    h_runNumber_Jet0NHF                                    ->Write();            
    h_runNumber_Jet0CM                                     ->Write();            
    h_runNumber_Jet0NM                                     ->Write();            
    h_runNumber_Jet0NEF                                    ->Write();            
    h_runNumber_Jet0CEF                                    ->Write();            
    h_runNumber_Jet0MF                                     ->Write();            
    h_runNumber_Jet0Mult                                   ->Write();            
    h_runNumber_NvtxGood                                   ->Write();            
    h_runNumber_Jet0Pt                                     ->Write();            
    h_runNumber_Jet0SDmass                                 ->Write();            
                                   
                                   
    // MC study                                 
    h_Jet0SDmass_matchedTop                               ->Write();                     
    h_Jet0SDmass_matchedTop_topDist                       ->Write();                     
    h_Jet0SDmass_outside                                  ->Write();                     
    h_Jet0SDmass_bq                                       ->Write();                     
    h_Jet0SDmass_qq                                       ->Write();                     
                                   
    h_Jet0SDmass_all                                      ->Write();                     
    h_Jet0SDmass_in_b                                     ->Write();                     
    h_Jet0SDmass_in_q                                     ->Write();                     
    h_Jet0SDmass_in_qq                                    ->Write();                     
    h_Jet0SDmass_in_qb                                    ->Write();                     
    h_Jet0SDmass_in_qqb                                   ->Write();                     
    h_Jet0SDmass_unmatched                                ->Write();                     
    h_Jet0Tau32_all                                       ->Write();                     
    h_Jet0Tau32_in_b                                      ->Write();                     
    h_Jet0Tau32_in_q                                      ->Write();                     
    h_Jet0Tau32_in_qq                                     ->Write();                     
    h_Jet0Tau32_in_qb                                     ->Write();                     
    h_Jet0Tau32_in_qqb                                    ->Write();                     
    h_Jet0Tau32_unmatched                                 ->Write();                     
    h_Jet0SDmass_Pt600_all                                ->Write();                     
    h_Jet0SDmass_Pt600_in_b                               ->Write();                     
    h_Jet0SDmass_Pt600_in_q                               ->Write();                     
    h_Jet0SDmass_Pt600_in_qq                              ->Write();                     
    h_Jet0SDmass_Pt600_in_qb                              ->Write();                     
    h_Jet0SDmass_Pt600_in_qqb                             ->Write();                     
    h_Jet0SDmass_Pt600_unmatched                          ->Write();                     
    h_Jet0Tau32_Pt600_all                                 ->Write();                     
    h_Jet0Tau32_Pt600_in_b                                ->Write();                     
    h_Jet0Tau32_Pt600_in_q                                ->Write();                     
    h_Jet0Tau32_Pt600_in_qq                               ->Write();                     
    h_Jet0Tau32_Pt600_in_qb                               ->Write();                     
    h_Jet0Tau32_Pt600_in_qqb                              ->Write();                     
    h_Jet0Tau32_Pt600_unmatched                           ->Write();                     
    h_Jet0SDmass_BtagM_all                                ->Write();                     
    h_Jet0SDmass_BtagM_in_b                               ->Write();                     
    h_Jet0SDmass_BtagM_in_q                               ->Write();                     
    h_Jet0SDmass_BtagM_in_qq                              ->Write();                     
    h_Jet0SDmass_BtagM_in_qb                              ->Write();                     
    h_Jet0SDmass_BtagM_in_qqb                             ->Write();                     
    h_Jet0SDmass_BtagM_unmatched                          ->Write();                     
    h_Jet0SDmass_BtagT_all                                ->Write();                     
    h_Jet0SDmass_BtagT_in_b                               ->Write();                     
    h_Jet0SDmass_BtagT_in_q                               ->Write();                     
    h_Jet0SDmass_BtagT_in_qq                              ->Write();                     
    h_Jet0SDmass_BtagT_in_qb                              ->Write();                     
    h_Jet0SDmass_BtagT_in_qqb                             ->Write();                     
    h_Jet0SDmass_BtagT_unmatched                          ->Write();                     
    h_Jet0Tau32_BtagM_all                                 ->Write();                     
    h_Jet0Tau32_BtagM_in_b                                ->Write();                     
    h_Jet0Tau32_BtagM_in_q                                ->Write();                     
    h_Jet0Tau32_BtagM_in_qq                               ->Write();                     
    h_Jet0Tau32_BtagM_in_qb                               ->Write();                     
    h_Jet0Tau32_BtagM_in_qqb                              ->Write();                     
    h_Jet0Tau32_BtagM_unmatched                           ->Write();                     
    h_Jet0Tau32_MassTag_all                               ->Write();                     
    h_Jet0Tau32_MassTag_in_b                              ->Write();                     
    h_Jet0Tau32_MassTag_in_q                              ->Write();                     
    h_Jet0Tau32_MassTag_in_qq                             ->Write();                     
    h_Jet0Tau32_MassTag_in_qb                             ->Write();                     
    h_Jet0Tau32_MassTag_in_qqb                            ->Write();                     
    h_Jet0Tau32_MassTag_unmatched                         ->Write();                     
    h_Jet0Tau32_BtagM_MassTag_all                         ->Write();                     
    h_Jet0Tau32_BtagM_MassTag_in_b                        ->Write();                     
    h_Jet0Tau32_BtagM_MassTag_in_q                        ->Write();                     
    h_Jet0Tau32_BtagM_MassTag_in_qq                       ->Write();                     
    h_Jet0Tau32_BtagM_MassTag_in_qb                       ->Write();                     
    h_Jet0Tau32_BtagM_MassTag_in_qqb                      ->Write();                     
    h_Jet0Tau32_BtagM_MassTag_unmatched                   ->Write();                     
    h_Jet0SDmass_TauTag_all                               ->Write();                     
    h_Jet0SDmass_TauTag_in_b                              ->Write();                     
    h_Jet0SDmass_TauTag_in_q                              ->Write();                     
    h_Jet0SDmass_TauTag_in_qq                             ->Write();                     
    h_Jet0SDmass_TauTag_in_qb                             ->Write();                     
    h_Jet0SDmass_TauTag_in_qqb                            ->Write();                     
    h_Jet0SDmass_TauTag_unmatched                         ->Write();                     
    h_Jet0SDmass_AntiTauTag_all                           ->Write();                     
    h_Jet0SDmass_AntiTauTag_in_b                          ->Write();                     
    h_Jet0SDmass_AntiTauTag_in_q                          ->Write();                     
    h_Jet0SDmass_AntiTauTag_in_qq                         ->Write();                     
    h_Jet0SDmass_AntiTauTag_in_qb                         ->Write();                     
    h_Jet0SDmass_AntiTauTag_in_qqb                        ->Write();                     
    h_Jet0SDmass_AntiTauTag_unmatched                     ->Write();                     
    h_Jet0SDmass_BtagM_TauTag_all                         ->Write();                     
    h_Jet0SDmass_BtagM_TauTag_in_b                        ->Write();                     
    h_Jet0SDmass_BtagM_TauTag_in_q                        ->Write();                     
    h_Jet0SDmass_BtagM_TauTag_in_qq                       ->Write();                     
    h_Jet0SDmass_BtagM_TauTag_in_qb                       ->Write();                     
    h_Jet0SDmass_BtagM_TauTag_in_qqb                      ->Write();                     
    h_Jet0SDmass_BtagM_TauTag_unmatched                   ->Write();                     
                                   
    // double tagged                                 
    h_2ttag_inclu_dRapIn_DijetMass                               ->Write();    
    h_2ttag_0btag_dRapIn_DijetMass                               ->Write();    
    h_2ttag_1btag_dRapIn_DijetMass                               ->Write();    
    h_2ttag_2btag_dRapIn_DijetMass                               ->Write();    
    h_2ttag_inclu_dRapLo_DijetMass                               ->Write();    
    h_2ttag_0btag_dRapLo_DijetMass                               ->Write();    
    h_2ttag_1btag_dRapLo_DijetMass                               ->Write();    
    h_2ttag_2btag_dRapLo_DijetMass                               ->Write();    
    h_2ttag_inclu_dRapHi_DijetMass                               ->Write();    
    h_2ttag_0btag_dRapHi_DijetMass                               ->Write();    
    h_2ttag_1btag_dRapHi_DijetMass                               ->Write();    
    h_2ttag_2btag_dRapHi_DijetMass                               ->Write();    
    h_2ttag_inclu_DeltaRap                                       ->Write();    
    h_2ttag_0btag_DeltaRap                                       ->Write();    
    h_2ttag_1btag_DeltaRap                                       ->Write();    
    h_2ttag_2btag_DeltaRap                                       ->Write();    
    h_2ttag_inclu_DeltaPhi                                       ->Write();    
    h_2ttag_0btag_DeltaPhi                                       ->Write();    
    h_2ttag_1btag_DeltaPhi                                       ->Write();    
    h_2ttag_2btag_DeltaPhi                                       ->Write();    
    h_2ttag_inclu_HT                                             ->Write();    
    h_2ttag_0btag_HT                                             ->Write();    
    h_2ttag_1btag_HT                                             ->Write();    
    h_2ttag_2btag_HT                                             ->Write();    
    h_2ttag_inclu_MET                                            ->Write();    
    h_2ttag_0btag_MET                                            ->Write();    
    h_2ttag_1btag_MET                                            ->Write();    
    h_2ttag_2btag_MET                                            ->Write();    
                                   
    h_2ttag_inclu_METphi                                         ->Write();    
    h_2ttag_0btag_METphi                                         ->Write();    
    h_2ttag_1btag_METphi                                         ->Write();    
    h_2ttag_2btag_METphi                                         ->Write();    
                                   
    h_2ttag_inclu_Nvtx                                           ->Write();    
    h_2ttag_0btag_Nvtx                                           ->Write();    
    h_2ttag_1btag_Nvtx                                           ->Write();    
    h_2ttag_2btag_Nvtx                                           ->Write();    
                                   
                                   
    h_2ttag_inclu_Jet0P                                          ->Write();        
    h_2ttag_inclu_Jet0Pt                                         ->Write();        
    h_2ttag_inclu_Jet0Phi                                        ->Write();        
    h_2ttag_inclu_Jet0Rap                                        ->Write();        
    h_2ttag_inclu_Jet0SDmass                                     ->Write();        
    h_2ttag_inclu_Jet0SDmassCorrL23                              ->Write();        
    h_2ttag_inclu_Jet0SDmassCorrL23Up                            ->Write();        
    h_2ttag_inclu_Jet0Tau1                                       ->Write();        
    h_2ttag_inclu_Jet0Tau2                                       ->Write();        
    h_2ttag_inclu_Jet0Tau3                                       ->Write();        
    h_2ttag_inclu_Jet0Tau4                                       ->Write();        
    h_2ttag_inclu_Jet0SDmaxbdisc                                 ->Write();        
    h_2ttag_inclu_Jet0SDsubjet0pt                                ->Write();        
    h_2ttag_inclu_Jet0SDsubjet0mass                              ->Write();        
    h_2ttag_inclu_Jet0SDsubjet0tau1                              ->Write();        
    h_2ttag_inclu_Jet0SDsubjet0tau2                              ->Write();        
    h_2ttag_inclu_Jet0SDsubjet0tau3                              ->Write();        
    h_2ttag_inclu_Jet0SDsubjet0bdisc                             ->Write();        
    h_2ttag_inclu_Jet0SDsubjet1pt                                ->Write();        
    h_2ttag_inclu_Jet0SDsubjet1mass                              ->Write();        
    h_2ttag_inclu_Jet0SDsubjet1tau1                              ->Write();        
    h_2ttag_inclu_Jet0SDsubjet1tau2                              ->Write();        
    h_2ttag_inclu_Jet0SDsubjet1tau3                              ->Write();        
    h_2ttag_inclu_Jet0SDsubjet1bdisc                             ->Write();        
    h_2ttag_inclu_Jet0PuppiPt                                    ->Write();        
    h_2ttag_inclu_Jet0PuppiMass                                  ->Write();        
    h_2ttag_inclu_Jet0PuppiSDpt                                  ->Write();        
    h_2ttag_inclu_Jet0PuppiTau1                                  ->Write();        
    h_2ttag_inclu_Jet0PuppiTau2                                  ->Write();        
    h_2ttag_inclu_Jet0PuppiTau3                                  ->Write();        
    h_2ttag_inclu_Jet0PuppiTau4                                  ->Write();        
    h_2ttag_inclu_Jet0PuppiSDmaxbdisc                            ->Write();        
    h_2ttag_inclu_Jet0PuppiSDsubjet0pt                           ->Write();        
    h_2ttag_inclu_Jet0PuppiSDsubjet0mass                         ->Write();        
    h_2ttag_inclu_Jet0PuppiSDsubjet0tau1                         ->Write();        
    h_2ttag_inclu_Jet0PuppiSDsubjet0tau2                         ->Write();        
    h_2ttag_inclu_Jet0PuppiSDsubjet0tau3                         ->Write();        
    h_2ttag_inclu_Jet0PuppiSDsubjet0bdisc                        ->Write();        
    h_2ttag_inclu_Jet0PuppiSDsubjet1pt                           ->Write();        
    h_2ttag_inclu_Jet0PuppiSDsubjet1mass                         ->Write();        
    h_2ttag_inclu_Jet0PuppiSDsubjet1tau1                         ->Write();        
    h_2ttag_inclu_Jet0PuppiSDsubjet1tau2                         ->Write();        
    h_2ttag_inclu_Jet0PuppiSDsubjet1tau3                         ->Write();        
    h_2ttag_inclu_Jet0PuppiSDsubjet1bdisc                        ->Write();        
    h_2ttag_inclu_Jet0CHF                                        ->Write();        
    h_2ttag_inclu_Jet0NHF                                        ->Write();        
    h_2ttag_inclu_Jet0CM                                         ->Write();        
    h_2ttag_inclu_Jet0NM                                         ->Write();        
    h_2ttag_inclu_Jet0NEF                                        ->Write();        
    h_2ttag_inclu_Jet0CEF                                        ->Write();        
    h_2ttag_inclu_Jet0MF                                         ->Write();        
    h_2ttag_inclu_Jet0Mult                                       ->Write();        
    h_2ttag_2btag_Jet0PuppiSDsubjet0pt                           ->Write();        
    h_2ttag_2btag_Jet0PuppiSDsubjet0mass                         ->Write();        
    h_2ttag_2btag_Jet0PuppiSDsubjet0tau1                         ->Write();        
    h_2ttag_2btag_Jet0PuppiSDsubjet0tau2                         ->Write();        
    h_2ttag_2btag_Jet0PuppiSDsubjet0tau3                         ->Write();        
    h_2ttag_2btag_Jet0PuppiSDsubjet0bdisc                        ->Write();        
    h_2ttag_2btag_Jet0PuppiSDsubjet1pt                           ->Write();        
    h_2ttag_2btag_Jet0PuppiSDsubjet1mass                         ->Write();        
    h_2ttag_2btag_Jet0PuppiSDsubjet1tau1                         ->Write();        
    h_2ttag_2btag_Jet0PuppiSDsubjet1tau2                         ->Write();        
    h_2ttag_2btag_Jet0PuppiSDsubjet1tau3                         ->Write();        
    h_2ttag_2btag_Jet0PuppiSDsubjet1bdisc                        ->Write();        
    h_2ttag_1btag_Jet0PuppiSDsubjet0pt                           ->Write();        
    h_2ttag_1btag_Jet0PuppiSDsubjet0mass                         ->Write();        
    h_2ttag_1btag_Jet0PuppiSDsubjet0tau1                         ->Write();        
    h_2ttag_1btag_Jet0PuppiSDsubjet0tau2                         ->Write();        
    h_2ttag_1btag_Jet0PuppiSDsubjet0tau3                         ->Write();        
    h_2ttag_1btag_Jet0PuppiSDsubjet0bdisc                        ->Write();        
    h_2ttag_1btag_Jet0PuppiSDsubjet1pt                           ->Write();        
    h_2ttag_1btag_Jet0PuppiSDsubjet1mass                         ->Write();        
    h_2ttag_1btag_Jet0PuppiSDsubjet1tau1                         ->Write();        
    h_2ttag_1btag_Jet0PuppiSDsubjet1tau2                         ->Write();        
    h_2ttag_1btag_Jet0PuppiSDsubjet1tau3                         ->Write();        
    h_2ttag_1btag_Jet0PuppiSDsubjet1bdisc                        ->Write();        
    h_2ttag_0btag_Jet0PuppiSDsubjet0pt                           ->Write();        
    h_2ttag_0btag_Jet0PuppiSDsubjet0mass                         ->Write();        
    h_2ttag_0btag_Jet0PuppiSDsubjet0tau1                         ->Write();        
    h_2ttag_0btag_Jet0PuppiSDsubjet0tau2                         ->Write();        
    h_2ttag_0btag_Jet0PuppiSDsubjet0tau3                         ->Write();        
    h_2ttag_0btag_Jet0PuppiSDsubjet0bdisc                        ->Write();        
    h_2ttag_0btag_Jet0PuppiSDsubjet1pt                           ->Write();        
    h_2ttag_0btag_Jet0PuppiSDsubjet1mass                         ->Write();        
    h_2ttag_0btag_Jet0PuppiSDsubjet1tau1                         ->Write();        
    h_2ttag_0btag_Jet0PuppiSDsubjet1tau2                         ->Write();        
    h_2ttag_0btag_Jet0PuppiSDsubjet1tau3                         ->Write();        
    h_2ttag_0btag_Jet0PuppiSDsubjet1bdisc                        ->Write();        
                                   
    h_2btag_DijetMass                                            ->Write();                    
    h_2btag_DeltaRap                                             ->Write();                    
    h_2btag_jet0massSD                                           ->Write();                    
    h_2btag_jet0tau32                                            ->Write();                    
    h_2btag_jet0tau21                                            ->Write();                    
    h_2btag_jet0tau1                                             ->Write();                    
    h_2btag_jet0tau2                                             ->Write();                    
    h_2btag_jet0tau3                                             ->Write();                    
    h_2btag_jet0subjet0mass                                      ->Write();                    
    h_2btag_jet0subjet1mass                                      ->Write();                    
    h_2btag_jet0subjet0mass_jet0subjet1mass                      ->Write();                    
    h_2btag_jet0subjet0bdisc_jet0subjet1bdisc                    ->Write();                    
    h_2btag_jet1massSD                                           ->Write();                    
    h_2btag_jet1tau32                                            ->Write();                    
    h_2btag_jet1tau21                                            ->Write();                    
    h_2btag_jet1tau1                                             ->Write();                    
    h_2btag_jet1tau2                                             ->Write();                    
    h_2btag_jet1tau3                                             ->Write();                    
    h_2btag_jet1subjet0mass                                      ->Write();                    
    h_2btag_jet1subjet1mass                                      ->Write();                    
    h_2btag_jet1subjet0mass_jet1subjet1mass                      ->Write();                    
    h_2btag_jet1subjet0bdisc_jet1subjet1bdisc                    ->Write();                    
    h_2btag_jet1ttag_jet0massSD                                  ->Write();                    
    h_2btag_jet1ttag_jet0tau32                                   ->Write();                    
    h_2btag_jet1ttag_jet0tau21                                   ->Write();                    
    h_2btag_jet1ttag_jet0tau1                                    ->Write();                    
    h_2btag_jet1ttag_jet0tau2                                    ->Write();                    
    h_2btag_jet1ttag_jet0tau3                                    ->Write();                    
    h_2btag_jet1ttag_jet0subjet0mass                             ->Write();                    
    h_2btag_jet1ttag_jet0subjet1mass                             ->Write();                    
    h_2btag_jet1ttag_jet0subjet0mass_jet0subjet1mass             ->Write();                    
    h_2btag_jet1ttag_jet0subjet0bdisc_jet0subjet1bdisc           ->Write();                    
    h_2btag_jet0ttag_jet1massSD                                  ->Write();                    
    h_2btag_jet0ttag_jet1tau32                                   ->Write();                    
    h_2btag_jet0ttag_jet1tau21                                   ->Write();                    
    h_2btag_jet0ttag_jet1tau1                                    ->Write();                    
    h_2btag_jet0ttag_jet1tau2                                    ->Write();                    
    h_2btag_jet0ttag_jet1tau3                                    ->Write();                    
    h_2btag_jet0ttag_jet1subjet0mass                             ->Write();                    
    h_2btag_jet0ttag_jet1subjet1mass                             ->Write();                    
    h_2btag_jet0ttag_jet1subjet0mass_jet1subjet1mass             ->Write();                    
    h_2btag_jet0ttag_jet1subjet0bdisc_jet1subjet1bdisc           ->Write();                    
    h_2btag_jet1ttag_jet0tautag_jet0massSD                       ->Write();                    
    h_2btag_jet1ttag_jet0masstag_jet0tau32                       ->Write();                    
    h_2btag_jet1ttag_jet0masstag_jet0tau21                       ->Write();                    
    h_2btag_jet1ttag_jet0masstag_jet0tau1                        ->Write();                    
    h_2btag_jet1ttag_jet0masstag_jet0tau2                        ->Write();                    
    h_2btag_jet1ttag_jet0masstag_jet0tau3                        ->Write();                    
    h_2btag_jet0ttag_jet1tautag_jet1massSD                       ->Write();                    
    h_2btag_jet0ttag_jet1masstag_jet1tau32                       ->Write();                    
    h_2btag_jet0ttag_jet1masstag_jet1tau21                       ->Write();                    
    h_2btag_jet0ttag_jet1masstag_jet1tau1                        ->Write();                    
    h_2btag_jet0ttag_jet1masstag_jet1tau2                        ->Write();                    
    h_2btag_jet0ttag_jet1masstag_jet1tau3                        ->Write();                    
    h_topTag_jet0subjet0pt                                       ->Write();                    
    h_topTag_jet0subjet1pt                                       ->Write();                    
    h_topTag_jet0pt                                              ->Write();                    
    h_topTag_jet0pt_jet0subjet0pt                                ->Write();                    
    h_topTag_jet0pt_jet0subjet1pt                                ->Write();                    
    h_topTag_jet0subjet0pt_jet0subjet1pt                         ->Write();                    
    h_topTag_jet0subjet0mass_jet0subjet1mass                     ->Write();                    
    h_topTag_jet0subjet0bdisc_jet0subjet1bdisc                   ->Write();                    
    h_topTag_jet0subjet0mass                                     ->Write();                    
    h_topTag_jet0subjet1mass                                     ->Write();                    
    h_topTag_jet0subjet0bdisc                                    ->Write();                    
    h_topTag_jet0subjet1bdisc                                    ->Write();                    
    h_topTag_jet0maxBdisc                                        ->Write();                    
    h_topTagbTag_jet0subjet0pt                                   ->Write();                    
    h_topTagbTag_jet0subjet1pt                                   ->Write();                    
    h_topTagbTag_jet0pt                                          ->Write();                    
    h_topTagbTag_jet0pt_jet0subjet0pt                            ->Write();                    
    h_topTagbTag_jet0pt_jet0subjet1pt                            ->Write();                    
    h_topTagbTag_jet0subjet0pt_jet0subjet1pt                     ->Write();                    
    h_topTagbTag_jet0subjet0mass_jet0subjet1mass                 ->Write();                    
    h_topTagbTag_jet0subjet0bdisc_jet0subjet1bdisc               ->Write();                    
    h_topTagbTag_jet0subjet0mass                                 ->Write();                    
    h_topTagbTag_jet0subjet1mass                                 ->Write();                    
    h_topTagbTag_jet0subjet0bdisc                                ->Write();                    
    h_topTagbTag_jet0subjet1bdisc                                ->Write();                    
    h_topTagbTag_jet0maxBdisc                                    ->Write();                    
                                   
                                   
    // DDT tests                                 
    h_jet0_rhoRatio                                              ->Write();      
    h_jet0_rhoRatioPrime                                         ->Write();      
    h_jet0_rhoRatioPmag                                          ->Write();      
    h_jet0_rhoRatioPmagPrime                                     ->Write();      
    h_jet0_rhoRatioPuppi                                         ->Write();      
    h_jet0_rhoRatioPuppiPrime                                    ->Write();      
    h_jet0_rhoRatioPuppiPmag                                     ->Write();      
    h_jet0_rhoRatioPuppiPmagPrime                                ->Write();      
    h_jet1_rhoRatio                                              ->Write();      
    h_jet1_rhoRatioPrime                                         ->Write();      
    h_jet1_rhoRatioPmag                                          ->Write();      
    h_jet1_rhoRatioPmagPrime                                     ->Write();      
    h_jet1_rhoRatioPuppi                                         ->Write();      
    h_jet1_rhoRatioPuppiPrime                                    ->Write();      
    h_jet1_rhoRatioPuppiPmag                                     ->Write();      
    h_jet1_rhoRatioPuppiPmagPrime                                ->Write();      
    h_jet0_tau32_rhoRatio                                ->Write();              
    h_jet0_tau32_rhoRatioPrime                           ->Write();              
    h_jet0_tau32_rhoRatioPmag                            ->Write();              
    h_jet0_tau32_rhoRatioPmagPrime                       ->Write();              
    h_jet0_tau32_rhoRatioPuppi                           ->Write();              
    h_jet0_tau32_rhoRatioPuppiPrime                      ->Write();              
    h_jet0_tau32_rhoRatioPuppiPmag                       ->Write();              
    h_jet0_tau32_rhoRatioPuppiPmagPrime                  ->Write();              
    h_jet1_tau32_rhoRatio                                ->Write();              
    h_jet1_tau32_rhoRatioPrime                           ->Write();              
    h_jet1_tau32_rhoRatioPmag                            ->Write();              
    h_jet1_tau32_rhoRatioPmagPrime                       ->Write();              
    h_jet1_tau32_rhoRatioPuppi                           ->Write();              
    h_jet1_tau32_rhoRatioPuppiPrime                      ->Write();              
    h_jet1_tau32_rhoRatioPuppiPmag                       ->Write();              
    h_jet1_tau32_rhoRatioPuppiPmagPrime                  ->Write();              
    h_jet0_tau21_rhoRatio                                ->Write();              
    h_jet0_tau21_rhoRatioPrime                           ->Write();              
    h_jet0_tau21_rhoRatioPmag                            ->Write();              
    h_jet0_tau21_rhoRatioPmagPrime                       ->Write();              
    h_jet0_tau21_rhoRatioPuppi                           ->Write();              
    h_jet0_tau21_rhoRatioPuppiPrime                      ->Write();              
    h_jet0_tau21_rhoRatioPuppiPmag                       ->Write();              
    h_jet0_tau21_rhoRatioPuppiPmagPrime                  ->Write();              
    h_jet1_tau21_rhoRatio                                ->Write();              
    h_jet1_tau21_rhoRatioPrime                           ->Write();              
    h_jet1_tau21_rhoRatioPmag                            ->Write();              
    h_jet1_tau21_rhoRatioPmagPrime                       ->Write();              
    h_jet1_tau21_rhoRatioPuppi                           ->Write();              
    h_jet1_tau21_rhoRatioPuppiPrime                      ->Write();              
    h_jet1_tau21_rhoRatioPuppiPmag                       ->Write();              
    h_jet1_tau21_rhoRatioPuppiPmagPrime                  ->Write();              
    h_jet0_tau42_rhoRatio                                ->Write();              
    h_jet0_tau42_rhoRatioPrime                           ->Write();              
    h_jet0_tau42_rhoRatioPmag                            ->Write();              
    h_jet0_tau42_rhoRatioPmagPrime                       ->Write();              
    h_jet0_tau42_rhoRatioPuppi                           ->Write();              
    h_jet0_tau42_rhoRatioPuppiPrime                      ->Write();              
    h_jet0_tau42_rhoRatioPuppiPmag                       ->Write();              
    h_jet0_tau42_rhoRatioPuppiPmagPrime                  ->Write();              
    h_jet1_tau42_rhoRatio                                ->Write();              
    h_jet1_tau42_rhoRatioPrime                           ->Write();              
    h_jet1_tau42_rhoRatioPmag                            ->Write();              
    h_jet1_tau42_rhoRatioPmagPrime                       ->Write();              
    h_jet1_tau42_rhoRatioPuppi                           ->Write();              
    h_jet1_tau42_rhoRatioPuppiPrime                      ->Write();              
    h_jet1_tau42_rhoRatioPuppiPmag                       ->Write();              
    h_jet1_tau42_rhoRatioPuppiPmagPrime                  ->Write();              
                                   
    //Hadronic mtt selection and background estimaion            ->Write();                  
    h_mttMass_tagMassSDTau32_dRapHi_inclusive                    ->Write();                  
    h_mttMass_tagMassSDTau32_dRapHi_0btag                        ->Write();                  
    h_mttMass_tagMassSDTau32_dRapHi_1btag                        ->Write();                  
    h_mttMass_tagMassSDTau32_dRapHi_2btag                        ->Write();                  
    h_mttMass_tagMassSDTau32_dRapLo_inclusive                    ->Write();                  
    h_mttMass_tagMassSDTau32_dRapLo_0btag                        ->Write();                  
    h_mttMass_tagMassSDTau32_dRapLo_1btag                        ->Write();                  
    h_mttMass_tagMassSDTau32_dRapLo_2btag                        ->Write();                  
    h_mttMass_tagMassSDTau32_dRapIn_inclusive                    ->Write();                  
    h_mttMass_tagMassSDTau32_dRapIn_0btag                        ->Write();                  
    h_mttMass_tagMassSDTau32_dRapIn_1btag                        ->Write();                  
    h_mttMass_tagMassSDTau32_dRapIn_2btag                        ->Write();                  
    h_bkgdEst_tagMassSDTau32_dRapHi_inclusive                    ->Write();                  
    h_bkgdEst_tagMassSDTau32_dRapHi_0btag                        ->Write();                  
    h_bkgdEst_tagMassSDTau32_dRapHi_1btag                        ->Write();                  
    h_bkgdEst_tagMassSDTau32_dRapHi_2btag                        ->Write();                  
    h_bkgdEst_tagMassSDTau32_dRapLo_inclusive                    ->Write();                  
    h_bkgdEst_tagMassSDTau32_dRapLo_0btag                        ->Write();                  
    h_bkgdEst_tagMassSDTau32_dRapLo_1btag                        ->Write();                  
    h_bkgdEst_tagMassSDTau32_dRapLo_2btag                        ->Write();                  
    h_bkgdEst_tagMassSDTau32_dRapIn_inclusive                    ->Write();                  
    h_bkgdEst_tagMassSDTau32_dRapIn_0btag                        ->Write();                  
    h_bkgdEst_tagMassSDTau32_dRapIn_1btag                        ->Write();                  
    h_bkgdEst_tagMassSDTau32_dRapIn_2btag                        ->Write();                  
    h_bkgdEst_modMass_tagMassSDTau32_dRapHi_inclusive            ->Write();                  
    h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag                ->Write();                  
    h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag                ->Write();                  
    h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag                ->Write();                  
    h_bkgdEst_modMass_tagMassSDTau32_dRapLo_inclusive            ->Write();                  
    h_bkgdEst_modMass_tagMassSDTau32_dRapLo_0btag                ->Write();                  
    h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag                ->Write();                  
    h_bkgdEst_modMass_tagMassSDTau32_dRapLo_2btag                ->Write();                  
    h_bkgdEst_modMass_tagMassSDTau32_dRapIn_inclusive            ->Write();                  
    h_bkgdEst_modMass_tagMassSDTau32_dRapIn_0btag                ->Write();                  
    h_bkgdEst_modMass_tagMassSDTau32_dRapIn_1btag                ->Write();                  
    h_bkgdEst_modMass_tagMassSDTau32_dRapIn_2btag                ->Write();                  
                                                                                            
                                                               
    Out->Close();
  }


  // write background estimate histograms to file
  if (run_bkgdest){
    cout<<"Writing background estimate histograms"<<endl;
    // h_mttMass_tagMassSDTau32_dRapHi_inclusive        ->Write();
    // h_mttMass_tagMassSDTau32_dRapHi_2btag            ->Write();
    // h_mttMass_tagMassSDTau32_dRapHi_1btag            ->Write();
    // h_mttMass_tagMassSDTau32_dRapHi_0btag            ->Write();
    // h_mttMass_tagMassSDTau32_dRapLo_inclusive        ->Write();
    // h_mttMass_tagMassSDTau32_dRapLo_2btag            ->Write();
    // h_mttMass_tagMassSDTau32_dRapLo_1btag            ->Write();
    // h_mttMass_tagMassSDTau32_dRapLo_0btag            ->Write();

    cout<<"Creating OutFile: "<<out_filename_bkgdEst<<endl;
    TFile * Out = new TFile(out_filename_bkgdEst.c_str(), "NEW");// "RECREATE");
    Out->cd();


    //-------------------------------------------------------------------------------------------------------------------
    // Write Predicted


    predDist_CHS_dRapHi_0btag_DijetMass        ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_0btag_DijetMassMod     ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_0btag_HT               ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_0btag_DeltaRap         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_0btag_JetP             ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_0btag_JetPt            ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_0btag_JetY             ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_0btag_JetSDmass        ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_0btag_JetTau32         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_0btag_maxbdisc         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_1btag_DijetMass        ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_1btag_DijetMassMod     ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_1btag_HT               ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_1btag_DeltaRap         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_1btag_JetP             ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_1btag_JetPt            ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_1btag_JetY             ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_1btag_JetSDmass        ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_1btag_JetTau32         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_1btag_maxbdisc         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_2btag_DijetMass        ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_2btag_DijetMassMod     ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_2btag_HT               ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_2btag_DeltaRap         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_2btag_JetP             ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_2btag_JetPt            ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_2btag_JetY             ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_2btag_JetSDmass        ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_2btag_JetTau32         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_2btag_maxbdisc         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_inclu_DijetMass        ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_inclu_DijetMassMod     ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_inclu_HT               ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_inclu_DeltaRap         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_inclu_JetP             ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_inclu_JetPt            ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_inclu_JetY             ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_inclu_JetSDmass        ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_inclu_JetTau32         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapHi_inclu_maxbdisc         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_0btag_DijetMass        ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_0btag_DijetMassMod     ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_0btag_HT               ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_0btag_DeltaRap         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_0btag_JetP             ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_0btag_JetPt            ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_0btag_JetY             ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_0btag_JetSDmass        ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_0btag_JetTau32         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_0btag_maxbdisc         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_1btag_DijetMass        ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_1btag_DijetMassMod     ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_1btag_HT               ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_1btag_DeltaRap         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_1btag_JetP             ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_1btag_JetPt            ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_1btag_JetY             ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_1btag_JetSDmass        ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_1btag_JetTau32         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_1btag_maxbdisc         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_2btag_DijetMass        ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_2btag_DijetMassMod     ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_2btag_HT               ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_2btag_DeltaRap         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_2btag_JetP             ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_2btag_JetPt            ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_2btag_JetY             ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_2btag_JetSDmass        ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_2btag_JetTau32         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_2btag_maxbdisc         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_inclu_DijetMass        ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_inclu_DijetMassMod     ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_inclu_HT               ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_inclu_DeltaRap         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_inclu_JetP             ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_inclu_JetPt            ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_inclu_JetY             ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_inclu_JetSDmass        ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_inclu_JetTau32         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapLo_inclu_maxbdisc         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_0btag_DijetMass        ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_0btag_DijetMassMod     ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_0btag_HT               ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_0btag_DeltaRap         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_0btag_JetP             ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_0btag_JetPt            ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_0btag_JetY             ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_0btag_JetSDmass        ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_0btag_JetTau32         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_0btag_maxbdisc         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_1btag_DijetMass        ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_1btag_DijetMassMod     ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_1btag_HT               ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_1btag_DeltaRap         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_1btag_JetP             ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_1btag_JetPt            ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_1btag_JetY             ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_1btag_JetSDmass        ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_1btag_JetTau32         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_1btag_maxbdisc         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_2btag_DijetMass        ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_2btag_DijetMassMod     ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_2btag_HT               ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_2btag_DeltaRap         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_2btag_JetP             ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_2btag_JetPt            ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_2btag_JetY             ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_2btag_JetSDmass        ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_2btag_JetTau32         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_2btag_maxbdisc         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_inclu_DijetMass        ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_inclu_DijetMassMod     ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_inclu_HT               ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_inclu_DeltaRap         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_inclu_JetP             ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_inclu_JetPt            ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_inclu_JetY             ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_inclu_JetSDmass        ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_inclu_JetTau32         ->GetPredictedHist()   ->Write();
    predDist_CHS_dRapIn_inclu_maxbdisc         ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_DijetMass      ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_DijetMassMod   ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_HT             ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_DeltaRap       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_JetP           ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_JetPt          ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_JetY           ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_JetSDmass      ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_JetTau32       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_maxbdisc       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_DijetMass      ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_DijetMassMod   ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_HT             ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_DeltaRap       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_JetP           ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_JetPt          ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_JetY           ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_JetSDmass      ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_JetTau32       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_maxbdisc       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_DijetMass      ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_DijetMassMod   ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_HT             ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_DeltaRap       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_JetP           ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_JetPt          ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_JetY           ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_JetSDmass      ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_JetTau32       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_maxbdisc       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_DijetMass      ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_DijetMassMod   ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_HT             ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_DeltaRap       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_JetP           ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_JetPt          ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_JetY           ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_JetSDmass      ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_JetTau32       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_maxbdisc       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_DijetMass      ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_DijetMassMod   ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_HT             ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_DeltaRap       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_JetP           ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_JetPt          ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_JetY           ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_JetSDmass      ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_JetTau32       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_maxbdisc       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_DijetMass      ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_DijetMassMod   ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_HT             ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_DeltaRap       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_JetP           ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_JetPt          ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_JetY           ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_JetSDmass      ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_JetTau32       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_maxbdisc       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_DijetMass      ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_DijetMassMod   ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_HT             ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_DeltaRap       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_JetP           ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_JetPt          ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_JetY           ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_JetSDmass      ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_JetTau32       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_maxbdisc       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_DijetMass      ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_DijetMassMod   ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_HT             ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_DeltaRap       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_JetP           ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_JetPt          ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_JetY           ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_JetSDmass      ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_JetTau32       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_maxbdisc       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_DijetMass      ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_DijetMassMod   ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_HT             ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_DeltaRap       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_JetP           ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_JetPt          ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_JetY           ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_JetSDmass      ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_JetTau32       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_maxbdisc       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_DijetMass      ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_DijetMassMod   ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_HT             ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_DeltaRap       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_JetP           ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_JetPt          ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_JetY           ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_JetSDmass      ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_JetTau32       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_maxbdisc       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_DijetMass      ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_DijetMassMod   ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_HT             ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_DeltaRap       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_JetP           ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_JetPt          ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_JetY           ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_JetSDmass      ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_JetTau32       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_maxbdisc       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_DijetMass      ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_DijetMassMod   ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_HT             ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_DeltaRap       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_JetP           ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_JetPt          ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_JetY           ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_JetSDmass      ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_JetTau32       ->GetPredictedHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_maxbdisc       ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_DijetMass     ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_DijetMassMod  ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_HT            ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_DeltaRap      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_JetP          ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_JetPt         ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_JetY          ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_JetSDmass     ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_JetTau32      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_maxbdisc      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_DijetMass     ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_DijetMassMod  ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_HT            ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_DeltaRap      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_JetP          ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_JetPt         ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_JetY          ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_JetSDmass     ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_JetTau32      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_maxbdisc      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_DijetMass     ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_DijetMassMod  ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_HT            ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_DeltaRap      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_JetP          ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_JetPt         ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_JetY          ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_JetSDmass     ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_JetTau32      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_maxbdisc      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_DijetMass     ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_DijetMassMod  ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_HT            ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_DeltaRap      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_JetP          ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_JetPt         ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_JetY          ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_JetSDmass     ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_JetTau32      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_maxbdisc      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_DijetMass     ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_DijetMassMod  ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_HT            ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_DeltaRap      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_JetP          ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_JetPt         ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_JetY          ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_JetSDmass     ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_JetTau32      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_maxbdisc      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_DijetMass     ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_DijetMassMod  ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_HT            ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_DeltaRap      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_JetP          ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_JetPt         ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_JetY          ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_JetSDmass     ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_JetTau32      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_maxbdisc      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_DijetMass     ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_DijetMassMod  ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_HT            ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_DeltaRap      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_JetP          ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_JetPt         ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_JetY          ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_JetSDmass     ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_JetTau32      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_maxbdisc      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_DijetMass     ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_DijetMassMod  ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_HT            ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_DeltaRap      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_JetP          ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_JetPt         ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_JetY          ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_JetSDmass     ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_JetTau32      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_maxbdisc      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_DijetMass     ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_DijetMassMod  ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_HT            ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_DeltaRap      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_JetP          ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_JetPt         ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_JetY          ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_JetSDmass     ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_JetTau32      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_maxbdisc      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_DijetMass     ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_DijetMassMod  ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_HT            ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_DeltaRap      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_JetP          ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_JetPt         ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_JetY          ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_JetSDmass     ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_JetTau32      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_maxbdisc      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_DijetMass     ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_DijetMassMod  ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_HT            ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_DeltaRap      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_JetP          ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_JetPt         ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_JetY          ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_JetSDmass     ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_JetTau32      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_maxbdisc      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_DijetMass     ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_DijetMassMod  ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_HT            ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_DeltaRap      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_JetP          ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_JetPt         ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_JetY          ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_JetSDmass     ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_JetTau32      ->GetPredictedHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_maxbdisc      ->GetPredictedHist()   ->Write();

    // if (!isFrozen || !isData ) 
    // ---------------------------------------------------------------------------
    // -- Write Observed histograms (double tagged)
    predDist_CHS_dRapHi_0btag_DijetMass        ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_0btag_DijetMassMod     ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_0btag_HT               ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_0btag_DeltaRap         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_0btag_JetP             ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_0btag_JetPt            ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_0btag_JetY             ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_0btag_JetSDmass        ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_0btag_JetTau32         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_0btag_maxbdisc         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_1btag_DijetMass        ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_1btag_DijetMassMod     ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_1btag_HT               ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_1btag_DeltaRap         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_1btag_JetP             ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_1btag_JetPt            ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_1btag_JetY             ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_1btag_JetSDmass        ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_1btag_JetTau32         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_1btag_maxbdisc         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_2btag_DijetMass        ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_2btag_DijetMassMod     ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_2btag_HT               ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_2btag_DeltaRap         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_2btag_JetP             ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_2btag_JetPt            ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_2btag_JetY             ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_2btag_JetSDmass        ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_2btag_JetTau32         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_2btag_maxbdisc         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_inclu_DijetMass        ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_inclu_DijetMassMod     ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_inclu_HT               ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_inclu_DeltaRap         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_inclu_JetP             ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_inclu_JetPt            ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_inclu_JetY             ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_inclu_JetSDmass        ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_inclu_JetTau32         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapHi_inclu_maxbdisc         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_0btag_DijetMass        ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_0btag_DijetMassMod     ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_0btag_HT               ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_0btag_DeltaRap         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_0btag_JetP             ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_0btag_JetPt            ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_0btag_JetY             ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_0btag_JetSDmass        ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_0btag_JetTau32         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_0btag_maxbdisc         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_1btag_DijetMass        ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_1btag_DijetMassMod     ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_1btag_HT               ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_1btag_DeltaRap         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_1btag_JetP             ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_1btag_JetPt            ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_1btag_JetY             ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_1btag_JetSDmass        ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_1btag_JetTau32         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_1btag_maxbdisc         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_2btag_DijetMass        ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_2btag_DijetMassMod     ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_2btag_HT               ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_2btag_DeltaRap         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_2btag_JetP             ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_2btag_JetPt            ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_2btag_JetY             ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_2btag_JetSDmass        ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_2btag_JetTau32         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_2btag_maxbdisc         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_inclu_DijetMass        ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_inclu_DijetMassMod     ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_inclu_HT               ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_inclu_DeltaRap         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_inclu_JetP             ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_inclu_JetPt            ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_inclu_JetY             ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_inclu_JetSDmass        ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_inclu_JetTau32         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapLo_inclu_maxbdisc         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_0btag_DijetMass        ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_0btag_DijetMassMod     ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_0btag_HT               ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_0btag_DeltaRap         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_0btag_JetP             ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_0btag_JetPt            ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_0btag_JetY             ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_0btag_JetSDmass        ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_0btag_JetTau32         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_0btag_maxbdisc         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_1btag_DijetMass        ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_1btag_DijetMassMod     ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_1btag_HT               ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_1btag_DeltaRap         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_1btag_JetP             ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_1btag_JetPt            ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_1btag_JetY             ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_1btag_JetSDmass        ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_1btag_JetTau32         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_1btag_maxbdisc         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_2btag_DijetMass        ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_2btag_DijetMassMod     ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_2btag_HT               ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_2btag_DeltaRap         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_2btag_JetP             ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_2btag_JetPt            ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_2btag_JetY             ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_2btag_JetSDmass        ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_2btag_JetTau32         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_2btag_maxbdisc         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_inclu_DijetMass        ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_inclu_DijetMassMod     ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_inclu_HT               ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_inclu_DeltaRap         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_inclu_JetP             ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_inclu_JetPt            ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_inclu_JetY             ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_inclu_JetSDmass        ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_inclu_JetTau32         ->GetObservedHist()   ->Write();
    predDist_CHS_dRapIn_inclu_maxbdisc         ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_DijetMass      ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_DijetMassMod   ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_HT             ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_DeltaRap       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_JetP           ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_JetPt          ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_JetY           ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_JetSDmass      ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_JetTau32       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_maxbdisc       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_DijetMass      ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_DijetMassMod   ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_HT             ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_DeltaRap       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_JetP           ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_JetPt          ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_JetY           ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_JetSDmass      ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_JetTau32       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_maxbdisc       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_DijetMass      ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_DijetMassMod   ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_HT             ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_DeltaRap       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_JetP           ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_JetPt          ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_JetY           ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_JetSDmass      ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_JetTau32       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_maxbdisc       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_DijetMass      ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_DijetMassMod   ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_HT             ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_DeltaRap       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_JetP           ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_JetPt          ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_JetY           ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_JetSDmass      ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_JetTau32       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_maxbdisc       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_DijetMass      ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_DijetMassMod   ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_HT             ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_DeltaRap       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_JetP           ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_JetPt          ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_JetY           ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_JetSDmass      ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_JetTau32       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_maxbdisc       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_DijetMass      ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_DijetMassMod   ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_HT             ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_DeltaRap       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_JetP           ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_JetPt          ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_JetY           ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_JetSDmass      ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_JetTau32       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_maxbdisc       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_DijetMass      ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_DijetMassMod   ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_HT             ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_DeltaRap       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_JetP           ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_JetPt          ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_JetY           ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_JetSDmass      ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_JetTau32       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_maxbdisc       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_DijetMass      ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_DijetMassMod   ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_HT             ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_DeltaRap       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_JetP           ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_JetPt          ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_JetY           ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_JetSDmass      ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_JetTau32       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_maxbdisc       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_DijetMass      ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_DijetMassMod   ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_HT             ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_DeltaRap       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_JetP           ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_JetPt          ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_JetY           ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_JetSDmass      ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_JetTau32       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_maxbdisc       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_DijetMass      ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_DijetMassMod   ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_HT             ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_DeltaRap       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_JetP           ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_JetPt          ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_JetY           ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_JetSDmass      ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_JetTau32       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_maxbdisc       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_DijetMass      ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_DijetMassMod   ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_HT             ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_DeltaRap       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_JetP           ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_JetPt          ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_JetY           ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_JetSDmass      ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_JetTau32       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_maxbdisc       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_DijetMass      ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_DijetMassMod   ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_HT             ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_DeltaRap       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_JetP           ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_JetPt          ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_JetY           ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_JetSDmass      ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_JetTau32       ->GetObservedHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_maxbdisc       ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_DijetMass     ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_DijetMassMod  ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_HT            ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_DeltaRap      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_JetP          ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_JetPt         ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_JetY          ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_JetSDmass     ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_JetTau32      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_maxbdisc      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_DijetMass     ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_DijetMassMod  ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_HT            ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_DeltaRap      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_JetP          ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_JetPt         ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_JetY          ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_JetSDmass     ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_JetTau32      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_maxbdisc      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_DijetMass     ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_DijetMassMod  ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_HT            ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_DeltaRap      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_JetP          ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_JetPt         ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_JetY          ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_JetSDmass     ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_JetTau32      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_maxbdisc      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_DijetMass     ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_DijetMassMod  ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_HT            ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_DeltaRap      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_JetP          ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_JetPt         ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_JetY          ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_JetSDmass     ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_JetTau32      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_maxbdisc      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_DijetMass     ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_DijetMassMod  ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_HT            ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_DeltaRap      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_JetP          ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_JetPt         ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_JetY          ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_JetSDmass     ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_JetTau32      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_maxbdisc      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_DijetMass     ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_DijetMassMod  ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_HT            ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_DeltaRap      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_JetP          ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_JetPt         ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_JetY          ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_JetSDmass     ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_JetTau32      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_maxbdisc      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_DijetMass     ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_DijetMassMod  ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_HT            ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_DeltaRap      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_JetP          ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_JetPt         ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_JetY          ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_JetSDmass     ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_JetTau32      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_maxbdisc      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_DijetMass     ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_DijetMassMod  ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_HT            ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_DeltaRap      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_JetP          ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_JetPt         ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_JetY          ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_JetSDmass     ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_JetTau32      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_maxbdisc      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_DijetMass     ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_DijetMassMod  ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_HT            ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_DeltaRap      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_JetP          ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_JetPt         ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_JetY          ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_JetSDmass     ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_JetTau32      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_maxbdisc      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_DijetMass     ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_DijetMassMod  ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_HT            ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_DeltaRap      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_JetP          ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_JetPt         ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_JetY          ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_JetSDmass     ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_JetTau32      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_maxbdisc      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_DijetMass     ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_DijetMassMod  ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_HT            ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_DeltaRap      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_JetP          ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_JetPt         ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_JetY          ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_JetSDmass     ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_JetTau32      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_maxbdisc      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_DijetMass     ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_DijetMassMod  ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_HT            ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_DeltaRap      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_JetP          ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_JetPt         ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_JetY          ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_JetSDmass     ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_JetTau32      ->GetObservedHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_maxbdisc      ->GetObservedHist()   ->Write();






    // ---------------------------------------------------------------------------
    // -- Write taggable histograms 
    predDist_CHS_dRapHi_0btag_DijetMass        ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_0btag_DijetMassMod     ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_0btag_HT               ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_0btag_DeltaRap         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_0btag_JetP             ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_0btag_JetPt            ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_0btag_JetY             ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_0btag_JetSDmass        ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_0btag_JetTau32         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_0btag_maxbdisc         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_1btag_DijetMass        ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_1btag_DijetMassMod     ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_1btag_HT               ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_1btag_DeltaRap         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_1btag_JetP             ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_1btag_JetPt            ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_1btag_JetY             ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_1btag_JetSDmass        ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_1btag_JetTau32         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_1btag_maxbdisc         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_2btag_DijetMass        ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_2btag_DijetMassMod     ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_2btag_HT               ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_2btag_DeltaRap         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_2btag_JetP             ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_2btag_JetPt            ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_2btag_JetY             ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_2btag_JetSDmass        ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_2btag_JetTau32         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_2btag_maxbdisc         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_inclu_DijetMass        ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_inclu_DijetMassMod     ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_inclu_HT               ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_inclu_DeltaRap         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_inclu_JetP             ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_inclu_JetPt            ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_inclu_JetY             ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_inclu_JetSDmass        ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_inclu_JetTau32         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapHi_inclu_maxbdisc         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_0btag_DijetMass        ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_0btag_DijetMassMod     ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_0btag_HT               ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_0btag_DeltaRap         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_0btag_JetP             ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_0btag_JetPt            ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_0btag_JetY             ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_0btag_JetSDmass        ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_0btag_JetTau32         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_0btag_maxbdisc         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_1btag_DijetMass        ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_1btag_DijetMassMod     ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_1btag_HT               ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_1btag_DeltaRap         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_1btag_JetP             ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_1btag_JetPt            ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_1btag_JetY             ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_1btag_JetSDmass        ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_1btag_JetTau32         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_1btag_maxbdisc         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_2btag_DijetMass        ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_2btag_DijetMassMod     ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_2btag_HT               ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_2btag_DeltaRap         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_2btag_JetP             ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_2btag_JetPt            ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_2btag_JetY             ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_2btag_JetSDmass        ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_2btag_JetTau32         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_2btag_maxbdisc         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_inclu_DijetMass        ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_inclu_DijetMassMod     ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_inclu_HT               ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_inclu_DeltaRap         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_inclu_JetP             ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_inclu_JetPt            ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_inclu_JetY             ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_inclu_JetSDmass        ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_inclu_JetTau32         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapLo_inclu_maxbdisc         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_0btag_DijetMass        ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_0btag_DijetMassMod     ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_0btag_HT               ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_0btag_DeltaRap         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_0btag_JetP             ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_0btag_JetPt            ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_0btag_JetY             ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_0btag_JetSDmass        ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_0btag_JetTau32         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_0btag_maxbdisc         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_1btag_DijetMass        ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_1btag_DijetMassMod     ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_1btag_HT               ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_1btag_DeltaRap         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_1btag_JetP             ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_1btag_JetPt            ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_1btag_JetY             ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_1btag_JetSDmass        ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_1btag_JetTau32         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_1btag_maxbdisc         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_2btag_DijetMass        ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_2btag_DijetMassMod     ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_2btag_HT               ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_2btag_DeltaRap         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_2btag_JetP             ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_2btag_JetPt            ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_2btag_JetY             ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_2btag_JetSDmass        ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_2btag_JetTau32         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_2btag_maxbdisc         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_inclu_DijetMass        ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_inclu_DijetMassMod     ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_inclu_HT               ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_inclu_DeltaRap         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_inclu_JetP             ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_inclu_JetPt            ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_inclu_JetY             ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_inclu_JetSDmass        ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_inclu_JetTau32         ->GetTaggableHist()   ->Write();
    predDist_CHS_dRapIn_inclu_maxbdisc         ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_DijetMass      ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_DijetMassMod   ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_HT             ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_DeltaRap       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_JetP           ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_JetPt          ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_JetY           ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_JetSDmass      ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_JetTau32       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_0btag_maxbdisc       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_DijetMass      ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_DijetMassMod   ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_HT             ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_DeltaRap       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_JetP           ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_JetPt          ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_JetY           ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_JetSDmass      ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_JetTau32       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_1btag_maxbdisc       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_DijetMass      ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_DijetMassMod   ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_HT             ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_DeltaRap       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_JetP           ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_JetPt          ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_JetY           ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_JetSDmass      ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_JetTau32       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_2btag_maxbdisc       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_DijetMass      ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_DijetMassMod   ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_HT             ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_DeltaRap       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_JetP           ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_JetPt          ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_JetY           ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_JetSDmass      ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_JetTau32       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapHi_inclu_maxbdisc       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_DijetMass      ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_DijetMassMod   ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_HT             ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_DeltaRap       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_JetP           ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_JetPt          ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_JetY           ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_JetSDmass      ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_JetTau32       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_0btag_maxbdisc       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_DijetMass      ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_DijetMassMod   ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_HT             ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_DeltaRap       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_JetP           ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_JetPt          ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_JetY           ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_JetSDmass      ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_JetTau32       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_1btag_maxbdisc       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_DijetMass      ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_DijetMassMod   ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_HT             ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_DeltaRap       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_JetP           ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_JetPt          ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_JetY           ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_JetSDmass      ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_JetTau32       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_2btag_maxbdisc       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_DijetMass      ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_DijetMassMod   ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_HT             ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_DeltaRap       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_JetP           ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_JetPt          ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_JetY           ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_JetSDmass      ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_JetTau32       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapLo_inclu_maxbdisc       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_DijetMass      ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_DijetMassMod   ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_HT             ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_DeltaRap       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_JetP           ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_JetPt          ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_JetY           ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_JetSDmass      ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_JetTau32       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_0btag_maxbdisc       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_DijetMass      ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_DijetMassMod   ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_HT             ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_DeltaRap       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_JetP           ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_JetPt          ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_JetY           ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_JetSDmass      ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_JetTau32       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_1btag_maxbdisc       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_DijetMass      ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_DijetMassMod   ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_HT             ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_DeltaRap       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_JetP           ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_JetPt          ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_JetY           ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_JetSDmass      ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_JetTau32       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_2btag_maxbdisc       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_DijetMass      ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_DijetMassMod   ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_HT             ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_DeltaRap       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_JetP           ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_JetPt          ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_JetY           ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_JetSDmass      ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_JetTau32       ->GetTaggableHist()   ->Write();
    predDist_Puppi_dRapIn_inclu_maxbdisc       ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_DijetMass     ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_DijetMassMod  ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_HT            ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_DeltaRap      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_JetP          ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_JetPt         ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_JetY          ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_JetSDmass     ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_JetTau32      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_0btag_maxbdisc      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_DijetMass     ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_DijetMassMod  ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_HT            ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_DeltaRap      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_JetP          ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_JetPt         ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_JetY          ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_JetSDmass     ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_JetTau32      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_1btag_maxbdisc      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_DijetMass     ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_DijetMassMod  ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_HT            ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_DeltaRap      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_JetP          ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_JetPt         ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_JetY          ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_JetSDmass     ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_JetTau32      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_2btag_maxbdisc      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_DijetMass     ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_DijetMassMod  ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_HT            ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_DeltaRap      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_JetP          ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_JetPt         ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_JetY          ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_JetSDmass     ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_JetTau32      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapHi_inclu_maxbdisc      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_DijetMass     ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_DijetMassMod  ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_HT            ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_DeltaRap      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_JetP          ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_JetPt         ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_JetY          ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_JetSDmass     ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_JetTau32      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_0btag_maxbdisc      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_DijetMass     ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_DijetMassMod  ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_HT            ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_DeltaRap      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_JetP          ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_JetPt         ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_JetY          ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_JetSDmass     ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_JetTau32      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_1btag_maxbdisc      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_DijetMass     ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_DijetMassMod  ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_HT            ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_DeltaRap      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_JetP          ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_JetPt         ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_JetY          ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_JetSDmass     ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_JetTau32      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_2btag_maxbdisc      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_DijetMass     ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_DijetMassMod  ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_HT            ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_DeltaRap      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_JetP          ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_JetPt         ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_JetY          ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_JetSDmass     ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_JetTau32      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapLo_inclu_maxbdisc      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_DijetMass     ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_DijetMassMod  ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_HT            ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_DeltaRap      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_JetP          ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_JetPt         ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_JetY          ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_JetSDmass     ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_JetTau32      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_0btag_maxbdisc      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_DijetMass     ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_DijetMassMod  ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_HT            ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_DeltaRap      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_JetP          ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_JetPt         ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_JetY          ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_JetSDmass     ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_JetTau32      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_1btag_maxbdisc      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_DijetMass     ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_DijetMassMod  ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_HT            ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_DeltaRap      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_JetP          ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_JetPt         ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_JetY          ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_JetSDmass     ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_JetTau32      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_2btag_maxbdisc      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_DijetMass     ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_DijetMassMod  ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_HT            ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_DeltaRap      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_JetP          ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_JetPt         ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_JetY          ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_JetSDmass     ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_JetTau32      ->GetTaggableHist()   ->Write();
    predDist_AltTag_dRapIn_inclu_maxbdisc      ->GetTaggableHist()   ->Write();

    // ---------------------------------------------------------------------------
    // -- Write additional test histograms
    h_DijetMass_modMass_jet0                                     ->Write();                                                               
    h_DijetMass_modMass_jet1                                     ->Write();  


    h_CutFlow                                                     ->Write();                   
    h_EventWeight                                                 ->Write();                   
    h_BtagCategoriesPreSF                                         ->Write();                   
    h_BtagCategoriesPostSF                                        ->Write();                   

    Out->Close();
  }
  cout<<"Nevents tree                     =  "<< treeNentries                 <<endl;
  cout<<"Nevents Cutflow 0                =  "<< h_CutFlow->GetBinContent(1) <<endl;
  cout<<"Nevents Cutflow 1 (Jet0 Jet1 pT) =  "<< h_CutFlow->GetBinContent(2) <<endl;
  cout<<"Nevents Cutflow 2 (HT)           =  "<< h_CutFlow->GetBinContent(3) <<endl;
  cout<<"Nevents Cutflow 3 (deltaPhi)     =  "<< h_CutFlow->GetBinContent(4) <<endl;
  cout<<"Nevents Cutflow 4 (NoiseFilters) =  "<< h_CutFlow->GetBinContent(5) <<endl;
  cout<<"Nevents doublecheck preselection =  "<< h_Jet0Pt->Integral()          <<endl;

  // Make ModMass File
  if (isQCDMC){
    cout<<"Making new ModMass file"<<endl;
    string modMassOutName = "runs/run"+savelabel+"/ModMass_Jetpt600HT1000_"+savelabel+"_"+input_file;

    TFile * ModMassOut = new TFile(modMassOutName.c_str(),"RECREATE");
    ModMassOut->cd();
      
    h_mAK8_ModMass->Write();
    h_mAK8_ModMass_jet0->Write();
    h_mAK8_ModMass_jet1->Write();

    h_mSDropAK8_ModMass->Write();
    h_mSDropAK8_ModMass_jet0->Write();
    h_mSDropAK8_ModMass_jet1->Write();

    h_mPuppiSDropAK8_ModMass->Write();
    h_mPuppiSDropAK8_ModMass_jet0->Write();
    h_mPuppiSDropAK8_ModMass_jet1->Write();

    ModMassOut->Close();
    cout<<"Done writing: "<<modMassOutName<<endl;
  }
}



//b-tag scale factor
bool applySF (bool isBTagged, float Btag_SF, float Btag_eff)
{
  bool newBTag = bool(isBTagged);
  float mistagPercent;

  if (Btag_SF == 1) return newBTag; //no correction needed                                                                                                                                                                        
  //throw dice
  TRandom3 rand2(0);
  double coin  = rand2.Uniform(0,1.0);

  if (Btag_SF > 1){  //use this if SF>1
    if (!isBTagged){
      //fraction of jets that need to be upgraded
      mistagPercent = (1.0 - Btag_SF) / (1.0 - (1.0/Btag_eff) );
      //upgrade to tagged
      if ( coin < mistagPercent ) newBTag = true;
    }
  }
  else{  //use this if SF<1
    //downgrade tagged to untagged
    if ( isBTagged && coin > Btag_SF ){
      newBTag = false;
    }
  }
  return bool(newBTag);
}
