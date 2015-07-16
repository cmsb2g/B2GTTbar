#! /usr/bin/env python

##################
# mistagRate3.py
# Updated mistag rate code - Anti-tag and probe
# Example: python mistagRate3.py --files='QCD_Pt-15TTo7000_TuneZ2star-Flat_13TeV_pythia6_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1.txt' --outname='mistag3_out.root' --FlatSample --maxevents=50000
##################

from optparse import OptionParser
parser = OptionParser()

parser.add_option('--files', type='string', action='store',
                  dest='files',
                  help='Input files')

parser.add_option('--outname', type='string', action='store',
                  default='probe_and_tag_hist.root',
                  dest='outname',
                  help='Name of output file')
 
parser.add_option('--verbose', action='store_true',
                  default=False,
                  dest='verbose',
                  help='Print debugging info')

parser.add_option('--maxevents', type='int', action='store',
                  default=-1,
                  dest='maxevents',
                  help='Number of events to run. -1 is all events')


parser.add_option('--minAK8Pt', type='float', action='store',
                  default=200.,
                  dest='minAK8Pt',
                  help='Minimum PT for AK8 jets')

parser.add_option('--maxAK8Rapidity', type='float', action='store',
                  default=2.4,
                  dest='maxAK8Rapidity',
                  help='Maximum AK8 rapidity')
parser.add_option('--FlatSample', action='store_true',
                  default=False,
                  dest='deweightFlat',
                  help='unweights flat samples')



(options, args) = parser.parse_args()
argv = []


#FWLITE STUFF

import ROOT
import sys
from DataFormats.FWLite import Events, Handle
ROOT.gROOT.Macro("rootlogon.C")
import copy
import random


#generator info

handle_generator = Handle("GenEventInfoProduct")
hlabel_generator = ("generator" , "" )

handle_NPV = Handle("std::int")
hlabel_NPV = ( "eventUserData" , "npv" )

handle_jetsAK8Area = Handle("std::vector<float>")
hlabel_jetsAK8Area = ( "jetsAK8" , "jetAK8jetArea" )


handle_rho = Handle("double")
hlabel_rho = ("fixedGridRhoFastjetAll", "")

#MET label and Handles
handle_metPt = Handle("std::vector<float>")
hlabel_metPt = ("met" , "metPt")
handle_metPx = Handle("std::vector<float>")
hlabel_metPx = ("met" , "metPx")
handle_metPy = Handle("std::vector<float>")
hlabel_metPy = ("met" , "metPy")
handle_metPhi = Handle("std::vector<float>")
hlabel_metPhi = ("met" , "metPhi")

#AK8 Jets label and Handles
handle_jetsAK8Pt = Handle("std::vector<float>")
hlabel_jetsAK8Pt = ("jetsAK8" , "jetAK8Pt") #
handle_jetsAK8Eta = Handle("std::vector<float>")
hlabel_jetsAK8Eta = ("jetsAK8" , "jetAK8Eta")
handle_jetsAK8Phi = Handle("std::vector<float>")
hlabel_jetsAK8Phi = ("jetsAK8" , "jetAK8Phi")
handle_jetsAK8Mass = Handle("std::vector<float>")
hlabel_jetsAK8Mass = ("jetsAK8" , "jetAK8Mass")
handle_jetsAK8Energy = Handle("std::vector<float>")
hlabel_jetsAK8Energy = ("jetsAK8" , "jetAK8E") 
handle_jetsAK8JEC = Handle("std::vector<float>")
hlabel_jetsAK8JEC = ("jetsAK8" , "jetAK8jecFactor0")
handle_jetsAK8Y = Handle("std::vector<float>")
hlabel_jetsAK8Y = ("jetsAK8" , "jetAK8Y")
#handle_jetsAK8CSV = Handle("std::vector<float>")
#hlabel_jetsAK8CSV = ("jetsAK8" , "jetAK8CSV")

handle_jetsAK8nHadEnergy = Handle("std::vector<float>")
hlabel_jetsAK8nHadEnergy = ("jetsAK8" , "jetAK8neutralHadronEnergy")
handle_jetsAK8nEMEnergy = Handle("std::vector<float>")
hlabel_jetsAK8nEMEnergy = ("jetsAK8" , "jetAK8neutralEmEnergy")
handle_jetsAK8HFHadronEnergy = Handle("std::vector<float>")
hlabel_jetsAK8HFHadronEnergy = ("jetsAK8" , "jetAK8HFHadronEnergy")
handle_jetsAK8cHadEnergy = Handle("std::vector<float>")
hlabel_jetsAK8cHadEnergy = ("jetsAK8" , "jetAK8chargedHadronEnergy")
handle_jetsAK8cEMEnergy = Handle("std::vector<float>")
hlabel_jetsAK8cEMEnergy = ("jetsAK8" , "jetAK8chargedEmEnergy")
handle_jetsAK8numDaughters = Handle("std::vector<float>")
hlabel_jetsAK8numDaughters = ("jetsAK8" , "jetAK8numberOfDaughters")
handle_jetsAK8cMultip = Handle("std::vector<float>")
hlabel_jetsAK8cMultip = ("jetsAK8" , "jetAK8chargedMultiplicity")
handle_jetsAK8Y = Handle("std::vector<float>")
hlabel_jetsAK8Y = ("jetsAK8" , "jetAK8Y")

handle_jetsAK8TrimMass = Handle("std::vector<float>")
hlabel_jetsAK8TrimMass = ("jetsAK8", "jetAK8trimmedMass" )
handle_jetsAK8PrunMass = Handle("std::vector<float>")
hlabel_jetsAK8PrunMass = ("jetsAK8", "jetAK8prunedMass" )
handle_jetsAK8FiltMass = Handle("std::vector<float>")
hlabel_jetsAK8FiltMass = ("jetsAK8", "jetAK8filteredMass" )
handle_jetsAK8SoftDropMass = Handle("std::vector<float>")
hlabel_jetsAK8SoftDropMass = ("jetsAK8", "jetAK8softDropMass" )
handle_jetsAK8Tau1 = Handle("std::vector<float>")
hlabel_jetsAK8Tau1 = ("jetsAK8", "jetAK8tau1" )
handle_jetsAK8Tau2 = Handle("std::vector<float>")
hlabel_jetsAK8Tau2 = ("jetsAK8", "jetAK8tau2" )
handle_jetsAK8Tau3 = Handle("std::vector<float>")
hlabel_jetsAK8Tau3 = ("jetsAK8", "jetAK8tau3" )
handle_jetsAK8nSubJets = Handle("std::vector<float>")
hlabel_jetsAK8nSubJets = ("jetsAK8", "jetAK8nSubJets" )
handle_jetsAK8minmass = Handle("std::vector<float>")
hlabel_jetsAK8minmass = ("jetsAK8", "jetAK8minmass" )

handle_jetsAK8vSubjetIndex0 = Handle("std::vector<float>")
hlabel_jetsAK8vSubjetIndex0 = ("jetsAK8", "jetAK8vSubjetIndex0")
handle_jetsAK8vSubjetIndex1 = Handle("std::vector<float>")
hlabel_jetsAK8vSubjetIndex1 = ("jetsAK8", "jetAK8vSubjetIndex1")

handle_jetsAK8TopSubjetIndex0 = Handle("std::vector<float>")
hlabel_jetsAK8TopSubjetIndex0 = ("jetsAK8", "jetAK8topSubjetIndex0")
handle_jetsAK8TopSubjetIndex1 = Handle("std::vector<float>")
hlabel_jetsAK8TopSubjetIndex1 = ("jetsAK8", "jetAK8topSubjetIndex1")
handle_jetsAK8TopSubjetIndex2 = Handle("std::vector<float>")
hlabel_jetsAK8TopSubjetIndex2 = ("jetsAK8", "jetAK8topSubjetIndex2")
handle_jetsAK8TopSubjetIndex3 = Handle("std::vector<float>")
hlabel_jetsAK8TopSubjetIndex3 = ("jetsAK8", "jetAK8topSubjetIndex3")

h_subjetsAK8BDisc = Handle( "std::vector<float>")
l_subjetsAK8BDisc = ("subjetsCmsTopTag", "subjetCmsTopTagCSV")
h_subjetsAK8Pt = Handle( "std::vector<float>")
l_subjetsAK8Pt = ("subjetsCmsTopTag", "subjetCmsTopTagPt")
h_subjetsAK8Eta = Handle( "std::vector<float>")
l_subjetsAK8Eta = ("subjetsCmsTopTag", "subjetCmsTopTagEta")
h_subjetsAK8Phi = Handle( "std::vector<float>")
l_subjetsAK8Phi = ("subjetsCmsTopTag", "subjetCmsTopTagPhi")
h_subjetsAK8Mass = Handle( "std::vector<float>")
l_subjetsAK8Mass = ("subjetsCmsTopTag", "subjetCmsTopTagMass")

## Booking the histograms
print 'Booking histograms'
f = ROOT.TFile( options.outname , "RECREATE")
f.cd()




h_AntiTagNone_Probe_jetPt                = ROOT.TH1D("h_AntiTagNone_Probe_jetPt"                , "", 800,  0,  4000 )      
h_AntiTagNone_Probe_jetY                 = ROOT.TH1D("h_AntiTagNone_Probe_jetY"                 , "", 800, -3,     3 )      
h_AntiTagNone_Probe_jetTau32             = ROOT.TH1D("h_AntiTagNone_Probe_jetTau32"             , "", 800,  0,     1 )      
h_AntiTagNone_Probe_jetBdisc             = ROOT.TH1D("h_AntiTagNone_Probe_jetBdisc"             , "", 800,  0,     1 )      
h_AntiTagNone_TagMassSD_jetPt            = ROOT.TH1D("h_AntiTagNone_TagMassSD_jetPt"            , "", 800,  0,  4000 )      
h_AntiTagNone_TagMassSD_jetY             = ROOT.TH1D("h_AntiTagNone_TagMassSD_jetY"             , "", 800, -3,     3 )      
h_AntiTagNone_TagMassSD_jetTau32         = ROOT.TH1D("h_AntiTagNone_TagMassSD_jetTau32"         , "", 800,  0,     1 )      
h_AntiTagNone_TagMassSD_jetBdisc         = ROOT.TH1D("h_AntiTagNone_TagMassSD_jetBdisc"         , "", 800,  0,     1 )      
h_AntiTagNone_TagMassSDTau32_jetPt       = ROOT.TH1D("h_AntiTagNone_TagMassSDTau32_jetPt"       , "", 800,  0,  4000 )      
h_AntiTagNone_TagMassSDTau32_jetY        = ROOT.TH1D("h_AntiTagNone_TagMassSDTau32_jetY"        , "", 800, -3,     3 )      
h_AntiTagNone_TagMassSDTau32_jetTau32    = ROOT.TH1D("h_AntiTagNone_TagMassSDTau32_jetTau32"    , "", 800,  0,     1 )      
h_AntiTagNone_TagMassSDTau32_jetBdisc    = ROOT.TH1D("h_AntiTagNone_TagMassSDTau32_jetBdisc"    , "", 800,  0,     1 )      
h_AntiTagNone_TagMassSDMinMass_jetPt     = ROOT.TH1D("h_AntiTagNone_TagMassSDMinMass_jetPt"     , "", 800,  0,  4000 )      
h_AntiTagNone_TagMassSDMinMass_jetY      = ROOT.TH1D("h_AntiTagNone_TagMassSDMinMass_jetY"      , "", 800, -3,     3 )      
h_AntiTagNone_TagMassSDMinMass_jetTau32  = ROOT.TH1D("h_AntiTagNone_TagMassSDMinMass_jetTau32"  , "", 800,  0,     1 )      
h_AntiTagNone_TagMassSDMinMass_jetBdisc  = ROOT.TH1D("h_AntiTagNone_TagMassSDMinMass_jetBdisc"  , "", 800,  0,     1 )      
h_AntiTagNone_TagMassSDMaxBdisc_jetPt    = ROOT.TH1D("h_AntiTagNone_TagMassSDMaxBdisc_jetPt"    , "", 800,  0,  4000 )      
h_AntiTagNone_TagMassSDMaxBdisc_jetY     = ROOT.TH1D("h_AntiTagNone_TagMassSDMaxBdisc_jetY"     , "", 800, -3,     3 )      
h_AntiTagNone_TagMassSDMaxBdisc_jetTau32 = ROOT.TH1D("h_AntiTagNone_TagMassSDMaxBdisc_jetTau32" , "", 800,  0,     1 )      
h_AntiTagNone_TagMassSDMaxBdisc_jetBdisc = ROOT.TH1D("h_AntiTagNone_TagMassSDMaxBdisc_jetBdisc" , "", 800,  0,     1 )      
h_AntiTagNone_TagMassFat_jetPt           = ROOT.TH1D("h_AntiTagNone_TagMassFat_jetPt"           , "", 800,  0,  4000 )      
h_AntiTagNone_TagMassFat_jetY            = ROOT.TH1D("h_AntiTagNone_TagMassFat_jetY"            , "", 800, -3,     3 )      
h_AntiTagNone_TagMassFat_jetTau32        = ROOT.TH1D("h_AntiTagNone_TagMassFat_jetTau32"        , "", 800,  0,     1 )      
h_AntiTagNone_TagMassFat_jetBdisc        = ROOT.TH1D("h_AntiTagNone_TagMassFat_jetBdisc"        , "", 800,  0,     1 )      
h_AntiTagNone_TagMassFatMinMass_jetPt    = ROOT.TH1D("h_AntiTagNone_TagMassFatMinMass_jetPt"    , "", 800,  0,  4000 )      
h_AntiTagNone_TagMassFatMinMass_jetY     = ROOT.TH1D("h_AntiTagNone_TagMassFatMinMass_jetY"     , "", 800, -3,     3 )      
h_AntiTagNone_TagMassFatMinMass_jetTau32 = ROOT.TH1D("h_AntiTagNone_TagMassFatMinMass_jetTau32" , "", 800,  0,     1 )      
h_AntiTagNone_TagMassFatMinMass_jetBdisc = ROOT.TH1D("h_AntiTagNone_TagMassFatMinMass_jetBdisc" , "", 800,  0,     1 ) 

h_AntiTagMinMass30_ReqTopMassSD_Probe_jetPt                 = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_Probe_jetPt"                , "", 800,  0,  4000 )      
h_AntiTagMinMass30_ReqTopMassSD_Probe_jetY                  = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_Probe_jetY"                 , "", 800, -3,     3 )      
h_AntiTagMinMass30_ReqTopMassSD_Probe_jetTau32              = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_Probe_jetTau32"             , "", 800,  0,     1 )      
h_AntiTagMinMass30_ReqTopMassSD_Probe_jetBdisc              = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_Probe_jetBdisc"             , "", 800,  0,     1 )      
h_AntiTagMinMass30_ReqTopMassSD_TagMassSD_jetPt             = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_TagMassSD_jetPt"            , "", 800,  0,  4000 )      
h_AntiTagMinMass30_ReqTopMassSD_TagMassSD_jetY              = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_TagMassSD_jetY"             , "", 800, -3,     3 )      
h_AntiTagMinMass30_ReqTopMassSD_TagMassSD_jetTau32          = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_TagMassSD_jetTau32"         , "", 800,  0,     1 )      
h_AntiTagMinMass30_ReqTopMassSD_TagMassSD_jetBdisc          = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_TagMassSD_jetBdisc"         , "", 800,  0,     1 )      
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32_jetPt        = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32_jetPt"       , "", 800,  0,  4000 )      
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32_jetY         = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32_jetY"        , "", 800, -3,     3 )      
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32_jetTau32     = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32_jetTau32"    , "", 800,  0,     1 )      
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32_jetBdisc     = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32_jetBdisc"    , "", 800,  0,     1 )      
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMinMass_jetPt      = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMinMass_jetPt"     , "", 800,  0,  4000 )      
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMinMass_jetY       = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMinMass_jetY"      , "", 800, -3,     3 )      
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMinMass_jetTau32   = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMinMass_jetTau32"  , "", 800,  0,     1 )      
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMinMass_jetBdisc   = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMinMass_jetBdisc"  , "", 800,  0,     1 )      
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMaxBdisc_jetPt     = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMaxBdisc_jetPt"    , "", 800,  0,  4000 )      
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMaxBdisc_jetY      = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMaxBdisc_jetY"     , "", 800, -3,     3 )      
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMaxBdisc_jetTau32  = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMaxBdisc_jetTau32" , "", 800,  0,     1 )      
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMaxBdisc_jetBdisc  = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMaxBdisc_jetBdisc" , "", 800,  0,     1 )      
h_AntiTagMinMass30_ReqTopMassSD_TagMassFat_jetPt            = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_TagMassFat_jetPt"           , "", 800,  0,  4000 )      
h_AntiTagMinMass30_ReqTopMassSD_TagMassFat_jetY             = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_TagMassFat_jetY"            , "", 800, -3,     3 )      
h_AntiTagMinMass30_ReqTopMassSD_TagMassFat_jetTau32         = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_TagMassFat_jetTau32"        , "", 800,  0,     1 )      
h_AntiTagMinMass30_ReqTopMassSD_TagMassFat_jetBdisc         = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_TagMassFat_jetBdisc"        , "", 800,  0,     1 )      
h_AntiTagMinMass30_ReqTopMassSD_TagMassFatMinMass_jetPt     = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_TagMassFatMinMass_jetPt"    , "", 800,  0,  4000 )      
h_AntiTagMinMass30_ReqTopMassSD_TagMassFatMinMass_jetY      = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_TagMassFatMinMass_jetY"     , "", 800, -3,     3 )      
h_AntiTagMinMass30_ReqTopMassSD_TagMassFatMinMass_jetTau32  = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_TagMassFatMinMass_jetTau32" , "", 800,  0,     1 )      
h_AntiTagMinMass30_ReqTopMassSD_TagMassFatMinMass_jetBdisc  = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassSD_TagMassFatMinMass_jetBdisc" , "", 800,  0,     1 )       



h_AntiTagNone_Probe_jetPt                . Sumw2()
h_AntiTagNone_Probe_jetY                 . Sumw2()
h_AntiTagNone_Probe_jetTau32             . Sumw2()
h_AntiTagNone_Probe_jetBdisc             . Sumw2()
h_AntiTagNone_TagMassSD_jetPt            . Sumw2()
h_AntiTagNone_TagMassSD_jetY             . Sumw2()
h_AntiTagNone_TagMassSD_jetTau32         . Sumw2()
h_AntiTagNone_TagMassSD_jetBdisc         . Sumw2()
h_AntiTagNone_TagMassSDTau32_jetPt       . Sumw2()
h_AntiTagNone_TagMassSDTau32_jetY        . Sumw2()
h_AntiTagNone_TagMassSDTau32_jetTau32    . Sumw2()
h_AntiTagNone_TagMassSDTau32_jetBdisc    . Sumw2()
h_AntiTagNone_TagMassSDMinMass_jetPt     . Sumw2()
h_AntiTagNone_TagMassSDMinMass_jetY      . Sumw2()
h_AntiTagNone_TagMassSDMinMass_jetTau32  . Sumw2()
h_AntiTagNone_TagMassSDMinMass_jetBdisc  . Sumw2()
h_AntiTagNone_TagMassSDMaxBdisc_jetPt    . Sumw2()
h_AntiTagNone_TagMassSDMaxBdisc_jetY     . Sumw2()
h_AntiTagNone_TagMassSDMaxBdisc_jetTau32 . Sumw2()
h_AntiTagNone_TagMassSDMaxBdisc_jetBdisc . Sumw2()
h_AntiTagNone_TagMassFat_jetPt           . Sumw2()
h_AntiTagNone_TagMassFat_jetY            . Sumw2()
h_AntiTagNone_TagMassFat_jetTau32        . Sumw2()
h_AntiTagNone_TagMassFat_jetBdisc        . Sumw2()
h_AntiTagNone_TagMassFatMinMass_jetPt    . Sumw2()
h_AntiTagNone_TagMassFatMinMass_jetY     . Sumw2()
h_AntiTagNone_TagMassFatMinMass_jetTau32 . Sumw2()
h_AntiTagNone_TagMassFatMinMass_jetBdisc . Sumw2()

h_AntiTagMinMass30_ReqTopMassSD_Probe_jetPt                . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_Probe_jetY                 . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_Probe_jetTau32             . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_Probe_jetBdisc             . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_TagMassSD_jetPt            . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_TagMassSD_jetY             . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_TagMassSD_jetTau32         . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_TagMassSD_jetBdisc         . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32_jetPt       . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32_jetY        . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32_jetTau32    . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32_jetBdisc    . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMinMass_jetPt     . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMinMass_jetY      . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMinMass_jetTau32  . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMinMass_jetBdisc  . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMaxBdisc_jetPt    . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMaxBdisc_jetY     . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMaxBdisc_jetTau32 . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMaxBdisc_jetBdisc . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_TagMassFat_jetPt           . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_TagMassFat_jetY            . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_TagMassFat_jetTau32        . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_TagMassFat_jetBdisc        . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_TagMassFatMinMass_jetPt    . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_TagMassFatMinMass_jetY     . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_TagMassFatMinMass_jetTau32 . Sumw2()
h_AntiTagMinMass30_ReqTopMassSD_TagMassFatMinMass_jetBdisc . Sumw2()



#JET CORRECTIONS

ROOT.gSystem.Load('libCondFormatsJetMETObjects')

print 'Getting L3 for AK8'
L3JetParAK8  = ROOT.JetCorrectorParameters("JECs/PHYS14_25_V2_L3Absolute_AK8PFchs.txt");
print 'Getting L2 for AK8'
L2JetParAK8  = ROOT.JetCorrectorParameters("JECs/PHYS14_25_V2_L2Relative_AK8PFchs.txt");
print 'Getting L1 for AK8'
L1JetParAK8  = ROOT.JetCorrectorParameters("JECs/PHYS14_25_V2_L1FastJet_AK8PFchs.txt");
# for data only :
#ResJetParAK8 = ROOT.JetCorrectorParameters("JECs/PHYS14_25_V2_L2L3Residual_AK8PFchs.txt"); 

#  Load the JetCorrectorParameter objects into a vector, IMPORTANT: THE ORDER MATTERS HERE !!!! 
vParJecAK8 = ROOT.vector('JetCorrectorParameters')()
vParJecAK8.push_back(L1JetParAK8)
vParJecAK8.push_back(L2JetParAK8)
vParJecAK8.push_back(L3JetParAK8)
# for data only :
#vParJecAK8.push_back(ResJetPar)

ak8JetCorrector = ROOT.FactorizedJetCorrector(vParJecAK8)


#EVENT LOOP
filelist = file( options.files )
filesraw = filelist.readlines()
files = []
nevents = 0
for ifile in filesraw:
    if len( ifile ) > 2 : 
        #s = 'root://cmsxrootd.fnal.gov/' + ifile.rstrip()
        s = ifile.rstrip()
        files.append( s )
        print 'Added ' + s
       
NGoodAK8Jets = 0
NGoodAntiTaggedEventsSD = 0
NGoodAntiTagTopTagPairsSD = 0
NGoodAntiTaggedEventsFJ = 0
NGoodAntiTagTopTagPairsFJ = 0
NGoodAntiTaggedEventsNM = 0
NGoodAntiTagTopTagPairsNM = 0
NGoodAntiTaggedEventsSDT = 0
NGoodAntiTagTopTagPairsSDT = 0
NGoodAntiTaggedEventsFJT = 0
NGoodAntiTagTopTagPairsFJT = 0
NGoodAntiTaggedEventsNMT = 0
NGoodAntiTagTopTagPairsNMT = 0
NGoodAntiTagTopTagPairsFree = 0
NPassDiJetCut = 0
NPassptCut = 0
NPassetaCut = 0
NPassdPhiCut = 0
NPassAllCuts = 0
# loop over files
for ifile in files : #{ Loop over root files
    print 'Processing file ' + ifile
    events = Events (ifile)
    if options.maxevents > 0 and nevents > options.maxevents :
        break

    # loop over events in this file
    for event in events: #{ Loop over events in root files
        if options.maxevents > 0 and nevents > options.maxevents :
            break
        nevents += 1

        if nevents % 1000 == 0 : 
            print '    ---> Event ' + str(nevents)
        if options.verbose :
            print '==============================================='
            print '    ---> Event ' + str(nevents)

        
        # Vertex Sets
        event.getByLabel( hlabel_NPV, handle_NPV )
        if len(handle_NPV.product()) == 0 :
            if options.verbose :
                print "Event has no good primary vertex."
            continue
        NPV = handle_NPV.product()[0]
        #@ RHO VALUE
        event.getByLabel( hlabel_rho, handle_rho )
        if len(handle_rho.product()) == 0 :
            print "Event has no rho values."
            continue
        else:
            rho = handle_rho.product()[0]
            if options.verbose :
                print 'rho = {0:6.2f}'.format( rho )

        ############################################
        # Get the AK8 jets
        ############################################

        event.getByLabel ( hlabel_jetsAK8Eta, handle_jetsAK8Eta )
        event.getByLabel ( hlabel_jetsAK8Pt, handle_jetsAK8Pt )
        event.getByLabel ( hlabel_jetsAK8Phi, handle_jetsAK8Phi )
        event.getByLabel ( hlabel_jetsAK8Mass, handle_jetsAK8Mass )
        event.getByLabel ( hlabel_jetsAK8Energy, handle_jetsAK8Energy )
        event.getByLabel ( hlabel_jetsAK8JEC, handle_jetsAK8JEC )
        event.getByLabel ( hlabel_jetsAK8Y, handle_jetsAK8Y )
        event.getByLabel ( hlabel_jetsAK8Area, handle_jetsAK8Area )

        event.getByLabel ( hlabel_jetsAK8nHadEnergy, handle_jetsAK8nHadEnergy)
        event.getByLabel ( hlabel_jetsAK8nEMEnergy, handle_jetsAK8nEMEnergy )
        event.getByLabel ( hlabel_jetsAK8cHadEnergy, handle_jetsAK8cHadEnergy )
        event.getByLabel ( hlabel_jetsAK8HFHadronEnergy, handle_jetsAK8HFHadronEnergy )
        event.getByLabel ( hlabel_jetsAK8cEMEnergy, handle_jetsAK8cEMEnergy )
        event.getByLabel ( hlabel_jetsAK8numDaughters, handle_jetsAK8numDaughters )
        event.getByLabel ( hlabel_jetsAK8cMultip, handle_jetsAK8cMultip )

        event.getByLabel ( hlabel_jetsAK8TrimMass, handle_jetsAK8TrimMass )
        event.getByLabel ( hlabel_jetsAK8PrunMass, handle_jetsAK8PrunMass )
        event.getByLabel ( hlabel_jetsAK8FiltMass, handle_jetsAK8FiltMass )
        event.getByLabel ( hlabel_jetsAK8SoftDropMass, handle_jetsAK8SoftDropMass )
        event.getByLabel ( hlabel_jetsAK8Tau1, handle_jetsAK8Tau1 )
        event.getByLabel ( hlabel_jetsAK8Tau2, handle_jetsAK8Tau2 )
        event.getByLabel ( hlabel_jetsAK8Tau3, handle_jetsAK8Tau3 )
        event.getByLabel ( hlabel_jetsAK8nSubJets, handle_jetsAK8nSubJets )
        event.getByLabel ( hlabel_jetsAK8minmass, handle_jetsAK8minmass )

        event.getByLabel ( hlabel_jetsAK8TopSubjetIndex0, handle_jetsAK8TopSubjetIndex0 )
        event.getByLabel ( hlabel_jetsAK8TopSubjetIndex1, handle_jetsAK8TopSubjetIndex1 )
        event.getByLabel ( hlabel_jetsAK8TopSubjetIndex2, handle_jetsAK8TopSubjetIndex2 )
        event.getByLabel ( hlabel_jetsAK8TopSubjetIndex3, handle_jetsAK8TopSubjetIndex3 )

        event.getByLabel ( l_subjetsAK8BDisc, h_subjetsAK8BDisc)
        event.getByLabel ( l_subjetsAK8Pt, h_subjetsAK8Pt)
        event.getByLabel ( l_subjetsAK8Eta, h_subjetsAK8Eta)
        event.getByLabel ( l_subjetsAK8Phi, h_subjetsAK8Phi)
        if options.deweightFlat : 
            #@ Event weights
            gotGenerator = event.getByLabel( hlabel_generator, handle_generator )

        evWeight = -1

        ak8JetsGood = []
        ak8JetsGoodTrimMass = []
        ak8JetsGoodPrunMass = []
        ak8JetsGoodFiltMass = []
        ak8JetsGoodSDropMass = []
        ak8JetsGoodTau1 = []
        ak8JetsGoodTau2 = []
        ak8JetsGoodTau3 = []
        ak8JetsGoodNSubJets = []
        ak8JetsGoodMinMass = []
        ak8JetsGoodMass = []
        ak8JetsGoodPhi = []
        ak8JetsGoodY = []
        ak8JetsGoodPt = []
        ak8JetsGoodTopSubjetIndex0 = []
        ak8JetsGoodTopSubjetIndex1 = []
        ak8JetsGoodTopSubjetIndex2 = []
        ak8JetsGoodTopSubjetIndex3 = []

        AK8SubJetsBDisc = []
        AK8SubJetsPt = []
        AK8SubJetsEta = []
        AK8SubJetsPhi = []


        if len( handle_jetsAK8Pt.product()) > 0 and len( h_subjetsAK8BDisc.product() ) > 0:

            AK8Pt = handle_jetsAK8Pt.product()
            AK8Eta = handle_jetsAK8Eta.product()
            AK8Phi = handle_jetsAK8Phi.product()
            AK8Mass = handle_jetsAK8Mass.product()
            AK8Energy = handle_jetsAK8Energy.product()
            AK8Y = handle_jetsAK8Y.product()

            AK8JEC = handle_jetsAK8JEC.product()
            AK8Area = handle_jetsAK8Area.product()

            AK8nHadE = handle_jetsAK8nHadEnergy.product()
            AK8nEME = handle_jetsAK8nEMEnergy.product()
            AK8cHadE =  handle_jetsAK8cHadEnergy.product()
            AK8HFHadE = handle_jetsAK8HFHadronEnergy.product()
            AK8cEME =  handle_jetsAK8cEMEnergy.product()
            AK8numDaughters = handle_jetsAK8numDaughters.product()
            AK8cMultip =  handle_jetsAK8cMultip.product()

            AK8TrimmedM = handle_jetsAK8TrimMass.product()
            AK8PrunedM = handle_jetsAK8PrunMass.product()
            AK8FilteredM = handle_jetsAK8FiltMass.product()
            AK8SDropM = handle_jetsAK8SoftDropMass.product()
            AK8Tau1 = handle_jetsAK8Tau1.product()
            AK8Tau2 = handle_jetsAK8Tau2.product()
            AK8Tau3 = handle_jetsAK8Tau3.product()
            AK8nSubJets = handle_jetsAK8nSubJets.product()
            AK8minmass = handle_jetsAK8minmass.product()
            AK8TopSubjetIndex0 = handle_jetsAK8TopSubjetIndex0.product()
            AK8TopSubjetIndex1 = handle_jetsAK8TopSubjetIndex1.product()
            AK8TopSubjetIndex2 = handle_jetsAK8TopSubjetIndex2.product()
            AK8TopSubjetIndex3 = handle_jetsAK8TopSubjetIndex3.product()
            AK8SubJetsBDisc = h_subjetsAK8BDisc.product()
            AK8SubJetsPt = h_subjetsAK8Pt.product()
            AK8SubJetsEta = h_subjetsAK8Eta.product()
            AK8SubJetsPhi = h_subjetsAK8Phi.product()
            if options.deweightFlat :
                pthat = 0.0
                if handle_generator.product().hasBinningValues() :
                    pthat = handle_generator.product().binningValues()[0]
                    evWeight = 1/pow(pthat/15.,4.5)
        else :
            continue
        for ak8Jet in range(0,len(AK8Pt)):
            BadStuff = False
            if len(AK8Pt) <= 0 or len(AK8Eta) <= 0 or len(AK8Phi) <= 0 or len(AK8Mass) <= 0 :
                continue
            AK8JECFromB2GAnaFW = AK8JEC[ak8Jet]
            AK8P4Raw = ROOT.TLorentzVector()
            AK8P4Raw.SetPtEtaPhiM( AK8Pt[ak8Jet] , AK8Eta[ak8Jet], AK8Phi[ak8Jet], AK8Mass[ak8Jet])
            # Remove the old JEC's to get raw energy
            AK8P4Raw *= AK8JECFromB2GAnaFW 
            RawAK8Energy = AK8P4Raw.Energy()

            #$ Cut based on charged and neutral energy for AK8 jets
            nhf = AK8nHadE[ak8Jet] / AK8P4Raw.E()
            nef = AK8nEME[ak8Jet] / AK8P4Raw.E()
            chf = AK8cHadE[ak8Jet] / AK8P4Raw.E()
            cef = AK8cEME[ak8Jet] / AK8P4Raw.E()
            nconstituents = AK8numDaughters[ak8Jet]
            nch = AK8cMultip[ak8Jet] 
            goodJet = \
                nhf < 0.99 and \
                nef < 0.99 and \
                chf > 0.00 and \
                cef < 0.99 and \
                nconstituents > 1 and \
                nch > 0

            if not goodJet :
                if options.verbose :
                    print '   bad jet pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}'.format (
                            AK8P4Raw.Perp(), AK8P4Raw.Rapidity(), AK8P4Raw.Phi(), AK8P4Raw.M()
                            )
                continue
            if options.verbose :
                  print '   raw jet pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}'.format (
                        AK8P4Raw.Perp(), AK8P4Raw.Rapidity(), AK8P4Raw.Phi(), AK8P4Raw.M()
                        )

            #@ JEC Scaling for AK8 Jets
            ak8JetCorrector.setJetEta( AK8P4Raw.Eta() )
            ak8JetCorrector.setJetPt ( AK8P4Raw.Perp() )
            ak8JetCorrector.setJetE  ( AK8P4Raw.E() )
            ak8JetCorrector.setJetA  ( AK8Area[ak8Jet] )
            ak8JetCorrector.setRho   ( rho )
            ak8JetCorrector.setNPV   ( NPV )
            newJEC = ak8JetCorrector.getCorrection()
            AK8P4Corr = AK8P4Raw*newJEC

            if options.verbose :
                print '  len(AK8SubJetsPt) : '+str(len(AK8SubJetsPt))
            for check in  [AK8TopSubjetIndex0[ak8Jet],
                           AK8TopSubjetIndex1[ak8Jet],
                           AK8TopSubjetIndex2[ak8Jet],
                           AK8TopSubjetIndex3[ak8Jet]] :
                if options.verbose :
                    print ' check: '+str(int(check))
                if int(check) > len(AK8SubJetsPt) :
                    print '===================='
                    print ' Catastrophic failure. Index is out of range. Setup is completely wrong.'
                    print '===================='
                    BadStuff = True
                    break
            if BadStuff :
                break

            if options.verbose :
                print '    ak8TopSubjetIndex0[ak8Jet] '+str(AK8TopSubjetIndex0[ak8Jet])
                print '    ak8TopSubjetIndex1[ak8Jet] '+str(AK8TopSubjetIndex1[ak8Jet])
                print '    ak8TopSubjetIndex2[ak8Jet] '+str(AK8TopSubjetIndex2[ak8Jet])
                print '    ak8TopSubjetIndex3[ak8Jet] '+str(AK8TopSubjetIndex3[ak8Jet])
            # h_pt.Fill(AK8P4Raw.Perp(), evWeight)

            #$ Cuts based on pt and rapidity
            if AK8P4Raw.Perp() < options.minAK8Pt or abs(AK8P4Raw.Rapidity()) > options.maxAK8Rapidity :
                  continue

            #if AK8nSubJets[i] >= 3 and AK8minmass[i] > 50 and AK8P4Corr.M() > 100 :
            ak8JetsGood.append(AK8P4Corr)
            ak8JetsGoodTrimMass.append( AK8TrimmedM[ak8Jet])
            ak8JetsGoodPrunMass.append( AK8PrunedM[ak8Jet])
            ak8JetsGoodFiltMass.append( AK8FilteredM[ak8Jet])
            ak8JetsGoodSDropMass.append( AK8SDropM[ak8Jet])
            ak8JetsGoodTau1.append( AK8Tau1[ak8Jet])
            ak8JetsGoodTau2.append( AK8Tau2[ak8Jet])
            ak8JetsGoodTau3.append( AK8Tau3[ak8Jet])
            ak8JetsGoodNSubJets.append( AK8nSubJets[ak8Jet])
            ak8JetsGoodMinMass.append( AK8minmass[ak8Jet] )
            ak8JetsGoodPhi.append( AK8Phi[ak8Jet] )
            ak8JetsGoodY.append( AK8Y[ak8Jet] )
            ak8JetsGoodPt.append( AK8Pt[ak8Jet] )
            ak8JetsGoodMass.append( AK8Mass[ak8Jet] )
            ak8JetsGoodTopSubjetIndex0.append( AK8TopSubjetIndex0[ak8Jet] )
            ak8JetsGoodTopSubjetIndex1.append( AK8TopSubjetIndex1[ak8Jet] )
            ak8JetsGoodTopSubjetIndex2.append( AK8TopSubjetIndex2[ak8Jet] )
            ak8JetsGoodTopSubjetIndex3.append( AK8TopSubjetIndex3[ak8Jet] )
            NGoodAK8Jets= NGoodAK8Jets + 1


        if len(ak8JetsGood) < 1 :
            if options.verbose :
                print 'Not enough AK8 jets, skipping'
            continue
        #print 'len ak8JetsGood', len(ak8JetsGood)
        subJetBDiscs = [None]*4
        subJetBDiscs[0] = []
        subJetBDiscs[1] = []
        subJetBDiscs[2] = []
        subJetBDiscs[3] = []

        #Looping over ak8 jets
        if options.verbose :
            print 'starting good jet loop'
        for goodAK8 in range(0,len(ak8JetsGood)): 
            if ak8JetsGood[goodAK8].Perp() < options.minAK8Pt :
                continue
            #subJetBDiscs.append([])
            if BadStuff : 
                break
            BadStuff = False
            sbdisc0 = -1.
            sbdisc1 = -1.
            sbdisc2 = -1.
            sbdisc3 = -1.
            spt0 = -1.
            spt1 = -1.
            spt2 = -1.
            spt3 = -1.
            seta0 = -1.
            seta1 = -1.
            seta2 = -1.
            seta3 = -1.
            sphi0 = -1.
            sphi1 = -1.
            sphi2 = -1.
            sphi3 = -1.
            if options.verbose :
                print 'len(AK8SubJetsPt) : '+str(len(AK8SubJetsPt))
            for check in [ak8JetsGoodTopSubjetIndex0[goodAK8],
                          ak8JetsGoodTopSubjetIndex1[goodAK8],
                          ak8JetsGoodTopSubjetIndex2[goodAK8],
                          ak8JetsGoodTopSubjetIndex3[goodAK8]] :
                if options.verbose :
                    print ' check: '+str(int(check))
                if int(check) > len(AK8SubJetsPt) :
                    print '===================='
                    print ' Catastrophic failure. Index is out of range. Setup is completely wrong.'
                    print '===================='
                    BadStuff = True
                    break
            if BadStuff :
                break
            if options.verbose :
               print 'ak8JetsGoodTopSubjetIndex0[goodAK8] '+str(ak8JetsGoodTopSubjetIndex0[goodAK8])
               print 'ak8JetsGoodTopSubjetIndex1[goodAK8] '+str(ak8JetsGoodTopSubjetIndex1[goodAK8])
               print 'ak8JetsGoodTopSubjetIndex2[goodAK8] '+str(ak8JetsGoodTopSubjetIndex2[goodAK8])
               print 'ak8JetsGoodTopSubjetIndex3[goodAK8] '+str(ak8JetsGoodTopSubjetIndex3[goodAK8])

            

            if ak8JetsGoodTopSubjetIndex0[goodAK8] > -1 :
               sbdisc0 = AK8SubJetsBDisc[ int(ak8JetsGoodTopSubjetIndex0[goodAK8]) ]
               spt0    = AK8SubJetsPt[ int(ak8JetsGoodTopSubjetIndex0[goodAK8]) ]
               seta0   = AK8SubJetsEta[ int(ak8JetsGoodTopSubjetIndex0[goodAK8]) ]
               sphi0   = AK8SubJetsPhi[ int(ak8JetsGoodTopSubjetIndex0[goodAK8]) ]
               if len( subJetBDiscs ) > 1 :
                   subJetBDiscs[0].append(sbdisc0)

            if ak8JetsGoodTopSubjetIndex1[goodAK8] > -1 :
               sbdisc1 = AK8SubJetsBDisc[ int(ak8JetsGoodTopSubjetIndex1[goodAK8]) ]
               spt1    = AK8SubJetsPt[ int(ak8JetsGoodTopSubjetIndex1[goodAK8]) ]
               seta1   = AK8SubJetsEta[ int(ak8JetsGoodTopSubjetIndex1[goodAK8]) ]
               sphi1   = AK8SubJetsPhi[ int(ak8JetsGoodTopSubjetIndex1[goodAK8]) ]
               if len( subJetBDiscs ) > 1 :
                   subJetBDiscs[1].append(sbdisc1)

            if ak8JetsGoodTopSubjetIndex2[goodAK8] > -1 :
               sbdisc2 = AK8SubJetsBDisc[ int(ak8JetsGoodTopSubjetIndex2[goodAK8]) ]
               spt2    = AK8SubJetsPt[ int(ak8JetsGoodTopSubjetIndex2[goodAK8]) ]
               seta2   = AK8SubJetsEta[ int(ak8JetsGoodTopSubjetIndex2[goodAK8]) ]
               sphi2   = AK8SubJetsPhi[ int(ak8JetsGoodTopSubjetIndex2[goodAK8]) ]
               if len( subJetBDiscs ) > 1 :
                   subJetBDiscs[2].append(sbdisc2)

            if ak8JetsGoodTopSubjetIndex3[goodAK8] > -1 :
               sbdisc3 = AK8SubJetsBDisc[ int(ak8JetsGoodTopSubjetIndex3[goodAK8]) ]
               spt3    = AK8SubJetsPt[ int(ak8JetsGoodTopSubjetIndex3[goodAK8]) ]
               seta3   = AK8SubJetsEta[ int(ak8JetsGoodTopSubjetIndex3[goodAK8]) ]
               sphi3   = AK8SubJetsPhi[ int(ak8JetsGoodTopSubjetIndex3[goodAK8]) ]
               if len( subJetBDiscs ) > 1 :
                   subJetBDiscs[3].append(sbdisc3)
        # Make sure there are at least 2 jets
        if len(ak8JetsGood) < 2 :
            continue
        NPassDiJetCut = NPassDiJetCut + 1
        if options.verbose :
            print 'len ak8JetsGood', len(ak8JetsGood)

        # deltaPhi cut assures the 2 jets are back to back
        deltaPhi = ak8JetsGoodPhi[0] - ak8JetsGoodPhi[1]
        if deltaPhi > ROOT.TMath.Pi():
            deltaPhi = deltaPhi - 2*ROOT.TMath.Pi()
        if deltaPhi < -ROOT.TMath.Pi():
            deltaPhi = deltaPhi + 2*ROOT.TMath.Pi()

        # apply the pt, Y, eta and deltaPhi cuts
        ptCuts = ak8JetsGoodPt[0] > 350 and ak8JetsGoodPt[1] > 350
        deltaY = (ak8JetsGoodY[0] - ak8JetsGoodY[1])
        etaCuts = abs(ak8JetsGoodY[0]) < 2.4 and abs(ak8JetsGoodY[1]) < 2.4
        deltaPhiCut = abs(deltaPhi)>2.1
        passType11KinCuts   = ptCuts and etaCuts and deltaPhiCut
        
        if ptCuts : 
            NPassptCut = NPassptCut + 1
        if etaCuts :
            NPassetaCut = NPassetaCut + 1
        if deltaPhiCut :
            NPassdPhiCut = NPassdPhiCut + 1

        # for the first 2 jets get the subjetBDiscs
        Jet0BDiscs = []
        Jet1BDiscs = []

        # i = 0
        # while i < (ak8JetsGoodNSubJets[0]):
        #    Jet0BDiscs.append( subJetBDiscs[0][i] )
        #    i = i + 1

        # i = 0
        # while i < (ak8JetsGoodNSubJets[1]):
        #    Jet1BDiscs.append( subJetBDiscs[1][i] )
        #    i = i + 1

        if len( subJetBDiscs ) > 1 :
           for j in xrange ( 0, len( subJetBDiscs[0]) ) :
               Jet0BDiscs.append( subJetBDiscs[0][j] )
           for j in xrange ( 0, len( subJetBDiscs[1]) ) :
               Jet1BDiscs.append( subJetBDiscs[1][j] )


        # find the maximum bDisc (of all the subjets probably one is a b with the biggest bDisc)
        maxBdisc_jet0_ = -999
        maxBdisc_jet1_ = -999
        if len( Jet0BDiscs ) > 0 : 
           maxBdisc_jet0_ = max(Jet0BDiscs)
        if len( Jet1BDiscs ) > 0 : 
           maxBdisc_jet1_ = max(Jet1BDiscs)

        # calculate tau32
        tau32_jet0_ = 999
        tau32_jet1_ = 999
        if ak8JetsGoodTau2[0] != 0 :
            tau32_jet0_ = ak8JetsGoodTau3[0] / ak8JetsGoodTau2[0]
        if ak8JetsGoodTau2[1] != 0 :            
            tau32_jet1_ = ak8JetsGoodTau3[1] / ak8JetsGoodTau2[1]


        if options.verbose :
            print 'jet 0 pt '+str(ak8JetsGoodPt[0])+' bisc '+str(maxBdisc_jet0_)+' tau32 '+str(tau32_jet0_)
            print 'jet 1 pt '+str(ak8JetsGoodPt[1])+' bisc '+str(maxBdisc_jet1_)+' tau32 '+str(tau32_jet1_)

        # New definitions from Jim
        # Many top tag definitions 

        topTag0MassFat                     = ak8JetsGoodMass[0] > 140 and ak8JetsGoodMass[0] < 250
        topTag1MassFat                     = ak8JetsGoodMass[1] > 140 and ak8JetsGoodMass[1] < 250
        topTag0MassSD                      = ak8JetsGoodSDropMass[0] > 110 and ak8JetsGoodSDropMass[0] < 210
        topTag1MassSD                      = ak8JetsGoodSDropMass[1] > 110 and ak8JetsGoodSDropMass[1] < 210
        topTag0Tau32                       = tau32_jet0_ < 0.61
        topTag1Tau32                       = tau32_jet1_ < 0.61
        topTag0MinMass                     = ak8JetsGoodMinMass[0] > 50 
        topTag1MinMass                     = ak8JetsGoodMinMass[1] > 50
        topTag0MaxBdiscL                   = maxBdisc_jet0_ > 0.605 # CSVv2 loose operating point 2015_06
        topTag1MaxBdiscL                   = maxBdisc_jet1_ > 0.605 # CSVv2 loose operating point 2015_06
        topTag0MaxBdiscM                   = maxBdisc_jet0_ > 0.890 # CSVv2 medium operating point 2015_06
        topTag1MaxBdiscM                   = maxBdisc_jet1_ > 0.890 # CSVv2 medium operating point 2015_06
        topTag0MaxBdiscT                   = maxBdisc_jet0_ > 0.970 # CSVv2 tight operating point 2015_06
        topTag1MaxBdiscT                   = maxBdisc_jet1_ > 0.970 # CSVv2 tight operating point 2015_06
        topTag0MassSDTau32                 = topTag0MassSD and topTag0Tau32
        topTag1MassSDTau32                 = topTag1MassSD and topTag1Tau32
        topTag0MassSDMinMass               = topTag0MassSD and topTag0MinMass
        topTag1MassSDMinMass               = topTag1MassSD and topTag1MinMass
        topTag0MassSDMinMassTau32          = topTag0MassSD and topTag0MinMass and topTag0Tau32
        topTag1MassSDMinMassTau32          = topTag1MassSD and topTag1MinMass and topTag1Tau32
        topTag0MassSDMaxBdisc              = topTag0MassSD and topTag0MaxBdiscM
        topTag1MassSDMaxBdisc              = topTag1MassSD and topTag1MaxBdiscM
        topTag0MassSDMaxBdiscMinMass       = topTag0MassSD and topTag0MaxBdiscM and topTag0MinMass 
        topTag1MassSDMaxBdiscMinMass       = topTag1MassSD and topTag1MaxBdiscM and topTag1MinMass 
        topTag0MassSDMaxBdiscTau32         = topTag0MassSD and topTag0MaxBdiscM and topTag0Tau32 
        topTag1MassSDMaxBdiscTau32         = topTag1MassSD and topTag1MaxBdiscM and topTag1Tau32 
        topTag0MassSDMaxBdiscMinMassTau32  = topTag0MassSD and topTag0MaxBdiscM and topTag0MinMass and topTag0Tau32
        topTag1MassSDMaxBdiscMinMassTau32  = topTag1MassSD and topTag1MaxBdiscM and topTag1MinMass and topTag1Tau32
        topTag0MassFatTau32                = topTag0MassFat and topTag0Tau32
        topTag1MassFatTau32                = topTag1MassFat and topTag1Tau32
        topTag0MassFatMinMass              = topTag0MassFat and topTag0MinMass
        topTag1MassFatMinMass              = topTag1MassFat and topTag1MinMass
        topTag0MassFatMinMassTau32         = topTag0MassFat and topTag0MinMass and topTag0Tau32
        topTag1MassFatMinMassTau32         = topTag1MassFat and topTag1MinMass and topTag1Tau32
        topTag0MassFatMaxBdisc             = topTag0MassFat and topTag0MaxBdiscM
        topTag1MassFatMaxBdisc             = topTag1MassFat and topTag1MaxBdiscM
        topTag0MassFatMaxBdiscMinMass      = topTag0MassFat and topTag0MaxBdiscM and topTag0MinMass 
        topTag1MassFatMaxBdiscMinMass      = topTag1MassFat and topTag1MaxBdiscM and topTag1MinMass 
        topTag0MassFatMaxBdiscTau32        = topTag0MassFat and topTag0MaxBdiscM and topTag0Tau32 
        topTag1MassFatMaxBdiscTau32        = topTag1MassFat and topTag1MaxBdiscM and topTag1Tau32 
        topTag0MassFatMaxBdiscMinMassTau32 = topTag0MassFat and topTag0MaxBdiscM and topTag0MinMass and topTag0Tau32
        topTag1MassFatMaxBdiscMinMassTau32 = topTag1MassFat and topTag1MaxBdiscM and topTag1MinMass and topTag1Tau32

        # Many anti-tag definitions
        antiTag0minMass50                       = ak8JetsGoodMinMass[0] < 50 
        antiTag1minMass50                       = ak8JetsGoodMinMass[1] < 50
        antiTag0minMass30                       = ak8JetsGoodMinMass[0] < 30 
        antiTag1minMass30                       = ak8JetsGoodMinMass[1] < 30
        antiTag0Tau32                           = tau32_jet0_ > 0.7
        antiTag1Tau32                           = tau32_jet1_ > 0.7
        antiTag0MaxBdiscVL                      = maxBdisc_jet0_ < 0.5 # very loose
        antiTag1MaxBdiscVL                      = maxBdisc_jet1_ < 0.5 # very loose
        antiTag0MaxBdiscL                       = maxBdisc_jet0_ < 0.605 # CSVv2 loose operating point 2015_06
        antiTag1MaxBdiscL                       = maxBdisc_jet1_ < 0.605 # CSVv2 loose operating point 2015_06

        antiTag0minMass50_ReqTopMassSD         = topTag0MassSD and antiTag0minMass50
        antiTag1minMass50_ReqTopMassSD         = topTag1MassSD and antiTag1minMass50
        antiTag0minMass30_ReqTopMassSD         = topTag0MassSD and antiTag0minMass30
        antiTag1minMass30_ReqTopMassSD         = topTag1MassSD and antiTag1minMass30
        antiTag0Tau32_ReqTopMassSD             = topTag0MassSD and antiTag0Tau32
        antiTag1Tau32_ReqTopMassSD             = topTag1MassSD and antiTag1Tau32
        antiTag0MaxBdiscVL_ReqTopMassSD        = topTag0MassSD and antiTag0MaxBdiscVL
        antiTag1MaxBdiscVL_ReqTopMassSD        = topTag1MassSD and antiTag1MaxBdiscVL
        antiTag0MaxBdiscL_ReqTopMassSD         = topTag0MassSD and antiTag0MaxBdiscL
        antiTag1MaxBdiscL_ReqTopMassSD         = topTag1MassSD and antiTag1MaxBdiscL

        antiTag0minMass50_ReqTopMassSD         = topTag0MassFat and antiTag0minMass50
        antiTag1minMass50_ReqTopMassSD         = topTag1MassFat and antiTag1minMass50
        antiTag0minMass30_ReqTopMassSD         = topTag0MassFat and antiTag0minMass30
        antiTag1minMass30_ReqTopMassSD         = topTag1MassFat and antiTag1minMass30
        antiTag0Tau32_ReqTopMassSD             = topTag0MassFat and antiTag0Tau32
        antiTag1Tau32_ReqTopMassSD             = topTag1MassFat and antiTag1Tau32
        antiTag0MaxBdiscVL_ReqTopMassSD        = topTag0MassFat and antiTag0MaxBdiscVL
        antiTag1MaxBdiscVL_ReqTopMassSD        = topTag1MassFat and antiTag1MaxBdiscVL
        antiTag0MaxBdiscL_ReqTopMassSD         = topTag0MassFat and antiTag0MaxBdiscL
        antiTag1MaxBdiscL_ReqTopMassSD         = topTag1MassFat and antiTag1MaxBdiscL



        #NOTE TO MARAL: USE THESE antitags and tags 
        # no antitag ( just randomly pick a jet and use the opposite jet to probe )
        # antiTag0minMass30_topTag0MassSD   
        # antiTag0Tau32_topTag0MassSD       
        # antiTag0MaxBdiscVL_topTag0MassSD  
        # antiTag0minMass30_topTag0MassFat 
        # antiTag0minMass30
       
        # topTag1MassSD               
        # topTag1MassSDTau32                 
        # topTag1MassSDMinMass               
        # topTag1MassSDMaxBdisc
        # topTag1MassFat                             
        # topTag1MassFatMinMass              
             
        # plot pt, Y, 32, bdsic 
        # -> 4*6 tag histograms + 4*1 probe histogram for each anti tag (6) -> 30* 6 = 180 histograms
        # keep the tag name the same for each histogram
        # anti tag names are:
        # h_AntiTagMinMass30_ReqTopMassSD
        # h_AntiTagTau32_ReqTopMassSD
        # h_AntiTagMaxVdiscVL_ReqTopMassSD
        # h_AntiTagMinMass30ReqTopMassFat
        # h_AntiTagMinMass30

   


        if evWeight != -1 :
            Weight = evWeight
        else :
            Weight = 1
            


        #########################################################################################################################
        #
        #
        #
        #
        #
        #
        #########################################################################################################################
        #
        #            
        #
        #
        #
        ######################################################################################################################### 
        # start anti-tag and probe procedure

        # Randomly selecting a jet, getting the probe jet and the tag.
        if passType11KinCuts :
            NPassAllCuts = NPassAllCuts + 1
            x = ROOT.gRandom.Uniform(1.0)
            # randomly select jet 0 to be the anti-tag and jet 1 to be the probe
            if x < 0.5 :

                # No anti-tag
                h_AntiTagNone_Probe_jetPt                      .Fill(        ak8JetsGoodPt[1], Weight )
                h_AntiTagNone_Probe_jetY                       .Fill(         ak8JetsGoodY[1], Weight ) 
                h_AntiTagNone_Probe_jetTau32                   .Fill(             tau32_jet1_, Weight )
                h_AntiTagNone_Probe_jetBdisc                   .Fill(          maxBdisc_jet1_, Weight )
                if topTag1MassSD         :  
                    h_AntiTagNone_TagMassSD_jetPt              .Fill(        ak8JetsGoodPt[1], Weight )
                    h_AntiTagNone_TagMassSD_jetY               .Fill(         ak8JetsGoodY[1], Weight ) 
                    h_AntiTagNone_TagMassSD_jetTau32           .Fill(             tau32_jet1_, Weight )
                    h_AntiTagNone_TagMassSD_jetBdisc           .Fill(          maxBdisc_jet1_, Weight )
                if topTag1MassSDTau32    : 
                    h_AntiTagNone_TagMassSDTau32_jetPt         .Fill(        ak8JetsGoodPt[1], Weight )
                    h_AntiTagNone_TagMassSDTau32_jetY          .Fill(         ak8JetsGoodY[1], Weight ) 
                    h_AntiTagNone_TagMassSDTau32_jetTau32      .Fill(             tau32_jet1_, Weight )
                    h_AntiTagNone_TagMassSDTau32_jetBdisc      .Fill(          maxBdisc_jet1_, Weight )                 
                if topTag1MassSDMinMass  :  
                    h_AntiTagNone_TagMassSDMinMass_jetPt       .Fill(        ak8JetsGoodPt[1], Weight )
                    h_AntiTagNone_TagMassSDMinMass_jetY        .Fill(         ak8JetsGoodY[1], Weight ) 
                    h_AntiTagNone_TagMassSDMinMass_jetTau32    .Fill(             tau32_jet1_, Weight )
                    h_AntiTagNone_TagMassSDMinMass_jetBdisc    .Fill(          maxBdisc_jet1_, Weight ) 
                if topTag1MassSDMaxBdisc : 
                    h_AntiTagNone_TagMassSDMaxBdisc_jetPt      .Fill(        ak8JetsGoodPt[1], Weight )
                    h_AntiTagNone_TagMassSDMaxBdisc_jetY       .Fill(         ak8JetsGoodY[1], Weight ) 
                    h_AntiTagNone_TagMassSDMaxBdisc_jetTau32   .Fill(             tau32_jet1_, Weight )
                    h_AntiTagNone_TagMassSDMaxBdisc_jetBdisc   .Fill(          maxBdisc_jet1_, Weight ) 
                if topTag1MassFat        :  
                    h_AntiTagNone_TagMassFat_jetPt             .Fill(        ak8JetsGoodPt[1], Weight )
                    h_AntiTagNone_TagMassFat_jetY              .Fill(         ak8JetsGoodY[1], Weight ) 
                    h_AntiTagNone_TagMassFat_jetTau32          .Fill(             tau32_jet1_, Weight )
                    h_AntiTagNone_TagMassFat_jetBdisc          .Fill(          maxBdisc_jet1_, Weight ) 
                if topTag1MassFatMinMass :  
                    h_AntiTagNone_TagMassFatMinMass_jetPt      .Fill(        ak8JetsGoodPt[1], Weight )
                    h_AntiTagNone_TagMassFatMinMass_jetY       .Fill(         ak8JetsGoodY[1], Weight ) 
                    h_AntiTagNone_TagMassFatMinMass_jetTau32   .Fill(             tau32_jet1_, Weight )
                    h_AntiTagNone_TagMassFatMinMass_jetBdisc   .Fill(          maxBdisc_jet1_, Weight ) 

                # anti-tag minMass<30, keep jet in SD mass window
                if antiTag0minMass30_ReqTopMassSD:
                    h_AntiTagMinMass30_ReqTopMassSD_Probe_jetPt                      .Fill(        ak8JetsGoodPt[1], Weight )
                    h_AntiTagMinMass30_ReqTopMassSD_Probe_jetY                       .Fill(         ak8JetsGoodY[1], Weight ) 
                    h_AntiTagMinMass30_ReqTopMassSD_Probe_jetTau32                   .Fill(             tau32_jet1_, Weight )
                    h_AntiTagMinMass30_ReqTopMassSD_Probe_jetBdisc                   .Fill(          maxBdisc_jet1_, Weight )
                    if topTag1MassSD         :  
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSD_jetPt              .Fill(        ak8JetsGoodPt[1], Weight )
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSD_jetY               .Fill(         ak8JetsGoodY[1], Weight ) 
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSD_jetTau32           .Fill(             tau32_jet1_, Weight )
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSD_jetBdisc           .Fill(          maxBdisc_jet1_, Weight )
                    if topTag1MassSDTau32    : 
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32_jetPt         .Fill(        ak8JetsGoodPt[1], Weight )
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32_jetY          .Fill(         ak8JetsGoodY[1], Weight ) 
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32_jetTau32      .Fill(             tau32_jet1_, Weight )
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32_jetBdisc      .Fill(          maxBdisc_jet1_, Weight )                 
                    if topTag1MassSDMinMass  :  
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMinMass_jetPt       .Fill(        ak8JetsGoodPt[1], Weight )
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMinMass_jetY        .Fill(         ak8JetsGoodY[1], Weight ) 
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMinMass_jetTau32    .Fill(             tau32_jet1_, Weight )
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMinMass_jetBdisc    .Fill(          maxBdisc_jet1_, Weight ) 
                    if topTag1MassSDMaxBdisc : 
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMaxBdisc_jetPt      .Fill(        ak8JetsGoodPt[1], Weight )
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMaxBdisc_jetY       .Fill(         ak8JetsGoodY[1], Weight ) 
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMaxBdisc_jetTau32   .Fill(             tau32_jet1_, Weight )
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMaxBdisc_jetBdisc   .Fill(          maxBdisc_jet1_, Weight ) 
                    if topTag1MassFat        :  
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassFat_jetPt             .Fill(        ak8JetsGoodPt[1], Weight )
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassFat_jetY              .Fill(         ak8JetsGoodY[1], Weight ) 
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassFat_jetTau32          .Fill(             tau32_jet1_, Weight )
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassFat_jetBdisc          .Fill(          maxBdisc_jet1_, Weight ) 
                    if topTag1MassFatMinMass :  
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassFatMinMass_jetPt      .Fill(        ak8JetsGoodPt[1], Weight )
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassFatMinMass_jetY       .Fill(         ak8JetsGoodY[1], Weight ) 
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassFatMinMass_jetTau32   .Fill(             tau32_jet1_, Weight )
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassFatMinMass_jetBdisc   .Fill(          maxBdisc_jet1_, Weight ) 



            #########################################################################################################################
            #
            #
            #
            #
            #
            #
            #########################################################################################################################
            #
            #            
            #
            #
            #
            ######################################################################################################################### 
            # step2
            # randomly select jet 1 to be the anti-tag and jet 0 to be the probe
            if x > 0.5 :

                # No anti-tag
                h_AntiTagNone_Probe_jetPt                      .Fill(        ak8JetsGoodPt[0], Weight )
                h_AntiTagNone_Probe_jetY                       .Fill(         ak8JetsGoodY[0], Weight ) 
                h_AntiTagNone_Probe_jetTau32                   .Fill(             tau32_jet0_, Weight )
                h_AntiTagNone_Probe_jetBdisc                   .Fill(          maxBdisc_jet0_, Weight )
                if topTag0MassSD         :  
                    h_AntiTagNone_TagMassSD_jetPt              .Fill(        ak8JetsGoodPt[0], Weight )
                    h_AntiTagNone_TagMassSD_jetY               .Fill(         ak8JetsGoodY[0], Weight ) 
                    h_AntiTagNone_TagMassSD_jetTau32           .Fill(             tau32_jet0_, Weight )
                    h_AntiTagNone_TagMassSD_jetBdisc           .Fill(          maxBdisc_jet0_, Weight )
                if topTag0MassSDTau32    : 
                    h_AntiTagNone_TagMassSDTau32_jetPt         .Fill(        ak8JetsGoodPt[0], Weight )
                    h_AntiTagNone_TagMassSDTau32_jetY          .Fill(         ak8JetsGoodY[0], Weight ) 
                    h_AntiTagNone_TagMassSDTau32_jetTau32      .Fill(             tau32_jet0_, Weight )
                    h_AntiTagNone_TagMassSDTau32_jetBdisc      .Fill(          maxBdisc_jet0_, Weight )                 
                if topTag0MassSDMinMass  :  
                    h_AntiTagNone_TagMassSDMinMass_jetPt       .Fill(        ak8JetsGoodPt[0], Weight )
                    h_AntiTagNone_TagMassSDMinMass_jetY        .Fill(         ak8JetsGoodY[0], Weight ) 
                    h_AntiTagNone_TagMassSDMinMass_jetTau32    .Fill(             tau32_jet0_, Weight )
                    h_AntiTagNone_TagMassSDMinMass_jetBdisc    .Fill(          maxBdisc_jet0_, Weight ) 
                if topTag0MassSDMaxBdisc : 
                    h_AntiTagNone_TagMassSDMaxBdisc_jetPt      .Fill(        ak8JetsGoodPt[0], Weight )
                    h_AntiTagNone_TagMassSDMaxBdisc_jetY       .Fill(         ak8JetsGoodY[0], Weight ) 
                    h_AntiTagNone_TagMassSDMaxBdisc_jetTau32   .Fill(             tau32_jet0_, Weight )
                    h_AntiTagNone_TagMassSDMaxBdisc_jetBdisc   .Fill(          maxBdisc_jet0_, Weight ) 
                if topTag0MassFat        :  
                    h_AntiTagNone_TagMassFat_jetPt             .Fill(        ak8JetsGoodPt[0], Weight )
                    h_AntiTagNone_TagMassFat_jetY              .Fill(         ak8JetsGoodY[0], Weight ) 
                    h_AntiTagNone_TagMassFat_jetTau32          .Fill(             tau32_jet0_, Weight )
                    h_AntiTagNone_TagMassFat_jetBdisc          .Fill(          maxBdisc_jet0_, Weight ) 
                if topTag0MassFatMinMass :  
                    h_AntiTagNone_TagMassFatMinMass_jetPt      .Fill(        ak8JetsGoodPt[0], Weight )
                    h_AntiTagNone_TagMassFatMinMass_jetY       .Fill(         ak8JetsGoodY[0], Weight ) 
                    h_AntiTagNone_TagMassFatMinMass_jetTau32   .Fill(             tau32_jet0_, Weight )
                    h_AntiTagNone_TagMassFatMinMass_jetBdisc   .Fill(          maxBdisc_jet0_, Weight ) 

                # anti-tag minMass<30, keep jet in SD mass window
                if antiTag1minMass30_ReqTopMassSD:
                    h_AntiTagMinMass30_ReqTopMassSD_Probe_jetPt                      .Fill(        ak8JetsGoodPt[0], Weight )
                    h_AntiTagMinMass30_ReqTopMassSD_Probe_jetY                       .Fill(         ak8JetsGoodY[0], Weight ) 
                    h_AntiTagMinMass30_ReqTopMassSD_Probe_jetTau32                   .Fill(             tau32_jet0_, Weight )
                    h_AntiTagMinMass30_ReqTopMassSD_Probe_jetBdisc                   .Fill(          maxBdisc_jet0_, Weight )
                    if topTag0MassSD         :  
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSD_jetPt              .Fill(        ak8JetsGoodPt[0], Weight )
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSD_jetY               .Fill(         ak8JetsGoodY[0], Weight ) 
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSD_jetTau32           .Fill(             tau32_jet0_, Weight )
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSD_jetBdisc           .Fill(          maxBdisc_jet0_, Weight )
                    if topTag0MassSDTau32    : 
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32_jetPt         .Fill(        ak8JetsGoodPt[0], Weight )
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32_jetY          .Fill(         ak8JetsGoodY[0], Weight ) 
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32_jetTau32      .Fill(             tau32_jet0_, Weight )
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32_jetBdisc      .Fill(          maxBdisc_jet0_, Weight )                 
                    if topTag0MassSDMinMass  :  
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMinMass_jetPt       .Fill(        ak8JetsGoodPt[0], Weight )
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMinMass_jetY        .Fill(         ak8JetsGoodY[0], Weight ) 
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMinMass_jetTau32    .Fill(             tau32_jet0_, Weight )
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMinMass_jetBdisc    .Fill(          maxBdisc_jet0_, Weight ) 
                    if topTag0MassSDMaxBdisc : 
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMaxBdisc_jetPt      .Fill(        ak8JetsGoodPt[0], Weight )
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMaxBdisc_jetY       .Fill(         ak8JetsGoodY[0], Weight ) 
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMaxBdisc_jetTau32   .Fill(             tau32_jet0_, Weight )
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMaxBdisc_jetBdisc   .Fill(          maxBdisc_jet0_, Weight ) 
                    if topTag0MassFat        :  
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassFat_jetPt             .Fill(        ak8JetsGoodPt[0], Weight )
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassFat_jetY              .Fill(         ak8JetsGoodY[0], Weight ) 
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassFat_jetTau32          .Fill(             tau32_jet0_, Weight )
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassFat_jetBdisc          .Fill(          maxBdisc_jet0_, Weight ) 
                    if topTag0MassFatMinMass :  
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassFatMinMass_jetPt      .Fill(        ak8JetsGoodPt[0], Weight )
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassFatMinMass_jetY       .Fill(         ak8JetsGoodY[0], Weight ) 
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassFatMinMass_jetTau32   .Fill(             tau32_jet0_, Weight )
                        h_AntiTagMinMass30_ReqTopMassSD_TagMassFatMinMass_jetBdisc   .Fill(          maxBdisc_jet0_, Weight ) 

               
 

# print "======================"
# print "~~~ Cut Flow Table ~~~"
# print "======================"
# print "Good AK8 Jets: " + str(NGoodAK8Jets)
# print " "
# print "Passing 2 Jets Cut: " + str(NPassDiJetCut)
# print " "
# print "Passing pt Cut (>350 GeV): " + str(NPassptCut)
# print "Passing eta Cut (<2.4): " + str(NPassetaCut)
# print "Passing \Delta \phi Cut (>2.1): " + str(NPassdPhiCut)
# print "Passing pt, eta, and \Delta \phi Cut: " + str(NPassAllCuts)
# print " "
# print "~~~~ Soft Drop Mass req ~~~~"
# print "Good AntiTagged Jets: " + str(NGoodAntiTaggedEventsSD)
# print "Good AntiTag TopTag Jet Pairs: " + str(NGoodAntiTagTopTagPairsSD)
# print "~~~~~~~ AK8 Mass req ~~~~~~~"
# print "Good AntiTagged Jets: " + str(NGoodAntiTaggedEventsFJ)
# print "Good AntiTag TopTag Jet Pairs: " + str(NGoodAntiTagTopTagPairsFJ)
# print "~~~~~~~~ No Mass req ~~~~~~~"
# print "Good AntiTagged Jets: " + str(NGoodAntiTaggedEventsNM)
# print "Good AntiTag TopTag Jet Pairs: " + str(NGoodAntiTagTopTagPairsNM)
# print " "
# print "====== Tau32 > .7 Anti-tags ======="
# print "~~~~ Soft Drop Mass req ~~~~"
# print "Good AntiTagged Jets: " + str(NGoodAntiTaggedEventsSDT)
# print "Good AntiTag TopTag Jet Pairs: " + str(NGoodAntiTagTopTagPairsSDT)
# print "~~~~~~~ AK8 Mass req ~~~~~~~"
# print "Good AntiTagged Jets: " + str(NGoodAntiTaggedEventsFJT)
# print "Good AntiTag TopTag Jet Pairs: " + str(NGoodAntiTagTopTagPairsFJT)
# print "~~~~~~~~ No Mass req ~~~~~~~"
# print "Good AntiTagged Jets: " + str(NGoodAntiTaggedEventsNMT)
# print "Good AntiTag TopTag Jet Pairs: " + str(NGoodAntiTagTopTagPairsNMT)
# print " "
# print "~~~~~~~~ No Anti-tag ~~~~~~~"
# print "TopTag Jet Pairs: " + str(NGoodAntiTagTopTagPairsFree)
f.cd()
f.Write()
f.Close()
