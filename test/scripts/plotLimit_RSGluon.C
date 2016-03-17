void plotLimit_RSGluon(){



TGraph * limit_obs = new TGraph();
  TGraph * limit_exp = new TGraph();
  TGraphAsymmErrors * band_exp1 = new TGraphAsymmErrors();
  TGraphAsymmErrors * band_exp2 = new TGraphAsymmErrors();

  TGraph *theory = new TGraph();
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

ifstream infile("limits_RSGluon_2016.txt");

gROOT->LoadMacro("CMS_lumi.C");

double mass, exp, obs, up1, up2, dn1, dn2;
int point = 0;

while (!infile.eof()){

  //infile >> mass >> exp >>  dn2 >> up2 >> dn1 >> up1;
  //obs = exp;	

  infile >> mass >> exp >>  dn2 >> up2 >> dn1 >> up1 >> obs;


  cout << mass << " & " << obs << " & " << exp << " & " << "["<<dn1<<", "<<up1<<"] & ["<<dn2<<", "<<up2<<"] \\" << endl;


  limit_obs->SetPoint(point, mass, obs);
  limit_exp->SetPoint(point, mass, exp);
  band_exp1->SetPoint(point, mass, exp);
  band_exp2->SetPoint(point, mass, exp);
  
  band_exp1->SetPointEYhigh(point, up1 - exp);
  band_exp1->SetPointEYlow(point, exp - dn1);
  band_exp2->SetPointEYhigh(point, up2 - exp);
  band_exp2->SetPointEYlow(point, exp - dn2);
  point++;

}

double max = 200000.0; //band_exp2->GetHistogram()->GetMaximum()*50;

  TCanvas *canvas = new TCanvas("limit set RSG","limit set RSG", 500,500);

  limit_exp->SetMinimum(0.01);
  limit_exp->Draw("AL");
  limit_exp->GetXaxis()->SetTitle("M_{g_{KK}} [GeV]");
  limit_exp->GetYaxis()->SetTitle("95 % CL Limit on #sigma(g_{KK}) [pb]");
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
  l->AddEntry(theory, "RS Gluon (LO #times 1.3)", "L");
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

  canvas->Print("RSG_limit.pdf");
  canvas->Print("RSG_limit.root");

}




