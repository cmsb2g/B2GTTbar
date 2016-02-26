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
void makeHists(bool, bool, vector<double>);

void run(){

  // Define mistag rate bins
  vector <double> bins_small;
  vector <double> bins_medium;
  vector <double> bins_big;
  vector <double> bins_eta;
  int x;

  cout<<"Define small bins: ";
  x=400;
  while (x<=5000){
    cout<<" "<<x;
    bins_small.push_back(x);
    if ( x<1000) x+=50;
    else if (x<2000) x+=100;
    else if (x<3500) x+=500;
    else x+=1000;
  }
  cout<<endl;

  cout<<"Define medium bins: ";
  x=400;
  while (x<=5000){
    cout<<" "<<x;
    bins_medium.push_back(x);
    if ( x<1000) x+=100;
    else if (x<1200) x+=200;
    else if (x<1500) x+=300;
    else if (x<2000) x+=500;
    else if (x<5000) x+=1000;
    else x+=1000;
  }
  cout<<endl;

  cout<<"Define big bins: ";
  // x=400;
  // while (x<=2000){
  //   cout<<" "<<x;
  //   bins_big.push_back(x);
  //   x+=100;
  // }
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


  cout<<"Define eta bins: ";
  // x=400;
  // while (x<=2000){
  //   cout<<" "<<x;
  //   bins_big.push_back(x);
  //   x+=100;
  // }
  for (double i = -2.4; i<= 2.4; i+=0.2){
      bins_eta.push_back(i);
      cout<<" "<<i;
  }
  cout<<endl;


  // bool data, bool noSubtract, vector of bins
  cout<<" makeHists(false, false, bins_small )"<<endl;   makeHists(true, false, bins_small );  // Monte Carlo  - small bins
  cout<<" makeHists(false, false, bins_medium )"<<endl;  makeHists(true, false, bins_medium );  // Monte Carlo  - bins_medium
  cout<<" makeHists(false, false, bins_eta)"<<endl;      makeHists(true, false, bins_eta );  // Monte Carlo  - bins_medium
  // cout<<" makeHists(false, false, bins_big   )"<<endl;  makeHists(false, false, bins_big   );  // Monte Carlo  - small bins
  // cout<<" makeHists(true , false, bins_medium   )"<<endl;  makeHists(true , false, bins_medium   );   // Data - subtract - medium bins
  // cout<<" makeHists(true ,  true, bins_medium   )"<<endl;  makeHists(true ,  true, bins_medium   );   // Data - no subtract - medium bins

}


// void makeHists( bool data = false, bool noSubtract = false, vector<int> bins ){
void makeHists( bool data, bool noSubtract, vector<double> bins ){
	// Get input file and setup output file
  TFile * InFile;
  TFile * InFileTTbar;
  TFile * OutFileBigBins;
  TFile * OutFile;

  string infile_name ;
  string infile_ttbar_name ;

  // QCD Monte Carlo Input (scaled) and Output files
  if (!data) infile_name = "outAntiTag_QCD_HT700toInf_B2Gv8p4_reader603e_notrig_021816_nom_scaled.root";

  if (data){

    infile_name       = "outAntiTag_JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65_021816.root";
    infile_ttbar_name = "outAntiTag_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e_021816.root";
  } 

  string date = "021816";
  //string syst = "jec_up";
  
  
  int nbins = bins.size();
  stringstream temp1;
  temp1 << nbins;
  string snbins = temp1 .str();
  string subtractOrNot = "";
  if (noSubtract) subtractOrNot = "_noSubstract_";
  if (!noSubtract) subtractOrNot = "_Substract_";
  if (!data) subtractOrNot = "_MC_";

  string outfile_name = "MistagRate_nbins_"+date+"_"+snbins+"_ttbar"+subtractOrNot+infile_name;

  cout<<"Opening "<<infile_name<<endl;
  InFile        = new TFile(      infile_name.c_str()      );
  OutFile       = new TFile(     outfile_name.c_str()        , "RECREATE");
  if (data) InFileTTbar   = new TFile(infile_ttbar_name.c_str()     );

  OutFile->cd();

  // Loop over anti-tag and tag combinations and make mistag rate
  vector <string> antitag_def;
  vector <string> tag_def;

  //antitag_def.push_back("AntiTagMinMass30_ReqTopMassFat");
  //antitag_def.push_back("AntiTagMinMass30_ReqTopMassSD");
  //antitag_def.push_back("AntiTagMinMass50_ReqTopMassFat");
  //antitag_def.push_back("AntiTagMinMass50_ReqTopMassSD");
  //antitag_def.push_back("AntiTagTau32_ReqTopMassFat");
  antitag_def.push_back("AntiTagTau32_ReqTopMassSD");
  antitag_def.push_back("AntiTagMinMass_ReqTopMassSD");
  antitag_def.push_back("NoAntiTag_ReqTopMassSD");
  antitag_def.push_back("AntiTagTau32_NoMassReq");
  antitag_def.push_back("TagOdd");
  antitag_def.push_back("TagEven");

 
  //tag_def.push_back("_TagMassFatMinMass");
  //tag_def.push_back("_TagMassSD"        );
  tag_def.push_back("_TagMassSDTau32"   );
  //tag_def.push_back("_TagMassSDMinMass" );

  //string pre = "AllHad/h_";
  string pre = "h_";
  string save_pre = "h_mistag_";
  string probe = "_Probe";
  vector <string> post;
  post.push_back("_jetPt_dRapIn_inclusive");
  post.push_back("_jetPt_dRapIn_0btag");
  post.push_back("_jetPt_dRapIn_1btag");
  post.push_back("_jetPt_dRapIn_2btag");
  post.push_back("_jetPt_dRapHi_inclusive");
  post.push_back("_jetPt_dRapHi_0btag");
  post.push_back("_jetPt_dRapHi_1btag");
  post.push_back("_jetPt_dRapHi_2btag");
  post.push_back("_jetPt_dRapLo_inclusive");
  post.push_back("_jetPt_dRapLo_0btag");
  post.push_back("_jetPt_dRapLo_1btag");
  post.push_back("_jetPt_dRapLo_2btag");
  
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

  post.push_back("_jetRap_dRapIn_inclusive");
  post.push_back("_jetRap_dRapIn_0btag");
  post.push_back("_jetRap_dRapIn_1btag");
  post.push_back("_jetRap_dRapIn_2btag");
  post.push_back("_jetRap_dRapHi_inclusive");
  post.push_back("_jetRap_dRapHi_0btag");
  post.push_back("_jetRap_dRapHi_1btag");
  post.push_back("_jetRap_dRapHi_2btag");
  post.push_back("_jetRap_dRapLo_inclusive");
  post.push_back("_jetRap_dRapLo_0btag");
  post.push_back("_jetRap_dRapLo_1btag");
  post.push_back("_jetRap_dRapLo_2btag");




  // post.push_back("_2D_dRapAll_inclusive");
  // post.push_back("_2D_dRapAll_0btag");
  // post.push_back("_2D_dRapAll_1btag");
  // post.push_back("_2D_dRapAll_2btag");
  // post.push_back("_2D_dRapHi_inclusive");
  // post.push_back("_2D_dRapHi_0btag");
  // post.push_back("_2D_dRapHi_1btag");
  // post.push_back("_2D_dRapHi_2btag");
  // post.push_back("_2D_dRapLo_inclusive");
  // post.push_back("_2D_dRapLo_0btag");
  // post.push_back("_2D_dRapLo_1btag");
  // post.push_back("_2D_dRapLo_2btag");

  // post.push_back("_jetPt_dRapHi_inclusive");
  // post.push_back("_jetPt_dRapHi_2btag");
  // post.push_back("_jetPt_dRapHi_1btag");
  // post.push_back("_jetPt_dRapHi_0btag");
  // post.push_back("_jetPt_dRapLo_inclusive");
  // post.push_back("_jetPt_dRapLo_2btag");
  // post.push_back("_jetPt_dRapLo_1btag");
  // post.push_back("_jetPt_dRapLo_0btag");
  
  
  
  for (unsigned int i=0; i<antitag_def.size(); i++ ){
    for (unsigned int j=0; j<tag_def.size(); j++ ){
      for (unsigned int k=0; k<post.size(); k++ ){
        string numer = pre + antitag_def[i] + tag_def[j] + post[k] ;
        cout <<"numer:"<<numer<<endl;
        string denom = pre + antitag_def[i] + probe + post[k] ;
        cout <<"denom:"<<denom<<endl;
        string savename = save_pre + antitag_def[i] + tag_def[j] + post[k] ;
        string savename2 = save_pre + antitag_def[i] + tag_def[j] + post[k] ;
        string savename3 = "teff_" + antitag_def[i] + tag_def[j] + post[k] ;

        // cout<<numer<<"      "<<denom<<"     "<<
        cout<<savename<<endl;

        TH1D * bkgd_numer = (TH1D*)InFile->Get(numer.c_str());
        TH1D * bkgd_denom = (TH1D*)InFile->Get(denom.c_str());
        bkgd_numer  ->Sumw2();
        bkgd_denom  ->Sumw2();
        
        TH1D *bkgd_numer_new =(TH1D*) bkgd_numer->Clone();
        TH1D *bkgd_denom_new =(TH1D*) bkgd_denom->Clone();
        bkgd_numer_new->Sumw2();
        bkgd_denom_new->Sumw2();

        // rebin with variable width bins
        int nbins = bins.size();
        double xbins[nbins];
        for( unsigned int i = 0; i < bins.size(); i++) xbins[i] = bins[i];
        for( unsigned int i = 0; i < bins.size(); i++) cout<<xbins[i]<<" ";
        cout<<endl;
        cout<<"nbins "<<nbins<<endl;
        TH1D* bkgd_numer_rebin = (TH1D*)bkgd_numer_new->Rebin(nbins-1,"bkgd_numer_rebin",xbins);
        TH1D* bkgd_denom_rebin = (TH1D*)bkgd_denom_new->Rebin(nbins-1,"bkgd_denom_rebin",xbins);
        bkgd_numer_rebin->Sumw2(); 
        bkgd_denom_rebin->Sumw2();

        TH1D *ttbar_numer_rebin;
        TH1D *ttbar_denom_rebin;
        if (data){

          TH1D * ttbar_numer = (TH1D*)InFileTTbar->Get(numer.c_str());
          TH1D * ttbar_denom = (TH1D*)InFileTTbar->Get(denom.c_str());
          ttbar_numer ->Sumw2();
          ttbar_denom ->Sumw2();
          TH1D *ttbar_numer_new;
          TH1D *ttbar_denom_new;
          ttbar_numer_new =(TH1D*) ttbar_numer->Clone();
          ttbar_denom_new =(TH1D*) ttbar_denom->Clone();
          ttbar_numer_new->Sumw2();
          ttbar_denom_new->Sumw2(); 
          ttbar_numer_rebin = (TH1D*)ttbar_numer_new->Rebin(nbins-1,"ttbar_numer_rebin",xbins);
          ttbar_denom_rebin = (TH1D*)ttbar_denom_new->Rebin(nbins-1,"ttbar_denom_rebin",xbins);
          ttbar_numer_rebin ->Sumw2();
          ttbar_denom_rebin ->Sumw2(); 
        }

        // subtract ttbar contribution
        if (data && !noSubtract){

      
          double luminosity = 2530;   //1263.890;  //166; pb-1
          double nevents_dataset_ttbar  = 96834559;
          double xsec_ttbar  =  831.76  ;
          double kfactor = 0.93;
          double toptagsf = 0.82;
          double scale_ttbar= toptagsf * toptagsf * kfactor * xsec_ttbar * luminosity / nevents_dataset_ttbar;
          cout<<"scale_ttbar "<<scale_ttbar<<endl;
          ttbar_numer_rebin->Scale(scale_ttbar);
          ttbar_denom_rebin->Scale(scale_ttbar);

          string ttbar_numer_name = "check_"+antitag_def[i] + tag_def[j] + post[k] +"_ttbar";
          string ttbar_denom_name = "check_"+antitag_def[i] + probe      + post[k] +"_ttbar";
          ttbar_numer_rebin ->SetName(ttbar_numer_name.c_str() );
          ttbar_denom_rebin ->SetName(ttbar_denom_name.c_str() );
          ttbar_numer_rebin ->Write();
          ttbar_denom_rebin ->Write();


          string data_nosubtract_numer_name =  "check_"+antitag_def[i] + tag_def[j] + post[k] +"_data_nosubtract";
          string data_nosubtract_denom_name =  "check_"+antitag_def[i] + probe      + post[k] +"_data_nosubtract";
          bkgd_numer_rebin ->SetName(data_nosubtract_numer_name.c_str() );
          bkgd_denom_rebin ->SetName(data_nosubtract_denom_name.c_str() );
          bkgd_numer_rebin ->Write();
          bkgd_denom_rebin ->Write();

          cout<<"pre subtract numer "<<bkgd_numer_rebin->Integral()<<endl;
          cout<<"pre subtract denom "<<bkgd_denom_rebin->Integral()<<endl;
          bkgd_numer_rebin->Add(ttbar_numer_rebin,-1);
          bkgd_denom_rebin->Add(ttbar_denom_rebin,-1);
          cout<<"post subtract numer "<<bkgd_numer_rebin->Integral()<<endl;
          cout<<"post subtract denom "<<bkgd_denom_rebin->Integral()<<endl;

          string data_subtract_numer_name =  "check_"+antitag_def[i] + tag_def[j] + post[k] +"_data_subtract";
          string data_subtract_denom_name =  "check_"+antitag_def[i] + probe      + post[k] +"_data_subtract";
          bkgd_numer_rebin ->SetName(data_subtract_numer_name.c_str() );
          bkgd_denom_rebin ->SetName(data_subtract_denom_name.c_str() );
          bkgd_numer_rebin ->Write();
          bkgd_denom_rebin ->Write();
        }
        cout<<"debug1"<<endl;

        // divide histograms

        // TEfficiency * eff_default = new TEfficiency(*bkgd_numer_rebin,*bkgd_denom_rebin);
        // TEfficiency * eff_normal  = new TEfficiency(*eff_default);
        // TEfficiency * eff_wilson  = new TEfficiency(*eff_default);
        // TEfficiency * eff_jeffrey = new TEfficiency(*eff_default);
        // eff_normal ->SetStatisticOption(TEfficiency::kFNormal);
        // eff_wilson ->SetStatisticOption(TEfficiency::kFWilson);
        // eff_jeffrey->SetStatisticOption(TEfficiency::kBJeffrey);


        // string savename_eff_default = savename3 + "_default" ;     
        // string savename_eff_normal  = savename3 + "_normal"  ;    
        // string savename_eff_wilson  = savename3 + "_wilson"  ;    
        // string savename_eff_jeffrey = savename3 + "_jeffrey" ;     
        // eff_default ->SetName(savename_eff_default.c_str());      
        // eff_normal  ->SetName(savename_eff_normal .c_str());      
        // eff_wilson  ->SetName(savename_eff_wilson .c_str());
        // eff_jeffrey ->SetName(savename_eff_jeffrey.c_str());
        // eff_default ->Write();
        // eff_normal  ->Write();
        // eff_wilson  ->Write();
        // eff_jeffrey ->Write();

        bkgd_numer_rebin->Divide(bkgd_numer_rebin,bkgd_denom_rebin,1,1,"B");
        bkgd_numer_rebin->SetTitle(";Jet PT (GeV/c);Top Mistag Rate");
        bkgd_numer_rebin->SetName(savename.c_str());
        bkgd_numer_rebin->Write();

        // TCanvas* c;
        // c = new TCanvas("c", "" , 700, 625);
        // c->cd();
        // bkgd_numer_rebin->Draw();
        // bkgd_numer_rebin->GetXaxis()->SetTitleSize(0.03);
        // bkgd_numer_rebin->GetXaxis()->SetLabelSize(0.025);
        // bkgd_numer_rebin->GetYaxis()->SetTitleSize(0.03);
        // bkgd_numer_rebin->GetYaxis()->SetLabelSize(0.025);
        // bkgd_numer_rebin->GetXaxis()->SetTitleOffset(1.3);
        // bkgd_numer_rebin->GetYaxis()->SetTitleOffset(1.5);
        // bkgd_numer_rebin->Draw("SAME");
        // string savename_mistag = savename +".png";
        // c->SaveAs(savename_mistag.c_str());

      }
    }
  }
  OutFile->cd();
  // OutFile->Write();
  OutFile->Close();
}




