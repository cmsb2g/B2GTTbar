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

void makeHists( string , double , vector<double>);

void run(){

  string date = "20161203";
  double lumi = 36220; //pb-1
  
  // Define mistag rate bins
  vector <double> bins_small;
  vector <double> bins_0btag;
  vector <double> bins_1btag;
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
    else x+=1000;
  }
  cout<<endl;

  //0 btag
  cout<<"Define 0btag bins: ";
  x=400;
  while (x<=6000){
    cout<<" "<<x;
    bins_0btag.push_back(x);
    if ( x<1000) x+=100;
    else if (x<1200) x+=200;
    else if (x<1500) x+=300;
    else if (x<2000) x+=500;
    else if (x<5000) x+=1000;
    else x+=1000;
  }
  cout<<endl;

  // 1 btag
  cout<<"Define 1btag bins: ";
  x=400;
  while (x<=5000){
    cout<<" "<<x;
    bins_1btag.push_back(x);
    if ( x<600) x+=100;
    else if (x<1000) x+=200;
    else if (x<1400) x+=400;
    else if (x<2000) x+=600;
    else if (x<3000) x+=1000;
    else x+=2000;
  }
  cout<<endl;

  // 2 btag
  cout<<"Define 2btag bins: ";
  x=400;
  while (x<=6000){
    cout<<" "<<x;
    bins_2btag.push_back(x);
    if ( x<600) x+=200;
    else if (x<5000) x+=1000;
    else x+=1000;
  }
  cout<<endl;

  // big bins
  cout<<"Define big bins: ";
  x=400;
  while (x<=8000){
    cout<<" "<<x;
    bins_big.push_back(x);
    if ( x<1000) x+=100;
    else x+=6000;
    // else if (x<2000) x+=200;
    // else if (x<3000) x+=500;
    // else if (x<5000) x+=1000;
    // else x+=2000;
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
  makeHists( date, lumi, bins_small );     // Monte Carlo  - small bins
  // makeHists( date, lumi, bins_0btag );     // Monte Carlo  - bins_medium
  // makeHists( date, lumi, bins_1btag );     // Monte Carlo  - bins_medium
  // makeHists( date, lumi, bins_2btag );     // Monte Carlo  - bins_medium
  makeHists( date, lumi, bins_constant );  // Monte Carlo  - bins_medium

}


// void makeHists( bool data = false, bool noSubtract = false, vector<int> bins ){
void makeHists( string date, double luminosity, vector<double> bins ){
	// Get input file and setup output file
  TFile * InFile;
  TFile * InFile2;
  TFile * OutFileBigBins;
  TFile * OutFile;

  string infolder = "/Users/jdolen/Nobackup/B2G2016/V4/runs/";

  vector <string> primary_files;
  primary_files.push_back("histsAntiTag_Jetpt500HT1000Syst0_20161202full_b2gtreeV4_JetHT_Run2016all_JSONnov14.root");
  primary_files.push_back("histsAntiTag_Jetpt500HT1000Syst0_20161202full_b2gtreeV4_JetHT_Run2016all_JSONnov14.root");
  // primary_files.push_back("histsAntiTag_Jetpt500HT1000Syst0_20161202fullNoPUreweight_b2gtreeV4_TT_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISpring16MiniAODv2-PUSpring16_reHLT_ext3_all.root");
  // primary_files.push_back("ScaleQCDtest.root");
  
  vector <string> secondary_files;
  secondary_files.push_back("histsAntiTag_Jetpt500HT1000Syst0_20161202fullNoPUreweight_b2gtreeV4_TT_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISpring16MiniAODv2-PUSpring16_reHLT_ext3_all.root");
  secondary_files.push_back("histsAntiTag_Jetpt500HT1000Syst0_20161202fullNoPUreweight_b2gtreeV4_TT_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISpring16MiniAODv2-PUSpring16_reHLT_ext3_all.root");
  // secondary_files.push_back("histsAntiTag_Jetpt500HT1000Syst0_20161202fullNoPUreweight_b2gtreeV4_TT_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISpring16MiniAODv2-PUSpring16_reHLT_ext3_all.root");
  // secondary_files.push_back("histsAntiTag_Jetpt500HT1000Syst0_20161202fullNoPUreweight_b2gtreeV4_TT_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISpring16MiniAODv2-PUSpring16_reHLT_ext3_all.root");

  vector <bool> subtract_secondary;
  subtract_secondary.push_back(true);
  subtract_secondary.push_back(false);
  // subtract_secondary.push_back(false);
  // subtract_secondary.push_back(false);

  vector <string> outfile_savename;
  outfile_savename.push_back("data_subtract_ttbar");
  outfile_savename.push_back("data_nosubtract_ttbar");
  // outfile_savename.push_back("ttMC");
  // outfile_savename.push_back("QCDMC");

  
  int nbins = bins.size();
  stringstream temp1;
  temp1 << nbins;
  string snbins = temp1 .str();

  cout<<"start file loop"<<endl;
  for (unsigned int ii=0; ii<primary_files.size(); ii++){
    cout<<endl;
    string outfile_name ;
    outfile_name = "MistagRate_nbins_"+snbins+"_"+date+"_"+outfile_savename[ii]+".root";

    string primary_name = infolder + primary_files[ii];
    string secondary_name = infolder + secondary_files[ii];;
    cout<<"Opening "<<primary_name<<endl;

    InFile        = new TFile(      primary_name.c_str()      );
    OutFile       = new TFile(      outfile_name.c_str()        , "RECREATE");
    if (subtract_secondary[ii] ) InFile2  = new TFile(secondary_name.c_str()     );

    OutFile->cd();

    // Loop over anti-tag and tag combinations and make mistag rate
    vector <string> antitag_def;
    vector <string> tag_def;

    antitag_def.push_back("AntiTagTau32_ReqTopMassSD");
    antitag_def.push_back("alt_AntiTagTau32_ReqTopMassSD");

    tag_def.push_back("_TagMassSDTau32"   );

    string pre = "h_";
    string save_pre = "h_mistag_";
    string probe = "_Probe";
    vector <string> post;

    post.push_back("_jetP_dRapIn_inclusive");
    post.push_back("_jetP_dRapIn_0btag");
    post.push_back("_jetP_dRapIn_1btag");
    post.push_back("_jetP_dRapIn_2btag");
    post.push_back("_jetP_dRapHi_inclusive");
    post.push_back("_jetP_dRapHi_0btag");
    post.push_back("_jetP_dRapHi_1btag");
    post.push_back("_jetP_dRapHi_2btag");
    post.push_back("_jetP_dRapLo_inclusive");
    post.push_back("_jetP_dRapLo_0btag");
    post.push_back("_jetP_dRapLo_1btag");
    post.push_back("_jetP_dRapLo_2btag");

    for (unsigned int i=0; i<antitag_def.size(); i++ ){
      for (unsigned int j=0; j<tag_def.size(); j++ ){
        for (unsigned int k=0; k<post.size(); k++ ){
          string numer = pre + antitag_def[i] + tag_def[j] + post[k] ;
          string denom = pre + antitag_def[i] + probe + post[k] ;
          string savename  = save_pre + antitag_def[i] + tag_def[j] + post[k] ;
          cout <<"numer   : "<<numer<<endl;
          cout <<"denom   : "<<denom<<endl;


          TH1D * primary_numer = (TH1D*) InFile->Get(numer.c_str());
          TH1D * primary_denom = (TH1D*) InFile->Get(denom.c_str());
          primary_numer  ->Sumw2();
          primary_denom  ->Sumw2();
          
          TH1D *primary_numer_new =(TH1D*) primary_numer->Clone();
          TH1D *primary_denom_new =(TH1D*) primary_denom->Clone();
          // primary_numer_new->Sumw2();
          // primary_denom_new->Sumw2();

          // rebin with variable width bins
          int nbins = bins.size();
          double xbins[nbins];
          for( unsigned int i = 0; i < bins.size(); i++) xbins[i] = bins[i];
          // for( unsigned int i = 0; i < bins.size(); i++) cout<<xbins[i]<<" ";
          // cout<<endl;
          cout<<"nbins "<<nbins<<endl;
          TH1D* primary_numer_rebin = (TH1D*)primary_numer_new->Rebin(nbins-1,"primary_numer_rebin",xbins);
          TH1D* primary_denom_rebin = (TH1D*)primary_denom_new->Rebin(nbins-1,"primary_denom_rebin",xbins);
          // primary_numer_rebin->Sumw2(); 
          // primary_denom_rebin->Sumw2();

          TH1D *secondary_numer_rebin;
          TH1D *secondary_denom_rebin;
          if (subtract_secondary[ii]){

            TH1D * secondary_numer = (TH1D*)InFile2->Get(numer.c_str());
            TH1D * secondary_denom = (TH1D*)InFile2->Get(denom.c_str());
            secondary_numer ->Sumw2();
            secondary_denom ->Sumw2();
            TH1D *secondary_numer_new;
            TH1D *secondary_denom_new;
            secondary_numer_new =(TH1D*) secondary_numer->Clone();
            secondary_denom_new =(TH1D*) secondary_denom->Clone();
            // secondary_numer_new->Sumw2();
            // secondary_denom_new->Sumw2(); 
            secondary_numer_rebin = (TH1D*)secondary_numer_new->Rebin(nbins-1,"secondary_numer_rebin",xbins);
            secondary_denom_rebin = (TH1D*)secondary_denom_new->Rebin(nbins-1,"secondary_denom_rebin",xbins);
            // secondary_numer_rebin ->Sumw2();
            // secondary_denom_rebin ->Sumw2(); 
          
            double nevents_dataset_ttbar  = 92925926;//92925926; //96834559;
            double xsec_ttbar  =  831.76  ;
            double kfactor  =  1.0 ; //0.94;
            double toptagsf =  1.0 ; //0.89;
            double scale_ttbar= toptagsf * toptagsf * kfactor * xsec_ttbar * luminosity / nevents_dataset_ttbar;
            cout<<"scale_ttbar "<<scale_ttbar<<" ( lumi = "<<luminosity<<" , xsec = "<<xsec_ttbar<<" , nevents = "<<nevents_dataset_ttbar <<" )" <<endl;
            secondary_numer_rebin->Scale(scale_ttbar);
            secondary_denom_rebin->Scale(scale_ttbar);

            string secondary_numer_name = "check_"+antitag_def[i] + tag_def[j] + post[k] +"_ttbar";
            string secondary_denom_name = "check_"+antitag_def[i] + probe      + post[k] +"_ttbar";
            secondary_numer_rebin ->SetName(secondary_numer_name.c_str() );
            secondary_denom_rebin ->SetName(secondary_denom_name.c_str() );
            secondary_numer_rebin ->Write();
            secondary_denom_rebin ->Write();


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

          cout<<"outfile string : "<<outfile_savename[ii]<<endl;
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
}
