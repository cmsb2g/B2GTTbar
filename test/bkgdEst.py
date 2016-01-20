#! /usr/bin/env python
import ROOT
from math import *
import copy
# ROOT.gSystem.Load("libAnalysisPredictedDistribution")
ROOT.gROOT.ProcessLine('.L BTagCalibrationStandalone.cc+') 

calib = ROOT.BTagCalibration("csvv1", "CSVV1.csv")

from optparse import OptionParser
parser = OptionParser()

parser.add_option('--file', type='string', action='store',
                  dest='file',
                  help='Input file')

parser.add_option('--mistagFile', type='string', action='store',
                  dest='mistagFile',
                  help='MistagRate file')

parser.add_option('--outname', type='string', action='store',
                  default='outBkgdEst_outplots',
                  dest='outname',
                  help='Name of output file')

parser.add_option('--Syst', type='int', action='store',
                  default= 0,
                  dest='Syst',
                  help='Systematic type; jerDn = -2; jecDn = -1; jecNom = 0; jecUp = +1; jerUp = +2; bTagUp = +3; bTagDn = -3 ')

parser.add_option('--date', type='string', action='store',
                  default='011416',
                  dest='date',
                  help='date')

(options, args) = parser.parse_args()
argv = []

#date = "121615"
#Syst = 0  # jerDn = -2; jecDn = -1; jecNom = 0; jecUp = +1; jerUp = +2; bTagUp = +3; bTagDn = -3

if options.Syst == 0:
  systType = "nom"
elif options.Syst == 1:
  systType = "jec_up"
elif options.Syst == -1:
  systType = "jec_dn"
elif options.Syst == 2:
  systType = "jer_up"
elif options.Syst == -2:
  systType = "jer_dn"
elif options.Syst == 3:
  systType = "bTag_up"
elif options.Syst == -3:
  systType = "bTag_dn"


#OUT =  ROOT.TFile("outBkgdEst_JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65_"+date+"_"+systType+".root","RECREATE");
OUT =  ROOT.TFile(options.outname+"_"+options.date+"_"+systType+".root","RECREATE");
#F1   =  ROOT.TFile("/eos/uscms/store/user/jdolen/B2GAnaFW/Trees/JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65.root");
F1   =  ROOT.TFile(options.file);
Tree = F1.Get("TreeAllHad");
entries = Tree.GetEntries();
print 'entries '+str(entries)  


#Fmistag = ROOT.TFile("MistagRate_nbins_121615_8_ttbar_nom__Substract_outAntiTag_JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65_121615_jec_nom.root")
Fmistag = ROOT.TFile(options.mistagFile)

post = ["_jetPt_dRapHi_inclusive", "_jetPt_dRapHi_2btag", "_jetPt_dRapHi_1btag", "_jetPt_dRapHi_0btag",   
        "_jetPt_dRapLo_inclusive", "_jetPt_dRapLo_2btag", "_jetPt_dRapLo_1btag", "_jetPt_dRapLo_0btag"]

#^ Hadronic mtt selection and background estimaion
h_mttMass_tagMassSDTau32_dRapHi_inclusive = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapHi_inclusive"   , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapHi_0btag     = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapHi_0btag"       , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapHi_1btag     = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapHi_1btag"       , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapHi_2btag     = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapHi_2btag"       , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapLo_inclusive = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapLo_inclusive"   , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapLo_0btag     = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapLo_0btag"       , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapLo_1btag     = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapLo_1btag"       , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapLo_2btag     = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapLo_2btag"       , "", 700, 0, 7000 )


h_bkgdEst_tagMassSDTau32_dRapHi_inclusive = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapHi_inclusive"    , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapHi_0btag     = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapHi_0btag"        , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapHi_1btag     = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapHi_1btag"        , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapHi_2btag     = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapHi_2btag"        , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapLo_inclusive = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapLo_inclusive"    , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapLo_0btag     = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapLo_0btag"        , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapLo_1btag     = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapLo_1btag"        , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapLo_2btag     = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapLo_2btag"        , "", 700, 0, 7000 )

h_bkgdEst_modMass_tagMassSDTau32_dRapHi_inclusive = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapHi_inclusive"    , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag     = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag"        , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag     = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag"        , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag     = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag"        , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapLo_inclusive = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapLo_inclusive"    , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapLo_0btag     = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapLo_0btag"        , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag     = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag"        , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapLo_2btag     = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapLo_2btag"        , "", 700, 0, 7000 )


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


h_mistag_vs_jetPt_TagMassSDTau32 = []
for i in xrange(len(post)):
    h_mistag_vs_jetPt_TagMassSDTau32.append( Fmistag.Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32"+ post[i]   ).Clone())
  
    h_mistag_vs_jetPt_TagMassSDTau32[i]      .SetName("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32"+ post[i]    )
    
    ROOT.SetOwnership( h_mistag_vs_jetPt_TagMassSDTau32[i]    , False )
    

count = 0
n_topTag0MaxBdiscM_True  = 0
n_topTag0MaxBdiscM_False = 0
n_topTag1MaxBdiscM_True  = 0
n_topTag1MaxBdiscM_False = 0
n_newbtagjet0_True  = 0
n_newbtagjet0_False = 0
n_newbtagjet1_True  = 0
n_newbtagjet1_False = 0



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

    return bool(newBTag)


for event in Tree:
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
  Jet0CorrFactorUp = event.Jet0CorrFactorUp
  Jet0CorrFactorDn = event.Jet0CorrFactorDn

  Jet1CorrFactor   = event.Jet1CorrFactor
  Jet1CorrFactorUp = event.Jet1CorrFactorUp
  Jet1CorrFactorDn = event.Jet1CorrFactorDn

  Jet0PtSmearFactor   = event.Jet0PtSmearFactor
  Jet0PtSmearFactorUp = event.Jet0PtSmearFactorUp
  Jet0PtSmearFactorDn = event.Jet0PtSmearFactorDn

  Jet1PtSmearFactor   = event.Jet1PtSmearFactor
  Jet1PtSmearFactorUp = event.Jet1PtSmearFactorUp
  Jet1PtSmearFactorDn = event.Jet1PtSmearFactorDn

 
  if options.Syst == 0:
      jet0P4 = jet0P4Raw * Jet0CorrFactor * Jet0PtSmearFactor
      jet1P4 = jet1P4Raw * Jet1CorrFactor * Jet1PtSmearFactor
      reader = ROOT.BTagCalibrationReader(calib, 0, "comb", "central")  # 0 is for loose op 
      maxJetHt = event.HT
  elif options.Syst == 1:
      jet0P4 = jet0P4Raw * Jet0CorrFactorUp * Jet0PtSmearFactor
      jet1P4 = jet1P4Raw * Jet1CorrFactorUp * Jet1PtSmearFactor
      reader = ROOT.BTagCalibrationReader(calib, 0, "comb", "central")  # 0 is for loose op 
      maxJetHt = event.HT_CorrUp
  elif options.Syst == -1:
      jet0P4 = jet0P4Raw * Jet0CorrFactorDn * Jet0PtSmearFactor
      jet1P4 = jet1P4Raw * Jet1CorrFactorDn * Jet1PtSmearFactor
      reader = ROOT.BTagCalibrationReader(calib, 0, "comb", "central")  # 0 is for loose op 
      maxJetHt = event.HT_CorrDn
  elif options.Syst == 2:
      jet0P4 = jet0P4Raw * Jet0CorrFactor * Jet0PtSmearFactorUp
      jet1P4 = jet1P4Raw * Jet1CorrFactor * Jet1PtSmearFactorUp
      reader = ROOT.BTagCalibrationReader(calib, 0, "comb", "central")  # 0 is for loose op 
      maxJetHt = event.HT_PtSmearUp
  elif options.Syst == -2:
      jet0P4 = jet0P4Raw * Jet0CorrFactor * Jet0PtSmearFactorDn
      jet1P4 = jet1P4Raw * Jet1CorrFactor * Jet1PtSmearFactorDn
      reader = ROOT.BTagCalibrationReader(calib, 0, "comb", "central")  # 0 is for loose op 
      maxJetHt = event.HT_PtSmearDn
  elif options.Syst == 3:
      jet0P4 = jet0P4Raw * Jet0CorrFactor * Jet0PtSmearFactor
      jet1P4 = jet1P4Raw * Jet1CorrFactor * Jet1PtSmearFactor
      reader = ROOT.BTagCalibrationReader(calib, 0, "comb", "up")  # 0 is for loose op
      maxJetHt = event.HT
  elif options.Syst == -3:
      jet0P4 = jet0P4Raw * Jet0CorrFactor * Jet0PtSmearFactor
      jet1P4 = jet1P4Raw * Jet1CorrFactor * Jet1PtSmearFactor 
      reader = ROOT.BTagCalibrationReader(calib, 0, "comb", "down")  # 0 is for loose op
      maxJetHt = event.HT
  
  DijetMass = (jet0P4 + jet1P4).M()


  if jet0P4.Perp() < 400 or jet1P4.Perp() < 400:
    continue

  if maxJetHt < 1000:
    continue

  maxBdisc_jet0_ = event.Jet0SDbdisc0
  maxBdisc_jet1_ = event.Jet0SDbdisc1
  
  if abs(event.Jet0SDmaxbdiscflav) == 5:
      Jet0BTagEntry = 0
  elif abs(event.Jet0SDmaxbdiscflav) == 4:
      Jet0BTagEntry = 1
  else:
      Jet0BTagEntry = 2

  if abs(event.Jet1SDmaxbdiscflav) == 5:
      Jet1BTagEntry = 0
  elif abs(event.Jet1SDmaxbdiscflav) == 4:
      Jet1BTagEntry = 1
  else:
      Jet1BTagEntry = 2
  
  
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

  
  if topTag0MaxBdiscM == True:
    n_topTag0MaxBdiscM_True += 1
  else:
    n_topTag0MaxBdiscM_False += 1
  #print "topTag0MaxBdiscM = ", topTag0MaxBdiscM
  
  if topTag1MaxBdiscM == True:
    n_topTag1MaxBdiscM_True += 1
  else:
    n_topTag1MaxBdiscM_False += 1
  #print "topTag1MaxBdiscM = ", topTag1MaxBdiscM


  # b-tagging scale-factor
  sf0 = reader.eval( Jet0BTagEntry,  jet0P4.Eta(),  jet0P4.Perp() )  # jet flavor, eta, pt
  sf1 = reader.eval( Jet1BTagEntry,  jet1P4.Eta(),  jet1P4.Perp() )  # jet flavor, eta, pt
  newbtagjet0 = bool( applySF ( topTag0MaxBdiscM , sf0 , Btag_eff = 0.9) )
  newbtagjet1 = bool( applySF ( topTag1MaxBdiscM , sf1 , Btag_eff = 0.9) )
  
  # define tags - make sure they are the same as what was used to calculate the mistag
  topTag0MassSDTau32                 = topTag0MassSD and topTag0Tau32
  topTag1MassSDTau32                 = topTag1MassSD and topTag1Tau32
  topTag0MassSDMinMass               = topTag0MassSD and topTag0MinMass
  topTag1MassSDMinMass               = topTag1MassSD and topTag1MinMass
  topTag0MassSDMinMassTau32          = topTag0MassSD and topTag0MinMass and topTag0Tau32
  topTag1MassSDMinMassTau32          = topTag1MassSD and topTag1MinMass and topTag1Tau32
  topTag0MassSDMaxBdisc              = topTag0MassSD and newbtagjet0
  topTag1MassSDMaxBdisc              = topTag1MassSD and newbtagjet1
  topTag0MassFatTau32                = topTag0MassFat and topTag0Tau32
  topTag1MassFatTau32                = topTag1MassFat and topTag1Tau32
  topTag0MassFatMinMass              = topTag0MassFat and topTag0MinMass
  topTag1MassFatMinMass              = topTag1MassFat and topTag1MinMass
  topTag0MassFatMinMassTau32         = topTag0MassFat and topTag0MinMass and topTag0Tau32
  topTag1MassFatMinMassTau32         = topTag1MassFat and topTag1MinMass and topTag1Tau32

  #setup the modMass procedure
  DijetMass_modMass_jet0 = DijetMass
  DijetMass_modMass_jet1 = DijetMass
  DijetMass_modMass_flat_jet0 = DijetMass
  DijetMass_modMass_flat_jet1 = DijetMass
  #-----
  # randomly sample from QCD mass distribution in [140,250] 
  # ROOT.gRandom.SetSeed(0) # make sure =0 -> TRandom3 - Set the random generator sequence if seed is 0 (default value) a TUUID is generated and used to fill the first 8 integers of the seed 
  ROOT.gRandom = ROOT.TRandom3(0)
  randMass_QCD_Fat_jet0 = h_modMass_SD_jet0.GetRandom()
  randMass_QCD_Fat_jet1 = h_modMass_SD_jet1.GetRandom()

  # when doing the tag+X bkgd estimate procedure, change the mass of the X jet 
  jet0P4_modMass = copy.copy ( jet0P4 )
  p_vec_jet0 = ROOT.TVector3( jet0P4_modMass.Px(), jet0P4_modMass.Py(), jet0P4_modMass.Pz())
  jet0P4_modMass.SetVectM( p_vec_jet0, randMass_QCD_Fat_jet0)

  jet1P4_modMass = copy.copy ( jet1P4 )
  p_vec_jet1 = ROOT.TVector3(jet1P4_modMass.Px(), jet1P4_modMass.Py(), jet1P4_modMass.Pz())
  jet1P4_modMass.SetVectM( p_vec_jet1, randMass_QCD_Fat_jet1)

  # #sample from a uniform distribution in [140,250]
  rand =  ROOT.TRandom3(0)
  rand_mass = rand.Uniform(110,210)

  # print 'randMass_QCD_Fat_jet0 '+str(randMass_QCD_Fat_jet0)
  # print 'randMass_QCD_Fat_jet1 '+str(randMass_QCD_Fat_jet1)
  # print 'rand_mass '+str(rand_mass)

  jet0P4_modMass_flat = copy.copy ( jet0P4 )
  p_vec_jet0 = ROOT.TVector3( jet0P4_modMass_flat.Px(), jet0P4_modMass_flat.Py(), jet0P4_modMass_flat.Pz())
  jet0P4_modMass_flat.SetVectM( p_vec_jet0, rand_mass )

  jet1P4_modMass_flat = copy.copy ( jet1P4 )
  p_vec_jet1 = ROOT.TVector3( jet1P4_modMass_flat.Px(), jet1P4_modMass_flat.Py(), jet1P4_modMass_flat.Pz())
  jet1P4_modMass_flat.SetVectM( p_vec_jet1, rand_mass )

  # if jet 0 is outside of the top mass window, force it to have mass in the window 
  if event.Jet0MassSoftDrop < 110 or event.Jet0MassSoftDrop > 210:
      DijetMass_modMass_jet0 = (jet1P4+ jet0P4_modMass ).M()
      DijetMass_modMass_flat_jet0 = (jet1P4+ jet0P4_modMass_flat ).M()

  # if jet 0 is outside of the top mass window, force it to have mass in the window (sample from QCD mass distribution in [140,250])
  if event.Jet1MassSoftDrop < 110 or event.Jet1MassSoftDrop > 210:
      DijetMass_modMass_jet1 = (jet0P4+ jet1P4_modMass ).M()
      DijetMass_modMass_flat_jet1 = (jet0P4+ jet1P4_modMass_flat ).M()


  evWeight = 1
  #^ fill double tagged dijet distributions
  if topTag0MassSDTau32 and topTag1MassSDTau32:
      if event.DijetDeltaRap > 1 :
          #inclusive
          h_mttMass_tagMassSDTau32_dRapHi_inclusive.Fill( DijetMass   , evWeight )
          if newbtagjet0 and newbtagjet1:
                #2btag
                h_mttMass_tagMassSDTau32_dRapHi_2btag.Fill( DijetMass   , evWeight )
          if (newbtagjet0 and not newbtagjet1) or (newbtagjet1 and not newbtagjet0):
                #1btag
                h_mttMass_tagMassSDTau32_dRapHi_1btag.Fill( DijetMass   , evWeight )
          if not newbtagjet0 and not newbtagjet1:
                #0btag
                h_mttMass_tagMassSDTau32_dRapHi_0btag.Fill( DijetMass   , evWeight )
      if event.DijetDeltaRap < 1:
            #inclusive
            h_mttMass_tagMassSDTau32_dRapLo_inclusive.Fill( DijetMass   , evWeight )
            if newbtagjet0 and newbtagjet1:
                #2btag
                h_mttMass_tagMassSDTau32_dRapLo_2btag.Fill( DijetMass   , evWeight )
            if (newbtagjet0 and not newbtagjet1) or (newbtagjet1 and not newbtagjet0):
                #1btag
                h_mttMass_tagMassSDTau32_dRapLo_1btag.Fill( DijetMass   , evWeight )
            if not newbtagjet0 and not newbtagjet1:
                #0btag
                h_mttMass_tagMassSDTau32_dRapLo_0btag.Fill( DijetMass   , evWeight )
  


  
  rand1 =  ROOT.TRandom3(0)
  rand_bkgdest  = rand1.Uniform(0,1.0)

  bin = []
  rate = []
 
  #^ Fill predicted distribution

  # randomly select jet 0 to be the tag then fill predDist based on probability that jet 1 is mis-tagged
  if rand_bkgdest < 0.5 :

      if topTag0MassSDTau32 :
          # mttPredDist_tagMassSDTau32        .Accumulate(              ttMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
          # mttPredDist_modMass_tagMassSDTau32.Accumulate( ttMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
          for i in xrange(len(post)):
              bin.append ( h_mistag_vs_jetPt_TagMassSDTau32[i].GetXaxis().FindBin( event.Jet1Pt ))
              rate.append( h_mistag_vs_jetPt_TagMassSDTau32[i].GetBinContent(bin[i]))
          if event.DijetDeltaRap > 1 :
              #inclusive
              h_bkgdEst_tagMassSDTau32_dRapHi_inclusive              .Fill( DijetMass       , evWeight*rate[0])
              h_bkgdEst_modMass_tagMassSDTau32_dRapHi_inclusive      .Fill( DijetMass_modMass_jet1, evWeight*rate[0])
              if newbtagjet0 and newbtagjet1:
                  #2btag
                  h_bkgdEst_tagMassSDTau32_dRapHi_2btag              .Fill( DijetMass       , evWeight*rate[1])
                  h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag      .Fill( DijetMass_modMass_jet1, evWeight*rate[1])
              if (newbtagjet0 and not newbtagjet1) or (newbtagjet1 and not newbtagjet0):
                  #1btag
                  h_bkgdEst_tagMassSDTau32_dRapHi_1btag              .Fill( DijetMass       , evWeight*rate[2])
                  h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag      .Fill( DijetMass_modMass_jet1, evWeight*rate[2])   
              if not newbtagjet0 and not newbtagjet1:
                  #0btag
                  h_bkgdEst_tagMassSDTau32_dRapHi_0btag              .Fill( DijetMass       , evWeight*rate[3])
                  h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag      .Fill( DijetMass_modMass_jet1, evWeight*rate[3])
          if event.DijetDeltaRap < 1:
              #inclusive
              h_bkgdEst_tagMassSDTau32_dRapLo_inclusive              .Fill( DijetMass       , evWeight*rate[4])
              h_bkgdEst_modMass_tagMassSDTau32_dRapLo_inclusive      .Fill( DijetMass_modMass_jet1, evWeight*rate[4])
              if newbtagjet0 and newbtagjet1:
                  #2btag
                  h_bkgdEst_tagMassSDTau32_dRapLo_2btag              .Fill( DijetMass       , evWeight*rate[5])
                  h_bkgdEst_modMass_tagMassSDTau32_dRapLo_2btag      .Fill( DijetMass_modMass_jet1, evWeight*rate[5])
              if (newbtagjet0 and not newbtagjet1) or (newbtagjet1 and not newbtagjet0):
                  #1btag
                  h_bkgdEst_tagMassSDTau32_dRapLo_1btag              .Fill( DijetMass       , evWeight*rate[6])
                  h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag      .Fill( DijetMass_modMass_jet1, evWeight*rate[6])
              if not newbtagjet0 and not newbtagjet1:
                  #0btag
                  h_bkgdEst_tagMassSDTau32_dRapLo_0btag              .Fill( DijetMass       , evWeight*rate[7])
                  h_bkgdEst_modMass_tagMassSDTau32_dRapLo_0btag      .Fill( DijetMass_modMass_jet1, evWeight*rate[7])


  # randomly select jet 1 to be the tag then fill predDist based on probability that jet 0 is mis-tagged
  if rand_bkgdest >= 0.5 :

      if topTag1MassSDTau32 :
          # mttPredDist_tagMassSDTau32        .Accumulate(              ttMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
          # mttPredDist_modMass_tagMassSDTau32.Accumulate( ttMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
          for i in xrange(len(post)):
              bin.append (h_mistag_vs_jetPt_TagMassSDTau32[i].GetXaxis().FindBin( event.Jet0Pt ))
              rate.append( h_mistag_vs_jetPt_TagMassSDTau32[i].GetBinContent(bin[i]))
          if event.DijetDeltaRap > 1 :
              #inclusive
              h_bkgdEst_tagMassSDTau32_dRapHi_inclusive              .Fill( DijetMass       , evWeight*rate[0])
              h_bkgdEst_modMass_tagMassSDTau32_dRapHi_inclusive      .Fill( DijetMass_modMass_jet0, evWeight*rate[0])
              if newbtagjet0 and newbtagjet1:
                  #2btag
                  h_bkgdEst_tagMassSDTau32_dRapHi_2btag              .Fill( DijetMass       , evWeight*rate[1])
                  h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag      .Fill( DijetMass_modMass_jet0, evWeight*rate[1])
              if (newbtagjet0 and not newbtagjet1) or (newbtagjet1 and not newbtagjet0):
                  #1btag
                  h_bkgdEst_tagMassSDTau32_dRapHi_1btag              .Fill( DijetMass       , evWeight*rate[2])
                  h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag      .Fill( DijetMass_modMass_jet0, evWeight*rate[2])   
              if not newbtagjet0 and not newbtagjet1:
                  #0btag
                  h_bkgdEst_tagMassSDTau32_dRapHi_0btag              .Fill( DijetMass       , evWeight*rate[3])
                  h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag      .Fill( DijetMass_modMass_jet0, evWeight*rate[3])
          if event.DijetDeltaRap < 1:
              #inclusive
              h_bkgdEst_tagMassSDTau32_dRapLo_inclusive              .Fill( DijetMass       , evWeight*rate[4])
              h_bkgdEst_modMass_tagMassSDTau32_dRapLo_inclusive      .Fill( DijetMass_modMass_jet0, evWeight*rate[4])
              if newbtagjet0 and newbtagjet1:
                  #2btag
                  h_bkgdEst_tagMassSDTau32_dRapLo_2btag              .Fill( DijetMass       , evWeight*rate[5])
                  h_bkgdEst_modMass_tagMassSDTau32_dRapLo_2btag      .Fill( DijetMass_modMass_jet0, evWeight*rate[5])
              if (newbtagjet0 and not newbtagjet1) or (newbtagjet1 and not newbtagjet0):
                  #1btag
                  h_bkgdEst_tagMassSDTau32_dRapLo_1btag              .Fill( DijetMass       , evWeight*rate[6])
                  h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag      .Fill( DijetMass_modMass_jet0, evWeight*rate[6])
              if not newbtagjet0 and not newbtagjet1:
                  #0btag
                  h_bkgdEst_tagMassSDTau32_dRapLo_0btag              .Fill( DijetMass       , evWeight*rate[7])
                  h_bkgdEst_modMass_tagMassSDTau32_dRapLo_0btag      .Fill( DijetMass_modMass_jet0, evWeight*rate[7])
          # h_bkgdEst_modMass_flat_tagMassSDTau32 .Fill(  ttMass_modMass_flat_jet0, evWeight*rate)
  
  if newbtagjet0 == True:
    n_newbtagjet0_True += 1
  else:
    n_newbtagjet0_False += 1
  #print "newbtagjet0 = ", newbtagjet0
  if newbtagjet1 == True:
    n_newbtagjet1_True += 1
  else:
    n_newbtagjet1_False += 1
  #print "newbtagjet1 = ", newbtagjet1

   

OUT.cd()

h_mttMass_tagMassSDTau32_dRapHi_inclusive        .Write()
h_mttMass_tagMassSDTau32_dRapHi_2btag            .Write()
h_mttMass_tagMassSDTau32_dRapHi_1btag            .Write()
h_mttMass_tagMassSDTau32_dRapHi_0btag            .Write()
h_mttMass_tagMassSDTau32_dRapLo_inclusive        .Write()
h_mttMass_tagMassSDTau32_dRapLo_2btag            .Write()
h_mttMass_tagMassSDTau32_dRapLo_1btag            .Write()
h_mttMass_tagMassSDTau32_dRapLo_0btag            .Write()
h_bkgdEst_tagMassSDTau32_dRapHi_inclusive        .Write()
h_bkgdEst_tagMassSDTau32_dRapHi_2btag            .Write()
h_bkgdEst_tagMassSDTau32_dRapHi_1btag            .Write()
h_bkgdEst_tagMassSDTau32_dRapHi_0btag            .Write()
h_bkgdEst_tagMassSDTau32_dRapLo_inclusive        .Write()
h_bkgdEst_tagMassSDTau32_dRapLo_2btag            .Write()
h_bkgdEst_tagMassSDTau32_dRapLo_1btag            .Write()
h_bkgdEst_tagMassSDTau32_dRapLo_0btag            .Write()
h_bkgdEst_modMass_tagMassSDTau32_dRapHi_inclusive.Write()
h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag    .Write()
h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag    .Write()
h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag    .Write()
h_bkgdEst_modMass_tagMassSDTau32_dRapLo_inclusive.Write()
h_bkgdEst_modMass_tagMassSDTau32_dRapLo_2btag    .Write() 
h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag    .Write()
h_bkgdEst_modMass_tagMassSDTau32_dRapLo_0btag    .Write()


OUT.Write()
OUT.Close()




print "Number of events in h_mttMass_tagMassSDTau32_dRapHi_inclusive: ", h_mttMass_tagMassSDTau32_dRapHi_inclusive.GetSum()
print "Number of events in h_mttMass_tagMassSDTau32_dRapHi_0btag: "    , h_mttMass_tagMassSDTau32_dRapHi_0btag    .GetSum()         
print "Number of events in h_mttMass_tagMassSDTau32_dRapHi_1btag: "    , h_mttMass_tagMassSDTau32_dRapHi_1btag    .GetSum()         
print "Number of events in h_mttMass_tagMassSDTau32_dRapHi_2btag: "    , h_mttMass_tagMassSDTau32_dRapHi_2btag    .GetSum()         
print "Summed number of events of dRapHi_0btag + dRapHi_1btag + dRapHi_2btag: "       , h_mttMass_tagMassSDTau32_dRapHi_0btag.GetSum() + h_mttMass_tagMassSDTau32_dRapHi_1btag.GetSum() + h_mttMass_tagMassSDTau32_dRapHi_2btag.GetSum()
print ""
print "Number of events in h_mttMass_tagMassSDTau32_dRapLo_inclusive: ", h_mttMass_tagMassSDTau32_dRapLo_inclusive.GetSum()         
print "Number of events in h_mttMass_tagMassSDTau32_dRapLo_0btag: "    , h_mttMass_tagMassSDTau32_dRapLo_0btag    .GetSum()         
print "Number of events in h_mttMass_tagMassSDTau32_dRapLo_1btag: "    , h_mttMass_tagMassSDTau32_dRapLo_1btag    .GetSum()         
print "Number of events in h_mttMass_tagMassSDTau32_dRapLo_2btag: "    , h_mttMass_tagMassSDTau32_dRapLo_2btag    .GetSum() 
print "Summed number of events of dRapLo_0btag + dRapLo_1btag + dRapLo_2btag: "       , h_mttMass_tagMassSDTau32_dRapLo_0btag.GetSum() + h_mttMass_tagMassSDTau32_dRapLo_1btag.GetSum() + h_mttMass_tagMassSDTau32_dRapLo_2btag.GetSum()        
print ""
print ""
print "Number of events in h_bkgdEst_tagMassSDTau32_dRapHi_inclusive: ", h_bkgdEst_tagMassSDTau32_dRapHi_inclusive.GetSum()
print "Number of events in h_bkgdEst_tagMassSDTau32_dRapHi_0btag: "    , h_bkgdEst_tagMassSDTau32_dRapHi_0btag    .GetSum()         
print "Number of events in h_bkgdEst_tagMassSDTau32_dRapHi_1btag: "    , h_bkgdEst_tagMassSDTau32_dRapHi_1btag    .GetSum()         
print "Number of events in h_bkgdEst_tagMassSDTau32_dRapHi_2btag: "    , h_bkgdEst_tagMassSDTau32_dRapHi_2btag    .GetSum()         
print "Summed number of events of dRapHi_0btag + dRapHi_1btag + dRapHi_2btag: "       , h_bkgdEst_tagMassSDTau32_dRapHi_0btag.GetSum() + h_bkgdEst_tagMassSDTau32_dRapHi_1btag.GetSum() + h_bkgdEst_tagMassSDTau32_dRapHi_2btag.GetSum()
print ""
print "Number of events in h_bkgdEst_tagMassSDTau32_dRapLo_inclusive: ", h_bkgdEst_tagMassSDTau32_dRapLo_inclusive.GetSum()         
print "Number of events in h_bkgdEst_tagMassSDTau32_dRapLo_0btag: "    , h_bkgdEst_tagMassSDTau32_dRapLo_0btag    .GetSum()         
print "Number of events in h_bkgdEst_tagMassSDTau32_dRapLo_1btag: "    , h_bkgdEst_tagMassSDTau32_dRapLo_1btag    .GetSum()         
print "Number of events in h_bkgdEst_tagMassSDTau32_dRapLo_2btag: "    , h_bkgdEst_tagMassSDTau32_dRapLo_2btag    .GetSum() 
print "Summed number of events of dRapLo_0btag + dRapLo_1btag + dRapLo_2btag: "       , h_bkgdEst_tagMassSDTau32_dRapLo_0btag.GetSum() + h_bkgdEst_tagMassSDTau32_dRapLo_1btag.GetSum() + h_bkgdEst_tagMassSDTau32_dRapLo_2btag.GetSum()        
print ""
print ""
print "Number of events in h_bkgdEst_modMass_tagMassSDTau32_dRapHi_inclusive: ", h_bkgdEst_modMass_tagMassSDTau32_dRapHi_inclusive.GetSum()
print "Number of events in h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag: "    , h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag    .GetSum()         
print "Number of events in h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag: "    , h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag    .GetSum()         
print "Number of events in h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag: "    , h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag    .GetSum()         
print "Summed number of events of dRapHi_0btag + dRapHi_1btag + dRapHi_2btag: "       , h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag.GetSum() + h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag.GetSum() + h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag.GetSum()
print ""
print "Number of events in h_bkgdEst_modMass_tagMassSDTau32_dRapLo_inclusive: ", h_bkgdEst_modMass_tagMassSDTau32_dRapLo_inclusive.GetSum()         
print "Number of events in h_bkgdEst_modMass_tagMassSDTau32_dRapLo_0btag: "    , h_bkgdEst_modMass_tagMassSDTau32_dRapLo_0btag    .GetSum()         
print "Number of events in h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag: "    , h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag    .GetSum()         
print "Number of events in h_bkgdEst_modMass_tagMassSDTau32_dRapLo_2btag: "    , h_bkgdEst_modMass_tagMassSDTau32_dRapLo_2btag    .GetSum() 
print "Summed number of events of dRapLo_0btag + dRapLo_1btag + dRapLo_2btag: "       , h_bkgdEst_modMass_tagMassSDTau32_dRapLo_0btag.GetSum() + h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag.GetSum() + h_bkgdEst_modMass_tagMassSDTau32_dRapLo_2btag.GetSum()        

print "n_topTag0MaxBdiscM_True = ",  n_topTag0MaxBdiscM_True  
print "n_topTag0MaxBdiscM_False = ", n_topTag0MaxBdiscM_False 
print "n_topTag1MaxBdiscM_True = ",  n_topTag1MaxBdiscM_True
print "n_topTag1MaxBdiscM_False = ", n_topTag1MaxBdiscM_False 
print "n_newbtagjet0_True = ",  n_newbtagjet0_True  
print "n_newbtagjet0_False = ", n_newbtagjet0_False
print "n_newbtagjet1_True = ",  n_newbtagjet1_True
print "n_newbtagjet1_False = ", n_newbtagjet1_False







