#! /usr/bin/env python

# To run:
# python AK8JetTester.py --files="file_list.txt" --maxevents=100 --verbose

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
                  default=999,
                  dest='maxjets',
                  help='Number of jets to plot. To plot all jets, set to a big number like 999')


parser.add_option('--bdisc', type='string', action='store',
                  default='combinedInclusiveSecondaryVertexV2BJetTags',
                  dest='bdisc',
                  help='Name of output file')


parser.add_option('--bDiscMin', type='float', action='store',
                  default=0.423,
                  dest='bDiscMin',
                  help='Minimum b discriminator')

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

parser.add_option('--mAK8GroomedCut', type='float', action='store',
                  default=100.,
                  dest='mAK8GroomedCut',
                  help='Groomed mass Cut for CMS Combined Tagger: Defauled for Soft Drop Mass')

parser.add_option('--tau32Cut', type='float', action='store',
                  default=0.6,
                  dest='tau32Cut',
                  help='Tau3 / Tau2 n-subjettiness cut for CMS Combined Tagger')

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
import copy


#gen labels and handles
h_genPartCharge = Handle("std::vector<float>")
l_genPartCharge = ("genPart" , "genPartCharge")
h_genPartE      = Handle("std::vector<float>")
l_genPartE      = ("genPart" , "genPartE")
h_genPartEta    = Handle("std::vector<float>")
l_genPartEta    = ("genPart" , "genPartEta")
h_genPartID     = Handle("std::vector<float>")
l_genPartID     = ("genPart" , "genPartID")
h_genPartMass   = Handle("std::vector<float>")
l_genPartMass   = ("genPart" , "genPartMass")
h_genPartMomID  = Handle("std::vector<float>")
l_genPartMomID  = ("genPart" , "genPartMomID")
h_genPartPhi    = Handle("std::vector<float>")
l_genPartPhi    = ("genPart" , "genPartPhi")
h_genPartPt     = Handle("std::vector<float>")
l_genPartPt     = ("genPart" , "genPartPt")
h_genPartE      = Handle("std::vector<float>")
l_genPartE      = ("genPart" , "genPartE")
h_genPartStatus = Handle("std::vector<float>")
l_genPartStatus = ("genPart" , "genPartStatus")
h_genPartY      = Handle("std::vector<float>")
l_genPartY      = ("genPart" , "genPartY")


#Rho
h_rho = Handle("double")
l_rho = ("fixedGridRhoFastjetAll", "")


h_NPV = Handle("std::int")
l_NPV = ( "eventUserData" , "npv" )

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




f = ROOT.TFile(options.outname, "RECREATE")
f.cd()

#^ Plot initialization
h_mttbar = ROOT.TH1F("h_mttbar", ";m_{t#bar{t}} (GeV)", 200, 0, 6000)
h_mttbar_true = ROOT.TH1F("h_mttbar_true", "True m_{t#bar{t}};m_{t#bar{t}} (GeV)", 200, 0, 6000)


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
h_nsjAK8 = ROOT.TH1F("h_nsjAK8", "AK8 CMS Top Tagger N_{subjets};N_{subjets}", 5, 0, 5)
h_tau21AK8 = ROOT.TH1F("h_tau21AK8", "AK8 Jet #tau_{2} / #tau_{1};Mass#tau_{21}", 100, 0, 1.0)
h_tau32AK8 = ROOT.TH1F("h_tau32AK8", "AK8 Jet #tau_{3} / #tau_{2};Mass#tau_{32}", 100, 0, 1.0)


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

NAK8Jets = 0
NPassGoodJetAK8Cut = 0

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

        countBadCategory = 0
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

        #EVENT GEN HANDLE FILLING
        event.getByLabel ( l_genPartCharge , h_genPartCharge  )
        event.getByLabel ( l_genPartE      , h_genPartE       )
        event.getByLabel ( l_genPartEta    , h_genPartEta     )
        event.getByLabel ( l_genPartID     , h_genPartID      )
        event.getByLabel ( l_genPartMass   , h_genPartMass    )
        event.getByLabel ( l_genPartMomID  , h_genPartMomID   )
        event.getByLabel ( l_genPartPhi    , h_genPartPhi     )
        event.getByLabel ( l_genPartPt     , h_genPartPt      )
        event.getByLabel ( l_genPartE      , h_genPartE       )
        event.getByLabel ( l_genPartStatus , h_genPartStatus  )
        event.getByLabel ( l_genPartY      , h_genPartY       )
 
        countHadronicWdaughters = 0
        if len(h_genPartPt.product()) > 0:
            genPartCharge = h_genPartCharge .product()
            genPartE      = h_genPartE      .product()
            genPartEta    = h_genPartEta    .product()
            genPartID     = h_genPartID     .product()
            genPartMass   = h_genPartMass   .product()
            genPartMomID  = h_genPartMomID  .product()
            genPartPhi    = h_genPartPhi    .product()
            genPartPt     = h_genPartPt     .product()
            genPartE      = h_genPartE      .product()
            genPartStatus = h_genPartStatus .product()
            genPartY      = h_genPartY      .product()
            for igen, gen in enumerate(genPartPt): #{ Loop over all gen particles in event
               if options.verbose :
                  print 'gen id '+str( genPartID[igen] )+' status '+str(genPartStatus[igen])+' momID '+str(genPartMomID[igen])+' genPartPt '+str(genPartPt[igen])
               pdgid  = genPartID[igen]
               mom    = genPartMomID[igen]
               status = genPartStatus[igen]
               # status 20-29 -> pythia 8 hardest subprocess. status 1 = pythia final state particle (W daugthers should not have daughters with status 1 but they seem to. Is this a bug in the Ntuple maker?)
               if abs(mom) == 24 and ((status< 30 and status>=20) or status == 1  or status == 2):
                  if options.verbose :
                     print ' -> Found W daughter'
                  if abs(pdgid)<6 and abs(pdgid)>0:
                     countHadronicWdaughters = countHadronicWdaughters + 1
                     if options.verbose :
                        print ' ---> Hadronic decay'

            if options.verbose:
                  print 'countHadronicWdaughters '+str(countHadronicWdaughters)
               # if mom == -24 and status< 30 and status>=20:
               #    if options.verbose :
               #       print ' -> Found W+ daughter'
               #    if abs(pdgid)<6 and abs(pdgid)>0:
               #       W1had = True
               #       if options.verbose :
               #          print ' ---> Hadronic decay'


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


                AK8SubJetsBDisc = []
                AK8SubJetsPt = []
                AK8SubJetsEta = []
                AK8SubJetsPhi = []
    
                if len( h_subjetsAK8BDisc.product() ) > 0 : 
                    AK8SubJetsBDisc = h_subjetsAK8BDisc.product()
                    AK8SubJetsPt = h_subjetsAK8Pt.product()
                    AK8SubJetsEta = h_subjetsAK8Eta.product()
                    AK8SubJetsPhi = h_subjetsAK8Phi.product()
                    
                

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


                    # if AK8minmass[i] > 50:
                    # if AK8P4Corr.M() > 100:
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

            subJetBDiscs = []

            for i in range(0,len(ak8JetsGood)):#{ Loop over Fat jets that passed cuts for t tagging
                if ak8JetsGood[i].Perp() < options.minAK8Pt : #$ Pt cut for passed jets
                    continue
                if evWeight != -1 :
                    FlatWeight = evWeight
                else :
                    FlatWeight = 1


                subJetBDiscs.append([])

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

                print 'len(AK8SubJetsPt) : '+str(len(AK8SubJetsPt))
                for check in [ak8JetsGoodTopSubjetIndex0[i],
                           ak8JetsGoodTopSubjetIndex1[i],
                           ak8JetsGoodTopSubjetIndex2[i],
                           ak8JetsGoodTopSubjetIndex3[i]] :
                    print ' check: '+str(int(check))
                    if int(check) > len(AK8SubJetsPt) :
                        print '===================='
                        print ' Catastrophic failure. Index is out of range. Setup is completely wrong.'
                        print '===================='
                        exit(1)

                print 'ak8JetsGoodTopSubjetIndex0[i] '+str(ak8JetsGoodTopSubjetIndex0[i])
                print 'ak8JetsGoodTopSubjetIndex1[i] '+str(ak8JetsGoodTopSubjetIndex1[i])
                print 'ak8JetsGoodTopSubjetIndex2[i] '+str(ak8JetsGoodTopSubjetIndex2[i])
                print 'ak8JetsGoodTopSubjetIndex3[i] '+str(ak8JetsGoodTopSubjetIndex3[i])

            

                if ak8JetsGoodTopSubjetIndex0[i] > -1 :
                    sbdisc0 = AK8SubJetsBDisc[ int(ak8JetsGoodTopSubjetIndex0[i]) ]
                    spt0    = AK8SubJetsPt[ int(ak8JetsGoodTopSubjetIndex0[i]) ]
                    seta0   = AK8SubJetsEta[ int(ak8JetsGoodTopSubjetIndex0[i]) ]
                    sphi0   = AK8SubJetsPhi[ int(ak8JetsGoodTopSubjetIndex0[i]) ]
                    if len( subJetBDiscs ) > 1 :
                        subJetBDiscs[i].append(sbdisc0)

                if ak8JetsGoodTopSubjetIndex1[i] > -1 :
                    sbdisc1 = AK8SubJetsBDisc[ int(ak8JetsGoodTopSubjetIndex1[i]) ]
                    spt1    = AK8SubJetsPt[ int(ak8JetsGoodTopSubjetIndex1[i]) ]
                    seta1   = AK8SubJetsEta[ int(ak8JetsGoodTopSubjetIndex1[i]) ]
                    sphi1   = AK8SubJetsPhi[ int(ak8JetsGoodTopSubjetIndex1[i]) ]
                    if len( subJetBDiscs ) > 1 :
                        subJetBDiscs[i].append(sbdisc1)

                if ak8JetsGoodTopSubjetIndex2[i] > -1 :
                    sbdisc2 = AK8SubJetsBDisc[ int(ak8JetsGoodTopSubjetIndex2[i]) ]
                    spt2    = AK8SubJetsPt[ int(ak8JetsGoodTopSubjetIndex2[i]) ]
                    seta2   = AK8SubJetsEta[ int(ak8JetsGoodTopSubjetIndex2[i]) ]
                    sphi2   = AK8SubJetsPhi[ int(ak8JetsGoodTopSubjetIndex2[i]) ]
                    if len( subJetBDiscs ) > 1 :
                        subJetBDiscs[i].append(sbdisc2)

                if ak8JetsGoodTopSubjetIndex3[i] > -1 :
                    sbdisc3 = AK8SubJetsBDisc[ int(ak8JetsGoodTopSubjetIndex3[i]) ]
                    spt3    = AK8SubJetsPt[ int(ak8JetsGoodTopSubjetIndex3[i]) ]
                    seta3   = AK8SubJetsEta[ int(ak8JetsGoodTopSubjetIndex3[i]) ]
                    sphi3   = AK8SubJetsPhi[ int(ak8JetsGoodTopSubjetIndex3[i]) ]
                    if len( subJetBDiscs ) > 1 :
                        subJetBDiscs[i].append(sbdisc3)


                if options.verbose :

                    print 'Top tag candidate : '
                    print '   top jet pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, m = {3:6.2f}'.format (
                        ak8JetsGood[i].Perp(), ak8JetsGood[i].Rapidity(), ak8JetsGood[i].Phi(), ak8JetsGood[i].M() )                 

                    
                    print '   Subjet indices : %6d %6d %6d %6d' % (ak8JetsGoodTopSubjetIndex0[i],
                                                                ak8JetsGoodTopSubjetIndex1[i],
                                                                ak8JetsGoodTopSubjetIndex2[i],
                                                                ak8JetsGoodTopSubjetIndex3[i])

                    for index in [ak8JetsGoodTopSubjetIndex0[i],
                                  ak8JetsGoodTopSubjetIndex1[i],
                                  ak8JetsGoodTopSubjetIndex2[i],
                                  ak8JetsGoodTopSubjetIndex3[i] ] :
                        if index > len(AK8SubJetsBDisc) :
                            print "Problem! Subjet indices are wrong!"
                            exit(1)


                    print '   -subjet0pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, B = {3:6.2f}'.format ( spt0,seta0,sphi0,sbdisc0 )
                    print '   -subjet1pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, B = {3:6.2f}'.format ( spt1,seta1,sphi1,sbdisc1 )
                    print '   -subjet2pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, B = {3:6.2f}'.format ( spt2,seta2,sphi2,sbdisc2 )
                    print '   -subjet3pt = {0:6.2f}, y = {1:6.2f}, phi = {2:6.2f}, B = {3:6.2f}'.format ( spt3,seta3,sphi3,sbdisc3 )

                mAK8Pruned = AK8PrunedM[i] 
                mAK8Filtered = AK8FilteredM[i] 
                mAK8Trimmed = AK8TrimmedM[i]
                mAK8SDrop = AK8SDropM[i]
                # Make sure there are top tags if we want to plot them
                minMass = AK8minmass[i]
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
                
                #^ Plot Kinematics for AK8 Jets
                h_ptAK8.Fill( ak8JetsGood[i].Perp(), FlatWeight )
                h_etaAK8.Fill( ak8JetsGood[i].Eta(), FlatWeight )
                h_yAK8.Fill( ak8JetsGood[i].Rapidity(), FlatWeight )
                h_mAK8.Fill( ak8JetsGood[i].M(), FlatWeight )
                h_mprunedAK8.Fill( ak8JetsGoodPrunMass[i], FlatWeight )
                h_mfilteredAK8.Fill( ak8JetsGoodFiltMass[i], FlatWeight )
                h_mtrimmedAK8.Fill( ak8JetsGoodTrimMass[i], FlatWeight )
                h_mSDropAK8.Fill( ak8JetsGoodSDropMass[i], FlatWeight )
                h_minmassAK8.Fill( ak8JetsGoodMinMass[i], FlatWeight )
                h_nsjAK8.Fill( ak8JetsGoodNSubJets[i], FlatWeight )    