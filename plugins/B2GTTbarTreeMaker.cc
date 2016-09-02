// -*- C++ -*-
//
// Package:    Analysis/B2GTTbarTreeMaker
// Class:      B2GTTbarTreeMaker
// 
/**\class B2GTTbarTreeMaker B2GTTbarTreeMaker.cc Analysis/B2GTTbarTreeMaker/plugins/B2GTTbarTreeMaker.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  James Dolen
//         Created:  Sat, 30 Apr 2016 17:40:42 GMT
//
//

// system include files
#include <memory>
#include <iostream>    
#include <algorithm>   

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// DataFormats
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"

// TFileService
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

// Gen particle
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

// JEC
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

// JER
#include "JetMETCorrections/Modules/interface/JetResolution.h"

// Trigger
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

// Utilities
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"

// root
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TLorentzVector.h"

//
// class declaration
//

class B2GTTbarTreeMaker : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit B2GTTbarTreeMaker(const edm::ParameterSet&);
      ~B2GTTbarTreeMaker();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
      edm::EDGetTokenT<pat::JetCollection> ak4jetToken_;
      edm::EDGetTokenT<pat::JetCollection> ak8jetToken_;
      edm::EDGetTokenT<pat::JetCollection> puppijetToken_;
      edm::EDGetTokenT<pat::JetCollection> ak8CHSSoftDropSubjetsToken_;
      edm::EDGetTokenT<reco::GenJetCollection> ak4genjetToken_;
      edm::EDGetTokenT<reco::GenJetCollection> ak8genjetToken_;
      edm::EDGetTokenT<edm::View<reco::GenParticle> > prunedGenToken_;
      edm::EDGetTokenT<double> rhoToken_;
      edm::EDGetTokenT<std::vector<reco::Vertex> > vtxToken_;
      edm::EDGetTokenT<edm::TriggerResults> triggerResultsMETFilterToken_;
      edm::EDGetTokenT<edm::TriggerResults> triggerResultsHLTToken_;
      edm::EDGetTokenT<bool> badMuonFilterToken_;
      edm::EDGetTokenT<bool> badChargedCandidateFilterToken_;
      edm::EDGetTokenT<pat::MuonCollection> muonToken_;
      edm::EDGetTokenT<pat::ElectronCollection> electronToken_;
      edm::EDGetTokenT<pat::METCollection> metToken_;

      
      bool useToolbox_;
      bool verbose_;
      bool verboseGen_;
      bool runGenLoop_;
      std::vector<std::string>  jecPayloadsAK4chs_;
      std::vector<std::string>  jecPayloadsAK8chs_;
      std::vector<std::string>  jecPayloadsAK4pup_;
      std::vector<std::string>  jecPayloadsAK8pup_;
      boost::shared_ptr<FactorizedJetCorrector> JetCorrectorAK4chs;
      boost::shared_ptr<FactorizedJetCorrector> JetCorrectorAK8chs;
      boost::shared_ptr<FactorizedJetCorrector> JetCorrectorAK4pup;
      boost::shared_ptr<FactorizedJetCorrector> JetCorrectorAK8pup;
      boost::shared_ptr<JetCorrectionUncertainty> JetCorrUncertAK4chs;
      boost::shared_ptr<JetCorrectionUncertainty> JetCorrUncertAK8chs;
      boost::shared_ptr<JetCorrectionUncertainty> JetCorrUncertAK4pup;
      boost::shared_ptr<JetCorrectionUncertainty> JetCorrUncertAK8pup;
      
      std::string jerSFtext_;

      TH1D * h_ak8chs_softDropMass   ;
      TH1D * h_ak8puppi_softDropMass ;

      //
      //       d8888 888 888        888    888               888     88888888888                           
      //      d88888 888 888        888    888               888         888                               
      //     d88P888 888 888        888    888               888         888                               
      //    d88P 888 888 888        8888888888  8888b.   .d88888         888     888d888  .d88b.   .d88b.  
      //   d88P  888 888 888        888    888     "88b d88" 888         888     888P"   d8P  Y8b d8P  Y8b 
      //  d88P   888 888 888 888888 888    888 .d888888 888  888         888     888     88888888 88888888 
      // d8888888888 888 888        888    888 888  888 Y88b 888         888     888     Y8b.     Y8b.     
      //d88P     888 888 888        888    888 "Y888888  "Y88888         888     888      "Y8888   "Y8888  
      //                                                                                                   
                                                                                                                                                                                                                                                                                              
      TTree *TreeAllHad;
      Int_t   PassMETFilters                         ;
      Float_t Jet0PtRaw                              ;
      Float_t Jet0EtaRaw                             ;
      Float_t Jet0PhiRaw                             ;
      Float_t Jet0MassRaw                            ;
      Float_t Jet0P                                  ;
      Float_t Jet0Pt                                 ;
      Float_t Jet0Eta                                ;
      Float_t Jet0Phi                                ;
      Float_t Jet0Rap                                ;
      Float_t Jet0Energy                             ;
      Float_t Jet0Mass                               ;
      Float_t Jet0Area                               ;
      Float_t Jet0MassSoftDrop                       ;
      Float_t Jet0MassSDsumSubjetRaw                 ;
      Float_t Jet0MassSDsumSubjetCorrL23             ;
      Float_t Jet0MassSDsumSubjetCorrL23Up           ;
      Float_t Jet0MassSDsumSubjetCorrL23Dn           ;
      Float_t Jet0MassSDsumSubjetCorrL123            ;
      Float_t Jet0MassSDsumSubjetCorrL123Up          ;
      Float_t Jet0MassSDsumSubjetCorrL123Dn          ;
      Float_t Jet0MassSDsumSubjetCorrSmear           ;
      Float_t Jet0MassSDsumSubjetCorrSmearUp         ;
      Float_t Jet0MassSDsumSubjetCorrSmearDn         ;
      Float_t Jet0MassPruned                         ;
      Float_t Jet0Tau1                               ;
      Float_t Jet0Tau2                               ;
      Float_t Jet0Tau3                               ;
      Float_t Jet0Tau32                              ;
      Float_t Jet0Tau21                              ;
      Float_t Jet0SDsubjet0bdisc                     ;
      Float_t Jet0SDsubjet1bdisc                     ;
      Float_t Jet0SDmaxbdisc                         ;
      Float_t Jet0SDmaxbdiscflavHadron               ;
      Float_t Jet0SDmaxbdiscflavParton               ;
      Float_t Jet0SDsubjet0pt                        ;
      Float_t Jet0SDsubjet0mass                      ;
      Float_t Jet0SDsubjet0eta                       ;
      Float_t Jet0SDsubjet0phi                       ;
      Float_t Jet0SDsubjet0area                      ;
      Float_t Jet0SDsubjet0flavHadron                ;
      Float_t Jet0SDsubjet0flavParton                ;
      Float_t Jet0SDsubjet0tau1                      ;
      Float_t Jet0SDsubjet0tau2                      ;
      Float_t Jet0SDsubjet0tau3                      ;
      Float_t Jet0SDsubjet1pt                        ;
      Float_t Jet0SDsubjet1mass                      ;
      Float_t Jet0SDsubjet1eta                       ;
      Float_t Jet0SDsubjet1phi                       ;
      Float_t Jet0SDsubjet1area                      ;
      Float_t Jet0SDsubjet1flavHadron                ;
      Float_t Jet0SDsubjet1flavParton                ;
      Float_t Jet0SDsubjet1tau1                      ;
      Float_t Jet0SDsubjet1tau2                      ;
      Float_t Jet0SDsubjet1tau3                      ;
      Float_t Jet0PuppiPt                            ;
      Float_t Jet0PuppiEta                           ;
      Float_t Jet0PuppiPhi                           ;
      Float_t Jet0PuppiMass                          ;
      Float_t Jet0PuppiMassSoftDrop                  ;
      Float_t Jet0PuppiMassSDsumSubjetRaw            ;
      Float_t Jet0PuppiMassSDsumSubjetCorr           ;
      Float_t Jet0PuppiMassSDsumSubjetCorrUp         ;
      Float_t Jet0PuppiMassSDsumSubjetCorrDn         ;
      Float_t Jet0PuppiMassSDsumSubjetCorrSmear      ;
      Float_t Jet0PuppiMassSDsumSubjetCorrSmearUp    ;
      Float_t Jet0PuppiMassSDsumSubjetCorrSmearDn    ;
      Float_t Jet0PuppiTau1                          ;
      Float_t Jet0PuppiTau2                          ;
      Float_t Jet0PuppiTau3                          ;
      Float_t Jet0PuppiTau32                         ;
      Float_t Jet0PuppiTau21                         ;
      Float_t Jet0PuppiSDsubjet0bdisc                ;
      Float_t Jet0PuppiSDsubjet1bdisc                ;
      Float_t Jet0PuppiSDmaxbdisc                    ;
      Float_t Jet0PuppiSDmaxbdiscflavHadron          ;
      Float_t Jet0PuppiSDmaxbdiscflavParton          ;
      Float_t Jet0PuppiSDsubjet0pt                   ;
      Float_t Jet0PuppiSDsubjet0mass                 ;
      Float_t Jet0PuppiSDsubjet0eta                  ;
      Float_t Jet0PuppiSDsubjet0phi                  ;
      Float_t Jet0PuppiSDsubjet0area                 ;
      Float_t Jet0PuppiSDsubjet0flavHadron           ;
      Float_t Jet0PuppiSDsubjet0flavParton           ;
      Float_t Jet0PuppiSDsubjet0tau1                 ;
      Float_t Jet0PuppiSDsubjet0tau2                 ;
      Float_t Jet0PuppiSDsubjet0tau3                 ;
      Float_t Jet0PuppiSDsubjet1pt                   ;
      Float_t Jet0PuppiSDsubjet1mass                 ;
      Float_t Jet0PuppiSDsubjet1eta                  ;
      Float_t Jet0PuppiSDsubjet1phi                  ;
      Float_t Jet0PuppiSDsubjet1area                 ;
      Float_t Jet0PuppiSDsubjet1flavHadron           ;
      Float_t Jet0PuppiSDsubjet1flavParton           ;
      Float_t Jet0PuppiSDsubjet1tau1                 ;
      Float_t Jet0PuppiSDsubjet1tau2                 ;
      Float_t Jet0PuppiSDsubjet1tau3                 ;
      Float_t Jet0CHF                                ;
      Float_t Jet0NHF                                ;
      Float_t Jet0CM                                 ;
      Float_t Jet0NM                                 ;
      Float_t Jet0NEF                                ;
      Float_t Jet0CEF                                ;
      Float_t Jet0MF                                 ;
      Float_t Jet0Mult                               ;
      Float_t Jet0MassCorrFactor                     ;
      Float_t Jet0MassCorrFactorUp                   ;
      Float_t Jet0MassCorrFactorDn                   ;
      Float_t Jet0CorrFactor                         ;
      Float_t Jet0CorrFactorUp                       ;
      Float_t Jet0CorrFactorDn                       ;
      Float_t Jet0PtSmearFactor                      ;
      Float_t Jet0PtSmearFactorUp                    ;
      Float_t Jet0PtSmearFactorDn                    ;
      Float_t Jet0PuppiMassCorrFactor                ;
      Float_t Jet0PuppiMassCorrFactorUp              ;
      Float_t Jet0PuppiMassCorrFactorDn              ;
      Float_t Jet0PuppiCorrFactor                    ;
      Float_t Jet0PuppiCorrFactorUp                  ;
      Float_t Jet0PuppiCorrFactorDn                  ;
      Float_t Jet0PuppiPtSmearFactor                 ;
      Float_t Jet0PuppiPtSmearFactorUp               ;
      Float_t Jet0PuppiPtSmearFactorDn               ;
      Float_t Jet0EtaScaleFactor                     ;
      Float_t Jet0PhiScaleFactor                     ;
      Float_t Jet0MatchedGenJetDR                    ;
      Float_t Jet0MatchedGenJetPt                    ;
      Float_t Jet0MatchedGenJetMass                  ;

      Int_t   Jet0GenMatched_TopHadronic             ;
      Float_t Jet0GenMatched_TopPt                   ;
      Float_t Jet0GenMatched_TopEta                  ;
      Float_t Jet0GenMatched_TopPhi                  ;
      Float_t Jet0GenMatched_TopMass                 ;
      Float_t Jet0GenMatched_bPt                     ;
      Float_t Jet0GenMatched_WPt                     ;
      Float_t Jet0GenMatched_Wd1Pt                   ;
      Float_t Jet0GenMatched_Wd2Pt                   ;
      Float_t Jet0GenMatched_Wd1ID                   ;
      Float_t Jet0GenMatched_Wd2ID                   ;
      Float_t Jet0GenMatched_MaxDeltaRPartonTop      ;
      Float_t Jet0GenMatched_MaxDeltaRWPartonTop     ;
      Float_t Jet0GenMatched_MaxDeltaRWPartonW       ;
      Float_t Jet0GenMatched_DeltaR_t_b              ;
      Float_t Jet0GenMatched_DeltaR_t_W              ;
      Float_t Jet0GenMatched_DeltaR_t_Wd1            ;
      Float_t Jet0GenMatched_DeltaR_t_Wd2            ;
      Float_t Jet0GenMatched_DeltaR_W_b1             ;
      Float_t Jet0GenMatched_DeltaR_W_Wd1            ;
      Float_t Jet0GenMatched_DeltaR_W_Wd2            ;
      Float_t Jet0GenMatched_DeltaR_Wd1_Wd2          ;
      Float_t Jet0GenMatched_DeltaR_Wd1_b            ;
      Float_t Jet0GenMatched_DeltaR_Wd2_b            ;
      Float_t Jet0GenMatched_DeltaR_jet_t            ;
      Float_t Jet0GenMatched_DeltaR_jet_W            ;
      Float_t Jet0GenMatched_DeltaR_jet_b            ;
      Float_t Jet0GenMatched_DeltaR_jet_Wd1          ;
      Float_t Jet0GenMatched_DeltaR_jet_Wd2          ;
      Float_t Jet0GenMatched_DeltaR_pup0_b           ;
      Float_t Jet0GenMatched_DeltaR_pup0_Wd1         ;
      Float_t Jet0GenMatched_DeltaR_pup0_Wd2         ;
      Float_t Jet0GenMatched_DeltaR_pup1_b           ;
      Float_t Jet0GenMatched_DeltaR_pup1_Wd1         ;
      Float_t Jet0GenMatched_DeltaR_pup1_Wd2         ;
      Float_t Jet0GenMatched_partonPt                ;
      Float_t Jet0GenMatched_partonEta               ;
      Float_t Jet0GenMatched_partonPhi               ;
      Float_t Jet0GenMatched_partonMass              ;
      Float_t Jet0GenMatched_partonID                ;
      Float_t Jet0GenMatched_DeltaRjetParton         ;

      Float_t Jet1PtRaw                              ;
      Float_t Jet1EtaRaw                             ;
      Float_t Jet1PhiRaw                             ;
      Float_t Jet1MassRaw                            ;
      Float_t Jet1P                                  ;
      Float_t Jet1Pt                                 ;
      Float_t Jet1Eta                                ;
      Float_t Jet1Phi                                ;
      Float_t Jet1Rap                                ;
      Float_t Jet1Energy                             ;
      Float_t Jet1Mass                               ;
      Float_t Jet1Area                               ;
      Float_t Jet1MassSoftDrop                       ;
      Float_t Jet1MassSDsumSubjetRaw                 ;
      Float_t Jet1MassSDsumSubjetCorrL23             ;
      Float_t Jet1MassSDsumSubjetCorrL23Up           ;
      Float_t Jet1MassSDsumSubjetCorrL23Dn           ;
      Float_t Jet1MassSDsumSubjetCorrL123            ;
      Float_t Jet1MassSDsumSubjetCorrL123Up          ;
      Float_t Jet1MassSDsumSubjetCorrL123Dn          ;
      Float_t Jet1MassSDsumSubjetCorrSmear           ;
      Float_t Jet1MassSDsumSubjetCorrSmearUp         ;
      Float_t Jet1MassSDsumSubjetCorrSmearDn         ;
      Float_t Jet1MassPruned                         ;
      Float_t Jet1Tau1                               ;
      Float_t Jet1Tau2                               ;
      Float_t Jet1Tau3                               ;
      Float_t Jet1Tau32                              ;
      Float_t Jet1Tau21                              ;
      Float_t Jet1SDsubjet0bdisc                           ;
      Float_t Jet1SDsubjet1bdisc                           ;
      Float_t Jet1SDmaxbdisc                         ;
      Float_t Jet1SDmaxbdiscflavHadron               ;
      Float_t Jet1SDmaxbdiscflavParton               ;
      Float_t Jet1SDsubjet0pt                        ;
      Float_t Jet1SDsubjet0eta                       ;
      Float_t Jet1SDsubjet0phi                       ;
      Float_t Jet1SDsubjet0mass                      ;
      Float_t Jet1SDsubjet0area                      ;
      Float_t Jet1SDsubjet0flavHadron                ;
      Float_t Jet1SDsubjet0flavParton                ;
      Float_t Jet1SDsubjet0tau1                      ;
      Float_t Jet1SDsubjet0tau2                      ;
      Float_t Jet1SDsubjet0tau3                      ;
      Float_t Jet1SDsubjet1pt                        ;
      Float_t Jet1SDsubjet1eta                       ;
      Float_t Jet1SDsubjet1phi                       ;
      Float_t Jet1SDsubjet1mass                      ;
      Float_t Jet1SDsubjet1area                      ;
      Float_t Jet1SDsubjet1flavHadron                ;
      Float_t Jet1SDsubjet1flavParton                ;
      Float_t Jet1SDsubjet1tau1                      ;
      Float_t Jet1SDsubjet1tau2                      ;
      Float_t Jet1SDsubjet1tau3                      ;
      Float_t Jet1PuppiPt                            ;
      Float_t Jet1PuppiEta                           ;
      Float_t Jet1PuppiPhi                           ;
      Float_t Jet1PuppiMass                          ;
      Float_t Jet1PuppiMassSoftDrop                  ;
      Float_t Jet1PuppiMassSDsumSubjetRaw            ;
      Float_t Jet1PuppiMassSDsumSubjetCorr           ;
      Float_t Jet1PuppiMassSDsumSubjetCorrUp         ;
      Float_t Jet1PuppiMassSDsumSubjetCorrDn         ;
      Float_t Jet1PuppiMassSDsumSubjetCorrSmear      ;
      Float_t Jet1PuppiMassSDsumSubjetCorrSmearUp    ;
      Float_t Jet1PuppiMassSDsumSubjetCorrSmearDn    ;
      Float_t Jet1PuppiTau1                          ;
      Float_t Jet1PuppiTau2                          ;
      Float_t Jet1PuppiTau3                          ;
      Float_t Jet1PuppiTau32                         ;
      Float_t Jet1PuppiTau21                         ;
      Float_t Jet1PuppiSDsubjet0bdisc                      ;
      Float_t Jet1PuppiSDsubjet1bdisc                      ;
      Float_t Jet1PuppiSDmaxbdisc                    ;
      Float_t Jet1PuppiSDmaxbdiscflavHadron          ;
      Float_t Jet1PuppiSDmaxbdiscflavParton          ;
      Float_t Jet1PuppiSDsubjet0pt                   ;
      Float_t Jet1PuppiSDsubjet0eta                  ;
      Float_t Jet1PuppiSDsubjet0phi                  ;
      Float_t Jet1PuppiSDsubjet0mass                 ;
      Float_t Jet1PuppiSDsubjet0area                 ;
      Float_t Jet1PuppiSDsubjet0flavHadron           ;
      Float_t Jet1PuppiSDsubjet0flavParton           ;
      Float_t Jet1PuppiSDsubjet0tau1                 ;
      Float_t Jet1PuppiSDsubjet0tau2                 ;
      Float_t Jet1PuppiSDsubjet0tau3                 ;
      Float_t Jet1PuppiSDsubjet1pt                   ;
      Float_t Jet1PuppiSDsubjet1eta                  ;
      Float_t Jet1PuppiSDsubjet1phi                  ;
      Float_t Jet1PuppiSDsubjet1mass                 ;
      Float_t Jet1PuppiSDsubjet1area                 ;
      Float_t Jet1PuppiSDsubjet1flavHadron           ;
      Float_t Jet1PuppiSDsubjet1flavParton           ;
      Float_t Jet1PuppiSDsubjet1tau1                 ;
      Float_t Jet1PuppiSDsubjet1tau2                 ;
      Float_t Jet1PuppiSDsubjet1tau3                 ;
      Float_t Jet1CHF                                ;
      Float_t Jet1NHF                                ;
      Float_t Jet1CM                                 ;
      Float_t Jet1NM                                 ;
      Float_t Jet1NEF                                ;
      Float_t Jet1CEF                                ;
      Float_t Jet1MF                                 ;
      Float_t Jet1Mult                               ;
      Float_t Jet1MassCorrFactor                     ;
      Float_t Jet1MassCorrFactorUp                   ;
      Float_t Jet1MassCorrFactorDn                   ;
      Float_t Jet1CorrFactor                         ;
      Float_t Jet1CorrFactorUp                       ;
      Float_t Jet1CorrFactorDn                       ;
      Float_t Jet1PtSmearFactor                      ;
      Float_t Jet1PtSmearFactorUp                    ;
      Float_t Jet1PtSmearFactorDn                    ;
      Float_t Jet1PuppiMassCorrFactor                ;
      Float_t Jet1PuppiMassCorrFactorUp              ;
      Float_t Jet1PuppiMassCorrFactorDn              ;
      Float_t Jet1PuppiCorrFactor                    ;
      Float_t Jet1PuppiCorrFactorUp                  ;
      Float_t Jet1PuppiCorrFactorDn                  ;
      Float_t Jet1PuppiPtSmearFactor                 ;
      Float_t Jet1PuppiPtSmearFactorUp               ;
      Float_t Jet1PuppiPtSmearFactorDn               ;
      Float_t Jet1EtaScaleFactor                     ;
      Float_t Jet1PhiScaleFactor                     ;
      Float_t Jet1MatchedGenJetDR                    ;
      Float_t Jet1MatchedGenJetPt                    ;
      Float_t Jet1MatchedGenJetMass                  ;

      Int_t   Jet1GenMatched_TopHadronic             ;
      Float_t Jet1GenMatched_TopPt                   ;
      Float_t Jet1GenMatched_TopEta                  ;
      Float_t Jet1GenMatched_TopPhi                  ;
      Float_t Jet1GenMatched_TopMass                 ;
      Float_t Jet1GenMatched_bPt                     ;
      Float_t Jet1GenMatched_WPt                     ;
      Float_t Jet1GenMatched_Wd1Pt                   ;
      Float_t Jet1GenMatched_Wd2Pt                   ;
      Float_t Jet1GenMatched_Wd1ID                   ;
      Float_t Jet1GenMatched_Wd2ID                   ;
      Float_t Jet1GenMatched_MaxDeltaRPartonTop      ;
      Float_t Jet1GenMatched_MaxDeltaRWPartonTop     ;
      Float_t Jet1GenMatched_MaxDeltaRWPartonW       ;
      Float_t Jet1GenMatched_DeltaR_t_b              ;
      Float_t Jet1GenMatched_DeltaR_t_W              ;
      Float_t Jet1GenMatched_DeltaR_t_Wd1            ;
      Float_t Jet1GenMatched_DeltaR_t_Wd2            ;
      Float_t Jet1GenMatched_DeltaR_W_b1             ;
      Float_t Jet1GenMatched_DeltaR_W_Wd1            ;
      Float_t Jet1GenMatched_DeltaR_W_Wd2            ;
      Float_t Jet1GenMatched_DeltaR_Wd1_Wd2          ;
      Float_t Jet1GenMatched_DeltaR_Wd1_b            ;
      Float_t Jet1GenMatched_DeltaR_Wd2_b            ;
      Float_t Jet1GenMatched_DeltaR_jet_t            ;
      Float_t Jet1GenMatched_DeltaR_jet_W            ;
      Float_t Jet1GenMatched_DeltaR_jet_b            ;
      Float_t Jet1GenMatched_DeltaR_jet_Wd1          ;
      Float_t Jet1GenMatched_DeltaR_jet_Wd2          ;
      Float_t Jet1GenMatched_DeltaR_pup0_b           ;
      Float_t Jet1GenMatched_DeltaR_pup0_Wd1         ;
      Float_t Jet1GenMatched_DeltaR_pup0_Wd2         ;
      Float_t Jet1GenMatched_DeltaR_pup1_b           ;
      Float_t Jet1GenMatched_DeltaR_pup1_Wd1         ;
      Float_t Jet1GenMatched_DeltaR_pup1_Wd2         ;      
      Float_t Jet1GenMatched_partonPt                ;
      Float_t Jet1GenMatched_partonEta               ;
      Float_t Jet1GenMatched_partonPhi               ;
      Float_t Jet1GenMatched_partonMass              ;
      Float_t Jet1GenMatched_partonID                ;
      Float_t Jet1GenMatched_DeltaRjetParton         ;

      Float_t AllHadMETpx                            ;           
      Float_t AllHadMETpy                            ;           
      Float_t AllHadMETpt                            ;           
      Float_t AllHadMETphi                           ;           
      Float_t AllHadMETsumET                         ;           
      Float_t AllHadNvtx                             ;           
      Float_t AllHadRho                              ;           
      Float_t AllHadEventWeight                      ;           
      Float_t DijetMass                              ;           
      Float_t DijetDeltaR                            ;           
      Float_t DijetDeltaPhi                          ;           
      Float_t DijetDeltaRap                          ;           
      Float_t DiGenJetMass                           ;           
      Float_t GenTTmass                              ;           
      Float_t HT                                     ;           
      Float_t HT_CorrDn                              ;           
      Float_t HT_CorrUp                              ;           
      Float_t HT_PtSmearUp                           ;           
      Float_t HT_PtSmearDn                           ;           
      Float_t Q2weight_CorrDn                        ;           
      Float_t Q2weight_CorrUp                        ;           
      Float_t NNPDF3weight_CorrDn                    ;           
      Float_t NNPDF3weight_CorrUp                    ;           
      Float_t AllHadRunNum                           ;           
      Float_t AllHadLumiBlock                        ;           
      Float_t AllHadEventNum                         ;    



      // 
      //  .d8888b.                         d8b        888                        888        88888888888                           
      // d88P  Y88b                        Y8P        888                        888            888                               
      // Y88b.                                        888                        888            888                               
      //  "Y888b.    .d88b.  88888b.d88b.  888        888       .d88b.  88888b.  888888         888     888d888  .d88b.   .d88b.  
      //     "Y88b. d8P  Y8b 888 "888 "88b 888        888      d8P  Y8b 888 "88b 888            888     888P"   d8P  Y8b d8P  Y8b 
      //       "888 88888888 888  888  888 888 888888 888      88888888 888  888 888            888     888     88888888 88888888 
      // Y88b  d88P Y8b.     888  888  888 888        888      Y8b.     888 d88P Y88b.          888     888     Y8b.     Y8b.     
      //  "Y8888P"   "Y8888  888  888  888 888        88888888  "Y8888  88888P"   "Y888         888     888      "Y8888   "Y8888  
      //                                                                888                                                       
      //                                                                888                                                       
      //                                                                888       
         
      TTree *TreeSemiLept;

      Float_t JetPtRaw                               ;      
      Float_t JetEtaRaw                              ;
      Float_t JetPhiRaw                              ;
      Float_t JetMassRaw                             ;
      Float_t JetP                                   ;
      Float_t JetPt                                  ;
      Float_t JetEta                                 ;
      Float_t JetPhi                                 ;
      Float_t JetRap                                 ;
      Float_t JetEnergy                              ;
      Float_t JetMass                                ;
      Float_t JetArea                                ;
      Float_t JetMassSoftDrop                        ;
      Float_t JetMassSDsumSubjetRaw                  ;
      Float_t JetMassSDsumSubjetCorrL23              ;
      Float_t JetMassSDsumSubjetCorrL23Up            ;
      Float_t JetMassSDsumSubjetCorrL23Dn            ;
      Float_t JetMassSDsumSubjetCorrL123             ;
      Float_t JetMassSDsumSubjetCorrL123Up           ;
      Float_t JetMassSDsumSubjetCorrL123Dn           ;
      Float_t JetMassSDsumSubjetCorrSmear            ;
      Float_t JetMassSDsumSubjetCorrSmearUp          ;
      Float_t JetMassSDsumSubjetCorrSmearDn          ;
      Float_t JetMassPruned                          ;
      Float_t JetTau1                                ;
      Float_t JetTau2                                ;
      Float_t JetTau3                                ;
      Float_t JetTau32                               ;
      Float_t JetTau21                               ;
      Float_t JetSDsubjet0bdisc                      ;
      Float_t JetSDsubjet1bdisc                      ;
      Float_t JetSDmaxbdisc                          ;
      Float_t JetSDmaxbdiscflavHadron                ;
      Float_t JetSDmaxbdiscflavParton                ;
      Float_t JetSDsubjet0pt                         ;
      Float_t JetSDsubjet0mass                       ;
      Float_t JetSDsubjet0eta                        ;
      Float_t JetSDsubjet0phi                        ;
      Float_t JetSDsubjet0area                       ;
      Float_t JetSDsubjet0flavHadron                 ;
      Float_t JetSDsubjet0flavParton                 ;
      Float_t JetSDsubjet0tau1                       ;
      Float_t JetSDsubjet0tau2                       ;
      Float_t JetSDsubjet0tau3                       ;
      Float_t JetSDsubjet1pt                         ;
      Float_t JetSDsubjet1mass                       ;
      Float_t JetSDsubjet1eta                        ;
      Float_t JetSDsubjet1phi                        ;
      Float_t JetSDsubjet1area                       ;
      Float_t JetSDsubjet1flavHadron                 ;
      Float_t JetSDsubjet1flavParton                 ;
      Float_t JetSDsubjet1tau1                       ;
      Float_t JetSDsubjet1tau2                       ;
      Float_t JetSDsubjet1tau3                       ;
      Float_t JetPuppiPt                             ;
      Float_t JetPuppiEta                            ;
      Float_t JetPuppiPhi                            ;
      Float_t JetPuppiMass                           ;
      Float_t JetPuppiMassSoftDrop                   ;
      Float_t JetPuppiMassSDsumSubjetRaw             ;
      Float_t JetPuppiMassSDsumSubjetCorr            ;
      Float_t JetPuppiMassSDsumSubjetCorrUp          ;
      Float_t JetPuppiMassSDsumSubjetCorrDn          ;
      Float_t JetPuppiMassSDsumSubjetCorrSmear       ;
      Float_t JetPuppiMassSDsumSubjetCorrSmearUp     ;
      Float_t JetPuppiMassSDsumSubjetCorrSmearDn     ;
      Float_t JetPuppiTau1                           ;
      Float_t JetPuppiTau2                           ;
      Float_t JetPuppiTau3                           ;
      Float_t JetPuppiTau32                          ;
      Float_t JetPuppiTau21                          ;
      Float_t JetPuppiSDsubjet0bdisc                 ;
      Float_t JetPuppiSDsubjet1bdisc                 ;
      Float_t JetPuppiSDmaxbdisc                     ;
      Float_t JetPuppiSDmaxbdiscflavHadron           ;
      Float_t JetPuppiSDmaxbdiscflavParton           ;
      Float_t JetPuppiSDsubjet0pt                    ;
      Float_t JetPuppiSDsubjet0mass                  ;
      Float_t JetPuppiSDsubjet0eta                   ;
      Float_t JetPuppiSDsubjet0phi                   ;
      Float_t JetPuppiSDsubjet0area                  ;
      Float_t JetPuppiSDsubjet0flavHadron            ;
      Float_t JetPuppiSDsubjet0flavParton            ;
      Float_t JetPuppiSDsubjet0tau1                  ;
      Float_t JetPuppiSDsubjet0tau2                  ;
      Float_t JetPuppiSDsubjet0tau3                  ;
      Float_t JetPuppiSDsubjet1pt                    ;
      Float_t JetPuppiSDsubjet1mass                  ;
      Float_t JetPuppiSDsubjet1eta                   ;
      Float_t JetPuppiSDsubjet1phi                   ;
      Float_t JetPuppiSDsubjet1area                  ;
      Float_t JetPuppiSDsubjet1flavHadron            ;
      Float_t JetPuppiSDsubjet1flavParton            ;
      Float_t JetPuppiSDsubjet1tau1                  ;
      Float_t JetPuppiSDsubjet1tau2                  ;
      Float_t JetPuppiSDsubjet1tau3                  ;
      Float_t JetCHF                                 ;
      Float_t JetNHF                                 ;
      Float_t JetCM                                  ;
      Float_t JetNM                                  ;
      Float_t JetNEF                                 ;
      Float_t JetCEF                                 ;
      Float_t JetMF                                  ;
      Float_t JetMult                                ;
      Float_t JetMassCorrFactor                      ;
      Float_t JetMassCorrFactorUp                    ;
      Float_t JetMassCorrFactorDn                    ;
      Float_t JetCorrFactor                          ;
      Float_t JetCorrFactorUp                        ;
      Float_t JetCorrFactorDn                        ;
      Float_t JetPtSmearFactor                       ;
      Float_t JetPtSmearFactorUp                     ;
      Float_t JetPtSmearFactorDn                     ;
      Float_t JetPuppiMassCorrFactor                 ;
      Float_t JetPuppiMassCorrFactorUp               ;
      Float_t JetPuppiMassCorrFactorDn               ;
      Float_t JetPuppiCorrFactor                     ;
      Float_t JetPuppiCorrFactorUp                   ;
      Float_t JetPuppiCorrFactorDn                   ;
      Float_t JetPuppiPtSmearFactor                  ;
      Float_t JetPuppiPtSmearFactorUp                ;
      Float_t JetPuppiPtSmearFactorDn                ;
      Float_t JetEtaScaleFactor                      ;
      Float_t JetPhiScaleFactor                      ;
      Float_t JetMatchedGenJetDR                     ;
      Float_t JetMatchedGenJetPt                     ;
      Float_t JetMatchedGenJetMass                   ;
      Int_t   JetGenMatched_TopHadronic              ;
      Float_t JetGenMatched_TopPt                    ;
      Float_t JetGenMatched_TopEta                   ;
      Float_t JetGenMatched_TopPhi                   ;
      Float_t JetGenMatched_TopMass                  ;
      Float_t JetGenMatched_bPt                      ;
      Float_t JetGenMatched_WPt                      ;
      Float_t JetGenMatched_Wd1Pt                    ;
      Float_t JetGenMatched_Wd2Pt                    ;
      Float_t JetGenMatched_Wd1ID                    ;
      Float_t JetGenMatched_Wd2ID                    ;
      Float_t JetGenMatched_MaxDeltaRPartonTop       ;
      Float_t JetGenMatched_MaxDeltaRWPartonTop      ;
      Float_t JetGenMatched_MaxDeltaRWPartonW        ;
      Float_t JetGenMatched_DeltaR_t_b               ;
      Float_t JetGenMatched_DeltaR_t_W               ;
      Float_t JetGenMatched_DeltaR_t_Wd1             ;
      Float_t JetGenMatched_DeltaR_t_Wd2             ;
      Float_t JetGenMatched_DeltaR_W_b1              ;
      Float_t JetGenMatched_DeltaR_W_Wd1             ;
      Float_t JetGenMatched_DeltaR_W_Wd2             ;
      Float_t JetGenMatched_DeltaR_Wd1_Wd2           ;
      Float_t JetGenMatched_DeltaR_Wd1_b             ;
      Float_t JetGenMatched_DeltaR_Wd2_b             ;
      Float_t JetGenMatched_DeltaR_jet_t             ;
      Float_t JetGenMatched_DeltaR_jet_W             ;
      Float_t JetGenMatched_DeltaR_jet_b             ;
      Float_t JetGenMatched_DeltaR_jet_Wd1           ;
      Float_t JetGenMatched_DeltaR_jet_Wd2           ;
      Float_t JetGenMatched_DeltaR_pup0_b            ;
      Float_t JetGenMatched_DeltaR_pup0_Wd1          ;
      Float_t JetGenMatched_DeltaR_pup0_Wd2          ;
      Float_t JetGenMatched_DeltaR_pup1_b            ;
      Float_t JetGenMatched_DeltaR_pup1_Wd1          ;
      Float_t JetGenMatched_DeltaR_pup1_Wd2          ;
      Float_t JetGenMatched_partonPt                 ;
      Float_t JetGenMatched_partonEta                ;
      Float_t JetGenMatched_partonPhi                ;
      Float_t JetGenMatched_partonMass               ;
      Float_t JetGenMatched_partonID                 ;
      Float_t JetGenMatched_DeltaRjetParton          ;
      Float_t SemiLeptMETpx                          ;
      Float_t SemiLeptMETpy                          ;
      Float_t SemiLeptMETpt                          ;
      Float_t SemiLeptMETphi                         ;
      Float_t SemiLeptMETsumET                       ;
      Float_t SemiLeptNvtx                           ;
      Float_t SemiLeptRho                            ;
      Float_t SemiLeptEventWeight                    ;

      Float_t SemiLeptGenTTmass                      ;
      Float_t SemiLeptHT                             ;
      Float_t SemiLeptHT_CorrDn                      ;
      Float_t SemiLeptHT_CorrUp                      ;
      Float_t SemiLeptHT_PtSmearUp                   ;
      Float_t SemiLeptHT_PtSmearDn                   ;
      Float_t SemiLeptQ2weight_CorrDn                ;
      Float_t SemiLeptQ2weight_CorrUp                ;
      Float_t SemiLeptNNPDF3weight_CorrDn            ;
      Float_t SemiLeptNNPDF3weight_CorrUp            ;
      Float_t SemiLeptRunNum                         ;
      Float_t SemiLeptLumiBlock                      ;
      Float_t SemiLeptEventNum                       ;
      Int_t   SemiLeptPassMETFilters                 ;       
        
      Float_t AK4dRminPt                             ;
      Float_t AK4dRminEta                            ;
      Float_t AK4dRminPhi                            ;
      Float_t AK4dRminBdisc                          ;
      Float_t AK4BtagdRminPt                         ;
      Float_t AK4BtagdRminBdisc                      ;
      Int_t   AK4BtaggedLoose                        ;
      Int_t   AK4BtaggedMedium                       ;
      Int_t   AK4BtaggedTight                        ;

      Float_t LeptonPhi                              ;
      Float_t LeptonPt                               ;
      Float_t LeptonEta                              ;
      Float_t LeptonMass                             ;
      Int_t   LeptonIsMu                             ;
      Int_t   MuTight                                ;
      Float_t DeltaRJetLep                           ; 
      Float_t DeltaPhiJetLep                         ; 

};

//
// constructors and destructor
//
B2GTTbarTreeMaker::B2GTTbarTreeMaker(const edm::ParameterSet& iConfig):
    ak4jetToken_(consumes<pat::JetCollection>(edm::InputTag("slimmedJets"))),
    ak8jetToken_(consumes<pat::JetCollection>( iConfig.getParameter<edm::InputTag>("ak8chsInput"))),  //edm::InputTag("slimmedJetsAK8"))),
    //puppijetToken_(consumes<pat::JetCollection>(edm::InputTag("selectedPatJetsAK8PFPuppi"))),
    ak4genjetToken_(consumes<reco::GenJetCollection>(edm::InputTag("slimmedGenJets"))),
    ak8genjetToken_(consumes<reco::GenJetCollection>(edm::InputTag("slimmedGenJetsAK8"))),
    prunedGenToken_(consumes<edm::View<reco::GenParticle> >(edm::InputTag("prunedGenParticles"))),
    rhoToken_(consumes<double>(edm::InputTag("fixedGridRhoFastjetAll"))),
    vtxToken_(consumes<std::vector<reco::Vertex> >(edm::InputTag("offlineSlimmedPrimaryVertices"))),
    triggerResultsMETFilterToken_(consumes<edm::TriggerResults>(edm::InputTag("TriggerResults", "", "RECO"))),  //"PAT"
    triggerResultsHLTToken_(consumes<edm::TriggerResults>(edm::InputTag("TriggerResults", "", "HLT"))),
    badMuonFilterToken_(consumes<bool>(edm::InputTag("BadPFMuonFilter",""))),
    badChargedCandidateFilterToken_(consumes<bool>(edm::InputTag("BadChargedCandidateFilter",""))),
    muonToken_(consumes<pat::MuonCollection>(edm::InputTag("slimmedMuons"))),
    electronToken_(consumes<pat::ElectronCollection>(edm::InputTag("slimmedElectrons"))),
    metToken_(consumes<pat::METCollection>(edm::InputTag("slimmedMETs"))),
    useToolbox_(iConfig.getParameter<bool>  ("useToolbox")),
    verbose_(iConfig.getParameter<bool>  ("verbose")),
    verboseGen_(iConfig.getParameter<bool>  ("verboseGen")),
    runGenLoop_(iConfig.getParameter<bool>  ("runGenLoop")),
    jecPayloadsAK4chs_ (iConfig.getParameter<std::vector<std::string> >  ("jecPayloadsAK4chs")),
    jecPayloadsAK8chs_ (iConfig.getParameter<std::vector<std::string> >  ("jecPayloadsAK8chs")),
    jecPayloadsAK4pup_ (iConfig.getParameter<std::vector<std::string> >  ("jecPayloadsAK4pup")),
    jecPayloadsAK8pup_ (iConfig.getParameter<std::vector<std::string> >  ("jecPayloadsAK8pup")),
    jerSFtext_ (iConfig.getParameter<std::string>  ("jerSFtext"))
{
  std::cout<<"B2GTTbarTreeMaker::B2GTTbarTreeMaker"<<std::endl;

  usesResource("TFileService");
  edm::Service<TFileService> fs;

  h_ak8chs_softDropMass   =  fs->make<TH1D>("h_ak8chs_softDropMass"        ,"",200,0,400);
  h_ak8puppi_softDropMass =  fs->make<TH1D>("h_ak8puppi_softDropMass"      ,"",200,0,400);

  //
  //       d8888 888 888        888    888               888     88888888888                           
  //      d88888 888 888        888    888               888         888                               
  //     d88P888 888 888        888    888               888         888                               
  //    d88P 888 888 888        8888888888  8888b.   .d88888         888     888d888  .d88b.   .d88b.  
  //   d88P  888 888 888        888    888     "88b d88" 888         888     888P"   d8P  Y8b d8P  Y8b 
  //  d88P   888 888 888 888888 888    888 .d888888 888  888         888     888     88888888 88888888 
  // d8888888888 888 888        888    888 888  888 Y88b 888         888     888     Y8b.     Y8b.     
  //d88P     888 888 888        888    888 "Y888888  "Y88888         888     888      "Y8888   "Y8888  
  //                                                                                                   
        
  TreeAllHad = new TTree("TreeAllHad","TreeAllHad"); 
 
  TreeAllHad->Branch("PassMETFilters"                        , & PassMETFilters                     ,    "PassMETFilters/I"                               );                                  
  TreeAllHad->Branch("Jet0PtRaw"                             , & Jet0PtRaw                          ,    "Jet0PtRaw/F"                               );                                  
  TreeAllHad->Branch("Jet0EtaRaw"                            , & Jet0EtaRaw                         ,    "Jet0EtaRaw/F"                              );                                   
  TreeAllHad->Branch("Jet0PhiRaw"                            , & Jet0PhiRaw                         ,    "Jet0PhiRaw/F"                              );                                   
  TreeAllHad->Branch("Jet0MassRaw"                           , & Jet0MassRaw                        ,    "Jet0MassRaw/F"                             );                                    
  TreeAllHad->Branch("Jet0P"                                 , & Jet0P                              ,    "Jet0P/F"                                   );                              
  TreeAllHad->Branch("Jet0Pt"                                , & Jet0Pt                             ,    "Jet0Pt/F"                                  );                               
  TreeAllHad->Branch("Jet0Eta"                               , & Jet0Eta                            ,    "Jet0Eta/F"                                 );                                
  TreeAllHad->Branch("Jet0Phi"                               , & Jet0Phi                            ,    "Jet0Phi/F"                                 );                                
  TreeAllHad->Branch("Jet0Rap"                               , & Jet0Rap                            ,    "Jet0Rap/F"                                 );                                
  TreeAllHad->Branch("Jet0Energy"                            , & Jet0Energy                         ,    "Jet0Energy/F"                              );                                   
  TreeAllHad->Branch("Jet0Mass"                              , & Jet0Mass                           ,    "Jet0Mass/F"                                );                                 
  TreeAllHad->Branch("Jet0Area"                              , & Jet0Area                           ,    "Jet0Area/F"                                );                                 
  TreeAllHad->Branch("Jet0MassSoftDrop"                      , & Jet0MassSoftDrop                   ,    "Jet0MassSoftDrop/F"                        );                                         
  TreeAllHad->Branch("Jet0MassSDsumSubjetRaw"                , & Jet0MassSDsumSubjetRaw             ,    "Jet0MassSDsumSubjetRaw/F"                  );                                               
  TreeAllHad->Branch("Jet0MassSDsumSubjetCorrL23"            , & Jet0MassSDsumSubjetCorrL23         ,    "Jet0MassSDsumSubjetCorrL23/F"              );                                                    
  TreeAllHad->Branch("Jet0MassSDsumSubjetCorrL23Up"          , & Jet0MassSDsumSubjetCorrL23Up       ,    "Jet0MassSDsumSubjetCorrL23Up/F"            );                                                      
  TreeAllHad->Branch("Jet0MassSDsumSubjetCorrL23Dn"          , & Jet0MassSDsumSubjetCorrL23Dn       ,    "Jet0MassSDsumSubjetCorrL23Dn/F"            );                                                      
  TreeAllHad->Branch("Jet0MassSDsumSubjetCorrL123"           , & Jet0MassSDsumSubjetCorrL123        ,    "Jet0MassSDsumSubjetCorrL123/F"             );                                                      
  TreeAllHad->Branch("Jet0MassSDsumSubjetCorrL123Up"         , & Jet0MassSDsumSubjetCorrL123Up      ,    "Jet0MassSDsumSubjetCorrL123Up/F"           );                                                        
  TreeAllHad->Branch("Jet0MassSDsumSubjetCorrL123Dn"         , & Jet0MassSDsumSubjetCorrL123Dn      ,    "Jet0MassSDsumSubjetCorrL123Dn/F"           );                                                        
  TreeAllHad->Branch("Jet0MassSDsumSubjetCorrSmear"          , & Jet0MassSDsumSubjetCorrSmear       ,    "Jet0MassSDsumSubjetCorrSmear/F"            );                                                     
  TreeAllHad->Branch("Jet0MassSDsumSubjetCorrSmearUp"        , & Jet0MassSDsumSubjetCorrSmearUp     ,    "Jet0MassSDsumSubjetCorrSmearUp/F"          );                                                       
  TreeAllHad->Branch("Jet0MassSDsumSubjetCorrSmearDn"        , & Jet0MassSDsumSubjetCorrSmearDn     ,    "Jet0MassSDsumSubjetCorrSmearDn/F"          );                                                       
  TreeAllHad->Branch("Jet0MassPruned"                        , & Jet0MassPruned                     ,    "Jet0MassPruned/F"                          );                                       
  TreeAllHad->Branch("Jet0Tau1"                              , & Jet0Tau1                           ,    "Jet0Tau1/F"                                );                                 
  TreeAllHad->Branch("Jet0Tau2"                              , & Jet0Tau2                           ,    "Jet0Tau2/F"                                );                                 
  TreeAllHad->Branch("Jet0Tau3"                              , & Jet0Tau3                           ,    "Jet0Tau3/F"                                );                                 
  TreeAllHad->Branch("Jet0Tau32"                             , & Jet0Tau32                          ,    "Jet0Tau32/F"                               );                                  
  TreeAllHad->Branch("Jet0Tau21"                             , & Jet0Tau21                          ,    "Jet0Tau21/F"                               );                                                                      
  TreeAllHad->Branch("Jet0SDmaxbdisc"                        , & Jet0SDmaxbdisc                     ,    "Jet0SDmaxbdisc/F"                          );                                       
  TreeAllHad->Branch("Jet0SDmaxbdiscflavHadron"              , & Jet0SDmaxbdiscflavHadron           ,    "Jet0SDmaxbdiscflavHadron/F"                );                                           
  TreeAllHad->Branch("Jet0SDmaxbdiscflavParton"              , & Jet0SDmaxbdiscflavParton           ,    "Jet0SDmaxbdiscflavParton/F"                );                                           
  TreeAllHad->Branch("Jet0SDsubjet0pt"                       , & Jet0SDsubjet0pt                    ,    "Jet0SDsubjet0pt/F"                         );                                        
  TreeAllHad->Branch("Jet0SDsubjet0mass"                     , & Jet0SDsubjet0mass                  ,    "Jet0SDsubjet0mass/F"                       ); 
  TreeAllHad->Branch("Jet0SDsubjet0eta"                      , & Jet0SDsubjet0eta                   ,    "Jet0SDsubjet0eta/F"                        );
  TreeAllHad->Branch("Jet0SDsubjet0phi"                      , & Jet0SDsubjet0phi                   ,    "Jet0SDsubjet0phi/F"                        );                                         
  TreeAllHad->Branch("Jet0SDsubjet0area"                     , & Jet0SDsubjet0area                  ,    "Jet0SDsubjet0area/F"                       );                                          
  TreeAllHad->Branch("Jet0SDsubjet0flavHadron"               , & Jet0SDsubjet0flavHadron            ,    "Jet0SDsubjet0flavHadron/F"                 );                                          
  TreeAllHad->Branch("Jet0SDsubjet0flavParton"               , & Jet0SDsubjet0flavParton            ,    "Jet0SDsubjet0flavParton/F"                 ); 
  TreeAllHad->Branch("Jet0SDsubjet0tau1"                     , & Jet0SDsubjet0tau1                  ,    "Jet0SDsubjet0tau1/F"                       );
  TreeAllHad->Branch("Jet0SDsubjet0tau2"                     , & Jet0SDsubjet0tau2                  ,    "Jet0SDsubjet0tau2/F"                       );
  TreeAllHad->Branch("Jet0SDsubjet0tau3"                     , & Jet0SDsubjet0tau3                  ,    "Jet0SDsubjet0tau3/F"                       ); 
  TreeAllHad->Branch("Jet0SDsubjet0bdisc"                    , & Jet0SDsubjet0bdisc                 ,    "Jet0SDsubjet0bdisc/F"                      );                                     
  TreeAllHad->Branch("Jet0SDsubjet1pt"                       , & Jet0SDsubjet1pt                    ,    "Jet0SDsubjet1pt/F"                         );                                        
  TreeAllHad->Branch("Jet0SDsubjet1mass"                     , & Jet0SDsubjet1mass                  ,    "Jet0SDsubjet1mass/F"                       );  
  TreeAllHad->Branch("Jet0SDsubjet1eta"                      , & Jet0SDsubjet1eta                   ,    "Jet0SDsubjet1eta/F"                        );
  TreeAllHad->Branch("Jet0SDsubjet1phi"                      , & Jet0SDsubjet1phi                   ,    "Jet0SDsubjet1phi/F"                        );                                        
  TreeAllHad->Branch("Jet0SDsubjet1area"                     , & Jet0SDsubjet1area                  ,    "Jet0SDsubjet1area/F"                       );                                          
  TreeAllHad->Branch("Jet0SDsubjet1flavHadron"               , & Jet0SDsubjet1flavHadron            ,    "Jet0SDsubjet1flavHadron/F"                 );                                          
  TreeAllHad->Branch("Jet0SDsubjet1flavParton"               , & Jet0SDsubjet1flavParton            ,    "Jet0SDsubjet1flavParton/F"                 ); 
  TreeAllHad->Branch("Jet0SDsubjet1tau1"                     , & Jet0SDsubjet1tau1                  ,    "Jet0SDsubjet1tau1/F"                       );
  TreeAllHad->Branch("Jet0SDsubjet1tau2"                     , & Jet0SDsubjet1tau2                  ,    "Jet0SDsubjet1tau2/F"                       );
  TreeAllHad->Branch("Jet0SDsubjet1tau3"                     , & Jet0SDsubjet1tau3                  ,    "Jet0SDsubjet1tau3/F"                       );  
  TreeAllHad->Branch("Jet0SDsubjet1bdisc"                    , & Jet0SDsubjet1bdisc                 ,    "Jet0SDsubjet1bdisc/F"                      );                                                                                    
  TreeAllHad->Branch("Jet0PuppiPt"                           , & Jet0PuppiPt                        ,    "Jet0PuppiPt/F"                             );                                    
  TreeAllHad->Branch("Jet0PuppiEta"                          , & Jet0PuppiEta                       ,    "Jet0PuppiEta/F"                            );                                     
  TreeAllHad->Branch("Jet0PuppiPhi"                          , & Jet0PuppiPhi                       ,    "Jet0PuppiPhi/F"                            );                                     
  TreeAllHad->Branch("Jet0PuppiMass"                         , & Jet0PuppiMass                      ,    "Jet0PuppiMass/F"                           );                                      
  TreeAllHad->Branch("Jet0PuppiMassSoftDrop"                 , & Jet0PuppiMassSoftDrop              ,    "Jet0PuppiMassSoftDrop/F"                   );                                              
  TreeAllHad->Branch("Jet0PuppiMassSDsumSubjetRaw"           , & Jet0PuppiMassSDsumSubjetRaw        ,    "Jet0PuppiMassSDsumSubjetRaw/F"             );                                                    
  TreeAllHad->Branch("Jet0PuppiMassSDsumSubjetCorr"          , & Jet0PuppiMassSDsumSubjetCorr       ,    "Jet0PuppiMassSDsumSubjetCorr/F"            );                                                     
  TreeAllHad->Branch("Jet0PuppiMassSDsumSubjetCorrUp"        , & Jet0PuppiMassSDsumSubjetCorrUp     ,    "Jet0PuppiMassSDsumSubjetCorrUp/F"          );                                                       
  TreeAllHad->Branch("Jet0PuppiMassSDsumSubjetCorrDn"        , & Jet0PuppiMassSDsumSubjetCorrDn     ,    "Jet0PuppiMassSDsumSubjetCorrDn/F"          );                                                       
  TreeAllHad->Branch("Jet0PuppiMassSDsumSubjetCorrSmear"     , & Jet0PuppiMassSDsumSubjetCorrSmear  ,    "Jet0PuppiMassSDsumSubjetCorrSmear/F"       );                                                          
  TreeAllHad->Branch("Jet0PuppiMassSDsumSubjetCorrSmearUp"   , & Jet0PuppiMassSDsumSubjetCorrSmearUp,    "Jet0PuppiMassSDsumSubjetCorrSmearUp/F"     );                                                            
  TreeAllHad->Branch("Jet0PuppiMassSDsumSubjetCorrSmearDn"   , & Jet0PuppiMassSDsumSubjetCorrSmearDn,    "Jet0PuppiMassSDsumSubjetCorrSmearDn/F"     );                                                            
  TreeAllHad->Branch("Jet0PuppiTau1"                         , & Jet0PuppiTau1                      ,    "Jet0PuppiTau1/F"                           );                                      
  TreeAllHad->Branch("Jet0PuppiTau2"                         , & Jet0PuppiTau2                      ,    "Jet0PuppiTau2/F"                           );                                      
  TreeAllHad->Branch("Jet0PuppiTau3"                         , & Jet0PuppiTau3                      ,    "Jet0PuppiTau3/F"                           );                                      
  TreeAllHad->Branch("Jet0PuppiTau32"                        , & Jet0PuppiTau32                     ,    "Jet0PuppiTau32/F"                          );                                       
  TreeAllHad->Branch("Jet0PuppiTau21"                        , & Jet0PuppiTau21                     ,    "Jet0PuppiTau21/F"                          );                                                                                
  TreeAllHad->Branch("Jet0PuppiSDmaxbdisc"                   , & Jet0PuppiSDmaxbdisc                ,    "Jet0PuppiSDmaxbdisc/F"                     );                                            
  TreeAllHad->Branch("Jet0PuppiSDmaxbdiscflavHadron"         , & Jet0PuppiSDmaxbdiscflavHadron      ,    "Jet0PuppiSDmaxbdiscflavHadron/F"           );                                                
  TreeAllHad->Branch("Jet0PuppiSDmaxbdiscflavParton"         , & Jet0PuppiSDmaxbdiscflavParton      ,    "Jet0PuppiSDmaxbdiscflavParton/F"           );                                                
  TreeAllHad->Branch("Jet0PuppiSDsubjet0pt"                  , & Jet0PuppiSDsubjet0pt               ,    "Jet0PuppiSDsubjet0pt/F"                    );                                             
  TreeAllHad->Branch("Jet0PuppiSDsubjet0mass"                , & Jet0PuppiSDsubjet0mass             ,    "Jet0PuppiSDsubjet0mass/F"                  );    
  TreeAllHad->Branch("Jet0PuppiSDsubjet0eta"                 , & Jet0PuppiSDsubjet0eta              ,    "Jet0PuppiSDsubjet0eta/F"                   );
  TreeAllHad->Branch("Jet0PuppiSDsubjet0phi"                 , & Jet0PuppiSDsubjet0phi              ,    "Jet0PuppiSDsubjet0phi/F"                   );                                           
  TreeAllHad->Branch("Jet0PuppiSDsubjet0area"                , & Jet0PuppiSDsubjet0area             ,    "Jet0PuppiSDsubjet0area/F"                  );                                               
  TreeAllHad->Branch("Jet0PuppiSDsubjet0flavHadron"          , & Jet0PuppiSDsubjet0flavHadron       ,    "Jet0PuppiSDsubjet0flavHadron/F"            );                                               
  TreeAllHad->Branch("Jet0PuppiSDsubjet0flavParton"          , & Jet0PuppiSDsubjet0flavParton       ,    "Jet0PuppiSDsubjet0flavParton/F"            ); 
  TreeAllHad->Branch("Jet0PuppiSDsubjet0tau1"                , & Jet0PuppiSDsubjet0tau1             ,    "Jet0PuppiSDsubjet0tau1/F"                  );
  TreeAllHad->Branch("Jet0PuppiSDsubjet0tau2"                , & Jet0PuppiSDsubjet0tau2             ,    "Jet0PuppiSDsubjet0tau2/F"                  );
  TreeAllHad->Branch("Jet0PuppiSDsubjet0tau3"                , & Jet0PuppiSDsubjet0tau3             ,    "Jet0PuppiSDsubjet0tau3/F"                  ); 
  TreeAllHad->Branch("Jet0PuppiSDsubjet0bdisc"               , & Jet0PuppiSDsubjet0bdisc            ,    "Jet0PuppiSDsubjet0bdisc/F"                 );                                          
  TreeAllHad->Branch("Jet0PuppiSDsubjet1pt"                  , & Jet0PuppiSDsubjet1pt               ,    "Jet0PuppiSDsubjet1pt/F"                    );                                             
  TreeAllHad->Branch("Jet0PuppiSDsubjet1mass"                , & Jet0PuppiSDsubjet1mass             ,    "Jet0PuppiSDsubjet1mass/F"                  );  
  TreeAllHad->Branch("Jet0PuppiSDsubjet1eta"                 , & Jet0PuppiSDsubjet1eta              ,    "Jet0PuppiSDsubjet1eta/F"                   );
  TreeAllHad->Branch("Jet0PuppiSDsubjet1phi"                 , & Jet0PuppiSDsubjet1phi              ,    "Jet0PuppiSDsubjet1phi/F"                   );                                             
  TreeAllHad->Branch("Jet0PuppiSDsubjet1area"                , & Jet0PuppiSDsubjet1area             ,    "Jet0PuppiSDsubjet1area/F"                  );                                               
  TreeAllHad->Branch("Jet0PuppiSDsubjet1flavHadron"          , & Jet0PuppiSDsubjet1flavHadron       ,    "Jet0PuppiSDsubjet1flavHadron/F"            );                                               
  TreeAllHad->Branch("Jet0PuppiSDsubjet1flavParton"          , & Jet0PuppiSDsubjet1flavParton       ,    "Jet0PuppiSDsubjet1flavParton/F"            );    
  TreeAllHad->Branch("Jet0PuppiSDsubjet1tau1"                , & Jet0PuppiSDsubjet1tau1             ,    "Jet0PuppiSDsubjet1tau1/F"                  );
  TreeAllHad->Branch("Jet0PuppiSDsubjet1tau2"                , & Jet0PuppiSDsubjet1tau2             ,    "Jet0PuppiSDsubjet1tau2/F"                  );
  TreeAllHad->Branch("Jet0PuppiSDsubjet1tau3"                , & Jet0PuppiSDsubjet1tau3             ,    "Jet0PuppiSDsubjet1tau3/F"                  ); 
  TreeAllHad->Branch("Jet0PuppiSDsubjet1bdisc"               , & Jet0PuppiSDsubjet1bdisc            ,    "Jet0PuppiSDsubjet1bdisc/F"                 );                                                                                          
  TreeAllHad->Branch("Jet0CHF"                               , & Jet0CHF                            ,    "Jet0CHF/F"                                 );                                
  TreeAllHad->Branch("Jet0NHF"                               , & Jet0NHF                            ,    "Jet0NHF/F"                                 );                                
  TreeAllHad->Branch("Jet0CM"                                , & Jet0CM                             ,    "Jet0CM/F"                                  );                               
  TreeAllHad->Branch("Jet0NM"                                , & Jet0NM                             ,    "Jet0NM/F"                                  );                               
  TreeAllHad->Branch("Jet0NEF"                               , & Jet0NEF                            ,    "Jet0NEF/F"                                 );                                
  TreeAllHad->Branch("Jet0CEF"                               , & Jet0CEF                            ,    "Jet0CEF/F"                                 );                                
  TreeAllHad->Branch("Jet0MF"                                , & Jet0MF                             ,    "Jet0MF/F"                                  );                               
  TreeAllHad->Branch("Jet0Mult"                              , & Jet0Mult                           ,    "Jet0Mult/F"                                );                                 
  TreeAllHad->Branch("Jet0MassCorrFactor"                    , & Jet0MassCorrFactor                 ,    "Jet0MassCorrFactor/F"                      );                                           
  TreeAllHad->Branch("Jet0MassCorrFactorUp"                  , & Jet0MassCorrFactorUp               ,    "Jet0MassCorrFactorUp/F"                    );                                             
  TreeAllHad->Branch("Jet0MassCorrFactorDn"                  , & Jet0MassCorrFactorDn               ,    "Jet0MassCorrFactorDn/F"                    );                                             
  TreeAllHad->Branch("Jet0CorrFactor"                        , & Jet0CorrFactor                     ,    "Jet0CorrFactor/F"                          );                                       
  TreeAllHad->Branch("Jet0CorrFactorUp"                      , & Jet0CorrFactorUp                   ,    "Jet0CorrFactorUp/F"                        );                                         
  TreeAllHad->Branch("Jet0CorrFactorDn"                      , & Jet0CorrFactorDn                   ,    "Jet0CorrFactorDn/F"                        );                                         
  TreeAllHad->Branch("Jet0PtSmearFactor"                     , & Jet0PtSmearFactor                  ,    "Jet0PtSmearFactor/F"                       );                                          
  TreeAllHad->Branch("Jet0PtSmearFactorUp"                   , & Jet0PtSmearFactorUp                ,    "Jet0PtSmearFactorUp/F"                     );                                            
  TreeAllHad->Branch("Jet0PtSmearFactorDn"                   , & Jet0PtSmearFactorDn                ,    "Jet0PtSmearFactorDn/F"                     );                                            
  TreeAllHad->Branch("Jet0PuppiMassCorrFactor"               , & Jet0PuppiMassCorrFactor            ,    "Jet0PuppiMassCorrFactor/F"                 );                                                
  TreeAllHad->Branch("Jet0PuppiMassCorrFactorUp"             , & Jet0PuppiMassCorrFactorUp          ,    "Jet0PuppiMassCorrFactorUp/F"               );                                                  
  TreeAllHad->Branch("Jet0PuppiMassCorrFactorDn"             , & Jet0PuppiMassCorrFactorDn          ,    "Jet0PuppiMassCorrFactorDn/F"               );                                                  
  TreeAllHad->Branch("Jet0PuppiCorrFactor"                   , & Jet0PuppiCorrFactor                ,    "Jet0PuppiCorrFactor/F"                     );                                            
  TreeAllHad->Branch("Jet0PuppiCorrFactorUp"                 , & Jet0PuppiCorrFactorUp              ,    "Jet0PuppiCorrFactorUp/F"                   );                                              
  TreeAllHad->Branch("Jet0PuppiCorrFactorDn"                 , & Jet0PuppiCorrFactorDn              ,    "Jet0PuppiCorrFactorDn/F"                   );                                              
  TreeAllHad->Branch("Jet0PuppiPtSmearFactor"                , & Jet0PuppiPtSmearFactor             ,    "Jet0PuppiPtSmearFactor/F"                  );                                               
  TreeAllHad->Branch("Jet0PuppiPtSmearFactorUp"              , & Jet0PuppiPtSmearFactorUp           ,    "Jet0PuppiPtSmearFactorUp/F"                );                                                 
  TreeAllHad->Branch("Jet0PuppiPtSmearFactorDn"              , & Jet0PuppiPtSmearFactorDn           ,    "Jet0PuppiPtSmearFactorDn/F"                );                                                 
  TreeAllHad->Branch("Jet0EtaScaleFactor"                    , & Jet0EtaScaleFactor                 ,    "Jet0EtaScaleFactor/F"                      );                                           
  TreeAllHad->Branch("Jet0PhiScaleFactor"                    , & Jet0PhiScaleFactor                 ,    "Jet0PhiScaleFactor/F"                      );                                           
  TreeAllHad->Branch("Jet0MatchedGenJetDR"                   , & Jet0MatchedGenJetDR                ,    "Jet0MatchedGenJetDR/F"                     );                                            
  TreeAllHad->Branch("Jet0MatchedGenJetPt"                   , & Jet0MatchedGenJetPt                ,    "Jet0MatchedGenJetPt/F"                     );                                            
  TreeAllHad->Branch("Jet0MatchedGenJetMass"                 , & Jet0MatchedGenJetMass              ,    "Jet0MatchedGenJetMass/F"                   );  

  TreeAllHad->Branch("Jet0GenMatched_TopHadronic"            , & Jet0GenMatched_TopHadronic         ,    "Jet0GenMatched_TopHadronic/I"              );      
  TreeAllHad->Branch("Jet0GenMatched_TopPt"                  , & Jet0GenMatched_TopPt               ,    "Jet0GenMatched_TopPt/F"                    );      
  TreeAllHad->Branch("Jet0GenMatched_TopEta"                 , & Jet0GenMatched_TopEta              ,    "Jet0GenMatched_TopEta/F"                   );      
  TreeAllHad->Branch("Jet0GenMatched_TopPhi"                 , & Jet0GenMatched_TopPhi              ,    "Jet0GenMatched_TopPhi/F"                   );      
  TreeAllHad->Branch("Jet0GenMatched_TopMass"                , & Jet0GenMatched_TopMass             ,    "Jet0GenMatched_TopMass/F"                  );      
  TreeAllHad->Branch("Jet0GenMatched_bPt"                    , & Jet0GenMatched_bPt                 ,    "Jet0GenMatched_bPt/F"                      );      
  TreeAllHad->Branch("Jet0GenMatched_WPt"                    , & Jet0GenMatched_WPt                 ,    "Jet0GenMatched_WPt/F"                      );      
  TreeAllHad->Branch("Jet0GenMatched_Wd1Pt"                  , & Jet0GenMatched_Wd1Pt               ,    "Jet0GenMatched_Wd1Pt/F"                    );      
  TreeAllHad->Branch("Jet0GenMatched_Wd2Pt"                  , & Jet0GenMatched_Wd2Pt               ,    "Jet0GenMatched_Wd2Pt/F"                    );      
  TreeAllHad->Branch("Jet0GenMatched_Wd1ID"                  , & Jet0GenMatched_Wd1ID               ,    "Jet0GenMatched_Wd1ID/F"                    );      
  TreeAllHad->Branch("Jet0GenMatched_Wd2ID"                  , & Jet0GenMatched_Wd2ID               ,    "Jet0GenMatched_Wd2ID/F"                    );      
  TreeAllHad->Branch("Jet0GenMatched_MaxDeltaRPartonTop"     , & Jet0GenMatched_MaxDeltaRPartonTop  ,    "Jet0GenMatched_MaxDeltaRPartonTop/F"       );      
  TreeAllHad->Branch("Jet0GenMatched_MaxDeltaRWPartonTop"    , & Jet0GenMatched_MaxDeltaRWPartonTop ,    "Jet0GenMatched_MaxDeltaRWPartonTop/F"      );      
  TreeAllHad->Branch("Jet0GenMatched_MaxDeltaRWPartonW"      , & Jet0GenMatched_MaxDeltaRWPartonW   ,    "Jet0GenMatched_MaxDeltaRWPartonW/F"        );      
  TreeAllHad->Branch("Jet0GenMatched_DeltaR_t_b"             , & Jet0GenMatched_DeltaR_t_b          ,    "Jet0GenMatched_DeltaR_t_b/F"               );      
  TreeAllHad->Branch("Jet0GenMatched_DeltaR_t_W"             , & Jet0GenMatched_DeltaR_t_W          ,    "Jet0GenMatched_DeltaR_t_W/F"               );      
  TreeAllHad->Branch("Jet0GenMatched_DeltaR_t_Wd1"           , & Jet0GenMatched_DeltaR_t_Wd1        ,    "Jet0GenMatched_DeltaR_t_Wd1/F"             );      
  TreeAllHad->Branch("Jet0GenMatched_DeltaR_t_Wd2"           , & Jet0GenMatched_DeltaR_t_Wd2        ,    "Jet0GenMatched_DeltaR_t_Wd2/F"             );      
  TreeAllHad->Branch("Jet0GenMatched_DeltaR_W_b1"            , & Jet0GenMatched_DeltaR_W_b1         ,    "Jet0GenMatched_DeltaR_W_b1/F"              );      
  TreeAllHad->Branch("Jet0GenMatched_DeltaR_W_Wd1"           , & Jet0GenMatched_DeltaR_W_Wd1        ,    "Jet0GenMatched_DeltaR_W_Wd1/F"             );      
  TreeAllHad->Branch("Jet0GenMatched_DeltaR_W_Wd2"           , & Jet0GenMatched_DeltaR_W_Wd2        ,    "Jet0GenMatched_DeltaR_W_Wd2/F"             );      
  TreeAllHad->Branch("Jet0GenMatched_DeltaR_Wd1_Wd2"         , & Jet0GenMatched_DeltaR_Wd1_Wd2      ,    "Jet0GenMatched_DeltaR_Wd1_Wd2/F"           );      
  TreeAllHad->Branch("Jet0GenMatched_DeltaR_Wd1_b"           , & Jet0GenMatched_DeltaR_Wd1_b        ,    "Jet0GenMatched_DeltaR_Wd1_b/F"             );      
  TreeAllHad->Branch("Jet0GenMatched_DeltaR_Wd2_b"           , & Jet0GenMatched_DeltaR_Wd2_b        ,    "Jet0GenMatched_DeltaR_Wd2_b/F"             );      
  TreeAllHad->Branch("Jet0GenMatched_DeltaR_jet_t"           , & Jet0GenMatched_DeltaR_jet_t        ,    "Jet0GenMatched_DeltaR_jet_t/F"             );      
  TreeAllHad->Branch("Jet0GenMatched_DeltaR_jet_W"           , & Jet0GenMatched_DeltaR_jet_W        ,    "Jet0GenMatched_DeltaR_jet_W/F"             );      
  TreeAllHad->Branch("Jet0GenMatched_DeltaR_jet_b"           , & Jet0GenMatched_DeltaR_jet_b        ,    "Jet0GenMatched_DeltaR_jet_b/F"             );      
  TreeAllHad->Branch("Jet0GenMatched_DeltaR_jet_Wd1"         , & Jet0GenMatched_DeltaR_jet_Wd1      ,    "Jet0GenMatched_DeltaR_jet_Wd1/F"           );      
  TreeAllHad->Branch("Jet0GenMatched_DeltaR_jet_Wd2"         , & Jet0GenMatched_DeltaR_jet_Wd2      ,    "Jet0GenMatched_DeltaR_jet_Wd2/F"           );      
  TreeAllHad->Branch("Jet0GenMatched_DeltaR_pup0_b"          , & Jet0GenMatched_DeltaR_pup0_b       ,    "Jet0GenMatched_DeltaR_pup0_b/F"            );      
  TreeAllHad->Branch("Jet0GenMatched_DeltaR_pup0_Wd1"        , & Jet0GenMatched_DeltaR_pup0_Wd1     ,    "Jet0GenMatched_DeltaR_pup0_Wd1/F"          );      
  TreeAllHad->Branch("Jet0GenMatched_DeltaR_pup0_Wd2"        , & Jet0GenMatched_DeltaR_pup0_Wd2     ,    "Jet0GenMatched_DeltaR_pup0_Wd2/F"          );      
  TreeAllHad->Branch("Jet0GenMatched_DeltaR_pup1_b"          , & Jet0GenMatched_DeltaR_pup1_b       ,    "Jet0GenMatched_DeltaR_pup1_b/F"            );      
  TreeAllHad->Branch("Jet0GenMatched_DeltaR_pup1_Wd1"        , & Jet0GenMatched_DeltaR_pup1_Wd1     ,    "Jet0GenMatched_DeltaR_pup1_Wd1/F"          );      
  TreeAllHad->Branch("Jet0GenMatched_DeltaR_pup1_Wd2"        , & Jet0GenMatched_DeltaR_pup1_Wd2     ,    "Jet0GenMatched_DeltaR_pup1_Wd2/F"          );               
  TreeAllHad->Branch("Jet0GenMatched_partonPt"               , & Jet0GenMatched_partonPt            ,    "Jet0GenMatched_partonPt/F"                 );      
  TreeAllHad->Branch("Jet0GenMatched_partonEta"              , & Jet0GenMatched_partonEta           ,    "Jet0GenMatched_partonEta/F"                );      
  TreeAllHad->Branch("Jet0GenMatched_partonPhi"              , & Jet0GenMatched_partonPhi           ,    "Jet0GenMatched_partonPhi/F"                );      
  TreeAllHad->Branch("Jet0GenMatched_partonMass"             , & Jet0GenMatched_partonMass          ,    "Jet0GenMatched_partonMass/F"               );      
  TreeAllHad->Branch("Jet0GenMatched_partonID"               , & Jet0GenMatched_partonID            ,    "Jet0GenMatched_partonID/F"                 );      
  TreeAllHad->Branch("Jet0GenMatched_DeltaRjetParton"        , & Jet0GenMatched_DeltaRjetParton     ,    "Jet0GenMatched_DeltaRjetParton/F"          );      
  std::cout<<"Setup Jet0"<<std::endl;
  
  TreeAllHad->Branch("Jet1PtRaw"                             , & Jet1PtRaw                          ,    "Jet1PtRaw/F"                               );                                  
  TreeAllHad->Branch("Jet1EtaRaw"                            , & Jet1EtaRaw                         ,    "Jet1EtaRaw/F"                              );                                   
  TreeAllHad->Branch("Jet1PhiRaw"                            , & Jet1PhiRaw                         ,    "Jet1PhiRaw/F"                              );                                   
  TreeAllHad->Branch("Jet1MassRaw"                           , & Jet1MassRaw                        ,    "Jet1MassRaw/F"                             );                                    
  TreeAllHad->Branch("Jet1P"                                 , & Jet1P                              ,    "Jet1P/F"                                   );                              
  TreeAllHad->Branch("Jet1Pt"                                , & Jet1Pt                             ,    "Jet1Pt/F"                                  );                               
  TreeAllHad->Branch("Jet1Eta"                               , & Jet1Eta                            ,    "Jet1Eta/F"                                 );                                
  TreeAllHad->Branch("Jet1Phi"                               , & Jet1Phi                            ,    "Jet1Phi/F"                                 );                                
  TreeAllHad->Branch("Jet1Rap"                               , & Jet1Rap                            ,    "Jet1Rap/F"                                 );                                
  TreeAllHad->Branch("Jet1Energy"                            , & Jet1Energy                         ,    "Jet1Energy/F"                              );                                   
  TreeAllHad->Branch("Jet1Mass"                              , & Jet1Mass                           ,    "Jet1Mass/F"                                );                                 
  TreeAllHad->Branch("Jet1Area"                              , & Jet1Area                           ,    "Jet1Area/F"                                );                                 
  TreeAllHad->Branch("Jet1MassSoftDrop"                      , & Jet1MassSoftDrop                   ,    "Jet1MassSoftDrop/F"                        );                                         
  TreeAllHad->Branch("Jet1MassSDsumSubjetRaw"                , & Jet1MassSDsumSubjetRaw             ,    "Jet1MassSDsumSubjetRaw/F"                  );                                               
  TreeAllHad->Branch("Jet1MassSDsumSubjetCorrL23"            , & Jet1MassSDsumSubjetCorrL23         ,    "Jet1MassSDsumSubjetCorrL23/F"              );                                                    
  TreeAllHad->Branch("Jet1MassSDsumSubjetCorrL23Up"          , & Jet1MassSDsumSubjetCorrL23Up       ,    "Jet1MassSDsumSubjetCorrL23Up/F"            );                                                      
  TreeAllHad->Branch("Jet1MassSDsumSubjetCorrL23Dn"          , & Jet1MassSDsumSubjetCorrL23Dn       ,    "Jet1MassSDsumSubjetCorrL23Dn/F"            );                                                      
  TreeAllHad->Branch("Jet1MassSDsumSubjetCorrL123"           , & Jet1MassSDsumSubjetCorrL123        ,    "Jet1MassSDsumSubjetCorrL123/F"             );                                                      
  TreeAllHad->Branch("Jet1MassSDsumSubjetCorrL123Up"         , & Jet1MassSDsumSubjetCorrL123Up      ,    "Jet1MassSDsumSubjetCorrL123Up/F"           );                                                        
  TreeAllHad->Branch("Jet1MassSDsumSubjetCorrL123Dn"         , & Jet1MassSDsumSubjetCorrL123Dn      ,    "Jet1MassSDsumSubjetCorrL123Dn/F"           );                                                        
  TreeAllHad->Branch("Jet1MassSDsumSubjetCorrSmear"          , & Jet1MassSDsumSubjetCorrSmear       ,    "Jet1MassSDsumSubjetCorrSmear/F"            );                                                     
  TreeAllHad->Branch("Jet1MassSDsumSubjetCorrSmearUp"        , & Jet1MassSDsumSubjetCorrSmearUp     ,    "Jet1MassSDsumSubjetCorrSmearUp/F"          );                                                       
  TreeAllHad->Branch("Jet1MassSDsumSubjetCorrSmearDn"        , & Jet1MassSDsumSubjetCorrSmearDn     ,    "Jet1MassSDsumSubjetCorrSmearDn/F"          );                                                       
  TreeAllHad->Branch("Jet1MassPruned"                        , & Jet1MassPruned                     ,    "Jet1MassPruned/F"                          );                                       
  TreeAllHad->Branch("Jet1Tau1"                              , & Jet1Tau1                           ,    "Jet1Tau1/F"                                );                                 
  TreeAllHad->Branch("Jet1Tau2"                              , & Jet1Tau2                           ,    "Jet1Tau2/F"                                );                                 
  TreeAllHad->Branch("Jet1Tau3"                              , & Jet1Tau3                           ,    "Jet1Tau3/F"                                );                                 
  TreeAllHad->Branch("Jet1Tau32"                             , & Jet1Tau32                          ,    "Jet1Tau32/F"                               );                                  
  TreeAllHad->Branch("Jet1Tau21"                             , & Jet1Tau21                          ,    "Jet1Tau21/F"                               );                                                                      
  TreeAllHad->Branch("Jet1SDmaxbdisc"                        , & Jet1SDmaxbdisc                     ,    "Jet1SDmaxbdisc/F"                          );                                       
  TreeAllHad->Branch("Jet1SDmaxbdiscflavHadron"              , & Jet1SDmaxbdiscflavHadron           ,    "Jet1SDmaxbdiscflavHadron/F"                );                                           
  TreeAllHad->Branch("Jet1SDmaxbdiscflavParton"              , & Jet1SDmaxbdiscflavParton           ,    "Jet1SDmaxbdiscflavParton/F"                );                                           
  TreeAllHad->Branch("Jet1SDsubjet0pt"                       , & Jet1SDsubjet0pt                    ,    "Jet1SDsubjet0pt/F"                         );                                        
  TreeAllHad->Branch("Jet1SDsubjet0mass"                     , & Jet1SDsubjet0mass                  ,    "Jet1SDsubjet0mass/F"                       ); 
  TreeAllHad->Branch("Jet1SDsubjet0eta"                      , & Jet1SDsubjet0eta                   ,    "Jet1SDsubjet0eta/F"                        );
  TreeAllHad->Branch("Jet1SDsubjet0phi"                      , & Jet1SDsubjet0phi                   ,    "Jet1SDsubjet0phi/F"                        );                                         
  TreeAllHad->Branch("Jet1SDsubjet0area"                     , & Jet1SDsubjet0area                  ,    "Jet1SDsubjet0area/F"                       );                                          
  TreeAllHad->Branch("Jet1SDsubjet0flavHadron"               , & Jet1SDsubjet0flavHadron            ,    "Jet1SDsubjet0flavHadron/F"                 );                                          
  TreeAllHad->Branch("Jet1SDsubjet0flavParton"               , & Jet1SDsubjet0flavParton            ,    "Jet1SDsubjet0flavParton/F"                 ); 
  TreeAllHad->Branch("Jet1SDsubjet0tau1"                     , & Jet1SDsubjet0tau1                  ,    "Jet1SDsubjet0tau1/F"                       );
  TreeAllHad->Branch("Jet1SDsubjet0tau2"                     , & Jet1SDsubjet0tau2                  ,    "Jet1SDsubjet0tau2/F"                       );
  TreeAllHad->Branch("Jet1SDsubjet0tau3"                     , & Jet1SDsubjet0tau3                  ,    "Jet1SDsubjet0tau3/F"                       );
  TreeAllHad->Branch("Jet1SDsubjet0bdisc"                    , & Jet1SDsubjet0bdisc                 ,    "Jet1SDsubjet0bdisc/F"                      );                                     
  TreeAllHad->Branch("Jet1SDsubjet1pt"                       , & Jet1SDsubjet1pt                    ,    "Jet1SDsubjet1pt/F"                         );                                        
  TreeAllHad->Branch("Jet1SDsubjet1mass"                     , & Jet1SDsubjet1mass                  ,    "Jet1SDsubjet1mass/F"                       );  
  TreeAllHad->Branch("Jet1SDsubjet1eta"                      , & Jet1SDsubjet1eta                   ,    "Jet1SDsubjet1eta/F"                        );
  TreeAllHad->Branch("Jet1SDsubjet1phi"                      , & Jet1SDsubjet1phi                   ,    "Jet1SDsubjet1phi/F"                        );                                        
  TreeAllHad->Branch("Jet1SDsubjet1area"                     , & Jet1SDsubjet1area                  ,    "Jet1SDsubjet1area/F"                       );                                          
  TreeAllHad->Branch("Jet1SDsubjet1flavHadron"               , & Jet1SDsubjet1flavHadron            ,    "Jet1SDsubjet1flavHadron/F"                 );                                          
  TreeAllHad->Branch("Jet1SDsubjet1flavParton"               , & Jet1SDsubjet1flavParton            ,    "Jet1SDsubjet1flavParton/F"                 ); 
  TreeAllHad->Branch("Jet1SDsubjet1tau1"                     , & Jet1SDsubjet1tau1                  ,    "Jet1SDsubjet1tau1/F"                       );
  TreeAllHad->Branch("Jet1SDsubjet1tau2"                     , & Jet1SDsubjet1tau2                  ,    "Jet1SDsubjet1tau2/F"                       );
  TreeAllHad->Branch("Jet1SDsubjet1tau3"                     , & Jet1SDsubjet1tau3                  ,    "Jet1SDsubjet1tau3/F"                       ); 
  TreeAllHad->Branch("Jet1SDsubjet1bdisc"                    , & Jet1SDsubjet1bdisc                 ,    "Jet1SDsubjet1bdisc/F"                      );                                                                                    
  TreeAllHad->Branch("Jet1PuppiPt"                           , & Jet1PuppiPt                        ,    "Jet1PuppiPt/F"                             );                                    
  TreeAllHad->Branch("Jet1PuppiEta"                          , & Jet1PuppiEta                       ,    "Jet1PuppiEta/F"                            );                                     
  TreeAllHad->Branch("Jet1PuppiPhi"                          , & Jet1PuppiPhi                       ,    "Jet1PuppiPhi/F"                            );                                     
  TreeAllHad->Branch("Jet1PuppiMass"                         , & Jet1PuppiMass                      ,    "Jet1PuppiMass/F"                           );                                      
  TreeAllHad->Branch("Jet1PuppiMassSoftDrop"                 , & Jet1PuppiMassSoftDrop              ,    "Jet1PuppiMassSoftDrop/F"                   );                                              
  TreeAllHad->Branch("Jet1PuppiMassSDsumSubjetRaw"           , & Jet1PuppiMassSDsumSubjetRaw        ,    "Jet1PuppiMassSDsumSubjetRaw/F"             );                                                    
  TreeAllHad->Branch("Jet1PuppiMassSDsumSubjetCorr"          , & Jet1PuppiMassSDsumSubjetCorr       ,    "Jet1PuppiMassSDsumSubjetCorr/F"            );                                                     
  TreeAllHad->Branch("Jet1PuppiMassSDsumSubjetCorrUp"        , & Jet1PuppiMassSDsumSubjetCorrUp     ,    "Jet1PuppiMassSDsumSubjetCorrUp/F"          );                                                       
  TreeAllHad->Branch("Jet1PuppiMassSDsumSubjetCorrDn"        , & Jet1PuppiMassSDsumSubjetCorrDn     ,    "Jet1PuppiMassSDsumSubjetCorrDn/F"          );                                                       
  TreeAllHad->Branch("Jet1PuppiMassSDsumSubjetCorrSmear"     , & Jet1PuppiMassSDsumSubjetCorrSmear  ,    "Jet1PuppiMassSDsumSubjetCorrSmear/F"       );                                                          
  TreeAllHad->Branch("Jet1PuppiMassSDsumSubjetCorrSmearUp"   , & Jet1PuppiMassSDsumSubjetCorrSmearUp,    "Jet1PuppiMassSDsumSubjetCorrSmearUp/F"     );                                                            
  TreeAllHad->Branch("Jet1PuppiMassSDsumSubjetCorrSmearDn"   , & Jet1PuppiMassSDsumSubjetCorrSmearDn,    "Jet1PuppiMassSDsumSubjetCorrSmearDn/F"     );                                                            
  TreeAllHad->Branch("Jet1PuppiTau1"                         , & Jet1PuppiTau1                      ,    "Jet1PuppiTau1/F"                           );                                      
  TreeAllHad->Branch("Jet1PuppiTau2"                         , & Jet1PuppiTau2                      ,    "Jet1PuppiTau2/F"                           );                                      
  TreeAllHad->Branch("Jet1PuppiTau3"                         , & Jet1PuppiTau3                      ,    "Jet1PuppiTau3/F"                           );                                      
  TreeAllHad->Branch("Jet1PuppiTau32"                        , & Jet1PuppiTau32                     ,    "Jet1PuppiTau32/F"                          );                                       
  TreeAllHad->Branch("Jet1PuppiTau21"                        , & Jet1PuppiTau21                     ,    "Jet1PuppiTau21/F"                          );                                       
  TreeAllHad->Branch("Jet1PuppiSDmaxbdisc"                   , & Jet1PuppiSDmaxbdisc                ,    "Jet1PuppiSDmaxbdisc/F"                     );                                            
  TreeAllHad->Branch("Jet1PuppiSDmaxbdiscflavHadron"         , & Jet1PuppiSDmaxbdiscflavHadron      ,    "Jet1PuppiSDmaxbdiscflavHadron/F"           );                                                
  TreeAllHad->Branch("Jet1PuppiSDmaxbdiscflavParton"         , & Jet1PuppiSDmaxbdiscflavParton      ,    "Jet1PuppiSDmaxbdiscflavParton/F"           );                                                
  TreeAllHad->Branch("Jet1PuppiSDsubjet0pt"                  , & Jet1PuppiSDsubjet0pt               ,    "Jet1PuppiSDsubjet0pt/F"                    );                                             
  TreeAllHad->Branch("Jet1PuppiSDsubjet0mass"                , & Jet1PuppiSDsubjet0mass             ,    "Jet1PuppiSDsubjet0mass/F"                  );    
  TreeAllHad->Branch("Jet1PuppiSDsubjet0eta"                 , & Jet1PuppiSDsubjet0eta              ,    "Jet1PuppiSDsubjet0eta/F"                   );
  TreeAllHad->Branch("Jet1PuppiSDsubjet0phi"                 , & Jet1PuppiSDsubjet0phi              ,    "Jet1PuppiSDsubjet0phi/F"                   );                                           
  TreeAllHad->Branch("Jet1PuppiSDsubjet0area"                , & Jet1PuppiSDsubjet0area             ,    "Jet1PuppiSDsubjet0area/F"                  );                                               
  TreeAllHad->Branch("Jet1PuppiSDsubjet0flavHadron"          , & Jet1PuppiSDsubjet0flavHadron       ,    "Jet1PuppiSDsubjet0flavHadron/F"            );                                               
  TreeAllHad->Branch("Jet1PuppiSDsubjet0flavParton"          , & Jet1PuppiSDsubjet0flavParton       ,    "Jet1PuppiSDsubjet0flavParton/F"            ); 
  TreeAllHad->Branch("Jet1PuppiSDsubjet0tau1"                , & Jet1PuppiSDsubjet0tau1             ,    "Jet1PuppiSDsubjet0tau1/F"                  );
  TreeAllHad->Branch("Jet1PuppiSDsubjet0tau2"                , & Jet1PuppiSDsubjet0tau2             ,    "Jet1PuppiSDsubjet0tau2/F"                  );
  TreeAllHad->Branch("Jet1PuppiSDsubjet0tau3"                , & Jet1PuppiSDsubjet0tau3             ,    "Jet1PuppiSDsubjet0tau3/F"                  );
  TreeAllHad->Branch("Jet1PuppiSDsubjet0bdisc"               , & Jet1PuppiSDsubjet0bdisc            ,    "Jet1PuppiSDsubjet0bdisc/F"                 );                                                                                         
  TreeAllHad->Branch("Jet1PuppiSDsubjet1pt"                  , & Jet1PuppiSDsubjet1pt               ,    "Jet1PuppiSDsubjet1pt/F"                    );                                             
  TreeAllHad->Branch("Jet1PuppiSDsubjet1mass"                , & Jet1PuppiSDsubjet1mass             ,    "Jet1PuppiSDsubjet1mass/F"                  );  
  TreeAllHad->Branch("Jet1PuppiSDsubjet1eta"                 , & Jet1PuppiSDsubjet1eta              ,    "Jet1PuppiSDsubjet1eta/F"                   );
  TreeAllHad->Branch("Jet1PuppiSDsubjet1phi"                 , & Jet1PuppiSDsubjet1phi              ,    "Jet1PuppiSDsubjet1phi/F"                   );                                             
  TreeAllHad->Branch("Jet1PuppiSDsubjet1area"                , & Jet1PuppiSDsubjet1area             ,    "Jet1PuppiSDsubjet1area/F"                  );                                               
  TreeAllHad->Branch("Jet1PuppiSDsubjet1flavHadron"          , & Jet1PuppiSDsubjet1flavHadron       ,    "Jet1PuppiSDsubjet1flavHadron/F"            );                                               
  TreeAllHad->Branch("Jet1PuppiSDsubjet1flavParton"          , & Jet1PuppiSDsubjet1flavParton       ,    "Jet1PuppiSDsubjet1flavParton/F"            );    
  TreeAllHad->Branch("Jet1PuppiSDsubjet1tau1"                , & Jet1PuppiSDsubjet1tau1             ,    "Jet1PuppiSDsubjet1tau1/F"                  );
  TreeAllHad->Branch("Jet1PuppiSDsubjet1tau2"                , & Jet1PuppiSDsubjet1tau2             ,    "Jet1PuppiSDsubjet1tau2/F"                  );
  TreeAllHad->Branch("Jet1PuppiSDsubjet1tau3"                , & Jet1PuppiSDsubjet1tau3             ,    "Jet1PuppiSDsubjet1tau3/F"                  ); 
  TreeAllHad->Branch("Jet1PuppiSDsubjet1bdisc"               , & Jet1PuppiSDsubjet1bdisc            ,    "Jet1PuppiSDsubjet1bdisc/F"                 );                                                                                       
  TreeAllHad->Branch("Jet1CHF"                               , & Jet1CHF                            ,    "Jet1CHF/F"                                 );                                
  TreeAllHad->Branch("Jet1NHF"                               , & Jet1NHF                            ,    "Jet1NHF/F"                                 );                                
  TreeAllHad->Branch("Jet1CM"                                , & Jet1CM                             ,    "Jet1CM/F"                                  );                               
  TreeAllHad->Branch("Jet1NM"                                , & Jet1NM                             ,    "Jet1NM/F"                                  );                               
  TreeAllHad->Branch("Jet1NEF"                               , & Jet1NEF                            ,    "Jet1NEF/F"                                 );                                
  TreeAllHad->Branch("Jet1CEF"                               , & Jet1CEF                            ,    "Jet1CEF/F"                                 );                                
  TreeAllHad->Branch("Jet1MF"                                , & Jet1MF                             ,    "Jet1MF/F"                                  );                               
  TreeAllHad->Branch("Jet1Mult"                              , & Jet1Mult                           ,    "Jet1Mult/F"                                );                                 
  TreeAllHad->Branch("Jet1MassCorrFactor"                    , & Jet1MassCorrFactor                 ,    "Jet1MassCorrFactor/F"                      );                                           
  TreeAllHad->Branch("Jet1MassCorrFactorUp"                  , & Jet1MassCorrFactorUp               ,    "Jet1MassCorrFactorUp/F"                    );                                             
  TreeAllHad->Branch("Jet1MassCorrFactorDn"                  , & Jet1MassCorrFactorDn               ,    "Jet1MassCorrFactorDn/F"                    );                                             
  TreeAllHad->Branch("Jet1CorrFactor"                        , & Jet1CorrFactor                     ,    "Jet1CorrFactor/F"                          );                                       
  TreeAllHad->Branch("Jet1CorrFactorUp"                      , & Jet1CorrFactorUp                   ,    "Jet1CorrFactorUp/F"                        );                                         
  TreeAllHad->Branch("Jet1CorrFactorDn"                      , & Jet1CorrFactorDn                   ,    "Jet1CorrFactorDn/F"                        );                                         
  TreeAllHad->Branch("Jet1PtSmearFactor"                     , & Jet1PtSmearFactor                  ,    "Jet1PtSmearFactor/F"                       );                                          
  TreeAllHad->Branch("Jet1PtSmearFactorUp"                   , & Jet1PtSmearFactorUp                ,    "Jet1PtSmearFactorUp/F"                     );                                            
  TreeAllHad->Branch("Jet1PtSmearFactorDn"                   , & Jet1PtSmearFactorDn                ,    "Jet1PtSmearFactorDn/F"                     );                                            
  TreeAllHad->Branch("Jet1PuppiMassCorrFactor"               , & Jet1PuppiMassCorrFactor            ,    "Jet1PuppiMassCorrFactor/F"                 );                                                
  TreeAllHad->Branch("Jet1PuppiMassCorrFactorUp"             , & Jet1PuppiMassCorrFactorUp          ,    "Jet1PuppiMassCorrFactorUp/F"               );                                                  
  TreeAllHad->Branch("Jet1PuppiMassCorrFactorDn"             , & Jet1PuppiMassCorrFactorDn          ,    "Jet1PuppiMassCorrFactorDn/F"               );                                                  
  TreeAllHad->Branch("Jet1PuppiCorrFactor"                   , & Jet1PuppiCorrFactor                ,    "Jet1PuppiCorrFactor/F"                     );                                            
  TreeAllHad->Branch("Jet1PuppiCorrFactorUp"                 , & Jet1PuppiCorrFactorUp              ,    "Jet1PuppiCorrFactorUp/F"                   );                                              
  TreeAllHad->Branch("Jet1PuppiCorrFactorDn"                 , & Jet1PuppiCorrFactorDn              ,    "Jet1PuppiCorrFactorDn/F"                   );                                              
  TreeAllHad->Branch("Jet1PuppiPtSmearFactor"                , & Jet1PuppiPtSmearFactor             ,    "Jet1PuppiPtSmearFactor/F"                  );                                               
  TreeAllHad->Branch("Jet1PuppiPtSmearFactorUp"              , & Jet1PuppiPtSmearFactorUp           ,    "Jet1PuppiPtSmearFactorUp/F"                );                                                 
  TreeAllHad->Branch("Jet1PuppiPtSmearFactorDn"              , & Jet1PuppiPtSmearFactorDn           ,    "Jet1PuppiPtSmearFactorDn/F"                );                                                 
  TreeAllHad->Branch("Jet1EtaScaleFactor"                    , & Jet1EtaScaleFactor                 ,    "Jet1EtaScaleFactor/F"                      );                                           
  TreeAllHad->Branch("Jet1PhiScaleFactor"                    , & Jet1PhiScaleFactor                 ,    "Jet1PhiScaleFactor/F"                      );                                           
  TreeAllHad->Branch("Jet1MatchedGenJetDR"                   , & Jet1MatchedGenJetDR                ,    "Jet1MatchedGenJetDR/F"                     );                                            
  TreeAllHad->Branch("Jet1MatchedGenJetPt"                   , & Jet1MatchedGenJetPt                ,    "Jet1MatchedGenJetPt/F"                     );                                            
  TreeAllHad->Branch("Jet1MatchedGenJetMass"                 , & Jet1MatchedGenJetMass              ,    "Jet1MatchedGenJetMass/F"                   ); 
                        
  TreeAllHad->Branch("Jet1GenMatched_TopHadronic"            , & Jet1GenMatched_TopHadronic         ,    "Jet1GenMatched_TopHadronic/I"              );      
  TreeAllHad->Branch("Jet1GenMatched_TopPt"                  , & Jet1GenMatched_TopPt               ,    "Jet1GenMatched_TopPt/F"                    );      
  TreeAllHad->Branch("Jet1GenMatched_TopEta"                 , & Jet1GenMatched_TopEta              ,    "Jet1GenMatched_TopEta/F"                   );      
  TreeAllHad->Branch("Jet1GenMatched_TopPhi"                 , & Jet1GenMatched_TopPhi              ,    "Jet1GenMatched_TopPhi/F"                   );      
  TreeAllHad->Branch("Jet1GenMatched_TopMass"                , & Jet1GenMatched_TopMass             ,    "Jet1GenMatched_TopMass/F"                  );      
  TreeAllHad->Branch("Jet1GenMatched_bPt"                    , & Jet1GenMatched_bPt                 ,    "Jet1GenMatched_bPt/F"                      );      
  TreeAllHad->Branch("Jet1GenMatched_WPt"                    , & Jet1GenMatched_WPt                 ,    "Jet1GenMatched_WPt/F"                      );      
  TreeAllHad->Branch("Jet1GenMatched_Wd1Pt"                  , & Jet1GenMatched_Wd1Pt               ,    "Jet1GenMatched_Wd1Pt/F"                    );      
  TreeAllHad->Branch("Jet1GenMatched_Wd2Pt"                  , & Jet1GenMatched_Wd2Pt               ,    "Jet1GenMatched_Wd2Pt/F"                    );      
  TreeAllHad->Branch("Jet1GenMatched_Wd1ID"                  , & Jet1GenMatched_Wd1ID               ,    "Jet1GenMatched_Wd1ID/F"                    );      
  TreeAllHad->Branch("Jet1GenMatched_Wd2ID"                  , & Jet1GenMatched_Wd2ID               ,    "Jet1GenMatched_Wd2ID/F"                    );      
  TreeAllHad->Branch("Jet1GenMatched_MaxDeltaRPartonTop"     , & Jet1GenMatched_MaxDeltaRPartonTop  ,    "Jet1GenMatched_MaxDeltaRPartonTop/F"       );      
  TreeAllHad->Branch("Jet1GenMatched_MaxDeltaRWPartonTop"    , & Jet1GenMatched_MaxDeltaRWPartonTop ,    "Jet1GenMatched_MaxDeltaRWPartonTop/F"      );      
  TreeAllHad->Branch("Jet1GenMatched_MaxDeltaRWPartonW"      , & Jet1GenMatched_MaxDeltaRWPartonW   ,    "Jet1GenMatched_MaxDeltaRWPartonW/F"        );      
  TreeAllHad->Branch("Jet1GenMatched_DeltaR_t_b"             , & Jet1GenMatched_DeltaR_t_b          ,    "Jet1GenMatched_DeltaR_t_b/F"               );      
  TreeAllHad->Branch("Jet1GenMatched_DeltaR_t_W"             , & Jet1GenMatched_DeltaR_t_W          ,    "Jet1GenMatched_DeltaR_t_W/F"               );      
  TreeAllHad->Branch("Jet1GenMatched_DeltaR_t_Wd1"           , & Jet1GenMatched_DeltaR_t_Wd1        ,    "Jet1GenMatched_DeltaR_t_Wd1/F"             );      
  TreeAllHad->Branch("Jet1GenMatched_DeltaR_t_Wd2"           , & Jet1GenMatched_DeltaR_t_Wd2        ,    "Jet1GenMatched_DeltaR_t_Wd2/F"             );      
  TreeAllHad->Branch("Jet1GenMatched_DeltaR_W_b1"            , & Jet1GenMatched_DeltaR_W_b1         ,    "Jet1GenMatched_DeltaR_W_b1/F"              );      
  TreeAllHad->Branch("Jet1GenMatched_DeltaR_W_Wd1"           , & Jet1GenMatched_DeltaR_W_Wd1        ,    "Jet1GenMatched_DeltaR_W_Wd1/F"             );      
  TreeAllHad->Branch("Jet1GenMatched_DeltaR_W_Wd2"           , & Jet1GenMatched_DeltaR_W_Wd2        ,    "Jet1GenMatched_DeltaR_W_Wd2/F"             );      
  TreeAllHad->Branch("Jet1GenMatched_DeltaR_Wd1_Wd2"         , & Jet1GenMatched_DeltaR_Wd1_Wd2      ,    "Jet1GenMatched_DeltaR_Wd1_Wd2/F"           );      
  TreeAllHad->Branch("Jet1GenMatched_DeltaR_Wd1_b"           , & Jet1GenMatched_DeltaR_Wd1_b        ,    "Jet1GenMatched_DeltaR_Wd1_b/F"             );      
  TreeAllHad->Branch("Jet1GenMatched_DeltaR_Wd2_b"           , & Jet1GenMatched_DeltaR_Wd2_b        ,    "Jet1GenMatched_DeltaR_Wd2_b/F"             );      
  TreeAllHad->Branch("Jet1GenMatched_DeltaR_jet_t"           , & Jet1GenMatched_DeltaR_jet_t        ,    "Jet1GenMatched_DeltaR_jet_t/F"             );      
  TreeAllHad->Branch("Jet1GenMatched_DeltaR_jet_W"           , & Jet1GenMatched_DeltaR_jet_W        ,    "Jet1GenMatched_DeltaR_jet_W/F"             );      
  TreeAllHad->Branch("Jet1GenMatched_DeltaR_jet_b"           , & Jet1GenMatched_DeltaR_jet_b        ,    "Jet1GenMatched_DeltaR_jet_b/F"             );      
  TreeAllHad->Branch("Jet1GenMatched_DeltaR_jet_Wd1"         , & Jet1GenMatched_DeltaR_jet_Wd1      ,    "Jet1GenMatched_DeltaR_jet_Wd1/F"           );      
  TreeAllHad->Branch("Jet1GenMatched_DeltaR_jet_Wd2"         , & Jet1GenMatched_DeltaR_jet_Wd2      ,    "Jet1GenMatched_DeltaR_jet_Wd2/F"           );      
  TreeAllHad->Branch("Jet1GenMatched_DeltaR_pup0_b"          , & Jet1GenMatched_DeltaR_pup0_b       ,    "Jet1GenMatched_DeltaR_pup0_b/F"            );      
  TreeAllHad->Branch("Jet1GenMatched_DeltaR_pup0_Wd1"        , & Jet1GenMatched_DeltaR_pup0_Wd1     ,    "Jet1GenMatched_DeltaR_pup0_Wd1/F"          );      
  TreeAllHad->Branch("Jet1GenMatched_DeltaR_pup0_Wd2"        , & Jet1GenMatched_DeltaR_pup0_Wd2     ,    "Jet1GenMatched_DeltaR_pup0_Wd2/F"          );      
  TreeAllHad->Branch("Jet1GenMatched_DeltaR_pup1_b"          , & Jet1GenMatched_DeltaR_pup1_b       ,    "Jet1GenMatched_DeltaR_pup1_b/F"            );      
  TreeAllHad->Branch("Jet1GenMatched_DeltaR_pup1_Wd1"        , & Jet1GenMatched_DeltaR_pup1_Wd1     ,    "Jet1GenMatched_DeltaR_pup1_Wd1/F"          );      
  TreeAllHad->Branch("Jet1GenMatched_DeltaR_pup1_Wd2"        , & Jet1GenMatched_DeltaR_pup1_Wd2     ,    "Jet1GenMatched_DeltaR_pup1_Wd2/F"          );               
  TreeAllHad->Branch("Jet1GenMatched_partonPt"               , & Jet1GenMatched_partonPt            ,    "Jet1GenMatched_partonPt/F"                 );      
  TreeAllHad->Branch("Jet1GenMatched_partonEta"              , & Jet1GenMatched_partonEta           ,    "Jet1GenMatched_partonEta/F"                );      
  TreeAllHad->Branch("Jet1GenMatched_partonPhi"              , & Jet1GenMatched_partonPhi           ,    "Jet1GenMatched_partonPhi/F"                );      
  TreeAllHad->Branch("Jet1GenMatched_partonMass"             , & Jet1GenMatched_partonMass          ,    "Jet1GenMatched_partonMass/F"               );      
  TreeAllHad->Branch("Jet1GenMatched_partonID"               , & Jet1GenMatched_partonID            ,    "Jet1GenMatched_partonID/F"                 );      
  TreeAllHad->Branch("Jet1GenMatched_DeltaRjetParton"        , & Jet1GenMatched_DeltaRjetParton     ,    "Jet1GenMatched_DeltaRjetParton/F"          );      
  std::cout<<"Setup Jet1"<<std::endl;

  TreeAllHad->Branch("AllHadMETpx"                           , & AllHadMETpx                        ,    "AllHadMETpx/F"                             );                                    
  TreeAllHad->Branch("AllHadMETpy"                           , & AllHadMETpy                        ,    "AllHadMETpy/F"                             );                                    
  TreeAllHad->Branch("AllHadMETpt"                           , & AllHadMETpt                        ,    "AllHadMETpt/F"                             );                                    
  TreeAllHad->Branch("AllHadMETphi"                          , & AllHadMETphi                       ,    "AllHadMETphi/F"                            );                                     
  TreeAllHad->Branch("AllHadMETsumET"                        , & AllHadMETsumET                     ,    "AllHadMETsumET/F"                          );                                     
  TreeAllHad->Branch("AllHadNvtx"                            , & AllHadNvtx                         ,    "AllHadNvtx/F"                              );                                   
  TreeAllHad->Branch("AllHadRho"                             , & AllHadRho                          ,    "AllHadRho/F"                               );                                  
  TreeAllHad->Branch("AllHadEventWeight"                     , & AllHadEventWeight                  ,    "AllHadEventWeight/F"                       );                                          
  TreeAllHad->Branch("DijetMass"                             , & DijetMass                          ,    "DijetMass/F"                               );                                  
  TreeAllHad->Branch("DijetDeltaR"                           , & DijetDeltaR                        ,    "DijetDeltaR/F"                             );                                    
  TreeAllHad->Branch("DijetDeltaPhi"                         , & DijetDeltaPhi                      ,    "DijetDeltaPhi/F"                           );                                      
  TreeAllHad->Branch("DijetDeltaRap"                         , & DijetDeltaRap                      ,    "DijetDeltaRap/F"                           );                                      
  TreeAllHad->Branch("DiGenJetMass"                          , & DiGenJetMass                       ,    "DiGenJetMass/F"                            );                                     
  TreeAllHad->Branch("GenTTmass"                             , & GenTTmass                          ,    "GenTTmass/F"                               );                                  
  TreeAllHad->Branch("HT"                                    , & HT                                 ,    "HT/F"                                      );                           
  TreeAllHad->Branch("HT_CorrDn"                             , & HT_CorrDn                          ,    "HT_CorrDn/F"                               );                                  
  TreeAllHad->Branch("HT_CorrUp"                             , & HT_CorrUp                          ,    "HT_CorrUp/F"                               );                                  
  TreeAllHad->Branch("HT_PtSmearUp"                          , & HT_PtSmearUp                       ,    "HT_PtSmearUp/F"                            );                                     
  TreeAllHad->Branch("HT_PtSmearDn"                          , & HT_PtSmearDn                       ,    "HT_PtSmearDn/F"                            );                                     
  TreeAllHad->Branch("Q2weight_CorrDn"                       , & Q2weight_CorrDn                    ,    "Q2weight_CorrDn/F"                         );                                        
  TreeAllHad->Branch("Q2weight_CorrUp"                       , & Q2weight_CorrUp                    ,    "Q2weight_CorrUp/F"                         );                                        
  TreeAllHad->Branch("NNPDF3weight_CorrDn"                   , & NNPDF3weight_CorrDn                ,    "NNPDF3weight_CorrDn/F"                     );                                            
  TreeAllHad->Branch("NNPDF3weight_CorrUp"                   , & NNPDF3weight_CorrUp                ,    "NNPDF3weight_CorrUp/F"                     );                                            
  TreeAllHad->Branch("AllHadRunNum"                          , & AllHadRunNum                       ,    "AllHadRunNum/F"                            );                                     
  TreeAllHad->Branch("AllHadLumiBlock"                       , & AllHadLumiBlock                    ,    "AllHadLumiBlock/F"                         );                                        
  TreeAllHad->Branch("AllHadEventNum"                        , & AllHadEventNum                     ,    "AllHadEventNum/F"                          );                                       
  std::cout<<"Setup all-had event tree"<<std::endl;

  // 
  //  .d8888b.                         d8b        888                        888        88888888888                           
  // d88P  Y88b                        Y8P        888                        888            888                               
  // Y88b.                                        888                        888            888                               
  //  "Y888b.    .d88b.  88888b.d88b.  888        888       .d88b.  88888b.  888888         888     888d888  .d88b.   .d88b.  
  //     "Y88b. d8P  Y8b 888 "888 "88b 888        888      d8P  Y8b 888 "88b 888            888     888P"   d8P  Y8b d8P  Y8b 
  //       "888 88888888 888  888  888 888 888888 888      88888888 888  888 888            888     888     88888888 88888888 
  // Y88b  d88P Y8b.     888  888  888 888        888      Y8b.     888 d88P Y88b.          888     888     Y8b.     Y8b.     
  //  "Y8888P"   "Y8888  888  888  888 888        88888888  "Y8888  88888P"   "Y888         888     888      "Y8888   "Y8888  
  //                                                                888                                                       
  //                                                                888                                                       
  //                                                                888       
  
  TreeSemiLept = new TTree("TreeSemiLept","TreeSemiLept"); 
       
  TreeSemiLept->Branch("JetPtRaw"                             , & JetPtRaw                          ,    "JetPtRaw/F"                               );                                  
  TreeSemiLept->Branch("JetEtaRaw"                            , & JetEtaRaw                         ,    "JetEtaRaw/F"                              );                                   
  TreeSemiLept->Branch("JetPhiRaw"                            , & JetPhiRaw                         ,    "JetPhiRaw/F"                              );                                   
  TreeSemiLept->Branch("JetMassRaw"                           , & JetMassRaw                        ,    "JetMassRaw/F"                             );                                    
  TreeSemiLept->Branch("JetP"                                 , & JetP                              ,    "JetP/F"                                   );                              
  TreeSemiLept->Branch("JetPt"                                , & JetPt                             ,    "JetPt/F"                                  );                               
  TreeSemiLept->Branch("JetEta"                               , & JetEta                            ,    "JetEta/F"                                 );                                
  TreeSemiLept->Branch("JetPhi"                               , & JetPhi                            ,    "JetPhi/F"                                 );                                
  TreeSemiLept->Branch("JetRap"                               , & JetRap                            ,    "JetRap/F"                                 );                                
  TreeSemiLept->Branch("JetEnergy"                            , & JetEnergy                         ,    "JetEnergy/F"                              );                                   
  TreeSemiLept->Branch("JetMass"                              , & JetMass                           ,    "JetMass/F"                                );                                 
  TreeSemiLept->Branch("JetArea"                              , & JetArea                           ,    "JetArea/F"                                );                                 
  TreeSemiLept->Branch("JetMassSoftDrop"                      , & JetMassSoftDrop                   ,    "JetMassSoftDrop/F"                        );                                         
  TreeSemiLept->Branch("JetMassSDsumSubjetRaw"                , & JetMassSDsumSubjetRaw             ,    "JetMassSDsumSubjetRaw/F"                  );                                               
  TreeSemiLept->Branch("JetMassSDsumSubjetCorrL23"            , & JetMassSDsumSubjetCorrL23         ,    "JetMassSDsumSubjetCorrL23/F"              );                                                    
  TreeSemiLept->Branch("JetMassSDsumSubjetCorrL23Up"          , & JetMassSDsumSubjetCorrL23Up       ,    "JetMassSDsumSubjetCorrL23Up/F"            );                                                      
  TreeSemiLept->Branch("JetMassSDsumSubjetCorrL23Dn"          , & JetMassSDsumSubjetCorrL23Dn       ,    "JetMassSDsumSubjetCorrL23Dn/F"            );                                                      
  TreeSemiLept->Branch("JetMassSDsumSubjetCorrL123"           , & JetMassSDsumSubjetCorrL123        ,    "JetMassSDsumSubjetCorrL123/F"             );                                                      
  TreeSemiLept->Branch("JetMassSDsumSubjetCorrL123Up"         , & JetMassSDsumSubjetCorrL123Up      ,    "JetMassSDsumSubjetCorrL123Up/F"           );                                                        
  TreeSemiLept->Branch("JetMassSDsumSubjetCorrL123Dn"         , & JetMassSDsumSubjetCorrL123Dn      ,    "JetMassSDsumSubjetCorrL123Dn/F"           );                                                        
  TreeSemiLept->Branch("JetMassSDsumSubjetCorrSmear"          , & JetMassSDsumSubjetCorrSmear       ,    "JetMassSDsumSubjetCorrSmear/F"            );                                                     
  TreeSemiLept->Branch("JetMassSDsumSubjetCorrSmearUp"        , & JetMassSDsumSubjetCorrSmearUp     ,    "JetMassSDsumSubjetCorrSmearUp/F"          );                                                       
  TreeSemiLept->Branch("JetMassSDsumSubjetCorrSmearDn"        , & JetMassSDsumSubjetCorrSmearDn     ,    "JetMassSDsumSubjetCorrSmearDn/F"          );                                                       
  TreeSemiLept->Branch("JetMassPruned"                        , & JetMassPruned                     ,    "JetMassPruned/F"                          );                                       
  TreeSemiLept->Branch("JetTau1"                              , & JetTau1                           ,    "JetTau1/F"                                );                                 
  TreeSemiLept->Branch("JetTau2"                              , & JetTau2                           ,    "JetTau2/F"                                );                                 
  TreeSemiLept->Branch("JetTau3"                              , & JetTau3                           ,    "JetTau3/F"                                );                                 
  TreeSemiLept->Branch("JetTau32"                             , & JetTau32                          ,    "JetTau32/F"                               );                                  
  TreeSemiLept->Branch("JetTau21"                             , & JetTau21                          ,    "JetTau21/F"                               );                                  
  TreeSemiLept->Branch("JetSDmaxbdisc"                        , & JetSDmaxbdisc                     ,    "JetSDmaxbdisc/F"                          );                                       
  TreeSemiLept->Branch("JetSDmaxbdiscflavHadron"              , & JetSDmaxbdiscflavHadron           ,    "JetSDmaxbdiscflavHadron/F"                );                                           
  TreeSemiLept->Branch("JetSDmaxbdiscflavParton"              , & JetSDmaxbdiscflavParton           ,    "JetSDmaxbdiscflavParton/F"                );  
  std::cout<<"Setup semi-lept chs jet"<<std::endl;
                                         
  TreeSemiLept->Branch("JetSDsubjet0pt"                       , & JetSDsubjet0pt                    ,    "JetSDsubjet0pt/F"                         );    
  TreeSemiLept->Branch("JetSDsubjet0mass"                     , & JetSDsubjet0mass                  ,    "JetSDsubjet0mass/F"                       );
  TreeSemiLept->Branch("JetSDsubjet0eta"                      , & JetSDsubjet0eta                   ,    "JetSDsubjet0eta/F"                        );
  TreeSemiLept->Branch("JetSDsubjet0phi"                      , & JetSDsubjet0phi                   ,    "JetSDsubjet0phi/F"                        );
  TreeSemiLept->Branch("JetSDsubjet0area"                     , & JetSDsubjet0area                  ,    "JetSDsubjet0area/F"                       );
  TreeSemiLept->Branch("JetSDsubjet0flavHadron"               , & JetSDsubjet0flavHadron            ,    "JetSDsubjet0flavHadron/F"                 );
  TreeSemiLept->Branch("JetSDsubjet0flavParton"               , & JetSDsubjet0flavParton            ,    "JetSDsubjet0flavParton/F"                 );
  TreeSemiLept->Branch("JetSDsubjet0tau1"                     , & JetSDsubjet0tau1                  ,    "JetSDsubjet0tau1/F"                       );
  TreeSemiLept->Branch("JetSDsubjet0tau2"                     , & JetSDsubjet0tau2                  ,    "JetSDsubjet0tau2/F"                       );
  TreeSemiLept->Branch("JetSDsubjet0tau3"                     , & JetSDsubjet0tau3                  ,    "JetSDsubjet0tau3/F"                       ); 
  TreeSemiLept->Branch("JetSDsubjet0bdisc"                    , & JetSDsubjet0bdisc                 ,    "JetSDsubjet0bdisc/F"                      );                                          
  TreeSemiLept->Branch("JetSDsubjet1pt"                       , & JetSDsubjet1pt                    ,    "JetSDsubjet1pt/F"                         );    
  TreeSemiLept->Branch("JetSDsubjet1mass"                     , & JetSDsubjet1mass                  ,    "JetSDsubjet1mass/F"                       );
  TreeSemiLept->Branch("JetSDsubjet1eta"                      , & JetSDsubjet1eta                   ,    "JetSDsubjet1eta/F"                        );
  TreeSemiLept->Branch("JetSDsubjet1phi"                      , & JetSDsubjet1phi                   ,    "JetSDsubjet1phi/F"                        );  
  TreeSemiLept->Branch("JetSDsubjet1area"                     , & JetSDsubjet1area                  ,    "JetSDsubjet1area/F"                       );
  TreeSemiLept->Branch("JetSDsubjet1flavHadron"               , & JetSDsubjet1flavHadron            ,    "JetSDsubjet1flavHadron/F"                 );
  TreeSemiLept->Branch("JetSDsubjet1flavParton"               , & JetSDsubjet1flavParton            ,    "JetSDsubjet1flavParton/F"                 );
  TreeSemiLept->Branch("JetSDsubjet1tau1"                     , & JetSDsubjet1tau1                  ,    "JetSDsubjet1tau1/F"                       );
  TreeSemiLept->Branch("JetSDsubjet1tau2"                     , & JetSDsubjet1tau2                  ,    "JetSDsubjet1tau2/F"                       );
  TreeSemiLept->Branch("JetSDsubjet1tau3"                     , & JetSDsubjet1tau3                  ,    "JetSDsubjet1tau3/F"                       );                                           
  TreeSemiLept->Branch("JetSDsubjet1bdisc"                    , & JetSDsubjet1bdisc                 ,    "JetSDsubjet1bdisc/F"                      );                                     
  std::cout<<"Setup semi-lept chs subjet"<<std::endl;

  TreeSemiLept->Branch("JetPuppiPt"                           , & JetPuppiPt                        ,    "JetPuppiPt/F"                             );                                    
  TreeSemiLept->Branch("JetPuppiEta"                          , & JetPuppiEta                       ,    "JetPuppiEta/F"                            );                                     
  TreeSemiLept->Branch("JetPuppiPhi"                          , & JetPuppiPhi                       ,    "JetPuppiPhi/F"                            );                                     
  TreeSemiLept->Branch("JetPuppiMass"                         , & JetPuppiMass                      ,    "JetPuppiMass/F"                           );                                      
  TreeSemiLept->Branch("JetPuppiMassSoftDrop"                 , & JetPuppiMassSoftDrop              ,    "JetPuppiMassSoftDrop/F"                   );                                              
  TreeSemiLept->Branch("JetPuppiMassSDsumSubjetRaw"           , & JetPuppiMassSDsumSubjetRaw        ,    "JetPuppiMassSDsumSubjetRaw/F"             );                                                    
  TreeSemiLept->Branch("JetPuppiMassSDsumSubjetCorr"          , & JetPuppiMassSDsumSubjetCorr       ,    "JetPuppiMassSDsumSubjetCorr/F"            );                                                     
  TreeSemiLept->Branch("JetPuppiMassSDsumSubjetCorrUp"        , & JetPuppiMassSDsumSubjetCorrUp     ,    "JetPuppiMassSDsumSubjetCorrUp/F"          );                                                       
  TreeSemiLept->Branch("JetPuppiMassSDsumSubjetCorrDn"        , & JetPuppiMassSDsumSubjetCorrDn     ,    "JetPuppiMassSDsumSubjetCorrDn/F"          );                                                       
  TreeSemiLept->Branch("JetPuppiMassSDsumSubjetCorrSmear"     , & JetPuppiMassSDsumSubjetCorrSmear  ,    "JetPuppiMassSDsumSubjetCorrSmear/F"       );                                                          
  TreeSemiLept->Branch("JetPuppiMassSDsumSubjetCorrSmearUp"   , & JetPuppiMassSDsumSubjetCorrSmearUp,    "JetPuppiMassSDsumSubjetCorrSmearUp/F"     );                                                            
  TreeSemiLept->Branch("JetPuppiMassSDsumSubjetCorrSmearDn"   , & JetPuppiMassSDsumSubjetCorrSmearDn,    "JetPuppiMassSDsumSubjetCorrSmearDn/F"     );                                                            
  TreeSemiLept->Branch("JetPuppiTau1"                         , & JetPuppiTau1                      ,    "JetPuppiTau1/F"                           );                                      
  TreeSemiLept->Branch("JetPuppiTau2"                         , & JetPuppiTau2                      ,    "JetPuppiTau2/F"                           );                                      
  TreeSemiLept->Branch("JetPuppiTau3"                         , & JetPuppiTau3                      ,    "JetPuppiTau3/F"                           );                                      
  TreeSemiLept->Branch("JetPuppiTau32"                        , & JetPuppiTau32                     ,    "JetPuppiTau32/F"                          );                                       
  TreeSemiLept->Branch("JetPuppiTau21"                        , & JetPuppiTau21                     ,    "JetPuppiTau21/F"                          );                                       
    std::cout<<"Setup semi-lept puppi jet"<<std::endl;

  TreeSemiLept->Branch("JetPuppiSDmaxbdisc"                   , & JetPuppiSDmaxbdisc                ,    "JetPuppiSDmaxbdisc/F"                     );                                            
  TreeSemiLept->Branch("JetPuppiSDmaxbdiscflavHadron"         , & JetPuppiSDmaxbdiscflavHadron      ,    "JetPuppiSDmaxbdiscflavHadron/F"           );                                                
  TreeSemiLept->Branch("JetPuppiSDmaxbdiscflavParton"         , & JetPuppiSDmaxbdiscflavParton      ,    "JetPuppiSDmaxbdiscflavParton/F"           );                                                
  TreeSemiLept->Branch("JetPuppiSDsubjet0pt"                  , & JetPuppiSDsubjet0pt               ,    "JetPuppiSDsubjet0pt/F"                    );    
  TreeSemiLept->Branch("JetPuppiSDsubjet0mass"                , & JetPuppiSDsubjet0mass             ,    "JetPuppiSDsubjet0mass/F"                  );
  TreeSemiLept->Branch("JetPuppiSDsubjet0eta"                 , & JetPuppiSDsubjet0eta              ,    "JetPuppiSDsubjet0eta/F"                   );
  TreeSemiLept->Branch("JetPuppiSDsubjet0phi"                 , & JetPuppiSDsubjet0phi              ,    "JetPuppiSDsubjet0phi/F"                   );
  TreeSemiLept->Branch("JetPuppiSDsubjet0area"                , & JetPuppiSDsubjet0area             ,    "JetPuppiSDsubjet0area/F"                  );
  TreeSemiLept->Branch("JetPuppiSDsubjet0flavHadron"          , & JetPuppiSDsubjet0flavHadron       ,    "JetPuppiSDsubjet0flavHadron/F"            );
  TreeSemiLept->Branch("JetPuppiSDsubjet0flavParton"          , & JetPuppiSDsubjet0flavParton       ,    "JetPuppiSDsubjet0flavParton/F"            );
  TreeSemiLept->Branch("JetPuppiSDsubjet0tau1"                , & JetPuppiSDsubjet0tau1             ,    "JetPuppiSDsubjet0tau1/F"                  );
  TreeSemiLept->Branch("JetPuppiSDsubjet0tau2"                , & JetPuppiSDsubjet0tau2             ,    "JetPuppiSDsubjet0tau2/F"                  );
  TreeSemiLept->Branch("JetPuppiSDsubjet0tau3"                , & JetPuppiSDsubjet0tau3             ,    "JetPuppiSDsubjet0tau3/F"                  );
  TreeSemiLept->Branch("JetPuppiSDsubjet0bdisc"               , & JetPuppiSDsubjet0bdisc            ,    "JetPuppiSDsubjet0bdisc/F"                 );                                                
  TreeSemiLept->Branch("JetPuppiSDsubjet1pt"                  , & JetPuppiSDsubjet1pt               ,    "JetPuppiSDsubjet1pt/F"                    );    
  TreeSemiLept->Branch("JetPuppiSDsubjet1mass"                , & JetPuppiSDsubjet1mass             ,    "JetPuppiSDsubjet1mass/F"                  );
  TreeSemiLept->Branch("JetPuppiSDsubjet1eta"                 , & JetPuppiSDsubjet1eta              ,    "JetPuppiSDsubjet1eta/F"                   );
  TreeSemiLept->Branch("JetPuppiSDsubjet1phi"                 , & JetPuppiSDsubjet1phi              ,    "JetPuppiSDsubjet1phi/F"                   );  
  TreeSemiLept->Branch("JetPuppiSDsubjet1area"                , & JetPuppiSDsubjet1area             ,    "JetPuppiSDsubjet1area/F"                  );
  TreeSemiLept->Branch("JetPuppiSDsubjet1flavHadron"          , & JetPuppiSDsubjet1flavHadron       ,    "JetPuppiSDsubjet1flavHadron/F"            );
  TreeSemiLept->Branch("JetPuppiSDsubjet1flavParton"          , & JetPuppiSDsubjet1flavParton       ,    "JetPuppiSDsubjet1flavParton/F"            );
  TreeSemiLept->Branch("JetPuppiSDsubjet1tau1"                , & JetPuppiSDsubjet1tau1             ,    "JetPuppiSDsubjet1tau1/F"                  );
  TreeSemiLept->Branch("JetPuppiSDsubjet1tau2"                , & JetPuppiSDsubjet1tau2             ,    "JetPuppiSDsubjet1tau2/F"                  );
  TreeSemiLept->Branch("JetPuppiSDsubjet1tau3"                , & JetPuppiSDsubjet1tau3             ,    "JetPuppiSDsubjet1tau3/F"                  );  
  TreeSemiLept->Branch("JetPuppiSDsubjet1bdisc"               , & JetPuppiSDsubjet1bdisc            ,    "JetPuppiSDsubjet1bdisc/F"                 );                                                                                                                        
  std::cout<<"Setup semi-lept puppi subjet"<<std::endl;


  TreeSemiLept->Branch("JetCHF"                               , & JetCHF                            ,    "JetCHF/F"                                 );                                
  TreeSemiLept->Branch("JetNHF"                               , & JetNHF                            ,    "JetNHF/F"                                 );                                
  TreeSemiLept->Branch("JetCM"                                , & JetCM                             ,    "JetCM/F"                                  );                               
  TreeSemiLept->Branch("JetNM"                                , & JetNM                             ,    "JetNM/F"                                  );                               
  TreeSemiLept->Branch("JetNEF"                               , & JetNEF                            ,    "JetNEF/F"                                 );                                
  TreeSemiLept->Branch("JetCEF"                               , & JetCEF                            ,    "JetCEF/F"                                 );                                
  TreeSemiLept->Branch("JetMF"                                , & JetMF                             ,    "JetMF/F"                                  );                               
  TreeSemiLept->Branch("JetMult"                              , & JetMult                           ,    "JetMult/F"                                );                                 
  TreeSemiLept->Branch("JetMassCorrFactor"                    , & JetMassCorrFactor                 ,    "JetMassCorrFactor/F"                      );                                           
  TreeSemiLept->Branch("JetMassCorrFactorUp"                  , & JetMassCorrFactorUp               ,    "JetMassCorrFactorUp/F"                    );                                             
  TreeSemiLept->Branch("JetMassCorrFactorDn"                  , & JetMassCorrFactorDn               ,    "JetMassCorrFactorDn/F"                    );                                             
  TreeSemiLept->Branch("JetCorrFactor"                        , & JetCorrFactor                     ,    "JetCorrFactor/F"                          );                                       
  TreeSemiLept->Branch("JetCorrFactorUp"                      , & JetCorrFactorUp                   ,    "JetCorrFactorUp/F"                        );                                         
  TreeSemiLept->Branch("JetCorrFactorDn"                      , & JetCorrFactorDn                   ,    "JetCorrFactorDn/F"                        );                                         
  TreeSemiLept->Branch("JetPtSmearFactor"                     , & JetPtSmearFactor                  ,    "JetPtSmearFactor/F"                       );                                          
  TreeSemiLept->Branch("JetPtSmearFactorUp"                   , & JetPtSmearFactorUp                ,    "JetPtSmearFactorUp/F"                     );                                            
  TreeSemiLept->Branch("JetPtSmearFactorDn"                   , & JetPtSmearFactorDn                ,    "JetPtSmearFactorDn/F"                     );                                            
  TreeSemiLept->Branch("JetPuppiMassCorrFactor"               , & JetPuppiMassCorrFactor            ,    "JetPuppiMassCorrFactor/F"                 );                                                
  TreeSemiLept->Branch("JetPuppiMassCorrFactorUp"             , & JetPuppiMassCorrFactorUp          ,    "JetPuppiMassCorrFactorUp/F"               );                                                  
  TreeSemiLept->Branch("JetPuppiMassCorrFactorDn"             , & JetPuppiMassCorrFactorDn          ,    "JetPuppiMassCorrFactorDn/F"               );                                                  
  TreeSemiLept->Branch("JetPuppiCorrFactor"                   , & JetPuppiCorrFactor                ,    "JetPuppiCorrFactor/F"                     );                                            
  TreeSemiLept->Branch("JetPuppiCorrFactorUp"                 , & JetPuppiCorrFactorUp              ,    "JetPuppiCorrFactorUp/F"                   );                                              
  TreeSemiLept->Branch("JetPuppiCorrFactorDn"                 , & JetPuppiCorrFactorDn              ,    "JetPuppiCorrFactorDn/F"                   );                                              
  TreeSemiLept->Branch("JetPuppiPtSmearFactor"                , & JetPuppiPtSmearFactor             ,    "JetPuppiPtSmearFactor/F"                  );                                               
  TreeSemiLept->Branch("JetPuppiPtSmearFactorUp"              , & JetPuppiPtSmearFactorUp           ,    "JetPuppiPtSmearFactorUp/F"                );                                                 
  TreeSemiLept->Branch("JetPuppiPtSmearFactorDn"              , & JetPuppiPtSmearFactorDn           ,    "JetPuppiPtSmearFactorDn/F"                );                                                 
  TreeSemiLept->Branch("JetEtaScaleFactor"                    , & JetEtaScaleFactor                 ,    "JetEtaScaleFactor/F"                      );                                           
  TreeSemiLept->Branch("JetPhiScaleFactor"                    , & JetPhiScaleFactor                 ,    "JetPhiScaleFactor/F"                      );                                           
  TreeSemiLept->Branch("JetMatchedGenJetDR"                   , & JetMatchedGenJetDR                ,    "JetMatchedGenJetDR/F"                     );                                            
  TreeSemiLept->Branch("JetMatchedGenJetPt"                   , & JetMatchedGenJetPt                ,    "JetMatchedGenJetPt/F"                     );                                            
  TreeSemiLept->Branch("JetMatchedGenJetMass"                 , & JetMatchedGenJetMass              ,    "JetMatchedGenJetMass/F"                   ); 
                        
  TreeSemiLept->Branch("JetGenMatched_TopHadronic"            , & JetGenMatched_TopHadronic         ,    "JetGenMatched_TopHadronic/I"              );      
  TreeSemiLept->Branch("JetGenMatched_TopPt"                  , & JetGenMatched_TopPt               ,    "JetGenMatched_TopPt/F"                    );      
  TreeSemiLept->Branch("JetGenMatched_TopEta"                 , & JetGenMatched_TopEta              ,    "JetGenMatched_TopEta/F"                   );      
  TreeSemiLept->Branch("JetGenMatched_TopPhi"                 , & JetGenMatched_TopPhi              ,    "JetGenMatched_TopPhi/F"                   );      
  TreeSemiLept->Branch("JetGenMatched_TopMass"                , & JetGenMatched_TopMass             ,    "JetGenMatched_TopMass/F"                  );      
  TreeSemiLept->Branch("JetGenMatched_bPt"                    , & JetGenMatched_bPt                 ,    "JetGenMatched_bPt/F"                      );      
  TreeSemiLept->Branch("JetGenMatched_WPt"                    , & JetGenMatched_WPt                 ,    "JetGenMatched_WPt/F"                      );      
  TreeSemiLept->Branch("JetGenMatched_Wd1Pt"                  , & JetGenMatched_Wd1Pt               ,    "JetGenMatched_Wd1Pt/F"                    );      
  TreeSemiLept->Branch("JetGenMatched_Wd2Pt"                  , & JetGenMatched_Wd2Pt               ,    "JetGenMatched_Wd2Pt/F"                    );      
  TreeSemiLept->Branch("JetGenMatched_Wd1ID"                  , & JetGenMatched_Wd1ID               ,    "JetGenMatched_Wd1ID/F"                    );      
  TreeSemiLept->Branch("JetGenMatched_Wd2ID"                  , & JetGenMatched_Wd2ID               ,    "JetGenMatched_Wd2ID/F"                    );      
  TreeSemiLept->Branch("JetGenMatched_MaxDeltaRPartonTop"     , & JetGenMatched_MaxDeltaRPartonTop  ,    "JetGenMatched_MaxDeltaRPartonTop/F"       );      
  TreeSemiLept->Branch("JetGenMatched_MaxDeltaRWPartonTop"    , & JetGenMatched_MaxDeltaRWPartonTop ,    "JetGenMatched_MaxDeltaRWPartonTop/F"      );      
  TreeSemiLept->Branch("JetGenMatched_MaxDeltaRWPartonW"      , & JetGenMatched_MaxDeltaRWPartonW   ,    "JetGenMatched_MaxDeltaRWPartonW/F"        );      
  TreeSemiLept->Branch("JetGenMatched_DeltaR_t_b"             , & JetGenMatched_DeltaR_t_b          ,    "JetGenMatched_DeltaR_t_b/F"               );      
  TreeSemiLept->Branch("JetGenMatched_DeltaR_t_W"             , & JetGenMatched_DeltaR_t_W          ,    "JetGenMatched_DeltaR_t_W/F"               );      
  TreeSemiLept->Branch("JetGenMatched_DeltaR_t_Wd1"           , & JetGenMatched_DeltaR_t_Wd1        ,    "JetGenMatched_DeltaR_t_Wd1/F"             );      
  TreeSemiLept->Branch("JetGenMatched_DeltaR_t_Wd2"           , & JetGenMatched_DeltaR_t_Wd2        ,    "JetGenMatched_DeltaR_t_Wd2/F"             );      
  TreeSemiLept->Branch("JetGenMatched_DeltaR_W_b1"            , & JetGenMatched_DeltaR_W_b1         ,    "JetGenMatched_DeltaR_W_b1/F"              );      
  TreeSemiLept->Branch("JetGenMatched_DeltaR_W_Wd1"           , & JetGenMatched_DeltaR_W_Wd1        ,    "JetGenMatched_DeltaR_W_Wd1/F"             );      
  TreeSemiLept->Branch("JetGenMatched_DeltaR_W_Wd2"           , & JetGenMatched_DeltaR_W_Wd2        ,    "JetGenMatched_DeltaR_W_Wd2/F"             );      
  TreeSemiLept->Branch("JetGenMatched_DeltaR_Wd1_Wd2"         , & JetGenMatched_DeltaR_Wd1_Wd2      ,    "JetGenMatched_DeltaR_Wd1_Wd2/F"           );      
  TreeSemiLept->Branch("JetGenMatched_DeltaR_Wd1_b"           , & JetGenMatched_DeltaR_Wd1_b        ,    "JetGenMatched_DeltaR_Wd1_b/F"             );      
  TreeSemiLept->Branch("JetGenMatched_DeltaR_Wd2_b"           , & JetGenMatched_DeltaR_Wd2_b        ,    "JetGenMatched_DeltaR_Wd2_b/F"             );      
  TreeSemiLept->Branch("JetGenMatched_DeltaR_jet_t"           , & JetGenMatched_DeltaR_jet_t        ,    "JetGenMatched_DeltaR_jet_t/F"             );      
  TreeSemiLept->Branch("JetGenMatched_DeltaR_jet_W"           , & JetGenMatched_DeltaR_jet_W        ,    "JetGenMatched_DeltaR_jet_W/F"             );      
  TreeSemiLept->Branch("JetGenMatched_DeltaR_jet_b"           , & JetGenMatched_DeltaR_jet_b        ,    "JetGenMatched_DeltaR_jet_b/F"             );      
  TreeSemiLept->Branch("JetGenMatched_DeltaR_jet_Wd1"         , & JetGenMatched_DeltaR_jet_Wd1      ,    "JetGenMatched_DeltaR_jet_Wd1/F"           );      
  TreeSemiLept->Branch("JetGenMatched_DeltaR_jet_Wd2"         , & JetGenMatched_DeltaR_jet_Wd2      ,    "JetGenMatched_DeltaR_jet_Wd2/F"           );      
  TreeSemiLept->Branch("JetGenMatched_DeltaR_pup0_b"          , & JetGenMatched_DeltaR_pup0_b       ,    "JetGenMatched_DeltaR_pup0_b/F"            );      
  TreeSemiLept->Branch("JetGenMatched_DeltaR_pup0_Wd1"        , & JetGenMatched_DeltaR_pup0_Wd1     ,    "JetGenMatched_DeltaR_pup0_Wd1/F"          );      
  TreeSemiLept->Branch("JetGenMatched_DeltaR_pup0_Wd2"        , & JetGenMatched_DeltaR_pup0_Wd2     ,    "JetGenMatched_DeltaR_pup0_Wd2/F"          );      
  TreeSemiLept->Branch("JetGenMatched_DeltaR_pup1_b"          , & JetGenMatched_DeltaR_pup1_b       ,    "JetGenMatched_DeltaR_pup1_b/F"            );      
  TreeSemiLept->Branch("JetGenMatched_DeltaR_pup1_Wd1"        , & JetGenMatched_DeltaR_pup1_Wd1     ,    "JetGenMatched_DeltaR_pup1_Wd1/F"          );      
  TreeSemiLept->Branch("JetGenMatched_DeltaR_pup1_Wd2"        , & JetGenMatched_DeltaR_pup1_Wd2     ,    "JetGenMatched_DeltaR_pup1_Wd2/F"          );               
  TreeSemiLept->Branch("JetGenMatched_partonPt"               , & JetGenMatched_partonPt            ,    "JetGenMatched_partonPt/F"                 );      
  TreeSemiLept->Branch("JetGenMatched_partonEta"              , & JetGenMatched_partonEta           ,    "JetGenMatched_partonEta/F"                );      
  TreeSemiLept->Branch("JetGenMatched_partonPhi"              , & JetGenMatched_partonPhi           ,    "JetGenMatched_partonPhi/F"                );      
  TreeSemiLept->Branch("JetGenMatched_partonMass"             , & JetGenMatched_partonMass          ,    "JetGenMatched_partonMass/F"               );      
  TreeSemiLept->Branch("JetGenMatched_partonID"               , & JetGenMatched_partonID            ,    "JetGenMatched_partonID/F"                 );      
  TreeSemiLept->Branch("JetGenMatched_DeltaRjetParton"        , & JetGenMatched_DeltaRjetParton     ,    "JetGenMatched_DeltaRjetParton/F"          );      
  std::cout<<"Setup semi-lept jets"<<std::endl;


  TreeSemiLept->Branch("SemiLeptMETpx"                        , & SemiLeptMETpx                     , "SemiLeptMETpx/F"                  );
  TreeSemiLept->Branch("SemiLeptMETpy"                        , & SemiLeptMETpy                     , "SemiLeptMETpy/F"                  );
  TreeSemiLept->Branch("SemiLeptMETpt"                        , & SemiLeptMETpt                     , "SemiLeptMETpt/F"                  );
  TreeSemiLept->Branch("SemiLeptMETphi"                       , & SemiLeptMETphi                    , "SemiLeptMETphi/F"                 );
  TreeSemiLept->Branch("SemiLeptMETsumET"                     , & SemiLeptMETsumET                  , "SemiLeptMETsumET/F"               );
  TreeSemiLept->Branch("SemiLeptNvtx"                         , & SemiLeptNvtx                      , "SemiLeptNvtx/F"                   );
  TreeSemiLept->Branch("SemiLeptRho"                          , & SemiLeptRho                       , "SemiLeptRho/F"                    );
  TreeSemiLept->Branch("SemiLeptEventWeight"                  , & SemiLeptEventWeight               , "SemiLeptEventWeight/F"            );

  TreeSemiLept->Branch("SemiLeptGenTTmass"                    , & SemiLeptGenTTmass                 , "SemiLeptGenTTmass/F"              );
  TreeSemiLept->Branch("SemiLeptHT"                           , & SemiLeptHT                        , "SemiLeptHT/F"                     );
  TreeSemiLept->Branch("SemiLeptHT_CorrDn"                    , & SemiLeptHT_CorrDn                 , "SemiLeptHT_CorrDn/F"              );
  TreeSemiLept->Branch("SemiLeptHT_CorrUp"                    , & SemiLeptHT_CorrUp                 , "SemiLeptHT_CorrUp/F"              );
  TreeSemiLept->Branch("SemiLeptHT_PtSmearUp"                 , & SemiLeptHT_PtSmearUp              , "SemiLeptHT_PtSmearUp/F"           );
  TreeSemiLept->Branch("SemiLeptHT_PtSmearDn"                 , & SemiLeptHT_PtSmearDn              , "SemiLeptHT_PtSmearDn/F"           );
  TreeSemiLept->Branch("SemiLeptQ2weight_CorrDn"              , & SemiLeptQ2weight_CorrDn           , "SemiLeptQ2weight_CorrDn/F"        );
  TreeSemiLept->Branch("SemiLeptQ2weight_CorrUp"              , & SemiLeptQ2weight_CorrUp           , "SemiLeptQ2weight_CorrUp/F"        );
  TreeSemiLept->Branch("SemiLeptNNPDF3weight_CorrDn"          , & SemiLeptNNPDF3weight_CorrDn       , "SemiLeptNNPDF3weight_CorrDn/F"    );
  TreeSemiLept->Branch("SemiLeptNNPDF3weight_CorrUp"          , & SemiLeptNNPDF3weight_CorrUp       , "SemiLeptNNPDF3weight_CorrUp/F"    );
  TreeSemiLept->Branch("SemiLeptRunNum"                       , & SemiLeptRunNum                    , "SemiLeptRunNum/F"                 );
  TreeSemiLept->Branch("SemiLeptLumiBlock"                    , & SemiLeptLumiBlock                 , "SemiLeptLumiBlock/F"              );
  TreeSemiLept->Branch("SemiLeptEventNum"                     , & SemiLeptEventNum                  , "SemiLeptEventNum/F"               );
  TreeSemiLept->Branch("SemiLeptPassMETFilters"               , & SemiLeptPassMETFilters            , "SemiLeptPassMETFilters/F"         );
 
  TreeSemiLept->Branch("AK4dRminPt"                           , & AK4dRminPt                        , "AK4dRminPt/F"                     );  
  TreeSemiLept->Branch("AK4dRminEta"                          , & AK4dRminEta                       , "AK4dRminEta/F"                    );  
  TreeSemiLept->Branch("AK4dRminPhi"                          , & AK4dRminPhi                       , "AK4dRminPhi/F"                    );  
  TreeSemiLept->Branch("AK4dRminBdisc"                        , & AK4dRminBdisc                     , "AK4dRminBdisc/F"                  );  
  TreeSemiLept->Branch("AK4BtagdRminPt"                       , & AK4BtagdRminPt                    , "AK4BtagdRminPt/F"                 );  
  TreeSemiLept->Branch("AK4BtagdRminBdisc"                    , & AK4BtagdRminBdisc                 , "AK4BtagdRminBdisc/F"              );  
  TreeSemiLept->Branch("AK4BtaggedLoose"                      , & AK4BtaggedLoose                   , "AK4BtaggedLoose/I"                );  
  TreeSemiLept->Branch("AK4BtaggedMedium"                     , & AK4BtaggedMedium                  , "AK4BtaggedMedium/I"               );  
  TreeSemiLept->Branch("AK4BtaggedTight"                      , & AK4BtaggedTight                   , "AK4BtaggedTight/I"                );  



  TreeSemiLept->Branch("LeptonPhi"                            , &  LeptonPhi                        , "LeptonPhi/F"                          ); 
  TreeSemiLept->Branch("LeptonPt"                             , &  LeptonPt                         , "LeptonPt/F"                           ); 
  TreeSemiLept->Branch("LeptonEta"                            , &  LeptonEta                        , "LeptonEta/F"                          ); 
  TreeSemiLept->Branch("LeptonMass"                           , &  LeptonMass                       , "LeptonMass/F"                         ); 
  TreeSemiLept->Branch("LeptonIsMu"                           , &  LeptonIsMu                       , "LeptonIsMu/I"                         ); 
  TreeSemiLept->Branch("MuTight"                              , &  MuTight                          , "MuTight/I"                        ); 
  TreeSemiLept->Branch("DeltaRJetLep"                         , &  DeltaRJetLep                     , "DeltaRJetLep/F"                   ); 
  TreeSemiLept->Branch("DeltaPhiJetLep"                       , &  DeltaPhiJetLep                   , "DeltaPhiJetLep/F"                 ); 
  std::cout<<"Setup semi-lept tree"<<std::endl;

  std::cout<<"Finished constructor"<<std::endl;

}


B2GTTbarTreeMaker::~B2GTTbarTreeMaker()
{
}


//
// member functions
//

// ------------ method called for each event  ------------
void
B2GTTbarTreeMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  using namespace reco;
  using namespace pat;

  //
  //    .d8888b.  8888888888 888b    888     8888888b.                   888    d8b          888                   
  //   d88P  Y88b 888        8888b   888     888   Y88b                  888    Y8P          888                   
  //   888    888 888        88888b  888     888    888                  888                 888                   
  //   888        8888888    888Y88b 888     888   d88P  8888b.  888d888 888888 888  .d8888b 888  .d88b.  .d8888b  
  //   888  88888 888        888 Y88b888     8888888P"      "88b 888P"   888    888 d88P"    888 d8P  Y8b 88K      
  //   888    888 888        888  Y88888     888        .d888888 888     888    888 888      888 88888888 "Y8888b. 
  //   Y88b  d88P 888        888   Y8888     888        888  888 888     Y88b.  888 Y88b.    888 Y8b.          X88 
  //    "Y8888P88 8888888888 888    Y888     888        "Y888888 888      "Y888 888  "Y8888P 888  "Y8888   88888P' 
  //                                                                                                               
                                                                                                                                                                                                                        
  bool top1hadronic=false;
  bool top2hadronic=false;
  bool top1leptonic=false;
  bool top2leptonic=false;

  TLorentzVector t1_p4;
  TLorentzVector t2_p4;
  TLorentzVector finalt1_p4;
  TLorentzVector finalt2_p4;
  TLorentzVector b1_p4;
  TLorentzVector b2_p4;
  TLorentzVector W1_p4;
  TLorentzVector W2_p4;
  TLorentzVector W1d1_p4;
  TLorentzVector W1d2_p4;
  TLorentzVector W2d1_p4;
  TLorentzVector W2d2_p4;
  TLorentzVector resonantW1_p4;
  TLorentzVector resonantW2_p4;
  TLorentzVector Resonance_p4;
  TLorentzVector hardest_parton_hardScatterOutgoing_p4;
  TLorentzVector second_hardest_parton_hardScatterOutgoing_p4;

  double hardest_parton_hardScatterOutgoing_pt        = 0;
  double second_hardest_parton_hardScatterOutgoing_pt = 0;

  int parton1id = 0;
  int parton2id = 0;

  int W1d1_id = 0 ;
  int W1d2_id = 0 ;
  int W2d1_id = 0 ;
  int W2d2_id = 0 ;

  bool GenTruth_allhadronic = false;
  bool GenTruth_semileptonic = false;

  double deltaR_t1_t2       = 99 ;
  double deltaR_t1_b1       = 99 ;
  double deltaR_t1_W1       = 99 ;
  double deltaR_t1_W1d1     = 99 ;
  double deltaR_t1_W1d2     = 99 ;
  double deltaR_W1_b1       = 99 ;
  double deltaR_W1_W1d1     = 99 ;
  double deltaR_W1_W1d2     = 99 ;
  double deltaR_W1d1_W1d2   = 99 ;
  double deltaR_W1d1_b1     = 99 ;
  double deltaR_W1d2_b1     = 99 ;
  double deltaR_t2_b2       = 99 ;
  double deltaR_t2_W2       = 99 ;
  double deltaR_t2_W2d1     = 99 ;
  double deltaR_t2_W2d2     = 99 ;
  double deltaR_W2_b2       = 99 ;
  double deltaR_W2_W2d1     = 99 ;
  double deltaR_W2_W2d2     = 99 ;
  double deltaR_W2d1_W2d2   = 99 ;
  double deltaR_W2d1_b2     = 99 ;
  double deltaR_W2d2_b2     = 99 ;

  double max_deltaR_parton_t1 = -1;
  double max_deltaR_parton_t2 = -1;
  double max_deltaR_Wparton_t1 = -1;
  double max_deltaR_Wparton_t2 = -1;
  double max_deltaR_Wparton_W1 = -1;
  double max_deltaR_Wparton_W2 = -1;

  double counttop = 0;
  if (!iEvent.isRealData() and runGenLoop_) {
    Handle<edm::View<reco::GenParticle> > genpart;
    iEvent.getByToken(prunedGenToken_,genpart);  

    // Classify the event based on the number of top quarks
    for(size_t i=0; i<genpart->size();i++){
    if (fabs((*genpart)[i].pdgId())==6 && (*genpart)[i].status()<30 && (*genpart)[i].status()>=20) counttop++;  // Z' events: status 22 = top from Z', status 52 with 2 daughters = the top that decays (after radiating a bunch of times)
    }
    if (verboseGen_) cout<<"counttop "<<counttop<<endl;
   
    // Loop over all pruned gen particles and find the 4-vectors of the top, W, B, W duaghters
    double countW = 0;
    double countb = 0;
    for(size_t i=0; i<genpart->size();i++){
      int id        = (*genpart)[i].pdgId();
      int status    = (*genpart)[i].status();
      int ndau      = (*genpart)[i].numberOfDaughters();
      double px     = (*genpart)[i].px();
      double py     = (*genpart)[i].py();
      double pz     = (*genpart)[i].pz();
      double e      = (*genpart)[i].energy();
      double m      = (*genpart)[i].mass();
      double pt     = (*genpart)[i].pt();
      double eta    = (*genpart)[i].eta();
      double phi    = (*genpart)[i].phi();
      //double nmothers = (*genpart)[i].numberOfMothers() ;

      // Find the particles from the hard scatter (for QCD samples)
      if (status==23 && counttop==0){
        if (pt>hardest_parton_hardScatterOutgoing_pt){
          second_hardest_parton_hardScatterOutgoing_pt = hardest_parton_hardScatterOutgoing_pt;
          second_hardest_parton_hardScatterOutgoing_p4 = hardest_parton_hardScatterOutgoing_p4;
          hardest_parton_hardScatterOutgoing_pt = pt;
          hardest_parton_hardScatterOutgoing_p4.SetPxPyPzE( px, py, pz, e );
          parton1id = id;
          if (verboseGen_) cout<<"---------- pt>hardest_parton_hardScatterOutgoing_pt - parton1id = "<<parton1id<<endl;
        }
        else if (pt>second_hardest_parton_hardScatterOutgoing_pt){
          second_hardest_parton_hardScatterOutgoing_pt = pt;
          second_hardest_parton_hardScatterOutgoing_p4.SetPxPyPzE( px, py, pz, e ); 
          parton2id = id;
          if (verboseGen_) cout<<"---------- pt>second_hardest_parton_hardScatterOutgoing_pt - parton2id = "<<parton2id<<endl;
        }
      }
      // Find the the resonance mass for Z'
      if (id>1000000 && status == 22) 
      {
        Resonance_p4.SetPxPyPzE( px, py, pz, e ); 
        if (verboseGen_) cout<<".Resonant particle with mass "<<m<<endl; // RSGWW id = 5100039, Z' id = 6000047
      }
      // Get tops from hard subprocess (for ttbar samples)
      if (id==6 && status<30 && status>=20) {
        t1_p4.SetPxPyPzE( px, py, pz, e ); 
        parton1id = id;
        if (verboseGen_) cout<<"..top (hard)"<<endl;//" with pt "<<pt<<" status "<<status<<" ndau "<< ndau <<" pt "<<pt<<" eta "<<eta<<" phi "<<phi<<" parton1id = "<<parton1id<<endl;
      }
      if (id==-6 && status<30 && status>=20) {
        t2_p4.SetPxPyPzE( px, py, pz, e ); 
        parton2id = id;
        if (verboseGen_) cout<<"..atop (hard)"<<endl;//" with pt "<<pt<<" status "<<status<<" ndau "<< ndau <<" pt "<<pt<<" eta "<<eta<<" phi "<<phi<<" parton2id = "<<parton2id<<endl;
      }

      // Get the tops which decay - record b and W information
      if (ndau==2 && id==6){
        finalt1_p4.SetPxPyPzE( px, py, pz, e ); 
        if (verboseGen_) cout<<"....two daughters top pt "<<pt<<" status "<<status<<" ndau "<< ndau <<" pt "<<pt<<" eta "<<eta<<" phi "<<phi<<endl;
        for (int daught =0; daught<2; daught++)
        {
          if ( fabs((*genpart)[i].daughter( daught )->pdgId())==5 )  b1_p4.SetPxPyPzE( (*genpart)[i].daughter( daught )->px(), (*genpart)[i].daughter( daught )->py(), (*genpart)[i].daughter( daught )->pz(), (*genpart)[i].daughter( daught )->energy() );
          if ( fabs((*genpart)[i].daughter( daught )->pdgId())==24 ) W1_p4.SetPxPyPzE( (*genpart)[i].daughter( daught )->px(), (*genpart)[i].daughter( daught )->py(), (*genpart)[i].daughter( daught )->pz(), (*genpart)[i].daughter( daught )->energy() );
          if (verboseGen_) cout<<"......top daughter ID "<< (*genpart)[i].daughter( daught )->pdgId() <<" pt "<< (*genpart)[i].daughter( daught )->pt()  <<endl;
        }
      }
      if (ndau==2 && id==-6){
        finalt2_p4.SetPxPyPzE( px, py, pz, e ); 
        if (verboseGen_) cout<<"....two daughters atop pt "<<pt<<" status "<<status<<" ndau "<< ndau <<" pt "<<pt<<" eta "<<eta<<" phi "<<phi<<endl;
        for (int daught =0; daught<2; daught++)
        {
          if ( fabs((*genpart)[i].daughter( daught )->pdgId())==5 )  b2_p4.SetPxPyPzE( (*genpart)[i].daughter( daught )->px(), (*genpart)[i].daughter( daught )->py(), (*genpart)[i].daughter( daught )->pz(), (*genpart)[i].daughter( daught )->energy() );
          if ( fabs((*genpart)[i].daughter( daught )->pdgId())==24 ) W2_p4.SetPxPyPzE( (*genpart)[i].daughter( daught )->px(), (*genpart)[i].daughter( daught )->py(), (*genpart)[i].daughter( daught )->pz(), (*genpart)[i].daughter( daught )->energy() );
          if (verboseGen_) cout<<"......atop daughter ID "<< (*genpart)[i].daughter( daught )->pdgId() <<" pt "<< (*genpart)[i].daughter( daught )->pt()  <<endl;
        }
      }

      // Get the Ws which decay - record their daughter information
      if (ndau==2 && id==24){
        if (verboseGen_) cout<<"....W+ with 2 daughters  id "<<id<<" status "<<status<<" ndau "<<ndau<<" pt "<<pt<<" eta "<<eta<<" phi "<<phi<<endl;
        if (verboseGen_) cout<<"......dd0 "<<(*genpart)[i].daughter( 0 )->pdgId()<<" ndau "<<(*genpart)[i].daughter( 0 )->numberOfDaughters()<<endl;
        if (verboseGen_) cout<<"......dd1 "<<(*genpart)[i].daughter( 1 )->pdgId()<<" ndau "<<(*genpart)[i].daughter( 1 )->numberOfDaughters()<<endl;
        W1d1_p4.SetPxPyPzE( (*genpart)[i].daughter( 0 )->px(), (*genpart)[i].daughter( 0 )->py(), (*genpart)[i].daughter( 0 )->pz(), (*genpart)[i].daughter( 0 )->energy() );
        W1d2_p4.SetPxPyPzE( (*genpart)[i].daughter( 1 )->px(), (*genpart)[i].daughter( 1 )->py(), (*genpart)[i].daughter( 1 )->pz(), (*genpart)[i].daughter( 1 )->energy() );
        if ( fabs( (*genpart)[i].daughter( 0 )->pdgId() ) < 6 && fabs( (*genpart)[i].daughter( 1 )->pdgId() ) < 6) top1hadronic = true;  
        if ( fabs( (*genpart)[i].daughter( 0 )->pdgId() ) <= 18 && fabs( (*genpart)[i].daughter( 0 )->pdgId() ) >= 11) top1leptonic = true;  
        W1d1_id = (*genpart)[i].daughter( 0 )->pdgId();
        W1d2_id = (*genpart)[i].daughter( 1 )->pdgId();
      }
      if (ndau==2 && id==-24){
        if (verboseGen_) cout<<"....W- with 2 daughters  id "<<id<<" status "<<status<<" ndau "<<ndau<<" pt "<<pt<<" eta "<<eta<<" phi "<<phi<<endl;
        if (verboseGen_) cout<<"......dd0 "<<(*genpart)[i].daughter( 0 )->pdgId()<<" ndau "<<(*genpart)[i].daughter( 0 )->numberOfDaughters()<<endl;
        if (verboseGen_) cout<<"......dd1 "<<(*genpart)[i].daughter( 1 )->pdgId()<<" ndau "<<(*genpart)[i].daughter( 1 )->numberOfDaughters()<<endl;
        W2d1_p4.SetPxPyPzE( (*genpart)[i].daughter( 0 )->px(), (*genpart)[i].daughter( 0 )->py(), (*genpart)[i].daughter( 0 )->pz(), (*genpart)[i].daughter( 0 )->energy() );
        W2d2_p4.SetPxPyPzE( (*genpart)[i].daughter( 1 )->px(), (*genpart)[i].daughter( 1 )->py(), (*genpart)[i].daughter( 1 )->pz(), (*genpart)[i].daughter( 1 )->energy() );
        if ( fabs( (*genpart)[i].daughter( 0 )->pdgId() ) < 6 && fabs( (*genpart)[i].daughter( 1 )->pdgId() ) < 6) top2hadronic = true;  
        if ( fabs( (*genpart)[i].daughter( 0 )->pdgId() ) <= 18 && fabs( (*genpart)[i].daughter( 0 )->pdgId() ) >= 11) top2leptonic = true;  
        W2d1_id = (*genpart)[i].daughter( 0 )->pdgId();
        W2d2_id = (*genpart)[i].daughter( 1 )->pdgId();
      }
    } // end genParticle loop

    // Generator truth all-hadronic or semileptonic
    if (top1hadronic && top2hadronic)  GenTruth_allhadronic = true;
    if (top1hadronic && !top2hadronic) GenTruth_semileptonic = true;
    if (!top1hadronic && top2hadronic) GenTruth_semileptonic = true;

    // Angles between particles
    deltaR_t1_t2       = t1_p4  .DeltaR(t2_p4  );
    deltaR_t1_b1       = t1_p4  .DeltaR(b1_p4  );
    deltaR_t1_W1       = t1_p4  .DeltaR(W1_p4  );
    deltaR_t1_W1d1     = t1_p4  .DeltaR(W1d1_p4);
    deltaR_t1_W1d2     = t1_p4  .DeltaR(W1d2_p4);
    deltaR_W1_b1       = W1_p4  .DeltaR(b1_p4  );
    deltaR_W1_W1d1     = W1_p4  .DeltaR(W1d1_p4);
    deltaR_W1_W1d2     = W1_p4  .DeltaR(W1d2_p4);
    deltaR_W1d1_W1d2   = W1d1_p4.DeltaR(W1d2_p4);
    deltaR_W1d1_b1     = W1d1_p4.DeltaR(b1_p4  );
    deltaR_W1d2_b1     = W1d2_p4.DeltaR(b1_p4  );
    deltaR_t2_b2       = t2_p4  .DeltaR(b2_p4  );
    deltaR_t2_W2       = t2_p4  .DeltaR(W2_p4  );
    deltaR_t2_W2d1     = t2_p4  .DeltaR(W2d1_p4);
    deltaR_t2_W2d2     = t2_p4  .DeltaR(W2d2_p4);
    deltaR_W2_b2       = W2_p4  .DeltaR(b2_p4  );
    deltaR_W2_W2d1     = W2_p4  .DeltaR(W2d1_p4);
    deltaR_W2_W2d2     = W2_p4  .DeltaR(W2d2_p4);
    deltaR_W2d1_W2d2   = W2d1_p4.DeltaR(W2d2_p4);
    deltaR_W2d1_b2     = W2d1_p4.DeltaR(b2_p4  );
    deltaR_W2d2_b2     = W2d2_p4.DeltaR(b2_p4  );

    // Find top decay products which have the farthest angle from the top and from the W
    // max parton deltaR from t1
    if ( deltaR_t1_b1   > max_deltaR_parton_t1 ) max_deltaR_parton_t1 = deltaR_t1_b1  ;
    if ( deltaR_t1_W1d1 > max_deltaR_parton_t1 ) max_deltaR_parton_t1 = deltaR_t1_W1d1;
    if ( deltaR_t1_W1d2 > max_deltaR_parton_t1 ) max_deltaR_parton_t1 = deltaR_t1_W1d2;

    // max parton deltaR from t2
    if ( deltaR_t2_b2   > max_deltaR_parton_t2 ) max_deltaR_parton_t2 = deltaR_t2_b2  ;
    if ( deltaR_t2_W2d1 > max_deltaR_parton_t2 ) max_deltaR_parton_t2 = deltaR_t2_W2d1;
    if ( deltaR_t2_W2d2 > max_deltaR_parton_t2 ) max_deltaR_parton_t2 = deltaR_t2_W2d2;

    // max W parton deltaR from t1
    if ( deltaR_t1_W1d1 > max_deltaR_Wparton_t1 ) max_deltaR_Wparton_t1 = deltaR_t1_W1d1;
    if ( deltaR_t1_W1d2 > max_deltaR_Wparton_t1 ) max_deltaR_Wparton_t1 = deltaR_t1_W1d2;

    // max W parton deltaR from t2
    if ( deltaR_t2_W2d1 > max_deltaR_Wparton_t2 ) max_deltaR_Wparton_t2 = deltaR_t2_W2d1;
    if ( deltaR_t2_W2d2 > max_deltaR_Wparton_t2 ) max_deltaR_Wparton_t2 = deltaR_t2_W2d2;

    // max W parton deltaR from W1
    if ( deltaR_W1_W1d1 > max_deltaR_Wparton_W1 ) max_deltaR_Wparton_W1 = deltaR_W1_W1d1;
    if ( deltaR_W1_W1d2 > max_deltaR_Wparton_W1 ) max_deltaR_Wparton_W1 = deltaR_W1_W1d2;

    // max W parton deltaR from W2
    if ( deltaR_W2_W2d1 > max_deltaR_Wparton_W2 ) max_deltaR_Wparton_W2 = deltaR_W2_W2d1;
    if ( deltaR_W2_W2d2 > max_deltaR_Wparton_W2 ) max_deltaR_Wparton_W2 = deltaR_W2_W2d2;

    if (verboseGen_)
    {
      cout<<"second_hardest_parton_hardScatterOutgoing_pt "<<second_hardest_parton_hardScatterOutgoing_pt      <<endl;                
      cout<<"second_hardest_parton_hardScatterOutgoing_p4pt "<<second_hardest_parton_hardScatterOutgoing_p4.Pt() <<endl;                      
      cout<<"second_hardest_parton_hardScatterOutgoing_eta "<<second_hardest_parton_hardScatterOutgoing_p4.Eta() <<endl;                      
      cout<<"hardest_parton_hardScatterOutgoing_pt        "<<hardest_parton_hardScatterOutgoing_pt             <<endl;  
      cout<<"hardest_parton_hardScatterOutgoing_p4pt        "<<hardest_parton_hardScatterOutgoing_p4.Pt()        <<endl;       
      cout<<"hardest_parton_hardScatterOutgoing_eta        "<<hardest_parton_hardScatterOutgoing_p4.Eta()        <<endl;       
      cout<<"parton1id = "<<parton1id<<endl;
      cout<<"parton2id = "<<parton1id<<endl;

      cout<<"top1hadronic "<<top1hadronic<<endl;
      cout<<"top2hadronic "<<top2hadronic<<endl;
      cout<<"top1leptonic "<<top1leptonic<<endl;
      cout<<"top2leptonic "<<top2leptonic<<endl;
      cout<<"W1d1_id "<<W1d1_id<<endl;
      cout<<"W1d2_id "<<W1d2_id<<endl;
      cout<<"W2d1_id "<<W2d1_id<<endl;
      cout<<"W2d2_id "<<W2d2_id<<endl;

      cout<<"top1hadronic "<<top1hadronic<<endl;
      cout<<"top2hadronic "<<top2hadronic<<endl;
      cout<<"top1leptonic "<<top1leptonic<<endl;
      cout<<"top2leptonic "<<top2leptonic<<endl;
      if (GenTruth_allhadronic)  cout<<"allhadronic"<<endl;
      if (GenTruth_semileptonic) cout<<"semileptonic"<<endl;
    
      cout<<"t1_p4   Pt "<<t1_p4  .Pt()<<" Eta "<<t1_p4  .Eta()<<" Phi "<<t1_p4  .Phi()<<" M "<<t1_p4  .M()<<endl;
      cout<<"t2_p4   Pt "<<t2_p4  .Pt()<<" Eta "<<t2_p4  .Eta()<<" Phi "<<t2_p4  .Phi()<<" M "<<t2_p4  .M()<<endl;
      cout<<"b1_p4   Pt "<<b1_p4  .Pt()<<" Eta "<<b1_p4  .Eta()<<" Phi "<<b1_p4  .Phi()<<" M "<<b1_p4  .M()<<endl;
      cout<<"b2_p4   Pt "<<b2_p4  .Pt()<<" Eta "<<b2_p4  .Eta()<<" Phi "<<b2_p4  .Phi()<<" M "<<b2_p4  .M()<<endl;
      cout<<"W1_p4   Pt "<<W1_p4  .Pt()<<" Eta "<<W1_p4  .Eta()<<" Phi "<<W1_p4  .Phi()<<" M "<<W1_p4  .M()<<endl;
      cout<<"W2_p4   Pt "<<W2_p4  .Pt()<<" Eta "<<W2_p4  .Eta()<<" Phi "<<W2_p4  .Phi()<<" M "<<W2_p4  .M()<<endl;
      cout<<"W1d1_p4 Pt "<<W1d1_p4.Pt()<<" Eta "<<W1d1_p4.Eta()<<" Phi "<<W1d1_p4.Phi()<<" M "<<W1d1_p4.M()<<endl;
      cout<<"W1d2_p4 Pt "<<W1d2_p4.Pt()<<" Eta "<<W1d2_p4.Eta()<<" Phi "<<W1d2_p4.Phi()<<" M "<<W1d2_p4.M()<<endl;
      cout<<"W2d1_p4 Pt "<<W2d1_p4.Pt()<<" Eta "<<W2d1_p4.Eta()<<" Phi "<<W2d1_p4.Phi()<<" M "<<W2d1_p4.M()<<endl;
      cout<<"W2d2_p4 Pt "<<W2d2_p4.Pt()<<" Eta "<<W2d2_p4.Eta()<<" Phi "<<W2d2_p4.Phi()<<" M "<<W2d2_p4.M()<<endl;
      cout<<"resonantW1_p4   Pt "<<resonantW1_p4  .Pt()<<" Eta "<<resonantW1_p4  .Eta()<<" Phi "<<resonantW1_p4  .Phi()<<" M "<<resonantW1_p4  .M()<<endl;
      cout<<"resonantW2_p4   Pt "<<resonantW2_p4  .Pt()<<" Eta "<<resonantW2_p4  .Eta()<<" Phi "<<resonantW2_p4  .Phi()<<" M "<<resonantW2_p4  .M()<<endl;
    
      cout<<"deltaR_t1_t2       "<<deltaR_t1_t2      <<endl;
      cout<<"deltaR_t1_b1       "<<deltaR_t1_b1      <<endl; 
      cout<<"deltaR_t1_W1d1     "<<deltaR_t1_W1d1    <<endl; 
      cout<<"deltaR_t1_W1d2     "<<deltaR_t1_W1d2    <<endl; 
      cout<<"deltaR_t2_b2       "<<deltaR_t2_b2      <<endl; 
      cout<<"deltaR_t2_W2d1     "<<deltaR_t2_W2d1    <<endl; 
      cout<<"deltaR_t2_W2d2     "<<deltaR_t2_W2d2    <<endl; 
      cout<<"max_deltaR_parton_t1 "<<max_deltaR_parton_t1<<endl;
      cout<<"max_deltaR_parton_t2 "<<max_deltaR_parton_t2<<endl;
      cout<<"counttop "<<counttop<<" countW "<<countW<<" countb "<<countb<<endl;
    }
  }
  // 
  // 888b     d888 8888888888 88888888888     888b    888          d8b                       8888888888 d8b 888 888                              
  // 8888b   d8888 888            888         8888b   888          Y8P                       888        Y8P 888 888                              
  // 88888b.d88888 888            888         88888b  888                                    888            888 888                              
  // 888Y88888P888 8888888        888         888Y88b 888  .d88b.  888 .d8888b   .d88b.      8888888    888 888 888888  .d88b.  888d888 .d8888b  
  // 888 Y888P 888 888            888         888 Y88b888 d88""88b 888 88K      d8P  Y8b     888        888 888 888    d8P  Y8b 888P"   88K      
  // 888  Y8P  888 888            888         888  Y88888 888  888 888 "Y8888b. 88888888     888        888 888 888    88888888 888     "Y8888b. 
  // 888   "   888 888            888         888   Y8888 Y88..88P 888      X88 Y8b.         888        888 888 Y88b.  Y8b.     888          X88 
  // 888       888 8888888888     888         888    Y888  "Y88P"  888  88888P'  "Y8888      888        888 888  "Y888  "Y8888  888      88888P' 

  bool passMETfilters=false;
  if ( iEvent.isRealData() ) {
    edm::Handle < edm::TriggerResults > metFilters;
    iEvent.getByToken(triggerResultsMETFilterToken_, metFilters);
    edm::TriggerNames const& filterTriggerNames = iEvent.triggerNames(*metFilters);

    int nMETfilters = metFilters->size();
    if (verbose_) cout<<"nMETfilters "<<nMETfilters<<endl;

    //https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2#MiniAOD_8011_ICHEP_dataset
    // Flag_HBHENoiseFilter TO BE USED
    // Flag_HBHENoiseIsoFilter TO BE USED
    // Flag_EcalDeadCellTriggerPrimitiveFilter TO BE USED
    // Flag_goodVertices TO BE USED
    // Flag_eeBadScFilter TO BE USED
    // Flag_globalTightHalo2016Filter NEW TO BE USED
    // badMuon (NEW not available in 80X miniAOD v2, see snippet below) TO BE USED
    // badCharged hadron (NEW not available in 80X miniAOD v2, see snippet below) TO BE USED 

    vector <string> filterFlags;
    filterFlags.push_back("Flag_HBHENoiseFilter");
    filterFlags.push_back("Flag_HBHENoiseIsoFilter");
    filterFlags.push_back("Flag_EcalDeadCellTriggerPrimitiveFilter");
    filterFlags.push_back("Flag_goodVertices");
    filterFlags.push_back("Flag_eeBadScFilter");
    filterFlags.push_back("Flag_globalTightHalo2016Filter");

    unsigned int count_matched_accept = 0;
    for (int itrig = 0; itrig != nMETfilters; ++itrig){
     std::string trigName = filterTriggerNames.triggerName(itrig);
      bool accept = metFilters->accept(itrig);
      if (verbose_) cout<<trigName<<"  "<<accept;
      if ( std::find( filterFlags.begin(), filterFlags.end(), trigName ) != filterFlags.end() ) {
          if (verbose_) cout<<"  -> matches filterFlags list ("<<trigName<<")"<<endl;
          if (accept) count_matched_accept++;
      }
      else { if (verbose_) cout<<endl;}
    }
    if (verbose_) cout<<"filterFlags.size() "<<filterFlags.size()<<" count_matched_accept "<<count_matched_accept<<endl;
    if ( count_matched_accept==filterFlags.size() ){
      passMETfilters=true;
    }
    if (verbose_) cout<<"miniAOD Flags pass? "<<passMETfilters<<endl;
  }
  else{
    passMETfilters=true;
  }

  // RECO problemes -> apply to both data and MC
  Handle<bool> ifilterbadChCand;
  iEvent.getByToken(badChargedCandidateFilterToken_ , ifilterbadChCand);
  bool  filterbadChCandidate = *ifilterbadChCand;
  if (verbose_) cout <<"filterbadChCandidate "<<filterbadChCandidate<<endl;

  Handle<bool> ifilterbadPFMuon;
  iEvent.getByToken(badMuonFilterToken_, ifilterbadPFMuon);
  bool filterbadPFMuon = *ifilterbadPFMuon;
  if (verbose_) cout <<"filterbadPFMuon "<<filterbadPFMuon<<endl;

  passMETfilters = passMETfilters && filterbadChCandidate && filterbadPFMuon;
  if (verbose_) cout<<"passMETfilters = "<< passMETfilters <<endl;

  //
  //  888888 8888888888  .d8888b.      8888888b.                    888                        888          
  //    "88b 888        d88P  Y88b     888   Y88b                   888                        888          
  //     888 888        888    888     888    888                   888                        888          
  //     888 8888888    888            888   d88P  8888b.  888  888 888  .d88b.   8888b.   .d88888 .d8888b  
  //     888 888        888            8888888P"      "88b 888  888 888 d88""88b     "88b d88" 888 88K      
  //     888 888        888    888     888        .d888888 888  888 888 888  888 .d888888 888  888 "Y8888b. 
  //     88P 888        Y88b  d88P     888        888  888 Y88b 888 888 Y88..88P 888  888 Y88b 888      X88 
  //     888 8888888888  "Y8888P"      888        "Y888888  "Y88888 888  "Y88P"  "Y888888  "Y88888  88888P' 
  //   .d88P                                                    888                                         
  // .d88P"                                                Y8b d88P                                         
  //888P"                                                   "Y88P"                                          
  //

  // AK4chs JEC 
  std::vector<JetCorrectorParameters> vParAK4chs;
   for ( std::vector<std::string>::const_iterator ipayload = jecPayloadsAK4chs_.begin(),
     ipayloadEnd = jecPayloadsAK4chs_.end(); ipayload != ipayloadEnd - 1; ++ipayload ) {
     JetCorrectorParameters pars(*ipayload);
     vParAK4chs.push_back(pars);
  }
  JetCorrectorAK4chs   = boost::shared_ptr<FactorizedJetCorrector>  ( new FactorizedJetCorrector(vParAK4chs) );
  JetCorrUncertAK4chs  = boost::shared_ptr<JetCorrectionUncertainty>( new JetCorrectionUncertainty(jecPayloadsAK4chs_.back()));
  
  // AK8chs JEC 
  std::vector<JetCorrectorParameters> vParAK8chs;
   for ( std::vector<std::string>::const_iterator ipayload = jecPayloadsAK8chs_.begin(),
     ipayloadEnd = jecPayloadsAK8chs_.end(); ipayload != ipayloadEnd - 1; ++ipayload ) {
     JetCorrectorParameters pars(*ipayload);
     vParAK8chs.push_back(pars);
  }
  JetCorrectorAK8chs   = boost::shared_ptr<FactorizedJetCorrector>  ( new FactorizedJetCorrector(vParAK8chs) );
  JetCorrUncertAK8chs  = boost::shared_ptr<JetCorrectionUncertainty>( new JetCorrectionUncertainty(jecPayloadsAK8chs_.back()));

  // AK4pup JEC 
  std::vector<JetCorrectorParameters> vParAK4pup;
   for ( std::vector<std::string>::const_iterator ipayload = jecPayloadsAK4pup_.begin(),
     ipayloadEnd = jecPayloadsAK4pup_.end(); ipayload != ipayloadEnd - 1; ++ipayload ) {
     JetCorrectorParameters pars(*ipayload);
     vParAK4pup.push_back(pars);
  }
  JetCorrectorAK4pup   = boost::shared_ptr<FactorizedJetCorrector>  ( new FactorizedJetCorrector(vParAK4pup) );
  JetCorrUncertAK4pup  = boost::shared_ptr<JetCorrectionUncertainty>( new JetCorrectionUncertainty(jecPayloadsAK4pup_.back()));
  
  // AK8pup JEC 
  std::vector<JetCorrectorParameters> vParAK8pup;
   for ( std::vector<std::string>::const_iterator ipayload = jecPayloadsAK8pup_.begin(),
     ipayloadEnd = jecPayloadsAK8pup_.end(); ipayload != ipayloadEnd - 1; ++ipayload ) {
     JetCorrectorParameters pars(*ipayload);
     vParAK8pup.push_back(pars);
  }
  JetCorrectorAK8pup   = boost::shared_ptr<FactorizedJetCorrector>  ( new FactorizedJetCorrector(vParAK8pup) );
  JetCorrUncertAK8pup  = boost::shared_ptr<JetCorrectionUncertainty>( new JetCorrectionUncertainty(jecPayloadsAK8pup_.back()));
  
  // jet resolution scale factor from text files
  JME::JetResolutionScaleFactor jer_scaler;
  jer_scaler = JME::JetResolutionScaleFactor(jerSFtext_);


  //
  //  888     888                  888    d8b                            
  //  888     888                  888    Y8P                            
  //  888     888                  888                                   
  //  Y88b   d88P  .d88b.  888d888 888888 888  .d8888b  .d88b.  .d8888b  
  //   Y88b d88P  d8P  Y8b 888P"   888    888 d88P"    d8P  Y8b 88K      
  //    Y88o88P   88888888 888     888    888 888      88888888 "Y8888b. 
  //     Y888P    Y8b.     888     Y88b.  888 Y88b.    Y8b.          X88 
  //      Y8P      "Y8888  888      "Y888 888  "Y8888P  "Y8888   88888P' 
  //                                                                     
  //                                                                     
                                                                       
  edm::Handle<std::vector<reco::Vertex> > vertices;
  iEvent.getByToken(vtxToken_, vertices);
  int nvtx = vertices->size();
  if (vertices->empty()) return; // skip the event if no PV found
  const reco::Vertex &PV = vertices->front();

  // 
  // 8888888b.  888               
  // 888   Y88b 888               
  // 888    888 888               
  // 888   d88P 88888b.   .d88b.  
  // 8888888P"  888 "88b d88""88b 
  // 888 T88b   888  888 888  888 
  // 888  T88b  888  888 Y88..88P 
  // 888   T88b 888  888  "Y88P"  
  //                

  Handle<double> rhoH;
  iEvent.getByToken(rhoToken_, rhoH);
  double rho = *rhoH;

  //
  // 888b     d888                            
  // 8888b   d8888                            
  // 88888b.d88888                            
  // 888Y88888P888 888  888  .d88b.  88888b.  
  // 888 Y888P 888 888  888 d88""88b 888 "88b 
  // 888  Y8P  888 888  888 888  888 888  888 
  // 888   "   888 Y88b 888 Y88..88P 888  888 
  // 888       888  "Y88888  "Y88P"  888  888 
  //                                          
                                             
  edm::Handle<pat::MuonCollection> muons;
  iEvent.getByToken(muonToken_, muons);

  TLorentzVector mu0_p4;
  bool mu0_isTight=false;
  int count_mu=0;
  for (const pat::Muon &mu : *muons) {
      if (mu.pt() < 30 || !mu.isLooseMuon() || fabs( mu.eta() ) < 2.1) continue;
      if (count_mu==0){
        mu0_p4.SetPtEtaPhiM( mu.pt(), mu.eta(), mu.phi(), mu.mass() );
        if ( mu.isTightMuon(PV) ) mu0_isTight = true;
        if (verbose_) cout<<"Muon pT "<<mu.pt()<<endl;
      } 
      // printf("muon with pt %4.1f, dz(PV) %+5.3f, POG loose id %d, tight id %d\n",
      // mu.pt(), mu.muonBestTrack()->dz(PV.position()), mu.isLooseMuon(), mu.isTightMuon(PV));
      count_mu++;
  }

  //
  // 8888888888 888                   888                              
  // 888        888                   888                              
  // 888        888                   888                              
  // 8888888    888  .d88b.   .d8888b 888888 888d888  .d88b.  88888b.  
  // 888        888 d8P  Y8b d88P"    888    888P"   d88""88b 888 "88b 
  // 888        888 88888888 888      888    888     888  888 888  888 
  // 888        888 Y8b.     Y88b.    Y88b.  888     Y88..88P 888  888 
  // 8888888888 888  "Y8888   "Y8888P  "Y888 888      "Y88P"  888  888 
  //                                                                   
  edm::Handle<pat::ElectronCollection> electrons;
  iEvent.getByToken(electronToken_, electrons);

  TLorentzVector el0_p4;
  int count_el=0;
  for (const pat::Electron &el : *electrons) {
      if (el.pt() < 50 || fabs(el.eta())>2.4 ) continue;
      if (count_el==0){
        el0_p4.SetPtEtaPhiM( el.pt(), el.eta(), el.phi(), el.mass() );
        if (verbose_) cout<<"Electron pT "<<el.pt()<<endl;
      } 
      count_el++;
      //printf("elec with pt %4.1f, supercluster eta %+5.3f, sigmaIetaIeta %.3f (%.3f with full5x5 shower shapes), lost hits %d, pass conv veto %d\n",
      //              el.pt(), el.superCluster()->eta(), el.sigmaIetaIeta(), el.full5x5_sigmaIetaIeta(), el.gsfTrack()->trackerExpectedHitsInner().numberOfLostHits(), el.passConversionVeto());
  }

  TLorentzVector lep0_p4;
  if (count_mu==1 &&  count_el==0)      lep0_p4 = mu0_p4;
  else if (count_el==1 && count_mu ==0) lep0_p4 = el0_p4;
  int count_lep = count_mu + count_el;

  //
  // 888b     d888 8888888888 88888888888 
  // 8888b   d8888 888            888     
  // 88888b.d88888 888            888     
  // 888Y88888P888 8888888        888     
  // 888 Y888P 888 888            888     
  // 888  Y8P  888 888            888     
  // 888   "   888 888            888     
  // 888       888 8888888888     888     
  //                                      

  edm::Handle<pat::METCollection> mets;
  iEvent.getByToken(metToken_, mets);
  const pat::MET &met = mets->front();
  if (verbose_){
    printf("MET: pt %5.1f, phi %+4.2f, sumEt (%.1f). genMET %.1f. MET with JES up/down: %.1f/%.1f\n",
        met.pt(), met.phi(), met.sumEt(),
        met.genMET()->pt(),
        met.shiftedPt(pat::MET::JetEnUp), met.shiftedPt(pat::MET::JetEnDown));
  }
  // 
  //        d8888 888    d8P      d8888       .d8888b.  888    888  .d8888b.         d8b          888             
  //       d88888 888   d8P      d8P888      d88P  Y88b 888    888 d88P  Y88b        Y8P          888             
  //      d88P888 888  d8P      d8P 888      888    888 888    888 Y88b.                          888             
  //     d88P 888 888d88K      d8P  888      888        8888888888  "Y888b.         8888  .d88b.  888888 .d8888b  
  //    d88P  888 8888888b    d88   888      888        888    888     "Y88b.       "888 d8P  Y8b 888    88K      
  //   d88P   888 888  Y88b   8888888888     888    888 888    888       "888        888 88888888 888    "Y8888b. 
  //  d8888888888 888   Y88b        888      Y88b  d88P 888    888 Y88b  d88P        888 Y8b.     Y88b.       X88 
  // d88P     888 888    Y88b       888       "Y8888P"  888    888  "Y8888P"         888  "Y8888   "Y888  88888P' 
  //                                                                                 888                          
  //                                                                                d88P                          

  //int count_AK4MINI = 0;
  TLorentzVector AK4_dRMinMu_p4;
  TLorentzVector AK4_btagged_dRMinMu_p4;
  double AK4_dRMinMu_bdisc = -99;
  double AK4_btagged_dRMinMu_bdisc = -99;
  double dRMinMu  = 99;
  double dRMinMu2 = 99;

  bool ak4_btag_loose  = false;
  bool ak4_btag_medium = false;
  bool ak4_btag_tight  = false;

  if (count_lep==1){  // don't need AK4 jets for all-hadronic

    edm::Handle<pat::JetCollection> AK4MINI;
    iEvent.getByToken(ak4jetToken_, AK4MINI);

    edm::Handle<reco::GenJetCollection> AK4GENJET;  
    iEvent.getByToken(ak4genjetToken_, AK4GENJET);

    for (const pat::Jet &ijet : *AK4MINI) {  
      
      //------------------------------------
      // AK4CHS JEC correction 
      //------------------------------------
      reco::Candidate::LorentzVector uncorrJet = ijet.correctedP4(0);
      JetCorrectorAK4chs->setJetEta( uncorrJet.eta() );
      JetCorrectorAK4chs->setJetPt ( uncorrJet.pt() );
      JetCorrectorAK4chs->setJetE  ( uncorrJet.energy() );
      JetCorrectorAK4chs->setJetA  ( ijet.jetArea() );
      JetCorrectorAK4chs->setRho   ( rho );
      JetCorrectorAK4chs->setNPV   ( nvtx );
      double corr = JetCorrectorAK4chs->getCorrection();

      reco::Candidate::LorentzVector corrJet = corr * uncorrJet;
      if (verbose_) cout<<"uncorrected AK4 jet pt "<<uncorrJet.pt()<<" corrected jet pt "<<corrJet.pt()<<endl;
      
      //------------------------------------
      // AK4CHS JEC uncertainty
      //------------------------------------
      double corrDn = 1.0;
      JetCorrUncertAK4chs->setJetPhi(  corrJet.phi()  );
      JetCorrUncertAK4chs->setJetEta(  corrJet.eta()  );
      JetCorrUncertAK4chs->setJetPt(   corrJet.pt()   );
      corrDn = corr - JetCorrUncertAK4chs->getUncertainty(0);
      double corrUp = 1.0;
      JetCorrUncertAK4chs->setJetPhi(  corrJet.phi()  );
      JetCorrUncertAK4chs->setJetEta(  corrJet.eta()  );
      JetCorrUncertAK4chs->setJetPt(   corrJet.pt()   );
      corrUp = corr + JetCorrUncertAK4chs->getUncertainty(1);

      if (verbose_) cout<<"corrDn "<<corrDn<<" corrUp "<< corrUp<<endl;
      //------------------------------------
      // GenJet  matched
      //------------------------------------ 
      TLorentzVector GenJetMatched;
      float GenJetMatched_dRmin   = 100;
      if (!iEvent.isRealData()) {
        for (const reco::GenJet &igen : *AK4GENJET) {  
          float dR = deltaR(ijet.eta(),ijet.phi(),igen.eta(),igen.phi());
          if (dR < GenJetMatched_dRmin) {
            GenJetMatched.SetPtEtaPhiM( igen.pt(), igen.eta(), igen.phi(), igen.mass() );
            GenJetMatched_dRmin = dR;
          }
        }
      }

      //------------------------------------
      // JER SF
      //------------------------------------
      double ptsmear   = 1;
      double ptsmearUp = 1;
      double ptsmearDn = 1;
      if (!iEvent.isRealData()) {
        double jer_sf    = jer_scaler.getScaleFactor({{JME::Binning::JetEta, corrJet.eta()}});
        double jer_sf_up = jer_scaler.getScaleFactor({{JME::Binning::JetEta, corrJet.eta()}}, Variation::UP);
        double jer_sf_dn = jer_scaler.getScaleFactor({{JME::Binning::JetEta, corrJet.eta()}}, Variation::DOWN);
        if (verbose_) std::cout << "JER Scale factors (Nominal / Up / Down) : " << jer_sf << " / " << jer_sf_up << " / " << jer_sf_dn << std::endl;
        double recopt    = corrJet.pt();
        double genpt     = GenJetMatched.Perp();
        double deltapt   = (recopt-genpt)*(jer_sf-1.0);
        double deltaptUp = (recopt-genpt)*(jer_sf_up-1.0);
        double deltaptDn = (recopt-genpt)*(jer_sf_dn-1.0);
        ptsmear   = std::max((double)0.0, (recopt+deltapt)/recopt     );
        ptsmearUp = std::max((double)0.0, (recopt+deltaptUp)/recopt   );
        ptsmearDn = std::max((double)0.0, (recopt+deltaptDn)/recopt   );
      }

      if (verbose_) cout<<"ptsmear "<<ptsmear<<" ptsmearUp "<< ptsmearDn<<" ptsmearDn "<< ptsmearUp<<endl;

      //------------------------------------
      // AK4 variables from miniAOD
      //------------------------------------
      double pt           = corrJet.pt();
      double mass         = corrJet.mass();
      double eta          = corrJet.eta();
      double phi          = corrJet.phi();
      //double rapidity     = ijet.rapidity();
      //double ndau         = ijet.numberOfDaughters();
      double bdisc        = ijet.bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"); 
      //double puid         = ijet.userFloat("pileupJetId:fullDiscriminant");

      //------------------------------------
      // Noise jet ID
      //------------------------------------    
      double NHF       = ijet.neutralHadronEnergyFraction();
      double NEMF      = ijet.neutralEmEnergyFraction();
      double CHF       = ijet.chargedHadronEnergyFraction();
      // double MUF       = ijet.muonEnergyFraction();
      double CEMF      = ijet.chargedEmEnergyFraction();
      // double NumConst  = ijet.chargedMultiplicity()+ijet.neutralMultiplicity();
      double NM        = ijet.neutralMultiplicity();
      double CM        = ijet.chargedMultiplicity(); 

      bool goodJet_looseJetID =  
        (fabs(eta) < 2.4 && CHF > 0.0 && NHF < 0.99 && CM > 0 && CEMF < 0.99 && NEMF < 0.99) 
        || ( fabs(eta) >= 2.4 && fabs(eta) < 3.0 && NEMF < 0.9 && NM > 2 ) 
        || ( fabs(eta) >= 3.0 && NEMF < 0.9 && NM > 10 );
      if (verbose_) cout<<"goodJet = "<<goodJet_looseJetID<<endl;

      //------------------------------------
      // Find AK4 jet closest to lepton
      //------------------------------------ 
      double deltaRlep = deltaR(corrJet.eta(), corrJet.phi(), lep0_p4.Eta(), lep0_p4.Phi() );

      if (pt>40 && fabs(eta)<2.4 && goodJet_looseJetID){
        if (deltaRlep<dRMinMu){
          dRMinMu = deltaRlep;
          AK4_dRMinMu_p4.SetPtEtaPhiM( pt, eta, phi, mass );
          AK4_dRMinMu_bdisc = bdisc;
        }
      }

      //------------------------------------
      // Find Loose b-tagged AK4 jet closest to lepton
      //------------------------------------ 
      if (pt>40 && fabs(eta)<2.4 && goodJet_looseJetID && bdisc>0.460 ){
        if (deltaRlep<dRMinMu2){
          dRMinMu2 = deltaRlep;
          AK4_btagged_dRMinMu_p4.SetPtEtaPhiM( pt, eta, phi, mass );
          AK4_btagged_dRMinMu_bdisc = bdisc;
        }
      }

      //------------------------------------
      // Check if there is a b-tagged AK4 jet in the lepton hemisphere
      //------------------------------------ 
      double deltaPhiLep = deltaPhi( phi,  lep0_p4.Phi() );  
      if (pt>40 && fabs(eta)<2.4 && goodJet_looseJetID){              
        if (deltaPhiLep<  3.14/2.0)
        {
          if (bdisc>0.460 ) ak4_btag_loose  = true;
          if (bdisc>0.800 ) ak4_btag_medium = true;
          if (bdisc>0.935 ) ak4_btag_tight  = true;
        }
      }
    }
   }

  //      
  //         d8888 888    d8P   .d8888b.       .d8888b.  888    888  .d8888b.         d8b          888             
  //        d88888 888   d8P   d88P  Y88b     d88P  Y88b 888    888 d88P  Y88b        Y8P          888             
  //       d88P888 888  d8P    Y88b. d88P     888    888 888    888 Y88b.                          888             
  //      d88P 888 888d88K      "Y88888"      888        8888888888  "Y888b.         8888  .d88b.  888888 .d8888b  
  //     d88P  888 8888888b    .d8P""Y8b.     888        888    888     "Y88b.       "888 d8P  Y8b 888    88K      
  //    d88P   888 888  Y88b   888    888     888    888 888    888       "888        888 88888888 888    "Y8888b. 
  //   d8888888888 888   Y88b  Y88b  d88P     Y88b  d88P 888    888 Y88b  d88P        888 Y8b.     Y88b.       X88 
  //  d88P     888 888    Y88b  "Y8888P"       "Y8888P"  888    888  "Y8888P"         888  "Y8888   "Y888  88888P' 
  //                                                                                  888                          
  //                                                                               d88P                          
  //                                                                             888P"                                                                                              

  edm::Handle<pat::JetCollection> AK8CHS;
  iEvent.getByToken(ak8jetToken_, AK8CHS);

  edm::Handle<reco::GenJetCollection> AK8GENJET;  
  iEvent.getByToken(ak8genjetToken_, AK8GENJET);

  if (useToolbox_){
    edm::Handle<pat::JetCollection> AK8CHSsub;
    iEvent.getByToken(ak8CHSSoftDropSubjetsToken_, AK8CHSsub);
  }

  int count_AK8CHS = 0;
  TLorentzVector AK8jet_SemiLept_P4corr;
  TLorentzVector AK8jet0_P4corr;
  TLorentzVector AK8jet1_P4corr;
  TLorentzVector GenJetMatched0;
  TLorentzVector GenJetMatched1;
  for (const pat::Jet &ijet : *AK8CHS) {  
    if (count_AK8CHS>1) break;
    if (count_AK8CHS==0 && ijet.pt()<250) break;
    //------------------------------------
    // AK8CHS JEC correction 
    //------------------------------------
    reco::Candidate::LorentzVector uncorrJet = ijet.correctedP4(0);
    JetCorrectorAK8chs->setJetEta( uncorrJet.eta() );
    JetCorrectorAK8chs->setJetPt ( uncorrJet.pt() );
    JetCorrectorAK8chs->setJetE  ( uncorrJet.energy() );
    JetCorrectorAK8chs->setJetA  ( ijet.jetArea() );
    JetCorrectorAK8chs->setRho   ( rho );
    JetCorrectorAK8chs->setNPV   ( nvtx );
    double corr = JetCorrectorAK8chs->getCorrection();

    reco::Candidate::LorentzVector corrJet = corr * uncorrJet;
    if (verbose_) cout<<"uncorrected AK8 jet pt "<<uncorrJet.pt()<<" corrected jet pt "<<corrJet.pt()<<endl;
    
    if(count_AK8CHS==0) AK8jet0_P4corr.SetPtEtaPhiM( corrJet.pt(), corrJet.eta(), corrJet.phi(), corrJet.mass() );
    if(count_AK8CHS==1) AK8jet1_P4corr.SetPtEtaPhiM( corrJet.pt(), corrJet.eta(), corrJet.phi(), corrJet.mass() );

    //------------------------------------
    // AK8CHS JEC L23 correction
    //------------------------------------
    JetCorrectorAK8chs->setJetEta( uncorrJet.eta() );
    JetCorrectorAK8chs->setJetPt ( uncorrJet.pt() );
    JetCorrectorAK8chs->setJetE  ( uncorrJet.energy() );
    JetCorrectorAK8chs->setJetA  ( ijet.jetArea() );
    JetCorrectorAK8chs->setRho   ( rho );
    JetCorrectorAK8chs->setNPV   ( nvtx );
    // getSubCorrections member function returns the vector of the subcorrections UP to the given level. For example in the example above, factors[0] is the L1 correction and factors[3] is the L1+L2+L3+Residual correction. 
    vector<float> factors = JetCorrectorAK8chs->getSubCorrections();
    float corr_factor_L1      = 1.0;
    float corr_factor_L12     = 1.0;
    float corr_factor_L123    = 1.0;
    float corr_factor_L123res = 1.0;
    if (factors.size() > 0) corr_factor_L1       = factors[0];
    if (factors.size() > 1) corr_factor_L12      = factors[1];
    if (factors.size() > 2) corr_factor_L123     = factors[2];
    if (factors.size() > 3) corr_factor_L123res  = factors[3];
    double corr_factor_L2 = corr_factor_L12/corr_factor_L1;
    double corr_factor_L3 = corr_factor_L123/corr_factor_L12;
    double corr_factor_res = corr_factor_L123res/corr_factor_L123;
    //double corr_factor_L23 = corr_factor_L2*corr_factor_L3;
    double corr_factor_L23res = corr_factor_L2*corr_factor_L3*corr_factor_res;

    //------------------------------------
    // AK8CHS JEC uncertainty
    //------------------------------------
    double corrDn_L23  = 1.0;
    double corrDn_L123 = 1.0;
    JetCorrUncertAK8chs->setJetPhi(  corrJet.phi()  );
    JetCorrUncertAK8chs->setJetEta(  corrJet.eta()  );
    JetCorrUncertAK8chs->setJetPt(   corrJet.pt()   );
    double corrDn_temp1 = JetCorrUncertAK8chs->getUncertainty(0);
    corrDn_L23   = corr_factor_L23res - corrDn_temp1;
    corrDn_L123 = corr - corrDn_temp1;
    double corrUp_L23  = 1.0;
    double corrUp_L123 = 1.0;
    JetCorrUncertAK8chs->setJetPhi(  corrJet.phi()  );
    JetCorrUncertAK8chs->setJetEta(  corrJet.eta()  );
    JetCorrUncertAK8chs->setJetPt(   corrJet.pt()   );
    double corrUp_temp1 = JetCorrUncertAK8chs->getUncertainty(1);
    corrUp_L23   = corr_factor_L23res + corrUp_temp1;
    corrUp_L123 = corr + corrUp_temp1;

    //------------------------------------
    // GenJet  matched
    //------------------------------------ 
    TLorentzVector GenJetMatched;
    float GenJetMatched_dRmin   = 100;
    if (!iEvent.isRealData()) {
      for (const reco::GenJet &igen : *AK8GENJET) {  
        float dR = deltaR(ijet.eta(),ijet.phi(),igen.eta(),igen.phi());
        if (dR < GenJetMatched_dRmin) {
          GenJetMatched.SetPtEtaPhiM( igen.pt(), igen.eta(), igen.phi(), igen.mass() );
          GenJetMatched_dRmin = dR;
        }
      }
    }
    if ( count_AK8CHS==0 ) GenJetMatched0 = GenJetMatched;
    if ( count_AK8CHS==1 ) GenJetMatched1 = GenJetMatched;

    //------------------------------------
    // JER SF
    //------------------------------------
    double ptsmear   = 1;
    double ptsmearUp = 1;
    double ptsmearDn = 1;
    if (!iEvent.isRealData()) {
      double jer_sf    = jer_scaler.getScaleFactor({{JME::Binning::JetEta, corrJet.eta()}});
      double jer_sf_up = jer_scaler.getScaleFactor({{JME::Binning::JetEta, corrJet.eta()}}, Variation::UP);
      double jer_sf_dn = jer_scaler.getScaleFactor({{JME::Binning::JetEta, corrJet.eta()}}, Variation::DOWN);
      if (verbose_) std::cout << "JER Scale factors (Nominal / Up / Down) : " << jer_sf << " / " << jer_sf_up << " / " << jer_sf_dn << std::endl;
      double recopt    = corrJet.pt();
      double genpt     = GenJetMatched.Perp();
      double deltapt   = (recopt-genpt)*(jer_sf-1.0);
      double deltaptUp = (recopt-genpt)*(jer_sf_up-1.0);
      double deltaptDn = (recopt-genpt)*(jer_sf_dn-1.0);
      ptsmear   = std::max((double)0.0, (recopt+deltapt)/recopt     );
      ptsmearUp = std::max((double)0.0, (recopt+deltaptUp)/recopt   );
      ptsmearDn = std::max((double)0.0, (recopt+deltaptDn)/recopt   );
    }

    //------------------------------------
    // AK8 variables from miniAOD
    //------------------------------------
    double pt           = corrJet.pt();
    //double mass         = corrJet.mass();
    //double eta          = corrJet.eta();
    //double phi          = corrJet.phi();
    //double rapidity     = ijet.rapidity();
    //double ndau         = ijet.numberOfDaughters();

    double tau1         = 99;
    double tau2         = 99;
    double tau3         = 99;
    // double tau4         = 99;
    double prunedMass   = ijet.userFloat("ak8PFJetsCHSPrunedMass");
    double softDropMass = ijet.userFloat("ak8PFJetsCHSSoftDropMass");
    // double trimmedMass  = -1;

  

    if (useToolbox_){
      tau1         = ijet.userFloat("NjettinessAK8CHS:tau1");
      tau2         = ijet.userFloat("NjettinessAK8CHS:tau2");
      tau3         = ijet.userFloat("NjettinessAK8CHS:tau3");
      // tau4         = ijet.userFloat("NjettinessAK8CHS:tau4");
      // trimmedMass  = ijet.userFloat("ak8PFJetsCHSTrimmedMass"); 
    }
    else{
      tau1         = ijet.userFloat("NjettinessAK8:tau1");
      tau2         = ijet.userFloat("NjettinessAK8:tau2");
      tau3         = ijet.userFloat("NjettinessAK8:tau3");
    }

    double tau21        = 99;
    double tau32        = 99;

    double puppi_pt     = -1;     
    double puppi_mass   = -1;     
    double puppi_eta    = -1;     
    double puppi_phi    = -1;     
    double puppi_tau1   = -1;     
    double puppi_tau2   = -1;     
    double puppi_tau3   = -1;     
 
    if (!useToolbox_){
      puppi_pt           = ijet.userFloat("ak8PFJetsPuppiValueMap:pt");
      puppi_mass         = ijet.userFloat("ak8PFJetsPuppiValueMap:mass");
      puppi_eta          = ijet.userFloat("ak8PFJetsPuppiValueMap:eta");
      puppi_phi          = ijet.userFloat("ak8PFJetsPuppiValueMap:phi");
      puppi_tau1         = ijet.userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau1");
      puppi_tau2         = ijet.userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau2");
      puppi_tau3         = ijet.userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau3");
    }
    double puppi_tau21        = 99;
    double puppi_tau32        = 99;

    //double deltaRpup = deltaR(ijet.eta(), ijet.phi(), puppi_eta, puppi_phi );

    if (tau1!=0) tau21 = tau2/tau1;
    if (tau2!=0) tau32 = tau3/tau2;

    if (puppi_tau1!=0) puppi_tau21 = puppi_tau2/puppi_tau1;
    if (puppi_tau2!=0) puppi_tau32 = puppi_tau3/puppi_tau2;

    TLorentzVector jet_p4;
    jet_p4.SetPtEtaPhiM( corrJet.pt(), corrJet.eta(), corrJet.phi(), corrJet.mass() );

    if (verbose_) cout<<"\nJet with pT "<<pt<<" sdMass "<<softDropMass<<endl;

    //------------------------------------
    // SoftDrop subjets
    //------------------------------------
    TLorentzVector sub0_P4_uncorr           ;
    TLorentzVector sub0_P4_L123res          ;
    TLorentzVector sub0_P4_L23res           ;
    TLorentzVector sub1_P4_uncorr           ;
    TLorentzVector sub1_P4_L123res          ;
    TLorentzVector sub1_P4_L23res           ;

    TLorentzVector sub0_P4_corrUp_L123res   ;
    TLorentzVector sub0_P4_corrUp_L23res    ;
    TLorentzVector sub1_P4_corrUp_L123res   ;
    TLorentzVector sub1_P4_corrUp_L23res    ;

    TLorentzVector sub0_P4_corrDn_L123res   ;
    TLorentzVector sub0_P4_corrDn_L23res    ;
    TLorentzVector sub1_P4_corrDn_L123res   ;
    TLorentzVector sub1_P4_corrDn_L23res    ;

    double sub0_area  = 0;
    double sub0_tau1  = 0;
    double sub0_tau2  = 0;
    double sub0_tau3  = 0;
    double sub0_flav_hadron  = 0;
    double sub0_flav_parton  = 0;
    double sub0_bdisc = 0;
    double sub1_area  = 0;
    double sub1_tau1  = 0;
    double sub1_tau2  = 0;
    double sub1_tau3  = 0;
    double sub1_flav_hadron  = 0;
    double sub1_flav_parton  = 0;
    double sub1_bdisc = 0;
    double mostMassiveSDsubjetMass = 0;
    int count_SD =0;

    if (!useToolbox_){
      auto const & sdSubjets = ijet.subjets("SoftDrop");
      for ( auto const & it : sdSubjets ) {
        double subjetPt       = it->correctedP4(0).pt();
        double subjetEta      = it->correctedP4(0).eta();
        double subjetPhi      = it->correctedP4(0).phi();
        double subjetMass     = it->correctedP4(0).mass();
        double subjetBdisc    = it->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"); 
        double deltaRsubjetJet = deltaR(ijet.eta(), ijet.phi(), subjetEta, subjetPhi);
      
        //------------------------------------
        // subjet JEC 
        //------------------------------------
        reco::Candidate::LorentzVector uncorrSubjet = it->correctedP4(0);
        JetCorrectorAK4chs -> setJetEta( uncorrSubjet.eta()    );
        JetCorrectorAK4chs -> setJetPt ( uncorrSubjet.pt()     );
        JetCorrectorAK4chs -> setJetE  ( uncorrSubjet.energy() );
        JetCorrectorAK4chs -> setJetA  ( it->jetArea()         );
        JetCorrectorAK4chs -> setRho   ( rho                   );
        JetCorrectorAK4chs -> setNPV   ( nvtx                  );
        double subjet_corr_factor_L123res_full = JetCorrectorAK4chs->getCorrection();
        reco::Candidate::LorentzVector corrSubjetL123res = subjet_corr_factor_L123res_full * uncorrSubjet;

        //------------------------------------
        // subjet L23 JEC 
        //------------------------------------
        JetCorrectorAK4chs->setJetEta( uncorrSubjet.eta()    );
        JetCorrectorAK4chs->setJetPt ( uncorrSubjet.pt()     );
        JetCorrectorAK4chs->setJetE  ( uncorrSubjet.energy() );
        JetCorrectorAK4chs->setJetA  ( it->jetArea()         );
        JetCorrectorAK4chs->setRho   ( rho                   );
        JetCorrectorAK4chs->setNPV   ( nvtx                  );
        // getSubCorrections member function returns the vector of the subcorrections UP to the given level. For example in the example above, factors[0] is the L1 correction and factors[3] is the L1+L2+L3+Residual correction. 
        vector<float> subjet_factors = JetCorrectorAK4chs->getSubCorrections();
        float subjet_corr_factor_L1      = 1.0;
        float subjet_corr_factor_L12     = 1.0;
        float subjet_corr_factor_L123    = 1.0;
        float subjet_corr_factor_L123res = 1.0;
        if (factors.size() > 0) subjet_corr_factor_L1      = subjet_factors[0];
        if (factors.size() > 1) subjet_corr_factor_L12     = subjet_factors[1];
        if (factors.size() > 2) subjet_corr_factor_L123    = subjet_factors[2];
        if (factors.size() > 3) subjet_corr_factor_L123res = subjet_factors[3];
        double subjet_corr_factor_L2     = subjet_corr_factor_L12     / subjet_corr_factor_L1     ;
        double subjet_corr_factor_L3     = subjet_corr_factor_L123    / subjet_corr_factor_L12    ;
        double subjet_corr_factor_res    = subjet_corr_factor_L123res / subjet_corr_factor_L123   ;
        double subjet_corr_factor_L23    = subjet_corr_factor_L2 * subjet_corr_factor_L3     ;
        double subjet_corr_factor_L23res = subjet_corr_factor_L2 * subjet_corr_factor_L3 * subjet_corr_factor_res    ;
        if (verbose_) cout<<"subjet corr: L1 "<<subjet_corr_factor_L1<<" L23 "<<subjet_corr_factor_L23<<" L23res "<<subjet_corr_factor_L23res<<" L123res"<<subjet_corr_factor_L123res<<endl;
        reco::Candidate::LorentzVector corrSubjetL23res   = subjet_corr_factor_L23res * uncorrSubjet;
        
        //------------------------------------
        // subjet JEC uncertainty
        //------------------------------------
        double subjet_corrDn_L23 =   1.0;
        double subjet_corrDn_L123 = 1.0;
        JetCorrUncertAK4chs->setJetPhi(  corrSubjetL123res.phi()  );
        JetCorrUncertAK4chs->setJetEta(  corrSubjetL123res.eta()  );
        JetCorrUncertAK4chs->setJetPt(   corrSubjetL123res.pt()   );
        double corrDn_temp2 = JetCorrUncertAK4chs->getUncertainty(0);
        subjet_corrDn_L23   = subjet_corr_factor_L23res - corrDn_temp2;
        subjet_corrDn_L123  = subjet_corr_factor_L123res_full - corrDn_temp2;

        double subjet_corrUp_L23   = 1.0;
        double subjet_corrUp_L123 = 1.0;
        JetCorrUncertAK4chs->setJetPhi(  corrSubjetL123res.phi()  );
        JetCorrUncertAK4chs->setJetEta(  corrSubjetL123res.eta()  );
        JetCorrUncertAK4chs->setJetPt(   corrSubjetL123res.pt()   );
        double corrUp_temp2 = JetCorrUncertAK4chs->getUncertainty(1);
        subjet_corrUp_L23   = subjet_corr_factor_L23res + corrUp_temp2;
        subjet_corrUp_L123  = subjet_corr_factor_L123res_full + corrUp_temp2;

        reco::Candidate::LorentzVector corrDnSubjetL123res  = subjet_corrDn_L123  * uncorrSubjet;
        reco::Candidate::LorentzVector corrUpSubjetL123res  = subjet_corrUp_L123  * uncorrSubjet;
        reco::Candidate::LorentzVector corrDnSubjetL23res   = subjet_corrDn_L23   * uncorrSubjet;
        reco::Candidate::LorentzVector corrUpSubjetL23res   = subjet_corrUp_L23   * uncorrSubjet;
     
        //------------------------------------
        // subjet values for Tree
        //------------------------------------
        if (count_SD==0){
          sub0_P4_uncorr            .SetPtEtaPhiM( subjetPt, subjetEta, subjetPhi, subjetMass);
          sub0_P4_L123res           .SetPtEtaPhiM( corrSubjetL123res.pt()   , corrSubjetL123res.eta()   , corrSubjetL123res.phi()   , corrSubjetL123res.mass()    );
          sub0_P4_L23res            .SetPtEtaPhiM( corrSubjetL23res.pt()    , corrSubjetL23res.eta()    , corrSubjetL23res.phi()    , corrSubjetL23res.mass()     );
          sub0_P4_corrUp_L123res    .SetPtEtaPhiM( corrUpSubjetL123res.pt() , corrUpSubjetL123res.eta() , corrUpSubjetL123res.phi() , corrUpSubjetL123res.mass()  );
          sub0_P4_corrUp_L23res     .SetPtEtaPhiM( corrUpSubjetL23res.pt()  , corrUpSubjetL23res.eta()  , corrUpSubjetL23res.phi()  , corrUpSubjetL23res.mass()   );
          sub0_P4_corrDn_L123res    .SetPtEtaPhiM( corrDnSubjetL123res.pt() , corrDnSubjetL123res.eta() , corrDnSubjetL123res.phi() , corrUpSubjetL123res.mass()  );
          sub0_P4_corrDn_L23res     .SetPtEtaPhiM( corrDnSubjetL23res.pt()  , corrDnSubjetL23res.eta()  , corrDnSubjetL23res.phi()  , corrSubjetL23res.mass()     );
          sub0_area   = it->jetArea() ;
          if (useToolbox_){
            sub0_tau1   = it->userFloat("NjettinessAK8:tau1");
            sub0_tau2   = it->userFloat("NjettinessAK8:tau2");
            sub0_tau3   = it->userFloat("NjettinessAK8:tau3");
          }
          sub0_flav_parton   = it->partonFlavour();
          sub0_flav_hadron   = it->hadronFlavour();
          sub0_bdisc  = subjetBdisc;
        }
        if (count_SD==1) {
          sub1_P4_uncorr          .SetPtEtaPhiM( subjetPt, subjetEta, subjetPhi, subjetMass);
          sub1_P4_L123res         .SetPtEtaPhiM( corrSubjetL123res.pt()   , corrSubjetL123res.eta()   , corrSubjetL123res.phi()   , corrSubjetL123res.mass()    );
          sub1_P4_L23res          .SetPtEtaPhiM( corrSubjetL23res.pt()    , corrSubjetL23res.eta()    , corrSubjetL23res.phi()    , corrSubjetL23res.mass()     );
          sub1_P4_corrUp_L123res  .SetPtEtaPhiM( corrUpSubjetL123res.pt() , corrUpSubjetL123res.eta() , corrUpSubjetL123res.phi() , corrUpSubjetL123res.mass()  );
          sub1_P4_corrUp_L23res   .SetPtEtaPhiM( corrUpSubjetL23res.pt()  , corrUpSubjetL23res.eta()  , corrUpSubjetL23res.phi()  , corrUpSubjetL23res.mass()   );
          sub1_P4_corrDn_L123res  .SetPtEtaPhiM( corrDnSubjetL123res.pt() , corrDnSubjetL123res.eta() , corrDnSubjetL123res.phi() , corrUpSubjetL123res.mass()  );
          sub1_P4_corrDn_L23res   .SetPtEtaPhiM( corrDnSubjetL23res.pt()  , corrDnSubjetL23res.eta()  , corrDnSubjetL23res.phi()  , corrSubjetL23res.mass()     );
          sub1_area   = it->jetArea() ;
          if (useToolbox_){
            sub1_tau1   = it->userFloat("NjettinessAK8:tau1");
            sub1_tau2   = it->userFloat("NjettinessAK8:tau2");
            sub1_tau3   = it->userFloat("NjettinessAK8:tau3");
          }
          sub1_flav_parton   = it->partonFlavour();
          sub1_flav_hadron   = it->hadronFlavour();
          sub1_bdisc  = subjetBdisc;
        }
        if (subjetMass > mostMassiveSDsubjetMass) mostMassiveSDsubjetMass = subjetMass;

        if (verbose_) cout<<" SD Subjet pt "<<subjetPt<<" Eta "<<subjetEta<<" deltaRsubjetJet "<<deltaRsubjetJet<<" Mass "<<subjetMass<<" Bdisc "<<subjetBdisc<<endl;
        count_SD++;
      }
    }

    TLorentzVector sumSDsubjets_P4_uncorr   ;
    TLorentzVector sumSDsubjets_P4_L123res  ;
    TLorentzVector sumSDsubjets_P4_L23res   ;
    TLorentzVector sumSDsubjets_P4_corrUp_L123res ;
    TLorentzVector sumSDsubjets_P4_corrUp_L23res  ;
    TLorentzVector sumSDsubjets_P4_corrDn_L123res ;
    TLorentzVector sumSDsubjets_P4_corrDn_L23res  ;
    if (count_SD>1){ 
      sumSDsubjets_P4_uncorr             = sub0_P4_uncorr              + sub1_P4_uncorr            ; 
      sumSDsubjets_P4_L123res            = sub0_P4_L123res             + sub1_P4_L123res           ; 
      sumSDsubjets_P4_L23res             = sub0_P4_L23res              + sub1_P4_L23res            ; 
      sumSDsubjets_P4_corrUp_L123res     = sub0_P4_corrUp_L123res      + sub1_P4_corrUp_L123res    ; 
      sumSDsubjets_P4_corrUp_L23res      = sub0_P4_corrUp_L23res       + sub1_P4_corrUp_L23res     ; 
      sumSDsubjets_P4_corrDn_L123res     = sub0_P4_corrDn_L123res      + sub1_P4_corrDn_L123res    ; 
      sumSDsubjets_P4_corrDn_L23res      = sub0_P4_corrDn_L23res       + sub1_P4_corrDn_L23res     ; 
    }  

    double maxbdisc = 0 ;
    double maxbdiscflav_hadron = 0 ;
    double maxbdiscflav_parton = 0 ;
    if (sub0_bdisc>=sub1_bdisc){
      maxbdisc = sub0_bdisc;
      maxbdiscflav_hadron = sub0_flav_hadron;
      maxbdiscflav_parton = sub0_flav_parton;
    } 
    else if (sub1_bdisc>sub0_bdisc){
      maxbdisc = sub1_bdisc;
      maxbdiscflav_hadron = sub1_flav_hadron;
      maxbdiscflav_parton = sub1_flav_parton;
    }  

    //------------------------------------
    // PUPPI SoftDrop subjets
    //------------------------------------ 
    TLorentzVector pup0_P4_uncorr    ;
    TLorentzVector pup0_P4_L23res    ;
    TLorentzVector pup1_P4_uncorr    ;
    TLorentzVector pup1_P4_L23res    ;

    TLorentzVector pup0_P4_corrUp_L23res    ;
    TLorentzVector pup1_P4_corrUp_L23res    ;

    TLorentzVector pup0_P4_corrDn_L23res    ;
    TLorentzVector pup1_P4_corrDn_L23res    ;

    double pup0_area  = 0;
    double pup0_tau1  = 0;
    double pup0_tau2  = 0;
    double pup0_tau3  = 0;
    double pup0_flav_hadron  = 0;
    double pup0_flav_parton  = 0;
    double pup0_bdisc = 0;
    double pup1_area  = 0;
    double pup1_tau1  = 0;
    double pup1_tau2  = 0;
    double pup1_tau3  = 0;
    double pup1_flav_hadron  = 0;
    double pup1_flav_parton  = 0;
    double pup1_bdisc = 0;
    double mostMassiveSDPUPPIsubjetMass = 0;
    auto const & sdSubjetsPuppi = ijet.subjets("SoftDropPuppi");
    int count_pup=0;

    if (!useToolbox_){
      for ( auto const & it : sdSubjetsPuppi ) {
        double subjetPt       = it->correctedP4(0).pt();
        double subjetEta      = it->correctedP4(0).eta();
        double subjetPhi      = it->correctedP4(0).phi();
        double subjetMass     = it->correctedP4(0).mass();
        double subjetBdisc    = it->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"); 
        double deltaRsubjetJet = deltaR(ijet.eta(), ijet.phi(), subjetEta, subjetPhi);
        if (verbose_) cout<<" SD Subjet pt "<<subjetPt<<" Eta "<<subjetEta<<" deltaRsubjetJet "<<deltaRsubjetJet<<" Mass "<<subjetMass<<" Bdisc "<<subjetBdisc<<endl; 
        
        //------------------------------------
        // PUPPI subjet JEC 
        //------------------------------------
        reco::Candidate::LorentzVector uncorrSubjet = it->correctedP4(0);
        JetCorrectorAK4pup -> setJetEta( uncorrSubjet.eta()    );
        JetCorrectorAK4pup -> setJetPt ( uncorrSubjet.pt()     );
        JetCorrectorAK4pup -> setJetE  ( uncorrSubjet.energy() );
        JetCorrectorAK4pup -> setJetA  ( it->jetArea()         );
        JetCorrectorAK4pup -> setRho   ( rho                   );
        JetCorrectorAK4pup -> setNPV   ( nvtx                  );
        double subjet_corr_factor_L23res_full = JetCorrectorAK4pup->getCorrection();
        reco::Candidate::LorentzVector corrSubjetL23res = subjet_corr_factor_L23res_full * uncorrSubjet;

        //------------------------------------
        // PUPPI subjet JEC uncertainty
        //------------------------------------
        double subjet_corrDn_L23 =   1.0;
        JetCorrUncertAK4pup->setJetPhi(  corrSubjetL23res.phi()  );
        JetCorrUncertAK4pup->setJetEta(  corrSubjetL23res.eta()  );
        JetCorrUncertAK4pup->setJetPt(   corrSubjetL23res.pt()   );
        subjet_corrDn_L23   = subjet_corr_factor_L23res_full - JetCorrUncertAK4pup->getUncertainty(0);
        double subjet_corrUp_L23 =   1.0;
        JetCorrUncertAK4pup->setJetPhi(  corrSubjetL23res.phi()  );
        JetCorrUncertAK4pup->setJetEta(  corrSubjetL23res.eta()  );
        JetCorrUncertAK4pup->setJetPt(   corrSubjetL23res.pt()   );
        subjet_corrUp_L23   = subjet_corr_factor_L23res_full + JetCorrUncertAK4pup->getUncertainty(1);

        reco::Candidate::LorentzVector corrDnSubjetL23res   = subjet_corrDn_L23   * uncorrSubjet;
        reco::Candidate::LorentzVector corrUpSubjetL23res   = subjet_corrUp_L23   * uncorrSubjet;
     
        if (count_pup==0){
          pup0_P4_uncorr           .SetPtEtaPhiM( subjetPt, subjetEta, subjetPhi, subjetMass);
          pup0_P4_L23res           .SetPtEtaPhiM( corrSubjetL23res.pt()    , corrSubjetL23res.eta()    , corrSubjetL23res.phi()    , corrSubjetL23res.mass()     );
          pup0_P4_corrUp_L23res    .SetPtEtaPhiM( corrUpSubjetL23res.pt()  , corrUpSubjetL23res.eta()  , corrUpSubjetL23res.phi()  , corrUpSubjetL23res.mass()   );
          pup0_P4_corrDn_L23res    .SetPtEtaPhiM( corrDnSubjetL23res.pt()  , corrDnSubjetL23res.eta()  , corrDnSubjetL23res.phi()  , corrSubjetL23res.mass()     );
          pup0_area   = it->jetArea() ;
          if (useToolbox_){
            pup0_tau1   = it->userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau1");
            pup0_tau2   = it->userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau2");
            pup0_tau3   = it->userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau3");
          }
          pup0_flav_parton   = it->partonFlavour();
          pup0_flav_hadron   = it->hadronFlavour();
          pup0_bdisc  = subjetBdisc;
        }
        if (count_pup==1) {
          pup1_P4_uncorr            .SetPtEtaPhiM( subjetPt, subjetEta, subjetPhi, subjetMass);
          pup1_P4_L23res           .SetPtEtaPhiM( corrSubjetL23res.pt()    , corrSubjetL23res.eta()    , corrSubjetL23res.phi()    , corrSubjetL23res.mass()     );
          pup1_P4_corrUp_L23res    .SetPtEtaPhiM( corrUpSubjetL23res.pt()  , corrUpSubjetL23res.eta()  , corrUpSubjetL23res.phi()  , corrUpSubjetL23res.mass()   );
          pup1_P4_corrDn_L23res    .SetPtEtaPhiM( corrDnSubjetL23res.pt()  , corrDnSubjetL23res.eta()  , corrDnSubjetL23res.phi()  , corrSubjetL23res.mass()     );
          pup1_area   = it->jetArea() ;
          if (useToolbox_){
            pup1_tau1   = it->userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau1");
            pup1_tau2   = it->userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau2");
            pup1_tau3   = it->userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau3");
          }
          pup1_flav_parton   = it->partonFlavour();
          pup1_flav_hadron   = it->hadronFlavour();
          pup1_bdisc  = subjetBdisc;
        }

        if (subjetMass > mostMassiveSDPUPPIsubjetMass) mostMassiveSDPUPPIsubjetMass = subjetMass;
        count_pup++;
      }
    }

    TLorentzVector sumPUPsubjets_P4_uncorr   ;
    TLorentzVector sumPUPsubjets_P4_L23res  ;
    TLorentzVector sumPUPsubjets_P4_corrUp_L23res  ;
    TLorentzVector sumPUPsubjets_P4_corrDn_L23res  ;
    if (count_SD>1){ 
      sumPUPsubjets_P4_uncorr              = pup0_P4_uncorr              + pup1_P4_uncorr             ; 
      sumPUPsubjets_P4_L23res             = pup0_P4_L23res             + pup1_P4_L23res            ; 
      sumPUPsubjets_P4_corrUp_L23res      = pup0_P4_corrUp_L23res      + pup1_P4_corrUp_L23res     ; 
      sumPUPsubjets_P4_corrDn_L23res      = pup0_P4_corrDn_L23res      + pup1_P4_corrDn_L23res     ; 
    } 

    double pup_maxbdisc = 0 ;
    double pup_maxbdiscflav_hadron = 0 ;
    double pup_maxbdiscflav_parton = 0 ;
    if (pup0_bdisc>=pup1_bdisc){
      pup_maxbdisc = pup0_bdisc;
      pup_maxbdiscflav_hadron = pup0_flav_hadron;
      pup_maxbdiscflav_parton = pup0_flav_parton;
    } 
    else if (pup1_bdisc>pup0_bdisc){
      pup_maxbdisc = pup1_bdisc;
      pup_maxbdiscflav_hadron = pup1_flav_hadron;
      pup_maxbdiscflav_parton = pup1_flav_parton;
    }  

    h_ak8chs_softDropMass    ->Fill( sumSDsubjets_P4_uncorr.M()   );
    h_ak8puppi_softDropMass  ->Fill( sumPUPsubjets_P4_uncorr.M()  );

    //------------------------------------
    // Gen particle info
    //------------------------------------ 
    
    double deltaR_jet_t1 = jet_p4.DeltaR(t1_p4  );
    double deltaR_jet_t2 = jet_p4.DeltaR(t2_p4  );
    bool jet_matched_t1 = false;
    bool jet_matched_t2 = false;
    if (deltaR_jet_t1<deltaR_jet_t2) jet_matched_t1 = true;
    if (deltaR_jet_t2<deltaR_jet_t1) jet_matched_t2 = true;

    double deltaR_jet_p1 =  jet_p4.DeltaR(hardest_parton_hardScatterOutgoing_p4);
    double deltaR_jet_p2 =  jet_p4.DeltaR(second_hardest_parton_hardScatterOutgoing_p4);
    bool jet_matched_p1 = false;
    bool jet_matched_p2 = false;
    if (deltaR_jet_p1<deltaR_jet_p2) jet_matched_p1 = true;
    if (deltaR_jet_p2<deltaR_jet_p1) jet_matched_p2 = true;
      
    //------------------------------------
    // Fill AllHadTree
    //------------------------------------ 

    if (count_AK8CHS==0){
      Jet0PtRaw                              = uncorrJet.pt()      ;                 
      Jet0EtaRaw                             = uncorrJet.eta()     ;                  
      Jet0PhiRaw                             = uncorrJet.phi()     ;   
      Jet0MassRaw                            = uncorrJet.mass()    ;                                           
      Jet0P                                  = corrJet.P()         ;        
      Jet0Pt                                 = corrJet.pt()        ;                  
      Jet0Eta                                = corrJet.eta()       ;                  
      Jet0Phi                                = corrJet.phi()       ;                  
      Jet0Rap                                = corrJet.Rapidity()  ;                  
      Jet0Energy                             = corrJet.energy()    ;                  
      Jet0Mass                               = corrJet.mass()      ;                    
      Jet0Area                               = ijet.jetArea()      ;                  
      Jet0MassSoftDrop                       = softDropMass;               
      Jet0MassSDsumSubjetRaw                 = sumSDsubjets_P4_uncorr.M()             ;
      Jet0MassSDsumSubjetCorrL23             = sumSDsubjets_P4_L23res.M()             ;  
      Jet0MassSDsumSubjetCorrL23Up           = sumSDsubjets_P4_corrUp_L23res.M()      ;  
      Jet0MassSDsumSubjetCorrL23Dn           = sumSDsubjets_P4_corrDn_L23res.M()      ;
      Jet0MassSDsumSubjetCorrL123            = sumSDsubjets_P4_L123res.M()            ; 
      Jet0MassSDsumSubjetCorrL123Up          = sumSDsubjets_P4_corrUp_L123res.M()     ;  
      Jet0MassSDsumSubjetCorrL123Dn          = sumSDsubjets_P4_corrDn_L123res.M()     ; 
      Jet0MassSDsumSubjetCorrSmear           = 1 ; // need to get some gen subjets 
      Jet0MassSDsumSubjetCorrSmearUp         = 1 ; // need to get some gen subjets 
      Jet0MassSDsumSubjetCorrSmearDn         = 1 ; // need to get some gen subjets 
      Jet0MassPruned                         = prunedMass ;     
      Jet0Tau1                               = tau1 ;  
      Jet0Tau2                               = tau2 ;  
      Jet0Tau3                               = tau3 ;  
      Jet0Tau32                              = tau32 ;  
      Jet0Tau21                              = tau21 ;  
      Jet0SDsubjet0bdisc                     = sub0_bdisc ;  
      Jet0SDsubjet1bdisc                     = sub1_bdisc ;   
      Jet0SDmaxbdisc                         = maxbdisc;
      Jet0SDmaxbdiscflavHadron               = maxbdiscflav_hadron;  
      Jet0SDmaxbdiscflavParton               = maxbdiscflav_parton;  
      Jet0SDsubjet0pt                        = sub0_P4_uncorr.Pt() ;               
      Jet0SDsubjet0mass                      = sub0_P4_uncorr.M()  ;  
      Jet0SDsubjet0eta                       = sub0_P4_uncorr.Eta()  ;  
      Jet0SDsubjet0phi                       = sub0_P4_uncorr.Phi()  ;  
      Jet0SDsubjet0area                      = sub0_area ;  
      Jet0SDsubjet0flavHadron                = sub0_flav_hadron ;  
      Jet0SDsubjet0flavParton                = sub0_flav_parton ;  
      Jet0SDsubjet0tau1                      = sub0_tau1 ;  
      Jet0SDsubjet0tau2                      = sub0_tau2 ;  
      Jet0SDsubjet0tau3                      = sub0_tau3 ;  
      Jet0SDsubjet1pt                        = sub1_P4_uncorr.Pt() ;                    
      Jet0SDsubjet1mass                      = sub1_P4_uncorr.M()  ; 
      Jet0SDsubjet1eta                       = sub1_P4_uncorr.Eta()  ;  
      Jet0SDsubjet1phi                       = sub1_P4_uncorr.Phi()  ;                     
      Jet0SDsubjet1area                      = sub1_area ;                    
      Jet0SDsubjet1flavHadron                = sub1_flav_hadron ;     
      Jet0SDsubjet1flavParton                = sub1_flav_parton ;     
      Jet0SDsubjet1tau1                      = sub1_tau1 ;  
      Jet0SDsubjet1tau2                      = sub1_tau2 ;  
      Jet0SDsubjet1tau3                      = sub1_tau3 ; 

      Jet0PuppiPt                            = puppi_pt   ;                  
      Jet0PuppiEta                           = puppi_eta  ;                   
      Jet0PuppiPhi                           = puppi_phi  ;                  
      Jet0PuppiMass                          = puppi_mass ;                  
      Jet0PuppiMassSoftDrop                  = sumPUPsubjets_P4_uncorr.M() ;
      Jet0PuppiMassSDsumSubjetRaw            = sumPUPsubjets_P4_uncorr.M() ;
      Jet0PuppiMassSDsumSubjetCorr           = sumPUPsubjets_P4_L23res.M() ;   
      Jet0PuppiMassSDsumSubjetCorrUp         = sumPUPsubjets_P4_corrUp_L23res.M() ;
      Jet0PuppiMassSDsumSubjetCorrDn         = sumPUPsubjets_P4_corrDn_L23res.M() ;
      Jet0PuppiMassSDsumSubjetCorrSmear      = 1;
      Jet0PuppiMassSDsumSubjetCorrSmearUp    = 1;
      Jet0PuppiMassSDsumSubjetCorrSmearDn    = 1;
      Jet0PuppiTau1                          = puppi_tau1       ;                  
      Jet0PuppiTau2                          = puppi_tau2       ;                  
      Jet0PuppiTau3                          = puppi_tau3       ;                  
      Jet0PuppiTau32                         = puppi_tau32      ;                  
      Jet0PuppiTau21                         = puppi_tau21      ;                  
      Jet0PuppiSDsubjet0bdisc                = pup0_bdisc       ;
      Jet0PuppiSDsubjet1bdisc                = pup1_bdisc       ;
      Jet0PuppiSDmaxbdisc                    = pup_maxbdisc     ;
      Jet0PuppiSDmaxbdiscflavHadron          = pup_maxbdiscflav_hadron ;
      Jet0PuppiSDmaxbdiscflavParton          = pup_maxbdiscflav_parton ;
      Jet0PuppiSDsubjet0pt                   = pup0_P4_uncorr.Pt()        ;
      Jet0PuppiSDsubjet0mass                 = pup0_P4_uncorr.M()         ;
      Jet0PuppiSDsubjet0eta                  = pup0_P4_uncorr.Eta()         ;
      Jet0PuppiSDsubjet0phi                  = pup0_P4_uncorr.Phi()         ;
      Jet0PuppiSDsubjet0area                 = pup0_area        ;
      Jet0PuppiSDsubjet0flavHadron           = pup0_flav_hadron        ;
      Jet0PuppiSDsubjet0flavParton           = pup0_flav_parton        ;
      Jet0PuppiSDsubjet0tau1                 = pup0_tau1 ;  
      Jet0PuppiSDsubjet0tau2                 = pup0_tau2 ;  
      Jet0PuppiSDsubjet0tau3                 = pup0_tau3 ; 
      Jet0PuppiSDsubjet1pt                   = pup1_P4_uncorr.Pt()        ;                 
      Jet0PuppiSDsubjet1mass                 = pup1_P4_uncorr.M()         ; 
      Jet0PuppiSDsubjet1eta                  = pup1_P4_uncorr.Eta()         ;
      Jet0PuppiSDsubjet1phi                  = pup1_P4_uncorr.Phi()         ;             
      Jet0PuppiSDsubjet1area                 = pup1_area        ;              
      Jet0PuppiSDsubjet1flavHadron           = pup1_flav_hadron        ;   
      Jet0PuppiSDsubjet1flavParton           = pup1_flav_parton        ;   
      Jet0PuppiSDsubjet1tau1                 = pup1_tau1 ;  
      Jet0PuppiSDsubjet1tau2                 = pup1_tau2 ;  
      Jet0PuppiSDsubjet1tau3                 = pup1_tau3 ; 

      Jet0CHF                                = ijet.chargedHadronEnergy() / uncorrJet.E()  ;                        
      Jet0NHF                                = ijet.neutralHadronEnergy() / uncorrJet.E()  ;                         
      Jet0CM                                 = ijet.chargedMultiplicity()  ;                         
      Jet0NM                                 = ijet.neutralMultiplicity()  ;                          
      Jet0NEF                                = ijet.neutralEmEnergy() / uncorrJet.E()  ;                            
      Jet0CEF                                = ijet.chargedEmEnergy() / uncorrJet.E()  ;                          
      Jet0MF                                 = ijet.muonEnergy() / uncorrJet.E()  ;                         
      Jet0Mult                               = ijet.numberOfDaughters() ;   

      Jet0MassCorrFactor                     = corr_factor_L23res ;        
      Jet0MassCorrFactorUp                   = corrUp_L23 ;
      Jet0MassCorrFactorDn                   = corrDn_L23 ;
      Jet0CorrFactor                         = corr ;        
      Jet0CorrFactorUp                       = corrUp_L123 ;
      Jet0CorrFactorDn                       = corrDn_L123;
      Jet0PtSmearFactor                      = ptsmear  ;
      Jet0PtSmearFactorUp                    = ptsmearUp;
      Jet0PtSmearFactorDn                    = ptsmearDn;
      Jet0PuppiMassCorrFactor                = 1;          
      Jet0PuppiMassCorrFactorUp              = 1;          
      Jet0PuppiMassCorrFactorDn              = 1;          
      Jet0PuppiCorrFactor                    = 1;          
      Jet0PuppiCorrFactorUp                  = 1;          
      Jet0PuppiCorrFactorDn                  = 1;          
      Jet0PuppiPtSmearFactor                 = 1;          
      Jet0PuppiPtSmearFactorUp               = 1;          
      Jet0PuppiPtSmearFactorDn               = 1;          
      Jet0EtaScaleFactor                     = 1;          
      Jet0PhiScaleFactor                     = 1;          
      Jet0MatchedGenJetDR                    = GenJetMatched_dRmin;             
      Jet0MatchedGenJetPt                    = GenJetMatched.Perp();       
      Jet0MatchedGenJetMass                  = GenJetMatched.M();   

      if (!iEvent.isRealData() and runGenLoop_) {
        if (counttop==2 && jet_matched_t1){
          if (top1hadronic) Jet0GenMatched_TopHadronic         = 1     ;
          else Jet0GenMatched_TopHadronic                      = 0     ;
          Jet0GenMatched_TopPt               = t1_p4.Perp()                   ;
          Jet0GenMatched_TopEta              = t1_p4.Eta()                    ;
          Jet0GenMatched_TopPhi              = t1_p4.Phi()                    ;
          Jet0GenMatched_TopMass             = t1_p4.M()                      ;
          Jet0GenMatched_bPt                 = b1_p4.Perp()                   ;
          Jet0GenMatched_WPt                 = W1_p4.Perp()                   ;
          Jet0GenMatched_Wd1Pt               = W1d1_p4.Perp()                 ;
          Jet0GenMatched_Wd2Pt               = W1d2_p4.Perp()                 ;
          Jet0GenMatched_Wd1ID               = W1d1_id                        ;
          Jet0GenMatched_Wd2ID               = W1d2_id                        ;
          Jet0GenMatched_MaxDeltaRPartonTop  = max_deltaR_parton_t1           ;
          Jet0GenMatched_MaxDeltaRWPartonTop = max_deltaR_Wparton_t1          ;
          Jet0GenMatched_MaxDeltaRWPartonW   = max_deltaR_Wparton_W1          ;
          Jet0GenMatched_DeltaR_t_b          = deltaR_t1_b1                   ;
          Jet0GenMatched_DeltaR_t_W          = deltaR_t1_W1                   ;
          Jet0GenMatched_DeltaR_t_Wd1        = deltaR_t1_W1d1                 ;
          Jet0GenMatched_DeltaR_t_Wd2        = deltaR_t1_W1d2                 ;
          Jet0GenMatched_DeltaR_W_b1         = deltaR_W1_b1                   ;
          Jet0GenMatched_DeltaR_W_Wd1        = deltaR_W1_W1d1                 ;
          Jet0GenMatched_DeltaR_W_Wd2        = deltaR_W1_W1d2                 ;
          Jet0GenMatched_DeltaR_Wd1_Wd2      = deltaR_W1d1_W1d2               ;
          Jet0GenMatched_DeltaR_Wd1_b        = deltaR_W1d1_b1                 ;
          Jet0GenMatched_DeltaR_Wd2_b        = deltaR_W1d2_b1                 ;
          Jet0GenMatched_DeltaR_jet_t        = deltaR_jet_t1                  ;
          Jet0GenMatched_DeltaR_jet_W        = jet_p4.DeltaR(W1_p4  )         ;
          Jet0GenMatched_DeltaR_jet_b        = jet_p4.DeltaR(b1_p4  )         ;
          Jet0GenMatched_DeltaR_jet_Wd1      = jet_p4.DeltaR(W1d1_p4)         ;
          Jet0GenMatched_DeltaR_jet_Wd2      = jet_p4.DeltaR(W1d2_p4)         ;
          Jet0GenMatched_DeltaR_pup0_b       = pup0_P4_L23res.DeltaR(b1_p4)   ;
          Jet0GenMatched_DeltaR_pup0_Wd1     = pup0_P4_L23res.DeltaR(W1d1_p4) ;
          Jet0GenMatched_DeltaR_pup0_Wd2     = pup0_P4_L23res.DeltaR(W1d2_p4) ;
          Jet0GenMatched_DeltaR_pup1_b       = pup1_P4_L23res.DeltaR(b1_p4)   ;
          Jet0GenMatched_DeltaR_pup1_Wd1     = pup1_P4_L23res.DeltaR(W1d1_p4) ;
          Jet0GenMatched_DeltaR_pup1_Wd2     = pup1_P4_L23res.DeltaR(W1d2_p4) ;
        }   
        if (counttop==2 && jet_matched_t2){
          if (top2hadronic) Jet0GenMatched_TopHadronic         = 1           ;
          else Jet0GenMatched_TopHadronic                      = 0           ;
          Jet0GenMatched_TopPt               = t2_p4.Perp()           ;
          Jet0GenMatched_TopEta              = t2_p4.Eta()            ;
          Jet0GenMatched_TopPhi              = t2_p4.Phi()            ;
          Jet0GenMatched_TopMass             = t2_p4.M()              ;
          Jet0GenMatched_bPt                 = b2_p4.Perp()           ;
          Jet0GenMatched_WPt                 = W2_p4.Perp()           ;
          Jet0GenMatched_Wd1Pt               = W2d1_p4.Perp()         ;
          Jet0GenMatched_Wd2Pt               = W2d2_p4.Perp()         ;
          Jet0GenMatched_Wd1ID               = W2d1_id                ;
          Jet0GenMatched_Wd2ID               = W2d2_id                ;
          Jet0GenMatched_MaxDeltaRPartonTop  = max_deltaR_parton_t2   ;
          Jet0GenMatched_MaxDeltaRWPartonTop = max_deltaR_Wparton_t2  ;
          Jet0GenMatched_MaxDeltaRWPartonW   = max_deltaR_Wparton_W2  ;
          Jet0GenMatched_DeltaR_t_b          = deltaR_t2_b2           ;
          Jet0GenMatched_DeltaR_t_W          = deltaR_t2_W2           ;
          Jet0GenMatched_DeltaR_t_Wd1        = deltaR_t2_W2d1         ;
          Jet0GenMatched_DeltaR_t_Wd2        = deltaR_t2_W2d2         ;
          Jet0GenMatched_DeltaR_W_b1         = deltaR_W2_b2           ;
          Jet0GenMatched_DeltaR_W_Wd1        = deltaR_W2_W2d1         ;
          Jet0GenMatched_DeltaR_W_Wd2        = deltaR_W2_W2d2         ;
          Jet0GenMatched_DeltaR_Wd1_Wd2      = deltaR_W2d1_W2d2       ;
          Jet0GenMatched_DeltaR_Wd1_b        = deltaR_W2d1_b2         ;
          Jet0GenMatched_DeltaR_Wd2_b        = deltaR_W2d2_b2         ;
          Jet0GenMatched_DeltaR_jet_t        = deltaR_jet_t2          ;
          Jet0GenMatched_DeltaR_jet_W        = jet_p4.DeltaR(W2_p4  ) ;
          Jet0GenMatched_DeltaR_jet_b        = jet_p4.DeltaR(b2_p4  ) ;
          Jet0GenMatched_DeltaR_jet_Wd1      = jet_p4.DeltaR(W2d1_p4) ;
          Jet0GenMatched_DeltaR_jet_Wd2      = jet_p4.DeltaR(W2d2_p4) ;
          Jet0GenMatched_DeltaR_pup0_b       = pup0_P4_L23res.DeltaR(b2_p4)   ;
          Jet0GenMatched_DeltaR_pup0_Wd1     = pup0_P4_L23res.DeltaR(W2d1_p4) ;
          Jet0GenMatched_DeltaR_pup0_Wd2     = pup0_P4_L23res.DeltaR(W2d2_p4) ;
          Jet0GenMatched_DeltaR_pup1_b       = pup1_P4_L23res.DeltaR(b2_p4)   ;
          Jet0GenMatched_DeltaR_pup1_Wd1     = pup1_P4_L23res.DeltaR(W2d1_p4) ;
          Jet0GenMatched_DeltaR_pup1_Wd2     = pup1_P4_L23res.DeltaR(W2d2_p4) ;
        }
        if (counttop==0 && jet_matched_p1){
          Jet0GenMatched_partonPt               = hardest_parton_hardScatterOutgoing_p4.Perp()           ;
          Jet0GenMatched_partonEta              = hardest_parton_hardScatterOutgoing_p4.Eta()            ;
          Jet0GenMatched_partonPhi              = hardest_parton_hardScatterOutgoing_p4.Phi()            ;
          Jet0GenMatched_partonMass             = hardest_parton_hardScatterOutgoing_p4.M()              ;
          Jet0GenMatched_partonID               = parton1id                                              ;
          Jet0GenMatched_DeltaRjetParton        = deltaR_jet_p1                                          ;
        }
        if (counttop==0 && jet_matched_p2){
          Jet0GenMatched_partonPt               = second_hardest_parton_hardScatterOutgoing_p4.Perp()    ;
          Jet0GenMatched_partonEta              = second_hardest_parton_hardScatterOutgoing_p4.Eta()     ;
          Jet0GenMatched_partonPhi              = second_hardest_parton_hardScatterOutgoing_p4.Phi()     ;
          Jet0GenMatched_partonMass             = second_hardest_parton_hardScatterOutgoing_p4.M()       ;
          Jet0GenMatched_partonID               = parton2id                                              ;
          Jet0GenMatched_DeltaRjetParton        = deltaR_jet_p2                                          ;
        }
      }
    }   
    if (count_AK8CHS==1){
      Jet1PtRaw                              = uncorrJet.pt()      ;                 
      Jet1EtaRaw                             = uncorrJet.eta()     ;                  
      Jet1PhiRaw                             = uncorrJet.phi()     ;   
      Jet1MassRaw                            = uncorrJet.mass()    ;                                           
      Jet1P                                  = corrJet.P()         ;        
      Jet1Pt                                 = corrJet.pt()        ;                  
      Jet1Eta                                = corrJet.eta()       ;                  
      Jet1Phi                                = corrJet.phi()       ;                  
      Jet1Rap                                = corrJet.Rapidity()  ;                  
      Jet1Energy                             = corrJet.energy()    ;                  
      Jet1Mass                               = corrJet.mass()      ;                    
      Jet1Area                               = ijet.jetArea()      ;                  
      Jet1MassSoftDrop                       = softDropMass        ;               
      Jet1MassSDsumSubjetRaw                 = sumSDsubjets_P4_uncorr.M()              ;
      Jet1MassSDsumSubjetCorrL23             = sumSDsubjets_P4_L23res.M()              ;  
      Jet1MassSDsumSubjetCorrL23Up           = sumSDsubjets_P4_corrUp_L23res.M()       ;  
      Jet1MassSDsumSubjetCorrL23Dn           = sumSDsubjets_P4_corrDn_L23res.M()       ;
      Jet1MassSDsumSubjetCorrL123            = sumSDsubjets_P4_L123res.M()             ; 
      Jet1MassSDsumSubjetCorrL123Up          = sumSDsubjets_P4_corrUp_L123res.M()      ;  
      Jet1MassSDsumSubjetCorrL123Dn          = sumSDsubjets_P4_corrDn_L123res.M()      ; 
      Jet1MassSDsumSubjetCorrSmear           = 1 ; // need to get some gen subjets 
      Jet1MassSDsumSubjetCorrSmearUp         = 1 ; // need to get some gen subjets 
      Jet1MassSDsumSubjetCorrSmearDn         = 1 ; // need to get some gen subjets 
      Jet1MassPruned                         = prunedMass ;     
      Jet1Tau1                               = tau1 ;  
      Jet1Tau2                               = tau2 ;  
      Jet1Tau3                               = tau3 ;  
      Jet1Tau32                              = tau32 ;  
      Jet1Tau21                              = tau21 ;  
      Jet1SDsubjet0bdisc                     = sub0_bdisc ;  
      Jet1SDsubjet1bdisc                     = sub1_bdisc ;   
      Jet1SDmaxbdisc                         = maxbdisc;
      Jet1SDmaxbdiscflavHadron               = maxbdiscflav_hadron;  
      Jet1SDmaxbdiscflavParton               = maxbdiscflav_parton;  
      Jet1SDsubjet0pt                        = sub0_P4_uncorr.Pt() ;               
      Jet1SDsubjet0mass                      = sub0_P4_uncorr.M()  ;  
      Jet1SDsubjet0eta                       = sub0_P4_uncorr.Eta()  ;  
      Jet1SDsubjet0phi                       = sub0_P4_uncorr.Phi()  ;  
      Jet1SDsubjet0area                      = sub0_area ;  
      Jet1SDsubjet0flavHadron                = sub0_flav_hadron ;  
      Jet1SDsubjet0flavParton                = sub0_flav_parton ;  
      Jet1SDsubjet0tau1                      = sub0_tau1 ;  
      Jet1SDsubjet0tau2                      = sub0_tau2 ;  
      Jet1SDsubjet0tau3                      = sub0_tau3 ;  
      Jet1SDsubjet1pt                        = sub1_P4_uncorr.Pt() ;                    
      Jet1SDsubjet1mass                      = sub1_P4_uncorr.M()  ;                    
      Jet1SDsubjet1eta                       = sub1_P4_uncorr.Eta()  ;                    
      Jet1SDsubjet1phi                       = sub1_P4_uncorr.Phi()  ;                    
      Jet1SDsubjet1area                      = sub1_area ;                    
      Jet1SDsubjet1flavHadron                = sub1_flav_hadron ;     
      Jet1SDsubjet1flavParton                = sub1_flav_parton ;     
      Jet1SDsubjet1tau1                      = sub1_tau1 ;  
      Jet1SDsubjet1tau2                      = sub1_tau2 ;  
      Jet1SDsubjet1tau3                      = sub1_tau3 ;

      Jet1PuppiPt                            = puppi_pt   ;                  
      Jet1PuppiEta                           = puppi_eta  ;                   
      Jet1PuppiPhi                           = puppi_phi  ;                  
      Jet1PuppiMass                          = puppi_mass ;                  
      Jet1PuppiMassSoftDrop                  = sumPUPsubjets_P4_uncorr.M() ;
      Jet1PuppiMassSDsumSubjetRaw            = sumPUPsubjets_P4_uncorr.M() ;
      Jet1PuppiMassSDsumSubjetCorr           = sumPUPsubjets_P4_L23res.M() ;   
      Jet1PuppiMassSDsumSubjetCorrUp         = sumPUPsubjets_P4_corrUp_L23res.M() ;
      Jet1PuppiMassSDsumSubjetCorrDn         = sumPUPsubjets_P4_corrDn_L23res.M() ;
      Jet1PuppiMassSDsumSubjetCorrSmear      = 1;
      Jet1PuppiMassSDsumSubjetCorrSmearUp    = 1;
      Jet1PuppiMassSDsumSubjetCorrSmearDn    = 1;
      Jet1PuppiTau1                          = puppi_tau1       ;                  
      Jet1PuppiTau2                          = puppi_tau2       ;                  
      Jet1PuppiTau3                          = puppi_tau3       ;                  
      Jet1PuppiTau32                         = puppi_tau32      ;                  
      Jet1PuppiTau21                         = puppi_tau21      ;                  
      Jet1PuppiSDsubjet0bdisc                = pup0_bdisc       ;
      Jet1PuppiSDsubjet1bdisc                = pup1_bdisc       ;
      Jet1PuppiSDmaxbdisc                    = pup_maxbdisc     ;
      Jet1PuppiSDmaxbdiscflavHadron          = pup_maxbdiscflav_hadron    ;
      Jet1PuppiSDmaxbdiscflavParton          = pup_maxbdiscflav_parton    ;
      Jet1PuppiSDsubjet0pt                   = pup0_P4_uncorr.Pt()        ;
      Jet1PuppiSDsubjet0mass                 = pup0_P4_uncorr.M()         ;
      Jet1PuppiSDsubjet0eta                  = pup0_P4_uncorr.Eta()       ;
      Jet1PuppiSDsubjet0phi                  = pup0_P4_uncorr.Phi()       ;
      Jet1PuppiSDsubjet0area                 = pup0_area                  ;
      Jet1PuppiSDsubjet0flavHadron           = pup0_flav_hadron           ;
      Jet1PuppiSDsubjet0flavParton           = pup0_flav_parton           ;
      Jet1PuppiSDsubjet0tau1                 = pup0_tau1                  ;
      Jet1PuppiSDsubjet0tau2                 = pup0_tau2                  ;
      Jet1PuppiSDsubjet0tau3                 = pup0_tau3                  ;
      Jet1PuppiSDsubjet1pt                   = pup1_P4_uncorr.Pt()        ;                 
      Jet1PuppiSDsubjet1mass                 = pup1_P4_uncorr.M()         ;              
      Jet1PuppiSDsubjet1eta                  = pup1_P4_uncorr.Eta()       ;              
      Jet1PuppiSDsubjet1phi                  = pup1_P4_uncorr.Phi()       ;              
      Jet1PuppiSDsubjet1area                 = pup1_area                  ;              
      Jet1PuppiSDsubjet1flavHadron           = pup1_flav_hadron           ;   
      Jet1PuppiSDsubjet1flavParton           = pup1_flav_parton           ;   
      Jet1PuppiSDsubjet1tau1                 = pup1_tau1                  ;
      Jet1PuppiSDsubjet1tau2                 = pup1_tau2                  ;
      Jet1PuppiSDsubjet1tau3                 = pup1_tau3                  ;

      Jet1CHF                                = ijet.chargedHadronEnergy() / uncorrJet.E()  ;                        
      Jet1NHF                                = ijet.neutralHadronEnergy() / uncorrJet.E()  ;                         
      Jet1CM                                 = ijet.chargedMultiplicity()                  ;                         
      Jet1NM                                 = ijet.neutralMultiplicity()                  ;                          
      Jet1NEF                                = ijet.neutralEmEnergy() / uncorrJet.E()      ;                            
      Jet1CEF                                = ijet.chargedEmEnergy() / uncorrJet.E()      ;                          
      Jet1MF                                 = ijet.muonEnergy() / uncorrJet.E()           ;                         
      Jet1Mult                               = ijet.numberOfDaughters()                    ;   

      Jet1MassCorrFactor                     = corr_factor_L23res ;        
      Jet1MassCorrFactorUp                   = corrUp_L23 ;
      Jet1MassCorrFactorDn                   = corrDn_L23 ;
      Jet1CorrFactor                         = corr ;        
      Jet1CorrFactorUp                       = corrUp_L123 ;
      Jet1CorrFactorDn                       = corrDn_L123;
      Jet1PtSmearFactor                      = ptsmear  ;
      Jet1PtSmearFactorUp                    = ptsmearUp;
      Jet1PtSmearFactorDn                    = ptsmearDn;
      Jet1PuppiMassCorrFactor                = 1;          
      Jet1PuppiMassCorrFactorUp              = 1;          
      Jet1PuppiMassCorrFactorDn              = 1;          
      Jet1PuppiCorrFactor                    = 1;          
      Jet1PuppiCorrFactorUp                  = 1;          
      Jet1PuppiCorrFactorDn                  = 1;          
      Jet1PuppiPtSmearFactor                 = 1;          
      Jet1PuppiPtSmearFactorUp               = 1;          
      Jet1PuppiPtSmearFactorDn               = 1;          
      Jet1EtaScaleFactor                     = 1;          
      Jet1PhiScaleFactor                     = 1;          
      Jet1MatchedGenJetDR                    = GenJetMatched_dRmin;             
      Jet1MatchedGenJetPt                    = GenJetMatched.Perp();       
      Jet1MatchedGenJetMass                  = GenJetMatched.M();   

      if (!iEvent.isRealData() and runGenLoop_) {
        if (counttop==2 && jet_matched_t1){
          if (top1hadronic) Jet1GenMatched_TopHadronic         = 1      ;
          else Jet1GenMatched_TopHadronic                      = 0      ;
          Jet1GenMatched_TopPt               = t1_p4.Perp()                   ;
          Jet1GenMatched_TopEta              = t1_p4.Eta()                    ;
          Jet1GenMatched_TopPhi              = t1_p4.Phi()                    ;
          Jet1GenMatched_TopMass             = t1_p4.M()                      ;
          Jet1GenMatched_bPt                 = b1_p4.Perp()                   ;
          Jet1GenMatched_WPt                 = W1_p4.Perp()                   ;
          Jet1GenMatched_Wd1Pt               = W1d1_p4.Perp()                 ;
          Jet1GenMatched_Wd2Pt               = W1d2_p4.Perp()                 ;
          Jet1GenMatched_Wd1ID               = W1d1_id                        ;
          Jet1GenMatched_Wd2ID               = W1d2_id                        ;
          Jet1GenMatched_MaxDeltaRPartonTop  = max_deltaR_parton_t1           ;
          Jet1GenMatched_MaxDeltaRWPartonTop = max_deltaR_Wparton_t1          ;
          Jet1GenMatched_MaxDeltaRWPartonW   = max_deltaR_Wparton_W1          ;
          Jet1GenMatched_DeltaR_t_b          = deltaR_t1_b1                   ;
          Jet1GenMatched_DeltaR_t_W          = deltaR_t1_W1                   ;
          Jet1GenMatched_DeltaR_t_Wd1        = deltaR_t1_W1d1                 ;
          Jet1GenMatched_DeltaR_t_Wd2        = deltaR_t1_W1d2                 ;
          Jet1GenMatched_DeltaR_W_b1         = deltaR_W1_b1                   ;
          Jet1GenMatched_DeltaR_W_Wd1        = deltaR_W1_W1d1                 ;
          Jet1GenMatched_DeltaR_W_Wd2        = deltaR_W1_W1d2                 ;
          Jet1GenMatched_DeltaR_Wd1_Wd2      = deltaR_W1d1_W1d2               ;
          Jet1GenMatched_DeltaR_Wd1_b        = deltaR_W1d1_b1                 ;
          Jet1GenMatched_DeltaR_Wd2_b        = deltaR_W1d2_b1                 ;
          Jet1GenMatched_DeltaR_jet_t        = deltaR_jet_t1                  ;
          Jet1GenMatched_DeltaR_jet_W        = jet_p4.DeltaR(W1_p4  )         ;
          Jet1GenMatched_DeltaR_jet_b        = jet_p4.DeltaR(b1_p4  )         ;
          Jet1GenMatched_DeltaR_jet_Wd1      = jet_p4.DeltaR(W1d1_p4)         ;
          Jet1GenMatched_DeltaR_jet_Wd2      = jet_p4.DeltaR(W1d2_p4)         ;
          Jet1GenMatched_DeltaR_pup0_b       = pup0_P4_L23res.DeltaR(b1_p4)   ;
          Jet1GenMatched_DeltaR_pup0_Wd1     = pup0_P4_L23res.DeltaR(W1d1_p4) ;
          Jet1GenMatched_DeltaR_pup0_Wd2     = pup0_P4_L23res.DeltaR(W1d2_p4) ;
          Jet1GenMatched_DeltaR_pup1_b       = pup1_P4_L23res.DeltaR(b1_p4)   ;
          Jet1GenMatched_DeltaR_pup1_Wd1     = pup1_P4_L23res.DeltaR(W1d1_p4) ;
          Jet1GenMatched_DeltaR_pup1_Wd2     = pup1_P4_L23res.DeltaR(W1d2_p4) ;
        }   
        if (counttop==2 && jet_matched_t2){
          if (top2hadronic) Jet1GenMatched_TopHadronic         = 1           ;
          else              Jet1GenMatched_TopHadronic         = 0           ;
          Jet1GenMatched_TopPt               = t2_p4.Perp()           ;
          Jet1GenMatched_TopEta              = t2_p4.Eta()            ;
          Jet1GenMatched_TopPhi              = t2_p4.Phi()            ;
          Jet1GenMatched_TopMass             = t2_p4.M()              ;
          Jet1GenMatched_bPt                 = b2_p4.Perp()           ;
          Jet1GenMatched_WPt                 = W2_p4.Perp()           ;
          Jet1GenMatched_Wd1Pt               = W2d1_p4.Perp()         ;
          Jet1GenMatched_Wd2Pt               = W2d2_p4.Perp()         ;
          Jet1GenMatched_Wd1ID               = W2d1_id                ;
          Jet1GenMatched_Wd2ID               = W2d2_id                ;
          Jet1GenMatched_MaxDeltaRPartonTop  = max_deltaR_parton_t2   ;
          Jet1GenMatched_MaxDeltaRWPartonTop = max_deltaR_Wparton_t2  ;
          Jet1GenMatched_MaxDeltaRWPartonW   = max_deltaR_Wparton_W2  ;
          Jet1GenMatched_DeltaR_t_b          = deltaR_t2_b2           ;
          Jet1GenMatched_DeltaR_t_W          = deltaR_t2_W2           ;
          Jet1GenMatched_DeltaR_t_Wd1        = deltaR_t2_W2d1         ;
          Jet1GenMatched_DeltaR_t_Wd2        = deltaR_t2_W2d2         ;
          Jet1GenMatched_DeltaR_W_b1         = deltaR_W2_b2           ;
          Jet1GenMatched_DeltaR_W_Wd1        = deltaR_W2_W2d1         ;
          Jet1GenMatched_DeltaR_W_Wd2        = deltaR_W2_W2d2         ;
          Jet1GenMatched_DeltaR_Wd1_Wd2      = deltaR_W2d1_W2d2       ;
          Jet1GenMatched_DeltaR_Wd1_b        = deltaR_W2d1_b2         ;
          Jet1GenMatched_DeltaR_Wd2_b        = deltaR_W2d2_b2         ;
          Jet1GenMatched_DeltaR_jet_t        = deltaR_jet_t2          ;
          Jet1GenMatched_DeltaR_jet_W        = jet_p4.DeltaR(W2_p4  ) ;
          Jet1GenMatched_DeltaR_jet_b        = jet_p4.DeltaR(b2_p4  ) ;
          Jet1GenMatched_DeltaR_jet_Wd1      = jet_p4.DeltaR(W2d1_p4) ;
          Jet1GenMatched_DeltaR_jet_Wd2      = jet_p4.DeltaR(W2d2_p4) ;
          Jet1GenMatched_DeltaR_pup0_b       = pup0_P4_L23res.DeltaR(b2_p4)   ;
          Jet1GenMatched_DeltaR_pup0_Wd1     = pup0_P4_L23res.DeltaR(W2d1_p4) ;
          Jet1GenMatched_DeltaR_pup0_Wd2     = pup0_P4_L23res.DeltaR(W2d2_p4) ;
          Jet1GenMatched_DeltaR_pup1_b       = pup1_P4_L23res.DeltaR(b2_p4)   ;
          Jet1GenMatched_DeltaR_pup1_Wd1     = pup1_P4_L23res.DeltaR(W2d1_p4) ;
          Jet1GenMatched_DeltaR_pup1_Wd2     = pup1_P4_L23res.DeltaR(W2d2_p4) ;
        }
        if (counttop==0 && jet_matched_p1){
          Jet1GenMatched_partonPt               = hardest_parton_hardScatterOutgoing_p4.Perp()           ;
          Jet1GenMatched_partonEta              = hardest_parton_hardScatterOutgoing_p4.Eta()            ;
          Jet1GenMatched_partonPhi              = hardest_parton_hardScatterOutgoing_p4.Phi()            ;
          Jet1GenMatched_partonMass             = hardest_parton_hardScatterOutgoing_p4.M()              ;
          Jet1GenMatched_partonID               = parton1id                                              ;
          Jet1GenMatched_DeltaRjetParton        = deltaR_jet_p1                                          ;
        }
        if (counttop==0 && jet_matched_p2){
          Jet1GenMatched_partonPt               = second_hardest_parton_hardScatterOutgoing_p4.Perp()    ;
          Jet1GenMatched_partonEta              = second_hardest_parton_hardScatterOutgoing_p4.Eta()     ;
          Jet1GenMatched_partonPhi              = second_hardest_parton_hardScatterOutgoing_p4.Phi()     ;
          Jet1GenMatched_partonMass             = second_hardest_parton_hardScatterOutgoing_p4.M()       ;
          Jet1GenMatched_partonID               = parton2id                                              ;
          Jet1GenMatched_DeltaRjetParton        = deltaR_jet_p2                                          ;
        }
      }   
    } 


    //------------------------------------
    // Fill SemiLeptTree
    //------------------------------------ 
    int fill_leptTree =0;

    double deltaPhi_lep_jet = deltaPhi(corrJet.phi(), lep0_p4.Phi() ) ;
    // AK8 jet should be in opposite hemisphere from lepton. If leading jet matches don't enter this if again. If it doensn't then check the second leading jet.
    if ( ((count_AK8CHS==0&&deltaPhi_lep_jet >=3.14/2) || (count_AK8CHS==1&&deltaPhi_lep_jet >=3.14/2)) && count_mu >=1 && fill_leptTree==0 ){
      fill_leptTree++;
      DeltaRJetLep                          = deltaR(corrJet.eta(), corrJet.phi(), lep0_p4.Eta(), lep0_p4.Phi() );
      DeltaPhiJetLep                        = deltaPhi_lep_jet;
      JetPtRaw                              = uncorrJet.pt()      ;                 
      JetEtaRaw                             = uncorrJet.eta()     ;                  
      JetPhiRaw                             = uncorrJet.phi()     ;   
      JetMassRaw                            = uncorrJet.mass()    ;                                           
      JetP                                  = corrJet.P()         ;        
      JetPt                                 = corrJet.pt()        ;                  
      JetEta                                = corrJet.eta()       ;                  
      JetPhi                                = corrJet.phi()       ;                  
      JetRap                                = corrJet.Rapidity()  ;                  
      JetEnergy                             = corrJet.energy()    ;                  
      JetMass                               = corrJet.mass()      ;                    
      JetArea                               = ijet.jetArea()      ;                  
      JetMassSoftDrop                       = softDropMass        ;               
      JetMassSDsumSubjetRaw                 = sumSDsubjets_P4_uncorr.M()             ;
      JetMassSDsumSubjetCorrL23             = sumSDsubjets_P4_L23res.M()             ;  
      JetMassSDsumSubjetCorrL23Up           = sumSDsubjets_P4_corrUp_L23res.M()      ;  
      JetMassSDsumSubjetCorrL23Dn           = sumSDsubjets_P4_corrDn_L23res.M()      ;
      JetMassSDsumSubjetCorrL123            = sumSDsubjets_P4_L123res.M()            ; 
      JetMassSDsumSubjetCorrL123Up          = sumSDsubjets_P4_corrUp_L123res.M()     ;  
      JetMassSDsumSubjetCorrL123Dn          = sumSDsubjets_P4_corrDn_L123res.M()     ; 
      JetMassSDsumSubjetCorrSmear           = 1 ; // need to get some gen subjets 
      JetMassSDsumSubjetCorrSmearUp         = 1 ; // need to get some gen subjets 
      JetMassSDsumSubjetCorrSmearDn         = 1 ; // need to get some gen subjets 
      JetMassPruned                         = prunedMass ;     
      JetTau1                               = tau1 ;  
      JetTau2                               = tau2 ;  
      JetTau3                               = tau3 ;  
      JetTau32                              = tau32 ;  
      JetTau21                              = tau21 ;  
      JetSDsubjet0bdisc                           = sub0_bdisc ;  
      JetSDsubjet1bdisc                           = sub1_bdisc ;   
      JetSDmaxbdisc                         = maxbdisc;
      JetSDmaxbdiscflavHadron               = maxbdiscflav_hadron;  
      JetSDmaxbdiscflavParton               = maxbdiscflav_parton;  
      JetSDsubjet0pt                        = sub0_P4_uncorr.Pt() ;               
      JetSDsubjet0mass                      = sub0_P4_uncorr.M()  ;  
      JetSDsubjet0eta                       = sub0_P4_uncorr.Eta()  ;  
      JetSDsubjet0phi                       = sub0_P4_uncorr.Phi()  ;  
      JetSDsubjet0area                      = sub0_area ;  
      JetSDsubjet0flavHadron                = sub0_flav_hadron ;  
      JetSDsubjet0flavParton                = sub0_flav_parton ;  
      JetSDsubjet0tau1                      = sub0_tau1                  ;
      JetSDsubjet0tau2                      = sub0_tau2                  ;
      JetSDsubjet0tau3                      = sub0_tau3                  ;
      JetSDsubjet1pt                        = sub1_P4_uncorr.Pt() ;                    
      JetSDsubjet1mass                      = sub1_P4_uncorr.M()  ;                    
      JetSDsubjet1eta                       = sub1_P4_uncorr.Eta()  ;                    
      JetSDsubjet1phi                       = sub1_P4_uncorr.Phi()  ;                    
      JetSDsubjet1area                      = sub1_area ;                    
      JetSDsubjet1flavHadron                = sub1_flav_hadron ;     
      JetSDsubjet1flavParton                = sub1_flav_parton ;     
      JetSDsubjet1tau1                      = sub1_tau1                  ;
      JetSDsubjet1tau2                      = sub1_tau2                  ;
      JetSDsubjet1tau3                      = sub1_tau3                  ;

      AK8jet_SemiLept_P4corr.SetPtEtaPhiM( corrJet.pt(), corrJet.eta(), corrJet.phi(), corrJet.mass() );

      JetPuppiPt                            = puppi_pt   ;                  
      JetPuppiEta                           = puppi_eta  ;                   
      JetPuppiPhi                           = puppi_phi  ;                  
      JetPuppiMass                          = puppi_mass ;                  
      JetPuppiMassSoftDrop                  = sumPUPsubjets_P4_uncorr.M() ;
      JetPuppiMassSDsumSubjetRaw            = sumPUPsubjets_P4_uncorr.M() ;
      JetPuppiMassSDsumSubjetCorr           = sumPUPsubjets_P4_L23res.M() ;   
      JetPuppiMassSDsumSubjetCorrUp         = sumPUPsubjets_P4_corrUp_L23res.M() ;
      JetPuppiMassSDsumSubjetCorrDn         = sumPUPsubjets_P4_corrDn_L23res.M() ;
      JetPuppiMassSDsumSubjetCorrSmear      = 1;
      JetPuppiMassSDsumSubjetCorrSmearUp    = 1;
      JetPuppiMassSDsumSubjetCorrSmearDn    = 1;
      JetPuppiTau1                          = puppi_tau1       ;                  
      JetPuppiTau2                          = puppi_tau2       ;                  
      JetPuppiTau3                          = puppi_tau3       ;                  
      JetPuppiTau32                         = puppi_tau32      ;                  
      JetPuppiTau21                         = puppi_tau21      ;                  
      JetPuppiSDsubjet0bdisc                = pup0_bdisc       ;
      JetPuppiSDsubjet1bdisc                = pup1_bdisc       ;
      JetPuppiSDmaxbdisc                    = pup_maxbdisc     ;   
      JetPuppiSDmaxbdiscflavHadron          = pup_maxbdiscflav_hadron    ;
      JetPuppiSDmaxbdiscflavParton          = pup_maxbdiscflav_parton    ;
      JetPuppiSDsubjet0pt                   = pup0_P4_uncorr.Pt()        ;
      JetPuppiSDsubjet0mass                 = pup0_P4_uncorr.M()         ;
      JetPuppiSDsubjet0eta                  = pup0_P4_uncorr.Eta()         ;
      JetPuppiSDsubjet0phi                  = pup0_P4_uncorr.Phi()         ;
      JetPuppiSDsubjet0area                 = pup0_area                  ;
      JetPuppiSDsubjet0flavHadron           = pup0_flav_hadron           ;
      JetPuppiSDsubjet0flavParton           = pup0_flav_parton           ;
      JetPuppiSDsubjet0tau1                 = pup0_tau1                  ;
      JetPuppiSDsubjet0tau2                 = pup0_tau2                  ;
      JetPuppiSDsubjet0tau3                 = pup0_tau3                  ;
      JetPuppiSDsubjet1pt                   = pup1_P4_uncorr.Pt()        ;                 
      JetPuppiSDsubjet1mass                 = pup1_P4_uncorr.M()         ;              
      JetPuppiSDsubjet1eta                  = pup1_P4_uncorr.Eta()       ;              
      JetPuppiSDsubjet1phi                  = pup1_P4_uncorr.Phi()       ;              
      JetPuppiSDsubjet1area                 = pup1_area                  ;              
      JetPuppiSDsubjet1flavHadron           = pup1_flav_hadron           ;   
      JetPuppiSDsubjet1flavParton           = pup1_flav_parton           ;   
      JetPuppiSDsubjet1tau1                 = pup1_tau1                  ;
      JetPuppiSDsubjet1tau2                 = pup1_tau2                  ;
      JetPuppiSDsubjet1tau3                 = pup1_tau3                  ;

      JetCHF                                = ijet.chargedHadronEnergy() / uncorrJet.E()  ;                        
      JetNHF                                = ijet.neutralHadronEnergy() / uncorrJet.E()  ;                         
      JetCM                                 = ijet.chargedMultiplicity()  ;                         
      JetNM                                 = ijet.neutralMultiplicity()  ;                          
      JetNEF                                = ijet.neutralEmEnergy() / uncorrJet.E()  ;                            
      JetCEF                                = ijet.chargedEmEnergy() / uncorrJet.E()  ;                          
      JetMF                                 = ijet.muonEnergy() / uncorrJet.E()  ;                         
      JetMult                               = ijet.numberOfDaughters() ;   

      JetMassCorrFactor                     = corr_factor_L23res ;        
      JetMassCorrFactorUp                   = corrUp_L23 ;
      JetMassCorrFactorDn                   = corrDn_L23 ;
      JetCorrFactor                         = corr ;        
      JetCorrFactorUp                       = corrUp_L123 ;
      JetCorrFactorDn                       = corrDn_L123;
      JetPtSmearFactor                      = ptsmear  ;
      JetPtSmearFactorUp                    = ptsmearUp;
      JetPtSmearFactorDn                    = ptsmearDn;
      JetPuppiMassCorrFactor                = 1;          
      JetPuppiMassCorrFactorUp              = 1;          
      JetPuppiMassCorrFactorDn              = 1;          
      JetPuppiCorrFactor                    = 1;          
      JetPuppiCorrFactorUp                  = 1;          
      JetPuppiCorrFactorDn                  = 1;          
      JetPuppiPtSmearFactor                 = 1;          
      JetPuppiPtSmearFactorUp               = 1;          
      JetPuppiPtSmearFactorDn               = 1;          
      JetEtaScaleFactor                     = 1;          
      JetPhiScaleFactor                     = 1;          
      JetMatchedGenJetDR                    = GenJetMatched_dRmin;             
      JetMatchedGenJetPt                    = GenJetMatched.Perp();       
      JetMatchedGenJetMass                  = GenJetMatched.M();   

      if (!iEvent.isRealData() and runGenLoop_) {
        if (counttop==2 && jet_matched_t1){
          if (top1hadronic) JetGenMatched_TopHadronic         = 1                   ;
          else              JetGenMatched_TopHadronic         = 0                   ;
          JetGenMatched_TopPt               = t1_p4.Perp()                   ;
          JetGenMatched_TopEta              = t1_p4.Eta()                    ;
          JetGenMatched_TopPhi              = t1_p4.Phi()                    ;
          JetGenMatched_TopMass             = t1_p4.M()                      ;
          JetGenMatched_bPt                 = b1_p4.Perp()                   ;
          JetGenMatched_WPt                 = W1_p4.Perp()                   ;
          JetGenMatched_Wd1Pt               = W1d1_p4.Perp()                 ;
          JetGenMatched_Wd2Pt               = W1d2_p4.Perp()                 ;
          JetGenMatched_Wd1ID               = W1d1_id                        ;
          JetGenMatched_Wd2ID               = W1d2_id                        ;
          JetGenMatched_MaxDeltaRPartonTop  = max_deltaR_parton_t1           ;
          JetGenMatched_MaxDeltaRWPartonTop = max_deltaR_Wparton_t1          ;
          JetGenMatched_MaxDeltaRWPartonW   = max_deltaR_Wparton_W1          ;
          JetGenMatched_DeltaR_t_b          = deltaR_t1_b1                   ;
          JetGenMatched_DeltaR_t_W          = deltaR_t1_W1                   ;
          JetGenMatched_DeltaR_t_Wd1        = deltaR_t1_W1d1                 ;
          JetGenMatched_DeltaR_t_Wd2        = deltaR_t1_W1d2                 ;
          JetGenMatched_DeltaR_W_b1         = deltaR_W1_b1                   ;
          JetGenMatched_DeltaR_W_Wd1        = deltaR_W1_W1d1                 ;
          JetGenMatched_DeltaR_W_Wd2        = deltaR_W1_W1d2                 ;
          JetGenMatched_DeltaR_Wd1_Wd2      = deltaR_W1d1_W1d2               ;
          JetGenMatched_DeltaR_Wd1_b        = deltaR_W1d1_b1                 ;
          JetGenMatched_DeltaR_Wd2_b        = deltaR_W1d2_b1                 ;
          JetGenMatched_DeltaR_jet_t        = deltaR_jet_t1                  ;
          JetGenMatched_DeltaR_jet_W        = jet_p4.DeltaR(W1_p4  )         ;
          JetGenMatched_DeltaR_jet_b        = jet_p4.DeltaR(b1_p4  )         ;
          JetGenMatched_DeltaR_jet_Wd1      = jet_p4.DeltaR(W1d1_p4)         ;
          JetGenMatched_DeltaR_jet_Wd2      = jet_p4.DeltaR(W1d2_p4)         ;
          JetGenMatched_DeltaR_pup0_b       = pup0_P4_L23res.DeltaR(b1_p4)   ;
          JetGenMatched_DeltaR_pup0_Wd1     = pup0_P4_L23res.DeltaR(W1d1_p4) ;
          JetGenMatched_DeltaR_pup0_Wd2     = pup0_P4_L23res.DeltaR(W1d2_p4) ;
          JetGenMatched_DeltaR_pup1_b       = pup1_P4_L23res.DeltaR(b1_p4)   ;
          JetGenMatched_DeltaR_pup1_Wd1     = pup1_P4_L23res.DeltaR(W1d1_p4) ;
          JetGenMatched_DeltaR_pup1_Wd2     = pup1_P4_L23res.DeltaR(W1d2_p4) ;
        }   
        if (counttop==2 && jet_matched_t2){
          if(top2hadronic) JetGenMatched_TopHadronic         = 1           ;
          else             JetGenMatched_TopHadronic         = 0           ;
          JetGenMatched_TopPt               = t2_p4.Perp()           ;
          JetGenMatched_TopEta              = t2_p4.Eta()            ;
          JetGenMatched_TopPhi              = t2_p4.Phi()            ;
          JetGenMatched_TopMass             = t2_p4.M()              ;
          JetGenMatched_bPt                 = b2_p4.Perp()           ;
          JetGenMatched_WPt                 = W2_p4.Perp()           ;
          JetGenMatched_Wd1Pt               = W2d1_p4.Perp()         ;
          JetGenMatched_Wd2Pt               = W2d2_p4.Perp()         ;
          JetGenMatched_Wd1ID               = W2d1_id                ;
          JetGenMatched_Wd2ID               = W2d2_id                ;
          JetGenMatched_MaxDeltaRPartonTop  = max_deltaR_parton_t2   ;
          JetGenMatched_MaxDeltaRWPartonTop = max_deltaR_Wparton_t2  ;
          JetGenMatched_MaxDeltaRWPartonW   = max_deltaR_Wparton_W2  ;
          JetGenMatched_DeltaR_t_b          = deltaR_t2_b2           ;
          JetGenMatched_DeltaR_t_W          = deltaR_t2_W2           ;
          JetGenMatched_DeltaR_t_Wd1        = deltaR_t2_W2d1         ;
          JetGenMatched_DeltaR_t_Wd2        = deltaR_t2_W2d2         ;
          JetGenMatched_DeltaR_W_b1         = deltaR_W2_b2           ;
          JetGenMatched_DeltaR_W_Wd1        = deltaR_W2_W2d1         ;
          JetGenMatched_DeltaR_W_Wd2        = deltaR_W2_W2d2         ;
          JetGenMatched_DeltaR_Wd1_Wd2      = deltaR_W2d1_W2d2       ;
          JetGenMatched_DeltaR_Wd1_b        = deltaR_W2d1_b2         ;
          JetGenMatched_DeltaR_Wd2_b        = deltaR_W2d2_b2         ;
          JetGenMatched_DeltaR_jet_t        = deltaR_jet_t2          ;
          JetGenMatched_DeltaR_jet_W        = jet_p4.DeltaR(W2_p4  ) ;
          JetGenMatched_DeltaR_jet_b        = jet_p4.DeltaR(b2_p4  ) ;
          JetGenMatched_DeltaR_jet_Wd1      = jet_p4.DeltaR(W2d1_p4) ;
          JetGenMatched_DeltaR_jet_Wd2      = jet_p4.DeltaR(W2d2_p4) ;
          JetGenMatched_DeltaR_pup0_b       = pup0_P4_L23res.DeltaR(b2_p4)   ;
          JetGenMatched_DeltaR_pup0_Wd1     = pup0_P4_L23res.DeltaR(W2d1_p4) ;
          JetGenMatched_DeltaR_pup0_Wd2     = pup0_P4_L23res.DeltaR(W2d2_p4) ;
          JetGenMatched_DeltaR_pup1_b       = pup1_P4_L23res.DeltaR(b2_p4)   ;
          JetGenMatched_DeltaR_pup1_Wd1     = pup1_P4_L23res.DeltaR(W2d1_p4) ;
          JetGenMatched_DeltaR_pup1_Wd2     = pup1_P4_L23res.DeltaR(W2d2_p4) ;
        }
        if (counttop==0 && jet_matched_p1){
          JetGenMatched_partonPt               = hardest_parton_hardScatterOutgoing_p4.Perp()           ;
          JetGenMatched_partonEta              = hardest_parton_hardScatterOutgoing_p4.Eta()            ;
          JetGenMatched_partonPhi              = hardest_parton_hardScatterOutgoing_p4.Phi()            ;
          JetGenMatched_partonMass             = hardest_parton_hardScatterOutgoing_p4.M()              ;
          JetGenMatched_partonID               = parton1id                                              ;
          JetGenMatched_DeltaRjetParton        = deltaR_jet_p1                                          ;
        }
        if (counttop==0 && jet_matched_p2){
          JetGenMatched_partonPt               = second_hardest_parton_hardScatterOutgoing_p4.Perp()    ;
          JetGenMatched_partonEta              = second_hardest_parton_hardScatterOutgoing_p4.Eta()     ;
          JetGenMatched_partonPhi              = second_hardest_parton_hardScatterOutgoing_p4.Phi()     ;
          JetGenMatched_partonMass             = second_hardest_parton_hardScatterOutgoing_p4.M()       ;
          JetGenMatched_partonID               = parton2id                                              ;
          JetGenMatched_DeltaRjetParton        = deltaR_jet_p2                                          ;
        }
      }
    } 

    count_AK8CHS++;
  }

  //
  //        d8888 888 888        888    888               888     88888888888                           
  //       d88888 888 888        888    888               888         888                               
  //      d88P888 888 888        888    888               888         888                               
  //     d88P 888 888 888        8888888888  8888b.   .d88888         888     888d888  .d88b.   .d88b.  
  //    d88P  888 888 888        888    888     "88b d88" 888         888     888P"   d8P  Y8b d8P  Y8b 
  //   d88P   888 888 888 888888 888    888 .d888888 888  888         888     888     88888888 88888888 
  //  d8888888888 888 888        888    888 888  888 Y88b 888         888     888     Y8b.     Y8b.     
  // d88P     888 888 888        888    888 "Y888888  "Y88888         888     888      "Y8888   "Y8888  
  //                                                                                                    
         
  AllHadMETpx          = met.px();                   
  AllHadMETpy          = met.py();                   
  AllHadMETpt          = met.pt();                   
  AllHadMETphi         = met.phi();                   
  AllHadMETsumET       = met.sumEt();                   
  AllHadNvtx           = nvtx;               
  AllHadRho            = rho ;               
  AllHadEventWeight    = 1 ;              
  DijetMass            = (AK8jet0_P4corr + AK8jet1_P4corr).M() ;                                                   
  DijetDeltaR          = deltaR( AK8jet0_P4corr.Eta(), AK8jet0_P4corr.Phi(), AK8jet1_P4corr.Eta(), AK8jet1_P4corr.Phi() );               
  DijetDeltaPhi        = deltaPhi( AK8jet0_P4corr.Phi(),  AK8jet1_P4corr.Phi() );                 
  DijetDeltaRap        = fabs(AK8jet0_P4corr.Rapidity() -  AK8jet1_P4corr.Rapidity() );

  DiGenJetMass         = (GenJetMatched0 + GenJetMatched1).M();                   
  GenTTmass            = (t1_p4+t2_p4).M() ;               
  HT                   = 1 ;                
  HT_CorrDn            = 1 ;                
  HT_CorrUp            = 1 ;                
  HT_PtSmearUp         = 1 ;                
  HT_PtSmearDn         = 1 ;                
  Q2weight_CorrDn      = 1 ;              
  Q2weight_CorrUp      = 1 ;              
  NNPDF3weight_CorrDn  = 1 ;              
  NNPDF3weight_CorrUp  = 1 ;              
  AllHadRunNum         = iEvent.id().run() ;              
  AllHadLumiBlock      = iEvent.id().luminosityBlock() ;              
  AllHadEventNum       = iEvent.id().event() ;  
  if (passMETfilters) PassMETFilters       = 1;
  else PassMETFilters                      = 0;

  //------------------------------------
  // WRITE TREE WITH BASELINE PT CUT AND ETA CUT
  //------------------------------------
  if (AK8jet0_P4corr.Perp()>400 && AK8jet1_P4corr.Perp()>400 &&  fabs( AK8jet0_P4corr.Rapidity() ) <2.4 &&  fabs( AK8jet1_P4corr.Rapidity() ) <2.4  ){
    TreeAllHad -> Fill();
  } 



  // 
  //  .d8888b.                         d8b        888                        888        88888888888                           
  // d88P  Y88b                        Y8P        888                        888            888                               
  // Y88b.                                        888                        888            888                               
  //  "Y888b.    .d88b.  88888b.d88b.  888        888       .d88b.  88888b.  888888         888     888d888  .d88b.   .d88b.  
  //     "Y88b. d8P  Y8b 888 "888 "88b 888        888      d8P  Y8b 888 "88b 888            888     888P"   d8P  Y8b d8P  Y8b 
  //       "888 88888888 888  888  888 888 888888 888      88888888 888  888 888            888     888     88888888 88888888 
  // Y88b  d88P Y8b.     888  888  888 888        888      Y8b.     888 d88P Y88b.          888     888     Y8b.     Y8b.     
  //  "Y8888P"   "Y8888  888  888  888 888        88888888  "Y8888  88888P"   "Y888         888     888      "Y8888   "Y8888  
  //                                                                888                                                       
  //                                                                888                                                       
  //                                                                888       
     
  SemiLeptMETpx                = met.px();                   
  SemiLeptMETpy                = met.py();                   
  SemiLeptMETpt                = met.pt();                   
  SemiLeptMETphi               = met.phi();                   
  SemiLeptMETsumET             = met.sumEt();                   
  SemiLeptNvtx                 = nvtx;               
  SemiLeptRho                  = rho ;               
  SemiLeptEventWeight          = 1 ;              

  SemiLeptGenTTmass            = (t1_p4+t2_p4).M() ;               
  SemiLeptHT                   = 1 ;                
  SemiLeptHT_CorrDn            = 1 ;                
  SemiLeptHT_CorrUp            = 1 ;                
  SemiLeptHT_PtSmearUp         = 1 ;                
  SemiLeptHT_PtSmearDn         = 1 ;                
  SemiLeptQ2weight_CorrDn      = 1 ;              
  SemiLeptQ2weight_CorrUp      = 1 ;              
  SemiLeptNNPDF3weight_CorrDn  = 1 ;              
  SemiLeptNNPDF3weight_CorrUp  = 1 ;              
  SemiLeptRunNum               = iEvent.id().run() ;              
  SemiLeptLumiBlock            = iEvent.id().luminosityBlock() ;              
  SemiLeptEventNum             = iEvent.id().event() ;              
  if(passMETfilters) SemiLeptPassMETFilters  = 1;
  else SemiLeptPassMETFilters  = 0;

  AK4dRminPt        = AK4_dRMinMu_p4.Perp();
  AK4dRminEta       = AK4_dRMinMu_p4.Eta();
  AK4dRminPhi       = AK4_dRMinMu_p4.Phi();
  AK4dRminBdisc     = AK4_dRMinMu_bdisc    ;
  AK4BtagdRminPt    = AK4_btagged_dRMinMu_p4.Perp();
  AK4BtagdRminBdisc = AK4_btagged_dRMinMu_bdisc    ;

  if (ak4_btag_loose) AK4BtaggedLoose   = 1  ;
  else                AK4BtaggedLoose   = 0  ;
  if (ak4_btag_medium)AK4BtaggedMedium  = 1  ;
  else                AK4BtaggedMedium  = 0  ;
  if (ak4_btag_tight) AK4BtaggedTight   = 1  ;
  else                AK4BtaggedTight   = 0  ;

  LeptonPhi   = lep0_p4.Phi()  ; 
  LeptonPt    = lep0_p4.Perp() ;  
  LeptonEta   = lep0_p4.Eta()  ; 
  LeptonMass  = lep0_p4.Eta()  ; 
  if (count_mu==1 && count_el==0) LeptonIsMu  = 1  ; 
  else if (count_mu==0 && count_el==1) LeptonIsMu  = 0  ; 
  else LeptonIsMu =0;



  if(mu0_isTight) MuTight = 1   ;
  else            MuTight = 0   ;

  //------------------------------------
  // WRITE TREE WITH BASELINE PT CUT AND ETA CUT
  //------------------------------------

  if (AK8jet_SemiLept_P4corr.Perp()>300 && fabs( AK8jet_SemiLept_P4corr.Rapidity() ) <2.4 && mu0_p4.Perp()>40 && met.pt() > 40 && AK4_dRMinMu_p4.Perp() > 20  ){
    TreeSemiLept -> Fill();
  } 


}


// ------------ method called once each job just before starting event loop  ------------
void 
B2GTTbarTreeMaker::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
B2GTTbarTreeMaker::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
B2GTTbarTreeMaker::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(B2GTTbarTreeMaker);
