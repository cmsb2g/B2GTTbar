
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


void run(){


  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(kWhite);
  gStyle->SetCanvasDefH(500); //Height of canvas
  gStyle->SetCanvasDefW(800); //Width of canvas
  gStyle->SetCanvasDefX(0);   //POsition on screen
  gStyle->SetCanvasDefY(0);

  // For the Pad:
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadColor(kWhite);
  gStyle->SetPadGridX(false);
  gStyle->SetPadGridY(false);
  gStyle->SetGridColor(0);
  gStyle->SetGridStyle(3);
  gStyle->SetGridWidth(1);

  // For the frame:
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameBorderSize(1);
  gStyle->SetFrameFillColor(0);
  gStyle->SetFrameFillStyle(0);
  gStyle->SetFrameLineColor(1);
  gStyle->SetFrameLineStyle(1);
  gStyle->SetFrameLineWidth(1);

  // For the histo:
  gStyle->SetHistLineWidth(2);

  //For the fit/function:
  gStyle->SetOptFit(1);
  gStyle->SetFitFormat("5.4g");
  gStyle->SetFuncColor(2);
  gStyle->SetFuncStyle(1);
  gStyle->SetFuncWidth(1);

  //For the date:
  gStyle->SetOptDate(0);

  // For the statistics box:
  gStyle->SetOptFile(0);
  gStyle->SetOptStat(111111); // To display the mean and RMS:   SetOptStat("mr");
  gStyle->SetStatColor(kWhite);
  gStyle->SetStatFont(42);
  gStyle->SetStatFontSize(0.025);
  gStyle->SetStatTextColor(1);
  gStyle->SetStatFormat("6.4g");
  gStyle->SetStatBorderSize(1);
  gStyle->SetStatH(0.1);
  gStyle->SetStatW(0.15);

  // Margins:
  gStyle->SetPadTopMargin(0.14);
  gStyle->SetPadBottomMargin(0.14);
  gStyle->SetPadLeftMargin(0.17);//0.14);//0.16);
  gStyle->SetPadRightMargin(0.13);//0.3);//0.16);

  // For the Global title:
  gStyle->SetTitleFont(42);
  gStyle->SetTitleColor(1);
  gStyle->SetTitleTextColor(1);
  gStyle->SetTitleFillColor(10);
  gStyle->SetTitleFontSize(0.04);
  gStyle->SetTitleW(0); // Set the width of the title box
  gStyle->SetTitleX(0.5); // Set the position of the title box
  gStyle->SetTitleY(0.94); // Set the position of the title box


  // For the axis titles:
  gStyle->SetTitleColor(1, "XYZ");
  gStyle->SetTitleFont(42, "XYZ");
  gStyle->SetTitleSize(0.05, "XYZ");
  gStyle->SetTitleXOffset(1.2);
  gStyle->SetTitleOffset(1.5, "Y"); // Another way to set the Offset

  // For the axis labels:
  gStyle->SetLabelColor(1, "XYZ");
  gStyle->SetLabelFont(42, "XYZ");
  gStyle->SetLabelOffset(0.007, "YZ");
  gStyle->SetLabelOffset(0.012, "X");
  gStyle->SetLabelSize(0.045, "XYZ");

  // For the axis:
  gStyle->SetAxisColor(1, "XYZ");
  gStyle->SetStripDecimals(kTRUE);
  gStyle->SetTickLength(0.03, "XYZ");
  gStyle->SetNdivisions(510, "XYZ");
  gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  gStyle->SetPadTickY(1);

  // Change for log plots:
  gStyle->SetOptLogx(0);
  gStyle->SetOptLogy(0);
  gStyle->SetOptLogz(0);
  gStyle->SetPalette(1,0);

  gStyle->SetOptStat(0);
  gROOT->UseCurrentStyle();
  gROOT->ForceStyle();


  gROOT->Reset();
  gROOT->ForceStyle(); 
  // gROOT->SetBatch(); 
  

  TCanvas *c1237= new TCanvas("c1237","",200,10,950,700);

  TFile * F_data_subtract                 = new TFile( "MistagRate_nbins8_Substract_outNTR_JetHT_Run2015D_PromptReco-v3andv4_oct19json_jdolen_all.root");
  // TFile * F_MC                 = new TFile( "MistagRate_nbins17_MC_ModMass_mistagTagAndProbe_2015_09_28bkgdEst.root");
  TFile * F_data_noSubtract                 = new TFile( "MistagRate_nbins8_noSubstract_outNTR_JetHT_Run2015D_PromptReco-v3andv4_oct19json_jdolen_all.root");

  // TH1F * h0                = F0               ->Get( "h_mistag_AntiTagMinMass30_ReqTopMassFat_TagMassFatMinMass" );
  // TH1F * h1                = F1               ->Get( "h_mistag_AntiTagMinMass30_ReqTopMassFat_TagMassFatMinMass" );


  TPaveText *textbox1 = new TPaveText(0.54,0.87,0.89,0.93,"NDC");
  textbox1->SetFillColor(0);
  textbox1->SetLineColor(0);
  TText *line1 = textbox1->AddText("Run 2015D - 166 pb^{-1} (13 TeV)");
  line1->SetTextColor(1);
  line1->SetTextSize(23);
  line1->SetTextFont(43);
  line1->SetTextAlign(13); //first number = horizontal alignment (1 left, 2 center, 3 right). second number =vertical alignment (1 top, 2 center, 3 bottom)
  

  string pre = "h_";
  string post = "_jetPt";
  string probe = "_Probe";
  string save_pre = "h_mistag_";

  vector <string> antitag_def;
  vector <string> tag_def;

  antitag_def.push_back("AntiTagMinMass30_ReqTopMassFat");
  antitag_def.push_back("AntiTagMinMass30_ReqTopMassSD");
  antitag_def.push_back("AntiTagMinMass50_ReqTopMassFat");
  antitag_def.push_back("AntiTagMinMass50_ReqTopMassSD");
  antitag_def.push_back("AntiTagTau32_ReqTopMassFat");
  antitag_def.push_back("AntiTagTau32_ReqTopMassSD");
 
  tag_def.push_back("_TagMassFatMinMass");
  tag_def.push_back("_TagMassSD"        );
  tag_def.push_back("_TagMassSDTau32"   );
  tag_def.push_back("_TagMassSDMinMass" );



  vector <string> name_antitag_def;
  name_antitag_def.push_back("AntiTag: m_{min} < 30, 140 < m_{fat}<250 ");
  name_antitag_def.push_back("AntiTag: m_{min} < 30, 110 < m_{SD}<210  ");
  name_antitag_def.push_back("AntiTag: m_{min} < 50, 140 < m_{fat}<250 ");
  name_antitag_def.push_back("AntiTag: m_{min} < 50, 110 < m_{SD}<210  ");
  name_antitag_def.push_back("AntiTag: #tau_{3}/#tau_{2}>0.61, 140 < m_{fat}<250 ");
  name_antitag_def.push_back("AntiTag: #tau_{3}/#tau_{2}>0.61, 110 < m_{SD}<210  ");
 
  vector <string> name_tag_def_fix;
  name_tag_def_fix.push_back("Tag: 140 < m_{fat}<250,  m_{min} > 50"         );
  name_tag_def_fix.push_back("Tag: 110 < m_{SD}<210"                         );
  name_tag_def_fix.push_back("Tag: 110 < m_{SD}<210,  #tau_{3}/#tau_{2}<0.61");
  name_tag_def_fix.push_back("Tag: 110 < m_{SD}<210,  m_{min} > 50"          );



  for (unsigned int i=0; i<antitag_def.size(); i++ ){
      for (unsigned int j=0; j<tag_def.size(); j++ ){
        string numer = pre + antitag_def[i] + tag_def[j] + post;
        string denom = pre + antitag_def[i] + probe+post;
        string savename = save_pre + antitag_def[i] + tag_def[j] ;
        // cout<<numer<<"      "<<denom<<"     "<<savename<<endl;

       string ttbar_numer_name           = "check_"+antitag_def[i] + tag_def[j] + post +"_ttbar";
       string ttbar_denom_name           = "check_"+antitag_def[i] + probe      + post +"_ttbar";
       string data_nosubtract_numer_name =  "check_"+antitag_def[i] + tag_def[j] + post +"_data_nosubtract";
       string data_nosubtract_denom_name =  "check_"+antitag_def[i] + probe      + post +"_data_nosubtract";
       string data_subtract_numer_name   =  "check_"+antitag_def[i] + tag_def[j] + post +"_data_subtract";
       string data_subtract_denom_name   =  "check_"+antitag_def[i] + probe      + post +"_data_subtract";



        TH1D * h0 = (TH1D*)F_data_subtract   ->Get(savename.c_str());
        // TH1D * h1 = (TH1D*)F_MC              ->Get(savename.c_str());
        TH1D * h2 = (TH1D*)F_data_noSubtract ->Get(savename.c_str());


        string savename_eff = "teff_" + antitag_def[i] + tag_def[j] ;
        string savename_eff_default = savename_eff + "_default" ;     
        string savename_eff_normal  = savename_eff + "_normal"  ;    
        string savename_eff_wilson  = savename_eff + "_wilson"  ;    
        string savename_eff_jeffrey = savename_eff + "_jeffrey" ;  

        TEfficiency * eff_default = (TEfficiency*) F_data_subtract->Get(savename_eff_default .c_str() );
        TEfficiency * eff_normal  = (TEfficiency*) F_data_subtract->Get(savename_eff_normal  .c_str() );
        TEfficiency * eff_wilson  = (TEfficiency*) F_data_subtract->Get(savename_eff_wilson  .c_str() );
        TEfficiency * eff_jeffrey = (TEfficiency*) F_data_subtract->Get(savename_eff_jeffrey .c_str() );

        TH1D * data_nosubtract_numer = (TH1D*)F_data_subtract ->Get(data_nosubtract_numer_name.c_str());
        TH1D * data_nosubtract_denom = (TH1D*)F_data_subtract ->Get(data_nosubtract_denom_name.c_str());

        TH1D * data_subtract_numer = (TH1D*)F_data_subtract ->Get(data_subtract_numer_name.c_str());
        TH1D * data_subtract_denom = (TH1D*)F_data_subtract ->Get(data_subtract_denom_name.c_str());

        TH1D * ttbar_numer              = (TH1D*)F_data_subtract ->Get(ttbar_numer_name.c_str());
        TH1D * ttbar_denom              = (TH1D*)F_data_subtract ->Get(ttbar_denom_name.c_str());


        string title = ";Jet p_{T} (GeV); Mistag Rate";
        h0->SetTitle(title.c_str());


        // double d0 = h0 -> GetMaximum();
        // double d1 = h1 -> GetMaximum();

        // if (d0>d1) h0->GetYaxis()->SetRangeUser(0,d0+d0*0.4);
        // else h0->GetYaxis()->SetRangeUser(0,d1+d1*0.4);

        h2->SetMarkerStyle(20);
        h2->SetMarkerColor(1);
        h2->SetLineColor(1);
        h2->Draw();

        // h1->SetMarkerStyle(21);
        // h1->SetMarkerColor(2);
        // h1->SetLineColor(2);
        // h1->Draw("same");

        h0->SetMarkerStyle(20);
        h0->SetMarkerColor(4);
        h0->SetLineColor(4);
        h0->SetLineStyle(2);
        h2->Draw("same");
        h0->Draw("same");

        TLegend * leg;
        leg = new TLegend( 0.57, 0.66,0.84, 0.83);
        leg->SetBorderSize(0);
        leg->SetFillColor(0);
        leg->SetFillStyle(4000);
       leg->AddEntry( h2   , "Data (no subtraction)" , "LP" );
        leg->AddEntry( h0   , "Data (ttbar subtracted)" , "LP" );
        // leg->AddEntry( h1   , "QCD MC (Pythia 8)  " , "LP" );
        leg->Draw("same");




        TPaveText *textbox2 = new TPaveText(0.19,0.73,0.5,0.84,"NDC");
        textbox2->SetFillColor(0);
        textbox2->SetLineColor(0); 
        TText *line1 = textbox2->AddText( name_antitag_def[i].c_str() );
        TText *line2 = textbox2->AddText( name_tag_def_fix[j].c_str() );
        line1->SetTextColor(1);
        line2->SetTextColor(1);
        line1->SetTextSize(22);
        line2->SetTextSize(22);
        line1->SetTextFont(43);
        line2->SetTextFont(43);
        line1->SetTextAlign(13); //first number = horizontal alignment (1 left, 2 center, 3 right). second number =vertical alignment (1 top, 2 center, 3 bottom)
        line2->SetTextAlign(13); //first number = horizontal alignment (1 left, 2 center, 3 right). second number =vertical alignment (1 top, 2 center, 3 bottom)
    


        textbox1->Draw("same");
        textbox2->Draw("same");
        gPad->RedrawAxis();



        cout<<savename<<endl;
        string savename2 = "plots_mistag/"+savename+"_tmistag.pdf";
        cout<<savename2<<endl;
        c1237->SaveAs(savename2.c_str());
      
        //-----------------

        // h2->Draw("");
        h0->Draw("");
         eff_default ->SetLineColor(3);
         eff_normal  ->SetLineColor(5);
         eff_wilson  ->SetLineColor(6);
         eff_jeffrey ->SetLineColor(7);
         eff_default ->SetMarkerColor(3);
         eff_normal  ->SetMarkerColor(5);
         eff_wilson  ->SetMarkerColor(6);
         eff_jeffrey ->SetMarkerColor(7);
         eff_default ->SetLineWidth(3);
         eff_normal  ->SetLineWidth(2);
         eff_wilson  ->SetLineWidth(1);
         eff_jeffrey ->SetLineWidth(1);

         eff_default ->SetLineStyle(4);
         eff_normal  ->SetLineStyle(1);
         eff_wilson  ->SetLineStyle(5);
         eff_jeffrey ->SetLineStyle(1);
        eff_default -> Draw("Psame");
        // eff_normal  -> Draw("Psame");
        eff_wilson  -> Draw("Psame");
        // eff_jeffrey -> Draw("Psame");

          TLegend * leg5;
        leg5 = new TLegend( 0.57, 0.66,0.84, 0.83);
        leg5->SetBorderSize(0);
        leg5->SetFillColor(0);
        leg5->SetFillStyle(4000);
        leg5->AddEntry( h0   , "Mistag binomial uncert" , "LP" );
        leg5->AddEntry( eff_default    , "Mistag Clopper-Pearson uncert" , "LP" );
        // leg5->AddEntry( eff_normal     , "Mistag Normal uncert" , "LP" );
        leg5->AddEntry( eff_wilson     , "Mistag Wilson uncert" , "LP" );
        // leg5->AddEntry( eff_jeffrey    , "Mistag Jeffrey uncert" , "LP" );
        // leg->AddEntry( h1   , "QCD MC (Pythia 8)  " , "LP" );
        leg5->Draw("same");




        string savename7 = "plots_mistag/"+savename+"_teff.pdf";
        c1237->SaveAs(savename7.c_str());
      
        //-----------------
        data_nosubtract_numer   ->SetLineColor(1); 
        data_nosubtract_denom   ->SetLineColor(1); 
     

        ttbar_numer   ->SetLineColor(2); 
        ttbar_denom   ->SetLineColor(2); 
        data_subtract_numer   ->SetLineColor(4); 
        data_subtract_denom   ->SetLineColor(4); 
     

        TLegend * leg2;
        leg2 = new TLegend( 0.57, 0.66,0.84, 0.83);
        leg2->SetBorderSize(0);
        leg2->SetFillColor(0);
        leg2->SetFillStyle(4000);
        leg2->AddEntry( data_nosubtract_numer   , "Data (no subtraction)" , "L" );
        leg2->AddEntry( data_subtract_numer   , "Data (ttbar subtracted)" , "L" );
        leg2->AddEntry( ttbar_numer   , "ttbar" , "L" );
        // leg->AddEntry( h1   , "QCD MC (Pythia 8)  " , "LP" );


        data_nosubtract_numer->GetYaxis()->SetRangeUser( 0.01,data_nosubtract_numer -> GetMaximum()*1.2);
        data_nosubtract_numer->Draw();
        data_subtract_numer  ->Draw("same");
        ttbar_numer          ->Draw("same");
                leg2->Draw("same");
        string savename3 = "plots_mistag/"+savename+"_numer_predivide.pdf";
        c1237->SetLogy();
        c1237->SaveAs(savename3.c_str());

        data_nosubtract_denom->GetYaxis()->SetRangeUser( 0.01,data_nosubtract_denom -> GetMaximum()*1.2);
        data_nosubtract_denom->Draw();
        data_subtract_denom  ->Draw("same");
        ttbar_denom          ->Draw("same");
                leg2->Draw("same");
        string savename4 = "plots_mistag/"+savename+"_denom_predivide.pdf";
        c1237->SaveAs(savename4.c_str());
        c1237->SetLogy(0);


    }
  }
}