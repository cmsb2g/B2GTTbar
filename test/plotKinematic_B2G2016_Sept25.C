// .L plotKinematic.C+
// run()

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
#include "TLegend.h"
#include "TColor.h"
#include "TStyle.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TString.h"
#include <vector> 
#include <algorithm>
#include "TROOT.h"
// #include "names.C"
// #include "CMS_lumi.C"



void plotter(TString, TString, TString, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, bool, bool, double, double);

void run(){
	gStyle->SetOptStat(0);
	gROOT->UseCurrentStyle();
	gROOT->ForceStyle();

	gROOT->Reset();
	gROOT->ForceStyle(); 
	// gROOT->SetBatch(); 
	  
	// TFile * fData = new TFile("JetHT_Kinematic_060716_nom_pt400.0.root");
	// TFile * fQCD  = new TFile("QCD_HTall_Kinematic_060716_nom_pt400.0_fixed.root");
	// TFile * fTT   = new TFile("TT_Kinematic_060716_nom_pt400.0.root");
	TFile * fZp10 = new TFile("runs/run20161010/histsAllHad_Jetpt600HT1000_20161010_b2gtree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISpring16MiniAODv2-PUSpring16_reHLT_ext3_V3_99percentFinished_All.root");
	TFile * fZp20 = new TFile("runs/run20161010/histsAllHad_Jetpt600HT1000_20161010_b2gtree_ZprimeToTT_M-2000_W-20_RunIISpring16MiniAODv2_reHLT_V3.root");
	// TFile * fZp30 = new TFile("Z3n_Kinematic_060716_nom_pt400.0.root");
	TFile * fZp40 = new TFile("runs/run20161010/histsAllHad_Jetpt600HT1000_20161010_b2gtree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISpring16MiniAODv2-PUSpring16_reHLT_ext3_V3_99percentFinished_All.root");

	TFile * fData = new TFile("runs/run20161010/histsAllHad_Jetpt600HT1000_20161010_b2gtree_JetHT_combined.root");
	TFile * fQCD  = new TFile("runs/run20161010/histsAllHad_Jetpt600HT1000_20161010_b2gtree_QCD_Pt_300toInf_pythia8_RunIISpring16MiniAODv2_reHLT_V3.root");
	TFile * fTT   = new TFile("runs/run20161010/histsAllHad_Jetpt600HT1000_20161010_b2gtree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISpring16MiniAODv2-PUSpring16_reHLT_ext3_V3_99percentFinished_All.root");
	TFile * fZp30 = new TFile("runs/run20161010/histsAllHad_Jetpt600HT1000_20161010_b2gtree_ZprimeToTT_M-3000_W-30_RunIISpring16MiniAODv2_reHLT_V3.root");

	vector<TString> hists_names;
	vector<TString> hists_title;
	vector<double> hists_rebin;
	vector<bool> legs;
	vector<bool> inverted;
	vector<TString> pave;
	vector<double> x_max_scale;
	vector<double> y_max_scale;

	hists_names.push_back("h_JetSDmass_OppositeJetTag_t_b");                  pave.push_back("H_{T} > 1000 GeV and AK8 jets with p_{T} > 600 GeV, |#eta|<2.4");                                       hists_title.push_back("Jet softdrop mass [GeV]");             hists_rebin.push_back(5);    legs.push_back(true);  inverted.push_back(false);           x_max_scale.push_back(300); y_max_scale.push_back(1.3);      
	hists_names.push_back("h_JetSDmass_OppositeJetTag_t_b_JetTag_b");         pave.push_back("#splitline{H_{T} > 1000 GeV and AK8 jets with p_{T} > 600 GeV,}{|#eta|<2.4, subjet b-tag}");                         hists_title.push_back("Jet softdrop mass [GeV]");             hists_rebin.push_back(5);    legs.push_back(true);  inverted.push_back(false);           x_max_scale.push_back(300); y_max_scale.push_back(1.3);      
	hists_names.push_back("h_JetSDmass_OppositeJetTag_t_b_JetTag_b_tau32");   pave.push_back("#splitline{H_{T} > 1000 GeV and AK8 jets with}{#splitline{p_{T} > 600 GeV, |#eta|<2.4, subjet b-tag,}{#tau_{32}<0.69}}");         hists_title.push_back("Jet softdrop mass [GeV]");             hists_rebin.push_back(5);    legs.push_back(true);  inverted.push_back(false);           x_max_scale.push_back(300); y_max_scale.push_back(1.3);      

	hists_names.push_back("h_JetTau32_OppositeJetTag_t_b");                   pave.push_back("H_{T} > 1000 GeV and AK8 jets with p_{T} > 600 GeV, |#eta|<2.4");                                       hists_title.push_back("Jet #tau_{32}");                       hists_rebin.push_back(5);    legs.push_back(true);  inverted.push_back(false);           x_max_scale.push_back(300); y_max_scale.push_back(1.3);      
	hists_names.push_back("h_JetTau32_OppositeJetTag_t_b_JetTag_b");          pave.push_back("#splitline{H_{T} > 1000 GeV and AK8 jets with p_{T} > 600 GeV,}{|#eta|<2.4, subjet b-tag}");                         hists_title.push_back("Jet #tau_{32}");                       hists_rebin.push_back(5);    legs.push_back(true);  inverted.push_back(false);           x_max_scale.push_back(300); y_max_scale.push_back(1.3);      
	hists_names.push_back("h_JetTau32_OppositeJetTag_t_b_JetTag_b_mass");     pave.push_back("#splitline{H_{T} > 1000 GeV and AK8 jets with p_{T} > 600 GeV, |#eta|<2.4,}{subjet b-tag, 110 GeV<M_{SD}<210 GeV}"); hists_title.push_back("Jet #tau_{32}");                       hists_rebin.push_back(5);    legs.push_back(true);  inverted.push_back(false);           x_max_scale.push_back(300); y_max_scale.push_back(1.3);      
	

	//hists_names.push_back("h_DijetMass_dRapIn");   pave.push_back("H_{T} > 1000 GeV and AK8 jets with p_{T} > 600 GeV, |#eta|<2.4"); hists_title.push_back("h_DijetMass_dRapIn");     hists_rebin.push_back(5);    legs.push_back(true);  inverted.push_back(true);           x_max_scale.push_back(300); y_max_scale.push_back(1.3);      
	hists_names.push_back("h_MET");                pave.push_back("H_{T} > 1000 GeV and AK8 jets with p_{T} > 600 GeV, |#eta|<2.4"); hists_title.push_back("h_MET");                  hists_rebin.push_back(5);    legs.push_back(true);  inverted.push_back(true);           x_max_scale.push_back(300); y_max_scale.push_back(1.3);      
	hists_names.push_back("h_Nvtx");               pave.push_back("H_{T} > 1000 GeV and AK8 jets with p_{T} > 600 GeV, |#eta|<2.4"); hists_title.push_back("h_Nvtx");                 hists_rebin.push_back(5);    legs.push_back(true);  inverted.push_back(true);           x_max_scale.push_back(300); y_max_scale.push_back(1.3);      
	hists_names.push_back("h_DeltaRap");           pave.push_back("H_{T} > 1000 GeV and AK8 jets with p_{T} > 600 GeV, |#eta|<2.4"); hists_title.push_back("h_DeltaRap");             hists_rebin.push_back(5);    legs.push_back(true);  inverted.push_back(true);           x_max_scale.push_back(300); y_max_scale.push_back(1.3);      
	hists_names.push_back("h_DeltaPhi");           pave.push_back("H_{T} > 1000 GeV and AK8 jets with p_{T} > 600 GeV, |#eta|<2.4"); hists_title.push_back("h_DeltaPhi");             hists_rebin.push_back(5);    legs.push_back(true);  inverted.push_back(true);           x_max_scale.push_back(3); y_max_scale.push_back(1.3);      
	hists_names.push_back("h_HT");                 pave.push_back("H_{T} > 1000 GeV and AK8 jets with p_{T} > 600 GeV, |#eta|<2.4"); hists_title.push_back("h_HT");                   hists_rebin.push_back(5);    legs.push_back(true);  inverted.push_back(true);           x_max_scale.push_back(4000); y_max_scale.push_back(1.3);

	hists_names.push_back("h_Jet0Pt");                 pave.push_back("H_{T} > 1000 GeV and AK8 jets with p_{T} > 600 GeV, |#eta|<2.4"); hists_title.push_back("h_Jet0Pt");                   hists_rebin.push_back(5);    legs.push_back(true);  inverted.push_back(true);           x_max_scale.push_back(3000); y_max_scale.push_back(1.3); 

	hists_names.push_back("h_Jet1Pt");                 pave.push_back("H_{T} > 1000 GeV and AK8 jets with p_{T} > 600 GeV, |#eta|<2.4"); hists_title.push_back("h_Jet1Pt");                   hists_rebin.push_back(5);    legs.push_back(true);  inverted.push_back(true);           x_max_scale.push_back(3000); y_max_scale.push_back(1.3); 
     
	


	for (unsigned int i=0; i< hists_names.size(); i++ ){
		cout<<"hData"<<endl;TH1D * hData = (TH1D*) fData ->Get( hists_names[i] ); 
		cout<<"hQCD "<<endl;TH1D * hQCD  = (TH1D*) fQCD  ->Get( hists_names[i] ); 
		cout<<"hTT  "<<endl;TH1D * hTT   = (TH1D*) fTT   ->Get( hists_names[i] ); 
		cout<<"hZp10"<<endl;TH1D * hZp10 = (TH1D*) fZp10 ->Get( hists_names[i] ); 
		cout<<"hZp20"<<endl;TH1D * hZp20 = (TH1D*) fZp20 ->Get( hists_names[i] ); 
		cout<<"hZp30"<<endl;TH1D * hZp30 = (TH1D*) fZp30 ->Get( hists_names[i] ); 
		cout<<"hZp40"<<endl;TH1D * hZp40 = (TH1D*) fZp40 ->Get( hists_names[i] ); 

		float lumi = 27220;
		float nttbar = 92925926; //96834559.;//19665194.;
		float kfactor = 0.94;
		float ttSF = 0.89*0.89;
		double xs_zp30 = 1; // set to 1 to match semilept
		//hQCD ->Scale( 0.9 ); //estimate from mistag rate ratio
		hTT  ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
		hZp10->Scale( 1. * ttSF * lumi / 122204. ); 
		hZp20->Scale( 1. * ttSF * lumi / 202573. ); 
		hZp30->Scale( xs_zp30 * 0.89 * lumi / 117069. ); 
		hZp40->Scale( 1. * ttSF * lumi / 111625. );

		double rebin = hists_rebin[i];
		hData  ->Rebin(rebin); 
		hQCD   ->Rebin(rebin);
		hTT    ->Rebin(rebin); 
		hZp10  ->Rebin(rebin); 
		hZp20  ->Rebin(rebin); 
		hZp30  ->Rebin(rebin); 
		hZp40  ->Rebin(rebin); 

		plotter(hists_names[i], hists_title[i], pave[i], hData, hTT, hQCD, hZp10, hZp20, hZp30, hZp40, legs[i], inverted[i], x_max_scale[i], y_max_scale[i] );

	}
}
void plotter(TString histname, TString histtitle, TString pave, TH1D* hData, TH1D * hTT, TH1D* hQCD, TH1D * hZp10, TH1D * hZp20, TH1D * hZp30, TH1D * hZp40, bool legswitch, bool invert, double x_max_scale, double y_max_scale ){

	Int_t ci;      // for color index setting
	TColor *color; // for color definition with alpha
	ci = TColor::GetColor("#cc3333");
	hTT ->SetFillColor(ci);
	ci = TColor::GetColor("#660000");
	hTT ->SetLineWidth(2);
	hTT ->SetLineColor(ci);
	hQCD->SetLineColor(kYellow+2);
	hQCD->SetLineWidth(2);
	hQCD->SetFillColor(kYellow);

	TCanvas *c1 = new TCanvas("c1", "c1",1,1,745,701);
	gStyle->SetOptFit(1);
	gStyle->SetOptStat(0);
	c1->SetHighLightColor(2);
	c1->Range(0,0,1,1);
	c1->SetFillColor(0);
	c1->SetBorderMode(0);
	c1->SetBorderSize(2);
	c1->SetTickx(1);
	c1->SetTicky(1);
	c1->SetLeftMargin(0.14);
	c1->SetRightMargin(0.04);
	c1->SetTopMargin(0.08);
	c1->SetBottomMargin(0.15);
	c1->SetFrameFillStyle(0);
	c1->SetFrameBorderMode(0);

	TPad *pad1 = new TPad("pad1", "pad1",0,0.3333333,1,1);
	pad1->Draw();
	pad1->cd();
	// pad1->Range(-0.1792683,-2.983224,1.10122,146.183);
	pad1->SetFillColor(0);
	pad1->SetBorderMode(0);
	pad1->SetBorderSize(2);
	pad1->SetTickx(1);
	pad1->SetTicky(1);
	pad1->SetLeftMargin(0.14);
	pad1->SetRightMargin(0.04);
	pad1->SetTopMargin(0.12);
	pad1->SetBottomMargin(0.02);
	pad1->SetFrameFillStyle(0);
	pad1->SetFrameBorderMode(0);
	pad1->SetFrameFillStyle(0);
	pad1->SetFrameBorderMode(0);


	hData->GetXaxis()->SetRangeUser(0, x_max_scale);
	hData->SetMaximum(y_max_scale * hData->GetMaximum() );
	hData->SetMinimum(0.0001 );
	hData->GetYaxis()->SetTitle("Events");
	hData->GetYaxis()->SetTitleSize(0.065);
	hData->GetYaxis()->SetTitleOffset(0.9); // 0.7);
	hData->GetYaxis()->SetLabelSize(0.06);
	// hData->SetMarkerStyle(20);
	// hData->SetMarkerSize(0.8);
	// hData->SetLineColor(kBlack);
	hData->SetTitle("");


	hData->SetLineColor(1);
	hData->SetFillColor(1);
	hData->SetFillStyle(0);
	hData->SetLineWidth(2);
	hData->SetMarkerStyle(20);
	hData->SetMarkerSize(0.8);

	hData->GetXaxis()->SetNdivisions(506);
	hData->GetXaxis()->SetLabelFont(42);
	hData->GetXaxis()->SetLabelSize(0);
	hData->GetXaxis()->SetTitleSize(0.0475);
	hData->GetXaxis()->SetTickLength(0.045);
	hData->GetXaxis()->SetTitleOffset(1.15);
	hData->GetXaxis()->SetTitleFont(42);
	hData->GetYaxis()->SetTitle("Events");
	hData->GetYaxis()->SetNdivisions(506);
	hData->GetYaxis()->SetLabelFont(42);
	hData->GetYaxis()->SetLabelSize(0.06375);
	hData->GetYaxis()->SetTitleSize(0.07125);
	hData->GetYaxis()->SetTitleOffset(0.9);
	hData->GetYaxis()->SetTitleFont(42);
	hData->GetZaxis()->SetLabelFont(42);
	hData->GetZaxis()->SetLabelSize(0.0425);
	hData->GetZaxis()->SetTitleSize(0.0475);
	hData->GetZaxis()->SetTitleFont(42);


	hData->Draw("lep");//E0");

	THStack *stack = new THStack();
	if (!invert){
	stack->Add(hQCD );
	stack->Add( hTT );
	}
	else{
	stack->Add( hTT );
	stack->Add(hQCD );
	}
	stack->Draw("hist same");

	hData->Draw("lepsame");

	//errors                                                                                                                                
	float xsErr_top = 0.15;
	float lumiErr_top = 0.027;
	float topTagErr_top = 2*(0.09/0.89);
	float totalTopErr = 0.0;
	float totalQCDErr = 0.0;
	float totalHistErr = 0.0;

	TH1F *totalH = (TH1F *) hQCD->Clone("totalH");
	totalH->Add(hTT);

	totalH->SetFillColor(202);
	totalH->SetFillStyle(3254);

	totalH->Draw("E2 same");

	int n_xbins = totalH->GetNbinsX();

	hZp30->SetFillColor(1);
	hZp30->SetFillStyle(0);
	hZp30->SetLineStyle(2);
	hZp30->SetLineWidth(2);

	hData->Draw("lepsame");

	TLatex *   tex = new TLatex(0.14,0.916,"#font[62]{CMS} #font[52]{Preliminary}");
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.0825);
	tex->SetLineWidth(2);
	tex->Draw();
	tex = new TLatex(0.96,0.916,"27.2 fb^{-1} (13 TeV)");
	tex->SetNDC();
	tex->SetTextAlign(31);
	tex->SetTextFont(42);
	tex->SetTextSize(0.0825);
	tex->SetLineWidth(2);
	tex->Draw();
	tex = new TLatex(0.181,0.82225,pave);
	tex->SetNDC();
	tex->SetTextAlign(13);
	tex->SetTextFont(42);
	tex->SetTextSize(0.045);
	tex->SetLineWidth(2);
	tex->Draw();

	double leg1 =0.5; double leg2 =0.49; double leg3 =0.85; double leg4 =0.8;
	TLegend *leg = new TLegend(leg1, leg2, leg3, leg4);
	leg->SetTextSize(0.057);
	leg->AddEntry(hData, "Data", "lp");
	leg->AddEntry(hQCD, "QCD simulation", "f");
	leg->AddEntry(hTT, "SM t#bar{t} simulation", "f");
	leg->SetFillColor(0);
	leg->SetLineColor(0);


	double peg1 =0.181; double peg2 =0.4642; double peg3 =0.468; double peg4 =0.7414;
	TLegend *peg = new TLegend(peg1, peg2, peg3, peg4,NULL,"brNDC");
	peg->SetBorderSize(0);
	peg->SetLineColor(1);
	peg->SetLineStyle(1);
	peg->SetLineWidth(1);
	peg->SetFillColor(0);
	peg->SetFillStyle(1001);

	peg->AddEntry(hData, "Data", "lep");
	peg->AddEntry(hTT, "SM t#bar{t} simulation", "f");

	peg->AddEntry(hQCD, "QCD simulation", "f");
	peg->AddEntry("hZp30","Z' 3 TeV (#sigma=1 pb)","l");

	peg->SetFillColor(0);
	peg->SetLineColor(0);

	/*if (legswitch)  peg->Draw("same");
	  if (!legswitch) leg->Draw("same");*/

	gPad->RedrawAxis();


	pad1->Modified();
	c1->cd();





	TPad *pad2 = new TPad("pad2", "pad2",0,0,1,0.3333333);
	pad2->Draw();
	pad2->cd();
	// pad2->Range(-0.1792683,-1.370091,1.10122,1.899);
	pad2->SetFillColor(0);
	pad2->SetBorderMode(0);
	pad2->SetBorderSize(2);
	pad2->SetTickx(1);
	pad2->SetTicky(1);
	pad2->SetLeftMargin(0.14);
	pad2->SetRightMargin(0.04);
	pad2->SetTopMargin(0);
	pad2->SetBottomMargin(0.45);
	pad2->SetFrameFillStyle(0);
	pad2->SetFrameBorderMode(0);
	pad2->SetFrameFillStyle(0);
	pad2->SetFrameBorderMode(0);

	TH1F *ratioH = new TH1F();
	ratioH = (TH1F*) hData->Clone("ratio");
	ratioH->Sumw2();
	ratioH->Divide(ratioH, totalH);

	TH1F *ratioErrH = new TH1F();
	ratioErrH = (TH1F*) totalH->Clone("ratioErr");
	ratioErrH->Sumw2();
	ratioErrH->Divide(ratioErrH, totalH);

	ratioH->GetYaxis()->SetRangeUser(0.01,1.99);
	// ratioH->GetYaxis()->SetTitle("Data / Bkgd");
	// ratioH->GetYaxis()->SetTitleOffset(0.3);
	// ratioH->GetYaxis()->SetTitleSize(0.17);
	// ratioH->GetYaxis()->SetNdivisions(205);
	// ratioH->GetYaxis()->SetLabelSize(0.11);
	// ratioH->GetXaxis()->SetLabelSize(0.11);
	// ratioH->GetXaxis()->SetTitleSize(0.17);
	ratioH->GetXaxis()->SetTitle( histtitle );

	ratioH->SetStats(0);
	ratioH->SetFillColor(1);
	ratioH->SetFillStyle(0);
	ratioH->SetLineWidth(2);
	ratioH->SetLineColor(1);
	ratioH->SetMarkerStyle(20);
	ratioH->SetMarkerSize(0.8);
	ratioH->GetXaxis()->SetNdivisions(506);
	ratioH->GetXaxis()->SetLabelFont(42);
	ratioH->GetXaxis()->SetLabelOffset(0.015);
	ratioH->GetXaxis()->SetLabelSize(0.1275);
	ratioH->GetXaxis()->SetTitleSize(0.1425);
	ratioH->GetXaxis()->SetTickLength(0.09);
	ratioH->GetXaxis()->SetTitleOffset(1.15);
	ratioH->GetXaxis()->SetTitleFont(42);
	ratioH->GetYaxis()->SetTitle("Data/Bkg");
	ratioH->GetYaxis()->CenterTitle(true);
	ratioH->GetYaxis()->SetNdivisions(304);
	ratioH->GetYaxis()->SetLabelFont(42);
	ratioH->GetYaxis()->SetLabelSize(0.1275);
	ratioH->GetYaxis()->SetTitleSize(0.1425);
	ratioH->GetYaxis()->SetTickLength(0.045);
	ratioH->GetYaxis()->SetTitleOffset(0.45);
	ratioH->GetYaxis()->SetTitleFont(42);
	ratioH->GetZaxis()->SetLabelFont(42);
	ratioH->GetZaxis()->SetLabelSize(0.0425);
	ratioH->GetZaxis()->SetTitleSize(0.0475);
	ratioH->GetZaxis()->SetTitleFont(42);

	ratioH->Draw("lepe0");

	ratioErrH->SetFillStyle(1001);
	ratioErrH->SetFillColor(kGray);

	ratioErrH->Draw("E2 same");

	TF1 *line = new TF1("line", "1", -7000, 7000);
	line->SetLineColor(kBlack);
	line->SetLineStyle(2);
	line->SetLineWidth(2);
	line->Draw("same");
	ratioH->Draw("E0 same");

	gPad->RedrawAxis();
	 
	pad2->Modified();
	c1->cd();
	c1->Modified();
	c1->cd();
	c1->SetSelected(c1);     

	if (invert) histname = histname+"_inverted";
	c1->SaveAs("runs/run20161010/kinPlots/Jetpt600HT1000_"+histname+".pdf");
	c1->SaveAs("runs/run20161010/kinPlots/Jetpt600HT1000_"+histname+".png");
	pad1->cd();
	hData->SetMaximum(30.0 * hData->GetMaximum() );
	pad1->SetLogy(1);
	c1->SaveAs("runs/run20161010/kinPlots/Jetpt600HT1000_"+histname+"_log.pdf");
	c1->SaveAs("runs/run20161010/kinPlots/Jetpt600HT1000_"+histname+"_log.png");

}
