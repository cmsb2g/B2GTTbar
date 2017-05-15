// ScaleAdd_QCD_topTag.cc
// Scale the QCD top tagging trees appropriately for each pT and Add them together
// [] .L ScaleAdd_QCD_topTag.cc+
// [] ScaleAdd_QCD_topTag()

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
#include "QCDcrosssections.C"
#include "QCDcrosssections.h"

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <cmath>

using namespace std;
using namespace QCD_xs_PTbinned;

string fileBegin = "topTagStudies/v5/topTag_b2gtreeV5_QCD_Pt_";
string fileEnd = "_pythia8_RunIISummer16MiniAODv2_withExt.root";

void ScaleAdd_QCD_topTag(){
  //getting QCD cross sections
  QCDcrossections();

  //Output file with QCD with pt from 300 to 2400 GeV
  TFile *outFile = new TFile(Form("%s300to2400%s",fileBegin.c_str(),fileEnd.c_str()),"RECREATE");

  //Output tree                                                                                                                              
  TTree *tree_topTag = new TTree("tree_topTag", "tree_topTag");
  std::map<std::string, float> topTagTreeVars;

  //Output tree variables                                                                                                                           
  vector <string> listOfVars;
  listOfVars.push_back("npv");
  listOfVars.push_back("pt");
  listOfVars.push_back("eta");
  listOfVars.push_back("phi");
  listOfVars.push_back("top_size");
  listOfVars.push_back("partonID");

  listOfVars.push_back("ak08_pt");
  listOfVars.push_back("ak08_eta");
  listOfVars.push_back("ak08_phi");
  listOfVars.push_back("ak08_mass");
  listOfVars.push_back("ak08_tau32");
  listOfVars.push_back("ak08_btag");
  listOfVars.push_back("ak08_deltaRgen");

  listOfVars.push_back("ak08softdropz10b00_mass");
  listOfVars.push_back("ak08pruned_mass");
  listOfVars.push_back("ak08trimmed_mass");
  listOfVars.push_back("ak08softdropz10b00_btag");
  listOfVars.push_back("ak08softdropz10b00_btagSubjetPartonFlavor");

  listOfVars.push_back("ak08Puppi_tau32");
  listOfVars.push_back("ak08Puppisoftdropz10b00_mass");
  listOfVars.push_back("ak08Puppipruned_mass");
  listOfVars.push_back("ak08Puppitrimmed_mass");
  listOfVars.push_back("ak08Puppisoftdropz10b00_btag");
  listOfVars.push_back("ak08Puppisoftdropz10b00_btagSubjetPartonFlavor");

  //output tree branches
  for (unsigned i_vars = 0; i_vars < listOfVars.size(); i_vars++){
    topTagTreeVars[ listOfVars[i_vars] ] = -999.99;
    tree_topTag->Branch( (listOfVars[i_vars]).c_str() , &(topTagTreeVars[ listOfVars[i_vars] ]), (listOfVars[i_vars]+"/F").c_str() );
  }

  Float_t weight_qcdSample;
  tree_topTag->Branch("weight_qcdSample", &weight_qcdSample, "weight_qcdSample/F");

  //looping over QCD pt bins from 300 to 2400 GeV
  for (int i_ptBins = 0; i_ptBins < QCD_xs_PTbinned::pt2400to3200; i_ptBins++){
    cout << "Processing " << labels_xs_pt[i_ptBins] << endl;

    float qcdWeight = xs_pt[i_ptBins]/Nevents_pt[i_ptBins];

    //input trees
    TFile *infile = new TFile(Form("%s%s%s",fileBegin.c_str(),(labels_xs_pt[i_ptBins]).c_str(),fileEnd.c_str()), "READ");
    TTree *T1 = (TTree*) infile ->Get("tree_topTag");

    double treeNentries = T1->GetEntries();
    cout<<"treeNentries = "<< treeNentries <<endl;

    //input tree branches
    std::map<std::string, float> treeVars;
    for (unsigned i_vars = 0; i_vars < listOfVars.size(); i_vars++){
      T1->SetBranchAddress((listOfVars[i_vars]).c_str(), &(treeVars[listOfVars[i_vars]]));
    }

    for (int i=0; i<treeNentries; i++ ){ //entries                                                                                            
      if (i%10000==0) cout<<i<<"  / "<<treeNentries<<endl;
      T1->GetEntry(i);

      //looping over variables
      for (unsigned i_vars = 0; i_vars < listOfVars.size(); i_vars++){
	topTagTreeVars[(listOfVars[i_vars]).c_str()] = treeVars[listOfVars[i_vars]];
      }
      
      weight_qcdSample = qcdWeight; 
      tree_topTag->Fill();

    }//end entries 
  }//end QCD sample loop

  outFile->cd();
  tree_topTag->Write();
  outFile->Close();
}







