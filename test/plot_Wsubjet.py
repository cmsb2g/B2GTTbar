#! /usr/bin/env python


## _________                _____.__                            __  .__               
## \_   ___ \  ____   _____/ ____\__| ____  __ ______________ _/  |_|__| ____   ____  
## /    \  \/ /  _ \ /    \   __\|  |/ ___\|  |  \_  __ \__  \\   __\  |/  _ \ /    \ 
## \     \___(  <_> )   |  \  |  |  / /_/  >  |  /|  | \// __ \|  | |  (  <_> )   |  \
##  \______  /\____/|___|  /__|  |__\___  /|____/ |__|  (____  /__| |__|\____/|___|  /
##         \/            \/        /_____/                   \/                    \/ 
import sys
import array as array
from optparse import OptionParser


def plot_Wsubjet(argv) : 
    parser = OptionParser()

    parser.add_option('--file_in', type='string', action='store',
                      dest='file_in',
                      help='Input file')

    parser.add_option('--file_out', type='string', action='store',
                      dest='file_out',
                      help='Output file')
    
    parser.add_option('--isData', action='store_true',
                      dest='isData',
                      default = False,
                      help='Is this Data?')

    parser.add_option('--cut', type='string', action='store',
                      dest='cut',
                      default = " ",
                      help='Cut for')
        
    (options, args) = parser.parse_args(argv)
    argv = []

    print '===== Command line options ====='
    print options
    print '================================'

    import ROOT

 #   from leptonic_nu_z_component import solve_nu_tmass, solve_nu

    fout= ROOT.TFile.Open(options.file_out, "RECREATE")

    h_mWsubjet = ROOT.TH1F("h_mWsubjet", ";m_{SD subjet0} (GeV);Number", 400, 0, 400)
    h_ptWsubjet = ROOT.TH1F("h_ptWsubjet", ";P_{T} SD subjet0 (GeV);Number", 1200, 0, 1200)

    fin = ROOT.TFile.Open( str(options.file_in) )
    print "Opened the File!"
    trees = [ fin.Get("TreeSemiLept") ]



    print fin.GetSize() 
   #     print "Tree is EMPTY! Oooh noooooo, my treeee!!!!!" 

    
    for itree,t in enumerate(trees) :

        if options.isData : 
            SemiLeptTrig        = array.array('i', [0]  )
        SemiLeptWeight      = array.array('f', [0.] )
        PUWeight            = array.array('f', [0.] )
        GenWeight           = array.array('f', [0.] )
        FatJetPt            = array.array('f', [-1.])
        FatJetEta           = array.array('f', [-1.])
        FatJetPhi           = array.array('f', [-1.])
        FatJetRap           = array.array('f', [-1.])
        FatJetEnergy        = array.array('f', [-1.])
        FatJetBDisc         = array.array('f', [-1.])
        FatJetMass          = array.array('f', [-1.])
        FatJetMassSoftDrop  = array.array('f', [-1.])
        FatJetTau32         = array.array('f', [-1.])
        FatJetTau21         = array.array('f', [-1.]) 
        FatJetSDbdiscW      = array.array('f', [-1.])
        FatJetSDbdiscB      = array.array('f', [-1.])
        FatJetSDsubjetWpt   = array.array('f', [-1.])
        FatJetSDsubjetWmass = array.array('f', [-1.])
        FatJetSDsubjetBpt   = array.array('f', [-1.])
        FatJetSDsubjetBmass = array.array('f', [-1.])
        FatJetJECUpSys      = array.array('f', [-1.])
        FatJetJECDnSys      = array.array('f', [-1.])
        FatJetJERUpSys      = array.array('f', [-1.])
        FatJetJERDnSys      = array.array('f', [-1.])
        LeptonType          = array.array('i', [-1])
        LeptonPt            = array.array('f', [-1.])
        LeptonEta           = array.array('f', [-1.])
        LeptonPhi           = array.array('f', [-1.])
        LeptonEnergy        = array.array('f', [-1.])
        LeptonIso           = array.array('f', [-1.])
        LeptonPtRel         = array.array('f', [-1.])
        LeptonDRMin         = array.array('f', [-1.])
        SemiLepMETpt        = array.array('f', [-1.])
        SemiLepMETphi       = array.array('f', [-1.])
        SemiLepNvtx         = array.array('f', [-1.])
        DeltaPhiLepFat      = array.array('f', [-1.]) 
        AK4bDisc            = array.array('f', [-1.])
        NearestAK4JetPt     = array.array('f', [-1.])
        NearestAK4JetEta    = array.array('f', [-1.])
        NearestAK4JetPhi    = array.array('f', [-1.])
        NearestAK4JetMass   = array.array('f', [-1.])
        NearestAK4JetJECUpSys = array.array('f', [-1.])
        NearestAK4JetJECDnSys = array.array('f', [-1.])
        NearestAK4JetJERUpSys = array.array('f', [-1.])
        NearestAK4JetJERDnSys = array.array('f', [-1.])
        SemiLeptRunNum        = array.array('f', [-1.])   
        SemiLeptLumiBlock     = array.array('f', [-1.])   
        SemiLeptEventNum      = array.array('f', [-1.])   



        if options.isData : 
            t.SetBranchAddress('SemiLeptTrig'        , SemiLeptTrig        )
        t.SetBranchAddress('SemiLeptWeight'      , SemiLeptWeight      )
        t.SetBranchAddress('PUWeight'            , PUWeight            )
        t.SetBranchAddress('GenWeight'           , GenWeight               )
        t.SetBranchAddress('FatJetPt'            , FatJetPt            )
        t.SetBranchAddress('FatJetEta'           , FatJetEta           )
        t.SetBranchAddress('FatJetPhi'           , FatJetPhi           )
        t.SetBranchAddress('FatJetRap'           , FatJetRap           )
        t.SetBranchAddress('FatJetEnergy'        , FatJetEnergy        )
        t.SetBranchAddress('FatJetBDisc'         , FatJetBDisc         )
        t.SetBranchAddress('FatJetMass'          , FatJetMass           )
        t.SetBranchAddress('FatJetMassSoftDrop'  , FatJetMassSoftDrop  )
        t.SetBranchAddress('FatJetTau32'         , FatJetTau32         )
        t.SetBranchAddress('FatJetTau21'         , FatJetTau21         )
        t.SetBranchAddress('FatJetSDbdiscW'      , FatJetSDbdiscW      )
        t.SetBranchAddress('FatJetSDbdiscB'      , FatJetSDbdiscB              )
        t.SetBranchAddress('FatJetSDsubjetWpt'   , FatJetSDsubjetWpt   )
        t.SetBranchAddress('FatJetSDsubjetWmass' , FatJetSDsubjetWmass )
        t.SetBranchAddress('FatJetSDsubjetBpt'   , FatJetSDsubjetBpt   )
        t.SetBranchAddress('FatJetSDsubjetBmass' , FatJetSDsubjetBmass )
        t.SetBranchAddress('FatJetJECUpSys'      , FatJetJECUpSys      )
        t.SetBranchAddress('FatJetJECDnSys'      , FatJetJECDnSys      )
        t.SetBranchAddress('FatJetJERUpSys'      , FatJetJERUpSys      )
        t.SetBranchAddress('FatJetJERDnSys'      , FatJetJERDnSys      )
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
        t.SetBranchAddress('AK4bDisc'            ,AK4bDisc             )
        t.SetBranchAddress('NearestAK4JetPt'     ,NearestAK4JetPt      )
        t.SetBranchAddress('NearestAK4JetEta'    ,NearestAK4JetEta     )
        t.SetBranchAddress('NearestAK4JetPhi'    ,NearestAK4JetPhi     )
        t.SetBranchAddress('NearestAK4JetMass'   ,NearestAK4JetMass    )
        t.SetBranchAddress('NearestAK4JetJECUpSys'      , NearestAK4JetJECUpSys)
        t.SetBranchAddress('NearestAK4JetJECDnSys'      , NearestAK4JetJECDnSys)
        t.SetBranchAddress('NearestAK4JetJERUpSys'      , NearestAK4JetJERUpSys)
        t.SetBranchAddress('NearestAK4JetJERDnSys'      , NearestAK4JetJERDnSys)
        t.SetBranchAddress('SemiLeptRunNum'         ,  SemiLeptRunNum       )
        t.SetBranchAddress('SemiLeptLumiBlock'      ,  SemiLeptLumiBlock    )
        t.SetBranchAddress('SemiLeptEventNum'       ,  SemiLeptEventNum     )


        t.SetBranchStatus ('*', 0)
        t.SetBranchStatus ('PUWeight', 1)
        t.SetBranchStatus ('FatJetPt', 1)
        t.SetBranchStatus ('FatJetEta', 1)
        t.SetBranchStatus ('FatJetPhi', 1)
        t.SetBranchStatus ('FatJetMass', 1)
        t.SetBranchStatus ('FatJetMassSoftDrop', 1)
        t.SetBranchStatus ('FatJetTau32', 1)
        t.SetBranchStatus ('SemiLeptTrig', 1)
        t.SetBranchStatus ('AK4bDisc', 1)
        t.SetBranchStatus ('NearestAK4JetPt'   ,1 )
        t.SetBranchStatus ('NearestAK4JetEta'  ,1 )
        t.SetBranchStatus ('NearestAK4JetPhi'  ,1 )
        t.SetBranchStatus ('NearestAK4JetMass' ,1 )
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


        entries = t.GetEntriesFast()
        print 'Processing tree ' + str(itree)


        eventsToRun = entries
        print entries

        passkin = 0 
        pass2D  = 0
        passB   = 0
        passT   = 0 
        passLep = 0
        passOp  = 0
        pass1   = 0
        pass2   = 0
        pass3   = 0
 
        for jentry in xrange( eventsToRun ):
            if jentry % 100000 == 0 :
                print 'processing ' + str(jentry)
            # get the next tree in the chain and verify
            ientry = t.GetEntry( jentry )
            if ientry < 0:
                break

            # Muons only for now
#            if LeptonType[0] != 13 :
#                continue

            # Muon triggers only for now
#            if options.isData and SemiLeptTrig[0] != 3  :
#                continue

            hadTopCandP4 = ROOT.TLorentzVector()
            hadTopCandP4.SetPtEtaPhiM( FatJetPt[0], FatJetEta[0], FatJetPhi[0], FatJetMass[0])
            bJetCandP4 = ROOT.TLorentzVector()
            bJetCandP4.SetPtEtaPhiM( NearestAK4JetPt[0], NearestAK4JetEta[0], NearestAK4JetPhi[0], NearestAK4JetMass[0])
            nuCandP4 = ROOT.TLorentzVector( )
            nuCandP4.SetPtEtaPhiM( SemiLepMETpt[0], 0, SemiLepMETphi[0], SemiLepMETpt[0] )
            theLepton = ROOT.TLorentzVector()
            theLepton.SetPtEtaPhiE( LeptonPt[0], LeptonEta[0], LeptonPhi[0], LeptonEnergy[0] ) # Assume massless
            
            
            tau32 = FatJetTau32[0]
            mass_sd = FatJetMassSoftDrop[0]
            bdisc = AK4bDisc[0]

            WsubJetCand_m = FatJetSDsubjetWmass[0]

            WsubJetCand_pt = FatJetSDsubjetWpt[0]
            MET_pt = SemiLepMETpt[0]

            passKin = hadTopCandP4.Perp() > 400.
            passTopTag = tau32 < 0.6 and mass_sd > 110. and mass_sd < 250.
            pass2DCut = LeptonPtRel[0] > 20. or LeptonDRMin[0] > 0.4 # B2G-15-002 uses  LeptonPtRel[0] > 20.or LeptonDRMin[0] > 0.4 (was 55.0 here)
            passBtag = bdisc > 0.7

            passEleMETcut =  LeptonType[0] == 1 and MET_pt > 120. #and theLepton.Perp() > 110.
            # B2G-15-002  uses ( theLepton.Perp() + MET_pt ) > 150. (was previously 250 here) 
            passMuHtLepcut = LeptonType[0] == 2 and ( theLepton.Perp() + MET_pt ) > 150. #and theLepton.Perp() > 55.
            passLepcut = passEleMETcut or passMuHtLepcut 

            if passKin :
                passkin += 1

            if pass2DCut :
                pass2D += 1

            if passBtag :
                passB += 1
           
            if passTopTag :
                passT += 1

            if passLepcut :
                passLep += 1

# or not options.cut
            if not passKin or not pass2DCut or not passBtag or not passTopTag  :
                continue

      #      print "The event passed with P_{T} " + str(WsubJetCand_pt) + " and  Mass " + str(WsubJetCand_m)
       
            h_mWsubjet.Fill(WsubJetCand_m , PUWeight[0] )
            h_ptWsubjet.Fill(WsubJetCand_pt , PUWeight[0] )

         #seperate into bins of subjet Pt

          #  if (WsubJetCand_pt > 0.0 and WsubJetCand_pt < 20 ):



    print "Number of events passing basic cuts:"
    print "M_Ak8 > 400 GeV : " + str(passkin)
    print "2D cut (LeptonPtRel > 20. or LeptonDRMin > 0.4) : " + str(passkin)
    print "B tag : " + str(passB)
    print "T tag : " + str(passT)
    print "pass Lepton cut : " + str(passLep)
    fout.cd()
    fout.Write()
    fout.Close()

if __name__ == "__main__" :
    plot_Wsubjet(sys.argv)

