#include<TROOT.h>
#include<TFile.h>
#include<vector>
#include<TChain.h>
#include<TPad.h>
#include<TCanvas.h>
#include<TBranch.h>
#include<TH1.h>
#include<TH2.h>
#include<TProfile.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<TLegend.h>
#include<TMath.h>
#include<TStyle.h>
#include<TDirectoryFile.h>
#include <ctime>

void draw(string variable, string x_axis_name, string cut, string outlabel, int nBins, float min, float max, double xInfo, double yInfoTop, int extra_cut_label = 0){
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0000000000);
  gStyle->SetTitleBorderSize(0);

  //cout<<"Calculating weights!"<<endl;

  ////dataset weights
  //double luminosity  = 2460;//pb^-1
  
  //double sigma_zpw1000 = 1;//normalize to 1 pb 
  /* double sigma_zpn2000 = 1;//normalize to 1 pb
  double sigma_zpw2000 = 1;//normalize to 1 pb
  double sigma_ttbar = 502.2;//pb, from mcm
  double sigma_qcd =  89731000000;//pb, from mcm*/

  //double Ngen_zpnw1000 = ;//from DAS 
  /*double Ngen_zpn2000 = 202573;//from DAS
  double Ngen_zpw2000 = 103854;//from DAS
  double Ngen_ttbar = 4992231;//from DAS
  double Ngen_qcd = 9824352;//from DAS*/

  //double w_zpw1000 = (luminosity * sigma_zpw1000)/(Ngen_zpw1000);
  /*double w_zpn2000 = (luminosity * sigma_zpn2000)/(Ngen_zpn2000);
  double w_zpw2000 = (luminosity * sigma_zpw2000)/(Ngen_zpw2000);
  double w_ttbar = (luminosity * sigma_ttbar)/(Ngen_ttbar);
  double w_qcd = (luminosity * sigma_qcd)/(Ngen_qcd);*/

  //cout<<"Summing QCD event weights!"<<endl;

  //summing qcd event weights
  /*TChain *chain = new TChain("b2gntuple/tree");
  chain->Add("../output/B2Gtree_QCD_Pt-15TTo7000_TuneZ2star-Flat_RunIISpring15DR74-Asympt50ns_74xV2.root");

  cout<<"TChain created!"<<endl;

  int n_entries = chain->GetEntries();
  TBranch *b_evWeight_corr;
  float evWeight_corr;
  float evWeight_total = 0;//summing event weights

  chain->SetBranchAddress("evWeight_corr", &evWeight_corr, &b_evWeight_corr);

  cout<<"Branch address set!"<<endl;

  //summing event weights
  for(int i = 0; i<n_entries;i++){
    //b_evWeight_corr->SetAddress(b_evWeight_corr);
    //b_evWeight_corr->GetEntry(i);

    chain->GetEntry(i,0);

    evWeight_total += evWeight_corr;
  }

  cout <<"The sum of QCD event weights: "<<evWeight_total<<endl;*/

  //double evWeight_total = 216764;//sum of QCD event weights
  //double w_qcd = (luminosity * sigma_qcd)/(evWeight_total); 
  

  //cout<<"Narrow 2 TeV Z' Weight: "<<w_zpn2000<<endl;
  //cout<<"Wide 2 TeV Z' Weight: "<<w_zpw2000<<endl;
  //cout<<"t#bar{t} Weight: "<<w_ttbar<<endl;
  //cout<<"QCD Weight: "<<w_qcd<<endl;

  cout<<"Reading in files!"<<endl;

  ////reading in files
  TFile *zpw1000F = new TFile("../output/B2Gtree_B2Gtree_ZprimeToTT_M-1000_W-100_JEC0.root"); 
  TFile *zpw1000_JECupF = new TFile("../output/B2Gtree_B2Gtree_ZprimeToTT_M-1000_W-100_JECup.root");
  TFile *zpw1000_JECdownF = new TFile("../output/B2Gtree_B2Gtree_ZprimeToTT_M-1000_W-100_JECdown.root"); 
  TFile *zpw1000_JERupF = new TFile("../output/B2Gtree_B2Gtree_ZprimeToTT_M-1000_W-100_JERup.root");
  TFile *zpw1000_JERdownF = new TFile("../output/B2Gtree_B2Gtree_ZprimeToTT_M-1000_W-100_JERdown.root");

  //TFile *zpn1000 = new TFile("histo_Zp1.root");
  //TFile *zpn3000 = new TFile("B2Gtree_ZPrimeToTTJets_M3000GeV_W30GeV.root");
  //TFile *zpn2000F = new TFile("../output/B2Gtree_ZPrimeToTT_M-2000_W-20_RunIISpring15DR74-Asympt50ns_74xV2.root");
  //TFile *zpw2000F = new TFile("../output/B2Gtree_ZPrimeToTT_M-2000_W-200_RunIISpring15DR74-Asympt50ns_74xV2.root");
  //TFile *zpn4000 = new TFile("histo_1000.root");
  //TFile *ttbarF = new TFile("../output/B2Gtree_TTJets-2-_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt50ns_74xV2.root");
  //TFile *qcdF = new TFile("../output/B2Gtree_QCD_Pt-15TTo7000_TuneZ2star-Flat_RunIISpring15DR74-Asympt50ns_74xV2.root");
  //TFile *dataF = new TFile("../output/B2Gtree_JetHT_Run2015B_B2GAnaFW_v74x_V5p1_DATA.root");
  cout<<"Treeeeeeeessss!"<<endl;
  
  //TFile*dataF = new TFile("/eos/uscms/store/user/camclean/JetHT/ZprimeAnaTrees_Run2015D-PromptReco-v3_Sep25_v74x_V7_25ns_2015_10_05_histo_DATA.root");

  TTree *zpw1000tree = (TTree *) zpw1000F->Get("b2gntuple/tree_had"); 
  TTree *zpw1000_JECuptree = (TTree *) zpw1000_JECupF->Get("b2gntuple/tree_had"); 
  TTree *zpw1000_JECdowntree = (TTree *) zpw1000_JECdownF->Get("b2gntuple/tree_had"); 
  TTree *zpw1000_JERuptree = (TTree *) zpw1000_JERupF->Get("b2gntuple/tree_had"); 
  TTree *zpw1000_JERdowntree = (TTree *) zpw1000_JERdownF->Get("b2gntuple/tree_had"); 
  //TTree *zpn1000tree = (TTree *) zpn1000->Get("b2gntuple/tree");
  /*TTree *zpn2000tree = (TTree *) zpn2000F->Get("b2gntuple/tree");
  TTree *zpw2000tree = (TTree *) zpw2000F->Get("b2gntuple/tree");
  TTree *ttbartree = (TTree *) ttbarF->Get("b2gntuple/tree");
  TTree *qcdtree = (TTree *) qcdF->Get("b2gntuple/tree");*/
  //TTree *datatree = (TTree *) dataF->Get("b2gntuple/tree");
 
  cout<<"Definining histograms"<<endl;

  ////drawing histograms
  TH1F *zpw1000H = new TH1F("zpw1000H", "zpw1000H", nBins, min, max);
  TH1F *zpw1000_JECupH = new TH1F("zpw1000_JECupH", "zpw1000_JECupH", nBins, min, max);
  TH1F *zpw1000_JECdownH = new TH1F("zpw1000_JECdownH", "zpw1000_JECdownH", nBins, min, max);
  TH1F *zpw1000_JERupH = new TH1F("zpw1000_JERupH", "zpw1000_JERupH", nBins, min, max);
  TH1F *zpw1000_JERdownH = new TH1F("zpw1000_JERdownH", "zpw1000_JERdownH", nBins, min, max);
  //TH1F *zpn1H = new TH1F("zpn1H", "zpn1H", nBins, min, max);
  /*TH1F *zpn2000H = new TH1F("zpn2000H", "zpn2000H", nBins, min, max);
  TH1F *zpw2000H = new TH1F("zpw2000H", "zpw2000H", nBins, min, max);
  //TH1F *zpn4H = new TH1F("zpn4H", "zpn4H", nBins, min, max);
  TH1F *ttbarH = new TH1F("ttbarH", "ttbarH", nBins, min, max);
  TH1F *qcdH = new TH1F("qcdH", "qcdH", nBins, min, max);*/
  //TH1F *dataH = new TH1F("dataH", "dataH", nBins, min, max);

  cout<<"Drawing histograms"<<endl;
  zpw1000tree->Draw( Form("%s>>zpw1000H", variable.c_str()), Form("%s", cut.c_str()), "goff");
  zpw1000_JECuptree->Draw( Form("%s>>zpw1000_JECupH", variable.c_str()), Form("%s", cut.c_str()), "goff");
  zpw1000_JECdowntree->Draw( Form("%s>>zpw1000_JECdownH", variable.c_str()), Form("%s", cut.c_str()), "goff");
  zpw1000_JERuptree->Draw( Form("%s>>zpw1000_JERupH", variable.c_str()), Form("%s", cut.c_str()), "goff");
  zpw1000_JERdowntree->Draw( Form("%s>>zpw1000_JERdownH", variable.c_str()), Form("%s", cut.c_str()), "goff");
  /*zpn2000tree->Draw( Form("%s>>zpn2000H", variable.c_str()), Form("%s", cut.c_str()), "goff");
  zpw2000tree->Draw( Form("%s>>zpw2000H", variable.c_str()), Form("%s", cut.c_str()), "goff");
  ttbartree->Draw( Form("%s>>ttbarH", variable.c_str()), Form("%s", cut.c_str()), "goff");
  qcdtree->Draw( Form("%s>>qcdH", variable.c_str()), Form("(%s)*evWeight_corr", cut.c_str()), "hist");*/
  //datatree->Draw( Form("%s>>dataH", variable.c_str()), Form("%s", cut.c_str()), "ep");

  //cout<<"Scaling histograms"<<endl;

  //Scaling histograms with weights
  /*zpn2000H->Scale(w_zpn2000);
  zpw2000H->Scale(w_zpw2000);
  ttbarH->Scale(w_ttbar);
  qcdH->Scale(w_qcd);*/

  //Cloning MC background histograms for ratio plot
  /*TH1F *mcH = (TH1F*) ttbarH->Clone();
    mcH->Add(qcdH);*/

  cout<<"Setting histogram properties!"<<endl;

  //Drawing histograms
  //dataH->SetMarkerStyle(20);

  zpw1000H->SetLineWidth(2);
  zpw1000_JECupH->SetLineWidth(2);
  zpw1000_JECdownH->SetLineWidth(2);
  zpw1000_JERupH->SetLineWidth(2);
  zpw1000_JERdownH->SetLineWidth(2);
  /*zpn2000H->SetLineWidth(2);
  //zpn1H->SetLineWidth(2);
  zpw2000H->SetLineWidth(2);
  //zpn4H->SetLineWidth(2);*/

  zpw1000_JECupH->SetLineColor(kRed);
  zpw1000_JECdownH->SetLineColor(kBlue);
  zpw1000_JERupH->SetLineColor(kOrange);
  zpw1000_JERdownH->SetLineColor(kGreen+1);
  /*zpn1H->SetLineColor(kBlack);
  zpn2000H->SetLineColor(kBlue);
  zpw2000H->SetLineColor(kViolet);
  //zpn4H->SetLineColor(kGreen+1);

  ttbarH->SetFillColor(kRed);
  //ttbarH->SetLineColor(kRed);

  qcdH->SetFillColor(kOrange);
  //qcdH->SetLineColor(kGreen);
   
  //cout<<"THStack!"<<endl;

  THStack *hs = new THStack();
  hs->Add(ttbarH);
  hs->Add(qcdH);*/

  cout<<"Creating canvas"<<endl;

  TCanvas *c = new TCanvas();
  cout<<"Drawing all the things!"<<endl;

  //Data/MC comparison plot will be in pad1
  /*TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad

  hs->Draw("hist");
  zpn2000H->Draw("SAME");
  zpw2000H->Draw("SAME");
  dataH->Draw("epSAME");*/

  zpw1000H->Draw("hist");
  zpw1000_JECupH->Draw("SAME");
  zpw1000_JECdownH->Draw("SAME");
  zpw1000_JERupH->Draw("SAME");
  zpw1000_JERdownH->Draw("SAME");
  
  //dataH->Draw("ep");

  /*hs->SetMinimum(0.001);
  hs->GetXaxis()->SetTitle(x_axis_name.c_str());
  hs->GetYaxis()->SetTitle("Fraction of Events / Bin");
  hs->GetYaxis()->SetTitleOffset(1.2);
  hs->SetTitle("");*/

  zpw1000H->SetMinimum(0.001);
  zpw1000H->GetXaxis()->SetTitle(x_axis_name.c_str());
  zpw1000H->GetYaxis()->SetTitle("Fraction of Events / Bin");
  zpw1000H->GetYaxis()->SetTitleOffset(1.2);
  zpw1000H->SetTitle("");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  /*hs->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( -5, 20, -5, 220, 20,220,510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();*/

  cout<<"Creating Legend!"<<endl;

  TLegend *leg = new TLegend(0.65, 0.69, 0.89, 0.89);
  leg->SetLineColor(0);
  leg->SetFillColor(0);
  //leg->AddEntry(dataH, "Data", "p");
  leg->AddEntry(zpw1000H, "1 TeV Z' #rightarrow t#bar{t}, #Gamma/m = 10%", "l");
  leg->AddEntry(zpw1000_JECupH, "1 TeV Z' #rightarrow t#bar{t}, #Gamma/m = 10%; JEC Up", "l");
  leg->AddEntry(zpw1000_JECdownH, "1 TeV Z' #rightarrow t#bar{t}, #Gamma/m = 10%; JEC Down", "l");
  leg->AddEntry(zpw1000_JERupH, "1 TeV Z' #rightarrow t#bar{t}, #Gamma/m = 10%; JER Up", "l");
  leg->AddEntry(zpw1000_JERdownH, "1 TeV Z' #rightarrow t#bar{t}, #Gamma/m = 10%; JER Down", "l");
  //leg->AddEntry(zpn1H, "1 TeV Z'", "l");
  /*leg->AddEntry(zpn2000H, "2 TeV Z' #rightarrow t#bar{t}, #Gamma/m = 1%", "l");
  leg->AddEntry(zpw2000H, "2 TeV Z' #rightarrow t#bar{t}, #Gamma/m = 10%", "l");
  //leg->AddEntry(zpn4H, "m_{#chi} = 1000 GeV", "l");
  leg->AddEntry(ttbarH, "t#bar{t}", "f");
  leg->AddEntry(qcdH, "QCD", "f");*/
  leg->Draw();

  //CMS and cut labels
  TLatex *tlx = new TLatex();
  tlx->SetNDC();
  tlx->SetTextFont(42);
  tlx->SetTextSize(0.057);
  tlx->DrawLatex(0.131, 0.905, "CMS Preliminary #sqrt{s}=13 TeV"); //, 150.02 pb^{-1}");
  tlx->SetTextSize(0.025);

  double yInfo2 = yInfoTop-0.042;
  double yInfo3 = yInfo2-0.042;
  double yInfo4 = yInfo3-0.042;
  double yInfo5 = yInfo4-0.042;
  double yInfo6 = yInfo5-0.042;
  double yInfo7 = yInfo6-0.042;
  double yInfo8 = yInfo7-0.042;
  double yInfo9 = yInfo8-0.042;

  tlx->DrawLatex(xInfo, yInfoTop, "#bf{CMS V2H Top Tagger}"); // same for AK4 and AK8
  tlx->DrawLatex(xInfo, yInfo2 , "#bf{Madgraph}"); // same for AK4 and AK8
  tlx->DrawLatex(xInfo, yInfo3, "#bf{AK R= 0.8}"); // 0.8 or 0.4 for AK8 and AK4
  tlx->DrawLatex(xInfo, yInfo4, "#bf{|#eta| < 2.4 }");  // same for AK4 and AK8
  tlx->DrawLatex(xInfo, yInfo5, "#bf{P_{T} > 400 GeV}");// > 400 for AK8 and > 30 for AK4
  tlx->DrawLatex(xInfo, yInfo6, "#bf{25 ns}");  // change with 25 or 50 ns bunchcrossings

  //labeling analysis cuts
  if ((extra_cut_label&1) == 1){
    tlx->DrawLatex(xInfo, yInfo7, "#bf{110 GeV < Soft Drop Mass < 210 GeV}");  // only when softdrop cut applied      change with histo
    if ((extra_cut_label&2) == 2){
      tlx->DrawLatex(xInfo, yInfo8, "#bf{#tau_{3}/#tau_{2} < 0.5}");
    }//tau32 0.5 loop
    else if ((extra_cut_label&4) == 4){
      tlx->DrawLatex(xInfo, yInfo8, "#bf{#tau_{3}/#tau_{2} < 0.61}");
      if ((extra_cut_label&8) == 8){
	tlx->DrawLatex(xInfo, yInfo9, "#bf{Soft Drop Subjet b-tag > 0.762}");
      }//b-tag 0.762 loop
      else if ((extra_cut_label&16) == 16){
	tlx->DrawLatex(xInfo, yInfo9, "#bf{1 subjet b-tag}");
      }//1 b-tag loop
      else if ((extra_cut_label&32) == 32){
	tlx->DrawLatex(xInfo, yInfo9, "#bf{2 subjet b-tags}");
      }//2 b-tags loop
    }//tau32 0.61 loop
    else if ((extra_cut_label&8) == 8){
      tlx->DrawLatex(xInfo, yInfo8, "#bf{CMSTT Subjet b-tag > 0.762}");
    }//b-tag 0.762 loop
  }//softdrop mass loop
  else if ((extra_cut_label&2) == 2){
      tlx->DrawLatex(xInfo, yInfo7, "#bf{#tau_{3}/#tau_{2} < 0.5}");
    }//tau32 0.5 loop
  else if ((extra_cut_label&4) == 4){
    tlx->DrawLatex(xInfo, yInfo7, "#bf{#tau_{3}/#tau_{2} < 0.61}");
    if ((extra_cut_label&8) == 8){
      tlx->DrawLatex(xInfo, yInfo8, "#bf{CMSTT Subjet b-tag > 0.762}");
    }//b-tag 0.762 loop
  }//tau32 0.61 loop

  //Ratio plot will be in pad2
  /*c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad

  // Define the ratio plot
  TH1F *hratio = (TH1F*)dataH->Clone("hratio");
  hratio->SetLineColor(kBlack);
  hratio->SetMinimum(0.0);  // Define Y ..
  hratio->SetMaximum(1.5); // .. range
  hratio->Sumw2();
  hratio->SetStats(0);      // No statistics on lower plot
  hratio->Divide(mcH);
  hratio->SetMarkerStyle(21);
  hratio->Draw("ep");       // Draw the ratio plot

  // Ratio plot (hratio) settings
  hratio->SetTitle(""); // Remove the ratio title

  // Y axis ratio plot settings
  hratio->GetYaxis()->SetTitle("ratio data/MC ");
  hratio->GetYaxis()->SetNdivisions(505);
  hratio->GetYaxis()->SetTitleSize(20);
  hratio->GetYaxis()->SetTitleFont(43);
  hratio->GetYaxis()->SetTitleOffset(1.55);
  hratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  hratio->GetYaxis()->SetLabelSize(15);

  // X axis ratio plot settings
  hratio->GetXaxis()->SetTitleSize(20);
  hratio->GetXaxis()->SetTitleFont(43);
  hratio->GetXaxis()->SetTitleOffset(4.);
  hratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  hratio->GetXaxis()->SetLabelSize(15);
  */
  //c->SetLogy();
  

  cout<<"Getting date for output file!"<<endl;

  // Get date for output file naming                                                            
  time_t now = time(0);
  tm *ltm = localtime(&now);
  int mon = 1 + ltm->tm_mon;
  string month = to_string(mon) ;
  string day = to_string(ltm->tm_mday) ;
  string year = to_string(1900 + ltm->tm_year) ;

  cout<<"Saving plots!"<<endl;

  c->Print(Form("Histos/StackedAllHadHistos_%s_25ns_%s_%s_%s.pdf",outlabel.c_str(),day.c_str(),month.c_str(),year.c_str()));
  c->Print(Form("Histos/StackedAllHadHistos_%s_25ns_%s_%s_%s.png",outlabel.c_str(),day.c_str(),month.c_str(),year.c_str()));
  c->Print(Form("Histos/StackedAllHadHistos_%s_25ns_%s_%s_%s.root",outlabel.c_str(),day.c_str(),month.c_str(),year.c_str()));
}

