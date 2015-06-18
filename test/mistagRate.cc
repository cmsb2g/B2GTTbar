/* 
  Script for dividing the tag and probe pT
  
*/
//  
//  load options & set plot style
//  
#include "TROOT.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH1.h"
#include "THStack.h"
#include "TH2.h"
#include "TF1.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TMath.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void mistagRate() {
	TFile* f_tagProbePt;

	TH1F* h_topTagPtSD;
	TH1F* h_topProbePtSD;
	TH1F* h_mistagrateSD;
        TH1F* h_topTagPtFJ;
        TH1F* h_topProbePtFJ;
        TH1F* h_mistagrateFJ;
        TH1F* h_topTagPtNM;
        TH1F* h_topProbePtNM;
        TH1F* h_mistagrateNM;
        TH1F* h_topTagPtSDT;
        TH1F* h_topProbePtSDT;
        TH1F* h_mistagrateSDT;
        TH1F* h_topTagPtFJT;
        TH1F* h_topProbePtFJT;
        TH1F* h_mistagrateFJT;
        TH1F* h_topTagPtNMT;
        TH1F* h_topProbePtNMT;
        TH1F* h_mistagrateNMT;
        TH1F* h_topTagPtFree;
        TH1F* h_topProbePtFree;
        TH1F* h_mistagrateFree;

	Int_t RB = 40;
	TCanvas* c1;
	//TH1F* Check;
	//	Double_t xbins[10] = {0, 349.5, 400, 500, 600, 700, 800, 900, 1000, 1200};  
	Double_t xbins[10] = {0, 20, 25, 30, 35, 40, 50, 60, 70, 80};  
	// getting the tag and probe root file
	cout<<"opening the file"<<endl;
	f_tagProbePt = new TFile("probe_and_tag_hist.root");
	//Check = (TH1F*) f_tagProbePt->Get("topTagPtSD")->Clone();
	//cout<<"DEBUG: after reading the file ="<< Check->GetSum()<<endl;

	// getting the topTagPt and topProbePt hists
	cout<<"getting the histograms"<<endl;
	h_topTagPtSD   = (TH1F*) f_tagProbePt->Get("topTagPtSD")->Clone();
	h_topProbePtSD = (TH1F*) f_tagProbePt->Get("topProbePtSD")->Clone();

	h_topProbePtSD->Rebin(RB);//9,, "topProbePtSD", xbins);
	h_topTagPtSD->Rebin(RB);//9,, "topTagPtSD", xbins);

	// dividing topProbePt by topTagPt
	h_mistagrateSD = (TH1F*) h_topTagPtSD->Clone();

	//h_mistagrateSD->SetName("mistagrate");
	h_mistagrateSD->SetTitle("Mistag Rate;p_{T}(GeV)");// Soft Drop Mass Window 140-200 GeV;p_{T}(GeV)");
	h_mistagrateSD->Divide((TH1F*) h_topProbePtSD);

	h_mistagrateSD->SetMarkerColor(1);
	h_mistagrateSD->SetLineColor(1);
	h_mistagrateSD->SetMarkerStyle(20);


        h_topTagPtFJ   = (TH1F*) f_tagProbePt->Get("topTagPtFJ")->Clone();
        h_topProbePtFJ = (TH1F*) f_tagProbePt->Get("topProbePtFJ")->Clone();

        //h_topProbePtFJ->Rebin(RB);
	h_topProbePtFJ->Rebin(RB);//9,, "topProbePtFJ", xbins);
	h_topTagPtFJ->Rebin(RB);//9,, "topTagPtFJ", xbins);

        // dividing topProbePt by topTagPt                                                                                                                                
        h_mistagrateFJ = (TH1F*) h_topTagPtFJ->Clone();
        //h_mistagrateSD->Rebin(2);                                                                                                                         
        //h_mistagrateSD->SetName("mistagrate");    

        h_mistagrateFJ->SetTitle("Mistag Rate");// Soft Drop Mass Window 140-200 GeV;p_{T}(GeV)");                                                      
        h_mistagrateFJ->Divide((TH1F*) h_topProbePtFJ);


	h_mistagrateFJ->SetMarkerColor(2);
	h_mistagrateFJ->SetLineColor(2);
	h_mistagrateFJ->SetMarkerStyle(21);



        h_topTagPtNM   = (TH1F*) f_tagProbePt->Get("topTagPtNM")->Clone();
        h_topProbePtNM = (TH1F*) f_tagProbePt->Get("topProbePtNM")->Clone();

        h_topProbePtNM->Rebin(RB);
        h_topTagPtNM->Rebin(RB);                                                                                                 
	h_topProbePtNM->Rebin(RB);//9,, "topProbePtNM", xbins);
	h_topTagPtNM->Rebin(RB);//9,, "topTagPtNM", xbins);

        // dividing topProbePt by topTagPt                                                                                                                                
        h_mistagrateNM = (TH1F*) h_topTagPtNM->Clone();


        //h_mistagrateNM->SetName("mistagrate");                                                                                                                          
        h_mistagrateNM->SetTitle("Mistag Rate");// Soft Drop Mass Window 140-200 GeV;p_{T}(GeV)");                                                                        
        h_mistagrateNM->Divide((TH1F*) h_topProbePtNM);


	h_mistagrateNM->SetMarkerColor(3);
	h_mistagrateNM->SetLineColor(3);
	h_mistagrateNM->SetMarkerStyle(22);


        h_topTagPtSDT   = (TH1F*) f_tagProbePt->Get("topTagPtSDT")->Clone();
        h_topProbePtSDT = (TH1F*) f_tagProbePt->Get("topProbePtSDT")->Clone();

        //h_topProbePtSDT->Rebin(RB);

	h_topProbePtSDT->Rebin(RB);//9,, "topProbePtSDT", xbins);
	h_topTagPtSDT->Rebin(RB);//9,, "topTagPtSDT", xbins);

        // dividing topProbePt by topTagPt                                                                                                                                
        h_mistagrateSDT = (TH1F*) h_topTagPtSDT->Clone();
        //h_mistagrateSDT->Rebin(2);                                                                                                                                          //h_mistagrateSDT->SetName("mistagrate");                                                                                                                    
     
        h_mistagrateSDT->SetTitle("Mistag Rate");// Soft Drop Mass Window 140-200 GeV;p_{T}(GeV)");                                                                        
        h_mistagrateSDT->Divide((TH1F*) h_topProbePtSDT);


	h_mistagrateSDT->SetMarkerColor(4);
	h_mistagrateSDT->SetLineColor(4);
	h_mistagrateSDT->SetMarkerStyle(23);

        h_topTagPtFJT   = (TH1F*) f_tagProbePt->Get("topTagPtFJT")->Clone();
        h_topProbePtFJT = (TH1F*) f_tagProbePt->Get("topProbePtFJT")->Clone();

        //h_topProbePtFJT->Rebin(RB);
	h_topProbePtFJT->Rebin(RB);//9, "topProbePtFJT", xbins);
	h_topTagPtFJT->Rebin(RB);//9, "topTagPtFJT", xbins);

        // dividing topProbePt by topTagPt                                                                                                                                
        h_mistagrateFJT = (TH1F*) h_topTagPtFJT->Clone();
        //h_mistagrateFJT->Rebin(2);                                                                                                                                       

        //h_mistagrateFJT->SetName("mistagrate");                                                                                                                          
        h_mistagrateFJT->SetTitle("Mistag Rate");// Soft Drop Mass Window 140-200 GeV;p_{T}(GeV)");                                                                        
        h_mistagrateFJT->Divide((TH1F*) h_topProbePtFJT);


	h_mistagrateFJT->SetMarkerColor(12);
	h_mistagrateFJT->SetLineColor(12);
	h_mistagrateFJT->SetMarkerStyle(33);

        h_topTagPtNMT   = (TH1F*) f_tagProbePt->Get("topTagPtNMT")->Clone();
        h_topProbePtNMT = (TH1F*) f_tagProbePt->Get("topProbePtNMT")->Clone();

        h_topProbePtNMT->Rebin(RB);

        h_topTagPtNMT->Rebin(RB);
	//h_topProbePtNMT->Rebin(9, "topProbePtNMT", xbins);
	//h_topTagPtNMT->Rebin(9, "topTagPtNMT", xbins);
        // dividing topProbePt by topTagPt                                                                                                                                
        h_mistagrateNMT = (TH1F*) h_topTagPtNMT->Clone();
       //h_mistagrateNMT->SetName("mistagrate");                                                                                                                          
        h_mistagrateNMT->SetTitle("Mistag Rate");// Soft Drop Mass Window 140-200 GeV;p_{T}(GeV)");                                                                        
        h_mistagrateNMT->Divide((TH1F*) h_topProbePtNMT);

	h_mistagrateNMT->SetMarkerColor(6);
	h_mistagrateNMT->SetLineColor(6);
	h_mistagrateNMT->SetMarkerStyle(34);

	
        h_topTagPtFree   = (TH1F*) f_tagProbePt->Get("topTagPtFree")->Clone();
        h_topProbePtFree = (TH1F*) f_tagProbePt->Get("topProbePtFree")->Clone();

        h_topProbePtFree->Rebin(RB);

        h_topTagPtFree->Rebin(RB);
	//h_topProbePtFree->Rebin(9, "topProbePtFree", xbins);
	//h_topTagPtFree->Rebin(9, "topTagPtFree", xbins);
        // dividing topProbePt by topTagPt                                                                                                                                
        h_mistagrateFree = (TH1F*) h_topTagPtFree->Clone();
       //h_mistagrateFree->SetName("mistagrate");                                                                                                                          
        h_mistagrateFree->SetTitle("Mistag Rate");// Soft Drop Mass Window 140-200 GeV;p_{T}(GeV)");                                                                        
        h_mistagrateFree->Divide((TH1F*) h_topProbePtFree);

	h_mistagrateFree->SetMarkerColor(7);
	h_mistagrateFree->SetLineColor(7);
	h_mistagrateFree->SetMarkerStyle(29);


	h_mistagrateSD->SetLineWidth(4);
        h_mistagrateFJ->SetLineWidth(4);
        h_mistagrateNM->SetLineWidth(4);
        h_mistagrateSDT->SetLineWidth(4);
        h_mistagrateFJT->SetLineWidth(4);
        h_mistagrateNMT->SetLineWidth(4);
        h_mistagrateFree->SetLineWidth(4);


	TLegend* leg = new TLegend(.8, .2, 1.05, .45);
	leg->AddEntry(h_mistagrateSD, "Soft Drop Mass Window 140-200 GeV","l");
	leg->AddEntry(h_mistagrateFJ, "AK8 Mass Window 140-250 GeV","l");
	leg->AddEntry(h_mistagrateNM, "No Mass Window","l");
	leg->AddEntry(h_mistagrateSDT, "Soft Drop Mass Window 140-200 GeV + Tau32 > .7","l");
	leg->AddEntry(h_mistagrateFJT, "AK8 Mass Window 140-200 GeV + Tau32 > .7","l");
	leg->AddEntry(h_mistagrateNMT, "Tau32 > .7","l");
	leg->AddEntry(h_mistagrateFree, "No Anti-tag","l");

	// plotting the mistagrate plot
	cout<<"plotting the mistagRate plot"<<endl;
	c1 = new TCanvas("c" , "" , 800, 600);

	c1->cd();
	//h_mistagrateSD->SetMaximum(0.65);
	//h_mistagrateSD->SetMinimum(0.0);
	h_mistagrateSD->Draw("hist");//h_topProbePt->Draw("");//h_mistagrate->Draw("");
	h_mistagrateFJ->Draw("SAMEhist");
	h_mistagrateNM->Draw("SAMEhist");
	h_mistagrateSDT->Draw("SAMEhist");
	h_mistagrateFJT->Draw("SAMEhist");
	h_mistagrateNMT->Draw("SAMEhist");
	h_mistagrateFree->Draw("SAMEhist");
	

	leg->Draw();
	c1->Draw();
	c1->SaveAs("mistagRatePlot.png", "png");




}
