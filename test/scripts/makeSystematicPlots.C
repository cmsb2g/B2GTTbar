void makeSystPlot(string file, string outname, string process, string systematic, string label){

  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0000000000); //this clears all the boxes and crap 
  
  TFile *inFile = new TFile(Form("%s",file.c_str()), "READ");

	TH1F *upShape_0btagH = (TH1F *) inFile->Get( Form("btag0__%s__%s__plus", process.c_str(), systematic.c_str()) );
	TH1F *upShape_1btagH = (TH1F *) inFile->Get( Form("btag1__%s__%s__plus", process.c_str(), systematic.c_str()) );
	TH1F *upShape_2btagH = (TH1F *) inFile->Get( Form("btag2__%s__%s__plus", process.c_str(), systematic.c_str()) );
	TH1F *dnShape_0btagH = (TH1F *) inFile->Get( Form("btag0__%s__%s__minus", process.c_str(), systematic.c_str()) );
	TH1F *dnShape_1btagH = (TH1F *) inFile->Get( Form("btag1__%s__%s__minus", process.c_str(), systematic.c_str()) );
	TH1F *dnShape_2btagH = (TH1F *) inFile->Get( Form("btag2__%s__%s__minus", process.c_str(), systematic.c_str()) );
	TH1F *nomShape_0btagH = (TH1F *) inFile->Get( Form("btag0__%s", process.c_str()) );
	TH1F *nomShape_1btagH = (TH1F *) inFile->Get( Form("btag1__%s", process.c_str()) );
	TH1F *nomShape_2btagH = (TH1F *) inFile->Get( Form("btag2__%s", process.c_str()) );
	
	TH1F *upShape_3btagH = (TH1F *) inFile->Get( Form("btag3__%s__%s__plus", process.c_str(), systematic.c_str()) );
	TH1F *upShape_4btagH = (TH1F *) inFile->Get( Form("btag4__%s__%s__plus", process.c_str(), systematic.c_str()) );
	TH1F *upShape_5btagH = (TH1F *) inFile->Get( Form("btag5__%s__%s__plus", process.c_str(), systematic.c_str()) );
	TH1F *dnShape_3btagH = (TH1F *) inFile->Get( Form("btag3__%s__%s__minus", process.c_str(), systematic.c_str()) );
	TH1F *dnShape_4btagH = (TH1F *) inFile->Get( Form("btag4__%s__%s__minus", process.c_str(), systematic.c_str()) );
	TH1F *dnShape_5btagH = (TH1F *) inFile->Get( Form("btag5__%s__%s__minus", process.c_str(), systematic.c_str()) );
	TH1F *nomShape_3btagH = (TH1F *) inFile->Get( Form("btag3__%s", process.c_str()) );
	TH1F *nomShape_4btagH = (TH1F *) inFile->Get( Form("btag4__%s", process.c_str()) );
	TH1F *nomShape_5btagH = (TH1F *) inFile->Get( Form("btag5__%s", process.c_str()) );
	



	for (int nTags = 0; nTags < 6; nTags++){

	TH1F *nomShape = new TH1F;
	TH1F *upShape = new TH1F;
	TH1F *dnShape = new TH1F;

	string btagLabel = "blah";

	if(nTags == 0){
		btagLabel = "0 b-tags, #Deltay < 1";
		nomShape = (TH1F *) nomShape_0btagH;
		upShape = (TH1F *) upShape_0btagH;
		dnShape = (TH1F *) dnShape_0btagH;
	}
	if(nTags == 1){
		btagLabel = "1 b-tags, #Deltay < 1";
		nomShape = nomShape_1btagH;
		upShape = upShape_1btagH;
		dnShape = dnShape_1btagH;
	}
	if(nTags == 2){
		btagLabel = "2 b-tags, #Deltay < 1";
		nomShape = nomShape_2btagH;
		upShape = upShape_2btagH;
		dnShape = dnShape_2btagH;
	}
	if(nTags == 3){
		btagLabel = "0 b-tags, #Deltay > 1";
		nomShape = nomShape_3btagH;
		upShape = upShape_3btagH;
		dnShape = dnShape_3btagH;
	}
	if(nTags == 4){
		btagLabel = "1 b-tags, #Deltay > 1";
		nomShape = nomShape_4btagH;
		upShape = upShape_4btagH;
		dnShape = dnShape_4btagH;
	}
	if(nTags == 5){
		btagLabel = "2 b-tags, #Deltay > 1";
		nomShape = nomShape_5btagH;
		upShape = upShape_5btagH;
		dnShape = dnShape_5btagH;
	}
	nomShape->Sumw2(); upShape->Sumw2(); dnShape->Sumw2();

	nomShape->SetFillColor(0);
	nomShape->SetLineColor(kBlack);
	upShape->SetFillColor(0);
	dnShape->SetFillColor(0);
	
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

	nomShape->SetTitle("");
	nomShape->GetYaxis()->SetTitle("Events");
	nomShape->GetXaxis()->SetLabelSize(0);
	nomShape->SetMaximum(TMath::Max(upShape->GetMaximum(), dnShape->GetMaximum())*1.30);
	nomShape->Draw("hist");
	upShape->SetLineColor(kGreen + 1);
	upShape->Draw("hist same");
	dnShape->SetLineColor(kRed);
	dnShape->Draw("hist same");

	TLegend *leg = new TLegend(0.6,0.6,0.9,0.88);
	leg->AddEntry(nomShape, label.c_str(), "");
	leg->AddEntry(nomShape, "Nominal", "l");
	leg->AddEntry(upShape, "+1 #sigma", "l");
	leg->AddEntry(dnShape, "-1 #sigma", "l");
	leg->AddEntry(nomShape, btagLabel.c_str(), "");
	leg->SetFillColor(0);
	leg->SetLineColor(0);
	leg->Draw();


	TLatex *cmsLabel = new TLatex();
	cmsLabel->SetNDC();
	//cmsLabel->DrawLatex(0.1, 0.93, "QCD MC");
	if (systematic == "jec") cmsLabel->DrawLatex(0.6,0.93, "Jet Energy Scale");
	if (systematic == "pdf") cmsLabel->DrawLatex(0.6,0.93, "PDF");
	if (systematic == "q2") cmsLabel->DrawLatex(0.6,0.93, "Q^{2} Scale");
	if (systematic == "btag") cmsLabel->DrawLatex(0.6,0.93, "b-Tagging");
	if (systematic == "jer") cmsLabel->DrawLatex(0.6,0.93, "Jet Energy Resolution");
	if (systematic == "modMass") cmsLabel->DrawLatex(0.6,0.93, "Modified Mass");
	if (systematic == "closure") cmsLabel->DrawLatex(0.6,0.93, "Closure Test");

	c1_1->cd();
	c1_1->SetTopMargin(0.01);
	c1_1->SetBottomMargin(0.3);
	c1_1->SetRightMargin(0.05);
	c1_1->SetLeftMargin(0.1);
	c1_1->SetFillStyle(0);

	TH1F *upRatio = (TH1F *) upShape->Clone("upRatio");
	TH1F *dnRatio = (TH1F *) dnShape->Clone("dnRatio");
	upRatio->Sumw2();
	dnRatio->Sumw2();
	

	upRatio->Divide(nomShape);
	dnRatio->Divide(nomShape);

	upRatio->SetTitle("");
	upRatio->GetYaxis()->SetRangeUser(0.,2.5);
	upRatio->GetYaxis()->SetTitle("Ratio to Nominal");
	upRatio->GetYaxis()->SetTitleOffset(0.4);
	upRatio->GetYaxis()->SetTitleSize(0.11);
	upRatio->GetXaxis()->SetLabelSize(0.11);
	upRatio->GetXaxis()->SetTitleSize(0.11);
	upRatio->GetXaxis()->SetTitle( "t#bar{t} Invariant Mass [GeV]");

	upRatio->Draw("hist");
	dnRatio->Draw("hist same");

	TF1 *line = new TF1("line", "1", 0, 5000);
	line->SetLineColor(kBlack);
	line->Draw("same");


	c1->SaveAs( Form("SystPlots/Syst_%s_%s_%dbtags.pdf", systematic.c_str(), outname.c_str(), nTags) );


	}//nTags Loop
}

