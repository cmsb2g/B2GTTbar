#! /usr/bin/env python
import ROOT
import array


class B2GTTreeSemiLep( ) :
    def __init__( self, options ):

        ### Get ONE chain for each species we are interested in.
        ### Add the files for this species to this TTree
        self.tree = ROOT.TChain("ana/TreeSemiLept", "ana/TreeSemiLept")
        self.tree.AddFile( options.infile )

        self.branches = {}

        ###
        ### Make a list of variables to add to our analysis
        ###
        self.variables = {
            'SemiLeptTrigPass':'b',
            ## 'JetPtRaw':'f',
            ## 'JetEtaRaw':'f',
            ## 'JetPhiRaw':'f',
            ## 'JetMassRaw':'f',
            ## 'JetP':'f',
            ## 'JetPt':'f',
            ## 'JetEta':'f',
            ## 'JetPhi':'f',
            ## 'JetRap':'f',
            ## 'JetEnergy':'f',
            ## 'JetMass':'f',
            ## 'JetArea':'f',
            ## 'JetSDmass':'f',
            ## 'JetSDmassRaw':'f',
            ## 'JetSDmassCorrL23':'f',
            ## 'JetSDmassCorrL23Up':'f',
            ## 'JetSDmassCorrL23Dn':'f',
            ## 'JetSDmassCorrL123':'f',
            ## 'JetSDmassCorrL123Up':'f',
            ## 'JetSDmassCorrL123Dn':'f',
            ## 'JetSDmassCorrL23Smear':'f',
            ## 'JetSDmassCorrL23SmearUp':'f',
            ## 'JetSDmassCorrL23SmearDn':'f',
            ## 'JetSDptRaw':'f',
            ## 'JetSDptCorrL23':'f',
            ## 'JetSDptCorrL23Up':'f',
            ## 'JetSDptCorrL23Dn':'f',
            ## 'JetSDptCorrL123':'f',
            ## 'JetSDptCorrL123Up':'f',
            ## 'JetSDptCorrL123Dn':'f',
            ## 'JetSDptCorrL23Smear':'f',
            ## 'JetSDptCorrL23SmearUp':'f',
            ## 'JetSDptCorrL23SmearDn':'f',
            ## 'JetSDetaRaw':'f',
            ## 'JetSDphiRaw':'f',
            ## 'JetMassPruned':'f',
            ## 'JetMassTrimmed':'f',
            ## 'JetTau1':'f',
            ## 'JetTau2':'f',
            ## 'JetTau3':'f',
            ## 'JetTau4':'f',
            ## 'JetTau32':'f',
            ## 'JetTau21':'f',
            ## 'JetSDsubjet0bdisc':'f',
            ## 'JetSDsubjet1bdisc':'f',
            ## 'JetSDmaxbdisc':'f',
            ## 'JetSDmaxbdiscflavHadron':'f',
            ## 'JetSDmaxbdiscflavParton':'f',
            ## 'JetSDsubjet0pt':'f',
            ## 'JetSDsubjet0mass':'f',
            ## 'JetSDsubjet0eta':'f',
            ## 'JetSDsubjet0phi':'f',
            ## 'JetSDsubjet0area':'f',
            ## 'JetSDsubjet0flavHadron':'f',
            ## 'JetSDsubjet0flavParton':'f',
            ## 'JetSDsubjet0tau1':'f',
            ## 'JetSDsubjet0tau2':'f',
            ## 'JetSDsubjet0tau3':'f',
            ## 'JetSDsubjet1pt':'f',
            ## 'JetSDsubjet1mass':'f',
            ## 'JetSDsubjet1eta':'f',
            ## 'JetSDsubjet1phi':'f',
            ## 'JetSDsubjet1area':'f',
            ## 'JetSDsubjet1flavHadron':'f',
            ## 'JetSDsubjet1flavParton':'f',
            ## 'JetSDsubjet1tau1':'f',
            ## 'JetSDsubjet1tau2':'f',
            ## 'JetSDsubjet1tau3':'f',
            'JetPuppiPt':'f',
            'JetPuppiEta':'f',
            'JetPuppiPhi':'f',
            'JetPuppiMass':'f',
            'JetPuppiSDmass':'f',
            ## 'JetPuppiSDmassCorr':'f',
            ## 'JetPuppiSDmassCorrUp':'f',
            ## 'JetPuppiSDmassCorrDn':'f',
            ## 'JetPuppiSDmassCorrL23Smear':'f',
            ## 'JetPuppiSDmassCorrL23SmearUp':'f',
            ## 'JetPuppiSDmassCorrL23SmearDn':'f',
            'JetPuppiSDpt':'f',
            ## 'JetPuppiSDptCorr':'f',
            ## 'JetPuppiSDptCorrUp':'f',
            ## 'JetPuppiSDptCorrDn':'f',
            ## 'JetPuppiSDptCorrL23Smear':'f',
            ## 'JetPuppiSDptCorrL23SmearUp':'f',
            ## 'JetPuppiSDptCorrL23SmearDn':'f',
            'JetPuppiSDeta':'f',
            'JetPuppiSDphi':'f',
            'JetPuppiTau1':'f',
            'JetPuppiTau2':'f',
            'JetPuppiTau3':'f',
            'JetPuppiTau4':'f',
            'JetPuppiTau32':'f',
            'JetPuppiTau21':'f',
            'JetPuppiSDsubjet0bdisc':'f',
            'JetPuppiSDsubjet1bdisc':'f',
            'JetPuppiSDmaxbdisc':'f',
            'JetPuppiSDmaxbdiscflavHadron':'f',
            'JetPuppiSDmaxbdiscflavParton':'f',
            'JetPuppiSDsubjet0pt':'f',
            'JetPuppiSDsubjet0mass':'f',
            'JetPuppiSDsubjet0eta':'f',
            'JetPuppiSDsubjet0phi':'f',
            'JetPuppiSDsubjet0area':'f',
            'JetPuppiSDsubjet0flavHadron':'f',
            'JetPuppiSDsubjet0flavParton':'f',
            'JetPuppiSDsubjet0tau1':'f',
            'JetPuppiSDsubjet0tau2':'f',
            'JetPuppiSDsubjet0tau3':'f',
            'JetPuppiSDsubjet1pt':'f',
            'JetPuppiSDsubjet1mass':'f',
            'JetPuppiSDsubjet1eta':'f',
            'JetPuppiSDsubjet1phi':'f',
            'JetPuppiSDsubjet1area':'f',
            'JetPuppiSDsubjet1flavHadron':'f',
            'JetPuppiSDsubjet1flavParton':'f',
            'JetPuppiSDsubjet1tau1':'f',
            'JetPuppiSDsubjet1tau2':'f',
            'JetPuppiSDsubjet1tau3':'f',
            'JetCHF':'f',
            'JetNHF':'f',
            'JetCM':'f',
            'JetNM':'f',
            'JetNEF':'f',
            'JetCEF':'f',
            'JetMF':'f',
            'JetMult':'f',
            ## 'JetMassCorrFactor':'f',
            ## 'JetMassCorrFactorUp':'f',
            ## 'JetMassCorrFactorDn':'f',
            ## 'JetCorrFactor':'f',
            ## 'JetCorrFactorUp':'f',
            ## 'JetCorrFactorDn':'f',
            ## 'JetPtSmearFactor':'f',
            ## 'JetPtSmearFactorUp':'f',
            ## 'JetPtSmearFactorDn':'f',
            ## 'JetPuppiMassCorrFactor':'f',
            ## 'JetPuppiMassCorrFactorUp':'f',
            ## 'JetPuppiMassCorrFactorDn':'f',
            ## 'JetPuppiCorrFactor':'f',
            ## 'JetPuppiCorrFactorUp':'f',
            ## 'JetPuppiCorrFactorDn':'f',
            ## 'JetPuppiPtSmearFactor':'f',
            ## 'JetPuppiPtSmearFactorUp':'f',
            ## 'JetPuppiPtSmearFactorDn':'f',
            ## 'JetEtaScaleFactor':'f',
            ## 'JetPhiScaleFactor':'f',
            ## 'JetMatchedGenJetPt':'f',
            ## 'JetMatchedGenJetMass':'f',
            ## 'JetGenMatched_TopHadronic':'i',
            ## 'JetGenMatched_TopPt':'f',
            ## 'JetGenMatched_TopEta':'f',
            ## 'JetGenMatched_TopPhi':'f',
            ## 'JetGenMatched_TopMass':'f',
            ## 'JetGenMatched_bPt':'f',
            ## 'JetGenMatched_WPt':'f',
            ## 'JetGenMatched_Wd1Pt':'f',
            ## 'JetGenMatched_Wd2Pt':'f',
            ## 'JetGenMatched_Wd1ID':'f',
            ## 'JetGenMatched_Wd2ID':'f',
            ## 'JetGenMatched_MaxDeltaRPartonTop':'f',
            ## 'JetGenMatched_MaxDeltaRWPartonTop':'f',
            ## 'JetGenMatched_MaxDeltaRWPartonW':'f',
            ## 'JetGenMatched_DeltaR_t_b':'f',
            ## 'JetGenMatched_DeltaR_t_W':'f',
            ## 'JetGenMatched_DeltaR_t_Wd1':'f',
            ## 'JetGenMatched_DeltaR_t_Wd2':'f',
            ## 'JetGenMatched_DeltaR_W_b1':'f',
            ## 'JetGenMatched_DeltaR_W_Wd1':'f',
            ## 'JetGenMatched_DeltaR_W_Wd2':'f',
            ## 'JetGenMatched_DeltaR_Wd1_Wd2':'f',
            ## 'JetGenMatched_DeltaR_Wd1_b':'f',
            ## 'JetGenMatched_DeltaR_Wd2_b':'f',
            ## 'JetGenMatched_DeltaR_jet_t':'f',
            ## 'JetGenMatched_DeltaR_jet_W':'f',
            ## 'JetGenMatched_DeltaR_jet_b':'f',
            ## 'JetGenMatched_DeltaR_jet_Wd1':'f',
            ## 'JetGenMatched_DeltaR_jet_Wd2':'f',
            ## 'JetGenMatched_DeltaR_pup0_b':'f',
            ## 'JetGenMatched_DeltaR_pup0_Wd1':'f',
            ## 'JetGenMatched_DeltaR_pup0_Wd2':'f',
            ## 'JetGenMatched_DeltaR_pup1_b':'f',
            ## 'JetGenMatched_DeltaR_pup1_Wd1':'f',
            ## 'JetGenMatched_DeltaR_pup1_Wd2':'f',
            ## 'JetGenMatched_partonPt':'f',
            ## 'JetGenMatched_partonEta':'f',
            ## 'JetGenMatched_partonPhi':'f',
            ## 'JetGenMatched_partonMass':'f',
            ## 'JetGenMatched_partonID':'f',
            ## 'JetGenMatched_DeltaRjetParton':'f',
            'SemiLeptMETpx':'f',
            'SemiLeptMETpy':'f',
            'SemiLeptMETpt':'f',
            'SemiLeptMETphi':'f',
            'SemiLeptMETsumET':'f',
            'SemiLeptNvtx':'f',
            #'SemiLeptNPUtrue':'f',
            'SemiLeptRho':'f',
            'SemiLeptEventWeight':'f',
            'SemiLeptPUweight':'f',
            'SemiLeptPUweight_MBup':'f',
            'SemiLeptPUweight_MBdn':'f',
            'SemiLeptGenTTmass':'f',
            'HTlep':'f',
            'ST':'f',
            ## 'ST_CorrDn':'f',
            ## 'ST_CorrUp':'f',
            ## 'ST_PtSmearNom':'f',
            ## 'ST_PtSmearUp':'f',
            ## 'ST_PtSmearDn':'f',
            ## 'SemiLeptQ2weight_CorrDn':'f',
            ## 'SemiLeptQ2weight_CorrUp':'f',
            ## 'SemiLeptNNPDF3weight_CorrDn':'f',
            ## 'SemiLeptNNPDF3weight_CorrUp':'f',
            'SemiLeptRunNum':'f',
            'SemiLeptLumiBlock':'f',
            'SemiLeptEventNum':'f',
            'SemiLeptPassMETFilters':'i',
            'AK4dRminPt':'f',
            'AK4dRminEta':'f',
            'AK4dRminPhi':'f',
            'AK4dRminBdisc':'f',
            'AK4dRminLep':'f',
            'AK4BtagdRminPt':'f',
            'AK4BtagdRminBdisc':'f',
            'AK4BtagdRminLep':'f',
            'LepHemiContainsAK4BtagLoose':'i',
            'LepHemiContainsAK4BtagMedium':'i',
            'LepHemiContainsAK4BtagTight':'i',
            'LeptonPhi':'f',
            'LeptonPt':'f',
            'LeptonEta':'f',
            'LeptonMass':'f',
            'PtRel':'f',
            'LeptonIsMu':'i',
            'MuTight':'i',
            'MuMedium':'i',
            'DeltaRJetLep':'f',
            'DeltaPhiJetLep':'f',
          }


        
        self.tree.SetBranchStatus ('*', 0)
        for var in self.variables.iteritems() :
            self.tree.SetBranchStatus( var[0], 1 )
            if var[1] != 'b' : 
                setattr( self, var[0], array.array(var[1], [-1] ) )
            else :
                setattr( self, var[0], ROOT.vector('bool')(  ) )
            self.tree.SetBranchAddress( var[0], getattr( self, var[0] )  )
            

            


        #self.SemiLeptTrigNames     = ROOT.std.vector('std::string')();
        #self.SemiLeptTrigPrescales     = ROOT.std.vector('std::string')();
        #self.tree.SetBranchAddress( 'SemiLeptTrigNames', self.SemiLeptTrigNames )
        #self.tree.SetBranchAddress( 'SemiLeptTrigPrescales', self.SemiLeptTrigPrescales )
        #self.tree.SetBranchStatus( 'SemiLeptTrigNames', 1 )
        #self.tree.SetBranchStatus( 'SemiLeptTrigPrescales', 1 )