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

//TO-DO-
// AK4 : h_ptAK4, h_mAK4, h_bdiscAK4, h_ptLep
// plot these: h_dRMin, h_2DCut






// uncomment the lines like ' cin >> InFile1;' if you want to plot different root files 
// but be sure to changes the lines like 'Double_t n_events1'


// SEARCH
//'change with histo' :to find differences btw each plot


void callHistos();
void StackedHistoMachineAK8_50ns_PUreweighted();
void plotter( TString HistoPlot);

TString xxx;
TString CalledHisto;

void StackedHistoMachineAK8_50ns_PUreweighted(){
    callHistos ();
}

void callHistos ( ){  
    cout << "****************************************************" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "****************************************************" << endl;
    cout << "****************************************************" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "****************************************************" << endl;
    cout << "====================================================" << endl;
    cout << "****************************************************" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "****************************************************" << endl;
    cout << "Welcome to the interactive Stacked Histogram Machine" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "Now featuring 13 TeV data from CMS accompanied by MC" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "Current optimized histograms to plot are as follows:" << endl;
    cout << "h_mAK8, h_mSDropAK8, h_mprunedAK8, h_mfilteredAK8   " << endl;
    cout << "h_mtrimmedAK8, h_minmassAK8, h_ptAK8, h_nsjAK8      " << endl;
    cout << "h_tau21AK8, h_tau32AK8                              " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "Please enter the UNIQUE name of your desired histo  " << endl;
    cout << "         (e.g. I want h_mAK8 so I enter m )         " << endl;  
    cout << "****************************************************" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "****************************************************" << endl;
    cin >> xxx ;
    CalledHisto = "h_"+xxx+"AK8";
    cout << "Your request for "+CalledHisto+" is being processed." << endl;
    cout << "           Your patience is appreciated.            " << endl;
    cout << "****************************************************" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "****************************************************" << endl;
    //TString CalledHisto = "h_mAK8";
    plotter( CalledHisto );
}

void plotter(TString HistoPlot){


TString xAxisTitle;  
double minX;
double maxX;
double maxY;
double xInfo;
double yInfoTop;
double legendLocation [4];

/*
    TString xAxisTitle = "M_{jet}\0(GeV)"; 
        minX = 10;
        maxX = 550; 
               xInfo = 0.301; //  location of plot description in normalized coordinates
               yInfoTop = 0.868;
    double legendLocation [4] = {0.440759, 0.320595, 0.750536, 0.611488 }; // {x1, y1, x2, y2} location of legend in normalized coordinates
*/
int histo = 0;

if (HistoPlot == "h_mAK8")
  histo =1;

if (HistoPlot == "h_mSDropAK8")
  histo =2;

if (HistoPlot == "h_mtrimmedAK8")
  histo =3;

if (HistoPlot == "h_mprunedAK8")
  histo =4;

if (HistoPlot == "h_mfilteredAK8")
  histo =5;

if (HistoPlot == "h_minmassAK8")
  histo =6;

if (HistoPlot == "h_tau32AK8")
  histo =7;

if (HistoPlot == "h_tau21AK8")
  histo =8;

if (HistoPlot == "h_nsjAK8")
  histo =9;

if (HistoPlot == "h_ptAK8" )
  histo =10;


switch (histo)
{
    case 1 :{
    xAxisTitle = "M_{jet} (GeV)"; 
    minX = 20;
    maxX = 600; 
    maxY = 60;
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
    minX = 20;
    maxX = 600; 
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
    minX = 10;
    maxX = 500; 
    xInfo = 0.341; //  location of plot description in normalized coordinates
    yInfoTop = 0.868;
    legendLocation[0] = 0.324777;
    legendLocation[1] = 0.450893;
    legendLocation[2] = 0.675223;
    legendLocation[3] = 0.651786;
    break;
    }
    case 4 :{
    xAxisTitle = "M_{jet} Pruned (GeV)";
    minX = 10;
    maxX = 500; 
    xInfo = 0.341; //  location of plot description in normalized coordinates
    yInfoTop = 0.868;
    legendLocation[0] = 0.324777;
    legendLocation[1] = 0.416667;
    legendLocation[2] = 0.675223;
    legendLocation[3] = 0.61756;
    break;
    }
    case 5 :{
    xAxisTitle = "M_{jet} Filtered (GeV)";
    minX = 10;
    maxX = 500; 
    xInfo = 0.341; //  location of plot description in normalized coordinates
    yInfoTop = 0.868;
    legendLocation[0] = 0.363839;
    legendLocation[1] = 0.434524;
    legendLocation[2] = 0.714286;
    legendLocation[3] = 0.635417;
    break;
    }
    case 6 :{
    xAxisTitle = "Minimum Mass Pairing of Subjets (GeV)"; 
    minX = 0;
    maxX = 200; 
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
    xInfo = 0.131; //  location of plot description in normalized coordinates
    yInfoTop = 0.868;
    legendLocation[0] = 0.290759;
    legendLocation[1] = 0.700595;
    legendLocation[2] = 0.60036;
    legendLocation[3] = 0.891488;
    cout << "This histo is n_tau21AK8 " << endl;
    break;
    }
    case 9 :{
    xAxisTitle = "Number of Subjets"; 
    minX = 0;
    maxX = 6; 
    xInfo = 0.131; //  location of plot description in normalized coordinates
    yInfoTop = 0.868;
    legendLocation[0] = 0.290759;
    legendLocation[1] = 0.700595;
    legendLocation[2] = 0.60036;
    legendLocation[3] = 0.891488;
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
  TString InFile1 = "July23-TTJets-50ns-sel1";  // TT Jets
  TString InFile2 = "July23-WJets-50ns-sel1";  // W + Jets                                                    
  TString InFile3 = "July23-ST-50ns-sel1";  // Single Top
  TString InFile4 = "July23-ZJets-50ns-sel1";  // Drell- Yan
  TString InFile5 = "July23-MuData-50ns-sel1";  //Muon Data
  TString InFile6 = "July23-Z-200-50ns-sel1"; // Z' W= 200
  TString InFile7 = "July23-Z-20-50ns-sel1"; // Z' W = 20
  TString InFile8 = "July23-ElData-50ns-sel1";  //Electron Data
/*
  cout << "Name of t #bar{t}->Jets Semi-Leptonic root file " << endl; 
  cin >> InFile1;
  cout <<"Name of W->Jets+l+nu Semi-Leptonic root file"<< endl;
  cin >> InFile2;
  cout <<"Name of Single Top t-channel Semi-Leptonic root file "<< endl;
  cin >> InFile3;
  cout <<"Name of Z->Jets+l+nu Semi-Leptonic root file"<< endl;
  cin >> InFile4;
//  cout <<"Name of DATA file Z'-> t #bar{t} Semi-Leptonic root file "<< endl;
//  cin >> InFile5;
  cout <<"Name of Signal MC, Z'-> t #bar{t} Semi-Leptonic W =200, root file "<< endl;
  cin >> InFile6;
  cout <<"Name of Signal MC, Z'-> t #bar{t} Semi-Leptonic W =20, root file "<< endl;
  cin >> InFile7;
*/

  TFile *PlotFile1 = TFile::Open("../"+InFile1+".root");       
  TFile *PlotFile2 = TFile::Open("../"+InFile2+".root");   
  TFile *PlotFile3 = TFile::Open("../"+InFile3+".root");       
  TFile *PlotFile4 = TFile::Open("../"+InFile4+".root");  
  TFile *PlotFile5 = TFile::Open("../"+InFile5+".root");       
  TFile *PlotFile6 = TFile::Open("../"+InFile6+".root");  
  TFile *PlotFile7 = TFile::Open("../"+InFile7+".root"); 
  TFile *PlotFile8 = TFile::Open("../"+InFile8+".root"); 

  TH1F* histo1;
  TH1F* histo2;
  TH1F* histo3;
  TH1F* histo4;
  TH1F* histo5;
  TH1F* histo6;
  TH1F* histo7;
  TH1F* histo8;

// weighted histos for Mudata
  TH1F* histo1m;
  TH1F* histo2m;
  TH1F* histo3m;
  TH1F* histo4m;

  TH1F* histo6m;
  TH1F* histo7m;
// weighted histos for Eldata
  TH1F* histo1e;
  TH1F* histo2e;
  TH1F* histo3e;
  TH1F* histo4e;

  TH1F* histo6e;
  TH1F* histo7e;

//  TString Plot = HistoPlot;
  histo1 = (TH1F*) PlotFile1->Get(HistoPlot);
  histo2 = (TH1F*) PlotFile2->Get(HistoPlot);
  histo3 = (TH1F*) PlotFile3->Get(HistoPlot);
  histo4 = (TH1F*) PlotFile4->Get(HistoPlot);
  histo5 = (TH1F*) PlotFile5->Get(HistoPlot);
  histo6 = (TH1F*) PlotFile6->Get(HistoPlot);
  histo7 = (TH1F*) PlotFile7->Get(HistoPlot);
  histo8 = (TH1F*) PlotFile8->Get(HistoPlot);

  histo1n = (TH1F*) PlotFile1->Get(h_NtrueIntPU);
  histo2n = (TH1F*) PlotFile2->Get(h_NtrueIntPU);
  histo3n = (TH1F*) PlotFile3->Get(h_NtrueIntPU);
  histo4n = (TH1F*) PlotFile4->Get(h_NtrueIntPU);
  histo5n = (TH1F*) PlotFile5->Get(h_NtrueIntPU);
  histo6n = (TH1F*) PlotFile6->Get(h_NtrueIntPU);
  histo7n = (TH1F*) PlotFile7->Get(h_NtrueIntPU);
  histo8n = (TH1F*) PlotFile8->Get(h_NtrueIntPU);

// for MuData - histo5n

  histo1rm = (TH1F*) histo5n.Divide(&histo1n);
  histo2rm = (TH1F*) histo5n.Divide(&histo2n);
  histo3rm = (TH1F*) histo5n.Divide(&histo3n);
  histo4rm = (TH1F*) histo5n.Divide(&histo4n);
  histo6rm = (TH1F*) histo5n.Divide(&histo6n);
  histo7rm = (TH1F*) histo5n.Divide(&histo7n);

// for ElData - histo8n

  histo1re = (TH1F*) histo8n.Divide(&histo1n);
  histo2re = (TH1F*) histo8n.Divide(&histo2n);
  histo3re = (TH1F*) histo8n.Divide(&histo3n);
  histo4re = (TH1F*) histo8n.Divide(&histo4n);
  histo6re = (TH1F*) histo8n.Divide(&histo6n);
  histo7re = (TH1F*) histo8n.Divide(&histo7n);

// Fill weighted Histos

// weighted histos

  int numBins1 = histo1->GetNbinsX()
  for (int j=0; j<numBins1; j++) {
    double weight1m = histo1rm->GetBinContent(j);
    double weight1e = histo1re->GetBinContent(j);
    double content1 = histo1->GetBinContent(j);
    histo1m->SetBinContent(content1, weight1m);
    histo1e->SetBinContent(content1, weight1e);
  }

  int numBins2 = histo2->GetNbinsX()
  for (int j=0; j<numBins2; j++) {
    double weight2m = histo2rm->GetBinContent(j);
    double weight2e = histo2re->GetBinContent(j);
    double content2 = histo2->GetBinContent(j);
    histo2m->SetBinContent(content2, weight2m);
    histo2e->SetBinContent(content2, weight2e);
  }
  int numBins3 = histo3->GetNbinsX()
  for (int j=0; j<numBins3; j++) {
    double weight3m = histo3rm->GetBinContent(j);
    double weight3e = histo3re->GetBinContent(j);
    double content3 = histo3->GetBinContent(j);
    histo3m->SetBinContent(content3, weight3m);
    histo3e->SetBinContent(content3, weight3e);
  }

  int numBins4 = histo4->GetNbinsX()
  for (int j=0; j<numBins4; j++) {
    double weight4m = histo4rm->GetBinContent(j);
    double weight4e = histo4re->GetBinContent(j);
    double content4 = histo4->GetBinContent(j);
    histo4m->SetBinContent(content4, weight4m);
    histo4e->SetBinContent(content4, weight4e);
  }

  int numBins6 = histo6->GetNbinsX()
  for (int j=0; j<numBins6; j++) {
    double weight6m = histo6rm->GetBinContent(j);
    double weight6e = histo6re->GetBinContent(j);
    double content6 = histo6->GetBinContent(j);
    histo6m->SetBinContent(content6, weight6m);
    histo6e->SetBinContent(content6, weight6e);
  }

  int numBins7 = histo7->GetNbinsX()
  for (int j=0; j<numBins7; j++) {
    double weight7m = histo7rm->GetBinContent(j);
    double weight7e = histo7re->GetBinContent(j);
    double content7 = histo7->GetBinContent(j);
    histo7m->SetBinContent(content7, weight7m);
    histo7e->SetBinContent(content7, weight7e);
  }

// @ set correct event numbers

  Double_t n_events1 = 4994250 ; // TTJets                     
  Double_t n_events2 = 24089991 ; // W->l+nu+Jets
  Double_t n_events3 = 3900814 ; // Single top
  Double_t n_events4 = 19925500 ; // Drell Yan

  Double_t n_events6 = 103854 ; //  Z'-> t tbar 2TeV W = 200
  Double_t n_events7 =  202573 ; //Z'-> t tbar 2TeV W = 20


  Double_t lum = 5.59 ; // From JSON
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

  
  histo1m->Scale( xsTT * lum / n_events1 );  
  histo1m->SetFillColor(kRed+1);

  histo1e->Scale( xsTT * lum / n_events1 );  
  histo1e->SetFillColor(kRed+1);

  histo2m->Scale( xsW * lum / n_events2 ); 
  histo2m->SetFillColor(kGreen+1); 

  histo2e->Scale( xsW * lum / n_events2 ); 
  histo2e->SetFillColor(kGreen+1); 

  histo3m->Scale( xsST * lum / n_events3 ); 
  histo3m->SetFillColor(kMagenta+1);  

  histo3e->Scale( xsST * lum / n_events3 ); 
  histo3e->SetFillColor(kMagenta+1); 

  histo4m->Scale( xsZ * lum / n_events4 ); 
  histo4m->SetFillColor(kBlue-4);  

  histo4e->Scale( xsZ * lum / n_events4 ); 
  histo4e->SetFillColor(kBlue-4); 
 
  histo5->SetMarkerStyle(20); 
//  histo5->SetBinError();  // https://root.cern.ch/root/html/TH1.html#TH1:SetBinError

  histo6m->Scale( xsZprime * lum / n_events6 ); 
  histo6m->SetLineWidth(2); 
  histo6m->SetLineColor(kGray+1);

  histo6e->Scale( xsZprime * lum / n_events6 ); 
  histo6e->SetLineWidth(2); 
  histo6e->SetLineColor(kGray+1);

  histo7m->Scale( xsZprime * lum / n_events7 ); 
  histo7m->SetLineWidth(2);
  histo7m->SetLineColor(kBlack);

  histo7e->Scale( xsZprime * lum / n_events7 ); 
  histo7e->SetLineWidth(2);
  histo7e->SetLineColor(kBlack);

  histo8->SetMarkerStyle(22);

  hs->Add(histo3m);
  hs->Add(histo4m);
  hs->Add(histo2m);
  hs->Add(histo1m);

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
  histo5->Draw("ep same");
//  histo8->Draw("ep same");
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
  tlx->DrawLatex(xInfo, yInfo6, "#bf{50 ns}");  // change with 25 or 50 ns bunchcrossings     change with root files
  canvas->Update();


  TLegend *legend=new TLegend(legendLocation[0], legendLocation[1],legendLocation[2], legendLocation[3] ); 
  canvas->cd(1);
  legend->SetTextFont(42);
  legend->SetTextSize(0.0395);
  legend->SetBorderSize(0.0);
  legend->SetMargin(0.3); 
  legend->AddEntry(histo5,"Muon Data", "p");
//  legend->AddEntry(histo8,"Electron Data", "p");
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
  canvas->Print("./Stacked/PUreweighted_50ns_"+CalledHisto+"_"+day+"_"+month+"_"+year+".png");

}



