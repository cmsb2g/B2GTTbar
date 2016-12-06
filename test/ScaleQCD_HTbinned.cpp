// [] .L ScaleHists.cpp+
// [] run()
// Jim Dolen 2015

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

TH1D * scaleHistsFromPtHatRootFilesReturnHist( string , vector <TFile* > & );
TH1D * scaleHists_QCD_HTbinned_ReturnHist(  string, vector <TFile* > &, double  );

void run(){
  // gROOT->ProcessLine(".L /Users/jdolen/Dropbox/Code/MyAnalysisRootFunctions_NEW.C");
  // gROOT->ProcessLine(".L /Users/jdolen/Dropbox/Code/JMAR/TopTagging/MyFunctions_TopTag.C");
  gROOT->SetBatch(); 

  TFile *out = new TFile("ScaleQCDtest.root","RECREATE");

  double lumi = 1;

  // TFile *F_qcdpt170   = new TFile("ntuples/ntuple_QCD_Pt_170to300_RunIISpring15DR74-Asympt50ns_2015_09_22.root");
  // TFile *F_qcdpt300   = new TFile("ntuples/ntuple_QCD_Pt_300to470_RunIISpring15DR74-Asympt50ns_2015_09_22c.root");
  // TFile *F_qcdpt470   = new TFile("ntuples/ntuple_QCD_Pt_470to600_RunIISpring15DR74-Asympt50ns_2015_09_22.root");
  // TFile *F_qcdpt600   = new TFile("ntuples/ntuple_QCD_Pt_600to800_RunIISpring15DR74-Asympt50ns_2015_09_22c.root");
  // TFile *F_qcdpt800   = new TFile("ntuples/ntuple_QCD_Pt_800to1000_RunIISpring15DR74-Asympt50ns_2015_09_22b.root");
  // TFile *F_qcdpt1000  = new TFile("ntuples/ntuple_QCD_Pt_1000to1400_RunIISpring15DR74-Asympt50ns_2015_09_22.root");
  // TFile *F_qcdpt1400  = new TFile("ntuples/ntuple_QCD_Pt_1400to1800_RunIISpring15DR74-Asympt50ns_2015_09_22.root");
  // TFile *F_qcdpt1800  = new TFile("ntuples/ntuple_QCD_Pt_1800to2400_RunIISpring15DR74-Asympt50ns_2015_09_22.root");
  // TFile *F_qcdpt2400  = new TFile("ntuples/ntuple_QCD_Pt_2400to3200_RunIISpring15DR74-Asympt50ns_2015_09_22.root");
  // TFile *F_qcdpt3200  = new TFile("ntuples/ntuple_QCD_Pt_3200toInf_RunIISpring15DR74-Asympt50ns_2015_09_22.root");
 
// histsAntiTag_Jetpt500HT1000Syst0_20161202full_b2gtreeV4_QCD_HT100to200_RunIISpring16MiniAODv2_try2.root
 
  string s1 = "histsKinemat_20161205noPUreweight_nom_noPUweight_b2gtreeV4_QCD_HT100to200_RunIISpring16MiniAODv2_try2.root";
  string s2 = "histsKinemat_20161205noPUreweight_nom_noPUweight_b2gtreeV4_QCD_HT200to300_RunIISpring16MiniAODv2_try2.root";
  string s3 = "histsKinemat_20161205noPUreweight_nom_noPUweight_b2gtreeV4_QCD_HT300to500_RunIISpring16MiniAODv2_try2.root";
  string s4 = "histsKinemat_20161205noPUreweight_nom_noPUweight_b2gtreeV4_QCD_HT500to700_RunIISpring16MiniAODv2_try2.root";
  string s5 = "histsKinemat_20161205noPUreweight_nom_noPUweight_b2gtreeV4_QCD_HT700to1000_RunIISpring16MiniAODv2.root";
  string s6 = "histsKinemat_20161205noPUreweight_nom_noPUweight_b2gtreeV4_QCD_HT1000to1500_RunIISpring16MiniAODv2.root";
  string s7 = "histsKinemat_20161205noPUreweight_nom_noPUweight_b2gtreeV4_QCD_HT1500to2000_RunIISpring16MiniAODv2_try4.root";
  string s8 = "histsKinemat_20161205noPUreweight_nom_noPUweight_b2gtreeV4_QCD_HT2000toInf_RunIISpring16MiniAODv2.root";

  string file_location = "/Users/jdolen/Nobackup/B2G2016/V4/runs/";


  TFile * F_HT200to300   = new TFile( (file_location+s2).c_str() );
  TFile * F_HT300to500   = new TFile( (file_location+s3).c_str() );
  TFile * F_HT500to700   = new TFile( (file_location+s4).c_str() );
  TFile * F_HT700to1000  = new TFile( (file_location+s5).c_str() );
  TFile * F_HT1000to1500 = new TFile( (file_location+s6).c_str() );
  TFile * F_HT1500to2000 = new TFile( (file_location+s7).c_str() );
  TFile * F_HT2000toInf  = new TFile( (file_location+s8).c_str() );


  std::vector <TFile* > rootFiles;
  // rootFiles.push_back( F_qcdpt170  );
  // rootFiles.push_back( F_qcdpt300  );
  // rootFiles.push_back( F_qcdpt470  );
  // rootFiles.push_back( F_qcdpt600  );
  // rootFiles.push_back( F_qcdpt800  );
  // rootFiles.push_back( F_qcdpt1000 );
  // rootFiles.push_back( F_qcdpt1400 );
  // rootFiles.push_back( F_qcdpt1800 );
  // rootFiles.push_back( F_qcdpt2400 );
  // rootFiles.push_back( F_qcdpt3200 );

  rootFiles.push_back( F_HT200to300   );
  rootFiles.push_back( F_HT300to500   );
  rootFiles.push_back( F_HT500to700   );
  rootFiles.push_back( F_HT700to1000  );
  rootFiles.push_back( F_HT1000to1500 );
  rootFiles.push_back( F_HT1500to2000 );
  rootFiles.push_back( F_HT2000toInf  );

  // for (unsigned int i=0; i<rootFiles.size(); i++){
  //   TH1D * h1 = (TH1D*)  rootFiles[i] -> Get( "h_mAK8_ModMass" );
  //   cout<<h1->Integral()<<endl;
  // }

  vector <string> histnames;
  histnames.push_back("h_CutFlow");

  histnames.push_back("h_EventWeight");         
  histnames.push_back("h_BtagCategoriesPreSF"); 
  histnames.push_back("h_BtagCategoriesPostSF");

  histnames.push_back("h_DijetMass_dRapIn"                             ); 
  histnames.push_back("h_DijetMass_dRapLo"                             ); 
  histnames.push_back("h_DijetMass_dRapHi"                             ); 
  histnames.push_back("h_DeltaRap"                                     ); 
  histnames.push_back("h_DeltaPhi"                                     ); 
  histnames.push_back("h_HT"                                           ); 
  histnames.push_back("h_MET"                                          ); 
  histnames.push_back("h_METphi"                                       ); 
  histnames.push_back("h_Nvtx"                                         ); 
  histnames.push_back("h_Jet0P"                                        ); 
  histnames.push_back("h_Jet0Pt"                                       ); 
  histnames.push_back("h_Jet0Phi"                                      ); 
  histnames.push_back("h_Jet0Rap"                                      ); 
  histnames.push_back("h_Jet0sdmass"                                   ); 
  histnames.push_back("h_Jet0Tau1"                                     ); 
  histnames.push_back("h_Jet0Tau2"                                     ); 
  histnames.push_back("h_Jet0Tau3"                                     ); 
  histnames.push_back("h_Jet0Tau4"                                     ); 
  histnames.push_back("h_Jet0SDmaxbdisc"                               ); 
  histnames.push_back("h_Jet0SDsubjet0pt"                              ); 
  histnames.push_back("h_Jet0SDsubjet0mass"                            ); 
  histnames.push_back("h_Jet0SDsubjet0tau1"                            ); 
  histnames.push_back("h_Jet0SDsubjet0tau2"                            ); 
  histnames.push_back("h_Jet0SDsubjet0tau3"                            ); 
  histnames.push_back("h_Jet0SDsubjet0bdisc"                           ); 
  histnames.push_back("h_Jet0SDsubjet1pt"                              ); 
  histnames.push_back("h_Jet0SDsubjet1mass"                            ); 
  histnames.push_back("h_Jet0SDsubjet1tau1"                            ); 
  histnames.push_back("h_Jet0SDsubjet1tau2"                            ); 
  histnames.push_back("h_Jet0SDsubjet1tau3"                            ); 
  histnames.push_back("h_Jet0SDsubjet1bdisc"                           ); 
  histnames.push_back("h_Jet0PuppiPt"                                  ); 
  histnames.push_back("h_Jet0PuppiMass"                                ); 
  histnames.push_back("h_Jet0PuppiSDpt"                                ); 
  histnames.push_back("h_Jet0PuppiTau1"                                ); 
  histnames.push_back("h_Jet0PuppiTau2"                                ); 
  histnames.push_back("h_Jet0PuppiTau3"                                ); 
  histnames.push_back("h_Jet0PuppiTau4"                                ); 
  histnames.push_back("h_Jet0PuppiSDmaxbdisc"                          ); 
  histnames.push_back("h_Jet0PuppiSDsubjet0pt"                         ); 
  histnames.push_back("h_Jet0PuppiSDsubjet0mass"                       ); 
  histnames.push_back("h_Jet0PuppiSDsubjet0tau1"                       ); 
  histnames.push_back("h_Jet0PuppiSDsubjet0tau2"                       ); 
  histnames.push_back("h_Jet0PuppiSDsubjet0tau3"                       ); 
  histnames.push_back("h_Jet0PuppiSDsubjet0bdisc"                      ); 
  histnames.push_back("h_Jet0PuppiSDsubjet1pt"                         ); 
  histnames.push_back("h_Jet0PuppiSDsubjet1mass"                       ); 
  histnames.push_back("h_Jet0PuppiSDsubjet1tau1"                       ); 
  histnames.push_back("h_Jet0PuppiSDsubjet1tau2"                       ); 
  histnames.push_back("h_Jet0PuppiSDsubjet1tau3"                       ); 
  histnames.push_back("h_Jet0PuppiSDsubjet1bdisc"                      ); 
  histnames.push_back("h_Jet0CHF"                                      ); 
  histnames.push_back("h_Jet0NHF"                                      ); 
  histnames.push_back("h_Jet0CM"                                       ); 
  histnames.push_back("h_Jet0NM"                                       ); 
  histnames.push_back("h_Jet0NEF"                                      ); 
  histnames.push_back("h_Jet0CEF"                                      ); 
  histnames.push_back("h_Jet0MF"                                       ); 
  histnames.push_back("h_Jet0Mult"                                     ); 
  histnames.push_back("h_Jet0PuppiCHF"                                 ); 
  histnames.push_back("h_Jet0PuppiNHF"                                 ); 
  histnames.push_back("h_Jet0PuppiCM"                                  ); 
  histnames.push_back("h_Jet0PuppiNM"                                  ); 
  histnames.push_back("h_Jet0PuppiNEF"                                 ); 
  histnames.push_back("h_Jet0PuppiCEF"                                 ); 
  histnames.push_back("h_Jet0PuppiMF"                                  ); 
  histnames.push_back("h_Jet0PuppiMult"                                ); 
  histnames.push_back("h_Jet1Pt"                                       ); 
  histnames.push_back("h_Jet1Rap"                                      ); 
  histnames.push_back("h_Jet0SDmass"                                   ); 
  histnames.push_back("h_Jet0SDmass_JetTag_b"                          ); 
  histnames.push_back("h_Jet0SDmass_JetTag_tau32"                      ); 
  histnames.push_back("h_Jet0SDmass_JetTag_b_tau32"                    ); 
  histnames.push_back("h_Jet0SDmass_OppositeJetTag_t_b"                ); 
  histnames.push_back("h_Jet0SDmass_OppositeJetTag_t_b_JetTag_b"       ); 
  histnames.push_back("h_Jet0SDmass_OppositeJetTag_t_b_JetTag_b_tau32" ); 
  histnames.push_back("h_Jet1SDmass"                                   ); 
  histnames.push_back("h_Jet1SDmass_JetTag_b"                          ); 
  histnames.push_back("h_Jet1SDmass_JetTag_tau32"                      ); 
  histnames.push_back("h_Jet1SDmass_JetTag_b_tau32"                    ); 
  histnames.push_back("h_Jet1SDmass_OppositeJetTag_t_b"                ); 
  histnames.push_back("h_Jet1SDmass_OppositeJetTag_t_b_JetTag_b"       ); 
  histnames.push_back("h_Jet1SDmass_OppositeJetTag_t_b_JetTag_b_tau32" ); 
  histnames.push_back("h_JetSDmass"                                    ); 
  histnames.push_back("h_JetSDmass_JetTag_b"                           ); 
  histnames.push_back("h_JetSDmass_JetTag_tau32"                       ); 
  histnames.push_back("h_JetSDmass_JetTag_b_tau32"                     ); 
  histnames.push_back("h_JetSDmass_OppositeJetTag_t_b"                 ); 
  histnames.push_back("h_JetSDmass_OppositeJetTag_t_b_JetTag_b"        ); 
  histnames.push_back("h_JetSDmass_OppositeJetTag_t_b_JetTag_b_tau32"  ); 
  histnames.push_back("h_Jet0Tau32"                                    ); 
  histnames.push_back("h_Jet0Tau32_JetTag_b"                           ); 
  histnames.push_back("h_Jet0Tau32_JetTag_mass"                        ); 
  histnames.push_back("h_Jet0Tau32_JetTag_b_mass"                      ); 
  histnames.push_back("h_Jet0Tau32_OppositeJetTag_t_b"                 ); 
  histnames.push_back("h_Jet0Tau32_OppositeJetTag_t_b_JetTag_b"        ); 
  histnames.push_back("h_Jet0Tau32_OppositeJetTag_t_b_JetTag_b_mass"   ); 
  histnames.push_back("h_Jet1Tau32"                                    ); 
  histnames.push_back("h_Jet1Tau32_JetTag_b"                           ); 
  histnames.push_back("h_Jet1Tau32_JetTag_mass"                        ); 
  histnames.push_back("h_Jet1Tau32_JetTag_b_mass"                      ); 
  histnames.push_back("h_Jet1Tau32_OppositeJetTag_t_b"                 ); 
  histnames.push_back("h_Jet1Tau32_OppositeJetTag_t_b_JetTag_b"        ); 
  histnames.push_back("h_Jet1Tau32_OppositeJetTag_t_b_JetTag_b_mass"   ); 
  histnames.push_back("h_JetTau32"                                     ); 
  histnames.push_back("h_JetTau32_JetTag_b"                            ); 
  histnames.push_back("h_JetTau32_JetTag_mass"                         ); 
  histnames.push_back("h_JetTau32_JetTag_b_mass"                       ); 
  histnames.push_back("h_JetTau32_OppositeJetTag_t_b"                  ); 
  histnames.push_back("h_JetTau32_OppositeJetTag_t_b_JetTag_b"         ); 
  histnames.push_back("h_JetTau32_OppositeJetTag_t_b_JetTag_b_mass"    ); 


  histnames.push_back("h_2ttag_inclu_dRapIn_DijetMass"   );
  histnames.push_back("h_2ttag_0btag_dRapIn_DijetMass"   );
  histnames.push_back("h_2ttag_1btag_dRapIn_DijetMass"   );
  histnames.push_back("h_2ttag_2btag_dRapIn_DijetMass"   );
  histnames.push_back("h_2ttag_inclu_dRapLo_DijetMass"   );
  histnames.push_back("h_2ttag_0btag_dRapLo_DijetMass"   );
  histnames.push_back("h_2ttag_1btag_dRapLo_DijetMass"   );
  histnames.push_back("h_2ttag_2btag_dRapLo_DijetMass"   );
  histnames.push_back("h_2ttag_inclu_dRapHi_DijetMass"   );
  histnames.push_back("h_2ttag_0btag_dRapHi_DijetMass"   );
  histnames.push_back("h_2ttag_1btag_dRapHi_DijetMass"   );
  histnames.push_back("h_2ttag_2btag_dRapHi_DijetMass"   );
  histnames.push_back("h_2ttag_inclu_DeltaRap"           );
  histnames.push_back("h_2ttag_0btag_DeltaRap"           );
  histnames.push_back("h_2ttag_1btag_DeltaRap"           );
  histnames.push_back("h_2ttag_2btag_DeltaRap"           );
  histnames.push_back("h_2ttag_inclu_DeltaPhi"           );
  histnames.push_back("h_2ttag_0btag_DeltaPhi"           );
  histnames.push_back("h_2ttag_1btag_DeltaPhi"           );
  histnames.push_back("h_2ttag_2btag_DeltaPhi"           );
  histnames.push_back("h_2ttag_inclu_HT"                 );
  histnames.push_back("h_2ttag_0btag_HT"                 );
  histnames.push_back("h_2ttag_1btag_HT"                 );
  histnames.push_back("h_2ttag_2btag_HT"                 );
  histnames.push_back("h_2ttag_inclu_MET"                );
  histnames.push_back("h_2ttag_0btag_MET"                );
  histnames.push_back("h_2ttag_1btag_MET"                );
  histnames.push_back("h_2ttag_2btag_MET"                );
  histnames.push_back("h_2ttag_inclu_METphi"             );
  histnames.push_back("h_2ttag_0btag_METphi"             );
  histnames.push_back("h_2ttag_1btag_METphi"             );
  histnames.push_back("h_2ttag_2btag_METphi"             );
  histnames.push_back("h_2ttag_inclu_Nvtx"               );
  histnames.push_back("h_2ttag_0btag_Nvtx"               );
  histnames.push_back("h_2ttag_1btag_Nvtx"               );
  histnames.push_back("h_2ttag_2btag_Nvtx"               );
  histnames.push_back("h_2ttag_inclu_Jet0P"                    );
  histnames.push_back("h_2ttag_inclu_Jet0Pt"                   );
  histnames.push_back("h_2ttag_inclu_Jet0Phi"                  );
  histnames.push_back("h_2ttag_inclu_Jet0Rap"                  );
  histnames.push_back("h_2ttag_inclu_Jet0SDmass"               );
  histnames.push_back("h_2ttag_inclu_Jet0SDmassCorrL23"        );
  histnames.push_back("h_2ttag_inclu_Jet0SDmassCorrL23Up"      );
  histnames.push_back("h_2ttag_inclu_Jet0Tau1"                 );
  histnames.push_back("h_2ttag_inclu_Jet0Tau2"                 );
  histnames.push_back("h_2ttag_inclu_Jet0Tau3"                 );
  histnames.push_back("h_2ttag_inclu_Jet0Tau4"                 );
  histnames.push_back("h_2ttag_inclu_Jet0SDmaxbdisc"           );
  histnames.push_back("h_2ttag_inclu_Jet0SDsubjet0pt"          );
  histnames.push_back("h_2ttag_inclu_Jet0SDsubjet0mass"        );
  histnames.push_back("h_2ttag_inclu_Jet0SDsubjet0tau1"        );
  histnames.push_back("h_2ttag_inclu_Jet0SDsubjet0tau2"        );
  histnames.push_back("h_2ttag_inclu_Jet0SDsubjet0tau3"        );
  histnames.push_back("h_2ttag_inclu_Jet0SDsubjet0bdisc"       );
  histnames.push_back("h_2ttag_inclu_Jet0SDsubjet1pt"          );
  histnames.push_back("h_2ttag_inclu_Jet0SDsubjet1mass"        );
  histnames.push_back("h_2ttag_inclu_Jet0SDsubjet1tau1"        );
  histnames.push_back("h_2ttag_inclu_Jet0SDsubjet1tau2"        );
  histnames.push_back("h_2ttag_inclu_Jet0SDsubjet1tau3"        );
  histnames.push_back("h_2ttag_inclu_Jet0SDsubjet1bdisc"       );
  histnames.push_back("h_2ttag_inclu_Jet0PuppiPt"              );
  histnames.push_back("h_2ttag_inclu_Jet0PuppiMass"            );
  histnames.push_back("h_2ttag_inclu_Jet0PuppiSDpt"            );
  histnames.push_back("h_2ttag_inclu_Jet0PuppiTau1"            );
  histnames.push_back("h_2ttag_inclu_Jet0PuppiTau2"            );
  histnames.push_back("h_2ttag_inclu_Jet0PuppiTau3"            );
  histnames.push_back("h_2ttag_inclu_Jet0PuppiTau4"            );
  histnames.push_back("h_2ttag_inclu_Jet0PuppiSDmaxbdisc"      );
  histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet0pt"     );
  histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet0mass"   );
  histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet0tau1"   );
  histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet0tau2"   );
  histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet0tau3"   );
  histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet0bdisc"  );
  histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet1pt"     );
  histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet1mass"   );
  histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet1tau1"   );
  histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet1tau2"   );
  histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet1tau3"   );
  histnames.push_back("h_2ttag_inclu_Jet0PuppiSDsubjet1bdisc"  );
  histnames.push_back("h_2ttag_inclu_Jet0CHF"                  );
  histnames.push_back("h_2ttag_inclu_Jet0NHF"                  );
  histnames.push_back("h_2ttag_inclu_Jet0CM"                   );
  histnames.push_back("h_2ttag_inclu_Jet0NM"                   );
  histnames.push_back("h_2ttag_inclu_Jet0NEF"                  );
  histnames.push_back("h_2ttag_inclu_Jet0CEF"                  );
  histnames.push_back("h_2ttag_inclu_Jet0MF"                   );
  histnames.push_back("h_2ttag_inclu_Jet0Mult"                 );
  histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet0pt"     );
  histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet0mass"   );
  histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet0tau1"   );
  histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet0tau2"   );
  histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet0tau3"   );
  histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet0bdisc"  );
  histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet1pt"     );
  histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet1mass"   );
  histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet1tau1"   );
  histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet1tau2"   );
  histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet1tau3"   );
  histnames.push_back("h_2ttag_2btag_Jet0PuppiSDsubjet1bdisc"  );
  histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet0pt"     );
  histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet0mass"   );
  histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet0tau1"   );
  histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet0tau2"   );
  histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet0tau3"   );
  histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet0bdisc"  );
  histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet1pt"     );
  histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet1mass"   );
  histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet1tau1"   );
  histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet1tau2"   );
  histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet1tau3"   );
  histnames.push_back("h_2ttag_1btag_Jet0PuppiSDsubjet1bdisc"  );
  histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet0pt"     );
  histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet0mass"   );
  histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet0tau1"   );
  histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet0tau2"   );
  histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet0tau3"   );
  histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet0bdisc"  );
  histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet1pt"     );
  histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet1mass"   );
  histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet1tau1"   );
  histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet1tau2"   );
  histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet1tau3"   );
  histnames.push_back("h_2ttag_0btag_Jet0PuppiSDsubjet1bdisc"  );
  histnames.push_back("h_2btag_DijetMass"                                   );
  histnames.push_back("h_2btag_DeltaRap"                                    );
  histnames.push_back("h_2btag_jet0massSD"                                  );
  histnames.push_back("h_2btag_jet0tau32"                                   );
  histnames.push_back("h_2btag_jet0tau21"                                   );
  histnames.push_back("h_2btag_jet0tau1"                                    );
  histnames.push_back("h_2btag_jet0tau2"                                    );
  histnames.push_back("h_2btag_jet0tau3"                                    );
  histnames.push_back("h_2btag_jet0subjet0mass"                             );
  histnames.push_back("h_2btag_jet0subjet1mass"                             );
  histnames.push_back("h_2btag_jet0subjet0mass_jet0subjet1mass"             );
  // histnames.push_back("h_2btag_jet0subjet0bdisc_jet0subjet1bdisc"           );
  // // histnames.push_back("h_2btag_jet1massSD"                                  );
  // histnames.push_back("h_2btag_jet1tau32"                                   );
  // histnames.push_back("h_2btag_jet1tau21"                                   );
  // histnames.push_back("h_2btag_jet1tau1"                                    );
  // histnames.push_back("h_2btag_jet1tau2"                                    );
  // histnames.push_back("h_2btag_jet1tau3"                                    );
  // histnames.push_back("h_2btag_jet1subjet0mass"                             );
  // histnames.push_back("h_2btag_jet1subjet1mass"                             );
  // histnames.push_back("h_2btag_jet1subjet0mass_jet1subjet1mass"             );
  // histnames.push_back("h_2btag_jet1subjet0bdisc_jet1subjet1bdisc"           );
  // histnames.push_back("h_2btag_jet1ttag_jet0massSD"                         );
  // histnames.push_back("h_2btag_jet1ttag_jet0tau32"                          );
  // histnames.push_back("h_2btag_jet1ttag_jet0tau21"                          );
  // histnames.push_back("h_2btag_jet1ttag_jet0tau1"                           );
  // histnames.push_back("h_2btag_jet1ttag_jet0tau2"                           );
  // histnames.push_back("h_2btag_jet1ttag_jet0tau3"                           );
  // histnames.push_back("h_2btag_jet1ttag_jet0subjet0mass"                    );
  // histnames.push_back("h_2btag_jet1ttag_jet0subjet1mass"                    );
  // histnames.push_back("h_2btag_jet1ttag_jet0subjet0mass_jet0subjet1mass"    );
  // histnames.push_back("h_2btag_jet1ttag_jet0subjet0bdisc_jet0subjet1bdisc"  );
  // histnames.push_back("h_2btag_jet0ttag_jet1massSD"                         );
  // histnames.push_back("h_2btag_jet0ttag_jet1tau32"                          );
  // histnames.push_back("h_2btag_jet0ttag_jet1tau21"                          );
  // histnames.push_back("h_2btag_jet0ttag_jet1tau1"                           );
  // histnames.push_back("h_2btag_jet0ttag_jet1tau2"                           );
  // histnames.push_back("h_2btag_jet0ttag_jet1tau3"                           );
  // histnames.push_back("h_2btag_jet0ttag_jet1subjet0mass"                    );
  // histnames.push_back("h_2btag_jet0ttag_jet1subjet1mass"                    );
  // histnames.push_back("h_2btag_jet0ttag_jet1subjet0mass_jet1subjet1mass"    );
  // histnames.push_back("h_2btag_jet0ttag_jet1subjet0bdisc_jet1subjet1bdisc"  );
  // histnames.push_back("h_2btag_jet1ttag_jet0tautag_jet0massSD"              );
  // histnames.push_back("h_2btag_jet1ttag_jet0masstag_jet0tau32"              );
  // histnames.push_back("h_2btag_jet1ttag_jet0masstag_jet0tau21"              );
  // histnames.push_back("h_2btag_jet1ttag_jet0masstag_jet0tau1"               );
  // histnames.push_back("h_2btag_jet1ttag_jet0masstag_jet0tau2"               );
  // histnames.push_back("h_2btag_jet1ttag_jet0masstag_jet0tau3"               );
  // histnames.push_back("h_2btag_jet0ttag_jet1tautag_jet1massSD"              );
  // histnames.push_back("h_2btag_jet0ttag_jet1masstag_jet1tau32"              );
  // histnames.push_back("h_2btag_jet0ttag_jet1masstag_jet1tau21"              );
  // histnames.push_back("h_2btag_jet0ttag_jet1masstag_jet1tau1"               );
  // histnames.push_back("h_2btag_jet0ttag_jet1masstag_jet1tau2"               );
  // histnames.push_back("h_2btag_jet0ttag_jet1masstag_jet1tau3"               );
                                                             
  out->cd();
  for (unsigned int i=0; i<histnames.size(); i++){
    cout<<"Getting "<<histnames[i]<<endl;
    TH1D  * hist = scaleHists_QCD_HTbinned_ReturnHist( histnames[i].c_str(), rootFiles, lumi) ;
    hist->SetName(histnames[i].c_str());
    hist->Write();
  }
  out->Write();
  out->Close();
}



TH1D * scaleHistsFromPtHatRootFilesReturnHist( string histname, vector <TFile* > &rootFiles )
{
  const double lumi = 40.03 ; // pb-1
  vector <double> mcscales;
  // mcscales.push_back(  117276.          / 3468514. * lumi);  // xs / nevents * lumi
  // mcscales.push_back(    7823.          / 2936644. * lumi);
  mcscales.push_back(     648.2         / 1971800. * lumi);
  mcscales.push_back(     186.9         / 1981608. * lumi);
  mcscales.push_back(      32.293       / 1990208. * lumi);
  mcscales.push_back(       9.4183      / 1487712. * lumi);
  mcscales.push_back(       0.84265     /  197959. * lumi);
  mcscales.push_back(       0.114943    /  194924. * lumi);
  mcscales.push_back(       0.00682981  /  198383. * lumi);
  mcscales.push_back(       0.000165445 /  194528. * lumi);

  TH1D * htemp = (TH1D*)  rootFiles[0] -> Get( histname.c_str() );
  TH1D * h_sum = (TH1D*)htemp->Clone(); 
  h_sum->Reset();
  h_sum->Sumw2();

  for (unsigned int i=0; i<rootFiles.size(); i++){
    TH1D * h1 = (TH1D*)  rootFiles[i] -> Get( histname.c_str() );
    // h1->Sumw2();
    h1->Scale(mcscales[i]);
    h_sum->Add(h1);
    // cout<<mcscales[i]<<"  "<<h1->Integral()<<endl;
  }
  return h_sum;
}




TH1D * scaleHists_QCD_HTbinned_ReturnHist(  string histname, vector <TFile* > &rootFiles, double lumi )
{
  cout<<"Scaling "<<histname<<endl;
  vector <double> mcscales;
  // mcscales.push_back(   27990000.0    / 18523829   * lumi );     // 100to200        
  mcscales.push_back(   1712000.0    / 18523829   * lumi );     // 200to300        
  mcscales.push_back(    347700.0    / 16830696   * lumi );     // 300to500       
  mcscales.push_back(     32100.0    / 19199088   * lumi );     // 500to700        
  mcscales.push_back(      6831.0    / 15621634   * lumi );     // 700to1000        
  mcscales.push_back(      1207.0    / 4980387    * lumi );     // 1000to1500       
  mcscales.push_back(       119.9    / 3846616    * lumi );     // 1500to2000       
  mcscales.push_back(        25.24   / 1960245    * lumi );     // 2000toInf       

  vector <string> binnames;
  // mcscales.push_back(   27990000.0    / 18523829   * lumi );     // 100to200        
  binnames.push_back(  "200to300"    );     // 200to300        
  binnames.push_back(  "300to500"    );     // 300to500       
  binnames.push_back(  "500to700"    );     // 500to700        
  binnames.push_back(  "700to1000"   );     // 700to1000        
  binnames.push_back(  "1000to1500"  );     // 1000to1500       
  binnames.push_back(  "1500to2000"  );     // 1500to2000       
  binnames.push_back(  "2000toInf"   );     // 2000toInf       


  TCanvas *c1 = new TCanvas("c1","",900,700);

  TH1D * htemp = (TH1D*)  rootFiles[0] -> Get( histname.c_str() ); cout<<"debug1"<<endl;
  TH1D * h_sum = (TH1D*)htemp->Clone(); cout<<"debug2"<<endl;
  h_sum->Reset();
  h_sum->Sumw2();

  THStack *hs = new THStack("hs","");

  TLegend * leg;
  leg  = new TLegend(0.7,0.54,0.95,0.89);
  leg ->SetBorderSize(0);
  leg ->SetFillColor(0);
  leg ->SetFillStyle(0);
  leg ->SetMargin(0.15);


  for (unsigned int i=0; i<rootFiles.size(); i++)
  {
    unsigned int j = rootFiles.size()-1-i;
    TH1D * h1 = (TH1D*)  rootFiles[j] -> Get( histname.c_str() );
    h1->Sumw2();
    cout<<"histogram "<<histname<<" "<<binnames[j]<<" Before Scale "<<h1->Integral();
    h1->Scale(mcscales[j]);
    cout<<" After Scale "<<h1->Integral()<<endl;;
    h1->SetFillColor(99-5*i);
    h1->SetLineColor(99-5*i);
    leg ->AddEntry(h1, binnames[j].c_str(), "F");
    h_sum->Add(h1);
    hs->Add(h1);
  }      

  hs    ->SetMinimum(0.0001);
  hs    ->Draw("HIST");
  h_sum ->Draw("Psame");
  leg   ->Draw("same");

  string savename  = "testScale/testStack_Jetpt500HT1000_"+histname+".pdf";
  string savename2 = "testScale/testStack_Jetpt500HT1000_"+histname+"_log.pdf";
  c1->SaveAs(savename.c_str() );
  c1->SetLogy();
  c1->SaveAs(savename2.c_str() );
  c1->SetLogy(0);

  return h_sum;
}
