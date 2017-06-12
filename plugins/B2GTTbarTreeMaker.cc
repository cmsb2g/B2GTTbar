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
#include "DataFormats/Common/interface/ValueMap.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

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
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/EgammaCandidates/interface/ConversionFwd.h"
#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"
#include "DataFormats/PatCandidates/interface/VIDCutFlowResult.h"

// Photon
#include "DataFormats/PatCandidates/interface/Photon.h"

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

// // CMS Top Tagger
// #include "DataFormats/BTauReco/interface/CATopJetTagInfo.h"
// #include "RecoJets/JetAlgorithms/interface/CATopJetHelper.h"

// Fastjet
// #include <fastjet/JetDefinition.hh>
// #include <fastjet/PseudoJet.hh>
// #include "fastjet/tools/Filter.hh"
// #include <fastjet/ClusterSequence.hh>
// #include <fastjet/ClusterSequenceArea.hh>
// #include "fastjet/contrib/SoftDrop.hh"
// #include "fastjet/contrib/EnergyCorrelator.hh"
// #include <fastjet/Selector.hh>
// #include "fastjet/tools/Pruner.hh"
// #include "Nsubjettiness.hh"
// #include "Njettiness.hh"

// root
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include <TRandom3.h>

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


      void printCutFlowResult(vid::CutFlowResult &cutflow);

      // ----------member data ---------------------------
      edm::EDGetTokenT<pat::JetCollection>                     ak4jetToken_                     ;
      edm::EDGetTokenT<pat::JetCollection>                     ak8jetToken_                     ;
      edm::EDGetTokenT<pat::JetCollection>                     puppijetToken_                   ;
      edm::EDGetTokenT<pat::JetCollection>                     ak8CHSSoftDropSubjetsToken_      ;
      edm::EDGetTokenT<pat::JetCollection>                     ak8PuppiSoftDropSubjetsToken_    ;
      edm::EDGetTokenT<reco::GenJetCollection>                 ak4genjetToken_                  ;
      edm::EDGetTokenT<reco::GenJetCollection>                 ak8genjetToken_                  ;               
      edm::EDGetTokenT<edm::View<reco::GenParticle>>           prunedGenToken_                  ;               
      edm::EDGetTokenT<double>                                 rhoToken_                        ;
      edm::EDGetTokenT<std::vector<reco::Vertex>>              vtxToken_                        ;
      edm::EDGetTokenT<edm::TriggerResults>                    triggerResultsMETFilterToken_    ;
      edm::EDGetTokenT<edm::TriggerResults>                    triggerBits_                     ;
      edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjects_                  ;
      edm::EDGetTokenT<pat::PackedTriggerPrescales>            triggerPrescales_                ;
      edm::EDGetTokenT<bool>                                   badMuonFilterToken_              ;
      edm::EDGetTokenT<bool>                                   badChargedCandidateFilterToken_  ;
      edm::EDGetTokenT<pat::MuonCollection>                    muonToken_                       ;
      edm::EDGetTokenT<edm::View<pat::Electron>>               electronToken_                   ;  
      edm::EDGetTokenT<edm::View<pat::Photon>>                 photonToken_                     ;  
      edm::EDGetTokenT<pat::METCollection>                     metToken_                        ;
      edm::EDGetTokenT<std::vector<PileupSummaryInfo>>         pileupInfoToken_                 ;
      edm::EDGetTokenT<LHEEventProduct>                        lheSrc_                          ;
      edm::EDGetTokenT<GenEventInfoProduct>                    pdfToken_                        ;
      edm::EDGetTokenT<reco::BeamSpot>                         beamSpotToken_                   ;                     
      edm::EDGetTokenT<reco::ConversionCollection>             conversionsToken_                ;

      edm::EDGetTokenT<edm::ValueMap<vid::CutFlowResult>>      eleIdFullInfoMapToken_HLTpre_    ;
      edm::EDGetTokenT<edm::ValueMap<vid::CutFlowResult>>      eleIdFullInfoMapToken_Loose_     ;
      edm::EDGetTokenT<edm::ValueMap<vid::CutFlowResult>>      eleIdFullInfoMapToken_Medium_    ;
      edm::EDGetTokenT<edm::ValueMap<vid::CutFlowResult>>      eleIdFullInfoMapToken_Tight_     ;
      edm::EDGetTokenT<edm::ValueMap<vid::CutFlowResult>>      eleIdFullInfoMapToken_HEEP_      ;
  
      // Grab from configuration file
    
      bool verbose_         ;
      bool verboseGen_      ;
      
      bool useToolbox_      ;

      bool runGenLoop_      ;
      bool runAllHadTree_   ;
      bool runSemiLeptTree_ ;

      bool isZprime_        ;
      bool isttbar_         ;
      bool isRSG_           ;
      bool isRun2016F_      ;

      std::vector<std::string>  jecPayloadsAK4chs_;
      std::vector<std::string>  jecPayloadsAK8chs_;
      std::vector<std::string>  jecPayloadsAK4pup_;
      std::vector<std::string>  jecPayloadsAK8pup_;

      std::vector<std::string>  jecPayloadsAK4chsSecondary_;
      std::vector<std::string>  jecPayloadsAK8chsSecondary_;
      std::vector<std::string>  jecPayloadsAK4pupSecondary_;
      std::vector<std::string>  jecPayloadsAK8pupSecondary_;

      std::string jertextAK4_;   // jet resolution AK4 jets
      std::string jertextAK8_;   // jet resolution AK8 jets
      std::string jerSFtext_ ;   // jer SF

      // JEC
      boost::shared_ptr<FactorizedJetCorrector>   JetCorrectorAK4chs;
      boost::shared_ptr<FactorizedJetCorrector>   JetCorrectorAK8chs;
      boost::shared_ptr<FactorizedJetCorrector>   JetCorrectorAK4pup;
      boost::shared_ptr<FactorizedJetCorrector>   JetCorrectorAK8pup;
      boost::shared_ptr<JetCorrectionUncertainty> JetCorrUncertAK4chs;
      boost::shared_ptr<JetCorrectionUncertainty> JetCorrUncertAK8chs;
      boost::shared_ptr<JetCorrectionUncertainty> JetCorrUncertAK4pup;
      boost::shared_ptr<JetCorrectionUncertainty> JetCorrUncertAK8pup;
      
      // PU weight
      TFile* fPUweight;
      TH1D* hPUweight;
      TH1D* hPUweight_MBup;
      TH1D* hPUweight_MBdn;

      // A few basic histograms
      TH1D * h_cutflow_allhad ;
      TH1D * h_cutflow_semilept;
      // TH1D * h_ak8puppi_softDropMass          ;
      // TH1D * h_ak8chs_softDropMass            ;
      // TH1D * h_ak8chs_softDropMass_reweighted ;
      // TH1D * h_ak8chs_pt                      ;
      // TH1D * h_ak8chs_pt_reweighted           ;
      TH1D * h_NtrueIntPU        ;
      TH1D * h_NPV               ;               
      TH1D * h_NPVreweighted     ;     
      TH1D * h_NPVgood           ;               
      TH1D * h_NPVgoodreweighted ;     

      // -- Triggers to be saved in tree
      std::vector<std::string> trigsToRun;

  
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

      // std::vector<float> *vAK4pt      = new std::vector<float>;
      // std::vector<float> *vAK4eta     = new std::vector<float>;
      // std::vector<float> *vAK4phi     = new std::vector<float>;
      // std::vector<float> *vAK4m       = new std::vector<float>;
      // std::vector<float> *vAK4bdisc   = new std::vector<float>;

      // std::vector<std::string> *AllHadTrigNames     = new std::vector<std::string>;
      std::vector<int>  *AllHadTrigPrescales = new std::vector<int>  ;
      std::vector<bool> *AllHadTrigPass      = new std::vector<bool> ;
      std::string AllHadTrigAcceptBits;

      Int_t   PassMETFilters                            ;
      Float_t Jet0PtRaw                                 ;
      Float_t Jet0EtaRaw                                ;
      Float_t Jet0PhiRaw                                ;
      Float_t Jet0MassRaw                               ;
      // Float_t Jet0P                                     ;
      // Float_t Jet0Pt                                    ;
      // Float_t Jet0Eta                                   ;
      // Float_t Jet0Phi                                   ;
      // Float_t Jet0Rap                                   ;
      // Float_t Jet0Energy                                ;
      // Float_t Jet0Mass                                  ;
      Float_t Jet0Area                                  ;
      // Float_t Jet0SDmass                                ;
      Float_t Jet0SDmassRaw                             ;
      Float_t Jet0SDmassSubjetCorrL23                   ;    
      // Float_t Jet0SDmassCorrL23Up                       ;    
      // Float_t Jet0SDmassCorrL23Dn                       ;     
      // Float_t Jet0SDmassCorrL23Smear                    ;    
      // Float_t Jet0SDmassCorrL23SmearUp                  ;    
      // Float_t Jet0SDmassCorrL23SmearDn                  ;  
      Float_t Jet0SDmassSubjetCorrL123                  ;    
      // Float_t Jet0SDmassCorrL123Up                      ;    
      // Float_t Jet0SDmassCorrL123Dn                      ;     
      Float_t Jet0SDptRaw                               ;    
      // Float_t Jet0SDptCorrL23                           ;    
      // Float_t Jet0SDptCorrL23Up                         ;    
      // Float_t Jet0SDptCorrL23Dn                         ;    
      // Float_t Jet0SDptCorrL123                          ;    
      // Float_t Jet0SDptCorrL123Up                        ;    
      // Float_t Jet0SDptCorrL123Dn                        ;    
      // Float_t Jet0SDptCorrL23Smear                      ;    
      // Float_t Jet0SDptCorrL23SmearUp                    ;    
      // Float_t Jet0SDptCorrL23SmearDn                    ;    
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
      Float_t Jet0SDsubjet0matchedgenjetpt              ;

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
      Float_t Jet0SDsubjet1matchedgenjetpt              ;
      Float_t Jet0SDsubjet1tau1                         ;
      Float_t Jet0SDsubjet1tau2                         ;
      Float_t Jet0SDsubjet1tau3                         ;

      // Float_t Jet0PuppiP                                ;
      Float_t Jet0PuppiPtRaw                            ;
      Float_t Jet0PuppiEtaRaw                           ;
      Float_t Jet0PuppiPhiRaw                           ;
      Float_t Jet0PuppiMassRaw                          ;
      Float_t Jet0PuppiArea                             ;

      Float_t Jet0PuppiSDmassRaw                        ;
      Float_t Jet0PuppiSDmassSubjetCorr                 ;
      // Float_t Jet0PuppiSDmassSubjetCorrUp                     ;
      // Float_t Jet0PuppiSDmassSubjetCorrDn                     ;
      // Float_t Jet0PuppiSDmassSubjetCorrL23Smear               ;
      // Float_t Jet0PuppiSDmassSubjetCorrL23SmearUp             ;
      // Float_t Jet0PuppiSDmassSubjetCorrL23SmearDn             ;
     
      // Float_t Jet0PuppiSDmassUserFloat   ;  
      Float_t Jet0PuppiMassPruned        ;  
      Float_t Jet0PuppiMassTrimmed       ;  

      Float_t Jet0PuppiSDptRaw                             ;
      // Float_t Jet0PuppiSDptSubjetCorr                         ;
      // Float_t Jet0PuppiSDptSubjetCorrUp                       ;
      // Float_t Jet0PuppiSDptSubjetCorrDn                       ;
      // Float_t Jet0PuppiSDptSubjetCorrL23Smear                 ;
      // Float_t Jet0PuppiSDptSubjetCorrL23SmearUp               ;
      // Float_t Jet0PuppiSDptSubjetCorrL23SmearDn               ;
      Float_t Jet0PuppiSDetaRaw                            ;
      Float_t Jet0PuppiSDphiRaw                            ;

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
      Float_t Jet0PuppiSDsubjet0matchedgenjetpt         ;
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
      Float_t Jet0PuppiSDsubjet1matchedgenjetpt         ;
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
      // Float_t Jet0EtaScaleFactor                        ;
      // Float_t Jet0PhiScaleFactor                        ;
      // Float_t Jet0MatchedGenJetDR                       ;
      Float_t Jet0MatchedGenJetPt                       ;
      Float_t Jet0MatchedGenJetMass                     ;
      Float_t Jet0PuppiMatchedGenJetPt                  ;
      Float_t Jet0PuppiMatchedGenJetMass                ;

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


      Int_t Jet0NsubjetsSD ;
      Int_t Jet0NsubjetsSDPuppi ;
      Int_t Jet1NsubjetsSD ;
      Int_t Jet1NsubjetsSDPuppi ;

      Float_t Jet1PtRaw                                 ;
      Float_t Jet1EtaRaw                                ;
      Float_t Jet1PhiRaw                                ;
      Float_t Jet1MassRaw                               ;
      // Float_t Jet1P                                     ;
      // Float_t Jet1Pt                                    ;
      // Float_t Jet1Eta                                   ;
      // Float_t Jet1Phi                                   ;
      // Float_t Jet1Rap                                   ;
      // Float_t Jet1Energy                                ;
      // Float_t Jet1Mass                                  ;
      Float_t Jet1Area                                  ;
      Float_t Jet1SDmass                                ;
      Float_t Jet1SDmassRaw                             ;
      Float_t Jet1SDmassSubjetCorrL23                         ;
      // Float_t Jet1SDmassCorrL23Up                       ;
      // Float_t Jet1SDmassCorrL23Dn                       ;
      Float_t Jet1SDmassSubjetCorrL123                        ;
      // Float_t Jet1SDmassCorrL123Up                      ;
      // Float_t Jet1SDmassCorrL123Dn                      ;
      // Float_t Jet1SDmassCorrL23Smear                    ;
      // Float_t Jet1SDmassCorrL23SmearUp                  ;
      // Float_t Jet1SDmassCorrL23SmearDn                  ;
      Float_t Jet1SDptRaw                               ;
      // Float_t Jet1SDptCorrL23                           ;
      // Float_t Jet1SDptCorrL23Up                         ;
      // Float_t Jet1SDptCorrL23Dn                         ;
      // Float_t Jet1SDptCorrL123                          ;
      // Float_t Jet1SDptCorrL123Up                        ;
      // Float_t Jet1SDptCorrL123Dn                        ;
      // Float_t Jet1SDptCorrL23Smear                      ;
      // Float_t Jet1SDptCorrL23SmearUp                    ;
      // Float_t Jet1SDptCorrL23SmearDn                    ;
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
      Float_t Jet1SDsubjet0matchedgenjetpt              ;
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
      Float_t Jet1SDsubjet1matchedgenjetpt              ;
      Float_t Jet1SDsubjet1tau1                         ;
      Float_t Jet1SDsubjet1tau2                         ;
      Float_t Jet1SDsubjet1tau3                         ;
      // Float_t Jet1PuppiP                                ;
      Float_t Jet1PuppiPtRaw                               ;
      Float_t Jet1PuppiEtaRaw                              ;
      Float_t Jet1PuppiPhiRaw                              ;
      Float_t Jet1PuppiMassRaw                             ;
      Float_t Jet1PuppiArea                             ;

      // Float_t Jet1PuppiSDmassUserFloat   ;  
      Float_t Jet1PuppiMassPruned        ;  
      Float_t Jet1PuppiMassTrimmed       ;  


      Float_t Jet1PuppiSDmassRaw                           ;
      Float_t Jet1PuppiSDmassSubjetCorr                       ;
      // Float_t Jet1PuppiSDmassSubjetCorrUp                     ;
      // Float_t Jet1PuppiSDmassSubjetCorrDn                     ;
      // Float_t Jet1PuppiSDmassSubjetCorrL23Smear               ;
      // Float_t Jet1PuppiSDmassSubjetCorrL23SmearUp             ;
      // Float_t Jet1PuppiSDmassSubjetCorrL23SmearDn             ;
      Float_t Jet1PuppiSDptRaw                             ;
      // Float_t Jet1PuppiSDptSubjetCorr                         ;
      // Float_t Jet1PuppiSDptSubjetCorrUp                       ;
      // Float_t Jet1PuppiSDptSubjetCorrDn                       ;
      // Float_t Jet1PuppiSDptSubjetCorrL23Smear                 ;
      // Float_t Jet1PuppiSDptSubjetCorrL23SmearUp               ;
      // Float_t Jet1PuppiSDptSubjetCorrL23SmearDn               ;
      Float_t Jet1PuppiSDetaRaw                            ;
      Float_t Jet1PuppiSDphiRaw                            ;

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
      Float_t Jet1PuppiSDsubjet0matchedgenjetpt              ;
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
      Float_t Jet1PuppiSDsubjet1matchedgenjetpt              ;
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
      // Float_t Jet1EtaScaleFactor                        ;
      // Float_t Jet1PhiScaleFactor                        ;
      // Float_t Jet1MatchedGenJetDR                       ;
      Float_t Jet1MatchedGenJetPt                       ;
      Float_t Jet1MatchedGenJetMass                     ;
      Float_t Jet1PuppiMatchedGenJetPt                       ;
      Float_t Jet1PuppiMatchedGenJetMass                     ;

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

      Float_t NeighborJet_Jet0_pt                       ;   
      Float_t NeighborJet_Jet0_eta                      ;   
      Float_t NeighborJet_Jet0_phi                      ;   
      Float_t NeighborJet_Jet0_m                        ;   
      Float_t NeighborJet_Jet0_bdisc                    ;   
      Float_t NeighborJet_Jet1_pt                       ;   
      Float_t NeighborJet_Jet1_eta                      ;   
      Float_t NeighborJet_Jet1_phi                      ;   
      Float_t NeighborJet_Jet1_m                        ;   
      Float_t NeighborJet_Jet1_bdisc                    ;   

      // Float_t AllHadMETpx                               ;           
      // Float_t AllHadMETpy                               ;           
      Float_t AllHadMETpt                               ;           
      Float_t AllHadMETphi                              ;           
      Float_t AllHadMETsumET                            ;           
      Float_t AllHadNvtx                                ;           
      Float_t AllHadNvtxGood                            ;           
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
      Int_t   CountLep                                  ;         
      Float_t GenTTmass                                 ;           
      Int_t   GenCountHadTop                            ;           
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
      Int_t   AllHadRunNum                               ;           
      Int_t   AllHadLumiBlock                            ;           
      Int_t   AllHadEventNum                             ;    



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
      // std::vector<std::string> *SemiLeptTrigNames     = new std::vector<std::string>;
      std::vector<int> *SemiLeptTrigPrescales = new std::vector<int>;
      std::vector<bool> *SemiLeptTrigPass    = new std::vector<bool>;

      // std::vector<float> *SemiLeptAK4pt      = new std::vector<float>;
      // std::vector<float> *SemiLeptAK4eta     = new std::vector<float>;
      // std::vector<float> *SemiLeptAK4phi     = new std::vector<float>;
      // std::vector<float> *SemiLeptAK4m       = new std::vector<float>;
      // std::vector<float> *SemiLeptAK4bdisc   = new std::vector<float>;

      //Chad
      std::vector<float> *v_AK8PuppiPt       = new std::vector<float>;
      std::vector<float> *v_AK8PuppiEta      = new std::vector<float>;
      std::vector<float> *v_AK8PuppiPhi      = new std::vector<float>;
      std::vector<float> *v_AK8PuppiM        = new std::vector<float>;
      std::vector<float> *v_AK8PuppiArea     = new std::vector<float>;

      std::vector<float> *v_AK8PuppiSdPt       = new std::vector<float>;
      std::vector<float> *v_AK8PuppiSdEta      = new std::vector<float>;
      std::vector<float> *v_AK8PuppiSdPhi      = new std::vector<float>;
      std::vector<float> *v_AK8PuppiSdM        = new std::vector<float>;
      std::vector<float> *v_AK8PuppiSdCorr     = new std::vector<float>;

      std::vector<float> *v_photonPt               = new std::vector<float>;
      std::vector<float> *v_photonSupClustEta      = new std::vector<float>;
      std::vector<float> *v_photonSigIEtaIEta      = new std::vector<float>;
      std::vector<float> *v_photonFullSigIEtaIEta  = new std::vector<float>;

      std::string SemiLeptTrigAcceptBits;

      Float_t JetPtRaw                               ;      
      Float_t JetEtaRaw                              ;
      Float_t JetPhiRaw                              ;
      Float_t JetMassRaw                             ;
      // Float_t JetP                                   ;
      // Float_t JetPt                                  ;
      // Float_t JetEta                                 ;
      // Float_t JetPhi                                 ;
      // Float_t JetRap                                 ;
      // Float_t JetEnergy                              ;
      // Float_t JetMass                                ;
      Float_t JetArea                                ;
      // Float_t JetSDmass                              ;
      Float_t JetSDmassRaw                           ;
      Float_t JetSDmassSubjetCorrL23                       ;
      // Float_t JetSDmassCorrL23Up                     ;
      // Float_t JetSDmassCorrL23Dn                     ;
      Float_t JetSDmassSubjetCorrL123                      ;
      // Float_t JetSDmassCorrL123Up                    ;
      // Float_t JetSDmassCorrL123Dn                    ;
      // Float_t JetSDmassCorrL23Smear                  ;
      // Float_t JetSDmassCorrL23SmearUp                ;
      // Float_t JetSDmassCorrL23SmearDn                ;
      Float_t JetSDptRaw                             ;
      // Float_t JetSDptCorrL23                         ;
      // Float_t JetSDptCorrL23Up                       ;
      // Float_t JetSDptCorrL23Dn                       ;
      // Float_t JetSDptCorrL123                        ;
      // Float_t JetSDptCorrL123Up                      ;
      // Float_t JetSDptCorrL123Dn                      ;
      // Float_t JetSDptCorrL23Smear                    ;
      // Float_t JetSDptCorrL23SmearUp                  ;
      // Float_t JetSDptCorrL23SmearDn                  ;
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
      Float_t JetSDsubjet0matchedgenjetpt                 ;
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
      Float_t JetSDsubjet1matchedgenjetpt                 ;
      Float_t JetSDsubjet1tau1                       ;
      Float_t JetSDsubjet1tau2                       ;
      Float_t JetSDsubjet1tau3                       ;
      // Float_t JetPuppiP                              ;
      Float_t JetPuppiPtRaw                             ;
      Float_t JetPuppiEtaRaw                            ;
      Float_t JetPuppiPhiRaw                            ;
      Float_t JetPuppiMassRaw                           ;
      Float_t JetPuppiArea                           ;
      Float_t JetPuppiSDmassRaw                         ;
      Float_t JetPuppiSDmassSubjetCorr                     ;
      // Float_t JetPuppiSDmassSubjetCorrUp                   ;
      // Float_t JetPuppiSDmassSubjetCorrDn                   ;
      // Float_t JetPuppiSDmassSubjetCorrL23Smear             ;
      // Float_t JetPuppiSDmassSubjetCorrL23SmearUp           ;
      // Float_t JetPuppiSDmassSubjetCorrL23SmearDn           ;
      Float_t JetPuppiSDptRaw                           ;
      // Float_t JetPuppiSDptSubjetCorr                       ;
      // Float_t JetPuppiSDptSubjetCorrUp                     ;
      // Float_t JetPuppiSDptSubjetCorrDn                     ;
      // Float_t JetPuppiSDptSubjetCorrL23Smear               ;
      // Float_t JetPuppiSDptSubjetCorrL23SmearUp             ;
      // Float_t JetPuppiSDptSubjetCorrL23SmearDn             ;
      Float_t JetPuppiSDetaRaw                          ;
      Float_t JetPuppiSDphiRaw                          ;
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
      Float_t JetPuppiSDsubjet0matchedgenjetpt            ;
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
      Float_t JetPuppiSDsubjet1matchedgenjetpt            ;
      Float_t JetPuppiSDsubjet1tau1                  ;
      Float_t JetPuppiSDsubjet1tau2                  ;
      Float_t JetPuppiSDsubjet1tau3                  ;

      // Float_t JetPuppiSDmassUserFloat   ;  
      Float_t JetPuppiMassPruned        ;  
      Float_t JetPuppiMassTrimmed       ;  


      Int_t JetNsubjetsSD ;
      Int_t JetNsubjetsSDPuppi ;

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
      // Float_t JetEtaScaleFactor                      ;
      // Float_t JetPhiScaleFactor                      ;
      // // Float_t JetMatchedGenJetDR                     ;
      Float_t JetMatchedGenJetPt                     ;
      Float_t JetMatchedGenJetMass                   ;
      Float_t JetPuppiMatchedGenJetPt                     ;
      Float_t JetPuppiMatchedGenJetMass                   ;

      Int_t   JetGenMatched_TopHadronic              ;
      Float_t JetGenMatched_TopPt                    ;
      Float_t JetGenMatched_TopEta                   ;
      Float_t JetGenMatched_TopPhi                   ;
      Float_t JetGenMatched_TopMass                  ;
      Float_t JetGenMatched_bPt                      ;
      Float_t JetGenMatched_WPt                      ;
      Float_t JetGenMatched_WEta                     ;
      Float_t JetGenMatched_WPhi                     ;
      Float_t JetGenMatched_WMass                    ;
      Float_t JetGenMatched_ZPt                      ;
      Float_t JetGenMatched_ZEta                     ;
      Float_t JetGenMatched_ZPhi                     ;
      Float_t JetGenMatched_ZMass                    ;
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
      Float_t SemiLeptMETgenMET                      ;
      Float_t SemiLeptMETuncorPt                     ;

      Float_t SemiLeptMETshiftedPtJetEnUp            ;
      Float_t SemiLeptMETshiftedPtJetEnDn            ;
      Float_t SemiLeptMETshiftedPtElEnUp             ;
      Float_t SemiLeptMETshiftedPtElEnDn             ;
      Float_t SemiLeptMETshiftedPtMuEnUp             ;
      Float_t SemiLeptMETshiftedPtMuEnDn             ;
      Float_t SemiLeptMETshiftedPtJetResUp           ;
      Float_t SemiLeptMETshiftedPtJetResDn           ;
      Float_t SemiLeptMETshiftedPtUnclEnUp           ;
      Float_t SemiLeptMETshiftedPtUnclEnDn           ;


      Float_t SemiLeptNvtx                           ;
      Float_t SemiLeptNvtxGood                       ;
      Float_t SemiLeptNPUtrue                        ;
      Float_t SemiLeptRho                            ;
      Float_t SemiLeptEventWeight                    ;
      Float_t SemiLeptPUweight                       ;
      Float_t SemiLeptPUweight_MBup                  ;
      Float_t SemiLeptPUweight_MBdn                  ;


      Float_t SemiLeptGenTTmass                      ;
      Int_t   SemiLeptGenCountHadTop                 ;

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
      Int_t   SemiLeptRunNum                         ;
      Int_t   SemiLeptLumiBlock                      ;
      Int_t   SemiLeptEventNum                       ;
      Int_t   SemiLeptPassMETFilters                 ;       
        
      Float_t AK4_dRminLep_Pt                             ;
      Float_t AK4_dRminLep_Eta                            ;
      Float_t AK4_dRminLep_Phi                            ;
      Float_t AK4_dRminLep_Mass                           ;
      Float_t AK4_dRminLep_Bdisc                          ;
      Float_t AK4_dRminLep_dRlep                          ;
      Float_t AK4_dRminLep_dRak8                          ;
      Float_t AK4_dRminLep_PtSmear                        ;
      Float_t AK4_dRminLep_PtSmearUp                      ;
      Float_t AK4_dRminLep_PtSmearDn                      ;
      Float_t AK4_dRminLep_PtUncorr                       ;
      Float_t AK4_dRminLep_Corr                           ;
      Float_t AK4_dRminLep_CorrUp                         ;
      Float_t AK4_dRminLep_CorrDn                         ;
       

      // Float_t AK4BtagdRminPt                         ;
      // Float_t AK4BtagdRminBdisc                      ;
      // Float_t AK4BtagdRminLep                        ;
      Int_t   LepHemiContainsAK4BtagLoose            ;
      Int_t   LepHemiContainsAK4BtagMedium           ;
      Int_t   LepHemiContainsAK4BtagTight            ;


      Float_t LeptonPhi0                              ;
      Float_t LeptonPt0                               ;
      Float_t LeptonEta0                              ;
      Float_t LeptonMass0                             ;
      Float_t LeptonPhi1                              ;
      Float_t LeptonPt1                               ;
      Float_t LeptonEta1                              ;
      Float_t LeptonMass1                             ;
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

      Int_t Electron_iso_passHLTpre                  ;
      Int_t Electron_iso_passLoose                   ;
      Int_t Electron_iso_passMedium                  ;
      Int_t Electron_iso_passTight                   ;
      Int_t Electron_iso_passHEEP                    ;
      Int_t Electron_noiso_passLoose                 ;
      Int_t Electron_noiso_passMedium                ;
      Int_t Electron_noiso_passTight                 ;
      Int_t Electron_noiso_passHEEP                  ;


};

//
// constructors and destructor
//
B2GTTbarTreeMaker::B2GTTbarTreeMaker(const edm::ParameterSet& iConfig):
    ak4jetToken_(consumes<pat::JetCollection>(    edm::InputTag("slimmedJets"))),
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
    electronToken_(consumes<edm::View<pat::Electron>>(edm::InputTag("slimmedElectrons"))), //Collection
    photonToken_(consumes<edm::View<pat::Photon>>(edm::InputTag("slimmedPhotons"))), //Collection
    metToken_(consumes<pat::METCollection>(edm::InputTag("slimmedMETs","","Ana"))),
    pileupInfoToken_(consumes<std::vector<PileupSummaryInfo>>(edm::InputTag("slimmedAddPileupInfo"))),
    lheSrc_(consumes<LHEEventProduct>(iConfig.getParameter<edm::InputTag>("lheSrc"))),
    pdfToken_(consumes<GenEventInfoProduct>(edm::InputTag("generator"))),
    beamSpotToken_(consumes<reco::BeamSpot>(edm::InputTag("offlineBeamSpot"))),
    conversionsToken_(consumes<reco::ConversionCollection>(edm::InputTag("reducedEgamma:reducedConversions"))),
    eleIdFullInfoMapToken_HLTpre_  (consumes<edm::ValueMap<vid::CutFlowResult> >(iConfig.getParameter<edm::InputTag>("eleIdFullInfoMapToken_HLTpre"))),
    eleIdFullInfoMapToken_Loose_   (consumes<edm::ValueMap<vid::CutFlowResult> >(iConfig.getParameter<edm::InputTag>("eleIdFullInfoMapToken_Loose"))),
    eleIdFullInfoMapToken_Medium_  (consumes<edm::ValueMap<vid::CutFlowResult> >(iConfig.getParameter<edm::InputTag>("eleIdFullInfoMapToken_Medium"))),
    eleIdFullInfoMapToken_Tight_   (consumes<edm::ValueMap<vid::CutFlowResult> >(iConfig.getParameter<edm::InputTag>("eleIdFullInfoMapToken_Tight"))),
    eleIdFullInfoMapToken_HEEP_    (consumes<edm::ValueMap<vid::CutFlowResult> >(iConfig.getParameter<edm::InputTag>("eleIdFullInfoMapToken_HEEP"))),
    verbose_         (iConfig.getParameter<bool>  ("verbose")),
    verboseGen_      (iConfig.getParameter<bool>  ("verboseGen")),
    useToolbox_      (iConfig.getParameter<bool>  ("useToolbox")),
    runGenLoop_      (iConfig.getParameter<bool>  ("runGenLoop")),
    runAllHadTree_   (iConfig.getParameter<bool>  ("runAllHadTree")),
    runSemiLeptTree_ (iConfig.getParameter<bool>  ("runSemiLeptTree")),
    isZprime_        (iConfig.getParameter<bool>  ("isZprime")),
    isttbar_         (iConfig.getParameter<bool>  ("isttbar")),
    isRSG_           (iConfig.getParameter<bool>  ("isRSG")),
    isRun2016F_      (iConfig.getParameter<bool>  ("isRun2016F")),
    jecPayloadsAK4chs_ (iConfig.getParameter<std::vector<std::string> >  ("jecPayloadsAK4chs")),
    jecPayloadsAK8chs_ (iConfig.getParameter<std::vector<std::string> >  ("jecPayloadsAK8chs")),
    jecPayloadsAK4pup_ (iConfig.getParameter<std::vector<std::string> >  ("jecPayloadsAK4pup")),
    jecPayloadsAK8pup_ (iConfig.getParameter<std::vector<std::string> >  ("jecPayloadsAK8pup")),
    jecPayloadsAK4chsSecondary_ (iConfig.getParameter<std::vector<std::string> >  ("jecPayloadsAK4chsSecondary")),
    jecPayloadsAK8chsSecondary_ (iConfig.getParameter<std::vector<std::string> >  ("jecPayloadsAK8chsSecondary")),
    jecPayloadsAK4pupSecondary_ (iConfig.getParameter<std::vector<std::string> >  ("jecPayloadsAK4pupSecondary")),
    jecPayloadsAK8pupSecondary_ (iConfig.getParameter<std::vector<std::string> >  ("jecPayloadsAK8pupSecondary")),
    jertextAK4_ (iConfig.getParameter<std::string>  ("jertextAK4")),
    jertextAK8_ (iConfig.getParameter<std::string>  ("jertextAK8")),
    jerSFtext_  (iConfig.getParameter<std::string>  ("jerSFtext"))
{
  std::cout<<"B2GTTbarTreeMaker::B2GTTbarTreeMaker"<<std::endl;

  //RS gluon PDF weights
  LHAPDF::initPDFSet(1, "NNPDF30_lo_as_0130");

  usesResource("TFileService");

  edm::Service<TFileService> fs;

  h_cutflow_allhad                   =  fs->make<TH1D>("h_cutflow_allhad"                  ,"",20,0,20);
  h_cutflow_semilept                 =  fs->make<TH1D>("h_cutflow_semilept"                ,"",20,0,20);
  // h_ak8puppi_softDropMass            =  fs->make<TH1D>("h_ak8puppi_softDropMass"           ,"",200,0,400);
  // h_ak8chs_softDropMass              =  fs->make<TH1D>("h_ak8chs_softDropMass"             ,"",200,0,400);
  // h_ak8chs_softDropMass_reweighted   =  fs->make<TH1D>("h_ak8chs_softDropMass_reweighted"  ,"",200,0,400);
  // h_ak8chs_pt                        =  fs->make<TH1D>("h_ak8chs_pt"                       ,"",200,0,4000);
  // h_ak8chs_pt_reweighted             =  fs->make<TH1D>("h_ak8chs_pt_reweighted"            ,"",200,0,4000);
  h_NtrueIntPU                       =  fs->make<TH1D>("h_NtrueIntPU"                      ,"",200,0,200);
  h_NPV                              =  fs->make<TH1D>("h_NPV"                             ,"",200,0,200);
  h_NPVreweighted                    =  fs->make<TH1D>("h_NPVreweighted"                   ,"",200,0,200);
  h_NPVgood                          =  fs->make<TH1D>("h_NPVgood"                         ,"",200,0,200);
  h_NPVgoodreweighted                =  fs->make<TH1D>("h_NPVgoodreweighted"               ,"",200,0,200);

  // HT 
  trigsToRun.push_back("HLT_PFHT300_v");
  trigsToRun.push_back("HLT_PFHT350_v");
  trigsToRun.push_back("HLT_PFHT400_v");
  trigsToRun.push_back("HLT_PFHT475_v");
  trigsToRun.push_back("HLT_PFHT600_v");
  trigsToRun.push_back("HLT_PFHT650_v");
  trigsToRun.push_back("HLT_PFHT800_v");
  trigsToRun.push_back("HLT_PFHT900_v");
  trigsToRun.push_back("HLT_PFHT650_WideJetMJJ900"); //HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v6
  trigsToRun.push_back("HLT_PFHT650_WideJetMJJ950"); //HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v6

  // Single jet
  trigsToRun.push_back("HLT_CaloJet500_NoJetID_v");
  trigsToRun.push_back("HLT_PFJet320_v");
  trigsToRun.push_back("HLT_PFJet400_v");
  trigsToRun.push_back("HLT_PFJet450_v");
  trigsToRun.push_back("HLT_PFJet500_v");
  trigsToRun.push_back("HLT_AK8PFJet450_v");
  trigsToRun.push_back("HLT_AK8PFJet500_v");

  // Substructure
  trigsToRun.push_back("HLT_AK8PFJet360_TrimMass30_v");
  trigsToRun.push_back("HLT_AK8PFHT650_TrimR0p1PT0p03Mass50_v");
  trigsToRun.push_back("HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v");

  // Substructure + b-tag
  trigsToRun.push_back("HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20_v");
  trigsToRun.push_back("HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_v");

  // Muon
  trigsToRun.push_back("HLT_Mu45_eta2p1_v");
  trigsToRun.push_back("HLT_Mu50_v");
  trigsToRun.push_back("HLT_Mu55_v");
  trigsToRun.push_back("HLT_TkMu50_v");
  trigsToRun.push_back("HLT_IsoMu22_eta2p1_v");
  trigsToRun.push_back("HLT_IsoMu24_v");
  trigsToRun.push_back("HLT_IsoMu27_v");

  // Muon + jet
  trigsToRun.push_back("HLT_Mu30_eta2p1_PFJet150_PFJet50_v");
  trigsToRun.push_back("HLT_Mu40_eta2p1_PFJet200_PFJet50_v");

  // Electron
  trigsToRun.push_back("HLT_Ele32_eta2p1_WPTight_Gsf_v");
  trigsToRun.push_back("HLT_Ele35_WPLoose_Gsf_v");
  trigsToRun.push_back("HLT_Ele105_CaloIdVT_GsfTrkIdT_v");
  trigsToRun.push_back("HLT_Ele115_CaloIdVT_GsfTrkIdT_v");

  // Electron + jet
  trigsToRun.push_back("HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50_v");
  trigsToRun.push_back("HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet140_v");
  trigsToRun.push_back("HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165_v");




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


  // TreeAllHad->Branch("vAK4pt"      , "vector<float>", &vAK4pt     );
  // TreeAllHad->Branch("vAK4eta"     , "vector<float>", &vAK4eta    );
  // TreeAllHad->Branch("vAK4phi"     , "vector<float>", &vAK4phi    );
  // TreeAllHad->Branch("vAK4m"       , "vector<float>", &vAK4m      );
  // TreeAllHad->Branch("vAK4bdisc"   , "vector<float>", &vAK4bdisc  );

  // TreeAllHad->Branch("AllHadTrigNames"       , "vector<std::string>", &AllHadTrigNames);
  TreeAllHad->Branch("AllHadTrigPrescales"   , "vector<int>", &AllHadTrigPrescales);
  TreeAllHad->Branch("AllHadTrigPass"        , "vector<bool>", &AllHadTrigPass);
  TreeAllHad->Branch("AllHadTrigAcceptBits"  , &AllHadTrigAcceptBits);

  TreeAllHad->Branch("PassMETFilters"                        , & PassMETFilters                     ,    "PassMETFilters/I"                          );                                  
  TreeAllHad->Branch("Jet0PtRaw"                             , & Jet0PtRaw                          ,    "Jet0PtRaw/F"                               );                                  
  TreeAllHad->Branch("Jet0EtaRaw"                            , & Jet0EtaRaw                         ,    "Jet0EtaRaw/F"                              );                                   
  TreeAllHad->Branch("Jet0PhiRaw"                            , & Jet0PhiRaw                         ,    "Jet0PhiRaw/F"                              );                                   
  TreeAllHad->Branch("Jet0MassRaw"                           , & Jet0MassRaw                        ,    "Jet0MassRaw/F"                             );                                    
  // TreeAllHad->Branch("Jet0P"                                 , & Jet0P                              ,    "Jet0P/F"                                   );                              
  // TreeAllHad->Branch("Jet0Pt"                                , & Jet0Pt                             ,    "Jet0Pt/F"                                  );                               
  // TreeAllHad->Branch("Jet0Eta"                               , & Jet0Eta                            ,    "Jet0Eta/F"                                 );                                
  // TreeAllHad->Branch("Jet0Phi"                               , & Jet0Phi                            ,    "Jet0Phi/F"                                 );                                
  // TreeAllHad->Branch("Jet0Rap"                               , & Jet0Rap                            ,    "Jet0Rap/F"                                 );                                
  // TreeAllHad->Branch("Jet0Energy"                            , & Jet0Energy                         ,    "Jet0Energy/F"                              );                                   
  // TreeAllHad->Branch("Jet0Mass"                              , & Jet0Mass                           ,    "Jet0Mass/F"                                );                                 
  // TreeAllHad->Branch("Jet0Area"                              , & Jet0Area                           ,    "Jet0Area/F"                                );                                 
  // TreeAllHad->Branch("Jet0SDmass"                            , & Jet0SDmass                         ,    "Jet0SDmass/F"                              );                                         
  TreeAllHad->Branch("Jet0SDmassRaw"                         , & Jet0SDmassRaw                      ,    "Jet0SDmassRaw/F"                           );                                               
  TreeAllHad->Branch("Jet0SDmassSubjetCorrL23"                     , & Jet0SDmassSubjetCorrL23                  ,    "Jet0SDmassSubjetCorrL23/F"                       );                                                    
  // TreeAllHad->Branch("Jet0SDmassSubjetCorrL23Up"                   , & Jet0SDmassSubjetCorrL23Up                ,    "Jet0SDmassSubjetCorrL23Up/F"                     );                                                      
  // TreeAllHad->Branch("Jet0SDmassSubjetCorrL23Dn"                   , & Jet0SDmassSubjetCorrL23Dn                ,    "Jet0SDmassSubjetCorrL23Dn/F"                     );                                                      
  TreeAllHad->Branch("Jet0SDmassSubjetCorrL123"                    , & Jet0SDmassSubjetCorrL123                 ,    "Jet0SDmassSubjetCorrL123/F"                      );                                                      
  // TreeAllHad->Branch("Jet0SDmassCorrL123Up"                  , & Jet0SDmassCorrL123Up               ,    "Jet0SDmassCorrL123Up/F"                    );                                                        
  // TreeAllHad->Branch("Jet0SDmassCorrL123Dn"                  , & Jet0SDmassCorrL123Dn               ,    "Jet0SDmassCorrL123Dn/F"                    );                                                        
  // TreeAllHad->Branch("Jet0SDmassCorrL23Smear"                , & Jet0SDmassCorrL23Smear             ,    "Jet0SDmassCorrL23Smear/F"                  );                                                     
  // TreeAllHad->Branch("Jet0SDmassCorrL23SmearUp"              , & Jet0SDmassCorrL23SmearUp           ,    "Jet0SDmassCorrL23SmearUp/F"                );                                                       
  // TreeAllHad->Branch("Jet0SDmassCorrL23SmearDn"              , & Jet0SDmassCorrL23SmearDn           ,    "Jet0SDmassCorrL23SmearDn/F"                );   
  TreeAllHad->Branch("Jet0SDptRaw"                           , & Jet0SDptRaw                        ,    "Jet0SDptRaw/F"                             );                                               
  // TreeAllHad->Branch("Jet0SDptCorrL23"                       , & Jet0SDptCorrL23                    ,    "Jet0SDptCorrL23/F"                         );                                                    
  // TreeAllHad->Branch("Jet0SDptCorrL23Up"                     , & Jet0SDptCorrL23Up                  ,    "Jet0SDptCorrL23Up/F"                       );                                                      
  // TreeAllHad->Branch("Jet0SDptCorrL23Dn"                     , & Jet0SDptCorrL23Dn                  ,    "Jet0SDptCorrL23Dn/F"                       );                                                      
  // TreeAllHad->Branch("Jet0SDptCorrL123"                      , & Jet0SDptCorrL123                   ,    "Jet0SDptCorrL123/F"                        );                                                      
  // TreeAllHad->Branch("Jet0SDptCorrL123Up"                    , & Jet0SDptCorrL123Up                 ,    "Jet0SDptCorrL123Up/F"                      );                                                        
  // TreeAllHad->Branch("Jet0SDptCorrL123Dn"                    , & Jet0SDptCorrL123Dn                 ,    "Jet0SDptCorrL123Dn/F"                      );                                                        
  // TreeAllHad->Branch("Jet0SDptCorrL23Smear"                  , & Jet0SDptCorrL23Smear               ,    "Jet0SDptCorrL23Smear/F"                    );                                                     
  // TreeAllHad->Branch("Jet0SDptCorrL23SmearUp"                , & Jet0SDptCorrL23SmearUp             ,    "Jet0SDptCorrL23SmearUp/F"                  );                                                       
  // TreeAllHad->Branch("Jet0SDptCorrL23SmearDn"                , & Jet0SDptCorrL23SmearDn             ,    "Jet0SDptCorrL23SmearDn/F"                  );                                                     
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
  TreeAllHad->Branch("Jet0SDsubjet0matchedgenjetpt"          , & Jet0SDsubjet0matchedgenjetpt       ,    "Jet0SDsubjet0matchedgenjetpt/F"            ); 
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
  TreeAllHad->Branch("Jet0SDsubjet1matchedgenjetpt"          , & Jet0SDsubjet1matchedgenjetpt       ,    "Jet0SDsubjet1matchedgenjetpt/F"            ); 
  TreeAllHad->Branch("Jet0SDsubjet1tau1"                     , & Jet0SDsubjet1tau1                  ,    "Jet0SDsubjet1tau1/F"                       );
  TreeAllHad->Branch("Jet0SDsubjet1tau2"                     , & Jet0SDsubjet1tau2                  ,    "Jet0SDsubjet1tau2/F"                       );
  TreeAllHad->Branch("Jet0SDsubjet1tau3"                     , & Jet0SDsubjet1tau3                  ,    "Jet0SDsubjet1tau3/F"                       );  
  TreeAllHad->Branch("Jet0SDsubjet1bdisc"                    , & Jet0SDsubjet1bdisc                 ,    "Jet0SDsubjet1bdisc/F"                      );                                                                                    
  // TreeAllHad->Branch("Jet0PuppiP"                            , & Jet0PuppiP                         ,    "Jet0PuppiP/F"                              );                                    
  TreeAllHad->Branch("Jet0PuppiPtRaw"                           , & Jet0PuppiPtRaw                        ,    "Jet0PuppiPtRaw/F"                             );                                    
  TreeAllHad->Branch("Jet0PuppiEtaRaw"                          , & Jet0PuppiEtaRaw                       ,    "Jet0PuppiEtaRaw/F"                            );                                     
  TreeAllHad->Branch("Jet0PuppiPhiRaw"                          , & Jet0PuppiPhiRaw                       ,    "Jet0PuppiPhiRaw/F"                            );                                     
  TreeAllHad->Branch("Jet0PuppiMassRaw"                         , & Jet0PuppiMassRaw                      ,    "Jet0PuppiMassRaw/F"                           );                                      
  TreeAllHad->Branch("Jet0PuppiArea"                         , & Jet0PuppiArea                      ,    "Jet0PuppiArea/F"                           );                                      
  
  TreeAllHad->Branch("Jet0PuppiSDmassRaw"                       , & Jet0PuppiSDmassRaw                    ,   "Jet0PuppiSDmassRaw/F"                          );
  TreeAllHad->Branch("Jet0PuppiSDmassSubjetCorr"             , & Jet0PuppiSDmassSubjetCorr          ,   "Jet0PuppiSDmassSubjetCorr/F"                );
  // TreeAllHad->Branch("Jet0PuppiSDmassSubjetCorrUp"           , & Jet0PuppiSDmassSubjetCorrUp        ,   "Jet0PuppiSDmassSubjetCorrUp/F"              );
  // TreeAllHad->Branch("Jet0PuppiSDmassSubjetCorrDn"           , & Jet0PuppiSDmassSubjetCorrDn        ,   "Jet0PuppiSDmassSubjetCorrDn/F"              );
  // TreeAllHad->Branch("Jet0PuppiSDmassSubjetCorrL23Smear"           , & Jet0PuppiSDmassSubjetCorrL23Smear        ,   "Jet0PuppiSDmassSubjetCorrL23Smear/F"              );
  // TreeAllHad->Branch("Jet0PuppiSDmassSubjetCorrL23SmearUp"         , & Jet0PuppiSDmassSubjetCorrL23SmearUp      ,   "Jet0PuppiSDmassSubjetCorrL23SmearUp/F"            );
  // TreeAllHad->Branch("Jet0PuppiSDmassSubjetCorrL23SmearDn"         , & Jet0PuppiSDmassSubjetCorrL23SmearDn      ,   "Jet0PuppiSDmassSubjetCorrL23SmearDn/F"            );
  

  // TreeAllHad->Branch("Jet0PuppiSDmassUserFloat"               , & Jet0PuppiSDmassUserFloat          ,   "Jet0PuppiSDmassUserFloat/F"                     );
  TreeAllHad->Branch("Jet0PuppiMassPruned"                    , & Jet0PuppiMassPruned               ,   "Jet0PuppiMassPruned/F"                          );
  TreeAllHad->Branch("Jet0PuppiMassTrimmed"                   , & Jet0PuppiMassTrimmed              ,   "Jet0PuppiMassTrimmed/F"                         );



  TreeAllHad->Branch("Jet0PuppiSDptRaw"                         , & Jet0PuppiSDptRaw                      ,   "Jet0PuppiSDptRaw/F"                            );
  // TreeAllHad->Branch("Jet0PuppiSDptSubjetCorr"               , & Jet0PuppiSDptSubjetCorr            ,   "Jet0PuppiSDptSubjetCorr/F"                  );
  // TreeAllHad->Branch("Jet0PuppiSDptSubjetCorrUp"             , & Jet0PuppiSDptSubjetCorrUp          ,   "Jet0PuppiSDptSubjetCorrUp/F"                );
  // TreeAllHad->Branch("Jet0PuppiSDptSubjetCorrDn"             , & Jet0PuppiSDptSubjetCorrDn          ,   "Jet0PuppiSDptSubjetCorrDn/F"                );
  // TreeAllHad->Branch("Jet0PuppiSDptSubjetCorrL23Smear"       , & Jet0PuppiSDptSubjetCorrL23Smear    ,   "Jet0PuppiSDptSubjetCorrL23Smear/F"          );
  // TreeAllHad->Branch("Jet0PuppiSDptSubjetCorrL23SmearUp"     , & Jet0PuppiSDptSubjetCorrL23SmearUp  ,   "Jet0PuppiSDptSubjetCorrL23SmearUp/F"        );
  // TreeAllHad->Branch("Jet0PuppiSDptSubjetCorrL23SmearDn"     , & Jet0PuppiSDptSubjetCorrL23SmearDn  ,   "Jet0PuppiSDptSubjetCorrL23SmearDn/F"        );
  TreeAllHad->Branch("Jet0PuppiSDetaRaw"                        , & Jet0PuppiSDetaRaw                     ,   "Jet0PuppiSDetaRaw/F"                           );
  TreeAllHad->Branch("Jet0PuppiSDphiRaw"                        , & Jet0PuppiSDphiRaw                     ,   "Jet0PuppiSDphiRaw/F"                           );
                                                           
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
  TreeAllHad->Branch("Jet0PuppiSDsubjet1matchedgenjetpt"     , & Jet0PuppiSDsubjet1matchedgenjetpt  ,    "Jet0PuppiSDsubjet1matchedgenjetpt/F"       );
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
  TreeAllHad->Branch("Jet0PuppiSDsubjet1matchedgenjetpt"     , & Jet1PuppiSDsubjet1matchedgenjetpt  ,    "Jet1PuppiSDsubjet1matchedgenjetpt/F"       );
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
  // TreeAllHad->Branch("Jet0EtaScaleFactor"                    , & Jet0EtaScaleFactor                 ,    "Jet0EtaScaleFactor/F"                      );                                           
  // TreeAllHad->Branch("Jet0PhiScaleFactor"                    , & Jet0PhiScaleFactor                 ,    "Jet0PhiScaleFactor/F"                      );                                           
  // TreeAllHad->Branch("Jet0MatchedGenJetDR"                   , & Jet0MatchedGenJetDR                ,    "Jet0MatchedGenJetDR/F"                     );                                            
  TreeAllHad->Branch("Jet0MatchedGenJetPt"                   , & Jet0MatchedGenJetPt                ,    "Jet0MatchedGenJetPt/F"                     );                                            
  TreeAllHad->Branch("Jet0MatchedGenJetMass"                 , & Jet0MatchedGenJetMass              ,    "Jet0MatchedGenJetMass/F"                   );  
  TreeAllHad->Branch("Jet0PuppiMatchedGenJetPt"                   , & Jet0PuppiMatchedGenJetPt                ,    "Jet0PuppiMatchedGenJetPt/F"                     );                                            
  TreeAllHad->Branch("Jet0PuppiMatchedGenJetMass"                 , & Jet0PuppiMatchedGenJetMass              ,    "Jet0PuppiMatchedGenJetMass/F"                   );  

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
  

  TreeAllHad->Branch("Jet0NsubjetsSD"        , & Jet0NsubjetsSD     ,    "Jet0NsubjetsSD/I"          );      
  TreeAllHad->Branch("Jet1NsubjetsSD"        , & Jet1NsubjetsSD     ,    "Jet1NsubjetsSD/I"          );      
  TreeAllHad->Branch("Jet0NsubjetsSDPuppi"        , & Jet0NsubjetsSDPuppi     ,    "Jet0NsubjetsSDPuppi/I"          );      
  TreeAllHad->Branch("Jet1NsubjetsSDPuppi"        , & Jet1NsubjetsSDPuppi     ,    "Jet1NsubjetsSDPuppi/I"          );      



  std::cout<<"Setup Jet0 in tree"<<std::endl;
  
  TreeAllHad->Branch("Jet1PtRaw"                             , & Jet1PtRaw                          ,    "Jet1PtRaw/F"                               );                                  
  TreeAllHad->Branch("Jet1EtaRaw"                            , & Jet1EtaRaw                         ,    "Jet1EtaRaw/F"                              );                                   
  TreeAllHad->Branch("Jet1PhiRaw"                            , & Jet1PhiRaw                         ,    "Jet1PhiRaw/F"                              );                                   
  TreeAllHad->Branch("Jet1MassRaw"                           , & Jet1MassRaw                        ,    "Jet1MassRaw/F"                             );                                    
  // TreeAllHad->Branch("Jet1P"                                 , & Jet1P                              ,    "Jet1P/F"                                   );                              
  // TreeAllHad->Branch("Jet1Pt"                                , & Jet1Pt                             ,    "Jet1Pt/F"                                  );                               
  // TreeAllHad->Branch("Jet1Eta"                               , & Jet1Eta                            ,    "Jet1Eta/F"                                 );                                
  // TreeAllHad->Branch("Jet1Phi"                               , & Jet1Phi                            ,    "Jet1Phi/F"                                 );                                
  // TreeAllHad->Branch("Jet1Rap"                               , & Jet1Rap                            ,    "Jet1Rap/F"                                 );                                
  // TreeAllHad->Branch("Jet1Energy"                            , & Jet1Energy                         ,    "Jet1Energy/F"                              );                                   
  // TreeAllHad->Branch("Jet1Mass"                              , & Jet1Mass                           ,    "Jet1Mass/F"                                );                                 
  TreeAllHad->Branch("Jet1Area"                              , & Jet1Area                           ,    "Jet1Area/F"                                );                                 
  TreeAllHad->Branch("Jet1SDmass"                            , & Jet1SDmass                         ,    "Jet1SDmass/F"                              );                                         
  TreeAllHad->Branch("Jet1SDmassRaw"                         , & Jet1SDmassRaw                      ,    "Jet1SDmassRaw/F"                           );                                               
  TreeAllHad->Branch("Jet1SDmassSubjetCorrL23"                     , & Jet1SDmassSubjetCorrL23                  ,    "Jet1SDmassSubjetCorrL23/F"                       );                                                    
  // TreeAllHad->Branch("Jet1SDmassSubjetCorrL23Up"                   , & Jet1SDmassSubjetCorrL23Up                ,    "Jet1SDmassSubjetCorrL23Up/F"                     );                                                      
  // TreeAllHad->Branch("Jet1SDmassSubjetCorrL23Dn"                   , & Jet1SDmassSubjetCorrL23Dn                ,    "Jet1SDmassSubjetCorrL23Dn/F"                     );                                                      
  TreeAllHad->Branch("Jet1SDmassSubjetCorrL123"                    , & Jet1SDmassSubjetCorrL123                 ,    "Jet1SDmassSubjetCorrL123/F"                      );                                                      
  // TreeAllHad->Branch("Jet1SDmassCorrL123Up"                  , & Jet1SDmassCorrL123Up               ,    "Jet1SDmassCorrL123Up/F"                    );                                                        
  // TreeAllHad->Branch("Jet1SDmassCorrL123Dn"                  , & Jet1SDmassCorrL123Dn               ,    "Jet1SDmassCorrL123Dn/F"                    );                                                        
  // TreeAllHad->Branch("Jet1SDmassCorrL23Smear"                , & Jet1SDmassCorrL23Smear             ,    "Jet1SDmassCorrL23Smear/F"                  );                                                     
  // TreeAllHad->Branch("Jet1SDmassCorrL23SmearUp"              , & Jet1SDmassCorrL23SmearUp           ,    "Jet1SDmassCorrL23SmearUp/F"                );                                                       
  // TreeAllHad->Branch("Jet1SDmassCorrL23SmearDn"              , & Jet1SDmassCorrL23SmearDn           ,    "Jet1SDmassCorrL23SmearDn/F"                );   
  TreeAllHad->Branch("Jet1SDptRaw"                           , & Jet1SDptRaw                        ,    "Jet1SDptRaw/F"                             );                                               
  // TreeAllHad->Branch("Jet1SDptCorrL23"                       , & Jet1SDptCorrL23                    ,    "Jet1SDptCorrL23/F"                         );                                                    
  // TreeAllHad->Branch("Jet1SDptCorrL23Up"                     , & Jet1SDptCorrL23Up                  ,    "Jet1SDptCorrL23Up/F"                       );                                                      
  // TreeAllHad->Branch("Jet1SDptCorrL23Dn"                     , & Jet1SDptCorrL23Dn                  ,    "Jet1SDptCorrL23Dn/F"                       );                                                      
  // TreeAllHad->Branch("Jet1SDptCorrL123"                      , & Jet1SDptCorrL123                   ,    "Jet1SDptCorrL123/F"                        );                                                      
  // TreeAllHad->Branch("Jet1SDptCorrL123Up"                    , & Jet1SDptCorrL123Up                 ,    "Jet1SDptCorrL123Up/F"                      );                                                        
  // TreeAllHad->Branch("Jet1SDptCorrL123Dn"                    , & Jet1SDptCorrL123Dn                 ,    "Jet1SDptCorrL123Dn/F"                      );                                                        
  // TreeAllHad->Branch("Jet1SDptCorrL23Smear"                  , & Jet1SDptCorrL23Smear               ,    "Jet1SDptCorrL23Smear/F"                    );                                                     
  // TreeAllHad->Branch("Jet1SDptCorrL23SmearUp"                , & Jet1SDptCorrL23SmearUp             ,    "Jet1SDptCorrL23SmearUp/F"                  );                                                       
  // TreeAllHad->Branch("Jet1SDptCorrL23SmearDn"                , & Jet1SDptCorrL23SmearDn             ,    "Jet1SDptCorrL23SmearDn/F"                  );                                                     
  TreeAllHad->Branch("Jet1SDetaRaw"                          , & Jet1SDetaRaw                       ,    "Jet1SDetaRaw/F"                            );                                               
  TreeAllHad->Branch("Jet1SDphiRaw"                          , & Jet1SDphiRaw                       ,    "Jet1SDphiRaw/F"                            );  

  // TreeAllHad->Branch("Jet1PuppiSDmassUserFloat"               , & Jet1PuppiSDmassUserFloat          ,   "Jet1PuppiSDmassUserFloat/F"                     );
  TreeAllHad->Branch("Jet1PuppiMassPruned"                    , & Jet1PuppiMassPruned               ,   "Jet1PuppiMassPruned/F"                          );
  TreeAllHad->Branch("Jet1PuppiMassTrimmed"                   , & Jet1PuppiMassTrimmed              ,   "Jet1PuppiMassTrimmed/F"                         );



  TreeAllHad->Branch("Jet1MassPruned"                        , & Jet1MassPruned                     ,    "Jet1MassPruned/F"                          );                                       
  TreeAllHad->Branch("Jet1MassTrimmed"                       , & Jet1MassTrimmed                    ,    "Jet1MassTrimmed/F"                         );                                       
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
  TreeAllHad->Branch("Jet1SDsubjet0matchedgenjetpt"          , & Jet1SDsubjet0matchedgenjetpt       ,    "Jet1SDsubjet0matchedgenjetpt/F"            ); 
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
  TreeAllHad->Branch("Jet1SDsubjet1matchedgenjetpt"          , & Jet1SDsubjet1matchedgenjetpt       ,    "Jet1SDsubjet1matchedgenjetpt/F"            ); 
  TreeAllHad->Branch("Jet1SDsubjet1tau1"                     , & Jet1SDsubjet1tau1                  ,    "Jet1SDsubjet1tau1/F"                       );
  TreeAllHad->Branch("Jet1SDsubjet1tau2"                     , & Jet1SDsubjet1tau2                  ,    "Jet1SDsubjet1tau2/F"                       );
  TreeAllHad->Branch("Jet1SDsubjet1tau3"                     , & Jet1SDsubjet1tau3                  ,    "Jet1SDsubjet1tau3/F"                       ); 
  TreeAllHad->Branch("Jet1SDsubjet1bdisc"                    , & Jet1SDsubjet1bdisc                 ,    "Jet1SDsubjet1bdisc/F"                      );                                                                                    
  // TreeAllHad->Branch("Jet1PuppiP"                            , & Jet1PuppiP                         ,    "Jet1PuppiP/F"                              );                                    
  TreeAllHad->Branch("Jet1PuppiPtRaw"                           , & Jet1PuppiPtRaw                       ,    "Jet1PuppiPtRaw/F"                             );                                    
  TreeAllHad->Branch("Jet1PuppiEtaRaw"                          , & Jet1PuppiEtaRaw                       ,    "Jet1PuppiEtaRaw/F"                            );                                     
  TreeAllHad->Branch("Jet1PuppiPhiRaw"                          , & Jet1PuppiPhiRaw                       ,    "Jet1PuppiPhiRaw/F"                            );                                     
  TreeAllHad->Branch("Jet1PuppiMassRaw"                         , & Jet1PuppiMassRaw                      ,    "Jet1PuppiMassRaw/F"                           );                                      
  TreeAllHad->Branch("Jet1PuppiArea"                         , & Jet1PuppiArea                      ,    "Jet1PuppiArea/F"                           );                                      
  
  TreeAllHad->Branch("Jet1PuppiSDmassRaw"                       , & Jet1PuppiSDmassRaw                    ,   "Jet1PuppiSDmassRaw/F"                          );
  TreeAllHad->Branch("Jet1PuppiSDmassSubjetCorr"                   , & Jet1PuppiSDmassSubjetCorr                ,   "Jet1PuppiSDmassSubjetCorr/F"                      );
  // TreeAllHad->Branch("Jet1PuppiSDmassSubjetCorrUp"                 , & Jet1PuppiSDmassSubjetCorrUp              ,   "Jet1PuppiSDmassSubjetCorrUp/F"                    );
  // TreeAllHad->Branch("Jet1PuppiSDmassSubjetCorrDn"                 , & Jet1PuppiSDmassSubjetCorrDn              ,   "Jet1PuppiSDmassSubjetCorrDn/F"                    );
  // TreeAllHad->Branch("Jet1PuppiSDmassSubjetCorrL23Smear"           , & Jet1PuppiSDmassSubjetCorrL23Smear        ,   "Jet1PuppiSDmassSubjetCorrL23Smear/F"              );
  // TreeAllHad->Branch("Jet1PuppiSDmassSubjetCorrL23SmearUp"         , & Jet1PuppiSDmassSubjetCorrL23SmearUp      ,   "Jet1PuppiSDmassSubjetCorrL23SmearUp/F"            );
  // TreeAllHad->Branch("Jet1PuppiSDmassSubjetCorrL23SmearDn"         , & Jet1PuppiSDmassSubjetCorrL23SmearDn      ,   "Jet1PuppiSDmassSubjetCorrL23SmearDn/F"            );
  TreeAllHad->Branch("Jet1PuppiSDptRaw"                         , & Jet1PuppiSDptRaw                      ,   "Jet1PuppiSDptRaw/F"                            );
  // TreeAllHad->Branch("Jet1PuppiSDptSubjetCorr"                     , & Jet1PuppiSDptSubjetCorr                  ,   "Jet1PuppiSDptSubjetCorr/F"                        );
  // TreeAllHad->Branch("Jet1PuppiSDptSubjetCorrUp"                   , & Jet1PuppiSDptSubjetCorrUp                ,   "Jet1PuppiSDptSubjetCorrUp/F"                      );
  // TreeAllHad->Branch("Jet1PuppiSDptSubjetCorrDn"                   , & Jet1PuppiSDptSubjetCorrDn                ,   "Jet1PuppiSDptSubjetCorrDn/F"                      );
  // TreeAllHad->Branch("Jet1PuppiSDptSubjetCorrL23Smear"             , & Jet1PuppiSDptSubjetCorrL23Smear          ,   "Jet1PuppiSDptSubjetCorrL23Smear/F"                );
  // TreeAllHad->Branch("Jet1PuppiSDptSubjetCorrL23SmearUp"           , & Jet1PuppiSDptSubjetCorrL23SmearUp        ,   "Jet1PuppiSDptSubjetCorrL23SmearUp/F"              );
  // TreeAllHad->Branch("Jet1PuppiSDptSubjetCorrL23SmearDn"           , & Jet1PuppiSDptSubjetCorrL23SmearDn        ,   "Jet1PuppiSDptSubjetCorrL23SmearDn/F"              );
  TreeAllHad->Branch("Jet1PuppiSDetaRaw"                        , & Jet1PuppiSDetaRaw                     ,   "Jet1PuppiSDetaRaw/F"                           );
  TreeAllHad->Branch("Jet1PuppiSDphiRaw"                        , & Jet1PuppiSDphiRaw                     ,   "Jet1PuppiSDphiRaw/F"                           );
                         
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
  TreeAllHad->Branch("Jet1PuppiSDsubjet0matchedgenjetpt"     , & Jet1PuppiSDsubjet0matchedgenjetpt  ,    "Jet1PuppiSDsubjet0matchedgenjetpt/F"       );
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
  TreeAllHad->Branch("Jet1PuppiSDsubjet1matchedgenjetpt"     , & Jet1PuppiSDsubjet1matchedgenjetpt  ,    "Jet1PuppiSDsubjet1matchedgenjetpt/F"       );
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
  // TreeAllHad->Branch("Jet1EtaScaleFactor"                    , & Jet1EtaScaleFactor                 ,    "Jet1EtaScaleFactor/F"                      );                                           
  // TreeAllHad->Branch("Jet1PhiScaleFactor"                    , & Jet1PhiScaleFactor                 ,    "Jet1PhiScaleFactor/F"                      );                                           
  // TreeAllHad->Branch("Jet1MatchedGenJetDR"                   , & Jet1MatchedGenJetDR                ,    "Jet1MatchedGenJetDR/F"                     );                                            
  TreeAllHad->Branch("Jet1MatchedGenJetPt"                   , & Jet1MatchedGenJetPt                ,    "Jet1MatchedGenJetPt/F"                     );                                            
  TreeAllHad->Branch("Jet1MatchedGenJetMass"                 , & Jet1MatchedGenJetMass              ,    "Jet1MatchedGenJetMass/F"                   ); 
  TreeAllHad->Branch("Jet1PuppiMatchedGenJetPt"                   , & Jet1PuppiMatchedGenJetPt                ,    "Jet1PuppiMatchedGenJetPt/F"                     );                                            
  TreeAllHad->Branch("Jet1PuppiMatchedGenJetMass"                 , & Jet1PuppiMatchedGenJetMass              ,    "Jet1PuppiMatchedGenJetMass/F"                   ); 
                                   
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

  TreeAllHad->Branch("NeighborJet_Jet0_pt"                   , &  NeighborJet_Jet0_pt               ,    "NeighborJet_Jet0_pt/F"                     ); 
  TreeAllHad->Branch("NeighborJet_Jet0_eta"                  , &  NeighborJet_Jet0_eta              ,    "NeighborJet_Jet0_eta/F"                    ); 
  TreeAllHad->Branch("NeighborJet_Jet0_phi"                  , &  NeighborJet_Jet0_phi              ,    "NeighborJet_Jet0_phi/F"                    ); 
  TreeAllHad->Branch("NeighborJet_Jet0_m"                    , &  NeighborJet_Jet0_m                ,    "NeighborJet_Jet0_m/F"                      ); 
  TreeAllHad->Branch("NeighborJet_Jet0_bdisc"                , &  NeighborJet_Jet0_bdisc            ,    "NeighborJet_Jet0_bdisc/F"                  ); 
  TreeAllHad->Branch("NeighborJet_Jet1_pt"                   , &  NeighborJet_Jet1_pt               ,    "NeighborJet_Jet1_pt/F"                     ); 
  TreeAllHad->Branch("NeighborJet_Jet1_eta"                  , &  NeighborJet_Jet1_eta              ,    "NeighborJet_Jet1_eta/F"                    ); 
  TreeAllHad->Branch("NeighborJet_Jet1_phi"                  , &  NeighborJet_Jet1_phi              ,    "NeighborJet_Jet1_phi/F"                    ); 
  TreeAllHad->Branch("NeighborJet_Jet1_m"                    , &  NeighborJet_Jet1_m                ,    "NeighborJet_Jet1_m/F"                      ); 
  TreeAllHad->Branch("NeighborJet_Jet1_bdisc"                , &  NeighborJet_Jet1_bdisc            ,    "NeighborJet_Jet1_bdisc/F"                  ); 

  // TreeAllHad->Branch("AllHadMETpx"                           , & AllHadMETpx                        ,    "AllHadMETpx/F"                             );                                    
  // TreeAllHad->Branch("AllHadMETpy"                           , & AllHadMETpy                        ,    "AllHadMETpy/F"                             );                                    
  TreeAllHad->Branch("AllHadMETpt"                           , & AllHadMETpt                        ,    "AllHadMETpt/F"                             );                                    
  TreeAllHad->Branch("AllHadMETphi"                          , & AllHadMETphi                       ,    "AllHadMETphi/F"                            );                                     
  TreeAllHad->Branch("AllHadMETsumET"                        , & AllHadMETsumET                     ,    "AllHadMETsumET/F"                          );                                     
  TreeAllHad->Branch("AllHadNvtx"                            , & AllHadNvtx                         ,    "AllHadNvtx/F"                              );                                   
  TreeAllHad->Branch("AllHadNvtxGood"                        , & AllHadNvtxGood                     ,    "AllHadNvtxGood/F"                          );                                   
  TreeAllHad->Branch("AllHadRho"                             , & AllHadRho                          ,    "AllHadRho/F"                               );                                  
  TreeAllHad->Branch("AllHadEventWeight"                     , & AllHadEventWeight                  ,    "AllHadEventWeight/F"                       );                                          
  TreeAllHad->Branch("AllHadPUweight"                        , & AllHadPUweight                     ,    "AllHadPUweight/F"                          );
  TreeAllHad->Branch("AllHadPUweight_MBup"                   , & AllHadPUweight_MBup                ,    "AllHadPUweight_MBup/F"                     );
  TreeAllHad->Branch("AllHadPUweight_MBdn"                   , & AllHadPUweight_MBdn                ,    "AllHadPUweight_MBdn/F"                     );
       
  TreeAllHad->Branch("DijetMass"                             , & DijetMass                          ,    "DijetMass/F"                               );                                  
  TreeAllHad->Branch("DijetMassPuppi"                        , & DijetMassPuppi                     ,    "DijetMassPuppi/F"                          );                                  
  TreeAllHad->Branch("DijetDeltaR"                           , & DijetDeltaR                        ,    "DijetDeltaR/F"                             );                                    
  TreeAllHad->Branch("DijetDeltaPhi"                         , & DijetDeltaPhi                      ,    "DijetDeltaPhi/F"                           );                                      
  TreeAllHad->Branch("DijetDeltaRap"                         , & DijetDeltaRap                      ,    "DijetDeltaRap/F"                           );                                      
  TreeAllHad->Branch("DiGenJetMass"                          , & DiGenJetMass                       ,    "DiGenJetMass/F"                            );                                     
  TreeAllHad->Branch("CountLep"                              , & CountLep                           ,    "CountLep/I"                                );                                  
  TreeAllHad->Branch("GenTTmass"                             , & GenTTmass                          ,    "GenTTmass/F"                               );                                  
  TreeAllHad->Branch("GenCountHadTop"                        , & GenCountHadTop                     ,    "GenCountHadTop/I"                         );                                  
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
  TreeAllHad->Branch("AllHadRunNum"                          , & AllHadRunNum                       ,    "AllHadRunNum/I"                            );                                     
  TreeAllHad->Branch("AllHadLumiBlock"                       , & AllHadLumiBlock                    ,    "AllHadLumiBlock/I"                         );                                        
  TreeAllHad->Branch("AllHadEventNum"                        , & AllHadEventNum                     ,    "AllHadEventNum/I"                          );                                       
  
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
       
  // TreeSemiLept->Branch("SemiLeptTrigNames"    , "vector<std::string>", &SemiLeptTrigNames);
  TreeSemiLept->Branch("SemiLeptTrigPrescales" , "vector<int>",  &SemiLeptTrigPrescales);
  TreeSemiLept->Branch("SemiLeptTrigPass"      , "vector<bool>", &SemiLeptTrigPass);
  TreeSemiLept->Branch("SemiLeptTrigAcceptBits", &SemiLeptTrigAcceptBits);

  TreeSemiLept->Branch("JetNsubjetsSD"        , & JetNsubjetsSD     ,    "JetNsubjetsSD/I"          );      
  TreeSemiLept->Branch("JetNsubjetsSDPuppi"        , & JetNsubjetsSDPuppi     ,    "JetNsubjetsSDPuppi/I"          );      


  // TreeSemiLept->Branch("SemiLeptAK4pt"      , "vector<float>", &SemiLeptAK4pt     );
  // TreeSemiLept->Branch("SemiLeptAK4eta"     , "vector<float>", &SemiLeptAK4eta    );
  // TreeSemiLept->Branch("SemiLeptAK4phi"     , "vector<float>", &SemiLeptAK4phi    );
  // TreeSemiLept->Branch("SemiLeptAK4m"       , "vector<float>", &SemiLeptAK4m      );
  // TreeSemiLept->Branch("SemiLeptAK4bdisc"   , "vector<float>", &SemiLeptAK4bdisc  );

  TreeSemiLept->Branch("v_AK8PuppiPt"    , "vector<float>", &v_AK8PuppiPt    );
  TreeSemiLept->Branch("v_AK8PuppiEta"   , "vector<float>", &v_AK8PuppiEta   );
  TreeSemiLept->Branch("v_AK8PuppiPhi"   , "vector<float>", &v_AK8PuppiPhi   );
  TreeSemiLept->Branch("v_AK8PuppiM"     , "vector<float>", &v_AK8PuppiM     );
  TreeSemiLept->Branch("v_AK8PuppiArea"  , "vector<float>", &v_AK8PuppiArea     );

  TreeSemiLept->Branch("v_AK8PuppiSdPt"    , "vector<float>", &v_AK8PuppiSdPt    );
  TreeSemiLept->Branch("v_AK8PuppiSdEta"   , "vector<float>", &v_AK8PuppiSdEta   );
  TreeSemiLept->Branch("v_AK8PuppiSdPhi"   , "vector<float>", &v_AK8PuppiSdPhi   );
  TreeSemiLept->Branch("v_AK8PuppiSdM"     , "vector<float>", &v_AK8PuppiSdM     );
  TreeSemiLept->Branch("v_AK8PuppiSdCorr"  , "vector<float>", &v_AK8PuppiSdCorr     );

  TreeSemiLept->Branch("v_photonPt"              , "vector<float>", &v_photonPt    );
  TreeSemiLept->Branch("v_photonSupClustEta"     , "vector<float>", &v_photonSupClustEta    );
  TreeSemiLept->Branch("v_photonSigIEtaIEta"     , "vector<float>", &v_photonSigIEtaIEta    );
  TreeSemiLept->Branch("v_photonFullSigIEtaIEta" , "vector<float>", &v_photonFullSigIEtaIEta    );

  TreeSemiLept->Branch("JetPtRaw"                             , & JetPtRaw                          ,    "JetPtRaw/F"                               );                                  
  TreeSemiLept->Branch("JetEtaRaw"                            , & JetEtaRaw                         ,    "JetEtaRaw/F"                              );                                   
  TreeSemiLept->Branch("JetPhiRaw"                            , & JetPhiRaw                         ,    "JetPhiRaw/F"                              );                                   
  TreeSemiLept->Branch("JetMassRaw"                           , & JetMassRaw                        ,    "JetMassRaw/F"                             );                                    
  // TreeSemiLept->Branch("JetP"                                 , & JetP                              ,    "JetP/F"                                   );                              
  // TreeSemiLept->Branch("JetPt"                                , & JetPt                             ,    "JetPt/F"                                  );                               
  // TreeSemiLept->Branch("JetEta"                               , & JetEta                            ,    "JetEta/F"                                 );                                
  // TreeSemiLept->Branch("JetPhi"                               , & JetPhi                            ,    "JetPhi/F"                                 );                                
  // TreeSemiLept->Branch("JetRap"                               , & JetRap                            ,    "JetRap/F"                                 );                                
  // TreeSemiLept->Branch("JetEnergy"                            , & JetEnergy                         ,    "JetEnergy/F"                              );                                   
  // TreeSemiLept->Branch("JetMass"                              , & JetMass                           ,    "JetMass/F"                                );                                 
  TreeSemiLept->Branch("JetArea"                              , & JetArea                           ,    "JetArea/F"                                );                                 
  
  // TreeSemiLept->Branch("JetSDmass"                            , & JetSDmass                         ,    "JetSDmass/F"                              );                                         
  TreeSemiLept->Branch("JetSDmassRaw"                         , & JetSDmassRaw                      ,    "JetSDmassRaw/F"                           );                                               
  TreeSemiLept->Branch("JetSDmassSubjetCorrL23"                     , & JetSDmassSubjetCorrL23                  ,    "JetSDmassSubjetCorrL23/F"                       );                                                    
  // TreeSemiLept->Branch("JetSDmassSubjetCorrL23Up"                   , & JetSDmassSubjetCorrL23Up                ,    "JetSDmassSubjetCorrL23Up/F"                     );                                                      
  // TreeSemiLept->Branch("JetSDmassSubjetCorrL23Dn"                   , & JetSDmassSubjetCorrL23Dn                ,    "JetSDmassSubjetCorrL23Dn/F"                     );                                                      
  TreeSemiLept->Branch("JetSDmassSubjetCorrL123"                    , & JetSDmassSubjetCorrL123                 ,    "JetSDmassSubjetCorrL123/F"                      );                                                      
  // TreeSemiLept->Branch("JetSDmassCorrL123Up"                  , & JetSDmassCorrL123Up               ,    "JetSDmassCorrL123Up/F"                    );                                                        
  // TreeSemiLept->Branch("JetSDmassCorrL123Dn"                  , & JetSDmassCorrL123Dn               ,    "JetSDmassCorrL123Dn/F"                    );                                                        
  // TreeSemiLept->Branch("JetSDmassCorrL23Smear"                , & JetSDmassCorrL23Smear             ,    "JetSDmassCorrL23Smear/F"                     );                                                     
  // TreeSemiLept->Branch("JetSDmassCorrL23SmearUp"              , & JetSDmassCorrL23SmearUp           ,    "JetSDmassCorrL23SmearUp/F"                   );                                                       
  // TreeSemiLept->Branch("JetSDmassCorrL23SmearDn"              , & JetSDmassCorrL23SmearDn           ,    "JetSDmassCorrL23SmearDn/F"                   );   
  TreeSemiLept->Branch("JetSDptRaw"                           , & JetSDptRaw                        ,    "JetSDptRaw/F"                             );                                               
  // TreeSemiLept->Branch("JetSDptCorrL23"                       , & JetSDptCorrL23                    ,    "JetSDptCorrL23/F"                         );                                                    
  // TreeSemiLept->Branch("JetSDptCorrL23Up"                     , & JetSDptCorrL23Up                  ,    "JetSDptCorrL23Up/F"                       );                                                      
  // TreeSemiLept->Branch("JetSDptCorrL23Dn"                     , & JetSDptCorrL23Dn                  ,    "JetSDptCorrL23Dn/F"                       );                                                      
  // TreeSemiLept->Branch("JetSDptCorrL123"                      , & JetSDptCorrL123                   ,    "JetSDptCorrL123/F"                        );                                                      
  // TreeSemiLept->Branch("JetSDptCorrL123Up"                    , & JetSDptCorrL123Up                 ,    "JetSDptCorrL123Up/F"                      );                                                        
  // TreeSemiLept->Branch("JetSDptCorrL123Dn"                    , & JetSDptCorrL123Dn                 ,    "JetSDptCorrL123Dn/F"                      );                                                        
  // TreeSemiLept->Branch("JetSDptCorrL23Smear"                  , & JetSDptCorrL23Smear               ,    "JetSDptCorrL23Smear/F"                       );                                                     
  // TreeSemiLept->Branch("JetSDptCorrL23SmearUp"                , & JetSDptCorrL23SmearUp             ,    "JetSDptCorrL23SmearUp/F"                     );                                                       
  // TreeSemiLept->Branch("JetSDptCorrL23SmearDn"                , & JetSDptCorrL23SmearDn             ,    "JetSDptCorrL23SmearDn/F"                     );                                                     
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
  TreeSemiLept->Branch("JetSDsubjet0matchedgenjetpt"          , & JetSDsubjet0matchedgenjetpt       ,    "JetSDsubjet0matchedgenjetpt/F"            ); 
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
  TreeSemiLept->Branch("JetSDsubjet1matchedgenjetpt"          , & JetSDsubjet1matchedgenjetpt       ,    "JetSDsubjet1matchedgenjetpt/F"            ); 
  TreeSemiLept->Branch("JetSDsubjet1tau1"                     , & JetSDsubjet1tau1                  ,    "JetSDsubjet1tau1/F"                       );
  TreeSemiLept->Branch("JetSDsubjet1tau2"                     , & JetSDsubjet1tau2                  ,    "JetSDsubjet1tau2/F"                       );
  TreeSemiLept->Branch("JetSDsubjet1tau3"                     , & JetSDsubjet1tau3                  ,    "JetSDsubjet1tau3/F"                       );                                           
  TreeSemiLept->Branch("JetSDsubjet1bdisc"                    , & JetSDsubjet1bdisc                 ,    "JetSDsubjet1bdisc/F"                      );                                     

  // TreeSemiLept->Branch("JetPuppiP"                            , & JetPuppiP                         ,    "JetPuppiP/F"                              );                                    
  TreeSemiLept->Branch("JetPuppiPtRaw"                           , & JetPuppiPtRaw                        ,    "JetPuppiPtRaw/F"                             );                                    
  TreeSemiLept->Branch("JetPuppiEtaRaw"                          , & JetPuppiEtaRaw                       ,    "JetPuppiEtaRaw/F"                            );                                     
  TreeSemiLept->Branch("JetPuppiPhiRaw"                          , & JetPuppiPhiRaw                       ,    "JetPuppiPhiRaw/F"                            );                                     
  TreeSemiLept->Branch("JetPuppiMassRaw"                         , & JetPuppiMassRaw                      ,    "JetPuppiMassRaw/F"                           );                                      
  TreeSemiLept->Branch("JetPuppiArea"                         , & JetPuppiArea                      ,    "JetPuppiArea/F"                           );                                      

  // TreeSemiLept->Branch("JetPuppiSDmassUserFloat"               , & JetPuppiSDmassUserFloat          ,   "JetPuppiSDmassUserFloat/F"                     );
  TreeSemiLept->Branch("JetPuppiMassPruned"                    , & JetPuppiMassPruned               ,   "JetPuppiMassPruned/F"                          );
  TreeSemiLept->Branch("JetPuppiMassTrimmed"                   , & JetPuppiMassTrimmed              ,   "JetPuppiMassTrimmed/F"                         );


  
  TreeSemiLept->Branch("JetPuppiSDmassRaw"                         , & JetPuppiSDmassRaw                    ,    "JetPuppiSDmassRaw/F"                          );
  TreeSemiLept->Branch("JetPuppiSDmassSubjetCorr"                     , & JetPuppiSDmassSubjetCorr                ,    "JetPuppiSDmassSubjetCorr/F"                      );
  // TreeSemiLept->Branch("JetPuppiSDmassSubjetCorrUp"                   , & JetPuppiSDmassSubjetCorrUp              ,    "JetPuppiSDmassSubjetCorrUp/F"                    );
  // TreeSemiLept->Branch("JetPuppiSDmassSubjetCorrDn"                   , & JetPuppiSDmassSubjetCorrDn              ,    "JetPuppiSDmassSubjetCorrDn/F"                    );
  // TreeSemiLept->Branch("JetPuppiSDmassSubjetCorrL23Smear"             , & JetPuppiSDmassSubjetCorrL23Smear        ,    "JetPuppiSDmassSubjetCorrL23Smear/F"              );
  // TreeSemiLept->Branch("JetPuppiSDmassSubjetCorrL23SmearUp"           , & JetPuppiSDmassSubjetCorrL23SmearUp      ,    "JetPuppiSDmassSubjetCorrL23SmearUp/F"            );
  // TreeSemiLept->Branch("JetPuppiSDmassSubjetCorrL23SmearDn"           , & JetPuppiSDmassSubjetCorrL23SmearDn      ,    "JetPuppiSDmassSubjetCorrL23SmearDn/F"            );
  TreeSemiLept->Branch("JetPuppiSDptRaw"                           , & JetPuppiSDptRaw                      ,    "JetPuppiSDptRaw/F"                            );
  // TreeSemiLept->Branch("JetPuppiSDptSubjetCorr"                       , & JetPuppiSDptSubjetCorr                  ,    "JetPuppiSDptSubjetCorr/F"                        );
  // TreeSemiLept->Branch("JetPuppiSDptSubjetCorrUp"                     , & JetPuppiSDptSubjetCorrUp                ,    "JetPuppiSDptSubjetCorrUp/F"                      );
  // TreeSemiLept->Branch("JetPuppiSDptSubjetCorrDn"                     , & JetPuppiSDptSubjetCorrDn                ,    "JetPuppiSDptSubjetCorrDn/F"                      );
  // TreeSemiLept->Branch("JetPuppiSDptSubjetCorrL23Smear"               , & JetPuppiSDptSubjetCorrL23Smear          ,    "JetPuppiSDptSubjetCorrL23Smear/F"                );
  // TreeSemiLept->Branch("JetPuppiSDptSubjetCorrL23SmearUp"             , & JetPuppiSDptSubjetCorrL23SmearUp        ,    "JetPuppiSDptSubjetCorrL23SmearUp/F"              );
  // TreeSemiLept->Branch("JetPuppiSDptSubjetCorrL23SmearDn"             , & JetPuppiSDptSubjetCorrL23SmearDn        ,    "JetPuppiSDptSubjetCorrL23SmearDn/F"              );
  TreeSemiLept->Branch("JetPuppiSDetaRaw"                          , & JetPuppiSDetaRaw                     ,    "JetPuppiSDetaRaw/F"                           );
  TreeSemiLept->Branch("JetPuppiSDphiRaw"                          , & JetPuppiSDphiRaw                     ,    "JetPuppiSDphiRaw/F"                           );
                         

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
  TreeSemiLept->Branch("JetPuppiSDsubjet0matchedgenjetpt"     , & JetPuppiSDsubjet0matchedgenjetpt  ,    "JetPuppiSDsubjet0matchedgenjetpt/F"       );
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
  TreeSemiLept->Branch("JetPuppiSDsubjet1matchedgenjetpt"     , & JetPuppiSDsubjet1matchedgenjetpt  ,    "JetPuppiSDsubjet1matchedgenjetpt/F"       );
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
  // TreeSemiLept->Branch("JetEtaScaleFactor"                    , & JetEtaScaleFactor                 ,    "JetEtaScaleFactor/F"                      );                                           
  // TreeSemiLept->Branch("JetPhiScaleFactor"                    , & JetPhiScaleFactor                 ,    "JetPhiScaleFactor/F"                      );                                           
  // TreeSemiLept->Branch("JetMatchedGenJetDR"                   , & JetMatchedGenJetDR                ,    "JetMatchedGenJetDR/F"                     );                                            
  TreeSemiLept->Branch("JetMatchedGenJetPt"                   , & JetMatchedGenJetPt                ,    "JetMatchedGenJetPt/F"                     );                                            
  TreeSemiLept->Branch("JetMatchedGenJetMass"                 , & JetMatchedGenJetMass              ,    "JetMatchedGenJetMass/F"                   ); 
  TreeSemiLept->Branch("JetPuppiMatchedGenJetPt"              , & JetPuppiMatchedGenJetPt           ,    "JetPuppiMatchedGenJetPt/F"                );                                            
  TreeSemiLept->Branch("JetPuppiMatchedGenJetMass"            , & JetPuppiMatchedGenJetMass         ,    "JetPuppiMatchedGenJetMass/F"              ); 
                           
  TreeSemiLept->Branch("JetGenMatched_TopHadronic"            , & JetGenMatched_TopHadronic         ,    "JetGenMatched_TopHadronic/I"              );      
  TreeSemiLept->Branch("JetGenMatched_TopPt"                  , & JetGenMatched_TopPt               ,    "JetGenMatched_TopPt/F"                    );      
  TreeSemiLept->Branch("JetGenMatched_TopEta"                 , & JetGenMatched_TopEta              ,    "JetGenMatched_TopEta/F"                   );      
  TreeSemiLept->Branch("JetGenMatched_TopPhi"                 , & JetGenMatched_TopPhi              ,    "JetGenMatched_TopPhi/F"                   );      
  TreeSemiLept->Branch("JetGenMatched_TopMass"                , & JetGenMatched_TopMass             ,    "JetGenMatched_TopMass/F"                  );      
  TreeSemiLept->Branch("JetGenMatched_bPt"                    , & JetGenMatched_bPt                 ,    "JetGenMatched_bPt/F"                      );      
  TreeSemiLept->Branch("JetGenMatched_WPt"                    , & JetGenMatched_WPt                 ,    "JetGenMatched_WPt/F"                      ); 
  TreeSemiLept->Branch("JetGenMatched_WEta"                   , & JetGenMatched_WEta                ,    "JetGenMatched_WEta/F"                     );
  TreeSemiLept->Branch("JetGenMatched_WPhi"                   , & JetGenMatched_WPhi                ,    "JetGenMatched_WPhi/F"                     );
  TreeSemiLept->Branch("JetGenMatched_WMass"                  , & JetGenMatched_WMass               ,    "JetGenMatched_WMass/F"                    );
  TreeSemiLept->Branch("JetGenMatched_ZPt"                    , & JetGenMatched_ZPt                 ,    "JetGenMatched_ZPt/F"                      ); 
  TreeSemiLept->Branch("JetGenMatched_ZEta"                   , & JetGenMatched_ZEta                ,    "JetGenMatched_ZEta/F"                     );
  TreeSemiLept->Branch("JetGenMatched_ZPhi"                   , & JetGenMatched_ZPhi                ,    "JetGenMatched_ZPhi/F"                     );
  TreeSemiLept->Branch("JetGenMatched_ZMass"                  , & JetGenMatched_ZMass               ,    "JetGenMatched_ZMass/F"                    );     
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
  TreeSemiLept->Branch("SemiLeptMETgenMET"                    , & SemiLeptMETgenMET                 , "SemiLeptMETgenMET/F"              );
  TreeSemiLept->Branch("SemiLeptMETuncorPt"                   , & SemiLeptMETuncorPt                , "SemiLeptMETuncorPt/F"             );

  TreeSemiLept->Branch("SemiLeptMETshiftedPtJetEnUp"      , & SemiLeptMETshiftedPtJetEnUp   , "SemiLeptMETshiftedPtJetEnUp/F"     );
  TreeSemiLept->Branch("SemiLeptMETshiftedPtJetEnDn"      , & SemiLeptMETshiftedPtJetEnDn   , "SemiLeptMETshiftedPtJetEnDn/F"     );
  TreeSemiLept->Branch("SemiLeptMETshiftedPtElEnUp"       , & SemiLeptMETshiftedPtElEnUp    , "SemiLeptMETshiftedPtElEnUp/F"      );
  TreeSemiLept->Branch("SemiLeptMETshiftedPtElEnDn"       , & SemiLeptMETshiftedPtElEnDn    , "SemiLeptMETshiftedPtElEnDn/F"      );
  TreeSemiLept->Branch("SemiLeptMETshiftedPtMuEnUp"       , & SemiLeptMETshiftedPtMuEnUp    , "SemiLeptMETshiftedPtMuEnUp/F"      );
  TreeSemiLept->Branch("SemiLeptMETshiftedPtMuEnDn"       , & SemiLeptMETshiftedPtMuEnDn    , "SemiLeptMETshiftedPtMuEnDn/F"      );
  TreeSemiLept->Branch("SemiLeptMETshiftedPtJetResUp"     , & SemiLeptMETshiftedPtJetResUp  , "SemiLeptMETshiftedPtJetResUp/F"    );
  TreeSemiLept->Branch("SemiLeptMETshiftedPtJetResDn"     , & SemiLeptMETshiftedPtJetResDn  , "SemiLeptMETshiftedPtJetResDn/F"    );
  TreeSemiLept->Branch("SemiLeptMETshiftedPtUnclEnUp"     , & SemiLeptMETshiftedPtUnclEnUp  , "SemiLeptMETshiftedPtUnclEnUp/F"    );
  TreeSemiLept->Branch("SemiLeptMETshiftedPtUnclEnDn"     , & SemiLeptMETshiftedPtUnclEnDn  , "SemiLeptMETshiftedPtUnclEnDn/F"    );

  TreeSemiLept->Branch("SemiLeptNvtx"                         , & SemiLeptNvtx                      , "SemiLeptNvtx/F"                   );
  TreeSemiLept->Branch("SemiLeptNvtxGood"                     , & SemiLeptNvtxGood                  , "SemiLeptNvtxGood/F"               );
  TreeSemiLept->Branch("SemiLeptRho"                          , & SemiLeptRho                       , "SemiLeptRho/F"                    );
  TreeSemiLept->Branch("SemiLeptEventWeight"                  , & SemiLeptEventWeight               , "SemiLeptEventWeight/F"            );
  TreeSemiLept->Branch("SemiLeptPUweight"                     , & SemiLeptPUweight                  , "SemiLeptPUweight/F"            );
  TreeSemiLept->Branch("SemiLeptPUweight_MBup"                , & SemiLeptPUweight_MBup             , "SemiLeptPUweight_MBup/F"            );
  TreeSemiLept->Branch("SemiLeptPUweight_MBdn"                , & SemiLeptPUweight_MBdn             , "SemiLeptPUweight_MBdn/F"            );
       
  

  TreeSemiLept->Branch("SemiLeptGenTTmass"                    , & SemiLeptGenTTmass                 , "SemiLeptGenTTmass/F"              );
  TreeSemiLept->Branch("SemiLeptGenCountHadTop"               , & SemiLeptGenCountHadTop            , "SemiLeptGenCountHadTop/I"         );
  
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
  TreeSemiLept->Branch("SemiLeptRunNum"                       , & SemiLeptRunNum                    , "SemiLeptRunNum/I"                 );
  TreeSemiLept->Branch("SemiLeptLumiBlock"                    , & SemiLeptLumiBlock                 , "SemiLeptLumiBlock/I"              );
  TreeSemiLept->Branch("SemiLeptEventNum"                     , & SemiLeptEventNum                  , "SemiLeptEventNum/I"               );
  TreeSemiLept->Branch("SemiLeptPassMETFilters"               , & SemiLeptPassMETFilters            , "SemiLeptPassMETFilters/I"         );
 
  TreeSemiLept->Branch("AK4_dRminLep_Pt"                           , & AK4_dRminLep_Pt                        , "AK4_dRminLep_Pt/F"                     );  
  TreeSemiLept->Branch("AK4_dRminLep_Eta"                          , & AK4_dRminLep_Eta                       , "AK4_dRminLep_Eta/F"                    );  
  TreeSemiLept->Branch("AK4_dRminLep_Phi"                          , & AK4_dRminLep_Phi                       , "AK4_dRminLep_Phi/F"                    );  
  TreeSemiLept->Branch("AK4_dRminLep_Mass"                         , & AK4_dRminLep_Mass                      , "AK4_dRminLep_Mass/F"                   );  
  TreeSemiLept->Branch("AK4_dRminLep_Bdisc"                        , & AK4_dRminLep_Bdisc                     , "AK4_dRminLep_Bdisc/F"                  );  
  TreeSemiLept->Branch("AK4_dRminLep_dRlep"                        , & AK4_dRminLep_dRlep                     , "AK4_dRminLep_dRlep/F"                  );  
  TreeSemiLept->Branch("AK4_dRminLep_dRak8"                        , & AK4_dRminLep_dRak8                     , "AK4_dRminLep_dRak8/F"                  );  
  TreeSemiLept->Branch("AK4_dRminLep_PtSmear"                      , & AK4_dRminLep_PtSmear                   , "AK4_dRminLep_PtSmear/F"   );
  TreeSemiLept->Branch("AK4_dRminLep_PtSmearUp"                    , & AK4_dRminLep_PtSmearUp                 , "AK4_dRminLep_PtSmearUp/F" );
  TreeSemiLept->Branch("AK4_dRminLep_PtSmearDn"                    , & AK4_dRminLep_PtSmearDn                 , "AK4_dRminLep_PtSmearDn/F" );
  TreeSemiLept->Branch("AK4_dRminLep_PtUncorr"                     , & AK4_dRminLep_PtUncorr                  , "AK4_dRminLep_PtUncorr/F"  );
  TreeSemiLept->Branch("AK4_dRminLep_Corr"                         , & AK4_dRminLep_Corr                      , "AK4_dRminLep_Corr/F"    );                
  TreeSemiLept->Branch("AK4_dRminLep_CorrUp"                       , & AK4_dRminLep_CorrUp                    , "AK4_dRminLep_CorrUp/F"  );                 
  TreeSemiLept->Branch("AK4_dRminLep_CorrDn"                       , & AK4_dRminLep_CorrDn                    , "AK4_dRminLep_CorrDn/F"  );                  



  // TreeSemiLept->Branch("AK4BtagdRminPt"                       , & AK4BtagdRminPt                    , "AK4BtagdRminPt/F"                 );  
  // TreeSemiLept->Branch("AK4BtagdRminBdisc"                    , & AK4BtagdRminBdisc                 , "AK4BtagdRminBdisc/F"              );  
  // TreeSemiLept->Branch("AK4BtagdRminLep"                      , & AK4BtagdRminLep                   , "AK4BtagdRminLep/F"                );  
  TreeSemiLept->Branch("LepHemiContainsAK4BtagLoose"          , & LepHemiContainsAK4BtagLoose       , "LepHemiContainsAK4BtagLoose/I"    );  
  TreeSemiLept->Branch("LepHemiContainsAK4BtagMedium"         , & LepHemiContainsAK4BtagMedium      , "LepHemiContainsAK4BtagMedium/I"   );  
  TreeSemiLept->Branch("LepHemiContainsAK4BtagTight"          , & LepHemiContainsAK4BtagTight       , "LepHemiContainsAK4BtagTight/I"    );  

  TreeSemiLept->Branch("LeptonPhi0"                            , &  LeptonPhi0                        , "LeptonPhi0/F"                      ); 
  TreeSemiLept->Branch("LeptonPt0"                             , &  LeptonPt0                         , "LeptonPt0/F"                       ); 
  TreeSemiLept->Branch("LeptonEta0"                            , &  LeptonEta0                        , "LeptonEta0/F"                      ); 
  TreeSemiLept->Branch("LeptonMass0"                           , &  LeptonMass0                       , "LeptonMass0/F"                     );
  TreeSemiLept->Branch("LeptonPhi1"                            , &  LeptonPhi1                        , "LeptonPhi1/F"                      ); 
  TreeSemiLept->Branch("LeptonPt1"                             , &  LeptonPt1                         , "LeptonPt1/F"                       ); 
  TreeSemiLept->Branch("LeptonEta1"                            , &  LeptonEta1                        , "LeptonEta1/F"                      ); 
  TreeSemiLept->Branch("LeptonMass1"                           , &  LeptonMass1                       , "LeptonMass1/F"                     ); 
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
 
  TreeSemiLept->Branch("Electron_iso_passHLTpre"      , & Electron_iso_passHLTpre   , "Electron_iso_passHLTpre/I"    );
  TreeSemiLept->Branch("Electron_iso_passLoose"       , & Electron_iso_passLoose    , "Electron_iso_passLoose/I"     );
  TreeSemiLept->Branch("Electron_iso_passMedium"      , & Electron_iso_passMedium   , "Electron_iso_passMedium/I"    );
  TreeSemiLept->Branch("Electron_iso_passTight"       , & Electron_iso_passTight    , "Electron_iso_passTight/I"     );
  TreeSemiLept->Branch("Electron_iso_passHEEP"        , & Electron_iso_passHEEP     , "Electron_iso_passHEEP/I"      );
  TreeSemiLept->Branch("Electron_noiso_passLoose"     , & Electron_noiso_passLoose  , "Electron_noiso_passLoose/I"   );
  TreeSemiLept->Branch("Electron_noiso_passMedium"    , & Electron_noiso_passMedium , "Electron_noiso_passMedium/I"  );
  TreeSemiLept->Branch("Electron_noiso_passTight"     , & Electron_noiso_passTight  , "Electron_noiso_passTight/I"   );
  TreeSemiLept->Branch("Electron_noiso_passHEEP"      , & Electron_noiso_passHEEP   , "Electron_noiso_passHEEP/I"    );
 

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
  // using namespace fastjet;

  if (verbose_) {
    cout<<"----------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"Analyze event "<<iEvent.id().event()<<" run "<<iEvent.id().run()<<" lumiblock "<<iEvent.id().luminosityBlock()<<endl;
  }

  h_cutflow_allhad   ->Fill(0.5);
  h_cutflow_semilept ->Fill(0.5);

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
  TLorentzVector Wp_p4;
  TLorentzVector Wm_p4;
  TLorentzVector Z1_p4;
  TLorentzVector Z2_p4;
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
  int count_gen_truth_hadronic_top = 0;

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

  double max_deltaR_parton_t1  = -1;
  double max_deltaR_parton_t2  = -1;
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
      if (id==24 && status<30 && status>=20) {
        Wp_p4.SetPxPyPzE( px, py, pz, e ); 
        parton1id = id;
        if (verboseGen_) cout<<"..Wplus (hard)"<<endl;//" with pt "<<pt<<" status "<<status<<" ndau "<< ndau <<" pt "<<pt<<" eta "<<eta<<" phi "<<phi<<" parton1id = "<<parton1id<<endl;
      }
      if (id==-24 && status<30 && status>=20) {
        Wm_p4.SetPxPyPzE( px, py, pz, e ); 
        parton2id = id;
        if (verboseGen_) cout<<"..Wminus (hard)"<<endl;//" with pt "<<pt<<" status "<<status<<" ndau "<< ndau <<" pt "<<pt<<" eta "<<eta<<" phi "<<phi<<" parton2id = "<<parton2id<<endl;
      }
      if (id==23 && status<30 && status>=20) {
        Z1_p4.SetPxPyPzE( px, py, pz, e ); 
        parton1id = id;
        if (verboseGen_) cout<<"..Zboson (hard)"<<endl;//" with pt "<<pt<<" status "<<status<<" ndau "<< ndau <<" pt "<<pt<<" eta "<<eta<<" phi "<<phi<<" parton1id = "<<parton1id<<endl;
      }
      if (id==-23 && status<30 && status>=20) {
        Z2_p4.SetPxPyPzE( px, py, pz, e ); 
        parton2id = id;
        if (verboseGen_) cout<<"..aZboson (hard)"<<endl;//" with pt "<<pt<<" status "<<status<<" ndau "<< ndau <<" pt "<<pt<<" eta "<<eta<<" phi "<<phi<<" parton1id = "<<parton1id<<endl;
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
    if (top1hadronic && top2hadronic)  { GenTruth_allhadronic  = true; count_gen_truth_hadronic_top =2; }
    if (top1hadronic && !top2hadronic) { GenTruth_semileptonic = true; count_gen_truth_hadronic_top =1; }
    if (!top1hadronic && top2hadronic) { GenTruth_semileptonic = true; count_gen_truth_hadronic_top =1; }

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
    
      cout<<"count_gen_truth_hadronic_top "<<count_gen_truth_hadronic_top<<endl;

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

  const int ntrigs = trigsToRun.size();
  if (verbose_) cout<<"trigsToRun size "<<ntrigs<<endl;

  // do the same thing two different ways ( to test)
  std::bitset<38> hltbit;
  vector<bool> trigAccept;

  // AllHadTrigNames       ->clear();
  // SemiLeptTrigNames     ->clear();
  AllHadTrigPrescales   ->clear();
  SemiLeptTrigPrescales ->clear();
  AllHadTrigPass        ->clear();
  SemiLeptTrigPass      ->clear();

  const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);
  if (verbose_) std::cout << "\n === TRIGGER PATHS === " << std::endl;
  int counttrigs =0;

  // Loop over the list of triggers to save
  for (unsigned int j=0; j<trigsToRun.size(); j++){ 
    if (verbose_) cout<<"try to find "<<setw(50)<< trigsToRun[j];
    
    bool foundtrig  = false;
    bool pass = false;
    int prescale = 0;
    string name = "";
    // Loop over all triggers in the event
    for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
      
      name = names.triggerName(i);
      std::size_t found = name.find( trigsToRun[j] );

      // If the trigger from the trigger list is found in the event check if it passed
      if ( found !=std::string::npos ) {
        foundtrig = true;
        int accept = triggerBits->accept(i) ;
        if (accept ==1 ) pass = true;
        prescale = triggerPrescales->getPrescaleForIndex(i)  ;
        break;
      }
    }// end loop over all triggers in event

    if (verbose_ && foundtrig)  cout<<"  -> found. pass = "<<pass << ", prescale = " << prescale<<", name = "<< name  << std::endl; 
    if (verbose_ && !foundtrig) cout<<"  -> did not find "<< trigsToRun[j]<<endl;

      trigAccept.push_back(pass);
      // AllHadTrigNames       ->push_back(name);
      // SemiLeptTrigNames     ->push_back(name);
      AllHadTrigPrescales   ->push_back(prescale);
      SemiLeptTrigPrescales ->push_back(prescale);
      AllHadTrigPass        ->push_back(pass);
      SemiLeptTrigPass      ->push_back(pass);
      if (pass)  hltbit[counttrigs]=1;  
      counttrigs++;
  
  }// end loop over list of triggers to save in tree

  if (verbose_) {
    cout<<"trig accept vector. size = "<<trigAccept.size()<<" contents = "<<endl;
    for (unsigned int i=0; i< trigAccept.size(); i++){
      cout<<trigAccept[trigAccept.size()-1-i];
    }
    cout<<endl;
    cout<<"hlt bit = "<<endl;
    cout<<hltbit.to_string()<<endl;
  }

  AllHadTrigAcceptBits   = hltbit.to_string();
  SemiLeptTrigAcceptBits = hltbit.to_string();
  

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

  edm::Handle < edm::TriggerResults > metFilters;
  iEvent.getByToken(triggerResultsMETFilterToken_, metFilters);
  edm::TriggerNames const& filterTriggerNames = iEvent.triggerNames(*metFilters);

  int nMETfilters = metFilters->size();
  if (verbose_) cout<<"nMETfilters "<<nMETfilters<<endl;

  //https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2

  vector <string> filterFlags;
  filterFlags.push_back("Flag_goodVertices");
  if ( iEvent.isRealData() ) filterFlags.push_back("Flag_globalTightHalo2016Filter"); //Data only
  filterFlags.push_back("Flag_HBHENoiseFilter");
  filterFlags.push_back("Flag_HBHENoiseIsoFilter");
  filterFlags.push_back("Flag_EcalDeadCellTriggerPrimitiveFilter");
  // filterFlags.push_back("Flag_eeBadScFilter");   // No longer suggested for Moriond 2017

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
 

  // RECO problemes -> apply to both data and MC. Not sure if we need these for the Summer16 samples. What about the re-miniAOD?
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

  // Run 2016 F into two JEC payloads. 
  //   IOV EF: [276831,278801] corresponds to Summer16_23Sep2016EFV3_DATA (For Runs E/early F)
  //   IOV FG: [278802,280385] corresponds to Summer16_23Sep2016GV3_DATA (For Runs lateF/G)
  std::vector<std::string>  jecPayloadsAK4chsFinal;
  std::vector<std::string>  jecPayloadsAK8chsFinal;
  std::vector<std::string>  jecPayloadsAK4pupFinal;
  std::vector<std::string>  jecPayloadsAK8pupFinal;

  int runNumber = iEvent.id().run();

  if (isRun2016F_ && runNumber < 278801 ){
    if (verbose_) cout<<"Using Run2016F early JEC"<<endl;
    jecPayloadsAK4chsFinal = jecPayloadsAK4chs_;
    jecPayloadsAK8chsFinal = jecPayloadsAK8chs_;
    jecPayloadsAK4pupFinal = jecPayloadsAK4pup_;
    jecPayloadsAK8pupFinal = jecPayloadsAK8pup_;
  } 
  else if (isRun2016F_ && runNumber > 278801 ){
    if (verbose_) cout<<"Using Run2016F late JEC"<<endl;
    jecPayloadsAK4chsFinal = jecPayloadsAK4chsSecondary_;
    jecPayloadsAK8chsFinal = jecPayloadsAK8chsSecondary_;
    jecPayloadsAK4pupFinal = jecPayloadsAK4pupSecondary_;
    jecPayloadsAK8pupFinal = jecPayloadsAK8pupSecondary_;
  } 
  else{
    if (verbose_) cout<<"Using Primary JEC from cfg"<<endl;
    jecPayloadsAK4chsFinal = jecPayloadsAK4chs_;
    jecPayloadsAK8chsFinal = jecPayloadsAK8chs_;
    jecPayloadsAK4pupFinal = jecPayloadsAK4pup_;
    jecPayloadsAK8pupFinal = jecPayloadsAK8pup_;
  }
  
  if (verbose_){
    cout<<"jecPayloadsAK4chs_.size()              "<<jecPayloadsAK4chs_.size()<<endl;
    cout<<"jecPayloadsAK4chsSecondary_.size()     "<<jecPayloadsAK4chsSecondary_.size()<<endl;
    cout<<"jecPayloadsAK4chsFinal.size()          "<<jecPayloadsAK4chsFinal.size()<<endl;
  }

  // AK4chs JEC 
  std::vector<JetCorrectorParameters> vParAK4chs;
   for ( std::vector<std::string>::const_iterator ipayload = jecPayloadsAK4chsFinal.begin(),
     ipayloadEnd = jecPayloadsAK4chsFinal.end(); ipayload != ipayloadEnd - 1; ++ipayload ) {
     if (verbose_)cout<<"AK4chs JEC txt: "<<*ipayload<<endl;
     JetCorrectorParameters pars(*ipayload);
     vParAK4chs.push_back(pars);
  }
  JetCorrectorAK4chs   = boost::shared_ptr<FactorizedJetCorrector>  ( new FactorizedJetCorrector(vParAK4chs) );
  JetCorrUncertAK4chs  = boost::shared_ptr<JetCorrectionUncertainty>( new JetCorrectionUncertainty(jecPayloadsAK4chsFinal.back()));
  
  // AK8chs JEC 
  std::vector<JetCorrectorParameters> vParAK8chs;
   for ( std::vector<std::string>::const_iterator ipayload = jecPayloadsAK8chsFinal.begin(),
     ipayloadEnd = jecPayloadsAK8chsFinal.end(); ipayload != ipayloadEnd - 1; ++ipayload ) {
     JetCorrectorParameters pars(*ipayload);
     vParAK8chs.push_back(pars);
  }
  JetCorrectorAK8chs   = boost::shared_ptr<FactorizedJetCorrector>  ( new FactorizedJetCorrector(vParAK8chs) );
  JetCorrUncertAK8chs  = boost::shared_ptr<JetCorrectionUncertainty>( new JetCorrectionUncertainty(jecPayloadsAK8chsFinal.back()));

  // AK4pup JEC 
  std::vector<JetCorrectorParameters> vParAK4pup;
   for ( std::vector<std::string>::const_iterator ipayload = jecPayloadsAK4pupFinal.begin(),
     ipayloadEnd = jecPayloadsAK4pupFinal.end(); ipayload != ipayloadEnd - 1; ++ipayload ) {
     JetCorrectorParameters pars(*ipayload);
     vParAK4pup.push_back(pars);
  }
  JetCorrectorAK4pup   = boost::shared_ptr<FactorizedJetCorrector>  ( new FactorizedJetCorrector(vParAK4pup) );
  JetCorrUncertAK4pup  = boost::shared_ptr<JetCorrectionUncertainty>( new JetCorrectionUncertainty(jecPayloadsAK4pupFinal.back()));
  
  // AK8pup JEC 
  std::vector<JetCorrectorParameters> vParAK8pup;
   for ( std::vector<std::string>::const_iterator ipayload = jecPayloadsAK8pupFinal.begin(),
     ipayloadEnd = jecPayloadsAK8pupFinal.end(); ipayload != ipayloadEnd - 1; ++ipayload ) {
     JetCorrectorParameters pars(*ipayload);
     vParAK8pup.push_back(pars);
  }
  JetCorrectorAK8pup   = boost::shared_ptr<FactorizedJetCorrector>  ( new FactorizedJetCorrector(vParAK8pup) );
  JetCorrUncertAK8pup  = boost::shared_ptr<JetCorrectionUncertainty>( new JetCorrectionUncertainty(jecPayloadsAK8pupFinal.back()));
  
  // jet resolution from text files
  JME::JetResolution jet_resolution_AK4CHS;
  JME::JetResolution jet_resolution_AK8CHS;
  jet_resolution_AK4CHS = JME::JetResolution(jertextAK4_);
  jet_resolution_AK8CHS = JME::JetResolution(jertextAK8_);

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

  int nvtxgood =0 ;
  for(std::vector<reco::Vertex>::const_iterator vtx = vertices->begin(); vtx != vertices->end(); ++vtx) {
    bool isFake = (vtx->chi2()==0 && vtx->ndof()==0);   //// bool isFake = vtx->isFake();  // for AOD
    if ( !isFake &&  vtx->ndof()>=4. && vtx->position().Rho()<=2.0 && fabs(vtx->position().Z())<=24.0) {
      nvtxgood++;
    }
  }
  if (verbose_) cout<<"nvtx "<<nvtx<<" nvtxgood "<<nvtxgood<<endl;

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

  if (verbose_) std::cout<<"nPU true  "<<nPU<<"  PU weight: "<<puweight<<std::endl;

  h_NtrueIntPU         ->Fill(nPU);
  h_NPV                ->Fill(nvtx);
  h_NPVreweighted      ->Fill(nvtx,puweight);
  h_NPVgood            ->Fill(nvtxgood);
  h_NPVgoodreweighted  ->Fill(nvtxgood,puweight);


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
    iEvent.getByToken(lheSrc_, EvtHandle);

    if (EvtHandle.isValid()){
      double centralWgt = EvtHandle->weights()[0].wgt;

      //Q^2 uncertainties
      if (verbose_) cout << "Calculating Q^2 uncertainties." << endl;
      double maxQ2wgt_frac = 1;
      double minQ2wgt_frac = 1;
      
      for (unsigned int iLHE = 0; iLHE < 9; ++iLHE){
        if (iLHE != 5 && iLHE != 7){
          double Q2wgt = EvtHandle->weights()[iLHE].wgt;
          double Q2wgt_frac = Q2wgt/(centralWgt);
          if (verbose_) cout << "Q^2 Weight: " << Q2wgt << "  Fractional Q^2 Weight: " << Q2wgt_frac << endl;
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
        if (verbose_){cout << "PDF Fractional weights: "; 
        for (unsigned int i_lhePDF = PDFstart; i_lhePDF < PDFend; ++i_lhePDF){
          NNPDF3wgt = EvtHandle->weights()[i_lhePDF].wgt;
          NNPDF3wgt_frac = NNPDF3wgt/(centralWgt);
          NNPDF3wgtAvg += NNPDF3wgt_frac;
          
            // cout << "-----" << endl;
            // cout << i_lhePDF - PDFstart
            if (verbose_)cout<< NNPDF3wgt_frac<<", ";
            // cout << "-----" << endl;
            // cout << "" << endl;
          }
        }
        if (verbose_) cout<<endl;

        NNPDF3wgtAvg = NNPDF3wgtAvg/(PDFend - PDFstart);
            
        for (unsigned int i_lhePDF = PDFstart; i_lhePDF < PDFend; ++i_lhePDF){
          NNPDF3wgt = EvtHandle->weights()[i_lhePDF].wgt;
          NNPDF3wgt_frac = NNPDF3wgt/(centralWgt);
          NNPDF3wgtRMS += (NNPDF3wgt_frac - NNPDF3wgtAvg)*(NNPDF3wgt_frac - NNPDF3wgtAvg);
        }

        NNPDF3wgtRMS = sqrt(NNPDF3wgtRMS/(PDFend - PDFstart - 1));
        NNPDF3wgt_up = 1.0 + NNPDF3wgtRMS;
        NNPDF3wgt_down = 1.0 - NNPDF3wgtRMS;

        if (verbose_) cout <<"NNPDF3wgtAvg = "<< NNPDF3wgtAvg<<" NNPDF3wgtRMS = "<< NNPDF3wgtRMS<<endl;

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

  edm::Handle<GenEventInfoProduct> genEventInfo;
  iEvent.getByToken(pdfToken_, genEventInfo);
  double evWeight = 1.0 ;
  double qScale = 1.0 ;
  double pthat = 1.0 ;
  if (genEventInfo.isValid())
  {
    evWeight = genEventInfo->weight();
    qScale   = genEventInfo->qScale();
    // const std::vector<double>& binningValues = genEventInfo->binningValues(); // in case of Pythia6, this will be pypars/pari(17)
    pthat    = (genEventInfo->hasBinningValues() ? (genEventInfo->binningValues())[0] : 0.0);
    // std::vector<double>& evtWeights = genEventInfo->weights();
    // if (evWeight < 0 ) cout<<"NEGATIVE"<<endl;

    // I'll do this at the tree reading stage
    // if (evWeight < 0 ){
    //   if (verbose_) cout<<"evWeight < 0. evWeight *= -1.0"<<endl;;  
    //   evWeight *= -1.0
    // }
    if(verbose_) cout<<"GenEventInfo: qScale = "<<qScale<<" pthat = "<<pthat<<" evWeight = "<<evWeight<<" 1/pow(pthat/15,4.5) "<<1/pow(pthat/15,4.5)<<endl;
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
  if (verbose_) cout<<"rho = "<<rho<<endl;
  
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
  TLorentzVector mu1_p4;
  bool mu0_isTight=false;
  bool mu0_isMedium=false;
  bool mu0_isHighPt = false;
  double mu0_iso04=0;
  int count_mu=0;

  std::vector<reco::CandidatePtr> muFootprint;

  for (const pat::Muon &mu : *muons) {

      // use only loose muons 
      if (mu.pt() < 30 || !mu.isLooseMuon() || fabs( mu.eta() ) > 2.1) continue;
      // use the leading muon only
      if (count_mu==0){
        mu0_p4.SetPtEtaPhiM( mu.pt(), mu.eta(), mu.phi(), mu.mass() );

        // Moriond 2017 short term instructions for medium muon ID
        //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideMuonIdRun2
        bool goodGlob   = mu.isGlobalMuon() && 
                          mu.globalTrack()->normalizedChi2() < 3 && 
                          mu.combinedQuality().chi2LocalPosition < 12 && 
                          mu.combinedQuality().trkKink < 20; 
        bool isMediumBF = muon::isLooseMuon(mu) && 
                          mu.innerTrack()->validFraction() > 0.49 && 
                          muon::segmentCompatibility(mu) > (goodGlob ? 0.303 : 0.451); 
        bool isMediumStandard = muon::isMediumMuon(mu);
        bool isMedium   = false;
        if      (iEvent.isRealData() && runNumber <= 278808) isMedium = isMediumBF;       // Data B-F
        else if (iEvent.isRealData() && runNumber  > 278808) isMedium = isMediumStandard; // Data G-H
        else isMedium = isMediumStandard;  // MC 
        if ( isMedium ) mu0_isMedium = true;

        // Tight ID
        if ( mu.isTightMuon(PV) ) mu0_isTight = true;

        // HighPt ID
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
        if (verbose_) cout<<"Muon pT "<<mu.pt()<<" iso04 "<<iso04<<" isMedium "<<mu0_isTight<<" isTight "<<mu0_isTight<<" isHighPt "<<mu0_isHighPt<<endl;
      } 
      if (count_mu==1){
        mu1_p4.SetPtEtaPhiM( mu.pt(), mu.eta(), mu.phi(), mu.mass() );
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
  edm::Handle<edm::View<pat::Electron>> electrons; //Collection
  iEvent.getByToken(electronToken_, electrons);

  // Get the conversions collection
  edm::Handle<reco::ConversionCollection> conversions;
  iEvent.getByToken(conversionsToken_, conversions);

  // Get the electron ID data from the event stream.
  // Note: this implies that the VID ID modules have been run upstream.
  // If you need more info, check with the EGM group.
  // edm::Handle<edm::ValueMap<bool> > ele_id_decisions;
  // iEvent.getByToken(eleIdMapToken_ ,ele_id_decisions);
 
  // Full cut flow info for one of the working points:
  // edm::Handle<edm::ValueMap<vid::CutFlowResult> > ele_id_cutflow_data;
  // iEvent.getByToken(eleIdFullInfoMapToken_,ele_id_cutflow_data);

  // edm::Handle<edm::ValueMap<bool> > pass_eleId_HLTpre  ;
  // edm::Handle<edm::ValueMap<bool> > pass_eleId_Loose   ;
  // edm::Handle<edm::ValueMap<bool> > pass_eleId_Medium  ;
  // edm::Handle<edm::ValueMap<bool> > pass_eleId_Tight   ;
  // edm::Handle<edm::ValueMap<bool> > pass_eleId_HEEP    ;
  // iEvent.getByToken(eleIdMapToken_HLTpre_   ,   pass_eleId_HLTpre  );
  // iEvent.getByToken(eleIdMapToken_Loose_    ,   pass_eleId_Loose   );
  // iEvent.getByToken(eleIdMapToken_Medium_   ,   pass_eleId_Medium  );
  // iEvent.getByToken(eleIdMapToken_Tight_    ,   pass_eleId_Tight   );
  // iEvent.getByToken(eleIdMapToken_HEEP_     ,   pass_eleId_HEEP    );

  edm::Handle<edm::ValueMap<vid::CutFlowResult> > cutflow_eleId_HLTpre  ;
  edm::Handle<edm::ValueMap<vid::CutFlowResult> > cutflow_eleId_Loose   ;
  edm::Handle<edm::ValueMap<vid::CutFlowResult> > cutflow_eleId_Medium  ;
  edm::Handle<edm::ValueMap<vid::CutFlowResult> > cutflow_eleId_Tight   ;
  edm::Handle<edm::ValueMap<vid::CutFlowResult> > cutflow_eleId_HEEP    ;
  iEvent.getByToken(eleIdFullInfoMapToken_HLTpre_   ,   cutflow_eleId_HLTpre   );
  iEvent.getByToken(eleIdFullInfoMapToken_Loose_    ,   cutflow_eleId_Loose   );
  iEvent.getByToken(eleIdFullInfoMapToken_Medium_   ,   cutflow_eleId_Medium  );
  iEvent.getByToken(eleIdFullInfoMapToken_Tight_    ,   cutflow_eleId_Tight   );
  iEvent.getByToken(eleIdFullInfoMapToken_HEEP_     ,   cutflow_eleId_HEEP    );

  TLorentzVector el0_p4;
  TLorentzVector el1_p4;
  Float_t el0_absiso           =0;
  Float_t el0_relIsoWithDBeta  =0;
  Float_t el0_absiso_EA        =0;
  Float_t el0_relIsoWithEA     =0;
  int el0_iso_passHLTpre    = 0;
  int el0_iso_passLoose     = 0;
  int el0_iso_passMedium    = 0;
  int el0_iso_passTight     = 0;
  int el0_iso_passHEEP      = 0;
  int el0_noiso_passLoose   = 0;
  int el0_noiso_passMedium  = 0;
  int el0_noiso_passTight   = 0;
  int el0_noiso_passHEEP    = 0;
  int count_el=0;

  std::vector<reco::CandidatePtr> elFootprint;

  for (size_t i = 0; i < electrons->size(); ++i){   
    const auto el = electrons->ptrAt(i);          // easier if we use ptrs for the id
    if (el->pt() < 50 || fabs(el->eta())>2.4 ) continue;

    // electron ID
    vid::CutFlowResult full_cutflow_HLTpre = (*cutflow_eleId_HLTpre )[el];
    vid::CutFlowResult full_cutflow_Loose  = (*cutflow_eleId_Loose  )[el];
    vid::CutFlowResult full_cutflow_Medium = (*cutflow_eleId_Medium )[el];
    vid::CutFlowResult full_cutflow_Tight  = (*cutflow_eleId_Tight  )[el];
    vid::CutFlowResult full_cutflow_HEEP   = (*cutflow_eleId_HEEP   )[el];

    bool iso_passHLTpre   =  full_cutflow_HLTpre.cutFlowPassed();
    bool iso_passLoose    =  full_cutflow_Loose .cutFlowPassed();
    bool iso_passMedium   =  full_cutflow_Medium.cutFlowPassed();
    bool iso_passTight    =  full_cutflow_Tight .cutFlowPassed();
    bool iso_passHEEP     =  full_cutflow_HEEP  .cutFlowPassed();

    // get electron ID without isolation cuts
    vid::CutFlowResult masked_cutflow_Loose  = full_cutflow_Loose     .getCutFlowResultMasking(7); // 7 = GsfEleEffAreaPFIsoCut_0
    vid::CutFlowResult masked_cutflow_Medium = full_cutflow_Medium    .getCutFlowResultMasking(7); // 7 = GsfEleEffAreaPFIsoCut_0
    vid::CutFlowResult masked_cutflow_Tight  = full_cutflow_Tight     .getCutFlowResultMasking(7); // 7 = GsfEleEffAreaPFIsoCut_0

    std::vector<std::string> maskCuts;
    // maskCuts.push_back("GsfEleTrkPtIsoCut_0");  // OLD HEEP v6 only
    maskCuts.push_back("GsfEleValueMapIsoRhoCut_0"); // new in HEEP v7
    maskCuts.push_back("GsfEleEmHadD1IsoRhoCut_0");
    vid::CutFlowResult masked_cutflow_HEEP   = full_cutflow_HEEP      .getCutFlowResultMasking(maskCuts);

    bool noiso_passLoose    =  masked_cutflow_Loose .cutFlowPassed();
    bool noiso_passMedium   =  masked_cutflow_Medium.cutFlowPassed();
    bool noiso_passTight    =  masked_cutflow_Tight .cutFlowPassed();
    bool noiso_passHEEP     =  masked_cutflow_HEEP  .cutFlowPassed();

    if (verbose_){
      cout<<"full_cutflow_Loose"<<endl;
      printCutFlowResult(full_cutflow_Loose);
      cout<<"masked_cutflow_Loose"<<endl;
      printCutFlowResult(masked_cutflow_Loose);
      cout<<"masked_cutflow_HEEP"<<endl;
      printCutFlowResult(masked_cutflow_HEEP);
    }


    bool electronEvent = noiso_passLoose || noiso_passHEEP;
    if (electronEvent){
      if (count_el==0){
        if (verbose_) cout<<"Electron pT "<<el->pt()<<endl;

        //calculate isolation variables    
        GsfElectron::PflowIsolationVariables pfIso = el->pfIsolationVariables();
        float absiso = pfIso.sumChargedHadronPt + max(0.0 , pfIso.sumNeutralHadronEt + pfIso.sumPhotonEt - 0.5 * pfIso.sumPUPt );
        float relIsoWithDBeta = absiso/el->pt();
        float eta = el->eta();

        float effArea = 0.;
        if(abs(eta)>0.0 && abs(eta)<=1.0) effArea = 0.1752;
        if(abs(eta)>1.0 && abs(eta)<=1.479) effArea = 0.1862;
        if(abs(eta)>1.479 && abs(eta)<=2.0) effArea = 0.1411;
        if(abs(eta)>2.0 && abs(eta)<=2.2) effArea = 0.1534;
        if(abs(eta)>2.2 && abs(eta)<=2.3) effArea = 0.1903;
        if(abs(eta)>2.3 && abs(eta)<=2.4) effArea = 0.2243;
        if(abs(eta)>2.4 && abs(eta)<=2.5) effArea = 0.2687;

        float absiso_EA = pfIso.sumChargedHadronPt + max(0.0 , pfIso.sumNeutralHadronEt + pfIso.sumPhotonEt - rho * effArea );
        float relIsoWithEA = absiso_EA/el->pt();

        el0_p4.SetPtEtaPhiM( el->pt(), el->eta(), el->phi(), el->mass() );
        el0_absiso           = absiso;
        el0_relIsoWithDBeta  = relIsoWithDBeta;
        el0_absiso_EA        = absiso_EA;
        el0_relIsoWithEA     = relIsoWithEA;

        el0_iso_passHLTpre    = (int) iso_passHLTpre   ;
        el0_iso_passLoose     = (int) iso_passLoose    ;
        el0_iso_passMedium    = (int) iso_passMedium   ;
        el0_iso_passTight     = (int) iso_passTight    ;
        el0_iso_passHEEP      = (int) iso_passHEEP     ;
        el0_noiso_passLoose   = (int) noiso_passLoose  ;
        el0_noiso_passMedium  = (int) noiso_passMedium ;
        el0_noiso_passTight   = (int) noiso_passTight  ;
        el0_noiso_passHEEP    = (int) noiso_passHEEP   ;

        for (unsigned int i = 0, n = el->numberOfSourceCandidatePtrs(); i < n; ++i) {
          elFootprint.push_back(el->sourceCandidatePtr(i));
        }
      } 
      if (count_el==1){
        el1_p4.SetPtEtaPhiM( el->pt(), el->eta(), el->phi(), el->mass() );
      }
      count_el++;
    }
    //printf("elec with pt %4.1f, supercluster eta %+5.3f, sigmaIetaIeta %.3f (%.3f with full5x5 shower shapes), lost hits %d, pass conv veto %d\n",
    //              el.pt(), el.superCluster()->eta(), el.sigmaIetaIeta(), el.full5x5_sigmaIetaIeta(), el.gsfTrack()->trackerExpectedHitsInner().numberOfLostHits(), el.passConversionVeto());
  }

  TLorentzVector lep0_p4;
  TLorentzVector lep1_p4;

  int count_lep = count_mu + count_el;
  if (count_lep==1){
    if (count_mu==1 && count_el==0)  lep0_p4 = mu0_p4;
    if (count_mu==0 && count_el==1)  lep0_p4 = el0_p4; 
  }
  if (count_lep==2){
    if (count_mu==2 && count_el==0) {
      lep0_p4 = mu0_p4;
      lep1_p4 = mu1_p4;
    }
    if (count_mu==0 && count_el==2) {
      lep0_p4 = el0_p4; 
      lep1_p4 = el1_p4; 

    }  
    if (count_mu==1 && count_el==1) { 
      lep0_p4 = el0_p4; 
      lep1_p4 = mu0_p4; 
    }
  } // end if 2 leptons loop

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

  int count_AK4 = 0;
  TLorentzVector AK4_dRMinLep_p4;
  TLorentzVector AK4_btagged_dRMinLep_p4;
  double AK4_dRMinLep_bdisc = -99;
  double AK4_btagged_dRMinLep_bdisc = -99;
  double AK4_dRMinLep_deltaR  = 99;
  double AK4_btagged_dRMinLep = 99;

  double AK4_dRMinLep_ptsmear    = 1; 
  double AK4_dRMinLep_ptsmearUp  = 1; 
  double AK4_dRMinLep_ptsmearDn  = 1; 
  double AK4_dRMinLep_ptuncorr   = 0; 
  double AK4_dRMinLep_corr       = 1;
  double AK4_dRMinLep_corrUp     = 1;
  double AK4_dRMinLep_corrDn     = 1;

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

  // vAK4pt    ->clear();
  // vAK4eta   ->clear();
  // vAK4phi   ->clear();
  // vAK4m     ->clear();
  // vAK4bdisc ->clear();

  // SemiLeptAK4pt    ->clear();
  // SemiLeptAK4eta   ->clear();
  // SemiLeptAK4phi   ->clear();
  // SemiLeptAK4m     ->clear();
  // SemiLeptAK4bdisc ->clear();

  if (verbose_) cout<<"AK4 jet loop"<<endl;

  for (const pat::Jet &ijet : *AK4MINI) {  
    
    if (ijet.pt()<15 || fabs(ijet.eta())>3.0) continue; 
    if (verbose_) cout<<" jet "<<count_AK4<<endl;
    count_AK4++;

    //------------------------------------
    // Remove leptons from AK4 jets
    //------------------------------------    
    auto uncorrJetObj = ijet.correctedJet(0);
    reco::Candidate::LorentzVector uncorrJet = ijet.correctedP4(0);
    // now loop on pf candidates
    //// Jet constituent indices for lepton matching
    std::vector<int> constituentIndices;
    auto jetConstituents = uncorrJetObj.daughterPtrVector();
    if ( verbose_ ) cout << "   -> before lepton cleaning uncorr pt,eta,phi,m = " << uncorrJet.pt() << ", " << uncorrJet.eta() << ", " << uncorrJet.phi() << ", " << uncorrJet.mass() << endl;
    for ( auto & constituent : jetConstituents ) {

      // If this constituent is part of a muon, remove the constituent's four vector
      if ( std::find(muFootprint.begin(), muFootprint.end(), constituent ) != muFootprint.end() ) {
        uncorrJet -= constituent->p4();
        if ( verbose_ ) cout << "     -> REMOVED part of muon" << endl;
        }
      // If this constituent is part of an electron, remove the constituent's four vector
      if ( std::find(elFootprint.begin(), elFootprint.end(), constituent ) != elFootprint.end() ) {
        uncorrJet -= constituent->p4();
        if ( verbose_ ) cout << "     -> REMOVED part of electron" << endl;
      }
    }
    if ( verbose_ ) cout << "   -> after lepton cleaning uncorr pt,eta,phi,m = " << uncorrJet.pt() << ", " << uncorrJet.eta() << ", " << uncorrJet.phi() << ", " << uncorrJet.mass() << endl;

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
      || ( fabs(eta) <= 3.0 && fabs(eta) > 2.7 && NHF < 0.98 && NEMF > 0.01 && NM > 2 ) 
      || ( fabs(eta)  > 3.0 && NEMF < 0.9 && NM > 10 );
    if (verbose_ && goodJet_looseJetID) cout<<"   -> goodJet "<<endl;

    if (!goodJet_looseJetID) {
      if(verbose_) cout<<"   -> bad AK4 jet. skip.  ( pt "<<ijet.pt()<<" eta "<<ijet.eta()<<" NumConst "<<NumConst<<" )"<<endl;
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
    if ( verbose_ ) cout << "   -> after JEC pt,eta,phi,m = " << corrJet.pt() << ", " << corrJet.eta() << ", " << corrJet.phi() << ", " << corrJet.mass() << endl;
    
    if (corrJet.pt()<15 ) continue;  

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

    if (verbose_) cout<<"   -> corr "<<corr<<" corrDn "<<corrDn<<" corrUp "<< corrUp<<endl;

    //------------------------------------
    // AK4 JER SF
    //------------------------------------
   
    double ptsmear   = 1;
    double ptsmearUp = 1;
    double ptsmearDn = 1;

    if (!iEvent.isRealData()) {
      if (verbose_) cout<<"   Get JER SF"<<endl;

      // get genjet
      double genpt = 0;
      TLorentzVector GenJetMatched;
      const reco::GenJet* genJet = ijet.genJet();
      bool foundgenjet = false;
      if (genJet) {
        foundgenjet=true;
        genpt = genJet->pt();
        GenJetMatched.SetPtEtaPhiM( genJet->pt(), genJet->eta(), genJet->phi(), genJet->mass() );
        if (verbose_) cout<<"      -> Found ak4 genJet pt "<<genJet->pt()<<" mass "<<genJet->mass()<<endl;
      }
      else{ if(verbose_)cout<<"      -> Did not find genJet"<<endl;}
    
      // Set parameters needed for jet resolution and scale factors
      JME::JetParameters jer_parameters;
      jer_parameters.setJetPt ( corrJet.pt()  );
      jer_parameters.setJetEta( corrJet.eta() );
      jer_parameters.setRho   ( rho           );

      // Get resolution
      double res = jet_resolution_AK4CHS.getResolution(jer_parameters); 

      // Get scale factors
      double jer_sf    = jer_scaler.getScaleFactor(jer_parameters                   );
      double jer_sf_up = jer_scaler.getScaleFactor(jer_parameters , Variation::UP   );
      double jer_sf_dn = jer_scaler.getScaleFactor(jer_parameters , Variation::DOWN );
      if (verbose_) std::cout << "      -> JER Scale factors (Nominal / Up / Down) : " << jer_sf << " / " << jer_sf_up << " / " << jer_sf_dn <<"    & Resolution :"<<res<< std::endl;
     
      // Get Smearings  
      // --- If well matched, smear based on GenJet, If not well matched,  gaussian smear based on resolution
      TLorentzVector AK4JetP4;
      AK4JetP4.SetPtEtaPhiM( corrJet.pt(), corrJet.eta(), corrJet.phi(), corrJet.mass() );
      double DeltaR_gen_reco  = AK4JetP4.DeltaR( GenJetMatched );
      double DeltaPt_gen_reco = AK4JetP4.Pt() - GenJetMatched.Pt()  ;
      double jet_distance_param = 0.4; 
      if (verbose_) cout<<"      -> gen pt "<<GenJetMatched.Pt()<<" reco pt "<<AK4JetP4.Pt()<<"  delta "<<DeltaPt_gen_reco<<endl;

      if (genJet && (DeltaR_gen_reco<jet_distance_param/2.0) && (std::abs(DeltaPt_gen_reco)<(3*res*AK4JetP4.Pt())) ) {
        if (verbose_) cout<<"      -> Well matched (recojet,genjet)"<<endl;
        double recopt    = corrJet.pt();
        // double genpt     = GenJetMatched.Perp();
        double deltapt   = (recopt-genpt)*(jer_sf-1.0);
        double deltaptUp = (recopt-genpt)*(jer_sf_up-1.0);
        double deltaptDn = (recopt-genpt)*(jer_sf_dn-1.0);

        ptsmear   = std::max((double)0.0, (recopt+deltapt)/recopt     );
        ptsmearUp = std::max((double)0.0, (recopt+deltaptUp)/recopt   );
        ptsmearDn = std::max((double)0.0, (recopt+deltaptDn)/recopt   );
      }
      else{
        if (verbose_){
          cout<<"      -> Not well matched. DeltaR_gen_reco "<<DeltaR_gen_reco<<" DeltaPt_gen_reco "<<DeltaPt_gen_reco<<" 3*res*AK4JetP4.Pt()) "<<3*res*AK4JetP4.Pt();
          if (!foundgenjet) cout<<". Did not find genjet"<<endl;
          else cout<<endl;
        }
        double sigma   = std::sqrt(jer_sf * jer_sf - 1)       * res ;  
        double sigmaUp = std::sqrt(jer_sf_up * jer_sf_up - 1) * res ;
        double sigmaDn = std::sqrt(jer_sf_dn * jer_sf_dn - 1) * res ;

        TRandom3 rand1(0);
        ptsmear   = std::max( (double)0.0, 1 + rand1.Gaus(0, sigma  ) );
        ptsmearUp = std::max( (double)0.0, 1 + rand1.Gaus(0, sigmaUp) );
        ptsmearDn = std::max( (double)0.0, 1 + rand1.Gaus(0, sigmaDn) );
      }
    }

    if (verbose_) cout<<"   -> ptsmear "<<ptsmear<<" ptsmearUp "<< ptsmearDn<<" ptsmearDn "<< ptsmearUp<<endl;

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
 
    //  if (corrJet.pt()>20 ){
    //   vAK4pt    ->push_back( corrJet.pt()    ); 
    //   vAK4eta   ->push_back( corrJet.eta()   ); 
    //   vAK4phi   ->push_back( corrJet.phi()   ); 
    //   vAK4m     ->push_back( corrJet.mass()  ); 
    //   vAK4bdisc ->push_back( bdisc           );

    //   SemiLeptAK4pt    ->push_back( corrJet.pt()    ); 
    //   SemiLeptAK4eta   ->push_back( corrJet.eta()   ); 
    //   SemiLeptAK4phi   ->push_back( corrJet.phi()   ); 
    //   SemiLeptAK4m     ->push_back( corrJet.mass()  ); 
    //   SemiLeptAK4bdisc ->push_back( bdisc           );
    // }  

    //------------------------------------
    // HT calculation
    //------------------------------------

    if (corrJet.pt()>30)            HT_AK4_pt30           +=   pt;
    if (corrUp * corrJet.pt()>30)   HT_AK4_pt30_corrUp    +=   corrUp * uncorrJet.pt();
    if (corrDn * corrJet.pt()>30)   HT_AK4_pt30_corrDn    +=   corrDn * uncorrJet.pt();
    if (ptsmear * corrJet.pt()>30)  HT_AK4_pt30_smearNom  +=   ptsmear * corrJet.pt();
    if (ptsmearUp* corrJet.pt()>30) HT_AK4_pt30_smearUp   +=   ptsmearUp * corrJet.pt();
    if (ptsmearDn* corrJet.pt()>30) HT_AK4_pt30_smearDn   +=   ptsmearDn * corrJet.pt();

    //------------------------------------
    // Find AK4 jet closest to lepton
    //------------------------------------ 
    double deltaRlep = deltaR(corrJet.eta(), corrJet.phi(), lep0_p4.Eta(), lep0_p4.Phi() );

    if (pt>25 && fabs(eta)<3.0 && goodJet_looseJetID){
      if (deltaRlep<AK4_dRMinLep_deltaR ){
        AK4_dRMinLep_deltaR = deltaRlep;
        AK4_dRMinLep_p4.SetPtEtaPhiM( pt, eta, phi, mass );
        AK4_dRMinLep_bdisc = bdisc;
        AK4_dRMinLep_ptsmear   = ptsmear;
        AK4_dRMinLep_ptsmearUp = ptsmearUp;
        AK4_dRMinLep_ptsmearDn = ptsmearDn;
        AK4_dRMinLep_ptuncorr  = uncorrJet.pt();
        AK4_dRMinLep_corr    = corr ;
        AK4_dRMinLep_corrUp  = corrUp ;
        AK4_dRMinLep_corrDn  = corrDn ;
      }
    }

    //------------------------------------
    // Find Loose b-tagged AK4 jet closest to lepton
    //------------------------------------ 
    if (pt>25. && fabs(eta)<3.0 && goodJet_looseJetID && bdisc> 0.5426  ){
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
    if (pt>25. && fabs(eta)<3.0 && goodJet_looseJetID){              
      if (deltaPhiLep<  3.14/2.0)
      {
        if (bdisc> 0.5426  ) ak4_btag_loose  = true;
        if (bdisc> 0.8484  ) ak4_btag_medium = true;
        if (bdisc> 0.9535  ) ak4_btag_tight  = true;
      }
    }
  } //end AK4 loop

  if (verbose_) {
    cout<<"AK4 summary:"<<endl;
    cout<<"  closest ak4 jet to lepton:"<<endl;
    cout<<"    pt =  "<<AK4_dRMinLep_p4.Perp()<<endl;
    cout<<"    bdisc =  "<<AK4_dRMinLep_bdisc<<endl;
    cout<<"    dR  = "<<AK4_dRMinLep_deltaR<<endl;
    cout<<"  closest loose b-tagged ak4 jet to lepton:"<<endl;
    cout<<"    pt =  "<<AK4_btagged_dRMinLep_p4.Perp()<<endl;
    cout<<"    bdisc =  "<<AK4_btagged_dRMinLep_bdisc<<endl;
    cout<<"    dR  = "<<AK4_btagged_dRMinLep<<endl;
    cout<<"  b-tagged jet in hemisphere around lepton?"<<endl;
    cout<<"    ak4_btag_loose  "<<ak4_btag_loose  <<endl; 
    cout<<"    ak4_btag_medium "<<ak4_btag_medium <<endl; 
    cout<<"    ak4_btag_tight  "<<ak4_btag_tight  <<endl; 

    cout<<"HT_AK4_pt30          "<<HT_AK4_pt30         <<endl;
    cout<<"HT_AK4_pt30_corrUp   "<<HT_AK4_pt30_corrUp  <<endl;
    cout<<"HT_AK4_pt30_corrDn   "<<HT_AK4_pt30_corrDn  <<endl;
    cout<<"HT_AK4_pt30_smearNom "<<HT_AK4_pt30_smearNom<<endl;
    cout<<"HT_AK4_pt30_smearUp  "<<HT_AK4_pt30_smearUp <<endl;
    cout<<"HT_AK4_pt30_smearDn  "<<HT_AK4_pt30_smearDn <<endl;
  }

  // PHOTONS (FANCY BIG WRITING!)

  if (runSemiLeptTree_) {

    v_photonPt              ->clear();
    v_photonSupClustEta     ->clear();
    v_photonSigIEtaIEta     ->clear();
    v_photonFullSigIEtaIEta ->clear();

    edm::Handle<edm::View<pat::Photon>> photons;
    iEvent.getByToken(photonToken_, photons);
    for (const pat::Photon &pho : *photons) {
      if (pho.pt() < 20 or pho.chargedHadronIso()/pho.pt() > 0.3) continue;

        v_photonPt              ->push_back( pho.pt() );
        v_photonSupClustEta     ->push_back( pho.superCluster()->eta() );
        v_photonSigIEtaIEta     ->push_back( pho.sigmaIetaIeta() );
        v_photonFullSigIEtaIEta ->push_back( pho.full5x5_sigmaIetaIeta() );
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

  edm::Handle<pat::JetCollection> AK8CHSsub;
  edm::Handle<pat::JetCollection> AK8PUPPI;
  edm::Handle<pat::JetCollection> AK8PUPPIsub;
  if (useToolbox_){
    iEvent.getByToken( ak8CHSSoftDropSubjetsToken_   , AK8CHSsub);
    iEvent.getByToken( puppijetToken_ , AK8PUPPI );
    iEvent.getByToken( ak8PuppiSoftDropSubjetsToken_ , AK8PUPPIsub);
  }

  int count_AK8CHS = 0;
  // int count_AK8CHS_good = 0;
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
  TLorentzVector GenJetMatchedPuppi0;
  TLorentzVector GenJetMatchedPuppi1;


  double closestAK8_to_Jet0_dR=99;
  double closestAK8_to_Jet1_dR=99;
  TLorentzVector closestAK8_to_Jet0_P4;
  TLorentzVector closestAK8_to_Jet1_P4;
  double closestAK8_to_Jet0_bdisc=-10;
  double closestAK8_to_Jet1_bdisc=-10;


  if (verbose_) cout<<"\nAK8 jet loop"<<endl;

  v_AK8PuppiPt  ->clear();
  v_AK8PuppiEta ->clear();
  v_AK8PuppiPhi ->clear();
  v_AK8PuppiM   ->clear();
  v_AK8PuppiArea->clear();

  v_AK8PuppiSdPt  ->clear();
  v_AK8PuppiSdEta ->clear();
  v_AK8PuppiSdPhi ->clear();
  v_AK8PuppiSdM   ->clear();
  v_AK8PuppiSdCorr->clear();

  for (const pat::Jet &ijet : *AK8CHS) {
    // if (count_AK8CHS>1) break;
    if (count_AK8CHS==0 && ijet.pt()<30) break;
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
      || ( fabs(eta) <= 3.0 && fabs(eta) > 2.7 && NHF < 0.98 && NEMF > 0.01 && NM > 2 ) 
      || ( fabs(eta)  > 3.0 && NEMF < 0.9 && NM > 10 );

    if (verbose_ && goodJet_looseJetID) cout<<"   -> goodJet "<<endl;

    if (!goodJet_looseJetID) {
      if(verbose_) cout<<"   -> bad AK8 jet. skip.  ( pt "<<ijet.pt()<<" eta "<<ijet.eta()<<" NumConst "<<NumConst<<" )"<<endl;
      continue;
    }
    // count_AK8CHS_good ++;

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
    if (verbose_) cout<<"   -> uncorrected AK8 jet pt "<<uncorrJet.pt()<<" corrected jet pt "<<corrJet.pt()<<endl;
    
    TLorentzVector jet_p4;
    jet_p4.SetPtEtaPhiM( corrJet.pt(), corrJet.eta(), corrJet.phi(), corrJet.mass() );


    if ( jet_p4.Pt() < 30 ) continue;

    if(count_AK8CHS==0) AK8jet0_P4corr = jet_p4;
    if(count_AK8CHS==1) AK8jet1_P4corr = jet_p4;

    if(count_AK8CHS>1) {
      double DeltaR_Jet0  = AK8jet0_P4corr.DeltaR( jet_p4 );
      double DeltaR_Jet1  = AK8jet1_P4corr.DeltaR( jet_p4 );
      if (DeltaR_Jet0 < closestAK8_to_Jet0_dR) {
        closestAK8_to_Jet0_dR = DeltaR_Jet0;
        closestAK8_to_Jet0_P4 = jet_p4 ;
        closestAK8_to_Jet0_bdisc = ijet.bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"); ;
      }
      if (DeltaR_Jet1 < closestAK8_to_Jet1_dR) {
        closestAK8_to_Jet1_dR = DeltaR_Jet1;
        closestAK8_to_Jet1_P4 = jet_p4 ;
        closestAK8_to_Jet1_bdisc = ijet.bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"); ;
      }
    }
    // Only need 3rd jet and beyond to find jet 0 and jet1 nearest neighbors (above)
    if(count_AK8CHS>1) continue; 

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

    if (verbose_) cout<<"   -> corr "<<corr<<" corr_factor_L23res "<<corr_factor_L23res<<" corrDn_L123 "<<corrDn_L123<<" corrUp_L123 "<<corrUp_L123<<endl;

    //------------------------------------
    // AK8 JER SF
    //------------------------------------
  
    TLorentzVector GenJetMatched;
    double ptsmear   = 1;
    double ptsmearUp = 1;
    double ptsmearDn = 1;

    if (!iEvent.isRealData()) {
      if (verbose_) cout<<"   Get JER SF"<<endl;

      // get genjet
      double genpt = 0;
      const reco::GenJet* genJet = ijet.genJet();
      bool foundgenjet = false;
      if (genJet) {
        foundgenjet=true;
        genpt = genJet->pt();
        GenJetMatched.SetPtEtaPhiM( genJet->pt(), genJet->eta(), genJet->phi(), genJet->mass() );
        if (verbose_) cout<<"     -> found ak8 genJet pt "<<genJet->pt()<<" mass "<<genJet->mass()<<endl;
      }
      else{ if(verbose_)cout<<"     -> did not find ak8 genJet"<<endl;}
    
      // Set parameters needed for jet resolution and scale factors
      JME::JetParameters jer_parameters;
      jer_parameters.setJetPt ( corrJet.pt()  );
      jer_parameters.setJetEta( corrJet.eta() );
      jer_parameters.setRho   ( rho           );

      // Get resolution
      double res = jet_resolution_AK8CHS.getResolution(jer_parameters); 

      // Get scale factors
      double jer_sf    = jer_scaler.getScaleFactor(jer_parameters                   );
      double jer_sf_up = jer_scaler.getScaleFactor(jer_parameters , Variation::UP   );
      double jer_sf_dn = jer_scaler.getScaleFactor(jer_parameters , Variation::DOWN );
      if (verbose_) std::cout << "     -> JER Scale factors (Nominal / Up / Down) : " << jer_sf << " / " << jer_sf_up << " / " << jer_sf_dn <<"    & Resolution :"<<res<< std::endl;
     
      // Get Smearings  
      // --- If well matched, smear based on GenJet, If not well matched,  gaussian smear based on resolution
      TLorentzVector AK8JetP4;
      AK8JetP4.SetPtEtaPhiM( corrJet.pt(), corrJet.eta(), corrJet.phi(), corrJet.mass() );
      double DeltaR_gen_reco  = AK8JetP4.DeltaR( GenJetMatched );
      double DeltaPt_gen_reco = AK8JetP4.Pt() - GenJetMatched.Pt()  ;
      double jet_distance_param = 0.4; 
      if (verbose_) cout<<"     -> gen pt "<<GenJetMatched.Pt()<<" reco pt "<<AK8JetP4.Pt()<<"  delta "<<DeltaPt_gen_reco<<endl;

      if (genJet && (DeltaR_gen_reco<jet_distance_param/2.0) && (std::abs(DeltaPt_gen_reco)<(3*res*AK8JetP4.Pt())) ) {
        if (verbose_) cout<<"     -> Well matched"<<endl;
        double recopt    = corrJet.pt();
        // double genpt     = GenJetMatched.Perp();
        double deltapt   = (recopt-genpt)*(jer_sf-1.0);
        double deltaptUp = (recopt-genpt)*(jer_sf_up-1.0);
        double deltaptDn = (recopt-genpt)*(jer_sf_dn-1.0);

        ptsmear   = std::max((double)0.0, (recopt+deltapt)/recopt     );
        ptsmearUp = std::max((double)0.0, (recopt+deltaptUp)/recopt   );
        ptsmearDn = std::max((double)0.0, (recopt+deltaptDn)/recopt   );
      }
      else{
        if (verbose_){
          cout<<"     -> Not well matched. DeltaR_gen_reco "<<DeltaR_gen_reco<<" DeltaPt_gen_reco "<<DeltaPt_gen_reco<<" 3*res*AK4JetP4.Pt()) "<<3*res*AK8JetP4.Pt();
          if (!foundgenjet) cout<<". Did not find genjet"<<endl;
          else cout<<endl;
        }
        double sigma   = std::sqrt(jer_sf * jer_sf - 1)       * res ;  
        double sigmaUp = std::sqrt(jer_sf_up * jer_sf_up - 1) * res ;
        double sigmaDn = std::sqrt(jer_sf_dn * jer_sf_dn - 1) * res ;

        TRandom3 rand1(0);
        ptsmear   = std::max( (double)0.0, 1 + rand1.Gaus(0, sigma  ) );
        ptsmearUp = std::max( (double)0.0, 1 + rand1.Gaus(0, sigmaUp) );
        ptsmearDn = std::max( (double)0.0, 1 + rand1.Gaus(0, sigmaDn) );
      }
    }

    if (verbose_) cout<<"   -> ptsmear "<<ptsmear<<" ptsmearUp "<< ptsmearDn<<" ptsmearDn "<< ptsmearUp<<endl;

    //------------------------------------
    // AK8CHS variables 
    //------------------------------------
    // double pt           = corrJet.pt();
    // double mass         = corrJet.mass();
    // double eta          = corrJet.eta();
    // double phi          = corrJet.phi();
    // double rapidity     = ijet.rapidity();
    // double ndau         = ijet.numberOfDaughters();

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

    if (tau1!=0) tau21 = tau2/tau1;
    if (tau2!=0) tau32 = tau3/tau2;


    // //-----------
    // // get jet constituents
    // //-----------
    // std::vector<fastjet::PseudoJet> FJparticles;
    // for (unsigned i = 0; i < ijet.numberOfDaughters() ; i++){
    //   const reco::PFCandidate* this_constituent = dynamic_cast<const reco::PFCandidate*>(ijet.daughter(i));
    //   FJparticles.push_back( fastjet::PseudoJet( this_constituent->px(),
    //            this_constituent->py(),
    //          this_constituent->pz(),
    //          this_constituent->energy() ) );
    // }

    // //------------------------------------
    // // Recluster jet
    // //------------------------------------
    // double R = 0.8;
    // double maxrap = 5.0;
    // unsigned int n_repeat = 1; // default is 1
    // double ghost_area = 0.01; // this is the default
    // fastjet::GhostedAreaSpec area_spec(maxrap, n_repeat, ghost_area);       
    // //fastjet::AreaDefinition area_def(fastjet::active_area, area_spec);
    // fastjet::AreaDefinition area_def(fastjet::active_area_explicit_ghosts, area_spec);
    // fastjet::JetDefinition jet_def(fastjet::cambridge_algorithm, R);
    // fastjet::ClusterSequenceArea cs(FJparticles, jet_def, area_def);
    // vector<fastjet::PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());


    // double z_cut = 0.10;
    // double beta  = 0.0;
    // contrib::SoftDrop sd(beta, z_cut);
    // cout << "SoftDrop groomer is: " << sd.description() << endl;

    // for (unsigned jjet = 0; jjet < jets.size(); jjet++) {
    //   // Run SoftDrop and examine the output
    //   PseudoJet sd_jet = sd(jets[jjet]);
    //   cout <<"sd mass "<<sd_jet.m() << endl;
    //   // cout << "original    jet: " << jets[jjet] << endl;
    //   // cout << "SoftDropped jet: " << sd_jet << endl;

    //   assert(sd_jet != 0); //because soft drop is a groomer (not a tagger), it should always return a soft-dropped jet
       
    //   cout << "  delta_R between subjets: " << sd_jet.structure_of<contrib::SoftDrop>().delta_R() << endl;
    //   cout << "  symmetry measure(z):     " << sd_jet.structure_of<contrib::SoftDrop>().symmetry() << endl;
    //   cout << "  mass drop(mu):           " << sd_jet.structure_of<contrib::SoftDrop>().mu() << endl;
    // }

    //------------------------------------
    // AK8PUPPI variables 
    //------------------------------------

    double puppi_pt             = -99;     
    double puppi_mass           = -99;     
    double puppi_eta            = -99;     
    double puppi_phi            = -99;     
    double puppi_area           = -99;     
    double puppi_tau1           = -99;     
    double puppi_tau2           = -99;     
    double puppi_tau3           = -99;     
    double puppi_tau4           = -99;     
    double puppi_prunedMass     = -1;     
    double puppi_trimmedMass    = -1;     
    // double puppi_softDropMass   = -1;     

    TLorentzVector AK8PUPPI_P4uncorr;
    TLorentzVector GenJetMatchedPuppi; 

    double puppi_CHF    = -99;
    double puppi_NHF    = -99;
    double puppi_CM     = -99;
    double puppi_NM     = -99;
    double puppi_NEF    = -99;
    double puppi_CEF    = -99;
    double puppi_MF     = -99;
    double puppi_Mult   = -99;
 
    // If you're getting jet variables from miniAOD
    if (!useToolbox_){
      puppi_pt           = ijet.userFloat("ak8PFJetsPuppiValueMap:pt");
      puppi_mass         = ijet.userFloat("ak8PFJetsPuppiValueMap:mass");
      puppi_eta          = ijet.userFloat("ak8PFJetsPuppiValueMap:eta");
      puppi_phi          = ijet.userFloat("ak8PFJetsPuppiValueMap:phi");
      puppi_tau1         = ijet.userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau1");
      puppi_tau2         = ijet.userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau2");
      puppi_tau3         = ijet.userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau3");
    }

    // If you've clustered AK8PUPPI using the toolbox, match the Puppi jets to AK8CHS and save the puppi variables

    double minDR_pup_chs = 99;
    if (useToolbox_){
      if (verbose_)  cout<<"   Puppi jet loop (toolbox)"<<endl; 
      int count_puppi_jet = 0;
      for (const pat::Jet &ipup : *AK8PUPPI) {  
        if (verbose_)  cout<<"    puppi jet "<<count_puppi_jet<<" uncorr "<<ipup.correctedP4(0).pt()<<" corr "<<ipup.pt()<<endl;
        double deltaRpup = deltaR(ijet.eta(), ijet.phi(), ipup.eta(), ipup.phi() );
        if (deltaRpup< minDR_pup_chs){
          minDR_pup_chs = deltaRpup;
          if (verbose_)  cout<<"      -> clostest puppi jet so far: deltaRpup "<<deltaRpup<<endl;
          if (deltaRpup<1.0){
            if (verbose_)  cout<<"      -> passes dR"<<endl;
            puppi_pt           = ipup.correctedP4(0).pt();
            puppi_mass         = ipup.correctedP4(0).mass();
            puppi_eta          = ipup.correctedP4(0).eta();
            puppi_phi          = ipup.correctedP4(0).phi();

            puppi_area         = ipup.jetArea();
            puppi_prunedMass   = ipup.userFloat("ak8PFJetsPuppiPrunedMass");
            puppi_trimmedMass  = ipup.userFloat("ak8PFJetsPuppiTrimmedMass");
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

            if (!iEvent.isRealData()){
              const reco::GenJet* genJet = ipup.genJet();
              if (genJet) {
                GenJetMatchedPuppi.SetPtEtaPhiM( genJet->pt(), genJet->eta(), genJet->phi(), genJet->mass() );
                if (verbose_) cout<<"      -> ak8puppi genJet pt "<<genJet->pt()<<" mass "<<genJet->mass()<<endl;
              }
            }
          }
        }
        count_puppi_jet++;
      }
    }
    AK8PUPPI_P4uncorr.SetPtEtaPhiM(puppi_pt, puppi_eta, puppi_phi, puppi_mass );
    if ( count_AK8CHS==0 ) GenJetMatchedPuppi0 = GenJetMatchedPuppi;
    if ( count_AK8CHS==1 ) GenJetMatchedPuppi1 = GenJetMatchedPuppi;

    if (minDR_pup_chs>1.0 && verbose_) cout<<"   Did not find matching PUPPI jet. Setting PUPPI variables to -99"<<endl;
    if (minDR_pup_chs<1.0 && verbose_) cout<<"   Found matching PUPPI jet with pt "<<puppi_pt<<" and mass " <<puppi_mass<<endl;

    double puppi_tau21        = 99;
    double puppi_tau32        = 99;
    if (puppi_tau1!=0) puppi_tau21 = puppi_tau2/puppi_tau1;
    if (puppi_tau2!=0) puppi_tau32 = puppi_tau3/puppi_tau2;

    //------------------------------------
    // AK8PUPPI JEC L23 correction
    //------------------------------------

    JetCorrectorAK8pup->setJetEta( puppi_eta );
    JetCorrectorAK8pup->setJetPt ( puppi_pt );
    JetCorrectorAK8pup->setJetE  ( AK8PUPPI_P4uncorr.E() );
    JetCorrectorAK8pup->setJetA  ( puppi_area );
    JetCorrectorAK8pup->setRho   ( rho );
    JetCorrectorAK8pup->setNPV   ( nvtx );
    // getSubCorrections member function returns the vector of the subcorrections UP to the given level. For example in the example above, factors[0] is the L1 correction and factors[3] is the L1+L2+L3+Residual correction. 
    vector<float> factorsAK8pup = JetCorrectorAK8pup->getSubCorrections();
    float corr_factorAK8pup_L1      = 1.0;
    float corr_factorAK8pup_L12     = 1.0;
    float corr_factorAK8pup_L123    = 1.0;
    float corr_factorAK8pup_L123res = 1.0;
    if (factors.size() > 0) corr_factorAK8pup_L1       = factorsAK8pup[0];
    if (factors.size() > 1) corr_factorAK8pup_L12      = factorsAK8pup[1];
    if (factors.size() > 2) corr_factorAK8pup_L123     = factorsAK8pup[2];
    if (factors.size() > 3) corr_factorAK8pup_L123res  = factorsAK8pup[3];
    double corr_factorAK8pup_L2 = corr_factorAK8pup_L12/corr_factorAK8pup_L1;
    double corr_factorAK8pup_L3 = corr_factorAK8pup_L123/corr_factorAK8pup_L12;
    double corr_factorAK8pup_res = corr_factorAK8pup_L123res/corr_factorAK8pup_L123;
    //double corr_factor_L23 = corr_factor_L2*corr_factor_L3;
    double corr_factorAK8pup_L23res = corr_factorAK8pup_L2*corr_factorAK8pup_L3*corr_factorAK8pup_res;

    TLorentzVector AK8PUPPI_P4corr;
    AK8PUPPI_P4corr = corr_factorAK8pup_L23res *  AK8PUPPI_P4uncorr;

    if(count_AK8CHS==0) PUPPIjet0_P4corr = AK8PUPPI_P4corr;
    if(count_AK8CHS==1) PUPPIjet1_P4corr = AK8PUPPI_P4corr;


    //------------------------------------
    // AK8PUPPI JEC uncertainty
    //------------------------------------
    double corrDn_pup_L23  = 1.0;
    double corrUp_pup_L23  = 1.0;

    if (puppi_pt>10){   //make sure puppi jet was found and filled
        JetCorrUncertAK8pup->setJetPhi(  puppi_phi  );
        JetCorrUncertAK8pup->setJetEta(  puppi_eta  );
        JetCorrUncertAK8pup->setJetPt(   puppi_pt * corr_factorAK8pup_L23res   );
        corrDn_pup_L23   = corr_factorAK8pup_L23res - JetCorrUncertAK8pup->getUncertainty(0);
        JetCorrUncertAK8pup->setJetPhi(   puppi_phi  );
        JetCorrUncertAK8pup->setJetEta(   puppi_eta  );
        JetCorrUncertAK8pup->setJetPt(    puppi_pt * corr_factorAK8pup_L23res   );
        corrUp_pup_L23   = corr_factorAK8pup_L23res + JetCorrUncertAK8pup->getUncertainty(1);;
    }
    if (verbose_){
      cout<<"    -> puppi uncorr pt "<<AK8PUPPI_P4uncorr.Perp()<<" corr pt "<<AK8PUPPI_P4corr.Perp() <<endl;
      cout<<"    -> corr L2L3res " <<corr_factorAK8pup_L23res<<" corr_factorAK8pup_L1 "<<corr_factorAK8pup_L1<<" corrDn_pup_L23"<<corrDn_pup_L23<<" corrUp_pup_L23 "<<corrUp_pup_L23<<endl;
    }

    //------------------------------------
    // AK8PUPPI JER SF
    //------------------------------------
    TLorentzVector GenJetMatched_Pup;

    double pup_ptsmear   = 1;
    double pup_ptsmearUp = 1;
    double pup_ptsmearDn = 1;
    if (!iEvent.isRealData()) {
      double jer_sf    = jer_scaler.getScaleFactor({{JME::Binning::JetEta, puppi_eta  }});
      double jer_sf_up = jer_scaler.getScaleFactor({{JME::Binning::JetEta, puppi_eta  }}, Variation::UP);
      double jer_sf_dn = jer_scaler.getScaleFactor({{JME::Binning::JetEta, puppi_eta  }}, Variation::DOWN);
      if (verbose_) std::cout << "   PUPPI JER Scale factors (Nominal / Up / Down) : " << jer_sf << " / " << jer_sf_up << " / " << jer_sf_dn << std::endl;
      double recopt    = AK8PUPPI_P4corr.Perp();
      double genpt     = GenJetMatched.Perp();
      double deltapt   = (recopt-genpt)*(jer_sf-1.0);
      double deltaptUp = (recopt-genpt)*(jer_sf_up-1.0);
      double deltaptDn = (recopt-genpt)*(jer_sf_dn-1.0);
      pup_ptsmear   = std::max((double)0.0, (recopt+deltapt)/recopt     );
      pup_ptsmearUp = std::max((double)0.0, (recopt+deltaptUp)/recopt   );
      pup_ptsmearDn = std::max((double)0.0, (recopt+deltaptDn)/recopt   );

      if (verbose_){
        cout<<"    -> AK8PUPPI JER recopt  "<<recopt <<endl;  
        cout<<"    -> AK8PUPPI JER genpt   "<<genpt  <<endl;  
        cout<<"    -> AK8PUPPI JER deltapt "<<deltapt<<endl;  
        cout<<"    -> AK8PUPPI JER ptsmear "<<pup_ptsmear<<endl;
        cout<<"    -> AK8PUPPI JER pup_ptsmearUp "<<pup_ptsmearUp<<endl;
        cout<<"    -> AK8PUPPI JER pup_ptsmearDn "<<pup_ptsmearDn<<endl;
      }
    }

    //------------------------------------
    // SoftDrop subjets
    //------------------------------------
    TLorentzVector sub0_P4_uncorr           ;
    TLorentzVector sub0_P4_L23res           ;
    // TLorentzVector sub0_P4_L23resCorrUp     ;
    // TLorentzVector sub0_P4_L23resCorrDn     ;
    // TLorentzVector sub0_P4_L23resPtSmear    ;
    // TLorentzVector sub0_P4_L23resPtSmearUp  ;
    // TLorentzVector sub0_P4_L23resPtSmearDn  ;
    TLorentzVector sub0_P4_L123res          ;
    // TLorentzVector sub0_P4_L123resCorrUp    ;
    // TLorentzVector sub0_P4_L123resCorrDn    ;

    TLorentzVector sub1_P4_uncorr           ;
    TLorentzVector sub1_P4_L23res           ;
    // TLorentzVector sub1_P4_L23resCorrUp     ;
    // TLorentzVector sub1_P4_L23resCorrDn     ;
    // TLorentzVector sub1_P4_L23resPtSmear    ;
    // TLorentzVector sub1_P4_L23resPtSmearUp  ;
    // TLorentzVector sub1_P4_L23resPtSmearDn  ;
    TLorentzVector sub1_P4_L123res          ;
    // TLorentzVector sub1_P4_L123resCorrUp    ;
    // TLorentzVector sub1_P4_L123resCorrDn    ;

    double sub0_area  = 0;
    double sub0_tau1  = 0;
    double sub0_tau2  = 0;
    double sub0_tau3  = 0;
    double sub0_flav_hadron  = 0;
    double sub0_flav_parton  = 0;
    double sub0_bdisc = 0;
    double sub0_genpt = 0;
    double sub1_area  = 0;
    double sub1_tau1  = 0;
    double sub1_tau2  = 0;
    double sub1_tau3  = 0;
    double sub1_flav_hadron  = 0;
    double sub1_flav_parton  = 0;
    double sub1_bdisc = 0;
    double sub1_genpt = 0;
    double mostMassiveSDsubjetMass = 0;
    int count_SD =0;

    int nsubjets_chs = 0;
    int nsubjets_pup = 0;

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
        
        // //------------------------------------
        // // subjet JEC uncertainty
        // //------------------------------------
        // double subjet_corrDn_L23 =   1.0;
        // double subjet_corrDn_L123 = 1.0;
        // JetCorrUncertAK4chs->setJetPhi(  corrSubjetL123res.phi()  );
        // JetCorrUncertAK4chs->setJetEta(  corrSubjetL123res.eta()  );
        // JetCorrUncertAK4chs->setJetPt(   corrSubjetL123res.pt()   );
        // double corrDn_temp2 = JetCorrUncertAK4chs->getUncertainty(0);
        // subjet_corrDn_L23   = subjet_corr_factor_L23res - corrDn_temp2;
        // subjet_corrDn_L123  = subjet_corr_factor_L123res_full - corrDn_temp2;

        // double subjet_corrUp_L23   = 1.0;
        // double subjet_corrUp_L123 = 1.0;
        // JetCorrUncertAK4chs->setJetPhi(  corrSubjetL123res.phi()  );
        // JetCorrUncertAK4chs->setJetEta(  corrSubjetL123res.eta()  );
        // JetCorrUncertAK4chs->setJetPt(   corrSubjetL123res.pt()   );
        // double corrUp_temp2 = JetCorrUncertAK4chs->getUncertainty(1);
        // subjet_corrUp_L23   = subjet_corr_factor_L23res + corrUp_temp2;
        // subjet_corrUp_L123  = subjet_corr_factor_L123res_full + corrUp_temp2;

        // reco::Candidate::LorentzVector corrSubjetL123resCorrDn  = subjet_corrDn_L123  * uncorrSubjet;
        // reco::Candidate::LorentzVector corrSubjetL123resCorrUp  = subjet_corrUp_L123  * uncorrSubjet;
        // reco::Candidate::LorentzVector corrSubjetL23resCorrDn   = subjet_corrDn_L23   * uncorrSubjet;
        // reco::Candidate::LorentzVector corrSubjetL23resCorrUp   = subjet_corrUp_L23   * uncorrSubjet;
     

        //------------------------------------
        // subjet values for Tree
        //------------------------------------
        if (count_SD==0){
          sub0_P4_uncorr            .SetPtEtaPhiM( subjetPt, subjetEta, subjetPhi, subjetMass);
          sub0_P4_L123res           .SetPtEtaPhiM( corrSubjetL123res.pt()   , corrSubjetL123res.eta()   , corrSubjetL123res.phi()   , corrSubjetL123res.mass()    );
          sub0_P4_L23res            .SetPtEtaPhiM( corrSubjetL23res.pt()    , corrSubjetL23res.eta()    , corrSubjetL23res.phi()    , corrSubjetL23res.mass()     );
          // sub0_P4_L123resCorrUp    .SetPtEtaPhiM( corrSubjetL123resCorrUp.pt() , corrSubjetL123resCorrUp.eta() , corrSubjetL123resCorrUp.phi() , corrSubjetL123resCorrUp.mass()  );
          // sub0_P4_L23resCorrUp     .SetPtEtaPhiM( corrSubjetL23resCorrUp.pt()  , corrSubjetL23resCorrUp.eta()  , corrSubjetL23resCorrUp.phi()  , corrSubjetL23resCorrUp.mass()   );
          // sub0_P4_L123resCorrDn    .SetPtEtaPhiM( corrSubjetL123resCorrDn.pt() , corrSubjetL123resCorrDn.eta() , corrSubjetL123resCorrDn.phi() , corrSubjetL123resCorrUp.mass()  );
          // sub0_P4_L23resCorrDn     .SetPtEtaPhiM( corrSubjetL23resCorrDn.pt()  , corrSubjetL23resCorrDn.eta()  , corrSubjetL23resCorrDn.phi()  , corrSubjetL23res.mass()     );
          sub0_area   = it->jetArea() ;
          sub0_flav_parton   = it->partonFlavour();
          sub0_flav_hadron   = it->hadronFlavour();
          sub0_bdisc  = subjetBdisc;
        }
        if (count_SD==1) {
          sub1_P4_uncorr          .SetPtEtaPhiM( subjetPt, subjetEta, subjetPhi, subjetMass);
          sub1_P4_L123res         .SetPtEtaPhiM( corrSubjetL123res.pt()   , corrSubjetL123res.eta()   , corrSubjetL123res.phi()   , corrSubjetL123res.mass()    );
          sub1_P4_L23res          .SetPtEtaPhiM( corrSubjetL23res.pt()    , corrSubjetL23res.eta()    , corrSubjetL23res.phi()    , corrSubjetL23res.mass()     );
          // sub1_P4_L123resCorrUp  .SetPtEtaPhiM( corrSubjetL123resCorrUp.pt() , corrSubjetL123resCorrUp.eta() , corrSubjetL123resCorrUp.phi() , corrSubjetL123resCorrUp.mass()  );
          // sub1_P4_L23resCorrUp   .SetPtEtaPhiM( corrSubjetL23resCorrUp.pt()  , corrSubjetL23resCorrUp.eta()  , corrSubjetL23resCorrUp.phi()  , corrSubjetL23resCorrUp.mass()   );
          // sub1_P4_L123resCorrDn  .SetPtEtaPhiM( corrSubjetL123resCorrDn.pt() , corrSubjetL123resCorrDn.eta() , corrSubjetL123resCorrDn.phi() , corrSubjetL123resCorrUp.mass()  );
          // sub1_P4_L23resCorrDn   .SetPtEtaPhiM( corrSubjetL23resCorrDn.pt()  , corrSubjetL23resCorrDn.eta()  , corrSubjetL23resCorrDn.phi()  , corrSubjetL23res.mass()     );
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
      if (verbose_) cout<<"   Toolbox AK8 jets. Find chs softdrop subjets "<<endl;
   
      int count_all_subjets =0;
      int count_matched_subjets =0;
      double closest_DR = 99;
      double closest_i = -1;
      double second_closest_DR = 99;
      double second_closest_i  = -1;

      // Loop once to find the subjets closest to the AK8 jet
      for (const pat::Jet &isub : *AK8CHSsub) {  
  
        double subjetPt       = isub.correctedP4(0).pt();
        double subjetEta      = isub.correctedP4(0).eta();
        double subjetPhi      = isub.correctedP4(0).phi();
        double subjetMass     = isub.correctedP4(0).mass();
        // double subjetBdisc    = isub.bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"); 

        double deltaRsubjetJet = deltaR(ijet.eta(), ijet.phi(), subjetEta, subjetPhi);

        if (verbose_) cout<<"     Subjet "<<count_all_subjets<<"   "<<subjetMass<<" "<<subjetPt<<" "<<deltaRsubjetJet<<endl;

        if (deltaRsubjetJet<closest_DR){
          second_closest_DR = closest_DR;
          closest_DR        = deltaRsubjetJet;
          second_closest_i  = closest_i;
          closest_i         = count_all_subjets;
        }
        else if (deltaRsubjetJet<second_closest_DR){
          second_closest_DR = deltaRsubjetJet ;
          second_closest_i  = count_all_subjets;
        }
        count_all_subjets++;
      }
      // Loop a second time. If one of the two closest subjets matches the dR requirement save its infromation. Subjet 0 = hardest.
      count_all_subjets =0;
      for (const pat::Jet &isub : *AK8CHSsub) {  
        
  
        double subjetPt       = isub.correctedP4(0).pt();
        double subjetEta      = isub.correctedP4(0).eta();
        double subjetPhi      = isub.correctedP4(0).phi();
        double subjetMass     = isub.correctedP4(0).mass();
        double subjetBdisc    = isub.bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"); 

        double deltaRsubjetJet = deltaR(ijet.eta(), ijet.phi(), subjetEta, subjetPhi);

        if (verbose_) cout<<"     Subjet "<<count_all_subjets<<"   "<<subjetMass<<" "<<subjetPt<<" "<<deltaRsubjetJet<<endl;

        if ( count_all_subjets==closest_i || count_all_subjets==second_closest_i ){
          if (verbose_) cout<<"      -> one of two closest "<<endl;
          if (deltaRsubjetJet<0.8){
            nsubjets_chs++;
            if (verbose_) cout<<"      -> dR matched subjet with mass "<< subjetMass<<endl;

            count_matched_subjets++;
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
            if (verbose_) cout<<"        -> subjet corr: L1 "<<subjet_corr_factor_L1<<" L23 "<<subjet_corr_factor_L23<<" L23res "<<subjet_corr_factor_L23res<<" L123res "<<subjet_corr_factor_L123res<<endl;
            reco::Candidate::LorentzVector corrSubjetL23res   = subjet_corr_factor_L23res * uncorrSubjet;
            
            // //------------------------------------
            // // subjet JEC uncertainty
            // //------------------------------------
            // double subjet_corrDn_L23 =   1.0;
            // double subjet_corrDn_L123 = 1.0;
            // JetCorrUncertAK4chs->setJetPhi(  corrSubjetL123res.phi()  );
            // JetCorrUncertAK4chs->setJetEta(  corrSubjetL123res.eta()  );
            // JetCorrUncertAK4chs->setJetPt(   corrSubjetL123res.pt()   );
            // double corrDn_temp2 = JetCorrUncertAK4chs->getUncertainty(0);
            // subjet_corrDn_L23   = subjet_corr_factor_L23res - corrDn_temp2;
            // subjet_corrDn_L123  = subjet_corr_factor_L123res_full - corrDn_temp2;

            // double subjet_corrUp_L23   = 1.0;
            // double subjet_corrUp_L123 = 1.0;
            // JetCorrUncertAK4chs->setJetPhi(  corrSubjetL123res.phi()  );
            // JetCorrUncertAK4chs->setJetEta(  corrSubjetL123res.eta()  );
            // JetCorrUncertAK4chs->setJetPt(   corrSubjetL123res.pt()   );
            // double corrUp_temp2 = JetCorrUncertAK4chs->getUncertainty(1);
            // subjet_corrUp_L23   = subjet_corr_factor_L23res + corrUp_temp2;
            // subjet_corrUp_L123  = subjet_corr_factor_L123res_full + corrUp_temp2;

            // reco::Candidate::LorentzVector corrSubjetL123resCorrDn  = subjet_corrDn_L123  * uncorrSubjet;
            // reco::Candidate::LorentzVector corrSubjetL123resCorrUp  = subjet_corrUp_L123  * uncorrSubjet;
            // reco::Candidate::LorentzVector corrSubjetL23resCorrDn   = subjet_corrDn_L23   * uncorrSubjet;
            // reco::Candidate::LorentzVector corrSubjetL23resCorrUp   = subjet_corrUp_L23   * uncorrSubjet;
           
            // //------------------------------------
            // // subjet JER SF
            // //------------------------------------

            // Doesn't work. Matched gensubjets don't match well

            // TLorentzVector GenSubJet;
            // double ptsmear   = 1;
            // double ptsmearUp = 1;
            // double ptsmearDn = 1;
            // if (!iEvent.isRealData()){
            //   const reco::GenJet* genJet = isub.genJet();
            //   if (genJet) {
            //     GenSubJet.SetPtEtaPhiM( genJet->pt(), genJet->eta(), genJet->phi(), genJet->mass() );
            //     if (verbose_) cout<<"  SD subjet genJet pt "<<genJet->pt()<<" mass "<<genJet->mass()<<" reco pt "<<subjetPt<<" reco mass "<<subjetMass<<endl;
            //   }
            //   double jer_sf    = jer_scaler.getScaleFactor({{JME::Binning::JetEta, corrSubjetL23res.eta()}});
            //   double jer_sf_up = jer_scaler.getScaleFactor({{JME::Binning::JetEta, corrSubjetL23res.eta()}}, Variation::UP);
            //   double jer_sf_dn = jer_scaler.getScaleFactor({{JME::Binning::JetEta, corrSubjetL23res.eta()}}, Variation::DOWN);
            //   if (verbose_) std::cout << " SD subjet JER Scale factors (Nominal / Up / Down) : " << jer_sf << " / " << jer_sf_up << " / " << jer_sf_dn << std::endl;
            //   double recopt    = corrSubjetL23res.pt();
            //   double genpt     = GenJetMatched.Perp();
            //   double deltapt   = (recopt-genpt)*(jer_sf-1.0);
            //   double deltaptUp = (recopt-genpt)*(jer_sf_up-1.0);
            //   double deltaptDn = (recopt-genpt)*(jer_sf_dn-1.0);
            //   ptsmear   = std::max((double)0.0, (recopt+deltapt)/recopt     );
            //   ptsmearUp = std::max((double)0.0, (recopt+deltaptUp)/recopt   );
            //   ptsmearDn = std::max((double)0.0, (recopt+deltaptDn)/recopt   );
            //   if (verbose_) std::cout<<" SD subjet ptsmear "<<ptsmear<<" ptsmearUp "<<ptsmearUp<<" ptsmearDn "<<ptsmearDn<<endl;
            // }
            // reco::Candidate::LorentzVector corrSubjetL23resPtSmear   = ptsmear * corrSubjetL23res ;
            // reco::Candidate::LorentzVector corrSubjetL23resPtSmearUp = ptsmearUp * corrSubjetL23res ;
            // reco::Candidate::LorentzVector corrSubjetL23resPtSmearDn = ptsmearDn * corrSubjetL23res ;

            //------------------------------------
            // subjet values for Tree
            //------------------------------------

            double gensubjetpt = 0;
            if (!iEvent.isRealData()){
              const reco::GenJet* genJet = isub.genJet();
              if (genJet) gensubjetpt = genJet->pt();
            }

            if (count_SD==0){
              sub0_P4_uncorr            .SetPtEtaPhiM( subjetPt, subjetEta, subjetPhi, subjetMass);
              sub0_P4_L23res            .SetPtEtaPhiM( corrSubjetL23res          .pt() , corrSubjetL23res          .eta()  , corrSubjetL23res          .phi()  , corrSubjetL23res          .mass()  );
              // sub0_P4_L23resCorrUp      .SetPtEtaPhiM( corrSubjetL23resCorrUp    .pt() , corrSubjetL23resCorrUp    .eta()  , corrSubjetL23resCorrUp    .phi()  , corrSubjetL23resCorrUp    .mass()  );
              // sub0_P4_L23resCorrDn      .SetPtEtaPhiM( corrSubjetL23resCorrDn    .pt() , corrSubjetL23resCorrDn    .eta()  , corrSubjetL23resCorrDn    .phi()  , corrSubjetL23resCorrDn    .mass()  );
              // sub0_P4_L23resPtSmear     .SetPtEtaPhiM( corrSubjetL23resPtSmear   .pt() , corrSubjetL23resPtSmear   .eta()  , corrSubjetL23resPtSmear   .phi()  , corrSubjetL23resPtSmear   .mass()  );
              // sub0_P4_L23resPtSmearUp   .SetPtEtaPhiM( corrSubjetL23resPtSmearUp .pt() , corrSubjetL23resPtSmearUp .eta()  , corrSubjetL23resPtSmearUp .phi()  , corrSubjetL23resPtSmearUp .mass()  );
              // sub0_P4_L23resPtSmearDn   .SetPtEtaPhiM( corrSubjetL23resPtSmearDn .pt() , corrSubjetL23resPtSmearDn .eta()  , corrSubjetL23resPtSmearDn .phi()  , corrSubjetL23resPtSmearDn .mass()  );
              sub0_P4_L123res           .SetPtEtaPhiM( corrSubjetL123res         .pt() , corrSubjetL123res         .eta()  , corrSubjetL123res         .phi()  , corrSubjetL123res         .mass()  );
              // sub0_P4_L123resCorrUp     .SetPtEtaPhiM( corrSubjetL123resCorrUp   .pt() , corrSubjetL123resCorrUp   .eta()  , corrSubjetL123resCorrUp   .phi()  , corrSubjetL123resCorrUp   .mass()  );
              // sub0_P4_L123resCorrDn     .SetPtEtaPhiM( corrSubjetL123resCorrDn   .pt() , corrSubjetL123resCorrDn   .eta()  , corrSubjetL123resCorrDn   .phi()  , corrSubjetL123resCorrDn   .mass()  );
   
              sub0_area          = isub.jetArea() ;
              sub0_flav_parton   = isub.partonFlavour();
              sub0_flav_hadron   = isub.hadronFlavour();
              sub0_bdisc         = subjetBdisc;
              // available from toolbox only (80X)
              sub0_tau1          = isub.userFloat("NsubjettinessAK8PFCHSSoftDropSubjets:tau1");
              sub0_tau2          = isub.userFloat("NsubjettinessAK8PFCHSSoftDropSubjets:tau2");
              sub0_tau3          = isub.userFloat("NsubjettinessAK8PFCHSSoftDropSubjets:tau3");
              sub0_genpt         = gensubjetpt;
            }
            if (count_SD==1) {
              sub1_P4_uncorr            .SetPtEtaPhiM( subjetPt, subjetEta, subjetPhi, subjetMass);
              sub1_P4_L23res            .SetPtEtaPhiM( corrSubjetL23res          .pt() , corrSubjetL23res          .eta()  , corrSubjetL23res          .phi()  , corrSubjetL23res          .mass()  );
              // sub1_P4_L23resCorrUp      .SetPtEtaPhiM( corrSubjetL23resCorrUp    .pt() , corrSubjetL23resCorrUp    .eta()  , corrSubjetL23resCorrUp    .phi()  , corrSubjetL23resCorrUp    .mass()  );
              // sub1_P4_L23resCorrDn      .SetPtEtaPhiM( corrSubjetL23resCorrDn    .pt() , corrSubjetL23resCorrDn    .eta()  , corrSubjetL23resCorrDn    .phi()  , corrSubjetL23resCorrDn    .mass()  );
              // sub1_P4_L23resPtSmear     .SetPtEtaPhiM( corrSubjetL23resPtSmear   .pt() , corrSubjetL23resPtSmear   .eta()  , corrSubjetL23resPtSmear   .phi()  , corrSubjetL23resPtSmear   .mass()  );
              // sub1_P4_L23resPtSmearUp   .SetPtEtaPhiM( corrSubjetL23resPtSmearUp .pt() , corrSubjetL23resPtSmearUp .eta()  , corrSubjetL23resPtSmearUp .phi()  , corrSubjetL23resPtSmearUp .mass()  );
              // sub1_P4_L23resPtSmearDn   .SetPtEtaPhiM( corrSubjetL23resPtSmearDn .pt() , corrSubjetL23resPtSmearDn .eta()  , corrSubjetL23resPtSmearDn .phi()  , corrSubjetL23resPtSmearDn .mass()  );
              sub1_P4_L123res           .SetPtEtaPhiM( corrSubjetL123res         .pt() , corrSubjetL123res         .eta()  , corrSubjetL123res         .phi()  , corrSubjetL123res         .mass()  );
              // sub1_P4_L123resCorrUp     .SetPtEtaPhiM( corrSubjetL123resCorrUp   .pt() , corrSubjetL123resCorrUp   .eta()  , corrSubjetL123resCorrUp   .phi()  , corrSubjetL123resCorrUp   .mass()  );
              // sub1_P4_L123resCorrDn     .SetPtEtaPhiM( corrSubjetL123resCorrDn   .pt() , corrSubjetL123resCorrDn   .eta()  , corrSubjetL123resCorrDn   .phi()  , corrSubjetL123resCorrDn   .mass()  );
   
              sub1_area          = isub.jetArea() ;
              sub1_flav_parton   = isub.partonFlavour();
              sub1_flav_hadron   = isub.hadronFlavour();
              sub1_bdisc         = subjetBdisc;
              // available from toolbox only (80X)
              sub1_tau1          = isub.userFloat("NsubjettinessAK8PFCHSSoftDropSubjets:tau1");
              sub1_tau2          = isub.userFloat("NsubjettinessAK8PFCHSSoftDropSubjets:tau2");
              sub1_tau3          = isub.userFloat("NsubjettinessAK8PFCHSSoftDropSubjets:tau3");
              sub1_genpt         = gensubjetpt;
            }
            if (subjetMass > mostMassiveSDsubjetMass) mostMassiveSDsubjetMass = subjetMass;

            if (verbose_) cout<<"        -> SD Subjet pt "<<subjetPt<<" Eta "<<subjetEta<<" deltaRsubjetJet "<<deltaRsubjetJet<<" Mass "<<subjetMass<<" corrMass "<<corrSubjetL23res.mass() <<" Bdisc "<<subjetBdisc<<endl;
            if (verbose_) cout<<"        ->    sub0_tau1 "<<sub0_tau1<<" sub0_tau2 "<<sub0_tau2<<" sub0_tau3 "<<sub0_tau3<<endl;
            count_SD++;

          }
        }
        count_all_subjets++;
      }
      if (verbose_) cout<<"     count_matched_subjets "<<count_matched_subjets<<endl;
      if (count_matched_subjets!=2 && verbose_ ) cout<<"     CHECKME"<<endl;
      if (verbose_) cout<<"     closest_DR "<<closest_DR<<endl;;
      if (verbose_) cout<<"     second_closest_DR "<<second_closest_DR<<endl;;
      if (verbose_) cout<<"     closest_i "<<closest_i<<endl;
      if (verbose_) cout<<"     second_closest_i "<<second_closest_i<<endl;

      
    }

    TLorentzVector sumSDsubjets_P4_uncorr           ;
    TLorentzVector sumSDsubjets_P4_L23res           ;
    // TLorentzVector sumSDsubjets_P4_L23resCorrUp     ;
    // TLorentzVector sumSDsubjets_P4_L23resCorrDn     ;
    // TLorentzVector sumSDsubjets_P4_L23resPtSmear    ;
    // TLorentzVector sumSDsubjets_P4_L23resPtSmearUp  ;
    // TLorentzVector sumSDsubjets_P4_L23resPtSmearDn  ;
    TLorentzVector sumSDsubjets_P4_L123res          ;
    // TLorentzVector sumSDsubjets_P4_L123resCorrDn    ;
    // TLorentzVector sumSDsubjets_P4_L123resCorrUp    ;

    if (count_SD>1){ 
      sumSDsubjets_P4_uncorr             = sub0_P4_uncorr              + sub1_P4_uncorr            ; 
      sumSDsubjets_P4_L23res             = sub0_P4_L23res              + sub1_P4_L23res            ; 
      // sumSDsubjets_P4_L23resCorrUp       = sub0_P4_L23resCorrUp        + sub1_P4_L23resCorrUp      ; 
      // sumSDsubjets_P4_L23resCorrDn       = sub0_P4_L23resCorrDn        + sub1_P4_L23resCorrDn      ; 
      // sumSDsubjets_P4_L23resPtSmear      = sub0_P4_L23resPtSmear       + sub1_P4_L23resPtSmear     ;
      // sumSDsubjets_P4_L23resPtSmearUp    = sub0_P4_L23resPtSmearUp     + sub1_P4_L23resPtSmearUp   ;
      // sumSDsubjets_P4_L23resPtSmearDn    = sub0_P4_L23resPtSmearDn     + sub1_P4_L23resPtSmearDn   ;
      sumSDsubjets_P4_L123res            = sub0_P4_L123res             + sub1_P4_L123res           ; 
      // sumSDsubjets_P4_L123resCorrUp      = sub0_P4_L123resCorrUp       + sub1_P4_L123resCorrUp     ; 
      // sumSDsubjets_P4_L123resCorrDn      = sub0_P4_L123resCorrDn       + sub1_P4_L123resCorrDn     ; 
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
    // TLorentzVector pup0_P4_L23resCorrUp     ;
    // TLorentzVector pup0_P4_L23resCorrDn     ;
    // TLorentzVector pup0_P4_L23resPtSmear    ;
    // TLorentzVector pup0_P4_L23resPtSmearUp  ;
    // TLorentzVector pup0_P4_L23resPtSmearDn  ;

    TLorentzVector pup1_P4_uncorr           ;
    TLorentzVector pup1_P4_L23res           ;
    // TLorentzVector pup1_P4_L23resCorrUp     ;
    // TLorentzVector pup1_P4_L23resCorrDn     ;
    // TLorentzVector pup1_P4_L23resPtSmear    ;
    // TLorentzVector pup1_P4_L23resPtSmearUp  ;
    // TLorentzVector pup1_P4_L23resPtSmearDn  ;


    double pup0_area  = 0;
    double pup0_tau1  = 0;
    double pup0_tau2  = 0;
    double pup0_tau3  = 0;
    double pup0_flav_hadron  = 0;
    double pup0_flav_parton  = 0;
    double pup0_bdisc = 0;
    double pup0_genpt = 0;
    double pup1_area  = 0;
    double pup1_tau1  = 0;
    double pup1_tau2  = 0;
    double pup1_tau3  = 0;
    double pup1_flav_hadron  = 0;
    double pup1_flav_parton  = 0;
    double pup1_bdisc = 0;
    double pup1_genpt = 0;
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

        // //------------------------------------
        // // PUPPI subjet JEC uncertainty
        // //------------------------------------
        // double subjet_corrDn_L23 =   1.0;
        // JetCorrUncertAK4pup->setJetPhi(  corrSubjetL23res.phi()  );
        // JetCorrUncertAK4pup->setJetEta(  corrSubjetL23res.eta()  );
        // JetCorrUncertAK4pup->setJetPt(   corrSubjetL23res.pt()   );
        // subjet_corrDn_L23   = subjet_corr_factor_L23res_full - JetCorrUncertAK4pup->getUncertainty(0);
        // double subjet_corrUp_L23 =   1.0;
        // JetCorrUncertAK4pup->setJetPhi(  corrSubjetL23res.phi()  );
        // JetCorrUncertAK4pup->setJetEta(  corrSubjetL23res.eta()  );
        // JetCorrUncertAK4pup->setJetPt(   corrSubjetL23res.pt()   );
        // subjet_corrUp_L23   = subjet_corr_factor_L23res_full + JetCorrUncertAK4pup->getUncertainty(1);

        // reco::Candidate::LorentzVector corrSubjetL23resCorrDn   = subjet_corrDn_L23   * uncorrSubjet;
        // reco::Candidate::LorentzVector corrSubjetL23resCorrUp   = subjet_corrUp_L23   * uncorrSubjet;
     
        //------------------------------------
        // subjet values for Tree
        //------------------------------------

        if (count_pup==0){
          pup0_P4_uncorr           .SetPtEtaPhiM( subjetPt, subjetEta, subjetPhi, subjetMass);
          pup0_P4_L23res           .SetPtEtaPhiM( corrSubjetL23res.pt()    , corrSubjetL23res.eta()    , corrSubjetL23res.phi()    , corrSubjetL23res.mass()     );
          // pup0_P4_L23resCorrUp    .SetPtEtaPhiM( corrSubjetL23resCorrUp.pt()  , corrSubjetL23resCorrUp.eta()  , corrSubjetL23resCorrUp.phi()  , corrSubjetL23resCorrUp.mass()   );
          // pup0_P4_L23resCorrDn    .SetPtEtaPhiM( corrSubjetL23resCorrDn.pt()  , corrSubjetL23resCorrDn.eta()  , corrSubjetL23resCorrDn.phi()  , corrSubjetL23res.mass()     );
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
          // pup1_P4_L23resCorrUp    .SetPtEtaPhiM( corrSubjetL23resCorrUp.pt()  , corrSubjetL23resCorrUp.eta()  , corrSubjetL23resCorrUp.phi()  , corrSubjetL23resCorrUp.mass()   );
          // pup1_P4_L23resCorrDn    .SetPtEtaPhiM( corrSubjetL23resCorrDn.pt()  , corrSubjetL23resCorrDn.eta()  , corrSubjetL23resCorrDn.phi()  , corrSubjetL23res.mass()     );
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
      if (verbose_) cout<<"   Toolbox AK8 jets. Find puppi softdrop subjets "<<endl;

 
      int count_all_subjets =0;
      int count_matched_subjets =0;
      double closest_DR = 99;
      double closest_i = -1;
      double second_closest_DR = 99;
      double second_closest_i  = -1;

      // Loop once to find the subjets closest to the AK8 jet
      for (const pat::Jet &isub : *AK8PUPPIsub) {  
  
        double subjetPt       = isub.correctedP4(0).pt();
        double subjetEta      = isub.correctedP4(0).eta();
        double subjetPhi      = isub.correctedP4(0).phi();
        double subjetMass     = isub.correctedP4(0).mass();
        // double subjetBdisc    = isub.bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"); 

        double deltaRsubjetJet = deltaR(puppi_eta, puppi_phi, subjetEta, subjetPhi);

        if (verbose_) cout<<"     PupSubjet "<<count_all_subjets<<"   "<<subjetMass<<" "<<subjetPt<<" "<<deltaRsubjetJet<<endl;

        if (deltaRsubjetJet<closest_DR){
          second_closest_DR = closest_DR;
          closest_DR        = deltaRsubjetJet;
          second_closest_i  = closest_i;
          closest_i         = count_all_subjets;
        }
        else if (deltaRsubjetJet<second_closest_DR){
          second_closest_DR = deltaRsubjetJet ;
          second_closest_i  = count_all_subjets;
        }
        count_all_subjets++;
      }

      // Loop a second time. If one of the two closest subjets matches the dR requirement save its infromation. Subjet 0 = hardest.
      count_all_subjets =0;
      for (const pat::Jet &isub : *AK8PUPPIsub) {  
        
  
        double subjetPt       = isub.correctedP4(0).pt();
        double subjetEta      = isub.correctedP4(0).eta();
        double subjetPhi      = isub.correctedP4(0).phi();
        double subjetMass     = isub.correctedP4(0).mass();
        double subjetBdisc    = isub.bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"); 

        double deltaRsubjetJet = deltaR(puppi_eta, puppi_phi, subjetEta, subjetPhi);

        if (verbose_) cout<<"     PupSubjet "<<count_all_subjets<<"   "<<subjetMass<<" "<<subjetPt<<" "<<deltaRsubjetJet<<endl;

        if ( count_all_subjets==closest_i || count_all_subjets==second_closest_i ){
          if (verbose_) cout<<"      -> one of two closest "<<endl;
          if (deltaRsubjetJet<0.8){
            nsubjets_pup++;
            if (verbose_) cout<<"      -> dR matched subjet with mass "<< subjetMass<<endl;

            count_matched_subjets++;

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

            // //------------------------------------
            // // PUPPI subjet JEC uncertainty
            // //------------------------------------
            // double subjet_corrDn_L23 =   1.0;
            // JetCorrUncertAK4pup->setJetPhi(  corrSubjetL23res.phi()  );
            // JetCorrUncertAK4pup->setJetEta(  corrSubjetL23res.eta()  );
            // JetCorrUncertAK4pup->setJetPt(   corrSubjetL23res.pt()   );
            // subjet_corrDn_L23   = subjet_corr_factor_L23res_full - JetCorrUncertAK4pup->getUncertainty(0);
            // double subjet_corrUp_L23 =   1.0;
            // JetCorrUncertAK4pup->setJetPhi(  corrSubjetL23res.phi()  );
            // JetCorrUncertAK4pup->setJetEta(  corrSubjetL23res.eta()  );
            // JetCorrUncertAK4pup->setJetPt(   corrSubjetL23res.pt()   );
            // subjet_corrUp_L23   = subjet_corr_factor_L23res_full + JetCorrUncertAK4pup->getUncertainty(1);

            // reco::Candidate::LorentzVector corrSubjetL23resCorrDn   = subjet_corrDn_L23   * uncorrSubjet;
            // reco::Candidate::LorentzVector corrSubjetL23resCorrUp   = subjet_corrUp_L23   * uncorrSubjet;
         
            // //------------------------------------
            // // subjet JER SF
            // //------------------------------------

            // Doesn't seem to work. Gen subjet from isub.genJet()  is not a good match (especially true for 2nd subjet). If i have the time try just smearing the jets with no gen info.

            // TLorentzVector GenSubJet;
            // double ptsmear   = 1;
            // double ptsmearUp = 1;
            // double ptsmearDn = 1;
            // if (!iEvent.isRealData()){
            //   const reco::GenJet* genJet = isub.genJet();
            //   if (genJet) {
            //     GenSubJet.SetPtEtaPhiM( genJet->pt(), genJet->eta(), genJet->phi(), genJet->mass() );
            //     if (verbose_) cout<<"  SD subjet genJet pt "<<genJet->pt()<<" mass "<<genJet->mass()<<" reco pt "<<subjetPt<<" reco mass "<<subjetMass<<endl;
            //   }
            //   double jer_sf    = jer_scaler.getScaleFactor({{JME::Binning::JetEta, corrSubjetL23res.eta()}});
            //   double jer_sf_up = jer_scaler.getScaleFactor({{JME::Binning::JetEta, corrSubjetL23res.eta()}}, Variation::UP);
            //   double jer_sf_dn = jer_scaler.getScaleFactor({{JME::Binning::JetEta, corrSubjetL23res.eta()}}, Variation::DOWN);
            //   if (verbose_) std::cout << " SD subjet JER Scale factors (Nominal / Up / Down) : " << jer_sf << " / " << jer_sf_up << " / " << jer_sf_dn << std::endl;
            //   double recopt    = corrSubjetL23res.pt();
            //   double genpt     = GenJetMatched.Perp();
            //   double deltapt   = (recopt-genpt)*(jer_sf-1.0);
            //   double deltaptUp = (recopt-genpt)*(jer_sf_up-1.0);
            //   double deltaptDn = (recopt-genpt)*(jer_sf_dn-1.0);

            //   cout<<"recopt     "<<recopt    <<endl; 
            //   cout<<"genpt      "<<genpt     <<endl; 
            //   cout<<"deltapt    "<<deltapt   <<endl; 

            //   cout<<"recopt + deltapt     "<<recopt +deltapt   <<endl; 
            //   cout<<"(recopt+deltapt)/recopt     "<<(recopt+deltapt)/recopt   <<endl; 

            //   ptsmear   = std::max((double)0.0, (recopt+deltapt)/recopt     );
            //   ptsmearUp = std::max((double)0.0, (recopt+deltaptUp)/recopt   );
            //   ptsmearDn = std::max((double)0.0, (recopt+deltaptDn)/recopt   );
            //   if (verbose_); std::cout<<" SD subjet ptsmear "<<ptsmear<<" ptsmearUp "<<ptsmearUp<<" ptsmearDn "<<ptsmearDn<<endl;
            // }
            // reco::Candidate::LorentzVector corrSubjetL23resPtSmear   = ptsmear   * corrSubjetL23res ;
            // reco::Candidate::LorentzVector corrSubjetL23resPtSmearUp = ptsmearUp * corrSubjetL23res ;
            // reco::Candidate::LorentzVector corrSubjetL23resPtSmearDn = ptsmearDn * corrSubjetL23res ;

            //------------------------------------
            // subjet values for Tree
            //------------------------------------

            double gensubjetpt = 0;
            if (!iEvent.isRealData()){
              const reco::GenJet* genJet = isub.genJet();
              if (genJet) gensubjetpt = genJet->pt();
            }

            if (count_pup==0){
              pup0_P4_uncorr            .SetPtEtaPhiM( subjetPt, subjetEta, subjetPhi, subjetMass);
              pup0_P4_L23res            .SetPtEtaPhiM( corrSubjetL23res          .pt() , corrSubjetL23res          .eta() , corrSubjetL23res          .phi() , corrSubjetL23res          .mass() );
              // pup0_P4_L23resCorrUp      .SetPtEtaPhiM( corrSubjetL23resCorrUp    .pt() , corrSubjetL23resCorrUp    .eta() , corrSubjetL23resCorrUp    .phi() , corrSubjetL23resCorrUp    .mass() );
              // pup0_P4_L23resCorrDn      .SetPtEtaPhiM( corrSubjetL23resCorrDn    .pt() , corrSubjetL23resCorrDn    .eta() , corrSubjetL23resCorrDn    .phi() , corrSubjetL23resCorrDn    .mass() );
              // pup0_P4_L23resPtSmear     .SetPtEtaPhiM( corrSubjetL23resPtSmear   .pt() , corrSubjetL23resPtSmear   .eta() , corrSubjetL23resPtSmear   .phi() , corrSubjetL23resPtSmear   .mass() );
              // pup0_P4_L23resPtSmearUp   .SetPtEtaPhiM( corrSubjetL23resPtSmearUp .pt() , corrSubjetL23resPtSmearUp .eta() , corrSubjetL23resPtSmearUp .phi() , corrSubjetL23resPtSmearUp .mass() );
              // pup0_P4_L23resPtSmearDn   .SetPtEtaPhiM( corrSubjetL23resPtSmearDn .pt() , corrSubjetL23resPtSmearDn .eta() , corrSubjetL23resPtSmearDn .phi() , corrSubjetL23resPtSmearDn .mass() );

              pup0_tau1   = isub.userFloat("NsubjettinessAK8PFPuppiSoftDropSubjets:tau1");
              pup0_tau2   = isub.userFloat("NsubjettinessAK8PFPuppiSoftDropSubjets:tau2");
              pup0_tau3   = isub.userFloat("NsubjettinessAK8PFPuppiSoftDropSubjets:tau3");
            
              pup0_flav_parton   = isub.partonFlavour();
              pup0_flav_hadron   = isub.hadronFlavour();
              pup0_area          = isub.jetArea() ;
              pup0_bdisc         = subjetBdisc;
              pup0_genpt         = gensubjetpt;
            }
            if (count_pup==1) {
              pup1_P4_uncorr            .SetPtEtaPhiM( subjetPt, subjetEta, subjetPhi, subjetMass);
              pup1_P4_L23res            .SetPtEtaPhiM( corrSubjetL23res          .pt() , corrSubjetL23res          .eta() , corrSubjetL23res          .phi() , corrSubjetL23res          .mass() );
              // pup1_P4_L23resCorrUp      .SetPtEtaPhiM( corrSubjetL23resCorrUp    .pt() , corrSubjetL23resCorrUp    .eta() , corrSubjetL23resCorrUp    .phi() , corrSubjetL23resCorrUp    .mass() );
              // pup1_P4_L23resCorrDn      .SetPtEtaPhiM( corrSubjetL23resCorrDn    .pt() , corrSubjetL23resCorrDn    .eta() , corrSubjetL23resCorrDn    .phi() , corrSubjetL23resCorrDn    .mass() );
              // pup1_P4_L23resPtSmear     .SetPtEtaPhiM( corrSubjetL23resPtSmear   .pt() , corrSubjetL23resPtSmear   .eta() , corrSubjetL23resPtSmear   .phi() , corrSubjetL23resPtSmear   .mass() );
              // pup1_P4_L23resPtSmearUp   .SetPtEtaPhiM( corrSubjetL23resPtSmearUp .pt() , corrSubjetL23resPtSmearUp .eta() , corrSubjetL23resPtSmearUp .phi() , corrSubjetL23resPtSmearUp .mass() );
              // pup1_P4_L23resPtSmearDn   .SetPtEtaPhiM( corrSubjetL23resPtSmearDn .pt() , corrSubjetL23resPtSmearDn .eta() , corrSubjetL23resPtSmearDn .phi() , corrSubjetL23resPtSmearDn .mass() );

              pup1_tau1   = isub.userFloat("NsubjettinessAK8PFPuppiSoftDropSubjets:tau1");
              pup1_tau2   = isub.userFloat("NsubjettinessAK8PFPuppiSoftDropSubjets:tau2");
              pup1_tau3   = isub.userFloat("NsubjettinessAK8PFPuppiSoftDropSubjets:tau3");
            
              pup1_flav_parton   = isub.partonFlavour();
              pup1_flav_hadron   = isub.hadronFlavour();
              pup1_area          = isub.jetArea() ;
              pup1_bdisc         = subjetBdisc;
              pup1_genpt         = gensubjetpt;
            }

            if (subjetMass > mostMassiveSDPUPPIsubjetMass) mostMassiveSDPUPPIsubjetMass = subjetMass;
            count_pup++;
            if (verbose_) cout<<"       -> SD Subjet pt "<<subjetPt<<" Eta "<<subjetEta<<" deltaRsubjetJet "<<deltaRsubjetJet<<" Mass "<<subjetMass<<" Bdisc "<<subjetBdisc<<endl; 

          }
        }
        count_all_subjets++;
      }
      if (verbose_) cout<<"     Puppi count_matched_subjets "<<count_matched_subjets<<endl;
      if (count_matched_subjets!=2 && verbose_ ) cout<<"     CHECKME"<<endl;
      if (verbose_) cout<<"     closest_DR "<<closest_DR<<endl;;
      if (verbose_) cout<<"     second_closest_DR "<<second_closest_DR<<endl;;
      if (verbose_) cout<<"     closest_i "<<closest_i<<endl;
      if (verbose_) cout<<"     second_closest_i "<<second_closest_i<<endl;
    }


    TLorentzVector sumPUPsubjets_P4_uncorr          ;
    TLorentzVector sumPUPsubjets_P4_L23res          ;
    // TLorentzVector sumPUPsubjets_P4_L23resCorrUp    ;
    // TLorentzVector sumPUPsubjets_P4_L23resCorrDn    ;
    // TLorentzVector sumPUPsubjets_P4_L23resPtSmear   ;
    // TLorentzVector sumPUPsubjets_P4_L23resPtSmearUp ;
    // TLorentzVector sumPUPsubjets_P4_L23resPtSmearDn ;
    if (count_SD>1){ 
      sumPUPsubjets_P4_uncorr            = pup0_P4_uncorr            + pup1_P4_uncorr            ; 
      sumPUPsubjets_P4_L23res            = pup0_P4_L23res            + pup1_P4_L23res            ; 
      // sumPUPsubjets_P4_L23resCorrUp      = pup0_P4_L23resCorrUp      + pup1_P4_L23resCorrUp      ; 
      // sumPUPsubjets_P4_L23resCorrDn      = pup0_P4_L23resCorrDn      + pup1_P4_L23resCorrDn      ; 
      // sumPUPsubjets_P4_L23resPtSmear     = pup0_P4_L23resPtSmear     + pup1_P4_L23resPtSmear     ; 
      // sumPUPsubjets_P4_L23resPtSmearUp   = pup0_P4_L23resPtSmearUp   + pup1_P4_L23resPtSmearUp   ; 
      // sumPUPsubjets_P4_L23resPtSmearDn   = pup0_P4_L23resPtSmearDn   + pup1_P4_L23resPtSmearDn   ; 
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

    //------------------------------------
    // Gen particle info
    //------------------------------------ 
    double deltaR_jet_t1 = 99;
    double deltaR_jet_t2 = 99;
    double deltaR_jet_p1 = 99;
    double deltaR_jet_p2 = 99;

    bool jet_matched_t1 = false;
    bool jet_matched_t2 = false;
    bool jet_matched_p1 = false;
    bool jet_matched_p2 = false;

    if (!iEvent.isRealData() and runGenLoop_) {
      deltaR_jet_t1 = jet_p4.DeltaR(t1_p4  );
      deltaR_jet_t2 = jet_p4.DeltaR(t2_p4  );
      deltaR_jet_p1 = jet_p4.DeltaR(hardest_parton_hardScatterOutgoing_p4        );
      deltaR_jet_p2 = jet_p4.DeltaR(second_hardest_parton_hardScatterOutgoing_p4 );
      if (deltaR_jet_t1<deltaR_jet_t2) jet_matched_t1 = true;
      if (deltaR_jet_t2<deltaR_jet_t1) jet_matched_t2 = true;
      if (deltaR_jet_p1<deltaR_jet_p2) jet_matched_p1 = true;
      if (deltaR_jet_p2<deltaR_jet_p1) jet_matched_p2 = true;
    } 

    //------------------------------------
    // Tree variables
    //------------------------------------ 

    // Jet 0
    if (runAllHadTree_ && count_AK8CHS==0){
      if (verbose_) cout<<"Put jet 0 variables in allhad tree"<<endl;
      
      // basic kinematic and ID variables
      Jet0PtRaw                              = uncorrJet.pt()      ;                 
      Jet0EtaRaw                             = uncorrJet.eta()     ;                  
      Jet0PhiRaw                             = uncorrJet.phi()     ;   
      Jet0MassRaw                            = uncorrJet.mass()    ;                                           
      // Jet0P                                  = corrJet.P()         ;        
      // Jet0Pt                                 = corrJet.pt()        ;                  
      // Jet0Eta                                = corrJet.eta()       ;                  
      // Jet0Phi                                = corrJet.phi()       ;                  
      // Jet0Rap                                = corrJet.Rapidity()  ;                  
      // Jet0Energy                             = corrJet.energy()    ;                  
      // Jet0Mass                               = corrJet.mass()      ;                    
      Jet0Area                               = ijet.jetArea()      ;                  
     
      Jet0CHF                                = ijet.chargedHadronEnergy() / uncorrJet.E()  ;                        
      Jet0NHF                                = ijet.neutralHadronEnergy() / uncorrJet.E()  ;                         
      Jet0CM                                 = ijet.chargedMultiplicity()  ;                         
      Jet0NM                                 = ijet.neutralMultiplicity()  ;                          
      Jet0NEF                                = ijet.neutralEmEnergy() / uncorrJet.E()  ;                            
      Jet0CEF                                = ijet.chargedEmEnergy() / uncorrJet.E()  ;                          
      Jet0MF                                 = ijet.muonEnergy() / uncorrJet.E()  ;                         
      Jet0Mult                               = ijet.numberOfDaughters() ;   

      Jet0NsubjetsSD                         = nsubjets_chs   ;
      Jet0NsubjetsSDPuppi                    = nsubjets_pup   ;
      // soft drop mass calculated from soft drop subjets                          
      Jet0SDmassRaw                          = sumSDsubjets_P4_uncorr   .M()    ;  
      Jet0SDetaRaw                           = sumSDsubjets_P4_uncorr   .Eta()  ;                    
      Jet0SDphiRaw                           = sumSDsubjets_P4_uncorr   .Phi()  ;  
      Jet0SDptRaw                            = sumSDsubjets_P4_uncorr   .Perp() ;  
  
      // experiment with JEC applied separately to each subjet
      Jet0SDmassSubjetCorrL23                      = sumSDsubjets_P4_L23res          .M()    ;   
      // Jet0SDmassSubjetCorrL23Up                    = sumSDsubjets_P4_L23resSubjetCorrUp    .M()    ;   
      // Jet0SDmassSubjetCorrL23Dn                    = sumSDsubjets_P4_L23resSubjetCorrDn    .M()    ; 
      Jet0SDmassSubjetCorrL123                     = sumSDsubjets_P4_L123res         .M()    ;  
      // Jet0SDmassSubjetCorrL123Up                   = sumSDsubjets_P4_L123resSubjetCorrUp   .M()    ;   
      // Jet0SDmassSubjetCorrL123Dn                   = sumSDsubjets_P4_L123resSubjetCorrDn   .M()    ;  
      // Jet0SDmassCorrL23Smear                 = sumSDsubjets_P4_L23resPtSmear   .M()    ;   // This doesn't work. Subjet genjets are not a good match.
      // Jet0SDmassCorrL23SmearUp               = sumSDsubjets_P4_L23resPtSmearUp .M()    ;
      // Jet0SDmassCorrL23SmearDn               = sumSDsubjets_P4_L23resPtSmearDn .M()    ;
      // Jet0SDptCorrL23                        = sumSDsubjets_P4_L23res          .Perp() ;  
      // Jet0SDptCorrL23Up                      = sumSDsubjets_P4_L23resCorrUp    .Perp() ;  
      // Jet0SDptCorrL23Dn                      = sumSDsubjets_P4_L23resCorrDn    .Perp() ;  
      // Jet0SDptCorrL123                       = sumSDsubjets_P4_L123res         .Perp() ;  
      // Jet0SDptCorrL123Up                     = sumSDsubjets_P4_L123resCorrUp   .Perp() ;  
      // Jet0SDptCorrL123Dn                     = sumSDsubjets_P4_L123resCorrDn   .Perp() ;  
      // Jet0SDptCorrL23Smear                   = sumSDsubjets_P4_L23resPtSmear   .Perp() ;
      // Jet0SDptCorrL23SmearUp                 = sumSDsubjets_P4_L23resPtSmearUp .Perp() ;
      // Jet0SDptCorrL23SmearDn                 = sumSDsubjets_P4_L23resPtSmearDn .Perp() ;
          
      // user floats from the toolbox
      // Jet0SDmass                             = softDropMass  ;   // soft Drop mass from miniAOD                 
      Jet0MassPruned                         = prunedMass    ;     
      Jet0MassTrimmed                        = trimmedMass   ;     
      Jet0Tau1                               = tau1          ;  
      Jet0Tau2                               = tau2          ;  
      Jet0Tau3                               = tau3          ;  
      Jet0Tau4                               = tau4          ;  
      Jet0Tau32                              = tau32         ;  
      Jet0Tau21                              = tau21         ;  

      // Softdrop subjet variables
      Jet0SDsubjet0bdisc                     = sub0_bdisc            ;  
      Jet0SDsubjet1bdisc                     = sub1_bdisc            ;   
      Jet0SDmaxbdisc                         = maxbdisc              ;
      Jet0SDmaxbdiscflavHadron               = maxbdiscflav_hadron   ;  
      Jet0SDmaxbdiscflavParton               = maxbdiscflav_parton   ;  
      Jet0SDsubjet0pt                        = sub0_P4_uncorr.Pt()   ;               
      Jet0SDsubjet0mass                      = sub0_P4_uncorr.M()    ;  
      Jet0SDsubjet0eta                       = sub0_P4_uncorr.Eta()  ;  
      Jet0SDsubjet0phi                       = sub0_P4_uncorr.Phi()  ;  
      Jet0SDsubjet0area                      = sub0_area             ;  
      Jet0SDsubjet0flavHadron                = sub0_flav_hadron      ;  
      Jet0SDsubjet0flavParton                = sub0_flav_parton      ;  
      Jet0SDsubjet0matchedgenjetpt           = sub0_genpt            ;  
      Jet0SDsubjet0tau1                      = sub0_tau1             ;  
      Jet0SDsubjet0tau2                      = sub0_tau2             ;  
      Jet0SDsubjet0tau3                      = sub0_tau3             ;  
      Jet0SDsubjet1pt                        = sub1_P4_uncorr.Pt()   ;                    
      Jet0SDsubjet1mass                      = sub1_P4_uncorr.M()    ; 
      Jet0SDsubjet1eta                       = sub1_P4_uncorr.Eta()  ;  
      Jet0SDsubjet1phi                       = sub1_P4_uncorr.Phi()  ;                     
      Jet0SDsubjet1area                      = sub1_area             ;                    
      Jet0SDsubjet1flavHadron                = sub1_flav_hadron      ;     
      Jet0SDsubjet1flavParton                = sub1_flav_parton      ;
      Jet0SDsubjet1matchedgenjetpt           = sub1_genpt            ;       
      Jet0SDsubjet1tau1                      = sub1_tau1             ;  
      Jet0SDsubjet1tau2                      = sub1_tau2             ;  
      Jet0SDsubjet1tau3                      = sub1_tau3             ; 

      // Angle between puppi jet and chs jet
      // Jet0DeltaRPuppi                        = minDR_pup_chs;       

      // Puppi jet kinematics (uncorrected) and ID variables
      // Jet0PuppiP                             = AK8PUPPI_P4uncorr.P()    ;                  
      Jet0PuppiPtRaw                            = puppi_pt   ;                  
      Jet0PuppiEtaRaw                           = puppi_eta  ;                   
      Jet0PuppiPhiRaw                           = puppi_phi  ;                  
      Jet0PuppiMassRaw                          = puppi_mass ;                  
      Jet0PuppiArea                          = puppi_area ;                  

      Jet0PuppiCHF                           = puppi_CHF   ; 
      Jet0PuppiNHF                           = puppi_NHF   ; 
      Jet0PuppiCM                            = puppi_CM    ; 
      Jet0PuppiNM                            = puppi_NM    ; 
      Jet0PuppiNEF                           = puppi_NEF   ; 
      Jet0PuppiCEF                           = puppi_CEF   ; 
      Jet0PuppiMF                            = puppi_MF    ; 
      Jet0PuppiMult                          = puppi_Mult  ; 

      // Puppi softdrop mass from puppi subjets ( JEC applied separately to each subjet )
      Jet0PuppiSDmassRaw                        = sumPUPsubjets_P4_uncorr           .M()   ;
      Jet0PuppiSDmassSubjetCorr              = sumPUPsubjets_P4_L23res           .M()   ;
      // Jet0PuppiSDmassSubjetCorrUp            = sumPUPsubjets_P4_L23resCorrUp     .M()   ;
      // Jet0PuppiSDmassSubjetCorrDn            = sumPUPsubjets_P4_L23resCorrDn     .M()   ;
      // Jet0PuppiSDmassSubjetCorrL23Smear            = sumPUPsubjets_P4_L23resPtSmear    .M()   ;
      // Jet0PuppiSDmassSubjetCorrL23SmearUp          = sumPUPsubjets_P4_L23resPtSmearUp  .M()   ;
      // Jet0PuppiSDmassSubjetCorrL23SmearDn          = sumPUPsubjets_P4_L23resPtSmearDn  .M()   ;
      Jet0PuppiSDptRaw                          = sumPUPsubjets_P4_uncorr           .Perp();
      // Jet0PuppiSDptSubjetCorr                = sumPUPsubjets_P4_L23res           .Perp();
      // Jet0PuppiSDptSubjetCorrUp              = sumPUPsubjets_P4_L23resCorrUp     .Perp();
      // Jet0PuppiSDptSubjetCorrDn              = sumPUPsubjets_P4_L23resCorrDn     .Perp();
      // Jet0PuppiSDptSubjetCorrL23Smear              = sumPUPsubjets_P4_L23resPtSmear    .Perp();
      // Jet0PuppiSDptSubjetCorrL23SmearUp            = sumPUPsubjets_P4_L23resPtSmearUp  .Perp();
      // Jet0PuppiSDptSubjetCorrL23SmearDn            = sumPUPsubjets_P4_L23resPtSmearDn  .Perp();
      Jet0PuppiSDetaRaw                         = sumPUPsubjets_P4_uncorr           .Eta() ;
      Jet0PuppiSDphiRaw                         = sumPUPsubjets_P4_uncorr           .Phi() ;

      // PUPPI user floats from the toolbox
      // Jet0PuppiSDmassUserFloat               = puppi_softDropMass ;
      Jet0PuppiMassPruned                    = puppi_prunedMass   ;
      Jet0PuppiMassTrimmed                   = puppi_trimmedMass  ; 
      Jet0PuppiTau1                          = puppi_tau1         ;                  
      Jet0PuppiTau2                          = puppi_tau2         ;                  
      Jet0PuppiTau3                          = puppi_tau3         ;                  
      Jet0PuppiTau4                          = puppi_tau4         ;                  
      Jet0PuppiTau32                         = puppi_tau32        ;                  
      Jet0PuppiTau21                         = puppi_tau21        ;   

      // PUPPI subjet variables               
      Jet0PuppiSDsubjet0bdisc                = pup0_bdisc                ;
      Jet0PuppiSDsubjet1bdisc                = pup1_bdisc                ;
      Jet0PuppiSDmaxbdisc                    = pup_maxbdisc              ;
      Jet0PuppiSDmaxbdiscflavHadron          = pup_maxbdiscflav_hadron   ;
      Jet0PuppiSDmaxbdiscflavParton          = pup_maxbdiscflav_parton   ;
      Jet0PuppiSDsubjet0pt                   = pup0_P4_uncorr.Pt()       ;
      Jet0PuppiSDsubjet0mass                 = pup0_P4_uncorr.M()        ;
      Jet0PuppiSDsubjet0eta                  = pup0_P4_uncorr.Eta()      ;
      Jet0PuppiSDsubjet0phi                  = pup0_P4_uncorr.Phi()      ;
      Jet0PuppiSDsubjet0area                 = pup0_area                 ;
      Jet0PuppiSDsubjet0flavHadron           = pup0_flav_hadron          ; 
      Jet0PuppiSDsubjet0flavParton           = pup0_flav_parton          ;
      Jet0PuppiSDsubjet0matchedgenjetpt      = pup0_genpt                ;       
      Jet0PuppiSDsubjet0tau1                 = pup0_tau1                 ;  
      Jet0PuppiSDsubjet0tau2                 = pup0_tau2                 ;  
      Jet0PuppiSDsubjet0tau3                 = pup0_tau3                 ; 
      Jet0PuppiSDsubjet1pt                   = pup1_P4_uncorr.Pt()       ;                 
      Jet0PuppiSDsubjet1mass                 = pup1_P4_uncorr.M()        ; 
      Jet0PuppiSDsubjet1eta                  = pup1_P4_uncorr.Eta()      ;
      Jet0PuppiSDsubjet1phi                  = pup1_P4_uncorr.Phi()      ;             
      Jet0PuppiSDsubjet1area                 = pup1_area                 ;              
      Jet0PuppiSDsubjet1flavHadron           = pup1_flav_hadron          ;   
      Jet0PuppiSDsubjet1flavParton           = pup1_flav_parton          ;   
      Jet0PuppiSDsubjet1matchedgenjetpt      = pup1_genpt                ;       
      Jet0PuppiSDsubjet1tau1                 = pup1_tau1                 ;  
      Jet0PuppiSDsubjet1tau2                 = pup1_tau2                 ;  
      Jet0PuppiSDsubjet1tau3                 = pup1_tau3                 ; 

      // AK8CHS JEC scale nom/up/down      
      Jet0CorrFactor                         = corr ;        
      Jet0CorrFactorUp                       = corrUp_L123 ;
      Jet0CorrFactorDn                       = corrDn_L123;
      // AK8CHS L2L3 JEC scale nom/up/down for groomed mass correction
      Jet0MassCorrFactor                     = corr_factor_L23res ;        
      Jet0MassCorrFactorUp                   = corrUp_L23 ;
      Jet0MassCorrFactorDn                   = corrDn_L23 ;
      // AK8CHS JER
      Jet0PtSmearFactor                      = ptsmear  ;
      Jet0PtSmearFactorUp                    = ptsmearUp;
      Jet0PtSmearFactorDn                    = ptsmearDn;         
      
      // AK8PUPPI JEC scale nom/up/down  (use for both full jet and groomed mass corrections)     
      Jet0PuppiCorrFactor                    = corr_factorAK8pup_L23res;          
      Jet0PuppiCorrFactorUp                  = corrUp_pup_L23;          
      Jet0PuppiCorrFactorDn                  = corrDn_pup_L23;    
      
      // AK8PUPPI JER
      Jet0PuppiPtSmearFactor                 = pup_ptsmear;          
      Jet0PuppiPtSmearFactorUp               = pup_ptsmearUp;          
      Jet0PuppiPtSmearFactorDn               = pup_ptsmearDn;  

      // AK8CHS JAR   
      // Jet0EtaScaleFactor                     = 1;          
      // Jet0PhiScaleFactor                     = 1;      

      // AK8CHS GenJet
      Jet0MatchedGenJetPt                    = GenJetMatched.Perp();       
      Jet0MatchedGenJetMass                  = GenJetMatched.M();   

      // AK8PUPPI GenJet
      Jet0PuppiMatchedGenJetPt               = GenJetMatchedPuppi.Perp();       
      Jet0PuppiMatchedGenJetMass             = GenJetMatchedPuppi.M();   
      // Jet0MatchedGenJetDR                 = GenJetMatched_dRmin;             


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

    // Jet 1
    if (runAllHadTree_ && count_AK8CHS==1){
      if (verbose_) cout<<"Put jet 1 variables in allhad tree"<<endl;

      // basic kinematic and ID variables
      Jet1PtRaw                              = uncorrJet.pt()      ;                 
      Jet1EtaRaw                             = uncorrJet.eta()     ;                  
      Jet1PhiRaw                             = uncorrJet.phi()     ;   
      Jet1MassRaw                            = uncorrJet.mass()    ;                                           
      // Jet1P                                  = corrJet.P()         ;        
      // Jet1Pt                                 = corrJet.pt()        ;                  
      // Jet1Eta                                = corrJet.eta()       ;                  
      // Jet1Phi                                = corrJet.phi()       ;                  
      // Jet1Rap                                = corrJet.Rapidity()  ;                  
      // Jet1Energy                             = corrJet.energy()    ;                  
      // Jet1Mass                               = corrJet.mass()      ;                    
      Jet1Area                               = ijet.jetArea()      ;                  
     
      Jet1CHF                                = ijet.chargedHadronEnergy() / uncorrJet.E()  ;                        
      Jet1NHF                                = ijet.neutralHadronEnergy() / uncorrJet.E()  ;                         
      Jet1CM                                 = ijet.chargedMultiplicity()  ;                         
      Jet1NM                                 = ijet.neutralMultiplicity()  ;                          
      Jet1NEF                                = ijet.neutralEmEnergy() / uncorrJet.E()  ;                            
      Jet1CEF                                = ijet.chargedEmEnergy() / uncorrJet.E()  ;                          
      Jet1MF                                 = ijet.muonEnergy() / uncorrJet.E()  ;                         
      Jet1Mult                               = ijet.numberOfDaughters() ;   

      // soft drop mass calculated from soft drop subjets                          
      Jet1SDmassRaw                          = sumSDsubjets_P4_uncorr   .M()    ;  
      Jet1SDetaRaw                           = sumSDsubjets_P4_uncorr   .Eta()  ;                    
      Jet1SDphiRaw                           = sumSDsubjets_P4_uncorr   .Phi()  ;  
      Jet1SDptRaw                            = sumSDsubjets_P4_uncorr   .Perp() ;  
  
      // experiment with JEC applied separately to each subjet
      Jet1SDmassSubjetCorrL23                      = sumSDsubjets_P4_L23res          .M()    ;   
      // Jet1SDmassSubjetCorrL23Up                    = sumSDsubjets_P4_L23resSubjetCorrUp    .M()    ;   
      // Jet1SDmassSubjetCorrL23Dn                    = sumSDsubjets_P4_L23resSubjetCorrDn    .M()    ; 
      Jet1SDmassSubjetCorrL123                     = sumSDsubjets_P4_L123res         .M()    ;  
      // Jet1SDmassCorrL123Up                   = sumSDsubjets_P4_L123resCorrUp   .M()    ;   
      // Jet1SDmassCorrL123Dn                   = sumSDsubjets_P4_L123resCorrDn   .M()    ;  
      // Jet1SDmassCorrL23Smear                 = sumSDsubjets_P4_L23resPtSmear   .M()    ;   // This doesn't work. Subjet genjets are not a good match.
      // Jet1SDmassCorrL23SmearUp               = sumSDsubjets_P4_L23resPtSmearUp .M()    ;
      // Jet1SDmassCorrL23SmearDn               = sumSDsubjets_P4_L23resPtSmearDn .M()    ;
      // Jet1SDptCorrL23                        = sumSDsubjets_P4_L23res          .Perp() ;  
      // Jet1SDptCorrL23Up                      = sumSDsubjets_P4_L23resCorrUp    .Perp() ;  
      // Jet1SDptCorrL23Dn                      = sumSDsubjets_P4_L23resCorrDn    .Perp() ;  
      // Jet1SDptCorrL123                       = sumSDsubjets_P4_L123res         .Perp() ;  
      // Jet1SDptCorrL123Up                     = sumSDsubjets_P4_L123resCorrUp   .Perp() ;  
      // Jet1SDptCorrL123Dn                     = sumSDsubjets_P4_L123resCorrDn   .Perp() ;  
      // Jet1SDptCorrL23Smear                   = sumSDsubjets_P4_L23resPtSmear   .Perp() ;
      // Jet1SDptCorrL23SmearUp                 = sumSDsubjets_P4_L23resPtSmearUp .Perp() ;
      // Jet1SDptCorrL23SmearDn                 = sumSDsubjets_P4_L23resPtSmearDn .Perp() ;
          
      // user floats from the toolbox
      Jet1SDmass                             = softDropMass  ;   // soft Drop mass from miniAOD                 
      Jet1MassPruned                         = prunedMass    ;     
      Jet1MassTrimmed                        = trimmedMass   ;     
      Jet1Tau1                               = tau1          ;  
      Jet1Tau2                               = tau2          ;  
      Jet1Tau3                               = tau3          ;  
      Jet1Tau4                               = tau4          ;  
      Jet1Tau32                              = tau32         ;  
      Jet1Tau21                              = tau21         ;  

      Jet1NsubjetsSD                         = nsubjets_chs   ;
      Jet1NsubjetsSDPuppi                    = nsubjets_pup   ;

      // Softdrop subjet variables
      Jet1SDsubjet0bdisc                     = sub0_bdisc            ;  
      Jet1SDsubjet1bdisc                     = sub1_bdisc            ;   
      Jet1SDmaxbdisc                         = maxbdisc              ;
      Jet1SDmaxbdiscflavHadron               = maxbdiscflav_hadron   ;  
      Jet1SDmaxbdiscflavParton               = maxbdiscflav_parton   ;  
      Jet1SDsubjet0pt                        = sub0_P4_uncorr.Pt()   ;               
      Jet1SDsubjet0mass                      = sub0_P4_uncorr.M()    ;  
      Jet1SDsubjet0eta                       = sub0_P4_uncorr.Eta()  ;  
      Jet1SDsubjet0phi                       = sub0_P4_uncorr.Phi()  ;  
      Jet1SDsubjet0area                      = sub0_area             ;  
      Jet1SDsubjet0flavHadron                = sub0_flav_hadron      ;  
      Jet1SDsubjet0flavParton                = sub0_flav_parton      ;  
      Jet1SDsubjet0matchedgenjetpt           = sub0_genpt            ;  
      Jet1SDsubjet0tau1                      = sub0_tau1             ;  
      Jet1SDsubjet0tau2                      = sub0_tau2             ;  
      Jet1SDsubjet0tau3                      = sub0_tau3             ;  
      Jet1SDsubjet1pt                        = sub1_P4_uncorr.Pt()   ;                    
      Jet1SDsubjet1mass                      = sub1_P4_uncorr.M()    ; 
      Jet1SDsubjet1eta                       = sub1_P4_uncorr.Eta()  ;  
      Jet1SDsubjet1phi                       = sub1_P4_uncorr.Phi()  ;                     
      Jet1SDsubjet1area                      = sub1_area             ;                    
      Jet1SDsubjet1flavHadron                = sub1_flav_hadron      ;     
      Jet1SDsubjet1flavParton                = sub1_flav_parton      ;
      Jet1SDsubjet1matchedgenjetpt           = sub1_genpt            ;       
      Jet1SDsubjet1tau1                      = sub1_tau1             ;  
      Jet1SDsubjet1tau2                      = sub1_tau2             ;  
      Jet1SDsubjet1tau3                      = sub1_tau3             ; 

      // Angle between puppi jet and chs jet
      // Jet1DeltaRPuppi                        = minDR_pup_chs;       

      // Puppi jet kinematics (uncorrected) and ID variables
      // Jet1PuppiP                             = AK8PUPPI_P4uncorr.P()    ;                  
      Jet1PuppiPtRaw                            = puppi_pt   ;                  
      Jet1PuppiEtaRaw                           = puppi_eta  ;                   
      Jet1PuppiPhiRaw                           = puppi_phi  ;                  
      Jet1PuppiMassRaw                          = puppi_mass ;                  
      Jet1PuppiArea                          = puppi_area ;                  

      Jet1PuppiCHF                           = puppi_CHF   ; 
      Jet1PuppiNHF                           = puppi_NHF   ; 
      Jet1PuppiCM                            = puppi_CM    ; 
      Jet1PuppiNM                            = puppi_NM    ; 
      Jet1PuppiNEF                           = puppi_NEF   ; 
      Jet1PuppiCEF                           = puppi_CEF   ; 
      Jet1PuppiMF                            = puppi_MF    ; 
      Jet1PuppiMult                          = puppi_Mult  ; 

      // Puppi softdrop mass from puppi subjets ( JEC applied separately to each subjet )
      Jet1PuppiSDmassRaw                        = sumPUPsubjets_P4_uncorr           .M()   ;
      Jet1PuppiSDmassSubjetCorr              = sumPUPsubjets_P4_L23res           .M()   ;
      // Jet1PuppiSDmassSubjetCorrUp            = sumPUPsubjets_P4_L23resCorrUp     .M()   ;
      // Jet1PuppiSDmassSubjetCorrDn            = sumPUPsubjets_P4_L23resCorrDn     .M()   ;
      // Jet1PuppiSDmassSubjetCorrL23Smear            = sumPUPsubjets_P4_L23resPtSmear    .M()   ;
      // Jet1PuppiSDmassSubjetCorrL23SmearUp          = sumPUPsubjets_P4_L23resPtSmearUp  .M()   ;
      // Jet1PuppiSDmassSubjetCorrL23SmearDn          = sumPUPsubjets_P4_L23resPtSmearDn  .M()   ;
      Jet1PuppiSDptRaw                          = sumPUPsubjets_P4_uncorr           .Perp();
      // Jet1PuppiSDptSubjetCorr                = sumPUPsubjets_P4_L23res           .Perp();
      // Jet1PuppiSDptSubjetCorrUp              = sumPUPsubjets_P4_L23resCorrUp     .Perp();
      // Jet1PuppiSDptSubjetCorrDn              = sumPUPsubjets_P4_L23resCorrDn     .Perp();
      // Jet1PuppiSDptSubjetCorrL23Smear              = sumPUPsubjets_P4_L23resPtSmear    .Perp();
      // Jet1PuppiSDptSubjetCorrL23SmearUp            = sumPUPsubjets_P4_L23resPtSmearUp  .Perp();
      // Jet1PuppiSDptSubjetCorrL23SmearDn            = sumPUPsubjets_P4_L23resPtSmearDn  .Perp();
      Jet1PuppiSDetaRaw                         = sumPUPsubjets_P4_uncorr           .Eta() ;
      Jet1PuppiSDphiRaw                         = sumPUPsubjets_P4_uncorr           .Phi() ;

      // PUPPI user floats from the toolbox
      // Jet1PuppiSDmassUserFloat               = puppi_softDropMass ;
      Jet1PuppiMassPruned                    = puppi_prunedMass   ;
      Jet1PuppiMassTrimmed                   = puppi_trimmedMass  ; 
      Jet1PuppiTau1                          = puppi_tau1         ;                  
      Jet1PuppiTau2                          = puppi_tau2         ;                  
      Jet1PuppiTau3                          = puppi_tau3         ;                  
      Jet1PuppiTau4                          = puppi_tau4         ;                  
      Jet1PuppiTau32                         = puppi_tau32        ;                  
      Jet1PuppiTau21                         = puppi_tau21        ;   

      // PUPPI subjet variables               
      Jet1PuppiSDsubjet0bdisc                = pup0_bdisc                ;
      Jet1PuppiSDsubjet1bdisc                = pup1_bdisc                ;
      Jet1PuppiSDmaxbdisc                    = pup_maxbdisc              ;
      Jet1PuppiSDmaxbdiscflavHadron          = pup_maxbdiscflav_hadron   ;
      Jet1PuppiSDmaxbdiscflavParton          = pup_maxbdiscflav_parton   ;
      Jet1PuppiSDsubjet0pt                   = pup0_P4_uncorr.Pt()       ;
      Jet1PuppiSDsubjet0mass                 = pup0_P4_uncorr.M()        ;
      Jet1PuppiSDsubjet0eta                  = pup0_P4_uncorr.Eta()      ;
      Jet1PuppiSDsubjet0phi                  = pup0_P4_uncorr.Phi()      ;
      Jet1PuppiSDsubjet0area                 = pup0_area                 ;
      Jet1PuppiSDsubjet0flavHadron           = pup0_flav_hadron          ; 
      Jet1PuppiSDsubjet0flavParton           = pup0_flav_parton          ;
      Jet1PuppiSDsubjet0matchedgenjetpt      = pup0_genpt                ;       
      Jet1PuppiSDsubjet0tau1                 = pup0_tau1                 ;  
      Jet1PuppiSDsubjet0tau2                 = pup0_tau2                 ;  
      Jet1PuppiSDsubjet0tau3                 = pup0_tau3                 ; 
      Jet1PuppiSDsubjet1pt                   = pup1_P4_uncorr.Pt()       ;                 
      Jet1PuppiSDsubjet1mass                 = pup1_P4_uncorr.M()        ; 
      Jet1PuppiSDsubjet1eta                  = pup1_P4_uncorr.Eta()      ;
      Jet1PuppiSDsubjet1phi                  = pup1_P4_uncorr.Phi()      ;             
      Jet1PuppiSDsubjet1area                 = pup1_area                 ;              
      Jet1PuppiSDsubjet1flavHadron           = pup1_flav_hadron          ;   
      Jet1PuppiSDsubjet1flavParton           = pup1_flav_parton          ;   
      Jet1PuppiSDsubjet1matchedgenjetpt      = pup1_genpt                ;       
      Jet1PuppiSDsubjet1tau1                 = pup1_tau1                 ;  
      Jet1PuppiSDsubjet1tau2                 = pup1_tau2                 ;  
      Jet1PuppiSDsubjet1tau3                 = pup1_tau3                 ; 

      // AK8CHS JEC scale nom/up/down      
      Jet1CorrFactor                         = corr ;        
      Jet1CorrFactorUp                       = corrUp_L123 ;
      Jet1CorrFactorDn                       = corrDn_L123;
      // AK8CHS L2L3 JEC scale nom/up/down for groomed mass correction
      Jet1MassCorrFactor                     = corr_factor_L23res ;        
      Jet1MassCorrFactorUp                   = corrUp_L23 ;
      Jet1MassCorrFactorDn                   = corrDn_L23 ;
      // AK8CHS JER
      Jet1PtSmearFactor                      = ptsmear  ;
      Jet1PtSmearFactorUp                    = ptsmearUp;
      Jet1PtSmearFactorDn                    = ptsmearDn;         
      
      // AK8PUPPI JEC scale nom/up/down  (use for both full jet and groomed mass corrections)     
      Jet1PuppiCorrFactor                    = corr_factorAK8pup_L23res;          
      Jet1PuppiCorrFactorUp                  = corrUp_pup_L23;          
      Jet1PuppiCorrFactorDn                  = corrDn_pup_L23;    
      
      // AK8PUPPI JER
      Jet1PuppiPtSmearFactor                 = pup_ptsmear;          
      Jet1PuppiPtSmearFactorUp               = pup_ptsmearUp;          
      Jet1PuppiPtSmearFactorDn               = pup_ptsmearDn;  

      // AK8CHS JAR   
      // Jet1EtaScaleFactor                     = 1;          
      // Jet1PhiScaleFactor                     = 1;      

      // AK8CHS GenJet
      Jet1MatchedGenJetPt                    = GenJetMatched.Perp();       
      Jet1MatchedGenJetMass                  = GenJetMatched.M();   

      // AK8PUPPI GenJet
      Jet1PuppiMatchedGenJetPt               = GenJetMatchedPuppi.Perp();       
      Jet1PuppiMatchedGenJetMass             = GenJetMatchedPuppi.M();   
      // Jet1MatchedGenJetDR                 = GenJetMatched_dRmin;             



      if (!iEvent.isRealData() and runGenLoop_) {
        if (counttop==2 && jet_matched_t1){
          Jet1GenMatched_TopHadronic         = (int) top1hadronic             ;
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
          Jet1GenMatched_TopHadronic         = (int) top2hadronic     ;
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

    //Chad
    if (runSemiLeptTree_) {
      v_AK8PuppiPt  ->push_back( puppi_pt );
      v_AK8PuppiEta ->push_back( puppi_eta );
      v_AK8PuppiPhi ->push_back( puppi_phi );
      v_AK8PuppiM   ->push_back( puppi_mass );
      v_AK8PuppiArea->push_back( puppi_area );

      v_AK8PuppiSdPt  ->push_back( sumPUPsubjets_P4_uncorr.Perp() );
      v_AK8PuppiSdEta ->push_back( sumPUPsubjets_P4_uncorr.Eta() );
      v_AK8PuppiSdPhi ->push_back( sumPUPsubjets_P4_uncorr.Phi() );
      v_AK8PuppiSdM   ->push_back( sumPUPsubjets_P4_uncorr.M() );
      v_AK8PuppiSdCorr->push_back( sumPUPsubjets_P4_L23res.M() / sumPUPsubjets_P4_uncorr.M() );
    }

    // Semilept Jet opposite lepton
    if (verbose_) cout<<"count_lep "<<count_lep<<endl;
    if (runSemiLeptTree_ && count_lep ==1){
      double deltaPhi_lep_jet = fabs( deltaPhi(corrJet.phi(), lep0_p4.Phi() )) ;
      if (verbose_) cout<<"  -> deltaPhi_lep_jet "<<deltaPhi_lep_jet<<endl;
      // AK8 jet should be in opposite hemisphere from lepton. If leading jet matches then use it. If it doensn't then check the second leading jet.
      if ( ((count_AK8CHS==0&& deltaPhi_lep_jet >=3.14/2) || (count_AK8CHS==1&&deltaPhi_lep_jet >=3.14/2)) && count_fill_leptTree==0 ){
        if (verbose_) cout<<"Put jet variables in semilept tree  -> count_AK8CHS "<<count_AK8CHS<<" count_fill_leptTree"<<count_fill_leptTree<<endl;
        count_fill_leptTree++;
        AK8jet_SemiLept_P4corr.SetPtEtaPhiM( corrJet.pt(), corrJet.eta(), corrJet.phi(), corrJet.mass() );

        DeltaRJetLep                          = deltaR(corrJet.eta(), corrJet.phi(), lep0_p4.Eta(), lep0_p4.Phi() );
        DeltaPhiJetLep                        = deltaPhi_lep_jet    ;

        // basic kinematic and ID variables
        JetPtRaw                              = uncorrJet.pt()      ;                 
        JetEtaRaw                             = uncorrJet.eta()     ;                  
        JetPhiRaw                             = uncorrJet.phi()     ;   
        JetMassRaw                            = uncorrJet.mass()    ;                                           
        // JetP                                  = corrJet.P()         ;        
        // JetPt                                 = corrJet.pt()        ;                  
        // JetEta                                = corrJet.eta()       ;                  
        // JetPhi                                = corrJet.phi()       ;                  
        // JetRap                                = corrJet.Rapidity()  ;                  
        // JetEnergy                             = corrJet.energy()    ;                  
        // JetMass                               = corrJet.mass()      ;                    
        JetArea                               = ijet.jetArea()      ;                  
       
        JetCHF                                = ijet.chargedHadronEnergy() / uncorrJet.E()  ;                        
        JetNHF                                = ijet.neutralHadronEnergy() / uncorrJet.E()  ;                         
        JetCM                                 = ijet.chargedMultiplicity()  ;                         
        JetNM                                 = ijet.neutralMultiplicity()  ;                          
        JetNEF                                = ijet.neutralEmEnergy() / uncorrJet.E()  ;                            
        JetCEF                                = ijet.chargedEmEnergy() / uncorrJet.E()  ;                          
        JetMF                                 = ijet.muonEnergy() / uncorrJet.E()  ;                         
        JetMult                               = ijet.numberOfDaughters() ;   

        // soft drop mass calculated from soft drop subjets                          
        JetSDmassRaw                          = sumSDsubjets_P4_uncorr   .M()    ;  
        JetSDetaRaw                           = sumSDsubjets_P4_uncorr   .Eta()  ;                    
        JetSDphiRaw                           = sumSDsubjets_P4_uncorr   .Phi()  ;  
        JetSDptRaw                            = sumSDsubjets_P4_uncorr   .Perp() ;  
    
        // experiment with JEC applied separately to each subjet
        JetSDmassSubjetCorrL23                      = sumSDsubjets_P4_L23res          .M()    ;   
        // JetSDmassSubjetCorrL23Up                    = sumSDsubjets_P4_L23resSubjetCorrUp    .M()    ;   
        // JetSDmassSubjetCorrL23Dn                    = sumSDsubjets_P4_L23resSubjetCorrDn    .M()    ; 
        JetSDmassSubjetCorrL123                     = sumSDsubjets_P4_L123res         .M()    ;  
        // JetSDmassCorrL123Up                   = sumSDsubjets_P4_L123resCorrUp   .M()    ;   
        // JetSDmassCorrL123Dn                   = sumSDsubjets_P4_L123resCorrDn   .M()    ;  
        // JetSDmassCorrL23Smear                 = sumSDsubjets_P4_L23resPtSmear   .M()    ;   // This doesn't work. Subjet genjets are not a good match.
        // JetSDmassCorrL23SmearUp               = sumSDsubjets_P4_L23resPtSmearUp .M()    ;
        // JetSDmassCorrL23SmearDn               = sumSDsubjets_P4_L23resPtSmearDn .M()    ;
        // JetSDptCorrL23                        = sumSDsubjets_P4_L23res          .Perp() ;  
        // JetSDptCorrL23Up                      = sumSDsubjets_P4_L23resCorrUp    .Perp() ;  
        // JetSDptCorrL23Dn                      = sumSDsubjets_P4_L23resCorrDn    .Perp() ;  
        // JetSDptCorrL123                       = sumSDsubjets_P4_L123res         .Perp() ;  
        // JetSDptCorrL123Up                     = sumSDsubjets_P4_L123resCorrUp   .Perp() ;  
        // JetSDptCorrL123Dn                     = sumSDsubjets_P4_L123resCorrDn   .Perp() ;  
        // JetSDptCorrL23Smear                   = sumSDsubjets_P4_L23resPtSmear   .Perp() ;
        // JetSDptCorrL23SmearUp                 = sumSDsubjets_P4_L23resPtSmearUp .Perp() ;
        // JetSDptCorrL23SmearDn                 = sumSDsubjets_P4_L23resPtSmearDn .Perp() ;
            
        // user floats from the toolbox
        // JetSDmass                             = softDropMass  ;   // soft Drop mass from miniAOD                 
        JetMassPruned                         = prunedMass    ;     
        JetMassTrimmed                        = trimmedMass   ;     
        JetTau1                               = tau1          ;  
        JetTau2                               = tau2          ;  
        JetTau3                               = tau3          ;  
        JetTau4                               = tau4          ;  
        JetTau32                              = tau32         ;  
        JetTau21                              = tau21         ;  

        JetNsubjetsSD                         = nsubjets_chs   ;
        JetNsubjetsSDPuppi                    = nsubjets_pup   ;

        // Softdrop subjet variables
        JetSDsubjet0bdisc                     = sub0_bdisc            ;  
        JetSDsubjet1bdisc                     = sub1_bdisc            ;   
        JetSDmaxbdisc                         = maxbdisc              ;
        JetSDmaxbdiscflavHadron               = maxbdiscflav_hadron   ;  
        JetSDmaxbdiscflavParton               = maxbdiscflav_parton   ;  
        JetSDsubjet0pt                        = sub0_P4_uncorr.Pt()   ;               
        JetSDsubjet0mass                      = sub0_P4_uncorr.M()    ;  
        JetSDsubjet0eta                       = sub0_P4_uncorr.Eta()  ;  
        JetSDsubjet0phi                       = sub0_P4_uncorr.Phi()  ;  
        JetSDsubjet0area                      = sub0_area             ;  
        JetSDsubjet0flavHadron                = sub0_flav_hadron      ;  
        JetSDsubjet0flavParton                = sub0_flav_parton      ;  
        JetSDsubjet0matchedgenjetpt           = sub0_genpt            ;  
        JetSDsubjet0tau1                      = sub0_tau1             ;  
        JetSDsubjet0tau2                      = sub0_tau2             ;  
        JetSDsubjet0tau3                      = sub0_tau3             ;  
        JetSDsubjet1pt                        = sub1_P4_uncorr.Pt()   ;                    
        JetSDsubjet1mass                      = sub1_P4_uncorr.M()    ; 
        JetSDsubjet1eta                       = sub1_P4_uncorr.Eta()  ;  
        JetSDsubjet1phi                       = sub1_P4_uncorr.Phi()  ;                     
        JetSDsubjet1area                      = sub1_area             ;                    
        JetSDsubjet1flavHadron                = sub1_flav_hadron      ;     
        JetSDsubjet1flavParton                = sub1_flav_parton      ;
        JetSDsubjet1matchedgenjetpt           = sub1_genpt            ;       
        JetSDsubjet1tau1                      = sub1_tau1             ;  
        JetSDsubjet1tau2                      = sub1_tau2             ;  
        JetSDsubjet1tau3                      = sub1_tau3             ; 

        // Angle between puppi jet and chs jet
        // JetDeltaRPuppi                        = minDR_pup_chs;       

        // Puppi jet kinematics (uncorrected) and ID variables
        // JetPuppiP                             = AK8PUPPI_P4uncorr.P()    ;                  
        JetPuppiPtRaw                            = puppi_pt   ;                  
        JetPuppiEtaRaw                           = puppi_eta  ;                   
        JetPuppiPhiRaw                           = puppi_phi  ;                  
        JetPuppiMassRaw                          = puppi_mass ;                  
        JetPuppiArea                          = puppi_area ;                  

        JetPuppiCHF                           = puppi_CHF   ; 
        JetPuppiNHF                           = puppi_NHF   ; 
        JetPuppiCM                            = puppi_CM    ; 
        JetPuppiNM                            = puppi_NM    ; 
        JetPuppiNEF                           = puppi_NEF   ; 
        JetPuppiCEF                           = puppi_CEF   ; 
        JetPuppiMF                            = puppi_MF    ; 
        JetPuppiMult                          = puppi_Mult  ; 

        // Puppi softdrop mass from puppi subjets ( JEC applied separately to each subjet )
        JetPuppiSDmassRaw                        = sumPUPsubjets_P4_uncorr           .M()   ;
        JetPuppiSDmassSubjetCorr              = sumPUPsubjets_P4_L23res           .M()   ;
        // JetPuppiSDmassSubjetCorrUp            = sumPUPsubjets_P4_L23resCorrUp     .M()   ;
        // JetPuppiSDmassSubjetCorrDn            = sumPUPsubjets_P4_L23resCorrDn     .M()   ;
        // JetPuppiSDmassSubjetCorrL23Smear            = sumPUPsubjets_P4_L23resPtSmear    .M()   ;
        // JetPuppiSDmassSubjetCorrL23SmearUp          = sumPUPsubjets_P4_L23resPtSmearUp  .M()   ;
        // JetPuppiSDmassSubjetCorrL23SmearDn          = sumPUPsubjets_P4_L23resPtSmearDn  .M()   ;
        JetPuppiSDptRaw                          = sumPUPsubjets_P4_uncorr           .Perp();
        // JetPuppiSDptSubjetCorr                = sumPUPsubjets_P4_L23res           .Perp();
        // JetPuppiSDptSubjetCorrUp              = sumPUPsubjets_P4_L23resCorrUp     .Perp();
        // JetPuppiSDptSubjetCorrDn              = sumPUPsubjets_P4_L23resCorrDn     .Perp();
        // JetPuppiSDptSubjetCorrL23Smear              = sumPUPsubjets_P4_L23resPtSmear    .Perp();
        // JetPuppiSDptSubjetCorrL23SmearUp            = sumPUPsubjets_P4_L23resPtSmearUp  .Perp();
        // JetPuppiSDptSubjetCorrL23SmearDn            = sumPUPsubjets_P4_L23resPtSmearDn  .Perp();
        JetPuppiSDetaRaw                         = sumPUPsubjets_P4_uncorr           .Eta() ;
        JetPuppiSDphiRaw                         = sumPUPsubjets_P4_uncorr           .Phi() ;

        // PUPPI user floats from the toolbox
        // JetPuppiSDmassUserFloat               = puppi_softDropMass ;
        JetPuppiMassPruned                    = puppi_prunedMass   ;
        JetPuppiMassTrimmed                   = puppi_trimmedMass  ; 
        JetPuppiTau1                          = puppi_tau1         ;                  
        JetPuppiTau2                          = puppi_tau2         ;                  
        JetPuppiTau3                          = puppi_tau3         ;                  
        JetPuppiTau4                          = puppi_tau4         ;                  
        JetPuppiTau32                         = puppi_tau32        ;                  
        JetPuppiTau21                         = puppi_tau21        ;   

        // PUPPI subjet variables               
        JetPuppiSDsubjet0bdisc                = pup0_bdisc                ;
        JetPuppiSDsubjet1bdisc                = pup1_bdisc                ;
        JetPuppiSDmaxbdisc                    = pup_maxbdisc              ;
        JetPuppiSDmaxbdiscflavHadron          = pup_maxbdiscflav_hadron   ;
        JetPuppiSDmaxbdiscflavParton          = pup_maxbdiscflav_parton   ;
        JetPuppiSDsubjet0pt                   = pup0_P4_uncorr.Pt()       ;
        JetPuppiSDsubjet0mass                 = pup0_P4_uncorr.M()        ;
        JetPuppiSDsubjet0eta                  = pup0_P4_uncorr.Eta()      ;
        JetPuppiSDsubjet0phi                  = pup0_P4_uncorr.Phi()      ;
        JetPuppiSDsubjet0area                 = pup0_area                 ;
        JetPuppiSDsubjet0flavHadron           = pup0_flav_hadron          ; 
        JetPuppiSDsubjet0flavParton           = pup0_flav_parton          ;
        JetPuppiSDsubjet0matchedgenjetpt      = pup0_genpt                ;       
        JetPuppiSDsubjet0tau1                 = pup0_tau1                 ;  
        JetPuppiSDsubjet0tau2                 = pup0_tau2                 ;  
        JetPuppiSDsubjet0tau3                 = pup0_tau3                 ; 
        JetPuppiSDsubjet1pt                   = pup1_P4_uncorr.Pt()       ;                 
        JetPuppiSDsubjet1mass                 = pup1_P4_uncorr.M()        ; 
        JetPuppiSDsubjet1eta                  = pup1_P4_uncorr.Eta()      ;
        JetPuppiSDsubjet1phi                  = pup1_P4_uncorr.Phi()      ;             
        JetPuppiSDsubjet1area                 = pup1_area                 ;              
        JetPuppiSDsubjet1flavHadron           = pup1_flav_hadron          ;   
        JetPuppiSDsubjet1flavParton           = pup1_flav_parton          ;   
        JetPuppiSDsubjet1matchedgenjetpt      = pup1_genpt                ;       
        JetPuppiSDsubjet1tau1                 = pup1_tau1                 ;  
        JetPuppiSDsubjet1tau2                 = pup1_tau2                 ;  
        JetPuppiSDsubjet1tau3                 = pup1_tau3                 ; 

        // AK8CHS JEC scale nom/up/down      
        JetCorrFactor                         = corr ;        
        JetCorrFactorUp                       = corrUp_L123 ;
        JetCorrFactorDn                       = corrDn_L123;
        // AK8CHS L2L3 JEC scale nom/up/down for groomed mass correction
        JetMassCorrFactor                     = corr_factor_L23res ;        
        JetMassCorrFactorUp                   = corrUp_L23 ;
        JetMassCorrFactorDn                   = corrDn_L23 ;
        // AK8CHS JER
        JetPtSmearFactor                      = ptsmear  ;
        JetPtSmearFactorUp                    = ptsmearUp;
        JetPtSmearFactorDn                    = ptsmearDn;         
        
        // AK8PUPPI JEC scale nom/up/down  (use for both full jet and groomed mass corrections)     
        JetPuppiCorrFactor                    = corr_factorAK8pup_L23res;          
        JetPuppiCorrFactorUp                  = corrUp_pup_L23;          
        JetPuppiCorrFactorDn                  = corrDn_pup_L23;    
        
        // AK8PUPPI JER
        JetPuppiPtSmearFactor                 = pup_ptsmear;          
        JetPuppiPtSmearFactorUp               = pup_ptsmearUp;          
        JetPuppiPtSmearFactorDn               = pup_ptsmearDn;  

        // AK8CHS JAR   
        // JetEtaScaleFactor                     = 1;          
        // JetPhiScaleFactor                     = 1;      

        // AK8CHS GenJet
        JetMatchedGenJetPt                    = GenJetMatched.Perp();       
        JetMatchedGenJetMass                  = GenJetMatched.M();   

        // AK8PUPPI GenJet
        JetPuppiMatchedGenJetPt               = GenJetMatchedPuppi.Perp();       
        JetPuppiMatchedGenJetMass             = GenJetMatchedPuppi.M();   
        // JetMatchedGenJetDR                 = GenJetMatched_dRmin;             


        if (!iEvent.isRealData() and runGenLoop_) {
          if (counttop==2 && jet_matched_t1){
            JetGenMatched_TopHadronic         = (int) top1hadronic             ;
            JetGenMatched_TopPt               = t1_p4.Perp()                   ;
            JetGenMatched_TopEta              = t1_p4.Eta()                    ;
            JetGenMatched_TopPhi              = t1_p4.Phi()                    ;
            JetGenMatched_TopMass             = t1_p4.M()                      ;
            JetGenMatched_bPt                 = b1_p4.Perp()                   ;
            JetGenMatched_WPt                 = Wp_p4.Perp()                   ;
            JetGenMatched_WEta                = Wp_p4.Eta()                    ;
            JetGenMatched_WPhi                = Wp_p4.Phi()                    ;
            JetGenMatched_WMass               = Wp_p4.M()                      ;
            JetGenMatched_ZPt                 = Z1_p4.Perp()                    ;
            JetGenMatched_ZEta                = Z1_p4.Eta()                     ;
            JetGenMatched_ZPhi                = Z1_p4.Phi()                     ;
            JetGenMatched_ZMass               = Z1_p4.M()                       ;
            JetGenMatched_Wd1Pt               = W1d1_p4.Perp()                 ;
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

            if (verbose_){
              cout<<"  JetGenMatched_DeltaR_pup0_b   "<<JetGenMatched_DeltaR_pup0_b  <<endl;
              cout<<"  JetGenMatched_DeltaR_pup0_Wd1 "<<JetGenMatched_DeltaR_pup0_Wd1<<endl;
              cout<<"  JetGenMatched_DeltaR_pup0_Wd2 "<<JetGenMatched_DeltaR_pup0_Wd2<<endl;
            }
          }   
          if (counttop==2 && jet_matched_t2){
            JetGenMatched_TopHadronic         = (int) top2hadronic     ;
            JetGenMatched_TopPt               = t2_p4.Perp()           ;
            JetGenMatched_TopEta              = t2_p4.Eta()            ;
            JetGenMatched_TopPhi              = t2_p4.Phi()            ;
            JetGenMatched_TopMass             = t2_p4.M()              ;
            JetGenMatched_bPt                 = b2_p4.Perp()           ;
            JetGenMatched_WPt                 = Wm_p4.Perp()           ;
            JetGenMatched_WEta                = Wm_p4.Eta()            ;
            JetGenMatched_WPhi                = Wm_p4.Phi()            ;
            JetGenMatched_WMass               = Wm_p4.M()              ;
            JetGenMatched_ZPt                 = Z2_p4.Perp()           ;
            JetGenMatched_ZEta                = Z2_p4.Eta()            ;
            JetGenMatched_ZPhi                = Z2_p4.Phi()            ;
            JetGenMatched_ZMass               = Z2_p4.M()              ;
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
      } // end if this jet is opposite the lepton
    }// end if event has 1 lepton
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
  

  //------------------------------------
  // WRITE TREE WITH BASELINE PT CUT AND ETA CUT
  //------------------------------------

  if (runAllHadTree_ &&  AK8jet0_P4corr.Perp()>170 && AK8jet1_P4corr.Perp()>170){
    h_cutflow_allhad   ->Fill(1.5);
   
    if ( fabs( AK8jet0_P4corr.Rapidity() ) <2.4 && fabs( AK8jet1_P4corr.Rapidity() ) <2.4 ){    
      h_cutflow_allhad   ->Fill(2.5);
      if (verbose_) cout<<"Write All-Had Tree"<<endl;


      NeighborJet_Jet0_pt      = closestAK8_to_Jet0_P4.Pt() ;
      NeighborJet_Jet0_eta     = closestAK8_to_Jet0_P4.Eta();
      NeighborJet_Jet0_phi     = closestAK8_to_Jet0_P4.Phi();
      NeighborJet_Jet0_m       = closestAK8_to_Jet0_P4.M()  ;
      NeighborJet_Jet0_bdisc   = closestAK8_to_Jet0_bdisc   ;

      NeighborJet_Jet1_pt      = closestAK8_to_Jet1_P4.Pt() ;
      NeighborJet_Jet1_eta     = closestAK8_to_Jet1_P4.Eta();
      NeighborJet_Jet1_phi     = closestAK8_to_Jet1_P4.Phi();
      NeighborJet_Jet1_m       = closestAK8_to_Jet1_P4.M()  ;
      NeighborJet_Jet1_bdisc   = closestAK8_to_Jet1_bdisc   ;

      // AllHadMETpx          = met.px();                   
      // AllHadMETpy          = met.py();                   
      AllHadMETpt          = met.pt();                   
      AllHadMETphi         = met.phi();                   
      AllHadMETsumET       = met.sumEt();                                  
      AllHadNvtx           = nvtx;    
      AllHadNvtxGood       = nvtxgood;    
      AllHadNPUtrue        = nPU;           
      AllHadRho            = rho ;               
     
      if ( !iEvent.isRealData() ){
        AllHadEventWeight    = evWeight ;   
        AllHadPUweight       = puweight  ; 
        AllHadPUweight_MBup  = puweightUp ;
        AllHadPUweight_MBdn  = puweightDn  ; 
        DiGenJetMass         = (GenJetMatched0 + GenJetMatched1).M();                   
        GenTTmass            = (t1_p4+t2_p4).M() ;   
        GenCountHadTop       = count_gen_truth_hadronic_top;    
        Q2weight_CorrDn      = Q2wgt_down ;              
        Q2weight_CorrUp      = Q2wgt_up ;              
        NNPDF3weight_CorrDn  = NNPDF3wgt_down ;              
        NNPDF3weight_CorrUp  = NNPDF3wgt_up ;                        
      }  
      else{ 
        AllHadEventWeight    = 1; 
        AllHadPUweight       = 1; 
        AllHadPUweight_MBup  = 1; 
        AllHadPUweight_MBdn  = 1; 
        DiGenJetMass         = 0; 
        GenTTmass            = 0; 
        GenCountHadTop       = 0; 
        Q2weight_CorrDn      = 1; 
        Q2weight_CorrUp      = 1; 
        NNPDF3weight_CorrDn  = 1; 
        NNPDF3weight_CorrUp  = 1;    
      }

      double dijetDeltaPhi = fabs( deltaPhi( AK8jet0_P4corr.Phi(),  AK8jet1_P4corr.Phi() ));

      DijetMass            = (AK8jet0_P4corr + AK8jet1_P4corr).M() ;                                                   
      DijetMassPuppi       = (PUPPIjet0_P4corr + PUPPIjet1_P4corr).M() ;                                                   
      DijetDeltaR          = deltaR( AK8jet0_P4corr.Eta(), AK8jet0_P4corr.Phi(), AK8jet1_P4corr.Eta(), AK8jet1_P4corr.Phi() );               
      DijetDeltaPhi        = dijetDeltaPhi;                 
      DijetDeltaRap        = fabs(AK8jet0_P4corr.Rapidity() -  AK8jet1_P4corr.Rapidity() );

      CountLep             = count_lep ;
          
      HT                   = HT_AK4_pt30          ;                
      HT_CorrDn            = HT_AK4_pt30_corrDn   ;                
      HT_CorrUp            = HT_AK4_pt30_corrUp   ;  
      HT_PtSmearNom        = HT_AK4_pt30_smearNom ;          
      HT_PtSmearUp         = HT_AK4_pt30_smearUp  ;               
      HT_PtSmearDn         = HT_AK4_pt30_smearDn  ;               
      
      AllHadRunNum         = iEvent.id().run() ;              
      AllHadLumiBlock      = iEvent.id().luminosityBlock() ;              
      AllHadEventNum       = iEvent.id().event() ;  
      PassMETFilters       = (int)  passMETfilters;

      TreeAllHad -> Fill();
    } // end rapidity
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
     
  if (count_lep ==1  && verbose_){
    cout<<" ak8pt  "<< AK8jet_SemiLept_P4corr.Perp() <<endl;
    cout<<" mu pt  "<< mu0_p4.Perp()                 <<endl;
    cout<<" el pt  "<< el0_p4.Perp()                 <<endl;
    cout<<" met    "<< met.pt()                      <<endl;
    cout<<" ak4 pt "<< AK4_dRMinLep_p4.Perp()        <<endl;
  }  

  //------------------------------------
  // WRITE TREE WITH BASELINE PT CUT AND ETA CUT
  //------------------------------------
  //  lep0_p4.Perp()>30 && met.pt() > 30 ){

  if (verbose_) cout<<"count_fill_leptTree "<<count_fill_leptTree<<endl;
  if (runSemiLeptTree_ && count_lep ==1){
    h_cutflow_semilept   ->Fill(1.5);

    if ( AK8jet_SemiLept_P4corr.Perp()>200){
      h_cutflow_semilept   ->Fill(2.5);

      if (fabs( AK8jet_SemiLept_P4corr.Rapidity() ) <2.4  ){
        h_cutflow_semilept   ->Fill(3.5);

        if (verbose_) cout<<"Write Semi-Lept Tree"<<endl;

        SemiLeptMETpx                = met.px();                   
        SemiLeptMETpy                = met.py();                   
        SemiLeptMETpt                = met.pt();                   
        SemiLeptMETphi               = met.phi();                   
        SemiLeptMETsumET             = met.sumEt();   
    
        if ( !iEvent.isRealData() )  SemiLeptMETgenMET            = met.genMET()->pt();                   
        SemiLeptMETuncorPt           = met.uncorPt();                    
           
        SemiLeptMETshiftedPtJetEnUp  = met.shiftedPt(pat::MET::JetEnUp            ) ;                    
        SemiLeptMETshiftedPtJetEnDn  = met.shiftedPt(pat::MET::JetEnDown          ) ;                    
        SemiLeptMETshiftedPtElEnUp   = met.shiftedPt(pat::MET::ElectronEnUp       ) ;                    
        SemiLeptMETshiftedPtElEnDn   = met.shiftedPt(pat::MET::ElectronEnDown     ) ;                    
        SemiLeptMETshiftedPtMuEnUp   = met.shiftedPt(pat::MET::MuonEnUp           ) ;                    
        SemiLeptMETshiftedPtMuEnDn   = met.shiftedPt(pat::MET::MuonEnDown         ) ;                    
        SemiLeptMETshiftedPtJetResUp = met.shiftedPt(pat::MET::JetResUp           ) ;                    
        SemiLeptMETshiftedPtJetResDn = met.shiftedPt(pat::MET::JetResDown         ) ;                    
        SemiLeptMETshiftedPtUnclEnUp = met.shiftedPt(pat::MET::UnclusteredEnUp    ) ;                    
        SemiLeptMETshiftedPtUnclEnDn = met.shiftedPt(pat::MET::UnclusteredEnDown  ) ;                    

        // if (verbose_){
        //   cout<<" met.pt() "<<   met.pt() <<endl;
        //   cout<<" met.shiftedPt(pat::MET::JetEnUp)             "<<met.shiftedPt(pat::MET::JetEnUp)            <<endl;       
        //   cout<<" met.shiftedPt(pat::MET::JetEnDown)           "<<met.shiftedPt(pat::MET::JetEnDown)          <<endl;               
        //   cout<<" met.shiftedPt(pat::MET::ElectronEnUp)        "<<met.shiftedPt(pat::MET::ElectronEnUp)       <<endl;            
        //   cout<<" met.shiftedPt(pat::MET::ElectronEnDown)      "<<met.shiftedPt(pat::MET::ElectronEnDown)     <<endl;                            
        //   cout<<" met.shiftedPt(pat::MET::MuonEnUp)            "<<met.shiftedPt(pat::MET::MuonEnUp)           <<endl;        
        //   cout<<" met.shiftedPt(pat::MET::MuonEnDown)          "<<met.shiftedPt(pat::MET::MuonEnDown)         <<endl;                      
        //   cout<<" met.shiftedPt(pat::MET::JetResUp)            "<<met.shiftedPt(pat::MET::JetResUp)           <<endl;        
        //   cout<<" met.shiftedPt(pat::MET::JetResDown)          "<<met.shiftedPt(pat::MET::JetResDown)         <<endl;               
        //   cout<<" met.shiftedPt(pat::MET::UnclusteredEnUp)     "<<met.shiftedPt(pat::MET::UnclusteredEnUp)    <<endl;               
        //   cout<<" met.shiftedPt(pat::MET::UnclusteredEnDown)   "<<met.shiftedPt(pat::MET::UnclusteredEnDown)  <<endl;                 
          
        //   cout<<" met.phi() "<<   met.phi() <<endl;
        //   cout<<" met.shiftedPhi(pat::MET::UnclusteredEnUp)    "<<met.shiftedPhi(pat::MET::UnclusteredEnUp)   <<endl;                
        //   cout<<" met.shiftedPhi(pat::MET::UnclusteredEnDown)  "<<met.shiftedPhi(pat::MET::UnclusteredEnDown) <<endl;                  
        //   cout<<" met.shiftedPhi(pat::MET::JetEnUp)            "<<met.shiftedPhi(pat::MET::JetEnUp)           <<endl;        
        //   cout<<" met.shiftedPhi(pat::MET::JetEnDown)          "<<met.shiftedPhi(pat::MET::JetEnDown)         <<endl; 
        //   cout<<" met.shiftedPhi(pat::MET::ElectronEnUp)       "<<met.shiftedPhi(pat::MET::ElectronEnUp)      <<endl;             
        //   cout<<" met.shiftedPhi(pat::MET::ElectronEnDown)     "<<met.shiftedPhi(pat::MET::ElectronEnDown)    <<endl; 
        //   cout<<" met.shiftedPhi(pat::MET::MuonEnUp)           "<<met.shiftedPhi(pat::MET::MuonEnUp)          <<endl;         
        //   cout<<" met.shiftedPhi(pat::MET::MuonEnDown)         "<<met.shiftedPhi(pat::MET::MuonEnDown)        <<endl;
        //   cout<<" met.shiftedPhi(pat::MET::JetResUp)           "<<met.shiftedPhi(pat::MET::JetResUp)          <<endl;         
        //   cout<<" met.shiftedPhi(pat::MET::JetResDown)         "<<met.shiftedPhi(pat::MET::JetResDown)        <<endl;    
        // }

        SemiLeptNvtx                 = nvtx;     
        SemiLeptNvtxGood             = nvtxgood;     
        SemiLeptNPUtrue              = nPU;     
        SemiLeptRho                  = rho ;               
        if ( !iEvent.isRealData() ){
          SemiLeptEventWeight          = evWeight ;              
          SemiLeptPUweight             = puweight  ; 
          SemiLeptPUweight_MBup        = puweightUp ;
          SemiLeptPUweight_MBdn        = puweightDn  ;
          SemiLeptGenTTmass            = (t1_p4+t2_p4).M() ; 
          SemiLeptGenCountHadTop       = count_gen_truth_hadronic_top;            
          SemiLeptQ2weight_CorrDn      = Q2wgt_down ;              
          SemiLeptQ2weight_CorrUp      = Q2wgt_up ;              
          SemiLeptNNPDF3weight_CorrDn  = NNPDF3wgt_down ;              
          SemiLeptNNPDF3weight_CorrUp  = NNPDF3wgt_up ;    
        }  
        else{ 
          SemiLeptEventWeight          = 1;    
          SemiLeptPUweight             = 1;
          SemiLeptPUweight_MBup        = 1;
          SemiLeptPUweight_MBdn        = 1;
          SemiLeptGenTTmass            = 0;
          SemiLeptGenCountHadTop       = 0;            
          SemiLeptQ2weight_CorrDn      = 1;       
          SemiLeptQ2weight_CorrUp      = 1;     
          SemiLeptNNPDF3weight_CorrDn  = 1;           
          SemiLeptNNPDF3weight_CorrUp  = 1;
        }
        double htlep = lep0_p4.Perp() + met.pt() ;



        HTlep                = htlep ;
        ST                   = htlep + HT_AK4_pt30           ;                
        ST_CorrDn            = htlep + HT_AK4_pt30_corrDn    ;                
        ST_CorrUp            = htlep + HT_AK4_pt30_corrUp    ;                
        ST_PtSmearNom        = htlep + HT_AK4_pt30_smearNom  ;                
        ST_PtSmearUp         = htlep + HT_AK4_pt30_smearUp   ;                
        ST_PtSmearDn         = htlep + HT_AK4_pt30_smearDn   ;  
              
        SemiLeptRunNum               = iEvent.id().run() ;              
        SemiLeptLumiBlock            = iEvent.id().luminosityBlock() ;              
        SemiLeptEventNum             = iEvent.id().event() ; 
        SemiLeptPassMETFilters       = (int) passMETfilters;              

        AK4_dRminLep_Pt        = AK4_dRMinLep_p4.Perp() ;
        AK4_dRminLep_Eta       = AK4_dRMinLep_p4.Eta()  ;
        AK4_dRminLep_Phi       = AK4_dRMinLep_p4.Phi()  ;
        AK4_dRminLep_Mass      = AK4_dRMinLep_p4.M()    ;
        AK4_dRminLep_Bdisc     = AK4_dRMinLep_bdisc     ;
        AK4_dRminLep_dRlep     = AK4_dRMinLep_deltaR    ;
        AK4_dRminLep_dRak8     = AK4_dRMinLep_p4.DeltaR( AK8jet_SemiLept_P4corr  ) ;
       
        AK4_dRminLep_PtSmear   = AK4_dRMinLep_ptsmear    ;
        AK4_dRminLep_PtSmearUp = AK4_dRMinLep_ptsmearUp  ;
        AK4_dRminLep_PtSmearDn = AK4_dRMinLep_ptsmearDn  ;
        AK4_dRminLep_PtUncorr  = AK4_dRMinLep_ptuncorr   ;

        AK4_dRminLep_Corr      = AK4_dRMinLep_corr       ;
        AK4_dRminLep_CorrUp    = AK4_dRMinLep_corrUp     ;
        AK4_dRminLep_CorrDn    = AK4_dRMinLep_corrDn     ;

        // Closest b-tagged jet to the lepton
        // I don't think we need this 
        // AK4BtagdRminPt    = AK4_btagged_dRMinLep_p4.Perp();
        // AK4BtagdRminBdisc = AK4_btagged_dRMinLep_bdisc    ;
        // AK4BtagdRminLep   = AK4_btagged_dRMinLep          ;
       
        LepHemiContainsAK4BtagLoose  = (int)  ak4_btag_loose;
        LepHemiContainsAK4BtagMedium = (int)  ak4_btag_medium;
        LepHemiContainsAK4BtagTight  = (int)  ak4_btag_tight;

        LeptonPhi0   = lep0_p4.Phi()  ; 
        LeptonPt0    = lep0_p4.Perp() ;  
        LeptonEta0   = lep0_p4.Eta()  ; 
        LeptonMass0  = lep0_p4.M() ; 
        LeptonPhi1   = lep1_p4.Phi()  ; 
        LeptonPt1    = lep1_p4.Perp() ;  
        LeptonEta1   = lep1_p4.Eta()  ; 
        LeptonMass1  = lep1_p4.M() ;


        if      (count_mu==1 && count_el==0) LeptonIsMu  = 1  ; 
        else if (count_mu==0 && count_el==1) LeptonIsMu  = 0  ; 
        else                                 LeptonIsMu  = -1  ;

        PtRel  = AK4_dRMinLep_p4.Perp( lep0_p4.Vect() );
        MuIso  = mu0_iso04;

        Elecron_absiso            = el0_absiso           ;  
        Elecron_relIsoWithDBeta   = el0_relIsoWithDBeta  ;  
        Elecron_absiso_EA         = el0_absiso_EA        ;  
        Elecron_relIsoWithEA      = el0_relIsoWithEA     ;  

        Electron_iso_passHLTpre   = el0_iso_passHLTpre  ;
        Electron_iso_passLoose    = el0_iso_passLoose   ;
        Electron_iso_passMedium   = el0_iso_passMedium  ;
        Electron_iso_passTight    = el0_iso_passTight   ;
        Electron_iso_passHEEP     = el0_iso_passHEEP    ;
        Electron_noiso_passLoose  = el0_noiso_passLoose ;
        Electron_noiso_passMedium = el0_noiso_passMedium;
        Electron_noiso_passTight  = el0_noiso_passTight ;
        Electron_noiso_passHEEP   = el0_noiso_passHEEP  ;

        MuMedium = (int) mu0_isMedium   ;
        MuTight  = (int) mu0_isTight    ;
        MuHighPt = (int) mu0_isHighPt   ;

        TreeSemiLept -> Fill();
      }// end rapidity selection
    }// end pt selection
  } 

  jecPayloadsAK4chsFinal  .clear();
  jecPayloadsAK8chsFinal  .clear();
  jecPayloadsAK4pupFinal  .clear();
  jecPayloadsAK8pupFinal  .clear();

}


// ------------ method called once each job just before starting event loop  ------------
void 
B2GTTbarTreeMaker::beginJob()
{
  fPUweight = new TFile("PUweight_FinalJSON2016_PileupJSONFeb2017_Xsec69200nominal_MCRunIISummer16MiniAODv2_PUMoriond17.root") ;
  hPUweight      = (TH1D*) fPUweight->Get("PUweight_true");
  hPUweight_MBup = (TH1D*) fPUweight->Get("PUweight_true_MBup");
  hPUweight_MBdn = (TH1D*) fPUweight->Get("PUweight_true_MBdn");
       
  std::cout<<"Test PU reweight file weights: "<<std::endl;
  std::cout<<std::setw(5)<<" NPU "<<std::setw(10)<<" weight "<<std::endl;
  for (int i=1; i<=50; i++ ){
      std::cout<<std::setw(5)<<hPUweight->GetBinLowEdge( i )<<"   "<<std::setw(10)<<hPUweight->GetBinContent( i ) <<std::endl;
  } 
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

void 
B2GTTbarTreeMaker::printCutFlowResult(vid::CutFlowResult &cutflow){

  printf("    CutFlow name= %s    decision is %d\n", 
   cutflow.cutFlowName().c_str(),
   (int) cutflow.cutFlowPassed());
  int ncuts = cutflow.cutFlowSize();
  printf(" Index                               cut name              isMasked    value-cut-upon     pass?\n");
  for(int icut = 0; icut<ncuts; icut++){
    printf("  %2d      %50s    %d        %f          %d\n", icut,
     cutflow.getNameAtIndex(icut).c_str(),
     (int)cutflow.isCutMasked(icut),
     cutflow.getValueCutUpon(icut),
     (int)cutflow.getCutResultByIndex(icut));
  }
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(B2GTTbarTreeMaker);

//  LocalWords:  NNPDF
