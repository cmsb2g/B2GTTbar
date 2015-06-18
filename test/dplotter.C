void dplotter(){

  gROOT->Reset();

  TFile *mcFile1 = TFile::Open("TTBarS1.root");
  TFile *mcFile2 = TFile::Open("ZPrime2TeVS1.root");
  TFile *mcFile3 = TFile::Open("ZPrime3TeVS1.root");
  TH1F* histo1;
  TH1F* histo2;
  TH1F* histo3;

  TString Plot = "h_bdiscAK4";
  TLatex *tlx = new TLatex();
  tlx->SetNDC();
  tlx->SetTextFont(42);
  tlx->SetTextSize(0.035);


  TLegend *legend=new TLegend(0.7,0.6,0.8,0.8);
  legend->SetTextFont(52);
  legend->SetTextSize(0.035);
  legend->SetFillStyle(kNone);
  legend->SetBorderSize(0.);
  legend->SetMargin(0.05);
  

    histo1 = (TH1F*) *mcFile1->Get(Plot);
    histo2 = (TH1F*) *mcFile2->Get(Plot);
    histo3 = (TH1F*) *mcFile3->Get(Plot);


  TCanvas *c1= new TCanvas("c1","Plots",900,700);
  c1->Update();
  gPad->Update();
  histo1->GetXaxis()->SetTitle("b discriminator");
  //histo1->GetYaxis()->SetTitle("Number of Interactions");
  //histo1->GetXaxis()->SetLimits(0,80);
  //histo1->GetYaxis()->SetRange(0,0.08);
  histo1->SetLineColor(2);
  Double_t norm = histo1->GetEntries();
  histo1->Scale(1/norm);
  histo1->Draw();

  
  histo2->SetLineColor(4);
  Double_t norm = histo2->GetEntries();
  histo2->Scale(1/norm);
  histo2->Draw("same");

  histo3->SetLineColor(8);
  Double_t norm = histo3->GetEntries();
  histo3->Scale(1/norm);
  histo3->Draw("same");
  tlx->DrawLatex(0.4, 0.92, "SemiLeptonic");


  //histo1->SetMarkerStyle(kFullCircle);
  histo1->SetMarkerColor(2);
  histo1->SetLineColor(2);
  histo1->SetLineWidth(2);
  histo1->SetFillStyle(0);
  histo2->SetMarkerColor(4);
  histo2->SetLineColor(4);
  histo2->SetLineWidth(2);
  histo3->SetMarkerColor(8);
  histo3->SetLineColor(8);
  histo3->SetLineWidth(2);
  legend->AddEntry(histo1,"TT Bar");
  legend->AddEntry(histo2,"ZPrime2Tev");
  legend->AddEntry(histo3,"ZPrime3Tev");
  legend->Draw("same");
  gPad->Modified();
  c1->SetFillColor(0);
  c1->GetFrame()->SetFillColor(0);
  c1->GetFrame()->SetBorderSize(12);
  c1->Modified();
  c1->Print("semileotonicAK4bdisc.png");

}
