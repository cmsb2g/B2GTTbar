// MistagDivide.cc
// Divide 2 histograms to calculate mistag rate or efficiency
// [] .L MistagDivide.cc+
// [] run()

#include "TROOT.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TMath.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
TH1D * divideHists(TFile*, string, string);

void run(){
	// Get input file and setup output file
    TFile * InFile  = new TFile("probe_and_tag_hist.root");
    TFile * OutFile = new TFile("MISTAG_RATE.root" , "RECREATE");

    //Calculate mistag rate (QCD only)
	TH1D * h_mistagSD = divideHists(InFile, "topTagPtSD", "topProbePtSD" );
	TH1D * h_mistagFJ = divideHists(InFile, "topTagPtFJ", "topProbePtFJ" );
	TH1D * h_mistagNM = divideHists(InFile, "topTagPtNM", "topProbePtNM" );

	// Save mistag rate to the output file
	InFile->Close();
    OutFile->cd();
	if (h_mistagSD){
		h_mistagSD->SetName("h_mistagSD");
		h_mistagSD->Write();
	}
	if (h_mistagFJ){
		h_mistagFJ->SetName("h_mistagFJ");
		h_mistagFJ->Write();
	}
	if (h_mistagNM){
		h_mistagNM->SetName("h_mistagNM");
		h_mistagNM->Write();
	}
    OutFile->Close();

}

TH1D * divideHists(TFile * File, string numer, string denom){

	TH1D * h1 = (TH1D*)File->Get(numer.c_str());
	TH1D * h2 = (TH1D*)File->Get(denom.c_str());

	if (h1 && h2){
		
		// setup 
		cout<<"Integrals: "<<numer<<" = "<<h1->Integral()<<" "<<denom<<" = "<<h2->Integral()<<" ratio = "<<h1->Integral()/h2->Integral()<<endl;
    	TH1D *h1new =(TH1D*) h1->Clone();
    	TH1D *h2new =(TH1D*) h2->Clone();
		h1new->Sumw2();
		h2new->Sumw2();

		// rebin with variable width bins
		static const int nbins = 15;
		double xbins[nbins] ={300, 350, 400, 450, 500, 600, 700, 800, 900, 1000, 1200, 1400, 1600, 1800, 2000};
		TH1D* h1rebin = (TH1D*)h1new->Rebin(nbins-1,"h1rebin",xbins);
		TH1D* h2rebin = (TH1D*)h2new->Rebin(nbins-1,"h2rebin",xbins);

		// divide histograms
		h1rebin->Divide(h1rebin,h2rebin,1,1,"B");
		h1rebin->SetTitle(";;Mistag Rate");

		// cleanup
		delete h1;
		delete h2;
		return h1rebin;	
	}
	else {
		cout<<"ERROR: did not get histograms "<<numer<<" "<<denom<<endl;
		return 0;
	}
}


