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

// TFile
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

// utilities
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
      edm::EDGetTokenT<reco::GenJetCollection> ak4genjetToken_;
      edm::EDGetTokenT<reco::GenJetCollection> ak8genjetToken_;
      edm::EDGetTokenT<edm::View<reco::GenParticle> > prunedGenToken_;
      edm::EDGetTokenT<double> rhoToken_;
      edm::EDGetTokenT<std::vector<reco::Vertex> > vtxToken_;
      edm::EDGetTokenT<edm::TriggerResults> triggerResultsMETFilterToken_;
      edm::EDGetTokenT<edm::TriggerResults> triggerResultsHLTToken_;

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

      TTree *TreeAllHad;

      Float_t Jet0PtRaw                             ;
      Float_t Jet0EtaRaw                            ;
      Float_t Jet0PhiRaw                            ;
      Float_t Jet0MassRaw                           ;
      Float_t Jet0P                                 ;
      Float_t Jet0Pt                                ;
      Float_t Jet0Eta                               ;
      Float_t Jet0Phi                               ;
      Float_t Jet0Rap                               ;
      Float_t Jet0Energy                            ;
      Float_t Jet0Mass                              ;
      Float_t Jet0Area                              ;
      Float_t Jet0MassSoftDrop                      ;
      Float_t Jet0MassSDsumSubjetRaw                ;
      Float_t Jet0MassSDsumSubjetCorrL23           ;
      Float_t Jet0MassSDsumSubjetCorrL23Up         ;
      Float_t Jet0MassSDsumSubjetCorrL23Dn         ;
      Float_t Jet0MassSDsumSubjetCorrL123         ;
      Float_t Jet0MassSDsumSubjetCorrL123Up       ;
      Float_t Jet0MassSDsumSubjetCorrL123Dn       ;
      Float_t Jet0MassSDsumSubjetCorrSmear          ;
      Float_t Jet0MassSDsumSubjetCorrSmearUp        ;
      Float_t Jet0MassSDsumSubjetCorrSmearDn        ;
      Float_t Jet0MassPruned                        ;
      Float_t Jet0Tau1                              ;
      Float_t Jet0Tau2                              ;
      Float_t Jet0Tau3                              ;
      Float_t Jet0Tau32                             ;
      Float_t Jet0Tau21                             ;
      Float_t Jet0SDbdisc0                          ;
      Float_t Jet0SDbdisc1                          ;
      Float_t Jet0SDmaxbdisc                        ;
      Float_t Jet0SDmaxbdiscflavHadron                    ;
      Float_t Jet0SDmaxbdiscflavParton                    ;
      Float_t Jet0SDsubjet0pt                       ;
      Float_t Jet0SDsubjet0mass                     ;
      Float_t Jet0SDsubjet0area                     ;
      Float_t Jet0SDsubjet0flavHadron                     ;
      Float_t Jet0SDsubjet0flavParton                     ;
      Float_t Jet0SDsubjet1pt                       ;
      Float_t Jet0SDsubjet1mass                     ;
      Float_t Jet0SDsubjet1area                     ;
      Float_t Jet0SDsubjet1flavHadron                     ;
      Float_t Jet0SDsubjet1flavParton                     ;
      Float_t Jet0PuppiPt                           ;
      Float_t Jet0PuppiEta                          ;
      Float_t Jet0PuppiPhi                          ;
      Float_t Jet0PuppiMass                         ;
      Float_t Jet0PuppiMassSoftDrop                 ;
      Float_t Jet0PuppiMassSDsumSubjetRaw           ;
      Float_t Jet0PuppiMassSDsumSubjetCorr          ;
      Float_t Jet0PuppiMassSDsumSubjetCorrUp        ;
      Float_t Jet0PuppiMassSDsumSubjetCorrDn        ;
      Float_t Jet0PuppiMassSDsumSubjetCorrSmear     ;
      Float_t Jet0PuppiMassSDsumSubjetCorrSmearUp   ;
      Float_t Jet0PuppiMassSDsumSubjetCorrSmearDn   ;
      Float_t Jet0PuppiTau1                         ;
      Float_t Jet0PuppiTau2                         ;
      Float_t Jet0PuppiTau3                         ;
      Float_t Jet0PuppiTau32                        ;
      Float_t Jet0PuppiTau21                        ;
      Float_t Jet0PuppiSDbdisc0                     ;
      Float_t Jet0PuppiSDbdisc1                     ;
      Float_t Jet0PuppiSDmaxbdisc                   ;
      Float_t Jet0PuppiSDmaxbdiscflavHadron               ;
      Float_t Jet0PuppiSDmaxbdiscflavParton               ;
      Float_t Jet0PuppiSDsubjet0pt                  ;
      Float_t Jet0PuppiSDsubjet0mass                ;
      Float_t Jet0PuppiSDsubjet0area                ;
      Float_t Jet0PuppiSDsubjet0flavHadron                ;
      Float_t Jet0PuppiSDsubjet0flavParton                ;
      Float_t Jet0PuppiSDsubjet1pt                  ;
      Float_t Jet0PuppiSDsubjet1mass                ;
      Float_t Jet0PuppiSDsubjet1area                ;
      Float_t Jet0PuppiSDsubjet1flavHadron                ;
      Float_t Jet0PuppiSDsubjet1flavParton                ;
      Float_t Jet0CHF                               ;
      Float_t Jet0NHF                               ;
      Float_t Jet0CM                                ;
      Float_t Jet0NM                                ;
      Float_t Jet0NEF                               ;
      Float_t Jet0CEF                               ;
      Float_t Jet0MF                                ;
      Float_t Jet0Mult                              ;
      Float_t Jet0MassCorrFactor                    ;
      Float_t Jet0MassCorrFactorUp                  ;
      Float_t Jet0MassCorrFactorDn                  ;
      Float_t Jet0CorrFactor                        ;
      Float_t Jet0CorrFactorUp                      ;
      Float_t Jet0CorrFactorDn                      ;
      Float_t Jet0PtSmearFactor                     ;
      Float_t Jet0PtSmearFactorUp                   ;
      Float_t Jet0PtSmearFactorDn                   ;
      Float_t Jet0PuppiMassCorrFactor               ;
      Float_t Jet0PuppiMassCorrFactorUp             ;
      Float_t Jet0PuppiMassCorrFactorDn             ;
      Float_t Jet0PuppiCorrFactor                   ;
      Float_t Jet0PuppiCorrFactorUp                 ;
      Float_t Jet0PuppiCorrFactorDn                 ;
      Float_t Jet0PuppiPtSmearFactor                ;
      Float_t Jet0PuppiPtSmearFactorUp              ;
      Float_t Jet0PuppiPtSmearFactorDn              ;
      Float_t Jet0EtaScaleFactor                    ;
      Float_t Jet0PhiScaleFactor                    ;
      Float_t Jet0MatchedGenJetDR                   ;
      Float_t Jet0MatchedGenJetPt                   ;
      Float_t Jet0MatchedGenJetMass                 ;

      Float_t Jet1PtRaw                             ;
      Float_t Jet1EtaRaw                            ;
      Float_t Jet1PhiRaw                            ;
      Float_t Jet1MassRaw                           ;
      Float_t Jet1P                                 ;
      Float_t Jet1Pt                                ;
      Float_t Jet1Eta                               ;
      Float_t Jet1Phi                               ;
      Float_t Jet1Rap                               ;
      Float_t Jet1Energy                            ;
      Float_t Jet1Mass                              ;
      Float_t Jet1Area                              ;
      Float_t Jet1MassSoftDrop                      ;
      Float_t Jet1MassSDsumSubjetRaw                ;
      Float_t Jet1MassSDsumSubjetCorrL23           ;
      Float_t Jet1MassSDsumSubjetCorrL23Up         ;
      Float_t Jet1MassSDsumSubjetCorrL23Dn         ;
      Float_t Jet1MassSDsumSubjetCorrL123         ;
      Float_t Jet1MassSDsumSubjetCorrL123Up       ;
      Float_t Jet1MassSDsumSubjetCorrL123Dn       ;
      Float_t Jet1MassSDsumSubjetCorrSmear          ;
      Float_t Jet1MassSDsumSubjetCorrSmearUp        ;
      Float_t Jet1MassSDsumSubjetCorrSmearDn        ;
      Float_t Jet1MassPruned                        ;
      Float_t Jet1Tau1                              ;
      Float_t Jet1Tau2                              ;
      Float_t Jet1Tau3                              ;
      Float_t Jet1Tau32                             ;
      Float_t Jet1Tau21                             ;
      Float_t Jet1SDbdisc0                          ;
      Float_t Jet1SDbdisc1                          ;
      Float_t Jet1SDmaxbdisc                        ;
      Float_t Jet1SDmaxbdiscflavHadron                    ;
      Float_t Jet1SDmaxbdiscflavParton                    ;
      Float_t Jet1SDsubjet0pt                       ;
      Float_t Jet1SDsubjet0mass                     ;
      Float_t Jet1SDsubjet0area                     ;
      Float_t Jet1SDsubjet0flavHadron                     ;
      Float_t Jet1SDsubjet0flavParton                     ;
      Float_t Jet1SDsubjet1pt                       ;
      Float_t Jet1SDsubjet1mass                     ;
      Float_t Jet1SDsubjet1area                     ;
      Float_t Jet1SDsubjet1flavHadron                     ;
      Float_t Jet1SDsubjet1flavParton                     ;
      Float_t Jet1PuppiPt                           ;
      Float_t Jet1PuppiEta                          ;
      Float_t Jet1PuppiPhi                          ;
      Float_t Jet1PuppiMass                         ;
      Float_t Jet1PuppiMassSoftDrop                 ;
      Float_t Jet1PuppiMassSDsumSubjetRaw           ;
      Float_t Jet1PuppiMassSDsumSubjetCorr          ;
      Float_t Jet1PuppiMassSDsumSubjetCorrUp        ;
      Float_t Jet1PuppiMassSDsumSubjetCorrDn        ;
      Float_t Jet1PuppiMassSDsumSubjetCorrSmear     ;
      Float_t Jet1PuppiMassSDsumSubjetCorrSmearUp   ;
      Float_t Jet1PuppiMassSDsumSubjetCorrSmearDn   ;
      Float_t Jet1PuppiTau1                         ;
      Float_t Jet1PuppiTau2                         ;
      Float_t Jet1PuppiTau3                         ;
      Float_t Jet1PuppiTau32                        ;
      Float_t Jet1PuppiTau21                        ;
      Float_t Jet1PuppiSDbdisc0                     ;
      Float_t Jet1PuppiSDbdisc1                     ;
      Float_t Jet1PuppiSDmaxbdisc                   ;
      Float_t Jet1PuppiSDmaxbdiscflavHadron               ;
      Float_t Jet1PuppiSDmaxbdiscflavParton               ;
      Float_t Jet1PuppiSDsubjet0pt                  ;
      Float_t Jet1PuppiSDsubjet0mass                ;
      Float_t Jet1PuppiSDsubjet0area                ;
      Float_t Jet1PuppiSDsubjet0flavHadron                ;
      Float_t Jet1PuppiSDsubjet0flavParton                ;
      Float_t Jet1PuppiSDsubjet1pt                  ;
      Float_t Jet1PuppiSDsubjet1mass                ;
      Float_t Jet1PuppiSDsubjet1area                ;
      Float_t Jet1PuppiSDsubjet1flavHadron                ;
      Float_t Jet1PuppiSDsubjet1flavParton                ;
      Float_t Jet1CHF                               ;
      Float_t Jet1NHF                               ;
      Float_t Jet1CM                                ;
      Float_t Jet1NM                                ;
      Float_t Jet1NEF                               ;
      Float_t Jet1CEF                               ;
      Float_t Jet1MF                                ;
      Float_t Jet1Mult                              ;
      Float_t Jet1MassCorrFactor                    ;
      Float_t Jet1MassCorrFactorUp                  ;
      Float_t Jet1MassCorrFactorDn                  ;
      Float_t Jet1CorrFactor                        ;
      Float_t Jet1CorrFactorUp                      ;
      Float_t Jet1CorrFactorDn                      ;
      Float_t Jet1PtSmearFactor                     ;
      Float_t Jet1PtSmearFactorUp                   ;
      Float_t Jet1PtSmearFactorDn                   ;
      Float_t Jet1PuppiMassCorrFactor               ;
      Float_t Jet1PuppiMassCorrFactorUp             ;
      Float_t Jet1PuppiMassCorrFactorDn             ;
      Float_t Jet1PuppiCorrFactor                   ;
      Float_t Jet1PuppiCorrFactorUp                 ;
      Float_t Jet1PuppiCorrFactorDn                 ;
      Float_t Jet1PuppiPtSmearFactor                ;
      Float_t Jet1PuppiPtSmearFactorUp              ;
      Float_t Jet1PuppiPtSmearFactorDn              ;
      Float_t Jet1EtaScaleFactor                    ;
      Float_t Jet1PhiScaleFactor                    ;
      Float_t Jet1MatchedGenJetDR                   ;
      Float_t Jet1MatchedGenJetPt                   ;
      Float_t Jet1MatchedGenJetMass                 ;

      Float_t AllHadMETpx                           ;           
      Float_t AllHadMETpy                           ;           
      Float_t AllHadMETpt                           ;           
      Float_t AllHadMETphi                          ;           
      Float_t AllHadNvtx                            ;           
      Float_t AllHadRho                             ;           
      Float_t AllHadEventWeight                     ;           
      Float_t DijetMass                             ;           
      Float_t DijetDeltaR                           ;           
      Float_t DijetDeltaPhi                         ;           
      Float_t DijetDeltaRap                         ;           
      Float_t DiGenJetMass                          ;           
      Float_t GenTTmass                             ;           
      Float_t HT                                    ;           
      Float_t HT_CorrDn                             ;           
      Float_t HT_CorrUp                             ;           
      Float_t HT_PtSmearUp                          ;           
      Float_t HT_PtSmearDn                          ;           
      Float_t Q2weight_CorrDn                       ;           
      Float_t Q2weight_CorrUp                       ;           
      Float_t NNPDF3weight_CorrDn                   ;           
      Float_t NNPDF3weight_CorrUp                   ;           
      Float_t AllHadRunNum                          ;           
      Float_t AllHadLumiBlock                       ;           
      Float_t AllHadEventNum                        ;           
        

};

//
// constructors and destructor
//
B2GTTbarTreeMaker::B2GTTbarTreeMaker(const edm::ParameterSet& iConfig):
    ak4jetToken_(consumes<pat::JetCollection>(edm::InputTag("slimmedJets"))),
    ak8jetToken_(consumes<pat::JetCollection>(edm::InputTag("slimmedJetsAK8"))),
    puppijetToken_(consumes<pat::JetCollection>(edm::InputTag("slimmedJetsPuppi"))),
    ak4genjetToken_(consumes<reco::GenJetCollection>(edm::InputTag("slimmedGenJets"))),
    ak8genjetToken_(consumes<reco::GenJetCollection>(edm::InputTag("slimmedGenJetsAK8"))),
    prunedGenToken_(consumes<edm::View<reco::GenParticle> >(edm::InputTag("prunedGenParticles"))),
    rhoToken_(consumes<double>(edm::InputTag("fixedGridRhoFastjetAll"))),
    vtxToken_(consumes<std::vector<reco::Vertex> >(edm::InputTag("offlineSlimmedPrimaryVertices"))),
    triggerResultsMETFilterToken_(consumes<edm::TriggerResults>(edm::InputTag("TriggerResults", "", "RECO"))),  //"PAT"
    triggerResultsHLTToken_(consumes<edm::TriggerResults>(edm::InputTag("TriggerResults", "", "HLT"))),
    jecPayloadsAK4chs_ (iConfig.getParameter<std::vector<std::string> >  ("jecPayloadsAK4chs")),
    jecPayloadsAK8chs_ (iConfig.getParameter<std::vector<std::string> >  ("jecPayloadsAK8chs")),
    jecPayloadsAK4pup_ (iConfig.getParameter<std::vector<std::string> >  ("jecPayloadsAK4pup")),
    jecPayloadsAK8pup_ (iConfig.getParameter<std::vector<std::string> >  ("jecPayloadsAK8pup")),
    jerSFtext_ (iConfig.getParameter<std::string>  ("jerSFtext"))
{
  usesResource("TFileService");
  edm::Service<TFileService> fs;

  h_ak8chs_softDropMass   =  fs->make<TH1D>("h_ak8chs_softDropMass"        ,"",200,0,400);
  h_ak8puppi_softDropMass =  fs->make<TH1D>("h_ak8puppi_softDropMass"      ,"",200,0,400);

  TreeAllHad = new TTree("TreeAllHad","TreeAllHad"); 
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
  TreeAllHad->Branch("Jet0MassSDsumSubjetCorrL23"           , & Jet0MassSDsumSubjetCorrL23        ,    "Jet0MassSDsumSubjetCorrL23/F"             );                                                    
  TreeAllHad->Branch("Jet0MassSDsumSubjetCorrL23Up"         , & Jet0MassSDsumSubjetCorrL23Up      ,    "Jet0MassSDsumSubjetCorrL23Up/F"           );                                                      
  TreeAllHad->Branch("Jet0MassSDsumSubjetCorrL23Dn"         , & Jet0MassSDsumSubjetCorrL23Dn      ,    "Jet0MassSDsumSubjetCorrL23Dn/F"           );                                                      
  TreeAllHad->Branch("Jet0MassSDsumSubjetCorrL123"         , & Jet0MassSDsumSubjetCorrL123      ,    "Jet0MassSDsumSubjetCorrL123/F"           );                                                      
  TreeAllHad->Branch("Jet0MassSDsumSubjetCorrL123Up"       , & Jet0MassSDsumSubjetCorrL123Up    ,    "Jet0MassSDsumSubjetCorrL123Up/F"         );                                                        
  TreeAllHad->Branch("Jet0MassSDsumSubjetCorrL123Dn"       , & Jet0MassSDsumSubjetCorrL123Dn    ,    "Jet0MassSDsumSubjetCorrL123Dn/F"         );                                                        
  TreeAllHad->Branch("Jet0MassSDsumSubjetCorrSmear"          , & Jet0MassSDsumSubjetCorrSmear       ,    "Jet0MassSDsumSubjetCorrSmear/F"            );                                                     
  TreeAllHad->Branch("Jet0MassSDsumSubjetCorrSmearUp"        , & Jet0MassSDsumSubjetCorrSmearUp     ,    "Jet0MassSDsumSubjetCorrSmearUp/F"          );                                                       
  TreeAllHad->Branch("Jet0MassSDsumSubjetCorrSmearDn"        , & Jet0MassSDsumSubjetCorrSmearDn     ,    "Jet0MassSDsumSubjetCorrSmearDn/F"          );                                                       
  TreeAllHad->Branch("Jet0MassPruned"                        , & Jet0MassPruned                     ,    "Jet0MassPruned/F"                          );                                       
  TreeAllHad->Branch("Jet0Tau1"                              , & Jet0Tau1                           ,    "Jet0Tau1/F"                                );                                 
  TreeAllHad->Branch("Jet0Tau2"                              , & Jet0Tau2                           ,    "Jet0Tau2/F"                                );                                 
  TreeAllHad->Branch("Jet0Tau3"                              , & Jet0Tau3                           ,    "Jet0Tau3/F"                                );                                 
  TreeAllHad->Branch("Jet0Tau32"                             , & Jet0Tau32                          ,    "Jet0Tau32/F"                               );                                  
  TreeAllHad->Branch("Jet0Tau21"                             , & Jet0Tau21                          ,    "Jet0Tau21/F"                               );                                  
  TreeAllHad->Branch("Jet0SDbdisc0"                          , & Jet0SDbdisc0                       ,    "Jet0SDbdisc0/F"                            );                                     
  TreeAllHad->Branch("Jet0SDbdisc1"                          , & Jet0SDbdisc1                       ,    "Jet0SDbdisc1/F"                            );                                     
  TreeAllHad->Branch("Jet0SDmaxbdisc"                        , & Jet0SDmaxbdisc                     ,    "Jet0SDmaxbdisc/F"                          );                                       
  TreeAllHad->Branch("Jet0SDmaxbdiscflavHadron"                    , & Jet0SDmaxbdiscflavHadron                 ,    "Jet0SDmaxbdiscflavHadron/F"                      );                                           
  TreeAllHad->Branch("Jet0SDmaxbdiscflavParton"                    , & Jet0SDmaxbdiscflavParton                 ,    "Jet0SDmaxbdiscflavParton/F"                      );                                           
  TreeAllHad->Branch("Jet0SDsubjet0pt"                       , & Jet0SDsubjet0pt                    ,    "Jet0SDsubjet0pt/F"                         );                                        
  TreeAllHad->Branch("Jet0SDsubjet0mass"                     , & Jet0SDsubjet0mass                  ,    "Jet0SDsubjet0mass/F"                       );                                          
  TreeAllHad->Branch("Jet0SDsubjet0area"                     , & Jet0SDsubjet0area                  ,    "Jet0SDsubjet0area/F"                       );                                          
  TreeAllHad->Branch("Jet0SDsubjet0flavHadron"                     , & Jet0SDsubjet0flavHadron                  ,    "Jet0SDsubjet0flavHadron/F"                       );                                          
  TreeAllHad->Branch("Jet0SDsubjet0flavParton"                     , & Jet0SDsubjet0flavParton                  ,    "Jet0SDsubjet0flavParton/F"                       );                                          
  TreeAllHad->Branch("Jet0SDsubjet1pt"                       , & Jet0SDsubjet1pt                    ,    "Jet0SDsubjet1pt/F"                         );                                        
  TreeAllHad->Branch("Jet0SDsubjet1mass"                     , & Jet0SDsubjet1mass                  ,    "Jet0SDsubjet1mass/F"                       );                                          
  TreeAllHad->Branch("Jet0SDsubjet1area"                     , & Jet0SDsubjet1area                  ,    "Jet0SDsubjet1area/F"                       );                                          
  TreeAllHad->Branch("Jet0SDsubjet1flavHadron"                     , & Jet0SDsubjet1flavHadron                  ,    "Jet0SDsubjet1flavHadron/F"                       );                                          
  TreeAllHad->Branch("Jet0SDsubjet1flavParton"                     , & Jet0SDsubjet1flavParton                  ,    "Jet0SDsubjet1flavParton/F"                       );                                          
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
  TreeAllHad->Branch("Jet0PuppiSDbdisc0"                     , & Jet0PuppiSDbdisc0                  ,    "Jet0PuppiSDbdisc0/F"                       );                                          
  TreeAllHad->Branch("Jet0PuppiSDbdisc1"                     , & Jet0PuppiSDbdisc1                  ,    "Jet0PuppiSDbdisc1/F"                       );                                          
  TreeAllHad->Branch("Jet0PuppiSDmaxbdisc"                   , & Jet0PuppiSDmaxbdisc                ,    "Jet0PuppiSDmaxbdisc/F"                     );                                            
  TreeAllHad->Branch("Jet0PuppiSDmaxbdiscflavHadron"               , & Jet0PuppiSDmaxbdiscflavHadron            ,    "Jet0PuppiSDmaxbdiscflavHadron/F"                 );                                                
  TreeAllHad->Branch("Jet0PuppiSDmaxbdiscflavParton"               , & Jet0PuppiSDmaxbdiscflavParton            ,    "Jet0PuppiSDmaxbdiscflavParton/F"                 );                                                
  TreeAllHad->Branch("Jet0PuppiSDsubjet0pt"                  , & Jet0PuppiSDsubjet0pt               ,    "Jet0PuppiSDsubjet0pt/F"                    );                                             
  TreeAllHad->Branch("Jet0PuppiSDsubjet0mass"                , & Jet0PuppiSDsubjet0mass             ,    "Jet0PuppiSDsubjet0mass/F"                  );                                               
  TreeAllHad->Branch("Jet0PuppiSDsubjet0area"                , & Jet0PuppiSDsubjet0area             ,    "Jet0PuppiSDsubjet0area/F"                  );                                               
  TreeAllHad->Branch("Jet0PuppiSDsubjet0flavHadron"                , & Jet0PuppiSDsubjet0flavHadron             ,    "Jet0PuppiSDsubjet0flavHadron/F"                  );                                               
  TreeAllHad->Branch("Jet0PuppiSDsubjet0flavParton"                , & Jet0PuppiSDsubjet0flavParton             ,    "Jet0PuppiSDsubjet0flavParton/F"                  );                                               
  TreeAllHad->Branch("Jet0PuppiSDsubjet1pt"                  , & Jet0PuppiSDsubjet1pt               ,    "Jet0PuppiSDsubjet1pt/F"                    );                                             
  TreeAllHad->Branch("Jet0PuppiSDsubjet1mass"                , & Jet0PuppiSDsubjet1mass             ,    "Jet0PuppiSDsubjet1mass/F"                  );                                               
  TreeAllHad->Branch("Jet0PuppiSDsubjet1area"                , & Jet0PuppiSDsubjet1area             ,    "Jet0PuppiSDsubjet1area/F"                  );                                               
  TreeAllHad->Branch("Jet0PuppiSDsubjet1flavHadron"                , & Jet0PuppiSDsubjet1flavHadron             ,    "Jet0PuppiSDsubjet1flavHadron/F"                  );                                               
  TreeAllHad->Branch("Jet0PuppiSDsubjet1flavParton"                , & Jet0PuppiSDsubjet1flavParton             ,    "Jet0PuppiSDsubjet1flavParton/F"                  );                                               
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
  TreeAllHad->Branch("Jet1MassSDsumSubjetCorrL23"           , & Jet1MassSDsumSubjetCorrL23        ,    "Jet1MassSDsumSubjetCorrL23/F"             );                                                    
  TreeAllHad->Branch("Jet1MassSDsumSubjetCorrL23Up"         , & Jet1MassSDsumSubjetCorrL23Up      ,    "Jet1MassSDsumSubjetCorrL23Up/F"           );                                                      
  TreeAllHad->Branch("Jet1MassSDsumSubjetCorrL23Dn"         , & Jet1MassSDsumSubjetCorrL23Dn      ,    "Jet1MassSDsumSubjetCorrL23Dn/F"           );                                                      
  TreeAllHad->Branch("Jet1MassSDsumSubjetCorrL123"         , & Jet1MassSDsumSubjetCorrL123      ,    "Jet1MassSDsumSubjetCorrL123/F"           );                                                      
  TreeAllHad->Branch("Jet1MassSDsumSubjetCorrL123Up"       , & Jet1MassSDsumSubjetCorrL123Up    ,    "Jet1MassSDsumSubjetCorrL123Up/F"         );                                                        
  TreeAllHad->Branch("Jet1MassSDsumSubjetCorrL123Dn"       , & Jet1MassSDsumSubjetCorrL123Dn    ,    "Jet1MassSDsumSubjetCorrL123Dn/F"         );                                                        
  TreeAllHad->Branch("Jet1MassSDsumSubjetCorrSmear"          , & Jet1MassSDsumSubjetCorrSmear       ,    "Jet1MassSDsumSubjetCorrSmear/F"            );                                                     
  TreeAllHad->Branch("Jet1MassSDsumSubjetCorrSmearUp"        , & Jet1MassSDsumSubjetCorrSmearUp     ,    "Jet1MassSDsumSubjetCorrSmearUp/F"          );                                                       
  TreeAllHad->Branch("Jet1MassSDsumSubjetCorrSmearDn"        , & Jet1MassSDsumSubjetCorrSmearDn     ,    "Jet1MassSDsumSubjetCorrSmearDn/F"          );                                                       
  TreeAllHad->Branch("Jet1MassPruned"                        , & Jet1MassPruned                     ,    "Jet1MassPruned/F"                          );                                       
  TreeAllHad->Branch("Jet1Tau1"                              , & Jet1Tau1                           ,    "Jet1Tau1/F"                                );                                 
  TreeAllHad->Branch("Jet1Tau2"                              , & Jet1Tau2                           ,    "Jet1Tau2/F"                                );                                 
  TreeAllHad->Branch("Jet1Tau3"                              , & Jet1Tau3                           ,    "Jet1Tau3/F"                                );                                 
  TreeAllHad->Branch("Jet1Tau32"                             , & Jet1Tau32                          ,    "Jet1Tau32/F"                               );                                  
  TreeAllHad->Branch("Jet1Tau21"                             , & Jet1Tau21                          ,    "Jet1Tau21/F"                               );                                  
  TreeAllHad->Branch("Jet1SDbdisc0"                          , & Jet1SDbdisc0                       ,    "Jet1SDbdisc0/F"                            );                                     
  TreeAllHad->Branch("Jet1SDbdisc1"                          , & Jet1SDbdisc1                       ,    "Jet1SDbdisc1/F"                            );                                     
  TreeAllHad->Branch("Jet1SDmaxbdisc"                        , & Jet1SDmaxbdisc                     ,    "Jet1SDmaxbdisc/F"                          );                                       
  TreeAllHad->Branch("Jet1SDmaxbdiscflavHadron"                    , & Jet1SDmaxbdiscflavHadron                 ,    "Jet1SDmaxbdiscflavHadron/F"                      );                                           
  TreeAllHad->Branch("Jet1SDmaxbdiscflavParton"                    , & Jet1SDmaxbdiscflavParton                 ,    "Jet1SDmaxbdiscflavParton/F"                      );                                           
  TreeAllHad->Branch("Jet1SDsubjet0pt"                       , & Jet1SDsubjet0pt                    ,    "Jet1SDsubjet0pt/F"                         );                                        
  TreeAllHad->Branch("Jet1SDsubjet0mass"                     , & Jet1SDsubjet0mass                  ,    "Jet1SDsubjet0mass/F"                       );                                          
  TreeAllHad->Branch("Jet1SDsubjet0area"                     , & Jet1SDsubjet0area                  ,    "Jet1SDsubjet0area/F"                       );                                          
  TreeAllHad->Branch("Jet1SDsubjet0flavHadron"                     , & Jet1SDsubjet0flavHadron                  ,    "Jet1SDsubjet0flavHadron/F"                       );                                          
  TreeAllHad->Branch("Jet1SDsubjet0flavParton"                     , & Jet1SDsubjet0flavParton                  ,    "Jet1SDsubjet0flavParton/F"                       );                                          
  TreeAllHad->Branch("Jet1SDsubjet1pt"                       , & Jet1SDsubjet1pt                    ,    "Jet1SDsubjet1pt/F"                         );                                        
  TreeAllHad->Branch("Jet1SDsubjet1mass"                     , & Jet1SDsubjet1mass                  ,    "Jet1SDsubjet1mass/F"                       );                                          
  TreeAllHad->Branch("Jet1SDsubjet1area"                     , & Jet1SDsubjet1area                  ,    "Jet1SDsubjet1area/F"                       );                                          
  TreeAllHad->Branch("Jet1SDsubjet1flavHadron"                     , & Jet1SDsubjet1flavHadron                  ,    "Jet1SDsubjet1flavHadron/F"                       );                                          
  TreeAllHad->Branch("Jet1SDsubjet1flavParton"                     , & Jet1SDsubjet1flavParton                  ,    "Jet1SDsubjet1flavParton/F"                       );                                          
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
  TreeAllHad->Branch("Jet1PuppiSDbdisc0"                     , & Jet1PuppiSDbdisc0                  ,    "Jet1PuppiSDbdisc0/F"                       );                                          
  TreeAllHad->Branch("Jet1PuppiSDbdisc1"                     , & Jet1PuppiSDbdisc1                  ,    "Jet1PuppiSDbdisc1/F"                       );                                          
  TreeAllHad->Branch("Jet1PuppiSDmaxbdisc"                   , & Jet1PuppiSDmaxbdisc                ,    "Jet1PuppiSDmaxbdisc/F"                     );                                            
  TreeAllHad->Branch("Jet1PuppiSDmaxbdiscflavHadron"               , & Jet1PuppiSDmaxbdiscflavHadron            ,    "Jet1PuppiSDmaxbdiscflavHadron/F"                 );                                                
  TreeAllHad->Branch("Jet1PuppiSDmaxbdiscflavParton"               , & Jet1PuppiSDmaxbdiscflavParton            ,    "Jet1PuppiSDmaxbdiscflavParton/F"                 );                                                
  TreeAllHad->Branch("Jet1PuppiSDsubjet0pt"                  , & Jet1PuppiSDsubjet0pt               ,    "Jet1PuppiSDsubjet0pt/F"                    );                                             
  TreeAllHad->Branch("Jet1PuppiSDsubjet0mass"                , & Jet1PuppiSDsubjet0mass             ,    "Jet1PuppiSDsubjet0mass/F"                  );                                               
  TreeAllHad->Branch("Jet1PuppiSDsubjet0area"                , & Jet1PuppiSDsubjet0area             ,    "Jet1PuppiSDsubjet0area/F"                  );                                               
  TreeAllHad->Branch("Jet1PuppiSDsubjet0flavHadron"                , & Jet1PuppiSDsubjet0flavHadron             ,    "Jet1PuppiSDsubjet0flavHadron/F"                  );                                               
  TreeAllHad->Branch("Jet1PuppiSDsubjet0flavParton"                , & Jet1PuppiSDsubjet0flavParton             ,    "Jet1PuppiSDsubjet0flavParton/F"                  );                                               
  TreeAllHad->Branch("Jet1PuppiSDsubjet1pt"                  , & Jet1PuppiSDsubjet1pt               ,    "Jet1PuppiSDsubjet1pt/F"                    );                                             
  TreeAllHad->Branch("Jet1PuppiSDsubjet1mass"                , & Jet1PuppiSDsubjet1mass             ,    "Jet1PuppiSDsubjet1mass/F"                  );                                               
  TreeAllHad->Branch("Jet1PuppiSDsubjet1area"                , & Jet1PuppiSDsubjet1area             ,    "Jet1PuppiSDsubjet1area/F"                  );                                               
  TreeAllHad->Branch("Jet1PuppiSDsubjet1flavHadron"                , & Jet1PuppiSDsubjet1flavHadron             ,    "Jet1PuppiSDsubjet1flavHadron/F"                  );                                               
  TreeAllHad->Branch("Jet1PuppiSDsubjet1flavParton"                , & Jet1PuppiSDsubjet1flavParton             ,    "Jet1PuppiSDsubjet1flavParton/F"                  );                                               
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
                                              
  TreeAllHad->Branch("AllHadMETpx"                           , & AllHadMETpx                        ,    "AllHadMETpx/F"                             );                                    
  TreeAllHad->Branch("AllHadMETpy"                           , & AllHadMETpy                        ,    "AllHadMETpy/F"                             );                                    
  TreeAllHad->Branch("AllHadMETpt"                           , & AllHadMETpt                        ,    "AllHadMETpt/F"                             );                                    
  TreeAllHad->Branch("AllHadMETphi"                          , & AllHadMETphi                       ,    "AllHadMETphi/F"                            );                                     
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

  bool verbose = false;

  //------------------------------------
  // MET Noise Filters 
  //------------------------------------

  if ( iEvent.isRealData() ) {
    edm::Handle < edm::TriggerResults > metFilters;
    iEvent.getByToken(triggerResultsMETFilterToken_, metFilters);
    edm::TriggerNames const& filterTriggerNames = iEvent.triggerNames(*metFilters);
    // const edm::TriggerNames &names = iEvent.triggerNames(*metFilters);

    int nMETfilters = metFilters->size();
    cout<<"nMETfilters "<<nMETfilters<<endl;

    vector <string> filterFlags;
    filterFlags.push_back("Flag_HBHENoiseFilter");
    filterFlags.push_back("Flag_HBHENoiseIsoFilter");
    filterFlags.push_back("Flag_CSCTightHalo2015Filter");
    filterFlags.push_back("Flag_EcalDeadCellTriggerPrimitiveFilter");
    filterFlags.push_back("Flag_goodVertices");
    filterFlags.push_back("Flag_eeBadScFilter");

   
   for (int itrig = 0; itrig != nMETfilters; ++itrig){
     std::string trigName = filterTriggerNames.triggerName(itrig);
      bool accept = metFilters->accept(itrig);
      cout<<trigName<<"  "<<accept<<endl;
       if ( std::find( filterFlags.begin(), filterFlags.end(), trigName ) != filterFlags.end() ) {
           cout<<"found "<<trigName<<endl;
       }
      }


    // bool event_pass_METfilter = false;

    // for ( unsigned int i = 0; i < metFilters->size(); ++i) {
    //   if ( std::find( filterFlags.begin(), filterFlags.end(), names.triggerName(i) ) != filterFlags.end() ) {

    //     bool passFilter = metFilters->accept( i );
    //      cout << "METfilter " << names.triggerName(i) << ". Pass? "<< passFilter << endl;

    //     event_pass_METfilter = event_pass_METfilter && passFilter;
    //     // metFilters->push_back( metFilters->accept( i ) );
    //   }
    // }
  }

  //------------------------------------
  // JECs 
  //------------------------------------

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
  
  //------------------------------------
  // JER 
  //------------------------------------

  // jet resolution scale factor from text files
  JME::JetResolutionScaleFactor jer_scaler;
  jer_scaler = JME::JetResolutionScaleFactor(jerSFtext_);

  //------------------------------------
  // Vertices 
  //------------------------------------ 
  edm::Handle<std::vector<reco::Vertex> > vertices;
  iEvent.getByToken(vtxToken_, vertices);
  int nvtx = vertices->size();

  //------------------------------------
  // Rho 
  //------------------------------------   
  Handle<double> rhoH;
  iEvent.getByToken(rhoToken_, rhoH);
  double rho = *rhoH;

  //------------------------------------
  // AK8 jet loop 
  //------------------------------------   
  edm::Handle<pat::JetCollection> AK8MINI;
  iEvent.getByToken(ak8jetToken_, AK8MINI);

  edm::Handle<reco::GenJetCollection> AK8GENJET;  
  iEvent.getByToken(ak8genjetToken_, AK8GENJET);

  int count_AK8MINI = 0;
  TLorentzVector AK8jet0_P4corr;
  TLorentzVector AK8jet1_P4corr;
  TLorentzVector GenJetMatched0;
  TLorentzVector GenJetMatched1;
  for (const pat::Jet &ijet : *AK8MINI) {  
    if (count_AK8MINI>1) break;

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
    cout<<"uncorrected AK8 jet pt "<<uncorrJet.pt()<<" corrected jet pt "<<corrJet.pt()<<endl;
    
    if(count_AK8MINI==0) AK8jet0_P4corr.SetPtEtaPhiM( corrJet.pt(), corrJet.eta(), corrJet.phi(), corrJet.mass() );
    if(count_AK8MINI==1) AK8jet1_P4corr.SetPtEtaPhiM( corrJet.pt(), corrJet.eta(), corrJet.phi(), corrJet.mass() );

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
    double corr_factor_L23 = corr_factor_L2*corr_factor_L3;
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
    if ( count_AK8MINI==0 ) GenJetMatched0 = GenJetMatched;
    if ( count_AK8MINI==1 ) GenJetMatched1 = GenJetMatched;


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
      if (verbose) std::cout << "JER Scale factors (Nominal / Up / Down) : " << jer_sf << " / " << jer_sf_up << " / " << jer_sf_dn << std::endl;
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
    double mass         = corrJet.mass();
    double rapidity     = ijet.rapidity();
    double ndau         = ijet.numberOfDaughters();
    double prunedMass   = ijet.userFloat("ak8PFJetsCHSPrunedMass");
    double softDropMass = ijet.userFloat("ak8PFJetsCHSSoftDropMass");
    double tau1         = ijet.userFloat("NjettinessAK8:tau1");
    double tau2         = ijet.userFloat("NjettinessAK8:tau2");
    double tau3         = ijet.userFloat("NjettinessAK8:tau3");
    double tau21        = 99;
    double tau32        = 99;

    double puppi_pt           = ijet.userFloat("ak8PFJetsPuppiValueMap:pt");
    double puppi_mass         = ijet.userFloat("ak8PFJetsPuppiValueMap:mass");
    double puppi_eta          = ijet.userFloat("ak8PFJetsPuppiValueMap:eta");
    double puppi_phi          = ijet.userFloat("ak8PFJetsPuppiValueMap:phi");
    double puppi_tau1         = ijet.userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau1");
    double puppi_tau2         = ijet.userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau2");
    double puppi_tau3         = ijet.userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau3");
    double puppi_tau21        = 99;
    double puppi_tau32        = 99;

    double deltaRpup = deltaR(ijet.eta(), ijet.phi(), puppi_eta, puppi_phi );

    if (tau1!=0) tau21 = tau2/tau1;
    if (tau2!=0) tau32 = tau3/tau2;

    if (puppi_tau1!=0) puppi_tau21 = puppi_tau2/puppi_tau1;
    if (puppi_tau2!=0) puppi_tau32 = puppi_tau3/puppi_tau2;

    if (verbose) cout<<"\nJet with pT "<<pt<<" sdMass "<<softDropMass<<endl;

    //------------------------------------
    // SoftDrop subjets
    //------------------------------------
    TLorentzVector sub0_P4_uncorr     ;
    TLorentzVector sub0_P4_L123res  ;
    TLorentzVector sub0_P4_L23res    ;
    TLorentzVector sub1_P4_uncorr     ;
    TLorentzVector sub1_P4_L123res  ;
    TLorentzVector sub1_P4_L23res    ;

    TLorentzVector sub0_P4_corrUp_L123res  ;
    TLorentzVector sub0_P4_corrUp_L23res    ;
    TLorentzVector sub1_P4_corrUp_L123res  ;
    TLorentzVector sub1_P4_corrUp_L23res    ;

    TLorentzVector sub0_P4_corrDn_L123res  ;
    TLorentzVector sub0_P4_corrDn_L23res    ;
    TLorentzVector sub1_P4_corrDn_L123res  ;
    TLorentzVector sub1_P4_corrDn_L23res    ;

    double sub0_area  = 0;
    double sub0_flav_hadron  = 0;
    double sub0_flav_parton  = 0;
    double sub0_bdisc = 0;
    double sub1_area  = 0;
    double sub1_flav_hadron  = 0;
    double sub1_flav_parton  = 0;
    double sub1_bdisc = 0;
    double mostMassiveSDsubjetMass = 0;
    int count_SD =0;
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
      if (verbose) cout<<"subjet corr: L1 "<<subjet_corr_factor_L1<<" L23 "<<subjet_corr_factor_L23<<" L23res "<<subjet_corr_factor_L23res<<" L123res"<<subjet_corr_factor_L123res<<endl;
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
      subjet_corrDn_L123 = subjet_corr_factor_L123res_full - corrDn_temp2;

      double subjet_corrUp_L23   = 1.0;
      double subjet_corrUp_L123 = 1.0;
      JetCorrUncertAK4chs->setJetPhi(  corrSubjetL123res.phi()  );
      JetCorrUncertAK4chs->setJetEta(  corrSubjetL123res.eta()  );
      JetCorrUncertAK4chs->setJetPt(   corrSubjetL123res.pt()   );
      double corrUp_temp2 = JetCorrUncertAK4chs->getUncertainty(1);
      subjet_corrUp_L23   = subjet_corr_factor_L23res + corrUp_temp2;
      subjet_corrUp_L123 = subjet_corr_factor_L123res_full + corrUp_temp2;

      reco::Candidate::LorentzVector corrDnSubjetL123res = subjet_corrDn_L123 * uncorrSubjet;
      reco::Candidate::LorentzVector corrUpSubjetL123res = subjet_corrUp_L123 * uncorrSubjet;
      reco::Candidate::LorentzVector corrDnSubjetL23res   = subjet_corrDn_L23   * uncorrSubjet;
      reco::Candidate::LorentzVector corrUpSubjetL23res   = subjet_corrUp_L23   * uncorrSubjet;
   

      //------------------------------------
      // subjet values for Tree
      //------------------------------------
      if (count_SD==0){
        sub0_P4_uncorr            .SetPtEtaPhiM( subjetPt, subjetEta, subjetPhi, subjetMass);
        sub0_P4_L123res         .SetPtEtaPhiM( corrSubjetL123res.pt()  , corrSubjetL123res.eta()  , corrSubjetL123res.phi()  , corrSubjetL123res.mass()   );
        sub0_P4_L23res           .SetPtEtaPhiM( corrSubjetL23res.pt()    , corrSubjetL23res.eta()    , corrSubjetL23res.phi()    , corrSubjetL23res.mass()     );
        sub0_P4_corrUp_L123res  .SetPtEtaPhiM( corrUpSubjetL123res.pt(), corrUpSubjetL123res.eta(), corrUpSubjetL123res.phi(), corrUpSubjetL123res.mass() );
        sub0_P4_corrUp_L23res    .SetPtEtaPhiM( corrUpSubjetL23res.pt()  , corrUpSubjetL23res.eta()  , corrUpSubjetL23res.phi()  , corrUpSubjetL23res.mass()   );
        sub0_P4_corrDn_L123res  .SetPtEtaPhiM( corrDnSubjetL123res.pt(), corrDnSubjetL123res.eta(), corrDnSubjetL123res.phi(), corrUpSubjetL123res.mass() );
        sub0_P4_corrDn_L23res    .SetPtEtaPhiM( corrDnSubjetL23res.pt()  , corrDnSubjetL23res.eta()  , corrDnSubjetL23res.phi()  , corrSubjetL23res.mass()     );
        sub0_area   = it->jetArea() ;
        sub0_flav_parton   = it->partonFlavour();
        sub0_flav_hadron   = it->hadronFlavour();
        sub0_bdisc  = subjetBdisc;
      }
      if (count_SD==1) {
        sub1_P4_uncorr            .SetPtEtaPhiM( subjetPt, subjetEta, subjetPhi, subjetMass);
        sub1_P4_L123res         .SetPtEtaPhiM( corrSubjetL123res.pt()  , corrSubjetL123res.eta()  , corrSubjetL123res.phi()  , corrSubjetL123res.mass()   );
        sub1_P4_L23res           .SetPtEtaPhiM( corrSubjetL23res.pt()    , corrSubjetL23res.eta()    , corrSubjetL23res.phi()    , corrSubjetL23res.mass()     );
        sub1_P4_corrUp_L123res  .SetPtEtaPhiM( corrUpSubjetL123res.pt(), corrUpSubjetL123res.eta(), corrUpSubjetL123res.phi(), corrUpSubjetL123res.mass() );
        sub1_P4_corrUp_L23res    .SetPtEtaPhiM( corrUpSubjetL23res.pt()  , corrUpSubjetL23res.eta()  , corrUpSubjetL23res.phi()  , corrUpSubjetL23res.mass()   );
        sub1_P4_corrDn_L123res  .SetPtEtaPhiM( corrDnSubjetL123res.pt(), corrDnSubjetL123res.eta(), corrDnSubjetL123res.phi(), corrUpSubjetL123res.mass() );
        sub1_P4_corrDn_L23res    .SetPtEtaPhiM( corrDnSubjetL23res.pt()  , corrDnSubjetL23res.eta()  , corrDnSubjetL23res.phi()  , corrSubjetL23res.mass()     );
        sub1_area   = it->jetArea() ;
        sub1_flav_parton   = it->partonFlavour();
        sub1_flav_hadron   = it->hadronFlavour();
        sub1_bdisc  = subjetBdisc;
      }
      if (subjetMass > mostMassiveSDsubjetMass) mostMassiveSDsubjetMass = subjetMass;

      if (verbose) cout<<" SD Subjet pt "<<subjetPt<<" Eta "<<subjetEta<<" deltaRsubjetJet "<<deltaRsubjetJet<<" Mass "<<subjetMass<<" Bdisc "<<subjetBdisc<<endl;
      count_SD++;
    }

    TLorentzVector sumSDsubjets_P4_uncorr   ;
    TLorentzVector sumSDsubjets_P4_L123res;
    TLorentzVector sumSDsubjets_P4_L23res  ;
    TLorentzVector sumSDsubjets_P4_corrUp_L123res;
    TLorentzVector sumSDsubjets_P4_corrUp_L23res  ;
    TLorentzVector sumSDsubjets_P4_corrDn_L123res;
    TLorentzVector sumSDsubjets_P4_corrDn_L23res  ;
    if (count_SD>1){ 
      sumSDsubjets_P4_uncorr              = sub0_P4_uncorr              + sub1_P4_uncorr             ; 
      sumSDsubjets_P4_L123res           = sub0_P4_L123res           + sub1_P4_L123res          ; 
      sumSDsubjets_P4_L23res             = sub0_P4_L23res             + sub1_P4_L23res            ; 
      sumSDsubjets_P4_corrUp_L123res    = sub0_P4_corrUp_L123res    + sub1_P4_corrUp_L123res   ; 
      sumSDsubjets_P4_corrUp_L23res      = sub0_P4_corrUp_L23res      + sub1_P4_corrUp_L23res     ; 
      sumSDsubjets_P4_corrDn_L123res    = sub0_P4_corrDn_L123res    + sub1_P4_corrDn_L123res   ; 
      sumSDsubjets_P4_corrDn_L23res      = sub0_P4_corrDn_L23res      + sub1_P4_corrDn_L23res     ; 
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
    TLorentzVector pup0_P4_uncorr     ;
    TLorentzVector pup0_P4_L23res    ;
    TLorentzVector pup1_P4_uncorr     ;
    TLorentzVector pup1_P4_L23res    ;

    TLorentzVector pup0_P4_corrUp_L23res    ;
    TLorentzVector pup1_P4_corrUp_L23res    ;

    TLorentzVector pup0_P4_corrDn_L23res    ;
    TLorentzVector pup1_P4_corrDn_L23res    ;

    double pup0_area  = 0;
    double pup0_flav_hadron  = 0;
    double pup0_flav_parton  = 0;
    double pup0_bdisc = 0;
    double pup1_area  = 0;
    double pup1_flav_hadron  = 0;
    double pup1_flav_parton  = 0;
    double pup1_bdisc = 0;
    double mostMassiveSDPUPPIsubjetMass = 0;
    auto const & sdSubjetsPuppi = ijet.subjets("SoftDropPuppi");
    int count_pup=0;
    for ( auto const & it : sdSubjetsPuppi ) {
      double subjetPt       = it->correctedP4(0).pt();
      double subjetEta      = it->correctedP4(0).eta();
      double subjetPhi      = it->correctedP4(0).phi();
      double subjetMass     = it->correctedP4(0).mass();
      double subjetBdisc    = it->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"); 
      double deltaRsubjetJet = deltaR(ijet.eta(), ijet.phi(), subjetEta, subjetPhi);
      if (verbose) cout<<" SD Subjet pt "<<subjetPt<<" Eta "<<subjetEta<<" deltaRsubjetJet "<<deltaRsubjetJet<<" Mass "<<subjetMass<<" Bdisc "<<subjetBdisc<<endl; 
      
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
        pup0_P4_uncorr            .SetPtEtaPhiM( subjetPt, subjetEta, subjetPhi, subjetMass);
        pup0_P4_L23res           .SetPtEtaPhiM( corrSubjetL23res.pt()    , corrSubjetL23res.eta()    , corrSubjetL23res.phi()    , corrSubjetL23res.mass()     );
        pup0_P4_corrUp_L23res    .SetPtEtaPhiM( corrUpSubjetL23res.pt()  , corrUpSubjetL23res.eta()  , corrUpSubjetL23res.phi()  , corrUpSubjetL23res.mass()   );
        pup0_P4_corrDn_L23res    .SetPtEtaPhiM( corrDnSubjetL23res.pt()  , corrDnSubjetL23res.eta()  , corrDnSubjetL23res.phi()  , corrSubjetL23res.mass()     );
        pup0_area   = it->jetArea() ;
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
        pup1_flav_parton   = it->partonFlavour();
        pup1_flav_hadron   = it->hadronFlavour();
        pup1_bdisc  = subjetBdisc;
      }

      if (subjetMass > mostMassiveSDPUPPIsubjetMass) mostMassiveSDPUPPIsubjetMass = subjetMass;
      count_pup++;
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
    // Fill AllHadTree
    //------------------------------------ 

    if (count_AK8MINI==0){
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
      Jet0MassSDsumSubjetRaw                 = sumSDsubjets_P4_uncorr.M()               ;
      Jet0MassSDsumSubjetCorrL23            = sumSDsubjets_P4_L23res.M()              ;  
      Jet0MassSDsumSubjetCorrL23Up          = sumSDsubjets_P4_corrUp_L23res.M()       ;  
      Jet0MassSDsumSubjetCorrL23Dn          = sumSDsubjets_P4_corrDn_L23res.M()       ;
      Jet0MassSDsumSubjetCorrL123          = sumSDsubjets_P4_L123res.M()            ; 
      Jet0MassSDsumSubjetCorrL123Up        = sumSDsubjets_P4_corrUp_L123res.M()     ;  
      Jet0MassSDsumSubjetCorrL123Dn        = sumSDsubjets_P4_corrDn_L123res.M()     ; 
      Jet0MassSDsumSubjetCorrSmear           = 1 ; // need to get some gen subjets 
      Jet0MassSDsumSubjetCorrSmearUp         = 1 ; // need to get some gen subjets 
      Jet0MassSDsumSubjetCorrSmearDn         = 1 ; // need to get some gen subjets 
      Jet0MassPruned                         = prunedMass ;     
      Jet0Tau1                               = tau1 ;  
      Jet0Tau2                               = tau2 ;  
      Jet0Tau3                               = tau3 ;  
      Jet0Tau32                              = tau32 ;  
      Jet0Tau21                              = tau21 ;  
      Jet0SDbdisc0                           = sub0_bdisc ;  
      Jet0SDbdisc1                           = sub1_bdisc ;   
      Jet0SDmaxbdisc                         = maxbdisc;
      Jet0SDmaxbdiscflavHadron                     = maxbdiscflav_hadron;  
      Jet0SDmaxbdiscflavParton                     = maxbdiscflav_parton;  
      Jet0SDsubjet0pt                        = sub0_P4_uncorr.Pt() ;               
      Jet0SDsubjet0mass                      = sub0_P4_uncorr.M()  ;  
      Jet0SDsubjet0area                      = sub0_area ;  
      Jet0SDsubjet0flavHadron                      = sub0_flav_hadron ;  
      Jet0SDsubjet0flavParton                      = sub0_flav_parton ;  
      Jet0SDsubjet1pt                        = sub1_P4_uncorr.Pt() ;                    
      Jet0SDsubjet1mass                      = sub1_P4_uncorr.M()  ;                    
      Jet0SDsubjet1area                      = sub1_area ;                    
      Jet0SDsubjet1flavHadron                      = sub1_flav_hadron ;     
      Jet0SDsubjet1flavParton                      = sub1_flav_parton ;     
 
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
      Jet0PuppiSDbdisc0                      = pup0_bdisc       ;
      Jet0PuppiSDbdisc1                      = pup1_bdisc       ;
      Jet0PuppiSDmaxbdisc                    = pup_maxbdisc     ;
      Jet0PuppiSDmaxbdiscflavHadron                = pup_maxbdiscflav_hadron ;
      Jet0PuppiSDmaxbdiscflavParton                = pup_maxbdiscflav_parton ;
      Jet0PuppiSDsubjet0pt                   = pup0_P4_uncorr.Pt()        ;
      Jet0PuppiSDsubjet0mass                 = pup0_P4_uncorr.M()         ;
      Jet0PuppiSDsubjet0area                 = pup0_area        ;
      Jet0PuppiSDsubjet0flavHadron                 = pup0_flav_hadron        ;
      Jet0PuppiSDsubjet0flavParton                 = pup0_flav_parton        ;
      Jet0PuppiSDsubjet1pt                   = pup1_P4_uncorr.Pt()        ;                 
      Jet0PuppiSDsubjet1mass                 = pup1_P4_uncorr.M()         ;              
      Jet0PuppiSDsubjet1area                 = pup1_area        ;              
      Jet0PuppiSDsubjet1flavHadron                 = pup1_flav_hadron        ;   
      Jet0PuppiSDsubjet1flavParton                 = pup1_flav_parton        ;   

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
    }   
    if (count_AK8MINI==1){
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
      Jet1MassSoftDrop                       = softDropMass;               
      Jet1MassSDsumSubjetRaw                 = sumSDsubjets_P4_uncorr.M()               ;
      Jet1MassSDsumSubjetCorrL23            = sumSDsubjets_P4_L23res.M()              ;  
      Jet1MassSDsumSubjetCorrL23Up          = sumSDsubjets_P4_corrUp_L23res.M()       ;  
      Jet1MassSDsumSubjetCorrL23Dn          = sumSDsubjets_P4_corrDn_L23res.M()       ;
      Jet1MassSDsumSubjetCorrL123          = sumSDsubjets_P4_L123res.M()            ; 
      Jet1MassSDsumSubjetCorrL123Up        = sumSDsubjets_P4_corrUp_L123res.M()     ;  
      Jet1MassSDsumSubjetCorrL123Dn        = sumSDsubjets_P4_corrDn_L123res.M()     ; 
      Jet1MassSDsumSubjetCorrSmear           = 1 ; // need to get some gen subjets 
      Jet1MassSDsumSubjetCorrSmearUp         = 1 ; // need to get some gen subjets 
      Jet1MassSDsumSubjetCorrSmearDn         = 1 ; // need to get some gen subjets 
      Jet1MassPruned                         = prunedMass ;     
      Jet1Tau1                               = tau1 ;  
      Jet1Tau2                               = tau2 ;  
      Jet1Tau3                               = tau3 ;  
      Jet1Tau32                              = tau32 ;  
      Jet1Tau21                              = tau21 ;  
      Jet1SDbdisc0                           = sub0_bdisc ;  
      Jet1SDbdisc1                           = sub1_bdisc ;   
      Jet1SDmaxbdisc                         = maxbdisc;
      Jet1SDmaxbdiscflavHadron                     = maxbdiscflav_hadron;  
      Jet1SDmaxbdiscflavParton                     = maxbdiscflav_parton;  
      Jet1SDsubjet0pt                        = sub0_P4_uncorr.Pt() ;               
      Jet1SDsubjet0mass                      = sub0_P4_uncorr.M()  ;  
      Jet1SDsubjet0area                      = sub0_area ;  
      Jet1SDsubjet0flavHadron                      = sub0_flav_hadron ;  
      Jet1SDsubjet0flavParton                      = sub0_flav_parton ;  
      Jet1SDsubjet1pt                        = sub1_P4_uncorr.Pt() ;                    
      Jet1SDsubjet1mass                      = sub1_P4_uncorr.M()  ;                    
      Jet1SDsubjet1area                      = sub1_area ;                    
      Jet1SDsubjet1flavHadron                      = sub1_flav_hadron ;     
      Jet1SDsubjet1flavParton                      = sub1_flav_parton ;     
 
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
      Jet1PuppiSDbdisc0                      = pup0_bdisc       ;
      Jet1PuppiSDbdisc1                      = pup1_bdisc       ;
      Jet1PuppiSDmaxbdisc                    = pup_maxbdisc     ;
      Jet1PuppiSDmaxbdiscflavHadron                = pup_maxbdiscflav_hadron ;
      Jet1PuppiSDmaxbdiscflavParton                = pup_maxbdiscflav_parton ;
      Jet1PuppiSDsubjet0pt                   = pup0_P4_uncorr.Pt()        ;
      Jet1PuppiSDsubjet0mass                 = pup0_P4_uncorr.M()         ;
      Jet1PuppiSDsubjet0area                 = pup0_area        ;
      Jet1PuppiSDsubjet0flavHadron                 = pup0_flav_hadron        ;
      Jet1PuppiSDsubjet0flavParton                 = pup0_flav_parton        ;
      Jet1PuppiSDsubjet1pt                   = pup1_P4_uncorr.Pt()        ;                 
      Jet1PuppiSDsubjet1mass                 = pup1_P4_uncorr.M()         ;              
      Jet1PuppiSDsubjet1area                 = pup1_area        ;              
      Jet1PuppiSDsubjet1flavHadron                 = pup1_flav_hadron        ;   
      Jet1PuppiSDsubjet1flavParton                 = pup1_flav_parton        ;   

      Jet1CHF                                = ijet.chargedHadronEnergy() / uncorrJet.E()  ;                        
      Jet1NHF                                = ijet.neutralHadronEnergy() / uncorrJet.E()  ;                         
      Jet1CM                                 = ijet.chargedMultiplicity()  ;                         
      Jet1NM                                 = ijet.neutralMultiplicity()  ;                          
      Jet1NEF                                = ijet.neutralEmEnergy() / uncorrJet.E()  ;                            
      Jet1CEF                                = ijet.chargedEmEnergy() / uncorrJet.E()  ;                          
      Jet1MF                                 = ijet.muonEnergy() / uncorrJet.E()  ;                         
      Jet1Mult                               = ijet.numberOfDaughters() ;   

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
    } 

  }
  AllHadMETpx          = 1;                   
  AllHadMETpy          = 1;                   
  AllHadMETpt          = 1;                   
  AllHadMETphi         = 1;                   
  AllHadNvtx           = nvtx;               
  AllHadRho            = rho ;               
  AllHadEventWeight    = 1 ;              
  DijetMass            = (AK8jet0_P4corr + AK8jet1_P4corr).M() ;                                                   
  DijetDeltaR          = deltaR( AK8jet0_P4corr.Eta(), AK8jet0_P4corr.Phi(), AK8jet1_P4corr.Eta(), AK8jet1_P4corr.Phi() );               
  DijetDeltaPhi        = deltaPhi( AK8jet0_P4corr.Phi(),  AK8jet1_P4corr.Phi() );                 
  DijetDeltaRap        = fabs(AK8jet0_P4corr.Rapidity() -  AK8jet1_P4corr.Rapidity() );

  DiGenJetMass         = (GenJetMatched0 + GenJetMatched1).M();                   
  GenTTmass            = 1 ;               
  HT                   = 1 ;                
  HT_CorrDn            = 1 ;                
  HT_CorrUp            = 1 ;                
  HT_PtSmearUp         = 1 ;                
  HT_PtSmearDn         = 1 ;                
  Q2weight_CorrDn      = 1 ;              
  Q2weight_CorrUp      = 1 ;              
  NNPDF3weight_CorrDn  = 1 ;              
  NNPDF3weight_CorrUp  = 1 ;              
  AllHadRunNum         = 1 ;              
  AllHadLumiBlock      = 1 ;              
  AllHadEventNum       = 1 ;              

  //------------------------------------
  // WRITE TREE WITH BASELINE PT CUT AND ETA CUT
  //------------------------------------

  if (AK8jet0_P4corr.Perp()>200 && AK8jet0_P4corr.Perp()> 200  && fabs( AK8jet0_P4corr.Eta() ) <2.4  && fabs( AK8jet1_P4corr.Eta() ) <2.4 ){
    TreeAllHad -> Fill();
  } 

  count_AK8MINI++;

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
