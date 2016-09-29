// root[] .L LoopTreeAllHad_V2.cpp++
// root[] run()

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <TTree.h>
#include <TH1F.h>
#include <sstream>
#include <TFile.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TROOT.h>
#include <TColor.h>
#include <TRandom3.h>

void looptree(string, string, bool, bool );


void run()
{
  string folder = "/uscmst1b_scratch/lpc1/lpcphys/jdolen/B2G2016/V2/";
  
  //void looptree(string input_folder, string input_file, bool isData, bool isFrozen )
  // looptree(folder, "b2gtree_QCD_Pt_300to470_pythia8_RunIISpring16MiniAODv2_reHLT_V2.root"    , false, false);
  // looptree(folder, "b2gtree_QCD_Pt_470to600_pythia8_RunIISpring16MiniAODv2_reHLT_V2.root"    , false, false);
  // looptree(folder, "b2gtree_QCD_Pt_600to800_pythia8_RunIISpring16MiniAODv2_reHLT_V2.root"    , false, false);
  // looptree(folder, "b2gtree_QCD_Pt_800to1000_pythia8_RunIISpring16MiniAODv2_reHLT_V2.root"   , false, false);   
  // looptree(folder, "b2gtree_QCD_Pt_1000to1400_pythia8_RunIISpring16MiniAODv2_reHLT_V2.root"  , false, false);  
  // looptree(folder, "b2gtree_QCD_Pt_1400to1800_pythia8_RunIISpring16MiniAODv2_reHLT_V2.root"  , false, false);  
  // looptree(folder, "b2gtree_QCD_Pt_1800to2400_pythia8_RunIISpring16MiniAODv2_reHLT_V2.root"  , false, false);  
  // looptree(folder, "b2gtree_QCD_Pt_2400to3200_pythia8_RunIISpring16MiniAODv2_reHLT_V2.root"  , false, false);  
  // looptree(folder, "b2gtree_QCD_Pt_3200toInf_pythia8_RunIISpring16MiniAODv2_reHLT_V2.root"   , false, false); 
  // looptree(folder, "b2gtree_JetHT_Run2016B-PromptReco-v2_JSONsept9_V2_99percentFinished_All.root", true, true);
  // looptree(folder, "b2gtree_JetHT_Run2016C-PromptReco-v2_JSONsept9_V2_99percentFinished_All.root", true, true);
  // looptree(folder, "b2gtree_JetHT_Run2016D-PromptReco-v2_JSONsept9_V2_99percentFinished_All.root", true, true);
  // looptree(folder, "b2gtree_JetHT_Run2016E-PromptReco-v2_JSONsept9_V2_99percentFinished_All.root", true, true);
  // looptree(folder, "b2gtree_JetHT_Run2016F-PromptReco-v1_JSONsept9_V2_99percentFinished_All.root", true, true);
  // looptree(folder, "b2gtree_JetHT_Run2016G-PromptReco-v1_JSONsept9_V2_99percentFinished_All.root", true, true);
  looptree(folder, "b2gtree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISpring16MiniAODv2-PUSpring16_reHLT_V2_99percentFinished_All.root", false, false);

}
void looptree(string input_folder, string input_file, bool isData, bool isFrozen )
{
  TCanvas *c1236= new TCanvas("c1236","",200,10,800,700);

  string file_name =  input_folder+input_file;
  TFile *F1   = new TFile(file_name.c_str() );

  // Get Tree entries
  Int_t   PassMETFilters                            ;
  Float_t Jet0PtRaw                                 ;
  Float_t Jet0EtaRaw                                ;
  Float_t Jet0PhiRaw                                ;
  Float_t Jet0MassRaw                               ;
  Float_t Jet0P                                     ;
  Float_t Jet0Pt                                    ;
  Float_t Jet0Eta                                   ;
  Float_t Jet0Phi                                   ;
  Float_t Jet0Rap                                   ;
  Float_t Jet0Energy                                ;
  Float_t Jet0Mass                                  ;
  Float_t Jet0Area                                  ;
  Float_t Jet0SDmass                                ;
  Float_t Jet0SDmassRaw                             ;
  Float_t Jet0SDmassCorrL23                         ;    
  Float_t Jet0SDmassCorrL23Up                       ;    
  Float_t Jet0SDmassCorrL23Dn                       ;     
  Float_t Jet0SDmassCorrL23Smear                    ;    
  Float_t Jet0SDmassCorrL23SmearUp                  ;    
  Float_t Jet0SDmassCorrL23SmearDn                  ;  
  Float_t Jet0SDmassCorrL123                        ;    
  Float_t Jet0SDmassCorrL123Up                      ;    
  Float_t Jet0SDmassCorrL123Dn                      ;     
  Float_t Jet0SDptRaw                               ;    
  Float_t Jet0SDptCorrL23                           ;    
  Float_t Jet0SDptCorrL23Up                         ;    
  Float_t Jet0SDptCorrL23Dn                         ;    
  Float_t Jet0SDptCorrL123                          ;    
  Float_t Jet0SDptCorrL123Up                        ;    
  Float_t Jet0SDptCorrL123Dn                        ;    
  Float_t Jet0SDptCorrL23Smear                      ;    
  Float_t Jet0SDptCorrL23SmearUp                    ;    
  Float_t Jet0SDptCorrL23SmearDn                    ;    
  Float_t Jet0SDetaRaw                              ;    
  Float_t Jet0SDphiRaw                              ;    
  Float_t Jet0MassPruned                            ;
  Float_t Jet0MassTrimmed                           ;
  Float_t Jet0Tau1                                  ;
  Float_t Jet0Tau2                                  ;
  Float_t Jet0Tau3                                  ;
  Float_t Jet0Tau4                                  ;
  Float_t Jet0Tau32                                 ;
  Float_t Jet0Tau21                                 ;
  Float_t Jet0SDsubjet0bdisc                        ;
  Float_t Jet0SDsubjet1bdisc                        ;
  Float_t Jet0SDmaxbdisc                            ;
  Float_t Jet0SDmaxbdiscflavHadron                  ;
  Float_t Jet0SDmaxbdiscflavParton                  ;
  Float_t Jet0SDsubjet0pt                           ;
  Float_t Jet0SDsubjet0mass                         ;
  Float_t Jet0SDsubjet0eta                          ;
  Float_t Jet0SDsubjet0phi                          ;
  Float_t Jet0SDsubjet0area                         ;
  Float_t Jet0SDsubjet0flavHadron                   ;
  Float_t Jet0SDsubjet0flavParton                   ;
  Float_t Jet0SDsubjet0tau1                         ;
  Float_t Jet0SDsubjet0tau2                         ;
  Float_t Jet0SDsubjet0tau3                         ;
  Float_t Jet0SDsubjet1pt                           ;
  Float_t Jet0SDsubjet1mass                         ;
  Float_t Jet0SDsubjet1eta                          ;
  Float_t Jet0SDsubjet1phi                          ;
  Float_t Jet0SDsubjet1area                         ;
  Float_t Jet0SDsubjet1flavHadron                   ;
  Float_t Jet0SDsubjet1flavParton                   ;
  Float_t Jet0SDsubjet1tau1                         ;
  Float_t Jet0SDsubjet1tau2                         ;
  Float_t Jet0SDsubjet1tau3                         ;
  Float_t Jet0PuppiPt                               ;
  Float_t Jet0PuppiEta                              ;
  Float_t Jet0PuppiPhi                              ;
  Float_t Jet0PuppiMass                             ;

  Float_t Jet0PuppiSDmass                           ;
  Float_t Jet0PuppiSDmassCorr                       ;
  Float_t Jet0PuppiSDmassCorrUp                     ;
  Float_t Jet0PuppiSDmassCorrDn                     ;
  Float_t Jet0PuppiSDmassCorrL23Smear               ;
  Float_t Jet0PuppiSDmassCorrL23SmearUp             ;
  Float_t Jet0PuppiSDmassCorrL23SmearDn             ;
  Float_t Jet0PuppiSDpt                             ;
  Float_t Jet0PuppiSDptCorr                         ;
  Float_t Jet0PuppiSDptCorrUp                       ;
  Float_t Jet0PuppiSDptCorrDn                       ;
  Float_t Jet0PuppiSDptCorrL23Smear                 ;
  Float_t Jet0PuppiSDptCorrL23SmearUp               ;
  Float_t Jet0PuppiSDptCorrL23SmearDn               ;
  Float_t Jet0PuppiSDeta                            ;
  Float_t Jet0PuppiSDphi                            ;

  Float_t Jet0PuppiTau1                             ;
  Float_t Jet0PuppiTau2                             ;
  Float_t Jet0PuppiTau3                             ;
  Float_t Jet0PuppiTau4                             ;
  Float_t Jet0PuppiTau32                            ;
  Float_t Jet0PuppiTau21                            ;
  Float_t Jet0PuppiSDsubjet0bdisc                   ;
  Float_t Jet0PuppiSDsubjet1bdisc                   ;
  Float_t Jet0PuppiSDmaxbdisc                       ;
  Float_t Jet0PuppiSDmaxbdiscflavHadron             ;
  Float_t Jet0PuppiSDmaxbdiscflavParton             ;
  Float_t Jet0PuppiSDsubjet0pt                      ;
  Float_t Jet0PuppiSDsubjet0mass                    ;
  Float_t Jet0PuppiSDsubjet0eta                     ;
  Float_t Jet0PuppiSDsubjet0phi                     ;
  Float_t Jet0PuppiSDsubjet0area                    ;
  Float_t Jet0PuppiSDsubjet0flavHadron              ;
  Float_t Jet0PuppiSDsubjet0flavParton              ;
  Float_t Jet0PuppiSDsubjet0tau1                    ;
  Float_t Jet0PuppiSDsubjet0tau2                    ;
  Float_t Jet0PuppiSDsubjet0tau3                    ;
  Float_t Jet0PuppiSDsubjet1pt                      ;
  Float_t Jet0PuppiSDsubjet1mass                    ;
  Float_t Jet0PuppiSDsubjet1eta                     ;
  Float_t Jet0PuppiSDsubjet1phi                     ;
  Float_t Jet0PuppiSDsubjet1area                    ;
  Float_t Jet0PuppiSDsubjet1flavHadron              ;
  Float_t Jet0PuppiSDsubjet1flavParton              ;
  Float_t Jet0PuppiSDsubjet1tau1                    ;
  Float_t Jet0PuppiSDsubjet1tau2                    ;
  Float_t Jet0PuppiSDsubjet1tau3                    ;
  Float_t Jet0CHF                                   ;
  Float_t Jet0NHF                                   ;
  Float_t Jet0CM                                    ;
  Float_t Jet0NM                                    ;
  Float_t Jet0NEF                                   ;
  Float_t Jet0CEF                                   ;
  Float_t Jet0MF                                    ;
  Float_t Jet0Mult                                  ;
  Float_t Jet0MassCorrFactor                        ;
  Float_t Jet0MassCorrFactorUp                      ;
  Float_t Jet0MassCorrFactorDn                      ;
  Float_t Jet0CorrFactor                            ;
  Float_t Jet0CorrFactorUp                          ;
  Float_t Jet0CorrFactorDn                          ;
  Float_t Jet0PtSmearFactor                         ;
  Float_t Jet0PtSmearFactorUp                       ;
  Float_t Jet0PtSmearFactorDn                       ;
  Float_t Jet0PuppiMassCorrFactor                   ;
  Float_t Jet0PuppiMassCorrFactorUp                 ;
  Float_t Jet0PuppiMassCorrFactorDn                 ;
  Float_t Jet0PuppiCorrFactor                       ;
  Float_t Jet0PuppiCorrFactorUp                     ;
  Float_t Jet0PuppiCorrFactorDn                     ;
  Float_t Jet0PuppiPtSmearFactor                    ;
  Float_t Jet0PuppiPtSmearFactorUp                  ;
  Float_t Jet0PuppiPtSmearFactorDn                  ;
  Float_t Jet0EtaScaleFactor                        ;
  Float_t Jet0PhiScaleFactor                        ;
  // Float_t Jet0MatchedGenJetDR                       ;
  Float_t Jet0MatchedGenJetPt                       ;
  Float_t Jet0MatchedGenJetMass                     ;

  Int_t   Jet0GenMatched_TopHadronic                ;
  Float_t Jet0GenMatched_TopPt                      ;
  Float_t Jet0GenMatched_TopEta                     ;
  Float_t Jet0GenMatched_TopPhi                     ;
  Float_t Jet0GenMatched_TopMass                    ;
  Float_t Jet0GenMatched_bPt                        ;
  Float_t Jet0GenMatched_WPt                        ;
  Float_t Jet0GenMatched_Wd1Pt                      ;
  Float_t Jet0GenMatched_Wd2Pt                      ;
  Float_t Jet0GenMatched_Wd1ID                      ;
  Float_t Jet0GenMatched_Wd2ID                      ;
  Float_t Jet0GenMatched_MaxDeltaRPartonTop         ;
  Float_t Jet0GenMatched_MaxDeltaRWPartonTop        ;
  Float_t Jet0GenMatched_MaxDeltaRWPartonW          ;
  Float_t Jet0GenMatched_DeltaR_t_b                 ;
  Float_t Jet0GenMatched_DeltaR_t_W                 ;
  Float_t Jet0GenMatched_DeltaR_t_Wd1               ;
  Float_t Jet0GenMatched_DeltaR_t_Wd2               ;
  Float_t Jet0GenMatched_DeltaR_W_b1                ;
  Float_t Jet0GenMatched_DeltaR_W_Wd1               ;
  Float_t Jet0GenMatched_DeltaR_W_Wd2               ;
  Float_t Jet0GenMatched_DeltaR_Wd1_Wd2             ;
  Float_t Jet0GenMatched_DeltaR_Wd1_b               ;
  Float_t Jet0GenMatched_DeltaR_Wd2_b               ;
  Float_t Jet0GenMatched_DeltaR_jet_t               ;
  Float_t Jet0GenMatched_DeltaR_jet_W               ;
  Float_t Jet0GenMatched_DeltaR_jet_b               ;
  Float_t Jet0GenMatched_DeltaR_jet_Wd1             ;
  Float_t Jet0GenMatched_DeltaR_jet_Wd2             ;
  Float_t Jet0GenMatched_DeltaR_pup0_b              ;
  Float_t Jet0GenMatched_DeltaR_pup0_Wd1            ;
  Float_t Jet0GenMatched_DeltaR_pup0_Wd2            ;
  Float_t Jet0GenMatched_DeltaR_pup1_b              ;
  Float_t Jet0GenMatched_DeltaR_pup1_Wd1            ;
  Float_t Jet0GenMatched_DeltaR_pup1_Wd2            ;
  Float_t Jet0GenMatched_partonPt                   ;
  Float_t Jet0GenMatched_partonEta                  ;
  Float_t Jet0GenMatched_partonPhi                  ;
  Float_t Jet0GenMatched_partonMass                 ;
  Float_t Jet0GenMatched_partonID                   ;
  Float_t Jet0GenMatched_DeltaRjetParton            ;

  Float_t Jet1PtRaw                                 ;
  Float_t Jet1EtaRaw                                ;
  Float_t Jet1PhiRaw                                ;
  Float_t Jet1MassRaw                               ;
  Float_t Jet1P                                     ;
  Float_t Jet1Pt                                    ;
  Float_t Jet1Eta                                   ;
  Float_t Jet1Phi                                   ;
  Float_t Jet1Rap                                   ;
  Float_t Jet1Energy                                ;
  Float_t Jet1Mass                                  ;
  Float_t Jet1Area                                  ;
  Float_t Jet1SDmass                                ;
  Float_t Jet1SDmassRaw                             ;
  Float_t Jet1SDmassCorrL23                         ;
  Float_t Jet1SDmassCorrL23Up                       ;
  Float_t Jet1SDmassCorrL23Dn                       ;
  Float_t Jet1SDmassCorrL123                        ;
  Float_t Jet1SDmassCorrL123Up                      ;
  Float_t Jet1SDmassCorrL123Dn                      ;
  Float_t Jet1SDmassCorrL23Smear                    ;
  Float_t Jet1SDmassCorrL23SmearUp                  ;
  Float_t Jet1SDmassCorrL23SmearDn                  ;
  Float_t Jet1SDptRaw                               ;
  Float_t Jet1SDptCorrL23                           ;
  Float_t Jet1SDptCorrL23Up                         ;
  Float_t Jet1SDptCorrL23Dn                         ;
  Float_t Jet1SDptCorrL123                          ;
  Float_t Jet1SDptCorrL123Up                        ;
  Float_t Jet1SDptCorrL123Dn                        ;
  Float_t Jet1SDptCorrL23Smear                      ;
  Float_t Jet1SDptCorrL23SmearUp                    ;
  Float_t Jet1SDptCorrL23SmearDn                    ;
  Float_t Jet1SDetaRaw                              ;
  Float_t Jet1SDphiRaw                              ; 
  Float_t Jet1MassPruned                            ;
  Float_t Jet1MassTrimmed                           ;
  Float_t Jet1Tau1                                  ;
  Float_t Jet1Tau2                                  ;
  Float_t Jet1Tau3                                  ;
  Float_t Jet1Tau4                                  ;
  Float_t Jet1Tau32                                 ;
  Float_t Jet1Tau21                                 ;
  Float_t Jet1SDsubjet0bdisc                        ;
  Float_t Jet1SDsubjet1bdisc                        ;
  Float_t Jet1SDmaxbdisc                            ;
  Float_t Jet1SDmaxbdiscflavHadron                  ;
  Float_t Jet1SDmaxbdiscflavParton                  ;
  Float_t Jet1SDsubjet0pt                           ;
  Float_t Jet1SDsubjet0eta                          ;
  Float_t Jet1SDsubjet0phi                          ;
  Float_t Jet1SDsubjet0mass                         ;
  Float_t Jet1SDsubjet0area                         ;
  Float_t Jet1SDsubjet0flavHadron                   ;
  Float_t Jet1SDsubjet0flavParton                   ;
  Float_t Jet1SDsubjet0tau1                         ;
  Float_t Jet1SDsubjet0tau2                         ;
  Float_t Jet1SDsubjet0tau3                         ;
  Float_t Jet1SDsubjet1pt                           ;
  Float_t Jet1SDsubjet1eta                          ;
  Float_t Jet1SDsubjet1phi                          ;
  Float_t Jet1SDsubjet1mass                         ;
  Float_t Jet1SDsubjet1area                         ;
  Float_t Jet1SDsubjet1flavHadron                   ;
  Float_t Jet1SDsubjet1flavParton                   ;
  Float_t Jet1SDsubjet1tau1                         ;
  Float_t Jet1SDsubjet1tau2                         ;
  Float_t Jet1SDsubjet1tau3                         ;
  Float_t Jet1PuppiPt                               ;
  Float_t Jet1PuppiEta                              ;
  Float_t Jet1PuppiPhi                              ;
  Float_t Jet1PuppiMass                             ;

  Float_t Jet1PuppiSDmass                           ;
  Float_t Jet1PuppiSDmassCorr                       ;
  Float_t Jet1PuppiSDmassCorrUp                     ;
  Float_t Jet1PuppiSDmassCorrDn                     ;
  Float_t Jet1PuppiSDmassCorrL23Smear               ;
  Float_t Jet1PuppiSDmassCorrL23SmearUp             ;
  Float_t Jet1PuppiSDmassCorrL23SmearDn             ;
  Float_t Jet1PuppiSDpt                             ;
  Float_t Jet1PuppiSDptCorr                         ;
  Float_t Jet1PuppiSDptCorrUp                       ;
  Float_t Jet1PuppiSDptCorrDn                       ;
  Float_t Jet1PuppiSDptCorrL23Smear                 ;
  Float_t Jet1PuppiSDptCorrL23SmearUp               ;
  Float_t Jet1PuppiSDptCorrL23SmearDn               ;
  Float_t Jet1PuppiSDeta                            ;
  Float_t Jet1PuppiSDphi                            ;

  Float_t Jet1PuppiTau1                             ;
  Float_t Jet1PuppiTau2                             ;
  Float_t Jet1PuppiTau3                             ;
  Float_t Jet1PuppiTau4                             ;
  Float_t Jet1PuppiTau32                            ;
  Float_t Jet1PuppiTau21                            ;
  Float_t Jet1PuppiSDsubjet0bdisc                   ;
  Float_t Jet1PuppiSDsubjet1bdisc                   ;
  Float_t Jet1PuppiSDmaxbdisc                       ;
  Float_t Jet1PuppiSDmaxbdiscflavHadron             ;
  Float_t Jet1PuppiSDmaxbdiscflavParton             ;
  Float_t Jet1PuppiSDsubjet0pt                      ;
  Float_t Jet1PuppiSDsubjet0eta                     ;
  Float_t Jet1PuppiSDsubjet0phi                     ;
  Float_t Jet1PuppiSDsubjet0mass                    ;
  Float_t Jet1PuppiSDsubjet0area                    ;
  Float_t Jet1PuppiSDsubjet0flavHadron              ;
  Float_t Jet1PuppiSDsubjet0flavParton              ;
  Float_t Jet1PuppiSDsubjet0tau1                    ;
  Float_t Jet1PuppiSDsubjet0tau2                    ;
  Float_t Jet1PuppiSDsubjet0tau3                    ;
  Float_t Jet1PuppiSDsubjet1pt                      ;
  Float_t Jet1PuppiSDsubjet1eta                     ;
  Float_t Jet1PuppiSDsubjet1phi                     ;
  Float_t Jet1PuppiSDsubjet1mass                    ;
  Float_t Jet1PuppiSDsubjet1area                    ;
  Float_t Jet1PuppiSDsubjet1flavHadron              ;
  Float_t Jet1PuppiSDsubjet1flavParton              ;
  Float_t Jet1PuppiSDsubjet1tau1                    ;
  Float_t Jet1PuppiSDsubjet1tau2                    ;
  Float_t Jet1PuppiSDsubjet1tau3                    ;
  Float_t Jet1CHF                                   ;
  Float_t Jet1NHF                                   ;
  Float_t Jet1CM                                    ;
  Float_t Jet1NM                                    ;
  Float_t Jet1NEF                                   ;
  Float_t Jet1CEF                                   ;
  Float_t Jet1MF                                    ;
  Float_t Jet1Mult                                  ;
  Float_t Jet1MassCorrFactor                        ;
  Float_t Jet1MassCorrFactorUp                      ;
  Float_t Jet1MassCorrFactorDn                      ;
  Float_t Jet1CorrFactor                            ;
  Float_t Jet1CorrFactorUp                          ;
  Float_t Jet1CorrFactorDn                          ;
  Float_t Jet1PtSmearFactor                         ;
  Float_t Jet1PtSmearFactorUp                       ;
  Float_t Jet1PtSmearFactorDn                       ;
  Float_t Jet1PuppiMassCorrFactor                   ;
  Float_t Jet1PuppiMassCorrFactorUp                 ;
  Float_t Jet1PuppiMassCorrFactorDn                 ;
  Float_t Jet1PuppiCorrFactor                       ;
  Float_t Jet1PuppiCorrFactorUp                     ;
  Float_t Jet1PuppiCorrFactorDn                     ;
  Float_t Jet1PuppiPtSmearFactor                    ;
  Float_t Jet1PuppiPtSmearFactorUp                  ;
  Float_t Jet1PuppiPtSmearFactorDn                  ;
  Float_t Jet1EtaScaleFactor                        ;
  Float_t Jet1PhiScaleFactor                        ;
  // Float_t Jet1MatchedGenJetDR                       ;
  Float_t Jet1MatchedGenJetPt                       ;
  Float_t Jet1MatchedGenJetMass                     ;

  Int_t   Jet1GenMatched_TopHadronic                ;
  Float_t Jet1GenMatched_TopPt                      ;
  Float_t Jet1GenMatched_TopEta                     ;
  Float_t Jet1GenMatched_TopPhi                     ;
  Float_t Jet1GenMatched_TopMass                    ;
  Float_t Jet1GenMatched_bPt                        ;
  Float_t Jet1GenMatched_WPt                        ;
  Float_t Jet1GenMatched_Wd1Pt                      ;
  Float_t Jet1GenMatched_Wd2Pt                      ;
  Float_t Jet1GenMatched_Wd1ID                      ;
  Float_t Jet1GenMatched_Wd2ID                      ;
  Float_t Jet1GenMatched_MaxDeltaRPartonTop         ;
  Float_t Jet1GenMatched_MaxDeltaRWPartonTop        ;
  Float_t Jet1GenMatched_MaxDeltaRWPartonW          ;
  Float_t Jet1GenMatched_DeltaR_t_b                 ;
  Float_t Jet1GenMatched_DeltaR_t_W                 ;
  Float_t Jet1GenMatched_DeltaR_t_Wd1               ;
  Float_t Jet1GenMatched_DeltaR_t_Wd2               ;
  Float_t Jet1GenMatched_DeltaR_W_b1                ;
  Float_t Jet1GenMatched_DeltaR_W_Wd1               ;
  Float_t Jet1GenMatched_DeltaR_W_Wd2               ;
  Float_t Jet1GenMatched_DeltaR_Wd1_Wd2             ;
  Float_t Jet1GenMatched_DeltaR_Wd1_b               ;
  Float_t Jet1GenMatched_DeltaR_Wd2_b               ;
  Float_t Jet1GenMatched_DeltaR_jet_t               ;
  Float_t Jet1GenMatched_DeltaR_jet_W               ;
  Float_t Jet1GenMatched_DeltaR_jet_b               ;
  Float_t Jet1GenMatched_DeltaR_jet_Wd1             ;
  Float_t Jet1GenMatched_DeltaR_jet_Wd2             ;
  Float_t Jet1GenMatched_DeltaR_pup0_b              ;
  Float_t Jet1GenMatched_DeltaR_pup0_Wd1            ;
  Float_t Jet1GenMatched_DeltaR_pup0_Wd2            ;
  Float_t Jet1GenMatched_DeltaR_pup1_b              ;
  Float_t Jet1GenMatched_DeltaR_pup1_Wd1            ;
  Float_t Jet1GenMatched_DeltaR_pup1_Wd2            ;      
  Float_t Jet1GenMatched_partonPt                   ;
  Float_t Jet1GenMatched_partonEta                  ;
  Float_t Jet1GenMatched_partonPhi                  ;
  Float_t Jet1GenMatched_partonMass                 ;
  Float_t Jet1GenMatched_partonID                   ;
  Float_t Jet1GenMatched_DeltaRjetParton            ;

  Float_t AllHadMETpx                               ;           
  Float_t AllHadMETpy                               ;           
  Float_t AllHadMETpt                               ;           
  Float_t AllHadMETphi                              ;           
  Float_t AllHadMETsumET                            ;           
  Float_t AllHadNvtx                                ;           
  Float_t AllHadNPUtrue                             ;           
  Float_t AllHadRho                                 ;           
  Float_t AllHadEventWeight                         ;    
  Float_t AllHadPUweight       ; 
  Float_t AllHadPUweight_MBup  ; 
  Float_t AllHadPUweight_MBdn  ;        
  Float_t DijetMass                                 ;           
  Float_t DijetMassPuppi                            ;           
  Float_t DijetDeltaR                               ;           
  Float_t DijetDeltaPhi                             ;           
  Float_t DijetDeltaRap                             ;           
  Float_t DiGenJetMass                              ;           
  Float_t GenTTmass                                 ;           
  Float_t HT                                        ;           
  Float_t HT_CorrDn                                 ;           
  Float_t HT_CorrUp                                 ;           
  Float_t HT_PtSmearNom                             ;           
  Float_t HT_PtSmearUp                              ;           
  Float_t HT_PtSmearDn                              ;           
  Float_t Q2weight_CorrDn                           ;           
  Float_t Q2weight_CorrUp                           ;           
  Float_t NNPDF3weight_CorrDn                       ;           
  Float_t NNPDF3weight_CorrUp                       ;           
  Float_t AllHadRunNum                              ;           
  Float_t AllHadLumiBlock                           ;           
  Float_t AllHadEventNum                            ;    

  std::vector<std::string> *AllHadTrigNames;
  std::vector<int>         *AllHadTrigPrescales = 0;

  TTree *T1    = (TTree*)  F1     ->Get("ana/TreeAllHad");

  double entries = T1->GetEntries();
  cout<<"entries = "<< entries <<endl;


  // T1->SetBranchAddress("AllHadTrigNames",&AllHadTrigNames);
  // T1->SetBranchAddress("AllHadTrigPrescales",&AllHadTrigPrescales);

  T1->SetBranchAddress("PassMETFilters"                        , & PassMETFilters                      );                                  
  T1->SetBranchAddress("Jet0PtRaw"                             , & Jet0PtRaw                           );                                  
  T1->SetBranchAddress("Jet0EtaRaw"                            , & Jet0EtaRaw                          );                                   
  T1->SetBranchAddress("Jet0PhiRaw"                            , & Jet0PhiRaw                          );                                   
  T1->SetBranchAddress("Jet0MassRaw"                           , & Jet0MassRaw                         );                                    
  T1->SetBranchAddress("Jet0P"                                 , & Jet0P                               );                              
  T1->SetBranchAddress("Jet0Pt"                                , & Jet0Pt                              );                               
  T1->SetBranchAddress("Jet0Eta"                               , & Jet0Eta                             );                                
  T1->SetBranchAddress("Jet0Phi"                               , & Jet0Phi                             );                                
  T1->SetBranchAddress("Jet0Rap"                               , & Jet0Rap                             );                                
  T1->SetBranchAddress("Jet0Energy"                            , & Jet0Energy                          );                                   
  T1->SetBranchAddress("Jet0Mass"                              , & Jet0Mass                            );                                 
  T1->SetBranchAddress("Jet0Area"                              , & Jet0Area                            );                                 
  T1->SetBranchAddress("Jet0SDmass"                            , & Jet0SDmass                          );                                         
  T1->SetBranchAddress("Jet0SDmassRaw"                         , & Jet0SDmassRaw                       );                                               
  T1->SetBranchAddress("Jet0SDmassCorrL23"                     , & Jet0SDmassCorrL23                   );                                                    
  T1->SetBranchAddress("Jet0SDmassCorrL23Up"                   , & Jet0SDmassCorrL23Up                 );                                                      
  T1->SetBranchAddress("Jet0SDmassCorrL23Dn"                   , & Jet0SDmassCorrL23Dn                 );                                                      
  T1->SetBranchAddress("Jet0SDmassCorrL123"                    , & Jet0SDmassCorrL123                  );                                                      
  T1->SetBranchAddress("Jet0SDmassCorrL123Up"                  , & Jet0SDmassCorrL123Up                );                                                        
  T1->SetBranchAddress("Jet0SDmassCorrL123Dn"                  , & Jet0SDmassCorrL123Dn                );                                                        
  T1->SetBranchAddress("Jet0SDmassCorrL23Smear"                , & Jet0SDmassCorrL23Smear              );                                                     
  T1->SetBranchAddress("Jet0SDmassCorrL23SmearUp"              , & Jet0SDmassCorrL23SmearUp            );                                                       
  T1->SetBranchAddress("Jet0SDmassCorrL23SmearDn"              , & Jet0SDmassCorrL23SmearDn            );   
  T1->SetBranchAddress("Jet0SDptRaw"                           , & Jet0SDptRaw                         );                                               
  T1->SetBranchAddress("Jet0SDptCorrL23"                       , & Jet0SDptCorrL23                     );                                                    
  T1->SetBranchAddress("Jet0SDptCorrL23Up"                     , & Jet0SDptCorrL23Up                   );                                                      
  T1->SetBranchAddress("Jet0SDptCorrL23Dn"                     , & Jet0SDptCorrL23Dn                   );                                                      
  T1->SetBranchAddress("Jet0SDptCorrL123"                      , & Jet0SDptCorrL123                    );                                                      
  T1->SetBranchAddress("Jet0SDptCorrL123Up"                    , & Jet0SDptCorrL123Up                  );                                                        
  T1->SetBranchAddress("Jet0SDptCorrL123Dn"                    , & Jet0SDptCorrL123Dn                  );                                                        
  T1->SetBranchAddress("Jet0SDptCorrL23Smear"                  , & Jet0SDptCorrL23Smear                );                                                     
  T1->SetBranchAddress("Jet0SDptCorrL23SmearUp"                , & Jet0SDptCorrL23SmearUp              );                                                       
  T1->SetBranchAddress("Jet0SDptCorrL23SmearDn"                , & Jet0SDptCorrL23SmearDn              );                                                     
  T1->SetBranchAddress("Jet0SDetaRaw"                          , & Jet0SDetaRaw                        );                                               
  T1->SetBranchAddress("Jet0SDphiRaw"                          , & Jet0SDphiRaw                        );                                               
  T1->SetBranchAddress("Jet0MassPruned"                        , & Jet0MassPruned                      );                                       
  T1->SetBranchAddress("Jet0MassTrimmed"                       , & Jet0MassTrimmed                     );                                       
  T1->SetBranchAddress("Jet0Tau1"                              , & Jet0Tau1                            );                                 
  T1->SetBranchAddress("Jet0Tau2"                              , & Jet0Tau2                            );                                 
  T1->SetBranchAddress("Jet0Tau3"                              , & Jet0Tau3                            );                                 
  T1->SetBranchAddress("Jet0Tau4"                              , & Jet0Tau4                            );                                 
  T1->SetBranchAddress("Jet0Tau32"                             , & Jet0Tau32                           );                                  
  T1->SetBranchAddress("Jet0Tau21"                             , & Jet0Tau21                           );                                                                      
  T1->SetBranchAddress("Jet0SDmaxbdisc"                        , & Jet0SDmaxbdisc                      );                                       
  T1->SetBranchAddress("Jet0SDmaxbdiscflavHadron"              , & Jet0SDmaxbdiscflavHadron            );                                           
  T1->SetBranchAddress("Jet0SDmaxbdiscflavParton"              , & Jet0SDmaxbdiscflavParton            );                                           
  T1->SetBranchAddress("Jet0SDsubjet0pt"                       , & Jet0SDsubjet0pt                     );                                        
  T1->SetBranchAddress("Jet0SDsubjet0mass"                     , & Jet0SDsubjet0mass                   ); 
  T1->SetBranchAddress("Jet0SDsubjet0eta"                      , & Jet0SDsubjet0eta                    );
  T1->SetBranchAddress("Jet0SDsubjet0phi"                      , & Jet0SDsubjet0phi                    );                                         
  T1->SetBranchAddress("Jet0SDsubjet0area"                     , & Jet0SDsubjet0area                   );                                          
  T1->SetBranchAddress("Jet0SDsubjet0flavHadron"               , & Jet0SDsubjet0flavHadron             );                                          
  T1->SetBranchAddress("Jet0SDsubjet0flavParton"               , & Jet0SDsubjet0flavParton             ); 
  T1->SetBranchAddress("Jet0SDsubjet0tau1"                     , & Jet0SDsubjet0tau1                   );
  T1->SetBranchAddress("Jet0SDsubjet0tau2"                     , & Jet0SDsubjet0tau2                   );
  T1->SetBranchAddress("Jet0SDsubjet0tau3"                     , & Jet0SDsubjet0tau3                   ); 
  T1->SetBranchAddress("Jet0SDsubjet0bdisc"                    , & Jet0SDsubjet0bdisc                  );                                     
  T1->SetBranchAddress("Jet0SDsubjet1pt"                       , & Jet0SDsubjet1pt                     );                                        
  T1->SetBranchAddress("Jet0SDsubjet1mass"                     , & Jet0SDsubjet1mass                   );  
  T1->SetBranchAddress("Jet0SDsubjet1eta"                      , & Jet0SDsubjet1eta                    );
  T1->SetBranchAddress("Jet0SDsubjet1phi"                      , & Jet0SDsubjet1phi                    );                                        
  T1->SetBranchAddress("Jet0SDsubjet1area"                     , & Jet0SDsubjet1area                   );                                          
  T1->SetBranchAddress("Jet0SDsubjet1flavHadron"               , & Jet0SDsubjet1flavHadron             );                                          
  T1->SetBranchAddress("Jet0SDsubjet1flavParton"               , & Jet0SDsubjet1flavParton             ); 
  T1->SetBranchAddress("Jet0SDsubjet1tau1"                     , & Jet0SDsubjet1tau1                   );
  T1->SetBranchAddress("Jet0SDsubjet1tau2"                     , & Jet0SDsubjet1tau2                   );
  T1->SetBranchAddress("Jet0SDsubjet1tau3"                     , & Jet0SDsubjet1tau3                   );  
  T1->SetBranchAddress("Jet0SDsubjet1bdisc"                    , & Jet0SDsubjet1bdisc                  );                                                                                    
  T1->SetBranchAddress("Jet0PuppiPt"                           , & Jet0PuppiPt                         );                                    
  T1->SetBranchAddress("Jet0PuppiEta"                          , & Jet0PuppiEta                        );                                     
  T1->SetBranchAddress("Jet0PuppiPhi"                          , & Jet0PuppiPhi                        );                                     
  T1->SetBranchAddress("Jet0PuppiMass"                         , & Jet0PuppiMass                       );                                      

  T1->SetBranchAddress("Jet0PuppiSDmass"                       , & Jet0PuppiSDmass                     );
  T1->SetBranchAddress("Jet0PuppiSDmassCorr"                   , & Jet0PuppiSDmassCorr                 );
  T1->SetBranchAddress("Jet0PuppiSDmassCorrUp"                 , & Jet0PuppiSDmassCorrUp               );
  T1->SetBranchAddress("Jet0PuppiSDmassCorrDn"                 , & Jet0PuppiSDmassCorrDn               );
  T1->SetBranchAddress("Jet0PuppiSDmassCorrL23Smear"           , & Jet0PuppiSDmassCorrL23Smear         );
  T1->SetBranchAddress("Jet0PuppiSDmassCorrL23SmearUp"         , & Jet0PuppiSDmassCorrL23SmearUp       );
  T1->SetBranchAddress("Jet0PuppiSDmassCorrL23SmearDn"         , & Jet0PuppiSDmassCorrL23SmearDn       );
  T1->SetBranchAddress("Jet0PuppiSDpt"                         , & Jet0PuppiSDpt                       );
  T1->SetBranchAddress("Jet0PuppiSDptCorr"                     , & Jet0PuppiSDptCorr                   );
  T1->SetBranchAddress("Jet0PuppiSDptCorrUp"                   , & Jet0PuppiSDptCorrUp                 );
  T1->SetBranchAddress("Jet0PuppiSDptCorrDn"                   , & Jet0PuppiSDptCorrDn                 );
  T1->SetBranchAddress("Jet0PuppiSDptCorrL23Smear"             , & Jet0PuppiSDptCorrL23Smear           );
  T1->SetBranchAddress("Jet0PuppiSDptCorrL23SmearUp"           , & Jet0PuppiSDptCorrL23SmearUp         );
  T1->SetBranchAddress("Jet0PuppiSDptCorrL23SmearDn"           , & Jet0PuppiSDptCorrL23SmearDn         );
  T1->SetBranchAddress("Jet0PuppiSDeta"                        , & Jet0PuppiSDeta                      );
  T1->SetBranchAddress("Jet0PuppiSDphi"                        , & Jet0PuppiSDphi                      );
                                                         
  T1->SetBranchAddress("Jet0PuppiTau1"                         , & Jet0PuppiTau1                       );                                      
  T1->SetBranchAddress("Jet0PuppiTau2"                         , & Jet0PuppiTau2                       );                                      
  T1->SetBranchAddress("Jet0PuppiTau3"                         , & Jet0PuppiTau3                       );                                      
  T1->SetBranchAddress("Jet0PuppiTau4"                         , & Jet0PuppiTau4                       );                                      
  T1->SetBranchAddress("Jet0PuppiTau32"                        , & Jet0PuppiTau32                      );                                       
  T1->SetBranchAddress("Jet0PuppiTau21"                        , & Jet0PuppiTau21                      );                                                                                
  T1->SetBranchAddress("Jet0PuppiSDmaxbdisc"                   , & Jet0PuppiSDmaxbdisc                 );                                            
  T1->SetBranchAddress("Jet0PuppiSDmaxbdiscflavHadron"         , & Jet0PuppiSDmaxbdiscflavHadron       );                                                
  T1->SetBranchAddress("Jet0PuppiSDmaxbdiscflavParton"         , & Jet0PuppiSDmaxbdiscflavParton       );                                                
  T1->SetBranchAddress("Jet0PuppiSDsubjet0pt"                  , & Jet0PuppiSDsubjet0pt                );                                             
  T1->SetBranchAddress("Jet0PuppiSDsubjet0mass"                , & Jet0PuppiSDsubjet0mass              );    
  T1->SetBranchAddress("Jet0PuppiSDsubjet0eta"                 , & Jet0PuppiSDsubjet0eta               );
  T1->SetBranchAddress("Jet0PuppiSDsubjet0phi"                 , & Jet0PuppiSDsubjet0phi               );                                           
  T1->SetBranchAddress("Jet0PuppiSDsubjet0area"                , & Jet0PuppiSDsubjet0area              );                                               
  T1->SetBranchAddress("Jet0PuppiSDsubjet0flavHadron"          , & Jet0PuppiSDsubjet0flavHadron        );                                               
  T1->SetBranchAddress("Jet0PuppiSDsubjet0flavParton"          , & Jet0PuppiSDsubjet0flavParton        ); 
  T1->SetBranchAddress("Jet0PuppiSDsubjet0tau1"                , & Jet0PuppiSDsubjet0tau1              );
  T1->SetBranchAddress("Jet0PuppiSDsubjet0tau2"                , & Jet0PuppiSDsubjet0tau2              );
  T1->SetBranchAddress("Jet0PuppiSDsubjet0tau3"                , & Jet0PuppiSDsubjet0tau3              ); 
  T1->SetBranchAddress("Jet0PuppiSDsubjet0bdisc"               , & Jet0PuppiSDsubjet0bdisc             );                                          
  T1->SetBranchAddress("Jet0PuppiSDsubjet1pt"                  , & Jet0PuppiSDsubjet1pt                );                                             
  T1->SetBranchAddress("Jet0PuppiSDsubjet1mass"                , & Jet0PuppiSDsubjet1mass              );  
  T1->SetBranchAddress("Jet0PuppiSDsubjet1eta"                 , & Jet0PuppiSDsubjet1eta               );
  T1->SetBranchAddress("Jet0PuppiSDsubjet1phi"                 , & Jet0PuppiSDsubjet1phi               );                                             
  T1->SetBranchAddress("Jet0PuppiSDsubjet1area"                , & Jet0PuppiSDsubjet1area              );                                               
  T1->SetBranchAddress("Jet0PuppiSDsubjet1flavHadron"          , & Jet0PuppiSDsubjet1flavHadron        );                                               
  T1->SetBranchAddress("Jet0PuppiSDsubjet1flavParton"          , & Jet0PuppiSDsubjet1flavParton        );    
  T1->SetBranchAddress("Jet0PuppiSDsubjet1tau1"                , & Jet0PuppiSDsubjet1tau1              );
  T1->SetBranchAddress("Jet0PuppiSDsubjet1tau2"                , & Jet0PuppiSDsubjet1tau2              );
  T1->SetBranchAddress("Jet0PuppiSDsubjet1tau3"                , & Jet0PuppiSDsubjet1tau3              ); 
  T1->SetBranchAddress("Jet0PuppiSDsubjet1bdisc"               , & Jet0PuppiSDsubjet1bdisc             );                                                                                          
  T1->SetBranchAddress("Jet0CHF"                               , & Jet0CHF                             );                                
  T1->SetBranchAddress("Jet0NHF"                               , & Jet0NHF                             );                                
  T1->SetBranchAddress("Jet0CM"                                , & Jet0CM                              );                               
  T1->SetBranchAddress("Jet0NM"                                , & Jet0NM                              );                               
  T1->SetBranchAddress("Jet0NEF"                               , & Jet0NEF                             );                                
  T1->SetBranchAddress("Jet0CEF"                               , & Jet0CEF                             );                                
  T1->SetBranchAddress("Jet0MF"                                , & Jet0MF                              );                               
  T1->SetBranchAddress("Jet0Mult"                              , & Jet0Mult                            );                                 
  T1->SetBranchAddress("Jet0MassCorrFactor"                    , & Jet0MassCorrFactor                  );                                           
  T1->SetBranchAddress("Jet0MassCorrFactorUp"                  , & Jet0MassCorrFactorUp                );                                             
  T1->SetBranchAddress("Jet0MassCorrFactorDn"                  , & Jet0MassCorrFactorDn                );                                             
  T1->SetBranchAddress("Jet0CorrFactor"                        , & Jet0CorrFactor                      );                                       
  T1->SetBranchAddress("Jet0CorrFactorUp"                      , & Jet0CorrFactorUp                    );                                         
  T1->SetBranchAddress("Jet0CorrFactorDn"                      , & Jet0CorrFactorDn                    );                                         
  T1->SetBranchAddress("Jet0PtSmearFactor"                     , & Jet0PtSmearFactor                   );                                          
  T1->SetBranchAddress("Jet0PtSmearFactorUp"                   , & Jet0PtSmearFactorUp                 );                                            
  T1->SetBranchAddress("Jet0PtSmearFactorDn"                   , & Jet0PtSmearFactorDn                 );                                            
  T1->SetBranchAddress("Jet0PuppiMassCorrFactor"               , & Jet0PuppiMassCorrFactor             );                                                
  T1->SetBranchAddress("Jet0PuppiMassCorrFactorUp"             , & Jet0PuppiMassCorrFactorUp           );                                                  
  T1->SetBranchAddress("Jet0PuppiMassCorrFactorDn"             , & Jet0PuppiMassCorrFactorDn           );                                                  
  T1->SetBranchAddress("Jet0PuppiCorrFactor"                   , & Jet0PuppiCorrFactor                 );                                            
  T1->SetBranchAddress("Jet0PuppiCorrFactorUp"                 , & Jet0PuppiCorrFactorUp               );                                              
  T1->SetBranchAddress("Jet0PuppiCorrFactorDn"                 , & Jet0PuppiCorrFactorDn               );                                              
  T1->SetBranchAddress("Jet0PuppiPtSmearFactor"                , & Jet0PuppiPtSmearFactor              );                                               
  T1->SetBranchAddress("Jet0PuppiPtSmearFactorUp"              , & Jet0PuppiPtSmearFactorUp            );                                                 
  T1->SetBranchAddress("Jet0PuppiPtSmearFactorDn"              , & Jet0PuppiPtSmearFactorDn            );                                                 
  T1->SetBranchAddress("Jet0EtaScaleFactor"                    , & Jet0EtaScaleFactor                  );                                           
  T1->SetBranchAddress("Jet0PhiScaleFactor"                    , & Jet0PhiScaleFactor                  );                                           
  //  T1->SetBranchAddress("Jet0MatchedGenJetDR"                   , & Jet0MatchedGenJetDR                 );                                            
  T1->SetBranchAddress("Jet0MatchedGenJetPt"                   , & Jet0MatchedGenJetPt                 );                                            
  T1->SetBranchAddress("Jet0MatchedGenJetMass"                 , & Jet0MatchedGenJetMass               );  

  T1->SetBranchAddress("Jet0GenMatched_TopHadronic"            , & Jet0GenMatched_TopHadronic          );      
  T1->SetBranchAddress("Jet0GenMatched_TopPt"                  , & Jet0GenMatched_TopPt                );      
  T1->SetBranchAddress("Jet0GenMatched_TopEta"                 , & Jet0GenMatched_TopEta               );      
  T1->SetBranchAddress("Jet0GenMatched_TopPhi"                 , & Jet0GenMatched_TopPhi               );      
  T1->SetBranchAddress("Jet0GenMatched_TopMass"                , & Jet0GenMatched_TopMass              );      
  T1->SetBranchAddress("Jet0GenMatched_bPt"                    , & Jet0GenMatched_bPt                  );      
  T1->SetBranchAddress("Jet0GenMatched_WPt"                    , & Jet0GenMatched_WPt                  );      
  T1->SetBranchAddress("Jet0GenMatched_Wd1Pt"                  , & Jet0GenMatched_Wd1Pt                );      
  T1->SetBranchAddress("Jet0GenMatched_Wd2Pt"                  , & Jet0GenMatched_Wd2Pt                );      
  T1->SetBranchAddress("Jet0GenMatched_Wd1ID"                  , & Jet0GenMatched_Wd1ID                );      
  T1->SetBranchAddress("Jet0GenMatched_Wd2ID"                  , & Jet0GenMatched_Wd2ID                );      
  T1->SetBranchAddress("Jet0GenMatched_MaxDeltaRPartonTop"     , & Jet0GenMatched_MaxDeltaRPartonTop   );      
  T1->SetBranchAddress("Jet0GenMatched_MaxDeltaRWPartonTop"    , & Jet0GenMatched_MaxDeltaRWPartonTop  );      
  T1->SetBranchAddress("Jet0GenMatched_MaxDeltaRWPartonW"      , & Jet0GenMatched_MaxDeltaRWPartonW    );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_t_b"             , & Jet0GenMatched_DeltaR_t_b           );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_t_W"             , & Jet0GenMatched_DeltaR_t_W           );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_t_Wd1"           , & Jet0GenMatched_DeltaR_t_Wd1         );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_t_Wd2"           , & Jet0GenMatched_DeltaR_t_Wd2         );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_W_b1"            , & Jet0GenMatched_DeltaR_W_b1          );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_W_Wd1"           , & Jet0GenMatched_DeltaR_W_Wd1         );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_W_Wd2"           , & Jet0GenMatched_DeltaR_W_Wd2         );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_Wd1_Wd2"         , & Jet0GenMatched_DeltaR_Wd1_Wd2       );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_Wd1_b"           , & Jet0GenMatched_DeltaR_Wd1_b         );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_Wd2_b"           , & Jet0GenMatched_DeltaR_Wd2_b         );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_jet_t"           , & Jet0GenMatched_DeltaR_jet_t         );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_jet_W"           , & Jet0GenMatched_DeltaR_jet_W         );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_jet_b"           , & Jet0GenMatched_DeltaR_jet_b         );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_jet_Wd1"         , & Jet0GenMatched_DeltaR_jet_Wd1       );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_jet_Wd2"         , & Jet0GenMatched_DeltaR_jet_Wd2       );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_pup0_b"          , & Jet0GenMatched_DeltaR_pup0_b        );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_pup0_Wd1"        , & Jet0GenMatched_DeltaR_pup0_Wd1      );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_pup0_Wd2"        , & Jet0GenMatched_DeltaR_pup0_Wd2      );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_pup1_b"          , & Jet0GenMatched_DeltaR_pup1_b        );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_pup1_Wd1"        , & Jet0GenMatched_DeltaR_pup1_Wd1      );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaR_pup1_Wd2"        , & Jet0GenMatched_DeltaR_pup1_Wd2      );               
  T1->SetBranchAddress("Jet0GenMatched_partonPt"               , & Jet0GenMatched_partonPt             );      
  T1->SetBranchAddress("Jet0GenMatched_partonEta"              , & Jet0GenMatched_partonEta            );      
  T1->SetBranchAddress("Jet0GenMatched_partonPhi"              , & Jet0GenMatched_partonPhi            );      
  T1->SetBranchAddress("Jet0GenMatched_partonMass"             , & Jet0GenMatched_partonMass           );      
  T1->SetBranchAddress("Jet0GenMatched_partonID"               , & Jet0GenMatched_partonID             );      
  T1->SetBranchAddress("Jet0GenMatched_DeltaRjetParton"        , & Jet0GenMatched_DeltaRjetParton      );      
  std::cout<<"Setup Jet0 in tree"<<std::endl;

  T1->SetBranchAddress("Jet1PtRaw"                             , & Jet1PtRaw                           );                                  
  T1->SetBranchAddress("Jet1EtaRaw"                            , & Jet1EtaRaw                          );                                   
  T1->SetBranchAddress("Jet1PhiRaw"                            , & Jet1PhiRaw                          );                                   
  T1->SetBranchAddress("Jet1MassRaw"                           , & Jet1MassRaw                         );                                    
  T1->SetBranchAddress("Jet1P"                                 , & Jet1P                               );                              
  T1->SetBranchAddress("Jet1Pt"                                , & Jet1Pt                              );                               
  T1->SetBranchAddress("Jet1Eta"                               , & Jet1Eta                             );                                
  T1->SetBranchAddress("Jet1Phi"                               , & Jet1Phi                             );                                
  T1->SetBranchAddress("Jet1Rap"                               , & Jet1Rap                             );                                
  T1->SetBranchAddress("Jet1Energy"                            , & Jet1Energy                          );                                   
  T1->SetBranchAddress("Jet1Mass"                              , & Jet1Mass                            );                                 
  T1->SetBranchAddress("Jet1Area"                              , & Jet1Area                            );                                 
  T1->SetBranchAddress("Jet1SDmass"                            , & Jet1SDmass                          );                                         
  T1->SetBranchAddress("Jet1SDmassRaw"                         , & Jet1SDmassRaw                       );                                               
  T1->SetBranchAddress("Jet1SDmassCorrL23"                     , & Jet1SDmassCorrL23                   );                                                    
  T1->SetBranchAddress("Jet1SDmassCorrL23Up"                   , & Jet1SDmassCorrL23Up                 );                                                      
  T1->SetBranchAddress("Jet1SDmassCorrL23Dn"                   , & Jet1SDmassCorrL23Dn                 );                                                      
  T1->SetBranchAddress("Jet1SDmassCorrL123"                    , & Jet1SDmassCorrL123                  );                                                      
  T1->SetBranchAddress("Jet1SDmassCorrL123Up"                  , & Jet1SDmassCorrL123Up                );                                                        
  T1->SetBranchAddress("Jet1SDmassCorrL123Dn"                  , & Jet1SDmassCorrL123Dn                );                                                        
  T1->SetBranchAddress("Jet1SDmassCorrL23Smear"                   , & Jet1SDmassCorrL23Smear                    );                                                     
  T1->SetBranchAddress("Jet1SDmassCorrL23SmearUp"                 , & Jet1SDmassCorrL23SmearUp                  );                                                       
  T1->SetBranchAddress("Jet1SDmassCorrL23SmearDn"                 , & Jet1SDmassCorrL23SmearDn                  );   
  T1->SetBranchAddress("Jet1SDptRaw"                           , & Jet1SDptRaw                         );                                               
  T1->SetBranchAddress("Jet1SDptCorrL23"                       , & Jet1SDptCorrL23                     );                                                    
  T1->SetBranchAddress("Jet1SDptCorrL23Up"                     , & Jet1SDptCorrL23Up                   );                                                      
  T1->SetBranchAddress("Jet1SDptCorrL23Dn"                     , & Jet1SDptCorrL23Dn                   );                                                      
  T1->SetBranchAddress("Jet1SDptCorrL123"                      , & Jet1SDptCorrL123                    );                                                      
  T1->SetBranchAddress("Jet1SDptCorrL123Up"                    , & Jet1SDptCorrL123Up                  );                                                        
  T1->SetBranchAddress("Jet1SDptCorrL123Dn"                    , & Jet1SDptCorrL123Dn                  );                                                        
  T1->SetBranchAddress("Jet1SDptCorrL23Smear"                     , & Jet1SDptCorrL23Smear                      );                                                     
  T1->SetBranchAddress("Jet1SDptCorrL23SmearUp"                   , & Jet1SDptCorrL23SmearUp                    );                                                       
  T1->SetBranchAddress("Jet1SDptCorrL23SmearDn"                   , & Jet1SDptCorrL23SmearDn                    );                                                     
  T1->SetBranchAddress("Jet1SDetaRaw"                          , & Jet1SDetaRaw                        );                                               
  T1->SetBranchAddress("Jet1SDphiRaw"                          , & Jet1SDphiRaw                        );  

  T1->SetBranchAddress("Jet1MassPruned"                        , & Jet1MassPruned                      );                                       
  T1->SetBranchAddress("Jet1MassTrimmed"                       , & Jet1MassTrimmed                      );                                       
  T1->SetBranchAddress("Jet1Tau1"                              , & Jet1Tau1                            );                                 
  T1->SetBranchAddress("Jet1Tau2"                              , & Jet1Tau2                            );                                 
  T1->SetBranchAddress("Jet1Tau3"                              , & Jet1Tau3                            );                                 
  T1->SetBranchAddress("Jet1Tau4"                              , & Jet1Tau4                            );                                 
  T1->SetBranchAddress("Jet1Tau32"                             , & Jet1Tau32                           );                                  
  T1->SetBranchAddress("Jet1Tau21"                             , & Jet1Tau21                           );                                                                      
  T1->SetBranchAddress("Jet1SDmaxbdisc"                        , & Jet1SDmaxbdisc                      );                                       
  T1->SetBranchAddress("Jet1SDmaxbdiscflavHadron"              , & Jet1SDmaxbdiscflavHadron            );                                           
  T1->SetBranchAddress("Jet1SDmaxbdiscflavParton"              , & Jet1SDmaxbdiscflavParton            );                                           
  T1->SetBranchAddress("Jet1SDsubjet0pt"                       , & Jet1SDsubjet0pt                     );                                        
  T1->SetBranchAddress("Jet1SDsubjet0mass"                     , & Jet1SDsubjet0mass                   ); 
  T1->SetBranchAddress("Jet1SDsubjet0eta"                      , & Jet1SDsubjet0eta                    );
  T1->SetBranchAddress("Jet1SDsubjet0phi"                      , & Jet1SDsubjet0phi                    );                                         
  T1->SetBranchAddress("Jet1SDsubjet0area"                     , & Jet1SDsubjet0area                   );                                          
  T1->SetBranchAddress("Jet1SDsubjet0flavHadron"               , & Jet1SDsubjet0flavHadron             );                                          
  T1->SetBranchAddress("Jet1SDsubjet0flavParton"               , & Jet1SDsubjet0flavParton             ); 
  T1->SetBranchAddress("Jet1SDsubjet0tau1"                     , & Jet1SDsubjet0tau1                   );
  T1->SetBranchAddress("Jet1SDsubjet0tau2"                     , & Jet1SDsubjet0tau2                   );
  T1->SetBranchAddress("Jet1SDsubjet0tau3"                     , & Jet1SDsubjet0tau3                   );
  T1->SetBranchAddress("Jet1SDsubjet0bdisc"                    , & Jet1SDsubjet0bdisc                  );                                     
  T1->SetBranchAddress("Jet1SDsubjet1pt"                       , & Jet1SDsubjet1pt                     );                                        
  T1->SetBranchAddress("Jet1SDsubjet1mass"                     , & Jet1SDsubjet1mass                   );  
  T1->SetBranchAddress("Jet1SDsubjet1eta"                      , & Jet1SDsubjet1eta                    );
  T1->SetBranchAddress("Jet1SDsubjet1phi"                      , & Jet1SDsubjet1phi                    );                                        
  T1->SetBranchAddress("Jet1SDsubjet1area"                     , & Jet1SDsubjet1area                   );                                          
  T1->SetBranchAddress("Jet1SDsubjet1flavHadron"               , & Jet1SDsubjet1flavHadron             );                                          
  T1->SetBranchAddress("Jet1SDsubjet1flavParton"               , & Jet1SDsubjet1flavParton             ); 
  T1->SetBranchAddress("Jet1SDsubjet1tau1"                     , & Jet1SDsubjet1tau1                   );
  T1->SetBranchAddress("Jet1SDsubjet1tau2"                     , & Jet1SDsubjet1tau2                   );
  T1->SetBranchAddress("Jet1SDsubjet1tau3"                     , & Jet1SDsubjet1tau3                   ); 
  T1->SetBranchAddress("Jet1SDsubjet1bdisc"                    , & Jet1SDsubjet1bdisc                  );                                                                                    
  T1->SetBranchAddress("Jet1PuppiPt"                           , & Jet1PuppiPt                         );                                    
  T1->SetBranchAddress("Jet1PuppiEta"                          , & Jet1PuppiEta                        );                                     
  T1->SetBranchAddress("Jet1PuppiPhi"                          , & Jet1PuppiPhi                        );                                     
  T1->SetBranchAddress("Jet1PuppiMass"                         , & Jet1PuppiMass                       );                                      

  T1->SetBranchAddress("Jet1PuppiSDmass"                       , & Jet1PuppiSDmass                     );
  T1->SetBranchAddress("Jet1PuppiSDmassCorr"                   , & Jet1PuppiSDmassCorr                 );
  T1->SetBranchAddress("Jet1PuppiSDmassCorrUp"                 , & Jet1PuppiSDmassCorrUp               );
  T1->SetBranchAddress("Jet1PuppiSDmassCorrDn"                 , & Jet1PuppiSDmassCorrDn               );
  T1->SetBranchAddress("Jet1PuppiSDmassCorrL23Smear"           , & Jet1PuppiSDmassCorrL23Smear         );
  T1->SetBranchAddress("Jet1PuppiSDmassCorrL23SmearUp"         , & Jet1PuppiSDmassCorrL23SmearUp       );
  T1->SetBranchAddress("Jet1PuppiSDmassCorrL23SmearDn"         , & Jet1PuppiSDmassCorrL23SmearDn       );
  T1->SetBranchAddress("Jet1PuppiSDpt"                         , & Jet1PuppiSDpt                       );
  T1->SetBranchAddress("Jet1PuppiSDptCorr"                     , & Jet1PuppiSDptCorr                   );
  T1->SetBranchAddress("Jet1PuppiSDptCorrUp"                   , & Jet1PuppiSDptCorrUp                 );
  T1->SetBranchAddress("Jet1PuppiSDptCorrDn"                   , & Jet1PuppiSDptCorrDn                 );
  T1->SetBranchAddress("Jet1PuppiSDptCorrL23Smear"             , & Jet1PuppiSDptCorrL23Smear           );
  T1->SetBranchAddress("Jet1PuppiSDptCorrL23SmearUp"           , & Jet1PuppiSDptCorrL23SmearUp         );
  T1->SetBranchAddress("Jet1PuppiSDptCorrL23SmearDn"           , & Jet1PuppiSDptCorrL23SmearDn         );
  T1->SetBranchAddress("Jet1PuppiSDeta"                        , & Jet1PuppiSDeta                      );
  T1->SetBranchAddress("Jet1PuppiSDphi"                        , & Jet1PuppiSDphi                      );
                       
  T1->SetBranchAddress("Jet1PuppiTau1"                         , & Jet1PuppiTau1                       );                                      
  T1->SetBranchAddress("Jet1PuppiTau2"                         , & Jet1PuppiTau2                       );                                      
  T1->SetBranchAddress("Jet1PuppiTau3"                         , & Jet1PuppiTau3                       );                                      
  T1->SetBranchAddress("Jet1PuppiTau4"                         , & Jet1PuppiTau4                       );                                      
  T1->SetBranchAddress("Jet1PuppiTau32"                        , & Jet1PuppiTau32                      );                                       
  T1->SetBranchAddress("Jet1PuppiTau21"                        , & Jet1PuppiTau21                      );                                       
  T1->SetBranchAddress("Jet1PuppiSDmaxbdisc"                   , & Jet1PuppiSDmaxbdisc                 );                                            
  T1->SetBranchAddress("Jet1PuppiSDmaxbdiscflavHadron"         , & Jet1PuppiSDmaxbdiscflavHadron       );                                                
  T1->SetBranchAddress("Jet1PuppiSDmaxbdiscflavParton"         , & Jet1PuppiSDmaxbdiscflavParton       );                                                
  T1->SetBranchAddress("Jet1PuppiSDsubjet0pt"                  , & Jet1PuppiSDsubjet0pt                );                                             
  T1->SetBranchAddress("Jet1PuppiSDsubjet0mass"                , & Jet1PuppiSDsubjet0mass              );    
  T1->SetBranchAddress("Jet1PuppiSDsubjet0eta"                 , & Jet1PuppiSDsubjet0eta               );
  T1->SetBranchAddress("Jet1PuppiSDsubjet0phi"                 , & Jet1PuppiSDsubjet0phi               );                                           
  T1->SetBranchAddress("Jet1PuppiSDsubjet0area"                , & Jet1PuppiSDsubjet0area              );                                               
  T1->SetBranchAddress("Jet1PuppiSDsubjet0flavHadron"          , & Jet1PuppiSDsubjet0flavHadron        );                                               
  T1->SetBranchAddress("Jet1PuppiSDsubjet0flavParton"          , & Jet1PuppiSDsubjet0flavParton        ); 
  T1->SetBranchAddress("Jet1PuppiSDsubjet0tau1"                , & Jet1PuppiSDsubjet0tau1              );
  T1->SetBranchAddress("Jet1PuppiSDsubjet0tau2"                , & Jet1PuppiSDsubjet0tau2              );
  T1->SetBranchAddress("Jet1PuppiSDsubjet0tau3"                , & Jet1PuppiSDsubjet0tau3              );
  T1->SetBranchAddress("Jet1PuppiSDsubjet0bdisc"               , & Jet1PuppiSDsubjet0bdisc             );                                                                                         
  T1->SetBranchAddress("Jet1PuppiSDsubjet1pt"                  , & Jet1PuppiSDsubjet1pt                );                                             
  T1->SetBranchAddress("Jet1PuppiSDsubjet1mass"                , & Jet1PuppiSDsubjet1mass              );  
  T1->SetBranchAddress("Jet1PuppiSDsubjet1eta"                 , & Jet1PuppiSDsubjet1eta               );
  T1->SetBranchAddress("Jet1PuppiSDsubjet1phi"                 , & Jet1PuppiSDsubjet1phi               );                                             
  T1->SetBranchAddress("Jet1PuppiSDsubjet1area"                , & Jet1PuppiSDsubjet1area              );                                               
  T1->SetBranchAddress("Jet1PuppiSDsubjet1flavHadron"          , & Jet1PuppiSDsubjet1flavHadron        );                                               
  T1->SetBranchAddress("Jet1PuppiSDsubjet1flavParton"          , & Jet1PuppiSDsubjet1flavParton        );    
  T1->SetBranchAddress("Jet1PuppiSDsubjet1tau1"                , & Jet1PuppiSDsubjet1tau1              );
  T1->SetBranchAddress("Jet1PuppiSDsubjet1tau2"                , & Jet1PuppiSDsubjet1tau2              );
  T1->SetBranchAddress("Jet1PuppiSDsubjet1tau3"                , & Jet1PuppiSDsubjet1tau3              ); 
  T1->SetBranchAddress("Jet1PuppiSDsubjet1bdisc"               , & Jet1PuppiSDsubjet1bdisc             );                                                                                       
  T1->SetBranchAddress("Jet1CHF"                               , & Jet1CHF                             );                                
  T1->SetBranchAddress("Jet1NHF"                               , & Jet1NHF                             );                                
  T1->SetBranchAddress("Jet1CM"                                , & Jet1CM                              );                               
  T1->SetBranchAddress("Jet1NM"                                , & Jet1NM                              );                               
  T1->SetBranchAddress("Jet1NEF"                               , & Jet1NEF                             );                                
  T1->SetBranchAddress("Jet1CEF"                               , & Jet1CEF                             );                                
  T1->SetBranchAddress("Jet1MF"                                , & Jet1MF                              );                               
  T1->SetBranchAddress("Jet1Mult"                              , & Jet1Mult                            );                                 
  T1->SetBranchAddress("Jet1MassCorrFactor"                    , & Jet1MassCorrFactor                  );                                           
  T1->SetBranchAddress("Jet1MassCorrFactorUp"                  , & Jet1MassCorrFactorUp                );                                             
  T1->SetBranchAddress("Jet1MassCorrFactorDn"                  , & Jet1MassCorrFactorDn                );                                             
  T1->SetBranchAddress("Jet1CorrFactor"                        , & Jet1CorrFactor                      );                                       
  T1->SetBranchAddress("Jet1CorrFactorUp"                      , & Jet1CorrFactorUp                    );                                         
  T1->SetBranchAddress("Jet1CorrFactorDn"                      , & Jet1CorrFactorDn                    );                                         
  T1->SetBranchAddress("Jet1PtSmearFactor"                     , & Jet1PtSmearFactor                   );                                          
  T1->SetBranchAddress("Jet1PtSmearFactorUp"                   , & Jet1PtSmearFactorUp                 );                                            
  T1->SetBranchAddress("Jet1PtSmearFactorDn"                   , & Jet1PtSmearFactorDn                 );                                            
  T1->SetBranchAddress("Jet1PuppiMassCorrFactor"               , & Jet1PuppiMassCorrFactor             );                                                
  T1->SetBranchAddress("Jet1PuppiMassCorrFactorUp"             , & Jet1PuppiMassCorrFactorUp           );                                                  
  T1->SetBranchAddress("Jet1PuppiMassCorrFactorDn"             , & Jet1PuppiMassCorrFactorDn           );                                                  
  T1->SetBranchAddress("Jet1PuppiCorrFactor"                   , & Jet1PuppiCorrFactor                 );                                            
  T1->SetBranchAddress("Jet1PuppiCorrFactorUp"                 , & Jet1PuppiCorrFactorUp               );                                              
  T1->SetBranchAddress("Jet1PuppiCorrFactorDn"                 , & Jet1PuppiCorrFactorDn               );                                              
  T1->SetBranchAddress("Jet1PuppiPtSmearFactor"                , & Jet1PuppiPtSmearFactor              );                                               
  T1->SetBranchAddress("Jet1PuppiPtSmearFactorUp"              , & Jet1PuppiPtSmearFactorUp            );                                                 
  T1->SetBranchAddress("Jet1PuppiPtSmearFactorDn"              , & Jet1PuppiPtSmearFactorDn            );                                                 
  T1->SetBranchAddress("Jet1EtaScaleFactor"                    , & Jet1EtaScaleFactor                  );                                           
  T1->SetBranchAddress("Jet1PhiScaleFactor"                    , & Jet1PhiScaleFactor                  );                                           
  //  T1->SetBranchAddress("Jet1MatchedGenJetDR"                   , & Jet1MatchedGenJetDR                 );                                            
  T1->SetBranchAddress("Jet1MatchedGenJetPt"                   , & Jet1MatchedGenJetPt                 );                                            
  T1->SetBranchAddress("Jet1MatchedGenJetMass"                 , & Jet1MatchedGenJetMass               ); 
                      
  T1->SetBranchAddress("Jet1GenMatched_TopHadronic"            , & Jet1GenMatched_TopHadronic          );      
  T1->SetBranchAddress("Jet1GenMatched_TopPt"                  , & Jet1GenMatched_TopPt                );      
  T1->SetBranchAddress("Jet1GenMatched_TopEta"                 , & Jet1GenMatched_TopEta               );      
  T1->SetBranchAddress("Jet1GenMatched_TopPhi"                 , & Jet1GenMatched_TopPhi               );      
  T1->SetBranchAddress("Jet1GenMatched_TopMass"                , & Jet1GenMatched_TopMass              );      
  T1->SetBranchAddress("Jet1GenMatched_bPt"                    , & Jet1GenMatched_bPt                  );      
  T1->SetBranchAddress("Jet1GenMatched_WPt"                    , & Jet1GenMatched_WPt                  );      
  T1->SetBranchAddress("Jet1GenMatched_Wd1Pt"                  , & Jet1GenMatched_Wd1Pt                );      
  T1->SetBranchAddress("Jet1GenMatched_Wd2Pt"                  , & Jet1GenMatched_Wd2Pt                );      
  T1->SetBranchAddress("Jet1GenMatched_Wd1ID"                  , & Jet1GenMatched_Wd1ID                );      
  T1->SetBranchAddress("Jet1GenMatched_Wd2ID"                  , & Jet1GenMatched_Wd2ID                );      
  T1->SetBranchAddress("Jet1GenMatched_MaxDeltaRPartonTop"     , & Jet1GenMatched_MaxDeltaRPartonTop   );      
  T1->SetBranchAddress("Jet1GenMatched_MaxDeltaRWPartonTop"    , & Jet1GenMatched_MaxDeltaRWPartonTop  );      
  T1->SetBranchAddress("Jet1GenMatched_MaxDeltaRWPartonW"      , & Jet1GenMatched_MaxDeltaRWPartonW    );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_t_b"             , & Jet1GenMatched_DeltaR_t_b           );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_t_W"             , & Jet1GenMatched_DeltaR_t_W           );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_t_Wd1"           , & Jet1GenMatched_DeltaR_t_Wd1         );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_t_Wd2"           , & Jet1GenMatched_DeltaR_t_Wd2         );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_W_b1"            , & Jet1GenMatched_DeltaR_W_b1          );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_W_Wd1"           , & Jet1GenMatched_DeltaR_W_Wd1         );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_W_Wd2"           , & Jet1GenMatched_DeltaR_W_Wd2         );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_Wd1_Wd2"         , & Jet1GenMatched_DeltaR_Wd1_Wd2       );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_Wd1_b"           , & Jet1GenMatched_DeltaR_Wd1_b         );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_Wd2_b"           , & Jet1GenMatched_DeltaR_Wd2_b         );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_jet_t"           , & Jet1GenMatched_DeltaR_jet_t         );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_jet_W"           , & Jet1GenMatched_DeltaR_jet_W         );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_jet_b"           , & Jet1GenMatched_DeltaR_jet_b         );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_jet_Wd1"         , & Jet1GenMatched_DeltaR_jet_Wd1       );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_jet_Wd2"         , & Jet1GenMatched_DeltaR_jet_Wd2       );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_pup0_b"          , & Jet1GenMatched_DeltaR_pup0_b        );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_pup0_Wd1"        , & Jet1GenMatched_DeltaR_pup0_Wd1      );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_pup0_Wd2"        , & Jet1GenMatched_DeltaR_pup0_Wd2      );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_pup1_b"          , & Jet1GenMatched_DeltaR_pup1_b        );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_pup1_Wd1"        , & Jet1GenMatched_DeltaR_pup1_Wd1      );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaR_pup1_Wd2"        , & Jet1GenMatched_DeltaR_pup1_Wd2      );               
  T1->SetBranchAddress("Jet1GenMatched_partonPt"               , & Jet1GenMatched_partonPt             );      
  T1->SetBranchAddress("Jet1GenMatched_partonEta"              , & Jet1GenMatched_partonEta            );      
  T1->SetBranchAddress("Jet1GenMatched_partonPhi"              , & Jet1GenMatched_partonPhi            );      
  T1->SetBranchAddress("Jet1GenMatched_partonMass"             , & Jet1GenMatched_partonMass           );      
  T1->SetBranchAddress("Jet1GenMatched_partonID"               , & Jet1GenMatched_partonID             );      
  T1->SetBranchAddress("Jet1GenMatched_DeltaRjetParton"        , & Jet1GenMatched_DeltaRjetParton      );      

  T1->SetBranchAddress("AllHadMETpx"                           , & AllHadMETpx                         );                                    
  T1->SetBranchAddress("AllHadMETpy"                           , & AllHadMETpy                         );                                    
  T1->SetBranchAddress("AllHadMETpt"                           , & AllHadMETpt                         );                                    
  T1->SetBranchAddress("AllHadMETphi"                          , & AllHadMETphi                        );                                     
  T1->SetBranchAddress("AllHadMETsumET"                        , & AllHadMETsumET                      );                                     
  T1->SetBranchAddress("AllHadNvtx"                            , & AllHadNvtx                          );                                   
  T1->SetBranchAddress("AllHadRho"                             , & AllHadRho                           );                                  
  T1->SetBranchAddress("AllHadEventWeight"                     , & AllHadEventWeight                   );                                          
  T1->SetBranchAddress("AllHadPUweight"                        , & AllHadPUweight                      );
  T1->SetBranchAddress("AllHadPUweight_MBup"                   , & AllHadPUweight_MBup                ); 
  T1->SetBranchAddress("AllHadPUweight_MBdn"                   , & AllHadPUweight_MBdn                ); 
     
  T1->SetBranchAddress("DijetMass"                             , & DijetMass                           );                                  
  T1->SetBranchAddress("DijetMassPuppi"                        , & DijetMassPuppi                      );                                  
  T1->SetBranchAddress("DijetDeltaR"                           , & DijetDeltaR                         );                                    
  T1->SetBranchAddress("DijetDeltaPhi"                         , & DijetDeltaPhi                       );                                      
  T1->SetBranchAddress("DijetDeltaRap"                         , & DijetDeltaRap                       );                                      
  T1->SetBranchAddress("DiGenJetMass"                          , & DiGenJetMass                        );                                     
  T1->SetBranchAddress("GenTTmass"                             , & GenTTmass                           );                                  
  T1->SetBranchAddress("HT"                                    , & HT                                  );                           
  T1->SetBranchAddress("HT_CorrDn"                             , & HT_CorrDn                           );                                  
  T1->SetBranchAddress("HT_CorrUp"                             , & HT_CorrUp                           );                                  
  T1->SetBranchAddress("HT_PtSmearNom"                         , & HT_PtSmearNom                       );                                     
  T1->SetBranchAddress("HT_PtSmearUp"                          , & HT_PtSmearUp                        );                                     
  T1->SetBranchAddress("HT_PtSmearDn"                          , & HT_PtSmearDn                        );                                     
  T1->SetBranchAddress("Q2weight_CorrDn"                       , & Q2weight_CorrDn                     );                                        
  T1->SetBranchAddress("Q2weight_CorrUp"                       , & Q2weight_CorrUp                     );                                        
  T1->SetBranchAddress("NNPDF3weight_CorrDn"                   , & NNPDF3weight_CorrDn                 );                                            
  T1->SetBranchAddress("NNPDF3weight_CorrUp"                   , & NNPDF3weight_CorrUp                 );                                            
  T1->SetBranchAddress("AllHadRunNum"                          , & AllHadRunNum                        );                                     
  T1->SetBranchAddress("AllHadLumiBlock"                       , & AllHadLumiBlock                     );                                        
  T1->SetBranchAddress("AllHadEventNum"                        , & AllHadEventNum                      );                                       


  // TH1D *  h_DijetMass_dRapIn_2ttag_PassMETfilt     = new TH1D( "h_DijetMass_dRapIn_2ttag_PassMETfilt"    , "", 400, 0, 8000); 
  // TH1D *  h_DijetMass_dRapHi_2ttag_PassMETfilt     = new TH1D( "h_DijetMass_dRapHi_2ttag_PassMETfilt"    , "", 400, 0, 8000); 
  // TH1D *  h_DijetMass_dRapLo_2ttag_PassMETfilt     = new TH1D( "h_DijetMass_dRapLo_2ttag_PassMETfilt"    , "", 400, 0, 8000); 

  TH1D *  h_2ttag_inclu_dRapIn_DijetMass      = new TH1D( "h_2ttag_inclu_dRapIn_DijetMass"    , "", 400, 0, 8000); 
  TH1D *  h_2ttag_0btag_dRapIn_DijetMass      = new TH1D( "h_2ttag_0btag_dRapIn_DijetMass"    , "", 400, 0, 8000); 
  TH1D *  h_2ttag_1btag_dRapIn_DijetMass      = new TH1D( "h_2ttag_1btag_dRapIn_DijetMass"    , "", 400, 0, 8000); 
  TH1D *  h_2ttag_2btag_dRapIn_DijetMass      = new TH1D( "h_2ttag_2btag_dRapIn_DijetMass"    , "", 400, 0, 8000); 

  TH1D *  h_2ttag_inclu_dRapLo_DijetMass      = new TH1D( "h_2ttag_inclu_dRapLo_DijetMass"    , "", 400, 0, 8000); 
  TH1D *  h_2ttag_0btag_dRapLo_DijetMass      = new TH1D( "h_2ttag_0btag_dRapLo_DijetMass"    , "", 400, 0, 8000); 
  TH1D *  h_2ttag_1btag_dRapLo_DijetMass      = new TH1D( "h_2ttag_1btag_dRapLo_DijetMass"    , "", 400, 0, 8000); 
  TH1D *  h_2ttag_2btag_dRapLo_DijetMass      = new TH1D( "h_2ttag_2btag_dRapLo_DijetMass"    , "", 400, 0, 8000); 

  TH1D *  h_2ttag_inclu_dRapHi_DijetMass      = new TH1D( "h_2ttag_inclu_dRapHi_DijetMass"    , "", 400, 0, 8000); 
  TH1D *  h_2ttag_0btag_dRapHi_DijetMass      = new TH1D( "h_2ttag_0btag_dRapHi_DijetMass"    , "", 400, 0, 8000); 
  TH1D *  h_2ttag_1btag_dRapHi_DijetMass      = new TH1D( "h_2ttag_1btag_dRapHi_DijetMass"    , "", 400, 0, 8000); 
  TH1D *  h_2ttag_2btag_dRapHi_DijetMass      = new TH1D( "h_2ttag_2btag_dRapHi_DijetMass"    , "", 400, 0, 8000); 

  TH1D *  h_2ttag_inclu_DeltaRap              = new TH1D( "h_2ttag_inclu_DeltaRap"            , "", 400, 0,    6); 
  TH1D *  h_2ttag_0btag_DeltaRap              = new TH1D( "h_2ttag_0btag_DeltaRap"            , "", 400, 0,    6); 
  TH1D *  h_2ttag_1btag_DeltaRap              = new TH1D( "h_2ttag_1btag_DeltaRap"            , "", 400, 0,    6); 
  TH1D *  h_2ttag_2btag_DeltaRap              = new TH1D( "h_2ttag_2btag_DeltaRap"            , "", 400, 0,    6); 

  TH1D *  h_2ttag_inclu_DeltaPhi              = new TH1D( "h_2ttag_inclu_DeltaPhi"            , "", 400, 0,  3.2); 
  TH1D *  h_2ttag_0btag_DeltaPhi              = new TH1D( "h_2ttag_0btag_DeltaPhi"            , "", 400, 0,  3.2); 
  TH1D *  h_2ttag_1btag_DeltaPhi              = new TH1D( "h_2ttag_1btag_DeltaPhi"            , "", 400, 0,  3.2); 
  TH1D *  h_2ttag_2btag_DeltaPhi              = new TH1D( "h_2ttag_2btag_DeltaPhi"            , "", 400, 0,  3.2); 

  TH1D *  h_2ttag_inclu_HT                    = new TH1D( "h_2ttag_inclu_HT"                  , "", 400, 0,  8000); 
  TH1D *  h_2ttag_0btag_HT                    = new TH1D( "h_2ttag_0btag_HT"                  , "", 400, 0,  8000); 
  TH1D *  h_2ttag_1btag_HT                    = new TH1D( "h_2ttag_1btag_HT"                  , "", 400, 0,  8000); 
  TH1D *  h_2ttag_2btag_HT                    = new TH1D( "h_2ttag_2btag_HT"                  , "", 400, 0,  8000); 

  TH1D *  h_2ttag_inclu_MET                   = new TH1D( "h_2ttag_inclu_MET"                 , "", 400, 0,  2000); 
  TH1D *  h_2ttag_0btag_MET                   = new TH1D( "h_2ttag_0btag_MET"                 , "", 400, 0,  2000); 
  TH1D *  h_2ttag_1btag_MET                   = new TH1D( "h_2ttag_1btag_MET"                 , "", 400, 0,  2000); 
  TH1D *  h_2ttag_2btag_MET                   = new TH1D( "h_2ttag_2btag_MET"                 , "", 400, 0,  2000); 
 
  TH1D *  h_2ttag_inclu_METphi                = new TH1D( "h_2ttag_inclu_METphi"              , "", 400, -3.2, 3.2 ); 
  TH1D *  h_2ttag_0btag_METphi                = new TH1D( "h_2ttag_0btag_METphi"              , "", 400, -3.2, 3.2 ); 
  TH1D *  h_2ttag_1btag_METphi                = new TH1D( "h_2ttag_1btag_METphi"              , "", 400, -3.2, 3.2 ); 
  TH1D *  h_2ttag_2btag_METphi                = new TH1D( "h_2ttag_2btag_METphi"              , "", 400, -3.2, 3.2 ); 
 
  TH1D *  h_2ttag_inclu_Nvtx                  = new TH1D( "h_2ttag_inclu_Nvtx"                , "", 100, 0,  100); 
  TH1D *  h_2ttag_0btag_Nvtx                  = new TH1D( "h_2ttag_0btag_Nvtx"                , "", 100, 0,  100); 
  TH1D *  h_2ttag_1btag_Nvtx                  = new TH1D( "h_2ttag_1btag_Nvtx"                , "", 100, 0,  100); 
  TH1D *  h_2ttag_2btag_Nvtx                  = new TH1D( "h_2ttag_2btag_Nvtx"                , "", 100, 0,  100); 
  

  TH1D *  h_DijetMass_dRapIn                     = new TH1D( "h_DijetMass_dRapIn"         ,"", 400, 0, 8000); 
  TH1D *  h_DijetMass_dRapLo                     = new TH1D( "h_DijetMass_dRapLo"         ,"", 400, 0, 8000); 
  TH1D *  h_DijetMass_dRapHi                     = new TH1D( "h_DijetMass_dRapHi"         ,"", 400, 0, 8000); 
  TH1D *  h_DeltaRap                             = new TH1D( "h_DeltaRap"                 ,"", 400, 0,    6); 
  TH1D *  h_DeltaPhi                             = new TH1D( "h_DeltaPhi"                 ,"", 400, 0,  3.2); 
  TH1D *  h_HT                                   = new TH1D( "h_HT"                       ,"", 400, 0,  8000); 
  TH1D *  h_MET                                  = new TH1D( "h_MET"                      ,"", 400, 0,  2000); 
  TH1D *  h_METphi                               = new TH1D( "h_METphi"                   ,"", 400, -3.2, 3.2 ); 
  TH1D *  h_Nvtx                                 = new TH1D( "h_Nvtx"                     ,"", 100, 0,  100); 
  TH1D *  h_Jet0P                                = new TH1D( "h_Jet0P"                    ,"", 400, 0, 6000); 
  TH1D *  h_Jet0Pt                               = new TH1D( "h_Jet0Pt"                   ,"", 400, 0, 4000); 
  TH1D *  h_Jet0Phi                              = new TH1D( "h_Jet0Phi"                  ,"", 400, -3.2, 3.2); 
  TH1D *  h_Jet0Rap                              = new TH1D( "h_Jet0Rap"                  ,"", 400, -5, 5); 
  TH1D *  h_Jet0SDmassCorrL23                    = new TH1D( "h_Jet0SDmassCorrL23"        ,"", 400, 0, 400); 
  TH1D *  h_Jet0SDmassCorrL23Up                  = new TH1D( "h_Jet0SDmassCorrL23Up"      ,"", 400, 0, 400); 
  TH1D *  h_Jet0Tau1                             = new TH1D( "h_Jet0Tau1"                 ,"", 400, 0, 1); 
  TH1D *  h_Jet0Tau2                             = new TH1D( "h_Jet0Tau2"                 ,"", 400, 0, 1); 
  TH1D *  h_Jet0Tau3                             = new TH1D( "h_Jet0Tau3"                 ,"", 400, 0, 1); 
  TH1D *  h_Jet0Tau4                             = new TH1D( "h_Jet0Tau4"                 ,"", 400, 0, 1); 
  TH1D *  h_Jet0SDmaxbdisc                       = new TH1D( "h_Jet0SDmaxbdisc"           ,"", 400, 0, 1); 
  TH1D *  h_Jet0SDsubjet0pt                      = new TH1D( "h_Jet0SDsubjet0pt"          ,"", 400, 0, 2000); 
  TH1D *  h_Jet0SDsubjet0mass                    = new TH1D( "h_Jet0SDsubjet0mass"        ,"", 400, 0, 300); 
  TH1D *  h_Jet0SDsubjet0tau1                    = new TH1D( "h_Jet0SDsubjet0tau1"        ,"", 400, 0, 1); 
  TH1D *  h_Jet0SDsubjet0tau2                    = new TH1D( "h_Jet0SDsubjet0tau2"        ,"", 400, 0, 1); 
  TH1D *  h_Jet0SDsubjet0tau3                    = new TH1D( "h_Jet0SDsubjet0tau3"        ,"", 400, 0, 1); 
  TH1D *  h_Jet0SDsubjet0bdisc                   = new TH1D( "h_Jet0SDsubjet0bdisc"       ,"", 400, 0, 1); 
  TH1D *  h_Jet0SDsubjet1pt                      = new TH1D( "h_Jet0SDsubjet1pt"          ,"", 400, 0, 2000); 
  TH1D *  h_Jet0SDsubjet1mass                    = new TH1D( "h_Jet0SDsubjet1mass"        ,"", 400, 0, 300); 
  TH1D *  h_Jet0SDsubjet1tau1                    = new TH1D( "h_Jet0SDsubjet1tau1"        ,"", 400, 0, 1); 
  TH1D *  h_Jet0SDsubjet1tau2                    = new TH1D( "h_Jet0SDsubjet1tau2"        ,"", 400, 0, 1); 
  TH1D *  h_Jet0SDsubjet1tau3                    = new TH1D( "h_Jet0SDsubjet1tau3"        ,"", 400, 0, 1); 
  TH1D *  h_Jet0SDsubjet1bdisc                   = new TH1D( "h_Jet0SDsubjet1bdisc"       ,"", 400, 0, 1); 
  TH1D *  h_Jet0PuppiPt                          = new TH1D( "h_Jet0PuppiPt"              ,"", 400, 0, 4000); 
  TH1D *  h_Jet0PuppiMass                        = new TH1D( "h_Jet0PuppiMass"            ,"", 400, 0, 300); 
  TH1D *  h_Jet0PuppiSDpt                        = new TH1D( "h_Jet0PuppiSDpt"            ,"", 400, 0, 4000); 
  TH1D *  h_Jet0PuppiTau1                        = new TH1D( "h_Jet0PuppiTau1"            ,"", 400, 0, 1); 
  TH1D *  h_Jet0PuppiTau2                        = new TH1D( "h_Jet0PuppiTau2"            ,"", 400, 0, 1); 
  TH1D *  h_Jet0PuppiTau3                        = new TH1D( "h_Jet0PuppiTau3"            ,"", 400, 0, 1); 
  TH1D *  h_Jet0PuppiTau4                        = new TH1D( "h_Jet0PuppiTau4"            ,"", 400, 0, 1); 
  TH1D *  h_Jet0PuppiSDmaxbdisc                  = new TH1D( "h_Jet0PuppiSDmaxbdisc"      ,"", 400, 0, 1); 
  TH1D *  h_Jet0PuppiSDsubjet0pt                 = new TH1D( "h_Jet0PuppiSDsubjet0pt"     ,"", 400, 0, 2000); 
  TH1D *  h_Jet0PuppiSDsubjet0mass               = new TH1D( "h_Jet0PuppiSDsubjet0mass"   ,"", 400, 0, 300); 
  TH1D *  h_Jet0PuppiSDsubjet0tau1               = new TH1D( "h_Jet0PuppiSDsubjet0tau1"   ,"", 400, 0, 1); 
  TH1D *  h_Jet0PuppiSDsubjet0tau2               = new TH1D( "h_Jet0PuppiSDsubjet0tau2"   ,"", 400, 0, 1); 
  TH1D *  h_Jet0PuppiSDsubjet0tau3               = new TH1D( "h_Jet0PuppiSDsubjet0tau3"   ,"", 400, 0, 1); 
  TH1D *  h_Jet0PuppiSDsubjet0bdisc              = new TH1D( "h_Jet0PuppiSDsubjet0bdisc"  ,"", 400, 0, 1); 
  TH1D *  h_Jet0PuppiSDsubjet1pt                 = new TH1D( "h_Jet0PuppiSDsubjet1pt"     ,"", 400, 0, 2000); 
  TH1D *  h_Jet0PuppiSDsubjet1mass               = new TH1D( "h_Jet0PuppiSDsubjet1mass"   ,"", 400, 0, 300); 
  TH1D *  h_Jet0PuppiSDsubjet1tau1               = new TH1D( "h_Jet0PuppiSDsubjet1tau1"   ,"", 400, 0, 1); 
  TH1D *  h_Jet0PuppiSDsubjet1tau2               = new TH1D( "h_Jet0PuppiSDsubjet1tau2"   ,"", 400, 0, 1); 
  TH1D *  h_Jet0PuppiSDsubjet1tau3               = new TH1D( "h_Jet0PuppiSDsubjet1tau3"   ,"", 400, 0, 1); 
  TH1D *  h_Jet0PuppiSDsubjet1bdisc              = new TH1D( "h_Jet0PuppiSDsubjet1bdisc"  ,"", 400, 0, 1); 
  TH1D *  h_Jet0CHF                              = new TH1D( "h_Jet0CHF"                  ,"", 400, 0, 1); 
  TH1D *  h_Jet0NHF                              = new TH1D( "h_Jet0NHF"                  ,"", 400, 0, 1); 
  TH1D *  h_Jet0CM                               = new TH1D( "h_Jet0CM"                   ,"", 200, 0, 200); 
  TH1D *  h_Jet0NM                               = new TH1D( "h_Jet0NM"                   ,"", 200, 0, 200); 
  TH1D *  h_Jet0NEF                              = new TH1D( "h_Jet0NEF"                  ,"", 400, 0, 1); 
  TH1D *  h_Jet0CEF                              = new TH1D( "h_Jet0CEF"                  ,"", 400, 0, 1); 
  TH1D *  h_Jet0MF                               = new TH1D( "h_Jet0MF"                   ,"", 10, 0, 10); 
  TH1D *  h_Jet0Mult                             = new TH1D( "h_Jet0Mult"                 ,"", 200, 0, 200); 
 

  TH1D *  h_2ttag_inclu_Jet0P                    = new TH1D( "h_2ttag_inclu_Jet0P"                    ,"", 400, 0, 6000); 
  TH1D *  h_2ttag_inclu_Jet0Pt                   = new TH1D( "h_2ttag_inclu_Jet0Pt"                   ,"", 400, 0, 4000); 
  TH1D *  h_2ttag_inclu_Jet0Phi                  = new TH1D( "h_2ttag_inclu_Jet0Phi"                  ,"", 400, -3.2, 3.2); 
  TH1D *  h_2ttag_inclu_Jet0Rap                  = new TH1D( "h_2ttag_inclu_Jet0Rap"                  ,"", 400, -5, 5); 
  TH1D *  h_2ttag_inclu_Jet0SDmass               = new TH1D( "h_2ttag_inclu_Jet0SDmass"               ,"", 400, 0, 400); 
  TH1D *  h_2ttag_inclu_Jet0SDmassCorrL23        = new TH1D( "h_2ttag_inclu_Jet0SDmassCorrL23"        ,"", 400, 0, 400); 
  TH1D *  h_2ttag_inclu_Jet0SDmassCorrL23Up      = new TH1D( "h_2ttag_inclu_Jet0SDmassCorrL23Up"      ,"", 400, 0, 400); 
  TH1D *  h_2ttag_inclu_Jet0Tau1                 = new TH1D( "h_2ttag_inclu_Jet0Tau1"                 ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0Tau2                 = new TH1D( "h_2ttag_inclu_Jet0Tau2"                 ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0Tau3                 = new TH1D( "h_2ttag_inclu_Jet0Tau3"                 ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0Tau4                 = new TH1D( "h_2ttag_inclu_Jet0Tau4"                 ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0SDmaxbdisc           = new TH1D( "h_2ttag_inclu_Jet0SDmaxbdisc"           ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0SDsubjet0pt          = new TH1D( "h_2ttag_inclu_Jet0SDsubjet0pt"          ,"", 400, 0, 2000); 
  TH1D *  h_2ttag_inclu_Jet0SDsubjet0mass        = new TH1D( "h_2ttag_inclu_Jet0SDsubjet0mass"        ,"", 400, 0, 300); 
  TH1D *  h_2ttag_inclu_Jet0SDsubjet0tau1        = new TH1D( "h_2ttag_inclu_Jet0SDsubjet0tau1"        ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0SDsubjet0tau2        = new TH1D( "h_2ttag_inclu_Jet0SDsubjet0tau2"        ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0SDsubjet0tau3        = new TH1D( "h_2ttag_inclu_Jet0SDsubjet0tau3"        ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0SDsubjet0bdisc       = new TH1D( "h_2ttag_inclu_Jet0SDsubjet0bdisc"       ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0SDsubjet1pt          = new TH1D( "h_2ttag_inclu_Jet0SDsubjet1pt"          ,"", 400, 0, 2000); 
  TH1D *  h_2ttag_inclu_Jet0SDsubjet1mass        = new TH1D( "h_2ttag_inclu_Jet0SDsubjet1mass"        ,"", 400, 0, 300); 
  TH1D *  h_2ttag_inclu_Jet0SDsubjet1tau1        = new TH1D( "h_2ttag_inclu_Jet0SDsubjet1tau1"        ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0SDsubjet1tau2        = new TH1D( "h_2ttag_inclu_Jet0SDsubjet1tau2"        ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0SDsubjet1tau3        = new TH1D( "h_2ttag_inclu_Jet0SDsubjet1tau3"        ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0SDsubjet1bdisc       = new TH1D( "h_2ttag_inclu_Jet0SDsubjet1bdisc"       ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiPt              = new TH1D( "h_2ttag_inclu_Jet0PuppiPt"              ,"", 400, 0, 4000); 
  TH1D *  h_2ttag_inclu_Jet0PuppiMass            = new TH1D( "h_2ttag_inclu_Jet0PuppiMass"            ,"", 400, 0, 300); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDpt            = new TH1D( "h_2ttag_inclu_Jet0PuppiSDpt"            ,"", 400, 0, 4000); 
  TH1D *  h_2ttag_inclu_Jet0PuppiTau1            = new TH1D( "h_2ttag_inclu_Jet0PuppiTau1"            ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiTau2            = new TH1D( "h_2ttag_inclu_Jet0PuppiTau2"            ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiTau3            = new TH1D( "h_2ttag_inclu_Jet0PuppiTau3"            ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiTau4            = new TH1D( "h_2ttag_inclu_Jet0PuppiTau4"            ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDmaxbdisc      = new TH1D( "h_2ttag_inclu_Jet0PuppiSDmaxbdisc"      ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDsubjet0pt     = new TH1D( "h_2ttag_inclu_Jet0PuppiSDsubjet0pt"     ,"", 400, 0, 2000); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDsubjet0mass   = new TH1D( "h_2ttag_inclu_Jet0PuppiSDsubjet0mass"   ,"", 400, 0, 300); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDsubjet0tau1   = new TH1D( "h_2ttag_inclu_Jet0PuppiSDsubjet0tau1"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDsubjet0tau2   = new TH1D( "h_2ttag_inclu_Jet0PuppiSDsubjet0tau2"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDsubjet0tau3   = new TH1D( "h_2ttag_inclu_Jet0PuppiSDsubjet0tau3"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDsubjet0bdisc  = new TH1D( "h_2ttag_inclu_Jet0PuppiSDsubjet0bdisc"  ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDsubjet1pt     = new TH1D( "h_2ttag_inclu_Jet0PuppiSDsubjet1pt"     ,"", 400, 0, 2000); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDsubjet1mass   = new TH1D( "h_2ttag_inclu_Jet0PuppiSDsubjet1mass"   ,"", 400, 0, 300); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDsubjet1tau1   = new TH1D( "h_2ttag_inclu_Jet0PuppiSDsubjet1tau1"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDsubjet1tau2   = new TH1D( "h_2ttag_inclu_Jet0PuppiSDsubjet1tau2"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDsubjet1tau3   = new TH1D( "h_2ttag_inclu_Jet0PuppiSDsubjet1tau3"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0PuppiSDsubjet1bdisc  = new TH1D( "h_2ttag_inclu_Jet0PuppiSDsubjet1bdisc"  ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0CHF                  = new TH1D( "h_2ttag_inclu_Jet0CHF"                  ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0NHF                  = new TH1D( "h_2ttag_inclu_Jet0NHF"                  ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0CM                   = new TH1D( "h_2ttag_inclu_Jet0CM"                   ,"", 200, 0, 200); 
  TH1D *  h_2ttag_inclu_Jet0NM                   = new TH1D( "h_2ttag_inclu_Jet0NM"                   ,"", 200, 0, 200); 
  TH1D *  h_2ttag_inclu_Jet0NEF                  = new TH1D( "h_2ttag_inclu_Jet0NEF"                  ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0CEF                  = new TH1D( "h_2ttag_inclu_Jet0CEF"                  ,"", 400, 0, 1); 
  TH1D *  h_2ttag_inclu_Jet0MF                   = new TH1D( "h_2ttag_inclu_Jet0MF"                   ,"", 10, 0, 10); 
  TH1D *  h_2ttag_inclu_Jet0Mult                 = new TH1D( "h_2ttag_inclu_Jet0Mult"                 ,"", 200, 0, 200); 



  TH1D *  h_2ttag_2btag_Jet0PuppiSDsubjet0pt     = new TH1D( "h_2ttag_2btag_Jet0PuppiSDsubjet0pt"     ,"", 400, 0, 2000);
  TH1D *  h_2ttag_2btag_Jet0PuppiSDsubjet0mass   = new TH1D( "h_2ttag_2btag_Jet0PuppiSDsubjet0mass"   ,"", 400, 0, 300); 
  TH1D *  h_2ttag_2btag_Jet0PuppiSDsubjet0tau1   = new TH1D( "h_2ttag_2btag_Jet0PuppiSDsubjet0tau1"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_2btag_Jet0PuppiSDsubjet0tau2   = new TH1D( "h_2ttag_2btag_Jet0PuppiSDsubjet0tau2"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_2btag_Jet0PuppiSDsubjet0tau3   = new TH1D( "h_2ttag_2btag_Jet0PuppiSDsubjet0tau3"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_2btag_Jet0PuppiSDsubjet0bdisc  = new TH1D( "h_2ttag_2btag_Jet0PuppiSDsubjet0bdisc"  ,"", 400, 0, 1); 
  TH1D *  h_2ttag_2btag_Jet0PuppiSDsubjet1pt     = new TH1D( "h_2ttag_2btag_Jet0PuppiSDsubjet1pt"     ,"", 400, 0, 2000);
  TH1D *  h_2ttag_2btag_Jet0PuppiSDsubjet1mass   = new TH1D( "h_2ttag_2btag_Jet0PuppiSDsubjet1mass"   ,"", 400, 0, 300); 
  TH1D *  h_2ttag_2btag_Jet0PuppiSDsubjet1tau1   = new TH1D( "h_2ttag_2btag_Jet0PuppiSDsubjet1tau1"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_2btag_Jet0PuppiSDsubjet1tau2   = new TH1D( "h_2ttag_2btag_Jet0PuppiSDsubjet1tau2"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_2btag_Jet0PuppiSDsubjet1tau3   = new TH1D( "h_2ttag_2btag_Jet0PuppiSDsubjet1tau3"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_2btag_Jet0PuppiSDsubjet1bdisc  = new TH1D( "h_2ttag_2btag_Jet0PuppiSDsubjet1bdisc"  ,"", 400, 0, 1); 


  TH1D *  h_2ttag_1btag_Jet0PuppiSDsubjet0pt     = new TH1D( "h_2ttag_1btag_Jet0PuppiSDsubjet0pt"     ,"", 400, 0, 2000);
  TH1D *  h_2ttag_1btag_Jet0PuppiSDsubjet0mass   = new TH1D( "h_2ttag_1btag_Jet0PuppiSDsubjet0mass"   ,"", 400, 0, 300); 
  TH1D *  h_2ttag_1btag_Jet0PuppiSDsubjet0tau1   = new TH1D( "h_2ttag_1btag_Jet0PuppiSDsubjet0tau1"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_1btag_Jet0PuppiSDsubjet0tau2   = new TH1D( "h_2ttag_1btag_Jet0PuppiSDsubjet0tau2"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_1btag_Jet0PuppiSDsubjet0tau3   = new TH1D( "h_2ttag_1btag_Jet0PuppiSDsubjet0tau3"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_1btag_Jet0PuppiSDsubjet0bdisc  = new TH1D( "h_2ttag_1btag_Jet0PuppiSDsubjet0bdisc"  ,"", 400, 0, 1); 
  TH1D *  h_2ttag_1btag_Jet0PuppiSDsubjet1pt     = new TH1D( "h_2ttag_1btag_Jet0PuppiSDsubjet1pt"     ,"", 400, 0, 2000);
  TH1D *  h_2ttag_1btag_Jet0PuppiSDsubjet1mass   = new TH1D( "h_2ttag_1btag_Jet0PuppiSDsubjet1mass"   ,"", 400, 0, 300); 
  TH1D *  h_2ttag_1btag_Jet0PuppiSDsubjet1tau1   = new TH1D( "h_2ttag_1btag_Jet0PuppiSDsubjet1tau1"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_1btag_Jet0PuppiSDsubjet1tau2   = new TH1D( "h_2ttag_1btag_Jet0PuppiSDsubjet1tau2"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_1btag_Jet0PuppiSDsubjet1tau3   = new TH1D( "h_2ttag_1btag_Jet0PuppiSDsubjet1tau3"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_1btag_Jet0PuppiSDsubjet1bdisc  = new TH1D( "h_2ttag_1btag_Jet0PuppiSDsubjet1bdisc"  ,"", 400, 0, 1); 


  TH1D *  h_2ttag_0btag_Jet0PuppiSDsubjet0pt     = new TH1D( "h_2ttag_0btag_Jet0PuppiSDsubjet0pt"     ,"", 400, 0, 2000);
  TH1D *  h_2ttag_0btag_Jet0PuppiSDsubjet0mass   = new TH1D( "h_2ttag_0btag_Jet0PuppiSDsubjet0mass"   ,"", 400, 0, 300); 
  TH1D *  h_2ttag_0btag_Jet0PuppiSDsubjet0tau1   = new TH1D( "h_2ttag_0btag_Jet0PuppiSDsubjet0tau1"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_0btag_Jet0PuppiSDsubjet0tau2   = new TH1D( "h_2ttag_0btag_Jet0PuppiSDsubjet0tau2"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_0btag_Jet0PuppiSDsubjet0tau3   = new TH1D( "h_2ttag_0btag_Jet0PuppiSDsubjet0tau3"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_0btag_Jet0PuppiSDsubjet0bdisc  = new TH1D( "h_2ttag_0btag_Jet0PuppiSDsubjet0bdisc"  ,"", 400, 0, 1); 
  TH1D *  h_2ttag_0btag_Jet0PuppiSDsubjet1pt     = new TH1D( "h_2ttag_0btag_Jet0PuppiSDsubjet1pt"     ,"", 400, 0, 2000);
  TH1D *  h_2ttag_0btag_Jet0PuppiSDsubjet1mass   = new TH1D( "h_2ttag_0btag_Jet0PuppiSDsubjet1mass"   ,"", 400, 0, 300); 
  TH1D *  h_2ttag_0btag_Jet0PuppiSDsubjet1tau1   = new TH1D( "h_2ttag_0btag_Jet0PuppiSDsubjet1tau1"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_0btag_Jet0PuppiSDsubjet1tau2   = new TH1D( "h_2ttag_0btag_Jet0PuppiSDsubjet1tau2"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_0btag_Jet0PuppiSDsubjet1tau3   = new TH1D( "h_2ttag_0btag_Jet0PuppiSDsubjet1tau3"   ,"", 400, 0, 1); 
  TH1D *  h_2ttag_0btag_Jet0PuppiSDsubjet1bdisc  = new TH1D( "h_2ttag_0btag_Jet0PuppiSDsubjet1bdisc"  ,"", 400, 0, 1); 



  TH1D *  h_Jet0SDmass                                    = new TH1D( "h_Jet0SDmass"                                   , "", 200, 0,  500); 
  TH1D *  h_Jet0SDmass_JetTag_b                           = new TH1D( "h_Jet0SDmass_JetTag_b"                          , "", 200, 0,  500); 
  TH1D *  h_Jet0SDmass_JetTag_tau32                       = new TH1D( "h_Jet0SDmass_JetTag_tau32"                      , "", 200, 0,  500); 
  TH1D *  h_Jet0SDmass_JetTag_b_tau32                     = new TH1D( "h_Jet0SDmass_JetTag_b_tau32"                    , "", 200, 0,  500); 
  TH1D *  h_Jet0SDmass_OppositeJetTag_t_b                 = new TH1D( "h_Jet0SDmass_OppositeJetTag_t_b"                , "", 200, 0,  500); 
  TH1D *  h_Jet0SDmass_OppositeJetTag_t_b_JetTag_b        = new TH1D( "h_Jet0SDmass_OppositeJetTag_t_b_JetTag_b"       , "", 200, 0,  500); 
  TH1D *  h_Jet0SDmass_OppositeJetTag_t_b_JetTag_b_tau32  = new TH1D( "h_Jet0SDmass_OppositeJetTag_t_b_JetTag_b_tau32" , "", 200, 0,  500); 

  TH1D *  h_Jet1SDmass                                    = new TH1D( "h_Jet1SDmass"                                   , "", 200, 0,  500);
  TH1D *  h_Jet1SDmass_JetTag_b                           = new TH1D( "h_Jet1SDmass_JetTag_b"                          , "", 200, 0,  500); 
  TH1D *  h_Jet1SDmass_JetTag_tau32                       = new TH1D( "h_Jet1SDmass_JetTag_tau32"                      , "", 200, 0,  500); 
  TH1D *  h_Jet1SDmass_JetTag_b_tau32                     = new TH1D( "h_Jet1SDmass_JetTag_b_tau32"                    , "", 200, 0,  500);  
  TH1D *  h_Jet1SDmass_OppositeJetTag_t_b                 = new TH1D( "h_Jet1SDmass_OppositeJetTag_t_b"                , "", 200, 0,  500); 
  TH1D *  h_Jet1SDmass_OppositeJetTag_t_b_JetTag_b        = new TH1D( "h_Jet1SDmass_OppositeJetTag_t_b_JetTag_b"       , "", 200, 0,  500); 
  TH1D *  h_Jet1SDmass_OppositeJetTag_t_b_JetTag_b_tau32  = new TH1D( "h_Jet1SDmass_OppositeJetTag_t_b_JetTag_b_tau32" , "", 200, 0,  500); 

  TH1D *  h_JetSDmass                                     = new TH1D( "h_JetSDmass"                                    , "", 200, 0,  500);
  TH1D *  h_JetSDmass_JetTag_b                            = new TH1D( "h_JetSDmass_JetTag_b"                           , "", 200, 0,  500); 
  TH1D *  h_JetSDmass_JetTag_tau32                        = new TH1D( "h_JetSDmass_JetTag_tau32"                       , "", 200, 0,  500); 
  TH1D *  h_JetSDmass_JetTag_b_tau32                      = new TH1D( "h_JetSDmass_JetTag_b_tau32"                     , "", 200, 0,  500);  
  TH1D *  h_JetSDmass_OppositeJetTag_t_b                  = new TH1D( "h_JetSDmass_OppositeJetTag_t_b"                 , "", 200, 0,  500); 
  TH1D *  h_JetSDmass_OppositeJetTag_t_b_JetTag_b         = new TH1D( "h_JetSDmass_OppositeJetTag_t_b_JetTag_b"        , "", 200, 0,  500); 
  TH1D *  h_JetSDmass_OppositeJetTag_t_b_JetTag_b_tau32   = new TH1D( "h_JetSDmass_OppositeJetTag_t_b_JetTag_b_tau32"  , "", 200, 0,  500); 

  TH1D *  h_Jet0Tau32                                     = new TH1D( "h_Jet0Tau32"                                    , "", 200, 0,    1); 
  TH1D *  h_Jet0Tau32_JetTag_b                            = new TH1D( "h_Jet0Tau32_JetTag_b"                           , "", 200, 0,    1); 
  TH1D *  h_Jet0Tau32_JetTag_mass                         = new TH1D( "h_Jet0Tau32_JetTag_mass"                        , "", 200, 0,    1); 
  TH1D *  h_Jet0Tau32_JetTag_b_mass                       = new TH1D( "h_Jet0Tau32_JetTag_b_mass"                      , "", 200, 0,    1); 
  TH1D *  h_Jet0Tau32_OppositeJetTag_t_b                  = new TH1D( "h_Jet0Tau32_OppositeJetTag_t_b"                 , "", 200, 0,    1); 
  TH1D *  h_Jet0Tau32_OppositeJetTag_t_b_JetTag_b         = new TH1D( "h_Jet0Tau32_OppositeJetTag_t_b_JetTag_b"        , "", 200, 0,    1); 
  TH1D *  h_Jet0Tau32_OppositeJetTag_t_b_JetTag_b_mass    = new TH1D( "h_Jet0Tau32_OppositeJetTag_t_b_JetTag_b_mass"   , "", 200, 0,    1); 

  TH1D *  h_Jet1Tau32                                     = new TH1D( "h_Jet1Tau32"                                    , "", 200, 0,    1); 
  TH1D *  h_Jet1Tau32_JetTag_b                            = new TH1D( "h_Jet1Tau32_JetTag_b"                           , "", 200, 0,    1); 
  TH1D *  h_Jet1Tau32_JetTag_mass                         = new TH1D( "h_Jet1Tau32_JetTag_mass"                        , "", 200, 0,    1); 
  TH1D *  h_Jet1Tau32_JetTag_b_mass                       = new TH1D( "h_Jet1Tau32_JetTag_b_mass"                      , "", 200, 0,    1); 
  TH1D *  h_Jet1Tau32_OppositeJetTag_t_b                  = new TH1D( "h_Jet1Tau32_OppositeJetTag_t_b"                 , "", 200, 0,    1); 
  TH1D *  h_Jet1Tau32_OppositeJetTag_t_b_JetTag_b         = new TH1D( "h_Jet1Tau32_OppositeJetTag_t_b_JetTag_b"        , "", 200, 0,    1); 
  TH1D *  h_Jet1Tau32_OppositeJetTag_t_b_JetTag_b_mass    = new TH1D( "h_Jet1Tau32_OppositeJetTag_t_b_JetTag_b_mass"   , "", 200, 0,    1); 

  TH1D *  h_JetTau32                                      = new TH1D( "h_JetTau32"                                     , "", 200, 0,    1); 
  TH1D *  h_JetTau32_JetTag_b                             = new TH1D( "h_JetTau32_JetTag_b"                            , "", 200, 0,    1); 
  TH1D *  h_JetTau32_JetTag_mass                          = new TH1D( "h_JetTau32_JetTag_mass"                         , "", 200, 0,    1); 
  TH1D *  h_JetTau32_JetTag_b_mass                        = new TH1D( "h_JetTau32_JetTag_b_mass"                       , "", 200, 0,    1); 
  TH1D *  h_JetTau32_OppositeJetTag_t_b                   = new TH1D( "h_JetTau32_OppositeJetTag_t_b"                  , "", 200, 0,    1); 
  TH1D *  h_JetTau32_OppositeJetTag_t_b_JetTag_b          = new TH1D( "h_JetTau32_OppositeJetTag_t_b_JetTag_b"         , "", 200, 0,    1); 
  TH1D *  h_JetTau32_OppositeJetTag_t_b_JetTag_b_mass     = new TH1D( "h_JetTau32_OppositeJetTag_t_b_JetTag_b_mass"    , "", 200, 0,    1); 





  // MC study
  TH1D * h_Jet0SDmass_matchedTop                          = new TH1D( "h_Jet0SDmass_matchedTop"                        , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_matchedTop_topDist                  = new TH1D( "h_Jet0SDmass_matchedTop_topDist"                , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_outside                             = new TH1D( "h_Jet0SDmass_outside"                           , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_bq                                  = new TH1D( "h_Jet0SDmass_bq"                                , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_qq                                  = new TH1D( "h_Jet0SDmass_qq"                                , "", 200, 0, 500); 
      
  TH1D * h_Jet0SDmass_all                                 = new TH1D( "h_Jet0SDmass_all"                               , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_in_b                                = new TH1D( "h_Jet0SDmass_in_b"                              , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_in_q                                = new TH1D( "h_Jet0SDmass_in_q"                              , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_in_qq                               = new TH1D( "h_Jet0SDmass_in_qq"                             , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_in_qb                               = new TH1D( "h_Jet0SDmass_in_qb"                             , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_in_qqb                              = new TH1D( "h_Jet0SDmass_in_qqb"                            , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_unmatched                           = new TH1D( "h_Jet0SDmass_unmatched"                         , "", 200, 0, 500); 

  TH1D * h_Jet0Tau32_all                                  = new TH1D( "h_Jet0Tau32_all"                                , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_in_b                                 = new TH1D( "h_Jet0Tau32_in_b"                               , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_in_q                                 = new TH1D( "h_Jet0Tau32_in_q"                               , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_in_qq                                = new TH1D( "h_Jet0Tau32_in_qq"                              , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_in_qb                                = new TH1D( "h_Jet0Tau32_in_qb"                              , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_in_qqb                               = new TH1D( "h_Jet0Tau32_in_qqb"                             , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_unmatched                            = new TH1D( "h_Jet0Tau32_unmatched"                          , "", 200, 0,   1); 

  TH1D * h_Jet0SDmass_Pt600_all                           = new TH1D( "h_Jet0SDmass_Pt600_all"                         , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_Pt600_in_b                          = new TH1D( "h_Jet0SDmass_Pt600_in_b"                        , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_Pt600_in_q                          = new TH1D( "h_Jet0SDmass_Pt600_in_q"                        , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_Pt600_in_qq                         = new TH1D( "h_Jet0SDmass_Pt600_in_qq"                       , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_Pt600_in_qb                         = new TH1D( "h_Jet0SDmass_Pt600_in_qb"                       , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_Pt600_in_qqb                        = new TH1D( "h_Jet0SDmass_Pt600_in_qqb"                      , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_Pt600_unmatched                     = new TH1D( "h_Jet0SDmass_Pt600_unmatched"                   , "", 200, 0, 500); 

  TH1D * h_Jet0Tau32_Pt600_all                            = new TH1D( "h_Jet0Tau32_Pt600_all"                          , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_Pt600_in_b                           = new TH1D( "h_Jet0Tau32_Pt600_in_b"                         , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_Pt600_in_q                           = new TH1D( "h_Jet0Tau32_Pt600_in_q"                         , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_Pt600_in_qq                          = new TH1D( "h_Jet0Tau32_Pt600_in_qq"                        , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_Pt600_in_qb                          = new TH1D( "h_Jet0Tau32_Pt600_in_qb"                        , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_Pt600_in_qqb                         = new TH1D( "h_Jet0Tau32_Pt600_in_qqb"                       , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_Pt600_unmatched                      = new TH1D( "h_Jet0Tau32_Pt600_unmatched"                    , "", 200, 0,   1); 

  TH1D * h_Jet0SDmass_BtagM_all                           = new TH1D( "h_Jet0SDmass_BtagM_all"                         , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagM_in_b                          = new TH1D( "h_Jet0SDmass_BtagM_in_b"                        , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagM_in_q                          = new TH1D( "h_Jet0SDmass_BtagM_in_q"                        , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagM_in_qq                         = new TH1D( "h_Jet0SDmass_BtagM_in_qq"                       , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagM_in_qb                         = new TH1D( "h_Jet0SDmass_BtagM_in_qb"                       , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagM_in_qqb                        = new TH1D( "h_Jet0SDmass_BtagM_in_qqb"                      , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagM_unmatched                     = new TH1D( "h_Jet0SDmass_BtagM_unmatched"                   , "", 200, 0, 500); 

  TH1D * h_Jet0SDmass_BtagT_all                           = new TH1D( "h_Jet0SDmass_BtagT_all"                         , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagT_in_b                          = new TH1D( "h_Jet0SDmass_BtagT_in_b"                        , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagT_in_q                          = new TH1D( "h_Jet0SDmass_BtagT_in_q"                        , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagT_in_qq                         = new TH1D( "h_Jet0SDmass_BtagT_in_qq"                       , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagT_in_qb                         = new TH1D( "h_Jet0SDmass_BtagT_in_qb"                       , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagT_in_qqb                        = new TH1D( "h_Jet0SDmass_BtagT_in_qqb"                      , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagT_unmatched                     = new TH1D( "h_Jet0SDmass_BtagT_unmatched"                   , "", 200, 0, 500); 

  TH1D * h_Jet0Tau32_BtagM_all                            = new TH1D( "h_Jet0Tau32_BtagM_all"                          , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_BtagM_in_b                           = new TH1D( "h_Jet0Tau32_BtagM_in_b"                         , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_BtagM_in_q                           = new TH1D( "h_Jet0Tau32_BtagM_in_q"                         , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_BtagM_in_qq                          = new TH1D( "h_Jet0Tau32_BtagM_in_qq"                        , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_BtagM_in_qb                          = new TH1D( "h_Jet0Tau32_BtagM_in_qb"                        , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_BtagM_in_qqb                         = new TH1D( "h_Jet0Tau32_BtagM_in_qqb"                       , "", 200, 0,   1); 
  TH1D * h_Jet0Tau32_BtagM_unmatched                      = new TH1D( "h_Jet0Tau32_BtagM_unmatched"                    , "", 200, 0,   1); 

  TH1D * h_Jet0Tau32_MassTag_all                          = new TH1D( "h_Jet0Tau32_MassTag_all"                       , "", 200, 0, 1); 
  TH1D * h_Jet0Tau32_MassTag_in_b                         = new TH1D( "h_Jet0Tau32_MassTag_in_b"                      , "", 200, 0, 1); 
  TH1D * h_Jet0Tau32_MassTag_in_q                         = new TH1D( "h_Jet0Tau32_MassTag_in_q"                      , "", 200, 0, 1); 
  TH1D * h_Jet0Tau32_MassTag_in_qq                        = new TH1D( "h_Jet0Tau32_MassTag_in_qq"                     , "", 200, 0, 1); 
  TH1D * h_Jet0Tau32_MassTag_in_qb                        = new TH1D( "h_Jet0Tau32_MassTag_in_qb"                     , "", 200, 0, 1); 
  TH1D * h_Jet0Tau32_MassTag_in_qqb                       = new TH1D( "h_Jet0Tau32_MassTag_in_qqb"                    , "", 200, 0, 1); 
  TH1D * h_Jet0Tau32_MassTag_unmatched                    = new TH1D( "h_Jet0Tau32_MassTag_unmatched"                 , "", 200, 0, 1); 

  TH1D * h_Jet0Tau32_BtagM_MassTag_all                    = new TH1D( "h_Jet0Tau32_BtagM_MassTag_all"                 , "", 200, 0, 1); 
  TH1D * h_Jet0Tau32_BtagM_MassTag_in_b                   = new TH1D( "h_Jet0Tau32_BtagM_MassTag_in_b"                , "", 200, 0, 1); 
  TH1D * h_Jet0Tau32_BtagM_MassTag_in_q                   = new TH1D( "h_Jet0Tau32_BtagM_MassTag_in_q"                , "", 200, 0, 1); 
  TH1D * h_Jet0Tau32_BtagM_MassTag_in_qq                  = new TH1D( "h_Jet0Tau32_BtagM_MassTag_in_qq"               , "", 200, 0, 1); 
  TH1D * h_Jet0Tau32_BtagM_MassTag_in_qb                  = new TH1D( "h_Jet0Tau32_BtagM_MassTag_in_qb"               , "", 200, 0, 1); 
  TH1D * h_Jet0Tau32_BtagM_MassTag_in_qqb                 = new TH1D( "h_Jet0Tau32_BtagM_MassTag_in_qqb"              , "", 200, 0, 1); 
  TH1D * h_Jet0Tau32_BtagM_MassTag_unmatched              = new TH1D( "h_Jet0Tau32_BtagM_MassTag_unmatched"           , "", 200, 0, 1); 

  TH1D * h_Jet0SDmass_TauTag_all                          = new TH1D( "h_Jet0SDmass_TauTag_all"                       , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_TauTag_in_b                         = new TH1D( "h_Jet0SDmass_TauTag_in_b"                      , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_TauTag_in_q                         = new TH1D( "h_Jet0SDmass_TauTag_in_q"                      , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_TauTag_in_qq                        = new TH1D( "h_Jet0SDmass_TauTag_in_qq"                     , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_TauTag_in_qb                        = new TH1D( "h_Jet0SDmass_TauTag_in_qb"                     , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_TauTag_in_qqb                       = new TH1D( "h_Jet0SDmass_TauTag_in_qqb"                    , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_TauTag_unmatched                    = new TH1D( "h_Jet0SDmass_TauTag_unmatched"                 , "", 200, 0, 500); 

  TH1D * h_Jet0SDmass_AntiTauTag_all                      = new TH1D( "h_Jet0SDmass_AntiTauTag_all"                   , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_AntiTauTag_in_b                     = new TH1D( "h_Jet0SDmass_AntiTauTag_in_b"                  , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_AntiTauTag_in_q                     = new TH1D( "h_Jet0SDmass_AntiTauTag_in_q"                  , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_AntiTauTag_in_qq                    = new TH1D( "h_Jet0SDmass_AntiTauTag_in_qq"                 , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_AntiTauTag_in_qb                    = new TH1D( "h_Jet0SDmass_AntiTauTag_in_qb"                 , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_AntiTauTag_in_qqb                   = new TH1D( "h_Jet0SDmass_AntiTauTag_in_qqb"                , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_AntiTauTag_unmatched                = new TH1D( "h_Jet0SDmass_AntiTauTag_unmatched"             , "", 200, 0, 500); 

  TH1D * h_Jet0SDmass_BtagM_TauTag_all                    = new TH1D( "h_Jet0SDmass_BtagM_TauTag_all"                 , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagM_TauTag_in_b                   = new TH1D( "h_Jet0SDmass_BtagM_TauTag_in_b"                , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagM_TauTag_in_q                   = new TH1D( "h_Jet0SDmass_BtagM_TauTag_in_q"                , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagM_TauTag_in_qq                  = new TH1D( "h_Jet0SDmass_BtagM_TauTag_in_qq"               , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagM_TauTag_in_qb                  = new TH1D( "h_Jet0SDmass_BtagM_TauTag_in_qb"               , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagM_TauTag_in_qqb                 = new TH1D( "h_Jet0SDmass_BtagM_TauTag_in_qqb"              , "", 200, 0, 500); 
  TH1D * h_Jet0SDmass_BtagM_TauTag_unmatched              = new TH1D( "h_Jet0SDmass_BtagM_TauTag_unmatched"           , "", 200, 0, 500); 
         
  // anti-tag and probe
  TH1D * h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_inclusive              = new TH1D( "h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_inclusive"                    , "", 1400, 0, 7000 );
  TH1D * h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_0btag                  = new TH1D( "h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_0btag"                        , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_1btag                  = new TH1D( "h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_1btag"                        , "", 1400, 0, 7000 ); 
  TH1D * h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_2btag                  = new TH1D( "h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_2btag"                        , "", 1400, 0, 7000 ); 
  TH1D * h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_inclusive              = new TH1D( "h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_inclusive"                    , "", 1400, 0, 7000 );
  TH1D * h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_0btag                  = new TH1D( "h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_0btag"                        , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_1btag                  = new TH1D( "h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_1btag"                        , "", 1400, 0, 7000 ); 
  TH1D * h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_2btag                  = new TH1D( "h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_2btag"                        , "", 1400, 0, 7000 ); 
  TH1D * h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_inclusive              = new TH1D( "h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_inclusive"                    , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_0btag                  = new TH1D( "h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_0btag"                        , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_1btag                  = new TH1D( "h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_1btag"                        , "", 1400, 0, 7000 );   
  TH1D * h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_2btag                  = new TH1D( "h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_2btag"                        , "", 1400, 0, 7000 );
  TH1D * h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_inclusive     = new TH1D( "h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_inclusive"           , "", 1400, 0, 7000 );
  TH1D * h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_0btag         = new TH1D( "h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_0btag"               , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_1btag         = new TH1D( "h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_1btag"               , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_2btag         = new TH1D( "h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_2btag"               , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_inclusive     = new TH1D( "h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_inclusive"           , "", 1400, 0, 7000 );
  TH1D * h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_0btag         = new TH1D( "h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_0btag"               , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_1btag         = new TH1D( "h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_1btag"               , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_2btag         = new TH1D( "h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_2btag"               , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_inclusive     = new TH1D( "h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_inclusive"           , "", 1400, 0, 7000 );  
  TH1D * h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_0btag         = new TH1D( "h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_0btag"               , "", 1400, 0, 7000 );     
  TH1D * h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_1btag         = new TH1D( "h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_1btag"               , "", 1400, 0, 7000 );     
  TH1D * h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_2btag         = new TH1D( "h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_2btag"               , "", 1400, 0, 7000 );  
              

  for (int i=0; i<entries; i++ ) //entries
  { 
    if (i%10000==0) cout<<i<<"  / "<<entries<<endl;
    T1->GetEntry(i);
    if (Jet0Pt <400 || Jet1Pt < 400) continue;
    // cout<<"here"<<endl;
    // for (unsigned int j = 0; j < AllHadTrigPrescales->size(); ++j) {
    //     cout<<"AllHadTrigPrescales->at(j) "<<AllHadTrigPrescales->at(j)<<endl;
    //     // cout<<AllHadTrigNames->at(j)<<" Prescale "<<AllHadTrigPrescales->at(j)<<endl;
    // }

    bool passMetFilt = false;
    if (PassMETFilters==1) passMetFilt=true;
    if (!passMetFilt) continue;

    // Top-tagging bools
    bool j0_tag_mass  = Jet0SDmass > 120 && Jet0SDmass < 220;
    bool j1_tag_mass  = Jet1SDmass > 120 && Jet1SDmass < 220;
    bool j0_tag_tau32 = Jet0Tau32 < 0.7;
    bool j1_tag_tau32 = Jet1Tau32 < 0.7;
    bool j0_tag_t     = j0_tag_mass && j0_tag_tau32;
    bool j1_tag_t     = j1_tag_mass && j1_tag_tau32;
    bool j0_tag_b     = Jet0SDmaxbdisc > 0.8;
    bool j1_tag_b     = Jet1SDmaxbdisc > 0.8;
    bool j0_tag_t_b   = j0_tag_t && j0_tag_b ;
    bool j1_tag_t_b   = j1_tag_t && j1_tag_b ;

    bool j0_puptag_mass  = Jet0PuppiSDmass > 120 && Jet0PuppiSDmass < 220;
    bool j1_puptag_mass  = Jet1PuppiSDmass > 120 && Jet1PuppiSDmass < 220;
    bool j0_puptag_tau32 = Jet0PuppiTau32 < 0.7;
    bool j1_puptag_tau32 = Jet1PuppiTau32 < 0.7;
    bool j0_puptag_t     = j0_puptag_mass && j0_puptag_tau32;
    bool j1_puptag_t     = j1_puptag_mass && j1_puptag_tau32;
    bool j0_puptag_b     = Jet0PuppiSDmaxbdisc > 0.8;
    bool j1_puptag_b     = Jet0PuppiSDmaxbdisc > 0.8;
    bool j0_puptag_t_b   = j0_puptag_t && j0_puptag_b ;
    bool j1_puptag_t_b   = j1_puptag_t && j1_puptag_b ;
    
    bool double_tag_t                 = j0_tag_t && j1_tag_t ;           
    bool double_tag_t_b               = j0_tag_t_b && j1_tag_t_b ;           
    bool double_tag_t_single_tag_b    = double_tag_t && ( (j0_tag_b && !j1_tag_b) || (!j0_tag_b && j1_tag_b) )  ;           
    bool double_tag_t_no_b            = double_tag_t && !j0_tag_b && !j1_tag_b ;           

    bool double_puptag_t                 = j0_puptag_t && j1_puptag_t ;           
    bool double_puptag_t_b               = j0_puptag_t_b && j1_puptag_t_b ;           
    bool double_puptag_t_single_puptag_b = double_puptag_t && ( (j0_puptag_b && !j1_puptag_b) || (!j0_puptag_b && j1_puptag_b) )  ;           
    bool double_puptag_t_no_b            = double_puptag_t && !j0_puptag_b && !j1_puptag_b ;           

    bool j0_antitag_tau32     = Jet0Tau32 > 0.7;
    bool j1_antitag_tau32     = Jet1Tau32 > 0.7;
    bool j0_antitag_tau32_tag_mass  =  j0_antitag_tau32 && j0_tag_mass ;
    bool j1_antitag_tau32_tag_mass  =  j1_antitag_tau32 && j1_tag_mass ;
  
    bool newbtagjet0 = j0_tag_b;
    bool newbtagjet1 = j1_tag_b;

    // Anti-tag and probe
    double evWeight =1;
    TRandom3 rand1(0);
    double rand_mistag  = rand1.Uniform(0,1.0);

    if (rand_mistag < 0.5){    // 50% of the time choose jet 0 to be the anti-tag and jet 1 to be the probe
      
      //----------anti-tag tau32, keep jet in SD mass window
      if (j0_antitag_tau32_tag_mass){

        h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_inclusive                             ->Fill( Jet1P        , evWeight ); 
        if (j1_tag_t)  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_inclusive     ->Fill( Jet1P        , evWeight );
        if (DijetDeltaRap<=1.0){
          h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_inclusive                           ->Fill( Jet1P        , evWeight );
          if (j1_tag_t)  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_inclusive   ->Fill( Jet1P        , evWeight );
        }
        if (DijetDeltaRap>1.0){
          h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_inclusive                           ->Fill( Jet1P        , evWeight );
          if (j1_tag_t)  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_inclusive   ->Fill( Jet1P        , evWeight );
        }
             
        if (newbtagjet0 && newbtagjet1){
          h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_2btag                             ->Fill( Jet1P        , evWeight );
          if (j1_tag_t)  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_2btag     ->Fill( Jet1P        , evWeight );
          if (DijetDeltaRap<=1.0){
            h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_2btag                           ->Fill( Jet1P        , evWeight );
            if (j1_tag_t)  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_2btag   ->Fill( Jet1P        , evWeight );
          }
          if (DijetDeltaRap>1.0){
            h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_2btag                           ->Fill( Jet1P        , evWeight );
            if (j1_tag_t)  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_2btag   ->Fill( Jet1P        , evWeight );
          }
        }
        if ( (newbtagjet0 && !newbtagjet1) || (newbtagjet1 && !newbtagjet0) ){
          h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_1btag                             ->Fill( Jet1P        , evWeight );
          if (j1_tag_t)  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_1btag     ->Fill( Jet1P        , evWeight );
          if (DijetDeltaRap<=1.0){
            h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_1btag                           ->Fill( Jet1P        , evWeight );
            if (j1_tag_t)  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_1btag   ->Fill( Jet1P        , evWeight );
          }
          if (DijetDeltaRap>1.0){
            h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_1btag                           ->Fill( Jet1P        , evWeight );
            if (j1_tag_t)  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_1btag   ->Fill( Jet1P        , evWeight );
          }
        }
        if (!newbtagjet0 && ! newbtagjet1){
          h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_0btag                             ->Fill( Jet1P        , evWeight );
          if (j1_tag_t)  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_0btag     ->Fill( Jet1P        , evWeight );
          if (DijetDeltaRap<=1.0){
            h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_0btag                           ->Fill( Jet1P        , evWeight );
            if (j1_tag_t)  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_0btag   ->Fill( Jet1P        , evWeight );
          }
          if (DijetDeltaRap>1.0){
            h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_0btag                           ->Fill( Jet1P        , evWeight );
            if (j1_tag_t)  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_0btag   ->Fill( Jet1P        , evWeight );
          }
        }
      }
    }
    else if ( rand_mistag >= 0.5 ){  // 50% of the time choose jet 1 to be the anti-tag and jet 0 to be the probe
       //----------anti-tag tau32, keep jet in SD mass window
      if (j1_antitag_tau32_tag_mass){
        h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_inclusive                             ->Fill( Jet0P        , evWeight );
        if (j0_tag_t)  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_inclusive     ->Fill( Jet0P        , evWeight );
        if (DijetDeltaRap<=1.0){
          h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_inclusive                           ->Fill( Jet0P        , evWeight );
          if (j0_tag_t)  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_inclusive   ->Fill( Jet0P        , evWeight );
        }
        if (DijetDeltaRap>1.0){
          h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_inclusive                           ->Fill( Jet0P        , evWeight );
          if (j0_tag_t)  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_inclusive   ->Fill( Jet0P        , evWeight );
        }
             
        if (newbtagjet0 && newbtagjet1){
          h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_2btag                             ->Fill( Jet0P        , evWeight );
          if (j0_tag_t)  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_2btag     ->Fill( Jet0P        , evWeight );
          if (DijetDeltaRap<=1.0){
            h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_2btag                           ->Fill( Jet0P        , evWeight );
            if (j0_tag_t)  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_2btag   ->Fill( Jet0P        , evWeight );
          }
          if (DijetDeltaRap>1.0){
            h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_2btag                           ->Fill( Jet0P        , evWeight );
            if (j0_tag_t)  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_2btag   ->Fill( Jet0P        , evWeight );
          }
        }
        if ( (newbtagjet0 && !newbtagjet1) || (newbtagjet1 && !newbtagjet0) ){
          h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_1btag                             ->Fill( Jet0P        , evWeight );
          if (j0_tag_t)  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_1btag     ->Fill( Jet0P        , evWeight );
          if (DijetDeltaRap<=1.0){
            h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_1btag                           ->Fill( Jet0P        , evWeight );
            if (j0_tag_t)  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_1btag   ->Fill( Jet0P        , evWeight );
          }
          if (DijetDeltaRap>1.0){
            h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_1btag                           ->Fill( Jet0P        , evWeight );
            if (j0_tag_t)  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_1btag   ->Fill( Jet0P        , evWeight );
          }
        }
        if (!newbtagjet0 && ! newbtagjet1){
          h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_0btag                             ->Fill( Jet0P        , evWeight );
          if (j0_tag_t)  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_0btag     ->Fill( Jet0P        , evWeight );
          if (DijetDeltaRap<=1.0){
            h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_0btag                           ->Fill( Jet0P        , evWeight );
            if (j0_tag_t)  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_0btag   ->Fill( Jet0P        , evWeight );
          }
          if (DijetDeltaRap>1.0){
            h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_0btag                           ->Fill( Jet0P        , evWeight );
            if (j0_tag_t)  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_0btag   ->Fill( Jet0P        , evWeight );
          }
        }
      }
    }
    // Plot some Variables
 
    h_DijetMass_dRapIn                         ->Fill( DijetMass                );   
    if (DijetDeltaRap  <1) h_DijetMass_dRapLo  ->Fill( DijetMass                );                                                    
    if (DijetDeltaRap >=1) h_DijetMass_dRapHi  ->Fill( DijetMass                );                           
                   
    h_DeltaRap                                 ->Fill( DijetDeltaRap            );         
    h_DeltaPhi                                 ->Fill( DijetDeltaPhi            );        
    h_HT                                       ->Fill( HT                       );   
    h_MET                                      ->Fill( AllHadMETpt              );   
    h_METphi                                   ->Fill( AllHadMETphi             );   
    h_Nvtx                                     ->Fill( AllHadNvtx               );   
    h_Jet0P                                    ->Fill( Jet0P                    );          
    h_Jet0Pt                                   ->Fill( Jet0Pt                   );          
    h_Jet0Phi                                  ->Fill( Jet0Phi                  );          
    h_Jet0Rap                                  ->Fill( Jet0Rap                  );          
    h_Jet0SDmassCorrL23                        ->Fill( Jet0SDmassCorrL23        );          
    h_Jet0SDmassCorrL23Up                      ->Fill( Jet0SDmassCorrL23Up      );                        
    h_Jet0Tau1                                 ->Fill( Jet0Tau1                 );          
    h_Jet0Tau2                                 ->Fill( Jet0Tau2                 );          
    h_Jet0Tau3                                 ->Fill( Jet0Tau3                 );          
    h_Jet0Tau4                                 ->Fill( Jet0Tau4                 );                                 
    h_Jet0SDmaxbdisc                           ->Fill( Jet0SDmaxbdisc           );        
    h_Jet0SDsubjet0pt                          ->Fill( Jet0SDsubjet0pt          );          
    h_Jet0SDsubjet0mass                        ->Fill( Jet0SDsubjet0mass        );                   
    h_Jet0SDsubjet0tau1                        ->Fill( Jet0SDsubjet0tau1        );          
    h_Jet0SDsubjet0tau2                        ->Fill( Jet0SDsubjet0tau2        );          
    h_Jet0SDsubjet0tau3                        ->Fill( Jet0SDsubjet0tau3        );          
    h_Jet0SDsubjet0bdisc                       ->Fill( Jet0SDsubjet0bdisc       );          
    h_Jet0SDsubjet1pt                          ->Fill( Jet0SDsubjet1pt          );          
    h_Jet0SDsubjet1mass                        ->Fill( Jet0SDsubjet1mass        );                                     
    h_Jet0SDsubjet1tau1                        ->Fill( Jet0SDsubjet1tau1        );          
    h_Jet0SDsubjet1tau2                        ->Fill( Jet0SDsubjet1tau2        );          
    h_Jet0SDsubjet1tau3                        ->Fill( Jet0SDsubjet1tau3        );          
    h_Jet0SDsubjet1bdisc                       ->Fill( Jet0SDsubjet1bdisc       );          
    h_Jet0PuppiPt                              ->Fill( Jet0PuppiPt              );                                
    h_Jet0PuppiMass                            ->Fill( Jet0PuppiMass            );                         
    h_Jet0PuppiSDpt                            ->Fill( Jet0PuppiSDpt            );                              
    h_Jet0PuppiTau1                            ->Fill( Jet0PuppiTau1            );          
    h_Jet0PuppiTau2                            ->Fill( Jet0PuppiTau2            );          
    h_Jet0PuppiTau3                            ->Fill( Jet0PuppiTau3            );          
    h_Jet0PuppiTau4                            ->Fill( Jet0PuppiTau4            );                              
    h_Jet0PuppiSDmaxbdisc                      ->Fill( Jet0PuppiSDmaxbdisc      );             
    h_Jet0PuppiSDsubjet0pt                     ->Fill( Jet0PuppiSDsubjet0pt     );          
    h_Jet0PuppiSDsubjet0mass                   ->Fill( Jet0PuppiSDsubjet0mass   );          
    h_Jet0PuppiSDsubjet0tau1                   ->Fill( Jet0PuppiSDsubjet0tau1   );          
    h_Jet0PuppiSDsubjet0tau2                   ->Fill( Jet0PuppiSDsubjet0tau2   );          
    h_Jet0PuppiSDsubjet0tau3                   ->Fill( Jet0PuppiSDsubjet0tau3   );          
    h_Jet0PuppiSDsubjet0bdisc                  ->Fill( Jet0PuppiSDsubjet0bdisc  );          
    h_Jet0PuppiSDsubjet1pt                     ->Fill( Jet0PuppiSDsubjet1pt     );          
    h_Jet0PuppiSDsubjet1mass                   ->Fill( Jet0PuppiSDsubjet1mass   );          
    h_Jet0PuppiSDsubjet1tau1                   ->Fill( Jet0PuppiSDsubjet1tau1   );          
    h_Jet0PuppiSDsubjet1tau2                   ->Fill( Jet0PuppiSDsubjet1tau2   );          
    h_Jet0PuppiSDsubjet1tau3                   ->Fill( Jet0PuppiSDsubjet1tau3   );          
    h_Jet0PuppiSDsubjet1bdisc                  ->Fill( Jet0PuppiSDsubjet1bdisc  );
    h_Jet0CHF                                  ->Fill( Jet0CHF                  );          
    h_Jet0NHF                                  ->Fill( Jet0NHF                  );          
    h_Jet0CM                                   ->Fill( Jet0CM                   );          
    h_Jet0NM                                   ->Fill( Jet0NM                   );          
    h_Jet0NEF                                  ->Fill( Jet0NEF                  );          
    h_Jet0CEF                                  ->Fill( Jet0CEF                  );          
    h_Jet0MF                                   ->Fill( Jet0MF                   );          
    h_Jet0Mult                                 ->Fill( Jet0Mult                 );          



    if (double_tag_t){
  
      if (!isFrozen || !isData ){    
        h_2ttag_inclu_dRapIn_DijetMass                        ->Fill( DijetMass );  
        if (DijetDeltaRap >=1) h_2ttag_inclu_dRapLo_DijetMass ->Fill( DijetMass );                          
        if (DijetDeltaRap  <1) h_2ttag_inclu_dRapHi_DijetMass ->Fill( DijetMass );  
      } 
           
      h_2ttag_inclu_DeltaRap                                  ->Fill( DijetDeltaRap            );   
      h_2ttag_inclu_DeltaPhi                                  ->Fill( DijetDeltaPhi            );   
      h_2ttag_inclu_HT                                        ->Fill( HT                       );   
      h_2ttag_inclu_MET                                       ->Fill( AllHadMETpt              );   
      h_2ttag_inclu_METphi                                    ->Fill( AllHadMETphi             );   
      h_2ttag_inclu_Nvtx                                      ->Fill( AllHadNvtx               );                
      h_2ttag_inclu_Jet0P                                     ->Fill( Jet0P                    );          
      h_2ttag_inclu_Jet0Pt                                    ->Fill( Jet0Pt                   );          
      h_2ttag_inclu_Jet0Phi                                   ->Fill( Jet0Phi                  );          
      h_2ttag_inclu_Jet0Rap                                   ->Fill( Jet0Rap                  );          
      h_2ttag_inclu_Jet0SDmass                                ->Fill( Jet0SDmass               );                           
      h_2ttag_inclu_Jet0SDmassCorrL23                         ->Fill( Jet0SDmassCorrL23        );          
      h_2ttag_inclu_Jet0SDmassCorrL23Up                       ->Fill( Jet0SDmassCorrL23Up      );                        
      h_2ttag_inclu_Jet0Tau1                                  ->Fill( Jet0Tau1                 );          
      h_2ttag_inclu_Jet0Tau2                                  ->Fill( Jet0Tau2                 );          
      h_2ttag_inclu_Jet0Tau3                                  ->Fill( Jet0Tau3                 );          
      h_2ttag_inclu_Jet0Tau4                                  ->Fill( Jet0Tau4                 );                                 
      h_2ttag_inclu_Jet0SDmaxbdisc                            ->Fill( Jet0SDmaxbdisc           );        
      h_2ttag_inclu_Jet0SDsubjet0pt                           ->Fill( Jet0SDsubjet0pt          );          
      h_2ttag_inclu_Jet0SDsubjet0mass                         ->Fill( Jet0SDsubjet0mass        );                   
      h_2ttag_inclu_Jet0SDsubjet0tau1                         ->Fill( Jet0SDsubjet0tau1        );          
      h_2ttag_inclu_Jet0SDsubjet0tau2                         ->Fill( Jet0SDsubjet0tau2        );          
      h_2ttag_inclu_Jet0SDsubjet0tau3                         ->Fill( Jet0SDsubjet0tau3        );          
      h_2ttag_inclu_Jet0SDsubjet0bdisc                        ->Fill( Jet0SDsubjet0bdisc       );          
      h_2ttag_inclu_Jet0SDsubjet1pt                           ->Fill( Jet0SDsubjet1pt          );          
      h_2ttag_inclu_Jet0SDsubjet1mass                         ->Fill( Jet0SDsubjet1mass        );                                     
      h_2ttag_inclu_Jet0SDsubjet1tau1                         ->Fill( Jet0SDsubjet1tau1        );          
      h_2ttag_inclu_Jet0SDsubjet1tau2                         ->Fill( Jet0SDsubjet1tau2        );          
      h_2ttag_inclu_Jet0SDsubjet1tau3                         ->Fill( Jet0SDsubjet1tau3        );          
      h_2ttag_inclu_Jet0SDsubjet1bdisc                        ->Fill( Jet0SDsubjet1bdisc       );          
      h_2ttag_inclu_Jet0PuppiPt                               ->Fill( Jet0PuppiPt              );                                
      h_2ttag_inclu_Jet0PuppiMass                             ->Fill( Jet0PuppiMass            );                         
      h_2ttag_inclu_Jet0PuppiSDpt                             ->Fill( Jet0PuppiSDpt            );                              
      h_2ttag_inclu_Jet0PuppiTau1                             ->Fill( Jet0PuppiTau1            );          
      h_2ttag_inclu_Jet0PuppiTau2                             ->Fill( Jet0PuppiTau2            );          
      h_2ttag_inclu_Jet0PuppiTau3                             ->Fill( Jet0PuppiTau3            );          
      h_2ttag_inclu_Jet0PuppiTau4                             ->Fill( Jet0PuppiTau4            );                              
      h_2ttag_inclu_Jet0PuppiSDmaxbdisc                       ->Fill( Jet0PuppiSDmaxbdisc      );             
      h_2ttag_inclu_Jet0PuppiSDsubjet0pt                      ->Fill( Jet0PuppiSDsubjet0pt     );          
      h_2ttag_inclu_Jet0PuppiSDsubjet0mass                    ->Fill( Jet0PuppiSDsubjet0mass   );          
      h_2ttag_inclu_Jet0PuppiSDsubjet0tau1                    ->Fill( Jet0PuppiSDsubjet0tau1   );          
      h_2ttag_inclu_Jet0PuppiSDsubjet0tau2                    ->Fill( Jet0PuppiSDsubjet0tau2   );          
      h_2ttag_inclu_Jet0PuppiSDsubjet0tau3                    ->Fill( Jet0PuppiSDsubjet0tau3   );          
      h_2ttag_inclu_Jet0PuppiSDsubjet0bdisc                   ->Fill( Jet0PuppiSDsubjet0bdisc  );          
      h_2ttag_inclu_Jet0PuppiSDsubjet1pt                      ->Fill( Jet0PuppiSDsubjet1pt     );          
      h_2ttag_inclu_Jet0PuppiSDsubjet1mass                    ->Fill( Jet0PuppiSDsubjet1mass   );          
      h_2ttag_inclu_Jet0PuppiSDsubjet1tau1                    ->Fill( Jet0PuppiSDsubjet1tau1   );          
      h_2ttag_inclu_Jet0PuppiSDsubjet1tau2                    ->Fill( Jet0PuppiSDsubjet1tau2   );          
      h_2ttag_inclu_Jet0PuppiSDsubjet1tau3                    ->Fill( Jet0PuppiSDsubjet1tau3   );          
      h_2ttag_inclu_Jet0PuppiSDsubjet1bdisc                   ->Fill( Jet0PuppiSDsubjet1bdisc  );
      h_2ttag_inclu_Jet0CHF                                   ->Fill( Jet0CHF                  );          
      h_2ttag_inclu_Jet0NHF                                   ->Fill( Jet0NHF                  );          
      h_2ttag_inclu_Jet0CM                                    ->Fill( Jet0CM                   );          
      h_2ttag_inclu_Jet0NM                                    ->Fill( Jet0NM                   );          
      h_2ttag_inclu_Jet0NEF                                   ->Fill( Jet0NEF                  );          
      h_2ttag_inclu_Jet0CEF                                   ->Fill( Jet0CEF                  );          
      h_2ttag_inclu_Jet0MF                                    ->Fill( Jet0MF                   );          
      h_2ttag_inclu_Jet0Mult                                  ->Fill( Jet0Mult                 );          
    }
    if (double_tag_t_b){
      if (!isFrozen || !isData ){       
        h_2ttag_2btag_dRapIn_DijetMass                        ->Fill( DijetMass                );  
        if (DijetDeltaRap >=1) h_2ttag_2btag_dRapLo_DijetMass ->Fill( DijetMass                );                          
        if (DijetDeltaRap  <1) h_2ttag_2btag_dRapHi_DijetMass ->Fill( DijetMass                );  
      }              
      h_2ttag_2btag_DeltaRap                                  ->Fill( DijetDeltaRap            );   
      h_2ttag_2btag_DeltaPhi                                  ->Fill( DijetDeltaPhi            ); 
      h_2ttag_2btag_HT                                        ->Fill( HT                       );   
      h_2ttag_2btag_MET                                       ->Fill( AllHadMETpt              );   
      h_2ttag_2btag_METphi                                    ->Fill( AllHadMETphi             );   
      h_2ttag_2btag_METphi                                    ->Fill( AllHadNvtx               );   

      h_2ttag_2btag_Jet0PuppiSDsubjet0pt                      ->Fill( Jet0PuppiSDsubjet0pt     );          
      h_2ttag_2btag_Jet0PuppiSDsubjet0mass                    ->Fill( Jet0PuppiSDsubjet0mass   );          
      h_2ttag_2btag_Jet0PuppiSDsubjet0tau1                    ->Fill( Jet0PuppiSDsubjet0tau1   );          
      h_2ttag_2btag_Jet0PuppiSDsubjet0tau2                    ->Fill( Jet0PuppiSDsubjet0tau2   );          
      h_2ttag_2btag_Jet0PuppiSDsubjet0tau3                    ->Fill( Jet0PuppiSDsubjet0tau3   );          
      h_2ttag_2btag_Jet0PuppiSDsubjet0bdisc                   ->Fill( Jet0PuppiSDsubjet0bdisc  );          
      h_2ttag_2btag_Jet0PuppiSDsubjet1pt                      ->Fill( Jet0PuppiSDsubjet1pt     );          
      h_2ttag_2btag_Jet0PuppiSDsubjet1mass                    ->Fill( Jet0PuppiSDsubjet1mass   );          
      h_2ttag_2btag_Jet0PuppiSDsubjet1tau1                    ->Fill( Jet0PuppiSDsubjet1tau1   );          
      h_2ttag_2btag_Jet0PuppiSDsubjet1tau2                    ->Fill( Jet0PuppiSDsubjet1tau2   );          
      h_2ttag_2btag_Jet0PuppiSDsubjet1tau3                    ->Fill( Jet0PuppiSDsubjet1tau3   );          
      h_2ttag_2btag_Jet0PuppiSDsubjet1bdisc                   ->Fill( Jet0PuppiSDsubjet1bdisc  );

    }
    if (double_tag_t_single_tag_b){

      if (!isFrozen || !isData ){      
        h_2ttag_1btag_dRapIn_DijetMass                        ->Fill( DijetMass                );  
        if (DijetDeltaRap >=1) h_2ttag_1btag_dRapLo_DijetMass ->Fill( DijetMass                );                          
        if (DijetDeltaRap  <1) h_2ttag_1btag_dRapHi_DijetMass ->Fill( DijetMass                ); 
      }              
      h_2ttag_1btag_DeltaRap                                  ->Fill( DijetDeltaRap            );   
      h_2ttag_1btag_DeltaPhi                                  ->Fill( DijetDeltaPhi            );    
      h_2ttag_1btag_HT                                        ->Fill( HT                       );   
      h_2ttag_1btag_MET                                       ->Fill( AllHadMETpt              );   
      h_2ttag_1btag_METphi                                    ->Fill( AllHadMETphi             );   
      h_2ttag_1btag_METphi                                    ->Fill( AllHadNvtx               );  


      h_2ttag_1btag_Jet0PuppiSDsubjet0pt                      ->Fill( Jet0PuppiSDsubjet0pt     );          
      h_2ttag_1btag_Jet0PuppiSDsubjet0mass                    ->Fill( Jet0PuppiSDsubjet0mass   );          
      h_2ttag_1btag_Jet0PuppiSDsubjet0tau1                    ->Fill( Jet0PuppiSDsubjet0tau1   );          
      h_2ttag_1btag_Jet0PuppiSDsubjet0tau2                    ->Fill( Jet0PuppiSDsubjet0tau2   );          
      h_2ttag_1btag_Jet0PuppiSDsubjet0tau3                    ->Fill( Jet0PuppiSDsubjet0tau3   );          
      h_2ttag_1btag_Jet0PuppiSDsubjet0bdisc                   ->Fill( Jet0PuppiSDsubjet0bdisc  );          
      h_2ttag_1btag_Jet0PuppiSDsubjet1pt                      ->Fill( Jet0PuppiSDsubjet1pt     );          
      h_2ttag_1btag_Jet0PuppiSDsubjet1mass                    ->Fill( Jet0PuppiSDsubjet1mass   );          
      h_2ttag_1btag_Jet0PuppiSDsubjet1tau1                    ->Fill( Jet0PuppiSDsubjet1tau1   );          
      h_2ttag_1btag_Jet0PuppiSDsubjet1tau2                    ->Fill( Jet0PuppiSDsubjet1tau2   );          
      h_2ttag_1btag_Jet0PuppiSDsubjet1tau3                    ->Fill( Jet0PuppiSDsubjet1tau3   );          
      h_2ttag_1btag_Jet0PuppiSDsubjet1bdisc                   ->Fill( Jet0PuppiSDsubjet1bdisc  );

    }     
     if (double_tag_t_no_b){
      if (!isFrozen || !isData ){      
        h_2ttag_0btag_dRapIn_DijetMass                        ->Fill( DijetMass                );  
        if (DijetDeltaRap >=1) h_2ttag_0btag_dRapLo_DijetMass ->Fill( DijetMass                );                          
        if (DijetDeltaRap  <1) h_2ttag_0btag_dRapHi_DijetMass ->Fill( DijetMass                ); 
      }    
      h_2ttag_0btag_DeltaRap                                  ->Fill( DijetDeltaRap            );   
      h_2ttag_0btag_DeltaPhi                                  ->Fill( DijetDeltaPhi            );              
      h_2ttag_0btag_HT                                        ->Fill( HT                       );   
      h_2ttag_0btag_MET                                       ->Fill( AllHadMETpt              );   
      h_2ttag_0btag_METphi                                    ->Fill( AllHadMETphi             );   
      h_2ttag_0btag_METphi                                    ->Fill( AllHadNvtx               );  


      h_2ttag_0btag_Jet0PuppiSDsubjet0pt                      ->Fill( Jet0PuppiSDsubjet0pt     );          
      h_2ttag_0btag_Jet0PuppiSDsubjet0mass                    ->Fill( Jet0PuppiSDsubjet0mass   );          
      h_2ttag_0btag_Jet0PuppiSDsubjet0tau1                    ->Fill( Jet0PuppiSDsubjet0tau1   );          
      h_2ttag_0btag_Jet0PuppiSDsubjet0tau2                    ->Fill( Jet0PuppiSDsubjet0tau2   );          
      h_2ttag_0btag_Jet0PuppiSDsubjet0tau3                    ->Fill( Jet0PuppiSDsubjet0tau3   );          
      h_2ttag_0btag_Jet0PuppiSDsubjet0bdisc                   ->Fill( Jet0PuppiSDsubjet0bdisc  );          
      h_2ttag_0btag_Jet0PuppiSDsubjet1pt                      ->Fill( Jet0PuppiSDsubjet1pt     );          
      h_2ttag_0btag_Jet0PuppiSDsubjet1mass                    ->Fill( Jet0PuppiSDsubjet1mass   );          
      h_2ttag_0btag_Jet0PuppiSDsubjet1tau1                    ->Fill( Jet0PuppiSDsubjet1tau1   );          
      h_2ttag_0btag_Jet0PuppiSDsubjet1tau2                    ->Fill( Jet0PuppiSDsubjet1tau2   );          
      h_2ttag_0btag_Jet0PuppiSDsubjet1tau3                    ->Fill( Jet0PuppiSDsubjet1tau3   );          
      h_2ttag_0btag_Jet0PuppiSDsubjet1bdisc                   ->Fill( Jet0PuppiSDsubjet1bdisc  );

    }     


 

    // Jet mass with different tagging requirements
                                                   h_Jet0SDmass                                    ->Fill( Jet0SDmass );
    if (j0_tag_b)                                  h_Jet0SDmass_JetTag_b                           ->Fill( Jet0SDmass );
    if (j0_tag_tau32)                              h_Jet0SDmass_JetTag_tau32                       ->Fill( Jet0SDmass );
    if (j0_tag_b && j0_tag_tau32)                  h_Jet0SDmass_JetTag_b_tau32                     ->Fill( Jet0SDmass );
    if (j1_tag_t_b)                                h_Jet0SDmass_OppositeJetTag_t_b                 ->Fill( Jet0SDmass );
    if (j1_tag_t_b && j0_tag_b )                   h_Jet0SDmass_OppositeJetTag_t_b_JetTag_b        ->Fill( Jet0SDmass );
    if (j1_tag_t_b && j0_tag_b && j0_tag_tau32 )   h_Jet0SDmass_OppositeJetTag_t_b_JetTag_b_tau32  ->Fill( Jet0SDmass );
    
                                                   h_Jet1SDmass                                    ->Fill( Jet1SDmass );
    if (j1_tag_b)                                  h_Jet1SDmass_JetTag_b                           ->Fill( Jet1SDmass );
    if (j1_tag_tau32)                              h_Jet1SDmass_JetTag_tau32                       ->Fill( Jet1SDmass );
    if (j1_tag_b && j1_tag_tau32)                  h_Jet1SDmass_JetTag_b_tau32                     ->Fill( Jet1SDmass );
    if (j0_tag_t_b)                                h_Jet1SDmass_OppositeJetTag_t_b                 ->Fill( Jet1SDmass );
    if (j0_tag_t_b && j1_tag_b )                   h_Jet1SDmass_OppositeJetTag_t_b_JetTag_b        ->Fill( Jet1SDmass );
    if (j0_tag_t_b && j1_tag_b && j1_tag_tau32 )   h_Jet1SDmass_OppositeJetTag_t_b_JetTag_b_tau32  ->Fill( Jet1SDmass );

                                                   h_JetSDmass                                     ->Fill( Jet0SDmass );
    if (j0_tag_b)                                  h_JetSDmass_JetTag_b                            ->Fill( Jet0SDmass );
    if (j0_tag_tau32)                              h_JetSDmass_JetTag_tau32                        ->Fill( Jet0SDmass );
    if (j0_tag_b && j0_tag_tau32)                  h_JetSDmass_JetTag_b_tau32                      ->Fill( Jet0SDmass );
    if (j1_tag_t_b)                                h_JetSDmass_OppositeJetTag_t_b                  ->Fill( Jet0SDmass );
    if (j1_tag_t_b && j0_tag_b )                   h_JetSDmass_OppositeJetTag_t_b_JetTag_b         ->Fill( Jet0SDmass );
    if (j1_tag_t_b && j0_tag_b && j0_tag_tau32 )   h_JetSDmass_OppositeJetTag_t_b_JetTag_b_tau32   ->Fill( Jet0SDmass );
                                                   h_JetSDmass                                     ->Fill( Jet1SDmass );
    if (j1_tag_b)                                  h_JetSDmass_JetTag_b                            ->Fill( Jet1SDmass );
    if (j1_tag_tau32)                              h_JetSDmass_JetTag_tau32                        ->Fill( Jet1SDmass );
    if (j1_tag_b && j1_tag_tau32)                  h_JetSDmass_JetTag_b_tau32                      ->Fill( Jet1SDmass );
    if (j0_tag_t_b)                                h_JetSDmass_OppositeJetTag_t_b                  ->Fill( Jet1SDmass );
    if (j0_tag_t_b && j1_tag_b )                   h_JetSDmass_OppositeJetTag_t_b_JetTag_b         ->Fill( Jet1SDmass );
    if (j0_tag_t_b && j1_tag_b && j1_tag_tau32 )   h_JetSDmass_OppositeJetTag_t_b_JetTag_b_tau32   ->Fill( Jet1SDmass );

                                                   h_Jet0Tau32                                     ->Fill( Jet0Tau32 );
    if (j0_tag_b)                                  h_Jet0Tau32_JetTag_b                            ->Fill( Jet0Tau32 );
    if (j0_tag_mass)                               h_Jet0Tau32_JetTag_mass                         ->Fill( Jet0Tau32 );
    if (j0_tag_b && j0_tag_mass)                   h_Jet0Tau32_JetTag_b_mass                       ->Fill( Jet0Tau32 );
    if (j1_tag_t_b)                                h_Jet0Tau32_OppositeJetTag_t_b                  ->Fill( Jet0Tau32 );
    if (j1_tag_t_b && j0_tag_b )                   h_Jet0Tau32_OppositeJetTag_t_b_JetTag_b         ->Fill( Jet0Tau32 );
    if (j1_tag_t_b && j0_tag_b && j0_tag_mass)     h_Jet0Tau32_OppositeJetTag_t_b_JetTag_b_mass    ->Fill( Jet0Tau32 );
    
                                                   h_Jet1Tau32                                     ->Fill( Jet1Tau32 );
    if (j1_tag_b)                                  h_Jet1Tau32_JetTag_b                            ->Fill( Jet1Tau32 );
    if (j1_tag_mass)                               h_Jet1Tau32_JetTag_mass                         ->Fill( Jet1Tau32 );
    if (j1_tag_b && j1_tag_mass)                   h_Jet1Tau32_JetTag_b_mass                       ->Fill( Jet1Tau32 );
    if (j0_tag_t_b)                                h_Jet1Tau32_OppositeJetTag_t_b                  ->Fill( Jet1Tau32 );
    if (j0_tag_t_b && j1_tag_b )                   h_Jet1Tau32_OppositeJetTag_t_b_JetTag_b         ->Fill( Jet1Tau32 );
    if (j0_tag_t_b && j1_tag_b && j1_tag_mass )    h_Jet1Tau32_OppositeJetTag_t_b_JetTag_b_mass    ->Fill( Jet1Tau32 );

                                                   h_JetTau32                                      ->Fill( Jet0Tau32 );
    if (j0_tag_b)                                  h_JetTau32_JetTag_b                             ->Fill( Jet0Tau32 );
    if (j0_tag_mass)                               h_JetTau32_JetTag_mass                          ->Fill( Jet0Tau32 );
    if (j0_tag_b && j0_tag_mass)                   h_JetTau32_JetTag_b_mass                        ->Fill( Jet0Tau32 );
    if (j1_tag_t_b)                                h_JetTau32_OppositeJetTag_t_b                   ->Fill( Jet0Tau32 );
    if (j1_tag_t_b && j0_tag_b )                   h_JetTau32_OppositeJetTag_t_b_JetTag_b          ->Fill( Jet0Tau32 );
    if (j1_tag_t_b && j0_tag_b && j0_tag_mass )    h_JetTau32_OppositeJetTag_t_b_JetTag_b_mass     ->Fill( Jet0Tau32 );
                                                   h_JetTau32                                      ->Fill( Jet1Tau32 );
    if (j1_tag_b)                                  h_JetTau32_JetTag_b                             ->Fill( Jet1Tau32 );
    if (j1_tag_mass)                               h_JetTau32_JetTag_mass                          ->Fill( Jet1Tau32 );
    if (j1_tag_b && j1_tag_mass)                   h_JetTau32_JetTag_b_mass                        ->Fill( Jet1Tau32 );
    if (j0_tag_t_b)                                h_JetTau32_OppositeJetTag_t_b                   ->Fill( Jet1Tau32 );
    if (j0_tag_t_b && j1_tag_b )                   h_JetTau32_OppositeJetTag_t_b_JetTag_b          ->Fill( Jet1Tau32 );
    if (j0_tag_t_b && j1_tag_b && j1_tag_mass )    h_JetTau32_OppositeJetTag_t_b_JetTag_b_mass     ->Fill( Jet1Tau32 );












    if (!isData) {
      // GenMatch bools
      double gen_match_condition = 0.8;
      bool j0_match_Wd1 = Jet0GenMatched_DeltaR_jet_Wd1 < gen_match_condition ;  
      bool j0_match_Wd2 = Jet0GenMatched_DeltaR_jet_Wd2 < gen_match_condition ;  
      bool j0_match_b   = Jet0GenMatched_DeltaR_jet_b   < gen_match_condition ; 

      // Old tests
      if (Jet0GenMatched_DeltaR_jet_t<0.8) h_Jet0SDmass_matchedTop->Fill( Jet0SDmass );
      if (Jet0GenMatched_DeltaR_jet_t<0.8 && Jet0GenMatched_MaxDeltaRPartonTop < 0.8 ) h_Jet0SDmass_matchedTop_topDist->Fill( Jet0SDmass );
      else h_Jet0SDmass_outside->Fill( Jet0SDmass );

      // Top decay combinatorics within the jet (ttbarMC)
      h_Jet0SDmass_all ->Fill( Jet0SDmass );
      if      (  j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_in_qqb    ->Fill( Jet0SDmass );
      else if (  j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_in_qq     ->Fill( Jet0SDmass );
      else if (  j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_in_qb     ->Fill( Jet0SDmass );
      else if ( !j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_in_qb     ->Fill( Jet0SDmass );
      else if ( !j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_in_b      ->Fill( Jet0SDmass );
      else if ( !j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_in_q      ->Fill( Jet0SDmass );
      else if (  j0_match_Wd1 && !j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_in_q      ->Fill( Jet0SDmass );
      else                                                            h_Jet0SDmass_unmatched ->Fill( Jet0SDmass );
    
      h_Jet0Tau32_all ->Fill( Jet0Tau32 );
      if      (  j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_in_qqb    ->Fill( Jet0Tau32 );
      else if (  j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_in_qq     ->Fill( Jet0Tau32 );
      else if (  j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_in_qb     ->Fill( Jet0Tau32 );
      else if ( !j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_in_qb     ->Fill( Jet0Tau32 );
      else if ( !j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_in_b      ->Fill( Jet0Tau32 );
      else if ( !j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_in_q      ->Fill( Jet0Tau32 );
      else if (  j0_match_Wd1 && !j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_in_q      ->Fill( Jet0Tau32 );
      else                                                            h_Jet0Tau32_unmatched ->Fill( Jet0Tau32 );
    

      if (Jet0Pt>600){
        h_Jet0SDmass_Pt600_all ->Fill( Jet0SDmass );
        if      (  j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_Pt600_in_qqb    ->Fill( Jet0SDmass );
        else if (  j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_Pt600_in_qq     ->Fill( Jet0SDmass );
        else if (  j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_Pt600_in_qb     ->Fill( Jet0SDmass );
        else if ( !j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_Pt600_in_qb     ->Fill( Jet0SDmass );
        else if ( !j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_Pt600_in_b      ->Fill( Jet0SDmass );
        else if ( !j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_Pt600_in_q      ->Fill( Jet0SDmass );
        else if (  j0_match_Wd1 && !j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_Pt600_in_q      ->Fill( Jet0SDmass );
        else                                                            h_Jet0SDmass_Pt600_unmatched ->Fill( Jet0SDmass );
       
        h_Jet0Tau32_Pt600_all ->Fill( Jet0Tau32 );
        if      (  j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_Pt600_in_qqb    ->Fill( Jet0Tau32 );
        else if (  j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_Pt600_in_qq     ->Fill( Jet0Tau32 );
        else if (  j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_Pt600_in_qb     ->Fill( Jet0Tau32 );
        else if ( !j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_Pt600_in_qb     ->Fill( Jet0Tau32 );
        else if ( !j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_Pt600_in_b      ->Fill( Jet0Tau32 );
        else if ( !j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_Pt600_in_q      ->Fill( Jet0Tau32 );
        else if (  j0_match_Wd1 && !j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_Pt600_in_q      ->Fill( Jet0Tau32 );
        else                                                            h_Jet0Tau32_Pt600_unmatched ->Fill( Jet0Tau32 );
      }

      if (j0_tag_b){
        h_Jet0SDmass_BtagM_all ->Fill( Jet0SDmass );
        if      (  j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_BtagM_in_qqb    ->Fill( Jet0SDmass );
        else if (  j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_BtagM_in_qq     ->Fill( Jet0SDmass );
        else if (  j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_BtagM_in_qb     ->Fill( Jet0SDmass );
        else if ( !j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_BtagM_in_qb     ->Fill( Jet0SDmass );
        else if ( !j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_BtagM_in_b      ->Fill( Jet0SDmass );
        else if ( !j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_BtagM_in_q      ->Fill( Jet0SDmass );
        else if (  j0_match_Wd1 && !j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_BtagM_in_q      ->Fill( Jet0SDmass );
        else                                                            h_Jet0SDmass_BtagM_unmatched ->Fill( Jet0SDmass );
        
        h_Jet0Tau32_BtagM_all ->Fill( Jet0Tau32 );
        if      (  j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_BtagM_in_qqb    ->Fill( Jet0Tau32 );
        else if (  j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_BtagM_in_qq     ->Fill( Jet0Tau32 );
        else if (  j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_BtagM_in_qb     ->Fill( Jet0Tau32 );
        else if ( !j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_BtagM_in_qb     ->Fill( Jet0Tau32 );
        else if ( !j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_BtagM_in_b      ->Fill( Jet0Tau32 );
        else if ( !j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_BtagM_in_q      ->Fill( Jet0Tau32 );
        else if (  j0_match_Wd1 && !j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_BtagM_in_q      ->Fill( Jet0Tau32 );
        else                                                            h_Jet0Tau32_BtagM_unmatched ->Fill( Jet0Tau32 );
      }

      if (Jet0SDmaxbdisc>0.935){
        h_Jet0SDmass_BtagT_all ->Fill( Jet0SDmass );
        if      (  j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_BtagT_in_qqb    ->Fill( Jet0SDmass );
        else if (  j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_BtagT_in_qq     ->Fill( Jet0SDmass );
        else if (  j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_BtagT_in_qb     ->Fill( Jet0SDmass );
        else if ( !j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_BtagT_in_qb     ->Fill( Jet0SDmass );
        else if ( !j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_BtagT_in_b      ->Fill( Jet0SDmass );
        else if ( !j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_BtagT_in_q      ->Fill( Jet0SDmass );
        else if (  j0_match_Wd1 && !j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_BtagT_in_q      ->Fill( Jet0SDmass );
        else                                                            h_Jet0SDmass_BtagT_unmatched ->Fill( Jet0SDmass );
      }

      if (j0_tag_tau32){
        h_Jet0SDmass_TauTag_all ->Fill( Jet0SDmass );
        if      (  j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_TauTag_in_qqb    ->Fill( Jet0SDmass );
        else if (  j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_TauTag_in_qq     ->Fill( Jet0SDmass );
        else if (  j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_TauTag_in_qb     ->Fill( Jet0SDmass );
        else if ( !j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_TauTag_in_qb     ->Fill( Jet0SDmass );
        else if ( !j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_TauTag_in_b      ->Fill( Jet0SDmass );
        else if ( !j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_TauTag_in_q      ->Fill( Jet0SDmass );
        else if (  j0_match_Wd1 && !j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_TauTag_in_q      ->Fill( Jet0SDmass );
        else                                                            h_Jet0SDmass_TauTag_unmatched ->Fill( Jet0SDmass );
      }

      if (!j0_tag_tau32){
        h_Jet0SDmass_AntiTauTag_all ->Fill( Jet0SDmass );
        if      (  j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_AntiTauTag_in_qqb    ->Fill( Jet0SDmass );
        else if (  j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_AntiTauTag_in_qq     ->Fill( Jet0SDmass );
        else if (  j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_AntiTauTag_in_qb     ->Fill( Jet0SDmass );
        else if ( !j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_AntiTauTag_in_qb     ->Fill( Jet0SDmass );
        else if ( !j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_AntiTauTag_in_b      ->Fill( Jet0SDmass );
        else if ( !j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_AntiTauTag_in_q      ->Fill( Jet0SDmass );
        else if (  j0_match_Wd1 && !j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_AntiTauTag_in_q      ->Fill( Jet0SDmass );
        else                                                            h_Jet0SDmass_AntiTauTag_unmatched ->Fill( Jet0SDmass );
      }

      if (j0_tag_tau32 && j0_tag_b){
        h_Jet0SDmass_BtagM_TauTag_all ->Fill( Jet0SDmass );
        if      (  j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_BtagM_TauTag_in_qqb    ->Fill( Jet0SDmass );
        else if (  j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_BtagM_TauTag_in_qq     ->Fill( Jet0SDmass );
        else if (  j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_BtagM_TauTag_in_qb     ->Fill( Jet0SDmass );
        else if ( !j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_BtagM_TauTag_in_qb     ->Fill( Jet0SDmass );
        else if ( !j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0SDmass_BtagM_TauTag_in_b      ->Fill( Jet0SDmass );
        else if ( !j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_BtagM_TauTag_in_q      ->Fill( Jet0SDmass );
        else if (  j0_match_Wd1 && !j0_match_Wd2 && !j0_match_b)  h_Jet0SDmass_BtagM_TauTag_in_q      ->Fill( Jet0SDmass );
        else                                                            h_Jet0SDmass_BtagM_TauTag_unmatched ->Fill( Jet0SDmass );
      }

      if (j0_tag_mass ){
        h_Jet0Tau32_MassTag_all ->Fill( Jet0Tau32 );
        if      (  j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_MassTag_in_qqb    ->Fill( Jet0Tau32 );
        else if (  j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_MassTag_in_qq     ->Fill( Jet0Tau32 );
        else if (  j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_MassTag_in_qb     ->Fill( Jet0Tau32 );
        else if ( !j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_MassTag_in_qb     ->Fill( Jet0Tau32 );
        else if ( !j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_MassTag_in_b      ->Fill( Jet0Tau32 );
        else if ( !j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_MassTag_in_q      ->Fill( Jet0Tau32 );
        else if (  j0_match_Wd1 && !j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_MassTag_in_q      ->Fill( Jet0Tau32 );
        else                                                            h_Jet0Tau32_MassTag_unmatched ->Fill( Jet0Tau32 );
      }

      if (j0_tag_b && j0_tag_mass ){
        h_Jet0Tau32_BtagM_MassTag_all ->Fill( Jet0Tau32 );
        if      (  j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_BtagM_MassTag_in_qqb    ->Fill( Jet0Tau32 );
        else if (  j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_BtagM_MassTag_in_qq     ->Fill( Jet0Tau32 );
        else if (  j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_BtagM_MassTag_in_qb     ->Fill( Jet0Tau32 );
        else if ( !j0_match_Wd1 &&  j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_BtagM_MassTag_in_qb     ->Fill( Jet0Tau32 );
        else if ( !j0_match_Wd1 && !j0_match_Wd2 &&  j0_match_b)  h_Jet0Tau32_BtagM_MassTag_in_b      ->Fill( Jet0Tau32 );
        else if ( !j0_match_Wd1 &&  j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_BtagM_MassTag_in_q      ->Fill( Jet0Tau32 );
        else if (  j0_match_Wd1 && !j0_match_Wd2 && !j0_match_b)  h_Jet0Tau32_BtagM_MassTag_in_q      ->Fill( Jet0Tau32 );
        else                                                            h_Jet0Tau32_BtagM_MassTag_unmatched ->Fill( Jet0Tau32 );
      }
    }
  }




  string out_filename = "histsAllHad_Sept19_"+input_file;
  TFile * Out = new TFile(out_filename.c_str(),"RECREATE");
  Out->cd();

  h_DijetMass_dRapIn                   ->Write();
  h_2ttag_inclu_dRapIn_DijetMass       ->Write();
  h_2ttag_0btag_dRapIn_DijetMass       ->Write();
  h_2ttag_1btag_dRapIn_DijetMass       ->Write();
  h_2ttag_2btag_dRapIn_DijetMass       ->Write();
  h_DijetMass_dRapLo                   ->Write();
  h_2ttag_inclu_dRapLo_DijetMass       ->Write();
  h_2ttag_0btag_dRapLo_DijetMass       ->Write();
  h_2ttag_1btag_dRapLo_DijetMass       ->Write();
  h_2ttag_2btag_dRapLo_DijetMass       ->Write();
  h_DijetMass_dRapHi                   ->Write();
  h_2ttag_inclu_dRapHi_DijetMass       ->Write();
  h_2ttag_0btag_dRapHi_DijetMass       ->Write();
  h_2ttag_1btag_dRapHi_DijetMass       ->Write();
  h_2ttag_2btag_dRapHi_DijetMass       ->Write();
  h_DeltaRap                           ->Write();
  h_2ttag_inclu_DeltaRap               ->Write();
  h_2ttag_0btag_DeltaRap               ->Write();
  h_2ttag_1btag_DeltaRap               ->Write();
  h_2ttag_2btag_DeltaRap               ->Write();
  h_DeltaPhi                           ->Write();
  h_2ttag_inclu_DeltaPhi               ->Write();
  h_2ttag_0btag_DeltaPhi               ->Write();
  h_2ttag_1btag_DeltaPhi               ->Write();
  h_2ttag_2btag_DeltaPhi               ->Write();
  h_HT                                 ->Write();
  h_2ttag_inclu_HT                     ->Write();
  h_2ttag_0btag_HT                     ->Write();
  h_2ttag_1btag_HT                     ->Write();
  h_2ttag_2btag_HT                     ->Write();
  h_MET                                ->Write();
  h_2ttag_inclu_MET                    ->Write();
  h_2ttag_0btag_MET                    ->Write();
  h_2ttag_1btag_MET                    ->Write();
  h_2ttag_2btag_MET                    ->Write();
  h_METphi                             ->Write();
  h_2ttag_inclu_METphi                 ->Write();
  h_2ttag_0btag_METphi                 ->Write();
  h_2ttag_1btag_METphi                 ->Write();
  h_2ttag_2btag_METphi                 ->Write();
  h_Nvtx                               ->Write();
  h_2ttag_inclu_Nvtx                   ->Write();
  h_2ttag_0btag_Nvtx                   ->Write();
  h_2ttag_1btag_Nvtx                   ->Write();
  h_2ttag_2btag_Nvtx                   ->Write();
                

  h_Jet0P                                ->Write();
  h_Jet0Pt                               ->Write();
  h_Jet0Phi                              ->Write();
  h_Jet0Rap                              ->Write();
  h_Jet0SDmassCorrL23                    ->Write();
  h_Jet0SDmassCorrL23Up                  ->Write();
  h_Jet0Tau1                             ->Write();
  h_Jet0Tau2                             ->Write();
  h_Jet0Tau3                             ->Write();
  h_Jet0Tau4                             ->Write();
  h_Jet0SDmaxbdisc                       ->Write();
  h_Jet0SDsubjet0pt                      ->Write();
  h_Jet0SDsubjet0mass                    ->Write();
  h_Jet0SDsubjet0tau1                    ->Write();
  h_Jet0SDsubjet0tau2                    ->Write();
  h_Jet0SDsubjet0tau3                    ->Write();
  h_Jet0SDsubjet0bdisc                   ->Write();
  h_Jet0SDsubjet1pt                      ->Write();
  h_Jet0SDsubjet1mass                    ->Write();
  h_Jet0SDsubjet1tau1                    ->Write();
  h_Jet0SDsubjet1tau2                    ->Write();
  h_Jet0SDsubjet1tau3                    ->Write();
  h_Jet0SDsubjet1bdisc                   ->Write();
  h_Jet0PuppiPt                          ->Write();
  h_Jet0PuppiMass                        ->Write();
  h_Jet0PuppiSDpt                        ->Write();
  h_Jet0PuppiTau1                        ->Write();
  h_Jet0PuppiTau2                        ->Write();
  h_Jet0PuppiTau3                        ->Write();
  h_Jet0PuppiTau4                        ->Write();
  h_Jet0PuppiSDmaxbdisc                  ->Write();
  h_Jet0PuppiSDsubjet0pt                 ->Write();
  h_Jet0PuppiSDsubjet0mass               ->Write();
  h_Jet0PuppiSDsubjet0tau1               ->Write();
  h_Jet0PuppiSDsubjet0tau2               ->Write();
  h_Jet0PuppiSDsubjet0tau3               ->Write();
  h_Jet0PuppiSDsubjet0bdisc              ->Write();
  h_Jet0PuppiSDsubjet1pt                 ->Write();
  h_Jet0PuppiSDsubjet1mass               ->Write();
  h_Jet0PuppiSDsubjet1tau1               ->Write();
  h_Jet0PuppiSDsubjet1tau2               ->Write();
  h_Jet0PuppiSDsubjet1tau3               ->Write();
  h_Jet0PuppiSDsubjet1bdisc              ->Write();
  h_Jet0CHF                              ->Write();
  h_Jet0NHF                              ->Write();
  h_Jet0CM                               ->Write();
  h_Jet0NM                               ->Write();
  h_Jet0NEF                              ->Write();
  h_Jet0CEF                              ->Write();
  h_Jet0MF                               ->Write();
  h_Jet0Mult                             ->Write();
  h_2ttag_inclu_Jet0P                    ->Write();
  h_2ttag_inclu_Jet0Pt                   ->Write();
  h_2ttag_inclu_Jet0Phi                  ->Write();
  h_2ttag_inclu_Jet0Rap                  ->Write();
  h_2ttag_inclu_Jet0SDmass               ->Write();
  h_2ttag_inclu_Jet0SDmassCorrL23        ->Write();
  h_2ttag_inclu_Jet0SDmassCorrL23Up      ->Write();
  h_2ttag_inclu_Jet0Tau1                 ->Write();
  h_2ttag_inclu_Jet0Tau2                 ->Write();
  h_2ttag_inclu_Jet0Tau3                 ->Write();
  h_2ttag_inclu_Jet0Tau4                 ->Write();
  h_2ttag_inclu_Jet0SDmaxbdisc           ->Write();
  h_2ttag_inclu_Jet0SDsubjet0pt          ->Write();
  h_2ttag_inclu_Jet0SDsubjet0mass        ->Write();
  h_2ttag_inclu_Jet0SDsubjet0tau1        ->Write();
  h_2ttag_inclu_Jet0SDsubjet0tau2        ->Write();
  h_2ttag_inclu_Jet0SDsubjet0tau3        ->Write();
  h_2ttag_inclu_Jet0SDsubjet0bdisc       ->Write();
  h_2ttag_inclu_Jet0SDsubjet1pt          ->Write();
  h_2ttag_inclu_Jet0SDsubjet1mass        ->Write();
  h_2ttag_inclu_Jet0SDsubjet1tau1        ->Write();
  h_2ttag_inclu_Jet0SDsubjet1tau2        ->Write();
  h_2ttag_inclu_Jet0SDsubjet1tau3        ->Write();
  h_2ttag_inclu_Jet0SDsubjet1bdisc       ->Write();
  h_2ttag_inclu_Jet0PuppiPt              ->Write();
  h_2ttag_inclu_Jet0PuppiMass            ->Write();
  h_2ttag_inclu_Jet0PuppiSDpt            ->Write();
  h_2ttag_inclu_Jet0PuppiTau1            ->Write();
  h_2ttag_inclu_Jet0PuppiTau2            ->Write();
  h_2ttag_inclu_Jet0PuppiTau3            ->Write();
  h_2ttag_inclu_Jet0PuppiTau4            ->Write();
  h_2ttag_inclu_Jet0PuppiSDmaxbdisc      ->Write();
  h_2ttag_inclu_Jet0PuppiSDsubjet0pt     ->Write();
  h_2ttag_inclu_Jet0PuppiSDsubjet0mass   ->Write();
  h_2ttag_inclu_Jet0PuppiSDsubjet0tau1   ->Write();
  h_2ttag_inclu_Jet0PuppiSDsubjet0tau2   ->Write();
  h_2ttag_inclu_Jet0PuppiSDsubjet0tau3   ->Write();
  h_2ttag_inclu_Jet0PuppiSDsubjet0bdisc  ->Write();
  h_2ttag_inclu_Jet0PuppiSDsubjet1pt     ->Write();
  h_2ttag_inclu_Jet0PuppiSDsubjet1mass   ->Write();
  h_2ttag_inclu_Jet0PuppiSDsubjet1tau1   ->Write();
  h_2ttag_inclu_Jet0PuppiSDsubjet1tau2   ->Write();
  h_2ttag_inclu_Jet0PuppiSDsubjet1tau3   ->Write();
  h_2ttag_inclu_Jet0PuppiSDsubjet1bdisc  ->Write();
  h_2ttag_inclu_Jet0CHF                  ->Write();
  h_2ttag_inclu_Jet0NHF                  ->Write();
  h_2ttag_inclu_Jet0CM                   ->Write();
  h_2ttag_inclu_Jet0NM                   ->Write();
  h_2ttag_inclu_Jet0NEF                  ->Write();
  h_2ttag_inclu_Jet0CEF                  ->Write();
  h_2ttag_inclu_Jet0MF                   ->Write();
  h_2ttag_inclu_Jet0Mult                 ->Write();


  h_Jet0SDmass                                     ->Write();
  h_Jet0SDmass_JetTag_b                            ->Write();
  h_Jet0SDmass_JetTag_tau32                        ->Write();
  h_Jet0SDmass_JetTag_b_tau32                      ->Write();
  h_Jet0SDmass_OppositeJetTag_t_b                  ->Write();
  h_Jet0SDmass_OppositeJetTag_t_b_JetTag_b         ->Write();
  h_Jet0SDmass_OppositeJetTag_t_b_JetTag_b_tau32   ->Write();
  h_Jet1SDmass                                     ->Write();
  h_Jet1SDmass_JetTag_b                            ->Write();
  h_Jet1SDmass_JetTag_tau32                        ->Write();
  h_Jet1SDmass_JetTag_b_tau32                      ->Write();
  h_Jet1SDmass_OppositeJetTag_t_b                  ->Write();
  h_Jet1SDmass_OppositeJetTag_t_b_JetTag_b         ->Write();
  h_Jet1SDmass_OppositeJetTag_t_b_JetTag_b_tau32   ->Write();
  h_JetSDmass                                      ->Write();
  h_JetSDmass_JetTag_b                             ->Write();
  h_JetSDmass_JetTag_tau32                         ->Write();
  h_JetSDmass_JetTag_b_tau32                       ->Write();
  h_JetSDmass_OppositeJetTag_t_b                   ->Write();
  h_JetSDmass_OppositeJetTag_t_b_JetTag_b          ->Write();
  h_JetSDmass_OppositeJetTag_t_b_JetTag_b_tau32    ->Write();
  h_Jet0Tau32                                      ->Write();
  h_Jet0Tau32_JetTag_b                             ->Write();
  h_Jet0Tau32_JetTag_mass                          ->Write();
  h_Jet0Tau32_JetTag_b_mass                        ->Write();
  h_Jet0Tau32_OppositeJetTag_t_b                   ->Write();
  h_Jet0Tau32_OppositeJetTag_t_b_JetTag_b          ->Write();
  h_Jet0Tau32_OppositeJetTag_t_b_JetTag_b_mass     ->Write();
  h_Jet1Tau32                                      ->Write();
  h_Jet1Tau32_JetTag_b                             ->Write();
  h_Jet1Tau32_JetTag_mass                          ->Write();
  h_Jet1Tau32_JetTag_b_mass                        ->Write();
  h_Jet1Tau32_OppositeJetTag_t_b                   ->Write();
  h_Jet1Tau32_OppositeJetTag_t_b_JetTag_b          ->Write();
  h_Jet1Tau32_OppositeJetTag_t_b_JetTag_b_mass     ->Write();
  h_JetTau32                                       ->Write();
  h_JetTau32_JetTag_b                              ->Write();
  h_JetTau32_JetTag_mass                           ->Write();
  h_JetTau32_JetTag_b_mass                         ->Write();
  h_JetTau32_OppositeJetTag_t_b                    ->Write();
  h_JetTau32_OppositeJetTag_t_b_JetTag_b           ->Write();
  h_JetTau32_OppositeJetTag_t_b_JetTag_b_mass      ->Write();


  h_2ttag_2btag_Jet0PuppiSDsubjet0pt               ->Write();
  h_2ttag_2btag_Jet0PuppiSDsubjet0mass             ->Write();
  h_2ttag_2btag_Jet0PuppiSDsubjet0tau1             ->Write();
  h_2ttag_2btag_Jet0PuppiSDsubjet0tau2             ->Write();
  h_2ttag_2btag_Jet0PuppiSDsubjet0tau3             ->Write();
  h_2ttag_2btag_Jet0PuppiSDsubjet0bdisc            ->Write();
  h_2ttag_2btag_Jet0PuppiSDsubjet1pt               ->Write();
  h_2ttag_2btag_Jet0PuppiSDsubjet1mass             ->Write();
  h_2ttag_2btag_Jet0PuppiSDsubjet1tau1             ->Write();
  h_2ttag_2btag_Jet0PuppiSDsubjet1tau2             ->Write();
  h_2ttag_2btag_Jet0PuppiSDsubjet1tau3             ->Write();
  h_2ttag_2btag_Jet0PuppiSDsubjet1bdisc            ->Write();

  h_2ttag_1btag_Jet0PuppiSDsubjet0pt               ->Write();
  h_2ttag_1btag_Jet0PuppiSDsubjet0mass             ->Write();
  h_2ttag_1btag_Jet0PuppiSDsubjet0tau1             ->Write();
  h_2ttag_1btag_Jet0PuppiSDsubjet0tau2             ->Write();
  h_2ttag_1btag_Jet0PuppiSDsubjet0tau3             ->Write();
  h_2ttag_1btag_Jet0PuppiSDsubjet0bdisc            ->Write();
  h_2ttag_1btag_Jet0PuppiSDsubjet1pt               ->Write();
  h_2ttag_1btag_Jet0PuppiSDsubjet1mass             ->Write();
  h_2ttag_1btag_Jet0PuppiSDsubjet1tau1             ->Write();
  h_2ttag_1btag_Jet0PuppiSDsubjet1tau2             ->Write();
  h_2ttag_1btag_Jet0PuppiSDsubjet1tau3             ->Write();
  h_2ttag_1btag_Jet0PuppiSDsubjet1bdisc            ->Write();

  h_2ttag_0btag_Jet0PuppiSDsubjet0pt               ->Write();
  h_2ttag_0btag_Jet0PuppiSDsubjet0mass             ->Write();
  h_2ttag_0btag_Jet0PuppiSDsubjet0tau1             ->Write();
  h_2ttag_0btag_Jet0PuppiSDsubjet0tau2             ->Write();
  h_2ttag_0btag_Jet0PuppiSDsubjet0tau3             ->Write();
  h_2ttag_0btag_Jet0PuppiSDsubjet0bdisc            ->Write();
  h_2ttag_0btag_Jet0PuppiSDsubjet1pt               ->Write();
  h_2ttag_0btag_Jet0PuppiSDsubjet1mass             ->Write();
  h_2ttag_0btag_Jet0PuppiSDsubjet1tau1             ->Write();
  h_2ttag_0btag_Jet0PuppiSDsubjet1tau2             ->Write();
  h_2ttag_0btag_Jet0PuppiSDsubjet1tau3             ->Write();
  h_2ttag_0btag_Jet0PuppiSDsubjet1bdisc            ->Write();


  if (!isData){
    h_Jet0SDmass_matchedTop              ->Write();
    h_Jet0SDmass_matchedTop_topDist      ->Write();
    h_Jet0SDmass_outside                 ->Write();
    h_Jet0SDmass_bq                      ->Write();
    h_Jet0SDmass_qq                      ->Write();

    h_Jet0SDmass_all                     ->Write();
    h_Jet0SDmass_in_b                    ->Write();
    h_Jet0SDmass_in_q                    ->Write();
    h_Jet0SDmass_in_qq                   ->Write();
    h_Jet0SDmass_in_qb                   ->Write();
    h_Jet0SDmass_in_qqb                  ->Write();
    h_Jet0SDmass_unmatched               ->Write();

    h_Jet0Tau32_all                      ->Write();
    h_Jet0Tau32_in_b                     ->Write();
    h_Jet0Tau32_in_q                     ->Write();
    h_Jet0Tau32_in_qq                    ->Write();
    h_Jet0Tau32_in_qb                    ->Write();
    h_Jet0Tau32_in_qqb                   ->Write();
    h_Jet0Tau32_unmatched                ->Write();

    h_Jet0SDmass_Pt600_all               ->Write();
    h_Jet0SDmass_Pt600_in_b              ->Write();
    h_Jet0SDmass_Pt600_in_q              ->Write();
    h_Jet0SDmass_Pt600_in_qq             ->Write();
    h_Jet0SDmass_Pt600_in_qb             ->Write();
    h_Jet0SDmass_Pt600_in_qqb            ->Write();
    h_Jet0SDmass_Pt600_unmatched         ->Write();

    h_Jet0Tau32_Pt600_all                ->Write();
    h_Jet0Tau32_Pt600_in_b               ->Write();
    h_Jet0Tau32_Pt600_in_q               ->Write();
    h_Jet0Tau32_Pt600_in_qq              ->Write();
    h_Jet0Tau32_Pt600_in_qb              ->Write();
    h_Jet0Tau32_Pt600_in_qqb             ->Write();
    h_Jet0Tau32_Pt600_unmatched          ->Write();

    h_Jet0SDmass_BtagM_all               ->Write();
    h_Jet0SDmass_BtagM_in_b              ->Write();
    h_Jet0SDmass_BtagM_in_q              ->Write();
    h_Jet0SDmass_BtagM_in_qq             ->Write();
    h_Jet0SDmass_BtagM_in_qb             ->Write();
    h_Jet0SDmass_BtagM_in_qqb            ->Write();
    h_Jet0SDmass_BtagM_unmatched         ->Write();

    h_Jet0SDmass_BtagT_all               ->Write();
    h_Jet0SDmass_BtagT_in_b              ->Write();
    h_Jet0SDmass_BtagT_in_q              ->Write();
    h_Jet0SDmass_BtagT_in_qq             ->Write();
    h_Jet0SDmass_BtagT_in_qb             ->Write();
    h_Jet0SDmass_BtagT_in_qqb            ->Write();
    h_Jet0SDmass_BtagT_unmatched         ->Write();

    h_Jet0Tau32_BtagM_all                ->Write();
    h_Jet0Tau32_BtagM_in_b               ->Write();
    h_Jet0Tau32_BtagM_in_q               ->Write();
    h_Jet0Tau32_BtagM_in_qq              ->Write();
    h_Jet0Tau32_BtagM_in_qb              ->Write();
    h_Jet0Tau32_BtagM_in_qqb             ->Write();
    h_Jet0Tau32_BtagM_unmatched          ->Write();

    h_Jet0Tau32_MassTag_all              ->Write(); 
    h_Jet0Tau32_MassTag_in_b             ->Write(); 
    h_Jet0Tau32_MassTag_in_q             ->Write(); 
    h_Jet0Tau32_MassTag_in_qq            ->Write(); 
    h_Jet0Tau32_MassTag_in_qb            ->Write(); 
    h_Jet0Tau32_MassTag_in_qqb           ->Write(); 
    h_Jet0Tau32_MassTag_unmatched        ->Write(); 

    h_Jet0Tau32_BtagM_MassTag_all        ->Write(); 
    h_Jet0Tau32_BtagM_MassTag_in_b       ->Write(); 
    h_Jet0Tau32_BtagM_MassTag_in_q       ->Write(); 
    h_Jet0Tau32_BtagM_MassTag_in_qq      ->Write(); 
    h_Jet0Tau32_BtagM_MassTag_in_qb      ->Write(); 
    h_Jet0Tau32_BtagM_MassTag_in_qqb     ->Write(); 
    h_Jet0Tau32_BtagM_MassTag_unmatched  ->Write(); 

    h_Jet0SDmass_TauTag_all              ->Write();
    h_Jet0SDmass_TauTag_in_b             ->Write();
    h_Jet0SDmass_TauTag_in_q             ->Write();
    h_Jet0SDmass_TauTag_in_qq            ->Write();
    h_Jet0SDmass_TauTag_in_qb            ->Write();
    h_Jet0SDmass_TauTag_in_qqb           ->Write();
    h_Jet0SDmass_TauTag_unmatched        ->Write();

    h_Jet0SDmass_AntiTauTag_all          ->Write();
    h_Jet0SDmass_AntiTauTag_in_b         ->Write();
    h_Jet0SDmass_AntiTauTag_in_q         ->Write();
    h_Jet0SDmass_AntiTauTag_in_qq        ->Write();
    h_Jet0SDmass_AntiTauTag_in_qb        ->Write();
    h_Jet0SDmass_AntiTauTag_in_qqb       ->Write();
    h_Jet0SDmass_AntiTauTag_unmatched    ->Write();

    h_Jet0SDmass_BtagM_TauTag_all        ->Write();
    h_Jet0SDmass_BtagM_TauTag_in_b       ->Write();
    h_Jet0SDmass_BtagM_TauTag_in_q       ->Write();
    h_Jet0SDmass_BtagM_TauTag_in_qq      ->Write();
    h_Jet0SDmass_BtagM_TauTag_in_qb      ->Write();
    h_Jet0SDmass_BtagM_TauTag_in_qqb     ->Write();
    h_Jet0SDmass_BtagM_TauTag_unmatched  ->Write();
  }

  cout<< h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_inclusive           ->Integral() <<endl;
  cout<< h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_0btag               ->Integral() <<endl;
  cout<< h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_1btag               ->Integral() <<endl;
  cout<< h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_2btag               ->Integral() <<endl;
  cout<< h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_inclusive           ->Integral() <<endl;
  cout<< h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_0btag               ->Integral() <<endl;
  cout<< h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_1btag               ->Integral() <<endl;
  cout<< h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_2btag               ->Integral() <<endl;
  cout<< h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_inclusive           ->Integral() <<endl;
  cout<< h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_0btag               ->Integral() <<endl;
  cout<< h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_1btag               ->Integral() <<endl;
  cout<< h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_2btag               ->Integral() <<endl;
  cout<< h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_inclusive  ->Integral() <<endl;
  cout<< h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_0btag      ->Integral() <<endl;
  cout<< h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_1btag      ->Integral() <<endl;
  cout<< h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_2btag      ->Integral() <<endl;
  cout<< h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_inclusive  ->Integral() <<endl;
  cout<< h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_0btag      ->Integral() <<endl;
  cout<< h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_1btag      ->Integral() <<endl;
  cout<< h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_2btag      ->Integral() <<endl;
  cout<< h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_inclusive  ->Integral() <<endl;
  cout<< h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_0btag      ->Integral() <<endl;
  cout<< h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_1btag      ->Integral() <<endl;
  cout<< h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_2btag      ->Integral() <<endl;

  h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_inclusive           ->Write();
  h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_0btag               ->Write();
  h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_1btag               ->Write();
  h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_2btag               ->Write();
  h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_inclusive           ->Write();
  h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_0btag               ->Write();
  h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_1btag               ->Write();
  h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_2btag               ->Write();
  h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_inclusive           ->Write();
  h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_0btag               ->Write();
  h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_1btag               ->Write();
  h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_2btag               ->Write();
  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_inclusive  ->Write();
  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_0btag      ->Write();
  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_1btag      ->Write();
  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_2btag      ->Write();
  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_inclusive  ->Write();
  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_0btag      ->Write();
  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_1btag      ->Write();
  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_2btag      ->Write();
  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_inclusive  ->Write();
  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_0btag      ->Write();
  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_1btag      ->Write();
  h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_2btag      ->Write();

  Out->Close();




}
 
