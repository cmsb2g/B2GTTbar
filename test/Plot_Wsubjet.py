#! /usr/bin/env python


## _________                _____.__                            __  .__               
## \_   ___ \  ____   _____/ ____\__| ____  __ ______________ _/  |_|__| ____   ____  
## /    \  \/ /  _ \ /    \   __\|  |/ ___\|  |  \_  __ \__  \\   __\  |/  _ \ /    \ 
## \     \___(  <_> )   |  \  |  |  / /_/  >  |  /|  | \// __ \|  | |  (  <_> )   |  \
##  \______  /\____/|___|  /__|  |__\___  /|____/ |__|  (____  /__| |__|\____/|___|  /
##         \/            \/        /_____/                   \/                    \/ 
import sys
import math
import array as array
from optparse import OptionParser

# This script reads a TTree and 

def Plot_Wsubjet(argv) : 
    parser = OptionParser()

    parser.add_option('--filestr', type='string', action='store',
                      dest='filestr',
                      default = '',
                      help='File string')
        
    parser.add_option('--tau21Cut', type='float', action='store',
                      dest='tau21Cut',
                      default = 0.6,
                      help='Tau21 < tau21Cut')
        
    (options, args) = parser.parse_args(argv)
    argv = []

 #   print '===== Command line options ====='
 #   print options
 #   print '================================'

    import ROOT

    fout= ROOT.TFile('Wmass_pt_binned' + options.filestr + '.root', "RECREATE")


    filesin = [ 'b2gttbar_ttrees/ttjets_ttree_76x_v1p2_puppi.root',
                'b2gttbar_ttrees/singleel_ttree_76x_v1p2_puppi.root', 
                'b2gttbar_ttrees/singlemu_ttree_76x_v1p2_puppi.root' ]

    filetitles =  ["ttjets_PUPPI",
                   "ElData_PUPPI",
                   "MuData_PUPPI"] 

    h_mWsubjet_ttjets = ROOT.TH1F("h_mWsubjet_ttjets", ";m_{SD subjet0} (GeV); ", 300, 0, 300)
    h_ptWsubjet_ttjets = ROOT.TH1F("h_ptWsubjet_ttjets", ";P_{T} SD subjet0 (GeV);  ", 1300, 0, 1300)

    h_mWjet_ttjets = ROOT.TH1F("h_mWjet_ttjets", ";m_{SD jet0} (GeV);  ", 300, 0, 300)
    h_ptWjet_ttjets = ROOT.TH1F("h_ptWjet_ttjets", ";P_{T} SD jet0 (GeV);  ", 1300, 0, 1300)

    h_mWsubjet_b1_ttjets  = ROOT.TH1F("h_mWsubjet_b1_ttjets", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)
    h_mWsubjet_b2_ttjets  = ROOT.TH1F("h_mWsubjet_b2_ttjets", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)
    h_mWsubjet_b3_ttjets  = ROOT.TH1F("h_mWsubjet_b3_ttjets", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)
    h_mWsubjet_b4_ttjets  = ROOT.TH1F("h_mWsubjet_b4_ttjets", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)

    h_mWjet_b1_ttjets  = ROOT.TH1F("h_mWjet_b1_ttjets", ";m_{SD jet0} (GeV);  ", 300, 0, 300)
    h_mWjet_b2_ttjets  = ROOT.TH1F("h_mWjet_b2_ttjets", ";m_{SD jet0} (GeV);  ", 300, 0, 300)
    h_mWjet_b3_ttjets  = ROOT.TH1F("h_mWjet_b3_ttjets", ";m_{SD jet0} (GeV);  ", 300, 0, 300)
    h_mWjet_b4_ttjets  = ROOT.TH1F("h_mWjet_b4_ttjets", ";m_{SD jet0} (GeV);  ", 300, 0, 300)

    h_mWsubjet_EleData = ROOT.TH1F("h_mWsubjet_EleData", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)
    h_ptWsubjet_EleData = ROOT.TH1F("h_ptWsubjet_EleData", ";P_{T} SD subjet0 (GeV);  ", 1300, 0, 1300)

    h_mWsubjet_b1_EleData  = ROOT.TH1F("h_mWsubjet_b1_EleData", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)
    h_mWsubjet_b2_EleData  = ROOT.TH1F("h_mWsubjet_b2_EleData", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)
    h_mWsubjet_b3_EleData  = ROOT.TH1F("h_mWsubjet_b3_EleData", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)
    h_mWsubjet_b4_EleData  = ROOT.TH1F("h_mWsubjet_b4_EleData", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)

    h_mWsubjet_MuData = ROOT.TH1F("h_mWsubjet_MuData", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)
    h_ptWsubjet_MuData = ROOT.TH1F("h_ptWsubjet_MuData", ";P_{T} SD subjet0 (GeV);  ", 1300, 0, 1300)

    h_mWsubjet_b1_MuData  = ROOT.TH1F("h_mWsubjet_b1_MuData", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)
    h_mWsubjet_b2_MuData  = ROOT.TH1F("h_mWsubjet_b2_MuData", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)
    h_mWsubjet_b3_MuData  = ROOT.TH1F("h_mWsubjet_b3_MuData", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)
    h_mWsubjet_b4_MuData  = ROOT.TH1F("h_mWsubjet_b4_MuData", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)

    h_mWsubjet_Data = ROOT.TH1F("h_mWsubjet_Data", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)
    h_ptWsubjet_Data = ROOT.TH1F("h_ptWsubjet_Data", ";P_{T} SD subjet0 (GeV);  ", 1300, 0, 1300)

    h_mWsubjet_b1_Data  = ROOT.TH1F("h_mWsubjet_b1_Data", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)
    h_mWsubjet_b2_Data  = ROOT.TH1F("h_mWsubjet_b2_Data", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)
    h_mWsubjet_b3_Data  = ROOT.TH1F("h_mWsubjet_b3_Data", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)
    h_mWsubjet_b4_Data  = ROOT.TH1F("h_mWsubjet_b4_Data", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)
    
    h_mWsubjet_ttjetsp = ROOT.TH1F("h_mWsubjet_ttjetsp", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)
    h_ptWsubjet_ttjetsp = ROOT.TH1F("h_ptWsubjet_ttjetsp", ";P_{T} SD subjet0 (GeV);  ", 1300, 0, 1300)

    h_mWsubjet_b1_ttjetsp  = ROOT.TH1F("h_mWsubjet_b1_ttjetsp", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)
    h_mWsubjet_b2_ttjetsp  = ROOT.TH1F("h_mWsubjet_b2_ttjetsp", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)
    h_mWsubjet_b3_ttjetsp  = ROOT.TH1F("h_mWsubjet_b3_ttjetsp", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)
    h_mWsubjet_b4_ttjetsp  = ROOT.TH1F("h_mWsubjet_b4_ttjetsp", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)

    h_mWsubjet_Datap = ROOT.TH1F("h_mWsubjet_Datap", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)
    h_ptWsubjet_Datap = ROOT.TH1F("h_ptWsubjet_Datap", ";P_{T} SD subjet0 (GeV);  ", 1300, 0, 1300)

    h_mWsubjet_b1_Datap  = ROOT.TH1F("h_mWsubjet_b1_Datap", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)
    h_mWsubjet_b2_Datap  = ROOT.TH1F("h_mWsubjet_b2_Datap", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)
    h_mWsubjet_b3_Datap  = ROOT.TH1F("h_mWsubjet_b3_Datap", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)
    h_mWsubjet_b4_Datap  = ROOT.TH1F("h_mWsubjet_b4_Datap", ";m_{SD subjet0} (GeV);  ", 300, 0, 300)

    h_mWjet_Data = ROOT.TH1F("h_mWjet_Data", ";m_{SD jet0} (GeV);  ", 300, 0, 300)
    h_ptWjet_Data = ROOT.TH1F("h_ptWjet_Data", ";P_{T} SD jet0 (GeV);  ", 1300, 0, 1300)

    h_mWjet_b1_Data  = ROOT.TH1F("h_mWjet_b1_Data", ";m_{SD jet0} (GeV);  ", 300, 0, 300)
    h_mWjet_b2_Data  = ROOT.TH1F("h_mWjet_b2_Data", ";m_{SD jet0} (GeV);  ", 300, 0, 300)
    h_mWjet_b3_Data  = ROOT.TH1F("h_mWjet_b3_Data", ";m_{SD jet0} (GeV);  ", 300, 0, 300)
    h_mWjet_b4_Data  = ROOT.TH1F("h_mWjet_b4_Data", ";m_{SD jet0} (GeV);  ", 300, 0, 300)
    
    h_mWjet_ttjetsp = ROOT.TH1F("h_mWjet_ttjetsp", ";m_{SD jet0} (GeV);  ", 300, 0, 300)
    h_ptWjet_ttjetsp = ROOT.TH1F("h_ptWjet_ttjetsp", ";P_{T} SD jet0 (GeV);  ", 1300, 0, 1300)

    h_mWjet_b1_ttjetsp  = ROOT.TH1F("h_mWjet_b1_ttjetsp", ";m_{SD jet0} (GeV);  ", 300, 0, 300)
    h_mWjet_b2_ttjetsp  = ROOT.TH1F("h_mWjet_b2_ttjetsp", ";m_{SD jet0} (GeV);  ", 300, 0, 300)
    h_mWjet_b3_ttjetsp  = ROOT.TH1F("h_mWjet_b3_ttjetsp", ";m_{SD jet0} (GeV);  ", 300, 0, 300)
    h_mWjet_b4_ttjetsp  = ROOT.TH1F("h_mWjet_b4_ttjetsp", ";m_{SD jet0} (GeV);  ", 300, 0, 300)

    h_mWjet_Datap = ROOT.TH1F("h_mWjet_Datap", ";m_{SD jet0} (GeV);  ", 300, 0, 300)
    h_ptWjet_Datap = ROOT.TH1F("h_ptWjet_Datap", ";P_{T} SD jet0 (GeV);  ", 1300, 0, 1300)

    h_mWjet_b1_Datap  = ROOT.TH1F("h_mWjet_b1_Datap", ";m_{SD jet0} (GeV);  ", 300, 0, 300)
    h_mWjet_b2_Datap  = ROOT.TH1F("h_mWjet_b2_Datap", ";m_{SD jet0} (GeV);  ", 300, 0, 300)
    h_mWjet_b3_Datap  = ROOT.TH1F("h_mWjet_b3_Datap", ";m_{SD jet0} (GeV);  ", 300, 0, 300)
    h_mWjet_b4_Datap  = ROOT.TH1F("h_mWjet_b4_Datap", ";m_{SD jet0} (GeV);  ", 300, 0, 300)

    h_ptWsubjet_Data_Type1 = ROOT.TH1F("h_ptWsubjet_Data_Type1", ";Jet P_{T} (GeV); ", 150, 0, 1500) # SD subjet0 
    h_ptWsubjet_Data_Type2 = ROOT.TH1F("h_ptWsubjet_Data_Type2", ";Jet P_{T} (GeV); ", 150, 0, 1500)#of leading AK8 jet

    h_ptWsubjet_MC_Type1 = ROOT.TH1F("h_ptWsubjet_MC_Type1", ";Jet P_{T} (GeV); ", 150, 0, 1500) # SD subjet0 
    h_ptWsubjet_MC_Type2 = ROOT.TH1F("h_ptWsubjet_MC_Type2", ";Jet P_{T} (GeV); ", 150, 0, 1500)#of leading AK8 jet

    h_mWjet_EleData = ROOT.TH1F("h_mWjet_EleData", ";m_{SD jet0} (GeV);  ", 300, 0, 300)
    h_ptWjet_EleData = ROOT.TH1F("h_ptWjet_EleData", ";P_{T} SD jet0 (GeV);  ", 1300, 0, 1300)

    h_mWjet_b1_EleData  = ROOT.TH1F("h_mWjet_b1_EleData", ";m_{SD jet0} (GeV);  ", 300, 0, 300)
    h_mWjet_b2_EleData  = ROOT.TH1F("h_mWjet_b2_EleData", ";m_{SD jet0} (GeV);  ", 300, 0, 300)
    h_mWjet_b3_EleData  = ROOT.TH1F("h_mWjet_b3_EleData", ";m_{SD jet0} (GeV);  ", 300, 0, 300)
    h_mWjet_b4_EleData  = ROOT.TH1F("h_mWjet_b4_EleData", ";m_{SD jet0} (GeV);  ", 300, 0, 300)

    h_mWjet_MuData = ROOT.TH1F("h_mWjet_MuData", ";m_{SD jet0} (GeV);  ", 300, 0, 300)
    h_ptWjet_MuData = ROOT.TH1F("h_ptWjet_MuData", ";P_{T} SD jet0 (GeV);  ", 1300, 0, 1300)

    h_mWjet_b1_MuData  = ROOT.TH1F("h_mWjet_b1_MuData", ";m_{SD jet0} (GeV);  ", 300, 0, 300)
    h_mWjet_b2_MuData  = ROOT.TH1F("h_mWjet_b2_MuData", ";m_{SD jet0} (GeV);  ", 300, 0, 300)
    h_mWjet_b3_MuData  = ROOT.TH1F("h_mWjet_b3_MuData", ";m_{SD jet0} (GeV);  ", 300, 0, 300)
    h_mWjet_b4_MuData  = ROOT.TH1F("h_mWjet_b4_MuData", ";m_{SD jet0} (GeV);  ", 300, 0, 300)

    ptBs = array.array('d', [200., 300., 400., 500., 800.])
    nptBs = len(ptBs) - 1
    hSF = ROOT.TH1F("hSF", " ;p_{T} of SD subjet 0 (GeV); SF (data/MC)", nptBs, ptBs)



    nMC = 0
    nMCp = 0
    nData = 0
    nDatap = 0

    nMC1 = 0
    nMCp1 = 0
    nData1 = 0
    nDatap1 = 0

    nMC2 = 0
    nMCp2 = 0
    nData2 = 0
    nDatap2 = 0

    nMC3 = 0
    nMCp3 = 0
    nData3 = 0
    nDatap3 = 0

    nMC4 = 0
    nMCp4 = 0
    nData4 = 0
    nDatap4 = 0    

    passkin = 0 
    passkin2 = 0
    pass2D  = 0
    passB   = 0
    passT   = 0 
    passLep = 0
    passOp  = 0
    passEle   = 0
    passMu   = 0
    pass3   = 0

    for ifile, filee in enumerate(filesin) :
        fin = ROOT.TFile.Open( filee )
#        print "Opened the File!  " + filee
#        print "This is file number : " + str(ifile)
        t =  fin.Get("TreeSemiLept") 
        if ifile == 0 : 
            fin2 = ROOT.TFile.Open( "b2gttbar_ttrees/ttjets_ttree_76x_v1p2.root" )
        if ifile == 1 : 
            fin2 = ROOT.TFile.Open( "b2gttbar_ttrees/singleel_ttree_76x_v1p2.root" )
        if ifile == 2 : 
            fin2 = ROOT.TFile.Open( "b2gttbar_ttrees/singlemu_ttree_76x_v1p2.root" )

        t2 = fin2.Get("TreeSemiLept")

        if (ifile  > 0 ): 
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
        FatJetSDbdiscW      = array.array('f', [-1.])
        FatJetSDbdiscB      = array.array('f', [-1.])
        FatJetSDmaxbdisc    = array.array('f', [-1.])
        FatJetSDsubjetWpt   = array.array('f', [-1.])
        FatJetSDsubjetWmass = array.array('f', [-1.])
        FatJetSDsubjetWp4   = array.array('f', [-1.])
        FatJetSDsubjetWtau1   = array.array('f', [-1.])
        FatJetSDsubjetWtau2   = array.array('f', [-1.])
        FatJetSDsubjetWtau3   = array.array('f', [-1.])
        FatJetSDsubjetBpt   = array.array('f', [-1.])
        FatJetSDsubjetBmass = array.array('f', [-1.])
        FatJetSDsubjetBp4   = array.array('f', [-1.])
        FatJetSDsubjetBtau1   = array.array('f', [-1.])
        FatJetSDsubjetBtau2   = array.array('f', [-1.])
        FatJetSDsubjetBtau3   = array.array('f', [-1.])
        FatJetSDsubjet0pt   = array.array('f', [-1.])
        FatJetSDsubjet0mass = array.array('f', [-1.])
        FatJetSDsubjet0area = array.array('f', [-1.])
        FatJetSDsubjet0flav = array.array('f', [-1.])
        FatJetSDsubjet0tau1 = array.array('f', [-1.])
        FatJetSDsubjet0tau2 = array.array('f', [-1.])
        FatJetSDsubjet0tau3 = array.array('f', [-1.])
        FatJetSDsubjet1pt   = array.array('f', [-1.])
        FatJetSDsubjet1mass = array.array('f', [-1.])
        FatJetSDsubjet1area = array.array('f', [-1.])
        FatJetSDsubjet1flav = array.array('f', [-1.])
        FatJetSDsubjet1tau1 = array.array('f', [-1.])
        FatJetSDsubjet1tau2 = array.array('f', [-1.])
        FatJetSDsubjet1tau3 = array.array('f', [-1.])
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
        BJetbDisc2           = array.array('f', [-1.])
        BJetPt2              = array.array('f', [-1.])
        BJetEta2             = array.array('f', [-1.])
        BJetPhi2             = array.array('f', [-1.])
        BJetMass2            = array.array('f', [-1.])
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
        SemiLepMETpx        = array.array('f', [-1.])
        SemiLepMETpy        = array.array('f', [-1.])
        SemiLepMETpt        = array.array('f', [-1.])
        SemiLepMETphi       = array.array('f', [-1.])
        SemiLepNvtx         = array.array('f', [-1.])
        SemiLepEventWeight  = array.array('f', [-1.])
        SemilLepTTmass      = array.array('f', [-1.])  
        DeltaPhiLepFat      = array.array('f', [-1.]) 
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

        if (ifile  > 0 ):  
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
        t.SetBranchAddress('FatJetSDsubjetWmass' , FatJetSDsubjetWmass )
        t.SetBranchAddress('FatJetSDsubjetWtau1' , FatJetSDsubjetWtau1 )
        t.SetBranchAddress('FatJetSDsubjetWtau2' , FatJetSDsubjetWtau2 )
        t.SetBranchAddress('FatJetSDsubjetWtau3' , FatJetSDsubjetWtau3 )
        t.SetBranchAddress('FatJetSDsubjetBpt'   , FatJetSDsubjetBpt   )
        t.SetBranchAddress('FatJetSDsubjetBmass' , FatJetSDsubjetBmass )
        t.SetBranchAddress('FatJetSDsubjetBtau1' , FatJetSDsubjetBtau1 )
        t.SetBranchAddress('FatJetSDsubjetBtau2' , FatJetSDsubjetBtau2 )
        t.SetBranchAddress('FatJetSDsubjetBtau3' , FatJetSDsubjetBtau3 )
        t.SetBranchAddress('FatJetSDsubjet0tau1' , FatJetSDsubjetWtau1 )
        t.SetBranchAddress('FatJetSDsubjet0tau2' , FatJetSDsubjetWtau2 )
        t.SetBranchAddress('FatJetSDsubjet0tau3' , FatJetSDsubjetWtau3 )
        t.SetBranchAddress('FatJetSDsubjet1tau1' , FatJetSDsubjetWtau1 )
        t.SetBranchAddress('FatJetSDsubjet1tau2' , FatJetSDsubjetWtau2 )
        t.SetBranchAddress('FatJetSDsubjet1tau3' , FatJetSDsubjetWtau3 )
        t.SetBranchAddress('BJetbDisc' , BJetbDisc )
        t.SetBranchAddress('BJetPt' , BJetPt )
        t.SetBranchAddress('BJetEta' , BJetEta )
        t.SetBranchAddress('BJetPhi' , BJetPhi )
        t.SetBranchAddress('BJetMass' , BJetMass )
        t2.SetBranchAddress('BJetbDisc' , BJetbDisc2 )
        t2.SetBranchAddress('BJetPt' , BJetPt2 )
        t2.SetBranchAddress('BJetEta' , BJetEta2 )
        t2.SetBranchAddress('BJetPhi' , BJetPhi2 )
        t2.SetBranchAddress('BJetMass' , BJetMass2 )
        t.SetBranchAddress('LeptonType'          , LeptonType          )
        t.SetBranchAddress('LeptonPt'            , LeptonPt            )
        t.SetBranchAddress('LeptonEta'           , LeptonEta           )
        t.SetBranchAddress('LeptonPhi'           , LeptonPhi           )
        t.SetBranchAddress('LeptonEnergy'        , LeptonEnergy        )
        t.SetBranchAddress('LeptonIso'           , LeptonIso           )
        t.SetBranchAddress('LeptonPtRel'         , LeptonPtRel         )
        t.SetBranchAddress('LeptonDRMin'         , LeptonDRMin         )
        t.SetBranchAddress('SemiLepMETpt'        , SemiLepMETpt        )
        t.SetBranchAddress('SemiLepMETphi'       , SemiLepMETphi       )
        t.SetBranchAddress('SemiLepNvtx'         , SemiLepNvtx         )
        t.SetBranchAddress('DeltaPhiLepFat'      , DeltaPhiLepFat      )
        t2.SetBranchAddress('AK4bDisc'           , AK4bDisc            )
        t2.SetBranchAddress('NearestAK4JetPt'     , NearestAK4JetPt2     )
        t2.SetBranchAddress('NearestAK4JetEta'    , NearestAK4JetEta2    )
        t2.SetBranchAddress('NearestAK4JetPhi'    , NearestAK4JetPhi2    )
        t2.SetBranchAddress('NearestAK4JetMass'   , NearestAK4JetMass2   )
        t.SetBranchAddress('NearestAK4JetPt'     , NearestAK4JetPt     )
        t.SetBranchAddress('NearestAK4JetEta'    , NearestAK4JetEta    )
        t.SetBranchAddress('NearestAK4JetPhi'    , NearestAK4JetPhi    )
        t.SetBranchAddress('NearestAK4JetMass'   , NearestAK4JetMass   )
        t.SetBranchAddress('SemiLepEventWeight'     ,  SemiLepEventWeight   )
        t.SetBranchAddress('SemiLeptRunNum'         ,  SemiLeptRunNum       )
        t.SetBranchAddress('SemiLeptLumiBlock'      ,  SemiLeptLumiBlock    )
        t.SetBranchAddress('SemiLeptEventNum'       ,  SemiLeptEventNum     )
        t2.SetBranchAddress('SemiLeptEventNum'       ,  SemiLeptEventNum2     )
        t.SetBranchAddress('PU_CorrDn'       ,  PU_CorrDn     )
        t.SetBranchAddress('PU_CorrUp'       ,  PU_CorrUp     )
 
        t.AddFriend(t2)

        t.SetBranchStatus ('*', 0)
        t.SetBranchStatus ('FatJetPt', 1)
        t.SetBranchStatus ('FatJetEta', 1)
        t.SetBranchStatus ('FatJetPhi', 1)
        t.SetBranchStatus ('FatJetMass', 1)
        t.SetBranchStatus ('FatJetMassSoftDrop', 1)
        t.SetBranchStatus ('FatJetTau32', 1)
        t.SetBranchStatus ('FatJetTau21', 1)
        t.SetBranchStatus ('FatJetRhoRatio', 1)
        #t.SetBranchStatus('BJetbDisc' , 1 )
        t.SetBranchStatus('BJetPt' , 1)
        t.SetBranchStatus('BJetEta' , 1)
        t.SetBranchStatus('BJetPhi' , 1 )
        t.SetBranchStatus('BJetMass' , 1)
        t2.SetBranchStatus('BJetbDisc' , 1 )
        t2.SetBranchStatus('BJetPt' , 1)
        t2.SetBranchStatus('BJetEta' , 1)
        t2.SetBranchStatus('BJetPhi' , 1 )
        t2.SetBranchStatus('BJetMass' , 1)
        t.SetBranchStatus('FatJetSDsubjetWpt',1)
        t.SetBranchStatus('FatJetSDsubjetWtau1',1)
        t.SetBranchStatus('FatJetSDsubjetWtau2',1)
        t.SetBranchStatus('FatJetSDsubjetWtau3',1)
        t.SetBranchStatus('FatJetSDsubjetBtau1',1)
        t.SetBranchStatus('FatJetSDsubjetBtau2',1)
        t.SetBranchStatus('FatJetSDsubjetBtau3',1)
        t.SetBranchStatus('FatJetSDsubjet0tau1',1)
        t.SetBranchStatus('FatJetSDsubjet0tau2',1)
        t.SetBranchStatus('FatJetSDsubjet0tau3',1)
        t.SetBranchStatus('FatJetSDsubjet1tau1',1)
        t.SetBranchStatus('FatJetSDsubjet1tau2',1)
        t.SetBranchStatus('FatJetSDsubjet1tau3',1)
        t.SetBranchStatus('FatJetSDsubjetBpt',1)
        t.SetBranchStatus('FatJetSDsubjetWmass',1)
        t.SetBranchStatus ('SemiLeptTrig', 1)
        t2.SetBranchStatus ('AK4bDisc', 1)
        t.SetBranchStatus ('NearestAK4JetPt'   ,1 )
        t.SetBranchStatus ('NearestAK4JetEta'  ,1 )
        t.SetBranchStatus ('NearestAK4JetPhi'  ,1 )
        t.SetBranchStatus ('NearestAK4JetMass' ,1 )
        t2.SetBranchStatus ('NearestAK4JetPt'   ,1 )
        t2.SetBranchStatus ('NearestAK4JetEta'  ,1 )
        t2.SetBranchStatus ('NearestAK4JetPhi'  ,1 )
        t2.SetBranchStatus ('NearestAK4JetMass' ,1 )
        t.SetBranchStatus ('SemiLepMETpt' , 1 )
        t.SetBranchStatus ('SemiLepMETphi' , 1 )
        t.SetBranchStatus ('LeptonType'          , 1 )
        t.SetBranchStatus ('LeptonPt'            , 1)
        t.SetBranchStatus ('LeptonEta'           , 1)
        t.SetBranchStatus ('LeptonPhi'           , 1)
        t.SetBranchStatus ('LeptonEnergy'        , 1)
        t.SetBranchStatus ('LeptonIso'           , 1)
        t.SetBranchStatus ('LeptonPtRel'         , 1)
        t.SetBranchStatus ('LeptonDRMin'         , 1)
        t.SetBranchStatus ('SemiLepEventWeight'  , 1) 
        t.SetBranchStatus ('SemiLeptRunNum'      , 1)
        t.SetBranchStatus ('SemiLeptLumiBlock'   , 1)
        t.SetBranchStatus ('SemiLeptEventNum'    , 1)
        t2.SetBranchStatus ('SemiLeptEventNum'    , 1)
        t.SetBranchStatus ('PU_CorrDn'           , 1)
        t.SetBranchStatus ('PU_CorrUp'           , 1)


        entries = t.GetEntriesFast()
        #eventsToRun = 10000
        eventsToRun = entries
#        print entries


        for jentry in xrange( eventsToRun ):
            if jentry % 100000 == 0 :
                print 'processing ' + str(jentry)
            # get the next tree in the chain and verify
            ientry = t.GetEntry( jentry )
            if ientry < 0:
                break

            # Muons only for now
      #      if LeptonType[0] != 13 :
      #          continue

            # Muon triggers only for now
       #     if options.isData and SemiLeptTrig[0] != 3  :
       #         continue



           # if (jentry == 5 or jentry == 500  ) : print "Pt of leading AK8 jet for events 5 and 500 : " + str(FatJetPt[0])
            #hadTopCandP4 = ROOT.TLorentzVector()
            #hadTopCandP4.SetPtEtaPhiM( FatJetPt[0], FatJetEta[0], FatJetPhi[0], FatJetMass[0])
            
            bJetCandP4puppi0 = ROOT.TLorentzVector()
            bJetCandP4puppi0.SetPtEtaPhiM( BJetPt[0], BJetEta[0], BJetPhi[0], BJetMass[0])
            bJetCandP4puppiEventnum = SemiLeptEventNum[0]
            bJetCandP4puppi0Bdisc = -1.0
            #print "b jet PUPPI event number : " + str(bJetCandP4puppiEventnum)

            '''
            bJetCandP4chs0 = ROOT.TLorentzVector()
            bJetCandP4chs0.SetPtEtaPhiM( BJetPt2[0], BJetEta2[0], BJetPhi2[0], BJetMass2[0])
            bJetCandP4chsBdisc = [ BJetbDisc2[0] ]
            bJetCandP4chs0Eventnum = SemiLeptEventNum2[0]

            if len(BJetPt2) == 2:
                bJetCandP4chs1 = ROOT.TLorentzVector()
                bJetCandP4chs1.SetPtEtaPhiM( BJetPt2[1], BJetEta2[1], BJetPhi2[1], BJetMass2[1])
                bJetCandP4chsBdisc = [  BJetbDisc2[0], BJetbDisc2[1] ]
                bJetCandP4chs1Eventnum = SemiLeptEventNum2[1]

            if len(BJetPt2) > 2:
                bJetCandP4chs2 = ROOT.TLorentzVector()
                bJetCandP4chs2.SetPtEtaPhiM( BJetPt2[2], BJetEta2[2], BJetPhi2[2], BJetMass2[2])
                bJetCandP4chsBdisc = [  BJetbDisc2[0], BJetbDisc2[1], BJetbDisc2[2]  ]
                bJetCandP4chs2Eventnum = SemiLeptEventNum2[2]

            #print "b jet CHS event number : " + str(bJetCandP4chs0Eventnum)

            
            DrMin = 9999.0
            dr = [bJetCandP4puppi0.DeltaR(bJetCandP4chs0), bJetCandP4puppi0.DeltaR(bJetCandP4chs1), bJetCandP4puppi0.DeltaR(bJetCandP4chs2) ]
            #fill the dr array 
            for i, s in dr :
                if s < DrMin:
                    DrMin = s
                    bJetCandP4puppi0Bdisc = 
                    bdisc = AK4bDisc[i]
            '''
            bdisc = BJetbDisc2[0]

            nuCandP4 = ROOT.TLorentzVector( )
            nuCandP4.SetPtEtaPhiM( SemiLepMETpt[0], 0, SemiLepMETphi[0], SemiLepMETpt[0] )
            theLepton = ROOT.TLorentzVector()
            theLepton.SetPtEtaPhiE( LeptonPt[0], LeptonEta[0], LeptonPhi[0], LeptonEnergy[0] ) # Assume massless
            
            # FatJetSDpt = m / (R*sqrt(rhoRatio)) 
            # using SD pts for both types
            FatJetSD_m = FatJetMassSoftDrop[0]
            Rhorat = FatJetRhoRatio[0]
            #print "Fat Jet Rho Ratio :" + str(Rhorat)
            if Rhorat > 0.001 :
                sqrtRhorat = math.sqrt(Rhorat)
                FatJetSD_pt = FatJetSD_m / (0.8 * sqrtRhorat  )
            else :
                FatJetSD_pt = 0.
            tau32 = FatJetTau32[0]
            tau21 = FatJetTau21[0]
            mass_sd = FatJetMassSoftDrop[0]


            W_m = FatJetSDsubjetWmass[0]
            W_pt = FatJetSDsubjetWpt[0]
            if FatJetSDsubjetWtau1[0] > 0.001 :
                W_tau21 = FatJetSDsubjetWtau2[0] / FatJetSDsubjetWtau1[0]
            else :
                W_tau21 = 1.0
            B_pt = FatJetSDsubjetBpt[0]
            MET_pt = SemiLepMETpt[0]
            W_pt2 = FatJetPt[0]




            ##  ____  __.__                              __  .__         __________                     
            ## |    |/ _|__| ____   ____   _____ _____ _/  |_|__| ____   \______   \ ____   ____  ____  
            ## |      < |  |/    \_/ __ \ /     \\__  \\   __\  |/ ___\   |       _// __ \_/ ___\/  _ \ 
            ## |    |  \|  |   |  \  ___/|  Y Y  \/ __ \|  | |  \  \___   |    |   \  ___/\  \__(  <_> )
            ## |____|__ \__|___|  /\___  >__|_|  (____  /__| |__|\___  >  |____|_  /\___  >\___  >____/ 
            ##         \/       \/     \/      \/     \/             \/          \/     \/     \/       

            # Now we do our kinematic calculation based on the semi-leptonic Z' selection detailed in  B2G-15-002 


            passKin = FatJetPt[0] > 400. and W_pt > 0. 
            passKin2 =  FatJetPt[0] > 200. #and W_m < 1.
            passWPre = W_m > 50. and W_pt > 0. 
            passWPre2 = FatJetSD_m > 50. and FatJetPt[0] > 200. # and W_m >50.
            passTopTag = tau32 < 0.8 and mass_sd > 110. and mass_sd < 250.
            pass2DCut = LeptonPtRel[0] > 20. or LeptonDRMin[0] > 0.4 # B2G-15-002 uses  LeptonPtRel[0] > 20.or LeptonDRMin[0] > 0.4 (was 55.0 here)
            passBtag = bdisc > 0.7

            passWPost = (65. < W_m < 105.) and W_tau21 < options.tau21Cut #65 to 130 before
            passWPost2 = (65. < FatJetSD_m < 105.) and tau21 < options.tau21Cut
            passEleMETcut =  LeptonType[0] == 1 and MET_pt > 120. and theLepton.Perp() > 55. #110.
            # B2G-15-002  uses ( theLepton.Perp() + MET_pt ) > 150. (was previously 250 here) 
            passMuHtLepcut = LeptonType[0] == 2 and ( theLepton.Perp() + MET_pt ) > 150. and theLepton.Perp() > 55.
            passLepcut = passEleMETcut or passMuHtLepcut 

            if pass2DCut : 
                pass2D += 1

            if passBtag :
                passB += 1
           
            if passTopTag :
                passT += 1

            if passLepcut :
                passLep += 1
            if passEleMETcut :
                passEle +=1
            if passMuHtLepcut :
                passMu +=1


            #if (ifile > 0 and passKin) :
                #h_ptWsubjet_Data_Type1.Fill(W_pt, 1)
                #print "Pt of W tagged subjet of the AK8 jet for events 5 and 500 : " + str( W_pt)
            #if (ifile > 0 and passKin2 ) :
                #h_ptWsubjet_Data_Type2.Fill( FatJetSD_pt , 1)   
                #print "Pt of W tagged AK8 jet for events 5 and 500 : " + str( W_pt)      
            if  passTopTag and pass2DCut and passLepcut: # and passBtag :  
                if passKin and passWPre:
                    #if ( ifile == 1 or ifile == 2 ):
                    #    h_ptWsubjet_Data_Type1.Fill(W_pt, 1)
                    passkin += 1
                    if (ifile == 0 ): #ttjets
                        nMCp +=1
                        h_mWsubjet_ttjetsp.Fill(W_m , 1 )
                        h_ptWsubjet_ttjetsp.Fill(W_pt , 1 )

                        if ( W_pt > 200.0 and W_pt < 300.0 ) : 
                            nMCp1 +=1
                            h_mWsubjet_b1_ttjetsp.Fill(W_m , 1 )

                        if ( W_pt > 300.0 and W_pt < 400.0 ) :
                            nMCp2 +=1 
                            h_mWsubjet_b2_ttjetsp.Fill(W_m , 1 )

                        if ( W_pt > 400.0 and W_pt < 500.0 ) : 
                            nMCp3 +=1
                            h_mWsubjet_b3_ttjetsp.Fill(W_m , 1 )

                        if ( W_pt > 500.0 ) : 
                            nMCp4 +=1
                            h_mWsubjet_b4_ttjetsp.Fill(W_m , 1 )
                    if (ifile != 0 ):
                        nDatap +=1
                        h_mWsubjet_Datap.Fill(W_m , 1 )
                        h_ptWsubjet_Datap.Fill(W_pt , 1 )

                        if ( W_pt > 200.0 and W_pt < 300.0 ) : 
                            nDatap1 +=1
                            h_mWsubjet_b1_Datap.Fill(W_m , 1 )

                        if ( W_pt > 300.0 and W_pt < 400.0 ) : 
                            nDatap2 +=1
                            h_mWsubjet_b2_Datap.Fill(W_m , 1 )

                        if ( W_pt > 400.0 and W_pt < 500.0 ) : 
                            nDatap3 +=1
                            h_mWsubjet_b3_Datap.Fill(W_m , 1 )

                        if ( W_pt > 500.0 ) : 
                            nDatap4 +=1
                            h_mWsubjet_b4_Datap.Fill(W_m , 1 )
                    if passWPost : #ttjets.root    
                        passOp += 1 
                        if (ifile == 0 ): #ttjets.root
                            nMC +=1
                            h_ptWsubjet_MC_Type1.Fill(W_pt, 1)
                            h_mWsubjet_ttjets.Fill(W_m , 1 )
                            h_ptWsubjet_ttjets.Fill(W_pt , 1 )

                            if ( W_pt > 200.0 and W_pt < 300.0 ) : 
                                nMC1 +=1
                                h_mWsubjet_b1_ttjets.Fill(W_m , 1 )

                            if ( W_pt > 300.0 and W_pt < 400.0 ) : 
                                nMC2 +=1
                                h_mWsubjet_b2_ttjets.Fill(W_m , 1 )

                            if ( W_pt > 400.0 and W_pt < 500.0 ) : 
                                nMC3 +=1
                                h_mWsubjet_b3_ttjets.Fill(W_m , 1 )

                            if ( W_pt > 500.0 ) : 
                                nMC4 +=1
                                h_mWsubjet_b4_ttjets.Fill(W_m , 1 )
                        if (ifile == 1  ):
                            h_mWsubjet_EleData.Fill(W_m , 1 )
                            h_ptWsubjet_EleData.Fill(W_pt , 1 )

                            if ( W_pt > 200.0 and W_pt < 300.0 ) : 
                                h_mWsubjet_b1_EleData.Fill(W_m , 1 )

                            if ( W_pt > 300.0 and W_pt < 400.0 ) : 
                                h_mWsubjet_b2_EleData.Fill(W_m , 1 )

                            if ( W_pt > 400.0 and W_pt < 500.0 ) : 
                                h_mWsubjet_b3_EleData.Fill(W_m , 1 )

                            if ( W_pt > 500.0 ) : 
                                h_mWsubjet_b4_EleData.Fill(W_m , 1 )

                        if (ifile == 2 ):
                            h_mWsubjet_MuData.Fill(W_m , 1 )
                            h_ptWsubjet_MuData.Fill(W_pt , 1 )

                            if ( W_pt > 200.0 and W_pt < 300.0 ) : 
                                h_mWsubjet_b1_MuData.Fill(W_m , 1 )

                            if ( W_pt > 300.0 and W_pt < 400.0 ) : 
                                h_mWsubjet_b2_MuData.Fill(W_m , 1 )

                            if ( W_pt > 400.0 and W_pt < 500.0 ) : 
                                h_mWsubjet_b3_MuData.Fill(W_m , 1 )

                            if ( W_pt > 500.0 ) : 
                                h_mWsubjet_b4_MuData.Fill(W_m , 1 )
                        if (ifile != 0 ):
                            nData +=1
                            h_ptWsubjet_Data_Type1.Fill(W_pt, 1)
                            h_mWsubjet_Data.Fill(W_m , 1 )
                            h_ptWsubjet_Data.Fill(W_pt , 1 )

                            if ( W_pt > 200.0 and W_pt < 300.0 ) : 
                                nData1 +=1
                                h_mWsubjet_b1_Data.Fill(W_m , 1 )

                            if ( W_pt > 300.0 and W_pt < 400.0 ) : 
                                nData2 +=1
                                h_mWsubjet_b2_Data.Fill(W_m , 1 )

                            if ( W_pt > 400.0 and W_pt < 500.0 ) : 
                                nData3 +=1
                                h_mWsubjet_b3_Data.Fill(W_m , 1 )

                            if ( W_pt > 500.0 ) : 
                                nData4 +=1
                                h_mWsubjet_b4_Data.Fill(W_m , 1 )
       
                if passKin2 and passWPre2:
                   # if (ifile == 1 or ifile == 2) :
                   #     h_ptWsubjet_Data_Type2.Fill( FatJetSD_pt , 1) 
                    passkin2 += 1
                    if (ifile == 0 ): #ttjets
                        nMCp +=1
                        h_mWjet_ttjetsp.Fill(FatJetSD_m , 1 )
                        h_ptWjet_ttjetsp.Fill(FatJetSD_pt , 1 )

                        if ( FatJetSD_pt > 200.0 and FatJetSD_pt < 300.0 ) : 
                            nMCp1 +=1
                            h_mWjet_b1_ttjetsp.Fill(FatJetSD_m , 1 )

                        if ( FatJetSD_pt > 300.0 and FatJetSD_pt < 400.0 ) :
                            nMCp2 +=1 
                            h_mWjet_b2_ttjetsp.Fill(FatJetSD_m , 1 )

                        if ( FatJetSD_pt > 400.0 and FatJetSD_pt < 500.0 ) : 
                            nMCp3 +=1
                            h_mWjet_b3_ttjetsp.Fill(FatJetSD_m , 1 )

                        if ( FatJetSD_pt > 500.0 ) : 
                            nMCp4 +=1
                            h_mWjet_b4_ttjetsp.Fill(FatJetSD_m , 1 )
                    if (ifile != 0 ):
                        nDatap +=1
                        h_mWjet_Datap.Fill(FatJetSD_m , 1 )
                        h_ptWjet_Datap.Fill(FatJetSD_pt , 1 )

                        if ( FatJetSD_pt > 200.0 and FatJetSD_pt < 300.0 ) : 
                            nDatap1 +=1
                            h_mWjet_b1_Datap.Fill(FatJetSD_m , 1 )

                        if ( FatJetSD_pt > 300.0 and FatJetSD_pt < 400.0 ) : 
                            nDatap2 +=1
                            h_mWjet_b2_Datap.Fill(FatJetSD_m , 1 )

                        if ( FatJetSD_pt > 400.0 and FatJetSD_pt < 500.0 ) : 
                            nDatap3 +=1
                            h_mWjet_b3_Datap.Fill(FatJetSD_m , 1 )

                        if ( FatJetSD_pt > 500.0 ) : 
                            nDatap4 +=1
                            h_mWjet_b4_Datap.Fill(FatJetSD_m , 1 )
                    if passWPost2 :   
                        passOp += 1 
                        if (ifile == 0 ): #ttjets.root
                            nMC +=1
                            h_ptWsubjet_MC_Type2.Fill( FatJetSD_pt , 1)
                            h_mWjet_ttjets.Fill(FatJetSD_m , 1 )
                            h_ptWjet_ttjets.Fill(FatJetSD_pt , 1 )

                            if ( FatJetSD_pt > 200.0 and FatJetSD_pt < 300.0 ) : 
                                nMC1 +=1
                                h_mWjet_b1_ttjets.Fill(FatJetSD_m , 1 )

                            if ( FatJetSD_pt > 300.0 and FatJetSD_pt < 400.0 ) : 
                                nMC2 +=1
                                h_mWjet_b2_ttjets.Fill(FatJetSD_m , 1 )

                            if ( FatJetSD_pt > 400.0 and FatJetSD_pt < 500.0 ) : 
                                nMC3 +=1
                                h_mWjet_b3_ttjets.Fill(FatJetSD_m , 1 )

                            if ( FatJetSD_pt > 500.0 ) : 
                                nMC4 +=1
                                h_mWjet_b4_ttjets.Fill(FatJetSD_m , 1 )
                        if (ifile == 1 ):
                            h_mWjet_EleData.Fill(FatJetSD_m , 1 )
                            h_ptWjet_EleData.Fill(FatJetSD_pt , 1 )

                            if ( FatJetSD_pt > 200.0 and FatJetSD_pt < 300.0 ) : 
                                h_mWjet_b1_EleData.Fill(FatJetSD_m , 1 )

                            if ( FatJetSD_pt > 300.0 and FatJetSD_pt < 400.0 ) : 
                                h_mWjet_b2_EleData.Fill(FatJetSD_m , 1 )

                            if ( FatJetSD_pt > 400.0 and FatJetSD_pt < 500.0 ) : 
                                h_mWjet_b3_EleData.Fill(FatJetSD_m , 1 )

                            if ( FatJetSD_pt > 500.0 ) : 
                                h_mWjet_b4_EleData.Fill(FatJetSD_m , 1 )

                        if (ifile == 2):
                            h_mWjet_MuData.Fill(FatJetSD_m , 1 )
                            h_ptWjet_MuData.Fill(FatJetSD_pt , 1 )

                            if ( FatJetSD_pt > 200.0 and FatJetSD_pt < 300.0 ) : 
                                h_mWjet_b1_MuData.Fill(FatJetSD_m , 1 )

                            if ( FatJetSD_pt > 300.0 and FatJetSD_pt < 400.0 ) : 
                                h_mWjet_b2_MuData.Fill(FatJetSD_m , 1 )

                            if ( FatJetSD_pt > 400.0 and FatJetSD_pt < 500.0 ) : 
                                h_mWjet_b3_MuData.Fill(FatJetSD_m , 1 )

                            if ( FatJetSD_pt > 500.0 ) : 
                                h_mWjet_b4_MuData.Fill(FatJetSD_m , 1 )
                        if (ifile != 0 ):
                            nData +=1
                            h_ptWsubjet_Data_Type2.Fill( FatJetSD_pt , 1)
                            h_mWjet_Data.Fill(FatJetSD_m , 1 )
                            h_ptWjet_Data.Fill(FatJetSD_pt , 1 )

                            if ( FatJetSD_pt > 200.0 and FatJetSD_pt < 300.0 ) : 
                                nData1 +=1
                                h_mWjet_b1_Data.Fill(FatJetSD_m , 1 )

                            if ( FatJetSD_pt > 300.0 and FatJetSD_pt < 400.0 ) : 
                                nData2 +=1
                                h_mWjet_b2_Data.Fill(FatJetSD_m , 1 )

                            if ( FatJetSD_pt > 400.0 and FatJetSD_pt < 500.0 ) : 
                                nData3 +=1
                                h_mWjet_b3_Data.Fill(FatJetSD_m , 1 )

                            if ( FatJetSD_pt > 500.0 ) : 
                                nData4 +=1
                                h_mWjet_b4_Data.Fill(FatJetSD_m , 1 )     

    #ptBs = [200.0, 300.0, 400.0, 500.0]

    #h = ROOT.TH1F("jms", "jms", nptBs, ptBs )


#   SF =  ( nData / nDatap ) / ( nMC / nMCp )
    nDBs = [float(nData1), float(nData2), float(nData3), float(nData4)]
    nDpBs = [float(nDatap1), float(nDatap2), float(nDatap3), float(nDatap4)]
    nMCBs = [float(nMC1), float(nMC2), float(nMC3), float(nMC4)]
    nMCpBs = [float(nMCp1), float(nMCp2), float(nMCp3), float(nMCp4)]

    print "TYPE 1:"
    print "N pass post W tag Data pt 200-300 : " + str(nDBs[0])
    print "N pass pre W tag Data pt 200-300 : " + str(nDpBs[0])

    print "N pass post W tag Data pt 300-400 : " + str(nDBs[1])
    print "N pass pre W tag Data pt 300-400 : " + str(nDpBs[1])

    print "N pass post W tag Data pt 400-500 : " + str(nDBs[2])
    print "N pass pre W tag Data pt 400-500 : " + str(nDpBs[2])

    print "N pass post W tag Data pt 500-inf : " + str(nDBs[3])
    print "N pass pre W tag Data pt 500-inf : " + str(nDpBs[3])

    print "N pass post W tag MC pt 200-300 : " + str(nMCBs[0])
    print "N pass pre W tag MC pt 200-300 : " + str(nMCpBs[0])

    print "N pass post W tag MC pt 300-400 : " + str(nMCBs[1])
    print "N pass pre W tag MC pt 300-400 : " + str(nMCpBs[1])

    print "N pass post W tag MC pt 400-500 : " + str(nMCBs[2])
    print "N pass pre W tag MC pt 400-500 : " + str(nMCpBs[2])

    print "N pass post W tag MC pt 500-inf : " + str(nMCBs[3])
    print "N pass pre W tag MC pt 500-inf : " + str(nMCpBs[3])

    for ipt in xrange(0,len(ptBs) - 1) :
        pt = float(ptBs[ipt])
        if pt > 800. : pt = 799.
        if (nDpBs[ipt] > 0 and nMCBs[ipt] > 0) :
            SF =  ( nDBs[ipt] / nDpBs[ipt] ) / ( nMCBs[ipt] / nMCpBs[ipt] )
            SF_sd = SF * math.sqrt(   (- nDBs[ipt] +nDpBs[ipt] ) / (nDBs[ipt] * nDpBs[ipt] )  + (-nMCBs[ipt]+ nMCpBs[ipt]) / (nMCBs[ipt] * nMCpBs[ipt])  )
            print "............................................"
            print "pt Bin lower bound in GeV :  " + str(pt)
            print "Preliminary W tagging SF from subjet w : " + str(SF)
            print "Data efficiency for this  bin" + str(nDBs[ipt] / nDpBs[ipt])
            print "MC efficiency for this  bin" + str(nMCBs[ipt] / nMCpBs[ipt])
            print "standard deviation : " + str(SF_sd)
            print "............................................"
            ibin = hSF.GetXaxis().FindBin(pt)
            hSF.SetBinContent(ibin, SF )
            hSF.SetBinError(ibin, SF_sd)
        else :
            ibin = hSF.GetXaxis().FindBin(pt)
            hSF.SetBinContent(ibin, 0.0 )

    print "Number of events passing basic cuts:"
    print "total passing pre-selection : " + str(passkin)

    print "total passing final selection : " + str(passOp)


    fout.cd() 
    fout.Write()
    fout.Close()

if __name__ == "__main__" :
    Plot_Wsubjet(sys.argv)
