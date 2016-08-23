#include "tdrstyle.C"
#include "CMS_lumi.C"

void plotLimit(int signal = 0){
//signal: 0 = ZPN, 1 = ZPW, 2 = ZPXW, 3 = RSG  

setTDRStyle();

//gROOT->SetStyle("Plain");
gStyle->SetOptStat(0000000000); //this clears all the boxes and crap
gStyle->SetLegendBorderSize(1);

TGraph * limit_obs = new TGraph(3);
TGraph * limit_exp = new TGraph(3);
TGraphAsymmErrors * band_exp1 = new TGraphAsymmErrors();
TGraphAsymmErrors * band_exp2 = new TGraphAsymmErrors();

TGraph * limit_obs_2 = new TGraph(3);
TGraph * limit_exp_2 = new TGraph(3);
TGraphAsymmErrors * band_exp1_2 = new TGraphAsymmErrors();
TGraphAsymmErrors * band_exp2_2 = new TGraphAsymmErrors();
TGraph * limit_obs_3 = new TGraph(3);
TGraph * limit_exp_3 = new TGraph(3);
TGraphAsymmErrors * band_exp1_3 = new TGraphAsymmErrors();
TGraphAsymmErrors * band_exp2_3 = new TGraphAsymmErrors();
TGraph * limit_obs_4 = new TGraph(3);
TGraph * limit_exp_4 = new TGraph(3);
TGraphAsymmErrors * band_exp1_4 = new TGraphAsymmErrors();
TGraphAsymmErrors * band_exp2_4 = new TGraphAsymmErrors();
TGraph *theory = new TGraph(3);
TGraph *theory2 = new TGraph(3);
TGraph *theory3 = new TGraph(3);
TGraph *theory4 = new TGraph(3);

   theory->SetPoint(0,  0.01, 4.24671);

   theory->SetPoint(1,  0.1, 42.24246);

   theory->SetPoint(2,  0.3, 122.17487);
   theory2->SetPoint(0,  0.01, 0.17980);
   theory2->SetPoint(1,  0.1, 2.00723);
   theory2->SetPoint(2,  0.3, 6.99950);
   theory3->SetPoint(0, 0.01, 0.01659*0.1);
   theory3->SetPoint(1,  0.1, 0.23030*0.1);
   theory3->SetPoint(2,  0.3, 1.03387*0.1);
   theory4->SetPoint(0, 0.01, 0.00203*0.01);
   theory4->SetPoint(1, 0.1, 0.04254*0.01);
   theory4->SetPoint(2, 0.3, 0.25352*0.01); 

 string filename = "Limits/comb_width_1TeV.txt";
 if (signal == 1) filename= "Limits/comb_width_2TeV.txt";
 if (signal == 2) filename= "Limits/comb_width_3TeV.txt";
 if (signal == 3) filename= "Limits/comb_width_4TeV.txt";

ifstream infile(filename);

double mass, exp, obs, up1, up2, dn1, dn2;
int point = 0;

while (!infile.eof()){

  //infile >> mass >> exp >>  dn2 >> up2 >> dn1 >> up1;
  //obs = exp;	

  infile >> mass >> obs >> exp >>  dn2 >> up2 >> dn1 >> up1;

 
  double sf = 1.0;
  cout.precision(3);
  //cout << mass << " & " << obs << " & " << exp << " & " << "["<<dn1<<", "<<up1<<"] & ["<<dn2<<", "<<up2<<"] \\" << endl;
  cout << mass << " & \\textbf{" << obs*sf << "} & " << dn2*sf << " & " << dn1*sf << " & \\textbf{" << exp*sf << "} & " << up1*sf << " & " << up2*sf <<  " \\\\" << endl;


  //if (mass == 2500) sf = 0.01;
  //if (mass == 3000) sf = 0.001;
  //if (mass == 3500) sf = 0.0001;
  //if (mass == 4000) sf = 0.0001;


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

ifstream infile2 ("Limits/comb_width_2TeV.txt");
point = 0;
while (!infile2.eof()){

  //infile >> mass >> exp >>  dn2 >> up2 >> dn1 >> up1;
  //obs = exp;	

  infile2 >> mass >> obs >> exp >>  dn2 >> up2 >> dn1 >> up1;

 
  double sf = 1.0;
  cout.precision(3);
  //cout << mass << " & " << obs << " & " << exp << " & " << "["<<dn1<<", "<<up1<<"] & ["<<dn2<<", "<<up2<<"] \\" << endl;
  cout << mass << " & \\textbf{" << obs*sf << "} & " << dn2*sf << " & " << dn1*sf << " & \\textbf{" << exp*sf << "} & " << up1*sf << " & " << up2*sf <<  " \\\\" << endl;


  //if (mass == 2500) sf = 0.01;
  //if (mass == 3000) sf = 0.001;
  //if (mass == 3500) sf = 0.0001;
  //if (mass == 4000) sf = 0.0001;


  limit_obs_2->SetPoint(point, mass, obs*sf);
  limit_exp_2->SetPoint(point, mass, exp*sf);
  band_exp1_2->SetPoint(point, mass, exp*sf);
  band_exp2_2->SetPoint(point, mass, exp*sf);
  
  band_exp1_2->SetPointEYhigh(point, up1*sf - exp*sf);
  band_exp1_2->SetPointEYlow(point, exp*sf - dn1*sf);
  band_exp2_2->SetPointEYhigh(point, up2*sf - exp*sf);
  band_exp2_2->SetPointEYlow(point, exp*sf - dn2*sf);
  point++;

}

ifstream infile3 ("Limits/comb_width_3TeV.txt");
point = 0;

while (!infile3.eof()){

  //infile >> mass >> exp >>  dn2 >> up2 >> dn1 >> up1;
  //obs = exp;	

  infile3 >> mass >> obs >> exp >>  dn2 >> up2 >> dn1 >> up1;

 
  double sf = 0.1;
  cout.precision(3);
  //cout << mass << " & " << obs << " & " << exp << " & " << "["<<dn1<<", "<<up1<<"] & ["<<dn2<<", "<<up2<<"] \\" << endl;
  cout << mass << " & \\textbf{" << obs*sf << "} & " << dn2*sf << " & " << dn1*sf << " & \\textbf{" << exp*sf << "} & " << up1*sf << " & " << up2*sf <<  " \\\\" << endl;


  //if (mass == 2500) sf = 0.01;
  //if (mass == 3000) sf = 0.001;
  //if (mass == 3500) sf = 0.0001;
  //if (mass == 4000) sf = 0.0001;


  limit_obs_3->SetPoint(point, mass, obs*sf);
  limit_exp_3->SetPoint(point, mass, exp*sf);
  band_exp1_3->SetPoint(point, mass, exp*sf);
  band_exp2_3->SetPoint(point, mass, exp*sf);

  band_exp1_3->SetPointEYhigh(point, up1*sf - exp*sf);
  band_exp1_3->SetPointEYlow(point, exp*sf - dn1*sf);
  band_exp2_3->SetPointEYhigh(point, up2*sf - exp*sf);
  band_exp2_3->SetPointEYlow(point, exp*sf - dn2*sf);
  point++;

}

ifstream infile4 ("Limits/comb_width_4TeV.txt");
point = 0;

while (!infile4.eof()){

  //infile >> mass >> exp >>  dn2 >> up2 >> dn1 >> up1;
  //obs = exp;	

  infile4 >> mass >> obs >> exp >>  dn2 >> up2 >> dn1 >> up1;

 
  double sf = 0.01;
  cout.precision(3);
  //cout << mass << " & " << obs << " & " << exp << " & " << "["<<dn1<<", "<<up1<<"] & ["<<dn2<<", "<<up2<<"] \\" << endl;
  cout << mass << " & \\textbf{" << obs*sf << "} & " << dn2*sf << " & " << dn1*sf << " & \\textbf{" << exp*sf << "} & " << up1*sf << " & " << up2*sf <<  " \\\\" << endl;


  //if (mass == 2500) sf = 0.01;
  //if (mass == 3000) sf = 0.001;
  //if (mass == 3500) sf = 0.0001;
  //if (mass == 4000) sf = 0.0001;


  limit_obs_4->SetPoint(point, mass, obs*sf);
  limit_exp_4->SetPoint(point, mass, exp*sf);
  band_exp1_4->SetPoint(point, mass, exp*sf);
  band_exp2_4->SetPoint(point, mass, exp*sf);
  band_exp1_4->SetPointEYhigh(point, up1*sf - exp*sf);
  band_exp1_4->SetPointEYlow(point, exp*sf - dn1*sf);
  band_exp2_4->SetPointEYhigh(point, up2*sf - exp*sf);
  band_exp2_4->SetPointEYlow(point, exp*sf - dn2*sf);
  point++;

}





double max = 200000.0; //band_exp2->GetHistogram()->GetMaximum()*50;

  TCanvas *canvas = new TCanvas("limit set ZPN","limit set ZPN", 500,500);

  limit_exp->SetMinimum(0.00001);
  limit_exp->GetXaxis()->SetLabelSize(0.05);
  limit_exp->GetYaxis()->SetLabelSize(0.05);
  limit_exp->Draw("AL");
  if (signal == 0){
    limit_exp->GetXaxis()->SetTitle("#Gamma_{Z'} / M_{Z'}");
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
  limit_exp->GetYaxis()->SetRangeUser(0.00001,2000);


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
  limit_exp->SetMinimum(0.000001);
  limit_exp->SetMarkerStyle(20);
  

  band_exp2_2->SetFillColor(5);
  band_exp2_2->SetLineColor(0);
  band_exp1_2->SetFillColor(3);
  band_exp1_2->SetLineColor(0);
  band_exp2_3->SetFillColor(5);
  band_exp2_3->SetLineColor(0);
  band_exp1_3->SetFillColor(3);
  band_exp1_3->SetLineColor(0);
  band_exp2_4->SetFillColor(5);
  band_exp2_4->SetLineColor(0);
  band_exp1_4->SetFillColor(3);
  band_exp1_4->SetLineColor(0);
  band_exp2_2->Draw("3same");
  band_exp1_2->Draw("3same");
  limit_obs_2->Draw("Lsame");
  limit_obs_2->SetLineWidth(2);
  limit_obs_2->SetMarkerSize(1.0);
  limit_obs_2->SetMarkerStyle(20);
  band_exp2_3->Draw("3same");
  band_exp1_3->Draw("3same");
  limit_obs_3->Draw("Lsame");
  limit_obs_3->SetLineWidth(2);
  limit_obs_3->SetMarkerSize(1.0);
  limit_obs_3->SetMarkerStyle(20);
  band_exp2_4->Draw("3same");
  band_exp1_4->Draw("3same");
  limit_obs_4->Draw("Lsame");
  limit_obs_4->SetLineWidth(2);
  limit_obs_4->SetMarkerSize(1.0);
  limit_obs_4->SetMarkerStyle(20);

  limit_exp_2->Draw("L same");
  limit_exp_2->SetLineStyle(2);
  limit_exp_2->SetLineWidth(2);
  limit_exp_2->SetMarkerSize(1.0);
  limit_exp_3->Draw("L same");
  limit_exp_3->SetLineStyle(2);
  limit_exp_3->SetLineWidth(2);
  limit_exp_3->SetMarkerSize(1.0);
  limit_exp_4->Draw("L same");
  limit_exp_4->SetLineStyle(2);
  limit_exp_4->SetLineWidth(2);
  limit_exp_4->SetMarkerSize(1.0);








    canvas->RedrawAxis();

  double x1 = 595; 
  double y1 = 1.0;
  double x2 = 905;
  double y2 = 1.0;
  TLine * line = new TLine(x1, y1, x2, y2);
  theory->SetLineColor(2);
  theory->SetLineWidth(2);
  theory->Draw("same");
	theory2->SetLineColor(kBlue);
	theory2->SetLineWidth(2);
	theory2->Draw("same");
	theory3->SetLineColor(kMagenta);
	theory3->SetLineWidth(2);
	theory3->Draw("same");
	theory4->SetLineColor(kCyan);
	theory4->SetLineWidth(2);
	theory4->Draw("same");

  CMS_lumi(canvas, 4, 10);

  float t = canvas->GetTopMargin();
  float r = canvas->GetRightMargin();

  //Legend
  TLegend *l = new TLegend(0.51,0.63,0.99-r,0.99-t);
  l->AddEntry(limit_obs,"Observed", "L");
  l->AddEntry(limit_exp,"Expected", "L");
  l->AddEntry(band_exp1,"#pm1 #sigma Exp.", "F");
  l->AddEntry(band_exp2,"#pm2 #sigma Exp.", "F");
    l->AddEntry(theory, "Z' 1 TeV (NLO)", "L");
    l->AddEntry(theory2, "Z' 2 TeV (NLO)", "L");
    l->AddEntry(theory3, "Z' 3 TeV (NLO x 0.1)", "L");
    l->AddEntry(theory4, "Z' 4 TeV (NLO x 0.01)", "L");
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
  canvas->SetLogx(1);
  canvas->SetTickx(1);
  canvas->SetTicky(1);


  if (signal == 0){
    canvas->Print("Limits/comb_ZPN_limit.pdf");
    canvas->Print("Limits/comb_ZPN_limit.root");
  }
  else if (signal == 1){
    canvas->Print("Limits/comb_ZPW_limit.pdf");
    canvas->Print("Limits/comb_ZPW_limit.root");
  }
  else if (signal == 2){
    canvas->Print("Limits/comb_ZPXW_limit.pdf");
    canvas->Print("Limits/comb_ZPXW_limit.root");
  }
  else if (signal == 3){
    canvas->Print("Limits/comb_RSG_limit.pdf");
    canvas->Print("Limits/comb_RSG_limit.root");
  }
}




