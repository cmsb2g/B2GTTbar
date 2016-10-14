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
#include <TStyle.h>

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <cmath>

using namespace std;
void run(){
    gROOT->SetBatch(); 
    
    const double lumi = 27220 ; // pb-1

    vector<string> hists_names;
    vector<string> modmass_hists_names;

    // hists_names.push_back("mttPredDist2_modMass_tagMassSDTau32_dRapHi_0btag_pred");
    hists_names.push_back("h_DijetMass_dRapIn");  
    hists_names.push_back("h_DijetMass_dRapLo");  
    hists_names.push_back("h_DijetMass_dRapHi");  
    hists_names.push_back("h_2ttag_inclu_dRapIn_DijetMass");  
    hists_names.push_back("h_2ttag_0btag_dRapIn_DijetMass");  
    hists_names.push_back("h_2ttag_1btag_dRapIn_DijetMass");  
    hists_names.push_back("h_2ttag_2btag_dRapIn_DijetMass");  
    hists_names.push_back("h_2ttag_inclu_dRapLo_DijetMass");  
    hists_names.push_back("h_2ttag_0btag_dRapLo_DijetMass");  
    hists_names.push_back("h_2ttag_1btag_dRapLo_DijetMass");  
    hists_names.push_back("h_2ttag_2btag_dRapLo_DijetMass");  
    hists_names.push_back("h_2ttag_inclu_dRapHi_DijetMass");  
    hists_names.push_back("h_2ttag_0btag_dRapHi_DijetMass");  
    hists_names.push_back("h_2ttag_1btag_dRapHi_DijetMass");  
    hists_names.push_back("h_2ttag_2btag_dRapHi_DijetMass");  
    hists_names.push_back("h_DeltaRap");          
    hists_names.push_back("h_DeltaPhi");          
    hists_names.push_back("h_Jet0Pt");
    hists_names.push_back("h_Jet0Rap");
    hists_names.push_back("h_Jet1Pt");
    hists_names.push_back("h_Jet1Rap");
    hists_names.push_back("h_HT");                
    hists_names.push_back("h_MET");               
    hists_names.push_back("h_METphi");            
    hists_names.push_back("h_Nvtx");              
    hists_names.push_back("h_Jet0SDmass");                                   
    hists_names.push_back("h_Jet0SDmass_JetTag_b");                             
    hists_names.push_back("h_Jet0SDmass_JetTag_tau32");                         
    hists_names.push_back("h_Jet0SDmass_JetTag_b_tau32");                       
    hists_names.push_back("h_Jet0SDmass_OppositeJetTag_t_b");                   
    hists_names.push_back("h_Jet0SDmass_OppositeJetTag_t_b_JetTag_b");          
    hists_names.push_back("h_Jet0SDmass_OppositeJetTag_t_b_JetTag_b_tau32");    
    hists_names.push_back("h_JetSDmass");                                   
    hists_names.push_back("h_JetSDmass_JetTag_b");                             
    hists_names.push_back("h_JetSDmass_JetTag_tau32");                         
    hists_names.push_back("h_JetSDmass_JetTag_b_tau32");                       
    hists_names.push_back("h_JetSDmass_OppositeJetTag_t_b");                   
    hists_names.push_back("h_JetSDmass_OppositeJetTag_t_b_JetTag_b");          
    hists_names.push_back("h_JetSDmass_OppositeJetTag_t_b_JetTag_b_tau32"); 

    hists_names.push_back("h_JetTau32");                                 
    hists_names.push_back("h_JetTau32_JetTag_b");                        
    hists_names.push_back("h_JetTau32_JetTag_mass");                     
    hists_names.push_back("h_JetTau32_JetTag_b_mass");                   
    hists_names.push_back("h_JetTau32_OppositeJetTag_t_b");              
    hists_names.push_back("h_JetTau32_OppositeJetTag_t_b_JetTag_b");     
    hists_names.push_back("h_JetTau32_OppositeJetTag_t_b_JetTag_b_mass");

    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_inclusive");            
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_0btag");                
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_1btag");                
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_2btag");                
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_inclusive");            
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_0btag");                
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_1btag");                
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_2btag");                
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_inclusive");            
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_0btag");                
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_1btag");                
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_2btag");                
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_inclusive");   
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_0btag");       
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_1btag");       
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_2btag");       
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_inclusive");   
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_0btag");       
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_1btag");       
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_2btag");       
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_inclusive");   
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_0btag");       
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_1btag");       
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_2btag");       

    //Modmass distributions
    modmass_hists_names.push_back("h_mAK8_ModMass");
    modmass_hists_names.push_back("h_mAK8_ModMass_jet0");
    modmass_hists_names.push_back("h_mAK8_ModMass_jet1");

    modmass_hists_names.push_back("h_mSDropAK8_ModMass");
    modmass_hists_names.push_back("h_mSDropAK8_ModMass_jet0");
    modmass_hists_names.push_back("h_mSDropAK8_ModMass_jet1");

    modmass_hists_names.push_back("h_mPuppiSDropAK8_ModMass");
    modmass_hists_names.push_back("h_mPuppiSDropAK8_ModMass_jet0");
    modmass_hists_names.push_back("h_mPuppiSDropAK8_ModMass_jet1");

    TFile * OutFile = new TFile("runs/run20161010/histsAllHad_Jetpt600HT1000_20161010_b2gtree_QCD_Pt_300toInf_pythia8_RunIISpring16MiniAODv2_reHLT_V3.root" , "RECREATE");
	
    TFile * fQCD1  = new TFile("runs/run20161010/histsAllHad_Jetpt600HT1000_20161010_b2gtree_QCD_Pt_300to470_pythia8_RunIISpring16MiniAODv2_reHLT_V3.root"   );
    TFile * fQCD2  = new TFile("runs/run20161010/histsAllHad_Jetpt600HT1000_20161010_b2gtree_QCD_Pt_470to600_pythia8_RunIISpring16MiniAODv2_reHLT_V3.root"   );
    TFile * fQCD3  = new TFile("runs/run20161010/histsAllHad_Jetpt600HT1000_20161010_b2gtree_QCD_Pt_600to800_pythia8_RunIISpring16MiniAODv2_reHLT_V3.root"   );
    TFile * fQCD4  = new TFile("runs/run20161010/histsAllHad_Jetpt600HT1000_20161010_b2gtree_QCD_Pt_800to1000_pythia8_RunIISpring16MiniAODv2_reHLT_V3.root"  );
    TFile * fQCD5  = new TFile("runs/run20161010/histsAllHad_Jetpt600HT1000_20161010_b2gtree_QCD_Pt_1000to1400_pythia8_RunIISpring16MiniAODv2_reHLT_V3.root" );
    TFile * fQCD6  = new TFile("runs/run20161010/histsAllHad_Jetpt600HT1000_20161010_b2gtree_QCD_Pt_1400to1800_pythia8_RunIISpring16MiniAODv2_reHLT_V3.root" );
    TFile * fQCD7  = new TFile("runs/run20161010/histsAllHad_Jetpt600HT1000_20161010_b2gtree_QCD_Pt_1800to2400_pythia8_RunIISpring16MiniAODv2_reHLT_V3.root" );
    TFile * fQCD8  = new TFile("runs/run20161010/histsAllHad_Jetpt600HT1000_20161010_b2gtree_QCD_Pt_2400to3200_pythia8_RunIISpring16MiniAODv2_reHLT_V3.root" );
    TFile * fQCD9  = new TFile("runs/run20161010/histsAllHad_Jetpt600HT1000_20161010_b2gtree_QCD_Pt_3200toInf_pythia8_RunIISpring16MiniAODv2_reHLT_V3.root"  );

TFile * ModMassOutFile = new TFile("runs/run20161010/ModMass_Jetpt600HT1000_20161010_b2gtree_QCD_Pt_300toInf_pythia8_RunIISpring16MiniAODv2_reHLT_V3.root" , "RECREATE");
	
    TFile * fModMass1  = new TFile("runs/run20161010/ModMass__Jetpt600HT1000_20161010_b2gtree_QCD_Pt_300to470_pythia8_RunIISpring16MiniAODv2_reHLT_V3.root"   );
    TFile * fModMass2  = new TFile("runs/run20161010/ModMass__Jetpt600HT1000_20161010_b2gtree_QCD_Pt_470to600_pythia8_RunIISpring16MiniAODv2_reHLT_V3.root"   );
    TFile * fModMass3  = new TFile("runs/run20161010/ModMass__Jetpt600HT1000_20161010_b2gtree_QCD_Pt_600to800_pythia8_RunIISpring16MiniAODv2_reHLT_V3.root"   );
    TFile * fModMass4  = new TFile("runs/run20161010/ModMass__Jetpt600HT1000_20161010_b2gtree_QCD_Pt_800to1000_pythia8_RunIISpring16MiniAODv2_reHLT_V3.root"  );
    TFile * fModMass5  = new TFile("runs/run20161010/ModMass__Jetpt600HT1000_20161010_b2gtree_QCD_Pt_1000to1400_pythia8_RunIISpring16MiniAODv2_reHLT_V3.root" );
    TFile * fModMass6  = new TFile("runs/run20161010/ModMass__Jetpt600HT1000_20161010_b2gtree_QCD_Pt_1400to1800_pythia8_RunIISpring16MiniAODv2_reHLT_V3.root" );
    TFile * fModMass7  = new TFile("runs/run20161010/ModMass__Jetpt600HT1000_20161010_b2gtree_QCD_Pt_1800to2400_pythia8_RunIISpring16MiniAODv2_reHLT_V3.root" );
    TFile * fModMass8  = new TFile("runs/run20161010/ModMass__Jetpt600HT1000_20161010_b2gtree_QCD_Pt_2400to3200_pythia8_RunIISpring16MiniAODv2_reHLT_V3.root" );
    TFile * fModMass9  = new TFile("runs/run20161010/ModMass__Jetpt600HT1000_20161010_b2gtree_QCD_Pt_3200toInf_pythia8_RunIISpring16MiniAODv2_reHLT_V3.root"  );
    
    // TFile * fQCD1  = new TFile("QCD_HT700_Kinematic_060716_nom_pt400.0.root" );
    // TFile * fQCD2  = new TFile("QCD_HT1000_Kinematic_060716_nom_pt400.0.root");
    // TFile * fQCD3  = new TFile("QCD_HT1500_Kinematic_060716_nom_pt400.0.root");
    // TFile * fQCD4  = new TFile("QCD_HT2000_Kinematic_060716_nom_pt400.0.root");

    OutFile->cd();
    for (unsigned int i=0; i< hists_names.size(); i++ ){
      TH1D * h1 = (TH1D*) fQCD1 ->Get( hists_names[i].c_str() ); 
      TH1D * h2 = (TH1D*) fQCD2 ->Get( hists_names[i].c_str() ); 
      TH1D * h3 = (TH1D*) fQCD3 ->Get( hists_names[i].c_str() ); 
      TH1D * h4 = (TH1D*) fQCD4 ->Get( hists_names[i].c_str() ); 
      TH1D * h5 = (TH1D*) fQCD5 ->Get( hists_names[i].c_str() ); 
      TH1D * h6 = (TH1D*) fQCD6 ->Get( hists_names[i].c_str() ); 
      TH1D * h7 = (TH1D*) fQCD7 ->Get( hists_names[i].c_str() ); 
      TH1D * h8 = (TH1D*) fQCD8 ->Get( hists_names[i].c_str() ); 
      TH1D * h9 = (TH1D*) fQCD9 ->Get( hists_names[i].c_str() ); 
      
      cout<<"h1 "<<h1->Integral()<<endl;
      cout<<"h2 "<<h2->Integral()<<endl;
      cout<<"h3 "<<h3->Integral()<<endl;
      cout<<"h4 "<<h4->Integral()<<endl;
      cout<<"h5 "<<h5->Integral()<<endl;
      cout<<"h6 "<<h6->Integral()<<endl;
      cout<<"h7 "<<h7->Integral()<<endl;
      cout<<"h8 "<<h8->Integral()<<endl;
      cout<<"h9 "<<h9->Integral()<<endl;
      

      h1->Sumw2();
      h2->Sumw2();
      h3->Sumw2();
      h4->Sumw2();
      h5->Sumw2();
      h6->Sumw2();
      h7->Sumw2();
      h8->Sumw2();
      h9->Sumw2();

      double h1_xs = 7475      ;
      double h2_xs = 587.1     ;
      double h3_xs = 167       ;
      double h4_xs = 28.25     ;
      double h5_xs = 8.195     ;
      double h6_xs = 0.7346    ;
      double h7_xs = 0.102     ;
      double h8_xs = 0.00644   ;
      double h9_xs = 0.000163  ;
      
      double h1_nevent =2482816  ; //300
      double h2_nevent =1998648  ; //470
      double h3_nevent =1377400  ; //600
      double h4_nevent =395328  ; //800
      double h5_nevent =299967  ;  //1000 
      double h6_nevent =38848  ; //1400
      double h7_nevent =39975  ;  //1800
      double h8_nevent =39990  ; //2400
      double h9_nevent =39988  ; //3200
		
      h1->Scale( h1_xs / h1_nevent * lumi);
      h2->Scale( h2_xs / h2_nevent * lumi);
      h3->Scale( h3_xs / h3_nevent * lumi);
      h4->Scale( h4_xs / h4_nevent * lumi);
      h5->Scale( h5_xs / h5_nevent * lumi);
      h6->Scale( h6_xs / h6_nevent * lumi);
      h7->Scale( h7_xs / h7_nevent * lumi);
      h8->Scale( h8_xs / h8_nevent * lumi);
      h9->Scale( h9_xs / h9_nevent * lumi);

      h1->SetFillColor(99);
      h2->SetFillColor(95);
      h3->SetFillColor(90);
      h4->SetFillColor(85);
      h5->SetFillColor(75);
      h6->SetFillColor(70);
      h7->SetFillColor(65);
      h8->SetFillColor(60);
      h9->SetFillColor(55);
      
      h1->SetLineColor(99);
      h2->SetLineColor(95);
      h3->SetLineColor(90);
      h4->SetLineColor(85);
      h5->SetLineColor(75);
      h6->SetLineColor(70);
      h7->SetLineColor(65);
      h8->SetLineColor(60);
      h9->SetLineColor(55);


      // h1->Rebin(5);
      // h2->Rebin(5);
      // h3->Rebin(5);
      // h4->Rebin(5);
      // h5->Rebin(5);
      // h6->Rebin(5);
      // h7->Rebin(5);
      // h8->Rebin(5);
      // h9->Rebin(5);
      

      cout<<"h1 "<<h1->Integral()<<endl;
      cout<<"h2 "<<h2->Integral()<<endl;
      cout<<"h3 "<<h3->Integral()<<endl;
      cout<<"h4 "<<h4->Integral()<<endl;
      cout<<"h5 "<<h5->Integral()<<endl;
      cout<<"h6 "<<h6->Integral()<<endl;
      cout<<"h7 "<<h7->Integral()<<endl;
      cout<<"h8 "<<h8->Integral()<<endl;
      cout<<"h9 "<<h9->Integral()<<endl;
      
      TCanvas *c1 = new TCanvas("c1","",900,700);
      THStack *hs = new THStack("hs","");
      // THStack hs("hs","hs");
      hs->Add(h9);
      hs->Add(h8);
      hs->Add(h7);
      hs->Add(h6);
      hs->Add(h5);
      hs->Add(h4);
      hs->Add(h3);
      hs->Add(h2);

      hs->Add(h1);
      hs->SetMinimum(0.0001);
      hs->Draw("HIST");

      TLegend * leg;
      leg  = new TLegend(0.7,0.54,0.95,0.89);
      leg ->SetBorderSize(0);
      leg ->SetFillColor(0);
      leg ->SetFillStyle(0);
      leg ->SetMargin(0.15);
      leg ->AddEntry(h1, "300-470", "F");
      leg ->AddEntry(h2, "470-600", "F");
      leg ->AddEntry(h3, "600-800", "F");
      leg ->AddEntry(h4, "800-1000", "F");
      leg ->AddEntry(h5, "1000-1400", "F");
      leg ->AddEntry(h6, "1400-1800", "F");
      leg ->AddEntry(h7, "1800-2400", "F");
      leg ->AddEntry(h8, "2400-3200", "F");
      leg ->AddEntry(h9, "3200-Inf", "F");
      leg ->Draw("same");
      
      // h1->Draw();
      // h2->Draw("same");
      string savename = "runs/run20161010/testStacks/testStack_Jetpt600HT1000_"+hists_names[i]+".pdf";
      string savename2 = "runs/run20161010/testStacks/testStack_Jetpt600HT1000_"+hists_names[i]+"_log.pdf";
      c1->SaveAs(savename.c_str() );
      c1->SetLogy();
      c1->SaveAs(savename2.c_str() );
      c1->SetLogy(0);

      h1->Add(h2);
      h1->Add(h3);
      h1->Add(h4);
      h1->Add(h5);
      h1->Add(h6);
      h1->Add(h7);
      h1->Add(h8);
      h1->Add(h9);
      
      h1->SetName(hists_names[i].c_str());
      h1->Write();
    }
    OutFile->Close();

    ModMassOutFile->cd();
    for (unsigned int i=0; i< modmass_hists_names.size(); i++ ){
      TH1D * h1 = (TH1D*) fModMass1 ->Get( modmass_hists_names[i].c_str() ); 
      TH1D * h2 = (TH1D*) fModMass2 ->Get( modmass_hists_names[i].c_str() ); 
      TH1D * h3 = (TH1D*) fModMass3 ->Get( modmass_hists_names[i].c_str() ); 
      TH1D * h4 = (TH1D*) fModMass4 ->Get( modmass_hists_names[i].c_str() ); 
      TH1D * h5 = (TH1D*) fModMass5 ->Get( modmass_hists_names[i].c_str() ); 
      TH1D * h6 = (TH1D*) fModMass6 ->Get( modmass_hists_names[i].c_str() ); 
      TH1D * h7 = (TH1D*) fModMass7 ->Get( modmass_hists_names[i].c_str() ); 
      TH1D * h8 = (TH1D*) fModMass8 ->Get( modmass_hists_names[i].c_str() ); 
      TH1D * h9 = (TH1D*) fModMass9 ->Get( modmass_hists_names[i].c_str() ); 
      
      cout<<"h1 "<<h1->Integral()<<endl;
      cout<<"h2 "<<h2->Integral()<<endl;
      cout<<"h3 "<<h3->Integral()<<endl;
      cout<<"h4 "<<h4->Integral()<<endl;
      cout<<"h5 "<<h5->Integral()<<endl;
      cout<<"h6 "<<h6->Integral()<<endl;
      cout<<"h7 "<<h7->Integral()<<endl;
      cout<<"h8 "<<h8->Integral()<<endl;
      cout<<"h9 "<<h9->Integral()<<endl;
      
      h1->Sumw2();
      h2->Sumw2();
      h3->Sumw2();
      h4->Sumw2();
      h5->Sumw2();
      h6->Sumw2();
      h7->Sumw2();
      h8->Sumw2();
      h9->Sumw2();

      double h1_xs = 7475      ;
      double h2_xs = 587.1     ;
      double h3_xs = 167       ;
      double h4_xs = 28.25     ;
      double h5_xs = 8.195     ;
      double h6_xs = 0.7346    ;
      double h7_xs = 0.102     ;
      double h8_xs = 0.00644   ;
      double h9_xs = 0.000163  ;
      
      double h1_nevent =2482816  ; //300
      double h2_nevent =1998648  ; //470
      double h3_nevent =1377400  ; //600
      double h4_nevent =395328  ; //800
      double h5_nevent =299967  ;  //1000 
      double h6_nevent =38848  ; //1400
      double h7_nevent =39975  ;  //1800
      double h8_nevent =39990  ; //2400
      double h9_nevent =39988  ; //3200
		
      h1->Scale( h1_xs / h1_nevent * lumi);
      h2->Scale( h2_xs / h2_nevent * lumi);
      h3->Scale( h3_xs / h3_nevent * lumi);
      h4->Scale( h4_xs / h4_nevent * lumi);
      h5->Scale( h5_xs / h5_nevent * lumi);
      h6->Scale( h6_xs / h6_nevent * lumi);
      h7->Scale( h7_xs / h7_nevent * lumi);
      h8->Scale( h8_xs / h8_nevent * lumi);
      h9->Scale( h9_xs / h9_nevent * lumi);

      h1->SetFillColor(99);
      h2->SetFillColor(95);
      h3->SetFillColor(90);
      h4->SetFillColor(85);
      h5->SetFillColor(75);
      h6->SetFillColor(70);
      h7->SetFillColor(65);
      h8->SetFillColor(60);
      h9->SetFillColor(55);
      
      h1->SetLineColor(99);
      h2->SetLineColor(95);
      h3->SetLineColor(90);
      h4->SetLineColor(85);
      h5->SetLineColor(75);
      h6->SetLineColor(70);
      h7->SetLineColor(65);
      h8->SetLineColor(60);
      h9->SetLineColor(55);


      // h1->Rebin(5);
      // h2->Rebin(5);
      // h3->Rebin(5);
      // h4->Rebin(5);
      // h5->Rebin(5);
      // h6->Rebin(5);
      // h7->Rebin(5);
      // h8->Rebin(5);
      // h9->Rebin(5);
      

      cout<<"h1 "<<h1->Integral()<<endl;
      cout<<"h2 "<<h2->Integral()<<endl;
      cout<<"h3 "<<h3->Integral()<<endl;
      cout<<"h4 "<<h4->Integral()<<endl;
      cout<<"h5 "<<h5->Integral()<<endl;
      cout<<"h6 "<<h6->Integral()<<endl;
      cout<<"h7 "<<h7->Integral()<<endl;
      cout<<"h8 "<<h8->Integral()<<endl;
      cout<<"h9 "<<h9->Integral()<<endl;
      
      TCanvas *c1 = new TCanvas("c1","",900,700);
      THStack *hs = new THStack("hs","");
      // THStack hs("hs","hs");
      hs->Add(h9);
      hs->Add(h8);
      hs->Add(h7);
      hs->Add(h6);
      hs->Add(h5);
      hs->Add(h4);
      hs->Add(h3);
      hs->Add(h2);

      hs->Add(h1);
      hs->SetMinimum(0.0001);
      hs->Draw("HIST");

      TLegend * leg;
      leg  = new TLegend(0.7,0.54,0.95,0.89);
      leg ->SetBorderSize(0);
      leg ->SetFillColor(0);
      leg ->SetFillStyle(0);
      leg ->SetMargin(0.15);
      leg ->AddEntry(h1, "300-470", "F");
      leg ->AddEntry(h2, "470-600", "F");
      leg ->AddEntry(h3, "600-800", "F");
      leg ->AddEntry(h4, "800-1000", "F");
      leg ->AddEntry(h5, "1000-1400", "F");
      leg ->AddEntry(h6, "1400-1800", "F");
      leg ->AddEntry(h7, "1800-2400", "F");
      leg ->AddEntry(h8, "2400-3200", "F");
      leg ->AddEntry(h9, "3200-Inf", "F");
      leg ->Draw("same");
      
      // h1->Draw();
      // h2->Draw("same");
      string savename = "runs/run20161010/testStacks/testStack_Jetpt600HT1000_"+modmass_hists_names[i]+".pdf";
      string savename2 = "runs/run20161010/testStacks/testStack_Jetpt600HT1000_"+modmass_hists_names[i]+"_log.pdf";
      c1->SaveAs(savename.c_str() );
      c1->SetLogy();
      c1->SaveAs(savename2.c_str() );
      c1->SetLogy(0);

      h1->Add(h2);
      h1->Add(h3);
      h1->Add(h4);
      h1->Add(h5);
      h1->Add(h6);
      h1->Add(h7);
      h1->Add(h8);
      h1->Add(h9);
      
      h1->SetName(modmass_hists_names[i].c_str());
      h1->Write();
    }
    ModMassOutFile->Close();
}
