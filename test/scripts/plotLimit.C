#include "tdrstyle.C"
#include "CMS_lumi.C"

void plotLimit(int signal = 0){
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
 }

 string filename = "Limits/limits_narrow.txt";
 if (signal == 1) filename= "Limits/limits_wide.txt";
 if (signal == 2) filename= "Limits/limits_extrawide.txt";
 if (signal == 3) filename= "Limits/limits_rsgluon.txt";

ifstream infile(filename);

double mass, exp, obs, up1, up2, dn1, dn2;
int point = 0;

while (!infile.eof()){

  //infile >> mass >> exp >>  dn2 >> up2 >> dn1 >> up1;
  //obs = exp;	

  infile >> mass >> obs >> exp >>  dn2 >> up2 >> dn1 >> up1;


  cout << mass << " & " << obs << " & " << exp << " & " << "["<<dn1<<", "<<up1<<"] & ["<<dn2<<", "<<up2<<"] \\" << endl;



  double sf = 1.0;
  if (mass == 2500) sf = 0.01;
  if (mass == 3000) sf = 0.001;
  if (mass == 3500) sf = 0.0001;
  if (mass == 4000) sf = 0.0001;


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
    limit_exp->GetXaxis()->SetTitle("M_{Z'} [GeV]");
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

  limit_obs->Draw("Lsame");
  limit_obs->SetLineWidth(2);
  limit_obs->SetMarkerSize(1.0);
  limit_obs->SetMarkerStyle(20);
   
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
  l->AddEntry(limit_obs,"Observed", "L");
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
    canvas->Print("Limits/ZPN_limit.pdf");
    canvas->Print("Limits/ZPN_limit.root");
  }
  else if (signal == 1){
    canvas->Print("Limits/ZPW_limit.pdf");
    canvas->Print("Limits/ZPW_limit.root");
  }
  else if (signal == 2){
    canvas->Print("Limits/ZPXW_limit.pdf");
    canvas->Print("Limits/ZPXW_limit.root");
  }
  else if (signal == 3){
    canvas->Print("Limits/RSG_limit.pdf");
    canvas->Print("Limits/RSG_limit.root");
  }
}




