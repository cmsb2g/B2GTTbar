// -*- C++ -*-
//
// Package:    Analysis/ZprimeB2Ganalyzer
// Class:      ZprimeB2Ganalyzer
// 
/**\class ZprimeB2Ganalyzer ZprimeB2Ganalyzer.cc Analysis/ZprimeB2Ganalyzer/plugins/ZprimeB2Ganalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  christine mclean
//         Created:  Wed, 15 Apr 2015 15:12:05 GMT
//
//


// system include files
#include <memory>
#include <iostream>
#include <fstream>
#include <vector>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
//#include "DataFormats/JetReco/interface/CATopJetTagInfo.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"

#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"

#include <TTree.h>
#include <TSystem.h>
#include <TLorentzVector.h>
using namespace std;

//
// class declaration
//

class ZprimeB2Ganalyzer : public edm::EDAnalyzer {
   public:
      explicit ZprimeB2Ganalyzer(const edm::ParameterSet&);
      ~ZprimeB2Ganalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
  //edm::EDGetTokenT<edm::View<vector<float>> > jetAK8PtSrc_;
  //edm::EDGetTokenT<edm::View<vector<float>> > jetAK8GenPtSrc_;
  

  //TTree *tree_lept;
  //TTree *tree_semilept;
  TTree *tree_had;

  TFile* fPU;
  TH1F* hPU;

  std::map<std::string, float> hadTreeVars;
  //std::map<std::string, float> semileptTreeVars;
  std::vector<std::string> listOfHadVars;
  //std::vector<std::string> listOfSemileptVars;

  boost::shared_ptr<FactorizedJetCorrector> ak4JetCorrector;
  boost::shared_ptr<FactorizedJetCorrector> ak4JetCorrectorForMass;
  boost::shared_ptr<FactorizedJetCorrector> ak8JetCorrector;
  boost::shared_ptr<JetCorrectionUncertainty> UncertJetAK8;

  //options
  bool negativeWeights_;
  bool isMC_;
  bool isFlat_;
  bool applyFilters_;
  double JERshift_;
  double JECshift_;
  bool reweightTopPt_;
  string puFile_;

  //std::string testSrc_; 

  float getJER(float jetEta, int sysType){
    /*
    Here, jetEta should be the jet pseudorapidity, and sysType is :
    nominal : 0
    down    : -1
    up      : +1
    */

    float jerSF = 1.0;

    if ( !(sysType==0 || sysType==-1 || sysType==1)){
      cout<<"ERROR: Can't get JER! use type=0 (nom), -1 (down), +1 (up)"<<endl;
      return (jerSF);
    }

    //Values from https://twiki.cern.ch/twiki/bin/view/CMS/JetResolution
    float etamin[7]{0.0,0.8,1.3,1.9,2.5,3.0,3.2};
    float etamax[7]{0.8,1.3,1.9,2.5,3.0,3.2,5.0};
    float scale_nom[7]{1.061,1.088,1.106,1.126,1.343,1.303,1.320};
    float scale_uncert[7]{0.023,0.029,0.030,0.094,0.123,0.111,0.286};
  
    // old 8 TeV
    // etamin = [0.0,0.5,1.1,1.7,2.3,2.8,3.2]
    // etamax = [0.5,1.1,1.7,2.3,2.8,3.2,5.0]
    // scale_nom = [1.079,1.099,1.121,1.208,1.254,1.395,1.056]
    // scale_dn  = [1.053,1.071,1.092,1.162,1.192,1.332,0.865]
    // scale_up  = [1.105,1.127,1.150,1.254,1.316,1.458,1.247]

    for (int iSF = 0; iSF < 7; iSF++){
      if (abs(jetEta) >= etamin[iSF] && abs(jetEta) < etamax[iSF]){
	if (sysType < 0) jerSF = scale_nom[iSF] - scale_uncert[iSF];
	else if (sysType > 0) jerSF = scale_nom[iSF] + scale_uncert[iSF];
	else jerSF = scale_nom[iSF];
	break;
      }
    }
    return (jerSF);
  }
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
ZprimeB2Ganalyzer::ZprimeB2Ganalyzer(const edm::ParameterSet& iConfig):
  //testSrc_ (iConfig.getParameter<std::string> ("testSrc") )
  //jetAK8PtSrc_(consumes<edm::View<vector<float>> >(iConfig.getParameter<edm::InputTag>("jetAK8PtSrc"))),
  //jetAK8GenPtSrc_(consumes<edm::View<vector<float>> >(iConfig.getParameter<edm::InputTag>("jetAK8GenPtSrc")))

  negativeWeights_   (iConfig.getParameter<bool>("negativeWeights")),
  isMC_              (iConfig.getParameter<bool>("isMC")),
  isFlat_            (iConfig.getParameter<bool>("isFlat")),
  applyFilters_      (iConfig.getParameter<bool>("applyFilters")),
  JERshift_          (iConfig.getParameter<double>("JERshift")),
  JECshift_          (iConfig.getParameter<double>("JECshift")),
  reweightTopPt_     (iConfig.getParameter<bool>("reweightTopPt")),
  puFile_            (iConfig.getParameter<string>("puFile"))
{
   //now do what ever initialization is needed
  edm::Service<TFileService> fs;
  //tree_lept = fs->make<TTree>("tree_lept","tree_lept");//leptonic tree
  //tree_semilept = fs->make<TTree>("tree_semilept","tree_semilept");//semi-leptonic tree
  tree_had = fs->make<TTree>("tree_had","tree_had");//all hadronic tree

  //hadronic tree variables
  listOfHadVars.push_back("eventNumber");
  listOfHadVars.push_back("cscFilt");
  listOfHadVars.push_back("vertexFilt");
  listOfHadVars.push_back("hbheFilt");
  listOfHadVars.push_back("htTrig");
  listOfHadVars.push_back("jetTrig");

  listOfHadVars.push_back("ak8TrimjetTrig");
  listOfHadVars.push_back("ht650TrimjetTrig");
  listOfHadVars.push_back("ht700TrimjetTrig");

  listOfHadVars.push_back("L1cor");
  listOfHadVars.push_back("L2cor");
  listOfHadVars.push_back("L3cor");

  listOfHadVars.push_back("npv");
  listOfHadVars.push_back("evWeight");
  listOfHadVars.push_back("nAK8pt400eta2p4jets");
  //listOfHadVars.push_back("nTopTagJets");
  listOfHadVars.push_back("cutflow");
  listOfHadVars.push_back("topTagJet0_topTagFlag");
  listOfHadVars.push_back("topTagJet1_topTagFlag");

  listOfHadVars.push_back("topTagJet0_pt");
  listOfHadVars.push_back("topTagJet0_eta");
  listOfHadVars.push_back("topTagJet0_phi");
  listOfHadVars.push_back("topTagJet0_E");
  listOfHadVars.push_back("topTagJet0_Y");
  listOfHadVars.push_back("topTagJet0_minmass");
  listOfHadVars.push_back("topTagJet0_nSubJets");
  listOfHadVars.push_back("topTagJet0_tau1");
  listOfHadVars.push_back("topTagJet0_tau2");
  listOfHadVars.push_back("topTagJet0_tau3");
  listOfHadVars.push_back("topTagJet0_tau32");
  listOfHadVars.push_back("topTagJet0_ungroomedMass");
  listOfHadVars.push_back("topTagJet0_topMass");
  listOfHadVars.push_back("topTagJet0_filteredMass");
  listOfHadVars.push_back("topTagJet0_prunedMass");
  listOfHadVars.push_back("topTagJet0_trimmedMass");
  listOfHadVars.push_back("topTagJet0_softDropMass");
  listOfHadVars.push_back("topTagJet0_ungroomedMassRaw");
  listOfHadVars.push_back("topTagJet0_topMassRaw");
  listOfHadVars.push_back("topTagJet0_filteredMassRaw");
  listOfHadVars.push_back("topTagJet0_prunedMassRaw");
  listOfHadVars.push_back("topTagJet0_trimmedMassRaw");
  listOfHadVars.push_back("topTagJet0_softDropMassRaw");

  listOfHadVars.push_back("topTagJet0_JetCorr");
  listOfHadVars.push_back("topTagJet0_JetCorrUp");
  listOfHadVars.push_back("topTagJet0_JetCorrDn");
  listOfHadVars.push_back("topTagJet0_px");
  listOfHadVars.push_back("topTagJet0_py");
  listOfHadVars.push_back("topTagJet0_pz");
  listOfHadVars.push_back("topTagJet0_rhoRatio");
  listOfHadVars.push_back("topTagJet0_tau21");
  listOfHadVars.push_back("topTagJet0_NHF");
  listOfHadVars.push_back("topTagJet0_CHF");
  listOfHadVars.push_back("topTagJet0_NEF");
  listOfHadVars.push_back("topTagJet0_CEF");
  listOfHadVars.push_back("topTagJet0_NC");
  listOfHadVars.push_back("topTagJet0_NCH");

  listOfHadVars.push_back("topTagJet1_pt");
  listOfHadVars.push_back("topTagJet1_eta");
  listOfHadVars.push_back("topTagJet1_phi");
  listOfHadVars.push_back("topTagJet1_E");
  listOfHadVars.push_back("topTagJet1_Y");
  listOfHadVars.push_back("topTagJet1_minmass");
  listOfHadVars.push_back("topTagJet1_nSubJets");
  listOfHadVars.push_back("topTagJet1_tau1");
  listOfHadVars.push_back("topTagJet1_tau2");
  listOfHadVars.push_back("topTagJet1_tau3");
  listOfHadVars.push_back("topTagJet1_tau32");
  listOfHadVars.push_back("topTagJet1_ungroomedMass");
  listOfHadVars.push_back("topTagJet1_topMass");
  listOfHadVars.push_back("topTagJet1_filteredMass");
  listOfHadVars.push_back("topTagJet1_prunedMass");
  listOfHadVars.push_back("topTagJet1_trimmedMass");
  listOfHadVars.push_back("topTagJet1_softDropMass");
  listOfHadVars.push_back("topTagJet1_ungroomedMassRaw");
  listOfHadVars.push_back("topTagJet1_topMassRaw");
  listOfHadVars.push_back("topTagJet1_filteredMassRaw");
  listOfHadVars.push_back("topTagJet1_prunedMassRaw");
  listOfHadVars.push_back("topTagJet1_trimmedMassRaw");
  listOfHadVars.push_back("topTagJet1_softDropMassRaw");

  listOfHadVars.push_back("topTagJet1_JetCorr");
  listOfHadVars.push_back("topTagJet1_JetCorrUp");
  listOfHadVars.push_back("topTagJet1_JetCorrDn");
  listOfHadVars.push_back("topTagJet1_px");
  listOfHadVars.push_back("topTagJet1_py");
  listOfHadVars.push_back("topTagJet1_pz");
  listOfHadVars.push_back("topTagJet1_rhoRatio");
  listOfHadVars.push_back("topTagJet1_tau21");
  listOfHadVars.push_back("topTagJet1_NHF");
  listOfHadVars.push_back("topTagJet1_CHF");
  listOfHadVars.push_back("topTagJet1_NEF");
  listOfHadVars.push_back("topTagJet1_CEF");
  listOfHadVars.push_back("topTagJet1_NC");
  listOfHadVars.push_back("topTagJet1_NCH");

  listOfHadVars.push_back("topTagJet0_maxSoftDropSubjetbtag");
  listOfHadVars.push_back("topTagJet0_maxCMSTTSubjetbtag");

  listOfHadVars.push_back("topTagJet0_SoftDropSubjet0btag");
  listOfHadVars.push_back("topTagJet0_SoftDropSubjet0pt");
  listOfHadVars.push_back("topTagJet0_SoftDropSubjet0mass");
  listOfHadVars.push_back("topTagJet0_SoftDropSubjet1btag");
  listOfHadVars.push_back("topTagJet0_SoftDropSubjet1pt");
  listOfHadVars.push_back("topTagJet0_SoftDropSubjet1mass");

  listOfHadVars.push_back("topTagJet0_CMSnSubJets");
  listOfHadVars.push_back("topTagJet0_CMSm01");
  listOfHadVars.push_back("topTagJet0_CMSm02");
  listOfHadVars.push_back("topTagJet0_CMSm12");

  listOfHadVars.push_back("topTagJet1_maxSoftDropSubjetbtag");
  listOfHadVars.push_back("topTagJet1_maxCMSTTSubjetbtag");

  listOfHadVars.push_back("topTagJet1_SoftDropSubjet0btag");
  listOfHadVars.push_back("topTagJet1_SoftDropSubjet0pt");
  listOfHadVars.push_back("topTagJet1_SoftDropSubjet0mass");
  listOfHadVars.push_back("topTagJet1_SoftDropSubjet1btag");
  listOfHadVars.push_back("topTagJet1_SoftDropSubjet1pt");
  listOfHadVars.push_back("topTagJet1_SoftDropSubjet1mass");

  listOfHadVars.push_back("topTagJet1_CMSnSubJets");
  listOfHadVars.push_back("topTagJet1_CMSm01");
  listOfHadVars.push_back("topTagJet1_CMSm02");
  listOfHadVars.push_back("topTagJet1_CMSm12");
 
  //listOfHadVars.push_back("jet0AK8GenPt");
  //listOfHadVars.push_back("jet1AK8GenPt");

  //listOfHadVars.push_back("cmstt_Z_mass");
  //listOfHadVars.push_back("filtered_Z_mass");
  //listOfHadVars.push_back("pruned_Z_mass");
  //listOfHadVars.push_back("trimmed_Z_mass");
  listOfHadVars.push_back("softDrop_Z_mass");
  listOfHadVars.push_back("ungroomedDeltaPhi");
  listOfHadVars.push_back("ungroomedDeltaRapidity");

  listOfHadVars.push_back("leptSelectionPass");
  listOfHadVars.push_back("semileptSelectionPass");
  listOfHadVars.push_back("hadSelectionPass");

  //semileptonic variables
  /*listOfSemileptVars.push_back("SemiLeptTrig");
  listOfSemileptVars.push_back("SemiLeptWeight");    
  listOfSemileptVars.push_back("BoosttypE");
  listOfSemileptVars.push_back("FatJetCorr");
  listOfSemileptVars.push_back("FatJetCorrUp");
  listOfSemileptVars.push_back("FatJetCorrDn");
  listOfSemileptVars.push_back("FatJetPt");
  listOfSemileptVars.push_back("FatJetEta");
  listOfSemileptVars.push_back("FatJetPhi");
  listOfSemileptVars.push_back("FatJetRap");
  listOfSemileptVars.push_back("FatJetPx");
  listOfSemileptVars.push_back("FatJetPy");
  listOfSemileptVars.push_back("FatJetPz");
  listOfSemileptVars.push_back("FatJetEnergy");
  listOfSemileptVars.push_back("FatJetBDisc");
  listOfSemileptVars.push_back("FatJetRhoRatio");
  listOfSemileptVars.push_back("FatJetMass");
  listOfSemileptVars.push_back("FatJetMassSoftDrop");
  listOfSemileptVars.push_back("FatJetMassPruned");
  listOfSemileptVars.push_back("FatJetMassFiltered");
  listOfSemileptVars.push_back("FatJetMassTrimmed");
  listOfSemileptVars.push_back("FatJetTau1");
  listOfSemileptVars.push_back("FatJetTau2");
  listOfSemileptVars.push_back("FatJetTau3");
  listOfSemileptVars.push_back("FatJetTau32");
  listOfSemileptVars.push_back("FatJetTau21");
  listOfSemileptVars.push_back("FatJetSDnsubjets");
  listOfSemileptVars.push_back("FatJetSDbdiscW");
  listOfSemileptVars.push_back("FatJetSDbdiscB");
  listOfSemileptVars.push_back("FatJetSDmaxbdisc");
  listOfSemileptVars.push_back("FatJetSDsubjetWpt");
  listOfSemileptVars.push_back("FatJetSDsubjetWmass");
  listOfSemileptVars.push_back("FatJetSDsubjetWp4");
  listOfSemileptVars.push_back("FatJetSDsubjetBpt");
  listOfSemileptVars.push_back("FatJetSDsubjetBmass");
  listOfSemileptVars.push_back("FatJetSDsubjetBp4");
  listOfSemileptVars.push_back("FatJetCMSmaxbdisc");
  listOfSemileptVars.push_back("FatJetCMSnsubjets");
  listOfSemileptVars.push_back("FatJetCMSminMass");
  listOfSemileptVars.push_back("FatJetCMSm01");
  listOfSemileptVars.push_back("FatJetCMSm02");
  listOfSemileptVars.push_back("FatJetCMSm12");
  listOfSemileptVars.push_back("BJetbDisc");
  listOfSemileptVars.push_back("BJetPt");
  listOfSemileptVars.push_back("BJetEta");
  listOfSemileptVars.push_back("BJetPhi");
  listOfSemileptVars.push_back("BJetMass");
  listOfSemileptVars.push_back("LeptonType");
  listOfSemileptVars.push_back("LeptonPt");
  listOfSemileptVars.push_back("LeptonEta");
  listOfSemileptVars.push_back("LeptonPhi");
  listOfSemileptVars.push_back("LeptonPx");
  listOfSemileptVars.push_back("LeptonPy");
  listOfSemileptVars.push_back("LeptonPz");
  listOfSemileptVars.push_back("LeptonEnergy");
  listOfSemileptVars.push_back("LeptonIso");
  listOfSemileptVars.push_back("LeptonPtRel");
  listOfSemileptVars.push_back("LeptonDRMin");        
  listOfSemileptVars.push_back("SemiLepMETpx");
  listOfSemileptVars.push_back("SemiLepMETpy");
  listOfSemileptVars.push_back("SemiLepMETpt");
  listOfSemileptVars.push_back("SemiLepMETphi");
  listOfSemileptVars.push_back("SemiLepNvtx");
  listOfSemileptVars.push_back("SemiLepEventWeight");
  listOfSemileptVars.push_back("SemilLepTTmass");
  listOfSemileptVars.push_back("DeltaPhiLepFat");
  listOfSemileptVars.push_back("AK4bDisc");
  listOfSemileptVars.push_back("NearestAK4JetPt");
  listOfSemileptVars.push_back("NearestAK4JetEta");
  listOfSemileptVars.push_back("NearestAK4JetPhi");
  listOfSemileptVars.push_back("NearestAK4JetMass");

  listOfSemileptVars.push_back("isoMu24trig");
  listOfSemileptVars.push_back("mu45trig");
  listOfSemileptVars.push_back("mu50trig");
  listOfSemileptVars.push_back("mu40trig");
  listOfSemileptVars.push_back("ele32trig");
  listOfSemileptVars.push_back("ele45trig");
  listOfSemileptVars.push_back("ele105trig");
  listOfSemileptVars.push_back("ele115trig");

  listOfSemileptVars.push_back("leptSelectionPass");
  listOfSemileptVars.push_back("semileptSelectionPass");
  listOfSemileptVars.push_back("hadSelectionPass");
  */
  for (unsigned i = 0; i < listOfHadVars.size(); i++){
    hadTreeVars[ listOfHadVars[i] ] = -999.99;
    tree_had->Branch( (listOfHadVars[i]).c_str() , &(hadTreeVars[ listOfHadVars[i] ]), (listOfHadVars[i]+"/F").c_str() );
  }
  /*for (unsigned i = 0; i < listOfSemileptVars.size(); i++){
    semileptTreeVars[ listOfSemileptVars[i] ] = -999.99;
    tree_semilept->Branch( (listOfSemileptVars[i]).c_str() , &(semileptTreeVars[ listOfSemileptVars[i] ]), (listOfSemileptVars[i]+"/F").c_str() );
    }*/

  //JECs - for MC
  //AK4
  const string L3JetParAK4_ptr("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/JECs/Summer15_25nsV6_MC_L3Absolute_AK4PFchs.txt");
  JetCorrectorParameters L3JetParAK4(L3JetParAK4_ptr);
  const string L2JetParAK4_ptr("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/JECs/Summer15_25nsV6_MC_L2Relative_AK4PFchs.txt");
  JetCorrectorParameters L2JetParAK4(L2JetParAK4_ptr);
  const string L1JetParAK4_ptr("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/JECs/Summer15_25nsV6_MC_L1FastJet_AK4PFchs.txt");
  JetCorrectorParameters L1JetParAK4(L1JetParAK4_ptr);
  const string UncertJetAK4_ptr("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/JECs/Summer15_25nsV6_MC_Uncertainty_AK4PFchs.txt");
  JetCorrectionUncertainty UncertJetAK4(UncertJetAK4_ptr);
  
  //AK8
  const string L3JetParAK8_ptr("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/JECs/Summer15_25nsV6_MC_L3Absolute_AK8PFchs.txt");
  JetCorrectorParameters L3JetParAK8(L3JetParAK8_ptr);
  const string L2JetParAK8_ptr("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/JECs/Summer15_25nsV6_MC_L2Relative_AK8PFchs.txt");
  JetCorrectorParameters L2JetParAK8(L2JetParAK8_ptr);
  const string L1JetParAK8_ptr("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/JECs/Summer15_25nsV6_MC_L1FastJet_AK8PFchs.txt");
  JetCorrectorParameters L1JetParAK8(L1JetParAK8_ptr);
  const string UncertJetAK8_ptr("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/JECs/Summer15_25nsV6_MC_Uncertainty_AK8PFchs.txt");
  UncertJetAK8 = boost::shared_ptr<JetCorrectionUncertainty>( new JetCorrectionUncertainty(UncertJetAK8_ptr));
  
  //for data
  const string ResJetParAK4_ptr("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/JECs/Summer15_25nsV6_DATA_L2L3Residual_AK4PFchs.txt");
  JetCorrectorParameters ResJetParAK4(ResJetParAK4_ptr);
  const string ResJetParAK8_ptr("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/JECs/Summer15_25nsV6_DATA_L2L3Residual_AK8PFchs.txt");
  JetCorrectorParameters ResJetParAK8(ResJetParAK8_ptr);
  
  if (isMC_){
    //cout<<"Getting MC JECs!"<<endl;
  }
  else{
    //cout<<"Getting DATA JECs!"<<endl;
    //AK4
    const string L3JetParAK4_ptr("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/JECs/Summer15_25nsV6_DATA_L3Absolute_AK4PFchs.txt");
    JetCorrectorParameters L3JetParAK4(L3JetParAK4_ptr);
    const string L2JetParAK4_ptr("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/JECs/Summer15_25nsV6_DATA_L2Relative_AK4PFchs.txt");
    JetCorrectorParameters L2JetParAK4(L2JetParAK4_ptr);
    const string L1JetParAK4_ptr("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/JECs/Summer15_25nsV6_DATA_L1FastJet_AK4PFchs.txt");
    JetCorrectorParameters L1JetParAK4(L1JetParAK4_ptr);
    const string UncertJetAK4_ptr("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/JECs/Summer15_25nsV6_DATA_Uncertainty_AK4PFchs.txt");
    JetCorrectionUncertainty UncertJetAK4(UncertJetAK4_ptr);
    
    //AK8
    const string L3JetParAK8_ptr("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/JECs/Summer15_25nsV6_DATA_L3Absolute_AK8PFchs.txt");
    JetCorrectorParameters L3JetParAK8(L3JetParAK8_ptr);
    const string L2JetParAK8_ptr("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/JECs/Summer15_25nsV6_DATA_L2Relative_AK8PFchs.txt");
    JetCorrectorParameters L2JetParAK8(L2JetParAK8_ptr);
    const string L1JetParAK8_ptr("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/JECs/Summer15_25nsV6_DATA_L1FastJet_AK8PFchs.txt");
    JetCorrectorParameters L1JetParAK8(L1JetParAK8_ptr);
    const string UncertJetAK8_ptr("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/JECs/Summer15_25nsV6_DATA_Uncertainty_AK8PFchs.txt");
    JetCorrectionUncertainty UncertJetAK8(UncertJetAK8_ptr);
  }

  //Load the JetCorrectorParameter objects into a vector, IMPORTANT: THE ORDER MATTERS HERE !!!!
  vector<JetCorrectorParameters> vParJecAK4;
  vParJecAK4.push_back(L1JetParAK4);
  vParJecAK4.push_back(L2JetParAK4);
  vParJecAK4.push_back(L3JetParAK4);
  //for data
  if (!isMC_) vParJecAK4.push_back(ResJetParAK4);
   
  ak4JetCorrector = boost::shared_ptr<FactorizedJetCorrector> (new FactorizedJetCorrector(vParJecAK4));

  vector<JetCorrectorParameters> vParJecAK4ForMass;
  vParJecAK4ForMass.push_back(L2JetParAK4);
  vParJecAK4ForMass.push_back(L3JetParAK4);
  //for data
  if (!isMC_) vParJecAK4ForMass.push_back(ResJetParAK4);
  
  ak4JetCorrectorForMass = boost::shared_ptr<FactorizedJetCorrector> (new FactorizedJetCorrector(vParJecAK4ForMass));
  
  vector<JetCorrectorParameters> vParJecAK8;
  vParJecAK8.push_back(L1JetParAK8);
  vParJecAK8.push_back(L2JetParAK8);
  vParJecAK8.push_back(L3JetParAK8);
  //for data
  if (!isMC_) vParJecAK8.push_back(ResJetParAK8);
  
  ak8JetCorrector = boost::shared_ptr<FactorizedJetCorrector> (new FactorizedJetCorrector(vParJecAK8));

  //pileup reweighting
  fPU = new TFile(puFile_.c_str(), "READ");
  hPU = (TH1F *) fPU->Get("h_NPVert");
}


ZprimeB2Ganalyzer::~ZprimeB2Ganalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
ZprimeB2Ganalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;

   //cout <<"Hello!"<<endl;
   //cout<<testSrc_<<endl;

   //***HANDLES***

   //trigger and filter handles
   Handle<vector<string> > triggerNameStringsHandleF;
   Handle<vector<float> > triggerBitHandleF;
   Handle<vector<int> > triggerPrescaleHandleF;

   Handle<bool> HBHEfilterHandleF;

   Handle<vector<string> > triggerNameStringsHandle;
   Handle<vector<float> > triggerBitHandle;
   Handle<vector<int> > triggerPrescaleHandle;

   //event info
   Handle<ULong64_t> h_eventNumber;

   Handle<int> h_npv;
   Handle<int> h_puNtrueInt;
      
   Handle<vector<float> > h_pv_chi;
   Handle<vector<float> > h_pv_rho;
   Handle<vector<float> > h_pv_z;
   Handle<vector<int> > h_pv_ndof;

   //generator info
   Handle<GenEventInfoProduct> h_genEventInfo;
   //Handle<LHERunInfoProduct> h_lheRunInfo; 

   //gen parton handles
   Handle<vector<float> > h_genPartPt;
   Handle<vector<float> > h_genPartEta;
   Handle<vector<float> > h_genPartPhi;
   Handle<vector<float> > h_genPartMass;
   Handle<vector<float> > h_genPartID;
   Handle<vector<float> > h_genPartStatus;
   Handle<vector<float> > h_genPartMomID;

   //muon handles
   Handle<vector<float> > h_muPt;
   Handle<vector<float> > h_muEta;
   Handle<vector<float> > h_muPhi;
   Handle<vector<float> > h_muTight;
   Handle<vector<float> > h_muLoose;
   Handle<vector<float> > h_muMass;
   Handle<vector<float> > h_muDz;
   Handle<vector<float> > h_muCharge;
   Handle<vector<float> > h_muIso04;

   Handle<vector<vector<int> > > h_muKey;

   //electron handles
   Handle<vector<float> > h_elPt;
   Handle<vector<float> > h_elEta;
   Handle<vector<float> > h_elPhi;
   Handle<vector<float> > h_elTight;
   Handle<vector<float> > h_elLoose;
   Handle<vector<float> > h_eldEtaIn;
   Handle<vector<float> > h_eldPhiIn;
   Handle<vector<float> > h_elHoE;
   Handle<vector<float> > h_elfull5x5siee;
   Handle<vector<float> > h_elE;
   Handle<vector<float> > h_elD0;
   Handle<vector<float> > h_elDz;
   Handle<vector<float> > h_elIso03;
   Handle<vector<float> > h_elisVeto;
   Handle<vector<float> > h_elhasMatchedConVeto;
   Handle<vector<float> > h_elooEmooP;
   Handle<vector<float> > h_elMass;
   Handle<vector<float> > h_elscEta;
   Handle<vector<float> > h_elCharge;

   Handle<vector<vector<int> > > h_elKey;

   //AK4 jet handles   
   Handle<vector<float> > h_jetsAK4E;
   Handle<vector<float> > h_jetsAK4Pt;
   Handle<vector<float> > h_jetsAK4Eta;
   Handle<vector<float> > h_jetsAK4Phi;
   Handle<vector<float> > h_jetsAK4ungroomedMass;
   Handle<vector<float> > h_jetsAK4JEC;
   Handle<vector<float> > h_jetsAK4CSV;
   Handle<vector<float> > h_jetsAK4NumDaughters;
   Handle<vector<float> > h_jetsAK4Area;

   Handle<vector<vector<int> > > h_jetsAK4Keys;

   Handle<vector<float> > h_jetsAK4nHadEnergy;
   Handle<vector<float> > h_jetsAK4nEMEnergy;
   Handle<vector<float> > h_jetsAK4HFHadronEnergy;
   Handle<vector<float> > h_jetsAK4cHadEnergy;
   Handle<vector<float> > h_jetsAK4cEMEnergy;
   Handle<vector<float> > h_jetsAK4numDaughters;
   Handle<vector<float> > h_jetsAK4cMultip;
   Handle<vector<float> > h_jetsAK4Y;

   //Rho handles
   Handle <double> h_rho;

   //MET handles
   Handle<vector<float> > h_metPt;
   Handle<vector<float> > h_metPx;
   Handle<vector<float> > h_metPy;
   Handle<vector<float> > h_metPhi;

   //AK8 jet handles
   Handle<vector<float> > h_jetsAK8GenJetE;
   Handle<vector<float> > h_jetsAK8GenJetPt;
   Handle<vector<float> > h_jetsAK8GenJetEta;
   Handle<vector<float> > h_jetsAK8GenJetPhi;
   Handle<vector<float> > h_jetsAK8GenJetY;

   Handle<vector<float> > h_jetsAK8E;
   Handle<vector<float> > h_jetsAK8Pt;
   Handle<vector<float> > h_jetsAK8Eta;
   Handle<vector<float> > h_jetsAK8Phi;
   Handle<vector<float> > h_jetsAK8Y;
   Handle<vector<float> > h_jetsAK8minmass;
   Handle<vector<float> > h_jetsAK8tau1;
   Handle<vector<float> > h_jetsAK8tau2;
   Handle<vector<float> > h_jetsAK8tau3;
   Handle<vector<float> > h_jetsAK8nSubJets;
   Handle<vector<float> > h_jetsAK8filteredMass;
   Handle<vector<float> > h_jetsAK8prunedMass;
   Handle<vector<float> > h_jetsAK8trimmedMass;
   Handle<vector<float> > h_jetsAK8softDropMass;
   Handle<vector<float> > h_jetsAK8topMass;
   Handle<vector<float> > h_jetsAK8ungroomedMass;
   Handle<vector<float> > h_jetsAK8Area;
   Handle<vector<float> > h_jetsAK8CSV;

   Handle<vector<float> > h_jetsAK8JEC;
   Handle<vector<float> > h_jetsAK8JERup;
   Handle<vector<float> > h_jetsAK8JERdown;
   
   Handle<vector<float> > h_jetsAK8SmearedE;
   Handle<vector<float> > h_jetsAK8SmearedEta;
   Handle<vector<float> > h_jetsAK8SmearedPhi;
   Handle<vector<float> > h_jetsAK8SmearedPt;
   
   Handle<vector<vector<int> > > h_jetsAK8Keys;

   Handle<vector<float> > h_jetsAK8nHadEnergy;
   Handle<vector<float> > h_jetsAK8nEMEnergy;
   Handle<vector<float> > h_jetsAK8HFHadronEnergy;
   Handle<vector<float> > h_jetsAK8cHadEnergy;
   Handle<vector<float> > h_jetsAK8cEMEnergy;

   Handle<vector<float> > h_jetsAK8nHadEnergyFrac;
   Handle<vector<float> > h_jetsAK8nEMEnergyFrac;
   Handle<vector<float> > h_jetsAK8HFHadronEnergyFrac;
   Handle<vector<float> > h_jetsAK8cHadEnergyFrac;
   Handle<vector<float> > h_jetsAK8cEMEnergyFrac;

   Handle<vector<float> > h_jetsAK8numDaughters;
   Handle<vector<float> > h_jetsAK8cMultip;
   Handle<vector<float> > h_jetsAK8nMultip;
   Handle<vector<float> > h_jetsAK8cHadMultip;
   Handle<vector<float> > h_jetsAK8nHadMultip;

   //AK8 CMS subjet handles
   Handle<vector<float> > h_ak8jetTopSubjetIndex0;
   Handle<vector<float> > h_ak8jetTopSubjetIndex1;
   Handle<vector<float> > h_ak8jetTopSubjetIndex2;
   Handle<vector<float> > h_ak8jetTopSubjetIndex3;
   Handle<vector<float> > h_subjetsCmsTopTagCSV;

   Handle<vector<float> > h_subjetsCmsTopTagPt;
   Handle<vector<float> > h_subjetsCmsTopTagEta;
   Handle<vector<float> > h_subjetsCmsTopTagPhi;
   Handle<vector<float> > h_subjetsCmsTopTagMass;
   Handle<vector<float> > h_subjetsCmsTopTagArea;
   Handle<vector<float> > h_subjetsCmsTopTagnumDaughters;
   Handle<vector<float> > h_subjetsCmsTopTagY;

   Handle<vector<float> > h_subjetsCmsTopTagJEC0;
   Handle<vector<float> > h_subjetsCmsTopTagJERup;
   Handle<vector<float> > h_subjetsCmsTopTagJERdown;

   Handle<vector<float> > h_subjetsCmsTopTagSmearedE;
   Handle<vector<float> > h_subjetsCmsTopTagSmearedEta;
   Handle<vector<float> > h_subjetsCmsTopTagSmearedPhi;
   Handle<vector<float> > h_subjetsCmsTopTagSmearedPt;

   //AK8 Soft Drop subjet handles - labeled
   Handle<vector<float> > h_ak8jetSoftDropSubjetIndex0;
   Handle<vector<float> > h_ak8jetSoftDropSubjetIndex1;
   Handle<vector<float> > h_subjetsSoftDropCSV;

   Handle<vector<float> > h_subjetsSoftDropPt;
   Handle<vector<float> > h_subjetsSoftDropEta;
   Handle<vector<float> > h_subjetsSoftDropPhi;
   Handle<vector<float> > h_subjetsSoftDropMass;
   Handle<vector<float> > h_subjetsSoftDropArea;
   Handle<vector<float> > h_subjetsSoftDropnumDaughters;
   Handle<vector<float> > h_subjetsSoftDropY;

   Handle<vector<float> > h_subjetsSoftDropJEC0;
   Handle<vector<float> > h_subjetsSoftDropJERup;
   Handle<vector<float> > h_subjetsSoftDropJERdown;

   Handle<vector<float> > h_subjetsSoftDropSmearedE;
   Handle<vector<float> > h_subjetsSoftDropSmearedEta;
   Handle<vector<float> > h_subjetsSoftDropSmearedPhi;
   Handle<vector<float> > h_subjetsSoftDropSmearedPt;

   /*Handle<vector<float> > h_subjetsAK8GenE;
   Handle<vector<float> > h_subjetsAK8GenPt;
   Handle<vector<float> > h_subjetsAK8GenEta;
   Handle<vector<float> > h_subjetsAK8GenPhi;

   Handle<vector<float> > h_subjetsAK8E;
   Handle<vector<float> > h_subjetsAK8Pt;
   Handle<vector<float> > h_subjetsAK8Eta;
   Handle<vector<float> > h_subjetsAK8Phi;*/


   //***LABELS***

   //trigger and filter labels
   iEvent.getByLabel("METUserData", "triggerNameTree", triggerNameStringsHandleF);
   iEvent.getByLabel("METUserData", "triggerBitTree", triggerBitHandleF);
   iEvent.getByLabel("METUserData", "triggerPrescaleTree", triggerPrescaleHandleF);

   iEvent.getByLabel("HBHENoiseFilterResultProducer", "HBHENoiseFilterResult", HBHEfilterHandleF);

   iEvent.getByLabel("TriggerUserData", "triggerNameTree", triggerNameStringsHandle);
   iEvent.getByLabel("TriggerUserData", "triggerBitTree", triggerBitHandle);
   iEvent.getByLabel("TriggerUserData", "triggerPrescaleTree", triggerPrescaleHandle);

   //event info
   iEvent.getByLabel("eventInfo", "evtInfoEventNumber", h_eventNumber);
   iEvent.getByLabel("eventUserData", "npv", h_npv );
   iEvent.getByLabel("eventUserData" , "puNtrueInt", h_puNtrueInt);
      
   iEvent.getByLabel("vertexInfo", "chi", h_pv_chi);
   iEvent.getByLabel("vertexInfo", "rho", h_pv_rho);
   iEvent.getByLabel("vertexInfo", "z", h_pv_z);
   iEvent.getByLabel("vertexInfo", "ndof", h_pv_ndof);

   //generator info
   if (isMC_){
     iEvent.getByLabel("generator", "", h_genEventInfo);
     //iEvent.getByLabel("externalLHEProducer", "", h_lheRunInfo);
   }

   //iEvent.getByLabel();

   //gen parton labels
   iEvent.getByLabel("genPart" , "genPartPt", h_genPartPt);
   iEvent.getByLabel("genPart" , "genPartEta", h_genPartEta);
   iEvent.getByLabel("genPart" , "genPartPhi", h_genPartPhi);
   iEvent.getByLabel("genPart" , "genPartPhi", h_genPartPhi);
   iEvent.getByLabel("genPart" , "genPartMass", h_genPartMass);
   iEvent.getByLabel("genPart" , "genPartID", h_genPartID);
   iEvent.getByLabel("genPart" , "genPartStatus", h_genPartStatus);
   iEvent.getByLabel("genPart" , "genPartMom0ID", h_genPartMomID);

   //muon labels
   iEvent.getByLabel("muons" , "muPt", h_muPt);
   iEvent.getByLabel("muons" , "muEta", h_muEta);
   iEvent.getByLabel("muons" , "muPhi", h_muPhi);
   iEvent.getByLabel("muons" , "muIsTightMuon", h_muTight);
   iEvent.getByLabel("muons" , "muIsLooseMuon", h_muLoose);
   iEvent.getByLabel("muons" , "muMass", h_muMass);
   iEvent.getByLabel("muons", "muDz", h_muDz);
   iEvent.getByLabel("muons", "muCharge", h_muCharge);
   iEvent.getByLabel("muons", "muIso04", h_muIso04);

   iEvent.getByLabel("muonKeys", "", h_muKey);

   //electron labels
   iEvent.getByLabel("electrons" , "elPt", h_elPt);
   iEvent.getByLabel("electrons" , "elEta", h_elEta);
   iEvent.getByLabel("electrons" , "elPhi", h_elPhi);
   iEvent.getByLabel("electrons" , "elisTight", h_elTight);
   iEvent.getByLabel("electrons" , "elisLoose", h_elLoose);
   iEvent.getByLabel("electrons" , "eldEtaIn", h_eldEtaIn);
   iEvent.getByLabel("electrons" , "eldPhiIn", h_eldPhiIn);
   iEvent.getByLabel("electrons" , "elHoE", h_elHoE);
   iEvent.getByLabel("electrons" , "elfull5x5siee", h_elfull5x5siee);
   iEvent.getByLabel("electrons" , "elE", h_elE);
   iEvent.getByLabel("electrons" , "elD0", h_elD0);
   iEvent.getByLabel("electrons" , "elDz", h_elDz);
   iEvent.getByLabel("electrons" , "elIso03", h_elIso03);
   iEvent.getByLabel("electrons" , "elisVeto", h_elisVeto);
   iEvent.getByLabel("electrons" , "elhasMatchedConVeto", h_elhasMatchedConVeto);
   iEvent.getByLabel("electrons" , "elooEmooP", h_elooEmooP);
   iEvent.getByLabel("electrons" , "elMass", h_elMass);
   iEvent.getByLabel("electrons" , "elscEta", h_elscEta);
   iEvent.getByLabel("electrons" , "elCharge", h_elCharge);

   iEvent.getByLabel("electronKeys", "", h_elKey);

   //AK4 jet labels
   iEvent.getByLabel("jetsAK4" , "jetAK4E", h_jetsAK4E);
   iEvent.getByLabel("jetsAK4" , "jetAK4Pt", h_jetsAK4Pt);
   iEvent.getByLabel("jetsAK4" , "jetAK4Eta", h_jetsAK4Eta);
   iEvent.getByLabel("jetsAK4" , "jetAK4Phi", h_jetsAK4Phi);
   iEvent.getByLabel("jetsAK4" , "jetAK4Mass", h_jetsAK4ungroomedMass);
   iEvent.getByLabel("jetsAK4" , "jetAK4jecFactor0", h_jetsAK4JEC);
   iEvent.getByLabel("jetsAK4" , "jetAK4CSV", h_jetsAK4CSV);
   iEvent.getByLabel("jetsAK4" , "jetAK4numberOfDaughters", h_jetsAK4NumDaughters);
   iEvent.getByLabel("jetsAK4" , "jetAK4jetArea", h_jetsAK4Area);

   iEvent.getByLabel("jetKeysAK4" , "", h_jetsAK4Keys);

   iEvent.getByLabel("jetsAK4" , "jetAK4neutralHadronEnergy", h_jetsAK4nHadEnergy);
   iEvent.getByLabel("jetsAK4" , "jetAK4neutralEmEnergy", h_jetsAK4nEMEnergy);
   iEvent.getByLabel("jetsAK4" , "jetAK4HFHadronEnergy", h_jetsAK4HFHadronEnergy);
   iEvent.getByLabel("jetsAK4" , "jetAK4chargedHadronEnergy", h_jetsAK4cHadEnergy);
   iEvent.getByLabel("jetsAK4" , "jetAK4chargedEmEnergy", h_jetsAK4cEMEnergy);
   iEvent.getByLabel("jetsAK4" , "jetAK4numberOfDaughters", h_jetsAK4numDaughters);
   iEvent.getByLabel("jetsAK4" , "jetAK4chargedMultiplicity", h_jetsAK4cMultip);
   iEvent.getByLabel("jetsAK4" , "jetAK4Y", h_jetsAK4Y);

   //Rho labels
   iEvent.getByLabel("fixedGridRhoFastjetAll", "", h_rho);

   //MET labels
   iEvent.getByLabel("met" , "metPt", h_metPt);
   iEvent.getByLabel("met" , "metPx", h_metPx);
   iEvent.getByLabel("met" , "metPy", h_metPy);
   iEvent.getByLabel("met" , "metPhi", h_metPhi);

   //AK8 jet labels
   iEvent.getByLabel("jetsAK8", "jetAK8GenJetE", h_jetsAK8GenJetE );
   iEvent.getByLabel("jetsAK8", "jetAK8GenJetPt", h_jetsAK8GenJetPt );
   iEvent.getByLabel("jetsAK8", "jetAK8GenJetEta", h_jetsAK8GenJetEta );
   iEvent.getByLabel("jetsAK8", "jetAK8GenJetPhi", h_jetsAK8GenJetPhi );
   iEvent.getByLabel("jetsAK8" , "jetAK8Y", h_jetsAK8GenJetY);

   iEvent.getByLabel("jetsAK8", "jetAK8E", h_jetsAK8E );
   iEvent.getByLabel("jetsAK8", "jetAK8Pt", h_jetsAK8Pt );
   iEvent.getByLabel("jetsAK8", "jetAK8Eta", h_jetsAK8Eta );
   iEvent.getByLabel("jetsAK8", "jetAK8Phi", h_jetsAK8Phi );
   iEvent.getByLabel("jetsAK8", "jetAK8Y", h_jetsAK8Y );
   iEvent.getByLabel("jetsAK8", "jetAK8minmass", h_jetsAK8minmass );
   iEvent.getByLabel("jetsAK8", "jetAK8tau1", h_jetsAK8tau1 );
   iEvent.getByLabel("jetsAK8", "jetAK8tau2", h_jetsAK8tau2 );
   iEvent.getByLabel("jetsAK8", "jetAK8tau3", h_jetsAK8tau3 );
   iEvent.getByLabel("jetsAK8", "jetAK8nSubJets", h_jetsAK8nSubJets );
   iEvent.getByLabel("jetsAK8", "jetAK8filteredMass", h_jetsAK8filteredMass );
   iEvent.getByLabel("jetsAK8", "jetAK8prunedMass", h_jetsAK8prunedMass );
   iEvent.getByLabel("jetsAK8", "jetAK8trimmedMass", h_jetsAK8trimmedMass );
   iEvent.getByLabel("jetsAK8", "jetAK8softDropMass", h_jetsAK8softDropMass );
   iEvent.getByLabel("jetsAK8", "jetAK8topMass", h_jetsAK8topMass );
   iEvent.getByLabel("jetsAK8", "jetAK8Mass", h_jetsAK8ungroomedMass );
   iEvent.getByLabel("jetsAK8" , "jetAK8jetArea", h_jetsAK8Area);//unlabeled
   iEvent.getByLabel("jetsAK8" , "jetAK8CSV", h_jetsAK8CSV);//unlabeled

   //unlabeled
   iEvent.getByLabel("jetsAK8" , "jetAK8jecFactor0", h_jetsAK8JEC);
   iEvent.getByLabel("jetsAK8" , "jetAK8JERup", h_jetsAK8JERup);
   iEvent.getByLabel("jetsAK8" , "jetAK8JERdown", h_jetsAK8JERdown);
   
   iEvent.getByLabel("jetsAK8" , "jetAK8SmearedE", h_jetsAK8SmearedE);
   iEvent.getByLabel("jetsAK8" , "jetAK8SmearedPEta", h_jetsAK8SmearedEta);
   iEvent.getByLabel("jetsAK8" , "jetAK8SmearedPhi", h_jetsAK8SmearedPhi);
   iEvent.getByLabel("jetsAK8" , "jetAK8SmearedPt", h_jetsAK8SmearedPt);

   iEvent.getByLabel("jetKeysAK8" , "", h_jetsAK8Keys);

   iEvent.getByLabel("jetsAK8" , "jetAK8neutralHadronEnergy", h_jetsAK8nHadEnergy);
   iEvent.getByLabel("jetsAK8" , "jetAK8neutralEmEnergy", h_jetsAK8nEMEnergy);
   iEvent.getByLabel("jetsAK8" , "jetAK8HFHadronEnergy", h_jetsAK8HFHadronEnergy);
   iEvent.getByLabel("jetsAK8" , "jetAK8chargedHadronEnergy", h_jetsAK8cHadEnergy);
   iEvent.getByLabel("jetsAK8" , "jetAK8chargedEmEnergy", h_jetsAK8cEMEnergy);

   iEvent.getByLabel("jetsAK8" , "jetAK8neutralHadronEnergyFrac", h_jetsAK8nHadEnergyFrac);
   iEvent.getByLabel("jetsAK8" , "jetAK8neutralEmEnergyFrac", h_jetsAK8nEMEnergyFrac);
   iEvent.getByLabel("jetsAK8" , "jetAK8HFHadronEnergyFrac", h_jetsAK8HFHadronEnergyFrac);
   iEvent.getByLabel("jetsAK8" , "jetAK8chargedHadronEnergyFrac", h_jetsAK8cHadEnergyFrac);
   iEvent.getByLabel("jetsAK8" , "jetAK8chargedEmEnergyFrac", h_jetsAK8cEMEnergyFrac);

   iEvent.getByLabel("jetsAK8" , "jetAK8numberOfDaughters", h_jetsAK8numDaughters);
   iEvent.getByLabel("jetsAK8" , "jetAK8chargedMultiplicity", h_jetsAK8cMultip);
   iEvent.getByLabel("jetsAK8" , "jetAK8neutralMultiplicity", h_jetsAK8nMultip);
   iEvent.getByLabel("jetsAK8" , "jetAK8chargedHadronMultiplicity", h_jetsAK8cHadMultip);
   iEvent.getByLabel("jetsAK8" , "jetAK8neutralHadronMultiplicity", h_jetsAK8nHadMultip);

   //AK8 CMS subjet labels
   iEvent.getByLabel("jetsAK8", "jetAK8topSubjetIndex0", h_ak8jetTopSubjetIndex0);
   iEvent.getByLabel("jetsAK8", "jetAK8topSubjetIndex1", h_ak8jetTopSubjetIndex1);
   iEvent.getByLabel("jetsAK8", "jetAK8topSubjetIndex2", h_ak8jetTopSubjetIndex2);
   iEvent.getByLabel("jetsAK8", "jetAK8topSubjetIndex3", h_ak8jetTopSubjetIndex3);
   iEvent.getByLabel("subjetsCmsTopTag", "subjetCmsTopTagCSV", h_subjetsCmsTopTagCSV);

   //unlabeled
   iEvent.getByLabel("subjetsCmsTopTag", "subjetCmsTopTagPt", h_subjetsCmsTopTagPt);
   iEvent.getByLabel("subjetsCmsTopTag", "subjetCmsTopTagEta", h_subjetsCmsTopTagEta);
   iEvent.getByLabel("subjetsCmsTopTag", "subjetCmsTopTagPhi", h_subjetsCmsTopTagPhi);
   iEvent.getByLabel("subjetsCmsTopTag", "subjetCmsTopTagMass", h_subjetsCmsTopTagMass);
   iEvent.getByLabel("subjetsCmsTopTag", "subjetCmsTopTagjetArea", h_subjetsCmsTopTagArea);
   iEvent.getByLabel("subjetsCmsTopTag", "subjetCmsTopTagnumberOfDaughters", h_subjetsCmsTopTagnumDaughters);
   iEvent.getByLabel("subjetsCmsTopTag", "subjetCmsTopTagY", h_subjetsCmsTopTagY);

   iEvent.getByLabel("subjetsCmsTopTag", "subjetCmsTopTagjecFactor0", h_subjetsCmsTopTagJEC0);
   iEvent.getByLabel("subjetsCmsTopTag", "subjetCmsTopTagJERup", h_subjetsCmsTopTagJERup);
   iEvent.getByLabel("subjetsCmsTopTag", "subjetCmsTopTagJERdown", h_subjetsCmsTopTagJERdown);

   iEvent.getByLabel("subjetsCmsTopTag" , "subjetCmsTopTagSmearedE", h_subjetsCmsTopTagSmearedE);
   iEvent.getByLabel("subjetsCmsTopTag" , "subjetCmsTopTagSmearedPEta", h_subjetsCmsTopTagSmearedEta);
   iEvent.getByLabel("subjetsCmsTopTag" , "subjetCmsTopTagSmearedPhi", h_subjetsCmsTopTagSmearedPhi);
   iEvent.getByLabel("subjetsCmsTopTag" , "subjetCmsTopTagSmearedPt", h_subjetsCmsTopTagSmearedPt);

   //AK8 Soft Drop subjet labels
   iEvent.getByLabel("jetsAK8", "jetAK8vSubjetIndex0", h_ak8jetSoftDropSubjetIndex0);
   iEvent.getByLabel("jetsAK8", "jetAK8vSubjetIndex1", h_ak8jetSoftDropSubjetIndex1);
   iEvent.getByLabel("subjetsAK8", "subjetAK8CSV", h_subjetsSoftDropCSV);

   iEvent.getByLabel("subjetsAK8", "subjetAK8Pt", h_subjetsSoftDropPt);
   iEvent.getByLabel("subjetsAK8", "subjetAK8Eta", h_subjetsSoftDropEta);
   iEvent.getByLabel("subjetsAK8", "subjetAK8Phi", h_subjetsSoftDropPhi);
   iEvent.getByLabel("subjetsAK8", "subjetAK8Mass", h_subjetsSoftDropMass);
   iEvent.getByLabel("subjetsAK8", "subjetAK8jetArea", h_subjetsSoftDropArea);
   iEvent.getByLabel("subjetsAK8", "subjetAK8numberOfDaughters", h_subjetsSoftDropnumDaughters);
   iEvent.getByLabel("subjetsAK8", "subjetAK8Y", h_subjetsSoftDropY);

   iEvent.getByLabel("subjetsAK8", "subjetAK8jecFactor0", h_subjetsSoftDropJEC0);
   iEvent.getByLabel("subjetsAK8", "subjetAK8JERup", h_subjetsSoftDropJERup);
   iEvent.getByLabel("subjetsAK8", "subjetAK8JERdown", h_subjetsSoftDropJERdown);

   iEvent.getByLabel("subjetsAK8", "subjetAK8DropSmearedE", h_subjetsSoftDropSmearedE);
   iEvent.getByLabel("subjetsAK8", "subjetAK8DropSmearedPEta", h_subjetsSoftDropSmearedEta);
   iEvent.getByLabel("subjetsAK8", "subjetAK8DropSmearedPhi", h_subjetsSoftDropSmearedPhi);
   iEvent.getByLabel("subjetsAK8", "subjetAK8DropSmearedPt", h_subjetsSoftDropSmearedPt);

   //cout<<"Handles set!"<<endl;

   /*iEvent.getByLabel("subjetsAK8", "subjetAK8GenSubjetE", h_subjetsAK8GenE );
   iEvent.getByLabel("subjetsAK8", "subjetAK8GenSubjetPt", h_subjetsAK8GenPt );
   iEvent.getByLabel("subjetsAK8", "subjetAK8GenSubjetEta", h_subjetsAK8GenEta );
   iEvent.getByLabel("subjetsAK8", "subjetAK8GenSubjetPhi", h_subjetsAK8GenPhi );

   iEvent.getByLabel("subjetsAK8", "subjetAK8E", h_subjetsAK8E );
   iEvent.getByLabel("subjetsAK8", "subjetAK8Pt", h_subjetsAK8Pt );
   iEvent.getByLabel("subjetsAK8", "subjetAK8Eta", h_subjetsAK8Eta );
   iEvent.getByLabel("subjetsAK8", "subjetAK8Phi", h_subjetsAK8Phi );*/

   //***Counters***
   //event count
   int NeventsDiLeptonic  = 0;
   int NeventsSemiLeptonic  = 0;
   int NeventsSemiLeptonicMuon      = 0;
   int NeventsSemiLeptonicElectron  = 0;
   int NeventsAllHadronic  = 0;
   
   int Nevents = 0;
   int NeventsBeforeChannelSelect = 0;
   int NeventsAfterChannelSelect = 0;
   int NeventsBkgdEstimation = 0;
   int NeventsAK8product = 0;
   
   int Nevents_weighted = 0;
   
   // Top Tag count
   int nttags = 0;

   //Tracker variables
   int DimuonEvents = 0;
   int DieleEvents = 0;
   int muoneleEvents = 0;
   int muonJetsEvents = 0;
   int eleJetsEvents = 0;
   int AllHadronicEvents = 0;
   int NMu = 0;
   int NEl = 0;
   int NAK4Jets = 0;
   int NAK8Jets = 0;
   int NPassMuonPtCut = 0;
   int NPassMuonEtaCut = 0; 
   int NPassMuonDzCut = 0;
   int NPassMuonTightCut = 0;
   int NPassElPtCut = 0;
   int NPassElEtaCut = 0;
   int NPassGoodElCut = 0;
   int NPassEldEtaIn = 0;
   int NPassEldPhiIn= 0;
   int NPassEl5x5= 0;
   int NPassElHoE = 0;
   int NPassElD0 = 0;
   int NPassElDz = 0;
   int NPassElEmooP = 0;
   int NPassElKeyCut = 0;
   int NPassGoodJetAK4Cut = 0;
   int NPassMinAK4PtCut = 0;
   int NPassMaxAK4RapidityCut = 0;
   int NPass2DCut = 0;
   int NPass2D2Cut = 0;
   int NPassMET = 0;
   int NPassHTLep = 0;
   int NPassST = 0;
   int NPassTriangularCut = 0;
   int NPassGoodJetAK8Cut = 0;
   int NPassMinRawAK8PtCut = 0;
   int NPassMaxAK8RapidityCut = 0; 
   int NPassSemiLeptonicDRjlCut = 0;
   int NPassAK8nSubJetsCut = 0;
   int NPassAK8MinMassCut = 0;
   int NPassAK8SubjetBDiscCut = 0;
   int NPassAK8CorrMassCut = 0; 
   int NPassminAK8PtCut = 0;
   int NPasstMinMassCut = 0; 
   int NPasstMAK8GroomedMinCut = 0; 
   int NPasstMAK8GroomedMaxCut = 0; 
   int NPasstau23Cut = 0;
   int NPasstau21Cut = 0; 
   int NPassBDiscMinCut = 0; 
   //int NPassBDiscMinMCut = 0;
   //int NPassBDiscMinTCut = 0;
   int NPassBDisc2MinCut = 0; 
   int NPassMuonBCut = 0;
   int NPassElBCut = 0;
   int NPassNearJCut = 0;
   int NPassNearJ2Cut = 0;
   int NPassMuon2DCut = 0;
   int NPassEl2DCut = 0;
   int NPassMuonTot = 0;
   int NPassAK4KinTot = 0;
   int NPassWbEvent= 0;
   
   //for MC
   int genSemiMuEvents = 0;
   int genSemiEEvents = 0;
   int genMuMuEvents = 0;
   int genMuEEvents = 0;
   int genEEEvents = 0;
   int genHadEvents = 0;
   

   //reco AK8 jets   
   int nAK8pt400eta2p4jets = 0;

   //top tagging
   //int nTopTagJets = 0;
   int topTagJet0_topTagFlag = 0;
   int topTagJet1_topTagFlag = 0;
   int nNsubjettinessCutJets = 0;
   int nBtagJets = 0;

   //saving jet 4 vectors to reconstruct Z' mass
   TLorentzVector softDropJet0;
   TLorentzVector softDropJet1;

   TLorentzVector ungroomedJet0;
   TLorentzVector ungroomedJet1;
   
   //int toptagindexJet0_cmstt = -1;
   //int toptagindexJet0_filtered = -1;
   //int toptagindexJet0_pruned = -1;
   //int toptagindexJet0_trimmed = -1;

   //int toptagindexJet1_cmstt = -1;
   //int toptagindexJet1_filtered = -1;
   //int toptagindexJet1_pruned = -1;
   //int toptagindexJet1_trimmed = -1;

   //TLorentzVector cmsttJet0;
   //TLorentzVector filteredJet0;
   //TLorentzVector prunedJet0;
   //TLorentzVector trimmedJet0;

   //TLorentzVector cmsttJet1;
   //TLorentzVector filteredJet1;
   //TLorentzVector prunedJet1;
   //TLorentzVector trimmedJet


   //cout <<"Event number: "<<*h_eventNumber<<endl;
   if (h_eventNumber.isValid()) hadTreeVars["eventNumber"] = *h_eventNumber;

   //want to make sure the AK8 jet vectors match up
   if (h_jetsAK8Pt->size() != h_jetsAK8minmass->size() || h_jetsAK8Pt->size() != h_jetsAK8topMass->size()){
     cout<<"Error! Mismatched vectors."<<endl;
   }

   //cout<<"Initializing branches!"<<endl;

   //initializing branches to -999.99
   for (unsigned i = 0; i < listOfHadVars.size(); i++){
     hadTreeVars[ listOfHadVars[i] ] = -999.99;
   }
   /*for (unsigned i = 0; i < listOfSemileptVars.size(); i++){
     semileptTreeVars[ listOfSemileptVars[i] ] = -999.99;
     }*/

   //event filters
   bool cscFilt = 0;
   bool vertexFilt = 0;
   bool hbheFilt = 0;
   
   hbheFilt = (*HBHEfilterHandleF);
   
   //cout<<"Setting filter bits!"<<endl;

   if (triggerNameStringsHandleF.isValid()){
     //cout<<"Valid Strings Handle!"<<endl;
     for (size_t i = 0; i < triggerNameStringsHandleF->size(); i++){
       if ( (*triggerNameStringsHandleF)[i].find("CSC") != string::npos) {
	 if ( (*triggerBitHandleF)[i] == 1 ) cscFilt = 1;
       }
       //Broken HBHE Filter
       //if ( (*triggerNameStringsHandleF)[i].find("HBHE") != string::npos) {
       //        if ( (*triggerBitHandleF)[i] == 1 ) hbheFilt = 1;
       //}
       if ( (*triggerNameStringsHandleF)[i].find("goodVer") != string::npos) {
	 if ( (*triggerBitHandleF)[i] == 1 ) vertexFilt = 1;
       }
     }
   }

   //cout<<"Filter bits set!"<<endl;

   hadTreeVars["cscFilt"] = cscFilt;
   hadTreeVars["vertexFilt"] = vertexFilt;
   hadTreeVars["hbheFilt"] = hbheFilt;

   /*semileptTreeVars["cscFilt"] = cscFilt;
   semileptTreeVars["vertexFilt"] = vertexFilt;
   semileptTreeVars["hbheFilt"] = hbheFilt;*/

   //cout<<"CSC Filter bit: "<<cscFilt<<endl;
   //cout<<"VERTEX Filter bit: "<<vertexFilt<<endl;
   //cout<<"HBHE Filter bit: "<<hbheFilt<<endl; 

   double evWeight = 1.0;

   //semileptonic triggers to run
   /*vector<string> trigsToRun;
   trigsToRun.push_back("HLT_IsoMu24_eta2p1");
   trigsToRun.push_back("HLT_Mu45_eta2p1");
   trigsToRun.push_back("HLT_Mu50_");
   trigsToRun.push_back("HLT_Mu40_eta2p1_PFJet200_PFJet50");
   trigsToRun.push_back("HLT_IsoMu24_eta2p1");
   trigsToRun.push_back("HLT_Ele32_eta2p1_WPLoose_Gsf");
   trigsToRun.push_back("HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50");
   trigsToRun.push_back("HLT_Ele105_CaloIdVT_GsfTrkIdT");
   trigsToRun.push_back("HLT_Ele115_CaloIdVT_GsfTrkIdT");

   bool passTrig = 0;
   double prescale = 1.0;
   bool unprescaled = 0;


   if (triggerNameStringsHandle.isValid()){
     for (size_t itrig = 0; itrig < triggerBitHandle->size(); itrig++){
       if ( (*triggerBitHandle)[itrig] == 1){
	 for(size_t itrigToRun = 0; itrigToRun < trigsToRun.size(); itrigToRun++){
	   while(!passTrig){
	     if ( (*triggerNameStringsHandle)[itrig].find(trigsToRun[itrigToRun]) != string::npos){
	       passTrig = 1;
	       semileptTreeVars["SemiLeptTrig"] = itrigToRun;
	       prescale = prescale * ((*triggerPrescaleHandle)[itrig]);
	       if ((*triggerPrescaleHandle)[itrig] == 1.0){
		 unprescaled = 1;
		 prescale = 1.0;
	       }
	     }//finding the first passed trigger and saving the associated prescale
	   }//saving the iterator number of the first passed trigger
	 }//looping over semileptonic triggers of interest
       }//finding fired triggers
     }//looping over triggers
   }//semileptonic triggers

   evWeight = evWeight * prescale;*/

   //leptonic trigger booleans
   /*bool isoMu24trig = 0;
   bool mu45trig = 0;
   bool mu50trig = 0;
   bool mu40trig = 0;
   bool ele32trig = 0;
   bool ele45trig = 0;
   bool ele105trig = 0;
   bool ele115trig = 0;

   if (triggerNameStringsHandle.isValid()){
     for (size_t i = 0; i < triggerNameStringsHandle->size(); i++){
       if ( (*triggerNameStringsHandle)[i].find("HLT_IsoMu24_eta2p1") != string::npos) {
	 if ( (*triggerBitHandle)[i] == 1 ) isoMu24trig = 1;
       }
       if ( (*triggerNameStringsHandle)[i].find("HLT_Mu45_eta2p1") != string::npos) {
	 if ( (*triggerBitHandle)[i] == 1 ) mu45trig = 1;
       }
       if ( (*triggerNameStringsHandle)[i].find("HLT_Mu50_") != string::npos) {
	 if ( (*triggerBitHandle)[i] == 1 ) mu50trig = 1;
       }
       if ( (*triggerNameStringsHandle)[i].find("HLT_Mu40_eta2p1_PFJet200_PFJet50") != string::npos) {
	 if ( (*triggerBitHandle)[i] == 1 ) mu40trig = 1;
       }
       if ( (*triggerNameStringsHandle)[i].find("HLT_Ele32_eta2p1_WPLoose_Gsf") != string::npos) {
	 if ( (*triggerBitHandle)[i] == 1 ) ele32trig = 1;
       }
       if ( (*triggerNameStringsHandle)[i].find("HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50") != string::npos) {
	 if ( (*triggerBitHandle)[i] == 1 ) ele45trig = 1;
       }
       if ( (*triggerNameStringsHandle)[i].find("HLT_Ele105_CaloIdVT_GsfTrkIdT") != string::npos) {
	 if ( (*triggerBitHandle)[i] == 1 ) ele105trig = 1;
       }
       if ( (*triggerNameStringsHandle)[i].find("HLT_Ele115_CaloIdVT_GsfTrkIdT") != string::npos) {
	 if ( (*triggerBitHandle)[i] == 1 ) ele115trig = 1;
       }
     }
   }

   semileptTreeVars["isoMu24trig"] = isoMu24trig;
   semileptTreeVars["mu45trig"] = mu45trig;
   semileptTreeVars["mu50trig"] = mu50trig;
   semileptTreeVars["mu40trig"] = mu40trig;
   semileptTreeVars["ele32trig"] =ele32trig;
   semileptTreeVars["ele45trig"] = ele45trig;
   semileptTreeVars["ele105trig"] = ele105trig;
   semileptTreeVars["ele115trig"] = ele115trig;
   */

   //hadronic trigger booleans
   bool htTrig = 0;
   bool jetTrig = 0;
   bool ak8TrimjetTrig = 0;
   bool ht650TrimjetTrig = 0;
   bool ht700TrimjetTrig = 0;

   //cout<<"Setting trigger bits!"<<endl;

   if (triggerNameStringsHandle.isValid()){
     for (size_t i = 0; i < triggerNameStringsHandle->size(); i++){
       if ( (*triggerNameStringsHandle)[i].find("PFHT800") != string::npos) {
	 if ( (*triggerBitHandle)[i] == 1 ) htTrig = 1;
       }
       if ( (*triggerNameStringsHandle)[i].find("PFJet400") != string::npos) {
	 if ( (*triggerBitHandle)[i] == 1 ) jetTrig = 1;
       }
       if ( (*triggerNameStringsHandle)[i].find("AK8PFJet360_TrimMass30") != string::npos) {
	 if ( (*triggerBitHandle)[i] == 1 ) ak8TrimjetTrig = 1;
       }
       if ( (*triggerNameStringsHandle)[i].find("HT650_Trim") != string::npos) {
	 if ( (*triggerBitHandle)[i] == 1 ) ht650TrimjetTrig = 1;
       }
       if ( (*triggerNameStringsHandle)[i].find("HT700_Trim") != string::npos) {
	 if ( (*triggerBitHandle)[i] == 1 ) ht700TrimjetTrig = 1;
       }
     }
   }

   //cout<<"Storing trigger bits!"<<endl;

   hadTreeVars["htTrig"] = htTrig;
   hadTreeVars["jetTrig"] = jetTrig;
   hadTreeVars["ak8TrimjetTrig"] = ak8TrimjetTrig;
   hadTreeVars["ht650TrimjetTrig"] = ht650TrimjetTrig;
   hadTreeVars["ht700TrimjetTrig"] = ht700TrimjetTrig;

   //cout<<"Initializing event weights!"<<endl;

   //generator info
   if(isMC_ && h_genPartPt.isValid()){
     vector<size_t> genEIndex;
     vector<size_t> genMuIndex;
     double topQuarkPt = 0.0;
     int ngenE = 0;
     int ngenMu = 0;

     for(size_t igen = 0; igen < h_genPartPt->size(); igen++){
       if((*h_genPartStatus)[igen] < 25 && (*h_genPartStatus)[igen] > 19){
	 if(abs((*h_genPartID)[igen] == 6)) topQuarkPt = (*h_genPartPt)[igen];
	 else if(abs((*h_genPartID)[igen] == 11) && abs((*h_genPartMomID)[igen] == 24)){
	   genEIndex.push_back(igen);
	   ngenE += 1;
	 }//electron
	 else if(abs((*h_genPartID)[igen] == 13) && abs((*h_genPartMomID)[igen] == 24)){
	   genMuIndex.push_back(igen);
	   ngenMu += 1;
	 }//muon
       }//gen status requirement
     }//gen particle for loop
     
     if (ngenE == 0 && ngenMu == 0) genHadEvents += 1;
     else if (ngenE == 1 && ngenMu == 0) genSemiEEvents += 1;
     else if (ngenE == 0 && ngenMu == 1) genSemiMuEvents += 1;
     else if (ngenE == 1 && ngenMu == 1) genMuEEvents += 1;
     else if (ngenE == 2) genEEEvents += 1;
     else if (ngenMu == 2) genMuMuEvents += 1;
   }//MC requirement

   //pileup reweighting
   int NPV = 0;
   for(size_t ivtx=0; ivtx < h_pv_chi->size(); ivtx++){
     if(abs((*h_pv_z)[ivtx]) < 24. && (*h_pv_ndof)[ivtx] > 4 && abs((*h_pv_rho)[ivtx]) < 2.0) NPV += 1;
   }
   if(isMC_){
     evWeight *= hPU->GetBinContent(hPU->GetXaxis()->FindBin(NPV));
   }

   //flat sample and negative weights reweighting
   if(isMC_ && (negativeWeights_ || isFlat_) && h_genEventInfo.isValid()){
     double pthat = 0.0;
     if(isFlat_){
       pthat    = (h_genEventInfo->hasBinningValues() ? (h_genEventInfo->binningValues())[0] : 0.0);
       evWeight *= 1/pow(pthat/15.,4.5);
     }//deweighting flat MC
     if(negativeWeights_){
       double iweight = h_genEventInfo->weight();
       if(iweight < 0){
	 evWeight *= -1.0;
	 Nevents_weighted -= 1;
       }
       else Nevents_weighted += 1;
     }//negative weights
   }//flat sample and negative weights

   //rho value
   double rho = -999.99;
   if(h_rho.isValid()) rho = (*h_rho);

   //muon selection
   vector<double> goodmuonPt;
   vector<double> goodmuonEta;
   vector<double> goodmuonPhi;
   vector<double> goodmuonMass;
   vector<vector<int> > goodmuonKey;
   vector<double> goodmuonCharge;
   vector<double> goodmuonIso;

   //muon loop
   if(h_muPt->size() > 0){
     for(size_t imuon = 0; imuon < h_muPt->size(); imuon++){
       NMu = NMu + 1;
       if((*h_muPt)[imuon] > 50.) NPassMuonPtCut = NPassMuonPtCut + 1;
       if(abs((*h_muEta)[imuon]) < 2.1) NPassMuonEtaCut = NPassMuonEtaCut;
       if((*h_muDz)[imuon] < 5.0) NPassMuonDzCut = NPassMuonDzCut + 1;
       if((*h_muLoose)[imuon] !=0) NPassMuonTightCut = NPassMuonTightCut + 1;
       if ((*h_muPt)[imuon] > 50. && abs((*h_muEta)[imuon]) < 2.1 && (*h_muDz)[imuon] < 5.0 && (*h_muLoose)[imuon] !=0){
	 NPassMuonTot += 1;
	 goodmuonPt.push_back((*h_muPt)[imuon]);
	 goodmuonEta.push_back((*h_muEta)[imuon]);
	 goodmuonPhi.push_back((*h_muPhi)[imuon]);
	 goodmuonMass.push_back((*h_muMass)[imuon]);
	 goodmuonKey.push_back((*h_muKey)[imuon]);
	 goodmuonCharge.push_back((*h_muCharge)[imuon]);
	 goodmuonIso.push_back((*h_muIso04)[imuon]);
       }
     }
   }

   //electron selection
   vector<double> goodelectronPt;
   vector<double> goodelectronEta;
   vector<double> goodelectronPhi;
   vector<double> goodelectronMass;
   vector<vector<int> > goodelectronKey;
   vector<double> goodelectronCharge;
   vector<double> goodelectronIso;
   bool goodElectron = 0;

   //electron loop
   if(h_elPt->size() > 0){
     for(size_t ielectron = 0; ielectron < h_elPt->size(); ielectron++){
       NEl = NEl + 1;
       if((*h_elPt)[ielectron] > 50.) NPassElPtCut += 1;
       if(abs((*h_elEta)[ielectron]) < 2.5) NPassElEtaCut += 1;

	//electron ID cut (current WP Loose : https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2 )
       if(abs((*h_elEta)[ielectron]) <= 1.479){
	 if(abs((*h_eldEtaIn)[ielectron]) < 0.00976) NPassEldEtaIn+=1;
	 if(abs((*h_eldPhiIn)[ielectron]) < 0.0929) NPassEldPhiIn+=1;
	 if((*h_elfull5x5siee)[ielectron] < 0.0105) NPassEl5x5+= 1;
	 if((*h_elHoE)[ielectron] <  0.0765)  NPassElHoE+= 1;
	 if(abs((*h_elD0)[ielectron]) < 0.0227) NPassElD0+=1;
	 if(abs((*h_elDz)[ielectron])  <  0.379) NPassElDz+=1;
	 if((*h_elooEmooP)[ielectron] <  0.184) NPassElEmooP+=1;
	 if((*h_elPt)[ielectron] > 50. && abs((*h_eldEtaIn)[ielectron]) < 0.00976 && abs((*h_eldPhiIn)[ielectron]) < 0.0929 && (*h_elfull5x5siee)[ielectron] < 0.0105 && (*h_elHoE)[ielectron] <  0.0765 && abs((*h_elD0)[ielectron]) < 0.0227 && abs((*h_elDz)[ielectron])  <  0.379 && (*h_elooEmooP)[ielectron] <  0.184) goodElectron = 1;
       }//barrel cuts
       else if(abs((*h_elEta)[ielectron]) < 2.5){
	 if(abs((*h_eldEtaIn)[ielectron]) < 0.00952) NPassEldEtaIn+=1;
	 if(abs((*h_eldPhiIn)[ielectron]) < 0.181) NPassEldPhiIn+=1;
	 if((*h_elfull5x5siee)[ielectron] < 0.0318) NPassEl5x5+= 1;
	 if((*h_elHoE)[ielectron] <  0.0824)  NPassElHoE+= 1;
	 if(abs((*h_elD0)[ielectron]) < 0.242) NPassElD0+=1;
	 if(abs((*h_elDz)[ielectron])  <  0.921) NPassElDz+=1;
	 if((*h_elooEmooP)[ielectron] <  0.125) NPassElEmooP+=1;
	 if((*h_elPt)[ielectron] > 50. && abs((*h_eldEtaIn)[ielectron]) < 0.00952 && abs((*h_eldPhiIn)[ielectron]) < 0.181 && (*h_elfull5x5siee)[ielectron] < 0.0318 && (*h_elHoE)[ielectron] <  0.0824 && abs((*h_elD0)[ielectron]) < 0.242 && abs((*h_elDz)[ielectron])  <  0.921 && (*h_elooEmooP)[ielectron] <  0.125) goodElectron = 1;
       }//endcap cuts
       if (goodElectron){
	 NPassGoodElCut += 1;
	 NPassElKeyCut+=1;
	 goodelectronPt.push_back((*h_elPt)[ielectron]);
	 goodelectronEta.push_back((*h_elEta)[ielectron]);
	 goodelectronPhi.push_back((*h_elPhi)[ielectron]);
	 goodelectronMass.push_back((*h_elMass)[ielectron]);
	 goodelectronKey.push_back((*h_elKey)[ielectron]);
	 goodelectronCharge.push_back((*h_elCharge)[ielectron]);
	 goodelectronIso.push_back((*h_elIso03)[ielectron]);
       }
     }
   }

   //channel definitions
   bool hadronic = 0;
   bool leptonic = 0;
   bool semileptonic = 0;

   if((goodmuonPt.size() + goodelectronPt.size()) == 0) hadronic = 1;
   if((goodmuonPt.size() + goodelectronPt.size()) == 2) leptonic = 1;
   if((goodmuonPt.size() + goodelectronPt.size()) == 1) semileptonic = 1;

   hadTreeVars["leptSelectionPass"] = leptonic;
   hadTreeVars["semileptSelectionPass"] = semileptonic;
   hadTreeVars["hadSelectionPass"] = hadronic;

   /*semileptTreeVars["leptSelectionPass"] = leptonic;
   semileptTreeVars["semileptSelectionPass"] = semileptonic;
   semileptTreeVars["hadSelectionPass"] = hadronic;*/

   //cutflow
   if(leptonic){
     NeventsDiLeptonic  +=1;
   }
   if(semileptonic){
     NeventsSemiLeptonic  +=1;
     if(goodmuonPt.size() == 1) NeventsSemiLeptonicMuon +=1;
     if(goodelectronPt.size() == 1) NeventsSemiLeptonicElectron +=1;
   }
   if(hadronic)  NeventsAllHadronic  +=1;   
   
   //Number of Primary Vertices
   //hadTreeVars["npv"] = *h_npv;
   //semileptTreeVars["npv"] = *h_npv;


   //AK8 Jet Vectors
   vector<double> ak8JetsGood;
   vector<double> ak8JetsGoodCorrUp  ;
   vector<double> ak8JetsGoodCorrDn  ;
   vector<double> ak8JetsGoodTrimMass;
   vector<double> ak8JetsGoodPrunMass;
   vector<double> ak8JetsGoodFiltMass;
   vector<double> ak8JetsGoodSDropMass;
   vector<double> ak8JetsGoodTau1;
   vector<double> ak8JetsGoodTau2;
   vector<double> ak8JetsGoodTau3;
   vector<double> ak8JetsGoodNHadE;
   vector<double> ak8JetsGoodNSubJets;
   vector<double> ak8JetsGoodMinMass;
   vector<double> ak8JetsGoodTopSubjetbDisc;
   vector<double> ak8JetsGoodTopSubjetMass;
   vector<double> ak8JetsGoodNHF;
   vector<double> ak8JetsGoodCHF;
   vector<double> ak8JetsGoodNEF;
   vector<double> ak8JetsGoodCEF;
   vector<double> ak8JetsGoodNC ;
   vector<double> ak8JetsGoodNCH;
   vector<double> ak8JetsGoodCSV;
   vector<double> ak8JetsGoodCMSTTsubjetIndex0;
   vector<double> ak8JetsGoodCMSTTsubjetIndex1;
   vector<double> ak8JetsGoodCMSTTsubjetIndex2;
   vector<double> ak8JetsGoodCMSTTsubjetIndex3;            
   vector<double> ak8JetsGoodSDsubjetIndex0;            
   vector<double> ak8JetsGoodSDsubjetIndex1;   
   vector<double> ak8JetsGoodSDsubjet0Mass;            
   vector<double> ak8JetsGoodSDsubjet1Mass; 
   vector<double> ak8JetsGoodSDsubjet0Bdisc;            
   vector<double> ak8JetsGoodSDsubjet1Bdisc;    
   vector<double> ak8JetsGoodSDsubjet0Pt;            
   vector<double> ak8JetsGoodSDsubjet1Pt; 
   vector<double> ak8JetsGoodSDsubjet0P4;            
   vector<double> ak8JetsGoodSDsubjet1P4;      
   vector<double> ak8JetsGoodL1cor;            
   vector<double> ak8JetsGoodL2cor;            
   vector<double> ak8JetsGoodL3cor;
   vector<double> ak8JetsDPhiLepJet;
   vector<double> ak8JetsGoodCorrFactor;
   vector<double> ak8JetsGoodCorrUpFactor;
   vector<double> ak8JetsGoodCorrDnFactor;

   vector<double> AK8TrimmedM;
   vector<double> AK8PrunedM;
   vector<double> AK8FilteredM;
   vector<double> AK8SDropM;
   
   vector<double> CMSTTsubjetBDisc       ;  
   vector<double> CMSTTsubjetPtRaw       ;
   vector<double> CMSTTsubjetPt          ;
   vector<double> CMSTTsubjetEta         ;  
   vector<double> CMSTTsubjetPhi         ;  
   vector<double> CMSTTsubjetMassRaw     ;
   vector<double> CMSTTsubjetMass        ;
   vector<double> CMSTTsubjetArea        ;  
   vector<double> CMSTTsubjetnumDaughters;  
   vector<double> CMSTTsubjetY           ;  
   vector<double> CMSTTsubjetJEC0        ;  
   vector<double> CMSTTsubjetJERup       ;  
   vector<double> CMSTTsubjetJERdown     ;  
   vector<double> CMSTTsubjetSmearedE    ;  
   vector<double> CMSTTsubjetSmearedEta  ;  
   vector<double> CMSTTsubjetSmearedPhi  ; 
     
   vector<double> SDsubjetBDisc        ;
   vector<double> SDsubjetPt           ;
   vector<double> SDsubjetEta          ;
   vector<double> SDsubjetPhi          ;
   vector<double> SDsubjetMass         ;
   vector<double> SDsubjetArea         ;
   vector<double> SDsubjetnumDaughters ;
   vector<double> SDsubjetY            ;
   vector<double> SDsubjetJEC0         ;
   vector<double> SDsubjetJERup        ;
   vector<double> SDsubjetJERdown      ;
   vector<double> SDsubjetSmearedE     ;
   vector<double> SDsubjetSmearedEta   ;
   vector<double> SDsubjetSmearedPhi   ;
   vector<double> SDsubjetSmearedPt    ;
	
   double ak8JetHt = 0;


   //AK8 Jet Loop
   if (h_jetsAK8Pt.isValid()){//make sure there are AK8 jets
     if(h_subjetsCmsTopTagCSV->size() > 0){
       for(size_t isubjet=0; isubjet < h_subjetsCmsTopTagPt->size(); isubjet++){
	 double spt  = ((*h_subjetsCmsTopTagJEC0)[isubjet])*((*h_subjetsCmsTopTagPt)[isubjet]);
	 double seta = (*h_subjetsCmsTopTagEta)[isubjet];
	 double sphi = (*h_subjetsCmsTopTagPhi)[isubjet];
	 double smass = ((*h_subjetsCmsTopTagJEC0)[isubjet])*((*h_subjetsCmsTopTagMass)[isubjet]);
	 TLorentzVector subjetP4Raw;
	 subjetP4Raw.SetPtEtaPhiM( spt, seta, sphi, smass);
	 ak4JetCorrectorForMass->setJetEta( subjetP4Raw.Eta() );
	 ak4JetCorrectorForMass->setJetPt ( subjetP4Raw.Perp() );
	 ak4JetCorrectorForMass->setJetE  ( subjetP4Raw.E() );
	 ak4JetCorrectorForMass->setRho   ( rho );
	 ak4JetCorrectorForMass->setNPV   ( NPV );
	 double newJEC = ak4JetCorrectorForMass->getCorrection();
	 TLorentzVector subjetP4 = subjetP4Raw * newJEC;
	 CMSTTsubjetPt.push_back( subjetP4.Perp() );
	 CMSTTsubjetMass.push_back( subjetP4.M() );
       }
     }//applying CMSTT subjet corrections

     if(h_subjetsSoftDropCSV->size() > 0){
       for(size_t isubjet=0; isubjet < h_subjetsSoftDropPt->size(); isubjet++){
	 double spt  = ((*h_subjetsSoftDropJEC0)[isubjet])*((*h_subjetsSoftDropPt)[isubjet]);
	 double seta = (*h_subjetsSoftDropEta)[isubjet];
	 double sphi = (*h_subjetsSoftDropPhi)[isubjet];
	 double smass = ((*h_subjetsSoftDropJEC0)[isubjet])*((*h_subjetsSoftDropMass)[isubjet]);
	 TLorentzVector subjetP4Raw;
	 subjetP4Raw.SetPtEtaPhiM( spt, seta, sphi, smass);
	 ak4JetCorrectorForMass->setJetEta( subjetP4Raw.Eta() );
	 ak4JetCorrectorForMass->setJetPt ( subjetP4Raw.Perp() );
	 ak4JetCorrectorForMass->setJetE  ( subjetP4Raw.E() );
	 ak4JetCorrectorForMass->setRho   ( rho );
	 ak4JetCorrectorForMass->setNPV   ( NPV );
	 double newJEC = ak4JetCorrectorForMass->getCorrection();
	 TLorentzVector subjetP4 = subjetP4Raw * newJEC;
	 SDsubjetPt.push_back( subjetP4.Perp() );
	 SDsubjetMass.push_back( subjetP4.M() );
       }
     }//applying SoftDrop subjet corrections
    
     for (unsigned i=0; i<h_jetsAK8Pt->size(); i++){//looping over AK8 jets
       //JEC
       double AK8JECFromB2GAnaFW = (*h_jetsAK8JEC)[i];
       TLorentzVector AK8P4Raw;
       AK8P4Raw.SetPtEtaPhiM( (*h_jetsAK8Pt)[i] , (*h_jetsAK8Eta)[i], (*h_jetsAK8Phi)[i], (*h_jetsAK8ungroomedMass)[i]);
       AK8P4Raw *= AK8JECFromB2GAnaFW;

       //Charged and neutral energy for AK8 jets
       double nhf = (*h_jetsAK8nHadEnergy)[i] / AK8P4Raw.E();
       double nef = (*h_jetsAK8nEMEnergy)[i] / AK8P4Raw.E();
       double chf = (*h_jetsAK8cHadEnergy)[i] / AK8P4Raw.E();
       double cef = (*h_jetsAK8cEMEnergy)[i] / AK8P4Raw.E();
       double nconstituents = (*h_jetsAK8numDaughters)[i];
       double nch = (*h_jetsAK8cMultip)[i];
       bool goodJet = 0;
       if(nhf < 0.99 && nef < 0.99 && chf > 0.00 && cef < 0.99 && nconstituents > 1 && nch > 0) goodJet = 1;
       
       //JEC scaling
       double corrDn = 1.0;
       double corrUp = 1.0;

       ak8JetCorrector->setJetEta( AK8P4Raw.Eta() );
       ak8JetCorrector->setJetPt ( AK8P4Raw.Perp() );
       ak8JetCorrector->setJetE  ( AK8P4Raw.E() );
       ak8JetCorrector->setJetA  ( (*h_jetsAK8Area)[i] );
       ak8JetCorrector->setRho   ( rho );
       ak8JetCorrector->setNPV   ( NPV );
       double newJEC = ak8JetCorrector->getCorrection();
       TLorentzVector AK8P4Corr = AK8P4Raw*newJEC;

       //JEC Uncertainty 
       corrDn *= newJEC;
       corrUp *= newJEC;

       UncertJetAK8->setJetPhi(  AK8P4Raw.Phi()  );
       UncertJetAK8->setJetEta(  AK8P4Raw.Eta()  );
       UncertJetAK8->setJetPt(   AK8P4Corr.Perp()  );
       corrDn -= UncertJetAK8->getUncertainty(0);
       UncertJetAK8->setJetPhi(  AK8P4Raw.Phi()  );
       UncertJetAK8->setJetEta(  AK8P4Raw.Eta()  );
       UncertJetAK8->setJetPt(   AK8P4Corr.Perp()  );
       corrUp += UncertJetAK8->getUncertainty(1);
	 
       //cout<<"JEC: "<<newJEC<<endl;
       // cout<<"JEC up: "<<corrUp<<endl;
       //cout<<"JEC down: "<<corrDn<<endl;

       //Raw Mass values
       float jetsAK8ungroomedMassRaw = AK8P4Raw.M();
       float jetsAK8topMassRaw = (*h_jetsAK8topMass)[i];
       float jetsAK8trimmedMassRaw = (*h_jetsAK8trimmedMass)[i];
       float jetsAK8prunedMassRaw = (*h_jetsAK8prunedMass)[i];
       float jetsAK8filteredMassRaw = (*h_jetsAK8filteredMass)[i];
       float jetsAK8softDropMassRaw = (*h_jetsAK8softDropMass)[i];

       //Mass values to be corrected
       float jetsAK8topMass = (*h_jetsAK8topMass)[i];
       float jetsAK8trimmedMass = (*h_jetsAK8trimmedMass)[i];
       float jetsAK8prunedMass = (*h_jetsAK8prunedMass)[i];
       float jetsAK8filteredMass = (*h_jetsAK8filteredMass)[i];
       float jetsAK8softDropMass = (*h_jetsAK8softDropMass)[i];
	 
       //no JEC applied
       if(JECshift_ == 0){
	 //cout<<"JEC shift = 0!"<<endl;
	 jetsAK8topMass *= newJEC;
	 jetsAK8trimmedMass *= newJEC;
	 jetsAK8prunedMass *= newJEC;
	 jetsAK8filteredMass *= newJEC;
	 jetsAK8softDropMass *= newJEC;
       }
       
       //JEC down
       if(JECshift_ == -1){
	 //cout<<"JEC shift = -1!"<<endl;
	 AK8P4Corr = AK8P4Raw*corrDn;
	 jetsAK8topMass *= corrDn;
	 jetsAK8trimmedMass *= corrDn;
	 jetsAK8prunedMass *= corrDn;
	 jetsAK8filteredMass *= corrDn;
	 jetsAK8softDropMass *= corrDn;
       }
       
       //JEC up
       if(JECshift_ == 1){
	 //cout<<"JEC shift = 1!"<<endl;
	 AK8P4Corr = AK8P4Raw*corrUp;
	 jetsAK8topMass *= corrUp;
	 jetsAK8trimmedMass *= corrUp;
	 jetsAK8prunedMass *= corrUp;
	 jetsAK8filteredMass *= corrUp;
	 jetsAK8softDropMass *= corrUp;
       }

       //saving L1, L2, and L3 corrections separately
       ak8JetCorrector->setJetEta( AK8P4Raw.Eta() );
       ak8JetCorrector->setJetPt ( AK8P4Raw.Perp() );
       ak8JetCorrector->setJetE  ( AK8P4Raw.E() );
       ak8JetCorrector->setJetA  ( (*h_jetsAK8Area)[i] );
       ak8JetCorrector->setRho   ( rho );
       ak8JetCorrector->setNPV   ( NPV );
       vector<float> factors = ak8JetCorrector->getSubCorrections();
       float L1cor = 1.0;
       float L2cor = 1.0;
       float L3cor = 1.0;
       if (factors.size() > 0) L1cor = factors[0];
       if (factors.size() > 1) L2cor = factors[1];
       if (factors.size() > 2) L3cor = factors[2];

       hadTreeVars["L1cor"] = L1cor;
       hadTreeVars["L2cor"] = L2cor;
       hadTreeVars["L3cor"] = L3cor;

       //JER and JAR
       float ptsmear   = 1.0;
       float ptsmearUp = 1.0;
       float ptsmearDn = 1.0;
       float etascale  = 1.0;
       float phiscale  = 1.0;

       if(isMC_){
	 //JER
	 float smear     = getJER( AK8P4Corr.Eta(),  0);
	 float smearUp   = getJER( AK8P4Corr.Eta(),  1);
	 float smearDn   = getJER( AK8P4Corr.Eta(), -1); 
	 float recopt    = AK8P4Corr.Pt();
	 float genpt     = (*h_jetsAK8GenJetPt)[i];
	 float deltapt   = (recopt-genpt)*(smear-1.0);
	 float deltaptUp = (recopt-genpt)*(smearUp-1.0);
	 float deltaptDn = (recopt-genpt)*(smearDn-1.0);
	 ptsmear   = max((float)0.0, (recopt+deltapt)/recopt);
	 ptsmearUp = max((float)0.0, (recopt+deltaptUp)/recopt);
	 ptsmearDn = max((float)0.0, (recopt+deltaptDn)/recopt);

	 //no JER applied
	 if(JERshift_ == 0){
	   //cout<<"JER shift = 0!"<<endl;
	   AK8P4Corr   = AK8P4Corr*ptsmear;
	   jetsAK8topMass *= ptsmear;
	   jetsAK8trimmedMass *= ptsmear;
	   jetsAK8prunedMass *= ptsmear;
	   jetsAK8filteredMass *= ptsmear;
	   jetsAK8softDropMass *= ptsmear;
	 }
       
	 //JER down
	 if(JERshift_ == -1){
	   //cout<<"JER shift = -1!"<<endl;
	   AK8P4Corr = AK8P4Corr*ptsmearDn;
	   jetsAK8topMass *= ptsmearDn;
	   jetsAK8trimmedMass *= ptsmearDn;
	   jetsAK8prunedMass *= ptsmearDn;
	   jetsAK8filteredMass *= ptsmearDn;
	   jetsAK8softDropMass *= ptsmearDn;
	 }
	 
	 //JER up
	 if(JERshift_ == 1){
	   //cout<<"JER shift = 1!"<<endl;
	   AK8P4Corr = AK8P4Corr*ptsmearUp;
	   jetsAK8topMass *= ptsmearUp;
	   jetsAK8trimmedMass *= ptsmearUp;
	   jetsAK8prunedMass *= ptsmearUp;
	   jetsAK8filteredMass *= ptsmearUp;
	   jetsAK8softDropMass *= ptsmearUp;
	 }

	 //JAR
	 float etasmearfactor = 0.1;
	 float recoeta = AK8P4Corr.Eta();
	 float geneta  = (*h_jetsAK8GenJetEta)[i];
	 float deltaeta = (recoeta-geneta)*etasmearfactor ;
	 etascale = max((float)0.0, (recoeta+deltaeta)/recoeta  );

	 float phismearfactor = 0.1;
	 float recophi = AK8P4Corr.Phi();
	 float genphi  = (*h_jetsAK8GenJetPhi)[i];
	 float deltaphi = (recophi-genphi)*phismearfactor;
	 phiscale = max((float)0.0, (recophi+deltaphi)/recophi  );
       }
       
       //getting kinematic values
       float jetsAK8Pt = AK8P4Corr.Pt();
       float jetsAK8Eta = AK8P4Corr.Eta();
       float jetsAK8Phi = AK8P4Corr.Phi();
       float jetsAK8E = AK8P4Corr.E();
       float jetsAK8Y = AK8P4Corr.Rapidity();
       float jetsAK8ungroomedMass = AK8P4Corr.M();

       AK8TrimmedM.push_back(jetsAK8trimmedMass);
       AK8PrunedM.push_back(jetsAK8prunedMass);
       AK8FilteredM.push_back(jetsAK8filteredMass);
       AK8SDropM.push_back(jetsAK8softDropMass);

       if(!goodJet) continue;
       NPassGoodJetAK8Cut = NPassGoodJetAK8Cut + 1;

       //pt and eta preselection cuts
       if (jetsAK8Pt > 400 && abs(jetsAK8Eta) < 2.4){
	 //hadTreeVars["jet"+s+"AK8Pt"] = jetsAK8Pt;
	 //top tagging requirements
	 if (nAK8pt400eta2p4jets == 0){//first top tag jet candidate
	   hadTreeVars["topTagJet0_pt"] = jetsAK8Pt;
	   hadTreeVars["topTagJet0_eta"] = jetsAK8Eta;
	   hadTreeVars["topTagJet0_phi"] = jetsAK8Phi;
	   hadTreeVars["topTagJet0_E"] = jetsAK8E;
	   hadTreeVars["topTagJet0_Y"] = jetsAK8Y;
	   hadTreeVars["topTagJet0_minmass"] = (*h_jetsAK8minmass)[i];
	   hadTreeVars["topTagJet0_nSubJets"] = (*h_jetsAK8nSubJets)[i];
	   hadTreeVars["topTagJet0_tau1"] = (*h_jetsAK8tau1)[i];
	   hadTreeVars["topTagJet0_tau2"] = (*h_jetsAK8tau2)[i];
	   hadTreeVars["topTagJet0_tau3"] = (*h_jetsAK8tau3)[i];
	   hadTreeVars["topTagJet0_ungroomedMass"] = jetsAK8ungroomedMass;
	   hadTreeVars["topTagJet0_topMass"] = jetsAK8topMass;
	   hadTreeVars["topTagJet0_filteredMass"] = jetsAK8filteredMass;
	   hadTreeVars["topTagJet0_prunedMass"] = jetsAK8prunedMass;
	   hadTreeVars["topTagJet0_trimmedMass"] = jetsAK8trimmedMass;
	   hadTreeVars["topTagJet0_softDropMass"] = jetsAK8softDropMass;
	   hadTreeVars["topTagJet0_ungroomedMassRaw"] = jetsAK8ungroomedMassRaw;
	   hadTreeVars["topTagJet0_topMassRaw"] = jetsAK8topMassRaw;
	   hadTreeVars["topTagJet0_filteredMassRaw"] = jetsAK8filteredMassRaw;
	   hadTreeVars["topTagJet0_prunedMassRaw"] = jetsAK8prunedMassRaw;
	   hadTreeVars["topTagJet0_trimmedMassRaw"] = jetsAK8trimmedMassRaw;
	   hadTreeVars["topTagJet0_softDropMassRaw"] = jetsAK8softDropMassRaw;

	   //Lorentz vectors
	   softDropJet0.SetPtEtaPhiM(jetsAK8Pt,jetsAK8Eta,jetsAK8Phi,jetsAK8softDropMass);
	   ungroomedJet0.SetPtEtaPhiM(jetsAK8Pt,jetsAK8Eta,jetsAK8Phi,jetsAK8ungroomedMass);
	   
	   //////b-tagging
	   float nSubjets_jet0 = (*h_jetsAK8nSubJets)[i];

	   //vector of subjet CSV values
	   vector<float> subjet0cmsttCSVs;
	   vector<float> subjet0softDropCSVs;
	   if (nSubjets_jet0 > 0){
	     subjet0cmsttCSVs.push_back((*h_subjetsCmsTopTagCSV)[(*h_ak8jetTopSubjetIndex0)[i]]);
	     subjet0softDropCSVs.push_back((*h_subjetsSoftDropCSV)[(*h_ak8jetSoftDropSubjetIndex0)[i]]);
	   }
	   if (nSubjets_jet0 > 1){
	     subjet0cmsttCSVs.push_back((*h_subjetsCmsTopTagCSV)[(*h_ak8jetTopSubjetIndex1)[i]]);
	     subjet0softDropCSVs.push_back((*h_subjetsSoftDropCSV)[(*h_ak8jetSoftDropSubjetIndex1)[i]]);
	   }
	   if (nSubjets_jet0 > 2){
	     subjet0cmsttCSVs.push_back((*h_subjetsCmsTopTagCSV)[(*h_ak8jetTopSubjetIndex2)[i]]);
	   }
	   if (nSubjets_jet0 > 3){
	     subjet0cmsttCSVs.push_back((*h_subjetsCmsTopTagCSV)[(*h_ak8jetTopSubjetIndex3)[i]]);
	   }

	   //saving max cmstt subjet b-tag score for jet 0
	   float maxSubjet0cmsttCSV = -999.;
	   for (size_t j = 0; j < subjet0cmsttCSVs.size(); j++){
	     maxSubjet0cmsttCSV = max(maxSubjet0cmsttCSV, subjet0cmsttCSVs[j]);
	   }

	   //saving max soft drop subjet b-tag score for jet 0
	   float maxSubjet0softDropCSV = -999.;
	   for (size_t j = 0; j < subjet0softDropCSVs.size(); j++){
	     maxSubjet0softDropCSV = max(maxSubjet0softDropCSV, subjet0softDropCSVs[j]);
	   }

	   hadTreeVars["topTagJet0_maxCMSTTSubjetbtag"] = maxSubjet0cmsttCSV;
	   hadTreeVars["topTagJet0_maxSoftDropSubjetbtag"] = maxSubjet0softDropCSV;

	   //nsubjettiness
	   float nSubjettiness = ((*h_jetsAK8tau3)[i])/((*h_jetsAK8tau2)[i]);
	   hadTreeVars["topTagJet0_tau32"] = nSubjettiness;
	   
	   //top tagging with softdrop mass
	   if (jetsAK8softDropMass > 110.0 && jetsAK8softDropMass < 210.0){
	     topTagJet0_topTagFlag = 1;
	   }
	   
	   hadTreeVars["topTagJet0_topTagFlag"] = topTagJet0_topTagFlag;
	   
	   //incrementing counter for number of jets passing the Nsubjettiness cut
	   if (nSubjettiness < 0.61){
	     nNsubjettinessCutJets += 1;
	   }

	   //incrementing counter for number of jets passing the b-tag cut
	   if (maxSubjet0softDropCSV > 0.76){
	     nBtagJets += 1;
	   }

	   //flagging the jet as top tagged by the cmstt mass
	   /*if ((*h_jetsAK8topMass)[i] > 140.0 && (*h_jetsAK8topMass)[i] < 250.0){
	     topTagJet0_topTagFlag |= 1;
	     //toptagindexJet0_cmstt = i;
	     cmsttJet0.SetPtEtaPhiM((*h_jetsAK8Pt)[i],(*h_jetsAK8Eta)[i],(*h_jetsAK8Phi)[i],(*h_jetsAK8topMass)[i]);
	   } 

	   //flagging the jet as top tagged by the filtered mass
	   if ((*h_jetsAK8filteredMass)[i] > 140.0 && (*h_jetsAK8filteredMass)[i] < 250.0){
	     topTagJet0_topTagFlag |= 2;
	     //toptagindexJet0_filtered = i;
	     filteredJet0.SetPtEtaPhiM((*h_jetsAK8Pt)[i],(*h_jetsAK8Eta)[i],(*h_jetsAK8Phi)[i],(*h_jetsAK8topMass)[i]);
	   }

	   //flagging the jet as top tagged by the pruned mass
	   if ((*h_jetsAK8prunedMass)[i] > 140.0 && (*h_jetsAK8prunedMass)[i] < 250.0){
	     topTagJet0_topTagFlag |= 4;
	     //toptagindexJet0_pruned = i;
	     prunedJet0.SetPtEtaPhiM((*h_jetsAK8Pt)[i],(*h_jetsAK8Eta)[i],(*h_jetsAK8Phi)[i],(*h_jetsAK8topMass)[i]);
	   }
	   
	   //flagging the jet as top tagged by the trimmed mass
	   if ((*h_jetsAK8trimmedMass)[i] > 140.0 && (*h_jetsAK8trimmedMass)[i] < 250.0){
	     topTagJet0_topTagFlag |= 8;
	     //toptagindexJet0_trimmed = i;
	     trimmedJet0.SetPtEtaPhiM((*h_jetsAK8Pt)[i],(*h_jetsAK8Eta)[i],(*h_jetsAK8Phi)[i],(*h_jetsAK8topMass)[i]);
	     }*/
	 }//end AK8 jet 0 loop
	 else if (nAK8pt400eta2p4jets == 1){//second top tag jet candidate
	   hadTreeVars["topTagJet1_pt"] = jetsAK8Pt;
	   hadTreeVars["topTagJet1_eta"] = jetsAK8Eta;
	   hadTreeVars["topTagJet1_phi"] = jetsAK8Phi;
	   hadTreeVars["topTagJet1_E"] = jetsAK8E;
	   hadTreeVars["topTagJet1_Y"] = jetsAK8Y;
	   hadTreeVars["topTagJet1_minmass"] = (*h_jetsAK8minmass)[i];
	   hadTreeVars["topTagJet1_nSubJets"] = (*h_jetsAK8nSubJets)[i];
	   hadTreeVars["topTagJet1_tau1"] = (*h_jetsAK8tau1)[i];
	   hadTreeVars["topTagJet1_tau2"] = (*h_jetsAK8tau2)[i];
	   hadTreeVars["topTagJet1_tau3"] = (*h_jetsAK8tau3)[i];
	   hadTreeVars["topTagJet1_ungroomedMass"] = jetsAK8ungroomedMass;
	   hadTreeVars["topTagJet1_topMass"] = jetsAK8topMass;
	   hadTreeVars["topTagJet1_filteredMass"] = jetsAK8filteredMass;
	   hadTreeVars["topTagJet1_prunedMass"] = jetsAK8prunedMass;
	   hadTreeVars["topTagJet1_trimmedMass"] = jetsAK8trimmedMass;
	   hadTreeVars["topTagJet1_softDropMass"] = jetsAK8softDropMass;
	   hadTreeVars["topTagJet1_ungroomedMassRaw"] = jetsAK8ungroomedMassRaw;
	   hadTreeVars["topTagJet1_topMassRaw"] = jetsAK8topMassRaw;
	   hadTreeVars["topTagJet1_filteredMassRaw"] = jetsAK8filteredMassRaw;
	   hadTreeVars["topTagJet1_prunedMassRaw"] = jetsAK8prunedMassRaw;
	   hadTreeVars["topTagJet1_trimmedMassRaw"] = jetsAK8trimmedMassRaw;
	   hadTreeVars["topTagJet1_softDropMassRaw"] = jetsAK8softDropMassRaw;

	   //Lorentz vectors
	   softDropJet1.SetPtEtaPhiM(jetsAK8Pt,jetsAK8Eta,jetsAK8Phi,jetsAK8softDropMass);
	   ungroomedJet1.SetPtEtaPhiM(jetsAK8Pt,jetsAK8Eta,jetsAK8Phi,jetsAK8ungroomedMass);
	   
	   //////b-tagging
	   float nSubjets_jet1 = (*h_jetsAK8nSubJets)[i];

	   //vector of subjet CSV values
	   vector<float> subjet1cmsttCSVs;
	   vector<float> subjet1softDropCSVs;
	   if (nSubjets_jet1 > 0){
	     subjet1cmsttCSVs.push_back((*h_subjetsCmsTopTagCSV)[(*h_ak8jetTopSubjetIndex0)[i]]);
	     subjet1softDropCSVs.push_back((*h_subjetsSoftDropCSV)[(*h_ak8jetSoftDropSubjetIndex0)[i]]);
	   }
	   if (nSubjets_jet1 > 1){
	     subjet1cmsttCSVs.push_back((*h_subjetsCmsTopTagCSV)[(*h_ak8jetTopSubjetIndex1)[i]]);
	     subjet1softDropCSVs.push_back((*h_subjetsSoftDropCSV)[(*h_ak8jetSoftDropSubjetIndex1)[i]]);
	   }
	   if (nSubjets_jet1 > 2){
	     subjet1cmsttCSVs.push_back((*h_subjetsCmsTopTagCSV)[(*h_ak8jetTopSubjetIndex2)[i]]);
	   }
	   if (nSubjets_jet1 > 3){
	     subjet1cmsttCSVs.push_back((*h_subjetsCmsTopTagCSV)[(*h_ak8jetTopSubjetIndex3)[i]]);
	   }

	   //saving max cmstt subjet b-tag score for jet 1
	   float maxSubjet1cmsttCSV = -999.;
	   for (size_t j = 0; j < subjet1cmsttCSVs.size(); j++){
	     maxSubjet1cmsttCSV = max(maxSubjet1cmsttCSV, subjet1cmsttCSVs[j]);
	   }

	   //saving max soft drop subjet b-tag score for jet 1
	   float maxSubjet1softDropCSV = -999.;
	   for (size_t j = 0; j < subjet1softDropCSVs.size(); j++){
	     maxSubjet1softDropCSV = max(maxSubjet1softDropCSV, subjet1softDropCSVs[j]);
	   }

	   hadTreeVars["topTagJet1_maxCMSTTSubjetbtag"] = maxSubjet1cmsttCSV;
	   hadTreeVars["topTagJet1_maxSoftDropSubjetbtag"] = maxSubjet1softDropCSV;

	   //nsubjettiness
	   float nSubjettiness = ((*h_jetsAK8tau3)[i])/((*h_jetsAK8tau2)[i]);
	   hadTreeVars["topTagJet1_tau32"] = nSubjettiness;

	   //top tagging with softdrop mass
	   if (jetsAK8softDropMass > 110.0 && jetsAK8softDropMass < 210.0){
	     topTagJet1_topTagFlag = 1;
	   }
	   
	   hadTreeVars["topTagJet1_topTagFlag"] = topTagJet1_topTagFlag;

	   //incrementing counter for number of jets passing the Nsubjettiness cut
	   if (nSubjettiness < 0.61){
	     nNsubjettinessCutJets += 1;
	   }

	   //incrementing counter for number of jets passing the b-tag cut
	   if (maxSubjet1softDropCSV > 0.76){
	     nBtagJets += 1;
	   }

	   //flagging the jet as top tagged by the cmstt top mass
	   /*if ((*h_jetsAK8topMass)[i] > 140.0 && (*h_jetsAK8topMass)[i] < 250.0){
	     topTagJet1_topTagFlag |= 1;
	     //toptagindexJet1_cmstt = i;
	     cmsttJet1.SetPtEtaPhiM((*h_jetsAK8Pt)[i],(*h_jetsAK8Eta)[i],(*h_jetsAK8Phi)[i],(*h_jetsAK8topMass)[i]);
	   } 
	   
	   //flagging the jet as top tagged by the filtered mass
	   if ((*h_jetsAK8filteredMass)[i] > 140.0 && (*h_jetsAK8filteredMass)[i] < 250.0){
	     topTagJet1_topTagFlag |= 2;
	     //toptagindexJet1_filtered = i;
	     filteredJet1.SetPtEtaPhiM((*h_jetsAK8Pt)[i],(*h_jetsAK8Eta)[i],(*h_jetsAK8Phi)[i],(*h_jetsAK8topMass)[i]);
	   }

	   //flagging the jet as top tagged by the pruned mass
	   if ((*h_jetsAK8prunedMass)[i] > 140.0 && (*h_jetsAK8prunedMass)[i] < 250.0){
	     topTagJet1_topTagFlag |= 4;
	     //toptagindexJet1_pruned = i;
	     prunedJet1.SetPtEtaPhiM((*h_jetsAK8Pt)[i],(*h_jetsAK8Eta)[i],(*h_jetsAK8Phi)[i],(*h_jetsAK8topMass)[i]);
	   }
	   
	   //flagging the jet as top tagged by the trimmed mass
	   if ((*h_jetsAK8trimmedMass)[i] > 140.0 && (*h_jetsAK8trimmedMass)[i] < 250.0){
	     topTagJet1_topTagFlag |= 8;
	     //toptagindexJet1_trimmed = i;
	     trimmedJet1.SetPtEtaPhiM((*h_jetsAK8Pt)[i],(*h_jetsAK8Eta)[i],(*h_jetsAK8Phi)[i],(*h_jetsAK8topMass)[i]);
	     }*/
	 }//end AK8 jet 1 loop
	 nAK8pt400eta2p4jets +=1;//top tagging candidate iterator
       }//pt and eta preselection cuts
     }//end AK8 jet loop
   }//checking AK8 jet validity

   hadTreeVars["nAK8pt400eta2p4jets"] = nAK8pt400eta2p4jets;

   //only filling tree if the event passes the filters
   if ((cscFilt == 1) && (vertexFilt == 1) && (hbheFilt == 1)){

     //cout <<"Filters passed!"<<endl;

     //filling out the cutflow values
     hadTreeVars["cutflow"] = 0.0;
     tree_had->Fill();
     
     if (nAK8pt400eta2p4jets > 0){
       hadTreeVars["cutflow"] = 1.0;//1 AK8 jet that passes preselection
       tree_had->Fill();
       if (nAK8pt400eta2p4jets > 1){
	 hadTreeVars["cutflow"] = 2.0;//2 AK8 jets that pass preselection
	 //Reconstructing the Z-peak with 2 good AK8 jets
	 TLorentzVector softDrop_Z = softDropJet0 + softDropJet1;
	 hadTreeVars["softDrop_Z_mass"] = softDrop_Z.M();
	 TLorentzVector ungroomed_Z = ungroomedJet0 + ungroomedJet1;
	 hadTreeVars["ungroomed_Z_mass"] = ungroomed_Z.M();
	 float ungroomedDeltaPhi = ungroomedJet0.DeltaPhi(ungroomedJet1);
	 hadTreeVars["ungroomedDeltaPhi"] = ungroomedDeltaPhi;
	 float ungroomedDeltaRapidity =  fabs(ungroomedJet0.Rapidity() - ungroomedJet1.Rapidity());
	 hadTreeVars["ungroomedDeltaRapidity"] = ungroomedDeltaRapidity;
	 tree_had->Fill();
       }//2+ good AK8 jets
       if ((topTagJet0_topTagFlag == 1) || (topTagJet1_topTagFlag == 1)){
	 hadTreeVars["cutflow"] = 3.0;//1 good AK8 jet in mass window
	 tree_had->Fill();
	 if((topTagJet0_topTagFlag == 1) && (topTagJet1_topTagFlag == 1)){
	   hadTreeVars["cutflow"] = 4.0;//2 good AK8 jets in mass window
	   tree_had->Fill();
	   if(nNsubjettinessCutJets > 1){
	     hadTreeVars["cutflow"] = 5.0;//2 good AK8 jets in mass window and 2 good jets passing Nsubjettiness cut
	     tree_had->Fill();
	     if(nBtagJets > 0){
	       hadTreeVars["cutflow"] = 6.0;//2 good AK8 jets in mass window, 2 good jet passing Nsubjettiness cut, and 1 good b-tagged jets
	       tree_had->Fill();
	     }//1+ b-tag jet
	     if(nBtagJets > 1){
	       hadTreeVars["cutflow"] = 7.0;//2 good AK8 jets in mass window, 2 good jet passing Nsubjettiness cut, and 2 good b-tagged jets
	       tree_had->Fill();
	     }//1+ b-tag jet
	   }//2 jets passing Nsubjettiness cut
	 }//2 jets in mass window
       }//1+ jet in mass window
     }//1+ good AK8 jets

     //cout<<"cutflow end"<<endl;

     //2 cmstt top tag jets
     /*if(((topTagJet0_topTagFlag & 1) == 1) && ((topTagJet1_topTagFlag & 1) == 1)){
       TLorentzVector cmstt_Z = cmsttJet0 + cmsttJet1;
       hadTreeVars["cmstt_Z_mass"] = cmstt_Z.M();
       }
   //2 filtered top tag jets
   if(((topTagJet0_topTagFlag & 2) == 2) && ((topTagJet1_topTagFlag & 2) == 2)){
     TLorentzVector filtered_Z = filteredJet0 + filteredJet1;
     hadTreeVars["filtered_Z_mass"] = filtered_Z.M();
											       }
   //2 pruned top tag jets
   if(((topTagJet0_topTagFlag & 4) == 4) && ((topTagJet1_topTagFlag & 4) == 4)){
     TLorentzVector pruned_Z = prunedJet0 + prunedJet1;
     hadTreeVars["pruned_Z_mass"] = pruned_Z.M();
											       }
   //2 trimmed top tag jets
   if(((topTagJet0_topTagFlag & 8) == 8) && ((topTagJet1_topTagFlag & 8) == 8)){
     TLorentzVector trimmed_Z = trimmedJet0 + trimmedJet1;
     hadTreeVars["trimmed_Z_mass"] = trimmed_Z.M();
     }*/

   /////Number of b-tags per event
   //if (topTagJet0_topTagFlag > 0 || topTagJet1_topTagFlag > 0){
     
   //}


   //cout<<"Number of top tagged jets: "<<nTopTagJets<<endl;
   //cout<<"Number of AK8 jets with pt > 400 GeV: "<<nAK8pt400eta2p4jets<<endl;
   }
}


// ------------ method called once each job just before starting event loop  ------------
void 
ZprimeB2Ganalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
ZprimeB2Ganalyzer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
/*
void 
ZprimeB2Ganalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
ZprimeB2Ganalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
ZprimeB2Ganalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
ZprimeB2Ganalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
ZprimeB2Ganalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(ZprimeB2Ganalyzer);
