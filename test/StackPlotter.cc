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

    const double luminosity = 2564.649;//2460;  //166;
    double nevents_ttbar  = 19665194;
    double xsec_ttbar  =  815.96  ;
    double kfactor = 0.8;
    double scale_ttbar= kfactor* xsec_ttbar * luminosity / nevents_ttbar;
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

    string date = "121615";
    const int nSyst = 3;
    string syst[nSyst] = {"_jec_dn", "_jec_nom", "_jec_up"};

    vector <string> post;
    post.push_back("_dRapHi_inclusive");
    post.push_back("_dRapHi_2btag");
    post.push_back("_dRapHi_1btag");
    post.push_back("_dRapHi_0btag");
    post.push_back("_dRapLo_inclusive");
    post.push_back("_dRapLo_2btag");
    post.push_back("_dRapLo_1btag");
    post.push_back("_dRapLo_0btag");



    // Get the ttbar MC, Zprime and data files
    cout<<"Getting the files"<<endl;
    TFile* f_ttbar[nSyst]; TFile* f_data; TFile* f_zPrime[nMass][nSyst]; TH1F* Check;

    for (int iSyst=0; iSyst<nSyst; iSyst++) {
        string fttbar = "outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_121615"+syst[iSyst]+".root";
        f_ttbar[iSyst]  = new TFile(fttbar.c_str(),"READ");
        cout<<"Got "<< fttbar.c_str() <<endl;
    }
    cout<<"checking"<<endl;
    string bkgdEst1 = "h_bkgdEst_tagMassSDTau32"+post[7]; //h_bkgdEst_modMass_tagMassSDTau32
    Check = (TH1F*) f_ttbar[2] ->Get(bkgdEst1.c_str())->Clone();
    cout<<"DEBUG: after reading the file array h_mttMass_tagMassSDTau32 for data jec up = "<< Check->GetSum()<<endl;
    
    string fdata = "outBkgdEst_JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65_121615_jec_nom.root";
    f_data = new TFile(fdata.c_str(),"READ");
    cout<<"Got "<< fdata.c_str() <<endl;


    //for (int iMass=0; iMass<nMass; iMass++) {
    //    f_zPrime[iMass] = new TFile("runs/run_102715/ZprimeToTT_"+name_zPrime[iMass]+"_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_bckGrndEst_102715.root","READ");
    //    cout <<"Got runs/run_102715/ZprimeToTT_"+name_zPrime[iMass]+"_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_bckGrndEst_102715.root"<<endl;
    //}

    //Check = (TH1F*) f_zPrime[5]->Get("h_mttMass_tagMassSDTau32")->Clone();
    //cout<<"DEBUG: after reading the file ="<< Check->GetSum()<<endl;
    TFile* OutFile;
    string outfile_name = "histfile_"+date+"_bkgdEst_tagMassSDTau32"+".root"; ///h_bkgdEst_modMass_tagMassSDTau32    h_bkgdEst_tagMassSDTau32    
    OutFile  = new TFile( outfile_name.c_str(), "RECREATE");
    OutFile->cd();

    for (int iSyst=0; iSyst<3; iSyst++){
        for (unsigned int i=0; i<post.size(); i++ ){
            // Get the h_backgrndEst hist for data and ttbar MC and Scale the ttbar MC backrndEst
            cout <<"Getting h_backgrndEst hist for data and ttbar MC for "+post[i]+"_region"<<endl;
            TH1F* bckGrnd_ttbar; TH1F* bckGrnd_data; TH1F* h_bckGrnd;
            
            string bkgdEst = "h_bkgdEst_tagMassSDTau32"+post[i]; ///h_bkgdEst_modMass_tagMassSDTau32
            cout << "h_bkgdEst: "<< bkgdEst <<endl;
            bckGrnd_ttbar = (TH1F*) f_ttbar[iSyst]->Get(bkgdEst.c_str())->Clone();
            bckGrnd_ttbar -> Scale(scale_ttbar);
            bckGrnd_data  = (TH1F*) f_data ->Get(bkgdEst.c_str())->Clone();
        
            // Subtract ttbar MC backGrndEst from data backgrndEst
            h_bckGrnd = (TH1F*) bckGrnd_data ->Clone();
            h_bckGrnd ->Add( (TH1F*)bckGrnd_ttbar, -1);
            string h_bckGrnd_name = "h_bkgdEst_tagMassSDTau32"+post[i]+syst[iSyst]; //h_bkgdEst_modMass_tagMassSDTau32
            h_bckGrnd -> SetName(h_bckGrnd_name.c_str());

            // Get mttMass ttbar signal hist
            TH1F* h_mttMass_ttbar;
            string mttMass = "h_mttMass_tagMassSDTau32"+post[i];
            cout << "h_mttMass: "<< bkgdEst <<endl;
            h_mttMass_ttbar = (TH1F*) f_ttbar[iSyst]->Get(mttMass.c_str())->Clone();

            // scale mttMass ttbar hist
            h_mttMass_ttbar -> Scale(scale_ttbar);
            string h_mttMass_ttbar_name = "h_mttMass_tagMassSDTau32"+post[i]+syst[iSyst];
            h_mttMass_ttbar -> SetName(h_mttMass_ttbar_name.c_str());

            // Get mttMass data hist
            TH1F* h_mttMass_data;
            h_mttMass_data = (TH1F*) f_data->Get(mttMass.c_str())->Clone();
            string h_mttMass_data_name = "h_mttMass_tagMassSDTau32_data"+post[i]+syst[iSyst];
            h_mttMass_data -> SetName(h_mttMass_data_name.c_str());

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
            gStyle->SetOptStat(0);
        
            THStack* h_stack;
            string stackName = "Stacked ttbar, bckground estimation, data, region"+post[i]+syst[iSyst];
            h_stack = new THStack( "h_stack",stackName.c_str());
            h_mttMass_ttbar->SetFillColor(kRed);
            h_stack-> Add(h_mttMass_ttbar);
            h_bckGrnd->SetFillColor(kYellow);
            h_stack-> Add(h_bckGrnd);
            h_mttMass_data->SetMarkerColor(kBlack);
            h_mttMass_data->SetMarkerStyle(20);
            

            TH1F* h_totalbckGrnd = (TH1F*) h_mttMass_ttbar->Clone(); 
            h_totalbckGrnd->Add(h_bckGrnd);
            string h_totalbckGrnd_name = "h_total_background_tagMassSDTau32"+post[i]+syst[iSyst];
            h_totalbckGrnd -> SetName(h_totalbckGrnd_name.c_str());

            TH1F* h_ratio = (TH1F*) h_mttMass_data->Clone();
            //h_ratio->Sumw2();
            h_ratio->Divide(h_totalbckGrnd);
            h_ratio->SetName("h_ratio");
            //h_ratio->SetTitle(";data/MC");
            h_ratio->GetYaxis()->SetTitle("Data/MC");
            h_ratio->GetXaxis()->SetTitle("Dijet Mass (GeV)");

            //for (int iMass=0; iMass<nMass; iMass++) {
            //    h_mttMass_zPrime[iMass] -> SetLineStyle(2+iMass);
            //    h_mttMass_zPrime[iMass] ->SetMarkerColor(kBlack);
            //}

            TCanvas* c; TPad* p1; TPad* p2; 
            c = new TCanvas("c", "" , 700, 625);
            p1 = new TPad("p1", "",0,0.3,1,1);
            p2 = new TPad("p2", "",0,0.0,1,0.28);
            c ->cd();
            p1->SetBottomMargin(0.05);
            p1->Draw();
            p1->cd();
            double max1 = h_mttMass_data->GetMaximum();
            double max2 = h_stack->GetMaximum();
            if (max2 > max1){
                max1 = max2;
            }
            h_mttMass_data->SetMaximum( max1 * 1.4);
            h_mttMass_data->Draw("ep");
            h_mttMass_data->GetYaxis()->SetTitle("Number of Events");
            h_mttMass_data->GetYaxis()->SetTitleSize(0.04);
            h_mttMass_data->GetYaxis()->SetLabelSize(0.04);
            h_mttMass_data->GetYaxis()->SetTitleOffset(1.15);
            h_stack->Draw("hist same");
            
            h_mttMass_data->Draw("ep same");
            // Plot on the same plot the mttMass for different Z’ samples
            //for (int iMass=0; iMass<nMass; iMass++) {
            //    h_mttMass_zPrime[iMass] -> Draw("hist same");
            //}

            TLegend* leg = new TLegend(0.45,0.55,0.9,0.9);  
            leg->AddEntry(h_bckGrnd,"Estimated Background","f");
            leg->AddEntry(h_mttMass_ttbar,"double tagged ttbar mass","f");
            leg->AddEntry(h_mttMass_data,"data","p");
            //for (int iMass=0; iMass<nMass; iMass++) {
            //    leg->AddEntry(h_mttMass_zPrime[iMass], "Z prime_"+ name_zPrime[iMass], "l");
            //}
            leg->SetFillStyle(0);
            leg->SetBorderSize(0);
            leg->SetTextSize(0.025);
            leg->SetTextFont(42);
            leg->Draw();
            c ->Draw();

            c->cd();
            p2->SetTopMargin(0.05);
            p2->SetBottomMargin(0.4);
            p2->SetGrid();
            p2->Draw();
            p2->cd();
            h_ratio->SetMaximum(2.0);
            h_ratio->SetMinimum(0.0);
            h_ratio->GetXaxis()->SetTitleSize(0.1);
            h_ratio->GetXaxis()->SetLabelSize(0.1);
            h_ratio->GetYaxis()->SetTitleSize(0.1);
            h_ratio->GetYaxis()->SetLabelSize(0.1);
            h_ratio->GetXaxis()->SetTitleOffset(1.3);
            h_ratio->GetYaxis()->SetTitleOffset(0.4);
            h_ratio->GetYaxis()->SetNdivisions(4,4,0,false);
            h_ratio->Draw("e");

            c->Update();

            string outname = "stacked_comparison_softDrop_"+date+post[i]+syst[iSyst]+".png";
            string outname_log = "stacked_comparison_log_softDrop_"+date+post[i]+syst[iSyst]+".png";
            c ->SaveAs(outname.c_str());
            p1 ->SetLogy();
            c ->SaveAs(outname_log.c_str());
            c ->SetLogy(0);

            
            h_mttMass_data->Write();
            h_bckGrnd->Write();
            h_mttMass_ttbar->Write();
            h_totalbckGrnd->Write();
            
            
        }
    }
    OutFile -> Close();
    
}











