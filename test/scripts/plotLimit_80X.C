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

void plotLimit_80X(int signal = 0, bool expectedOnly = 1, string dateLabel = "ApplybTagSFbySubjetPuppiEffTest20170625_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw"){
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
   theory->SetPoint(0,  1000, 4.24671);
   theory->SetPoint(1,  1250, 1.67078);
   theory->SetPoint(2,  1500, 0.74006);
   theory->SetPoint(3,  1750, 0.35479);
   theory->SetPoint(4,  2000, 0.17980);
   theory->SetPoint(5,  2250, 0.09496);
   theory->SetPoint(6,  2500, 0.05178);
   theory->SetPoint(7,  2750, 0.02896);
   theory->SetPoint(8,  3000, 0.01659);
   theory->SetPoint(9,  3250, 0.00961);
   theory->SetPoint(10, 3500, 0.00566);
   theory->SetPoint(11, 3750, 0.00337);
   theory->SetPoint(12, 4000, 0.00203);
 }
 else if (signal == 1){
   theory->SetPoint(0,  1000, 42.24246);
   theory->SetPoint(1,  1250, 17.03858);
   theory->SetPoint(2,  1500, 7.74129);
   theory->SetPoint(3,  1750, 3.82201);
   theory->SetPoint(4,  2000, 2.00723);
   theory->SetPoint(5,  2250, 1.10600);
   theory->SetPoint(6,  2500, 0.63398);
   theory->SetPoint(7,  2750, 0.37621);
   theory->SetPoint(8,  3000, 0.23030);
   theory->SetPoint(9,  3250, 0.14504);
   theory->SetPoint(10, 3500, 0.09387);
   theory->SetPoint(11, 3750, 0.06237);
   theory->SetPoint(12, 4000, 0.04254);
 }
 else if (signal == 2){
   theory->SetPoint(0,  1000, 122.17487);
   theory->SetPoint(1,  1250, 51.51389);
   theory->SetPoint(2,  1500, 24.46373);
   theory->SetPoint(3,  1750, 12.66093);
   theory->SetPoint(4,  2000, 6.99950);
   theory->SetPoint(5,  2250, 4.08126);
   theory->SetPoint(6,  2500, 2.48821);
   theory->SetPoint(7,  2750, 1.57672);
   theory->SetPoint(8,  3000, 1.03387);
   theory->SetPoint(9,  3250, 0.69914);
   theory->SetPoint(10, 3500, 0.48624);
   theory->SetPoint(11, 3750, 0.34698);
   theory->SetPoint(12, 4000, 0.25352); 
 }
 else if (signal == 3){
   theory->SetPoint(0,  1000, 1.3*20.05);
   theory->SetPoint(1,  1250, 1.3*7.92);
   theory->SetPoint(2,  1500, 1.3*3.519);
   //theory->SetPoint(3,  1750, 1.3*);                                   
   theory->SetPoint(3,  2000, 1.3*0.9528);
   //theory->SetPoint(5,  2250, 1.3*);                                   
   theory->SetPoint(4,  2500, 1.3*0.3136);
   //theory->SetPoint(7,  2750, 1.3*);                                   
   theory->SetPoint(5,  3000, 1.3*0.1289);
   //theory->SetPoint(9,  3250, 1.3*);                                   
   theory->SetPoint(6, 3500, 1.3*0.05452);
   //theory->SetPoint(11, 3750, 1.3*);                                   
   theory->SetPoint(7, 4000, 1.3*0.02807);
   theory->SetPoint(8, 4500, 1.3*0.01603);
   theory->SetPoint(9, 5000, 1.3*0.009095);
 }

 string filename = Form("Limits/limits_narrow_%s.txt",dateLabel.c_str());
 if (signal == 1) filename= Form("Limits/limits_wide_%s.txt",dateLabel.c_str());
 if (signal == 2) filename= Form("Limits/limits_extrawide_%s.txt",dateLabel.c_str());
 if (signal == 3) filename= Form("Limits/limits_RSGluon_%s.txt",dateLabel.c_str());

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

  if (expectedOnly) cout << mass << " & " <<roundToSignificantFigures(sf*dn2,2)<<" & "<<roundToSignificantFigures(sf*dn1,2)<<" & textbf{"<<roundToSignificantFigures(sf*exp,2)<< "} & "<<roundToSignificantFigures(sf*up1,2)<<" & "<<roundToSignificantFigures(sf*up2,2)<<" # " << endl;

  else cout << mass << " & textbf{" <<roundToSignificantFigures(sf*obs,2)<< "} & "<<roundToSignificantFigures(sf*dn2,2)<<" & "<<roundToSignificantFigures(sf*dn1,2)<< " & textbf{"<<roundToSignificantFigures(sf*exp,2)<<"} & "<<roundToSignificantFigures(sf*up1,2)<<" & "<<roundToSignificantFigures(sf*up2,2)<<" # " << endl;

  limit_obs->SetPoint(point, mass, obs*sf);
  limit_exp->SetPoint(point, mass, exp*sf);
  band_exp1->SetPoint(point, mass, exp*sf);
  band_exp2->SetPoint(point, mass, exp*sf);
  
  band_exp1->SetPointEYhigh(point, up1*sf - exp*sf);
  band_exp1->SetPointEYlow(point, exp*sf - dn1*sf);
  band_exp2->SetPointEYhigh(point, up2*sf - exp*sf);
  band_exp2->SetPointEYlow(point, exp*sf - dn2*sf);
  point++;

}

double max = 200000.0; //band_exp2->GetHistogram()->GetMaximum()*50;

  TCanvas *canvas = new TCanvas("limit set ZPN","limit set ZPN", 500,500);

  limit_exp->SetMinimum(0.01);
  limit_exp->Draw("AL");
  if (signal == 0){
    limit_exp->GetXaxis()->SetTitle("M_{Z'} [GeV]");
    limit_exp->GetYaxis()->SetTitle("95% CL Limit on #sigma_{Z'} #times B(Z'#rightarrowt#bar{t}) [pb]");
  }
  else if (signal == 1){
    limit_exp->GetXaxis()->SetTitle("M_{Z'} [GeV]");
    limit_exp->GetYaxis()->SetTitle("95% CL Limit on #sigma_{Z'} #times B(Z'#rightarrowt#bar{t}) [pb]");
  }
  else if (signal == 2){
    limit_exp->GetXaxis()->SetTitle("M_{Z'} [GeV]");
    limit_exp->GetYaxis()->SetTitle("95% CL Limit on #sigma_{Z'} #times B(Z'#rightarrowt#bar{t}) [pb]");
  }
  else if (signal == 3){
    limit_exp->GetXaxis()->SetTitle("M_{g_{KK}} [GeV]");
    limit_exp->GetYaxis()->SetTitle("95% CL Limit on #sigma_{g_{KK}} #times B(g_{KK}#rightarrowt#bar{t}) [pb]");
  }
  //limit_exp->GetYaxis()->SetTitleOffset(1.2);
  cout<<limit_exp->GetYaxis()->GetTitleSize()<<endl;
  cout<<limit_exp->GetXaxis()->GetTitleSize()<<endl;
  limit_exp->GetYaxis()->SetRangeUser(0.01,2000);

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
  limit_exp->SetMaximum(max);
  limit_exp->SetMinimum(0.001);
  limit_exp->SetMarkerStyle(20);

  double x1 = 595; 
  double y1 = 1.0;
  double x2 = 905;
  double y2 = 1.0;
  TLine * line = new TLine(x1, y1, x2, y2);
  theory->SetLineColor(2);
  theory->SetLineWidth(2);
  theory->Draw("same");

  
  CMS_lumi(canvas, 4, 10);

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
    canvas->Print(Form("Limits/ZPN_%s_limit.pdf",dateLabel.c_str()));
    //canvas->Print(Form("Limits/ZPN_limit.root");
  }
  else if (signal == 1){
    canvas->Print(Form("Limits/ZPW_%s_limit.pdf",dateLabel.c_str()));
    //canvas->Print(Form("Limits/ZPW_limit.root");
  }
  else if (signal == 2){
    canvas->Print(Form("Limits/ZPXW_%s_limit.pdf",dateLabel.c_str()));
    //canvas->Print(Form("Limits/ZPXW_limit.root");
  }
  else if (signal == 3){
    canvas->Print(Form("Limits/RSG_%s_limit.pdf",dateLabel.c_str()));
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

       if (expectedOnly) cout << mass << " & " <<roundToSignificantFigures(sf*dn2,2)<<" & "<<roundToSignificantFigures(sf*dn1,2)<<" & textbf{"<<roundToSignificantFigures(sf*exp,2)<< "} & "<<roundToSignificantFigures(sf*up1,2)<<" & "<<roundToSignificantFigures(sf*up2,2)<<" # " << endl;

       else cout << mass << " & textbf{" <<roundToSignificantFigures(sf*obs,2)<< "} & "<<roundToSignificantFigures(sf*dn2,2)<<" & "<<roundToSignificantFigures(sf*dn1,2)<< " & textbf{"<<roundToSignificantFigures(sf*exp,2)<<"} & "<<roundToSignificantFigures(sf*up1,2)<<" & "<<roundToSignificantFigures(sf*up2,2)<<" # " << endl;

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




