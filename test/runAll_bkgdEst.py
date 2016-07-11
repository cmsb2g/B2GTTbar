import subprocess

from optparse import OptionParser
parser = OptionParser()
# Systematic type; jecNom = 0; jecUp = +1; jecDn = -1; jerUp = +2; jerDn = -2; bTagUp = +3; bTagDn = -3; pdfUp = +4; pdfDn = -4; q2Up = +5; q2Dn = -5
# the command line is like: python runAll_bkgdEst.py --mistagFile=/uscms_data/d3/maral87/ttbarResonances/B2GAnaFW/CMSSW_7_4_12/src/Analysis/B2GTTbar/test/runs/run_020516/MistagRate_nbins_020516_8_ttbar_Substract_outAntiTag_JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65_020516.root --treedir=root://cmsxrootd-site.fnal.gov//... --date=020516 --isData or isTTbar or isZprime or isRSGluon 

# Direcetory of the trees as of 02/23/16:
# ttbar:   /store/user/camclean/B2GAnaFW/Trees/20160214_UpdatedPDF/
# Zprime:  /store/user/camclean/B2GAnaFW/Trees/20160214_UpdatedPDF/
# RSGluon: /store/user/camclean/B2GAnaFW/Trees/20160214_UpdatedPDF/

# parser.add_option('--mistagFile', type='string', action='store',
#                   default='/uscms_data/d3/maral87/ttbarResonances/B2GAnaFW/CMSSW_7_4_12/src/Analysis/B2GTTbar/test/runs/run_121615/MistagRate_nbins_121615_8_ttbar_jec_nom__Substract_outAntiTag_JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65_121615_jec_nom.root',
#                   dest='mistagFile',
#                   help='MistagRate file')

parser.add_option('--date', type='string', action='store',
                  default='011516',
                  dest='date',
                  help='date')

parser.add_option('--outname', type='string', action='store',
                  default='outBkgdEst_outplots',
                  dest='outname',
                  help='Name of output file')

parser.add_option('--treedir', type='string', action='store',
                  default='root://cmsxrootd-site.fnal.gov//store/user/pilot/ZprimeTrees/',
                  dest='treedir',
                  help='treedir')

parser.add_option('--isData', action='store_true',
                  default=False,
                  dest='isData',
                  help='is it Data?')

parser.add_option('--isTTbar', action='store_true',
                  default=False,
                  dest='isTTbar',
                  help='is it TTbar?')

parser.add_option('--isZprime', action='store_true',
                  default=False,
                  dest='isZprime',
                  help='is it Zprime?')

parser.add_option('--isRSGluon', action='store_true',
                  default=False,
                  dest='isRSGluon',
                  help='is it RSGluon?')

parser.add_option('--isQCDMC', action='store_true',
                  default=False,
                  dest='isQCDMC',
                  help='is it QCDMC?')

parser.add_option('--minAK8Pt', type='float', action='store',
                  default=500,
                  dest='minAK8Pt',
                  help='Minimum PT for AK8 jets')

parser.add_option('--Zp1000n', action='store_true',
                  default=False,
                  dest='Zp1000n',
                  help='')

parser.add_option('--Zp1000w', action='store_true',
                  default=False,
                  dest='Zp1000w',
                  help='')

parser.add_option('--Zp1000ww', action='store_true',
                  default=False,
                  dest='Zp1000ww',
                  help='')

parser.add_option('--Zp1250n', action='store_true',
                  default=False,
                  dest='Zp1250n',
                  help='')

parser.add_option('--Zp1250w', action='store_true',
                  default=False,
                  dest='Zp1250w',
                  help='')


parser.add_option('--Zp1500n', action='store_true',
                  default=False,
                  dest='Zp1500n',
                  help='')

parser.add_option('--Zp1500w', action='store_true',
                  default=False,
                  dest='Zp1500w',
                  help='')

parser.add_option('--Zp2000n', action='store_true',
                  default=False,
                  dest='Zp2000n',
                  help='')

parser.add_option('--Zp2000w', action='store_true',
                  default=False,
                  dest='Zp2000w',
                  help='')

parser.add_option('--Zp2000ww', action='store_true',
                  default=False,
                  dest='Zp2000ww',
                  help='')


parser.add_option('--Zp2500n', action='store_true',
                  default=False,
                  dest='Zp2500n',
                  help='')

parser.add_option('--Zp2500w', action='store_true',
                  default=False,
                  dest='Zp2500w',
                  help='')

parser.add_option('--Zp3000n', action='store_true',
                  default=False,
                  dest='Zp3000n',
                  help='')

parser.add_option('--Zp3000w', action='store_true',
                  default=False,
                  dest='Zp3000w',
                  help='')

parser.add_option('--Zp3000ww', action='store_true',
                  default=False,
                  dest='Zp3000ww',
                  help='')


parser.add_option('--Zp3500n', action='store_true',
                  default=False,
                  dest='Zp3500n',
                  help='')

parser.add_option('--Zp3500w', action='store_true',
                  default=False,
                  dest='Zp3500w',
                  help='')

parser.add_option('--Zp4000n', action='store_true',
                  default=False,
                  dest='Zp4000n',
                  help='')

parser.add_option('--Zp4000w', action='store_true',
                  default=False,
                  dest='Zp4000w',
                  help='')

parser.add_option('--Zp4000ww', action='store_true',
                  default=False,
                  dest='Zp4000ww',
                  help='')





(options, args) = parser.parse_args()
argv = []

path_data = [
    # data  root://cmsxrootd-site.fnal.gov///store/user/camclean/B2GAnaFW/Trees/201603018_JECv7WithPUerrors/
    "python bkgdEst.py --file="+options.treedir+"JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65.root --outname=runs/run"+options.date+"/outBkgdEst_JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65 --isData --date="+options.date+" --minAK8Pt="+str(options.minAK8Pt) 
]

path_QCDMC = [
    #QCD MC nom
    "python bkgdEst.py --file="+options.treedir+"tree_QCD_HT700to1000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_QCD_HT700to1000_B2Gv8p4_reader603e_notrig --date="+options.date+" --minAK8Pt="+str(options.minAK8Pt)+" &",
    "python bkgdEst.py --file="+options.treedir+"tree_QCD_HT1000to1500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_QCD_HT1000to1500_B2Gv8p4_reader603e_notrig --date="+options.date+" --minAK8Pt="+str(options.minAK8Pt)+" &",
    "python bkgdEst.py --file="+options.treedir+"tree_QCD_HT1500to2000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_QCD_HT1500to2000_B2Gv8p4_reader603e_notrig --date="+options.date+" --minAK8Pt="+str(options.minAK8Pt)+" &",
    "python bkgdEst.py --file="+options.treedir+"tree_QCD_HT2000toInf_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_QCD_HT2000toInf_B2Gv8p4_reader603e_notrig --date="+options.date+" --minAK8Pt="+str(options.minAK8Pt)+" &"
]

path_ttbar = [    
    
    # ttbar nom
    "python bkgdEst.py --file="+options.treedir+"tree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65 --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &" ,
    # ttbar jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65 --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &" ,
    # ttbar jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65 --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &" ,    
    # ttbar jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65 --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &" ,
    # ttbar jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65 --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &" ,
    # ttbar btagup
    "python bkgdEst.py --file="+options.treedir+"tree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65 --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &" ,
    # ttbar btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65 --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &" 
    # ttbar pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65 --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &" ,
    # ttbar pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65 --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &" ,
    # ttbar q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65 --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &" ,
    # ttbar q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65 --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &" , 
    # ttbar puUp
    "python bkgdEst.py --file="+options.treedir+"tree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65 --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &" ,
    # ttbar puDn
    "python bkgdEst.py --file="+options.treedir+"tree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65 --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" "  
    
    # # High-mass ttbar samples; M_1000
    # # ttbar nom
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M1000.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M1000 --Syst=0  --date="+options.date+" &" ,
    # # ttbar jecUp
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M1000.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M1000 --Syst=+1 --date="+options.date+" &" ,
    # # ttbar jecDn
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M1000.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M1000 --Syst=-1 --date="+options.date+" &" ,    
    # # ttbar jerUp
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M1000.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M1000 --Syst=+2 --date="+options.date+" &" ,
    # # ttbar jerDn
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M1000.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M1000 --Syst=-2 --date="+options.date+" &" ,
    # # ttbar btagup
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M1000.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M1000 --Syst=+3 --date="+options.date+" &" ,
    # # ttbar btagDn
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M1000.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M1000 --Syst=-3 --date="+options.date+" &" 
    # # ttbar pdfUp
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M1000.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M1000 --Syst=+4 --date="+options.date+" &" ,
    # # ttbar pdfDn
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M1000.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M1000 --Syst=-4 --date="+options.date+" &" ,
    # # ttbar q2Up
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M1000.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M1000 --Syst=+5 --date="+options.date+" &" ,
    # # ttbar q2Dn
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M1000.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M1000 --Syst=-5 --date="+options.date+" &" , 
    # # ttbar puUp
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M1000.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M1000 --Syst=+6 --date="+options.date+" &" ,
    # # ttbar puDn
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M1000.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M1000 --Syst=-6 --date="+options.date+" &" ,  
    
    # # High-mass ttbar samples; M_700
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M700.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M700 --Syst=0  --date="+options.date+" &" ,
    # # ttbar jecUp
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M700.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M700 --Syst=+1 --date="+options.date+" &" ,
    # # ttbar jecDn
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M700.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M700 --Syst=-1 --date="+options.date+" &" ,    
    # # ttbar jerUp
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M700.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M700 --Syst=+2 --date="+options.date+" &" ,
    # # ttbar jerDn
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M700.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M700 --Syst=-2 --date="+options.date+" &" ,
    # # ttbar btagup
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M700.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M700 --Syst=+3 --date="+options.date+" &" ,
    # # ttbar btagDn
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M700.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M700 --Syst=-3 --date="+options.date+" &" 
    # # ttbar pdfUp
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M700.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M700 --Syst=+4 --date="+options.date+" &" ,
    # # ttbar pdfDn
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M700.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M700 --Syst=-4 --date="+options.date+" &" ,
    # # ttbar q2Up
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M700.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M700 --Syst=+5 --date="+options.date+" &" ,
    # # ttbar q2Dn
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M700.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M700 --Syst=-5 --date="+options.date+" &" , 
    # # ttbar puUp
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M700.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M700 --Syst=+6 --date="+options.date+" &" ,
    # # ttbar puDn
    # "python bkgdEst.py --file="+options.treedir+"ttbar_M700.root --outname=runs/run"+options.date+"/outBkgdEst_ttbar_M700 --Syst=-6 --date="+options.date+" "  

]

path_Zprime = [
    
    # ZprimeToTT_M-1000_W-10 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-10 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-10 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-10 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-10 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-10 btagup
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-10 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-10 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-10 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-10 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-10 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-10 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-1000_W-10 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",


    # ZprimeToTT_M-1000_W-100 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-100 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-100 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-100 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-100 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-100 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-100 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-100 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-100 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-100 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-100 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-100 puUp
     "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-1000_W-100 puDn
     "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",


    # ZprimeToTT_M-1000_W-300 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-300 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-300 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-300 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-300 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-300 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-300 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-300 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-300 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-300 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-300 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-300 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-1000_W-300 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",


    # ZprimeToTT_M-1250_W-12p5 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-12p5 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-12p5 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-12p5 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-12p5 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-12p5 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-12p5 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-12p5 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-12p5 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-12p5 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-12p5 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-12p5 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-1250_W-12p5 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",


    # ZprimeToTT_M-1250_W-125 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-125 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-125 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-125 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-125 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-125 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-125 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-125 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-125 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-125 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-125 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-125 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-1250_W-125 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",


    # ZprimeToTT_M-1500_W-15 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-15 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-15 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-15 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-15 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-15 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-15 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-15 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-15 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-15 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-15 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-15 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-1500_W-15 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",


    # ZprimeToTT_M-1500_W-150 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-150 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-150 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-150 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-150 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-150 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-150 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-150 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-150 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-150 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-150 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-150 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-1500_W-150 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",


    # ZprimeToTT_M-2000_W-20 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-20 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-20 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-20 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-20 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-20 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-20 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-20 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-20 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &" ,
    # ZprimeToTT_M-2000_W-20 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-20 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-20 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-2000_W-20 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    

    # ZprimeToTT_M-2000_W-200 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-200 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-200 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-200 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-200 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-200 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-200 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-200 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-200 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-200 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-200 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-200 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-2000_W-200 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",


    # ZprimeToTT_M-2000_W-600 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-600 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-600 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-600 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-600 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-600 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-600 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-600 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-600 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-600 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-600 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-600 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-2000_W-600 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",


    # ZprimeToTT_M-2500_W-25 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-25 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-25 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-25 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-25 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-25 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-25 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-25 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-25 pdfdn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-25 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-25 q2dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-25 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-2500_W-25 pudn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",


    # ZprimeToTT_M-2500_W-250 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-250 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-250 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-250 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-250 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-250 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-250 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-250 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-250 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-250 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-250 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-250 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-2500_W-250 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",


    # ZprimeToTT_M-3000_W-30 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-30 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-30 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-30 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-30 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-30 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-30 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-30 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-30 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-30 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-30 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-30 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-3000_W-30 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    

    # ZprimeToTT_M-3000_W-300 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-300 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-300 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-300 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-300 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-300 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-300 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-300 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-300 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-300 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-300 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-300 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-3000_W-300 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",

    
    # ZprimeToTT_M-3000_W-900 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-900 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-900 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-900 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-900 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-900 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-900 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-900 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-900 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-900 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-900 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-900 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-3000_W-900 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",


    # ZprimeToTT_M-3500_W-35 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-35 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-35 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-35 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-35 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-35 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-35 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-35 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-35 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-35 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-35 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-35 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-3500_W-35 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",


    # ZprimeToTT_M-3500_W-350 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-350 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-350 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-350 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-350 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-350 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-350 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-350 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-350 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-350 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-350 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-350 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-3500_W-350 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
 

    # ZprimeToTT_M-4000_W-40 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-40 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-40 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-40 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-40 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-40 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-40 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-40 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-40 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-40 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-40 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-40 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-4000_W-40 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",

  
    # ZprimeToTT_M-4000_W-400 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-400 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-400 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-400 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-400 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-400 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-400 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-400 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-400 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-400 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-400 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-400 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-4000_W-400 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",


    # ZprimeToTT_M-4000_W-1200 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-1200 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-1200 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-1200 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-1200 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-1200 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-1200 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-1200 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-1200 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-1200 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-1200 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &" ,
    # ZprimeToTT_M-4000_W-1200 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-4000_W-1200 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" " 



]

path_RSGluon = [

    # RSGluonToTT_M-1000 nom
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1000 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1000 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1000 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1000 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1000 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1000 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1000 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1000 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1000 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1000 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1000 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1000 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1000_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",


    # RSGluonToTT_M-1250 nom 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1250 jecUp 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1250 jecDn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1250 jerUp 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1250 jerDn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1250 btagUp 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1250 btagDn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1250 pdfUp 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1250 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1250 q2Up 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1250 q2Dn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1250 puUp 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1250 puDn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1250_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",


    # RSGluonToTT_M-1500 nom 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1500 jecUp 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1500 jecDn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1500 jerUp 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1500 jerDn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1500 btagUp 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1500 btagDn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1500 pdfUp 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1500 pdfDn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1500 q2Up 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1500 q2Dn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1500 puUp 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-1500 puDn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-1500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-1500_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",


    # RSGluonToTT_M-2000 nom 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-2000 jecUp 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-2000 jecDn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-2000 jerUp 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-2000 jerDn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-2000 btagUp 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-2000 btagDn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-2000 pdfUp 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-2000 pdfDn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-2000 q2Up 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-2000 q2Dn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-2000 puUp 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-2000 puDn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2000_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",


    # RSGluonToTT_M-2500 nom 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-2500 jecUp 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-2500 jecDn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-2500 jerUp 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-2500 jerDn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-2500 btagUp 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-2500 btagDn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-2500 pdfUp 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-2500 pdfDn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-2500 q2Up 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-2500 q2Dn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-2500 puUp 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-2500 puDn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-2500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-2500_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",


    # RSGluonToTT_M-3000 nom 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-3000 jecUp 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-3000 jecDn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-3000 jerUp 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-3000 jerDn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-3000 btagUp 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-3000 btagDn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-3000 pdfUp 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-3000 pdfDn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-3000 q2Up 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-3000 q2Dn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-3000 puUp 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-3000 puDn 
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3000_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",


    # RSGluonToTT_M-3500 nom
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-3500 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-3500 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-3500 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-3500 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-3500 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-3500 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-3500 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-3500 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-3500 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-3500 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-3500 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-3500 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-3500_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-3500_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &", 

    # RSGluonToTT_M-4000 nom
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-4000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-4000 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-4000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-4000 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-4000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-4000 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-4000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-4000 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-4000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-4000 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-4000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-4000 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-4000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-4000 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-4000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-4000 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-4000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-4000 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-4000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-4000 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-4000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-4000 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-4000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # RSGluonToTT_M-4000 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_RSGluonToTT_M-4000_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_RSGluonToTT_M-4000_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" " 


]

path_Zp1000n = [
    # ZprimeToTT_M-1000_W-10 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-10 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-10 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-10 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-10 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-10 btagup
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-10 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-10 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-10 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-10 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-10 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-10 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-1000_W-10 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &"
]
path_Zp1000w = [
    # ZprimeToTT_M-1000_W-100 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-100 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-100 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-100 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-100 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-100 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-100 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-100 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-100 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-100 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-100 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-100 puUp
     "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-1000_W-100 puDn
     "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &"
]
path_Zp1000ww = [
    # ZprimeToTT_M-1000_W-300 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-300 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-300 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-300 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-300 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-300 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-300 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-300 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-300 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-300 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-300 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1000_W-300 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-1000_W-300 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &"
]
path_Zp1250n = [
    # ZprimeToTT_M-1250_W-12p5 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-12p5 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-12p5 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-12p5 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-12p5 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-12p5 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-12p5 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-12p5 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-12p5 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-12p5 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-12p5 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-12p5 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-1250_W-12p5 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &"
]
path_Zp1250w = [
    # ZprimeToTT_M-1250_W-125 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-125 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-125 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-125 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-125 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-125 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-125 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-125 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-125 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-125 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-125 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1250_W-125 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-1250_W-125 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &"
]
path_Zp1500n = [
    # ZprimeToTT_M-1500_W-15 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-15 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-15 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-15 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-15 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-15 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-15 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-15 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-15 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-15 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-15 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-15 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-1500_W-15 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &"
]
path_Zp1500w = [
    # ZprimeToTT_M-1500_W-150 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-150 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-150 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-150 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-150 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-150 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-150 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-150 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-150 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-150 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-150 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-1500_W-150 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-1500_W-150 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &"
]
path_Zp2000n = [
    # ZprimeToTT_M-2000_W-20 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-20 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-20 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-20 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-20 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-20 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-20 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-20 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-20 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &" ,
    # ZprimeToTT_M-2000_W-20 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-20 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-20 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-2000_W-20 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &"
]
path_Zp2000w = [
    # ZprimeToTT_M-2000_W-200 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-200 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-200 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-200 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-200 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-200 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-200 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-200 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-200 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-200 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-200 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-200 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-2000_W-200 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &"
]
path_Zp2000ww = [
    # ZprimeToTT_M-2000_W-600 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-600 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-600 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-600 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-600 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-600 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-600 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-600 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-600 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-600 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-600 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2000_W-600 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-2000_W-600 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &"
]
path_Zp2500n = [
    # ZprimeToTT_M-2500_W-25 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-25 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-25 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-25 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-25 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-25 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-25 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-25 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-25 pdfdn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-25 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-25 q2dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-25 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-2500_W-25 pudn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &"
]
path_Zp2500w = [
    # ZprimeToTT_M-2500_W-250 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-250 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-250 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-250 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-250 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-250 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-250 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-250 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-250 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-250 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-250 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-2500_W-250 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-2500_W-250 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &"
]
path_Zp3000n = [
    # ZprimeToTT_M-3000_W-30 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-30 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-30 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-30 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-30 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-30 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-30 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-30 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-30 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-30 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-30 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-30 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-3000_W-30 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &"
 ]   
path_Zp3000w = [
    # ZprimeToTT_M-3000_W-300 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-300 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-300 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-300 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-300 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-300 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-300 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-300 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-300 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-300 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-300 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-300 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-3000_W-300 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &"
]
path_Zp3000ww = [    
    # ZprimeToTT_M-3000_W-900 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-900 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-900 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-900 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-900 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-900 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-900 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-900 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-900 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-900 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-900 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3000_W-900 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-3000_W-900 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &"
]
path_Zp3500n = [
    # ZprimeToTT_M-3500_W-35 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-35 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-35 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-35 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-35 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-35 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-35 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-35 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-35 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-35 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-35 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-35 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-3500_W-35 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &"
]
path_Zp3500w = [
    # ZprimeToTT_M-3500_W-350 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-350 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-350 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-350 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-350 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-350 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-350 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-350 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-350 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-350 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-350 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-3500_W-350 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-3500_W-350 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &"
 ]
path_Zp4000n = [
    # ZprimeToTT_M-4000_W-40 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-40 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-40 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-40 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-40 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-40 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-40 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-40 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-40 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-40 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-40 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-40 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-4000_W-40 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &"
]
path_Zp4000w = [ 
    # ZprimeToTT_M-4000_W-400 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-400 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-400 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-400 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-400 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-400 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-400 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-400 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-400 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-400 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-400 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-400 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-4000_W-400 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &"
]
path_Zp4000ww = [
    # ZprimeToTT_M-4000_W-1200 nom
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=0  --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-1200 jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-1200 jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-1200 jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-1200 jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-1200 btagUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-1200 btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-1200 pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-1200 pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-1200 q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # ZprimeToTT_M-4000_W-1200 q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &" ,
    # ZprimeToTT_M-4000_W-1200 puUp
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=+6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" &",
    # # ZprimeToTT_M-4000_W-1200 puDn
    "python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --outname=runs/run"+options.date+"/outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=-6 --date="+options.date+"  --minAK8Pt="+str(options.minAK8Pt)+" " 

]

if options.isData == True:
    path = path_data
if options.isTTbar == True:
    path = path_ttbar
if options.isZprime == True:
    path = path_Zprime
if options.isRSGluon == True:
    path = path_RSGluon
if options.isQCDMC == True:
    path = path_QCDMC

if options.Zp1000n == True:
    path = path_Zp1000n 
if options.Zp1000w == True:
    path = path_Zp1000w 
if options.Zp1000ww == True:    
    path = path_Zp1000ww 
if options.Zp1250n == True:    
    path = path_Zp1250n  
if options.Zp1250w == True:    
    path = path_Zp1250w  
if options.Zp1500n == True:    
    path = path_Zp1500n  
if options.Zp1500w == True:    
    path = path_Zp1500w  
if options.Zp2000n == True:    
    path = path_Zp2000n 
if options.Zp2000w == True:     
    path = path_Zp2000w  
if options.Zp2000ww == True:    
    path = path_Zp2000ww 
if options.Zp2500n == True:    
    path = path_Zp2500n 
if options.Zp2500w == True:    
    path = path_Zp2500w 
if options.Zp3000n == True:    
    path = path_Zp3000n 
if options.Zp3000w == True:    
    path = path_Zp3000w 
if options.Zp3000ww == True:    
    path = path_Zp3000ww   
if options.Zp3500n == True:    
    path = path_Zp3500n 
if options.Zp3500w == True:    
    path = path_Zp3500w 
if options.Zp4000n == True:    
    path = path_Zp4000n 
if options.Zp4000w == True:    
    path = path_Zp4000w  
if options.Zp4000ww == True:    
    path = path_Zp4000ww 

for s in path :
    print s
    subprocess.call( [s, ""], shell=True )
    print "Done!"
