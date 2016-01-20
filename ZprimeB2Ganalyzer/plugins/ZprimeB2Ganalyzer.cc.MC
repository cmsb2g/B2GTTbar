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

#include <TTree.h>
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

  TTree *tree;

  std::map<std::string, float> treeVars;
  std::vector<std::string> listOfVars;
  
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
ZprimeB2Ganalyzer::ZprimeB2Ganalyzer(const edm::ParameterSet& iConfig)
  //jetAK8PtSrc_(consumes<edm::View<vector<float>> >(iConfig.getParameter<edm::InputTag>("jetAK8PtSrc"))),
  //jetAK8GenPtSrc_(consumes<edm::View<vector<float>> >(iConfig.getParameter<edm::InputTag>("jetAK8GenPtSrc")))
{
   //now do what ever initialization is needed
  edm::Service<TFileService> fs;
  tree = fs->make<TTree>("tree","tree");

  listOfVars.push_back("npv");
  listOfVars.push_back("evWeight_corr");
  listOfVars.push_back("nAK8pt400eta2p4jets");
  //listOfVars.push_back("nTopTagJets");
  listOfVars.push_back("cutflow");
  listOfVars.push_back("topTagJet1_topTagFlag");
  listOfVars.push_back("topTagJet2_topTagFlag");

  listOfVars.push_back("topTagJet1_pt");
  listOfVars.push_back("topTagJet1_eta");
  listOfVars.push_back("topTagJet1_phi");
  listOfVars.push_back("topTagJet1_E");
  listOfVars.push_back("topTagJet1_Y");
  listOfVars.push_back("topTagJet1_minmass");
  listOfVars.push_back("topTagJet1_nSubJets");
  listOfVars.push_back("topTagJet1_tau1");
  listOfVars.push_back("topTagJet1_tau2");
  listOfVars.push_back("topTagJet1_tau3");
  listOfVars.push_back("topTagJet1_subjetCSV");
  listOfVars.push_back("topTagJet1_nSubjettiness");
  listOfVars.push_back("topTagJet1_topMass");
  listOfVars.push_back("topTagJet1_filteredMass");
  listOfVars.push_back("topTagJet1_prunedMass");
  listOfVars.push_back("topTagJet1_trimmedMass");
  listOfVars.push_back("topTagJet1_softDropMass");

  listOfVars.push_back("topTagJet2_pt");
  listOfVars.push_back("topTagJet2_eta");
  listOfVars.push_back("topTagJet2_phi");
  listOfVars.push_back("topTagJet2_E");
  listOfVars.push_back("topTagJet2_Y");
  listOfVars.push_back("topTagJet2_minmass");
  listOfVars.push_back("topTagJet2_nSubJets");
  listOfVars.push_back("topTagJet2_tau1");
  listOfVars.push_back("topTagJet2_tau2");
  listOfVars.push_back("topTagJet2_tau3");
  listOfVars.push_back("topTagJet2_subjetCSV");
  listOfVars.push_back("topTagJet2_nSubjettiness");
  listOfVars.push_back("topTagJet2_topMass");
  listOfVars.push_back("topTagJet2_filteredMass");
  listOfVars.push_back("topTagJet2_prunedMass");
  listOfVars.push_back("topTagJet2_trimmedMass");
  listOfVars.push_back("topTagJet2_softDropMass");

  listOfVars.push_back("topTagJet1_maxSubjetbtag");
  listOfVars.push_back("topTagJet2_maxSubjetbtag");

  //listOfVars.push_back("jet1AK8GenPt");
  //listOfVars.push_back("jet2AK8GenPt");

  //listOfVars.push_back("cmstt_Z_mass");
  //listOfVars.push_back("filtered_Z_mass");
  //listOfVars.push_back("pruned_Z_mass");
  //listOfVars.push_back("trimmed_Z_mass");
  listOfVars.push_back("softDrop_Z_mass");
  
  for (unsigned i = 0; i < listOfVars.size(); i++){
    treeVars[ listOfVars[i] ] = -999.99;
    tree->Branch( (listOfVars[i]).c_str() , &(treeVars[ listOfVars[i] ]), (listOfVars[i]+"/F").c_str() );
  }

  //tree->Branch();

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
   //cout <<"Event number: "<<iEvent<<endl;

   Handle<int> h_npv;
   Handle<GenEventInfoProduct> h_genEventInfo;

   Handle<vector<float> > h_jetAK8GenE;
   Handle<vector<float> > h_jetAK8GenPt;
   Handle<vector<float> > h_jetAK8GenEta;
   Handle<vector<float> > h_jetAK8GenPhi;

   Handle<vector<float> > h_jetAK8E;
   Handle<vector<float> > h_jetAK8Pt;
   Handle<vector<float> > h_jetAK8Eta;
   Handle<vector<float> > h_jetAK8Phi;
   Handle<vector<float> > h_jetAK8Y;
   Handle<vector<float> > h_jetAK8minmass;
   Handle<vector<float> > h_jetAK8tau1;
   Handle<vector<float> > h_jetAK8tau2;
   Handle<vector<float> > h_jetAK8tau3;
   Handle<vector<float> > h_jetAK8nSubJets;
   Handle<vector<float> > h_jetAK8filteredMass;
   Handle<vector<float> > h_jetAK8prunedMass;
   Handle<vector<float> > h_jetAK8trimmedMass;
   Handle<vector<float> > h_jetAK8softDropMass;
   Handle<vector<float> > h_jetAK8topMass;

   Handle<vector<float> > h_ak8jetSubjetIndex0;
   Handle<vector<float> > h_ak8jetSubjetIndex1;
   Handle<vector<float> > h_ak8jetSubjetIndex2;
   Handle<vector<float> > h_ak8jetSubjetIndex3;
   Handle<vector<float> > h_subjetCmsTopTagCSV;

   /*Handle<vector<float> > h_subjetAK8GenE;
   Handle<vector<float> > h_subjetAK8GenPt;
   Handle<vector<float> > h_subjetAK8GenEta;
   Handle<vector<float> > h_subjetAK8GenPhi;

   Handle<vector<float> > h_subjetAK8E;
   Handle<vector<float> > h_subjetAK8Pt;
   Handle<vector<float> > h_subjetAK8Eta;
   Handle<vector<float> > h_subjetAK8Phi;*/

   iEvent.getByLabel("eventUserData", "npv", h_npv );
   iEvent.getByLabel("generator", "", h_genEventInfo);

   iEvent.getByLabel("jetsAK8", "jetAK8GenJetE", h_jetAK8GenE );
   iEvent.getByLabel("jetsAK8", "jetAK8GenJetPt", h_jetAK8GenPt );
   iEvent.getByLabel("jetsAK8", "jetAK8GenJetEta", h_jetAK8GenEta );
   iEvent.getByLabel("jetsAK8", "jetAK8GenJetPhi", h_jetAK8GenPhi );

   iEvent.getByLabel("jetsAK8", "jetAK8E", h_jetAK8E );
   iEvent.getByLabel("jetsAK8", "jetAK8Pt", h_jetAK8Pt );
   iEvent.getByLabel("jetsAK8", "jetAK8Eta", h_jetAK8Eta );
   iEvent.getByLabel("jetsAK8", "jetAK8Phi", h_jetAK8Phi );
   iEvent.getByLabel("jetsAK8", "jetAK8Y", h_jetAK8Y );
   iEvent.getByLabel("jetsAK8", "jetAK8minmass", h_jetAK8minmass );
   iEvent.getByLabel("jetsAK8", "jetAK8tau1", h_jetAK8tau1 );
   iEvent.getByLabel("jetsAK8", "jetAK8tau2", h_jetAK8tau2 );
   iEvent.getByLabel("jetsAK8", "jetAK8tau3", h_jetAK8tau3 );
   iEvent.getByLabel("jetsAK8", "jetAK8nSubJets", h_jetAK8nSubJets );
   iEvent.getByLabel("jetsAK8", "jetAK8filteredMass", h_jetAK8filteredMass );
   iEvent.getByLabel("jetsAK8", "jetAK8prunedMass", h_jetAK8prunedMass );
   iEvent.getByLabel("jetsAK8", "jetAK8trimmedMass", h_jetAK8trimmedMass );
   iEvent.getByLabel("jetsAK8", "jetAK8softDropMass", h_jetAK8softDropMass );
   iEvent.getByLabel("jetsAK8", "jetAK8topMass", h_jetAK8topMass );

   iEvent.getByLabel("jetsAK8", "jetAK8topSubjetIndex0", h_ak8jetSubjetIndex0);
   iEvent.getByLabel("jetsAK8", "jetAK8topSubjetIndex1", h_ak8jetSubjetIndex1);
   iEvent.getByLabel("jetsAK8", "jetAK8topSubjetIndex2", h_ak8jetSubjetIndex2);
   iEvent.getByLabel("jetsAK8", "jetAK8topSubjetIndex3", h_ak8jetSubjetIndex3);
   iEvent.getByLabel("subjetsCmsTopTag", "subjetCmsTopTagCSV", h_subjetCmsTopTagCSV);

   /*iEvent.getByLabel("subjetsAK8", "subjetAK8GenSubjetE", h_subjetAK8GenE );
   iEvent.getByLabel("subjetsAK8", "subjetAK8GenSubjetPt", h_subjetAK8GenPt );
   iEvent.getByLabel("subjetsAK8", "subjetAK8GenSubjetEta", h_subjetAK8GenEta );
   iEvent.getByLabel("subjetsAK8", "subjetAK8GenSubjetPhi", h_subjetAK8GenPhi );

   iEvent.getByLabel("subjetsAK8", "subjetAK8E", h_subjetAK8E );
   iEvent.getByLabel("subjetsAK8", "subjetAK8Pt", h_subjetAK8Pt );
   iEvent.getByLabel("subjetsAK8", "subjetAK8Eta", h_subjetAK8Eta );
   iEvent.getByLabel("subjetsAK8", "subjetAK8Phi", h_subjetAK8Phi );*/

   //want to make sure the AK8 jet vectors match up
   if (h_jetAK8Pt->size() != h_jetAK8minmass->size() || h_jetAK8Pt->size() != h_jetAK8topMass->size()){
     cout<<"Error! Mismatched vectors."<<endl;
   }

   //initializing branches to -999.99
   for (unsigned i = 0; i < listOfVars.size(); i++){
     treeVars[ listOfVars[i] ] = -999.99;
   }

   //initializing and storing event weights
   double evWeight = 1.0 ;
   double qScale = 1.0 ;
   double pthat = 1.0 ;
   double evWeight_corr = 1.0;

   if (h_genEventInfo.isValid())
     {
       evWeight = h_genEventInfo->weight();
       qScale   = h_genEventInfo->qScale();
       pthat    = (h_genEventInfo->hasBinningValues() ? (h_genEventInfo->binningValues())[0] : 0.0);
       evWeight_corr = 1/pow(pthat/15,4.5);

       treeVars["evWeight_corr"] = evWeight_corr;
       //cout<<"GenEventInfo: qScale = "<<qScale<<" pthat = "<<pthat<<" evWeight = "<<evWeight<<" 1/pow(pthat/15,4.5) "<<1/pow(pthat/15,4.5)<<endl;
     }

   //reco AK8 jets
   int nAK8pt400eta2p4jets = 0;

   //top tagging
   //int nTopTagJets = 0;
   int topTagJet1_topTagFlag = 0;
   int topTagJet2_topTagFlag = 0;
   int nNsubjettinessCutJets = 0;
   int nBtagJets = 0;

   TLorentzVector softDropJet1;
   TLorentzVector softDropJet2;
   
   //int toptagindexJet1_cmstt = -1;
   //int toptagindexJet1_filtered = -1;
   //int toptagindexJet1_pruned = -1;
   //int toptagindexJet1_trimmed = -1;

   //int toptagindexJet2_cmstt = -1;
   //int toptagindexJet2_filtered = -1;
   //int toptagindexJet2_pruned = -1;
   //int toptagindexJet2_trimmed = -1;

   //TLorentzVector cmsttJet1;
   //TLorentzVector filteredJet1;
   //TLorentzVector prunedJet1;
   //TLorentzVector trimmedJet1;

   //TLorentzVector cmsttJet2;
   //TLorentzVector filteredJet2;
   //TLorentzVector prunedJet2;
   //TLorentzVector trimmedJet2;


   //Number of Primary Vertices
   treeVars["npv"] = *h_npv;

   //AK8 Jet Loop
   if (h_jetAK8Pt.isValid()){//make sure there are AK8 jets
     for (unsigned i=0; i<h_jetAK8Pt->size(); i++){//looping over AK8 jets
       //pt and eta preselection cuts
       if ((*h_jetAK8Pt)[i] > 400 && abs((*h_jetAK8Eta)[i]) < 2.4){
	 //treeVars["jet"+s+"AK8Pt"] = (*h_jetAK8Pt)[i];
	 //top tagging requirements
	 if (nAK8pt400eta2p4jets == 0){//first top tag jet candidate
	   treeVars["topTagJet1_pt"] = (*h_jetAK8Pt)[i];
	   treeVars["topTagJet1_eta"] = (*h_jetAK8Eta)[i];
	   treeVars["topTagJet1_phi"] = (*h_jetAK8Phi)[i];
	   treeVars["topTagJet1_E"] = (*h_jetAK8E)[i];
	   treeVars["topTagJet1_Y"] = (*h_jetAK8Y)[i];
	   treeVars["topTagJet1_minmass"] = (*h_jetAK8minmass)[i];
	   treeVars["topTagJet1_nSubJets"] = (*h_jetAK8nSubJets)[i];
	   treeVars["topTagJet1_tau1"] = (*h_jetAK8tau1)[i];
	   treeVars["topTagJet1_tau2"] = (*h_jetAK8tau2)[i];
	   treeVars["topTagJet1_tau3"] = (*h_jetAK8tau3)[i];
	   treeVars["topTagJet1_topMass"] = (*h_jetAK8topMass)[i];
	   treeVars["topTagJet1_filteredMass"] = (*h_jetAK8filteredMass)[i];
	   treeVars["topTagJet1_prunedMass"] = (*h_jetAK8prunedMass)[i];
	   treeVars["topTagJet1_trimmedMass"] = (*h_jetAK8trimmedMass)[i];
	   treeVars["topTagJet1_softDropMass"] = (*h_jetAK8softDropMass)[i];

	   //////b-tagging
	   float nSubjets_jet1 = (*h_jetAK8nSubJets)[i];

	   //vector of subjet CSV values
	   vector<float> subjet1CSVs;
	   if (nSubjets_jet1 > 0){
	     subjet1CSVs.push_back((*h_subjetCmsTopTagCSV)[(*h_ak8jetSubjetIndex0)[i]]);
	   }
	   if (nSubjets_jet1 > 1){
	     subjet1CSVs.push_back((*h_subjetCmsTopTagCSV)[(*h_ak8jetSubjetIndex1)[i]]);
	   }
	   if (nSubjets_jet1 > 2){
	     subjet1CSVs.push_back((*h_subjetCmsTopTagCSV)[(*h_ak8jetSubjetIndex2)[i]]);
	   }
	   if (nSubjets_jet1 > 3){
	     subjet1CSVs.push_back((*h_subjetCmsTopTagCSV)[(*h_ak8jetSubjetIndex3)[i]]);
	   }

	   //saving max subjet b-tag score for jet 1
	   float maxSubjet1CSV = -999.;
	   for (size_t j = 0; j < subjet1CSVs.size(); j++){
	     maxSubjet1CSV = max(maxSubjet1CSV, subjet1CSVs[j]);
	   }

	   /*cout<<"Top Candidate 1 pt: "<<(*h_jetAK8Pt)[i]<<" Gev"<<endl;
	   for (size_t j = 0; j < subjet1CSVs.size(); j++){
             cout<<"Subjet "<<j<<" CSV value: "<<subjet1CSVs[j]<<endl;
           }

	   cout<<"Max Subjet CSV value: "<<maxSubjet1CSV<<endl;*/

	   treeVars["topTagJet1_maxSubjetbtag"] = maxSubjet1CSV;

	   //nsubjettiness
	   float nSubjettiness = ((*h_jetAK8tau3)[i])/((*h_jetAK8tau2)[i]);
	   treeVars["topTagJet1_nSubjettiness"] = nSubjettiness;
	   
	   //top tagging with softdrop mass
	   if ((*h_jetAK8softDropMass)[i] > 110.0 && (*h_jetAK8softDropMass)[i] < 210.0){
	     topTagJet1_topTagFlag = 1;
	     softDropJet1.SetPtEtaPhiM((*h_jetAK8Pt)[i],(*h_jetAK8Eta)[i],(*h_jetAK8Phi)[i],(*h_jetAK8topMass)[i]);
	   }

	   treeVars["topTagJet1_topTagFlag"] = topTagJet1_topTagFlag;
	   
	   //incrementing counter for number of jets passing the Nsubjettiness cut
	   if (nSubjettiness < 0.61){
	     nNsubjettinessCutJets += 1;
	   }

	   //incrementing counter for number of jets passing the b-tag cut
	   if (maxSubjet1CSV > 0.76){
	     nBtagJets += 1;
	   }

	   //flagging the jet as top tagged by the cmstt mass
	   /*if ((*h_jetAK8topMass)[i] > 140.0 && (*h_jetAK8topMass)[i] < 250.0){
	     topTagJet1_topTagFlag |= 1;
	     //toptagindexJet1_cmstt = i;
	     cmsttJet1.SetPtEtaPhiM((*h_jetAK8Pt)[i],(*h_jetAK8Eta)[i],(*h_jetAK8Phi)[i],(*h_jetAK8topMass)[i]);
	   } 

	   //flagging the jet as top tagged by the filtered mass
	   if ((*h_jetAK8filteredMass)[i] > 140.0 && (*h_jetAK8filteredMass)[i] < 250.0){
	     topTagJet1_topTagFlag |= 2;
	     //toptagindexJet1_filtered = i;
	     filteredJet1.SetPtEtaPhiM((*h_jetAK8Pt)[i],(*h_jetAK8Eta)[i],(*h_jetAK8Phi)[i],(*h_jetAK8topMass)[i]);
	   }

	   //flagging the jet as top tagged by the pruned mass
	   if ((*h_jetAK8prunedMass)[i] > 140.0 && (*h_jetAK8prunedMass)[i] < 250.0){
	     topTagJet1_topTagFlag |= 4;
	     //toptagindexJet1_pruned = i;
	     prunedJet1.SetPtEtaPhiM((*h_jetAK8Pt)[i],(*h_jetAK8Eta)[i],(*h_jetAK8Phi)[i],(*h_jetAK8topMass)[i]);
	   }
	   
	   //flagging the jet as top tagged by the trimmed mass
	   if ((*h_jetAK8trimmedMass)[i] > 140.0 && (*h_jetAK8trimmedMass)[i] < 250.0){
	     topTagJet1_topTagFlag |= 8;
	     //toptagindexJet1_trimmed = i;
	     trimmedJet1.SetPtEtaPhiM((*h_jetAK8Pt)[i],(*h_jetAK8Eta)[i],(*h_jetAK8Phi)[i],(*h_jetAK8topMass)[i]);
	     }*/
	 }//end AK8 jet 1 loop
	 else if (nAK8pt400eta2p4jets == 1){//second top tag jet candidate
	   treeVars["topTagJet2_pt"] = (*h_jetAK8Pt)[i];
	   treeVars["topTagJet2_eta"] = (*h_jetAK8Eta)[i];
	   treeVars["topTagJet2_phi"] = (*h_jetAK8Phi)[i];
	   treeVars["topTagJet2_E"] = (*h_jetAK8E)[i];
	   treeVars["topTagJet2_Y"] = (*h_jetAK8Y)[i];
	   treeVars["topTagJet2_minmass"] = (*h_jetAK8minmass)[i];
	   treeVars["topTagJet2_nSubJets"] = (*h_jetAK8nSubJets)[i];
	   treeVars["topTagJet2_tau1"] = (*h_jetAK8tau1)[i];
	   treeVars["topTagJet2_tau2"] = (*h_jetAK8tau2)[i];
	   treeVars["topTagJet2_tau3"] = (*h_jetAK8tau3)[i];
	   treeVars["topTagJet2_topMass"] = (*h_jetAK8topMass)[i];
	   treeVars["topTagJet2_filteredMass"] = (*h_jetAK8filteredMass)[i];
	   treeVars["topTagJet2_prunedMass"] = (*h_jetAK8prunedMass)[i];
	   treeVars["topTagJet2_trimmedMass"] = (*h_jetAK8trimmedMass)[i];
	   treeVars["topTagJet2_softDropMass"] = (*h_jetAK8softDropMass)[i];
	   //treeVars["topTagJet2_subjetCSV"] = (*h_jetAK8subjetCSV)[i];
	       
	   //////b-tagging
	   float nSubjets_jet2 = (*h_jetAK8nSubJets)[i];

	   //vector of subjet CSV values
	   vector<float> subjet2CSVs;
	   if (nSubjets_jet2 > 0){
	     subjet2CSVs.push_back((*h_subjetCmsTopTagCSV)[(*h_ak8jetSubjetIndex0)[i]]);
	   }
	   if (nSubjets_jet2 > 1){
	     subjet2CSVs.push_back((*h_subjetCmsTopTagCSV)[(*h_ak8jetSubjetIndex1)[i]]);
	   }
	   if (nSubjets_jet2 > 2){
	     subjet2CSVs.push_back((*h_subjetCmsTopTagCSV)[(*h_ak8jetSubjetIndex2)[i]]);
	   }
	   if (nSubjets_jet2 > 3){
	     subjet2CSVs.push_back((*h_subjetCmsTopTagCSV)[(*h_ak8jetSubjetIndex3)[i]]);
	   }

	   //saving max subjet b-tag score for jet 2
	   float maxSubjet2CSV = -999.;
	   for (size_t j = 0; j < subjet2CSVs.size(); j++){
	     maxSubjet2CSV = max(maxSubjet2CSV, subjet2CSVs[j]);
	   }

	   /*cout<<"Top Candidate 2 pt: "<<(*h_jetAK8Pt)[i]<<" Gev"<<endl;
	   for (size_t j = 0; j < subjet2CSVs.size(); j++){
             cout<<"Subjet "<<j<<" CSV value: "<<subjet2CSVs[j]<<endl;
           }

	   cout<<"Max Subjet CSV value: "<<maxSubjet2CSV<<endl;*/

	   treeVars["topTagJet2_maxSubjetbtag"] = maxSubjet2CSV;

	   //nsubjettiness
	   float nSubjettiness = ((*h_jetAK8tau3)[i])/((*h_jetAK8tau2)[i]);
	   treeVars["topTagJet2_nSubjettiness"] = nSubjettiness;

	   //top tagging with softdrop mass
	   if ((*h_jetAK8softDropMass)[i] > 110.0 && (*h_jetAK8softDropMass)[i] < 210.0){
	     topTagJet2_topTagFlag = 1;
	     softDropJet2.SetPtEtaPhiM((*h_jetAK8Pt)[i],(*h_jetAK8Eta)[i],(*h_jetAK8Phi)[i],(*h_jetAK8topMass)[i]);
	   }
	   
	   treeVars["topTagJet2_topTagFlag"] = topTagJet2_topTagFlag;

	   //incrementing counter for number of jets passing the Nsubjettiness cut
	   if (nSubjettiness < 0.61){
	     nNsubjettinessCutJets += 1;
	   }

	   //incrementing counter for number of jets passing the b-tag cut
	   if (maxSubjet2CSV > 0.76){
	     nBtagJets += 1;
	   }

	   //flagging the jet as top tagged by the cmstt top mass
	   /*if ((*h_jetAK8topMass)[i] > 140.0 && (*h_jetAK8topMass)[i] < 250.0){
	     topTagJet2_topTagFlag |= 1;
	     //toptagindexJet2_cmstt = i;
	     cmsttJet2.SetPtEtaPhiM((*h_jetAK8Pt)[i],(*h_jetAK8Eta)[i],(*h_jetAK8Phi)[i],(*h_jetAK8topMass)[i]);
	   } 
	   
	   //flagging the jet as top tagged by the filtered mass
	   if ((*h_jetAK8filteredMass)[i] > 140.0 && (*h_jetAK8filteredMass)[i] < 250.0){
	     topTagJet2_topTagFlag |= 2;
	     //toptagindexJet2_filtered = i;
	     filteredJet2.SetPtEtaPhiM((*h_jetAK8Pt)[i],(*h_jetAK8Eta)[i],(*h_jetAK8Phi)[i],(*h_jetAK8topMass)[i]);
	   }

	   //flagging the jet as top tagged by the pruned mass
	   if ((*h_jetAK8prunedMass)[i] > 140.0 && (*h_jetAK8prunedMass)[i] < 250.0){
	     topTagJet2_topTagFlag |= 4;
	     //toptagindexJet2_pruned = i;
	     prunedJet2.SetPtEtaPhiM((*h_jetAK8Pt)[i],(*h_jetAK8Eta)[i],(*h_jetAK8Phi)[i],(*h_jetAK8topMass)[i]);
	   }
	   
	   //flagging the jet as top tagged by the trimmed mass
	   if ((*h_jetAK8trimmedMass)[i] > 140.0 && (*h_jetAK8trimmedMass)[i] < 250.0){
	     topTagJet2_topTagFlag |= 8;
	     //toptagindexJet2_trimmed = i;
	     trimmedJet2.SetPtEtaPhiM((*h_jetAK8Pt)[i],(*h_jetAK8Eta)[i],(*h_jetAK8Phi)[i],(*h_jetAK8topMass)[i]);
	     }*/
	 }//end AK8 jet 2 loop
	 nAK8pt400eta2p4jets +=1;//top tagging candidate iterator
       }//pt and eta preselection cuts
     }//end AK8 jet loop
   }//checking AK8 jet validity

   treeVars["nAK8pt400eta2p4jets"] = nAK8pt400eta2p4jets;

   //filling out the cutflow values
   treeVars["cutflow"] = 0.0;
   tree->Fill();

   if (nAK8pt400eta2p4jets > 0){
     treeVars["cutflow"] = 1.0;//1 AK8 jet that passes preselection
     tree->Fill();
     if (nAK8pt400eta2p4jets > 1){
       treeVars["cutflow"] = 2.0;//2 AK8 jets that pass preselection
       tree->Fill();
     }//2+ good AK8 jets
     if ((topTagJet1_topTagFlag == 1) || (topTagJet2_topTagFlag == 1)){
       treeVars["cutflow"] = 3.0;//1 good AK8 jet in mass window
       tree->Fill();
       if((topTagJet1_topTagFlag == 1) && (topTagJet2_topTagFlag == 1)){
	 //Reconstructing the Z-peak with 2 soft drop top tag jets
	 TLorentzVector softDrop_Z = softDropJet1 + softDropJet2;
	 treeVars["softDrop_Z_mass"] = softDrop_Z.M();
	 treeVars["cutflow"] = 4.0;//2 good AK8 jets in mass window
	 tree->Fill();
	 if(nNsubjettinessCutJets > 1){
	   treeVars["cutflow"] = 6.0;//2 good AK8 jets in mass window and 2 good jets passing Nsubjettiness cut
	   tree->Fill();
	   if(nBtagJets > 0){
	     treeVars["cutflow"] = 8.0;//2 good AK8 jets in mass window, 2 good jet passing Nsubjettiness cut, and 1 good b-tagged jets
	     tree->Fill();
	   }//1+ b-tag jet
	   if(nBtagJets > 1){
	     treeVars["cutflow"] = 9.0;//2 good AK8 jets in mass window, 2 good jet passing Nsubjettiness cut, and 2 good b-tagged jets
	     tree->Fill();
	   }//1+ b-tag jet
	 }//2 jets passing Nsubjettiness cut
       }//2 jets in mass window
       if(nNsubjettinessCutJets > 0){
	 treeVars["cutflow"] = 5.0;//1 good AK8 jet in mass window and 1 good jet passing Nsubjettiness cut
	 tree->Fill();
	 if(nBtagJets > 0){
	   treeVars["cutflow"] = 7.0;//1 good AK8 jet in mass window, 1 good jet passing Nsubjettiness cut, and 1 good b-tagged jet
	   tree->Fill();
	 }//1+ b-tag jet
       }//1+ jets passing Nsubjettiness cut
     }//1+ jet in mass window
   }//1+ good AK8 jets


   //2 cmstt top tag jets
   /*if(((topTagJet1_topTagFlag & 1) == 1) && ((topTagJet2_topTagFlag & 1) == 1)){
     TLorentzVector cmstt_Z = cmsttJet1 + cmsttJet2;
     treeVars["cmstt_Z_mass"] = cmstt_Z.M();
											       }
   //2 filtered top tag jets
   if(((topTagJet1_topTagFlag & 2) == 2) && ((topTagJet2_topTagFlag & 2) == 2)){
     TLorentzVector filtered_Z = filteredJet1 + filteredJet2;
     treeVars["filtered_Z_mass"] = filtered_Z.M();
											       }
   //2 pruned top tag jets
   if(((topTagJet1_topTagFlag & 4) == 4) && ((topTagJet2_topTagFlag & 4) == 4)){
     TLorentzVector pruned_Z = prunedJet1 + prunedJet2;
     treeVars["pruned_Z_mass"] = pruned_Z.M();
											       }
   //2 trimmed top tag jets
   if(((topTagJet1_topTagFlag & 8) == 8) && ((topTagJet2_topTagFlag & 8) == 8)){
     TLorentzVector trimmed_Z = trimmedJet1 + trimmedJet2;
     treeVars["trimmed_Z_mass"] = trimmed_Z.M();
     }*/

   /////Number of b-tags per event
   //if (topTagJet1_topTagFlag > 0 || topTagJet2_topTagFlag > 0){
     
   //}


   //cout<<"Number of top tagged jets: "<<nTopTagJets<<endl;
   //cout<<"Number of AK8 jets with pt > 400 GeV: "<<nAK8pt400eta2p4jets<<endl;
   
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
