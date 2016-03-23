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
                  help='Systematic type; jerDn = -2; jecDn = -1; jecNom = 0; jecUp = +1; jerUp = +2; bTagUp = +3; bTagDn = -3; pdfUp = +4; pdfDn = -4; q2Up = +5; q2Dn = -5')

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

#Syst = 0  # jerDn = -2; jecDn = -1; jecNom = 0; jecUp = +1; jerUp = +2; bTagUp = +3; bTagDn = -3; pdfUp = +4; pdfDn = -4; q2Up = +5; q2Dn = -5 
verbose = False

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
elif options.Syst == 4:
  systType = "pdf_up"
elif options.Syst == -4:
  systType = "pdf_dn"
elif options.Syst == 5:
  systType = "q2_up"
elif options.Syst == -5:
  systType = "q2_dn"
print 'systType '+systType

#OUT =  ROOT.TFile("outBkgdEst_JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65_"+date+"_"+systType+".root","RECREATE");
OUT =  ROOT.TFile(options.outname+"_"+options.date+"_"+systType+".root","RECREATE");
#F1   =  ROOT.TFile("/eos/uscms/store/user/jdolen/B2GAnaFW/Trees/JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65.root");
F1   =  ROOT.TFile.Open(options.file);
Tree = F1.Get("TreeAllHad");
entries = Tree.GetEntries();
print 'entries '+str(entries)  





#^ Hadronic mtt selection and background estimaion
h_mttMass_tagMassSDTau32_dRapHi_inclusive = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapHi_inclusive"   , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapHi_0btag     = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapHi_0btag"       , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapHi_1btag     = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapHi_1btag"       , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapHi_2btag     = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapHi_2btag"       , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapLo_inclusive = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapLo_inclusive"   , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapLo_0btag     = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapLo_0btag"       , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapLo_1btag     = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapLo_1btag"       , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapLo_2btag     = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapLo_2btag"       , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapIn_inclusive = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapIn_inclusive"   , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapIn_0btag     = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapIn_0btag"       , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapIn_1btag     = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapIn_1btag"       , "", 700, 0, 7000 )
h_mttMass_tagMassSDTau32_dRapIn_2btag     = ROOT.TH1D("h_mttMass_tagMassSDTau32_dRapIn_2btag"       , "", 700, 0, 7000 )

h_bkgdEst_tagMassSDTau32_dRapHi_inclusive = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapHi_inclusive"    , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapHi_0btag     = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapHi_0btag"        , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapHi_1btag     = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapHi_1btag"        , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapHi_2btag     = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapHi_2btag"        , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapLo_inclusive = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapLo_inclusive"    , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapLo_0btag     = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapLo_0btag"        , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapLo_1btag     = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapLo_1btag"        , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapLo_2btag     = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapLo_2btag"        , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapIn_inclusive = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapIn_inclusive"    , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapIn_0btag     = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapIn_0btag"        , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapIn_1btag     = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapIn_1btag"        , "", 700, 0, 7000 )
h_bkgdEst_tagMassSDTau32_dRapIn_2btag     = ROOT.TH1D("h_bkgdEst_tagMassSDTau32_dRapIn_2btag"        , "", 700, 0, 7000 )

h_bkgdEst_modMass_tagMassSDTau32_dRapHi_inclusive = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapHi_inclusive"    , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag     = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag"        , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag     = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag"        , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag     = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag"        , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapLo_inclusive = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapLo_inclusive"    , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapLo_0btag     = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapLo_0btag"        , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag     = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag"        , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapLo_2btag     = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapLo_2btag"        , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapIn_inclusive = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapIn_inclusive"    , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapIn_0btag     = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapIn_0btag"        , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapIn_1btag     = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapIn_1btag"        , "", 700, 0, 7000 )
h_bkgdEst_modMass_tagMassSDTau32_dRapIn_2btag     = ROOT.TH1D("h_bkgdEst_modMass_tagMassSDTau32_dRapIn_2btag"        , "", 700, 0, 7000 )


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


#Fmistag = ROOT.TFile("MistagRate_nbins_121615_8_ttbar_nom__Substract_outAntiTag_JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65_121615_jec_nom.root")
# Fmistag = ROOT.TFile(options.mistagFile)

Fmistag      = ROOT.TFile("MistagRate_nbins_030716_27_MC_outAntiTagExp_QCD_HT700toInf_B2Gv8p4_reader603e_notrig_fix_030816_nom_scaled.root")
Fmistag_jetP = ROOT.TFile("MistagRate_nbins_030716_13_MC_outAntiTagExp_QCD_HT700toInf_B2Gv8p4_reader603e_notrig_fix_030816_nom_scaled.root")




post = [ "_jetPt_dRapHi_0btag" ,  "_jetPt_dRapHi_1btag" ,  "_jetPt_dRapHi_2btag" , "_jetPt_dRapHi_inclusive" ,   
         "_jetPt_dRapLo_0btag" ,  "_jetPt_dRapLo_1btag" ,  "_jetPt_dRapLo_2btag" , "_jetPt_dRapLo_inclusive" ,   
         "_jetPt_dRapIn_0btag" ,  "_jetPt_dRapIn_1btag",   "_jetPt_dRapIn_2btag" , "_jetPt_dRapIn_inclusive"  
]

post2 = [ "_jetP_dRapHi_0btag" ,  "_jetP_dRapHi_1btag" ,  "_jetP_dRapHi_2btag" , "_jetP_dRapHi_inclusive" ,   
          "_jetP_dRapLo_0btag" ,  "_jetP_dRapLo_1btag" ,  "_jetP_dRapLo_2btag" , "_jetP_dRapLo_inclusive" ,   
          "_jetP_dRapIn_0btag" ,  "_jetP_dRapIn_1btag" ,  "_jetP_dRapIn_2btag" , "_jetP_dRapIn_inclusive"  
]




h_mistag_vs_jetPt_TagMassSDTau32 = []
h_mistag_vs_jetP_TagMassSDTau32 = []
h_mistag_vs_jetP_TagMassSDTau32_OddEvent = []
h_mistag_vs_jetP_TagMassSDTau32_EvenEvent = []
h_mistag_vs_jetPt_TagMassSDTau32_OddEvent = []
h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent = []
h_mistag_vs_jetPt_TagMassSDTau32_AntiTagMinMass = []
h_mistag_vs_jetPt_TagMassSDTau32_NoAntiTag = []
h_mistag_vs_jetPt_TagMassSDTau32_AntiTagTau32_NoMassReq = []
 
for i in xrange(len(post)):
    h_mistag_vs_jetPt_TagMassSDTau32.append( Fmistag.Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32"+ post[i]).Clone())
    ROOT.SetOwnership( h_mistag_vs_jetPt_TagMassSDTau32[i]    , False )
    h_mistag_vs_jetPt_TagMassSDTau32[i]      .SetName("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32"+ post[i]    )
    

    h_mistag_vs_jetPt_TagMassSDTau32_OddEvent.append( Fmistag.Get("h_mistag_TagOdd_TagMassSDTau32"+ post[i]).Clone())
    ROOT.SetOwnership( h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[i]    , False )
    h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[i]      .SetName("h_mistag_TagOdd_TagMassSDTau32"+ post[i]    )
    
    h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent.append( Fmistag.Get("h_mistag_TagEven_TagMassSDTau32"+ post[i]).Clone())
    ROOT.SetOwnership( h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[i]    , False )
    h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[i]      .SetName("h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent_TagMassSDTau32"+ post[i]    )

    h_mistag_vs_jetPt_TagMassSDTau32_AntiTagMinMass.append( Fmistag.Get("h_mistag_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32"+ post[i]).Clone())
    ROOT.SetOwnership( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagMinMass[i]    , False )
    h_mistag_vs_jetPt_TagMassSDTau32_AntiTagMinMass[i]      .SetName("h_mistag_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32"+ post[i]    )

    h_mistag_vs_jetPt_TagMassSDTau32_NoAntiTag.append( Fmistag.Get("h_mistag_NoAntiTag_ReqTopMassSD_TagMassSDTau32"+ post[i]).Clone())
    ROOT.SetOwnership( h_mistag_vs_jetPt_TagMassSDTau32_NoAntiTag[i]    , False )
    h_mistag_vs_jetPt_TagMassSDTau32_NoAntiTag[i]      .SetName("h_mistag_NoAntiTag_ReqTopMassSD_TagMassSDTau32"+ post[i]    )

    h_mistag_vs_jetPt_TagMassSDTau32_AntiTagTau32_NoMassReq.append( Fmistag.Get("h_mistag_AntiTagTau32_NoMassReq_TagMassSDTau32"+ post[i]).Clone())
    ROOT.SetOwnership( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagTau32_NoMassReq[i]    , False )
    h_mistag_vs_jetPt_TagMassSDTau32_AntiTagTau32_NoMassReq[i]      .SetName("h_mistag_AntiTagTau32_NoMassReq_TagMassSDTau32"+ post[i]    )


for i in xrange(len(post2)):    
    h_mistag_vs_jetP_TagMassSDTau32.append( Fmistag_jetP.Get("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32"+ post2[i]).Clone())
    ROOT.SetOwnership( h_mistag_vs_jetP_TagMassSDTau32[i]    , False )
    h_mistag_vs_jetP_TagMassSDTau32[i]      .SetName("h_mistag_AntiTagTau32_ReqTopMassSD_TagMassSDTau32"+ post2[i]    )

    h_mistag_vs_jetP_TagMassSDTau32_OddEvent.append( Fmistag.Get("h_mistag_TagOdd_TagMassSDTau32"+ post2[i]).Clone())
    ROOT.SetOwnership( h_mistag_vs_jetP_TagMassSDTau32_OddEvent[i]    , False )
    h_mistag_vs_jetP_TagMassSDTau32_OddEvent[i]      .SetName("h_mistag_TagOdd_TagMassSDTau32"+ post2[i]    )
    
    h_mistag_vs_jetP_TagMassSDTau32_EvenEvent.append( Fmistag.Get("h_mistag_TagEven_TagMassSDTau32"+ post2[i]).Clone())
    ROOT.SetOwnership( h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[i]    , False )
    h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[i]      .SetName("h_mistag_vs_jetP_TagMassSDTau32_EvenEvent_TagMassSDTau32"+ post2[i]    )
        


# pred_ = []
# for i in xrange(len(post)):
#      pname = "mttPredDist_modMass_tagMassSDTau32"+post[i]
#      p   = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[i],  pname , "mTT Mass", 700, 0, 7000)
#      pred_.append( p )


#^ Predicted Distribution - Background estimation 
mttPredDist_modMass_tagMassSDTau32_dRapHi_0btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[0],  "mttPredDist_modMass_tagMassSDTau32_dRapHi_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_modMass_tagMassSDTau32_dRapHi_1btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[1],  "mttPredDist_modMass_tagMassSDTau32_dRapHi_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_modMass_tagMassSDTau32_dRapHi_2btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[2],  "mttPredDist_modMass_tagMassSDTau32_dRapHi_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_modMass_tagMassSDTau32_dRapHi_inclusive                        = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[3],  "mttPredDist_modMass_tagMassSDTau32_dRapHi_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist_modMass_tagMassSDTau32_dRapLo_0btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[4],  "mttPredDist_modMass_tagMassSDTau32_dRapLo_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_modMass_tagMassSDTau32_dRapLo_1btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[5],  "mttPredDist_modMass_tagMassSDTau32_dRapLo_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_modMass_tagMassSDTau32_dRapLo_2btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[6],  "mttPredDist_modMass_tagMassSDTau32_dRapLo_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_modMass_tagMassSDTau32_dRapLo_inclusive                        = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[7],  "mttPredDist_modMass_tagMassSDTau32_dRapLo_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist_modMass_tagMassSDTau32_dRapIn_0btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[8],  "mttPredDist_modMass_tagMassSDTau32_dRapIn_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_modMass_tagMassSDTau32_dRapIn_1btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[9],  "mttPredDist_modMass_tagMassSDTau32_dRapIn_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_modMass_tagMassSDTau32_dRapIn_2btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[10], "mttPredDist_modMass_tagMassSDTau32_dRapIn_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_modMass_tagMassSDTau32_dRapIn_inclusive                        = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[11], "mttPredDist_modMass_tagMassSDTau32_dRapIn_inclusive"      , "mTT Mass", 700, 0, 7000)


mttPredDist_tagMassSDTau32_dRapHi_DijetMass_0btag                          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[0], "mttPredDist_tagMassSDTau32_dRapHi_DijetMass_0btag"        , "mTT Mass"     , 700,  0, 7000 )
mttPredDist_tagMassSDTau32_dRapHi_JetMass_0btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[0], "mttPredDist_tagMassSDTau32_dRapHi_JetMass_0btag"          , "Jet Mass"     , 500,  0,  500 )
mttPredDist_tagMassSDTau32_dRapHi_JetPt_0btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[0], "mttPredDist_tagMassSDTau32_dRapHi_JetPt_0btag"            , "Jet pT"       , 400,  0, 4000 )
mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_0btag                        = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[0], "mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_0btag"      , "Jet Rapidity" , 600, -3,    3 )
mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_0btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[0], "mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_0btag"     , "SoftDrop Mass", 500,  0,  500 )
mttPredDist_tagMassSDTau32_dRapHi_Tau32_0btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[0], "mttPredDist_tagMassSDTau32_dRapHi_Tau32_0btag"            , "Tau32"        , 500,  0,    1 )
mttPredDist_tagMassSDTau32_dRapHi_bDisc_0btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[0], "mttPredDist_tagMassSDTau32_dRapHi_bDisc_0btag"            , "bDisc"        , 500,  0,    1 )

mttPredDist_tagMassSDTau32_dRapHi_DijetMass_1btag                          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[1], "mttPredDist_tagMassSDTau32_dRapHi_DijetMass_1btag"        , "mTT Mass"     , 700,  0, 7000 )
mttPredDist_tagMassSDTau32_dRapHi_JetMass_1btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[1], "mttPredDist_tagMassSDTau32_dRapHi_JetMass_1btag"          , "Jet Mass"     , 500,  0,  500 )
mttPredDist_tagMassSDTau32_dRapHi_JetPt_1btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[1], "mttPredDist_tagMassSDTau32_dRapHi_JetPt_1btag"            , "Jet pT"       , 400,  0, 4000 )
mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_1btag                        = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[1], "mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_1btag"      , "Jet Rapidity" , 600, -3,    3 )
mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_1btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[1], "mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_1btag"     , "SoftDrop Mass", 500,  0,  500 )
mttPredDist_tagMassSDTau32_dRapHi_Tau32_1btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[1], "mttPredDist_tagMassSDTau32_dRapHi_Tau32_1btag"            , "Tau32"        , 500,  0,    1 )
mttPredDist_tagMassSDTau32_dRapHi_bDisc_1btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[1], "mttPredDist_tagMassSDTau32_dRapHi_bDisc_1btag"            , "bDisc"        , 500,  0,    1 )

mttPredDist_tagMassSDTau32_dRapHi_DijetMass_2btag                          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[2], "mttPredDist_tagMassSDTau32_dRapHi_DijetMass_2btag"        , "mTT Mass"     , 700,  0, 7000 )
mttPredDist_tagMassSDTau32_dRapHi_JetMass_2btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[2], "mttPredDist_tagMassSDTau32_dRapHi_JetMass_2btag"          , "Jet Mass"     , 500,  0,  500 )
mttPredDist_tagMassSDTau32_dRapHi_JetPt_2btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[2], "mttPredDist_tagMassSDTau32_dRapHi_JetPt_2btag"            , "Jet pT"       , 400,  0, 4000 )
mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_2btag                        = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[2], "mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_2btag"      , "Jet Rapidity" , 600, -3,    3 )
mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_2btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[2], "mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_2btag"     , "SoftDrop Mass", 500,  0,  500 )
mttPredDist_tagMassSDTau32_dRapHi_Tau32_2btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[2], "mttPredDist_tagMassSDTau32_dRapHi_Tau32_2btag"            , "Tau32"        , 500,  0,    1 )
mttPredDist_tagMassSDTau32_dRapHi_bDisc_2btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[2], "mttPredDist_tagMassSDTau32_dRapHi_bDisc_2btag"            , "bDisc"        , 500,  0,    1 )

mttPredDist_tagMassSDTau32_dRapHi_DijetMass_inclusive                      = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[3], "mttPredDist_tagMassSDTau32_dRapHi_DijetMass_inclusive"    , "mTT Mass"     , 700,  0, 7000 )
mttPredDist_tagMassSDTau32_dRapHi_JetMass_inclusive                        = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[3], "mttPredDist_tagMassSDTau32_dRapHi_JetMass_inclusive"      , "Jet Mass"     , 500,  0,  500 ) 
mttPredDist_tagMassSDTau32_dRapHi_JetPt_inclusive                          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[3], "mttPredDist_tagMassSDTau32_dRapHi_JetPt_inclusive"        , "Jet pT"       , 400,  0, 4000 )
mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_inclusive                    = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[3], "mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_inclusive"  , "Jet Rapidity" , 600, -3,    3 )
mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_inclusive                   = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[3], "mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_inclusive" , "SoftDrop Mass", 500,  0,  500 )
mttPredDist_tagMassSDTau32_dRapHi_Tau32_inclusive                          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[3], "mttPredDist_tagMassSDTau32_dRapHi_Tau32_inclusive"        , "Tau32"        , 500,  0,    1 )
mttPredDist_tagMassSDTau32_dRapHi_bDisc_inclusive                          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[3], "mttPredDist_tagMassSDTau32_dRapHi_bDisc_inclusive"        , "bDisc"        , 500,  0,    1 )


mttPredDist_tagMassSDTau32_dRapLo_DijetMass_0btag                          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[4], "mttPredDist_tagMassSDTau32_dRapLo_DijetMass_0btag"        , "mTT Mass"     , 700,  0, 7000 )
mttPredDist_tagMassSDTau32_dRapLo_JetMass_0btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[4], "mttPredDist_tagMassSDTau32_dRapLo_JetMass_0btag"          , "Jet Mass"     , 500,  0,  500 )
mttPredDist_tagMassSDTau32_dRapLo_JetPt_0btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[4], "mttPredDist_tagMassSDTau32_dRapLo_JetPt_0btag"            , "Jet pT"       , 400,  0, 4000 )
mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_0btag                        = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[4], "mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_0btag"      , "Jet Rapidity" , 600, -3,    3 )
mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_0btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[4], "mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_0btag"     , "SoftDrop Mass", 500,  0,  500 )
mttPredDist_tagMassSDTau32_dRapLo_Tau32_0btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[4], "mttPredDist_tagMassSDTau32_dRapLo_Tau32_0btag"            , "Tau32"        , 500,  0,    1 )
mttPredDist_tagMassSDTau32_dRapLo_bDisc_0btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[4], "mttPredDist_tagMassSDTau32_dRapLo_bDisc_0btag"            , "bDisc"        , 500,  0,    1 )

mttPredDist_tagMassSDTau32_dRapLo_DijetMass_1btag                          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[5], "mttPredDist_tagMassSDTau32_dRapLo_DijetMass_1btag"        , "mTT Mass"     , 700,  0, 7000 )
mttPredDist_tagMassSDTau32_dRapLo_JetMass_1btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[5], "mttPredDist_tagMassSDTau32_dRapLo_JetMass_1btag"          , "Jet Mass"     , 500,  0,  500 )
mttPredDist_tagMassSDTau32_dRapLo_JetPt_1btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[5], "mttPredDist_tagMassSDTau32_dRapLo_JetPt_1btag"            , "Jet pT"       , 400,  0, 4000 )
mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_1btag                        = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[5], "mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_1btag"      , "Jet Rapidity" , 600, -3,    3 )
mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_1btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[5], "mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_1btag"     , "SoftDrop Mass", 500,  0,  500 )
mttPredDist_tagMassSDTau32_dRapLo_Tau32_1btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[5], "mttPredDist_tagMassSDTau32_dRapLo_Tau32_1btag"            , "Tau32"        , 500,  0,    1 )
mttPredDist_tagMassSDTau32_dRapLo_bDisc_1btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[5], "mttPredDist_tagMassSDTau32_dRapLo_bDisc_1btag"            , "bDisc"        , 500,  0,    1 )

mttPredDist_tagMassSDTau32_dRapLo_DijetMass_2btag                          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[6], "mttPredDist_tagMassSDTau32_dRapLo_DijetMass_2btag"        , "mTT Mass"     , 700,  0, 7000 )
mttPredDist_tagMassSDTau32_dRapLo_JetMass_2btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[6], "mttPredDist_tagMassSDTau32_dRapLo_JetMass_2btag"          , "Jet Mass"     , 500,  0,  500 )
mttPredDist_tagMassSDTau32_dRapLo_JetPt_2btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[6], "mttPredDist_tagMassSDTau32_dRapLo_JetPt_2btag"            , "Jet pT"       , 400,  0, 4000 )
mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_2btag                        = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[6], "mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_2btag"      , "Jet Rapidity" , 600, -3,    3 )
mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_2btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[6], "mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_2btag"     , "SoftDrop Mass", 500,  0,  500 )
mttPredDist_tagMassSDTau32_dRapLo_Tau32_2btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[6], "mttPredDist_tagMassSDTau32_dRapLo_Tau32_2btag"            , "Tau32"        , 500,  0,    1 )
mttPredDist_tagMassSDTau32_dRapLo_bDisc_2btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[6], "mttPredDist_tagMassSDTau32_dRapLo_bDisc_2btag"            , "bDisc"        , 500,  0,    1 )

mttPredDist_tagMassSDTau32_dRapLo_DijetMass_inclusive                      = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[7], "mttPredDist_tagMassSDTau32_dRapLo_DijetMass_inclusive"    , "mTT Mass"     , 700,  0, 7000 )
mttPredDist_tagMassSDTau32_dRapLo_JetMass_inclusive                        = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[7], "mttPredDist_tagMassSDTau32_dRapLo_JetMass_inclusive"      , "Jet Mass"     , 500,  0,  500 )
mttPredDist_tagMassSDTau32_dRapLo_JetPt_inclusive                          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[7], "mttPredDist_tagMassSDTau32_dRapLo_JetPt_inclusive"        , "Jet pT"       , 400,  0, 4000 )
mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_inclusive                    = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[7], "mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_inclusive"  , "Jet Rapidity" , 600, -3,    3 )
mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_inclusive                   = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[7], "mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_inclusive" , "SoftDrop Mass", 500,  0,  500 )
mttPredDist_tagMassSDTau32_dRapLo_Tau32_inclusive                          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[7], "mttPredDist_tagMassSDTau32_dRapLo_Tau32_inclusive"        , "Tau32"        , 500,  0,    1 )
mttPredDist_tagMassSDTau32_dRapLo_bDisc_inclusive                          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[7], "mttPredDist_tagMassSDTau32_dRapLo_bDisc_inclusive"        , "bDisc"        , 500,  0,    1 )


mttPredDist_tagMassSDTau32_dRapIn_DijetMass_0btag                          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[8], "mttPredDist_tagMassSDTau32_dRapIn_DijetMass_0btag"        , "mTT Mass"     , 700,  0, 7000 )
mttPredDist_tagMassSDTau32_dRapIn_JetMass_0btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[8], "mttPredDist_tagMassSDTau32_dRapIn_JetMass_0btag"          , "Jet Mass"     , 500,  0,  500 )
mttPredDist_tagMassSDTau32_dRapIn_JetPt_0btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[8], "mttPredDist_tagMassSDTau32_dRapIn_JetPt_0btag"            , "Jet pT"       , 400,  0, 4000 )
mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_0btag                        = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[8], "mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_0btag"      , "Jet Rapidity" , 600, -3,    3 )
mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_0btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[8], "mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_0btag"     , "SoftDrop Mass", 500,  0,  500 )
mttPredDist_tagMassSDTau32_dRapIn_Tau32_0btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[8], "mttPredDist_tagMassSDTau32_dRapIn_Tau32_0btag"            , "Tau32"        , 500,  0,    1 )
mttPredDist_tagMassSDTau32_dRapIn_bDisc_0btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[8], "mttPredDist_tagMassSDTau32_dRapIn_bDisc_0btag"            , "bDisc"        , 500,  0,    1 )

mttPredDist_tagMassSDTau32_dRapIn_DijetMass_1btag                          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[9], "mttPredDist_tagMassSDTau32_dRapIn_DijetMass_1btag"        , "mTT Mass"     , 700,  0, 7000 )
mttPredDist_tagMassSDTau32_dRapIn_JetMass_1btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[9], "mttPredDist_tagMassSDTau32_dRapIn_JetMass_1btag"          , "Jet Mass"     , 500,  0,  500 )
mttPredDist_tagMassSDTau32_dRapIn_JetPt_1btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[9], "mttPredDist_tagMassSDTau32_dRapIn_JetPt_1btag"            , "Jet pT"       , 400,  0, 4000 )
mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_1btag                        = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[9], "mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_1btag"      , "Jet Rapidity" , 600, -3,    3 )
mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_1btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[9], "mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_1btag"     , "SoftDrop Mass", 500,  0,  500 )
mttPredDist_tagMassSDTau32_dRapIn_Tau32_1btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[9], "mttPredDist_tagMassSDTau32_dRapIn_Tau32_1btag"            , "Tau32"        , 500,  0,    1 )
mttPredDist_tagMassSDTau32_dRapIn_bDisc_1btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[9], "mttPredDist_tagMassSDTau32_dRapIn_bDisc_1btag"            , "bDisc"        , 500,  0,    1 )

mttPredDist_tagMassSDTau32_dRapIn_DijetMass_2btag                          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[10], "mttPredDist_tagMassSDTau32_dRapIn_DijetMass_2btag"        , "mTT Mass"     , 700,  0, 7000 )
mttPredDist_tagMassSDTau32_dRapIn_JetMass_2btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[10], "mttPredDist_tagMassSDTau32_dRapIn_JetMass_2btag"          , "Jet Mass"     , 500,  0,  500 )
mttPredDist_tagMassSDTau32_dRapIn_JetPt_2btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[10], "mttPredDist_tagMassSDTau32_dRapIn_JetPt_2btag"            , "Jet pT"       , 400,  0, 4000 )
mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_2btag                        = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[10], "mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_2btag"      , "Jet Rapidity" , 600, -3,    3 )
mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_2btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[10], "mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_2btag"     , "SoftDrop Mass", 500,  0,  500 )
mttPredDist_tagMassSDTau32_dRapIn_Tau32_2btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[10], "mttPredDist_tagMassSDTau32_dRapIn_Tau32_2btag"            , "Tau32"        , 500,  0,    1 )
mttPredDist_tagMassSDTau32_dRapIn_bDisc_2btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[10], "mttPredDist_tagMassSDTau32_dRapIn_bDisc_2btag"            , "bDisc"        , 500,  0,    1 )

mttPredDist_tagMassSDTau32_dRapIn_DijetMass_inclusive                      = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[11], "mttPredDist_tagMassSDTau32_dRapIn_DijetMass_inclusive"    , "mTT Mass"     , 700,  0, 7000 )
mttPredDist_tagMassSDTau32_dRapIn_JetMass_inclusive                        = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[11], "mttPredDist_tagMassSDTau32_dRapIn_JetMass_inclusive"      , "Jet Mass"     , 500,  0,  500 )
mttPredDist_tagMassSDTau32_dRapIn_JetPt_inclusive                          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[11], "mttPredDist_tagMassSDTau32_dRapIn_JetPt_inclusive"        , "Jet pT"       , 400,  0, 4000 )
mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_inclusive                    = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[11], "mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_inclusive"  , "Jet Rapidity" , 600, -3,    3 )
mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_inclusive                   = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[11], "mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_inclusive" , "SoftDrop Mass", 500,  0,  500 )
mttPredDist_tagMassSDTau32_dRapIn_Tau32_inclusive                          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[11], "mttPredDist_tagMassSDTau32_dRapIn_Tau32_inclusive"        , "Tau32"        , 500,  0,    1 )
mttPredDist_tagMassSDTau32_dRapIn_bDisc_inclusive                          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32[11], "mttPredDist_tagMassSDTau32_dRapIn_bDisc_inclusive"        , "bDisc"        , 500,  0,    1 )



#^ Predicted Distribution - Background estimation 
mttPredDist2_modMass_tagMassSDTau32_dRapHi_0btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[0],  "mttPredDist2_modMass_tagMassSDTau32_dRapHi_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_modMass_tagMassSDTau32_dRapHi_1btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[1],  "mttPredDist2_modMass_tagMassSDTau32_dRapHi_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_modMass_tagMassSDTau32_dRapHi_2btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[2],  "mttPredDist2_modMass_tagMassSDTau32_dRapHi_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_modMass_tagMassSDTau32_dRapHi_inclusive                        = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[3],  "mttPredDist2_modMass_tagMassSDTau32_dRapHi_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist2_modMass_tagMassSDTau32_dRapLo_0btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[4],  "mttPredDist2_modMass_tagMassSDTau32_dRapLo_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_modMass_tagMassSDTau32_dRapLo_1btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[5],  "mttPredDist2_modMass_tagMassSDTau32_dRapLo_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_modMass_tagMassSDTau32_dRapLo_2btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[6],  "mttPredDist2_modMass_tagMassSDTau32_dRapLo_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_modMass_tagMassSDTau32_dRapLo_inclusive                        = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[7],  "mttPredDist2_modMass_tagMassSDTau32_dRapLo_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist2_modMass_tagMassSDTau32_dRapIn_0btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[8],  "mttPredDist2_modMass_tagMassSDTau32_dRapIn_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_modMass_tagMassSDTau32_dRapIn_1btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[9],  "mttPredDist2_modMass_tagMassSDTau32_dRapIn_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_modMass_tagMassSDTau32_dRapIn_2btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[10], "mttPredDist2_modMass_tagMassSDTau32_dRapIn_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_modMass_tagMassSDTau32_dRapIn_inclusive                        = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[11], "mttPredDist2_modMass_tagMassSDTau32_dRapIn_inclusive"      , "mTT Mass", 700, 0, 7000)


mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_0btag                          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[0], "mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_0btag"        , "mTT Mass"     , 700,  0, 7000 )
mttPredDist2_tagMassSDTau32_dRapHi_JetMass_0btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[0], "mttPredDist2_tagMassSDTau32_dRapHi_JetMass_0btag"          , "Jet Mass"     , 500,  0,  500 )
mttPredDist2_tagMassSDTau32_dRapHi_JetPt_0btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[0], "mttPredDist2_tagMassSDTau32_dRapHi_JetPt_0btag"            , "Jet pT"       , 400,  0, 4000 )
mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_0btag                        = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[0], "mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_0btag"      , "Jet Rapidity" , 600, -3,    3 )
mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_0btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[0], "mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_0btag"     , "SoftDrop Mass", 500,  0,  500 )
mttPredDist2_tagMassSDTau32_dRapHi_Tau32_0btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[0], "mttPredDist2_tagMassSDTau32_dRapHi_Tau32_0btag"            , "Tau32"        , 500,  0,    1 )
mttPredDist2_tagMassSDTau32_dRapHi_bDisc_0btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[0], "mttPredDist2_tagMassSDTau32_dRapHi_bDisc_0btag"            , "bDisc"        , 500,  0,    1 )

mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_1btag                          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[1], "mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_1btag"        , "mTT Mass"     , 700,  0, 7000 )
mttPredDist2_tagMassSDTau32_dRapHi_JetMass_1btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[1], "mttPredDist2_tagMassSDTau32_dRapHi_JetMass_1btag"          , "Jet Mass"     , 500,  0,  500 )
mttPredDist2_tagMassSDTau32_dRapHi_JetPt_1btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[1], "mttPredDist2_tagMassSDTau32_dRapHi_JetPt_1btag"            , "Jet pT"       , 400,  0, 4000 )
mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_1btag                        = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[1], "mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_1btag"      , "Jet Rapidity" , 600, -3,    3 )
mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_1btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[1], "mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_1btag"     , "SoftDrop Mass", 500,  0,  500 )
mttPredDist2_tagMassSDTau32_dRapHi_Tau32_1btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[1], "mttPredDist2_tagMassSDTau32_dRapHi_Tau32_1btag"            , "Tau32"        , 500,  0,    1 )
mttPredDist2_tagMassSDTau32_dRapHi_bDisc_1btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[1], "mttPredDist2_tagMassSDTau32_dRapHi_bDisc_1btag"            , "bDisc"        , 500,  0,    1 )

mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_2btag                          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[2], "mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_2btag"        , "mTT Mass"     , 700,  0, 7000 )
mttPredDist2_tagMassSDTau32_dRapHi_JetMass_2btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[2], "mttPredDist2_tagMassSDTau32_dRapHi_JetMass_2btag"          , "Jet Mass"     , 500,  0,  500 )
mttPredDist2_tagMassSDTau32_dRapHi_JetPt_2btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[2], "mttPredDist2_tagMassSDTau32_dRapHi_JetPt_2btag"            , "Jet pT"       , 400,  0, 4000 )
mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_2btag                        = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[2], "mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_2btag"      , "Jet Rapidity" , 600, -3,    3 )
mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_2btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[2], "mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_2btag"     , "SoftDrop Mass", 500,  0,  500 )
mttPredDist2_tagMassSDTau32_dRapHi_Tau32_2btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[2], "mttPredDist2_tagMassSDTau32_dRapHi_Tau32_2btag"            , "Tau32"        , 500,  0,    1 )
mttPredDist2_tagMassSDTau32_dRapHi_bDisc_2btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[2], "mttPredDist2_tagMassSDTau32_dRapHi_bDisc_2btag"            , "bDisc"        , 500,  0,    1 )

mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_inclusive                      = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[3], "mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_inclusive"    , "mTT Mass"     , 700,  0, 7000 )
mttPredDist2_tagMassSDTau32_dRapHi_JetMass_inclusive                        = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[3], "mttPredDist2_tagMassSDTau32_dRapHi_JetMass_inclusive"      , "Jet Mass"     , 500,  0,  500 ) 
mttPredDist2_tagMassSDTau32_dRapHi_JetPt_inclusive                          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[3], "mttPredDist2_tagMassSDTau32_dRapHi_JetPt_inclusive"        , "Jet pT"       , 400,  0, 4000 )
mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_inclusive                    = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[3], "mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_inclusive"  , "Jet Rapidity" , 600, -3,    3 )
mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_inclusive                   = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[3], "mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_inclusive" , "SoftDrop Mass", 500,  0,  500 )
mttPredDist2_tagMassSDTau32_dRapHi_Tau32_inclusive                          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[3], "mttPredDist2_tagMassSDTau32_dRapHi_Tau32_inclusive"        , "Tau32"        , 500,  0,    1 )
mttPredDist2_tagMassSDTau32_dRapHi_bDisc_inclusive                          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[3], "mttPredDist2_tagMassSDTau32_dRapHi_bDisc_inclusive"        , "bDisc"        , 500,  0,    1 )


mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_0btag                          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[4], "mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_0btag"        , "mTT Mass"     , 700,  0, 7000 )
mttPredDist2_tagMassSDTau32_dRapLo_JetMass_0btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[4], "mttPredDist2_tagMassSDTau32_dRapLo_JetMass_0btag"          , "Jet Mass"     , 500,  0,  500 )
mttPredDist2_tagMassSDTau32_dRapLo_JetPt_0btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[4], "mttPredDist2_tagMassSDTau32_dRapLo_JetPt_0btag"            , "Jet pT"       , 400,  0, 4000 )
mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_0btag                        = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[4], "mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_0btag"      , "Jet Rapidity" , 600, -3,    3 )
mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_0btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[4], "mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_0btag"     , "SoftDrop Mass", 500,  0,  500 )
mttPredDist2_tagMassSDTau32_dRapLo_Tau32_0btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[4], "mttPredDist2_tagMassSDTau32_dRapLo_Tau32_0btag"            , "Tau32"        , 500,  0,    1 )
mttPredDist2_tagMassSDTau32_dRapLo_bDisc_0btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[4], "mttPredDist2_tagMassSDTau32_dRapLo_bDisc_0btag"            , "bDisc"        , 500,  0,    1 )

mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_1btag                          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[5], "mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_1btag"        , "mTT Mass"     , 700,  0, 7000 )
mttPredDist2_tagMassSDTau32_dRapLo_JetMass_1btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[5], "mttPredDist2_tagMassSDTau32_dRapLo_JetMass_1btag"          , "Jet Mass"     , 500,  0,  500 )
mttPredDist2_tagMassSDTau32_dRapLo_JetPt_1btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[5], "mttPredDist2_tagMassSDTau32_dRapLo_JetPt_1btag"            , "Jet pT"       , 400,  0, 4000 )
mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_1btag                        = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[5], "mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_1btag"      , "Jet Rapidity" , 600, -3,    3 )
mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_1btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[5], "mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_1btag"     , "SoftDrop Mass", 500,  0,  500 )
mttPredDist2_tagMassSDTau32_dRapLo_Tau32_1btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[5], "mttPredDist2_tagMassSDTau32_dRapLo_Tau32_1btag"            , "Tau32"        , 500,  0,    1 )
mttPredDist2_tagMassSDTau32_dRapLo_bDisc_1btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[5], "mttPredDist2_tagMassSDTau32_dRapLo_bDisc_1btag"            , "bDisc"        , 500,  0,    1 )

mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_2btag                          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[6], "mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_2btag"        , "mTT Mass"     , 700,  0, 7000 )
mttPredDist2_tagMassSDTau32_dRapLo_JetMass_2btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[6], "mttPredDist2_tagMassSDTau32_dRapLo_JetMass_2btag"          , "Jet Mass"     , 500,  0,  500 )
mttPredDist2_tagMassSDTau32_dRapLo_JetPt_2btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[6], "mttPredDist2_tagMassSDTau32_dRapLo_JetPt_2btag"            , "Jet pT"       , 400,  0, 4000 )
mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_2btag                        = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[6], "mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_2btag"      , "Jet Rapidity" , 600, -3,    3 )
mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_2btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[6], "mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_2btag"     , "SoftDrop Mass", 500,  0,  500 )
mttPredDist2_tagMassSDTau32_dRapLo_Tau32_2btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[6], "mttPredDist2_tagMassSDTau32_dRapLo_Tau32_2btag"            , "Tau32"        , 500,  0,    1 )
mttPredDist2_tagMassSDTau32_dRapLo_bDisc_2btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[6], "mttPredDist2_tagMassSDTau32_dRapLo_bDisc_2btag"            , "bDisc"        , 500,  0,    1 )

mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_inclusive                      = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[7], "mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_inclusive"    , "mTT Mass"     , 700,  0, 7000 )
mttPredDist2_tagMassSDTau32_dRapLo_JetMass_inclusive                        = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[7], "mttPredDist2_tagMassSDTau32_dRapLo_JetMass_inclusive"      , "Jet Mass"     , 500,  0,  500 )
mttPredDist2_tagMassSDTau32_dRapLo_JetPt_inclusive                          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[7], "mttPredDist2_tagMassSDTau32_dRapLo_JetPt_inclusive"        , "Jet pT"       , 400,  0, 4000 )
mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_inclusive                    = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[7], "mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_inclusive"  , "Jet Rapidity" , 600, -3,    3 )
mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_inclusive                   = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[7], "mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_inclusive" , "SoftDrop Mass", 500,  0,  500 )
mttPredDist2_tagMassSDTau32_dRapLo_Tau32_inclusive                          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[7], "mttPredDist2_tagMassSDTau32_dRapLo_Tau32_inclusive"        , "Tau32"        , 500,  0,    1 )
mttPredDist2_tagMassSDTau32_dRapLo_bDisc_inclusive                          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[7], "mttPredDist2_tagMassSDTau32_dRapLo_bDisc_inclusive"        , "bDisc"        , 500,  0,    1 )


mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_0btag                          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[8], "mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_0btag"        , "mTT Mass"     , 700,  0, 7000 )
mttPredDist2_tagMassSDTau32_dRapIn_JetMass_0btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[8], "mttPredDist2_tagMassSDTau32_dRapIn_JetMass_0btag"          , "Jet Mass"     , 500,  0,  500 )
mttPredDist2_tagMassSDTau32_dRapIn_JetPt_0btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[8], "mttPredDist2_tagMassSDTau32_dRapIn_JetPt_0btag"            , "Jet pT"       , 400,  0, 4000 )
mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_0btag                        = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[8], "mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_0btag"      , "Jet Rapidity" , 600, -3,    3 )
mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_0btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[8], "mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_0btag"     , "SoftDrop Mass", 500,  0,  500 )
mttPredDist2_tagMassSDTau32_dRapIn_Tau32_0btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[8], "mttPredDist2_tagMassSDTau32_dRapIn_Tau32_0btag"            , "Tau32"        , 500,  0,    1 )
mttPredDist2_tagMassSDTau32_dRapIn_bDisc_0btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[8], "mttPredDist2_tagMassSDTau32_dRapIn_bDisc_0btag"            , "bDisc"        , 500,  0,    1 )

mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_1btag                          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[9], "mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_1btag"        , "mTT Mass"     , 700,  0, 7000 )
mttPredDist2_tagMassSDTau32_dRapIn_JetMass_1btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[9], "mttPredDist2_tagMassSDTau32_dRapIn_JetMass_1btag"          , "Jet Mass"     , 500,  0,  500 )
mttPredDist2_tagMassSDTau32_dRapIn_JetPt_1btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[9], "mttPredDist2_tagMassSDTau32_dRapIn_JetPt_1btag"            , "Jet pT"       , 400,  0, 4000 )
mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_1btag                        = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[9], "mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_1btag"      , "Jet Rapidity" , 600, -3,    3 )
mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_1btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[9], "mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_1btag"     , "SoftDrop Mass", 500,  0,  500 )
mttPredDist2_tagMassSDTau32_dRapIn_Tau32_1btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[9], "mttPredDist2_tagMassSDTau32_dRapIn_Tau32_1btag"            , "Tau32"        , 500,  0,    1 )
mttPredDist2_tagMassSDTau32_dRapIn_bDisc_1btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[9], "mttPredDist2_tagMassSDTau32_dRapIn_bDisc_1btag"            , "bDisc"        , 500,  0,    1 )

mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_2btag                          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[10], "mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_2btag"        , "mTT Mass"     , 700,  0, 7000 )
mttPredDist2_tagMassSDTau32_dRapIn_JetMass_2btag                            = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[10], "mttPredDist2_tagMassSDTau32_dRapIn_JetMass_2btag"          , "Jet Mass"     , 500,  0,  500 )
mttPredDist2_tagMassSDTau32_dRapIn_JetPt_2btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[10], "mttPredDist2_tagMassSDTau32_dRapIn_JetPt_2btag"            , "Jet pT"       , 400,  0, 4000 )
mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_2btag                        = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[10], "mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_2btag"      , "Jet Rapidity" , 600, -3,    3 )
mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_2btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[10], "mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_2btag"     , "SoftDrop Mass", 500,  0,  500 )
mttPredDist2_tagMassSDTau32_dRapIn_Tau32_2btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[10], "mttPredDist2_tagMassSDTau32_dRapIn_Tau32_2btag"            , "Tau32"        , 500,  0,    1 )
mttPredDist2_tagMassSDTau32_dRapIn_bDisc_2btag                              = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[10], "mttPredDist2_tagMassSDTau32_dRapIn_bDisc_2btag"            , "bDisc"        , 500,  0,    1 )

mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_inclusive                      = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[11], "mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_inclusive"    , "mTT Mass"     , 700,  0, 7000 )
mttPredDist2_tagMassSDTau32_dRapIn_JetMass_inclusive                        = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[11], "mttPredDist2_tagMassSDTau32_dRapIn_JetMass_inclusive"      , "Jet Mass"     , 500,  0,  500 )
mttPredDist2_tagMassSDTau32_dRapIn_JetPt_inclusive                          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[11], "mttPredDist2_tagMassSDTau32_dRapIn_JetPt_inclusive"        , "Jet pT"       , 400,  0, 4000 )
mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_inclusive                    = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[11], "mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_inclusive"  , "Jet Rapidity" , 600, -3,    3 )
mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_inclusive                   = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[11], "mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_inclusive" , "SoftDrop Mass", 500,  0,  500 )
mttPredDist2_tagMassSDTau32_dRapIn_Tau32_inclusive                          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[11], "mttPredDist2_tagMassSDTau32_dRapIn_Tau32_inclusive"        , "Tau32"        , 500,  0,    1 )
mttPredDist2_tagMassSDTau32_dRapIn_bDisc_inclusive                          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32[11], "mttPredDist2_tagMassSDTau32_dRapIn_bDisc_inclusive"        , "bDisc"        , 500,  0,    1 )


mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[0],  "mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[1],  "mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[2],  "mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[3],  "mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[4],  "mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[5],  "mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[6],  "mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[7],  "mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[8],  "mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[9],  "mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[10], "mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[11], "mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_inclusive"      , "mTT Mass", 700, 0, 7000)


mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[0],  "mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[1],  "mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[2],  "mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[3],  "mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[4],  "mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[5],  "mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[6],  "mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[7],  "mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[8],  "mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[9],  "mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[10], "mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_EvenEvent[11], "mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_inclusive"      , "mTT Mass", 700, 0, 7000)


mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[0],  "mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[1],  "mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[2],  "mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[3],  "mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[4],  "mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[5],  "mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[6],  "mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[7],  "mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[8],  "mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[9],  "mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[10], "mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[11], "mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_inclusive"      , "mTT Mass", 700, 0, 7000)

mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[0],  "mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[1],  "mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[2],  "mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[3],  "mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[4],  "mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[5],  "mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[6],  "mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[7],  "mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[8],  "mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[9],  "mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[10], "mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_OddEvent[11], "mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_inclusive"      , "mTT Mass", 700, 0, 7000)


mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[0],  "mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[1],  "mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[2],  "mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[3],  "mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[4],  "mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[5],  "mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[6],  "mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[7],  "mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[8],  "mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[9],  "mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[10], "mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[11], "mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_inclusive"      , "mTT Mass", 700, 0, 7000)


mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[0],  "mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[1],  "mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[2],  "mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[3],  "mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[4],  "mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[5],  "mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[6],  "mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[7],  "mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[8],  "mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[9],  "mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[10], "mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_EvenEvent[11], "mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_inclusive"      , "mTT Mass", 700, 0, 7000)


mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_OddEvent[0],  "mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_OddEvent[1],  "mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_OddEvent[2],  "mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_OddEvent[3],  "mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_OddEvent[4],  "mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_OddEvent[5],  "mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_OddEvent[6],  "mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_OddEvent[7],  "mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_OddEvent[8],  "mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_OddEvent[9],  "mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_OddEvent[10], "mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_OddEvent[11], "mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_inclusive"      , "mTT Mass", 700, 0, 7000)

mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_OddEvent[0],  "mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_OddEvent[1],  "mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_OddEvent[2],  "mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_OddEvent[3],  "mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_OddEvent[4],  "mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_OddEvent[5],  "mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_OddEvent[6],  "mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_OddEvent[7],  "mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_OddEvent[8],  "mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_OddEvent[9],  "mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_OddEvent[10], "mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetP_TagMassSDTau32_OddEvent[11], "mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_inclusive"      , "mTT Mass", 700, 0, 7000)


mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_0btag                  = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagMinMass[0],  "mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_1btag                  = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagMinMass[1],  "mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_2btag                  = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagMinMass[2],  "mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_inclusive              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagMinMass[3],  "mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_0btag                  = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagMinMass[4],  "mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_1btag                  = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagMinMass[5],  "mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_2btag                  = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagMinMass[6],  "mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_inclusive              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagMinMass[7],  "mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_0btag                  = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagMinMass[8],  "mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_1btag                  = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagMinMass[9],  "mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_2btag                  = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagMinMass[10], "mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_inclusive              = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagMinMass[11], "mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_inclusive"      , "mTT Mass", 700, 0, 7000)
             
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_0btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_NoAntiTag[0],  "mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_1btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_NoAntiTag[1],  "mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_2btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_NoAntiTag[2],  "mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_inclusive                   = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_NoAntiTag[3],  "mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_0btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_NoAntiTag[4],  "mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_1btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_NoAntiTag[5],  "mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_2btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_NoAntiTag[6],  "mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_inclusive                   = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_NoAntiTag[7],  "mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_0btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_NoAntiTag[8],  "mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_1btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_NoAntiTag[9],  "mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_2btag                       = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_NoAntiTag[10], "mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_inclusive                   = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_NoAntiTag[11], "mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_inclusive"      , "mTT Mass", 700, 0, 7000)

mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagTau32_NoMassReq[0],  "mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagTau32_NoMassReq[1],  "mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagTau32_NoMassReq[2],  "mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagTau32_NoMassReq[3],  "mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagTau32_NoMassReq[4],  "mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagTau32_NoMassReq[5],  "mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagTau32_NoMassReq[6],  "mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagTau32_NoMassReq[7],  "mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_inclusive"      , "mTT Mass", 700, 0, 7000)
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_0btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagTau32_NoMassReq[8],  "mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_0btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_1btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagTau32_NoMassReq[9],  "mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_1btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_2btag          = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagTau32_NoMassReq[10], "mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_2btag"          , "mTT Mass", 700, 0, 7000)
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_inclusive      = ROOT.PredictedDistribution( h_mistag_vs_jetPt_TagMassSDTau32_AntiTagTau32_NoMassReq[11], "mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_inclusive"      , "mTT Mass", 700, 0, 7000)




# ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32    , False )
# ROOT.SetOwnership( mttPredDist_tagMassSDTau32    , False )


count_events = 0
n_topTag0MaxBdiscM_True  = 0
n_topTag0MaxBdiscM_False = 0
n_topTag1MaxBdiscM_True  = 0
n_topTag1MaxBdiscM_False = 0
n_newbtagjet0_True  = 0
n_newbtagjet0_False = 0
n_newbtagjet1_True  = 0
n_newbtagjet1_False = 0

count = 0
countOdd  = 0
countEven = 0

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

count_oldbtagjet0 =0
count_newbtagjet0 =0
count_topTag1MassSDTau32=0
count_newtopTag1MassSDTau32=0

for event in Tree:
  count_events +=1
  if count_events%1000 ==0:
    print str(count_events)+" / "+str(entries)

  count +=1
  if count%1000 ==0:
    print str(count)+" / "+str(entries)

  # if count_events > 20000:
  #   break
  
  Jet0MassSoftDrop = event.Jet0MassSoftDrop
  Jet1MassSoftDrop = event.Jet1MassSoftDrop

  Jet0Tau32 = event.Jet0Tau32
  Jet1Tau32 = event.Jet1Tau32

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

  # Top tagging scale factors from Svenja's talk
  sf0_MassTau32_nom     = 1.0
  sf0_MassTau32_err     = 0.0
  sf0_MassTau32_up      = 1.0
  sf0_MassTau32_dn      = 1.0
  sf0_MassTau32bTag_nom = 1.0
  sf0_MassTau32bTag_err = 0.0
  sf0_MassTau32bTag_up  = 1.0
  sf0_MassTau32bTag_dn  = 1.0
  sf0_bTag_nom          = 1.0
  sf0_bTag_err          = 0.0
  sf0_bTag_up           = 1.0
  sf0_bTag_dn           = 1.0
  sf1_MassTau32_nom     = 1.0
  sf1_MassTau32_err     = 0.0
  sf1_MassTau32_up      = 1.0
  sf1_MassTau32_dn      = 1.0
  sf1_MassTau32bTag_nom = 1.0
  sf1_MassTau32bTag_err = 0.0
  sf1_MassTau32bTag_up  = 1.0
  sf1_MassTau32bTag_dn  = 1.0
  sf1_bTag_nom          = 1.0
  sf1_bTag_err          = 0.0
  sf1_bTag_up           = 1.0
  sf1_bTag_dn           = 1.0
  # Jet 0
  if  400 < jet0P4Raw.Perp() * Jet0CorrFactor * Jet0PtSmearFactor < 550:
      sf0_MassTau32_nom     = 0.8
      sf0_MassTau32_err     = 0.1
      sf0_MassTau32_up      = sf0_MassTau32_nom + sf0_MassTau32_err
      sf0_MassTau32_dn      = sf0_MassTau32_nom - sf0_MassTau32_err
      sf0_MassTau32bTag_nom = 0.75
      sf0_MassTau32bTag_err = 0.1
      sf0_MassTau32bTag_up  = sf0_MassTau32bTag_nom + sf0_MassTau32bTag_err
      sf0_MassTau32bTag_dn  = sf0_MassTau32bTag_nom - sf0_MassTau32bTag_err
      sf0_bTag_nom          = 0.92 #sf0_MassTau32bTag_nom / sf0_MassTau32_nom
      sf0_bTag_err          = 0.07 #(1/sf0_bTag_nom)*sqrt((sf0_MassTau32_err/sf0_MassTau32_nom)**2+(sf0_MassTau32bTag_err/sf0_MassTau32bTag_nom)**2)
      sf0_bTag_up           = sf0_bTag_nom + sf0_bTag_err
      sf0_bTag_dn           = sf0_bTag_nom - sf0_bTag_err
      #print 'sf0_MassTau32_nom '+str(sf0_MassTau32_nom)+' sf0_MassTau32bTag_nom '+str(sf0_MassTau32bTag_nom)+' sf0_bTag_nom '+str(sf0_bTag_nom)
  if jet0P4Raw.Perp() * Jet0CorrFactor * Jet0PtSmearFactor > 550:
      sf0_MassTau32_nom     = 0.8
      sf0_MassTau32_err     = 0.1
      sf0_MassTau32_up      = sf0_MassTau32_nom + sf0_MassTau32_err
      sf0_MassTau32_dn      = sf0_MassTau32_nom - sf0_MassTau32_err
      sf0_MassTau32bTag_nom = 0.75
      sf0_MassTau32bTag_err = 0.1
      sf0_MassTau32bTag_up  = sf0_MassTau32bTag_nom + sf0_MassTau32bTag_err
      sf0_MassTau32bTag_dn  = sf0_MassTau32bTag_nom - sf0_MassTau32bTag_err
      sf0_bTag_nom          = 0.72 #sf0_MassTau32bTag_nom / sf0_MassTau32_nom
      sf0_bTag_err          = 0.16#(1/sf0_bTag_nom)*sqrt((sf0_MassTau32_err/sf0_MassTau32_nom)**2+(sf0_MassTau32bTag_err/sf0_MassTau32bTag_nom)**2)
      sf0_bTag_up           = sf0_bTag_nom + sf0_bTag_err
      sf0_bTag_dn           = sf0_bTag_nom - sf0_bTag_err
  # Jet 1
  if  400 < jet1P4Raw.Perp() * Jet1CorrFactor * Jet1PtSmearFactor < 550:
      sf1_MassTau32_nom     = 0.8
      sf1_MassTau32_err     = 0.1
      sf1_MassTau32_up      = sf1_MassTau32_nom + sf1_MassTau32_err
      sf1_MassTau32_dn      = sf1_MassTau32_nom - sf1_MassTau32_err
      sf1_MassTau32bTag_nom = 0.75
      sf1_MassTau32bTag_err = 0.1
      sf1_MassTau32bTag_up  = sf1_MassTau32bTag_nom + sf1_MassTau32bTag_err
      sf1_MassTau32bTag_dn  = sf1_MassTau32bTag_nom - sf1_MassTau32bTag_err
      sf1_bTag_nom          = 0.92 #sf1_MassTau32bTag_nom / sf1_MassTau32_nom
      sf1_bTag_err          = 0.07 #(1/sf1_bTag_nom)*sqrt((sf1_MassTau32_err/sf1_MassTau32_nom)**2+(sf1_MassTau32bTag_err/sf1_MassTau32bTag_nom)**2)
      sf1_bTag_up           = sf1_bTag_nom + sf1_bTag_err
      sf1_bTag_dn           = sf1_bTag_nom - sf1_bTag_err
      #print 'sf1_MassTau32_nom '+str(sf1_MassTau32_nom)+' sf1_MassTau32bTag_nom '+str(sf1_MassTau32bTag_nom)+' sf1_bTag_nom '+str(sf1_bTag_nom)
  if jet1P4Raw.Perp() * Jet1CorrFactor * Jet1PtSmearFactor > 550:
      sf1_MassTau32_nom     = 0.8
      sf1_MassTau32_err     = 0.1
      sf1_MassTau32_up      = sf1_MassTau32_nom + sf1_MassTau32_err
      sf1_MassTau32_dn      = sf1_MassTau32_nom - sf1_MassTau32_err
      sf1_MassTau32bTag_nom = 0.75
      sf1_MassTau32bTag_err = 0.1
      sf1_MassTau32bTag_up  = sf1_MassTau32bTag_nom + sf1_MassTau32bTag_err
      sf1_MassTau32bTag_dn  = sf1_MassTau32bTag_nom - sf1_MassTau32bTag_err
      sf1_bTag_nom          = 0.72 #sf1_MassTau32bTag_nom / sf1_MassTau32_nom
      sf1_bTag_err          = 0.16 #(1/sf1_bTag_nom)*sqrt((sf1_MassTau32_err/sf1_MassTau32_nom)**2+(sf1_MassTau32bTag_err/sf1_MassTau32bTag_nom)**2)
      sf1_bTag_up           = sf1_bTag_nom + sf1_bTag_err
      sf1_bTag_dn           = sf1_bTag_nom - sf1_bTag_err

 
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
      # nom, pdf_up, pdf_dn, q2_up, q2_dn
      if (options.Syst == 0 or abs(options.Syst) == 4 or abs(options.Syst) == 5):
          jet0P4 = jet0P4Raw * Jet0CorrFactor * Jet0PtSmearFactor
          jet1P4 = jet1P4Raw * Jet1CorrFactor * Jet1PtSmearFactor
          sf0_MassTau32     = sf0_MassTau32_nom
          sf0_MassTau32bTag = sf0_MassTau32bTag_nom
          sf0_bTag          = sf0_bTag_nom
          sf1_MassTau32     = sf1_MassTau32_nom
          sf1_MassTau32bTag = sf1_MassTau32bTag_nom
          sf1_bTag          = sf1_bTag_nom
          #reader = ROOT.BTagCalibrationReader(calib, 0, "comb", "central")  # 0 is for loose op 
          maxJetHt = event.HT
      # jec_up
      elif options.Syst == 1:
          jet0P4 = jet0P4Raw * Jet0CorrFactorUp * Jet0PtSmearFactor
          jet1P4 = jet1P4Raw * Jet1CorrFactorUp * Jet1PtSmearFactor
          sf0_MassTau32     = sf0_MassTau32_nom
          sf0_MassTau32bTag = sf0_MassTau32bTag_nom
          sf0_bTag          = sf0_bTag_nom
          sf1_MassTau32     = sf1_MassTau32_nom
          sf1_MassTau32bTag = sf1_MassTau32bTag_nom
          sf1_bTag          = sf1_bTag_nom
          #reader = ROOT.BTagCalibrationReader(calib, 0, "comb", "central")  # 0 is for loose op 
          maxJetHt = event.HT_CorrUp
      # jec_dn
      elif options.Syst == -1:
          jet0P4 = jet0P4Raw * Jet0CorrFactorDn * Jet0PtSmearFactor
          jet1P4 = jet1P4Raw * Jet1CorrFactorDn * Jet1PtSmearFactor
          sf0_MassTau32     = sf0_MassTau32_nom
          sf0_MassTau32bTag = sf0_MassTau32bTag_nom
          sf0_bTag          = sf0_bTag_nom
          sf1_MassTau32     = sf1_MassTau32_nom
          sf1_MassTau32bTag = sf1_MassTau32bTag_nom
          sf1_bTag          = sf1_bTag_nom
          #reader = ROOT.BTagCalibrationReader(calib, 0, "comb", "central")  # 0 is for loose op 
          maxJetHt = event.HT_CorrDn
      # jer_up
      elif options.Syst == 2:
          jet0P4 = jet0P4Raw * Jet0CorrFactor * Jet0PtSmearFactorUp
          jet1P4 = jet1P4Raw * Jet1CorrFactor * Jet1PtSmearFactorUp
          sf0_MassTau32     = sf0_MassTau32_nom
          sf0_MassTau32bTag = sf0_MassTau32bTag_nom
          sf0_bTag          = sf0_bTag_nom
          sf1_MassTau32     = sf1_MassTau32_nom
          sf1_MassTau32bTag = sf1_MassTau32bTag_nom
          sf1_bTag          = sf1_bTag_nom
          #reader = ROOT.BTagCalibrationReader(calib, 0, "comb", "central")  # 0 is for loose op 
          maxJetHt = event.HT_PtSmearUp
      # jer_dn
      elif options.Syst == -2:
          jet0P4 = jet0P4Raw * Jet0CorrFactor * Jet0PtSmearFactorDn
          jet1P4 = jet1P4Raw * Jet1CorrFactor * Jet1PtSmearFactorDn
          sf0_MassTau32     = sf0_MassTau32_nom
          sf0_MassTau32bTag = sf0_MassTau32bTag_nom
          sf0_bTag          = sf0_bTag_nom
          sf1_MassTau32     = sf1_MassTau32_nom
          sf1_MassTau32bTag = sf1_MassTau32bTag_nom
          sf1_bTag          = sf1_bTag_nom
          #reader = ROOT.BTagCalibrationReader(calib, 0, "comb", "central")  # 0 is for loose op 
          maxJetHt = event.HT_PtSmearDn
      #bTag_up
      elif options.Syst == 3:
          jet0P4 = jet0P4Raw * Jet0CorrFactor * Jet0PtSmearFactor
          jet1P4 = jet1P4Raw * Jet1CorrFactor * Jet1PtSmearFactor
          sf0_MassTau32     = sf0_MassTau32_up
          sf0_MassTau32bTag = sf0_MassTau32bTag_up
          sf0_bTag          = sf0_bTag_up
          sf1_MassTau32     = sf1_MassTau32_up
          sf1_MassTau32bTag = sf1_MassTau32bTag_up
          sf1_bTag          = sf1_bTag_up
          #reader = ROOT.BTagCalibrationReader(calib, 0, "comb", "up")  # 0 is for loose op
          maxJetHt = event.HT
      # bTag_dn
      elif options.Syst == -3:
          jet0P4 = jet0P4Raw * Jet0CorrFactor * Jet0PtSmearFactor
          jet1P4 = jet1P4Raw * Jet1CorrFactor * Jet1PtSmearFactor 
          sf0_MassTau32     = sf0_MassTau32_dn
          sf0_MassTau32bTag = sf0_MassTau32bTag_dn
          sf0_bTag          = sf0_bTag_dn
          sf1_MassTau32     = sf1_MassTau32_dn
          sf1_MassTau32bTag = sf1_MassTau32bTag_dn
          sf1_bTag          = sf1_bTag_dn
          #reader = ROOT.BTagCalibrationReader(calib, 0, "comb", "down")  # 0 is for loose op
          maxJetHt = event.HT
  
  

  DijetMass = (jet0P4 + jet1P4).M()


  if jet0P4.Perp() < 400 or jet1P4.Perp() < 400:
    continue

  if maxJetHt < 1000:
    continue

  evenEvent = False
  oddEvent = False
  # if event.AllHadEventNum % 2 == 0 :
  if count % 2 == 0 :
    evenEvent = True
  else:
    oddEvent = True

  if oddEvent:
     countOdd+=1  
  if evenEvent:
     countEven+=1


  



  maxBdisc_jet0_ = event.Jet0SDbdisc0
  maxBdisc_jet1_ = event.Jet0SDbdisc1
  

  # Only necessary if using official AK4 b-tagging SF
  # if abs(event.Jet0SDmaxbdiscflav) == 5:
  #     Jet0BTagEntry = 0
  # elif abs(event.Jet0SDmaxbdiscflav) == 4:
  #     Jet0BTagEntry = 1
  # else:
  #     Jet0BTagEntry = 2

  # if abs(event.Jet1SDmaxbdiscflav) == 5:
  #     Jet1BTagEntry = 0
  # elif abs(event.Jet1SDmaxbdiscflav) == 4:
  #     Jet1BTagEntry = 1
  # else:
  #     Jet1BTagEntry = 2
  
  # define tags - make sure they are the same as what was used to calculate the mistag
  topTag0MassSD                      = event.Jet0MassSoftDrop > 110 and event.Jet0MassSoftDrop < 210
  topTag1MassSD                      = event.Jet1MassSoftDrop > 110 and event.Jet1MassSoftDrop < 210
  topTag0Tau32                       = event.Jet0Tau32 < 0.69
  topTag1Tau32                       = event.Jet1Tau32 < 0.69
  topTag0MaxBdiscM                   = maxBdisc_jet0_ > 0.890 # CSVv2 medium operating point 2015_06
  topTag1MaxBdiscM                   = maxBdisc_jet1_ > 0.890 # CSVv2 medium operating point 2015_06
  topTag0MassSDTau32                 = topTag0MassSD and topTag0Tau32
  topTag1MassSDTau32                 = topTag1MassSD and topTag1Tau32

  
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

  # newtopTag0MassSDTau32 =    bool( applySF ( topTag0MassSDTau32 , sf0_MassTau32 , Btag_eff = 0.2) )
  # newtopTag1MassSDTau32 =    bool( applySF ( topTag1MassSDTau32 , sf1_MassTau32 , Btag_eff = 0.2) )

  # newtopTag0MassSDTau32btag =    bool( applySF ( topTag0MassSDTau32 , sf0_MassTau32 , Btag_eff = 0.17) )
  # newtopTag1MassSDTau32btag =    bool( applySF ( topTag1MassSDTau32 , sf1_MassTau32 , Btag_eff = 0.17) )

  newbtagjet0 =  bool( applySF ( topTag0MaxBdiscM , sf0_bTag , Btag_eff = 0.7) )
  newbtagjet1 =  bool( applySF ( topTag1MaxBdiscM , sf1_bTag , Btag_eff = 0.7) )


  # Track SF changes
  # if topTag0MaxBdiscM:
  #   count_oldbtagjet0 +=1
  # if newbtagjet0:
  #   count_newbtagjet0 +=1
  # if topTag1MassSDTau32: 
  #   count_topTag1MassSDTau32+=1
  # if newtopTag1MassSDTau32: 
  #   count_newtopTag1MassSDTau32+=1

  # ModMass
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

  if verbose:
    print 'randMass_QCD_Fat_jet0 '+str(randMass_QCD_Fat_jet0)
    print 'randMass_QCD_Fat_jet1 '+str(randMass_QCD_Fat_jet1)
    print 'rand_mass '+str(rand_mass)

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



  if (options.isData): 
     evWeight = 1.0
  else:
     evWeight = event.AllHadEventWeight
  if (options.Syst == 4):
     evWeight *= event.NNPDF3weight_CorrUp
  if (options.Syst == -4):
     evWeight *= event.NNPDF3weight_CorrDn
  if (options.Syst == 5):
     evWeight *= event.Q2weight_CorrUp
  if (options.Syst == -5):
     evWeight *= event.Q2weight_CorrDn



  #^ fill double tagged dijet distributions
  if topTag0MassSDTau32 and topTag1MassSDTau32:
      if event.DijetDeltaRap > 1 :
          #inclusive
          h_mttMass_tagMassSDTau32_dRapHi_inclusive.Fill( DijetMass   , evWeight )
          if newbtagjet0 and newbtagjet1:
                #2btag
                h_mttMass_tagMassSDTau32_dRapHi_2btag.Fill( DijetMass   , evWeight ) #* sf0_MassTau32bTag * sf1_MassTau32bTag )
          if (newbtagjet0 and not newbtagjet1):
                #1btag
                h_mttMass_tagMassSDTau32_dRapHi_1btag.Fill( DijetMass   , evWeight ) #* sf1_MassTau32 * sf0_MassTau32bTag )
          if (newbtagjet1 and not newbtagjet0):
                h_mttMass_tagMassSDTau32_dRapHi_1btag.Fill( DijetMass   , evWeight ) #* sf0_MassTau32 * sf1_MassTau32bTag )
          if not newbtagjet0 and not newbtagjet1:
                #0btag
                h_mttMass_tagMassSDTau32_dRapHi_0btag.Fill( DijetMass   , evWeight ) #* sf0_MassTau32 * sf1_MassTau32 )
      if event.DijetDeltaRap <= 1:
            #inclusive
            h_mttMass_tagMassSDTau32_dRapLo_inclusive.Fill( DijetMass   , evWeight )
            if newbtagjet0 and newbtagjet1:
                #2btag
                h_mttMass_tagMassSDTau32_dRapLo_2btag.Fill( DijetMass   , evWeight )#* sf0_MassTau32bTag * sf1_MassTau32bTag )
            if (newbtagjet0 and not newbtagjet1):
                #1btag
                h_mttMass_tagMassSDTau32_dRapLo_1btag.Fill( DijetMass   , evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
            if (newbtagjet1 and not newbtagjet0):
                h_mttMass_tagMassSDTau32_dRapLo_1btag.Fill( DijetMass   , evWeight )#* sf0_MassTau32 * sf1_MassTau32bTag)
            if not newbtagjet0 and not newbtagjet1:
                #0btag
                h_mttMass_tagMassSDTau32_dRapLo_0btag.Fill( DijetMass   , evWeight )#* sf0_MassTau32 * sf1_MassTau32 )
  


  
  rand1 =  ROOT.TRandom3(0)
  rand_bkgdest  = rand1.Uniform(0,1.0)

  bin = []
  rate = []
 
  #^ Fill predicted distribution

  # randomly select jet 0 to be the tag then fill predDist based on probability that jet 1 is mis-tagged
  if rand_bkgdest < 0.5 :

      # Mistag as a function of p_T
      if topTag0MassSDTau32 :
          # mttPredDist_tagMassSDTau32        .Accumulate(              ttMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
          # mttPredDist_modMass_tagMassSDTau32.Accumulate( ttMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
          for i in xrange(len(post)):
              bin.append ( h_mistag_vs_jetPt_TagMassSDTau32[i].GetXaxis().FindBin( event.Jet1Pt ))
              rate.append( h_mistag_vs_jetPt_TagMassSDTau32[i].GetBinContent(bin[i]))

          #dRapIn
          mttPredDist_tagMassSDTau32_dRapIn_DijetMass_inclusive            .Accumulate(              DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_DijetMass_inclusive    , False )
          mttPredDist_tagMassSDTau32_dRapIn_JetMass_inclusive              .Accumulate(             jet1P4.M(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetMass_inclusive      , False )
          mttPredDist_tagMassSDTau32_dRapIn_JetPt_inclusive                .Accumulate(           jet1P4.Perp(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetPt_inclusive        , False )
          mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_inclusive               .Accumulate(       jet1P4.Rapidity(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_inclusive       , False )
          mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_inclusive         .Accumulate(        Jet1MassSoftDrop, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_inclusive , False )
          mttPredDist_tagMassSDTau32_dRapIn_Tau32_inclusive                .Accumulate(               Jet1Tau32, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_Tau32_inclusive        , False )
          mttPredDist_tagMassSDTau32_dRapIn_bDisc_inclusive                .Accumulate(          maxBdisc_jet1_, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_bDisc_inclusive        , False )

          mttPredDist_modMass_tagMassSDTau32_dRapIn_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership(  mttPredDist_modMass_tagMassSDTau32_dRapIn_inclusive   , False )
          h_bkgdEst_tagMassSDTau32_dRapIn_inclusive              .Fill( DijetMass       , evWeight*rate[0])
          h_bkgdEst_modMass_tagMassSDTau32_dRapIn_inclusive      .Fill( DijetMass_modMass_jet1, evWeight*rate[0])
          if newbtagjet0 and newbtagjet1:
              #2btag
              mttPredDist_tagMassSDTau32_dRapIn_DijetMass_2btag            .Accumulate(              DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership(  mttPredDist_tagMassSDTau32_dRapIn_DijetMass_2btag   , False )
              mttPredDist_tagMassSDTau32_dRapIn_JetMass_2btag              .Accumulate(             jet1P4.M(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetMass_2btag      , False )
              mttPredDist_tagMassSDTau32_dRapIn_JetPt_2btag                .Accumulate(           jet1P4.Perp(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetPt_2btag        , False )
              mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_2btag               .Accumulate(       jet1P4.Rapidity(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_2btag       , False )
              mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_2btag         .Accumulate(        Jet1MassSoftDrop, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_2btag , False )
              mttPredDist_tagMassSDTau32_dRapIn_Tau32_2btag                .Accumulate(               Jet1Tau32, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_Tau32_2btag        , False )
              mttPredDist_tagMassSDTau32_dRapIn_bDisc_2btag                .Accumulate(          maxBdisc_jet1_, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_bDisc_2btag        , False )

              mttPredDist_modMass_tagMassSDTau32_dRapIn_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32_dRapIn_2btag    , False )
              h_bkgdEst_tagMassSDTau32_dRapIn_2btag              .Fill( DijetMass             , evWeight*rate[1] )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              h_bkgdEst_modMass_tagMassSDTau32_dRapIn_2btag      .Fill( DijetMass_modMass_jet1, evWeight*rate[1] )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
          if (newbtagjet0 and not newbtagjet1):
              #1btag
              mttPredDist_tagMassSDTau32_dRapIn_DijetMass_1btag            .Accumulate(              DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_DijetMass_1btag    , False )
              mttPredDist_tagMassSDTau32_dRapIn_JetMass_1btag              .Accumulate(             jet1P4.M(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetMass_1btag      , False )
              mttPredDist_tagMassSDTau32_dRapIn_JetPt_1btag                .Accumulate(           jet1P4.Perp(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetPt_1btag        , False )
              mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_1btag               .Accumulate(       jet1P4.Rapidity(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_1btag       , False )
              mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_1btag         .Accumulate(        Jet1MassSoftDrop, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_1btag , False )
              mttPredDist_tagMassSDTau32_dRapIn_Tau32_1btag                .Accumulate(               Jet1Tau32, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_Tau32_1btag        , False )
              mttPredDist_tagMassSDTau32_dRapIn_bDisc_1btag                .Accumulate(          maxBdisc_jet1_, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_bDisc_1btag        , False )

              mttPredDist_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32_dRapIn_1btag    , False )
              h_bkgdEst_tagMassSDTau32_dRapIn_1btag              .Fill( DijetMass             , evWeight*rate[2] )# * sf1_MassTau32 * sf0_MassTau32bTag)
              h_bkgdEst_modMass_tagMassSDTau32_dRapIn_1btag      .Fill( DijetMass_modMass_jet1, evWeight*rate[2] )# * sf1_MassTau32 * sf0_MassTau32bTag)
          if (newbtagjet1 and not newbtagjet0):
              mttPredDist_tagMassSDTau32_dRapIn_DijetMass_1btag            .Accumulate(              DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_DijetMass_1btag    , False )
              mttPredDist_tagMassSDTau32_dRapIn_JetMass_1btag              .Accumulate(             jet1P4.M(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetMass_1btag      , False )
              mttPredDist_tagMassSDTau32_dRapIn_JetPt_1btag                .Accumulate(           jet1P4.Perp(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetPt_1btag        , False )
              mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_1btag               .Accumulate(       jet1P4.Rapidity(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_1btag       , False )
              mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_1btag         .Accumulate(        Jet1MassSoftDrop, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_1btag , False )
              mttPredDist_tagMassSDTau32_dRapIn_Tau32_1btag                .Accumulate(               Jet1Tau32, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_Tau32_1btag        , False )
              mttPredDist_tagMassSDTau32_dRapIn_bDisc_1btag                .Accumulate(          maxBdisc_jet1_, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_bDisc_1btag        , False )

              mttPredDist_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32_dRapIn_1btag    , False )
              h_bkgdEst_tagMassSDTau32_dRapIn_1btag              .Fill( DijetMass             , evWeight*rate[2] )#* sf0_MassTau32 * sf1_MassTau32bTag )
              h_bkgdEst_modMass_tagMassSDTau32_dRapIn_1btag      .Fill( DijetMass_modMass_jet1, evWeight*rate[2] )#* sf0_MassTau32 * sf1_MassTau32bTag )
          if not newbtagjet0 and not newbtagjet1:
              #0btag
              mttPredDist_tagMassSDTau32_dRapIn_DijetMass_0btag            .Accumulate(                        DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_DijetMass_0btag    , False )
              mttPredDist_tagMassSDTau32_dRapIn_JetMass_0btag              .Accumulate(             jet1P4.M(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetMass_0btag      , False )
              mttPredDist_tagMassSDTau32_dRapIn_JetPt_0btag                .Accumulate(           jet1P4.Perp(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetPt_0btag        , False )
              mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_0btag               .Accumulate(       jet1P4.Rapidity(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_0btag       , False )
              mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_0btag         .Accumulate(        Jet1MassSoftDrop, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_0btag , False )
              mttPredDist_tagMassSDTau32_dRapIn_Tau32_0btag                .Accumulate(               Jet1Tau32, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_Tau32_0btag        , False )
              mttPredDist_tagMassSDTau32_dRapIn_bDisc_0btag                .Accumulate(          maxBdisc_jet1_, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_bDisc_0btag        , False )

              mttPredDist_modMass_tagMassSDTau32_dRapIn_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32_dRapIn_0btag    , False )
              h_bkgdEst_tagMassSDTau32_dRapIn_0btag              .Fill( DijetMass             , evWeight*rate[3] )#* sf1_MassTau32 * sf1_MassTau32bTag )
              h_bkgdEst_modMass_tagMassSDTau32_dRapIn_0btag      .Fill( DijetMass_modMass_jet1, evWeight*rate[3] )#* sf1_MassTau32 * sf1_MassTau32bTag )


          if event.DijetDeltaRap > 1 :
              #inclusive
              mttPredDist_tagMassSDTau32_dRapHi_DijetMass_inclusive            .Accumulate(              DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_DijetMass_inclusive    , False )
              mttPredDist_tagMassSDTau32_dRapHi_JetMass_inclusive              .Accumulate(             jet1P4.M(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetMass_inclusive      , False )
              mttPredDist_tagMassSDTau32_dRapHi_JetPt_inclusive                .Accumulate(           jet1P4.Perp(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetPt_inclusive        , False )
              mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_inclusive               .Accumulate(       jet1P4.Rapidity(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_inclusive       , False )
              mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_inclusive         .Accumulate(        Jet1MassSoftDrop, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_inclusive , False )
              mttPredDist_tagMassSDTau32_dRapHi_Tau32_inclusive                .Accumulate(               Jet1Tau32, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_Tau32_inclusive        , False )
              mttPredDist_tagMassSDTau32_dRapHi_bDisc_inclusive                .Accumulate(          maxBdisc_jet1_, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_bDisc_inclusive        , False )

              mttPredDist_modMass_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32_dRapHi_inclusive    , False )
              h_bkgdEst_tagMassSDTau32_dRapHi_inclusive              .Fill( DijetMass             , evWeight*rate[0])
              h_bkgdEst_modMass_tagMassSDTau32_dRapHi_inclusive      .Fill( DijetMass_modMass_jet1, evWeight*rate[0])
              if newbtagjet0 and newbtagjet1:
                  #2btag
                  mttPredDist_tagMassSDTau32_dRapHi_DijetMass_2btag            .Accumulate(              DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_tagMassSDTau32_dRapHi_DijetMass_2btag   , False )
                  mttPredDist_tagMassSDTau32_dRapHi_JetMass_2btag              .Accumulate(             jet1P4.M(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetMass_2btag      , False )
                  mttPredDist_tagMassSDTau32_dRapHi_JetPt_2btag                .Accumulate(           jet1P4.Perp(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetPt_2btag        , False )
                  mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_2btag               .Accumulate(       jet1P4.Rapidity(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_2btag       , False )
                  mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_2btag         .Accumulate(        Jet1MassSoftDrop, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_2btag , False )
                  mttPredDist_tagMassSDTau32_dRapHi_Tau32_2btag                .Accumulate(               Jet1Tau32, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_Tau32_2btag        , False )
                  mttPredDist_tagMassSDTau32_dRapHi_bDisc_2btag                .Accumulate(          maxBdisc_jet1_, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_bDisc_2btag        , False )

                  mttPredDist_modMass_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_modMass_tagMassSDTau32_dRapHi_2btag   , False )
                  h_bkgdEst_tagMassSDTau32_dRapHi_2btag              .Fill( DijetMass             , evWeight*rate[1] )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag      .Fill( DijetMass_modMass_jet1, evWeight*rate[1] )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              if (newbtagjet0 and not newbtagjet1):
                  #1btag
                  mttPredDist_tagMassSDTau32_dRapHi_DijetMass_1btag            .Accumulate(              DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_DijetMass_1btag    , False )
                  mttPredDist_tagMassSDTau32_dRapHi_JetMass_1btag              .Accumulate(             jet1P4.M(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetMass_1btag      , False )
                  mttPredDist_tagMassSDTau32_dRapHi_JetPt_1btag                .Accumulate(           jet1P4.Perp(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetPt_1btag        , False )
                  mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_1btag               .Accumulate(       jet1P4.Rapidity(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_1btag       , False )
                  mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_1btag         .Accumulate(        Jet1MassSoftDrop, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_1btag , False )
                  mttPredDist_tagMassSDTau32_dRapHi_Tau32_1btag                .Accumulate(               Jet1Tau32, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_Tau32_1btag        , False )
                  mttPredDist_tagMassSDTau32_dRapHi_bDisc_1btag                .Accumulate(          maxBdisc_jet1_, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_bDisc_1btag        , False )

                  mttPredDist_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32_dRapHi_1btag    , False )
                  h_bkgdEst_tagMassSDTau32_dRapHi_1btag              .Fill( DijetMass             , evWeight*rate[2] )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag      .Fill( DijetMass_modMass_jet1, evWeight*rate[2] )#* sf1_MassTau32 * sf0_MassTau32bTag)
              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist_tagMassSDTau32_dRapHi_DijetMass_1btag            .Accumulate(              DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_DijetMass_1btag    , False )
                  mttPredDist_tagMassSDTau32_dRapHi_JetMass_1btag              .Accumulate(             jet1P4.M(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetMass_1btag      , False )
                  mttPredDist_tagMassSDTau32_dRapHi_JetPt_1btag                .Accumulate(           jet1P4.Perp(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetPt_1btag        , False )
                  mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_1btag               .Accumulate(       jet1P4.Rapidity(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_1btag       , False )
                  mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_1btag         .Accumulate(        Jet1MassSoftDrop, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_1btag , False )
                  mttPredDist_tagMassSDTau32_dRapHi_Tau32_1btag                .Accumulate(               Jet1Tau32, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_Tau32_1btag        , False )
                  mttPredDist_tagMassSDTau32_dRapHi_bDisc_1btag                .Accumulate(          maxBdisc_jet1_, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_bDisc_1btag        , False )

                  mttPredDist_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_modMass_tagMassSDTau32_dRapHi_1btag   , False )
                  h_bkgdEst_tagMassSDTau32_dRapHi_1btag              .Fill( DijetMass             , evWeight*rate[2] )#* sf0_MassTau32 * sf1_MassTau32bTag )
                  h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag      .Fill( DijetMass_modMass_jet1, evWeight*rate[2] )#* sf0_MassTau32 * sf1_MassTau32bTag )
              if not newbtagjet0 and not newbtagjet1:
                  #0btag
                  mttPredDist_tagMassSDTau32_dRapHi_DijetMass_0btag            .Accumulate(                        DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_DijetMass_0btag    , False )
                  mttPredDist_tagMassSDTau32_dRapHi_JetMass_0btag              .Accumulate(             jet1P4.M(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetMass_0btag      , False )
                  mttPredDist_tagMassSDTau32_dRapHi_JetPt_0btag                .Accumulate(           jet1P4.Perp(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetPt_0btag        , False )
                  mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_0btag               .Accumulate(       jet1P4.Rapidity(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_0btag       , False )
                  mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_0btag         .Accumulate(        Jet1MassSoftDrop, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_0btag , False )
                  mttPredDist_tagMassSDTau32_dRapHi_Tau32_0btag                .Accumulate(               Jet1Tau32, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_Tau32_0btag        , False )
                  mttPredDist_tagMassSDTau32_dRapHi_bDisc_0btag                .Accumulate(          maxBdisc_jet1_, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_bDisc_0btag        , False )

                  mttPredDist_modMass_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32_dRapHi_0btag    , False )
                  h_bkgdEst_tagMassSDTau32_dRapHi_0btag              .Fill( DijetMass             , evWeight*rate[3])# * sf1_MassTau32 * sf1_MassTau32bTag )
                  h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag      .Fill( DijetMass_modMass_jet1, evWeight*rate[3])# * sf1_MassTau32 * sf1_MassTau32bTag )
          
          if event.DijetDeltaRap < 1:
              #inclusive
              mttPredDist_tagMassSDTau32_dRapLo_DijetMass_inclusive            .Accumulate(              DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_DijetMass_inclusive    , False )
              mttPredDist_tagMassSDTau32_dRapLo_JetMass_inclusive              .Accumulate(             jet1P4.M(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetMass_inclusive      , False )
              mttPredDist_tagMassSDTau32_dRapLo_JetPt_inclusive                .Accumulate(           jet1P4.Perp(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetPt_inclusive        , False )
              mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_inclusive               .Accumulate(       jet1P4.Rapidity(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_inclusive       , False )
              mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_inclusive         .Accumulate(        Jet1MassSoftDrop, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_inclusive , False )
              mttPredDist_tagMassSDTau32_dRapLo_Tau32_inclusive                .Accumulate(               Jet1Tau32, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_Tau32_inclusive        , False )
              mttPredDist_tagMassSDTau32_dRapLo_bDisc_inclusive                .Accumulate(          maxBdisc_jet1_, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_bDisc_inclusive        , False )

              mttPredDist_modMass_tagMassSDTau32_dRapLo_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership(  mttPredDist_modMass_tagMassSDTau32_dRapLo_inclusive   , False )
              h_bkgdEst_tagMassSDTau32_dRapLo_inclusive              .Fill( DijetMass       , evWeight*rate[0])
              h_bkgdEst_modMass_tagMassSDTau32_dRapLo_inclusive      .Fill( DijetMass_modMass_jet1, evWeight*rate[0])
              if newbtagjet0 and newbtagjet1:
                  #2btag
                  mttPredDist_tagMassSDTau32_dRapLo_DijetMass_2btag            .Accumulate(              DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_tagMassSDTau32_dRapLo_DijetMass_2btag   , False )
                  mttPredDist_tagMassSDTau32_dRapLo_JetMass_2btag              .Accumulate(             jet1P4.M(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetMass_2btag      , False )
                  mttPredDist_tagMassSDTau32_dRapLo_JetPt_2btag                .Accumulate(           jet1P4.Perp(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetPt_2btag        , False )
                  mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_2btag               .Accumulate(       jet1P4.Rapidity(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_2btag       , False )
                  mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_2btag         .Accumulate(        Jet1MassSoftDrop, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_2btag , False )
                  mttPredDist_tagMassSDTau32_dRapLo_Tau32_2btag                .Accumulate(               Jet1Tau32, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_Tau32_2btag        , False )
                  mttPredDist_tagMassSDTau32_dRapLo_bDisc_2btag                .Accumulate(          maxBdisc_jet1_, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_bDisc_2btag        , False )

                  mttPredDist_modMass_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32_dRapLo_2btag    , False )
                  h_bkgdEst_tagMassSDTau32_dRapLo_2btag              .Fill( DijetMass             , evWeight*rate[1] )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  h_bkgdEst_modMass_tagMassSDTau32_dRapLo_2btag      .Fill( DijetMass_modMass_jet1, evWeight*rate[1] )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              if (newbtagjet0 and not newbtagjet1):
                  #1btag
                  mttPredDist_tagMassSDTau32_dRapLo_DijetMass_1btag            .Accumulate(              DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_DijetMass_1btag    , False )
                  mttPredDist_tagMassSDTau32_dRapLo_JetMass_1btag              .Accumulate(             jet1P4.M(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetMass_1btag      , False )
                  mttPredDist_tagMassSDTau32_dRapLo_JetPt_1btag                .Accumulate(           jet1P4.Perp(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetPt_1btag        , False )
                  mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_1btag               .Accumulate(       jet1P4.Rapidity(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_1btag       , False )
                  mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_1btag         .Accumulate(        Jet1MassSoftDrop, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_1btag , False )
                  mttPredDist_tagMassSDTau32_dRapLo_Tau32_1btag                .Accumulate(               Jet1Tau32, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_Tau32_1btag        , False )
                  mttPredDist_tagMassSDTau32_dRapLo_bDisc_1btag                .Accumulate(          maxBdisc_jet1_, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_bDisc_1btag        , False )

                  mttPredDist_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32_dRapLo_1btag    , False )
                  h_bkgdEst_tagMassSDTau32_dRapLo_1btag              .Fill( DijetMass             , evWeight*rate[2] )# * sf1_MassTau32 * sf0_MassTau32bTag)
                  h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag      .Fill( DijetMass_modMass_jet1, evWeight*rate[2] )# * sf1_MassTau32 * sf0_MassTau32bTag)
              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist_tagMassSDTau32_dRapLo_DijetMass_1btag            .Accumulate(              DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_DijetMass_1btag    , False )
                  mttPredDist_tagMassSDTau32_dRapLo_JetMass_1btag              .Accumulate(             jet1P4.M(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetMass_1btag      , False )
                  mttPredDist_tagMassSDTau32_dRapLo_JetPt_1btag                .Accumulate(           jet1P4.Perp(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetPt_1btag        , False )
                  mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_1btag               .Accumulate(       jet1P4.Rapidity(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_1btag       , False )
                  mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_1btag         .Accumulate(        Jet1MassSoftDrop, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_1btag , False )
                  mttPredDist_tagMassSDTau32_dRapLo_Tau32_1btag                .Accumulate(               Jet1Tau32, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_Tau32_1btag        , False )
                  mttPredDist_tagMassSDTau32_dRapLo_bDisc_1btag                .Accumulate(          maxBdisc_jet1_, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_bDisc_1btag        , False )

                  mttPredDist_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32_dRapLo_1btag    , False )
                  h_bkgdEst_tagMassSDTau32_dRapLo_1btag              .Fill( DijetMass             , evWeight*rate[2] )#* sf0_MassTau32 * sf1_MassTau32bTag )
                  h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag      .Fill( DijetMass_modMass_jet1, evWeight*rate[2] )#* sf0_MassTau32 * sf1_MassTau32bTag )
              if not newbtagjet0 and not newbtagjet1:
                  #0btag
                  mttPredDist_tagMassSDTau32_dRapLo_DijetMass_0btag            .Accumulate(                        DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_DijetMass_0btag    , False )
                  mttPredDist_tagMassSDTau32_dRapLo_JetMass_0btag              .Accumulate(             jet1P4.M(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetMass_0btag      , False )
                  mttPredDist_tagMassSDTau32_dRapLo_JetPt_0btag                .Accumulate(           jet1P4.Perp(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetPt_0btag        , False )
                  mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_0btag               .Accumulate(       jet1P4.Rapidity(), jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_0btag       , False )
                  mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_0btag         .Accumulate(        Jet1MassSoftDrop, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_0btag , False )
                  mttPredDist_tagMassSDTau32_dRapLo_Tau32_0btag                .Accumulate(               Jet1Tau32, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_Tau32_0btag        , False )
                  mttPredDist_tagMassSDTau32_dRapLo_bDisc_0btag                .Accumulate(          maxBdisc_jet1_, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_bDisc_0btag        , False )

                  mttPredDist_modMass_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32_dRapLo_0btag    , False )
                  h_bkgdEst_tagMassSDTau32_dRapLo_0btag              .Fill( DijetMass             , evWeight*rate[3] )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  h_bkgdEst_modMass_tagMassSDTau32_dRapLo_0btag      .Fill( DijetMass_modMass_jet1, evWeight*rate[3] )#* sf1_MassTau32 * sf1_MassTau32bTag )

      # Mistag as a function of P
      if topTag0MassSDTau32 :

          #inclusive
          mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_inclusive            .Accumulate(              DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_inclusive    , False )
          mttPredDist2_tagMassSDTau32_dRapIn_JetMass_inclusive              .Accumulate(             jet1P4.M(), jet1P4.P(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetMass_inclusive      , False )
          mttPredDist2_tagMassSDTau32_dRapIn_JetPt_inclusive                .Accumulate(           jet1P4.P(), jet1P4.P(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetPt_inclusive        , False )
          mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_inclusive               .Accumulate(       jet1P4.Rapidity(), jet1P4.P(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_inclusive       , False )
          mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_inclusive         .Accumulate(        Jet1MassSoftDrop, jet1P4.P(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_inclusive , False )
          mttPredDist2_tagMassSDTau32_dRapIn_Tau32_inclusive                .Accumulate(               Jet1Tau32, jet1P4.P(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_Tau32_inclusive        , False )
          mttPredDist2_tagMassSDTau32_dRapIn_bDisc_inclusive                .Accumulate(          maxBdisc_jet1_, jet1P4.P(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_bDisc_inclusive        , False )

          mttPredDist2_modMass_tagMassSDTau32_dRapIn_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership( mttPredDist2_modMass_tagMassSDTau32_dRapIn_inclusive    , False )

          if newbtagjet0 and newbtagjet1:
              #2btag
              mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_2btag            .Accumulate(              DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership(  mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_2btag   , False )
              mttPredDist2_tagMassSDTau32_dRapIn_JetMass_2btag              .Accumulate(             jet1P4.M(), jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetMass_2btag      , False )
              mttPredDist2_tagMassSDTau32_dRapIn_JetPt_2btag                .Accumulate(           jet1P4.P(), jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetPt_2btag        , False )
              mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_2btag               .Accumulate(       jet1P4.Rapidity(), jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_2btag       , False )
              mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_2btag         .Accumulate(        Jet1MassSoftDrop, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_2btag , False )
              mttPredDist2_tagMassSDTau32_dRapIn_Tau32_2btag                .Accumulate(               Jet1Tau32, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_Tau32_2btag        , False )
              mttPredDist2_tagMassSDTau32_dRapIn_bDisc_2btag                .Accumulate(          maxBdisc_jet1_, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_bDisc_2btag        , False )

              mttPredDist2_modMass_tagMassSDTau32_dRapIn_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership(  mttPredDist2_modMass_tagMassSDTau32_dRapIn_2btag   , False )

          if (newbtagjet0 and not newbtagjet1):
              #1btag
              mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_1btag            .Accumulate(              DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_1btag    , False )
              mttPredDist2_tagMassSDTau32_dRapIn_JetMass_1btag              .Accumulate(             jet1P4.M(), jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetMass_1btag      , False )
              mttPredDist2_tagMassSDTau32_dRapIn_JetPt_1btag                .Accumulate(           jet1P4.P(), jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetPt_1btag        , False )
              mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_1btag               .Accumulate(       jet1P4.Rapidity(), jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_1btag       , False )
              mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_1btag         .Accumulate(        Jet1MassSoftDrop, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_1btag , False )
              mttPredDist2_tagMassSDTau32_dRapIn_Tau32_1btag                .Accumulate(               Jet1Tau32, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_Tau32_1btag        , False )
              mttPredDist2_tagMassSDTau32_dRapIn_bDisc_1btag                .Accumulate(          maxBdisc_jet1_, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_bDisc_1btag        , False )

              mttPredDist2_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_modMass_tagMassSDTau32_dRapIn_1btag    , False )

          if (newbtagjet1 and not newbtagjet0):
              mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_1btag            .Accumulate(              DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_1btag    , False )
              mttPredDist2_tagMassSDTau32_dRapIn_JetMass_1btag              .Accumulate(             jet1P4.M(), jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetMass_1btag      , False )
              mttPredDist2_tagMassSDTau32_dRapIn_JetPt_1btag                .Accumulate(           jet1P4.P(), jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetPt_1btag        , False )
              mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_1btag               .Accumulate(       jet1P4.Rapidity(), jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_1btag       , False )
              mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_1btag         .Accumulate(        Jet1MassSoftDrop, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_1btag , False )
              mttPredDist2_tagMassSDTau32_dRapIn_Tau32_1btag                .Accumulate(               Jet1Tau32, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_Tau32_1btag        , False )
              mttPredDist2_tagMassSDTau32_dRapIn_bDisc_1btag                .Accumulate(          maxBdisc_jet1_, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_bDisc_1btag        , False )

              mttPredDist2_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership(  mttPredDist2_modMass_tagMassSDTau32_dRapIn_1btag   , False )

          if not newbtagjet0 and not newbtagjet1:
              #0btag
              mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_0btag            .Accumulate(                        DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_0btag    , False )
              mttPredDist2_tagMassSDTau32_dRapIn_JetMass_0btag              .Accumulate(             jet1P4.M(), jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetMass_0btag      , False )
              mttPredDist2_tagMassSDTau32_dRapIn_JetPt_0btag                .Accumulate(           jet1P4.P(), jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetPt_0btag        , False )
              mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_0btag               .Accumulate(       jet1P4.Rapidity(), jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_0btag       , False )
              mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_0btag         .Accumulate(        Jet1MassSoftDrop, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_0btag , False )
              mttPredDist2_tagMassSDTau32_dRapIn_Tau32_0btag                .Accumulate(               Jet1Tau32, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_Tau32_0btag        , False )
              mttPredDist2_tagMassSDTau32_dRapIn_bDisc_0btag                .Accumulate(          maxBdisc_jet1_, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_bDisc_0btag        , False )

              mttPredDist2_modMass_tagMassSDTau32_dRapIn_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_modMass_tagMassSDTau32_dRapIn_0btag    , False )
      

          if event.DijetDeltaRap > 1 :
              #inclusive
              mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_inclusive            .Accumulate(              DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_inclusive    , False )
              mttPredDist2_tagMassSDTau32_dRapHi_JetMass_inclusive              .Accumulate(             jet1P4.M(), jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetMass_inclusive      , False )
              mttPredDist2_tagMassSDTau32_dRapHi_JetPt_inclusive                .Accumulate(           jet1P4.P(), jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetPt_inclusive        , False )
              mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_inclusive               .Accumulate(       jet1P4.Rapidity(), jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_inclusive       , False )
              mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_inclusive         .Accumulate(        Jet1MassSoftDrop, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_inclusive , False )
              mttPredDist2_tagMassSDTau32_dRapHi_Tau32_inclusive                .Accumulate(               Jet1Tau32, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_Tau32_inclusive        , False )
              mttPredDist2_tagMassSDTau32_dRapHi_bDisc_inclusive                .Accumulate(          maxBdisc_jet1_, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_bDisc_inclusive        , False )

              mttPredDist2_modMass_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_modMass_tagMassSDTau32_dRapHi_inclusive    , False )

              if newbtagjet0 and newbtagjet1:
                  #2btag
                  mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_2btag            .Accumulate(              DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_2btag   , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_JetMass_2btag              .Accumulate(             jet1P4.M(), jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetMass_2btag      , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_JetPt_2btag                .Accumulate(           jet1P4.P(), jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetPt_2btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_2btag               .Accumulate(       jet1P4.Rapidity(), jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_2btag       , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_2btag         .Accumulate(        Jet1MassSoftDrop, jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_2btag , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_Tau32_2btag                .Accumulate(               Jet1Tau32, jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_Tau32_2btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_bDisc_2btag                .Accumulate(          maxBdisc_jet1_, jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_bDisc_2btag        , False )

                  mttPredDist2_modMass_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist2_modMass_tagMassSDTau32_dRapHi_2btag   , False )

              if (newbtagjet0 and not newbtagjet1):
                  #1btag
                  mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_1btag            .Accumulate(              DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_1btag    , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_JetMass_1btag              .Accumulate(             jet1P4.M(), jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetMass_1btag      , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_JetPt_1btag                .Accumulate(           jet1P4.P(), jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetPt_1btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_1btag               .Accumulate(       jet1P4.Rapidity(), jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_1btag       , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_1btag         .Accumulate(        Jet1MassSoftDrop, jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_1btag , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_Tau32_1btag                .Accumulate(               Jet1Tau32, jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_Tau32_1btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_bDisc_1btag                .Accumulate(          maxBdisc_jet1_, jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_bDisc_1btag        , False )

                  mttPredDist2_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_modMass_tagMassSDTau32_dRapHi_1btag    , False )

              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_1btag            .Accumulate(              DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_1btag    , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_JetMass_1btag              .Accumulate(             jet1P4.M(), jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetMass_1btag      , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_JetPt_1btag                .Accumulate(           jet1P4.P(), jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetPt_1btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_1btag               .Accumulate(       jet1P4.Rapidity(), jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_1btag       , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_1btag         .Accumulate(        Jet1MassSoftDrop, jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_1btag , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_Tau32_1btag                .Accumulate(               Jet1Tau32, jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_Tau32_1btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_bDisc_1btag                .Accumulate(          maxBdisc_jet1_, jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_bDisc_1btag        , False )

                  mttPredDist2_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist2_modMass_tagMassSDTau32_dRapHi_1btag   , False )

              if not newbtagjet0 and not newbtagjet1:
                  #0btag
                  mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_0btag            .Accumulate(                        DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_0btag    , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_JetMass_0btag              .Accumulate(             jet1P4.M(), jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetMass_0btag      , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_JetPt_0btag                .Accumulate(           jet1P4.P(), jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetPt_0btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_0btag               .Accumulate(       jet1P4.Rapidity(), jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_0btag       , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_0btag         .Accumulate(        Jet1MassSoftDrop, jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_0btag , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_Tau32_0btag                .Accumulate(               Jet1Tau32, jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_Tau32_0btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_bDisc_0btag                .Accumulate(          maxBdisc_jet1_, jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_bDisc_0btag        , False )

                  mttPredDist2_modMass_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_modMass_tagMassSDTau32_dRapHi_0btag    , False )
          
          if event.DijetDeltaRap < 1:
              #inclusive
              mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_inclusive            .Accumulate(              DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_inclusive    , False )
              mttPredDist2_tagMassSDTau32_dRapLo_JetMass_inclusive              .Accumulate(             jet1P4.M(), jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetMass_inclusive      , False )
              mttPredDist2_tagMassSDTau32_dRapLo_JetPt_inclusive                .Accumulate(           jet1P4.P(), jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetPt_inclusive        , False )
              mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_inclusive               .Accumulate(       jet1P4.Rapidity(), jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_inclusive       , False )
              mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_inclusive         .Accumulate(        Jet1MassSoftDrop, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_inclusive , False )
              mttPredDist2_tagMassSDTau32_dRapLo_Tau32_inclusive                .Accumulate(               Jet1Tau32, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_Tau32_inclusive        , False )
              mttPredDist2_tagMassSDTau32_dRapLo_bDisc_inclusive                .Accumulate(          maxBdisc_jet1_, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_bDisc_inclusive        , False )

              mttPredDist2_modMass_tagMassSDTau32_dRapLo_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership(  mttPredDist2_modMass_tagMassSDTau32_dRapLo_inclusive   , False )

              if newbtagjet0 and newbtagjet1:
                  #2btag
                  mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_2btag            .Accumulate(              DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_2btag   , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_JetMass_2btag              .Accumulate(             jet1P4.M(), jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetMass_2btag      , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_JetPt_2btag                .Accumulate(           jet1P4.P(), jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetPt_2btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_2btag               .Accumulate(       jet1P4.Rapidity(), jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_2btag       , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_2btag         .Accumulate(        Jet1MassSoftDrop, jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_2btag , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_Tau32_2btag                .Accumulate(               Jet1Tau32, jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_Tau32_2btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_bDisc_2btag                .Accumulate(          maxBdisc_jet1_, jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_bDisc_2btag        , False )

                  mttPredDist2_modMass_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_modMass_tagMassSDTau32_dRapLo_2btag    , False )

              if (newbtagjet0 and not newbtagjet1):
                  #1btag
                  mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_1btag            .Accumulate(              DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_1btag    , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_JetMass_1btag              .Accumulate(             jet1P4.M(), jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetMass_1btag      , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_JetPt_1btag                .Accumulate(           jet1P4.P(), jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetPt_1btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_1btag               .Accumulate(       jet1P4.Rapidity(), jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_1btag       , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_1btag         .Accumulate(        Jet1MassSoftDrop, jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_1btag , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_Tau32_1btag                .Accumulate(               Jet1Tau32, jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_Tau32_1btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_bDisc_1btag                .Accumulate(          maxBdisc_jet1_, jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_bDisc_1btag        , False )

                  mttPredDist2_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_modMass_tagMassSDTau32_dRapLo_1btag    , False )

              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_1btag            .Accumulate(              DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_1btag    , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_JetMass_1btag              .Accumulate(             jet1P4.M(), jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetMass_1btag      , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_JetPt_1btag                .Accumulate(           jet1P4.P(), jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetPt_1btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_1btag               .Accumulate(       jet1P4.Rapidity(), jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_1btag       , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_1btag         .Accumulate(        Jet1MassSoftDrop, jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_1btag , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_Tau32_1btag                .Accumulate(               Jet1Tau32, jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_Tau32_1btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_bDisc_1btag                .Accumulate(          maxBdisc_jet1_, jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_bDisc_1btag        , False )

                  mttPredDist2_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_modMass_tagMassSDTau32_dRapLo_1btag    , False )

              if not newbtagjet0 and not newbtagjet1:
                  #0btag
                  mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_0btag            .Accumulate(                        DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_0btag    , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_JetMass_0btag              .Accumulate(             jet1P4.M(), jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetMass_0btag      , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_JetPt_0btag                .Accumulate(           jet1P4.P(), jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetPt_0btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_0btag               .Accumulate(       jet1P4.Rapidity(), jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_0btag       , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_0btag         .Accumulate(        Jet1MassSoftDrop, jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_0btag , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_Tau32_0btag                .Accumulate(               Jet1Tau32, jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_Tau32_0btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_bDisc_0btag                .Accumulate(          maxBdisc_jet1_, jet1P4.P(), topTag1MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_bDisc_0btag        , False )

                  mttPredDist2_modMass_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_modMass_tagMassSDTau32_dRapLo_0btag    , False )

      # 
      if topTag0MassSDTau32 and oddEvent :
          mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_inclusive    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership(  mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_inclusive   , False )
          mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_inclusive    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership(  mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_inclusive   , False )

          mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership(  mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_inclusive   , False )
          mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership(  mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_inclusive   , False )
          
          if newbtagjet0 and newbtagjet1:
              #2btag
              mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_2btag    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_2btag    , False )
              mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_2btag    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_2btag    , False )

              mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_2btag    , False )
              mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_2btag    , False )

          if (newbtagjet0 and not newbtagjet1):
              #1btag
              mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag    , False )
              mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag    , False )
              
              mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag    , False )
              mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag    , False )
                 

          if (newbtagjet1 and not newbtagjet0):

              mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag    , False )
              mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag    , False )

              mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag    , False )
              mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag    , False )

              

          if not newbtagjet0 and not newbtagjet1:

              mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_0btag    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_0btag    , False )
              mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_0btag    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_0btag    , False )

              mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_0btag    , False )
              mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_0btag    , False )


          if event.DijetDeltaRap > 1 :
              
              mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_inclusive    , False )
              mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_inclusive    , False )
              
              mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_inclusive    , False )
              mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_inclusive    , False )
              

              if newbtagjet0 and newbtagjet1:
                  mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass , jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_2btag   , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass , jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_2btag   , False )
              
                  mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_2btag   , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_2btag   , False )
              

              if (newbtagjet0 and not newbtagjet1):
                  mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag    , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag    , False )
              
                  mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag    , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag    , False )
              
              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag   , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag   , False )

                  mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag   , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag   , False )

                  
              if not newbtagjet0 and not newbtagjet1:
                  mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_0btag    , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_0btag    , False )
          
                  mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_0btag    , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_0btag    , False )
          
          if event.DijetDeltaRap < 1:
              #inclusive

              mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership(  mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_inclusive   , False )
              mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership(  mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_inclusive   , False )
              

              if newbtagjet0 and newbtagjet1:

                  mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_2btag    , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_2btag    , False )


                  mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_2btag    , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_2btag    , False )

                  

              if (newbtagjet0 and not newbtagjet1):
                  mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag    , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag    , False )
              
                  mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag    , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag    , False )
              

              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag    , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag    , False )

                  mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag    , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag    , False )

                  

              if not newbtagjet0 and not newbtagjet1:
                  mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_0btag    , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_0btag    , False )
                 
                  mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_0btag    , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_0btag    , False )

                 
      if topTag0MassSDTau32 and evenEvent :
          mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_inclusive    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership(  mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_inclusive   , False )
          mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_inclusive    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership(  mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_inclusive   , False )

          mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership(  mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_inclusive   , False )
          mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership(  mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_inclusive   , False )
          
          if newbtagjet0 and newbtagjet1:
              #2btag
              mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_2btag    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_2btag    , False )
              mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_2btag    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_2btag    , False )

              mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_2btag    , False )
              mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_2btag    , False )

          if (newbtagjet0 and not newbtagjet1):
              #1btag
              mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag    , False )
              mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag    , False )
              
              mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag    , False )
              mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag    , False )
                 

          if (newbtagjet1 and not newbtagjet0):

              mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag    , False )
              mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag    , False )

              mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag    , False )
              mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag    , False )

              

          if not newbtagjet0 and not newbtagjet1:

              mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_0btag    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_0btag    , False )
              mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_0btag    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_0btag    , False )

              mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_0btag    , False )
              mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_0btag    , False )


          if event.DijetDeltaRap > 1 :
              
              mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_inclusive    , False )
              mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_inclusive    , False )
              
              mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_inclusive    , False )
              mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_inclusive    , False )
              

              if newbtagjet0 and newbtagjet1:
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass , jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_2btag   , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass , jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_2btag   , False )
              
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_2btag   , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_2btag   , False )
              

              if (newbtagjet0 and not newbtagjet1):
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag    , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag    , False )
              
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag    , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag    , False )
              
              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag   , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag   , False )

                  mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag   , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag   , False )

                  
              if not newbtagjet0 and not newbtagjet1:
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_0btag    , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_0btag    , False )
          
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_0btag    , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_0btag    , False )
          
          if event.DijetDeltaRap < 1:
              #inclusive
              mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership(  mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_inclusive   , False )
              mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership(  mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_inclusive   , False )
              
              if newbtagjet0 and newbtagjet1:
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_2btag    , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_2btag    , False )


                  mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_2btag    , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_2btag    , False )

                  

              if (newbtagjet0 and not newbtagjet1):
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag    , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag    , False )
              
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag    , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag    , False )
              

              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag    , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag    , False )

                  mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag    , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag    , False )  

              if not newbtagjet0 and not newbtagjet1:
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_0btag    , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_0btag    , False )
                 
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_0btag    , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.P(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_0btag    , False )
                 




      if topTag0MassSDTau32  :
          mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership(  mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_inclusive   , False )
          if newbtagjet0 and newbtagjet1:
              #2btag
              mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_2btag    , False )
          if (newbtagjet0 and not newbtagjet1):
              #1btag
              mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_1btag    , False )
          if (newbtagjet1 and not newbtagjet0):
              mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_1btag    , False )
          if not newbtagjet0 and not newbtagjet1:
              mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_0btag    , False )

          if event.DijetDeltaRap > 1 :
              mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_inclusive    , False )
              if newbtagjet0 and newbtagjet1:
                  mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_2btag   , False )
              if (newbtagjet0 and not newbtagjet1):
                  mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_1btag    , False )
              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_1btag   , False )
              if not newbtagjet0 and not newbtagjet1:
                  mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_0btag    , False )
          
          if event.DijetDeltaRap < 1:
              #inclusive
              mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership(  mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_inclusive   , False )
              if newbtagjet0 and newbtagjet1:
                  mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_2btag    , False )
              if (newbtagjet0 and not newbtagjet1):
                  mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_1btag    , False )
              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_1btag    , False )
              if not newbtagjet0 and not newbtagjet1:
                  mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_0btag    , False )
      if topTag0MassSDTau32  :
          mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership(  mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_inclusive   , False )
          if newbtagjet0 and newbtagjet1:
              #2btag
              mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_2btag    , False )
          if (newbtagjet0 and not newbtagjet1):
              #1btag
              mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_1btag    , False )
          if (newbtagjet1 and not newbtagjet0):
              mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_1btag    , False )
          if not newbtagjet0 and not newbtagjet1:
              mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_0btag    , False )

          if event.DijetDeltaRap > 1 :
              mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_inclusive    , False )
              if newbtagjet0 and newbtagjet1:
                  mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_2btag   , False )
              if (newbtagjet0 and not newbtagjet1):
                  mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_1btag    , False )
              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_1btag   , False )
              if not newbtagjet0 and not newbtagjet1:
                  mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_0btag    , False )
          
          if event.DijetDeltaRap < 1:
              #inclusive
              mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership(  mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_inclusive   , False )
              if newbtagjet0 and newbtagjet1:
                  mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_2btag    , False )
              if (newbtagjet0 and not newbtagjet1):
                  mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_1btag    , False )
              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_1btag    , False )
              if not newbtagjet0 and not newbtagjet1:
                  mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_0btag    , False )
      if topTag0MassSDTau32  :
          mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership(  mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_inclusive   , False )
          if newbtagjet0 and newbtagjet1:
              #2btag
              mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_2btag    , False )
          if (newbtagjet0 and not newbtagjet1):
              #1btag
              mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_1btag    , False )
          if (newbtagjet1 and not newbtagjet0):
              mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_1btag    , False )
          if not newbtagjet0 and not newbtagjet1:
              mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_0btag    , False )

          if event.DijetDeltaRap > 1 :
              mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_inclusive    , False )
              if newbtagjet0 and newbtagjet1:
                  mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_2btag   , False )
              if (newbtagjet0 and not newbtagjet1):
                  mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_1btag    , False )
              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_1btag   , False )
              if not newbtagjet0 and not newbtagjet1:
                  mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_0btag    , False )
          
          if event.DijetDeltaRap < 1:
              #inclusive
              mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_inclusive    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership(  mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_inclusive   , False )
              if newbtagjet0 and newbtagjet1:
                  mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_2btag    , False )
              if (newbtagjet0 and not newbtagjet1):
                  mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_1btag    , False )
              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_1btag    , False )
              if not newbtagjet0 and not newbtagjet1:
                  mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass_modMass_jet1, jet1P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_0btag    , False )
  
 


  

  # randomly select jet 1 to be the tag then fill predDist based on probability that jet 0 is mis-tagged
  if rand_bkgdest >= 0.5 :

      # Mistag as a function of p_T
      if topTag1MassSDTau32 :
          # mttPredDist_tagMassSDTau32        .Accumulate(              ttMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
          # mttPredDist_modMass_tagMassSDTau32.Accumulate( ttMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
          for i in xrange(len(post)):
              bin.append (h_mistag_vs_jetPt_TagMassSDTau32[i].GetXaxis().FindBin( event.Jet0Pt ))
              rate.append( h_mistag_vs_jetPt_TagMassSDTau32[i].GetBinContent(bin[i]))
          
          # dRap all 
          # inclusive
          mttPredDist_tagMassSDTau32_dRapIn_DijetMass_inclusive            .Accumulate(              DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
          ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_DijetMass_inclusive    , False )
          mttPredDist_tagMassSDTau32_dRapIn_JetMass_inclusive              .Accumulate(             jet0P4.M(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
          ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetMass_inclusive      , False )
          mttPredDist_tagMassSDTau32_dRapIn_JetPt_inclusive                .Accumulate(           jet0P4.Perp(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
          ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetPt_inclusive        , False )
          mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_inclusive               .Accumulate(       jet0P4.Rapidity(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
          ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_inclusive       , False )
          mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_inclusive         .Accumulate(        Jet0MassSoftDrop, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
          ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_inclusive , False )
          mttPredDist_tagMassSDTau32_dRapIn_Tau32_inclusive                .Accumulate(               Jet0Tau32, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
          ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_Tau32_inclusive        , False )
          mttPredDist_tagMassSDTau32_dRapIn_bDisc_inclusive                .Accumulate(          maxBdisc_jet0_, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
          ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_bDisc_inclusive        , False )

          mttPredDist_modMass_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
          ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32_dRapHi_inclusive    , False )
          h_bkgdEst_tagMassSDTau32_dRapHi_inclusive              .Fill( DijetMass             , evWeight*rate[0])
          h_bkgdEst_modMass_tagMassSDTau32_dRapHi_inclusive      .Fill( DijetMass_modMass_jet0, evWeight*rate[0])
          if newbtagjet0 and newbtagjet1:
              #2btag
              mttPredDist_tagMassSDTau32_dRapIn_DijetMass_2btag            .Accumulate(              DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf0_MassTau32bTag )
              ROOT.SetOwnership(  mttPredDist_tagMassSDTau32_dRapIn_DijetMass_2btag   , False )
              mttPredDist_tagMassSDTau32_dRapIn_JetMass_2btag              .Accumulate(             jet0P4.M(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetMass_2btag      , False )
              mttPredDist_tagMassSDTau32_dRapIn_JetPt_2btag                .Accumulate(           jet0P4.Perp(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetPt_2btag        , False )
              mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_2btag               .Accumulate(       jet0P4.Rapidity(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_2btag       , False )
              mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_2btag         .Accumulate(        Jet0MassSoftDrop, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_2btag , False )
              mttPredDist_tagMassSDTau32_dRapIn_Tau32_2btag                .Accumulate(               Jet0Tau32, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_Tau32_2btag        , False )
              mttPredDist_tagMassSDTau32_dRapIn_bDisc_2btag                .Accumulate(          maxBdisc_jet0_, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_bDisc_2btag        , False )

              mttPredDist_modMass_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32_dRapHi_2btag    , False )
              h_bkgdEst_tagMassSDTau32_dRapHi_2btag              .Fill( DijetMass             , evWeight*rate[1] )#* sf0_MassTau32bTag * sf1_MassTau32bTag )
              h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag      .Fill( DijetMass_modMass_jet0, evWeight*rate[1] )#* sf0_MassTau32bTag * sf1_MassTau32bTag )
          if (newbtagjet0 and not newbtagjet1):
              #1btag
              mttPredDist_tagMassSDTau32_dRapIn_DijetMass_1btag            .Accumulate(              DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_DijetMass_1btag    , False )
              mttPredDist_tagMassSDTau32_dRapIn_JetMass_1btag              .Accumulate(             jet0P4.M(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetMass_1btag      , False )
              mttPredDist_tagMassSDTau32_dRapIn_JetPt_1btag                .Accumulate(           jet0P4.Perp(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetPt_1btag        , False )
              mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_1btag               .Accumulate(       jet0P4.Rapidity(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_1btag       , False )
              mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_1btag         .Accumulate(        Jet0MassSoftDrop, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_1btag , False )
              mttPredDist_tagMassSDTau32_dRapIn_Tau32_1btag                .Accumulate(               Jet0Tau32, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_Tau32_1btag        , False )
              mttPredDist_tagMassSDTau32_dRapIn_bDisc_1btag                .Accumulate(          maxBdisc_jet0_, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_bDisc_1btag        , False )

              mttPredDist_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32_dRapHi_1btag    , False )
              h_bkgdEst_tagMassSDTau32_dRapHi_1btag              .Fill( DijetMass             , evWeight*rate[2] )#* sf1_MassTau32 * sf0_MassTau32bTag)
              h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag      .Fill( DijetMass_modMass_jet0, evWeight*rate[2] )#* sf1_MassTau32 * sf0_MassTau32bTag) 
          if (newbtagjet1 and not newbtagjet0):
              mttPredDist_tagMassSDTau32_dRapIn_DijetMass_1btag            .Accumulate(              DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_DijetMass_1btag    , False )
              mttPredDist_tagMassSDTau32_dRapIn_JetMass_1btag              .Accumulate(             jet0P4.M(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetMass_1btag      , False )
              mttPredDist_tagMassSDTau32_dRapIn_JetPt_1btag                .Accumulate(           jet0P4.Perp(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetPt_1btag        , False )
              mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_1btag               .Accumulate(       jet0P4.Rapidity(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_1btag       , False )
              mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_1btag         .Accumulate(        Jet0MassSoftDrop, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_1btag , False )
              mttPredDist_tagMassSDTau32_dRapIn_Tau32_1btag                .Accumulate(               Jet0Tau32, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_Tau32_1btag        , False )
              mttPredDist_tagMassSDTau32_dRapIn_bDisc_1btag                .Accumulate(          maxBdisc_jet0_, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_bDisc_1btag        , False )

              mttPredDist_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf0_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32_dRapHi_1btag    , False )
              h_bkgdEst_tagMassSDTau32_dRapHi_1btag              .Fill( DijetMass             , evWeight*rate[2] )#* sf0_MassTau32 * sf1_MassTau32bTag )
              h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag      .Fill( DijetMass_modMass_jet0, evWeight*rate[2] )#* sf0_MassTau32 * sf1_MassTau32bTag )
          if not newbtagjet0 and not newbtagjet1:
              #0btag
              mttPredDist_tagMassSDTau32_dRapIn_DijetMass_0btag            .Accumulate(              DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_DijetMass_0btag    , False )
              mttPredDist_tagMassSDTau32_dRapIn_JetMass_0btag              .Accumulate(             jet0P4.M(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetMass_0btag      , False )
              mttPredDist_tagMassSDTau32_dRapIn_JetPt_0btag                .Accumulate(           jet0P4.Perp(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetPt_0btag        , False )
              mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_0btag               .Accumulate(       jet0P4.Rapidity(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_0btag       , False )
              mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_0btag         .Accumulate(        Jet0MassSoftDrop, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_0btag , False )
              mttPredDist_tagMassSDTau32_dRapIn_Tau32_0btag                .Accumulate(               Jet0Tau32, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_Tau32_0btag        , False )
              mttPredDist_tagMassSDTau32_dRapIn_bDisc_0btag                .Accumulate(          maxBdisc_jet0_, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapIn_bDisc_0btag        , False )

              mttPredDist_modMass_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32_dRapHi_0btag   , False )
              h_bkgdEst_tagMassSDTau32_dRapHi_0btag              .Fill( DijetMass             , evWeight*rate[3] )#* sf1_MassTau32 * sf1_MassTau32bTag )
              h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag      .Fill( DijetMass_modMass_jet0, evWeight*rate[3] )#* sf1_MassTau32 * sf1_MassTau32bTag )
      

          if event.DijetDeltaRap > 1 :
              #inclusive
              mttPredDist_tagMassSDTau32_dRapHi_DijetMass_inclusive            .Accumulate(              DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_DijetMass_inclusive    , False )
              mttPredDist_tagMassSDTau32_dRapHi_JetMass_inclusive              .Accumulate(             jet0P4.M(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetMass_inclusive      , False )
              mttPredDist_tagMassSDTau32_dRapHi_JetPt_inclusive                .Accumulate(           jet0P4.Perp(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetPt_inclusive        , False )
              mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_inclusive               .Accumulate(       jet0P4.Rapidity(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_inclusive       , False )
              mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_inclusive         .Accumulate(        Jet0MassSoftDrop, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_inclusive , False )
              mttPredDist_tagMassSDTau32_dRapHi_Tau32_inclusive                .Accumulate(               Jet0Tau32, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_Tau32_inclusive        , False )
              mttPredDist_tagMassSDTau32_dRapHi_bDisc_inclusive                .Accumulate(          maxBdisc_jet0_, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_bDisc_inclusive        , False )

              mttPredDist_modMass_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32_dRapHi_inclusive    , False )
              h_bkgdEst_tagMassSDTau32_dRapHi_inclusive              .Fill( DijetMass             , evWeight*rate[0])
              h_bkgdEst_modMass_tagMassSDTau32_dRapHi_inclusive      .Fill( DijetMass_modMass_jet0, evWeight*rate[0])
              if newbtagjet0 and newbtagjet1:
                  #2btag
                  mttPredDist_tagMassSDTau32_dRapHi_DijetMass_2btag            .Accumulate(              DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf0_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_tagMassSDTau32_dRapHi_DijetMass_2btag   , False )
                  mttPredDist_tagMassSDTau32_dRapHi_JetMass_2btag              .Accumulate(             jet0P4.M(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetMass_2btag      , False )
                  mttPredDist_tagMassSDTau32_dRapHi_JetPt_2btag                .Accumulate(           jet0P4.Perp(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetPt_2btag        , False )
                  mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_2btag               .Accumulate(       jet0P4.Rapidity(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_2btag       , False )
                  mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_2btag         .Accumulate(        Jet0MassSoftDrop, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_2btag , False )
                  mttPredDist_tagMassSDTau32_dRapHi_Tau32_2btag                .Accumulate(               Jet0Tau32, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_Tau32_2btag        , False )
                  mttPredDist_tagMassSDTau32_dRapHi_bDisc_2btag                .Accumulate(          maxBdisc_jet0_, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_bDisc_2btag        , False )

                  mttPredDist_modMass_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32_dRapHi_2btag    , False )
                  h_bkgdEst_tagMassSDTau32_dRapHi_2btag              .Fill( DijetMass             , evWeight*rate[1] )#* sf0_MassTau32bTag * sf1_MassTau32bTag )
                  h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag      .Fill( DijetMass_modMass_jet0, evWeight*rate[1] )#* sf0_MassTau32bTag * sf1_MassTau32bTag )
              if (newbtagjet0 and not newbtagjet1):
                  #1btag
                  mttPredDist_tagMassSDTau32_dRapHi_DijetMass_1btag            .Accumulate(              DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_DijetMass_1btag    , False )
                  mttPredDist_tagMassSDTau32_dRapHi_JetMass_1btag              .Accumulate(             jet0P4.M(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetMass_1btag      , False )
                  mttPredDist_tagMassSDTau32_dRapHi_JetPt_1btag                .Accumulate(           jet0P4.Perp(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetPt_1btag        , False )
                  mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_1btag               .Accumulate(       jet0P4.Rapidity(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_1btag       , False )
                  mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_1btag         .Accumulate(        Jet0MassSoftDrop, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_1btag , False )
                  mttPredDist_tagMassSDTau32_dRapHi_Tau32_1btag                .Accumulate(               Jet0Tau32, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_Tau32_1btag        , False )
                  mttPredDist_tagMassSDTau32_dRapHi_bDisc_1btag                .Accumulate(          maxBdisc_jet0_, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_bDisc_1btag        , False )

                  mttPredDist_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32_dRapHi_1btag    , False )
                  h_bkgdEst_tagMassSDTau32_dRapHi_1btag              .Fill( DijetMass             , evWeight*rate[2] )#* sf1_MassTau32 * sf0_MassTau32bTag)
                  h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag      .Fill( DijetMass_modMass_jet0, evWeight*rate[2] )#* sf1_MassTau32 * sf0_MassTau32bTag) 
              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist_tagMassSDTau32_dRapHi_DijetMass_1btag            .Accumulate(              DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_DijetMass_1btag    , False )
                  mttPredDist_tagMassSDTau32_dRapHi_JetMass_1btag              .Accumulate(             jet0P4.M(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetMass_1btag      , False )
                  mttPredDist_tagMassSDTau32_dRapHi_JetPt_1btag                .Accumulate(           jet0P4.Perp(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetPt_1btag        , False )
                  mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_1btag               .Accumulate(       jet0P4.Rapidity(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_1btag       , False )
                  mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_1btag         .Accumulate(        Jet0MassSoftDrop, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_1btag , False )
                  mttPredDist_tagMassSDTau32_dRapHi_Tau32_1btag                .Accumulate(               Jet0Tau32, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_Tau32_1btag        , False )
                  mttPredDist_tagMassSDTau32_dRapHi_bDisc_1btag                .Accumulate(          maxBdisc_jet0_, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_bDisc_1btag        , False )

                  mttPredDist_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32_dRapHi_1btag    , False )
                  h_bkgdEst_tagMassSDTau32_dRapHi_1btag              .Fill( DijetMass             , evWeight*rate[2] )#* sf0_MassTau32 * sf1_MassTau32bTag )
                  h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag      .Fill( DijetMass_modMass_jet0, evWeight*rate[2] )#* sf0_MassTau32 * sf1_MassTau32bTag )
              if not newbtagjet0 and not newbtagjet1:
                  #0btag
                  mttPredDist_tagMassSDTau32_dRapHi_DijetMass_0btag            .Accumulate(              DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_DijetMass_0btag    , False )
                  mttPredDist_tagMassSDTau32_dRapHi_JetMass_0btag              .Accumulate(             jet0P4.M(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetMass_0btag      , False )
                  mttPredDist_tagMassSDTau32_dRapHi_JetPt_0btag                .Accumulate(           jet0P4.Perp(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetPt_0btag        , False )
                  mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_0btag               .Accumulate(       jet0P4.Rapidity(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_0btag       , False )
                  mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_0btag         .Accumulate(        Jet0MassSoftDrop, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_0btag , False )
                  mttPredDist_tagMassSDTau32_dRapHi_Tau32_0btag                .Accumulate(               Jet0Tau32, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_Tau32_0btag        , False )
                  mttPredDist_tagMassSDTau32_dRapHi_bDisc_0btag                .Accumulate(          maxBdisc_jet0_, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapHi_bDisc_0btag        , False )

                  mttPredDist_modMass_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32_dRapHi_0btag   , False )
                  h_bkgdEst_tagMassSDTau32_dRapHi_0btag              .Fill( DijetMass             , evWeight*rate[3] )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag      .Fill( DijetMass_modMass_jet0, evWeight*rate[3] )#* sf1_MassTau32 * sf1_MassTau32bTag )
          
          if event.DijetDeltaRap < 1:
              #inclusive
              mttPredDist_tagMassSDTau32_dRapLo_DijetMass_inclusive            .Accumulate(              DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_DijetMass_inclusive    , False )
              mttPredDist_tagMassSDTau32_dRapLo_JetMass_inclusive              .Accumulate(             jet0P4.M(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetMass_inclusive      , False )
              mttPredDist_tagMassSDTau32_dRapLo_JetPt_inclusive                .Accumulate(           jet0P4.Perp(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetPt_inclusive        , False )
              mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_inclusive               .Accumulate(       jet0P4.Rapidity(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_inclusive       , False )
              mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_inclusive         .Accumulate(        Jet0MassSoftDrop, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_inclusive , False )
              mttPredDist_tagMassSDTau32_dRapLo_Tau32_inclusive                .Accumulate(               Jet0Tau32, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_Tau32_inclusive        , False )
              mttPredDist_tagMassSDTau32_dRapLo_bDisc_inclusive                .Accumulate(          maxBdisc_jet0_, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_bDisc_inclusive        , False )

              mttPredDist_modMass_tagMassSDTau32_dRapLo_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32_dRapLo_inclusive    , False )
              h_bkgdEst_tagMassSDTau32_dRapLo_inclusive              .Fill( DijetMass             , evWeight*rate[0])
              h_bkgdEst_modMass_tagMassSDTau32_dRapLo_inclusive      .Fill( DijetMass_modMass_jet0, evWeight*rate[0])
              if newbtagjet0 and newbtagjet1:
                  #2btag
                  mttPredDist_tagMassSDTau32_dRapLo_DijetMass_2btag            .Accumulate(              DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf0_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_tagMassSDTau32_dRapLo_DijetMass_2btag   , False )
                  mttPredDist_tagMassSDTau32_dRapLo_JetMass_2btag              .Accumulate(             jet0P4.M(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetMass_2btag      , False )
                  mttPredDist_tagMassSDTau32_dRapLo_JetPt_2btag                .Accumulate(           jet0P4.Perp(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetPt_2btag        , False )
                  mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_2btag               .Accumulate(       jet0P4.Rapidity(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_2btag       , False )
                  mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_2btag         .Accumulate(        Jet0MassSoftDrop, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_2btag , False )
                  mttPredDist_tagMassSDTau32_dRapLo_Tau32_2btag                .Accumulate(               Jet0Tau32, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_Tau32_2btag        , False )
                  mttPredDist_tagMassSDTau32_dRapLo_bDisc_2btag                .Accumulate(          maxBdisc_jet0_, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_bDisc_2btag        , False )

                  mttPredDist_modMass_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32_dRapLo_2btag    , False )
                  h_bkgdEst_tagMassSDTau32_dRapLo_2btag              .Fill( DijetMass             , evWeight*rate[1] )#* sf0_MassTau32bTag * sf1_MassTau32bTag )
                  h_bkgdEst_modMass_tagMassSDTau32_dRapLo_2btag      .Fill( DijetMass_modMass_jet0, evWeight*rate[1] )#* sf0_MassTau32bTag * sf1_MassTau32bTag )
              if (newbtagjet0 and not newbtagjet1):
                  #1btag
                  mttPredDist_tagMassSDTau32_dRapLo_DijetMass_1btag            .Accumulate(              DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_DijetMass_1btag    , False )
                  mttPredDist_tagMassSDTau32_dRapLo_JetMass_1btag              .Accumulate(             jet0P4.M(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetMass_1btag      , False )
                  mttPredDist_tagMassSDTau32_dRapLo_JetPt_1btag                .Accumulate(           jet0P4.Perp(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetPt_1btag        , False )
                  mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_1btag               .Accumulate(       jet0P4.Rapidity(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_1btag       , False )
                  mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_1btag         .Accumulate(        Jet0MassSoftDrop, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_1btag , False )
                  mttPredDist_tagMassSDTau32_dRapLo_Tau32_1btag                .Accumulate(               Jet0Tau32, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_Tau32_1btag        , False )
                  mttPredDist_tagMassSDTau32_dRapLo_bDisc_1btag                .Accumulate(           maxBdisc_jet0_, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_bDisc_1btag        , False )

                  mttPredDist_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_modMass_tagMassSDTau32_dRapLo_1btag   , False )
                  h_bkgdEst_tagMassSDTau32_dRapLo_1btag              .Fill( DijetMass             , evWeight*rate[2] )#* sf1_MassTau32 * sf0_MassTau32bTag)
                  h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag      .Fill( DijetMass_modMass_jet0, evWeight*rate[2] )#* sf1_MassTau32 * sf0_MassTau32bTag)
              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist_tagMassSDTau32_dRapLo_DijetMass_1btag            .Accumulate(              DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_DijetMass_1btag    , False )
                  mttPredDist_tagMassSDTau32_dRapLo_JetMass_1btag              .Accumulate(             jet0P4.M(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetMass_1btag      , False )
                  mttPredDist_tagMassSDTau32_dRapLo_JetPt_1btag                .Accumulate(           jet0P4.Perp(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetPt_1btag        , False )
                  mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_1btag               .Accumulate(       jet0P4.Rapidity(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_1btag       , False )
                  mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_1btag         .Accumulate(        Jet0MassSoftDrop, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_1btag , False )
                  mttPredDist_tagMassSDTau32_dRapLo_Tau32_1btag                .Accumulate(               Jet0Tau32, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_Tau32_1btag        , False )
                  mttPredDist_tagMassSDTau32_dRapLo_bDisc_1btag                .Accumulate(          maxBdisc_jet0_, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_bDisc_1btag        , False )

                  mttPredDist_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32_dRapLo_1btag    , False )
                  h_bkgdEst_tagMassSDTau32_dRapLo_1btag              .Fill( DijetMass             , evWeight*rate[2] )#* sf0_MassTau32 * sf1_MassTau32bTag )
                  h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag      .Fill( DijetMass_modMass_jet0, evWeight*rate[2] )#* sf0_MassTau32 * sf1_MassTau32bTag )
              if not newbtagjet0 and not newbtagjet1:
                  #0btag
                  mttPredDist_tagMassSDTau32_dRapLo_DijetMass_0btag            .Accumulate(              DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_DijetMass_0btag    , False )
                  mttPredDist_tagMassSDTau32_dRapLo_JetMass_0btag              .Accumulate(             jet0P4.M(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetMass_0btag      , False )
                  mttPredDist_tagMassSDTau32_dRapLo_JetPt_0btag                .Accumulate(           jet0P4.Perp(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetPt_0btag        , False )
                  mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_0btag               .Accumulate(       jet0P4.Rapidity(), jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_0btag       , False )
                  mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_0btag         .Accumulate(        Jet0MassSoftDrop, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_0btag , False )
                  mttPredDist_tagMassSDTau32_dRapLo_Tau32_0btag                .Accumulate(               Jet0Tau32, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_Tau32_0btag        , False )
                  mttPredDist_tagMassSDTau32_dRapLo_bDisc_0btag                .Accumulate(          maxBdisc_jet0_, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist_tagMassSDTau32_dRapLo_bDisc_0btag        , False )

                  mttPredDist_modMass_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_modMass_tagMassSDTau32_dRapLo_0btag    , False )
                  h_bkgdEst_tagMassSDTau32_dRapLo_0btag              .Fill( DijetMass             , evWeight*rate[3] )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  h_bkgdEst_modMass_tagMassSDTau32_dRapLo_0btag      .Fill( DijetMass_modMass_jet0, evWeight*rate[3] )#* sf1_MassTau32 * sf1_MassTau32bTag )
  
      # Mistag as a function of P
      if topTag1MassSDTau32 :
          # mttPredDist2_tagMassSDTau32        .Accumulate(              ttMass, jet0P4.P(), topTag0MassSDTau32, evWeight )
          # mttPredDist2_modMass_tagMassSDTau32.Accumulate( ttMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )
          for i in xrange(len(post)):
              bin.append (h_mistag_vs_jetPt_TagMassSDTau32[i].GetXaxis().FindBin( event.Jet0Pt ))
              rate.append( h_mistag_vs_jetPt_TagMassSDTau32[i].GetBinContent(bin[i]))


              #inclusive
              mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_inclusive            .Accumulate(              DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_inclusive    , False )
              mttPredDist2_tagMassSDTau32_dRapIn_JetMass_inclusive              .Accumulate(             jet0P4.M(), jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetMass_inclusive      , False )
              mttPredDist2_tagMassSDTau32_dRapIn_JetPt_inclusive                .Accumulate(           jet0P4.P(), jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetPt_inclusive        , False )
              mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_inclusive               .Accumulate(       jet0P4.Rapidity(), jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_inclusive       , False )
              mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_inclusive         .Accumulate(        Jet0MassSoftDrop, jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_inclusive , False )
              mttPredDist2_tagMassSDTau32_dRapIn_Tau32_inclusive                .Accumulate(               Jet0Tau32, jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_Tau32_inclusive        , False )
              mttPredDist2_tagMassSDTau32_dRapIn_bDisc_inclusive                .Accumulate(          maxBdisc_jet0_, jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_bDisc_inclusive        , False )

              mttPredDist2_modMass_tagMassSDTau32_dRapIn_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_modMass_tagMassSDTau32_dRapIn_inclusive    , False )

              if newbtagjet0 and newbtagjet1:
                  #2btag
                  mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_2btag            .Accumulate(              DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf0_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_2btag   , False )
                  mttPredDist2_tagMassSDTau32_dRapIn_JetMass_2btag              .Accumulate(             jet0P4.M(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetMass_2btag      , False )
                  mttPredDist2_tagMassSDTau32_dRapIn_JetPt_2btag                .Accumulate(           jet0P4.P(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetPt_2btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_2btag               .Accumulate(       jet0P4.Rapidity(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_2btag       , False )
                  mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_2btag         .Accumulate(        Jet0MassSoftDrop, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_2btag , False )
                  mttPredDist2_tagMassSDTau32_dRapIn_Tau32_2btag                .Accumulate(               Jet0Tau32, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_Tau32_2btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapIn_bDisc_2btag                .Accumulate(          maxBdisc_jet0_, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_bDisc_2btag        , False )

                  mttPredDist2_modMass_tagMassSDTau32_dRapIn_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_modMass_tagMassSDTau32_dRapIn_2btag    , False )

              if (newbtagjet0 and not newbtagjet1):
                  #1btag
                  mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_1btag            .Accumulate(              DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_1btag    , False )
                  mttPredDist2_tagMassSDTau32_dRapIn_JetMass_1btag              .Accumulate(             jet0P4.M(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetMass_1btag      , False )
                  mttPredDist2_tagMassSDTau32_dRapIn_JetPt_1btag                .Accumulate(           jet0P4.P(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetPt_1btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_1btag               .Accumulate(       jet0P4.Rapidity(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_1btag       , False )
                  mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_1btag         .Accumulate(        Jet0MassSoftDrop, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_1btag , False )
                  mttPredDist2_tagMassSDTau32_dRapIn_Tau32_1btag                .Accumulate(               Jet0Tau32, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_Tau32_1btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapIn_bDisc_1btag                .Accumulate(          maxBdisc_jet0_, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_bDisc_1btag        , False )

                  mttPredDist2_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_modMass_tagMassSDTau32_dRapIn_1btag    , False )

              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_1btag            .Accumulate(              DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_1btag    , False )
                  mttPredDist2_tagMassSDTau32_dRapIn_JetMass_1btag              .Accumulate(             jet0P4.M(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetMass_1btag      , False )
                  mttPredDist2_tagMassSDTau32_dRapIn_JetPt_1btag                .Accumulate(           jet0P4.P(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetPt_1btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_1btag               .Accumulate(       jet0P4.Rapidity(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_1btag       , False )
                  mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_1btag         .Accumulate(        Jet0MassSoftDrop, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_1btag , False )
                  mttPredDist2_tagMassSDTau32_dRapIn_Tau32_1btag                .Accumulate(               Jet0Tau32, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_Tau32_1btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapIn_bDisc_1btag                .Accumulate(          maxBdisc_jet0_, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_bDisc_1btag        , False )

                  mttPredDist2_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_modMass_tagMassSDTau32_dRapIn_1btag    , False )

              if not newbtagjet0 and not newbtagjet1:
                  #0btag
                  mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_0btag            .Accumulate(              DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_0btag    , False )
                  mttPredDist2_tagMassSDTau32_dRapIn_JetMass_0btag              .Accumulate(             jet0P4.M(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetMass_0btag      , False )
                  mttPredDist2_tagMassSDTau32_dRapIn_JetPt_0btag                .Accumulate(           jet0P4.P(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetPt_0btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_0btag               .Accumulate(       jet0P4.Rapidity(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_0btag       , False )
                  mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_0btag         .Accumulate(        Jet0MassSoftDrop, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_0btag , False )
                  mttPredDist2_tagMassSDTau32_dRapIn_Tau32_0btag                .Accumulate(               Jet0Tau32, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_Tau32_0btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapIn_bDisc_0btag                .Accumulate(          maxBdisc_jet0_, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapIn_bDisc_0btag        , False )

                  mttPredDist2_modMass_tagMassSDTau32_dRapIn_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_modMass_tagMassSDTau32_dRapIn_0btag   , False )

          


          if event.DijetDeltaRap > 1 :
              #inclusive
              mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_inclusive            .Accumulate(              DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_inclusive    , False )
              mttPredDist2_tagMassSDTau32_dRapHi_JetMass_inclusive              .Accumulate(             jet0P4.M(), jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetMass_inclusive      , False )
              mttPredDist2_tagMassSDTau32_dRapHi_JetPt_inclusive                .Accumulate(           jet0P4.P(), jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetPt_inclusive        , False )
              mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_inclusive               .Accumulate(       jet0P4.Rapidity(), jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_inclusive       , False )
              mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_inclusive         .Accumulate(        Jet0MassSoftDrop, jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_inclusive , False )
              mttPredDist2_tagMassSDTau32_dRapHi_Tau32_inclusive                .Accumulate(               Jet0Tau32, jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_Tau32_inclusive        , False )
              mttPredDist2_tagMassSDTau32_dRapHi_bDisc_inclusive                .Accumulate(          maxBdisc_jet0_, jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_bDisc_inclusive        , False )

              mttPredDist2_modMass_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_modMass_tagMassSDTau32_dRapHi_inclusive    , False )

              if newbtagjet0 and newbtagjet1:
                  #2btag
                  mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_2btag            .Accumulate(              DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf0_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_2btag   , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_JetMass_2btag              .Accumulate(             jet0P4.M(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetMass_2btag      , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_JetPt_2btag                .Accumulate(           jet0P4.P(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetPt_2btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_2btag               .Accumulate(       jet0P4.Rapidity(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_2btag       , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_2btag         .Accumulate(        Jet0MassSoftDrop, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_2btag , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_Tau32_2btag                .Accumulate(               Jet0Tau32, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_Tau32_2btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_bDisc_2btag                .Accumulate(          maxBdisc_jet0_, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_bDisc_2btag        , False )

                  mttPredDist2_modMass_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_modMass_tagMassSDTau32_dRapHi_2btag    , False )

              if (newbtagjet0 and not newbtagjet1):
                  #1btag
                  mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_1btag            .Accumulate(              DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_1btag    , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_JetMass_1btag              .Accumulate(             jet0P4.M(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetMass_1btag      , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_JetPt_1btag                .Accumulate(           jet0P4.P(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetPt_1btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_1btag               .Accumulate(       jet0P4.Rapidity(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_1btag       , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_1btag         .Accumulate(        Jet0MassSoftDrop, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_1btag , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_Tau32_1btag                .Accumulate(               Jet0Tau32, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_Tau32_1btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_bDisc_1btag                .Accumulate(          maxBdisc_jet0_, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_bDisc_1btag        , False )

                  mttPredDist2_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_modMass_tagMassSDTau32_dRapHi_1btag    , False )

              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_1btag            .Accumulate(              DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_1btag    , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_JetMass_1btag              .Accumulate(             jet0P4.M(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetMass_1btag      , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_JetPt_1btag                .Accumulate(           jet0P4.P(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetPt_1btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_1btag               .Accumulate(       jet0P4.Rapidity(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_1btag       , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_1btag         .Accumulate(        Jet0MassSoftDrop, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_1btag , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_Tau32_1btag                .Accumulate(               Jet0Tau32, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_Tau32_1btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_bDisc_1btag                .Accumulate(          maxBdisc_jet0_, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_bDisc_1btag        , False )

                  mttPredDist2_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_modMass_tagMassSDTau32_dRapHi_1btag    , False )

              if not newbtagjet0 and not newbtagjet1:
                  #0btag
                  mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_0btag            .Accumulate(              DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_0btag    , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_JetMass_0btag              .Accumulate(             jet0P4.M(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetMass_0btag      , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_JetPt_0btag                .Accumulate(           jet0P4.P(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetPt_0btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_0btag               .Accumulate(       jet0P4.Rapidity(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_0btag       , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_0btag         .Accumulate(        Jet0MassSoftDrop, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_0btag , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_Tau32_0btag                .Accumulate(               Jet0Tau32, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_Tau32_0btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapHi_bDisc_0btag                .Accumulate(          maxBdisc_jet0_, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapHi_bDisc_0btag        , False )

                  mttPredDist2_modMass_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_modMass_tagMassSDTau32_dRapHi_0btag   , False )

          if event.DijetDeltaRap < 1:
              #inclusive
              mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_inclusive            .Accumulate(              DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_inclusive    , False )
              mttPredDist2_tagMassSDTau32_dRapLo_JetMass_inclusive              .Accumulate(             jet0P4.M(), jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetMass_inclusive      , False )
              mttPredDist2_tagMassSDTau32_dRapLo_JetPt_inclusive                .Accumulate(           jet0P4.P(), jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetPt_inclusive        , False )
              mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_inclusive               .Accumulate(       jet0P4.Rapidity(), jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_inclusive       , False )
              mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_inclusive         .Accumulate(        Jet0MassSoftDrop, jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_inclusive , False )
              mttPredDist2_tagMassSDTau32_dRapLo_Tau32_inclusive                .Accumulate(               Jet0Tau32, jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_Tau32_inclusive        , False )
              mttPredDist2_tagMassSDTau32_dRapLo_bDisc_inclusive                .Accumulate(          maxBdisc_jet0_, jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_bDisc_inclusive        , False )

              mttPredDist2_modMass_tagMassSDTau32_dRapLo_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_modMass_tagMassSDTau32_dRapLo_inclusive    , False )

              if newbtagjet0 and newbtagjet1:
                  #2btag
                  mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_2btag            .Accumulate(              DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf0_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_2btag   , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_JetMass_2btag              .Accumulate(             jet0P4.M(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetMass_2btag      , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_JetPt_2btag                .Accumulate(           jet0P4.P(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetPt_2btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_2btag               .Accumulate(       jet0P4.Rapidity(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_2btag       , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_2btag         .Accumulate(        Jet0MassSoftDrop, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_2btag , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_Tau32_2btag                .Accumulate(               Jet0Tau32, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_Tau32_2btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_bDisc_2btag                .Accumulate(          maxBdisc_jet0_, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_bDisc_2btag        , False )

                  mttPredDist2_modMass_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_modMass_tagMassSDTau32_dRapLo_2btag    , False )

              if (newbtagjet0 and not newbtagjet1):
                  #1btag
                  mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_1btag            .Accumulate(              DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_1btag    , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_JetMass_1btag              .Accumulate(             jet0P4.M(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetMass_1btag      , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_JetPt_1btag                .Accumulate(           jet0P4.P(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetPt_1btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_1btag               .Accumulate(       jet0P4.Rapidity(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_1btag       , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_1btag         .Accumulate(        Jet0MassSoftDrop, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_1btag , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_Tau32_1btag                .Accumulate(               Jet0Tau32, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_Tau32_1btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_bDisc_1btag                .Accumulate(           maxBdisc_jet0_, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_bDisc_1btag        , False )

                  mttPredDist2_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist2_modMass_tagMassSDTau32_dRapLo_1btag   , False )

              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_1btag            .Accumulate(              DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_1btag    , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_JetMass_1btag              .Accumulate(             jet0P4.M(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetMass_1btag      , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_JetPt_1btag                .Accumulate(           jet0P4.P(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetPt_1btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_1btag               .Accumulate(       jet0P4.Rapidity(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_1btag       , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_1btag         .Accumulate(        Jet0MassSoftDrop, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_1btag , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_Tau32_1btag                .Accumulate(               Jet0Tau32, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_Tau32_1btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_bDisc_1btag                .Accumulate(          maxBdisc_jet0_, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_bDisc_1btag        , False )

                  mttPredDist2_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_modMass_tagMassSDTau32_dRapLo_1btag    , False )

              if not newbtagjet0 and not newbtagjet1:
                  #0btag
                  mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_0btag            .Accumulate(              DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_0btag    , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_JetMass_0btag              .Accumulate(             jet0P4.M(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetMass_0btag      , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_JetPt_0btag                .Accumulate(           jet0P4.P(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetPt_0btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_0btag               .Accumulate(       jet0P4.Rapidity(), jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_0btag       , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_0btag         .Accumulate(        Jet0MassSoftDrop, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_0btag , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_Tau32_0btag                .Accumulate(               Jet0Tau32, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_Tau32_0btag        , False )
                  mttPredDist2_tagMassSDTau32_dRapLo_bDisc_0btag                .Accumulate(          maxBdisc_jet0_, jet0P4.P(), topTag0MassSDTau32, evWeight )
                  ROOT.SetOwnership( mttPredDist2_tagMassSDTau32_dRapLo_bDisc_0btag        , False )

                  mttPredDist2_modMass_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_modMass_tagMassSDTau32_dRapLo_0btag    , False )


      if topTag1MassSDTau32 and oddEvent :
          mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_inclusive    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
          ROOT.SetOwnership(  mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_inclusive   , False )
          mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_inclusive    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )
          ROOT.SetOwnership(  mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_inclusive   , False )

          mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
          ROOT.SetOwnership(  mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_inclusive   , False )
          mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )
          ROOT.SetOwnership(  mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_inclusive   , False )
          
          if newbtagjet0 and newbtagjet1:
              #2btag
              mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_2btag    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_2btag    , False )
              mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_2btag    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_2btag    , False )

              mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_2btag    , False )
              mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_2btag    , False )

          if (newbtagjet0 and not newbtagjet1):
              #1btag
              mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag    , False )
              mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag    , False )
              
              mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag    , False )
              mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag    , False )
                 

          if (newbtagjet1 and not newbtagjet0):
              mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag    , False )
              mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag    , False )

              mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag    , False )
              mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag    , False )

              

          if not newbtagjet0 and not newbtagjet1:
              mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_0btag    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_0btag    , False )
              mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_0btag    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_0btag    , False )

              mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_0btag    , False )
              mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_0btag    , False )


          if event.DijetDeltaRap > 1 :    
              mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_inclusive    , False )
              mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_inclusive    , False )
              
              mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_inclusive    , False )
              mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_inclusive    , False )
              

              if newbtagjet0 and newbtagjet1:
                  mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass , jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_2btag   , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass , jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_2btag   , False )
              
                  mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_2btag   , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_2btag   , False )
              

              if (newbtagjet0 and not newbtagjet1):
                  mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag    , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag    , False )
              
                  mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag    , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag    , False )
              
              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag   , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag   , False )

                  mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag   , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag   , False )

                  
              if not newbtagjet0 and not newbtagjet1:
                  mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_0btag    , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_0btag    , False )
          
                  mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_0btag    , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_0btag    , False )
          
          if event.DijetDeltaRap < 1:
              #inclusive
            

              mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership(  mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_inclusive   , False )
              mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership(  mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_inclusive   , False )
              
              if newbtagjet0 and newbtagjet1:
                  mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_2btag    , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_2btag    , False )


                  mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_2btag    , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_2btag    , False )

                  
              if (newbtagjet0 and not newbtagjet1):
                  mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag    , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag    , False )
              
                  mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag    , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag    , False )
              

              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag    , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag    , False )

                  mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag    , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag    , False )
                  

              if not newbtagjet0 and not newbtagjet1:
                  mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_0btag    , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_0btag    , False )
                 
                  mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_0btag    , False )
                  mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_0btag    , False )
                 
      if topTag1MassSDTau32 and evenEvent :
          mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_inclusive    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
          ROOT.SetOwnership(  mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_inclusive   , False )
          mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_inclusive    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )
          ROOT.SetOwnership(  mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_inclusive   , False )

          mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
          ROOT.SetOwnership(  mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_inclusive   , False )
          mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )
          ROOT.SetOwnership(  mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_inclusive   , False )
          
          if newbtagjet0 and newbtagjet1:
              #2btag
              mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_2btag    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_2btag    , False )
              mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_2btag    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_2btag    , False )

              mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_2btag    , False )
              mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_2btag    , False )

          if (newbtagjet0 and not newbtagjet1):
              #1btag
              mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag    , False )
              mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag    , False )
              
              mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag    , False )
              mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag    , False )
                 

          if (newbtagjet1 and not newbtagjet0):
              mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag    , False )
              mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag    , False )

              mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag    , False )
              mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag    , False )

              

          if not newbtagjet0 and not newbtagjet1:

              mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_0btag    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_0btag    , False )
              mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_0btag    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_0btag    , False )

              mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_0btag    , False )
              mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_0btag    , False )


          if event.DijetDeltaRap > 1 :
              
              mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_inclusive    , False )
              mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_inclusive    , False )
              
              mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_inclusive    , False )
              mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_inclusive    , False )
              

              if newbtagjet0 and newbtagjet1:
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass , jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_2btag   , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass , jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_2btag   , False )
              
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_2btag   , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_2btag   , False )
              

              if (newbtagjet0 and not newbtagjet1):
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag    , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag    , False )
              
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag    , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag    , False )
              
              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag   , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag   , False )

                  mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag   , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag   , False )

                  
              if not newbtagjet0 and not newbtagjet1:
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_0btag    , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_0btag    , False )
          
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_0btag    , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_0btag    , False )
          
          if event.DijetDeltaRap < 1:
              #inclusive

              mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership(  mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_inclusive   , False )
              mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )
              ROOT.SetOwnership(  mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_inclusive   , False )
              
              if newbtagjet0 and newbtagjet1:
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_2btag    , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_2btag    , False )


                  mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_2btag    , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_2btag    , False )

                  

              if (newbtagjet0 and not newbtagjet1):
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag    , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag    , False )
              
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag    , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag    , False )
              

              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag    , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag    , False )

                  mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag    , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag    , False )

                  

              if not newbtagjet0 and not newbtagjet1:
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_0btag    , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_0btag    , False )
                 
                  mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_0btag    , False )
                  mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.P(), topTag0MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_0btag    , False )
                 


  
      if topTag1MassSDTau32  :
          mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership(  mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_inclusive   , False )
          if newbtagjet0 and newbtagjet1:
              #2btag
              mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_2btag    , False )
          if (newbtagjet0 and not newbtagjet1):
              #1btag
              mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_1btag    , False )
          if (newbtagjet1 and not newbtagjet0):
              mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_1btag    , False )
          if not newbtagjet0 and not newbtagjet1:
              mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_0btag    , False )

          if event.DijetDeltaRap > 1 :
              mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_inclusive    , False )
              if newbtagjet0 and newbtagjet1:
                  mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_2btag   , False )
              if (newbtagjet0 and not newbtagjet1):
                  mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_1btag    , False )
              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_1btag   , False )
              if not newbtagjet0 and not newbtagjet1:
                  mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_0btag    , False )
          
          if event.DijetDeltaRap < 1:
              #inclusive
              mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership(  mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_inclusive   , False )
              if newbtagjet0 and newbtagjet1:
                  mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_2btag    , False )
              if (newbtagjet0 and not newbtagjet1):
                  mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_1btag    , False )
              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_1btag    , False )
              if not newbtagjet0 and not newbtagjet1:
                  mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_0btag    , False )
      if topTag1MassSDTau32  :
          mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership(  mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_inclusive   , False )
          if newbtagjet0 and newbtagjet1:
              #2btag
              mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_2btag    , False )
          if (newbtagjet0 and not newbtagjet1):
              #1btag
              mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_1btag    , False )
          if (newbtagjet1 and not newbtagjet0):
              mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_1btag    , False )
          if not newbtagjet0 and not newbtagjet1:
              mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_0btag    , False )

          if event.DijetDeltaRap > 1 :
              mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_inclusive    , False )
              if newbtagjet0 and newbtagjet1:
                  mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_2btag   , False )
              if (newbtagjet0 and not newbtagjet1):
                  mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_1btag    , False )
              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_1btag   , False )
              if not newbtagjet0 and not newbtagjet1:
                  mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_0btag    , False )
          
          if event.DijetDeltaRap < 1:
              #inclusive
              mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership(  mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_inclusive   , False )
              if newbtagjet0 and newbtagjet1:
                  mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_2btag    , False )
              if (newbtagjet0 and not newbtagjet1):
                  mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_1btag    , False )
              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_1btag    , False )
              if not newbtagjet0 and not newbtagjet1:
                  mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_0btag    , False )
      if topTag1MassSDTau32  :
          mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )
          ROOT.SetOwnership(  mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_inclusive   , False )
          if newbtagjet0 and newbtagjet1:
              #2btag
              mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_2btag    , False )
          if (newbtagjet0 and not newbtagjet1):
              #1btag
              mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_1btag    , False )
          if (newbtagjet1 and not newbtagjet0):
              mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_1btag    , False )
          if not newbtagjet0 and not newbtagjet1:
              mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
              ROOT.SetOwnership( mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_0btag    , False )

          if event.DijetDeltaRap > 1 :
              mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership( mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_inclusive    , False )
              if newbtagjet0 and newbtagjet1:
                  mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_2btag   , False )
              if (newbtagjet0 and not newbtagjet1):
                  mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )# * sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_1btag    , False )
              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership(  mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_1btag   , False )
              if not newbtagjet0 and not newbtagjet1:
                  mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_0btag    , False )
          
          if event.DijetDeltaRap < 1:
              #inclusive
              mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_inclusive    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )
              ROOT.SetOwnership(  mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_inclusive   , False )
              if newbtagjet0 and newbtagjet1:
                  mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_2btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )# * sf0_MassTau32bTag * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_2btag    , False )
              if (newbtagjet0 and not newbtagjet1):
                  mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf0_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_1btag    , False )
              if (newbtagjet1 and not newbtagjet0):
                  mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_1btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight)# * sf0_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_1btag    , False )
              if not newbtagjet0 and not newbtagjet1:
                  mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_0btag    .Accumulate( DijetMass_modMass_jet0, jet0P4.Perp(), topTag1MassSDTau32, evWeight )#* sf1_MassTau32 * sf1_MassTau32bTag )
                  ROOT.SetOwnership( mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_0btag    , False )

  



OUT.cd()

h_mttMass_tagMassSDTau32_dRapHi_inclusive        .Write()
h_mttMass_tagMassSDTau32_dRapHi_2btag            .Write()
h_mttMass_tagMassSDTau32_dRapHi_1btag            .Write()
h_mttMass_tagMassSDTau32_dRapHi_0btag            .Write()
h_mttMass_tagMassSDTau32_dRapLo_inclusive        .Write()
h_mttMass_tagMassSDTau32_dRapLo_2btag            .Write()
h_mttMass_tagMassSDTau32_dRapLo_1btag            .Write()
h_mttMass_tagMassSDTau32_dRapLo_0btag            .Write()
# h_bkgdEst_tagMassSDTau32_dRapHi_inclusive        .Write()
# h_bkgdEst_tagMassSDTau32_dRapHi_2btag            .Write()
# h_bkgdEst_tagMassSDTau32_dRapHi_1btag            .Write()
# h_bkgdEst_tagMassSDTau32_dRapHi_0btag            .Write()
# h_bkgdEst_tagMassSDTau32_dRapLo_inclusive        .Write()
# h_bkgdEst_tagMassSDTau32_dRapLo_2btag            .Write()
# h_bkgdEst_tagMassSDTau32_dRapLo_1btag            .Write()
# h_bkgdEst_tagMassSDTau32_dRapLo_0btag            .Write()
# h_bkgdEst_modMass_tagMassSDTau32_dRapHi_inclusive.Write()
# h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag    .Write()
# h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag    .Write()
# h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag    .Write()
# h_bkgdEst_modMass_tagMassSDTau32_dRapLo_inclusive.Write()
# h_bkgdEst_modMass_tagMassSDTau32_dRapLo_2btag    .Write() 
# h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag    .Write()
# h_bkgdEst_modMass_tagMassSDTau32_dRapLo_0btag    .Write()

# mttPredDist_modMass_tagMassSDTau32_dRapHi_inclusive .GetPredictedHist() .Write()
# mttPredDist_modMass_tagMassSDTau32_dRapHi_inclusive .GetObservedHist()  .Write()
# mttPredDist_modMass_tagMassSDTau32_dRapHi_inclusive .GetTaggableHist()  .Write()  
# mttPredDist_modMass_tagMassSDTau32_dRapHi_0btag     .GetPredictedHist() .Write()
# mttPredDist_modMass_tagMassSDTau32_dRapHi_0btag     .GetObservedHist()  .Write()
# mttPredDist_modMass_tagMassSDTau32_dRapHi_0btag     .GetTaggableHist()  .Write() 
# mttPredDist_modMass_tagMassSDTau32_dRapHi_1btag     .GetPredictedHist() .Write()      
# mttPredDist_modMass_tagMassSDTau32_dRapHi_1btag     .GetObservedHist()  .Write()
# mttPredDist_modMass_tagMassSDTau32_dRapHi_1btag     .GetTaggableHist()  .Write()
# mttPredDist_modMass_tagMassSDTau32_dRapHi_2btag     .GetPredictedHist() .Write()
# mttPredDist_modMass_tagMassSDTau32_dRapHi_2btag     .GetObservedHist()  .Write()
# mttPredDist_modMass_tagMassSDTau32_dRapHi_2btag     .GetTaggableHist()  .Write()  
# mttPredDist_modMass_tagMassSDTau32_dRapLo_inclusive .GetPredictedHist() .Write()
# mttPredDist_modMass_tagMassSDTau32_dRapLo_inclusive .GetObservedHist()  .Write() 
# mttPredDist_modMass_tagMassSDTau32_dRapLo_inclusive .GetTaggableHist()  .Write() 
# mttPredDist_modMass_tagMassSDTau32_dRapLo_0btag     .GetPredictedHist() .Write()
# mttPredDist_modMass_tagMassSDTau32_dRapLo_0btag     .GetObservedHist()  .Write()
# mttPredDist_modMass_tagMassSDTau32_dRapLo_0btag     .GetTaggableHist()  .Write() 
# mttPredDist_modMass_tagMassSDTau32_dRapLo_1btag     .GetPredictedHist() .Write()     
# mttPredDist_modMass_tagMassSDTau32_dRapLo_1btag     .GetObservedHist()  .Write()
# mttPredDist_modMass_tagMassSDTau32_dRapLo_1btag     .GetTaggableHist()  .Write()
# mttPredDist_modMass_tagMassSDTau32_dRapLo_2btag     .GetPredictedHist() .Write()
# mttPredDist_modMass_tagMassSDTau32_dRapLo_2btag     .GetObservedHist()  .Write()
# mttPredDist_modMass_tagMassSDTau32_dRapLo_2btag     .GetTaggableHist()  .Write()      

# mttPredDist_tagMassSDTau32_dRapHi_DijetMass_inclusive .GetPredictedHist()   .Write()
# mttPredDist_tagMassSDTau32_dRapHi_DijetMass_inclusive .GetObservedHist()    .Write()
# mttPredDist_tagMassSDTau32_dRapHi_DijetMass_inclusive .GetTaggableHist()    .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetMass_inclusive .GetPredictedHist()     .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetMass_inclusive .GetObservedHist()      .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetMass_inclusive .GetTaggableHist()      .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetPt_inclusive .GetPredictedHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetPt_inclusive .GetObservedHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetPt_inclusive .GetTaggableHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_inclusive .GetPredictedHist()      .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_inclusive .GetObservedHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_inclusive .GetTaggableHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_inclusive .GetPredictedHist().Write()
# mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_inclusive .GetObservedHist() .Write()
# mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_inclusive .GetTaggableHist() .Write()
# mttPredDist_tagMassSDTau32_dRapHi_Tau32_inclusive .GetPredictedHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapHi_Tau32_inclusive .GetObservedHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapHi_Tau32_inclusive .GetTaggableHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapHi_bDisc_inclusive .GetPredictedHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapHi_bDisc_inclusive .GetObservedHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapHi_bDisc_inclusive .GetTaggableHist()        .Write()

# mttPredDist_tagMassSDTau32_dRapHi_DijetMass_0btag     .GetPredictedHist()   .Write()
# mttPredDist_tagMassSDTau32_dRapHi_DijetMass_0btag     .GetObservedHist()    .Write()
# mttPredDist_tagMassSDTau32_dRapHi_DijetMass_0btag     .GetTaggableHist()    .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetMass_0btag     .GetPredictedHist()     .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetMass_0btag     .GetObservedHist()      .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetMass_0btag     .GetTaggableHist()      .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetPt_0btag     .GetPredictedHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetPt_0btag     .GetObservedHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetPt_0btag     .GetTaggableHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_0btag     .GetPredictedHist()      .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_0btag     .GetObservedHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_0btag     .GetTaggableHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_0btag     .GetPredictedHist().Write()
# mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_0btag     .GetObservedHist() .Write()
# mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_0btag     .GetTaggableHist() .Write()
# mttPredDist_tagMassSDTau32_dRapHi_Tau32_0btag     .GetPredictedHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapHi_Tau32_0btag     .GetObservedHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapHi_Tau32_0btag     .GetTaggableHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapHi_bDisc_0btag     .GetPredictedHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapHi_bDisc_0btag     .GetObservedHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapHi_bDisc_0btag     .GetTaggableHist()        .Write()

# mttPredDist_tagMassSDTau32_dRapHi_DijetMass_1btag     .GetPredictedHist()   .Write()
# mttPredDist_tagMassSDTau32_dRapHi_DijetMass_1btag     .GetObservedHist()    .Write()
# mttPredDist_tagMassSDTau32_dRapHi_DijetMass_1btag     .GetTaggableHist()    .Write() 
# mttPredDist_tagMassSDTau32_dRapHi_JetMass_1btag     .GetPredictedHist()     .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetMass_1btag     .GetObservedHist()      .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetMass_1btag     .GetTaggableHist()      .Write() 
# mttPredDist_tagMassSDTau32_dRapHi_JetPt_1btag     .GetPredictedHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetPt_1btag     .GetObservedHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetPt_1btag     .GetTaggableHist()        .Write() 
# mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_1btag     .GetPredictedHist()      .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_1btag     .GetObservedHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_1btag     .GetTaggableHist()       .Write() 
# mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_1btag     .GetPredictedHist().Write()
# mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_1btag     .GetObservedHist() .Write()
# mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_1btag     .GetTaggableHist() .Write() 
# mttPredDist_tagMassSDTau32_dRapHi_Tau32_1btag     .GetPredictedHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapHi_Tau32_1btag     .GetObservedHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapHi_Tau32_1btag     .GetTaggableHist()        .Write() 
# mttPredDist_tagMassSDTau32_dRapHi_bDisc_1btag     .GetPredictedHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapHi_bDisc_1btag     .GetObservedHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapHi_bDisc_1btag     .GetTaggableHist()        .Write() 

# mttPredDist_tagMassSDTau32_dRapHi_DijetMass_2btag     .GetPredictedHist()   .Write() 
# mttPredDist_tagMassSDTau32_dRapHi_DijetMass_2btag     .GetObservedHist()    .Write()   
# mttPredDist_tagMassSDTau32_dRapHi_DijetMass_2btag     .GetTaggableHist()    .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetMass_2btag     .GetPredictedHist()     .Write() 
# mttPredDist_tagMassSDTau32_dRapHi_JetMass_2btag     .GetObservedHist()      .Write()   
# mttPredDist_tagMassSDTau32_dRapHi_JetMass_2btag     .GetTaggableHist()      .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetPt_2btag     .GetPredictedHist()       .Write() 
# mttPredDist_tagMassSDTau32_dRapHi_JetPt_2btag     .GetObservedHist()        .Write()   
# mttPredDist_tagMassSDTau32_dRapHi_JetPt_2btag     .GetTaggableHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_2btag     .GetPredictedHist()      .Write() 
# mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_2btag     .GetObservedHist()       .Write()   
# mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_2btag     .GetTaggableHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_2btag     .GetPredictedHist().Write() 
# mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_2btag     .GetObservedHist() .Write()   
# mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_2btag     .GetTaggableHist() .Write()
# mttPredDist_tagMassSDTau32_dRapHi_Tau32_2btag     .GetPredictedHist()       .Write() 
# mttPredDist_tagMassSDTau32_dRapHi_Tau32_2btag     .GetObservedHist()        .Write()   
# mttPredDist_tagMassSDTau32_dRapHi_Tau32_2btag     .GetTaggableHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapHi_bDisc_2btag     .GetPredictedHist()       .Write() 
# mttPredDist_tagMassSDTau32_dRapHi_bDisc_2btag     .GetObservedHist()        .Write()   
# mttPredDist_tagMassSDTau32_dRapHi_bDisc_2btag     .GetTaggableHist()        .Write()

# mttPredDist_tagMassSDTau32_dRapLo_DijetMass_inclusive .GetPredictedHist()   .Write()
# mttPredDist_tagMassSDTau32_dRapLo_DijetMass_inclusive .GetObservedHist()    .Write()
# mttPredDist_tagMassSDTau32_dRapLo_DijetMass_inclusive .GetTaggableHist()    .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetMass_inclusive .GetPredictedHist()     .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetMass_inclusive .GetObservedHist()      .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetMass_inclusive .GetTaggableHist()      .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetPt_inclusive .GetPredictedHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetPt_inclusive .GetObservedHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetPt_inclusive .GetTaggableHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_inclusive .GetPredictedHist()      .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_inclusive .GetObservedHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_inclusive .GetTaggableHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_inclusive .GetPredictedHist().Write()
# mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_inclusive .GetObservedHist() .Write()
# mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_inclusive .GetTaggableHist() .Write()
# mttPredDist_tagMassSDTau32_dRapLo_Tau32_inclusive .GetPredictedHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapLo_Tau32_inclusive .GetObservedHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapLo_Tau32_inclusive .GetTaggableHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapLo_bDisc_inclusive .GetPredictedHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapLo_bDisc_inclusive .GetObservedHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapLo_bDisc_inclusive .GetTaggableHist()        .Write()

# mttPredDist_tagMassSDTau32_dRapLo_DijetMass_0btag     .GetPredictedHist()   .Write()
# mttPredDist_tagMassSDTau32_dRapLo_DijetMass_0btag     .GetObservedHist()    .Write()
# mttPredDist_tagMassSDTau32_dRapLo_DijetMass_0btag     .GetTaggableHist()    .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetMass_0btag     .GetPredictedHist()     .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetMass_0btag     .GetObservedHist()      .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetMass_0btag     .GetTaggableHist()      .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetPt_0btag     .GetPredictedHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetPt_0btag     .GetObservedHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetPt_0btag     .GetTaggableHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_0btag     .GetPredictedHist()      .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_0btag     .GetObservedHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_0btag     .GetTaggableHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_0btag     .GetPredictedHist().Write()
# mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_0btag     .GetObservedHist() .Write()
# mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_0btag     .GetTaggableHist() .Write()
# mttPredDist_tagMassSDTau32_dRapLo_Tau32_0btag     .GetPredictedHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapLo_Tau32_0btag     .GetObservedHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapLo_Tau32_0btag     .GetTaggableHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapLo_bDisc_0btag     .GetPredictedHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapLo_bDisc_0btag     .GetObservedHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapLo_bDisc_0btag     .GetTaggableHist()        .Write()

# mttPredDist_tagMassSDTau32_dRapLo_DijetMass_1btag     .GetPredictedHist()   .Write()
# mttPredDist_tagMassSDTau32_dRapLo_DijetMass_1btag     .GetObservedHist()    .Write()
# mttPredDist_tagMassSDTau32_dRapLo_DijetMass_1btag     .GetTaggableHist()    .Write() 
# mttPredDist_tagMassSDTau32_dRapLo_JetMass_1btag     .GetPredictedHist()     .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetMass_1btag     .GetObservedHist()      .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetMass_1btag     .GetTaggableHist()      .Write() 
# mttPredDist_tagMassSDTau32_dRapLo_JetPt_1btag     .GetPredictedHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetPt_1btag     .GetObservedHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetPt_1btag     .GetTaggableHist()        .Write() 
# mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_1btag     .GetPredictedHist()      .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_1btag     .GetObservedHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_1btag     .GetTaggableHist()       .Write() 
# mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_1btag     .GetPredictedHist().Write()
# mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_1btag     .GetObservedHist() .Write()
# mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_1btag     .GetTaggableHist() .Write() 
# mttPredDist_tagMassSDTau32_dRapLo_Tau32_1btag     .GetPredictedHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapLo_Tau32_1btag     .GetObservedHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapLo_Tau32_1btag     .GetTaggableHist()        .Write() 
# mttPredDist_tagMassSDTau32_dRapLo_bDisc_1btag     .GetPredictedHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapLo_bDisc_1btag     .GetObservedHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapLo_bDisc_1btag     .GetTaggableHist()        .Write() 

# mttPredDist_tagMassSDTau32_dRapLo_DijetMass_2btag     .GetPredictedHist()   .Write() 
# mttPredDist_tagMassSDTau32_dRapLo_DijetMass_2btag     .GetObservedHist()    .Write()   
# mttPredDist_tagMassSDTau32_dRapLo_DijetMass_2btag     .GetTaggableHist()    .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetMass_2btag     .GetPredictedHist()     .Write() 
# mttPredDist_tagMassSDTau32_dRapLo_JetMass_2btag     .GetObservedHist()      .Write()   
# mttPredDist_tagMassSDTau32_dRapLo_JetMass_2btag     .GetTaggableHist()      .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetPt_2btag     .GetPredictedHist()       .Write() 
# mttPredDist_tagMassSDTau32_dRapLo_JetPt_2btag     .GetObservedHist()        .Write()   
# mttPredDist_tagMassSDTau32_dRapLo_JetPt_2btag     .GetTaggableHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_2btag     .GetPredictedHist()      .Write() 
# mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_2btag     .GetObservedHist()       .Write()   
# mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_2btag     .GetTaggableHist()       .Write()
# mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_2btag     .GetPredictedHist().Write() 
# mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_2btag     .GetObservedHist() .Write()   
# mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_2btag     .GetTaggableHist() .Write()
# mttPredDist_tagMassSDTau32_dRapLo_Tau32_2btag     .GetPredictedHist()       .Write() 
# mttPredDist_tagMassSDTau32_dRapLo_Tau32_2btag     .GetObservedHist()        .Write()   
# mttPredDist_tagMassSDTau32_dRapLo_Tau32_2btag     .GetTaggableHist()        .Write()
# mttPredDist_tagMassSDTau32_dRapLo_bDisc_2btag     .GetPredictedHist()       .Write() 
# mttPredDist_tagMassSDTau32_dRapLo_bDisc_2btag     .GetObservedHist()        .Write()   
# mttPredDist_tagMassSDTau32_dRapLo_bDisc_2btag     .GetTaggableHist()        .Write()

# .GetPredictedHist().Write()
# .GetObservedHist().Write()
# .GetTaggableHist().Write()




mttPredDist_modMass_tagMassSDTau32_dRapHi_0btag                            .GetPredictedHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapHi_1btag                            .GetPredictedHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapHi_2btag                            .GetPredictedHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapHi_inclusive                        .GetPredictedHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapLo_0btag                            .GetPredictedHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapLo_1btag                            .GetPredictedHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapLo_2btag                            .GetPredictedHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapLo_inclusive                        .GetPredictedHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapIn_0btag                            .GetPredictedHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapIn_1btag                            .GetPredictedHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapIn_2btag                            .GetPredictedHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapIn_inclusive                        .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_DijetMass_0btag                          .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetMass_0btag                            .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetPt_0btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_0btag                        .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_0btag                       .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_Tau32_0btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_bDisc_0btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_DijetMass_1btag                          .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetMass_1btag                            .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetPt_1btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_1btag                        .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_1btag                       .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_Tau32_1btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_bDisc_1btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_DijetMass_2btag                          .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetMass_2btag                            .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetPt_2btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_2btag                        .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_2btag                       .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_Tau32_2btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_bDisc_2btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_DijetMass_inclusive                      .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetMass_inclusive                        .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetPt_inclusive                          .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_inclusive                    .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_inclusive                   .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_Tau32_inclusive                          .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_bDisc_inclusive                          .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_DijetMass_0btag                          .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetMass_0btag                            .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetPt_0btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_0btag                        .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_0btag                       .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_Tau32_0btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_bDisc_0btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_DijetMass_1btag                          .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetMass_1btag                            .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetPt_1btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_1btag                        .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_1btag                       .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_Tau32_1btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_bDisc_1btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_DijetMass_2btag                          .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetMass_2btag                            .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetPt_2btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_2btag                        .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_2btag                       .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_Tau32_2btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_bDisc_2btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_DijetMass_inclusive                      .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetMass_inclusive                        .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetPt_inclusive                          .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_inclusive                    .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_inclusive                   .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_Tau32_inclusive                          .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_bDisc_inclusive                          .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_DijetMass_0btag                          .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetMass_0btag                            .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetPt_0btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_0btag                        .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_0btag                       .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_Tau32_0btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_bDisc_0btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_DijetMass_1btag                          .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetMass_1btag                            .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetPt_1btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_1btag                        .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_1btag                       .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_Tau32_1btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_bDisc_1btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_DijetMass_2btag                          .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetMass_2btag                            .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetPt_2btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_2btag                        .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_2btag                       .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_Tau32_2btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_bDisc_2btag                              .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_DijetMass_inclusive                      .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetMass_inclusive                        .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetPt_inclusive                          .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_inclusive                    .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_inclusive                   .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_Tau32_inclusive                          .GetPredictedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_bDisc_inclusive                          .GetPredictedHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapHi_0btag                           .GetPredictedHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapHi_1btag                           .GetPredictedHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapHi_2btag                           .GetPredictedHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapHi_inclusive                       .GetPredictedHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapLo_0btag                           .GetPredictedHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapLo_1btag                           .GetPredictedHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapLo_2btag                           .GetPredictedHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapLo_inclusive                       .GetPredictedHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapIn_0btag                           .GetPredictedHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapIn_1btag                           .GetPredictedHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapIn_2btag                           .GetPredictedHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapIn_inclusive                       .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_0btag                         .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetMass_0btag                           .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetPt_0btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_0btag                       .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_0btag                      .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_Tau32_0btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_bDisc_0btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_1btag                         .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetMass_1btag                           .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetPt_1btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_1btag                       .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_1btag                      .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_Tau32_1btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_bDisc_1btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_2btag                         .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetMass_2btag                           .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetPt_2btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_2btag                       .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_2btag                      .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_Tau32_2btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_bDisc_2btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_inclusive                     .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetMass_inclusive                       .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetPt_inclusive                         .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_inclusive                   .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_inclusive                  .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_Tau32_inclusive                         .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_bDisc_inclusive                         .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_0btag                         .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetMass_0btag                           .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetPt_0btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_0btag                       .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_0btag                      .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_Tau32_0btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_bDisc_0btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_1btag                         .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetMass_1btag                           .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetPt_1btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_1btag                       .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_1btag                      .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_Tau32_1btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_bDisc_1btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_2btag                         .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetMass_2btag                           .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetPt_2btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_2btag                       .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_2btag                      .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_Tau32_2btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_bDisc_2btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_inclusive                     .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetMass_inclusive                       .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetPt_inclusive                         .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_inclusive                   .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_inclusive                  .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_Tau32_inclusive                         .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_bDisc_inclusive                         .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_0btag                         .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetMass_0btag                           .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetPt_0btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_0btag                       .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_0btag                      .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_Tau32_0btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_bDisc_0btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_1btag                         .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetMass_1btag                           .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetPt_1btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_1btag                       .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_1btag                      .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_Tau32_1btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_bDisc_1btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_2btag                         .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetMass_2btag                           .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetPt_2btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_2btag                       .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_2btag                      .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_Tau32_2btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_bDisc_2btag                             .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_inclusive                     .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetMass_inclusive                       .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetPt_inclusive                         .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_inclusive                   .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_inclusive                  .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_Tau32_inclusive                         .GetPredictedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_bDisc_inclusive                         .GetPredictedHist()   .Write()   


mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_0btag         .GetPredictedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag         .GetPredictedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_2btag         .GetPredictedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_inclusive     .GetPredictedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_0btag         .GetPredictedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag         .GetPredictedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_2btag         .GetPredictedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_inclusive     .GetPredictedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_0btag         .GetPredictedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag         .GetPredictedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_2btag         .GetPredictedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_inclusive     .GetPredictedHist()   .Write() 

mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_0btag         .GetPredictedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag         .GetPredictedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_2btag         .GetPredictedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_inclusive     .GetPredictedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_0btag         .GetPredictedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag         .GetPredictedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_2btag         .GetPredictedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_inclusive     .GetPredictedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_0btag         .GetPredictedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag         .GetPredictedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_2btag         .GetPredictedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_inclusive     .GetPredictedHist()   .Write() 



mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_0btag         .GetPredictedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag         .GetPredictedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_2btag         .GetPredictedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_inclusive     .GetPredictedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_0btag         .GetPredictedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag         .GetPredictedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_2btag         .GetPredictedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_inclusive     .GetPredictedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_0btag         .GetPredictedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag         .GetPredictedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_2btag         .GetPredictedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_inclusive     .GetPredictedHist()   .Write()   


mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_0btag         .GetPredictedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag         .GetPredictedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_2btag         .GetPredictedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_inclusive     .GetPredictedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_0btag         .GetPredictedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag         .GetPredictedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_2btag         .GetPredictedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_inclusive     .GetPredictedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_0btag         .GetPredictedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag         .GetPredictedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_2btag         .GetPredictedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_inclusive     .GetPredictedHist()   .Write()   


mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_0btag         .GetPredictedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag         .GetPredictedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_2btag         .GetPredictedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_inclusive     .GetPredictedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_0btag         .GetPredictedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag         .GetPredictedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_2btag         .GetPredictedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_inclusive     .GetPredictedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_0btag         .GetPredictedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag         .GetPredictedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_2btag         .GetPredictedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_inclusive     .GetPredictedHist()   .Write() 

mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_0btag         .GetPredictedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag         .GetPredictedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_2btag         .GetPredictedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_inclusive     .GetPredictedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_0btag         .GetPredictedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag         .GetPredictedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_2btag         .GetPredictedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_inclusive     .GetPredictedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_0btag         .GetPredictedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag         .GetPredictedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_2btag         .GetPredictedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_inclusive     .GetPredictedHist()   .Write() 



mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_0btag         .GetPredictedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag         .GetPredictedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_2btag         .GetPredictedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_inclusive     .GetPredictedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_0btag         .GetPredictedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag         .GetPredictedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_2btag         .GetPredictedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_inclusive     .GetPredictedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_0btag         .GetPredictedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag         .GetPredictedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_2btag         .GetPredictedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_inclusive     .GetPredictedHist()   .Write()   


mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_0btag         .GetPredictedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag         .GetPredictedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_2btag         .GetPredictedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_inclusive     .GetPredictedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_0btag         .GetPredictedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag         .GetPredictedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_2btag         .GetPredictedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_inclusive     .GetPredictedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_0btag         .GetPredictedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag         .GetPredictedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_2btag         .GetPredictedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_inclusive     .GetPredictedHist()   .Write()   



mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_0btag             .GetPredictedHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_1btag             .GetPredictedHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_2btag             .GetPredictedHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_inclusive         .GetPredictedHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_0btag             .GetPredictedHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_1btag             .GetPredictedHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_2btag             .GetPredictedHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_inclusive         .GetPredictedHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_0btag             .GetPredictedHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_1btag             .GetPredictedHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_2btag             .GetPredictedHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_inclusive         .GetPredictedHist()   .Write()      
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_0btag                  .GetPredictedHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_1btag                  .GetPredictedHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_2btag                  .GetPredictedHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_inclusive              .GetPredictedHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_0btag                  .GetPredictedHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_1btag                  .GetPredictedHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_2btag                  .GetPredictedHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_inclusive              .GetPredictedHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_0btag                  .GetPredictedHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_1btag                  .GetPredictedHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_2btag                  .GetPredictedHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_inclusive              .GetPredictedHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_0btag     .GetPredictedHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_1btag     .GetPredictedHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_2btag     .GetPredictedHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_inclusive .GetPredictedHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_0btag     .GetPredictedHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_1btag     .GetPredictedHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_2btag     .GetPredictedHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_inclusive .GetPredictedHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_0btag     .GetPredictedHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_1btag     .GetPredictedHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_2btag     .GetPredictedHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_inclusive .GetPredictedHist()   .Write()   



mttPredDist_modMass_tagMassSDTau32_dRapHi_0btag                            .GetObservedHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapHi_1btag                            .GetObservedHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapHi_2btag                            .GetObservedHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapHi_inclusive                        .GetObservedHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapLo_0btag                            .GetObservedHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapLo_1btag                            .GetObservedHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapLo_2btag                            .GetObservedHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapLo_inclusive                        .GetObservedHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapIn_0btag                            .GetObservedHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapIn_1btag                            .GetObservedHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapIn_2btag                            .GetObservedHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapIn_inclusive                        .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_DijetMass_0btag                          .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetMass_0btag                            .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetPt_0btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_0btag                        .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_0btag                       .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_Tau32_0btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_bDisc_0btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_DijetMass_1btag                          .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetMass_1btag                            .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetPt_1btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_1btag                        .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_1btag                       .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_Tau32_1btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_bDisc_1btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_DijetMass_2btag                          .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetMass_2btag                            .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetPt_2btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_2btag                        .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_2btag                       .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_Tau32_2btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_bDisc_2btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_DijetMass_inclusive                      .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetMass_inclusive                        .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetPt_inclusive                          .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_inclusive                    .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_inclusive                   .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_Tau32_inclusive                          .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_bDisc_inclusive                          .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_DijetMass_0btag                          .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetMass_0btag                            .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetPt_0btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_0btag                        .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_0btag                       .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_Tau32_0btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_bDisc_0btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_DijetMass_1btag                          .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetMass_1btag                            .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetPt_1btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_1btag                        .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_1btag                       .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_Tau32_1btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_bDisc_1btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_DijetMass_2btag                          .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetMass_2btag                            .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetPt_2btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_2btag                        .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_2btag                       .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_Tau32_2btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_bDisc_2btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_DijetMass_inclusive                      .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetMass_inclusive                        .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetPt_inclusive                          .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_inclusive                    .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_inclusive                   .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_Tau32_inclusive                          .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_bDisc_inclusive                          .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_DijetMass_0btag                          .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetMass_0btag                            .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetPt_0btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_0btag                        .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_0btag                       .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_Tau32_0btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_bDisc_0btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_DijetMass_1btag                          .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetMass_1btag                            .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetPt_1btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_1btag                        .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_1btag                       .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_Tau32_1btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_bDisc_1btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_DijetMass_2btag                          .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetMass_2btag                            .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetPt_2btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_2btag                        .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_2btag                       .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_Tau32_2btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_bDisc_2btag                              .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_DijetMass_inclusive                      .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetMass_inclusive                        .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetPt_inclusive                          .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_inclusive                    .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_inclusive                   .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_Tau32_inclusive                          .GetObservedHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_bDisc_inclusive                          .GetObservedHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapHi_0btag                           .GetObservedHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapHi_1btag                           .GetObservedHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapHi_2btag                           .GetObservedHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapHi_inclusive                       .GetObservedHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapLo_0btag                           .GetObservedHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapLo_1btag                           .GetObservedHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapLo_2btag                           .GetObservedHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapLo_inclusive                       .GetObservedHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapIn_0btag                           .GetObservedHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapIn_1btag                           .GetObservedHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapIn_2btag                           .GetObservedHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapIn_inclusive                       .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_0btag                         .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetMass_0btag                           .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetPt_0btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_0btag                       .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_0btag                      .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_Tau32_0btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_bDisc_0btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_1btag                         .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetMass_1btag                           .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetPt_1btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_1btag                       .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_1btag                      .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_Tau32_1btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_bDisc_1btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_2btag                         .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetMass_2btag                           .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetPt_2btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_2btag                       .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_2btag                      .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_Tau32_2btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_bDisc_2btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_inclusive                     .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetMass_inclusive                       .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetPt_inclusive                         .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_inclusive                   .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_inclusive                  .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_Tau32_inclusive                         .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_bDisc_inclusive                         .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_0btag                         .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetMass_0btag                           .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetPt_0btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_0btag                       .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_0btag                      .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_Tau32_0btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_bDisc_0btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_1btag                         .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetMass_1btag                           .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetPt_1btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_1btag                       .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_1btag                      .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_Tau32_1btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_bDisc_1btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_2btag                         .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetMass_2btag                           .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetPt_2btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_2btag                       .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_2btag                      .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_Tau32_2btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_bDisc_2btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_inclusive                     .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetMass_inclusive                       .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetPt_inclusive                         .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_inclusive                   .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_inclusive                  .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_Tau32_inclusive                         .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_bDisc_inclusive                         .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_0btag                         .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetMass_0btag                           .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetPt_0btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_0btag                       .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_0btag                      .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_Tau32_0btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_bDisc_0btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_1btag                         .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetMass_1btag                           .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetPt_1btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_1btag                       .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_1btag                      .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_Tau32_1btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_bDisc_1btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_2btag                         .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetMass_2btag                           .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetPt_2btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_2btag                       .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_2btag                      .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_Tau32_2btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_bDisc_2btag                             .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_inclusive                     .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetMass_inclusive                       .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetPt_inclusive                         .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_inclusive                   .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_inclusive                  .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_Tau32_inclusive                         .GetObservedHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_bDisc_inclusive                         .GetObservedHist()   .Write()   

mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_0btag         .GetObservedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag         .GetObservedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_2btag         .GetObservedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_inclusive     .GetObservedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_0btag         .GetObservedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag         .GetObservedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_2btag         .GetObservedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_inclusive     .GetObservedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_0btag         .GetObservedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag         .GetObservedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_2btag         .GetObservedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_inclusive     .GetObservedHist()   .Write()   

mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_0btag         .GetObservedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag         .GetObservedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_2btag         .GetObservedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_inclusive     .GetObservedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_0btag         .GetObservedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag         .GetObservedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_2btag         .GetObservedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_inclusive     .GetObservedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_0btag         .GetObservedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag         .GetObservedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_2btag         .GetObservedHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_inclusive     .GetObservedHist()   .Write()   

mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_0btag         .GetObservedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag         .GetObservedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_2btag         .GetObservedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_inclusive     .GetObservedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_0btag         .GetObservedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag         .GetObservedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_2btag         .GetObservedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_inclusive     .GetObservedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_0btag         .GetObservedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag         .GetObservedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_2btag         .GetObservedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_inclusive     .GetObservedHist()   .Write()   

mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_0btag         .GetObservedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag         .GetObservedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_2btag         .GetObservedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_inclusive     .GetObservedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_0btag         .GetObservedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag         .GetObservedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_2btag         .GetObservedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_inclusive     .GetObservedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_0btag         .GetObservedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag         .GetObservedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_2btag         .GetObservedHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_inclusive     .GetObservedHist()   .Write()


mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_0btag         .GetObservedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag         .GetObservedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_2btag         .GetObservedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_inclusive     .GetObservedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_0btag         .GetObservedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag         .GetObservedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_2btag         .GetObservedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_inclusive     .GetObservedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_0btag         .GetObservedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag         .GetObservedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_2btag         .GetObservedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_inclusive     .GetObservedHist()   .Write()   

mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_0btag         .GetObservedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag         .GetObservedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_2btag         .GetObservedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_inclusive     .GetObservedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_0btag         .GetObservedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag         .GetObservedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_2btag         .GetObservedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_inclusive     .GetObservedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_0btag         .GetObservedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag         .GetObservedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_2btag         .GetObservedHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_inclusive     .GetObservedHist()   .Write()   

mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_0btag         .GetObservedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag         .GetObservedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_2btag         .GetObservedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_inclusive     .GetObservedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_0btag         .GetObservedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag         .GetObservedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_2btag         .GetObservedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_inclusive     .GetObservedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_0btag         .GetObservedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag         .GetObservedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_2btag         .GetObservedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_inclusive     .GetObservedHist()   .Write()   

mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_0btag         .GetObservedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag         .GetObservedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_2btag         .GetObservedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_inclusive     .GetObservedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_0btag         .GetObservedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag         .GetObservedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_2btag         .GetObservedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_inclusive     .GetObservedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_0btag         .GetObservedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag         .GetObservedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_2btag         .GetObservedHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_inclusive     .GetObservedHist()   .Write()



mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_0btag             .GetObservedHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_1btag             .GetObservedHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_2btag             .GetObservedHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_inclusive         .GetObservedHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_0btag             .GetObservedHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_1btag             .GetObservedHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_2btag             .GetObservedHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_inclusive         .GetObservedHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_0btag             .GetObservedHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_1btag             .GetObservedHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_2btag             .GetObservedHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_inclusive         .GetObservedHist()   .Write()      
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_0btag                  .GetObservedHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_1btag                  .GetObservedHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_2btag                  .GetObservedHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_inclusive              .GetObservedHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_0btag                  .GetObservedHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_1btag                  .GetObservedHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_2btag                  .GetObservedHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_inclusive              .GetObservedHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_0btag                  .GetObservedHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_1btag                  .GetObservedHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_2btag                  .GetObservedHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_inclusive              .GetObservedHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_0btag     .GetObservedHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_1btag     .GetObservedHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_2btag     .GetObservedHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_inclusive .GetObservedHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_0btag     .GetObservedHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_1btag     .GetObservedHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_2btag     .GetObservedHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_inclusive .GetObservedHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_0btag     .GetObservedHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_1btag     .GetObservedHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_2btag     .GetObservedHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_inclusive .GetObservedHist()   .Write()   




mttPredDist_modMass_tagMassSDTau32_dRapHi_0btag                            .GetTaggableHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapHi_1btag                            .GetTaggableHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapHi_2btag                            .GetTaggableHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapHi_inclusive                        .GetTaggableHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapLo_0btag                            .GetTaggableHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapLo_1btag                            .GetTaggableHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapLo_2btag                            .GetTaggableHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapLo_inclusive                        .GetTaggableHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapIn_0btag                            .GetTaggableHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapIn_1btag                            .GetTaggableHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapIn_2btag                            .GetTaggableHist()   .Write()  
mttPredDist_modMass_tagMassSDTau32_dRapIn_inclusive                        .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_DijetMass_0btag                          .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetMass_0btag                            .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetPt_0btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_0btag                        .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_0btag                       .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_Tau32_0btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_bDisc_0btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_DijetMass_1btag                          .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetMass_1btag                            .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetPt_1btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_1btag                        .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_1btag                       .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_Tau32_1btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_bDisc_1btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_DijetMass_2btag                          .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetMass_2btag                            .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetPt_2btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_2btag                        .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_2btag                       .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_Tau32_2btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_bDisc_2btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_DijetMass_inclusive                      .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetMass_inclusive                        .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetPt_inclusive                          .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_JetRapidity_inclusive                    .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_SoftDropMass_inclusive                   .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_Tau32_inclusive                          .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapHi_bDisc_inclusive                          .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_DijetMass_0btag                          .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetMass_0btag                            .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetPt_0btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_0btag                        .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_0btag                       .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_Tau32_0btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_bDisc_0btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_DijetMass_1btag                          .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetMass_1btag                            .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetPt_1btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_1btag                        .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_1btag                       .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_Tau32_1btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_bDisc_1btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_DijetMass_2btag                          .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetMass_2btag                            .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetPt_2btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_2btag                        .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_2btag                       .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_Tau32_2btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_bDisc_2btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_DijetMass_inclusive                      .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetMass_inclusive                        .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetPt_inclusive                          .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_JetRapidity_inclusive                    .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_SoftDropMass_inclusive                   .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_Tau32_inclusive                          .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapLo_bDisc_inclusive                          .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_DijetMass_0btag                          .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetMass_0btag                            .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetPt_0btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_0btag                        .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_0btag                       .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_Tau32_0btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_bDisc_0btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_DijetMass_1btag                          .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetMass_1btag                            .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetPt_1btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_1btag                        .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_1btag                       .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_Tau32_1btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_bDisc_1btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_DijetMass_2btag                          .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetMass_2btag                            .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetPt_2btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_2btag                        .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_2btag                       .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_Tau32_2btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_bDisc_2btag                              .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_DijetMass_inclusive                      .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetMass_inclusive                        .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetPt_inclusive                          .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_JetRapidity_inclusive                    .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_SoftDropMass_inclusive                   .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_Tau32_inclusive                          .GetTaggableHist()   .Write()  
mttPredDist_tagMassSDTau32_dRapIn_bDisc_inclusive                          .GetTaggableHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapHi_0btag                           .GetTaggableHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapHi_1btag                           .GetTaggableHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapHi_2btag                           .GetTaggableHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapHi_inclusive                       .GetTaggableHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapLo_0btag                           .GetTaggableHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapLo_1btag                           .GetTaggableHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapLo_2btag                           .GetTaggableHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapLo_inclusive                       .GetTaggableHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapIn_0btag                           .GetTaggableHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapIn_1btag                           .GetTaggableHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapIn_2btag                           .GetTaggableHist()   .Write()   
mttPredDist2_modMass_tagMassSDTau32_dRapIn_inclusive                       .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_0btag                         .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetMass_0btag                           .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetPt_0btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_0btag                       .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_0btag                      .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_Tau32_0btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_bDisc_0btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_1btag                         .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetMass_1btag                           .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetPt_1btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_1btag                       .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_1btag                      .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_Tau32_1btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_bDisc_1btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_2btag                         .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetMass_2btag                           .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetPt_2btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_2btag                       .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_2btag                      .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_Tau32_2btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_bDisc_2btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_DijetMass_inclusive                     .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetMass_inclusive                       .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetPt_inclusive                         .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_JetRapidity_inclusive                   .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_SoftDropMass_inclusive                  .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_Tau32_inclusive                         .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapHi_bDisc_inclusive                         .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_0btag                         .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetMass_0btag                           .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetPt_0btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_0btag                       .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_0btag                      .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_Tau32_0btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_bDisc_0btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_1btag                         .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetMass_1btag                           .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetPt_1btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_1btag                       .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_1btag                      .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_Tau32_1btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_bDisc_1btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_2btag                         .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetMass_2btag                           .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetPt_2btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_2btag                       .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_2btag                      .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_Tau32_2btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_bDisc_2btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_DijetMass_inclusive                     .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetMass_inclusive                       .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetPt_inclusive                         .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_JetRapidity_inclusive                   .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_SoftDropMass_inclusive                  .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_Tau32_inclusive                         .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapLo_bDisc_inclusive                         .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_0btag                         .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetMass_0btag                           .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetPt_0btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_0btag                       .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_0btag                      .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_Tau32_0btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_bDisc_0btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_1btag                         .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetMass_1btag                           .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetPt_1btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_1btag                       .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_1btag                      .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_Tau32_1btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_bDisc_1btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_2btag                         .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetMass_2btag                           .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetPt_2btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_2btag                       .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_2btag                      .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_Tau32_2btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_bDisc_2btag                             .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_DijetMass_inclusive                     .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetMass_inclusive                       .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetPt_inclusive                         .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_JetRapidity_inclusive                   .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_SoftDropMass_inclusive                  .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_Tau32_inclusive                         .GetTaggableHist()   .Write()   
mttPredDist2_tagMassSDTau32_dRapIn_bDisc_inclusive                         .GetTaggableHist()   .Write()   


mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_0btag         .GetTaggableHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag         .GetTaggableHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_2btag         .GetTaggableHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_inclusive     .GetTaggableHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_0btag         .GetTaggableHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag         .GetTaggableHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_2btag         .GetTaggableHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_inclusive     .GetTaggableHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_0btag         .GetTaggableHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag         .GetTaggableHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_2btag         .GetTaggableHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_inclusive     .GetTaggableHist()   .Write()

mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_0btag         .GetTaggableHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag         .GetTaggableHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_2btag         .GetTaggableHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_inclusive     .GetTaggableHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_0btag         .GetTaggableHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag         .GetTaggableHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_2btag         .GetTaggableHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_inclusive     .GetTaggableHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_0btag         .GetTaggableHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag         .GetTaggableHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_2btag         .GetTaggableHist()   .Write()   
mttPredDist_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_inclusive     .GetTaggableHist()   .Write()

mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_0btag         .GetTaggableHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag         .GetTaggableHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_2btag         .GetTaggableHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_inclusive     .GetTaggableHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_0btag         .GetTaggableHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag         .GetTaggableHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_2btag         .GetTaggableHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_inclusive     .GetTaggableHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_0btag         .GetTaggableHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag         .GetTaggableHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_2btag         .GetTaggableHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_inclusive     .GetTaggableHist()   .Write() 

mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_0btag         .GetTaggableHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag         .GetTaggableHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_2btag         .GetTaggableHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_inclusive     .GetTaggableHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_0btag         .GetTaggableHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag         .GetTaggableHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_2btag         .GetTaggableHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_inclusive     .GetTaggableHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_0btag         .GetTaggableHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag         .GetTaggableHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_2btag         .GetTaggableHist()   .Write()   
mttPredDist_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_inclusive     .GetTaggableHist()   .Write() 



mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_0btag         .GetTaggableHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_1btag         .GetTaggableHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_2btag         .GetTaggableHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapHi_inclusive     .GetTaggableHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_0btag         .GetTaggableHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_1btag         .GetTaggableHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_2btag         .GetTaggableHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapLo_inclusive     .GetTaggableHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_0btag         .GetTaggableHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_1btag         .GetTaggableHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_2btag         .GetTaggableHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_tagMassSDTau32_dRapIn_inclusive     .GetTaggableHist()   .Write()

mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_0btag         .GetTaggableHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_1btag         .GetTaggableHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_2btag         .GetTaggableHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapHi_inclusive     .GetTaggableHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_0btag         .GetTaggableHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_1btag         .GetTaggableHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_2btag         .GetTaggableHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapLo_inclusive     .GetTaggableHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_0btag         .GetTaggableHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_1btag         .GetTaggableHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_2btag         .GetTaggableHist()   .Write()   
mttPredDist2_EvenPred_EvenMistag_EvenObserved_modMass_tagMassSDTau32_dRapIn_inclusive     .GetTaggableHist()   .Write()

mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_0btag         .GetTaggableHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_1btag         .GetTaggableHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_2btag         .GetTaggableHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapHi_inclusive     .GetTaggableHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_0btag         .GetTaggableHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_1btag         .GetTaggableHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_2btag         .GetTaggableHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapLo_inclusive     .GetTaggableHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_0btag         .GetTaggableHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_1btag         .GetTaggableHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_2btag         .GetTaggableHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_tagMassSDTau32_dRapIn_inclusive     .GetTaggableHist()   .Write() 

mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_0btag         .GetTaggableHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_1btag         .GetTaggableHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_2btag         .GetTaggableHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapHi_inclusive     .GetTaggableHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_0btag         .GetTaggableHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_1btag         .GetTaggableHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_2btag         .GetTaggableHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapLo_inclusive     .GetTaggableHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_0btag         .GetTaggableHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_1btag         .GetTaggableHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_2btag         .GetTaggableHist()   .Write()   
mttPredDist2_OddPred_OddMistag_OddObserved_modMass_tagMassSDTau32_dRapIn_inclusive     .GetTaggableHist()   .Write() 



mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_0btag             .GetTaggableHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_1btag             .GetTaggableHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_2btag             .GetTaggableHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapHi_inclusive         .GetTaggableHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_0btag             .GetTaggableHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_1btag             .GetTaggableHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_2btag             .GetTaggableHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapLo_inclusive         .GetTaggableHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_0btag             .GetTaggableHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_1btag             .GetTaggableHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_2btag             .GetTaggableHist()   .Write()   
mttPredDist_AntiTagMinMass_modMass_tagMassSDTau32_dRapIn_inclusive         .GetTaggableHist()   .Write()      
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_0btag                  .GetTaggableHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_1btag                  .GetTaggableHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_2btag                  .GetTaggableHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapHi_inclusive              .GetTaggableHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_0btag                  .GetTaggableHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_1btag                  .GetTaggableHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_2btag                  .GetTaggableHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapLo_inclusive              .GetTaggableHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_0btag                  .GetTaggableHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_1btag                  .GetTaggableHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_2btag                  .GetTaggableHist()   .Write()   
mttPredDist_NoAntiTag_modMass_tagMassSDTau32_dRapIn_inclusive              .GetTaggableHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_0btag     .GetTaggableHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_1btag     .GetTaggableHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_2btag     .GetTaggableHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapHi_inclusive .GetTaggableHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_0btag     .GetTaggableHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_1btag     .GetTaggableHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_2btag     .GetTaggableHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapLo_inclusive .GetTaggableHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_0btag     .GetTaggableHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_1btag     .GetTaggableHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_2btag     .GetTaggableHist()   .Write()   
mttPredDist_AntiTagTau32_NoMassReq_modMass_tagMassSDTau32_dRapIn_inclusive .GetTaggableHist()   .Write()   





OUT.Write()
OUT.Close()

# print 'sf0_bTag '+str(sf0_bTag)


# print "Number of events in h_mttMass_tagMassSDTau32_dRapHi_inclusive: ", h_mttMass_tagMassSDTau32_dRapHi_inclusive.GetSum()
# print "Number of events in h_mttMass_tagMassSDTau32_dRapHi_0btag: "    , h_mttMass_tagMassSDTau32_dRapHi_0btag    .GetSum()         
# print "Number of events in h_mttMass_tagMassSDTau32_dRapHi_1btag: "    , h_mttMass_tagMassSDTau32_dRapHi_1btag    .GetSum()         
# print "Number of events in h_mttMass_tagMassSDTau32_dRapHi_2btag: "    , h_mttMass_tagMassSDTau32_dRapHi_2btag    .GetSum()         
# print "Summed number of events of dRapHi_0btag + dRapHi_1btag + dRapHi_2btag: "       , h_mttMass_tagMassSDTau32_dRapHi_0btag.GetSum() + h_mttMass_tagMassSDTau32_dRapHi_1btag.GetSum() + h_mttMass_tagMassSDTau32_dRapHi_2btag.GetSum()
# print ""
# print "Number of events in h_mttMass_tagMassSDTau32_dRapLo_inclusive: ", h_mttMass_tagMassSDTau32_dRapLo_inclusive.GetSum()         
# print "Number of events in h_mttMass_tagMassSDTau32_dRapLo_0btag: "    , h_mttMass_tagMassSDTau32_dRapLo_0btag    .GetSum()         
# print "Number of events in h_mttMass_tagMassSDTau32_dRapLo_1btag: "    , h_mttMass_tagMassSDTau32_dRapLo_1btag    .GetSum()         
# print "Number of events in h_mttMass_tagMassSDTau32_dRapLo_2btag: "    , h_mttMass_tagMassSDTau32_dRapLo_2btag    .GetSum() 
# print "Summed number of events of dRapLo_0btag + dRapLo_1btag + dRapLo_2btag: "       , h_mttMass_tagMassSDTau32_dRapLo_0btag.GetSum() + h_mttMass_tagMassSDTau32_dRapLo_1btag.GetSum() + h_mttMass_tagMassSDTau32_dRapLo_2btag.GetSum()        
# print ""
# print ""
# print "Number of events in h_bkgdEst_tagMassSDTau32_dRapHi_inclusive: ", h_bkgdEst_tagMassSDTau32_dRapHi_inclusive.GetSum()
# print "Number of events in h_bkgdEst_tagMassSDTau32_dRapHi_0btag: "    , h_bkgdEst_tagMassSDTau32_dRapHi_0btag    .GetSum()         
# print "Number of events in h_bkgdEst_tagMassSDTau32_dRapHi_1btag: "    , h_bkgdEst_tagMassSDTau32_dRapHi_1btag    .GetSum()         
# print "Number of events in h_bkgdEst_tagMassSDTau32_dRapHi_2btag: "    , h_bkgdEst_tagMassSDTau32_dRapHi_2btag    .GetSum()         
# print "Summed number of events of dRapHi_0btag + dRapHi_1btag + dRapHi_2btag: "       , h_bkgdEst_tagMassSDTau32_dRapHi_0btag.GetSum() + h_bkgdEst_tagMassSDTau32_dRapHi_1btag.GetSum() + h_bkgdEst_tagMassSDTau32_dRapHi_2btag.GetSum()
# print ""
# print "Number of events in h_bkgdEst_tagMassSDTau32_dRapLo_inclusive: ", h_bkgdEst_tagMassSDTau32_dRapLo_inclusive.GetSum()         
# print "Number of events in h_bkgdEst_tagMassSDTau32_dRapLo_0btag: "    , h_bkgdEst_tagMassSDTau32_dRapLo_0btag    .GetSum()         
# print "Number of events in h_bkgdEst_tagMassSDTau32_dRapLo_1btag: "    , h_bkgdEst_tagMassSDTau32_dRapLo_1btag    .GetSum()         
# print "Number of events in h_bkgdEst_tagMassSDTau32_dRapLo_2btag: "    , h_bkgdEst_tagMassSDTau32_dRapLo_2btag    .GetSum() 
# print "Summed number of events of dRapLo_0btag + dRapLo_1btag + dRapLo_2btag: "       , h_bkgdEst_tagMassSDTau32_dRapLo_0btag.GetSum() + h_bkgdEst_tagMassSDTau32_dRapLo_1btag.GetSum() + h_bkgdEst_tagMassSDTau32_dRapLo_2btag.GetSum()        
# print ""
# print ""
# print "Number of events in h_bkgdEst_modMass_tagMassSDTau32_dRapHi_inclusive: ", h_bkgdEst_modMass_tagMassSDTau32_dRapHi_inclusive.GetSum()
# print "Number of events in h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag: "    , h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag    .GetSum()         
# print "Number of events in h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag: "    , h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag    .GetSum()         
# print "Number of events in h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag: "    , h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag    .GetSum()         
# print "Summed number of events of dRapHi_0btag + dRapHi_1btag + dRapHi_2btag: "       , h_bkgdEst_modMass_tagMassSDTau32_dRapHi_0btag.GetSum() + h_bkgdEst_modMass_tagMassSDTau32_dRapHi_1btag.GetSum() + h_bkgdEst_modMass_tagMassSDTau32_dRapHi_2btag.GetSum()
# print ""
# print "Number of events in h_bkgdEst_modMass_tagMassSDTau32_dRapLo_inclusive: ", h_bkgdEst_modMass_tagMassSDTau32_dRapLo_inclusive.GetSum()         
# print "Number of events in h_bkgdEst_modMass_tagMassSDTau32_dRapLo_0btag: "    , h_bkgdEst_modMass_tagMassSDTau32_dRapLo_0btag    .GetSum()         
# print "Number of events in h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag: "    , h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag    .GetSum()         
# print "Number of events in h_bkgdEst_modMass_tagMassSDTau32_dRapLo_2btag: "    , h_bkgdEst_modMass_tagMassSDTau32_dRapLo_2btag    .GetSum() 
# print "Summed number of events of dRapLo_0btag + dRapLo_1btag + dRapLo_2btag: "       , h_bkgdEst_modMass_tagMassSDTau32_dRapLo_0btag.GetSum() + h_bkgdEst_modMass_tagMassSDTau32_dRapLo_1btag.GetSum() + h_bkgdEst_modMass_tagMassSDTau32_dRapLo_2btag.GetSum()        



# print 'count_oldbtagjet0      ' + str(count_oldbtagjet0      )            
# print 'count_newbtagjet0           ' + str(count_newbtagjet0           )       
# print 'count_topTag1MassSDTau32    ' + str(count_topTag1MassSDTau32    )             
# print 'count_newtopTag1MassSDTau32 ' + str(count_newtopTag1MassSDTau32 )                




