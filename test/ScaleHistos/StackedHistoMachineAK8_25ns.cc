#include <TH1F.h>
#include <TH2F.h>
#include <iostream>
#include <ctime>
#include <string>
#include "TFile.h"
#include "TBranch.h"
#include "TTree.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TString.h"
#include "TFrame.h"
#include "THStack.h"
#include "TColor.h"
using namespace std;

TString theHists [] = {"h_mAK8","h_mSDropAK8","h_mprunedAK8","h_mfilteredAK8","h_mtrimmedAK8","h_minmassAK8","h_ptAK8","h_nsjAK8","h_tau21AK8","h_tau32AK8"};

void callHistos();
void StackedHistoMachineAK8_25ns();
void plotter( TString Histo );

TString CalledHisto;

void StackedHistoMachineAK8_25ns(){
    callHistos ();
}

void callHistos ( ){  
    plotter( CalledHisto );
}

void plotter(TString Histo){


TString xAxisTitle;  
double minX;
double maxX;
double maxY;
double xInfo;
double yInfoTop;
double legendLocation [4];

  
for (int j=0; j<10; j++) {
	int histo = 0;
	Histo = theHists[j];
	if (Histo == "h_mAK8")
		histo =1;

	if (Histo == "h_mSDropAK8")
		histo =2;

	if (Histo == "h_mtrimmedAK8")
		histo =3;

	if (Histo == "h_mprunedAK8")
		histo =4;

	if (Histo == "h_mfilteredAK8")
		histo =5;

	if (Histo == "h_minmassAK8")
		histo =6;

	if (Histo == "h_tau32AK8")
		histo =7;

	if (Histo == "h_tau21AK8")
		histo =8;

	if (Histo == "h_nsjAK8")
		histo =9;

	if (Histo == "h_ptAK8" )
		histo =10;


	switch (histo)
	{
	    case 1 :{
	    xAxisTitle = "M_{jet} (GeV)"; 
	    minX = 0;
	    maxX = 600; 
	    maxY = 45;
	    xInfo = 0.301; //  location of plot description in normalized coordinates
	    yInfoTop = 0.868;
	    legendLocation[0] = 0.38058;
	    legendLocation[1] = 0.377976;
	    legendLocation[2] = 0.700893;
	    legendLocation[3] = 0.668155;
	    cout << "This histo is h_mAK8 " << endl;
	  //  return xAxisTitle, minX, maxX, xInfo, yInfoTop, legendLocation [4];
	    break;
	    }
	    case 2 :{ 
	    xAxisTitle = "M_{jet} Soft Drop (GeV)"; 
	    minX = 0;
	    maxX = 600; 
	    maxY = 45;
	    xInfo = 0.131; //  location of plot description in normalized coordinates
	    yInfoTop = 0.868;
	    legendLocation[0] = 0.370759;
	    legendLocation[1] = 0.320595;
	    legendLocation[2] = 0.650536;
	    legendLocation[3] = 0.611488;
	    cout << "This histo is n_mSDropAK8 " << endl;
	    break;
	    }
	    case 3 :{
	    xAxisTitle = "M_{jet} Trimmed (GeV)";
	    minX = 0;
	    maxX = 500; 
	    maxY = 45;
	    xInfo = 0.341; //  location of plot description in normalized coordinates
	    yInfoTop = 0.868;
	    legendLocation[0] = 0.324777;
	    legendLocation[1] = 0.350893;
	    legendLocation[2] = 0.675223;
	    legendLocation[3] = 0.651786;
	    break;
	    }
	    case 4 :{
	    xAxisTitle = "M_{jet} Pruned (GeV)";
	    minX = 0;
	    maxX = 500; 
	    maxY = 45;
	    xInfo = 0.341; //  location of plot description in normalized coordinates
	    yInfoTop = 0.868;
	    legendLocation[0] = 0.324777;
	    legendLocation[1] = 0.350893;
	    legendLocation[2] = 0.675223;
	    legendLocation[3] = 0.651786;
	    break;
	    }
	    case 5 :{
	    xAxisTitle = "M_{jet} Filtered (GeV)";
	    minX = 0;
	    maxX = 500; 
	    maxY = 45;
	    xInfo = 0.341; //  location of plot description in normalized coordinates
	    yInfoTop = 0.868;
	    legendLocation[0] = 0.324777;
	    legendLocation[1] = 0.350893;
	    legendLocation[2] = 0.675223;
	    legendLocation[3] = 0.651786;
	    break;
	    }
	    case 6 :{
	    xAxisTitle = "Minimum Mass Pairing of Subjets (GeV)"; 
	    minX = 0;
	    maxX = 200; 
	    maxY = 45;
	    xInfo = 0.131; //  location of plot description in normalized coordinates
	    yInfoTop = 0.868;
	    legendLocation[0] = 0.415179;
	    legendLocation[1] = 0.547619;
	    legendLocation[2] = 0.584821;
	    legendLocation[3] = 0.848214;
	    cout << "This histo is h_minmassAK8 " << endl;
	    break;
	    }
	    case 7 :{
	    xAxisTitle = "#tau_{3}/#tau_{2}"; 
	    minX = 0;
	    maxX = 1; 
	    maxY = 45;
	    xInfo = 0.131; //  location of plot description in normalized coordinates
	    yInfoTop = 0.868;
	    legendLocation[0] = 0.100759;
	    legendLocation[1] = 0.350595;
	    legendLocation[2] = 0.470536;
	    legendLocation[3] = 0.651488;
	    cout << "This histo is n_tau32AK8 " << endl;
	    break;
	    }
	    case 8:{
	    xAxisTitle = "#tau_{2}/#tau_{1}"; 
	    minX = 0;
	    maxX = 1; 
	    maxY = 45;
	    xInfo = 0.131; //  location of plot description in normalized coordinates
	    yInfoTop = 0.868;
	    legendLocation[0] = 0.100759;
	    legendLocation[1] = 0.350595;
	    legendLocation[2] = 0.470536;
	    legendLocation[3] = 0.651488;
	    cout << "This histo is n_tau21AK8 " << endl;
	    break;
	    }
	    case 9 :{
	    xAxisTitle = "Number of Subjets"; 
	    minX = 0;
	    maxX = 10; 
	    maxY = 125;
	    xInfo = 0.131; //  location of plot description in normalized coordinates
	    yInfoTop = 0.868;
	    legendLocation[0] = 0.420759;
	    legendLocation[1] = 0.450595;
	    legendLocation[2] = 0.60036;
	    legendLocation[3] = 0.751488;
	    cout << "This histo is n_nsjAK8 " << endl;
	    break;
	    }
	    case 10 :{
	    xAxisTitle = "Jet p_{T}"; 
	    minX = 390;
	    maxX = 1300; 
	    xInfo = 0.281; //  location of plot description in normalized coordinates
	    yInfoTop = 0.868;
	    legendLocation[0] = 0.256696;
	    legendLocation[1] = 0.315476;
	    legendLocation[2] = 0.607143;
	    legendLocation[3] = 0.616071;
	    cout << "This histo is h_ptAK8 " << endl;
	    break;    
	    }
	    case 0 :{
	    cout << "Invalid Histogram" << endl;
	    break;
	    }
	}//end switch


	  THStack *hs = new THStack();

	//  @ set the Infile names (.root assumed)
	  TString InFile1 = "July23-TTJets-25ns-sel1";  // TT Jets
	  TString InFile2 = "July23-WJets-25ns-sel1";  // W + Jets                                                    
	  TString InFile3 = "July23-ST-25ns-sel1";  // Single Top
	  TString InFile4 = "July23-ZJets-25ns-sel1";  // Drell- Yan
	  //TString InFile5 = "July23-MuData-25ns-sel1";  //Muon Data
	  TString InFile6 = "July23-Z-200-25ns-sel1"; // Z' W= 200
	  TString InFile7 = "July23-Z-20-25ns-sel1"; // Z' W = 20
	 // TString InFile8 = "July23-ElData-25ns-sel1";  //Electron Data

	  TFile *PlotFile1 = TFile::Open("../"+InFile1+".root");       
	  TFile *PlotFile2 = TFile::Open("../"+InFile2+".root");   
	  TFile *PlotFile3 = TFile::Open("../"+InFile3+".root");       
	  TFile *PlotFile4 = TFile::Open("../"+InFile4+".root");  
	 // TFile *PlotFile5 = TFile::Open("../"+InFile5+".root");       
	  TFile *PlotFile6 = TFile::Open("../"+InFile6+".root");  
	  TFile *PlotFile7 = TFile::Open("../"+InFile7+".root"); 
	  //TFile *PlotFile8 = TFile::Open("../"+InFile8+".root"); 

	  TH1F* histo1;
	  TH1F* histo2;
	  TH1F* histo3;
	  TH1F* histo4;
	  //TH1F* histo5;
	  TH1F* histo6;
	  TH1F* histo7;
	  //TH1F* histo8;

	//  TString Plot = Histo;
	  histo1 = (TH1F*) PlotFile1->Get(Histo);
	  histo2 = (TH1F*) PlotFile2->Get(Histo);
	  histo3 = (TH1F*) PlotFile3->Get(Histo);
	  histo4 = (TH1F*) PlotFile4->Get(Histo);
	  //histo5 = (TH1F*) PlotFile5->Get(Histo);
	  histo6 = (TH1F*) PlotFile6->Get(Histo);
	  histo7 = (TH1F*) PlotFile7->Get(Histo);
	  //histo8 = (TH1F*) PlotFile8->Get(Histo);
	// @ set correct event numbers

	  Double_t n_events1 = 4992231 ; // TTJets                     
	  Double_t n_events2 = 24089991 ; // W->l+nu+Jets
	  Double_t n_events3 = 1273800 ; // Single top
	  Double_t n_events4 = 19925500 ; // Drell Yan

	  Double_t n_events6 = 103854 ; //  Z'-> t tbar 2TeV W = 200
	  Double_t n_events7 = 202573 ; //Z'-> t tbar 2TeV W = 20


	  Double_t lum = 1000 ; // arbitrary, set to data JSON eventually
	  Double_t xsTT = 831.76; // for 13 TeV from https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO used top mass as 172.5, uncertainties on twiki	
	  Double_t xsW = 20508.9;   // inclusive W  https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeV
	  Double_t xsST = 136.02 ;   // t channel top at 13 TeV https://twiki.cern.ch/twiki/bin/viewauth/CMS/SingleTopSigma
	  Double_t xsZ = 3205.6 ; // inclusive Z production https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeV
	  Double_t xsZprime = 10 ; // Arbitrary



	  TCanvas *canvas= new TCanvas("canvas","Plots",900,700);

	  canvas->cd(1);
	  canvas->SetFillColor(0);
	  canvas->GetFrame()->SetFillColor(0);
	  canvas->GetFrame()->SetBorderSize(12);

	  
	  histo1->Scale( xsTT * lum / n_events1 );  
	  histo1->SetFillColor(kRed+1);


	  histo2->Scale( xsW * lum / n_events2 ); 
	  histo2->SetFillColor(kGreen+1); 

	  histo3->Scale( xsST * lum / n_events3 ); 
	  histo3->SetFillColor(kMagenta+1);  

	  histo4->Scale( xsZ * lum / n_events4 ); 
	  histo4->SetFillColor(kBlue-4);  

	 
	 // histo5->SetMarkerStyle(20); 
	//  histo5->SetBinError();  // https://root.cern.ch/root/html/TH1.html#TH1:SetBinError

	  histo6->Scale( xsZprime * lum / n_events6 ); 
	  histo6->SetLineWidth(2); 
	  histo6->SetLineColor(kGray+1);

	  histo7->Scale( xsZprime * lum / n_events7 ); 
	  histo7->SetLineWidth(2);
	  histo7->SetLineColor(kBlack);
          
          //histo8->Sumw2();
          //histo8->Add(1, histo5);
	  //h/isto8->SetMarkerStyle(20);

	  hs->Add(histo3);
	  hs->Add(histo4);
	  hs->Add(histo2);
	  hs->Add(histo1);

	  hs->Draw();
	  hs->GetXaxis()->SetLabelSize(0.042);
	  hs->GetYaxis()->SetLabelSize(0.042);

	  hs->GetXaxis()->SetTitle(xAxisTitle); // change with histo
	  hs->GetXaxis()->CenterTitle();
	  hs->GetXaxis()->SetTitleOffset(1.);
	  hs->GetXaxis()->SetTitleSize(0.044);

	  hs->GetYaxis()->SetTitle("Events");
	  hs->GetYaxis()->SetTitleOffset(1.2);
	  hs->GetYaxis()->SetTitleSize(0.044);

	  hs->SetMaximum(maxY);
	  hs->GetXaxis()->SetLimits(minX, maxX); // change with histo
	  canvas->Modified();


	  histo6->Draw("same");
	  histo7->Draw("same");
	  //histo5->Draw("ep same");
	 // histo8->Draw("ep same");
	  canvas->Modified();

	  TLatex *tlx = new TLatex();
	  tlx->SetNDC();
	  tlx->SetTextFont(42);
	  tlx->SetTextSize(0.057);
	  tlx->DrawLatex(0.131, 0.905, "CMS Preliminary #sqrt{s}=13 TeV, 1 fb^{-1}");
	 // tlx->DrawLatex(0.77, 0.86, "#bf{CMS}");
	 // tlx->DrawLatex(0.72, 0.83, "#it{very preliminary}");
	  tlx->SetTextSize(0.025);

	  double yInfo2 = yInfoTop-0.042;
	  double yInfo3 = yInfo2-0.042;
	  double yInfo4 = yInfo3-0.042;
	  double yInfo5 = yInfo4-0.042;
	  double yInfo6 = yInfo5-0.042;
	  tlx->DrawLatex(xInfo, yInfoTop, "#bf{CMS Top Tagger}"); // same for AK4 and AK8
	  tlx->DrawLatex(xInfo, yInfo2 , "#bf{Madgraph}"); // same for AK4 and AK8                   
	  tlx->DrawLatex(xInfo, yInfo3, "#bf{AK R= 0.8}"); // 0.8 or 0.4 for AK8 and AK4              change with histo
	  tlx->DrawLatex(xInfo, yInfo4, "#bf{|#eta| < 2.4 }");  // same for AK4 and AK8
	  tlx->DrawLatex(xInfo, yInfo5, "#bf{P_{T} > 400 GeV}");// > 400 for AK8 and > 30 for AK4     change with histo
	  tlx->DrawLatex(xInfo, yInfo6, "#bf{25 ns}");  // change with 25 or 50 ns bunchcrossings     change with root files
	  canvas->Update();


	  TLegend *legend=new TLegend(legendLocation[0], legendLocation[1],legendLocation[2], legendLocation[3] ); 
	  canvas->cd(1);
	  legend->SetTextFont(42);
	  legend->SetTextSize(0.0395);
	  legend->SetBorderSize(0.0);
	  legend->SetMargin(0.3); 
	  //legend->AddEntry(histo5,"Electron Data", "p");
	  //legend->AddEntry(histo8,"Data", "p");
	  legend->AddEntry(histo7,"Z' 2 TeV #sigma = 10 pb, W = 20 GeV", "l");
	  legend->AddEntry(histo6,"Z' 2 TeV #sigma = 10 pb, W = 200 GeV", "l");
	  legend->AddEntry(histo1," t#bar{t}", "f");  
	  legend->AddEntry(histo2,"W + Jets", "f");
	  legend->AddEntry(histo4,"Z + Jets", "f");
	  legend->AddEntry(histo3,"Single Top", "f");
	  legend->Draw();  

	  // Get date for output file naming
	  time_t now = time(0);
	  tm *ltm = localtime(&now);
	  int mon = 1 + ltm->tm_mon;
	  string month = to_string(mon) ;
	  string day = to_string(ltm->tm_mday) ;
	  string year = to_string(1900 + ltm->tm_year) ;
	 
	  canvas->Update();
	  canvas->Modified();
	 // Name the stacked histogram
	  canvas->Print("./Stacked/QualityCuts_25ns_"+Histo+"_"+day+"_"+month+"_"+year+".png");

	}

}

