#! /usr/bin/env python

##################
# Editting flags
# #!!! Error or Something fishy
# #{ #} Start and stop loop (so reading indents isn't so bad
# #^ Plotting
# #~ Tree
# #@ New section (muons, electrons, AK4 jets etc.)
# #$ Cuts
# @@@ Incomplete
##################




#@ CONFIGURATION

from optparse import OptionParser
parser = OptionParser()

parser.add_option('--files', type='string', action='store',
                  dest='files',
                  help='Input files')

parser.add_option('--outname', type='string', action='store',
                  default='outplots.root',
                  dest='outname',
                  help='Name of output file')

parser.add_option('--verbose', type='int', action='store',
                  default=0,
                  dest='verbose',
                  help='Print debugging info')

parser.add_option('--selection', type='int', action='store',
                  default=-1,
                  dest='selection',
                  help='Leptonic (0), SemiLeptonic (1) or AllHadronic (2)')

parser.add_option('--maxevents', type='int', action='store',
                  default=-1,
                  dest='maxevents',
                  help='Number of events to run. -1 is all events')

parser.add_option('--maxjets', type='int', action='store',
                  default=1,
                  dest='maxjets',
                  help='Number of jets to plot. To plot all jets, set to a big number like 999')

parser.add_option('--bdisc', type='string', action='store',
                  default=0.605,
                  dest='bdisc',
                  help='combinedInclusiveSecondaryVertexV2BJetTags')

parser.add_option('--bDiscMin', type='float', action='store',
                  default=0.605,
                  ##  using loose OP- CSVv2L from  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation74X50ns  
                  ##previously this was 0.423
                  dest='bDiscMin',
                  help='Minimum b discriminator - loose')

#parser.add_option('--bDiscMinM', type='float', action='store',
#                  default=0.890, ##  using medium OP 0.890 from  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation74X50ns 
#                  dest='bDiscMinM',
#                  help='Minimum b discriminator - Medium')

#parser.add_option('--bDiscMinT', type='float', action='store',
#                  default=0.970, ##  using tight OP 0.970 from  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation74X50ns 
#                  dest='bDiscMinT',
#                  help='Minimum b discriminator - Tight')

parser.add_option('--minMuonPt', type='float', action='store',
                  default=50.,
                  dest='minMuonPt',
                  help='Minimum PT for muons')

parser.add_option('--maxMuonEta', type='float', action='store',
                  default=2.1,
                  dest='maxMuonEta',
                  help='Maximum muon pseudorapidity')

parser.add_option('--minElectronPt', type='float', action='store',
                  default=50.,
                  dest='minElectronPt',
                  help='Minimum PT for electrons')

parser.add_option('--maxElectronEta', type='float', action='store',
                  default=2.5,
                  dest='maxElectronEta',
                  help='Maximum electron pseudorapidity')


parser.add_option('--minAK4Pt', type='float', action='store',
                  default=50.,
                  dest='minAK4Pt',
                  help='Minimum PT for AK4 jets')

parser.add_option('--maxAK4Rapidity', type='float', action='store',
                  default=2.4,
                  dest='maxAK4Rapidity',
                  help='Maximum AK4 rapidity')

parser.add_option('--minAK8Pt', type='float', action='store',
                  default=200.,
                  dest='minAK8Pt',
                  help='Minimum PT for AK8 jets')

parser.add_option('--maxAK8Rapidity', type='float', action='store',
                  default=2.4,
                  dest='maxAK8Rapidity',
                  help='Maximum AK8 rapidity')

parser.add_option('--minAK8JetHt', type='float', action='store',
                  default=400,
                  dest='minAK8JetHt',
                  help='HT cut for all-hadronic')

parser.add_option('--hemisphereDPhi', type='float', action='store',
                  default=1.0,
                  dest='hemisphereDPhi',
                  help='DR cut to define hemispheres for semilep analysis')


parser.add_option('--minMassCut', type='float', action='store',
                  default=50.,
                  dest='minMassCut',
                  help='Minimum Mass Pairing Cut for CMS Combined Tagger')

parser.add_option('--mAK8GroomedMinCut', type='float', action='store',
                  default=110.,
                  dest='mAK8GroomedMinCut',
                  help='Groomed minimum mass Cut for CMS Combined Tagger: Defaulted for Soft Drop Mass')

parser.add_option('--mAK8GroomedMaxCut', type='float', action='store',
                  default=210.,
                  dest='mAK8GroomedMaxCut',
                  help='Groomed maximum mass Cut for CMS Combined Tagger: Defaulted for Soft Drop Mass')


parser.add_option('--mAK8GroomedWMinCut', type='float', action='store',
                  default=60.,
                  dest='mAK8GroomedWMinCut',
                  help='Groomed minimum mass Cut for CMS Combined Tagger: Defaulted for Soft Drop Mass')

parser.add_option('--mAK8GroomedWMaxCut', type='float', action='store',
                  default=100.,
                  dest='mAK8GroomedWMaxCut',
                  help='Groomed maximum mass Cut for CMS Combined Tagger: Defaulted for Soft Drop Mass')




parser.add_option('--tau32Cut', type='float', action='store',
                  default=0.62,
                  dest='tau32Cut',
                  help='Tau3 / Tau2 n-subjettiness cut for CMS Combined Tagger')

parser.add_option('--tau21Cut', type='float', action='store',
                  default=0.5,
                  dest='tau21Cut',
                  help='Tau2 / Tau1 n-subjettiness cut for CMS Combined Tagger')


parser.add_option('--metMin', type='float', action='store',
                  default=None,
                  dest='metMin',
                  help='Minimum MET')

parser.add_option('--htLepMin', type='float', action='store',
                  default=None,
                  dest='htLepMin',
                  help='Minimum HT lep')


parser.add_option('--stMin', type='float', action='store',
                  default=None,
                  dest='stMin',
                  help='Minimum ST = pt lep + MET + HT')

parser.add_option('--useTriangular', metavar='F', action='store_true',
                  default=True,
                  dest='useTriangular',
                  help='Use triangular cut to reject electron QCD?')

parser.add_option('--ignore2D', metavar='I', action='store_true',
                  default=False,
                  dest='ignore2D',
                  help='Ignore the 2D cut')

parser.add_option('--BkgEst', action='store_true',
                  default=False,
                  dest='BkgEst',
                  help='QCD Background Estimation process')

parser.add_option('--FlatSample', action='store_true',
                  default=False,
                  dest='deweightFlat',
                  help='unweights flat samples')

parser.add_option('--negativeWeights', action='store_true',
                  default=False,
                  dest='negativeWeights',
                  help='Are there negative weights? aMC@NLO and madgraph have these')

parser.add_option('--isMC', action='store_true',
                  default=False,
                  dest='isMC',
                  help='is it MC?')

parser.add_option('--isZprime', action='store_true',
                  default=False,
                  dest='isZprime',
                  help='is it Zprime?')

parser.add_option('--isttbar', action='store_true',
                  default=False,
                  dest='isttbar',
                  help='is it ttbar?')

parser.add_option('--isRSG', action='store_true',
		  default=False,
		  dest='isRSG',
		  help='is it RSG?')

parser.add_option('--getGenInfo', action='store_true',
                  default=False,
                  dest='getGenInfo',
                  help='Get ttbar event gen-level info?')


parser.add_option('--xrootd', type='string', action='store',
                  default=None,
                  dest='xrootd',
                  help='xrootd redirector. Try root://cmsxrootd.fnal.gov//')

parser.add_option('--applyFilters', action='store_true',
                  default=False,
                  dest='applyFilters',
                  help='Apply MET filters')


parser.add_option('--applyTriggers', action='store_true',
                  default=False,
                  dest='applyTriggers',
                  help='Apply triggers')

parser.add_option('--quickSelect', action='store_true',
                  default=False,
                  dest='quickSelect',
                  help='Require AK8 pt > min immediately to remove low-pt events')


parser.add_option('--quickSelectminAK8Pt', type='float', action='store',
                  default=350.,
                  dest='quickSelectminAK8Pt',
                  help='Minimum PT for quick select using AK8 jets')


parser.add_option('--njobs', type='int', action='store',
                  default=None,
                  dest='njobs',
                  help='Number of jobs in total')

parser.add_option('--job', type='int', action='store',
                  default=None,
                  dest='job',
                  help='This job number')



parser.add_option('--puFile', type='string', action='store',
                  default="PUweight20160316.root",
                  dest='puFile',
                  help='Name of Pileup Reweighting File')

parser.add_option('--puDistNOM', type='string', action='store',
                  default="MyDataPileupHistogram.root",
                  dest='puDistNOM',
                  help='Name of Pileup Distribution File - Nominal')

parser.add_option('--puDistUP', type='string', action='store',
                  default="MyDataPileupHistogramUP.root",
                  dest='puDistUP',
                  help='Name of Pileup Distribution File - 5% Up')

parser.add_option('--puDistDN', type='string', action='store',
                  default="MyDataPileupHistogramDN.root",
                  dest='puDistDN',
                  help='Name of Pileup Distribution File - 5% Down')

parser.add_option('--showEvents', type='int', action='store',
                  default=None,
                  dest='showEvents',
                  help='Number of events to print')


parser.add_option('--writeTree', action='store_true',
                  default=False,
                  dest='writeTree',
                  help='Write "baby tree"')

parser.add_option('--keyBasedCleaning', action='store_true',
                  default=False,
                  dest='keyBasedCleaning',
                  help='Do cleaning based on PF keys')

parser.add_option('--reweightTopPt', action='store_true',
                  default=False,
                  dest='reweightTopPt',
                  help='Reweight top pt spectrum')

(options, args) = parser.parse_args()
argv = []


#@ FWLITE STUFF

import ROOT
import sys
from DataFormats.FWLite import Events, Handle
#ROOT.gROOT.Macro("rootlogon.C")
from leptonic_nu_z_component import solve_nu_tmass, solve_nu
import copy
from array import array
from math import *
ROOT.gSystem.Load("libAnalysisPredictedDistribution")

#@ Labels and Handles
h_genPartPt = Handle("std::vector<float>")
l_genPartPt = ("genPart" , "genPartPt")
h_genPartEta = Handle("std::vector<float>")
l_genPartEta = ("genPart" , "genPartEta")
h_genPartPhi = Handle("std::vector<float>")
l_genPartPhi = ("genPart" , "genPartPhi")
h_genPartMass = Handle("std::vector<float>")
l_genPartMass = ("genPart" , "genPartMass")
h_genPartID = Handle("std::vector<float>")
l_genPartID = ("genPart" , "genPartID")
h_genPartStatus = Handle("std::vector<float>")
l_genPartStatus = ("genPart" , "genPartStatus")
h_genPartMomID = Handle("std::vector<float>")
l_genPartMomID = ("genPart" , "genPartMom0ID")

#@ GenJets
h_genJetsAK8Pt = Handle("std::vector<float>")
l_genJetsAK8Pt = ("genJetsAK8" , "genJetsAK8Pt")
h_genJetsAK8Eta = Handle("std::vector<float>")
l_genJetsAK8Eta = ("genJetsAK8" , "genJetsAK8Eta")
h_genJetsAK8Phi = Handle("std::vector<float>")
l_genJetsAK8Phi = ("genJetsAK8" , "genJetsAK8Phi")
h_genJetsAK8Mass = Handle("std::vector<float>")
l_genJetsAK8Mass = ("genJetsAK8" , "genJetsAK8Mass")


h_genJetsAK8SoftDropPt = Handle("std::vector<float>")
l_genJetsAK8SoftDropPt = ("genJetsAK8SoftDrop" , "genJetsAK8SoftDropPt")
h_genJetsAK8SoftDropEta = Handle("std::vector<float>")
l_genJetsAK8SoftDropEta = ("genJetsAK8SoftDrop" , "genJetsAK8SoftDropEta")
h_genJetsAK8SoftDropPhi = Handle("std::vector<float>")
l_genJetsAK8SoftDropPhi = ("genJetsAK8SoftDrop" , "genJetsAK8SoftDropPhi")
h_genJetsAK8SoftDropMass = Handle("std::vector<float>")
l_genJetsAK8SoftDropMass = ("genJetsAK8SoftDrop" , "genJetsAK8SoftDropMass")


#muon labels and handles
h_muPt = Handle("std::vector<float>")
l_muPt = ("muons" , "muPt")
h_muEta = Handle("std::vector<float>")
l_muEta = ("muons" , "muEta")
h_muPhi = Handle("std::vector<float>")
l_muPhi = ("muons" , "muPhi")
h_muTight = Handle("std::vector<float>")
l_muTight = ("muons" , "muIsTightMuon" )
h_muLoose = Handle("std::vector<float>")
l_muLoose = ("muons" , "muIsLooseMuon" )
h_muMass = Handle("std::vector<float>")
l_muMass = ("muons" , "muMass")
h_muDz = Handle("std::vector<float>")
l_muDz = ("muons", "muDz")
h_muCharge = Handle("std::vector<float>")
l_muCharge = ("muons", "muCharge")

h_muIso04 = Handle("std::vector<float>")
l_muIso04 = ("muons", "muIso04")

h_muKey = Handle("std::vector<std::vector<int> >")
l_muKey = ("muonKeys")

#electron label and handles
h_elPt = Handle("std::vector<float>")
l_elPt = ("electrons" , "elPt")
h_elEta = Handle("std::vector<float>")
l_elEta = ("electrons" , "elEta")
h_elPhi = Handle("std::vector<float>")
l_elPhi = ("electrons" , "elPhi")
h_elTight = Handle("std::vector<float>")
l_elTight = ("electrons" , "elisTight" )
h_elLoose = Handle("std::vector<float>")
l_elLoose = ("electrons" , "elisLoose" )
h_eldEtaIn = Handle("std::vector<float>")
l_eldEtaIn = ( "electrons" , "eldEtaIn" )
h_eldPhiIn = Handle("std::vector<float>")
l_eldPhiIn = ( "electrons" , "eldPhiIn" )
h_elHoE = Handle("std::vector<float>")
l_elHoE = ( "electrons" , "elHoE" )
h_elfull5x5siee = Handle("std::vector<float>")
l_elfull5x5siee = ( "electrons" , "elfull5x5siee")
h_elE = Handle("std::vector<float>")
l_elE = ( "electrons" , "elE" )
h_elD0 = Handle("std::vector<float>")
l_elD0 = ( "electrons" , "elD0" )
h_elDz = Handle("std::vector<float>")
l_elDz = ( "electrons" , "elDz")
h_elIso03 = Handle("std::vector<float>")
l_elIso03 = ( "electrons" , "elIso03" )
h_elisVeto = Handle("std::vector<float>")
l_elisVeto = ( "electrons" , "elisVeto" )
h_elhasMatchedConVeto = Handle("std::vector<float>")
l_elhasMatchedConVeto = ( "electrons" , "elhasMatchedConVeto" )
h_elooEmooP = Handle("std::vector<float>")
l_elooEmooP = ( "electrons" , "elooEmooP" )
h_elMass = Handle("std::vector<float>")
l_elMass = ( "electrons" , "elMass" )
h_elscEta = Handle("std::vector<float>")
l_elscEta = ( "electrons" , "elscEta" )
h_elCharge = Handle("std::vector<float>")
l_elCharge = ( "electrons" , "elCharge" )

h_elKey = Handle("std::vector<std::vector<int> >")
l_elKey = ( "electronKeys" )

#AK4 Jet Label and Handles
h_jetsAK4Pt = Handle("std::vector<float>")
l_jetsAK4Pt = ("jetsAK4" , "jetAK4Pt") #
h_jetsAK4Eta = Handle("std::vector<float>")
l_jetsAK4Eta = ("jetsAK4" , "jetAK4Eta")
h_jetsAK4Phi = Handle("std::vector<float>")
l_jetsAK4Phi = ("jetsAK4" , "jetAK4Phi")
h_jetsAK4Mass = Handle("std::vector<float>")
l_jetsAK4Mass = ("jetsAK4" , "jetAK4Mass")
h_jetsAK4Energy = Handle("std::vector<float>")
l_jetsAK4Energy = ("jetsAK4" , "jetAK4E") 
h_jetsAK4JEC = Handle("std::vector<float>")
l_jetsAK4JEC = ("jetsAK4" , "jetAK4jecFactor0") 
h_jetsAK4CSV = Handle("std::vector<float>")
l_jetsAK4CSV = ("jetsAK4" , "jetAK4CSV")
h_jetsAK4NumDaughters = Handle("std::vector<float>")
l_jetsAK4NumDaughters = ( "jetsAK4" , "jetAK4numberOfDaughters" )
h_jetsAK4Area = Handle("std::vector<float>")
l_jetsAK4Area = ( "jetsAK4" , "jetAK4jetArea" )

h_pv_chi = Handle("std::vector<float>")
l_pv_chi = ( "vertexInfo", "chi" )
h_pv_rho = Handle("std::vector<float>")
l_pv_rho = ( "vertexInfo", "rho" )
h_pv_z = Handle("std::vector<float>")
l_pv_z = ( "vertexInfo", "z" )
h_pv_ndof = Handle("std::vector<std::int>")
l_pv_ndof = ( "vertexInfo", "ndof" )

h_puNtrueInt = Handle("std::int")
l_puNtrueInt = ( "eventUserData" , "puNtrueInt" )

h_jetsAK4Keys = Handle("std::vector<std::vector<int> >")
l_jetsAK4Keys = ( "jetKeysAK4" , "" )

h_jetsAK4nHadEnergy = Handle("std::vector<float>")
l_jetsAK4nHadEnergy = ("jetsAK4" , "jetAK4neutralHadronEnergy")
h_jetsAK4nEMEnergy = Handle("std::vector<float>")
l_jetsAK4nEMEnergy = ("jetsAK4" , "jetAK4neutralEmEnergy")
h_jetsAK4HFHadronEnergy = Handle("std::vector<float>")
l_jetsAK4HFHadronEnergy = ("jetsAK4" , "jetAK4HFHadronEnergy")
h_jetsAK4cHadEnergy = Handle("std::vector<float>")
l_jetsAK4cHadEnergy = ("jetsAK4" , "jetAK4chargedHadronEnergy")
h_jetsAK4cEMEnergy = Handle("std::vector<float>")
l_jetsAK4cEMEnergy = ("jetsAK4" , "jetAK4chargedEmEnergy")
h_jetsAK4numDaughters = Handle("std::vector<float>")
l_jetsAK4numDaughters = ("jetsAK4" , "jetAK4numberOfDaughters")
h_jetsAK4cMultip = Handle("std::vector<float>")
l_jetsAK4cMultip = ("jetsAK4" , "jetAK4chargedMultiplicity")
h_jetsAK4Y = Handle("std::vector<float>")
l_jetsAK4Y = ("jetsAK4" , "jetAK4Y")

#Rho
h_rho = Handle("double")
l_rho = ("fixedGridRhoFastjetAll", "")

#MET label and Handles
h_metPt = Handle("std::vector<float>")
l_metPt = ("metNoHF" , "metNoHFPt")
h_metPx = Handle("std::vector<float>")
l_metPx = ("metNoHF" , "metNoHFPx")
h_metPy = Handle("std::vector<float>")
l_metPy = ("metNoHF" , "metNoHFPy")
h_metPhi = Handle("std::vector<float>")
l_metPhi = ("metNoHF" , "metNoHFPhi")


# vector<float>             "metFull"                   "metFullPhi"      "b2gEDMNtuples"
# vector<float>             "metFull"                   "metFullPt"       "b2gEDMNtuples"
# vector<float>             "metFull"                   "metFullPx"       "b2gEDMNtuples"
# vector<float>             "metFull"                   "metFullPy"       "b2gEDMNtuples"
# vector<float>             "metFull"                   "metFulluncorPhi"   "b2gEDMNtuples"
# vector<float>             "metFull"                   "metFulluncorPt"   "b2gEDMNtuples"
# vector<float>             "metFull"                   "metFulluncorSumEt"   "b2gEDMNtuples"
# vector<float>             "metNoHF"                   "metNoHFPhi"      "b2gEDMNtuples"
# vector<float>             "metNoHF"                   "metNoHFPt"       "b2gEDMNtuples"
# vector<float>             "metNoHF"                   "metNoHFPx"       "b2gEDMNtuples"
# vector<float>             "metNoHF"                   "metNoHFPy"       "b2gEDMNtuples"
# vector<float>             "metNoHF"                   "metNoHFuncorPhi"   "b2gEDMNtuples"
# vector<float>             "metNoHF"                   "metNoHFuncorPt"   "b2gEDMNtuples"
# vector<float>             "metNoHF"                   "metNoHFuncorSumEt"   "b2gEDMNtuples"

# Generator info
if options.isMC :
    h_generator = Handle("GenEventInfoProduct")
    l_generator = ("generator" , "", "SIM" )
    h_lhe = Handle("LHEEventProduct")
    l_lhe = ("externalLHEProducer", "")
    
#AK8 Jets label and Handles
h_jetsAK8Pt = Handle("std::vector<float>")
l_jetsAK8Pt = ("jetsAK8" , "jetAK8Pt") #
h_jetsAK8Eta = Handle("std::vector<float>")
l_jetsAK8Eta = ("jetsAK8" , "jetAK8Eta")
h_jetsAK8Phi = Handle("std::vector<float>")
l_jetsAK8Phi = ("jetsAK8" , "jetAK8Phi")
h_jetsAK8Mass = Handle("std::vector<float>")
l_jetsAK8Mass = ("jetsAK8" , "jetAK8Mass")
h_jetsAK8Energy = Handle("std::vector<float>")
l_jetsAK8Energy = ("jetsAK8" , "jetAK8E") 
h_jetsAK8Y = Handle("std::vector<float>")
l_jetsAK8Y = ("jetsAK8" , "jetAK8Y")

h_jetsAK8JEC = Handle("std::vector<float>")
l_jetsAK8JEC = ("jetsAK8" , "jetAK8jecFactor0")

h_jetsAK8JERup   = Handle("std::vector<float>")
l_jetsAK8JERup   = ("jetsAK8" , "jetAK8JERup")
h_jetsAK8JERdown = Handle("std::vector<float>")
l_jetsAK8JERdown = ("jetsAK8" , "jetAK8JERdown")

h_jetsAK8SmearedE = Handle("std::vector<float>")
l_jetsAK8SmearedE = ("jetsAK8" , "jetAK8SmearedE")
h_jetsAK8SmearedEta = Handle("std::vector<float>")
l_jetsAK8SmearedEta = ("jetsAK8" , "jetAK8SmearedPEta")
h_jetsAK8SmearedPhi = Handle("std::vector<float>")
l_jetsAK8SmearedPhi = ("jetsAK8" , "jetAK8SmearedPhi")
h_jetsAK8SmearedPt = Handle("std::vector<float>")
l_jetsAK8SmearedPt = ("jetsAK8" , "jetAK8SmearedPt")


h_jetsAK8GenJetE = Handle("std::vector<float>")
l_jetsAK8GenJetE = ("jetsAK8" , "jetAK8GenJetE")
h_jetsAK8GenJetEta = Handle("std::vector<float>")
l_jetsAK8GenJetEta = ("jetsAK8" , "jetAK8GenJetEta")
h_jetsAK8GenJetPhi = Handle("std::vector<float>")
l_jetsAK8GenJetPhi = ("jetsAK8" , "jetAK8GenJetPhi")
h_jetsAK8GenJetPt = Handle("std::vector<float>")
l_jetsAK8GenJetPt = ("jetsAK8" , "jetAK8GenJetPt")
h_jetsAK8GenJetY = Handle("std::vector<float>")
l_jetsAK8GenJetY = ("jetsAK8" , "jetAK8GenJetY")


h_jetsAK8nHadEnergy = Handle("std::vector<float>")
l_jetsAK8nHadEnergy = ("jetsAK8" , "jetAK8neutralHadronEnergy")
h_jetsAK8nEMEnergy = Handle("std::vector<float>")
l_jetsAK8nEMEnergy = ("jetsAK8" , "jetAK8neutralEmEnergy")
h_jetsAK8HFHadronEnergy = Handle("std::vector<float>")
l_jetsAK8HFHadronEnergy = ("jetsAK8" , "jetAK8HFHadronEnergy")
h_jetsAK8cHadEnergy = Handle("std::vector<float>")
l_jetsAK8cHadEnergy = ("jetsAK8" , "jetAK8chargedHadronEnergy")
h_jetsAK8cEMEnergy = Handle("std::vector<float>")
l_jetsAK8cEMEnergy = ("jetsAK8" , "jetAK8chargedEmEnergy")

h_jetsAK8nHadEnergyFrac = Handle("std::vector<float>")
l_jetsAK8nHadEnergyFrac = ("jetsAK8" , "jetAK8neutralHadronEnergyFrac")
h_jetsAK8nEMEnergyFrac = Handle("std::vector<float>")
l_jetsAK8nEMEnergyFrac = ("jetsAK8" , "jetAK8neutralEmEnergyFrac")
h_jetsAK8HFHadronEnergyFrac = Handle("std::vector<float>")
l_jetsAK8HFHadronEnergyFrac = ("jetsAK8" , "jetAK8HFHadronEnergyFrac")
h_jetsAK8cHadEnergyFrac = Handle("std::vector<float>")
l_jetsAK8cHadEnergyFrac = ("jetsAK8" , "jetAK8chargedHadronEnergyFrac")
h_jetsAK8cEMEnergyFrac = Handle("std::vector<float>")
l_jetsAK8cEMEnergyFrac = ("jetsAK8" , "jetAK8chargedEmEnergyFrac")

h_jetsAK8numDaughters = Handle("std::vector<float>")
l_jetsAK8numDaughters = ("jetsAK8" , "jetAK8numberOfDaughters")
h_jetsAK8cMultip = Handle("std::vector<float>")
l_jetsAK8cMultip = ("jetsAK8" , "jetAK8chargedMultiplicity")
h_jetsAK8nMultip = Handle("std::vector<float>")
l_jetsAK8nMultip = ("jetsAK8" , "jetAK8neutralMultiplicity")
l_jetsAK8numDaughters = ("jetsAK8" , "jetAK8numberOfDaughters")
h_jetsAK8cHadMultip = Handle("std::vector<float>")
l_jetsAK8cHadMultip = ("jetsAK8" , "jetAK8chargedHadronMultiplicity")
h_jetsAK8nHadMultip = Handle("std::vector<float>")
l_jetsAK8nHadMultip = ("jetsAK8" , "jetAK8neutralHadronMultiplicity")


h_jetsAK8Keys = Handle("std::vector<std::vector<int> >")
l_jetsAK8Keys = ( "jetKeysAK8" , "" )

h_jetsAK8TrimMass = Handle("std::vector<float>")
l_jetsAK8TrimMass = ("jetsAK8", "jetAK8trimmedMass" )
h_jetsAK8PrunMass = Handle("std::vector<float>")
l_jetsAK8PrunMass = ("jetsAK8", "jetAK8prunedMass" )
h_jetsAK8FiltMass = Handle("std::vector<float>")
l_jetsAK8FiltMass = ("jetsAK8", "jetAK8filteredMass" )
h_jetsAK8SoftDropMass = Handle("std::vector<float>")
l_jetsAK8SoftDropMass = ("jetsAK8", "jetAK8softDropMass" )
h_jetsAK8Tau1 = Handle("std::vector<float>")
l_jetsAK8Tau1 = ("jetsAK8", "jetAK8tau1" )
h_jetsAK8Tau2 = Handle("std::vector<float>")
l_jetsAK8Tau2 = ("jetsAK8", "jetAK8tau2" )
h_jetsAK8Tau3 = Handle("std::vector<float>")
l_jetsAK8Tau3 = ("jetsAK8", "jetAK8tau3" )
h_jetsAK8nSubJets = Handle("std::vector<float>")
l_jetsAK8nSubJets = ("jetsAK8", "jetAK8nSubJets" )
h_jetsAK8minmass = Handle("std::vector<float>")
l_jetsAK8minmass = ("jetsAK8", "jetAK8minmass" )
h_jetsAK8Area = Handle("std::vector<float>")
l_jetsAK8Area = ( "jetsAK8" , "jetAK8jetArea" )


h_jetsAK8CSV = Handle("std::vector<float>")               # use this ***
l_jetsAK8CSV = ( "jetsAK8" , "jetAK8CSV" )

#CMSTT W mass
#h_jetsAK8wMass = Handle("std::vector<float>")
#l_jetsAK8wMass = ("jetsAK8", "jetAK8wMass")

h_jetsAK8CmsTopTagSubjetIndex0       = Handle("std::vector<float>")
l_jetsAK8CmsTopTagSubjetIndex0       = ("jetsAK8", "jetAK8topSubjetIndex0")
h_jetsAK8CmsTopTagSubjetIndex1       = Handle("std::vector<float>")
l_jetsAK8CmsTopTagSubjetIndex1       = ("jetsAK8", "jetAK8topSubjetIndex1")
h_jetsAK8CmsTopTagSubjetIndex2       = Handle("std::vector<float>")
l_jetsAK8CmsTopTagSubjetIndex2       = ("jetsAK8", "jetAK8topSubjetIndex2")
h_jetsAK8CmsTopTagSubjetIndex3       = Handle("std::vector<float>")
l_jetsAK8CmsTopTagSubjetIndex3       = ("jetsAK8", "jetAK8topSubjetIndex3")

h_subjetsCmsTopTagBDisc        = Handle( "std::vector<float>")
l_subjetsCmsTopTagBDisc        = ("subjetsCmsTopTag", "subjetCmsTopTagCSV") 
h_subjetsCmsTopTagPt           = Handle( "std::vector<float>")
l_subjetsCmsTopTagPt           = ("subjetsCmsTopTag", "subjetCmsTopTagPt")
h_subjetsCmsTopTagEta          = Handle( "std::vector<float>")
l_subjetsCmsTopTagEta          = ("subjetsCmsTopTag", "subjetCmsTopTagEta")
h_subjetsCmsTopTagPhi          = Handle( "std::vector<float>")
l_subjetsCmsTopTagPhi          = ("subjetsCmsTopTag", "subjetCmsTopTagPhi")
h_subjetsCmsTopTagMass         = Handle( "std::vector<float>")
l_subjetsCmsTopTagMass         = ("subjetsCmsTopTag", "subjetCmsTopTagMass")
h_subjetsCmsTopTagArea         = Handle( "std::vector<float>")
l_subjetsCmsTopTagArea         = ("subjetsCmsTopTag", "subjetCmsTopTagjetArea")
h_subjetsCmsTopTagnumDaughters = Handle( "std::vector<float>")
l_subjetsCmsTopTagnumDaughters = ("subjetsCmsTopTag", "subjetCmsTopTagnumberOfDaughters")
h_subjetsCmsTopTagY            = Handle( "std::vector<float>")
l_subjetsCmsTopTagY            = ("subjetsCmsTopTag", "subjetCmsTopTagY")

h_subjetsCmsTopTagJEC0         = Handle( "std::vector<float>")
l_subjetsCmsTopTagJEC0         = ("subjetsCmsTopTag", "subjetCmsTopTagjecFactor0")
h_subjetsCmsTopTagJERup        = Handle( "std::vector<float>")
l_subjetsCmsTopTagJERup        = ("subjetsCmsTopTag", "subjetCmsTopTagJERup")
h_subjetsCmsTopTagJERdown      = Handle( "std::vector<float>")
l_subjetsCmsTopTagJERdown      = ("subjetsCmsTopTag", "subjetCmsTopTagJERdown")

h_subjetsCmsTopTagSmearedE     = Handle("std::vector<float>")
l_subjetsCmsTopTagSmearedE     = ("subjetsCmsTopTag" , "subjetCmsTopTagSmearedE")
h_subjetsCmsTopTagSmearedEta   = Handle("std::vector<float>")
l_subjetsCmsTopTagSmearedEta   = ("subjetsCmsTopTag" , "subjetCmsTopTagSmearedPEta")
h_subjetsCmsTopTagSmearedPhi   = Handle("std::vector<float>")
l_subjetsCmsTopTagSmearedPhi   = ("subjetsCmsTopTag" , "subjetCmsTopTagSmearedPhi")
h_subjetsCmsTopTagSmearedPt    = Handle("std::vector<float>")
l_subjetsCmsTopTagSmearedPt    = ("subjetsCmsTopTag" , "subjetCmsTopTagSmearedPt")



h_jetsAK8SoftDropSubjetIndex0    = Handle("std::vector<float>")
l_jetsAK8SoftDropSubjetIndex0    = ("jetsAK8", "jetAK8vSubjetIndex0")
h_jetsAK8SoftDropSubjetIndex1    = Handle("std::vector<float>")
l_jetsAK8SoftDropSubjetIndex1    = ("jetsAK8", "jetAK8vSubjetIndex1")

h_subjetsSoftDropBDisc           = Handle( "std::vector<float>")
l_subjetsSoftDropBDisc           = ("subjetsAK8", "subjetAK8CSV") 
h_subjetsSoftDropPt              = Handle( "std::vector<float>")
l_subjetsSoftDropPt              = ("subjetsAK8", "subjetAK8Pt")
h_subjetsSoftDropEta             = Handle( "std::vector<float>")
l_subjetsSoftDropEta             = ("subjetsAK8", "subjetAK8Eta")
h_subjetsSoftDropPhi             = Handle( "std::vector<float>")
l_subjetsSoftDropPhi             = ("subjetsAK8", "subjetAK8Phi")
h_subjetsSoftDropMass            = Handle( "std::vector<float>")
l_subjetsSoftDropMass            = ("subjetsAK8", "subjetAK8Mass")
h_subjetsSoftDropArea            = Handle( "std::vector<float>")
l_subjetsSoftDropArea            = ("subjetsAK8", "subjetAK8jetArea")
h_subjetsSoftDropnumDaughters    = Handle( "std::vector<float>")
l_subjetsSoftDropnumDaughters    = ("subjetsAK8", "subjetAK8numberOfDaughters")
h_subjetsSoftDropY               = Handle( "std::vector<float>")
l_subjetsSoftDropY               = ("subjetsAK8", "subjetAK8Y")

h_subjetsSoftDropJEC0            = Handle( "std::vector<float>")
l_subjetsSoftDropJEC0            = ("subjetsAK8", "subjetAK8jecFactor0")
h_subjetsSoftDropJERup           = Handle( "std::vector<float>")
l_subjetsSoftDropJERup           = ("subjetsAK8", "subjetAK8JERup")
h_subjetsSoftDropJERdown         = Handle( "std::vector<float>")
l_subjetsSoftDropJERdown         = ("subjetsAK8", "subjetAK8JERdown")

h_subjetsSoftDropSmearedE        = Handle("std::vector<float>")
l_subjetsSoftDropSmearedE        = ("subjetsAK8" , "subjetAK8SmearedE")
h_subjetsSoftDropSmearedEta      = Handle("std::vector<float>")
l_subjetsSoftDropSmearedEta      = ("subjetsAK8" , "subjetAK8SmearedPEta")
h_subjetsSoftDropSmearedPhi      = Handle("std::vector<float>")
l_subjetsSoftDropSmearedPhi      = ("subjetsAK8" , "subjetAK8SmearedPhi")
h_subjetsSoftDropSmearedPt       = Handle("std::vector<float>")
l_subjetsSoftDropSmearedPt       = ("subjetsAK8" , "subjetAK8SmearedPt")

h_subjetsSoftDropGenJetE         = Handle("std::vector<float>")
l_subjetsSoftDropGenJetE         = ("subjetsAK8" , "subjetAK8GenJetE")
h_subjetsSoftDropGenJetEta       = Handle("std::vector<float>")
l_subjetsSoftDropGenJetEta       = ("subjetsAK8" , "subjetAK8GenJetEta")
h_subjetsSoftDropGenJetPhi       = Handle("std::vector<float>")
l_subjetsSoftDropGenJetPhi       = ("subjetsAK8" , "subjetAK8GenJetPhi")
h_subjetsSoftDropGenJetPt        = Handle("std::vector<float>")
l_subjetsSoftDropGenJetPt        = ("subjetsAK8" , "subjetAK8GenJetPt")

h_subjetsSoftDropJetArea         = Handle("std::vector<float>")
l_subjetsSoftDropJetArea         = ("subjetsAK8" , "subjetAK8jetArea")
h_subjetsSoftDropPartonFlavour   = Handle("std::vector<float>")
l_subjetsSoftDropPartonFlavour   = ("subjetsAK8" , "subjetAK8PartonFlavour")





# MET and HCAL Filter handles
h_filterNameStrings = Handle( "std::vector<std::string>")
l_filterNameStrings = ("METUserData", "triggerNameTree")
h_filterBits = Handle( "std::vector<float>")
l_filterBits = ("METUserData", "triggerBitTree")
h_filterPrescales = Handle( "std::vector<int>")
l_filterPrescales = ("METUserData", "triggerPrescaleTree")
h_HBHEfilter = Handle("bool")
l_HBHEfilter = ("HBHENoiseFilterResultProducer", "HBHENoiseFilterResult")

# Triggers
h_triggerNameStrings = Handle( "std::vector<std::string>")
l_triggerNameStrings = ("TriggerUserData", "triggerNameTree")
h_triggerBits = Handle( "std::vector<float>")
l_triggerBits = ("TriggerUserData", "triggerBitTree")
h_triggerPrescales = Handle( "std::vector<int>")
l_triggerPrescales = ("TriggerUserData", "triggerPrescaleTree")


# _____ _   _ _____  _    _ _______   _    _ _____  _____ _______ _____ 
#|_   _| \ | |  __ \| |  | |__   __| | |  | |_   _|/ ____|__   __/ ____|
#  | | |  \| | |__) | |  | |  | |    | |__| | | | | (___    | | | (___  
#  | | | . ` |  ___/| |  | |  | |    |  __  | | |  \___ \   | |  \___ \ 
# _| |_| |\  | |    | |__| |  | |    | |  | |_| |_ ____) |  | |  ____) |
#|_____|_| \_|_|     \____/   |_|    |_|  |_|_____|_____/   |_| |_____/ 

#@ MODMASS
FmodMass = ROOT.TFile("ModMass_2015_09_22.root")

h_modMass_Fat            = FmodMass.Get( "h_mAK8_ModMass"           ).Clone()
h_modMass_SD             = FmodMass.Get( "h_mSDropAK8_ModMass"      ).Clone()
h_modMass_Fat_jet0       = FmodMass.Get( "h_mAK8_ModMass_jet0"      ).Clone()
h_modMass_SD_jet0        = FmodMass.Get( "h_mSDropAK8_ModMass_jet0" ).Clone()
h_modMass_Fat_jet1       = FmodMass.Get( "h_mAK8_ModMass_jet1"      ).Clone()
h_modMass_SD_jet1        = FmodMass.Get( "h_mSDropAK8_ModMass_jet1" ).Clone()

h_modMass_Fat      .SetName("h_modMass_Fat")  
h_modMass_SD       .SetName("h_modMass_SD")  
h_modMass_Fat_jet0 .SetName("h_modMass_Fat_jet0")  
h_modMass_SD_jet0  .SetName("h_modMass_SD_jet0")  
h_modMass_Fat_jet1 .SetName("h_modMass_Fat_jet1")  
h_modMass_SD_jet1  .SetName("h_modMass_SD_jet1")  

ROOT.SetOwnership( h_modMass_Fat       , False )
ROOT.SetOwnership( h_modMass_SD        , False )
ROOT.SetOwnership( h_modMass_Fat_jet0  , False )
ROOT.SetOwnership( h_modMass_SD_jet0   , False )
ROOT.SetOwnership( h_modMass_Fat_jet1  , False )
ROOT.SetOwnership( h_modMass_SD_jet1   , False )

print "h_modMass_Fat      integral  " + str( h_modMass_Fat     .Integral() )
print "h_modMass_SD       integral  " + str( h_modMass_SD      .Integral() )
print "h_modMass_Fat_jet0 integral  " + str( h_modMass_Fat_jet0.Integral() )
print "h_modMass_SD_jet0  integral  " + str( h_modMass_SD_jet0 .Integral() )
print "h_modMass_Fat_jet1 integral  " + str( h_modMass_Fat_jet1.Integral() )
print "h_modMass_SD_jet1  integral  " + str( h_modMass_SD_jet1 .Integral() )

# Remake the modMass jet mass distributions in the range 140-250 for fat jet mass, 110-210 for SD mass
# binWidth = h_mAK8.GetBinWidth(1)
# nBinsX   = h_mAK8.GetNbinsX()
# nBinsmodMassFat   = (250-140)*nBinsX
# nBinsmodMassSD    = (210-110)*nBinsX
# h_modMass_Fat=ROOT.TH1F("h_modMass_Fat","",nBinsmodMassFat,140,250)
# h_modMass_SD =ROOT.TH1F("h_modMass_SD","",nBinsmodMassSD,110,210)

# # for i in range( 1, nBinsX ):
# #     print 'bin '+str(i)+' contents '+ str(h_mAK8.GetBinContent(i))+' width '+ str(h_mAK8.GetBinWidth(i))+' low edge '+ str(h_mAK8.GetBinLowEdge(i))
# #     if h_mAK8.GetBinLowEdge(i) >=140 and (h_mAK8.GetBinLowEdge(i)+binWidth)<=250:
# #         h_modMass_Fat.Fill( h_mAK8.GetBinCenter(i), h_mAK8.GetBinContent(i) )
# #         print 'fillFat '+str( h_mAK8.GetBinContent(i) )
# #     if h_mAK8.GetBinLowEdge(i) >=110 and (h_mAK8.GetBinLowEdge(i)+binWidth)<=210:
# #         h_modMass_SD.Fill(h_mAK8.GetBinCenter(i), h_mSDropAK8.GetBinContent(i) )
# #         print 'fillSD '+str( h_mSDropAK8.GetBinContent(i) )



#@ Get MISTAG RATE HISTOGRAMS

if options.isMC:
  Fmistag = ROOT.TFile("MistagRate_2015_09_25.root")
else:
  Fmistag = ROOT.TFile("MistagRateBigBins_JetHT_knash_crab_Run2015D_PromptReco_v3_Sep25_v74x_V7_25ns_All_2015_09_28.root")

h_mistag_vs_jetPt_TagMassSD           = Fmistag.Get("h_mistag_AntiTagMinMass30_ReqTopMassSD_TagMassSD"         ).Clone()
h_mistag_vs_jetPt_TagMassSDTau32      = Fmistag.Get("h_mistag_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32"    ).Clone()
h_mistag_vs_jetPt_TagMassSDMinMass    = Fmistag.Get("h_mistag_AntiTagMinMass50_ReqTopMassSD_TagMassSDMinMass"  ).Clone()
h_mistag_vs_jetPt_TagMassFatMinMass   = Fmistag.Get("h_mistag_AntiTagMinMass50_ReqTopMassFat_TagMassFatMinMass").Clone()
# h_mistag_vs_jetPt_TagMassFat          = Fmistag.Get("h_mistag_vs_jetPt_TagMassFat").Clone()

h_mistag_vs_jetPt_TagMassSD           .SetName("h_mistag_AntiTagMinMass30_ReqTopMassSD_TagMassSD"         )
h_mistag_vs_jetPt_TagMassSDTau32      .SetName("h_mistag_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32"    )
h_mistag_vs_jetPt_TagMassSDMinMass    .SetName("h_mistag_AntiTagMinMass50_ReqTopMassSD_TagMassSDMinMass"  )
h_mistag_vs_jetPt_TagMassFatMinMass   .SetName("h_mistag_AntiTagMinMass50_ReqTopMassFat_TagMassFatMinMass")


ROOT.SetOwnership( h_mistag_vs_jetPt_TagMassSD         , False )
ROOT.SetOwnership( h_mistag_vs_jetPt_TagMassSDTau32    , False )
ROOT.SetOwnership( h_mistag_vs_jetPt_TagMassSDMinMass  , False )
ROOT.SetOwnership( h_mistag_vs_jetPt_TagMassFatMinMass , False )
# ROOT.SetOwnership( h_mistag_vs_jetPt_TagMassFat        , False )


#@ Pileup reweighting
if options.isMC:
    if options.puFile != None:
        fPUweight      = ROOT.TFile(options.puFile)
        hPUweight      = fPUweight.Get("PUweight_true")
        hPUweight_MBup = fPUweight.Get("PUweight_true_MBup")
        hPUweight_MBdn = fPUweight.Get("PUweight_true_MBdn")
    if options.puDistNOM != None:
        fPU_NOM = ROOT.TFile(options.puDistNOM)
        hPU_NOM = fPU_NOM.Get("pileup")
    if options.puDistUP != None:
        fPU_UP = ROOT.TFile(options.puDistUP)
        hPU_UP = fPU_UP.Get("pileup")
    if options.puDistDN != None:
        fPU_DN = ROOT.TFile(options.puDistDN)
        hPU_DN = fPU_DN.Get("pileup")


#@ Reweight top function

reweightTopPt = ROOT.TF1("reweightTopPt", "6.5e-4 + 0.9", 0, 13000)


#   ____  _    _ _______ _____  _    _ _______   _____   ____   ____ _______ 
#  / __ \| |  | |__   __|  __ \| |  | |__   __| |  __ \ / __ \ / __ \__   __|
# | |  | | |  | |  | |  | |__) | |  | |  | |    | |__) | |  | | |  | | | |   
# | |  | | |  | |  | |  |  ___/| |  | |  | |    |  _  /| |  | | |  | | | |   
# | |__| | |__| |  | |  | |    | |__| |  | |    | | \ \| |__| | |__| | | |   
#  \____/ \____/   |_|  |_|     \____/   |_|    |_|  \_\\____/ \____/  |_|   
                                                                            

# @@@ Create output root file

f = ROOT.TFile(options.outname, "RECREATE")
f.cd()

#~ Tree initializations

if options.writeTree  and options.selection == 1 : 
    TreeSemiLept = ROOT.TTree("TreeSemiLept", "TreeSemiLept")
    SemiLeptTrig        = array('i', [0]  )
    BoosttypE           = array('i', [0] )
    SemiLeptWeight      = array('f', [0.] )
    
    FatJetCorr          = array('f', [-1.])
    FatJetCorrUp        = array('f', [-1.])
    FatJetCorrDn        = array('f', [-1.])
    FatJetMassCorr      = array('f', [-1.])
    FatJetMassCorrUp    = array('f', [-1.])
    FatJetMassCorrDn    = array('f', [-1.])
    JetPtSmearFactor    = array('f', [-1.])
    JetPtSmearFactorUp  = array('f', [-1.])
    JetPtSmearFactorDn  = array('f', [-1.])
    JetEtaScaleFactor   = array('f', [-1.])
    JetPhiScaleFactor   = array('f', [-1.])
    JetMatchedGenJetPt  = array('f', [-1.])
    FatJetPtRaw         = array('f', [-1.])
    FatJetEtaRaw        = array('f', [-1.])
    FatJetPhiRaw        = array('f', [-1.])
    FatJetRapRaw        = array('f', [-1.])
    FatJetMassRaw       = array('f', [-1.])
    FatJetP             = array('f', [-1.])
    FatJetPt            = array('f', [-1.])
    FatJetEta           = array('f', [-1.])
    FatJetPhi           = array('f', [-1.])
    FatJetRap           = array('f', [-1.])
    FatJetEnergy        = array('f', [-1.])
    FatJetBDisc         = array('f', [-1.])
    FatJetRhoRatio      = array('f', [-1.])
    FatJetMass          = array('f', [-1.])
    FatJetMassSoftDrop  = array('f', [-1.])
    FatJetMassSDsumSubjetCorr        = array('f', [-1.] )
    FatJetMassSDsumSubjetRaw         = array('f', [-1.] )
    FatJetMassSDsumSubjetCorrUp      = array('f', [-1.] )
    FatJetMassSDsumSubjetCorrDn      = array('f', [-1.] )
    FatJetMassSDsumSubjetCorrSmear   = array('f', [-1.] )
    FatJetMassSDsumSubjetCorrSmearUp = array('f', [-1.] )
    FatJetMassSDsumSubjetCorrSmearDn = array('f', [-1.] )
    FatJetMassPruned    = array('f', [-1.])
    FatJetMassFiltered  = array('f', [-1.])
    FatJetMassTrimmed   = array('f', [-1.])
    FatJetTau1          = array('f', [-1.]) 
    FatJetTau2          = array('f', [-1.]) 
    FatJetTau3          = array('f', [-1.]) 
    FatJetTau32         = array('f', [-1.])
    FatJetTau21         = array('f', [-1.]) 
    FatJetSDnsubjets    = array('f', [-1.])
    FatJetSDbdiscW      = array('f', [-1.])
    FatJetSDbdiscB      = array('f', [-1.])
    FatJetSDmaxbdisc    = array('f', [-1.])
    FatJetSDsubjetWpt   = array('f', [-1.])
    FatJetSDsubjetWmass = array('f', [-1.])
    FatJetSDsubjetWp4   = array('f', [-1.])
    FatJetSDsubjetBpt   = array('f', [-1.])
    FatJetSDsubjetBmass = array('f', [-1.])
    FatJetSDsubjetBp4   = array('f', [-1.])
    FatJetCMSmaxbdisc   = array('f', [-1.])
    FatJetCMSnsubjets   = array('f', [-1.])
    FatJetCMSminMass    = array('f', [-1.])
    FatJetCMSm01        = array('f', [-1.])
    FatJetCMSm02        = array('f', [-1.])
    FatJetCMSm12        = array('f', [-1.])
    FatJetNHF           = array('f', [-1.])   
    FatJetCHF           = array('f', [-1.])   
    FatJetNEF           = array('f', [-1.])   
    FatJetCEF           = array('f', [-1.])   
    FatJetNC            = array('f', [-1.])   
    FatJetNCH           = array('f', [-1.])   
    FatJetSDsubjet0pt   = array('f', [-1.])   
    FatJetSDsubjet0mass = array('f', [-1.])   
    FatJetSDsubjet0area = array('f', [-1.])   
    FatJetSDsubjet0flav = array('f', [-1.])   
    FatJetSDsubjet1pt   = array('f', [-1.])   
    FatJetSDsubjet1mass = array('f', [-1.])   
    FatJetSDsubjet1area = array('f', [-1.])   
    FatJetSDsubjet1flav = array('f', [-1.])   
    BJetbDisc           = array('f', [-1.])
    BJetPt              = array('f', [-1.])
    BJetEta             = array('f', [-1.])
    BJetPhi             = array('f', [-1.])
    BJetMass            = array('f', [-1.])
    Type2PairMass       = array('f', [-1.])
    Type2PairPt         = array('f', [-1.])

    LeptonType          = array('i', [-1])
    LeptonPt            = array('f', [-1.])
    LeptonEta           = array('f', [-1.])
    LeptonPhi           = array('f', [-1.])
    LeptonPx            = array('f', [-1.])
    LeptonPy            = array('f', [-1.])
    LeptonPz            = array('f', [-1.])
    LeptonEnergy        = array('f', [-1.])
    LeptonIso           = array('f', [-1.])
    LeptonPtRel         = array('f', [-1.])
    LeptonDRMin         = array('f', [-1.])

    SemiLepMETpx        = array('f', [-1.])
    SemiLepMETpy        = array('f', [-1.])
    SemiLepMETpt        = array('f', [-1.])
    SemiLepMETphi       = array('f', [-1.])
    SemiLepNvtx         = array('f', [-1.])
    SemiLepEventWeight  = array('f', [-1.])

    SemilLepTTmass      = array('f', [-1.])
    DeltaPhiLepFat      = array('f', [-1.]) 

    AK4bDisc            = array('f', [-1.])
    NearestAK4JetPt     = array('f', [-1.])
    NearestAK4JetEta    = array('f', [-1.])
    NearestAK4JetPhi    = array('f', [-1.])
    NearestAK4JetMass   = array('f', [-1.])

    SemiLeptRunNum        = array('f', [-1.])   
    SemiLeptLumiBlock     = array('f', [-1.])   
    SemiLeptEventNum      = array('f', [-1.])   

    
    TreeSemiLept.Branch('SemiLeptTrig'        , SemiLeptTrig        ,  'SemiLeptTrig/I'        )
    TreeSemiLept.Branch('SemiLeptWeight'      , SemiLeptWeight      ,  'SemiLeptWeight/F'      )    
    TreeSemiLept.Branch('BoosttypE'           , BoosttypE           ,  'BoosttypE/I'           )
    TreeSemiLept.Branch('FatJetCorr'          , FatJetCorr          ,  'FatJetCorr/F'          )
    TreeSemiLept.Branch('FatJetCorrUp'        , FatJetCorrUp        ,  'FatJetCorrUp/F'        )
    TreeSemiLept.Branch('FatJetCorrDn'        , FatJetCorrDn        ,  'FatJetCorrDn/F'        )
    TreeSemiLept.Branch('FatJetMassCorr'          , FatJetMassCorr          ,  'FatJetMassCorr/F'          )
    TreeSemiLept.Branch('FatJetMassCorrUp'        , FatJetMassCorrUp        ,  'FatJetMassCorrUp/F'        )
    TreeSemiLept.Branch('FatJetMassCorrDn'        , FatJetMassCorrDn        ,  'FatJetMassCorrDn/F'        )
    TreeSemiLept.Branch('JetPtSmearFactor'  , JetPtSmearFactor   , 'JetPtSmearFactor/F'   ) 
    TreeSemiLept.Branch('JetPtSmearFactorUp', JetPtSmearFactorUp , 'JetPtSmearFactorUp/F' ) 
    TreeSemiLept.Branch('JetPtSmearFactorDn', JetPtSmearFactorDn , 'JetPtSmearFactorDn/F' ) 
    TreeSemiLept.Branch('JetEtaScaleFactor' , JetEtaScaleFactor  , 'JetEtaScaleFactor/F'  ) 
    TreeSemiLept.Branch('JetPhiScaleFactor' , JetPhiScaleFactor  , 'JetPhiScaleFactor/F'  ) 
    TreeSemiLept.Branch('JetMatchedGenJetPt', JetMatchedGenJetPt , 'JetMatchedGenJetPt/F' ) 
    TreeSemiLept.Branch('FatJetPtRaw'          , FatJetPtRaw           , 'FatJetPtRaw/F'           )
    TreeSemiLept.Branch('FatJetEtaRaw'         , FatJetEtaRaw          , 'FatJetEtaRaw/F'          ) 
    TreeSemiLept.Branch('FatJetPhiRaw'         , FatJetPhiRaw          , 'FatJetPhiRaw/F'          ) 
    TreeSemiLept.Branch('FatJetRapRaw'         , FatJetRapRaw          , 'FatJetRapRaw/F'          ) 
    TreeSemiLept.Branch('FatJetMassRaw'        , FatJetMassRaw         , 'FatJetMassRaw/F'         ) 
    TreeSemiLept.Branch('FatJetP'             , FatJetP             ,  'FatJetP/F'             )
    TreeSemiLept.Branch('FatJetPt'            , FatJetPt            ,  'FatJetPt/F'            )
    TreeSemiLept.Branch('FatJetEta'           , FatJetEta           ,  'FatJetEta/F'           )
    TreeSemiLept.Branch('FatJetPhi'           , FatJetPhi           ,  'FatJetPhi/F'           )
    TreeSemiLept.Branch('FatJetRap'           , FatJetRap           ,  'FatJetRap/F'           )
    TreeSemiLept.Branch('FatJetEnergy'        , FatJetEnergy        ,  'FatJetEnergy/F'        )
    TreeSemiLept.Branch('FatJetBDisc'         , FatJetBDisc         ,  'FatJetBDisc/F'         )
    TreeSemiLept.Branch('FatJetRhoRatio'      , FatJetRhoRatio      ,  'FatJetRhoRatio/F'      )
    TreeSemiLept.Branch('FatJetMass'          , FatJetMass          ,  'FatJetMass/F'          )
    TreeSemiLept.Branch('FatJetMassSoftDrop'  , FatJetMassSoftDrop  ,  'FatJetMassSoftDrop/F'  )
    TreeSemiLept.Branch('FatJetMassSDsumSubjetCorr'        , FatJetMassSDsumSubjetCorr         , 'FatJetMassSDsumSubjetCorr/F'        )   
    TreeSemiLept.Branch('FatJetMassSDsumSubjetRaw'         , FatJetMassSDsumSubjetRaw          , 'FatJetMassSDsumSubjetRaw/F'         )   
    TreeSemiLept.Branch('FatJetMassSDsumSubjetCorrUp'      , FatJetMassSDsumSubjetCorrUp       , 'FatJetMassSDsumSubjetCorrUp/F'      )   
    TreeSemiLept.Branch('FatJetMassSDsumSubjetCorrDn'      , FatJetMassSDsumSubjetCorrDn       , 'FatJetMassSDsumSubjetCorrDn/F'      )   
    TreeSemiLept.Branch('FatJetMassSDsumSubjetCorrSmear'   , FatJetMassSDsumSubjetCorrSmear    , 'FatJetMassSDsumSubjetCorrSmear/F'   )   
    TreeSemiLept.Branch('FatJetMassSDsumSubjetCorrSmearUp' , FatJetMassSDsumSubjetCorrSmearUp  , 'FatJetMassSDsumSubjetCorrSmearUp/F' )   
    TreeSemiLept.Branch('FatJetMassSDsumSubjetCorrSmearDn' , FatJetMassSDsumSubjetCorrSmearDn  , 'FatJetMassSDsumSubjetCorrSmearDn/F' )   
    TreeSemiLept.Branch('FatJetMassPruned'    , FatJetMassPruned    ,  'FatJetMassPruned/F'    )
    TreeSemiLept.Branch('FatJetMassFiltered'  , FatJetMassFiltered  ,  'FatJetMassFiltered/F'  )
    TreeSemiLept.Branch('FatJetMassTrimmed'   , FatJetMassTrimmed   ,  'FatJetMassTrimmed/F'   )
    TreeSemiLept.Branch('FatJetTau1'          , FatJetTau1          ,  'FatJetTau1/F'          )
    TreeSemiLept.Branch('FatJetTau2'          , FatJetTau2          ,  'FatJetTau2/F'          )
    TreeSemiLept.Branch('FatJetTau3'          , FatJetTau3          ,  'FatJetTau3/F'          )
    TreeSemiLept.Branch('FatJetTau32'         , FatJetTau32         ,  'FatJetTau32/F'         )
    TreeSemiLept.Branch('FatJetTau21'         , FatJetTau21         ,  'FatJetTau21/F'         )
    TreeSemiLept.Branch('FatJetSDnsubjets'    , FatJetSDnsubjets    ,  'FatJetSDnsubjets/F'    )
    TreeSemiLept.Branch('FatJetSDbdiscW'      , FatJetSDbdiscW      ,  'FatJetSDbdiscW/F'      )
    TreeSemiLept.Branch('FatJetSDbdiscB'      , FatJetSDbdiscB      ,  'FatJetSDbdiscB/F'      )
    TreeSemiLept.Branch('FatJetSDmaxbdisc'    , FatJetSDmaxbdisc    ,  'FatJetSDmaxbdisc/F'    )
    TreeSemiLept.Branch('FatJetSDsubjetWpt'   , FatJetSDsubjetWpt   ,  'FatJetSDsubjetWpt/F'   )
    TreeSemiLept.Branch('FatJetSDsubjetWmass' , FatJetSDsubjetWmass ,  'FatJetSDsubjetWmass/F' )
    TreeSemiLept.Branch('FatJetSDsubjetWp4'   , FatJetSDsubjetWp4   ,  'FatJetSDsubjetWp4/F'   )
    TreeSemiLept.Branch('FatJetSDsubjetBpt'   , FatJetSDsubjetBpt   ,  'FatJetSDsubjetBpt/F'   )
    TreeSemiLept.Branch('FatJetSDsubjetBmass' , FatJetSDsubjetBmass ,  'FatJetSDsubjetBmass/F' )
    TreeSemiLept.Branch('FatJetSDsubjetBp4'   , FatJetSDsubjetBp4   ,  'FatJetSDsubjetBp4/F'   )
    TreeSemiLept.Branch('FatJetSDsubjet0pt'   , FatJetSDsubjet0pt   ,  'FatJetSDsubjet0pt/F'   ) 
    TreeSemiLept.Branch('FatJetSDsubjet0mass' , FatJetSDsubjet0mass ,  'FatJetSDsubjet0mass/F' ) 
    TreeSemiLept.Branch('FatJetSDsubjet0area' , FatJetSDsubjet0area ,  'FatJetSDsubjet0area/F' ) 
    TreeSemiLept.Branch('FatJetSDsubjet0flav' , FatJetSDsubjet0flav ,  'FatJetSDsubjet0flav/F' ) 
    TreeSemiLept.Branch('FatJetSDsubjet1pt'   , FatJetSDsubjet1pt   ,  'FatJetSDsubjet1pt/F'   ) 
    TreeSemiLept.Branch('FatJetSDsubjet1mass' , FatJetSDsubjet1mass ,  'FatJetSDsubjet1mass/F' ) 
    TreeSemiLept.Branch('FatJetSDsubjet1area' , FatJetSDsubjet1area ,  'FatJetSDsubjet1area/F' ) 
    TreeSemiLept.Branch('FatJetSDsubjet1flav' , FatJetSDsubjet1flav ,  'FatJetSDsubjet1flav/F' ) 
    TreeSemiLept.Branch('FatJetCMSmaxbdisc'   , FatJetCMSmaxbdisc   ,  'FatJetCMSmaxbdisc/F'   )
    TreeSemiLept.Branch('FatJetCMSnsubjets'   , FatJetCMSnsubjets   ,  'FatJetCMSnsubjets/F'   )
    TreeSemiLept.Branch('FatJetCMSminMass'    , FatJetCMSminMass    ,  'FatJetCMSminMass/F'    )
    TreeSemiLept.Branch('FatJetCMSm01'        , FatJetCMSm01        ,  'FatJetCMSm01/F'        )
    TreeSemiLept.Branch('FatJetCMSm02'        , FatJetCMSm02        ,  'FatJetCMSm02/F'        )
    TreeSemiLept.Branch('FatJetCMSm12'        , FatJetCMSm12        ,  'FatJetCMSm12/F'        )
    TreeSemiLept.Branch('FatJetNHF'           , FatJetNHF           ,  'FatJetNHF/F'           )  
    TreeSemiLept.Branch('FatJetCHF'           , FatJetCHF           ,  'FatJetCHF/F'           )  
    TreeSemiLept.Branch('FatJetNEF'           , FatJetNEF           ,  'FatJetNEF/F'           )  
    TreeSemiLept.Branch('FatJetCEF'           , FatJetCEF           ,  'FatJetCEF/F'           )  
    TreeSemiLept.Branch('FatJetNC'            , FatJetNC            ,  'FatJetNC/F'            ) 
    TreeSemiLept.Branch('FatJetNCH'           , FatJetNCH           ,  'FatJetNCH/F'           )    
    TreeSemiLept.Branch('BJetbDisc'           , BJetbDisc           ,  'BJetbDisc/F'           )
    TreeSemiLept.Branch('BJetPt'              , BJetPt              ,  'BJetPt/F'              )
    TreeSemiLept.Branch('BJetEta'             , BJetEta             ,  'BJetEta/F'             )
    TreeSemiLept.Branch('BJetPhi'             , BJetPhi             ,  'BJetPhi/F'             )
    TreeSemiLept.Branch('BJetMass'            , BJetMass            ,  'BJetMass/F'            )
    TreeSemiLept.Branch('Type2PairMass'       , Type2PairMass       ,  'Type2PairMass/F'       )
    TreeSemiLept.Branch('Type2PairPt'         , Type2PairPt         ,  'Type2PairPt/F'         )
    TreeSemiLept.Branch('LeptonType'          , LeptonType          ,  'LeptonType/I'          )
    TreeSemiLept.Branch('LeptonPt'            , LeptonPt            ,  'LeptonPt/F'            )
    TreeSemiLept.Branch('LeptonEta'           , LeptonEta           ,  'LeptonEta/F'           )
    TreeSemiLept.Branch('LeptonPhi'           , LeptonPhi           ,  'LeptonPhi/F'           )
    TreeSemiLept.Branch('LeptonPx'            , LeptonPx            ,  'LeptonPx/F'            )
    TreeSemiLept.Branch('LeptonPy'            , LeptonPy            ,  'LeptonPy/F'            )
    TreeSemiLept.Branch('LeptonPz'            , LeptonPz            ,  'LeptonPz/F'            )
    TreeSemiLept.Branch('LeptonEnergy'        , LeptonEnergy        ,  'LeptonEnergy/F'        )
    TreeSemiLept.Branch('LeptonIso'           , LeptonIso           ,  'LeptonIso/F'           )
    TreeSemiLept.Branch('LeptonPtRel'         , LeptonPtRel         ,  'LeptonPtRel/F'         )
    TreeSemiLept.Branch('LeptonDRMin'         , LeptonDRMin         ,  'LeptonDRMin/F'         )        
    TreeSemiLept.Branch('SemiLepMETpx'        , SemiLepMETpx        ,  'SemiLepMETpx/F'        )
    TreeSemiLept.Branch('SemiLepMETpy'        , SemiLepMETpy        ,  'SemiLepMETpy/F'        )
    TreeSemiLept.Branch('SemiLepMETpt'        , SemiLepMETpt        ,  'SemiLepMETpt/F'        )
    TreeSemiLept.Branch('SemiLepMETphi'       , SemiLepMETphi       ,  'SemiLepMETphi/F'       )
    TreeSemiLept.Branch('SemiLepNvtx'         , SemiLepNvtx         ,  'SemiLepNvtx/F'         )
    TreeSemiLept.Branch('SemiLepEventWeight'  , SemiLepEventWeight  ,  'SemiLepEventWeight/F'  )
    TreeSemiLept.Branch('SemilLepTTmass'      , SemilLepTTmass      ,  'SemilLepTTmass/F'      )
    TreeSemiLept.Branch('DeltaPhiLepFat'      , DeltaPhiLepFat      ,  'DeltaPhiLepFat/F'      )
    TreeSemiLept.Branch('AK4bDisc'            ,AK4bDisc             ,  'AK4bDisc/F'            )
    TreeSemiLept.Branch('NearestAK4JetPt'     ,NearestAK4JetPt      ,  'NearestAK4JetPt/F'     )
    TreeSemiLept.Branch('NearestAK4JetEta'    ,NearestAK4JetEta     ,  'NearestAK4JetEta/F'    )
    TreeSemiLept.Branch('NearestAK4JetPhi'    ,NearestAK4JetPhi     ,  'NearestAK4JetPhi/F'    )
    TreeSemiLept.Branch('NearestAK4JetMass'   ,NearestAK4JetMass    ,  'NearestAK4JetMass/F'   )

    TreeSemiLept.Branch('SemiLeptRunNum'         ,  SemiLeptRunNum       ,  'SemiLeptRunNum/F'          )
    TreeSemiLept.Branch('SemiLeptLumiBlock'      ,  SemiLeptLumiBlock    ,  'SemiLeptLumiBlock/F'       )
    TreeSemiLept.Branch('SemiLeptEventNum'       ,  SemiLeptEventNum     ,  'SemiLeptEventNum/F'        )


if options.writeTree  and options.selection == 2 : 

    TreeAllHad = ROOT.TTree("TreeAllHad", "TreeAllHad")

    SemiLeptTrig        = array('i', [0]  )
    Jet0CorrFactor      = array('f', [1.])
    Jet0CorrFactorUp    = array('f', [1.])
    Jet0CorrFactorDn    = array('f', [1.])
    Jet0MassCorrFactor  = array('f', [1.])
    Jet0MassCorrFactorUp= array('f', [1.])
    Jet0MassCorrFactorDn= array('f', [1.])
    Jet0PtSmearFactor   = array('f', [1.])
    Jet0PtSmearFactorUp = array('f', [1.])
    Jet0PtSmearFactorDn = array('f', [1.])
    Jet0EtaScaleFactor  = array('f', [1.])
    Jet0PhiScaleFactor  = array('f', [1.])
    Jet0MatchedGenJetPt = array('f', [-1.])
    Jet0MatchedGenJetMass = array('f', [-1.])
    Jet0MatchedGenJetMassSD = array('f', [-1.])
    Jet0PtRaw           = array('f', [-1.])
    Jet0EtaRaw          = array('f', [-1.])
    Jet0PhiRaw          = array('f', [-1.])
    Jet0RapRaw          = array('f', [-1.])
    Jet0MassRaw         = array('f', [-1.])
    Jet0P               = array('f', [-1.])
    Jet0Pt              = array('f', [-1.])
    Jet0Eta             = array('f', [-1.])
    Jet0Phi             = array('f', [-1.])
    Jet0Rap             = array('f', [-1.])
    Jet0Energy          = array('f', [-1.])
    Jet0RhoRatio        = array('f', [-1.])
    Jet0Mass            = array('f', [-1.])
    Jet0MassSoftDrop    = array('f', [-1.])
    Jet0MassSDsumSubjetCorr        = array('f', [-1.] )
    Jet0MassSDsumSubjetRaw         = array('f', [-1.] )
    Jet0MassSDsumSubjetCorrUp      = array('f', [-1.] )
    Jet0MassSDsumSubjetCorrDn      = array('f', [-1.] )
    Jet0MassSDsumSubjetCorrSmear   = array('f', [-1.] )
    Jet0MassSDsumSubjetCorrSmearUp = array('f', [-1.] )
    Jet0MassSDsumSubjetCorrSmearDn = array('f', [-1.] )
    Jet0MassPruned      = array('f', [-1.])
    Jet0MassFiltered    = array('f', [-1.])
    Jet0MassTrimmed     = array('f', [-1.])
    Jet0Tau1            = array('f', [-1.])
    Jet0Tau2            = array('f', [-1.])
    Jet0Tau3            = array('f', [-1.])
    Jet0Tau32           = array('f', [-1.])
    Jet0Tau21           = array('f', [-1.])
    Jet0SDbdisc0        = array('f', [-1.])
    Jet0SDbdisc1        = array('f', [-1.])
    Jet0SDmaxbdisc      = array('f', [-1.])
    Jet0SDmaxbdiscflav  = array('f', [-1.])
    Jet0SDsubjet0pt     = array('f', [-1.])
    Jet0SDsubjet0mass   = array('f', [-1.])
    Jet0SDsubjet0area   = array('f', [-1.])
    Jet0SDsubjet0flav   = array('f', [-1.])
    Jet0SDsubjet1pt     = array('f', [-1.])
    Jet0SDsubjet1mass   = array('f', [-1.])
    Jet0SDsubjet1area   = array('f', [-1.])
    Jet0SDsubjet1flav   = array('f', [-1.])
    Jet0CMSmaxbdisc     = array('f', [-1.])
    Jet0CMSnsubjets     = array('f', [-1.])
    Jet0CMSminMass      = array('f', [-1.])
    Jet0CMSm01          = array('f', [-1.])
    Jet0CMSm02          = array('f', [-1.])
    Jet0CMSm12          = array('f', [-1.])
    Jet0NHF             = array('f', [-1.])
    Jet0CHF             = array('f', [-1.])
    Jet0NEF             = array('f', [-1.])
    Jet0CEF             = array('f', [-1.])
    Jet0NC              = array('f', [-1.])
    Jet0NCH             = array('f', [-1.])

    Jet1CorrFactor      = array('f', [1.])
    Jet1CorrFactorUp    = array('f', [1.])
    Jet1CorrFactorDn    = array('f', [1.])
    Jet1MassCorrFactor  = array('f', [1.])
    Jet1MassCorrFactorUp= array('f', [1.])
    Jet1MassCorrFactorDn= array('f', [1.])
    Jet1PtSmearFactor   = array('f', [1.])
    Jet1PtSmearFactorUp = array('f', [1.])
    Jet1PtSmearFactorDn = array('f', [1.])
    Jet1EtaScaleFactor  = array('f', [1.])
    Jet1PhiScaleFactor  = array('f', [1.])
    Jet1MatchedGenJetPt = array('f', [-1.])
    Jet1MatchedGenJetMass = array('f', [-1.])
    Jet1MatchedGenJetMassSD = array('f', [-1.])
    Jet1PtRaw           = array('f', [-1.])
    Jet1EtaRaw          = array('f', [-1.])
    Jet1PhiRaw          = array('f', [-1.])
    Jet1RapRaw          = array('f', [-1.])
    Jet1MassRaw         = array('f', [-1.])
    Jet1Corr            = array('f', [-1.])
    Jet1CorrUp          = array('f', [-1.])
    Jet1CorrDn          = array('f', [-1.])
    Jet1P               = array('f', [-1.])
    Jet1Pt              = array('f', [-1.])
    Jet1Eta             = array('f', [-1.])
    Jet1Phi             = array('f', [-1.])
    Jet1Rap             = array('f', [-1.])
    Jet1Energy          = array('f', [-1.])
    Jet1RhoRatio        = array('f', [-1.])
    Jet1Mass            = array('f', [-1.])
    Jet1MassSoftDrop    = array('f', [-1.])
    Jet1MassSDsumSubjetCorr        = array('f', [-1.] )
    Jet1MassSDsumSubjetRaw         = array('f', [-1.] )
    Jet1MassSDsumSubjetCorrUp      = array('f', [-1.] )
    Jet1MassSDsumSubjetCorrDn      = array('f', [-1.] )
    Jet1MassSDsumSubjetCorrSmear   = array('f', [-1.] )
    Jet1MassSDsumSubjetCorrSmearUp = array('f', [-1.] )
    Jet1MassSDsumSubjetCorrSmearDn = array('f', [-1.] )
    Jet1MassPruned      = array('f', [-1.])
    Jet1MassFiltered    = array('f', [-1.])
    Jet1MassTrimmed     = array('f', [-1.])
    Jet1Tau1            = array('f', [-1.])
    Jet1Tau2            = array('f', [-1.])
    Jet1Tau3            = array('f', [-1.])
    Jet1Tau32           = array('f', [-1.])
    Jet1Tau21           = array('f', [-1.])
    Jet1SDbdisc0        = array('f', [-1.])
    Jet1SDbdisc1        = array('f', [-1.])
    Jet1SDmaxbdisc      = array('f', [-1.])
    Jet1SDmaxbdiscflav  = array('f', [-1.])
    Jet1SDsubjet0pt     = array('f', [-1.])
    Jet1SDsubjet0mass   = array('f', [-1.])
    Jet1SDsubjet0area   = array('f', [-1.])
    Jet1SDsubjet0flav   = array('f', [-1.])
    Jet1SDsubjet1pt     = array('f', [-1.])
    Jet1SDsubjet1mass   = array('f', [-1.])
    Jet1SDsubjet1area   = array('f', [-1.])
    Jet1SDsubjet1flav   = array('f', [-1.])
    Jet1CMSmaxbdisc     = array('f', [-1.])
    Jet1CMSnsubjets     = array('f', [-1.])
    Jet1CMSminMass      = array('f', [-1.])
    Jet1CMSm01          = array('f', [-1.])
    Jet1CMSm02          = array('f', [-1.])
    Jet1CMSm12          = array('f', [-1.])
    Jet1NHF             = array('f', [-1.])
    Jet1CHF             = array('f', [-1.])
    Jet1NEF             = array('f', [-1.])
    Jet1CEF             = array('f', [-1.])
    Jet1NC              = array('f', [-1.])
    Jet1NCH             = array('f', [-1.])

    AllHadMETpx         = array('f', [-1.])
    AllHadMETpy         = array('f', [-1.])
    AllHadMETpt         = array('f', [-1.])
    AllHadMETphi        = array('f', [-1.])
    AllHadNvtx          = array('f', [-1.])
    AllHadEventWeight   = array('f', [0.])

    AllHadNPUtrue       = array('f', [-1.]) 
    AllHadPUweight      = array('f', [0.]) 
    AllHadPUweight_MBup = array('f', [0.]) 
    AllHadPUweight_MBdn = array('f', [0.]) 

    DijetMass           = array('f', [-1.])
    DijetModMassJet0    = array('f', [-1.])
    DijetModMassJet1    = array('f', [-1.])
    DijetDeltaR         = array('f', [-1.])
    DijetDeltaPhi       = array('f', [-1.])
    DijetDeltaRap       = array('f', [-1.])

    GenTTmass           = array('f', [-1.])
    DiGenJetMass        = array('f', [-1.])

    HT                  = array('f', [-1.])   
    HT_CorrDn           = array('f', [-1.])   
    HT_CorrUp           = array('f', [-1.])   
    HT_PtSmearUp        = array('f', [-1.])   
    HT_PtSmearDn        = array('f', [-1.])   

    Q2weight_CorrDn     = array('f', [-1.])
    Q2weight_CorrUp     = array('f', [-1.])

    NNPDF3weight_CorrDn     = array('f', [-1.])
    NNPDF3weight_CorrUp     = array('f', [-1.])
    
    PU_CorrDn           = array('f', [-1.])
    PU_CorrUp           = array('f', [-1.])

    AllHadRunNum        = array('f', [-1.])   
    AllHadLumiBlock     = array('f', [-1.])   
    AllHadEventNum      = array('f', [-1.])   

    TreeAllHad.Branch('SemiLeptTrig'        , SemiLeptTrig        ,  'SemiLeptTrig/I'        )
    TreeAllHad.Branch('Jet0CorrFactor'     , Jet0CorrFactor      , 'Jet0CorrFactor/F'      ) 
    TreeAllHad.Branch('Jet0CorrFactorUp'   , Jet0CorrFactorUp    , 'Jet0CorrFactorUp/F'    ) 
    TreeAllHad.Branch('Jet0CorrFactorDn'   , Jet0CorrFactorDn    , 'Jet0CorrFactorDn/F'    ) 
    TreeAllHad.Branch('Jet0MassCorrFactor'     , Jet0MassCorrFactor      , 'Jet0MassCorrFactor/F'      ) 
    TreeAllHad.Branch('Jet0MassCorrFactorUp'   , Jet0MassCorrFactorUp    , 'Jet0MassCorrFactorUp/F'    ) 
    TreeAllHad.Branch('Jet0MassCorrFactorDn'   , Jet0MassCorrFactorDn    , 'Jet0MassCorrFactorDn/F'    ) 
    TreeAllHad.Branch('Jet0PtSmearFactor'  , Jet0PtSmearFactor   , 'Jet0PtSmearFactor/F'   ) 
    TreeAllHad.Branch('Jet0PtSmearFactorUp', Jet0PtSmearFactorUp , 'Jet0PtSmearFactorUp/F' ) 
    TreeAllHad.Branch('Jet0PtSmearFactorDn', Jet0PtSmearFactorDn , 'Jet0PtSmearFactorDn/F' ) 
    TreeAllHad.Branch('Jet0EtaScaleFactor' , Jet0EtaScaleFactor  , 'Jet0EtaScaleFactor/F'  ) 
    TreeAllHad.Branch('Jet0PhiScaleFactor' , Jet0PhiScaleFactor  , 'Jet0PhiScaleFactor/F'  ) 
    TreeAllHad.Branch('Jet0MatchedGenJetPt', Jet0MatchedGenJetPt , 'Jet0MatchedGenJetPt/F' ) 
    TreeAllHad.Branch('Jet0MatchedGenJetMass', Jet0MatchedGenJetMass , 'Jet0MatchedGenJetMass/F' ) 
    TreeAllHad.Branch('Jet0MatchedGenJetMassSD', Jet0MatchedGenJetMassSD , 'Jet0MatchedGenJetMassSD/F' ) 
    TreeAllHad.Branch('Jet0PtRaw'          , Jet0PtRaw           , 'Jet0PtRaw/F'           )
    TreeAllHad.Branch('Jet0EtaRaw'         , Jet0EtaRaw          , 'Jet0EtaRaw/F'          ) 
    TreeAllHad.Branch('Jet0PhiRaw'         , Jet0PhiRaw          , 'Jet0PhiRaw/F'          ) 
    TreeAllHad.Branch('Jet0RapRaw'         , Jet0RapRaw          , 'Jet0RapRaw/F'          ) 
    TreeAllHad.Branch('Jet0MassRaw'        , Jet0MassRaw         , 'Jet0MassRaw/F'         ) 
    TreeAllHad.Branch('Jet0P'              , Jet0P               , 'Jet0P/F'               )
    TreeAllHad.Branch('Jet0Pt'             , Jet0Pt              , 'Jet0Pt/F'              )
    TreeAllHad.Branch('Jet0Eta'            , Jet0Eta             , 'Jet0Eta/F'             )
    TreeAllHad.Branch('Jet0Phi'            , Jet0Phi             , 'Jet0Phi/F'             )
    TreeAllHad.Branch('Jet0Rap'            , Jet0Rap             , 'Jet0Rap/F'             )
    TreeAllHad.Branch('Jet0Energy'         , Jet0Energy          , 'Jet0Energy/F'          )
    TreeAllHad.Branch('Jet0RhoRatio'       , Jet0RhoRatio        , 'Jet0RhoRatio/F'        )
    TreeAllHad.Branch('Jet0Mass'           , Jet0Mass            , 'Jet0Mass/F'            )
    TreeAllHad.Branch('Jet0MassSoftDrop'   , Jet0MassSoftDrop    , 'Jet0MassSoftDrop/F'    )
    TreeAllHad.Branch('Jet0MassSDsumSubjetCorr'        , Jet0MassSDsumSubjetCorr         , 'Jet0MassSDsumSubjetCorr/F'        )   
    TreeAllHad.Branch('Jet0MassSDsumSubjetRaw'         , Jet0MassSDsumSubjetRaw          , 'Jet0MassSDsumSubjetRaw/F'         )   
    TreeAllHad.Branch('Jet0MassSDsumSubjetCorrUp'      , Jet0MassSDsumSubjetCorrUp       , 'Jet0MassSDsumSubjetCorrUp/F'      )   
    TreeAllHad.Branch('Jet0MassSDsumSubjetCorrDn'      , Jet0MassSDsumSubjetCorrDn       , 'Jet0MassSDsumSubjetCorrDn/F'      )   
    TreeAllHad.Branch('Jet0MassSDsumSubjetCorrSmear'   , Jet0MassSDsumSubjetCorrSmear    , 'Jet0MassSDsumSubjetCorrSmear/F'   )   
    TreeAllHad.Branch('Jet0MassSDsumSubjetCorrSmearUp' , Jet0MassSDsumSubjetCorrSmearUp  , 'Jet0MassSDsumSubjetCorrSmearUp/F' )   
    TreeAllHad.Branch('Jet0MassSDsumSubjetCorrSmearDn' , Jet0MassSDsumSubjetCorrSmearDn  , 'Jet0MassSDsumSubjetCorrSmearDn/F' )   
    TreeAllHad.Branch('Jet0MassPruned'     , Jet0MassPruned      , 'Jet0MassPruned/F'      )
    TreeAllHad.Branch('Jet0MassFiltered'   , Jet0MassFiltered    , 'Jet0MassFiltered/F'    )
    TreeAllHad.Branch('Jet0MassTrimmed'    , Jet0MassTrimmed     , 'Jet0MassTrimmed/F'     )
    TreeAllHad.Branch('Jet0Tau1'           , Jet0Tau1            , 'Jet0Tau1/F'            )
    TreeAllHad.Branch('Jet0Tau2'           , Jet0Tau2            , 'Jet0Tau2/F'            )
    TreeAllHad.Branch('Jet0Tau3'           , Jet0Tau3            , 'Jet0Tau3/F'            )
    TreeAllHad.Branch('Jet0Tau32'          , Jet0Tau32           , 'Jet0Tau32/F'           )
    TreeAllHad.Branch('Jet0Tau21'          , Jet0Tau21           , 'Jet0Tau21/F'           )
    TreeAllHad.Branch('Jet0SDbdisc0'       , Jet0SDbdisc0        , 'Jet0SDbdisc0/F'        )
    TreeAllHad.Branch('Jet0SDbdisc1'       , Jet0SDbdisc1        , 'Jet0SDbdisc1/F'        )
    TreeAllHad.Branch('Jet0SDmaxbdisc'     , Jet0SDmaxbdisc      , 'Jet0SDmaxbdisc/F'      )
    TreeAllHad.Branch('Jet0SDmaxbdiscflav' , Jet0SDmaxbdiscflav  , 'Jet0SDmaxbdiscflav/F'  )
    TreeAllHad.Branch('Jet0SDsubjet0pt'    , Jet0SDsubjet0pt     , 'Jet0SDsubjet0pt/F'     )
    TreeAllHad.Branch('Jet0SDsubjet0mass'  , Jet0SDsubjet0mass   , 'Jet0SDsubjet0mass/F'   )
    TreeAllHad.Branch('Jet0SDsubjet0area'  , Jet0SDsubjet0area   , 'Jet0SDsubjet0area/F'   )
    TreeAllHad.Branch('Jet0SDsubjet0flav'  , Jet0SDsubjet0flav   , 'Jet0SDsubjet0flav/F'   )
    TreeAllHad.Branch('Jet0SDsubjet1pt'    , Jet0SDsubjet1pt     , 'Jet0SDsubjet1pt/F'     )
    TreeAllHad.Branch('Jet0SDsubjet1mass'  , Jet0SDsubjet1mass   , 'Jet0SDsubjet1mass/F'   )
    TreeAllHad.Branch('Jet0SDsubjet1area'  , Jet0SDsubjet1area   , 'Jet0SDsubjet1area/F'   )
    TreeAllHad.Branch('Jet0SDsubjet1flav'  , Jet0SDsubjet1flav   , 'Jet0SDsubjet1flav/F'   )
    TreeAllHad.Branch('Jet0CMSmaxbdisc'    , Jet0CMSmaxbdisc     , 'Jet0CMSmaxbdisc/F'     )
    TreeAllHad.Branch('Jet0CMSnsubjets'    , Jet0CMSnsubjets     , 'Jet0CMSnsubjets/F'     )
    TreeAllHad.Branch('Jet0CMSminMass'     , Jet0CMSminMass      , 'Jet0CMSminMass/F'      )
    TreeAllHad.Branch('Jet0CMSm01'         , Jet0CMSm01          , 'Jet0CMSm01/F'          )
    TreeAllHad.Branch('Jet0CMSm02'         , Jet0CMSm02          , 'Jet0CMSm02/F'          )
    TreeAllHad.Branch('Jet0CMSm12'         , Jet0CMSm12          , 'Jet0CMSm12/F'          )
    TreeAllHad.Branch('Jet0NHF'            , Jet0NHF             , 'Jet0NHF/F'             )    
    TreeAllHad.Branch('Jet0CHF'            , Jet0CHF             , 'Jet0CHF/F'             )    
    TreeAllHad.Branch('Jet0NEF'            , Jet0NEF             , 'Jet0NEF/F'             )    
    TreeAllHad.Branch('Jet0CEF'            , Jet0CEF             , 'Jet0CEF/F'             )    
    TreeAllHad.Branch('Jet0NC'             , Jet0NC              , 'Jet0NC/F'              )    
    TreeAllHad.Branch('Jet0NCH'            , Jet0NCH             , 'Jet0NCH/F'             )    

    TreeAllHad.Branch('Jet1CorrFactor'     , Jet1CorrFactor      , 'Jet1CorrFactor/F'      ) 
    TreeAllHad.Branch('Jet1CorrFactorUp'   , Jet1CorrFactorUp    , 'Jet1CorrFactorUp/F'    ) 
    TreeAllHad.Branch('Jet1CorrFactorDn'   , Jet1CorrFactorDn    , 'Jet1CorrFactorDn/F'    ) 
    TreeAllHad.Branch('Jet1MassCorrFactor'     , Jet1MassCorrFactor      , 'Jet1MassCorrFactor/F'      ) 
    TreeAllHad.Branch('Jet1MassCorrFactorUp'   , Jet1MassCorrFactorUp    , 'Jet1MassCorrFactorUp/F'    ) 
    TreeAllHad.Branch('Jet1MassCorrFactorDn'   , Jet1MassCorrFactorDn    , 'Jet1MassCorrFactorDn/F'    ) 
    TreeAllHad.Branch('Jet1PtSmearFactor'  , Jet1PtSmearFactor   , 'Jet1PtSmearFactor/F'   ) 
    TreeAllHad.Branch('Jet1PtSmearFactorUp', Jet1PtSmearFactorUp , 'Jet1PtSmearFactorUp/F' ) 
    TreeAllHad.Branch('Jet1PtSmearFactorDn', Jet1PtSmearFactorDn , 'Jet1PtSmearFactorDn/F' ) 
    TreeAllHad.Branch('Jet1EtaScaleFactor' , Jet1EtaScaleFactor  , 'Jet1EtaScaleFactor/F'  ) 
    TreeAllHad.Branch('Jet1PhiScaleFactor' , Jet1PhiScaleFactor  , 'Jet1PhiScaleFactor/F'  ) 
    TreeAllHad.Branch('Jet1MatchedGenJetPt', Jet1MatchedGenJetPt , 'Jet1MatchedGenJetPt/F' ) 
    TreeAllHad.Branch('Jet1MatchedGenJetMass', Jet1MatchedGenJetMass , 'Jet1MatchedGenJetMass/F' ) 
    TreeAllHad.Branch('Jet1MatchedGenJetMassSD', Jet1MatchedGenJetMassSD , 'Jet1MatchedGenJetMassSD/F' ) 
    TreeAllHad.Branch('Jet1PtRaw'          , Jet1PtRaw           , 'Jet1PtRaw/F'           )
    TreeAllHad.Branch('Jet1EtaRaw'         , Jet1EtaRaw          , 'Jet1EtaRaw/F'          ) 
    TreeAllHad.Branch('Jet1PhiRaw'         , Jet1PhiRaw          , 'Jet1PhiRaw/F'          ) 
    TreeAllHad.Branch('Jet1RapRaw'         , Jet1RapRaw          , 'Jet1RapRaw/F'          ) 
    TreeAllHad.Branch('Jet1MassRaw'        , Jet1MassRaw         , 'Jet1MassRaw/F'         ) 
    TreeAllHad.Branch('Jet1P'              , Jet1P               , 'Jet1P/F'               )
    TreeAllHad.Branch('Jet1Pt'             , Jet1Pt              , 'Jet1Pt/F'              )
    TreeAllHad.Branch('Jet1Eta'            , Jet1Eta             , 'Jet1Eta/F'             )
    TreeAllHad.Branch('Jet1Phi'            , Jet1Phi             , 'Jet1Phi/F'             )
    TreeAllHad.Branch('Jet1Rap'            , Jet1Rap             , 'Jet1Rap/F'             )
    TreeAllHad.Branch('Jet1Energy'         , Jet1Energy          , 'Jet1Energy/F'          )
    TreeAllHad.Branch('Jet1RhoRatio'       , Jet1RhoRatio        , 'Jet1RhoRatio/F'        )
    TreeAllHad.Branch('Jet1Mass'           , Jet1Mass            , 'Jet1Mass/F'            )
    TreeAllHad.Branch('Jet1MassSoftDrop'   , Jet1MassSoftDrop    , 'Jet1MassSoftDrop/F'    )
    TreeAllHad.Branch('Jet1MassSDsumSubjetCorr'        , Jet1MassSDsumSubjetCorr         , 'Jet1MassSDsumSubjetCorr/F'        )   
    TreeAllHad.Branch('Jet1MassSDsumSubjetRaw'         , Jet1MassSDsumSubjetRaw          , 'Jet1MassSDsumSubjetRaw/F'         )   
    TreeAllHad.Branch('Jet1MassSDsumSubjetCorrUp'      , Jet1MassSDsumSubjetCorrUp       , 'Jet1MassSDsumSubjetCorrUp/F'      )   
    TreeAllHad.Branch('Jet1MassSDsumSubjetCorrDn'      , Jet1MassSDsumSubjetCorrDn       , 'Jet1MassSDsumSubjetCorrDn/F'      )   
    TreeAllHad.Branch('Jet1MassSDsumSubjetCorrSmear'   , Jet1MassSDsumSubjetCorrSmear    , 'Jet1MassSDsumSubjetCorrSmear/F'   )   
    TreeAllHad.Branch('Jet1MassSDsumSubjetCorrSmearUp' , Jet1MassSDsumSubjetCorrSmearUp  , 'Jet1MassSDsumSubjetCorrSmearUp/F' )   
    TreeAllHad.Branch('Jet1MassSDsumSubjetCorrSmearDn' , Jet1MassSDsumSubjetCorrSmearDn  , 'Jet1MassSDsumSubjetCorrSmearDn/F' )   
    TreeAllHad.Branch('Jet1MassPruned'     , Jet1MassPruned      , 'Jet1MassPruned/F'      )
    TreeAllHad.Branch('Jet1MassFiltered'   , Jet1MassFiltered    , 'Jet1MassFiltered/F'    )
    TreeAllHad.Branch('Jet1MassTrimmed'    , Jet1MassTrimmed     , 'Jet1MassTrimmed/F'     )
    TreeAllHad.Branch('Jet1Tau1'           , Jet1Tau1            , 'Jet1Tau1/F'            )
    TreeAllHad.Branch('Jet1Tau2'           , Jet1Tau2            , 'Jet1Tau2/F'            )
    TreeAllHad.Branch('Jet1Tau3'           , Jet1Tau3            , 'Jet1Tau3/F'            )
    TreeAllHad.Branch('Jet1Tau32'          , Jet1Tau32           , 'Jet1Tau32/F'           )
    TreeAllHad.Branch('Jet1Tau21'          , Jet1Tau21           , 'Jet1Tau21/F'           )
    TreeAllHad.Branch('Jet1SDbdisc0'       , Jet1SDbdisc0        , 'Jet1SDbdisc0/F'        )
    TreeAllHad.Branch('Jet1SDbdisc1'       , Jet1SDbdisc1        , 'Jet1SDbdisc1/F'        )
    TreeAllHad.Branch('Jet1SDmaxbdisc'     , Jet1SDmaxbdisc      , 'Jet1SDmaxbdisc/F'      )
    TreeAllHad.Branch('Jet1SDmaxbdiscflav' , Jet1SDmaxbdiscflav  , 'Jet1SDmaxbdiscflav/F'  )
    TreeAllHad.Branch('Jet1SDsubjet0pt'    , Jet1SDsubjet0pt     , 'Jet1SDsubjet0pt/F'     )
    TreeAllHad.Branch('Jet1SDsubjet0mass'  , Jet1SDsubjet0mass   , 'Jet1SDsubjet0mass/F'   )
    TreeAllHad.Branch('Jet1SDsubjet0area'  , Jet1SDsubjet0area   , 'Jet1SDsubjet0area/F'   )
    TreeAllHad.Branch('Jet1SDsubjet0flav'  , Jet1SDsubjet0flav   , 'Jet1SDsubjet0flav/F'   )
    TreeAllHad.Branch('Jet1SDsubjet1pt'    , Jet1SDsubjet1pt     , 'Jet1SDsubjet1pt/F'     )
    TreeAllHad.Branch('Jet1SDsubjet1mass'  , Jet1SDsubjet1mass   , 'Jet1SDsubjet1mass/F'   )
    TreeAllHad.Branch('Jet1SDsubjet1area'  , Jet1SDsubjet1area   , 'Jet1SDsubjet1area/F'   )
    TreeAllHad.Branch('Jet1SDsubjet1flav'  , Jet1SDsubjet1flav   , 'Jet1SDsubjet1flav/F'   )
    TreeAllHad.Branch('Jet1CMSmaxbdisc'    , Jet1CMSmaxbdisc     , 'Jet1CMSmaxbdisc/F'     )
    TreeAllHad.Branch('Jet1CMSnsubjets'    , Jet1CMSnsubjets     , 'Jet1CMSnsubjets/F'     )
    TreeAllHad.Branch('Jet1CMSminMass'     , Jet1CMSminMass      , 'Jet1CMSminMass/F'      )
    TreeAllHad.Branch('Jet1CMSm01'         , Jet1CMSm01          , 'Jet1CMSm01/F'          )
    TreeAllHad.Branch('Jet1CMSm02'         , Jet1CMSm02          , 'Jet1CMSm02/F'          )
    TreeAllHad.Branch('Jet1CMSm12'         , Jet1CMSm12          , 'Jet1CMSm12/F'          )
    TreeAllHad.Branch('Jet1NHF'            , Jet1NHF             , 'Jet1NHF/F'             )    
    TreeAllHad.Branch('Jet1CHF'            , Jet1CHF             , 'Jet1CHF/F'             )    
    TreeAllHad.Branch('Jet1NEF'            , Jet1NEF             , 'Jet1NEF/F'             )    
    TreeAllHad.Branch('Jet1CEF'            , Jet1CEF             , 'Jet1CEF/F'             )    
    TreeAllHad.Branch('Jet1NC'             , Jet1NC              , 'Jet1NC/F'              )    
    TreeAllHad.Branch('Jet1NCH'            , Jet1NCH             , 'Jet1NCH/F'             ) 

    TreeAllHad.Branch('AllHadMETpx'         , AllHadMETpx        , 'AllHadMETpx/F'           )
    TreeAllHad.Branch('AllHadMETpy'         , AllHadMETpy        , 'AllHadMETpy/F'           )
    TreeAllHad.Branch('AllHadMETpt'         , AllHadMETpt        , 'AllHadMETpt/F'           )
    TreeAllHad.Branch('AllHadMETphi'        , AllHadMETphi       , 'AllHadMETpphi/F'         )
    TreeAllHad.Branch('AllHadNvtx'          , AllHadNvtx         , 'AllHadNvtx/F'            )
    TreeAllHad.Branch('AllHadEventWeight'   , AllHadEventWeight  , 'AllHadEventWeight/F'     )

    TreeAllHad.Branch('AllHadNPUtrue'       , AllHadNPUtrue      , 'AllHadNPUtrue/F'           )
    TreeAllHad.Branch('AllHadPUweight'      , AllHadPUweight     , 'AllHadPUweight/F'          )
    TreeAllHad.Branch('AllHadPUweight_MBup' , AllHadPUweight_MBup, 'AllHadPUweight_MBup/F'     )
    TreeAllHad.Branch('AllHadPUweight_MBdn' , AllHadPUweight_MBdn, 'AllHadPUweight_MBdn/F'     )

    TreeAllHad.Branch('DijetMass'         , DijetMass        , 'DijetMass/F'           )
    TreeAllHad.Branch('DijetModMassJet0'  , DijetModMassJet0 , 'DijetModMassJet0/F'    )
    TreeAllHad.Branch('DijetModMassJet1'  , DijetModMassJet1 , 'DijetModMassJet1/F'    )
    TreeAllHad.Branch('DijetDeltaR'       , DijetDeltaR      , 'DijetDeltaR/F'         )
    TreeAllHad.Branch('DijetDeltaPhi'     , DijetDeltaPhi    , 'DijetDeltaPhi/F'       )
    TreeAllHad.Branch('DijetDeltaRap'     , DijetDeltaRap    , 'DijetDeltaRap/F'       )
      
    TreeAllHad.Branch('GenTTmass'         , GenTTmass        , 'GenTTmass/F'           )
    TreeAllHad.Branch('DiGenJetMass'         , DiGenJetMass        , 'DiGenJetMass/F'           )

    TreeAllHad.Branch('HT'                ,  HT              ,  'HT/F'                 )
    TreeAllHad.Branch('HT_CorrDn'         ,  HT_CorrDn       ,  'HT_CorrDn/F'          )
    TreeAllHad.Branch('HT_CorrUp'         ,  HT_CorrUp       ,  'HT_CorrUp/F'          )
    TreeAllHad.Branch('HT_PtSmearUp'      ,  HT_PtSmearUp    ,  'HT_PtSmearUp/F'       )
    TreeAllHad.Branch('HT_PtSmearDn'      ,  HT_PtSmearDn    ,  'HT_PtSmearDn/F'       )

    TreeAllHad.Branch('Q2weight_CorrDn'   ,  Q2weight_CorrDn       ,  'Q2weight_CorrDn/F'          )
    TreeAllHad.Branch('Q2weight_CorrUp'   ,  Q2weight_CorrUp       ,  'Q2weight_CorrUp/F'          )

    TreeAllHad.Branch('NNPDF3weight_CorrDn'   ,  NNPDF3weight_CorrDn       ,  'NNPDF3weight_CorrDn/F'          )
    TreeAllHad.Branch('NNPDF3weight_CorrUp'   ,  NNPDF3weight_CorrUp       ,  'NNPDF3weight_CorrUp/F'          )

    TreeAllHad.Branch('PU_CorrDn'         ,  PU_CorrDn       ,  'PU_CorrDn/F'          )
    TreeAllHad.Branch('PU_CorrUp'         ,  PU_CorrUp       ,  'PU_CorrUp/F'          )

    TreeAllHad.Branch('AllHadRunNum'         ,  AllHadRunNum       ,  'AllHadRunNum/F'          )
    TreeAllHad.Branch('AllHadLumiBlock'      ,  AllHadLumiBlock    ,  'AllHadLumiBlock/F'       )
    TreeAllHad.Branch('AllHadEventNum'       ,  AllHadEventNum     ,  'AllHadEventNum/F'        )


#^ Plot initialization
h_NPVert         = ROOT.TH1D("h_NPVert"        , "", 200,0,200 )
h_NtrueIntPU     = ROOT.TH1D("h_NtrueIntPU"    , "", 200,0,200 )
h_NPVertWeighted = ROOT.TH1D("h_NPVertWeighted", "", 200,0,200 )


h_CutFlow_AllHad         = ROOT.TH1D("h_CutFlow_AllHad"      , "", 30,0,30 )
h_CutFlow_SemiLept       = ROOT.TH1D("h_CutFlow_SemiLept"    , "", 30,0,30 )


if options.selection == 1 : 

    # Loop over channels and selections. Make histograms for each. 
    f.mkdir("SelectionLoop").cd()

    # indices correspond to the lepton flavor
    # Type2 semi-leptonic selection - no top tagged jet instead a w jet pt> 200 and a btagged jet
    ALL_NDX = 0
    EL_NDX = 1
    MU_NDX = 2
    ALL_TYPE1_NDX = 3
    EL_TYPE1_NDX = 4
    MU_TYPE1_NDX = 5
    ALL_TYPE2_NDX = 6             
    EL_TYPE2_NDX = 7
    MU_TYPE2_NDX = 8
    channels = [
        '', 'el', 'mu', 'alltype1', 'eltype1', 'mutype1', 'alltype2', 'eltype2', 'mutype2'
        ]

    # indices correspond to stages in the selection
    SEL_ALL_NDX = 0
    SEL_M_NDX = 1
    SEL_TAU32_NDX = 2
    SEL_TAU21_NDX = 3
    SEL_M_TAU32_NDX = 4
    SEL_MINMASS_NDX = 5
    SEL_BDISC_NDX = 6
    SEL_BDISC_TAU32_NDX = 7
    SEL_M_MINMASS_NDX = 8
    SEL_M_TAU32_BDISC_NDX = 9
    SEL_NHF_LOW_NDX = 10
    SEL_NHF_HIGH_NDX = 11
    SEL_MW_NDX = 12
    SEL_MW_TAU21_NDX = 13
    SEL_MW_TAU21_BDISC_NDX = 14
    selections = [
        '', '_mSDcut', '_tau32cut', '_tau21cut', '_mSDcut_tau32cut', '_minMasscut', '_bDiscMincut', '_bDiscMincut_tau32cut', '_mSDcut_minMasscut', '_mSDcut_tau32cut_bDiscMincut', '_nhfLow', '_nhfHigh', '_mWSDcut', '_mWSDcut_tau21cut', '_mWSDcut_tau21cut_bDiscMincut'
        ]

    #$ Below histos with only quality cuts (see default in options above) : only plotted jets with mSD > 10 GeV as Sal suggested
    h_mttbar = []
    h_mttbar_true = []

    h_ptLep = []
    h_etaLep = []

    h_met = []
    h_htLep = []
    h_st = []
    h_ptRel = []
    h_dRMin = []
    h_2DCut = []

    h_ptAK4 = []
    h_etaAK4 = []
    h_yAK4 = []
    h_phiAK4 = []
    h_mAK4 = []
    h_bdiscAK4 = []


    h_ptAK8 = []
    h_etaAK8 = []
    h_yAK8 = []
    h_phiAK8 = []
    h_mAK8 = []
    h_mprunedAK8 = []
    h_mfilteredAK8 = []
    h_mtrimmedAK8 = []
    h_mSDropAK8 = []
    h_minmassAK8 = []
    h_subjetMassAK8 = []
    h_subjetBdiscAK8 = []
    h_nsjAK8 = []
    h_tau21AK8 = []
    h_tau32AK8 = []
    h_BdiscAK8 = []
    h_nhfAK8 = []
    h_chfAK8 = []                    # *** add AK8 CSV
    h_nefAK8 = []
    h_cefAK8 = []
    h_ncAK8 = []
    h_nchAK8 = []
        
    for ichannel,channel in enumerate(channels) :
        h_mttbar.append( [] )
        h_mttbar_true.append( [] )

        h_ptLep.append( ROOT.TH1F("h_ptLep" + channel, "Lepton p_{T};p_{T} (GeV)", 100, 0, 1000) )
        h_etaLep.append( ROOT.TH1F("h_etaLep" + channel, "Lepton #eta;#eta", 100, -5.0, 5.0 ) )
        h_met.append( ROOT.TH1F("h_met" + channel, "Missing p_{T};p_{T} (GeV)", 100, 0, 1000) )
        h_htLep.append( ROOT.TH1F("h_htLep" + channel, "Lepton p_{T} + Missing p_{T};H_{T}^{lep} (GeV)", 100, 0, 1000) )
        h_st.append( ROOT.TH1F("h_st" + channel, "Lepton p_{T} + Missing p_{T} + H_{T};S_{T} (GeV)", 100, 0, 4000) )
        h_ptRel.append( ROOT.TH1F("h_ptRel" + channel, "p_{T}^{REL};p_{T}^{REL} (GeV)", 100, 0, 100) )
        h_dRMin.append( ROOT.TH1F("h_dRMin" + channel, "#Delta R_{MIN};#Delta R_{MIN}", 100, 0, 5.0) )
        h_2DCut.append( ROOT.TH2F("h_2DCut" + channel, "2D Cut;#Delta R;p_{T}^{REL}", 20, 0, 5.0, 20, 0, 100 ) )
        
        h_ptAK4.append( [] )
        h_etaAK4.append( [] )
        h_yAK4.append( [] )
        h_phiAK4.append( [] )
        h_mAK4.append( [] )
        h_bdiscAK4.append( [] )

        h_ptAK8.append( [] )
        h_etaAK8.append( [] )
        h_yAK8.append( [] )
        h_phiAK8.append( [] )
        h_mAK8.append( [] )
        h_mprunedAK8.append( [] )
        h_mfilteredAK8.append( [] )
        h_mtrimmedAK8.append( [] )
        h_mSDropAK8.append( [] )
        h_minmassAK8.append( [] )
        h_subjetMassAK8.append( [] )
        h_subjetBdiscAK8.append( [] )
        h_nsjAK8.append( [] )
        h_tau21AK8.append( [] )
        h_tau32AK8.append( [] )
        h_BdiscAK8.append( [] )
        h_nhfAK8.append( [] )
        h_chfAK8.append( [] )
        h_nefAK8.append( [] )
        h_cefAK8.append( [] )
        h_ncAK8.append( [] )
        h_nchAK8.append( [] )    
        for isel, sel in enumerate(selections) : 
            #$ Below histos with only quality cuts (see default in options above) : only plotted jets with mSD > 10 GeV as Sal suggested
            h_mttbar[ichannel].append( ROOT.TH1F("h_mttbar" + channel + sel, ";m_{t#bar{t}} (GeV)", 200, 0, 6000) )
            h_mttbar_true[ichannel].append( ROOT.TH1F("h_mttbar_true" + channel + sel, "True m_{t#bar{t}};m_{t#bar{t}} (GeV)", 200, 0, 6000) )

            h_ptAK4[ichannel].append( ROOT.TH1F("h_ptAK4" + channel + sel, "AK4 Jet p_{T};p_{T} (GeV)", 300, 0, 3000) )
            h_etaAK4[ichannel].append( ROOT.TH1F("h_etaAK4" + channel + sel, "AK4 Jet #eta;#eta", 120, -6, 6) )
            h_yAK4[ichannel].append( ROOT.TH1F("h_yAK4" + channel + sel, "AK4 Jet Rapidity;y", 120, -6, 6) )
            h_phiAK4[ichannel].append( ROOT.TH1F("h_phiAK4" + channel + sel, "AK4 Jet #phi;#phi (radians)",100,-3.14, 3.14) )
            h_mAK4[ichannel].append( ROOT.TH1F("h_mAK4" + channel + sel, "AK4 Jet Mass;Mass (GeV)", 100, 0, 1000) )
            h_bdiscAK4[ichannel].append( ROOT.TH1F("h_bdiscAK4" + channel + sel, "AK4 b discriminator;b discriminator", 100, 0, 1.0) )

            h_ptAK8[ichannel].append( ROOT.TH1F("h_ptAK8" + channel + sel, "AK8 Jet p_{T};p_{T} (GeV)", 300, 0, 3000) )
            h_etaAK8[ichannel].append( ROOT.TH1F("h_etaAK8" + channel + sel, "AK8 Jet #eta;#eta", 120, -6, 6) )
            h_yAK8[ichannel].append( ROOT.TH1F("h_yAK8" + channel + sel, "AK8 Jet Rapidity;y", 120, -6, 6) )
            h_phiAK8[ichannel].append( ROOT.TH1F("h_phiAK8" + channel + sel, "AK8 Jet #phi;#phi (radians)",100,-3.14, 3.14) )
            h_mAK8[ichannel].append( ROOT.TH1F("h_mAK8" + channel + sel, "AK8 Jet Mass;Mass (GeV)", 1000, 0, 1000) )
            h_mprunedAK8[ichannel].append( ROOT.TH1F("h_mprunedAK8" + channel + sel, "AK8 Pruned Jet Mass;Mass (GeV)", 1000, 0, 1000) )
            h_mfilteredAK8[ichannel].append( ROOT.TH1F("h_mfilteredAK8" + channel + sel, "AK8 Filtered Jet Mass;Mass (GeV)", 1000, 0, 1000) )
            h_mtrimmedAK8[ichannel].append( ROOT.TH1F("h_mtrimmedAK8" + channel + sel, "AK8 Trimmed Jet Mass;Mass (GeV)", 1000, 0, 1000) )
            h_mSDropAK8[ichannel].append( ROOT.TH1F("h_mSDropAK8" + channel + sel, "AK8 Soft Drop Jet Mass;Mass (GeV)", 1000, 0, 1000) )
            h_minmassAK8[ichannel].append( ROOT.TH1F("h_minmassAK8" + channel + sel, "AK8 CMS Top Tagger Min Mass Paring;m_{min} (GeV)", 1000, 0, 1000) )
            h_subjetMassAK8[ichannel].append( ROOT.TH1F("h_subjetMassAK8" + channel + sel, "AK8 subjet mass; Mass (GeV)", 1000, 0, 1000) )
            h_subjetBdiscAK8[ichannel].append( ROOT.TH1F("h_subjetBdiscAK8" + channel + sel, "AK8 subjet b discriminator;b discriminator", 100, 0, 1.0) )
            h_nsjAK8[ichannel].append( ROOT.TH1F("h_nsjAK8" + channel + sel, "AK8 CMS Top Tagger N_{subjets};N_{subjets}", 5, 0, 5) )
            h_tau21AK8[ichannel].append( ROOT.TH1F("h_tau21AK8" + channel + sel, "AK8 Jet #tau_{2} / #tau_{1};#tau_{21}", 100, 0, 1.0) )
            h_tau32AK8[ichannel].append( ROOT.TH1F("h_tau32AK8" + channel + sel, "AK8 Jet #tau_{3} / #tau_{2};#tau_{32}", 100, 0, 1.0) )
            h_BdiscAK8[ichannel].append( ROOT.TH1F("h_BdiscAK8" + channel + sel, "AK8 Jet b-discriminator;b discriminator", 100, 0, 1.0) )
            h_nhfAK8[ichannel].append( ROOT.TH1F("h_nhfAK8" + channel + sel, "AK8 Neutral hadron fraction;NHF", 100, 0, 1.0) )
            h_chfAK8[ichannel].append( ROOT.TH1F("h_chfAK8" + channel + sel, "AK8 Charged hadron fraction;CHF", 100, 0, 1.0) )
            h_nefAK8[ichannel].append( ROOT.TH1F("h_nefAK8" + channel + sel, "AK8 Neutral EM fraction;NEF", 100, 0, 1.0) )
            h_cefAK8[ichannel].append( ROOT.TH1F("h_cefAK8" + channel + sel, "AK8 Charged EM fraction;CEF", 100, 0, 1.0) )
            h_ncAK8[ichannel].append( ROOT.TH1F("h_ncAK8" + channel + sel, "AK8 Number of constituents;Number of constituents", 100, 0, 100) )
            h_nchAK8[ichannel].append( ROOT.TH1F("h_nchAK8" + channel + sel, "AK8 Number of charged hadrons;N charged hadrons", 100, 0, 100) )

#^ Basic plots from all-hadronic preselected events (2 AK8 pT>400 jets)
if  options.selection == 2: 

    f.cd()
    f.mkdir("AllHad").cd()

    #^ Make modMass hist with small binning
    h_mAK8_ModMass           = ROOT.TH1F("h_mAK8_ModMass"               , "AK8 Jet Mass;Mass (GeV)", 220, 140, 250 )
    h_mSDropAK8_ModMass      = ROOT.TH1F("h_mSDropAK8_ModMass"          , "AK8 Jet Mass;Mass (GeV)", 200, 110, 210 )
    h_mAK8_ModMass_jet0      = ROOT.TH1F("h_mAK8_ModMass_jet0"          , "AK8 Jet Mass;Mass (GeV)", 220, 140, 250 )
    h_mSDropAK8_ModMass_jet0 = ROOT.TH1F("h_mSDropAK8_ModMass_jet0"     , "AK8 Jet Mass;Mass (GeV)", 200, 110, 210 )
    h_mAK8_ModMass_jet1      = ROOT.TH1F("h_mAK8_ModMass_jet1"          , "AK8 Jet Mass;Mass (GeV)", 220, 140, 250 )
    h_mSDropAK8_ModMass_jet1 = ROOT.TH1F("h_mSDropAK8_ModMass_jet1"     , "AK8 Jet Mass;Mass (GeV)", 200, 110, 210 )


f.cd()


#@ JET CORRECTIONS

ROOT.gSystem.Load('libCondFormatsJetMETObjects')
#jecParStrAK4 = ROOT.std.string('JECs/PHYS14_25_V2_AK4PFchs.txt')
#jecUncAK4 = ROOT.JetCorrectionUncertainty( jecParStrAK4 )
#jecParStrAK8 = ROOT.std.string('JECs/PHYS14_25_V2_AK8PFchs.txt')
#jecUncAK8 = ROOT.JetCorrectionUncertainty( jecParStrAK8 )

if options.isMC : 
    print 'Getting L3 for AK4 MC'
    L3JetParAK4  = ROOT.JetCorrectorParameters("JECs/Summer15_25nsV7_MC_L3Absolute_AK4PFchs.txt");
    print 'Getting L2 for AK4 MC'
    L2JetParAK4  = ROOT.JetCorrectorParameters("JECs/Summer15_25nsV7_MC_L2Relative_AK4PFchs.txt");
    print 'Getting L1 for AK4 MC'
    L1JetParAK4  = ROOT.JetCorrectorParameters("JECs/Summer15_25nsV7_MC_L1FastJet_AK4PFchs.txt");
    print 'Getting Uncertainty for AK4 MC'
    UncertJetAK4  = ROOT.JetCorrectionUncertainty("JECs/Summer15_25nsV7_MC_Uncertainty_AK4PFchs.txt");


    print 'Getting L3 for AK8 MC'
    L3JetParAK8  = ROOT.JetCorrectorParameters("JECs/Summer15_25nsV7_MC_L3Absolute_AK8PFchs.txt");
    print 'Getting L2 for AK8 MC'
    L2JetParAK8  = ROOT.JetCorrectorParameters("JECs/Summer15_25nsV7_MC_L2Relative_AK8PFchs.txt");
    print 'Getting L1 for AK8 MC'
    L1JetParAK8  = ROOT.JetCorrectorParameters("JECs/Summer15_25nsV7_MC_L1FastJet_AK8PFchs.txt");
    print 'Getting Uncertainty for AK8 MC'
    UncertJetAK8  = ROOT.JetCorrectionUncertainty("JECs/Summer15_25nsV7_MC_Uncertainty_AK8PFchs.txt");
else :
    print 'Getting L3 for AK4 DATA'
    L3JetParAK4  = ROOT.JetCorrectorParameters("JECs/Summer15_25nsV7_DATA_L3Absolute_AK4PFchs.txt");
    print 'Getting L2 for AK4 DATA'
    L2JetParAK4  = ROOT.JetCorrectorParameters("JECs/Summer15_25nsV7_DATA_L2Relative_AK4PFchs.txt");
    print 'Getting L1 for AK4 DATA'
    L1JetParAK4  = ROOT.JetCorrectorParameters("JECs/Summer15_25nsV7_DATA_L1FastJet_AK4PFchs.txt");
    # for data only :
    print 'Getting L2L3Residual for AK4 DATA'
    ResJetParAK4 = ROOT.JetCorrectorParameters("JECs/Summer15_25nsV7_DATA_L2L3Residual_AK4PFchs.txt");
    print 'Getting Uncertainty for AK4 DATA'
    UncertJetAK4  = ROOT.JetCorrectionUncertainty("JECs/Summer15_25nsV7_DATA_Uncertainty_AK4PFchs.txt");

    print 'Getting L3 for AK8 DATA'
    L3JetParAK8  = ROOT.JetCorrectorParameters("JECs/Summer15_25nsV7_DATA_L3Absolute_AK8PFchs.txt");
    print 'Getting L2 for AK8 DATA'
    L2JetParAK8  = ROOT.JetCorrectorParameters("JECs/Summer15_25nsV7_DATA_L2Relative_AK8PFchs.txt");
    print 'Getting L1 for AK8 DATA'
    L1JetParAK8  = ROOT.JetCorrectorParameters("JECs/Summer15_25nsV7_DATA_L1FastJet_AK8PFchs.txt");
    # for data only :
    print 'Getting L2L3Residual for AK8 DATA'
    ResJetParAK8 = ROOT.JetCorrectorParameters("JECs/Summer15_25nsV7_DATA_L2L3Residual_AK8PFchs.txt");
    print 'Getting Uncertainty for AK8 DATA'
    UncertJetAK8  = ROOT.JetCorrectionUncertainty("JECs/Summer15_25nsV7_DATA_Uncertainty_AK8PFchs.txt");


# uncertSources = ["Absolute", "HighPtExtra",  "SinglePionECAL", "SinglePionHCAL",
#    "FlavorQCD", "Time",
#    "RelativeJEREC1", "RelativeJEREC2", "RelativeJERHF",
#    "RelativePtBB","RelativePtEC1", "RelativePtEC2", "RelativePtHF", "RelativeFSR",
#    "RelativeStatEC2", "RelativeStatHF",
#    "PileUpDataMC", 
#    "PileUpPtBB", "PileUpPtEC", "PileUpPtHF","PileUpBias",
#    "SubTotalPileUp","SubTotalRelative","SubTotalPt","SubTotalMC",
#    "Total","TotalNoFlavor",
#    "FlavorZJet","FlavorPhotonJet","FlavorPureGluon","FlavorPureQuark","FlavorPureCharm","FlavorPureBottom"]


    
#  Load the JetCorrectorParameter objects into a vector, IMPORTANT: THE ORDER MATTERS HERE !!!! 
vParJecAK4 = ROOT.vector('JetCorrectorParameters')()
vParJecAK4.push_back(L1JetParAK4)
vParJecAK4.push_back(L2JetParAK4)
vParJecAK4.push_back(L3JetParAK4)
# for data only :
if not options.isMC : 
    vParJecAK4.push_back(ResJetParAK4)

ak4JetCorrector = ROOT.FactorizedJetCorrector(vParJecAK4)

vParJecAK4ForMass = ROOT.vector('JetCorrectorParameters')()
vParJecAK4ForMass.push_back(L2JetParAK4)
vParJecAK4ForMass.push_back(L3JetParAK4)
if not options.isMC : 
    vParJecAK4ForMass.push_back(ResJetParAK4)

ak4JetCorrectorForMass = ROOT.FactorizedJetCorrector(vParJecAK4ForMass)

vParJecAK8 = ROOT.vector('JetCorrectorParameters')()
vParJecAK8.push_back(L1JetParAK8)
vParJecAK8.push_back(L2JetParAK8)
vParJecAK8.push_back(L3JetParAK8)
# for data only :
if not options.isMC : 
    vParJecAK8.push_back(ResJetParAK8)

ak8JetCorrector = ROOT.FactorizedJetCorrector(vParJecAK8)




def getJER(jetEta, sysType) :
    """
    Here, jetEta should be the jet pseudorapidity, and sysType is :
        nominal : 0
        down    : -1
        up      : +1
    """

    jerSF = 1.0

    if ( (sysType==0 or sysType==-1 or sysType==1) == False):
        print "ERROR: Can't get JER! use type=0 (nom), -1 (down), +1 (up)"
        return float(jerSF)

    # Values from https://twiki.cern.ch/twiki/bin/view/CMS/JetResolution
    etamin = [0.0,0.8,1.3,1.9,2.5,3.0,3.2]
    etamax = [0.8,1.3,1.9,2.5,3.0,3.2,5.0]
    scale_nom =    [1.061,1.088,1.106,1.126,1.343,1.303,1.320]
    scale_uncert = [0.023,0.029,0.030,0.094,0.123,0.111,0.286]
 
    # old 8 TeV
    # etamin = [0.0,0.5,1.1,1.7,2.3,2.8,3.2]
    # etamax = [0.5,1.1,1.7,2.3,2.8,3.2,5.0]
    # scale_nom = [1.079,1.099,1.121,1.208,1.254,1.395,1.056]
    # scale_dn  = [1.053,1.071,1.092,1.162,1.192,1.332,0.865]
    # scale_up  = [1.105,1.127,1.150,1.254,1.316,1.458,1.247]

    for iSF in range(0,len(scale_nom)) :
        if abs(jetEta) >= etamin[iSF] and abs(jetEta) < etamax[iSF] :
            if sysType < 0 :
                jerSF = scale_nom[iSF] - scale_uncert[iSF]
            elif sysType > 0 :
                jerSF = scale_nom[iSF] + scale_uncert[iSF]
            else :
                jerSF = scale_nom[iSF]
            break

    return float(jerSF)




#@ Run / lumi / event numbers
runNumbers = []

#  ________      ________ _   _ _______   _      ____   ____  _____  
# |  ____\ \    / /  ____| \ | |__   __| | |    / __ \ / __ \|  __ \ 
# | |__   \ \  / /| |__  |  \| |  | |    | |   | |  | | |  | | |__) |
# |  __|   \ \/ / |  __| | . ` |  | |    | |   | |  | | |  | |  ___/ 
# | |____   \  /  | |____| |\  |  | |    | |___| |__| | |__| | |     
# |______|   \/   |______|_| \_|  |_|    |______\____/ \____/|_|     


#@ EVENT LOOP

#@ CUTFLOW

#event count
NeventsDiLeptonic  = 0
NeventsSemiLeptonic  = 0
NeventsSemiLeptonicMuon      = 0
NeventsSemiLeptonicElectron  = 0
NeventsAllHadronic  = 0

Nevents = 0
NeventsBeforeChannelSelect = 0
NeventsAfterChannelSelect = 0
NeventsBkgdEstimation =0
NeventsAK8product = 0

Nevents_weighted = 0

# Top Tag count
nttags = 0

#Tracker variables
DimuonEvents = 0
DieleEvents = 0
muoneleEvents = 0
muonJetsEvents = 0
eleJetsEvents = 0
AllHadronicEvents = 0
NMu = 0
NEl = 0
NAK4Jets = 0
NAK8Jets = 0
NPassMuonPtCut = 0
NPassMuonEtaCut = 0 
NPassMuonDzCut = 0
NPassMuonTightCut = 0
NPassElPtCut = 0
NPassElEtaCut = 0
NPassGoodElCut = 0
NPassEldEtaIn = 0
NPassEldPhiIn= 0
NPassEl5x5= 0
NPassElHoE = 0
NPassElD0 = 0
NPassElDz = 0
NPassElEmooP = 0
NPassElKeyCut = 0
NPassGoodJetAK4Cut = 0
NPassMinAK4PtCut = 0
NPassMaxAK4RapidityCut = 0
NPass2DCut = 0
NPass2D2Cut = 0
NPassMET = 0
NPassHTLep = 0
NPassST = 0
NPassTriangularCut = 0
NPassGoodJetAK8Cut = 0
NPassMinRawAK8PtCut = 0
NPassMaxAK8RapidityCut = 0 
NPassSemiLeptonicDRjlCut = 0
NPassAK8nSubJetsCut = 0
NPassAK8MinMassCut = 0
NPassAK8SubjetBDiscCut = 0
NPassAK8CorrMassCut = 0 
NPassminAK8PtCut = 0
NPasstMinMassCut = 0 
NPasstMAK8GroomedMinCut = 0 
NPasstMAK8GroomedMaxCut = 0 
NPasstau23Cut = 0
NPasstau21Cut = 0 
NPassBDiscMinCut = 0 
#NPassBDiscMinMCut = 0
#NPassBDiscMinTCut = 0
NPassBDisc2MinCut = 0 
NPassMuonBCut = 0
NPassElBCut = 0
NPassNearJCut = 0
NPassNearJ2Cut = 0
NPassMuon2DCut = 0
NPassEl2DCut = 0
NPassMuonTot = 0
NPassAK4KinTot = 0
NPassWbEvent= 0

if options.isMC :
    genSemiMuEvents = 0
    genSemiEEvents = 0
    genMuMuEvents = 0
    genMuEEvents = 0
    genEEEvents = 0
    genHadEvents = 0



#@ EVENT LOOP



filelist = file( options.files )
filesraw1 = filelist.readlines()

if options.njobs != None and options.njobs > 1 and options.job >= 0 and options.job < options.njobs : 
    from grouptools import *

    filesraw2 = groupfiles( filesraw1, options.njobs )

    print 'Raw files:'
    print filesraw2

    filesraw = filesraw2[options.job]
else :
    filesraw = filesraw1

files = []
Nevents = 0
for ifile in filesraw : #{ Loop over text file and find root files linked
    if len( ifile ) > 2 :
        if options.xrootd != None : 
            s = options.xrootd + ifile.rstrip()
        else : 
            s = ifile.rstrip()
        files.append( s )
        print 'Added ' + s
        #} End loop over txt file

trigsToRun = []

if options.selection == 1:
      trigsToRun = [
          "HLT_IsoMu24_eta2p1",
          "HLT_Mu45_eta2p1",
          "HLT_Mu50_",
          "HLT_Mu40_eta2p1_PFJet200_PFJet50",
          "HLT_IsoMu24_eta2p1",
          "HLT_Ele32_eta2p1_WPLoose_Gsf",
          "HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50",
          "HLT_Ele105_CaloIdVT_GsfTrkIdT",
          "HLT_Ele115_CaloIdVT_GsfTrkIdT"
          ]
if options.selection == 2:
    if options.isMC:
        trigsToRun = [
            "HLT_PFHT900"
            ]
    else :
        trigsToRun = [
            #"HLT_PFHT200_v",
            #"HLT_PFHT250_v",
            #"HLT_PFHT300_v",
            #"HLT_PFHT350_v",
            #"HLT_PFHT400_v",
            #"HLT_PFHT475_v",
            #"HLT_PFHT600_v",
            #"HLT_PFHT650_v",
            "HLT_PFHT800_v",
            #"HLT_PFJet140_v",
            #"HLT_PFJet200_v",
            #"HLT_PFJet260_v",
            #"HLT_PFJet320_v",
            #"HLT_PFJet400_v",
            #"HLT_PFJet450_v",
            #"HLT_PFJet500_v"
            ]

# loop over files
for ifile in files : #{ Loop over root files
    print 'Processing file ' + ifile
    events = Events (ifile)
    print 'Opened file successfully'
    if options.verbose : 
        print 'Opened file successfully'
    if options.maxevents > 0 and Nevents > options.maxevents :
        break

    # Make sure the handles we want are in the files so we can
    # avoid leaking memory
    readFilters = True
    

    

    
    NeventsInFile = events.size()
    if NeventsInFile <= 0 : 
        continue
    # loop over events in this file
    for event in events: #{ Loop over events in root files


        # Event weight
        evWeight = 1.0
        if options.verbose: 
            print '------'
            print 'evWeight starts at : ' + str(evWeight)

        if options.maxevents > 0 and Nevents > options.maxevents :
            break
        Nevents += 1

        if Nevents % 1000 == 0 : 
            print '    ---> Event ' + str(Nevents)
        if options.verbose :
            print '==============================================='
            print '    ---> Event ' + str(Nevents)


        h_CutFlow_AllHad    .Fill("Events", 1)
        h_CutFlow_SemiLept  .Fill("Events", 1) 
     

        if options.quickSelect :
            event.getByLabel ( l_jetsAK8Pt, h_jetsAK8Pt )
            ak8jetpts = h_jetsAK8Pt.product()
            if len(ak8jetpts) == 0 :
                continue
            if h_jetsAK8Pt.product()[0] < options.quickSelectminAK8Pt :
                continue


        h_CutFlow_AllHad    .Fill("Jet350",1)
        h_CutFlow_SemiLept  .Fill("Jet350",1) 

        if options.verbose >3:
            print ' '
            print 'event '+str( event.object().id().event() )

        if options.applyFilters and readFilters :
            cscFilt = False
            vertexFilt = False
            hbheFilt = False
            # hbheisoFilt = False
            eeBadScFilt = False

            
            gotit1 = event.getByLabel( l_filterNameStrings, h_filterNameStrings )
            gotit2 = event.getByLabel( l_filterBits, h_filterBits )
            #gotit3 = event.getByLabel( l_filterPrescales, h_filterPrescales )
            gotit4 = event.getByLabel( l_HBHEfilter, h_HBHEfilter )


            if options.verbose > 5 :
                print 'Filter string names?  ' + str(gotit1)
                print 'Filter bits?          ' + str(gotit2)

            if gotit1 == False or gotit2 == False  :
                readFilters = False

            filterNameStrings = h_filterNameStrings.product()
            filterBits = h_filterBits.product()

            hbheFilt = h_HBHEfilter.product()[0]
            
            for itrig in xrange(0, len(filterNameStrings) ) :
                if options.verbose > 5 :
                    print 'Filter name = ' + filterNameStrings[itrig]
                    print 'Filter bit  = ' + str(filterBits[itrig])
                if "CSC" in filterNameStrings[itrig] :
                    if filterBits[itrig] == 1 :
                        cscFilt = True
                # (Apply vertex filter later)
                if "goodVer" in filterNameStrings[itrig] :
                   if filterBits[itrig] == 1 :
                       vertexFilt = True
                # (Should work in B2GAnaFW8p4
                if "HBHE" in filterNameStrings[itrig] :
                   if filterBits[itrig] == 1 :
                       hbheFilt = True
                if "eeBadSc" in filterNameStrings[itrig] :
                   if filterBits[itrig] == 1 :
                       eeBadScFilt = True

            if hbheFilt == False or vertexFilt == False or eeBadScFilt == False :  #  cscFilt == False  # use the file lists for the csc filter
                if options.verbose > 5 :
                    print 'Found filters, but they failed'
                continue


        if not readFilters :
            if options.verbose > 5 :
                print 'Did not find filters'
            continue

        h_CutFlow_AllHad    .Fill("METfilter",1)
        h_CutFlow_SemiLept  .Fill("METfilter",1) 


        if options.applyTriggers :

            passTrig = False
            prescale = 1.0
            unprescaled = False
            
            event.getByLabel( l_triggerNameStrings, h_triggerNameStrings )
            event.getByLabel( l_triggerBits, h_triggerBits )
            event.getByLabel( l_triggerPrescales, h_triggerPrescales )

            triggerNameStrings = h_triggerNameStrings.product()
            triggerBits = h_triggerBits.product()
            triggerPrescales = h_triggerPrescales.product()
            if options.verbose > 5 : 
                print '-----'
            firedTrigs = []
            for itrig in xrange(0, len(triggerBits) ) :
                if triggerBits[itrig] == 1 :
                    firedTrigs.append( itrig )

            for trig in firedTrigs :
                trigName = triggerNameStrings[trig]
                for itrigToRun in xrange(0,len(trigsToRun)) :
                    if trigsToRun[itrigToRun] in trigName :
                        passTrig = True
                        SemiLeptTrig[0] = itrigToRun
                        break
                if passTrig :
                    break

            if options.verbose > 5 :
                for itrig in xrange(0, len(triggerNameStrings) ) :
                    print "%60s : %12.0f" % ( triggerNameStrings[itrigToRun] , triggerPrescales[itrigToRun] )## Changed itrig to itrigToRun


            if passTrig :
                if triggerPrescales[itrigToRun] == 1.0 : ## Changed itrig to itrigToRun
                    unprescaled = True
                prescale = prescale * triggerPrescales[itrigToRun] ## Changed itrig to itrigToRun
                        


            if unprescaled :
                prescale = 1.0

            evWeight = evWeight * prescale
            if options.verbose > 3 : 
                print 'after prescale, evWeight is : ' + str(evWeight)
            if passTrig == False :
                continue

        h_CutFlow_AllHad    .Fill("Trigger",1)
        h_CutFlow_SemiLept  .Fill("Trigger",1) 
    
        genZprimeMass = -1
                
        if options.isMC and options.getGenInfo :
            #@ Generator information
            genEIndex = []
            genMuIndex = []
            gotGen = event.getByLabel( l_genPartPt, h_genPartPt )
            topQuarkPt = 0.0 
            top  = ROOT.TLorentzVector()
            atop = ROOT.TLorentzVector()
            if gotGen :
                event.getByLabel( l_genPartEta, h_genPartEta )
                event.getByLabel( l_genPartPhi, h_genPartPhi )
                event.getByLabel( l_genPartMass, h_genPartMass )
                event.getByLabel( l_genPartID, h_genPartID )
                event.getByLabel( l_genPartStatus, h_genPartStatus )
                event.getByLabel( l_genPartMomID, h_genPartMomID )
                genPartPt = h_genPartPt.product()
                genPartEta = h_genPartEta.product()
                genPartPhi = h_genPartPhi.product()
                genPartMass = h_genPartMass.product()
                genPartID = h_genPartID.product()
                genPartStatus = h_genPartStatus.product()
                genPartMomID = h_genPartMomID.product()
                ngenE = 0
                ngenMu = 0
                for igen in xrange(0, len( genPartPt ) ) :
                    genName = None
                    if genPartStatus[igen] < 20 or genPartStatus[igen] > 24 :
                        continue
                    if abs(genPartID[igen]) == 6 :
                        genName = 'Top quark'
                        topQuarkPt = genPartPt[igen]
                        if genPartID[igen] == 6 :
                            top.SetPtEtaPhiM( genPartPt[igen], genPartEta[igen], genPartPhi[igen], genPartPtMass[igen])
                        if genPartID[igen] == -6 :
                            atop.SetPtEtaPhiM( genPartPt[igen], genPartEta[igen], genPartPhi[igen], genPartPtMass[igen])
                    elif abs(genPartID[igen]) == 24 :
                        genName = 'W boson'
                    elif abs(genPartID[igen]) == 11 and abs(genPartMomID[igen]) == 24 :
                        genName = 'Electron'
                        genEIndex.append( igen )
                        ngenE += 1
                    elif abs(genPartID[igen]) == 13 and abs(genPartMomID[igen]) == 24 :
                        genName = 'Muon'
                        genMuIndex.append( igen )
                        ngenMu += 1
                    elif abs(genPartID[igen]) == 15 and abs(genPartMomID[igen]) == 24 :
                        genName = 'Tau'
                    if options.verbose > 3  and genName != None:
                        print '%10s : %6d %6d %7.2f %6.3f %6.3f %6.3f' % ( genName, genPartID[igen], genPartStatus[igen], genPartPt[igen], genPartEta[igen], genPartPhi[igen], genPartMass[igen] )
                genZprimeMass = (top+atop).M()
                      
            if ngenE == 0 and ngenMu == 0 :
                genHadEvents += 1
            elif ngenE == 1 and ngenMu == 0 :
                genSemiEEvents += 1
            elif ngenE == 0 and ngenMu == 1 :
                genSemiMuEvents += 1
            elif ngenMu == 1 and ngenE == 1 :
                genMuEEvents += 1            
            elif ngenE == 2 :
                genEEEvents += 1
            elif ngenMu == 2 :
                genMuMuEvents += 1

            if options.reweightTopPt :
                ptWeight = reweightTopPt.Eval( topQuarkPt  )
                if ptWeight > 0.0000001 : 
                    evWeight /= ptWeight
                    print 'after top pt reweighting, evWeight is : ' + str(evWeight)




        #@ VERTEX SETS
        event.getByLabel( l_pv_chi, h_pv_chi )
        event.getByLabel( l_pv_rho, h_pv_rho )
        event.getByLabel( l_pv_z, h_pv_z )
        event.getByLabel( l_pv_ndof, h_pv_ndof )

        pv_chi = h_pv_chi.product()
        pv_rho = h_pv_rho.product()
        pv_z = h_pv_z.product()
        pv_ndof = h_pv_ndof.product()
        NPV = 0

        for ivtx in xrange( len(pv_chi) ) :
            if abs(pv_z[ivtx]) < 24. and pv_ndof[ivtx] > 4 and abs(pv_rho[ivtx]) < 2.0 :
                NPV += 1


        NPUtrue = 1
        PUweight       = 1.0
        PUweight_MBup  = 1.0
        PUweight_MBdn  = 1.0
        if options.isMC : 
            #@ PU interactions
            event.getByLabel(l_puNtrueInt, h_puNtrueInt)
            puNTrueInt = h_puNtrueInt.product()[0]    # @@@ is this right?
            h_NtrueIntPU.Fill( puNTrueInt )
            NPUtrue = puNTrueInt

            evWeight *= hPUweight.GetBinContent( hPUweight.GetXaxis().FindBin( puNTrueInt ) )
            if options.verbose :
                print 'after purw, evWeight is : ' + str(evWeight)


            PUweight      = hPUweight.GetBinContent( hPUweight.GetXaxis().FindBin( puNTrueInt ) )
            PUweight_MBup = hPUweight_MBup.GetBinContent( hPUweight_MBup.GetXaxis().FindBin( puNTrueInt ) )
            PUweight_MBdn = hPUweight_MBdn.GetBinContent( hPUweight_MBdn.GetXaxis().FindBin( puNTrueInt ) )

            #@ PU errors
            #instructions to generate root files: https://twiki.cern.ch/twiki/bin/view/CMS/PileupJSONFileforData#2015_Pileup_JSON_Files
            pu_nom = hPU_NOM.GetBinContent( hPU_NOM.GetXaxis().FindBin( puNTrueInt) )
            pu_up  = hPU_UP.GetBinContent( hPU_UP.GetXaxis().FindBin( puNTrueInt) )
            pu_dn  = hPU_DN.GetBinContent( hPU_DN.GetXaxis().FindBin( puNTrueInt) )

            if pu_nom == 0.:
                PU_CorrUp[0] = 0.
                PU_CorrDn[0] = 0.
            else:
                PU_CorrUp[0] = pu_up/pu_nom
                PU_CorrDn[0] = pu_dn/pu_nom
            

        if options.isZprime or options.isttbar:
            #@Event weight errors
            #instructions: https://indico.cern.ch/event/460462/contribution/3/attachments/1184257/1717129/PPD_Review_for_B2G.pdf
            gotLHE = event.getByLabel( l_lhe, h_lhe )
            lhe = h_lhe.product()
           
            #Q^2 up and down
            maxQ2wgt_frac = 1
            minQ2wgt_frac = 1
            
            for i_lhe in range(0,9):
                if i_lhe != 5 and i_lhe != 7:
                    Q2wgt = lhe.weights()[i_lhe].wgt
                    Q2wgt_frac = Q2wgt/(lhe.weights()[0].wgt)
                    maxQ2wgt_frac = max(maxQ2wgt_frac, Q2wgt_frac)
                    minQ2wgt_frac = min(minQ2wgt_frac, Q2wgt_frac)
                    if options.verbose :
                        print str(i_lhe) + ".)"
                        print "Q^2 LHE weight: " + str(Q2wgt)
                        Q2wgt_norm = Q2wgt/(lhe.originalXWGTUP())
                        print "Normalized Q2wgt: " + str(Q2wgt_norm)
                        print "Fractional Q2wgt (compared to central value): " + str(Q2wgt_frac)

            Q2wgt_up = maxQ2wgt_frac
            Q2wgt_down = minQ2wgt_frac
            if options.verbose :
                print "Q^2 weight up: " + str(Q2wgt_up)
                print "Q^2 weight down: " + str(Q2wgt_down)
                print ""

            #NNPDF3 PDF up and down
            NNPDF3wgtAvg = 0.0
            NNPDF3wgtRMS = 0.0
            PDFcentral = 1.0
                
            if options.isZprime:
                PDFstart = 111
                PDFend = 211
                PDFcentral = lhe.weights()[110].wgt 
            else:
                PDFstart = 9
                PDFend = 109

            if options.verbose:
                print "************************"
                
            #Making sure central PDF isn't zero
            if PDFcentral == 0:
                if options.verbose :
                    print "Unphysical: central PDF weight is zero!"
            else:
                for i_lhePDF in range(PDFstart,PDFend):
                    NNPDF3wgt = lhe.weights()[i_lhePDF].wgt
                    NNPDF3wgt_frac = NNPDF3wgt/(PDFcentral)
                    NNPDF3wgtAvg += NNPDF3wgt_frac
                    if options.verbose:
                        print "-----"
                        print i_lhePDF - PDFstart
                        print "Fractional PDF weight: " + str(NNPDF3wgt_frac)
                        print "-----"
                        print ""
                NNPDF3wgtAvg = NNPDF3wgtAvg/100
                if options.verbose:
                    print NNPDF3wgtAvg
                for i_lhePDF in range(PDFstart,PDFend):
                    NNPDF3wgt = lhe.weights()[i_lhePDF].wgt
                    NNPDF3wgt_frac = NNPDF3wgt/(PDFcentral)
                    NNPDF3wgtRMS += (NNPDF3wgt_frac - NNPDF3wgtAvg)*(NNPDF3wgt_frac - NNPDF3wgtAvg)
 
            NNPDF3wgtRMS = sqrt(NNPDF3wgtRMS/99)
            if options.verbose:
                print NNPDF3wgtRMS
            if PDFcentral == 0:
                NNPDF3wgt_up = 0.
                NNPDF3wgt_down = 0.
            else:
                NNPDF3wgt_up = 1.0 + NNPDF3wgtRMS
                NNPDF3wgt_down = 1.0 - NNPDF3wgtRMS
            if options.verbose:
                print "NNPDF RMS: " + str(NNPDF3wgtRMS)
                print "NNPDF UP: " + str(NNPDF3wgt_up)
                print "NNPDF DOWN: " + str(NNPDF3wgt_down)
                print "************************"
                print ""
        elif options.isRSG:

            h_pdfWtUp = Handle("double")
            l_pdfWtUp = ("pdfweights", "pdfWtUp" , "PDFANA")
            h_pdfWtDn = Handle("double")
            l_pdfWtDn = ("pdfweights", "pdfWtDn" , "PDFANA")
            

            event.getByLabel(l_pdfWtUp, h_pdfWtUp)
            event.getByLabel(l_pdfWtDn, h_pdfWtDn)
            
            Q2wgt_up = -999
            Q2wgt_down = -999
            NNPDF3wgt_up = h_pdfWtUp.product()[0]
            NNPDF3wgt_down = h_pdfWtDn.product()[0]

        else:
            Q2wgt_up = -999
            Q2wgt_down = -999
            NNPDF3wgt_up = -999
            NNPDF3wgt_down = -999
             
        
        h_NPVert.Fill( NPV )
        h_NPVertWeighted.Fill( NPV, evWeight )
        
        if NPV == 0 :
            if options.verbose :
                print "Event has no good primary vertex."
            continue
            
        h_CutFlow_AllHad    .Fill("NPV",1)
        h_CutFlow_SemiLept  .Fill("NPV",1) 

        if options.isMC and ( options.deweightFlat or options.negativeWeights ) : 
            # Event weights
            gotGenerator = event.getByLabel( l_generator, h_generator )
            generator = h_generator.product()


            if not gotGenerator :
                continue
                        
            if options.deweightFlat :
                pthat = 0.0
                if generator.hasBinningValues() :
                    pthat = generator.binningValues()[0]
                    evWeight *= 1/pow(pthat/15.,4.5)
                    if options.verbose : 
                        print 'after deweight flat, evWeight is : ' + str(evWeight)
            if options.negativeWeights and gotGenerator :

                ## if options.verbose :
                ##     for lheInfo in lhe :
                ##         print lheInfo.tag()
                ##         for iline in lheInfo.lines() :
                ##             print iline
                
                evtWeights = generator.weights()
                iweight = generator.weight()
                if iweight < 0 : 
                    evWeight *= -1.0
                    Nevents_weighted -= 1
                else :
                    Nevents_weighted += 1
                if options.verbose : 
                    print 'after negative weights, evWeight is : ' + str(evWeight)
                    print 'got negative weights for generator, weight = ' + str( iweight )
                    print 'now Nevents_weight = ' + str(Nevents_weighted)

                             
        #@ RHO VALUE
        event.getByLabel( l_rho, h_rho )
        if len(h_rho.product()) == 0 :
            print "Event has no rho values."
            continue
        else:
            rho = h_rho.product()[0]
            if options.verbose :
                print 'rho = {0:6.2f}'.format( rho )

        h_CutFlow_AllHad    .Fill("NoRho",1)
        h_CutFlow_SemiLept  .Fill("NoRho",1) 

        #EVENT MUON HANDLE FILLING
        event.getByLabel ( l_muPt, h_muPt )
        event.getByLabel ( l_muEta, h_muEta )
        event.getByLabel ( l_muPhi, h_muPhi )
        event.getByLabel ( l_muTight, h_muTight )
        event.getByLabel ( l_muLoose, h_muLoose )
        event.getByLabel ( l_muMass, h_muMass ) 
        event.getByLabel ( l_muDz, h_muDz )
        event.getByLabel ( l_muKey, h_muKey )
        event.getByLabel ( l_muCharge, h_muCharge )
        event.getByLabel ( l_muIso04, h_muIso04 )

        #@ Muon Selection

        goodmuonPt = []
        goodmuonEta = []
        goodmuonPhi = []
        goodmuonMass = []
        goodmuonKey = []
        goodmuonCharge = []
        goodmuonIso = []

        #Use MuPt as iterater due to no definite iterator value in ntuples
        if len(h_muEta.product()) > 0:
            muonPt = h_muPt.product()
            muonEta = h_muEta.product()
            muonPhi = h_muPhi.product()
            muonTight = h_muTight.product()
            muonLoose = h_muLoose.product()
            muonMass = h_muMass.product()
            muonDz = h_muDz.product()
            muKey = h_muKey.product()
            muCharge = h_muCharge.product()
            muIso = h_muIso04.product()
            for imuon, muon in enumerate(muonPt): #{ Loop over all muons in event
                NMu = NMu + 1
                if muonPt[imuon] < options.minMuonPt :  #$ Muon cuts
                    continue
                else: 
                    NPassMuonPtCut = NPassMuonPtCut + 1

                if abs(muonEta[imuon]) > options.maxMuonEta :
                    continue
                else:
                    NPassMuonEtaCut = NPassMuonEtaCut + 1
                if muonDz[imuon] > 5.0:
                    continue
                else:
                    NPassMuonDzCut = NPassMuonDzCut + 1
                if muonLoose[imuon] == 0 :
                    continue
                else:
                    NPassMuonTightCut = NPassMuonTightCut + 1
                NPassMuonTot += 1 
                goodmuonPt.append(muonPt[imuon])
                goodmuonEta.append(muonEta[imuon])
                goodmuonPhi.append(muonPhi[imuon])
                goodmuonMass.append(muonMass[imuon])
                goodmuonKey.append(muKey[imuon])
                goodmuonCharge.append(muCharge[imuon])
                goodmuonIso.append( muIso[imuon] )
                if options.verbose  : 
                    print "muon %2d: keys " %(imuon)
                    for ikey in muKey[imuon] : 
                        print   " %4d" % ( ikey ),
                    print "     ---> pt %4.1f, eta %+5.3f phi %+5.3f dz(PV) %+5.3f, POG loose id %d, tight id %d., iso %d" %  \
                        ( muonPt[imuon], muonEta[imuon],muonPhi[imuon], muonDz[imuon], muonLoose[imuon], muonTight[imuon], muIso[imuon])

                #} End Muon loop
                        
        event.getByLabel ( l_elPt, h_elPt )
        event.getByLabel ( l_elEta, h_elEta )
        event.getByLabel ( l_elPhi, h_elPhi )
        event.getByLabel ( l_elTight, h_elTight )
        event.getByLabel ( l_elLoose, h_elLoose )
        event.getByLabel ( l_eldEtaIn, h_eldEtaIn )
        event.getByLabel ( l_eldPhiIn, h_eldPhiIn )
        event.getByLabel ( l_elHoE, h_elHoE )
        event.getByLabel ( l_elfull5x5siee, h_elfull5x5siee )
        event.getByLabel ( l_elE, h_elE )
        event.getByLabel ( l_elD0, h_elD0)
        event.getByLabel ( l_elDz, h_elDz)
        event.getByLabel ( l_elIso03, h_elIso03)
        event.getByLabel ( l_elhasMatchedConVeto, h_elhasMatchedConVeto)
        event.getByLabel ( l_elooEmooP, h_elooEmooP)
        event.getByLabel ( l_elMass, h_elMass )
        event.getByLabel ( l_elscEta , h_elscEta )
        event.getByLabel ( l_elKey, h_elKey )
        event.getByLabel ( l_elCharge, h_elCharge )
        
        #@ Electron Selection      

        goodelectronPt = []
        goodelectronEta = []
        goodelectronPhi = []
        goodelectronMass = []
        goodelectronKey = []
        goodelectronCharge = []
        goodelectronIso = []



        if len(h_elPt.product()) > 0:
            electronPt = h_elPt.product()
            electronEta = h_elEta.product()
            electronPhi = h_elPhi.product()
            electronTight = h_elTight.product()
            electronLoose = h_elLoose.product()
            electronecalEnergy = h_elE.product()
            electrondEtaIn = h_eldEtaIn.product()
            electrondPhiIn = h_eldPhiIn.product()
            electronHoE=h_elHoE.product()
            electronfullsiee=h_elfull5x5siee.product()
            electronooEmooP=h_elooEmooP.product()
            electronD0 = h_elD0.product()
            electronDz = h_elDz.product()
            electronabsiso = h_elIso03.product()
            electronMass = h_elMass.product()
            electronscEta = h_elscEta.product()
            elKey = h_elKey.product()
            passConversionVeto = h_elhasMatchedConVeto.product()
            electronCharge = h_elCharge.product()
            #for i in xrange( len(electronPt.size() ) ) :
            if len(electronPt) > 0 :
                for ielectron, electron in enumerate(electronPt): #{ Loop over all electrons in event
                    NEl = NEl + 1
                    iePt = electronPt[ielectron]   
                    ieEta = electronEta[ielectron]
                    iePhi = electronPhi[ielectron]
                    ieMass = electronMass[ielectron]
                    ieCharge = electronCharge[ielectron]
                    iedEtaIn = electrondEtaIn[ielectron]
                    iedPhiIn = electrondPhiIn[ielectron]
                    ieHoE = electronHoE[ielectron]
                    ieD0 = electronD0[ielectron]
                    ieDz = electronDz[ielectron]
                    ieEmooP = electronooEmooP[ielectron]
                    ie5x5sigma = electronfullsiee[ielectron]
                    ieIso = electronabsiso[ielectron]

                    if iePt > options.minElectronPt:
                        NPassElPtCut = NPassElPtCut + 1
                    else:
                        continue
                    if abs(ieEta) < options.maxElectronEta : #$ Electron eta cut (based on options)
                        NPassElEtaCut = NPassElEtaCut + 1
                    else:
                        continue
                    goodElectron = False #$ Electron ID Cut (current WP Loose : https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2 )
                    if abs( ieEta ) <= 1.479 :
                        if abs(iedEtaIn) < 0.00976 :
                            NPassEldEtaIn+=1
                        else :
                            continue
                        if abs(iedPhiIn ) < 0.0929 :
                            NPassEldPhiIn+=1
                        else :
                            continue
                        if ie5x5sigma < 0.0105 :
                            NPassEl5x5+= 1
                        else :
                            continue
                        if ieHoE <  0.0765 :
                            NPassElHoE+= 1
                        else :
                            continue
                        if abs(ieD0) < 0.0227 :
                            NPassElD0+=1
                        else :
                            continue
                        if abs(ieDz) <  0.379 :
                            NPassElDz+=1
                        else :
                            continue
                        if ieEmooP <  0.184 :
                            NPassElEmooP+=1
                            goodElectron = True
                        else :
                            continue
                    else :
                        if abs(iedEtaIn) < 0.00952 :
                            NPassEldEtaIn+=1
                        else :
                            continue
                        if abs(iedPhiIn ) < 0.181 :
                            NPassEldPhiIn+=1
                        else :
                            continue 
                        if ie5x5sigma < 0.0318 :
                            NPassEl5x5+= 1
                        else :
                            continue
                        if ieHoE <  0.0824 :
                            NPassElHoE+= 1
                        else :
                            continue
                        if abs(ieD0) <  0.242 :
                            NPassElD0+=1
                        else :
                            continue
                        if abs(ieDz) < 0.921 :
                            NPassElDz+=1
                        else :
                            continue
                        if ieEmooP <  0.125 :
                            NPassElEmooP+=1
                            goodElectron = True
                        else :
                            continue                       
                    if goodElectron == True : 
                        NPassGoodElCut = NPassGoodElCut + 1 
                    #if elKey[ielectron] != 0 and elKey[ielectron] != 18446744073709551616 :
                        NPassElKeyCut+=1
                        goodelectronPt.append( iePt )
                        goodelectronEta.append( ieEta )
                        goodelectronPhi.append( iePhi )
                        goodelectronMass.append( ieMass )
                        goodelectronKey.append( elKey[ielectron] )
                        goodelectronCharge.append( ieCharge )
                        goodelectronIso.append( ieIso )
                        if options.verbose : 
                            print "elec %2d: keys " %(ielectron)
                            for ikey in elKey[ielectron] : 
                                print   " %4d" % ( ikey ),
                            print "     ---> , pt %4.1f, eta %4.1f, phi %+5.3f %f" % ( iePt, ieEta, iePhi, ieIso)
                    
                    #} End Electron Loop


        #^ define the type of decay channel based on number of leptons in event
        # Skip if not any of these

        #@ Channel Definition
        
        Hadronic = (len(goodmuonPt) + len(goodelectronPt)) == 0
        Leptonic = (len(goodmuonPt) + len(goodelectronPt)) == 2 
        SemiLeptonic = (len(goodmuonPt) + len(goodelectronPt)) == 1         

        #& cutflow
        if Leptonic:
            NeventsDiLeptonic  +=1  
        if SemiLeptonic:
            NeventsSemiLeptonic  +=1  
            if ( len(goodmuonPt)==1 ):
                NeventsSemiLeptonicMuon +=1
            if ( len(goodelectronPt)==1 ):
                NeventsSemiLeptonicElectron +=1
        if Hadronic:
            NeventsAllHadronic  +=1  


        if options.verbose :
            print 'Number of good muons = ' + str( len(goodmuonPt) )
            print 'Number of good electrons = ' + str( len(goodelectronPt) )

            if options.isMC and options.getGenInfo :
                if ngenE > 0 and len(goodelectronPt) == 0 :
                    print '--------------------'
                    print 'Electron not found : %6d %6d %7.2f %6.3f %6.3f %6.3f' % \
                        (  genPartID[genEIndex[0]], genPartStatus[genEIndex[0]], \
                               genPartPt[genEIndex[0]], genPartEta[genEIndex[0]], genPartPhi[genEIndex[0]], genPartMass[genEIndex[0]] )
                    print 'Electrons : ' 
                    for ielectron in xrange(0, len(electronPt) ) :
                        print "      pt %4.1f, eta %4.1f, phi %+5.3f " % ( electronPt[ielectron], electronEta[ielectron], electronPhi[ielectron] )
                if ngenMu > 0 and len(goodmuonPt) == 0 :
                    print '--------------------'
                    print 'Muon not found     : %6d %6d %7.2f %6.3f %6.3f %6.3f' % \
                        (  genPartID[genMuIndex[0]], genPartStatus[genMuIndex[0]], \
                               genPartPt[genMuIndex[0]], genPartEta[genMuIndex[0]], genPartPhi[genMuIndex[0]], genPartMass[genMuIndex[0]] )
                    print 'Muons : '
                    for imuon in xrange(0, len(muonPt) ) :
                        print "     pt %4.1f, eta %+5.3f phi %+5.3f dz(PV) %+5.3f, POG loose id %d, tight id %d." %  \
                            ( muonPt[imuon], muonEta[imuon],muonPhi[imuon], muonDz[imuon], muonLoose[imuon], muonTight[imuon])

        NeventsBeforeChannelSelect +=1
        if options.selection == 0 and not Leptonic :
            continue
        elif options.selection == 1 and not SemiLeptonic :
            continue
        elif options.selection == 2 and not Hadronic :
            continue
        NeventsAfterChannelSelect  +=1  

        if Hadronic :
            h_CutFlow_AllHad    .Fill("ChannelSelect",1)
        if SemiLeptonic :
            h_CutFlow_SemiLept  .Fill("ChannelSelect",1) 


        #@Get MET HERE
        event.getByLabel ( l_metPt, h_metPt )
        event.getByLabel ( l_metPx, h_metPx )
        event.getByLabel ( l_metPy, h_metPy )
        event.getByLabel ( l_metPhi, h_metPhi )
        
        if len(h_metPx.product()) > 0 :
            metPx = h_metPx.product()[0]
            metPy = h_metPy.product()[0]
            metPhi = h_metPhi.product()[0]
            metPt = h_metPt.product()[0]

        #@ Dileptonic
        if Leptonic == True : 
            #^ Dilepton Selection        
            if len(goodmuonPt) == 2 and goodmuonCharge[0]*goodmuonCharge[1]<0:
                dimuonCandidate = True
            else :
                dimuonCandidate = False

            if len(goodelectronPt) == 2 and goodelectronCharge[0]*goodelectronCharge[1]<0:
                dielectronCandidate = True
            else :
                dielectronCandidate = False

            if len(goodmuonPt) == 1 and len(goodelectronPt)==1 and  goodelectronCharge[0]*goodmuonCharge[0]<0 :
                mixedCandidate = True
            else :
                mixedCandidate = False
            if dimuonCandidate == False and dielectronCandidate == False and mixedCandidate == False : 
                if options.verbose :
                    print " Event with 2 Leptons but not of opposite charge, skipping "
                continue
            
            if dimuonCandidate :
                Lepton1 = ROOT.TLorentzVector()
                Lepton2 = ROOT.TLorentzVector()
                Muon1 = ROOT.TLorentzVector()
                Muon2 = ROOT.TLorentzVector()
                Lepton1.SetPtEtaPhiM( goodmuonPt[0],
                                      goodmuonEta[0],
                                      goodmuonPhi[0],
                                      goodmuonMass[0] )
                Lepton1ObjKey = goodmuonKey[0]
                Lepton2.SetPtEtaPhiM( goodmuonPt[1],
                                      goodmuonEta[1],
                                      goodmuonPhi[1],
                                      goodmuonMass[1] )
                Lepton2ObjKey = goodmuonKey[1]
                Muon1.SetPtEtaPhiM( goodmuonPt[0],
                                      goodmuonEta[0],
                                      goodmuonPhi[0],
                                      goodmuonMass[0] )
                Muon1ObjKey = goodmuonKey[0]
                Muon2.SetPtEtaPhiM( goodmuonPt[1],
                                      goodmuonEta[1],
                                      goodmuonPhi[1],
                                      goodmuonMass[1] )
                Muon2ObjKey = goodmuonKey[1]
            elif dielectronCandidate :
                Lepton1 = ROOT.TLorentzVector()
                Lepton2 = ROOT.TLorentzVector()
                Electron1 = ROOT.TLorentzVector()
                Electron2 = ROOT.TLorentzVector()
                Lepton1.SetPtEtaPhiM( goodelectronPt[0],
                                      goodelectronEta[0],
                                      goodelectronPhi[0],
                                      goodelectronMass[0] )
                Lepton1ObjKey = goodelectronKey[0]
                Lepton2.SetPtEtaPhiM( goodelectronPt[1],
                                      goodelectronEta[1],
                                      goodelectronPhi[1],
                                      goodelectronMass[1] )
                Lepton2ObjKey = goodelectronKey[1]
                Electron1.SetPtEtaPhiM( goodelectronPt[0],
                                      goodelectronEta[0],
                                      goodelectronPhi[0],
                                      goodelectronMass[0] )
                Electron1ObjKey = goodelectronKey[0]
                Electron2.SetPtEtaPhiM( goodelectronPt[1],
                                      goodelectronEta[1],
                                      goodelectronPhi[1],
                                      goodelectronMass[1] )
                Electron2ObjKey = goodelectronKey[1]
            elif mixedCandidate :
                Lepton1 = ROOT.TLorentzVector()
                Lepton2 = ROOT.TLorentzVector()
                Muon1 = ROOT.TLorentzVector()
                Electron2 = ROOT.TLorentzVector()
                Lepton1.SetPtEtaPhiM( goodmuonPt[0],
                                    goodmuonEta[0],
                                    goodmuonPhi[0],
                                    goodmuonMass[0] )
                Lepton1ObjKey = goodmuonKey[0]
                Lepton2.SetPtEtaPhiM( goodelectronPt[0],
                                        goodelectronEta[0],
                                        goodelectronPhi[0],
                                        goodelectronMass[0] )
                Lepton2ObjKey = goodelectronKey[0]
                Muon1.SetPtEtaPhiM( goodmuonPt[0],
                                    goodmuonEta[0],
                                    goodmuonPhi[0],
                                    goodmuonMass[0] )
                Muon1ObjKey = goodmuonKey[0]
                Electron2.SetPtEtaPhiM( goodelectronPt[0],
                                        goodelectronEta[0],
                                        goodelectronPhi[0],
                                        goodelectronMass[0] )
                Electron2ObjKey = goodelectronKey[0]
                
        #@ Semileptonic
        muJets = False
        eleJets = False
        theLepton = ROOT.TLorentzVector()
        theMuon = ROOT.TLorentzVector()
        theElectron = ROOT.TLorentzVector()
        theLeptonPtRel = -1.0
        theLeptonDRMin = -1.0
        theLeptonIso = -1.0
        if SemiLeptonic :

            if len(goodmuonPt) > 0 :
                muJets = True
                # theLepton = ROOT.TLorentzVector()
                theLepton.SetPtEtaPhiM( goodmuonPt[0],
                                        goodmuonEta[0],
                                        goodmuonPhi[0],
                                        goodmuonMass[0] )
                theLeptonObjKey = goodmuonKey[0]
                theMuon = ROOT.TLorentzVector()
                theMuon.SetPtEtaPhiM( goodmuonPt[0],
                                        goodmuonEta[0],
                                        goodmuonPhi[0],
                                        goodmuonMass[0] )
                theMuonObjKey = goodmuonKey[0]
                theLeptonIso = goodmuonIso[0]
            else :
                eleJets = True
                # theLepton = ROOT.TLorentzVector()
                theLepton.SetPtEtaPhiM( goodelectronPt[0],
                                        goodelectronEta[0],
                                        goodelectronPhi[0],
                                        goodelectronMass[0] )
                theLeptonObjKey = goodelectronKey[0]
                theElectron = ROOT.TLorentzVector()
                theElectron.SetPtEtaPhiM( goodelectronPt[0],
                                        goodelectronEta[0],
                                        goodelectronPhi[0],
                                        goodelectronMass[0] )
                theElectronObjKey = goodelectronKey[0]
                theLeptonIso = goodelectronIso[0]

                                   
        # EVENT AK4 JET HANDLES
        event.getByLabel ( l_jetsAK4Pt, h_jetsAK4Pt )
        event.getByLabel ( l_jetsAK4Eta, h_jetsAK4Eta )
        event.getByLabel ( l_jetsAK4Phi, h_jetsAK4Phi )
        event.getByLabel ( l_jetsAK4Mass, h_jetsAK4Mass )
        event.getByLabel ( l_jetsAK4Energy, h_jetsAK4Energy )
        event.getByLabel ( l_jetsAK4JEC, h_jetsAK4JEC )
        event.getByLabel ( l_jetsAK4CSV, h_jetsAK4CSV )
        event.getByLabel ( l_jetsAK4NumDaughters, h_jetsAK4NumDaughters)
        event.getByLabel ( l_jetsAK4Area, h_jetsAK4Area )

        event.getByLabel ( l_jetsAK4Keys, h_jetsAK4Keys )

        event.getByLabel ( l_jetsAK4nHadEnergy, h_jetsAK4nHadEnergy)
        event.getByLabel ( l_jetsAK4nEMEnergy, h_jetsAK4nEMEnergy )
        event.getByLabel ( l_jetsAK4cHadEnergy, h_jetsAK4cHadEnergy )
        event.getByLabel ( l_jetsAK4HFHadronEnergy, h_jetsAK4HFHadronEnergy )
        event.getByLabel ( l_jetsAK4cEMEnergy, h_jetsAK4cEMEnergy )
        event.getByLabel ( l_jetsAK4numDaughters, h_jetsAK4numDaughters )
        event.getByLabel ( l_jetsAK4cMultip, h_jetsAK4cMultip )
        event.getByLabel ( l_jetsAK4Y, h_jetsAK4Y )

        
        #@ AK4 jet selection
        
        # This array stores all of our favorite jets , those that meet the selection criteria
        ak4JetsGood = []
        ak4JetsGoodbDiscrim = []
        # For selecting leptons, look at 2-d cut of dRMin, ptRel of
        # lepton and nearest jet that has pt > 30 GeV
        dRMin = 9999.0
        dR2Min = 9999.0
        dRMinsave = 9999.0
        inearestJet = -1    # Index of nearest jet
        i2nearestJet = -1
        inearestJetsave = -1 # Index to save for dilepton channel in case  jet is closer to other lepton
        nearest2JetMass = None
        nearestJetMass = None   # Nearest jet
        nearestJetP4 = None
        nearest2JetP4 = None
        nearestJetbDiscrim = 0.0

# *** added ifarJet1, farJet2bDiscrim etc...

        if len(h_jetsAK4Pt.product()) > 0 :
            AK4Pt = h_jetsAK4Pt.product()
            AK4Eta = h_jetsAK4Eta.product()
            AK4Phi = h_jetsAK4Phi.product()
            AK4Mass = h_jetsAK4Mass.product()
            AK4Energy = h_jetsAK4Energy.product()
            AK4CSV = h_jetsAK4CSV.product()
            AK4NumDaughters = h_jetsAK4NumDaughters.product()
            AK4Area = h_jetsAK4Area.product()

            AK4Keys = h_jetsAK4Keys.product()

            if options.verbose :
                print '----------------'
                print 'N AK4 keys = ' + str( len(AK4Keys)) + ', N AK4Pt = ' + str(len(AK4Pt))

            AK4JEC = h_jetsAK4JEC.product()
            AK4nHadE = h_jetsAK4nHadEnergy.product()
            AK4nEME = h_jetsAK4nEMEnergy.product()
            AK4cHadE =  h_jetsAK4cHadEnergy.product()
            AK4HFHadE = h_jetsAK4HFHadronEnergy.product()
            AK4cEME =  h_jetsAK4cEMEnergy.product()
            AK4numDaughters = h_jetsAK4numDaughters.product()
            AK4cMultip =  h_jetsAK4cMultip.product()
            AK4Y =  h_jetsAK4Y.product()    
            
        if Hadronic : # Don't care about AK4 jets if hadronic event
            length = 0
        else :
            length = len(AK4Pt)

        for i in range(0,length): #{ Loop over AK4 Jets
            NAK4Jets = NAK4Jets + 1
            #get the jets transverse momentum, Eta, Phi and Mass ( gives same information as the 4 vector)
            #v = TLorentzVector()
            jetP4Raw = ROOT.TLorentzVector()
            jetP4Raw.SetPtEtaPhiM( AK4Pt[i], AK4Eta[i], AK4Phi[i], AK4Mass[i])

            # Get correction applied to B2G ntuples
            AK4JECFromB2GAnaFW = AK4JEC[i]
            
            # Remove the old JEC's to get raw energy
            jetP4Raw *= AK4JEC[i] 
                        
            #$ Jet Cut s based on energy distribution
            nhf = AK4nHadE[i] / jetP4Raw.E()
            nef = AK4nEME[i] / jetP4Raw.E()
            chf = AK4cHadE[i] / jetP4Raw.E()
            cef = AK4cEME[i] / jetP4Raw.E()
            nconstituents = AK4NumDaughters[i]
            nch = AK4cMultip[i] 
            goodJet = \
              nhf < 0.99 and \
              nef < 0.99 and \
              chf > 0.00 and \
              cef < 0.99 and \
              nconstituents > 1 and \
              nch > 0

            if options.verbose > 1 :
                print '-----'
                print 'jet index = %2d, nhf = %6.2f, nef = %6.2f, chf = %6.2f, cef = %6.2f, nconstituents = %3d, nch = %3d' % (i, nhf, nef, chf, cef, nconstituents, nch)
                print '   keys : ', 
                for j in range( 0, len(AK4Keys[i]) ) :
                    print ' %d' % ( AK4Keys[i][j] ),
                print ''
            if not goodJet :
                if options.verbose > 1 : 
                    print '   bad jet pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}'.format (
                        jetP4Raw.Perp(), jetP4Raw.Rapidity(), jetP4Raw.Phi(), jetP4Raw.M()
                        )
                continue
            NPassGoodJetAK4Cut = NPassGoodJetAK4Cut + 1
            if options.verbose > 1 :
                print '   raw jet pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}'.format (
                    jetP4Raw.Perp(), jetP4Raw.Rapidity(), jetP4Raw.Phi(), jetP4Raw.M()
                    )

            #Subtract the lepton 4-Vectors from the jets neighboring it
            cleaned = False
            zeroedEnergy = False # if the lepton energy is higher than jet, set it to zero

            if options.keyBasedCleaning : 
                if SemiLeptonic : 
                    if theLepton.DeltaR(jetP4Raw) < 0.4: 
                        # Check all daughters of jets close to the lepton
                        pfcands = int(AK4NumDaughters[i])
                        for j in range(0,pfcands) : #{ Loop over keys                
                            # If any of the jet daughters matches the good lepton, remove the lepton p4 from the jet p4
                            if AK4Keys[i][j] in theLeptonObjKey : 
                                if options.verbose :
                                    print '     -----> removing lepton, pt/eta/phi = {0:6.2f},{1:6.2f},{2:6.2f}'.format(
                                        theLepton.Perp(), theLepton.Eta(), theLepton.Phi()
                                        )
                                if theLepton.Energy() > jetP4Raw.Energy() :
                                    zeroedEnergy = True
                                jetP4Raw -= theLepton
                                cleaned = True
                                break
                        #} End Loop over Jet Keys

                elif Leptonic :
                    if Lepton1.DeltaR(jetP4Raw) < 0.4: 
                        # Check all daughters of jets close to the lepton
                        pfcands = int(AK4NumDaughters[i])
                        for j in range(0,pfcands) : #{ Loop over jet keys            
                            # If any of the jet daughters matches the good lepton, remove the lepton p4 from the jet p4
                            if AK4Keys[i][j] in Lepton1ObjKey : 
                                if options.verbose :
                                    print '     -----> removing lepton, pt/eta/phi = {0:6.2f},{1:6.2f},{2:6.2f}'.format(
                                        Lepton1.Perp(), Lepton1.Eta(), Lepton1.Phi()
                                        )
                                if theLepton1.Energy() > jetP4Raw.Energy() :
                                    zeroedEnergy = True
                                jetP4Raw -= Lepton1
                                cleaned = True
                                break
                            #} End loop over jet keys
                    if Lepton2.DeltaR(jetP4Raw) < 0.4: 
                        # Check all daughters of jets close to the lepton
                        pfcands = int(AK4NumDaughters[i])
                        for j in range(0,pfcands) : #{ Loop over Jet Keys            
                            # If any of the jet daughters matches the good lepton, remove the lepton p4 from the jet p4
                            if AK4Keys[i][j] in Lepton2ObjKey : 
                                if options.verbose :
                                    print '     -----> removing lepton, pt/eta/phi = {0:6.2f},{1:6.2f},{2:6.2f}'.format(
                                        Lepton2.Perp(), Lepton2.Eta(), Lepton2.Phi()
                                        )
                                if theLepton2.Energy() > jetP4Raw.Energy() :
                                    zeroedEnergy = True
                                jetP4Raw -= Lepton2
                                cleaned = True
                                break
                            #} End loop over jet keys
            else :  # Delta-R based cleaning
                if SemiLeptonic : 
                    if theLepton.DeltaR(jetP4Raw) < 0.4: 
                        if options.verbose :
                            print '     -----> removing lepton, pt/eta/phi = {0:6.2f},{1:6.2f},{2:6.2f}'.format(
                                theLepton.Perp(), theLepton.Eta(), theLepton.Phi()
                                )
                        if theLepton.Energy() > jetP4Raw.Energy() :
                            zeroedEnergy = True
                        jetP4Raw -= theLepton
                        cleaned = True


                elif Leptonic :
                    if Lepton1.DeltaR(jetP4Raw) < 0.4:
                        if theLepton1.Energy() > jetP4Raw.Energy() :
                            zeroedEnergy = True
                        jetP4Raw -= Lepton1
                        cleaned = True

                    if Lepton2.DeltaR(jetP4Raw) < 0.4:
                        if theLepton2.Energy() > jetP4Raw.Energy() :
                            zeroedEnergy = True
                        jetP4Raw -= Lepton2
                        cleaned = True


            if zeroedEnergy :                
                continue
            #@ Jet energy corrections
            ak4JetCorrector.setJetEta( jetP4Raw.Eta() )
            ak4JetCorrector.setJetPt ( jetP4Raw.Perp() )
            ak4JetCorrector.setJetE  ( jetP4Raw.E() )
            ak4JetCorrector.setJetA  ( AK4Area[i] )
            ak4JetCorrector.setRho   ( rho )
            ak4JetCorrector.setNPV   ( NPV )
            newJEC = ak4JetCorrector.getCorrection()
            jetP4 = jetP4Raw*newJEC
            if jetP4.Perp() > options.minAK4Pt:   #$ Cuts for Pt and Rapidity
                NPassMinAK4PtCut = NPassMinAK4PtCut + 1
            else:
                if options.verbose > 1 :
                   print '   jet failed kinematic cuts'
                continue
            if abs(jetP4.Rapidity()) < options.maxAK4Rapidity:                  
                NPassMaxAK4RapidityCut = NPassMaxAK4RapidityCut + 1
            else:
                if options.verbose > 1 :
                   print '   jet failed kinematic cuts'
                continue

            # NPassAK4KinTot += 1
            if SemiLeptonic :
                if eleJets :
                    dR = jetP4.DeltaR(theElectron)
                elif muJets :
                    dR = jetP4.DeltaR(theMuon)
                dR = jetP4.DeltaR(theLepton )
            if Leptonic :
                if dimuonCandidate :
                    dR1 = jetP4.DeltaR(Muon1 )
                    dR2 = jetP4.DeltaR(Muon2 )
                if dielectronCandidate :
                    dR1 = jetP4.DeltaR(Electron1 )
                    dR2 = jetP4.DeltaR(Electron2 )
                if mixedCandidate :
                    dR1 = jetP4.DeltaR(Muon1 )
                    dR2 = jetP4.DeltaR(Electron2 )
                dR1 = jetP4.DeltaR(Lepton1 )
                dR2 = jetP4.DeltaR(Lepton2 )
            ak4JetsGood.append(jetP4)
            ak4JetsGoodbDiscrim.append(AK4CSV[i])
            if options.verbose > 1 :
                print '   corrjet pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}, bdisc = {4:6.2f}'.format (
                    jetP4.Perp(), jetP4.Rapidity(), jetP4.Phi(), jetP4.M(), AK4CSV[i] )
            #@ Find the closest jets to each lepton
            if SemiLeptonic :
                if dR < dRMin :   
                    inearestJet = i
                    nearestJetP4 = jetP4
                    dRMin = dR
                    nearestJetbDiscrim = AK4CSV[i]


            # @@@ SemiLeptonic but not boosted case- here we want 2 AK4 jets one of which is b-tagged  and other which is approx the W mass 
            ## and both far from the lepton 
            elif Leptonic :
                if abs(dR1) < dRMin :
                    #Save in case duplicate bjets
                    inearestJetsave = inearestJet
                    nearestJetP4save = nearestJetP4
                    dRMinsave = dRMin
                    nearestJetbDiscrimsave = nearestJetbDiscrim
                    
                    inearestJet = i
                    nearestJetP4 = jetP4
                    dRMin = dR1
                    nearestJetbDiscrim = AK4CSV[i]
                if abs(dR2) < dR2Min :
                    if i == inearestJet :
                        if abs(dR2) < abs(dR1) :
                            i2nearestJet = i
                            nearest2JetP4 = jetP4
                            dR2Min = abs(dR2)
                            nearest2JetbDiscrim = AK4CSV[i]

                            inearestJet = inearestJetsave
                            nearestJetP4 = nearestJetP4save
                            dRMin = dRMinsave
                            nearestJetbDiscrim = nearestJetbDiscrimsave
                    else :
                        i2nearestJet = i
                        nearest2JetP4 = jetP4
                        dR2Min = abs(dR2)
                        nearest2JetbDiscrim = AK4CSV[i]

            #} End AK4Jet Loop
        if Leptonic and inearestJet < 0 :
            if options.verbose :
                print "Oops missed a nearest jet, going back through AK4 Loop for it"
            for i in xrange( len(ak4JetsGood) ) : 
                if dielectronCandidate :
                   dR1 = ak4JetsGood[i].DeltaR( Electron1 ) 
                elif dimuonCandidate or mixedCandidate :
                   dR1 = ak4JetsGood[i].DeltaR( Muon1 ) 
                dR1 = ak4JetsGood[i].DeltaR( Lepton1 )
                if dR1 < dRMin and i != i2nearestJet:
                    inearestJet = i
                    nearestJetP4 = ak4JetsGood[i]
                    dRMin = dR1
                    nearestJetbDiscrim = ak4JetsGoodbDiscrim[i] 
        #$ Here, we have the AK4 jets and the leptons, and skip if we do not find a jet near the lepton(s)
        if SemiLeptonic :
            NPassWbEvent+= 1 
            if inearestJet < 0 :
                if options.verbose :
                    print '   no nearest jet found, skipping'
                continue
            else :
                NPassNearJCut = NPassNearJCut + 1
                h_CutFlow_SemiLept  .Fill("FoundNearestJet",1) 
                if options.verbose :
                    print '>>>>>>>> nearest jet to lepton is ' + str( inearestJet )
                    print '   corrjet pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}, bdisc = {4:6.2f}'.format (
                        nearestJetP4.Perp(), nearestJetP4.Rapidity(), nearestJetP4.Phi(), nearestJetP4.M(), nearestJetbDiscrim )   


        if Leptonic :
            NPassWbEvent += 1

            if inearestJet >= 0 :
                NPassNearJCut += 1
            if i2nearestJet >= 0:
                NPassNearJ2Cut += 1        

            if inearestJet < 0 or i2nearestJet < 0:
                if options.verbose :
                    print '   no nearest jet found for both leptons, skipping'
                continue
            else :
                if options.verbose :
                    print '>>>>>>>> nearest jet to lepton 1 is ' + str( inearestJet )
                    print '   corrjet pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}, bdisc = {4:6.2f}'.format (
                        nearestJetP4.Perp(), nearestJetP4.Rapidity(), nearestJetP4.Phi(), nearestJetP4.M(), nearestJetbDiscrim )
                    print '>>>>>>>> nearest jet to lepton 2 is ' + str( i2nearestJet )
                    print '   corrjet pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}, bdisc = {4:6.2f}'.format (
                        nearest2JetP4.Perp(), nearest2JetP4.Rapidity(), nearest2JetP4.Phi(), nearest2JetP4.M(), nearest2JetbDiscrim )
        
        #^ Plotting for SemiLeptonic Channel pre 2D cuts
        theLepJet = ROOT.TLorentzVector()
        theLepJetBDisc = -1.0
        theElJet = ROOT.TLorentzVector()
        theElJetBDisc = -1.0
        theMuJet = ROOT.TLorentzVector()
        theMuJetBDisc = -1.0
        ptRel = 0
        htLep = 0
        
        if SemiLeptonic :

            h_ptLep[ALL_NDX].Fill( theLepton.Perp(), evWeight )
            if eleJets :
                h_ptLep[EL_NDX].Fill( theLepton.Perp(), evWeight )
            if muJets :
                h_ptLep[MU_NDX].Fill( theLepton.Perp(), evWeight )


            h_etaLep[ALL_NDX].Fill( theLepton.Eta(), evWeight )
            if eleJets :
                h_etaLep[EL_NDX].Fill( theLepton.Eta(), evWeight )
            if muJets :
                h_etaLep[MU_NDX].Fill( theLepton.Eta(), evWeight )
                                            
            htLep = theLepton.Perp() + metPt

            ht = 0
            for iak4,ak4jet in enumerate(ak4JetsGood) :
                ht += ak4jet.Perp()

            st = ht + htLep

            theLepJet = nearestJetP4
            theLepJetBDisc = nearestJetbDiscrim
            if eleJets :
                theElJet = nearestJetP4
                theElJetBDisc = nearestJetbDiscrim      
            else :
                theMuJet = nearestJetP4
                theMuJetBDisc = nearestJetbDiscrim
            ptRel = theLepJet.Perp( theLepton.Vect() )
            
            #@ 2D Cuts
            theLeptonPtRel = ptRel
            theLeptonDRMin = dRMin
            pass2D = ptRel > 40.0 or dRMin > 0.4
            h_2DCut[ALL_NDX].Fill( dRMin,ptRel, evWeight)
            h_dRMin[ALL_NDX].Fill( dRMin, evWeight )
            if muJets :
                h_2DCut[MU_NDX].Fill( dRMin,ptRel, evWeight)
                h_dRMin[MU_NDX].Fill( dRMin, evWeight )
            if eleJets :
                h_2DCut[EL_NDX].Fill( dRMin,ptRel, evWeight)
                h_dRMin[EL_NDX].Fill( dRMin, evWeight )
            if options.verbose :
                print '>>>>>>>>>>>>>>'
                print '2d cut : dRMin = {0:6.2f}, ptRel = {1:6.2f}'.format( dRMin, ptRel )
                print '>>>>>>>>>>>>>>'
            if not options.ignore2D and pass2D == False :
                continue
            else:
                NPass2DCut += 1
                if muJets :
                   NPassMuon2DCut += 1
                elif eleJets :
                   NPassEl2DCut += 1
                h_CutFlow_SemiLept  .Fill("2Dcut",1) 


            
                
                   
            if options.metMin != None : 
                passMET = metPt > options.metMin
            else :
                passMET = True
            
            if options.htLepMin != None : 
                passHTLep = htLep > options.htLepMin
            else :
                passHTLep = True


            if options.stMin != None :
                passST = st > options.stMin
            else :
                passST = True

            h_met[ALL_NDX].Fill( metPt, evWeight )
            if muJets :
                h_met[MU_NDX].Fill( metPt, evWeight )
            if eleJets :
                h_met[EL_NDX].Fill( metPt, evWeight )
            
            if passMET == False :
                continue
            else :
                NPassMET += 1
                h_CutFlow_SemiLept  .Fill("METcut",1) 


            h_htLep[ALL_NDX].Fill( htLep, evWeight )
            if muJets :
                h_htLep[MU_NDX].Fill( htLep, evWeight )
            if eleJets :
                h_htLep[EL_NDX].Fill( htLep, evWeight )
                
            if passHTLep == False :
                continue
            else :
                NPassHTLep += 1
                h_CutFlow_SemiLept  .Fill("HTLepCut",1) 

            h_st[ALL_NDX].Fill( st, evWeight )
            if muJets :
                h_st[MU_NDX].Fill( st, evWeight )
            if eleJets :
                h_st[EL_NDX].Fill( st, evWeight )
                
            if passST == False :
                continue
            else :
                NPassST += 1
                h_CutFlow_SemiLept  .Fill("STcut",1) 

            passTriangular = True

            if eleJets and options.useTriangular:
                dphi_emet = abs(metPhi - theLepton.Phi())
                while dphi_emet > 3.14159 : 
                    dphi_emet = abs(2*3.14159 - dphi_emet)
                dphi_jetmet = abs(metPhi - theLepJet.Phi())
                while dphi_jetmet > 3.14159 : 
                    dphi_jetmet = abs(2*3.14159 - dphi_jetmet)

                
                if ( abs(dphi_emet-1.5) > 1.5*metPt/75.0 or abs(dphi_jetmet-1.5) > 1.5*metPt/75.0 ):
                    passTriangular = False
            if passTriangular == False :
                continue
            else :
                NPassTriangularCut += 1
                h_CutFlow_SemiLept  .Fill("TriangleCut",1) 

                
        #^ Plotting for DiLeptonic Channel pre 2D cuts
        elif Leptonic :
            theLepJet = nearestJetP4
            theLepJetBDisc = nearestJetbDiscrim
            if dielectronCandidate :
                theElJet = nearestJetP4
                theElJetBDisc = nearestJetbDiscrim   
            else :
                theMuJet = nearestJetP4
                theMuJetBDisc = nearestJetbDiscrim
            ptRel = theLepJet.Perp( theLepton.Vect() )
            
            #@ First Lepton 2D Cuts
            pass2D1 = ptRel > 20.0 or dRMin > 0.4
            if options.verbose :
                print '>>>>>>>>>>>>>>'
                print '2d cut 1 : dRMin = {0:6.2f}, ptRel = {1:6.2f}'.format( dRMin, ptRel )
                print '>>>>>>>>>>>>>>'
            if pass2D1 :
                NPass2DCut += 1
                if dimuonCandidate :
                    NPassMuon2DCut += 1
                elif dielectronCandidate :
                    NPassEl2DCut += 1
                elif mixedCandidate :
                    NPassMuon2DCut += 1

            theLepJet2 = nearest2JetP4
            theLepJetBDisc2 = nearest2JetbDiscrim
            if dielectronCandidate or mixedCandidate:
                theElJet2 = nearest2JetP4
                theElJetBDisc2 = nearest2JetbDiscrim   
            else :
                theMuJet2 = nearest2JetP4
                theMuJetBDisc2 = nearest2JetbDiscrim
            ptRel2 = theLepJet2.Perp( Lepton2.Vect() )
            
            #@ Second Lepton 2D Cuts
            pass2D2 = ptRel2 > 20.0 or dR2Min > 0.4
            if options.verbose :
                print '>>>>>>>>>>>>>>'
                print '2d cut 2 : dRMin = {0:6.2f}, ptRel = {1:6.2f}'.format( dR2Min, ptRel2 )
                print '>>>>>>>>>>>>>>'
            if pass2D2 :
                NPass2D2Cut += 1
                if dimuonCandidate :
                    NPassMuon2DCut += 1
                elif dielectronCandidate :
                    NPassEl2DCut += 1
                elif mixedCandidate :
                    NPassEl2DCut += 1

            if pass2D1 == False :
                continue
            if pass2D2 == False :
                continue
        #@ AK8 selection
        #channels:
        # Hadronic - get 2 AK8 jets with no leptons
        # Dilepton - no AK8 jets
        # SemiLeptonic - Get the AK8 jet away from the lepton
        
        # For dileptons, we don't read out the AK8 jets. 
        if not Leptonic : 
            #EVENT AK8 HANDLES
            if not options.quickSelect : 
                event.getByLabel ( l_jetsAK8Pt, h_jetsAK8Pt )
            event.getByLabel ( l_jetsAK8Eta, h_jetsAK8Eta )
            event.getByLabel ( l_jetsAK8Phi, h_jetsAK8Phi )
            event.getByLabel ( l_jetsAK8Mass, h_jetsAK8Mass )
            event.getByLabel ( l_jetsAK8Energy, h_jetsAK8Energy )
            event.getByLabel ( l_jetsAK8Y, h_jetsAK8Y )

            event.getByLabel ( l_jetsAK8JEC, h_jetsAK8JEC )
            
            event.getByLabel ( l_jetsAK8JERup     , h_jetsAK8JERup )
            event.getByLabel ( l_jetsAK8JERdown   , h_jetsAK8JERdown )
            event.getByLabel ( l_jetsAK8SmearedE  , h_jetsAK8SmearedE )
            event.getByLabel ( l_jetsAK8SmearedPhi, h_jetsAK8SmearedPhi )
            event.getByLabel ( l_jetsAK8SmearedEta, h_jetsAK8SmearedEta )
            event.getByLabel ( l_jetsAK8SmearedPt , h_jetsAK8SmearedPt )

            event.getByLabel ( l_jetsAK8GenJetE   , h_jetsAK8GenJetE )
            event.getByLabel ( l_jetsAK8GenJetEta , h_jetsAK8GenJetEta )
            event.getByLabel ( l_jetsAK8GenJetPhi , h_jetsAK8GenJetPhi )
            event.getByLabel ( l_jetsAK8GenJetPt  , h_jetsAK8GenJetPt )
            event.getByLabel ( l_jetsAK8GenJetY   , h_jetsAK8GenJetY )





            event.getByLabel ( l_jetsAK8nHadEnergy, h_jetsAK8nHadEnergy)
            event.getByLabel ( l_jetsAK8nEMEnergy, h_jetsAK8nEMEnergy )
            event.getByLabel ( l_jetsAK8cHadEnergy, h_jetsAK8cHadEnergy )
            event.getByLabel ( l_jetsAK8HFHadronEnergy, h_jetsAK8HFHadronEnergy )
            event.getByLabel ( l_jetsAK8cEMEnergy, h_jetsAK8cEMEnergy )
            event.getByLabel ( l_jetsAK8numDaughters, h_jetsAK8numDaughters )
            event.getByLabel ( l_jetsAK8cMultip, h_jetsAK8cMultip )

            event.getByLabel ( l_jetsAK8Keys, h_jetsAK8Keys )

            event.getByLabel ( l_jetsAK8TrimMass, h_jetsAK8TrimMass )
            event.getByLabel ( l_jetsAK8PrunMass, h_jetsAK8PrunMass )
            event.getByLabel ( l_jetsAK8FiltMass, h_jetsAK8FiltMass )
            event.getByLabel ( l_jetsAK8SoftDropMass, h_jetsAK8SoftDropMass )
            event.getByLabel ( l_jetsAK8Tau1, h_jetsAK8Tau1 )
            event.getByLabel ( l_jetsAK8Tau2, h_jetsAK8Tau2 )
            event.getByLabel ( l_jetsAK8Tau3, h_jetsAK8Tau3 )
            event.getByLabel ( l_jetsAK8nSubJets, h_jetsAK8nSubJets )
            event.getByLabel ( l_jetsAK8minmass, h_jetsAK8minmass )
            event.getByLabel ( l_jetsAK8Area, h_jetsAK8Area )
            event.getByLabel ( l_jetsAK8CSV, h_jetsAK8CSV )

            
            event.getByLabel ( l_jetsAK8CmsTopTagSubjetIndex0 , h_jetsAK8CmsTopTagSubjetIndex0  )
            event.getByLabel ( l_jetsAK8CmsTopTagSubjetIndex1 , h_jetsAK8CmsTopTagSubjetIndex1  )
            event.getByLabel ( l_jetsAK8CmsTopTagSubjetIndex2 , h_jetsAK8CmsTopTagSubjetIndex2  )
            event.getByLabel ( l_jetsAK8CmsTopTagSubjetIndex3 , h_jetsAK8CmsTopTagSubjetIndex3  )

            event.getByLabel ( l_subjetsCmsTopTagBDisc        , h_subjetsCmsTopTagBDisc         )
            event.getByLabel ( l_subjetsCmsTopTagPt           , h_subjetsCmsTopTagPt            )
            event.getByLabel ( l_subjetsCmsTopTagEta          , h_subjetsCmsTopTagEta           )
            event.getByLabel ( l_subjetsCmsTopTagPhi          , h_subjetsCmsTopTagPhi           )
            event.getByLabel ( l_subjetsCmsTopTagMass         , h_subjetsCmsTopTagMass          )            
            event.getByLabel ( l_subjetsCmsTopTagArea         , h_subjetsCmsTopTagArea          )            
            event.getByLabel ( l_subjetsCmsTopTagnumDaughters , h_subjetsCmsTopTagnumDaughters  )            
            event.getByLabel ( l_subjetsCmsTopTagY            , h_subjetsCmsTopTagY             )            
            event.getByLabel ( l_subjetsCmsTopTagJEC0         , h_subjetsCmsTopTagJEC0          )            
            event.getByLabel ( l_subjetsCmsTopTagJERup        , h_subjetsCmsTopTagJERup         )            
            event.getByLabel ( l_subjetsCmsTopTagJERdown      , h_subjetsCmsTopTagJERdown       )            
            event.getByLabel ( l_subjetsCmsTopTagSmearedE     , h_subjetsCmsTopTagSmearedE      )            
            event.getByLabel ( l_subjetsCmsTopTagSmearedEta   , h_subjetsCmsTopTagSmearedEta    )            
            event.getByLabel ( l_subjetsCmsTopTagSmearedPhi   , h_subjetsCmsTopTagSmearedPhi    )            
            event.getByLabel ( l_subjetsCmsTopTagSmearedPt    , h_subjetsCmsTopTagSmearedPt     )            
         

            
            event.getByLabel ( l_jetsAK8SoftDropSubjetIndex0  , h_jetsAK8SoftDropSubjetIndex0   )
            event.getByLabel ( l_jetsAK8SoftDropSubjetIndex1  , h_jetsAK8SoftDropSubjetIndex1   )

            event.getByLabel ( l_subjetsSoftDropBDisc        , h_subjetsSoftDropBDisc         )
            event.getByLabel ( l_subjetsSoftDropPt           , h_subjetsSoftDropPt            )
            event.getByLabel ( l_subjetsSoftDropEta          , h_subjetsSoftDropEta           )
            event.getByLabel ( l_subjetsSoftDropPhi          , h_subjetsSoftDropPhi           )
            event.getByLabel ( l_subjetsSoftDropMass         , h_subjetsSoftDropMass          )            
            event.getByLabel ( l_subjetsSoftDropArea         , h_subjetsSoftDropArea          )            
            event.getByLabel ( l_subjetsSoftDropnumDaughters , h_subjetsSoftDropnumDaughters  )            
            event.getByLabel ( l_subjetsSoftDropY            , h_subjetsSoftDropY             )            
            event.getByLabel ( l_subjetsSoftDropJEC0         , h_subjetsSoftDropJEC0          )            
            event.getByLabel ( l_subjetsSoftDropJERup        , h_subjetsSoftDropJERup         )            
            event.getByLabel ( l_subjetsSoftDropJERdown      , h_subjetsSoftDropJERdown       )            
            event.getByLabel ( l_subjetsSoftDropSmearedE     , h_subjetsSoftDropSmearedE      )            
            event.getByLabel ( l_subjetsSoftDropSmearedEta   , h_subjetsSoftDropSmearedEta    )            
            event.getByLabel ( l_subjetsSoftDropSmearedPhi   , h_subjetsSoftDropSmearedPhi    )            
            event.getByLabel ( l_subjetsSoftDropSmearedPt    , h_subjetsSoftDropSmearedPt     )            
                   
            event.getByLabel ( l_subjetsSoftDropGenJetE          , h_subjetsSoftDropGenJetE       )            
            event.getByLabel ( l_subjetsSoftDropGenJetEta        , h_subjetsSoftDropGenJetEta     )            
            event.getByLabel ( l_subjetsSoftDropGenJetPhi        , h_subjetsSoftDropGenJetPhi     )            
            event.getByLabel ( l_subjetsSoftDropGenJetPt         , h_subjetsSoftDropGenJetPt      )            
            event.getByLabel ( l_subjetsSoftDropJetArea          , h_subjetsSoftDropJetArea       )            
            event.getByLabel ( l_subjetsSoftDropPartonFlavour    , h_subjetsSoftDropPartonFlavour )            


            
                
            ak8JetsGood = []
            ak8JetsGoodRaw      = []
            ak8JetsGoodCorrUp   = []
            ak8JetsGoodCorrDn   = []
            ak8JetsGoodTrimMass = []
            ak8JetsGoodPrunMass = []
            ak8JetsGoodFiltMass = []
            ak8JetsGoodSDropMass = []
            ak8JetsGoodTau1 = []
            ak8JetsGoodTau2 = []
            ak8JetsGoodTau3 = []
            ak8JetsGoodNHadE = []
            ak8JetsGoodNSubJets = []
            ak8JetsGoodMinMass = []
            ak8JetsGoodTopSubjetbDisc = []
            ak8JetsGoodTopSubjetMass = []
            ak8JetsGoodNHF = []
            ak8JetsGoodCHF = []
            ak8JetsGoodNEF = []
            ak8JetsGoodCEF = []
            ak8JetsGoodNC  = []
            ak8JetsGoodNCH = []
            ak8JetsGoodCSV = []
            ak8JetsGoodCMSTTsubjetIndex0 = []
            ak8JetsGoodCMSTTsubjetIndex1 = []
            ak8JetsGoodCMSTTsubjetIndex2 = []
            ak8JetsGoodCMSTTsubjetIndex3 = []            
            ak8JetsGoodSDsubjetIndex0 = []            
            ak8JetsGoodSDsubjetIndex1 = []   
            ak8JetsGoodSDsubjet0Mass = []            
            ak8JetsGoodSDsubjet1Mass = [] 
            ak8JetsGoodSDsubjet0Bdisc = []            
            ak8JetsGoodSDsubjet1Bdisc = []    
            ak8JetsGoodSDsubjet0Pt = []            
            ak8JetsGoodSDsubjet1Pt = [] 
            ak8JetsGoodSDsubjet0P4 = []            
            ak8JetsGoodSDsubjet1P4 = []      

            ak8JetsGoodJetMassCorrFactor = []
            ak8JetsGoodJetMassCorrFactorUp = []
            ak8JetsGoodJetMassCorrFactorDn = []
            ak8JetsDPhiLepJet = []
            ak8JetsGoodCorrFactor = []
            ak8JetsGoodCorrUpFactor = []
            ak8JetsGoodCorrDnFactor = []
            ak8JetsGoodPtSmear   = []
            ak8JetsGoodPtSmearUp = []
            ak8JetsGoodPtSmearDn = []
            ak8JetsGoodEtaScale  = []
            ak8JetsGoodPhiScale  = []
            ak8JetsGoodMatchedGenJetPt = []
            ak8JetsGoodMatchedGenJetP4 = []
            ak8JetsGoodMatchedGenJetMass = []
            ak8JetsGoodMatchedGenJetMassSD = []


            ak8JetHt           = 0     
            ak8JetHt_CorrDn    = 0 
            ak8JetHt_CorrUp    = 0 
            ak8JetHt_PtSmearUp = 0 
            ak8JetHt_PtSmearDn = 0    

            if len( h_jetsAK8Pt.product()) > 0 : 
                AK8Pt              = h_jetsAK8Pt                 .product()
                AK8Eta             = h_jetsAK8Eta                .product()
                AK8Phi             = h_jetsAK8Phi                .product()
                AK8Mass            = h_jetsAK8Mass               .product()
                AK8Energy          = h_jetsAK8Energy             .product()
                AK8Y               = h_jetsAK8Y                  .product()
                AK8CSV             = h_jetsAK8CSV                .product()  

                AK8JEC             = h_jetsAK8JEC                .product()
                
                AK8JERup           = h_jetsAK8JERup              .product()
                AK8JERdown         = h_jetsAK8JERdown            .product()
                AK8SmearedE        = h_jetsAK8SmearedE           .product()
                AK8SmearedPhi      = h_jetsAK8SmearedPhi         .product()
                AK8SmearedEta      = h_jetsAK8SmearedEta         .product()
                AK8SmearedPt       = h_jetsAK8SmearedPt          .product()
                 
                AK8GenJetE         = h_jetsAK8GenJetE            .product()
                AK8GenJetEta       = h_jetsAK8GenJetEta          .product()
                AK8GenJetPhi       = h_jetsAK8GenJetPhi          .product()
                AK8GenJetPt        = h_jetsAK8GenJetPt           .product()
                AK8GenJetY         = h_jetsAK8GenJetY            .product()




                AK8nHadE           = h_jetsAK8nHadEnergy         .product()
                AK8nEME            = h_jetsAK8nEMEnergy          .product()
                AK8cHadE           = h_jetsAK8cHadEnergy         .product()
                AK8HFHadE          = h_jetsAK8HFHadronEnergy     .product()
                AK8cEME            = h_jetsAK8cEMEnergy          .product()
                AK8numDaughters    = h_jetsAK8numDaughters       .product()
                AK8cMultip         = h_jetsAK8cMultip            .product()
  
                AK8TrimmedMRaw     = h_jetsAK8TrimMass           .product()
                AK8PrunedMRaw      = h_jetsAK8PrunMass           .product()
                AK8FilteredMRaw    = h_jetsAK8FiltMass           .product()
                AK8SDropMRaw       = h_jetsAK8SoftDropMass       .product()
                AK8Tau1            = h_jetsAK8Tau1               .product()
                AK8Tau2            = h_jetsAK8Tau2               .product()
                AK8Tau3            = h_jetsAK8Tau3               .product()
                AK8nSubJets        = h_jetsAK8nSubJets           .product()
                AK8minmass         = h_jetsAK8minmass            .product()
                AK8Area            = h_jetsAK8Area               .product()

                AK8TrimmedM = []
                AK8PrunedM = []
                AK8FilteredM = []
                AK8SDropM = []
                

                # Get CMSTT subjets and re-correct them
                AK8CMSTTsubjetIndex0         = h_jetsAK8CmsTopTagSubjetIndex0 .product()
                AK8CMSTTsubjetIndex1         = h_jetsAK8CmsTopTagSubjetIndex1 .product()
                AK8CMSTTsubjetIndex2         = h_jetsAK8CmsTopTagSubjetIndex2 .product()
                AK8CMSTTsubjetIndex3         = h_jetsAK8CmsTopTagSubjetIndex3 .product()
                
                CMSTTsubjetBDisc        =[]  
                CMSTTsubjetPtRaw        =[]
                CMSTTsubjetPt           =[]
                CMSTTsubjetEta          =[]  
                CMSTTsubjetPhi          =[]  
                CMSTTsubjetMassRaw      =[]
                CMSTTsubjetMass         =[]
                CMSTTsubjetArea         =[]  
                CMSTTsubjetnumDaughters =[]  
                CMSTTsubjetY            =[]  
                CMSTTsubjetJEC0         =[]  
                CMSTTsubjetJERup        =[]  
                CMSTTsubjetJERdown      =[]  
                CMSTTsubjetSmearedE     =[]  
                CMSTTsubjetSmearedEta   =[]  
                CMSTTsubjetSmearedPhi   =[] 

                if len(h_subjetsCmsTopTagBDisc.product() ) > 0 :
                    CMSTTsubjetBDisc          = h_subjetsCmsTopTagBDisc          .product()
                    CMSTTsubjetPtRaw          = h_subjetsCmsTopTagPt             .product()
                    CMSTTsubjetEta            = h_subjetsCmsTopTagEta            .product()
                    CMSTTsubjetPhi            = h_subjetsCmsTopTagPhi            .product()
                    CMSTTsubjetMassRaw        = h_subjetsCmsTopTagMass           .product()
                    CMSTTsubjetArea           = h_subjetsCmsTopTagArea           .product()
                    CMSTTsubjetnumDaughters   = h_subjetsCmsTopTagnumDaughters   .product()
                    CMSTTsubjetY              = h_subjetsCmsTopTagY              .product()
                    CMSTTsubjetJEC0           = h_subjetsCmsTopTagJEC0           .product()
                    CMSTTsubjetJERup          = h_subjetsCmsTopTagJERup          .product()
                    CMSTTsubjetJERdown        = h_subjetsCmsTopTagJERdown        .product()
                    CMSTTsubjetSmearedE       = h_subjetsCmsTopTagSmearedE       .product()
                    CMSTTsubjetSmearedEta     = h_subjetsCmsTopTagSmearedEta     .product()
                    CMSTTsubjetSmearedPhi     = h_subjetsCmsTopTagSmearedPhi     .product()
                    CMSTTsubjetSmearedPt      = h_subjetsCmsTopTagSmearedPt      .product()


                    for isubjet in xrange( len(CMSTTsubjetPtRaw) ) :
                        spt  = CMSTTsubjetJEC0[isubjet] * CMSTTsubjetPtRaw[isubjet]
                        seta = CMSTTsubjetEta[isubjet]
                        sphi = CMSTTsubjetPhi[isubjet]
                        smass= CMSTTsubjetJEC0[isubjet] * CMSTTsubjetMassRaw[isubjet]
                        subjetP4Raw = ROOT.TLorentzVector()
                        subjetP4Raw.SetPtEtaPhiM( spt, seta, sphi, smass)
                        ak4JetCorrectorForMass.setJetEta( subjetP4Raw.Eta() )
                        ak4JetCorrectorForMass.setJetPt ( subjetP4Raw.Perp() )
                        ak4JetCorrectorForMass.setJetE  ( subjetP4Raw.E() )
                        ak4JetCorrectorForMass.setRho   ( rho )
                        ak4JetCorrectorForMass.setNPV   ( NPV )
                        newJEC = ak4JetCorrectorForMass.getCorrection()
                        subjetP4 = subjetP4Raw * newJEC
                        CMSTTsubjetPt.append( subjetP4.Perp() )
                        CMSTTsubjetMass.append( subjetP4.M() )


                # Get SoftDrop subjets and re-correct them        
                AK8SDsubjetIndex0    = h_jetsAK8SoftDropSubjetIndex0 .product()
                AK8SDsubjetIndex1    = h_jetsAK8SoftDropSubjetIndex1 .product()

                SDsubjetBDisc         = []
                SDsubjetPt            = []
                SDsubjetEta           = []
                SDsubjetPhi           = []
                SDsubjetMass          = []
                SDsubjetArea          = []
                SDsubjetnumDaughters  = []
                SDsubjetY             = []
                SDsubjetJEC0          = []
                SDsubjetJERup         = []
                SDsubjetJERdown       = []
                SDsubjetSmearedE      = []
                SDsubjetSmearedEta    = []
                SDsubjetSmearedPhi    = []
                SDsubjetSmearedPt     = []
                SDsubjetP4corr        = []
                SDsubjetP4raw         = []
                SDsubjetP4corrUp      = []
                SDsubjetP4corrDn      = []
                SDsubjetSmearFactor    = []
                SDsubjetSmearFactorUp  = []
                SDsubjetSmearFactorDn  = []
                SDsubjetScaleEta       = []
                SDsubjetScalePhi       = []
                SDsubjetJetArea        = []
                SDsubjetPartonFlavour  = []
                if len(h_subjetsSoftDropBDisc.product() ) > 0 :
                    SDsubjetBDisc          = h_subjetsSoftDropBDisc          .product()
                    SDsubjetPtOrig         = h_subjetsSoftDropPt             .product()
                    SDsubjetEta            = h_subjetsSoftDropEta            .product()
                    SDsubjetPhi            = h_subjetsSoftDropPhi            .product()
                    SDsubjetMassOrig       = h_subjetsSoftDropMass           .product()
                    SDsubjetArea           = h_subjetsSoftDropArea           .product()
                    SDsubjetnumDaughters   = h_subjetsSoftDropnumDaughters   .product()
                    SDsubjetY              = h_subjetsSoftDropY              .product()
                    SDsubjetJEC0           = h_subjetsSoftDropJEC0           .product()
                    SDsubjetJERup          = h_subjetsSoftDropJERup          .product()
                    SDsubjetJERdown        = h_subjetsSoftDropJERdown        .product()
                    SDsubjetSmearedE       = h_subjetsSoftDropSmearedE       .product()
                    SDsubjetSmearedEta     = h_subjetsSoftDropSmearedEta     .product()
                    SDsubjetSmearedPhi     = h_subjetsSoftDropSmearedPhi     .product()
                    SDsubjetSmearedPt      = h_subjetsSoftDropSmearedPt      .product()
                    SDsubjetGenJetE        = h_subjetsSoftDropGenJetE        .product()
                    SDsubjetGenJetEta      = h_subjetsSoftDropGenJetEta      .product()
                    SDsubjetGenJetPhi      = h_subjetsSoftDropGenJetPhi      .product()
                    SDsubjetGenJetPt       = h_subjetsSoftDropGenJetPt       .product()
                    SDsubjetJetArea        = h_subjetsSoftDropJetArea        .product()
                    SDsubjetPartonFlavour  = h_subjetsSoftDropPartonFlavour  .product()

                              

                    for isubjet in xrange( len(SDsubjetPtOrig) ) :
                        spt  = SDsubjetJEC0[isubjet] * SDsubjetPtOrig[isubjet]
                        seta = SDsubjetEta[isubjet]
                        sphi = SDsubjetPhi[isubjet]
                        smass= SDsubjetJEC0[isubjet] * SDsubjetMassOrig[isubjet]
                        subjetP4Raw = ROOT.TLorentzVector()
                        subjetP4Raw.SetPtEtaPhiM( spt, seta, sphi, smass)

                        ak4JetCorrectorForMass.setJetEta( subjetP4Raw.Eta() )
                        ak4JetCorrectorForMass.setJetPt ( subjetP4Raw.Perp() )
                        ak4JetCorrectorForMass.setJetE  ( subjetP4Raw.E() )
                        ak4JetCorrectorForMass.setRho   ( rho )
                        ak4JetCorrectorForMass.setNPV   ( NPV )
                        newJEC = ak4JetCorrectorForMass.getCorrection()
                        subjetP4 = subjetP4Raw* newJEC
                       
                        SDsubjetPt     .append( subjetP4.Perp() )
                        SDsubjetMass   .append( subjetP4.M()    )
                        SDsubjetP4raw  .append( subjetP4Raw )
                        SDsubjetP4corr .append( subjetP4    )

                        # JEC Uncert
                        if not UncertJetAK4:
                          print "UncertJetAK4 not available"
                        corrDn = newJEC
                        corrUp = newJEC
                        UncertJetAK4.setJetPhi(  subjetP4Raw.Phi()  )
                        UncertJetAK4.setJetEta(  subjetP4Raw.Eta()  )
                        UncertJetAK4.setJetPt(   subjetP4.Perp()    )
                        corrDn -= UncertJetAK4.getUncertainty(0)
                        UncertJetAK4.setJetPhi(  subjetP4Raw.Phi()  )
                        UncertJetAK4.setJetEta(  subjetP4Raw.Eta()  )
                        UncertJetAK4.setJetPt(   subjetP4.Perp()    )
                        corrUp += UncertJetAK4.getUncertainty(1)

                        subjetP4corrDn = subjetP4Raw*corrDn
                        subjetP4corrUp = subjetP4Raw*corrUp
                        SDsubjetP4corrDn .append( subjetP4corrDn    )
                        SDsubjetP4corrUp .append( subjetP4corrUp    )


                        sdptsmear   = 1.0
                        sdptsmearUp = 1.0
                        sdptsmearDn = 1.0
                        sdetascale  = 1.0
                        sdphiscale  = 1.0

                        if options.isMC:
                            # ---------------------------------------
                            # JER
                            # ---------------------------------------

                            smear     = getJER( subjetP4.Eta(),  0) 
                            smearUp   = getJER( subjetP4.Eta(),  1) 
                            smearDn   = getJER( subjetP4.Eta(), -1) 
                            recopt    = subjetP4.Pt()
                            genpt     = SDsubjetGenJetPt[isubjet]
                            deltapt   = (recopt-genpt)*(smear-1.0)
                            deltaptUp = (recopt-genpt)*(smearUp-1.0)
                            deltaptDn = (recopt-genpt)*(smearDn-1.0)
                            sdptsmear   = max(0.0, (recopt+deltapt)/recopt)
                            sdptsmearUp = max(0.0, (recopt+deltaptUp)/recopt)
                            sdptsmearDn = max(0.0, (recopt+deltaptDn)/recopt)


                            SDsubjetSmearFactor    .append( sdptsmear   )
                            SDsubjetSmearFactorUp  .append( sdptsmearUp )
                            SDsubjetSmearFactorDn  .append( sdptsmearDn )

                            # ---------------------------------------
                            # JAR
                            # ---------------------------------------
                            etasmearfactor = 0.1
                            recoeta = subjetP4.Eta()
                            geneta  = SDsubjetGenJetEta[isubjet]
                            deltaeta = (recoeta-geneta)*etasmearfactor 
                            etascale = max(0.0, (recoeta+deltaeta)/recoeta  )

                            phismearfactor = 0.1
                            recophi = subjetP4.Phi()
                            genphi  = SDsubjetGenJetPhi[isubjet]
                            deltaphi = (recophi-genphi)*phismearfactor 
                            phiscale = max(0.0, (recophi+deltaphi)/recophi  )
                            
                            SDsubjetScaleEta .append( etascale )
                            SDsubjetScalePhi .append( phiscale )



                
                AK8Keys = h_jetsAK8Keys.product()

                if options.verbose :
                    print '----------------'
                    print 'N AK8 keys = ' + str( len(AK8Keys)) + ', N AK8Pt = ' + str(len(AK8Pt))


                for i in range(0,len(AK8Pt)):#{ Loop over AK8 Jets
                    NAK8Jets = NAK8Jets + 1
                    AK8JECFromB2GAnaFW = AK8JEC[i]   
                    AK8P4Raw = ROOT.TLorentzVector()
                    AK8P4Raw.SetPtEtaPhiM( AK8Pt[i] , AK8Eta[i], AK8Phi[i], AK8Mass[i])
                    # Remove the old JEC's to get raw energy
                    AK8P4Raw *= AK8JECFromB2GAnaFW 

                    #$ Cut based on charged and neutral energy for AK8 jets
                    nhf = AK8nHadE[i] / AK8P4Raw.E()
                    nef = AK8nEME[i] / AK8P4Raw.E()
                    chf = AK8cHadE[i] / AK8P4Raw.E()
                    cef = AK8cEME[i] / AK8P4Raw.E()
                    nconstituents = AK8numDaughters[i]
                    nch = AK8cMultip[i] 
                    goodJet = \
                      nhf < 0.99 and \
                      nef < 0.99 and \
                      chf > 0.00 and \
                      cef < 0.99 and \
                      nconstituents > 1 and \
                      nch > 0

                     
                    #@ JEC Scaling for AK8 Jets
                    corrDn = 1.0
                    corrUp = 1.0

                    ak8JetCorrector.setJetEta( AK8P4Raw.Eta() )
                    ak8JetCorrector.setJetPt ( AK8P4Raw.Perp() )
                    ak8JetCorrector.setJetE  ( AK8P4Raw.E() )
                    ak8JetCorrector.setJetA  ( AK8Area[i] )
                    ak8JetCorrector.setRho   ( rho )
                    ak8JetCorrector.setNPV   ( NPV )
                    newJEC = ak8JetCorrector.getCorrection()
                    AK8P4Corr = AK8P4Raw*newJEC

                    AK8TrimmedM    .append( AK8TrimmedMRaw[i]  )#  * newJEC )
                    AK8PrunedM     .append( AK8PrunedMRaw[i]   )#  * newJEC )
                    AK8FilteredM   .append( AK8FilteredMRaw[i] )#  * newJEC )
                    AK8SDropM      .append( AK8SDropMRaw[i]    )#  * newJEC )

                    # JEC Uncert
                    if not UncertJetAK8:
                      print "UncertJetAK8 not available"
                    corrDn *= newJEC
                    corrUp *= newJEC
                    UncertJetAK8.setJetPhi(  AK8P4Raw.Phi()  )
                    UncertJetAK8.setJetEta(  AK8P4Raw.Eta()  )
                    UncertJetAK8.setJetPt(   AK8P4Corr.Perp()  )
                    uncertDn = UncertJetAK8.getUncertainty(0)
                    corrDn -= uncertDn
                    UncertJetAK8.setJetPhi(  AK8P4Raw.Phi()  )
                    UncertJetAK8.setJetEta(  AK8P4Raw.Eta()  )
                    UncertJetAK8.setJetPt(   AK8P4Corr.Perp()  )
                    uncertUp = UncertJetAK8.getUncertainty(1)
                    corrUp += uncertUp

                    AK8P4CorrDn = AK8P4Raw*corrDn
                    AK8P4CorrUp = AK8P4Raw*corrUp

                    if options.verbose:
                        print 'newJEC '+str(newJEC)
                        print 'corrDn '+str(corrDn)
                        print 'corrUp '+str(corrUp)

                    # avoid "%MSG-e FactorizedJetCorrectorCalculator: jet eta is not set" errors
                    ak8JetCorrector.setJetEta( AK8P4Raw.Eta() )
                    ak8JetCorrector.setJetPt ( AK8P4Raw.Perp() )
                    ak8JetCorrector.setJetE  ( AK8P4Raw.E() )
                    ak8JetCorrector.setJetA  ( AK8Area[i] )
                    ak8JetCorrector.setRho   ( rho )
                    ak8JetCorrector.setNPV   ( NPV )
                    
                    # https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyCorrections#JetEnCorFWLite
                    # IMPORTANT: the getSubCorrections member function returns the vector of the subcorrections UP to the given level. For example in the example above, factors[0] is the L1 correction and factors[3] is the L1+L2+L3+Residual correction.
                    factors = ak8JetCorrector.getSubCorrections();
                    L1cor = 1.0
                    L12cor = 1.0
                    L123cor = 1.0
                    L123rescor = 1.0
                    if factors.size() > 0:
                        L1cor = factors[0]
                    if factors.size() > 1:
                        L12cor = factors[1]
                    if factors.size() > 2:
                        L123cor = factors[2]
                    if factors.size() > 3 and not options.isMC :
                        L123rescor = factors[3]


                    L2cor = L12cor/L1cor
                    L3cor = L123cor/L12cor
                    L23cor = L2cor*L3cor
                    L23rescor = L123rescor/L123cor

                    L23corDn    = L23cor-uncertDn
                    L23corUp    = L23cor+uncertUp
                    L23rescorDn = L23rescor-uncertDn
                    L23rescorUp = L23rescor+uncertUp

                    if options.verbose > 3:         
                        print 'newJEC       '+str(newJEC)
                        print 'L1cor        '+str(L1cor)
                        print 'L12cor       '+str(L12cor)
                        print 'L123cor      '+str(L123cor)
                        print 'L123rescor   '+str(L123rescor)
                        print 'L2cor         '+str(L2cor)
                        print 'L3cor        '+str(L3cor)
                        print 'L23cor       '+str(L23cor)
                        print 'L23rescor    '+str(L23rescor)
                        print 'L1*L2        '+str(L1cor*L2cor)
                        print 'L1*L2*L3     '+str(L1cor*L2cor*L3cor)
                        print 'L1*L2*L3*res '+str(L1cor*L2cor*L3cor*L23rescor)
                        print 'L2*L3        '+str(L2cor*L3cor)


                    ptsmear   = 1.0
                    ptsmearUp = 1.0
                    ptsmearDn = 1.0
                    etascale  = 1.0
                    phiscale  = 1.0

                    if options.isMC:
                        # ---------------------------------------
                        # JER
                        # ---------------------------------------

                        smear     = getJER( AK8P4Corr.Eta(),  0) 
                        smearUp   = getJER( AK8P4Corr.Eta(),  1) 
                        smearDn   = getJER( AK8P4Corr.Eta(), -1) 
                        recopt    = AK8P4Corr.Pt()
                        genpt     = AK8GenJetPt[i]
                        deltapt   = (recopt-genpt)*(smear-1.0)
                        deltaptUp = (recopt-genpt)*(smearUp-1.0)
                        deltaptDn = (recopt-genpt)*(smearDn-1.0)
                        ptsmear   = max(0.0, (recopt+deltapt)/recopt)
                        ptsmearUp = max(0.0, (recopt+deltaptUp)/recopt)
                        ptsmearDn = max(0.0, (recopt+deltaptDn)/recopt)

                        AK8P4Corr   = AK8P4Corr*ptsmear
                        AK8P4CorrDn = AK8P4CorrDn*ptsmear
                        AK8P4CorrUp = AK8P4CorrUp*ptsmear

                        # ---------------------------------------
                        # JAR
                        # ---------------------------------------
                        etasmearfactor = 0.1
                        recoeta = AK8P4Corr.Eta()
                        geneta  = AK8GenJetEta[i]
                        deltaeta = (recoeta-geneta)*etasmearfactor 
                        etascale = max(0.0, (recoeta+deltaeta)/recoeta  )

                        phismearfactor = 0.1
                        recophi = AK8P4Corr.Phi()
                        genphi  = AK8GenJetPhi[i]
                        deltaphi = (recophi-genphi)*phismearfactor 
                        phiscale = max(0.0, (recophi+deltaphi)/recophi  )


                        if options.verbose > 3 :
                            print "uncorr pt            "  + str( AK8P4Raw.Perp() )
                            print "corr pt              "  + str( AK8P4Corr.Perp() )
                            print "corr up pt           "  + str( AK8P4CorrUp.Perp() )
                            print "corr dn pt           "  + str( AK8P4CorrDn.Perp() )
                            print "corr pt * smearnom   "  + str( AK8P4Corr.Perp() * smear   )
                            print "corr pt * smearup    "  + str( AK8P4Corr.Perp() * smearUp )
                            print "corr pt * smeardn    "  + str( AK8P4Corr.Perp() * smearDn )
                            print "corr pt * smeardn    "  + str( AK8P4Corr.Perp() * smearDn )
                            print "smear                "  + str( smear   )
                            print "smearUp              "  + str( smearUp )
                            print "smearDn              "  + str( smearDn )
                            print "AK8JERup             "  + str( AK8JERup        [i] )
                            print "AK8JERdown           "  + str( AK8JERdown      [i] )
                            print "AK8SmearedE          "  + str( AK8SmearedE     [i] )  
                            print "AK8SmearedPhi        "  + str( AK8SmearedPhi   [i] )  
                            print "AK8SmearedEta        "  + str( AK8SmearedEta   [i] )  
                            print "AK8SmearedPt         "  + str( AK8SmearedPt    [i] )  
                            print "AK8PtRaw             "  + str( AK8P4Raw.Perp() )  
                            print "AK8PtB2GCorr         "  + str( AK8Pt    [i] )  

                    if not goodJet :
                        if options.verbose > 3 : 
                            print '   bad jet pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}'.format (
                                AK8P4Raw.Perp(), AK8P4Raw.Rapidity(), AK8P4Raw.Phi(), AK8P4Raw.M()
                                )
                        continue
                    NPassGoodJetAK8Cut = NPassGoodJetAK8Cut + 1
                    if options.verbose > 3 :
                        print '   raw jet pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}'.format (
                            AK8P4Raw.Perp(), AK8P4Raw.Rapidity(), AK8P4Raw.Phi(), AK8P4Raw.M()
                            )
                        print '   corr jet pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}'.format (
                            AK8P4Corr.Perp(), AK8P4Corr.Rapidity(), AK8P4Corr.Phi(), AK8P4Corr.M()
                            )                        

                    if abs(AK8P4Corr.Rapidity()) > options.maxAK8Rapidity :
                        continue
                    NPassMaxAK8RapidityCut = NPassMaxAK8RapidityCut + 1

                    #$ Ht = sume jet energy
                    ak8JetHt = ak8JetHt + AK8P4Corr.Perp()
                    ak8JetHt_CorrDn    = ak8JetHt_CorrDn  + AK8P4CorrDn.Perp()
                    ak8JetHt_CorrUp    = ak8JetHt_CorrUp  + AK8P4CorrUp.Perp()
                    ak8JetHt_PtSmearUp = ak8JetHt_PtSmearUp  + AK8P4Raw.Perp()*newJEC*ptsmearUp
                    ak8JetHt_PtSmearDn = ak8JetHt_PtSmearDn  + AK8P4Raw.Perp()*newJEC*ptsmearDn

                    if options.verbose >3:
                        print 'ak8JetHt ' +str(ak8JetHt)+'  AK8P4Corr.Perp() '+str( AK8P4Corr.Perp() )+'  AK8P4Corr.Eta() '+str( AK8P4Corr.Eta() )

                    #$ Cuts based on pt and rapidity
                    if AK8P4Corr.Perp() < options.minAK8Pt :
                        continue
                    NPassMinRawAK8PtCut = NPassMinRawAK8PtCut + 1

                    # SemiLeptonic- Only keep AK8 jets "away" from the lepton, so we do not need lepton-jet cleaning here. There's no double counting. 
                    # Leptonic - No fat jets                                                                          
                    # Hadronic - 2 AK8's, no massy leptons to clean up after

                    #$ Cuts for fat jets that are far away from the leptons
                    if SemiLeptonic :
                        if eleJets :
                            dPhi = abs( jetP4.DeltaPhi(theElectron ) )
                        elif muJets :
                            dPhi = abs( jetP4.DeltaPhi(theMuon )  )
                        if options.verbose :
                            print 'dphi = ' + str(dPhi)
                        if dPhi > options.hemisphereDPhi :
                            NPassSemiLeptonicDRjlCut = NPassSemiLeptonicDRjlCut + 1
                            #       print 'N AK8 Subjet B discriminators = ' + str( len(AK8SubjetbDisc) )
                            #        print 'N AK8 Subjets = ' + str( len(AK8nSubJets) )    
                            #         print 'N AK8 min mass pairings = ' + str( len(AK8minmass) )  
                            #          print 'N AK8 trimmed masses = ' + str( len(AK8TrimmedM) )  
                            #           print 'Next event'                    
                            ak8JetsGood.append(AK8P4Corr)
                            ak8JetsGoodCorrUp.append(AK8P4CorrUp)
                            ak8JetsGoodCorrDn.append(AK8P4CorrDn)
                            if options.isMC:
                                ak8JetsGoodJetMassCorrFactor.append( L23cor )
                                ak8JetsGoodJetMassCorrFactorUp.append( L23corUp )
                                ak8JetsGoodJetMassCorrFactorDn.append( L23corDn )
                            else:
                                ak8JetsGoodJetMassCorrFactor.append( L23rescor )
                                ak8JetsGoodJetMassCorrFactorUp.append( L23rescorUp )
                                ak8JetsGoodJetMassCorrFactorDn.append( L23rescorDn )


                            ak8JetsGoodTrimMass.append( AK8TrimmedM[i])
                            ak8JetsGoodPrunMass.append( AK8PrunedM[i])
                            ak8JetsGoodFiltMass.append( AK8FilteredM[i])
                            ak8JetsGoodSDropMass.append( AK8SDropM[i])
                            ak8JetsGoodTau1.append( AK8Tau1[i])
                            ak8JetsGoodTau2.append( AK8Tau2[i])
                            ak8JetsGoodTau3.append( AK8Tau3[i])
                            ak8JetsGoodNSubJets.append( AK8nSubJets[i])
                            ak8JetsGoodMinMass.append( AK8minmass[i] )
                            ak8JetsGoodNHadE.append( AK8nHadE[i]   )
                            #ak8JetsGoodTopSubjetMass.append(  CMSTTsubjetMass[ int(AK8CMSTTsubjetIndex0[i]) ]  )
                            #ak8JetsGoodTopSubjetbDisc.append(  CMSTTsubjetBDisc[ int(AK8CMSTTsubjetIndex0[i]) ]  )
                            ak8JetsGoodCMSTTsubjetIndex0.append( AK8CMSTTsubjetIndex0[i] )
                            ak8JetsGoodCMSTTsubjetIndex1.append( AK8CMSTTsubjetIndex1[i] )
                            ak8JetsGoodCMSTTsubjetIndex2.append( AK8CMSTTsubjetIndex2[i] )
                            ak8JetsGoodCMSTTsubjetIndex3.append( AK8CMSTTsubjetIndex3[i] )
                            ak8JetsGoodSDsubjetIndex0.append( AK8SDsubjetIndex0[i] )
                            ak8JetsGoodSDsubjetIndex1.append( AK8SDsubjetIndex1[i] )
                            if len(SDsubjetMass) >= 2:
                                ak8JetsGoodSDsubjet0Mass.append( SDsubjetMass[int(AK8SDsubjetIndex0[i])] )
                                ak8JetsGoodSDsubjet1Mass.append( SDsubjetMass[int(AK8SDsubjetIndex1[i])] )
                                ak8JetsGoodSDsubjet0Pt.append( SDsubjetPt[int(AK8SDsubjetIndex0[i])] )
                                ak8JetsGoodSDsubjet1Pt.append( SDsubjetPt[int(AK8SDsubjetIndex1[i])] )
                                ak8JetsGoodSDsubjet0Bdisc.append( SDsubjetBDisc[int(AK8SDsubjetIndex0[i])] )
                                ak8JetsGoodSDsubjet1Bdisc.append( SDsubjetBDisc[int(AK8SDsubjetIndex1[i])] )
                            else :
                                ak8JetsGoodSDsubjet0Mass.append( 0 )
                                ak8JetsGoodSDsubjet1Mass.append( 0 )
                                ak8JetsGoodSDsubjet0Pt.append( 0 )
                                ak8JetsGoodSDsubjet1Pt.append( 0 )
                                ak8JetsGoodSDsubjet0Bdisc.append( 0 )
                                ak8JetsGoodSDsubjet1Bdisc.append( 0 )

                            ak8JetsGoodNHF.append( nhf )
                            ak8JetsGoodCHF.append( chf )
                            ak8JetsGoodNEF.append( nef )
                            ak8JetsGoodCEF.append( cef )
                            ak8JetsGoodNC.append( nconstituents )
                            ak8JetsGoodNCH.append( nch )
                            ak8JetsGoodCSV.append( AK8CSV[i]  )
                            ak8JetsDPhiLepJet.append( dPhi )
                            ak8JetsGoodCorrFactor.append( newJEC )
                            ak8JetsGoodCorrUpFactor.append( corrUp )
                            ak8JetsGoodCorrDnFactor.append( corrDn )
                    #$ Cuts for Hadronic channel
                    else : 
                        if options.verbose:
                            print 'N AK8 CMSTT Subjet B discriminators, Hadronic = ' + str( len(CMSTTsubjetBDisc) )
                            print 'N AK8 SD Subjet B discriminators, Hadronic = ' + str( len(SDsubjetBDisc) )
                            print 'AK8SDropM[i]  '+str(AK8SDropM[i] )
                            print 'AK8CMSTTsubjetIndex0[i] '+str(AK8CMSTTsubjetIndex0[i] )
                            print 'AK8CMSTTsubjetIndex1[i] '+str(AK8CMSTTsubjetIndex1[i] )
                            print 'AK8CMSTTsubjetIndex2[i] '+str(AK8CMSTTsubjetIndex2[i] )
                            print 'AK8CMSTTsubjetIndex3[i] '+str(AK8CMSTTsubjetIndex3[i] )

                        ak8JetsGood             .append( AK8P4Corr       )
                        ak8JetsGoodRaw          .append( AK8P4Raw        )
                        ak8JetsGoodCorrUp       .append( AK8P4CorrUp     )
                        ak8JetsGoodCorrDn       .append( AK8P4CorrDn     )
                        ak8JetsGoodTrimMass     .append( AK8TrimmedM[i]  )
                        ak8JetsGoodPrunMass     .append( AK8PrunedM[i]   )
                        ak8JetsGoodFiltMass     .append( AK8FilteredM[i] )
                        ak8JetsGoodSDropMass    .append( AK8SDropM[i]    )
                        ak8JetsGoodTau1         .append( AK8Tau1[i]      )
                        ak8JetsGoodTau2         .append( AK8Tau2[i]      )
                        ak8JetsGoodTau3         .append( AK8Tau3[i]      )
                        ak8JetsGoodNSubJets     .append( AK8nSubJets[i]  )
                        ak8JetsGoodMinMass      .append( AK8minmass[i]   )

                        ak8JetsGoodCMSTTsubjetIndex0.append( AK8CMSTTsubjetIndex0[i] )
                        ak8JetsGoodCMSTTsubjetIndex1.append( AK8CMSTTsubjetIndex1[i] )
                        ak8JetsGoodCMSTTsubjetIndex2.append( AK8CMSTTsubjetIndex2[i] )
                        ak8JetsGoodCMSTTsubjetIndex3.append( AK8CMSTTsubjetIndex3[i] )  
                        ak8JetsGoodSDsubjetIndex0.append( AK8SDsubjetIndex0[i] )
                        ak8JetsGoodSDsubjetIndex1.append( AK8SDsubjetIndex1[i] )
                        #ak8JetsGoodTopSubjetMass.append(  CMSTTsubjetMass[ int(AK8CMSTTsubjetIndex0[i]) ]  )
                        #ak8JetsGoodTopSubjetbDisc.append(  CMSTTsubjetBDisc[ int(AK8CMSTTsubjetIndex0[i]) ]  )
                        ak8JetsGoodNHF.append( nhf )
                        ak8JetsGoodCHF.append( chf )
                        ak8JetsGoodNEF.append( nef )
                        ak8JetsGoodCEF.append( cef )
                        ak8JetsGoodNC .append( nconstituents )
                        ak8JetsGoodNCH.append( nch ) 
                       

                        ak8JetsGoodCorrFactor.append( newJEC )
                        ak8JetsGoodCorrUpFactor.append( corrUp )
                        ak8JetsGoodCorrDnFactor.append( corrDn )
                        if options.isMC:
                            ak8JetsGoodJetMassCorrFactor.append( L23cor )
                            ak8JetsGoodJetMassCorrFactorUp.append( L23corUp )
                            ak8JetsGoodJetMassCorrFactorDn.append( L23corDn )
                        else:
                            ak8JetsGoodJetMassCorrFactor.append( L23rescor )
                            ak8JetsGoodJetMassCorrFactorUp.append( L23rescorUp )
                            ak8JetsGoodJetMassCorrFactorDn.append( L23rescorDn )

                        ak8JetsGoodPtSmear.append( ptsmear )
                        ak8JetsGoodPtSmearUp.append( ptsmearUp )
                        ak8JetsGoodPtSmearDn.append( ptsmearDn )
                        ak8JetsGoodEtaScale.append( etascale )
                        ak8JetsGoodPhiScale.append( phiscale )

                        ak8JetsGoodMatchedGenJetPt.append( AK8GenJetPt[i] )

                        
                        # matchingGenJetMass = 0
                        # matchingGenJetSoftDropMass = 0

                        # # hack since mass not saved for matching gen jet
                        # if options.isMC:
                        #     event.getByLabel ( l_genJetsAK8Pt     , h_genJetsAK8Pt )
                        #     event.getByLabel ( l_genJetsAK8Mass     , h_genJetsAK8Mass )
                        #     event.getByLabel ( l_genJetsAK8SoftDropMass     , h_genJetsAK8SoftDropMass )
                        #     if len( h_genJetsAK8Pt.product()) > 0 : 
                        #          GenJetPt  = h_genJetsAK8Pt                 .product()
                        #          GenJetMass  = h_genJetsAK8Mass                 .product()
                        #          GenJetDSMass  = h_genJetsAK8SoftDropMass                 .product()

                        #          if options.verbose > 8 :
                        #             print 'event '+str( Nevents )+' AK8GenJetPt[i] '+str(AK8GenJetPt[i])
                        #          for k in range(0,len(GenJetPt)):
                        #               if options.verbose > 8 :
                        #                   print '  GenJetPt[k] '+str(GenJetPt[k])
                        #               if abs(AK8GenJetPt[i] - GenJetPt[k]) < 1 :
                        #                   matchingGenJetMass = GenJetMass[k]
                        #                   matchingGenJetSoftDropMass = GenJetDSMass[k]
                        #                   if options.verbose > 8 :
                        #                       print 'found matching GenJet!' 

                        # ak8JetsGoodMatchedGenJetMass.append( matchingGenJetMass )
                        # ak8JetsGoodMatchedGenJetMassSD.append( matchingGenJetSoftDropMass )
                     
                        # GenJetP4 = ROOT.TLorentzVector()
                        # GenJetP4.SetPtEtaPhiM( AK8GenJetPt[i] , AK8GenJetEta[i] , AK8GenJetPhi[i] , matchingGenJetMass)
   
                        # ak8JetsGoodMatchedGenJetP4.append( GenJetP4 )


                #} End AK8 Loop
            #} End if have AK8 product

            if len(ak8JetsGood) < 1 :
                if options.verbose :
                    print 'Not enough AK8 jets, skipping'
                continue

            if SemiLeptonic:
                h_CutFlow_SemiLept  .Fill("1GoodJet",1) 

            if ak8JetsGood[0].Perp() < options.minAK8Pt : #$ Pt cut for passed jets
                continue
            NPassminAK8PtCut = NPassminAK8PtCut + 1
            if SemiLeptonic:
                h_CutFlow_SemiLept  .Fill("PtCut2",1) 
            if Hadronic:
                h_CutFlow_AllHad    .Fill("PtCut2",1) 


            if options.showEvents != None : 
                runNumbers.append( [event.object().id().run(), event.object().luminosityBlock(), event.object().id().event()] ) 


            #@ ALL-HADRONIC plotting and background estimation
            rand1 =  ROOT.TRandom3(0)
            rand2 =  ROOT.TRandom3(0)
            rand_mistag  = rand1.Uniform(0,1.0)
            rand_bkgdest = rand2.Uniform(0,1.0)
            # print 'rand_mistag  '+str(rand_mistag)
            # print 'rand_bkgdest '+str(rand_bkgdest)

            if len(ak8JetsGood) > 1 and Hadronic: #{ check that we have at least 2 AK8 jets for all-hadronic background estimation    
                NeventsBkgdEstimation +=1
                deltaphi_jet0_jet1 = abs( ak8JetsGood[0].DeltaPhi (ak8JetsGood[1]) )
                

                h_CutFlow_AllHad    .Fill("2GoodJets",1) 

                if deltaphi_jet0_jet1 < 2.1:
                    if options.verbose > 2:
                        print 'deltaphi_jet0_jet1 '+str(deltaphi_jet0_jet1)
                        print 'FAILS DELTAPHI CUT'
                    continue
                h_CutFlow_AllHad    .Fill("DeltaPhiCut",1) 

                if ak8JetHt < options.minAK8JetHt:
                    continue    

                h_CutFlow_AllHad    .Fill("HTcut",1) 

                # print 'jet 0 ak8JetsGood Perp          ' +str( ak8JetsGood               [0].Perp()  )    
                # print 'jet 0 ak8JetsGood Eta           ' +str( ak8JetsGood               [0].Eta()   )    
                # print 'jet 0 ak8JetsGoodTrimMass       ' +str( ak8JetsGoodTrimMass       [0]         )    
                # print 'jet 0 ak8JetsGoodPrunMass       ' +str( ak8JetsGoodPrunMass       [0]         )    
                # print 'jet 0 ak8JetsGoodFiltMass       ' +str( ak8JetsGoodFiltMass       [0]         )    
                # print 'jet 0 ak8JetsGoodSDropMass      ' +str( ak8JetsGoodSDropMass      [0]         )    
                # print 'jet 0 ak8JetsGoodTau1           ' +str( ak8JetsGoodTau1           [0]         )    
                # print 'jet 0 ak8JetsGoodTau2           ' +str( ak8JetsGoodTau2           [0]         )    
                # print 'jet 0 ak8JetsGoodTau3           ' +str( ak8JetsGoodTau3           [0]         )    
                # print 'jet 0 ak8JetsGoodNSubJets       ' +str( ak8JetsGoodNSubJets       [0]         )    
                # print 'jet 0 ak8JetsGoodMinMass        ' +str( ak8JetsGoodMinMass        [0]         )    
                # print 'jet 0 ak8JetsGoodTopSubjetIndex0' +str( ak8JetsGoodTopSubjetIndex0[0]         )
                # print 'jet 0 ak8JetsGoodTopSubjetIndex1' +str( ak8JetsGoodTopSubjetIndex1[0]         )
                # print 'jet 0 ak8JetsGoodTopSubjetIndex2' +str( ak8JetsGoodTopSubjetIndex2[0]         )
                # print 'jet 0 ak8JetsGoodTopSubjetIndex3' +str( ak8JetsGoodTopSubjetIndex3[0]         )
                # print 'jet 0 ak8JetsGoodTopSubjetIndex3' +str( ak8JetsGoodSDSubjetIndex3 [0]         )
                # print 'jet 0 ak8JetsGoodTopSubjetIndex3' +str( ak8JetsGoodSDSubjetIndex3 [0]         )
                # print 'len ak8JetsGoodTopSubjetbDisc   '+str(len(ak8JetsGoodTopSubjetbDisc         ))
                # for i in range(0,len(ak8JetsGoodTopSubjetbDisc)):
                #   print 'subjet disc '+str(ak8JetsGoodTopSubjetbDisc[i])
                #   print 'subjet mass '+str(ak8JetsGoodTopMass[i])

                # calculate tau21
                tau21_jet0_ = 1
                tau21_jet1_ = 1
                if ak8JetsGoodTau1[0] !=0:
                  tau21_jet0_ = ak8JetsGoodTau2[0] / ak8JetsGoodTau1[0]
                if ak8JetsGoodTau1[1] !=0:
                  tau21_jet1_ = ak8JetsGoodTau2[1] / ak8JetsGoodTau1[1]

                # calculate tau32 
                tau32_jet0_ = 1
                tau32_jet1_ = 1
                if ak8JetsGoodTau2[0] !=0:
                  tau32_jet0_ = ak8JetsGoodTau3[0] / ak8JetsGoodTau2[0]
                if ak8JetsGoodTau2[1] !=0:
                  tau32_jet1_ = ak8JetsGoodTau3[1] / ak8JetsGoodTau2[1]

                # calculate the dijet mass
                ttMass = (ak8JetsGood[0]+ak8JetsGood[1]).M()


                # jet0 SD subjets
                jet0_sd_s0_bdisc    = -1.
                jet0_sd_s1_bdisc    = -1.
                jet0_sd_s0_pt       = -1.
                jet0_sd_s1_pt       = -1.
                jet0_sd_s0_eta      = -1.
                jet0_sd_s1_eta      = -1.
                jet0_sd_s0_phi      = -1.
                jet0_sd_s1_phi      = -1.
                jet0_sd_s0_m        = -1.
                jet0_sd_s1_m        = -1.
                jet0_sd_s0_jec0     = -1.
                jet0_sd_s1_jec0     = -1.
                jet0_sd_s0_p4corr   = ROOT.TLorentzVector()
                jet0_sd_s1_p4corr   = ROOT.TLorentzVector()
                jet0_sd_s0_p4raw    = ROOT.TLorentzVector()
                jet0_sd_s1_p4raw    = ROOT.TLorentzVector()
                jet0_sd_s0_p4corrUp = ROOT.TLorentzVector()
                jet0_sd_s1_p4corrUp = ROOT.TLorentzVector()
                jet0_sd_s0_p4corrDn = ROOT.TLorentzVector()
                jet0_sd_s1_p4corrDn = ROOT.TLorentzVector()
                jet0_sd_s0_smear    = 1.
                jet0_sd_s1_smear    = 1.
                jet0_sd_s0_smearUp  = 1.
                jet0_sd_s1_smearUp  = 1.
                jet0_sd_s0_smearDn  = 1.
                jet0_sd_s1_smearDn  = 1.
                jet0_sd_s0_scaleEta  = 1.
                jet0_sd_s1_scaleEta  = 1.
                jet0_sd_s0_scalePhi  = 1.
                jet0_sd_s1_scalePhi  = 1.
                jet0_sd_s0_area      = -1.
                jet0_sd_s1_area      = -1.
                jet0_sd_s0_flavour   = -1.
                jet0_sd_s1_flavour   = -1.


                if ak8JetsGoodSDsubjetIndex0[0] > -1 :
                    jet0_sd_s0_bdisc      = SDsubjetBDisc          [ int(ak8JetsGoodSDsubjetIndex0[0]) ]
                    jet0_sd_s0_pt         = SDsubjetPt             [ int(ak8JetsGoodSDsubjetIndex0[0]) ]
                    jet0_sd_s0_eta        = SDsubjetEta            [ int(ak8JetsGoodSDsubjetIndex0[0]) ]
                    jet0_sd_s0_phi        = SDsubjetPhi            [ int(ak8JetsGoodSDsubjetIndex0[0]) ]
                    jet0_sd_s0_m          = SDsubjetMass           [ int(ak8JetsGoodSDsubjetIndex0[0]) ]
                    jet0_sd_s0_jec0       = SDsubjetJEC0           [ int(ak8JetsGoodSDsubjetIndex0[0]) ]
                    jet0_sd_s0_p4corr     = SDsubjetP4corr         [ int(ak8JetsGoodSDsubjetIndex0[0]) ]
                    jet0_sd_s0_p4raw      = SDsubjetP4raw          [ int(ak8JetsGoodSDsubjetIndex0[0]) ]
                    jet0_sd_s0_p4corrUp   = SDsubjetP4corrUp       [ int(ak8JetsGoodSDsubjetIndex0[0]) ]
                    jet0_sd_s0_p4corrDn   = SDsubjetP4corrDn       [ int(ak8JetsGoodSDsubjetIndex0[0]) ]
                    jet0_sd_s0_area       = SDsubjetJetArea        [ int(ak8JetsGoodSDsubjetIndex0[0]) ]       
                    if options.isMC:
                        jet0_sd_s0_smear      = SDsubjetSmearFactor    [ int(ak8JetsGoodSDsubjetIndex0[0]) ]
                        jet0_sd_s0_smearUp    = SDsubjetSmearFactorUp  [ int(ak8JetsGoodSDsubjetIndex0[0]) ]
                        jet0_sd_s0_smearDn    = SDsubjetSmearFactorDn  [ int(ak8JetsGoodSDsubjetIndex0[0]) ]
                        jet0_sd_s0_scaleEta   = SDsubjetScaleEta       [ int(ak8JetsGoodSDsubjetIndex0[0]) ]
                        jet0_sd_s0_scalePhi   = SDsubjetScalePhi       [ int(ak8JetsGoodSDsubjetIndex0[0]) ]
                        jet0_sd_s0_flavour    = SDsubjetPartonFlavour  [ int(ak8JetsGoodSDsubjetIndex0[0]) ]
 

                if ak8JetsGoodSDsubjetIndex1[0] > -1 :
                    jet0_sd_s1_bdisc      = SDsubjetBDisc          [ int(ak8JetsGoodSDsubjetIndex1[0]) ]
                    jet0_sd_s1_pt         = SDsubjetPt             [ int(ak8JetsGoodSDsubjetIndex1[0]) ]
                    jet0_sd_s1_eta        = SDsubjetEta            [ int(ak8JetsGoodSDsubjetIndex1[0]) ]
                    jet0_sd_s1_phi        = SDsubjetPhi            [ int(ak8JetsGoodSDsubjetIndex1[0]) ]
                    jet0_sd_s1_m          = SDsubjetMass           [ int(ak8JetsGoodSDsubjetIndex1[0]) ]
                    jet0_sd_s1_jec0       = SDsubjetJEC0           [ int(ak8JetsGoodSDsubjetIndex1[0]) ]
                    jet0_sd_s1_p4corr     = SDsubjetP4corr         [ int(ak8JetsGoodSDsubjetIndex1[0]) ]
                    jet0_sd_s1_p4raw      = SDsubjetP4raw          [ int(ak8JetsGoodSDsubjetIndex1[0]) ]
                    jet0_sd_s1_p4corrUp   = SDsubjetP4corrUp       [ int(ak8JetsGoodSDsubjetIndex1[0]) ]
                    jet0_sd_s1_p4corrDn   = SDsubjetP4corrDn       [ int(ak8JetsGoodSDsubjetIndex1[0]) ]
                    jet0_sd_s1_area       = SDsubjetJetArea        [ int(ak8JetsGoodSDsubjetIndex1[0]) ]       
                    if options.isMC:
                        jet0_sd_s1_smear      = SDsubjetSmearFactor    [ int(ak8JetsGoodSDsubjetIndex1[0]) ]
                        jet0_sd_s1_smearUp    = SDsubjetSmearFactorUp  [ int(ak8JetsGoodSDsubjetIndex1[0]) ]
                        jet0_sd_s1_smearDn    = SDsubjetSmearFactorDn  [ int(ak8JetsGoodSDsubjetIndex1[0]) ]
                        jet0_sd_s1_scaleEta   = SDsubjetScaleEta       [ int(ak8JetsGoodSDsubjetIndex1[0]) ]
                        jet0_sd_s1_scalePhi   = SDsubjetScalePhi       [ int(ak8JetsGoodSDsubjetIndex1[0]) ]
                        jet0_sd_s1_flavour    = SDsubjetPartonFlavour  [ int(ak8JetsGoodSDsubjetIndex1[0]) ]

                
                if options.verbose > 2:
                    print '   Subjet indices : %6d %6d' % (ak8JetsGoodSDsubjetIndex0[0],
                                                                   ak8JetsGoodSDsubjetIndex1[0])

                    for index in [ak8JetsGoodCMSTTsubjetIndex0[0],
                                  ak8JetsGoodCMSTTsubjetIndex1[0] ] :
                        if index > len(SDsubjetBDisc) :
                            print "Problem! Subjet indices are wrong!"
                            exit(1)


                    print '   -subjet0pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, B = {3:6.2f}'.format ( jet0_sd_s0_pt, jet0_sd_s0_eta, jet0_sd_s0_phi, jet0_sd_s0_bdisc )
                    print '   -subjet1pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, B = {3:6.2f}'.format ( jet0_sd_s1_pt, jet0_sd_s1_eta, jet0_sd_s1_phi, jet0_sd_s1_bdisc )


                # Sum subjet 4-vector
                jet0_sum_sd_subjet_p4_corr           = jet0_sd_s0_p4corr   + jet0_sd_s1_p4corr  
                jet0_sum_sd_subjet_p4_raw            = jet0_sd_s0_p4raw    + jet0_sd_s1_p4raw   
                jet0_sum_sd_subjet_p4_corrUp         = jet0_sd_s0_p4corrUp + jet0_sd_s1_p4corrUp
                jet0_sum_sd_subjet_p4_corrDn         = jet0_sd_s0_p4corrDn + jet0_sd_s1_p4corrDn
                jet0_sum_sd_subjet_p4_corr_smear     = jet0_sd_s0_p4corr*jet0_sd_s0_smear   + jet0_sd_s1_p4corr*jet0_sd_s1_smear   
                jet0_sum_sd_subjet_p4_corr_smearUp   = jet0_sd_s0_p4corr*jet0_sd_s0_smearUp + jet0_sd_s1_p4corr*jet0_sd_s1_smearUp   
                jet0_sum_sd_subjet_p4_corr_smearDn   = jet0_sd_s0_p4corr*jet0_sd_s0_smearDn + jet0_sd_s1_p4corr*jet0_sd_s1_smearDn   

                # find max subjet b-disc
                jet0_bdiscs =[jet0_sd_s0_bdisc, jet0_sd_s1_bdisc] 
                jet0_sd_maxbdisc = max(jet0_bdiscs)
                jet0_sd_maxbdisc_subjet_flavour = 0
                if (jet0_sd_maxbdisc == jet0_sd_s0_bdisc) :
                  jet0_sd_maxbdisc_subjet_flavour = jet0_sd_s0_flavour
                if (jet0_sd_maxbdisc == jet0_sd_s1_bdisc) :
                  jet0_sd_maxbdisc_subjet_flavour = jet0_sd_s1_flavour

                # print 'jet0_sd_s0_bdisc ' +str(jet0_sd_s0_bdisc) + ' jet0_sd_s0_flavour '+ str( jet0_sd_s0_flavour )
                # print 'jet0_sd_s1_bdisc ' +str(jet0_sd_s1_bdisc) + ' jet0_sd_s1_flavour '+ str( jet0_sd_s1_flavour )
                # print 'jet0_sd_maxbdisc ' +str(jet0_sd_maxbdisc) + ' jet0_sd_maxbdisc_subjet_flavour '+ str( jet0_sd_maxbdisc_subjet_flavour )
               
             

                # jet1 SD subjets
                jet1_sd_s0_bdisc    = -1.
                jet1_sd_s1_bdisc    = -1.
                jet1_sd_s0_pt       = -1.
                jet1_sd_s1_pt       = -1.
                jet1_sd_s0_eta      = -1.
                jet1_sd_s1_eta      = -1.
                jet1_sd_s0_phi      = -1.
                jet1_sd_s1_phi      = -1.
                jet1_sd_s0_m        = -1.
                jet1_sd_s1_m        = -1.
                jet1_sd_s0_jec0     = -1.
                jet1_sd_s1_jec0     = -1.
                jet1_sd_s0_p4corr   = ROOT.TLorentzVector()
                jet1_sd_s1_p4corr   = ROOT.TLorentzVector()
                jet1_sd_s0_p4raw    = ROOT.TLorentzVector()
                jet1_sd_s1_p4raw    = ROOT.TLorentzVector()
                jet1_sd_s0_p4corrUp = ROOT.TLorentzVector()
                jet1_sd_s1_p4corrUp = ROOT.TLorentzVector()
                jet1_sd_s0_p4corrDn = ROOT.TLorentzVector()
                jet1_sd_s1_p4corrDn = ROOT.TLorentzVector()
                jet1_sd_s0_smear    = 1.
                jet1_sd_s1_smear    = 1.
                jet1_sd_s0_smearUp  = 1.
                jet1_sd_s1_smearUp  = 1.
                jet1_sd_s0_smearDn  = 1.
                jet1_sd_s1_smearDn  = 1.
                jet1_sd_s0_scaleEta  = 1.
                jet1_sd_s1_scaleEta  = 1.
                jet1_sd_s0_scalePhi  = 1.
                jet1_sd_s1_scalePhi  = 1.
                jet1_sd_s0_area      = -1.
                jet1_sd_s1_area      = -1.
                jet1_sd_s0_flavour   = -1.
                jet1_sd_s1_flavour   = -1.


                if ak8JetsGoodSDsubjetIndex0[0] > -1 :
                    jet1_sd_s0_bdisc      = SDsubjetBDisc          [ int(ak8JetsGoodSDsubjetIndex0[1]) ]
                    jet1_sd_s0_pt         = SDsubjetPt             [ int(ak8JetsGoodSDsubjetIndex0[1]) ]
                    jet1_sd_s0_eta        = SDsubjetEta            [ int(ak8JetsGoodSDsubjetIndex0[1]) ]
                    jet1_sd_s0_phi        = SDsubjetPhi            [ int(ak8JetsGoodSDsubjetIndex0[1]) ]
                    jet1_sd_s0_m          = SDsubjetMass           [ int(ak8JetsGoodSDsubjetIndex0[1]) ]
                    jet1_sd_s0_jec0       = SDsubjetJEC0           [ int(ak8JetsGoodSDsubjetIndex0[1]) ]
                    jet1_sd_s0_p4corr     = SDsubjetP4corr         [ int(ak8JetsGoodSDsubjetIndex0[1]) ]
                    jet1_sd_s0_p4raw      = SDsubjetP4raw          [ int(ak8JetsGoodSDsubjetIndex0[1]) ]
                    jet1_sd_s0_p4corrUp   = SDsubjetP4corrUp       [ int(ak8JetsGoodSDsubjetIndex0[1]) ]
                    jet1_sd_s0_p4corrDn   = SDsubjetP4corrDn       [ int(ak8JetsGoodSDsubjetIndex0[1]) ]
                    jet1_sd_s0_area       = SDsubjetJetArea        [ int(ak8JetsGoodSDsubjetIndex0[1]) ]       
                    if options.isMC:
                        jet1_sd_s0_smear      = SDsubjetSmearFactor    [ int(ak8JetsGoodSDsubjetIndex0[1]) ]
                        jet1_sd_s0_smearUp    = SDsubjetSmearFactorUp  [ int(ak8JetsGoodSDsubjetIndex0[1]) ]
                        jet1_sd_s0_smearDn    = SDsubjetSmearFactorDn  [ int(ak8JetsGoodSDsubjetIndex0[1]) ]
                        jet1_sd_s0_scaleEta   = SDsubjetScaleEta  [ int(ak8JetsGoodSDsubjetIndex0[1]) ]
                        jet1_sd_s0_scalePhi   = SDsubjetScalePhi  [ int(ak8JetsGoodSDsubjetIndex0[1]) ]
                        jet1_sd_s0_flavour    = SDsubjetPartonFlavour  [ int(ak8JetsGoodSDsubjetIndex0[1]) ]
 

                if ak8JetsGoodSDsubjetIndex1[0] > -1 :
                    jet1_sd_s1_bdisc      = SDsubjetBDisc          [ int(ak8JetsGoodSDsubjetIndex1[1]) ]
                    jet1_sd_s1_pt         = SDsubjetPt             [ int(ak8JetsGoodSDsubjetIndex1[1]) ]
                    jet1_sd_s1_eta        = SDsubjetEta            [ int(ak8JetsGoodSDsubjetIndex1[1]) ]
                    jet1_sd_s1_phi        = SDsubjetPhi            [ int(ak8JetsGoodSDsubjetIndex1[1]) ]
                    jet1_sd_s1_m          = SDsubjetMass           [ int(ak8JetsGoodSDsubjetIndex1[1]) ]
                    jet1_sd_s1_jec0       = SDsubjetJEC0           [ int(ak8JetsGoodSDsubjetIndex1[1]) ]
                    jet1_sd_s1_p4corr     = SDsubjetP4corr         [ int(ak8JetsGoodSDsubjetIndex1[1]) ]
                    jet1_sd_s1_p4raw      = SDsubjetP4raw          [ int(ak8JetsGoodSDsubjetIndex1[1]) ]
                    jet1_sd_s1_p4corrUp   = SDsubjetP4corrUp       [ int(ak8JetsGoodSDsubjetIndex1[1]) ]
                    jet1_sd_s1_p4corrDn   = SDsubjetP4corrDn       [ int(ak8JetsGoodSDsubjetIndex1[1]) ]
                    jet1_sd_s1_area       = SDsubjetJetArea        [ int(ak8JetsGoodSDsubjetIndex1[1]) ]       
                    if options.isMC:
                        jet1_sd_s1_smear      = SDsubjetSmearFactor    [ int(ak8JetsGoodSDsubjetIndex1[1]) ]
                        jet1_sd_s1_smearUp    = SDsubjetSmearFactorUp  [ int(ak8JetsGoodSDsubjetIndex1[1]) ]
                        jet1_sd_s1_smearDn    = SDsubjetSmearFactorDn  [ int(ak8JetsGoodSDsubjetIndex1[1]) ]
                        jet1_sd_s1_scaleEta   = SDsubjetScaleEta  [ int(ak8JetsGoodSDsubjetIndex1[1]) ]
                        jet1_sd_s1_scalePhi   = SDsubjetScalePhi  [ int(ak8JetsGoodSDsubjetIndex1[1]) ]
                        jet1_sd_s1_flavour    = SDsubjetPartonFlavour  [ int(ak8JetsGoodSDsubjetIndex1[1]) ]


              
                # Sum subjet 4-vector
                jet1_sum_sd_subjet_p4_corr           = jet1_sd_s0_p4corr   + jet1_sd_s1_p4corr  
                jet1_sum_sd_subjet_p4_raw            = jet1_sd_s0_p4raw    + jet1_sd_s1_p4raw   
                jet1_sum_sd_subjet_p4_corrUp         = jet1_sd_s0_p4corrUp + jet1_sd_s1_p4corrUp
                jet1_sum_sd_subjet_p4_corrDn         = jet1_sd_s0_p4corrDn + jet1_sd_s1_p4corrDn
                jet1_sum_sd_subjet_p4_corr_smear     = jet1_sd_s0_p4corr*jet1_sd_s0_smear   + jet1_sd_s1_p4corr*jet1_sd_s1_smear   
                jet1_sum_sd_subjet_p4_corr_smearUp   = jet1_sd_s0_p4corr*jet1_sd_s0_smearUp + jet1_sd_s1_p4corr*jet1_sd_s1_smearUp   
                jet1_sum_sd_subjet_p4_corr_smearDn   = jet1_sd_s0_p4corr*jet1_sd_s0_smearDn + jet1_sd_s1_p4corr*jet1_sd_s1_smearDn   

                # find max subjet b-disc
                jet1_bdiscs =[jet1_sd_s0_bdisc, jet1_sd_s1_bdisc] 
                jet1_sd_maxbdisc = max(jet1_bdiscs)
                jet1_sd_maxbdisc_subjet_flavour = 0 
                if (jet1_sd_maxbdisc == jet1_sd_s0_bdisc) :
                  jet1_sd_maxbdisc_subjet_flavour = jet1_sd_s0_flavour
                if (jet1_sd_maxbdisc == jet1_sd_s1_bdisc) :
                  jet1_sd_maxbdisc_subjet_flavour = jet1_sd_s1_flavour

                # print 'jet1_sd_s0_bdisc ' +str(jet1_sd_s0_bdisc) + ' jet1_sd_s0_flavour '+ str( jet1_sd_s0_flavour )
                # print 'jet1_sd_s1_bdisc ' +str(jet1_sd_s1_bdisc) + ' jet1_sd_s1_flavour '+ str( jet1_sd_s1_flavour )
                # print 'jet1_sd_maxbdisc ' +str(jet1_sd_maxbdisc) + ' jet1_sd_maxbdisc_subjet_flavour '+ str( jet1_sd_maxbdisc_subjet_flavour )
               

                if options.verbose >3 :
                    print 'jet0_sd_s0_bdisc '+str(jet0_sd_s0_bdisc)
                    print 'jet0_sd_s1_bdisc '+str(jet0_sd_s1_bdisc)
                    print 'jet0_sd_maxbdisc '+str(jet0_sd_maxbdisc)

                    print 'jet1_sd_s0_bdisc '+str(jet1_sd_s0_bdisc)
                    print 'jet1_sd_s1_bdisc '+str(jet1_sd_s1_bdisc)
                    print 'jet1_sd_maxbdisc '+str(jet1_sd_maxbdisc)


                # Jet 0 CMSTT subjets
                jet0_cmstt_s0_bdisc = -1.
                jet0_cmstt_s1_bdisc = -1.
                jet0_cmstt_s2_bdisc = -1.
                jet0_cmstt_s3_bdisc = -1.
                jet0_cmstt_s0_pt    = -1.
                jet0_cmstt_s1_pt    = -1.
                jet0_cmstt_s2_pt    = -1.
                jet0_cmstt_s3_pt    = -1.
                jet0_cmstt_s0_eta   = -1.
                jet0_cmstt_s1_eta   = -1.
                jet0_cmstt_s2_eta   = -1.
                jet0_cmstt_s3_eta   = -1.
                jet0_cmstt_s0_phi   = -1.
                jet0_cmstt_s1_phi   = -1.
                jet0_cmstt_s2_phi   = -1.
                jet0_cmstt_s3_phi   = -1.
                jet0_cmstt_s0_m     = -1.
                jet0_cmstt_s1_m     = -1.
                jet0_cmstt_s2_m     = -1.
                jet0_cmstt_s3_m     = -1.

                if ak8JetsGoodCMSTTsubjetIndex0[0] > -1 :
                    jet0_cmstt_s0_bdisc = CMSTTsubjetBDisc[ int(ak8JetsGoodCMSTTsubjetIndex0[0]) ]
                    jet0_cmstt_s0_pt    = CMSTTsubjetPt   [ int(ak8JetsGoodCMSTTsubjetIndex0[0]) ]
                    jet0_cmstt_s0_eta   = CMSTTsubjetEta  [ int(ak8JetsGoodCMSTTsubjetIndex0[0]) ]
                    jet0_cmstt_s0_phi   = CMSTTsubjetPhi  [ int(ak8JetsGoodCMSTTsubjetIndex0[0]) ]
                    jet0_cmstt_s0_m     = CMSTTsubjetMass [ int(ak8JetsGoodCMSTTsubjetIndex0[0]) ]

                if ak8JetsGoodCMSTTsubjetIndex1[0] > -1 :
                    jet0_cmstt_s1_bdisc = CMSTTsubjetBDisc[ int(ak8JetsGoodCMSTTsubjetIndex1[0]) ]
                    jet0_cmstt_s1_pt    = CMSTTsubjetPt   [ int(ak8JetsGoodCMSTTsubjetIndex1[0]) ]
                    jet0_cmstt_s1_eta   = CMSTTsubjetEta  [ int(ak8JetsGoodCMSTTsubjetIndex1[0]) ]
                    jet0_cmstt_s1_phi   = CMSTTsubjetPhi  [ int(ak8JetsGoodCMSTTsubjetIndex1[0]) ]
                    jet0_cmstt_s1_m     = CMSTTsubjetMass [ int(ak8JetsGoodCMSTTsubjetIndex1[0]) ]

                if ak8JetsGoodCMSTTsubjetIndex2[0] > -1 :
                    jet0_cmstt_s2_bdisc = CMSTTsubjetBDisc[ int(ak8JetsGoodCMSTTsubjetIndex2[0]) ]
                    jet0_cmstt_s2_pt    = CMSTTsubjetPt   [ int(ak8JetsGoodCMSTTsubjetIndex2[0]) ]
                    jet0_cmstt_s2_eta   = CMSTTsubjetEta  [ int(ak8JetsGoodCMSTTsubjetIndex2[0]) ]
                    jet0_cmstt_s2_phi   = CMSTTsubjetPhi  [ int(ak8JetsGoodCMSTTsubjetIndex2[0]) ]
                    jet0_cmstt_s2_m     = CMSTTsubjetMass [ int(ak8JetsGoodCMSTTsubjetIndex2[0]) ]

                if ak8JetsGoodCMSTTsubjetIndex3[0] > -1 :
                    jet0_cmstt_s3_bdisc = CMSTTsubjetBDisc[ int(ak8JetsGoodCMSTTsubjetIndex3[0]) ]
                    jet0_cmstt_s3_pt    = CMSTTsubjetPt   [ int(ak8JetsGoodCMSTTsubjetIndex3[0]) ]
                    jet0_cmstt_s3_eta   = CMSTTsubjetEta  [ int(ak8JetsGoodCMSTTsubjetIndex3[0]) ]
                    jet0_cmstt_s3_phi   = CMSTTsubjetPhi  [ int(ak8JetsGoodCMSTTsubjetIndex3[0]) ]
                    jet0_cmstt_s3_m     = CMSTTsubjetMass [ int(ak8JetsGoodCMSTTsubjetIndex3[0]) ]

                jet0_bdiscs =[jet0_cmstt_s0_bdisc, jet0_cmstt_s1_bdisc, jet0_cmstt_s2_bdisc, jet0_cmstt_s3_bdisc] 
                jet0_cmstt_maxbdisc = max(jet0_bdiscs)
                
                jet0_cmstt_s0 = ROOT.TLorentzVector()
                jet0_cmstt_s1 = ROOT.TLorentzVector()
                jet0_cmstt_s2 = ROOT.TLorentzVector()
                jet0_cmstt_s0.SetPtEtaPhiM( jet0_cmstt_s0_pt , jet0_cmstt_s0_eta, jet0_cmstt_s0_phi, jet0_cmstt_s0_m )
                jet0_cmstt_s1.SetPtEtaPhiM( jet0_cmstt_s1_pt , jet0_cmstt_s1_eta, jet0_cmstt_s1_phi, jet0_cmstt_s1_m )
                jet0_cmstt_s2.SetPtEtaPhiM( jet0_cmstt_s2_pt , jet0_cmstt_s2_eta, jet0_cmstt_s2_phi, jet0_cmstt_s2_m )
                jet0_cmstt_m01 = (jet0_cmstt_s0 + jet0_cmstt_s1 ).M()
                jet0_cmstt_m02 = (jet0_cmstt_s0 + jet0_cmstt_s2 ).M()
                jet0_cmstt_m12 = (jet0_cmstt_s1 + jet0_cmstt_s2 ).M()

                if options.verbose:
                    print 'Top tag candidate : '+str(0)
                    print '   top jet pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}'.format (
                        ak8JetsGood[0].Perp(), ak8JetsGood[0].Rapidity(), ak8JetsGood[0].Phi(), ak8JetsGood[0].M() )                 

                    print '   Subjet indices : %6d %6d %6d %6d' % (ak8JetsGoodCMSTTsubjetIndex0[0],
                                                                   ak8JetsGoodCMSTTsubjetIndex1[0],
                                                                   ak8JetsGoodCMSTTsubjetIndex2[0],
                                                                   ak8JetsGoodCMSTTsubjetIndex3[0])

                    for index in [ak8JetsGoodCMSTTsubjetIndex0[0],
                                  ak8JetsGoodCMSTTsubjetIndex1[0],
                                  ak8JetsGoodCMSTTsubjetIndex2[0],
                                  ak8JetsGoodCMSTTsubjetIndex3[0] ] :
                        if index > len(CMSTTsubjetBDisc) :
                            print "Problem! Subjet indices are wrong!"
                            exit(1)

                    print '   -subjet0pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, B = {3:6.2f}'.format ( jet0_cmstt_s0_pt, jet0_cmstt_s0_eta, jet0_cmstt_s0_phi, jet0_cmstt_s0_bdisc )
                    print '   -subjet1pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, B = {3:6.2f}'.format ( jet0_cmstt_s1_pt, jet0_cmstt_s1_eta, jet0_cmstt_s1_phi, jet0_cmstt_s1_bdisc )
                    print '   -subjet2pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, B = {3:6.2f}'.format ( jet0_cmstt_s2_pt, jet0_cmstt_s2_eta, jet0_cmstt_s2_phi, jet0_cmstt_s2_bdisc )
                    print '   -subjet3pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, B = {3:6.2f}'.format ( jet0_cmstt_s3_pt, jet0_cmstt_s3_eta, jet0_cmstt_s3_phi, jet0_cmstt_s3_bdisc )                 
                    print 'jet0_cmstt_maxbdisc '+str(jet0_cmstt_maxbdisc)

                 # Jet 0 CMSTT subjets
                jet1_cmstt_s0_bdisc = -1.
                jet1_cmstt_s1_bdisc = -1.
                jet1_cmstt_s2_bdisc = -1.
                jet1_cmstt_s3_bdisc = -1.
                jet1_cmstt_s0_pt    = -1.
                jet1_cmstt_s1_pt    = -1.
                jet1_cmstt_s2_pt    = -1.
                jet1_cmstt_s3_pt    = -1.
                jet1_cmstt_s0_eta   = -1.
                jet1_cmstt_s1_eta   = -1.
                jet1_cmstt_s2_eta   = -1.
                jet1_cmstt_s3_eta   = -1.
                jet1_cmstt_s0_phi   = -1.
                jet1_cmstt_s1_phi   = -1.
                jet1_cmstt_s2_phi   = -1.
                jet1_cmstt_s3_phi   = -1.
                jet1_cmstt_s0_m     = -1.
                jet1_cmstt_s1_m     = -1.
                jet1_cmstt_s2_m     = -1.
                jet1_cmstt_s3_m     = -1.

                if ak8JetsGoodCMSTTsubjetIndex0[1] > -1 :
                    jet1_cmstt_s0_bdisc = CMSTTsubjetBDisc[ int(ak8JetsGoodCMSTTsubjetIndex0[1]) ]
                    jet1_cmstt_s0_pt    = CMSTTsubjetPt   [ int(ak8JetsGoodCMSTTsubjetIndex0[1]) ]
                    jet1_cmstt_s0_eta   = CMSTTsubjetEta  [ int(ak8JetsGoodCMSTTsubjetIndex0[1]) ]
                    jet1_cmstt_s0_phi   = CMSTTsubjetPhi  [ int(ak8JetsGoodCMSTTsubjetIndex0[1]) ]
                    jet1_cmstt_s0_m     = CMSTTsubjetMass [ int(ak8JetsGoodCMSTTsubjetIndex0[1]) ]

                if ak8JetsGoodCMSTTsubjetIndex1[1] > -1 :
                    jet1_cmstt_s1_bdisc = CMSTTsubjetBDisc[ int(ak8JetsGoodCMSTTsubjetIndex1[1]) ]
                    jet1_cmstt_s1_pt    = CMSTTsubjetPt   [ int(ak8JetsGoodCMSTTsubjetIndex1[1]) ]
                    jet1_cmstt_s1_eta   = CMSTTsubjetEta  [ int(ak8JetsGoodCMSTTsubjetIndex1[1]) ]
                    jet1_cmstt_s1_phi   = CMSTTsubjetPhi  [ int(ak8JetsGoodCMSTTsubjetIndex1[1]) ]
                    jet1_cmstt_s1_m     = CMSTTsubjetMass [ int(ak8JetsGoodCMSTTsubjetIndex1[1]) ]

                if ak8JetsGoodCMSTTsubjetIndex2[1] > -1 :
                    jet1_cmstt_s2_bdisc = CMSTTsubjetBDisc[ int(ak8JetsGoodCMSTTsubjetIndex2[1]) ]
                    jet1_cmstt_s2_pt    = CMSTTsubjetPt   [ int(ak8JetsGoodCMSTTsubjetIndex2[1]) ]
                    jet1_cmstt_s2_eta   = CMSTTsubjetEta  [ int(ak8JetsGoodCMSTTsubjetIndex2[1]) ]
                    jet1_cmstt_s2_phi   = CMSTTsubjetPhi  [ int(ak8JetsGoodCMSTTsubjetIndex2[1]) ]
                    jet1_cmstt_s2_m     = CMSTTsubjetMass [ int(ak8JetsGoodCMSTTsubjetIndex2[1]) ]

                if ak8JetsGoodCMSTTsubjetIndex3[1] > -1 :
                    jet1_cmstt_s3_bdisc = CMSTTsubjetBDisc[ int(ak8JetsGoodCMSTTsubjetIndex3[1]) ]
                    jet1_cmstt_s3_pt    = CMSTTsubjetPt   [ int(ak8JetsGoodCMSTTsubjetIndex3[1]) ]
                    jet1_cmstt_s3_eta   = CMSTTsubjetEta  [ int(ak8JetsGoodCMSTTsubjetIndex3[1]) ]
                    jet1_cmstt_s3_phi   = CMSTTsubjetPhi  [ int(ak8JetsGoodCMSTTsubjetIndex3[1]) ]
                    jet1_cmstt_s3_m     = CMSTTsubjetMass [ int(ak8JetsGoodCMSTTsubjetIndex3[1]) ]

                jet1_bdiscs =[jet1_cmstt_s0_bdisc, jet1_cmstt_s1_bdisc, jet1_cmstt_s2_bdisc, jet1_cmstt_s3_bdisc] 
                jet1_cmstt_maxbdisc = max(jet1_bdiscs)
                
                jet1_cmstt_s0 = ROOT.TLorentzVector()
                jet1_cmstt_s1 = ROOT.TLorentzVector()
                jet1_cmstt_s2 = ROOT.TLorentzVector()
                jet1_cmstt_s0.SetPtEtaPhiM( jet1_cmstt_s0_pt , jet1_cmstt_s0_eta, jet1_cmstt_s0_phi, jet1_cmstt_s0_m )
                jet1_cmstt_s1.SetPtEtaPhiM( jet1_cmstt_s1_pt , jet1_cmstt_s1_eta, jet1_cmstt_s1_phi, jet1_cmstt_s1_m )
                jet1_cmstt_s2.SetPtEtaPhiM( jet1_cmstt_s2_pt , jet1_cmstt_s2_eta, jet1_cmstt_s2_phi, jet1_cmstt_s2_m )
                jet1_cmstt_m01 = (jet1_cmstt_s0 + jet1_cmstt_s1 ).M()
                jet1_cmstt_m02 = (jet1_cmstt_s0 + jet1_cmstt_s2 ).M()
                jet1_cmstt_m12 = (jet1_cmstt_s1 + jet1_cmstt_s2 ).M()


                if options.verbose:
                    print 'Top tag candidate : '+str(0)
                    print '   top jet pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}'.format (
                        ak8JetsGood[1].Perp(), ak8JetsGood[1].Rapidity(), ak8JetsGood[1].Phi(), ak8JetsGood[1].M() )                 

                    print '   Subjet indices : %6d %6d %6d %6d' % (ak8JetsGoodCMSTTsubjetIndex0[1],
                                                                   ak8JetsGoodCMSTTsubjetIndex1[1],
                                                                   ak8JetsGoodCMSTTsubjetIndex2[1],
                                                                   ak8JetsGoodCMSTTsubjetIndex3[1])

                    for index in [ak8JetsGoodCMSTTsubjetIndex0[1],
                                  ak8JetsGoodCMSTTsubjetIndex1[1],
                                  ak8JetsGoodCMSTTsubjetIndex2[1],
                                  ak8JetsGoodCMSTTsubjetIndex3[1] ] :
                        if index > len(CMSTTsubjetBDisc) :
                            print "Problem! Subjet indices are wrong!"
                            exit(1)

                    print '   -subjet1pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, B = {3:6.2f}'.format ( jet1_cmstt_s0_pt, jet1_cmstt_s0_eta, jet1_cmstt_s0_phi, jet1_cmstt_s0_bdisc )
                    print '   -subjet1pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, B = {3:6.2f}'.format ( jet1_cmstt_s1_pt, jet1_cmstt_s1_eta, jet1_cmstt_s1_phi, jet1_cmstt_s1_bdisc )
                    print '   -subjet2pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, B = {3:6.2f}'.format ( jet1_cmstt_s2_pt, jet1_cmstt_s2_eta, jet1_cmstt_s2_phi, jet1_cmstt_s2_bdisc )
                    print '   -subjet3pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, B = {3:6.2f}'.format ( jet1_cmstt_s3_pt, jet1_cmstt_s3_eta, jet1_cmstt_s3_phi, jet1_cmstt_s3_bdisc )                 
                    print 'jet1_cmstt_maxbdisc '+str(jet1_cmstt_maxbdisc)


                #@ ALL-HADRONIC BACKGROUND ESTIMATION 
                
                # make the modMass histograms
                h_mAK8_ModMass      .Fill( ak8JetsGood[0].M()       , evWeight )        
                h_mSDropAK8_ModMass .Fill( ak8JetsGoodSDropMass[0]  , evWeight )
                h_mAK8_ModMass      .Fill( ak8JetsGood[1].M()       , evWeight )        
                h_mSDropAK8_ModMass .Fill( ak8JetsGoodSDropMass[1]  , evWeight )
                
                h_mAK8_ModMass_jet0      .Fill( ak8JetsGood[0].M()       , evWeight )        
                h_mSDropAK8_ModMass_jet0 .Fill( ak8JetsGoodSDropMass[0]  , evWeight )
                h_mAK8_ModMass_jet1      .Fill( ak8JetsGood[1].M()       , evWeight )        
                h_mSDropAK8_ModMass_jet1 .Fill( ak8JetsGoodSDropMass[1]  , evWeight )

                #setup the modMass procedure
                ttMass_modMass_jet0 = ttMass
                ttMass_modMass_jet1 = ttMass
                ttMass_modMass_flat_jet0 = ttMass
                ttMass_modMass_flat_jet1 = ttMass
                #-----
                # randomly sample from QCD mass distribution in [140,250] 
                # ROOT.gRandom.SetSeed(0) # make sure =0 -> TRandom3 - Set the random generator sequence if seed is 0 (default value) a TUUID is generated and used to fill the first 8 integers of the seed 
                ROOT.gRandom = ROOT.TRandom3(0)
                randMass_QCD_Fat_jet0 = h_modMass_Fat_jet0.GetRandom()
                randMass_QCD_Fat_jet1 = h_modMass_Fat_jet1.GetRandom()

                # when doing the tag+X bkgd estimate procedure, change the mass of the X jet 
                jet0P4_modMass = copy.copy ( ak8JetsGood[0] )
                p_vec_jet0 = ROOT.TVector3( jet0P4_modMass.Px(), jet0P4_modMass.Py(), jet0P4_modMass.Pz())
                jet0P4_modMass.SetVectM( p_vec_jet0, randMass_QCD_Fat_jet0)

                jet1P4_modMass = copy.copy ( ak8JetsGood[1] )
                p_vec_jet1 = ROOT.TVector3(jet1P4_modMass.Px(), jet1P4_modMass.Py(), jet1P4_modMass.Pz())
                jet1P4_modMass.SetVectM( p_vec_jet1, randMass_QCD_Fat_jet1)

                # #sample from a uniform distribution in [140,250]
                rand =  ROOT.TRandom3(0)
                rand_mass = rand.Uniform(140,250)

                # print 'randMass_QCD_Fat_jet0 '+str(randMass_QCD_Fat_jet0)
                # print 'randMass_QCD_Fat_jet1 '+str(randMass_QCD_Fat_jet1)
                # print 'rand_mass '+str(rand_mass)

                jet0P4_modMass_flat = copy.copy ( ak8JetsGood[0] )
                p_vec_jet0 = ROOT.TVector3( jet0P4_modMass_flat.Px(), jet0P4_modMass_flat.Py(), jet0P4_modMass_flat.Pz())
                jet0P4_modMass_flat.SetVectM( p_vec_jet0, rand_mass )

                jet1P4_modMass_flat = copy.copy ( ak8JetsGood[1] )
                p_vec_jet1 = ROOT.TVector3( jet1P4_modMass_flat.Px(), jet1P4_modMass_flat.Py(), jet1P4_modMass_flat.Pz())
                jet1P4_modMass_flat.SetVectM( p_vec_jet1, rand_mass )

                # if jet 0 is outside of the top mass window, force it to have mass in the window 
                if ak8JetsGood[0].M()<140 or ak8JetsGood[0].M()>250:
                    ttMass_modMass_jet0 = (ak8JetsGood[1]+ jet0P4_modMass ).M()
                    ttMass_modMass_flat_jet0 = (ak8JetsGood[1]+ jet0P4_modMass_flat ).M()

                # if jet 0 is outside of the top mass window, force it to have mass in the window (sample from QCD mass distribution in [140,250])
                if ak8JetsGood[1].M()<140 or ak8JetsGood[1].M()>250:
                    ttMass_modMass_jet1 = (ak8JetsGood[0]+ jet1P4_modMass ).M()
                    ttMass_modMass_flat_jet1 = (ak8JetsGood[0]+ jet1P4_modMass_flat ).M()

                
                #~ FILL ALL-HADRONIC TREE
                if options.writeTree :
                    Jet0MassCorrFactor             [0] =  ak8JetsGoodJetMassCorrFactor[0]
                    Jet0MassCorrFactorUp           [0] =  ak8JetsGoodJetMassCorrFactorUp[0]
                    Jet0MassCorrFactorDn           [0] =  ak8JetsGoodJetMassCorrFactorDn[0]
                    Jet0CorrFactor                 [0] =  ak8JetsGoodCorrFactor[0]
                    Jet0CorrFactorUp               [0] =  ak8JetsGoodCorrUpFactor[0]
                    Jet0CorrFactorDn               [0] =  ak8JetsGoodCorrDnFactor[0]
                    Jet0PtSmearFactor              [0] =  ak8JetsGoodPtSmear[0]
                    Jet0PtSmearFactorUp            [0] =  ak8JetsGoodPtSmearUp[0]
                    Jet0PtSmearFactorDn            [0] =  ak8JetsGoodPtSmearDn[0]
                    Jet0EtaScaleFactor             [0] =  ak8JetsGoodEtaScale[0]
                    Jet0PhiScaleFactor             [0] =  ak8JetsGoodPhiScale[0]
                    Jet0MatchedGenJetPt            [0] =  ak8JetsGoodMatchedGenJetPt[0]
                    # Jet0MatchedGenJetMass          [0] =  ak8JetsGoodMatchedGenJetMass[0]
                    # Jet0MatchedGenJetMassSD        [0] =  ak8JetsGoodMatchedGenJetMassSD[0]
                    Jet0PtRaw                      [0] =  ak8JetsGoodRaw[0].Perp()
                    Jet0EtaRaw                     [0] =  ak8JetsGoodRaw[0].Eta()
                    Jet0PhiRaw                     [0] =  ak8JetsGoodRaw[0].Phi()
                    Jet0RapRaw                     [0] =  ak8JetsGoodRaw[0].Rapidity()
                    Jet0MassRaw                    [0] =  ak8JetsGoodRaw[0].M()
                    Jet0P                          [0] =  ak8JetsGood[0].P()
                    Jet0Pt                         [0] =  ak8JetsGood[0].Perp()
                    Jet0Eta                        [0] =  ak8JetsGood[0].Eta()
                    Jet0Phi                        [0] =  ak8JetsGood[0].Phi()
                    Jet0Rap                        [0] =  ak8JetsGood[0].Rapidity()
                    Jet0Energy                     [0] =  ak8JetsGood[0].Energy()
                    Jet0RhoRatio                   [0] =  pow( ak8JetsGood[0].M() / (ak8JetsGood[0].Perp()*0.8) , 2)
                    Jet0Mass                       [0] =  ak8JetsGood[0].M()
                    Jet0MassSoftDrop               [0] =  ak8JetsGoodSDropMass[0]
                    Jet0MassSDsumSubjetCorr        [0] =  (jet0_sum_sd_subjet_p4_corr         ).M() 
                    Jet0MassSDsumSubjetRaw         [0] =  (jet0_sum_sd_subjet_p4_raw          ).M() 
                    Jet0MassSDsumSubjetCorrUp      [0] =  (jet0_sum_sd_subjet_p4_corrUp       ).M() 
                    Jet0MassSDsumSubjetCorrDn      [0] =  (jet0_sum_sd_subjet_p4_corrDn       ).M() 
                    Jet0MassSDsumSubjetCorrSmear   [0] =  (jet0_sum_sd_subjet_p4_corr_smear   ).M() 
                    Jet0MassSDsumSubjetCorrSmearUp [0] =  (jet0_sum_sd_subjet_p4_corr_smearUp ).M() 
                    Jet0MassSDsumSubjetCorrSmearDn [0] =  (jet0_sum_sd_subjet_p4_corr_smearDn ).M() 
                    Jet0MassPruned                 [0] =  ak8JetsGoodPrunMass[0]
                    Jet0MassFiltered               [0] =  ak8JetsGoodFiltMass[0]
                    Jet0MassTrimmed                [0] =  ak8JetsGoodTrimMass[0]
                    Jet0Tau1                       [0] =  ak8JetsGoodTau1[0]
                    Jet0Tau2                       [0] =  ak8JetsGoodTau2[0]
                    Jet0Tau3                       [0] =  ak8JetsGoodTau3[0]
                    Jet0Tau32                      [0] =  tau32_jet0_
                    Jet0Tau21                      [0] =  tau21_jet0_
                    Jet0SDbdisc0                   [0] =  jet0_sd_s0_bdisc
                    Jet0SDbdisc1                   [0] =  jet0_sd_s1_bdisc
                    Jet0SDmaxbdisc                 [0] =  jet0_sd_maxbdisc
                    Jet0SDmaxbdiscflav             [0] =  jet0_sd_maxbdisc_subjet_flavour
                    Jet0SDsubjet0pt                [0] =  jet0_sd_s0_p4corr.Perp()
                    Jet0SDsubjet0mass              [0] =  jet0_sd_s0_p4corr.M()
                    Jet0SDsubjet0area              [0] =  jet0_sd_s0_area
                    Jet0SDsubjet0flav              [0] =  jet0_sd_s0_flavour
                    Jet0SDsubjet1pt                [0] =  jet0_sd_s1_p4corr.Perp()
                    Jet0SDsubjet1mass              [0] =  jet0_sd_s1_p4corr.M()
                    Jet0SDsubjet1area              [0] =  jet0_sd_s1_area
                    Jet0SDsubjet1flav              [0] =  jet0_sd_s1_flavour
                    Jet0CMSmaxbdisc                [0] =  jet0_cmstt_maxbdisc
                    Jet0CMSnsubjets                [0] =  ak8JetsGoodNSubJets[0]
                    Jet0CMSminMass                 [0] =  ak8JetsGoodMinMass[0]
                    Jet0CMSm01                     [0] =  jet0_cmstt_m01
                    Jet0CMSm02                     [0] =  jet0_cmstt_m02
                    Jet0CMSm12                     [0] =  jet0_cmstt_m12
                    Jet0NHF                        [0] =  ak8JetsGoodNHF[0]
                    Jet0CHF                        [0] =  ak8JetsGoodCHF[0]
                    Jet0NEF                        [0] =  ak8JetsGoodNEF[0]
                    Jet0CEF                        [0] =  ak8JetsGoodCEF[0]
                    Jet0NC                         [0] =  ak8JetsGoodNC [0]
                    Jet0NCH                        [0] =  ak8JetsGoodNCH[0]

                    # # Debug high bdisc
                    # if jet0_sd_s0_bdisc > 1:
                    #    print 'jet0_sd_s0_bdisc = '+str(jet0_sd_s0_bdisc)
                    #    print 'jet0_sd_s1_bdisc = '+str(jet0_sd_s1_bdisc)
                    #    print 'jet0_sd_s0_pt    = '+str(jet1_sd_s0_pt)
                    #    print 'jet0_sd_s1_pt    = '+str(jet1_sd_s1_pt)
                    #    print 'jet0_sd_s0_ptcor = '+str(jet0_sd_s0_p4corr.Perp())
                    #    print 'jet0_sd_s1_ptcor = '+str(jet0_sd_s1_p4corr.Perp())
                    #    print 'jet0_sd_s0_mass  = '+str(jet0_sd_s0_p4corr.M())
                    #    print 'jet0_sd_s1_mass  = '+str(jet0_sd_s1_p4corr.M())
                    #    print 'jet0_sd_s0_flav  = '+str(jet0_sd_s0_flavour)
                    #    print 'jet0_sd_s1_flav  = '+str(jet0_sd_s1_flavour)
                    #    print 'ak8JetsGood[0].Perp() = '+str(ak8JetsGood[0].Perp())
                    #    print 'ak8JetsGoodSDsubjetIndex0[0]' +str(ak8JetsGoodSDsubjetIndex0[0])
                    #    if ak8JetsGoodSDsubjetIndex0[0] > -1 :
                    #       print ' SDsubjetBDisc     '  + str( SDsubjetBDisc          [ int(ak8JetsGoodSDsubjetIndex0[0]) ])
                    #       print ' SDsubjetPt        '  + str( SDsubjetPt             [ int(ak8JetsGoodSDsubjetIndex0[0]) ])
                    #       print ' SDsubjetEta       '  + str( SDsubjetEta            [ int(ak8JetsGoodSDsubjetIndex0[0]) ])
                    #       print ' SDsubjetPhi       '  + str( SDsubjetPhi            [ int(ak8JetsGoodSDsubjetIndex0[0]) ])
                    #       print ' SDsubjetMass      '  + str( SDsubjetMass           [ int(ak8JetsGoodSDsubjetIndex0[0]) ])
                    #       print ' SDsubjetJEC0      '  + str( SDsubjetJEC0           [ int(ak8JetsGoodSDsubjetIndex0[0]) ])
                    #       print ' SDsubjetP4corr    '  + str( SDsubjetP4corr         [ int(ak8JetsGoodSDsubjetIndex0[0]) ])
                    #       print ' SDsubjetP4raw     '  + str( SDsubjetP4raw          [ int(ak8JetsGoodSDsubjetIndex0[0]) ])
                    #       print ' SDsubjetP4corrUp  '  + str( SDsubjetP4corrUp       [ int(ak8JetsGoodSDsubjetIndex0[0]) ])
                    #       print ' SDsubjetP4corrDn  '  + str( SDsubjetP4corrDn       [ int(ak8JetsGoodSDsubjetIndex0[0]) ])
                    #       print ' SDsubjetJetArea   '  + str( SDsubjetJetArea        [ int(ak8JetsGoodSDsubjetIndex0[0]) ] )      


                    Jet1MassCorrFactor             [0] =  ak8JetsGoodJetMassCorrFactor[1]
                    Jet1MassCorrFactorUp           [0] =  ak8JetsGoodJetMassCorrFactorUp[1]
                    Jet1MassCorrFactorDn           [0] =  ak8JetsGoodJetMassCorrFactorDn[1]
                    Jet1CorrFactor                 [0] =  ak8JetsGoodCorrFactor[1]
                    Jet1CorrFactorUp               [0] =  ak8JetsGoodCorrUpFactor[1]
                    Jet1CorrFactorDn               [0] =  ak8JetsGoodCorrDnFactor[1]
                    Jet1PtSmearFactor              [0] =  ak8JetsGoodPtSmear[1]
                    Jet1PtSmearFactorUp            [0] =  ak8JetsGoodPtSmearUp[1]
                    Jet1PtSmearFactorDn            [0] =  ak8JetsGoodPtSmearDn[1]
                    Jet1EtaScaleFactor             [0] =  ak8JetsGoodEtaScale[1]
                    Jet1PhiScaleFactor             [0] =  ak8JetsGoodPhiScale[1]
                    Jet1MatchedGenJetPt            [0] =  ak8JetsGoodMatchedGenJetPt[1]
                    # Jet1MatchedGenJetMass          [0] =  ak8JetsGoodMatchedGenJetMass[1]
                    # Jet1MatchedGenJetMassSD        [0] =  ak8JetsGoodMatchedGenJetMassSD[1]
                    Jet1PtRaw                      [0] =  ak8JetsGoodRaw[1].Perp()
                    Jet1EtaRaw                     [0] =  ak8JetsGoodRaw[1].Eta()
                    Jet1PhiRaw                     [0] =  ak8JetsGoodRaw[1].Phi()
                    Jet1RapRaw                     [0] =  ak8JetsGoodRaw[1].Rapidity()
                    Jet1MassRaw                    [0] =  ak8JetsGoodRaw[1].M()
                    Jet1P                          [0] =  ak8JetsGood[1].P()
                    Jet1Pt                         [0] =  ak8JetsGood[1].Perp()
                    Jet1Eta                        [0] =  ak8JetsGood[1].Eta()
                    Jet1Phi                        [0] =  ak8JetsGood[1].Phi()
                    Jet1Rap                        [0] =  ak8JetsGood[1].Rapidity()
                    Jet1Energy                     [0] =  ak8JetsGood[1].Energy()
                    Jet1RhoRatio                   [0] =  pow( ak8JetsGood[1].M() / (ak8JetsGood[1].Perp()*0.8) , 2)
                    Jet1Mass                       [0] =  ak8JetsGood[1].M()
                    Jet1MassSoftDrop               [0] =  ak8JetsGoodSDropMass[1]
                    Jet1MassSDsumSubjetCorr        [0] =  (jet1_sum_sd_subjet_p4_corr         ).M() 
                    Jet1MassSDsumSubjetRaw         [0] =  (jet1_sum_sd_subjet_p4_raw          ).M() 
                    Jet1MassSDsumSubjetCorrUp      [0] =  (jet1_sum_sd_subjet_p4_corrUp       ).M() 
                    Jet1MassSDsumSubjetCorrDn      [0] =  (jet1_sum_sd_subjet_p4_corrDn       ).M() 
                    Jet1MassSDsumSubjetCorrSmear   [0] =  (jet1_sum_sd_subjet_p4_corr_smear   ).M() 
                    Jet1MassSDsumSubjetCorrSmearUp [0] =  (jet1_sum_sd_subjet_p4_corr_smearUp ).M() 
                    Jet1MassSDsumSubjetCorrSmearDn [0] =  (jet1_sum_sd_subjet_p4_corr_smearDn ).M() 
                    Jet1MassPruned                 [0] =  ak8JetsGoodPrunMass[1]
                    Jet1MassFiltered               [0] =  ak8JetsGoodFiltMass[1]
                    Jet1MassTrimmed                [0] =  ak8JetsGoodTrimMass[1]
                    Jet1Tau1                       [0] =  ak8JetsGoodTau1[1]
                    Jet1Tau2                       [0] =  ak8JetsGoodTau2[1]
                    Jet1Tau3                       [0] =  ak8JetsGoodTau3[1]
                    Jet1Tau32                      [0] =  tau32_jet1_
                    Jet1Tau21                      [0] =  tau21_jet1_
                    Jet1SDbdisc0                   [0] =  jet1_sd_s0_bdisc
                    Jet1SDbdisc1                   [0] =  jet1_sd_s1_bdisc
                    Jet1SDmaxbdisc                 [0] =  jet1_sd_maxbdisc
                    Jet1SDmaxbdiscflav             [0] =  jet1_sd_maxbdisc_subjet_flavour
                    Jet1SDsubjet0pt                [0] =  jet1_sd_s0_p4corr.Perp()
                    Jet1SDsubjet0mass              [0] =  jet1_sd_s0_p4corr.M()
                    Jet1SDsubjet0area              [0] =  jet1_sd_s0_area
                    Jet1SDsubjet0flav              [0] =  jet1_sd_s0_flavour
                    Jet1SDsubjet1pt                [0] =  jet1_sd_s1_p4corr.Perp()
                    Jet1SDsubjet1mass              [0] =  jet1_sd_s1_p4corr.M()
                    Jet1SDsubjet1area              [0] =  jet1_sd_s1_area
                    Jet1SDsubjet1flav              [0] =  jet1_sd_s1_flavour
                    Jet1CMSmaxbdisc                [0] =  jet1_cmstt_maxbdisc
                    Jet1CMSnsubjets                [0] =  ak8JetsGoodNSubJets[1]
                    Jet1CMSminMass                 [0] =  ak8JetsGoodMinMass[1]
                    Jet1CMSm01                     [0] =  jet1_cmstt_m01
                    Jet1CMSm02                     [0] =  jet1_cmstt_m02
                    Jet1CMSm12                     [0] =  jet1_cmstt_m12
                    Jet1NHF                        [0] =  ak8JetsGoodNHF[0]
                    Jet1CHF                        [0] =  ak8JetsGoodCHF[0]
                    Jet1NEF                        [0] =  ak8JetsGoodNEF[0]
                    Jet1CEF                        [0] =  ak8JetsGoodCEF[0]
                    Jet1NC                         [0] =  ak8JetsGoodNC [0]
                    Jet1NCH                        [0] =  ak8JetsGoodNCH[0]          

                    AllHadMETpx                    [0] = metPx
                    AllHadMETpy                    [0] = metPy
                    AllHadMETpt                    [0] = metPt
                    AllHadMETphi                   [0] = metPhi      
                    AllHadNvtx                     [0] = NPV   
                    AllHadEventWeight              [0] = evWeight   

                    AllHadNPUtrue                  [0] = NPUtrue
                    AllHadPUweight                 [0] = PUweight      
                    AllHadPUweight_MBup            [0] = PUweight_MBup 
                    AllHadPUweight_MBdn            [0] = PUweight_MBdn 

                    DijetMass                      [0] = ttMass
                    DijetModMassJet0               [0] = ttMass_modMass_jet0
                    DijetModMassJet1               [0] = ttMass_modMass_jet1
                    DijetDeltaR                    [0] = ak8JetsGood[0].DeltaR   (ak8JetsGood[1])
                    DijetDeltaPhi                  [0] = ak8JetsGood[0].DeltaPhi (ak8JetsGood[1])
                    DijetDeltaRap                  [0] = abs(ak8JetsGood[0].Rapidity() - ak8JetsGood[1].Rapidity() )

                    # DiGenJetMass                   [0] = (ak8JetsGoodMatchedGenJetP4[0]+ak8JetsGoodMatchedGenJetP4[1]).M()
                    GenTTmass                      [0] = genZprimeMass

                    HT                             [0] = ak8JetHt          
                    HT_CorrDn                      [0] = ak8JetHt_CorrDn   
                    HT_CorrUp                      [0] = ak8JetHt_CorrUp   
                    HT_PtSmearUp                   [0] = ak8JetHt_PtSmearUp
                    HT_PtSmearDn                   [0] = ak8JetHt_PtSmearDn

                    Q2weight_CorrDn                [0] = Q2wgt_down
                    Q2weight_CorrUp                [0] = Q2wgt_up 

                    NNPDF3weight_CorrDn            [0] = NNPDF3wgt_down
                    NNPDF3weight_CorrUp            [0] = NNPDF3wgt_up   

                    AllHadRunNum                   [0] = event.object().id().run()
                    AllHadLumiBlock                [0] = event.object().luminosityBlock()
                    AllHadEventNum                 [0] = event.object().id().event()


                    TreeAllHad.Fill()
                #} end check that we have at least 2 AK8 jets for all-hadronic background estimation            




           #Ashley - fill semileptonic histograms
            if SemiLeptonic:
                typE = None # set type 2 if one of the AK8's is b-tagged else type 1
                tagCand = 0 # Type 1 top procedure
                leadingAK8Pt = 0.0
                if options.verbose :
                    print '    After final selection, lepton has pt = %6.2f, eta = %6.2f, phi = %6.2f'  % (theLepton.Perp(), theLepton.Eta(), theLepton.Phi() )
                    print '    After final selection, jets are : '
                for icand in xrange(0, len(ak8JetsGood)):
                    if options.verbose :
                        print ' %3d : pt,eta,phi,m = %6.2f, %6.2f, %6.2f, %6.2f ' % ( icand, ak8JetsGood[icand].Perp(), ak8JetsGood[icand].Eta(), ak8JetsGood[icand].Phi(), ak8JetsGood[icand].M() )
                    if ak8JetsGood[icand].Perp() > leadingAK8Pt :
                        tagCand = icand
                        leadingAK8Pt = ak8JetsGood[icand].Perp()

                if options.verbose :
                    print 'Leading AK8 jet : %3d, pt = %6.2f, dphi(lep,jet) = %6.2f' % \
                       ( tagCand, ak8JetsGood[tagCand].Perp(), ak8JetsDPhiLepJet[tagCand] )
                
                mAK8Pruned = ak8JetsGoodPrunMass[tagCand] 
                mAK8Filtered = ak8JetsGoodFiltMass[tagCand] 
                mAK8Trimmed = ak8JetsGoodTrimMass[tagCand]
                mAK8SDrop = ak8JetsGoodSDropMass[tagCand]
                # Make sure there are top tags if we want to plot them
                minMass = ak8JetsGoodMinMass[tagCand]
                if ak8JetsGoodSDsubjet0Bdisc[tagCand] > ak8JetsGoodSDsubjet1Bdisc[tagCand] :
                    subjetBdiscW = ak8JetsGoodSDsubjet1Bdisc[tagCand]   
                    subjetBdiscB = ak8JetsGoodSDsubjet0Bdisc[tagCand]  
                    subjetBdiscMax = ak8JetsGoodSDsubjet0Bdisc[tagCand] 
                    subjetWMass  = ak8JetsGoodSDsubjet1Mass[tagCand] 
                    subjetBMass  = ak8JetsGoodSDsubjet0Mass[tagCand]  
                    subjetWPt  = ak8JetsGoodSDsubjet1Pt[tagCand] 
                    subjetBPt  = ak8JetsGoodSDsubjet0Pt[tagCand]
                else :                    
                    subjetBdiscW = ak8JetsGoodSDsubjet0Bdisc[tagCand]   
                    subjetBdiscB = ak8JetsGoodSDsubjet1Bdisc[tagCand]  
                    subjetBdiscMax = ak8JetsGoodSDsubjet1Bdisc[tagCand] 
                    subjetWMass  = ak8JetsGoodSDsubjet0Mass[tagCand] 
                    subjetBMass  = ak8JetsGoodSDsubjet1Mass[tagCand] 
                    subjetWPt  = ak8JetsGoodSDsubjet0Pt[tagCand] 
                    subjetBPt  = ak8JetsGoodSDsubjet1Pt[tagCand]     

                nsubjets = ak8JetsGoodNSubJets[tagCand]
                tau1 = ak8JetsGoodTau1[tagCand]  
                tau2 = ak8JetsGoodTau2[tagCand] 
                tau3 = ak8JetsGoodTau3[tagCand]
                #^ Plot Taus
                if tau1 > 0.0001 :
                    tau21 = tau2 / tau1
                else :
                    tau21 = -1.0
                if tau2 > 0.0001 :
                    tau32 = tau3 / tau2
                else :
                    tau32 = -1.0


                # jetFat SD subjets
                jetFat_sd_s0_bdisc    = -1.
                jetFat_sd_s1_bdisc    = -1.
                jetFat_sd_s0_pt       = -1.
                jetFat_sd_s1_pt       = -1.
                jetFat_sd_s0_eta      = -1.
                jetFat_sd_s1_eta      = -1.
                jetFat_sd_s0_phi      = -1.
                jetFat_sd_s1_phi      = -1.
                jetFat_sd_s0_m        = -1.
                jetFat_sd_s1_m        = -1.
                jetFat_sd_s0_jec0     = -1.
                jetFat_sd_s1_jec0     = -1.
                jetFat_sd_s0_p4corr   = ROOT.TLorentzVector()
                jetFat_sd_s1_p4corr   = ROOT.TLorentzVector()
                jetFat_sd_s0_p4raw    = ROOT.TLorentzVector()
                jetFat_sd_s1_p4raw    = ROOT.TLorentzVector()
                jetFat_sd_s0_p4corrUp = ROOT.TLorentzVector()
                jetFat_sd_s1_p4corrUp = ROOT.TLorentzVector()
                jetFat_sd_s0_p4corrDn = ROOT.TLorentzVector()
                jetFat_sd_s1_p4corrDn = ROOT.TLorentzVector()
                jetFat_sd_s0_smear    = 1.
                jetFat_sd_s1_smear    = 1.
                jetFat_sd_s0_smearUp  = 1.
                jetFat_sd_s1_smearUp  = 1.
                jetFat_sd_s0_smearDn  = 1.
                jetFat_sd_s1_smearDn  = 1.
                jetFat_sd_s0_scaleEta  = 1.
                jetFat_sd_s1_scaleEta  = 1.
                jetFat_sd_s0_scalePhi  = 1.
                jetFat_sd_s1_scalePhi  = 1.
                jetFat_sd_s0_area      = -1.
                jetFat_sd_s1_area      = -1.
                jetFat_sd_s0_flavour   = -1.
                jetFat_sd_s1_flavour   = -1.


                if ak8JetsGoodSDsubjetIndex0[0] > -1 :
                    jetFat_sd_s0_bdisc      = SDsubjetBDisc          [ int(ak8JetsGoodSDsubjetIndex0[tagCand]) ]
                    jetFat_sd_s0_pt         = SDsubjetPt             [ int(ak8JetsGoodSDsubjetIndex0[tagCand]) ]
                    jetFat_sd_s0_eta        = SDsubjetEta            [ int(ak8JetsGoodSDsubjetIndex0[tagCand]) ]
                    jetFat_sd_s0_phi        = SDsubjetPhi            [ int(ak8JetsGoodSDsubjetIndex0[tagCand]) ]
                    jetFat_sd_s0_m          = SDsubjetMass           [ int(ak8JetsGoodSDsubjetIndex0[tagCand]) ]
                    jetFat_sd_s0_jec0       = SDsubjetJEC0           [ int(ak8JetsGoodSDsubjetIndex0[tagCand]) ]
                    jetFat_sd_s0_p4corr     = SDsubjetP4corr         [ int(ak8JetsGoodSDsubjetIndex0[tagCand]) ]
                    jetFat_sd_s0_p4raw      = SDsubjetP4raw          [ int(ak8JetsGoodSDsubjetIndex0[tagCand]) ]
                    jetFat_sd_s0_p4corrUp   = SDsubjetP4corrUp       [ int(ak8JetsGoodSDsubjetIndex0[tagCand]) ]
                    jetFat_sd_s0_p4corrDn   = SDsubjetP4corrDn       [ int(ak8JetsGoodSDsubjetIndex0[tagCand]) ]
                    jetFat_sd_s0_area       = SDsubjetJetArea        [ int(ak8JetsGoodSDsubjetIndex0[tagCand]) ]       
                    if options.isMC:
                        jetFat_sd_s0_smear      = SDsubjetSmearFactor    [ int(ak8JetsGoodSDsubjetIndex0[tagCand]) ]
                        jetFat_sd_s0_smearUp    = SDsubjetSmearFactorUp  [ int(ak8JetsGoodSDsubjetIndex0[tagCand]) ]
                        jetFat_sd_s0_smearDn    = SDsubjetSmearFactorDn  [ int(ak8JetsGoodSDsubjetIndex0[tagCand]) ]
                        jetFat_sd_s0_scaleEta   = SDsubjetScaleEta  [ int(ak8JetsGoodSDsubjetIndex0[tagCand]) ]
                        jetFat_sd_s0_scalePhi   = SDsubjetScalePhi  [ int(ak8JetsGoodSDsubjetIndex0[tagCand]) ]
                        jetFat_sd_s0_flavour    = SDsubjetPartonFlavour  [ int(ak8JetsGoodSDsubjetIndex0[tagCand]) ]
 

                if ak8JetsGoodSDsubjetIndex1[0] > -1 :
                    jetFat_sd_s1_bdisc      = SDsubjetBDisc          [ int(ak8JetsGoodSDsubjetIndex1[tagCand]) ]
                    jetFat_sd_s1_pt         = SDsubjetPt             [ int(ak8JetsGoodSDsubjetIndex1[tagCand]) ]
                    jetFat_sd_s1_eta        = SDsubjetEta            [ int(ak8JetsGoodSDsubjetIndex1[tagCand]) ]
                    jetFat_sd_s1_phi        = SDsubjetPhi            [ int(ak8JetsGoodSDsubjetIndex1[tagCand]) ]
                    jetFat_sd_s1_m          = SDsubjetMass           [ int(ak8JetsGoodSDsubjetIndex1[tagCand]) ]
                    jetFat_sd_s1_jec0       = SDsubjetJEC0           [ int(ak8JetsGoodSDsubjetIndex1[tagCand]) ]
                    jetFat_sd_s1_p4corr     = SDsubjetP4corr         [ int(ak8JetsGoodSDsubjetIndex1[tagCand]) ]
                    jetFat_sd_s1_p4raw      = SDsubjetP4raw          [ int(ak8JetsGoodSDsubjetIndex1[tagCand]) ]
                    jetFat_sd_s1_p4corrUp   = SDsubjetP4corrUp       [ int(ak8JetsGoodSDsubjetIndex1[tagCand]) ]
                    jetFat_sd_s1_p4corrDn   = SDsubjetP4corrDn       [ int(ak8JetsGoodSDsubjetIndex1[tagCand]) ]
                    jetFat_sd_s1_area       = SDsubjetJetArea        [ int(ak8JetsGoodSDsubjetIndex1[tagCand]) ]       
                    if options.isMC:
                        jetFat_sd_s1_smear      = SDsubjetSmearFactor    [ int(ak8JetsGoodSDsubjetIndex1[tagCand]) ]
                        jetFat_sd_s1_smearUp    = SDsubjetSmearFactorUp  [ int(ak8JetsGoodSDsubjetIndex1[tagCand]) ]
                        jetFat_sd_s1_smearDn    = SDsubjetSmearFactorDn  [ int(ak8JetsGoodSDsubjetIndex1[tagCand]) ]
                        jetFat_sd_s1_scaleEta   = SDsubjetScaleEta  [ int(ak8JetsGoodSDsubjetIndex1[tagCand]) ]
                        jetFat_sd_s1_scalePhi   = SDsubjetScalePhi  [ int(ak8JetsGoodSDsubjetIndex1[tagCand]) ]
                        jetFat_sd_s1_flavour    = SDsubjetPartonFlavour  [ int(ak8JetsGoodSDsubjetIndex1[tagCand]) ]


              
                # Sum subjet 4-vector
                jetFat_sum_sd_subjet_p4_corr           = jetFat_sd_s0_p4corr   + jetFat_sd_s1_p4corr  
                jetFat_sum_sd_subjet_p4_raw            = jetFat_sd_s0_p4raw    + jetFat_sd_s1_p4raw   
                jetFat_sum_sd_subjet_p4_corrUp         = jetFat_sd_s0_p4corrUp + jetFat_sd_s1_p4corrUp
                jetFat_sum_sd_subjet_p4_corrDn         = jetFat_sd_s0_p4corrDn + jetFat_sd_s1_p4corrDn
                jetFat_sum_sd_subjet_p4_corr_smear     = jetFat_sd_s0_p4corr*jetFat_sd_s0_smear   + jetFat_sd_s1_p4corr*jetFat_sd_s1_smear   
                jetFat_sum_sd_subjet_p4_corr_smearUp   = jetFat_sd_s0_p4corr*jetFat_sd_s0_smearUp + jetFat_sd_s1_p4corr*jetFat_sd_s1_smearUp   
                jetFat_sum_sd_subjet_p4_corr_smearDn   = jetFat_sd_s0_p4corr*jetFat_sd_s0_smearDn + jetFat_sd_s1_p4corr*jetFat_sd_s1_smearDn   

                # find max subjet b-disc
                jetFat_bdiscs =[jetFat_sd_s0_bdisc, jetFat_sd_s1_bdisc] 
                jetFat_sd_maxbdisc = max(jetFat_bdiscs)
                
                if (jetFat_sd_maxbdisc == jetFat_sd_s0_bdisc) :
                  jetFat_sd_maxbdisc_subjet_flavour = jetFat_sd_s0_flavour
                if (jetFat_sd_maxbdisc == jetFat_sd_s1_bdisc) :
                  jetFat_sd_maxbdisc_subjet_flavour = jetFat_sd_s1_flavour






                # AK8 jet CMSTT subjets
                jetFat_cmstt_s0_bdisc = -1.
                jetFat_cmstt_s1_bdisc = -1.
                jetFat_cmstt_s2_bdisc = -1.
                jetFat_cmstt_s3_bdisc = -1.
                jetFat_cmstt_s0_pt    = -1.
                jetFat_cmstt_s1_pt    = -1.
                jetFat_cmstt_s2_pt    = -1.
                jetFat_cmstt_s3_pt    = -1.
                jetFat_cmstt_s0_eta   = -1.
                jetFat_cmstt_s1_eta   = -1.
                jetFat_cmstt_s2_eta   = -1.
                jetFat_cmstt_s3_eta   = -1.
                jetFat_cmstt_s0_phi   = -1.
                jetFat_cmstt_s1_phi   = -1.
                jetFat_cmstt_s2_phi   = -1.
                jetFat_cmstt_s3_phi   = -1.
                jetFat_cmstt_s0_m     = -1.
                jetFat_cmstt_s1_m     = -1.
                jetFat_cmstt_s2_m     = -1.
                jetFat_cmstt_s3_m     = -1.

                if ak8JetsGoodCMSTTsubjetIndex0[0] > -1 :
                    jetFat_cmstt_s0_bdisc = CMSTTsubjetBDisc[ int(ak8JetsGoodCMSTTsubjetIndex0[tagCand]) ]
                    jetFat_cmstt_s0_pt    = CMSTTsubjetPt   [ int(ak8JetsGoodCMSTTsubjetIndex0[tagCand]) ]
                    jetFat_cmstt_s0_eta   = CMSTTsubjetEta  [ int(ak8JetsGoodCMSTTsubjetIndex0[tagCand]) ]
                    jetFat_cmstt_s0_phi   = CMSTTsubjetPhi  [ int(ak8JetsGoodCMSTTsubjetIndex0[tagCand]) ]
                    jetFat_cmstt_s0_m     = CMSTTsubjetMass [ int(ak8JetsGoodCMSTTsubjetIndex0[tagCand]) ]

                if ak8JetsGoodCMSTTsubjetIndex1[0] > -1 :
                    jetFat_cmstt_s1_bdisc = CMSTTsubjetBDisc[ int(ak8JetsGoodCMSTTsubjetIndex1[tagCand]) ]
                    jetFat_cmstt_s1_pt    = CMSTTsubjetPt   [ int(ak8JetsGoodCMSTTsubjetIndex1[tagCand]) ]
                    jetFat_cmstt_s1_eta   = CMSTTsubjetEta  [ int(ak8JetsGoodCMSTTsubjetIndex1[tagCand]) ]
                    jetFat_cmstt_s1_phi   = CMSTTsubjetPhi  [ int(ak8JetsGoodCMSTTsubjetIndex1[tagCand]) ]
                    jetFat_cmstt_s1_m     = CMSTTsubjetMass [ int(ak8JetsGoodCMSTTsubjetIndex1[tagCand]) ]

                if ak8JetsGoodCMSTTsubjetIndex2[0] > -1 :
                    jetFat_cmstt_s2_bdisc = CMSTTsubjetBDisc[ int(ak8JetsGoodCMSTTsubjetIndex2[tagCand]) ]
                    jetFat_cmstt_s2_pt    = CMSTTsubjetPt   [ int(ak8JetsGoodCMSTTsubjetIndex2[tagCand]) ]
                    jetFat_cmstt_s2_eta   = CMSTTsubjetEta  [ int(ak8JetsGoodCMSTTsubjetIndex2[tagCand]) ]
                    jetFat_cmstt_s2_phi   = CMSTTsubjetPhi  [ int(ak8JetsGoodCMSTTsubjetIndex2[tagCand]) ]
                    jetFat_cmstt_s2_m     = CMSTTsubjetMass [ int(ak8JetsGoodCMSTTsubjetIndex2[tagCand]) ]

                if ak8JetsGoodCMSTTsubjetIndex3[0] > -1 :
                    jetFat_cmstt_s3_bdisc = CMSTTsubjetBDisc[ int(ak8JetsGoodCMSTTsubjetIndex3[tagCand]) ]
                    jetFat_cmstt_s3_pt    = CMSTTsubjetPt   [ int(ak8JetsGoodCMSTTsubjetIndex3[tagCand]) ]
                    jetFat_cmstt_s3_eta   = CMSTTsubjetEta  [ int(ak8JetsGoodCMSTTsubjetIndex3[tagCand]) ]
                    jetFat_cmstt_s3_phi   = CMSTTsubjetPhi  [ int(ak8JetsGoodCMSTTsubjetIndex3[tagCand]) ]
                    jetFat_cmstt_s3_m     = CMSTTsubjetMass [ int(ak8JetsGoodCMSTTsubjetIndex3[tagCand]) ]

                jetFat_bdiscs =[jetFat_cmstt_s0_bdisc, jetFat_cmstt_s1_bdisc, jetFat_cmstt_s2_bdisc, jetFat_cmstt_s3_bdisc] 
                jetFat_cmstt_maxbdisc = max(jetFat_bdiscs)
                
                jetFat_cmstt_s0 = ROOT.TLorentzVector()
                jetFat_cmstt_s1 = ROOT.TLorentzVector()
                jetFat_cmstt_s2 = ROOT.TLorentzVector()
                jetFat_cmstt_s0.SetPtEtaPhiM( jetFat_cmstt_s0_pt , jetFat_cmstt_s0_eta, jetFat_cmstt_s0_phi, jetFat_cmstt_s0_m )
                jetFat_cmstt_s1.SetPtEtaPhiM( jetFat_cmstt_s1_pt , jetFat_cmstt_s1_eta, jetFat_cmstt_s1_phi, jetFat_cmstt_s1_m )
                jetFat_cmstt_s2.SetPtEtaPhiM( jetFat_cmstt_s2_pt , jetFat_cmstt_s2_eta, jetFat_cmstt_s2_phi, jetFat_cmstt_s2_m )
                jetFat_cmstt_m01 = (jetFat_cmstt_s0 + jetFat_cmstt_s1 ).M()
                jetFat_cmstt_m02 = (jetFat_cmstt_s0 + jetFat_cmstt_s2 ).M()
                jetFat_cmstt_m12 = (jetFat_cmstt_s1 + jetFat_cmstt_s2 ).M()

                if options.verbose:
                    print 'Top tag candidate : '+str(0)
                    print '   top jet pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}'.format (
                        ak8JetsGood[0].Perp(), ak8JetsGood[0].Rapidity(), ak8JetsGood[0].Phi(), ak8JetsGood[0].M() )                 

                    print '   Subjet indices : %6d %6d %6d %6d' % (ak8JetsGoodCMSTTsubjetIndex0[tagCand],
                                                                   ak8JetsGoodCMSTTsubjetIndex1[tagCand],
                                                                   ak8JetsGoodCMSTTsubjetIndex2[tagCand],
                                                                   ak8JetsGoodCMSTTsubjetIndex3[tagCand])

                    for index in [ak8JetsGoodCMSTTsubjetIndex0[tagCand],
                                  ak8JetsGoodCMSTTsubjetIndex1[tagCand],
                                  ak8JetsGoodCMSTTsubjetIndex2[tagCand],
                                  ak8JetsGoodCMSTTsubjetIndex3[tagCand] ] :
                        if index > len(CMSTTsubjetBDisc) :
                            print "Problem! Subjet indices are wrong!"
                            exit(1)

                    print '   -subjetFatpt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, B = {3:6.2f}'.format ( jetFat_cmstt_s0_pt, jetFat_cmstt_s0_eta, jetFat_cmstt_s0_phi, jetFat_cmstt_s0_bdisc )
                    print '   -subjet1pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, B = {3:6.2f}'.format ( jetFat_cmstt_s1_pt, jetFat_cmstt_s1_eta, jetFat_cmstt_s1_phi, jetFat_cmstt_s1_bdisc )
                    print '   -subjet2pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, B = {3:6.2f}'.format ( jetFat_cmstt_s2_pt, jetFat_cmstt_s2_eta, jetFat_cmstt_s2_phi, jetFat_cmstt_s2_bdisc )
                    print '   -subjet3pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, B = {3:6.2f}'.format ( jetFat_cmstt_s3_pt, jetFat_cmstt_s3_eta, jetFat_cmstt_s3_phi, jetFat_cmstt_s3_bdisc )                 
                    print 'jetFat_cmstt_maxbdisc '+str(jetFat_cmstt_maxbdisc)


   


                wtagCand = None # type 2 -w boson jet                               
                btagCand = None # type 2 -b quark 

                if len(ak8JetsGoodCSV) >= 2 :
                    wtagCand = 0 # type 2 -w boson jet                               
                    btagCand = 1 # type 2 -b quark 
                    # assume the leading jet is the W
                    AK8Bdisc0 = ak8JetsGoodCSV[wtagCand]
                    AK8Bdisc1 = ak8JetsGoodCSV[btagCand]
                
                    # switch w and b jets if b is leading jet
                    if  AK8Bdisc0 > AK8Bdisc1:
                        wtagCand = 1
                        btagCand = 0
                        AK8Bdisc0 = ak8JetsGoodCSV[wtagCand]
                        AK8Bdisc1 = ak8JetsGoodCSV[btagCand]


                if wtagCand != None and AK8Bdisc1 > options.bDiscMin:
                    typE = 2
                    mAK8Pruned   = ak8JetsGoodPrunMass[wtagCand] 
                    mAK8Filtered = ak8JetsGoodFiltMass[wtagCand] 
                    mAK8Trimmed  = ak8JetsGoodTrimMass[wtagCand]
                    mAK8SDrop    = ak8JetsGoodSDropMass[wtagCand]
                    # Make sure there are top tags if we want to plot them
                    minMass      = ak8JetsGoodMinMass[wtagCand]


                    subjetBdiscW = 0  
                    subjetBdiscB = 0  
                    subjetBdiscMax = 0  

                    subjetWMass  = 0  
                    subjetBMass  = 0  
                    subjetWPt  = 0  
                    subjetBPt = 0 

                    nsubjets = ak8JetsGoodNSubJets[wtagCand]
                    tau1 = ak8JetsGoodTau1[wtagCand]  
                    tau2 = ak8JetsGoodTau2[wtagCand] 
                    tau3 = ak8JetsGoodTau3[wtagCand]
                    #^ Plot Taus
                    if tau1 > 0.0001 :
                        tau21 = tau2 / tau1
                    else :
                        tau21 = -1.0
                    if tau2 > 0.0001 :
                        tau32 = tau3 / tau2
                    else :
                        tau32 = -1.0
                else :
                    typE = 1




                if options.writeTree :
                    leptonType = 0
                    if eleJets :
                        leptonType = 1
                    elif muJets :
                        leptonType = 2

                    type2pairP4 = ROOT.TLorentzVector()  # W jet + B jet should be top mass
                    type2pairMass  = 0 
                    type2pairPt    = 0 
                    if typE == 1 :
                        tagCand = tagCand
                        BjetBDisc = 0
                        BjetPt = 0
                        BjetEta = 0
                        BjetPhi = 0
                        BjetMass = 0
                    else :
                        tagCand = wtagCand
                        BjetBDisc = ak8JetsGoodCSV[btagCand]
                        BjetPt = ak8JetsGood[btagCand].Perp()
                        BjetEta = ak8JetsGood[btagCand].Eta()
                        BjetPhi = ak8JetsGood[btagCand].Phi()
                        BjetMass = ak8JetsGood[btagCand].M()
                        type2pairP4 = ak8JetsGood[btagCand] + ak8JetsGood[wtagCand]
                        type2pairMass  = type2pairP4.M()
                        type2pairPt    = type2pairP4.Perp()


                    candToPlot = tagCand
                    if typE == 2 :
                        candToPlot = wtagCand


                    if len(ak8JetsGoodPtSmear) >= (candToPlot+1) :
                        smearPt = ak8JetsGoodPtSmear[candToPlot]
                        smearPtu = ak8JetsGoodPtSmearUp[candToPlot]
                        smearPtd = ak8JetsGoodPtSmearDn[candToPlot]
                    else :
                        smearPt = 1.
                        smearPtu = 1.
                        smearPtd = 1.

                    if len(ak8JetsGoodEtaScale) >= (candToPlot+1) :
                        etas = ak8JetsGoodEtaScale[candToPlot]
                        phis = ak8JetsGoodPhiScale[candToPlot]
                        matgen = ak8JetsGoodMatchedGenJetPt[candToPlot]
                    else :
                        etas = 1.
                        phis = 1.
                        matgen = 0.

                    if len(ak8JetsGoodRaw) >= (candToPlot+1) :
                        rpt = ak8JetsGoodRaw[candToPlot].Perp()
                        reta = ak8JetsGoodRaw[candToPlot].Eta()
                        rphi = ak8JetsGoodRaw[candToPlot].Phi()
                        ry = ak8JetsGoodRaw[candToPlot].Rapidity()
                        rmass = ak8JetsGoodRaw[candToPlot].M()
                    else :
                        rpt = 0.
                        reta = 0.
                        rphi = 0.
                        ry = 0.
                        rmass = 0.

                    print 'candToPlot '+str(candToPlot)


                    #~ Fill SemiLeptonic tree 
                    BoosttypE           [0] = typE
                    SemiLeptWeight      [0] = evWeight
                    FatJetCorr          [0] = ak8JetsGoodCorrFactor[candToPlot]
                    FatJetCorrUp        [0] = ak8JetsGoodCorrUpFactor[candToPlot]
                    FatJetCorrDn        [0] = ak8JetsGoodCorrDnFactor[candToPlot]
                    FatJetMassCorr      [0] = ak8JetsGoodJetMassCorrFactor[candToPlot]
                    FatJetMassCorrUp    [0] = ak8JetsGoodJetMassCorrFactorUp[candToPlot]
                    FatJetMassCorrDn    [0] = ak8JetsGoodJetMassCorrFactorDn[candToPlot]
                    JetPtSmearFactor    [0] =  smearPt
                    JetPtSmearFactorUp  [0] =  smearPtu
                    JetPtSmearFactorDn  [0] =  smearPtd
                    JetEtaScaleFactor   [0] =  etas
                    JetPhiScaleFactor   [0] =  phis
                    JetMatchedGenJetPt  [0] =  matgen
                    FatJetPtRaw         [0] =  rpt
                    FatJetEtaRaw        [0] =  reta
                    FatJetPhiRaw        [0] =  rphi
                    FatJetRapRaw        [0] =  ry
                    FatJetMassRaw       [0] =  rmass
                    FatJetP             [0] = ak8JetsGood[candToPlot].P()
                    FatJetPt            [0] = ak8JetsGood[candToPlot].Perp()
                    FatJetEta           [0] = ak8JetsGood[candToPlot].Eta()
                    FatJetPhi           [0] = ak8JetsGood[candToPlot].Phi()
                    FatJetRap           [0] = ak8JetsGood[candToPlot].Rapidity()
                    FatJetEnergy        [0] = ak8JetsGood[candToPlot].Energy()
                    FatJetBDisc         [0] = ak8JetsGoodCSV[candToPlot]
                    FatJetRhoRatio      [0] = pow( ak8JetsGood[candToPlot].M() / (ak8JetsGood[candToPlot].Perp()*0.8) , 2)
                    FatJetMass          [0] = ak8JetsGood[candToPlot].M()
                    FatJetMassSoftDrop  [0] = mAK8SDrop
                    FatJetMassPruned    [0] = mAK8Pruned
                    FatJetMassFiltered  [0] = mAK8Filtered
                    FatJetMassTrimmed   [0] = mAK8Trimmed
                    FatJetMassSDsumSubjetCorr        [0] =  (jetFat_sum_sd_subjet_p4_corr         ).M() 
                    FatJetMassSDsumSubjetRaw         [0] =  (jetFat_sum_sd_subjet_p4_raw          ).M() 
                    FatJetMassSDsumSubjetCorrUp      [0] =  (jetFat_sum_sd_subjet_p4_corrUp       ).M() 
                    FatJetMassSDsumSubjetCorrDn      [0] =  (jetFat_sum_sd_subjet_p4_corrDn       ).M() 
                    FatJetMassSDsumSubjetCorrSmear   [0] =  (jetFat_sum_sd_subjet_p4_corr_smear   ).M() 
                    FatJetMassSDsumSubjetCorrSmearUp [0] =  (jetFat_sum_sd_subjet_p4_corr_smearUp ).M() 
                    FatJetMassSDsumSubjetCorrSmearDn [0] =  (jetFat_sum_sd_subjet_p4_corr_smearDn ).M() 
                    FatJetTau1          [0] = tau1
                    FatJetTau2          [0] = tau2
                    FatJetTau3          [0] = tau3
                    FatJetTau32         [0] = tau32
                    FatJetTau21         [0] = tau21
                    FatJetSDnsubjets    [0] = nsubjets                 
                    FatJetSDbdiscW      [0] = subjetBdiscW
                    FatJetSDbdiscB      [0] = subjetBdiscB
                    FatJetSDmaxbdisc    [0] = subjetBdiscMax
                    FatJetSDsubjetWpt   [0] = subjetWPt
                    FatJetSDsubjetWmass [0] = subjetWMass
                    FatJetSDsubjetBpt   [0] = subjetBPt 
                    FatJetSDsubjetBmass [0] = subjetBMass
                    # Adding these also to reuse code from All-had
                    FatJetSDsubjet0pt   [0] = jetFat_sd_s0_p4corr.Perp() 
                    FatJetSDsubjet0mass [0] = jetFat_sd_s0_p4corr.M() 
                    FatJetSDsubjet0area [0] = jetFat_sd_s0_area
                    FatJetSDsubjet0flav [0] = jetFat_sd_s0_flavour
                    FatJetSDsubjet1pt   [0] = jetFat_sd_s1_p4corr.Perp() 
                    FatJetSDsubjet1mass [0] = jetFat_sd_s1_p4corr.M() 
                    FatJetSDsubjet1area [0] = jetFat_sd_s1_area
                    FatJetSDsubjet1flav [0] = jetFat_sd_s1_flavour

                    FatJetCMSmaxbdisc   [0] = jetFat_cmstt_maxbdisc
                    FatJetCMSnsubjets   [0] = nsubjets
                    FatJetCMSminMass    [0] = minMass
                    FatJetCMSm01        [0] = jetFat_cmstt_m01
                    FatJetCMSm02        [0] = jetFat_cmstt_m02
                    FatJetCMSm12        [0] = jetFat_cmstt_m12
                    FatJetNHF           [0] = ak8JetsGoodNHF[0]
                    FatJetCHF           [0] = ak8JetsGoodCHF[0]
                    FatJetNEF           [0] = ak8JetsGoodNEF[0]
                    FatJetCEF           [0] = ak8JetsGoodCEF[0]
                    FatJetNC            [0] = ak8JetsGoodNC [0]
                    FatJetNCH           [0] = ak8JetsGoodNCH[0]
                    BJetbDisc           [0] = BjetBDisc          
                    BJetPt              [0] = BjetPt
                    BJetEta             [0] = BjetEta
                    BJetPhi             [0] = BjetPhi
                    BJetMass            [0] = BjetMass
                    Type2PairMass       [0] = type2pairMass
                    Type2PairPt         [0] = type2pairPt  
                    LeptonType          [0] = leptonType
                    LeptonPt            [0] = theLepton.Perp()  
                    LeptonEta           [0] = theLepton.Eta()
                    LeptonPhi           [0] = theLepton.Phi()
                    LeptonPx            [0] = theLepton.Px() 
                    LeptonPy            [0] = theLepton.Py() 
                    LeptonPz            [0] = theLepton.Pz()
                    LeptonEnergy        [0] = theLepton.E()
                    LeptonPtRel         [0] = theLeptonPtRel
                    LeptonDRMin         [0] = theLeptonDRMin
                    LeptonIso           [0] = theLeptonIso
                    SemiLepMETpx        [0] = metPx
                    SemiLepMETpy        [0] = metPy
                    SemiLepMETpt        [0] = metPt
                    SemiLepMETphi       [0] = metPhi     
                    SemiLepNvtx         [0] = NPV   
                    SemiLepEventWeight  [0] = evWeight 
                    AK4bDisc            [0] = nearestJetbDiscrim
                    NearestAK4JetPt     [0] = nearestJetP4.Perp()
                    NearestAK4JetEta    [0] = nearestJetP4.Eta()
                    NearestAK4JetPhi    [0] = nearestJetP4.Phi()
                    NearestAK4JetMass   [0] = nearestJetP4.M()
                    # SemilLepTTmass      [0] = 
                    DeltaPhiLepFat      [0] = ak8JetsDPhiLepJet[tagCand]

                    SemiLeptRunNum      [0] = event.object().id().run()
                    SemiLeptLumiBlock   [0] = event.object().luminosityBlock()
                    SemiLeptEventNum    [0] = event.object().id().event()

                    TreeSemiLept.Fill()
                                
            #@ Tagging
            if len(ak8JetsGood) < 1 :
                if options.verbose :
                    print 'Not enough AK8 jets, skipping'
                continue

            nttags = 0
            tJets = []
            for i in range(0,len(ak8JetsGood)):#{ Loop over Fat jets that passed cuts for t tagging
            
                mAK8SDrop = ak8JetsGoodSDropMass[i]
                minMass = ak8JetsGoodMinMass[i]
                tau1 = ak8JetsGoodTau1[i]  
                tau2 = ak8JetsGoodTau2[i] 
                tau3 = ak8JetsGoodTau3[i]
                #^ Plot Taus
                if tau1 > 0.0001 :
                    tau21 = tau2 / tau1
                else :
                    tau21 = -1.0
                if tau2 > 0.0001 :
                    tau32 = tau3 / tau2
                else :
                    tau32 = -1.0


                if minMass > options.minMassCut:
                    NPasstMinMassCut = NPasstMinMassCut + 1
                else:
                    continue
                if mAK8SDrop > options.mAK8GroomedMinCut:
                    NPasstMAK8GroomedMinCut = NPasstMAK8GroomedMinCut + 1
                else:
                    continue
                if tau32 < options.tau32Cut:
                    NPasstau23Cut = NPasstau23Cut + 1
                else: 
                    continue
                nttags += 1
                tJets.append( ak8JetsGood[i] )

                if options.verbose : 
                    print ' --->Tagged jet!'
                else :
                    if options.verbose : 
                        print ''

                #} End t tagging loop






                
        #@ KINEMATICS for all channels

        #@ Leptonic Kin
        if Leptonic :

            ttbarCandP4 = None


            #$ Check if the nearest jets to the leptons are b-tagged
            if theLepJetBDisc > options.bDiscMin:
                NPassBDiscMinCut = NPassBDiscMinCut + 1
                if dimuonCandidate :
                    NPassMuonBCut += 1
                elif dielectronCandidate :
                    NPassElBCut += 1
                elif mixedCandidate :
                    NPassMuonBCut += 1
            if theLepJetBDisc2 > options.bDiscMin:
                NPassBDisc2MinCut = NPassBDisc2MinCut + 1
                if dimuonCandidate :
                    NPassMuonBCut += 1
                elif dielectronCandidate :
                    NPassElBCut += 1
                elif mixedCandidate :
                    NPassElBCut += 1
            if theLepJetBDisc < options.bDiscMin and theLepJetBDisc2 < options.bDiscMin :

                if options.verbose : 
                    print 'closest jet to lepton is not b-tagged'
                    #!!! Eventually we should make 0-btag categories. 
                continue
            else  :

                if options.verbose :
                    print 'Event is fully tagged.'
                if dimuonCandidate :
                    DimuonEvents += 1
                elif dielectronCandidate :
                    DieleEvents += 1
                elif mixedCandidate :
                    muoneleEvents += 1

                bJetCandP4 = theLepJet
                bJetCand2P4 = theLepJet2
                
                nuCandP4 = ROOT.TLorentzVector()#(metPx, metPy ,0.0, metPt)
                nuCandP4.SetPxPyPzE(metPx, metPy, 0.0, metPt)
                #!!! This part is fairly strange to me, just add all 4 vectors together
                ttbarCandP4 = nuCandP4 + Lepton1 + Lepton2 + bJetCandP4 + bJetCand2P4
                #if ttbarCandP4.M() < 1000.0 :
                #    print ' ================'
                #    print ' Low Mass Values '
                #    print ' '
                #    print '   Lepton1 pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}'.format (
                #        Lepton1.Perp(), Lepton1.Rapidity(), Lepton1.Phi(), Lepton1.M())
                #    print '   Lepton2 pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}'.format (
                #        Lepton2.Perp(), Lepton2.Rapidity(), Lepton2.Phi(), Lepton2.M())
                #    print '   bJetCandP4 pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}'.format (
                #        bJetCandP4.Perp(), bJetCandP4.Rapidity(), bJetCandP4.Phi(), bJetCandP4.M())
                #    print '   bJetCand2P4 pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}'.format (
                #        bJetCand2P4.Perp(), bJetCand2P4.Rapidity(), bJetCand2P4.Phi(), bJetCand2P4.M())
                #    print '   nuCandP4 pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}, px = {4:6.2f}, py = {5:6.2f}'.format (
                #        nuCandP4.Perp(), nuCandP4.Rapidity(), nuCandP4.Phi(), nuCandP4.M(), nuCandP4.Px(), nuCandP4.Py())
                #else :
                #    print ' ================'
                #    print ' Normal Mass Values '
                #    print ' '
                #    print '   Lepton1 pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}'.format (
                #        Lepton1.Perp(), Lepton1.Rapidity(), Lepton1.Phi(), Lepton1.M())
                #    print '   Lepton2 pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}'.format (
                #        Lepton2.Perp(), Lepton2.Rapidity(), Lepton2.Phi(), Lepton2.M())
                #    print '   bJetCandP4 pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}'.format (
                #        bJetCandP4.Perp(), bJetCandP4.Rapidity(), bJetCandP4.Phi(), bJetCandP4.M())
                #    print '   bJetCand2P4 pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}'.format (
                #        bJetCand2P4.Perp(), bJetCand2P4.Rapidity(), bJetCand2P4.Phi(), bJetCand2P4.M())
                #    print '   nuCandP4 pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}, px = {4:6.2f}, py = {5:6.2f}'.format (
                #        nuCandP4.Perp(), nuCandP4.Rapidity(), nuCandP4.Phi(), nuCandP4.M(), nuCandP4.Px(), nuCandP4.Py())
                    
        #@ Semileptonic
        elif SemiLeptonic == True and nttags >= 1 :    
            hadTopCandP4 = tJets[0] 
            lepTopCandP4 = None
            
            #$ Check if the nearest jet to the lepton is b-tagged
            if theLepJetBDisc > options.bDiscMin:
                NPassBDiscMinCut = NPassBDiscMinCut + 1
            if theLepJetBDisc < options.bDiscMin :
                if options.verbose : 
                    print 'closest jet to lepton is not b-tagged'
                    
                continue
            else  :

                if options.verbose :
                    print 'Event is fully tagged.'
                # Get the z-component of the lepton from the W mass constraint
                
                bJetCandP4 = theLepJet
                
                #nuCandP4 = ROOT.TLorentzVector(metPx, metPy ,0.0, metPt)
                nuCandP4 = ROOT.TLorentzVector()#(metPx, metPy ,0.0, metPt)
                nuCandP4.SetPxPyPzE(metPx, metPy, 0.0, metPt)
                solution, nuz1, nuz2 = solve_nu( vlep=theLepton, vnu=nuCandP4 )
                # If there is at least one real solution, pick it up                              
                if solution :
                    if options.verbose : 
                        print '--- Have a solution --- '
                    nuCandP4.SetPz(nuz1)
                else :
                    if options.verbose : 
                        print '--- No solution for neutrino z ---'
                    nuCandP4.SetPz(nuz1.real)

                if muJets :
                    muonJetsEvents += 1
                elif eleJets :
                    eleJetsEvents += 1

                lepTopCandP4 = nuCandP4 + theLepton + bJetCandP4

                #if ttbarCandP4.M() < 1000.0 :
                #    print 'Weird event : ' + str(event.object().id().luminosityBlock()) + ', ' + str(event.object().id().event())
                #    print ' ================'
                #    print ' Low Mass Values '
                #    print ' '
                #    print '   theLepton pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}, E = {4:6.2f}'.format (
                #        theLepton.Perp(), theLepton.Rapidity(), theLepton.Phi(), theLepton.M(), theLepton.E())
                #    print '   bJetCandP4 pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}, E = {4:6.2f} '.format (
                #        bJetCandP4.Perp(), bJetCandP4.Rapidity(), bJetCandP4.Phi(), bJetCandP4.M(), bJetCandP4.E())
                #    print '   hadTopCandP4 pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}, E = {4:6.2f} '.format (
                #        hadTopCandP4.Perp(), hadTopCandP4.Rapidity(), hadTopCandP4.Phi(), hadTopCandP4.M(), hadTopCandP4.E())
                #    print '   nuCandP4 pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}, E = {4:6.2f}'.format (
                #        nuCandP4.Perp(), nuCandP4.Rapidity(), nuCandP4.Phi(), nuCandP4.M(), nuCandP4.E())
                #else :
                #    print ' ================'
                #    print ' Normal Mass Values '
                #    print ' '
                #    print '   theLepton pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}, E = {4:6.2f} '.format (
                #    theLepton.Perp(), theLepton.Rapidity(), theLepton.Phi(), theLepton.M(), theLepton.E())
                #    print '   bJetCandP4 pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}, E = {4:6.2f}'.format (
                #        bJetCandP4.Perp(), bJetCandP4.Rapidity(), bJetCandP4.Phi(), bJetCandP4.M(), bJetCandP4.E())
                #    print '   hadTopCandP4 pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}, E = {4:6.2f}'.format (
                #        hadTopCandP4.Perp(), hadTopCandP4.Rapidity(), hadTopCandP4.Phi(), hadTopCandP4.M(), hadTopCandP4.E())
                #    print '   nuCandP4 pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}, E = {4:6.2f}'.format (
                #        nuCandP4.Perp(), nuCandP4.Rapidity(), nuCandP4.Phi(), nuCandP4.M(), nuCandP4.E())
                        
        #@ Hadronic
        elif Hadronic and nttags >= 2 : # $$$
            hadTopCand1P4 = tJets[0]
            hadTopCand2P4 = tJets[1]
            AllHadronicEvents += 1



        
        #^ Plot for ttbar Candidate Mass
        ttbarCand = None


        #!!! We need to eventually fix this so that we don't just
        #!!! throw away events that are not back-to-back. My feeling is that the events
        #!!! with ttbar systems that are boosted (due to ISR) will be
        #!!! background-enriched in any case. Food for thought. 
                                
        if Hadronic == True and nttags >= 2 : 
            ttbarCand = hadTopCand1P4 + hadTopCand2P4
        if Leptonic == True  : 
            ttbarCand = ttbarCandP4
        if SemiLeptonic == True and nttags >= 1 and hadTopCandP4.DeltaR( lepTopCandP4) > 2.0:
            ttbarCand = hadTopCandP4 + lepTopCandP4

        if ttbarCand != None and SemiLeptonic : 
            h_mttbar[0][0].Fill( ttbarCand.M(), evWeight )
            #^ Eventually fill the h_mttbar histos with cuts


        #} End event loop
    #} End root file loop
#
print '========================================='
print ' Awesome Cut Flow Table'
print '========================================='
print 'Number of Events                            ' +str(Nevents)
print 'Number of Events after event weighting      ' +str(Nevents_weighted)
print 'Number of Events before channel selection   ' +str(NeventsBeforeChannelSelect)
print 'Number of Events DiLeptonic                 ' +str(NeventsDiLeptonic           )         
print 'Number of Events SemiLeptonic               ' +str(NeventsSemiLeptonic         )            
print 'Number of Events SemiLeptonic with Muon     ' +str(NeventsSemiLeptonicMuon     )                    
print 'Number of Events SemiLeptonic with Electron ' +str(NeventsSemiLeptonicElectron )                    
print 'Number of Events AllHadronic                ' +str(NeventsAllHadronic          )           
print 'Number of Events after channel selection    ' +str(NeventsAfterChannelSelect)
print 'Number of Events with BkgdEstimation        ' +str(NeventsBkgdEstimation)
print '========================================='
print 'Number of Muons: ' +str(NMu) 
print ' Pass Pt Cut: ' +str(NPassMuonPtCut)
print ' Pass Eta Cut: ' +str(NPassMuonEtaCut)
print ' Pass Dz Cut: ' +str(NPassMuonDzCut)
print ' Pass Tight Cut: ' +str(NPassMuonTightCut)
print '========================================='
print 'Number of Electrons: ' +str(NEl)       
print ' Pass Pt Cut: ' +str(NPassElPtCut)
print ' Pass Eta Cut: ' +str(NPassElEtaCut)
print ' ~~~~~~~~ Electron ID Loose WP ~~~~~~~~~~'
print ' Pass dEtaIn Cut: ' +str(NPassEldEtaIn)
print ' Pass dPhiIn Cut: ' +str(NPassEldPhiIn)
print ' Pass 5x5 Sigma eta^{2} Cut: ' + str(NPassEl5x5)
print ' Pass H over E Cut: ' + str(NPassElHoE)
print ' Pass D0 Cut: ' + str(NPassElD0)
print ' Pass Dz Cut: ' + str(NPassElDz)
print ' Pass ooEmooP Cut: ' + str(NPassElEmooP)
print ' Pass Good Cut: ' +str(NPassGoodElCut)
print ' Pass Electron Key Cut: ' + str(NPassElKeyCut)
if options.selection == 1 or options.selection == 0 :
    print '========================================='
    print 'Number of AK4 Jets: ' +str(NAK4Jets)
    print ' Pass Good Cut: ' +str(NPassGoodJetAK4Cut)
    print ' Pass Pt Cut: ' +str(NPassMinAK4PtCut)
    print ' Pass Rapidity Cut: ' +str(NPassMaxAK4RapidityCut)
    print '========================================='
    print '~~~~~~~~~  W + b jet Selection  ~~~~~~~~~'
    print ' Passed events with nearest jet: ' +str(NPassWbEvent)
    print ' Pass Found Near Jet 1 Cut:  ' +str(NPassNearJCut)
    if options.selection == 0:
        print ' Pass Found Near Jet 2 Cut: ' +str(NPassNearJ2Cut)
    print ' Pass 2D Cut: ' +str(NPass2DCut)
    if options.selection == 0:
        print ' Pass 2D Lepton 2 Cut: ' +str(NPass2D2Cut)
    print ' Muon Pass 2D Cut: ' +str(NPassMuon2DCut)
    print ' Electron Pass 2D Cut: ' +str(NPassEl2DCut)
    print ' Pass MET cut : ' + str(NPassMET)
    print ' Pass HTLep cut : ' + str(NPassHTLep)    
    print ' Pass b Disc Min Cut: ' +str(NPassBDiscMinCut)
    if options.selection == 0:
        print ' Pass b Disc Lepton 2 Min Cut: ' +str(NPassBDisc2MinCut)
    print ' Muon Pass b Disc: ' +str(NPassMuonBCut)
    print ' Electron Pass b Disc Cut: ' +str(NPassElBCut)
if options.selection == 1 or options.selection == 2 :
    print '========================================='
    print 'Number of AK8 Jets: ' +str(NAK8Jets)
    print ' Pass Good Cut: ' +str(NPassGoodJetAK8Cut)
    print ' Pass Pt Cut: ' +str(NPassMinRawAK8PtCut)
    print ' Pass Rapidity Cut: ' +str(NPassMaxAK8RapidityCut)
    print ' Pass Semi Leptonic DR Cut: ' + str(NPassSemiLeptonicDRjlCut)
    if options.selection == 2:
        print ' Pass n Sub Jets Cut: ' +str(NPassAK8nSubJetsCut)
        print ' Pass Min Mass Cut: ' +str(NPassAK8MinMassCut) 
        print ' Pass Corrected Mass Cut: ' +str(NPassAK8CorrMassCut)
    print ' Pass Good  Min Pt Cut: ' +str(NPassminAK8PtCut)
    print ' Pass Min Mass2 Cut: ' +str(NPasstMinMassCut)
    print ' Pass Groomed Min Cut: ' +str(NPasstMAK8GroomedMinCut)
    print ' Pass Groomed Max Cut: ' +str(NPasstMAK8GroomedMaxCut)
    print ' Pass tau32 Cut: ' +str(NPasstau23Cut)
    print ' Pass tau21 Cut: ' +str(NPasstau21Cut)
print '========================================='
print 'End Awesome Cut Flow Table'
print '========================================='


if options.selection == 0 :
    print ' Number of Dimuon Events: ' + str(DimuonEvents) 
    print ' Number of Dielectron Events: ' + str(DieleEvents) 
    print ' Number of muon + electron events: ' + str(muoneleEvents)
elif options.selection == 1 :
    print ' Number of muon + Jets events: ' + str(muonJetsEvents) 
    print ' Number of electron + Jets events: ' + str(eleJetsEvents)
elif options.selection == 2 :
    print ' Number of All Hadronic Events: ' + str(AllHadronicEvents) 
else :
    print ' Number of Dimuon Events: ' + str(DimuonEvents) 
    print ' Number of Dielectron Events: ' + str(DieleEvents)
    print ' Number of muon + electron events: ' + str(muoneleEvents) 
    print ' Number of muon + Jets events: ' + str(muonJetsEvents)
    print ' Number of electron + Jets events: ' + str(eleJetsEvents)
    print ' Number of All Hadronic Events: ' + str(AllHadronicEvents)
if DimuonEvents / 1.5 < DieleEvents and DieleEvents / 1.5 < DimuonEvents :
    print ':) '

if options.isMC :
    print ''
    print 'Gen events : '
    print 'hadronic : ' + str(genHadEvents )
    print 'e+jets   : ' + str(genSemiEEvents )
    print 'mu+jets  : ' + str(genSemiMuEvents )
    print 'ee       : ' + str(genEEEvents )
    print 'emu      : ' + str(genMuEEvents)
    print 'mumu     : ' + str(genMuMuEvents)
    
#@ CLEANUP

f.cd()
f.Write()
f.Close()

if options.showEvents != None :
    print '%15s %15s %15s' % ("Run", "Lumi", "Event")
    
    for irun, run in enumerate(runNumbers) :
        if options.showEvents > 0 and irun > options.showEvents :
            break
        print '%15d %15d %15d' % (run[0], run[1], run[2])

print 'So long, and thanks for all the fish!'

