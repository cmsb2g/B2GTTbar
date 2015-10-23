#! /usr/bin/env python
import ROOT

OUT =  ROOT.TFile("outAntiTag_JetHT_Run2015D_PromptReco-v4_oct19json_jdolen_all.root","RECREATE");
F1   =  ROOT.TFile("outNTR_JetHT_Run2015D_PromptReco-v4_oct19json_jdolen_all.root");
Tree = F1.Get("TreeAllHad");
entries = Tree.GetEntries();
print 'entries '+str(entries)  


#^ Make mistag plots

h_AntiTagNone_ReqTopMassSD_Probe_jetPt                   = ROOT.TH1D( "h_AntiTagNone_ReqTopMassSD_Probe_jetPt"                  , "", 1400, 0, 7000 ) 
h_AntiTagNone_ReqTopMassSD_TagMassSD_jetPt               = ROOT.TH1D( "h_AntiTagNone_ReqTopMassSD_TagMassSD_jetPt"              , "", 1400, 0, 7000 ) 
h_AntiTagNone_ReqTopMassSD_TagMassSDTau32_jetPt          = ROOT.TH1D( "h_AntiTagNone_ReqTopMassSD_TagMassSDTau32_jetPt"         , "", 1400, 0, 7000 ) 
h_AntiTagNone_ReqTopMassSD_TagMassSDMinMass_jetPt        = ROOT.TH1D( "h_AntiTagNone_ReqTopMassSD_TagMassSDMinMass_jetPt"       , "", 1400, 0, 7000 ) 
h_AntiTagNone_ReqTopMassSD_TagMassFat_jetPt              = ROOT.TH1D( "h_AntiTagNone_ReqTopMassSD_TagMassFat_jetPt"             , "", 1400, 0, 7000 ) 
h_AntiTagNone_ReqTopMassSD_TagMassFatMinMass_jetPt       = ROOT.TH1D( "h_AntiTagNone_ReqTopMassSD_TagMassFatMinMass_jetPt"      , "", 1400, 0, 7000 ) 
     
h_AntiTagNone_ReqTopMassFat_Probe_jetPt                  = ROOT.TH1D("h_AntiTagNone_ReqTopMassFat_Probe_jetPt"                  , "", 1400, 0, 7000 ) 
h_AntiTagNone_ReqTopMassFat_TagMassSD_jetPt              = ROOT.TH1D("h_AntiTagNone_ReqTopMassFat_TagMassSD_jetPt"              , "", 1400, 0, 7000 ) 
h_AntiTagNone_ReqTopMassFat_TagMassSDTau32_jetPt         = ROOT.TH1D("h_AntiTagNone_ReqTopMassFat_TagMassSDTau32_jetPt"         , "", 1400, 0, 7000 ) 
h_AntiTagNone_ReqTopMassFat_TagMassSDMinMass_jetPt       = ROOT.TH1D("h_AntiTagNone_ReqTopMassFat_TagMassSDMinMass_jetPt"       , "", 1400, 0, 7000 ) 
h_AntiTagNone_ReqTopMassFat_TagMassFat_jetPt             = ROOT.TH1D("h_AntiTagNone_ReqTopMassFat_TagMassFat_jetPt"             , "", 1400, 0, 7000 ) 
h_AntiTagNone_ReqTopMassFat_TagMassFatMinMass_jetPt      = ROOT.TH1D("h_AntiTagNone_ReqTopMassFat_TagMassFatMinMass_jetPt"      , "", 1400, 0, 7000 ) 


h_AntiTagMinMass30_ReqTopMassSD_Probe_jetPt              = ROOT.TH1D( "h_AntiTagMinMass30_ReqTopMassSD_Probe_jetPt"             , "", 1400, 0, 7000 ) 
h_AntiTagMinMass30_ReqTopMassSD_TagMassSD_jetPt          = ROOT.TH1D( "h_AntiTagMinMass30_ReqTopMassSD_TagMassSD_jetPt"         , "", 1400, 0, 7000 ) 
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32_jetPt     = ROOT.TH1D( "h_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32_jetPt"    , "", 1400, 0, 7000 ) 
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMinMass_jetPt   = ROOT.TH1D( "h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMinMass_jetPt"  , "", 1400, 0, 7000 ) 
h_AntiTagMinMass30_ReqTopMassSD_TagMassFat_jetPt         = ROOT.TH1D( "h_AntiTagMinMass30_ReqTopMassSD_TagMassFat_jetPt"        , "", 1400, 0, 7000 ) 
h_AntiTagMinMass30_ReqTopMassSD_TagMassFatMinMass_jetPt  = ROOT.TH1D( "h_AntiTagMinMass30_ReqTopMassSD_TagMassFatMinMass_jetPt" , "", 1400, 0, 7000 ) 

h_AntiTagMinMass30_ReqTopMassFat_Probe_jetPt             = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassFat_Probe_jetPt"             , "", 1400, 0, 7000 ) 
h_AntiTagMinMass30_ReqTopMassFat_TagMassSD_jetPt         = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassFat_TagMassSD_jetPt"         , "", 1400, 0, 7000 ) 
h_AntiTagMinMass30_ReqTopMassFat_TagMassSDTau32_jetPt    = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassFat_TagMassSDTau32_jetPt"    , "", 1400, 0, 7000 ) 
h_AntiTagMinMass30_ReqTopMassFat_TagMassSDMinMass_jetPt  = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassFat_TagMassSDMinMass_jetPt"  , "", 1400, 0, 7000 ) 
h_AntiTagMinMass30_ReqTopMassFat_TagMassFat_jetPt        = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassFat_TagMassFat_jetPt"        , "", 1400, 0, 7000 ) 
h_AntiTagMinMass30_ReqTopMassFat_TagMassFatMinMass_jetPt = ROOT.TH1D("h_AntiTagMinMass30_ReqTopMassFat_TagMassFatMinMass_jetPt" , "", 1400, 0, 7000 ) 

 
h_AntiTagMinMass50_ReqTopMassSD_Probe_jetPt              = ROOT.TH1D( "h_AntiTagMinMass50_ReqTopMassSD_Probe_jetPt"             , "", 1400, 0, 7000 ) 
h_AntiTagMinMass50_ReqTopMassSD_TagMassSD_jetPt          = ROOT.TH1D( "h_AntiTagMinMass50_ReqTopMassSD_TagMassSD_jetPt"         , "", 1400, 0, 7000 ) 
h_AntiTagMinMass50_ReqTopMassSD_TagMassSDTau32_jetPt     = ROOT.TH1D( "h_AntiTagMinMass50_ReqTopMassSD_TagMassSDTau32_jetPt"    , "", 1400, 0, 7000 ) 
h_AntiTagMinMass50_ReqTopMassSD_TagMassSDMinMass_jetPt   = ROOT.TH1D( "h_AntiTagMinMass50_ReqTopMassSD_TagMassSDMinMass_jetPt"  , "", 1400, 0, 7000 ) 
h_AntiTagMinMass50_ReqTopMassSD_TagMassFat_jetPt         = ROOT.TH1D( "h_AntiTagMinMass50_ReqTopMassSD_TagMassFat_jetPt"        , "", 1400, 0, 7000 ) 
h_AntiTagMinMass50_ReqTopMassSD_TagMassFatMinMass_jetPt  = ROOT.TH1D( "h_AntiTagMinMass50_ReqTopMassSD_TagMassFatMinMass_jetPt" , "", 1400, 0, 7000 ) 

h_AntiTagMinMass50_ReqTopMassFat_Probe_jetPt             = ROOT.TH1D("h_AntiTagMinMass50_ReqTopMassFat_Probe_jetPt"             , "", 1400, 0, 7000 ) 
h_AntiTagMinMass50_ReqTopMassFat_TagMassSD_jetPt         = ROOT.TH1D("h_AntiTagMinMass50_ReqTopMassFat_TagMassSD_jetPt"         , "", 1400, 0, 7000 ) 
h_AntiTagMinMass50_ReqTopMassFat_TagMassSDTau32_jetPt    = ROOT.TH1D("h_AntiTagMinMass50_ReqTopMassFat_TagMassSDTau32_jetPt"    , "", 1400, 0, 7000 ) 
h_AntiTagMinMass50_ReqTopMassFat_TagMassSDMinMass_jetPt  = ROOT.TH1D("h_AntiTagMinMass50_ReqTopMassFat_TagMassSDMinMass_jetPt"  , "", 1400, 0, 7000 ) 
h_AntiTagMinMass50_ReqTopMassFat_TagMassFat_jetPt        = ROOT.TH1D("h_AntiTagMinMass50_ReqTopMassFat_TagMassFat_jetPt"        , "", 1400, 0, 7000 ) 
h_AntiTagMinMass50_ReqTopMassFat_TagMassFatMinMass_jetPt = ROOT.TH1D("h_AntiTagMinMass50_ReqTopMassFat_TagMassFatMinMass_jetPt" , "", 1400, 0, 7000 ) 


h_AntiTagTau32_ReqTopMassSD_Probe_jetPt                  = ROOT.TH1D( "h_AntiTagTau32_ReqTopMassSD_Probe_jetPt"                 , "", 1400, 0, 7000 ) 
h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetPt              = ROOT.TH1D( "h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetPt"             , "", 1400, 0, 7000 ) 
h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt         = ROOT.TH1D( "h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt"        , "", 1400, 0, 7000 ) 
h_AntiTagTau32_ReqTopMassSD_TagMassSDMinMass_jetPt       = ROOT.TH1D( "h_AntiTagTau32_ReqTopMassSD_TagMassSDMinMass_jetPt"      , "", 1400, 0, 7000 ) 
h_AntiTagTau32_ReqTopMassSD_TagMassFat_jetPt             = ROOT.TH1D( "h_AntiTagTau32_ReqTopMassSD_TagMassFat_jetPt"            , "", 1400, 0, 7000 ) 
h_AntiTagTau32_ReqTopMassSD_TagMassFatMinMass_jetPt      = ROOT.TH1D( "h_AntiTagTau32_ReqTopMassSD_TagMassFatMinMass_jetPt"     , "", 1400, 0, 7000 ) 
    
h_AntiTagTau32_ReqTopMassFat_Probe_jetPt                 = ROOT.TH1D("h_AntiTagTau32_ReqTopMassFat_Probe_jetPt"                 , "", 1400, 0, 7000 ) 
h_AntiTagTau32_ReqTopMassFat_TagMassSD_jetPt             = ROOT.TH1D("h_AntiTagTau32_ReqTopMassFat_TagMassSD_jetPt"             , "", 1400, 0, 7000 ) 
h_AntiTagTau32_ReqTopMassFat_TagMassSDTau32_jetPt        = ROOT.TH1D("h_AntiTagTau32_ReqTopMassFat_TagMassSDTau32_jetPt"        , "", 1400, 0, 7000 ) 
h_AntiTagTau32_ReqTopMassFat_TagMassSDMinMass_jetPt      = ROOT.TH1D("h_AntiTagTau32_ReqTopMassFat_TagMassSDMinMass_jetPt"      , "", 1400, 0, 7000 ) 
h_AntiTagTau32_ReqTopMassFat_TagMassFat_jetPt            = ROOT.TH1D("h_AntiTagTau32_ReqTopMassFat_TagMassFat_jetPt"            , "", 1400, 0, 7000 ) 
h_AntiTagTau32_ReqTopMassFat_TagMassFatMinMass_jetPt     = ROOT.TH1D("h_AntiTagTau32_ReqTopMassFat_TagMassFatMinMass_jetPt"     , "", 1400, 0, 7000 ) 


count = 0
for event in Tree:
  count +=1
  if count%1000 ==0:
    print count
  maxBdisc_jet0_ =0
  maxBdisc_jet1_ =0
  # define tags - make sure they are the same as what was used to calculate the mistag
  topTag0MassFat                     = event.Jet0Mass > 140 and event.Jet1Mass< 250
  topTag1MassFat                     = event.Jet1Mass > 140 and event.Jet1Mass< 250
  topTag0MassSD                      = event.Jet0MassSoftDrop > 110 and event.Jet0MassSoftDrop < 210
  topTag1MassSD                      = event.Jet1MassSoftDrop > 110 and event.Jet1MassSoftDrop < 210
  topTag0Tau32                       = event.Jet0Tau32 < 0.61
  topTag1Tau32                       = event.Jet1Tau32 < 0.61
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


  # Many anti-tag definitions
  antiTag0minMass50                       = event.Jet0CMSminMass < 50 
  antiTag1minMass50                       = event.Jet1CMSminMass < 50
  antiTag0minMass30                       = event.Jet0CMSminMass < 30 
  antiTag1minMass30                       = event.Jet1CMSminMass < 30
  antiTag0Tau32                           = event.Jet0Tau32 > 0.61
  antiTag1Tau32                           = event.Jet1Tau32 > 0.61
  # antiTag0MaxBdiscVL                      = maxBdisc_jet0_ < 0.5 # very loose
  # antiTag1MaxBdiscVL                      = maxBdisc_jet1_ < 0.5 # very loose
  # antiTag0MaxBdiscL                       = maxBdisc_jet0_ < 0.605 # CSVv2 loose operating point 2015_06
  # antiTag1MaxBdiscL                       = maxBdisc_jet1_ < 0.605 # CSVv2 loose operating point 2015_06

  antiTag0minMass50_ReqTopMassSD         = topTag0MassSD and antiTag0minMass50
  antiTag1minMass50_ReqTopMassSD         = topTag1MassSD and antiTag1minMass50
  antiTag0minMass30_ReqTopMassSD         = topTag0MassSD and antiTag0minMass30
  antiTag1minMass30_ReqTopMassSD         = topTag1MassSD and antiTag1minMass30
  antiTag0Tau32_ReqTopMassSD             = topTag0MassSD and antiTag0Tau32
  antiTag1Tau32_ReqTopMassSD             = topTag1MassSD and antiTag1Tau32
  # antiTag0MaxBdiscVL_ReqTopMassSD        = topTag0MassSD and antiTag0MaxBdiscVL
  # antiTag1MaxBdiscVL_ReqTopMassSD        = topTag1MassSD and antiTag1MaxBdiscVL
  # antiTag0MaxBdiscL_ReqTopMassSD         = topTag0MassSD and antiTag0MaxBdiscL
  # antiTag1MaxBdiscL_ReqTopMassSD         = topTag1MassSD and antiTag1MaxBdiscL

  antiTag0minMass50_ReqTopMassFat         = topTag0MassFat and antiTag0minMass50
  antiTag1minMass50_ReqTopMassFat         = topTag1MassFat and antiTag1minMass50
  antiTag0minMass30_ReqTopMassFat         = topTag0MassFat and antiTag0minMass30
  antiTag1minMass30_ReqTopMassFat         = topTag1MassFat and antiTag1minMass30
  antiTag0Tau32_ReqTopMassFat             = topTag0MassFat and antiTag0Tau32
  antiTag1Tau32_ReqTopMassFat             = topTag1MassFat and antiTag1Tau32
  # antiTag0MaxBdiscVL_ReqTopMassFat        = topTag0MassFat and antiTag0MaxBdiscVL
  # antiTag1MaxBdiscVL_ReqTopMassFat        = topTag1MassFat and antiTag1MaxBdiscVL
  # antiTag0MaxBdiscL_ReqTopMassFat         = topTag0MassFat and antiTag0MaxBdiscL
  # antiTag1MaxBdiscL_ReqTopMassFat         = topTag1MassFat and antiTag1MaxBdiscL

  evWeight = 1
  rand1 =  ROOT.TRandom3(0)
  rand_mistag  = rand1.Uniform(0,1.0)

  if rand_mistag < 0.5 :
    #----------anti-tag minMass<30, keep jet in SD mass window
    if antiTag0minMass30_ReqTopMassSD:
        h_AntiTagMinMass30_ReqTopMassSD_Probe_jetPt                       .Fill( event.Jet1Pt, evWeight )
        if topTag1MassSD         :  
            h_AntiTagMinMass30_ReqTopMassSD_TagMassSD_jetPt               .Fill( event.Jet1Pt, evWeight )
        if topTag1MassSDTau32    : 
            h_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32_jetPt          .Fill( event.Jet1Pt, evWeight )
        if topTag1MassSDMinMass  :  
            h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMinMass_jetPt        .Fill( event.Jet1Pt, evWeight )
        if topTag1MassSDMaxBdisc : 
            h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMaxBdisc_jetPt       .Fill( event.Jet1Pt, evWeight )
        if topTag1MassFat        :  
            h_AntiTagMinMass30_ReqTopMassSD_TagMassFat_jetPt              .Fill( event.Jet1Pt, evWeight )
        if topTag1MassFatMinMass :  
            h_AntiTagMinMass30_ReqTopMassSD_TagMassFatMinMass_jetPt       .Fill( event.Jet1Pt, evWeight )
    #----------anti-tag minMass<30, keep jet in Fat mass window
    if antiTag0minMass30_ReqTopMassFat:
        h_AntiTagMinMass30_ReqTopMassFat_Probe_jetPt                      .Fill( event.Jet1Pt, evWeight )
        if topTag1MassSD         :  
            h_AntiTagMinMass30_ReqTopMassFat_TagMassSD_jetPt              .Fill( event.Jet1Pt, evWeight )
        if topTag1MassSDTau32    : 
            h_AntiTagMinMass30_ReqTopMassFat_TagMassSDTau32_jetPt         .Fill( event.Jet1Pt, evWeight )
        if topTag1MassSDMinMass  :  
            h_AntiTagMinMass30_ReqTopMassFat_TagMassSDMinMass_jetPt       .Fill( event.Jet1Pt, evWeight )
        if topTag1MassSDMaxBdisc : 
            h_AntiTagMinMass30_ReqTopMassFat_TagMassSDMaxBdisc_jetPt      .Fill( event.Jet1Pt, evWeight )
        if topTag1MassFat        :  
            h_AntiTagMinMass30_ReqTopMassFat_TagMassFat_jetPt             .Fill( event.Jet1Pt, evWeight )
        if topTag1MassFatMinMass :  
            h_AntiTagMinMass30_ReqTopMassFat_TagMassFatMinMass_jetPt      .Fill( event.Jet1Pt, evWeight )
    #----------anti-tag minMass<50, keep jet in SD mass window
    if antiTag0minMass50_ReqTopMassSD:
        h_AntiTagMinMass50_ReqTopMassSD_Probe_jetPt                       .Fill( event.Jet1Pt, evWeight )
        if topTag1MassSD         :  
            h_AntiTagMinMass50_ReqTopMassSD_TagMassSD_jetPt               .Fill( event.Jet1Pt, evWeight )
        if topTag1MassSDTau32    : 
            h_AntiTagMinMass50_ReqTopMassSD_TagMassSDTau32_jetPt          .Fill( event.Jet1Pt, evWeight )
        if topTag1MassSDMinMass  :  
            h_AntiTagMinMass50_ReqTopMassSD_TagMassSDMinMass_jetPt        .Fill( event.Jet1Pt, evWeight )
        if topTag1MassSDMaxBdisc : 
            h_AntiTagMinMass50_ReqTopMassSD_TagMassSDMaxBdisc_jetPt       .Fill( event.Jet1Pt, evWeight )
        if topTag1MassFat        :  
            h_AntiTagMinMass50_ReqTopMassSD_TagMassFat_jetPt              .Fill( event.Jet1Pt, evWeight )
        if topTag1MassFatMinMass :  
            h_AntiTagMinMass50_ReqTopMassSD_TagMassFatMinMass_jetPt       .Fill( event.Jet1Pt, evWeight )
    #----------anti-tag minMass<50, keep jet in Fat mass window
    if antiTag0minMass50_ReqTopMassFat:
        h_AntiTagMinMass50_ReqTopMassFat_Probe_jetPt                      .Fill( event.Jet1Pt, evWeight )
        if topTag1MassSD         :  
            h_AntiTagMinMass50_ReqTopMassFat_TagMassSD_jetPt              .Fill( event.Jet1Pt, evWeight )
        if topTag1MassSDTau32    : 
            h_AntiTagMinMass50_ReqTopMassFat_TagMassSDTau32_jetPt         .Fill( event.Jet1Pt, evWeight )
        if topTag1MassSDMinMass  :  
            h_AntiTagMinMass50_ReqTopMassFat_TagMassSDMinMass_jetPt       .Fill( event.Jet1Pt, evWeight )
        if topTag1MassSDMaxBdisc : 
            h_AntiTagMinMass50_ReqTopMassFat_TagMassSDMaxBdisc_jetPt      .Fill( event.Jet1Pt, evWeight )
        if topTag1MassFat        :  
            h_AntiTagMinMass50_ReqTopMassFat_TagMassFat_jetPt             .Fill( event.Jet1Pt, evWeight )
        if topTag1MassFatMinMass :  
            h_AntiTagMinMass50_ReqTopMassFat_TagMassFatMinMass_jetPt      .Fill( event.Jet1Pt, evWeight )
    #----------anti-tag tau32, keep jet in SD mass window
    if antiTag0Tau32_ReqTopMassSD:
        h_AntiTagTau32_ReqTopMassSD_Probe_jetPt                           .Fill( event.Jet1Pt, evWeight )
        if topTag1MassSD         :  
            h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetPt                   .Fill( event.Jet1Pt, evWeight )
        if topTag1MassSDTau32    : 
            h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt              .Fill( event.Jet1Pt, evWeight )
        if topTag1MassSDMinMass  :  
            h_AntiTagTau32_ReqTopMassSD_TagMassSDMinMass_jetPt            .Fill( event.Jet1Pt, evWeight )
        if topTag1MassSDMaxBdisc : 
            h_AntiTagTau32_ReqTopMassSD_TagMassSDMaxBdisc_jetPt           .Fill( event.Jet1Pt, evWeight )
        if topTag1MassFat        :  
            h_AntiTagTau32_ReqTopMassSD_TagMassFat_jetPt                  .Fill( event.Jet1Pt, evWeight )
        if topTag1MassFatMinMass :  
            h_AntiTagTau32_ReqTopMassSD_TagMassFatMinMass_jetPt           .Fill( event.Jet1Pt, evWeight )
    #----------anti-tag tau32, keep jet in Fat mass window
    if antiTag0Tau32_ReqTopMassFat:
        h_AntiTagTau32_ReqTopMassFat_Probe_jetPt                          .Fill( event.Jet1Pt, evWeight )
        if topTag1MassSD         :  
            h_AntiTagTau32_ReqTopMassFat_TagMassSD_jetPt                  .Fill( event.Jet1Pt, evWeight )
        if topTag1MassSDTau32    : 
            h_AntiTagTau32_ReqTopMassFat_TagMassSDTau32_jetPt             .Fill( event.Jet1Pt, evWeight )
        if topTag1MassSDMinMass  :  
            h_AntiTagTau32_ReqTopMassFat_TagMassSDMinMass_jetPt           .Fill( event.Jet1Pt, evWeight )
        if topTag1MassSDMaxBdisc : 
            h_AntiTagTau32_ReqTopMassFat_TagMassSDMaxBdisc_jetPt          .Fill( event.Jet1Pt, evWeight )
        if topTag1MassFat        :  
            h_AntiTagTau32_ReqTopMassFat_TagMassFat_jetPt                 .Fill( event.Jet1Pt, evWeight )
        if topTag1MassFatMinMass :  
            h_AntiTagTau32_ReqTopMassFat_TagMassFatMinMass_jetPt          .Fill( event.Jet1Pt, evWeight )

if rand_mistag >= 0.5 :
    #----------anti-tag minMass<30, keep jet in SD mass window
    if antiTag1minMass30_ReqTopMassSD:
        h_AntiTagMinMass30_ReqTopMassSD_Probe_jetPt                       .Fill( event.Jet0Pt, evWeight )
        if topTag0MassSD         :  
            h_AntiTagMinMass30_ReqTopMassSD_TagMassSD_jetPt               .Fill( event.Jet0Pt, evWeight )
        if topTag0MassSDTau32    : 
            h_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32_jetPt          .Fill( event.Jet0Pt, evWeight )
        if topTag0MassSDMinMass  :  
            h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMinMass_jetPt        .Fill( event.Jet0Pt, evWeight )
        if topTag0MassSDMaxBdisc : 
            h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMaxBdisc_jetPt       .Fill( event.Jet0Pt, evWeight )
        if topTag0MassFat        :  
            h_AntiTagMinMass30_ReqTopMassSD_TagMassFat_jetPt              .Fill( event.Jet0Pt, evWeight )
        if topTag0MassFatMinMass :  
            h_AntiTagMinMass30_ReqTopMassSD_TagMassFatMinMass_jetPt       .Fill( event.Jet0Pt, evWeight )
    #----------anti-tag minMass<30, keep jet in Fat mass window
    if antiTag1minMass30_ReqTopMassFat:
        h_AntiTagMinMass30_ReqTopMassFat_Probe_jetPt                      .Fill( event.Jet0Pt, evWeight )
        if topTag0MassSD         :  
            h_AntiTagMinMass30_ReqTopMassFat_TagMassSD_jetPt              .Fill( event.Jet0Pt, evWeight )
        if topTag0MassSDTau32    : 
            h_AntiTagMinMass30_ReqTopMassFat_TagMassSDTau32_jetPt         .Fill( event.Jet0Pt, evWeight )
        if topTag0MassSDMinMass  :  
            h_AntiTagMinMass30_ReqTopMassFat_TagMassSDMinMass_jetPt       .Fill( event.Jet0Pt, evWeight )
        if topTag0MassSDMaxBdisc : 
            h_AntiTagMinMass30_ReqTopMassFat_TagMassSDMaxBdisc_jetPt      .Fill( event.Jet0Pt, evWeight )
        if topTag0MassFat        :  
            h_AntiTagMinMass30_ReqTopMassFat_TagMassFat_jetPt             .Fill( event.Jet0Pt, evWeight )
        if topTag0MassFatMinMass :  
            h_AntiTagMinMass30_ReqTopMassFat_TagMassFatMinMass_jetPt      .Fill( event.Jet0Pt, evWeight )
    #----------anti-tag minMass<50, keep jet in SD mass window
    if antiTag1minMass50_ReqTopMassSD:
        h_AntiTagMinMass50_ReqTopMassSD_Probe_jetPt                       .Fill( event.Jet0Pt, evWeight )
        if topTag0MassSD         :  
            h_AntiTagMinMass50_ReqTopMassSD_TagMassSD_jetPt               .Fill( event.Jet0Pt, evWeight )
        if topTag0MassSDTau32    : 
            h_AntiTagMinMass50_ReqTopMassSD_TagMassSDTau32_jetPt          .Fill( event.Jet0Pt, evWeight )
        if topTag0MassSDMinMass  :  
            h_AntiTagMinMass50_ReqTopMassSD_TagMassSDMinMass_jetPt        .Fill( event.Jet0Pt, evWeight )
        if topTag0MassSDMaxBdisc : 
            h_AntiTagMinMass50_ReqTopMassSD_TagMassSDMaxBdisc_jetPt       .Fill( event.Jet0Pt, evWeight )
        if topTag0MassFat        :  
            h_AntiTagMinMass50_ReqTopMassSD_TagMassFat_jetPt              .Fill( event.Jet0Pt, evWeight )
        if topTag0MassFatMinMass :  
            h_AntiTagMinMass50_ReqTopMassSD_TagMassFatMinMass_jetPt       .Fill( event.Jet0Pt, evWeight )
    #----------anti-tag minMass<50, keep jet in Fat mass window
    if antiTag1minMass50_ReqTopMassFat:
        h_AntiTagMinMass50_ReqTopMassFat_Probe_jetPt                      .Fill( event.Jet0Pt, evWeight )
        if topTag0MassSD         :  
            h_AntiTagMinMass50_ReqTopMassFat_TagMassSD_jetPt              .Fill( event.Jet0Pt, evWeight )
        if topTag0MassSDTau32    : 
            h_AntiTagMinMass50_ReqTopMassFat_TagMassSDTau32_jetPt         .Fill( event.Jet0Pt, evWeight )
        if topTag0MassSDMinMass  :  
            h_AntiTagMinMass50_ReqTopMassFat_TagMassSDMinMass_jetPt       .Fill( event.Jet0Pt, evWeight )
        if topTag0MassSDMaxBdisc : 
            h_AntiTagMinMass50_ReqTopMassFat_TagMassSDMaxBdisc_jetPt      .Fill( event.Jet0Pt, evWeight )
        if topTag0MassFat        :  
            h_AntiTagMinMass50_ReqTopMassFat_TagMassFat_jetPt             .Fill( event.Jet0Pt, evWeight )
        if topTag0MassFatMinMass :  
            h_AntiTagMinMass50_ReqTopMassFat_TagMassFatMinMass_jetPt      .Fill( event.Jet0Pt, evWeight )
    #----------anti-tag tau32, keep jet in SD mass window
    if antiTag1Tau32_ReqTopMassSD:
        h_AntiTagTau32_ReqTopMassSD_Probe_jetPt                           .Fill( event.Jet0Pt, evWeight )
        if topTag0MassSD         :  
            h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetPt                   .Fill( event.Jet0Pt, evWeight )
        if topTag0MassSDTau32    : 
            h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt              .Fill( event.Jet0Pt, evWeight )
        if topTag0MassSDMinMass  :  
            h_AntiTagTau32_ReqTopMassSD_TagMassSDMinMass_jetPt            .Fill( event.Jet0Pt, evWeight )
        if topTag0MassSDMaxBdisc : 
            h_AntiTagTau32_ReqTopMassSD_TagMassSDMaxBdisc_jetPt           .Fill( event.Jet0Pt, evWeight )
        if topTag0MassFat        :  
            h_AntiTagTau32_ReqTopMassSD_TagMassFat_jetPt                  .Fill( event.Jet0Pt, evWeight )
        if topTag0MassFatMinMass :  
            h_AntiTagTau32_ReqTopMassSD_TagMassFatMinMass_jetPt           .Fill( event.Jet0Pt, evWeight )
    #----------anti-tag tau32, keep jet in Fat mass window
    if antiTag1Tau32_ReqTopMassFat:
        h_AntiTagTau32_ReqTopMassFat_Probe_jetPt                          .Fill( event.Jet0Pt, evWeight )
        if topTag0MassSD         :  
            h_AntiTagTau32_ReqTopMassFat_TagMassSD_jetPt                  .Fill( event.Jet0Pt, evWeight )
        if topTag0MassSDTau32    : 
            h_AntiTagTau32_ReqTopMassFat_TagMassSDTau32_jetPt             .Fill( event.Jet0Pt, evWeight )
        if topTag0MassSDMinMass  :  
            h_AntiTagTau32_ReqTopMassFat_TagMassSDMinMass_jetPt           .Fill( event.Jet0Pt, evWeight )
        if topTag0MassSDMaxBdisc : 
            h_AntiTagTau32_ReqTopMassFat_TagMassSDMaxBdisc_jetPt          .Fill( event.Jet0Pt, evWeight )
        if topTag0MassFat        :  
            h_AntiTagTau32_ReqTopMassFat_TagMassFat_jetPt                 .Fill( event.Jet0Pt, evWeight )
        if topTag0MassFatMinMass :  
            h_AntiTagTau32_ReqTopMassFat_TagMassFatMinMass_jetPt          .Fill( event.Jet0Pt, evWeight )


OUT.cd()

h_AntiTagNone_ReqTopMassSD_Probe_jetPt                   .Write()
h_AntiTagNone_ReqTopMassSD_TagMassSD_jetPt               .Write()
h_AntiTagNone_ReqTopMassSD_TagMassSDTau32_jetPt          .Write()
h_AntiTagNone_ReqTopMassSD_TagMassSDMinMass_jetPt        .Write()
h_AntiTagNone_ReqTopMassSD_TagMassFat_jetPt              .Write()
h_AntiTagNone_ReqTopMassSD_TagMassFatMinMass_jetPt       .Write()
h_AntiTagNone_ReqTopMassFat_Probe_jetPt                  .Write()
h_AntiTagNone_ReqTopMassFat_TagMassSD_jetPt              .Write()
h_AntiTagNone_ReqTopMassFat_TagMassSDTau32_jetPt         .Write()
h_AntiTagNone_ReqTopMassFat_TagMassSDMinMass_jetPt       .Write()
h_AntiTagNone_ReqTopMassFat_TagMassFat_jetPt             .Write()
h_AntiTagNone_ReqTopMassFat_TagMassFatMinMass_jetPt      .Write()
h_AntiTagMinMass30_ReqTopMassSD_Probe_jetPt              .Write()
h_AntiTagMinMass30_ReqTopMassSD_TagMassSD_jetPt          .Write()
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDTau32_jetPt     .Write()
h_AntiTagMinMass30_ReqTopMassSD_TagMassSDMinMass_jetPt   .Write()
h_AntiTagMinMass30_ReqTopMassSD_TagMassFat_jetPt         .Write()
h_AntiTagMinMass30_ReqTopMassSD_TagMassFatMinMass_jetPt  .Write()
h_AntiTagMinMass30_ReqTopMassFat_Probe_jetPt             .Write()
h_AntiTagMinMass30_ReqTopMassFat_TagMassSD_jetPt         .Write()
h_AntiTagMinMass30_ReqTopMassFat_TagMassSDTau32_jetPt    .Write()
h_AntiTagMinMass30_ReqTopMassFat_TagMassSDMinMass_jetPt  .Write()
h_AntiTagMinMass30_ReqTopMassFat_TagMassFat_jetPt        .Write()
h_AntiTagMinMass30_ReqTopMassFat_TagMassFatMinMass_jetPt .Write()
h_AntiTagMinMass50_ReqTopMassSD_Probe_jetPt              .Write()
h_AntiTagMinMass50_ReqTopMassSD_TagMassSD_jetPt          .Write()
h_AntiTagMinMass50_ReqTopMassSD_TagMassSDTau32_jetPt     .Write()
h_AntiTagMinMass50_ReqTopMassSD_TagMassSDMinMass_jetPt   .Write()
h_AntiTagMinMass50_ReqTopMassSD_TagMassFat_jetPt         .Write()
h_AntiTagMinMass50_ReqTopMassSD_TagMassFatMinMass_jetPt  .Write()
h_AntiTagMinMass50_ReqTopMassFat_Probe_jetPt             .Write()
h_AntiTagMinMass50_ReqTopMassFat_TagMassSD_jetPt         .Write()
h_AntiTagMinMass50_ReqTopMassFat_TagMassSDTau32_jetPt    .Write()
h_AntiTagMinMass50_ReqTopMassFat_TagMassSDMinMass_jetPt  .Write()
h_AntiTagMinMass50_ReqTopMassFat_TagMassFat_jetPt        .Write()
h_AntiTagMinMass50_ReqTopMassFat_TagMassFatMinMass_jetPt .Write()
h_AntiTagTau32_ReqTopMassSD_Probe_jetPt                  .Write()
h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetPt              .Write()
h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt         .Write()
h_AntiTagTau32_ReqTopMassSD_TagMassSDMinMass_jetPt       .Write()
h_AntiTagTau32_ReqTopMassSD_TagMassFat_jetPt             .Write()
h_AntiTagTau32_ReqTopMassSD_TagMassFatMinMass_jetPt      .Write()
h_AntiTagTau32_ReqTopMassFat_Probe_jetPt                 .Write()
h_AntiTagTau32_ReqTopMassFat_TagMassSD_jetPt             .Write()
h_AntiTagTau32_ReqTopMassFat_TagMassSDTau32_jetPt        .Write()
h_AntiTagTau32_ReqTopMassFat_TagMassSDMinMass_jetPt      .Write()
h_AntiTagTau32_ReqTopMassFat_TagMassFat_jetPt            .Write()
h_AntiTagTau32_ReqTopMassFat_TagMassFatMinMass_jetPt     .Write()

OUT.Write()
OUT.Close()

