#! /usr/bin/env python

import ROOT

class B2GSelectSemiLepTTbar( ) :
    """
    Selects semileptonic ttbar events with widely separated top quarks.
    This selects type 2 top events with traditional lepton isolation.
    """
    def __init__(self, options, tree ):
        self.tau21Cut = options.tau21Cut
        self.tau32Cut = options.tau32Cut
        self.nstages = 9
        self.tree = tree        

        # Cached class member variables for plotting
        self.leptonP4 = None
        self.nuP4 = None
        self.ak4Jet = None
        self.ak8Jet = None
        self.ak8SDJet = None
        self.ak8SDJet_Subjet0 = None
        self.ak8SDJet_Subjet1 = None


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
        self.ak8SDJet_Subjet0 = None
        self.ak8SDJet_Subjet1 = None
        self.trigIndex = [22, 23]
        

        self.leptonP4 = ROOT.TLorentzVector()
        self.leptonP4.SetPtEtaPhiM( self.tree.LeptonPt[0], self.tree.LeptonEta[0], self.tree.LeptonPhi[0], 0)
        self.nuP4 = ROOT.TLorentzVector( self.tree.SemiLeptMETpt[0], self.tree.SemiLeptMETpx[0], self.tree.SemiLeptMETpy[0], 0. )
        self.ak4Jet = ROOT.TLorentzVector( )        
        self.ak4Jet.SetPtEtaPhiM( self.tree.AK4dRminPt[0], self.tree.AK4dRminEta[0], self.tree.AK4dRminPhi[0], 0 )
        self.ak8Jet = ROOT.TLorentzVector()
        self.ak8Jet.SetPtEtaPhiM( self.tree.JetPuppiPt[0], self.tree.JetPuppiEta[0], self.tree.JetPuppiPhi[0], self.tree.JetPuppiMass[0] )        
        self.ak8SDJet_Subjet0 = ROOT.TLorentzVector()
        self.ak8SDJet_Subjet1 = ROOT.TLorentzVector()
        self.ak8SDJet_Subjet0.SetPtEtaPhiM( self.tree.JetPuppiSDsubjet0pt[0], self.tree.JetPuppiSDsubjet0eta[0], self.tree.JetPuppiSDsubjet0phi[0], self.tree.JetPuppiSDsubjet0mass[0] )
        self.ak8SDJet_Subjet1.SetPtEtaPhiM( self.tree.JetPuppiSDsubjet1pt[0], self.tree.JetPuppiSDsubjet1eta[0], self.tree.JetPuppiSDsubjet1phi[0], self.tree.JetPuppiSDsubjet1mass[0] )
        self.ak8SDJet =  self.ak8SDJet_Subjet0 +  self.ak8SDJet_Subjet1
        self.tau21 = self.tree.JetPuppiTau21[0]
        #print 'ak8SDJet = (%6.2f,%8.3f,%8.3f,%6.2f)' % ( self.ak8SDJet.Perp(), self.ak8SDJet.Eta(), self.ak8SDJet.Phi(), self.ak8SDJet.M() )


        # Work the cut flow
        passed = [False] * self.nstages

        passed[0] = True

        for itrig in self.trigIndex :
            if bool ( self.tree.SemiLeptTrigPass[itrig] ) == True :
                passed[1] = True
        if not passed[1] : return passed

        if not ( self.tree.LeptonIsMu[0] == 1 and self.leptonP4.Perp() > 53. and abs(self.leptonP4.Eta()) < 2.1 and self.tree.MuTight[0] ) : return passed
        passed[2] = True
        
        if not (self.nuP4.Perp() > 80.) : return passed
        passed[3] = True
        
        if not ( self.ak4Jet.Perp() > 30. and abs(self.ak4Jet.Eta()) < 2.4 and self.tree.DeltaRJetLep[0] and self.ak4Jet.DeltaR( self.leptonP4) > 0.4 ) : return passed
        passed[4] = True
        
        if not ( (self.leptonP4 + self.nuP4).Perp() > 200. ) : return passed
        passed[5] = True

        if not (self.ak8Jet.Perp() > 200. and abs(self.ak8Jet.Eta()) < 2.4 and self.ak8Jet.DeltaR( self.leptonP4) > 1.0 ) : return passed
        passed[6] = True
        
        if not ( 30. < self.ak8SDJet.M() < 150. ) : return passed
        passed[7] = True

        if not ( self.tau21 < 0.7 ) : return passed
        passed[8] = True

        return passed

                    

    
