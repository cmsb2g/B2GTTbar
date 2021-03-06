#include "TROOT.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
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

void plot(string);
void plotCompare(string, string, string, string, string);

void run(){
  // plot("7");
  // plot("9");
  /*plot("6");
  plot("10");
  plot("13");*/
  // plot("30");
  plotCompare("13","10","6","dRapLo","|#Deltay| < 1.0");
  plotCompare("13","10","6","dRapHi", "|#Deltay| > 1.0");
}

void plotCompare(string nbins_0btag, string nbins_1btag, string nbins_2btag, string dRap, string dRapLabel){


  gStyle->SetOptStat(0);
  gROOT->UseCurrentStyle();
  gROOT->ForceStyle();


  gROOT->Reset();
  gROOT->ForceStyle(); 
  // gROOT->SetBatch(); 
  
  // TCanvas *c1237= new TCanvas("c1237","",200,10,950,700);
  // TCanvas *c1237= new TCanvas("c1237","",1,1,745,600);
  TCanvas *c1237= new TCanvas("c1237","",1,1,745,640);

  // TCanvas *c1 = new TCanvas("c1", "c1",1,1,745,701);
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

  string data_0btag = "/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/runs/run20160706/MistagRate_nbins_20160706_"+nbins_0btag+"_ttbar_Subtract_outAntiTag_JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65_20160706.root";
  TFile * F_0btag_subtract                 = new TFile( data_0btag.c_str() );
  string data_1btag = "/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/runs/run20160706/MistagRate_nbins_20160706_"+nbins_1btag+"_ttbar_Subtract_outAntiTag_JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65_20160706.root";
  TFile * F_1btag_subtract                 = new TFile( data_1btag.c_str() );
    string data_2btag = "/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/runs/run20160706/MistagRate_nbins_20160706_"+nbins_2btag+"_ttbar_Subtract_outAntiTag_JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65_20160706.root";
  TFile * F_2btag_subtract                 = new TFile( data_2btag.c_str() );

  TH1D *histos[3];

  string hist_name_0btag = "h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_"+dRap+"_0btag";
  string hist_name_1btag = "h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_"+dRap+"_1btag";
  string hist_name_2btag = "h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_"+dRap+"_2btag";

  histos[0] = (TH1D*)F_0btag_subtract   ->Get(hist_name_0btag.c_str());
  histos[1] = (TH1D*)F_1btag_subtract   ->Get(hist_name_1btag.c_str());
  histos[2] = (TH1D*)F_2btag_subtract   ->Get(hist_name_2btag.c_str());

  string title = ";Jet momentum [GeV]; t mistag rate";
  histos[0]->GetYaxis()->SetTitleSize(0.065);
  histos[0]->GetYaxis()->SetTitleOffset(0.9); // 0.7);
  histos[0]->GetYaxis()->SetLabelSize(0.06);
  
  histos[0]->GetXaxis()->SetNdivisions(506);
  histos[0]->GetXaxis()->SetLabelFont(42);
  histos[0]->GetXaxis()->SetLabelSize(0.05);//0.0425);
  histos[0]->GetXaxis()->SetTitleSize(0.056);//0.0475);0.0475);
  histos[0]->GetXaxis()->SetTickLength(0.045);
  histos[0]->GetXaxis()->SetTitleOffset(1.15);
  histos[0]->GetXaxis()->SetTitleFont(42);
  
  histos[0]->GetYaxis()->SetNdivisions(506);
  histos[0]->GetYaxis()->SetLabelFont(42);
  histos[0]->GetYaxis()->SetLabelSize(0.05);//  //0.04375);//0.06375);
  histos[0]->GetYaxis()->SetTitleSize(0.06125);//0.07125);
  histos[0]->GetYaxis()->SetTitleOffset(1.17);//0.9);
  histos[0]->GetYaxis()->SetTitleFont(42);
  
  histos[0]->GetZaxis()->SetLabelFont(42);
  histos[0]->GetZaxis()->SetLabelSize(0.0425);
  histos[0]->GetZaxis()->SetTitleSize(0.0475);
  histos[0]->GetZaxis()->SetTitleFont(42);

  double d0 = 0.0;
  for (unsigned int i=0; i< 3; i++ ){
    
    histos[i]->SetTitle(title.c_str());
    histos[i]->GetXaxis()->SetNoExponent();
    histos[i]->GetXaxis()->SetMoreLogLabels();

    histos[i]->SetMarkerSize(1.5);
    histos[i]->SetLineStyle(1);
    histos[i]->SetLineWidth(2);

    d0 = max(d0,histos[i]->GetMaximum());
  }
  
  histos[0]->SetMarkerColor(2);
  histos[0]->SetMarkerStyle(20);
  histos[0]->SetLineColor(2);
  histos[0]->GetYaxis()->SetRangeUser(0.01,d0*1.5);
  histos[0]->Draw();

  histos[1]->SetMarkerColor(3);
  histos[1]->SetMarkerStyle(21);
  histos[1]->SetLineColor(3);
  histos[1]->Draw("SAME");

  histos[2]->SetMarkerColor(4);
  histos[2]->SetMarkerStyle(22);
  histos[2]->SetLineColor(4);
  histos[2]->Draw("SAME");

  TLatex *   tex = new TLatex(0.18,0.83,"#font[62]{CMS}"); //#font[52]{Preliminary}");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.0625);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(0.96,0.936,"2.6 fb^{-1} (13 TeV)");
  tex->SetNDC();
  tex->SetTextAlign(31);
  tex->SetTextFont(42);
  // tex->SetTextSize(0.0625);
  tex->SetTextSize(0.0575);
  tex->SetLineWidth(2);
  tex->Draw();

  tex = new TLatex(0.18,0.80, dRapLabel.c_str());  //(0.66,0.87, dRapLabel.c_str());
  tex->SetNDC();
  tex->SetTextAlign(13);
  tex->SetTextFont(42);
  tex->SetTextSize(0.045);
  tex->SetLineWidth(2);
  tex->Draw();

  // leg = new TLegend( 0.45, 0.67,0.84, 0.83); //0.51, 0.66,0.84, 0.83
  leg = new TLegend(0.16,0.56,0.5,0.75); //( 0.64, 0.63,0.98, 0.82); //0.51, 0.66,0.84, 0.83
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetFillStyle(4000);
  leg->SetTextSize(0.042);  //0.03
  leg->AddEntry( histos[0]   , "0 b tag"  , "LP" );
  leg->AddEntry( histos[1]   , "1 b tag"  , "LP" );
  leg->AddEntry( histos[2]   , "2 b tag"  , "LP" );
  leg->Draw("same");

  gPad->RedrawAxis();

  c1237->SetLogx();

  string savename = "plots_74X/plots_mistag/h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_"+dRap+"_btagCompare_tmistag.pdf";
  cout<<savename<<endl;
  c1237->SaveAs(savename.c_str());
  
  string savenamelog = "plots_74X/plots_mistag/h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_"+dRap+"_btagCompare_tmistag_log.pdf";
  cout<<savenamelog<<endl;
  //if (dRap.find("Hi") != std::string::npos) histos[0]->SetMaximum(histos[0]->GetMaximum()*10);
  //else histos[0]->SetMaximum(histos[0]->GetMaximum()*70);
  histos[0]->SetMaximum(1.75);
  c1237->SetLogy();
  c1237->SaveAs(savenamelog.c_str());
      
}


void plot(string nbins){


  gStyle->SetOptStat(0);
  gROOT->UseCurrentStyle();
  gROOT->ForceStyle();


  gROOT->Reset();
  gROOT->ForceStyle(); 
  // gROOT->SetBatch(); 
  
  // TCanvas *c1237= new TCanvas("c1237","",200,10,950,700);
  // TCanvas *c1237= new TCanvas("c1237","",1,1,745,600);
  TCanvas *c1237= new TCanvas("c1237","",1,1,745,640);

  // TCanvas *c1 = new TCanvas("c1", "c1",1,1,745,701);
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






  // c1237->cd();
  // TPad *p1237= new TPad("p1237","",200,10,950,700);
  // CMS_lumi(c1237, 4, 10);

  // string data = "MistagRate_nbins_051916_"+nbins+"_ttbar_Subtract_outAntiTag_JetHT_Run2015D_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_20160318_051816_BothParts.root";
  // string MC   =  "MistagRate_nbins_052016_"+nbins+"_MC_outAntiTag_QCD_HT700toInf_B2Gv8p4_reader603e_notrig_052016_nom_scaled.root";
  
  /*string data   =  "/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/runs/run20160706/MistagRate_nbins_20160706_"+nbins+"_ttbar_Subtract_outAntiTag_JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65_20160706.root";
    string MC   =  "/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/runs/run20160706/MistagRate_nbins_20160706_"+nbins+"_MC_outAntiTag_QCD_HT700toInf_B2Gv8p4_reader603e_notrig_20160706_nom_scaled.root";*/
  string data   =  "/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/runs/run20160520/MistagRate_nbins_20160520_"+nbins+"_ttbar_Subtract_outAntiTag_JetHT_Run2015D_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_20160318_051816_BothParts.root";
  string MC   =  "/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/runs/run20160520/MistagRate_nbins_20160520_"+nbins+"_MC_outAntiTag_QCD_HT700toInf_B2Gv8p4_reader603e_notrig_052016_nom_scaled.root";  

  TFile * F_data_subtract                 = new TFile( data.c_str() );
  // TFile * F_MC                 = new TFile( "Mistag_AntiTagDec17_QCDscaled_25ns_B2Gv8p4_reader5a85e65.root");
  
  TFile * F_MC                 = new TFile( MC.c_str() );
  // TFile * F_data_noSubtract                 = new TFile( "MistagRate_nbins8_noSubtract_outNTR_JetHT_Run2015D_PromptReco-v3andv4_oct19json_jdolen_all.root");

  // TH1F * h0                = F0               ->Get( "h_mistag_AntiTagMinMass30_ReqTopMassFat_TagMassFatMinMass" );
  // TH1F * h1                = F1               ->Get( "h_mistag_AntiTagMinMass30_ReqTopMassFat_TagMassFatMinMass" );


  TPaveText *textbox1 = new TPaveText(0.54,0.87,0.89,0.93,"NDC");
  textbox1->SetFillColor(0);
  textbox1->SetLineColor(0);
  TText *line1 = textbox1->AddText("2.6 fb^{-1} (13 TeV)");
  line1->SetTextColor(1);
  line1->SetTextSize(23);
  line1->SetTextFont(42);
  line1->SetTextAlign(33); //first number = horizontal alignment (1 left, 2 center, 3 right). second number =vertical alignment (1 top, 2 center, 3 bottom)
  
  TPaveText *textbox3 = new TPaveText(0.37,0.75,0.35,0.93,"NDC"); //0.19, .87, 0.35, 0.93
  textbox3->SetFillColor(0);
  textbox3->SetLineColor(0);
  // TText *line2 = textbox3->AddText("#bf{#it{CMS Preliminary}}");
  // line2->SetTextColor(1);
  // line2->SetTextSize(23);
  // line2->SetTextFont(43);
  // line2->SetTextAlign(33); 

 
  // Loop over anti-tag and tag combinations and make mistag rate
  vector <string> antitag_def;
  vector <string> tag_def;

  //antitag_def.push_back("AntiTagMinMass30_ReqTopMassFat");
  //antitag_def.push_back("AntiTagMinMass30_ReqTopMassSD");
  //antitag_def.push_back("AntiTagMinMass50_ReqTopMassFat");
  //antitag_def.push_back("AntiTagMinMass50_ReqTopMassSD");
  //antitag_def.push_back("AntiTagTau32_ReqTopMassFat");
  antitag_def.push_back("AntiTagTau32_ReqTopMassSD");
 
  //tag_def.push_back("_TagMassFatMinMass");
  //tag_def.push_back("_TagMassSD"        );
  tag_def.push_back("_TagMassSDTau32"   );
  //tag_def.push_back("_TagMassSDMinMass" );

  //string pre = "AllHad/h_";
  string pre = "h_";
  string save_pre = "h_mistag_";
  string probe = "_Probe";
  vector <string> post;
  post.push_back("_jetP_dRapHi_inclusive");
  post.push_back("_jetP_dRapHi_2btag");
  post.push_back("_jetP_dRapHi_1btag");
  post.push_back("_jetP_dRapHi_0btag");
  post.push_back("_jetP_dRapLo_inclusive");
  post.push_back("_jetP_dRapLo_2btag");
  post.push_back("_jetP_dRapLo_1btag");
  post.push_back("_jetP_dRapLo_0btag");
  post.push_back("_jetP_dRapIn_inclusive");
  post.push_back("_jetP_dRapIn_2btag");
  post.push_back("_jetP_dRapIn_1btag");
  post.push_back("_jetP_dRapIn_0btag");
    
  // vector <string> name_antitag_def;
  // name_antitag_def.push_back("AntiTag: #tau_{3}/#tau_{2}>0.69, 110 < m_{SD}<210  ");
 
  vector <string> name_tag_def_fix;
  // name_tag_def_fix.push_back("Tag: 140 < m_{fat}<250,  m_{min} > 50"         );
  // name_tag_def_fix.push_back("Tag: 110 < m_{SD}<210"                         );
  // name_tag_def_fix.push_back("Tag: 110 < m_{SD}<210,  #tau_{3}/#tau_{2}<0.69");
  // name_tag_def_fix.push_back("Tag: 110 < m_{SD}<210,  m_{min} > 50"          );

 vector <string> name_post_def;
 name_post_def.push_back("|#Deltay|>1.0, inclusive");
 name_post_def.push_back("|#Deltay|>1.0, 2 btag");
 name_post_def.push_back("|#Deltay|>1.0, 1 btag");
 name_post_def.push_back("|#Deltay|>1.0, 0 btag");
 name_post_def.push_back("|#Deltay|<1.0, inclusive");
 name_post_def.push_back("|#Deltay|<1.0, 2 btag");
 name_post_def.push_back("|#Deltay|<1.0, 1 btag");
 name_post_def.push_back("|#Deltay|<1.0, 0 btag");
 name_post_def.push_back("|#Deltay| all, inclusive");
 name_post_def.push_back("|#Deltay| all, 2 btag");
 name_post_def.push_back("|#Deltay| all, 1 btag");
 name_post_def.push_back("|#Deltay| all, 0 btag");
  
 


  

  for (unsigned int i=0; i<antitag_def.size(); i++ ){
    for (unsigned int j=0; j<tag_def.size(); j++ ){
      for (unsigned int k=0; k<post.size(); k++ ){



        string savename = save_pre + antitag_def[i] + tag_def[j] + post[k] ;
        string savename3 = "teff_" + antitag_def[i] + tag_def[j] + post[k] ;

        // // cout<<numer<<"      "<<denom<<"     "<<
        // cout<<savename<<endl;

        // // string numer = pre + antitag_def[i] + tag_def[j] + post;
        // // string denom = pre + antitag_def[i] + probe+post;
        // string savename = save_pre + antitag_def[i] + tag_def[j] ;
        cout<<savename<<endl;

       // string ttbar_numer_name           = "check_"+antitag_def[i] + tag_def[j] + post +"_ttbar";
       // string ttbar_denom_name           = "check_"+antitag_def[i] + probe      + post +"_ttbar";
       // string data_nosubtract_numer_name =  "check_"+antitag_def[i] + tag_def[j] + post +"_data_nosubtract";
       // string data_nosubtract_denom_name =  "check_"+antitag_def[i] + probe      + post +"_data_nosubtract";
       // string data_subtract_numer_name   =  "check_"+antitag_def[i] + tag_def[j] + post +"_data_subtract";
       // string data_subtract_denom_name   =  "check_"+antitag_def[i] + probe      + post +"_data_subtract";



        TH1D * h0 = (TH1D*)F_data_subtract   ->Get(savename.c_str());
        TH1D * h1 = (TH1D*)F_MC              ->Get(savename.c_str());
        // TH1D * h2 = (TH1D*)F_data_noSubtract ->Get(savename.c_str());

 
        string savename_eff = "teff_" + antitag_def[i] + tag_def[j]  + post[k]  ;
        string savename_eff_default = savename_eff + "_default" ;     
        string savename_eff_normal  = savename_eff + "_normal"  ;    
        string savename_eff_wilson  = savename_eff + "_wilson"  ;    
        string savename_eff_jeffrey = savename_eff + "_jeffrey" ;  

        TEfficiency * eff_default = (TEfficiency*) F_data_subtract->Get(savename_eff_default .c_str() );
        TEfficiency * eff_normal  = (TEfficiency*) F_data_subtract->Get(savename_eff_normal  .c_str() );
        TEfficiency * eff_wilson  = (TEfficiency*) F_data_subtract->Get(savename_eff_wilson  .c_str() );
        TEfficiency * eff_jeffrey = (TEfficiency*) F_data_subtract->Get(savename_eff_jeffrey .c_str() );

        // TH1D * data_nosubtract_numer = (TH1D*)F_data_subtract ->Get(data_nosubtract_numer_name.c_str());
        // TH1D * data_nosubtract_denom = (TH1D*)F_data_subtract ->Get(data_nosubtract_denom_name.c_str());

        // TH1D * data_subtract_numer = (TH1D*)F_data_subtract ->Get(data_subtract_numer_name.c_str());
        // TH1D * data_subtract_denom = (TH1D*)F_data_subtract ->Get(data_subtract_denom_name.c_str());

        // TH1D * ttbar_numer              = (TH1D*)F_data_subtract ->Get(ttbar_numer_name.c_str());
        // TH1D * ttbar_denom              = (TH1D*)F_data_subtract ->Get(ttbar_denom_name.c_str());


        string title = ";Jet momentum [GeV]; Mistag Rate";
        h0->SetTitle(title.c_str());
        h1->SetTitle(title.c_str());
        h0->GetXaxis()->SetNoExponent();
        h1->GetXaxis()->SetNoExponent();
        h0->GetXaxis()->SetMoreLogLabels();
        h1->GetXaxis()->SetMoreLogLabels();


        double d0 = h0 -> GetMaximum();
        double d1 = h1 -> GetMaximum();
        cout<<"d0 "<<d0<<endl;
        cout<<"d1 "<<d1<<endl;
        if (d1>d0) h1->GetYaxis()->SetRangeUser(0,d1+d1*0.5);
        else h1->GetYaxis()->SetRangeUser(0,d0+d0*0.5);

        // h2->SetMarkerStyle(20);
        // h2->SetMarkerColor(1);
        // h2->SetLineColor(1);
        // h2->Draw();

     
        h1->SetMarkerStyle(21);
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


  bool specialLogAxis = false;
  TGaxis *a;
  if (specialLogAxis){
 gPad->Modified(); gPad->Update(); // make sure it's drawn

  // http://root.cern.ch/root/html/TF1.html#TF1:TF1@1
  // http://root.cern.ch/root/html/TFormula.html#TFormula:Analyze
  TF1 *f_h1_log10_x_axis = new TF1("f_h1_log10_x_axis", // name
               "log10(x)", // formula
               h1->GetXaxis()->GetXmin(), // xmin
               h1->GetXaxis()->GetXmax()); // xmax

  // http://root.cern.ch/root/html/TGaxis.html#TGaxis:TGaxis@3
  // http://root.cern.ch/root/html/TGaxis.html#TGaxis:PaintAxis
  a = new TGaxis(h1->GetXaxis()->GetXmin(), // xmin
          h1->GetYaxis()->GetXmin(), // ymin
          h1->GetXaxis()->GetXmax(), // xmax
          h1->GetYaxis()->GetXmin(), // ymax
          "f_h1_log10_x_axis", // funcname
          1005, // ndiv (try 100006 or 506, don't try 1006)
          "BS", // chopt (try "BS" or "UBS")
          0.0); // gridlength

  // a->SetTickSize(h1->GetTickLength("X")); // use "the same" size
  a->SetTickSize(1.0 * h1->GetTickLength("X")); // make it bigger
  h1->SetTickLength(0.0, "X"); // get rid of "original" ticks

    gPad->SetTickx();
    gPad->SetTicky(); 

  if (!(TString(a->GetOption())).Contains("U")) {
    a->SetLabelFont(h1->GetLabelFont("X")); // use "the same" font
    a->SetLabelSize(h1->GetLabelSize("X")); // use "the same" size
    h1->SetLabelSize(0.0, "X"); // get rid of "original" labels
  }
}

// ndiv : Number of divisions.

//     ndiv=N1 + 100*N2 + 10000*N3
//     N1=number of 1st divisions.
//     N2=number of 2nd divisions.
//     N3=number of 3rd divisions. e.g.:
//         ndiv=0 –> no tick marks.
//         ndiv=2 –> 2 divisions, one tick mark in the middle of the axis.






//         Int_t    step_normal     = 1;
//          Int_t    factor_large    = 2;
//          Float_t  fraction_normal = 0.015;
//          Float_t  fraction_large  = 0.035;

// Float_t uymin = c1237->GetUymin();
//   Float_t uymax = c1237->GetUymax();
 
 
//   // x-axis ticks
//   //----------------------------------------------------------------------------
//   if (c1237->GetLogx()) {

//     xlo = h1->GetMinimum();
//     xup = h1->GetMaximum();
//     Int_t ixlow      = Int_t(xlo);
//     Int_t ixup       = Int_t(xup);
//     Int_t step_large = factor_large * step_normal;

//     h1->GetXaxis()->SetNdivisions(0);
   
//     Float_t ymin = (c1237->GetLogy()) ? pow(10, uymin) : uymin;
//     Float_t ymax = (c1237->GetLogy()) ? pow(10, uymax) : uymax;

//     Float_t bottom_tick_normal = fraction_normal * (uymax - uymin);
//     Float_t bottom_tick_large  = fraction_large  * (uymax - uymin);

//     Float_t top_tick_normal = fraction_normal * (uymax - uymin);
//     Float_t top_tick_large  = fraction_large  * (uymax - uymin);

//     if (c1237->GetLogy()) {

//       bottom_tick_normal = pow(10, uymin + bottom_tick_normal) - pow(10, uymin);
//       bottom_tick_large  = pow(10, uymin + bottom_tick_large)  - pow(10, uymin);

//       top_tick_normal = pow(10, uymax) - pow(10, uymax - top_tick_normal);
//       top_tick_large  = pow(10, uymax) - pow(10, uymax - top_tick_large);
//     }

//     TLine tick;

//     for (Int_t i=ixlow; i<=ixup; i+=step_normal) {

//       Float_t xx = i;

//       tick.DrawLine(xx, ymin, xx, ymin + ((i-ixlow)%step_large == 0 ? bottom_tick_large : bottom_tick_normal));
//       tick.DrawLine(xx, ymax, xx, ymax - ((i-ixlow)%step_large == 0 ? top_tick_large    : top_tick_normal));
//     }


//     // x-axis labels
//     //--------------------------------------------------------------------------
//     Float_t ylatex = ymin - bottom_tick_normal;

//     if ((ixup-ixlow)%step_large >= step_normal) {

//       TLatex* latex = new TLatex(xup, ylatex, Form("%.0f", xup));
     
//       latex->SetTextAlign(   23);
//       latex->SetTextFont (   42);
//       latex->SetTextSize (0.035);
//       latex->Draw("same");
//     }

//     for (Int_t i=ixlow; i<ixup; i+=step_large) {

//       Float_t xx = i;

//       TLatex* latex = new TLatex(xx, ylatex, Form("%.0f", xx));

//       latex->SetTextAlign(   23);
//       latex->SetTextFont (   42);
//       latex->SetTextSize (0.035);
//       latex->Draw("same");
//     }
//   }



// gPad->SetGrid(1,1);

        h1->GetYaxis()->SetTitle("t-Mistag Rate");
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
        if (specialLogAxis){
          a->Draw();
          gPad->Modified(); gPad->Update(); // make sure it's redrawn
        }



        h0->SetMarkerStyle(20);
        h0->SetMarkerSize(1.5);
        h0->SetMarkerColor(4);
        h0->SetLineColor(4);
        h0->SetLineStyle(2);
        h0->SetLineWidth(2);
        // h2->Draw("same");



        h0->Draw("same");



        TLegend * leg;
        // leg = new TLegend( 0.45, 0.67,0.84, 0.83); //0.51, 0.66,0.84, 0.83
        leg = new TLegend( 0.54, 0.67,0.78, 0.82); //0.51, 0.66,0.84, 0.83
        leg->SetBorderSize(0);
        leg->SetFillColor(0);
        leg->SetFillStyle(4000);
        leg->SetTextSize(0.042);  //0.03
	// leg->AddEntry( h2   , "Data (no subtraction)" , "LP" );
        leg->AddEntry( h0   , "Data" , "LP" );
        leg->AddEntry( h1   , "QCD Simulation"  , "LP" );  //(Pythia 8)  " , "LP" );
        // leg->AddEntry( (TObject*)0 , name_post_def[k].c_str(), "");
        leg->Draw("same");

	TLatex *   tex = new TLatex(0.18,0.83,"#font[62]{CMS}"); //#font[52]{Preliminary}");
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.0625);
	tex->SetLineWidth(2);
	tex->Draw();
	tex = new TLatex(0.96,0.936,"2.6 fb^{-1} (13 TeV)");
	tex->SetNDC();
	tex->SetTextAlign(31);
	tex->SetTextFont(42);
	// tex->SetTextSize(0.0625);
	tex->SetTextSize(0.0575);
	tex->SetLineWidth(2);
	tex->Draw();
	tex = new TLatex(0.56,0.87, name_post_def[k].c_str());
	tex->SetNDC();
	tex->SetTextAlign(13);
	tex->SetTextFont(42);
	tex->SetTextSize(0.045);
	tex->SetLineWidth(2);
	tex->Draw();

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
        textbox3->Draw("same");
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
        cout<<savename<<endl;
        // string savename2 = "plots_74X/plots_mistag3/"+savename+"_20160520_tmistag.pdf";
        string savename2 = "plots_74X/plots_mistag/"+savename+"_"+nbins+"_20160520_tmistag.pdf";
        cout<<savename2<<endl;
        // c1237->SetLogx();
        // c1237->SaveAs(savename2.c_str());
        c1237->SetLogx();
        c1237->SaveAs(savename2.c_str());
      
        // //-----------------

        // // h2->Draw("");
        // h0->Draw("");
        //  eff_default ->SetLineColor(3);
        //  eff_normal  ->SetLineColor(5);
        //  eff_wilson  ->SetLineColor(6);
        //  eff_jeffrey ->SetLineColor(7);
        //  eff_default ->SetMarkerColor(3);
        //  eff_normal  ->SetMarkerColor(5);
        //  eff_wilson  ->SetMarkerColor(6);
        //  eff_jeffrey ->SetMarkerColor(7);
        //  eff_default ->SetLineWidth(3);
        //  eff_normal  ->SetLineWidth(2);
        //  eff_wilson  ->SetLineWidth(1);
        //  eff_jeffrey ->SetLineWidth(1);

        //  eff_default ->SetLineStyle(4);
        //  eff_normal  ->SetLineStyle(1);
        //  eff_wilson  ->SetLineStyle(5);
        //  eff_jeffrey ->SetLineStyle(1);
        // eff_default -> Draw("Psame");
        // // eff_normal  -> Draw("Psame");
        // eff_wilson  -> Draw("Psame");
        // // eff_jeffrey -> Draw("Psame");

        //   TLegend * leg5;
        // leg5 = new TLegend( 0.57, 0.66,0.84, 0.83);
        // leg5->SetBorderSize(0);
        // leg5->SetFillColor(0);
        // leg5->SetFillStyle(4000);
        // leg5->AddEntry( h0   , "Mistag binomial uncert" , "LP" );
        // leg5->AddEntry( eff_default    , "Mistag Clopper-Pearson uncert" , "LP" );
        // // leg5->AddEntry( eff_normal     , "Mistag Normal uncert" , "LP" );
        // leg5->AddEntry( eff_wilson     , "Mistag Wilson uncert" , "LP" );
        // // leg5->AddEntry( eff_jeffrey    , "Mistag Jeffrey uncert" , "LP" );
        // // leg->AddEntry( h1   , "QCD MC (Pythia 8)  " , "LP" );
        // leg5->Draw("same");




        // string savename7 = "plots_74X/plots_mistag/"+savename+"_teff.pdf";
        // c1237->SaveAs(savename7.c_str());
      
        // //-----------------
        // data_nosubtract_numer   ->SetLineColor(1); 
        // data_nosubtract_denom   ->SetLineColor(1); 
     

        // ttbar_numer   ->SetLineColor(2); 
        // ttbar_denom   ->SetLineColor(2); 
        // data_subtract_numer   ->SetLineColor(4); 
        // data_subtract_denom   ->SetLineColor(4); 
     

        // TLegend * leg2;
        // leg2 = new TLegend( 0.57, 0.66,0.84, 0.83);
        // leg2->SetBorderSize(0);
        // leg2->SetFillColor(0);
        // leg2->SetFillStyle(4000);
        // leg2->AddEntry( data_nosubtract_numer   , "Data (no subtraction)" , "L" );
        // leg2->AddEntry( data_subtract_numer   , "Data (ttbar subtracted)" , "L" );
        // leg2->AddEntry( ttbar_numer   , "ttbar" , "L" );
        // // leg->AddEntry( h1   , "QCD MC (Pythia 8)  " , "LP" );


        // data_nosubtract_numer->GetYaxis()->SetRangeUser( 0.01,data_nosubtract_numer -> GetMaximum()*1.2);
        // data_nosubtract_numer->Draw();
        // data_subtract_numer  ->Draw("same");
        // ttbar_numer          ->Draw("same");
        //         leg2->Draw("same");
        // string savename3 = "plots_74X/plots_mistag/"+savename+"_numer_predivide.pdf";
        // c1237->SetLogy();
        // c1237->SaveAs(savename3.c_str());

        // data_nosubtract_denom->GetYaxis()->SetRangeUser( 0.01,data_nosubtract_denom -> GetMaximum()*1.2);
        // data_nosubtract_denom->Draw();
        // data_subtract_denom  ->Draw("same");
        // ttbar_denom          ->Draw("same");
        //         leg2->Draw("same");
        // string savename4 = "plots_74X/plots_mistag/"+savename+"_denom_predivide.pdf";
        // c1237->SaveAs(savename4.c_str());
        // c1237->SetLogy(0);
        
}

    }
  }
}
