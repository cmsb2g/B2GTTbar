void run(string histname, string histtitle, double xlo, double xhi ){


	using namespace std;
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetCanvasColor(kWhite);
	gStyle->SetCanvasDefH(500); //Height of canvas
	gStyle->SetCanvasDefW(800); //Width of canvas
	gStyle->SetCanvasDefX(0);   //POsition on screen
	gStyle->SetCanvasDefY(0);

	// For the Pad:
	gStyle->SetPadBorderMode(0);
	gStyle->SetPadColor(kWhite);
	gStyle->SetPadGridX(false);
	gStyle->SetPadGridY(false);
	gStyle->SetGridColor(0);
	gStyle->SetGridStyle(3);
	gStyle->SetGridWidth(1);

	// For the frame:
	gStyle->SetFrameBorderMode(0);
	gStyle->SetFrameBorderSize(1);
	gStyle->SetFrameFillColor(0);
	gStyle->SetFrameFillStyle(0);
	gStyle->SetFrameLineColor(1);
	gStyle->SetFrameLineStyle(1);
	gStyle->SetFrameLineWidth(1);

	// For the histo:
	gStyle->SetHistLineWidth(2);

	//For the fit/function:
	gStyle->SetOptFit(1);
	gStyle->SetFitFormat("5.4g");
	gStyle->SetFuncColor(2);
	gStyle->SetFuncStyle(1);
	gStyle->SetFuncWidth(1);

	//For the date:
	gStyle->SetOptDate(0);

	// For the statistics box:
	gStyle->SetOptFile(0);
	gStyle->SetOptStat(111111); // To display the mean and RMS:   SetOptStat("mr");
	gStyle->SetStatColor(kWhite);
	gStyle->SetStatFont(42);
	gStyle->SetStatFontSize(0.025);
	gStyle->SetStatTextColor(1);
	gStyle->SetStatFormat("6.4g");
	gStyle->SetStatBorderSize(1);
	gStyle->SetStatH(0.1);
	gStyle->SetStatW(0.15);

	// Margins:
	gStyle->SetPadTopMargin(0.09 );//0.14);
	gStyle->SetPadBottomMargin(0.14);
	gStyle->SetPadLeftMargin(0.17);//0.14);//0.16);
	gStyle->SetPadRightMargin(0.07);//13);//0.3);//0.16);

	// For the Global title:
	gStyle->SetTitleFont(42);
	gStyle->SetTitleColor(1);
	gStyle->SetTitleTextColor(1);
	gStyle->SetTitleFillColor(10);
	gStyle->SetTitleFontSize(0.04);
	gStyle->SetTitleW(0); // Set the width of the title box
	gStyle->SetTitleX(0.5); // Set the position of the title box
	gStyle->SetTitleY(0.94); // Set the position of the title box


	// For the axis titles:
	gStyle->SetTitleColor(1, "XYZ");
	gStyle->SetTitleFont(42, "XYZ");
	gStyle->SetTitleSize(0.05, "XYZ");
	gStyle->SetTitleXOffset(1.2);
	gStyle->SetTitleOffset(1.7, "Y"); // Another way to set the Offset

	// For the axis labels:
	gStyle->SetLabelColor(1, "XYZ");
	gStyle->SetLabelFont(42, "XYZ");
	gStyle->SetLabelOffset(0.007, "YZ");
	gStyle->SetLabelOffset(0.012, "X");
	gStyle->SetLabelSize(0.045, "XYZ");

	// For the axis:
	gStyle->SetAxisColor(1, "XYZ");
	gStyle->SetStripDecimals(kTRUE);
	gStyle->SetTickLength(0.03, "XYZ");
	gStyle->SetNdivisions(510, "XYZ");
	gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
	gStyle->SetPadTickY(1);

	// Change for log plots:
	gStyle->SetOptLogx(0);
	gStyle->SetOptLogy(0);
	gStyle->SetOptLogz(0);
	gStyle->SetPalette(1,0);

	gStyle->SetOptStat(0);
	gROOT->UseCurrentStyle();
	gROOT->ForceStyle();

	gROOT->Reset();
	 gROOT->ForceStyle(); 
	gROOT->SetBatch(); 


		TCanvas *c1 = new TCanvas("c1", "c1",1,1,745,701);


	string infolder = "/uscms_data/d2/jdolen/B2G2016/CMSSW_8_0_26_patch2/src/Analysis/B2GTTbar/test/runs/";

	string sdata   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_JetHT_all.root";
	string stt     = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root";
	
	string sZp10n   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_ZprimeToTT_M-1000_W-10_RunIISummer16MiniAODv2.root";
	string sZp12n   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_ZprimeToTT_M-1250_W-12p5_RunIISummer16MiniAODv2.root";
	string sZp15n   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_ZprimeToTT_M-1500_W-15_RunIISummer16MiniAODv2.root";
	string sZp20n   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_ZprimeToTT_M-2000_W-20_RunIISummer16MiniAODv2.root";
	string sZp25n   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_ZprimeToTT_M-2500_W-25_RunIISummer16MiniAODv2.root";
	string sZp30n   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_ZprimeToTT_M-3000_W-30_RunIISummer16MiniAODv2.root";
	string sZp35n   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_ZprimeToTT_M-3500_W-35_RunIISummer16MiniAODv2.root";
	string sZp40n   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_ZprimeToTT_M-4000_W-40_RunIISummer16MiniAODv2.root";
	string sZp45n   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_ZprimeToTT_M-4500_W-45_RunIISummer16MiniAODv2.root";
	string sZp50n   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_ZprimeToTT_M-5000_W-50_RunIISummer16MiniAODv2.root";
	string sZp10w   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_ZprimeToTT_M-1000_W-100_RunIISummer16MiniAODv2.root";
	string sZp12w   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_ZprimeToTT_M-1250_W-125_RunIISummer16MiniAODv2.root";
	string sZp15w   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_ZprimeToTT_M-1500_W-150_RunIISummer16MiniAODv2.root";
	string sZp20w   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_ZprimeToTT_M-2000_W-200_RunIISummer16MiniAODv2.root";
	string sZp25w   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_ZprimeToTT_M-2500_W-250_RunIISummer16MiniAODv2.root";
	string sZp30w   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_ZprimeToTT_M-3000_W-300_RunIISummer16MiniAODv2.root";
	string sZp35w   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_ZprimeToTT_M-3500_W-350_RunIISummer16MiniAODv2.root";
	string sZp40w   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_ZprimeToTT_M-4000_W-400_RunIISummer16MiniAODv2.root";
	string sZp45w   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_ZprimeToTT_M-4500_W-450_RunIISummer16MiniAODv2.root";
	string sZp50w   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_ZprimeToTT_M-5000_W-500_RunIISummer16MiniAODv2.root";
	string sZp10e   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_ZprimeToTT_M-1000_W-300_RunIISummer16MiniAODv2.root";
	string sZp20e   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_ZprimeToTT_M-2000_W-600_RunIISummer16MiniAODv2.root";
	string sZp40e   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_ZprimeToTT_M-4000_W-1200_RunIISummer16MiniAODv2.root";
	string sZp50e   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_ZprimeToTT_M-5000_W-1500_RunIISummer16MiniAODv2.root";
	string sRSG10   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_RSGluonToTT_M-1000_RunIISummer16MiniAODv2.root";
	string sRSG12   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_RSGluonToTT_M-1250_RunIISummer16MiniAODv2.root";
	string sRSG15   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_RSGluonToTT_M-1500_RunIISummer16MiniAODv2.root";
	string sRSG20   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_RSGluonToTT_M-2000_RunIISummer16MiniAODv2.root";
	string sRSG25   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_RSGluonToTT_M-2500_RunIISummer16MiniAODv2.root";
	string sRSG30   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_RSGluonToTT_M-3000_RunIISummer16MiniAODv2.root";
	string sRSG35   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_RSGluonToTT_M-3500_RunIISummer16MiniAODv2.root";
	string sRSG40   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_RSGluonToTT_M-4000_RunIISummer16MiniAODv2.root";
	string sRSG45   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_RSGluonToTT_M-4500_RunIISummer16MiniAODv2.root";
	string sRSG50   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_RSGluonToTT_M-5000_RunIISummer16MiniAODv2.root";

	string sqcd1   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_QCD_HTscaled.root";
	string sqcd2   = infolder+"histsKinemat_20160524full_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_QCD_Ptscaled.root";

	cout<<" sdata  "<<sdata <<endl; 
	cout<<" stt    "<<stt   <<endl; 
	cout<<" sqcd1  "<<sqcd1  <<endl; 
	cout<<" sqcd2  "<<sqcd2  <<endl; 

	// TFile * fData   = new TFile(sdata.c_str()   );
	// TFile * fQCD1   = new TFile(sqcd1.c_str()   );
	// TFile * fQCD2   = new TFile(sqcd2.c_str()   );
	// TFile * fTT     = new TFile(stt  .c_str()   );
	// TFile * fZp10   = new TFile(sZp10.c_str()   );
	// TFile * fZp20   = new TFile(sZp20.c_str()   );
	// TFile * fZp30   = new TFile(sZp30.c_str()   );
	// TFile * fZp40   = new TFile(sZp40.c_str()   );
	// TFile * fZp50   = new TFile(sZp50.c_str()   );


	TFile * fZp10n = new TFile( sZp10n .c_str() ); 
	TFile * fZp12n = new TFile( sZp12n .c_str() ); 
	TFile * fZp15n = new TFile( sZp15n .c_str() ); 
	TFile * fZp20n = new TFile( sZp20n .c_str() ); 
	TFile * fZp25n = new TFile( sZp25n .c_str() ); 
	TFile * fZp30n = new TFile( sZp30n .c_str() ); 
	TFile * fZp35n = new TFile( sZp35n .c_str() ); 
	TFile * fZp40n = new TFile( sZp40n .c_str() ); 
	TFile * fZp45n = new TFile( sZp45n .c_str() ); 
	TFile * fZp50n = new TFile( sZp50n .c_str() ); 
	TFile * fZp10w = new TFile( sZp10w .c_str() ); 
	TFile * fZp12w = new TFile( sZp12w .c_str() ); 
	TFile * fZp15w = new TFile( sZp15w .c_str() ); 
	TFile * fZp20w = new TFile( sZp20w .c_str() ); 
	TFile * fZp25w = new TFile( sZp25w .c_str() ); 
	TFile * fZp30w = new TFile( sZp30w .c_str() ); 
	TFile * fZp35w = new TFile( sZp35w .c_str() ); 
	TFile * fZp40w = new TFile( sZp40w .c_str() ); 
	TFile * fZp45w = new TFile( sZp45w .c_str() ); 
	TFile * fZp50w = new TFile( sZp50w .c_str() ); 
	TFile * fZp10e = new TFile( sZp10e .c_str() ); 
	TFile * fZp20e = new TFile( sZp20e .c_str() ); 
	TFile * fZp40e = new TFile( sZp40e .c_str() ); 
	TFile * fZp50e = new TFile( sZp50e .c_str() ); 
	TFile * fRSG10 = new TFile( sRSG10 .c_str() ); 
	TFile * fRSG12 = new TFile( sRSG12 .c_str() ); 
	TFile * fRSG15 = new TFile( sRSG15 .c_str() ); 
	TFile * fRSG20 = new TFile( sRSG20 .c_str() ); 
	TFile * fRSG25 = new TFile( sRSG25 .c_str() ); 
	TFile * fRSG30 = new TFile( sRSG30 .c_str() ); 
	TFile * fRSG35 = new TFile( sRSG35 .c_str() ); 
	TFile * fRSG40 = new TFile( sRSG40 .c_str() ); 
	TFile * fRSG45 = new TFile( sRSG45 .c_str() ); 
	TFile * fRSG50 = new TFile( sRSG50 .c_str() ); 

	TH1D * hZp10n = (TH1D*) fZp10n ->Get( histname.c_str() );
	TH1D * hZp12n = (TH1D*) fZp12n ->Get( histname.c_str() );
	TH1D * hZp15n = (TH1D*) fZp15n ->Get( histname.c_str() );
	TH1D * hZp20n = (TH1D*) fZp20n ->Get( histname.c_str() );
	TH1D * hZp25n = (TH1D*) fZp25n ->Get( histname.c_str() );
	TH1D * hZp30n = (TH1D*) fZp30n ->Get( histname.c_str() );
	TH1D * hZp35n = (TH1D*) fZp35n ->Get( histname.c_str() );
	TH1D * hZp40n = (TH1D*) fZp40n ->Get( histname.c_str() );
	TH1D * hZp45n = (TH1D*) fZp45n ->Get( histname.c_str() );
	TH1D * hZp50n = (TH1D*) fZp50n ->Get( histname.c_str() );
	TH1D * hZp10w = (TH1D*) fZp10w ->Get( histname.c_str() );
	TH1D * hZp12w = (TH1D*) fZp12w ->Get( histname.c_str() );
	TH1D * hZp15w = (TH1D*) fZp15w ->Get( histname.c_str() );
	TH1D * hZp20w = (TH1D*) fZp20w ->Get( histname.c_str() );
	TH1D * hZp25w = (TH1D*) fZp25w ->Get( histname.c_str() );
	TH1D * hZp30w = (TH1D*) fZp30w ->Get( histname.c_str() );
	TH1D * hZp35w = (TH1D*) fZp35w ->Get( histname.c_str() );
	TH1D * hZp40w = (TH1D*) fZp40w ->Get( histname.c_str() );
	TH1D * hZp45w = (TH1D*) fZp45w ->Get( histname.c_str() );
	TH1D * hZp50w = (TH1D*) fZp50w ->Get( histname.c_str() );
	TH1D * hZp10e = (TH1D*) fZp10e ->Get( histname.c_str() );
	TH1D * hZp20e = (TH1D*) fZp20e ->Get( histname.c_str() );
	TH1D * hZp40e = (TH1D*) fZp40e ->Get( histname.c_str() );
	TH1D * hZp50e = (TH1D*) fZp50e ->Get( histname.c_str() );
	TH1D * hRSG10 = (TH1D*) fRSG10 ->Get( histname.c_str() );
	TH1D * hRSG12 = (TH1D*) fRSG12 ->Get( histname.c_str() );
	TH1D * hRSG15 = (TH1D*) fRSG15 ->Get( histname.c_str() );
	TH1D * hRSG20 = (TH1D*) fRSG20 ->Get( histname.c_str() );
	TH1D * hRSG25 = (TH1D*) fRSG25 ->Get( histname.c_str() );
	TH1D * hRSG30 = (TH1D*) fRSG30 ->Get( histname.c_str() );
	TH1D * hRSG35 = (TH1D*) fRSG35 ->Get( histname.c_str() );
	TH1D * hRSG40 = (TH1D*) fRSG40 ->Get( histname.c_str() );
	TH1D * hRSG45 = (TH1D*) fRSG45 ->Get( histname.c_str() );
	TH1D * hRSG50 = (TH1D*) fRSG50 ->Get( histname.c_str() );


 if (!hZp10n) {cout<<"Did not get hZp10n"<<endl; return; }
 if (!hZp12n) {cout<<"Did not get hZp12n"<<endl; return; }
 if (!hZp15n) {cout<<"Did not get hZp15n"<<endl; return; }
 if (!hZp20n) {cout<<"Did not get hZp20n"<<endl; return; }
 if (!hZp25n) {cout<<"Did not get hZp25n"<<endl; return; }
 if (!hZp30n) {cout<<"Did not get hZp30n"<<endl; return; }
 if (!hZp35n) {cout<<"Did not get hZp35n"<<endl; return; }
 if (!hZp40n) {cout<<"Did not get hZp40n"<<endl; return; }
 if (!hZp45n) {cout<<"Did not get hZp45n"<<endl; return; }
 if (!hZp50n) {cout<<"Did not get hZp50n"<<endl; return; }
 if (!hZp10w) {cout<<"Did not get hZp10w"<<endl; return; }
 if (!hZp12w) {cout<<"Did not get hZp12w"<<endl; return; }
 if (!hZp15w) {cout<<"Did not get hZp15w"<<endl; return; }
 if (!hZp20w) {cout<<"Did not get hZp20w"<<endl; return; }
 if (!hZp25w) {cout<<"Did not get hZp25w"<<endl; return; }
 if (!hZp30w) {cout<<"Did not get hZp30w"<<endl; return; }
 if (!hZp35w) {cout<<"Did not get hZp35w"<<endl; return; }
 if (!hZp40w) {cout<<"Did not get hZp40w"<<endl; return; }
 if (!hZp45w) {cout<<"Did not get hZp45w"<<endl; return; }
 if (!hZp50w) {cout<<"Did not get hZp50w"<<endl; return; }
 if (!hZp10e) {cout<<"Did not get hZp10e"<<endl; return; }
 if (!hZp20e) {cout<<"Did not get hZp20e"<<endl; return; }
 if (!hZp40e) {cout<<"Did not get hZp40e"<<endl; return; }
 if (!hZp50e) {cout<<"Did not get hZp50e"<<endl; return; }
 if (!hRSG10) {cout<<"Did not get hRSG10"<<endl; return; }
 if (!hRSG12) {cout<<"Did not get hRSG12"<<endl; return; }
 if (!hRSG15) {cout<<"Did not get hRSG15"<<endl; return; }
 if (!hRSG20) {cout<<"Did not get hRSG20"<<endl; return; }
 if (!hRSG25) {cout<<"Did not get hRSG25"<<endl; return; }
 if (!hRSG30) {cout<<"Did not get hRSG30"<<endl; return; }
 if (!hRSG35) {cout<<"Did not get hRSG35"<<endl; return; }
 if (!hRSG40) {cout<<"Did not get hRSG40"<<endl; return; }
 if (!hRSG45) {cout<<"Did not get hRSG45"<<endl; return; }
 if (!hRSG50) {cout<<"Did not get hRSG50"<<endl; return; }

hZp10n->SetLineColor(99);
hZp12n->SetLineColor(94);
hZp15n->SetLineColor(91);
hZp20n->SetLineColor(84);
hZp25n->SetLineColor(79);
hZp30n->SetLineColor(74);
hZp35n->SetLineColor(69);
hZp40n->SetLineColor(64);
hZp45n->SetLineColor(59);
hZp50n->SetLineColor(54);
hZp10w->SetLineColor(99);
hZp12w->SetLineColor(94);
hZp15w->SetLineColor(91);
hZp20w->SetLineColor(84);
hZp25w->SetLineColor(79);
hZp30w->SetLineColor(74);
hZp35w->SetLineColor(69);
hZp40w->SetLineColor(64);
hZp45w->SetLineColor(59);
hZp50w->SetLineColor(54);
hZp10e->SetLineColor(99);
hZp20e->SetLineColor(84);
hZp40e->SetLineColor(64);
hZp50e->SetLineColor(54);
hRSG10->SetLineColor(99);
hRSG12->SetLineColor(94);
hRSG15->SetLineColor(91);
hRSG20->SetLineColor(84);
hRSG25->SetLineColor(79);
hRSG30->SetLineColor(74);
hRSG35->SetLineColor(69);
hRSG40->SetLineColor(64);
hRSG45->SetLineColor(59);
hRSG50->SetLineColor(54);

int rebin = 5;
hZp10n->Rebin(rebin);
hZp12n->Rebin(rebin);
hZp15n->Rebin(rebin);
hZp20n->Rebin(rebin);
hZp25n->Rebin(rebin);
hZp30n->Rebin(rebin);
hZp35n->Rebin(rebin);
hZp40n->Rebin(rebin);
hZp45n->Rebin(rebin);
hZp50n->Rebin(rebin);
hZp10w->Rebin(rebin);
hZp12w->Rebin(rebin);
hZp15w->Rebin(rebin);
hZp20w->Rebin(rebin);
hZp25w->Rebin(rebin);
hZp30w->Rebin(rebin);
hZp35w->Rebin(rebin);
hZp40w->Rebin(rebin);
hZp45w->Rebin(rebin);
hZp50w->Rebin(rebin);
hZp10e->Rebin(rebin);
hZp20e->Rebin(rebin);
hZp40e->Rebin(rebin);
hZp50e->Rebin(rebin);
hRSG10->Rebin(rebin);
hRSG12->Rebin(rebin);
hRSG15->Rebin(rebin);
hRSG20->Rebin(rebin);
hRSG25->Rebin(rebin);
hRSG30->Rebin(rebin);
hRSG35->Rebin(rebin);
hRSG40->Rebin(rebin);
hRSG45->Rebin(rebin);
hRSG50->Rebin(rebin);

//------------------------------------------

hZp25n->SetStats(0);
hZp25n->SetTitle(histtitle.c_str());

hZp10n->Scale( hZp25n->Integral()/   hZp10n->Integral() );
hZp12n->Scale( hZp25n->Integral()/   hZp12n->Integral() );
hZp15n->Scale( hZp25n->Integral()/   hZp15n->Integral() );
hZp20n->Scale( hZp25n->Integral()/   hZp20n->Integral() );
hZp25n->Scale( hZp25n->Integral()/   hZp25n->Integral() );
hZp30n->Scale( hZp25n->Integral()/   hZp30n->Integral() );
hZp35n->Scale( hZp25n->Integral()/   hZp35n->Integral() );
hZp40n->Scale( hZp25n->Integral()/   hZp40n->Integral() );
hZp45n->Scale( hZp25n->Integral()/   hZp45n->Integral() );
hZp50n->Scale( hZp25n->Integral()/   hZp50n->Integral() );

if (xhi>0) hZp25n->GetXaxis()->SetRangeUser(xlo,xhi);
hZp25n->SetMaximum(1.3* hZp10n->GetMaximum() );
hZp25n->Draw("HIST");
hZp10n->Draw("HISTsame");
hZp12n->Draw("HISTsame");
hZp15n->Draw("HISTsame");
hZp20n->Draw("HISTsame");
hZp25n->Draw("HISTsame");
hZp30n->Draw("HISTsame");
hZp35n->Draw("HISTsame");
hZp40n->Draw("HISTsame");
hZp45n->Draw("HISTsame");
hZp50n->Draw("HISTsame");

double leg1 =0.54; double leg2 =0.53; double leg3 =0.88; double leg4 =0.87;
TLegend *leg = new TLegend(leg1, leg2, leg3, leg4);
leg->SetTextSize(0.036);
leg->SetMargin(0.2);
leg->AddEntry( hZp10n , "Z` (1 TeV) narrow"                   , "L" );
leg->AddEntry( hZp12n , "Z` (1.25 TeV) narrow"                   , "L" );
leg->AddEntry( hZp15n , "Z` (1.5 TeV) narrow"                   , "L" );
leg->AddEntry( hZp20n , "Z` (2 TeV) narrow"                   , "L" );
leg->AddEntry( hZp25n , "Z` (2.5 TeV) narrow"                   , "L" );
leg->AddEntry( hZp30n , "Z` (3 TeV) narrow"                   , "L" );
leg->AddEntry( hZp35n , "Z` (3.5 TeV) narrow"                   , "L" );
leg->AddEntry( hZp40n , "Z` (4 TeV) narrow"                   , "L" );
leg->AddEntry( hZp45n , "Z` (4.5 TeV) narrow"                   , "L" );
leg->AddEntry( hZp50n , "Z` (5 TeV) narrow"                   , "L" );
leg->SetFillColor(0);
leg->SetLineColor(0); 
leg->Draw("same");

TLatex *   h1_tex = new TLatex(0.2,0.84,"#font[62]{CMS}");// #font[52]{Simulation Preliminary}");
h1_tex->SetNDC();
h1_tex->SetTextFont(42);
h1_tex->SetTextSize(0.0455); //0.0625
h1_tex->SetLineWidth(2);
h1_tex->Draw();
TLatex *   h2_tex = new TLatex(0.2,0.79,"#font[52]{Simulation Preliminary}");
h2_tex->SetNDC();
h2_tex->SetTextFont(42);
h2_tex->SetTextSize(0.04); //0.0625
h2_tex->SetLineWidth(2);
h2_tex->Draw();

gPad->RedrawAxis();	 

savename = "plotsSignal/ZPnarrow_"+histname+".pdf";
savename_log = "plotsSignal/ZPnarrow_"+histname+"_log.pdf";
c1->SaveAs( savename .c_str() );
hZp25n->SetMaximum(40* hZp10n->GetMaximum() );
c1->SetLogy();
c1->SaveAs( savename_log .c_str() );
c1->SetLogy(0);



//------------------------------------------

hZp25w->SetStats(0);
hZp25w->SetTitle(histtitle.c_str());

hZp10w->Scale( hZp25w->Integral()/   hZp10w->Integral() );
hZp12w->Scale( hZp25w->Integral()/   hZp12w->Integral() );
hZp15w->Scale( hZp25w->Integral()/   hZp15w->Integral() );
hZp20w->Scale( hZp25w->Integral()/   hZp20w->Integral() );
hZp25w->Scale( hZp25w->Integral()/   hZp25w->Integral() );
hZp30w->Scale( hZp25w->Integral()/   hZp30w->Integral() );
hZp35w->Scale( hZp25w->Integral()/   hZp35w->Integral() );
hZp40w->Scale( hZp25w->Integral()/   hZp40w->Integral() );
hZp45w->Scale( hZp25w->Integral()/   hZp45w->Integral() );
hZp50w->Scale( hZp25w->Integral()/   hZp50w->Integral() );

if (xhi>0) hZp25w->GetXaxis()->SetRangeUser(xlo,xhi);
hZp25w->SetMaximum(1.3* hZp10w->GetMaximum() );
hZp25w->Draw("HIST");
hZp10w->Draw("HISTsame");
hZp12w->Draw("HISTsame");
hZp15w->Draw("HISTsame");
hZp20w->Draw("HISTsame");
hZp25w->Draw("HISTsame");
hZp30w->Draw("HISTsame");
hZp35w->Draw("HISTsame");
hZp40w->Draw("HISTsame");
hZp45w->Draw("HISTsame");
hZp50w->Draw("HISTsame");

TLegend *legB = new TLegend(leg1, leg2, leg3, leg4);
legB->SetTextSize(0.036);
legB->SetMargin(0.2);
legB->AddEntry( hZp10w , "Z` (1 TeV) wide"                   , "L" );
legB->AddEntry( hZp12w , "Z` (1.25 TeV) wide"                   , "L" );
legB->AddEntry( hZp15w , "Z` (1.5 TeV) wide"                   , "L" );
legB->AddEntry( hZp20w , "Z` (2 TeV) wide"                   , "L" );
legB->AddEntry( hZp25w , "Z` (2.5 TeV) wide"                   , "L" );
legB->AddEntry( hZp30w , "Z` (3 TeV) wide"                   , "L" );
legB->AddEntry( hZp35w , "Z` (3.5 TeV) wide"                   , "L" );
legB->AddEntry( hZp40w , "Z` (4 TeV) wide"                   , "L" );
legB->AddEntry( hZp45w , "Z` (4.5 TeV) wide"                   , "L" );
legB->AddEntry( hZp50w , "Z` (5 TeV) wide"                   , "L" );
legB->SetFillColor(0);
legB->SetLineColor(0); 
legB->Draw("same");

h1_tex->Draw();
h2_tex->Draw();

gPad->RedrawAxis();	 

savename = "plotsSignal/ZPwide"+histname+".pdf";
savename_log = "plotsSignal/ZPwide_"+histname+"_log.pdf";
c1->SaveAs( savename .c_str() );
hZp25w->SetMaximum(40* hZp10w->GetMaximum() );
c1->SetLogy();
c1->SaveAs( savename_log .c_str() );
c1->SetLogy(0);




//------------------------------------------

hZp20e->SetStats(0);
hZp20e->SetTitle(histtitle.c_str());

hZp10e->Scale( hZp20e->Integral()/   hZp10e->Integral() );
hZp20e->Scale( hZp20e->Integral()/   hZp20e->Integral() );
hZp40e->Scale( hZp20e->Integral()/   hZp40e->Integral() );
hZp50e->Scale( hZp20e->Integral()/   hZp50e->Integral() );

if (xhi>0) hZp20e->GetXaxis()->SetRangeUser(xlo,xhi);
hZp20e->SetMaximum(1.3* hZp10e->GetMaximum() );
hZp20e->Draw("HIST");
hZp10e->Draw("HISTsame");
hZp20e->Draw("HISTsame");
hZp40e->Draw("HISTsame");
hZp50e->Draw("HISTsame");

TLegend *legC = new TLegend(leg1, leg2, leg3, leg4);
legC->SetTextSize(0.032);
legC->SetMargin(0.2);
legC->AddEntry( hZp10w , "Z` (1 TeV) extra wide"                   , "L" );
legC->AddEntry( hZp20w , "Z` (2 TeV) extra wide"                   , "L" );
legC->AddEntry( hZp40w , "Z` (4 TeV) extra wide"                   , "L" );
legC->AddEntry( hZp50w , "Z` (5 TeV) extra wide"                   , "L" );
legC->SetFillColor(0);
legC->SetLineColor(0); 
legC->Draw("same");

h1_tex->Draw();
h2_tex->Draw();

gPad->RedrawAxis();	 

savename = "plotsSignal/ZPextrawide"+histname+".pdf";
savename_log = "plotsSignal/ZPextrawide_"+histname+"_log.pdf";
c1->SaveAs( savename .c_str() );
hZp25w->SetMaximum(40* hZp10e->GetMaximum() );
c1->SetLogy();
c1->SaveAs( savename_log .c_str() );
c1->SetLogy(0);








//------------------------------------------



hRSG25->SetStats(0);
hRSG25->SetTitle(histtitle.c_str());

hRSG10->Scale( hRSG25->Integral()/   hRSG10->Integral() );
hRSG12->Scale( hRSG25->Integral()/   hRSG12->Integral() );
hRSG15->Scale( hRSG25->Integral()/   hRSG15->Integral() );
hRSG20->Scale( hRSG25->Integral()/   hRSG20->Integral() );
hRSG25->Scale( hRSG25->Integral()/   hRSG25->Integral() );
hRSG30->Scale( hRSG25->Integral()/   hRSG30->Integral() );
hRSG35->Scale( hRSG25->Integral()/   hRSG35->Integral() );
hRSG40->Scale( hRSG25->Integral()/   hRSG40->Integral() );
hRSG45->Scale( hRSG25->Integral()/   hRSG45->Integral() );
hRSG50->Scale( hRSG25->Integral()/   hRSG50->Integral() );

if (xhi>0) hRSG25->GetXaxis()->SetRangeUser(xlo,xhi);
hRSG25->SetMaximum(1.3* hRSG10->GetMaximum() );
hRSG25->Draw("HIST");
hRSG10->Draw("HISTsame");
hRSG12->Draw("HISTsame");
hRSG15->Draw("HISTsame");
hRSG20->Draw("HISTsame");
hRSG25->Draw("HISTsame");
hRSG30->Draw("HISTsame");
hRSG35->Draw("HISTsame");
hRSG40->Draw("HISTsame");
hRSG45->Draw("HISTsame");
hRSG50->Draw("HISTsame");

TLegend *legD = new TLegend(leg1, leg2, leg3, leg4);
legD->SetTextSize(0.036);
legD->SetMargin(0.2);
legD->AddEntry( hRSG10 , "RS Gluon (1 TeV) "                   , "L" );
legD->AddEntry( hRSG12 , "RS Gluon (1.25 TeV) "                   , "L" );
legD->AddEntry( hRSG15 , "RS Gluon (1.5 TeV) "                   , "L" );
legD->AddEntry( hRSG20 , "RS Gluon (2 TeV) "                   , "L" );
legD->AddEntry( hRSG25 , "RS Gluon (2.5 TeV) "                   , "L" );
legD->AddEntry( hRSG30 , "RS Gluon (3 TeV) "                   , "L" );
legD->AddEntry( hRSG35 , "RS Gluon (3.5 TeV) "                   , "L" );
legD->AddEntry( hRSG40 , "RS Gluon (4 TeV) "                   , "L" );
legD->AddEntry( hRSG45 , "RS Gluon (4.5 TeV) "                   , "L" );
legD->AddEntry( hRSG50 , "RS Gluon (5 TeV) "                   , "L" );
legD->SetFillColor(0);
legD->SetLineColor(0); 
legD->Draw("same");

h1_tex->Draw();
h2_tex->Draw();

gPad->RedrawAxis();	 

savename = "plotsSignal/RSG_"+histname+".pdf";
savename_log = "plotsSignal/RSG_"+histname+"_log.pdf";
c1->SaveAs( savename .c_str() );
hRSG25->SetMaximum(40* hRSG10->GetMaximum() );
c1->SetLogy();
c1->SaveAs( savename_log .c_str() );
c1->SetLogy(0);
















}
void multi(){

	run("h_DijetMass_dRapIn",";Dijet Mass [GeV];Number of Events", 500, 6000);
	run("h_DijetMass_dRapLo",";Dijet Mass (#Delta Y < 1) [GeV];Number of Events", 500, 6000);
	run("h_DijetMass_dRapHi",";Dijet Mass (#Delta Y > 1) [GeV];Number of Events", 500, 6000);
	run("h_DeltaRap",";#Delta Y;Number of Events", 0, 6);
	run("h_DeltaRap_mTTgt2",";#Delta Y (m_{t#bar{t}}>2 TeV);Number of Events", 0, 6);
	run("h_DeltaPhi",";#Delta Y;Number of Events", -1, -1);
	run("h_HT",";HT;Number of Events", 400, 6000);
	run("h_MET",";MET;Number of Events", -1, -1);
	run("h_Jet0Pt",";Jet0Pt;Number of Events", 400, 3000);
	run("h_Jet0PuppiSDsubjet0mass",";h_Jet0PuppiSDsubjet0mass;Number of Events", -1, -1);
	run("h_Jet0PuppiTau32",";h_Jet0PuppiTau32;Number of Events", -1, -1);
	run("h_Jet0PuppiSDmaxbdisc",";h_Jet0PuppiSDmaxbdisc;Number of Events", -1, -1);
	run("h_Jet0puppisdmass",";h_Jet0puppisdmass;Number of Events", -1, -1);


           

}