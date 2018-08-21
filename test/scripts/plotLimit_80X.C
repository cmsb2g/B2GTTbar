#include <cstdlib>
#include "TClonesArray.h"
#include "TLorentzVector.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TFile.h"
#include "TF1.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include "TChain.h"
#include "TLatex.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TLegend.h"
#include "TColor.h"
#include "TStyle.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TString.h"
#include <vector>
#include <algorithm>
#include "TROOT.h"
#include "tdrstyle.C"
#include "CMS_lumi.C"

double roundToSignificantFigures(double num, int n) {
  if(num == 0) {
    return 0;
  }

  double d = ceil(log10(num < 0 ? -num: num));
  int power = n - (int) d;

  double magnitude = pow(10, power);
  long shifted = round(num*magnitude);
  return shifted/magnitude;
}

void plotLimit_80X(int signal = 0, bool expectedOnly = 0, string dateLabel = "ht950_pt400_WPB_withClosureUncert", string extraText = "", int CMStext = 4){
//signal: 0 = ZPN, 1 = ZPW, 2 = ZPXW, 3 = RSG  

setTDRStyle();

//gROOT->SetStyle("Plain");
gStyle->SetOptStat(0000000000); //this clears all the boxes and crap
gStyle->SetLegendBorderSize(1);

TGraph * limit_obs = new TGraph();
TGraph * limit_exp = new TGraph();
TGraphAsymmErrors * band_exp1 = new TGraphAsymmErrors();
TGraphAsymmErrors * band_exp2 = new TGraphAsymmErrors();

TGraph *theory = new TGraph();
 if (signal == 0){
   /*   theory->SetPoint(0,  1000, 4.24671);
   theory->SetPoint(1,  1.250, 1.67078);
   theory->SetPoint(2,  1.5, 0.74006);
   theory->SetPoint(3,  1.75, 0.35479);
   theory->SetPoint(4,  2000, 0.17980);
   theory->SetPoint(5,  2.250, 0.09496);
   theory->SetPoint(6,  2.5, 0.05178);
   theory->SetPoint(7,  2.75, 0.02896);
   theory->SetPoint(8,  3000, 0.01659);
   theory->SetPoint(9,  3.250, 0.00961);
   theory->SetPoint(10, 3.5, 0.00566);
   theory->SetPoint(11, 3.75, 0.00337);
   theory->SetPoint(12, 4000, 0.00203);*/

   //new theory points from Tomas Jezo
   //theory->SetPoint(0,  .5, 5.83131e+01);
   //theory->SetPoint(0,  .75, 1.36051e+01);
   theory->SetPoint(0,  1, 4.50540e+00);
   theory->SetPoint(1,  1.250, 1.80866e+00);
   theory->SetPoint(2,  1.5, 8.13716e-01);
   theory->SetPoint(3,  1.75, 3.97420e-01);
   theory->SetPoint(4,  2, 2.05510e-01);
   theory->SetPoint(5,  2.250, 1.10890e-01);
   theory->SetPoint(6,  2.5, 6.17038e-02);
   theory->SetPoint(7,  2.75, 3.52336e-02);
   theory->SetPoint(8,  3, 2.05665e-02);
   theory->SetPoint(9,  3.250, 1.21935e-02);
   theory->SetPoint(10, 3.5, 7.34662e-03);
   theory->SetPoint(11, 3.75, 4.46826e-03);
   theory->SetPoint(12, 4, 2.75870e-03);
   theory->SetPoint(13, 4.250, 1.72335e-03);
   theory->SetPoint(14, 4.5, 1.09115e-03);
   theory->SetPoint(15, 4.75, 6.99838e-04);
   theory->SetPoint(16, 5, 4.58135e-04);
   theory->SetPoint(17, 5.250, 3.04742e-04);
   theory->SetPoint(18, 5.5, 2.07506e-04);
   theory->SetPoint(19, 5.75, 1.44911e-04);
   theory->SetPoint(20, 6, 1.03407e-04);
   theory->SetPoint(21, 6.25, 7.60116e-05);
   theory->SetPoint(22, 6.5, 5.71530e-05);
   theory->SetPoint(23, 6.75, 4.42244e-05);
   theory->SetPoint(24, 7, 3.49246e-05);
 }
 else if (signal == 1){
   /*theory->SetPoint(0,  1, 42.24246);
   theory->SetPoint(1,  1.250, 17.03858);
   theory->SetPoint(2,  1.5, 7.74129);
   theory->SetPoint(3,  1.75, 3.82201);
   theory->SetPoint(4,  2, 2.00723);
   theory->SetPoint(5,  2.250, 1.10600);
   theory->SetPoint(6,  2.5, 0.63398);
   theory->SetPoint(7,  2.75, 0.37621);
   theory->SetPoint(8,  3, 0.23030);
   theory->SetPoint(9,  3.250, 0.14504);
   theory->SetPoint(10, 3.5, 0.09387);
   theory->SetPoint(11, 3.75, 0.06237);
   theory->SetPoint(12, 4, 0.04254);*/

   //new theory points from Tomas Jezo
   //theory->SetPoint(0,  .5, 5.36522e+02);
   //theory->SetPoint(0,  .75, 1.31954e+02);
   theory->SetPoint(0,  1, 4.48526e+01);
   theory->SetPoint(1,  1.250, 1.83735e+01);
   theory->SetPoint(2,  1.5, 8.47610e+00);
   theory->SetPoint(3,  1.75, 4.24656e+00);
   theory->SetPoint(4,  2, 2.26215e+00);
   theory->SetPoint(5,  2.250, 1.26395e+00);
   theory->SetPoint(6,  2.5, 7.34314e-01);
   theory->SetPoint(7,  2.75, 4.41032e-01);
   theory->SetPoint(8,  3, 2.72788e-01);
   theory->SetPoint(9,  3.250, 1.73249e-01);
   theory->SetPoint(10, 3.5, 1.12874e-01);
   theory->SetPoint(11, 3.75, 7.53710e-02);
   theory->SetPoint(12, 4, 5.15542e-02);
   theory->SetPoint(13, 4.250, 3.61230e-02);
   theory->SetPoint(14, 4.5, 2.59114e-02);
   theory->SetPoint(15, 4.75, 1.90265e-02);
   theory->SetPoint(16, 5, 1.42839e-02);
   theory->SetPoint(17, 5.250, 1.09496e-02);
   theory->SetPoint(18, 5.5, 8.55804e-03);
   theory->SetPoint(19, 5.75, 6.80722e-03);
   theory->SetPoint(20, 6, 5.50276e-03);
   theory->SetPoint(21, 6.25, 4.50943e-03);
   theory->SetPoint(22, 6.5, 3.74190e-03);
   theory->SetPoint(23, 6.75, 3.13889e-03);
   theory->SetPoint(24, 7, 2.65864e-03);
 }
 else if (signal == 2){
   /*theory->SetPoint(0,  1, 122.17487);
   theory->SetPoint(1,  1.250, 51.51389);
   theory->SetPoint(2,  1.5, 24.46373);
   theory->SetPoint(3,  1.75, 12.66093);
   theory->SetPoint(4,  2, 6.99950);
   theory->SetPoint(5,  2.250, 4.08126);
   theory->SetPoint(6,  2.5, 2.48821);
   theory->SetPoint(7,  2.75, 1.57672);
   theory->SetPoint(8,  3, 1.03387);
   theory->SetPoint(9,  3.250, 0.69914);
   theory->SetPoint(10, 3.5, 0.48624);
   theory->SetPoint(11, 3.75, 0.34698);
   theory->SetPoint(12, 4, 0.25352); */

   //new theory points from Tomas Jezo
   //theory->SetPoint(0,  .5, 1.32811e+03);
   //theory->SetPoint(0,  .75, 3.61926e+02);
   theory->SetPoint(0,  1, 1.29361e+02);
   theory->SetPoint(1,  1.250, 5.52047e+01);
   theory->SetPoint(2,  1.5, 2.65207e+01);
   theory->SetPoint(3,  1.75, 1.38696e+01);
   theory->SetPoint(4,  2, 7.74166e+00);
   theory->SetPoint(5,  2.250, 4.55142e+00);
   theory->SetPoint(6,  2.5, 2.79430e+00);
   theory->SetPoint(7,  2.75, 1.78062e+00);
   theory->SetPoint(8,  3, 1.17252e+00);
   theory->SetPoint(9,  3.250, 7.95149e-01);
   theory->SetPoint(10, 3.5, 5.53916e-01);
   theory->SetPoint(11, 3.75, 3.95485e-01);
   theory->SetPoint(12, 4, 2.88839e-01);
   theory->SetPoint(13, 4.250, 2.15406e-01);
   theory->SetPoint(14, 4.5, 1.63747e-01);
   theory->SetPoint(15, 4.75, 1.26704e-01);
   theory->SetPoint(16, 5, 9.95997e-02);
   theory->SetPoint(17, 5.250, 7.94496e-02);
   theory->SetPoint(18, 5.5, 6.42139e-02);
   theory->SetPoint(19, 5.75, 5.25241e-02);
   theory->SetPoint(20, 6, 4.34250e-02);
   theory->SetPoint(21, 6.25, 3.62486e-02);
   theory->SetPoint(22, 6.5, 3.05223e-02);
   theory->SetPoint(23, 6.75, 2.59064e-02);
   theory->SetPoint(24, 7, 2.21476e-02);
 }
 else if (signal == 3){
   theory->SetPoint(0,  1, 1.3*20.05);
   theory->SetPoint(1,  1.250, 1.3*7.92);
   theory->SetPoint(2,  1.5, 1.3*3.519);
   //theory->SetPoint(3,  1.75, 1.3*);                                   
   theory->SetPoint(3,  2, 1.3*0.9528);
   //theory->SetPoint(5,  2.250, 1.3*);                                   
   theory->SetPoint(4,  2.5, 1.3*0.3136);
   //theory->SetPoint(7,  2.75, 1.3*);                                   
   theory->SetPoint(5,  3, 1.3*0.1289);
   //theory->SetPoint(9,  3.250, 1.3*);                                   
   theory->SetPoint(6, 3.5, 1.3*0.05452);
   //theory->SetPoint(11, 3.75, 1.3*);                                   
   theory->SetPoint(7, 4, 1.3*0.02807);
   theory->SetPoint(8, 4.5, 1.3*0.01603);
   theory->SetPoint(9, 5, 1.3*0.009095);
 }

 string filename = Form("Limits/limits_2016_narrow_%s.txt",dateLabel.c_str());
 if (signal == 1) filename= Form("Limits/limits_2016_wide_%s.txt",dateLabel.c_str());
 if (signal == 2) filename= Form("Limits/limits_2016_extrawide_%s.txt",dateLabel.c_str());
 if (signal == 3) filename= Form("Limits/limits_2016_RSGluon_%s.txt",dateLabel.c_str());

 cout << "Using limit file: " << filename << endl;

ifstream infile(filename);

double mass, exp, obs, up1, up2, dn1, dn2;
int point = 0;

while (!infile.eof()){

  //infile >> mass >> exp >>  dn2 >> up2 >> dn1 >> up1;
  //obs = exp;	

  if (expectedOnly) infile >> mass >> exp >>  dn2 >> up2 >> dn1 >> up1;
  else infile >> mass >> obs >> exp >>  dn2 >> up2 >> dn1 >> up1;

  mass = mass/1000;

  double sf = 1.0;
  if (mass == 2.5) sf = 0.01;
  if (mass == 3) sf = 0.001;
  if (mass == 3.5) sf = 0.0001;
  if (mass == 4) sf = 0.0001;
  if (mass == 4.5) sf = 0.0001;
  if (mass == 5) sf = 0.0001;
  if (mass == 6) sf = 0.0001;
  if (mass == 6.5) sf = 0.0001;
  if (mass == 7) sf = 0.0001;

  if (expectedOnly) cout << mass << " & " <<roundToSignificantFigures(sf*dn2,2)<<" & "<<roundToSignificantFigures(sf*dn1,2)<<" & #textbf{"<<roundToSignificantFigures(sf*exp,2)<< "} & "<<roundToSignificantFigures(sf*up1,2)<<" & "<<roundToSignificantFigures(sf*up2,2)<<" ## " << endl;

  else cout << mass << " & #textbf{" <<roundToSignificantFigures(sf*obs,2)<< "} & "<<roundToSignificantFigures(sf*dn2,2)<<" & "<<roundToSignificantFigures(sf*dn1,2)<< " & #textbf{"<<roundToSignificantFigures(sf*exp,2)<<"} & "<<roundToSignificantFigures(sf*up1,2)<<" & "<<roundToSignificantFigures(sf*up2,2)<<" ## " << endl;

  if (mass >= 1){
    if (!expectedOnly) limit_obs->SetPoint(point, mass, obs*sf);
    limit_exp->SetPoint(point, mass, exp*sf);
    //cout << mass << endl;
    band_exp1->SetPoint(point, mass, exp*sf);
    band_exp2->SetPoint(point, mass, exp*sf);
  
    band_exp1->SetPointEYhigh(point, up1*sf - exp*sf);
    band_exp1->SetPointEYlow(point, exp*sf - dn1*sf);
    band_exp2->SetPointEYhigh(point, up2*sf - exp*sf);
    band_exp2->SetPointEYlow(point, exp*sf - dn2*sf);
  }
  point++;

}

double max = 200000.0; //band_exp2->GetHistogram()->GetMaximum()*50;

  TCanvas *canvas = new TCanvas("limit set ZPN","limit set ZPN", 500,500);

  theory->Draw("AL");
  theory->SetMaximum(max);
  theory->SetMinimum(0.0001);
  limit_exp->Draw("LSAME");

  if (signal == 0){
    theory->GetXaxis()->SetTitle("M_{Z'} [TeV]");
    theory->GetYaxis()->SetTitle("95% CL Limit on #sigma_{Z'} #times B(Z'#rightarrowt#bar{t}) [pb]");
  }
  else if (signal == 1){
    theory->GetXaxis()->SetTitle("M_{Z'} [TeV]");
    theory->GetYaxis()->SetTitle("95% CL Limit on #sigma_{Z'} #times B(Z'#rightarrowt#bar{t}) [pb]");
  }
  else if (signal == 2){
    theory->GetXaxis()->SetTitle("M_{Z'} [TeV]");
    theory->GetYaxis()->SetTitle("95% CL Limit on #sigma_{Z'} #times B(Z'#rightarrowt#bar{t}) [pb]");
  }
  else if (signal == 3){
    theory->GetXaxis()->SetTitle("M_{g_{KK}} [TeV]");
    theory->GetYaxis()->SetTitle("95% CL Limit on #sigma_{g_{KK}} #times B(g_{KK}#rightarrowt#bar{t}) [pb]");
  }
  //theory->GetYaxis()->SetTitleOffset(1.2);
  cout<<theory->GetYaxis()->GetTitleSize()<<endl;
  cout<<theory->GetXaxis()->GetTitleSize()<<endl;
  //theory->GetYaxis()->SetRangeUser(0.01,2000);

  band_exp2->SetFillColor(5);
  band_exp2->SetLineColor(0);
  //band_exp2->SetFillStyle(4000);
  band_exp2->Draw("3same");

  band_exp1->SetFillColor(3);
  band_exp1->SetLineColor(0);
  //band_exp1->SetFillStyle(4000);
  band_exp1->Draw("3same");

  if (!expectedOnly){
    limit_obs->Draw("Lsame");
    limit_obs->SetLineWidth(2);
    limit_obs->SetMarkerSize(1.0);
    limit_obs->SetMarkerStyle(20);
  }
  limit_exp->Draw("Lsame");
  limit_exp->SetLineStyle(2);
  limit_exp->SetLineWidth(2);
  limit_exp->SetMarkerSize(1.0);
  limit_exp->SetMarkerStyle(20);
  canvas->Update();

  theory->SetLineColor(2);
  theory->SetLineWidth(2);
  theory->Draw("same");

  
  CMS_lumi(canvas, CMStext, 10);

  float t = canvas->GetTopMargin();
  float r = canvas->GetRightMargin();

  //Legend
  TLegend *l = new TLegend(0.51,0.63,0.99-r,0.99-t);
  if (!expectedOnly) l->AddEntry(limit_obs,"Observed", "L");
  l->AddEntry(limit_exp,"Expected", "L");
  l->AddEntry(band_exp1,"#pm1 #sigma Exp.", "F");
  l->AddEntry(band_exp2,"#pm2 #sigma Exp.", "F");
  if (signal == 0){
    l->AddEntry(theory, "Z' 1% Width (NLO)", "L");
  }
  else if (signal == 1){
    l->AddEntry(theory, "Z' 10% Width (NLO)", "L");
  }
  else if (signal == 2){
    l->AddEntry(theory, "Z' 30% Width (NLO)", "L");
  }
  else if (signal == 3){
    l->AddEntry(theory, "RS Gluon (LO #times 1.3)", "L");
  }
  l->AddEntry((TObject*)0, extraText.c_str(), "");
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->SetTextSize(0.04);
  l->SetTextFont(42);
  l->Draw();

  //TLatex * label = new TLatex();
  //label->SetNDC();
  //label->DrawLatex(0.2,0.86,"CMS Preliminary, 19.7 fb^{-1}");
  //label->DrawLatex(0.2,0.80,"#sqrt{s} = 8 TeV");
  //label->DrawLatex(0.6,0.80, Form("BR(b'#rightarrow %s) = 1", channel.Data()));
  //label->DrawLatex(0.55,0.80, "BR(b'#rightarrow tW) = 0.5");
  //label->DrawLatex(0.55,0.74, "BR(b'#rightarrow bH) = 0.25");
  //label->DrawLatex(0.55,0.68, "BR(b'#rightarrow bZ) = 0.25");
  //label->DrawLatex(0.2,0.74, lepton.Data());

  canvas->SetLogy(1);

  if (signal == 0){
    canvas->Print(Form("Limits/ZPN_extendedTheoryCurve_%s_limit.pdf",dateLabel.c_str()));
    //canvas->Print(Form("Limits/ZPN_limit.root");
  }
  else if (signal == 1){
    canvas->Print(Form("Limits/ZPW_extendedTheoryCurve_%s_limit.pdf",dateLabel.c_str()));
    //canvas->Print(Form("Limits/ZPW_limit.root");
  }
  else if (signal == 2){
    canvas->Print(Form("Limits/ZPXW_extendedTheoryCurve_%s_limit.pdf",dateLabel.c_str()));
    //canvas->Print(Form("Limits/ZPXW_limit.root");
  }
  else if (signal == 3){
    canvas->Print(Form("Limits/RSG_extendedTheoryCurve_%s_limit.pdf",dateLabel.c_str()));
    //canvas->Print(Form("Limits/RSG_limit.root");
  }
}

void plotLimitCompare_80X(int signal = 0, bool expectedOnly = 1, string dateLabel = "ApplybTagSFbySubjetPuppiEffTest20170625"){
//signal: 0 = ZPN, 1 = ZPW, 2 = ZPXW, 3 = RSG  

setTDRStyle();

//gROOT->SetStyle("Plain");
gStyle->SetOptStat(0000000000); //this clears all the boxes and crap
gStyle->SetLegendBorderSize(1);

 vector <string> tauWPs;
 vector <string> btagWPs;
 vector <Color_t> histColorVec;

 tauWPs.push_back("WPA");
 tauWPs.push_back("WPB");
 tauWPs.push_back("WPC");

 btagWPs.push_back("bL");
 btagWPs.push_back("bM");

 histColorVec.push_back(kBlack);
 histColorVec.push_back(kRed);
 histColorVec.push_back(kGreen+2);
 histColorVec.push_back(kBlue);
 histColorVec.push_back(kMagenta+3);
 histColorVec.push_back(kOrange-3);

 int i_histColorVec = 0;

 TGraph * limit_exp[histColorVec.size()];
 for (unsigned int h = 0; h < histColorVec.size(); h++){
   limit_exp[h] = new TGraph();
 }
     

 double max = 200.0; //band_exp2->GetHistogram()->GetMaximum()*50;
 TCanvas *canvas = new TCanvas("limit set ZPN","limit set ZPN", 500,500);

 //Legend
 CMS_lumi(canvas, 4, 10);

 float t = canvas->GetTopMargin();
 float r = canvas->GetRightMargin();

 TLegend *l = new TLegend(0.51,0.63,0.99-r,0.99-t);
 
 //loop over working points
 for (unsigned int i_tauWPs=0;i_tauWPs<tauWPs.size();i_tauWPs++){
   for (unsigned int i_btagWPs=0;i_btagWPs<btagWPs.size();i_btagWPs++){
     string filename = Form("Limits/limits_narrow_%s_ht950_pt400_%s_alt40_alt260_%s_PUw_TTw.txt",dateLabel.c_str(),tauWPs[i_tauWPs].c_str(),btagWPs[i_btagWPs].c_str());
     if (signal == 1) filename= Form("Limits/limits_wide_%s_ht950_pt400_%s_alt40_alt260_%s_PUw_TTw.txt",dateLabel.c_str(),tauWPs[i_tauWPs].c_str(),btagWPs[i_btagWPs].c_str());
     if (signal == 2) filename= Form("Limits/limits_extrawide_%s_ht950_pt400_%s_alt40_alt260_%s_PUw_TTw.txt",dateLabel.c_str(),tauWPs[i_tauWPs].c_str(),btagWPs[i_btagWPs].c_str());
     if (signal == 3) filename= Form("Limits/limits_RSGluon_%s_ht950_pt400_%s_alt40_alt260_%s_PUw_TTw.txt",dateLabel.c_str(),tauWPs[i_tauWPs].c_str(),btagWPs[i_btagWPs].c_str());

     ifstream infile(filename);

     double mass, exp, obs, up1, up2, dn1, dn2;
     int point = 0;

     while (!infile.eof()){

       //infile >> mass >> exp >>  dn2 >> up2 >> dn1 >> up1;
       //obs = exp;	

       if (expectedOnly) infile >> mass >> exp >>  dn2 >> up2 >> dn1 >> up1;
       else infile >> mass >> obs >> exp >>  dn2 >> up2 >> dn1 >> up1;

       double sf = 1.0;
       if (mass == 2500) sf = 0.01;
       if (mass == 3000) sf = 0.001;
       if (mass == 3500) sf = 0.0001;
       if (mass == 4000) sf = 0.0001;
       if (mass == 4500) sf = 0.0001;
       if (mass == 5000) sf = 0.0001;

       if (expectedOnly) cout << mass << " & " <<roundToSignificantFigures(sf*dn2,2)<<" & "<<roundToSignificantFigures(sf*dn1,2)<<" & #textbf{"<<roundToSignificantFigures(sf*exp,2)<< "} & "<<roundToSignificantFigures(sf*up1,2)<<" & "<<roundToSignificantFigures(sf*up2,2)<<" ## " << endl;

       else cout << mass << " & #textbf{" <<roundToSignificantFigures(sf*obs,2)<< "} & "<<roundToSignificantFigures(sf*dn2,2)<<" & "<<roundToSignificantFigures(sf*dn1,2)<< " & #textbf{"<<roundToSignificantFigures(sf*exp,2)<<"} & "<<roundToSignificantFigures(sf*up1,2)<<" & "<<roundToSignificantFigures(sf*up2,2)<<" ## " << endl;

       limit_exp[i_histColorVec]->SetPoint(point, mass, exp*sf);
       point++;

     }
     
     limit_exp[i_histColorVec]->SetLineWidth(2);
     limit_exp[i_histColorVec]->SetMaximum(max);
     limit_exp[i_histColorVec]->SetMinimum(0.001);
     limit_exp[i_histColorVec]->SetLineColor(histColorVec[i_histColorVec]);

     cout << i_histColorVec << endl;

     if (i_histColorVec==0){
       limit_exp[i_histColorVec]->Draw("AL");

       if (signal == 0){
	 limit_exp[i_histColorVec]->GetXaxis()->SetTitle("M_{Z'} [GeV]");
	 limit_exp[i_histColorVec]->GetYaxis()->SetTitle("95% CL Limit on #sigma_{Z'} #times B(Z'#rightarrowt#bar{t}) [pb]");
       }
       else if (signal == 1){
	 limit_exp[i_histColorVec]->GetXaxis()->SetTitle("M_{Z'} [GeV]");
	 limit_exp[i_histColorVec]->GetYaxis()->SetTitle("95% CL Limit on #sigma_{Z'} #times B(Z'#rightarrowt#bar{t}) [pb]");
       }
       else if (signal == 2){
	 limit_exp[i_histColorVec]->GetXaxis()->SetTitle("M_{Z'} [GeV]");
	 limit_exp[i_histColorVec]->GetYaxis()->SetTitle("95% CL Limit on #sigma_{Z'} #times B(Z'#rightarrowt#bar{t}) [pb]");
       }
       else if (signal == 3){
	 limit_exp[i_histColorVec]->GetXaxis()->SetTitle("M_{g_{KK}} [GeV]");
	 limit_exp[i_histColorVec]->GetYaxis()->SetTitle("95% CL Limit on #sigma_{g_{KK}} #times B(g_{KK}#rightarrowt#bar{t}) [pb]");
       }
       //limit_exp[i_histColorVec]->GetYaxis()->SetTitleOffset(1.2);
       cout<<limit_exp[i_histColorVec]->GetYaxis()->GetTitleSize()<<endl;
       cout<<limit_exp[i_histColorVec]->GetXaxis()->GetTitleSize()<<endl;
       limit_exp[i_histColorVec]->GetYaxis()->SetRangeUser(0.01,2000);
     }//end if histColorVec is 0
     else limit_exp[i_histColorVec]->Draw("Lsame");

     l->AddEntry(limit_exp[i_histColorVec],Form("Expected: %s, %s",tauWPs[i_tauWPs].c_str(),btagWPs[i_btagWPs].c_str()), "L");
     i_histColorVec++;

   }//end btag WP loop
 }//end tau32 WP loop

 if (signal == 0){
   l->AddEntry((TObject*)0, "Z' 1% Width (NLO)", "");
 }
 else if (signal == 1){
   l->AddEntry((TObject*)0, "Z' 10% Width (NLO)", "");
 }
 else if (signal == 2){
   l->AddEntry((TObject*)0, "Z' 30% Width (NLO)", "");
 }
 else if (signal == 3){
   l->AddEntry((TObject*)0, "RS Gluon (LO #times 1.3)", "");
 }

 l->SetFillColor(0);
 l->SetLineColor(0);
 l->SetTextSize(0.04);
 l->SetTextFont(42);
 l->Draw();

 CMS_lumi(canvas, 4, 10);

  //TLatex * label = new TLatex();
  //label->SetNDC();
  //label->DrawLatex(0.2,0.86,"CMS Preliminary, 19.7 fb^{-1}");
  //label->DrawLatex(0.2,0.80,"#sqrt{s} = 8 TeV");
  //label->DrawLatex(0.6,0.80, Form("BR(b'#rightarrow %s) = 1", channel.Data()));
  //label->DrawLatex(0.55,0.80, "BR(b'#rightarrow tW) = 0.5");
  //label->DrawLatex(0.55,0.74, "BR(b'#rightarrow bH) = 0.25");
  //label->DrawLatex(0.55,0.68, "BR(b'#rightarrow bZ) = 0.25");
  //label->DrawLatex(0.2,0.74, lepton.Data());

  canvas->SetLogy(1);

  if (signal == 0){
    canvas->Print(Form("Limits/ZPN_%s_ht950_pt400_alt40_alt260_PUw_TTw_limitsCompareWPs.pdf",dateLabel.c_str()));
    //canvas->Print(Form("Limits/ZPN_limit.root");
  }
  else if (signal == 1){
    canvas->Print(Form("Limits/ZPW_%s_ht950_pt400_alt40_alt260_PUw_TTw_limitsCompareWPs.pdf",dateLabel.c_str()));
    //canvas->Print(Form("Limits/ZPW_limit.root");
  }
  else if (signal == 2){
    canvas->Print(Form("Limits/ZPXW_%s_ht950_pt400_alt40_alt260_PUw_TTw_limitsCompareWPs.pdf",dateLabel.c_str()));
    //canvas->Print(Form("Limits/ZPXW_limit.root");
  }
  else if (signal == 3){
    canvas->Print(Form("Limits/RSG_%s_ht950_pt400_alt40_alt260_PUw_TTw_limitsCompareWPs.pdf",dateLabel.c_str()));
    //canvas->Print(Form("Limits/RSG_limit.root");
  }
}

void plotLimitCompare_btagCats_80X(int signal = 0, bool expectedOnly = 1, string dateLabel = "withClosureUncert"){
//signal: 0 = ZPN, 1 = ZPW, 2 = ZPXW, 3 = RSG  

setTDRStyle();

//gROOT->SetStyle("Plain");
gStyle->SetOptStat(0000000000); //this clears all the boxes and crap
gStyle->SetLegendBorderSize(1);

 vector <string> btagCats;
 vector <Color_t> histColorVec;

 btagCats.push_back("btag0");
 btagCats.push_back("btag1");
 btagCats.push_back("btag2");
 btagCats.push_back("btag3");
 btagCats.push_back("btag4");
 btagCats.push_back("btag5");

 histColorVec.push_back(kBlack);
 histColorVec.push_back(kRed);
 histColorVec.push_back(kGreen+2);
 histColorVec.push_back(kBlue);
 histColorVec.push_back(kMagenta+3);
 histColorVec.push_back(kOrange-3);

 int i_histColorVec = 0;

 TGraph * limit_exp[histColorVec.size()];
 for (unsigned int h = 0; h < histColorVec.size(); h++){
   limit_exp[h] = new TGraph();
 }
 
 double max = 200.0; //band_exp2->GetHistogram()->GetMaximum()*50;
 TCanvas *canvas = new TCanvas("limit set ZPN","limit set ZPN", 500,500);

 //Legend
 CMS_lumi(canvas, 4, 10);

 float t = canvas->GetTopMargin();
 float r = canvas->GetRightMargin();

 TLegend *l = new TLegend(0.51,0.63,0.99-r,0.99-t);
 
 //loop over working points
 for (unsigned int i_btagCats=0;i_btagCats<btagCats.size();i_btagCats++){
   string filename = Form("Limits/limits_2016_narrow_ht950_pt400_WPB_%s_%s.txt",dateLabel.c_str(),btagCats[i_btagCats].c_str());
   if (signal == 1) filename= Form("Limits/limits_2016_wide_ht950_pt400_WPB_%s_%s.txt",dateLabel.c_str(),btagCats[i_btagCats].c_str());
   if (signal == 2) filename= Form("Limits/limits_2016_extrawide_ht950_pt400_WPB_%s_%s.txt",dateLabel.c_str(),btagCats[i_btagCats].c_str());
   if (signal == 3) filename= Form("Limits/limits_2016_RSGluon_ht950_pt400_WPB_%s_%s.txt",dateLabel.c_str(),btagCats[i_btagCats].c_str());

   ifstream infile(filename);

   double mass, exp, obs, up1, up2, dn1, dn2;
   int point = 0;

   while (!infile.eof()){

     //infile >> mass >> exp >>  dn2 >> up2 >> dn1 >> up1;
     //obs = exp;	

     //if (expectedOnly || mass > 2.0) infile >> mass >> exp >>  dn2 >> up2 >> dn1 >> up1;
     infile >> mass >> obs >> exp >>  dn2 >> up2 >> dn1 >> up1;

     double sf = 1.0;
     if (mass == 2500) sf = 0.01;
     if (mass == 3000) sf = 0.001;
     if (mass == 3500) sf = 0.0001;
     if (mass == 4000) sf = 0.0001;
     if (mass == 4500) sf = 0.0001;
     if (mass == 5000) sf = 0.0001;

     if (expectedOnly || mass > 2.0) cout << mass << " & " <<roundToSignificantFigures(sf*dn2,2)<<" & "<<roundToSignificantFigures(sf*dn1,2)<<" & #textbf{"<<roundToSignificantFigures(sf*exp,2)<< "} & "<<roundToSignificantFigures(sf*up1,2)<<" & "<<roundToSignificantFigures(sf*up2,2)<<" ## " << endl;

     else cout << mass << " & #textbf{" <<roundToSignificantFigures(sf*obs,2)<< "} & "<<roundToSignificantFigures(sf*dn2,2)<<" & "<<roundToSignificantFigures(sf*dn1,2)<< " & #textbf{"<<roundToSignificantFigures(sf*exp,2)<<"} & "<<roundToSignificantFigures(sf*up1,2)<<" & "<<roundToSignificantFigures(sf*up2,2)<<" ## " << endl;

     limit_exp[i_histColorVec]->SetPoint(point, mass, exp*sf);
     point++;

   }
     
   limit_exp[i_histColorVec]->SetLineWidth(2);
   limit_exp[i_histColorVec]->SetMaximum(max);
   limit_exp[i_histColorVec]->SetMinimum(0.001);
   limit_exp[i_histColorVec]->SetLineColor(histColorVec[i_histColorVec]);

   cout << i_histColorVec << endl;

   if (i_histColorVec==0){
     limit_exp[i_histColorVec]->Draw("AL");

     if (signal == 0){
       limit_exp[i_histColorVec]->GetXaxis()->SetTitle("M_{Z'} [GeV]");
       limit_exp[i_histColorVec]->GetYaxis()->SetTitle("95% CL Limit on #sigma_{Z'} #times B(Z'#rightarrowt#bar{t}) [pb]");
     }
     else if (signal == 1){
       limit_exp[i_histColorVec]->GetXaxis()->SetTitle("M_{Z'} [GeV]");
       limit_exp[i_histColorVec]->GetYaxis()->SetTitle("95% CL Limit on #sigma_{Z'} #times B(Z'#rightarrowt#bar{t}) [pb]");
     }
     else if (signal == 2){
       limit_exp[i_histColorVec]->GetXaxis()->SetTitle("M_{Z'} [GeV]");
       limit_exp[i_histColorVec]->GetYaxis()->SetTitle("95% CL Limit on #sigma_{Z'} #times B(Z'#rightarrowt#bar{t}) [pb]");
     }
     else if (signal == 3){
       limit_exp[i_histColorVec]->GetXaxis()->SetTitle("M_{g_{KK}} [GeV]");
       limit_exp[i_histColorVec]->GetYaxis()->SetTitle("95% CL Limit on #sigma_{g_{KK}} #times B(g_{KK}#rightarrowt#bar{t}) [pb]");
     }
     //limit_exp[i_histColorVec]->GetYaxis()->SetTitleOffset(1.2);
     cout<<limit_exp[i_histColorVec]->GetYaxis()->GetTitleSize()<<endl;
     cout<<limit_exp[i_histColorVec]->GetXaxis()->GetTitleSize()<<endl;
     limit_exp[i_histColorVec]->GetYaxis()->SetRangeUser(0.01,2000);
   }//end if histColorVec is 0
   else limit_exp[i_histColorVec]->Draw("Lsame");

   l->AddEntry(limit_exp[i_histColorVec],Form("Expected: %s", btagCats[i_btagCats].c_str()), "L");
   i_histColorVec++;

 }//end btag category loop

 if (signal == 0){
   l->AddEntry((TObject*)0, "Z' 1% Width (NLO)", "");
 }
 else if (signal == 1){
   l->AddEntry((TObject*)0, "Z' 10% Width (NLO)", "");
 }
 else if (signal == 2){
   l->AddEntry((TObject*)0, "Z' 30% Width (NLO)", "");
 }
 else if (signal == 3){
   l->AddEntry((TObject*)0, "RS Gluon (LO #times 1.3)", "");
 }

 l->SetFillColor(0);
 l->SetLineColor(0);
 l->SetTextSize(0.04);
 l->SetTextFont(42);
 l->Draw();

 CMS_lumi(canvas, 4, 10);

  //TLatex * label = new TLatex();
  //label->SetNDC();
  //label->DrawLatex(0.2,0.86,"CMS Preliminary, 19.7 fb^{-1}");
  //label->DrawLatex(0.2,0.80,"#sqrt{s} = 8 TeV");
  //label->DrawLatex(0.6,0.80, Form("BR(b'#rightarrow %s) = 1", channel.Data()));
  //label->DrawLatex(0.55,0.80, "BR(b'#rightarrow tW) = 0.5");
  //label->DrawLatex(0.55,0.74, "BR(b'#rightarrow bH) = 0.25");
  //label->DrawLatex(0.55,0.68, "BR(b'#rightarrow bZ) = 0.25");
  //label->DrawLatex(0.2,0.74, lepton.Data());

  canvas->SetLogy(1);

  if (signal == 0){
    canvas->Print(Form("Limits/ZPN_%s_ht950_pt400_alt40_alt260_PUw_TTw_limitsComparebTagCats.pdf",dateLabel.c_str()));
    //canvas->Print(Form("Limits/ZPN_limit.root");
  }
  else if (signal == 1){
    canvas->Print(Form("Limits/ZPW_%s_ht950_pt400_alt40_alt260_PUw_TTw_limitsComparebTagCats.pdf",dateLabel.c_str()));
    //canvas->Print(Form("Limits/ZPW_limit.root");
  }
  else if (signal == 2){
    canvas->Print(Form("Limits/ZPXW_%s_ht950_pt400_alt40_alt260_PUw_TTw_limitsComparebTagCats.pdf",dateLabel.c_str()));
    //canvas->Print(Form("Limits/ZPXW_limit.root");
  }
  else if (signal == 3){
    canvas->Print(Form("Limits/RSG_%s_ht950_pt400_alt40_alt260_PUw_TTw_limitsComparebTagCats.pdf",dateLabel.c_str()));
    //canvas->Print(Form("Limits/RSG_limit.root");
  }
}




