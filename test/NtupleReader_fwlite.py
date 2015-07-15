#! /usr/bin/env python

##################
# Editting flags
# #!!! Error or Something fishy
# #{ #} Start and stop loop (so reading indents isn't so bad
# #^ Plotting
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

parser.add_option('--verbose', action='store_true',
                  default=False,
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
                  default=30.,
                  dest='minMuonPt',
                  help='Minimum PT for muons')

parser.add_option('--maxMuonEta', type='float', action='store',
                  default=2.1,
                  dest='maxMuonEta',
                  help='Maximum muon pseudorapidity')

parser.add_option('--minElectronPt', type='float', action='store',
                  default=30.,
                  dest='minElectronPt',
                  help='Minimum PT for electrons')

parser.add_option('--maxElectronEta', type='float', action='store',
                  default=2.5,
                  dest='maxElectronEta',
                  help='Maximum electron pseudorapidity')


parser.add_option('--minAK4Pt', type='float', action='store',
                  default=30.,
                  dest='minAK4Pt',
                  help='Minimum PT for AK4 jets')

parser.add_option('--maxAK4Rapidity', type='float', action='store',
                  default=2.4,
                  dest='maxAK4Rapidity',
                  help='Maximum AK4 rapidity')

parser.add_option('--minAK8Pt', type='float', action='store',
                  default=400.,
                  dest='minAK8Pt',
                  help='Minimum PT for AK8 jets')

parser.add_option('--maxAK8Rapidity', type='float', action='store',
                  default=2.4,
                  dest='maxAK8Rapidity',
                  help='Maximum AK8 rapidity')


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

parser.add_option('--tau32Cut', type='float', action='store',
                  default=0.62,
                  dest='tau32Cut',
                  help='Tau3 / Tau2 n-subjettiness cut for CMS Combined Tagger')

parser.add_option('--tau21Cut', type='float', action='store',
                  default=0.5,
                  dest='tau21Cut',
                  help='Tau2 / Tau1 n-subjettiness cut for CMS Combined Tagger')

parser.add_option('--BkgEst', action='store_true',
                  default=False,
                  dest='BkgEst',
                  help='QCD Background Estimation process')

parser.add_option('--FlatSample', action='store_true',
                  default=False,
                  dest='deweightFlat',
                  help='unweights flat samples')


(options, args) = parser.parse_args()
argv = []


#@ FWLITE STUFF

import ROOT
import sys
from DataFormats.FWLite import Events, Handle
ROOT.gROOT.Macro("rootlogon.C")
from leptonic_nu_z_component import solve_nu_tmass, solve_nu
import copy


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
l_genPartMomID = ("genPart" , "genPartMomID")

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

h_NPV = Handle("std::int")
l_NPV = ( "eventUserData" , "npv" )

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
l_metPt = ("met" , "metPt")
h_metPx = Handle("std::vector<float>")
l_metPx = ("met" , "metPx")
h_metPy = Handle("std::vector<float>")
l_metPy = ("met" , "metPy")
h_metPhi = Handle("std::vector<float>")
l_metPhi = ("met" , "metPhi")

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
h_jetsAK8JEC = Handle("std::vector<float>")
l_jetsAK8JEC = ("jetsAK8" , "jetAK8jecFactor0")
h_jetsAK8Y = Handle("std::vector<float>")
l_jetsAK8Y = ("jetsAK8" , "jetAK8Y")

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
h_jetsAK8numDaughters = Handle("std::vector<float>")
l_jetsAK8numDaughters = ("jetsAK8" , "jetAK8numberOfDaughters")
h_jetsAK8cMultip = Handle("std::vector<float>")
l_jetsAK8cMultip = ("jetsAK8" , "jetAK8chargedMultiplicity")
h_jetsAK8Y = Handle("std::vector<float>")
l_jetsAK8Y = ("jetsAK8" , "jetAK8Y")

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

h_generator = Handle("GenEventInfoProduct")
l_generator = ("generator" , "" )

h_jetsAK8VSubjetIndex0 = Handle("std::vector<float>")
l_jetsAK8VSubjetIndex0 = ("jetsAK8", "jetAK8vSubjetIndex0")
h_jetsAK8VSubjetIndex1 = Handle("std::vector<float>")
l_jetsAK8VSubjetIndex1 = ("jetsAK8", "jetAK8vSubjetIndex1")

h_jetsAK8TopSubjetIndex0 = Handle("std::vector<float>")
l_jetsAK8TopSubjetIndex0 = ("jetsAK8", "jetAK8topSubjetIndex0")
h_jetsAK8TopSubjetIndex1 = Handle("std::vector<float>")
l_jetsAK8TopSubjetIndex1 = ("jetsAK8", "jetAK8topSubjetIndex1")
h_jetsAK8TopSubjetIndex2 = Handle("std::vector<float>")
l_jetsAK8TopSubjetIndex2 = ("jetsAK8", "jetAK8topSubjetIndex2")
h_jetsAK8TopSubjetIndex3 = Handle("std::vector<float>")
l_jetsAK8TopSubjetIndex3 = ("jetsAK8", "jetAK8topSubjetIndex3")


# @@@ add to cut-flow table NPassAK8SubjetBDiscCut = 0

# @@@ add label and handle for subjet pairwise masses m12, m13, and m23 then histos and cut-flow

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

# @@@ create histos for h_subjetsAK8Mass then fill them - then add to cut-flow table NPassAK8SubjetMassCut = 0

f = ROOT.TFile(options.outname, "RECREATE")
f.cd()

#^ Plot initialization

#$ Below histos with only quality cuts (see default in options above) : only plotted jets with mSD > 10 GeV as Sal suggested
h_mttbar = ROOT.TH1F("h_mttbar", ";m_{t#bar{t}} (GeV)", 200, 0, 6000)
h_mttbar_true = ROOT.TH1F("h_mttbar_true", "True m_{t#bar{t}};m_{t#bar{t}} (GeV)", 200, 0, 6000)

h_ptLep = ROOT.TH1F("h_ptLep", "Lepton p_{T};p_{T} (GeV)", 100, 0, 1000) 
h_ptEl = ROOT.TH1F("h_ptEl", "Electron p_{T};p_{T} (GeV)", 100, 0, 1000)
h_ptMu = ROOT.TH1F("h_ptMu", "Muon p_{T};p_{T} (GeV)", 100, 0, 1000)

h_etaLep = ROOT.TH1F("h_etaLep", "Lepton #eta;p_{T} (GeV)#eta", 100, 0, ROOT.TMath.TwoPi() )
h_met = ROOT.TH1F("h_met", "Missing p_{T};p_{T} (GeV)", 100, 0, 1000)
h_ptRel = ROOT.TH1F("h_ptRel", "p_{T}^{REL};p_{T}^{REL} (GeV)", 100, 0, 100)
h_dRMin = ROOT.TH1F("h_dRMin", "#Delta R_{MIN};#Delta R_{MIN}", 100, 0, 5.0)
h_2DCut = ROOT.TH2F("h_2DCut", "2D Cut;#Delta R;p_{T}^{REL}", 20, 0, 5.0, 20, 0, 100 )

h_ptAK4 = ROOT.TH1F("h_ptAK4", "AK4 Jet p_{T};p_{T} (GeV)", 300, 0, 3000)
h_etaAK4 = ROOT.TH1F("h_etaAK4", "AK4 Jet #eta;#eta", 120, -6, 6)
h_yAK4 = ROOT.TH1F("h_yAK4", "AK4 Jet Rapidity;y", 120, -6, 6)
h_phiAK4 = ROOT.TH1F("h_phiAK4", "AK4 Jet #phi;#phi (radians)",100,-3.14, 3.14)
h_mAK4 = ROOT.TH1F("h_mAK4", "AK4 Jet Mass;Mass (GeV)", 100, 0, 1000)
h_bdiscAK4 = ROOT.TH1F("h_bdiscAK4", "AK4 b discriminator;b discriminator", 100, 0, 1.0)

h_ptAK8 = ROOT.TH1F("h_ptAK8", "AK8 Jet p_{T};p_{T} (GeV)", 300, 0, 3000)
h_etaAK8 = ROOT.TH1F("h_etaAK8", "AK8 Jet #eta;#eta", 120, -6, 6)
h_yAK8 = ROOT.TH1F("h_yAK8", "AK8 Jet Rapidity;y", 120, -6, 6)
h_phiAK8 = ROOT.TH1F("h_phiAK8", "AK8 Jet #phi;#phi (radians)",100,-3.14, 3.14)
h_mAK8 = ROOT.TH1F("h_mAK8", "AK8 Jet Mass;Mass (GeV)", 100, 0, 1000)
h_mprunedAK8 = ROOT.TH1F("h_mprunedAK8", "AK8 Pruned Jet Mass;Mass (GeV)", 100, 0, 1000)
h_mfilteredAK8 = ROOT.TH1F("h_mfilteredAK8", "AK8 Filtered Jet Mass;Mass (GeV)", 100, 0, 1000)
h_mtrimmedAK8 = ROOT.TH1F("h_mtrimmedAK8", "AK8 Trimmed Jet Mass;Mass (GeV)", 100, 0, 1000)
h_mSDropAK8 = ROOT.TH1F("h_mSDropAK8", "AK8 Soft Drop Jet Mass;Mass (GeV)", 100, 0, 1000)
h_minmassAK8 = ROOT.TH1F("h_minmassAK8", "AK8 CMS Top Tagger Min Mass Paring;m_{min} (GeV)", 100, 0, 1000)
h_subjetBdiscAK8 = ROOT.TH1F("h_subjetBdiscAK8", "AK8 subjet b discriminator;b discriminator", 100, 0, 1.0)
h_nsjAK8 = ROOT.TH1F("h_nsjAK8", "AK8 CMS Top Tagger N_{subjets};N_{subjets}", 5, 0, 5)
h_tau21AK8 = ROOT.TH1F("h_tau21AK8", "AK8 Jet #tau_{2} / #tau_{1};Mass#tau_{21}", 100, 0, 1.0)
h_tau32AK8 = ROOT.TH1F("h_tau32AK8", "AK8 Jet #tau_{3} / #tau_{2};Mass#tau_{32}", 100, 0, 1.0)

#$ below plots with M_{Soft Drop} cut : 110 GeV < M_{SD} < 210 GeV

h_ptLep_mSDcut = ROOT.TH1F("h_ptLep_mSDcut", "Lepton p_{T} for 110<M_{Soft Drop}(GeV)<210;p_{T} (GeV)", 100, 0, 1000)
h_ptEl_mSDcut = ROOT.TH1F("h_ptEl_mSDcut", "Electron p_{T} for 110<M_{Soft Drop}(GeV)<210;p_{T} (GeV)", 100, 0, 1000)
h_ptMu_mSDcut = ROOT.TH1F("h_ptMu_mSDcut", "Muon p_{T} for 110<M_{Soft Drop}(GeV)<210;p_{T} (GeV)", 100, 0, 1000)

h_ptAK4_mSDcut = ROOT.TH1F("h_ptAK4_mSDcut", "AK4 Jet p_{T} for 110<M_{Soft Drop}(GeV)<210;p_{T} (GeV)", 300, 0, 3000)
h_mAK4_mSDcut = ROOT.TH1F("h_mAK4_mSDcut", "AK4 Jet Massfor 110<M_{Soft Drop}(GeV)<210;Mass (GeV)", 100, 0, 1000)
h_bdiscAK4_mSDcut = ROOT.TH1F("h_bdiscAK4_mSDcut", "AK4 b discriminatorfor 110<M_{Soft Drop}(GeV)<210;b discriminator", 100, 0, 1.0)

h_ptAK8_mSDcut = ROOT.TH1F("h_ptAK8_mSDcut", "AK8 Jet p_{T}for 110<M_{Soft Drop}(GeV)<210;p_{T} (GeV)", 300, 0, 3000)
h_etaAK8_mSDcut = ROOT.TH1F("h_etaAK8_mSDcut", "AK8 Jet #etafor 110<M_{Soft Drop}(GeV)<210;#eta", 120, -6, 6)
h_yAK8_mSDcut = ROOT.TH1F("h_yAK8_mSDcut", "AK8 Jet Rapidity for 110<M_{Soft Drop}(GeV)<210;y", 120, -6, 6)
h_phiAK8_mSDcut = ROOT.TH1F("h_phiAK8_mSDcut", "AK8 Jet #phi for 110<M_{Soft Drop}(GeV)<210;#phi (radians)",100,-3.14, 3.14)
h_mAK8_mSDcut = ROOT.TH1F("h_mAK8_mSDcut", "AK8 Jet Mass for 110<M_{Soft Drop}(GeV)<210;Mass (GeV)", 100, 0, 1000)
h_mprunedAK8_mSDcut = ROOT.TH1F("h_mprunedAK8_mSDcut", "AK8 Pruned Jet Mass for 110<M_{Soft Drop}(GeV)<210;Mass (GeV)", 100, 0, 1000)
h_mfilteredAK8_mSDcut = ROOT.TH1F("h_mfilteredAK8_mSDcut", "AK8 Filtered Jet Mass for 110<M_{Soft Drop}(GeV)<210;Mass (GeV)", 100, 0, 1000)
h_mtrimmedAK8_mSDcut = ROOT.TH1F("h_mtrimmedAK8_mSDcut", "AK8 Trimmed Jet Mass for 110<M_{Soft Drop}(GeV)<210;Mass (GeV)", 100, 0, 1000)
h_mSDropAK8_mSDcut = ROOT.TH1F("h_mSDropAK8_mSDcut", "AK8 Soft Drop Jet Mass for 110<M_{Soft Drop}(GeV)<210;Mass (GeV)", 100, 0, 1000)
h_minmassAK8_mSDcut = ROOT.TH1F("h_minmassAK8_mSDcut", "AK8 CMS Top Tagger Min Mass Paring for 110<M_{Soft Drop}(GeV)<210;m_{min} (GeV)", 100, 0, 1000)
h_subjetBdiscAK8_mSDcut = ROOT.TH1F("h_subjetBdiscAK8_mSDcut", "AK8 subjet b discriminator for 110<M_{Soft Drop}(GeV)<210;b discriminator", 100, 0, 1.0)
h_nsjAK8_mSDcut = ROOT.TH1F("h_nsjAK8_mSDcut", "AK8 CMS Top Tagger N_{subjets}for 110<M_{Soft Drop}(GeV)<210;N_{subjets}", 5, 0, 5)
h_tau21AK8_mSDcut = ROOT.TH1F("h_tau21AK8_mSDcut", "AK8 Jet #tau_{2} / #tau_{1} for 110<M_{Soft Drop}(GeV)<210;Mass#tau_{21}", 100, 0, 1.0)
h_tau32AK8_mSDcut = ROOT.TH1F("h_tau32AK8_mSDcut", "AK8 Jet #tau_{3} / #tau_{2} for 110<M_{Soft Drop}(GeV)<210;Mass#tau_{32}", 100, 0, 1.0)

#$ below plots with tau32 cut

h_ptLep_tau32cut = ROOT.TH1F("h_ptLep_tau32cut", "Lepton p_{T} for tau32 cut;p_{T} (GeV)", 100, 0, 1000)
h_ptEl_tau32cut = ROOT.TH1F("h_ptEl_tau32cut", "Electron p_{T} for tau32 cut;p_{T} (GeV)", 100, 0, 1000)
h_ptMu_tau32cut = ROOT.TH1F("h_ptMu_tau32cut", "Muon p_{T} for tau32 cut;p_{T} (GeV)", 100, 0, 1000)

h_ptAK4_tau32cut = ROOT.TH1F("h_ptAK4_tau32cut", "AK4 Jet p_{T} for tau32 cut;p_{T} (GeV)", 300, 0, 3000)
h_mAK4_tau32cut = ROOT.TH1F("h_mAK4_tau32cut", "AK4 Jet Massfor tau32 cut;Mass (GeV)", 100, 0, 1000)
h_bdiscAK4_tau32cut = ROOT.TH1F("h_bdiscAK4_tau32cut", "AK4 b discriminatorfor tau32 cut;b discriminator", 100, 0, 1.0)

h_ptAK8_tau32cut = ROOT.TH1F("h_ptAK8_tau32cut", "AK8 Jet p_{T}for tau32 cut;p_{T} (GeV)", 300, 0, 3000)
h_etaAK8_tau32cut = ROOT.TH1F("h_etaAK8_tau32cut", "AK8 Jet #etafor tau32 cut;#eta", 120, -6, 6)
h_yAK8_tau32cut = ROOT.TH1F("h_yAK8_tau32cut", "AK8 Jet Rapidity for tau32 cut;y", 120, -6, 6)
h_phiAK8_tau32cut = ROOT.TH1F("h_phiAK8_tau32cut", "AK8 Jet #phi for tau32 cut;#phi (radians)",100,-3.14, 3.14)
h_mAK8_tau32cut = ROOT.TH1F("h_mAK8_tau32cut", "AK8 Jet Mass for tau32 cut;Mass (GeV)", 100, 0, 1000)
h_mprunedAK8_tau32cut = ROOT.TH1F("h_mprunedAK8_tau32cut", "AK8 Pruned Jet Mass for tau32 cut;Mass (GeV)", 100, 0, 1000)
h_mfilteredAK8_tau32cut = ROOT.TH1F("h_mfilteredAK8_tau32cut", "AK8 Filtered Jet Mass for tau32 cut;Mass (GeV)", 100, 0, 1000)
h_mtrimmedAK8_tau32cut = ROOT.TH1F("h_mtrimmedAK8_tau32cut", "AK8 Trimmed Jet Mass for tau32 cut;Mass (GeV)", 100, 0, 1000)
h_mSDropAK8_tau32cut = ROOT.TH1F("h_mSDropAK8_tau32cut", "AK8 Soft Drop Jet Mass for tau32 cut;Mass (GeV)", 100, 0, 1000)
h_minmassAK8_tau32cut = ROOT.TH1F("h_minmassAK8_tau32cut", "AK8 CMS Top Tagger Min Mass Paring for tau32 cut;m_{min} (GeV)", 100, 0, 1000)
h_subjetBdiscAK8_tau32cut = ROOT.TH1F("h_subjetBdiscAK8_tau32cut", "AK8 subjet b discriminator for tau32 cut;b discriminator", 100, 0, 1.0)
h_nsjAK8_tau32cut = ROOT.TH1F("h_nsjAK8_tau32cut", "AK8 CMS Top Tagger N_{subjets}for tau32 cut;N_{subjets}", 5, 0, 5)
h_tau21AK8_tau32cut = ROOT.TH1F("h_tau21AK8_tau32cut", "AK8 Jet #tau_{2} / #tau_{1} for tau32 cut;Mass#tau_{21}", 100, 0, 1.0)
h_tau32AK8_tau32cut = ROOT.TH1F("h_tau32AK8_tau32cut", "AK8 Jet #tau_{3} / #tau_{2} for tau32 cut;Mass#tau_{32}", 100, 0, 1.0)
#$ plots with tau21 cut

h_ptLep_tau21cut = ROOT.TH1F("h_ptLep_tau21cut", "Lepton p_{T} for tau21 cut;p_{T} (GeV)", 100, 0, 1000)
h_ptEl_tau21cut = ROOT.TH1F("h_ptEl_tau21cut", "Electron p_{T} for tau21 cut;p_{T} (GeV)", 100, 0, 1000)
h_ptMu_tau21cut = ROOT.TH1F("h_ptMu_tau21cut", "Muon p_{T} for tau21 cut;p_{T} (GeV)", 100, 0, 1000)

h_ptAK4_tau21cut = ROOT.TH1F("h_ptAK4_tau21cut", "AK4 Jet p_{T} for tau21 cut;p_{T} (GeV)", 300, 0, 3000)
h_mAK4_tau21cut = ROOT.TH1F("h_mAK4_tau21cut", "AK4 Jet Massfor tau21 cut;Mass (GeV)", 100, 0, 1000)
h_bdiscAK4_tau21cut = ROOT.TH1F("h_bdiscAK4_tau21cut", "AK4 b discriminatorfor tau21 cut;b discriminator", 100, 0, 1.0)

h_ptAK8_tau21cut = ROOT.TH1F("h_ptAK8_tau21cut", "AK8 Jet p_{T}for tau21 cut;p_{T} (GeV)", 300, 0, 3000)
h_etaAK8_tau21cut = ROOT.TH1F("h_etaAK8_tau21cut", "AK8 Jet #etafor tau21 cut;#eta", 120, -6, 6)
h_yAK8_tau21cut = ROOT.TH1F("h_yAK8_tau21cut", "AK8 Jet Rapidity for tau21 cut;y", 120, -6, 6)
h_phiAK8_tau21cut = ROOT.TH1F("h_phiAK8_tau21cut", "AK8 Jet #phi for tau21 cut;#phi (radians)",100,-3.14, 3.14)
h_mAK8_tau21cut = ROOT.TH1F("h_mAK8_tau21cut", "AK8 Jet Mass for tau21 cut;Mass (GeV)", 100, 0, 1000)
h_mprunedAK8_tau21cut = ROOT.TH1F("h_mprunedAK8_tau21cut", "AK8 Pruned Jet Mass for tau21 cut;Mass (GeV)", 100, 0, 1000)
h_mfilteredAK8_tau21cut = ROOT.TH1F("h_mfilteredAK8_tau21cut", "AK8 Filtered Jet Mass for tau21 cut;Mass (GeV)", 100, 0, 1000)
h_mtrimmedAK8_tau21cut = ROOT.TH1F("h_mtrimmedAK8_tau21cut", "AK8 Trimmed Jet Mass for tau21 cut;Mass (GeV)", 100, 0, 1000)
h_mSDropAK8_tau21cut = ROOT.TH1F("h_mSDropAK8_tau21cut", "AK8 Soft Drop Jet Mass for tau21 cut;Mass (GeV)", 100, 0, 1000)
h_minmassAK8_tau21cut = ROOT.TH1F("h_minmassAK8_tau21cut", "AK8 CMS Top Tagger Min Mass Paring for tau21 cut;m_{min} (GeV)", 100, 0, 1000)
h_subjetBdiscAK8_tau21cut = ROOT.TH1F("h_subjetBdiscAK8_tau21cut", "AK8 subjet b discriminator for tau21 cut;b discriminator", 100, 0, 1.0)
h_nsjAK8_tau21cut = ROOT.TH1F("h_nsjAK8_tau21cut", "AK8 CMS Top Tagger N_{subjets}for tau21 cut;N_{subjets}", 5, 0, 5)
h_tau32AK8_tau21cut = ROOT.TH1F("h_tau21AK8_tau21cut", "AK8 Jet #tau_{3} / #tau_{2} for tau21 cut;Mass#tau_{32}", 100, 0, 1.0)
h_tau21AK8_tau21cut = ROOT.TH1F("h_tau21AK8_tau21cut", "AK8 Jet #tau_{2} / #tau_{1} for tau32 cut;Mass#tau_{21}", 100, 0, 1.0)

#$ plots with both mass and tau32 cut - SD tagged

h_ptLep_mSDcut_tau32cut = ROOT.TH1F("h_ptLep_mSDcut_tau32cut", "Lepton p_{T} for 110<M_{Soft Drop}(GeV)<210 and tau32<0.62;p_{T} (GeV)", 100, 0, 1000)
h_ptEl_mSDcut_tau32cut = ROOT.TH1F("h_ptEl_mSDcut_tau32cut", "Electron p_{T} for 110<M_{Soft Drop}(GeV)<210 and tau32<0.62;p_{T} (GeV)", 100, 0, 1000)
h_ptMu_mSDcut_tau32cut = ROOT.TH1F("h_ptMu_mSDcut_tau32cut", "Muon p_{T} for 110<M_{Soft Drop}(GeV)<210 and tau32<0.62;p_{T} (GeV)", 100, 0, 1000)
h_ptAK4_mSDcut_tau32cut = ROOT.TH1F("h_ptAK4_mSDcut_tau32cut", "AK4 Jet p_{T} for 110<M_{Soft Drop}(GeV)<210 and tau32<0.62;p_{T} (GeV)", 300, 0, 3000)
h_mAK4_mSDcut_tau32cut = ROOT.TH1F("h_mAK4_mSDcut_tau32cut", "AK4 Jet Massfor 110<M_{Soft Drop}(GeV)<210 and tau32<0.62;Mass (GeV)", 100, 0, 1000)
h_bdiscAK4_mSDcut_tau32cut = ROOT.TH1F("h_bdiscAK4_mSDcut_tau32cut", "AK4 b discriminatorfor 110<M_{Soft Drop}(GeV)<210 and tau32<0.62;b discriminator", 100, 0, 1.0)

h_ptAK8_mSDcut_tau32cut = ROOT.TH1F("h_ptAK8_mSDcut_tau32cut", "AK8 Jet p_{T}for 110<M_{Soft Drop}(GeV)<210 and tau32<0.62;p_{T} (GeV)", 300, 0, 3000)
h_etaAK8_mSDcut_tau32cut = ROOT.TH1F("h_etaAK8_mSDcut_tau32cut", "AK8 Jet #etafor 110<M_{Soft Drop}(GeV)<210 and tau32<0.62;#eta", 120, -6, 6)
h_yAK8_mSDcut_tau32cut = ROOT.TH1F("h_yAK8_mSDcut_tau32cut", "AK8 Jet Rapidity for 110<M_{Soft Drop}(GeV)<210 and tau32<0.62;y", 120, -6, 6)
h_phiAK8_mSDcut_tau32cut = ROOT.TH1F("h_phiAK8_mSDcut_tau32cut", "AK8 Jet #phi for 110<M_{Soft Drop}(GeV)<210 and tau32<0.62;#phi (radians)",100,-3.14, 3.14)
h_mAK8_mSDcut_tau32cut = ROOT.TH1F("h_mAK8_mSDcut_tau32cut", "AK8 Jet Mass for 110<M_{Soft Drop}(GeV)<210 and tau32<0.62;Mass (GeV)", 100, 0, 1000)
h_mprunedAK8_mSDcut_tau32cut = ROOT.TH1F("h_mprunedAK8_mSDcut_tau32cut", "AK8 Pruned Jet Mass for 110<M_{Soft Drop}(GeV)<210 and tau32<0.62;Mass (GeV)", 100, 0, 1000)
h_mfilteredAK8_mSDcut_tau32cut = ROOT.TH1F("h_mfilteredAK8_mSDcut_tau32cut", "AK8 Filtered Jet Mass for 110<M_{Soft Drop}(GeV)<210 and tau32<0.62;Mass (GeV)", 100, 0, 1000)
h_mtrimmedAK8_mSDcut_tau32cut = ROOT.TH1F("h_mtrimmedAK8_mSDcut_tau32cut", "AK8 Trimmed Jet Mass for 110<M_{Soft Drop}(GeV)<210 and tau32<0.62;Mass (GeV)", 100, 0, 1000)
h_mSDropAK8_mSDcut_tau32cut = ROOT.TH1F("h_mSDropAK8_mSDcut_tau32cut", "AK8 Soft Drop Jet Mass for 110<M_{Soft Drop}(GeV)<210 and tau32<0.62;Mass (GeV)", 100, 0, 1000)
h_minmassAK8_mSDcut_tau32cut = ROOT.TH1F("h_minmassAK8_mSDcut_tau32cut", "AK8 CMS Top Tagger Min Mass Paring for 110<M_{Soft Drop}(GeV)<210 and tau32<0.62;m_{min} (GeV)", 100, 0, 1000)
h_subjetBdiscAK8_mSDcut_tau32cut = ROOT.TH1F("h_subjetBdiscAK8_mSDcut_tau32cut", "AK8 subjet b discriminator for 110<M_{Soft Drop}(GeV)<210 and tau32<0.62;b discriminator", 100, 0, 1.0)
h_nsjAK8_mSDcut_tau32cut = ROOT.TH1F("h_nsjAK8_mSDcut_tau32cut", "AK8 CMS Top Tagger N_{subjets}for 110<M_{Soft Drop}(GeV)<210 and tau32<0.62;N_{subjets}", 5, 0, 5)
h_tau21AK8_mSDcut_tau32cut = ROOT.TH1F("h_tau21AK8_mSDcut_tau32cut", "AK8 Jet #tau_{2} / #tau_{1} for 110<M_{Soft Drop}(GeV)<210 and tau32<0.62;Mass#tau_{21}", 100, 0, 1.0)
h_tau32AK8_mSDcut_tau32cut = ROOT.TH1F("h_tau32AK8_mSDcut_tau32cut", "AK8 Jet #tau_{3} / #tau_{2} for 110<M_{Soft Drop}(GeV)<210 and tau32<0.62;Mass#tau_{32}", 100, 0, 1.0)

#$ plots with pt of the electron cut

#h_mttbar_ptElcut = ROOT.TH1F("h_mttbar", ";m_{t#bar{t}} for ptEl cut (GeV)", 200, 0, 6000)

h_ptLep_ptElcut = ROOT.TH1F("h_ptLep_ptElcut", "Lepton p_{T} for pt El cut;p_{T} (GeV)", 100, 0, 1000)
h_ptMu_ptElcut = ROOT.TH1F("h_ptMu_ptElcut", "Electron p_{T} for pt El cut;p_{T} (GeV)", 100, 0, 1000)
h_ptEl_ptElcut = ROOT.TH1F("h_ptEl_ptElcut", "Muon p_{T} for pt El cut;p_{T} (GeV)", 100, 0, 1000)

h_ptAK4_ptElcut = ROOT.TH1F("h_ptAK4_ptElcut", "AK4 Jet p_{T} for ptEl cut;p_{T} (GeV)", 300, 0, 3000)
h_mAK4_ptElcut = ROOT.TH1F("h_mAK4_ptElcut", "AK4 Jet Massfor ptEl cut;Mass (GeV)", 100, 0, 1000)
h_bdiscAK4_ptElcut = ROOT.TH1F("h_bdiscAK4_ptElcut", "AK4 b discriminator for ptEl cut;b discriminator", 100, 0, 1.0)

h_ptAK8_ptElcut = ROOT.TH1F("h_ptAK8_ptElcut", "AK8 Jet p_{T}for ptEl cut;p_{T} (GeV)", 300, 0, 3000)
h_etaAK8_ptElcut = ROOT.TH1F("h_etaAK8_ptElcut", "AK8 Jet #etafor ptEl cut;#eta", 120, -6, 6)
h_yAK8_ptElcut = ROOT.TH1F("h_yAK8_ptElcut", "AK8 Jet Rapidity for ptEl cut;y", 120, -6, 6)
h_phiAK8_ptElcut = ROOT.TH1F("h_phiAK8_ptElcut", "AK8 Jet #phi for ptEl cut;#phi (radians)",100,-3.14, 3.14)
h_mAK8_ptElcut = ROOT.TH1F("h_mAK8_ptElcut", "AK8 Jet Mass for ptEl cut;Mass (GeV)", 100, 0, 1000)
h_mprunedAK8_ptElcut = ROOT.TH1F("h_mprunedAK8_ptElcut", "AK8 Pruned Jet Mass for ptEl cut;Mass (GeV)", 100, 0, 1000)
h_mfilteredAK8_ptElcut = ROOT.TH1F("h_mfilteredAK8_ptElcut", "AK8 Filtered Jet Mass for ptEl cut;Mass (GeV)", 100, 0, 1000)
h_mtrimmedAK8_ptElcut = ROOT.TH1F("h_mtrimmedAK8_ptElcut", "AK8 Trimmed Jet Mass for ptEl cut;Mass (GeV)", 100, 0, 1000)
h_mSDropAK8_ptElcut = ROOT.TH1F("h_mSDropAK8_ptElcut", "AK8 Soft Drop Jet Mass for ptEl cut;Mass (GeV)", 100, 0, 1000)
h_minmassAK8_ptElcut = ROOT.TH1F("h_minmassAK8_ptElcut", "AK8 CMS Top Tagger Min Mass Paring for ptEl cut;m_{min} (GeV)", 100, 0, 1000)
h_subjetBdiscAK8_ptElcut = ROOT.TH1F("h_subjetBdiscAK8_ptElcut", "AK8 subjet b discriminator for  ptEl cut;b discriminator", 100, 0, 1.0)
h_nsjAK8_ptElcut = ROOT.TH1F("h_nsjAK8_ptElcut", "AK8 CMS Top Tagger N_{subjets}for ptEl cut;N_{subjets}", 5, 0, 5)
h_tau32AK8_ptElcut = ROOT.TH1F("h_ptElAK8_ptElcut", "AK8 Jet #tau_{3} / #tau_{2} for ptEl cut;Mass#tau_{32}", 100, 0, 1.0)

#$ plots with pt of the muon cut

h_ptLep_ptMucut = ROOT.TH1F("h_ptLep_ptMucut", "Lepton p_{T} for pt Muon cut;p_{T} (GeV)", 100, 0, 1000)
h_ptMu_ptMucut = ROOT.TH1F("h_ptMu_ptMucut", "Electron p_{T} for pt Muon cut;p_{T} (GeV)", 100, 0, 1000)
h_ptEl_ptMucut = ROOT.TH1F("h_ptEl_ptMucut", "Muon p_{T} for pt Muon cut;p_{T} (GeV)", 100, 0, 1000)

h_ptAK4_ptMucut = ROOT.TH1F("h_ptAK4_ptMucut", "AK4 Jet p_{T} for ptMuon cut;p_{T} (GeV)", 300, 0, 3000)
h_mAK4_ptMucut = ROOT.TH1F("h_mAK4_ptMucut", "AK4 Jet Massfor ptMuon cut;Mass (GeV)", 100, 0, 1000)
h_bdiscAK4_ptMucut = ROOT.TH1F("h_bdiscAK4_ptMucut", "AK4 b discriminator for ptMuon cut;b discriminator", 100, 0, 1.0)

h_ptAK8_ptMucut = ROOT.TH1F("h_ptAK8_ptMucut", "AK8 Jet p_{T}for ptMuon cut;p_{T} (GeV)", 300, 0, 3000)
h_etaAK8_ptMucut = ROOT.TH1F("h_etaAK8_ptMucut", "AK8 Jet #etafor ptMuon cut;#eta", 120, -6, 6)
h_yAK8_ptMucut = ROOT.TH1F("h_yAK8_ptMucut", "AK8 Jet Rapidity for ptMuon cut;y", 120, -6, 6)
h_phiAK8_ptMucut = ROOT.TH1F("h_phiAK8_ptMucut", "AK8 Jet #phi for ptMuon cut;#phi (radians)",100,-3.14, 3.14)
h_mAK8_ptMucut = ROOT.TH1F("h_mAK8_ptMucut", "AK8 Jet Mass for ptMuon cut;Mass (GeV)", 100, 0, 1000)
h_mprunedAK8_ptMucut = ROOT.TH1F("h_mprunedAK8_ptMucut", "AK8 Pruned Jet Mass for ptMuon cut;Mass (GeV)", 100, 0, 1000)
h_mfilteredAK8_ptMucut = ROOT.TH1F("h_mfilteredAK8_ptMucut", "AK8 Filtered Jet Mass for ptMuon cut;Mass (GeV)", 100, 0, 1000)
h_mtrimmedAK8_ptMucut = ROOT.TH1F("h_mtrimmedAK8_ptMucut", "AK8 Trimmed Jet Mass for ptMuon cut;Mass (GeV)", 100, 0, 1000)
h_mSDropAK8_ptMucut = ROOT.TH1F("h_mSDropAK8_ptMucut", "AK8 Soft Drop Jet Mass for ptMuon cut;Mass (GeV)", 100, 0, 1000)
h_minmassAK8_ptMucut = ROOT.TH1F("h_minmassAK8_ptMucut", "AK8 CMS Top Tagger Min Mass Paring for ptMuon cut;m_{min} (GeV)", 100, 0, 1000)
h_subjetBdiscAK8_ptMucut = ROOT.TH1F("h_subjetBdiscAK8_ptMucut", "AK8 subjet b discriminator for  ptMuon cut;b discriminator", 100, 0, 1.0)
h_nsjAK8_ptMucut = ROOT.TH1F("h_nsjAK8_ptMucut", "AK8 CMS Top Tagger N_{subjets}for ptMuon cut;N_{subjets}", 5, 0, 5)
h_tau32AK8_ptMucut = ROOT.TH1F("h_ptElAK8_ptMucut", "AK8 Jet #tau_{3} / #tau_{2} for ptMuon cut;Mass#tau_{32}", 100, 0, 1.0)


#$ below plots with min Mass cut


h_ptLep_minMasscut = ROOT.TH1F("h_ptLep_minMasscut", "Lepton p_{T} for min Mass cut;p_{T} (GeV)", 100, 0, 1000)
h_ptMu_minMasscut = ROOT.TH1F("h_ptMu_minMasscut", "Muon p_{T} for min Mass cut;p_{T} (GeV)", 100, 0, 1000)
h_ptEl_minMasscut = ROOT.TH1F("h_ptEl_minMasscut", "Electron p_{T} for min Mass cut;p_{T} (GeV)", 100, 0, 1000)

h_ptAK4_minMasscut = ROOT.TH1F("h_ptAK4_minMasscut", "AK4 Jet p_{T} for min Mass cut;p_{T} (GeV)", 300, 0, 3000)
h_mAK4_minMasscut = ROOT.TH1F("h_mAK4_minMasscut", "AK4 Jet Massfor min Mass cut;Mass (GeV)", 100, 0, 1000)
h_bdiscAK4_minMasscut = ROOT.TH1F("h_bdiscAK4_minMasscut", "AK4 b discriminatorfor min Mass cut;b discriminator", 100, 0, 1.0)

h_ptAK8_minMasscut = ROOT.TH1F("h_ptAK8_minMasscut", "AK8 Jet p_{T}for min Mass cut;p_{T} (GeV)", 300, 0, 3000)
h_etaAK8_minMasscut = ROOT.TH1F("h_etaAK8_minMasscut", "AK8 Jet #etafor minMass cut;#eta", 120, -6, 6)
h_yAK8_minMasscut = ROOT.TH1F("h_yAK8_minMasscut", "AK8 Jet Rapidity for minMass cut;y", 120, -6, 6)
h_phiAK8_minMasscut = ROOT.TH1F("h_phiAK8_minMasscut", "AK8 Jet #phi for minMass cut;#phi (radians)",100,-3.14, 3.14)
h_mAK8_minMasscut = ROOT.TH1F("h_mAK8_minMasscut", "AK8 Jet Mass for min Mass cut;Mass (GeV)", 100, 0, 1000)
h_mprunedAK8_minMasscut = ROOT.TH1F("h_mprunedAK8_minMasscut", "AK8 Pruned Jet Mass for min Mass cut;Mass (GeV)", 100, 0, 1000)
h_mfilteredAK8_minMasscut = ROOT.TH1F("h_mfilteredAK8_minMasscut", "AK8 Filtered Jet Mass for min Mass cut;Mass (GeV)", 100, 0, 1000)
h_mtrimmedAK8_minMasscut = ROOT.TH1F("h_mtrimmedAK8_minMasscut", "AK8 Trimmed Jet Mass for min Mass cut;Mass (GeV)", 100, 0, 1000)
h_mSDropAK8_minMasscut = ROOT.TH1F("h_mSDropAK8_minMasscut", "AK8 Soft Drop Jet Mass for min Mass cut;Mass (GeV)", 100, 0, 1000)
h_minmassAK8_minMasscut = ROOT.TH1F("h_minmassAK8_minMasscut", "AK8 CMS Top Tagger Min Mass Paring for min Mass cut;m_{min} (GeV)", 100, 0, 1000)
h_subjetBdiscAK8_minMasscut = ROOT.TH1F("h_subjetBdiscAK8_minMasscut", "AK8 subjet b discriminator for min Mass cut;b discriminator", 100, 0, 1.0)
h_nsjAK8_minMasscut = ROOT.TH1F("h_nsjAK8_minMasscut", "AK8 CMS Top Tagger N_{subjets}for min Mass cut;N_{subjets}", 5, 0, 5)
h_tau21AK8_minMasscut = ROOT.TH1F("h_tau21AK8_minMasscut", "AK8 Jet #tau_{2} / #tau_{1} for min Mass cut;Mass#tau_{21}", 100, 0, 1.0)
h_tau32AK8_minMasscut = ROOT.TH1F("h_tau32AK8_minMasscut", "AK8 Jet #tau_{3} / #tau_{2} for min Mass cut;Mass#tau_{32}", 100, 0, 1.0)


#$ below plots with bdiscmin cut

h_ptLep_bDiscMincut = ROOT.TH1F("h_ptLep_bDiscMincut", "Lepton p_{T} for bDiscMincut loose  cut;p_{T} (GeV)", 100, 0, 1000)
h_ptMu_bDiscMincut = ROOT.TH1F("h_ptMu_bDiscMincut", "Muon p_{T} for bDiscMincut loose cut;p_{T} (GeV)", 100, 0, 1000)
h_ptEl_bDiscMincut = ROOT.TH1F("h_ptEl_bDiscMincut", "Electron p_{T} for bDiscMincut loose cut;p_{T} (GeV)", 100, 0, 1000)

h_ptAK4_bDiscMincut = ROOT.TH1F("h_ptAK4_bDiscMincut", "AK4 Jet p_{T} for bDiscMincut loose cut;p_{T} (GeV)", 300, 0, 3000)
h_mAK4_bDiscMincut = ROOT.TH1F("h_mAK4_bDiscMincut", "AK4 Jet Mass for bDiscMincut loose cut;Mass (GeV)", 100, 0, 1000)
h_bdiscAK4_bDiscMincut = ROOT.TH1F("h_bdiscAK4_bDiscMincut", "AK4 b discriminator for bDiscMincut loose cut;b discriminator", 100, 0, 1.0)

h_ptAK8_bDiscMincut = ROOT.TH1F("h_ptAK8_bDiscMincut", "AK8 Jet p_{T}for bDiscMincut loose cut;p_{T} (GeV)", 300, 0, 3000)
h_etaAK8_bDiscMincut = ROOT.TH1F("h_etaAK8_bDiscMincut", "AK8 Jet #eta for bDiscMincut loose  cut;#eta", 120, -6, 6)
h_yAK8_bDiscMincut = ROOT.TH1F("h_yAK8_bDiscMincut", "AK8 Jet Rapidity for bDiscMincut loose  cut;y", 120, -6, 6)
h_phiAK8_bDiscMincut = ROOT.TH1F("h_phiAK8_bDiscMincut", "AK8 Jet #phi for bDiscMincut loose  cut;#phi (radians)",100,-3.14, 3.14)
h_mAK8_bDiscMincut = ROOT.TH1F("h_mAK8_bDiscMincut", "AK8 Jet Mass for bDiscMincut loose cut;Mass (GeV)", 100, 0, 1000)
h_mprunedAK8_bDiscMincut = ROOT.TH1F("h_mprunedAK8_bDiscMincut", "AK8 Pruned Jet Mass for bDiscMincut loose cut;Mass (GeV)", 100, 0, 1000)
h_mfilteredAK8_bDiscMincut = ROOT.TH1F("h_mfilteredAK8_bDiscMincut", "AK8 Filtered Jet Mass for bDiscMincut loose cut;Mass (GeV)", 100, 0, 1000)
h_mtrimmedAK8_bDiscMincut = ROOT.TH1F("h_mtrimmedAK8_bDiscMincut", "AK8 Trimmed Jet Mass for bDiscMincut loose cut;Mass (GeV)", 100, 0, 1000)
h_mSDropAK8_bDiscMincut = ROOT.TH1F("h_mSDropAK8_bDiscMincut", "AK8 Soft Drop Jet Mass for bDiscMincut loose cut;Mass (GeV)", 100, 0, 1000)
h_minmassAK8_bDiscMincut = ROOT.TH1F("h_minmassAK8_bDiscMincut", "AK8 CMS Top Tagger bDiscMincut loose Paring for bDiscMincut loose cut;m_{min} (GeV)", 100, 0, 1000)
h_subjetBdiscAK8_bDiscMincut = ROOT.TH1F("h_subjetBdiscAK8_bDiscMincut", "AK8 CMS Top Tagger subjet bDisc for bDiscMincut loose cut;m_{min} (GeV)", 100, 0, 1000)
h_nsjAK8_bDiscMincut = ROOT.TH1F("h_nsjAK8_bDiscMincut", "AK8 CMS Top Tagger N_{subjets}for bDiscMincut loose cut;N_{subjets}", 5, 0, 5)
h_tau21AK8_bDiscMincut = ROOT.TH1F("h_tau21AK8_bDiscMincut", "AK8 Jet #tau_{2} / #tau_{1} for bDiscMincut loose cut;Mass#tau_{21}", 100, 0, 1.0)
h_tau32AK8_bDiscMincut = ROOT.TH1F("h_tau32AK8_bDiscMincut", "AK8 Jet #tau_{3} / #tau_{2} for bDiscMincut loose  cut;Mass#tau_{32}", 100, 0, 1.0)


#$ plots with both mass and minmass cut - CMSTT tagged

h_ptLep_mSDcut_minMasscut= ROOT.TH1F("h_ptLep_mSDcut_minMasscut", "Lepton p_{T} for 110<M_{Soft Drop}(GeV)<210 and minMass > 50 GeV;p_{T} (GeV)", 100, 0, 1000)
h_ptEl_mSDcut_minMasscut = ROOT.TH1F("h_ptEl_mSDcut_minMasscut", "Electron p_{T} for 110<M_{Soft Drop}(GeV)<210 and minMass > 50 GeV;p_{T} (GeV)", 100, 0, 1000)
h_ptMu_mSDcut_minMasscut = ROOT.TH1F("h_ptMu_mSDcut_minMasscut", "Muon p_{T} for 110<M_{Soft Drop}(GeV)<210 and minMass > 50 GeV;p_{T} (GeV)", 100, 0, 1000)
h_ptAK4_mSDcut_minMasscut = ROOT.TH1F("h_ptAK4_mSDcut_minMasscut", "AK4 Jet p_{T} for 110<M_{Soft Drop}(GeV)<210 and minMass > 50 GeV;p_{T} (GeV)", 300, 0, 3000)
h_mAK4_mSDcut_minMasscut = ROOT.TH1F("h_mAK4_mSDcut_minMasscut", "AK4 Jet Massfor 110<M_{Soft Drop}(GeV)<210 and minMass > 50 GeV;Mass (GeV)", 100, 0, 1000)
h_bdiscAK4_mSDcut_minMasscut = ROOT.TH1F("h_bdiscAK4_mSDcut_minMasscut", "AK4 b discriminatorfor 110<M_{Soft Drop}(GeV)<210 and minMass > 50 GeV;b discriminator", 100, 0, 1.0)

h_ptAK8_mSDcut_minMasscut = ROOT.TH1F("h_ptAK8_mSDcut_minMasscut", "AK8 Jet p_{T}for 110<M_{Soft Drop}(GeV)<210 and minMass > 50 GeV;p_{T} (GeV)", 300, 0, 3000)
h_etaAK8_mSDcut_minMasscut = ROOT.TH1F("h_etaAK8_mSDcut_minMasscut", "AK8 Jet #etafor 110<M_{Soft Drop}(GeV)<210 and minMass > 50 GeV;#eta", 120, -6, 6)
h_yAK8_mSDcut_minMasscut = ROOT.TH1F("h_yAK8_mSDcut_minMasscut", "AK8 Jet Rapidity for 110<M_{Soft Drop}(GeV)<210 and minMass > 50 GeV;y", 120, -6, 6)
h_phiAK8_mSDcut_minMasscut = ROOT.TH1F("h_phiAK8_mSDcut_minMasscut", "AK8 Jet #phi for 110<M_{Soft Drop}(GeV)<210 and minMass > 50 GeV;#phi (radians)",100,-3.14, 3.14)
h_mAK8_mSDcut_minMasscut = ROOT.TH1F("h_mAK8_mSDcut_minMasscut", "AK8 Jet Mass for 110<M_{Soft Drop}(GeV)<210 and minMass > 50 GeV;Mass (GeV)", 100, 0, 1000)
h_mprunedAK8_mSDcut_minMasscut = ROOT.TH1F("h_mprunedAK8_mSDcut_minMasscut", "AK8 Pruned Jet Mass for 110<M_{Soft Drop}(GeV)<210 and minMass > 50 GeV;Mass (GeV)", 100, 0, 1000)
h_mfilteredAK8_mSDcut_minMasscut = ROOT.TH1F("h_mfilteredAK8_mSDcut_minMasscut", "AK8 Filtered Jet Mass for 110<M_{Soft Drop}(GeV)<210 and minMass > 50 GeV;Mass (GeV)", 100, 0, 1000)
h_mtrimmedAK8_mSDcut_minMasscut = ROOT.TH1F("h_mtrimmedAK8_mSDcut_minMasscut", "AK8 Trimmed Jet Mass for 110<M_{Soft Drop}(GeV)<210 and minMass > 50 GeV;Mass (GeV)", 100, 0, 1000)
h_mSDropAK8_mSDcut_minMasscut = ROOT.TH1F("h_mSDropAK8_mSDcut_minMasscut", "AK8 Soft Drop Jet Mass for 110<M_{Soft Drop}(GeV)<210 and minMass > 50 GeV;Mass (GeV)", 100, 0, 1000)
h_minmassAK8_mSDcut_minMasscut = ROOT.TH1F("h_minmassAK8_mSDcut_minMasscut", "AK8 CMS Top Tagger Min Mass Paring for 110<M_{Soft Drop}(GeV)<210 and minMass > 50 GeV;m_{min} (GeV)", 100, 0, 1000)
h_subjetBdiscAK8_mSDcut_minMasscut = ROOT.TH1F("h_subjetBdiscAK8_mSDcut_minMasscut", "AK8 subjet b discriminator for 110<M_{Soft Drop}(GeV)<210 and minMass > 50 GeV;b discriminator", 100, 0, 1.0)
h_nsjAK8_mSDcut_minMasscut = ROOT.TH1F("h_nsjAK8_mSDcut_minMasscut", "AK8 CMS Top Tagger N_{subjets}for 110<M_{Soft Drop}(GeV)<210 and minMass > 50 GeV;N_{subjets}", 5, 0, 5)
h_tau21AK8_mSDcut_minMasscut = ROOT.TH1F("h_tau21AK8_mSDcut_minMasscut", "AK8 Jet #tau_{2} / #tau_{1} for 110<M_{Soft Drop}(GeV)<210 and minMass > 50 GeV;Mass#tau_{21}", 100, 0, 1.0)
h_tau32AK8_mSDcut_minMasscut = ROOT.TH1F("h_tau32AK8_mSDcut_minMasscut", "AK8 Jet #tau_{3} / #tau_{2} for 110<M_{Soft Drop}(GeV)<210 and minMass > 50 GeV;Mass#tau_{32}", 100, 0, 1.0)
 
#$ plots with min pairwise mass in the W mass window - 60 GeV < minpairwise < 110

h_ptLep_minMasscutWmass = ROOT.TH1F("h_ptLep_minMasscutWmass", "Lepton p_{T} for min Mass cut  60 GeV < minpairwise < 110;p_{T} (GeV)", 100, 0, 1000)
h_ptMu_minMasscutWmass = ROOT.TH1F("h_ptMu_minMasscutWmass", "Muon p_{T} for min Mass cut  60 GeV < minpairwise < 110;p_{T} (GeV)", 100, 0, 1000)
h_ptEl_minMasscutWmass = ROOT.TH1F("h_ptEl_minMasscutWmass", "Electron p_{T} for min Mass cut  60 GeV < minpairwise < 110;p_{T} (GeV)", 100, 0, 1000)

h_ptAK4_minMasscutWmass = ROOT.TH1F("h_ptAK4_minMasscutWmass", "AK4 Jet p_{T} for min Mass cut  60 GeV < minpairwise < 110;p_{T} (GeV)", 300, 0, 3000)
h_mAK4_minMasscutWmass = ROOT.TH1F("h_mAK4_minMasscutWmass", "AK4 Jet Massfor min Mass cut  60 GeV < minpairwise < 110;Mass (GeV)", 100, 0, 1000)
h_bdiscAK4_minMasscutWmass = ROOT.TH1F("h_bdiscAK4_minMasscutWmass", "AK4 b discriminatorfor min Mass cut  60 GeV < minpairwise < 110;b discriminator", 100, 0, 1.0)

h_ptAK8_minMasscutWmass = ROOT.TH1F("h_ptAK8_minMasscutWmass", "AK8 Jet p_{T}for min Mass cut  60 GeV < minpairwise < 110;p_{T} (GeV)", 300, 0, 3000)
h_etaAK8_minMasscutWmass = ROOT.TH1F("h_etaAK8_minMasscutWmass", "AK8 Jet #etafor minMass cut  60 GeV < minpairwise < 110;#eta", 120, -6, 6)
h_yAK8_minMasscutWmass = ROOT.TH1F("h_yAK8_minMasscutWmass", "AK8 Jet Rapidity for minMass cut  60 GeV < minpairwise < 110;y", 120, -6, 6)
h_phiAK8_minMasscutWmass = ROOT.TH1F("h_phiAK8_minMasscutWmass", "AK8 Jet #phi for minMass cut  60 GeV < minpairwise < 110;#phi (radians)",100,-3.14, 3.14)
h_mAK8_minMasscutWmass = ROOT.TH1F("h_mAK8_minMasscutWmass", "AK8 Jet Mass for min Mass cut  60 GeV < minpairwise < 110;Mass (GeV)", 100, 0, 1000)
h_mprunedAK8_minMasscutWmass = ROOT.TH1F("h_mprunedAK8_minMasscutWmass", "AK8 Pruned Jet Mass for min Mass cut  60 GeV < minpairwise < 110;Mass (GeV)", 100, 0, 1000)
h_mfilteredAK8_minMasscutWmass = ROOT.TH1F("h_mfilteredAK8_minMasscutWmass", "AK8 Filtered Jet Mass for min Mass cut  60 GeV < minpairwise < 110;Mass (GeV)", 100, 0, 1000)
h_mtrimmedAK8_minMasscutWmass = ROOT.TH1F("h_mtrimmedAK8_minMasscutWmass", "AK8 Trimmed Jet Mass for min Mass cut  60 GeV < minpairwise < 110;Mass (GeV)", 100, 0, 1000)
h_mSDropAK8_minMasscutWmass = ROOT.TH1F("h_mSDropAK8_minMasscutWmass", "AK8 Soft Drop Jet Mass for min Mass cut  60 GeV < minpairwise < 110;Mass (GeV)", 100, 0, 1000)
h_minmassAK8_minMasscutWmass = ROOT.TH1F("h_minmassAK8_minMasscutWmass", "AK8 CMS Top Tagger Min Mass Paring for min Mass cut  60 GeV < minpairwise < 110;m_{min} (GeV)", 100, 0, 1000)
h_subjetBdiscAK8_minMasscutWmass = ROOT.TH1F("h_subjetBdiscAK8_minMasscutWmass", "AK8 subjet b discriminator for min Mass cut  60 GeV < minpairwise < 110;b discriminator", 100, 0, 1.0)
h_nsjAK8_minMasscutWmass = ROOT.TH1F("h_nsjAK8_minMasscutWmass", "AK8 CMS Top Tagger N_{subjets}for min Mass cut  60 GeV < minpairwise < 110;N_{subjets}", 5, 0, 5)
h_tau21AK8_minMasscutWmass = ROOT.TH1F("h_tau21AK8_minMasscutWmass", "AK8 Jet #tau_{2} / #tau_{1} for min Mass cut  60 GeV < minpairwise < 110;Mass#tau_{21}", 100, 0, 1.0)
h_tau32AK8_minMasscutWmass = ROOT.TH1F("h_tau32AK8_minMasscutWmass", "AK8 Jet #tau_{3} / #tau_{2} for min Mass cut  60 GeV < minpairwise < 110;Mass#tau_{32}", 100, 0, 1.0)


#@ JET CORRECTIONS

ROOT.gSystem.Load('libCondFormatsJetMETObjects')
#jecParStrAK4 = ROOT.std.string('JECs/PHYS14_25_V2_AK4PFchs.txt')
#jecUncAK4 = ROOT.JetCorrectionUncertainty( jecParStrAK4 )
#jecParStrAK8 = ROOT.std.string('JECs/PHYS14_25_V2_AK8PFchs.txt')
#jecUncAK8 = ROOT.JetCorrectionUncertainty( jecParStrAK8 )

print 'Getting L3 for AK4'
L3JetParAK4  = ROOT.JetCorrectorParameters("JECs/PHYS14_25_V2_L3Absolute_AK4PFchs.txt");
print 'Getting L2 for AK4'
L2JetParAK4  = ROOT.JetCorrectorParameters("JECs/PHYS14_25_V2_L2Relative_AK4PFchs.txt");
print 'Getting L1 for AK4'
L1JetParAK4  = ROOT.JetCorrectorParameters("JECs/PHYS14_25_V2_L1FastJet_AK4PFchs.txt");
# for data only :
#ResJetParAK4 = ROOT.JetCorrectorParameters("JECs/PHYS14_25_V2_L2L3Residual_AK4PFchs.txt");

print 'Getting L3 for AK8'
L3JetParAK8  = ROOT.JetCorrectorParameters("JECs/PHYS14_25_V2_L3Absolute_AK8PFchs.txt");
print 'Getting L2 for AK8'
L2JetParAK8  = ROOT.JetCorrectorParameters("JECs/PHYS14_25_V2_L2Relative_AK8PFchs.txt");
print 'Getting L1 for AK8'
L1JetParAK8  = ROOT.JetCorrectorParameters("JECs/PHYS14_25_V2_L1FastJet_AK8PFchs.txt");
# for data only :
#ResJetParAK8 = ROOT.JetCorrectorParameters("JECs/PHYS14_25_V2_L2L3Residual_AK8PFchs.txt"); 


#  Load the JetCorrectorParameter objects into a vector, IMPORTANT: THE ORDER MATTERS HERE !!!! 
vParJecAK4 = ROOT.vector('JetCorrectorParameters')()
vParJecAK4.push_back(L1JetParAK4)
vParJecAK4.push_back(L2JetParAK4)
vParJecAK4.push_back(L3JetParAK4)
# for data only :
#vParJecAK4.push_back(ResJetPar)

ak4JetCorrector = ROOT.FactorizedJetCorrector(vParJecAK4)

vParJecAK8 = ROOT.vector('JetCorrectorParameters')()
vParJecAK8.push_back(L1JetParAK8)
vParJecAK8.push_back(L2JetParAK8)
vParJecAK8.push_back(L3JetParAK8)
# for data only :
#vParJecAK8.push_back(ResJetPar)

ak8JetCorrector = ROOT.FactorizedJetCorrector(vParJecAK8)


#@ EVENT LOOP

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

genSemiMuEvents = 0
genSemiEEvents = 0
genMuMuEvents = 0
genMuEEvents = 0
genEEEvents = 0
genHadEvents = 0


filelist = file( options.files )
filesraw = filelist.readlines()
files = []
nevents = 0
for ifile in filesraw : #{ Loop over text file and find root files linked
    if len( ifile ) > 2 : 
        #s = 'root://cmsxrootd.fnal.gov/' + ifile.rstrip()
        s = ifile.rstrip()
        files.append( s )
        print 'Added ' + s
        #} End loop over txt file

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



        #@ Generator information
        genEIndex = []
        genMuIndex = []
        gotGen = event.getByLabel( l_genPartPt, h_genPartPt )
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
                if options.verbose  and genName != None:
                    print '%10s : %6d %6d %7.2f %6.3f %6.3f %6.3f' % ( genName, genPartID[igen], genPartStatus[igen], genPartPt[igen], genPartEta[igen], genPartPhi[igen], genPartMass[igen] )

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

        #@ VERTEX SETS
        event.getByLabel( l_NPV, h_NPV )
        NPV = h_NPV.product()[0]
        if len(h_NPV.product()) == 0 :
            if options.verbose :
                print "Event has no good primary vertex."
            continue
            

        #@ RHO VALUE
        event.getByLabel( l_rho, h_rho )
        if len(h_rho.product()) == 0 :
            print "Event has no rho values."
            continue
        else:
            rho = h_rho.product()[0]
            if options.verbose :
                print 'rho = {0:6.2f}'.format( rho )

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

        #@ Muon Selection

        goodmuonPt = []
        goodmuonEta = []
        goodmuonPhi = []
        goodmuonMass = []
        goodmuonKey = []
        goodmuonCharge = []

        #Use MuPt as iterater due to no definite iterator value in ntuples
        if len(h_muPt.product()) > 0:
            muonPt = h_muPt.product()
            muonEta = h_muEta.product()
            muonPhi = h_muPhi.product()
            muonTight = h_muTight.product()
            muonLoose = h_muLoose.product()
            muonMass = h_muMass.product()
            muonDz = h_muDz.product()
            muKey = h_muKey.product()
            muCharge = h_muCharge.product()
            for imuon, muon in enumerate(muonPt): #{ Loop over all muons in event
                NMu = NMu + 1
                if muonPt[imuon] < options.minMuonPt :  #$ Muon cuts
                    continue
                else: 
                    NPassMuonPtCut = NPassMuonPtCut + 1
                    #$ muon pt cuts here
                    h_ptLep_ptMucut.Fill(muonPt[imuon])
                    h_ptMu_ptMucut.Fill(muonPt[imuon])
                if abs(muonEta[imuon]) > options.maxMuonEta :
                    continue
                else:
                    NPassMuonEtaCut = NPassMuonEtaCut + 1
                if muonDz[imuon] > 5.0:
                    continue
                else:
                    NPassMuonDzCut = NPassMuonDzCut + 1
                if muonTight[imuon] == 0 :
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
                if options.verbose : 
                    print "muon %2d: keys " %(imuon)
                    for ikey in muKey[imuon] : 
                        print   " %4d" % ( ikey ),
                    print "     ---> pt %4.1f, eta %+5.3f phi %+5.3f dz(PV) %+5.3f, POG loose id %d, tight id %d." %  \
                        ( muonPt[imuon], muonEta[imuon],muonPhi[imuon], muonDz[imuon], muonLoose[imuon], muonTight[imuon])

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

                    if iePt > options.minElectronPt:
                        NPassElPtCut = NPassElPtCut + 1
                        #$ electron pt cuts here 
                        h_ptLep_ptElcut.Fill(iePt)
                        h_ptEl_ptElcut.Fill(iePt)
                    else:
                        continue
                    if abs(ieEta) < options.maxElectronEta : #$ Electron eta cut (based on options)
                        NPassElEtaCut = NPassElEtaCut + 1
                    else:
                        continue
                    goodElectron = False #$ Electron ID Cut (current WP Loose : https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2 )
                    if abs( ieEta ) <= 1.479 :
                        if abs(iedEtaIn) < 0.009277 :
                            NPassEldEtaIn+=1
                        else :
                            continue
                        if abs(iedPhiIn ) < 0.094739 :
                            NPassEldPhiIn+=1
                        else :
                            continue
                        if ie5x5sigma < 0.010331 :
                            NPassEl5x5+= 1
                        else :
                            continue
                        if ieHoE <  0.093068 :
                            NPassElHoE+= 1
                        else :
                            continue
                        if abs(ieD0) <  0.035904 :
                            NPassElD0+=1
                        else :
                            continue
                        if abs(ieDz) <  0.075496 :
                            NPassElDz+=1
                        else :
                            continue
                        if ieEmooP <  0.189968 :
                            NPassElEmooP+=1
                            goodElectron = True
                        else :
                            continue
                    else :
                        if abs(iedEtaIn) < 0.009833 :
                            NPassEldEtaIn+=1
                        else :
                            continue
                        if abs(iedPhiIn ) < 0.149934 :
                            NPassEldPhiIn+=1
                        else :
                            continue 
                        if ie5x5sigma < 0.031838 :
                            NPassEl5x5+= 1
                        else :
                            continue
                        if ieHoE <  0.115754 :
                            NPassElHoE+= 1
                        else :
                            continue
                        if abs(ieD0) <  0.099266 :
                            NPassElD0+=1
                        else :
                            continue
                        if abs(ieDz) <  0.197897 :
                            NPassElDz+=1
                        else :
                            continue
                        if ieEmooP <  0.140662 :
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
                        if options.verbose : 
                            print "elec %2d: keys " %(ielectron)
                            for ikey in elKey[ielectron] : 
                                print   " %4d" % ( ikey ),
                            print "     ---> , pt %4.1f, eta %4.1f, phi %+5.3f " % ( electronPt[ielectron], electronEta[ielectron], electronPhi[ielectron] )
                    
                    #} End Electron Loop


        #^ define the type of decay channel based on number of leptons in event
        # Skip if not any of these

        #@ Channel Definition
        
        Hadronic = (len(goodmuonPt) + len(goodelectronPt)) == 0
        Leptonic = (len(goodmuonPt) + len(goodelectronPt)) == 2 
        SemiLeptonic = (len(goodmuonPt) + len(goodelectronPt)) == 1         

        if options.verbose :
            print 'Number of good muons = ' + str( len(goodmuonPt) )
            print 'Number of good electrons = ' + str( len(goodelectronPt) )


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
        if options.selection == 0 and not Leptonic :
            continue
        elif options.selection == 1 and not SemiLeptonic :
            continue
        elif options.selection == 2 and not Hadronic :
            continue
        
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
        if SemiLeptonic : 

            if len(goodmuonPt) > 0 :
                muJets = True
                theLepton = ROOT.TLorentzVector()
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

            else :
                eleJets = True
                theLepton = ROOT.TLorentzVector()
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

            if options.verbose :
                print '-----'
                print 'jet index = %2d, nhf = %6.2f, nef = %6.2f, chf = %6.2f, cef = %6.2f, nconstituents = %3d, nch = %3d' % (i, nhf, nef, chf, cef, nconstituents, nch)
                print '   keys : ', 
                for j in range( 0, len(AK4Keys[i]) ) :
                    print ' %d' % ( AK4Keys[i][j] ),
                print ''
            if not goodJet :
                if options.verbose : 
                    print '   bad jet pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}'.format (
                        jetP4Raw.Perp(), jetP4Raw.Rapidity(), jetP4Raw.Phi(), jetP4Raw.M()
                        )
                continue
            NPassGoodJetAK4Cut = NPassGoodJetAK4Cut + 1
            if options.verbose :
                print '   raw jet pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}'.format (
                    jetP4Raw.Perp(), jetP4Raw.Rapidity(), jetP4Raw.Phi(), jetP4Raw.M()
                    )

            #Subtract the lepton 4-Vectors from the jets neighboring it
            cleaned = False
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
                            jetP4Raw -= Lepton2
                            cleaned = True
                            break
                        #} End loop over jet keys
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
                if options.verbose :
                   print '   jet failed kinematic cuts'
                continue
            if abs(jetP4.Rapidity()) < options.maxAK4Rapidity:                  
                NPassMaxAK4RapidityCut = NPassMaxAK4RapidityCut + 1
            else:
                if options.verbose :
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
            if options.verbose :
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

        #Get MET HERE
        event.getByLabel ( l_metPt, h_metPt )
        event.getByLabel ( l_metPx, h_metPx )
        event.getByLabel ( l_metPy, h_metPy )
        event.getByLabel ( l_metPhi, h_metPhi )

        metPx = h_metPx.product()[0]
        metPy = h_metPy.product()[0]
        metPhi = h_metPhi.product()[0]
        metPt = h_metPt.product()[0]
        
        #^ Plotting for SemiLeptonic Channel pre 2D cuts
        if SemiLeptonic : 
            theLepJet = nearestJetP4
            theLepJetBDisc = nearestJetbDiscrim
            if eleJets :
                theElJet = nearestJetP4
                theElJetBDisc = nearestJetbDiscrim   
                h_ptAK4.Fill( theElJet.Perp() )
                h_etaAK4.Fill( theElJet.Eta() )
                h_yAK4.Fill( theElJet.Rapidity() )
                h_mAK4.Fill( theElJet.M() )
                h_bdiscAK4.Fill( theElJetBDisc )
                ptRel = theElJet.Perp( theElectron.Vect() ) 
                h_ptEl.Fill(theElectron.Perp())     
                h_ptLep.Fill(theElectron.Perp())
                h_etaLep.Fill(theElectron.Eta())  
            elif muJets :
                theMuJet = nearestJetP4
                theMuJetBDisc = nearestJetbDiscrim
                h_ptAK4.Fill( theMuJet.Perp() )
                h_etaAK4.Fill( theMuJet.Eta() )
                h_yAK4.Fill( theMuJet.Rapidity() )
                h_mAK4.Fill( theMuJet.M() )
                h_bdiscAK4.Fill( theMuJetBDisc )
                ptRel = theMuJet.Perp( theMuon.Vect() )
                h_ptMu.Fill(theMuon.Perp())
                h_ptLep.Fill(theMuon.Perp())
                h_etaLep.Fill(theMuon.Eta())
            h_met.Fill(metPt)
            h_ptRel.Fill( ptRel )
            h_dRMin.Fill( dRMin )
            h_2DCut.Fill( dRMin, ptRel )

            
            #@ 2D Cuts
            pass2D = ptRel > 20.0 or dRMin > 0.4
            if options.verbose :
                print '>>>>>>>>>>>>>>'
                print '2d cut : dRMin = {0:6.2f}, ptRel = {1:6.2f}'.format( dRMin, ptRel )
                print '>>>>>>>>>>>>>>'
            if pass2D == False :
                continue
            else:
                NPass2DCut += 1
                if muJets :
                   NPassMuon2DCut += 1
                elif eleJets :
                   NPassEl2DCut += 1
        #^ Plotting for DiLeptonic Channel pre 2D cuts
        elif Leptonic :
            #theLepJet = nearestJetP4
            #theLepJetBDisc = nearestJetbDiscrim
            if dielectronCandidate:
                theElJet = nearestJetP4
                theElJetBDisc = nearestJetbDiscrim   
                h_ptAK4.Fill( theElJet.Perp() )
                h_etaAK4.Fill( theElJet.Eta() )
                h_yAK4.Fill( theElJet.Rapidity() )
                h_mAK4.Fill( theElJet.M() )
                h_bdiscAK4.Fill( theElJetBDisc )
                ptRel = theElJet.Perp( Electron1.Vect() ) 
                h_ptEl.Fill(Electron1.Perp())     
                h_ptLep.Fill(Electron1.Perp())
                h_etaLep.Fill(Electron1.Eta())  
            elif dimuonCandidate or mixedCandidate:
                theMuJet = nearestJetP4
                theMuJetBDisc = nearestJetbDiscrim
                h_ptAK4.Fill( theMuJet.Perp() )
                h_etaAK4.Fill( theMuJet.Eta() )
                h_yAK4.Fill( theMuJet.Rapidity() )
                h_mAK4.Fill( theMuJet.M() )
                h_bdiscAK4.Fill( theMuJetBDisc )
                ptRel = theMuJet.Perp( Muon1.Vect() )
                h_ptMu.Fill(Muon1.Perp())
                h_ptLep.Fill(Muon1.Perp())
                h_etaLep.Fill(Muon1.Eta())
            h_met.Fill(metPt)
            h_ptRel.Fill( ptRel )
            h_dRMin.Fill( dRMin )
            h_2DCut.Fill( dRMin, ptRel )
            
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

            #theLepJet2 = nearest2JetP4
            #theLepJetBDisc2 = nearest2JetbDiscrim
            if dielectronCandidate or mixedCandidate: 
                theElJet2 = nearestJetP4
                theElJetBDisc2 = nearestJetbDiscrim   
                h_ptAK4.Fill( theElJet2.Perp() )
                h_etaAK4.Fill( theElJet2.Eta() )
                h_yAK4.Fill( theElJet2.Rapidity() )
                h_mAK4.Fill( theElJet2.M() )
                h_bdiscAK4.Fill( theElJetBDisc2 )
                ptRel = theElJet.Perp( Electron2.Vect() ) 
                h_ptEl.Fill(Electron2.Perp())     
                h_ptLep.Fill(Electron2.Perp())
                h_etaLep.Fill(Electron2.Eta())  
            elif dimuonCandidate:
                theMuJet2 = nearestJetP4
                theMuJetBDisc2 = nearestJetbDiscrim
                h_ptAK4.Fill( theMuJet2.Perp() )
                h_etaAK4.Fill( theMuJet2.Eta() )
                h_yAK4.Fill( theMuJet2.Rapidity() )
                h_mAK4.Fill( theMuJet2.M() )
                h_bdiscAK4.Fill( theMuJetBDisc2 )
                ptRel2 = theMuJet.Perp( Muon2.Vect() )
                h_ptMu.Fill(Muon2.Perp())
                h_ptLep.Fill(Muon2.Perp())
                h_etaLep.Fill(Muon2.Eta())
            h_met.Fill(metPt)
            h_ptRel.Fill( ptRel )
            h_dRMin.Fill( dR2Min )
            h_2DCut.Fill( dR2Min, ptRel )
            
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
            event.getByLabel ( l_jetsAK8Eta, h_jetsAK8Eta )
            event.getByLabel ( l_jetsAK8Pt, h_jetsAK8Pt )
            event.getByLabel ( l_jetsAK8Phi, h_jetsAK8Phi )
            event.getByLabel ( l_jetsAK8Mass, h_jetsAK8Mass )
            event.getByLabel ( l_jetsAK8Energy, h_jetsAK8Energy )
            event.getByLabel ( l_jetsAK8JEC, h_jetsAK8JEC )
            event.getByLabel ( l_jetsAK8Y, h_jetsAK8Y )
            event.getByLabel ( l_jetsAK8Area, h_jetsAK8Area )

            event.getByLabel ( l_jetsAK8TrimMass, h_jetsAK8TrimMass )
            event.getByLabel ( l_jetsAK8PrunMass, h_jetsAK8PrunMass )
            event.getByLabel ( l_jetsAK8FiltMass, h_jetsAK8FiltMass )
            event.getByLabel ( l_jetsAK8SoftDropMass, h_jetsAK8SoftDropMass )
            event.getByLabel ( l_jetsAK8Tau1, h_jetsAK8Tau1 )
            event.getByLabel ( l_jetsAK8Tau2, h_jetsAK8Tau2 )
            event.getByLabel ( l_jetsAK8Tau3, h_jetsAK8Tau3 )
            event.getByLabel ( l_jetsAK8nSubJets, h_jetsAK8nSubJets )
            event.getByLabel ( l_jetsAK8minmass, h_jetsAK8minmass )
            event.getByLabel ( l_subjetsAK8BDisc, h_subjetsAK8BDisc )


            event.getByLabel ( l_jetsAK8nHadEnergy, h_jetsAK8nHadEnergy)
            event.getByLabel ( l_jetsAK8nEMEnergy, h_jetsAK8nEMEnergy )
            event.getByLabel ( l_jetsAK8cHadEnergy, h_jetsAK8cHadEnergy )
            event.getByLabel ( l_jetsAK8HFHadronEnergy, h_jetsAK8HFHadronEnergy )
            event.getByLabel ( l_jetsAK8cEMEnergy, h_jetsAK8cEMEnergy )
            event.getByLabel ( l_jetsAK8numDaughters, h_jetsAK8numDaughters )
            event.getByLabel ( l_jetsAK8cMultip, h_jetsAK8cMultip )
            event.getByLabel ( l_jetsAK8Y, h_jetsAK8Y )

            event.getByLabel ( l_jetsAK8Keys, h_jetsAK8Keys )

            
            event.getByLabel ( l_jetsAK8TopSubjetIndex0, h_jetsAK8TopSubjetIndex0 )
            event.getByLabel ( l_jetsAK8TopSubjetIndex1, h_jetsAK8TopSubjetIndex1 )
            event.getByLabel ( l_jetsAK8TopSubjetIndex2, h_jetsAK8TopSubjetIndex2 )
            event.getByLabel ( l_jetsAK8TopSubjetIndex3, h_jetsAK8TopSubjetIndex3 )

            event.getByLabel ( l_subjetsAK8BDisc, h_subjetsAK8BDisc)
            event.getByLabel ( l_subjetsAK8Pt, h_subjetsAK8Pt)
            event.getByLabel ( l_subjetsAK8Eta, h_subjetsAK8Eta)
            event.getByLabel ( l_subjetsAK8Phi, h_subjetsAK8Phi)

            if options.deweightFlat : 
                # Event weights
                gotGenerator = event.getByLabel( l_generator, h_generator )
            
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
            ak8JetsGoodSubjetbDisc = []
            ak8JetsGoodTopSubjetIndex0 = []
            ak8JetsGoodTopSubjetIndex1 = []
            ak8JetsGoodTopSubjetIndex2 = []
            ak8JetsGoodTopSubjetIndex3 = []            
            

            if len( h_jetsAK8Pt.product()) > 0 : 
                AK8Pt = h_jetsAK8Pt.product()
                AK8Eta = h_jetsAK8Eta.product()
                AK8Phi = h_jetsAK8Phi.product()
                AK8Mass = h_jetsAK8Mass.product()
                AK8Energy = h_jetsAK8Energy.product()
                AK8Y = h_jetsAK8Y.product()

                AK8JEC = h_jetsAK8JEC.product()
                AK8Area = h_jetsAK8Area.product()

                AK8nHadE = h_jetsAK8nHadEnergy.product()
                AK8nEME = h_jetsAK8nEMEnergy.product()
                AK8cHadE =  h_jetsAK8cHadEnergy.product()
                AK8HFHadE = h_jetsAK8HFHadronEnergy.product()
                AK8cEME =  h_jetsAK8cEMEnergy.product()
                AK8numDaughters = h_jetsAK8numDaughters.product()
                AK8cMultip =  h_jetsAK8cMultip.product()
                AK8Y =  h_jetsAK8Y.product()

                AK8TrimmedM = h_jetsAK8TrimMass.product()
                AK8PrunedM = h_jetsAK8PrunMass.product()
                AK8FilteredM = h_jetsAK8FiltMass.product()
                AK8SDropM = h_jetsAK8SoftDropMass.product()
                AK8Tau1 = h_jetsAK8Tau1.product()
                AK8Tau2 = h_jetsAK8Tau2.product()
                AK8Tau3 = h_jetsAK8Tau3.product()
                AK8nSubJets = h_jetsAK8nSubJets.product()
                AK8minmass = h_jetsAK8minmass.product()
                AK8SubjetbDisc = subjetsAK8BDisc.product()
                AK8TopSubjetIndex0 = h_jetsAK8TopSubjetIndex0.product()
                AK8TopSubjetIndex1 = h_jetsAK8TopSubjetIndex1.product()
                AK8TopSubjetIndex2 = h_jetsAK8TopSubjetIndex2.product()
                AK8TopSubjetIndex3 = h_jetsAK8TopSubjetIndex3.product()
                if options.deweightFlat :
                    pthat = 0.0
                    if h_generator.product().hasBinningValues() :
                        pthat = h_generator.product().binningValues()[0]
                        evWeight = 1/pow(pthat/15.,4.5)
 
                
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

                    if not goodJet :
                        if options.verbose : 
                            print '   bad jet pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}'.format (
                                AK8P4Raw.Perp(), AK8P4Raw.Rapidity(), AK8P4Raw.Phi(), AK8P4Raw.M()
                                )
                        continue
                    NPassGoodJetAK8Cut = NPassGoodJetAK8Cut + 1
                    if options.verbose :
                        print '   raw jet pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}'.format (
                            AK8P4Raw.Perp(), AK8P4Raw.Rapidity(), AK8P4Raw.Phi(), AK8P4Raw.M()
                            )

                    #@ JEC Scaling for AK8 Jets
                    ak8JetCorrector.setJetEta( AK8P4Raw.Eta() )
                    ak8JetCorrector.setJetPt ( AK8P4Raw.Perp() )
                    ak8JetCorrector.setJetE  ( AK8P4Raw.E() )
                    ak8JetCorrector.setJetA  ( AK8Area[i] )
                    ak8JetCorrector.setRho   ( rho )
                    ak8JetCorrector.setNPV   ( NPV )
                    newJEC = ak8JetCorrector.getCorrection()
                    AK8P4Corr = AK8P4Raw*newJEC



                    #$ Cuts based on pt and rapidity
                    if AK8P4Raw.Perp() < options.minAK8Pt or abs(AK8P4Raw.Rapidity()) > options.maxAK8Rapidity :
                        continue
                    if AK8P4Raw.Perp() > options.minAK8Pt:
                        NPassMinRawAK8PtCut = NPassMinRawAK8PtCut + 1
                    if abs(AK8P4Raw.Rapidity()) < options.maxAK8Rapidity :
                        NPassMaxAK8RapidityCut = NPassMaxAK8RapidityCut + 1
                    # SemiLeptonic- Only keep AK8 jets "away" from the lepton, so we do not need lepton-jet cleaning here. There's no double counting. 
                    # Leptonic - No fat jets                                                                          
                    # Hadronic - 2 AK8's, no massy leptons to clean up after

                    #$ Cuts for fat jets that are far away from the leptons
                    if SemiLeptonic :
                        if eleJets :
                            dR = jetP4.DeltaR(theElectron ) 
                        elif muJets :
                            dR = jetP4.DeltaR(theMuon )  
                        if dR > ROOT.TMath.Pi()/2.0 :
                            NPassSemiLeptonicDRjlCut = NPassSemiLeptonicDRjlCut + 1
                            ak8JetsGood.append(AK8P4Corr)
                            ak8JetsGoodTrimMass.append( AK8TrimmedM[i])
                            ak8JetsGoodPrunMass.append( AK8PrunedM[i])
                            ak8JetsGoodFiltMass.append( AK8FilteredM[i])
                            ak8JetsGoodSDropMass.append( AK8SDropM[i])
                            ak8JetsGoodTau1.append( AK8Tau1[i])
                            ak8JetsGoodTau2.append( AK8Tau2[i])
                            ak8JetsGoodTau3.append( AK8Tau3[i])
                            ak8JetsGoodNSubJets.append( AK8nSubJets[i])
                            ak8JetsGoodMinMass.append( AK8minmass[i] )
                            ak8JetsGoodSubjetbDisc.append( AK8SubjetbDisc[i] )
                            ak8JetsGoodTopSubjetIndex0.append( AK8TopSubjetIndex0[i] )
                            ak8JetsGoodTopSubjetIndex1.append( AK8TopSubjetIndex1[i] )
                            ak8JetsGoodTopSubjetIndex2.append( AK8TopSubjetIndex2[i] )
                            ak8JetsGoodTopSubjetIndex3.append( AK8TopSubjetIndex3[i] )
                    #$ Cuts for Hadronic channel
                    else : 
                        ## HADRONIC CHANNEL CRITERIA 

                        # - minimum mass pairing > 50 GeV
                        # - number of Subjets >= 3
                        # - Jet Mass > 100 GeV
                        if AK8nSubJets[i] >= 3:
                            NPassAK8nSubJetsCut = NPassAK8nSubJetsCut + 1
                        else:
                            continue
                        if AK8minmass[i] > 50:
                            NPassAK8MinMassCut = NPassAK8MinMassCut + 1
                        else:
                            continue
                        if AK8P4Corr.M() > 100:
                            NPassAK8CorrMassCut = NPassAK8CorrMassCut + 1
                        else:
                            continue
                        ak8JetsGood.append(AK8P4Corr)
                        ak8JetsGoodTrimMass.append( AK8TrimmedM[i])
                        ak8JetsGoodPrunMass.append( AK8PrunedM[i])
                        ak8JetsGoodFiltMass.append( AK8FilteredM[i])
                        ak8JetsGoodSDropMass.append( AK8SDropM[i])
                        ak8JetsGoodTau1.append( AK8Tau1[i])
                        ak8JetsGoodTau2.append( AK8Tau2[i])
                        ak8JetsGoodTau3.append( AK8Tau3[i])
                        ak8JetsGoodNSubJets.append( AK8nSubJets[i])
                        ak8JetsGoodMinMass.append( AK8minmass[i] )
                        ak8JetsGoodSubjetbDisc.append( AK8SubjetbDisc[i] )
                        ak8JetsGoodTopSubjetIndex0.append( AK8TopSubjetIndex0[i] )
                        ak8JetsGoodTopSubjetIndex1.append( AK8TopSubjetIndex1[i] )
                        ak8JetsGoodTopSubjetIndex2.append( AK8TopSubjetIndex2[i] )
                        ak8JetsGoodTopSubjetIndex3.append( AK8TopSubjetIndex3[i] )                        
                        #} End AK8 Loop

            #@ Tagging
            if len(ak8JetsGood) < 1 :
                if options.verbose :
                    print 'Not enough AK8 jets, skipping'
                continue

            nttags = 0
            tJets = []

            for i in range(0,len(ak8JetsGood)):#{ Loop over Fat jets that passed cuts for t tagging
                if ak8JetsGood[i].Perp() < options.minAK8Pt : #$ Pt cut for passed jets
                    continue
                NPassminAK8PtCut = NPassminAK8PtCut + 1
                if evWeight != -1 :
                    FlatWeight = evWeight
                else :
                    FlatWeight = 1

                mAK8Pruned = AK8PrunedM[i] 
                mAK8Filtered = AK8FilteredM[i] 
                mAK8Trimmed = AK8TrimmedM[i]
                mAK8SDrop = AK8SDropM[i]
                # Make sure there are top tags if we want to plot them
                minMass = AK8minmass[i]
                subjetBdisc = AK8SubjetbDisc[i]
                nsubjets = AK8nSubJets[i]
                tau1 = AK8Tau1[i]  
                tau2 = AK8Tau2[i] 
                tau3 = AK8Tau3[i]
                #^ Plot Taus
                if tau1 > 0.0001 :
                    tau21 = tau2 / tau1
                    h_tau21AK8.Fill( tau21, FlatWeight )
                else :
                    h_tau21AK8.Fill( -1.0, FlatWeight )
                if tau2 > 0.0001 :
                    tau32 = tau3 / tau2
                    h_tau32AK8.Fill( tau32, FlatWeight )
                else :
                    h_tau32AK8.Fill( -1.0, FlatWeight )
                
                #^ Plot Kinematics for AK8 Jets, using only those with soft drop mass > 10 GeV
                if mAK8SDrop > 10:
                    h_ptAK8.Fill( ak8JetsGood[i].Perp(), FlatWeight )
                    h_etaAK8.Fill( ak8JetsGood[i].Eta(), FlatWeight )
                    h_phiAK8.Fill( ak8JetsGood[i].Phi(), FlatWeight )
                    h_yAK8.Fill( ak8JetsGood[i].Rapidity(), FlatWeight )
                    h_mAK8.Fill( ak8JetsGood[i].M(), FlatWeight )
                    h_mprunedAK8.Fill( ak8JetsGoodPrunMass[i], FlatWeight )
                    h_mfilteredAK8.Fill( ak8JetsGoodFiltMass[i], FlatWeight )
                    h_mtrimmedAK8.Fill( ak8JetsGoodTrimMass[i], FlatWeight )
                    h_mSDropAK8.Fill( ak8JetsGoodSDropMass[i], FlatWeight )
                    h_minmassAK8.Fill( ak8JetsGoodMinMass[i], FlatWeight )
                    h_subjetBdiscAK8.Fill( ak8JetsGoodSubjetbDisc[i], FlatWeight )
                    h_nsjAK8.Fill( ak8JetsGoodNSubJets[i], FlatWeight )
                if options.verbose : 
                    print 'minMass = {0:6.2f}, Groomed mass = {1:6.2f}, tau32 = {2:6.2f}'.format(
                        minMass, mAK8SDrop, tau32
                        ),
                if minMass > options.minMassCut:
                    #^ fill histos with min mass pairing greater than min mass cut 
                    NPasstMinMassCut = NPasstMinMassCut + 1
                    h_tau32AK8_minMasscut.Fill( tau32, FlatWeight )
                    h_tau21AK8_minMasscut.Fill( tau21, FlatWeight )
                    h_ptAK8_minMasscut.Fill( ak8JetsGood[i].Perp(), FlatWeight )
                    h_etaAK8_minMasscut.Fill( ak8JetsGood[i].Eta(), FlatWeight )
                    h_phiAK8_minMasscut.Fill( ak8JetsGood[i].Phi(), FlatWeight )
                    h_yAK8_minMasscut.Fill( ak8JetsGood[i].Rapidity(), FlatWeight )
                    h_mAK8_minMasscut.Fill( ak8JetsGood[i].M(), FlatWeight )
                    h_mprunedAK8_minMasscut.Fill( ak8JetsGoodPrunMass[i], FlatWeight )
                    h_mfilteredAK8_minMasscut.Fill( ak8JetsGoodFiltMass[i], FlatWeight )
                    h_mtrimmedAK8_minMasscut.Fill( ak8JetsGoodTrimMass[i], FlatWeight )
                    h_mSDropAK8_minMasscut.Fill( ak8JetsGoodSDropMass[i], FlatWeight )
                    h_minmassAK8_minMasscut.Fill( ak8JetsGoodMinMass[i], FlatWeight )
                    h_subjetBdiscAK8_minMasscut.Fill( ak8JetsGoodSubjetbDisc[i], FlatWeight )
                    h_nsjAK8_minMasscut.Fill( ak8JetsGoodNSubJets[i], FlatWeight )
                else:
                    continue
                if mAK8SDrop > options.mAK8GroomedMinCut:
                    NPasstMAK8GroomedMinCut = NPasstMAK8GroomedMinCut + 1
                else:
                    continue
                if mAK8SDrop < options.mAK8GroomedMaxCut:
                    NPasstMAK8GroomedMaxCut = NPasstMAK8GroomedMaxCut + 1
                else: 
                    continue
                if mAK8SDrop < options.mAK8GroomedMaxCut and mAK8SDrop > options.mAK8GroomedMinCut: 
 # @@@ fix this and all below fills of cut histos, more lepton and AK4 stuff to other loops
                   #^ Fill histos between min and max soft drop mass cuts
                    h_tau32AK8_mSDcut.Fill( tau32, FlatWeight )
                    h_tau21AK8_mSDcut.Fill( tau21, FlatWeight )

# @@@ add subjet bdisc fill to all below plots

#                    h_ptLep_mSDcut.Fill(theLepton.Perp())   @@@ fix this
# $$$               if theLepton == Mu :
#  h_ptMu_mSDcut.Fill(theLepton.Perp())
# $$$               if theLepton == El :
#  h_ptEl_mSDcut.Fill(theLepton.Perp())
#                    h_ptAK4_mSDcut.Fill( theLepJet.Perp() )
#                    h_mAK4_mSDcut.Fill( theLepJet.M() )
#                    h_bdiscAK4_mSDcut.Fill( theLepJetBDisc )


                    h_ptAK8_mSDcut.Fill( ak8JetsGood[i].Perp(), FlatWeight )
                    h_etaAK8_mSDcut.Fill( ak8JetsGood[i].Eta(), FlatWeight )
                    h_yAK8_mSDcut.Fill( ak8JetsGood[i].Rapidity(), FlatWeight )
                    h_mAK8_mSDcut.Fill( ak8JetsGood[i].M(), FlatWeight )
                    h_mprunedAK8_mSDcut.Fill( ak8JetsGoodPrunMass[i], FlatWeight )
                    h_mfilteredAK8_mSDcut.Fill( ak8JetsGoodFiltMass[i], FlatWeight )
                    h_mtrimmedAK8_mSDcut.Fill( ak8JetsGoodTrimMass[i], FlatWeight )
                    h_mSDropAK8_mSDcut.Fill( ak8JetsGoodSDropMass[i], FlatWeight )
                    h_minmassAK8_mSDcut.Fill( ak8JetsGoodMinMass[i], FlatWeight )
                    h_subjetBdiscAK8_mSDcut.Fill( ak8JetsGoodSubjetbDisc[i], FlatWeight )
                    h_nsjAK8_mSDcut.Fill( ak8JetsGoodNSubJets[i], FlatWeight )
                else: 
                    continue
                if tau32 < options.tau32Cut:
                    NPasstau23Cut = NPasstau23Cut + 1
                    #^ fill histos with tau32 < max tau32
                    h_tau21AK8_tau32cut.Fill( tau21, FlatWeight )

#                    h_ptLep_tau32cut.Fill(theLepton.Perp())  @@@ Fix this
# $$$ if muJets :
 #                   h_ptMu_tau32cut.Fill(theLepton.Perp())
# $$$ if eleJets :
 #                   h_ptEl_tau32cut.Fill(theLepton.Perp())
#                    h_ptAK4_tau32cut.Fill( theLepJet.Perp() )
#                    h_mAK4_tau32cut.Fill( theLepJet.M() )
#                    h_bdiscAK4_tau32cut.Fill( theLepJetBDisc )

                    h_ptAK8_tau32cut.Fill( ak8JetsGood[i].Perp(), FlatWeight )
                    h_etaAK8_tau32cut.Fill( ak8JetsGood[i].Eta(), FlatWeight )
                    h_yAK8_tau32cut.Fill( ak8JetsGood[i].Rapidity(), FlatWeight )
                    h_mAK8_tau32cut.Fill( ak8JetsGood[i].M(), FlatWeight )
                    h_mprunedAK8_tau32cut.Fill( ak8JetsGoodPrunMass[i], FlatWeight )
                    h_mfilteredAK8_tau32cut.Fill( ak8JetsGoodFiltMass[i], FlatWeight )
                    h_mtrimmedAK8_tau32cut.Fill( ak8JetsGoodTrimMass[i], FlatWeight )
                    h_mSDropAK8_tau32cut.Fill( ak8JetsGoodSDropMass[i], FlatWeight )
                    h_minmassAK8_tau32cut.Fill( ak8JetsGoodMinMass[i], FlatWeight )
                    h_nsjAK8_tau32cut.Fill( ak8JetsGoodNSubJets[i], FlatWeight )

                else: 
                    continue
                if mAK8SDrop < options.mAK8GroomedMaxCut and mAK8SDrop > options.mAK8GroomedMinCut and tau32 < options.tau32Cut: 
                    #^ Fill histos with 110 < M_{jet Soft Drop} GeV < 210 (can change default min and max groomed mass cuts in options)
                    h_tau32AK8_mSDcut_tau32cut.Fill( tau32, FlatWeight )
                    h_tau21AK8_mSDcut_tau32cut.Fill( tau21, FlatWeight )

#                    h_ptLep_mSDcut_tau32cut.Fill(theLepton.Perp())    @@@ Fix this
#                   if muJets :
#                    h_ptMu_mSDcut_tau32cut.Fill(theLepton.Perp())
#                   if eleJets :
#                    h_ptEl_mSDcut_tau32cut.Fill(theLepton.Perp())
#                    h_ptAK4_mSDcut_tau32cut.Fill( theLepJet.Perp() )
#                    h_mAK4_mSDcut_tau32cut.Fill( theLepJet.M() )
#                    h_bdiscAK4_mSDcut_tau32cut.Fill( theLepJetBDisc )

                    h_ptAK8_mSDcut_tau32cut.Fill( ak8JetsGood[i].Perp(), FlatWeight )
                    h_etaAK8_mSDcut_tau32cut.Fill( ak8JetsGood[i].Eta(), FlatWeight )
                    h_yAK8_mSDcut_tau32cut.Fill( ak8JetsGood[i].Rapidity(), FlatWeight )
                    h_mAK8_mSDcut_tau32cut.Fill( ak8JetsGood[i].M(), FlatWeight )
                    h_mprunedAK8_mSDcut_tau32cut.Fill( ak8JetsGoodPrunMass[i], FlatWeight )
                    h_mfilteredAK8_mSDcut_tau32cut.Fill( ak8JetsGoodFiltMass[i], FlatWeight )
                    h_mtrimmedAK8_mSDcut_tau32cut.Fill( ak8JetsGoodTrimMass[i], FlatWeight )
                    h_mSDropAK8_mSDcut_tau32cut.Fill( ak8JetsGoodSDropMass[i], FlatWeight )
                    h_minmassAK8_mSDcut_tau32cut.Fill( ak8JetsGoodMinMass[i], FlatWeight )
                    h_nsjAK8_mSDcut_tau32cut.Fill( ak8JetsGoodNSubJets[i], FlatWeight )
                else: 
                    continue
                if tau21 < options.tau21Cut:
                    NPasstau21Cut = NPasstau21Cut + 1
                    #^ fill histos with tau21 cuts
                    h_tau32AK8_tau21cut.Fill( tau32, FlatWeight )

#                    h_ptLep_tau21cut.Fill(theLepton.Perp())
#                   if theLepton == Mu :                                                  @@@ Fix this
#                    h_ptMu_tau21cut.Fill(theLepton.Perp())
#                   if theLepton == El :
#                    h_ptEl_tau21cut.Fill(theLepton.Perp())
#                    h_ptAK4_tau21cut.Fill( theLepJet.Perp() )
#                    h_mAK4_tau21cut.Fill( theLepJet.M() )
#                    h_bdiscAK4_tau21cut.Fill( theLepJetBDisc )

                    h_ptAK8_tau21cut.Fill( ak8JetsGood[i].Perp(), FlatWeight )
                    h_etaAK8_tau21cut.Fill( ak8JetsGood[i].Eta(), FlatWeight )
                    h_yAK8_tau21cut.Fill( ak8JetsGood[i].Rapidity(), FlatWeight )
                    h_mAK8_tau21cut.Fill( ak8JetsGood[i].M(), FlatWeight )
                    h_mprunedAK8_tau21cut.Fill( ak8JetsGoodPrunMass[i], FlatWeight )
                    h_mfilteredAK8_tau21cut.Fill( ak8JetsGoodFiltMass[i], FlatWeight )
                    h_mtrimmedAK8_tau21cut.Fill( ak8JetsGoodTrimMass[i], FlatWeight )
                    h_mSDropAK8_tau21cut.Fill( ak8JetsGoodSDropMass[i], FlatWeight )
                    h_minmassAK8_tau21cut.Fill( ak8JetsGoodMinMass[i], FlatWeight )
                    h_nsjAK8_tau21cut.Fill( ak8JetsGoodNSubJets[i], FlatWeight )

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
# @@@ Fix this                
############# loop over good muons and fill histos for muon cuts


# these need to fill in mu/el loop,  for h_minmassAK8_minMasscut >  options.minMassCut:
#                    h_ptLep_minMasscut.Fill(theLepton.Perp())
# $$$               if theLepton == Mu :
#                   h_ptMu_minMasscut.Fill(theLepton.Perp())
# $$$               if theLepton == El :
#                   h_ptEl_minMasscut.Fill(theLepton.Perp())
#                    h_ptAK4_minMasscut.Fill( theLepJet.Perp() )
#                    h_mAK4_minMasscut.Fill( theLepJet.M() )
#                    h_bdiscAK4_minMasscut.Fill( theLepJetBDisc )


#^ fill histos with muon pt cuts
            for imuon, muon in enumerate(goodmuonPt): #{ Loop over all Good muons to plot muon pt cut
                if goodmuonPt[imuon] < options.minMuonPt :  #$ Muon cuts
                    continue
                else: 
#   @@@ Fix this
           #  these already filled about        h_ptLep_ptMucut.Fill(goodmuonPt[imuon])
            #        h_ptMu_ptMucut.Fill(goodmuonPt[imuon])
                    h_tau32AK8_ptMucut.Fill( tau32, FlatWeight )
                    h_tau21AK8_ptMucut.Fill( tau21, FlatWeight )
                    h_ptAK4_ptMucut.Fill( theLepJet.Perp() )
                    h_mAK4_ptMucut.Fill( theLepJet.M() )
                    h_bdiscAK4_ptMucut.Fill( theLepJetBDisc )
                    h_ptAK8_ptMucut.Fill( ak8JetsGood[i].Perp(), FlatWeight )
                    h_etaAK8_ptMucut.Fill( ak8JetsGood[i].Eta(), FlatWeight )
                    h_yAK8_ptMucut.Fill( ak8JetsGood[i].Rapidity(), FlatWeight )
                    h_mAK8_ptMucut.Fill( ak8JetsGood[i].M(), FlatWeight )
                    h_mprunedAK8_ptMucut.Fill( ak8JetsGoodPrunMass[i], FlatWeight )
                    h_mfilteredAK8_ptMucut.Fill( ak8JetsGoodFiltMass[i], FlatWeight )
                    h_mtrimmedAK8_ptMucut.Fill( ak8JetsGoodTrimMass[i], FlatWeight )
                    h_mSDropAK8_ptMucut.Fill( ak8JetsGoodSDropMass[i], FlatWeight )
                    h_minmassAK8_ptMucut.Fill( ak8JetsGoodMinMass[i], FlatWeight )
                    h_nsjAK8_ptMucut.Fill( ak8JetsGoodNSubJets[i], FlatWeight 

                #} End Good Muon loop

###   $$$ once this is sorted out add same for electron pt 

        #@ KINEMATICS for all channels

        #@ Leptonic Kin
        if Leptonic :

            ttbarCandP4 = None


            #$ Check if the nearest jets to the leptons are b-tagged
            if theLepJetBDisc > options.bDiscMin:
                NPassBDiscMinCut = NPassBDiscMinCut + 1
                #^ fill bdiscmin cut here
                h_ptAK4_bDiscMincut.Fill(theLepJet.Perp())
                h_mAK4_bDiscMincut.Fill(theLepJet.M() )
                h_bdiscAK4_bDiscMincut.Fill(theLepJetBDisc)
                if dimuonCandidate :
                    NPassMuonBCut += 1
                elif dielectronCandidate :
                    NPassElBCut += 1
                elif mixedCandidate :
                    NPassMuonBCut += 1
            if theLepJetBDisc2 > options.bDiscMin:
                NPassBDisc2MinCut = NPassBDisc2MinCut + 1
                #^ fill bdiscmincut here
                h_ptAK4_bDiscMincut.Fill(theLepJet.Perp())
                h_mAK4_bDiscMincut.Fill(theLepJet.M() )
                h_bdiscAK4_bDiscMincut.Fill(theLepJetBDisc)
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
                #^ fill bdiscmincut histos here
                h_ptAK4_bDiscMincut.Fill(theLepJet.Perp())
                h_mAK4_bDiscMincut.Fill(theLepJet.M() )
                h_bdiscAK4_bDiscMincut.Fill(theLepJetBDisc)
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

           # @@@ Could you check this, I don't think it's fully correct
        #@ Semileptonic- but not boosted   
"""
        elif SemiLeptonic == True and nttags < 1 :    
            hadTopCandP4 = None  # ?
            lepTopCandP4 = None
            
            #$ Check if the nearest jet to the lepton is b-tagged
            if theLepJetBDisc > options.bDiscMin:
                NPassBDiscMinCut = NPassBDiscMinCut + 1
                #^ fill bdiscmincut histos here
                h_ptAK4_bDiscMincut.Fill(theLepJet.Perp())
                h_mAK4_bDiscMincut.Fill(theLepJet.M() )
                h_bdiscAK4_bDiscMincut.Fill(theLepJetBDisc)
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


        #@ End- Semileptonic- but not boosted 
"""
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

        if ttbarCand != None : 
            h_mttbar.Fill( ttbarCand.M() )
            #^ Eventually fill the h_mttbar histos with cuts


        #} End event loop
    #} End root file loop
#
print '========================================='
print ' Awesome Cut Flow Table'
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
