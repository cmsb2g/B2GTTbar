#! /usr/bin/env python
import ROOT
from math import *
import copy
ROOT.gSystem.Load("libAnalysisPredictedDistribution")

# For official AK4 b-tag SF
#ROOT.gROOT.ProcessLine('.L BTagCalibrationStandalone.cc+') 
#calib = ROOT.BTagCalibration("csvv1", "CSVV1.csv")


from optparse import OptionParser
parser = OptionParser()

parser.add_option('--file', type='string', action='store',
                  dest='file',
                  help='Input file')

parser.add_option('--outname', type='string', action='store',
                  default='outAntiTag_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e',
                  dest='outname',
                  help='Name of output file')

# parser.add_option('--Syst', type='int', action='store',
#                   default= 0,
#                   dest='Syst',
#                   help='Systematic type; jerDn = -2; jecDn = -1; jecNom = 0; jecUp = +1; jerUp = +2; bTagUp = +3; bTagDn = -3; pdfUp = +4; pdfDn = -4; q2Up = +5; q2Dn = -5')

parser.add_option('--date', type='string', action='store',
                  default='011416',
                  dest='date',
                  help='date')

parser.add_option('--isData', action='store_true',
                  default=False,
                  dest='isData',
                  help='is it Data?')

(options, args) = parser.parse_args()
argv = []

verbose = False

# date = "121615"
# jecSys = 1  # jecDn = -1; jecNom = 0; jecUp = +1

# if jecSys == 0:
#   syst = "jec_nom"
# elif jecSys == 1:
#   syst = "jec_up"
# elif jecSys == -1:
#   syst = "jec_dn"

OUT =  ROOT.TFile(options.outname+"_"+options.date+".root","RECREATE");
F1  =  ROOT.TFile.Open(options.file);



Tree = F1.Get("TreeAllHad");
entries = Tree.GetEntries();
print 'entries '+str(entries)  

      

#^ Make mistag plots

h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_inclusive          = ROOT.TH1D( "h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_inclusive"            , "", 1400, 0, 7000 )
h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_0btag              = ROOT.TH1D( "h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_0btag"                , "", 1400, 0, 7000 )  
h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_1btag              = ROOT.TH1D( "h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_1btag"                , "", 1400, 0, 7000 ) 
h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_2btag              = ROOT.TH1D( "h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_2btag"                , "", 1400, 0, 7000 ) 
h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_inclusive          = ROOT.TH1D( "h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_inclusive"            , "", 1400, 0, 7000 )  
h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_0btag              = ROOT.TH1D( "h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_0btag"                , "", 1400, 0, 7000 )  
h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_1btag              = ROOT.TH1D( "h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_1btag"                , "", 1400, 0, 7000 )   
h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_2btag              = ROOT.TH1D( "h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_2btag"                , "", 1400, 0, 7000 )
h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_inclusive = ROOT.TH1D( "h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_inclusive"   , "", 1400, 0, 7000 )
h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_0btag     = ROOT.TH1D( "h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_0btag"       , "", 1400, 0, 7000 )  
h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_1btag     = ROOT.TH1D( "h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_1btag"       , "", 1400, 0, 7000 )  
h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_2btag     = ROOT.TH1D( "h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_2btag"       , "", 1400, 0, 7000 )  
h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_inclusive = ROOT.TH1D( "h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_inclusive"   , "", 1400, 0, 7000 )  
h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_0btag     = ROOT.TH1D( "h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_0btag"       , "", 1400, 0, 7000 )     
h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_1btag     = ROOT.TH1D( "h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_1btag"       , "", 1400, 0, 7000 )     
h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_2btag     = ROOT.TH1D( "h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_2btag"       , "", 1400, 0, 7000 )  
   

count = 0
maxJet0Ht = 0
maxJet1Ht = 0

def applySF ( isBTagged, Btag_SF, Btag_eff):

    newBTag = bool(isBTagged)


    if (Btag_SF == 1) :
       return newBTag; #no correction needed

    #throw dice
    rand2 =  ROOT.TRandom3(0)
    coin  = rand2.Uniform(0,1.0)


    if (Btag_SF > 1):  #use this if SF>1
        if ( not isBTagged ):
            #fraction of jets that need to be upgraded
            mistagPercent = (1.0 - Btag_SF) / (1.0 - (1.0/Btag_eff) )
            #upgrade to tagged
            if ( coin < mistagPercent ):
                newBTag = True

    else:  # use this if SF<1
    #downgrade tagged to untagged
        if ( isBTagged and coin > Btag_SF ):
            newBTag = False

    if newBTag != isBTagged and verbose:
        print 'isBTagged '+str(isBTagged)+' newBTag '+ str(newBTag )+' Btag_SF '+str(Btag_SF)+' coin '+str(coin)

    return bool(newBTag)

for event in Tree:
  # count +=1
  # if count%1000 ==0:
  #   print count


  # # Get same hists in different files for up/nom/dn
  # RawJet0Pt = event.Jet0PtRaw
  # RawJet1Pt = event.Jet1PtRaw

  # Jet0CorrFactor   = event.Jet0CorrFactor
  # Jet0CorrFactorUp = event.Jet0CorrFactorUp
  # Jet0CorrFactorDn = event.Jet0CorrFactorDn

  # Jet1CorrFactor   = event.Jet1CorrFactor
  # Jet1CorrFactorUp = event.Jet1CorrFactorUp
  # Jet1CorrFactorDn = event.Jet1CorrFactorDn  

  # if jecSys == 0:
  #     Jet0Pt = RawJet0Pt * Jet0CorrFactor
  #     Jet1Pt = RawJet1Pt * Jet1CorrFactor
  #     maxJetHt = event.HT
  # elif jecSys == 1:
  #     Jet0Pt = RawJet0Pt * Jet0CorrFactorUp
  #     Jet1Pt = RawJet1Pt * Jet1CorrFactorUp
  #     maxJetHt = event.HT_CorrUp
  # elif jecSys == -1:
  #     Jet0Pt = RawJet0Pt * Jet0CorrFactorDn
  #     Jet1Pt = RawJet1Pt * Jet1CorrFactorDn
  #     maxJetHt = event.HT_CorrDn

  # maxBdisc_jet0_ = event.Jet0SDbdisc0
  # maxBdisc_jet1_ = event.Jet0SDbdisc1

  count +=1
  if count%1000 ==0:
    print str(count)+" / "+str(entries)
  
  RawJet0Pt   = event.Jet0PtRaw
  RawJet0Eta  = event.Jet0EtaRaw
  RawJet0Phi  = event.Jet0PhiRaw
  RawJet0Mass = event.Jet0MassRaw

  jet0P4Raw = ROOT.TLorentzVector()
  jet0P4Raw.SetPtEtaPhiM( RawJet0Pt, RawJet0Eta, RawJet0Phi, RawJet0Mass)

  RawJet1Pt   = event.Jet1PtRaw
  RawJet1Eta  = event.Jet1EtaRaw
  RawJet1Phi  = event.Jet1PhiRaw
  RawJet1Mass = event.Jet1MassRaw

  jet1P4Raw = ROOT.TLorentzVector()
  jet1P4Raw.SetPtEtaPhiM( RawJet1Pt, RawJet1Eta, RawJet1Phi, RawJet1Mass)

  # Jec corrections
  Jet0CorrFactor   = event.Jet0CorrFactor
  # Jet0CorrFactorUp = event.Jet0CorrFactorUp
  # Jet0CorrFactorDn = event.Jet0CorrFactorDn

  Jet1CorrFactor   = event.Jet1CorrFactor
  # Jet1CorrFactorUp = event.Jet1CorrFactorUp
  # Jet1CorrFactorDn = event.Jet1CorrFactorDn

  Jet0PtSmearFactor   = event.Jet0PtSmearFactor
  # Jet0PtSmearFactorUp = event.Jet0PtSmearFactorUp
  # Jet0PtSmearFactorDn = event.Jet0PtSmearFactorDn

  Jet1PtSmearFactor   = event.Jet1PtSmearFactor
  # Jet1PtSmearFactorUp = event.Jet1PtSmearFactorUp
  # Jet1PtSmearFactorDn = event.Jet1PtSmearFactorDn

  # Top tagging scale factors from Svenja's talk
  # Jet 0
  if  400 < jet0P4Raw.Perp() * Jet0CorrFactor * Jet0PtSmearFactor < 550:
      sf0_MassTau32_nom     = 0.8 #0.812915
      sf0_MassTau32_err     = 0.1 #0.0849926
      # sf0_MassTau32_up      = sf0_MassTau32_nom + sf0_MassTau32_err
      # sf0_MassTau32_dn      = sf0_MassTau32_nom - sf0_MassTau32_err
      sf0_MassTau32bTag_nom = 0.75 #0.841186
      sf0_MassTau32bTag_err = 0.1 #0.0936928
      # sf0_MassTau32bTag_up  = sf0_MassTau32bTag_nom + sf0_MassTau32bTag_err
      # sf0_MassTau32bTag_dn  = sf0_MassTau32bTag_nom - sf0_MassTau32bTag_err
      sf0_bTag_nom          = 0.92
      sf0_bTag_err          = 0.07 #(1/sf0_bTag_nom)*sqrt((sf0_MassTau32_err/sf0_MassTau32_nom)**2+(sf0_MassTau32bTag_err/sf0_MassTau32bTag_nom)**2)
      # sf0_bTag_up           = sf0_bTag_nom + sf0_bTag_err
      # sf0_bTag_dn           = sf0_bTag_nom - sf0_bTag_err
      #print 'sf0_MassTau32_nom '+str(sf0_MassTau32_nom)+' sf0_MassTau32bTag_nom '+str(sf0_MassTau32bTag_nom)+' sf0_bTag_nom '+str(sf0_bTag_nom)
  if jet0P4Raw.Perp() * Jet0CorrFactor * Jet0PtSmearFactor > 550:
      sf0_MassTau32_nom     = 0.8 #0.975712
      sf0_MassTau32_err     = 0.1 #0.193765
      # sf0_MassTau32_up      = sf0_MassTau32_nom + sf0_MassTau32_err
      # sf0_MassTau32_dn      = sf0_MassTau32_nom - sf0_MassTau32_err
      sf0_MassTau32bTag_nom = 0.75 #0.849168
      sf0_MassTau32bTag_err = 0.1 #0.193302
      # sf0_MassTau32bTag_up  = sf0_MassTau32bTag_nom + sf0_MassTau32bTag_err
      # sf0_MassTau32bTag_dn  = sf0_MassTau32bTag_nom - sf0_MassTau32bTag_err
      sf0_bTag_nom          = 0.72
      sf0_bTag_err          = 0.16 #(1/sf0_bTag_nom)*sqrt((sf0_MassTau32_err/sf0_MassTau32_nom)**2+(sf0_MassTau32bTag_err/sf0_MassTau32bTag_nom)**2)
      # sf0_bTag_up           = sf0_bTag_nom + sf0_bTag_err
      # sf0_bTag_dn           = sf0_bTag_nom - sf0_bTag_err
  # Jet 1
  if  400 < jet1P4Raw.Perp() * Jet1CorrFactor * Jet1PtSmearFactor < 550:
      sf1_MassTau32_nom     = 0.8 #0.812915
      sf1_MassTau32_err     = 0.1 #0.0849926
      # sf1_MassTau32_up      = sf1_MassTau32_nom + sf1_MassTau32_err
      # sf1_MassTau32_dn      = sf1_MassTau32_nom - sf1_MassTau32_err
      sf1_MassTau32bTag_nom = 0.75 #0.841186
      sf1_MassTau32bTag_err = 0.1 #0.0936928
      # sf1_MassTau32bTag_up  = sf1_MassTau32bTag_nom + sf1_MassTau32bTag_err
      # sf1_MassTau32bTag_dn  = sf1_MassTau32bTag_nom - sf1_MassTau32bTag_err
      sf1_bTag_nom          = 0.92
      sf1_bTag_err          = 0.07 #(1/sf1_bTag_nom)*sqrt((sf1_MassTau32_err/sf1_MassTau32_nom)**2+(sf1_MassTau32bTag_err/sf1_MassTau32bTag_nom)**2)
      # sf1_bTag_up           = sf1_bTag_nom + sf1_bTag_err
      # sf1_bTag_dn           = sf1_bTag_nom - sf1_bTag_err
  if jet1P4Raw.Perp() * Jet1CorrFactor * Jet1PtSmearFactor > 550:
      sf1_MassTau32_nom     = 0.8 #0.975712
      sf1_MassTau32_err     = 0.1 #0.193765
      # sf1_MassTau32_up      = sf1_MassTau32_nom + sf1_MassTau32_err
      # sf1_MassTau32_dn      = sf1_MassTau32_nom - sf1_MassTau32_err
      sf1_MassTau32bTag_nom = 0.75 #0.849168
      sf1_MassTau32bTag_err = 0.1 #0.193302
      # sf1_MassTau32bTag_up  = sf1_MassTau32bTag_nom + sf1_MassTau32bTag_err
      # sf1_MassTau32bTag_dn  = sf1_MassTau32bTag_nom - sf1_MassTau32bTag_err
      sf1_bTag_nom          = 0.72
      sf1_bTag_err          = 0.16 #(1/sf1_bTag_nom)*sqrt((sf1_MassTau32_err/sf1_MassTau32_nom)**2+(sf1_MassTau32bTag_err/sf1_MassTau32bTag_nom)**2)
      # sf1_bTag_up           = sf1_bTag_nom + sf1_bTag_err
      # sf1_bTag_dn           = sf1_bTag_nom - sf1_bTag_err

 
  if options.isData == True:
      jet0P4 = jet0P4Raw * Jet0CorrFactor 
      jet1P4 = jet1P4Raw * Jet1CorrFactor 
      sf0_MassTau32 = 1
      sf0_MassTau32bTag = 1
      sf1_MassTau32 = 1
      sf1_MassTau32bTag = 1
      sf0_bTag = 1
      sf1_bTag = 1
      #reader = ROOT.BTagCalibrationReader(calib, 0, "comb", "central")  # 0 is for loose op 
      maxJetHt = event.HT

  elif options.isData == False:
      # nom only
      jet0P4 = jet0P4Raw * Jet0CorrFactor * Jet0PtSmearFactor
      jet1P4 = jet1P4Raw * Jet1CorrFactor * Jet1PtSmearFactor
      sf0_MassTau32     = sf0_MassTau32_nom
      sf0_MassTau32bTag = sf0_MassTau32bTag_nom
      sf0_bTag          = sf0_bTag_nom
      sf1_MassTau32     = sf0_MassTau32_nom
      sf1_MassTau32bTag = sf0_MassTau32bTag_nom
      sf1_bTag          = sf0_bTag_nom
      #reader = ROOT.BTagCalibrationReader(calib, 0, "comb", "central")  # 0 is for loose op 
      maxJetHt = event.HT

  if jet0P4.Perp() < 400 or jet1P4.Perp() < 400:
    continue

  if maxJetHt < 1000:
    continue

  maxBdisc_jet0_ = event.Jet0SDbdisc0
  maxBdisc_jet1_ = event.Jet0SDbdisc1

  # define tags - make sure they are the same as what was used to calculate the mistag
  topTag0MassFat                     = event.Jet0Mass > 140 and event.Jet1Mass< 250
  topTag1MassFat                     = event.Jet1Mass > 140 and event.Jet1Mass< 250
  topTag0MassSD                      = event.Jet0MassSoftDrop > 110 and event.Jet0MassSoftDrop < 210
  topTag1MassSD                      = event.Jet1MassSoftDrop > 110 and event.Jet1MassSoftDrop < 210
  topTag0Tau32                       = event.Jet0Tau32 < 0.69
  topTag1Tau32                       = event.Jet1Tau32 < 0.69
  topTag0MinMass                     = event.Jet0CMSminMass > 50 
  topTag1MinMass                     = event.Jet1CMSminMass > 50
  topTag0MaxBdiscM                   = maxBdisc_jet0_ > 0.890 # CSVv2 medium operating point 2015_06
  topTag1MaxBdiscM                   = maxBdisc_jet1_ > 0.890 # CSVv2 medium operating point 2015_06
  topTag0MassSDTau32                 = topTag0MassSD and topTag0Tau32
  topTag1MassSDTau32                 = topTag1MassSD and topTag1Tau32
  topTag0MassSDMinMass               = topTag0MassSD and topTag0MinMass
  topTag1MassSDMinMass               = topTag1MassSD and topTag1MinMass
  topTag0MassSDMinMassTau32          = topTag0MassSD and topTag0MinMass and topTag0Tau32
  topTag1MassSDMinMassTau32          = topTag1MassSD and topTag1MinMass and topTag1Tau32
  topTag0MassSDMaxBdisc              = topTag0MassSD and topTag0MaxBdiscM
  topTag1MassSDMaxBdisc              = topTag1MassSD and topTag1MaxBdiscM
  topTag0MassFatTau32                = topTag0MassFat and topTag0Tau32
  topTag1MassFatTau32                = topTag1MassFat and topTag1Tau32
  topTag0MassFatMinMass              = topTag0MassFat and topTag0MinMass
  topTag1MassFatMinMass              = topTag1MassFat and topTag1MinMass
  topTag0MassFatMinMassTau32         = topTag0MassFat and topTag0MinMass and topTag0Tau32
  topTag1MassFatMinMassTau32         = topTag1MassFat and topTag1MinMass and topTag1Tau32
  

  # Many anti-tag definitions
  antiTag0minMass50                       = event.Jet0CMSminMass < 50 
  antiTag1minMass50                       = event.Jet1CMSminMass < 50
  antiTag0minMass30                       = event.Jet0CMSminMass < 30 
  antiTag1minMass30                       = event.Jet1CMSminMass < 30
  antiTag0Tau32                           = event.Jet0Tau32 > 0.69
  antiTag1Tau32                           = event.Jet1Tau32 > 0.69
  
  antiTag0minMass50_ReqTopMassSD         = topTag0MassSD and antiTag0minMass50
  antiTag1minMass50_ReqTopMassSD         = topTag1MassSD and antiTag1minMass50
  antiTag0minMass30_ReqTopMassSD         = topTag0MassSD and antiTag0minMass30
  antiTag1minMass30_ReqTopMassSD         = topTag1MassSD and antiTag1minMass30
  antiTag0Tau32_ReqTopMassSD             = topTag0MassSD and antiTag0Tau32
  antiTag1Tau32_ReqTopMassSD             = topTag1MassSD and antiTag1Tau32
  
  antiTag0minMass50_ReqTopMassFat         = topTag0MassFat and antiTag0minMass50
  antiTag1minMass50_ReqTopMassFat         = topTag1MassFat and antiTag1minMass50
  antiTag0minMass30_ReqTopMassFat         = topTag0MassFat and antiTag0minMass30
  antiTag1minMass30_ReqTopMassFat         = topTag1MassFat and antiTag1minMass30
  antiTag0Tau32_ReqTopMassFat             = topTag0MassFat and antiTag0Tau32
  antiTag1Tau32_ReqTopMassFat             = topTag1MassFat and antiTag1Tau32
  
  # Scale factor modifications

  # official AK4 b-tagging scale-factor
  #sf0 = reader.eval( Jet0BTagEntry,  jet0P4.Eta(),  jet0P4.Perp() )  # jet flavor, eta, pt
  #sf1 = reader.eval( Jet1BTagEntry,  jet1P4.Eta(),  jet1P4.Perp() )  # jet flavor, eta, pt
  # newbtagjet0 = bool( applySF ( topTag0MaxBdiscM , sf0 , Btag_eff = 0.1) )
  # newbtagjet1 = bool( applySF ( topTag1MaxBdiscM , sf1 , Btag_eff = 0.1) )

  # newtopTag0MassSDTau32 = bool( applySF ( topTag0MassSDTau32 , sf0_MassTau32 , Btag_eff = 0.2) )
  # newtopTag1MassSDTau32 = bool( applySF ( topTag1MassSDTau32 , sf1_MassTau32 , Btag_eff = 0.2) )

  # newbtagjet0 = bool( applySF ( topTag0MaxBdiscM , sf0_bTag , Btag_eff = 0.6) )
  # newbtagjet1 = bool( applySF ( topTag1MaxBdiscM , sf1_bTag , Btag_eff = 0.6) )

  # newtopTag0MassSDTau32 = topTag0MassSDTau32 #  bool( applySF ( topTag0MassSDTau32 , sf0_MassTau32 , Btag_eff = 0.2) )
  # newtopTag1MassSDTau32 = topTag1MassSDTau32 #  bool( applySF ( topTag1MassSDTau32 , sf1_MassTau32 , Btag_eff = 0.2) )

  newbtagjet0 = bool( applySF ( topTag0MaxBdiscM , sf0_bTag , Btag_eff = 0.7) )
  newbtagjet1 = bool( applySF ( topTag1MaxBdiscM , sf1_bTag , Btag_eff = 0.7) )


  evWeight = 1
  rand1 =  ROOT.TRandom3(0)
  rand_mistag  = rand1.Uniform(0,1.0)

  if rand_mistag < 0.5 :
    #----------anti-tag tau32, keep jet in SD mass window
    if antiTag0Tau32_ReqTopMassSD:
        #if event.DijetDeltaRap > 1:
        #inclusive
        h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_inclusive  .Fill( event.Jet1Pt, evWeight )
        #2btag
        if newbtagjet0 and newbtagjet1:
            h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_2btag  .Fill( event.Jet1Pt, evWeight )
        #1btag
        if (newbtagjet0 and not newbtagjet1):
            h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_1btag  .Fill( event.Jet1Pt, evWeight )
        if (newbtagjet1 and not newbtagjet0):
            h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_1btag  .Fill( event.Jet1Pt, evWeight )
        #0btag
        if not newbtagjet0 and not newbtagjet1:
            h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_0btag  .Fill( event.Jet1Pt, evWeight )
        # if event.DijetDeltaRap < 1:
        #     #inclusive
        #     h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_inclusive     .Fill( event.Jet1Pt, evWeight )
        #     #2btag
        #     if newbtagjet0 and newbtagjet1:
        #         h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_2btag     .Fill( event.Jet1Pt, evWeight )
        #     #1btag
        #     if (newbtagjet0 and not newbtagjet1):
        #         h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_1btag     .Fill( event.Jet1Pt, evWeight )
        #     if (newbtagjet1 and not newbtagjet0):
        #         h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_1btag     .Fill( event.Jet1Pt, evWeight )
        #     #0btag
        #     if not newbtagjet0 and not newbtagjet1:
        #         h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_0btag     .Fill( event.Jet1Pt, evWeight )
        
        if topTag1MassSDTau32    : 
            #if event.DijetDeltaRap > 1 :
            #inclusive
            h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_inclusive  .Fill( event.Jet1Pt, evWeight )
            #2btag
            if newbtagjet0 and newbtagjet1:
                h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_2btag  .Fill( event.Jet1Pt, evWeight )
            #1btag
            if (newbtagjet0 and not newbtagjet1):
                h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_1btag  .Fill( event.Jet1Pt, evWeight )
            if (newbtagjet1 and not newbtagjet0):
                h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_1btag  .Fill( event.Jet1Pt, evWeight )
            #0btag
            if not newbtagjet0 and not newbtagjet1:
                h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_0btag  .Fill( event.Jet1Pt, evWeight )
            # if event.DijetDeltaRap < 1 :
            #     #inclusive
            #     h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_inclusive     .Fill( event.Jet1Pt, evWeight )
            #     #2btag
            #     if newbtagjet0 and newbtagjet1:
            #         h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_2btag     .Fill( event.Jet1Pt, evWeight )
            #     #1btag
            #     if (newbtagjet0 and not newbtagjet1):
            #         h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_1btag     .Fill( event.Jet1Pt, evWeight )
            #     if (newbtagjet1 and not newbtagjet0):
            #         h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_1btag     .Fill( event.Jet1Pt, evWeight )
            #     #0btag
            #     if not newbtagjet0 and not newbtagjet1:
            #         h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_0btag     .Fill( event.Jet1Pt, evWeight )
        
    

  if rand_mistag >= 0.5 :
    #----------anti-tag tau32, keep jet in SD mass window
    if antiTag1Tau32_ReqTopMassSD:
        #if event.DijetDeltaRap > 1:
        #inclusive
        h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_inclusive  .Fill( event.Jet0Pt, evWeight )
        #2btag
        if newbtagjet0 and newbtagjet1:
            h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_2btag  .Fill( event.Jet0Pt, evWeight )
        #1btag
        if (newbtagjet0 and not newbtagjet1):
            h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_1btag  .Fill( event.Jet0Pt, evWeight )
        if (newbtagjet1 and not newbtagjet0):
            h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_1btag  .Fill( event.Jet0Pt, evWeight )
        #0btag
        if not newbtagjet0 and not newbtagjet1:
            h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_0btag  .Fill( event.Jet0Pt, evWeight )
        # if event.DijetDeltaRap < 1: 
        #     #inclusive
        #     h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_inclusive     .Fill( event.Jet0Pt, evWeight )
        #     #2btag
        #     if newbtagjet0 and newbtagjet1:
        #         h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_2btag     .Fill( event.Jet0Pt, evWeight )
        #     #1btag
        #     if (newbtagjet0 and not newbtagjet1):
        #         h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_1btag     .Fill( event.Jet0Pt, evWeight )
        #     if (newbtagjet1 and not newbtagjet0):
        #         h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_1btag     .Fill( event.Jet0Pt, evWeight )
        #     #0btag
        #     if not newbtagjet0 and not newbtagjet1:
        #         h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_0btag     .Fill( event.Jet0Pt, evWeight )   
        
        if topTag0MassSDTau32    : 
            #if event.DijetDeltaRap > 1 :
            #inclusive
            h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_inclusive  .Fill( event.Jet0Pt, evWeight )
            #2btag
            if newbtagjet0 and newbtagjet1:
                h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_2btag  .Fill( event.Jet0Pt, evWeight )
            #1btag
            if (newbtagjet0 and not newbtagjet1):
                h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_1btag  .Fill( event.Jet0Pt, evWeight )
            if (newbtagjet1 and not newbtagjet0):
                h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_1btag  .Fill( event.Jet0Pt, evWeight ) 
            #0btag
            if not newbtagjet0 and not newbtagjet1:
                h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_0btag  .Fill( event.Jet0Pt, evWeight )
            # if event.DijetDeltaRap < 1 :
            #     #inclusive
            #     h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_inclusive  .Fill( event.Jet0Pt, evWeight )
            #     #2btag
            #     if newbtagjet0 and newbtagjet1:
            #         h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_2btag  .Fill( event.Jet0Pt, evWeight )
            #     #1btag
            #     if (newbtagjet0 and not newbtagjet1):
            #         h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_1btag  .Fill( event.Jet0Pt, evWeight )
            #     if (newbtagjet1 and not newbtagjet0):
            #         h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_1btag  .Fill( event.Jet0Pt, evWeight )
            #     #0btag
            #     if not newbtagjet0 and not newbtagjet1:
            #         h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_0btag  .Fill( event.Jet0Pt, evWeight )
    


OUT.cd()

h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_inclusive         .Write()
h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_0btag             .Write()
h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_1btag             .Write()
h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_2btag             .Write()
# h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_inclusive         .Write()
# h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_0btag             .Write()
# h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_1btag             .Write()
# h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_2btag             .Write()
h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_inclusive.Write()
h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_0btag    .Write() 
h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_1btag    .Write()
h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_2btag    .Write()
# h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_inclusive.Write()
# h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_0btag    .Write()
# h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_1btag    .Write()
# h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_2btag    .Write()


OUT.Write()
OUT.Close()

print "Number of events in h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_inclusive: ", h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_inclusive.GetSum()
print "Number of events in h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_0btag: "    , h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_0btag    .GetSum()         
print "Number of events in h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_1btag: "    , h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_1btag    .GetSum()         
print "Number of events in h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_2btag: "    , h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_2btag    .GetSum()         
print "Summed number of events of dRapHi_0btag + dRapHi_1btag + dRapHi_2btag: "       , h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_0btag.GetSum() + h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_1btag.GetSum() + h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_2btag.GetSum()
# print ""
# print "Number of events in h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_inclusive: ", h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_inclusive.GetSum()         
# print "Number of events in h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_0btag: "    , h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_0btag    .GetSum()         
# print "Number of events in h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_1btag: "    , h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_1btag    .GetSum()         
# print "Number of events in h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_2btag: "    , h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_2btag    .GetSum() 
# print "Summed number of events of dRapLo_0btag + dRapLo_1btag + dRapLo_2btag: "       , h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_0btag.GetSum() + h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_1btag.GetSum() + h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_2btag.GetSum()        





