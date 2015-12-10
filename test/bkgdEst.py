#! /usr/bin/env python
import ROOT
from math import *
# ROOT.gSystem.Load("libAnalysisPredictedDistribution")


OUT =  ROOT.TFile("outBkgdEst_JetHT_Run2015D_PromptReco-v3_and_v4_oct19json_120615.root","RECREATE");
F1   =  ROOT.TFile("/uscms_data/d3/maral87/ttbarResonances/B2GAnaFW/CMSSW_7_4_12/src/Analysis/B2GAnaFW_Maral/NTUPLES/runs/run_102415/JetHT_Run2015D_PromptReco-v3_and_v4_oct19json_tag_and_probe_102415.root");
Tree = F1.Get("TreeAllHad");
entries = Tree.GetEntries();
print 'entries '+str(entries)  


Fmistag = ROOT.TFile("run_113015/run_113015_2/MistagRate_nbins_113015_8_Substract_outAntiTag_JetHT_Run2015D_PromptReco-v3_and_v4_oct19json_tag_and_probe_113015.root")

post = ["_jetPt_dRapHi_inclusive", "_jetPt_dRapHi_2btag", "_jetPt_dRapHi_1btag", "_jetPt_dRapHi_0btag",   
        "_jetPt_dRapLo_inclusive", "_jetPt_dRapLo_2btag", "_jetPt_dRapLo_1btag", "_jetPt_dRapLo_0btag"]

#^ Hadronic mtt selection and background estimaion
h_mttMass_tagMassSD                       = ROOT.TH1D("h_mttMass_tagMassSD"                        , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapHi_inclusive = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapHi_inclusive"  , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapHi_0btag     = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapHi_0btag"      , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapHi_1btag     = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapHi_1btag"      , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapHi_2btag     = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapHi_2btag"      , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapLo_inclusive = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapLo_inclusive"  , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapLo_0btag     = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapLo_0btag"      , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapLo_1btag     = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapLo_1btag"      , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapLo_2btag     = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapLo_2btag"      , "", 700, 0, 7000 )
h_mttMass_tagMassSDMinMass                = ROOT.TH1D("h_mttMass_tagMassSDMinMass"                 , "", 700, 0, 7000 )
h_mttMass_tagMassFat                      = ROOT.TH1D("h_mttMass_tagMassFat"                       , "", 700, 0, 7000 )
h_mttMass_tagMassFatMinMass               = ROOT.TH1D("h_mttMass_tagMassFatMinMass"                , "", 700, 0, 7000 )

h_bkgdEst_tagMassSD                       = ROOT.TH1D("h_bkgdEst_tagMassSD"                         , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapHi_inclusive = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapHi_inclusive"   , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapHi_0btag     = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapHi_0btag"       , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapHi_1btag     = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapHi_1btag"       , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapHi_2btag     = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapHi_2btag"       , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapLo_inclusive = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapLo_inclusive"   , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapLo_0btag     = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapLo_0btag"       , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapLo_1btag     = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapLo_1btag"       , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapLo_2btag     = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapLo_2btag"       , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDMinMass                = ROOT.TH1D("h_bkgdEst_tagMassSDMinMass"                  , "", 700, 0, 7000 )
h_bkgdEst_tagMassFat                      = ROOT.TH1D("h_bkgdEst_tagMassFat"                        , "", 700, 0, 7000 )
h_bkgdEst_tagMassFatMinMass               = ROOT.TH1D("h_bkgdEst_tagMassFatMinMass"                 , "", 700, 0, 7000 )

h_bkgdEst_modMass_tagMassSD                       = ROOT.TH1D("h_bkgdEst_modMass_tagMassSD"                         , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapHi_inclusive = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapHi_inclusive"   , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag     = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag"       , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag     = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag"       , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag     = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag"       , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapLo_inclusive = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapLo_inclusive"   , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapLo_0btag     = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapLo_0btag"       , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag     = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag"       , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapLo_2btag     = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapLo_2btag"       , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDMinMass                = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDMinMass"                  , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassFat                      = ROOT.TH1D("h_bkgdEst_modMass_tagMassFat"                        , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassFatMinMass               = ROOT.TH1D("h_bkgdEst_modMass_tagMassFatMinMass"                 , "", 700, 0, 7000 )

h_bkgdEst_modMass_flat_tagMassSD         = ROOT.TH1D("h_bkgdEst_modMass_flat_tagMassSD"        , "", 700, 0, 7000 )
h_bkgdEst_modMass_flat_tagMassSDTau32    = ROOT.TH1D("h_bkgdEst_modMass_flat_tagMassSDTau32"   , "", 700, 0, 7000 )
h_bkgdEst_modMass_flat_tagMassSDMinMass  = ROOT.TH1D("h_bkgdEst_modMass_flat_tagMassSDMinMass" , "", 700, 0, 7000 )
h_bkgdEst_modMass_flat_tagMassFat        = ROOT.TH1D("h_bkgdEst_modMass_flat_tagMassFat"       , "", 700, 0, 7000 )
h_bkgdEst_modMass_flat_tagMassFatMinMass = ROOT.TH1D("h_bkgdEst_modMass_flat_tagMassFatMinMass", "", 700, 0, 7000 )

# #^ Predicted Distribution - Background estimation 
# mttPredDist_modMass_tagMassSD          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSD         , "mttPredDist_modMass_tagMassSD"        , "mTT Mass", 700, 0, 7000 )
# mttPredDist_modMass_tagMassSDTau32     = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32    , "mttPredDist_modMass_tagMassSDTau32"   , "mTT Mass", 700, 0, 7000 )
# mttPredDist_modMass_tagMassSDMinMass   = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDMinMass  , "mttPredDist_modMass_tagMassSDMinMass" , "mTT Mass", 700, 0, 7000 )
# # mttPredDist_modMass_tagMassFat         = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassFat        , "mttPredDist_modMass_tagMassFat"       , "mTT Mass", 700, 0, 7000 )
# mttPredDist_modMass_tagMassFatMinMass  = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassFatMinMass , "mttPredDist_modMass_tagMassFatMinMass", "mTT Mass", 700, 0, 7000 )

# ROOT.SetOwnership( mttPredDist_modMass_tagMassSD         , False )
# ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32    , False )
# ROOT.SetOwnership( mttPredDist_modMass_tagMassSDMinMass  , False )
# # ROOT.SetOwnership( mttPredDist_modMass_tagMassFat        , False )
# ROOT.SetOwnership( mttPredDist_modMass_tagMassFatMinMass , False )

# mttPredDist_tagMassSD         = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSD         , "mttPredDist_tagMassSD"        , "mTT Mass", 700, 0, 7000 )
# mttPredDist_tagMassSDTau32    = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32    , "mttPredDist_tagMassSDTau32"   , "mTT Mass", 700, 0, 7000 )
# mttPredDist_tagMassSDMinMass  = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDMinMass  , "mttPredDist_tagMassSDMinMass" , "mTT Mass", 700, 0, 7000 )
# # mttPredDist_tagMassFat        = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassFat        , "mttPredDist_tagMassFat"       , "mTT Mass", 700, 0, 7000 )
# mttPredDist_tagMassFatMinMass = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassFatMinMass , "mttPredDist_tagMassFatMinMass", "mTT Mass", 700, 0, 7000 )

# ROOT.SetOwnership( mttPredDist_tagMassSD         , False )
# ROOT.SetOwnership( mttPredDist_tagMassSDTau32    , False )
# ROOT.SetOwnership( mttPredDist_tagMassSDMinMass  , False )
# # ROOT.SetOwnership( mttPredDist_tagMassFat        , False )
# ROOT.SetOwnership( mttPredDist_tagMassFatMinMass , False )


h_mistag_vs_jetPt_TagMassSDTau32 = []
for i in xrange(len(post)):
    #h_mistag_vs_jetPt_TagMassSD           = Fmistag.Get("h_mistag_AntiTagMinMass30_ReqTopMassSD_TagMassSD"         ).Clone()
    #h_mistag_vs_jetPt_TagMassSDTau32      = Fmistag.Get("h_mistag_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32"    ).Clone()
    h_mistag_vs_jetPt_TagMassSDTau32.append( Fmistag.Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32"+ post[i]   ).Clone())
    #h_mistag_vs_jetPt_TagMassSDMinMass    = Fmistag.Get("h_mistag_AntiTagMinMass50_ReqTopMassSD_TagMassSDMinMass"  ).Clone()
    #h_mistag_vs_jetPt_TagMassFatMinMass   = Fmistag.Get("h_mistag_AntiTagMinMass50_ReqTopMassFat_TagMassFatMinMass").Clone()
    #h_mistag_vs_jetPt_TagMassFatMinMass   = Fmistag.Get("h_mistag_AntiTagMinMass30_ReqTopMassFat_TagMassFatMinMass").Clone()
    # h_mistag_vs_jetPt_TagMassFat          = Fmistag.Get("h_mistag_vs_jetPt_TagMassFat").Clone()

    #h_mistag_vs_jetPt_TagMassSD           .SetName("h_mistag_AntiTagMinMass30_ReqTopMassSD_TagMassSD"         )
    #h_mistag_vs_jetPt_TagMassSDTau32      .SetName("h_mistag_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32"    )
    h_mistag_vs_jetPt_TagMassSDTau32[i]      .SetName("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32"+ post[i]    )
    #h_mistag_vs_jetPt_TagMassSDMinMass    .SetName("h_mistag_AntiTagMinMass50_ReqTopMassSD_TagMassSDMinMass"  )
    #h_mistag_vs_jetPt_TagMassFatMinMass   .SetName("h_mistag_AntiTagMinMass50_ReqTopMassFat_TagMassFatMinMass")
    #h_mistag_vs_jetPt_TagMassFatMinMass   .SetName("h_mistag_AntiTagMinMass30_ReqTopMassFat_TagMassFatMinMass")


    #ROOT.SetOwnership( h_mistag_vs_jetPt_TagMassSD         , False )
    ROOT.SetOwnership( h_mistag_vs_jetPt_TagMassSDTau32[i]    , False )
    #ROOT.SetOwnership( h_mistag_vs_jetPt_TagMassSDMinMass  , False )
    #ROOT.SetOwnership( h_mistag_vs_jetPt_TagMassFatMinMass , False )
    # ROOT.SetOwnership( h_mistag_vs_jetPt_TagMassFat        , False )



    




count = 0
for event in Tree:
  count +=1
  if count%1000 ==0:
    print str(count)+" / "+str(entries)
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
  # topTag0MaxBdiscL                   = maxBdisc_jet0_ > 0.605 # CSVv2 loose operating point 2015_06
  # topTag1MaxBdiscL                   = maxBdisc_jet1_ > 0.605 # CSVv2 loose operating point 2015_06
  topTag0MaxBdiscM                   = maxBdisc_jet0_ > 0.890 # CSVv2 medium operating point 2015_06
  topTag1MaxBdiscM                   = maxBdisc_jet1_ > 0.890 # CSVv2 medium operating point 2015_06
  # topTag0MaxBdiscT                   = maxBdisc_jet0_ > 0.970 # CSVv2 tight operating point 2015_06
  # topTag1MaxBdiscT                   = maxBdisc_jet1_ > 0.970 # CSVv2 tight operating point 2015_06
  topTag0MassSDTau32                 = topTag0MassSD and topTag0Tau32
  topTag1MassSDTau32                 = topTag1MassSD and topTag1Tau32
  topTag0MassSDMinMass               = topTag0MassSD and topTag0MinMass
  topTag1MassSDMinMass               = topTag1MassSD and topTag1MinMass
  topTag0MassSDMinMassTau32          = topTag0MassSD and topTag0MinMass and topTag0Tau32
  topTag1MassSDMinMassTau32          = topTag1MassSD and topTag1MinMass and topTag1Tau32
  topTag0MassSDMaxBdisc              = topTag0MassSD and topTag0MaxBdiscM
  topTag1MassSDMaxBdisc              = topTag1MassSD and topTag1MaxBdiscM
  # topTag0MassSDMaxBdiscMinMass       = topTag0MassSD and topTag0MaxBdiscM and topTag0MinMass 
  # topTag1MassSDMaxBdiscMinMass       = topTag1MassSD and topTag1MaxBdiscM and topTag1MinMass 
  # topTag0MassSDMaxBdiscTau32         = topTag0MassSD and topTag0MaxBdiscM and topTag0Tau32 
  # topTag1MassSDMaxBdiscTau32         = topTag1MassSD and topTag1MaxBdiscM and topTag1Tau32 
  # topTag0MassSDMaxBdiscMinMassTau32  = topTag0MassSD and topTag0MaxBdiscM and topTag0MinMass and topTag0Tau32
  # topTag1MassSDMaxBdiscMinMassTau32  = topTag1MassSD and topTag1MaxBdiscM and topTag1MinMass and topTag1Tau32
  topTag0MassFatTau32                = topTag0MassFat and topTag0Tau32
  topTag1MassFatTau32                = topTag1MassFat and topTag1Tau32
  topTag0MassFatMinMass              = topTag0MassFat and topTag0MinMass
  topTag1MassFatMinMass              = topTag1MassFat and topTag1MinMass
  topTag0MassFatMinMassTau32         = topTag0MassFat and topTag0MinMass and topTag0Tau32
  topTag1MassFatMinMassTau32         = topTag1MassFat and topTag1MinMass and topTag1Tau32
  # topTag0MassFatMaxBdisc             = topTag0MassFat and topTag0MaxBdiscM
  # topTag1MassFatMaxBdisc             = topTag1MassFat and topTag1MaxBdiscM
  # topTag0MassFatMaxBdiscMinMass      = topTag0MassFat and topTag0MaxBdiscM and topTag0MinMass 
  # topTag1MassFatMaxBdiscMinMass      = topTag1MassFat and topTag1MaxBdiscM and topTag1MinMass 
  # topTag0MassFatMaxBdiscTau32        = topTag0MassFat and topTag0MaxBdiscM and topTag0Tau32 
  # topTag1MassFatMaxBdiscTau32        = topTag1MassFat and topTag1MaxBdiscM and topTag1Tau32 
  # topTag0MassFatMaxBdiscMinMassTau32 = topTag0MassFat and topTag0MaxBdiscM and topTag0MinMass and topTag0Tau32
  # topTag1MassFatMaxBdiscMinMassTau32 = topTag1MassFat and topTag1MaxBdiscM and topTag1MinMass and topTag1Tau32
    #MaxBdiscL_ReqTopMassFat         = topTag1MassFat and antiTag1MaxBdiscL

  #^ fill double tagged dijet distributions
  if topTag0MassSD and topTag1MassSD:
      h_mttMass_tagMassSD.Fill( event.DijetMass   , evWeight )
  if topTag0MassSDTau32 and topTag1MassSDTau32:
      if event.DijetDeltaRap > 1 :
          #inclusive
          h_mttMass_tagMassSDTau32_dRapHi_inclusive.Fill( event.DijetMass   , evWeight )
          if topTag0MaxBdiscM and topTag1MaxBdiscM:
                #2btag
                h_mttMass_tagMassSDTau32_dRapHi_2btag.Fill( event.DijetMass   , evWeight )
          if (topTag0MaxBdiscM and not topTag1MaxBdiscM) or (topTag1MaxBdiscM and not topTag0MaxBdiscM):
                #1btag
                h_mttMass_tagMassSDTau32_dRapHi_1btag.Fill( event.DijetMass   , evWeight )
          if not topTag0MaxBdiscM and not topTag1MaxBdiscM:
                #0btag
                h_mttMass_tagMassSDTau32_dRapHi_0btag.Fill( event.DijetMass   , evWeight )
      if event.DijetDeltaRap < 1:
            #inclusive
            h_mttMass_tagMassSDTau32_dRapLo_inclusive.Fill( event.DijetMass   , evWeight )
            if topTag0MaxBdiscM and topTag1MaxBdiscM:
                #2btag
                h_mttMass_tagMassSDTau32_dRapLo_2btag.Fill( event.DijetMass   , evWeight )
            if (topTag0MaxBdiscM and not topTag1MaxBdiscM) or (topTag1MaxBdiscM and not topTag0MaxBdiscM):
                #1btag
                h_mttMass_tagMassSDTau32_dRapLo_1btag.Fill( event.DijetMass   , evWeight )
            if not topTag0MaxBdiscM and not topTag1MaxBdiscM:
                #0btag
                h_mttMass_tagMassSDTau32_dRapLo_0btag.Fill( event.DijetMass   , evWeight )
  if topTag0MassSDMinMass and topTag1MassSDMinMass:
      h_mttMass_tagMassSDMinMass.Fill( event.DijetMass   , evWeight )
  if topTag0MassFat and topTag1MassFat:
      h_mttMass_tagMassFat.Fill( event.DijetMass   , evWeight )
  if topTag0MassFatMinMass and topTag1MassFatMinMass:
      h_mttMass_tagMassFatMinMass.Fill( event.DijetMass   , evWeight )


  evWeight = 1
  rand1 =  ROOT.TRandom3(0)
  rand_bkgdest  = rand1.Uniform(0,1.0)

  bin = []
  rate = []
 
  #^ Fill predicted distribution

  # randomly select jet 0 to be the tag then fill predDist based on probability that jet 1 is mis-tagged
  if rand_bkgdest < 0.5 :
      #if topTag0MassSD :
          # mttPredDist_tagMassSD        .Accumulate(              ttMass, ak8JetsGood[1].Perp(), topTag1MassSD, evWeight )
          # mttPredDist_modMass_tagMassSD.Accumulate( ttMass_modMass_jet1, ak8JetsGood[1].Perp(), topTag1MassSD, evWeight )
          #bin   = h_mistag_vs_jetPt_TagMassSD.GetXaxis().FindBin( event.Jet1Pt )
          #rate  = h_mistag_vs_jetPt_TagMassSD.GetBinContent(bin);
          #h_bkgdEst_tagMassSD              .Fill(       event.DijetMass       , evWeight*rate)
          #h_bkgdEst_modMass_tagMassSD      .Fill(       event.DijetModMassJet1, evWeight*rate)
          # h_bkgdEst_modMass_flat_tagMassSD .Fill(  ttMass_modMass_flat_jet1, evWeight*rate)
      if topTag0MassSDTau32 :
          # mttPredDist_tagMassSDTau32        .Accumulate(              ttMass, ak8JetsGood[1].Perp(), topTag1MassSDTau32, evWeight )
          # mttPredDist_modMass_tagMassSDTau32.Accumulate( ttMass_modMass_jet1, ak8JetsGood[1].Perp(), topTag1MassSDTau32, evWeight )
          for i in xrange(len(post)):
              bin.append ( h_mistag_vs_jetPt_TagMassSDTau32[i].GetXaxis().FindBin( event.Jet1Pt ))
              rate.append( h_mistag_vs_jetPt_TagMassSDTau32[i].GetBinContent(bin[i]))
          if event.DijetDeltaRap > 1 :
              #inclusive
              h_bkgdEst_tagMassSDTau32_dRapHi_inclusive              .Fill( event.DijetMass       , evWeight*rate[0])
              h_bkgdEst_modMass_tagMassSDTau32_dRapHi_inclusive      .Fill( event.DijetModMassJet1, evWeight*rate[0])
              if topTag0MaxBdiscM and topTag1MaxBdiscM:
                  #2btag
                  h_bkgdEst_tagMassSDTau32_dRapHi_2btag              .Fill( event.DijetMass       , evWeight*rate[1])
                  h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag      .Fill( event.DijetModMassJet1, evWeight*rate[1])
              if (topTag0MaxBdiscM and not topTag1MaxBdiscM) or (topTag1MaxBdiscM and not topTag0MaxBdiscM):
                  #1btag
                  h_bkgdEst_tagMassSDTau32_dRapHi_1btag              .Fill( event.DijetMass       , evWeight*rate[2])
                  h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag      .Fill( event.DijetModMassJet1, evWeight*rate[2])   
              if not topTag0MaxBdiscM and not topTag1MaxBdiscM:
                  #0btag
                  h_bkgdEst_tagMassSDTau32_dRapHi_0btag              .Fill( event.DijetMass       , evWeight*rate[3])
                  h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag      .Fill( event.DijetModMassJet1, evWeight*rate[3])
          if event.DijetDeltaRap < 1:
              #inclusive
              h_bkgdEst_tagMassSDTau32_dRapLo_inclusive              .Fill( event.DijetMass       , evWeight*rate[4])
              h_bkgdEst_modMass_tagMassSDTau32_dRapLo_inclusive      .Fill( event.DijetModMassJet1, evWeight*rate[4])
              if topTag0MaxBdiscM and topTag1MaxBdiscM:
                  #2btag
                  h_bkgdEst_tagMassSDTau32_dRapLo_2btag              .Fill( event.DijetMass       , evWeight*rate[5])
                  h_bkgdEst_modMass_tagMassSDTau32_dRapLo_2btag      .Fill( event.DijetModMassJet1, evWeight*rate[5])
              if (topTag0MaxBdiscM and not topTag1MaxBdiscM) or (topTag1MaxBdiscM and not topTag0MaxBdiscM):
                  #1btag
                  h_bkgdEst_tagMassSDTau32_dRapLo_1btag              .Fill( event.DijetMass       , evWeight*rate[6])
                  h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag      .Fill( event.DijetModMassJet1, evWeight*rate[6])
              if not topTag0MaxBdiscM and not topTag1MaxBdiscM:
                  #0btag
                  h_bkgdEst_tagMassSDTau32_dRapLo_0btag              .Fill( event.DijetMass       , evWeight*rate[7])
                  h_bkgdEst_modMass_tagMassSDTau32_dRapLo_0btag      .Fill( event.DijetModMassJet1, evWeight*rate[7])
          # h_bkgdEst_modMass_flat_tagMassSDTau32 .Fill(  ttMass_modMass_flat_jet1, evWeight*rate)

      #if topTag0MassSDMinMass :
          # mttPredDist_tagMassSDMinMass        .Accumulate(              ttMass, ak8JetsGood[1].Perp(), topTag1MassSDMinMass, evWeight )
          #bin   = h_mistag_vs_jetPt_TagMassSDMinMass.GetXaxis().FindBin( event.Jet1Pt )
          #rate  = h_mistag_vs_jetPt_TagMassSDMinMass.GetBinContent(bin);
          #h_bkgdEst_tagMassSDMinMass              .Fill(  event.DijetMass       , evWeight*rate)
          #h_bkgdEst_modMass_tagMassSDMinMass      .Fill(  event.DijetModMassJet1, evWeight*rate)
          # h_bkgdEst_modMass_flat_tagMassSDMinMass .Fill(  ttMass_modMass_flat_jet1, evWeight*rate)

          # print 'debug1'
          # mttPredDist_modMass_tagMassSDMinMass.Accumulate( ttMass_modMass_jet1, ak8JetsGood[1].Perp(), topTag1MassSDMinMass, evWeight )
          # print 'debug2'
      # if topTag0MassFat :
      #     # print 'debug3'
      #     if options.verbose:
      #         print '  tagged topTag0MassFat -> Accumulate ( ttmass = '+str(ttMass)+' pt = '+str(ak8JetsGood[1].Perp())+' tagged = '+str(topTag1MassFat)+ ' evWeight '+ str(evWeight)
      #     mttPredDist_tagMassFat        .Accumulate(              ttMass, ak8JetsGood[1].Perp(), topTag1MassFat, evWeight )
      #     # mttPredDist_modMass_tagMassFat.Accumulate( ttMass_modMass_jet1, ak8JetsGood[1].Perp(), topTag1MassFat, evWeight )
      #     bin   = h_mistag_vs_jetPt_TagMassFat.GetXaxis().FindBin( ak8JetsGood[1].Perp() )
      #     rate  = h_mistag_vs_jetPt_TagMassFat.GetBinContent(bin);
      #     h_bkgdEst_tagMassFat .Fill(ttMass, evWeight*rate)
      #if topTag0MassFatMinMass :
          # mttPredDist_tagMassFatMinMass        .Accumulate(              ttMass, ak8JetsGood[1].Perp(), topTag1MassFatMinMass, evWeight )
          # mttPredDist_modMass_tagMassFatMinMass.Accumulate( event.DijetModMassJet1, event.Jet1Pt, topTag1MassFatMinMass, evWeight )
          # do it again with incorrect error bars
          #bin   = h_mistag_vs_jetPt_TagMassFatMinMass.GetXaxis().FindBin( event.Jet1Pt )
          #rate  = h_mistag_vs_jetPt_TagMassFatMinMass.GetBinContent(bin);
          #h_bkgdEst_tagMassFatMinMass               .Fill(   event.DijetMass       , evWeight*rate)
          #h_bkgdEst_modMass_tagMassFatMinMass       .Fill(   event.DijetModMassJet1, evWeight*rate)
          # h_bkgdEst_modMass_flat_tagMassFatMinMass  .Fill( ttMass_modMass_flat_jet1, evWeight*rate)

  # randomly select jet 1 to be the tag then fill predDist based on probability that jet 0 is mis-tagged
  if rand_bkgdest >= 0.5 :
      #if topTag1MassSD :
          # mttPredDist_tagMassSD        .Accumulate(              ttMass, ak8JetsGood[0].Perp(), topTag0MassSD, evWeight )
          # mttPredDist_modMass_tagMassSD.Accumulate( ttMass_modMass_jet0, ak8JetsGood[0].Perp(), topTag0MassSD, evWeight )
          #bin   = h_mistag_vs_jetPt_TagMassSD.GetXaxis().FindBin( event.Jet0Pt )
          #rate  = h_mistag_vs_jetPt_TagMassSD.GetBinContent(bin);
          #h_bkgdEst_tagMassSD              .Fill(    event.DijetMass       , evWeight*rate)
          #h_bkgdEst_modMass_tagMassSD      .Fill(    event.DijetModMassJet0, evWeight*rate)
          # h_bkgdEst_modMass_flat_tagMassSD .Fill(  ttMass_modMass_flat_jet0, evWeight*rate)

      if topTag1MassSDTau32 :
          # mttPredDist_tagMassSDTau32        .Accumulate(              ttMass, ak8JetsGood[0].Perp(), topTag0MassSDTau32, evWeight )
          # mttPredDist_modMass_tagMassSDTau32.Accumulate( ttMass_modMass_jet0, ak8JetsGood[0].Perp(), topTag0MassSDTau32, evWeight )
          for i in xrange(len(post)):
              bin.append (h_mistag_vs_jetPt_TagMassSDTau32[i].GetXaxis().FindBin( event.Jet0Pt ))
              rate.append( h_mistag_vs_jetPt_TagMassSDTau32[i].GetBinContent(bin[i]))
          if event.DijetDeltaRap > 1 :
              #inclusive
              h_bkgdEst_tagMassSDTau32_dRapHi_inclusive              .Fill( event.DijetMass       , evWeight*rate[0])
              h_bkgdEst_modMass_tagMassSDTau32_dRapHi_inclusive      .Fill( event.DijetModMassJet0, evWeight*rate[0])
              if topTag0MaxBdiscM and topTag1MaxBdiscM:
                  #2btag
                  h_bkgdEst_tagMassSDTau32_dRapHi_2btag              .Fill( event.DijetMass       , evWeight*rate[1])
                  h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag      .Fill( event.DijetModMassJet0, evWeight*rate[1])
              if (topTag0MaxBdiscM and not topTag1MaxBdiscM) or (topTag1MaxBdiscM and not topTag0MaxBdiscM):
                  #1btag
                  h_bkgdEst_tagMassSDTau32_dRapHi_1btag              .Fill( event.DijetMass       , evWeight*rate[2])
                  h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag      .Fill( event.DijetModMassJet0, evWeight*rate[2])   
              if not topTag0MaxBdiscM and not topTag1MaxBdiscM:
                  #0btag
                  h_bkgdEst_tagMassSDTau32_dRapHi_0btag              .Fill( event.DijetMass       , evWeight*rate[3])
                  h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag      .Fill( event.DijetModMassJet0, evWeight*rate[3])
          if event.DijetDeltaRap < 1:
              #inclusive
              h_bkgdEst_tagMassSDTau32_dRapLo_inclusive              .Fill( event.DijetMass       , evWeight*rate[4])
              h_bkgdEst_modMass_tagMassSDTau32_dRapLo_inclusive      .Fill( event.DijetModMassJet0, evWeight*rate[4])
              if topTag0MaxBdiscM and topTag1MaxBdiscM:
                  #2btag
                  h_bkgdEst_tagMassSDTau32_dRapLo_2btag              .Fill( event.DijetMass       , evWeight*rate[5])
                  h_bkgdEst_modMass_tagMassSDTau32_dRapLo_2btag      .Fill( event.DijetModMassJet0, evWeight*rate[5])
              if (topTag0MaxBdiscM and not topTag1MaxBdiscM) or (topTag1MaxBdiscM and not topTag0MaxBdiscM):
                  #1btag
                  h_bkgdEst_tagMassSDTau32_dRapLo_1btag              .Fill( event.DijetMass       , evWeight*rate[6])
                  h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag      .Fill( event.DijetModMassJet0, evWeight*rate[6])
              if not topTag0MaxBdiscM and not topTag1MaxBdiscM:
                  #0btag
                  h_bkgdEst_tagMassSDTau32_dRapLo_0btag              .Fill( event.DijetMass       , evWeight*rate[7])
                  h_bkgdEst_modMass_tagMassSDTau32_dRapLo_0btag      .Fill( event.DijetModMassJet0, evWeight*rate[7])
          # h_bkgdEst_modMass_flat_tagMassSDTau32 .Fill(  ttMass_modMass_flat_jet0, evWeight*rate)


      #if topTag1MassSDMinMass :
          # mttPredDist_tagMassSDMinMass        .Accumulate(              ttMass, ak8JetsGood[0].Perp(), topTag0MassSDMinMass, evWeight )
          # mttPredDist_modMass_tagMassSDMinMass.Accumulate( ttMass_modMass_jet0, ak8JetsGood[0].Perp(), topTag0MassSDMinMass, evWeight )
          #bin   = h_mistag_vs_jetPt_TagMassSDMinMass.GetXaxis().FindBin( event.Jet0Pt )
          #rate  = h_mistag_vs_jetPt_TagMassSDMinMass.GetBinContent(bin);
          #h_bkgdEst_tagMassSDMinMass              .Fill(       event.DijetMass       , evWeight*rate)
          #h_bkgdEst_modMass_tagMassSDMinMass      .Fill(       event.DijetModMassJet0, evWeight*rate)
          # h_bkgdEst_modMass_flat_tagMassSDMinMass .Fill(  ttMass_modMass_flat_jet0, evWeight*rate)


      # if topTag1MassFat :
      #     # print 'debug5'
      #     if options.verbose:
      #         print '  tagged topTag1MassFat -> Accumulate ( ttmass = '+str(ttMass)+' pt = '+str(ak8JetsGood[0].Perp())+' tagged = '+str(topTag0MassFat)+ ' evWeight '+ str(evWeight)
      #     mttPredDist_tagMassFat        .Accumulate(              ttMass, ak8JetsGood[0].Perp(), topTag0MassFat, evWeight )
      #     mttPredDist_modMass_tagMassFat.Accumulate( ttMass_modMass_jet0, ak8JetsGood[0].Perp(), topTag0MassFat, evWeight )
      #     bin   = h_mistag_vs_jetPt_TagMassFat.GetXaxis().FindBin( ak8JetsGood[0].Perp() )
      #     rate  = h_mistag_vs_jetPt_TagMassFat.GetBinContent(bin);
      #     h_bkgdEst_tagMassFat .Fill(ttMass, evWeight*rate)
      #if topTag1MassFatMinMass :
          # mttPredDist_tagMassFatMinMass        .Accumulate(              ttMass, ak8JetsGood[0].Perp(), topTag0MassFatMinMass, evWeight )
          # mttPredDist_modMass_tagMassFatMinMass.Accumulate( event.DijetModMassJet0,  event.Jet0Pt, topTag0MassFatMinMass, evWeight )
          # do it again with incorrect error bars
          #bin   = h_mistag_vs_jetPt_TagMassFatMinMass.GetXaxis().FindBin( event.Jet0Pt )
          #rate  = h_mistag_vs_jetPt_TagMassFatMinMass.GetBinContent(bin);
          #h_bkgdEst_tagMassFatMinMass                .Fill(    event.DijetMass       , evWeight*rate)
          #h_bkgdEst_modMass_tagMassFatMinMass        .Fill(    event.DijetModMassJet0, evWeight*rate)
          # h_bkgdEst_modMass_flat_tagMassFatMinMass   .Fill(ttMass_modMass_flat_jet0, evWeight*rate)

   

OUT.cd()

h_mttMass_tagMassSD                              .Write()
h_mttMass_tagMassSDTau32_dRapHi_inclusive        .Write()
h_mttMass_tagMassSDTau32_dRapHi_2btag            .Write()
h_mttMass_tagMassSDTau32_dRapHi_1btag            .Write()
h_mttMass_tagMassSDTau32_dRapHi_0btag            .Write()
h_mttMass_tagMassSDTau32_dRapLo_inclusive        .Write()
h_mttMass_tagMassSDTau32_dRapLo_2btag            .Write()
h_mttMass_tagMassSDTau32_dRapLo_1btag            .Write()
h_mttMass_tagMassSDTau32_dRapLo_0btag            .Write()
h_mttMass_tagMassSDMinMass                       .Write()
h_mttMass_tagMassFat                             .Write()
h_mttMass_tagMassFatMinMass                      .Write()
h_bkgdEst_tagMassSD                              .Write()
h_bkgdEst_tagMassSDTau32_dRapHi_inclusive        .Write()
h_bkgdEst_tagMassSDTau32_dRapHi_2btag            .Write()
h_bkgdEst_tagMassSDTau32_dRapHi_1btag            .Write()
h_bkgdEst_tagMassSDTau32_dRapHi_0btag            .Write()
h_bkgdEst_tagMassSDTau32_dRapLo_inclusive        .Write()
h_bkgdEst_tagMassSDTau32_dRapLo_2btag            .Write()
h_bkgdEst_tagMassSDTau32_dRapLo_1btag            .Write()
h_bkgdEst_tagMassSDTau32_dRapLo_0btag            .Write()
h_bkgdEst_tagMassSDMinMass                       .Write()
h_bkgdEst_tagMassFat                             .Write()
h_bkgdEst_tagMassFatMinMass                      .Write()
h_bkgdEst_modMass_tagMassSD                      .Write()
h_bkgdEst_modMass_tagMassSDTau32_dRapHi_inclusive.Write()
h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag    .Write()
h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag    .Write()
h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag    .Write()
h_bkgdEst_modMass_tagMassSDTau32_dRapLo_inclusive.Write()
h_bkgdEst_modMass_tagMassSDTau32_dRapLo_2btag    .Write() 
h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag    .Write()
h_bkgdEst_modMass_tagMassSDTau32_dRapLo_0btag    .Write()
h_bkgdEst_modMass_tagMassSDMinMass               .Write()
h_bkgdEst_modMass_tagMassFat                     .Write()
h_bkgdEst_modMass_tagMassFatMinMass              .Write()

OUT.Write()
OUT.Close()

