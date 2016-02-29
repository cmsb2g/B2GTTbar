
void plot(TString histname, TString qcd_histname, TString label, int rebin, int dy = -1, int btag =-1){


gROOT->LoadMacro("CMS_lumi.C");

TFile *dataF = new TFile("outBkgdEst_JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65_022316_nom.root", "READ");
TFile *ttbarF = new TFile("outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all_022316_nom.root", "READ");



TH1F *dataH = (TH1F *) dataF->Get(histname);
TH1F *qcdH = (TH1F *) dataF->Get(qcd_histname);
TH1F *ttbarH = (TH1F *) ttbarF->Get(histname);
TH1F *ttbarMisH = (TH1F *) ttbarF->Get(qcd_histname);


dataH->Sumw2();
ttbarH->Sumw2();
qcdH->Sumw2();
ttbarMisH->Sumw2();

ttbarH->Add(ttbarMisH, -1);

ttbarH->SetLineColor(kRed);
ttbarH->SetFillColor(kRed);
qcdH->SetLineColor(kYellow);
qcdH->SetFillColor(kYellow);


dataH->Rebin(rebin);
qcdH->Rebin(rebin);
ttbarH->Rebin(rebin);



float lumi = 2592.3;
float NNLOf = 0.942;



ttbarH->Scale( 831.76 * NNLOf * lumi  / 96834559. );

TCanvas *c1 = new TCanvas("c1", "c1",0,0,600,500);
  c1->Range(0,0,1,1);
c1->Draw();

TPad *c1_1 = new TPad("c1_1", "newpad",0.01,0.01,0.99,0.32);
  c1_1->Draw();
TPad *c1_2 = new TPad("c1_2", "newpad",0.01,0.33,0.99,0.99);
  c1_2->Draw(); 

c1->cd();
  c1_2->cd();
  c1_2->SetTopMargin(0.1);
  c1_2->SetBottomMargin(0.01);
  c1_2->SetRightMargin(0.05);
  c1_2->SetLeftMargin(0.1);
  c1_2->SetFillStyle(0);


THStack *stack = new THStack("stack", "stack");
stack->Add(ttbarH);
stack->Add(qcdH);

TH1F *totalH = ttbarH->Clone("totalH");
totalH->Sumw2();

totalH->Add(qcdH);

dataH->SetMaximum(dataH->GetMaximum()*1.8);
dataH->GetYaxis()->SetTitle("Events");
dataH->GetYaxis()->SetTitleSize(0.07);
dataH->GetYaxis()->SetTitleOffset(0.65);
dataH->GetYaxis()->SetLabelSize(0.05);
dataH->Draw("E");
stack->Draw("hist same");
dataH->SetMarkerStyle(21);
dataH->SetMarkerSize(0.75);
dataH->SetLineColor(kBlack);
dataH->Draw("E same");

TLegend *leg = new TLegend(0.6, 0.5, 0.89, 0.89);
leg->AddEntry(dataH, "Data", "pl");
leg->AddEntry(qcdH, "Non-Top Multijet", "f");
leg->AddEntry(ttbarH, "SM Top Pair", "f");
if (dy == 1) leg->AddEntry( dataH, "|#Delta y| < 1.0", "");
if (dy == 2) leg->AddEntry( dataH, "|#Delta y| > 1.0", "");
if (btag == 0) leg->AddEntry( dataH, "0 b-tags", "");
if (btag == 1) leg->AddEntry( dataH, "1 b-tags", "");
if (btag == 2) leg->AddEntry( dataH, "2 b-tags", "");
if (btag == -1) leg->AddEntry(dataH, "Inclusive", "");


leg->SetFillColor(0);
leg->SetLineColor(0);
leg->Draw("same");


CMS_lumi(c1_2, 4, 10);




TH1F *ratioH = new TH1F();
ratioH->Sumw2();
ratioH = (TH1F*) dataH->Clone("ratio");
ratioH->Divide(totalH);

c1_1->cd();
  c1_1->SetTopMargin(0.01);
  c1_1->SetBottomMargin(0.3);
  c1_1->SetRightMargin(0.05);
  c1_1->SetLeftMargin(0.1);
  c1_1->SetFillStyle(0);


ratioH->GetYaxis()->SetRangeUser(0.,2.);
ratioH->GetYaxis()->SetTitle("Data / BG Ratio");
ratioH->GetYaxis()->SetTitleOffset(0.4);
ratioH->GetYaxis()->SetTitleSize(0.11);
ratioH->GetXaxis()->SetLabelSize(0.11);
ratioH->GetXaxis()->SetTitleSize(0.11);
ratioH->GetXaxis()->SetTitle(label);
ratioH->Draw("E");



TF1 *line = new TF1("line", "1", -5000, 10000);
line->SetLineColor(kBlack);
line->Draw("same");

gPad->RedrawAxis();

c1->SaveAs( histname + ".pdf"  );
c1_2->cd();


gPad->SetLogy(1);
dataH->SetMaximum( 100* dataH->GetMaximum() );
dataH->SetMinimum(0.1);
gPad->RedrawAxis();

c1->SaveAs( histname + "_log.pdf"  );







}


