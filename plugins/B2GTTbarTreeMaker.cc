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
#include "DataFormats/EgammaCandidates/interface/Photon.h"

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
      edm::EDGetTokenT<reco::GenJetCollection>                 ak8genjetSDToken_                  ;
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
      bool isPhoton_         ;
      bool isW_         ;
      bool isZ_         ;
      bool isDown_         ;
      bool isDY_         ;


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

      std::vector<float> *v_photonEta              = new std::vector<float>;
      std::vector<float> *v_photonPhi              = new std::vector<float>;
      std::vector<float> *v_photonPt               = new std::vector<float>;
      std::vector<float> *v_photonSupClustEta      = new std::vector<float>;
      std::vector<float> *v_photonSigIEtaIEta      = new std::vector<float>;
      std::vector<float> *v_photonFullSigIEtaIEta  = new std::vector<float>;
      std::vector<float> *v_photonisTight          = new std::vector<float>;
      std::vector<float> *v_photonisMedium         = new std::vector<float>;
      std::vector<float> *v_photonisLoose          = new std::vector<float>;
      std::vector<float> *v_NHadronIso             = new std::vector<float>;
      std::vector<float> *v_CHadronIso             = new std::vector<float>;
      std::vector<float> *v_PUCHadronIso           = new std::vector<float>;
      std::vector<float> *v_photonIso              = new std::vector<float>;
      std::vector<float> *v_PUPPIphotonIso         = new std::vector<float>;
      std::vector<float> *v_PUPPINHadronIso        = new std::vector<float>;
      std::vector<float> *v_PUPPICHadronIso        = new std::vector<float>;


      std::vector<float> *v_genJetPt        = new std::vector<float>;
      std::vector<float> *v_genJetEta       = new std::vector<float>;
      std::vector<float> *v_genJetPhi       = new std::vector<float>;
      std::vector<float> *v_genJetMass      = new std::vector<float>;
      std::vector<float> *v_genJetArea      = new std::vector<float>;

      std::vector<float> *v_genJetSdPt        = new std::vector<float>;
      std::vector<float> *v_genJetSdEta       = new std::vector<float>;
      std::vector<float> *v_genJetSdPhi       = new std::vector<float>;
      std::vector<float> *v_genJetSdMass      = new std::vector<float>;
      std::vector<float> *v_genJetSdArea      = new std::vector<float>;

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
      Float_t JetAK4PuppiCorrFactor                  ;
      Float_t JetAK4PuppiCorrFactorUp                ;
      Float_t JetAK4PuppiCorrFactorDn                ;     
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

      Int_t   GenQuarkPDGid                          ;
      Int_t   JetGenMatched_QuarkNpartonsStatus20to30              ;
      Float_t JetGenMatched_QuarkPt                    ;
      Float_t JetGenMatched_QuarkEta                   ;
      Float_t JetGenMatched_QuarkPhi                   ;
      Float_t JetGenMatched_QuarkMass                  ;
      Float_t JetGenMatched_AntiQuarkPt                    ;
      Float_t JetGenMatched_AntiQuarkEta                   ;
      Float_t JetGenMatched_AntiQuarkPhi                   ;
      Float_t JetGenMatched_AntiQuarkMass                  ;

      // number of gen DY objects                     
      Int_t   JetGenMatched_NgenDYObjs                      ;
      Int_t   Genl0PDGid                          ;
      Int_t   Genl1PDGid                          ;            
      Float_t JetGenMatched_l0Pt                      ;
      Float_t JetGenMatched_l0Eta                     ;
      Float_t JetGenMatched_l0Phi                     ;
      Float_t JetGenMatched_l0Mass                    ;
      Float_t JetGenMatched_l1Pt                      ;
      Float_t JetGenMatched_l1Eta                     ;
      Float_t JetGenMatched_l1Phi                     ;
      Float_t JetGenMatched_l1Mass                    ; 

      Int_t   JetGenMatched_WNpartonsStatus20to30                 ;
      Float_t JetGenMatched_WplusPt                      ;
      Float_t JetGenMatched_WplusEta                     ;
      Float_t JetGenMatched_WplusPhi                     ;
      Float_t JetGenMatched_WplusMass                    ;
      Float_t JetGenMatched_WminusPt                      ;
      Float_t JetGenMatched_WminusEta                     ;
      Float_t JetGenMatched_WminusPhi                     ;
      Float_t JetGenMatched_WminusMass                    ;
    
      Int_t   JetGenMatched_ZNpartonsStatus20to30                 ;
      Float_t JetGenMatched_Z0Pt                      ;
      Float_t JetGenMatched_Z0Eta                     ;
      Float_t JetGenMatched_Z0Phi                     ;
      Float_t JetGenMatched_Z0Mass                    ;
      Float_t JetGenMatched_Z1Pt                      ;
      Float_t JetGenMatched_Z1Eta                     ;
      Float_t JetGenMatched_Z1Phi                     ;
      Float_t JetGenMatched_Z1Mass                    ; 

      Int_t   JetGenMatched_GammaNpartonsStatus20to30                 ;
      Float_t JetGenMatched_Gamma0Pt                      ;
      Float_t JetGenMatched_Gamma0Eta                     ;
      Float_t JetGenMatched_Gamma0Phi                     ;
      Float_t JetGenMatched_Gamma0Mass                    ;     
      Float_t JetGenMatched_Gamma1Pt                      ;
      Float_t JetGenMatched_Gamma1Eta                     ;
      Float_t JetGenMatched_Gamma1Phi                     ;
      Float_t JetGenMatched_Gamma1Mass                    ;
     
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
      Int_t   SemiLeptGenCountHadObj                 ;
      Int_t   SemiLeptGenObjPDGID                 ;

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
        
      Float_t AK4_dRminLep0_Pt                             ;
      Float_t AK4_dRminLep0_Eta                            ;
      Float_t AK4_dRminLep0_Phi                            ;
      Float_t AK4_dRminLep0_Mass                           ;
      Float_t AK4_dRminLep0_Bdisc                          ;
      Float_t AK4_dRminLep0_dRlep                          ;
      Float_t AK4_dRminLep0_dRak8                          ;
      Float_t AK4_dRminLep0_PtSmear                        ;
      Float_t AK4_dRminLep0_PtSmearUp                      ;
      Float_t AK4_dRminLep0_PtSmearDn                      ;
      Float_t AK4_dRminLep0_PtUncorr                       ;
      Float_t AK4_dRminLep0_Corr                           ;
      Float_t AK4_dRminLep0_CorrUp                         ;
      Float_t AK4_dRminLep0_CorrDn                         ;
       

      // Float_t AK4BtagdRminPt                         ;
      // Float_t AK4BtagdRminBdisc                      ;
      // Float_t AK4BtagdRminLep                        ;
      Int_t   Lep0HemiContainsAK4BtagLoose            ;
      Int_t   Lep0HemiContainsAK4BtagMedium           ;
      Int_t   Lep0HemiContainsAK4BtagTight            ;

      Int_t   CountLep                                  ;

      Char_t  lep0flavor                             ;
      Char_t  lep1flavor                             ;

      Int_t   ChargeLep0                              ;      
      Float_t LeptonPhi0                              ;
      Float_t LeptonPt0                               ;
      Float_t LeptonEta0                              ;
      Float_t LeptonMass0                             ;
      Int_t   ChargeLep1                              ;          
      Float_t LeptonPhi1                              ;
      Float_t LeptonPt1                               ;
      Float_t LeptonEta1                              ;
      Float_t LeptonMass1                             ;
    
      Float_t PtRel0                                  ;
      Float_t PtRel1                                  ;
      Int_t   Lepton0IsMu                             ;
      Int_t   Lepton1IsMu                             ;
    
      Int_t   Mu0HighPt                                ;
      Int_t   Mu0Tight                                ;
      Int_t   Mu0Medium                               ;
      Float_t DeltaRJetLep0                           ; 
      Float_t DeltaPhiJetLep0                         ; 
      Float_t Mu0Iso                                  ;
      Float_t Elecron0_absiso                         ;
      Float_t Elecron0_relIsoWithDBeta                ;
      Float_t Elecron0_absiso_EA                      ;
      Float_t Elecron0_relIsoWithEA                   ;

      Int_t   Mu1HighPt                                ;
      Int_t   Mu1Tight                                ;
      Int_t   Mu1Medium                               ;
      Float_t DeltaRJetLep1                           ;
      Float_t DeltaPhiJetLep1                         ;
      Float_t Mu1Iso                                  ;
      Float_t Elecron1_absiso                         ;
      Float_t Elecron1_relIsoWithDBeta                ;
      Float_t Elecron1_absiso_EA                      ;
      Float_t Elecron1_relIsoWithEA                   ;

      Int_t Electron0_iso_passHLTpre                  ;
      Int_t Electron0_iso_passLoose                   ;
      Int_t Electron0_iso_passMedium                  ;
      Int_t Electron0_iso_passTight                   ;
      Int_t Electron0_iso_passHEEP                    ;
      Int_t Electron0_noiso_passLoose                 ;
      Int_t Electron0_noiso_passMedium                ;
      Int_t Electron0_noiso_passTight                 ;
      Int_t Electron0_noiso_passHEEP                  ;

      Int_t Electron1_iso_passHLTpre                  ;
      Int_t Electron1_iso_passLoose                   ;
      Int_t Electron1_iso_passMedium                  ;
      Int_t Electron1_iso_passTight                   ;
      Int_t Electron1_iso_passHEEP                    ;
      Int_t Electron1_noiso_passLoose                 ;
      Int_t Electron1_noiso_passMedium                ;
      Int_t Electron1_noiso_passTight                 ;
      Int_t Electron1_noiso_passHEEP                  ;

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
    ak8genjetSDToken_(consumes<reco::GenJetCollection>( iConfig.getParameter<edm::InputTag>("ak8GenJetsSoftDropInput"))),
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
    isPhoton_      (iConfig.getParameter<bool>  ("isPhoton")),   
    isW_           (iConfig.getParameter<bool>  ("isW")),
    isZ_           (iConfig.getParameter<bool>  ("isZ")),
    isDown_           (iConfig.getParameter<bool>  ("isDown")),
    isDY_           (iConfig.getParameter<bool>  ("isDY")),
   

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
  // Added these triggers used in AN-16-150
  trigsToRun.push_back("HLT_PFJet80_v");
  trigsToRun.push_back("HLT_PFJet140_v");
  trigsToRun.push_back("HLT_PFJet200_v");
  trigsToRun.push_back("HLT_PFJet260_v");

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

  TreeSemiLept->Branch("v_photonEta"              , "vector<float>", &v_photonEta    );
  TreeSemiLept->Branch("v_photonPhi"              , "vector<float>", &v_photonPhi    );
  TreeSemiLept->Branch("v_photonPt"              , "vector<float>", &v_photonPt    );
  TreeSemiLept->Branch("v_photonSupClustEta"     , "vector<float>", &v_photonSupClustEta    );
  TreeSemiLept->Branch("v_photonSigIEtaIEta"     , "vector<float>", &v_photonSigIEtaIEta    );
  TreeSemiLept->Branch("v_photonFullSigIEtaIEta" , "vector<float>", &v_photonFullSigIEtaIEta    );
  TreeSemiLept->Branch("v_photonisTight"                , "vector<float>", &v_photonisTight    );
  TreeSemiLept->Branch("v_photonisMedium "              , "vector<float>", &v_photonisMedium     );
  TreeSemiLept->Branch("v_photonisLoose"                , "vector<float>", &v_photonisLoose    );
  TreeSemiLept->Branch("v_NHadronIso"                   , "vector<float>", &v_NHadronIso    );
  TreeSemiLept->Branch("v_CHadronIso"                   , "vector<float>", &v_CHadronIso    );
  TreeSemiLept->Branch("v_PUCHadronIso"                 , "vector<float>", &v_PUCHadronIso    );
  TreeSemiLept->Branch("v_photonIso"                    , "vector<float>", &v_photonIso    );
  TreeSemiLept->Branch("v_PUPPIphotonIso"               , "vector<float>", &v_PUPPIphotonIso    );
  TreeSemiLept->Branch("v_PUPPINHadronIso"              , "vector<float>", &v_PUPPINHadronIso    );
  TreeSemiLept->Branch("v_PUPPICHadronIso"              , "vector<float>", &v_PUPPICHadronIso    );


  TreeSemiLept->Branch("v_genJetPt"              , "vector<float>", &v_genJetPt      );
  TreeSemiLept->Branch("v_genJetEta"             , "vector<float>", &v_genJetEta     );
  TreeSemiLept->Branch("v_genJetPhi"             , "vector<float>", &v_genJetPhi     );
  TreeSemiLept->Branch("v_genJetMass"            , "vector<float>", &v_genJetMass    );
  TreeSemiLept->Branch("v_genJetArea"            , "vector<float>", &v_genJetArea    );

  TreeSemiLept->Branch("v_genJetSdPt"              , "vector<float>", &v_genJetSdPt      );
  TreeSemiLept->Branch("v_genJetSdEta"             , "vector<float>", &v_genJetSdEta     );
  TreeSemiLept->Branch("v_genJetSdPhi"             , "vector<float>", &v_genJetSdPhi     );
  TreeSemiLept->Branch("v_genJetSdMass"            , "vector<float>", &v_genJetSdMass    );
  TreeSemiLept->Branch("v_genJetSdArea"            , "vector<float>", &v_genJetSdArea    );

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
  TreeSemiLept->Branch("JetAK4PuppiCorrFactor"                   , & JetAK4PuppiCorrFactor                ,    "JetAK4PuppiCorrFactor/F"                     );
  TreeSemiLept->Branch("JetAK4PuppiCorrFactorUp"                 , & JetAK4PuppiCorrFactorUp              ,    "JetAK4PuppiCorrFactorUp/F"                   );
  TreeSemiLept->Branch("JetAK4PuppiCorrFactorDn"                 , & JetAK4PuppiCorrFactorDn              ,    "JetAK4PuppiCorrFactorDn/F"                   );
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
                          

  TreeSemiLept->Branch("GenQuarkPDGid"            , & GenQuarkPDGid         ,    "GenQuarkPDGid/I"              );
  TreeSemiLept->Branch("JetGenMatched_QuarkNpartonsStatus20to30"            , & JetGenMatched_QuarkNpartonsStatus20to30         ,    "JetGenMatched_QuarkNpartonsStatus20to30/I"              );      
  TreeSemiLept->Branch("JetGenMatched_QuarkPt"                  , & JetGenMatched_QuarkPt               ,    "JetGenMatched_QuarkPt/F"                    );      
  TreeSemiLept->Branch("JetGenMatched_QuarkEta"                 , & JetGenMatched_QuarkEta              ,    "JetGenMatched_QuarkEta/F"                   );      
  TreeSemiLept->Branch("JetGenMatched_QuarkPhi"                 , & JetGenMatched_QuarkPhi              ,    "JetGenMatched_QuarkPhi/F"                   );      
  TreeSemiLept->Branch("JetGenMatched_QuarkMass"                , & JetGenMatched_QuarkMass             ,    "JetGenMatched_QuarkMass/F"                  );      
 
  TreeSemiLept->Branch("JetGenMatched_AntiQuarkPt"                  , & JetGenMatched_AntiQuarkPt               ,    "JetGenMatched_AntiQuarkPt/F"                    );
  TreeSemiLept->Branch("JetGenMatched_AntiQuarkEta"                 , & JetGenMatched_AntiQuarkEta              ,    "JetGenMatched_AntiQuarkEta/F"                   );      
  TreeSemiLept->Branch("JetGenMatched_AntiQuarkPhi"                 , & JetGenMatched_AntiQuarkPhi              ,    "JetGenMatched_AntiQuarkPhi/F"                   );
  TreeSemiLept->Branch("JetGenMatched_AntiQuarkMass"                , & JetGenMatched_AntiQuarkMass             ,    "JetGenMatched_AntiQuarkMass/F"                  );
  
  //TreeSemiLept->Branch("JetGenMatched_bPt"                    , & JetGenMatched_bPt                 ,    "JetGenMatched_bPt/F"                      );
  TreeSemiLept->Branch("JetGenMatched_NgenDYObjs"              , & JetGenMatched_NgenDYObjs           ,    "NgenDYObjs/I"              );
  TreeSemiLept->Branch("Genl0PDGid"            , & Genl0PDGid         ,    "Genl0PDGid/I"              );
  TreeSemiLept->Branch("Genl1PDGid"            , & Genl1PDGid         ,    "Genl1PDGid/I"              );
  TreeSemiLept->Branch("JetGenMatched_l0Pt"                    , & JetGenMatched_l0Pt                 ,    "JetGenMatched_l0Pt/F"                      );
  TreeSemiLept->Branch("JetGenMatched_l0Eta"                   , & JetGenMatched_l0Eta                ,    "JetGenMatched_l0Eta/F"                     );
  TreeSemiLept->Branch("JetGenMatched_l0Phi"                   , & JetGenMatched_l0Phi                ,    "JetGenMatched_l0Phi/F"                     );
  TreeSemiLept->Branch("JetGenMatched_l0Mass"                  , & JetGenMatched_l0Mass               ,    "JetGenMatched_l0Mass/F"                    );

  TreeSemiLept->Branch("JetGenMatched_l1Pt"                    , & JetGenMatched_l1Pt                 ,    "JetGenMatched_l1Pt/F"                      ); 
  TreeSemiLept->Branch("JetGenMatched_l1Eta"                   , & JetGenMatched_l1Eta                ,    "JetGenMatched_l1Eta/F"                     );
  TreeSemiLept->Branch("JetGenMatched_l1Phi"                   , & JetGenMatched_l1Phi                ,    "JetGenMatched_l1Phi/F"                     );
  TreeSemiLept->Branch("JetGenMatched_l1Mass"                  , & JetGenMatched_l1Mass               ,    "JetGenMatched_l1Mass/F"                    );   

  TreeSemiLept->Branch("JetGenMatched_WNpartonsStatus20to30"            , & JetGenMatched_WNpartonsStatus20to30         ,    "JetGenMatched_WNpartonsStatus20to30/I"              );
  TreeSemiLept->Branch("JetGenMatched_WplusPt"                    , & JetGenMatched_WplusPt                 ,    "JetGenMatched_WplusPt/F"                      ); 
  TreeSemiLept->Branch("JetGenMatched_WplusEta"                   , & JetGenMatched_WplusEta                ,    "JetGenMatched_WplusEta/F"                     );
  TreeSemiLept->Branch("JetGenMatched_WplusPhi"                   , & JetGenMatched_WplusPhi                ,    "JetGenMatched_WplusPhi/F"                     );
  TreeSemiLept->Branch("JetGenMatched_WplusMass"                  , & JetGenMatched_WplusMass               ,    "JetGenMatched_WplusMass/F"                    );

  TreeSemiLept->Branch("JetGenMatched_WminusPt"                    , & JetGenMatched_WminusPt                 ,    "JetGenMatched_WminusPt/F"                      );
  TreeSemiLept->Branch("JetGenMatched_WminusEta"                   , & JetGenMatched_WminusEta                ,    "JetGenMatched_WEta/F"                     );
  TreeSemiLept->Branch("JetGenMatched_WminusPhi"                   , & JetGenMatched_WminusPhi                ,    "JetGenMatched_WminusPhi/F"                     );
  TreeSemiLept->Branch("JetGenMatched_WminusMass"                  , & JetGenMatched_WminusMass               ,    "JetGenMatched_WminusMass/F"                    );
 
  TreeSemiLept->Branch("JetGenMatched_ZNpartonsStatus20to30"            , & JetGenMatched_ZNpartonsStatus20to30         ,    "JetGenMatched_ZNpartonsStatus20to30/I"              );
  TreeSemiLept->Branch("JetGenMatched_Z0Pt"                    , & JetGenMatched_Z0Pt                 ,    "JetGenMatched_Z0Pt/F"                      );
  TreeSemiLept->Branch("JetGenMatched_Z0Eta"                   , & JetGenMatched_Z0Eta                ,    "JetGenMatched_Z0Eta/F"                     );
  TreeSemiLept->Branch("JetGenMatched_Z0Phi"                   , & JetGenMatched_Z0Phi                ,    "JetGenMatched_Z0Phi/F"                     );
  TreeSemiLept->Branch("JetGenMatched_Z0Mass"                  , & JetGenMatched_Z0Mass               ,    "JetGenMatched_Z0Mass/F"                    );

  TreeSemiLept->Branch("JetGenMatched_Z1Pt"                    , & JetGenMatched_Z1Pt                 ,    "JetGenMatched_Z1Pt/F"                      ); 
  TreeSemiLept->Branch("JetGenMatched_Z1Eta"                   , & JetGenMatched_Z1Eta                ,    "JetGenMatched_Z1Eta/F"                     );
  TreeSemiLept->Branch("JetGenMatched_Z1Phi"                   , & JetGenMatched_Z1Phi                ,    "JetGenMatched_Z1Phi/F"                     );
  TreeSemiLept->Branch("JetGenMatched_Z1Mass"                  , & JetGenMatched_Z1Mass               ,    "JetGenMatched_Z1Mass/F"                    );     
 
  TreeSemiLept->Branch("JetGenMatched_GammaNpartonsStatus20to30"            , & JetGenMatched_GammaNpartonsStatus20to30         ,    "JetGenMatched_GammaNpartonsStatus20to30/I"              );
  TreeSemiLept->Branch("JetGenMatched_Gamma0Pt"                    , & JetGenMatched_Gamma0Pt                 ,    "JetGenMatched_Gamma0Pt/F"                      );
  TreeSemiLept->Branch("JetGenMatched_Gamma0Eta"                   , & JetGenMatched_Gamma0Eta                ,    "JetGenMatched_Gamma0Eta/F"                     );
  TreeSemiLept->Branch("JetGenMatched_Gamma0Phi"                   , & JetGenMatched_Gamma0Phi                ,    "JetGenMatched_Gamma0Phi/F"                     );
  TreeSemiLept->Branch("JetGenMatched_Gamma0Mass"                  , & JetGenMatched_Gamma0Mass               ,    "JetGenMatched_Gamma0Mass/F"                    );
 
  TreeSemiLept->Branch("JetGenMatched_Gamma1Pt"                    , & JetGenMatched_Gamma1Pt                 ,    "JetGenMatched_Gamma1Pt/F"                      );
  TreeSemiLept->Branch("JetGenMatched_Gamma1Eta"                   , & JetGenMatched_Gamma1Eta                ,    "JetGenMatched_Gamma1Eta/F"                     );
  TreeSemiLept->Branch("JetGenMatched_Gamma1Phi"                   , & JetGenMatched_Gamma1Phi                ,    "JetGenMatched_Gamma1Phi/F"                     );
  TreeSemiLept->Branch("JetGenMatched_Gamma1Mass"                  , & JetGenMatched_Gamma1Mass               ,    "JetGenMatched_Gamma1Mass/F"                    );


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
  TreeSemiLept->Branch("SemiLeptGenCountHadObj"               , & SemiLeptGenCountHadObj            , "SemiLeptGenCountHadObj/I"         );
  TreeSemiLept->Branch("SemiLeptGenObjPDGID"                  , & SemiLeptGenObjPDGID               , "SemiLeptGenObjPDGID/F"                     );

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
 
  TreeSemiLept->Branch("AK4_dRminLep0_Pt"                           , & AK4_dRminLep0_Pt                        , "AK4_dRminLep0_Pt/F"                     );  
  TreeSemiLept->Branch("AK4_dRminLep0_Eta"                          , & AK4_dRminLep0_Eta                       , "AK4_dRminLep0_Eta/F"                    );  
  TreeSemiLept->Branch("AK4_dRminLep0_Phi"                          , & AK4_dRminLep0_Phi                       , "AK4_dRminLep0_Phi/F"                    );  
  TreeSemiLept->Branch("AK4_dRminLep0_Mass"                         , & AK4_dRminLep0_Mass                      , "AK4_dRminLep0_Mass/F"                   );  
  TreeSemiLept->Branch("AK4_dRminLep0_Bdisc"                        , & AK4_dRminLep0_Bdisc                     , "AK4_dRminLep0_Bdisc/F"                  );  
  TreeSemiLept->Branch("AK4_dRminLep0_dRlep"                        , & AK4_dRminLep0_dRlep                     , "AK4_dRminLep0_dRlep/F"                  );  
  TreeSemiLept->Branch("AK4_dRminLep0_dRak8"                        , & AK4_dRminLep0_dRak8                     , "AK4_dRminLep0_dRak8/F"                  );  
  TreeSemiLept->Branch("AK4_dRminLep0_PtSmear"                      , & AK4_dRminLep0_PtSmear                   , "AK4_dRminLep0_PtSmear/F"   );
  TreeSemiLept->Branch("AK4_dRminLep0_PtSmearUp"                    , & AK4_dRminLep0_PtSmearUp                 , "AK4_dRminLep0_PtSmearUp/F" );
  TreeSemiLept->Branch("AK4_dRminLep0_PtSmearDn"                    , & AK4_dRminLep0_PtSmearDn                 , "AK4_dRminLep0_PtSmearDn/F" );
  TreeSemiLept->Branch("AK4_dRminLep0_PtUncorr"                     , & AK4_dRminLep0_PtUncorr                  , "AK4_dRminLep0_PtUncorr/F"  );
  TreeSemiLept->Branch("AK4_dRminLep0_Corr"                         , & AK4_dRminLep0_Corr                      , "AK4_dRminLep0_Corr/F"    );                
  TreeSemiLept->Branch("AK4_dRminLep0_CorrUp"                       , & AK4_dRminLep0_CorrUp                    , "AK4_dRminLep0_CorrUp/F"  );                 
  TreeSemiLept->Branch("AK4_dRminLep0_CorrDn"                       , & AK4_dRminLep0_CorrDn                    , "AK4_dRminLep0_CorrDn/F"  );                  
  // TreeSemiLept->Branch("AK4BtagdRminPt"                       , & AK4BtagdRminPt                    , "AK4BtagdRminPt/F"                 );  
  // TreeSemiLept->Branch("AK4BtagdRminBdisc"                    , & AK4BtagdRminBdisc                 , "AK4BtagdRminBdisc/F"              );  
  // TreeSemiLept->Branch("AK4BtagdRminLep"                      , & AK4BtagdRminLep                   , "AK4BtagdRminLep/F"                );  
  TreeSemiLept->Branch("Lep0HemiContainsAK4BtagLoose"          , & Lep0HemiContainsAK4BtagLoose       , "Lep0HemiContainsAK4BtagLoose/I"    );  
  TreeSemiLept->Branch("Lep0HemiContainsAK4BtagMedium"         , & Lep0HemiContainsAK4BtagMedium      , "Lep0HemiContainsAK4BtagMedium/I"   );  
  TreeSemiLept->Branch("Lep0HemiContainsAK4BtagTight"          , & Lep0HemiContainsAK4BtagTight       , "Lep0HemiContainsAK4BtagTight/I"    );  

  TreeSemiLept->Branch("CountLep"                              , & CountLep                           ,    "CountLep/I"                  );
  TreeSemiLept->Branch("ChargeLep0"                              , & ChargeLep0                           ,    "ChargeLep0/I"                  );
  TreeSemiLept->Branch("ChargeLep1"                              , & ChargeLep1                           ,    "ChargeLep1/I"                  );


  TreeSemiLept->Branch("lep0flavor"                            , &  lep0flavor                        , "lep0flavor/B"                      ); 
  TreeSemiLept->Branch("lep1flavor"                            , &  lep1flavor                        , "lep1flavor/B"                      ); 
  TreeSemiLept->Branch("LeptonPhi0"                            , &  LeptonPhi0                        , "LeptonPhi0/F"                      ); 
  TreeSemiLept->Branch("LeptonPt0"                             , &  LeptonPt0                         , "LeptonPt0/F"                       ); 
  TreeSemiLept->Branch("LeptonEta0"                            , &  LeptonEta0                        , "LeptonEta0/F"                      ); 
  TreeSemiLept->Branch("LeptonMass0"                           , &  LeptonMass0                       , "LeptonMass0/F"                     );
  TreeSemiLept->Branch("LeptonPhi1"                            , &  LeptonPhi1                        , "LeptonPhi1/F"                      ); 
  TreeSemiLept->Branch("LeptonPt1"                             , &  LeptonPt1                         , "LeptonPt1/F"                       ); 
  TreeSemiLept->Branch("LeptonEta1"                            , &  LeptonEta1                        , "LeptonEta1/F"                      ); 
  TreeSemiLept->Branch("LeptonMass1"                           , &  LeptonMass1                       , "LeptonMass1/F"                     ); 
  
  TreeSemiLept->Branch("PtRel0"                                , &  PtRel0                            , "PtRel0/F"                          ); 
  TreeSemiLept->Branch("Lepton0IsMu"                           , &  Lepton0IsMu                       , "Lepton0IsMu/I"                     ); 
  TreeSemiLept->Branch("Mu0Medium"                             , &  Mu0Medium                         , "Mu0Medium/I"                       ); 
  TreeSemiLept->Branch("Mu0Tight"                              , &  Mu0Tight                          , "Mu0Tight/I"                        ); 
  TreeSemiLept->Branch("Mu0HighPt"                             , &  Mu0HighPt                         , "MuH0ighPt/I"                       ); 
  TreeSemiLept->Branch("DeltaRJetLep0"                         , &  DeltaRJetLep0                     , "DeltaRJetLep0/F"                   ); 
  TreeSemiLept->Branch("DeltaPhiJetLep0"                       , &  DeltaPhiJetLep0                   , "DeltaPhiJetLep0/F"                 ); 
  
  TreeSemiLept->Branch("PtRel1"                                , &  PtRel1                            , "PtRel1/F"                          );
  TreeSemiLept->Branch("Lepton1IsMu"                           , &  Lepton1IsMu                       , "Lepton1IsMu/I"                     );
  TreeSemiLept->Branch("Mu1Medium"                             , &  Mu1Medium                         , "Mu1Medium/I"                       );
  TreeSemiLept->Branch("Mu1Tight"                              , &  Mu1Tight                          , "Mu1Tight/I"                        );
  TreeSemiLept->Branch("Mu1HighPt"                             , &  Mu1HighPt                         , "Mu1HighPt/I"                       );
  TreeSemiLept->Branch("DeltaRJetLep1"                         , &  DeltaRJetLep1                     , "DeltaRJetLep1/F"                   );
  TreeSemiLept->Branch("DeltaPhiJetLep1"                       , &  DeltaPhiJetLep1                   , "DeltaPhiJetLep1/F"                 );

  TreeSemiLept->Branch("Mu0Iso"                                , &  Mu0Iso                            , "Mu0Iso/F"                          ); 
  TreeSemiLept->Branch("Elecron0_absiso"                       , &  Elecron0_absiso                   , "Elecron0_absiso/F"                 ); 
  TreeSemiLept->Branch("Elecron0_relIsoWithDBeta"              , &  Elecron0_relIsoWithDBeta          , "Elecron0_relIsoWithDBeta/F"        ); 
  TreeSemiLept->Branch("Elecron0_absiso_EA"                    , &  Elecron0_absiso_EA                , "Elecron0_absiso_EA/F"              ); 
  TreeSemiLept->Branch("Elecron0_relIsoWithEA"                 , &  Elecron0_relIsoWithEA             , "Elecron0_relIsoWithEA/F"           ); 
 
  TreeSemiLept->Branch("Electron0_iso_passHLTpre"      , & Electron0_iso_passHLTpre   , "Electron0_iso_passHLTpre/I"    );
  TreeSemiLept->Branch("Electron0_iso_passLoose"       , & Electron0_iso_passLoose    , "Electron0_iso_passLoose/I"     );
  TreeSemiLept->Branch("Electron0_iso_passMedium"      , & Electron0_iso_passMedium   , "Electron0_iso_passMedium/I"    );
  TreeSemiLept->Branch("Electron0_iso_passTight"       , & Electron0_iso_passTight    , "Electron0_iso_passTight/I"     );
  TreeSemiLept->Branch("Electron0_iso_passHEEP"        , & Electron0_iso_passHEEP     , "Electron0_iso_passHEEP/I"      );
  TreeSemiLept->Branch("Electron0_noiso_passLoose"     , & Electron0_noiso_passLoose  , "Electron0_noiso_passLoose/I"   );
  TreeSemiLept->Branch("Electron0_noiso_passMedium"    , & Electron0_noiso_passMedium , "Electron0_noiso_passMedium/I"  );
  TreeSemiLept->Branch("Electron0_noiso_passTight"     , & Electron0_noiso_passTight  , "Electron0_noiso_passTight/I"   );
  TreeSemiLept->Branch("Electron0_noiso_passHEEP"      , & Electron0_noiso_passHEEP   , "Electron0_noiso_passHEEP/I"    );

  TreeSemiLept->Branch("Mu1Iso"                                , &  Mu1Iso                            , "Mu1Iso/F"                          );
  TreeSemiLept->Branch("Elecron1_absiso"                       , &  Elecron1_absiso                   , "Elecron1_absiso/F"                 );
  TreeSemiLept->Branch("Elecron1_relIsoWithDBeta"              , &  Elecron1_relIsoWithDBeta          , "Elecron1_relIsoWithDBeta/F"        );
  TreeSemiLept->Branch("Elecron1_absiso_EA"                    , &  Elecron1_absiso_EA                , "Elecron1_absiso_EA/F"              );
  TreeSemiLept->Branch("Elecron1_relIsoWithEA"                 , &  Elecron1_relIsoWithEA             , "Elecron1_relIsoWithEA/F"           );

  TreeSemiLept->Branch("Electron1_iso_passHLTpre"      , & Electron1_iso_passHLTpre   , "Electron1_iso_passHLTpre/I"    );
  TreeSemiLept->Branch("Electron1_iso_passLoose"       , & Electron1_iso_passLoose    , "Electron1_iso_passLoose/I"     );
  TreeSemiLept->Branch("Electron1_iso_passMedium"      , & Electron1_iso_passMedium   , "Electron1_iso_passMedium/I"    );
  TreeSemiLept->Branch("Electron1_iso_passTight"       , & Electron1_iso_passTight    , "Electron1_iso_passTight/I"     );
  TreeSemiLept->Branch("Electron1_iso_passHEEP"        , & Electron1_iso_passHEEP     , "Electron1_iso_passHEEP/I"      );
  TreeSemiLept->Branch("Electron1_noiso_passLoose"     , & Electron1_noiso_passLoose  , "Electron1_noiso_passLoose/I"   );
  TreeSemiLept->Branch("Electron1_noiso_passMedium"    , & Electron1_noiso_passMedium , "Electron1_noiso_passMedium/I"  );
  TreeSemiLept->Branch("Electron1_noiso_passTight"     , & Electron1_noiso_passTight  , "Electron1_noiso_passTight/I"   );
  TreeSemiLept->Branch("Electron1_noiso_passHEEP"      , & Electron1_noiso_passHEEP   , "Electron1_noiso_passHEEP/I"    ); 
 

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
  
  // use for checking the problem event

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
                                                                                                                                                                                                                        
  // bool top1hadronic=false;
  // bool top2hadronic=false;
  // bool top1leptonic=false;
  //bool top2leptonic=false;

  TLorentzVector t1_p4;
  TLorentzVector t2_p4;
  TLorentzVector finalt1_p4;
  TLorentzVector finalt2_p4;
  TLorentzVector b1_p4;
  TLorentzVector b2_p4;
  TLorentzVector Wp_p4;
  TLorentzVector Wm_p4;
  TLorentzVector Z1_p4;
  TLorentzVector Z2_p4;
  TLorentzVector Gamma1_p4;
  TLorentzVector Gamma2_p4;
  //Drell-Yan
  TLorentzVector l1_p4;  // leptons from DY
  TLorentzVector l2_p4;
  int genl1PDGID;
  genl1PDGID = 0;
  int genl2PDGID;
  genl2PDGID = 0;

  int genQuarkPDGID;
  genQuarkPDGID = 0;
  TLorentzVector qhard_p4;// d quark 1                                                                                                                                                          
  TLorentzVector antiqhard_p4;// d quark 2    

  TLorentzVector hardest_parton_hardScatterOutgoing_p4;                                                                                                     
  TLorentzVector second_hardest_parton_hardScatterOutgoing_p4;   
  double hardest_parton_hardScatterOutgoing_pt        = 0;                                                                                                  
  double second_hardest_parton_hardScatterOutgoing_pt = 0;                                                                                                  
                                                                                                                                                          
  int parton1id = 0;                                                                                                                                       
  int parton2id = 0;  
  //bool GenTruth_allhadronic = false;                                                                                                                       
  // bool GenTruth_semileptonic = false;                                                                                                                      
  int count_gen_truth_hadronic_obj = 0;      

  int objPDGID = 0;
  if(isttbar_ )objPDGID = 6;
  if(isPhoton_ )objPDGID = 22;
  if(isW_ )objPDGID = 24;
  if(isZ_ )objPDGID = 23;
  if(isDown_ )objPDGID = 1;
  if(isDY_ )objPDGID = -1;
  //if(isUp_ )objPDGID = 2;

  // For Drell-Yan isDY the intermediate gamma/Z is not stored so classify it by events where you see :
  //  a quark and an antiquark then a lepton and antilepton
  //std::vector<int> *hasDY = new std::vector<int>;
  //std::vector<int> *hasq0 = new std::vector<int>;
  //std::vector<int> *hasq1 = new std::vector<int>;
  //std::vector<int> *hasl0 = new std::vector<int>;
  //std::vector<int> *hasl1 = new std::vector<int>;  
  int q0PDGID = 0;
  int q1PDGID = 0;

  int l0PDGID = 0;
  int l1PDGID = 0;   

  double countObj = 0;
  if (!iEvent.isRealData() and runGenLoop_) { 
    Handle<edm::View<reco::GenParticle> > genpart;
    iEvent.getByToken(prunedGenToken_,genpart);  

    
    //hasDY ->clear();
    //hasq0 ->clear();
    //hasq1 ->clear();
    //hasl0 ->clear();
    //hasl1 ->clear();  
    int hasDY = 0;          
    // Classify the event based on the number of a given object with objPDGID e.g. W bosons : objPDGID = 24
    if (objPDGID >= 0) {
      if (verboseGen_) cout<<"Looping over genparticles in event for classification "<<endl;
      for(size_t i=0; i<genpart->size();i++){
        if (fabs((*genpart)[i].pdgId())==objPDGID && (*genpart)[i].status()<30 && (*genpart)[i].status()>=20) countObj++;  // Z' events: status 22 = top from Z', status 52 with 2 daughters = the top that decays (after radiating a bunch of times)
      }
      if (verboseGen_) cout<<"countObj : "<<countObj<< "  objPDGID : " << objPDGID <<endl;
    }  
    if ( objPDGID < 0 ) { // isDY  
      if (verboseGen_) cout<<"Looping over genparticles in event for classification "<<endl;
      if (verboseGen_) cout<<"Looking for Drell-Yan signatures"<<endl;
      
      for(size_t i=0; i<genpart->size();i++){ // 
        if ( 1<= fabs((*genpart)[i].pdgId()) && fabs((*genpart)[i].pdgId()) <=6  && (*genpart)[i].status()<30 && (*genpart)[i].status()>=20 ) {
          if (q0PDGID == 0 ){
          q0PDGID = (*genpart)[i].pdgId() ;  
          //hasq0 ->push_back(i);
          if (verboseGen_) cout<<"quark 0 identified as gen partcle i = "<< i << " PDG id "<< q0PDGID <<endl; 
          }  
          //if (q0PDGID != 0 ) hasq0 ->push_back(-1);
        }  
        if ( q0PDGID != 0 && 1<= fabs((*genpart)[i].pdgId()) && fabs((*genpart)[i].pdgId()) <=6  && (*genpart)[i].status()<30 && (*genpart)[i].status()>=20 && q0PDGID == -1 * (*genpart)[i].pdgId()  ) {
          if (q1PDGID == 0 ) {
            q1PDGID = (*genpart)[i].pdgId() ;
            //hasq1 ->push_back(i);
            if (verboseGen_) cout<<"quark 1 identified as gen partcle i = "<< i << " PDG id "<< q0PDGID <<endl;
          }  
          //if (q1PDGID != 0 ) hasq1 ->push_back(-1);
        }  
        if ( q0PDGID != 0 && q1PDGID != 0 && verboseGen_) cout<<"q0PDGID : "<< q0PDGID << "  q1PDGID : " << q1PDGID <<endl;   
        // if there is already a quark - antiqark pair then a lepton and l0PDGID = 0 then this is lepton0
        if ( q0PDGID != 0 && q1PDGID != 0 && 11<= fabs((*genpart)[i].pdgId()) && fabs((*genpart)[i].pdgId()) <=18  && l0PDGID == 0 ) {
          l0PDGID = (*genpart)[i].pdgId() ;
          if (verboseGen_) cout<<"lepton 0 identified as gen partcle i = "<< i << " PDG id "<< q0PDGID <<endl;
        }  
        // if we already have the first lepton and this is its antiparticle then this is lepton1
        if (l0PDGID != 0 && l1PDGID == 0 && -1* l0PDGID == (*genpart)[i].pdgId()) {
          l1PDGID = (*genpart)[i].pdgId() ;
          if (verboseGen_) cout<<"lepton 1 identified as gen partcle i = "<< i << " PDG id "<< q0PDGID <<endl;
        }  
        if (q0PDGID != 0 && q1PDGID != 0 && l0PDGID != 0 && l1PDGID != 0) { 
        if (verboseGen_)  cout<<"l0PDGID : "<< l0PDGID << "  l1PDGID : " << l1PDGID <<endl;
        countObj++;
        //hasDY ->push_back(i);
        hasDY = int(i);
        if (verboseGen_) cout<<" hasDY recorded as i "<< i <<endl;
        q0PDGID = 0 ; q1PDGID = 0; l0PDGID = 0; l1PDGID = 0;
        }
        //else hasDY ->push_back(-1);
      }
      if (verboseGen_) cout<<"countObj : "<<countObj<< " Drell-Yan signatures in this event "<<endl;    
    }   
    // Loop over all pruned gen particles and find the 4-vectors of the top, W, B, W duaghters
    // double countW = 0;
    //double countb = 0;
   
    count_gen_truth_hadronic_obj = countObj ;
    for(size_t i=0; i<genpart->size();i++){ // size_t 
      int id        = (*genpart)[i].pdgId();
      int status    = (*genpart)[i].status();
      int ndau      = (*genpart)[i].numberOfDaughters();
      double px     = (*genpart)[i].px();
      double py     = (*genpart)[i].py();
      double pz     = (*genpart)[i].pz();
      double e      = (*genpart)[i].energy();
      //double m      = (*genpart)[i].mass();
      double pt     = (*genpart)[i].pt();
      double eta    = (*genpart)[i].eta();
      double phi    = (*genpart)[i].phi();
      //double nmothers = (*genpart)[i].numberOfMothers() ;
      if (verboseGen_) cout<<"For Genparticle  "<< i << " PDGID is  "<< id  << " status is "  << status  <<endl;

      // Find the lepton and antilepton from Drell-Yan
      if (objPDGID <0 && countObj>=1 ) {
         //lepton 1
         if ( int(i+1) == int(hasDY) ) {
           l1_p4.SetPxPyPzE( px, py, pz, e );
           genl1PDGID = id;
           if (verboseGen_) cout<<"..Drell-Yan lepton 1 : status "<< status <<" ndau "<< ndau <<" pt "<< pt <<" eta "<< eta <<" phi "<< phi <<" id "<< id <<endl;
           }

         //lepton 2   
         if ( int(i) == int(hasDY) ){
           l2_p4.SetPxPyPzE( px, py, pz, e );
           genl2PDGID = id;
           if (verboseGen_) cout<<"..Drell-Yan lepton 2 : status "<< status <<" ndau "<< ndau <<" pt "<< pt <<" eta "<< eta <<" phi "<< phi <<" id "<< id <<endl;
         }
      }

      // Find the particles from the hard scatter (for QCD samples)
      if (status==23 && countObj==0){
        if (pt>hardest_parton_hardScatterOutgoing_pt){
          second_hardest_parton_hardScatterOutgoing_pt = hardest_parton_hardScatterOutgoing_pt;
          second_hardest_parton_hardScatterOutgoing_p4 = hardest_parton_hardScatterOutgoing_p4;
          hardest_parton_hardScatterOutgoing_pt = pt;
          hardest_parton_hardScatterOutgoing_p4.SetPxPyPzE( px, py, pz, e );
          parton1id = id;
          if (verboseGen_) cout<<"---------- pt>hardest_parton_hardScatterOutgoing_pt - parton1id = "<<parton1id<<endl;

	  //if (parton1id == 22 ) {
	    // Gamma1_p4.SetPxPyPzE( px, py, pz, e );
	    //if (verboseGen_) cout<<"..Photon 1 : "<< " with pt "<<pt<<" status "<<status<<" ndau "<< ndau <<" pt "<<pt<<" eta "<<eta<<" phi "<<phi<<" parton1id = "<<parton1id<<endl;
	    //}


        }
        else if (pt>second_hardest_parton_hardScatterOutgoing_pt){
          second_hardest_parton_hardScatterOutgoing_pt = pt;
          second_hardest_parton_hardScatterOutgoing_p4.SetPxPyPzE( px, py, pz, e ); 
          parton2id = id;
          if (verboseGen_) cout<<"---------- pt>second_hardest_parton_hardScatterOutgoing_pt - parton2id = "<<parton2id<<endl;


	  //  if (parton2id == 22 ) {
	  // Gamma2_p4.SetPxPyPzE( px, py, pz, e );
	  // if (verboseGen_) cout<<"..Photon 2 :  "<< " with pt "<<pt<<" status "<<status<<" ndau "<< ndau <<" pt "<<pt<<" eta "<<eta<<" phi "<<phi<<" parton2id = "<<parton2id<<endl;
	  // }
        }                                                                               

      } // end if countObj == 0 and hard scatter                                                 


      /*
      // Find the the resonance mass for Z'
      if (id>1000000 && status == 22) 
      {
        Resonance_p4.SetPxPyPzE( px, py, pz, e ); 
        if (verboseGen_) cout<<".Resonant particle with mass "<<m<<endl; // RSGWW id = 5100039, Z' id = 6000047
      }
      */
      if (verboseGen_) cout<<".. Inside Gen Loop.. "<<endl; 
      // Get Gen Photons 
      if (id == 22 && verboseGen_ ) cout<<"..Gen Parton is Photon.. "<<endl;
      if (id == 22 && status ==23  ) {
	if (verboseGen_) cout<<"..Gen Parton is Photon from hard scatter.. "<<endl;
        if (Gamma1_p4.Perp()<= 1.0 ){
	Gamma1_p4.SetPxPyPzE( px, py, pz, e );
	if (verboseGen_) cout<<"..Photon 1 : "<< " with pt "<<pt<<" status "<<status<<" ndau "<< ndau <<" pt "<<pt<<" eta "<<eta<<" phi "<<phi<<" parton1id = "<<parton1id<<endl;
      }
        if (Gamma1_p4.Perp()>= 1.0 && Gamma2_p4.Perp()<= 1.0 && phi != Gamma1_p4.Phi()  ){
	  Gamma2_p4.SetPxPyPzE( px, py, pz, e );
	  if (verboseGen_) cout<<"..Photon 2 : "<< " with pt "<<pt<<" status "<<status<<" ndau "<< ndau <<" pt "<<pt<<" eta "<<eta<<" phi "<<phi<<" parton1id = "<<parton1id<<endl;
	}

      }

      // Get Gen Ws                                                                                                                                                                         
      if ((id == 24 || id == -24) && verboseGen_ ) cout<<"..Gen Parton is W Boson.. status is  "<< status  <<endl;
      if ( (id == 24 || id == -24)  && status<30 && status>=20 ) {
        if (verboseGen_) cout<<".. from hard subprocess.. "<<endl;
        if (id == 24 && Wp_p4.Perp() <= 1.0) {
	  Wp_p4.SetPxPyPzE( px, py, pz, e );
	  if (verboseGen_) cout<<"..W+ 1 : "<<" status "<<status<<" ndau "<< ndau <<" pt "<<pt<<" eta "<<eta<<" phi "<<phi<<" id = "<< id <<endl;
        }
        if (id == -24 && Wm_p4.Perp() <= 1.0) {
          Wm_p4.SetPxPyPzE( px, py, pz, e );
          if (verboseGen_) cout<<"..W- 1 : "<<" status "<<status<<" ndau "<< ndau <<" pt "<<pt<<" eta "<<eta<<" phi "<<phi<<" id = "<< id <<endl;
        }
      
      }// end Gen Ws

      // Get Gen Zs                                                                                                                                                                              
      if (id == 23  && verboseGen_ ) cout<<"..Gen Parton is Z0  Boson.. status is  "<< status  <<endl;
      if ( id == 23  && status<30 && status>=20 ) {
        if (verboseGen_) cout<<".. from hard subprocess.. "<<endl;
        if (id == 23 && Z1_p4.Perp() <= 1.0) {
          Z1_p4.SetPxPyPzE( px, py, pz, e );
          if (verboseGen_) cout<<"..Z0 1 : "<<" status "<<status<<" ndau "<< ndau <<" pt "<<pt<<" eta "<<eta<<" phi "<<phi<<" id = "<< id <<endl;
        }
        if (id == 23 && Z1_p4.Perp()>= 1.0 && Z2_p4.Perp()<= 1.0 && phi != Z1_p4.Phi()  ){
          Z2_p4.SetPxPyPzE( px, py, pz, e );
          if (verboseGen_) cout<<"..Z0 2 : "<<" status "<<status<<" ndau "<< ndau <<" pt "<<pt<<" eta "<<eta<<" phi "<<phi<<" id = "<< id <<endl;
        }
      }// end Gen Zs  

      // Get Gen quarks                                                                                                                                                                               
      if (id >= -6  && id <= 6  && verboseGen_ ) cout<<"..Gen Parton is Quark of PDGid .."<< id  <<   " status is  "<< status  <<endl;
      if ( id >= -6 && id <= 6 && status==23 ) {
        if (verboseGen_) cout<<".. from hard scatter.. "<<endl;
      
        if (id >= 1 && id <=6  && qhard_p4.Perp() <= 1.0) {
          qhard_p4.SetPxPyPzE( px, py, pz, e );
          genQuarkPDGID = int(id);
          if (verboseGen_) cout<<"..Quark : "<<" status "<<status<<" ndau "<< ndau <<" pt "<<pt<<" eta "<<eta<<" phi "<<phi<<" id = "<< id <<endl;
        }
        if (id >= -6 && id <= -1  && antiqhard_p4.Perp()<= 1.0  ){
          genQuarkPDGID =int(id);
          antiqhard_p4.SetPxPyPzE( px, py, pz, e );
          if (verboseGen_) cout<<"..Anti-Quark : "<<" status "<<status<<" ndau "<< ndau <<" pt "<<pt<<" eta "<<eta<<" phi "<<phi<<" id = "<< id <<endl;
        }
      }// end Gen Quarks    
  

      }// end genParticle loop
    } // end run gen loop and MC 
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
  //AllHadTrigPrescales   ->clear();
  SemiLeptTrigPrescales ->clear();
  //AllHadTrigPass        ->clear();
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
      //AllHadTrigPrescales   ->push_back(prescale);
      SemiLeptTrigPrescales ->push_back(prescale);
      //AllHadTrigPass        ->push_back(pass);
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

  //AllHadTrigAcceptBits   = hltbit.to_string();
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

  if (isZprime_ || isttbar_ || isPhoton_ || isW_ || isZ_ || isDown_ ){
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

  TLorentzVector mu0_p4, mu1_p4;
  bool mu0_isTight=false;
  bool mu0_isMedium=false;
  bool mu0_isHighPt = false;
  double mu0_iso04=0;
  bool mu1_isTight=false;
  bool mu1_isMedium=false;
  bool mu1_isHighPt = false;
  double mu1_iso04=0;
  int count_mu=0;
  //int chargeMu = 0;
  std::vector<reco::CandidatePtr> muFootprint0, muFootprint1;

  for (const pat::Muon &mu : *muons) {

      // use only loose muons 
      if (mu.pt() < 30 || !mu.isLooseMuon() || fabs( mu.eta() ) > 2.1) continue;

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
        //chargeMu = mu.charge();
        if (verbose_) cout<<"Muon charge "<< mu.charge() <<endl; 

        if      (iEvent.isRealData() && runNumber <= 278808) isMedium = isMediumBF;       // Data B-F
        else if (iEvent.isRealData() && runNumber  > 278808) isMedium = isMediumStandard; // Data G-H
        else isMedium = isMediumStandard;  // MC 
     

        // HighPt ID
        bool isHighPt = mu.isHighPtMuon(PV);

        // https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId#Accessing_PF_Isolation_from_reco
        double sumChargedHadronPt = mu.pfIsolationR04().sumChargedHadronPt;
        double sumNeutralHadronPt = mu.pfIsolationR04().sumNeutralHadronEt;
        double sumPhotonPt        = mu.pfIsolationR04().sumPhotonEt;
        double sumPUPt            = mu.pfIsolationR04().sumPUPt;
        double pt                 = mu.pt();
        double iso04 = (sumChargedHadronPt+TMath::Max(0.,sumNeutralHadronPt+sumPhotonPt-0.5*sumPUPt))/pt;

      if (count_mu==0){
        Lepton0IsMu  = 1  ;
        mu0_p4.SetPtEtaPhiM( mu.pt(), mu.eta(), mu.phi(), mu.mass() );
        if ( isMedium ) mu0_isMedium = true;

        // Tight ID                                                                                                                                         
        if ( mu.isTightMuon(PV) ) mu0_isTight = true;
        mu0_iso04 = iso04;
        if ( isHighPt ) mu0_isHighPt = true;

        for (unsigned int i = 0, n = mu.numberOfSourceCandidatePtrs(); i < n; ++i) {
          muFootprint0.push_back(mu.sourceCandidatePtr(i));
        }
        if (verbose_) cout<<"Muon pT "<<mu.pt()<<" iso04 "<<iso04<<" isMedium "<<mu0_isTight<<" isTight "<<mu0_isTight<<" isHighPt "<<mu0_isHighPt<<endl;
      } 
      else if (count_mu==1){
        Lepton1IsMu  = 1; 
        mu1_p4.SetPtEtaPhiM( mu.pt(), mu.eta(), mu.phi(), mu.mass() );
        if ( isMedium ) mu1_isMedium = true;
        // Tight ID                                                                                                                                         
        if ( mu.isTightMuon(PV) ) mu1_isTight = true;
        if ( isHighPt ) mu1_isHighPt = true;
	mu1_iso04 = iso04;
        for (unsigned int i = 0, n = mu.numberOfSourceCandidatePtrs(); i < n; ++i) {
          muFootprint1.push_back(mu.sourceCandidatePtr(i));
        }
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

  TLorentzVector el0_p4, el1_p4;
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

  Float_t el1_absiso           =0;
  Float_t el1_relIsoWithDBeta  =0;
  Float_t el1_absiso_EA        =0;
  Float_t el1_relIsoWithEA     =0;
  int el1_iso_passHLTpre    = 0;
  int el1_iso_passLoose     = 0;
  int el1_iso_passMedium    = 0;
  int el1_iso_passTight     = 0;
  int el1_iso_passHEEP      = 0;
  int el1_noiso_passLoose   = 0;
  int el1_noiso_passMedium  = 0;
  int el1_noiso_passTight   = 0;
  int el1_noiso_passHEEP    = 0;
  int count_el=0;
  //int chargeEl = 0;

  std::vector<reco::CandidatePtr> elFootprint0, elFootprint1;

  for (size_t i = 0; i < electrons->size(); ++i){   
    const pat::Electron& electron = electrons->at(i);  
    const auto el = electrons->ptrAt(i);          // easier if we use ptrs for the id
    if (el->pt() < 50 || fabs(el->eta())>2.4 ) continue;
    //chargeEl = electron.charge();
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
      //if (count_el==0){
	//  if (verbose_) cout<<"Electron pT "<<el->pt()<<endl;

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

      if (count_el==0){
      if (verbose_) cout<<"Electron charge "<< electron.charge() <<endl;      
	if (verbose_) cout<<"Electron pT "<<el->pt()<<endl;
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
          elFootprint0.push_back(el->sourceCandidatePtr(i));
        }
      } 
      else if (count_el==1){
        el1_p4.SetPtEtaPhiM( el->pt(), el->eta(), el->phi(), el->mass() );
      
        el1_absiso           = absiso;
        el1_relIsoWithDBeta  = relIsoWithDBeta;
        el1_absiso_EA        = absiso_EA;
        el1_relIsoWithEA     = relIsoWithEA;

        el1_iso_passHLTpre    = (int) iso_passHLTpre   ;
        el1_iso_passLoose     = (int) iso_passLoose    ;
        el1_iso_passMedium    = (int) iso_passMedium   ;
        el1_iso_passTight     = (int) iso_passTight    ;
        el1_iso_passHEEP      = (int) iso_passHEEP     ;
        el1_noiso_passLoose   = (int) noiso_passLoose  ;
        el1_noiso_passMedium  = (int) noiso_passMedium ;
        el1_noiso_passTight   = (int) noiso_passTight  ;
        el1_noiso_passHEEP    = (int) noiso_passHEEP   ;

        for (unsigned int i = 0, n = el->numberOfSourceCandidatePtrs(); i < n; ++i) {
          elFootprint1.push_back(el->sourceCandidatePtr(i));
        }
      }
      count_el++;
    }
    //printf("elec with pt %4.1f, supercluster eta %+5.3f, sigmaIetaIeta %.3f (%.3f with full5x5 shower shapes), lost hits %d, pass conv veto %d\n",
    //              el.pt(), el.superCluster()->eta(), el.sigmaIetaIeta(), el.full5x5_sigmaIetaIeta(), el.gsfTrack()->trackerExpectedHitsInner().numberOfLostHits(), el.passConversionVeto());
  }

  TLorentzVector lep0_p4;
  TLorentzVector lep1_p4;

  int count_lep = count_mu + count_el;

  //these are initialized to zero if empty
  if (el0_p4.Pt() > mu0_p4.Pt()) {

    lep0_p4 = el0_p4;
    lep0flavor = 'e';
    Lepton0IsMu = 0;

    if (el1_p4.Pt() > mu0_p4.Pt()) {
      lep1_p4 = el1_p4;
      lep1flavor = 'e';
      Lepton1IsMu= 0;
    }
    else {
      lep1_p4 = mu0_p4;
      lep1flavor = 'm';
      Lepton1IsMu= 1;
    }
  }
  else {

    lep0_p4 = mu0_p4;
    lep0flavor = 'm';
    Lepton0IsMu= 1;
    if (mu1_p4.Pt() > el0_p4.Pt()) {
      lep1_p4 = mu1_p4;
      lep1flavor = 'm';
      Lepton1IsMu= 1;
    }
    else {
      lep1_p4 = el0_p4;
      lep1flavor = 'e';
      Lepton1IsMu= 0;
    }
  }
  if (lep0_p4.E() == 0) lep0flavor = 'x';
  if (lep1_p4.E() == 0) lep1flavor = 'x';

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
      if ( std::find(muFootprint0.begin(), muFootprint0.end(), constituent ) != muFootprint0.end() ) {
        uncorrJet -= constituent->p4();
        if ( verbose_ ) cout << "     -> REMOVED part of muon0" << endl;
      }
      else if ( std::find(muFootprint1.begin(), muFootprint1.end(), constituent ) != muFootprint1.end() ) {
        uncorrJet -= constituent->p4();
        if ( verbose_ ) cout << "     -> REMOVED part of muon1" << endl;
      }

      // If this constituent is part of an electron, remove the constituent's four vector
      else if ( std::find(elFootprint0.begin(), elFootprint0.end(), constituent ) != elFootprint0.end() ) {
        uncorrJet -= constituent->p4();
        if ( verbose_ ) cout << "     -> REMOVED part of electron0" << endl;
      }
      else if ( std::find(elFootprint1.begin(), elFootprint1.end(), constituent ) != elFootprint1.end() ) {
        uncorrJet -= constituent->p4();
        if ( verbose_ ) cout << "     -> REMOVED part of electron1" << endl;
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

                                                                                        
  //    ,ad8888ba,                                        88                                  
  //   d8"'    `"8b                                       88                ,d                
  //  d8'                                                 88                88                
  //  88              ,adPPYba,  8b,dPPYba,               88   ,adPPYba,  MM88MMM  ,adPPYba,  
  //  88      88888  a8P_____88  88P'   `"8a              88  a8P_____88    88     I8[    ""  
  //  Y8,        88  8PP"""""""  88       88              88  8PP"""""""    88      `"Y8ba,   
  //   Y8a.    .a88  "8b,   ,aa  88       88      88,   ,d88  "8b,   ,aa    88,    aa    ]8I  
  //    `"Y88888P"    `"Ybbd8"'  88       88       "Y8888P"    `"Ybbd8"'    "Y888  `"YbbdP"'  

  if (runSemiLeptTree_ && !iEvent.isRealData()) {

    v_genJetPt    ->clear();
    v_genJetEta   ->clear();
    v_genJetPhi   ->clear();
    v_genJetMass  ->clear();
    v_genJetArea  ->clear();

    edm::Handle<reco::GenJetCollection> AK8GENJET;  
    iEvent.getByToken(ak8genjetToken_, AK8GENJET);

    for (const reco::GenJet &ijet : *AK8GENJET) {
      if ( ijet.pt() < 15 ) continue;

      v_genJetPt  ->push_back( ijet.pt() );
      v_genJetEta ->push_back( ijet.eta() );
      v_genJetPhi ->push_back( ijet.phi() );
      v_genJetMass->push_back( ijet.mass() );
      v_genJetArea->push_back( ijet.jetArea() );
    }

    v_genJetSdPt    ->clear();
    v_genJetSdEta   ->clear();
    v_genJetSdPhi   ->clear();
    v_genJetSdMass  ->clear();
    v_genJetSdArea  ->clear();

    edm::Handle<reco::GenJetCollection> AK8GENJETSD;  
    iEvent.getByToken(ak8genjetSDToken_, AK8GENJETSD);

    for (const reco::GenJet &ijet : *AK8GENJETSD) {
      if ( ijet.pt() < 15 ) continue;

      v_genJetSdPt  ->push_back( ijet.pt() );
      v_genJetSdEta ->push_back( ijet.eta() );
      v_genJetSdPhi ->push_back( ijet.phi() );
      v_genJetSdMass->push_back( ijet.mass() );
      v_genJetSdArea->push_back( ijet.jetArea() );
    }
  }
                                                                                     
  //  88888888ba   88                                                                      
  //  88      "8b  88                          ,d                                          
  //  88      ,8P  88                          88                                          
  //  88aaaaaa8P'  88,dPPYba,    ,adPPYba,   MM88MMM   ,adPPYba,   8b,dPPYba,   ,adPPYba,  
  //  88""""""'    88P'    "8a  a8"     "8a    88     a8"     "8a  88P'   `"8a  I8[    ""  
  //  88           88       88  8b       d8    88     8b       d8  88       88   `"Y8ba,   
  //  88           88       88  "8a,   ,a8"    88,    "8a,   ,a8"  88       88  aa    ]8I  
  //  88           88       88   `"YbbdP"'     "Y888   `"YbbdP"'   88       88  `"YbbdP"'  
  // Here be photons!

  if (runSemiLeptTree_) {

    v_photonEta             ->clear();
    v_photonPhi             ->clear();
    v_photonPt              ->clear();
    v_photonSupClustEta     ->clear();
    v_photonSigIEtaIEta     ->clear();
    v_photonFullSigIEtaIEta ->clear();
    v_photonisTight         ->clear();
    v_photonisMedium        ->clear();
    v_photonisLoose         ->clear();
    v_NHadronIso            ->clear();
    v_CHadronIso            ->clear();
    v_PUCHadronIso          ->clear();
    v_photonIso             ->clear();
    v_PUPPIphotonIso        ->clear();
    v_PUPPINHadronIso       ->clear();
    v_PUPPICHadronIso       ->clear();

    edm::Handle<edm::View<pat::Photon>> photons;
    iEvent.getByToken(photonToken_, photons);
    for (const pat::Photon &pho : *photons) {
      if (pho.pt() < 20 or pho.chargedHadronIso()/pho.pt() > 0.3) continue;

        v_photonEta              ->push_back( pho.eta() );
        v_photonPhi              ->push_back( pho.phi() );
        v_photonPt              ->push_back( pho.pt() );
        v_photonSupClustEta     ->push_back( pho.superCluster()->eta() );
        v_photonSigIEtaIEta     ->push_back( pho.sigmaIetaIeta() );
        v_photonFullSigIEtaIEta ->push_back( pho.full5x5_sigmaIetaIeta() );
	//v_photonisTight         ->push_back( pho.egmPhotonIDs:cutBasedPhotonID-Spring16-V2p2-tight() );
	//v_photonisMedium        ->push_back( pho.egmPhotonIDs:cutBasedPhotonID-Spring16-V2p2-medium() );
	//v_photonisLoose         ->push_back( egmPhotonIDs:cutBasedPhotonID-Spring16-V2p2-loose() );
	v_NHadronIso            ->push_back( pho.neutralHadronIso()  );
	v_CHadronIso            ->push_back( pho.chargedHadronIso()  );
	v_PUCHadronIso          ->push_back( pho.puChargedHadronIso()  );
	v_photonIso             ->push_back( pho.photonIso()  );
        //v_PUPPIphotonIso        ->push_back( pho.puppiPhotonIso()  );
        //v_PUPPINHadronIso       ->push_back( pho.puppiNeutralHadronIso()  );
        //v_PUPPICHadronIso       ->push_back( pho.puppiChargedHadronIso()  );
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

  /*
  double closestAK8_to_Jet0_dR=99;
  double closestAK8_to_Jet1_dR=99;
  TLorentzVector closestAK8_to_Jet0_P4;
  TLorentzVector closestAK8_to_Jet1_P4;
  double closestAK8_to_Jet0_bdisc=-10;
  double closestAK8_to_Jet1_bdisc=-10;
  */

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
    
    /*
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
    */

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
    //double softDropMass = ijet.userFloat("ak8PFJetsCHSSoftDropMass");
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
    double subjet_corr_factor_L23res = 1.0 ;
    double subjet_corrDn_L23 = 1.0 ;
    double subjet_corrUp_L23 = 1.0 ;
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
        JetCorrUncertAK4chs->setJetPhi(  corrSubjetL123res.phi()  );
        JetCorrUncertAK4chs->setJetEta(  corrSubjetL123res.eta()  );
        JetCorrUncertAK4chs->setJetPt(   corrSubjetL123res.pt()   );
        double corrDn_temp2 = JetCorrUncertAK4chs->getUncertainty(0);
        subjet_corrDn_L23   = subjet_corr_factor_L23res - corrDn_temp2;
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
            subjet_corr_factor_L23res = subjet_corr_factor_L2 * subjet_corr_factor_L3 * subjet_corr_factor_res    ;
            if (verbose_) cout<<"        -> subjet corr: L1 "<<subjet_corr_factor_L1<<" L23 "<<subjet_corr_factor_L23<<" L23res "<<subjet_corr_factor_L23res<<" L123res "<<subjet_corr_factor_L123res<<endl;
            reco::Candidate::LorentzVector corrSubjetL23res   = subjet_corr_factor_L23res * uncorrSubjet;
            
            // //------------------------------------
            // // subjet JEC uncertainty
            // //------------------------------------
            // double subjet_corrDn_L23 =   1.0;
            // double subjet_corrDn_L123 = 1.0;
            JetCorrUncertAK4chs->setJetPhi(  corrSubjetL123res.phi()  );
            JetCorrUncertAK4chs->setJetEta(  corrSubjetL123res.eta()  );
            JetCorrUncertAK4chs->setJetPt(   corrSubjetL123res.pt()   );
            double corrDn_temp2 = JetCorrUncertAK4chs->getUncertainty(0);
            subjet_corrDn_L23   = subjet_corr_factor_L23res - corrDn_temp2;
            // subjet_corrDn_L123  = subjet_corr_factor_L123res_full - corrDn_temp2;

            // double subjet_corrUp_L23   = 1.0;
            // double subjet_corrUp_L123 = 1.0;
            JetCorrUncertAK4chs->setJetPhi(  corrSubjetL123res.phi()  );
            JetCorrUncertAK4chs->setJetEta(  corrSubjetL123res.eta()  );
            JetCorrUncertAK4chs->setJetPt(   corrSubjetL123res.pt()   );
            double corrUp_temp2 = JetCorrUncertAK4chs->getUncertainty(1);
            subjet_corrUp_L23   = subjet_corr_factor_L23res + corrUp_temp2;
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
      // FATAL ROOT error happening after this print statement
      
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
    if (verbose_) cout<<"    Debug0"<<endl;
    if (count_SD>1 && (sub0_P4_uncorr.Pt() < 1.0 || sub1_P4_uncorr.Pt() < 1.0 ) ){ 
      if (verbose_) cout<<"    Debug1"<<endl;
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
    if (verbose_) cout<<"    Debug1"<<endl;
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
    if (verbose_) cout<<"    Debug2"<<endl;
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
      if (verbose_) cout<<"    Debug4"<<endl;
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
      // FATAL root error after this line
      if (verbose_) cout<<"  PUPPI Debug0"<<endl;
    }

    if (verbose_) cout<<"  PUPPI Debug1"<<endl;
    TLorentzVector sumPUPsubjets_P4_uncorr          ;
    TLorentzVector sumPUPsubjets_P4_L23res          ;
    // TLorentzVector sumPUPsubjets_P4_L23resCorrUp    ;
    // TLorentzVector sumPUPsubjets_P4_L23resCorrDn    ;
    // TLorentzVector sumPUPsubjets_P4_L23resPtSmear   ;
    // TLorentzVector sumPUPsubjets_P4_L23resPtSmearUp ;
    // TLorentzVector sumPUPsubjets_P4_L23resPtSmearDn ;
    if (count_SD>1){ 
      if (verbose_) cout<<"  PUPPI Debug2"<<endl;
      sumPUPsubjets_P4_uncorr            = pup0_P4_uncorr            + pup1_P4_uncorr            ; 
      sumPUPsubjets_P4_L23res            = pup0_P4_L23res            + pup1_P4_L23res            ; 
      // sumPUPsubjets_P4_L23resCorrUp      = pup0_P4_L23resCorrUp      + pup1_P4_L23resCorrUp      ; 
      // sumPUPsubjets_P4_L23resCorrDn      = pup0_P4_L23resCorrDn      + pup1_P4_L23resCorrDn      ; 
      // sumPUPsubjets_P4_L23resPtSmear     = pup0_P4_L23resPtSmear     + pup1_P4_L23resPtSmear     ; 
      // sumPUPsubjets_P4_L23resPtSmearUp   = pup0_P4_L23resPtSmearUp   + pup1_P4_L23resPtSmearUp   ; 
      // sumPUPsubjets_P4_L23resPtSmearDn   = pup0_P4_L23resPtSmearDn   + pup1_P4_L23resPtSmearDn   ; 
    } 

    if (verbose_) cout<<"  PUPPI Debug3"<<endl;
    double pup_maxbdisc = 0 ;
    double pup_maxbdiscflav_hadron = 0 ;
    double pup_maxbdiscflav_parton = 0 ;
    if (pup0_bdisc>=pup1_bdisc){
      if (verbose_) cout<<"  PUPPI Debug4"<<endl;
      pup_maxbdisc = pup0_bdisc;
      pup_maxbdiscflav_hadron = pup0_flav_hadron;
      pup_maxbdiscflav_parton = pup0_flav_parton;
    } 
    else if (pup1_bdisc>pup0_bdisc){
      if (verbose_) cout<<"  PUPPI Debug5"<<endl;
      pup_maxbdisc = pup1_bdisc;
      pup_maxbdiscflav_hadron = pup1_flav_hadron;
      pup_maxbdiscflav_parton = pup1_flav_parton;
    }  


    
    //------------------------------------
    // Gen particle info     jet_matched_q || jet_matched_Wm || jet_matched_Z || jet_matched_Gamma 
    //------------------------------------ 
    double deltaR_jet_q = 99;
    double deltaR_jet_aq = 99;
    double deltaR_jet_p1 = 99;
    double deltaR_jet_p2 = 99;
    double deltaR_jet_Wp = 99;
    double deltaR_jet_Wm = 99;
    double deltaR_jet_Z1 = 99;
    double deltaR_jet_Z2 = 99;
    double deltaR_jet_G1 = 99;
    double deltaR_jet_G2 = 99;

    bool jet_matched_q = false;
    bool jet_matched_aq = false;
    bool jet_matched_p1 = false;
    bool jet_matched_p2 = false;
    bool jet_matched_Wp = false;
    bool jet_matched_Wm = false;
    bool jet_matched_Z1 = false;
    bool jet_matched_Z2 = false;
    bool jet_matched_G1 = false;
    bool jet_matched_G2 = false;


    if (!iEvent.isRealData() and runGenLoop_) {
      if (verbose_) cout<<"  PUPPI Debug6"<<endl;
      if (qhard_p4.Pt() > 1. ) deltaR_jet_q = jet_p4.DeltaR(qhard_p4  );
      if (antiqhard_p4.Pt() > 1. ) deltaR_jet_aq = jet_p4.DeltaR(antiqhard_p4  );
      if (hardest_parton_hardScatterOutgoing_p4.Pt() > 1. ) deltaR_jet_p1 = jet_p4.DeltaR(hardest_parton_hardScatterOutgoing_p4        );
      if (second_hardest_parton_hardScatterOutgoing_p4.Pt() > 1. ) deltaR_jet_p2 = jet_p4.DeltaR(second_hardest_parton_hardScatterOutgoing_p4 );
      if (Wp_p4.Pt() > 1. ) deltaR_jet_Wp = jet_p4.DeltaR(Wp_p4  );
      if (Wm_p4.Pt() > 1. ) deltaR_jet_Wm = jet_p4.DeltaR(Wm_p4  );
      if (Z1_p4.Pt() > 1. ) deltaR_jet_Z1 = jet_p4.DeltaR(Z1_p4  );
      if (Z2_p4.Pt() > 1. ) deltaR_jet_Z2 = jet_p4.DeltaR(Z2_p4  );
      if (Gamma1_p4.Pt() > 1. ) deltaR_jet_G1 = jet_p4.DeltaR(Gamma1_p4  );
      if (Gamma2_p4.Pt() > 1. ) deltaR_jet_G2 = jet_p4.DeltaR(Gamma2_p4  );
      if (verbose_) cout<<"  PUPPI Debug7"<<endl;
      if (deltaR_jet_q<deltaR_jet_aq) jet_matched_q = true;
      if (deltaR_jet_aq<deltaR_jet_q) jet_matched_aq = true;
      if (deltaR_jet_p1<deltaR_jet_p2) jet_matched_p1 = true;
      if (deltaR_jet_p2<deltaR_jet_p1) jet_matched_p2 = true;
      if (deltaR_jet_Wp<deltaR_jet_Wm) jet_matched_Wp = true;
      if (deltaR_jet_Wm<deltaR_jet_Wp) jet_matched_Wm = true;
      if (deltaR_jet_Z1<deltaR_jet_Z2) jet_matched_Z1 = true;
      if (deltaR_jet_Z2<deltaR_jet_Z1) jet_matched_Z2 = true;
      if (deltaR_jet_G1<deltaR_jet_G2) jet_matched_G1 = true;
      if (deltaR_jet_G2<deltaR_jet_G1) jet_matched_G2 = true;
      if (verbose_) cout<<"  PUPPI Debug8"<<endl;
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
    if (runSemiLeptTree_ && count_lep >=0 ){
      double deltaPhi_lep_jet = fabs( deltaPhi(corrJet.phi(), lep0_p4.Phi() )) ;
      if (verbose_) cout<<"  -> deltaPhi_lep_jet "<<deltaPhi_lep_jet<<endl;
      // AK8 jet should be in opposite hemisphere from lepton. If leading jet matches then use it. If it doensn't then check the second leading jet.
      //if ( ((count_AK8CHS==0&& deltaPhi_lep_jet >=3.14/2) || (count_AK8CHS==1&&deltaPhi_lep_jet >=3.14/2)) && count_fill_leptTree==0 ){
        if (verbose_) cout<<"Put jet variables in semilept tree  -> count_AK8CHS "<<count_AK8CHS<<" count_fill_leptTree"<<count_fill_leptTree<<endl;
        count_fill_leptTree++;
        AK8jet_SemiLept_P4corr.SetPtEtaPhiM( corrJet.pt(), corrJet.eta(), corrJet.phi(), corrJet.mass() );

        DeltaRJetLep0                          = deltaR(corrJet.eta(), corrJet.phi(), lep0_p4.Eta(), lep0_p4.Phi() );
        DeltaPhiJetLep0                        = deltaPhi_lep_jet    ;

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
    
        // AK4PUPPI JEC scale nom/up/down  (use for both full jet and groomed mass corrections)                             
                                                                                                                          
        JetAK4PuppiCorrFactor                    = subjet_corr_factor_L23res ;
        JetAK4PuppiCorrFactorUp                  = subjet_corrUp_L23;
        JetAK4PuppiCorrFactorDn                  = subjet_corrDn_L23;
                  

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
          // Drell Yan  
          if (countObj>=1 && objPDGID==-1){
            JetGenMatched_NgenDYObjs = (int) count_gen_truth_hadronic_obj  ; 
            Genl0PDGid                         = genl1PDGID                       ;    
            Genl1PDGid                         = genl2PDGID                       ;                      
            JetGenMatched_l0Pt                 = l1_p4.Perp()                    ;
            JetGenMatched_l0Eta                = l1_p4.Eta()                     ;
            JetGenMatched_l0Phi                = l1_p4.Phi()                     ;
            JetGenMatched_l0Mass               = l1_p4.M()                       ;            
            JetGenMatched_l1Pt                 = l2_p4.Perp()                    ;
            JetGenMatched_l1Eta                = l2_p4.Eta()                     ;
            JetGenMatched_l1Phi                = l2_p4.Phi()                     ;
            JetGenMatched_l1Mass               = l2_p4.M()                       ;  
          }


          if (countObj>=1 && (jet_matched_q || jet_matched_Wp || jet_matched_Z1 || jet_matched_G1 ) ){
            if (objPDGID== genQuarkPDGID)  JetGenMatched_QuarkNpartonsStatus20to30         = (int) count_gen_truth_hadronic_obj   ;
            GenQuarkPDGid                       = genQuarkPDGID                       ;
            JetGenMatched_QuarkPt               = qhard_p4.Perp()                   ;
            JetGenMatched_QuarkEta              = qhard_p4.Eta()                    ;
            JetGenMatched_QuarkPhi              = qhard_p4.Phi()                    ;
            JetGenMatched_QuarkMass             = qhard_p4.M()                      ;
            //JetGenMatched_AntiQuarkPt               = antiqhard_p4.Perp()                   ;
            //JetGenMatched_AntiQuarkEta              = antiqhard_p4.Eta()                    ;
            //JetGenMatched_AntiQuarkPhi              = antiqhard_p4.Phi()                    ;
            //JetGenMatched_AntiQuarkMass             = antiqhard_p4.M()                      ;
        
	    //     JetGenMatched_bPt                 = b1_p4.Perp()                   ;

            if (objPDGID==24) JetGenMatched_WNpartonsStatus20to30         = (int) count_gen_truth_hadronic_obj  ;    
            JetGenMatched_WplusPt                 = Wp_p4.Perp()                   ;
            JetGenMatched_WplusEta                = Wp_p4.Eta()                    ;
            JetGenMatched_WplusPhi                = Wp_p4.Phi()                    ;
            JetGenMatched_WplusMass               = Wp_p4.M()                      ;
	    //JetGenMatched_WminusPt                 = Wm_p4.Perp()                   ;
            //JetGenMatched_WminusEta                = Wm_p4.Eta()                    ;
            //JetGenMatched_WminusPhi                = Wm_p4.Phi()                    ;
            //JetGenMatched_WminusMass               = Wm_p4.M()                      ;

            if (objPDGID==23) JetGenMatched_ZNpartonsStatus20to30         = (int) count_gen_truth_hadronic_obj    ;
            JetGenMatched_Z0Pt                 = Z1_p4.Perp()                    ;
            JetGenMatched_Z0Eta                = Z1_p4.Eta()                     ;
            JetGenMatched_Z0Phi                = Z1_p4.Phi()                     ;
            JetGenMatched_Z0Mass               = Z1_p4.M()                       ;
            //JetGenMatched_Z1Pt                 = Z2_p4.Perp()                    ;
            //JetGenMatched_Z1Eta                = Z2_p4.Eta()                     ;
	    // JetGenMatched_Z1Phi                = Z2_p4.Phi()                     ;
            //JetGenMatched_Z1Mass               = Z2_p4.M()                       ;
       
            if (objPDGID==22) JetGenMatched_GammaNpartonsStatus20to30         = (int) count_gen_truth_hadronic_obj  ;
            JetGenMatched_Gamma0Pt                 = Gamma1_p4.Perp()                    ;
            JetGenMatched_Gamma0Eta                = Gamma1_p4.Eta()                     ;
            JetGenMatched_Gamma0Phi                = Gamma1_p4.Phi()                     ;
            JetGenMatched_Gamma0Mass               = Gamma1_p4.M()                       ;
            //JetGenMatched_Gamma1Pt                 = Gamma2_p4.Perp()                    ;
            //JetGenMatched_Gamma1Eta                = Gamma2_p4.Eta()                     ;
            //JetGenMatched_Gamma1Phi                = Gamma2_p4.Phi()                     ;
            //JetGenMatched_Gamma1Mass               = Gamma2_p4.M()                       ;
	  }   // countObj>=1

          if (countObj>=1 && (jet_matched_aq || jet_matched_Wm || jet_matched_Z2 || jet_matched_G2 ) ){
            if (objPDGID== genQuarkPDGID)  JetGenMatched_QuarkNpartonsStatus20to30         = (int) count_gen_truth_hadronic_obj   ;
            GenQuarkPDGid                       = genQuarkPDGID                       ;
            //JetGenMatched_QuarkPt               = qhard_p4.Perp()                   ;
            //JetGenMatched_QuarkEta              = qhard_p4.Eta()                    ;
            //JetGenMatched_QuarkPhi              = qhard_p4.Phi()                    ;
            //JetGenMatched_QuarkMass             = qhard_p4.M()                      ;
            JetGenMatched_AntiQuarkPt               = antiqhard_p4.Perp()                   ;
            JetGenMatched_AntiQuarkEta              = antiqhard_p4.Eta()                    ;
            JetGenMatched_AntiQuarkPhi              = antiqhard_p4.Phi()                    ;
            JetGenMatched_AntiQuarkMass             = antiqhard_p4.M()                      ;

            //     JetGenMatched_bPt                 = b1_p4.Perp()                   ;                                                                                                                            

            if (objPDGID==24) JetGenMatched_WNpartonsStatus20to30         = (int) count_gen_truth_hadronic_obj  ;
	    // JetGenMatched_WplusPt                 = Wp_p4.Perp()                   ;
            //JetGenMatched_WplusEta                = Wp_p4.Eta()                    ;
            //JetGenMatched_WplusPhi                = Wp_p4.Phi()                    ;
            //JetGenMatched_WplusMass               = Wp_p4.M()                      ;
            JetGenMatched_WminusPt                 = Wm_p4.Perp()                   ;
            JetGenMatched_WminusEta                = Wm_p4.Eta()                    ;
            JetGenMatched_WminusPhi                = Wm_p4.Phi()                    ;
            JetGenMatched_WminusMass               = Wm_p4.M()                      ;



            if (objPDGID==23) JetGenMatched_ZNpartonsStatus20to30         = (int) count_gen_truth_hadronic_obj    ;
            //JetGenMatched_Z0Pt                 = Z1_p4.Perp()                    ;
            //JetGenMatched_Z0Eta                = Z1_p4.Eta()                     ;
            //JetGenMatched_Z0Phi                = Z1_p4.Phi()                     ;
            //JetGenMatched_Z0Mass               = Z1_p4.M()                       ;
            JetGenMatched_Z1Pt                 = Z2_p4.Perp()                    ;
            JetGenMatched_Z1Eta                = Z2_p4.Eta()                     ;
            JetGenMatched_Z1Phi                = Z2_p4.Phi()                     ;
            JetGenMatched_Z1Mass               = Z2_p4.M()                       ;

            if (objPDGID==22) JetGenMatched_GammaNpartonsStatus20to30         = (int) count_gen_truth_hadronic_obj  ;
            //JetGenMatched_Gamma0Pt                 = Gamma1_p4.Perp()                    ;
            //JetGenMatched_Gamma0Eta                = Gamma1_p4.Eta()                     ;
            //JetGenMatched_Gamma0Phi                = Gamma1_p4.Phi()                     ;
            //JetGenMatched_Gamma0Mass               = Gamma1_p4.M()                       ;
            JetGenMatched_Gamma1Pt                 = Gamma2_p4.Perp()                    ;
            JetGenMatched_Gamma1Eta                = Gamma2_p4.Eta()                     ;
            JetGenMatched_Gamma1Phi                = Gamma2_p4.Phi()                     ;
            JetGenMatched_Gamma1Mass               = Gamma2_p4.M()                       ;
          }   // countObj>=1  
          if (countObj==0 && jet_matched_p1 ){


	  JetGenMatched_partonPt               = hardest_parton_hardScatterOutgoing_p4.Perp()           ;                                                                                                        
	  JetGenMatched_partonEta              = hardest_parton_hardScatterOutgoing_p4.Eta()            ;                                                                                                        
	  JetGenMatched_partonPhi              = hardest_parton_hardScatterOutgoing_p4.Phi()            ;                                                                                                        
	  JetGenMatched_partonMass             = hardest_parton_hardScatterOutgoing_p4.M()              ;                                                                                                        
	  JetGenMatched_partonID               = parton1id                                              ;                                                                                                        
	  JetGenMatched_DeltaRjetParton        = deltaR_jet_p1                                          ;   
          }
          if (countObj==0 && jet_matched_p2 ){
            JetGenMatched_partonPt               = second_hardest_parton_hardScatterOutgoing_p4.Perp()    ;                                                                                                       
            JetGenMatched_partonEta              = second_hardest_parton_hardScatterOutgoing_p4.Eta()     ;                                                                                                       
            JetGenMatched_partonPhi              = second_hardest_parton_hardScatterOutgoing_p4.Phi()     ;                                                                                                       
            JetGenMatched_partonMass             = second_hardest_parton_hardScatterOutgoing_p4.M()       ;                                                                                                       
            JetGenMatched_partonID               = parton2id                                              ;                                                                                                       
            JetGenMatched_DeltaRjetParton        = deltaR_jet_p2                                          ;   
	  }
 
  
	} // if MC and GenLoop On
        
	 }
	//} // end if this jet is opposite the lepton
	count_AK8CHS++; 
   }// end if event has >=1 lepton
  //  count_AK8CHS++;
  // }


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
     
  if ( count_lep >=1 && verbose_){
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
  if ( AK8jet_SemiLept_P4corr.Perp()>200 ) count_fill_leptTree++ ;
  if (verbose_) cout<<"count_fill_leptTree "<<count_fill_leptTree<<endl;
  if (runSemiLeptTree_ && count_lep >=0 ){
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
          SemiLeptGenCountHadObj       = count_gen_truth_hadronic_obj;            
          SemiLeptGenObjPDGID          = objPDGID ;
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
          SemiLeptGenCountHadObj       = 0;
          SemiLeptGenObjPDGID          = 0;            
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

        AK4_dRminLep0_Pt        = AK4_dRMinLep_p4.Perp() ;
        AK4_dRminLep0_Eta       = AK4_dRMinLep_p4.Eta()  ;
        AK4_dRminLep0_Phi       = AK4_dRMinLep_p4.Phi()  ;
        AK4_dRminLep0_Mass      = AK4_dRMinLep_p4.M()    ;
        AK4_dRminLep0_Bdisc     = AK4_dRMinLep_bdisc     ;
        AK4_dRminLep0_dRlep     = AK4_dRMinLep_deltaR    ;
        AK4_dRminLep0_dRak8     = AK4_dRMinLep_p4.DeltaR( AK8jet_SemiLept_P4corr  ) ;
       
        AK4_dRminLep0_PtSmear   = AK4_dRMinLep_ptsmear    ;
        AK4_dRminLep0_PtSmearUp = AK4_dRMinLep_ptsmearUp  ;
        AK4_dRminLep0_PtSmearDn = AK4_dRMinLep_ptsmearDn  ;
        AK4_dRminLep0_PtUncorr  = AK4_dRMinLep_ptuncorr   ;

        AK4_dRminLep0_Corr      = AK4_dRMinLep_corr       ;
        AK4_dRminLep0_CorrUp    = AK4_dRMinLep_corrUp     ;
        AK4_dRminLep0_CorrDn    = AK4_dRMinLep_corrDn     ;

        // Closest b-tagged jet to the lepton
        // I don't think we need this 
        // AK4BtagdRminPt    = AK4_btagged_dRMinLep_p4.Perp();
        // AK4BtagdRminBdisc = AK4_btagged_dRMinLep_bdisc    ;
        // AK4BtagdRminLep   = AK4_btagged_dRMinLep          ;
       
        Lep0HemiContainsAK4BtagLoose  = (int)  ak4_btag_loose;
        Lep0HemiContainsAK4BtagMedium = (int)  ak4_btag_medium;
        Lep0HemiContainsAK4BtagTight  = (int)  ak4_btag_tight;

        LeptonPhi0   = lep0_p4.Phi()  ; 
        LeptonPt0    = lep0_p4.Perp() ;  
        LeptonEta0   = lep0_p4.Eta()  ; 
        LeptonMass0  = lep0_p4.M() ; 
        LeptonPhi1   = lep1_p4.Phi()  ; 
        LeptonPt1    = lep1_p4.Perp() ;  
        LeptonEta1   = lep1_p4.Eta()  ; 
        LeptonMass1  = lep1_p4.M() ;

     
	//  if      (count_mu==1 && count_el==0) LeptonIsMu  = 1  ; 
        //else if (count_mu==0 && count_el==1) LeptonIsMu  = 0  ; 
        //else                                 LeptonIsMu  = -1  ;
     
        PtRel0  = AK4_dRMinLep_p4.Perp( lep0_p4.Vect() );
        Mu0Iso  = mu0_iso04;

        Elecron0_absiso            = el0_absiso           ;  
        Elecron0_relIsoWithDBeta   = el0_relIsoWithDBeta  ;  
        Elecron0_absiso_EA         = el0_absiso_EA        ;  
        Elecron0_relIsoWithEA      = el0_relIsoWithEA     ;  

        Electron0_iso_passHLTpre   = el0_iso_passHLTpre  ;
        Electron0_iso_passLoose    = el0_iso_passLoose   ;
        Electron0_iso_passMedium   = el0_iso_passMedium  ;
        Electron0_iso_passTight    = el0_iso_passTight   ;
        Electron0_iso_passHEEP     = el0_iso_passHEEP    ;
        Electron0_noiso_passLoose  = el0_noiso_passLoose ;
        Electron0_noiso_passMedium = el0_noiso_passMedium;
        Electron0_noiso_passTight  = el0_noiso_passTight ;
        Electron0_noiso_passHEEP   = el0_noiso_passHEEP  ;

        Mu0Medium = (int) mu0_isMedium   ;
        Mu0Tight  = (int) mu0_isTight    ;
        Mu0HighPt = (int) mu0_isHighPt   ;

        PtRel1  = 0. ; //AK4_dRMinLep_p4.Perp( lep1_p4.Vect() );
	Mu1Iso  = mu1_iso04;

        Elecron1_absiso            = el1_absiso           ;
        Elecron1_relIsoWithDBeta   = el1_relIsoWithDBeta  ;
        Elecron1_absiso_EA         = el1_absiso_EA        ;
        Elecron1_relIsoWithEA      = el1_relIsoWithEA     ;

        Electron1_iso_passHLTpre   = el1_iso_passHLTpre  ;
        Electron1_iso_passLoose    = el1_iso_passLoose   ;
        Electron1_iso_passMedium   = el1_iso_passMedium  ;
        Electron1_iso_passTight    = el1_iso_passTight   ;
	Electron1_iso_passHEEP     = el1_iso_passHEEP    ;
        Electron1_noiso_passLoose  = el1_noiso_passLoose ;
        Electron1_noiso_passMedium = el1_noiso_passMedium;
        Electron1_noiso_passTight  = el1_noiso_passTight ;
	Electron1_noiso_passHEEP   = el1_noiso_passHEEP  ;

        Mu1Medium = (int) mu1_isMedium   ;
        Mu1Tight  = (int) mu1_isTight    ;
        Mu1HighPt = (int) mu1_isHighPt   ;

        TreeSemiLept -> Fill();
      }// end rapidity selection
    }// end pt selection
  } 

  jecPayloadsAK4chsFinal  .clear();
  jecPayloadsAK8chsFinal  .clear();
  jecPayloadsAK4pupFinal  .clear();
  jecPayloadsAK8pupFinal  .clear();

}


// ------------ method called once each job just before starting event loop  ----------
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
