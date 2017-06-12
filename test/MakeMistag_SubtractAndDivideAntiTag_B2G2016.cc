// MakeMistag_SubtractAndDivideAntiTag.cc
// Divide two histograms to calculate mistag rate or efficiency
// [] .L MakeMistag_SubtractAndDivideAntiTag.cc+
// [] run()

#include "TROOT.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TEfficiency.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TMath.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void makeHists( string , double , vector<double>, string);

void run(string label){

  //label "20160529tagfix_nom_PUw";
  double lumi = 35922; //pb-1
  
  // Define mistag rate bins
  vector <double> bins_small;
  vector <double> bins_0btag;
  vector <double> bins_0btags;
  vector <double> bins_1btag;
  vector <double> bins_1btagt;
  vector <double> bins_2btag;
  vector <double> bins_constant;
  vector <double> bins_big;
  vector <double> bins_eta;

  int x;

  // Small bins (for visual not for bkgd est)
  cout<<"Define small bins: ";
  x=400;
  while (x<=7000){
    cout<<" "<<x;
    bins_small.push_back(x);
    if ( x<1000) x+=50;
    else if (x<2000) x+=100;
    else if (x<4000) x+=500;
    else if (x<5000) x+=1000;
    else x+=2000;
  }
  cout<<endl;

  //0 btag
  cout<<"Define 0btag bins: ";
  x=400;
  while (x<=7000){
    cout<<" "<<x;
    bins_0btag.push_back(x);
    if ( x<1000) x+=100;
    else if (x<1200) x+=200;
    else if (x<1500) x+=300;
    else if (x<2000) x+=500;
    else if (x<3000) x+=1000;
    else x+=4000;
  }
  cout<<endl;

  //0 btag small start
  cout<<"Define 0btag small low pt bins: ";
  x=400;
  while (x<=7000){
    cout<<" "<<x;
    bins_0btags.push_back(x);
    if ( x<1000) x+=50;
    else if (x<1400) x+=100;
    else if (x<1600) x+=200;
    else if (x<2000) x+=400;
    else if (x<3000) x+=1000;
    else x+=4000;
  }
  cout<<endl;


  // 1 btag
  cout<<"Define 1btag bins: ";
  x=400;
  while (x<=7000){
    cout<<" "<<x;
    bins_1btag.push_back(x);
    if ( x<600) x+=50;
    else if (x<800)  x+=100;
    else if (x<1000) x+=200;
    else if (x<1400) x+=400;
    else if (x<2000) x+=600;
    else if (x<3000) x+=1000;
    else x+=4000;
  }
  cout<<endl;


  cout<<"Define 1btag bins with big tail: ";
  x=400;
  while (x<=7000){
    cout<<" "<<x;
    bins_1btagt.push_back(x);
    if ( x<600) x+=100;
    else if (x<1000) x+=200;
    else if (x<1400) x+=400;
    else if (x<2000) x+=600;
    else if (x<3000) x+=1000;
    else x+=4000;
  }
  cout<<endl;

  // // 1 btag
  // cout<<"Define 1btag bins: ";
  // x=400;
  // while (x<=7000){
  //   cout<<" "<<x;
  //   bins_1btag.push_back(x);
  //   if ( x<600) x+=100;
  //   else if (x<1000) x+=200;
  //   else if (x<1400) x+=400;
  //   else if (x<2000) x+=600;
  //   else if (x<3000) x+=1000;
  //   else x+=4000;
  // }
  // cout<<endl;


  // 2 btag
  cout<<"Define 2btag bins: ";
  x=400;
  while (x<=7000){
    cout<<" "<<x;
    bins_2btag.push_back(x);
    if ( x<500) x+=100;
    else if (x<700) x+=200;
    else if (x<1000) x+=300;
    else if (x<3000) x+=1000;
    else x+=4000;
  }
  cout<<endl;


  // bins_constant
  cout<<"constant bins: ";
  x=400;
  while (x<=6000){
    cout<<" "<<x;
    bins_constant.push_back(x);
    x+=200;
  }
  cout<<endl;




  // bool data, bool noSubtract, vector of bins            makeHists( bool data, bool noSubtract, vector<double> bins ){
  makeHists( label, lumi, bins_small    , "small" );     
  makeHists( label, lumi, bins_0btag    , "0btag" );     
  makeHists( label, lumi, bins_1btag    , "1btag" );     
  makeHists( label, lumi, bins_2btag    , "2btag" );     
  makeHists( label, lumi, bins_constant , "const" );     
  makeHists( label, lumi, bins_1btagt   , "1btagtail" ); 
  makeHists( label, lumi, bins_0btags   , "0btagsmall" );



}


// void makeHists( bool data = false, bool noSubtract = false, vector<int> bins ){
void makeHists( string label, double luminosity, vector<double> bins, string binslabel ){
	// Get input file and setup output file
  TFile * InFile;
  TFile * InFile2;
  TFile * OutFileBigBins;
  TFile * OutFile;

  string infolder = "/uscms_data/d2/jdolen/B2G2016/CMSSW_8_0_26_patch2/src/Analysis/B2GTTbar/test/runs/";
  // string infolder = "/Users/jdolen/NoBackup/B2G2016/V5/runs/";
  // string infolder = "/Users/jdolen/Code/GitHub/B2GTTbar/test/runs/";

  vector <string> primary_files;
  vector <string> secondary_files;
  vector <bool> subtract_secondary;
  vector <string> outfile_savename;

// 20160420_ht1000_pt500_WPC_alt40_alt260_bM_PUw_noTTw_nom
// _20160512full_ht950_pt400_WPB_alt40_alt260_bM_PUw_noTTw_nom_b2gtreeV5

  string sdata  = "histsAntiTag_"+label+"_TTw_nom_b2gtreeV5_JetHT_all.root";
  string sqcdht = "histsAntiTag_"+label+"_TTw_nom_b2gtreeV5_QCD_HTscaled.root";
  string sqcdpt = "histsAntiTag_"+label+"_TTw_nom_b2gtreeV5_QCD_Ptscaled.root";
  string stt    = "histsAntiTag_"+label+"_noTTw_nom_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root";
  string sttw   = "histsAntiTag_"+label+"_TTw_nom_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root";


  string stt_PU_dn     = "histsAntiTag_20160516checkSystMistag_ht950_pt400_WPB_alt40_alt260_bM_PUw_noTTw_PU_dn_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root";
  string stt_PU_up     = "histsAntiTag_20160516checkSystMistag_ht950_pt400_WPB_alt40_alt260_bM_PUw_noTTw_PU_up_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root";
  string stt_btag_dn   = "histsAntiTag_20160516checkSystMistag_ht950_pt400_WPB_alt40_alt260_bM_PUw_noTTw_bTag_dn_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root";
  string stt_btag_up   = "histsAntiTag_20160516checkSystMistag_ht950_pt400_WPB_alt40_alt260_bM_PUw_noTTw_bTag_up_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root";
  string stt_jec_dn    = "histsAntiTag_20160516checkSystMistag_ht950_pt400_WPB_alt40_alt260_bM_PUw_noTTw_jec_dn_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root";
  string stt_jec_up    = "histsAntiTag_20160516checkSystMistag_ht950_pt400_WPB_alt40_alt260_bM_PUw_noTTw_jec_up_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root";
  string stt_jer_dn    = "histsAntiTag_20160516checkSystMistag_ht950_pt400_WPB_alt40_alt260_bM_PUw_noTTw_jer_dn_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root";
  string stt_jer_up    = "histsAntiTag_20160516checkSystMistag_ht950_pt400_WPB_alt40_alt260_bM_PUw_noTTw_jer_up_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root";
  string stt_pdf_dn    = "histsAntiTag_20160516checkSystMistag_ht950_pt400_WPB_alt40_alt260_bM_PUw_noTTw_pdf_dn_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root";
  string stt_pdf_up    = "histsAntiTag_20160516checkSystMistag_ht950_pt400_WPB_alt40_alt260_bM_PUw_noTTw_pdf_up_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root";
  string stt_q2_dn     = "histsAntiTag_20160516checkSystMistag_ht950_pt400_WPB_alt40_alt260_bM_PUw_noTTw_q2_dn_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root";
  string stt_q2_up     = "histsAntiTag_20160516checkSystMistag_ht950_pt400_WPB_alt40_alt260_bM_PUw_noTTw_q2_up_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root";



  primary_files.push_back(sdata.c_str()  );   secondary_files.push_back(           stt.c_str() );  subtract_secondary.push_back(true);    outfile_savename.push_back("data_subtract_ttbar");
  primary_files.push_back(sdata.c_str()  );   secondary_files.push_back(          sttw.c_str() );  subtract_secondary.push_back(true);    outfile_savename.push_back("data_subtract_ttbarw");
  primary_files.push_back(sdata.c_str()  );   secondary_files.push_back(           stt.c_str() );  subtract_secondary.push_back(false);   outfile_savename.push_back("data_nosubtract_ttbar");
  primary_files.push_back(sqcdht.c_str() );   secondary_files.push_back(           stt.c_str() );  subtract_secondary.push_back(false);   outfile_savename.push_back("QCDHT");
  primary_files.push_back(sqcdpt.c_str() );   secondary_files.push_back(           stt.c_str() );  subtract_secondary.push_back(false);   outfile_savename.push_back("QCDPt");
  // primary_files.push_back(sdata.c_str()  );   secondary_files.push_back(     stt_PU_dn.c_str() );  subtract_secondary.push_back(true);    outfile_savename.push_back("data_subtract_ttbar_PU_dn");
  // primary_files.push_back(sdata.c_str()  );   secondary_files.push_back(     stt_PU_up.c_str() );  subtract_secondary.push_back(true);    outfile_savename.push_back("data_subtract_ttbar_PU_up");
  // primary_files.push_back(sdata.c_str()  );   secondary_files.push_back(   stt_btag_dn.c_str() );  subtract_secondary.push_back(true);    outfile_savename.push_back("data_subtract_ttbar_btag_dn");
  // primary_files.push_back(sdata.c_str()  );   secondary_files.push_back(   stt_btag_up.c_str() );  subtract_secondary.push_back(true);    outfile_savename.push_back("data_subtract_ttbar_btag_up");
  // primary_files.push_back(sdata.c_str()  );   secondary_files.push_back(    stt_jec_dn.c_str() );  subtract_secondary.push_back(true);    outfile_savename.push_back("data_subtract_ttbar_jec_dn");
  // primary_files.push_back(sdata.c_str()  );   secondary_files.push_back(    stt_jec_up.c_str() );  subtract_secondary.push_back(true);    outfile_savename.push_back("data_subtract_ttbar_jec_up");
  // primary_files.push_back(sdata.c_str()  );   secondary_files.push_back(    stt_jer_dn.c_str() );  subtract_secondary.push_back(true);    outfile_savename.push_back("data_subtract_ttbar_jer_dn");
  // primary_files.push_back(sdata.c_str()  );   secondary_files.push_back(    stt_jer_up.c_str() );  subtract_secondary.push_back(true);    outfile_savename.push_back("data_subtract_ttbar_jer_up");
  // primary_files.push_back(sdata.c_str()  );   secondary_files.push_back(    stt_pdf_dn.c_str() );  subtract_secondary.push_back(true);    outfile_savename.push_back("data_subtract_ttbar_pdf_dn");
  // primary_files.push_back(sdata.c_str()  );   secondary_files.push_back(    stt_pdf_up.c_str() );  subtract_secondary.push_back(true);    outfile_savename.push_back("data_subtract_ttbar_pdf_up");
  // primary_files.push_back(sdata.c_str()  );   secondary_files.push_back(     stt_q2_dn.c_str() );  subtract_secondary.push_back(true);    outfile_savename.push_back("data_subtract_ttbar_q2_dn");
  // primary_files.push_back(sdata.c_str()  );   secondary_files.push_back(     stt_q2_up.c_str() );  subtract_secondary.push_back(true);    outfile_savename.push_back("data_subtract_ttbar_q2_up");

  

 





  int nbins = bins.size();
  stringstream temp1;
  temp1 << nbins;
  string snbins = temp1 .str();

  cout<<"start file loop"<<endl;
  for (unsigned int ifile=0; ifile<primary_files.size(); ifile++){
    cout<<endl;
    string outfile_name ;
    outfile_name = "MistagRate_"+binslabel+"_"+label+"_"+outfile_savename[ifile]+".root";

    string primary_name = infolder + primary_files[ifile];
    string secondary_name = infolder + secondary_files[ifile];;
    cout<<"Opening "<<primary_name<<endl;

    InFile        = new TFile(      primary_name.c_str()      );
    OutFile       = new TFile(      outfile_name.c_str()        , "RECREATE");
    if (subtract_secondary[ifile] ) InFile2  = new TFile(secondary_name.c_str()     );



 
    if (InFile    ->IsZombie() ){ cout<<"InFile   ->IsZombie()"<<endl; delete InFile   ; InFile    = 0;}
    if (InFile   ==0) { cout<<"Did not open "<<primary_name<<endl; return; } else {cout<<"Opened "<<primary_name<<endl; }
    if (subtract_secondary[ifile] ) {
      if (InFile2    ->IsZombie() ){ cout<<"InFile2   ->IsZombie()"<<endl; delete InFile2   ; InFile2    = 0;}
      if (InFile2   ==0) { cout<<"Did not open "<<secondary_name<<endl; return; } else {cout<<"Opened "<<secondary_name<<endl; }  
    }
    OutFile->cd();

    // Loop over anti-tag and tag combinations and make mistag rate
    vector <string> antitag_def;
    vector <string> tag_def;

    antitag_def.push_back("AntiTagCHS");
    antitag_def.push_back("AntiTagPuppi");
    antitag_def.push_back("alt_AntiTagCHS");
    antitag_def.push_back("alt2_AntiTagCHS");
    // antitag_def.push_back("alt_AntiTagPuppi");
    // antitag_def.push_back("alt2_AntiTagPuppi");


    tag_def.push_back("_TagMassSDTau32"   );
    tag_def.push_back("_TagMassSD"        );
    tag_def.push_back("_TagTau32"         );

    string pre = "h_";
    string save_pre = "h_mistag_";
    string probe = "_Probe";
    vector <string> post;
    vector <bool> rebin;

    post.push_back("_jetP_dRapIn_inclusive");       rebin.push_back(true);            
    post.push_back("_jetP_dRapIn_0btag");           rebin.push_back(true);        
    post.push_back("_jetP_dRapIn_1btag");           rebin.push_back(true);        
    post.push_back("_jetP_dRapIn_2btag");           rebin.push_back(true);        
    post.push_back("_jetP_dRapHi_inclusive");       rebin.push_back(true);            
    post.push_back("_jetP_dRapHi_0btag");           rebin.push_back(true);        
    post.push_back("_jetP_dRapHi_1btag");           rebin.push_back(true);        
    post.push_back("_jetP_dRapHi_2btag");           rebin.push_back(true);        
    post.push_back("_jetP_dRapLo_inclusive");       rebin.push_back(true);            
    post.push_back("_jetP_dRapLo_0btag");           rebin.push_back(true);        
    post.push_back("_jetP_dRapLo_1btag");           rebin.push_back(true);        
    post.push_back("_jetP_dRapLo_2btag");           rebin.push_back(true);        

    post.push_back("_jetY_dRapIn_inclusive");       rebin.push_back(false);            
    post.push_back("_jetY_dRapIn_0btag");           rebin.push_back(false);        
    post.push_back("_jetY_dRapIn_1btag");           rebin.push_back(false);        
    post.push_back("_jetY_dRapIn_2btag");           rebin.push_back(false);        
    post.push_back("_jetY_dRapHi_inclusive");       rebin.push_back(false);            
    post.push_back("_jetY_dRapHi_0btag");           rebin.push_back(false);        
    post.push_back("_jetY_dRapHi_1btag");           rebin.push_back(false);        
    post.push_back("_jetY_dRapHi_2btag");           rebin.push_back(false);        
    post.push_back("_jetY_dRapLo_inclusive");       rebin.push_back(false);            
    post.push_back("_jetY_dRapLo_0btag");           rebin.push_back(false);        
    post.push_back("_jetY_dRapLo_1btag");           rebin.push_back(false);        
    post.push_back("_jetY_dRapLo_2btag");           rebin.push_back(false);        

    post.push_back("_Nvtx_dRapIn_inclusive");       rebin.push_back(false);            
    post.push_back("_Nvtx_dRapIn_0btag");           rebin.push_back(false);        
    post.push_back("_Nvtx_dRapIn_1btag");           rebin.push_back(false);        
    post.push_back("_Nvtx_dRapIn_2btag");           rebin.push_back(false);        
    post.push_back("_Nvtx_dRapHi_inclusive");       rebin.push_back(false);            
    post.push_back("_Nvtx_dRapHi_0btag");           rebin.push_back(false);        
    post.push_back("_Nvtx_dRapHi_1btag");           rebin.push_back(false);        
    post.push_back("_Nvtx_dRapHi_2btag");           rebin.push_back(false);        
    post.push_back("_Nvtx_dRapLo_inclusive");       rebin.push_back(false);            
    post.push_back("_Nvtx_dRapLo_0btag");           rebin.push_back(false);        
    post.push_back("_Nvtx_dRapLo_1btag");           rebin.push_back(false);        
    post.push_back("_Nvtx_dRapLo_2btag");           rebin.push_back(false);        


    for (unsigned int ii=0; ii<antitag_def.size(); ii++ ){
      for (unsigned int jj=0; jj<tag_def.size(); jj++ ){
        for (unsigned int kk=0; kk<post.size(); kk++ ){
          // cout<<"antitag_def["<<ii<<"] "<<antitag_def[ii]<<endl;
          cout<<" File iteration "<<ifile<<" outfile "<<outfile_savename[ifile]<<" hist iteration "<<ii<<" "<<" "<<jj<<" "<<kk<<" rebin "<<rebin[kk]<<endl;
          string numer = pre + antitag_def[ii] + tag_def[jj] + post[kk] ;
          string denom = pre + antitag_def[ii] + probe + post[kk] ;
          string savename  = save_pre + antitag_def[ii] + tag_def[jj] + post[kk] ;
          cout <<"numer   : "<<numer<<endl;
          cout <<"denom   : "<<denom<<endl;


          // Skip hisotgrams that don't exist
          if (  (antitag_def[ii]=="alt_AntiTagCHS"   || 
                 antitag_def[ii]=="alt2_AntiTagCHS"  || 
                 antitag_def[ii]=="alt_AntiTagPuppi" || 
                 antitag_def[ii]=="alt2_AntiTagPuppi" 
                )
                && 
                !rebin[kk]) continue; 
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && antitag_def[ii]== "AntiTagCHS"          ) continue;
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && antitag_def[ii]== "alt_AntiTagCHS"      ) continue;
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && antitag_def[ii]== "alt2_AntiTagCHS"     ) continue;
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && antitag_def[ii]== "alt_AntiTagPuppi"    ) continue;
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && antitag_def[ii]== "alt2_AntiTagPuppi"   ) continue;
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && post[kk]=="_jetP_dRapHi_inclusive"  ) continue;
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && post[kk]=="_jetP_dRapHi_0btag"      ) continue;    
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && post[kk]=="_jetP_dRapHi_1btag"      ) continue;    
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && post[kk]=="_jetP_dRapHi_2btag"      ) continue;    
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && post[kk]=="_jetP_dRapLo_inclusive"  ) continue;
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && post[kk]=="_jetP_dRapLo_0btag"      ) continue;    
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && post[kk]=="_jetP_dRapLo_1btag"      ) continue;    
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && post[kk]=="_jetP_dRapLo_2btag"      ) continue;    
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && post[kk]=="_jetY_dRapHi_inclusive"  ) continue;
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && post[kk]=="_jetY_dRapHi_0btag"      ) continue;    
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && post[kk]=="_jetY_dRapHi_1btag"      ) continue;    
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && post[kk]=="_jetY_dRapHi_2btag"      ) continue;    
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && post[kk]=="_jetY_dRapLo_inclusive"  ) continue;
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && post[kk]=="_jetY_dRapLo_0btag"      ) continue;    
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && post[kk]=="_jetY_dRapLo_1btag"      ) continue;    
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && post[kk]=="_jetY_dRapLo_2btag"      ) continue;      
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && post[kk]=="_Nvtx_dRapHi_inclusive"  ) continue;
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && post[kk]=="_Nvtx_dRapHi_0btag"      ) continue;    
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && post[kk]=="_Nvtx_dRapHi_1btag"      ) continue;    
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && post[kk]=="_Nvtx_dRapHi_2btag"      ) continue;    
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && post[kk]=="_Nvtx_dRapLo_inclusive"  ) continue;
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && post[kk]=="_Nvtx_dRapLo_0btag"      ) continue;    
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && post[kk]=="_Nvtx_dRapLo_1btag"      ) continue;    
          if (  (tag_def[jj] == "_TagMassSD"  || tag_def[jj] == "_TagTau32" ) && post[kk]=="_Nvtx_dRapLo_2btag"      ) continue;    


          TH1D * primary_numer = (TH1D*) InFile->Get(numer.c_str());
          TH1D * primary_denom = (TH1D*) InFile->Get(denom.c_str());

          if (primary_numer) cout<<"got primary: "<<numer<<endl;
          else{ cout<<"CHECK: did not get primary: "<<numer<<endl; continue;}
          if (primary_denom) cout<<"got primary: "<<denom<<endl;
          else{ cout<<"CHECK: did not get primary: "<<denom<<endl; continue;}

          primary_numer  ->Sumw2();
          primary_denom  ->Sumw2();
          
          TH1D *primary_numer_new =(TH1D*) primary_numer->Clone();
          TH1D *primary_denom_new =(TH1D*) primary_denom->Clone();

          cout<<"original hist numer "<<primary_numer_new->Integral()<<endl;
          cout<<"original hist denom "<<primary_denom_new->Integral()<<endl;
          // primary_numer_new->Sumw2();
          // primary_denom_new->Sumw2();

          // rebin with variable width bins

          int nbins = bins.size();
          double *xbins=new double[nbins];
          // double xbins[nbins];
          for( unsigned int ibin = 0; ibin < bins.size(); ibin++) xbins[ibin] = bins[ibin];
          // for( unsigned int i = 0; i < bins.size(); i++) cout<<xbins[i]<<" ";
          // cout<<endl;
          cout<<"nbins "<<nbins<<endl;

          TH1D* primary_numer_rebin ;
          TH1D* primary_denom_rebin ;

          if (rebin[kk]){
            primary_numer_rebin = (TH1D*)primary_numer_new->Rebin(nbins-1,"primary_numer_rebin",xbins);
            primary_denom_rebin = (TH1D*)primary_denom_new->Rebin(nbins-1,"primary_denom_rebin",xbins);
          }
          else{
            primary_numer_rebin =  primary_numer_new;
            primary_denom_rebin =  primary_denom_new;
          }
          // primary_numer_rebin->Sumw2(); 
          // primary_denom_rebin->Sumw2();

          TH1D *secondary_numer_rebin;
          TH1D *secondary_denom_rebin;
          if (subtract_secondary[ifile]){

            TH1D * secondary_numer = (TH1D*)InFile2->Get(numer.c_str());
            TH1D * secondary_denom = (TH1D*)InFile2->Get(denom.c_str());


            if (secondary_numer) cout<<"got secondary: "<<numer<<endl;
            else{ cout<<"CHECK: CHECK: did not get secondary: "<<numer<<endl; continue;}
            if (secondary_denom) cout<<"got secondary:"<<denom<<endl;
            else{ cout<<"CHECK: did not get secondary: "<<denom<<endl; continue;}


            secondary_numer ->Sumw2();
            secondary_denom ->Sumw2();
            TH1D *secondary_numer_new;
            TH1D *secondary_denom_new;
            secondary_numer_new =(TH1D*) secondary_numer->Clone();
            secondary_denom_new =(TH1D*) secondary_denom->Clone();
            // secondary_numer_new->Sumw2();
            // secondary_denom_new->Sumw2(); 
            if (rebin[kk]){
              secondary_numer_rebin = (TH1D*)secondary_numer_new->Rebin(nbins-1,"secondary_numer_rebin",xbins);
              secondary_denom_rebin = (TH1D*)secondary_denom_new->Rebin(nbins-1,"secondary_denom_rebin",xbins);
            }
            else{
              secondary_numer_rebin =  secondary_numer_new;
              secondary_denom_rebin =  secondary_denom_new;
            }
            // secondary_numer_rebin ->Sumw2();
            // secondary_denom_rebin ->Sumw2(); 
          
            float average_tt_pt_weight = 1.0;

            if (outfile_savename[ifile] == "data_subtract_ttbarw" ) average_tt_pt_weight = 0.82;


            double nevents_dataset_ttbar =  77229341 + 78006311 ;// = 92925926;//92925926; //96834559;
            double xsec_ttbar  =  831.76  ;
            double kfactor  =  0.7 ; //0.94;
            double toptagsf =  1.0 ; //0.89;
            double scale_ttbar= toptagsf * toptagsf * kfactor * xsec_ttbar * luminosity / ( nevents_dataset_ttbar * average_tt_pt_weight );
          

            cout<<"scale_ttbar "<<scale_ttbar<<" ( lumi = "<<luminosity<<" , xsec = "<<xsec_ttbar<<" , nevents = "<<nevents_dataset_ttbar <<" )" <<endl;
            secondary_numer_rebin->Scale(scale_ttbar);
            secondary_denom_rebin->Scale(scale_ttbar);

            string secondary_numer_name = "check_"+antitag_def[ii] + tag_def[jj] + post[kk] +"_ttbar";
            string secondary_denom_name = "check_"+antitag_def[ii] + probe      + post[kk] +"_ttbar";
            secondary_numer_rebin ->SetName(secondary_numer_name.c_str() );
            secondary_denom_rebin ->SetName(secondary_denom_name.c_str() );
            // secondary_numer_rebin ->Write();
            // secondary_denom_rebin ->Write();


            cout<<"secondary numer "<<secondary_numer_rebin->Integral()<<endl;
            cout<<"secondary denom "<<secondary_denom_rebin->Integral()<<endl;
            cout<<"primary pre subtract numer "<<primary_numer_rebin->Integral()<<endl;
            cout<<"primary pre subtract denom "<<primary_denom_rebin->Integral()<<endl;
            primary_numer_rebin->Add(secondary_numer_rebin,-1);
            primary_denom_rebin->Add(secondary_denom_rebin,-1);
            cout<<"primary post subtract numer "<<primary_numer_rebin->Integral()<<endl;
            cout<<"primary post subtract denom "<<primary_denom_rebin->Integral()<<endl;
            // string data_subtract_numer_name =  "check_"+antitag_def[i] + tag_def[j] + post[k] +"_data_subtract";
            // string data_subtract_denom_name =  "check_"+antitag_def[i] + probe      + post[k] +"_data_subtract";
            // primary_numer_rebin ->SetName(data_subtract_numer_name.c_str() );
            // primary_denom_rebin ->SetName(data_subtract_denom_name.c_str() );
            // primary_numer_rebin ->Write();
            // primary_denom_rebin ->Write();
          }

          cout<<"outfile string : "<<outfile_savename[ifile]<<endl;
          cout<<"about to divide : numer "<<primary_numer_rebin->Integral()<<endl;
          cout<<"about to divide : denom "<<primary_denom_rebin->Integral()<<endl;
          primary_numer_rebin->Divide(primary_numer_rebin,primary_denom_rebin,1,1,"B");
          primary_numer_rebin->SetTitle(";Jet PT (GeV/c);Top Mistag Rate");
          primary_numer_rebin->SetName(savename.c_str());
          primary_numer_rebin->Write();
          cout<<endl;


        }
      }
    }
    OutFile->cd();
    // OutFile->Write();
    OutFile->Close();
  }

  bins.clear();
  primary_files.clear();
  secondary_files.clear();
  subtract_secondary.clear();
  outfile_savename.clear();
  
  cout<<"Exiting: bins.size() "<<bins.size()<<endl;
}
