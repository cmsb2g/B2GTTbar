#! /usr/bin/env python



class TrigMap () :
    def __init__ (self ) :
        self.names = [
            "HLT_PFHT300_v",
            "HLT_PFHT350_v",
            "HLT_PFHT400_v",
            "HLT_PFHT475_v",
            "HLT_PFHT600_v",
            "HLT_PFHT650_v",
            "HLT_PFHT800_v",
            "HLT_PFHT900_v",
            "HLT_PFJet320_v",
            "HLT_PFJet400_v",
            "HLT_PFJet450_v",
            "HLT_PFJet500_v",
            "HLT_AK8PFJet360_TrimMass30_v",
            "HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v",
            "HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20_v",
            "HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_v",
            "HLT_Mu45_eta2p1_v",
            "HLT_Mu50_v",
            "HLT_Mu55_v",
            "HLT_IsoMu22_eta2p1_v",
            "HLT_IsoMu24_v",
            "HLT_IsoMu27_v",
            "HLT_Mu30_eta2p1_PFJet150_PFJet50_v",
            "HLT_Mu40_eta2p1_PFJet200_PFJet50_v",
            "HLT_Ele32_eta2p1_WPTight_Gsf_v",
            "HLT_Ele35_WPLoose_Gsf_v",
            "HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50_v",
            "HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet140_v",
            "HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165_v",
            "HLT_Ele105_CaloIdVT_GsfTrkIdT_v",
            ]
        for iname in self.names:
            setattr( self, iname, self.names.index(iname) )
        
