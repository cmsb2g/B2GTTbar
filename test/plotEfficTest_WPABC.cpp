void plotEfficTest_WPABC(bool forPUPPIpaper=0, string CMSsubtext="Supplementary"){
  //forPUPPIpaper: adds AK8 label, x-axis label changed

  string endlabel = "";
  std::size_t foundCMSsubtext = CMSsubtext.find("y");
  if (foundCMSsubtext !=std::string::npos) endlabel = Form("_Simulation%s",CMSsubtext.c_str());
  if (forPUPPIpaper) endlabel = Form("%s_forPUPPIpaper",endlabel.c_str());

  TCanvas *c1237= new TCanvas("c1237","",1,1,745,640);
  gStyle->SetOptFit(1);
  gStyle->SetOptStat(0);
  c1237->SetHighLightColor(2);
  c1237->Range(0,0,1,1);
  c1237->SetFillColor(0);
  c1237->SetBorderMode(0);
  c1237->SetBorderSize(2);
  c1237->SetTickx(1);
  c1237->SetTicky(1);
  c1237->SetLeftMargin(0.14);
  c1237->SetRightMargin(0.04);
  c1237->SetTopMargin(0.08);
  c1237->SetBottomMargin(0.15);
  c1237->SetFrameFillStyle(0);
  c1237->SetFrameBorderMode(0);


  //gStyle->SetLegendFont(42);
  gStyle->SetOptStat(0);
  // gROOT->SetBatch(); 
  gROOT->UseCurrentStyle();
  gROOT->ForceStyle();

  // gROOT->UseCurrentStyle();
  // gROOT->ForceStyle();

  // gROOT->Reset();
  // gROOT->ForceStyle(); 
  

  vector <double> bins_nvtx;
  int x;
  x=0;
  while (x<=80){
    cout<<" "<<x;
    bins_nvtx.push_back(x);
    if ( x<10) x+=5;
    // else if ( x<40) x+=2;
    else if ( x<45) x+=5;
    else x+=35;
  }
  cout<<endl;
  int nbins_nvtx = bins_nvtx.size();
  double *xbins_nvtx=new double[nbins_nvtx];
  for( unsigned int i = 0; i < bins_nvtx.size(); i++){
    xbins_nvtx[i] = bins_nvtx[i];
    cout<<bins_nvtx[i]<<" ";
  }
  cout<<endl;



  //string folder = "/uscms_data/d2/jdolen/B2G2016/CMSSW_8_0_26_patch2/src/Analysis/B2GTTbar/test/runs/";
  string folder = "/uscms/home/camclean/nobackup/B2G2016/CMSSW_8_0_26/src/Analysis/B2GTTbar/test/runs/";

  // string s1 = "histsAntiTag_ApplybTagSFbySubjetPuppiEffTest20170625_ht950_pt400_WPA_alt40_alt260_bM_PUw_noTTw_nom_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root";
  // string s2 = "histsAntiTag_ApplybTagSFbySubjetPuppiEffTest20170625_ht950_pt400_WPB_alt40_alt260_bM_PUw_noTTw_nom_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root";
  // string s3 = "histsAntiTag_ApplybTagSFbySubjetPuppiEffTest20170625_ht950_pt400_WPC_alt40_alt260_bM_PUw_noTTw_nom_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root";

  string s1w = "histsAntiTag_ApplybTagSFbySubjetPuppiEffTest20170625_ht950_pt400_WPA_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root";
  string s2w = "histsAntiTag_ApplybTagSFbySubjetPuppiEffTest20170625_ht950_pt400_WPB_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root";
  string s3w = "histsAntiTag_ApplybTagSFbySubjetPuppiEffTest20170625_ht950_pt400_WPC_alt40_alt260_bM_PUw_TTw_nom_b2gtreeV5_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2_orig_and_backup_missing2.root";

  // TFile * fTop1   = TFile::Open( (folder+s1).c_str() );
  // TFile * fTop2   = TFile::Open( (folder+s2).c_str() );
  // TFile * fTop3   = TFile::Open( (folder+s3).c_str() );

  TFile * fTop1w   = TFile::Open( (folder+s1w).c_str() );
  TFile * fTop2w   = TFile::Open( (folder+s2w).c_str() );
  TFile * fTop3w   = TFile::Open( (folder+s3w).c_str() );


  string title = ";N_{vtx}^{good}; t-tag efficiency";
  if (forPUPPIpaper) title = ";Number of Vertices; t-tag efficiency";


  //  TH1D *    h1_Effic_Denom_pup0P                           = (TH1D *) fTop1->Get( "h_Effic_Denom_pup0P"                            );
  //  TH1D *    h1_Effic_Denom_jet0P                           = (TH1D *) fTop1->Get( "h_Effic_Denom_jet0P"                            );
  //  TH1D *    h1_Effic_Denom_jet0Y                           = (TH1D *) fTop1->Get( "h_Effic_Denom_jet0Y"                            );
  //  TH1D *    h1_Effic_Denom_nvtxg                           = (TH1D *) fTop1->Get( "h_Effic_Denom_nvtxg"                            );
  //  TH1D *    h1_Effic_Denom_jet0P_TopMatch                  = (TH1D *) fTop1->Get( "h_Effic_Denom_jet0P_TopMatch"                   );
  //  TH1D *    h1_Effic_Denom_jet0P_TopMatch_TopDist          = (TH1D *) fTop1->Get( "h_Effic_Denom_jet0P_TopMatch_TopDist"           );
  //  TH1D *    h1_Effic_puptag_tau32_pup0P                    = (TH1D *) fTop1->Get( "h_Effic_puptag_tau32_pup0P"                     );
  //  TH1D *    h1_Effic_puptag_tau32_jet0P                    = (TH1D *) fTop1->Get( "h_Effic_puptag_tau32_jet0P"                     );
  //  TH1D *    h1_Effic_puptag_tau32_jet0Y                    = (TH1D *) fTop1->Get( "h_Effic_puptag_tau32_jet0Y"                     );
  //  TH1D *    h1_Effic_puptag_tau32_nvtxg                    = (TH1D *) fTop1->Get( "h_Effic_puptag_tau32_nvtxg"                     );
  //  TH1D *    h1_Effic_puptag_tau32_jet0P_TopMatch           = (TH1D *) fTop1->Get( "h_Effic_puptag_tau32_jet0P_TopMatch"            );
  //  TH1D *    h1_Effic_puptag_tau32_jet0P_TopMatch_TopDist   = (TH1D *) fTop1->Get( "h_Effic_puptag_tau32_jet0P_TopMatch_TopDist"    );
  //  TH1D *    h1_Effic_chstag_tau32_pup0P                    = (TH1D *) fTop1->Get( "h_Effic_chstag_tau32_pup0P"                     );
  //  TH1D *    h1_Effic_chstag_tau32_jet0P                    = (TH1D *) fTop1->Get( "h_Effic_chstag_tau32_jet0P"                     );
  //  TH1D *    h1_Effic_chstag_tau32_jet0Y                    = (TH1D *) fTop1->Get( "h_Effic_chstag_tau32_jet0Y"                     );
  //  TH1D *    h1_Effic_chstag_tau32_nvtxg                    = (TH1D *) fTop1->Get( "h_Effic_chstag_tau32_nvtxg"                     );
  //  TH1D *    h1_Effic_chstag_tau32_jet0P_TopMatch           = (TH1D *) fTop1->Get( "h_Effic_chstag_tau32_jet0P_TopMatch"            );
  //  TH1D *    h1_Effic_chstag_tau32_jet0P_TopMatch_TopDist   = (TH1D *) fTop1->Get( "h_Effic_chstag_tau32_jet0P_TopMatch_TopDist"    );
  //  TH1D *    h1_Effic_puptag_mass_pup0P                     = (TH1D *) fTop1->Get( "h_Effic_puptag_mass_pup0P"                      );
  //  TH1D *    h1_Effic_puptag_mass_jet0P                     = (TH1D *) fTop1->Get( "h_Effic_puptag_mass_jet0P"                      );
  //  TH1D *    h1_Effic_puptag_mass_jet0Y                     = (TH1D *) fTop1->Get( "h_Effic_puptag_mass_jet0Y"                      );
  //  TH1D *    h1_Effic_puptag_mass_nvtxg                     = (TH1D *) fTop1->Get( "h_Effic_puptag_mass_nvtxg"                      );
  //  TH1D *    h1_Effic_puptag_mass_jet0P_TopMatch            = (TH1D *) fTop1->Get( "h_Effic_puptag_mass_jet0P_TopMatch"             );
  //  TH1D *    h1_Effic_puptag_mass_jet0P_TopMatch_TopDist    = (TH1D *) fTop1->Get( "h_Effic_puptag_mass_jet0P_TopMatch_TopDist"     );
  //  TH1D *    h1_Effic_chstag_mass_pup0P                     = (TH1D *) fTop1->Get( "h_Effic_chstag_mass_pup0P"                      );
  //  TH1D *    h1_Effic_chstag_mass_jet0P                     = (TH1D *) fTop1->Get( "h_Effic_chstag_mass_jet0P"                      );
  //  TH1D *    h1_Effic_chstag_mass_jet0Y                     = (TH1D *) fTop1->Get( "h_Effic_chstag_mass_jet0Y"                      );
  //  TH1D *    h1_Effic_chstag_mass_nvtxg                     = (TH1D *) fTop1->Get( "h_Effic_chstag_mass_nvtxg"                      );
  //  TH1D *    h1_Effic_chstag_mass_jet0P_TopMatch            = (TH1D *) fTop1->Get( "h_Effic_chstag_mass_jet0P_TopMatch"             );
  //  TH1D *    h1_Effic_chstag_mass_jet0P_TopMatch_TopDist    = (TH1D *) fTop1->Get( "h_Effic_chstag_mass_jet0P_TopMatch_TopDist"     );
  //  TH1D *    h1_Effic_puptag_t_pup0P                        = (TH1D *) fTop1->Get( "h_Effic_puptag_t_pup0P"                         );
  //  TH1D *    h1_Effic_puptag_t_jet0P                        = (TH1D *) fTop1->Get( "h_Effic_puptag_t_jet0P"                         );
  //  TH1D *    h1_Effic_puptag_t_jet0Y                        = (TH1D *) fTop1->Get( "h_Effic_puptag_t_jet0Y"                         );
  //  TH1D *    h1_Effic_puptag_t_nvtxg                        = (TH1D *) fTop1->Get( "h_Effic_puptag_t_nvtxg"                         );
  //  TH1D *    h1_Effic_puptag_t_jet0P_TopMatch               = (TH1D *) fTop1->Get( "h_Effic_puptag_t_jet0P_TopMatch"                );
  //  TH1D *    h1_Effic_puptag_t_jet0P_TopMatch_TopDist       = (TH1D *) fTop1->Get( "h_Effic_puptag_t_jet0P_TopMatch_TopDist"        );
  //  TH1D *    h1_Effic_chstag_t_pup0P                        = (TH1D *) fTop1->Get( "h_Effic_chstag_t_pup0P"                         );
  //  TH1D *    h1_Effic_chstag_t_jet0P                        = (TH1D *) fTop1->Get( "h_Effic_chstag_t_jet0P"                         );
  //  TH1D *    h1_Effic_chstag_t_jet0Y                        = (TH1D *) fTop1->Get( "h_Effic_chstag_t_jet0Y"                         );
  //  TH1D *    h1_Effic_chstag_t_nvtxg                        = (TH1D *) fTop1->Get( "h_Effic_chstag_t_nvtxg"                         );
  //  TH1D *    h1_Effic_chstag_t_jet0P_TopMatch               = (TH1D *) fTop1->Get( "h_Effic_chstag_t_jet0P_TopMatch"                );
  //  TH1D *    h1_Effic_chstag_t_jet0P_TopMatch_TopDist       = (TH1D *) fTop1->Get( "h_Effic_chstag_t_jet0P_TopMatch_TopDist"        );




  //  TH1D *    h1_new_Effic_Denom_pup0P                         = (TH1D*) h1_Effic_Denom_pup0P                            ->Clone();  
  //  TH1D *    h1_new_Effic_Denom_jet0P                         = (TH1D*) h1_Effic_Denom_jet0P                            ->Clone();  
  //  TH1D *    h1_new_Effic_Denom_jet0Y                         = (TH1D*) h1_Effic_Denom_jet0Y                            ->Clone();  
  //  TH1D *    h1_new_Effic_Denom_nvtxg                         = (TH1D*) h1_Effic_Denom_nvtxg                            ->Clone();  
  //  TH1D *    h1_new_Effic_Denom_jet0P_TopMatch                = (TH1D*) h1_Effic_Denom_jet0P_TopMatch                   ->Clone();  
  //  TH1D *    h1_new_Effic_Denom_jet0P_TopMatch_TopDist        = (TH1D*) h1_Effic_Denom_jet0P_TopMatch_TopDist           ->Clone();  
  //  TH1D *    h1_new_Effic_puptag_tau32_pup0P                  = (TH1D*) h1_Effic_puptag_tau32_pup0P                     ->Clone();  
  //  TH1D *    h1_new_Effic_puptag_tau32_jet0P                  = (TH1D*) h1_Effic_puptag_tau32_jet0P                     ->Clone();  
  //  TH1D *    h1_new_Effic_puptag_tau32_jet0Y                  = (TH1D*) h1_Effic_puptag_tau32_jet0Y                     ->Clone();  
  //  TH1D *    h1_new_Effic_puptag_tau32_nvtxg                  = (TH1D*) h1_Effic_puptag_tau32_nvtxg                     ->Clone();  
  //  TH1D *    h1_new_Effic_puptag_tau32_jet0P_TopMatch         = (TH1D*) h1_Effic_puptag_tau32_jet0P_TopMatch            ->Clone();  
  //  TH1D *    h1_new_Effic_puptag_tau32_jet0P_TopMatch_TopDist = (TH1D*) h1_Effic_puptag_tau32_jet0P_TopMatch_TopDist    ->Clone();  
  //  TH1D *    h1_new_Effic_chstag_tau32_pup0P                  = (TH1D*) h1_Effic_chstag_tau32_pup0P                     ->Clone();  
  //  TH1D *    h1_new_Effic_chstag_tau32_jet0P                  = (TH1D*) h1_Effic_chstag_tau32_jet0P                     ->Clone();  
  //  TH1D *    h1_new_Effic_chstag_tau32_jet0Y                  = (TH1D*) h1_Effic_chstag_tau32_jet0Y                     ->Clone();  
  //  TH1D *    h1_new_Effic_chstag_tau32_nvtxg                  = (TH1D*) h1_Effic_chstag_tau32_nvtxg                     ->Clone();  
  //  TH1D *    h1_new_Effic_chstag_tau32_jet0P_TopMatch         = (TH1D*) h1_Effic_chstag_tau32_jet0P_TopMatch            ->Clone();  
  //  TH1D *    h1_new_Effic_chstag_tau32_jet0P_TopMatch_TopDist = (TH1D*) h1_Effic_chstag_tau32_jet0P_TopMatch_TopDist    ->Clone();  
  //  TH1D *    h1_new_Effic_puptag_mass_pup0P                   = (TH1D*) h1_Effic_puptag_mass_pup0P                      ->Clone();  
  //  TH1D *    h1_new_Effic_puptag_mass_jet0P                   = (TH1D*) h1_Effic_puptag_mass_jet0P                      ->Clone();  
  //  TH1D *    h1_new_Effic_puptag_mass_jet0Y                   = (TH1D*) h1_Effic_puptag_mass_jet0Y                      ->Clone();  
  //  TH1D *    h1_new_Effic_puptag_mass_nvtxg                   = (TH1D*) h1_Effic_puptag_mass_nvtxg                      ->Clone();  
  //  TH1D *    h1_new_Effic_puptag_mass_jet0P_TopMatch          = (TH1D*) h1_Effic_puptag_mass_jet0P_TopMatch             ->Clone();  
  //  TH1D *    h1_new_Effic_puptag_mass_jet0P_TopMatch_TopDist  = (TH1D*) h1_Effic_puptag_mass_jet0P_TopMatch_TopDist     ->Clone();  
  //  TH1D *    h1_new_Effic_chstag_mass_pup0P                   = (TH1D*) h1_Effic_chstag_mass_pup0P                      ->Clone();  
  //  TH1D *    h1_new_Effic_chstag_mass_jet0P                   = (TH1D*) h1_Effic_chstag_mass_jet0P                      ->Clone();  
  //  TH1D *    h1_new_Effic_chstag_mass_jet0Y                   = (TH1D*) h1_Effic_chstag_mass_jet0Y                      ->Clone();  
  //  TH1D *    h1_new_Effic_chstag_mass_nvtxg                   = (TH1D*) h1_Effic_chstag_mass_nvtxg                      ->Clone();  
  //  TH1D *    h1_new_Effic_chstag_mass_jet0P_TopMatch          = (TH1D*) h1_Effic_chstag_mass_jet0P_TopMatch             ->Clone();  
  //  TH1D *    h1_new_Effic_chstag_mass_jet0P_TopMatch_TopDist  = (TH1D*) h1_Effic_chstag_mass_jet0P_TopMatch_TopDist     ->Clone();  
  //  TH1D *    h1_new_Effic_puptag_t_pup0P                      = (TH1D*) h1_Effic_puptag_t_pup0P                         ->Clone();  
  //  TH1D *    h1_new_Effic_puptag_t_jet0P                      = (TH1D*) h1_Effic_puptag_t_jet0P                         ->Clone();  
  //  TH1D *    h1_new_Effic_puptag_t_jet0Y                      = (TH1D*) h1_Effic_puptag_t_jet0Y                         ->Clone();  
  //  TH1D *    h1_new_Effic_puptag_t_nvtxg                      = (TH1D*) h1_Effic_puptag_t_nvtxg                         ->Clone();  
  //  TH1D *    h1_new_Effic_puptag_t_jet0P_TopMatch             = (TH1D*) h1_Effic_puptag_t_jet0P_TopMatch                ->Clone();  
  //  TH1D *    h1_new_Effic_puptag_t_jet0P_TopMatch_TopDist     = (TH1D*) h1_Effic_puptag_t_jet0P_TopMatch_TopDist        ->Clone();  
  //  TH1D *    h1_new_Effic_chstag_t_pup0P                      = (TH1D*) h1_Effic_chstag_t_pup0P                         ->Clone();  
  //  TH1D *    h1_new_Effic_chstag_t_jet0P                      = (TH1D*) h1_Effic_chstag_t_jet0P                         ->Clone();  
  //  TH1D *    h1_new_Effic_chstag_t_jet0Y                      = (TH1D*) h1_Effic_chstag_t_jet0Y                         ->Clone();  
  //  TH1D *    h1_new_Effic_chstag_t_nvtxg                      = (TH1D*) h1_Effic_chstag_t_nvtxg                         ->Clone();  
  //  TH1D *    h1_new_Effic_chstag_t_jet0P_TopMatch             = (TH1D*) h1_Effic_chstag_t_jet0P_TopMatch                ->Clone();  
  //  TH1D *    h1_new_Effic_chstag_t_jet0P_TopMatch_TopDist     = (TH1D*) h1_Effic_chstag_t_jet0P_TopMatch_TopDist        ->Clone();  


  // TH1D * h1_rebin_Effic_Denom_pup0P                          ;  
  // TH1D * h1_rebin_Effic_Denom_jet0P                          ;  
  // TH1D * h1_rebin_Effic_Denom_jet0Y                          ;  
  // TH1D * h1_rebin_Effic_Denom_nvtxg                          ;  
  // TH1D * h1_rebin_Effic_Denom_jet0P_TopMatch                 ;  
  // TH1D * h1_rebin_Effic_Denom_jet0P_TopMatch_TopDist         ;  
  // TH1D * h1_rebin_Effic_puptag_tau32_pup0P                   ;  
  // TH1D * h1_rebin_Effic_puptag_tau32_jet0P                   ;  
  // TH1D * h1_rebin_Effic_puptag_tau32_jet0Y                   ;  
  // TH1D * h1_rebin_Effic_puptag_tau32_nvtxg                   ;  
  // TH1D * h1_rebin_Effic_puptag_tau32_jet0P_TopMatch          ;  
  // TH1D * h1_rebin_Effic_puptag_tau32_jet0P_TopMatch_TopDist  ;  
  // TH1D * h1_rebin_Effic_chstag_tau32_pup0P                   ;  
  // TH1D * h1_rebin_Effic_chstag_tau32_jet0P                   ;  
  // TH1D * h1_rebin_Effic_chstag_tau32_jet0Y                   ;  
  // TH1D * h1_rebin_Effic_chstag_tau32_nvtxg                   ;  
  // TH1D * h1_rebin_Effic_chstag_tau32_jet0P_TopMatch          ;  
  // TH1D * h1_rebin_Effic_chstag_tau32_jet0P_TopMatch_TopDist  ;  
  // TH1D * h1_rebin_Effic_puptag_mass_pup0P                    ;  
  // TH1D * h1_rebin_Effic_puptag_mass_jet0P                    ;  
  // TH1D * h1_rebin_Effic_puptag_mass_jet0Y                    ;  
  // TH1D * h1_rebin_Effic_puptag_mass_nvtxg                    ;  
  // TH1D * h1_rebin_Effic_puptag_mass_jet0P_TopMatch           ;  
  // TH1D * h1_rebin_Effic_puptag_mass_jet0P_TopMatch_TopDist   ;  
  // TH1D * h1_rebin_Effic_chstag_mass_pup0P                    ;  
  // TH1D * h1_rebin_Effic_chstag_mass_jet0P                    ;  
  // TH1D * h1_rebin_Effic_chstag_mass_jet0Y                    ;  
  // TH1D * h1_rebin_Effic_chstag_mass_nvtxg                    ;  
  // TH1D * h1_rebin_Effic_chstag_mass_jet0P_TopMatch           ;  
  // TH1D * h1_rebin_Effic_chstag_mass_jet0P_TopMatch_TopDist   ;  
  // TH1D * h1_rebin_Effic_puptag_t_pup0P                       ;  
  // TH1D * h1_rebin_Effic_puptag_t_jet0P                       ;  
  // TH1D * h1_rebin_Effic_puptag_t_jet0Y                       ;  
  // TH1D * h1_rebin_Effic_puptag_t_nvtxg                       ;  
  // TH1D * h1_rebin_Effic_puptag_t_jet0P_TopMatch              ;  
  // TH1D * h1_rebin_Effic_puptag_t_jet0P_TopMatch_TopDist      ;  
  // TH1D * h1_rebin_Effic_chstag_t_pup0P                       ;  
  // TH1D * h1_rebin_Effic_chstag_t_jet0P                       ;  
  // TH1D * h1_rebin_Effic_chstag_t_jet0Y                       ;  
  // TH1D * h1_rebin_Effic_chstag_t_nvtxg                       ;  
  // TH1D * h1_rebin_Effic_chstag_t_jet0P_TopMatch              ;  
  // TH1D * h1_rebin_Effic_chstag_t_jet0P_TopMatch_TopDist      ;  



  // h1_rebin_Effic_Denom_nvtxg         = (TH1D*)h1_new_Effic_Denom_nvtxg           ->Rebin(nbins_nvtx-1,"h1_rebin_Effic_Denom_nvtxg"       ,xbins_nvtx);
  // h1_rebin_Effic_puptag_tau32_nvtxg  = (TH1D*)h1_new_Effic_puptag_tau32_nvtxg    ->Rebin(nbins_nvtx-1,"h1_rebin_Effic_puptag_tau32_nvtxg",xbins_nvtx);
  // h1_rebin_Effic_chstag_tau32_nvtxg  = (TH1D*)h1_new_Effic_chstag_tau32_nvtxg    ->Rebin(nbins_nvtx-1,"h1_rebin_Effic_chstag_tau32_nvtxg",xbins_nvtx);
  // h1_rebin_Effic_puptag_mass_nvtxg   = (TH1D*)h1_new_Effic_puptag_mass_nvtxg     ->Rebin(nbins_nvtx-1,"h1_rebin_Effic_puptag_mass_nvtxg" ,xbins_nvtx);
  // h1_rebin_Effic_chstag_mass_nvtxg   = (TH1D*)h1_new_Effic_chstag_mass_nvtxg     ->Rebin(nbins_nvtx-1,"h1_rebin_Effic_chstag_mass_nvtxg" ,xbins_nvtx);
  // h1_rebin_Effic_puptag_t_nvtxg      = (TH1D*)h1_new_Effic_puptag_t_nvtxg        ->Rebin(nbins_nvtx-1,"h1_rebin_Effic_puptag_t_nvtxg"    ,xbins_nvtx);
  // h1_rebin_Effic_chstag_t_nvtxg      = (TH1D*)h1_new_Effic_chstag_t_nvtxg        ->Rebin(nbins_nvtx-1,"h1_rebin_Effic_chstag_t_nvtxg"    ,xbins_nvtx);

  // h1_Effic_Denom_pup0P                          ->Rebin(10);
  // h1_Effic_Denom_jet0P                          ->Rebin(10);
  // h1_Effic_Denom_jet0Y                          ->Rebin(10);
  // h1_Effic_Denom_jet0P_TopMatch                 ->Rebin(10);
  // h1_Effic_Denom_jet0P_TopMatch_TopDist         ->Rebin(10);
  // h1_Effic_puptag_tau32_pup0P                   ->Rebin(10);
  // h1_Effic_puptag_tau32_jet0P                   ->Rebin(10);
  // h1_Effic_puptag_tau32_jet0Y                   ->Rebin(10);
  // h1_Effic_puptag_tau32_jet0P_TopMatch          ->Rebin(10);
  // h1_Effic_puptag_tau32_jet0P_TopMatch_TopDist  ->Rebin(10);
  // h1_Effic_chstag_tau32_pup0P                   ->Rebin(10);
  // h1_Effic_chstag_tau32_jet0P                   ->Rebin(10);
  // h1_Effic_chstag_tau32_jet0Y                   ->Rebin(10);
  // h1_Effic_chstag_tau32_jet0P_TopMatch          ->Rebin(10);
  // h1_Effic_chstag_tau32_jet0P_TopMatch_TopDist  ->Rebin(10);
  // h1_Effic_puptag_mass_pup0P                    ->Rebin(10);
  // h1_Effic_puptag_mass_jet0P                    ->Rebin(10);
  // h1_Effic_puptag_mass_jet0Y                    ->Rebin(10);
  // h1_Effic_puptag_mass_jet0P_TopMatch           ->Rebin(10);
  // h1_Effic_puptag_mass_jet0P_TopMatch_TopDist   ->Rebin(10);
  // h1_Effic_chstag_mass_pup0P                    ->Rebin(10);
  // h1_Effic_chstag_mass_jet0P                    ->Rebin(10);
  // h1_Effic_chstag_mass_jet0Y                    ->Rebin(10);
  // h1_Effic_chstag_mass_jet0P_TopMatch           ->Rebin(10);
  // h1_Effic_chstag_mass_jet0P_TopMatch_TopDist   ->Rebin(10);
  // h1_Effic_puptag_t_pup0P                       ->Rebin(10);
  // h1_Effic_puptag_t_jet0P                       ->Rebin(10);
  // h1_Effic_puptag_t_jet0Y                       ->Rebin(10);
  // h1_Effic_puptag_t_jet0P_TopMatch              ->Rebin(10);
  // h1_Effic_puptag_t_jet0P_TopMatch_TopDist      ->Rebin(10);
  // h1_Effic_chstag_t_pup0P                       ->Rebin(10);
  // h1_Effic_chstag_t_jet0P                       ->Rebin(10);
  // h1_Effic_chstag_t_jet0Y                       ->Rebin(10);
  // h1_Effic_chstag_t_jet0P_TopMatch              ->Rebin(10);
  // h1_Effic_chstag_t_jet0P_TopMatch_TopDist      ->Rebin(10);


  // TH1D *effic_tau32_pup0P =(TH1D*) h1_Effic_puptag_tau32_pup0P->Clone();
  // // effic_tau32_pup0P->Reset();
  // effic_tau32_pup0P->Divide( h1_Effic_puptag_tau32_pup0P, h1_Effic_Denom_pup0P,1,1,"B");

  // TH1D *effic_tau32_jet0P =(TH1D*) h1_Effic_puptag_tau32_jet0P->Clone();
  // // effic_tau32_jet0P->Reset();
  // effic_tau32_jet0P->Divide( h1_Effic_puptag_tau32_jet0P, h1_Effic_Denom_jet0P,1,1,"B");

  // TH1D *effic_chstag_tau32_jet0P =(TH1D*) h1_Effic_chstag_tau32_jet0P->Clone();
  // // effic_chstag_tau32_jet0P->Reset();
  // effic_chstag_tau32_jet0P->Divide( h1_Effic_chstag_tau32_jet0P, h1_Effic_Denom_jet0P,1,1,"B");


  // TH1D *effic_mass_jet0P =(TH1D*) h1_Effic_puptag_mass_jet0P->Clone();
  // // effic_mass_jet0P->Reset();
  // effic_mass_jet0P->Divide( h1_Effic_puptag_mass_jet0P, h1_Effic_Denom_jet0P,1,1,"B");

  // TH1D *effic_t_jet0P =(TH1D*) h1_Effic_puptag_t_jet0P->Clone();
  // // effic_t_jet0P->Reset();
  // effic_t_jet0P->Divide( h1_Effic_puptag_t_jet0P, h1_Effic_Denom_jet0P,1,1,"B");

  // effic_tau32_pup0P ->SetLineColor(2);    
  // effic_tau32_jet0P ->SetLineColor(3);        
  // effic_mass_jet0P  ->SetLineColor(4);       
  // effic_t_jet0P     ->SetLineColor(5);
  // effic_chstag_tau32_jet0P->SetLineColor(6);

  // effic_tau32_pup0P->GetXaxis()->SetRangeUser(300,4000);
  // effic_tau32_pup0P ->Draw("HIST");          
  // effic_tau32_jet0P ->Draw("HISTsame");
  // effic_chstag_tau32_jet0P  ->Draw("HISTsame");         
  // effic_mass_jet0P  ->Draw("HISTsame");         
  // effic_t_jet0P     ->Draw("HISTsame");      
  // c1237->SaveAs("./plotsEfficTest/effic_tau32_pup0P.pdf");

  // cout<<"h1_Effic_puptag_tau32_jet0P_TopMatch "<<h1_Effic_puptag_tau32_jet0P_TopMatch->Integral()<<endl;
  // cout<<"h1_Effic_Denom_jet0P_TopMatch "<<h1_Effic_Denom_jet0P_TopMatch->Integral()<<endl;

  // cout<<"h1_Effic_puptag_tau32_jet0P_TopMatch_TopDist "<<h1_Effic_puptag_tau32_jet0P_TopMatch_TopDist->Integral()<<endl;
  // cout<<"h1_Effic_Denom_jet0P_TopMatch_TopDist "<<h1_Effic_Denom_jet0P_TopMatch_TopDist->Integral()<<endl;


  // TH1D *effic_puptag_tau32_jet0P_TopMatch =(TH1D*) h1_Effic_puptag_tau32_jet0P_TopMatch->Clone();
  // effic_puptag_tau32_jet0P_TopMatch->Reset();
  // effic_puptag_tau32_jet0P_TopMatch->Divide( h1_Effic_puptag_tau32_jet0P_TopMatch, h1_Effic_Denom_jet0P_TopMatch,1,1,"B");

  // TH1D *effic_puptag_tau32_jet0P_TopMatch_TopDist =(TH1D*) h1_Effic_puptag_tau32_jet0P_TopMatch_TopDist->Clone();
  // effic_puptag_tau32_jet0P_TopMatch_TopDist->Reset();
  // effic_puptag_tau32_jet0P_TopMatch_TopDist->Divide( h1_Effic_puptag_tau32_jet0P_TopMatch_TopDist, h1_Effic_Denom_jet0P_TopMatch_TopDist,1,1,"B");

  // effic_puptag_tau32_jet0P_TopMatch         ->SetLineColor(1);
  // effic_puptag_tau32_jet0P_TopMatch_TopDist->SetLineColor(2);

  // effic_puptag_tau32_jet0P_TopMatch_TopDist->GetXaxis()->SetRangeUser(300,4000);
  // effic_puptag_tau32_jet0P_TopMatch_TopDist ->Draw("HIST");          
  // effic_puptag_tau32_jet0P_TopMatch ->Draw("HISTsame");    
  // c1237->SaveAs("./plotsEfficTest/effic_match.pdf");





  // TH1D *h1_effic_puptag_tau32_nvtxg =(TH1D*) h1_rebin_Effic_puptag_tau32_nvtxg->Clone();
  // // h1_effic_puptag_tau32_nvtxg->Reset();
  // h1_effic_puptag_tau32_nvtxg->Divide( h1_rebin_Effic_puptag_tau32_nvtxg, h1_rebin_Effic_Denom_nvtxg,1,1,"B");

  // TH1D *h1_effic_puptag_mass_nvtxg =(TH1D*) h1_rebin_Effic_puptag_mass_nvtxg->Clone();
  // // h1_effic_puptag_mass_nvtxg->Reset();
  // h1_effic_puptag_mass_nvtxg->Divide( h1_rebin_Effic_puptag_mass_nvtxg, h1_rebin_Effic_Denom_nvtxg,1,1,"B");

  // TH1D *h1_effic_puptag_t_nvtxg =(TH1D*) h1_rebin_Effic_puptag_t_nvtxg->Clone();
  // // h1_effic_puptag_t_nvtxg->Reset();
  // h1_effic_puptag_t_nvtxg->Divide( h1_rebin_Effic_puptag_t_nvtxg, h1_rebin_Effic_Denom_nvtxg,1,1,"B");


  // TH1D *h1_effic_chstag_tau32_nvtxg =(TH1D*) h1_rebin_Effic_chstag_tau32_nvtxg->Clone();
  // // h1_effic_chstag_tau32_nvtxg->Reset();
  // h1_effic_chstag_tau32_nvtxg->Divide( h1_rebin_Effic_chstag_tau32_nvtxg, h1_rebin_Effic_Denom_nvtxg,1,1,"B");

  // TH1D *h1_effic_chstag_mass_nvtxg =(TH1D*) h1_rebin_Effic_chstag_mass_nvtxg->Clone();
  // // h1_effic_chstag_mass_nvtxg->Reset();
  // h1_effic_chstag_mass_nvtxg->Divide( h1_rebin_Effic_chstag_mass_nvtxg, h1_rebin_Effic_Denom_nvtxg,1,1,"B");

  // TH1D *h1_effic_chstag_t_nvtxg =(TH1D*) h1_rebin_Effic_chstag_t_nvtxg->Clone();
  // // h1_effic_chstag_t_nvtxg->Reset();
  // h1_effic_chstag_t_nvtxg->Divide( h1_rebin_Effic_chstag_t_nvtxg, h1_rebin_Effic_Denom_nvtxg,1,1,"B");

  // h1_effic_puptag_tau32_nvtxg ->SetMarkerStyle(20);        
  // h1_effic_puptag_mass_nvtxg  ->SetMarkerStyle(21);       
  // h1_effic_puptag_t_nvtxg     ->SetMarkerStyle(22);

  // h1_effic_chstag_tau32_nvtxg ->SetMarkerStyle(24);        
  // h1_effic_chstag_mass_nvtxg  ->SetMarkerStyle(25);       
  // h1_effic_chstag_t_nvtxg     ->SetMarkerStyle(26);

  // h1_effic_puptag_tau32_nvtxg ->SetMarkerColor(6);              
  // h1_effic_puptag_mass_nvtxg  ->SetMarkerColor(kBlue);         
  // h1_effic_puptag_t_nvtxg     ->SetMarkerColor(kOrange+1);

  // h1_effic_chstag_tau32_nvtxg ->SetMarkerColor(6);        
  // h1_effic_chstag_mass_nvtxg  ->SetMarkerColor(kBlue);       
  // h1_effic_chstag_t_nvtxg     ->SetMarkerColor(kOrange+1);

  // h1_effic_puptag_tau32_nvtxg ->SetLineColor(6);           
  // h1_effic_puptag_mass_nvtxg  ->SetLineColor(kBlue);      
  // h1_effic_puptag_t_nvtxg     ->SetLineColor(kOrange+1);

  // h1_effic_chstag_tau32_nvtxg ->SetLineColor(6);           
  // h1_effic_chstag_mass_nvtxg  ->SetLineColor(kBlue);      
  // h1_effic_chstag_t_nvtxg     ->SetLineColor(kOrange+1);

  // h1_effic_puptag_tau32_nvtxg ->SetLineWidth(2);   
  // h1_effic_puptag_mass_nvtxg  ->SetLineWidth(2);  
  // h1_effic_puptag_t_nvtxg     ->SetLineWidth(2);

  // h1_effic_chstag_tau32_nvtxg ->SetLineWidth(2);   
  // h1_effic_chstag_mass_nvtxg  ->SetLineWidth(2);  
  // h1_effic_chstag_t_nvtxg     ->SetLineWidth(2);




  //   h1_effic_puptag_tau32_nvtxg->SetTitle(title.c_str());

  //   h1_effic_puptag_tau32_nvtxg->SetStats(0);


  //   h1_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleSize(0.065);
  //   h1_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleOffset(0.9); 
  //   h1_effic_puptag_tau32_nvtxg->GetYaxis()->SetLabelSize(0.06);

  //   h1_effic_puptag_tau32_nvtxg->GetXaxis()->SetNdivisions(506);
  //   h1_effic_puptag_tau32_nvtxg->GetXaxis()->SetLabelFont(42);
  //   h1_effic_puptag_tau32_nvtxg->GetXaxis()->SetLabelSize(0.05);
  //   h1_effic_puptag_tau32_nvtxg->GetXaxis()->SetTitleSize(0.056);
  //   h1_effic_puptag_tau32_nvtxg->GetXaxis()->SetTickLength(0.045);
  //   h1_effic_puptag_tau32_nvtxg->GetXaxis()->SetTitleOffset(1.15);
  //   h1_effic_puptag_tau32_nvtxg->GetXaxis()->SetTitleFont(42);

  //   h1_effic_puptag_tau32_nvtxg->GetYaxis()->SetNdivisions(506);
  //   h1_effic_puptag_tau32_nvtxg->GetYaxis()->SetLabelFont(42);
  //   h1_effic_puptag_tau32_nvtxg->GetYaxis()->SetLabelSize(0.05);
  //   h1_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleSize(0.06125);
  //   h1_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleOffset(1.17);
  //   h1_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleFont(42);

  //   h1_effic_puptag_tau32_nvtxg->GetZaxis()->SetLabelFont(42);
  //   h1_effic_puptag_tau32_nvtxg->GetZaxis()->SetLabelSize(0.0425);
  //   h1_effic_puptag_tau32_nvtxg->GetZaxis()->SetTitleSize(0.0475);
  //   h1_effic_puptag_tau32_nvtxg->GetZaxis()->SetTitleFont(42);

  // h1_effic_puptag_tau32_nvtxg->GetYaxis()->SetRangeUser(0.0,1.1);
  // h1_effic_puptag_tau32_nvtxg ->Draw("");
  // h1_effic_puptag_mass_nvtxg  ->Draw("same");         
  // h1_effic_puptag_t_nvtxg     ->Draw("same");      

  // h1_effic_chstag_tau32_nvtxg ->Draw("same");
  // h1_effic_chstag_mass_nvtxg  ->Draw("same");         
  // h1_effic_chstag_t_nvtxg     ->Draw("same");      





  //   TLegend * h1_leg;
  //   h1_leg = new TLegend( 0.58, 0.6,0.95, 0.88);  //( 0.56, 0.69,0.98, 0.89);
  //   h1_leg->SetBorderSize(0);
  //   h1_leg->SetFillColor(0);
  //   h1_leg->SetFillStyle(4000);
  //   h1_leg->SetTextSize(0.04);   //0.038
  //   h1_leg->SetMargin(0.18 );
  //   h1_leg->SetHeader("Loose t-tag");
  //   h1_leg->AddEntry( h1_effic_chstag_mass_nvtxg    , "CHS: m_{SD} tag"            , "LP" );
  //   h1_leg->AddEntry( h1_effic_chstag_tau32_nvtxg   , "CHS: #tau_{32} tag"         , "LP" );
  //   h1_leg->AddEntry( h1_effic_chstag_t_nvtxg       , "CHS: m_{SD}+#tau_{32} tag"  , "LP" );
  
  //   h1_leg->AddEntry( h1_effic_puptag_mass_nvtxg    , "PUPPI: m_{SD} tag"                     , "LP" );
  //   h1_leg->AddEntry( h1_effic_puptag_tau32_nvtxg   , "PUPPI: #tau_{32} tag"                  , "LP" );
  //   h1_leg->AddEntry( h1_effic_puptag_t_nvtxg       , "PUPPI: m_{SD}+#tau_{32} tag"           , "LP" );
  //   h1_leg->Draw("same");

  //   TLatex *   h1_tex = new TLatex(0.18,0.83,"#font[62]{CMS}");// #font[52]{Simulation Preliminary}");
  //   h1_tex->SetNDC();
  //   h1_tex->SetTextFont(42);
  //   h1_tex->SetTextSize(0.0555); //0.0625
  //   h1_tex->SetLineWidth(2);
  //   h1_tex->Draw();
  //   h1_tex = new TLatex(0.18,0.77,"#font[52]{Simulation Preliminary}");
  //   h1_tex->SetNDC();
  //   h1_tex->SetTextFont(42);
  //   h1_tex->SetTextSize(0.05); //0.0625
  //   h1_tex->SetLineWidth(2);
  //   h1_tex->Draw();
  //   h1_tex = new TLatex(0.96,0.936,"36 fb^{-1} (13 TeV)");
  //   h1_tex->SetNDC();
  //   h1_tex->SetTextAlign(31);
  //   h1_tex->SetTextFont(42);
  //   h1_tex->SetTextSize(0.0575);
  //   h1_tex->SetLineWidth(2);
  //   // tex->Draw();
  

  //   c1237->SaveAs("./plotEfficTest_WPABC/h1_effic_tau32_nvtxg_WPA.pdf");

  //--------------------------------------------------------------------------------------------------------------




  //  TH1D *    h2_Effic_Denom_pup0P                           = (TH1D *) fTop2->Get( "h_Effic_Denom_pup0P"                            );
  //  TH1D *    h2_Effic_Denom_jet0P                           = (TH1D *) fTop2->Get( "h_Effic_Denom_jet0P"                            );
  //  TH1D *    h2_Effic_Denom_jet0Y                           = (TH1D *) fTop2->Get( "h_Effic_Denom_jet0Y"                            );
  //  TH1D *    h2_Effic_Denom_nvtxg                           = (TH1D *) fTop2->Get( "h_Effic_Denom_nvtxg"                            );
  //  TH1D *    h2_Effic_Denom_jet0P_TopMatch                  = (TH1D *) fTop2->Get( "h_Effic_Denom_jet0P_TopMatch"                   );
  //  TH1D *    h2_Effic_Denom_jet0P_TopMatch_TopDist          = (TH1D *) fTop2->Get( "h_Effic_Denom_jet0P_TopMatch_TopDist"           );
  //  TH1D *    h2_Effic_puptag_tau32_pup0P                    = (TH1D *) fTop2->Get( "h_Effic_puptag_tau32_pup0P"                     );
  //  TH1D *    h2_Effic_puptag_tau32_jet0P                    = (TH1D *) fTop2->Get( "h_Effic_puptag_tau32_jet0P"                     );
  //  TH1D *    h2_Effic_puptag_tau32_jet0Y                    = (TH1D *) fTop2->Get( "h_Effic_puptag_tau32_jet0Y"                     );
  //  TH1D *    h2_Effic_puptag_tau32_nvtxg                    = (TH1D *) fTop2->Get( "h_Effic_puptag_tau32_nvtxg"                     );
  //  TH1D *    h2_Effic_puptag_tau32_jet0P_TopMatch           = (TH1D *) fTop2->Get( "h_Effic_puptag_tau32_jet0P_TopMatch"            );
  //  TH1D *    h2_Effic_puptag_tau32_jet0P_TopMatch_TopDist   = (TH1D *) fTop2->Get( "h_Effic_puptag_tau32_jet0P_TopMatch_TopDist"    );
  //  TH1D *    h2_Effic_chstag_tau32_pup0P                    = (TH1D *) fTop2->Get( "h_Effic_chstag_tau32_pup0P"                     );
  //  TH1D *    h2_Effic_chstag_tau32_jet0P                    = (TH1D *) fTop2->Get( "h_Effic_chstag_tau32_jet0P"                     );
  //  TH1D *    h2_Effic_chstag_tau32_jet0Y                    = (TH1D *) fTop2->Get( "h_Effic_chstag_tau32_jet0Y"                     );
  //  TH1D *    h2_Effic_chstag_tau32_nvtxg                    = (TH1D *) fTop2->Get( "h_Effic_chstag_tau32_nvtxg"                     );
  //  TH1D *    h2_Effic_chstag_tau32_jet0P_TopMatch           = (TH1D *) fTop2->Get( "h_Effic_chstag_tau32_jet0P_TopMatch"            );
  //  TH1D *    h2_Effic_chstag_tau32_jet0P_TopMatch_TopDist   = (TH1D *) fTop2->Get( "h_Effic_chstag_tau32_jet0P_TopMatch_TopDist"    );
  //  TH1D *    h2_Effic_puptag_mass_pup0P                     = (TH1D *) fTop2->Get( "h_Effic_puptag_mass_pup0P"                      );
  //  TH1D *    h2_Effic_puptag_mass_jet0P                     = (TH1D *) fTop2->Get( "h_Effic_puptag_mass_jet0P"                      );
  //  TH1D *    h2_Effic_puptag_mass_jet0Y                     = (TH1D *) fTop2->Get( "h_Effic_puptag_mass_jet0Y"                      );
  //  TH1D *    h2_Effic_puptag_mass_nvtxg                     = (TH1D *) fTop2->Get( "h_Effic_puptag_mass_nvtxg"                      );
  //  TH1D *    h2_Effic_puptag_mass_jet0P_TopMatch            = (TH1D *) fTop2->Get( "h_Effic_puptag_mass_jet0P_TopMatch"             );
  //  TH1D *    h2_Effic_puptag_mass_jet0P_TopMatch_TopDist    = (TH1D *) fTop2->Get( "h_Effic_puptag_mass_jet0P_TopMatch_TopDist"     );
  //  TH1D *    h2_Effic_chstag_mass_pup0P                     = (TH1D *) fTop2->Get( "h_Effic_chstag_mass_pup0P"                      );
  //  TH1D *    h2_Effic_chstag_mass_jet0P                     = (TH1D *) fTop2->Get( "h_Effic_chstag_mass_jet0P"                      );
  //  TH1D *    h2_Effic_chstag_mass_jet0Y                     = (TH1D *) fTop2->Get( "h_Effic_chstag_mass_jet0Y"                      );
  //  TH1D *    h2_Effic_chstag_mass_nvtxg                     = (TH1D *) fTop2->Get( "h_Effic_chstag_mass_nvtxg"                      );
  //  TH1D *    h2_Effic_chstag_mass_jet0P_TopMatch            = (TH1D *) fTop2->Get( "h_Effic_chstag_mass_jet0P_TopMatch"             );
  //  TH1D *    h2_Effic_chstag_mass_jet0P_TopMatch_TopDist    = (TH1D *) fTop2->Get( "h_Effic_chstag_mass_jet0P_TopMatch_TopDist"     );
  //  TH1D *    h2_Effic_puptag_t_pup0P                        = (TH1D *) fTop2->Get( "h_Effic_puptag_t_pup0P"                         );
  //  TH1D *    h2_Effic_puptag_t_jet0P                        = (TH1D *) fTop2->Get( "h_Effic_puptag_t_jet0P"                         );
  //  TH1D *    h2_Effic_puptag_t_jet0Y                        = (TH1D *) fTop2->Get( "h_Effic_puptag_t_jet0Y"                         );
  //  TH1D *    h2_Effic_puptag_t_nvtxg                        = (TH1D *) fTop2->Get( "h_Effic_puptag_t_nvtxg"                         );
  //  TH1D *    h2_Effic_puptag_t_jet0P_TopMatch               = (TH1D *) fTop2->Get( "h_Effic_puptag_t_jet0P_TopMatch"                );
  //  TH1D *    h2_Effic_puptag_t_jet0P_TopMatch_TopDist       = (TH1D *) fTop2->Get( "h_Effic_puptag_t_jet0P_TopMatch_TopDist"        );
  //  TH1D *    h2_Effic_chstag_t_pup0P                        = (TH1D *) fTop2->Get( "h_Effic_chstag_t_pup0P"                         );
  //  TH1D *    h2_Effic_chstag_t_jet0P                        = (TH1D *) fTop2->Get( "h_Effic_chstag_t_jet0P"                         );
  //  TH1D *    h2_Effic_chstag_t_jet0Y                        = (TH1D *) fTop2->Get( "h_Effic_chstag_t_jet0Y"                         );
  //  TH1D *    h2_Effic_chstag_t_nvtxg                        = (TH1D *) fTop2->Get( "h_Effic_chstag_t_nvtxg"                         );
  //  TH1D *    h2_Effic_chstag_t_jet0P_TopMatch               = (TH1D *) fTop2->Get( "h_Effic_chstag_t_jet0P_TopMatch"                );
  //  TH1D *    h2_Effic_chstag_t_jet0P_TopMatch_TopDist       = (TH1D *) fTop2->Get( "h_Effic_chstag_t_jet0P_TopMatch_TopDist"        );




  //  TH1D *    h2_new_Effic_Denom_pup0P                         = (TH1D*) h2_Effic_Denom_pup0P                            ->Clone();  
  //  TH1D *    h2_new_Effic_Denom_jet0P                         = (TH1D*) h2_Effic_Denom_jet0P                            ->Clone();  
  //  TH1D *    h2_new_Effic_Denom_jet0Y                         = (TH1D*) h2_Effic_Denom_jet0Y                            ->Clone();  
  //  TH1D *    h2_new_Effic_Denom_nvtxg                         = (TH1D*) h2_Effic_Denom_nvtxg                            ->Clone();  
  //  TH1D *    h2_new_Effic_Denom_jet0P_TopMatch                = (TH1D*) h2_Effic_Denom_jet0P_TopMatch                   ->Clone();  
  //  TH1D *    h2_new_Effic_Denom_jet0P_TopMatch_TopDist        = (TH1D*) h2_Effic_Denom_jet0P_TopMatch_TopDist           ->Clone();  
  //  TH1D *    h2_new_Effic_puptag_tau32_pup0P                  = (TH1D*) h2_Effic_puptag_tau32_pup0P                     ->Clone();  
  //  TH1D *    h2_new_Effic_puptag_tau32_jet0P                  = (TH1D*) h2_Effic_puptag_tau32_jet0P                     ->Clone();  
  //  TH1D *    h2_new_Effic_puptag_tau32_jet0Y                  = (TH1D*) h2_Effic_puptag_tau32_jet0Y                     ->Clone();  
  //  TH1D *    h2_new_Effic_puptag_tau32_nvtxg                  = (TH1D*) h2_Effic_puptag_tau32_nvtxg                     ->Clone();  
  //  TH1D *    h2_new_Effic_puptag_tau32_jet0P_TopMatch         = (TH1D*) h2_Effic_puptag_tau32_jet0P_TopMatch            ->Clone();  
  //  TH1D *    h2_new_Effic_puptag_tau32_jet0P_TopMatch_TopDist = (TH1D*) h2_Effic_puptag_tau32_jet0P_TopMatch_TopDist    ->Clone();  
  //  TH1D *    h2_new_Effic_chstag_tau32_pup0P                  = (TH1D*) h2_Effic_chstag_tau32_pup0P                     ->Clone();  
  //  TH1D *    h2_new_Effic_chstag_tau32_jet0P                  = (TH1D*) h2_Effic_chstag_tau32_jet0P                     ->Clone();  
  //  TH1D *    h2_new_Effic_chstag_tau32_jet0Y                  = (TH1D*) h2_Effic_chstag_tau32_jet0Y                     ->Clone();  
  //  TH1D *    h2_new_Effic_chstag_tau32_nvtxg                  = (TH1D*) h2_Effic_chstag_tau32_nvtxg                     ->Clone();  
  //  TH1D *    h2_new_Effic_chstag_tau32_jet0P_TopMatch         = (TH1D*) h2_Effic_chstag_tau32_jet0P_TopMatch            ->Clone();  
  //  TH1D *    h2_new_Effic_chstag_tau32_jet0P_TopMatch_TopDist = (TH1D*) h2_Effic_chstag_tau32_jet0P_TopMatch_TopDist    ->Clone();  
  //  TH1D *    h2_new_Effic_puptag_mass_pup0P                   = (TH1D*) h2_Effic_puptag_mass_pup0P                      ->Clone();  
  //  TH1D *    h2_new_Effic_puptag_mass_jet0P                   = (TH1D*) h2_Effic_puptag_mass_jet0P                      ->Clone();  
  //  TH1D *    h2_new_Effic_puptag_mass_jet0Y                   = (TH1D*) h2_Effic_puptag_mass_jet0Y                      ->Clone();  
  //  TH1D *    h2_new_Effic_puptag_mass_nvtxg                   = (TH1D*) h2_Effic_puptag_mass_nvtxg                      ->Clone();  
  //  TH1D *    h2_new_Effic_puptag_mass_jet0P_TopMatch          = (TH1D*) h2_Effic_puptag_mass_jet0P_TopMatch             ->Clone();  
  //  TH1D *    h2_new_Effic_puptag_mass_jet0P_TopMatch_TopDist  = (TH1D*) h2_Effic_puptag_mass_jet0P_TopMatch_TopDist     ->Clone();  
  //  TH1D *    h2_new_Effic_chstag_mass_pup0P                   = (TH1D*) h2_Effic_chstag_mass_pup0P                      ->Clone();  
  //  TH1D *    h2_new_Effic_chstag_mass_jet0P                   = (TH1D*) h2_Effic_chstag_mass_jet0P                      ->Clone();  
  //  TH1D *    h2_new_Effic_chstag_mass_jet0Y                   = (TH1D*) h2_Effic_chstag_mass_jet0Y                      ->Clone();  
  //  TH1D *    h2_new_Effic_chstag_mass_nvtxg                   = (TH1D*) h2_Effic_chstag_mass_nvtxg                      ->Clone();  
  //  TH1D *    h2_new_Effic_chstag_mass_jet0P_TopMatch          = (TH1D*) h2_Effic_chstag_mass_jet0P_TopMatch             ->Clone();  
  //  TH1D *    h2_new_Effic_chstag_mass_jet0P_TopMatch_TopDist  = (TH1D*) h2_Effic_chstag_mass_jet0P_TopMatch_TopDist     ->Clone();  
  //  TH1D *    h2_new_Effic_puptag_t_pup0P                      = (TH1D*) h2_Effic_puptag_t_pup0P                         ->Clone();  
  //  TH1D *    h2_new_Effic_puptag_t_jet0P                      = (TH1D*) h2_Effic_puptag_t_jet0P                         ->Clone();  
  //  TH1D *    h2_new_Effic_puptag_t_jet0Y                      = (TH1D*) h2_Effic_puptag_t_jet0Y                         ->Clone();  
  //  TH1D *    h2_new_Effic_puptag_t_nvtxg                      = (TH1D*) h2_Effic_puptag_t_nvtxg                         ->Clone();  
  //  TH1D *    h2_new_Effic_puptag_t_jet0P_TopMatch             = (TH1D*) h2_Effic_puptag_t_jet0P_TopMatch                ->Clone();  
  //  TH1D *    h2_new_Effic_puptag_t_jet0P_TopMatch_TopDist     = (TH1D*) h2_Effic_puptag_t_jet0P_TopMatch_TopDist        ->Clone();  
  //  TH1D *    h2_new_Effic_chstag_t_pup0P                      = (TH1D*) h2_Effic_chstag_t_pup0P                         ->Clone();  
  //  TH1D *    h2_new_Effic_chstag_t_jet0P                      = (TH1D*) h2_Effic_chstag_t_jet0P                         ->Clone();  
  //  TH1D *    h2_new_Effic_chstag_t_jet0Y                      = (TH1D*) h2_Effic_chstag_t_jet0Y                         ->Clone();  
  //  TH1D *    h2_new_Effic_chstag_t_nvtxg                      = (TH1D*) h2_Effic_chstag_t_nvtxg                         ->Clone();  
  //  TH1D *    h2_new_Effic_chstag_t_jet0P_TopMatch             = (TH1D*) h2_Effic_chstag_t_jet0P_TopMatch                ->Clone();  
  //  TH1D *    h2_new_Effic_chstag_t_jet0P_TopMatch_TopDist     = (TH1D*) h2_Effic_chstag_t_jet0P_TopMatch_TopDist        ->Clone();  


  // TH1D * h2_rebin_Effic_Denom_pup0P                          ;  
  // TH1D * h2_rebin_Effic_Denom_jet0P                          ;  
  // TH1D * h2_rebin_Effic_Denom_jet0Y                          ;  
  // TH1D * h2_rebin_Effic_Denom_nvtxg                          ;  
  // TH1D * h2_rebin_Effic_Denom_jet0P_TopMatch                 ;  
  // TH1D * h2_rebin_Effic_Denom_jet0P_TopMatch_TopDist         ;  
  // TH1D * h2_rebin_Effic_puptag_tau32_pup0P                   ;  
  // TH1D * h2_rebin_Effic_puptag_tau32_jet0P                   ;  
  // TH1D * h2_rebin_Effic_puptag_tau32_jet0Y                   ;  
  // TH1D * h2_rebin_Effic_puptag_tau32_nvtxg                   ;  
  // TH1D * h2_rebin_Effic_puptag_tau32_jet0P_TopMatch          ;  
  // TH1D * h2_rebin_Effic_puptag_tau32_jet0P_TopMatch_TopDist  ;  
  // TH1D * h2_rebin_Effic_chstag_tau32_pup0P                   ;  
  // TH1D * h2_rebin_Effic_chstag_tau32_jet0P                   ;  
  // TH1D * h2_rebin_Effic_chstag_tau32_jet0Y                   ;  
  // TH1D * h2_rebin_Effic_chstag_tau32_nvtxg                   ;  
  // TH1D * h2_rebin_Effic_chstag_tau32_jet0P_TopMatch          ;  
  // TH1D * h2_rebin_Effic_chstag_tau32_jet0P_TopMatch_TopDist  ;  
  // TH1D * h2_rebin_Effic_puptag_mass_pup0P                    ;  
  // TH1D * h2_rebin_Effic_puptag_mass_jet0P                    ;  
  // TH1D * h2_rebin_Effic_puptag_mass_jet0Y                    ;  
  // TH1D * h2_rebin_Effic_puptag_mass_nvtxg                    ;  
  // TH1D * h2_rebin_Effic_puptag_mass_jet0P_TopMatch           ;  
  // TH1D * h2_rebin_Effic_puptag_mass_jet0P_TopMatch_TopDist   ;  
  // TH1D * h2_rebin_Effic_chstag_mass_pup0P                    ;  
  // TH1D * h2_rebin_Effic_chstag_mass_jet0P                    ;  
  // TH1D * h2_rebin_Effic_chstag_mass_jet0Y                    ;  
  // TH1D * h2_rebin_Effic_chstag_mass_nvtxg                    ;  
  // TH1D * h2_rebin_Effic_chstag_mass_jet0P_TopMatch           ;  
  // TH1D * h2_rebin_Effic_chstag_mass_jet0P_TopMatch_TopDist   ;  
  // TH1D * h2_rebin_Effic_puptag_t_pup0P                       ;  
  // TH1D * h2_rebin_Effic_puptag_t_jet0P                       ;  
  // TH1D * h2_rebin_Effic_puptag_t_jet0Y                       ;  
  // TH1D * h2_rebin_Effic_puptag_t_nvtxg                       ;  
  // TH1D * h2_rebin_Effic_puptag_t_jet0P_TopMatch              ;  
  // TH1D * h2_rebin_Effic_puptag_t_jet0P_TopMatch_TopDist      ;  
  // TH1D * h2_rebin_Effic_chstag_t_pup0P                       ;  
  // TH1D * h2_rebin_Effic_chstag_t_jet0P                       ;  
  // TH1D * h2_rebin_Effic_chstag_t_jet0Y                       ;  
  // TH1D * h2_rebin_Effic_chstag_t_nvtxg                       ;  
  // TH1D * h2_rebin_Effic_chstag_t_jet0P_TopMatch              ;  
  // TH1D * h2_rebin_Effic_chstag_t_jet0P_TopMatch_TopDist      ;  



  // h2_rebin_Effic_Denom_nvtxg         = (TH1D*)h2_new_Effic_Denom_nvtxg           ->Rebin(nbins_nvtx-1,"h2_rebin_Effic_Denom_nvtxg"       ,xbins_nvtx);
  // h2_rebin_Effic_puptag_tau32_nvtxg  = (TH1D*)h2_new_Effic_puptag_tau32_nvtxg    ->Rebin(nbins_nvtx-1,"h2_rebin_Effic_puptag_tau32_nvtxg",xbins_nvtx);
  // h2_rebin_Effic_chstag_tau32_nvtxg  = (TH1D*)h2_new_Effic_chstag_tau32_nvtxg    ->Rebin(nbins_nvtx-1,"h2_rebin_Effic_chstag_tau32_nvtxg",xbins_nvtx);
  // h2_rebin_Effic_puptag_mass_nvtxg   = (TH1D*)h2_new_Effic_puptag_mass_nvtxg     ->Rebin(nbins_nvtx-1,"h2_rebin_Effic_puptag_mass_nvtxg" ,xbins_nvtx);
  // h2_rebin_Effic_chstag_mass_nvtxg   = (TH1D*)h2_new_Effic_chstag_mass_nvtxg     ->Rebin(nbins_nvtx-1,"h2_rebin_Effic_chstag_mass_nvtxg" ,xbins_nvtx);
  // h2_rebin_Effic_puptag_t_nvtxg      = (TH1D*)h2_new_Effic_puptag_t_nvtxg        ->Rebin(nbins_nvtx-1,"h2_rebin_Effic_puptag_t_nvtxg"    ,xbins_nvtx);
  // h2_rebin_Effic_chstag_t_nvtxg      = (TH1D*)h2_new_Effic_chstag_t_nvtxg        ->Rebin(nbins_nvtx-1,"h2_rebin_Effic_chstag_t_nvtxg"    ,xbins_nvtx);

  // h2_Effic_Denom_pup0P                          ->Rebin(10);
  // h2_Effic_Denom_jet0P                          ->Rebin(10);
  // h2_Effic_Denom_jet0Y                          ->Rebin(10);
  // h2_Effic_Denom_jet0P_TopMatch                 ->Rebin(10);
  // h2_Effic_Denom_jet0P_TopMatch_TopDist         ->Rebin(10);
  // h2_Effic_puptag_tau32_pup0P                   ->Rebin(10);
  // h2_Effic_puptag_tau32_jet0P                   ->Rebin(10);
  // h2_Effic_puptag_tau32_jet0Y                   ->Rebin(10);
  // h2_Effic_puptag_tau32_jet0P_TopMatch          ->Rebin(10);
  // h2_Effic_puptag_tau32_jet0P_TopMatch_TopDist  ->Rebin(10);
  // h2_Effic_chstag_tau32_pup0P                   ->Rebin(10);
  // h2_Effic_chstag_tau32_jet0P                   ->Rebin(10);
  // h2_Effic_chstag_tau32_jet0Y                   ->Rebin(10);
  // h2_Effic_chstag_tau32_jet0P_TopMatch          ->Rebin(10);
  // h2_Effic_chstag_tau32_jet0P_TopMatch_TopDist  ->Rebin(10);
  // h2_Effic_puptag_mass_pup0P                    ->Rebin(10);
  // h2_Effic_puptag_mass_jet0P                    ->Rebin(10);
  // h2_Effic_puptag_mass_jet0Y                    ->Rebin(10);
  // h2_Effic_puptag_mass_jet0P_TopMatch           ->Rebin(10);
  // h2_Effic_puptag_mass_jet0P_TopMatch_TopDist   ->Rebin(10);
  // h2_Effic_chstag_mass_pup0P                    ->Rebin(10);
  // h2_Effic_chstag_mass_jet0P                    ->Rebin(10);
  // h2_Effic_chstag_mass_jet0Y                    ->Rebin(10);
  // h2_Effic_chstag_mass_jet0P_TopMatch           ->Rebin(10);
  // h2_Effic_chstag_mass_jet0P_TopMatch_TopDist   ->Rebin(10);
  // h2_Effic_puptag_t_pup0P                       ->Rebin(10);
  // h2_Effic_puptag_t_jet0P                       ->Rebin(10);
  // h2_Effic_puptag_t_jet0Y                       ->Rebin(10);
  // h2_Effic_puptag_t_jet0P_TopMatch              ->Rebin(10);
  // h2_Effic_puptag_t_jet0P_TopMatch_TopDist      ->Rebin(10);
  // h2_Effic_chstag_t_pup0P                       ->Rebin(10);
  // h2_Effic_chstag_t_jet0P                       ->Rebin(10);
  // h2_Effic_chstag_t_jet0Y                       ->Rebin(10);
  // h2_Effic_chstag_t_jet0P_TopMatch              ->Rebin(10);
  // h2_Effic_chstag_t_jet0P_TopMatch_TopDist      ->Rebin(10);


  // TH1D *effic_tau32_pup0P =(TH1D*) h2_Effic_puptag_tau32_pup0P->Clone();
  // // effic_tau32_pup0P->Reset();
  // effic_tau32_pup0P->Divide( h2_Effic_puptag_tau32_pup0P, h2_Effic_Denom_pup0P,1,1,"B");

  // TH1D *effic_tau32_jet0P =(TH1D*) h2_Effic_puptag_tau32_jet0P->Clone();
  // // effic_tau32_jet0P->Reset();
  // effic_tau32_jet0P->Divide( h2_Effic_puptag_tau32_jet0P, h2_Effic_Denom_jet0P,1,1,"B");

  // TH1D *effic_chstag_tau32_jet0P =(TH1D*) h2_Effic_chstag_tau32_jet0P->Clone();
  // // effic_chstag_tau32_jet0P->Reset();
  // effic_chstag_tau32_jet0P->Divide( h2_Effic_chstag_tau32_jet0P, h2_Effic_Denom_jet0P,1,1,"B");


  // TH1D *effic_mass_jet0P =(TH1D*) h2_Effic_puptag_mass_jet0P->Clone();
  // // effic_mass_jet0P->Reset();
  // effic_mass_jet0P->Divide( h2_Effic_puptag_mass_jet0P, h2_Effic_Denom_jet0P,1,1,"B");

  // TH1D *effic_t_jet0P =(TH1D*) h2_Effic_puptag_t_jet0P->Clone();
  // // effic_t_jet0P->Reset();
  // effic_t_jet0P->Divide( h2_Effic_puptag_t_jet0P, h2_Effic_Denom_jet0P,1,1,"B");

  // effic_tau32_pup0P ->SetLineColor(2);    
  // effic_tau32_jet0P ->SetLineColor(3);        
  // effic_mass_jet0P  ->SetLineColor(4);       
  // effic_t_jet0P     ->SetLineColor(5);
  // effic_chstag_tau32_jet0P->SetLineColor(6);

  // effic_tau32_pup0P->GetXaxis()->SetRangeUser(300,4000);
  // effic_tau32_pup0P ->Draw("HIST");          
  // effic_tau32_jet0P ->Draw("HISTsame");
  // effic_chstag_tau32_jet0P  ->Draw("HISTsame");         
  // effic_mass_jet0P  ->Draw("HISTsame");         
  // effic_t_jet0P     ->Draw("HISTsame");      
  // c1237->SaveAs("./plotsEfficTest/effic_tau32_pup0P.pdf");

  // cout<<"h2_Effic_puptag_tau32_jet0P_TopMatch "<<h2_Effic_puptag_tau32_jet0P_TopMatch->Integral()<<endl;
  // cout<<"h2_Effic_Denom_jet0P_TopMatch "<<h2_Effic_Denom_jet0P_TopMatch->Integral()<<endl;

  // cout<<"h2_Effic_puptag_tau32_jet0P_TopMatch_TopDist "<<h2_Effic_puptag_tau32_jet0P_TopMatch_TopDist->Integral()<<endl;
  // cout<<"h2_Effic_Denom_jet0P_TopMatch_TopDist "<<h2_Effic_Denom_jet0P_TopMatch_TopDist->Integral()<<endl;


  // TH1D *effic_puptag_tau32_jet0P_TopMatch =(TH1D*) h2_Effic_puptag_tau32_jet0P_TopMatch->Clone();
  // effic_puptag_tau32_jet0P_TopMatch->Reset();
  // effic_puptag_tau32_jet0P_TopMatch->Divide( h2_Effic_puptag_tau32_jet0P_TopMatch, h2_Effic_Denom_jet0P_TopMatch,1,1,"B");

  // TH1D *effic_puptag_tau32_jet0P_TopMatch_TopDist =(TH1D*) h2_Effic_puptag_tau32_jet0P_TopMatch_TopDist->Clone();
  // effic_puptag_tau32_jet0P_TopMatch_TopDist->Reset();
  // effic_puptag_tau32_jet0P_TopMatch_TopDist->Divide( h2_Effic_puptag_tau32_jet0P_TopMatch_TopDist, h2_Effic_Denom_jet0P_TopMatch_TopDist,1,1,"B");

  // effic_puptag_tau32_jet0P_TopMatch         ->SetLineColor(1);
  // effic_puptag_tau32_jet0P_TopMatch_TopDist->SetLineColor(2);

  // effic_puptag_tau32_jet0P_TopMatch_TopDist->GetXaxis()->SetRangeUser(300,4000);
  // effic_puptag_tau32_jet0P_TopMatch_TopDist ->Draw("HIST");          
  // effic_puptag_tau32_jet0P_TopMatch ->Draw("HISTsame");    
  // c1237->SaveAs("./plotsEfficTest/effic_match.pdf");





  // TH1D *h2_effic_puptag_tau32_nvtxg =(TH1D*) h2_rebin_Effic_puptag_tau32_nvtxg->Clone();
  // // h2_effic_puptag_tau32_nvtxg->Reset();
  // h2_effic_puptag_tau32_nvtxg->Divide( h2_rebin_Effic_puptag_tau32_nvtxg, h2_rebin_Effic_Denom_nvtxg,1,1,"B");

  // TH1D *h2_effic_puptag_mass_nvtxg =(TH1D*) h2_rebin_Effic_puptag_mass_nvtxg->Clone();
  // // h2_effic_puptag_mass_nvtxg->Reset();
  // h2_effic_puptag_mass_nvtxg->Divide( h2_rebin_Effic_puptag_mass_nvtxg, h2_rebin_Effic_Denom_nvtxg,1,1,"B");

  // TH1D *h2_effic_puptag_t_nvtxg =(TH1D*) h2_rebin_Effic_puptag_t_nvtxg->Clone();
  // // h2_effic_puptag_t_nvtxg->Reset();
  // h2_effic_puptag_t_nvtxg->Divide( h2_rebin_Effic_puptag_t_nvtxg, h2_rebin_Effic_Denom_nvtxg,1,1,"B");


  // TH1D *h2_effic_chstag_tau32_nvtxg =(TH1D*) h2_rebin_Effic_chstag_tau32_nvtxg->Clone();
  // // h2_effic_chstag_tau32_nvtxg->Reset();
  // h2_effic_chstag_tau32_nvtxg->Divide( h2_rebin_Effic_chstag_tau32_nvtxg, h2_rebin_Effic_Denom_nvtxg,1,1,"B");

  // TH1D *h2_effic_chstag_mass_nvtxg =(TH1D*) h2_rebin_Effic_chstag_mass_nvtxg->Clone();
  // // h2_effic_chstag_mass_nvtxg->Reset();
  // h2_effic_chstag_mass_nvtxg->Divide( h2_rebin_Effic_chstag_mass_nvtxg, h2_rebin_Effic_Denom_nvtxg,1,1,"B");

  // TH1D *h2_effic_chstag_t_nvtxg =(TH1D*) h2_rebin_Effic_chstag_t_nvtxg->Clone();
  // // h2_effic_chstag_t_nvtxg->Reset();
  // h2_effic_chstag_t_nvtxg->Divide( h2_rebin_Effic_chstag_t_nvtxg, h2_rebin_Effic_Denom_nvtxg,1,1,"B");

  // h2_effic_puptag_tau32_nvtxg ->SetMarkerStyle(20);        
  // h2_effic_puptag_mass_nvtxg  ->SetMarkerStyle(21);       
  // h2_effic_puptag_t_nvtxg     ->SetMarkerStyle(22);

  // h2_effic_chstag_tau32_nvtxg ->SetMarkerStyle(24);        
  // h2_effic_chstag_mass_nvtxg  ->SetMarkerStyle(25);       
  // h2_effic_chstag_t_nvtxg     ->SetMarkerStyle(26);

  // h2_effic_puptag_tau32_nvtxg ->SetMarkerColor(6);              
  // h2_effic_puptag_mass_nvtxg  ->SetMarkerColor(kBlue);         
  // h2_effic_puptag_t_nvtxg     ->SetMarkerColor(kOrange+1);

  // h2_effic_chstag_tau32_nvtxg ->SetMarkerColor(6);        
  // h2_effic_chstag_mass_nvtxg  ->SetMarkerColor(kBlue);       
  // h2_effic_chstag_t_nvtxg     ->SetMarkerColor(kOrange+1);

  // h2_effic_puptag_tau32_nvtxg ->SetLineColor(6);           
  // h2_effic_puptag_mass_nvtxg  ->SetLineColor(kBlue);      
  // h2_effic_puptag_t_nvtxg     ->SetLineColor(kOrange+1);

  // h2_effic_chstag_tau32_nvtxg ->SetLineColor(6);           
  // h2_effic_chstag_mass_nvtxg  ->SetLineColor(kBlue);      
  // h2_effic_chstag_t_nvtxg     ->SetLineColor(kOrange+1);

  // h2_effic_puptag_tau32_nvtxg ->SetLineWidth(2);   
  // h2_effic_puptag_mass_nvtxg  ->SetLineWidth(2);  
  // h2_effic_puptag_t_nvtxg     ->SetLineWidth(2);

  // h2_effic_chstag_tau32_nvtxg ->SetLineWidth(2);   
  // h2_effic_chstag_mass_nvtxg  ->SetLineWidth(2);  
  // h2_effic_chstag_t_nvtxg     ->SetLineWidth(2);




  //   h2_effic_puptag_tau32_nvtxg->SetTitle(title.c_str());

  //   h2_effic_puptag_tau32_nvtxg->SetStats(0);


  //   h2_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleSize(0.065);
  //   h2_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleOffset(0.9); 
  //   h2_effic_puptag_tau32_nvtxg->GetYaxis()->SetLabelSize(0.06);

  //   h2_effic_puptag_tau32_nvtxg->GetXaxis()->SetNdivisions(506);
  //   h2_effic_puptag_tau32_nvtxg->GetXaxis()->SetLabelFont(42);
  //   h2_effic_puptag_tau32_nvtxg->GetXaxis()->SetLabelSize(0.05);
  //   h2_effic_puptag_tau32_nvtxg->GetXaxis()->SetTitleSize(0.056);
  //   h2_effic_puptag_tau32_nvtxg->GetXaxis()->SetTickLength(0.045);
  //   h2_effic_puptag_tau32_nvtxg->GetXaxis()->SetTitleOffset(1.15);
  //   h2_effic_puptag_tau32_nvtxg->GetXaxis()->SetTitleFont(42);

  //   h2_effic_puptag_tau32_nvtxg->GetYaxis()->SetNdivisions(506);
  //   h2_effic_puptag_tau32_nvtxg->GetYaxis()->SetLabelFont(42);
  //   h2_effic_puptag_tau32_nvtxg->GetYaxis()->SetLabelSize(0.05);
  //   h2_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleSize(0.06125);
  //   h2_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleOffset(1.17);
  //   h2_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleFont(42);

  //   h2_effic_puptag_tau32_nvtxg->GetZaxis()->SetLabelFont(42);
  //   h2_effic_puptag_tau32_nvtxg->GetZaxis()->SetLabelSize(0.0425);
  //   h2_effic_puptag_tau32_nvtxg->GetZaxis()->SetTitleSize(0.0475);
  //   h2_effic_puptag_tau32_nvtxg->GetZaxis()->SetTitleFont(42);

  // h2_effic_puptag_tau32_nvtxg->GetYaxis()->SetRangeUser(0.0,1.1);
  // h2_effic_puptag_tau32_nvtxg ->Draw("");
  // h2_effic_puptag_mass_nvtxg  ->Draw("same");         
  // h2_effic_puptag_t_nvtxg     ->Draw("same");      

  // h2_effic_chstag_tau32_nvtxg ->Draw("same");
  // h2_effic_chstag_mass_nvtxg  ->Draw("same");         
  // h2_effic_chstag_t_nvtxg     ->Draw("same");      





  //   TLegend * h2_leg;
  //   h2_leg = new TLegend( 0.58, 0.6,0.95, 0.88);  //( 0.56, 0.69,0.98, 0.89);
  //   h2_leg->SetBorderSize(0);
  //   h2_leg->SetFillColor(0);
  //   h2_leg->SetFillStyle(4000);
  //   h2_leg->SetTextSize(0.04);   //0.038
  //   h2_leg->SetMargin(0.18 );
  //   h2_leg->SetHeader("Medium t-tag");
  //   h2_leg->AddEntry( h2_effic_chstag_mass_nvtxg    , "CHS: m_{SD} tag"            , "LP" );
  //   h2_leg->AddEntry( h2_effic_chstag_tau32_nvtxg   , "CHS: #tau_{32} tag"         , "LP" );
  //   h2_leg->AddEntry( h2_effic_chstag_t_nvtxg       , "CHS: m_{SD}+#tau_{32} tag"  , "LP" );
  
  //   h2_leg->AddEntry( h2_effic_puptag_mass_nvtxg    , "PUPPI: m_{SD} tag"                     , "LP" );
  //   h2_leg->AddEntry( h2_effic_puptag_tau32_nvtxg   , "PUPPI: #tau_{32} tag"                  , "LP" );
  //   h2_leg->AddEntry( h2_effic_puptag_t_nvtxg       , "PUPPI: m_{SD}+#tau_{32} tag"           , "LP" );
  //   h2_leg->Draw("same");

  //   TLatex *   h2_tex = new TLatex(0.18,0.83,"#font[62]{CMS}");// #font[52]{Simulation Preliminary}");
  //   h2_tex->SetNDC();
  //   h2_tex->SetTextFont(42);
  //   h2_tex->SetTextSize(0.0555); //0.0625
  //   h2_tex->SetLineWidth(2);
  //   h2_tex->Draw();
  //   h2_tex = new TLatex(0.18,0.77,"#font[52]{Simulation Preliminary}");
  //   h2_tex->SetNDC();
  //   h2_tex->SetTextFont(42);
  //   h2_tex->SetTextSize(0.05); //0.0625
  //   h2_tex->SetLineWidth(2);
  //   h2_tex->Draw();
  //   h2_tex = new TLatex(0.96,0.936,"36 fb^{-1} (13 TeV)");
  //   h2_tex->SetNDC();
  //   h2_tex->SetTextAlign(31);
  //   h2_tex->SetTextFont(42);
  //   h2_tex->SetTextSize(0.0575);
  //   h2_tex->SetLineWidth(2);
  //   // tex->Draw();
  

  //   c1237->SaveAs("./plotEfficTest_WPABC/h2_effic_tau32_nvtxg_WPB.pdf");

  //---------------------------------------------------------------------------------------------------------------------------



  //  TH1D *    h3_Effic_Denom_pup0P                           = (TH1D *) fTop3->Get( "h_Effic_Denom_pup0P"                            );
  //  TH1D *    h3_Effic_Denom_jet0P                           = (TH1D *) fTop3->Get( "h_Effic_Denom_jet0P"                            );
  //  TH1D *    h3_Effic_Denom_jet0Y                           = (TH1D *) fTop3->Get( "h_Effic_Denom_jet0Y"                            );
  //  TH1D *    h3_Effic_Denom_nvtxg                           = (TH1D *) fTop3->Get( "h_Effic_Denom_nvtxg"                            );
  //  TH1D *    h3_Effic_Denom_jet0P_TopMatch                  = (TH1D *) fTop3->Get( "h_Effic_Denom_jet0P_TopMatch"                   );
  //  TH1D *    h3_Effic_Denom_jet0P_TopMatch_TopDist          = (TH1D *) fTop3->Get( "h_Effic_Denom_jet0P_TopMatch_TopDist"           );
  //  TH1D *    h3_Effic_puptag_tau32_pup0P                    = (TH1D *) fTop3->Get( "h_Effic_puptag_tau32_pup0P"                     );
  //  TH1D *    h3_Effic_puptag_tau32_jet0P                    = (TH1D *) fTop3->Get( "h_Effic_puptag_tau32_jet0P"                     );
  //  TH1D *    h3_Effic_puptag_tau32_jet0Y                    = (TH1D *) fTop3->Get( "h_Effic_puptag_tau32_jet0Y"                     );
  //  TH1D *    h3_Effic_puptag_tau32_nvtxg                    = (TH1D *) fTop3->Get( "h_Effic_puptag_tau32_nvtxg"                     );
  //  TH1D *    h3_Effic_puptag_tau32_jet0P_TopMatch           = (TH1D *) fTop3->Get( "h_Effic_puptag_tau32_jet0P_TopMatch"            );
  //  TH1D *    h3_Effic_puptag_tau32_jet0P_TopMatch_TopDist   = (TH1D *) fTop3->Get( "h_Effic_puptag_tau32_jet0P_TopMatch_TopDist"    );
  //  TH1D *    h3_Effic_chstag_tau32_pup0P                    = (TH1D *) fTop3->Get( "h_Effic_chstag_tau32_pup0P"                     );
  //  TH1D *    h3_Effic_chstag_tau32_jet0P                    = (TH1D *) fTop3->Get( "h_Effic_chstag_tau32_jet0P"                     );
  //  TH1D *    h3_Effic_chstag_tau32_jet0Y                    = (TH1D *) fTop3->Get( "h_Effic_chstag_tau32_jet0Y"                     );
  //  TH1D *    h3_Effic_chstag_tau32_nvtxg                    = (TH1D *) fTop3->Get( "h_Effic_chstag_tau32_nvtxg"                     );
  //  TH1D *    h3_Effic_chstag_tau32_jet0P_TopMatch           = (TH1D *) fTop3->Get( "h_Effic_chstag_tau32_jet0P_TopMatch"            );
  //  TH1D *    h3_Effic_chstag_tau32_jet0P_TopMatch_TopDist   = (TH1D *) fTop3->Get( "h_Effic_chstag_tau32_jet0P_TopMatch_TopDist"    );
  //  TH1D *    h3_Effic_puptag_mass_pup0P                     = (TH1D *) fTop3->Get( "h_Effic_puptag_mass_pup0P"                      );
  //  TH1D *    h3_Effic_puptag_mass_jet0P                     = (TH1D *) fTop3->Get( "h_Effic_puptag_mass_jet0P"                      );
  //  TH1D *    h3_Effic_puptag_mass_jet0Y                     = (TH1D *) fTop3->Get( "h_Effic_puptag_mass_jet0Y"                      );
  //  TH1D *    h3_Effic_puptag_mass_nvtxg                     = (TH1D *) fTop3->Get( "h_Effic_puptag_mass_nvtxg"                      );
  //  TH1D *    h3_Effic_puptag_mass_jet0P_TopMatch            = (TH1D *) fTop3->Get( "h_Effic_puptag_mass_jet0P_TopMatch"             );
  //  TH1D *    h3_Effic_puptag_mass_jet0P_TopMatch_TopDist    = (TH1D *) fTop3->Get( "h_Effic_puptag_mass_jet0P_TopMatch_TopDist"     );
  //  TH1D *    h3_Effic_chstag_mass_pup0P                     = (TH1D *) fTop3->Get( "h_Effic_chstag_mass_pup0P"                      );
  //  TH1D *    h3_Effic_chstag_mass_jet0P                     = (TH1D *) fTop3->Get( "h_Effic_chstag_mass_jet0P"                      );
  //  TH1D *    h3_Effic_chstag_mass_jet0Y                     = (TH1D *) fTop3->Get( "h_Effic_chstag_mass_jet0Y"                      );
  //  TH1D *    h3_Effic_chstag_mass_nvtxg                     = (TH1D *) fTop3->Get( "h_Effic_chstag_mass_nvtxg"                      );
  //  TH1D *    h3_Effic_chstag_mass_jet0P_TopMatch            = (TH1D *) fTop3->Get( "h_Effic_chstag_mass_jet0P_TopMatch"             );
  //  TH1D *    h3_Effic_chstag_mass_jet0P_TopMatch_TopDist    = (TH1D *) fTop3->Get( "h_Effic_chstag_mass_jet0P_TopMatch_TopDist"     );
  //  TH1D *    h3_Effic_puptag_t_pup0P                        = (TH1D *) fTop3->Get( "h_Effic_puptag_t_pup0P"                         );
  //  TH1D *    h3_Effic_puptag_t_jet0P                        = (TH1D *) fTop3->Get( "h_Effic_puptag_t_jet0P"                         );
  //  TH1D *    h3_Effic_puptag_t_jet0Y                        = (TH1D *) fTop3->Get( "h_Effic_puptag_t_jet0Y"                         );
  //  TH1D *    h3_Effic_puptag_t_nvtxg                        = (TH1D *) fTop3->Get( "h_Effic_puptag_t_nvtxg"                         );
  //  TH1D *    h3_Effic_puptag_t_jet0P_TopMatch               = (TH1D *) fTop3->Get( "h_Effic_puptag_t_jet0P_TopMatch"                );
  //  TH1D *    h3_Effic_puptag_t_jet0P_TopMatch_TopDist       = (TH1D *) fTop3->Get( "h_Effic_puptag_t_jet0P_TopMatch_TopDist"        );
  //  TH1D *    h3_Effic_chstag_t_pup0P                        = (TH1D *) fTop3->Get( "h_Effic_chstag_t_pup0P"                         );
  //  TH1D *    h3_Effic_chstag_t_jet0P                        = (TH1D *) fTop3->Get( "h_Effic_chstag_t_jet0P"                         );
  //  TH1D *    h3_Effic_chstag_t_jet0Y                        = (TH1D *) fTop3->Get( "h_Effic_chstag_t_jet0Y"                         );
  //  TH1D *    h3_Effic_chstag_t_nvtxg                        = (TH1D *) fTop3->Get( "h_Effic_chstag_t_nvtxg"                         );
  //  TH1D *    h3_Effic_chstag_t_jet0P_TopMatch               = (TH1D *) fTop3->Get( "h_Effic_chstag_t_jet0P_TopMatch"                );
  //  TH1D *    h3_Effic_chstag_t_jet0P_TopMatch_TopDist       = (TH1D *) fTop3->Get( "h_Effic_chstag_t_jet0P_TopMatch_TopDist"        );




  //  TH1D *    h3_new_Effic_Denom_pup0P                         = (TH1D*) h3_Effic_Denom_pup0P                            ->Clone();  
  //  TH1D *    h3_new_Effic_Denom_jet0P                         = (TH1D*) h3_Effic_Denom_jet0P                            ->Clone();  
  //  TH1D *    h3_new_Effic_Denom_jet0Y                         = (TH1D*) h3_Effic_Denom_jet0Y                            ->Clone();  
  //  TH1D *    h3_new_Effic_Denom_nvtxg                         = (TH1D*) h3_Effic_Denom_nvtxg                            ->Clone();  
  //  TH1D *    h3_new_Effic_Denom_jet0P_TopMatch                = (TH1D*) h3_Effic_Denom_jet0P_TopMatch                   ->Clone();  
  //  TH1D *    h3_new_Effic_Denom_jet0P_TopMatch_TopDist        = (TH1D*) h3_Effic_Denom_jet0P_TopMatch_TopDist           ->Clone();  
  //  TH1D *    h3_new_Effic_puptag_tau32_pup0P                  = (TH1D*) h3_Effic_puptag_tau32_pup0P                     ->Clone();  
  //  TH1D *    h3_new_Effic_puptag_tau32_jet0P                  = (TH1D*) h3_Effic_puptag_tau32_jet0P                     ->Clone();  
  //  TH1D *    h3_new_Effic_puptag_tau32_jet0Y                  = (TH1D*) h3_Effic_puptag_tau32_jet0Y                     ->Clone();  
  //  TH1D *    h3_new_Effic_puptag_tau32_nvtxg                  = (TH1D*) h3_Effic_puptag_tau32_nvtxg                     ->Clone();  
  //  TH1D *    h3_new_Effic_puptag_tau32_jet0P_TopMatch         = (TH1D*) h3_Effic_puptag_tau32_jet0P_TopMatch            ->Clone();  
  //  TH1D *    h3_new_Effic_puptag_tau32_jet0P_TopMatch_TopDist = (TH1D*) h3_Effic_puptag_tau32_jet0P_TopMatch_TopDist    ->Clone();  
  //  TH1D *    h3_new_Effic_chstag_tau32_pup0P                  = (TH1D*) h3_Effic_chstag_tau32_pup0P                     ->Clone();  
  //  TH1D *    h3_new_Effic_chstag_tau32_jet0P                  = (TH1D*) h3_Effic_chstag_tau32_jet0P                     ->Clone();  
  //  TH1D *    h3_new_Effic_chstag_tau32_jet0Y                  = (TH1D*) h3_Effic_chstag_tau32_jet0Y                     ->Clone();  
  //  TH1D *    h3_new_Effic_chstag_tau32_nvtxg                  = (TH1D*) h3_Effic_chstag_tau32_nvtxg                     ->Clone();  
  //  TH1D *    h3_new_Effic_chstag_tau32_jet0P_TopMatch         = (TH1D*) h3_Effic_chstag_tau32_jet0P_TopMatch            ->Clone();  
  //  TH1D *    h3_new_Effic_chstag_tau32_jet0P_TopMatch_TopDist = (TH1D*) h3_Effic_chstag_tau32_jet0P_TopMatch_TopDist    ->Clone();  
  //  TH1D *    h3_new_Effic_puptag_mass_pup0P                   = (TH1D*) h3_Effic_puptag_mass_pup0P                      ->Clone();  
  //  TH1D *    h3_new_Effic_puptag_mass_jet0P                   = (TH1D*) h3_Effic_puptag_mass_jet0P                      ->Clone();  
  //  TH1D *    h3_new_Effic_puptag_mass_jet0Y                   = (TH1D*) h3_Effic_puptag_mass_jet0Y                      ->Clone();  
  //  TH1D *    h3_new_Effic_puptag_mass_nvtxg                   = (TH1D*) h3_Effic_puptag_mass_nvtxg                      ->Clone();  
  //  TH1D *    h3_new_Effic_puptag_mass_jet0P_TopMatch          = (TH1D*) h3_Effic_puptag_mass_jet0P_TopMatch             ->Clone();  
  //  TH1D *    h3_new_Effic_puptag_mass_jet0P_TopMatch_TopDist  = (TH1D*) h3_Effic_puptag_mass_jet0P_TopMatch_TopDist     ->Clone();  
  //  TH1D *    h3_new_Effic_chstag_mass_pup0P                   = (TH1D*) h3_Effic_chstag_mass_pup0P                      ->Clone();  
  //  TH1D *    h3_new_Effic_chstag_mass_jet0P                   = (TH1D*) h3_Effic_chstag_mass_jet0P                      ->Clone();  
  //  TH1D *    h3_new_Effic_chstag_mass_jet0Y                   = (TH1D*) h3_Effic_chstag_mass_jet0Y                      ->Clone();  
  //  TH1D *    h3_new_Effic_chstag_mass_nvtxg                   = (TH1D*) h3_Effic_chstag_mass_nvtxg                      ->Clone();  
  //  TH1D *    h3_new_Effic_chstag_mass_jet0P_TopMatch          = (TH1D*) h3_Effic_chstag_mass_jet0P_TopMatch             ->Clone();  
  //  TH1D *    h3_new_Effic_chstag_mass_jet0P_TopMatch_TopDist  = (TH1D*) h3_Effic_chstag_mass_jet0P_TopMatch_TopDist     ->Clone();  
  //  TH1D *    h3_new_Effic_puptag_t_pup0P                      = (TH1D*) h3_Effic_puptag_t_pup0P                         ->Clone();  
  //  TH1D *    h3_new_Effic_puptag_t_jet0P                      = (TH1D*) h3_Effic_puptag_t_jet0P                         ->Clone();  
  //  TH1D *    h3_new_Effic_puptag_t_jet0Y                      = (TH1D*) h3_Effic_puptag_t_jet0Y                         ->Clone();  
  //  TH1D *    h3_new_Effic_puptag_t_nvtxg                      = (TH1D*) h3_Effic_puptag_t_nvtxg                         ->Clone();  
  //  TH1D *    h3_new_Effic_puptag_t_jet0P_TopMatch             = (TH1D*) h3_Effic_puptag_t_jet0P_TopMatch                ->Clone();  
  //  TH1D *    h3_new_Effic_puptag_t_jet0P_TopMatch_TopDist     = (TH1D*) h3_Effic_puptag_t_jet0P_TopMatch_TopDist        ->Clone();  
  //  TH1D *    h3_new_Effic_chstag_t_pup0P                      = (TH1D*) h3_Effic_chstag_t_pup0P                         ->Clone();  
  //  TH1D *    h3_new_Effic_chstag_t_jet0P                      = (TH1D*) h3_Effic_chstag_t_jet0P                         ->Clone();  
  //  TH1D *    h3_new_Effic_chstag_t_jet0Y                      = (TH1D*) h3_Effic_chstag_t_jet0Y                         ->Clone();  
  //  TH1D *    h3_new_Effic_chstag_t_nvtxg                      = (TH1D*) h3_Effic_chstag_t_nvtxg                         ->Clone();  
  //  TH1D *    h3_new_Effic_chstag_t_jet0P_TopMatch             = (TH1D*) h3_Effic_chstag_t_jet0P_TopMatch                ->Clone();  
  //  TH1D *    h3_new_Effic_chstag_t_jet0P_TopMatch_TopDist     = (TH1D*) h3_Effic_chstag_t_jet0P_TopMatch_TopDist        ->Clone();  

  // TH1D * h3_rebin_Effic_Denom_pup0P                          ;  
  // TH1D * h3_rebin_Effic_Denom_jet0P                          ;  
  // TH1D * h3_rebin_Effic_Denom_jet0Y                          ;  
  // TH1D * h3_rebin_Effic_Denom_nvtxg                          ;  
  // TH1D * h3_rebin_Effic_Denom_jet0P_TopMatch                 ;  
  // TH1D * h3_rebin_Effic_Denom_jet0P_TopMatch_TopDist         ;  
  // TH1D * h3_rebin_Effic_puptag_tau32_pup0P                   ;  
  // TH1D * h3_rebin_Effic_puptag_tau32_jet0P                   ;  
  // TH1D * h3_rebin_Effic_puptag_tau32_jet0Y                   ;  
  // TH1D * h3_rebin_Effic_puptag_tau32_nvtxg                   ;  
  // TH1D * h3_rebin_Effic_puptag_tau32_jet0P_TopMatch          ;  
  // TH1D * h3_rebin_Effic_puptag_tau32_jet0P_TopMatch_TopDist  ;  
  // TH1D * h3_rebin_Effic_chstag_tau32_pup0P                   ;  
  // TH1D * h3_rebin_Effic_chstag_tau32_jet0P                   ;  
  // TH1D * h3_rebin_Effic_chstag_tau32_jet0Y                   ;  
  // TH1D * h3_rebin_Effic_chstag_tau32_nvtxg                   ;  
  // TH1D * h3_rebin_Effic_chstag_tau32_jet0P_TopMatch          ;  
  // TH1D * h3_rebin_Effic_chstag_tau32_jet0P_TopMatch_TopDist  ;  
  // TH1D * h3_rebin_Effic_puptag_mass_pup0P                    ;  
  // TH1D * h3_rebin_Effic_puptag_mass_jet0P                    ;  
  // TH1D * h3_rebin_Effic_puptag_mass_jet0Y                    ;  
  // TH1D * h3_rebin_Effic_puptag_mass_nvtxg                    ;  
  // TH1D * h3_rebin_Effic_puptag_mass_jet0P_TopMatch           ;  
  // TH1D * h3_rebin_Effic_puptag_mass_jet0P_TopMatch_TopDist   ;  
  // TH1D * h3_rebin_Effic_chstag_mass_pup0P                    ;  
  // TH1D * h3_rebin_Effic_chstag_mass_jet0P                    ;  
  // TH1D * h3_rebin_Effic_chstag_mass_jet0Y                    ;  
  // TH1D * h3_rebin_Effic_chstag_mass_nvtxg                    ;  
  // TH1D * h3_rebin_Effic_chstag_mass_jet0P_TopMatch           ;  
  // TH1D * h3_rebin_Effic_chstag_mass_jet0P_TopMatch_TopDist   ;  
  // TH1D * h3_rebin_Effic_puptag_t_pup0P                       ;  
  // TH1D * h3_rebin_Effic_puptag_t_jet0P                       ;  
  // TH1D * h3_rebin_Effic_puptag_t_jet0Y                       ;  
  // TH1D * h3_rebin_Effic_puptag_t_nvtxg                       ;  
  // TH1D * h3_rebin_Effic_puptag_t_jet0P_TopMatch              ;  
  // TH1D * h3_rebin_Effic_puptag_t_jet0P_TopMatch_TopDist      ;  
  // TH1D * h3_rebin_Effic_chstag_t_pup0P                       ;  
  // TH1D * h3_rebin_Effic_chstag_t_jet0P                       ;  
  // TH1D * h3_rebin_Effic_chstag_t_jet0Y                       ;  
  // TH1D * h3_rebin_Effic_chstag_t_nvtxg                       ;  
  // TH1D * h3_rebin_Effic_chstag_t_jet0P_TopMatch              ;  
  // TH1D * h3_rebin_Effic_chstag_t_jet0P_TopMatch_TopDist      ;  



  // h3_rebin_Effic_Denom_nvtxg         = (TH1D*)h3_new_Effic_Denom_nvtxg           ->Rebin(nbins_nvtx-1,"h3_rebin_Effic_Denom_nvtxg"       ,xbins_nvtx);
  // h3_rebin_Effic_puptag_tau32_nvtxg  = (TH1D*)h3_new_Effic_puptag_tau32_nvtxg    ->Rebin(nbins_nvtx-1,"h3_rebin_Effic_puptag_tau32_nvtxg",xbins_nvtx);
  // h3_rebin_Effic_chstag_tau32_nvtxg  = (TH1D*)h3_new_Effic_chstag_tau32_nvtxg    ->Rebin(nbins_nvtx-1,"h3_rebin_Effic_chstag_tau32_nvtxg",xbins_nvtx);
  // h3_rebin_Effic_puptag_mass_nvtxg   = (TH1D*)h3_new_Effic_puptag_mass_nvtxg     ->Rebin(nbins_nvtx-1,"h3_rebin_Effic_puptag_mass_nvtxg" ,xbins_nvtx);
  // h3_rebin_Effic_chstag_mass_nvtxg   = (TH1D*)h3_new_Effic_chstag_mass_nvtxg     ->Rebin(nbins_nvtx-1,"h3_rebin_Effic_chstag_mass_nvtxg" ,xbins_nvtx);
  // h3_rebin_Effic_puptag_t_nvtxg      = (TH1D*)h3_new_Effic_puptag_t_nvtxg        ->Rebin(nbins_nvtx-1,"h3_rebin_Effic_puptag_t_nvtxg"    ,xbins_nvtx);
  // h3_rebin_Effic_chstag_t_nvtxg      = (TH1D*)h3_new_Effic_chstag_t_nvtxg        ->Rebin(nbins_nvtx-1,"h3_rebin_Effic_chstag_t_nvtxg"    ,xbins_nvtx);

  // h3_Effic_Denom_pup0P                          ->Rebin(10);
  // h3_Effic_Denom_jet0P                          ->Rebin(10);
  // h3_Effic_Denom_jet0Y                          ->Rebin(10);
  // h3_Effic_Denom_jet0P_TopMatch                 ->Rebin(10);
  // h3_Effic_Denom_jet0P_TopMatch_TopDist         ->Rebin(10);
  // h3_Effic_puptag_tau32_pup0P                   ->Rebin(10);
  // h3_Effic_puptag_tau32_jet0P                   ->Rebin(10);
  // h3_Effic_puptag_tau32_jet0Y                   ->Rebin(10);
  // h3_Effic_puptag_tau32_jet0P_TopMatch          ->Rebin(10);
  // h3_Effic_puptag_tau32_jet0P_TopMatch_TopDist  ->Rebin(10);
  // h3_Effic_chstag_tau32_pup0P                   ->Rebin(10);
  // h3_Effic_chstag_tau32_jet0P                   ->Rebin(10);
  // h3_Effic_chstag_tau32_jet0Y                   ->Rebin(10);
  // h3_Effic_chstag_tau32_jet0P_TopMatch          ->Rebin(10);
  // h3_Effic_chstag_tau32_jet0P_TopMatch_TopDist  ->Rebin(10);
  // h3_Effic_puptag_mass_pup0P                    ->Rebin(10);
  // h3_Effic_puptag_mass_jet0P                    ->Rebin(10);
  // h3_Effic_puptag_mass_jet0Y                    ->Rebin(10);
  // h3_Effic_puptag_mass_jet0P_TopMatch           ->Rebin(10);
  // h3_Effic_puptag_mass_jet0P_TopMatch_TopDist   ->Rebin(10);
  // h3_Effic_chstag_mass_pup0P                    ->Rebin(10);
  // h3_Effic_chstag_mass_jet0P                    ->Rebin(10);
  // h3_Effic_chstag_mass_jet0Y                    ->Rebin(10);
  // h3_Effic_chstag_mass_jet0P_TopMatch           ->Rebin(10);
  // h3_Effic_chstag_mass_jet0P_TopMatch_TopDist   ->Rebin(10);
  // h3_Effic_puptag_t_pup0P                       ->Rebin(10);
  // h3_Effic_puptag_t_jet0P                       ->Rebin(10);
  // h3_Effic_puptag_t_jet0Y                       ->Rebin(10);
  // h3_Effic_puptag_t_jet0P_TopMatch              ->Rebin(10);
  // h3_Effic_puptag_t_jet0P_TopMatch_TopDist      ->Rebin(10);
  // h3_Effic_chstag_t_pup0P                       ->Rebin(10);
  // h3_Effic_chstag_t_jet0P                       ->Rebin(10);
  // h3_Effic_chstag_t_jet0Y                       ->Rebin(10);
  // h3_Effic_chstag_t_jet0P_TopMatch              ->Rebin(10);
  // h3_Effic_chstag_t_jet0P_TopMatch_TopDist      ->Rebin(10);


  // TH1D *effic_tau32_pup0P =(TH1D*) h3_Effic_puptag_tau32_pup0P->Clone();
  // // effic_tau32_pup0P->Reset();
  // effic_tau32_pup0P->Divide( h3_Effic_puptag_tau32_pup0P, h3_Effic_Denom_pup0P,1,1,"B");

  // TH1D *effic_tau32_jet0P =(TH1D*) h3_Effic_puptag_tau32_jet0P->Clone();
  // // effic_tau32_jet0P->Reset();
  // effic_tau32_jet0P->Divide( h3_Effic_puptag_tau32_jet0P, h3_Effic_Denom_jet0P,1,1,"B");

  // TH1D *effic_chstag_tau32_jet0P =(TH1D*) h3_Effic_chstag_tau32_jet0P->Clone();
  // // effic_chstag_tau32_jet0P->Reset();
  // effic_chstag_tau32_jet0P->Divide( h3_Effic_chstag_tau32_jet0P, h3_Effic_Denom_jet0P,1,1,"B");


  // TH1D *effic_mass_jet0P =(TH1D*) h3_Effic_puptag_mass_jet0P->Clone();
  // // effic_mass_jet0P->Reset();
  // effic_mass_jet0P->Divide( h3_Effic_puptag_mass_jet0P, h3_Effic_Denom_jet0P,1,1,"B");

  // TH1D *effic_t_jet0P =(TH1D*) h3_Effic_puptag_t_jet0P->Clone();
  // // effic_t_jet0P->Reset();
  // effic_t_jet0P->Divide( h3_Effic_puptag_t_jet0P, h3_Effic_Denom_jet0P,1,1,"B");

  // effic_tau32_pup0P ->SetLineColor(2);    
  // effic_tau32_jet0P ->SetLineColor(3);        
  // effic_mass_jet0P  ->SetLineColor(4);       
  // effic_t_jet0P     ->SetLineColor(5);
  // effic_chstag_tau32_jet0P->SetLineColor(6);

  // effic_tau32_pup0P->GetXaxis()->SetRangeUser(300,4000);
  // effic_tau32_pup0P ->Draw("HIST");          
  // effic_tau32_jet0P ->Draw("HISTsame");
  // effic_chstag_tau32_jet0P  ->Draw("HISTsame");         
  // effic_mass_jet0P  ->Draw("HISTsame");         
  // effic_t_jet0P     ->Draw("HISTsame");      
  // c1237->SaveAs("./plotsEfficTest/effic_tau32_pup0P.pdf");

  // cout<<"h3_Effic_puptag_tau32_jet0P_TopMatch "<<h3_Effic_puptag_tau32_jet0P_TopMatch->Integral()<<endl;
  // cout<<"h3_Effic_Denom_jet0P_TopMatch "<<h3_Effic_Denom_jet0P_TopMatch->Integral()<<endl;

  // cout<<"h3_Effic_puptag_tau32_jet0P_TopMatch_TopDist "<<h3_Effic_puptag_tau32_jet0P_TopMatch_TopDist->Integral()<<endl;
  // cout<<"h3_Effic_Denom_jet0P_TopMatch_TopDist "<<h3_Effic_Denom_jet0P_TopMatch_TopDist->Integral()<<endl;


  // TH1D *effic_puptag_tau32_jet0P_TopMatch =(TH1D*) h3_Effic_puptag_tau32_jet0P_TopMatch->Clone();
  // effic_puptag_tau32_jet0P_TopMatch->Reset();
  // effic_puptag_tau32_jet0P_TopMatch->Divide( h3_Effic_puptag_tau32_jet0P_TopMatch, h3_Effic_Denom_jet0P_TopMatch,1,1,"B");

  // TH1D *effic_puptag_tau32_jet0P_TopMatch_TopDist =(TH1D*) h3_Effic_puptag_tau32_jet0P_TopMatch_TopDist->Clone();
  // effic_puptag_tau32_jet0P_TopMatch_TopDist->Reset();
  // effic_puptag_tau32_jet0P_TopMatch_TopDist->Divide( h3_Effic_puptag_tau32_jet0P_TopMatch_TopDist, h3_Effic_Denom_jet0P_TopMatch_TopDist,1,1,"B");

  // effic_puptag_tau32_jet0P_TopMatch         ->SetLineColor(1);
  // effic_puptag_tau32_jet0P_TopMatch_TopDist->SetLineColor(2);

  // effic_puptag_tau32_jet0P_TopMatch_TopDist->GetXaxis()->SetRangeUser(300,4000);
  // effic_puptag_tau32_jet0P_TopMatch_TopDist ->Draw("HIST");          
  // effic_puptag_tau32_jet0P_TopMatch ->Draw("HISTsame");    
  // c1237->SaveAs("./plotsEfficTest/effic_match.pdf");





  // TH1D *h3_effic_puptag_tau32_nvtxg =(TH1D*) h3_rebin_Effic_puptag_tau32_nvtxg->Clone();
  // // h3_effic_puptag_tau32_nvtxg->Reset();
  // h3_effic_puptag_tau32_nvtxg->Divide( h3_rebin_Effic_puptag_tau32_nvtxg, h3_rebin_Effic_Denom_nvtxg,1,1,"B");

  // TH1D *h3_effic_puptag_mass_nvtxg =(TH1D*) h3_rebin_Effic_puptag_mass_nvtxg->Clone();
  // // h3_effic_puptag_mass_nvtxg->Reset();
  // h3_effic_puptag_mass_nvtxg->Divide( h3_rebin_Effic_puptag_mass_nvtxg, h3_rebin_Effic_Denom_nvtxg,1,1,"B");

  // TH1D *h3_effic_puptag_t_nvtxg =(TH1D*) h3_rebin_Effic_puptag_t_nvtxg->Clone();
  // // h3_effic_puptag_t_nvtxg->Reset();
  // h3_effic_puptag_t_nvtxg->Divide( h3_rebin_Effic_puptag_t_nvtxg, h3_rebin_Effic_Denom_nvtxg,1,1,"B");


  // TH1D *h3_effic_chstag_tau32_nvtxg =(TH1D*) h3_rebin_Effic_chstag_tau32_nvtxg->Clone();
  // // h3_effic_chstag_tau32_nvtxg->Reset();
  // h3_effic_chstag_tau32_nvtxg->Divide( h3_rebin_Effic_chstag_tau32_nvtxg, h3_rebin_Effic_Denom_nvtxg,1,1,"B");

  // TH1D *h3_effic_chstag_mass_nvtxg =(TH1D*) h3_rebin_Effic_chstag_mass_nvtxg->Clone();
  // // h3_effic_chstag_mass_nvtxg->Reset();
  // h3_effic_chstag_mass_nvtxg->Divide( h3_rebin_Effic_chstag_mass_nvtxg, h3_rebin_Effic_Denom_nvtxg,1,1,"B");

  // TH1D *h3_effic_chstag_t_nvtxg =(TH1D*) h3_rebin_Effic_chstag_t_nvtxg->Clone();
  // // h3_effic_chstag_t_nvtxg->Reset();
  // h3_effic_chstag_t_nvtxg->Divide( h3_rebin_Effic_chstag_t_nvtxg, h3_rebin_Effic_Denom_nvtxg,1,1,"B");

  // h3_effic_puptag_tau32_nvtxg ->SetMarkerStyle(20);        
  // h3_effic_puptag_mass_nvtxg  ->SetMarkerStyle(21);       
  // h3_effic_puptag_t_nvtxg     ->SetMarkerStyle(22);

  // h3_effic_chstag_tau32_nvtxg ->SetMarkerStyle(24);        
  // h3_effic_chstag_mass_nvtxg  ->SetMarkerStyle(25);       
  // h3_effic_chstag_t_nvtxg     ->SetMarkerStyle(26);

  // h3_effic_puptag_tau32_nvtxg ->SetMarkerColor(6);              
  // h3_effic_puptag_mass_nvtxg  ->SetMarkerColor(kBlue);         
  // h3_effic_puptag_t_nvtxg     ->SetMarkerColor(kOrange+1);

  // h3_effic_chstag_tau32_nvtxg ->SetMarkerColor(6);        
  // h3_effic_chstag_mass_nvtxg  ->SetMarkerColor(kBlue);       
  // h3_effic_chstag_t_nvtxg     ->SetMarkerColor(kOrange+1);

  // h3_effic_puptag_tau32_nvtxg ->SetLineColor(6);           
  // h3_effic_puptag_mass_nvtxg  ->SetLineColor(kBlue);      
  // h3_effic_puptag_t_nvtxg     ->SetLineColor(kOrange+1);

  // h3_effic_chstag_tau32_nvtxg ->SetLineColor(6);           
  // h3_effic_chstag_mass_nvtxg  ->SetLineColor(kBlue);      
  // h3_effic_chstag_t_nvtxg     ->SetLineColor(kOrange+1);

  // h3_effic_puptag_tau32_nvtxg ->SetLineWidth(2);   
  // h3_effic_puptag_mass_nvtxg  ->SetLineWidth(2);  
  // h3_effic_puptag_t_nvtxg     ->SetLineWidth(2);

  // h3_effic_chstag_tau32_nvtxg ->SetLineWidth(2);   
  // h3_effic_chstag_mass_nvtxg  ->SetLineWidth(2);  
  // h3_effic_chstag_t_nvtxg     ->SetLineWidth(2);




  //   h3_effic_puptag_tau32_nvtxg->SetTitle(title.c_str());

  //   h3_effic_puptag_tau32_nvtxg->SetStats(0);


  //   h3_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleSize(0.065);
  //   h3_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleOffset(0.9); 
  //   h3_effic_puptag_tau32_nvtxg->GetYaxis()->SetLabelSize(0.06);

  //   h3_effic_puptag_tau32_nvtxg->GetXaxis()->SetNdivisions(506);
  //   h3_effic_puptag_tau32_nvtxg->GetXaxis()->SetLabelFont(42);
  //   h3_effic_puptag_tau32_nvtxg->GetXaxis()->SetLabelSize(0.05);
  //   h3_effic_puptag_tau32_nvtxg->GetXaxis()->SetTitleSize(0.056);
  //   h3_effic_puptag_tau32_nvtxg->GetXaxis()->SetTickLength(0.045);
  //   h3_effic_puptag_tau32_nvtxg->GetXaxis()->SetTitleOffset(1.15);
  //   h3_effic_puptag_tau32_nvtxg->GetXaxis()->SetTitleFont(42);

  //   h3_effic_puptag_tau32_nvtxg->GetYaxis()->SetNdivisions(506);
  //   h3_effic_puptag_tau32_nvtxg->GetYaxis()->SetLabelFont(42);
  //   h3_effic_puptag_tau32_nvtxg->GetYaxis()->SetLabelSize(0.05);
  //   h3_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleSize(0.06125);
  //   h3_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleOffset(1.17);
  //   h3_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleFont(42);

  //   h3_effic_puptag_tau32_nvtxg->GetZaxis()->SetLabelFont(42);
  //   h3_effic_puptag_tau32_nvtxg->GetZaxis()->SetLabelSize(0.0425);
  //   h3_effic_puptag_tau32_nvtxg->GetZaxis()->SetTitleSize(0.0475);
  //   h3_effic_puptag_tau32_nvtxg->GetZaxis()->SetTitleFont(42);

  // h3_effic_puptag_tau32_nvtxg->GetYaxis()->SetRangeUser(0.0,1.1);
  // h3_effic_puptag_tau32_nvtxg ->Draw("");
  // h3_effic_puptag_mass_nvtxg  ->Draw("same");         
  // h3_effic_puptag_t_nvtxg     ->Draw("same");      

  // h3_effic_chstag_tau32_nvtxg ->Draw("same");
  // h3_effic_chstag_mass_nvtxg  ->Draw("same");         
  // h3_effic_chstag_t_nvtxg     ->Draw("same");      





  //   TLegend * h3_leg;
  //   h3_leg = new TLegend( 0.58, 0.6,0.95, 0.88);  //( 0.56, 0.69,0.98, 0.89);
  //   h3_leg->SetBorderSize(0);
  //   h3_leg->SetFillColor(0);
  //   h3_leg->SetFillStyle(4000);
  //   h3_leg->SetTextSize(0.04);   //0.038
  //   h3_leg->SetMargin(0.18 );
  //   h3_leg->SetHeader("Tight t-tag");
  //   h3_leg->AddEntry( h3_effic_chstag_mass_nvtxg    , "CHS: m_{SD} tag"            , "LP" );
  //   h3_leg->AddEntry( h3_effic_chstag_tau32_nvtxg   , "CHS: #tau_{32} tag"         , "LP" );
  //   h3_leg->AddEntry( h3_effic_chstag_t_nvtxg       , "CHS: m_{SD}+#tau_{32} tag"  , "LP" );
  
  //   h3_leg->AddEntry( h3_effic_puptag_mass_nvtxg    , "PUPPI: m_{SD} tag"                     , "LP" );
  //   h3_leg->AddEntry( h3_effic_puptag_tau32_nvtxg   , "PUPPI: #tau_{32} tag"                  , "LP" );
  //   h3_leg->AddEntry( h3_effic_puptag_t_nvtxg       , "PUPPI: m_{SD}+#tau_{32} tag"           , "LP" );
  //   h3_leg->Draw("same");

  //   TLatex *   h3_tex = new TLatex(0.18,0.83,"#font[62]{CMS}");// #font[52]{Simulation Preliminary}");
  //   h3_tex->SetNDC();
  //   h3_tex->SetTextFont(42);
  //   h3_tex->SetTextSize(0.0555); //0.0625
  //   h3_tex->SetLineWidth(2);
  //   h3_tex->Draw();
  //   h3_tex = new TLatex(0.18,0.77,"#font[52]{Simulation Preliminary}");
  //   h3_tex->SetNDC();
  //   h3_tex->SetTextFont(42);
  //   h3_tex->SetTextSize(0.05); //0.0625
  //   h3_tex->SetLineWidth(2);
  //   h3_tex->Draw();
  //   h3_tex = new TLatex(0.96,0.936,"36 fb^{-1} (13 TeV)");
  //   h3_tex->SetNDC();
  //   h3_tex->SetTextAlign(31);
  //   h3_tex->SetTextFont(42);
  //   h3_tex->SetTextSize(0.0575);
  //   h3_tex->SetLineWidth(2);
  //   // tex->Draw();
  

  //   c1237->SaveAs("./plotEfficTest_WPABC/h3_effic_tau32_nvtxg_WPC.pdf");

  //----------------------------------






























  TH1D *    h1w_Effic_Denom_pup0P                           = (TH1D *) fTop1w->Get( "h_Effic_Denom_pup0P"                            );
  TH1D *    h1w_Effic_Denom_jet0P                           = (TH1D *) fTop1w->Get( "h_Effic_Denom_jet0P"                            );
  TH1D *    h1w_Effic_Denom_jet0Y                           = (TH1D *) fTop1w->Get( "h_Effic_Denom_jet0Y"                            );
  TH1D *    h1w_Effic_Denom_nvtxg                           = (TH1D *) fTop1w->Get( "h_Effic_Denom_nvtxg"                            );
  TH1D *    h1w_Effic_Denom_jet0P_TopMatch                  = (TH1D *) fTop1w->Get( "h_Effic_Denom_jet0P_TopMatch"                   );
  TH1D *    h1w_Effic_Denom_jet0P_TopMatch_TopDist          = (TH1D *) fTop1w->Get( "h_Effic_Denom_jet0P_TopMatch_TopDist"           );
  TH1D *    h1w_Effic_puptag_tau32_pup0P                    = (TH1D *) fTop1w->Get( "h_Effic_puptag_tau32_pup0P"                     );
  TH1D *    h1w_Effic_puptag_tau32_jet0P                    = (TH1D *) fTop1w->Get( "h_Effic_puptag_tau32_jet0P"                     );
  TH1D *    h1w_Effic_puptag_tau32_jet0Y                    = (TH1D *) fTop1w->Get( "h_Effic_puptag_tau32_jet0Y"                     );
  TH1D *    h1w_Effic_puptag_tau32_nvtxg                    = (TH1D *) fTop1w->Get( "h_Effic_puptag_tau32_nvtxg"                     );
  TH1D *    h1w_Effic_puptag_tau32_jet0P_TopMatch           = (TH1D *) fTop1w->Get( "h_Effic_puptag_tau32_jet0P_TopMatch"            );
  TH1D *    h1w_Effic_puptag_tau32_jet0P_TopMatch_TopDist   = (TH1D *) fTop1w->Get( "h_Effic_puptag_tau32_jet0P_TopMatch_TopDist"    );
  TH1D *    h1w_Effic_chstag_tau32_pup0P                    = (TH1D *) fTop1w->Get( "h_Effic_chstag_tau32_pup0P"                     );
  TH1D *    h1w_Effic_chstag_tau32_jet0P                    = (TH1D *) fTop1w->Get( "h_Effic_chstag_tau32_jet0P"                     );
  TH1D *    h1w_Effic_chstag_tau32_jet0Y                    = (TH1D *) fTop1w->Get( "h_Effic_chstag_tau32_jet0Y"                     );
  TH1D *    h1w_Effic_chstag_tau32_nvtxg                    = (TH1D *) fTop1w->Get( "h_Effic_chstag_tau32_nvtxg"                     );
  TH1D *    h1w_Effic_chstag_tau32_jet0P_TopMatch           = (TH1D *) fTop1w->Get( "h_Effic_chstag_tau32_jet0P_TopMatch"            );
  TH1D *    h1w_Effic_chstag_tau32_jet0P_TopMatch_TopDist   = (TH1D *) fTop1w->Get( "h_Effic_chstag_tau32_jet0P_TopMatch_TopDist"    );
  TH1D *    h1w_Effic_puptag_mass_pup0P                     = (TH1D *) fTop1w->Get( "h_Effic_puptag_mass_pup0P"                      );
  TH1D *    h1w_Effic_puptag_mass_jet0P                     = (TH1D *) fTop1w->Get( "h_Effic_puptag_mass_jet0P"                      );
  TH1D *    h1w_Effic_puptag_mass_jet0Y                     = (TH1D *) fTop1w->Get( "h_Effic_puptag_mass_jet0Y"                      );
  TH1D *    h1w_Effic_puptag_mass_nvtxg                     = (TH1D *) fTop1w->Get( "h_Effic_puptag_mass_nvtxg"                      );
  TH1D *    h1w_Effic_puptag_mass_jet0P_TopMatch            = (TH1D *) fTop1w->Get( "h_Effic_puptag_mass_jet0P_TopMatch"             );
  TH1D *    h1w_Effic_puptag_mass_jet0P_TopMatch_TopDist    = (TH1D *) fTop1w->Get( "h_Effic_puptag_mass_jet0P_TopMatch_TopDist"     );
  TH1D *    h1w_Effic_chstag_mass_pup0P                     = (TH1D *) fTop1w->Get( "h_Effic_chstag_mass_pup0P"                      );
  TH1D *    h1w_Effic_chstag_mass_jet0P                     = (TH1D *) fTop1w->Get( "h_Effic_chstag_mass_jet0P"                      );
  TH1D *    h1w_Effic_chstag_mass_jet0Y                     = (TH1D *) fTop1w->Get( "h_Effic_chstag_mass_jet0Y"                      );
  TH1D *    h1w_Effic_chstag_mass_nvtxg                     = (TH1D *) fTop1w->Get( "h_Effic_chstag_mass_nvtxg"                      );
  TH1D *    h1w_Effic_chstag_mass_jet0P_TopMatch            = (TH1D *) fTop1w->Get( "h_Effic_chstag_mass_jet0P_TopMatch"             );
  TH1D *    h1w_Effic_chstag_mass_jet0P_TopMatch_TopDist    = (TH1D *) fTop1w->Get( "h_Effic_chstag_mass_jet0P_TopMatch_TopDist"     );
  TH1D *    h1w_Effic_puptag_t_pup0P                        = (TH1D *) fTop1w->Get( "h_Effic_puptag_t_pup0P"                         );
  TH1D *    h1w_Effic_puptag_t_jet0P                        = (TH1D *) fTop1w->Get( "h_Effic_puptag_t_jet0P"                         );
  TH1D *    h1w_Effic_puptag_t_jet0Y                        = (TH1D *) fTop1w->Get( "h_Effic_puptag_t_jet0Y"                         );
  TH1D *    h1w_Effic_puptag_t_nvtxg                        = (TH1D *) fTop1w->Get( "h_Effic_puptag_t_nvtxg"                         );
  TH1D *    h1w_Effic_puptag_t_jet0P_TopMatch               = (TH1D *) fTop1w->Get( "h_Effic_puptag_t_jet0P_TopMatch"                );
  TH1D *    h1w_Effic_puptag_t_jet0P_TopMatch_TopDist       = (TH1D *) fTop1w->Get( "h_Effic_puptag_t_jet0P_TopMatch_TopDist"        );
  TH1D *    h1w_Effic_chstag_t_pup0P                        = (TH1D *) fTop1w->Get( "h_Effic_chstag_t_pup0P"                         );
  TH1D *    h1w_Effic_chstag_t_jet0P                        = (TH1D *) fTop1w->Get( "h_Effic_chstag_t_jet0P"                         );
  TH1D *    h1w_Effic_chstag_t_jet0Y                        = (TH1D *) fTop1w->Get( "h_Effic_chstag_t_jet0Y"                         );
  TH1D *    h1w_Effic_chstag_t_nvtxg                        = (TH1D *) fTop1w->Get( "h_Effic_chstag_t_nvtxg"                         );
  TH1D *    h1w_Effic_chstag_t_jet0P_TopMatch               = (TH1D *) fTop1w->Get( "h_Effic_chstag_t_jet0P_TopMatch"                );
  TH1D *    h1w_Effic_chstag_t_jet0P_TopMatch_TopDist       = (TH1D *) fTop1w->Get( "h_Effic_chstag_t_jet0P_TopMatch_TopDist"        );




  TH1D *    h1w_new_Effic_Denom_pup0P                         = (TH1D*) h1w_Effic_Denom_pup0P                            ->Clone();  
  TH1D *    h1w_new_Effic_Denom_jet0P                         = (TH1D*) h1w_Effic_Denom_jet0P                            ->Clone();  
  TH1D *    h1w_new_Effic_Denom_jet0Y                         = (TH1D*) h1w_Effic_Denom_jet0Y                            ->Clone();  
  TH1D *    h1w_new_Effic_Denom_nvtxg                         = (TH1D*) h1w_Effic_Denom_nvtxg                            ->Clone();  
  TH1D *    h1w_new_Effic_Denom_jet0P_TopMatch                = (TH1D*) h1w_Effic_Denom_jet0P_TopMatch                   ->Clone();  
  TH1D *    h1w_new_Effic_Denom_jet0P_TopMatch_TopDist        = (TH1D*) h1w_Effic_Denom_jet0P_TopMatch_TopDist           ->Clone();  
  TH1D *    h1w_new_Effic_puptag_tau32_pup0P                  = (TH1D*) h1w_Effic_puptag_tau32_pup0P                     ->Clone();  
  TH1D *    h1w_new_Effic_puptag_tau32_jet0P                  = (TH1D*) h1w_Effic_puptag_tau32_jet0P                     ->Clone();  
  TH1D *    h1w_new_Effic_puptag_tau32_jet0Y                  = (TH1D*) h1w_Effic_puptag_tau32_jet0Y                     ->Clone();  
  TH1D *    h1w_new_Effic_puptag_tau32_nvtxg                  = (TH1D*) h1w_Effic_puptag_tau32_nvtxg                     ->Clone();  
  TH1D *    h1w_new_Effic_puptag_tau32_jet0P_TopMatch         = (TH1D*) h1w_Effic_puptag_tau32_jet0P_TopMatch            ->Clone();  
  TH1D *    h1w_new_Effic_puptag_tau32_jet0P_TopMatch_TopDist = (TH1D*) h1w_Effic_puptag_tau32_jet0P_TopMatch_TopDist    ->Clone();  
  TH1D *    h1w_new_Effic_chstag_tau32_pup0P                  = (TH1D*) h1w_Effic_chstag_tau32_pup0P                     ->Clone();  
  TH1D *    h1w_new_Effic_chstag_tau32_jet0P                  = (TH1D*) h1w_Effic_chstag_tau32_jet0P                     ->Clone();  
  TH1D *    h1w_new_Effic_chstag_tau32_jet0Y                  = (TH1D*) h1w_Effic_chstag_tau32_jet0Y                     ->Clone();  
  TH1D *    h1w_new_Effic_chstag_tau32_nvtxg                  = (TH1D*) h1w_Effic_chstag_tau32_nvtxg                     ->Clone();  
  TH1D *    h1w_new_Effic_chstag_tau32_jet0P_TopMatch         = (TH1D*) h1w_Effic_chstag_tau32_jet0P_TopMatch            ->Clone();  
  TH1D *    h1w_new_Effic_chstag_tau32_jet0P_TopMatch_TopDist = (TH1D*) h1w_Effic_chstag_tau32_jet0P_TopMatch_TopDist    ->Clone();  
  TH1D *    h1w_new_Effic_puptag_mass_pup0P                   = (TH1D*) h1w_Effic_puptag_mass_pup0P                      ->Clone();  
  TH1D *    h1w_new_Effic_puptag_mass_jet0P                   = (TH1D*) h1w_Effic_puptag_mass_jet0P                      ->Clone();  
  TH1D *    h1w_new_Effic_puptag_mass_jet0Y                   = (TH1D*) h1w_Effic_puptag_mass_jet0Y                      ->Clone();  
  TH1D *    h1w_new_Effic_puptag_mass_nvtxg                   = (TH1D*) h1w_Effic_puptag_mass_nvtxg                      ->Clone();  
  TH1D *    h1w_new_Effic_puptag_mass_jet0P_TopMatch          = (TH1D*) h1w_Effic_puptag_mass_jet0P_TopMatch             ->Clone();  
  TH1D *    h1w_new_Effic_puptag_mass_jet0P_TopMatch_TopDist  = (TH1D*) h1w_Effic_puptag_mass_jet0P_TopMatch_TopDist     ->Clone();  
  TH1D *    h1w_new_Effic_chstag_mass_pup0P                   = (TH1D*) h1w_Effic_chstag_mass_pup0P                      ->Clone();  
  TH1D *    h1w_new_Effic_chstag_mass_jet0P                   = (TH1D*) h1w_Effic_chstag_mass_jet0P                      ->Clone();  
  TH1D *    h1w_new_Effic_chstag_mass_jet0Y                   = (TH1D*) h1w_Effic_chstag_mass_jet0Y                      ->Clone();  
  TH1D *    h1w_new_Effic_chstag_mass_nvtxg                   = (TH1D*) h1w_Effic_chstag_mass_nvtxg                      ->Clone();  
  TH1D *    h1w_new_Effic_chstag_mass_jet0P_TopMatch          = (TH1D*) h1w_Effic_chstag_mass_jet0P_TopMatch             ->Clone();  
  TH1D *    h1w_new_Effic_chstag_mass_jet0P_TopMatch_TopDist  = (TH1D*) h1w_Effic_chstag_mass_jet0P_TopMatch_TopDist     ->Clone();  
  TH1D *    h1w_new_Effic_puptag_t_pup0P                      = (TH1D*) h1w_Effic_puptag_t_pup0P                         ->Clone();  
  TH1D *    h1w_new_Effic_puptag_t_jet0P                      = (TH1D*) h1w_Effic_puptag_t_jet0P                         ->Clone();  
  TH1D *    h1w_new_Effic_puptag_t_jet0Y                      = (TH1D*) h1w_Effic_puptag_t_jet0Y                         ->Clone();  
  TH1D *    h1w_new_Effic_puptag_t_nvtxg                      = (TH1D*) h1w_Effic_puptag_t_nvtxg                         ->Clone();  
  TH1D *    h1w_new_Effic_puptag_t_jet0P_TopMatch             = (TH1D*) h1w_Effic_puptag_t_jet0P_TopMatch                ->Clone();  
  TH1D *    h1w_new_Effic_puptag_t_jet0P_TopMatch_TopDist     = (TH1D*) h1w_Effic_puptag_t_jet0P_TopMatch_TopDist        ->Clone();  
  TH1D *    h1w_new_Effic_chstag_t_pup0P                      = (TH1D*) h1w_Effic_chstag_t_pup0P                         ->Clone();  
  TH1D *    h1w_new_Effic_chstag_t_jet0P                      = (TH1D*) h1w_Effic_chstag_t_jet0P                         ->Clone();  
  TH1D *    h1w_new_Effic_chstag_t_jet0Y                      = (TH1D*) h1w_Effic_chstag_t_jet0Y                         ->Clone();  
  TH1D *    h1w_new_Effic_chstag_t_nvtxg                      = (TH1D*) h1w_Effic_chstag_t_nvtxg                         ->Clone();  
  TH1D *    h1w_new_Effic_chstag_t_jet0P_TopMatch             = (TH1D*) h1w_Effic_chstag_t_jet0P_TopMatch                ->Clone();  
  TH1D *    h1w_new_Effic_chstag_t_jet0P_TopMatch_TopDist     = (TH1D*) h1w_Effic_chstag_t_jet0P_TopMatch_TopDist        ->Clone();  


  TH1D * h1w_rebin_Effic_Denom_pup0P                          ;  
  TH1D * h1w_rebin_Effic_Denom_jet0P                          ;  
  TH1D * h1w_rebin_Effic_Denom_jet0Y                          ;  
  TH1D * h1w_rebin_Effic_Denom_nvtxg                          ;  
  TH1D * h1w_rebin_Effic_Denom_jet0P_TopMatch                 ;  
  TH1D * h1w_rebin_Effic_Denom_jet0P_TopMatch_TopDist         ;  
  TH1D * h1w_rebin_Effic_puptag_tau32_pup0P                   ;  
  TH1D * h1w_rebin_Effic_puptag_tau32_jet0P                   ;  
  TH1D * h1w_rebin_Effic_puptag_tau32_jet0Y                   ;  
  TH1D * h1w_rebin_Effic_puptag_tau32_nvtxg                   ;  
  TH1D * h1w_rebin_Effic_puptag_tau32_jet0P_TopMatch          ;  
  TH1D * h1w_rebin_Effic_puptag_tau32_jet0P_TopMatch_TopDist  ;  
  TH1D * h1w_rebin_Effic_chstag_tau32_pup0P                   ;  
  TH1D * h1w_rebin_Effic_chstag_tau32_jet0P                   ;  
  TH1D * h1w_rebin_Effic_chstag_tau32_jet0Y                   ;  
  TH1D * h1w_rebin_Effic_chstag_tau32_nvtxg                   ;  
  TH1D * h1w_rebin_Effic_chstag_tau32_jet0P_TopMatch          ;  
  TH1D * h1w_rebin_Effic_chstag_tau32_jet0P_TopMatch_TopDist  ;  
  TH1D * h1w_rebin_Effic_puptag_mass_pup0P                    ;  
  TH1D * h1w_rebin_Effic_puptag_mass_jet0P                    ;  
  TH1D * h1w_rebin_Effic_puptag_mass_jet0Y                    ;  
  TH1D * h1w_rebin_Effic_puptag_mass_nvtxg                    ;  
  TH1D * h1w_rebin_Effic_puptag_mass_jet0P_TopMatch           ;  
  TH1D * h1w_rebin_Effic_puptag_mass_jet0P_TopMatch_TopDist   ;  
  TH1D * h1w_rebin_Effic_chstag_mass_pup0P                    ;  
  TH1D * h1w_rebin_Effic_chstag_mass_jet0P                    ;  
  TH1D * h1w_rebin_Effic_chstag_mass_jet0Y                    ;  
  TH1D * h1w_rebin_Effic_chstag_mass_nvtxg                    ;  
  TH1D * h1w_rebin_Effic_chstag_mass_jet0P_TopMatch           ;  
  TH1D * h1w_rebin_Effic_chstag_mass_jet0P_TopMatch_TopDist   ;  
  TH1D * h1w_rebin_Effic_puptag_t_pup0P                       ;  
  TH1D * h1w_rebin_Effic_puptag_t_jet0P                       ;  
  TH1D * h1w_rebin_Effic_puptag_t_jet0Y                       ;  
  TH1D * h1w_rebin_Effic_puptag_t_nvtxg                       ;  
  TH1D * h1w_rebin_Effic_puptag_t_jet0P_TopMatch              ;  
  TH1D * h1w_rebin_Effic_puptag_t_jet0P_TopMatch_TopDist      ;  
  TH1D * h1w_rebin_Effic_chstag_t_pup0P                       ;  
  TH1D * h1w_rebin_Effic_chstag_t_jet0P                       ;  
  TH1D * h1w_rebin_Effic_chstag_t_jet0Y                       ;  
  TH1D * h1w_rebin_Effic_chstag_t_nvtxg                       ;  
  TH1D * h1w_rebin_Effic_chstag_t_jet0P_TopMatch              ;  
  TH1D * h1w_rebin_Effic_chstag_t_jet0P_TopMatch_TopDist      ;  



  h1w_rebin_Effic_Denom_nvtxg         = (TH1D*)h1w_new_Effic_Denom_nvtxg           ->Rebin(nbins_nvtx-1,"h1w_rebin_Effic_Denom_nvtxg"       ,xbins_nvtx);
  h1w_rebin_Effic_puptag_tau32_nvtxg  = (TH1D*)h1w_new_Effic_puptag_tau32_nvtxg    ->Rebin(nbins_nvtx-1,"h1w_rebin_Effic_puptag_tau32_nvtxg",xbins_nvtx);
  h1w_rebin_Effic_chstag_tau32_nvtxg  = (TH1D*)h1w_new_Effic_chstag_tau32_nvtxg    ->Rebin(nbins_nvtx-1,"h1w_rebin_Effic_chstag_tau32_nvtxg",xbins_nvtx);
  h1w_rebin_Effic_puptag_mass_nvtxg   = (TH1D*)h1w_new_Effic_puptag_mass_nvtxg     ->Rebin(nbins_nvtx-1,"h1w_rebin_Effic_puptag_mass_nvtxg" ,xbins_nvtx);
  h1w_rebin_Effic_chstag_mass_nvtxg   = (TH1D*)h1w_new_Effic_chstag_mass_nvtxg     ->Rebin(nbins_nvtx-1,"h1w_rebin_Effic_chstag_mass_nvtxg" ,xbins_nvtx);
  h1w_rebin_Effic_puptag_t_nvtxg      = (TH1D*)h1w_new_Effic_puptag_t_nvtxg        ->Rebin(nbins_nvtx-1,"h1w_rebin_Effic_puptag_t_nvtxg"    ,xbins_nvtx);
  h1w_rebin_Effic_chstag_t_nvtxg      = (TH1D*)h1w_new_Effic_chstag_t_nvtxg        ->Rebin(nbins_nvtx-1,"h1w_rebin_Effic_chstag_t_nvtxg"    ,xbins_nvtx);

  h1w_Effic_Denom_pup0P                          ->Rebin(10);
  h1w_Effic_Denom_jet0P                          ->Rebin(10);
  h1w_Effic_Denom_jet0Y                          ->Rebin(10);
  h1w_Effic_Denom_jet0P_TopMatch                 ->Rebin(10);
  h1w_Effic_Denom_jet0P_TopMatch_TopDist         ->Rebin(10);
  h1w_Effic_puptag_tau32_pup0P                   ->Rebin(10);
  h1w_Effic_puptag_tau32_jet0P                   ->Rebin(10);
  h1w_Effic_puptag_tau32_jet0Y                   ->Rebin(10);
  h1w_Effic_puptag_tau32_jet0P_TopMatch          ->Rebin(10);
  h1w_Effic_puptag_tau32_jet0P_TopMatch_TopDist  ->Rebin(10);
  h1w_Effic_chstag_tau32_pup0P                   ->Rebin(10);
  h1w_Effic_chstag_tau32_jet0P                   ->Rebin(10);
  h1w_Effic_chstag_tau32_jet0Y                   ->Rebin(10);
  h1w_Effic_chstag_tau32_jet0P_TopMatch          ->Rebin(10);
  h1w_Effic_chstag_tau32_jet0P_TopMatch_TopDist  ->Rebin(10);
  h1w_Effic_puptag_mass_pup0P                    ->Rebin(10);
  h1w_Effic_puptag_mass_jet0P                    ->Rebin(10);
  h1w_Effic_puptag_mass_jet0Y                    ->Rebin(10);
  h1w_Effic_puptag_mass_jet0P_TopMatch           ->Rebin(10);
  h1w_Effic_puptag_mass_jet0P_TopMatch_TopDist   ->Rebin(10);
  h1w_Effic_chstag_mass_pup0P                    ->Rebin(10);
  h1w_Effic_chstag_mass_jet0P                    ->Rebin(10);
  h1w_Effic_chstag_mass_jet0Y                    ->Rebin(10);
  h1w_Effic_chstag_mass_jet0P_TopMatch           ->Rebin(10);
  h1w_Effic_chstag_mass_jet0P_TopMatch_TopDist   ->Rebin(10);
  h1w_Effic_puptag_t_pup0P                       ->Rebin(10);
  h1w_Effic_puptag_t_jet0P                       ->Rebin(10);
  h1w_Effic_puptag_t_jet0Y                       ->Rebin(10);
  h1w_Effic_puptag_t_jet0P_TopMatch              ->Rebin(10);
  h1w_Effic_puptag_t_jet0P_TopMatch_TopDist      ->Rebin(10);
  h1w_Effic_chstag_t_pup0P                       ->Rebin(10);
  h1w_Effic_chstag_t_jet0P                       ->Rebin(10);
  h1w_Effic_chstag_t_jet0Y                       ->Rebin(10);
  h1w_Effic_chstag_t_jet0P_TopMatch              ->Rebin(10);
  h1w_Effic_chstag_t_jet0P_TopMatch_TopDist      ->Rebin(10);


  // TH1D *effic_tau32_pup0P =(TH1D*) h1w_Effic_puptag_tau32_pup0P->Clone();
  // // effic_tau32_pup0P->Reset();
  // effic_tau32_pup0P->Divide( h1w_Effic_puptag_tau32_pup0P, h1w_Effic_Denom_pup0P,1,1,"B");

  // TH1D *effic_tau32_jet0P =(TH1D*) h1w_Effic_puptag_tau32_jet0P->Clone();
  // // effic_tau32_jet0P->Reset();
  // effic_tau32_jet0P->Divide( h1w_Effic_puptag_tau32_jet0P, h1w_Effic_Denom_jet0P,1,1,"B");

  // TH1D *effic_chstag_tau32_jet0P =(TH1D*) h1w_Effic_chstag_tau32_jet0P->Clone();
  // // effic_chstag_tau32_jet0P->Reset();
  // effic_chstag_tau32_jet0P->Divide( h1w_Effic_chstag_tau32_jet0P, h1w_Effic_Denom_jet0P,1,1,"B");


  // TH1D *effic_mass_jet0P =(TH1D*) h1w_Effic_puptag_mass_jet0P->Clone();
  // // effic_mass_jet0P->Reset();
  // effic_mass_jet0P->Divide( h1w_Effic_puptag_mass_jet0P, h1w_Effic_Denom_jet0P,1,1,"B");

  // TH1D *effic_t_jet0P =(TH1D*) h1w_Effic_puptag_t_jet0P->Clone();
  // // effic_t_jet0P->Reset();
  // effic_t_jet0P->Divide( h1w_Effic_puptag_t_jet0P, h1w_Effic_Denom_jet0P,1,1,"B");

  // effic_tau32_pup0P ->SetLineColor(2);    
  // effic_tau32_jet0P ->SetLineColor(3);        
  // effic_mass_jet0P  ->SetLineColor(4);       
  // effic_t_jet0P     ->SetLineColor(5);
  // effic_chstag_tau32_jet0P->SetLineColor(6);

  // effic_tau32_pup0P->GetXaxis()->SetRangeUser(300,4000);
  // effic_tau32_pup0P ->Draw("HIST");          
  // effic_tau32_jet0P ->Draw("HISTsame");
  // effic_chstag_tau32_jet0P  ->Draw("HISTsame");         
  // effic_mass_jet0P  ->Draw("HISTsame");         
  // effic_t_jet0P     ->Draw("HISTsame");      
  // c1237->SaveAs("./plotsEfficTest/effic_tau32_pup0P.pdf");

  // cout<<"h1w_Effic_puptag_tau32_jet0P_TopMatch "<<h1w_Effic_puptag_tau32_jet0P_TopMatch->Integral()<<endl;
  // cout<<"h1w_Effic_Denom_jet0P_TopMatch "<<h1w_Effic_Denom_jet0P_TopMatch->Integral()<<endl;

  // cout<<"h1w_Effic_puptag_tau32_jet0P_TopMatch_TopDist "<<h1w_Effic_puptag_tau32_jet0P_TopMatch_TopDist->Integral()<<endl;
  // cout<<"h1w_Effic_Denom_jet0P_TopMatch_TopDist "<<h1w_Effic_Denom_jet0P_TopMatch_TopDist->Integral()<<endl;


  // TH1D *effic_puptag_tau32_jet0P_TopMatch =(TH1D*) h1w_Effic_puptag_tau32_jet0P_TopMatch->Clone();
  // effic_puptag_tau32_jet0P_TopMatch->Reset();
  // effic_puptag_tau32_jet0P_TopMatch->Divide( h1w_Effic_puptag_tau32_jet0P_TopMatch, h1w_Effic_Denom_jet0P_TopMatch,1,1,"B");

  // TH1D *effic_puptag_tau32_jet0P_TopMatch_TopDist =(TH1D*) h1w_Effic_puptag_tau32_jet0P_TopMatch_TopDist->Clone();
  // effic_puptag_tau32_jet0P_TopMatch_TopDist->Reset();
  // effic_puptag_tau32_jet0P_TopMatch_TopDist->Divide( h1w_Effic_puptag_tau32_jet0P_TopMatch_TopDist, h1w_Effic_Denom_jet0P_TopMatch_TopDist,1,1,"B");

  // effic_puptag_tau32_jet0P_TopMatch         ->SetLineColor(1);
  // effic_puptag_tau32_jet0P_TopMatch_TopDist->SetLineColor(2);

  // effic_puptag_tau32_jet0P_TopMatch_TopDist->GetXaxis()->SetRangeUser(300,4000);
  // effic_puptag_tau32_jet0P_TopMatch_TopDist ->Draw("HIST");          
  // effic_puptag_tau32_jet0P_TopMatch ->Draw("HISTsame");    
  // c1237->SaveAs("./plotsEfficTest/effic_match.pdf");





  TH1D *h1w_effic_puptag_tau32_nvtxg =(TH1D*) h1w_rebin_Effic_puptag_tau32_nvtxg->Clone();
  // h1w_effic_puptag_tau32_nvtxg->Reset();
  h1w_effic_puptag_tau32_nvtxg->Divide( h1w_rebin_Effic_puptag_tau32_nvtxg, h1w_rebin_Effic_Denom_nvtxg,1,1,"B");

  TH1D *h1w_effic_puptag_mass_nvtxg =(TH1D*) h1w_rebin_Effic_puptag_mass_nvtxg->Clone();
  // h1w_effic_puptag_mass_nvtxg->Reset();
  h1w_effic_puptag_mass_nvtxg->Divide( h1w_rebin_Effic_puptag_mass_nvtxg, h1w_rebin_Effic_Denom_nvtxg,1,1,"B");

  TH1D *h1w_effic_puptag_t_nvtxg =(TH1D*) h1w_rebin_Effic_puptag_t_nvtxg->Clone();
  // h1w_effic_puptag_t_nvtxg->Reset();
  h1w_effic_puptag_t_nvtxg->Divide( h1w_rebin_Effic_puptag_t_nvtxg, h1w_rebin_Effic_Denom_nvtxg,1,1,"B");


  TH1D *h1w_effic_chstag_tau32_nvtxg =(TH1D*) h1w_rebin_Effic_chstag_tau32_nvtxg->Clone();
  // h1w_effic_chstag_tau32_nvtxg->Reset();
  h1w_effic_chstag_tau32_nvtxg->Divide( h1w_rebin_Effic_chstag_tau32_nvtxg, h1w_rebin_Effic_Denom_nvtxg,1,1,"B");

  TH1D *h1w_effic_chstag_mass_nvtxg =(TH1D*) h1w_rebin_Effic_chstag_mass_nvtxg->Clone();
  // h1w_effic_chstag_mass_nvtxg->Reset();
  h1w_effic_chstag_mass_nvtxg->Divide( h1w_rebin_Effic_chstag_mass_nvtxg, h1w_rebin_Effic_Denom_nvtxg,1,1,"B");

  TH1D *h1w_effic_chstag_t_nvtxg =(TH1D*) h1w_rebin_Effic_chstag_t_nvtxg->Clone();
  // h1w_effic_chstag_t_nvtxg->Reset();
  h1w_effic_chstag_t_nvtxg->Divide( h1w_rebin_Effic_chstag_t_nvtxg, h1w_rebin_Effic_Denom_nvtxg,1,1,"B");

  h1w_effic_puptag_tau32_nvtxg ->SetMarkerStyle(20);        
  h1w_effic_puptag_mass_nvtxg  ->SetMarkerStyle(21);       
  h1w_effic_puptag_t_nvtxg     ->SetMarkerStyle(22);

  h1w_effic_chstag_tau32_nvtxg ->SetMarkerStyle(24);        
  h1w_effic_chstag_mass_nvtxg  ->SetMarkerStyle(25);       
  h1w_effic_chstag_t_nvtxg     ->SetMarkerStyle(26);

  h1w_effic_puptag_tau32_nvtxg ->SetMarkerColor(6);              
  h1w_effic_puptag_mass_nvtxg  ->SetMarkerColor(kBlue);         
  h1w_effic_puptag_t_nvtxg     ->SetMarkerColor(kOrange+1);

  h1w_effic_chstag_tau32_nvtxg ->SetMarkerColor(6);        
  h1w_effic_chstag_mass_nvtxg  ->SetMarkerColor(kBlue);       
  h1w_effic_chstag_t_nvtxg     ->SetMarkerColor(kOrange+1);

  h1w_effic_puptag_tau32_nvtxg ->SetLineColor(6);           
  h1w_effic_puptag_mass_nvtxg  ->SetLineColor(kBlue);      
  h1w_effic_puptag_t_nvtxg     ->SetLineColor(kOrange+1);

  h1w_effic_chstag_tau32_nvtxg ->SetLineColor(6);           
  h1w_effic_chstag_mass_nvtxg  ->SetLineColor(kBlue);      
  h1w_effic_chstag_t_nvtxg     ->SetLineColor(kOrange+1);

  h1w_effic_puptag_tau32_nvtxg ->SetLineWidth(2);   
  h1w_effic_puptag_mass_nvtxg  ->SetLineWidth(2);  
  h1w_effic_puptag_t_nvtxg     ->SetLineWidth(2);

  h1w_effic_chstag_tau32_nvtxg ->SetLineWidth(2);   
  h1w_effic_chstag_mass_nvtxg  ->SetLineWidth(2);  
  h1w_effic_chstag_t_nvtxg     ->SetLineWidth(2);




  h1w_effic_puptag_tau32_nvtxg->SetTitle(title.c_str());

  h1w_effic_puptag_tau32_nvtxg->SetStats(0);


  h1w_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleSize(0.065);
  h1w_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleOffset(0.9); 
  h1w_effic_puptag_tau32_nvtxg->GetYaxis()->SetLabelSize(0.06);

  h1w_effic_puptag_tau32_nvtxg->GetXaxis()->SetNdivisions(506);
  h1w_effic_puptag_tau32_nvtxg->GetXaxis()->SetLabelFont(42);
  h1w_effic_puptag_tau32_nvtxg->GetXaxis()->SetLabelSize(0.05);
  h1w_effic_puptag_tau32_nvtxg->GetXaxis()->SetTitleSize(0.056);
  h1w_effic_puptag_tau32_nvtxg->GetXaxis()->SetTickLength(0.045);
  h1w_effic_puptag_tau32_nvtxg->GetXaxis()->SetTitleOffset(1.15);
  h1w_effic_puptag_tau32_nvtxg->GetXaxis()->SetTitleFont(42);

  h1w_effic_puptag_tau32_nvtxg->GetYaxis()->SetNdivisions(506);
  h1w_effic_puptag_tau32_nvtxg->GetYaxis()->SetLabelFont(42);
  h1w_effic_puptag_tau32_nvtxg->GetYaxis()->SetLabelSize(0.05);
  h1w_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleSize(0.06125);
  h1w_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleOffset(1.17);
  h1w_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleFont(42);

  h1w_effic_puptag_tau32_nvtxg->GetZaxis()->SetLabelFont(42);
  h1w_effic_puptag_tau32_nvtxg->GetZaxis()->SetLabelSize(0.0425);
  h1w_effic_puptag_tau32_nvtxg->GetZaxis()->SetTitleSize(0.0475);
  h1w_effic_puptag_tau32_nvtxg->GetZaxis()->SetTitleFont(42);

  h1w_effic_puptag_tau32_nvtxg->GetYaxis()->SetRangeUser(0.0,1.1);
  h1w_effic_puptag_tau32_nvtxg ->Draw("");
  h1w_effic_puptag_mass_nvtxg  ->Draw("same");         
  h1w_effic_puptag_t_nvtxg     ->Draw("same");      

  h1w_effic_chstag_tau32_nvtxg ->Draw("same");
  h1w_effic_chstag_mass_nvtxg  ->Draw("same");         
  h1w_effic_chstag_t_nvtxg     ->Draw("same");      





  TLegend * h1w_leg;
  h1w_leg = new TLegend( 0.58, 0.6,0.95, 0.88);  //( 0.56, 0.69,0.98, 0.89);
  h1w_leg->SetBorderSize(0);
  h1w_leg->SetFillColor(0);
  h1w_leg->SetFillStyle(4000);
  h1w_leg->SetTextSize(0.04);   //0.038
  h1w_leg->SetMargin(0.18 );
  //h1w_leg->SetHeader("Loose t-tag - tt weight");
  h1w_leg->AddEntry( h1w_effic_chstag_mass_nvtxg    , "CHS: m_{SD} tag"            , "LP" );
  h1w_leg->AddEntry( h1w_effic_chstag_tau32_nvtxg   , "CHS: #tau_{32} tag"         , "LP" );
  h1w_leg->AddEntry( h1w_effic_chstag_t_nvtxg       , "CHS: m_{SD}+#tau_{32} tag"  , "LP" );
  
  h1w_leg->AddEntry( h1w_effic_puptag_mass_nvtxg    , "PUPPI: m_{SD} tag"                     , "LP" );
  h1w_leg->AddEntry( h1w_effic_puptag_tau32_nvtxg   , "PUPPI: #tau_{32} tag"                  , "LP" );
  h1w_leg->AddEntry( h1w_effic_puptag_t_nvtxg       , "PUPPI: m_{SD}+#tau_{32} tag"           , "LP" );
  h1w_leg->Draw("same");

  TLatex *   h1w_tex = new TLatex(0.18,0.83,"#font[62]{CMS}");// #font[52]{Simulation Preliminary}");
  h1w_tex->SetNDC();
  h1w_tex->SetTextFont(42);
  h1w_tex->SetTextSize(0.0555); //0.0625
  h1w_tex->SetLineWidth(2);
  h1w_tex->Draw();
  h1w_tex = new TLatex(0.18,0.77,Form("#font[52]{#splitline{Simulation}{%s}}",CMSsubtext.c_str()));
  h1w_tex->SetNDC();
  h1w_tex->SetTextFont(42);
  h1w_tex->SetTextSize(0.05); //0.0625
  h1w_tex->SetLineWidth(2);
  h1w_tex->Draw();
  h1w_tex = new TLatex(0.96,0.936,"13 TeV");
  h1w_tex->SetNDC();
  h1w_tex->SetTextAlign(31);
  h1w_tex->SetTextFont(42);
  h1w_tex->SetTextSize(0.0575);
  h1w_tex->SetLineWidth(2);
  h1w_tex->Draw();
  

  c1237->SaveAs(Form("./plotEfficTest_WPABC/h1w_effic_tau32_nvtxg_WPA%s.pdf",endlabel.c_str()));

  //--------------------------------------------------------------------------------------------------------------




  TH1D *    h2w_Effic_Denom_pup0P                           = (TH1D *) fTop2w->Get( "h_Effic_Denom_pup0P"                            );
  TH1D *    h2w_Effic_Denom_jet0P                           = (TH1D *) fTop2w->Get( "h_Effic_Denom_jet0P"                            );
  TH1D *    h2w_Effic_Denom_jet0Y                           = (TH1D *) fTop2w->Get( "h_Effic_Denom_jet0Y"                            );
  TH1D *    h2w_Effic_Denom_nvtxg                           = (TH1D *) fTop2w->Get( "h_Effic_Denom_nvtxg"                            );
  TH1D *    h2w_Effic_Denom_jet0P_TopMatch                  = (TH1D *) fTop2w->Get( "h_Effic_Denom_jet0P_TopMatch"                   );
  TH1D *    h2w_Effic_Denom_jet0P_TopMatch_TopDist          = (TH1D *) fTop2w->Get( "h_Effic_Denom_jet0P_TopMatch_TopDist"           );
  TH1D *    h2w_Effic_puptag_tau32_pup0P                    = (TH1D *) fTop2w->Get( "h_Effic_puptag_tau32_pup0P"                     );
  TH1D *    h2w_Effic_puptag_tau32_jet0P                    = (TH1D *) fTop2w->Get( "h_Effic_puptag_tau32_jet0P"                     );
  TH1D *    h2w_Effic_puptag_tau32_jet0Y                    = (TH1D *) fTop2w->Get( "h_Effic_puptag_tau32_jet0Y"                     );
  TH1D *    h2w_Effic_puptag_tau32_nvtxg                    = (TH1D *) fTop2w->Get( "h_Effic_puptag_tau32_nvtxg"                     );
  TH1D *    h2w_Effic_puptag_tau32_jet0P_TopMatch           = (TH1D *) fTop2w->Get( "h_Effic_puptag_tau32_jet0P_TopMatch"            );
  TH1D *    h2w_Effic_puptag_tau32_jet0P_TopMatch_TopDist   = (TH1D *) fTop2w->Get( "h_Effic_puptag_tau32_jet0P_TopMatch_TopDist"    );
  TH1D *    h2w_Effic_chstag_tau32_pup0P                    = (TH1D *) fTop2w->Get( "h_Effic_chstag_tau32_pup0P"                     );
  TH1D *    h2w_Effic_chstag_tau32_jet0P                    = (TH1D *) fTop2w->Get( "h_Effic_chstag_tau32_jet0P"                     );
  TH1D *    h2w_Effic_chstag_tau32_jet0Y                    = (TH1D *) fTop2w->Get( "h_Effic_chstag_tau32_jet0Y"                     );
  TH1D *    h2w_Effic_chstag_tau32_nvtxg                    = (TH1D *) fTop2w->Get( "h_Effic_chstag_tau32_nvtxg"                     );
  TH1D *    h2w_Effic_chstag_tau32_jet0P_TopMatch           = (TH1D *) fTop2w->Get( "h_Effic_chstag_tau32_jet0P_TopMatch"            );
  TH1D *    h2w_Effic_chstag_tau32_jet0P_TopMatch_TopDist   = (TH1D *) fTop2w->Get( "h_Effic_chstag_tau32_jet0P_TopMatch_TopDist"    );
  TH1D *    h2w_Effic_puptag_mass_pup0P                     = (TH1D *) fTop2w->Get( "h_Effic_puptag_mass_pup0P"                      );
  TH1D *    h2w_Effic_puptag_mass_jet0P                     = (TH1D *) fTop2w->Get( "h_Effic_puptag_mass_jet0P"                      );
  TH1D *    h2w_Effic_puptag_mass_jet0Y                     = (TH1D *) fTop2w->Get( "h_Effic_puptag_mass_jet0Y"                      );
  TH1D *    h2w_Effic_puptag_mass_nvtxg                     = (TH1D *) fTop2w->Get( "h_Effic_puptag_mass_nvtxg"                      );
  TH1D *    h2w_Effic_puptag_mass_jet0P_TopMatch            = (TH1D *) fTop2w->Get( "h_Effic_puptag_mass_jet0P_TopMatch"             );
  TH1D *    h2w_Effic_puptag_mass_jet0P_TopMatch_TopDist    = (TH1D *) fTop2w->Get( "h_Effic_puptag_mass_jet0P_TopMatch_TopDist"     );
  TH1D *    h2w_Effic_chstag_mass_pup0P                     = (TH1D *) fTop2w->Get( "h_Effic_chstag_mass_pup0P"                      );
  TH1D *    h2w_Effic_chstag_mass_jet0P                     = (TH1D *) fTop2w->Get( "h_Effic_chstag_mass_jet0P"                      );
  TH1D *    h2w_Effic_chstag_mass_jet0Y                     = (TH1D *) fTop2w->Get( "h_Effic_chstag_mass_jet0Y"                      );
  TH1D *    h2w_Effic_chstag_mass_nvtxg                     = (TH1D *) fTop2w->Get( "h_Effic_chstag_mass_nvtxg"                      );
  TH1D *    h2w_Effic_chstag_mass_jet0P_TopMatch            = (TH1D *) fTop2w->Get( "h_Effic_chstag_mass_jet0P_TopMatch"             );
  TH1D *    h2w_Effic_chstag_mass_jet0P_TopMatch_TopDist    = (TH1D *) fTop2w->Get( "h_Effic_chstag_mass_jet0P_TopMatch_TopDist"     );
  TH1D *    h2w_Effic_puptag_t_pup0P                        = (TH1D *) fTop2w->Get( "h_Effic_puptag_t_pup0P"                         );
  TH1D *    h2w_Effic_puptag_t_jet0P                        = (TH1D *) fTop2w->Get( "h_Effic_puptag_t_jet0P"                         );
  TH1D *    h2w_Effic_puptag_t_jet0Y                        = (TH1D *) fTop2w->Get( "h_Effic_puptag_t_jet0Y"                         );
  TH1D *    h2w_Effic_puptag_t_nvtxg                        = (TH1D *) fTop2w->Get( "h_Effic_puptag_t_nvtxg"                         );
  TH1D *    h2w_Effic_puptag_t_jet0P_TopMatch               = (TH1D *) fTop2w->Get( "h_Effic_puptag_t_jet0P_TopMatch"                );
  TH1D *    h2w_Effic_puptag_t_jet0P_TopMatch_TopDist       = (TH1D *) fTop2w->Get( "h_Effic_puptag_t_jet0P_TopMatch_TopDist"        );
  TH1D *    h2w_Effic_chstag_t_pup0P                        = (TH1D *) fTop2w->Get( "h_Effic_chstag_t_pup0P"                         );
  TH1D *    h2w_Effic_chstag_t_jet0P                        = (TH1D *) fTop2w->Get( "h_Effic_chstag_t_jet0P"                         );
  TH1D *    h2w_Effic_chstag_t_jet0Y                        = (TH1D *) fTop2w->Get( "h_Effic_chstag_t_jet0Y"                         );
  TH1D *    h2w_Effic_chstag_t_nvtxg                        = (TH1D *) fTop2w->Get( "h_Effic_chstag_t_nvtxg"                         );
  TH1D *    h2w_Effic_chstag_t_jet0P_TopMatch               = (TH1D *) fTop2w->Get( "h_Effic_chstag_t_jet0P_TopMatch"                );
  TH1D *    h2w_Effic_chstag_t_jet0P_TopMatch_TopDist       = (TH1D *) fTop2w->Get( "h_Effic_chstag_t_jet0P_TopMatch_TopDist"        );




  TH1D *    h2w_new_Effic_Denom_pup0P                         = (TH1D*) h2w_Effic_Denom_pup0P                            ->Clone();  
  TH1D *    h2w_new_Effic_Denom_jet0P                         = (TH1D*) h2w_Effic_Denom_jet0P                            ->Clone();  
  TH1D *    h2w_new_Effic_Denom_jet0Y                         = (TH1D*) h2w_Effic_Denom_jet0Y                            ->Clone();  
  TH1D *    h2w_new_Effic_Denom_nvtxg                         = (TH1D*) h2w_Effic_Denom_nvtxg                            ->Clone();  
  TH1D *    h2w_new_Effic_Denom_jet0P_TopMatch                = (TH1D*) h2w_Effic_Denom_jet0P_TopMatch                   ->Clone();  
  TH1D *    h2w_new_Effic_Denom_jet0P_TopMatch_TopDist        = (TH1D*) h2w_Effic_Denom_jet0P_TopMatch_TopDist           ->Clone();  
  TH1D *    h2w_new_Effic_puptag_tau32_pup0P                  = (TH1D*) h2w_Effic_puptag_tau32_pup0P                     ->Clone();  
  TH1D *    h2w_new_Effic_puptag_tau32_jet0P                  = (TH1D*) h2w_Effic_puptag_tau32_jet0P                     ->Clone();  
  TH1D *    h2w_new_Effic_puptag_tau32_jet0Y                  = (TH1D*) h2w_Effic_puptag_tau32_jet0Y                     ->Clone();  
  TH1D *    h2w_new_Effic_puptag_tau32_nvtxg                  = (TH1D*) h2w_Effic_puptag_tau32_nvtxg                     ->Clone();  
  TH1D *    h2w_new_Effic_puptag_tau32_jet0P_TopMatch         = (TH1D*) h2w_Effic_puptag_tau32_jet0P_TopMatch            ->Clone();  
  TH1D *    h2w_new_Effic_puptag_tau32_jet0P_TopMatch_TopDist = (TH1D*) h2w_Effic_puptag_tau32_jet0P_TopMatch_TopDist    ->Clone();  
  TH1D *    h2w_new_Effic_chstag_tau32_pup0P                  = (TH1D*) h2w_Effic_chstag_tau32_pup0P                     ->Clone();  
  TH1D *    h2w_new_Effic_chstag_tau32_jet0P                  = (TH1D*) h2w_Effic_chstag_tau32_jet0P                     ->Clone();  
  TH1D *    h2w_new_Effic_chstag_tau32_jet0Y                  = (TH1D*) h2w_Effic_chstag_tau32_jet0Y                     ->Clone();  
  TH1D *    h2w_new_Effic_chstag_tau32_nvtxg                  = (TH1D*) h2w_Effic_chstag_tau32_nvtxg                     ->Clone();  
  TH1D *    h2w_new_Effic_chstag_tau32_jet0P_TopMatch         = (TH1D*) h2w_Effic_chstag_tau32_jet0P_TopMatch            ->Clone();  
  TH1D *    h2w_new_Effic_chstag_tau32_jet0P_TopMatch_TopDist = (TH1D*) h2w_Effic_chstag_tau32_jet0P_TopMatch_TopDist    ->Clone();  
  TH1D *    h2w_new_Effic_puptag_mass_pup0P                   = (TH1D*) h2w_Effic_puptag_mass_pup0P                      ->Clone();  
  TH1D *    h2w_new_Effic_puptag_mass_jet0P                   = (TH1D*) h2w_Effic_puptag_mass_jet0P                      ->Clone();  
  TH1D *    h2w_new_Effic_puptag_mass_jet0Y                   = (TH1D*) h2w_Effic_puptag_mass_jet0Y                      ->Clone();  
  TH1D *    h2w_new_Effic_puptag_mass_nvtxg                   = (TH1D*) h2w_Effic_puptag_mass_nvtxg                      ->Clone();  
  TH1D *    h2w_new_Effic_puptag_mass_jet0P_TopMatch          = (TH1D*) h2w_Effic_puptag_mass_jet0P_TopMatch             ->Clone();  
  TH1D *    h2w_new_Effic_puptag_mass_jet0P_TopMatch_TopDist  = (TH1D*) h2w_Effic_puptag_mass_jet0P_TopMatch_TopDist     ->Clone();  
  TH1D *    h2w_new_Effic_chstag_mass_pup0P                   = (TH1D*) h2w_Effic_chstag_mass_pup0P                      ->Clone();  
  TH1D *    h2w_new_Effic_chstag_mass_jet0P                   = (TH1D*) h2w_Effic_chstag_mass_jet0P                      ->Clone();  
  TH1D *    h2w_new_Effic_chstag_mass_jet0Y                   = (TH1D*) h2w_Effic_chstag_mass_jet0Y                      ->Clone();  
  TH1D *    h2w_new_Effic_chstag_mass_nvtxg                   = (TH1D*) h2w_Effic_chstag_mass_nvtxg                      ->Clone();  
  TH1D *    h2w_new_Effic_chstag_mass_jet0P_TopMatch          = (TH1D*) h2w_Effic_chstag_mass_jet0P_TopMatch             ->Clone();  
  TH1D *    h2w_new_Effic_chstag_mass_jet0P_TopMatch_TopDist  = (TH1D*) h2w_Effic_chstag_mass_jet0P_TopMatch_TopDist     ->Clone();  
  TH1D *    h2w_new_Effic_puptag_t_pup0P                      = (TH1D*) h2w_Effic_puptag_t_pup0P                         ->Clone();  
  TH1D *    h2w_new_Effic_puptag_t_jet0P                      = (TH1D*) h2w_Effic_puptag_t_jet0P                         ->Clone();  
  TH1D *    h2w_new_Effic_puptag_t_jet0Y                      = (TH1D*) h2w_Effic_puptag_t_jet0Y                         ->Clone();  
  TH1D *    h2w_new_Effic_puptag_t_nvtxg                      = (TH1D*) h2w_Effic_puptag_t_nvtxg                         ->Clone();  
  TH1D *    h2w_new_Effic_puptag_t_jet0P_TopMatch             = (TH1D*) h2w_Effic_puptag_t_jet0P_TopMatch                ->Clone();  
  TH1D *    h2w_new_Effic_puptag_t_jet0P_TopMatch_TopDist     = (TH1D*) h2w_Effic_puptag_t_jet0P_TopMatch_TopDist        ->Clone();  
  TH1D *    h2w_new_Effic_chstag_t_pup0P                      = (TH1D*) h2w_Effic_chstag_t_pup0P                         ->Clone();  
  TH1D *    h2w_new_Effic_chstag_t_jet0P                      = (TH1D*) h2w_Effic_chstag_t_jet0P                         ->Clone();  
  TH1D *    h2w_new_Effic_chstag_t_jet0Y                      = (TH1D*) h2w_Effic_chstag_t_jet0Y                         ->Clone();  
  TH1D *    h2w_new_Effic_chstag_t_nvtxg                      = (TH1D*) h2w_Effic_chstag_t_nvtxg                         ->Clone();  
  TH1D *    h2w_new_Effic_chstag_t_jet0P_TopMatch             = (TH1D*) h2w_Effic_chstag_t_jet0P_TopMatch                ->Clone();  
  TH1D *    h2w_new_Effic_chstag_t_jet0P_TopMatch_TopDist     = (TH1D*) h2w_Effic_chstag_t_jet0P_TopMatch_TopDist        ->Clone();  


  TH1D * h2w_rebin_Effic_Denom_pup0P                          ;  
  TH1D * h2w_rebin_Effic_Denom_jet0P                          ;  
  TH1D * h2w_rebin_Effic_Denom_jet0Y                          ;  
  TH1D * h2w_rebin_Effic_Denom_nvtxg                          ;  
  TH1D * h2w_rebin_Effic_Denom_jet0P_TopMatch                 ;  
  TH1D * h2w_rebin_Effic_Denom_jet0P_TopMatch_TopDist         ;  
  TH1D * h2w_rebin_Effic_puptag_tau32_pup0P                   ;  
  TH1D * h2w_rebin_Effic_puptag_tau32_jet0P                   ;  
  TH1D * h2w_rebin_Effic_puptag_tau32_jet0Y                   ;  
  TH1D * h2w_rebin_Effic_puptag_tau32_nvtxg                   ;  
  TH1D * h2w_rebin_Effic_puptag_tau32_jet0P_TopMatch          ;  
  TH1D * h2w_rebin_Effic_puptag_tau32_jet0P_TopMatch_TopDist  ;  
  TH1D * h2w_rebin_Effic_chstag_tau32_pup0P                   ;  
  TH1D * h2w_rebin_Effic_chstag_tau32_jet0P                   ;  
  TH1D * h2w_rebin_Effic_chstag_tau32_jet0Y                   ;  
  TH1D * h2w_rebin_Effic_chstag_tau32_nvtxg                   ;  
  TH1D * h2w_rebin_Effic_chstag_tau32_jet0P_TopMatch          ;  
  TH1D * h2w_rebin_Effic_chstag_tau32_jet0P_TopMatch_TopDist  ;  
  TH1D * h2w_rebin_Effic_puptag_mass_pup0P                    ;  
  TH1D * h2w_rebin_Effic_puptag_mass_jet0P                    ;  
  TH1D * h2w_rebin_Effic_puptag_mass_jet0Y                    ;  
  TH1D * h2w_rebin_Effic_puptag_mass_nvtxg                    ;  
  TH1D * h2w_rebin_Effic_puptag_mass_jet0P_TopMatch           ;  
  TH1D * h2w_rebin_Effic_puptag_mass_jet0P_TopMatch_TopDist   ;  
  TH1D * h2w_rebin_Effic_chstag_mass_pup0P                    ;  
  TH1D * h2w_rebin_Effic_chstag_mass_jet0P                    ;  
  TH1D * h2w_rebin_Effic_chstag_mass_jet0Y                    ;  
  TH1D * h2w_rebin_Effic_chstag_mass_nvtxg                    ;  
  TH1D * h2w_rebin_Effic_chstag_mass_jet0P_TopMatch           ;  
  TH1D * h2w_rebin_Effic_chstag_mass_jet0P_TopMatch_TopDist   ;  
  TH1D * h2w_rebin_Effic_puptag_t_pup0P                       ;  
  TH1D * h2w_rebin_Effic_puptag_t_jet0P                       ;  
  TH1D * h2w_rebin_Effic_puptag_t_jet0Y                       ;  
  TH1D * h2w_rebin_Effic_puptag_t_nvtxg                       ;  
  TH1D * h2w_rebin_Effic_puptag_t_jet0P_TopMatch              ;  
  TH1D * h2w_rebin_Effic_puptag_t_jet0P_TopMatch_TopDist      ;  
  TH1D * h2w_rebin_Effic_chstag_t_pup0P                       ;  
  TH1D * h2w_rebin_Effic_chstag_t_jet0P                       ;  
  TH1D * h2w_rebin_Effic_chstag_t_jet0Y                       ;  
  TH1D * h2w_rebin_Effic_chstag_t_nvtxg                       ;  
  TH1D * h2w_rebin_Effic_chstag_t_jet0P_TopMatch              ;  
  TH1D * h2w_rebin_Effic_chstag_t_jet0P_TopMatch_TopDist      ;  



  h2w_rebin_Effic_Denom_nvtxg         = (TH1D*)h2w_new_Effic_Denom_nvtxg           ->Rebin(nbins_nvtx-1,"h2w_rebin_Effic_Denom_nvtxg"       ,xbins_nvtx);
  h2w_rebin_Effic_puptag_tau32_nvtxg  = (TH1D*)h2w_new_Effic_puptag_tau32_nvtxg    ->Rebin(nbins_nvtx-1,"h2w_rebin_Effic_puptag_tau32_nvtxg",xbins_nvtx);
  h2w_rebin_Effic_chstag_tau32_nvtxg  = (TH1D*)h2w_new_Effic_chstag_tau32_nvtxg    ->Rebin(nbins_nvtx-1,"h2w_rebin_Effic_chstag_tau32_nvtxg",xbins_nvtx);
  h2w_rebin_Effic_puptag_mass_nvtxg   = (TH1D*)h2w_new_Effic_puptag_mass_nvtxg     ->Rebin(nbins_nvtx-1,"h2w_rebin_Effic_puptag_mass_nvtxg" ,xbins_nvtx);
  h2w_rebin_Effic_chstag_mass_nvtxg   = (TH1D*)h2w_new_Effic_chstag_mass_nvtxg     ->Rebin(nbins_nvtx-1,"h2w_rebin_Effic_chstag_mass_nvtxg" ,xbins_nvtx);
  h2w_rebin_Effic_puptag_t_nvtxg      = (TH1D*)h2w_new_Effic_puptag_t_nvtxg        ->Rebin(nbins_nvtx-1,"h2w_rebin_Effic_puptag_t_nvtxg"    ,xbins_nvtx);
  h2w_rebin_Effic_chstag_t_nvtxg      = (TH1D*)h2w_new_Effic_chstag_t_nvtxg        ->Rebin(nbins_nvtx-1,"h2w_rebin_Effic_chstag_t_nvtxg"    ,xbins_nvtx);

  h2w_Effic_Denom_pup0P                          ->Rebin(10);
  h2w_Effic_Denom_jet0P                          ->Rebin(10);
  h2w_Effic_Denom_jet0Y                          ->Rebin(10);
  h2w_Effic_Denom_jet0P_TopMatch                 ->Rebin(10);
  h2w_Effic_Denom_jet0P_TopMatch_TopDist         ->Rebin(10);
  h2w_Effic_puptag_tau32_pup0P                   ->Rebin(10);
  h2w_Effic_puptag_tau32_jet0P                   ->Rebin(10);
  h2w_Effic_puptag_tau32_jet0Y                   ->Rebin(10);
  h2w_Effic_puptag_tau32_jet0P_TopMatch          ->Rebin(10);
  h2w_Effic_puptag_tau32_jet0P_TopMatch_TopDist  ->Rebin(10);
  h2w_Effic_chstag_tau32_pup0P                   ->Rebin(10);
  h2w_Effic_chstag_tau32_jet0P                   ->Rebin(10);
  h2w_Effic_chstag_tau32_jet0Y                   ->Rebin(10);
  h2w_Effic_chstag_tau32_jet0P_TopMatch          ->Rebin(10);
  h2w_Effic_chstag_tau32_jet0P_TopMatch_TopDist  ->Rebin(10);
  h2w_Effic_puptag_mass_pup0P                    ->Rebin(10);
  h2w_Effic_puptag_mass_jet0P                    ->Rebin(10);
  h2w_Effic_puptag_mass_jet0Y                    ->Rebin(10);
  h2w_Effic_puptag_mass_jet0P_TopMatch           ->Rebin(10);
  h2w_Effic_puptag_mass_jet0P_TopMatch_TopDist   ->Rebin(10);
  h2w_Effic_chstag_mass_pup0P                    ->Rebin(10);
  h2w_Effic_chstag_mass_jet0P                    ->Rebin(10);
  h2w_Effic_chstag_mass_jet0Y                    ->Rebin(10);
  h2w_Effic_chstag_mass_jet0P_TopMatch           ->Rebin(10);
  h2w_Effic_chstag_mass_jet0P_TopMatch_TopDist   ->Rebin(10);
  h2w_Effic_puptag_t_pup0P                       ->Rebin(10);
  h2w_Effic_puptag_t_jet0P                       ->Rebin(10);
  h2w_Effic_puptag_t_jet0Y                       ->Rebin(10);
  h2w_Effic_puptag_t_jet0P_TopMatch              ->Rebin(10);
  h2w_Effic_puptag_t_jet0P_TopMatch_TopDist      ->Rebin(10);
  h2w_Effic_chstag_t_pup0P                       ->Rebin(10);
  h2w_Effic_chstag_t_jet0P                       ->Rebin(10);
  h2w_Effic_chstag_t_jet0Y                       ->Rebin(10);
  h2w_Effic_chstag_t_jet0P_TopMatch              ->Rebin(10);
  h2w_Effic_chstag_t_jet0P_TopMatch_TopDist      ->Rebin(10);


  // TH1D *effic_tau32_pup0P =(TH1D*) h2w_Effic_puptag_tau32_pup0P->Clone();
  // // effic_tau32_pup0P->Reset();
  // effic_tau32_pup0P->Divide( h2w_Effic_puptag_tau32_pup0P, h2w_Effic_Denom_pup0P,1,1,"B");

  // TH1D *effic_tau32_jet0P =(TH1D*) h2w_Effic_puptag_tau32_jet0P->Clone();
  // // effic_tau32_jet0P->Reset();
  // effic_tau32_jet0P->Divide( h2w_Effic_puptag_tau32_jet0P, h2w_Effic_Denom_jet0P,1,1,"B");

  // TH1D *effic_chstag_tau32_jet0P =(TH1D*) h2w_Effic_chstag_tau32_jet0P->Clone();
  // // effic_chstag_tau32_jet0P->Reset();
  // effic_chstag_tau32_jet0P->Divide( h2w_Effic_chstag_tau32_jet0P, h2w_Effic_Denom_jet0P,1,1,"B");


  // TH1D *effic_mass_jet0P =(TH1D*) h2w_Effic_puptag_mass_jet0P->Clone();
  // // effic_mass_jet0P->Reset();
  // effic_mass_jet0P->Divide( h2w_Effic_puptag_mass_jet0P, h2w_Effic_Denom_jet0P,1,1,"B");

  // TH1D *effic_t_jet0P =(TH1D*) h2w_Effic_puptag_t_jet0P->Clone();
  // // effic_t_jet0P->Reset();
  // effic_t_jet0P->Divide( h2w_Effic_puptag_t_jet0P, h2w_Effic_Denom_jet0P,1,1,"B");

  // effic_tau32_pup0P ->SetLineColor(2);    
  // effic_tau32_jet0P ->SetLineColor(3);        
  // effic_mass_jet0P  ->SetLineColor(4);       
  // effic_t_jet0P     ->SetLineColor(5);
  // effic_chstag_tau32_jet0P->SetLineColor(6);

  // effic_tau32_pup0P->GetXaxis()->SetRangeUser(300,4000);
  // effic_tau32_pup0P ->Draw("HIST");          
  // effic_tau32_jet0P ->Draw("HISTsame");
  // effic_chstag_tau32_jet0P  ->Draw("HISTsame");         
  // effic_mass_jet0P  ->Draw("HISTsame");         
  // effic_t_jet0P     ->Draw("HISTsame");      
  // c1237->SaveAs("./plotsEfficTest/effic_tau32_pup0P.pdf");

  // cout<<"h2w_Effic_puptag_tau32_jet0P_TopMatch "<<h2w_Effic_puptag_tau32_jet0P_TopMatch->Integral()<<endl;
  // cout<<"h2w_Effic_Denom_jet0P_TopMatch "<<h2w_Effic_Denom_jet0P_TopMatch->Integral()<<endl;

  // cout<<"h2w_Effic_puptag_tau32_jet0P_TopMatch_TopDist "<<h2w_Effic_puptag_tau32_jet0P_TopMatch_TopDist->Integral()<<endl;
  // cout<<"h2w_Effic_Denom_jet0P_TopMatch_TopDist "<<h2w_Effic_Denom_jet0P_TopMatch_TopDist->Integral()<<endl;


  // TH1D *effic_puptag_tau32_jet0P_TopMatch =(TH1D*) h2w_Effic_puptag_tau32_jet0P_TopMatch->Clone();
  // effic_puptag_tau32_jet0P_TopMatch->Reset();
  // effic_puptag_tau32_jet0P_TopMatch->Divide( h2w_Effic_puptag_tau32_jet0P_TopMatch, h2w_Effic_Denom_jet0P_TopMatch,1,1,"B");

  // TH1D *effic_puptag_tau32_jet0P_TopMatch_TopDist =(TH1D*) h2w_Effic_puptag_tau32_jet0P_TopMatch_TopDist->Clone();
  // effic_puptag_tau32_jet0P_TopMatch_TopDist->Reset();
  // effic_puptag_tau32_jet0P_TopMatch_TopDist->Divide( h2w_Effic_puptag_tau32_jet0P_TopMatch_TopDist, h2w_Effic_Denom_jet0P_TopMatch_TopDist,1,1,"B");

  // effic_puptag_tau32_jet0P_TopMatch         ->SetLineColor(1);
  // effic_puptag_tau32_jet0P_TopMatch_TopDist->SetLineColor(2);

  // effic_puptag_tau32_jet0P_TopMatch_TopDist->GetXaxis()->SetRangeUser(300,4000);
  // effic_puptag_tau32_jet0P_TopMatch_TopDist ->Draw("HIST");          
  // effic_puptag_tau32_jet0P_TopMatch ->Draw("HISTsame");    
  // c1237->SaveAs("./plotsEfficTest/effic_match.pdf");





  TH1D *h2w_effic_puptag_tau32_nvtxg =(TH1D*) h2w_rebin_Effic_puptag_tau32_nvtxg->Clone();
  // h2w_effic_puptag_tau32_nvtxg->Reset();
  h2w_effic_puptag_tau32_nvtxg->Divide( h2w_rebin_Effic_puptag_tau32_nvtxg, h2w_rebin_Effic_Denom_nvtxg,1,1,"B");

  TH1D *h2w_effic_puptag_mass_nvtxg =(TH1D*) h2w_rebin_Effic_puptag_mass_nvtxg->Clone();
  // h2w_effic_puptag_mass_nvtxg->Reset();
  h2w_effic_puptag_mass_nvtxg->Divide( h2w_rebin_Effic_puptag_mass_nvtxg, h2w_rebin_Effic_Denom_nvtxg,1,1,"B");

  TH1D *h2w_effic_puptag_t_nvtxg =(TH1D*) h2w_rebin_Effic_puptag_t_nvtxg->Clone();
  // h2w_effic_puptag_t_nvtxg->Reset();
  h2w_effic_puptag_t_nvtxg->Divide( h2w_rebin_Effic_puptag_t_nvtxg, h2w_rebin_Effic_Denom_nvtxg,1,1,"B");


  TH1D *h2w_effic_chstag_tau32_nvtxg =(TH1D*) h2w_rebin_Effic_chstag_tau32_nvtxg->Clone();
  // h2w_effic_chstag_tau32_nvtxg->Reset();
  h2w_effic_chstag_tau32_nvtxg->Divide( h2w_rebin_Effic_chstag_tau32_nvtxg, h2w_rebin_Effic_Denom_nvtxg,1,1,"B");

  TH1D *h2w_effic_chstag_mass_nvtxg =(TH1D*) h2w_rebin_Effic_chstag_mass_nvtxg->Clone();
  // h2w_effic_chstag_mass_nvtxg->Reset();
  h2w_effic_chstag_mass_nvtxg->Divide( h2w_rebin_Effic_chstag_mass_nvtxg, h2w_rebin_Effic_Denom_nvtxg,1,1,"B");

  TH1D *h2w_effic_chstag_t_nvtxg =(TH1D*) h2w_rebin_Effic_chstag_t_nvtxg->Clone();
  // h2w_effic_chstag_t_nvtxg->Reset();
  h2w_effic_chstag_t_nvtxg->Divide( h2w_rebin_Effic_chstag_t_nvtxg, h2w_rebin_Effic_Denom_nvtxg,1,1,"B");

  h2w_effic_puptag_tau32_nvtxg ->SetMarkerStyle(20);        
  h2w_effic_puptag_mass_nvtxg  ->SetMarkerStyle(21);       
  h2w_effic_puptag_t_nvtxg     ->SetMarkerStyle(22);

  h2w_effic_chstag_tau32_nvtxg ->SetMarkerStyle(24);        
  h2w_effic_chstag_mass_nvtxg  ->SetMarkerStyle(25);       
  h2w_effic_chstag_t_nvtxg     ->SetMarkerStyle(26);

  h2w_effic_puptag_tau32_nvtxg ->SetMarkerColor(6);              
  h2w_effic_puptag_mass_nvtxg  ->SetMarkerColor(kBlue);         
  h2w_effic_puptag_t_nvtxg     ->SetMarkerColor(kOrange+1);

  h2w_effic_chstag_tau32_nvtxg ->SetMarkerColor(6);        
  h2w_effic_chstag_mass_nvtxg  ->SetMarkerColor(kBlue);       
  h2w_effic_chstag_t_nvtxg     ->SetMarkerColor(kOrange+1);

  h2w_effic_puptag_tau32_nvtxg ->SetLineColor(6);           
  h2w_effic_puptag_mass_nvtxg  ->SetLineColor(kBlue);      
  h2w_effic_puptag_t_nvtxg     ->SetLineColor(kOrange+1);

  h2w_effic_chstag_tau32_nvtxg ->SetLineColor(6);           
  h2w_effic_chstag_mass_nvtxg  ->SetLineColor(kBlue);      
  h2w_effic_chstag_t_nvtxg     ->SetLineColor(kOrange+1);

  h2w_effic_puptag_tau32_nvtxg ->SetLineWidth(2);   
  h2w_effic_puptag_mass_nvtxg  ->SetLineWidth(2);  
  h2w_effic_puptag_t_nvtxg     ->SetLineWidth(2);

  h2w_effic_chstag_tau32_nvtxg ->SetLineWidth(2);   
  h2w_effic_chstag_mass_nvtxg  ->SetLineWidth(2);  
  h2w_effic_chstag_t_nvtxg     ->SetLineWidth(2);




  h2w_effic_puptag_tau32_nvtxg->SetTitle(title.c_str());

  h2w_effic_puptag_tau32_nvtxg->SetStats(0);


  h2w_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleSize(0.065);
  h2w_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleOffset(0.9); 
  h2w_effic_puptag_tau32_nvtxg->GetYaxis()->SetLabelSize(0.06);

  h2w_effic_puptag_tau32_nvtxg->GetXaxis()->SetNdivisions(506);
  h2w_effic_puptag_tau32_nvtxg->GetXaxis()->SetLabelFont(42);
  h2w_effic_puptag_tau32_nvtxg->GetXaxis()->SetLabelSize(0.05);
  h2w_effic_puptag_tau32_nvtxg->GetXaxis()->SetTitleSize(0.056);
  h2w_effic_puptag_tau32_nvtxg->GetXaxis()->SetTickLength(0.045);
  h2w_effic_puptag_tau32_nvtxg->GetXaxis()->SetTitleOffset(1.15);
  h2w_effic_puptag_tau32_nvtxg->GetXaxis()->SetTitleFont(42);

  h2w_effic_puptag_tau32_nvtxg->GetYaxis()->SetNdivisions(506);
  h2w_effic_puptag_tau32_nvtxg->GetYaxis()->SetLabelFont(42);
  h2w_effic_puptag_tau32_nvtxg->GetYaxis()->SetLabelSize(0.05);
  h2w_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleSize(0.06125);
  h2w_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleOffset(1.17);
  h2w_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleFont(42);

  h2w_effic_puptag_tau32_nvtxg->GetZaxis()->SetLabelFont(42);
  h2w_effic_puptag_tau32_nvtxg->GetZaxis()->SetLabelSize(0.0425);
  h2w_effic_puptag_tau32_nvtxg->GetZaxis()->SetTitleSize(0.0475);
  h2w_effic_puptag_tau32_nvtxg->GetZaxis()->SetTitleFont(42);

  h2w_effic_puptag_tau32_nvtxg->GetYaxis()->SetRangeUser(0.0,1.1);
  h2w_effic_puptag_tau32_nvtxg ->Draw("");
  h2w_effic_puptag_mass_nvtxg  ->Draw("same");         
  h2w_effic_puptag_t_nvtxg     ->Draw("same");      

  h2w_effic_chstag_tau32_nvtxg ->Draw("same");
  h2w_effic_chstag_mass_nvtxg  ->Draw("same");         
  h2w_effic_chstag_t_nvtxg     ->Draw("same");      





  TLegend * h2w_leg;
  h2w_leg = new TLegend( 0.58, 0.6,0.95, 0.88);  //( 0.56, 0.69,0.98, 0.89);
  h2w_leg->SetBorderSize(0);
  h2w_leg->SetFillColor(0);
  h2w_leg->SetFillStyle(4000);
  h2w_leg->SetTextSize(0.04);   //0.038
  h2w_leg->SetMargin(0.18 );
  //h2w_leg->SetHeader("Medium t-tag - tt weight");
  if (forPUPPIpaper) h2w_leg->AddEntry((TObject*)0, "Anti-k_{T}, R=0.8", "");
  h2w_leg->AddEntry( h2w_effic_chstag_mass_nvtxg    , "CHS: m_{SD} tag"            , "LP" );
  h2w_leg->AddEntry( h2w_effic_chstag_tau32_nvtxg   , "CHS: #tau_{32} tag"         , "LP" );
  h2w_leg->AddEntry( h2w_effic_chstag_t_nvtxg       , "CHS: m_{SD}+#tau_{32} tag"  , "LP" );
  
  h2w_leg->AddEntry( h2w_effic_puptag_mass_nvtxg    , "PUPPI: m_{SD} tag"                     , "LP" );
  h2w_leg->AddEntry( h2w_effic_puptag_tau32_nvtxg   , "PUPPI: #tau_{32} tag"                  , "LP" );
  h2w_leg->AddEntry( h2w_effic_puptag_t_nvtxg       , "PUPPI: m_{SD}+#tau_{32} tag"           , "LP" );
  h2w_leg->Draw("same");

  TLatex *   h2w_tex = new TLatex(0.18,0.83,"#font[62]{CMS}");// #font[52]{Simulation Preliminary}");
  h2w_tex->SetNDC();
  h2w_tex->SetTextFont(42);
  h2w_tex->SetTextSize(0.0555); //0.0625
  h2w_tex->SetLineWidth(2);
  h2w_tex->Draw();
  h2w_tex = new TLatex(0.18,0.75,Form("#font[52]{#splitline{Simulation}{%s}}",CMSsubtext.c_str()));
  h2w_tex->SetNDC();
  h2w_tex->SetTextFont(42);
  h2w_tex->SetTextSize(0.05); //0.0625
  h2w_tex->SetLineWidth(2);
  h2w_tex->Draw();
  h2w_tex = new TLatex(0.96,0.936,"13 TeV");
  h2w_tex->SetNDC();
  h2w_tex->SetTextAlign(31);
  h2w_tex->SetTextFont(42);
  h2w_tex->SetTextSize(0.0575);
  h2w_tex->SetLineWidth(2);
  h2w_tex->Draw();
  
  
  c1237->SaveAs(Form("./plotEfficTest_WPABC/h2w_effic_tau32_nvtxg_WPB%s.pdf",endlabel.c_str()));

  //---------------------------------------------------------------------------------------------------------------------------



  TH1D *    h3w_Effic_Denom_pup0P                           = (TH1D *) fTop3w->Get( "h_Effic_Denom_pup0P"                            );
  TH1D *    h3w_Effic_Denom_jet0P                           = (TH1D *) fTop3w->Get( "h_Effic_Denom_jet0P"                            );
  TH1D *    h3w_Effic_Denom_jet0Y                           = (TH1D *) fTop3w->Get( "h_Effic_Denom_jet0Y"                            );
  TH1D *    h3w_Effic_Denom_nvtxg                           = (TH1D *) fTop3w->Get( "h_Effic_Denom_nvtxg"                            );
  TH1D *    h3w_Effic_Denom_jet0P_TopMatch                  = (TH1D *) fTop3w->Get( "h_Effic_Denom_jet0P_TopMatch"                   );
  TH1D *    h3w_Effic_Denom_jet0P_TopMatch_TopDist          = (TH1D *) fTop3w->Get( "h_Effic_Denom_jet0P_TopMatch_TopDist"           );
  TH1D *    h3w_Effic_puptag_tau32_pup0P                    = (TH1D *) fTop3w->Get( "h_Effic_puptag_tau32_pup0P"                     );
  TH1D *    h3w_Effic_puptag_tau32_jet0P                    = (TH1D *) fTop3w->Get( "h_Effic_puptag_tau32_jet0P"                     );
  TH1D *    h3w_Effic_puptag_tau32_jet0Y                    = (TH1D *) fTop3w->Get( "h_Effic_puptag_tau32_jet0Y"                     );
  TH1D *    h3w_Effic_puptag_tau32_nvtxg                    = (TH1D *) fTop3w->Get( "h_Effic_puptag_tau32_nvtxg"                     );
  TH1D *    h3w_Effic_puptag_tau32_jet0P_TopMatch           = (TH1D *) fTop3w->Get( "h_Effic_puptag_tau32_jet0P_TopMatch"            );
  TH1D *    h3w_Effic_puptag_tau32_jet0P_TopMatch_TopDist   = (TH1D *) fTop3w->Get( "h_Effic_puptag_tau32_jet0P_TopMatch_TopDist"    );
  TH1D *    h3w_Effic_chstag_tau32_pup0P                    = (TH1D *) fTop3w->Get( "h_Effic_chstag_tau32_pup0P"                     );
  TH1D *    h3w_Effic_chstag_tau32_jet0P                    = (TH1D *) fTop3w->Get( "h_Effic_chstag_tau32_jet0P"                     );
  TH1D *    h3w_Effic_chstag_tau32_jet0Y                    = (TH1D *) fTop3w->Get( "h_Effic_chstag_tau32_jet0Y"                     );
  TH1D *    h3w_Effic_chstag_tau32_nvtxg                    = (TH1D *) fTop3w->Get( "h_Effic_chstag_tau32_nvtxg"                     );
  TH1D *    h3w_Effic_chstag_tau32_jet0P_TopMatch           = (TH1D *) fTop3w->Get( "h_Effic_chstag_tau32_jet0P_TopMatch"            );
  TH1D *    h3w_Effic_chstag_tau32_jet0P_TopMatch_TopDist   = (TH1D *) fTop3w->Get( "h_Effic_chstag_tau32_jet0P_TopMatch_TopDist"    );
  TH1D *    h3w_Effic_puptag_mass_pup0P                     = (TH1D *) fTop3w->Get( "h_Effic_puptag_mass_pup0P"                      );
  TH1D *    h3w_Effic_puptag_mass_jet0P                     = (TH1D *) fTop3w->Get( "h_Effic_puptag_mass_jet0P"                      );
  TH1D *    h3w_Effic_puptag_mass_jet0Y                     = (TH1D *) fTop3w->Get( "h_Effic_puptag_mass_jet0Y"                      );
  TH1D *    h3w_Effic_puptag_mass_nvtxg                     = (TH1D *) fTop3w->Get( "h_Effic_puptag_mass_nvtxg"                      );
  TH1D *    h3w_Effic_puptag_mass_jet0P_TopMatch            = (TH1D *) fTop3w->Get( "h_Effic_puptag_mass_jet0P_TopMatch"             );
  TH1D *    h3w_Effic_puptag_mass_jet0P_TopMatch_TopDist    = (TH1D *) fTop3w->Get( "h_Effic_puptag_mass_jet0P_TopMatch_TopDist"     );
  TH1D *    h3w_Effic_chstag_mass_pup0P                     = (TH1D *) fTop3w->Get( "h_Effic_chstag_mass_pup0P"                      );
  TH1D *    h3w_Effic_chstag_mass_jet0P                     = (TH1D *) fTop3w->Get( "h_Effic_chstag_mass_jet0P"                      );
  TH1D *    h3w_Effic_chstag_mass_jet0Y                     = (TH1D *) fTop3w->Get( "h_Effic_chstag_mass_jet0Y"                      );
  TH1D *    h3w_Effic_chstag_mass_nvtxg                     = (TH1D *) fTop3w->Get( "h_Effic_chstag_mass_nvtxg"                      );
  TH1D *    h3w_Effic_chstag_mass_jet0P_TopMatch            = (TH1D *) fTop3w->Get( "h_Effic_chstag_mass_jet0P_TopMatch"             );
  TH1D *    h3w_Effic_chstag_mass_jet0P_TopMatch_TopDist    = (TH1D *) fTop3w->Get( "h_Effic_chstag_mass_jet0P_TopMatch_TopDist"     );
  TH1D *    h3w_Effic_puptag_t_pup0P                        = (TH1D *) fTop3w->Get( "h_Effic_puptag_t_pup0P"                         );
  TH1D *    h3w_Effic_puptag_t_jet0P                        = (TH1D *) fTop3w->Get( "h_Effic_puptag_t_jet0P"                         );
  TH1D *    h3w_Effic_puptag_t_jet0Y                        = (TH1D *) fTop3w->Get( "h_Effic_puptag_t_jet0Y"                         );
  TH1D *    h3w_Effic_puptag_t_nvtxg                        = (TH1D *) fTop3w->Get( "h_Effic_puptag_t_nvtxg"                         );
  TH1D *    h3w_Effic_puptag_t_jet0P_TopMatch               = (TH1D *) fTop3w->Get( "h_Effic_puptag_t_jet0P_TopMatch"                );
  TH1D *    h3w_Effic_puptag_t_jet0P_TopMatch_TopDist       = (TH1D *) fTop3w->Get( "h_Effic_puptag_t_jet0P_TopMatch_TopDist"        );
  TH1D *    h3w_Effic_chstag_t_pup0P                        = (TH1D *) fTop3w->Get( "h_Effic_chstag_t_pup0P"                         );
  TH1D *    h3w_Effic_chstag_t_jet0P                        = (TH1D *) fTop3w->Get( "h_Effic_chstag_t_jet0P"                         );
  TH1D *    h3w_Effic_chstag_t_jet0Y                        = (TH1D *) fTop3w->Get( "h_Effic_chstag_t_jet0Y"                         );
  TH1D *    h3w_Effic_chstag_t_nvtxg                        = (TH1D *) fTop3w->Get( "h_Effic_chstag_t_nvtxg"                         );
  TH1D *    h3w_Effic_chstag_t_jet0P_TopMatch               = (TH1D *) fTop3w->Get( "h_Effic_chstag_t_jet0P_TopMatch"                );
  TH1D *    h3w_Effic_chstag_t_jet0P_TopMatch_TopDist       = (TH1D *) fTop3w->Get( "h_Effic_chstag_t_jet0P_TopMatch_TopDist"        );




  TH1D *    h3w_new_Effic_Denom_pup0P                         = (TH1D*) h3w_Effic_Denom_pup0P                            ->Clone();  
  TH1D *    h3w_new_Effic_Denom_jet0P                         = (TH1D*) h3w_Effic_Denom_jet0P                            ->Clone();  
  TH1D *    h3w_new_Effic_Denom_jet0Y                         = (TH1D*) h3w_Effic_Denom_jet0Y                            ->Clone();  
  TH1D *    h3w_new_Effic_Denom_nvtxg                         = (TH1D*) h3w_Effic_Denom_nvtxg                            ->Clone();  
  TH1D *    h3w_new_Effic_Denom_jet0P_TopMatch                = (TH1D*) h3w_Effic_Denom_jet0P_TopMatch                   ->Clone();  
  TH1D *    h3w_new_Effic_Denom_jet0P_TopMatch_TopDist        = (TH1D*) h3w_Effic_Denom_jet0P_TopMatch_TopDist           ->Clone();  
  TH1D *    h3w_new_Effic_puptag_tau32_pup0P                  = (TH1D*) h3w_Effic_puptag_tau32_pup0P                     ->Clone();  
  TH1D *    h3w_new_Effic_puptag_tau32_jet0P                  = (TH1D*) h3w_Effic_puptag_tau32_jet0P                     ->Clone();  
  TH1D *    h3w_new_Effic_puptag_tau32_jet0Y                  = (TH1D*) h3w_Effic_puptag_tau32_jet0Y                     ->Clone();  
  TH1D *    h3w_new_Effic_puptag_tau32_nvtxg                  = (TH1D*) h3w_Effic_puptag_tau32_nvtxg                     ->Clone();  
  TH1D *    h3w_new_Effic_puptag_tau32_jet0P_TopMatch         = (TH1D*) h3w_Effic_puptag_tau32_jet0P_TopMatch            ->Clone();  
  TH1D *    h3w_new_Effic_puptag_tau32_jet0P_TopMatch_TopDist = (TH1D*) h3w_Effic_puptag_tau32_jet0P_TopMatch_TopDist    ->Clone();  
  TH1D *    h3w_new_Effic_chstag_tau32_pup0P                  = (TH1D*) h3w_Effic_chstag_tau32_pup0P                     ->Clone();  
  TH1D *    h3w_new_Effic_chstag_tau32_jet0P                  = (TH1D*) h3w_Effic_chstag_tau32_jet0P                     ->Clone();  
  TH1D *    h3w_new_Effic_chstag_tau32_jet0Y                  = (TH1D*) h3w_Effic_chstag_tau32_jet0Y                     ->Clone();  
  TH1D *    h3w_new_Effic_chstag_tau32_nvtxg                  = (TH1D*) h3w_Effic_chstag_tau32_nvtxg                     ->Clone();  
  TH1D *    h3w_new_Effic_chstag_tau32_jet0P_TopMatch         = (TH1D*) h3w_Effic_chstag_tau32_jet0P_TopMatch            ->Clone();  
  TH1D *    h3w_new_Effic_chstag_tau32_jet0P_TopMatch_TopDist = (TH1D*) h3w_Effic_chstag_tau32_jet0P_TopMatch_TopDist    ->Clone();  
  TH1D *    h3w_new_Effic_puptag_mass_pup0P                   = (TH1D*) h3w_Effic_puptag_mass_pup0P                      ->Clone();  
  TH1D *    h3w_new_Effic_puptag_mass_jet0P                   = (TH1D*) h3w_Effic_puptag_mass_jet0P                      ->Clone();  
  TH1D *    h3w_new_Effic_puptag_mass_jet0Y                   = (TH1D*) h3w_Effic_puptag_mass_jet0Y                      ->Clone();  
  TH1D *    h3w_new_Effic_puptag_mass_nvtxg                   = (TH1D*) h3w_Effic_puptag_mass_nvtxg                      ->Clone();  
  TH1D *    h3w_new_Effic_puptag_mass_jet0P_TopMatch          = (TH1D*) h3w_Effic_puptag_mass_jet0P_TopMatch             ->Clone();  
  TH1D *    h3w_new_Effic_puptag_mass_jet0P_TopMatch_TopDist  = (TH1D*) h3w_Effic_puptag_mass_jet0P_TopMatch_TopDist     ->Clone();  
  TH1D *    h3w_new_Effic_chstag_mass_pup0P                   = (TH1D*) h3w_Effic_chstag_mass_pup0P                      ->Clone();  
  TH1D *    h3w_new_Effic_chstag_mass_jet0P                   = (TH1D*) h3w_Effic_chstag_mass_jet0P                      ->Clone();  
  TH1D *    h3w_new_Effic_chstag_mass_jet0Y                   = (TH1D*) h3w_Effic_chstag_mass_jet0Y                      ->Clone();  
  TH1D *    h3w_new_Effic_chstag_mass_nvtxg                   = (TH1D*) h3w_Effic_chstag_mass_nvtxg                      ->Clone();  
  TH1D *    h3w_new_Effic_chstag_mass_jet0P_TopMatch          = (TH1D*) h3w_Effic_chstag_mass_jet0P_TopMatch             ->Clone();  
  TH1D *    h3w_new_Effic_chstag_mass_jet0P_TopMatch_TopDist  = (TH1D*) h3w_Effic_chstag_mass_jet0P_TopMatch_TopDist     ->Clone();  
  TH1D *    h3w_new_Effic_puptag_t_pup0P                      = (TH1D*) h3w_Effic_puptag_t_pup0P                         ->Clone();  
  TH1D *    h3w_new_Effic_puptag_t_jet0P                      = (TH1D*) h3w_Effic_puptag_t_jet0P                         ->Clone();  
  TH1D *    h3w_new_Effic_puptag_t_jet0Y                      = (TH1D*) h3w_Effic_puptag_t_jet0Y                         ->Clone();  
  TH1D *    h3w_new_Effic_puptag_t_nvtxg                      = (TH1D*) h3w_Effic_puptag_t_nvtxg                         ->Clone();  
  TH1D *    h3w_new_Effic_puptag_t_jet0P_TopMatch             = (TH1D*) h3w_Effic_puptag_t_jet0P_TopMatch                ->Clone();  
  TH1D *    h3w_new_Effic_puptag_t_jet0P_TopMatch_TopDist     = (TH1D*) h3w_Effic_puptag_t_jet0P_TopMatch_TopDist        ->Clone();  
  TH1D *    h3w_new_Effic_chstag_t_pup0P                      = (TH1D*) h3w_Effic_chstag_t_pup0P                         ->Clone();  
  TH1D *    h3w_new_Effic_chstag_t_jet0P                      = (TH1D*) h3w_Effic_chstag_t_jet0P                         ->Clone();  
  TH1D *    h3w_new_Effic_chstag_t_jet0Y                      = (TH1D*) h3w_Effic_chstag_t_jet0Y                         ->Clone();  
  TH1D *    h3w_new_Effic_chstag_t_nvtxg                      = (TH1D*) h3w_Effic_chstag_t_nvtxg                         ->Clone();  
  TH1D *    h3w_new_Effic_chstag_t_jet0P_TopMatch             = (TH1D*) h3w_Effic_chstag_t_jet0P_TopMatch                ->Clone();  
  TH1D *    h3w_new_Effic_chstag_t_jet0P_TopMatch_TopDist     = (TH1D*) h3w_Effic_chstag_t_jet0P_TopMatch_TopDist        ->Clone();  

  TH1D * h3w_rebin_Effic_Denom_pup0P                          ;  
  TH1D * h3w_rebin_Effic_Denom_jet0P                          ;  
  TH1D * h3w_rebin_Effic_Denom_jet0Y                          ;  
  TH1D * h3w_rebin_Effic_Denom_nvtxg                          ;  
  TH1D * h3w_rebin_Effic_Denom_jet0P_TopMatch                 ;  
  TH1D * h3w_rebin_Effic_Denom_jet0P_TopMatch_TopDist         ;  
  TH1D * h3w_rebin_Effic_puptag_tau32_pup0P                   ;  
  TH1D * h3w_rebin_Effic_puptag_tau32_jet0P                   ;  
  TH1D * h3w_rebin_Effic_puptag_tau32_jet0Y                   ;  
  TH1D * h3w_rebin_Effic_puptag_tau32_nvtxg                   ;  
  TH1D * h3w_rebin_Effic_puptag_tau32_jet0P_TopMatch          ;  
  TH1D * h3w_rebin_Effic_puptag_tau32_jet0P_TopMatch_TopDist  ;  
  TH1D * h3w_rebin_Effic_chstag_tau32_pup0P                   ;  
  TH1D * h3w_rebin_Effic_chstag_tau32_jet0P                   ;  
  TH1D * h3w_rebin_Effic_chstag_tau32_jet0Y                   ;  
  TH1D * h3w_rebin_Effic_chstag_tau32_nvtxg                   ;  
  TH1D * h3w_rebin_Effic_chstag_tau32_jet0P_TopMatch          ;  
  TH1D * h3w_rebin_Effic_chstag_tau32_jet0P_TopMatch_TopDist  ;  
  TH1D * h3w_rebin_Effic_puptag_mass_pup0P                    ;  
  TH1D * h3w_rebin_Effic_puptag_mass_jet0P                    ;  
  TH1D * h3w_rebin_Effic_puptag_mass_jet0Y                    ;  
  TH1D * h3w_rebin_Effic_puptag_mass_nvtxg                    ;  
  TH1D * h3w_rebin_Effic_puptag_mass_jet0P_TopMatch           ;  
  TH1D * h3w_rebin_Effic_puptag_mass_jet0P_TopMatch_TopDist   ;  
  TH1D * h3w_rebin_Effic_chstag_mass_pup0P                    ;  
  TH1D * h3w_rebin_Effic_chstag_mass_jet0P                    ;  
  TH1D * h3w_rebin_Effic_chstag_mass_jet0Y                    ;  
  TH1D * h3w_rebin_Effic_chstag_mass_nvtxg                    ;  
  TH1D * h3w_rebin_Effic_chstag_mass_jet0P_TopMatch           ;  
  TH1D * h3w_rebin_Effic_chstag_mass_jet0P_TopMatch_TopDist   ;  
  TH1D * h3w_rebin_Effic_puptag_t_pup0P                       ;  
  TH1D * h3w_rebin_Effic_puptag_t_jet0P                       ;  
  TH1D * h3w_rebin_Effic_puptag_t_jet0Y                       ;  
  TH1D * h3w_rebin_Effic_puptag_t_nvtxg                       ;  
  TH1D * h3w_rebin_Effic_puptag_t_jet0P_TopMatch              ;  
  TH1D * h3w_rebin_Effic_puptag_t_jet0P_TopMatch_TopDist      ;  
  TH1D * h3w_rebin_Effic_chstag_t_pup0P                       ;  
  TH1D * h3w_rebin_Effic_chstag_t_jet0P                       ;  
  TH1D * h3w_rebin_Effic_chstag_t_jet0Y                       ;  
  TH1D * h3w_rebin_Effic_chstag_t_nvtxg                       ;  
  TH1D * h3w_rebin_Effic_chstag_t_jet0P_TopMatch              ;  
  TH1D * h3w_rebin_Effic_chstag_t_jet0P_TopMatch_TopDist      ;  



  h3w_rebin_Effic_Denom_nvtxg         = (TH1D*)h3w_new_Effic_Denom_nvtxg           ->Rebin(nbins_nvtx-1,"h3w_rebin_Effic_Denom_nvtxg"       ,xbins_nvtx);
  h3w_rebin_Effic_puptag_tau32_nvtxg  = (TH1D*)h3w_new_Effic_puptag_tau32_nvtxg    ->Rebin(nbins_nvtx-1,"h3w_rebin_Effic_puptag_tau32_nvtxg",xbins_nvtx);
  h3w_rebin_Effic_chstag_tau32_nvtxg  = (TH1D*)h3w_new_Effic_chstag_tau32_nvtxg    ->Rebin(nbins_nvtx-1,"h3w_rebin_Effic_chstag_tau32_nvtxg",xbins_nvtx);
  h3w_rebin_Effic_puptag_mass_nvtxg   = (TH1D*)h3w_new_Effic_puptag_mass_nvtxg     ->Rebin(nbins_nvtx-1,"h3w_rebin_Effic_puptag_mass_nvtxg" ,xbins_nvtx);
  h3w_rebin_Effic_chstag_mass_nvtxg   = (TH1D*)h3w_new_Effic_chstag_mass_nvtxg     ->Rebin(nbins_nvtx-1,"h3w_rebin_Effic_chstag_mass_nvtxg" ,xbins_nvtx);
  h3w_rebin_Effic_puptag_t_nvtxg      = (TH1D*)h3w_new_Effic_puptag_t_nvtxg        ->Rebin(nbins_nvtx-1,"h3w_rebin_Effic_puptag_t_nvtxg"    ,xbins_nvtx);
  h3w_rebin_Effic_chstag_t_nvtxg      = (TH1D*)h3w_new_Effic_chstag_t_nvtxg        ->Rebin(nbins_nvtx-1,"h3w_rebin_Effic_chstag_t_nvtxg"    ,xbins_nvtx);

  h3w_Effic_Denom_pup0P                          ->Rebin(10);
  h3w_Effic_Denom_jet0P                          ->Rebin(10);
  h3w_Effic_Denom_jet0Y                          ->Rebin(10);
  h3w_Effic_Denom_jet0P_TopMatch                 ->Rebin(10);
  h3w_Effic_Denom_jet0P_TopMatch_TopDist         ->Rebin(10);
  h3w_Effic_puptag_tau32_pup0P                   ->Rebin(10);
  h3w_Effic_puptag_tau32_jet0P                   ->Rebin(10);
  h3w_Effic_puptag_tau32_jet0Y                   ->Rebin(10);
  h3w_Effic_puptag_tau32_jet0P_TopMatch          ->Rebin(10);
  h3w_Effic_puptag_tau32_jet0P_TopMatch_TopDist  ->Rebin(10);
  h3w_Effic_chstag_tau32_pup0P                   ->Rebin(10);
  h3w_Effic_chstag_tau32_jet0P                   ->Rebin(10);
  h3w_Effic_chstag_tau32_jet0Y                   ->Rebin(10);
  h3w_Effic_chstag_tau32_jet0P_TopMatch          ->Rebin(10);
  h3w_Effic_chstag_tau32_jet0P_TopMatch_TopDist  ->Rebin(10);
  h3w_Effic_puptag_mass_pup0P                    ->Rebin(10);
  h3w_Effic_puptag_mass_jet0P                    ->Rebin(10);
  h3w_Effic_puptag_mass_jet0Y                    ->Rebin(10);
  h3w_Effic_puptag_mass_jet0P_TopMatch           ->Rebin(10);
  h3w_Effic_puptag_mass_jet0P_TopMatch_TopDist   ->Rebin(10);
  h3w_Effic_chstag_mass_pup0P                    ->Rebin(10);
  h3w_Effic_chstag_mass_jet0P                    ->Rebin(10);
  h3w_Effic_chstag_mass_jet0Y                    ->Rebin(10);
  h3w_Effic_chstag_mass_jet0P_TopMatch           ->Rebin(10);
  h3w_Effic_chstag_mass_jet0P_TopMatch_TopDist   ->Rebin(10);
  h3w_Effic_puptag_t_pup0P                       ->Rebin(10);
  h3w_Effic_puptag_t_jet0P                       ->Rebin(10);
  h3w_Effic_puptag_t_jet0Y                       ->Rebin(10);
  h3w_Effic_puptag_t_jet0P_TopMatch              ->Rebin(10);
  h3w_Effic_puptag_t_jet0P_TopMatch_TopDist      ->Rebin(10);
  h3w_Effic_chstag_t_pup0P                       ->Rebin(10);
  h3w_Effic_chstag_t_jet0P                       ->Rebin(10);
  h3w_Effic_chstag_t_jet0Y                       ->Rebin(10);
  h3w_Effic_chstag_t_jet0P_TopMatch              ->Rebin(10);
  h3w_Effic_chstag_t_jet0P_TopMatch_TopDist      ->Rebin(10);


  // TH1D *effic_tau32_pup0P =(TH1D*) h3w_Effic_puptag_tau32_pup0P->Clone();
  // // effic_tau32_pup0P->Reset();
  // effic_tau32_pup0P->Divide( h3w_Effic_puptag_tau32_pup0P, h3w_Effic_Denom_pup0P,1,1,"B");

  // TH1D *effic_tau32_jet0P =(TH1D*) h3w_Effic_puptag_tau32_jet0P->Clone();
  // // effic_tau32_jet0P->Reset();
  // effic_tau32_jet0P->Divide( h3w_Effic_puptag_tau32_jet0P, h3w_Effic_Denom_jet0P,1,1,"B");

  // TH1D *effic_chstag_tau32_jet0P =(TH1D*) h3w_Effic_chstag_tau32_jet0P->Clone();
  // // effic_chstag_tau32_jet0P->Reset();
  // effic_chstag_tau32_jet0P->Divide( h3w_Effic_chstag_tau32_jet0P, h3w_Effic_Denom_jet0P,1,1,"B");


  // TH1D *effic_mass_jet0P =(TH1D*) h3w_Effic_puptag_mass_jet0P->Clone();
  // // effic_mass_jet0P->Reset();
  // effic_mass_jet0P->Divide( h3w_Effic_puptag_mass_jet0P, h3w_Effic_Denom_jet0P,1,1,"B");

  // TH1D *effic_t_jet0P =(TH1D*) h3w_Effic_puptag_t_jet0P->Clone();
  // // effic_t_jet0P->Reset();
  // effic_t_jet0P->Divide( h3w_Effic_puptag_t_jet0P, h3w_Effic_Denom_jet0P,1,1,"B");

  // effic_tau32_pup0P ->SetLineColor(2);    
  // effic_tau32_jet0P ->SetLineColor(3);        
  // effic_mass_jet0P  ->SetLineColor(4);       
  // effic_t_jet0P     ->SetLineColor(5);
  // effic_chstag_tau32_jet0P->SetLineColor(6);

  // effic_tau32_pup0P->GetXaxis()->SetRangeUser(300,4000);
  // effic_tau32_pup0P ->Draw("HIST");          
  // effic_tau32_jet0P ->Draw("HISTsame");
  // effic_chstag_tau32_jet0P  ->Draw("HISTsame");         
  // effic_mass_jet0P  ->Draw("HISTsame");         
  // effic_t_jet0P     ->Draw("HISTsame");      
  // c1237->SaveAs("./plotsEfficTest/effic_tau32_pup0P.pdf");

  // cout<<"h3w_Effic_puptag_tau32_jet0P_TopMatch "<<h3w_Effic_puptag_tau32_jet0P_TopMatch->Integral()<<endl;
  // cout<<"h3w_Effic_Denom_jet0P_TopMatch "<<h3w_Effic_Denom_jet0P_TopMatch->Integral()<<endl;

  // cout<<"h3w_Effic_puptag_tau32_jet0P_TopMatch_TopDist "<<h3w_Effic_puptag_tau32_jet0P_TopMatch_TopDist->Integral()<<endl;
  // cout<<"h3w_Effic_Denom_jet0P_TopMatch_TopDist "<<h3w_Effic_Denom_jet0P_TopMatch_TopDist->Integral()<<endl;


  // TH1D *effic_puptag_tau32_jet0P_TopMatch =(TH1D*) h3w_Effic_puptag_tau32_jet0P_TopMatch->Clone();
  // effic_puptag_tau32_jet0P_TopMatch->Reset();
  // effic_puptag_tau32_jet0P_TopMatch->Divide( h3w_Effic_puptag_tau32_jet0P_TopMatch, h3w_Effic_Denom_jet0P_TopMatch,1,1,"B");

  // TH1D *effic_puptag_tau32_jet0P_TopMatch_TopDist =(TH1D*) h3w_Effic_puptag_tau32_jet0P_TopMatch_TopDist->Clone();
  // effic_puptag_tau32_jet0P_TopMatch_TopDist->Reset();
  // effic_puptag_tau32_jet0P_TopMatch_TopDist->Divide( h3w_Effic_puptag_tau32_jet0P_TopMatch_TopDist, h3w_Effic_Denom_jet0P_TopMatch_TopDist,1,1,"B");

  // effic_puptag_tau32_jet0P_TopMatch         ->SetLineColor(1);
  // effic_puptag_tau32_jet0P_TopMatch_TopDist->SetLineColor(2);

  // effic_puptag_tau32_jet0P_TopMatch_TopDist->GetXaxis()->SetRangeUser(300,4000);
  // effic_puptag_tau32_jet0P_TopMatch_TopDist ->Draw("HIST");          
  // effic_puptag_tau32_jet0P_TopMatch ->Draw("HISTsame");    
  // c1237->SaveAs("./plotsEfficTest/effic_match.pdf");





  TH1D *h3w_effic_puptag_tau32_nvtxg =(TH1D*) h3w_rebin_Effic_puptag_tau32_nvtxg->Clone();
  // h3w_effic_puptag_tau32_nvtxg->Reset();
  h3w_effic_puptag_tau32_nvtxg->Divide( h3w_rebin_Effic_puptag_tau32_nvtxg, h3w_rebin_Effic_Denom_nvtxg,1,1,"B");

  TH1D *h3w_effic_puptag_mass_nvtxg =(TH1D*) h3w_rebin_Effic_puptag_mass_nvtxg->Clone();
  // h3w_effic_puptag_mass_nvtxg->Reset();
  h3w_effic_puptag_mass_nvtxg->Divide( h3w_rebin_Effic_puptag_mass_nvtxg, h3w_rebin_Effic_Denom_nvtxg,1,1,"B");

  TH1D *h3w_effic_puptag_t_nvtxg =(TH1D*) h3w_rebin_Effic_puptag_t_nvtxg->Clone();
  // h3w_effic_puptag_t_nvtxg->Reset();
  h3w_effic_puptag_t_nvtxg->Divide( h3w_rebin_Effic_puptag_t_nvtxg, h3w_rebin_Effic_Denom_nvtxg,1,1,"B");


  TH1D *h3w_effic_chstag_tau32_nvtxg =(TH1D*) h3w_rebin_Effic_chstag_tau32_nvtxg->Clone();
  // h3w_effic_chstag_tau32_nvtxg->Reset();
  h3w_effic_chstag_tau32_nvtxg->Divide( h3w_rebin_Effic_chstag_tau32_nvtxg, h3w_rebin_Effic_Denom_nvtxg,1,1,"B");

  TH1D *h3w_effic_chstag_mass_nvtxg =(TH1D*) h3w_rebin_Effic_chstag_mass_nvtxg->Clone();
  // h3w_effic_chstag_mass_nvtxg->Reset();
  h3w_effic_chstag_mass_nvtxg->Divide( h3w_rebin_Effic_chstag_mass_nvtxg, h3w_rebin_Effic_Denom_nvtxg,1,1,"B");

  TH1D *h3w_effic_chstag_t_nvtxg =(TH1D*) h3w_rebin_Effic_chstag_t_nvtxg->Clone();
  // h3w_effic_chstag_t_nvtxg->Reset();
  h3w_effic_chstag_t_nvtxg->Divide( h3w_rebin_Effic_chstag_t_nvtxg, h3w_rebin_Effic_Denom_nvtxg,1,1,"B");

  h3w_effic_puptag_tau32_nvtxg ->SetMarkerStyle(20);        
  h3w_effic_puptag_mass_nvtxg  ->SetMarkerStyle(21);       
  h3w_effic_puptag_t_nvtxg     ->SetMarkerStyle(22);

  h3w_effic_chstag_tau32_nvtxg ->SetMarkerStyle(24);        
  h3w_effic_chstag_mass_nvtxg  ->SetMarkerStyle(25);       
  h3w_effic_chstag_t_nvtxg     ->SetMarkerStyle(26);

  h3w_effic_puptag_tau32_nvtxg ->SetMarkerColor(6);              
  h3w_effic_puptag_mass_nvtxg  ->SetMarkerColor(kBlue);         
  h3w_effic_puptag_t_nvtxg     ->SetMarkerColor(kOrange+1);

  h3w_effic_chstag_tau32_nvtxg ->SetMarkerColor(6);        
  h3w_effic_chstag_mass_nvtxg  ->SetMarkerColor(kBlue);       
  h3w_effic_chstag_t_nvtxg     ->SetMarkerColor(kOrange+1);

  h3w_effic_puptag_tau32_nvtxg ->SetLineColor(6);           
  h3w_effic_puptag_mass_nvtxg  ->SetLineColor(kBlue);      
  h3w_effic_puptag_t_nvtxg     ->SetLineColor(kOrange+1);

  h3w_effic_chstag_tau32_nvtxg ->SetLineColor(6);           
  h3w_effic_chstag_mass_nvtxg  ->SetLineColor(kBlue);      
  h3w_effic_chstag_t_nvtxg     ->SetLineColor(kOrange+1);

  h3w_effic_puptag_tau32_nvtxg ->SetLineWidth(2);   
  h3w_effic_puptag_mass_nvtxg  ->SetLineWidth(2);  
  h3w_effic_puptag_t_nvtxg     ->SetLineWidth(2);

  h3w_effic_chstag_tau32_nvtxg ->SetLineWidth(2);   
  h3w_effic_chstag_mass_nvtxg  ->SetLineWidth(2);  
  h3w_effic_chstag_t_nvtxg     ->SetLineWidth(2);




  h3w_effic_puptag_tau32_nvtxg->SetTitle(title.c_str());

  h3w_effic_puptag_tau32_nvtxg->SetStats(0);


  h3w_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleSize(0.065);
  h3w_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleOffset(0.9); 
  h3w_effic_puptag_tau32_nvtxg->GetYaxis()->SetLabelSize(0.06);

  h3w_effic_puptag_tau32_nvtxg->GetXaxis()->SetNdivisions(506);
  h3w_effic_puptag_tau32_nvtxg->GetXaxis()->SetLabelFont(42);
  h3w_effic_puptag_tau32_nvtxg->GetXaxis()->SetLabelSize(0.05);
  h3w_effic_puptag_tau32_nvtxg->GetXaxis()->SetTitleSize(0.056);
  h3w_effic_puptag_tau32_nvtxg->GetXaxis()->SetTickLength(0.045);
  h3w_effic_puptag_tau32_nvtxg->GetXaxis()->SetTitleOffset(1.15);
  h3w_effic_puptag_tau32_nvtxg->GetXaxis()->SetTitleFont(42);

  h3w_effic_puptag_tau32_nvtxg->GetYaxis()->SetNdivisions(506);
  h3w_effic_puptag_tau32_nvtxg->GetYaxis()->SetLabelFont(42);
  h3w_effic_puptag_tau32_nvtxg->GetYaxis()->SetLabelSize(0.05);
  h3w_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleSize(0.06125);
  h3w_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleOffset(1.17);
  h3w_effic_puptag_tau32_nvtxg->GetYaxis()->SetTitleFont(42);

  h3w_effic_puptag_tau32_nvtxg->GetZaxis()->SetLabelFont(42);
  h3w_effic_puptag_tau32_nvtxg->GetZaxis()->SetLabelSize(0.0425);
  h3w_effic_puptag_tau32_nvtxg->GetZaxis()->SetTitleSize(0.0475);
  h3w_effic_puptag_tau32_nvtxg->GetZaxis()->SetTitleFont(42);

  h3w_effic_puptag_tau32_nvtxg->GetYaxis()->SetRangeUser(0.0,1.1);
  h3w_effic_puptag_tau32_nvtxg ->Draw("");
  h3w_effic_puptag_mass_nvtxg  ->Draw("same");         
  h3w_effic_puptag_t_nvtxg     ->Draw("same");      

  h3w_effic_chstag_tau32_nvtxg ->Draw("same");
  h3w_effic_chstag_mass_nvtxg  ->Draw("same");         
  h3w_effic_chstag_t_nvtxg     ->Draw("same");      





  TLegend * h3w_leg;
  h3w_leg = new TLegend( 0.58, 0.6,0.95, 0.88);  //( 0.56, 0.69,0.98, 0.89);
  h3w_leg->SetBorderSize(0);
  h3w_leg->SetFillColor(0);
  h3w_leg->SetFillStyle(4000);
  h3w_leg->SetTextSize(0.04);   //0.038
  h3w_leg->SetMargin(0.18 );
  //h3w_leg->SetHeader("Tight t-tag - tt weight");
  h3w_leg->AddEntry( h3w_effic_chstag_mass_nvtxg    , "CHS: m_{SD} tag"            , "LP" );
  h3w_leg->AddEntry( h3w_effic_chstag_tau32_nvtxg   , "CHS: #tau_{32} tag"         , "LP" );
  h3w_leg->AddEntry( h3w_effic_chstag_t_nvtxg       , "CHS: m_{SD}+#tau_{32} tag"  , "LP" );
  
  h3w_leg->AddEntry( h3w_effic_puptag_mass_nvtxg    , "PUPPI: m_{SD} tag"                     , "LP" );
  h3w_leg->AddEntry( h3w_effic_puptag_tau32_nvtxg   , "PUPPI: #tau_{32} tag"                  , "LP" );
  h3w_leg->AddEntry( h3w_effic_puptag_t_nvtxg       , "PUPPI: m_{SD}+#tau_{32} tag"           , "LP" );
  h3w_leg->Draw("same");

  TLatex *   h3w_tex = new TLatex(0.18,0.83,"#font[62]{CMS}");// #font[52]{Simulation Preliminary}");
  h3w_tex->SetNDC();
  h3w_tex->SetTextFont(42);
  h3w_tex->SetTextSize(0.0555); //0.0625
  h3w_tex->SetLineWidth(2);
  h3w_tex->Draw();
  h3w_tex = new TLatex(0.18,0.77,Form("#font[52]{#splitline{Simulation}{%s}}",CMSsubtext.c_str()));
  h3w_tex->SetNDC();
  h3w_tex->SetTextFont(42);
  h3w_tex->SetTextSize(0.05); //0.0625
  h3w_tex->SetLineWidth(2);
  h3w_tex->Draw();
  h3w_tex = new TLatex(0.96,0.936,"13 TeV");
  h3w_tex->SetNDC();
  h3w_tex->SetTextAlign(31);
  h3w_tex->SetTextFont(42);
  h3w_tex->SetTextSize(0.0575);
  h3w_tex->SetLineWidth(2);
  h3w_tex->Draw();
  

  c1237->SaveAs(Form("./plotEfficTest_WPABC/h3w_effic_tau32_nvtxg_WPC%s.pdf",endlabel.c_str()));

  //----------------------------------





}
