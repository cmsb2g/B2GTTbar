#! /usr/bin/env python
import ROOT

date = "121615"
jecSys = 1  # jecDn = -1; jecNom = 0; jecUp = +1

if jecSys == 0:
  syst = "jec_nom"
elif jecSys == 1:
  syst = "jec_up"
elif jecSys == -1:
  syst = "jec_dn"

OUT =  ROOT.TFile("outAntiTag_TTpowheg_B2Gv8p4_reader5a85e65_all_"+date+"_"+syst+".root","RECREATE");
F1   =  ROOT.TFile("/eos/uscms/store/user/jdolen/B2GAnaFW/Trees/tree_TTpowheg_B2Gv8p4_reader5a85e65_all.root");



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

for event in Tree:
  count +=1
  if count%1000 ==0:
    print count


  # Get same hists in different files for up/nom/dn
  RawJet0Pt = event.Jet0PtRaw
  RawJet1Pt = event.Jet1PtRaw

  Jet0CorrFactor   = event.Jet0CorrFactor
  Jet0CorrFactorUp = event.Jet0CorrFactorUp
  Jet0CorrFactorDn = event.Jet0CorrFactorDn

  Jet1CorrFactor   = event.Jet1CorrFactor
  Jet1CorrFactorUp = event.Jet1CorrFactorUp
  Jet1CorrFactorDn = event.Jet1CorrFactorDn  

  if jecSys == 0:
      Jet0Pt = RawJet0Pt * Jet0CorrFactor
      Jet1Pt = RawJet1Pt * Jet1CorrFactor
      maxJetHt = event.HT
  elif jecSys == 1:
      Jet0Pt = RawJet0Pt * Jet0CorrFactorUp
      Jet1Pt = RawJet1Pt * Jet1CorrFactorUp
      maxJetHt = event.HT_CorrUp
  elif jecSys == -1:
      Jet0Pt = RawJet0Pt * Jet0CorrFactorDn
      Jet1Pt = RawJet1Pt * Jet1CorrFactorDn
      maxJetHt = event.HT_CorrDn

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
  

  if Jet0Pt < 400 or Jet1Pt < 400:
    continue

  if maxJetHt < 1000:
    continue

  evWeight = 1
  rand1 =  ROOT.TRandom3(0)
  rand_mistag  = rand1.Uniform(0,1.0)

  if rand_mistag < 0.5 :
    #----------anti-tag tau32, keep jet in SD mass window
    if antiTag0Tau32_ReqTopMassSD:
        if event.DijetDeltaRap > 1:
            #inclusive
            h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_inclusive  .Fill( event.Jet1Pt, evWeight )
            if topTag0MaxBdiscM and topTag1MaxBdiscM:
                #2btag
                h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_2btag  .Fill( event.Jet1Pt, evWeight )
            if (topTag0MaxBdiscM and not topTag1MaxBdiscM) or (topTag1MaxBdiscM and not topTag0MaxBdiscM):
                #1btag
                h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_1btag  .Fill( event.Jet1Pt, evWeight )
            if not topTag0MaxBdiscM and not topTag1MaxBdiscM:
                #0btag
                h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_0btag  .Fill( event.Jet1Pt, evWeight )
        if event.DijetDeltaRap < 1:
            #inclusive
            h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_inclusive     .Fill( event.Jet1Pt, evWeight )
            if topTag0MaxBdiscM and topTag1MaxBdiscM:
                #2btag
                h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_2btag     .Fill( event.Jet1Pt, evWeight )
            if (topTag0MaxBdiscM and not topTag1MaxBdiscM) or (topTag1MaxBdiscM and not topTag0MaxBdiscM):
                #1btag
                h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_1btag     .Fill( event.Jet1Pt, evWeight )
            if not topTag0MaxBdiscM and not topTag1MaxBdiscM:
                #0btag
                h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_0btag     .Fill( event.Jet1Pt, evWeight )
        
        if topTag1MassSDTau32    : 
            if event.DijetDeltaRap > 1 :
                #inclusive
                h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_inclusive  .Fill( event.Jet1Pt, evWeight )
                if topTag0MaxBdiscM and topTag1MaxBdiscM:
                    #2btag
                    h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_2btag  .Fill( event.Jet1Pt, evWeight )
                if (topTag0MaxBdiscM and not topTag1MaxBdiscM) or (topTag1MaxBdiscM and not topTag0MaxBdiscM):
                    #1btag
                    h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_1btag  .Fill( event.Jet1Pt, evWeight )
                if not topTag0MaxBdiscM and not topTag1MaxBdiscM:
                    #0btag
                    h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_0btag  .Fill( event.Jet1Pt, evWeight )
            if event.DijetDeltaRap < 1 :
                #inclusive
                h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_inclusive     .Fill( event.Jet1Pt, evWeight )
                if topTag0MaxBdiscM and topTag1MaxBdiscM:
                    #2btag
                    h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_2btag     .Fill( event.Jet1Pt, evWeight )
                if (topTag0MaxBdiscM and not topTag1MaxBdiscM) or (topTag1MaxBdiscM and not topTag0MaxBdiscM):
                    #1btag
                    h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_1btag     .Fill( event.Jet1Pt, evWeight )
                if not topTag0MaxBdiscM and not topTag1MaxBdiscM:
                    #0btag
                    h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_0btag     .Fill( event.Jet1Pt, evWeight )
        
    

if rand_mistag >= 0.5 :
    #----------anti-tag tau32, keep jet in SD mass window
    if antiTag1Tau32_ReqTopMassSD:
        if event.DijetDeltaRap > 1:
            #inclusive
            h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_inclusive  .Fill( event.Jet0Pt, evWeight )
            if topTag0MaxBdiscM and topTag1MaxBdiscM:
                #2btag
                h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_2btag  .Fill( event.Jet0Pt, evWeight )
            if (topTag0MaxBdiscM and not topTag1MaxBdiscM) or (topTag1MaxBdiscM and not topTag0MaxBdiscM):
                #1btag
                h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_1btag  .Fill( event.Jet0Pt, evWeight )
            if not topTag0MaxBdiscM and not topTag1MaxBdiscM:
                #0btag
                h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_0btag  .Fill( event.Jet0Pt, evWeight )
        if event.DijetDeltaRap < 1: 
            #inclusive
            h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_inclusive     .Fill( event.Jet0Pt, evWeight )
            if topTag0MaxBdiscM and topTag1MaxBdiscM:
                #2btag
                h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_2btag     .Fill( event.Jet0Pt, evWeight )
            if (topTag0MaxBdiscM and not topTag1MaxBdiscM) or (topTag1MaxBdiscM and not topTag0MaxBdiscM):
                #1btag
                h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_1btag     .Fill( event.Jet0Pt, evWeight )
            if not topTag0MaxBdiscM and not topTag1MaxBdiscM:
                #0btag
                h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_0btag     .Fill( event.Jet0Pt, evWeight )   
        
        if topTag0MassSDTau32    : 
            if event.DijetDeltaRap > 1 :
                #inclusive
                h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_inclusive  .Fill( event.Jet0Pt, evWeight )
                if topTag0MaxBdiscM and topTag1MaxBdiscM:
                    #2btag
                    h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_2btag  .Fill( event.Jet0Pt, evWeight )
                if (topTag0MaxBdiscM and not topTag1MaxBdiscM) or (topTag1MaxBdiscM and not topTag0MaxBdiscM):
                    #1btag
                    h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_1btag  .Fill( event.Jet0Pt, evWeight )
                if not topTag0MaxBdiscM and not topTag1MaxBdiscM:
                    #0btag
                    h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_0btag  .Fill( event.Jet0Pt, evWeight )
            if event.DijetDeltaRap < 1 :
                #inclusive
                h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_inclusive  .Fill( event.Jet0Pt, evWeight )
                if topTag0MaxBdiscM and topTag1MaxBdiscM:
                    #2btag
                    h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_2btag  .Fill( event.Jet0Pt, evWeight )
                if (topTag0MaxBdiscM and not topTag1MaxBdiscM) or (topTag1MaxBdiscM and not topTag0MaxBdiscM):
                    #1btag
                    h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_1btag  .Fill( event.Jet0Pt, evWeight )
                if not topTag0MaxBdiscM and not topTag1MaxBdiscM:
                    #0btag
                    h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_0btag  .Fill( event.Jet0Pt, evWeight )
    


OUT.cd()

h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_inclusive         .Write()
h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_0btag             .Write()
h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_1btag             .Write()
h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_2btag             .Write()
h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_inclusive         .Write()
h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_0btag             .Write()
h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_1btag             .Write()
h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_2btag             .Write()
h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_inclusive.Write()
h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_0btag    .Write() 
h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_1btag    .Write()
h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_2btag    .Write()
h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_inclusive.Write()
h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_0btag    .Write()
h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_1btag    .Write()
h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_2btag    .Write()


OUT.Write()
OUT.Close()

print "Number of events in h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_inclusive_"+syst+": ", h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_inclusive.GetSum()
print "Number of events in h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_0btag_"+syst+": "    , h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_0btag    .GetSum()         
print "Number of events in h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_1btag_"+syst+": "    , h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_1btag    .GetSum()         
print "Number of events in h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_2btag_"+syst+": "    , h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_2btag    .GetSum()         
print "Summed number of events of dRapHi_0btag + dRapHi_1btag + dRapHi_2btag_"+syst+": "       , h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_0btag.GetSum() + h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_1btag.GetSum() + h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_2btag.GetSum()
print ""
print "Number of events in h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_inclusive_"+syst+": ", h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_inclusive.GetSum()         
print "Number of events in h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_0btag_"+syst+": "    , h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_0btag    .GetSum()         
print "Number of events in h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_1btag_"+syst+": "    , h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_1btag    .GetSum()         
print "Number of events in h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_2btag_"+syst+": "    , h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_2btag    .GetSum() 
print "Summed number of events of dRapLo_0btag + dRapLo_1btag + dRapLo_2btag_"+syst+": "       , h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_0btag.GetSum() + h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_1btag.GetSum() + h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_2btag.GetSum()        





