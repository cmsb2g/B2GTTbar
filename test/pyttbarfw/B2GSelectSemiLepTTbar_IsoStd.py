#! /usr/bin/env python

import ROOT

import TrigMap

class B2GSelectSemiLepTTbar_IsoStd( ) :
    """
    Selects boosted semileptonic ttbar events with standard isolation.
    """
    def __init__(self, options, tree ):
        self.ignoreTrig = options.ignoreTrig
        self.nstages = 6
        self.tree = tree        
        self.trigMap = TrigMap.TrigMap()

        # Cached class member variables for plotting
        self.leptonP4 = None
        self.nuP4 = None
        self.trigIndex = [self.trigMap.HLT_Mu45_eta2p1_v, self.trigMap.HLT_Mu50_v, self.trigMap.HLT_Mu55_v, self.trigMap.HLT_Ele105_CaloIdVT_GsfTrkIdT_v]
        self.printAK4Warning = True

        self.passed = [False] * self.nstages  

    """
        This is the "select" function that does the work for the event selection. If you have any complicated
        stuff to do, do it here and create a class member variable to cache the results. 
    """
    def select( self ) :

        self.leptonP4 = None
        self.nuP4 = None
        self.ak4Jet = None
        self.ak8Jet = None
        self.ak8SDJet = None
        

        self.leptonP4 = ROOT.TLorentzVector()        
        self.leptonP4.SetPtEtaPhiM( self.tree.LeptonPt[0], self.tree.LeptonEta[0], self.tree.LeptonPhi[0], 0)
        #print 'lepton : (%8.1f %6.3f %6.3f %8.1f)' % ( self.leptonP4.Perp(), self.leptonP4.Eta(), self.leptonP4.Phi(), self.leptonP4.M() )
        self.nuP4 = ROOT.TLorentzVector( self.tree.SemiLeptMETpt[0], self.tree.SemiLeptMETpx[0], self.tree.SemiLeptMETpy[0], 0. )
        #print 'nu     : (%8.1f %6.3f %6.3f %8.1f)' % ( self.nuP4.Perp(), self.nuP4.Eta(), self.nuP4.Phi(), self.nuP4.M() )
        self.ak4Jet = ROOT.TLorentzVector()
        self.ak4Jet.SetPtEtaPhiM( self.tree.AK4_dRminLep_Pt[0], self.tree.AK4_dRminLep_Eta[0], self.tree.AK4_dRminLep_Phi[0], self.tree.AK4_dRminLep_Mass[0] )
        #print 'ak4Jet : (%8.1f %6.3f %6.3f %8.1f)' % ( self.ak4Jet.Perp(), self.ak4Jet.Eta(), self.ak4Jet.Phi(), self.ak4Jet.M() )

        # Work the cut flow
        # Stage 0 : None.
        # Stage 1 : Trigger
        # Stage 2 : Lepton selection
        # Stage 3 : MET selection
        # Stage 4 : Leptonic-side AK4 jet selection
        # Stage 5 : Wlep pt selection
        self.passed = [False] * self.nstages

        self.passed[0] = True

        if not self.ignoreTrig : 
            for itrig in self.trigIndex :
                if bool ( self.tree.SemiLeptTrigPass[itrig] ) == True :
                    self.passed[1] = True
            if not self.passed[1] : return self.passed
        else :
            self.passed[1] = True

        passMuon = self.tree.LeptonIsMu[0] == 1 and self.leptonP4.Perp() > 53. and abs(self.leptonP4.Eta()) < 2.1 and self.tree.MuTight[0] and self.tree.MuIso[0] < 0.1
        passElectron = self.tree.LeptonIsMu[0] == 0 and self.leptonP4.Perp() > 110. and abs(self.leptonP4.Eta()) < 2.5 and self.tree.Electron_iso_passMedium[0] and self.tree.Elecron_relIsoWithEA[0] < 0.15
        if not ( passMuon or passElectron ) : return self.passed
        self.passed[2] = True
        
        if not (self.nuP4.Perp() > 40.) : return self.passed
        self.passed[3] = True
        
        if not ( self.ak4Jet.Perp() > 30. and abs(self.ak4Jet.Eta()) < 2.4 and self.tree.AK4_dRminLep_dRlep[0] > 0.4 ) : return self.passed
        self.passed[4] = True
        
        if not ( (self.leptonP4 + self.nuP4).Perp() > 200. ) : return self.passed
        self.passed[5] = True

        return self.passed

                    

    
