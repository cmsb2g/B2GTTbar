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

//--------------------------
// To add:
// - NNPDF3weight  
// - electron quality cuts
// - trigger
//
// Note. The following items should be applied at the tree reader level:
// - MU ID (HIP)
// -- TFile* f_muID = TFile::Open("MuonID_Z_RunBCD_prompt80X_7p65.root","read");
// -- TH1F* h_muID = (TH1F*) f_muID->Get("MC_NUM_MediumID_DEN_genTracks_PAR_eta/eta_ratio")->Clone();
// -- float SF_muID = h_muID->GetBinContent(h_muID->FindBin(eta););
// - BTagCalibrationReader
//--------------------------


// system include files
#include <memory>
#include <iostream>    
#include <algorithm>   
#include <bitset>   

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// DataFormats
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
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

// Electron
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/ConversionFwd.h"
#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"

// Trigger
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"

// Vertex
#include "DataFormats/VertexReco/interface/Vertex.h"

// Pileup
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

// LHE weights
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// Utilities
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"

// root
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TLorentzVector.h"

//RS gluon PDF weights
namespace LHAPDF {
  void initPDFSet(int nset, const std::string& filename, int member=0);
  int numberPDF(int nset);
  void usePDFMember(int nset, int member);
  double xfx(int nset, double x, double Q, int fl);
  double getXmin(int nset, int member);
  double getXmax(int nset, int member);
  double getQ2min(int nset, int member);
  double getQ2max(int nset, int member);
  void extrapolate(bool extrapolate=true);
}

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
      edm::EDGetTokenT<pat::JetCollection> ak8PuppiSoftDropSubjetsToken_;
      edm::EDGetTokenT<reco::GenJetCollection> ak4genjetToken_;
      edm::EDGetTokenT<reco::GenJetCollection> ak8genjetToken_;
      edm::EDGetTokenT<edm::View<reco::GenParticle> > prunedGenToken_;
      edm::EDGetTokenT<double> rhoToken_;
      edm::EDGetTokenT<std::vector<reco::Vertex> > vtxToken_;
      edm::EDGetTokenT<edm::TriggerResults> triggerResultsMETFilterToken_;
      edm::EDGetTokenT<edm::TriggerResults> triggerBits_;
      edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjects_;
      edm::EDGetTokenT<pat::PackedTriggerPrescales> triggerPrescales_;
      edm::EDGetTokenT<bool> badMuonFilterToken_;
      edm::EDGetTokenT<bool> badChargedCandidateFilterToken_;
      edm::EDGetTokenT<pat::MuonCollection> muonToken_;
      edm::EDGetTokenT<pat::ElectronCollection> electronToken_;
      edm::EDGetTokenT<pat::METCollection> metToken_;
      edm::EDGetTokenT<std::vector<PileupSummaryInfo> > pileupInfoToken_;
      edm::EDGetTokenT<LHEEventProduct> theSrc_;
      edm::EDGetTokenT<GenEventInfoProduct> pdfToken_;
      
      bool useToolbox_;
      bool verbose_;
      bool verboseGen_;
      bool runGenLoop_;
      bool isZprime_;
      bool isttbar_;
      bool isRSG_;
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

      TFile* fPUweight;
      TH1D* hPUweight;
      TH1D* hPUweight_MBup;
      TH1D* hPUweight_MBdn;

      int count_GenTruth_semileptonic ;
      int count_nMu_gt1 ; 
      int count_nEl_gt1 ; 
      int count_nMu_e1 ; 
      int count_nEl_e1 ; 
      int count_nLep_e1 ; 
      int count_JetPt300 ; 
      int count_JetPt300Eta ; 
      int count_JetPt300Eta_AK4 ; 
      int count_JetPt300Eta_muPt40 ; 
      int count_JetPt300Eta_muPt40_MET40 ; 
      int count_JetPt300Eta_muPt40_MET40_AK4 ; 


      TH1D * h_ak8puppi_softDropMass ;
      TH1D * h_ak8chs_softDropMass   ;
      TH1D * h_ak8chs_softDropMass_reweighted ;
      TH1D * h_ak8chs_pt   ;
      TH1D * h_ak8chs_pt_reweighted ;
      TH1D * h_NtrueIntPU ;
      TH1D * h_NPV           ;               
      TH1D * h_NPVreweighted ;                 

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

      std::vector<std::string> *AllHadTrigNames     = new std::vector<std::string>;
      std::vector<int> *AllHadTrigPrescales = new std::vector<int>;
      std::vector<bool> *AllHadTrigPass    = new std::vector<bool>;

      std::string AllHadTrigAcceptBits;

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
      Float_t Jet0PuppiP                                ;
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
      Float_t Jet0PuppiCHF                              ;
      Float_t Jet0PuppiNHF                              ;
      Float_t Jet0PuppiCM                               ;
      Float_t Jet0PuppiNM                               ;
      Float_t Jet0PuppiNEF                              ;
      Float_t Jet0PuppiCEF                              ;
      Float_t Jet0PuppiMF                               ;
      Float_t Jet0PuppiMult                             ;
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
      Float_t Jet1PuppiP                                ;
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
      Float_t Jet1PuppiCHF                              ;
      Float_t Jet1PuppiNHF                              ;
      Float_t Jet1PuppiCM                               ;
      Float_t Jet1PuppiNM                               ;
      Float_t Jet1PuppiNEF                              ;
      Float_t Jet1PuppiCEF                              ;
      Float_t Jet1PuppiMF                               ;
      Float_t Jet1PuppiMult                             ;
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
      std::vector<std::string> *SemiLeptTrigNames     = new std::vector<std::string>;
      std::vector<int> *SemiLeptTrigPrescales = new std::vector<int>;
      std::vector<bool> *SemiLeptTrigPass    = new std::vector<bool>;



      std::string SemiLeptTrigAcceptBits;

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
      Float_t JetSDmass                              ;
      Float_t JetSDmassRaw                           ;
      Float_t JetSDmassCorrL23                       ;
      Float_t JetSDmassCorrL23Up                     ;
      Float_t JetSDmassCorrL23Dn                     ;
      Float_t JetSDmassCorrL123                      ;
      Float_t JetSDmassCorrL123Up                    ;
      Float_t JetSDmassCorrL123Dn                    ;
      Float_t JetSDmassCorrL23Smear                  ;
      Float_t JetSDmassCorrL23SmearUp                ;
      Float_t JetSDmassCorrL23SmearDn                ;
      Float_t JetSDptRaw                             ;
      Float_t JetSDptCorrL23                         ;
      Float_t JetSDptCorrL23Up                       ;
      Float_t JetSDptCorrL23Dn                       ;
      Float_t JetSDptCorrL123                        ;
      Float_t JetSDptCorrL123Up                      ;
      Float_t JetSDptCorrL123Dn                      ;
      Float_t JetSDptCorrL23Smear                    ;
      Float_t JetSDptCorrL23SmearUp                  ;
      Float_t JetSDptCorrL23SmearDn                  ;
      Float_t JetSDetaRaw                            ;
      Float_t JetSDphiRaw                            ;
      Float_t JetMassPruned                          ;
      Float_t JetMassTrimmed                         ;
      Float_t JetTau1                                ;
      Float_t JetTau2                                ;
      Float_t JetTau3                                ;
      Float_t JetTau4                                ;
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
      Float_t JetPuppiP                              ;
      Float_t JetPuppiPt                             ;
      Float_t JetPuppiEta                            ;
      Float_t JetPuppiPhi                            ;
      Float_t JetPuppiMass                           ;
      Float_t JetPuppiSDmass                         ;
      Float_t JetPuppiSDmassCorr                     ;
      Float_t JetPuppiSDmassCorrUp                   ;
      Float_t JetPuppiSDmassCorrDn                   ;
      Float_t JetPuppiSDmassCorrL23Smear             ;
      Float_t JetPuppiSDmassCorrL23SmearUp           ;
      Float_t JetPuppiSDmassCorrL23SmearDn           ;
      Float_t JetPuppiSDpt                           ;
      Float_t JetPuppiSDptCorr                       ;
      Float_t JetPuppiSDptCorrUp                     ;
      Float_t JetPuppiSDptCorrDn                     ;
      Float_t JetPuppiSDptCorrL23Smear               ;
      Float_t JetPuppiSDptCorrL23SmearUp             ;
      Float_t JetPuppiSDptCorrL23SmearDn             ;
      Float_t JetPuppiSDeta                          ;
      Float_t JetPuppiSDphi                          ;
      Float_t JetPuppiTau1                           ;
      Float_t JetPuppiTau2                           ;
      Float_t JetPuppiTau3                           ;
      Float_t JetPuppiTau4                           ;
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
      Float_t JetPuppiCHF                            ;
      Float_t JetPuppiNHF                            ;
      Float_t JetPuppiCM                             ;
      Float_t JetPuppiNM                             ;
      Float_t JetPuppiNEF                            ;
      Float_t JetPuppiCEF                            ;
      Float_t JetPuppiMF                             ;
      Float_t JetPuppiMult                           ;
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
      // Float_t JetMatchedGenJetDR                     ;
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
      Float_t SemiLeptNPUtrue                        ;
      Float_t SemiLeptRho                            ;
      Float_t SemiLeptEventWeight                    ;
      Float_t SemiLeptPUweight       ;
      Float_t SemiLeptPUweight_MBup  ;
      Float_t SemiLeptPUweight_MBdn  ;


      Float_t SemiLeptGenTTmass                      ;

      Float_t HTlep                                  ;
      Float_t ST                                     ;                
      Float_t ST_CorrDn                              ;                
      Float_t ST_CorrUp                              ;                
      Float_t ST_PtSmearNom                          ;                
      Float_t ST_PtSmearUp                           ;                
      Float_t ST_PtSmearDn                           ;   

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
      Float_t AK4dRminMass                           ;
      Float_t AK4dRminBdisc                          ;
      Float_t AK4dRminLep                            ;
      Float_t AK4BtagdRminPt                         ;
      Float_t AK4BtagdRminBdisc                      ;
      Float_t AK4BtagdRminLep                        ;
      Int_t   LepHemiContainsAK4BtagLoose            ;
      Int_t   LepHemiContainsAK4BtagMedium           ;
      Int_t   LepHemiContainsAK4BtagTight            ;


      Float_t LeptonPhi                              ;
      Float_t LeptonPt                               ;
      Float_t LeptonEta                              ;
      Float_t LeptonMass                             ;
      Float_t PtRel                                  ;
      Int_t   LeptonIsMu                             ;
      Int_t   MuHighPt                                ;
      Int_t   MuTight                                ;
      Int_t   MuMedium                               ;
      Float_t DeltaRJetLep                           ; 
      Float_t DeltaPhiJetLep                         ; 
      Float_t MuIso                                  ;
      Float_t Elecron_absiso                         ;
      Float_t Elecron_relIsoWithDBeta                ;
      Float_t Elecron_absiso_EA                      ;
      Float_t Elecron_relIsoWithEA                   ;

      Int_t Electron_isMedium   ; 
      Int_t Electron_isTight    ; 

};

//
// constructors and destructor
//
B2GTTbarTreeMaker::B2GTTbarTreeMaker(const edm::ParameterSet& iConfig):
    ak4jetToken_(consumes<pat::JetCollection>(edm::InputTag("slimmedJets"))),
    ak8jetToken_(consumes<pat::JetCollection>(    iConfig.getParameter<edm::InputTag>("ak8chsInput"))),  //edm::InputTag("slimmedJetsAK8"))),
    puppijetToken_(consumes<pat::JetCollection>(  iConfig.getParameter<edm::InputTag>("ak8puppiInput"))),
    ak8CHSSoftDropSubjetsToken_(consumes<pat::JetCollection>(  iConfig.getParameter<edm::InputTag>("ak8chsSubjetsInput"))),
    ak8PuppiSoftDropSubjetsToken_(consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("ak8puppiSubjetsInput"))),
    ak4genjetToken_(consumes<reco::GenJetCollection>(edm::InputTag("slimmedGenJets"))),
    ak8genjetToken_(consumes<reco::GenJetCollection>(edm::InputTag("slimmedGenJetsAK8"))),
    prunedGenToken_(consumes<edm::View<reco::GenParticle> >(edm::InputTag("prunedGenParticles"))),
    rhoToken_(consumes<double>(edm::InputTag("fixedGridRhoFastjetAll"))),
    vtxToken_(consumes<std::vector<reco::Vertex> >(edm::InputTag("offlineSlimmedPrimaryVertices"))),
    triggerResultsMETFilterToken_(consumes<edm::TriggerResults>(edm::InputTag("TriggerResults", "", "RECO"))),  //"PAT"
    triggerBits_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerBits"))),//"TriggerResults", "", "HLT2"))),
    triggerObjects_(consumes<pat::TriggerObjectStandAloneCollection>(edm::InputTag("patTrigger"))),
    triggerPrescales_(consumes<pat::PackedTriggerPrescales>(edm::InputTag("patTrigger"))),  //   selectedPatTrigger))),
    badMuonFilterToken_(consumes<bool>(edm::InputTag("BadPFMuonFilter",""))),
    badChargedCandidateFilterToken_(consumes<bool>(edm::InputTag("BadChargedCandidateFilter",""))),
    muonToken_(consumes<pat::MuonCollection>(edm::InputTag("slimmedMuons"))),
    electronToken_(consumes<pat::ElectronCollection>(edm::InputTag("slimmedElectrons"))),
    metToken_(consumes<pat::METCollection>(edm::InputTag("slimmedMETs"))),
    pileupInfoToken_(consumes<std::vector<PileupSummaryInfo>>(edm::InputTag("slimmedAddPileupInfo"))),
    theSrc_(consumes<LHEEventProduct>(iConfig.getParameter<edm::InputTag>("theSrc"))),
    pdfToken_(consumes<GenEventInfoProduct>(edm::InputTag("generator"))),
    useToolbox_(iConfig.getParameter<bool>  ("useToolbox")),
    verbose_(iConfig.getParameter<bool>  ("verbose")),
    verboseGen_(iConfig.getParameter<bool>  ("verboseGen")),
    runGenLoop_(iConfig.getParameter<bool>  ("runGenLoop")),
    isZprime_(iConfig.getParameter<bool>  ("isZprime")),
    isttbar_(iConfig.getParameter<bool>  ("isttbar")),
    isRSG_(iConfig.getParameter<bool>  ("isRSG")),
    jecPayloadsAK4chs_ (iConfig.getParameter<std::vector<std::string> >  ("jecPayloadsAK4chs")),
    jecPayloadsAK8chs_ (iConfig.getParameter<std::vector<std::string> >  ("jecPayloadsAK8chs")),
    jecPayloadsAK4pup_ (iConfig.getParameter<std::vector<std::string> >  ("jecPayloadsAK4pup")),
    jecPayloadsAK8pup_ (iConfig.getParameter<std::vector<std::string> >  ("jecPayloadsAK8pup")),
    jerSFtext_ (iConfig.getParameter<std::string>  ("jerSFtext"))
{
  std::cout<<"B2GTTbarTreeMaker::B2GTTbarTreeMaker"<<std::endl;

  //RS gluon PDF weights
  LHAPDF::initPDFSet(1, "NNPDF30_lo_as_0130");

  usesResource("TFileService");

  edm::Service<TFileService> fs;

  h_ak8puppi_softDropMass            =  fs->make<TH1D>("h_ak8puppi_softDropMass"           ,"",200,0,400);
  h_ak8chs_softDropMass              =  fs->make<TH1D>("h_ak8chs_softDropMass"             ,"",200,0,400);
  h_ak8chs_softDropMass_reweighted   =  fs->make<TH1D>("h_ak8chs_softDropMass_reweighted"  ,"",200,0,400);
  h_ak8chs_pt                        =  fs->make<TH1D>("h_ak8chs_pt"                       ,"",200,0,4000);
  h_ak8chs_pt_reweighted             =  fs->make<TH1D>("h_ak8chs_pt_reweighted"            ,"",200,0,4000);
  h_NtrueIntPU                       =  fs->make<TH1D>("h_NtrueIntPU"                      ,"",200,0,200);
  h_NPV                              =  fs->make<TH1D>("h_NPV"                             ,"",200,0,200);
  h_NPVreweighted                    =  fs->make<TH1D>("h_NPVreweighted"                   ,"",200,0,200);



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


  TreeAllHad->Branch("AllHadTrigNames"    , "vector<std::string>", &AllHadTrigNames);
  TreeAllHad->Branch("AllHadTrigPrescales"   , "vector<int>", &AllHadTrigPrescales);
  TreeAllHad->Branch("AllHadTrigPass"        , "vector<bool>", &AllHadTrigPass);
  TreeAllHad->Branch("AllHadTrigAcceptBits"  , &AllHadTrigAcceptBits);


  TreeAllHad->Branch("PassMETFilters"                        , & PassMETFilters                     ,    "PassMETFilters/I"                          );                                  
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
  TreeAllHad->Branch("Jet0SDmass"                            , & Jet0SDmass                         ,    "Jet0SDmass/F"                              );                                         
  TreeAllHad->Branch("Jet0SDmassRaw"                         , & Jet0SDmassRaw                      ,    "Jet0SDmassRaw/F"                           );                                               
  TreeAllHad->Branch("Jet0SDmassCorrL23"                     , & Jet0SDmassCorrL23                  ,    "Jet0SDmassCorrL23/F"                       );                                                    
  TreeAllHad->Branch("Jet0SDmassCorrL23Up"                   , & Jet0SDmassCorrL23Up                ,    "Jet0SDmassCorrL23Up/F"                     );                                                      
  TreeAllHad->Branch("Jet0SDmassCorrL23Dn"                   , & Jet0SDmassCorrL23Dn                ,    "Jet0SDmassCorrL23Dn/F"                     );                                                      
  TreeAllHad->Branch("Jet0SDmassCorrL123"                    , & Jet0SDmassCorrL123                 ,    "Jet0SDmassCorrL123/F"                      );                                                      
  TreeAllHad->Branch("Jet0SDmassCorrL123Up"                  , & Jet0SDmassCorrL123Up               ,    "Jet0SDmassCorrL123Up/F"                    );                                                        
  TreeAllHad->Branch("Jet0SDmassCorrL123Dn"                  , & Jet0SDmassCorrL123Dn               ,    "Jet0SDmassCorrL123Dn/F"                    );                                                        
  TreeAllHad->Branch("Jet0SDmassCorrL23Smear"                , & Jet0SDmassCorrL23Smear             ,    "Jet0SDmassCorrL23Smear/F"                  );                                                     
  TreeAllHad->Branch("Jet0SDmassCorrL23SmearUp"              , & Jet0SDmassCorrL23SmearUp           ,    "Jet0SDmassCorrL23SmearUp/F"                );                                                       
  TreeAllHad->Branch("Jet0SDmassCorrL23SmearDn"              , & Jet0SDmassCorrL23SmearDn           ,    "Jet0SDmassCorrL23SmearDn/F"                );   
  TreeAllHad->Branch("Jet0SDptRaw"                           , & Jet0SDptRaw                        ,    "Jet0SDptRaw/F"                             );                                               
  TreeAllHad->Branch("Jet0SDptCorrL23"                       , & Jet0SDptCorrL23                    ,    "Jet0SDptCorrL23/F"                         );                                                    
  TreeAllHad->Branch("Jet0SDptCorrL23Up"                     , & Jet0SDptCorrL23Up                  ,    "Jet0SDptCorrL23Up/F"                       );                                                      
  TreeAllHad->Branch("Jet0SDptCorrL23Dn"                     , & Jet0SDptCorrL23Dn                  ,    "Jet0SDptCorrL23Dn/F"                       );                                                      
  TreeAllHad->Branch("Jet0SDptCorrL123"                      , & Jet0SDptCorrL123                   ,    "Jet0SDptCorrL123/F"                        );                                                      
  TreeAllHad->Branch("Jet0SDptCorrL123Up"                    , & Jet0SDptCorrL123Up                 ,    "Jet0SDptCorrL123Up/F"                      );                                                        
  TreeAllHad->Branch("Jet0SDptCorrL123Dn"                    , & Jet0SDptCorrL123Dn                 ,    "Jet0SDptCorrL123Dn/F"                      );                                                        
  TreeAllHad->Branch("Jet0SDptCorrL23Smear"                  , & Jet0SDptCorrL23Smear               ,    "Jet0SDptCorrL23Smear/F"                    );                                                     
  TreeAllHad->Branch("Jet0SDptCorrL23SmearUp"                , & Jet0SDptCorrL23SmearUp             ,    "Jet0SDptCorrL23SmearUp/F"                  );                                                       
  TreeAllHad->Branch("Jet0SDptCorrL23SmearDn"                , & Jet0SDptCorrL23SmearDn             ,    "Jet0SDptCorrL23SmearDn/F"                  );                                                     
  TreeAllHad->Branch("Jet0SDetaRaw"                          , & Jet0SDetaRaw                       ,    "Jet0SDetaRaw/F"                            );                                               
  TreeAllHad->Branch("Jet0SDphiRaw"                          , & Jet0SDphiRaw                       ,    "Jet0SDphiRaw/F"                            );                                               
  TreeAllHad->Branch("Jet0MassPruned"                        , & Jet0MassPruned                     ,    "Jet0MassPruned/F"                          );                                       
  TreeAllHad->Branch("Jet0MassTrimmed"                       , & Jet0MassTrimmed                    ,    "Jet0MassTrimmed/F"                         );                                       
  TreeAllHad->Branch("Jet0Tau1"                              , & Jet0Tau1                           ,    "Jet0Tau1/F"                                );                                 
  TreeAllHad->Branch("Jet0Tau2"                              , & Jet0Tau2                           ,    "Jet0Tau2/F"                                );                                 
  TreeAllHad->Branch("Jet0Tau3"                              , & Jet0Tau3                           ,    "Jet0Tau3/F"                                );                                 
  TreeAllHad->Branch("Jet0Tau4"                              , & Jet0Tau4                           ,    "Jet0Tau4/F"                                );                                 
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
  TreeAllHad->Branch("Jet0PuppiP"                            , & Jet0PuppiP                         ,    "Jet0PuppiP/F"                              );                                    
  TreeAllHad->Branch("Jet0PuppiPt"                           , & Jet0PuppiPt                        ,    "Jet0PuppiPt/F"                             );                                    
  TreeAllHad->Branch("Jet0PuppiEta"                          , & Jet0PuppiEta                       ,    "Jet0PuppiEta/F"                            );                                     
  TreeAllHad->Branch("Jet0PuppiPhi"                          , & Jet0PuppiPhi                       ,    "Jet0PuppiPhi/F"                            );                                     
  TreeAllHad->Branch("Jet0PuppiMass"                         , & Jet0PuppiMass                      ,    "Jet0PuppiMass/F"                           );                                      
  
  TreeAllHad->Branch("Jet0PuppiSDmass"                       , & Jet0PuppiSDmass                    ,   "Jet0PuppiSDmass/F"                          );
  TreeAllHad->Branch("Jet0PuppiSDmassCorr"                   , & Jet0PuppiSDmassCorr                ,   "Jet0PuppiSDmassCorr/F"                      );
  TreeAllHad->Branch("Jet0PuppiSDmassCorrUp"                 , & Jet0PuppiSDmassCorrUp              ,   "Jet0PuppiSDmassCorrUp/F"                    );
  TreeAllHad->Branch("Jet0PuppiSDmassCorrDn"                 , & Jet0PuppiSDmassCorrDn              ,   "Jet0PuppiSDmassCorrDn/F"                    );
  TreeAllHad->Branch("Jet0PuppiSDmassCorrL23Smear"           , & Jet0PuppiSDmassCorrL23Smear        ,   "Jet0PuppiSDmassCorrL23Smear/F"              );
  TreeAllHad->Branch("Jet0PuppiSDmassCorrL23SmearUp"         , & Jet0PuppiSDmassCorrL23SmearUp      ,   "Jet0PuppiSDmassCorrL23SmearUp/F"            );
  TreeAllHad->Branch("Jet0PuppiSDmassCorrL23SmearDn"         , & Jet0PuppiSDmassCorrL23SmearDn      ,   "Jet0PuppiSDmassCorrL23SmearDn/F"            );
  TreeAllHad->Branch("Jet0PuppiSDpt"                         , & Jet0PuppiSDpt                      ,   "Jet0PuppiSDpt/F"                            );
  TreeAllHad->Branch("Jet0PuppiSDptCorr"                     , & Jet0PuppiSDptCorr                  ,   "Jet0PuppiSDptCorr/F"                        );
  TreeAllHad->Branch("Jet0PuppiSDptCorrUp"                   , & Jet0PuppiSDptCorrUp                ,   "Jet0PuppiSDptCorrUp/F"                      );
  TreeAllHad->Branch("Jet0PuppiSDptCorrDn"                   , & Jet0PuppiSDptCorrDn                ,   "Jet0PuppiSDptCorrDn/F"                      );
  TreeAllHad->Branch("Jet0PuppiSDptCorrL23Smear"             , & Jet0PuppiSDptCorrL23Smear          ,   "Jet0PuppiSDptCorrL23Smear/F"                );
  TreeAllHad->Branch("Jet0PuppiSDptCorrL23SmearUp"           , & Jet0PuppiSDptCorrL23SmearUp        ,   "Jet0PuppiSDptCorrL23SmearUp/F"              );
  TreeAllHad->Branch("Jet0PuppiSDptCorrL23SmearDn"           , & Jet0PuppiSDptCorrL23SmearDn        ,   "Jet0PuppiSDptCorrL23SmearDn/F"              );
  TreeAllHad->Branch("Jet0PuppiSDeta"                        , & Jet0PuppiSDeta                     ,   "Jet0PuppiSDeta/F"                           );
  TreeAllHad->Branch("Jet0PuppiSDphi"                        , & Jet0PuppiSDphi                     ,   "Jet0PuppiSDphi/F"                           );
                                                           
  TreeAllHad->Branch("Jet0PuppiTau1"                         , & Jet0PuppiTau1                      ,    "Jet0PuppiTau1/F"                           );                                      
  TreeAllHad->Branch("Jet0PuppiTau2"                         , & Jet0PuppiTau2                      ,    "Jet0PuppiTau2/F"                           );                                      
  TreeAllHad->Branch("Jet0PuppiTau3"                         , & Jet0PuppiTau3                      ,    "Jet0PuppiTau3/F"                           );                                      
  TreeAllHad->Branch("Jet0PuppiTau4"                         , & Jet0PuppiTau4                      ,    "Jet0PuppiTau4/F"                           );                                      
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


  TreeAllHad->Branch("Jet0PuppiCHF"                         , & Jet0PuppiCHF                        ,    "Jet0PuppiCHF/F"                            );                                
  TreeAllHad->Branch("Jet0PuppiNHF"                         , & Jet0PuppiNHF                        ,    "Jet0PuppiNHF/F"                            );                                
  TreeAllHad->Branch("Jet0PuppiCM"                          , & Jet0PuppiCM                         ,    "Jet0PuppiCM/F"                             );                               
  TreeAllHad->Branch("Jet0PuppiNM"                          , & Jet0PuppiNM                         ,    "Jet0PuppiNM/F"                             );                               
  TreeAllHad->Branch("Jet0PuppiNEF"                         , & Jet0PuppiNEF                        ,    "Jet0PuppiNEF/F"                            );                                
  TreeAllHad->Branch("Jet0PuppiCEF"                         , & Jet0PuppiCEF                        ,    "Jet0PuppiCEF/F"                            );                                
  TreeAllHad->Branch("Jet0PuppiMF"                          , & Jet0PuppiMF                         ,    "Jet0PuppiMF/F"                             );                               
  TreeAllHad->Branch("Jet0PuppiMult"                        , & Jet0PuppiMult                       ,    "Jet0PuppiMult/F"                           );  

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
  // TreeAllHad->Branch("Jet0MatchedGenJetDR"                   , & Jet0MatchedGenJetDR                ,    "Jet0MatchedGenJetDR/F"                     );                                            
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
  std::cout<<"Setup Jet0 in tree"<<std::endl;
  
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
  TreeAllHad->Branch("Jet1SDmass"                            , & Jet1SDmass                         ,    "Jet1SDmass/F"                              );                                         
  TreeAllHad->Branch("Jet1SDmassRaw"                         , & Jet1SDmassRaw                      ,    "Jet1SDmassRaw/F"                           );                                               
  TreeAllHad->Branch("Jet1SDmassCorrL23"                     , & Jet1SDmassCorrL23                  ,    "Jet1SDmassCorrL23/F"                       );                                                    
  TreeAllHad->Branch("Jet1SDmassCorrL23Up"                   , & Jet1SDmassCorrL23Up                ,    "Jet1SDmassCorrL23Up/F"                     );                                                      
  TreeAllHad->Branch("Jet1SDmassCorrL23Dn"                   , & Jet1SDmassCorrL23Dn                ,    "Jet1SDmassCorrL23Dn/F"                     );                                                      
  TreeAllHad->Branch("Jet1SDmassCorrL123"                    , & Jet1SDmassCorrL123                 ,    "Jet1SDmassCorrL123/F"                      );                                                      
  TreeAllHad->Branch("Jet1SDmassCorrL123Up"                  , & Jet1SDmassCorrL123Up               ,    "Jet1SDmassCorrL123Up/F"                    );                                                        
  TreeAllHad->Branch("Jet1SDmassCorrL123Dn"                  , & Jet1SDmassCorrL123Dn               ,    "Jet1SDmassCorrL123Dn/F"                    );                                                        
  TreeAllHad->Branch("Jet1SDmassCorrL23Smear"                   , & Jet1SDmassCorrL23Smear                ,    "Jet1SDmassCorrL23Smear/F"                     );                                                     
  TreeAllHad->Branch("Jet1SDmassCorrL23SmearUp"                 , & Jet1SDmassCorrL23SmearUp              ,    "Jet1SDmassCorrL23SmearUp/F"                   );                                                       
  TreeAllHad->Branch("Jet1SDmassCorrL23SmearDn"                 , & Jet1SDmassCorrL23SmearDn              ,    "Jet1SDmassCorrL23SmearDn/F"                   );   
  TreeAllHad->Branch("Jet1SDptRaw"                           , & Jet1SDptRaw                        ,    "Jet1SDptRaw/F"                             );                                               
  TreeAllHad->Branch("Jet1SDptCorrL23"                       , & Jet1SDptCorrL23                    ,    "Jet1SDptCorrL23/F"                         );                                                    
  TreeAllHad->Branch("Jet1SDptCorrL23Up"                     , & Jet1SDptCorrL23Up                  ,    "Jet1SDptCorrL23Up/F"                       );                                                      
  TreeAllHad->Branch("Jet1SDptCorrL23Dn"                     , & Jet1SDptCorrL23Dn                  ,    "Jet1SDptCorrL23Dn/F"                       );                                                      
  TreeAllHad->Branch("Jet1SDptCorrL123"                      , & Jet1SDptCorrL123                   ,    "Jet1SDptCorrL123/F"                        );                                                      
  TreeAllHad->Branch("Jet1SDptCorrL123Up"                    , & Jet1SDptCorrL123Up                 ,    "Jet1SDptCorrL123Up/F"                      );                                                        
  TreeAllHad->Branch("Jet1SDptCorrL123Dn"                    , & Jet1SDptCorrL123Dn                 ,    "Jet1SDptCorrL123Dn/F"                      );                                                        
  TreeAllHad->Branch("Jet1SDptCorrL23Smear"                     , & Jet1SDptCorrL23Smear                  ,    "Jet1SDptCorrL23Smear/F"                       );                                                     
  TreeAllHad->Branch("Jet1SDptCorrL23SmearUp"                   , & Jet1SDptCorrL23SmearUp                ,    "Jet1SDptCorrL23SmearUp/F"                     );                                                       
  TreeAllHad->Branch("Jet1SDptCorrL23SmearDn"                   , & Jet1SDptCorrL23SmearDn                ,    "Jet1SDptCorrL23SmearDn/F"                     );                                                     
  TreeAllHad->Branch("Jet1SDetaRaw"                          , & Jet1SDetaRaw                       ,    "Jet1SDetaRaw/F"                            );                                               
  TreeAllHad->Branch("Jet1SDphiRaw"                          , & Jet1SDphiRaw                       ,    "Jet1SDphiRaw/F"                            );  

  TreeAllHad->Branch("Jet1MassPruned"                        , & Jet1MassPruned                     ,    "Jet1MassPruned/F"                          );                                       
  TreeAllHad->Branch("Jet1MassTrimmed"                       , & Jet1MassTrimmed                    ,    "Jet1MassTrimmed/F"                          );                                       
  TreeAllHad->Branch("Jet1Tau1"                              , & Jet1Tau1                           ,    "Jet1Tau1/F"                                );                                 
  TreeAllHad->Branch("Jet1Tau2"                              , & Jet1Tau2                           ,    "Jet1Tau2/F"                                );                                 
  TreeAllHad->Branch("Jet1Tau3"                              , & Jet1Tau3                           ,    "Jet1Tau3/F"                                );                                 
  TreeAllHad->Branch("Jet1Tau4"                              , & Jet1Tau4                           ,    "Jet1Tau4/F"                                );                                 
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
  TreeAllHad->Branch("Jet1PuppiP"                            , & Jet1PuppiP                         ,    "Jet1PuppiP/F"                              );                                    
  TreeAllHad->Branch("Jet1PuppiPt"                           , & Jet1PuppiPt                        ,    "Jet1PuppiPt/F"                             );                                    
  TreeAllHad->Branch("Jet1PuppiEta"                          , & Jet1PuppiEta                       ,    "Jet1PuppiEta/F"                            );                                     
  TreeAllHad->Branch("Jet1PuppiPhi"                          , & Jet1PuppiPhi                       ,    "Jet1PuppiPhi/F"                            );                                     
  TreeAllHad->Branch("Jet1PuppiMass"                         , & Jet1PuppiMass                      ,    "Jet1PuppiMass/F"                           );                                      
  
  TreeAllHad->Branch("Jet1PuppiSDmass"                       , & Jet1PuppiSDmass                    ,   "Jet1PuppiSDmass/F"                          );
  TreeAllHad->Branch("Jet1PuppiSDmassCorr"                   , & Jet1PuppiSDmassCorr                ,   "Jet1PuppiSDmassCorr/F"                      );
  TreeAllHad->Branch("Jet1PuppiSDmassCorrUp"                 , & Jet1PuppiSDmassCorrUp              ,   "Jet1PuppiSDmassCorrUp/F"                    );
  TreeAllHad->Branch("Jet1PuppiSDmassCorrDn"                 , & Jet1PuppiSDmassCorrDn              ,   "Jet1PuppiSDmassCorrDn/F"                    );
  TreeAllHad->Branch("Jet1PuppiSDmassCorrL23Smear"           , & Jet1PuppiSDmassCorrL23Smear        ,   "Jet1PuppiSDmassCorrL23Smear/F"              );
  TreeAllHad->Branch("Jet1PuppiSDmassCorrL23SmearUp"         , & Jet1PuppiSDmassCorrL23SmearUp      ,   "Jet1PuppiSDmassCorrL23SmearUp/F"            );
  TreeAllHad->Branch("Jet1PuppiSDmassCorrL23SmearDn"         , & Jet1PuppiSDmassCorrL23SmearDn      ,   "Jet1PuppiSDmassCorrL23SmearDn/F"            );
  TreeAllHad->Branch("Jet1PuppiSDpt"                         , & Jet1PuppiSDpt                      ,   "Jet1PuppiSDpt/F"                            );
  TreeAllHad->Branch("Jet1PuppiSDptCorr"                     , & Jet1PuppiSDptCorr                  ,   "Jet1PuppiSDptCorr/F"                        );
  TreeAllHad->Branch("Jet1PuppiSDptCorrUp"                   , & Jet1PuppiSDptCorrUp                ,   "Jet1PuppiSDptCorrUp/F"                      );
  TreeAllHad->Branch("Jet1PuppiSDptCorrDn"                   , & Jet1PuppiSDptCorrDn                ,   "Jet1PuppiSDptCorrDn/F"                      );
  TreeAllHad->Branch("Jet1PuppiSDptCorrL23Smear"             , & Jet1PuppiSDptCorrL23Smear          ,   "Jet1PuppiSDptCorrL23Smear/F"                );
  TreeAllHad->Branch("Jet1PuppiSDptCorrL23SmearUp"           , & Jet1PuppiSDptCorrL23SmearUp        ,   "Jet1PuppiSDptCorrL23SmearUp/F"              );
  TreeAllHad->Branch("Jet1PuppiSDptCorrL23SmearDn"           , & Jet1PuppiSDptCorrL23SmearDn        ,   "Jet1PuppiSDptCorrL23SmearDn/F"              );
  TreeAllHad->Branch("Jet1PuppiSDeta"                        , & Jet1PuppiSDeta                     ,   "Jet1PuppiSDeta/F"                           );
  TreeAllHad->Branch("Jet1PuppiSDphi"                        , & Jet1PuppiSDphi                     ,   "Jet1PuppiSDphi/F"                           );
                         
  TreeAllHad->Branch("Jet1PuppiTau1"                         , & Jet1PuppiTau1                      ,    "Jet1PuppiTau1/F"                           );                                      
  TreeAllHad->Branch("Jet1PuppiTau2"                         , & Jet1PuppiTau2                      ,    "Jet1PuppiTau2/F"                           );                                      
  TreeAllHad->Branch("Jet1PuppiTau3"                         , & Jet1PuppiTau3                      ,    "Jet1PuppiTau3/F"                           );                                      
  TreeAllHad->Branch("Jet1PuppiTau4"                         , & Jet1PuppiTau4                      ,    "Jet1PuppiTau4/F"                           );                                      
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
  TreeAllHad->Branch("Jet1PuppiCHF"                          , & Jet1PuppiCHF                       ,    "Jet1PuppiCHF/F"                            );                                
  TreeAllHad->Branch("Jet1PuppiNHF"                          , & Jet1PuppiNHF                       ,    "Jet1PuppiNHF/F"                            );                                
  TreeAllHad->Branch("Jet1PuppiCM"                           , & Jet1PuppiCM                        ,    "Jet1PuppiCM/F"                             );                               
  TreeAllHad->Branch("Jet1PuppiNM"                           , & Jet1PuppiNM                        ,    "Jet1PuppiNM/F"                             );                               
  TreeAllHad->Branch("Jet1PuppiNEF"                          , & Jet1PuppiNEF                       ,    "Jet1PuppiNEF/F"                            );                                
  TreeAllHad->Branch("Jet1PuppiCEF"                          , & Jet1PuppiCEF                       ,    "Jet1PuppiCEF/F"                            );                                
  TreeAllHad->Branch("Jet1PuppiMF"                           , & Jet1PuppiMF                        ,    "Jet1PuppiMF/F"                             );                               
  TreeAllHad->Branch("Jet1PuppiMult"                         , & Jet1PuppiMult                      ,    "Jet1PuppiMult/F"                           );                                     
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
  // TreeAllHad->Branch("Jet1MatchedGenJetDR"                   , & Jet1MatchedGenJetDR                ,    "Jet1MatchedGenJetDR/F"                     );                                            
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
  std::cout<<"Setup Jet1 in tree"<<std::endl;

  TreeAllHad->Branch("AllHadMETpx"                           , & AllHadMETpx                        ,    "AllHadMETpx/F"                             );                                    
  TreeAllHad->Branch("AllHadMETpy"                           , & AllHadMETpy                        ,    "AllHadMETpy/F"                             );                                    
  TreeAllHad->Branch("AllHadMETpt"                           , & AllHadMETpt                        ,    "AllHadMETpt/F"                             );                                    
  TreeAllHad->Branch("AllHadMETphi"                          , & AllHadMETphi                       ,    "AllHadMETphi/F"                            );                                     
  TreeAllHad->Branch("AllHadMETsumET"                        , & AllHadMETsumET                     ,    "AllHadMETsumET/F"                          );                                     
  TreeAllHad->Branch("AllHadNvtx"                            , & AllHadNvtx                         ,    "AllHadNvtx/F"                              );                                   
  TreeAllHad->Branch("AllHadRho"                             , & AllHadRho                          ,    "AllHadRho/F"                               );                                  
  TreeAllHad->Branch("AllHadEventWeight"                     , & AllHadEventWeight                  ,    "AllHadEventWeight/F"                       );                                          
  TreeAllHad->Branch("AllHadPUweight"                  , & AllHadPUweight               , "AllHadPUweight/F"            );
  TreeAllHad->Branch("AllHadPUweight_MBup"                  , & AllHadPUweight_MBup               , "AllHadPUweight_MBup/F"            );
  TreeAllHad->Branch("AllHadPUweight_MBdn"                  , & AllHadPUweight_MBdn               , "AllHadPUweight_MBdn/F"            );
       
  
  

  TreeAllHad->Branch("DijetMass"                             , & DijetMass                          ,    "DijetMass/F"                               );                                  
  TreeAllHad->Branch("DijetMassPuppi"                        , & DijetMassPuppi                     ,    "DijetMassPuppi/F"                          );                                  
  TreeAllHad->Branch("DijetDeltaR"                           , & DijetDeltaR                        ,    "DijetDeltaR/F"                             );                                    
  TreeAllHad->Branch("DijetDeltaPhi"                         , & DijetDeltaPhi                      ,    "DijetDeltaPhi/F"                           );                                      
  TreeAllHad->Branch("DijetDeltaRap"                         , & DijetDeltaRap                      ,    "DijetDeltaRap/F"                           );                                      
  TreeAllHad->Branch("DiGenJetMass"                          , & DiGenJetMass                       ,    "DiGenJetMass/F"                            );                                     
  TreeAllHad->Branch("GenTTmass"                             , & GenTTmass                          ,    "GenTTmass/F"                               );                                  
  TreeAllHad->Branch("HT"                                    , & HT                                 ,    "HT/F"                                      );                           
  TreeAllHad->Branch("HT_CorrDn"                             , & HT_CorrDn                          ,    "HT_CorrDn/F"                               );                                  
  TreeAllHad->Branch("HT_CorrUp"                             , & HT_CorrUp                          ,    "HT_CorrUp/F"                               );                                  
  TreeAllHad->Branch("HT_PtSmearNom"                         , & HT_PtSmearNom                      ,    "HT_PtSmearNom/F"                           );                                     
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
       
  TreeSemiLept->Branch("SemiLeptTrigNames"    , "vector<std::string>", &SemiLeptTrigNames);
  TreeSemiLept->Branch("SemiLeptTrigPrescales" , "vector<int>",  &SemiLeptTrigPrescales);
  TreeSemiLept->Branch("SemiLeptTrigPass"      , "vector<bool>", &SemiLeptTrigPass);
  TreeSemiLept->Branch("SemiLeptTrigAcceptBits", &SemiLeptTrigAcceptBits);



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
  
  TreeSemiLept->Branch("JetSDmass"                            , & JetSDmass                         ,    "JetSDmass/F"                              );                                         
  TreeSemiLept->Branch("JetSDmassRaw"                         , & JetSDmassRaw                      ,    "JetSDmassRaw/F"                           );                                               
  TreeSemiLept->Branch("JetSDmassCorrL23"                     , & JetSDmassCorrL23                  ,    "JetSDmassCorrL23/F"                       );                                                    
  TreeSemiLept->Branch("JetSDmassCorrL23Up"                   , & JetSDmassCorrL23Up                ,    "JetSDmassCorrL23Up/F"                     );                                                      
  TreeSemiLept->Branch("JetSDmassCorrL23Dn"                   , & JetSDmassCorrL23Dn                ,    "JetSDmassCorrL23Dn/F"                     );                                                      
  TreeSemiLept->Branch("JetSDmassCorrL123"                    , & JetSDmassCorrL123                 ,    "JetSDmassCorrL123/F"                      );                                                      
  TreeSemiLept->Branch("JetSDmassCorrL123Up"                  , & JetSDmassCorrL123Up               ,    "JetSDmassCorrL123Up/F"                    );                                                        
  TreeSemiLept->Branch("JetSDmassCorrL123Dn"                  , & JetSDmassCorrL123Dn               ,    "JetSDmassCorrL123Dn/F"                    );                                                        
  TreeSemiLept->Branch("JetSDmassCorrL23Smear"                , & JetSDmassCorrL23Smear             ,    "JetSDmassCorrL23Smear/F"                     );                                                     
  TreeSemiLept->Branch("JetSDmassCorrL23SmearUp"              , & JetSDmassCorrL23SmearUp           ,    "JetSDmassCorrL23SmearUp/F"                   );                                                       
  TreeSemiLept->Branch("JetSDmassCorrL23SmearDn"              , & JetSDmassCorrL23SmearDn           ,    "JetSDmassCorrL23SmearDn/F"                   );   
  TreeSemiLept->Branch("JetSDptRaw"                           , & JetSDptRaw                        ,    "JetSDptRaw/F"                             );                                               
  TreeSemiLept->Branch("JetSDptCorrL23"                       , & JetSDptCorrL23                    ,    "JetSDptCorrL23/F"                         );                                                    
  TreeSemiLept->Branch("JetSDptCorrL23Up"                     , & JetSDptCorrL23Up                  ,    "JetSDptCorrL23Up/F"                       );                                                      
  TreeSemiLept->Branch("JetSDptCorrL23Dn"                     , & JetSDptCorrL23Dn                  ,    "JetSDptCorrL23Dn/F"                       );                                                      
  TreeSemiLept->Branch("JetSDptCorrL123"                      , & JetSDptCorrL123                   ,    "JetSDptCorrL123/F"                        );                                                      
  TreeSemiLept->Branch("JetSDptCorrL123Up"                    , & JetSDptCorrL123Up                 ,    "JetSDptCorrL123Up/F"                      );                                                        
  TreeSemiLept->Branch("JetSDptCorrL123Dn"                    , & JetSDptCorrL123Dn                 ,    "JetSDptCorrL123Dn/F"                      );                                                        
  TreeSemiLept->Branch("JetSDptCorrL23Smear"                  , & JetSDptCorrL23Smear               ,    "JetSDptCorrL23Smear/F"                       );                                                     
  TreeSemiLept->Branch("JetSDptCorrL23SmearUp"                , & JetSDptCorrL23SmearUp             ,    "JetSDptCorrL23SmearUp/F"                     );                                                       
  TreeSemiLept->Branch("JetSDptCorrL23SmearDn"                , & JetSDptCorrL23SmearDn             ,    "JetSDptCorrL23SmearDn/F"                     );                                                     
  TreeSemiLept->Branch("JetSDetaRaw"                          , & JetSDetaRaw                       ,    "JetSDetaRaw/F"                            );                                               
  TreeSemiLept->Branch("JetSDphiRaw"                          , & JetSDphiRaw                       ,    "JetSDphiRaw/F"                            );  

  TreeSemiLept->Branch("JetMassPruned"                        , & JetMassPruned                     ,    "JetMassPruned/F"                          );                                       
  TreeSemiLept->Branch("JetMassTrimmed"                       , & JetMassTrimmed                    ,    "JetMassTrimmed/F"                         );                                       
  TreeSemiLept->Branch("JetTau1"                              , & JetTau1                           ,    "JetTau1/F"                                );                                 
  TreeSemiLept->Branch("JetTau2"                              , & JetTau2                           ,    "JetTau2/F"                                );                                 
  TreeSemiLept->Branch("JetTau3"                              , & JetTau3                           ,    "JetTau3/F"                                );                                 
  TreeSemiLept->Branch("JetTau4"                              , & JetTau4                           ,    "JetTau4/F"                                );                                 
  TreeSemiLept->Branch("JetTau32"                             , & JetTau32                          ,    "JetTau32/F"                               );                                  
  TreeSemiLept->Branch("JetTau21"                             , & JetTau21                          ,    "JetTau21/F"                               );                                  
  TreeSemiLept->Branch("JetSDmaxbdisc"                        , & JetSDmaxbdisc                     ,    "JetSDmaxbdisc/F"                          );                                       
  TreeSemiLept->Branch("JetSDmaxbdiscflavHadron"              , & JetSDmaxbdiscflavHadron           ,    "JetSDmaxbdiscflavHadron/F"                );                                           
  TreeSemiLept->Branch("JetSDmaxbdiscflavParton"              , & JetSDmaxbdiscflavParton           ,    "JetSDmaxbdiscflavParton/F"                );  
                                         
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

  TreeSemiLept->Branch("JetPuppiP"                            , & JetPuppiP                         ,    "JetPuppiP/F"                              );                                    
  TreeSemiLept->Branch("JetPuppiPt"                           , & JetPuppiPt                        ,    "JetPuppiPt/F"                             );                                    
  TreeSemiLept->Branch("JetPuppiEta"                          , & JetPuppiEta                       ,    "JetPuppiEta/F"                            );                                     
  TreeSemiLept->Branch("JetPuppiPhi"                          , & JetPuppiPhi                       ,    "JetPuppiPhi/F"                            );                                     
  TreeSemiLept->Branch("JetPuppiMass"                         , & JetPuppiMass                      ,    "JetPuppiMass/F"                           );                                      

  
  TreeSemiLept->Branch("JetPuppiSDmass"                         , & JetPuppiSDmass                    ,    "JetPuppiSDmass/F"                          );
  TreeSemiLept->Branch("JetPuppiSDmassCorr"                     , & JetPuppiSDmassCorr                ,    "JetPuppiSDmassCorr/F"                      );
  TreeSemiLept->Branch("JetPuppiSDmassCorrUp"                   , & JetPuppiSDmassCorrUp              ,    "JetPuppiSDmassCorrUp/F"                    );
  TreeSemiLept->Branch("JetPuppiSDmassCorrDn"                   , & JetPuppiSDmassCorrDn              ,    "JetPuppiSDmassCorrDn/F"                    );
  TreeSemiLept->Branch("JetPuppiSDmassCorrL23Smear"             , & JetPuppiSDmassCorrL23Smear        ,    "JetPuppiSDmassCorrL23Smear/F"              );
  TreeSemiLept->Branch("JetPuppiSDmassCorrL23SmearUp"           , & JetPuppiSDmassCorrL23SmearUp      ,    "JetPuppiSDmassCorrL23SmearUp/F"            );
  TreeSemiLept->Branch("JetPuppiSDmassCorrL23SmearDn"           , & JetPuppiSDmassCorrL23SmearDn      ,    "JetPuppiSDmassCorrL23SmearDn/F"            );
  TreeSemiLept->Branch("JetPuppiSDpt"                           , & JetPuppiSDpt                      ,    "JetPuppiSDpt/F"                            );
  TreeSemiLept->Branch("JetPuppiSDptCorr"                       , & JetPuppiSDptCorr                  ,    "JetPuppiSDptCorr/F"                        );
  TreeSemiLept->Branch("JetPuppiSDptCorrUp"                     , & JetPuppiSDptCorrUp                ,    "JetPuppiSDptCorrUp/F"                      );
  TreeSemiLept->Branch("JetPuppiSDptCorrDn"                     , & JetPuppiSDptCorrDn                ,    "JetPuppiSDptCorrDn/F"                      );
  TreeSemiLept->Branch("JetPuppiSDptCorrL23Smear"               , & JetPuppiSDptCorrL23Smear          ,    "JetPuppiSDptCorrL23Smear/F"                );
  TreeSemiLept->Branch("JetPuppiSDptCorrL23SmearUp"             , & JetPuppiSDptCorrL23SmearUp        ,    "JetPuppiSDptCorrL23SmearUp/F"              );
  TreeSemiLept->Branch("JetPuppiSDptCorrL23SmearDn"             , & JetPuppiSDptCorrL23SmearDn        ,    "JetPuppiSDptCorrL23SmearDn/F"              );
  TreeSemiLept->Branch("JetPuppiSDeta"                          , & JetPuppiSDeta                     ,    "JetPuppiSDeta/F"                           );
  TreeSemiLept->Branch("JetPuppiSDphi"                          , & JetPuppiSDphi                     ,    "JetPuppiSDphi/F"                           );
                         

  TreeSemiLept->Branch("JetPuppiTau1"                         , & JetPuppiTau1                      ,    "JetPuppiTau1/F"                           );                                      
  TreeSemiLept->Branch("JetPuppiTau2"                         , & JetPuppiTau2                      ,    "JetPuppiTau2/F"                           );                                      
  TreeSemiLept->Branch("JetPuppiTau3"                         , & JetPuppiTau3                      ,    "JetPuppiTau3/F"                           );                                      
  TreeSemiLept->Branch("JetPuppiTau4"                         , & JetPuppiTau4                      ,    "JetPuppiTau4/F"                           );                                      
  TreeSemiLept->Branch("JetPuppiTau32"                        , & JetPuppiTau32                     ,    "JetPuppiTau32/F"                          );                                       
  TreeSemiLept->Branch("JetPuppiTau21"                        , & JetPuppiTau21                     ,    "JetPuppiTau21/F"                          );                                       

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


  TreeSemiLept->Branch("JetCHF"                               , & JetCHF                            ,    "JetCHF/F"                                 );                                
  TreeSemiLept->Branch("JetNHF"                               , & JetNHF                            ,    "JetNHF/F"                                 );                                
  TreeSemiLept->Branch("JetCM"                                , & JetCM                             ,    "JetCM/F"                                  );                               
  TreeSemiLept->Branch("JetNM"                                , & JetNM                             ,    "JetNM/F"                                  );                               
  TreeSemiLept->Branch("JetNEF"                               , & JetNEF                            ,    "JetNEF/F"                                 );                                
  TreeSemiLept->Branch("JetCEF"                               , & JetCEF                            ,    "JetCEF/F"                                 );                                
  TreeSemiLept->Branch("JetMF"                                , & JetMF                             ,    "JetMF/F"                                  );                               
  TreeSemiLept->Branch("JetMult"                              , & JetMult                           ,    "JetMult/F"                                );
  TreeSemiLept->Branch("JetPuppiCHF"                          , & JetPuppiCHF                       ,    "JetPuppiCHF/F"                            );                                
  TreeSemiLept->Branch("JetPuppiNHF"                          , & JetPuppiNHF                       ,    "JetPuppiNHF/F"                            );                                
  TreeSemiLept->Branch("JetPuppiCM"                           , & JetPuppiCM                        ,    "JetPuppiCM/F"                             );                               
  TreeSemiLept->Branch("JetPuppiNM"                           , & JetPuppiNM                        ,    "JetPuppiNM/F"                             );                               
  TreeSemiLept->Branch("JetPuppiNEF"                          , & JetPuppiNEF                       ,    "JetPuppiNEF/F"                            );                                
  TreeSemiLept->Branch("JetPuppiCEF"                          , & JetPuppiCEF                       ,    "JetPuppiCEF/F"                            );                                
  TreeSemiLept->Branch("JetPuppiMF"                           , & JetPuppiMF                        ,    "JetPuppiMF/F"                             );                               
  TreeSemiLept->Branch("JetPuppiMult"                         , & JetPuppiMult                      ,    "JetPuppiMult/F"                           );                                  
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
  // TreeSemiLept->Branch("JetMatchedGenJetDR"                   , & JetMatchedGenJetDR                ,    "JetMatchedGenJetDR/F"                     );                                            
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
  std::cout<<"Setup semi-lept jets in tree"<<std::endl;


  TreeSemiLept->Branch("SemiLeptMETpx"                        , & SemiLeptMETpx                     , "SemiLeptMETpx/F"                  );
  TreeSemiLept->Branch("SemiLeptMETpy"                        , & SemiLeptMETpy                     , "SemiLeptMETpy/F"                  );
  TreeSemiLept->Branch("SemiLeptMETpt"                        , & SemiLeptMETpt                     , "SemiLeptMETpt/F"                  );
  TreeSemiLept->Branch("SemiLeptMETphi"                       , & SemiLeptMETphi                    , "SemiLeptMETphi/F"                 );
  TreeSemiLept->Branch("SemiLeptMETsumET"                     , & SemiLeptMETsumET                  , "SemiLeptMETsumET/F"               );
  TreeSemiLept->Branch("SemiLeptNvtx"                         , & SemiLeptNvtx                      , "SemiLeptNvtx/F"                   );
  TreeSemiLept->Branch("SemiLeptRho"                          , & SemiLeptRho                       , "SemiLeptRho/F"                    );
  TreeSemiLept->Branch("SemiLeptEventWeight"                  , & SemiLeptEventWeight               , "SemiLeptEventWeight/F"            );
  TreeSemiLept->Branch("SemiLeptPUweight"                  , & SemiLeptPUweight               , "SemiLeptPUweight/F"            );
  TreeSemiLept->Branch("SemiLeptPUweight_MBup"                  , & SemiLeptPUweight_MBup               , "SemiLeptPUweight_MBup/F"            );
  TreeSemiLept->Branch("SemiLeptPUweight_MBdn"                  , & SemiLeptPUweight_MBdn               , "SemiLeptPUweight_MBdn/F"            );
       
  
  
 
  TreeSemiLept->Branch("SemiLeptGenTTmass"                    , & SemiLeptGenTTmass                 , "SemiLeptGenTTmass/F"              );
  
  TreeSemiLept->Branch("HTlep"                                , & HTlep                             , "HTlep/F"                  );
  TreeSemiLept->Branch("ST"                                   , & ST                                , "ST/F"                     );
  TreeSemiLept->Branch("ST_CorrDn"                            , & ST_CorrDn                         , "ST_CorrDn/F"              );
  TreeSemiLept->Branch("ST_CorrUp"                            , & ST_CorrUp                         , "ST_CorrUp/F"              );
  TreeSemiLept->Branch("ST_PtSmearNom"                        , & ST_PtSmearNom                     , "ST_PtSmearNom/F"          );
  TreeSemiLept->Branch("ST_PtSmearUp"                         , & ST_PtSmearUp                      , "ST_PtSmearUp/F"           );
  TreeSemiLept->Branch("ST_PtSmearDn"                         , & ST_PtSmearDn                      , "ST_PtSmearDn/F"           );
  
  TreeSemiLept->Branch("SemiLeptQ2weight_CorrDn"              , & SemiLeptQ2weight_CorrDn           , "SemiLeptQ2weight_CorrDn/F"        );
  TreeSemiLept->Branch("SemiLeptQ2weight_CorrUp"              , & SemiLeptQ2weight_CorrUp           , "SemiLeptQ2weight_CorrUp/F"        );
  TreeSemiLept->Branch("SemiLeptNNPDF3weight_CorrDn"          , & SemiLeptNNPDF3weight_CorrDn       , "SemiLeptNNPDF3weight_CorrDn/F"    );
  TreeSemiLept->Branch("SemiLeptNNPDF3weight_CorrUp"          , & SemiLeptNNPDF3weight_CorrUp       , "SemiLeptNNPDF3weight_CorrUp/F"    );
  TreeSemiLept->Branch("SemiLeptRunNum"                       , & SemiLeptRunNum                    , "SemiLeptRunNum/F"                 );
  TreeSemiLept->Branch("SemiLeptLumiBlock"                    , & SemiLeptLumiBlock                 , "SemiLeptLumiBlock/F"              );
  TreeSemiLept->Branch("SemiLeptEventNum"                     , & SemiLeptEventNum                  , "SemiLeptEventNum/F"               );
  TreeSemiLept->Branch("SemiLeptPassMETFilters"               , & SemiLeptPassMETFilters            , "SemiLeptPassMETFilters/I"         );
 
  TreeSemiLept->Branch("AK4dRminPt"                           , & AK4dRminPt                        , "AK4dRminPt/F"                     );  
  TreeSemiLept->Branch("AK4dRminEta"                          , & AK4dRminEta                       , "AK4dRminEta/F"                    );  
  TreeSemiLept->Branch("AK4dRminPhi"                          , & AK4dRminPhi                       , "AK4dRminPhi/F"                    );  
  TreeSemiLept->Branch("AK4dRminMass"                         , & AK4dRminMass                     , "AK4dRminMass/F"                    );  
  TreeSemiLept->Branch("AK4dRminBdisc"                        , & AK4dRminBdisc                     , "AK4dRminBdisc/F"                  );  
  TreeSemiLept->Branch("AK4dRminLep"                          , & AK4dRminLep                       , "AK4dRminLep/F"                    );  
  TreeSemiLept->Branch("AK4BtagdRminPt"                       , & AK4BtagdRminPt                    , "AK4BtagdRminPt/F"                 );  
  TreeSemiLept->Branch("AK4BtagdRminBdisc"                    , & AK4BtagdRminBdisc                 , "AK4BtagdRminBdisc/F"              );  
  TreeSemiLept->Branch("AK4BtagdRminLep"                      , & AK4BtagdRminLep                   , "AK4BtagdRminLep/F"                );  
  TreeSemiLept->Branch("LepHemiContainsAK4BtagLoose"          , & LepHemiContainsAK4BtagLoose       , "LepHemiContainsAK4BtagLoose/I"    );  
  TreeSemiLept->Branch("LepHemiContainsAK4BtagMedium"         , & LepHemiContainsAK4BtagMedium      , "LepHemiContainsAK4BtagMedium/I"   );  
  TreeSemiLept->Branch("LepHemiContainsAK4BtagTight"          , & LepHemiContainsAK4BtagTight       , "LepHemiContainsAK4BtagTight/I"    );  

  TreeSemiLept->Branch("LeptonPhi"                            , &  LeptonPhi                        , "LeptonPhi/F"                      ); 
  TreeSemiLept->Branch("LeptonPt"                             , &  LeptonPt                         , "LeptonPt/F"                       ); 
  TreeSemiLept->Branch("LeptonEta"                            , &  LeptonEta                        , "LeptonEta/F"                      ); 
  TreeSemiLept->Branch("LeptonMass"                           , &  LeptonMass                       , "LeptonMass/F"                     ); 
  TreeSemiLept->Branch("PtRel"                                , &  PtRel                            , "PtRel/F"                          ); 
  TreeSemiLept->Branch("LeptonIsMu"                           , &  LeptonIsMu                       , "LeptonIsMu/I"                     ); 
  TreeSemiLept->Branch("MuMedium"                             , &  MuMedium                         , "MuMedium/I"                       ); 
  TreeSemiLept->Branch("MuTight"                              , &  MuTight                          , "MuTight/I"                        ); 
  TreeSemiLept->Branch("MuHighPt"                             , &  MuHighPt                         , "MuHighPt/I"                       ); 
  TreeSemiLept->Branch("DeltaRJetLep"                         , &  DeltaRJetLep                     , "DeltaRJetLep/F"                   ); 
  TreeSemiLept->Branch("DeltaPhiJetLep"                       , &  DeltaPhiJetLep                   , "DeltaPhiJetLep/F"                 ); 
  

  TreeSemiLept->Branch("MuIso"                                , &  MuIso                            , "MuIso/F"                          ); 
  TreeSemiLept->Branch("Elecron_absiso"                       , &  Elecron_absiso                   , "Elecron_absiso/F"                 ); 
  TreeSemiLept->Branch("Elecron_relIsoWithDBeta"              , &  Elecron_relIsoWithDBeta          , "Elecron_relIsoWithDBeta/F"        ); 
  TreeSemiLept->Branch("Elecron_absiso_EA"                    , &  Elecron_absiso_EA                , "Elecron_absiso_EA/F"              ); 
  TreeSemiLept->Branch("Elecron_relIsoWithEA"                 , &  Elecron_relIsoWithEA             , "Elecron_relIsoWithEA/F"           ); 

  TreeSemiLept->Branch("Electron_isMedium"                 , &  Electron_isMedium             , "Electron_isMedium/I"           ); 
  TreeSemiLept->Branch("Electron_isTight"                  , &  Electron_isTight              , "Electron_isTight/I"            ); 

 
 
 
 
 
 
 
  

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
  using namespace LHAPDF;
  
  if (verbose_) {
    cout<<"----------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"Analyze event "<<iEvent.id().event()<<" run "<<iEvent.id().run()<<" lumiblock "<<iEvent.id().luminosityBlock()<<endl;
  }
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
  // 888    888 888      88888888888 
  // 888    888 888          888     
  // 888    888 888          888     
  // 8888888888 888          888     
  // 888    888 888          888     
  // 888    888 888          888     
  // 888    888 888          888     
  // 888    888 88888888     888     
  // 
  
    edm::Handle<edm::TriggerResults> triggerBits;
    edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
    edm::Handle<pat::PackedTriggerPrescales> triggerPrescales;

    iEvent.getByToken(triggerBits_, triggerBits);
    iEvent.getByToken(triggerObjects_, triggerObjects);
    iEvent.getByToken(triggerPrescales_, triggerPrescales);

    vector<string> trigsToRun;
    trigsToRun.push_back("HLT_PFHT300_v");
    trigsToRun.push_back("HLT_PFHT350_v");
    trigsToRun.push_back("HLT_PFHT400_v");
    trigsToRun.push_back("HLT_PFHT475_v");
    trigsToRun.push_back("HLT_PFHT600_v");
    trigsToRun.push_back("HLT_PFHT650_v");
    trigsToRun.push_back("HLT_PFHT800_v");
    trigsToRun.push_back("HLT_PFHT900_v");
    trigsToRun.push_back("HLT_PFJet320_v");
    trigsToRun.push_back("HLT_PFJet400_v");
    trigsToRun.push_back("HLT_PFJet450_v");
    trigsToRun.push_back("HLT_PFJet500_v");
    trigsToRun.push_back("HLT_AK8PFJet360_TrimMass30_v");
    trigsToRun.push_back("HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v");
    trigsToRun.push_back("HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20_v");
    trigsToRun.push_back("HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_v");
    trigsToRun.push_back("HLT_Mu45_eta2p1_v");
    trigsToRun.push_back("HLT_Mu50_v");
    trigsToRun.push_back("HLT_Mu55_v");
    trigsToRun.push_back("HLT_IsoMu22_eta2p1_v");
    trigsToRun.push_back("HLT_IsoMu24_v");
    trigsToRun.push_back("HLT_IsoMu27_v");
    trigsToRun.push_back("HLT_Mu30_eta2p1_PFJet150_PFJet50_v");
    trigsToRun.push_back("HLT_Mu40_eta2p1_PFJet200_PFJet50_v");
    trigsToRun.push_back("HLT_Ele32_eta2p1_WPTight_Gsf_v");
    trigsToRun.push_back("HLT_Ele35_WPLoose_Gsf_v");
    trigsToRun.push_back("HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50_v");
    trigsToRun.push_back("HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet140_v");
    trigsToRun.push_back("HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165_v");
    trigsToRun.push_back("HLT_Ele105_CaloIdVT_GsfTrkIdT_v");

    const int ntrigs = trigsToRun.size();
    if (verbose_) cout<<"trigsToRun size "<<ntrigs<<endl;

    // do the same thing two different ways ( to test)
    std::bitset<30> hltbit;
    vector<bool> trigAccept;

    AllHadTrigNames       ->clear();
    SemiLeptTrigNames     ->clear();
    AllHadTrigPrescales   ->clear();
    SemiLeptTrigPrescales ->clear();
    AllHadTrigPass        ->clear();
    SemiLeptTrigPass      ->clear();

    const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);
    if (verbose_) std::cout << "\n === TRIGGER PATHS === " << std::endl;
    int counttrigs =0;
    // for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
    for (unsigned int j=0; j<trigsToRun.size(); j++){  // Running this loop first even though it is slow in order to preserve order (temporary solution)
      if (verbose_) cout<<"try to find "<< trigsToRun[j]<<endl;
      for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
        string name = names.triggerName(i);
        //if (verbose_) cout<<" "<<name<<endl;
        std::size_t found = name.find( trigsToRun[j] );
        // cout<<" Check: "<<trigsToRun[j]  <<" = "<<name<< " ?" <<found<<endl;
        if ( found !=std::string::npos ) {
          int accept = triggerBits->accept(i) ;
          bool pass = false;
          if (accept ==1 ) pass = true;
          int prescale = triggerPrescales->getPrescaleForIndex(i)  ;
        
          if (verbose_) std::cout << "  Found Trigger " << names.triggerName(i) << ", prescale " << triggerPrescales->getPrescaleForIndex(i) <<": " << (triggerBits->accept(i) ? "PASS" : "fail (or not run)") << std::endl; 
          trigAccept.push_back(pass);
          // trigStrings.push_back(name);
          // trigPrescale.push_back(prescale);
          AllHadTrigNames       ->push_back(name);
          SemiLeptTrigNames     ->push_back(name);
          AllHadTrigPrescales   ->push_back(prescale);
          SemiLeptTrigPrescales ->push_back(prescale);
          AllHadTrigPass        ->push_back(pass);
          SemiLeptTrigPass      ->push_back(pass);
          if (pass)  hltbit[counttrigs]=1;  
          counttrigs++;
          break;
        }
      }
    }

    if (verbose_) {
      cout<<"trig accept size "<<trigAccept.size()<<endl;
      for (unsigned int i=0; i< trigAccept.size(); i++){
        cout<<trigAccept[trigAccept.size()-1-i];
      }
      cout<<endl;
      cout<<"hlt bit"<<endl;
      cout<<hltbit.to_string()<<endl;
    }

    AllHadTrigAcceptBits   = hltbit.to_string();
    SemiLeptTrigAcceptBits = hltbit.to_string();
    
    // if (verbose_){
    //   cout<<"trigStrings "<<trigStrings.size()<<endl;
    //   cout<<"trigAccept "<<trigAccept.size()<<endl;
    //   cout<<"trigPrescale "<<trigPrescale.size()<<endl;
    // }

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

    // Recomendation:
    // primary vertex filter (available in miniAOD v2)
    // beam halo filter (NEW available in miniAOD v2)
    // HBHE noise filter (available in miniAOD v2)
    // HBHEiso noise filter (available in miniAOD v2)
    // ee badSC noise filter (available in miniAOD v2)
    // ECAL TP filter (available in miniAOD v2)
    // badMuon (NEW not available in miniAOD v2, see snippet below)
    // badCharged hadron (NEW not available in miniAOD v2, see snippet below) 

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
  const reco::Vertex &PV = vertices->front();  // save PV for tight muon ID

  // int nvtxgood =0 ;
  // for (VertexCollection::const_iterator vtx = vertices->begin(); vtx != vertices->end(); ++vtx, ++firstGoodVertexIdx) {
  //   // Replace isFake() for miniAOD because it requires tracks and miniAOD vertices don't have tracks:
  //   // Vertex.h: bool isFake() const {return (chi2_==0 && ndof_==0 && tracks_.empty());}
  //   bool isFake = (vtx->chi2()==0 && vtx->ndof()==0);
  //   if ( !isFake &&  vtx->ndof()>=4. && vtx->position().Rho()<=2.0 && fabs(vtx->position().Z())<=24.0) {
  //     nvtxgood++;
  //   }
  // }
  // cout<<"nvtx "<<nvtx<<" nvtxgood "<<nvtxgood<<endl;
  //
  //  8888888b.  888     888     888       888          d8b          888      888    
  //  888   Y88b 888     888     888   o   888          Y8P          888      888    
  //  888    888 888     888     888  d8b  888                       888      888    
  //  888   d88P 888     888     888 d888b 888  .d88b.  888  .d88b.  88888b.  888888 
  //  8888888P"  888     888     888d88888b888 d8P  Y8b 888 d88P"88b 888 "88b 888    
  //  888        888     888     88888P Y88888 88888888 888 888  888 888  888 888    
  //  888        Y88b. .d88P     8888P   Y8888 Y8b.     888 Y88b 888 888  888 Y88b.  
  //  888         "Y88888P"      888P     Y888  "Y8888  888  "Y88888 888  888  "Y888 
  //                                                             888                 
  //                                                        Y8b d88P                 
  //                                                         "Y88P"                  

  edm::Handle<std::vector<PileupSummaryInfo> > pileup;
  iEvent.getByToken(pileupInfoToken_, pileup);
  int nPU = 0;
  if(pileup.isValid()) { // protection for data
    for(std::vector<PileupSummaryInfo>::const_iterator iPV = pileup->begin(); iPV != pileup->end(); ++iPV) {
      if(iPV->getBunchCrossing() == 0) {
        nPU = iPV->getTrueNumInteractions();  
        //  numGenPV = iPV->getPU_NumInteractions();
        break;
      }
    }
  }

  double puweight   = hPUweight     ->GetBinContent( hPUweight     ->GetXaxis()->FindBin( nPU ) )  ;
  double puweightUp = hPUweight_MBup->GetBinContent( hPUweight_MBup->GetXaxis()->FindBin( nPU ) )  ;
  double puweightDn = hPUweight_MBdn->GetBinContent( hPUweight_MBdn->GetXaxis()->FindBin( nPU ) )  ;

  if (verbose_) std::cout<<"PU weight: "<<puweight<<std::endl;

  h_NtrueIntPU ->Fill(nPU);
  h_NPV ->Fill(nvtx);
  h_NPVreweighted  ->Fill(nvtx,puweight);

  //  888      888    888 8888888888     888       888          d8b          888      888             
  //  888      888    888 888            888   o   888          Y8P          888      888             
  //  888      888    888 888            888  d8b  888                       888      888             
  //  888      8888888888 8888888        888 d888b 888  .d88b.  888  .d88b.  88888b.  888888 .d8888b  
  //  888      888    888 888            888d88888b888 d8P  Y8b 888 d88P"88b 888 "88b 888    88K      
  //  888      888    888 888            88888P Y88888 88888888 888 888  888 888  888 888    "Y8888b. 
  //  888      888    888 888            8888P   Y8888 Y8b.     888 Y88b 888 888  888 Y88b.       X88 
  //  88888888 888    888 8888888888     888P     Y888  "Y8888  888  "Y88888 888  888  "Y888  88888P' 
  //                                                                     888                          
  //                                                                Y8b d88P                          
  //                                                                 "Y88P"                           

  double Q2wgt_up = -999;
  double Q2wgt_down = -999;

  double NNPDF3wgt_up = -999;
  double NNPDF3wgt_down = -999;

  if (isZprime_ || isttbar_){
    edm::Handle<LHEEventProduct> EvtHandle;
    iEvent.getByToken(theSrc_, EvtHandle);

    if (EvtHandle.isValid()){
      double centralWgt = EvtHandle->weights()[0].wgt;

      //Q^2 uncertainties
      if (verbose_) cout << "Calculating Q^2 uncertainties." << endl;
      double maxQ2wgt_frac = 1;
      double minQ2wgt_frac = 1;
      
      if (verbose_) cout << "Q^2 loop" <<endl;
      for (unsigned int iLHE = 0; iLHE < 9; ++iLHE){
	if (iLHE != 5 && iLHE != 7){
	  double Q2wgt = EvtHandle->weights()[iLHE].wgt;
	  if (verbose_) cout << "Q^2 Weight: " << Q2wgt << endl;
	  double Q2wgt_frac = Q2wgt/(centralWgt);
	  if (verbose_) cout << "Fractional Q^2 Weight: " << Q2wgt_frac << endl;
	  maxQ2wgt_frac = max(maxQ2wgt_frac, Q2wgt_frac);
	  minQ2wgt_frac = min(minQ2wgt_frac, Q2wgt_frac);
	}
      }
      
      Q2wgt_up = maxQ2wgt_frac;
      Q2wgt_down = minQ2wgt_frac;

      //NNPDF3 uncertainties
      if (verbose_) cout << "Calculating NNPDF3 uncertainties." << endl;
      double NNPDF3wgtAvg = 0.0;
      double NNPDF3wgtRMS = 0.0;
      double NNPDF3wgt = 0.0;
      double NNPDF3wgt_frac = 0.0;

      //ttbar
      unsigned int PDFstart = 9;
      unsigned int PDFend = 109;

      //Zprime
      if (isZprime_){
	PDFstart = 10;
	PDFend = 110;
      }

      //Making sure central PDF isn't zero                                                                                              
      if (centralWgt == 0){
	NNPDF3wgt_up = 0.0;
        NNPDF3wgt_down = 0.0;
	if (verbose_) cout << "Unphysical: central PDF weight is zero!" << endl;
      }
      else{
	for (unsigned int i_lhePDF = PDFstart; i_lhePDF < PDFend; ++i_lhePDF){
	  NNPDF3wgt = EvtHandle->weights()[i_lhePDF].wgt;
	  NNPDF3wgt_frac = NNPDF3wgt/(centralWgt);
	  NNPDF3wgtAvg += NNPDF3wgt_frac;
	  if (verbose_){
	    cout << "-----" << endl;
	    cout << i_lhePDF - PDFstart << endl;
	    cout << "Fractional PDF weight: " << NNPDF3wgt_frac << endl;
	    cout << "-----" << endl;
	    cout << "" << endl;
	  }
	}

	NNPDF3wgtAvg = NNPDF3wgtAvg/(PDFend - PDFstart);
	if (verbose_) cout << NNPDF3wgtAvg;
      
	for (unsigned int i_lhePDF = PDFstart; i_lhePDF < PDFend; ++i_lhePDF){
	  NNPDF3wgt = EvtHandle->weights()[i_lhePDF].wgt;
	  NNPDF3wgt_frac = NNPDF3wgt/(centralWgt);
	  NNPDF3wgtRMS += (NNPDF3wgt_frac - NNPDF3wgtAvg)*(NNPDF3wgt_frac - NNPDF3wgtAvg);
	}
	
	NNPDF3wgtRMS = sqrt(NNPDF3wgtRMS/(PDFend - PDFstart - 1));
	NNPDF3wgt_up = 1.0 + NNPDF3wgtRMS;
        NNPDF3wgt_down = 1.0 - NNPDF3wgtRMS;
      }
    }
  }

  else if (isRSG_){
    edm::Handle<GenEventInfoProduct> pdfstuff;
    iEvent.getByToken(pdfToken_, pdfstuff);

    LHAPDF::usePDFMember(1,0);

    float q = pdfstuff->pdf()->scalePDF;

    int id1 = pdfstuff->pdf()->id.first;
    double x1 = pdfstuff->pdf()->x.first;
    //double pdf1 = pdfstuff->pdf()->xPDF.first;                                                                                           

    int id2 = pdfstuff->pdf()->id.second;
    double x2 = pdfstuff->pdf()->x.second;
    //double pdf2 = pdfstuff->pdf()->xPDF.second;                                                                                          

    double xpdf1 = LHAPDF::xfx(1, x1, q, id1);
    double xpdf2 = LHAPDF::xfx(1, x2, q, id2);
    double w0 = xpdf1 * xpdf2;
    double sumsq = 0.0;
    for(int i=1; i <=100; ++i){
      LHAPDF::usePDFMember(1,i);
      double xpdf1_new = LHAPDF::xfx(1, x1, q, id1);
      double xpdf2_new = LHAPDF::xfx(1, x2, q, id2);
      double weight = xpdf1_new * xpdf2_new / w0;
      sumsq += ( weight - w0 ) * (weight - w0);
    }


    double rmsWt = sqrt( (1./99.)*sumsq );

    if ( rmsWt > 1.0){

      NNPDF3wgt_up = rmsWt;
      NNPDF3wgt_down = 2 - rmsWt;
    }

    if (rmsWt < 1.0){

      NNPDF3wgt_down = rmsWt;
      NNPDF3wgt_up = 2 - rmsWt;
    }
    
  }


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
  bool mu0_isMedium=false;
  bool mu0_isHighPt = false;
  double mu0_iso04=0;
  int count_mu=0;

  std::vector<reco::CandidatePtr> muFootprint;

  for (const pat::Muon &mu : *muons) {
      if (mu.pt() < 30 || !mu.isLooseMuon() || fabs( mu.eta() ) > 2.1) continue;


      if (count_mu==0){
        mu0_p4.SetPtEtaPhiM( mu.pt(), mu.eta(), mu.phi(), mu.mass() );
        if ( mu.isTightMuon(PV) ) mu0_isTight = true;
        // ICHEP HIP MEDIUM MUON ID https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideMuonIdRun2#Short_Term_Instructions_for_ICHE
        bool goodGlob = mu.isGlobalMuon() && 
                      mu.globalTrack()->normalizedChi2() < 3 && 
                      mu.combinedQuality().chi2LocalPosition < 12 && 
                      mu.combinedQuality().trkKink < 20; 
        bool isMedium = muon::isLooseMuon(mu) && 
                      mu.innerTrack()->validFraction() > 0.49 && 
                      muon::segmentCompatibility(mu) > (goodGlob ? 0.303 : 0.451); 
        if ( isMedium ) mu0_isMedium = true;

        bool isHighPt = mu.isHighPtMuon(PV);
        if ( isHighPt ) mu0_isHighPt = true;

        // https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId#Accessing_PF_Isolation_from_reco
        double sumChargedHadronPt = mu.pfIsolationR04().sumChargedHadronPt;
        double sumNeutralHadronPt = mu.pfIsolationR04().sumNeutralHadronEt;
        double sumPhotonPt        = mu.pfIsolationR04().sumPhotonEt;
        double sumPUPt            = mu.pfIsolationR04().sumPUPt;
        double pt                 = mu.pt();
        double iso04 = (sumChargedHadronPt+TMath::Max(0.,sumNeutralHadronPt+sumPhotonPt-0.5*sumPUPt))/pt;
        mu0_iso04 = iso04;

        for (unsigned int i = 0, n = mu.numberOfSourceCandidatePtrs(); i < n; ++i) {
          muFootprint.push_back(mu.sourceCandidatePtr(i));
        }



        if (verbose_) cout<<"Muon pT "<<mu.pt()<<" iso04 "<<iso04<<endl;
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
  Float_t el0_absiso           =0;
  Float_t el0_relIsoWithDBeta  =0;
  Float_t el0_absiso_EA        =0;
  Float_t el0_relIsoWithEA     =0;
  bool el0_isMedium     = false;
  bool el0_isTight      = false;
  int count_el=0;

  std::vector<reco::CandidatePtr> elFootprint;



  for (const pat::Electron &el : *electrons) {
      if (el.pt() < 50 || fabs(el.eta())>2.4 ) continue;

      float eta = el.eta();
      // Implemation of loose Quality cuts (need to study this and improve)
      // https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2
      // Recomended isolation variables are stored separately and not included in the loose quality cut


      bool passLoose      = false;
      bool passMedium     = false;
      bool passTight      = false;

      float ooEmooP_; 
      if( el.ecalEnergy() == 0 ){
        if(verbose_) printf("Electron energy is zero!\n");
        ooEmooP_ = 999;
      }else if( !std::isfinite(el.ecalEnergy())){
        if(verbose_) printf("Electron energy is not finite!\n");
        ooEmooP_ = 998;
      }else{
        ooEmooP_ = fabs(1.0/el.ecalEnergy() - el.eSuperClusterOverP()/el.ecalEnergy() );
      }
      float missHits = el.gsfTrack()->hitPattern().numberOfLostTrackerHits(HitPattern::MISSING_INNER_HITS);
      

      GsfElectron::PflowIsolationVariables pfIso = el.pfIsolationVariables();
      float absiso = pfIso.sumChargedHadronPt + max(0.0 , pfIso.sumNeutralHadronEt + pfIso.sumPhotonEt - 0.5 * pfIso.sumPUPt );
      float relIsoWithDBeta = absiso/el.pt();

      float effArea = 0.;
      if(abs(eta)>0.0 && abs(eta)<=1.0) effArea = 0.1752;
      if(abs(eta)>1.0 && abs(eta)<=1.479) effArea = 0.1862;
      if(abs(eta)>1.479 && abs(eta)<=2.0) effArea = 0.1411;
      if(abs(eta)>2.0 && abs(eta)<=2.2) effArea = 0.1534;
      if(abs(eta)>2.2 && abs(eta)<=2.3) effArea = 0.1903;
      if(abs(eta)>2.3 && abs(eta)<=2.4) effArea = 0.2243;
      if(abs(eta)>2.4 && abs(eta)<=2.5) effArea = 0.2687;

      float absiso_EA = pfIso.sumChargedHadronPt + max(0.0 , pfIso.sumNeutralHadronEt + pfIso.sumPhotonEt - rho * effArea );
      float relIsoWithEA = absiso_EA/el.pt();


      if (fabs(el.eta())<=1.479 ){
        if( el.full5x5_sigmaIetaIeta()                <      0.011      &&
            fabs(el.deltaEtaSuperClusterTrackAtVtx()) <      0.00477    &&
            fabs(el.deltaPhiSuperClusterTrackAtVtx()) <      0.222      &&
            el.hadronicOverEm()                       <      0.298      &&
            ooEmooP_                                  <      0.241      &&
            missHits                                  <=     1           ){ 
          passLoose =true ;
        }
        if( el.full5x5_sigmaIetaIeta()                <      0.00998     &&
            fabs(el.deltaEtaSuperClusterTrackAtVtx()) <      0.00311     &&
            fabs(el.deltaPhiSuperClusterTrackAtVtx()) <      0.103       &&
            el.hadronicOverEm()                       <      0.253       &&
            ooEmooP_                                  <      0.134       &&
            missHits                                  <=     1           ){ 
          passMedium =true ;
        }
        if( el.full5x5_sigmaIetaIeta()                <      0.00998     &&
            fabs(el.deltaEtaSuperClusterTrackAtVtx()) <      0.00308     &&
            fabs(el.deltaPhiSuperClusterTrackAtVtx()) <      0.0816      &&
            el.hadronicOverEm()                       <      0.0414      &&
            ooEmooP_                                  <      0.0129      &&
            missHits                                  <=     1           ){ 
          passTight =true ;
        }
      }
      else { 
        if( el.full5x5_sigmaIetaIeta()                <      0.0314     &&
            fabs(el.deltaEtaSuperClusterTrackAtVtx()) <      0.00868    &&
            fabs(el.deltaPhiSuperClusterTrackAtVtx()) <      0.213      &&
            el.hadronicOverEm()                       <      0.101      &&
            ooEmooP_                                  <      0.14       &&
            missHits                                  <=     1             ){ 
          passLoose =true ;
        }
        if( el.full5x5_sigmaIetaIeta()                <      0.0298      &&
            fabs(el.deltaEtaSuperClusterTrackAtVtx()) <      0.00609     &&
            fabs(el.deltaPhiSuperClusterTrackAtVtx()) <      0.045       &&
            el.hadronicOverEm()                       <      0.0878      &&
            ooEmooP_                                  <      0.13        &&
            missHits                                  <=     1             ){ 
          passMedium =true ;
        }
        if( el.full5x5_sigmaIetaIeta()                <      0.0292      &&
            fabs(el.deltaEtaSuperClusterTrackAtVtx()) <      0.00605     &&
            fabs(el.deltaPhiSuperClusterTrackAtVtx()) <      0.0394      &&
            el.hadronicOverEm()                       <      0.0641      &&
            ooEmooP_                                  <      0.0129      &&
            missHits                                  <=     1             ){ 
          passTight =true ;
        }
      }



      if (!passLoose) continue;

      if (count_el==0){
        el0_p4.SetPtEtaPhiM( el.pt(), el.eta(), el.phi(), el.mass() );

        el0_absiso           = absiso;
        el0_relIsoWithDBeta  = relIsoWithDBeta;
        el0_absiso_EA        = absiso_EA;
        el0_relIsoWithEA     = relIsoWithEA;
        el0_isMedium         = passMedium;
        el0_isTight          = passTight ;

        for (unsigned int i = 0, n = el.numberOfSourceCandidatePtrs(); i < n; ++i) {
          elFootprint.push_back(el.sourceCandidatePtr(i));
        }


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

  if (verbose_){
    cout<<"count_mu  "<<count_mu<<endl;
    cout<<"count_el  "<<count_el<<endl;
    cout<<"count_lep "<<count_lep<<endl;
  }

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

  if (verbose_) cout<<"debug: about to grab met"<<endl;
  edm::Handle<pat::METCollection> mets;
  iEvent.getByToken(metToken_, mets);
  const pat::MET &met = mets->front();
  if (verbose_){
    cout<<"MET pt "<<met.pt()<<endl;
    cout<<"MET phi "<<met.phi()<<endl;
    cout<<"MET sumEt "<<met.sumEt()<<endl;
    if (!iEvent.isRealData() )  cout<<"genMET "<< met.genMET()->pt()<<endl;
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
  TLorentzVector AK4_dRMinLep_p4;
  TLorentzVector AK4_btagged_dRMinLep_p4;
  double AK4_dRMinLep_bdisc = -99;
  double AK4_btagged_dRMinLep_bdisc = -99;
  double AK4_dRMinLep  = 99;
  double AK4_btagged_dRMinLep = 99;

  bool ak4_btag_loose  = false;
  bool ak4_btag_medium = false;
  bool ak4_btag_tight  = false;

  double HT_AK4_pt30           = 0 ;
  double HT_AK4_pt30_corrUp    = 0 ;
  double HT_AK4_pt30_corrDn    = 0 ;
  double HT_AK4_pt30_smearNom  = 0 ;
  double HT_AK4_pt30_smearUp   = 0 ;
  double HT_AK4_pt30_smearDn   = 0 ;

  edm::Handle<pat::JetCollection> AK4MINI;
  iEvent.getByToken(ak4jetToken_, AK4MINI);

  edm::Handle<reco::GenJetCollection> AK4GENJET;  
  iEvent.getByToken(ak4genjetToken_, AK4GENJET);

  if (verbose_) cout<<"debug: about to grab ak4 jets"<<endl;

  for (const pat::Jet &ijet : *AK4MINI) {  
    
    if (ijet.pt()<15 || fabs(ijet.eta())>3.0) continue; 



    //------------------------------------
    // Remove leptons from AK4 jets
    //------------------------------------    
    auto uncorrJetObj = ijet.correctedJet(0);
    reco::Candidate::LorentzVector uncorrJet = ijet.correctedP4(0);
    // now loop on pf candidates
    //// Jet constituent indices for lepton matching
    std::vector<int> constituentIndices;
    auto jetConstituents = uncorrJetObj.daughterPtrVector();
    if ( verbose_ ) cout << "debug: uncorr jet before lepton cleaning pt,eta,phi,m = " << uncorrJet.pt() << ", " << uncorrJet.eta() << ", " << uncorrJet.phi() << ", " << uncorrJet.mass() << endl;
    for ( auto & constituent : jetConstituents ) {

      // If this constituent is part of a muon, remove the constituent's four vector
      if ( std::find(muFootprint.begin(), muFootprint.end(), constituent ) != muFootprint.end() ) {
	uncorrJet -= constituent->p4();
	if ( verbose_ ) cout << "debug: REMOVED part of muon" << endl;
      }
      // If this constituent is part of an electron, remove the constituent's four vector
      if ( std::find(elFootprint.begin(), elFootprint.end(), constituent ) != elFootprint.end() ) {
	uncorrJet -= constituent->p4();
	if ( verbose_ ) cout << "debug: REMOVED part of electron" << endl;
      }

    }
    if ( verbose_ ) cout << "debug: uncorr jet after lepton cleaning pt,eta,phi,m = " << uncorrJet.pt() << ", " << uncorrJet.eta() << ", " << uncorrJet.phi() << ", " << uncorrJet.mass() << endl;

    



    //------------------------------------
    // Noise jet ID
    //------------------------------------    
    double NHF       = ijet.neutralHadronEnergyFraction();
    double NEMF      = ijet.neutralEmEnergyFraction();
    double CHF       = ijet.chargedHadronEnergyFraction();
    // double MUF       = ijet.muonEnergyFraction();
    double CEMF      = ijet.chargedEmEnergyFraction();
    double NumConst  = ijet.chargedMultiplicity()+ijet.neutralMultiplicity();
    double NM        = ijet.neutralMultiplicity();
    double CM        = ijet.chargedMultiplicity(); 
    double eta       = ijet.eta(); 

    bool goodJet_looseJetID =  
         ( fabs(eta) <= 2.4 && NHF < 0.99 && NEMF < 0.99 && NumConst >1 && CHF > 0.0  && CM > 0 && CEMF < 0.99   ) 
      || ( fabs(eta) <= 2.7 && fabs(eta) > 2.4 && NHF < 0.99 && NEMF < 0.99 && NumConst >1 ) 
      || ( fabs(eta) <= 3.0 && fabs(eta) > 2.7 && NEMF < 0.9 && NM > 2 ) 
      || ( fabs(eta)  > 3.0 && NEMF < 0.9 && NM > 10 );
    if (verbose_) cout<<"  goodJet = "<<goodJet_looseJetID<<endl;

    if (!goodJet_looseJetID) {
      if(verbose_) cout<<"  bad AK4 jet. skip.  ( pt "<<ijet.pt()<<" eta "<<ijet.eta()<<" NumConst "<<NumConst<<" )"<<endl;
      continue;
    }

    //------------------------------------
    // AK4CHS JEC correction 
    //------------------------------------
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

    if (verbose_) cout<<"  corrDn "<<corrDn<<" corrUp "<< corrUp<<endl;

    //------------------------------------
    // GenJet  matched
    //------------------------------------ 
    double genpt = 0;
    if (!iEvent.isRealData()){
      const reco::GenJet* genJet = ijet.genJet();
      if (genJet) {
        genpt = genJet->pt();
        if (verbose_) cout<<"  ak4 genJet pt "<<genJet->pt()<<" mass "<<genJet->mass()<<endl;
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
      if (verbose_) std::cout << "  JER Scale factors (Nominal / Up / Down) : " << jer_sf << " / " << jer_sf_up << " / " << jer_sf_dn << std::endl;
      double recopt    = corrJet.pt();
      // double genpt     = GenJetMatched.Perp();
      double deltapt   = (recopt-genpt)*(jer_sf-1.0);
      double deltaptUp = (recopt-genpt)*(jer_sf_up-1.0);
      double deltaptDn = (recopt-genpt)*(jer_sf_dn-1.0);
      ptsmear   = std::max((double)0.0, (recopt+deltapt)/recopt     );
      ptsmearUp = std::max((double)0.0, (recopt+deltaptUp)/recopt   );
      ptsmearDn = std::max((double)0.0, (recopt+deltaptDn)/recopt   );
    }

    if (verbose_) cout<<"  ptsmear "<<ptsmear<<" ptsmearUp "<< ptsmearDn<<" ptsmearDn "<< ptsmearUp<<endl;


    //------------------------------------
    // AK4 variables 
    //------------------------------------
    double pt           = corrJet.pt();
    double mass         = corrJet.mass();
    eta                 = corrJet.eta();
    double phi          = corrJet.phi();
    //double rapidity     = ijet.rapidity();
    //double ndau         = ijet.numberOfDaughters();
    double bdisc        = ijet.bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"); 
    //double puid         = ijet.userFloat("pileupJetId:fullDiscriminant");
 
    //------------------------------------
    // HT calculation
    //------------------------------------

    if (corrJet.pt()>30)            HT_AK4_pt30           +=   pt;
    if (corrUp * corrJet.pt()>30)   HT_AK4_pt30_corrUp    +=   corrUp * corrJet.pt();
    if (corrDn * corrJet.pt()>30)   HT_AK4_pt30_corrDn    +=   corrDn * corrJet.pt();
    if (ptsmear * corrJet.pt()>30)  HT_AK4_pt30_smearNom  +=   ptsmear * corrJet.pt();
    if (ptsmearUp* corrJet.pt()>30) HT_AK4_pt30_smearUp   +=   ptsmearUp * corrJet.pt();
    if (ptsmearDn* corrJet.pt()>30) HT_AK4_pt30_smearDn   +=   ptsmearDn * corrJet.pt();

    //------------------------------------
    // Find AK4 jet closest to lepton
    //------------------------------------ 
    double deltaRlep = deltaR(corrJet.eta(), corrJet.phi(), lep0_p4.Eta(), lep0_p4.Phi() );

    if (pt>15 && fabs(eta)<3.0 && goodJet_looseJetID){
      if (deltaRlep<AK4_dRMinLep){
        AK4_dRMinLep = deltaRlep;
        AK4_dRMinLep_p4.SetPtEtaPhiM( pt, eta, phi, mass );
        AK4_dRMinLep_bdisc = bdisc;
      }
    }



    //------------------------------------
    // Find Loose b-tagged AK4 jet closest to lepton
    //------------------------------------ 
    if (pt>15. && fabs(eta)<3.0 && goodJet_looseJetID && bdisc>0.460 ){
      if (deltaRlep<AK4_btagged_dRMinLep){
        AK4_btagged_dRMinLep = deltaRlep;
        AK4_btagged_dRMinLep_p4.SetPtEtaPhiM( pt, eta, phi, mass );
        AK4_btagged_dRMinLep_bdisc = bdisc;
      }
    }

    //------------------------------------
    // Check if there is a b-tagged AK4 jet in the lepton hemisphere
    //------------------------------------ 
    double deltaPhiLep = fabs( deltaPhi( phi,  lep0_p4.Phi() ));  
    if (pt>15. && fabs(eta)<3.0 && goodJet_looseJetID){              
      if (deltaPhiLep<  3.14/2.0)
      {
        if (bdisc>0.460 ) ak4_btag_loose  = true;
        if (bdisc>0.800 ) ak4_btag_medium = true;
        if (bdisc>0.935 ) ak4_btag_tight  = true;
      }
    }
  } //end AK4 loop

  if (verbose_) {
    cout<<"AK4 summary:"<<endl;
    cout<<"  closest ak4 jet to lepton:"<<endl;
    cout<<"    pt =  "<<AK4_dRMinLep_p4.Perp()<<endl;
    cout<<"    bdisc =  "<<AK4_dRMinLep_bdisc<<endl;
    cout<<"    dR  = "<<AK4_dRMinLep<<endl;
    cout<<"  closest loose b-tagged ak4 jet to lepton:"<<endl;
    cout<<"    pt =  "<<AK4_btagged_dRMinLep_p4.Perp()<<endl;
    cout<<"    bdisc =  "<<AK4_btagged_dRMinLep_bdisc<<endl;
    cout<<"    dR  = "<<AK4_btagged_dRMinLep<<endl;
    cout<<"  b-tagged jet in hemisphere around lepton?"<<endl;
    cout<<"    ak4_btag_loose  "<<ak4_btag_loose  <<endl; 
    cout<<"    ak4_btag_medium "<<ak4_btag_medium <<endl; 
    cout<<"    ak4_btag_tight  "<<ak4_btag_tight  <<endl; 
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

  edm::Handle<pat::JetCollection> AK8CHSsub;
  edm::Handle<pat::JetCollection> AK8PUPPI;
  edm::Handle<pat::JetCollection> AK8PUPPIsub;
  if (useToolbox_){
    iEvent.getByToken( ak8CHSSoftDropSubjetsToken_   , AK8CHSsub);
    iEvent.getByToken( puppijetToken_ , AK8PUPPI );
    iEvent.getByToken( ak8PuppiSoftDropSubjetsToken_ , AK8PUPPIsub);
  }

  int count_AK8CHS = 0;
  int count_fill_leptTree =0;

  TLorentzVector AK8jet_SemiLept_P4corr;
  TLorentzVector AK8jet0_P4corr;
  TLorentzVector AK8jet1_P4corr;
  TLorentzVector PUPPIjet0_P4;
  TLorentzVector PUPPIjet1_P4;
  TLorentzVector PUPPIjet0_P4corr;
  TLorentzVector PUPPIjet1_P4corr;

  TLorentzVector GenJetMatched0;
  TLorentzVector GenJetMatched1;

  if (verbose_) cout<<"debug: about to grab ak8 jets"<<endl;

  for (const pat::Jet &ijet : *AK8CHS) {  
    if (count_AK8CHS>1) break;
    if (count_AK8CHS==0 && ijet.pt()<250) break;

    if (verbose_) cout<<"\nJet "<<count_AK8CHS<<" with pT "<<ijet.pt()<<" sdMass "<<ijet.userFloat("ak8PFJetsCHSSoftDropMass")<<endl;

    //------------------------------------
    // Noise jet ID
    //------------------------------------    
    double NHF       = ijet.neutralHadronEnergyFraction();
    double NEMF      = ijet.neutralEmEnergyFraction();
    double CHF       = ijet.chargedHadronEnergyFraction();
    // double MUF       = ijet.muonEnergyFraction();
    double CEMF      = ijet.chargedEmEnergyFraction();
    double NumConst  = ijet.chargedMultiplicity()+ijet.neutralMultiplicity();
    double NM        = ijet.neutralMultiplicity();
    double CM        = ijet.chargedMultiplicity(); 
    double eta       = ijet.eta();

    bool goodJet_looseJetID =  
         ( fabs(eta) <= 2.4 && NHF < 0.99 && NEMF < 0.99 && NumConst >1 && CHF > 0.0  && CM > 0 && CEMF < 0.99   ) 
      || ( fabs(eta) <= 2.7 && fabs(eta) > 2.4 && NHF < 0.99 && NEMF < 0.99 && NumConst >1 ) 
      || ( fabs(eta) <= 3.0 && fabs(eta) > 2.7 && NEMF < 0.9 && NM > 2 ) 
      || ( fabs(eta)  > 3.0 && NEMF < 0.9 && NM > 10 );
    if (verbose_) cout<<"  goodJet = "<<goodJet_looseJetID<<endl;

    if (!goodJet_looseJetID) {
      if(verbose_) cout<<"  bad AK8 jet. skip.  ( pt "<<ijet.pt()<<" eta "<<ijet.eta()<<" NumConst "<<NumConst<<" )"<<endl;
      continue;
    }

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
    if (verbose_) cout<<" uncorrected AK8 jet pt "<<uncorrJet.pt()<<" corrected jet pt "<<corrJet.pt()<<endl;
    
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
    if (!iEvent.isRealData()){
      const reco::GenJet* genJet = ijet.genJet();
      if (genJet) {
        GenJetMatched.SetPtEtaPhiM( genJet->pt(), genJet->eta(), genJet->phi(), genJet->mass() );
        if (verbose_) cout<<"  ak8 genJet pt "<<genJet->pt()<<" mass "<<genJet->mass()<<endl;
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
      if (verbose_) std::cout << " JER Scale factors (Nominal / Up / Down) : " << jer_sf << " / " << jer_sf_up << " / " << jer_sf_dn << std::endl;
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
    // double pt           = corrJet.pt();
    //double mass         = corrJet.mass();
    // double eta          = corrJet.eta();
    // double phi          = corrJet.phi();
    //double rapidity     = ijet.rapidity();
    //double ndau         = ijet.numberOfDaughters();

    double tau1         = 99;
    double tau2         = 99;
    double tau3         = 99;
    double tau4         = 99;
    double prunedMass   = ijet.userFloat("ak8PFJetsCHSPrunedMass");
    double softDropMass = ijet.userFloat("ak8PFJetsCHSSoftDropMass");
    double trimmedMass  = -1;

    if (useToolbox_){
      tau1         = ijet.userFloat("NjettinessAK8CHS:tau1");
      tau2         = ijet.userFloat("NjettinessAK8CHS:tau2");
      tau3         = ijet.userFloat("NjettinessAK8CHS:tau3");
      tau4         = ijet.userFloat("NjettinessAK8CHS:tau4");
      trimmedMass  = ijet.userFloat("ak8PFJetsCHSTrimmedMass"); 
    }
    else{
      tau1         = ijet.userFloat("NjettinessAK8:tau1");
      tau2         = ijet.userFloat("NjettinessAK8:tau2");
      tau3         = ijet.userFloat("NjettinessAK8:tau3");
    }
    double tau21        = 99;
    double tau32        = 99;

    double puppi_p              = -1;     
    double puppi_pt             = -1;     
    double puppi_mass           = -1;     
    double puppi_eta            = -1;     
    double puppi_phi            = -1;     
    double puppi_tau1           = -1;     
    double puppi_tau2           = -1;     
    double puppi_tau3           = -1;     
    double puppi_tau4           = -1;     
    // double puppi_prunedMass     = -1;     
    // double puppi_trimmedMass    = -1;     
    // double puppi_softDropMass   = -1;     

    double puppi_CHF    = -1;
    double puppi_NHF    = -1;
    double puppi_CM     = -1;
    double puppi_NM     = -1;
    double puppi_NEF    = -1;
    double puppi_CEF    = -1;
    double puppi_MF     = -1;
    double puppi_Mult   = -1;
 
    if (!useToolbox_){
      puppi_pt           = ijet.userFloat("ak8PFJetsPuppiValueMap:pt");
      puppi_mass         = ijet.userFloat("ak8PFJetsPuppiValueMap:mass");
      puppi_eta          = ijet.userFloat("ak8PFJetsPuppiValueMap:eta");
      puppi_phi          = ijet.userFloat("ak8PFJetsPuppiValueMap:phi");
      puppi_tau1         = ijet.userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau1");
      puppi_tau2         = ijet.userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau2");
      puppi_tau3         = ijet.userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau3");
    }
    if (useToolbox_){
      for (const pat::Jet &ipup : *AK8PUPPI) {  
        if (ipup.pt()<180) break;    
        double deltaRpup = deltaR(ijet.eta(), ijet.phi(), ipup.eta(), ipup.phi() );
        if (deltaRpup<0.8){
          puppi_p            = ipup.p();
          puppi_pt           = ipup.pt();
          puppi_mass         = ipup.mass();
          puppi_eta          = ipup.eta();
          puppi_phi          = ipup.phi();
          // puppi_prunedMass   = ipup.userFloat("ak8PFJetsPuppiPrunedMass");
          // puppi_trimmedMass  = ipup.userFloat("ak8PFJetsPuppiTrimmedMass");
          // puppi_softDropMass = ipup.userFloat("ak8PFJetsPuppiSoftDropMass");
          puppi_tau1         = ipup.userFloat("NjettinessAK8Puppi:tau1");
          puppi_tau2         = ipup.userFloat("NjettinessAK8Puppi:tau2");
          puppi_tau3         = ipup.userFloat("NjettinessAK8Puppi:tau3");
          puppi_tau4         = ipup.userFloat("NjettinessAK8Puppi:tau4");

          puppi_CHF          = ipup.chargedHadronEnergy() / ipup.correctedP4(0).E()  ;  
          puppi_NHF          = ipup.neutralHadronEnergy() / ipup.correctedP4(0).E()  ;  
          puppi_CM           = ipup.chargedMultiplicity()  ;                  
          puppi_NM           = ipup.neutralMultiplicity()  ;                  
          puppi_NEF          = ipup.neutralEmEnergy() / ipup.correctedP4(0).E()  ;      
          puppi_CEF          = ipup.chargedEmEnergy() / ipup.correctedP4(0).E()  ;      
          puppi_MF           = ipup.muonEnergy() / ipup.correctedP4(0).E()  ;           
          puppi_Mult         = ipup.numberOfDaughters() ;   

        }
      }
    }
    double puppi_tau21        = 99;
    double puppi_tau32        = 99;


    if (tau1!=0) tau21 = tau2/tau1;
    if (tau2!=0) tau32 = tau3/tau2;

    if (puppi_tau1!=0) puppi_tau21 = puppi_tau2/puppi_tau1;
    if (puppi_tau2!=0) puppi_tau32 = puppi_tau3/puppi_tau2;

    TLorentzVector jet_p4;
    jet_p4.SetPtEtaPhiM( corrJet.pt(), corrJet.eta(), corrJet.phi(), corrJet.mass() );
  

    // //------------------------------------
    // // AK8PUPPI JEC L23 correction
    // //------------------------------------

    // TLorentzVector jet_p4;
    // pupppijet_p4.SetPtEtaPhiM( puppi_pt, puppi_eta, puppi_phi, puppi_mass);
  

    // JetCorrectorAK8chs->setJetEta( puppi_eta );
    // JetCorrectorAK8chs->setJetPt ( puppi_pt );
    // JetCorrectorAK8chs->setJetE  ( puppi_e );
    // JetCorrectorAK8chs->setJetA  ( ijet.jetArea() );
    // JetCorrectorAK8chs->setRho   ( rho );
    // JetCorrectorAK8chs->setNPV   ( nvtx );
    // // getSubCorrections member function returns the vector of the subcorrections UP to the given level. For example in the example above, factors[0] is the L1 correction and factors[3] is the L1+L2+L3+Residual correction. 
    // vector<float> factors = JetCorrectorAK8chs->getSubCorrections();
    // float corr_factor_L1      = 1.0;
    // float corr_factor_L12     = 1.0;
    // float corr_factor_L123    = 1.0;
    // float corr_factor_L123res = 1.0;
    // if (factors.size() > 0) corr_factor_L1       = factors[0];
    // if (factors.size() > 1) corr_factor_L12      = factors[1];
    // if (factors.size() > 2) corr_factor_L123     = factors[2];
    // if (factors.size() > 3) corr_factor_L123res  = factors[3];
    // double corr_factor_L2 = corr_factor_L12/corr_factor_L1;
    // double corr_factor_L3 = corr_factor_L123/corr_factor_L12;
    // double corr_factor_res = corr_factor_L123res/corr_factor_L123;
    // //double corr_factor_L23 = corr_factor_L2*corr_factor_L3;
    // double corr_factor_L23res = corr_factor_L2*corr_factor_L3*corr_factor_res;


    if(count_AK8CHS==0) PUPPIjet0_P4corr.SetPtEtaPhiM( puppi_pt, puppi_eta, puppi_phi, puppi_mass );
    if(count_AK8CHS==1) PUPPIjet1_P4corr.SetPtEtaPhiM( puppi_pt, puppi_eta, puppi_phi, puppi_mass );



    //------------------------------------
    // SoftDrop subjets
    //------------------------------------
    TLorentzVector sub0_P4_uncorr           ;
    TLorentzVector sub0_P4_L23res           ;
    TLorentzVector sub0_P4_L23resCorrUp     ;
    TLorentzVector sub0_P4_L23resCorrDn     ;
    TLorentzVector sub0_P4_L23resPtSmear    ;
    TLorentzVector sub0_P4_L23resPtSmearUp  ;
    TLorentzVector sub0_P4_L23resPtSmearDn  ;
    TLorentzVector sub0_P4_L123res          ;
    TLorentzVector sub0_P4_L123resCorrUp    ;
    TLorentzVector sub0_P4_L123resCorrDn    ;

    TLorentzVector sub1_P4_uncorr           ;
    TLorentzVector sub1_P4_L23res           ;
    TLorentzVector sub1_P4_L23resCorrUp     ;
    TLorentzVector sub1_P4_L23resCorrDn     ;
    TLorentzVector sub1_P4_L23resPtSmear    ;
    TLorentzVector sub1_P4_L23resPtSmearUp  ;
    TLorentzVector sub1_P4_L23resPtSmearDn  ;
    TLorentzVector sub1_P4_L123res          ;
    TLorentzVector sub1_P4_L123resCorrUp    ;
    TLorentzVector sub1_P4_L123resCorrDn    ;

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

        reco::Candidate::LorentzVector corrSubjetL123resCorrDn  = subjet_corrDn_L123  * uncorrSubjet;
        reco::Candidate::LorentzVector corrSubjetL123resCorrUp  = subjet_corrUp_L123  * uncorrSubjet;
        reco::Candidate::LorentzVector corrSubjetL23resCorrDn   = subjet_corrDn_L23   * uncorrSubjet;
        reco::Candidate::LorentzVector corrSubjetL23resCorrUp   = subjet_corrUp_L23   * uncorrSubjet;
     

        //------------------------------------
        // subjet values for Tree
        //------------------------------------
        if (count_SD==0){
          sub0_P4_uncorr            .SetPtEtaPhiM( subjetPt, subjetEta, subjetPhi, subjetMass);
          sub0_P4_L123res           .SetPtEtaPhiM( corrSubjetL123res.pt()   , corrSubjetL123res.eta()   , corrSubjetL123res.phi()   , corrSubjetL123res.mass()    );
          sub0_P4_L23res            .SetPtEtaPhiM( corrSubjetL23res.pt()    , corrSubjetL23res.eta()    , corrSubjetL23res.phi()    , corrSubjetL23res.mass()     );
          sub0_P4_L123resCorrUp    .SetPtEtaPhiM( corrSubjetL123resCorrUp.pt() , corrSubjetL123resCorrUp.eta() , corrSubjetL123resCorrUp.phi() , corrSubjetL123resCorrUp.mass()  );
          sub0_P4_L23resCorrUp     .SetPtEtaPhiM( corrSubjetL23resCorrUp.pt()  , corrSubjetL23resCorrUp.eta()  , corrSubjetL23resCorrUp.phi()  , corrSubjetL23resCorrUp.mass()   );
          sub0_P4_L123resCorrDn    .SetPtEtaPhiM( corrSubjetL123resCorrDn.pt() , corrSubjetL123resCorrDn.eta() , corrSubjetL123resCorrDn.phi() , corrSubjetL123resCorrUp.mass()  );
          sub0_P4_L23resCorrDn     .SetPtEtaPhiM( corrSubjetL23resCorrDn.pt()  , corrSubjetL23resCorrDn.eta()  , corrSubjetL23resCorrDn.phi()  , corrSubjetL23res.mass()     );
          sub0_area   = it->jetArea() ;
          sub0_flav_parton   = it->partonFlavour();
          sub0_flav_hadron   = it->hadronFlavour();
          sub0_bdisc  = subjetBdisc;
        }
        if (count_SD==1) {
          sub1_P4_uncorr          .SetPtEtaPhiM( subjetPt, subjetEta, subjetPhi, subjetMass);
          sub1_P4_L123res         .SetPtEtaPhiM( corrSubjetL123res.pt()   , corrSubjetL123res.eta()   , corrSubjetL123res.phi()   , corrSubjetL123res.mass()    );
          sub1_P4_L23res          .SetPtEtaPhiM( corrSubjetL23res.pt()    , corrSubjetL23res.eta()    , corrSubjetL23res.phi()    , corrSubjetL23res.mass()     );
          sub1_P4_L123resCorrUp  .SetPtEtaPhiM( corrSubjetL123resCorrUp.pt() , corrSubjetL123resCorrUp.eta() , corrSubjetL123resCorrUp.phi() , corrSubjetL123resCorrUp.mass()  );
          sub1_P4_L23resCorrUp   .SetPtEtaPhiM( corrSubjetL23resCorrUp.pt()  , corrSubjetL23resCorrUp.eta()  , corrSubjetL23resCorrUp.phi()  , corrSubjetL23resCorrUp.mass()   );
          sub1_P4_L123resCorrDn  .SetPtEtaPhiM( corrSubjetL123resCorrDn.pt() , corrSubjetL123resCorrDn.eta() , corrSubjetL123resCorrDn.phi() , corrSubjetL123resCorrUp.mass()  );
          sub1_P4_L23resCorrDn   .SetPtEtaPhiM( corrSubjetL23resCorrDn.pt()  , corrSubjetL23resCorrDn.eta()  , corrSubjetL23resCorrDn.phi()  , corrSubjetL23res.mass()     );
          sub1_area   = it->jetArea() ;
          sub1_flav_parton   = it->partonFlavour();
          sub1_flav_hadron   = it->hadronFlavour();
          sub1_bdisc  = subjetBdisc;
        }
        if (subjetMass > mostMassiveSDsubjetMass) mostMassiveSDsubjetMass = subjetMass;

        if (verbose_) cout<<" SD Subjet pt "<<subjetPt<<" Eta "<<subjetEta<<" deltaRsubjetJet "<<deltaRsubjetJet<<" Mass "<<subjetMass<<" Bdisc "<<subjetBdisc<<endl;
        count_SD++;
      }
    }
    if (useToolbox_){
      for (const pat::Jet &isub : *AK8CHSsub) {  
  
        double subjetPt       = isub.correctedP4(0).pt();
        double subjetEta      = isub.correctedP4(0).eta();
        double subjetPhi      = isub.correctedP4(0).phi();
        double subjetMass     = isub.correctedP4(0).mass();
        double subjetBdisc    = isub.bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"); 

        double deltaRsubjetJet = deltaR(ijet.eta(), ijet.phi(), subjetEta, subjetPhi);
        if (deltaRsubjetJet<0.8){
          if (verbose_) cout<<" matched subjet with mass "<< subjetMass<<endl;

          //------------------------------------
          // subjet JEC 
          //------------------------------------
          reco::Candidate::LorentzVector uncorrSubjet = isub.correctedP4(0);
          JetCorrectorAK4chs -> setJetEta( uncorrSubjet.eta()    );
          JetCorrectorAK4chs -> setJetPt ( uncorrSubjet.pt()     );
          JetCorrectorAK4chs -> setJetE  ( uncorrSubjet.energy() );
          JetCorrectorAK4chs -> setJetA  ( isub.jetArea()        );
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
          JetCorrectorAK4chs->setJetA  ( isub.jetArea()         );
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
          if (verbose_) cout<<"  subjet corr: L1 "<<subjet_corr_factor_L1<<" L23 "<<subjet_corr_factor_L23<<" L23res "<<subjet_corr_factor_L23res<<" L123res "<<subjet_corr_factor_L123res<<endl;
          reco::Candidate::LorentzVector corrSubjetL23res   = subjet_corr_factor_L23res * uncorrSubjet;
          
   cout<<"CHSsubjet area "<<isub.jetArea() <<endl;
          
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

          reco::Candidate::LorentzVector corrSubjetL123resCorrDn  = subjet_corrDn_L123  * uncorrSubjet;
          reco::Candidate::LorentzVector corrSubjetL123resCorrUp  = subjet_corrUp_L123  * uncorrSubjet;
          reco::Candidate::LorentzVector corrSubjetL23resCorrDn   = subjet_corrDn_L23   * uncorrSubjet;
          reco::Candidate::LorentzVector corrSubjetL23resCorrUp   = subjet_corrUp_L23   * uncorrSubjet;
         
          //------------------------------------
          // subjet JER SF
          //------------------------------------
          TLorentzVector GenSubJet;
          double ptsmear   = 1;
          double ptsmearUp = 1;
          double ptsmearDn = 1;
          if (!iEvent.isRealData()){
            const reco::GenJet* genJet = isub.genJet();
            if (genJet) {
              GenSubJet.SetPtEtaPhiM( genJet->pt(), genJet->eta(), genJet->phi(), genJet->mass() );
              if (verbose_) cout<<"  SD subjet genJet pt "<<genJet->pt()<<" mass "<<genJet->mass()<<" reco pt "<<subjetPt<<" reco mass "<<subjetMass<<endl;
            }
            double jer_sf    = jer_scaler.getScaleFactor({{JME::Binning::JetEta, corrSubjetL23res.eta()}});
            double jer_sf_up = jer_scaler.getScaleFactor({{JME::Binning::JetEta, corrSubjetL23res.eta()}}, Variation::UP);
            double jer_sf_dn = jer_scaler.getScaleFactor({{JME::Binning::JetEta, corrSubjetL23res.eta()}}, Variation::DOWN);
            if (verbose_) std::cout << " SD subjet JER Scale factors (Nominal / Up / Down) : " << jer_sf << " / " << jer_sf_up << " / " << jer_sf_dn << std::endl;
            double recopt    = corrSubjetL23res.pt();
            double genpt     = GenJetMatched.Perp();
            double deltapt   = (recopt-genpt)*(jer_sf-1.0);
            double deltaptUp = (recopt-genpt)*(jer_sf_up-1.0);
            double deltaptDn = (recopt-genpt)*(jer_sf_dn-1.0);
            ptsmear   = std::max((double)0.0, (recopt+deltapt)/recopt     );
            ptsmearUp = std::max((double)0.0, (recopt+deltaptUp)/recopt   );
            ptsmearDn = std::max((double)0.0, (recopt+deltaptDn)/recopt   );
            if (verbose_) std::cout<<" SD subjet ptsmear "<<ptsmear<<" ptsmearUp "<<ptsmearUp<<" ptsmearDn "<<ptsmearDn<<endl;
          }
          reco::Candidate::LorentzVector corrSubjetL23resPtSmear   = ptsmear * corrSubjetL23res ;
          reco::Candidate::LorentzVector corrSubjetL23resPtSmearUp = ptsmearUp * corrSubjetL23res ;
          reco::Candidate::LorentzVector corrSubjetL23resPtSmearDn = ptsmearDn * corrSubjetL23res ;

          //------------------------------------
          // subjet values for Tree
          //------------------------------------
          if (count_SD==0){
            sub0_P4_uncorr            .SetPtEtaPhiM( subjetPt, subjetEta, subjetPhi, subjetMass);
            sub0_P4_L23res            .SetPtEtaPhiM( corrSubjetL23res          .pt() , corrSubjetL23res          .eta()  , corrSubjetL23res          .phi()  , corrSubjetL23res          .mass()  );
            sub0_P4_L23resCorrUp      .SetPtEtaPhiM( corrSubjetL23resCorrUp    .pt() , corrSubjetL23resCorrUp    .eta()  , corrSubjetL23resCorrUp    .phi()  , corrSubjetL23resCorrUp    .mass()  );
            sub0_P4_L23resCorrDn      .SetPtEtaPhiM( corrSubjetL23resCorrDn    .pt() , corrSubjetL23resCorrDn    .eta()  , corrSubjetL23resCorrDn    .phi()  , corrSubjetL23resCorrDn    .mass()  );
            sub0_P4_L23resPtSmear     .SetPtEtaPhiM( corrSubjetL23resPtSmear   .pt() , corrSubjetL23resPtSmear   .eta()  , corrSubjetL23resPtSmear   .phi()  , corrSubjetL23resPtSmear   .mass()  );
            sub0_P4_L23resPtSmearUp   .SetPtEtaPhiM( corrSubjetL23resPtSmearUp .pt() , corrSubjetL23resPtSmearUp .eta()  , corrSubjetL23resPtSmearUp .phi()  , corrSubjetL23resPtSmearUp .mass()  );
            sub0_P4_L23resPtSmearDn   .SetPtEtaPhiM( corrSubjetL23resPtSmearDn .pt() , corrSubjetL23resPtSmearDn .eta()  , corrSubjetL23resPtSmearDn .phi()  , corrSubjetL23resPtSmearDn .mass()  );
            sub0_P4_L123res           .SetPtEtaPhiM( corrSubjetL123res         .pt() , corrSubjetL123res         .eta()  , corrSubjetL123res         .phi()  , corrSubjetL123res         .mass()  );
            sub0_P4_L123resCorrUp     .SetPtEtaPhiM( corrSubjetL123resCorrUp   .pt() , corrSubjetL123resCorrUp   .eta()  , corrSubjetL123resCorrUp   .phi()  , corrSubjetL123resCorrUp   .mass()  );
            sub0_P4_L123resCorrDn     .SetPtEtaPhiM( corrSubjetL123resCorrDn   .pt() , corrSubjetL123resCorrDn   .eta()  , corrSubjetL123resCorrDn   .phi()  , corrSubjetL123resCorrDn   .mass()  );
 
            sub0_area          = isub.jetArea() ;
            sub0_flav_parton   = isub.partonFlavour();
            sub0_flav_hadron   = isub.hadronFlavour();
            sub0_bdisc         = subjetBdisc;
            // available from toolbox only (80X)
            sub0_tau1          = isub.userFloat("NsubjettinessAK8PFCHSSoftDropSubjets:tau1");
            sub0_tau2          = isub.userFloat("NsubjettinessAK8PFCHSSoftDropSubjets:tau2");
            sub0_tau3          = isub.userFloat("NsubjettinessAK8PFCHSSoftDropSubjets:tau3");
          }
          if (count_SD==1) {
            sub1_P4_uncorr            .SetPtEtaPhiM( subjetPt, subjetEta, subjetPhi, subjetMass);
            sub1_P4_L23res            .SetPtEtaPhiM( corrSubjetL23res          .pt() , corrSubjetL23res          .eta()  , corrSubjetL23res          .phi()  , corrSubjetL23res          .mass()  );
            sub1_P4_L23resCorrUp      .SetPtEtaPhiM( corrSubjetL23resCorrUp    .pt() , corrSubjetL23resCorrUp    .eta()  , corrSubjetL23resCorrUp    .phi()  , corrSubjetL23resCorrUp    .mass()  );
            sub1_P4_L23resCorrDn      .SetPtEtaPhiM( corrSubjetL23resCorrDn    .pt() , corrSubjetL23resCorrDn    .eta()  , corrSubjetL23resCorrDn    .phi()  , corrSubjetL23resCorrDn    .mass()  );
            sub1_P4_L23resPtSmear     .SetPtEtaPhiM( corrSubjetL23resPtSmear   .pt() , corrSubjetL23resPtSmear   .eta()  , corrSubjetL23resPtSmear   .phi()  , corrSubjetL23resPtSmear   .mass()  );
            sub1_P4_L23resPtSmearUp   .SetPtEtaPhiM( corrSubjetL23resPtSmearUp .pt() , corrSubjetL23resPtSmearUp .eta()  , corrSubjetL23resPtSmearUp .phi()  , corrSubjetL23resPtSmearUp .mass()  );
            sub1_P4_L23resPtSmearDn   .SetPtEtaPhiM( corrSubjetL23resPtSmearDn .pt() , corrSubjetL23resPtSmearDn .eta()  , corrSubjetL23resPtSmearDn .phi()  , corrSubjetL23resPtSmearDn .mass()  );
            sub1_P4_L123res           .SetPtEtaPhiM( corrSubjetL123res         .pt() , corrSubjetL123res         .eta()  , corrSubjetL123res         .phi()  , corrSubjetL123res         .mass()  );
            sub1_P4_L123resCorrUp     .SetPtEtaPhiM( corrSubjetL123resCorrUp   .pt() , corrSubjetL123resCorrUp   .eta()  , corrSubjetL123resCorrUp   .phi()  , corrSubjetL123resCorrUp   .mass()  );
            sub1_P4_L123resCorrDn     .SetPtEtaPhiM( corrSubjetL123resCorrDn   .pt() , corrSubjetL123resCorrDn   .eta()  , corrSubjetL123resCorrDn   .phi()  , corrSubjetL123resCorrDn   .mass()  );
 
            sub1_area          = isub.jetArea() ;
            sub1_flav_parton   = isub.partonFlavour();
            sub1_flav_hadron   = isub.hadronFlavour();
            sub1_bdisc         = subjetBdisc;
            // available from toolbox only (80X)
            sub1_tau1          = isub.userFloat("NsubjettinessAK8PFCHSSoftDropSubjets:tau1");
            sub1_tau2          = isub.userFloat("NsubjettinessAK8PFCHSSoftDropSubjets:tau2");
            sub1_tau3          = isub.userFloat("NsubjettinessAK8PFCHSSoftDropSubjets:tau3");
          }
          if (subjetMass > mostMassiveSDsubjetMass) mostMassiveSDsubjetMass = subjetMass;

          if (verbose_) cout<<"  SD Subjet pt "<<subjetPt<<" Eta "<<subjetEta<<" deltaRsubjetJet "<<deltaRsubjetJet<<" Mass "<<subjetMass<<" corrMass "<<corrSubjetL23res.mass() <<" Bdisc "<<subjetBdisc<<endl;
          if (verbose_) cout<<"    sub0_tau1 "<<sub0_tau1<<" sub0_tau2 "<<sub0_tau2<<" sub0_tau3 "<<sub0_tau3<<endl;
          count_SD++;

        }
      }
    }

    TLorentzVector sumSDsubjets_P4_uncorr           ;
    TLorentzVector sumSDsubjets_P4_L23res           ;
    TLorentzVector sumSDsubjets_P4_L23resCorrUp     ;
    TLorentzVector sumSDsubjets_P4_L23resCorrDn     ;
    TLorentzVector sumSDsubjets_P4_L23resPtSmear    ;
    TLorentzVector sumSDsubjets_P4_L23resPtSmearUp  ;
    TLorentzVector sumSDsubjets_P4_L23resPtSmearDn  ;
    TLorentzVector sumSDsubjets_P4_L123res          ;
    TLorentzVector sumSDsubjets_P4_L123resCorrDn    ;
    TLorentzVector sumSDsubjets_P4_L123resCorrUp    ;

    if (count_SD>1){ 
      sumSDsubjets_P4_uncorr             = sub0_P4_uncorr              + sub1_P4_uncorr            ; 
      sumSDsubjets_P4_L23res             = sub0_P4_L23res              + sub1_P4_L23res            ; 
      sumSDsubjets_P4_L23resCorrUp       = sub0_P4_L23resCorrUp        + sub1_P4_L23resCorrUp      ; 
      sumSDsubjets_P4_L23resCorrDn       = sub0_P4_L23resCorrDn        + sub1_P4_L23resCorrDn      ; 
      sumSDsubjets_P4_L23resPtSmear      = sub0_P4_L23resPtSmear       + sub1_P4_L23resPtSmear     ;
      sumSDsubjets_P4_L23resPtSmearUp    = sub0_P4_L23resPtSmearUp     + sub1_P4_L23resPtSmearUp   ;
      sumSDsubjets_P4_L23resPtSmearDn    = sub0_P4_L23resPtSmearDn     + sub1_P4_L23resPtSmearDn   ;
      sumSDsubjets_P4_L123res            = sub0_P4_L123res             + sub1_P4_L123res           ; 
      sumSDsubjets_P4_L123resCorrUp      = sub0_P4_L123resCorrUp       + sub1_P4_L123resCorrUp     ; 
      sumSDsubjets_P4_L123resCorrDn      = sub0_P4_L123resCorrDn       + sub1_P4_L123resCorrDn     ; 
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
    TLorentzVector pup0_P4_uncorr           ;
    TLorentzVector pup0_P4_L23res           ;
    TLorentzVector pup0_P4_L23resCorrUp     ;
    TLorentzVector pup0_P4_L23resCorrDn     ;
    TLorentzVector pup0_P4_L23resPtSmear    ;
    TLorentzVector pup0_P4_L23resPtSmearUp  ;
    TLorentzVector pup0_P4_L23resPtSmearDn  ;

    TLorentzVector pup1_P4_uncorr           ;
    TLorentzVector pup1_P4_L23res           ;
    TLorentzVector pup1_P4_L23resCorrUp     ;
    TLorentzVector pup1_P4_L23resCorrDn     ;
    TLorentzVector pup1_P4_L23resPtSmear    ;
    TLorentzVector pup1_P4_L23resPtSmearUp  ;
    TLorentzVector pup1_P4_L23resPtSmearDn  ;


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
    int count_pup=0;

    if (!useToolbox_){
      auto const & sdSubjetsPuppi = ijet.subjets("SoftDropPuppi");
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

        reco::Candidate::LorentzVector corrSubjetL23resCorrDn   = subjet_corrDn_L23   * uncorrSubjet;
        reco::Candidate::LorentzVector corrSubjetL23resCorrUp   = subjet_corrUp_L23   * uncorrSubjet;
     
        //------------------------------------
        // subjet values for Tree
        //------------------------------------

        if (count_pup==0){
          pup0_P4_uncorr           .SetPtEtaPhiM( subjetPt, subjetEta, subjetPhi, subjetMass);
          pup0_P4_L23res           .SetPtEtaPhiM( corrSubjetL23res.pt()    , corrSubjetL23res.eta()    , corrSubjetL23res.phi()    , corrSubjetL23res.mass()     );
          pup0_P4_L23resCorrUp    .SetPtEtaPhiM( corrSubjetL23resCorrUp.pt()  , corrSubjetL23resCorrUp.eta()  , corrSubjetL23resCorrUp.phi()  , corrSubjetL23resCorrUp.mass()   );
          pup0_P4_L23resCorrDn    .SetPtEtaPhiM( corrSubjetL23resCorrDn.pt()  , corrSubjetL23resCorrDn.eta()  , corrSubjetL23resCorrDn.phi()  , corrSubjetL23res.mass()     );
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
          pup1_P4_L23resCorrUp    .SetPtEtaPhiM( corrSubjetL23resCorrUp.pt()  , corrSubjetL23resCorrUp.eta()  , corrSubjetL23resCorrUp.phi()  , corrSubjetL23resCorrUp.mass()   );
          pup1_P4_L23resCorrDn    .SetPtEtaPhiM( corrSubjetL23resCorrDn.pt()  , corrSubjetL23resCorrDn.eta()  , corrSubjetL23resCorrDn.phi()  , corrSubjetL23res.mass()     );
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
    if (useToolbox_){
      for (const pat::Jet &isub : *AK8PUPPIsub) {  
  
        double subjetPt        = isub.correctedP4(0).pt();
        double subjetEta       = isub.correctedP4(0).eta();
        double subjetPhi       = isub.correctedP4(0).phi();
        double subjetMass      = isub.correctedP4(0).mass();
        double subjetBdisc     = isub.bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"); 
        double deltaRsubjetJet = deltaR(ijet.eta(), ijet.phi(), subjetEta, subjetPhi);

        if (deltaRsubjetJet<0.8){
          if (verbose_) cout<<" matched puppi subjet with mass "<< subjetMass<<endl;

          //------------------------------------
          // PUPPI subjet JEC 
          //------------------------------------
          reco::Candidate::LorentzVector uncorrSubjet = isub.correctedP4(0);
          JetCorrectorAK4pup -> setJetEta( uncorrSubjet.eta()    );
          JetCorrectorAK4pup -> setJetPt ( uncorrSubjet.pt()     );
          JetCorrectorAK4pup -> setJetE  ( uncorrSubjet.energy() );
          JetCorrectorAK4pup -> setJetA  ( isub.jetArea()         );
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

          reco::Candidate::LorentzVector corrSubjetL23resCorrDn   = subjet_corrDn_L23   * uncorrSubjet;
          reco::Candidate::LorentzVector corrSubjetL23resCorrUp   = subjet_corrUp_L23   * uncorrSubjet;
       
          //------------------------------------
          // subjet JER SF
          //------------------------------------
          TLorentzVector GenSubJet;
          double ptsmear   = 1;
          double ptsmearUp = 1;
          double ptsmearDn = 1;
          if (!iEvent.isRealData()){
            const reco::GenJet* genJet = isub.genJet();
            if (genJet) {
              GenSubJet.SetPtEtaPhiM( genJet->pt(), genJet->eta(), genJet->phi(), genJet->mass() );
              if (verbose_) cout<<"  SD subjet genJet pt "<<genJet->pt()<<" mass "<<genJet->mass()<<" reco pt "<<subjetPt<<" reco mass "<<subjetMass<<endl;
            }
            double jer_sf    = jer_scaler.getScaleFactor({{JME::Binning::JetEta, corrSubjetL23res.eta()}});
            double jer_sf_up = jer_scaler.getScaleFactor({{JME::Binning::JetEta, corrSubjetL23res.eta()}}, Variation::UP);
            double jer_sf_dn = jer_scaler.getScaleFactor({{JME::Binning::JetEta, corrSubjetL23res.eta()}}, Variation::DOWN);
            if (verbose_) std::cout << " SD subjet JER Scale factors (Nominal / Up / Down) : " << jer_sf << " / " << jer_sf_up << " / " << jer_sf_dn << std::endl;
            double recopt    = corrSubjetL23res.pt();
            double genpt     = GenJetMatched.Perp();
            double deltapt   = (recopt-genpt)*(jer_sf-1.0);
            double deltaptUp = (recopt-genpt)*(jer_sf_up-1.0);
            double deltaptDn = (recopt-genpt)*(jer_sf_dn-1.0);
            ptsmear   = std::max((double)0.0, (recopt+deltapt)/recopt     );
            ptsmearUp = std::max((double)0.0, (recopt+deltaptUp)/recopt   );
            ptsmearDn = std::max((double)0.0, (recopt+deltaptDn)/recopt   );
            if (verbose_) std::cout<<" SD subjet ptsmear "<<ptsmear<<" ptsmearUp "<<ptsmearUp<<" ptsmearDn "<<ptsmearDn<<endl;
          }
          reco::Candidate::LorentzVector corrSubjetL23resPtSmear   = ptsmear   * corrSubjetL23res ;
          reco::Candidate::LorentzVector corrSubjetL23resPtSmearUp = ptsmearUp * corrSubjetL23res ;
          reco::Candidate::LorentzVector corrSubjetL23resPtSmearDn = ptsmearDn * corrSubjetL23res ;

          //------------------------------------
          // subjet values for Tree
          //------------------------------------

          if (count_pup==0){
            pup0_P4_uncorr            .SetPtEtaPhiM( subjetPt, subjetEta, subjetPhi, subjetMass);
            pup0_P4_L23res            .SetPtEtaPhiM( corrSubjetL23res          .pt() , corrSubjetL23res          .eta() , corrSubjetL23res          .phi() , corrSubjetL23res          .mass() );
            pup0_P4_L23resCorrUp      .SetPtEtaPhiM( corrSubjetL23resCorrUp    .pt() , corrSubjetL23resCorrUp    .eta() , corrSubjetL23resCorrUp    .phi() , corrSubjetL23resCorrUp    .mass() );
            pup0_P4_L23resCorrDn      .SetPtEtaPhiM( corrSubjetL23resCorrDn    .pt() , corrSubjetL23resCorrDn    .eta() , corrSubjetL23resCorrDn    .phi() , corrSubjetL23resCorrDn    .mass() );
            pup0_P4_L23resPtSmear     .SetPtEtaPhiM( corrSubjetL23resPtSmear   .pt() , corrSubjetL23resPtSmear   .eta() , corrSubjetL23resPtSmear   .phi() , corrSubjetL23resPtSmear   .mass() );
            pup0_P4_L23resPtSmearUp   .SetPtEtaPhiM( corrSubjetL23resPtSmearUp .pt() , corrSubjetL23resPtSmearUp .eta() , corrSubjetL23resPtSmearUp .phi() , corrSubjetL23resPtSmearUp .mass() );
            pup0_P4_L23resPtSmearDn   .SetPtEtaPhiM( corrSubjetL23resPtSmearDn .pt() , corrSubjetL23resPtSmearDn .eta() , corrSubjetL23resPtSmearDn .phi() , corrSubjetL23resPtSmearDn .mass() );

            pup0_tau1   = isub.userFloat("NsubjettinessAK8PFPuppiSoftDropSubjets:tau1");
            pup0_tau2   = isub.userFloat("NsubjettinessAK8PFPuppiSoftDropSubjets:tau2");
            pup0_tau3   = isub.userFloat("NsubjettinessAK8PFPuppiSoftDropSubjets:tau3");
          
            pup0_flav_parton   = isub.partonFlavour();
            pup0_flav_hadron   = isub.hadronFlavour();
            pup0_area          = isub.jetArea() ;
            pup0_bdisc         = subjetBdisc;
          }
          if (count_pup==1) {
            pup1_P4_uncorr            .SetPtEtaPhiM( subjetPt, subjetEta, subjetPhi, subjetMass);
            pup1_P4_L23res            .SetPtEtaPhiM( corrSubjetL23res          .pt() , corrSubjetL23res          .eta() , corrSubjetL23res          .phi() , corrSubjetL23res          .mass() );
            pup1_P4_L23resCorrUp      .SetPtEtaPhiM( corrSubjetL23resCorrUp    .pt() , corrSubjetL23resCorrUp    .eta() , corrSubjetL23resCorrUp    .phi() , corrSubjetL23resCorrUp    .mass() );
            pup1_P4_L23resCorrDn      .SetPtEtaPhiM( corrSubjetL23resCorrDn    .pt() , corrSubjetL23resCorrDn    .eta() , corrSubjetL23resCorrDn    .phi() , corrSubjetL23resCorrDn    .mass() );
            pup1_P4_L23resPtSmear     .SetPtEtaPhiM( corrSubjetL23resPtSmear   .pt() , corrSubjetL23resPtSmear   .eta() , corrSubjetL23resPtSmear   .phi() , corrSubjetL23resPtSmear   .mass() );
            pup1_P4_L23resPtSmearUp   .SetPtEtaPhiM( corrSubjetL23resPtSmearUp .pt() , corrSubjetL23resPtSmearUp .eta() , corrSubjetL23resPtSmearUp .phi() , corrSubjetL23resPtSmearUp .mass() );
            pup1_P4_L23resPtSmearDn   .SetPtEtaPhiM( corrSubjetL23resPtSmearDn .pt() , corrSubjetL23resPtSmearDn .eta() , corrSubjetL23resPtSmearDn .phi() , corrSubjetL23resPtSmearDn .mass() );

            pup1_tau1   = isub.userFloat("NsubjettinessAK8PFPuppiSoftDropSubjets:tau1");
            pup1_tau2   = isub.userFloat("NsubjettinessAK8PFPuppiSoftDropSubjets:tau2");
            pup1_tau3   = isub.userFloat("NsubjettinessAK8PFPuppiSoftDropSubjets:tau3");
          
            pup1_flav_parton   = isub.partonFlavour();
            pup1_flav_hadron   = isub.hadronFlavour();
            pup1_area          = isub.jetArea() ;
            pup1_bdisc         = subjetBdisc;
          }

          if (subjetMass > mostMassiveSDPUPPIsubjetMass) mostMassiveSDPUPPIsubjetMass = subjetMass;
          count_pup++;
           if (verbose_) cout<<"  SD Subjet pt "<<subjetPt<<" Eta "<<subjetEta<<" deltaRsubjetJet "<<deltaRsubjetJet<<" Mass "<<subjetMass<<" Bdisc "<<subjetBdisc<<endl; 


        }
      }
    }

    TLorentzVector sumPUPsubjets_P4_uncorr          ;
    TLorentzVector sumPUPsubjets_P4_L23res          ;
    TLorentzVector sumPUPsubjets_P4_L23resCorrUp    ;
    TLorentzVector sumPUPsubjets_P4_L23resCorrDn    ;
    TLorentzVector sumPUPsubjets_P4_L23resPtSmear   ;
    TLorentzVector sumPUPsubjets_P4_L23resPtSmearUp ;
    TLorentzVector sumPUPsubjets_P4_L23resPtSmearDn ;
    if (count_SD>1){ 
      sumPUPsubjets_P4_uncorr            = pup0_P4_uncorr            + pup1_P4_uncorr            ; 
      sumPUPsubjets_P4_L23res            = pup0_P4_L23res            + pup1_P4_L23res            ; 
      sumPUPsubjets_P4_L23resCorrUp      = pup0_P4_L23resCorrUp      + pup1_P4_L23resCorrUp      ; 
      sumPUPsubjets_P4_L23resCorrDn      = pup0_P4_L23resCorrDn      + pup1_P4_L23resCorrDn      ; 
      sumPUPsubjets_P4_L23resPtSmear     = pup0_P4_L23resPtSmear     + pup1_P4_L23resPtSmear     ; 
      sumPUPsubjets_P4_L23resPtSmearUp   = pup0_P4_L23resPtSmearUp   + pup1_P4_L23resPtSmearUp   ; 
      sumPUPsubjets_P4_L23resPtSmearDn   = pup0_P4_L23resPtSmearDn   + pup1_P4_L23resPtSmearDn   ; 
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
    if (verbose_) cout<<"Fill AllHadTree "<<endl;
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
      Jet0SDmass                             = softDropMass;                            
      Jet0SDmassRaw                          = sumSDsubjets_P4_uncorr          .M()    ; // Full softDrop uncorrected 4-vector     
      Jet0SDmassCorrL23                      = sumSDsubjets_P4_L23res          .M()    ;   
      Jet0SDmassCorrL23Up                    = sumSDsubjets_P4_L23resCorrUp    .M()    ;   
      Jet0SDmassCorrL23Dn                    = sumSDsubjets_P4_L23resCorrDn    .M()    ; 
      Jet0SDmassCorrL123                     = sumSDsubjets_P4_L123res         .M()    ;  
      Jet0SDmassCorrL123Up                   = sumSDsubjets_P4_L123resCorrUp   .M()    ;   
      Jet0SDmassCorrL123Dn                   = sumSDsubjets_P4_L123resCorrDn   .M()    ;  
      Jet0SDmassCorrL23Smear                 = sumSDsubjets_P4_L23resPtSmear   .M()    ;
      Jet0SDmassCorrL23SmearUp               = sumSDsubjets_P4_L23resPtSmearUp .M()    ;
      Jet0SDmassCorrL23SmearDn               = sumSDsubjets_P4_L23resPtSmearDn .M()    ;
      Jet0SDptRaw                            = sumSDsubjets_P4_uncorr          .Perp() ;  // Full softDrop uncorrected 4-vector 
      Jet0SDptCorrL23                        = sumSDsubjets_P4_L23res          .Perp() ;  
      Jet0SDptCorrL23Up                      = sumSDsubjets_P4_L23resCorrUp    .Perp() ;  
      Jet0SDptCorrL23Dn                      = sumSDsubjets_P4_L23resCorrDn    .Perp() ;  
      Jet0SDptCorrL123                       = sumSDsubjets_P4_L123res         .Perp() ;  
      Jet0SDptCorrL123Up                     = sumSDsubjets_P4_L123resCorrUp   .Perp() ;  
      Jet0SDptCorrL123Dn                     = sumSDsubjets_P4_L123resCorrDn   .Perp() ;  
      Jet0SDptCorrL23Smear                   = sumSDsubjets_P4_L23resPtSmear   .Perp() ;
      Jet0SDptCorrL23SmearUp                 = sumSDsubjets_P4_L23resPtSmearUp .Perp() ;
      Jet0SDptCorrL23SmearDn                 = sumSDsubjets_P4_L23resPtSmearDn .Perp() ;
      Jet0SDetaRaw                           = sumSDsubjets_P4_uncorr.Eta()  ;          // Full softDrop uncorrected 4-vector           
      Jet0SDphiRaw                           = sumSDsubjets_P4_uncorr.Phi()  ;          // Full softDrop uncorrected 4-vector           
      Jet0MassPruned                         = prunedMass ;     
      Jet0MassTrimmed                        = trimmedMass ;     
      Jet0Tau1                               = tau1 ;  
      Jet0Tau2                               = tau2 ;  
      Jet0Tau3                               = tau3 ;  
      Jet0Tau4                               = tau4 ;  
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

      Jet0PuppiP                             = puppi_p    ;                  
      Jet0PuppiPt                            = puppi_pt   ;                  
      Jet0PuppiEta                           = puppi_eta  ;                   
      Jet0PuppiPhi                           = puppi_phi  ;                  
      Jet0PuppiMass                          = puppi_mass ;                  
      Jet0PuppiSDmass                        = sumPUPsubjets_P4_uncorr           .M()   ;
      Jet0PuppiSDmassCorr                    = sumPUPsubjets_P4_L23res           .M()   ;
      Jet0PuppiSDmassCorrUp                  = sumPUPsubjets_P4_L23resCorrUp     .M()   ;
      Jet0PuppiSDmassCorrDn                  = sumPUPsubjets_P4_L23resCorrDn     .M()   ;
      Jet0PuppiSDmassCorrL23Smear            = sumPUPsubjets_P4_L23resPtSmear    .M()   ;
      Jet0PuppiSDmassCorrL23SmearUp          = sumPUPsubjets_P4_L23resPtSmearUp  .M()   ;
      Jet0PuppiSDmassCorrL23SmearDn          = sumPUPsubjets_P4_L23resPtSmearDn  .M()   ;
      Jet0PuppiSDpt                          = sumPUPsubjets_P4_uncorr           .Perp();
      Jet0PuppiSDptCorr                      = sumPUPsubjets_P4_L23res           .Perp();
      Jet0PuppiSDptCorrUp                    = sumPUPsubjets_P4_L23resCorrUp     .Perp();
      Jet0PuppiSDptCorrDn                    = sumPUPsubjets_P4_L23resCorrDn     .Perp();
      Jet0PuppiSDptCorrL23Smear              = sumPUPsubjets_P4_L23resPtSmear    .Perp();
      Jet0PuppiSDptCorrL23SmearUp            = sumPUPsubjets_P4_L23resPtSmearUp  .Perp();
      Jet0PuppiSDptCorrL23SmearDn            = sumPUPsubjets_P4_L23resPtSmearDn  .Perp();
      Jet0PuppiSDeta                         = sumPUPsubjets_P4_uncorr           .Eta() ;
      Jet0PuppiSDphi                         = sumPUPsubjets_P4_uncorr           .Phi() ;
      Jet0PuppiTau1                          = puppi_tau1       ;                  
      Jet0PuppiTau2                          = puppi_tau2       ;                  
      Jet0PuppiTau3                          = puppi_tau3       ;                  
      Jet0PuppiTau4                          = puppi_tau4       ;                  
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

      Jet0PuppiCHF                                = puppi_CHF   ; 
      Jet0PuppiNHF                                = puppi_NHF   ; 
      Jet0PuppiCM                                 = puppi_CM    ; 
      Jet0PuppiNM                                 = puppi_NM    ; 
      Jet0PuppiNEF                                = puppi_NEF   ; 
      Jet0PuppiCEF                                = puppi_CEF   ; 
      Jet0PuppiMF                                 = puppi_MF    ; 
      Jet0PuppiMult                               = puppi_Mult  ; 

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
      // Jet0MatchedGenJetDR                    = GenJetMatched_dRmin;             
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
      Jet1SDmass                             = softDropMass;                           // Full softDrop uncorrected 4-vector      
      Jet1SDmassRaw                          = sumSDsubjets_P4_uncorr          .M()    ; // Full softDrop uncorrected 4-vector     
      Jet1SDmassCorrL23                      = sumSDsubjets_P4_L23res          .M()    ;   
      Jet1SDmassCorrL23Up                    = sumSDsubjets_P4_L23resCorrUp   .M()    ;   
      Jet1SDmassCorrL23Dn                    = sumSDsubjets_P4_L23resCorrDn   .M()    ; 
      Jet1SDmassCorrL123                     = sumSDsubjets_P4_L123res         .M()    ;  
      Jet1SDmassCorrL123Up                   = sumSDsubjets_P4_L123resCorrUp  .M()    ;   
      Jet1SDmassCorrL123Dn                   = sumSDsubjets_P4_L123resCorrDn  .M()    ;  
      Jet1SDmassCorrL23Smear                    = sumSDsubjets_P4_L23resPtSmear   .M()    ;
      Jet1SDmassCorrL23SmearUp                  = sumSDsubjets_P4_L23resPtSmearUp .M()    ;
      Jet1SDmassCorrL23SmearDn                  = sumSDsubjets_P4_L23resPtSmearDn .M()    ;
      Jet1SDptRaw                            = sumSDsubjets_P4_uncorr          .Perp() ;  // Full softDrop uncorrected 4-vector 
      Jet1SDptCorrL23                        = sumSDsubjets_P4_L23res          .Perp() ;  
      Jet1SDptCorrL23Up                      = sumSDsubjets_P4_L23resCorrUp   .Perp() ;  
      Jet1SDptCorrL23Dn                      = sumSDsubjets_P4_L23resCorrDn   .Perp() ;  
      Jet1SDptCorrL123                       = sumSDsubjets_P4_L123res         .Perp() ;  
      Jet1SDptCorrL123Up                     = sumSDsubjets_P4_L123resCorrUp  .Perp() ;  
      Jet1SDptCorrL123Dn                     = sumSDsubjets_P4_L123resCorrDn  .Perp() ;  
      Jet1SDptCorrL23Smear                      = sumSDsubjets_P4_L23resPtSmear   .Perp() ;
      Jet1SDptCorrL23SmearUp                    = sumSDsubjets_P4_L23resPtSmearUp .Perp() ;
      Jet1SDptCorrL23SmearDn                    = sumSDsubjets_P4_L23resPtSmearDn .Perp() ;
      Jet1SDetaRaw                           = sumSDsubjets_P4_uncorr.Eta()          ;  // Full softDrop uncorrected 4-vector           
      Jet1SDphiRaw                           = sumSDsubjets_P4_uncorr.Phi()          ;  // Full softDrop uncorrected 4-vector   
      Jet1MassPruned                         = prunedMass ;     
      Jet1MassTrimmed                        = trimmedMass ;     
      Jet1Tau1                               = tau1 ;  
      Jet1Tau2                               = tau2 ;  
      Jet1Tau3                               = tau3 ;  
      Jet1Tau4                               = tau4 ;  
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

      Jet1PuppiP                             = puppi_p    ;                  
      Jet1PuppiPt                            = puppi_pt   ;                  
      Jet1PuppiEta                           = puppi_eta  ;                   
      Jet1PuppiPhi                           = puppi_phi  ;                  
      Jet1PuppiMass                          = puppi_mass ;   

      Jet1PuppiSDmass                        = sumPUPsubjets_P4_uncorr           .M()   ;
      Jet1PuppiSDmassCorr                    = sumPUPsubjets_P4_L23res           .M()   ;
      Jet1PuppiSDmassCorrUp                  = sumPUPsubjets_P4_L23resCorrUp     .M()   ;
      Jet1PuppiSDmassCorrDn                  = sumPUPsubjets_P4_L23resCorrDn     .M()   ;
      Jet1PuppiSDmassCorrL23Smear            = sumPUPsubjets_P4_L23resPtSmear    .M()   ;
      Jet1PuppiSDmassCorrL23SmearUp          = sumPUPsubjets_P4_L23resPtSmearUp  .M()   ;
      Jet1PuppiSDmassCorrL23SmearDn          = sumPUPsubjets_P4_L23resPtSmearDn  .M()   ;
      Jet1PuppiSDpt                          = sumPUPsubjets_P4_uncorr           .Perp();
      Jet1PuppiSDptCorr                      = sumPUPsubjets_P4_L23res           .Perp();
      Jet1PuppiSDptCorrUp                    = sumPUPsubjets_P4_L23resCorrUp     .Perp();
      Jet1PuppiSDptCorrDn                    = sumPUPsubjets_P4_L23resCorrDn     .Perp();
      Jet1PuppiSDptCorrL23Smear              = sumPUPsubjets_P4_L23resPtSmear    .Perp();
      Jet1PuppiSDptCorrL23SmearUp            = sumPUPsubjets_P4_L23resPtSmearUp  .Perp();
      Jet1PuppiSDptCorrL23SmearDn            = sumPUPsubjets_P4_L23resPtSmearDn  .Perp();
      Jet1PuppiSDeta                         = sumPUPsubjets_P4_uncorr           .Eta() ;
      Jet1PuppiSDphi                         = sumPUPsubjets_P4_uncorr           .Phi() ;

      Jet1PuppiTau1                          = puppi_tau1       ;                  
      Jet1PuppiTau2                          = puppi_tau2       ;                  
      Jet1PuppiTau3                          = puppi_tau3       ;                  
      Jet1PuppiTau4                          = puppi_tau4       ;                  
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


      Jet1PuppiCHF                                = puppi_CHF   ; 
      Jet1PuppiNHF                                = puppi_NHF   ; 
      Jet1PuppiCM                                 = puppi_CM    ; 
      Jet1PuppiNM                                 = puppi_NM    ; 
      Jet1PuppiNEF                                = puppi_NEF   ; 
      Jet1PuppiCEF                                = puppi_CEF   ; 
      Jet1PuppiMF                                 = puppi_MF    ; 
      Jet1PuppiMult                               = puppi_Mult  ; 


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
      // Jet1MatchedGenJetDR                 = GenJetMatched_dRmin;             
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
    if (verbose_) cout<<"Fill SemiLeptTree "<<endl;
    double deltaPhi_lep_jet = fabs( deltaPhi(corrJet.phi(), lep0_p4.Phi() )) ;
    // AK8 jet should be in opposite hemisphere from lepton. If leading jet matches then use it. If it doensn't then check the second leading jet.
    if ( ((count_AK8CHS==0&& deltaPhi_lep_jet >=3.14/2) || (count_AK8CHS==1&&deltaPhi_lep_jet >=3.14/2)) && count_lep >=1 && count_fill_leptTree==0 ){
      count_fill_leptTree++;
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
      JetSDmass                             = softDropMass;                           // Full softDrop uncorrected 4-vector      
      JetSDmassRaw                          = sumSDsubjets_P4_uncorr          .M()    ; // Full softDrop uncorrected 4-vector     
      JetSDmassCorrL23                      = sumSDsubjets_P4_L23res          .M()    ;   
      JetSDmassCorrL23Up                    = sumSDsubjets_P4_L23resCorrUp   .M()    ;   
      JetSDmassCorrL23Dn                    = sumSDsubjets_P4_L23resCorrDn   .M()    ; 
      JetSDmassCorrL123                     = sumSDsubjets_P4_L123res         .M()    ;  
      JetSDmassCorrL123Up                   = sumSDsubjets_P4_L123resCorrUp  .M()    ;   
      JetSDmassCorrL123Dn                   = sumSDsubjets_P4_L123resCorrDn  .M()    ;  
      JetSDmassCorrL23Smear                    = sumSDsubjets_P4_L23resPtSmear   .M()    ;
      JetSDmassCorrL23SmearUp                  = sumSDsubjets_P4_L23resPtSmearUp .M()    ;
      JetSDmassCorrL23SmearDn                  = sumSDsubjets_P4_L23resPtSmearDn .M()    ;
      JetSDptRaw                            = sumSDsubjets_P4_uncorr          .Perp() ;  // Full softDrop uncorrected 4-vector 
      JetSDptCorrL23                        = sumSDsubjets_P4_L23res          .Perp() ;  
      JetSDptCorrL23Up                      = sumSDsubjets_P4_L23resCorrUp   .Perp() ;  
      JetSDptCorrL23Dn                      = sumSDsubjets_P4_L23resCorrDn   .Perp() ;  
      JetSDptCorrL123                       = sumSDsubjets_P4_L123res         .Perp() ;  
      JetSDptCorrL123Up                     = sumSDsubjets_P4_L123resCorrUp  .Perp() ;  
      JetSDptCorrL123Dn                     = sumSDsubjets_P4_L123resCorrDn  .Perp() ;  
      JetSDptCorrL23Smear                      = sumSDsubjets_P4_L23resPtSmear   .Perp() ;
      JetSDptCorrL23SmearUp                    = sumSDsubjets_P4_L23resPtSmearUp .Perp() ;
      JetSDptCorrL23SmearDn                    = sumSDsubjets_P4_L23resPtSmearDn .Perp() ;
      JetSDetaRaw                           = sumSDsubjets_P4_uncorr.Eta()     ;      // Full softDrop uncorrected 4-vector           
      JetSDphiRaw                           = sumSDsubjets_P4_uncorr.Phi()     ;      // Full softDrop uncorrected 4-vector   
      JetMassPruned                         = prunedMass ;     
      JetMassTrimmed                        = trimmedMass ;     
      JetTau1                               = tau1 ;  
      JetTau2                               = tau2 ;  
      JetTau3                               = tau3 ;  
      JetTau4                               = tau4 ;  
      JetTau32                              = tau32 ;  
      JetTau21                              = tau21 ;  
      JetSDsubjet0bdisc                     = sub0_bdisc ;  
      JetSDsubjet1bdisc                     = sub1_bdisc ;   
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

      JetPuppiP                             = puppi_p    ;                  
      JetPuppiPt                            = puppi_pt   ;                  
      JetPuppiEta                           = puppi_eta  ;                   
      JetPuppiPhi                           = puppi_phi  ;                  
      JetPuppiMass                          = puppi_mass ;                  

      Jet1PuppiSDmass                       = sumPUPsubjets_P4_uncorr           .M()   ;
      Jet1PuppiSDmassCorr                   = sumPUPsubjets_P4_L23res           .M()   ;
      Jet1PuppiSDmassCorrUp                 = sumPUPsubjets_P4_L23resCorrUp     .M()   ;
      Jet1PuppiSDmassCorrDn                 = sumPUPsubjets_P4_L23resCorrDn     .M()   ;
      Jet1PuppiSDmassCorrL23Smear           = sumPUPsubjets_P4_L23resPtSmear    .M()   ;
      Jet1PuppiSDmassCorrL23SmearUp         = sumPUPsubjets_P4_L23resPtSmearUp  .M()   ;
      Jet1PuppiSDmassCorrL23SmearDn         = sumPUPsubjets_P4_L23resPtSmearDn  .M()   ;
      Jet1PuppiSDpt                         = sumPUPsubjets_P4_uncorr           .Perp();
      Jet1PuppiSDptCorr                     = sumPUPsubjets_P4_L23res           .Perp();
      Jet1PuppiSDptCorrUp                   = sumPUPsubjets_P4_L23resCorrUp     .Perp();
      Jet1PuppiSDptCorrDn                   = sumPUPsubjets_P4_L23resCorrDn     .Perp();
      Jet1PuppiSDptCorrL23Smear             = sumPUPsubjets_P4_L23resPtSmear    .Perp();
      Jet1PuppiSDptCorrL23SmearUp           = sumPUPsubjets_P4_L23resPtSmearUp  .Perp();
      Jet1PuppiSDptCorrL23SmearDn           = sumPUPsubjets_P4_L23resPtSmearDn  .Perp();
      Jet1PuppiSDeta                        = sumPUPsubjets_P4_uncorr           .Eta() ;
      Jet1PuppiSDphi                        = sumPUPsubjets_P4_uncorr           .Phi() ;

      JetPuppiTau1                          = puppi_tau1       ;                  
      JetPuppiTau2                          = puppi_tau2       ;                  
      JetPuppiTau3                          = puppi_tau3       ;                  
      JetPuppiTau4                          = puppi_tau4       ;                  
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


      JetPuppiCHF                                = puppi_CHF   ; 
      JetPuppiNHF                                = puppi_NHF   ; 
      JetPuppiCM                                 = puppi_CM    ; 
      JetPuppiNM                                 = puppi_NM    ; 
      JetPuppiNEF                                = puppi_NEF   ; 
      JetPuppiCEF                                = puppi_CEF   ; 
      JetPuppiMF                                 = puppi_MF    ; 
      JetPuppiMult                               = puppi_Mult  ; 

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
      // JetMatchedGenJetDR                    = GenJetMatched_dRmin;             
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
  AllHadNPUtrue        = nPU;           
  AllHadRho            = rho ;               
  AllHadEventWeight    = 1 ;   
  AllHadPUweight       = puweight  ; 
  AllHadPUweight_MBup  = puweightUp ;
  AllHadPUweight_MBdn  = puweightDn  ;          
  DijetMass            = (AK8jet0_P4corr + AK8jet1_P4corr).M() ;                                                   
  DijetMassPuppi       = (PUPPIjet0_P4corr + PUPPIjet1_P4corr).M() ;                                                   
  DijetDeltaR          = deltaR( AK8jet0_P4corr.Eta(), AK8jet0_P4corr.Phi(), AK8jet1_P4corr.Eta(), AK8jet1_P4corr.Phi() );               
  DijetDeltaPhi        = fabs( deltaPhi( AK8jet0_P4corr.Phi(),  AK8jet1_P4corr.Phi() ));                 
  DijetDeltaRap        = fabs(AK8jet0_P4corr.Rapidity() -  AK8jet1_P4corr.Rapidity() );

  DiGenJetMass         = (GenJetMatched0 + GenJetMatched1).M();                   
  GenTTmass            = (t1_p4+t2_p4).M() ;               
  HT                   = HT_AK4_pt30          ;                
  HT_CorrDn            = HT_AK4_pt30_corrDn   ;                
  HT_CorrUp            = HT_AK4_pt30_corrUp   ;  
  HT_PtSmearNom        = HT_AK4_pt30_smearNom ;          
  HT_PtSmearUp         = HT_AK4_pt30_smearUp  ;               
  HT_PtSmearDn         = HT_AK4_pt30_smearDn  ;               
  Q2weight_CorrDn      = Q2wgt_down ;              
  Q2weight_CorrUp      = Q2wgt_up ;              
  NNPDF3weight_CorrDn  = NNPDF3wgt_down ;              
  NNPDF3weight_CorrUp  = NNPDF3wgt_up ;              
  AllHadRunNum         = iEvent.id().run() ;              
  AllHadLumiBlock      = iEvent.id().luminosityBlock() ;              
  AllHadEventNum       = iEvent.id().event() ;  
  if (passMETfilters) PassMETFilters       = 1;
  else PassMETFilters                      = 0;


                 


  //------------------------------------
  // WRITE TREE WITH BASELINE PT CUT AND ETA CUT
  //------------------------------------
  if (AK8jet0_P4corr.Perp()>300 && AK8jet1_P4corr.Perp()>300 && fabs( AK8jet0_P4corr.Rapidity() ) <2.4 &&  fabs( AK8jet1_P4corr.Rapidity() ) <2.4  ){
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
  SemiLeptNPUtrue              = nPU;     
  SemiLeptRho                  = rho ;               
  SemiLeptEventWeight          = 1 ;              
  SemiLeptPUweight       = puweight  ; 
  SemiLeptPUweight_MBup  = puweightUp ;
  SemiLeptPUweight_MBdn  = puweightDn  ;

  SemiLeptGenTTmass            = (t1_p4+t2_p4).M() ; 
    

  double htlep = lep0_p4.Perp() + met.pt() ;
  HTlep                = htlep ;
  ST                   = htlep + HT_AK4_pt30           ;                
  ST_CorrDn            = htlep + HT_AK4_pt30_corrDn    ;                
  ST_CorrUp            = htlep + HT_AK4_pt30_corrUp    ;                
  ST_PtSmearNom        = htlep + HT_AK4_pt30_smearNom  ;                
  ST_PtSmearUp         = htlep + HT_AK4_pt30_smearUp   ;                
  ST_PtSmearDn         = htlep + HT_AK4_pt30_smearDn   ;                
  SemiLeptQ2weight_CorrDn      = Q2wgt_down ;              
  SemiLeptQ2weight_CorrUp      = Q2wgt_up ;              
  SemiLeptNNPDF3weight_CorrDn  = NNPDF3wgt_down ;              
  SemiLeptNNPDF3weight_CorrUp  = NNPDF3wgt_up ;              
  SemiLeptRunNum               = iEvent.id().run() ;              
  SemiLeptLumiBlock            = iEvent.id().luminosityBlock() ;              
  SemiLeptEventNum             = iEvent.id().event() ;              
  if(passMETfilters) SemiLeptPassMETFilters  = 1;
  else SemiLeptPassMETFilters  = 0;

  AK4dRminPt        = AK4_dRMinLep_p4.Perp() ;
  AK4dRminEta       = AK4_dRMinLep_p4.Eta()  ;
  AK4dRminPhi       = AK4_dRMinLep_p4.Phi()  ;
  AK4dRminMass      = AK4_dRMinLep_p4.M()    ;
  AK4dRminBdisc     = AK4_dRMinLep_bdisc     ;
  AK4dRminLep       = AK4_dRMinLep           ;
  
  AK4BtagdRminPt    = AK4_btagged_dRMinLep_p4.Perp();
  AK4BtagdRminBdisc = AK4_btagged_dRMinLep_bdisc    ;
  AK4BtagdRminLep   = AK4_btagged_dRMinLep          ;

 
  if (ak4_btag_loose)  LepHemiContainsAK4BtagLoose   = 1  ;
  else                 LepHemiContainsAK4BtagLoose   = 0  ;
  if (ak4_btag_medium) LepHemiContainsAK4BtagMedium  = 1  ;
  else                 LepHemiContainsAK4BtagMedium  = 0  ;
  if (ak4_btag_tight)  LepHemiContainsAK4BtagTight   = 1  ;
  else                 LepHemiContainsAK4BtagTight   = 0  ;

  LeptonPhi   = lep0_p4.Phi()  ; 
  LeptonPt    = lep0_p4.Perp() ;  
  LeptonEta   = lep0_p4.Eta()  ; 
  LeptonMass  = lep0_p4.M() ; 


  if (count_mu==1 && count_el==0)      LeptonIsMu  = 1  ; 
  else if (count_mu==0 && count_el==1) LeptonIsMu  = 0  ; 
  else LeptonIsMu =0;

  PtRel  = AK4_dRMinLep_p4.Perp( lep0_p4.Vect() );
  MuIso  = mu0_iso04;

  Elecron_absiso            = el0_absiso           ;  
  Elecron_relIsoWithDBeta   = el0_relIsoWithDBeta  ;  
  Elecron_absiso_EA         = el0_absiso_EA        ;  
  Elecron_relIsoWithEA      = el0_relIsoWithEA     ;  
  if (el0_isMedium) Electron_isMedium  = 1         ;
  else              Electron_isMedium  = 0;
  if (el0_isTight)  Electron_isTight   = 1         ;
  else              Electron_isTight   = 0;

  if(mu0_isMedium) MuMedium = 1   ;
  else             MuMedium = 0   ;

  if(mu0_isTight) MuTight = 1   ;
  else            MuTight = 0   ;

  if(mu0_isHighPt) MuHighPt = 1   ;
  else             MuHighPt = 0   ;

  //------------------------------------
  // WRITE TREE WITH BASELINE PT CUT AND ETA CUT
  //------------------------------------


  if (GenTruth_semileptonic)  count_GenTruth_semileptonic ++;
  if (count_mu  >=1 )  count_nMu_gt1 ++; 
  if (count_el  >=1 )  count_nEl_gt1 ++; 
  if (count_mu  ==1 )  count_nMu_e1 ++; 
  if (count_el  ==1 )  count_nEl_e1 ++; 
  if (count_lep ==1 )  count_nLep_e1 ++; 
  if (count_lep ==1  && AK8jet_SemiLept_P4corr.Perp()>300)  count_JetPt300 ++; 
  if (count_lep ==1  && AK8jet_SemiLept_P4corr.Perp()>300 && fabs( AK8jet_SemiLept_P4corr.Rapidity() ) <2.4 )  count_JetPt300Eta ++; 
  if (count_lep ==1  && AK8jet_SemiLept_P4corr.Perp()>300 && fabs( AK8jet_SemiLept_P4corr.Rapidity() ) <2.4 && AK4_dRMinLep_p4.Perp() > 20)  count_JetPt300Eta_AK4 ++; 
  if (count_lep ==1  && AK8jet_SemiLept_P4corr.Perp()>300 && fabs( AK8jet_SemiLept_P4corr.Rapidity() ) <2.4 &&  mu0_p4.Perp()>40)  count_JetPt300Eta_muPt40 ++; 
  if (count_lep ==1  && AK8jet_SemiLept_P4corr.Perp()>300 && fabs( AK8jet_SemiLept_P4corr.Rapidity() ) <2.4 &&  mu0_p4.Perp()>40 && met.pt() > 40)  count_JetPt300Eta_muPt40_MET40 ++; 
  if (count_lep ==1  && AK8jet_SemiLept_P4corr.Perp()>300 && fabs( AK8jet_SemiLept_P4corr.Rapidity() ) <2.4 &&  mu0_p4.Perp()>40 && met.pt() > 40 &&  AK4_dRMinLep_p4.Perp() > 20)  count_JetPt300Eta_muPt40_MET40_AK4 ++; 

  if (count_lep ==1  && verbose_){
    cout<<" ak8pt "<<AK8jet_SemiLept_P4corr.Perp()<<endl;
    cout<<" mu pt "<<mu0_p4.Perp()<<endl;
    cout<<" el pt "<<el0_p4.Perp()<<endl;
    cout<<" met "<<met.pt() <<endl;
    cout<<" ak4 pt "<<AK4_dRMinLep_p4.Perp() <<endl;
  } 
  if (count_lep ==1 && AK8jet_SemiLept_P4corr.Perp()>200 && fabs( AK8jet_SemiLept_P4corr.Rapidity() ) <2.4 
    &&  lep0_p4.Perp()>30 && met.pt() > 30 ){
    TreeSemiLept -> Fill();
  } 


}


// ------------ method called once each job just before starting event loop  ------------
void 
B2GTTbarTreeMaker::beginJob()
{
  fPUweight = new TFile("PUweight20160908.root") ;
  hPUweight      = (TH1D*) fPUweight->Get("PUweight_true");
  hPUweight_MBup = (TH1D*) fPUweight->Get("PUweight_true_MBup");
  hPUweight_MBdn = (TH1D*) fPUweight->Get("PUweight_true_MBdn");
       
  std::cout<<"Test PU reweight file: "<<hPUweight->GetBinContent( hPUweight->GetXaxis()->FindBin( 30 ) )<<std::endl;
    

  count_GenTruth_semileptonic =0;
  count_nMu_gt1 =0; 
  count_nEl_gt1 =0; 
  count_nMu_e1 =0; 
  count_nEl_e1 =0; 
  count_nLep_e1 =0; 
  count_JetPt300 =0; 
  count_JetPt300Eta =0; 
  count_JetPt300Eta_AK4 =0; 
  count_JetPt300Eta_muPt40 =0; 
  count_JetPt300Eta_muPt40_MET40 =0; 
  count_JetPt300Eta_muPt40_MET40_AK4 =0; 

}

// ------------ method called once each job just after ending the event loop  ------------
void 
B2GTTbarTreeMaker::endJob() 
{

  std::cout<<" nEvents GenTruth semileptonic  :" <<count_GenTruth_semileptonic<<std::endl;
  std::cout<<" nEvents nMu =1   :" <<count_nMu_e1 <<std::endl;
  std::cout<<" nEvents nEl =1   :" <<count_nEl_e1 <<std::endl;
  std::cout<<" nEvents nLepton =1   :" <<count_nLep_e1 <<std::endl;
  std::cout<<" nEvents nLepton =1 && JetPt300   :" <<count_JetPt300 <<std::endl;
  std::cout<<" nEvents nLepton =1 && JetPt300Eta   :" <<count_JetPt300Eta <<std::endl;
  std::cout<<" nEvents nLepton =1 && JetPt300Eta && AK4pt>20   :" <<count_JetPt300Eta_AK4 <<std::endl;
  std::cout<<" nEvents nLepton =1 && JetPt300Eta && muPt40   :" <<count_JetPt300Eta_muPt40 <<std::endl;
  std::cout<<" nEvents nLepton =1 && JetPt300Eta && muPt40 && MET40   :" <<count_JetPt300Eta_muPt40_MET40 <<std::endl;
  std::cout<<" nEvents nLepton =1 && JetPt300Eta && muPt40 && MET40 && AK4pt>20  :" <<count_JetPt300Eta_muPt40_MET40_AK4 <<std::endl;

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

//  LocalWords:  NNPDF
