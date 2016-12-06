#include "TROOT.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TGaxis.h"
#include "TPaveText.h"
#include "TEfficiency.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TMath.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <cmath>
// #include "CMS_lumi.C"

void plotMistag_Compare_DataQCD(string, string, string, string, string);
void plotMistag_Compare_TTsubtract(string);
void plotMistag_Compare_BtagRapidityBins(string, string, string, string);
void plotMistag_Compare_RunPeriod(string);

void plot2(TH1D*,TH1D*, string, string, string, string, string);
void plot4(TH1D*,TH1D*,TH1D*,TH1D*, string, string, string, string);

void run(){

  string savefolder = "plots_mistag_20161003/";


  plotMistag_Compare_DataQCD("14", "20161203", "data_subtract_ttbar", "QCDMC", savefolder);

  vector<string> poststrings;
  poststrings.push_back("ttMC"                   );
  poststrings.push_back("data_subtract_ttbar"    );
  poststrings.push_back("data_nosubtract_ttbar"  );
  poststrings.push_back("QCDMC"                  );

  // for (unsigned int i=0; i<poststrings.size(); i++ ){
  //   plotMistag_Compare_BtagRapidityBins("9", "20161203",  poststrings[i],  savefolder);
  //   plotMistag_Compare_BtagRapidityBins("14", "20161203",  poststrings[i],  savefolder);
  //   plotMistag_Compare_BtagRapidityBins("29", "20161203",  poststrings[i],  savefolder);
  //   plotMistag_Compare_BtagRapidityBins("30", "20161203",  poststrings[i],  savefolder);
  // }
  // plotMistag_Compare_RunPeriod("14", savefolder);
}

void plotMistag_Compare_DataQCD(string nbins, string date, string poststring1, string poststring2, string savefolder)
{

 
  // string f1   =  "MistagRate_nbins_20161203_"+nbins+"_ttbar_Subtract_histsAntiTag_Jetpt500HT1000Syst0_20161202full_b2gtreeV4_JetHT_Run2016all_JSONnov14.root";
  string f1   =  "MistagRate_nbins_"+nbins+"_"+date+"_"+poststring1+".root";
  string f2   =  "MistagRate_nbins_"+nbins+"_"+date+"_"+poststring2+".root";
  TFile * F1                 = new TFile( f1.c_str() );
  TFile * F2                 = new TFile( f2.c_str() );

  TH1D * h1_dRapIn_inclu = (TH1D*)F1   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_inclusive");
  TH1D * h1_dRapIn_0btag = (TH1D*)F1   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_0btag");
  TH1D * h1_dRapIn_1btag = (TH1D*)F1   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_1btag");
  TH1D * h1_dRapIn_2btag = (TH1D*)F1   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_2btag");

  TH1D * h1_dRapLo_inclu = (TH1D*)F1   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_inclusive");
  TH1D * h1_dRapLo_0btag = (TH1D*)F1   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_0btag");
  TH1D * h1_dRapLo_1btag = (TH1D*)F1   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_1btag");
  TH1D * h1_dRapLo_2btag = (TH1D*)F1   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_2btag");

  TH1D * h1_dRapHi_inclu = (TH1D*)F1   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_inclusive");
  TH1D * h1_dRapHi_0btag = (TH1D*)F1   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_0btag");
  TH1D * h1_dRapHi_1btag = (TH1D*)F1   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_1btag");
  TH1D * h1_dRapHi_2btag = (TH1D*)F1   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_2btag");

  TH1D * h2_dRapIn_inclu = (TH1D*)F2   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_inclusive");
  TH1D * h2_dRapIn_0btag = (TH1D*)F2   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_0btag");
  TH1D * h2_dRapIn_1btag = (TH1D*)F2   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_1btag");
  TH1D * h2_dRapIn_2btag = (TH1D*)F2   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_2btag");

  TH1D * h2_dRapLo_inclu = (TH1D*)F2   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_inclusive");
  TH1D * h2_dRapLo_0btag = (TH1D*)F2   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_0btag");
  TH1D * h2_dRapLo_1btag = (TH1D*)F2   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_1btag");
  TH1D * h2_dRapLo_2btag = (TH1D*)F2   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_2btag");

  TH1D * h2_dRapHi_inclu = (TH1D*)F2   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_inclusive");
  TH1D * h2_dRapHi_0btag = (TH1D*)F2   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_0btag");
  TH1D * h2_dRapHi_1btag = (TH1D*)F2   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_1btag");
  TH1D * h2_dRapHi_2btag = (TH1D*)F2   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_2btag");


  plot2(h1_dRapIn_inclu, h2_dRapIn_inclu,  "_DataQCD", "_dRapIn_inclu",  savefolder, nbins, poststring1 );
  plot2(h1_dRapIn_0btag, h2_dRapIn_0btag,  "_DataQCD", "_dRapIn_0btag",  savefolder, nbins, poststring1 );
  plot2(h1_dRapIn_1btag, h2_dRapIn_1btag,  "_DataQCD", "_dRapIn_1btag",  savefolder, nbins, poststring1 );
  plot2(h1_dRapIn_2btag, h2_dRapIn_2btag,  "_DataQCD", "_dRapIn_2btag",  savefolder, nbins, poststring1 );

}

void plotMistag_Compare_RunPeriod(string nbins, string savefolder){

  gStyle->SetOptStat(0);
  gROOT->UseCurrentStyle();
  gROOT->ForceStyle();

  gROOT->Reset();
  gROOT->ForceStyle(); 
 
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


  string fB = "/Users/jdolen/Code/GitHub/B2GTTbar/test/MistagFiles/MistagRate_nbins_20161203_"+nbins+"_ttbar_histsAntiTag_Jetpt500HT1000Syst0_20161126_b2gtreeV4_JetHT_Run2016B-23Sep2016-v3_JSONnov14_All_partial.root";
  string fC = "/Users/jdolen/Code/GitHub/B2GTTbar/test/MistagFiles/MistagRate_nbins_20161203_"+nbins+"_ttbar_histsAntiTag_Jetpt500HT1000Syst0_20161126_b2gtreeV4_JetHT_Run2016D-23Sep2016-v1_JSONnov14_All.root";
  string fD = "/Users/jdolen/Code/GitHub/B2GTTbar/test/MistagFiles/MistagRate_nbins_20161203_"+nbins+"_ttbar_histsAntiTag_Jetpt500HT1000Syst0_20161126_b2gtreeV4_JetHT_Run2016G-23Sep2016-v1_JSONnov14_All.root";
  string fE = "/Users/jdolen/Code/GitHub/B2GTTbar/test/MistagFiles/MistagRate_nbins_20161203_"+nbins+"_ttbar_histsAntiTag_Jetpt500HT1000Syst0_20161126_b2gtreeV4_JetHT_Run2016H-PromptReco-v2_All.root";
  string fF = "/Users/jdolen/Code/GitHub/B2GTTbar/test/MistagFiles/MistagRate_nbins_20161203_"+nbins+"_ttbar_histsAntiTag_Jetpt500HT1000Syst0_20161126_b2gtreeV4_JetHT_Run2016H-PromptReco-v2_All.root";
  string fG = "/Users/jdolen/Code/GitHub/B2GTTbar/test/MistagFiles/MistagRate_nbins_20161203_"+nbins+"_ttbar_histsAntiTag_Jetpt500HT1000Syst0_20161126_b2gtreeV4_JetHT_Run2016H-PromptReco-v2_All.root";
  string fH = "/Users/jdolen/Code/GitHub/B2GTTbar/test/MistagFiles/MistagRate_nbins_20161203_"+nbins+"_ttbar_histsAntiTag_Jetpt500HT1000Syst0_20161126_b2gtreeV4_JetHT_Run2016H-PromptReco-v2_All.root";

  TFile * F1                 = new TFile( fB.c_str() );
  TFile * F2                 = new TFile( fC.c_str() );
  TFile * F3                 = new TFile( fD.c_str() );
  TFile * F4                 = new TFile( fE.c_str() );
  // TF


  TPaveText *textbox1 = new TPaveText(0.54,0.87,0.89,0.93,"NDC");
  textbox1->SetFillColor(0);
  textbox1->SetLineColor(0);
  TText *line1 = textbox1->AddText("27.2 fb^{-1} (13 TeV)");
  line1->SetTextColor(1);
  line1->SetTextSize(23);
  line1->SetTextFont(42);
  line1->SetTextAlign(33); //first number = horizontal alignment (1 left, 2 center, 3 right). second number =vertical alignment (1 top, 2 center, 3 bottom)
  
  // TPaveText *textbox3 = new TPaveText(0.37,0.75,0.35,0.93,"NDC"); //0.19, .87, 0.35, 0.93
  // textbox3->SetFillColor(0);
  // textbox3->SetLineColor(0);
  // TText *line2 = textbox3->AddText("#bf{#it{CMS Preliminary}}");
  // line2->SetTextColor(1);
  // line2->SetTextSize(23);
  // line2->SetTextFont(43);
  // line2->SetTextAlign(33); 
                                                 // h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_2btag
  TH1D * h0 = (TH1D*)F1   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_inclusive");
  TH1D * h1 = (TH1D*)F2   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_inclusive");
  TH1D * h2 = (TH1D*)F3   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_inclusive");
  TH1D * h3 = (TH1D*)F4   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_inclusive");


  string title = ";Jet Momentum [GeV]; Mistag Rate";
  h0->SetTitle(title.c_str());
  h1->SetTitle(title.c_str());
  h0->GetXaxis()->SetNoExponent();
  h1->GetXaxis()->SetNoExponent();
  h0->GetXaxis()->SetMoreLogLabels();
  h1->GetXaxis()->SetMoreLogLabels();


        double d0 = h0 -> GetMaximum();
        double d3 = 1.5* h2 -> GetMaximum();
        cout<<"d0 "<<d0<<endl;
        cout<<"d3 "<<d3<<endl;
        if (d3>d0) h1->GetYaxis()->SetRangeUser(0,d3+d3*0.5);
        else h1->GetYaxis()->SetRangeUser(0,d0+d0*0.5);

        // h2->SetMarkerStyle(20);
        // h2->SetMarkerColor(1);
        // h2->SetLineColor(1);
        // h2->Draw();


        h1->SetMarkerStyle(20);
        h1->SetMarkerColor(2);
        h1->SetMarkerSize(1.5);
        h1->SetLineColor(2);
        h1->SetLineWidth(2);

        h1->GetYaxis()->SetTitleSize(0.065);
        h1->GetYaxis()->SetTitleOffset(0.9); // 0.7);
        h1->GetYaxis()->SetLabelSize(0.06);

        h1->GetXaxis()->SetNdivisions(506);
        h1->GetXaxis()->SetLabelFont(42);
        h1->GetXaxis()->SetLabelSize(0.05);//0.0425);
        h1->GetXaxis()->SetTitleSize(0.056);//0.0475);0.0475);
        h1->GetXaxis()->SetTickLength(0.045);
        h1->GetXaxis()->SetTitleOffset(1.15);
        h1->GetXaxis()->SetTitleFont(42);
        // h1->GetXaxis()->SetNdivisions(999, kTRUE);
        // h1->GetXaxis()->SetMoreLogLabels(kTRUE);
        // h1->GetXaxis()->SetNoExponent();


        h1->GetYaxis()->SetTitle("t-tag mistag rate");
        h1->GetYaxis()->SetNdivisions(506);
        h1->GetYaxis()->SetLabelFont(42);
        h1->GetYaxis()->SetLabelSize(0.05);//  //0.04375);//0.06375);
        h1->GetYaxis()->SetTitleSize(0.06125);//0.07125);
        h1->GetYaxis()->SetTitleOffset(1.17);//0.9);
        h1->GetYaxis()->SetTitleFont(42);

        h1->GetZaxis()->SetLabelFont(42);
        h1->GetZaxis()->SetLabelSize(0.0425);
        h1->GetZaxis()->SetTitleSize(0.0475);
        h1->GetZaxis()->SetTitleFont(42);


        // if (nbins=="6") h1->GetYaxis()->SetRangeUser(0,0.4);
        h1->Draw("");



        h0->SetMarkerStyle(20);
        h0->SetMarkerSize(1.5);
        h0->SetMarkerColor(1);
        h0->SetLineColor(1);
        h0->SetLineStyle(1);
        h0->SetLineWidth(2);

        h2->SetMarkerStyle(20);
        h2->SetMarkerSize(1.5);
        h2->SetMarkerColor(3);
        h2->SetLineColor(3);
        h2->SetLineStyle(1);
        h2->SetLineWidth(2);

        h3->SetMarkerStyle(20);
        h3->SetMarkerSize(1.5);
        h3->SetMarkerColor(4);
        h3->SetLineColor(4);
        h3->SetLineStyle(1);
        h3->SetLineWidth(2);
        // h2->Draw("same");



        h0->Draw("same");
        h2->Draw("same");
        h3->Draw("same");



        TLegend * leg;
        // leg = new TLegend( 0.45, 0.67,0.84, 0.83); //0.51, 0.66,0.84, 0.83
        leg = new TLegend( 0.64, 0.67,0.98, 0.86); //0.51, 0.66,0.84, 0.83
        leg->SetBorderSize(0);
        leg->SetFillColor(0);
        leg->SetFillStyle(4000);
        leg->SetTextSize(0.042);  //0.03
       // leg->AddEntry( h2   , "Data (no subtraction)" , "LP" );
        leg->AddEntry( h0   , "Run2016B" , "LP" );
        leg->AddEntry( h1   , "Run2016D"  , "LP" );  //(Pythia 8)  " , "LP" );
        leg->AddEntry( h2   , "Run2016G"  , "LP" );  //(Pythia 8)  " , "LP" );
        leg->AddEntry( h3   , "Run2016H"  , "LP" );  //(Pythia 8)  " , "LP" );
        // leg->AddEntry( (TObject*)0 , name_post_def[k].c_str(), "");
        leg->Draw("same");

  TLatex *   tex = new TLatex(0.18,0.83,"#font[62]{CMS} #font[52]{Preliminary}");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.0625);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(0.96,0.936,"27.2 fb^{-1} (13 TeV)");
  tex->SetNDC();
  tex->SetTextAlign(31);
  tex->SetTextFont(42);
  // tex->SetTextSize(0.0625);
  tex->SetTextSize(0.0575);
  tex->SetLineWidth(2);
  tex->Draw();
  // tex = new TLatex(0.56,0.87, name_post_def[k].c_str());
  // tex->SetNDC();
  // tex->SetTextAlign(13);
  // tex->SetTextFont(42);
  // tex->SetTextSize(0.045);
  // tex->SetLineWidth(2);
  // tex->Draw();

        // TPaveText *textbox2 = new TPaveText(0.19,0.72,0.5,0.85,"NDC");
        // textbox2->SetFillColor(0);
        // textbox2->SetLineColor(0); 
        // TText *line1 = textbox2->AddText( name_antitag_def[i].c_str() );
        // TText *line2 = textbox2->AddText( name_tag_def_fix[j].c_str() );
        // TText *line3 = textbox2->AddText( name_post_def[k].c_str() );
        // line1->SetTextColor(1);
        // line1->SetTextSize(22);
        // line1->SetTextFont(43);
        // line1->SetTextAlign(13); //first number = horizontal alignment (1 left, 2 center, 3 right). second number =vertical alignment (1 top, 2 center, 3 bottom)
        // line2->SetTextColor(1);
        // line2->SetTextSize(22);
        // line2->SetTextFont(43);
        // line2->SetTextAlign(13); //first number = horizontal alignment (1 left, 2 center, 3 right). second number =vertical alignment (1 top, 2 center, 3 bottom)
        // line3->SetTextColor(1);
        // line3->SetTextSize(22);
        // line3->SetTextFont(43);
        // line3->SetTextAlign(13); //first number = horizontal alignment (1 left, 2 center, 3 right). second number =vertical alignment (1 top, 2 center, 3 bottom)
    


        // textbox1->Draw("same");
        // textbox2->Draw("same");
        // textbox3->Draw("same");
        gPad->RedrawAxis();

        // TLatex l;
        // float cmsTextSize = 0.07;
        // l.SetTextSize(cmsTextSize); 
        // l.SetTextFont(61); 
        // l.SetTextAngle(0);
        // l.SetNDC();
        // l.SetTextColor(1);
        // l.DrawLatex(2,1.25,"#it{#bf{CMS Preliminary}}");

        // TPaveText *textbox2 = new TPaveText(0.19,0.72,0.5,0.85,"NDC");
        // textbox2->SetFillColor(0);
        // textbox2->SetLineColor(0); 
        // TText *line4 = textbox2->AddText( "CMS Preliminary" );
        // float cmsTextSize = 0.07;
        // line4->SetTextSize(cmsTextSize); 
        // line4->SetTextFont(61); 
        // line4->SetTextAngle(0);
        // line4->SetNDC();
        // line4->SetTextColor(1);
        // line4->DrawLatex(2,1.25,"CMS Preliminary");   
        // textbox1->Draw("same");     
        




        // CMS_lumi(c1237, 4, 10);  
        // cout<<savename<<endl;
        // string savename2 = "runs/run20161010/plots_mistag3/"+savename+"_tmistag.pdf";
        string savename2 = "compare_RunPeriod_tmistag.pdf";
        cout<<savename2<<endl;
        // c1237->SetLogx();
        // c1237->SaveAs(savename2.c_str());
        c1237->SetLogx();
        c1237->SaveAs(savename2.c_str());
      
}

void plotMistag_Compare_BtagRapidityBins(string nbins, string date, string poststring, string savefolder){



 
  // string f1   =  "MistagRate_nbins_20161203_"+nbins+"_ttbar_Subtract_histsAntiTag_Jetpt500HT1000Syst0_20161202full_b2gtreeV4_JetHT_Run2016all_JSONnov14.root";
  string f1   =  "MistagRate_nbins_"+nbins+"_"+date+"_"+poststring+".root";
  TFile * F1                 = new TFile( f1.c_str() );

  TH1D * h_dRapIn_inclu = (TH1D*)F1   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_inclusive");
  TH1D * h_dRapIn_0btag = (TH1D*)F1   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_0btag");
  TH1D * h_dRapIn_1btag = (TH1D*)F1   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_1btag");
  TH1D * h_dRapIn_2btag = (TH1D*)F1   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_2btag");

  TH1D * h_dRapLo_inclu = (TH1D*)F1   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_inclusive");
  TH1D * h_dRapLo_0btag = (TH1D*)F1   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_0btag");
  TH1D * h_dRapLo_1btag = (TH1D*)F1   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_1btag");
  TH1D * h_dRapLo_2btag = (TH1D*)F1   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_2btag");

  TH1D * h_dRapHi_inclu = (TH1D*)F1   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_inclusive");
  TH1D * h_dRapHi_0btag = (TH1D*)F1   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_0btag");
  TH1D * h_dRapHi_1btag = (TH1D*)F1   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_1btag");
  TH1D * h_dRapHi_2btag = (TH1D*)F1   ->Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_2btag");

  plot4(h_dRapIn_inclu, 
        h_dRapIn_0btag, 
        h_dRapIn_1btag, 
        h_dRapIn_2btag, 
        "_dRapIn_btagbins",
        savefolder, 
        nbins,
        poststring
        );

  plot4(h_dRapLo_inclu, 
        h_dRapLo_0btag, 
        h_dRapLo_1btag, 
        h_dRapLo_2btag, 
        "_dRapLo_btagbins",
        savefolder, 
        nbins,
        poststring
        );

    plot4(h_dRapHi_inclu, 
          h_dRapHi_0btag, 
          h_dRapHi_1btag, 
          h_dRapHi_2btag, 
          "_dRapHi_btagbins",
          savefolder, 
          nbins,
          poststring
          );

  plot2(h_dRapHi_inclu, 
        h_dRapLo_inclu, 
        "_btagInclusive_dRapbins", 
        "",
        savefolder, 
        nbins,  
        poststring );


  // g1->GetYaxis()->SetTitleSize(0.065);
  // g1->GetYaxis()->SetTitleOffset(0.9); 
  // g1->GetYaxis()->SetLabelSize(0.06);

  // g1->GetXaxis()->SetNdivisions(506);
  // g1->GetXaxis()->SetLabelFont(42);
  // g1->GetXaxis()->SetLabelSize(0.05);
  // g1->GetXaxis()->SetTitleSize(0.056);
  // g1->GetXaxis()->SetTickLength(0.045);
  // g1->GetXaxis()->SetTitleOffset(1.15);
  // g1->GetXaxis()->SetTitleFont(42);

  // g1->GetYaxis()->SetTitle("t-tag mistag rate");
  // g1->GetYaxis()->SetNdivisions(506);
  // g1->GetYaxis()->SetLabelFont(42);
  // g1->GetYaxis()->SetLabelSize(0.05);
  // g1->GetYaxis()->SetTitleSize(0.06125);
  // g1->GetYaxis()->SetTitleOffset(1.17);
  // g1->GetYaxis()->SetTitleFont(42);

  // g1->GetZaxis()->SetLabelFont(42);
  // g1->GetZaxis()->SetLabelSize(0.0425);
  // g1->GetZaxis()->SetTitleSize(0.0475);
  // g1->GetZaxis()->SetTitleFont(42);

  // g1->Draw("");

  // h0->SetMarkerStyle(20);
  // h0->SetMarkerSize(1.5);
  // h0->SetMarkerColor(1);
  // h0->SetLineColor(1);
  // h0->SetLineStyle(1);
  // h0->SetLineWidth(2);

  // g1->SetMarkerStyle(20);
  // g1->SetMarkerSize(1.5);
  // g1->SetMarkerColor(kOrange);
  // g1->SetLineColor(kOrange);
  // g1->SetLineStyle(1);
  // g1->SetLineWidth(2);

  // g2->SetMarkerStyle(20);
  // g2->SetMarkerSize(1.5);
  // g2->SetMarkerColor(kBlue-2);
  // g2->SetLineColor(kBlue-2);
  // g2->SetLineStyle(1);
  // g2->SetLineWidth(2);

  // g1->GetYaxis()->SetRangeUser(0,h0->GetMaximum()*1.5);;

  // g1->Draw();
  // g2->Draw("same");

  // TLegend * leg2;
  // leg2 = new TLegend( 0.64, 0.67,0.98, 0.86); //0.51, 0.66,0.84, 0.83
  // leg2->SetBorderSize(0);
  // leg2->SetFillColor(0);
  // leg2->SetFillStyle(4000);
  // leg2->SetTextSize(0.042);  //0.03

  // leg2->AddEntry( g1   , "|y|<1"  , "LP" );  //(Pythia 8)  " , "LP" );
  // leg2->AddEntry( g2   , "|y|>1"  , "LP" );  //(Pythia 8)  " , "LP" );
  // leg2->Draw("same");

  // TLatex *   tex2 = new TLatex(0.18,0.83,"#font[62]{CMS} #font[52]{Preliminary}");
  // tex2->SetNDC();
  // tex2->SetTextFont(42);
  // tex2->SetTextSize(0.0625);
  // tex2->SetLineWidth(2);
  // tex2->Draw();
  // tex2 = new TLatex(0.96,0.936,"27.2 fb^{-1} (13 TeV)");
  // tex2->SetNDC();
  // tex2->SetTextAlign(31);
  // tex2->SetTextFont(42);
  // tex2->SetTextSize(0.0575);
  // tex2->SetLineWidth(2);
  // tex2->Draw();

  // gPad->RedrawAxis();

  // string savename3 = savefolder+"compare_tmistag_ybins_nbins"+nbins+".pdf";
  // cout<<savename3<<endl;

  // c1237->SetLogx();
  // c1237->SaveAs(savename3.c_str());


}

void plot4(TH1D * h0, TH1D * h1, TH1D * h2, TH1D * h3, string savestring, string savefolder, string nbins,  string poststring ){

  gStyle->SetOptStat(0);
  gROOT->UseCurrentStyle();
  gROOT->ForceStyle();

  gROOT->Reset();
  gROOT->ForceStyle(); 
  
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

  string title = ";Jet Momentum [GeV]; Mistag Rate";
  h0->SetTitle(title.c_str());
  h1->SetTitle(title.c_str());
  h2->SetTitle(title.c_str());
  h3->SetTitle(title.c_str());
  
  h0->GetXaxis()->SetNoExponent();
  h1->GetXaxis()->SetNoExponent();
  h2->GetXaxis()->SetNoExponent();
  h3->GetXaxis()->SetNoExponent();
 
  h0->GetXaxis()->SetMoreLogLabels();
  h1->GetXaxis()->SetMoreLogLabels();
  h2->GetXaxis()->SetMoreLogLabels();
  h3->GetXaxis()->SetMoreLogLabels();

  double m0 = h0 -> GetMaximum();
  double m1 = h1 -> GetMaximum();
  double m2 = h2 -> GetMaximum();
  double m3 = h3 -> GetMaximum();

  vector<double> v;
  v.push_back(m0);
  v.push_back(m1);
  v.push_back(m2);
  v.push_back(m3);  
  vector<double>::const_iterator largest = max_element(v.begin(),v.end());
  double max  = *largest;

  h0->GetYaxis()->SetRangeUser(0,max+max*0.5);
  h1->GetYaxis()->SetRangeUser(0,max+max*0.5);
  h2->GetYaxis()->SetRangeUser(0,max+max*0.5);
  h3->GetYaxis()->SetRangeUser(0,max+max*0.5);

  h1->SetMarkerStyle(20);
  h1->SetMarkerColor(2);
  h1->SetMarkerSize(1.5);
  h1->SetLineColor(2);
  h1->SetLineWidth(2);

  h1->GetYaxis()->SetTitleSize(0.065);
  h1->GetYaxis()->SetTitleOffset(0.9); 
  h1->GetYaxis()->SetLabelSize(0.06);

  h1->GetXaxis()->SetNdivisions(506);
  h1->GetXaxis()->SetLabelFont(42);
  h1->GetXaxis()->SetLabelSize(0.05);
  h1->GetXaxis()->SetTitleSize(0.056);
  h1->GetXaxis()->SetTickLength(0.045);
  h1->GetXaxis()->SetTitleOffset(1.15);
  h1->GetXaxis()->SetTitleFont(42);

  h1->GetYaxis()->SetTitle("t-tag mistag rate");
  h1->GetYaxis()->SetNdivisions(506);
  h1->GetYaxis()->SetLabelFont(42);
  h1->GetYaxis()->SetLabelSize(0.05);
  h1->GetYaxis()->SetTitleSize(0.06125);
  h1->GetYaxis()->SetTitleOffset(1.17);
  h1->GetYaxis()->SetTitleFont(42);

  h1->GetZaxis()->SetLabelFont(42);
  h1->GetZaxis()->SetLabelSize(0.0425);
  h1->GetZaxis()->SetTitleSize(0.0475);
  h1->GetZaxis()->SetTitleFont(42);

  h1->Draw("");

  h0->SetMarkerStyle(20);
  h0->SetMarkerSize(1.5);
  h0->SetMarkerColor(1);
  h0->SetLineColor(1);
  h0->SetLineStyle(1);
  h0->SetLineWidth(2);

  h2->SetMarkerStyle(20);
  h2->SetMarkerSize(1.5);
  h2->SetMarkerColor(3);
  h2->SetLineColor(3);
  h2->SetLineStyle(1);
  h2->SetLineWidth(2);

  h3->SetMarkerStyle(20);
  h3->SetMarkerSize(1.5);
  h3->SetMarkerColor(4);
  h3->SetLineColor(4);
  h3->SetLineStyle(1);
  h3->SetLineWidth(2);

  h0->Draw("same");
  h2->Draw("same");
  h3->Draw("same");

  TLegend * leg;
  leg = new TLegend( 0.64, 0.67,0.98, 0.86);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetFillStyle(4000);
  leg->SetTextSize(0.042); 
  leg->AddEntry( h0   , "Inclusive" , "LP" );
  leg->AddEntry( h1   , "0btag"     , "LP" );  
  leg->AddEntry( h2   , "1btag"     , "LP" );  
  leg->AddEntry( h3   , "2btag"     , "LP" );  
  leg->Draw("same");

  TLatex *   tex = new TLatex(0.18,0.83,"#font[62]{CMS} #font[52]{Preliminary}");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.0625);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(0.96,0.936,"36.2 fb^{-1} (13 TeV)");
  tex->SetNDC();
  tex->SetTextAlign(31);
  tex->SetTextFont(42);
  tex->SetTextSize(0.0575);
  tex->SetLineWidth(2);
  tex->Draw();
  

  // TPaveText *textbox1 = new TPaveText(0.54,0.87,0.89,0.93,"NDC");
  // textbox1->SetFillColor(0);
  // textbox1->SetLineColor(0);
  // TText *line1 = textbox1->AddText("36.2 fb^{-1} (13 TeV)");
  // line1->SetTextColor(1);
  // line1->SetTextSize(23);
  // line1->SetTextFont(42);
  // line1->SetTextAlign(33); //first number = horizontal alignment (1 left, 2 center, 3 right). second number =vertical alignment (1 top, 2 center, 3 bottom)
  
  gPad->RedrawAxis();

  string savename2 = savefolder+ "compare_tmistag_"+savestring+"_nbins"+nbins+"_"+poststring+".pdf";
  cout<<savename2<<endl;

  c1237->SetLogx();
  c1237->SaveAs(savename2.c_str());

}

void plot2(TH1D * h0, TH1D * h1, string savestring, string savestring2, string savefolder, string nbins,  string poststring ){

  gStyle->SetOptStat(0);
  gROOT->UseCurrentStyle();
  gROOT->ForceStyle();

  gROOT->Reset();
  gROOT->ForceStyle(); 
  
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

  string title = ";Jet Momentum [GeV]; Mistag Rate";
  h0->SetTitle(title.c_str());
  h1->SetTitle(title.c_str());
  
  h0->GetXaxis()->SetNoExponent();
  h1->GetXaxis()->SetNoExponent();
  
  h0->GetXaxis()->SetMoreLogLabels();
  h1->GetXaxis()->SetMoreLogLabels();

  double m0 = h0 -> GetMaximum();
  double m1 = h1 -> GetMaximum();

  vector<double> v;
  v.push_back(m0);
  v.push_back(m1);
 
  vector<double>::const_iterator largest = max_element(v.begin(),v.end());
  double max  = *largest;

  h0->GetYaxis()->SetRangeUser(0,max+max*0.5);
  h1->GetYaxis()->SetRangeUser(0,max+max*0.5);
 
  h1->SetMarkerStyle(20);
  h1->SetMarkerColor(2);
  h1->SetMarkerSize(1.5);
  h1->SetLineColor(2);
  h1->SetLineWidth(2);

  h1->GetYaxis()->SetTitleSize(0.065);
  h1->GetYaxis()->SetTitleOffset(0.9); 
  h1->GetYaxis()->SetLabelSize(0.06);

  h1->GetXaxis()->SetNdivisions(506);
  h1->GetXaxis()->SetLabelFont(42);
  h1->GetXaxis()->SetLabelSize(0.05);
  h1->GetXaxis()->SetTitleSize(0.056);
  h1->GetXaxis()->SetTickLength(0.045);
  h1->GetXaxis()->SetTitleOffset(1.15);
  h1->GetXaxis()->SetTitleFont(42);

  h1->GetYaxis()->SetTitle("t-tag mistag rate");
  h1->GetYaxis()->SetNdivisions(506);
  h1->GetYaxis()->SetLabelFont(42);
  h1->GetYaxis()->SetLabelSize(0.05);
  h1->GetYaxis()->SetTitleSize(0.06125);
  h1->GetYaxis()->SetTitleOffset(1.17);
  h1->GetYaxis()->SetTitleFont(42);

  h1->GetZaxis()->SetLabelFont(42);
  h1->GetZaxis()->SetLabelSize(0.0425);
  h1->GetZaxis()->SetTitleSize(0.0475);
  h1->GetZaxis()->SetTitleFont(42);

  h1->Draw("");

  h0->SetMarkerStyle(20);
  h0->SetMarkerSize(1.5);
  h0->SetMarkerColor(1);
  h0->SetLineColor(1);
  h0->SetLineStyle(1);
  h0->SetLineWidth(2);

  h0->Draw("same");

  TLegend * leg;
  leg = new TLegend( 0.64, 0.67,0.98, 0.86);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetFillStyle(4000);
  leg->SetTextSize(0.042); 
  leg->AddEntry( h0   , "#DeltaY>1.0" , "LP" );
  leg->AddEntry( h1   , "#DeltaY<1.0"     , "LP" );  
  leg->Draw("same");

  TLatex *   tex = new TLatex(0.18,0.83,"#font[62]{CMS} #font[52]{Preliminary}");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.0625);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(0.96,0.936,"36.2 fb^{-1} (13 TeV)");
  tex->SetNDC();
  tex->SetTextAlign(31);
  tex->SetTextFont(42);
  tex->SetTextSize(0.0575);
  tex->SetLineWidth(2);
  tex->Draw();
  

  // TPaveText *textbox1 = new TPaveText(0.54,0.87,0.89,0.93,"NDC");
  // textbox1->SetFillColor(0);
  // textbox1->SetLineColor(0);
  // TText *line1 = textbox1->AddText("36.2 fb^{-1} (13 TeV)");
  // line1->SetTextColor(1);
  // line1->SetTextSize(23);
  // line1->SetTextFont(42);
  // line1->SetTextAlign(33); //first number = horizontal alignment (1 left, 2 center, 3 right). second number =vertical alignment (1 top, 2 center, 3 bottom)
  
  gPad->RedrawAxis();

  string savename2 = savefolder+ "compare_tmistag_"+savestring+savestring2+"_nbins"+nbins+"_"+poststring+".pdf";
  cout<<savename2<<endl;

  c1237->SetLogx();
  c1237->SaveAs(savename2.c_str());

}
