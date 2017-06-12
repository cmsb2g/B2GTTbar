// .L plotBkgdEst.C+
// Plot data-based plots:
// run(string file_label_fragment,string top tagging working point,bool use tt reweighting, [0 for nominal t-tag SF, 1 for up, -1 for dn])
// example:  run("20160420btagL_ht1000_pt500_WPB_alt40_alt260_bL_PUw","B",false,0)

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

void plotterBkgd(TString, TString, TString,TString, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, bool, bool, double, double, TString, TString, bool);
void plotterBkgdNoSR(TString, TString, TString, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, bool, bool, double, double, TString);
void plotterClosure(TString, TString, TString, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, bool, bool, double, double, TString);
void plotter2QCD(TString, TString, TString, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, bool, bool, double, double, TString);
void plotterSF(TString, TString, TString, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, bool, bool, double, double, TString);

// run("20160420btagL_ht1000_pt500_WPB_alt40_alt260_bL_PUw","B",false,0)
// run("20160512fullFix_ht950_pt400_WPB_alt40_alt260_bM_PUw","B", true, 0)
// run("20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw","B", true, 0)

void run(string label, string tWP, bool ttW, int topTagSFset=0 ){
	gStyle->SetOptStat(0);
	gROOT->UseCurrentStyle();
	gROOT->ForceStyle();

	gROOT->Reset();
	gROOT->ForceStyle(); 
	gROOT->SetBatch(); 
	
	// SETUP  
	// string infolder = "/Users/jdolen/NoBackup/B2G2016/V5/runs/";
	string infolder = "/uscms_data/d2/jdolen/B2G2016/CMSSW_8_0_26_patch2/src/Analysis/B2GTTbar/test/runs/";

	// string savefolder = "/Users/jdolen/NoBackup/B2G2016/V5/plots/bkgdEstPlots_20160512fullFix/";
	// string savefolder = "./bkgdEstPlots_"+label+"/";
	string savefolder ="./bkgdEstPlots_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_3/";
	TString savelabel = label;
	if (ttW) savelabel = savelabel + "_ttW";
	if (!ttW) savelabel = savelabel + "_nottW";
	if (topTagSFset==1)  savelabel = savelabel + "_tSFup";
	if (topTagSFset==-1) savelabel = savelabel + "_tSFdn";

	// OUTPUT FILE WITH HISTOGRAM TEMPLATES
	TString outfile_name = "templates_"+savelabel+".root";
    TFile * OutFile       = new TFile(  outfile_name       , "RECREATE");


    // SETUP INPUT FILES
	// string label = "20160420_ht1000_pt500_WPB_alt40_alt260_bM_PUw"
	string sdata   = infolder + "histsBkgdEst_"+label+"_TTw_nom_b2gtreeV5_JetHT_all.root";	                 
	string stt     = infolder + "histsBkgdEst_"+label+"_noTTw_nom_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root";
	if(ttW)   stt  = infolder + "histsBkgdEst_"+label+"_TTw_nom_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root";
	string sz10w   = infolder + "histsBkgdEst_"+label+"_TTw_nom_b2gtreeV5_ZprimeToTT_M-1000_W-100_RunIISummer16MiniAODv2.root";
	string sz12w   = infolder + "histsBkgdEst_"+label+"_TTw_nom_b2gtreeV5_ZprimeToTT_M-1250_W-125_RunIISummer16MiniAODv2.root";
	string sz15w   = infolder + "histsBkgdEst_"+label+"_TTw_nom_b2gtreeV5_ZprimeToTT_M-1500_W-150_RunIISummer16MiniAODv2.root";
	string sz20w   = infolder + "histsBkgdEst_"+label+"_TTw_nom_b2gtreeV5_ZprimeToTT_M-2000_W-200_RunIISummer16MiniAODv2.root";
	string sz25w   = infolder + "histsBkgdEst_"+label+"_TTw_nom_b2gtreeV5_ZprimeToTT_M-2500_W-250_RunIISummer16MiniAODv2.root";
	string sz30w   = infolder + "histsBkgdEst_"+label+"_TTw_nom_b2gtreeV5_ZprimeToTT_M-3000_W-300_RunIISummer16MiniAODv2.root";
	string sz35w   = infolder + "histsBkgdEst_"+label+"_TTw_nom_b2gtreeV5_ZprimeToTT_M-3500_W-350_RunIISummer16MiniAODv2.root";
	string sz40w   = infolder + "histsBkgdEst_"+label+"_TTw_nom_b2gtreeV5_ZprimeToTT_M-4000_W-400_RunIISummer16MiniAODv2.root";
	string sz45w   = infolder + "histsBkgdEst_"+label+"_TTw_nom_b2gtreeV5_ZprimeToTT_M-4500_W-450_RunIISummer16MiniAODv2.root";
	string sz50w   = infolder + "histsBkgdEst_"+label+"_TTw_nom_b2gtreeV5_ZprimeToTT_M-5000_W-500_RunIISummer16MiniAODv2.root";

	TFile * fData    = new TFile( sdata.c_str()   );
	TFile * fTT      = new TFile(   stt.c_str()   );
	TFile * fZp10w   = new TFile( sz10w.c_str()   );
	TFile * fZp12w   = new TFile( sz12w.c_str()   );
	TFile * fZp15w   = new TFile( sz15w.c_str()   );
	TFile * fZp20w   = new TFile( sz20w.c_str()   );
	TFile * fZp25w   = new TFile( sz25w.c_str()   );
	TFile * fZp30w   = new TFile( sz30w.c_str()   );
	TFile * fZp35w   = new TFile( sz35w.c_str()   );
	TFile * fZp40w   = new TFile( sz40w.c_str()   );
	TFile * fZp45w   = new TFile( sz45w.c_str()   );
	TFile * fZp50w   = new TFile( sz50w.c_str()   );
	



	// DEFINE HISTOGRAM NAMES AND LABELS
	vector <string> algo;
	vector <string> algo_label;
	// algo.push_back("CHS");      algo_label.push_back("CHS");
	algo.push_back("Puppi"); 	algo_label.push_back("PUPPI");
	vector <string> region;
	vector <string> region_label;
	region.push_back("SR");     region_label.push_back("t-tag");       
	// region.push_back("SB1");    region_label.push_back("sideband tag");        
	// region.push_back("SB2");    region_label.push_back("Sideband tag 2");        
	vector <string> dRap;
	vector <string> dRap_label;
	dRap.push_back("dRapHi");   dRap_label.push_back("#DeltaY>1.0"); 
	dRap.push_back("dRapLo");   dRap_label.push_back("#DeltaY<1.0"); 
	dRap.push_back("dRapIn");   dRap_label.push_back("#DeltaY inclusive"); 
	vector <string> nbtag;
	vector <string> nbtag_label;
	nbtag.push_back("0btag");    nbtag_label.push_back("0 b-tag"); 
	nbtag.push_back("1btag");    nbtag_label.push_back("1 b-tag"); 
	nbtag.push_back("2btag");    nbtag_label.push_back("2 b-tag"); 
	// nbtag.push_back("inclu");    nbtag_label.push_back("b-tag inclusive"); 
	vector <string> var;
	vector <string> axislabel;
	vector <int> rebin;
	// var.push_back("DijetMass"    );  axislabel.push_back("Dijet mass [GeV]"               );   rebin.push_back(10);        
	var.push_back("DijetMassMod" );  axislabel.push_back("Dijet mass (mod) [GeV]"         );   rebin.push_back(20);   
	var.push_back("HT"           );  axislabel.push_back("HT"                             );   rebin.push_back(10);   
	var.push_back("DeltaRap"     );  axislabel.push_back("#Delta Y"                       );   rebin.push_back(10);    
	var.push_back("JetP"         );  axislabel.push_back("Jet momentum [GeV]"             );   rebin.push_back(20);   
	var.push_back("JetPt"        );  axislabel.push_back("Jet p_{T} [GeV]"                );   rebin.push_back(10);    
	var.push_back("JetY"         );  axislabel.push_back("Jet rapidity"                   );   rebin.push_back(10);    
	// var.push_back("JetSDmass"    );  axislabel.push_back("Jet softdrop mass [GeV]"        );   rebin.push_back(10);     
	// var.push_back("JetTau32"     );  axislabel.push_back("Jet #tau_{32}"                  );   rebin.push_back( 5);     
	var.push_back("maxbdisc"     );  axislabel.push_back("Maximum subjet b-discriminant"  );   rebin.push_back( 2);    

	bool drawSignal = false;

	for (unsigned int i=0; i< algo.size()  ; i++){
	for (unsigned int j=0; j< region.size(); j++){
	for (unsigned int k=0; k< dRap.size()  ; k++){
	for (unsigned int l=0; l< nbtag.size() ; l++){
	for (unsigned int m=0; m< var.size()   ; m++){

		// SETUP HIST NAME AND LABEL

		string varS = var[m];
		string varB = var[m];
		if (var[m]=="DijetMassMod") varS="DijetMass";

		string s1 = "predDist_"+algo[i]+"_"+region[j]+"_"+dRap[k]+"_"+nbtag[l]+"_"+varS;
		string s2 = "predDist_"+algo[i]+"_"+region[j]+"_"+dRap[k]+"_"+nbtag[l]+"_"+varB+"_pred";
		string mypave1 = dRap_label[k]+", "+nbtag_label[l] ;
		string mypave2 = algo_label[i]+" "+region_label[j] ;

		if  (region[j]=="SR") drawSignal = true;
		else drawSignal = false;

		cout<<"drawSignal "<<drawSignal<<endl;

		cout<<"\nGETTING HIST : "<<s1<<endl;
		cout<<"\nGETTING HIST : "<<s2<<endl;

		// GET HISTOGRAMS
		TH1D * hData  = (TH1D*) fData  ->Get( s1.c_str() ); 
		TH1D * hBkgd  = (TH1D*) fData  ->Get( s2.c_str() ); 
		TH1D * hTT    = (TH1D*) fTT    ->Get( s1.c_str() ); 
		TH1D * hTT2   = (TH1D*) fTT    ->Get( s2.c_str() ); 
		TH1D * hZp10w = (TH1D*) fZp10w ->Get( s1.c_str() ); 
		TH1D * hZp12w = (TH1D*) fZp12w ->Get( s1.c_str() ); 
		TH1D * hZp15w = (TH1D*) fZp15w ->Get( s1.c_str() ); 
		TH1D * hZp20w = (TH1D*) fZp20w ->Get( s1.c_str() ); 
		TH1D * hZp25w = (TH1D*) fZp25w ->Get( s1.c_str() ); 
		TH1D * hZp30w = (TH1D*) fZp30w ->Get( s1.c_str() ); 
		TH1D * hZp35w = (TH1D*) fZp35w ->Get( s1.c_str() ); 
		TH1D * hZp40w = (TH1D*) fZp40w ->Get( s1.c_str() ); 

		hData  ->Sumw2();
		hBkgd  ->Sumw2();
		hTT    ->Sumw2();
		hTT2   ->Sumw2();
		hZp10w ->Sumw2();
		hZp12w ->Sumw2();
		hZp15w ->Sumw2();
		hZp20w ->Sumw2();
		hZp25w ->Sumw2();
		hZp30w ->Sumw2();
		hZp35w ->Sumw2();
		hZp40w ->Sumw2();

		// SETUP MC SCALING
		float lumi = 35922;
		
		float nttbar;
		nttbar =  77229341 + 78006311 ; // nom + backup  
		
		float kfactor = 0.82 ;
		// if (ttW){ kfactor = 0.9;    }
		// else    { kfactor = 0.7;    } //0.94

		float ttSF     = 1   ; 
		if (tWP=="A") ttSF = 1.07;     //	Working point A  tau32 < 0.80	SF 1.07	+0.10 -0.04
		if (tWP=="B") ttSF = 1.09;     //	Working point B  tau32 < 0.65	SF 1.09	+0.13 -0.05
		if (tWP=="C") ttSF = 1.09;     //	Working point C  tau32 < 0.54	SF 1.09	+0.10 -0.05
		if (topTagSFset == 1 && tWP=="A") ttSF +=0.10;
		if (topTagSFset == 1 && tWP=="B") ttSF +=0.13;
		if (topTagSFset == 1 && tWP=="C") ttSF +=0.10;
		if (topTagSFset ==-1 && tWP=="A") ttSF -=0.04;
		if (topTagSFset ==-1 && tWP=="B") ttSF -=0.05;
		if (topTagSFset ==-1 && tWP=="C") ttSF -=0.05;

		float average_tt_pt_weight = 1.0;
		if (ttW) average_tt_pt_weight = 0.82;


		hTT     ->Scale( 831.76 * ttSF * ttSF * lumi * kfactor / (nttbar + average_tt_pt_weight) );
		hTT2    ->Scale( 831.76 * ttSF * ttSF * lumi * kfactor / (nttbar + average_tt_pt_weight) );
		hZp10w  ->Scale(   1.0  * ttSF * ttSF * lumi * kfactor / 101056 );
		hZp12w  ->Scale(   1.0  * ttSF * ttSF * lumi * kfactor / 96845 );
		hZp15w  ->Scale(   1.0  * ttSF * ttSF * lumi * kfactor / 111108 );
		hZp20w  ->Scale(   1.0  * ttSF * ttSF * lumi * kfactor / 104119 );
		hZp25w  ->Scale(   1.0  * ttSF * ttSF * lumi * kfactor / 96077  );
		hZp30w  ->Scale(   1.0  * ttSF * ttSF * lumi * kfactor / 189164 );
		hZp35w  ->Scale(   1.0  * ttSF * ttSF * lumi * kfactor / 101022 );
		hZp40w  ->Scale(   1.0  * ttSF * ttSF * lumi * kfactor / 102411 );

		// SUBTRACT TT BKGDEST FROM BKGDEST
		hBkgd->Add(hTT2,-1);

		// REBIN
		hData   ->Rebin(rebin[m]); 
		hBkgd   ->Rebin(rebin[m]);
		hTT     ->Rebin(rebin[m]); 
		hTT2    ->Rebin(rebin[m]); 
		hZp10w  ->Rebin(rebin[m]); 
		hZp12w  ->Rebin(rebin[m]); 
		hZp15w  ->Rebin(rebin[m]); 
		hZp20w  ->Rebin(rebin[m]); 
		hZp25w  ->Rebin(rebin[m]); 
		hZp30w  ->Rebin(rebin[m]); 
		hZp35w  ->Rebin(rebin[m]); 
		hZp40w  ->Rebin(rebin[m]); 

    	cout<<"PLOTTING     : "<<s1<<endl;

    	// change xmax for certain hisotgrams
    	double xmax = -1; 
    	if (var[m]=="JetPt") xmax = 3000;


		plotterBkgd(   
	      s2,           //   TString histname, 
	      axislabel[m], //   TString histtitle,
	      mypave1,       //   TString pave, 
	      mypave2,       //   TString pave, 
	      hData, hTT, hBkgd, hTT2, hZp10w, hZp20w, hZp30w, hZp40w, 
	      true, 
	      true, 
	      xmax, 
	      1.4,
	      savefolder,
	      savelabel ,
	      drawSignal
	    );

		// SELECT HISTOGRAMS TO WRITE TO TEMPLATES     
		if (algo[i]=="Puppi" && var[m] =="DijetMassMod" && region[j] =="SR"){

			OutFile->cd();

			TString sinsert = dRap[k]+"_"+nbtag[l];
			TString sData   = "h_"+sinsert+"_Data"          ;
			TString sTT     = "h_"+sinsert+"_TT"            ;
			TString sBkgd   = "h_"+sinsert+"_BkgdEst"       ;
			TString sBkgdT  = "h_"+sinsert+"_Total"         ;
			TString sZp10w  = "h_"+sinsert+"_Zp10w"         ;
			TString sZp12w  = "h_"+sinsert+"_Zp12w"         ;
			TString sZp15w  = "h_"+sinsert+"_Zp15w"         ;
			TString sZp20w  = "h_"+sinsert+"_Zp20w"         ;
			TString sZp25w  = "h_"+sinsert+"_Zp25w"         ;
			TString sZp30w  = "h_"+sinsert+"_Zp30w"         ;
			TString sZp35w  = "h_"+sinsert+"_Zp35w"         ;
			TString sZp40w  = "h_"+sinsert+"_Zp40w"         ;

			TH1F *hTotal = (TH1F *) hBkgd->Clone("hTotal");
			hTotal->Add(hTT);

			// hData   ->SetName( sData   );
			hTT     ->SetName( sTT     );
			hBkgd   ->SetName( sBkgd   );
			hTotal  ->SetName( sBkgdT  );
			hZp10w  ->SetName( sZp10w  );
			hZp12w  ->SetName( sZp12w  );
			hZp15w  ->SetName( sZp15w  );
			hZp20w  ->SetName( sZp20w  );
			hZp25w  ->SetName( sZp25w  );
			hZp30w  ->SetName( sZp30w  );
			hZp35w  ->SetName( sZp35w  );
			hZp40w  ->SetName( sZp40w  );

			// hData   ->Write();
			hTT     ->Write();
			hBkgd   ->Write();
			hTotal  ->Write();
			// hTT2 ->Write();
			hZp10w  ->Write();
			hZp12w  ->Write();
			hZp15w  ->Write();
			hZp20w  ->Write();
			hZp25w  ->Write();
			hZp30w  ->Write();
			hZp35w  ->Write();
			hZp40w  ->Write();

		}// end if write histograms
		cout<<"Done with iteration"<<endl;
	}
	}
	}
	}
	}
    OutFile->cd();
    OutFile->Close();
}




void runClosure(){
	gStyle->SetOptStat(0);
	gROOT->UseCurrentStyle();
	gROOT->ForceStyle();

	gROOT->Reset();
	gROOT->ForceStyle(); 
	 gROOT->SetBatch(); 
	  
	// string savefolder = "/Users/jdolen/NoBackup/B2G2016/V5/plots/bkgdEstPlots/";
	string savefolder = "./bkgdEstPlots_20160529tagfixmistagfix_closurePt/";

	string infolder = "/uscms_data/d2/jdolen/B2G2016/CMSSW_8_0_26_patch2/src/Analysis/B2GTTbar/test/runs/";
	// string infolder = "/Users/jdolen/NoBackup/B2G2016/V5/runs/";
	// string sdata = infolder+"histsBkgdEst_20160523b_nom_PUw_crab_b2gtreeV5_JetHT_all.root";
	                      // 'histsKinemat_20170309btag_nom_PUw_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root
	// string stt   = infolder+"histsBkgdEst_20160523b_nom_PUw_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root";
	// string sqcd1  = infolder+"histsBkgdEst_20160526antiPupBugFix_nom_PUw_b2gtreeV5_QCD_Ptscaled.root";
	string sqcd1  = infolder+"histsBkgdEst_20160529tagfixmistagfix_nom_PUw_b2gtreeV5_QCD_Ptscaled.root";
	// string sqcd2  = infolder+"histsBkgdEst_20160523_nom_PUw_b2gtreeV5_QCD_Ptscaled.root";


	// TFile * fData   = new TFile(sdata.c_str() );
	// TFile * fTT     = new TFile(stt.c_str()   );
	// TFile * fZp10   = new TFile(stt.c_str()   );
	// TFile * fZp20   = new TFile(stt.c_str()   );
	// TFile * fZp30   = new TFile(stt.c_str()   );
	// TFile * fZp40   = new TFile(stt.c_str()   );
	TFile * fQCD   = new TFile(sqcd1.c_str()   );

	// vector<TString> histnames;
	// vector<TString> htitle;
	// vector<double>  hrebin;
	// vector<bool>    legs;
	// vector<bool>    QCDonTop;
	// vector<TString> pave;
	// vector<double>  xmax;
	// vector<double>  yscale;


	
	vector <string> algo;
	// algo.push_back("CHS");
	algo.push_back("Puppi");
	vector <string> region;
	region.push_back("SR");
	// region.push_back("SB1");
	// region.push_back("SB2");
	vector <string> dRap;
	vector <string> dRap_label;
	dRap.push_back("dRapHi");   dRap_label.push_back("#DeltaY>1.0"); 
	dRap.push_back("dRapLo");   dRap_label.push_back("#DeltaY<1.0"); 
	dRap.push_back("dRapIn");   dRap_label.push_back("#DeltaY inclusive"); 
	vector <string> nbtag;
	vector <string> nbtag_label;
	nbtag.push_back("0btag");        nbtag_label.push_back("0 b-tag"); 
	nbtag.push_back("1btag");        nbtag_label.push_back("1 b-tag"); 
	nbtag.push_back("2btag");        nbtag_label.push_back("2 b-tag"); 
	nbtag.push_back("inclu");        nbtag_label.push_back("b-tag inclusive"); 
	vector <string> var;
	vector <string> axislabel;
	vector <int> rebin;
	var.push_back("DijetMass"    );      rebin.push_back(10);    axislabel.push_back("Dijet mass [GeV]"               );      
	var.push_back("DijetMassMod" );      rebin.push_back(10);    axislabel.push_back("Dijet mass (mod) [GeV]"         );      
	var.push_back("HT"           );      rebin.push_back(10);    axislabel.push_back("HT"                             );      
	var.push_back("DeltaRap"     );      rebin.push_back(2);     axislabel.push_back("#Delta Y"                       );     
	var.push_back("JetP"         );      rebin.push_back(10);    axislabel.push_back("Jet momentum [GeV]"             );      
	var.push_back("JetPt"        );      rebin.push_back(2);     axislabel.push_back("Jet p_{T} [GeV]"                );     
	var.push_back("JetY"         );      rebin.push_back(2);     axislabel.push_back("Jet rapidity"                   );     
	// var.push_back("JetSDmass"    );   rebin.push_back();      axislabel.push_back("JetSDmass"                      );       
	// var.push_back("JetTau32"     );   rebin.push_back();      axislabel.push_back("JetTau32"                       );       
	var.push_back("maxbdisc"     );      rebin.push_back(2);     axislabel.push_back("Maximum subjet b-discriminant"  );     

	for (unsigned int i=0; i< algo.size()  ; i++){
	for (unsigned int j=0; j< region.size(); j++){
	for (unsigned int k=0; k< dRap.size()  ; k++){
	for (unsigned int l=0; l< nbtag.size() ; l++){
	for (unsigned int m=0; m< var.size()   ; m++){
	
	string s1 = "predDist_"+algo[i]+"_"+region[j]+"_"+dRap[k]+"_"+nbtag[l]+"_"+var[m];
	string s2 = s1+"_pred";
	// string s1 = "predDist_CHS_SR_dRapIn_inclu_JetP";
	// string s2 = "predDist_CHS_SR_dRapIn_inclu_JetP_pred";
	cout<<s1<<endl;
	// for (unsigned int i=0; i< histnames.size(); i++ ){
		TH1D * hData = (TH1D*) fQCD ->Get( s1.c_str() ); 
		TH1D * hBkgd = (TH1D*) fQCD ->Get( s2.c_str() ); 
		TH1D * hTT    = (TH1D*) fQCD   ->Get( s1.c_str() ); 
		TH1D * hTT2   = (TH1D*) fQCD   ->Get( s2.c_str() ); 
		TH1D * hZp10 = (TH1D*) fQCD ->Get( s1.c_str() ); 
		TH1D * hZp20 = (TH1D*) fQCD ->Get( s1.c_str() ); 
		TH1D * hZp30 = (TH1D*) fQCD ->Get( s1.c_str() ); 
		TH1D * hZp40 = (TH1D*) fQCD ->Get( s1.c_str() ); 



		float lumi = 35867 ;  //36220;//27220;
		float nttbar;
		nttbar =  77229341 + 78006311 ; // nom + backup  // 70452080;//;92925926;//92925926; //96834559.;//19665194.;
		float kfactor = 0.7;//0.94;//1;//0.94;
		float ttSF = 1;//0.89*0.89;
		double xs_zp30 = 1; // set to 1 to match semilept
		// hTT    ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );
		// hTT2   ->Scale( 831.76 * ttSF * lumi * kfactor / nttbar );

		hData ->Scale(lumi);
		hBkgd ->Scale(lumi);

		double rebinx = rebin[m];
		hData   ->Rebin(rebinx); 
		hBkgd   ->Rebin(rebinx);
		// hTT    ->Rebin(rebin); 
		// hTT2    ->Rebin(rebin); 
		// hZp10  ->Rebin(rebin); 
		// hZp20  ->Rebin(rebin); 
		// hZp30  ->Rebin(rebin); 
		// hZp40  ->Rebin(rebin); 

    	cout<<"plotting "<<s1<<endl;

    	double xmax = -1; 
    	if (var[m]=="JetPt") xmax = 3000;

		string mypave = dRap_label[k]+", "+nbtag_label[l] ;

		plotterClosure(   
	      s2,  //  TString histname, 
	      axislabel[m],  //  TString histtitle,
	      mypave,  //  TString pave, 
	      hData, hTT, hBkgd, hTT2, hZp10, hZp20, hZp30, hZp40, 
	      true, 
	      true, 
	      xmax, 
	      1.4,
	      savefolder 
	    );


	}
	}
	}
	}
	}
	 //    cout<<"done"<<endl;

	// }
}


void plotterBkgd(
  TString histname, 
  TString histtitle, 
  TString pave1, 
  TString pave2, 
  TH1D* hData, TH1D * hTT, TH1D* hBkgd, TH1D* hTT2, TH1D * hZp10, TH1D * hZp20, TH1D * hZp30, TH1D * hZp40, 
  bool legswitch, 
  bool invert, 
  double xmax, 
  double yscale,
  TString savefolder,
  TString savelabel,
  bool drawSignal
   )
{
    cout<<"plotterBkgd("<<histname<<")"<<endl;
    gStyle->SetOptStat(0);

	// SETUP CANVAS
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

	// SETUP UPPER PAD
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

	// SETUP DATA STYLE AND AXES
	double data_MAX = hData->GetMaximum() ;
	if (xmax>0) hData->GetXaxis()->SetRangeUser(0, xmax);
	hData->SetMaximum(yscale * data_MAX );
	hData->SetMinimum(0.01 ); //0.0001 );
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

	Int_t ci;      // for color index setting
	TColor *color; // for color definition with alpha
	ci = TColor::GetColor("#cc3333");
	hTT ->SetFillColor(ci);
	ci = TColor::GetColor("#660000");
	hTT ->SetLineWidth(2);
	hTT ->SetLineColor(ci);
	hBkgd->SetLineColor(kYellow+2);
	hBkgd->SetLineWidth(2);
	hBkgd->SetFillColor(kYellow);

	hZp10->SetFillColor(1);
	hZp10->SetFillStyle(0);
	hZp10->SetLineStyle(2);
	hZp10->SetLineWidth(2);

	hZp20->SetFillColor(1);
	hZp20->SetFillStyle(0);
	hZp20->SetLineStyle(2);
	hZp20->SetLineWidth(2);

	hZp30->SetFillColor(1);
	hZp30->SetFillStyle(0);
	hZp30->SetLineStyle(2);
	hZp30->SetLineWidth(2);

	hZp40->SetFillColor(1);
	hZp40->SetFillStyle(0);
	hZp40->SetLineStyle(2);
	hZp40->SetLineWidth(2);

	// DRAW
	hData->Draw("lep");//E0");

	THStack *stack = new THStack();
	if (!invert){
	stack->Add(hBkgd );
	stack->Add(hTT );
	}
	else{
	stack->Add( hTT );
	stack->Add(hBkgd );
	}
	stack->Draw("hist same");

	if (drawSignal){
		// hZp10->Draw("HISTsame");
		hZp20->Draw("HISTsame");
		hZp30->Draw("HISTsame");
		hZp40->Draw("HISTsame");
	}
	hData->Draw("lepsame");

	// LABELS
	TLatex *   tex1 = new TLatex(0.14,0.916,"#font[62]{CMS} #font[52]{Preliminary}");
	tex1->SetNDC();
	tex1->SetTextFont(42);
	tex1->SetTextSize(0.0825);
	tex1->SetLineWidth(2);
	tex1->Draw();
	TLatex *   tex2 = new TLatex(0.96,0.916,"36 fb^{-1} (13 TeV)");
	tex2->SetNDC();
	tex2->SetTextAlign(31);
	tex2->SetTextFont(42);
	tex2->SetTextSize(0.0825);
	tex2->SetLineWidth(2);
	tex2->Draw();
	TLatex *   tex3 = new TLatex(0.181,0.82225,pave1);
	tex3->SetNDC();
	tex3->SetTextAlign(13);
	tex3->SetTextFont(42);
	tex3->SetTextSize(0.045);
	tex3->SetLineWidth(2);
	tex3->Draw();
	TLatex *   tex4 = new TLatex(0.181,0.77225,pave2);
	tex4->SetNDC();
	tex4->SetTextAlign(13);
	tex4->SetTextFont(42);
	tex4->SetTextSize(0.045);
	tex4->SetLineWidth(2);
	tex4->Draw();

	// LEGEND
	// double leg1 =0.65; double leg2 =0.65; double leg3 =0.89; double leg4 =0.83;
	double leg1 =0.65; double leg2 =0.62; double leg3 =0.89; double leg4 =0.83;
	TLegend *leg = new TLegend(leg1, leg2, leg3, leg4);
	leg->SetTextSize(0.052);
	leg->AddEntry( hData , "Data"                   , "LP" );
	leg->AddEntry( hBkgd , "NTMJ bkg est."          , "F"  );
	leg->AddEntry(   hTT , "SM t#bar{t} simulation" , "F"  );
	leg->AddEntry( hZp30 , "Z` templates"           , "L"  );
	leg->SetFillColor(0);
	leg->SetLineColor(0); 
	leg->Draw("same");

	// FINISH PAD 1
	gPad->RedrawAxis();
	pad1->Modified();
	c1->cd();


	// START PAD 2 - RATIO PLOT
	TPad *pad2 = new TPad("pad2", "pad2",0,0,1,0.3333333);
	pad2->Draw();
	pad2->cd();
	// pad2->Range(-0.1792683,-1.570091,1.10122,1.899);
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


	// SETUP RATIO PLOTS

	// total background histogram
	TH1F *hTotal = (TH1F *) hBkgd->Clone("hTotal");
	hTotal->Sumw2();
	hTotal->Add(hTT);
	hTotal->SetFillColor(202);
	hTotal->SetFillStyle(3254);
	// int n_xbins = totalH->GetNbinsX();

	// ratio data / bkgd
	TH1F *hRatio = new TH1F();
	hRatio = (TH1F*) hData->Clone("hRatio");
	hRatio->Sumw2();
	hRatio->Divide( hRatio, hTotal );

	// ratio data / bkgd - define again
	TH1F *hRatio2 = new TH1F();
	hRatio2 = (TH1F*) hData->Clone("hRatio2");
	hRatio2->Sumw2();
	hRatio2->Divide(hRatio2, hTotal);

	// ratioErr -  bkgd over bkgd
	TH1F *hRatioErr = new TH1F();
	hRatioErr = (TH1F*) hTotal->Clone("hRatioErr");
	hRatioErr->Sumw2();
	hRatioErr->Divide(hRatioErr, hTotal);

	// SETUP DRAW
	hRatio->GetYaxis()->SetRangeUser(0.01,1.99);
	// ratioH->GetYaxis()->SetTitle("Data / Bkgd");
	// ratioH->GetYaxis()->SetTitleOffset(0.3);
	// ratioH->GetYaxis()->SetTitleSize(0.17);
	// ratioH->GetYaxis()->SetNdivisions(205);
	// ratioH->GetYaxis()->SetLabelSize(0.11);
	// ratioH->GetXaxis()->SetLabelSize(0.11);
	// ratioH->GetXaxis()->SetTitleSize(0.17);
	hRatio->GetXaxis()->SetTitle( histtitle );

	hRatio->SetStats(0);
	hRatio->SetFillColor(1);
	hRatio->SetFillStyle(0);
	hRatio->SetLineWidth(2);
	hRatio->SetLineColor(1);
	hRatio->SetMarkerStyle(20);
	hRatio->SetMarkerSize(0.8);
	hRatio->GetXaxis()->SetNdivisions(506);
	hRatio->GetXaxis()->SetLabelFont(42);
	hRatio->GetXaxis()->SetLabelOffset(0.015);
	hRatio->GetXaxis()->SetLabelSize(0.1275);
	hRatio->GetXaxis()->SetTitleSize(0.1425);
	hRatio->GetXaxis()->SetTickLength(0.09);
	hRatio->GetXaxis()->SetTitleOffset(1.15);
	hRatio->GetXaxis()->SetTitleFont(42);
	hRatio->GetYaxis()->SetTitle("Data/Bkg");
	hRatio->GetYaxis()->CenterTitle(true);
	hRatio->GetYaxis()->SetNdivisions(304);
	hRatio->GetYaxis()->SetLabelFont(42);
	hRatio->GetYaxis()->SetLabelSize(0.1275);
	hRatio->GetYaxis()->SetTitleSize(0.1425);
	hRatio->GetYaxis()->SetTickLength(0.045);
	hRatio->GetYaxis()->SetTitleOffset(0.45);
	hRatio->GetYaxis()->SetTitleFont(42);
	hRatio->GetZaxis()->SetLabelFont(42);
	hRatio->GetZaxis()->SetLabelSize(0.0425);
	hRatio->GetZaxis()->SetTitleSize(0.0475);
	hRatio->GetZaxis()->SetTitleFont(42);

	hRatioErr->SetFillStyle(1001);
	hRatioErr->SetFillColor(kGray);

	// DRAW
	hRatio    ->Draw("lepe0");
	hRatioErr ->Draw("E2 same");

	TF1 *line = new TF1("line", "1", -7000, 7000);
	line->SetLineColor(kBlack);
	line->SetLineStyle(2);
	line->SetLineWidth(2);
	line->Draw("same");
	hRatio->Draw("E0 same");


	// ratioH2->SetStats(0);
	// ratioH2->SetFillColor(1);
	// ratioH2->SetFillStyle(0);
	// ratioH2->SetLineWidth(2);
	// ratioH2->SetLineColor(3);
	// ratioH2->SetMarkerColor(3);
	// ratioH2->SetMarkerStyle(20);
	// ratioH2->SetMarkerSize(0.8);
	// ratioH2->Draw("samelepe0");


	// FINALIZE PAD 2
	gPad->RedrawAxis();
	 
	pad2->Modified();
	c1->cd();
	c1->Modified();
	c1->cd();
	c1->SetSelected(c1);     
	
	// SAVE HISTOGRAM
	TString histname2=histname;
	histname2 = histname2+"_"+savelabel+"_Bkgd";
	c1->SaveAs(savefolder+histname2+".pdf");   // c1->SaveAs(savefolder+histname2+".png");
	pad1->cd();
	hData->SetMaximum(30.0 * hData->GetMaximum() );
	pad1->SetLogy(1);
	c1->SaveAs(savefolder+histname2+"_log.pdf"); // c1->SaveAs(savefolder+histname2+"_log.png");
	pad1->SetLogy(0);


	//--------------------------------------------------------------------------------------------------------------------
	// DRAW AGAIN WITH NO DATA (blind templates)

	TCanvas *c2 = new TCanvas("c2", "c2",1,1,745,701);
	c2->cd();
	gStyle->SetOptFit(1);
	gStyle->SetOptStat(0);
	c2->SetHighLightColor(2);
	c2->Range(0,0,1,1);
	c2->SetFillColor(0);
	c2->SetBorderMode(0);
	c2->SetBorderSize(2);
	c2->SetTickx(1);
	c2->SetTicky(1);
	c2->SetLeftMargin(0.14);
	c2->SetRightMargin(0.04);
	c2->SetTopMargin(0.08);
	c2->SetBottomMargin(0.15);
	c2->SetFrameFillStyle(0);
	c2->SetFrameBorderMode(0);

	TPad *ppad1 = new TPad("ppad1", "ppad1",0,0.3333333,1,1);
	ppad1->Draw();
	ppad1->cd();
	// ppad1->Range(-0.1792683,-2.983224,1.10122,146.183);
	ppad1->SetFillColor(0);
	ppad1->SetBorderMode(0);
	ppad1->SetBorderSize(2);
	ppad1->SetTickx(1);
	ppad1->SetTicky(1);
	ppad1->SetLeftMargin(0.14);
	ppad1->SetRightMargin(0.04);
	ppad1->SetTopMargin(0.12);
	ppad1->SetBottomMargin(0.02);
	ppad1->SetFrameFillStyle(0);
	ppad1->SetFrameBorderMode(0);
	ppad1->SetFrameFillStyle(0);
	ppad1->SetFrameBorderMode(0);
	ppad1->SetLogy(0);

	// DRAW
	// Draw data with white markers to set the range etc.

	hData->GetYaxis()->SetTitle("Events");
	hData->GetYaxis()->SetTitleSize(0.065);
	hData->GetYaxis()->SetTitleOffset(0.9); // 0.7);
	hData->GetYaxis()->SetLabelSize(0.06);
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




	hData->SetMarkerColor(0);
	hData->SetLineColor(0);


	// hData->GetYaxis()->SetRangeUser(0.01,hData->GetMaximum()*1.5);
	hData->SetMaximum(yscale * data_MAX );
	hData->SetMinimum(0.01 ); //0.0001 );
	hData->Draw("lep");//E0");





	stack->SetMaximum(yscale * data_MAX );
	stack->Draw("histsame");

	if (drawSignal){
		hZp10->Draw("histsame");
		hZp20->Draw("histsame");
		hZp30->Draw("histsame");
		hZp40->Draw("histsame");
	}
	// LABELS
	tex1->Draw();
	tex2->Draw();
	tex3->Draw();
	tex4->Draw();

	// LEGEND
	leg->Draw("same");

	// FINALIZE PAD 1
	gPad->RedrawAxis();
	ppad1->Modified();
	
	// PAD2
	c2->cd();
	TPad *ppad2 = new TPad("ppad2", "ppad2",0,0,1,0.3333333);
	ppad2->Draw();
	ppad2->cd();
	// ppad2->Range(-0.1792683,-1.570091,1.10122,1.899);
	ppad2->SetFillColor(0);
	ppad2->SetBorderMode(0);
	ppad2->SetBorderSize(2);
	ppad2->SetTickx(1);
	ppad2->SetTicky(1);
	ppad2->SetLeftMargin(0.14);
	ppad2->SetRightMargin(0.04);
	ppad2->SetTopMargin(0);
	ppad2->SetBottomMargin(0.45);
	ppad2->SetFrameFillStyle(0);
	ppad2->SetFrameBorderMode(0);
	ppad2->SetFrameFillStyle(0);
	ppad2->SetFrameBorderMode(0);

	hRatio->SetStats(0);
	hRatio->SetFillColor(0);
	hRatio->SetFillStyle(0);
	hRatio->SetLineWidth(0);
	hRatio->SetLineColor(0);
	hRatio->SetMarkerColor(0);
	
	hRatioErr->SetFillStyle(1001);
	hRatioErr->SetFillColor(kGray);

	// DRAW
	hRatio    ->Draw("lepe0");
	hRatioErr ->Draw("E2same");
	line->Draw("same");

	// FINALIZE PAD2
	gPad->RedrawAxis();
	 
	ppad2->Modified();
	c2->cd();
	c2->Modified();
	c2->cd();
	c2->SetSelected(c2);     
	
	// SAVE HISTOGRAMS
	TString histname3=histname;
	histname3 = histname+"_"+savelabel+"_BkgdNoSR";
	c2->SaveAs(savefolder+histname3+".pdf");  // c2->SaveAs(savefolder+histname3+".png");
	ppad1->cd();
	ppad1->SetLogy(0);
	hData->SetMaximum(30.0 * data_MAX );
	stack->SetMaximum(30.0 * data_MAX );
	ppad1->SetLogy(1);
	c2->SaveAs(savefolder+histname3+"_log.pdf");  // c2->SaveAs(savefolder+histname3+"_log.png");

}


void plotterBkgdNoSR(
  TString histname, 
  TString histtitle, 
  TString pave, 
  TH1D* hData, TH1D * hTT, TH1D* hBkgd, TH1D* hTT2, TH1D * hZp10, TH1D * hZp20, TH1D * hZp30, TH1D * hZp40, 
  bool legswitch, 
  bool invert, 
  double xmax, 
  double yscale,
  TString savefolder )
{
  cout<<"plotter("<<histname<<endl;
    gStyle->SetOptStat(0);

	Int_t ci;      // for color index setting
	TColor *color; // for color definition with alpha
	ci = TColor::GetColor("#cc3333");
	hTT ->SetFillColor(ci);
	ci = TColor::GetColor("#660000");
	hTT ->SetLineWidth(2);
	hTT ->SetLineColor(ci);
	hBkgd->SetLineColor(kYellow+2);
	hBkgd->SetLineWidth(2);
	hBkgd->SetFillColor(kYellow);

	// hQCD2->SetLineColor(kGreen+2);
	// hQCD2->SetLineWidth(2);
	// hQCD2->SetFillColor(0);

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

	TPad *ppad1 = new TPad("ppad1", "ppad1",0,0.3333333,1,1);
	ppad1->Draw();
	ppad1->cd();
	// ppad1->Range(-0.1792683,-2.983224,1.10122,146.183);
	ppad1->SetFillColor(0);
	ppad1->SetBorderMode(0);
	ppad1->SetBorderSize(2);
	ppad1->SetTickx(1);
	ppad1->SetTicky(1);
	ppad1->SetLeftMargin(0.14);
	ppad1->SetRightMargin(0.04);
	ppad1->SetTopMargin(0.12);
	ppad1->SetBottomMargin(0.02);
	ppad1->SetFrameFillStyle(0);
	ppad1->SetFrameBorderMode(0);
	ppad1->SetFrameFillStyle(0);
	ppad1->SetFrameBorderMode(0);


	if (xmax>0) hData->GetXaxis()->SetRangeUser(0, xmax);
	hData->SetMaximum(yscale * hData->GetMaximum() );
	hData->SetMinimum(0.01 ); //0.0001 );
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

	hData->SetMarkerColor(0);
	hData->SetLineColor(0);

	hData->Draw("lep");//E0");

	hBkgd->Add(hTT2,-1);


	THStack *stack = new THStack();
	if (!invert){
	stack->Add(hBkgd );
	stack->Add(hTT );
	}
	else{
	stack->Add( hTT );
	stack->Add(hBkgd );
	}
	stack->Draw("hist same");

	// hQCD2->Add(hTT);
	// hQCD2->Draw("hist same");
	// hData->Draw("lepsame");

	//errors                                                                                                                                
	float xsErr_top = 0.15;
	float lumiErr_top = 0.027;
	float topTagErr_top = 2*(0.09/0.89);
	float totalTopErr = 0.0;
	float totalQCDErr = 0.0;
	float totalHistErr = 0.0;

	TH1F *totalH = (TH1F *) hBkgd->Clone("totalH");
	totalH->Add(hTT);

	totalH->SetFillColor(202);
	totalH->SetFillStyle(3254);

	// totalH->Draw("E2 same");

	int n_xbins = totalH->GetNbinsX();

	hZp10->SetFillColor(1);
	hZp10->SetFillStyle(0);
	hZp10->SetLineStyle(2);
	hZp10->SetLineWidth(2);

	hZp20->SetFillColor(1);
	hZp20->SetFillStyle(0);
	hZp20->SetLineStyle(2);
	hZp20->SetLineWidth(2);

	hZp30->SetFillColor(1);
	hZp30->SetFillStyle(0);
	hZp30->SetLineStyle(2);
	hZp30->SetLineWidth(2);

	hZp40->SetFillColor(1);
	hZp40->SetFillStyle(0);
	hZp40->SetLineStyle(2);
	hZp40->SetLineWidth(2);

	hZp10->Draw("HISTsame");
	hZp20->Draw("HISTsame");
	hZp30->Draw("HISTsame");
	hZp40->Draw("HISTsame");

	// hData->Draw("lepsame");

	TLatex *   tex = new TLatex(0.14,0.916,"#font[62]{CMS} #font[52]{Preliminary}");
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.0825);
	tex->SetLineWidth(2);
	tex->Draw();
	tex = new TLatex(0.96,0.916,"36 fb^{-1} (13 TeV)");
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

	// double leg1 =0.5; double leg2 =0.49; double leg3 =0.85; double leg4 =0.8;
	double leg1 =0.65; double leg2 =0.65; double leg3 =0.89; double leg4 =0.83;
	TLegend *leg = new TLegend(leg1, leg2, leg3, leg4);
	leg->SetTextSize(0.052);
	leg->AddEntry(hData, "Data", "lp");
	// leg->AddEntry(hQCD2, "QCD simulation (madgraph + pythia)", "f");
	leg->AddEntry(hBkgd, "NTMJ bkg est.", "F");
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
		peg->AddEntry(hBkgd, "NTMJ bkg est.", "F");

	peg->AddEntry(hTT, "SM t#bar{t} simulation", "f");

	// peg->AddEntry(hQCD2, "QCD simulation (madgraph + pythia)", "f");
	// peg->AddEntry("hZp30","Z' 3 TeV (#sigma=1 pb)","l");

	peg->SetFillColor(0);
	peg->SetLineColor(0);

	// if (legswitch)  peg->Draw("same");
	  // if (!legswitch) 
	  	leg->Draw("same");

	gPad->RedrawAxis();


	ppad1->Modified();
	c1->cd();





	TPad *ppad2 = new TPad("ppad2", "ppad2",0,0,1,0.3333333);
	ppad2->Draw();
	ppad2->cd();
	// ppad2->Range(-0.1792683,-1.570091,1.10122,1.899);
	ppad2->SetFillColor(0);
	ppad2->SetBorderMode(0);
	ppad2->SetBorderSize(2);
	ppad2->SetTickx(1);
	ppad2->SetTicky(1);
	ppad2->SetLeftMargin(0.14);
	ppad2->SetRightMargin(0.04);
	ppad2->SetTopMargin(0);
	ppad2->SetBottomMargin(0.45);
	ppad2->SetFrameFillStyle(0);
	ppad2->SetFrameBorderMode(0);
	ppad2->SetFrameFillStyle(0);
	ppad2->SetFrameBorderMode(0);

	TH1F *ratioH = new TH1F();
	ratioH = (TH1F*) hData->Clone("ratioH");


	TH1F *ratioH2 = new TH1F();
	ratioH2 = (TH1F*) hData->Clone("ratioH2");

	ratioH->Sumw2();
	ratioH->Divide(totalH, totalH);  //	ratioH->Divide(ratioH, totalH);


	ratioH2->Sumw2();
	ratioH2->Divide(hBkgd, hBkgd);  //ratioH2->Divide(ratioH2, hBkgd);



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


	// ratioH2->SetStats(0);
	// ratioH2->SetFillColor(1);
	// ratioH2->SetFillStyle(0);
	// ratioH2->SetLineWidth(2);
	// ratioH2->SetLineColor(3);
	// ratioH2->SetMarkerColor(3);
	// ratioH2->SetMarkerStyle(20);
	// ratioH2->SetMarkerSize(0.8);
	// ratioH2->Draw("samelepe0");



	gPad->RedrawAxis();
	 
	ppad2->Modified();
	c1->cd();
	c1->Modified();
	c1->cd();
	c1->SetSelected(c1);     

	if (invert) histname = histname+"_BkgdNoSR";
	c1->SaveAs(savefolder+histname+".pdf");
	c1->SaveAs(savefolder+histname+".png");
	// c1->SaveAs("runs/run20161010/kinPlots/Jetpt600HT1000_"+histname+".png");
	ppad1->cd();
	hData->SetMaximum(30.0 * hData->GetMaximum() );
	ppad1->SetLogy(1);
	c1->SaveAs(savefolder+histname+"_log.pdf");
	c1->SaveAs(savefolder+histname+"_log.png");
	// c1->SaveAs("runs/run20161010/kinPlots/Jetpt600HT1000_"+histname+"_log.png");

}


void plotterClosure(
  TString histname, 
  TString histtitle, 
  TString pave, 
  TH1D* hData, TH1D * hTT, TH1D* hBkgd, TH1D* hTT2, TH1D * hZp10, TH1D * hZp20, TH1D * hZp30, TH1D * hZp40, 
  bool legswitch, 
  bool invert, 
  double xmax, 
  double yscale,
  TString savefolder )
{
  cout<<"plotter("<<histname<<endl;
    gStyle->SetOptStat(0);

	Int_t ci;      // for color index setting
	TColor *color; // for color definition with alpha
	ci = TColor::GetColor("#cc3333");
	hTT ->SetFillColor(ci);
	ci = TColor::GetColor("#660000");
	hTT ->SetLineWidth(2);
	hTT ->SetLineColor(ci);
	hBkgd->SetLineColor(kYellow+2);
	hBkgd->SetLineWidth(2);
	hBkgd->SetFillColor(kYellow);

	// hQCD2->SetLineColor(kGreen+2);
	// hQCD2->SetLineWidth(2);
	// hQCD2->SetFillColor(0);

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


	if (xmax>0) hData->GetXaxis()->SetRangeUser(0, xmax);
	hData->SetMaximum(yscale * hData->GetMaximum() );
	hData->SetMinimum(0.000001 );
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

	// hTT.Add(hTT2,-1);


	THStack *stack = new THStack();
	if (!invert){
	stack->Add(hBkgd );
	// stack->Add(hTT );
	}
	else{
	// stack->Add( hTT );
	stack->Add(hBkgd );
	}
	stack->Draw("hist same");

	// hQCD2->Add(hTT);
	// hQCD2->Draw("hist same");
	hData->Draw("lepsame");

	//errors                                                                                                                                
	float xsErr_top = 0.15;
	float lumiErr_top = 0.027;
	float topTagErr_top = 2*(0.09/0.89);
	float totalTopErr = 0.0;
	float totalQCDErr = 0.0;
	float totalHistErr = 0.0;

	TH1F *totalH = (TH1F *) hBkgd->Clone("totalH");
	// totalH->Add(hTT);

	totalH->SetFillColor(202);
	totalH->SetFillStyle(3254);

	// totalH->Draw("E2 same");

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
	tex = new TLatex(0.96,0.916,"36.2 fb^{-1} (13 TeV)");
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

	// double leg1 =0.5; double leg2 =0.49; double leg3 =0.85; double leg4 =0.8;
	double leg1 =0.7; double leg2 =0.7; double leg3 =0.89; double leg4 =0.83;
	TLegend *leg = new TLegend(leg1, leg2, leg3, leg4);
	// leg->SetTextSize(0.057);
	leg->AddEntry(hData, "QCD SR", "lp");
	// leg->AddEntry(hQCD2, "QCD simulation (madgraph + pythia)", "f");
	leg->AddEntry(hBkgd, "QCD BkgdEst", "F");
	// leg->AddEntry(hTT, "SM t#bar{t} simulation", "f");
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

	peg->AddEntry(hData, "QCD SR", "lep");
	// peg->AddEntry(hTT, "SM t#bar{t} simulation", "f");

	// peg->AddEntry(hQCD2, "QCD simulation (madgraph + pythia)", "f");
	peg->AddEntry(hBkgd, "QCD BkgdEst", "F");
	// peg->AddEntry("hZp30","Z' 3 TeV (#sigma=1 pb)","l");

	peg->SetFillColor(0);
	peg->SetLineColor(0);

	// if (legswitch)  peg->Draw("same");
	  // if (!legswitch) 
	  	leg->Draw("same");

	gPad->RedrawAxis();


	pad1->Modified();
	c1->cd();





	TPad *pad2 = new TPad("pad2", "pad2",0,0,1,0.3333333);
	pad2->Draw();
	pad2->cd();
	// pad2->Range(-0.1792683,-1.570091,1.10122,1.899);
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
	ratioH = (TH1F*) hData->Clone("ratioH");


	TH1F *ratioH2 = new TH1F();
	ratioH2 = (TH1F*) hData->Clone("ratioH2");

	ratioH->Sumw2();
	ratioH->Divide(ratioH, totalH);

	ratioH2->Sumw2();
	ratioH2->Divide(ratioH2, hBkgd);



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


	// ratioH2->SetStats(0);
	// ratioH2->SetFillColor(1);
	// ratioH2->SetFillStyle(0);
	// ratioH2->SetLineWidth(2);
	// ratioH2->SetLineColor(3);
	// ratioH2->SetMarkerColor(3);
	// ratioH2->SetMarkerStyle(20);
	// ratioH2->SetMarkerSize(0.8);
	// ratioH2->Draw("samelepe0");



	gPad->RedrawAxis();
	 
	pad2->Modified();
	c1->cd();
	c1->Modified();
	c1->cd();
	c1->SetSelected(c1);     

	if (invert) histname = histname+"_Bkgd";
	c1->SaveAs(savefolder+"closure_"+histname+".pdf");
	c1->SaveAs(savefolder+"closure_"+histname+".png");
	// c1->SaveAs("runs/run20161010/kinPlots/Jetpt600HT1000_"+histname+".png");
	pad1->cd();
	hData->SetMaximum(30.0 * hData->GetMaximum() );
	pad1->SetLogy(1);
	c1->SaveAs(savefolder+"closureHT_"+histname+"_log.pdf");
	c1->SaveAs(savefolder+"closureHT_"+histname+"_log.png");
	// c1->SaveAs("runs/run20161010/kinPlots/Jetpt600HT1000_"+histname+"_log.png");

}


void plotterSF(
  TString histname, 
  TString histtitle, 
  TString pave, 
  TH1D* hData, TH1D * hTT, TH1D* hQCD, TH1D* hQCD2, TH1D * hZp10, TH1D * hZp20, TH1D * hZp30, TH1D * hZp40, 
  bool legswitch, 
  bool invert, 
  double xmax, 
  double yscale,
  TString savefolder )
{
  cout<<"plotter("<<histname<<endl;
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

	// hQCD2->SetLineColor(kGreen+2);
	// hQCD2->SetLineWidth(2);
	// hQCD2->SetFillColor(0);

	TCanvas *c1 = new TCanvas("c1", "c1",1,1,745,701);
	gStyle->SetOptFit(0);
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


	if (xmax>0) hData->GetXaxis()->SetRangeUser(0, xmax);
	hData->SetMaximum(yscale * hData->GetMaximum() );
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

	// stack->Add(hQCD );
	// stack->Add(hTT );

	hData->Add(hQCD,-1);

	hData->Draw("lep");//E0");

	// THStack *stack = new THStack();
	// if (!invert){
	// stack->Add(hQCD );
	// stack->Add(hTT );
	// }
	// else{
	// stack->Add( hTT );
	// stack->Add(hQCD );
	// }
	// stack->Draw("hist same");

	// hQCD2->Add(hTT);
	// hQCD2->Draw("hist same");
	hTT->Draw("hist same");
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

	// totalH->Draw("E2 same");

	int n_xbins = totalH->GetNbinsX();

	hZp30->SetFillColor(1);
	hZp30->SetFillStyle(0);
	hZp30->SetLineStyle(2);
	hZp30->SetLineWidth(2);

	hData->Draw("lepsame");

	cout<<"hData ->Integral (11,18) "<<hData ->Integral (11,18)<<endl;
	cout<<"hTT ->Integral (11,18)   "<<hTT ->Integral (11,18)<<endl;
	cout<<"SF mass                  = "<<hData ->Integral (11,18) / hTT ->Integral (11,18)<<endl;
	// cout<<"hData ->Integral (0,10) "<<hData ->Integral (0,10)<<endl;
	// cout<<"hTT ->Integral (0,10)   "<<hTT ->Integral (0,10)<<endl;
	// cout<<"SF TAU                  = "<<hData ->Integral (0,10) / hTT ->Integral (0,10)<<endl;


			TF1 *gfit = new TF1("Gaussian","gaus",110,230); 
		
			hData->Fit(gfit,"RQ"); // Fit histogram in range 
			double amp    = gfit->GetParameter(0);
			double eamp   = gfit->GetParError(0); 
			double mean   = gfit->GetParameter(1);
			double emean  = gfit->GetParError(1); 
			double width  = gfit->GetParameter(2);
			double ewidth = gfit->GetParError(2); 

			TF1 *gfit0 = new TF1("Gaussian","gaus",mean-1.75*width,mean+1.75*width); 
	
			hData->Fit(gfit0,"RQ"); // Fit histogram in range  R
			amp    = gfit0->GetParameter(0);
			eamp   = gfit0->GetParError(0); 
			mean   = gfit0->GetParameter(1);
			emean  = gfit0->GetParError(1); 
			width  = gfit0->GetParameter(2);
			ewidth = gfit0->GetParError(2); 



			TF1 *hfit = new TF1("Gaussian","gaus",110,230); 

			hTT->Fit(hfit,"RQ"); // Fit histogram in range 
			double hamp    = hfit->GetParameter(0);
			double heamp   = hfit->GetParError(0); 
			double hmean   = hfit->GetParameter(1);
			double hemean  = hfit->GetParError(1); 
			double hwidth  = hfit->GetParameter(2);
			double hewidth = hfit->GetParError(2); 

			TF1 *hfit0 = new TF1("Gaussian","gaus",hmean-1.5*hwidth,hmean+1.5*hwidth); 
		
			hTT->Fit(hfit0,"RQ"); // Fit histogram in range  R
			hamp    = hfit0->GetParameter(0);
			heamp   = hfit0->GetParError(0); 
			hmean   = hfit0->GetParameter(1);
			hemean  = hfit0->GetParError(1); 
			hwidth  = hfit0->GetParameter(2);
			hewidth = hfit0->GetParError(2); 


			cout<<"width data "<<width<<" width mc "<<hwidth<<endl;

			gfit0->SetLineColor(1);
			hfit0->SetLineColor(3);

			gfit0->SetLineStyle(2);
			hfit0->SetLineStyle(2);
			gfit0->Draw("same");
			hfit0->Draw("same");

	TLatex *   tex = new TLatex(0.14,0.916,"#font[62]{CMS} #font[52]{Preliminary}");
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.0825);
	tex->SetLineWidth(2);
	tex->Draw();
	tex = new TLatex(0.96,0.916,"36.2 fb^{-1} (13 TeV)");
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

	// double leg1 =0.5; double leg2 =0.49; double leg3 =0.85; double leg4 =0.8;
	double leg1 =0.7; double leg2 =0.7; double leg3 =0.89; double leg4 =0.83;
	TLegend *leg = new TLegend(leg1, leg2, leg3, leg4);
	// leg->SetTextSize(0.057);
	leg->AddEntry(hData, "Data", "lp");
	// leg->AddEntry(hQCD2, "QCD simulation (madgraph + pythia)", "f");
	leg->AddEntry(hQCD, "QCD simulation (pythia 8)", "F");
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

	// peg->AddEntry(hQCD2, "QCD simulation (madgraph + pythia)", "f");
	peg->AddEntry(hQCD, "QCD simulation (pythia 8)", "F");
	// peg->AddEntry("hZp30","Z' 3 TeV (#sigma=1 pb)","l");

	peg->SetFillColor(0);
	peg->SetLineColor(0);

	// if (legswitch)  peg->Draw("same");
	  // if (!legswitch) 
	  	// leg->Draw("same");

	gPad->RedrawAxis();


	pad1->Modified();
	c1->cd();





	TPad *pad2 = new TPad("pad2", "pad2",0,0,1,0.3333333);
	pad2->Draw();
	pad2->cd();
	// pad2->Range(-0.1792683,-1.570091,1.10122,1.899);
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
	ratioH = (TH1F*) hData->Clone("ratioH");


	TH1F *ratioH2 = new TH1F();
	ratioH2 = (TH1F*) hData->Clone("ratioH2");

	ratioH->Sumw2();
	ratioH->Divide(ratioH, hTT);

	// ratioH2->Sumw2();
	// ratioH2->Divide(ratioH2, hQCD2);



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


	// ratioH2->SetStats(0);
	// ratioH2->SetFillColor(1);
	// ratioH2->SetFillStyle(0);
	// ratioH2->SetLineWidth(2);
	// ratioH2->SetLineColor(3);
	// ratioH2->SetMarkerColor(3);
	// ratioH2->SetMarkerStyle(20);
	// ratioH2->SetMarkerSize(0.8);
	// ratioH2->Draw("samelepe0");



	gPad->RedrawAxis();
	 
	pad2->Modified();
	c1->cd();
	c1->Modified();
	c1->cd();
	c1->SetSelected(c1);     
	histname = histname + "_SF";
	if (invert) histname = histname+"_QCDonTop";
	c1->SaveAs(savefolder+histname+".pdf");
	c1->SaveAs(savefolder+histname+".png");
	// c1->SaveAs("runs/run20161010/kinPlots/Jetpt600HT1000_"+histname+".png");
	pad1->cd();
	hData->SetMaximum(30.0 * hData->GetMaximum() );
	pad1->SetLogy(1);
	c1->SaveAs(savefolder+histname+"_log.pdf");
	c1->SaveAs(savefolder+histname+"_log.png");
	// c1->SaveAs("runs/run20161010/kinPlots/Jetpt600HT1000_"+histname+"_log.png");

	delete pad1;
	delete pad2;
	delete c1;
}





void plotter2(
  TString histname, 
  TString histtitle, 
  TString pave, 
  TH1D* hData, TH1D * hTT, TH1D* hQCD, TH1D* hQCD2, TH1D * hZp10, TH1D * hZp20, TH1D * hZp30, TH1D * hZp40, 
  bool legswitch, 
  bool invert, 
  double xmax, 
  double yscale )
{
  cout<<"plotter("<<histname<<endl;
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

	hQCD2->SetLineColor(kGreen+2);
	hQCD2->SetLineWidth(2);
	// hQCD2->SetFillColor(0);

	TCanvas *c1 = new TCanvas("c1", "c1",1,1,745,701);
	// gStyle->SetOptFit(1);
	gStyle->SetOptFit(0);
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


	if (xmax>0) hData->GetXaxis()->SetRangeUser(0, xmax);
	hData->SetMaximum(yscale * hData->GetMaximum() );
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
	// if (!invert){
	stack->Add( hTT );
	stack->Add(hQCD );
	// }
	// else{
	// stack->Add( hTT );
	// stack->Add(hQCD );
	// }
	stack->Draw("hist same");

	hQCD2->Add(hTT);
	hQCD2->Draw("hist same");
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
	tex = new TLatex(0.96,0.916,"36.2 fb^{-1} (13 TeV)");
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

	// double leg1 =0.5; double leg2 =0.49; double leg3 =0.85; double leg4 =0.8;
	double leg1 =0.6; double leg2 =0.7; double leg3 =0.85; double leg4 =0.83;
	TLegend *leg = new TLegend(leg1, leg2, leg3, leg4);
	// leg->SetTextSize(0.057);
	leg->AddEntry(hData, "Data", "lp");
	leg->AddEntry(hQCD, "QCD simulation (madgraph + pythia)", "f");
	leg->AddEntry(hQCD2, "QCD simulation (pythia 8)", "L");
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

	peg->AddEntry(hQCD, "QCD simulation (madgraph + pythia)", "f");
	peg->AddEntry(hQCD2, "QCD simulation (pythia 8)", "L");
	// peg->AddEntry("hZp30","Z' 3 TeV (#sigma=1 pb)","l");

	peg->SetFillColor(0);
	peg->SetLineColor(0);

	// if (legswitch)  peg->Draw("same");
	  // if (!legswitch) 
	  	leg->Draw("same");

	gPad->RedrawAxis();


	pad1->Modified();
	c1->cd();





	TPad *pad2 = new TPad("pad2", "pad2",0,0,1,0.3333333);
	pad2->Draw();
	pad2->cd();
	// pad2->Range(-0.1792683,-1.570091,1.10122,1.899);
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
	ratioH = (TH1F*) hData->Clone("ratioH");


	TH1F *ratioH2 = new TH1F();
	ratioH2 = (TH1F*) hData->Clone("ratioH2");

	ratioH->Sumw2();
	ratioH->Divide(ratioH, totalH);

	ratioH2->Sumw2();
	ratioH2->Divide(ratioH2, hQCD2);



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


	ratioH2->SetStats(0);
	ratioH2->SetFillColor(1);
	ratioH2->SetFillStyle(0);
	ratioH2->SetLineWidth(2);
	ratioH2->SetLineColor(3);
	ratioH2->SetMarkerColor(3);
	ratioH2->SetMarkerStyle(20);
	ratioH2->SetMarkerSize(0.8);
	ratioH2->Draw("samelepe0");



	gPad->RedrawAxis();
	 
	pad2->Modified();
	c1->cd();
	c1->Modified();
	c1->cd();
	c1->SetSelected(c1);     

	if (invert) histname = histname+"_QCDonTop";
	c1->SaveAs("kinPlots/"+histname+".pdf");
	c1->SaveAs("kinPlots/"+histname+".png");
	// c1->SaveAs("runs/run20161010/kinPlots/Jetpt600HT1000_"+histname+".png");
	pad1->cd();
	hData->SetMaximum(30.0 * hData->GetMaximum() );
	pad1->SetLogy(1);
	c1->SaveAs("kinPlots/"+histname+"_log.pdf");
	c1->SaveAs("kinPlots/"+histname+"_log.png");
	// c1->SaveAs("runs/run20161010/kinPlots/Jetpt600HT1000_"+histname+"_log.png");

}










void plotter2QCD(
  TString histname, 
  TString histtitle, 
  TString pave, 
  TH1D* hData, TH1D * hTT, TH1D* hQCD1, TH1D* hQCD2, TH1D * hZp10, TH1D * hZp20, TH1D * hZp30, TH1D * hZp40, 
  bool legswitch, 
  bool invert, 
  double xmax, 
  double yscale,
  TString savefolder )
{
  cout<<"plotter("<<histname<<endl;
	


	//--- Canvas ---

	TCanvas *c1 = new TCanvas("c1", "c1",1,1,745,701);
	// gStyle->SetOptFit(1);
	gStyle->SetOptFit(0);
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

	//--- Pad ---

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

	//--- Histogram ---

	if (xmax>0) hData->GetXaxis()->SetRangeUser(0, xmax);
	hData->SetMaximum(yscale * hData->GetMaximum() );
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

	Int_t ci;                          // for color index setting
	TColor *color;                     // for color definition with alpha
	ci = TColor::GetColor("#cc3333");
	hTT ->SetFillColor(ci);
	ci = TColor::GetColor("#660000");
	hTT ->SetLineWidth(2);
	hTT ->SetLineColor(ci);
	
	hQCD1->SetLineColor(kGreen+2);
	hQCD1->SetLineWidth(2);

	hQCD2->SetLineColor(kBlue+2);
	hQCD2->SetLineWidth(2);

	//--- Draw ---

	hData->Draw("lep");

	THStack *stack = new THStack();
	stack->Add( hTT );
	stack->Add(hQCD1 );
	stack->Draw("hist same");

	hQCD2->Add(hTT);
	hQCD2->Draw("hist same");
	hData->Draw("lepsame");

	//--- Errors ---
	float xsErr_top = 0.15;
	float lumiErr_top = 0.027;
	float topTagErr_top = 2*(0.09/0.89);
	float totalTopErr = 0.0;
	float totalQCDErr = 0.0;
	float totalHistErr = 0.0;

	TH1F *totalH = (TH1F *) hQCD1->Clone("totalH");
	totalH->Add(hTT);
	totalH->SetFillColor(202);
	totalH->SetFillStyle(3254);
	// totalH->Draw("E2 same");

	// int n_xbins = totalH->GetNbinsX();

	//--- Signal ---
	hZp30->SetFillColor(1);
	hZp30->SetFillStyle(0);
	hZp30->SetLineStyle(2);
	hZp30->SetLineWidth(2);

	hData->Draw("lepsame");


	//--- TLatex ---

	TLatex *   tex = new TLatex(0.14,0.916,"#font[62]{CMS} #font[52]{Preliminary}");
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.0825);
	tex->SetLineWidth(2);
	tex->Draw();
	tex = new TLatex(0.96,0.916,"36.2 fb^{-1} (13 TeV)");
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
	// tex->SetTextSize(0.045);
	tex->SetTextSize(0.041);
	tex->SetLineWidth(2);
	tex->Draw();

	//--- Legend ---

	// Top-right of plot
	double leg1 =0.6; double leg2 =0.66; double leg3 =0.89; double leg4 =0.84; // double leg1 =0.5; double leg2 =0.49; double leg3 =0.85; double leg4 =0.8;
	TLegend *leg = new TLegend(leg1, leg2, leg3, leg4);
	leg->SetTextSize(0.038);
	leg->AddEntry(hData, "Data", "lp");
	leg->AddEntry(hQCD2, "QCD simulation (madgraph + pythia)", "L");
	leg->AddEntry(hQCD1, "QCD simulation (pythia 8)", "L");
	leg->AddEntry(hTT, "SM t#bar{t} simulation", "F");
	leg->SetFillColor(0);
	leg->SetLineColor(0);

	// Top-left of plot
	double peg1 =0.181; double peg2 =0.4642; double peg3 =0.468; double peg4 =0.7414;
	TLegend *peg = new TLegend(peg1, peg2, peg3, peg4,NULL,"brNDC");
	peg->SetBorderSize(0);
	peg->SetLineColor(1);
	peg->SetLineStyle(1);
	peg->SetLineWidth(1);
	peg->SetFillColor(0);
	peg->SetFillStyle(4001);

	peg->AddEntry(hData, "Data", "lep");
	peg->AddEntry(hQCD2, "QCD simulation (madgraph + pythia)", "L");
	peg->AddEntry(hQCD1, "QCD simulation (pythia 8)", "L");
	peg->AddEntry(hTT  , "SM t#bar{t} simulation", "f");
	// peg->AddEntry("hZp30","Z' 3 TeV (#sigma=1 pb)","l");

	peg->SetFillColor(0);
	peg->SetLineColor(0);

	if (legswitch)  peg->Draw("same");
	if (!legswitch) leg->Draw("same");

	gPad->RedrawAxis();

	pad1->Modified();
	c1->cd();



	//---------------- Ratio plot ------------------

	//--- Pad ---

	TPad *pad2 = new TPad("pad2", "pad2",0,0,1,0.3333333);
	pad2->Draw();
	pad2->cd();
	// pad2->Range(-0.1792683,-1.570091,1.10122,1.899);
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

	//--- Calculate ratio ---

	// Data / (tt + QCD1)
	TH1F *ratioH = new TH1F();
	ratioH = (TH1F*) hData->Clone("ratioH");
	ratioH->Sumw2();
	ratioH->Divide(ratioH, totalH);

	// Data / (tt + QCD2) - already added

	TH1F *ratioH2 = new TH1F();
	ratioH2 = (TH1F*) hData->Clone("ratioH2");
	ratioH2->Sumw2();
	ratioH2->Divide(ratioH2, hQCD2);



	TH1F *ratioErrH = new TH1F();
	ratioErrH = (TH1F*) totalH->Clone("ratioErrH");
	ratioErrH->Sumw2();
	ratioErrH->Divide(ratioErrH, totalH);



	//--- Draw ratio ---

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
	ratioH->SetLineColor(kGreen+2);
	ratioH->SetMarkerColor(kGreen+2);
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


	ratioH2->SetStats(0);
	ratioH2->SetFillColor(0);
	ratioH2->SetFillStyle(0);
	ratioH2->SetLineWidth(2);
	ratioH2->SetLineColor(kBlue+2);
	ratioH2->SetMarkerColor(kBlue+2);
	ratioH2->SetMarkerStyle(20);
	ratioH2->SetMarkerSize(0.8);
	ratioH2->Draw("samelepe0");



	gPad->RedrawAxis();
	 
	pad2->Modified();
	c1->cd();
	c1->Modified();
	c1->cd();
	c1->SetSelected(c1);     

	histname = histname+"_2QCD";
	if (invert) histname = histname+"_QCDonTop";
	c1->SaveAs(savefolder+histname+".pdf");
	c1->SaveAs(savefolder+histname+".png");
	// c1->SaveAs("runs/run20161010/kinPlots/Jetpt600HT1000_"+histname+".png");
	pad1->cd();
	hData->SetMaximum(30.0 * hData->GetMaximum() );
	pad1->SetLogy(1);
	c1->SaveAs(savefolder+histname+"_log.pdf");
	c1->SaveAs(savefolder+histname+"_log.png");
	// c1->SaveAs("runs/run20161010/kinPlots/Jetpt600HT1000_"+histname+"_log.png");
	delete pad1;
	delete pad2;
	delete c1;

}