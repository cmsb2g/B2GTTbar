void makeSignalPlot(string file, string signal){

  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0000000000); //this clears all the boxes and crap

  TFile *inFile = new TFile( Form("../%s", file.c_str()), "READ");

  cout << "Read in file!" <<endl;

  TH1F *mass1000 = (TH1F *) inFile->Get("btag0__Zprime1000");
  TH1F *mass1250 = (TH1F *) inFile->Get("btag0__Zprime1250");
  TH1F *mass1500 = (TH1F *) inFile->Get("btag0__Zprime1500");
  TH1F *mass2000 = (TH1F *) inFile->Get("btag0__Zprime2000");
  TH1F *mass2500 = (TH1F *) inFile->Get("btag0__Zprime2500");
  TH1F *mass3000 = (TH1F *) inFile->Get("btag0__Zprime3000");
  TH1F *mass3500 = (TH1F *) inFile->Get("btag0__Zprime3500");
  TH1F *mass4000 = (TH1F *) inFile->Get("btag0__Zprime4000");

  cout << "Acquired histograms!" <<endl;

  mass1000->SetLineColor(4);
  mass1250->SetLineColor(kOrange+1);
  mass1500->SetLineColor(2);
  mass2000->SetLineColor(8);
  mass2500->SetLineColor(9);
  mass3000->SetLineColor(6);
  mass3500->SetLineColor(46);
  mass4000->SetLineColor(7);

  mass1000->SetLineWidth(2);
  mass1250->SetLineWidth(2);
  mass1500->SetLineWidth(2);
  mass2000->SetLineWidth(2);
  mass2500->SetLineWidth(2);
  mass3000->SetLineWidth(2);
  mass3500->SetLineWidth(2);
  mass4000->SetLineWidth(2);

  cout << "Set desired style!" <<endl;

  TCanvas* c1 = new TCanvas();

  mass1500->GetYaxis()->SetTitle("Events");
  mass1500->GetXaxis()->SetTitle("t#bar{t} Invariant Mass [GeV]");

  mass1500->Draw("HIST");
  mass1000->Draw("HISTSAME");
  mass1250->Draw("HISTSAME");
  mass2000->Draw("HISTSAME");
  mass2500->Draw("HISTSAME");
  mass3000->Draw("HISTSAME");
  mass3500->Draw("HISTSAME");
  mass4000->Draw("HISTSAME");

  c1->SaveAs( Form("mttbarSpectrum_%s.pdf", signal.c_str()) );
  c1->SaveAs( Form("mttbarSpectrum_%s.root", signal.c_str()) );
}
