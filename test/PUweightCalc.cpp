{
  TFile * F_data_PUnom       = new TFile( "MyDataPileupHistogram.root"                      );
  TFile * F_data_PUup        = new TFile( "MyDataPileupHistogramUP.root"                    );
  TFile * F_data_PUdn        = new TFile( "MyDataPileupHistogramDN.root"                    );
  TFile * F_MC               = new TFile( "tree_RSGluonToTT_M-2000_B2Gv8p4_reader603e.root" );

  TH1D * NPU_data_true       = F_data_PUnom->Get("pileup");
  TH1D * NPU_data_true_MBup  = F_data_PUup->Get("pileup");
  TH1D * NPU_data_true_MBdn  = F_data_PUdn->Get("pileup");
  TH1D * NPU_MC_true         = F_MC->Get("h_NtrueIntPU");

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
  NPU_data_true->GetXaxis()->SetRangeUser(0,30);

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

  // Draw NPU data (MBup and down) and MC
  TCanvas *c1237= new TCanvas("c1237","",200,10,950,700);
  gStyle->SetOptStat(0);
  gStyle->SetHistLineWidth(2);

  NPU_data_true       ->SetLineColor(1);
  NPU_data_true_MBup  ->SetLineColor(3);
  NPU_data_true_MBdn  ->SetLineColor(4);
  NPU_MC_true         ->SetLineColor(2);

  NPU_data_true_MBdn->SetTitle(";N_{PU} true;Number of events");
  NPU_data_true_MBdn->GetXaxis()->SetRangeUser(0,30);

  NPU_data_true_MBdn   ->Draw("HIST");
  NPU_data_true_MBup   ->Draw("HISTsame");
  NPU_data_true        ->Draw("HISTsame");
  NPU_MC_true          ->Draw("HISTsame");

  TLegend * leg = new TLegend(0.6,0.7,0.85,0.84);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetFillStyle( 4050 );
  leg->AddEntry(NPU_data_true      ,"data nominal","L");
  leg->AddEntry(NPU_data_true_MBup ,"data #sigma_{MB} up","L");
  leg->AddEntry(NPU_data_true_MBdn ,"data #sigma_{MB} down","L");
  leg->AddEntry(NPU_MC_true        ,"MC","L");
  leg->Draw("same");

  c1237->RedrawAxis();
  c1237->SaveAs("NPU_updn.pdf");


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

  NPU_data_true->GetXaxis()->SetRangeUser(0,30);
  NPU_data_true->GetYaxis()->SetRangeUser(0,5);

  NPU_data_true      ->Draw();
  NPU_data_true_MBup ->Draw("same");
  NPU_data_true_MBdn ->Draw("same");

  TLegend * leg = new TLegend(0.7,0.6,0.85,0.84);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetFillStyle( 4050 );
  leg->AddEntry(NPU_data_true ,"Nominal","LP");
  leg->AddEntry(NPU_data_true_MBup   ,"#sigma_{MB} up","LP");
  leg->AddEntry(NPU_data_true_MBdn   ,"#sigma_{MB} dn","LP");
  leg->Draw("same");

  c1237->RedrawAxis();
  c1237->SaveAs("PUweight.pdf");

  // Save weight in output file
  TFile *Out;
  Out = new TFile("PUweight20160316.root","RECREATE");
  Out->cd();

  NPU_data_true       ->Write();
  NPU_data_true_MBup  ->Write();
  NPU_data_true_MBdn  ->Write();

  Out->ls();
  Out->Write();
}