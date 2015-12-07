/* -------------------------------------------------------------------------------------------------------------------------
  Stack plots of ttbar MC, backdround estimation and data + Z'
  -------------------------------------------------------------------------------------------------------------------------
*/
//  -------------------------------------------------------------------------------------
//  load options & set plot style
//  -------------------------------------------------------------------------------------

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

#include <iostream>
#include <string>
#include <vector>

using namespace std;


void run(){

    const double luminosity = 1263.890;  //166;
    double nevents_ttbar  = 19665194;
    double xsec_ttbar  =  815.96  ;
    double scale_ttbar= xsec_ttbar * luminosity / nevents_ttbar;
    cout<<"scale_ttbar "<<scale_ttbar<<endl;
    /*
    //                          xs(pb)  / nevents * lumi
    double Zprime_scales[6] =  {20/122204 * luminosity    ,   //ZprimeToTT_M-1000_W-10
                                3.5/108916 * luminosity   ,   //ZprimeToTT_M-1500_W-15
                                0.7/202573 * luminosity   ,   //ZprimeToTT_M-2000_W-20
                                0.3/118319 * luminosity   ,   //ZprimeToTT_M-2500_W-25
                                0.12/117069 * luminosity  ,   //ZprimeToTT_M-3000_W-30
                                0.05/113527 * luminosity     //ZprimeToTT_M-3500_W-35
                               };
    */
    const int nMass = 6;
    TString name_zPrime[nMass] = {"M-1000_W-10", "M-1500_W-15", "M-2000_W-20", "M-2500_W-25", "M-3000_W-30", "M-3500_W-35"};

    string date = "120615";

    vector <string> post;
    post.push_back("_dRapHi_inclusive");
    post.push_back("_dRapHi_2btag");
    //post.push_back("_dRapHi_1btag");
    //post.push_back("_dRapHi_0btag");
    post.push_back("_dRapLo_inclusive");
    post.push_back("_dRapLo_2btag");
    //post.push_back("_dRapLo_1btag");
    //post.push_back("_dRapLo_0btag");

    // Get the ttbar MC, Zprime and data files
    cout<<"Getting the files"<<endl;
    TFile* f_ttbar; TFile* f_data; TFile* f_zPrime[nMass]; //TH1F* Check;
    f_data = new TFile("outBkgdEst_JetHT_Run2015D_PromptReco-v3_and_v4_oct19json_120615.root","READ");
    cout<<"Got outBkgdEst_JetHT_Run2015D_PromptReco-v3_and_v4_oct19json_120615.root"<<endl;
    f_ttbar = new TFile("outBkgdEst_ttjets_b2ganafw_v6_120615.root","READ");
    cout<<"Got outBkgdEst_ttjets_b2ganafw_v6_120615.root"<<endl;
    //for (int iMass=0; iMass<nMass; iMass++) {
    //    f_zPrime[iMass] = new TFile("runs/run_102715/ZprimeToTT_"+name_zPrime[iMass]+"_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_bckGrndEst_102715.root","READ");
    //    cout <<"Got runs/run_102715/ZprimeToTT_"+name_zPrime[iMass]+"_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_bckGrndEst_102715.root"<<endl;
    //}

    //Check = (TH1F*) f_zPrime[5]->Get("h_mttMass_tagMassSDTau32")->Clone();
    //cout<<"DEBUG: after reading the file ="<< Check->GetSum()<<endl;
    for (unsigned int i=0; i<post.size(); i++ ){
        // Get the h_backgrndEst hist for data and ttbar MC and Scale the ttbar MC backrndEst
        cout <<"Getting h_backgrndEst hist for data and ttbar MC for "+post[i]+"_region"<<endl;
        TH1F* bckGrnd_ttbar; TH1F* bckGrnd_data; TH1F* h_bckGrnd;
        
        string bkgdEst = "h_bkgdEst_tagMassSDTau32"+post[i];
        cout << "h_bkgdEst: "<< bkgdEst <<endl;
        bckGrnd_ttbar = (TH1F*) f_ttbar->Get(bkgdEst.c_str())->Clone();
        bckGrnd_ttbar -> Scale(scale_ttbar);
        bckGrnd_data  = (TH1F*) f_data ->Get(bkgdEst.c_str())->Clone();
    
        // Subtract ttbar MC backGrndEst from data backgrndEst
        h_bckGrnd = (TH1F*) bckGrnd_data ->Clone();
        h_bckGrnd ->Add( (TH1F*)bckGrnd_ttbar, -1);

        // Get mttMass ttbar signal hist
        TH1F* h_mttMass_ttbar;
        string mttMass = "h_mttMass_tagMassSDTau32"+post[i];
        cout << "h_mttMass: "<< bkgdEst <<endl;
        h_mttMass_ttbar = (TH1F*) f_ttbar->Get(mttMass.c_str())->Clone();

        // scale mttMass ttbar hist
        h_mttMass_ttbar -> Scale(scale_ttbar);

        // Get mttMass data hist
        TH1F* h_mttMass_data;
        h_mttMass_data = (TH1F*) f_data->Get(mttMass.c_str())->Clone();

        /*
        // Get mttMass for different Z’ samples
        vector<TH1F*> h_mttMass_zPrime;
        for (int iMass=0; iMass<nMass; iMass++) {
            h_mttMass_zPrime.push_back( (TH1F*) f_zPrime[iMass]->Get("AllHad/h_mttMass_tagMassSDTau32")->Clone() );
        }
        for (int iMass=0; iMass<nMass; iMass++) {
            h_mttMass_zPrime[iMass] -> Scale(Zprime_scales[iMass]);
            h_mttMass_zPrime[iMass] -> Rebin(25);
        }
        */
        h_bckGrnd -> Rebin(25);
        h_mttMass_ttbar-> Rebin(25);
        h_mttMass_data -> Rebin(25);

        // Make a stack plot of backgrndEst; mttMass ttbar Signal and mttMass data
        Float_t f_textSize=0.03;
        gStyle->SetPadLeftMargin(0.12);
        gStyle->SetPadRightMargin(0.1);
        gStyle->SetTextSize(f_textSize);
        gStyle->SetLabelSize(f_textSize,"x");
        gStyle->SetTitleSize(f_textSize,"x");
        gStyle->SetLabelSize(f_textSize,"y");
        gStyle->SetTitleSize(f_textSize,"y");
        gStyle->SetOptStat(0);
    
        THStack* h_stack;
        string stackName = "Stacked ttbar, bckground estimation, data, region"+post[i];
        h_stack = new THStack( "h_stack",stackName.c_str());
        h_mttMass_ttbar->SetFillColor(kRed);
        h_stack-> Add(h_mttMass_ttbar);
        h_bckGrnd->SetFillColor(kYellow);
        h_stack-> Add(h_bckGrnd);
        h_mttMass_data->SetMarkerColor(kBlack);
        h_mttMass_data->SetMarkerStyle(20);

        //for (int iMass=0; iMass<nMass; iMass++) {
        //    h_mttMass_zPrime[iMass] -> SetLineStyle(2+iMass);
        //    h_mttMass_zPrime[iMass] ->SetMarkerColor(kBlack);
        //}

        TCanvas* c;
        c = new TCanvas("c", "" , 700, 625);
        c ->cd();
        h_stack->Draw("hist");
        h_mttMass_data->Draw("e same");
        //for (int iMass=0; iMass<nMass; iMass++) {
        //    h_mttMass_zPrime[iMass] -> Draw("hist same");
        //}
        //h_stack->GetXaxis()->SetTitle("p (generated top) [GeV]");
        //h_stack->GetYaxis()->SetTitle("d#sigma/dp_{T} [fb/GeV]");
        //h_stack->GetXaxis()->CenterTitle();
        //h_stack->Draw("hist");

        TLegend* leg = new TLegend(0.45,0.55,0.9,0.9);  
        leg->AddEntry(h_bckGrnd,"Estimated Background","f");
        leg->AddEntry(h_mttMass_ttbar,"double tagged ttbar mass","f");
        leg->AddEntry(h_mttMass_data,"data","p");
        //for (int iMass=0; iMass<nMass; iMass++) {
        //    leg->AddEntry(h_mttMass_zPrime[iMass], "Z prime_"+ name_zPrime[iMass], "l");
        //}
        leg->SetFillStyle(0);
        leg->SetBorderSize(0);
        leg->SetTextSize(0.02);
        leg->SetTextFont(42);
        leg->Draw();
        c ->Draw();
        string outname = "stacked_comparison_softDrop_"+date+post[i]+".png";
        string outname_log = "stacked_comparison_log_softDrop_"+date+post[i]+".png";
        c ->SaveAs(outname.c_str());
        c ->SetLogy();
        c ->SaveAs(outname_log.c_str());
        c ->SetLogy(0);


        // Plot on the same plot the mttMass for different Z’ samples
    }

}











