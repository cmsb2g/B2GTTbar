#! /usr/bin/env python


## _________                _____.__                            __  .__               
## \_   ___ \  ____   _____/ ____\__| ____  __ ______________ _/  |_|__| ____   ____  
## /    \  \/ /  _ \ /    \   __\|  |/ ___\|  |  \_  __ \__  \\   __\  |/  _ \ /    \ 
## \     \___(  <_> )   |  \  |  |  / /_/  >  |  /|  | \// __ \|  | |  (  <_> )   |  \
##  \______  /\____/|___|  /__|  |__\___  /|____/ |__|  (____  /__| |__|\____/|___|  /
##         \/            \/        /_____/                   \/                    \/ 
import sys
import math
import time
import array as array
from optparse import OptionParser


def Wtag_Selector(argv) : 
    parser = OptionParser()

    parser.add_option('--maxEvents', type='int', action='store',
                  default=-1,
                  dest='maxEvents',
                  help='Number of events to run. -1 is all events')

    parser.add_option('--filestr', type='string', action='store',
                      dest='filestr',
                      default = '',
                      help='File string') 

    parser.add_option('--treeLocation', type='string', action='store',
                      dest='treeLocation',
                      default = '80xTTrees', # 'Last80xTrees',#'80xTTrees',
                      help='directory ??? where CRAB output ttrees created by NtupleReader are located /store/group/lpctlbsm/aparker/???') 

    parser.add_option('--writeTree', action='store_true',
                      default=False,
                      dest='writeTree',
                      help='Write a ttree after the selection but before tau21 and tight W mass cuts')

    parser.add_option('--tau32Cut', type='float', action='store',
                      dest='tau32Cut',
                      default = 0.7,
                      help='Tau32 < tau32Cut')

    parser.add_option('--Ak8PtCut', type='float', action='store',
                      dest='Ak8PtCut',
                      default = 350.,
                      help='Ak8Pt < Ak8PtCut')

    parser.add_option('--80x', action='store_true',
                      default=True,
                      dest='is80x',
                      help='Are the ttrees produced using CMSSW 80X?')

    parser.add_option('--b2gtree', action='store_true',
                      default=False,
                      dest='b2gtree',
                      help='Are the ttrees produced using B2GTTbarb2gtree.cc ?')

    parser.add_option('--type', type='string', action='store',
                      dest='dtype',
                      default = '',
                      help='type of files to combine: data , ttjets, wjets (1-7) , st (1-4) and pseudodata (all MC combined)') # fix add pseud 

    parser.add_option('--tau21Cut', type='float', action='store',
                      dest='tau21Cut',
                      default = 0.45,
                      help='Tau21 < tau21Cut')

    parser.add_option('--verbose', action='store_true',
                      default=False,
                      dest='verbose',
                      help='Do you want to print values of key variables?')

    parser.add_option('--match', action='store_true',
                      default=False,
                      dest='match',
                      help='Do you want to get the gen match info for the ttjets MC?')

    parser.add_option('--applyTheaCorr', action='store_true',
                      default=False,
                      dest='applyTheaCorr',
                      help='Do you want to apply SD mass corrections from Thea ???')

    parser.add_option('--Type2', action='store_true',
                      default=True,
                      dest='Type2',
                      help='Do you want to apply selection for type 2 tops as described in AN-16-215 ?')

    parser.add_option('--applyHIPCorr', action='store_true',
                      default=False,
                      dest='applyHIPCorr',
                      help='Do you want apply the HIP corrections to the muons ?')

    parser.add_option('--applyElSF', action='store_true',
                      default=False,
                      dest='applyElSF',
                      help='Do you want apply the scale factors to the electrons ?')

    parser.add_option('--isMC', action='store_true',
                      default=False,
                      dest='isMC',
                      help='is it MC?')

    (options, args) = parser.parse_args(argv)
    argv = []

 #   print '===== Command line options ====='
 #   print options
 #   print '================================'

    import ROOT
    ROOT.gStyle.SetOptStat(0000000000)
    startTime = time.time()

    if options.applyTheaCorr : 
        finCor1 = ROOT.TFile.Open( "./PuppiCorr/PuppiSoftdropMassCorr/weights/puppiCorr.root","READ")
        puppisd_corrGEN      = finCor1.Get("puppiJECcorr_gen")
        puppisd_corrRECO_cen = finCor1.Get("puppiJECcorr_reco_0eta1v3")
        puppisd_corrRECO_for = finCor1.Get("puppiJECcorr_reco_1v3eta2v5")

    def getPUPPIweight(puppipt, puppieta) : #{

        genCorr  = 1.
        recoCorr = 1.
        totalWeight = 1.

        genCorr =  puppisd_corrGEN.Eval( puppipt )
        
        if (abs(puppieta) <=1.3 ): recoCorr = puppisd_corrRECO_cen.Eval(puppipt)
        if (abs(puppieta) > 1.3 ): recoCorr = puppisd_corrRECO_for.Eval(puppipt)
        totalWeight = genCorr * recoCorr
        return totalWeight
        #} 

    if options.applyElSF :
        finSF = ROOT.TFile.Open( "./egammaEffitxt_SF2D.root","READ")
        th2_EGamma_SF2D     = finSF.Get("EGamma_SF2D")
        def getgsfTrackEffScaleFactor(eleta, elpt) : #{ https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammaIDRecipesRun2#Electron_efficiencies_and_scale

            if elpt <= 200. :
                binx = th2_EGamma_SF2D.GetXaxis().FindBin( eleta )
                biny = th2_EGamma_SF2D.GetYaxis().FindBin( elpt )
                thegsfSF = th2_EGamma_SF2D.GetBinContent(binx, biny )
            else :
                binx = th2_EGamma_SF2D.GetXaxis().FindBin( eleta )
                biny = th2_EGamma_SF2D.GetYaxis().FindBin( 200. )
                thegsfSF = th2_EGamma_SF2D.GetBinContent(binx, biny )
            return thegsfSF
            #}  

    if options.applyHIPCorr :
        if options.isMC :
            c=ROOT.KalmanMuonCalibrator("MC_80X_13TeV")
        else :
            c=ROOT.KalmanMuonCalibrator("DATA_80X_13TeV")
        def getHIPMuonCorr(pt, eta, phi, charge) : #{
            # apply HIP muon corrections as described here https://twiki.cern.ch/twiki/bin/viewauth/CMS/MuonScaleResolKalman
            if pt > 200. : return pt # shoulld add inner tracker eta cut
            if options.verbose : print 'HIP Correcting Muon Pt = {0:4.3f} GeV'.format(pt)
            if charge < 0. :
                chargeSign = -1 
            if charge > 0. :
                chargeSign = 1    
            CorrMuPt =c.getCorrectedPt(pt, eta, phi, chargeSign)
            if options.verbose : print 'After HIP Correcting Muon Pt = {0:4.3f} GeV'.format(CorrMuPt)
            dpt = abs( pt- CorrMuPt )
            dptopt = dpt/ pt
            CorrMuPtError = c.getCorrectedError(CorrMuPt , eta, dptopt)#'Recall! This correction is only valid after smearing'
            CorrMuPt = c.smear(CorrMuPt , eta)
            '''
            #print 'propagate the statistical error of the calibration
            #print 'first get number of parameters'
            N=c.getN()
            #print N,'parameters'
            for i in range(0,N):
                c.vary(i,+1)
                #print 'variation',i,'ptUp', c.getCorrectedPt(pt, eta phi, charge)
                c.vary(i,-1)
                #print 'variation',i,'ptDwn', c.getCorrectedPt(pt, eta phi, charge)
            c.reset()
            #print 'propagate the closure error 
            c.varyClosure(+1)
            '''
            #newpt =  c.getCorrectedPt(pt, eta, phi, chargeSign)
            if options.verbose : print 'After HIP Correcting Muon Pt and vary closure and smear  = {0:4.3f}'.format(CorrMuPt)
            #newpt2 = c.smear(pt , eta)
            #if options.verbose : print 'After HIP Correcting Muon Pt and vary closure and smear  = {0:4.3f}'.format(newpt2)

            return CorrMuPt
            #} 


    # Create output ROOT file to store ttree after selection-When selection is good, produce final ttrees with No wtag cuts for Roofit input
    if options.writeTree :
            
        fout = ROOT.TFile( fileout, "RECREATE") 

        fout.cd()

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
        FatJetttio      = array('f', [-1.])
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
        FatJetSDsubjetWEta   = array('f', [-1.])
        FatJetSDsubjetWPhi   = array('f', [-1.])
        FatJetSDsubjetWptRaw   = array('f', [-1.])
        FatJetSDsubjetWmass = array('f', [-1.])
        FatJetSDsubjetWmassRaw = array('f', [-1.])
        FatJetSDsubjetWtau1 = array('f', [-1.])
        FatJetSDsubjetWtau2 = array('f', [-1.])
        FatJetSDsubjetWtau3 = array('f', [-1.])
        FatJetSDsubjetWtau21 = array('f', [-1.])
        FatJetSDsubjetWtau32 = array('f', [-1.])

        FatJetSDsubjetBpt   = array('f', [-1.])
        FatJetSDsubjetBmass = array('f', [-1.])
        FatJetSDsubjetBtau1 = array('f', [-1.])
        FatJetSDsubjetBtau2 = array('f', [-1.])
        FatJetSDsubjetBtau3 = array('f', [-1.])
        FatJetSDsubjetBtau21 = array('f', [-1.])
        FatJetSDsubjetBtau32 = array('f', [-1.])

        FatJetCMSmaxbdisc   = array('f', [-1.])
        FatJetCMSnsubjets   = array('f', [-1.])
        #FatJetCMSminMass    = array('f', [-1.])
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
        BJet2bDisc           = array('f', [-1.])
        BJet2Pt              = array('f', [-1.])
        BJet2Eta             = array('f', [-1.])
        BJet2Phi             = array('f', [-1.])
        BJet2Mass            = array('f', [-1.])
        Type2PairMass       = array('f', [-1.])
        Type2PairPt         = array('f', [-1.])
        DeltaRLepFat        = array('f', [-1.])
        DeltaRAK4AK8        = array('f', [-1.])

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
        LeptonLoose         = array('f', [-1.])
        LeptonTight         = array('f', [-1.])
        LeptonCharge        = array('f', [-1.])

        SemiLepMETpx        = array('f', [-1.])
        SemiLepMETpy        = array('f', [-1.])
        SemiLepMETpt        = array('f', [-1.])
        SemiLepMETphi       = array('f', [-1.])
        SemiLepNvtx         = array('f', [-1.])
        SemiLepEventWeight  = array('f', [-1.])

        SemilLepTTmass      = array('f', [-1.])
        DeltaPhiLepFat      = array('f', [-1.]) 
        DeltaRLepFat        = array('f', [-1.]) 
        DeltaRAK4AK8        = array('f', [-1.]) 
 
        AK4bDisc            = array('f', [-1.])
        NearestAK4JetPt     = array('f', [-1.])
        NearestAK4JetEta    = array('f', [-1.])
        NearestAK4JetPhi    = array('f', [-1.])
        NearestAK4JetMass   = array('f', [-1.])
        PU_CorrDn           = array('f', [-1.])
        PU_CorrUp           = array('f', [-1.])

        SemiLeptRunNum        = array('f', [-1.])   
        SemiLeptLumiBlock     = array('f', [-1.])   
        SemiLeptEventNum      = array('f', [-1.]) 

        NearestAK4JetMass   = array('f', [-1.])
        PU_CorrDn           = array('f', [-1.])
        PU_CorrUp           = array('f', [-1.])
        
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
        TreeSemiLept.Branch('FatJetSDsubjetWPhi'   , FatJetSDsubjetWPhi   ,  'FatJetSDsubjetWPhi/F'   )
        TreeSemiLept.Branch('FatJetSDsubjetWEta'   , FatJetSDsubjetWEta   ,  'FatJetSDsubjetWEta/F'   )
        TreeSemiLept.Branch('FatJetSDsubjetWptRaw'   , FatJetSDsubjetWptRaw   ,  'FatJetSDsubjetWptRaw/F'   )
        TreeSemiLept.Branch('FatJetSDsubjetWmass' , FatJetSDsubjetWmass ,  'FatJetSDsubjetWmass/F' )
        TreeSemiLept.Branch('FatJetSDsubjetWmassRaw' , FatJetSDsubjetWmassRaw ,  'FatJetSDsubjetWmassRaw/F' )
        TreeSemiLept.Branch('FatJetSDsubjetWtau1' , FatJetSDsubjetWtau1 ,  'FatJetSDsubjetWtau1/F' )
        TreeSemiLept.Branch('FatJetSDsubjetWtau2' , FatJetSDsubjetWtau2 ,  'FatJetSDsubjetWtau2/F' )
        TreeSemiLept.Branch('FatJetSDsubjetWtau3' , FatJetSDsubjetWtau3 ,  'FatJetSDsubjetWtau3/F' )
        TreeSemiLept.Branch('FatJetSDsubjetWtau21' , FatJetSDsubjetWtau21 ,  'FatJetSDsubjetWtau21/F' )
        TreeSemiLept.Branch('FatJetSDsubjetWtau32' , FatJetSDsubjetWtau32 ,  'FatJetSDsubjetWtau32/F' )
        TreeSemiLept.Branch('FatJetSDsubjetBpt'   , FatJetSDsubjetBpt   ,  'FatJetSDsubjetBpt/F'   )
        TreeSemiLept.Branch('FatJetSDsubjetBmass' , FatJetSDsubjetBmass ,  'FatJetSDsubjetBmass/F' )
        TreeSemiLept.Branch('FatJetSDsubjetBtau1' , FatJetSDsubjetBtau1 ,  'FatJetSDsubjetBtau1/F' )
        TreeSemiLept.Branch('FatJetSDsubjetBtau2' , FatJetSDsubjetBtau2 ,  'FatJetSDsubjetBtau2/F' )
        TreeSemiLept.Branch('FatJetSDsubjetBtau3' , FatJetSDsubjetBtau3 ,  'FatJetSDsubjetBtau3/F' )
        TreeSemiLept.Branch('FatJetSDsubjetBtau21' , FatJetSDsubjetBtau21 ,  'FatJetSDsubjetBtau21/F' )
        TreeSemiLept.Branch('FatJetSDsubjetBtau32' , FatJetSDsubjetBtau32 ,  'FatJetSDsubjetBtau32/F' )
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
        #TreeSemiLept.Branch('FatJetCMSminMass'    , FatJetCMSminMass    ,  'FatJetCMSminMass/F'    )
        TreeSemiLept.Branch('FatJetCMSm01'        , FatJetCMSm01        ,  'FatJetCMSm01/F'        )
        TreeSemiLept.Branch('FatJetCMSm02'        , FatJetCMSm02        ,  'FatJetCMSm02/F'        )
        TreeSemiLept.Branch('FatJetCMSm12'        , FatJetCMSm12        ,  'FatJetCMSm12/F'        )
        TreeSemiLept.Branch('FatJetNHF'           , FatJetNHF           ,  'FatJetNHF/F'           )  
        TreeSemiLept.Branch('FatJetCHF'           , FatJetCHF           ,  'FatJetCHF/F'           )  
        TreeSemiLept.Branch('FatJetNEF'           , FatJetNEF           ,  'FatJetNEF/F'           )  
        TreeSemiLept.Branch('FatJetCEF'           , FatJetCEF           ,  'FatJetCEF/F'           )  
        TreeSemiLept.Branch('FatJetNC'            , FatJetNC            ,  'FatJetNC/F'            ) 
        TreeSemiLept.Branch('FatJetNCH'           , FatJetNCH           ,  'FatJetNCH/F'           )    
        TreeSemiLept.Branch('BJet2bDisc'           , BJet2bDisc           ,  'BJet2bDisc/F'           )
        TreeSemiLept.Branch('BJet2Pt'              , BJet2Pt              ,  'BJet2Pt/F'              )
        TreeSemiLept.Branch('BJet2Eta'             , BJet2Eta             ,  'BJet2Eta/F'             )
        TreeSemiLept.Branch('BJet2Phi'             , BJet2Phi             ,  'BJet2Phi/F'             )
        TreeSemiLept.Branch('BJet2Mass'            , BJet2Mass            ,  'BJet2Mass/F'            )
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
        TreeSemiLept.Branch('LeptonCharge'        , LeptonCharge        ,  'LeptonCharge/F'         )
        TreeSemiLept.Branch('LeptonLoose'         , LeptonLoose         ,  'LeptonLoose/F'         )
        TreeSemiLept.Branch('LeptonTight'         , LeptonTight         ,  'LeptonTight/F'         )        
        TreeSemiLept.Branch('SemiLepMETpx'        , SemiLepMETpx        ,  'SemiLepMETpx/F'        )
        TreeSemiLept.Branch('SemiLepMETpy'        , SemiLepMETpy        ,  'SemiLepMETpy/F'        )
        TreeSemiLept.Branch('SemiLepMETpt'        , SemiLepMETpt        ,  'SemiLepMETpt/F'        )
        TreeSemiLept.Branch('SemiLepMETphi'       , SemiLepMETphi       ,  'SemiLepMETphi/F'       )
        TreeSemiLept.Branch('SemiLepNvtx'         , SemiLepNvtx         ,  'SemiLepNvtx/F'         )
        TreeSemiLept.Branch('SemiLepEventWeight'  , SemiLepEventWeight  ,  'SemiLepEventWeight/F'  )
        TreeSemiLept.Branch('SemilLepTTmass'      , SemilLepTTmass      ,  'SemilLepTTmass/F'      )
        TreeSemiLept.Branch('DeltaPhiLepFat'      , DeltaPhiLepFat      ,  'DeltaPhiLepFat/F'      )
        TreeSemiLept.Branch('DeltaRLepFat'        , DeltaRLepFat        ,  'DeltaRLepFat/F'        )
        TreeSemiLept.Branch('DeltaRAK4AK8'        , DeltaRAK4AK8        ,  'DeltaRAK4AK8/F'        )
        TreeSemiLept.Branch('AK4bDisc'            ,AK4bDisc             ,  'AK4bDisc/F'            )
        TreeSemiLept.Branch('NearestAK4JetPt'     ,NearestAK4JetPt      ,  'NearestAK4JetPt/F'     )
        TreeSemiLept.Branch('NearestAK4JetEta'    ,NearestAK4JetEta     ,  'NearestAK4JetEta/F'    )
        TreeSemiLept.Branch('NearestAK4JetPhi'    ,NearestAK4JetPhi     ,  'NearestAK4JetPhi/F'    )

        TreeSemiLept.Branch('NearestAK4JetMass' ,  NearestAK4JetMass    ,  'NearestAK4JetMass/F'   )
        TreeSemiLept.Branch('PU_CorrDn'         ,  PU_CorrDn            ,  'PU_CorrDn/F'           )
        TreeSemiLept.Branch('PU_CorrUp'         ,  PU_CorrUp            ,  'PU_CorrUp/F'           )
   
        TreeSemiLept.Branch('SemiLeptRunNum'         ,  SemiLeptRunNum       ,  'SemiLeptRunNum/F'          )
        TreeSemiLept.Branch('SemiLeptLumiBlock'      ,  SemiLeptLumiBlock    ,  'SemiLeptLumiBlock/F'       ) 
        TreeSemiLept.Branch('SemiLeptEventNum'       ,  SemiLeptEventNum     ,  'SemiLeptEventNum/F'        )


    if options.is80x and not options.b2gtree:  
        if options.maxEvents > 0. :
            if options.Type2 : fout= ROOT.TFile('./output80xselector/histos_type2_80x_'+str(options.maxEvents)+'_' +options.dtype + '_'+ options.treeLocation+'_'+ options.filestr + '.root', "RECREATE")
            else : fout= ROOT.TFile('./output80xselector/histos_80x_'+str(options.maxEvents)+'_' +options.dtype + '_'+ options.treeLocation+'_'+ options.filestr + '.root', "RECREATE")
        else : 
            if options.Type2 : fout= ROOT.TFile('./output80xselector/histos_type2_80x_' +options.dtype + '_'+ options.treeLocation+'_'+ options.filestr + '.root', "RECREATE")
            else : fout= ROOT.TFile('./output80xselector/histos_80x_' +options.dtype + '_'+ options.treeLocation+'_'+ options.filestr + '.root', "RECREATE")
        filein =  './%s/Puppi_%s_%s_80Xv2p0Ntuple.root'%(options.dtype, options.dtype, options.treeLocation)
        #if "wjets" in options.dtype : # fix this : only valid when running on lpc
        #    filein =  './%s/Puppi_%s_%s_80Xv2p0Ntuple.root'%('wjets', options.dtype, options.treeLocation)
        #if  options.dtype =="data": # fix this : only valid when running on lpc
        #    filein =  './%s/mu%s/Puppi_mu%s_%s_80Xv2p0Ntuple.root'%(options.dtype, options.dtype, options.dtype, options.treeLocation)

    if options.is80x and options.b2gtree:  
        if options.maxEvents > 0. :
            if options.Type2 : fout= ROOT.TFile('./Joutput80xselector/Jhistos_type2_80x_'+str(options.maxEvents)+'_' +options.dtype + '_'+ options.filestr + '.root', "RECREATE")
            if not options.Type2 : fout= ROOT.TFile('./Joutput80xselector/Jhistos_80x_'+str(options.maxEvents)+'_' +options.dtype + '_'+ options.filestr + '.root', "RECREATE")
        else : 
            if options.Type2 : fout= ROOT.TFile('./Joutput80xselector/Jhistos_type2_80x_' +options.dtype + '_'+ options.filestr + '.root', "RECREATE")
            else : fout= ROOT.TFile('./Joutput80xselector/Jhistos_80x_' +options.dtype + '_'+ options.filestr + '.root', "RECREATE")
        if options.dtype == 'data' :    filein =  './J%s/b2gtree_SingleMuon_Run2016BCD-PromptReco-v2_JSONsept9_V2_99percentFinished_All.root'%(options.dtype)
        if options.dtype == 'ttjets' :    filein = './J%s/b2gtree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISpring16MiniAODv2-PUSpring16_reHLT_V2_99percentFinished_All.root'%(options.dtype)


    if options.verbose : print "Infile  :   {0}".format( filein )
    if options.verbose : print "Outfile :   {0}".format( fout   )


    binlimit = 300.
    numbins = 1200

    h_mWsubjet_b1  = ROOT.TH1F("h_mWsubjet_b1", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_b2  = ROOT.TH1F("h_mWsubjet_b2", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_b3  = ROOT.TH1F("h_mWsubjet_b3", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_b4  = ROOT.TH1F("h_mWsubjet_b4", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_b5  = ROOT.TH1F("h_mWsubjet_b5", "; ;  ", numbins, 0, binlimit)

    h_mWsubjet_b1p  = ROOT.TH1F("h_mWsubjet_b1p", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_b2p  = ROOT.TH1F("h_mWsubjet_b2p", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_b3p  = ROOT.TH1F("h_mWsubjet_b3p", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_b4p  = ROOT.TH1F("h_mWsubjet_b4p", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_b5p  = ROOT.TH1F("h_mWsubjet_b5p", "; ;  ", numbins, 0, binlimit)

    h_mWsubjet_b1e  = ROOT.TH1F("h_mWsubjet_b1e", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_b2e  = ROOT.TH1F("h_mWsubjet_b2e", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_b3e  = ROOT.TH1F("h_mWsubjet_b3e", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_b4e  = ROOT.TH1F("h_mWsubjet_b4e", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_b5e  = ROOT.TH1F("h_mWsubjet_b5e", "; ;  ", numbins, 0, binlimit)

    h_mWsubjet_b1pe  = ROOT.TH1F("h_mWsubjet_b1pe", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_b2pe  = ROOT.TH1F("h_mWsubjet_b2pe", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_b3pe  = ROOT.TH1F("h_mWsubjet_b3pe", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_b4pe  = ROOT.TH1F("h_mWsubjet_b4pe", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_b5pe  = ROOT.TH1F("h_mWsubjet_b5pe", "; ;  ", numbins, 0, binlimit)


    h_mWsubjet_b1m  = ROOT.TH1F("h_mWsubjet_b1m", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_b2m  = ROOT.TH1F("h_mWsubjet_b2m", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_b3m  = ROOT.TH1F("h_mWsubjet_b3m", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_b4m  = ROOT.TH1F("h_mWsubjet_b4m", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_b5m  = ROOT.TH1F("h_mWsubjet_b5m", "; ;  ", numbins, 0, binlimit)

    h_mWsubjet_b1pm  = ROOT.TH1F("h_mWsubjet_b1pm", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_b2pm  = ROOT.TH1F("h_mWsubjet_b2pm", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_b3pm  = ROOT.TH1F("h_mWsubjet_b3pm", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_b4pm  = ROOT.TH1F("h_mWsubjet_b4pm", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_b5pm  = ROOT.TH1F("h_mWsubjet_b5pm", "; ;  ", numbins, 0, binlimit)

    h_mWsubjet_MC = ROOT.TH1F("h_mWsubjet_MC", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_Data = ROOT.TH1F("h_mWsubjet_Data", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_ElData = ROOT.TH1F("h_mWsubjet_ElData", "; ;  ", numbins, 0, binlimit)
    h_mWsubjet_MuData = ROOT.TH1F("h_mWsubjet_MuData", "; ;  ", numbins, 0, binlimit)
                        
    h_mWsubjetPasstag_MC = ROOT.TH1F("h_mWsubjetPasstag_MC", "; ;  ", numbins, 0, binlimit)
    h_mWsubjetPasstag_Data = ROOT.TH1F("h_mWsubjetPasstag_Data", "; ;  ", numbins, 0, binlimit)
    h_mWsubjetPasstag_ElData = ROOT.TH1F("h_mWsubjetPasstag_ElData", "; ;  ", numbins, 0, binlimit)
    h_mWsubjetPasstag_MuData = ROOT.TH1F("h_mWsubjetPasstag_MuData", "; ;  ", numbins, 0, binlimit)
 
    h_mWsubjetFailtag_MC = ROOT.TH1F("h_mWsubjetFailtag_MC", "; ;  ", numbins, 0, binlimit)
    h_mWsubjetFailtag_Data = ROOT.TH1F("h_mWsubjetFailtag_Data", "; ;  ", numbins, 0, binlimit)
    h_mWsubjetFailtag_ElData = ROOT.TH1F("h_mWsubjetFailtag_ElData", "; ;  ", numbins, 0, binlimit)
    h_mWsubjetFailtag_MuData = ROOT.TH1F("h_mWsubjetFailtag_MuData", "; ;  ", numbins, 0, binlimit)
 
    hpAll_mWsubjetPasstag_MC = ROOT.TH1F("hpAll_mWsubjetPasstag_MC", "; ;  ", numbins, 0, binlimit)
    hpAll_mWsubjetPasstag_Data = ROOT.TH1F("hpAll_mWsubjetPasstag_Data", "; ;  ", numbins, 0, binlimit)
    hpAll_mWsubjetPasstag_ElData = ROOT.TH1F("hpAll_mWsubjetPasstag_ElData", "; ;  ", numbins, 0, binlimit)
    hpAll_mWsubjetPasstag_MuData = ROOT.TH1F("hpAll_mWsubjetPasstag_MuData", "; ;  ", numbins, 0, binlimit)
 
    hpAll_mWsubjetFailtag_MC = ROOT.TH1F("hpAll_mWsubjetFailtag_MC", "; ;  ", numbins, 0, binlimit)
    hpAll_mWsubjetFailtag_Data = ROOT.TH1F("hpAll_mWsubjetFailtag_Data", "; ;  ", numbins, 0, binlimit)
    hpAll_mWsubjetFailtag_ElData = ROOT.TH1F("hpAll_mWsubjetFailtag_ElData", "; ;  ", numbins, 0, binlimit)
    hpAll_mWsubjetFailtag_MuData = ROOT.TH1F("hpAll_mWsubjetFailtag_MuData", "; ;  ", numbins, 0, binlimit)

    hlep_mWsubjetPasstag_MC = ROOT.TH1F("hlep_mWsubjetPasstag_MC", "; ;  ", numbins, 0, binlimit)
    hlep_mWsubjetPasstag_Data = ROOT.TH1F("hlep_mWsubjetPasstag_Data", "; ;  ", numbins, 0, binlimit)
    hlep_mWsubjetPasstag_ElData = ROOT.TH1F("hlep_mWsubjetPasstag_ElData", "; ;  ", numbins, 0, binlimit)
    hlep_mWsubjetPasstag_MuData = ROOT.TH1F("hlep_mWsubjetPasstag_MuData", "; ;  ", numbins, 0, binlimit)
 
    hlep_mWsubjetFailtag_MC = ROOT.TH1F("hlep_mWsubjetFailtag_MC", "; ;  ", numbins, 0, binlimit)
    hlep_mWsubjetFailtag_Data = ROOT.TH1F("hlep_mWsubjetFailtag_Data", "; ;  ", numbins, 0, binlimit)
    hlep_mWsubjetFailtag_ElData = ROOT.TH1F("hlep_mWsubjetFailtag_ElData", "; ;  ", numbins, 0, binlimit)
    hlep_mWsubjetFailtag_MuData = ROOT.TH1F("hlep_mWsubjetFailtag_MuData", "; ;  ", numbins, 0, binlimit)

    hak4_mWsubjetPasstag_MC = ROOT.TH1F("hak4_mWsubjetPasstag_MC", "; ;  ", numbins, 0, binlimit)
    hak4_mWsubjetPasstag_Data = ROOT.TH1F("hak4_mWsubjetPasstag_Data", "; ;  ", numbins, 0, binlimit)
    hak4_mWsubjetPasstag_ElData = ROOT.TH1F("hak4_mWsubjetPasstag_ElData", "; ;  ", numbins, 0, binlimit)
    hak4_mWsubjetPasstag_MuData = ROOT.TH1F("hak4_mWsubjetPasstag_MuData", "; ;  ", numbins, 0, binlimit)
 
    hak4_mWsubjetFailtag_MC = ROOT.TH1F("hak4_mWsubjetFailtag_MC", "; ;  ", numbins, 0, binlimit)
    hak4_mWsubjetFailtag_Data = ROOT.TH1F("hak4_mWsubjetFailtag_Data", "; ;  ", numbins, 0, binlimit)
    hak4_mWsubjetFailtag_ElData = ROOT.TH1F("hak4_mWsubjetFailtag_ElData", "; ;  ", numbins, 0, binlimit)
    hak4_mWsubjetFailtag_MuData = ROOT.TH1F("hak4_mWsubjetFailtag_MuData", "; ;  ", numbins, 0, binlimit)

    binlimit2 = 600.
    numbins2 = 2400

    h_lepPt_MC     = ROOT.TH1F("h_lepPt_MC", "; ;  ", numbins2, 0., binlimit2)
    h_lepEta_MC    = ROOT.TH1F("h_lepEta_MC", "; ;  ", numbins2, -3., 3.)
    h_lepHt_MC     = ROOT.TH1F("h_lepHt_MC", "; ;  ", numbins2, 0., binlimit2)
    h_lepHtLep_MC  = ROOT.TH1F("h_lepHtLep_MC", "; ;  ", numbins2, 0., binlimit2)
    h_lepSt_MC     = ROOT.TH1F("h_lepSt_MC", "; ;  ", numbins2, 0., binlimit2)

    h_lepPt_Data     = ROOT.TH1F("h_lepPt_Data ", "; ;  ", numbins2, 0., binlimit2)
    h_lepEta_Data     = ROOT.TH1F("h_lepEta_Data ", "; ;  ", numbins2, -3., 3.)
    h_lepHt_Data      = ROOT.TH1F("h_lepHt_Data ", "; ;  ", numbins2, 0., binlimit2)
    h_lepHtLep_Data   = ROOT.TH1F("h_lepHtLep_Data ", "; ;  ", numbins2, 0., binlimit2)
    h_lepSt_Data      = ROOT.TH1F("h_lepSt_Data ", "; ;  ", numbins2, 0., binlimit2)

    h_lepPt_ElData     = ROOT.TH1F("h_lepPt_ElData ", "; ;  ", numbins2, 0., binlimit2)
    h_lepEta_ElData     = ROOT.TH1F("h_lepEta_ElData ", "; ;  ", numbins2, -3., 3.)
    h_lepHt_ElData      = ROOT.TH1F("h_lepHt_ElData ", "; ;  ", numbins2, 0., binlimit2)
    h_lepHtLep_ElData   = ROOT.TH1F("h_lepHtLep_ElData ", "; ;  ", numbins2, 0., binlimit2)
    h_lepSt_ElData      = ROOT.TH1F("h_lepSt_ElData ", "; ;  ", numbins2, 0., binlimit2)

    h_lepPt_MuData     = ROOT.TH1F("h_lepPt_MuData ", "; ;  ", numbins2, 0., binlimit2)
    h_lepEta_MuData     = ROOT.TH1F("h_lepEta_MuData ", "; ;  ", numbins2, -3., 3.)
    h_lepHt_MuData      = ROOT.TH1F("h_lepHt_MuData ", "; ;  ", numbins2, 0., binlimit2)
    h_lepHtLep_MuData   = ROOT.TH1F("h_lepHtLep_MuData ", "; ;  ", numbins2, 0., binlimit2)
    h_lepSt_MuData      = ROOT.TH1F("h_lepSt_MuData ", "; ;  ", numbins2, 0., binlimit2)

    hlep_lepPt_MC     = ROOT.TH1F("hlep_lepPt_MC", "; ;  ", numbins2, 0., binlimit2)
    hlep_lepEta_MC    = ROOT.TH1F("hlep_lepEta_MC", "; ;  ", numbins2, -3., 3.)
    hlep_lepHt_MC     = ROOT.TH1F("hlep_lepHt_MC", "; ;  ", numbins2, 0., binlimit2)
    hlep_lepHtLep_MC  = ROOT.TH1F("hlep_lepHtLep_MC", "; ;  ", numbins2, 0., binlimit2)
    hlep_lepSt_MC     = ROOT.TH1F("hlep_lepSt_MC", "; ;  ", numbins2, 0., binlimit2)

    hlep_lepPt_Data     = ROOT.TH1F("hlep_lepPt_Data ", "; ;  ", numbins2, 0., binlimit2)
    hlep_lepEta_Data     = ROOT.TH1F("hlep_lepEta_Data ", "; ;  ", numbins2, -3., 3.)
    hlep_lepHt_Data      = ROOT.TH1F("hlep_lepHt_Data ", "; ;  ", numbins2, 0., binlimit2)
    hlep_lepHtLep_Data   = ROOT.TH1F("hlep_lepHtLep_Data ", "; ;  ", numbins2, 0., binlimit2)
    hlep_lepSt_Data      = ROOT.TH1F("hlep_lepSt_Data ", "; ;  ", numbins2, 0., binlimit2)

    hlep_lepPt_ElData     = ROOT.TH1F("hlep_lepPt_ElData ", "; ;  ", numbins2, 0., binlimit2)
    hlep_lepEta_ElData     = ROOT.TH1F("hlep_lepEta_ElData ", "; ;  ", numbins2, -3., 3.)
    hlep_lepHt_ElData      = ROOT.TH1F("hlep_lepHt_ElData ", "; ;  ", numbins2, 0., binlimit2)
    hlep_lepHtLep_ElData   = ROOT.TH1F("hlep_lepHtLep_ElData ", "; ;  ", numbins2, 0., binlimit2)
    hlep_lepSt_ElData      = ROOT.TH1F("hlep_lepSt_ElData ", "; ;  ", numbins2, 0., binlimit2)

    hlep_lepPt_MuData     = ROOT.TH1F("hlep_lepPt_MuData ", "; ;  ", numbins2, 0., binlimit2)
    hlep_lepEta_MuData     = ROOT.TH1F("hlep_lepEta_MuData ", "; ;  ", numbins2, -3., 3.)
    hlep_lepHt_MuData      = ROOT.TH1F("hlep_lepHt_MuData ", "; ;  ", numbins2, 0., binlimit2)
    hlep_lepHtLep_MuData   = ROOT.TH1F("hlep_lepHtLep_MuData ", "; ;  ", numbins2, 0., binlimit2)
    hlep_lepSt_MuData      = ROOT.TH1F("hlep_lepSt_MuData ", "; ;  ", numbins2, 0., binlimit2)

    hpAll_lepPt_MC     = ROOT.TH1F("hpAll_lepPt_MC", "; ;  ", numbins2, 0., binlimit2)
    hpAll_lepEta_MC    = ROOT.TH1F("hpAll_lepEta_MC", "; ;  ", numbins2, -3., 3.)
    hpAll_lepHt_MC     = ROOT.TH1F("hpAll_lepHt_MC", "; ;  ", numbins2, 0., binlimit2)
    hpAll_lepHtLep_MC  = ROOT.TH1F("hpAll_lepHtLep_MC", "; ;  ", numbins2, 0., binlimit2)
    hpAll_lepSt_MC     = ROOT.TH1F("hpAll_lepSt_MC", "; ;  ", numbins2, 0., binlimit2)

    hpAll_lepPt_Data     = ROOT.TH1F("hpAll_lepPt_Data ", "; ;  ", numbins2, 0., binlimit2)
    hpAll_lepEta_Data     = ROOT.TH1F("hpAll_lepEta_Data ", "; ;  ", numbins2, -3., 3.)
    hpAll_lepHt_Data      = ROOT.TH1F("hpAll_lepHt_Data ", "; ;  ", numbins2, 0., binlimit2)
    hpAll_lepHtLep_Data   = ROOT.TH1F("hpAll_lepHtLep_Data ", "; ;  ", numbins2, 0., binlimit2)
    hpAll_lepSt_Data      = ROOT.TH1F("hpAll_lepSt_Data ", "; ;  ", numbins2, 0., binlimit2)

    hpAll_lepPt_ElData     = ROOT.TH1F("hpAll_lepPt_ElData ", "; ;  ", numbins2, 0., binlimit2)
    hpAll_lepEta_ElData     = ROOT.TH1F("hpAll_lepEta_ElData ", "; ;  ", numbins2, -3., 3.)
    hpAll_lepHt_ElData      = ROOT.TH1F("hpAll_lepHt_ElData ", "; ;  ", numbins2, 0., binlimit2)
    hpAll_lepHtLep_ElData   = ROOT.TH1F("hpAll_lepHtLep_ElData ", "; ;  ", numbins2, 0., binlimit2)
    hpAll_lepSt_ElData      = ROOT.TH1F("hpAll_lepSt_ElData ", "; ;  ", numbins2, 0., binlimit2)

    hpAll_lepPt_MuData     = ROOT.TH1F("hpAll_lepPt_MuData ", "; ;  ", numbins2, 0., binlimit2)
    hpAll_lepEta_MuData     = ROOT.TH1F("hpAll_lepEta_MuData ", "; ;  ", numbins2, -3., 3.)
    hpAll_lepHt_MuData      = ROOT.TH1F("hpAll_lepHt_MuData ", "; ;  ", numbins2, 0., binlimit2)
    hpAll_lepHtLep_MuData   = ROOT.TH1F("hpAll_lepHtLep_MuData ", "; ;  ", numbins2, 0., binlimit2)
    hpAll_lepSt_MuData      = ROOT.TH1F("hpAll_lepSt_MuData ", "; ;  ", numbins2, 0., binlimit2)

    hak4_lepPt_MC     = ROOT.TH1F("hak4_lepPt_MC", "; ;  ", numbins2, 0., binlimit2)
    hak4_lepEta_MC    = ROOT.TH1F("hak4_lepEta_MC", "; ;  ", numbins2, -3., 3.)
    hak4_lepHt_MC     = ROOT.TH1F("hak4_lepHt_MC", "; ;  ", numbins2, 0., binlimit2)
    hak4_lepHtLep_MC  = ROOT.TH1F("hak4_lepHtLep_MC", "; ;  ", numbins2, 0., binlimit2)
    hak4_lepSt_MC     = ROOT.TH1F("hak4_lepSt_MC", "; ;  ", numbins2, 0., binlimit2)

    hak4_lepPt_Data     = ROOT.TH1F("hak4_lepPt_Data ", "; ;  ", numbins2, 0., binlimit2)
    hak4_lepEta_Data     = ROOT.TH1F("hak4_lepEta_Data ", "; ;  ", numbins2, -3., 3.)
    hak4_lepHt_Data      = ROOT.TH1F("hak4_lepHt_Data ", "; ;  ", numbins2, 0., binlimit2)
    hak4_lepHtLep_Data   = ROOT.TH1F("hak4_lepHtLep_Data ", "; ;  ", numbins2, 0., binlimit2)
    hak4_lepSt_Data      = ROOT.TH1F("hak4_lepSt_Data ", "; ;  ", numbins2, 0., binlimit2)

    hak4_lepPt_ElData     = ROOT.TH1F("hak4_lepPt_ElData ", "; ;  ", numbins2, 0., binlimit2)
    hak4_lepEta_ElData     = ROOT.TH1F("hak4_lepEta_ElData ", "; ;  ", numbins2, -3., 3.)
    hak4_lepHt_ElData      = ROOT.TH1F("hak4_lepHt_ElData ", "; ;  ", numbins2, 0., binlimit2)
    hak4_lepHtLep_ElData   = ROOT.TH1F("hak4_lepHtLep_ElData ", "; ;  ", numbins2, 0., binlimit2)
    hak4_lepSt_ElData      = ROOT.TH1F("hak4_lepSt_ElData ", "; ;  ", numbins2, 0., binlimit2)

    hak4_lepPt_MuData     = ROOT.TH1F("hak4_lepPt_MuData ", "; ;  ", numbins2, 0., binlimit2)
    hak4_lepEta_MuData     = ROOT.TH1F("hak4_lepEta_MuData ", "; ;  ", numbins2, -3., 3.)
    hak4_lepHt_MuData      = ROOT.TH1F("hak4_lepHt_MuData ", "; ;  ", numbins2, 0., binlimit2)
    hak4_lepHtLep_MuData   = ROOT.TH1F("hak4_lepHtLep_MuData ", "; ;  ", numbins2, 0., binlimit2)
    hak4_lepSt_MuData      = ROOT.TH1F("hak4_lepSt_MuData ", "; ;  ", numbins2, 0., binlimit2)

    binlimit3 = 1000.
    numbins3 = 2000


    h_AK8Tau21_Data           = ROOT.TH1F("h_AK8Tau21_Data", "; ;  ", numbins2, 0., 1.)
    h_AK8subjetTau21_Data     = ROOT.TH1F("h_AK8subjetTau21_Data", "; ;  ", numbins2, 0.,1.)
    h_AK8Pt_Data              = ROOT.TH1F("h_AK8Pt_Data", "; ;  ", numbins3, 0., binlimit3)
    h_AK8subjetPt_Data        = ROOT.TH1F("h_AK8subjetPt_Data", "; ;  ", numbins3, 0., binlimit3)

    h_AK8Tau21_ElData           = ROOT.TH1F("h_AK8Tau21_ElData", "; ;  ", numbins2, 0., 1.)
    h_AK8subjetTau21_ElData     = ROOT.TH1F("h_AK8subjetTau21_ElData", "; ;  ", numbins2, 0., 1.)
    h_AK8Pt_ElData              = ROOT.TH1F("h_AK8Pt_ElData", "; ;  ", numbins3, 0., binlimit3)
    h_AK8subjetPt_ElData        = ROOT.TH1F("h_AK8subjetPt_ElData", "; ;  ", numbins3, 0., binlimit3)

    h_AK8Tau21_MuData           = ROOT.TH1F("h_AK8Tau21_MuData", "; ;  ", numbins2, 0., 1.)
    h_AK8subjetTau21_MuData     = ROOT.TH1F("h_AK8subjetTau21_MuData", "; ;  ", numbins2, 0., 1.)
    h_AK8Pt_MuData              = ROOT.TH1F("h_AK8Pt_MuData", "; ;  ", numbins3, 0., binlimit3)
    h_AK8subjetPt_MuData        = ROOT.TH1F("h_AK8subjetPt_MuData", "; ;  ", numbins3, 0., binlimit3)

    h_AK8Tau21_MC           = ROOT.TH1F("h_AK8Tau21_MC", "; ;  ", numbins2, 0., 1.)
    h_AK8subjetTau21_MC     = ROOT.TH1F("h_AK8subjetTau21_MC", "; ;  ", numbins2,0., 1.)
    h_AK8Pt_MC              = ROOT.TH1F("h_AK8Pt_MC", "; ;  ", numbins3, 0., binlimit3)
    h_AK8subjetPt_MC        = ROOT.TH1F("h_AK8subjetPt_MC", "; ;  ", numbins3, 0., binlimit3)

    hlep_AK8Tau21_Data           = ROOT.TH1F("hlep_AK8Tau21_Data", "; ;  ", numbins2, 0., 1.)
    hlep_AK8subjetTau21_Data     = ROOT.TH1F("hlep_AK8subjetTau21_Data", "; ;  ", numbins2, 0.,1.)
    hlep_AK8Pt_Data              = ROOT.TH1F("hlep_AK8Pt_Data", "; ;  ", numbins3, 0., binlimit3)
    hlep_AK8subjetPt_Data        = ROOT.TH1F("hlep_AK8subjetPt_Data", "; ;  ", numbins3, 0., binlimit3)

    hlep_AK8Tau21_ElData           = ROOT.TH1F("hlep_AK8Tau21_ElData", "; ;  ", numbins2, 0., 1.)
    hlep_AK8subjetTau21_ElData     = ROOT.TH1F("hlep_AK8subjetTau21_ElData", "; ;  ", numbins2, 0., 1.)
    hlep_AK8Pt_ElData              = ROOT.TH1F("hlep_AK8Pt_ElData", "; ;  ", numbins3, 0., binlimit2)
    hlep_AK8subjetPt_ElData        = ROOT.TH1F("hlep_AK8subjetPt_ElData", "; ;  ", numbins3, 0., binlimit3)

    hlep_AK8Tau21_MuData           = ROOT.TH1F("hlep_AK8Tau21_MuData", "; ;  ", numbins2, 0., 1.)
    hlep_AK8subjetTau21_MuData     = ROOT.TH1F("hlep_AK8subjetTau21_MuData", "; ;  ", numbins2, 0., 1.)
    hlep_AK8Pt_MuData              = ROOT.TH1F("hlep_AK8Pt_MuData", "; ;  ", numbins3, 0., binlimit3)
    hlep_AK8subjetPt_MuData        = ROOT.TH1F("hlep_AK8subjetPt_MuData", "; ;  ", numbins3, 0., binlimit3)

    hlep_AK8Tau21_MC           = ROOT.TH1F("hlep_AK8Tau21_MC", "; ;  ", numbins2, 0., 1.)
    hlep_AK8subjetTau21_MC     = ROOT.TH1F("hlep_AK8subjetTau21_MC", "; ;  ", numbins2,0., 1.)
    hlep_AK8Pt_MC              = ROOT.TH1F("hlep_AK8Pt_MC", "; ;  ", numbins3, 0., binlimit3)
    hlep_AK8subjetPt_MC        = ROOT.TH1F("hlep_AK8subjetPt_MC", "; ;  ", numbins3, 0., binlimit3)

    hpAll_AK8Tau21_Data           = ROOT.TH1F("hpAll_AK8Tau21_Data", "; ;  ", numbins2, 0., 1.)
    hpAll_AK8subjetTau21_Data     = ROOT.TH1F("hpAll_AK8subjetTau21_Data", "; ;  ", numbins2, 0.,1.)
    hpAll_AK8Pt_Data              = ROOT.TH1F("hpAll_AK8Pt_Data", "; ;  ", numbins3, 0., binlimit3)
    hpAll_AK8subjetPt_Data        = ROOT.TH1F("hpAll_AK8subjetPt_Data", "; ;  ", numbins3, 0., binlimit3)

    hpAll_AK8Tau21_ElData           = ROOT.TH1F("hpAll_AK8Tau21_ElData", "; ;  ", numbins2, 0., 1.)
    hpAll_AK8subjetTau21_ElData     = ROOT.TH1F("hpAll_AK8subjetTau21_ElData", "; ;  ", numbins2, 0., 1.)
    hpAll_AK8Pt_ElData              = ROOT.TH1F("hpAll_AK8Pt_ElData", "; ;  ", numbins3, 0., binlimit3)
    hpAll_AK8subjetPt_ElData        = ROOT.TH1F("hpAll_AK8subjetPt_ElData", "; ;  ", numbins3, 0., binlimit3)

    hpAll_AK8Tau21_MuData           = ROOT.TH1F("hpAll_AK8Tau21_MuData", "; ;  ", numbins2, 0., 1.)
    hpAll_AK8subjetTau21_MuData     = ROOT.TH1F("hpAll_AK8subjetTau21_MuData", "; ;  ", numbins2, 0., 1.)
    hpAll_AK8Pt_MuData              = ROOT.TH1F("hpAll_AK8Pt_MuData", "; ;  ", numbins3, 0., binlimit3)
    hpAll_AK8subjetPt_MuData        = ROOT.TH1F("hpAll_AK8subjetPt_MuData", "; ;  ", numbins3, 0., binlimit3)

    hpAll_AK8Tau21_MC           = ROOT.TH1F("hpAll_AK8Tau21_MC", "; ;  ", numbins2, 0., 1.)
    hpAll_AK8subjetTau21_MC     = ROOT.TH1F("hpAll_AK8subjetTau21_MC", "; ;  ", numbins2,0., 1.)
    hpAll_AK8Pt_MC              = ROOT.TH1F("hpAll_AK8Pt_MC", "; ;  ", numbins3, 0., binlimit3)
    hpAll_AK8subjetPt_MC        = ROOT.TH1F("hpAll_AK8subjetPt_MC", "; ;  ", numbins3, 0., binlimit3)

    hak4_AK8Tau21_Data           = ROOT.TH1F("hak4_AK8Tau21_Data", "; ;  ", numbins2, 0., 1.)
    hak4_AK8subjetTau21_Data     = ROOT.TH1F("hak4_AK8subjetTau21_Data", "; ;  ", numbins2, 0.,1.)
    hak4_AK8Pt_Data              = ROOT.TH1F("hak4_AK8Pt_Data", "; ;  ", numbins3, 0., binlimit3)
    hak4_AK8subjetPt_Data        = ROOT.TH1F("hak4_AK8subjetPt_Data", "; ;  ", numbins3, 0., binlimit3)

    hak4_AK8Tau21_ElData           = ROOT.TH1F("hak4_AK8Tau21_ElData", "; ;  ", numbins2, 0., 1.)
    hak4_AK8subjetTau21_ElData     = ROOT.TH1F("hak4_AK8subjetTau21_ElData", "; ;  ", numbins2, 0., 1.)
    hak4_AK8Pt_ElData              = ROOT.TH1F("hak4_AK8Pt_ElData", "; ;  ", numbins3, 0., binlimit3)
    hak4_AK8subjetPt_ElData        = ROOT.TH1F("hak4_AK8subjetPt_ElData", "; ;  ", numbins3, 0., binlimit3)

    hak4_AK8Tau21_MuData           = ROOT.TH1F("hak4_AK8Tau21_MuData", "; ;  ", numbins2, 0., 1.)
    hak4_AK8subjetTau21_MuData     = ROOT.TH1F("hak4_AK8subjetTau21_MuData", "; ;  ", numbins2, 0., 1.)
    hak4_AK8Pt_MuData              = ROOT.TH1F("hak4_AK8Pt_MuData", "; ;  ", numbins3, 0., binlimit3)
    hak4_AK8subjetPt_MuData        = ROOT.TH1F("hak4_AK8subjetPt_MuData", "; ;  ", numbins3, 0., binlimit3)

    hak4_AK8Tau21_MC           = ROOT.TH1F("hak4_AK8Tau21_MC", "; ;  ", numbins2, 0., 1.)
    hak4_AK8subjetTau21_MC     = ROOT.TH1F("hak4_AK8subjetTau21_MC", "; ;  ", numbins2,0., 1.)
    hak4_AK8Pt_MC              = ROOT.TH1F("hak4_AK8Pt_MC", "; ;  ", numbins3, 0., binlimit3)
    hak4_AK8subjetPt_MC        = ROOT.TH1F("hak4_AK8subjetPt_MC", "; ;  ", numbins3, 0., binlimit3)


    # Counters for cut flow table
    passcuts = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    fillTree = False
    NpassPre = 0
    NpassPost = 0

    # Open Input file and read tree


    fin = ROOT.TFile.Open( filein )
    if options.verbose :  print "Opened the File!  {}".format(filein)

    if options.b2gtree :
        t =  fin.Get("ana/TreeSemiLept") 
    if not options.b2gtree :
        t =  fin.Get("TreeSemiLept") 
    if options.b2gtree :

        JetPtRaw                     = array.array('f', [0.] )      
        JetEtaRaw                    = array.array('f', [0.] )
        JetPhiRaw                    = array.array('f', [0.] )
        JetMassRaw                   = array.array('f', [0.] )
        JetP                         = array.array('f', [0.] )
        JetPt                        = array.array('f', [0.] )
        JetEta                       = array.array('f', [0.] )
        JetPhi                       = array.array('f', [0.] )
        JetRap                       = array.array('f', [0.] )
        JetEnergy                    = array.array('f', [0.] )
        JetMass                      = array.array('f', [0.] )
        JetArea                      = array.array('f', [0.] )
        JetSDmass                    = array.array('f', [0.] )
        JetSDmassRaw                 = array.array('f', [0.] )
        JetSDmassCorrL23             = array.array('f', [0.] )
        JetSDmassCorrL23Up           = array.array('f', [0.] )
        JetSDmassCorrL23Dn           = array.array('f', [0.] )
        JetSDmassCorrL123            = array.array('f', [0.] )
        JetSDmassCorrL123Up          = array.array('f', [0.] )
        JetSDmassCorrL123Dn          = array.array('f', [0.] )
        JetSDmassCorrL23Smear        = array.array('f', [0.] )
        JetSDmassCorrL23SmearUp      = array.array('f', [0.] )
        JetSDmassCorrL23SmearDn      = array.array('f', [0.] )
        JetSDptRaw                   = array.array('f', [0.] )
        JetSDptCorrL23               = array.array('f', [0.] )
        JetSDptCorrL23Up             = array.array('f', [0.] )
        JetSDptCorrL23Dn             = array.array('f', [0.] )
        JetSDptCorrL123              = array.array('f', [0.] )
        JetSDptCorrL123Up            = array.array('f', [0.] )
        JetSDptCorrL123Dn            = array.array('f', [0.] )
        JetSDptCorrL23Smear          = array.array('f', [0.] )
        JetSDptCorrL23SmearUp        = array.array('f', [0.] )
        JetSDptCorrL23SmearDn        = array.array('f', [0.] )
        JetSDetaRaw                  = array.array('f', [0.] )
        JetSDphiRaw                  = array.array('f', [0.] )
        JetMassPruned                = array.array('f', [0.] )
        JetMassTrimmed               = array.array('f', [0.] )
        JetTau1                      = array.array('f', [0.] )
        JetTau2                      = array.array('f', [0.] )
        JetTau3                      = array.array('f', [0.] )
        JetTau4                      = array.array('f', [0.] )
        JetTau32                     = array.array('f', [0.] )
        JetTau21                     = array.array('f', [0.] )
        JetSDsubjet0bdisc            = array.array('f', [0.] )
        JetSDsubjet1bdisc            = array.array('f', [0.] )
        JetSDmaxbdisc                = array.array('f', [0.] )
        JetSDmaxbdiscflavHadron      = array.array('f', [0.] )
        JetSDmaxbdiscflavParton      = array.array('f', [0.] )
        JetSDsubjet0pt               = array.array('f', [0.] )
        JetSDsubjet0mass             = array.array('f', [0.] )
        JetSDsubjet0eta              = array.array('f', [0.] )
        JetSDsubjet0phi              = array.array('f', [0.] )
        JetSDsubjet0area             = array.array('f', [0.] )
        JetSDsubjet0flavHadron       = array.array('f', [0.] )
        JetSDsubjet0flavParton       = array.array('f', [0.] )
        JetSDsubjet0tau1             = array.array('f', [0.] )
        JetSDsubjet0tau2             = array.array('f', [0.] )
        JetSDsubjet0tau3             = array.array('f', [0.] )
        JetSDsubjet1pt               = array.array('f', [0.] )
        JetSDsubjet1mass             = array.array('f', [0.] )
        JetSDsubjet1eta              = array.array('f', [0.] )
        JetSDsubjet1phi              = array.array('f', [0.] )
        JetSDsubjet1area             = array.array('f', [0.] )
        JetSDsubjet1flavHadron                = array.array('f', [0.] )
        JetSDsubjet1flavParton                = array.array('f', [0.] )
        JetSDsubjet1tau1             = array.array('f', [0.] )
        JetSDsubjet1tau2             = array.array('f', [0.] )
        JetSDsubjet1tau3             = array.array('f', [0.] )
        JetPuppiP                    = array.array('f', [0.] )
        JetPuppiPt                   = array.array('f', [0.] )
        JetPuppiEta                  = array.array('f', [0.] )
        JetPuppiPhi                  = array.array('f', [0.] )
        JetPuppiMass                 = array.array('f', [0.] )
        JetPuppiSDmass               = array.array('f', [0.] )
        JetPuppiSDmassCorr           = array.array('f', [0.] )
        JetPuppiSDmassCorrUp         = array.array('f', [0.] )
        JetPuppiSDmassCorrDn         = array.array('f', [0.] )
        JetPuppiSDmassCorrL23Smear           = array.array('f', [0.] )
        JetPuppiSDmassCorrL23SmearUp         = array.array('f', [0.] )
        JetPuppiSDmassCorrL23SmearDn         = array.array('f', [0.] )
        JetPuppiSDpt                 = array.array('f', [0.] )
        JetPuppiSDptCorr             = array.array('f', [0.] )
        JetPuppiSDptCorrUp           = array.array('f', [0.] )
        JetPuppiSDptCorrDn           = array.array('f', [0.] )
        JetPuppiSDptCorrL23Smear             = array.array('f', [0.] )
        JetPuppiSDptCorrL23SmearUp           = array.array('f', [0.] )
        JetPuppiSDptCorrL23SmearDn           = array.array('f', [0.] )
        JetPuppiSDeta                = array.array('f', [0.] )
        JetPuppiSDphi                = array.array('f', [0.] )
        JetPuppiTau1                 = array.array('f', [0.] )
        JetPuppiTau2                 = array.array('f', [0.] )
        JetPuppiTau3                 = array.array('f', [0.] )
        JetPuppiTau4                 = array.array('f', [0.] )
        JetPuppiTau32                = array.array('f', [0.] )
        JetPuppiTau21                = array.array('f', [0.] )
        JetPuppiSDsubjet0bdisc               = array.array('f', [0.] )
        JetPuppiSDsubjet1bdisc               = array.array('f', [0.] )
        JetPuppiSDmaxbdisc           = array.array('f', [0.] )
        JetPuppiSDmaxbdiscflavHadron         = array.array('f', [0.] )
        JetPuppiSDmaxbdiscflavParton         = array.array('f', [0.] )
        JetPuppiSDsubjet0pt          = array.array('f', [0.] )
        JetPuppiSDsubjet0mass                = array.array('f', [0.] )
        JetPuppiSDsubjet0eta         = array.array('f', [0.] )
        JetPuppiSDsubjet0phi         = array.array('f', [0.] )
        JetPuppiSDsubjet0area                = array.array('f', [0.] )
        JetPuppiSDsubjet0flavHadron          = array.array('f', [0.] )
        JetPuppiSDsubjet0flavParton          = array.array('f', [0.] )
        JetPuppiSDsubjet0tau1                = array.array('f', [0.] )
        JetPuppiSDsubjet0tau2                = array.array('f', [0.] )
        JetPuppiSDsubjet0tau3                = array.array('f', [0.] )
        JetPuppiSDsubjet1pt          = array.array('f', [0.] )
        JetPuppiSDsubjet1mass                = array.array('f', [0.] )
        JetPuppiSDsubjet1eta         = array.array('f', [0.] )
        JetPuppiSDsubjet1phi         = array.array('f', [0.] )
        JetPuppiSDsubjet1area                = array.array('f', [0.] )
        JetPuppiSDsubjet1flavHadron          = array.array('f', [0.] )
        JetPuppiSDsubjet1flavParton          = array.array('f', [0.] )
        JetPuppiSDsubjet1tau1                = array.array('f', [0.] )
        JetPuppiSDsubjet1tau2                = array.array('f', [0.] )
        JetPuppiSDsubjet1tau3                = array.array('f', [0.] )
        JetCHF                       = array.array('f', [0.] )
        JetNHF                       = array.array('f', [0.] )
        JetCM                        = array.array('f', [0.] )
        JetNM                        = array.array('f', [0.] )
        JetNEF                       = array.array('f', [0.] )
        JetCEF                       = array.array('f', [0.] )
        JetMF                        = array.array('f', [0.] )
        JetMult                      = array.array('f', [0.] )
        JetPuppiCHF                  = array.array('f', [0.] )
        JetPuppiNHF                  = array.array('f', [0.] )
        JetPuppiCM                   = array.array('f', [0.] )
        JetPuppiNM                   = array.array('f', [0.] )
        JetPuppiNEF                  = array.array('f', [0.] )
        JetPuppiCEF                  = array.array('f', [0.] )
        JetPuppiMF                   = array.array('f', [0.] )
        JetPuppiMult                 = array.array('f', [0.] )
        JetMassCorrFactor            = array.array('f', [0.] )
        JetMassCorrFactorUp          = array.array('f', [0.] )
        JetMassCorrFactorDn          = array.array('f', [0.] )
        JetCorrFactor                = array.array('f', [0.] )
        JetCorrFactorUp              = array.array('f', [0.] )
        JetCorrFactorDn              = array.array('f', [0.] )
        JetPtSmearFactor             = array.array('f', [0.] )
        JetPtSmearFactorUp           = array.array('f', [0.] )
        JetPtSmearFactorDn           = array.array('f', [0.] )
        JetPuppiMassCorrFactor               = array.array('f', [0.] )
        JetPuppiMassCorrFactorUp             = array.array('f', [0.] )
        JetPuppiMassCorrFactorDn             = array.array('f', [0.] )
        JetPuppiCorrFactor           = array.array('f', [0.] )
        JetPuppiCorrFactorUp         = array.array('f', [0.] )
        JetPuppiCorrFactorDn         = array.array('f', [0.] )
        JetPuppiPtSmearFactor                = array.array('f', [0.] )
        JetPuppiPtSmearFactorUp              = array.array('f', [0.] )
        JetPuppiPtSmearFactorDn              = array.array('f', [0.] )
        JetEtaScaleFactor            = array.array('f', [0.] )
        JetPhiScaleFactor            = array.array('f', [0.] )
        JetMatchedGenJetDR           = array.array('f', [0.] )
        JetMatchedGenJetPt           = array.array('f', [0.] )
        JetMatchedGenJetMass         = array.array('f', [0.] )
        JetGenMatched_TopHadronic            = array.array('f', [0.] )
        JetGenMatched_TopPt          = array.array('f', [0.] )
        JetGenMatched_TopEta         = array.array('f', [0.] )
        JetGenMatched_TopPhi         = array.array('f', [0.] )
        JetGenMatched_TopMass                = array.array('f', [0.] )
        JetGenMatched_bPt            = array.array('f', [0.] )
        JetGenMatched_WPt            = array.array('f', [0.] )
        JetGenMatched_Wd1Pt          = array.array('f', [0.] )
        JetGenMatched_Wd2Pt          = array.array('f', [0.] )
        JetGenMatched_Wd1ID          = array.array('f', [0.] )
        JetGenMatched_Wd2ID          = array.array('f', [0.] )
        JetGenMatched_MaxDeltaRPartonTop     = array.array('f', [0.] )
        JetGenMatched_MaxDeltaRWPartonTop    = array.array('f', [0.] )
        JetGenMatched_MaxDeltaRWPartonW      = array.array('f', [0.] )
        JetGenMatched_DeltaR_t_b             = array.array('f', [0.] )
        JetGenMatched_DeltaR_t_W             = array.array('f', [0.] )
        JetGenMatched_DeltaR_t_Wd1           = array.array('f', [0.] )
        JetGenMatched_DeltaR_t_Wd2           = array.array('f', [0.] )
        JetGenMatched_DeltaR_W_b1            = array.array('f', [0.] )
        JetGenMatched_DeltaR_W_Wd1           = array.array('f', [0.] )
        JetGenMatched_DeltaR_W_Wd2           = array.array('f', [0.] )
        JetGenMatched_DeltaR_Wd1_Wd2         = array.array('f', [0.] )
        JetGenMatched_DeltaR_Wd1_b           = array.array('f', [0.] )
        JetGenMatched_DeltaR_Wd2_b           = array.array('f', [0.] )
        JetGenMatched_DeltaR_jet_t           = array.array('f', [0.] )
        JetGenMatched_DeltaR_jet_W           = array.array('f', [0.] )
        JetGenMatched_DeltaR_jet_b           = array.array('f', [0.] )
        JetGenMatched_DeltaR_jet_Wd1         = array.array('f', [0.] )
        JetGenMatched_DeltaR_jet_Wd2         = array.array('f', [0.] )
        JetGenMatched_DeltaR_pup0_b          = array.array('f', [0.] )
        JetGenMatched_DeltaR_pup0_Wd1        = array.array('f', [0.] )
        JetGenMatched_DeltaR_pup0_Wd2        = array.array('f', [0.] )
        JetGenMatched_DeltaR_pup1_b          = array.array('f', [0.] )
        JetGenMatched_DeltaR_pup1_Wd1        = array.array('f', [0.] )
        JetGenMatched_DeltaR_pup1_Wd2        = array.array('f', [0.] )
        JetGenMatched_partonPt               = array.array('f', [0.] )
        JetGenMatched_partonEta              = array.array('f', [0.] )
        JetGenMatched_partonPhi              = array.array('f', [0.] )
        JetGenMatched_partonMass             = array.array('f', [0.] )
        JetGenMatched_partonID               = array.array('f', [0.] )
        JetGenMatched_DeltaRjetParton        = array.array('f', [0.] )
        SemiLeptMETpx                = array.array('f', [0.] )
        SemiLeptMETpy                = array.array('f', [0.] )
        SemiLeptMETpt                = array.array('f', [0.] )
        SemiLeptMETphi               = array.array('f', [0.] )
        SemiLeptMETsumET             = array.array('f', [0.] )
        SemiLeptNvtx                 = array.array('f', [0.] )
        SemiLeptNPUtrue              = array.array('f', [0.] )
        SemiLeptRho                  = array.array('f', [0.] )
        SemiLeptEventWeight          = array.array('f', [0.] )
        SemiLeptPUweight     = array.array('f', [0.] )
        SemiLeptPUweight_MBup= array.array('f', [0.] )
        SemiLeptPUweight_MBdn= array.array('f', [0.] )


        SemiLeptGenTTmass            = array.array('f', [0.] )

        HTlep                        = array.array('f', [0.] )
        ST                           = array.array('f', [0.] )                
        ST_CorrDn                    = array.array('f', [0.] )                
        ST_CorrUp                    = array.array('f', [0.] )                
        ST_PtSmearNom                = array.array('f', [0.] )                
        ST_PtSmearUp                 = array.array('f', [0.] )                
        ST_PtSmearDn                 = array.array('f', [0.] )   

        SemiLeptQ2weight_CorrDn              = array.array('f', [0.] )
        SemiLeptQ2weight_CorrUp              = array.array('f', [0.] )
        SemiLeptNNPDF3weight_CorrDn          = array.array('f', [0.] )
        SemiLeptNNPDF3weight_CorrUp          = array.array('f', [0.] )
        SemiLeptRunNum               = array.array('f', [0.] )
        SemiLeptLumiBlock            = array.array('f', [0.] )
        SemiLeptEventNum             = array.array('f', [0.] )
        SemiLeptPassMETFilters               = array.array('f', [0.] )       

        AK4dRminPt                   = array.array('f', [0.] )
        AK4dRminEta                  = array.array('f', [0.] )
        AK4dRminPhi                  = array.array('f', [0.] )
        AK4dRminMass                 = array.array('f', [0.] )
        AK4dRminBdisc                = array.array('f', [0.] )
        AK4dRminLep                  = array.array('f', [0.] )
        AK4BtagdRminPt               = array.array('f', [0.] )
        AK4BtagdRminBdisc            = array.array('f', [0.] )
        AK4BtagdRminLep              = array.array('f', [0.] )
        LepHemiContainsAK4BtagLoose          = array.array('f', [0.] )
        LepHemiContainsAK4BtagMedium         = array.array('f', [0.] )
        LepHemiContainsAK4BtagTight          = array.array('f', [0.] )


        LeptonPhi                    = array.array('f', [0.] )
        LeptonPt                     = array.array('f', [0.] )
        LeptonEta                    = array.array('f', [0.] )
        LeptonMass                   = array.array('f', [0.] )
        PtRel                        = array.array('f', [0.] )
        LeptonIsMu                   = array.array('f', [0.] )
        MuTight                      = array.array('f', [0.] )
        MuMedium                     = array.array('f', [0.] )
        DeltaRJetLep                 = array.array('f', [0.] ) 
        DeltaPhiJetLep               = array.array('f', [0.] ) 
        MuIso                        = array.array('f', [0.] )
        Elecron_absiso               = array.array('f', [0.] )
        Elecron_relIsoWithDBeta      = array.array('f', [0.] )
        Elecron_absiso_EA            = array.array('f', [0.] )
        Elecron_relIsoWithEA         = array.array('f', [0.] )


        t.SetBranchAddress('JetPtRaw', JetPtRaw)   
        t.SetBranchAddress('JetEtaRaw', JetEtaRaw)      
        t.SetBranchAddress('JetPhiRaw',  JetPhiRaw    )
        t.SetBranchAddress('JetMassRaw', JetMassRaw     )
        t.SetBranchAddress('JetP',  JetP    )
        t.SetBranchAddress('JetPt', JetPt     )
        t.SetBranchAddress('JetEta',   JetEta   )
        t.SetBranchAddress('JetPhi',  JetPhi    )
        t.SetBranchAddress('JetMass', JetMass     )
        t.SetBranchAddress('JetSDmass',  JetSDmass    )
        t.SetBranchAddress('JetSDmassRaw',  JetSDmassRaw    )
        t.SetBranchAddress('JetSDptRaw',    JetSDptRaw  )
        t.SetBranchAddress('JetSDetaRaw',  JetSDetaRaw    )
        t.SetBranchAddress('JetSDphiRaw',   JetSDphiRaw   )
        #t.SetBranchAddress('JetMassPruned              ',      )
        #t.SetBranchAddress('JetMassTrimmed             ',      )
        t.SetBranchAddress('JetTau32',   JetTau32   )
        t.SetBranchAddress('JetTau21',   JetTau21   )
        '''
        t.SetBranchAddress('JetSDsubjet0bdisc', JetSDsubjet0bdisc     )
        t.SetBranchAddress('JetSDsubjet1bdisc',  JetSDsubjet1bdisc    )
        t.SetBranchAddress('JetSDmaxbdisc', JetSDmaxbdisc     )
        #t.SetBranchAddress('JetSDmaxbdiscflavHadron    ',      )
        #t.SetBranchAddress('JetSDmaxbdiscflavParton    ',      )
        t.SetBranchAddress('JetSDsubjet0pt', JetSDsubjet0pt     )
        t.SetBranchAddress('JetSDsubjet0mass', 1     )
        t.SetBranchAddress('JetSDsubjet0eta',  1     )
        t.SetBranchAddress('JetSDsubjet0phi',  1     )
        #t.SetBranchAddress('JetSDsubjet0area           ',      )
        #t.SetBranchAddress('JetSDsubjet0flavHadron     ',      )
        #t.SetBranchAddress('JetSDsubjet0flavParton     ',      )
        t.SetBranchAddress('JetSDsubjet0tau1',  1    )
        t.SetBranchAddress('JetSDsubjet0tau2',  1    )
        t.SetBranchAddress('JetSDsubjet0tau3',  1    )
        t.SetBranchAddress('JetSDsubjet1pt',    1    )
        t.SetBranchAddress('JetSDsubjet1mass',  JetSDsubjet1mass    )
        t.SetBranchAddress('JetSDsubjet1eta',   JetSDsubjet1eta    )
        t.SetBranchAddress('JetSDsubjet1phi',  JetSDsubjet1phi    )
        #t.SetBranchAddress('JetSDsubjet1area           ',      )
        #t.SetBranchAddress('JetSDsubjet1flavHadron              ',      )
        #t.SetBranchAddress('JetSDsubjet1flavParton              ',      )
        t.SetBranchAddress('JetSDsubjet1tau1',    JetSDsubjet1tau1  )
        t.SetBranchAddress('JetSDsubjet1tau2',    JetSDsubjet1tau2   )
        t.SetBranchAddress('JetSDsubjet1tau3',   JetSDsubjet1tau3   )
        #t.SetBranchAddress('JetPuppiP                  ',      )
        '''    
        t.SetBranchAddress('JetPuppiPt',  JetPuppiPt   )
        t.SetBranchAddress('JetPuppiEta',  JetPuppiEta   )
        t.SetBranchAddress('JetPuppiPhi',  JetPuppiPhi    )
        t.SetBranchAddress('JetPuppiMass',  JetPuppiMass    )

        t.SetBranchAddress('JetPuppiSDmass', JetPuppiSDmass    )
        t.SetBranchAddress('JetPuppiSDmassCorr',  JetPuppiSDmassCorr    )
        #t.SetBranchAddress('JetPuppiSDmassCorrUp       ',      )
        #t.SetBranchAddress('JetPuppiSDmassCorrDn       ',      )
        #t.SetBranchAddress('JetPuppiSDmassCorrL23Smear         ',      )
        #t.SetBranchAddress('JetPuppiSDmassCorrL23SmearUp       ',      )
        #t.SetBranchAddress('JetPuppiSDmassCorrL23SmearDn       ',      )
        
        t.SetBranchAddress('JetPuppiSDpt',   JetPuppiSDpt  )
        t.SetBranchAddress('JetPuppiSDptCorr', JetPuppiSDptCorr     )
        #t.SetBranchAddress('JetPuppiSDptCorrUp         ',      )
        #t.SetBranchAddress('JetPuppiSDptCorrDn         ',      )
        #t.SetBranchAddress('JetPuppiSDptCorrL23Smear           ',      )
        #t.SetBranchAddress('JetPuppiSDptCorrL23SmearUp         ',      )
        #t.SetBranchAddress('JetPuppiSDptCorrL23SmearDn         ',      )
        t.SetBranchAddress('JetPuppiSDeta',   JetPuppiSDeta   )
        t.SetBranchAddress('JetPuppiSDphi',   JetPuppiSDphi   )
        t.SetBranchAddress('JetPuppiTau1', JetPuppiTau1     )
        t.SetBranchAddress('JetPuppiTau2', JetPuppiTau2     )
        t.SetBranchAddress('JetPuppiTau3',  JetPuppiTau3    )
        #t.SetBranchAddress('JetPuppiTau4               ',      )
        t.SetBranchAddress('JetPuppiTau32', JetPuppiTau32     )
        t.SetBranchAddress('JetPuppiTau21', JetPuppiTau21      )
        '''
        t.SetBranchAddress('JetPuppiSDsubjet0bdisc             ',      )
        t.SetBranchAddress('JetPuppiSDsubjet1bdisc             ',      )
        t.SetBranchAddress('JetPuppiSDmaxbdisc         ',      )
        t.SetBranchAddress('JetPuppiSDmaxbdiscflavHadron       ',      )
        t.SetBranchAddress('JetPuppiSDmaxbdiscflavParton       ',      )
        t.SetBranchAddress('JetPuppiSDsubjet0pt        ',      )
        t.SetBranchAddress('JetPuppiSDsubjet0mass              ',      )
        t.SetBranchAddress('JetPuppiSDsubjet0eta       ',      )
        t.SetBranchAddress('JetPuppiSDsubjet0phi       ',      )
        t.SetBranchAddress('JetPuppiSDsubjet0area              ',      )
        t.SetBranchAddress('JetPuppiSDsubjet0flavHadron        ',      )
        t.SetBranchAddress('JetPuppiSDsubjet0flavParton        ',      )
        t.SetBranchAddress('JetPuppiSDsubjet0tau1              ',      )
        t.SetBranchAddress('JetPuppiSDsubjet0tau2              ',      )
        t.SetBranchAddress('JetPuppiSDsubjet0tau3              ',      )
        t.SetBranchAddress('JetPuppiSDsubjet1pt        ',      )
        t.SetBranchAddress('JetPuppiSDsubjet1mass              ',      )
        t.SetBranchAddress('JetPuppiSDsubjet1eta       ',      )
        t.SetBranchAddress('JetPuppiSDsubjet1phi       ',      )
        t.SetBranchAddress('JetPuppiSDsubjet1area              ',      )
        t.SetBranchAddress('JetPuppiSDsubjet1flavHadron        ',      )
        t.SetBranchAddress('JetPuppiSDsubjet1flavParton        ',      )
        t.SetBranchAddress('JetPuppiSDsubjet1tau1              ',      )
        t.SetBranchAddress('JetPuppiSDsubjet1tau2              ',      )
        t.SetBranchAddress('JetPuppiSDsubjet1tau3              ',      )
        
        t.SetBranchAddress('JetCHF                     ',      )
        t.SetBranchAddress('JetNHF                     ',      )
        t.SetBranchAddress('JetCM                      ',      )
        t.SetBranchAddress('JetNM                      ',      )
        t.SetBranchAddress('JetNEF                     ',      )
        t.SetBranchAddress('JetCEF                     ',      )
        t.SetBranchAddress('JetMF                      ',      )
        t.SetBranchAddress('JetMult                    ',      )
        t.SetBranchAddress('JetPuppiCHF                ',      )
        t.SetBranchAddress('JetPuppiNHF                ',      )
        t.SetBranchAddress('JetPuppiCM                 ',      )
        t.SetBranchAddress('JetPuppiNM                 ',      )
        t.SetBranchAddress('JetPuppiNEF                ',      )
        t.SetBranchAddress('JetPuppiCEF                ',      )
        t.SetBranchAddress('JetPuppiMF                 ',      )
        t.SetBranchAddress('JetPuppiMult               ',      )
        t.SetBranchAddress('JetMassCorrFactor          ',      )
        t.SetBranchAddress('JetMassCorrFactorUp        ',      )
        t.SetBranchAddress('JetMassCorrFactorDn        ',      )
        #t.SetBranchAddress('JetCorrFactor              ',      )
        #t.SetBranchAddress('JetCorrFactorUp            ',      )
        #t.SetBranchAddress('JetCorrFactorDn            ',      )
        #t.SetBranchAddress('JetPtSmearFactor           ',      )
        #t.SetBranchAddress('JetPtSmearFactorUp         ',      )
        #t.SetBranchAddress('JetPtSmearFactorDn         ',      )
        #t.SetBranchAddress('JetPuppiMassCorrFactor             ',      )
        #t.SetBranchAddress('JetPuppiMassCorrFactorUp           ',      )
        #t.SetBranchAddress('JetPuppiMassCorrFactorDn           ',      )
        #t.SetBranchAddress('JetPuppiCorrFactor         ',      )
        #t.SetBranchAddress('JetPuppiCorrFactorUp       ',      )
        #t.SetBranchAddress('JetPuppiCorrFactorDn       ',      )
        #t.SetBranchAddress('JetPuppiPtSmearFactor              ',      )
        #t.SetBranchAddress('JetPuppiPtSmearFactorUp            ',      )
        #t.SetBranchAddress('JetPuppiPtSmearFactorDn            ',      )
        #t.SetBranchAddress('JetEtaScaleFactor          ',      )
        #t.SetBranchAddress('JetPhiScaleFactor          ',      )
       
        t.SetBranchAddress('JetMatchedGenJetDR         ',      )
        t.SetBranchAddress('JetMatchedGenJetPt         ',      )
        t.SetBranchAddress('JetMatchedGenJetMass       ',      )
        t.SetBranchAddress('JetGenMatched_TopHadronic          ',      )
        t.SetBranchAddress('JetGenMatched_TopPt        ',      )
        t.SetBranchAddress('JetGenMatched_TopEta       ',      )
        t.SetBranchAddress('JetGenMatched_TopPhi       ',      )
        t.SetBranchAddress('JetGenMatched_TopMass              ',      )
        t.SetBranchAddress('JetGenMatched_bPt          ',      )
        t.SetBranchAddress('JetGenMatched_WPt          ',      )
        t.SetBranchAddress('JetGenMatched_Wd1Pt        ',      )
        t.SetBranchAddress('JetGenMatched_Wd2Pt        ',      )
        t.SetBranchAddress('JetGenMatched_Wd1ID        ',      )
        t.SetBranchAddress('JetGenMatched_Wd2ID        ',      )
        t.SetBranchAddress('JetGenMatched_MaxDeltaRPartonTop   ',      )
        t.SetBranchAddress('JetGenMatched_MaxDeltaRWPartonTop  ',      )
        t.SetBranchAddress('JetGenMatched_MaxDeltaRWPartonW    ',      )
        t.SetBranchAddress('JetGenMatched_DeltaR_t_b           ',      )
        t.SetBranchAddress('JetGenMatched_DeltaR_t_W           ',      )
        t.SetBranchAddress('JetGenMatched_DeltaR_t_Wd1         ',      )
        t.SetBranchAddress('JetGenMatched_DeltaR_t_Wd2         ',      )
        t.SetBranchAddress('JetGenMatched_DeltaR_W_b1          ',      )
        t.SetBranchAddress('JetGenMatched_DeltaR_W_Wd1         ',      )
        t.SetBranchAddress('JetGenMatched_DeltaR_W_Wd2         ',      )
        t.SetBranchAddress('JetGenMatched_DeltaR_Wd1_Wd2       ',      )
        t.SetBranchAddress('JetGenMatched_DeltaR_Wd1_b         ',      )
        t.SetBranchAddress('JetGenMatched_DeltaR_Wd2_b         ',      )
        t.SetBranchAddress('JetGenMatched_DeltaR_jet_t         ',      )
        t.SetBranchAddress('JetGenMatched_DeltaR_jet_W         ',      )
        t.SetBranchAddress('JetGenMatched_DeltaR_jet_b         ',      )
        t.SetBranchAddress('JetGenMatched_DeltaR_jet_Wd1       ',      )
        t.SetBranchAddress('JetGenMatched_DeltaR_jet_Wd2       ',      )
        t.SetBranchAddress('JetGenMatched_DeltaR_pup0_b        ',      )
        t.SetBranchAddress('JetGenMatched_DeltaR_pup0_Wd1      ',      )
        t.SetBranchAddress('JetGenMatched_DeltaR_pup0_Wd2      ',      )
        t.SetBranchAddress('JetGenMatched_DeltaR_pup1_b        ',      )
        t.SetBranchAddress('JetGenMatched_DeltaR_pup1_Wd1      ',      )
        t.SetBranchAddress('JetGenMatched_DeltaR_pup1_Wd2      ',      )
        t.SetBranchAddress('JetGenMatched_partonPt             ',      )
        t.SetBranchAddress('JetGenMatched_partonEta            ',      )
        t.SetBranchAddress('JetGenMatched_partonPhi            ',      )
        t.SetBranchAddress('JetGenMatched_partonMass           ',      )
        t.SetBranchAddress('JetGenMatched_partonID            ',      )
        t.SetBranchAddress('JetGenMatched_DeltaRjetParton      ',      )
        '''
        t.SetBranchAddress('SemiLeptMETpx',  SemiLeptMETpx  )
        t.SetBranchAddress('SemiLeptMETpy',  SemiLeptMETpy   )
        t.SetBranchAddress('SemiLeptMETpt',  SemiLeptMETpt   )
        t.SetBranchAddress('SemiLeptMETphi',  SemiLeptMETphi   )
        #t.SetBranchAddress('SemiLeptMETsumET',   )
        #t.SetBranchAddress('SemiLeptNvtx               ',      )
        #t.SetBranchAddress('SemiLeptNPUtrue            ',      )
        t.SetBranchAddress('SemiLeptRho',  SemiLeptRho   )
        t.SetBranchAddress('SemiLeptEventWeight',  SemiLeptEventWeight    )
        t.SetBranchAddress('SemiLeptPUweight', SemiLeptPUweight    )
        t.SetBranchAddress('SemiLeptPUweight_MBup',   SemiLeptPUweight_MBup   )
        t.SetBranchAddress('SemiLeptPUweight_MBdn', SemiLeptPUweight_MBdn  )


        #t.SetBranchAddress('SemiLeptGenTTmass          ',      )
        t.SetBranchAddress('HTlep',  HTlep  )
        t.SetBranchAddress('ST',   ST   )                
        #t.SetBranchAddress('ST_CorrDn                  ',      )                
        #t.SetBranchAddress('ST_CorrUp                    ',      )               
        #t.SetBranchAddress('ST_PtSmearNom                ',      )               
        #t.SetBranchAddress('ST_PtSmearUp                 ',      )               
        #t.SetBranchAddress('ST_PtSmearDn                 ',      )  

        #t.SetBranchAddress('SemiLeptQ2weight_CorrDn                 ',      ) 
        #t.SetBranchAddress('SemiLeptQ2weight_CorrUp               ',      ) 
        #t.SetBranchAddress('SemiLeptNNPDF3weight_CorrDn            ',      ) 
        #t.SetBranchAddress('SemiLeptNNPDF3weight_CorrUp            ',      ) 
        t.SetBranchAddress('SemiLeptRunNum',  SemiLeptRunNum  ) 
        t.SetBranchAddress('SemiLeptLumiBlock',  SemiLeptLumiBlock   ) 
        t.SetBranchAddress('SemiLeptEventNum',  SemiLeptEventNum    ) 
        #t.SetBranchAddress('SemiLeptPassMETFilters',   1   )      

        t.SetBranchAddress('AK4dRminPt',  AK4dRminPt   )
        t.SetBranchAddress('AK4dRminEta',  AK4dRminEta  )
        t.SetBranchAddress('AK4dRminPhi',  AK4dRminPhi  )
        t.SetBranchAddress('AK4dRminMass', AK4dRminMass )
        t.SetBranchAddress('AK4dRminBdisc', AK4dRminBdisc )
        t.SetBranchAddress('AK4dRminLep',   AK4dRminLep   )
        #t.SetBranchAddress('SemiBtagdRminPt', SemiBtagdRminPt  )
        #t.SetBranchAddress('SemiBtagdRminBdisc',  SemiBtagdRminBdisc   )
        #t.SetBranchAddress('AK4BtagdRminLep', AK4BtagdRminLep   )
        t.SetBranchAddress('LepHemiContainsAK4BtagLoose',  LepHemiContainsAK4BtagLoose   )
        t.SetBranchAddress('LepHemiContainsAK4BtagMedium', LepHemiContainsAK4BtagMedium   )
        t.SetBranchAddress('LepHemiContainsAK4BtagTight',  LepHemiContainsAK4BtagTight  )

        t.SetBranchAddress('LeptonPhi', LeptonPhi    )
        t.SetBranchAddress('LeptonPt',  LeptonPt  )
        t.SetBranchAddress('LeptonEta',  LeptonEta  )
        t.SetBranchAddress('LeptonMass',  LeptonMass  )
        t.SetBranchAddress('PtRel',   PtRel  )
        t.SetBranchAddress('LeptonIsMu', LeptonIsMu     )
        t.SetBranchAddress('MuTight',  MuTight  )
        #t.SetBranchAddress('MuMedium                   ',      )
        t.SetBranchAddress('DeltaRJetLep', DeltaRJetLep   ) 
        #t.SetBranchAddress('DeltaPhiJetLep             ',      ) 
        t.SetBranchAddress('MuIso',MuIso    )
        #t.SetBranchAddress('Semion_absiso             ',      )
        #t.SetBranchAddress('Semion_relIsoWithDBeta            ',      )
        #t.SetBranchAddress('Semion_absiso_EA          ',      )
        #t.SetBranchAddress('Semion_relIsoWithEA      ',      )


        t.SetBranchStatus('*', 0 )
        t.SetBranchStatus('JetPtRaw', 1)   
        t.SetBranchStatus('JetEtaRaw', 1)      
        t.SetBranchStatus('JetPhiRaw',  1 )
        t.SetBranchStatus('JetMassRaw', 1     )
        t.SetBranchStatus('JetP',  1    )
        t.SetBranchStatus('JetPt', 1     )
        t.SetBranchStatus('JetEta',   1   )
        t.SetBranchStatus('JetPhi',  1   )
        t.SetBranchStatus('JetMass', 1     )
        t.SetBranchStatus('JetSDmass',  1    )
        t.SetBranchStatus('JetSDmassRaw', 1   )
        t.SetBranchStatus('JetSDptRaw',    1 )
        t.SetBranchStatus('JetSDetaRaw',  1    )
        t.SetBranchStatus('JetSDphiRaw',   1   )
        #t.SetBranchStatus('JetMassPruned              ',      )
        #t.SetBranchStatus('JetMassTrimmed             ',      )
        t.SetBranchStatus('JetTau32',   1   )
        t.SetBranchStatus('JetTau21',   1   )
        t.SetBranchStatus('JetSDsubjet0bdisc', 1    )
        t.SetBranchStatus('JetSDsubjet1bdisc',  1    )
        t.SetBranchStatus('JetSDmaxbdisc', 1     )
        #t.SetBranchStatus('JetSDmaxbdiscflavHadron    ',      )
        #t.SetBranchStatus('JetSDmaxbdiscflavParton    ',      )
        t.SetBranchStatus('JetSDsubjet0pt', 1     )
        t.SetBranchStatus('JetSDsubjet0mass', 1     )
        t.SetBranchStatus('JetSDsubjet0eta',  1     )
        t.SetBranchStatus('JetSDsubjet0phi',  1     )
        #t.SetBranchStatus('JetSDsubjet0area           ',      )
        #t.SetBranchStatus('JetSDsubjet0flavHadron     ',      )
        #t.SetBranchStatus('JetSDsubjet0flavParton     ',      )
        t.SetBranchStatus('JetSDsubjet0tau1',  1    )
        t.SetBranchStatus('JetSDsubjet0tau2',  1    )
        t.SetBranchStatus('JetSDsubjet0tau3',  1    )
        t.SetBranchStatus('JetSDsubjet1pt',    1    )
        t.SetBranchStatus('JetSDsubjet1mass',  1    )
        t.SetBranchStatus('JetSDsubjet1eta',   1    )
        t.SetBranchStatus('JetSDsubjet1phi',   1    )
        #t.SetBranchStatus('JetSDsubjet1area           ',      )
        #t.SetBranchStatus('JetSDsubjet1flavHadron              ',      )
        #t.SetBranchStatus('JetSDsubjet1flavParton              ',      )
        t.SetBranchStatus('JetSDsubjet1tau1',    1   )
        t.SetBranchStatus('JetSDsubjet1tau2',    1   )
        t.SetBranchStatus('JetSDsubjet1tau3',    1   )
        #t.SetBranchStatus('JetPuppiP                  ',      )
        t.SetBranchStatus('JetPuppiPt',   1   )
        t.SetBranchStatus('JetPuppiEta',  1    )
        t.SetBranchStatus('JetPuppiPhi',  1    )
        t.SetBranchStatus('JetPuppiMass',  1    )
        t.SetBranchStatus('JetPuppiSDmass', 1     )
        t.SetBranchStatus('JetPuppiSDmassCorr',  1    )
        #t.SetBranchStatus('JetPuppiSDmassCorrUp       ',      )
        #t.SetBranchStatus('JetPuppiSDmassCorrDn       ',      )
        #t.SetBranchStatus('JetPuppiSDmassCorrL23Smear         ',      )
        #t.SetBranchStatus('JetPuppiSDmassCorrL23SmearUp       ',      )
        #t.SetBranchStatus('JetPuppiSDmassCorrL23SmearDn       ',      )
        t.SetBranchStatus('JetPuppiSDpt',    1  )
        t.SetBranchStatus('JetPuppiSDptCorr', 1     )
        ''' 
        t.SetBranchStatus('JetPuppiSDptCorrUp         ',      )
        t.SetBranchStatus('JetPuppiSDptCorrDn         ',      )
        t.SetBranchStatus('JetPuppiSDptCorrL23Smear           ',      )
        t.SetBranchStatus('JetPuppiSDptCorrL23SmearUp         ',      )
        t.SetBranchStatus('JetPuppiSDptCorrL23SmearDn         ',      )
        '''
        t.SetBranchStatus('JetPuppiSDeta',    1  )
        t.SetBranchStatus('JetPuppiSDphi',    1  )
        t.SetBranchStatus('JetPuppiTau1',     1  )
        t.SetBranchStatus('JetPuppiTau2',     1  )
        t.SetBranchStatus('JetPuppiTau3               ',      )
        #t.SetBranchStatus('JetPuppiTau4               ',      )
        t.SetBranchStatus('JetPuppiTau32',    1  )
        t.SetBranchStatus('JetPuppiTau21',    1  )
        '''
        t.SetBranchStatus('JetPuppiSDsubjet0bdisc             ',      )
        t.SetBranchStatus('JetPuppiSDsubjet1bdisc             ',      )
        t.SetBranchStatus('JetPuppiSDmaxbdisc         ',      )
        t.SetBranchStatus('JetPuppiSDmaxbdiscflavHadron       ',      )
        t.SetBranchStatus('JetPuppiSDmaxbdiscflavParton       ',      )
        t.SetBranchStatus('JetPuppiSDsubjet0pt        ',      )
        t.SetBranchStatus('JetPuppiSDsubjet0mass              ',      )
        t.SetBranchStatus('JetPuppiSDsubjet0eta       ',      )
        t.SetBranchStatus('JetPuppiSDsubjet0phi       ',      )
        t.SetBranchStatus('JetPuppiSDsubjet0area              ',      )
        t.SetBranchStatus('JetPuppiSDsubjet0flavHadron        ',      )
        t.SetBranchStatus('JetPuppiSDsubjet0flavParton        ',      )
        t.SetBranchStatus('JetPuppiSDsubjet0tau1              ',      )
        t.SetBranchStatus('JetPuppiSDsubjet0tau2              ',      )
        t.SetBranchStatus('JetPuppiSDsubjet0tau3              ',      )
        t.SetBranchStatus('JetPuppiSDsubjet1pt        ',      )
        t.SetBranchStatus('JetPuppiSDsubjet1mass              ',      )
        t.SetBranchStatus('JetPuppiSDsubjet1eta       ',      )
        t.SetBranchStatus('JetPuppiSDsubjet1phi       ',      )
        t.SetBranchStatus('JetPuppiSDsubjet1area              ',      )
        t.SetBranchStatus('JetPuppiSDsubjet1flavHadron        ',      )
        t.SetBranchStatus('JetPuppiSDsubjet1flavParton        ',      )
        t.SetBranchStatus('JetPuppiSDsubjet1tau1              ',      )
        t.SetBranchStatus('JetPuppiSDsubjet1tau2              ',      )
        t.SetBranchStatus('JetPuppiSDsubjet1tau3              ',      )
        
        t.SetBranchStatus('JetCHF                     ',      )
        t.SetBranchStatus('JetNHF                     ',      )
        t.SetBranchStatus('JetCM                      ',      )
        t.SetBranchStatus('JetNM                      ',      )
        t.SetBranchStatus('JetNEF                     ',      )
        t.SetBranchStatus('JetCEF                     ',      )
        t.SetBranchStatus('JetMF                      ',      )
        t.SetBranchStatus('JetMult                    ',      )
        t.SetBranchStatus('JetPuppiCHF                ',      )
        t.SetBranchStatus('JetPuppiNHF                ',      )
        t.SetBranchStatus('JetPuppiCM                 ',      )
        t.SetBranchStatus('JetPuppiNM                 ',      )
        t.SetBranchStatus('JetPuppiNEF                ',      )
        t.SetBranchStatus('JetPuppiCEF                ',      )
        t.SetBranchStatus('JetPuppiMF                 ',      )
        t.SetBranchStatus('JetPuppiMult               ',      )
        t.SetBranchStatus('JetMassCorrFactor          ',      )
        t.SetBranchStatus('JetMassCorrFactorUp        ',      )
        t.SetBranchStatus('JetMassCorrFactorDn        ',      )
        #t.SetBranchStatus('JetCorrFactor              ',      )
        #t.SetBranchStatus('JetCorrFactorUp            ',      )
        #t.SetBranchStatus('JetCorrFactorDn            ',      )
        #t.SetBranchStatus('JetPtSmearFactor           ',      )
        #t.SetBranchStatus('JetPtSmearFactorUp         ',      )
        #t.SetBranchStatus('JetPtSmearFactorDn         ',      )
        #t.SetBranchStatus('JetPuppiMassCorrFactor             ',      )
        #t.SetBranchStatus('JetPuppiMassCorrFactorUp           ',      )
        #t.SetBranchStatus('JetPuppiMassCorrFactorDn           ',      )
        #t.SetBranchStatus('JetPuppiCorrFactor         ',      )
        #t.SetBranchStatus('JetPuppiCorrFactorUp       ',      )
        #t.SetBranchStatus('JetPuppiCorrFactorDn       ',      )
        #t.SetBranchStatus('JetPuppiPtSmearFactor              ',      )
        #t.SetBranchStatus('JetPuppiPtSmearFactorUp            ',      )
        #t.SetBranchStatus('JetPuppiPtSmearFactorDn            ',      )
        #t.SetBranchStatus('JetEtaScaleFactor          ',      )
        #t.SetBranchStatus('JetPhiScaleFactor          ',      )
       
        t.SetBranchStatus('JetMatchedGenJetDR         ',      )
        t.SetBranchStatus('JetMatchedGenJetPt         ',      )
        t.SetBranchStatus('JetMatchedGenJetMass       ',      )
        t.SetBranchStatus('JetGenMatched_TopHadronic          ',      )
        t.SetBranchStatus('JetGenMatched_TopPt        ',      )
        t.SetBranchStatus('JetGenMatched_TopEta       ',      )
        t.SetBranchStatus('JetGenMatched_TopPhi       ',      )
        t.SetBranchStatus('JetGenMatched_TopMass              ',      )
        t.SetBranchStatus('JetGenMatched_bPt          ',      )
        t.SetBranchStatus('JetGenMatched_WPt          ',      )
        t.SetBranchStatus('JetGenMatched_Wd1Pt        ',      )
        t.SetBranchStatus('JetGenMatched_Wd2Pt        ',      )
        t.SetBranchStatus('JetGenMatched_Wd1ID        ',      )
        t.SetBranchStatus('JetGenMatched_Wd2ID        ',      )
        t.SetBranchStatus('JetGenMatched_MaxDeltaRPartonTop   ',      )
        t.SetBranchStatus('JetGenMatched_MaxDeltaRWPartonTop  ',      )
        t.SetBranchStatus('JetGenMatched_MaxDeltaRWPartonW    ',      )
        t.SetBranchStatus('JetGenMatched_DeltaR_t_b           ',      )
        t.SetBranchStatus('JetGenMatched_DeltaR_t_W           ',      )
        t.SetBranchStatus('JetGenMatched_DeltaR_t_Wd1         ',      )
        t.SetBranchStatus('JetGenMatched_DeltaR_t_Wd2         ',      )
        t.SetBranchStatus('JetGenMatched_DeltaR_W_b1          ',      )
        t.SetBranchStatus('JetGenMatched_DeltaR_W_Wd1         ',      )
        t.SetBranchStatus('JetGenMatched_DeltaR_W_Wd2         ',      )
        t.SetBranchStatus('JetGenMatched_DeltaR_Wd1_Wd2       ',      )
        t.SetBranchStatus('JetGenMatched_DeltaR_Wd1_b         ',      )
        t.SetBranchStatus('JetGenMatched_DeltaR_Wd2_b         ',      )
        t.SetBranchStatus('JetGenMatched_DeltaR_jet_t         ',      )
        t.SetBranchStatus('JetGenMatched_DeltaR_jet_W         ',      )
        t.SetBranchStatus('JetGenMatched_DeltaR_jet_b         ',      )
        t.SetBranchStatus('JetGenMatched_DeltaR_jet_Wd1       ',      )
        t.SetBranchStatus('JetGenMatched_DeltaR_jet_Wd2       ',      )
        t.SetBranchStatus('JetGenMatched_DeltaR_pup0_b        ',      )
        t.SetBranchStatus('JetGenMatched_DeltaR_pup0_Wd1      ',      )
        t.SetBranchStatus('JetGenMatched_DeltaR_pup0_Wd2      ',      )
        t.SetBranchStatus('JetGenMatched_DeltaR_pup1_b        ',      )
        t.SetBranchStatus('JetGenMatched_DeltaR_pup1_Wd1      ',      )
        t.SetBranchStatus('JetGenMatched_DeltaR_pup1_Wd2      ',      )
        t.SetBranchStatus('JetGenMatched_partonPt             ',      )
        t.SetBranchStatus('JetGenMatched_partonEta            ',      )
        t.SetBranchStatus('JetGenMatched_partonPhi            ',      )
        t.SetBranchStatus('JetGenMatched_partonMass           ',      )
        t.SetBranchStatus('JetGenMatched_partonID            ',      )
        t.SetBranchStatus('JetGenMatched_DeltaRjetParton      ',      )
        '''
        t.SetBranchStatus('SemiLeptMETpx',   1   )
        t.SetBranchStatus('SemiLeptMETpy',   1   )
        t.SetBranchStatus('SemiLeptMETpt',   1   )
        t.SetBranchStatus('SemiLeptMETphi',  1   )
        #t.SetBranchStatus('SemiLeptMETsumET',   )
        #t.SetBranchStatus('SemiLeptNvtx               ',      )
        #t.SetBranchStatus('SemiLeptNPUtrue            ',      )
        t.SetBranchStatus('SemiLeptRho',   1   )
        t.SetBranchStatus('SemiLeptEventWeight',  1    )
        t.SetBranchStatus('SemiLeptPUweight',  1    )
        t.SetBranchStatus('SemiLeptPUweight_MBup',   1   )
        t.SetBranchStatus('SemiLeptPUweight_MBdn',   1   )


        #t.SetBranchStatus('SemiLeptGenTTmass          ',      )
        t.SetBranchStatus('HTlep',   1   )
        t.SetBranchStatus('ST',   1   )                
        #t.SetBranchStatus('ST_CorrDn                  ',      )                
        #t.SetBranchStatus('ST_CorrUp                    ',      )               
        #t.SetBranchStatus('ST_PtSmearNom                ',      )               
        #t.SetBranchStatus('ST_PtSmearUp                 ',      )               
        #t.SetBranchStatus('ST_PtSmearDn                 ',      )  

        #t.SetBranchStatus('SemiLeptQ2weight_CorrDn                 ',      ) 
        #t.SetBranchStatus('SemiLeptQ2weight_CorrUp               ',      ) 
        #t.SetBranchStatus('SemiLeptNNPDF3weight_CorrDn            ',      ) 
        #t.SetBranchStatus('SemiLeptNNPDF3weight_CorrUp            ',      ) 
        t.SetBranchStatus('SemiLeptRunNum',   1   ) 
        t.SetBranchStatus('SemiLeptLumiBlock',   1   ) 
        t.SetBranchStatus('SemiLeptEventNum',  1    ) 
        #t.SetBranchStatus('SemiLeptPassMETFilters',   1   )      

        t.SetBranchStatus('AK4dRminPt', 1      )
        t.SetBranchStatus('AK4dRminEta', 1     )
        t.SetBranchStatus('AK4dRminPhi', 1     )
        t.SetBranchStatus('AK4dRminMass', 1    )
        t.SetBranchStatus('AK4dRminBdisc', 1   )
        t.SetBranchStatus('AK4dRminLep',   1   )
        t.SetBranchStatus('SemiBtagdRminPt',  1    )
        t.SetBranchStatus('SemiBtagdRminBdisc',   1   )
        t.SetBranchStatus('AK4BtagdRminLep',   1   )
        t.SetBranchStatus('LepHemiContainsAK4BtagLoose',  1   )
        t.SetBranchStatus('LepHemiContainsAK4BtagMedium', 1   )
        t.SetBranchStatus('LepHemiContainsAK4BtagTight',  1 )

        t.SetBranchStatus('LeptonPhi', 1     )
        t.SetBranchStatus('LeptonPt',   1   )
        t.SetBranchStatus('LeptonEta',   1   )
        t.SetBranchStatus('LeptonMass',   1   )
        t.SetBranchStatus('PtRel',    1  )
        t.SetBranchStatus('LeptonIsMu', 1      )
        t.SetBranchStatus('MuTight',   1   )
        #t.SetBranchStatus('MuMedium                   ',      )
        t.SetBranchStatus('DeltaRJetLep',  1    ) 
        #t.SetBranchStatus('DeltaPhiJetLep             ',      ) 
        t.SetBranchStatus('MuIso', 1     )
        #t.SetBranchStatus('Semion_absiso             ',      )
        #t.SetBranchStatus('Semion_relIsoWithDBeta            ',      )
        #t.SetBranchStatus('Semion_absiso_EA          ',      )
        #t.SetBranchStatus('Semion_relIsoWithEA      ',      )


    if not options.b2gtree :

        SemiLeptTrig        = array.array('i', [0]  )
        SemiLeptWeight      = array.array('f', [0.] )
        BoosttypE           = array.array('i', [0] )
        FatJetCorr          = array.array('f', [0.] )
        FatJetCorrUp        = array.array('f', [0.] )
        FatJetCorrDn        = array.array('f', [0.] )
        FatJetMassCorr      = array.array('f', [0.] )
        FatJetMassCorrUp    = array.array('f', [0.] )
        FatJetMassCorrDn    = array.array('f', [0.] )
        JetPtSmearFactor    = array.array('f', [0.] )
        JetPtSmearFactorUp  = array.array('f', [0.] )
        JetPtSmearFactorDn  = array.array('f', [0.] )
        JetEtaScaleFactor   = array.array('f', [0.] )
        JetPhiScaleFactor   = array.array('f', [0.] )
        JetMatchedGenJetPt  = array.array('f', [0.] )
        FatJetPtRaw         = array.array('f', [0.] )
        FatJetEtaRaw        = array.array('f', [0.] )  
        FatJetPhiRaw        = array.array('f', [0.] )
        FatJetRapRaw        = array.array('f', [0.] )
        FatJetMassRaw       = array.array('f', [0.] )
        FatJetP             = array.array('f', [0.] )
        FatJetPt            = array.array('f', [-1.])
        FatJetEta           = array.array('f', [-1.])
        FatJetPhi           = array.array('f', [-1.])
        FatJetRap           = array.array('f', [-1.])
        FatJetEnergy        = array.array('f', [-1.])
        FatJetBDisc         = array.array('f', [-1.])
        FatJetRhoRatio      = array.array('f', [-1.])
        FatJetMass          = array.array('f', [-1.])
        FatJetMassSoftDrop  = array.array('f', [-1.])
        FatJetMassSDsumSubjetCorr        = array.array('f', [-1.])
        FatJetMassSDsumSubjetRaw         = array.array('f', [-1.])
        FatJetMassSDsumSubjetCorrUp      = array.array('f', [-1.])
        FatJetMassSDsumSubjetCorrDn      = array.array('f', [-1.])
        FatJetMassSDsumSubjetCorrSmear   = array.array('f', [-1.])
        FatJetMassSDsumSubjetCorrSmearUp = array.array('f', [-1.])
        FatJetMassSDsumSubjetCorrSmearDn = array.array('f', [-1.])
        FatJetMassPruned    = array.array('f', [-1.])
        FatJetMassFiltered  = array.array('f', [-1.])       
        FatJetMassTrimmed   = array.array('f', [-1.])
        FatJetTau1          = array.array('f', [-1.])
        FatJetTau2          = array.array('f', [-1.])
        FatJetTau3          = array.array('f', [-1.])
        FatJetTau32         = array.array('f', [-1.])
        FatJetTau21         = array.array('f', [-1.]) 
        FatJetSDnsubjets    = array.array('f', [-1.])
        FatJetSDmaxbdisc    = array.array('f', [-1.])
        FatJetSDsubjetWpt   = array.array('f', [-1.])
        FatJetSDsubjetWEta   = array.array('f', [-1.])
        FatJetSDsubjetWPhi   = array.array('f', [-1.])
        FatJetSDsubjetWmass = array.array('f', [-1.])
        FatJetSDsubjetWtau1   = array.array('f', [-1.])
        FatJetSDsubjetWtau2   = array.array('f', [-1.])
        FatJetSDsubjetWtau3   = array.array('f', [-1.])
        FatJetSDsubjetWtau21   = array.array('f', [-1.])
        FatJetSDsubjetWtau32   = array.array('f', [-1.])
        FatJetSDbdiscW      = array.array('f', [-1.])
        FatJetSDsubjetBpt   = array.array('f', [-1.])
        FatJetSDsubjetBmass = array.array('f', [-1.])
        FatJetSDsubjetBtau1   = array.array('f', [-1.])
        FatJetSDsubjetBtau2   = array.array('f', [-1.])
        FatJetSDsubjetBtau3   = array.array('f', [-1.])
        FatJetSDsubjetBtau21   = array.array('f', [-1.])
        FatJetSDsubjetBtau32   = array.array('f', [-1.])
        FatJetSDbdiscB      = array.array('f', [-1.])
        FatJetCMSmaxbdisc   = array.array('f', [-1.])
        FatJetCMSnsubjets   = array.array('f', [-1.])
        FatJetCMSminMass    = array.array('f', [-1.])
        FatJetCMSm01        = array.array('f', [-1.])
        FatJetCMSm02        = array.array('f', [-1.])
        FatJetCMSm12        = array.array('f', [-1.])
        FatJetNHF           = array.array('f', [-1.])
        FatJetCHF           = array.array('f', [-1.])
        FatJetNEF           = array.array('f', [-1.])
        FatJetCEF           = array.array('f', [-1.])
        FatJetNC            = array.array('f', [-1.])
        FatJetNCH           = array.array('f', [-1.])
        BJetbDisc           = array.array('f', [-1.])
        BJetPt              = array.array('f', [-1.])
        BJetEta             = array.array('f', [-1.])
        BJetPhi             = array.array('f', [-1.])
        BJetMass            = array.array('f', [-1.])
        BJet2bDisc           = array.array('f', [-1.])
        BJet2Pt              = array.array('f', [-1.])
        BJet2Eta             = array.array('f', [-1.])
        BJet2Phi             = array.array('f', [-1.])
        BJet2Mass            = array.array('f', [-1.])
        Type2PairMass       = array.array('f', [-1.])
        Type2PairPt         = array.array('f', [-1.])
        LeptonType          = array.array('i', [-1])
        LeptonPt            = array.array('f', [-1.])
        LeptonEta           = array.array('f', [-1.])
        LeptonPhi           = array.array('f', [-1.])
        LeptonPx            = array.array('f', [-1.])
        LeptonPy            = array.array('f', [-1.])
        LeptonPz            = array.array('f', [-1.])
        LeptonEnergy        = array.array('f', [-1.])
        LeptonIso           = array.array('f', [-1.])
        LeptonPtRel         = array.array('f', [-1.])
        LeptonDRMin         = array.array('f', [-1.])
        LeptonCharge        = array.array('f', [-1.])
        LeptonHEEPEl        = array.array('f', [-1.])
        LeptonCutIDLooseEl  = array.array('f', [-1.])
        LeptonHighPtMu      = array.array('f', [-1.])
        LeptonLoose         = array.array('f', [-1.])
        LeptonTight         = array.array('f', [-1.]) 
        SemiLepMETpx        = array.array('f', [-1.])
        SemiLepMETpy        = array.array('f', [-1.])
        SemiLepMETpt        = array.array('f', [-1.])
        SemiLepMETphi       = array.array('f', [-1.])
        SemiLepNvtx         = array.array('f', [-1.])
        SemiLepEventWeight  = array.array('f', [-1.])
        SemilLepTTmass      = array.array('f', [-1.])  
        DeltaPhiLepFat      = array.array('f', [-1.]) 
        DeltaRLepFat        = array.array('f', [-1.])
        DeltaRAK4AK8        = array.array('f', [-1.])
        NearestAK4JetPt     = array.array('f', [-1.])
        AK4bDisc            = array.array('f', [-1.])
        NearestAK4JetPt     = array.array('f', [-1.])
        NearestAK4JetEta    = array.array('f', [-1.])
        NearestAK4JetPhi    = array.array('f', [-1.])
        NearestAK4JetMass   = array.array('f', [-1.])
        NearestAK4JetPt2     = array.array('f', [-1.])
        NearestAK4JetEta2    = array.array('f', [-1.])
        NearestAK4JetPhi2    = array.array('f', [-1.])
        NearestAK4JetMass2   = array.array('f', [-1.])
        SemiLeptRunNum      = array.array('f', [-1.])  
        SemiLeptLumiBlock   = array.array('f', [-1.])  
        SemiLeptEventNum    = array.array('f', [-1.])
        SemiLeptEventNum2    = array.array('f', [-1.])  
        PU_CorrDn           = array.array('f', [-1.])
        PU_CorrUp           = array.array('f', [-1.])


        t.SetBranchAddress('SemiLeptTrig'        , SemiLeptTrig        )
        t.SetBranchAddress('SemiLeptWeight'      , SemiLeptWeight      )
        t.SetBranchAddress('FatJetPt'            , FatJetPt            )
        t.SetBranchAddress('FatJetEta'           , FatJetEta           )
        t.SetBranchAddress('FatJetPhi'           , FatJetPhi           )
        t.SetBranchAddress('FatJetRap'           , FatJetRap           )
        t.SetBranchAddress('FatJetEnergy'        , FatJetEnergy        )
        t.SetBranchAddress('FatJetBDisc'         , FatJetBDisc         )
        t.SetBranchAddress('FatJetMass'          , FatJetMass          )
        t.SetBranchAddress('FatJetMassSoftDrop'  , FatJetMassSoftDrop  )
        t.SetBranchAddress('FatJetTau32'         , FatJetTau32         )
        t.SetBranchAddress('FatJetTau21'         , FatJetTau21         )
        t.SetBranchAddress('FatJetRhoRatio'      , FatJetRhoRatio      )
        t.SetBranchAddress('FatJetSDbdiscW'      , FatJetSDbdiscW      )
        t.SetBranchAddress('FatJetSDbdiscB'      , FatJetSDbdiscB      )
        t.SetBranchAddress('FatJetSDsubjetWpt'   , FatJetSDsubjetWpt   )
        t.SetBranchAddress('FatJetSDsubjetWEta'   , FatJetSDsubjetWEta )
        t.SetBranchAddress('FatJetSDsubjetWPhi'   , FatJetSDsubjetWPhi )
        t.SetBranchAddress('FatJetSDsubjetWmass' , FatJetSDsubjetWmass )
        t.SetBranchAddress('FatJetSDsubjetWtau1' , FatJetSDsubjetWtau1 )
        t.SetBranchAddress('FatJetSDsubjetWtau2' , FatJetSDsubjetWtau2 )
        t.SetBranchAddress('FatJetSDsubjetWtau3' , FatJetSDsubjetWtau3 )
        t.SetBranchAddress('FatJetSDsubjetWtau21' , FatJetSDsubjetWtau21 )
        t.SetBranchAddress('FatJetSDsubjetWtau32' , FatJetSDsubjetWtau32 )
        t.SetBranchAddress('FatJetSDsubjetBpt'   , FatJetSDsubjetBpt   )
        t.SetBranchAddress('FatJetSDsubjetBmass' , FatJetSDsubjetBmass )
        t.SetBranchAddress('FatJetSDsubjetBtau1' , FatJetSDsubjetBtau1 )
        t.SetBranchAddress('FatJetSDsubjetBtau2' , FatJetSDsubjetBtau2 )
        t.SetBranchAddress('FatJetSDsubjetBtau32' , FatJetSDsubjetBtau32 )
        t.SetBranchAddress('FatJetSDsubjetBtau21' , FatJetSDsubjetBtau21 )
        t.SetBranchAddress('FatJetSDsubjetBtau3' , FatJetSDsubjetBtau3 )
        t.SetBranchAddress('BJet2bDisc'   , BJet2bDisc )
        t.SetBranchAddress('BJet2Pt'      , BJet2Pt    )
        t.SetBranchAddress('BJet2Eta'     , BJet2Eta   )
        t.SetBranchAddress('BJet2Phi'     , BJet2Phi   )
        t.SetBranchAddress('BJet2Mass'    , BJet2Mass  )
        t.SetBranchAddress('LeptonType'          , LeptonType          )
        t.SetBranchAddress('LeptonPt'            , LeptonPt            )
        t.SetBranchAddress('LeptonEta'           , LeptonEta           )
        t.SetBranchAddress('LeptonPhi'           , LeptonPhi           )
        t.SetBranchAddress('LeptonEnergy'        , LeptonEnergy        )
        t.SetBranchAddress('LeptonIso'           , LeptonIso           )
        t.SetBranchAddress('LeptonPtRel'         , LeptonPtRel         )
        t.SetBranchAddress('LeptonDRMin'         , LeptonDRMin         )
        t.SetBranchAddress('LeptonCharge'        , LeptonCharge        )
        t.SetBranchAddress('LeptonHEEPEl'        , LeptonHEEPEl         )
        t.SetBranchAddress('LeptonCutIDLooseEl'  , LeptonCutIDLooseEl   )
        t.SetBranchAddress('LeptonHighPtMu'      , LeptonHighPtMu       ) 
        t.SetBranchAddress('LeptonLoose'         , LeptonLoose         )
        t.SetBranchAddress('LeptonTight'         , LeptonTight         )
        t.SetBranchAddress('SemiLepMETpt'        , SemiLepMETpt        )
        t.SetBranchAddress('SemiLepMETpx'        , SemiLepMETpx        )
        t.SetBranchAddress('SemiLepMETpy'        , SemiLepMETpy        )
        t.SetBranchAddress('AK4bDisc'            , AK4bDisc            )
        t.SetBranchAddress('SemiLepMETphi'       , SemiLepMETphi       )
        t.SetBranchAddress('SemiLepNvtx'         , SemiLepNvtx         )
        t.SetBranchAddress('DeltaPhiLepFat'      , DeltaPhiLepFat      )
        t.SetBranchAddress('DeltaRLepFat'        , DeltaRLepFat        )
        t.SetBranchAddress('DeltaRAK4AK8'        , DeltaRAK4AK8        )
        t.SetBranchAddress('NearestAK4JetPt'     , NearestAK4JetPt     )
        t.SetBranchAddress('NearestAK4JetEta'    , NearestAK4JetEta    )
        t.SetBranchAddress('NearestAK4JetPhi'    , NearestAK4JetPhi    )
        t.SetBranchAddress('NearestAK4JetMass'   , NearestAK4JetMass   )
        t.SetBranchAddress('SemiLepEventWeight'     ,  SemiLepEventWeight   )
        t.SetBranchAddress('SemiLeptRunNum'         ,  SemiLeptRunNum       )
        t.SetBranchAddress('SemiLeptLumiBlock'      ,  SemiLeptLumiBlock    )
        t.SetBranchAddress('SemiLeptEventNum'       ,  SemiLeptEventNum     )
        t.SetBranchAddress('PU_CorrDn'       ,  PU_CorrDn     )
        t.SetBranchAddress('PU_CorrUp'       ,  PU_CorrUp     )

        t.SetBranchStatus ('*', 0)
        t.SetBranchStatus ('FatJetPt', 1)
        t.SetBranchStatus ('FatJetEta', 1)
        t.SetBranchStatus ('FatJetPhi', 1)
        t.SetBranchStatus ('FatJetMass', 1)
        t.SetBranchStatus ('FatJetMassSoftDrop', 1)
        t.SetBranchStatus ('FatJetTau32', 1)
        t.SetBranchStatus ('FatJetTau21', 1)
        t.SetBranchStatus ('FatJetRhoRatio', 1)
        t.SetBranchStatus('BJet2Pt' , 1)
        t.SetBranchStatus('BJet2Eta' , 1)
        t.SetBranchStatus('BJet2Phi' , 1 )
        t.SetBranchStatus('BJet2Mass' , 1)
        t.SetBranchStatus('BJet2bDisc' , 1)
        t.SetBranchStatus('FatJetSDsubjetWpt',1)
        t.SetBranchStatus('FatJetSDsubjetWtau1',1)
        t.SetBranchStatus('FatJetSDsubjetWtau2',1)
        t.SetBranchStatus('FatJetSDsubjetWtau3',1)
        t.SetBranchStatus('FatJetSDsubjetWtau21',1)
        t.SetBranchStatus('FatJetSDsubjetWtau32',1)
        t.SetBranchStatus('FatJetSDbdiscW',1)
        t.SetBranchStatus('FatJetSDsubjetWEta',1)
        t.SetBranchStatus('FatJetSDsubjetWPhi',1)
        t.SetBranchStatus('FatJetSDsubjetBtau1',1)
        t.SetBranchStatus('FatJetSDsubjetBtau2',1)
        t.SetBranchStatus('FatJetSDsubjetBtau3',1)
        t.SetBranchStatus('FatJetSDsubjetBtau21',1)
        t.SetBranchStatus('FatJetSDsubjetBtau32',1)
        t.SetBranchStatus('FatJetSDbdiscB',1)
        t.SetBranchStatus('FatJetSDsubjetBpt',1)
        t.SetBranchStatus('FatJetSDsubjetWmass',1)
        t.SetBranchStatus ('SemiLeptTrig', 1)
        t.SetBranchStatus ('DeltaPhiLepFat'  ,1   )
        t.SetBranchStatus ('DeltaRLepFat'    ,1   )
        t.SetBranchStatus ('DeltaRAK4AK8'    ,1   )
        t.SetBranchStatus ('NearestAK4JetPt'   ,1 )
        t.SetBranchStatus ('NearestAK4JetEta'  ,1 )
        t.SetBranchStatus ('NearestAK4JetPhi'  ,1 )
        t.SetBranchStatus ('NearestAK4JetMass' ,1 )
        t.SetBranchStatus ('SemiLepMETpt'  , 1  )
        t.SetBranchStatus ('SemiLepMETpx'  , 1  )
        t.SetBranchStatus ('SemiLepMETpy'  , 1  )
        t.SetBranchStatus ('AK4bDisc'      , 1  )
        t.SetBranchStatus ('SemiLepMETphi' , 1  )
        t.SetBranchStatus ('LeptonType'          , 1)
        t.SetBranchStatus ('LeptonPt'            , 1)
        t.SetBranchStatus ('LeptonEta'           , 1)
        t.SetBranchStatus ('LeptonPhi'           , 1)
        t.SetBranchStatus ('LeptonEnergy'        , 1)
        t.SetBranchStatus ('LeptonIso'           , 1)
        t.SetBranchStatus ('LeptonPtRel'         , 1)
        t.SetBranchStatus ('LeptonDRMin'         , 1)
        t.SetBranchStatus ('LeptonCharge'        , 1)
        t.SetBranchStatus ('LeptonHEEPEl'        , 1)
        t.SetBranchStatus ('LeptonCutIDLooseEl'  , 1)
        t.SetBranchStatus ('LeptonHighPtMu'      , 1)
        t.SetBranchStatus ('LeptonLoose'         , 1)
        t.SetBranchStatus ('LeptonTight'         , 1)
        t.SetBranchStatus ('SemiLepEventWeight'  , 1) 
        t.SetBranchStatus ('SemiLeptRunNum'      , 1)
        t.SetBranchStatus ('SemiLeptLumiBlock'   , 1)
        t.SetBranchStatus ('SemiLeptEventNum'    , 1)
        t.SetBranchStatus ('PU_CorrDn'           , 1)
        t.SetBranchStatus ('PU_CorrUp'           , 1)


    entries = t.GetEntriesFast()
    if options.maxEvents < 0. :
        eventsToRun = entries
    else :
        eventsToRun = options.maxEvents
    if not options.b2gtree :
        if options.verbose : print "Testing trees located at /store/group/lpctlbsm/aparker/{0} ".format(options.treeLocation)
    # Begin Event Loop
    for jentry in xrange( eventsToRun ):
        if jentry % 100000 == 0 or options.verbose :
            print 'processing ' + str(jentry)
        ientry = t.GetEntry( jentry )
        if ientry < 0:
            break
        # Event Info
        
        if options.b2gtree :
            weightS = SemiLeptEventWeight[0]
            eventNum = SemiLeptEventNum[0]

            # Lepton Observables
            theLepton = ROOT.TLorentzVector()
            theLepton.SetPtEtaPhiM( LeptonPt[0], LeptonEta[0], LeptonPhi[0], LeptonMass[0] ) 
            LepPt = theLepton.Perp()
            LepEta = theLepton.Eta()
            LepPhi = theLepton.Phi()
            LepMass = theLepton.M()

            LepType = 2
            LepisMu =  1. # FIX THIS LeptonIsMu[0] does not appear functional
            Muistight = MuTight[0]
            MuIsolation = MuIso[0]    
            LeptonIsol = MuIsolation

            lepton_ptRel = PtRel[0]

            lepton_DRmin = DeltaRJetLep[0] 

            DeltaRLepFat = [] # DR lepton and AK8
            DeltaRLepFat.append( DeltaRJetLep[0] )
            LeptonDRMin = [] # DR lepton and AK4
            LeptonDRMin.append( AK4dRminLep[0] )

            # MET Observables
            nuCandP4 = ROOT.TLorentzVector( )
            nuCandP4.SetPxPyPzE(SemiLeptMETpx[0], SemiLeptMETpy[0], 0.0, SemiLeptMETpt[0])
            MET_pt = nuCandP4.Perp()

            # ak4 Observables            
            ak4CandP4puppi0 = ROOT.TLorentzVector()
            ak4CandP4puppi0.SetPtEtaPhiM( AK4dRminPt[0], AK4dRminEta[0], AK4dRminPhi[0], AK4dRminMass[0])
            ak4_bdisc = AK4dRminBdisc[0]
            ak4_HemiHasBtagLoose = LepHemiContainsAK4BtagLoose[0]
            ak4_HemiHasBtagMedium = LepHemiContainsAK4BtagMedium[0]
            ak4_HemiHasBtagTight = LepHemiContainsAK4BtagTight[0]

        if not options.b2gtree :
            weightS = SemiLepEventWeight[0]
            eventNum = SemiLeptEventNum[0]
            triggerRun = SemiLeptTrig[0]
            type1or2 = BoosttypE[0]
            runNum = SemiLeptRunNum[0]
            lumiBlock = SemiLeptLumiBlock[0]

            # Lepton Observables
            theLepton = ROOT.TLorentzVector()
            theLepton.SetPtEtaPhiE( LeptonPt[0], LeptonEta[0], LeptonPhi[0], LeptonEnergy[0] ) # Assume massless
            if options.verbose : 
                print "Lepton ( Pt = {0:3.2f}, Eta = {1:3.2f}, Phi = {2:3.2f}, Mass = {3:3.2f}), Iso = {4:0.3f}".format(LeptonPt[0], LeptonEta[0], LeptonPhi[0], LeptonEnergy[0], LeptonIso[0] )

            LepPt = theLepton.Perp()
            LepEta = theLepton.Eta()
            LepPhi = theLepton.Phi()
            LepType =  LeptonType[0]
            LepMass = theLepton.M()
            LeptonIsol = LeptonIso[0]
            lepton_ptRel = LeptonPtRel[0]
            lepton_DRmin = LeptonDRMin[0] 

            lepton_isTight = LeptonTight[0]
            lepton_isLoose = LeptonLoose[0]
            lepton_HEEP_el = LeptonHEEPEl[0] 
            lepton_CutIDLoose_el = LeptonCutIDLooseEl[0] 
            lepton_HighPt_mu = LeptonHighPtMu[0] 

            # MET Observables
            nuCandP4 = ROOT.TLorentzVector( )
            #nuCandP4.SetPtEtaPhiM( SemiLepMETpt[0], 0, SemiLepMETphi[0], SemiLepMETpt[0] )
            nuCandP4.SetPxPyPzE(SemiLepMETpx[0], SemiLepMETpy[0], 0.0, SemiLepMETpt[0])
            MET_pt = nuCandP4.Perp()
            if options.verbose : 
                print "MET ( Px = {0:3.3f}, Py = {1:3.3f}, Pz = {2:3.3f}, Pt = {3:3.3f})".format(SemiLepMETpx[0], SemiLepMETpy[0], 0.0, SemiLepMETpt[0])
            # ak4 Observables            
            ak4CandP4puppi0 = ROOT.TLorentzVector()
            ak4CandP4puppi0.SetPtEtaPhiM( NearestAK4JetPt[0], NearestAK4JetEta[0], NearestAK4JetPhi[0], NearestAK4JetMass[0])
            ak4_bdisc = AK4bDisc[0]
            if options.verbose : print "AK4 ( Pt = {0:3.3f}, Eta = {1:3.3f}, Phi = {2:3.3f}, Mass = {3:3.3f})".format(NearestAK4JetPt[0], NearestAK4JetEta[0], NearestAK4JetPhi[0], NearestAK4JetMass[0])


        if options.b2gtree :
            # ak8 Observables 

            FatJetP4 = ROOT.TLorentzVector()    # fix this, obs should be SD mass but its empty in new Jim trees
            FatJetP4.SetPtEtaPhiM( JetPuppiPt[0], JetPuppiEta[0], JetPuppiPhi[0], JetPuppiMass[0] ) #* JetPuppiSDmassCorr[0])
            drAK4AK8 = 1.1 # fix this, should be DR btw AK4 and AK8
            fateta =  JetPuppiEta[0]
            FatJetSD_m = JetPuppiMass[0] # fix this should be JetPuppiSDmass[0]
            #print "Fat jet SD mass is : {0}".format(JetPuppiMass[0] ) 
            FatJetSD_pt = JetPuppiSDpt[0]
            tau32 = JetPuppiTau32[0]
            tau21 = JetPuppiTau21[0]
            #tau3 = JetPuppiTau3[0]
            #tau2 = JetPuppiTau2[0]
            #tau1 = JetPuppiTau1[0]


            # ak8 subjet Observables      # fix this (define these for type 1 selection)       
            '''
            W_m = FatJetSDsubjetWmass[0]
            W_pt = FatJetSDsubjetWpt[0]
            W_tau1 = FatJetSDsubjetWtau1[0]
            W_tau2 = FatJetSDsubjetWtau2[0]
            W_tau3 = FatJetSDsubjetWtau3[0]
            W_bdisc = FatJetSDbdiscW[0]
            W_eta = FatJetSDsubjetWEta[0]
            W_phi = FatJetSDsubjetWPhi[0]
            W_tau21 = FatJetSDsubjetWtau21[0]
            if options.Type2 :
                B_pt = BJet2Pt[0]
                B_m = BJet2Mass[0]
                B_bdisc = BJet2bDisc[0]

            if not options.Type2 :
                B_pt = FatJetSDsubjetBpt[0]
                B_m = FatJetSDsubjetBmass[0]
                B_bdisc = FatJetSDbdiscB[0]

            '''
            #applying Thea's corrections for Type 2   
            if options.applyTheaCorr and  options.Type2  and FatJetSD_pt >  170. : # and type1or2 == 2 :
                W_mRaw = FatJetSD_m  # mass is initially raw, multiply by correction factor to give corrected mass
                W_ptRaw = FatJetSD_pt
                W_eta = JetPuppiSDeta[0]
                puppiCorr = getPUPPIweight( W_ptRaw , W_eta )
                FatJetSD_m = W_mRaw * puppiCorr
            '''  # fix this, change to work for options.b2gtree
            #applying Thea's corrections for Type 1
            if options.applyTheaCorr and ( not options.Type2 ) and FatJetSD_pt > (options.Ak8PtCut - 20. ) and W_pt > 170. and type1or2 == 1  :
                W_mRaw = FatJetSDsubjetWmassRaw[0]
                W_ptRaw = FatJetSDsubjetWptRaw[0]
                puppiCorr = getPUPPIweight( W_ptRaw , W_eta )
                W_m =  W_mRaw  * puppiCorr
            '''
            # applying High Intensity Proton (HIP) muon corrections

            # Fix this LeptonIsMu does not appear to be functional
            if LepisMu >= 1 : LepType = 2
            else : LepType = 1
            #print "Leptype is : {0}".format(LepType)

            if options.Type2 :
                if options.applyHIPCorr and LepisMu >0. and LepPt > 50. and abs(LepEta) < 2.1 and LeptonIso[0] < 0.1 and FatJetSD_pt > 200. : 
                    HIPcorrPt = getHIPMuonCorr(LepPt, LepEta, LepPhi, int(LeptonCharge[0]))
                    LepPt = HIPcorrPt
            else :
                if options.applyHIPCorr and LepisMu >0. and LepPt > 50. and abs(LepEta) < 2.1 and LeptonIso[0] < 0.1 and FatJetSD_pt > (options.Ak8PtCut - 20. ) : 
                    HIPcorrPt = getHIPMuonCorr(LepPt, LepEta, LepPhi, int(LeptonCharge[0]))
                    LepPt = HIPcorrPt
            # getting electron scale factors
            if options.verbose: print "the value of LepisMu is {0}".format( LepisMu )
            if options.applyElSF and LepisMu <= 0. :
                ElScaleFactor = getgsfTrackEffScaleFactor( LepEta, LepPt )
                if options.verbose: print "Electron Scale factor is : {0:4.3f} ".format( ElScaleFactor )

        if not options.b2gtree :
            # ak8 Observables 

            FatJetP4 = ROOT.TLorentzVector()    
            FatJetP4.SetPtEtaPhiM( FatJetPt[0], FatJetEta[0], FatJetPhi[0], FatJetMass[0])     
            fatpt = FatJetP4.Perp()
            fateta = FatJetP4.Eta()
            fatmass = FatJetP4.M()
            drAK4AK8 = DeltaRAK4AK8[0]

            FatJetSD_m = FatJetMassSoftDrop[0]
            Rhorat = FatJetRhoRatio[0]
            if (Rhorat > 0.001): # FatJetSDpt = m / (R*sqrt(rhoRatio))
                sqrtRhorat = math.sqrt(Rhorat)
                FatJetSD_pt = FatJetSD_m / (0.8 * sqrtRhorat  )
            else:
                FatJetSD_pt = 0.

            if options.verbose : print "Fat jet P4 is : {0:3.3f}  {1:3.3f} {2:3.3f} {3:3.3f} ".format( FatJetPt[0], FatJetEta[0], FatJetPhi[0], FatJetMass[0] )
            if options.verbose : print "Fat jet SD pt and mass are:  {0:3.3f}  {1:3.3f} ".format( FatJetSD_pt, FatJetMassSoftDrop[0] )
            tau32 = FatJetTau32[0]
            tau21 = FatJetTau21[0]
            #tau3 = FatJetTau3[0]
            #tau2 = FatJetTau2[0]
            #tau1 = FatJetTau1[0]

            if options.verbose : print "Fat jet tau  21 32 : {0:3.3f}  {1:3.3f}  ".format( FatJetTau21[0], FatJetTau32[0])

            # ak8 subjet Observables             

            W_m = FatJetSDsubjetWmass[0]
            W_pt = FatJetSDsubjetWpt[0]
            W_tau1 = FatJetSDsubjetWtau1[0]
            W_tau2 = FatJetSDsubjetWtau2[0]
            W_tau3 = FatJetSDsubjetWtau3[0]
            W_bdisc = FatJetSDbdiscW[0]
            W_eta = FatJetSDsubjetWEta[0]
            W_phi = FatJetSDsubjetWPhi[0]
            W_tau21 = FatJetSDsubjetWtau21[0]
            if options.Type2 :
                B_pt = BJet2Pt[0]
                B_m = BJet2Mass[0]
                B_bdisc = BJet2bDisc[0]

            if not options.Type2 :
                B_pt = FatJetSDsubjetBpt[0]
                B_m = FatJetSDsubjetBmass[0]
                B_bdisc = FatJetSDbdiscB[0]


            #applying Thea's corrections for Type 2   FIX THIS SHOULD BE SD MASS AND PT RAW
            if options.applyTheaCorr and  options.Type2 : 
                W_mRaw = FatJetSD_m # SD mass is raw
                W_ptRaw = FatJetSD_pt
                puppiCorr = getPUPPIweight( W_ptRaw , W_eta )
                FatJetSD_m = W_mRaw * puppiCorr

            #applying Thea's corrections for Type 1
            if options.applyTheaCorr and ( not options.Type2 ) : 
                W_mRaw = FatJetSDsubjetWmassRaw[0]
                W_ptRaw = FatJetSDsubjetWptRaw[0]
                puppiCorr = getPUPPIweight( W_ptRaw , W_eta )
                W_m =  W_mRaw  * puppiCorr

            # applying High Intensity Proton (HIP) muon corrections
            if options.applyHIPCorr and LepType == 2 : 
                HIPcorrPt = getHIPMuonCorr(LepPt, LepEta, LepPhi, int(LeptonCharge[0]))
                LepPt = float(HIPcorrPt)
            # getting electron scale factors
            if options.applyElSF and LepType == 1 :
                ElScaleFactor = getgsfTrackEffScaleFactor( LepEta, LepPt )
                if options.verbose: print "Electron Scale factor is : {0:4.3f}".format( ElScaleFactor )


        realw = -1
        fakew = -1
        # Get Generator level matching Info
        if options.match and options.dtype == 'ttjets':
            # FIX THIS to read the Matched tree and get info or re-do the gen matching
            realw = FatJetSDsubjet_isRealW[0]
            fakew = FatJetSDsubjet_isRealW[0]


        TheWeight = weightS

        # applying electron scale factors
        if LepType == 1 and options.applyElSF and options.dtype != 'data':
            TheWeight = weightS * ElScaleFactor
            if options.verbose : print "An electron SF of {0:2.3f} was applied ".format(ElScaleFactor)
 
        HtLep = LepPt + MET_pt
        Ht = 0.
        if options.b2gtree :
            for iak4,ak4jet in enumerate(AK4dRminPt) : 
                if AK4dRminPt[iak4] > 30. :
                    Ht += AK4dRminPt[iak4] 
        if  not options.b2gtree :
            for iak4,ak4jet in enumerate(NearestAK4JetPt) : 
                if NearestAK4JetPt[iak4] > 30. :
                    Ht += NearestAK4JetPt[iak4]   

        if options.Type2 :
            thatMass = FatJetSD_m
            W_pt = FatJetSD_pt
            ptcut = 200.
        else :
            thatMass = W_m
            ptcut = options.Ak8PtCut
        fout.cd()

        #if fatpt < ptcut : continue

        # Filling lepton histograms before All cuts (except qaulity cuts made in creation of Ntuples and ttrees )
        if (str(options.dtype) == 'data') :
            hpAll_lepPt_Data.Fill(LepPt       , TheWeight)
            hpAll_lepEta_Data.Fill(LepEta     , TheWeight)
            hpAll_lepHtLep_Data.Fill(HtLep    , TheWeight)
            if LepType == 1 :
                hpAll_lepPt_ElData.Fill(LepPt       , TheWeight)
                hpAll_lepEta_ElData.Fill(LepEta     , TheWeight)
                hpAll_lepHtLep_ElData.Fill(HtLep    , TheWeight)
            elif LepType == 2 :
                hpAll_lepPt_MuData.Fill(LepPt       , TheWeight)
                hpAll_lepEta_MuData.Fill(LepEta     , TheWeight)
                hpAll_lepHtLep_MuData.Fill(HtLep    , TheWeight)
        if (str(options.dtype) != 'data') : 
            hpAll_lepPt_MC.Fill(LepPt       , TheWeight)
            hpAll_lepEta_MC.Fill(LepEta     , TheWeight)
            hpAll_lepHtLep_MC.Fill(HtLep    , TheWeight)

        # filling jet variable plots before lepton and AK4 selection 
        if options.b2gtree:
            if (options.dtype == 'data') :
                hpAll_lepSt_Data.Fill(ST[0] ,            TheWeight )  
                hpAll_lepHt_Data.Fill(Ht ,               TheWeight )
                hpAll_AK8Tau21_Data.Fill(tau21,          TheWeight ) 
                hpAll_AK8Pt_Data.Fill(FatJetSD_pt ,      TheWeight )
                if LepisMu <= 0. : # 
                    hpAll_lepHt_ElData.Fill(Ht ,        TheWeight )
                    hpAll_lepSt_ElData.Fill(ST[0] ,     TheWeight )
                    hpAll_AK8Tau21_ElData.Fill(tau21,          TheWeight ) 
                    hpAll_AK8Pt_ElData.Fill(FatJetSD_pt ,      TheWeight )
                    #h_AK8subjetTau21_ElData.Fill(W_tau21,  TheWeight )
                    #h_AK8subjetPt_ElData.Fill(W_pt,        TheWeight )
                if LepisMu < 0. :
                    hpAll_lepHt_MuData.Fill(Ht ,        TheWeight )
                    hpAll_lepSt_MuData.Fill(ST[0] ,     TheWeight )
                    hpAll_AK8Tau21_MuData.Fill(tau21,          TheWeight ) 
                    hpAll_AK8Pt_MuData.Fill(FatJetSD_pt ,      TheWeight )
                    #h_AK8subjetTau21_MuData.Fill(W_tau21,  TheWeight )
                    #h_AK8subjetPt_MuData.Fill(W_pt,        TheWeight )
            if (options.dtype != 'data') :
                hpAll_lepSt_MC.Fill(ST[0] ,            TheWeight )  
                hpAll_lepHt_MC.Fill(Ht ,               TheWeight )
                hpAll_AK8Tau21_MC.Fill(tau21,          TheWeight ) 
                hpAll_AK8Pt_MC.Fill(FatJetSD_pt ,      TheWeight )          
        if not options.b2gtree:
            St = Ht + HtLep
            if (options.dtype == 'data') :
                hpAll_lepSt_Data.Fill(St ,                       TheWeight )
                hpAll_lepHt_Data.Fill(Ht ,                       TheWeight )
                hpAll_AK8Tau21_Data.Fill(tau21,                  TheWeight ) 
                hpAll_AK8Pt_Data.Fill(FatJetSD_pt ,              TheWeight )
                hpAll_mWsubjetPasstag_Data.Fill(thatMass       , TheWeight )
                #hpAll_AK8subjetTau21_Data.Fill(W_tau21,  TheWeight )
                #hpAll_AK8subjetPt_Data.Fill(W_pt, TheWeight )
                if LepType == 1 :
                    hpAll_lepHt_ElData.Fill(Ht ,     TheWeight )
                    hpAll_lepSt_ElData.Fill(St ,     TheWeight )
                    hpAll_AK8Tau21_ElData.Fill(tau21,          TheWeight ) 
                    hpAll_AK8Pt_ElData.Fill(FatJetSD_pt ,      TheWeight )
                    hpAll_mWsubjetPasstag_ElData.Fill(thatMass       , TheWeight )
                    #hpAll_AK8subjetTau21_ElData.Fill(W_tau21,  TheWeight )
                    #hpAll_AK8subjetPt_ElData.Fill(W_pt, TheWeight )
                if LepType == 2 :
                    hpAll_lepHt_MuData.Fill(Ht ,     TheWeight )
                    hpAll_lepSt_MuData.Fill(St ,     TheWeight )
                    hpAll_AK8Tau21_MuData.Fill(tau21,          TheWeight ) 
                    hpAll_AK8Pt_MuData.Fill(FatJetSD_pt ,      TheWeight )
                    hpAll_mWsubjetPasstag_MuData.Fill(thatMass       , TheWeight )
                    #hpAll_AK8subjetTau21_MuData.Fill(W_tau21,  TheWeight )
                    #hpAll_AK8subjetPt_MuData.Fill(W_pt, TheWeight )
            if (options.dtype != 'data') :
                hpAll_lepSt_MC.Fill(St ,               TheWeight )  
                hpAll_lepHt_MC.Fill(Ht ,               TheWeight )
                hpAll_AK8Tau21_MC.Fill(tau21,          TheWeight ) 
                hpAll_AK8Pt_MC.Fill(FatJetSD_pt ,      TheWeight )  
                hpAll_mWsubjetPasstag_MC.Fill(thatMass       , TheWeight )





        ##  ____  __.__                              __  .__         __________                     
        ## |    |/ _|__| ____   ____   _____ _____ _/  |_|__| ____   \______   \ ____   ____  ____  
        ## |      < |  |/    \_/ __ \ /     \\__  \\   __\  |/ ___\   |       _// __ \_/ ___\/  _ \ 
        ## |    |  \|  |   |  \  ___/|  Y Y  \/ __ \|  | |  \  \___   |    |   \  ___/\  \__(  <_> )
        ## |____|__ \__|___|  /\___  >__|_|  (____  /__| |__|\___  >  |____|_  /\___  >\___  >____/ 
        ##         \/       \/     \/      \/     \/             \/          \/     \/     \/       

        # Now we do our kinematic calculation based on the semi-leptonic selection detailed in AN-16-215 (previous selection was B2G-15-002)


        if options.verbose : print "Pre-selection Lepton : Pt {0:3.3f}, Eta {1:3.3f}, METpt {2:3.3f}, Iso {3:3.3f}, Leptype {4:1.0f}".format(LepPt, LepEta, MET_pt, LeptonIsol, LepType  ) 

        #Electron Selection

        passEleMETcut     = LepType == 1  and  MET_pt > 80. 
        passEleEtacut     = LepType == 1  and ( 0. < abs(LepEta) < 1.442 or 1.56 < abs(LepEta) < 2.5 )
        passElePtcut      = LepType == 1  and  LepPt > 120. 
        passEleHEEPcut    = LepType == 1  and  lepton_HEEP_el > 0. 
        passEleCutIDcut   = LepType == 1  and  lepton_CutIDLoose_el > 0. 
        passEleTrigger    = LepType == 1  and  triggerRun > 1.       # fix this : apply this cut

        passEl         = (passEleMETcut and passElePtcut and passEleEtacut and passEleHEEPcut  )

        if passElePtcut :
            passcuts[0] +=1    
        if passEleEtacut :
            passcuts[1] +=1
        if passEleMETcut :
            passcuts[2] +=1
        if passEleTrigger :
            passcuts[28] +=1
        if passEleHEEPcut :  
            passcuts[30] +=1
        if passEl :
            passcuts[18] +=1
            if options.verbose  : 
                print "Electron:  pt {0:3.2f}, eta {1:3.2f}, MET_pt {2:3.2f}".format(LepPt, abs(LepEta),  MET_pt) 



        #Muon Selection

        passMuPtcut        = LepType == 2 and LepPt > 53. 
        passMuEtacut       = LepType == 2 and abs(LepEta) < 2.1 
        passMuMETcut       = LepType == 2 and MET_pt > 40.
        passMuIsocut       = LepType == 2 and LeptonIsol < 0.1
        passMuTightcut     = LepType == 2 and lepton_isTight > 0. 
        passMuTrigger      = LepType == 2 and triggerRun < 2.      
        
        if options.treeLocation == '80xTTrees' : 
            passMuHighPtcut    = LepType == 2 and lepton_HighPt_mu > 0.
            passMuLoosecut     = LepType == 2 and (lepton_isLoose > 0. and LepPt > 20. and abs(LepEta) < 2.4 and lepton_HighPt_mu > 0. )  
   
            passMu             = (passMuPtcut and passMuMETcut and passMuEtacut and passMuIsocut and passMuHighPtcut and (passMuTightcut or passMuLoosecut ) and passMuTrigger) 

        if options.treeLocation == 'Last80xTrees' : 
               passMu          = (passMuPtcut and passMuMETcut and passMuEtacut and passMuIsocut and passMuTightcut and passMuTrigger) 

        # fix this : require above passMu definition

        passMu          = (passMuPtcut and passMuMETcut and passMuEtacut and passMuIsocut and passMuTightcut and passMuTrigger) 

        if options.verbose : print "The muon passed the following cuts with values:"

        if passMuPtcut :
            passcuts[3]   +=1
            if options.verbose : print "Pt > 53  :              {0:3.3f} ".format(LepPt ) 


        if passMuEtacut :
            passcuts[19]  +=1
            if options.verbose : print "|eta|<2.1  :            {0:3.3f} ".format( LepEta ) 


        if passMuMETcut :
            passcuts[20]  +=1
            if options.verbose : print "MET Pt > 40  :          {0:3.3f}".format(MET_pt ) 


        if passMuIsocut :
            passcuts[4]   +=1  
            if options.verbose : print "MuonIso < 0.1  :        {0:3.3f} ".format(LeptonIsol)
 
        if options.treeLocation == '80xTTrees' : 
            if passMuHighPtcut :
                passcuts[26]   +=1  
                if options.verbose : print "HighPtMuon  :           {0:1.0f} ".format(lepton_HighPt_mu) 

        if passMuTightcut :
            passcuts[27]   +=1  
            if options.verbose : print "MuonisTight  :              {0:1.0f} ".format(lepton_isTight) 


        if passMuTrigger :
            passcuts[29]   +=1  
            if triggerRun == 0 : trigIs = "HLT_Mu45_eta2p1_"
            if triggerRun == 1 : trigIs = "HLT_Mu50_"
            if options.verbose : print "Muon passing Trigger :  {0:s} ".format(trigIs) 

                        
        if passMu :
            passcuts[21]  +=1
            if options.verbose : print "Muon p4 passing all Muon cuts : {0:3.3f}  {1:3.3f} {2:3.3f} {3:3.3f}".format(LepPt, LepEta, LepPhi, LepMass ) 
            if options.verbose : 
                print "Muon:  pt {0:3.2f}, eta {1:3.2f}, MET_pt {2:3.2f}".format(LepPt, abs(LepEta),  MET_pt) 



        #Lepton Selection


        #passLepDrmin    = LeptonDRMin[0] > 0.3
        passHemidR = DeltaRLepFat[0] >= 1. 
        passLepcut = ( passMu or passEl)  and passHemidR  #  passLepDrmin 

        

        #if passLepDrmin :
        #    passcuts[22] += 1
        #    if options.verbose and LepType == 2: print "Lepton p4 passing  Dr( Lep, AK4) > 0.3 : {0:3.3f}  {1:3.3f} {2:3.3f} {3:3.3f}".format(LepPt, LepEta, LepPhi, LepMass ) 
        if passHemidR:
            passcuts[7] += 1
            if options.verbose and LepType == 2 : print " Dr(Lep, AK8) {0:3.3f} ".format( DeltaRLepFat[0])
            if options.verbose and LepType == 2 : print "Lepton p4 passing  Dr( Lep, AK8) > 1. : {0:3.3f}  {1:3.3f} {2:3.3f} {3:3.3f}".format(LepPt, LepEta, LepPhi, LepMass ) 


        # final lepton cuts applied
        if not passLepcut : continue
        else : passcuts[5] += 1




        # Filling lepton histograms after lepton cuts
        if (str(options.dtype) == 'data') :
            hlep_lepPt_Data.Fill(LepPt       , TheWeight)
            hlep_lepEta_Data.Fill(LepEta     , TheWeight)
            hlep_lepHtLep_Data.Fill(HtLep    , TheWeight)
            if LepType == 1 :
                hlep_lepPt_ElData.Fill(LepPt       , TheWeight)
                hlep_lepEta_ElData.Fill(LepEta     , TheWeight)
                hlep_lepHtLep_ElData.Fill(HtLep    , TheWeight)
            elif LepType == 2 :
                hlep_lepPt_MuData.Fill(LepPt       , TheWeight)
                hlep_lepEta_MuData.Fill(LepEta     , TheWeight)
                hlep_lepHtLep_MuData.Fill(HtLep    , TheWeight)
        if (str(options.dtype) != 'data') : # fix this should be != 'data'
            hlep_lepPt_MC.Fill(LepPt       , TheWeight)
            hlep_lepEta_MC.Fill(LepEta     , TheWeight)
            hlep_lepHtLep_MC.Fill(HtLep    , TheWeight)

        # filling jet variable plots after lepton selection 
        if options.b2gtree:
            if (options.dtype == 'data') :
                hlep_lepSt_Data.Fill(ST[0] ,               TheWeight )  
                hlep_lepHt_Data.Fill(Ht ,               TheWeight )
                hlep_AK8Tau21_Data.Fill(tau21,          TheWeight ) 
                hlep_AK8Pt_Data.Fill(FatJetSD_pt ,      TheWeight )
                if LepisMu <= 0. : # 
                    hlep_lepHt_ElData.Fill(Ht ,     TheWeight )
                    hlep_lepSt_ElData.Fill(ST[0] ,     TheWeight )
                    hlep_AK8Tau21_ElData.Fill(tau21,          TheWeight ) 
                    hlep_AK8Pt_ElData.Fill(FatJetSD_pt ,      TheWeight )
                    #h_AK8subjetTau21_ElData.Fill(W_tau21,  TheWeight )
                    #h_AK8subjetPt_ElData.Fill(W_pt, TheWeight )
                if LepisMu < 0. :
                    hlep_lepHt_MuData.Fill(Ht ,     TheWeight )
                    hlep_lepSt_MuData.Fill(ST[0] ,     TheWeight )
                    hlep_AK8Tau21_MuData.Fill(tau21,          TheWeight ) 
                    hlep_AK8Pt_MuData.Fill(FatJetSD_pt ,      TheWeight )
                    #h_AK8subjetTau21_MuData.Fill(W_tau21,  TheWeight )
                    #h_AK8subjetPt_MuData.Fill(W_pt, TheWeight )
            if (options.dtype != 'data') :
                hlep_lepSt_MC.Fill(ST[0] ,               TheWeight )  
                hlep_lepHt_MC.Fill(Ht ,               TheWeight )
                hlep_AK8Tau21_MC.Fill(tau21,          TheWeight ) 
                hlep_AK8Pt_MC.Fill(FatJetSD_pt ,      TheWeight )          
        if not options.b2gtree:
            St = Ht + HtLep
            if (options.dtype == 'data') :
                hlep_lepSt_Data.Fill(St ,               TheWeight )
                hlep_lepHt_Data.Fill(Ht ,               TheWeight )
                hlep_AK8Tau21_Data.Fill(tau21,          TheWeight ) 
                hlep_AK8Pt_Data.Fill(FatJetSD_pt ,      TheWeight )
                hlep_mWsubjetPasstag_Data.Fill(thatMass       , TheWeight )
                #h_AK8subjetTau21_Data.Fill(W_tau21,  TheWeight )
                #h_AK8subjetPt_Data.Fill(W_pt, TheWeight )
                if LepType == 1 :
                    hlep_lepHt_ElData.Fill(Ht ,     TheWeight )
                    hlep_lepSt_ElData.Fill(St ,     TheWeight )
                    hlep_AK8Tau21_ElData.Fill(tau21,          TheWeight ) 
                    hlep_AK8Pt_ElData.Fill(FatJetSD_pt ,      TheWeight )
                    hlep_mWsubjetPasstag_ElData.Fill(thatMass       , TheWeight )
                    #h_AK8subjetTau21_ElData.Fill(W_tau21,  TheWeight )
                    #h_AK8subjetPt_ElData.Fill(W_pt, TheWeight )
                if LepType == 2 :
                    hlep_lepHt_MuData.Fill(Ht ,     TheWeight )
                    hlep_lepSt_MuData.Fill(St ,     TheWeight )
                    hlep_AK8Tau21_MuData.Fill(tau21,          TheWeight ) 
                    hlep_AK8Pt_MuData.Fill(FatJetSD_pt ,      TheWeight )
                    hlep_mWsubjetPasstag_MuData.Fill(thatMass       , TheWeight )
                    #h_AK8subjetTau21_MuData.Fill(W_tau21,  TheWeight )
                    #h_AK8subjetPt_MuData.Fill(W_pt, TheWeight )
            if (options.dtype != 'data') :
                hlep_lepSt_MC.Fill(St ,                 TheWeight )  
                hlep_lepHt_MC.Fill(Ht ,                 TheWeight )
                hlep_AK8Tau21_MC.Fill(tau21,            TheWeight ) 
                hlep_AK8Pt_MC.Fill(FatJetSD_pt ,        TheWeight ) 
                hlep_mWsubjetPasstag_MC.Fill(thatMass,  TheWeight ) 


        #AK4 Selection
        passBtagBdisc = ak4_bdisc > 0.8
        passBtagPt = ak4CandP4puppi0.Perp() > 30.
        passBtagEta = abs(ak4CandP4puppi0.Eta()) < 2.4
        passBDrAK8 = drAK4AK8 > 0.8 

        passAK4 = (passBtagBdisc and passBtagPt and passBtagEta ) #and passBDrAK8)
        if passBtagBdisc :
            passcuts[12] += 1
        if passBtagPt :
            passcuts[13] += 1  
        if passBtagEta :
            passcuts[25] += 1 
        if passBDrAK8 :
            passcuts[23] += 1  
        if passAK4 :
            passcuts[24] += 1


        # AK4 cuts applied
        if not passAK4 : continue


        # Filling lepton histograms after lepton and AK4 cuts
        if (str(options.dtype) == 'data') :
            hak4_lepPt_Data.Fill(LepPt       , TheWeight)
            hak4_lepEta_Data.Fill(LepEta     , TheWeight)
            hak4_lepHtLep_Data.Fill(HtLep    , TheWeight)
            if LepType == 1 :
                hak4_lepPt_ElData.Fill(LepPt       , TheWeight)
                hak4_lepEta_ElData.Fill(LepEta     , TheWeight)
                hak4_lepHtLep_ElData.Fill(HtLep    , TheWeight)
            elif LepType == 2 :
                hak4_lepPt_MuData.Fill(LepPt       , TheWeight)
                hak4_lepEta_MuData.Fill(LepEta     , TheWeight)
                hak4_lepHtLep_MuData.Fill(HtLep    , TheWeight)
        if (str(options.dtype) != 'data') : # fix this should be != 'data'
            hak4_lepPt_MC.Fill(LepPt       , TheWeight)
            hak4_lepEta_MC.Fill(LepEta     , TheWeight)
            hak4_lepHtLep_MC.Fill(HtLep    , TheWeight)

        # filling jet variable plots after lepton and AK4 selection 
        if options.b2gtree:
            if (options.dtype == 'data') :
                hak4_lepSt_Data.Fill(ST[0] ,               TheWeight )  
                hak4_lepHt_Data.Fill(Ht ,               TheWeight )
                hak4_AK8Tau21_Data.Fill(tau21,          TheWeight ) 
                hak4_AK8Pt_Data.Fill(FatJetSD_pt ,      TheWeight )
                if LepisMu <= 0. : # 
                    hak4_lepHt_ElData.Fill(Ht ,     TheWeight )
                    hak4_lepSt_ElData.Fill(ST[0] ,     TheWeight )
                    hak4_AK8Tau21_ElData.Fill(tau21,          TheWeight ) 
                    hak4_AK8Pt_ElData.Fill(FatJetSD_pt ,      TheWeight )
                    #h_AK8subjetTau21_ElData.Fill(W_tau21,  TheWeight )
                    #h_AK8subjetPt_ElData.Fill(W_pt, TheWeight )
                if LepisMu < 0. :
                    hak4_lepHt_MuData.Fill(Ht ,     TheWeight )
                    hak4_lepSt_MuData.Fill(ST[0] ,     TheWeight )
                    hak4_AK8Tau21_MuData.Fill(tau21,          TheWeight ) 
                    hak4_AK8Pt_MuData.Fill(FatJetSD_pt ,      TheWeight )
                    #h_AK8subjetTau21_MuData.Fill(W_tau21,  TheWeight )
                    #h_AK8subjetPt_MuData.Fill(W_pt, TheWeight )
            if (options.dtype != 'data') :
                hak4_lepSt_MC.Fill(ST[0] ,               TheWeight )  
                hak4_lepHt_MC.Fill(Ht ,               TheWeight )
                hak4_AK8Tau21_MC.Fill(tau21,          TheWeight ) 
                hak4_AK8Pt_MC.Fill(FatJetSD_pt ,      TheWeight )          
        if not options.b2gtree:
            St = Ht + HtLep
            if (options.dtype == 'data') :
                hak4_lepSt_Data.Fill(St ,               TheWeight )
                hak4_lepHt_Data.Fill(Ht ,               TheWeight )
                hak4_AK8Tau21_Data.Fill(tau21,          TheWeight ) 
                hak4_AK8Pt_Data.Fill(FatJetSD_pt ,      TheWeight )
                hak4_mWsubjetPasstag_Data.Fill(thatMass       , TheWeight )
                #h_AK8subjetTau21_Data.Fill(W_tau21,  TheWeight )
                #h_AK8subjetPt_Data.Fill(W_pt, TheWeight )
                if LepType == 1 :
                    hak4_lepHt_ElData.Fill(Ht ,     TheWeight )
                    hak4_lepSt_ElData.Fill(St ,     TheWeight )
                    hak4_AK8Tau21_ElData.Fill(tau21,          TheWeight ) 
                    hak4_AK8Pt_ElData.Fill(FatJetSD_pt ,      TheWeight )
                    hak4_mWsubjetPasstag_ElData.Fill(thatMass , TheWeight )
                    #h_AK8subjetTau21_ElData.Fill(W_tau21,  TheWeight )
                    #h_AK8subjetPt_ElData.Fill(W_pt, TheWeight )
                if LepType == 2 :
                    hak4_lepHt_MuData.Fill(Ht ,     TheWeight )
                    hak4_lepSt_MuData.Fill(St ,     TheWeight )
                    hak4_AK8Tau21_MuData.Fill(tau21,          TheWeight ) 
                    hak4_AK8Pt_MuData.Fill(FatJetSD_pt ,      TheWeight )
                    hak4_mWsubjetPasstag_MuData.Fill(thatMass , TheWeight )
                    #h_AK8subjetTau21_MuData.Fill(W_tau21,  TheWeight )
                    #h_AK8subjetPt_MuData.Fill(W_pt, TheWeight )
            if (options.dtype != 'data') :
                hak4_lepSt_MC.Fill(St ,               TheWeight )  
                hak4_lepHt_MC.Fill(Ht ,               TheWeight )
                hak4_AK8Tau21_MC.Fill(tau21,          TheWeight ) 
                hak4_AK8Pt_MC.Fill(FatJetSD_pt ,      TheWeight ) 
                hak4_mWsubjetPasstag_MC.Fill(thatMass         , TheWeight ) 



        #AK8 Selection

        if options.Type2 :                                                                    # Type 2 AK8 selection
            #passWPre2 = FatJetSD_m > 50.
            passKin2 =  fatpt > 200. and abs(fateta) < 2.4 
            passWTagmass = 0.1 < fatmass < 150.
            passWPosttau2 = tau21 < options.tau21Cut 
            passWPostM2 = 40. < fatmass < 150.

            if passKin2 :
                passcuts[14] += 1
            if passWTagmass :
                passcuts[10] += 1
            if passWPosttau2:
                passcuts[15] +=1
            if passWPostM2:
                passcuts[16] +=1

        else :                                                                                # Type 1 AK8 selection
            passWPre =   W_m > 50. 

            passWPostM = 55. < W_m < 115.
            passWPosttau =  W_tau21 < options.tau21Cut 

            passKin = fatpt > options.Ak8PtCut
            #print "Fat Jet SD Pt : {0}".format(FatJetSD_pt)  
            passWKin = W_pt > 200.  and abs(W_eta) < 2.4 

            passTopTagtau = tau32 < options.tau32Cut 
            passTopTagmass =  110. < FatJetSD_m < 250.
            pass2DCut = LeptonPtRel[0] > 20. or LeptonDRMin[0] > 0.4

            if passKin :
                passcuts[8] += 1
            if passWKin :
                passcuts[14] += 1
            if pass2DCut : 
                passcuts[11] += 1
            if passTopTagtau :
                passcuts[9] += 1
            if passTopTagmass :
                passcuts[10] += 1
            if passWPosttau:
                passcuts[15] +=1
            if passWPostM:
                passcuts[16] +=1

        if options.Type2 :
            passPost = passWPosttau2
        else :
            passPost = passWPosttau
        
        # Type 2 cuts applied
        if options.Type2 :
            if passKin2:
                NpassPre +=1
                fillTree = True
                if  passWTagmass : # passWPosttau2 passWPostM2  
                    NpassPost +=1                                         
        # Type 1 cuts applied
        elif not options.Type2 :
            if passKin:
                NpassPre +=1
                topandKin = passTopTagtau and passTopTagmass  and passWKin
                if  ( topandKin and pass2DCut ):
                    NpassPost +=1  
                    fillTree = True
                    if options.verbose  :
                        print "Fat Jet: SD Mass {0:6.3}, Pt {1:6.3}, tau32 {2:0.4} - W Subjet: SD Mass {3:6.3}, Pt {4:6.3}, tau21 {5:0.4} - dRLepFat {6:6.3} ".format(FatJetSD_m, FatJetSD_pt, tau32, W_m, W_pt, W_tau21, DeltaRLepFat[0] )

        # FIX THIS -Fill the Combined Trees after selection here for later use as RooFit Input
        if fillTree is True :    
            if options.writeTree :
                print "Tree writing is not yet enabled"

                #tree.Fill()
                            


            fout.cd()



            # Filling the W mass distributions for AK8 jets of all Pts before the tau21 cut
            if (str(options.dtype) != 'data'):
                h_mWsubjet_MC.Fill(thatMass         , TheWeight )
            if (str(options.dtype) == 'data'):
                h_mWsubjet_Data.Fill(thatMass       , TheWeight )
                if LepType == 1 :
                    h_mWsubjet_ElData.Fill(thatMass , TheWeight ) 
                if LepType == 2 :
                    h_mWsubjet_MuData.Fill(thatMass , TheWeight )
            if passPost : # Filling W mass histos passing tau21 cut 
                if (str(options.dtype) != 'data'):
                    h_mWsubjetPasstag_MC.Fill(thatMass         , TheWeight )
                if (str(options.dtype) == 'data'):
                    h_mWsubjetPasstag_Data.Fill(thatMass       , TheWeight )
                    if LepType == 1 :
                        h_mWsubjetPasstag_ElData.Fill(thatMass , TheWeight ) 
                    if LepType == 2 :
                        h_mWsubjetPasstag_MuData.Fill(thatMass , TheWeight )
                # filling Lepton histograms after final selection
                if (str(options.dtype) == 'data') :
                    h_lepPt_Data.Fill(LepPt       , TheWeight)
                    h_lepEta_Data.Fill(LepEta     , TheWeight)
                    h_lepHtLep_Data.Fill(HtLep    , TheWeight)
                    if LepType == 1 :
                        h_lepPt_ElData.Fill(LepPt       , TheWeight)
                        h_lepEta_ElData.Fill(LepEta     , TheWeight)
                        h_lepHtLep_ElData.Fill(HtLep    , TheWeight)
                    elif LepType == 2 :
                        h_lepPt_MuData.Fill(LepPt       , TheWeight)
                        h_lepEta_MuData.Fill(LepEta     , TheWeight)
                        h_lepHtLep_MuData.Fill(HtLep    , TheWeight)
                if (str(options.dtype) != 'data') : # fix this should be != 'data'
                    h_lepPt_MC.Fill(LepPt       , TheWeight)
                    h_lepEta_MC.Fill(LepEta     , TheWeight)
                    h_lepHtLep_MC.Fill(HtLep    , TheWeight)
                # filling Jet histograms after final selection
                if options.b2gtree:
                    if (options.dtype == 'data') :
                        h_lepSt_Data.Fill(ST[0] ,               TheWeight )  
                        h_lepHt_Data.Fill(Ht ,               TheWeight )
                        h_AK8Tau21_Data.Fill(tau21,          TheWeight ) 
                        h_AK8Pt_Data.Fill(FatJetSD_pt ,      TheWeight )
                        if LepisMu <= 0. : # 
                            h_lepHt_ElData.Fill(Ht ,     TheWeight )
                            h_lepSt_ElData.Fill(ST[0] ,     TheWeight )
                            h_AK8Tau21_ElData.Fill(tau21,          TheWeight ) 
                            h_AK8Pt_ElData.Fill(FatJetSD_pt ,      TheWeight )
                            #h_AK8subjetTau21_ElData.Fill(W_tau21,  TheWeight )
                            #h_AK8subjetPt_ElData.Fill(W_pt, TheWeight )
                        if LepisMu < 0. :
                            h_lepHt_MuData.Fill(Ht ,     TheWeight )
                            h_lepSt_MuData.Fill(ST[0] ,     TheWeight )
                            h_AK8Tau21_MuData.Fill(tau21,          TheWeight ) 
                            h_AK8Pt_MuData.Fill(FatJetSD_pt ,      TheWeight )
                            #h_AK8subjetTau21_MuData.Fill(W_tau21,  TheWeight )
                            #h_AK8subjetPt_MuData.Fill(W_pt, TheWeight )
                    if (options.dtype != 'data') :
                        h_lepSt_MC.Fill(ST[0] ,               TheWeight )  
                        h_lepHt_MC.Fill(Ht ,               TheWeight )
                        h_AK8Tau21_MC.Fill(tau21,          TheWeight ) 
                        h_AK8Pt_MC.Fill(FatJetSD_pt ,      TheWeight )          
                if not options.b2gtree:
                    St = Ht + HtLep
                    if (options.dtype == 'data') :
                        h_lepSt_Data.Fill(St ,               TheWeight )
                        h_lepHt_Data.Fill(Ht ,               TheWeight )
                        h_AK8Tau21_Data.Fill(tau21,          TheWeight ) 
                        h_AK8Pt_Data.Fill(FatJetSD_pt ,      TheWeight )
                        #h_AK8subjetTau21_Data.Fill(W_tau21,  TheWeight )
                        #h_AK8subjetPt_Data.Fill(W_pt, TheWeight )
                        if LepType == 1 :
                            h_lepHt_ElData.Fill(Ht ,     TheWeight )
                            h_lepSt_ElData.Fill(St ,     TheWeight )
                            h_AK8Tau21_ElData.Fill(tau21,          TheWeight ) 
                            h_AK8Pt_ElData.Fill(FatJetSD_pt ,      TheWeight )
                            #h_AK8subjetTau21_ElData.Fill(W_tau21,  TheWeight )
                            #h_AK8subjetPt_ElData.Fill(W_pt, TheWeight )
                        if LepType == 2 :
                            h_lepHt_MuData.Fill(Ht ,     TheWeight )
                            h_lepSt_MuData.Fill(St ,     TheWeight )
                            h_AK8Tau21_MuData.Fill(tau21,          TheWeight ) 
                            h_AK8Pt_MuData.Fill(FatJetSD_pt ,      TheWeight )
                            #h_AK8subjetTau21_MuData.Fill(W_tau21,  TheWeight )
                            #h_AK8subjetPt_MuData.Fill(W_pt, TheWeight )
                    if (options.dtype != 'data') :
                        h_lepSt_MC.Fill(St ,               TheWeight )  
                        h_lepHt_MC.Fill(Ht ,               TheWeight )
                        h_AK8Tau21_MC.Fill(tau21,          TheWeight ) 
                        h_AK8Pt_MC.Fill(FatJetSD_pt ,      TheWeight ) 

            if  ( not passPost ) and ( tau21 != 1.0 ): # Filling W mass  histos failing tau21 cut # fix this W_tau21 for type1
                if (str(options.dtype) != 'data'):
                    h_mWsubjetFailtag_MC.Fill(thatMass         , TheWeight )
                if (str(options.dtype) == 'data'):
                    TheWeight = 1.
                    h_mWsubjetFailtag_Data.Fill(thatMass       , TheWeight )
                    if LepType == 1 :
                        h_mWsubjetFailtag_ElData.Fill(thatMass , TheWeight ) 
                    if LepType == 2 :
                        h_mWsubjetFailtag_MuData.Fill(thatMass , TheWeight )

            # Filling the W mass distributions binned by Pt of the W jet candidate before the tau21 cut
            if ( 200.0 < W_pt < 300.0 ):
                h_mWsubjet_b1p.Fill(thatMass              , TheWeight )
            if ( 300.0 < W_pt < 400.0 ) :                       
                h_mWsubjet_b2p.Fill(thatMass              , TheWeight )
            if ( 400.0 < W_pt < 500.0 ) : 
                h_mWsubjet_b3p.Fill(thatMass              , TheWeight )
            if ( W_pt > 500.0 ) : 
                h_mWsubjet_b4p.Fill(thatMass              , TheWeight )
            if ( 200. < W_pt < 800.0 ) : 
                h_mWsubjet_b5p.Fill(thatMass              , TheWeight )
            # Fill Electron 
            if (str(options.dtype) == 'data') and LepType == 1 :
                if ( 200.0 < W_pt < 300.0 ):
                    h_mWsubjet_b1pe.Fill(thatMass, TheWeight )
                if ( 300.0 < W_pt < 400.0 ) :                       
                    h_mWsubjet_b2pe.Fill(thatMass , TheWeight )
                if ( 400.0 < W_pt < 500.0 ) : 
                    h_mWsubjet_b3pe.Fill(thatMass, TheWeight )
                if ( W_pt > 500.0 ) : 
                    h_mWsubjet_b4pe.Fill(thatMass, TheWeight )
                if ( 200. < W_pt < 800.0 ) : 
                    h_mWsubjet_b5pe.Fill(thatMass, TheWeight )
            # Fill Muon 
            if (str(options.dtype) == 'data') and LepType == 2 :
                if (  200.0 < W_pt < 300.0 ):
                    h_mWsubjet_b1pm.Fill(thatMass, TheWeight )
                if (  300.0 < W_pt < 400.0 ) :                       
                    h_mWsubjet_b2pm.Fill(thatMass , TheWeight )
                if ( 400.0 < W_pt < 500.0 ) : 
                    h_mWsubjet_b3pm.Fill(thatMass, TheWeight )
                if ( W_pt > 500.0 ) : 
                    h_mWsubjet_b4pm.Fill(thatMass, TheWeight )
                if ( 200. < W_pt < 800.0 ) : 
                    h_mWsubjet_b5pm.Fill(thatMass, TheWeight )
            if passPost : # Post cut histos after tau21 cut 
                if ( W_pt > 200.0 and W_pt < 300.0 ):
                    h_mWsubjet_b1.Fill(thatMass, TheWeight )
                if ( W_pt > 300.0 and W_pt < 400.0 ) :                       
                    h_mWsubjet_b2.Fill(thatMass , TheWeight )
                if ( W_pt > 400.0 and W_pt < 500.0 ) : 
                    h_mWsubjet_b3.Fill(thatMass, TheWeight )
                if ( W_pt > 500.0 ) : 
                    h_mWsubjet_b4.Fill(thatMass, TheWeight )
                if ( 200. < W_pt < 800.0 ) : 
                    h_mWsubjet_b5.Fill(thatMass, TheWeight )
                # Fill Electron 
                if (str(options.dtype) == 'data') and LepType == 1 :
                    if ( W_pt > 200.0 and W_pt < 300.0 ):
                        h_mWsubjet_b1e.Fill(thatMass, TheWeight )
                    if ( W_pt > 300.0 and W_pt < 400.0 ) :                       
                        h_mWsubjet_b2e.Fill(thatMass , TheWeight )
                    if ( W_pt > 400.0 and W_pt < 500.0 ) : 
                        h_mWsubjet_b3e.Fill(thatMass, TheWeight )
                    if ( W_pt > 500.0 ) : 
                        h_mWsubjet_b4e.Fill(thatMass, TheWeight )
                    if ( 200. < W_pt < 800.0 ) : 
                        h_mWsubjet_b5e.Fill(thatMass, TheWeight )
                # Fill Muon 
                if (str(options.dtype) == 'data') and LepType == 2 :
                    if ( W_pt > 200.0 and W_pt < 300.0 ):
                        h_mWsubjet_b1m.Fill(thatMass, TheWeight )
                    if ( W_pt > 300.0 and W_pt < 400.0 ) :                       
                        h_mWsubjet_b2m.Fill(thatMass , TheWeight )
                    if ( W_pt > 400.0 and W_pt < 500.0 ) : 
                        h_mWsubjet_b3m.Fill(thatMass, TheWeight )
                    if ( W_pt > 500.0 ) : 
                        h_mWsubjet_b4m.Fill(thatMass, TheWeight )
                    if ( 200. < W_pt < 800.0 ) : 
                        h_mWsubjet_b5m.Fill(thatMass, TheWeight )

    print "          ****Cut Flow Table****         "
    print "total number of events of type {0:s} passing each cut".format(options.dtype) 
    print "..................................................."
    print "                Electrons                          "
    print "..................................................."
    print "Trigger:                   {0}".format(passcuts[28] )
    print "Pt cut:                    {0}".format(passcuts[0]  )
    print "Eta cut:                   {0}".format(passcuts[1]  ) 
    print "MET cut :                  {0}".format(passcuts[2]  ) 
    print "HEEP cut :                 {0}".format(passcuts[30] ) 
    print "ALL Electron cuts :        {0}".format(passcuts[18] )
    print "..................................................."
    print "                   Muons                           "
    print "..................................................."
    print "Trigger:                   {0}".format(passcuts[29] )
    print "Pt cut:                    {0}".format(passcuts[3]  )
    print "Eta cut:                   {0}".format(passcuts[19] ) 
    print "MET cut :                  {0}".format(passcuts[20] ) 
    print "Iso cut :                  {0}".format(passcuts[4]  ) 
    print "HighPt cut :               {0}".format(passcuts[26] ) 
    print "isTight cut :              {0}".format(passcuts[27] )
    print "ALL Muon cuts :            {0}".format(passcuts[21] )
    print "..................................................."
    print "                  Lepton                           "
    print "..................................................."
    #print "DR(lepton, AK4) cut:       {0}".format(passcuts[22] )
    print "DR(lepton, AK8) cut:       {0}".format(passcuts[7]  )
    print "ALL Lepton cuts:           {0}".format(passcuts[5]  )
    print "..................................................."
    print "                   AK4                             "
    print "..................................................."
    print "Pt cut:                    {0}".format(passcuts[13]  )
    print "Eta cut:                   {0}".format(passcuts[25]  )
    print "CSVv2 Bdisc cut:           {0}".format(passcuts[12]  )
    print "DR(AK4, AK8) cut:          {0}".format(passcuts[23]  )
    print "ALL AK4 cuts:              {0}".format(passcuts[24]  )

    if options.Type2:

        print "..................................................."
        print "                 Type 2 AK8                        "
        print "..................................................."



        print "total passing W jet pt and eta cut:   " + str(passcuts[14] ) 
        print "total passing W jet mass cut:         " + str(passcuts[16] ) 

        print "total passing pre-selection : " + str(NpassPre ) 

        print "total passing final selection : " + str(NpassPost )

    else :
        print "..................................................."
        print "                 Type 1 AK8                        "
        print "..................................................."
        print "total passing top pt cut: " + str(passcuts[8] ) 
        print "total passing top tau32 cut: " + str(passcuts[9] ) 
        print "total passing top mass: " + str(passcuts[10] ) 

        print "total passing 2D cut: " + str(passcuts[11] ) 
        print "total passing B tag bdisc: " + str(passcuts[12] ) 
        print "total passing B tag pt: " + str(passcuts[13] ) 

        print "total passing W subjet pt and eta cut:   " + str(passcuts[14] )
        print "total passing W subjet tau21 cut:        " + str(passcuts[15])
        print "total passing W subjet mass cut:         " + str(passcuts[16] )


        print "total passing pre-selection : " + str(NpassPre ) 

        print "total passing final selection : " + str(NpassPost )


    ts = (time.time() -startTime)

    unitIs = 'Seconds'
    if ts > 60. :
        ts /= 60.
        unitIs = 'Minutes'
        if ts > 60. :
            ts /= 60.
            unitIs = 'Hours' 

    print ('The script took {0}  {1}!'.format(   ts  , unitIs    ) )

    fout.cd()
    fout.Write()
    fout.Close()

if __name__ == "__main__" :
    Wtag_Selector(sys.argv)
