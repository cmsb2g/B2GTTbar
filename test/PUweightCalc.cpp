// root [0] .L PUweightCalc.cpp++
// root [1] run()

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <TTree.h>
#include <TH1F.h>
#include <sstream>
#include <TFile.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TF1.h>
#include <TROOT.h>
#include <TColor.h>
#include <TStyle.h>
#include <TCanvas.h>

void run(){


  TFile * F_data_PUnom       = new TFile( "MyDataPileupHistogram_FinalJSON_LatestPileupJSON_Xsec69200.root"                    );
  TFile * F_data_PUup        = new TFile( "MyDataPileupHistogram_FinalJSON_LatestPileupJSON_Xsec72383.root"                    );
  TFile * F_data_PUdn        = new TFile( "MyDataPileupHistogram_FinalJSON_LatestPileupJSON_Xsec66017.root"                    );
  TFile * F_MC               = new TFile( "b2gtreeV5prelim_ZprimeToTT_M-2000_W-200_MCRunIISummer16MiniAODv2_PUMoriond17.root"  );

  TH1D * NPU_data_true       = (TH1D*) F_data_PUnom->Get("pileup");
  TH1D * NPU_data_true_MBup  = (TH1D*) F_data_PUup->Get("pileup");
  TH1D * NPU_data_true_MBdn  = (TH1D*) F_data_PUdn->Get("pileup");
  TH1D * NPU_MC_true         = (TH1D*) F_MC->Get("ana/h_NtrueIntPU");

  NPU_data_true       ->Sumw2();
  NPU_data_true_MBup  ->Sumw2();
  NPU_data_true_MBdn  ->Sumw2();
  NPU_MC_true         ->Sumw2();

  // scale to have area 1
  NPU_data_true       ->Scale( 1.0 / NPU_data_true       ->Integral() );
  NPU_data_true_MBup  ->Scale( 1.0 / NPU_data_true_MBup  ->Integral() );
  NPU_data_true_MBdn  ->Scale( 1.0 / NPU_data_true_MBdn  ->Integral() );
  NPU_MC_true         ->Scale( 1.0 / NPU_MC_true         ->Integral() );

  // Draw NPU data and MC
  TCanvas *c1237= new TCanvas("c1237","",200,10,950,700);
  gStyle->SetOptStat(0);
  gStyle->SetHistLineWidth(2);

  NPU_data_true ->SetLineColor(1);
  NPU_MC_true   ->SetLineColor(2);

  NPU_data_true ->SetMarkerColor(1);
  NPU_MC_true   ->SetMarkerColor(2);

  NPU_data_true ->SetMarkerStyle(20);
  NPU_MC_true   ->SetMarkerStyle(21);

  NPU_data_true->SetTitle(";N_{PU} true;Number of events");
  NPU_data_true->GetXaxis()->SetRangeUser(0,80);

  NPU_data_true ->Draw();
  NPU_MC_true   ->Draw("same");

  TLegend * leg = new TLegend(0.7,0.7,0.85,0.84);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetFillStyle( 4050 );
  leg->AddEntry(NPU_data_true ,"data","LP");
  leg->AddEntry(NPU_MC_true   ,"MC","LP");
  leg->Draw("same");

  c1237->RedrawAxis();
  c1237->SaveAs("NPU.pdf");
  c1237->SetLogy();
  c1237->SaveAs("NPUlog.pdf");
  c1237->SetLogy(0);

  // Draw NPU data (MBup and down) and MC
  // TCanvas *c1237= new TCanvas("c1237","",200,10,950,700);
  gStyle->SetOptStat(0);
  gStyle->SetHistLineWidth(2);

  NPU_data_true       ->SetLineColor(1);
  NPU_data_true_MBup  ->SetLineColor(3);
  NPU_data_true_MBdn  ->SetLineColor(4);
  NPU_MC_true         ->SetLineColor(2);

  NPU_data_true_MBdn->SetTitle(";N_{PU} true;Number of events");
  NPU_data_true_MBdn->GetXaxis()->SetRangeUser(0,80);

  NPU_data_true_MBdn   ->Draw("HIST");
  NPU_data_true_MBup   ->Draw("HISTsame");
  NPU_data_true        ->Draw("HISTsame");
  NPU_MC_true          ->Draw("HISTsame");

  TLegend * leg2 = new TLegend(0.6,0.7,0.85,0.84);
  leg2->SetBorderSize(0);
  leg2->SetFillColor(0);
  leg2->SetFillStyle( 4050 );
  leg2->AddEntry(NPU_data_true      ,"data nominal","L");
  leg2->AddEntry(NPU_data_true_MBup ,"data #sigma_{MB} up","L");
  leg2->AddEntry(NPU_data_true_MBdn ,"data #sigma_{MB} down","L");
  leg2->AddEntry(NPU_MC_true        ,"MC","L");
  leg2->Draw("same");

  c1237->RedrawAxis();
  c1237->SaveAs("NPU_updn.pdf");
  c1237->SetLogy();
  c1237->SaveAs("NPU_updn_log.pdf");
  c1237->SetLogy(0);

  // calculate weight = data / MC
  NPU_data_true       ->Divide( NPU_MC_true );
  NPU_data_true_MBup  ->Divide( NPU_MC_true );
  NPU_data_true_MBdn  ->Divide( NPU_MC_true );

  NPU_data_true      ->SetName( "PUweight_true"      ) ;
  NPU_data_true_MBup ->SetName( "PUweight_true_MBup" ) ;
  NPU_data_true_MBdn ->SetName( "PUweight_true_MBdn" ) ;

  NPU_data_true      ->SetTitle( ";N_{PU} true; Weight"      ) ;

  // Draw weight 
  NPU_data_true      ->SetLineColor(1);
  NPU_data_true_MBup ->SetLineColor(2);
  NPU_data_true_MBdn ->SetLineColor(3);

  NPU_data_true      ->SetMarkerColor(1);
  NPU_data_true_MBup ->SetMarkerColor(2);
  NPU_data_true_MBdn ->SetMarkerColor(3);

  NPU_data_true      ->SetMarkerStyle(20);
  NPU_data_true_MBup ->SetMarkerStyle(20);
  NPU_data_true_MBdn ->SetMarkerStyle(20);

  NPU_data_true     ->GetXaxis()->SetRangeUser(0,80);
  NPU_data_true_MBup->GetXaxis()->SetRangeUser(0,80);
  NPU_data_true_MBdn->GetXaxis()->SetRangeUser(0,80);
  NPU_data_true->GetYaxis()->SetRangeUser(0,5);

  NPU_data_true      ->Draw();
  NPU_data_true_MBup ->Draw("same");
  NPU_data_true_MBdn ->Draw("same");

  TLegend * leg3 = new TLegend(0.7,0.6,0.85,0.84);
  leg3->SetBorderSize(0);
  leg3->SetFillColor(0);
  leg3->SetFillStyle( 4050 );
  leg3->AddEntry(NPU_data_true ,"Nominal","LP");
  leg3->AddEntry(NPU_data_true_MBup   ,"#sigma_{MB} up","LP");
  leg3->AddEntry(NPU_data_true_MBdn   ,"#sigma_{MB} dn","LP");
  leg3->Draw("same");

  c1237->RedrawAxis();
  c1237->SaveAs("PUweight.pdf");
  c1237->SetLogy();
  c1237->SaveAs("PUweightlog.pdf");
  c1237->SetLogy(0);

  // Save weight in output file
  TFile *Out;
  Out = new TFile("PUweight_FinalJSON2016_PileupJSONFeb2017_Xsec69200nominal_MCRunIISummer16MiniAODv2_PUMoriond17.root","RECREATE");
  Out->cd();

  NPU_data_true       ->Write();
  NPU_data_true_MBup  ->Write();
  NPU_data_true_MBdn  ->Write();

  Out->ls();
  Out->Write();
}