void plotLimit_wide(string filename){



TGraph * limit_obs = new TGraph();
  TGraph * limit_exp = new TGraph();
  TGraphAsymmErrors * band_exp1 = new TGraphAsymmErrors();
  TGraphAsymmErrors * band_exp2 = new TGraphAsymmErrors();

TGraph *theory = new TGraph();
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


ifstream infile(filename);

gROOT->LoadMacro("CMS_lumi.C");

double mass, exp, obs, up1, up2, dn1, dn2;
int point = 0;

while (!infile.eof()){

  //infile >> mass >> exp >>  dn2 >> up2 >> dn1 >> up1;
  //obs = exp;	

  infile >> mass >> exp >>  dn2 >> up2 >> dn1 >> up1 >> obs;


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

  TCanvas *canvas = new TCanvas("limit set ZPW","limit set ZPW", 500,500);

  limit_exp->SetMinimum(0.01);
  limit_exp->Draw("AL");
  limit_exp->GetXaxis()->SetTitle("M_{Z'} [GeV]");
  limit_exp->GetYaxis()->SetTitle("95 % CL limit on #sigma(Z') [pb]");
  limit_exp->GetYaxis()->SetTitleOffset(1.2);
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

  



  //Legend
  TLegend *l = new TLegend(0.57,0.62,0.88,0.88);
  l->AddEntry(limit_obs,"Observed", "L");
  l->AddEntry(limit_exp,"Expected", "L");
  l->AddEntry(band_exp1,"#pm1 #sigma Exp.", "F");
  l->AddEntry(band_exp2,"#pm2 #sigma Exp.", "F");
  l->AddEntry(theory, "Z' 10% Width (NLO)", "L");
  l->SetFillColor(0);
  l->SetLineColor(0);
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
  CMS_lumi(canvas, 4, 10);

  canvas->Print("ZPW_limit.pdf");
  canvas->Print("ZPW_limit.root");

}




