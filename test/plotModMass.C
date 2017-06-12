{

		gStyle->SetOptFit(1);
	gStyle->SetOptStat(0);
	string infolder = "/uscms_data/d2/jdolen/B2G2016/CMSSW_8_0_26_patch2/src/Analysis/B2GTTbar/test/runs/";

	string sdata   = infolder + "histsModMass_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_JetHT_all.root";	                 
	TFile * fData    = new TFile( sdata.c_str()   );

	TH1D * hData1  = (TH1D*) fData  ->Get( "h_mPuppiSDropAK8_ModMass_jet0" ); 
	TH1D * hData2  = (TH1D*) fData  ->Get( "h_mPuppiSDropAK8_ModMass_jet1" ); 

	TCanvas *c1 = new TCanvas("c1", "c1",1,1,745,701);

hData1->Rebin(2);
hData2->Rebin(2);

	hData1->SetStats(0);
	hData1->GetYaxis()->SetRangeUser( 0.8*hData2->GetMinimum() ,   1.1*hData2->GetMaximum() );

hData1->SetLineColor(1);
hData2->SetLineColor(2);
hData1->SetLineWidth(2);
hData2->SetLineWidth(2);

hData1->SetTitle(";m_{SD}^{PUPPI} [GeV];Number of jets");
	hData1->GetYaxis()->SetTitleOffset(1.2);

hData1->Draw();
hData2->Draw("same");

	double leg1 =0.53; double leg2 =0.66; double leg3 =0.88; double leg4 =0.85;
	TLegend *leg = new TLegend(leg1, leg2, leg3, leg4);
	leg->SetTextSize(0.042);
	leg->SetMargin(0.2);
	leg->AddEntry( hData1 , "Leading jet"                   , "L" );
	leg->AddEntry( hData2 , "Sub-leading jet"                   , "L" );
	leg->SetFillColor(0);
	leg->SetLineColor(0); 
	leg->Draw("same");

c1->SaveAs("plotsModMass/h_modmass_data.pdf");


// h_mPuppiSDropAK8_ModMass_jet1

//   KEY: TH1F	h_mAK8_ModMass;1	
//   KEY: TH1F	h_mAK8_ModMass_jet0;1	
//   KEY: TH1F	h_mAK8_ModMass_jet1;1	
//   KEY: TH1F	h_mSDropAK8_ModMass;1	
//   KEY: TH1F	h_mSDropAK8_ModMass_jet0;1	
//   KEY: TH1F	h_mSDropAK8_ModMass_jet1;1	
//   KEY: TH1F	h_mSDropAK8_AltTag_ModMass;1	
//   KEY: TH1F	h_mSDropAK8_AltTag_ModMass_jet0;1	
//   KEY: TH1F	h_mSDropAK8_AltTag_ModMass_jet1;1	
//   KEY: TH1F	h_mSDropAK8_AltTag2_ModMass;1	
//   KEY: TH1F	h_mSDropAK8_AltTag2_ModMass_jet0;1	
//   KEY: TH1F	h_mSDropAK8_AltTag2_ModMass_jet1;1	
//   KEY: TH1F	h_mPuppiSDropAK8_ModMass;1	
//   KEY: TH1F	h_mPuppiSDropAK8_ModMass_jet0;1	
//   KEY: TH1F	h_mPuppiSDropAK8_ModMass_jet1;1	
//   KEY: TH1F	h_mPuppiSDropAK8_AltTag_ModMass;1	
//   KEY: TH1F	h_mPuppiSDropAK8_AltTag_ModMass_jet0;1	
//   KEY: TH1F	h_mPuppiSDropAK8_AltTag_ModMass_jet1;1	
//   KEY: TH1F	h_mPuppiSDropAK8_AltTag2_ModMass;1	
//   KEY: TH1F	h_mPuppiSDropAK8_AltTag2_ModMass_jet0;1	
//   KEY: TH1F	h_mPuppiSDropAK8_AltTag2_ModMass_jet1;1	
//   KEY: TH2F	h_pT_mSDropAK8_ModMass;1	
//   KEY: TH2F	h_pT_mSDropAK8_ModMass_jet0;1	
//   KEY: TH2F	h_pT_mSDropAK8_ModMass_jet1;1	
//   KEY: TH2F	h_pT_mSDropAK8_AltTag_ModMass;1	
//   KEY: TH2F	h_pT_mSDropAK8_AltTag_ModMass_jet0;1	
//   KEY: TH2F	h_pT_mSDropAK8_AltTag_ModMass_jet1;1	
//   KEY: TH2F	h_pT_mPuppiSDropAK8_ModMass;1	
//   KEY: TH2F	h_pT_mPuppiSDropAK8_ModMass_jet0;1	
//   KEY: TH2F	h_pT_mPuppiSDropAK8_ModMass_jet1;1	
//   KEY: TH2F	h_pT_mPuppiSDropAK8_AltTag_ModMass;1	
//   KEY: TH2F	h_pT_mPuppiSDropAK8_AltTag_ModMass_jet0;1	
//   KEY: TH2F	h_pT_mPuppiSDropAK8_AltTag_ModMass_jet1;1	
//   KEY: TH2F	h_pT_PuppimSDropAK8_AltTag2_ModMass;1	
//   KEY: TH2F	h_pT_PuppimSDropAK8_AltTag2_ModMass_jet0;1	
//   KEY: TH2F	h_pT_PuppimSDropAK8_AltTag2_ModMass_jet1;1	
//   KEY: TH2F	h_p_mPuppiSDropAK8_ModMass;1	
//   KEY: TH2F	h_p_mPuppiSDropAK8_ModMass_jet0;1	
//   KEY: TH2F	h_p_mPuppiSDropAK8_ModMass_jet1;1	
//   KEY: TH2F	h_p_mPuppiSDropAK8_AltTag_ModMass;1	
//   KEY: TH2F	h_p_mPuppiSDropAK8_AltTag_ModMass_jet0;1	
//   KEY: TH2F	h_p_mPuppiSDropAK8_AltTag_ModMass_jet1;1	
//   KEY: TH2F	h_p_PuppimSDropAK8_AltTag2_ModMass;1	
//   KEY: TH2F	h_p_PuppimSDropAK8_AltTag2_ModMass_jet0;1	
//   KEY: TH2F	h_p_PuppimSDropAK8_AltTag2_ModMass_jet1;1

  }