import subprocess

from optparse import OptionParser
parser = OptionParser()
# Systematic type; jecNom = 0; jecUp = +1; jecDn = -1; jerUp = +2; jerDn = -2; bTagUp = +3; bTagDn = -3; pdfUp = +4; pdfDn = -4; q2Up = +5; q2Dn = -5
# the command line is like: python runAll_bkgdEst.py --mistagFile=/uscms_data/d3/maral87/ttbarResonances/B2GAnaFW/CMSSW_7_4_12/src/Analysis/B2GTTbar/test/runs/run_012716/MistagRate_nbins_012716_8_ttbar_Substract_outAntiTag_JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65_012716.root --treedir=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/ --date=012716

parser.add_option('--mistagFile', type='string', action='store',
                  default='/uscms_data/d3/maral87/ttbarResonances/B2GAnaFW/CMSSW_7_4_12/src/Analysis/B2GTTbar/test/runs/run_121615/MistagRate_nbins_121615_8_ttbar_jec_nom__Substract_outAntiTag_JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65_121615_jec_nom.root',
                  dest='mistagFile',
                  help='MistagRate file')

parser.add_option('--date', type='string', action='store',
                  default='011516',
                  dest='date',
                  help='date')

parser.add_option('--treedir', type='string', action='store',
                  default='root://cmseos.fnal.gov//store/user/pilot/ZprimeTrees/',
                  dest='treedir',
                  help='treedir')


(options, args) = parser.parse_args()
argv = []

path2 = [
    # data
    "python bkgdEst.py --file=root://cmseos.fnal.gov//store/user/jdolen/B2GAnaFW/Trees/JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65 --Syst=0 --date="+options.date+" &" ,
    
    
    # ttbar nom
    "python bkgdEst.py --file="+options.treedir+"tree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all --Syst=0  --date="+options.date+" &" ,
    # ttbar jecUp
    "python bkgdEst.py --file="+options.treedir+"tree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all --Syst=+1 --date="+options.date+" &" ,
    # ttbar jecDn
    "python bkgdEst.py --file="+options.treedir+"tree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all --Syst=-1 --date="+options.date+" &" ,    
    # ttbar jerUp
    "python bkgdEst.py --file="+options.treedir+"tree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all --Syst=+2 --date="+options.date+" &" ,
    # ttbar jerDn
    "python bkgdEst.py --file="+options.treedir+"tree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all --Syst=-2 --date="+options.date+" &" ,
    # ttbar btagup
    "python bkgdEst.py --file="+options.treedir+"tree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all --Syst=+3 --date="+options.date+" &" ,
    # ttbar btagDn
    "python bkgdEst.py --file="+options.treedir+"tree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all --Syst=-3 --date="+options.date+" &" 
    # ttbar pdfUp
    "python bkgdEst.py --file="+options.treedir+"tree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all --Syst=+4 --date="+options.date+" &" ,
    # ttbar pdfDn
    "python bkgdEst.py --file="+options.treedir+"tree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all --Syst=-4 --date="+options.date+" &" ,
    # ttbar q2Up
    "python bkgdEst.py --file="+options.treedir+"tree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all --Syst=+5 --date="+options.date+" &" ,
    # ttbar q2Dn
    "python bkgdEst.py --file="+options.treedir+"tree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_janos_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all --Syst=-5 --date="+options.date+" " 

]

path = [
    
    # ZprimeToTT_M-1000_W-10 nom
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst= 0 --date="+options.date+" &",
    # ZprimeToTT_M-1000_W-10 jecUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+" &",
    # ZprimeToTT_M-1000_W-10 jecDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+" &",
    # ZprimeToTT_M-1000_W-10 jerUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+" &",
    # ZprimeToTT_M-1000_W-10 jerDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+" &",
    # ZprimeToTT_M-1000_W-10 btagup
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+" &",
    # ZprimeToTT_M-1000_W-10 btagDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+" &",
    # ZprimeToTT_M-1000_W-10 pdfUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+" &",
    # ZprimeToTT_M-1000_W-10 pdfDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+" &",
    # ZprimeToTT_M-1000_W-10 q2Up
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+" &",
    # ZprimeToTT_M-1000_W-10 q2Dn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+" ",


    # ZprimeToTT_M-2000_W-20 nom
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=0  --date="+options.date+" &",
    # ZprimeToTT_M-2000_W-20 jecUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+" &",
    # ZprimeToTT_M-2000_W-20 jecDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+" &",
    # ZprimeToTT_M-2000_W-20 jerUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+" &",
    # ZprimeToTT_M-2000_W-20 jerDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+" &",
    # ZprimeToTT_M-2000_W-20 btagUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+" &",
    # ZprimeToTT_M-2000_W-20 btagDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+" &",
    # ZprimeToTT_M-2000_W-20 pdfUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+" &",
    # ZprimeToTT_M-2000_W-20 pdfUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+" ",
    # ZprimeToTT_M-2000_W-20 q2Up
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+" &",
    # ZprimeToTT_M-2000_W-20 q2Dn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+" ",
    

    # ZprimeToTT_M-3000_W-30 nom
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=0  --date="+options.date+" &",
    # ZprimeToTT_M-3000_W-30 jecUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+" &",
    # ZprimeToTT_M-3000_W-30 jecDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+" &",
    # ZprimeToTT_M-3000_W-30 jerUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+" &",
    # ZprimeToTT_M-3000_W-30 jerDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+" &",
    # ZprimeToTT_M-3000_W-30 btagUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+" &",
    # ZprimeToTT_M-3000_W-30 btagDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+" &",
    # ZprimeToTT_M-3000_W-30 pdfUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+" &",
    # ZprimeToTT_M-3000_W-30 pdfDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+" &",
    # ZprimeToTT_M-3000_W-30 q2Up
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+" &",
    # ZprimeToTT_M-3000_W-30 q2Dn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+" ",
   

    # ZprimeToTT_M-4000_W-40 nom
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=0  --date="+options.date+" &",
    # ZprimeToTT_M-4000_W-40 jecUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+" &",
    # ZprimeToTT_M-4000_W-40 jecDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+" &",
    # ZprimeToTT_M-4000_W-40 jerUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+" &",
    # ZprimeToTT_M-4000_W-40 jerDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+" &",
    # ZprimeToTT_M-4000_W-40 btagUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+" &",
    # ZprimeToTT_M-4000_W-40 btagDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+" &",
    # ZprimeToTT_M-4000_W-40 pdfUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+" &",
    # ZprimeToTT_M-4000_W-40 pdfDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+" &",
    # ZprimeToTT_M-4000_W-40 q2Up
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+" &",
    # ZprimeToTT_M-4000_W-40 q2Dn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+" ",

]

path3 = [
    #ZprimeToTT_M-1000_W-100 nom
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=0  --date="+options.date+" &",
    #ZprimeToTT_M-1000_W-100 jecUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+" &",
    #ZprimeToTT_M-1000_W-100 jecDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+" &",
    #ZprimeToTT_M-1000_W-100 jerUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+" &",
    #ZprimeToTT_M-1000_W-100 jerDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+" &",
    #ZprimeToTT_M-1000_W-100 btagUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+" &",
    #ZprimeToTT_M-1000_W-100 btagDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+" &",
    #ZprimeToTT_M-1000_W-100 pdfUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+" &",
    #ZprimeToTT_M-1000_W-100 pdfDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+" &",
    #ZprimeToTT_M-1000_W-100 q2Up
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+" &",
    #ZprimeToTT_M-1000_W-100 q2Dn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+" ",


    #ZprimeToTT_M-2000_W-200 nom
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=0  --date="+options.date+" &",
    #ZprimeToTT_M-2000_W-200 jecUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+" &",
    #ZprimeToTT_M-2000_W-200 jecDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+" &",
    #ZprimeToTT_M-2000_W-200 jerUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+" &",
    #ZprimeToTT_M-2000_W-200 jerDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+" &",
    #ZprimeToTT_M-2000_W-200 btagUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+" &",
    #ZprimeToTT_M-2000_W-200 btagDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+" &",
    #ZprimeToTT_M-2000_W-200 pdfUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+" &",
    #ZprimeToTT_M-2000_W-200 pdfDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+" &",
    #ZprimeToTT_M-2000_W-200 q2Up
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+" &",
    #ZprimeToTT_M-2000_W-200 q2Dn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+" ",


    #ZprimeToTT_M-3000_W-300 nom
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=0  --date="+options.date+" &",
    #ZprimeToTT_M-3000_W-300 jecUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+" &",
    #ZprimeToTT_M-3000_W-300 jecDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+" &",
    #ZprimeToTT_M-3000_W-300 jerUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+" &",
    #ZprimeToTT_M-3000_W-300 jerDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+" &",
    #ZprimeToTT_M-3000_W-300 btagUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+" &",
    #ZprimeToTT_M-3000_W-300 btagDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+" &",
    #ZprimeToTT_M-3000_W-300 pdfUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+" &",
    #ZprimeToTT_M-3000_W-300 pdfDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+" &",
    #ZprimeToTT_M-3000_W-300 q2Up
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+" &",
    #ZprimeToTT_M-3000_W-300 q2Dn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+" ",


    #ZprimeToTT_M-4000_W-400 nom
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=0  --date="+options.date+" &",
    #ZprimeToTT_M-4000_W-400 jecUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+" &",
    #ZprimeToTT_M-4000_W-400 jecDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+" &",
    #ZprimeToTT_M-4000_W-400 jerUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+" &",
    #ZprimeToTT_M-4000_W-400 jerDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+" &",
    #ZprimeToTT_M-4000_W-400 btagUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+" &",
    #ZprimeToTT_M-4000_W-400 btagDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+" &",
    #ZprimeToTT_M-4000_W-400 pdfUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+" &",
    #ZprimeToTT_M-4000_W-400 pdfDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+" &",
    #ZprimeToTT_M-4000_W-400 q2Up
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+" &",
    #ZprimeToTT_M-4000_W-400 q2Dn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+" ",


    #ZprimeToTT_M-1500_W-15 nom
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=0  --date="+options.date+" &",
    #ZprimeToTT_M-1500_W-15 jecUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+" &",
    #ZprimeToTT_M-1500_W-15 jecDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+" &",
    #ZprimeToTT_M-1500_W-15 jerUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+" &",
    #ZprimeToTT_M-1500_W-15 jerDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+" &",
    #ZprimeToTT_M-1500_W-15 btagUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+" &",
    #ZprimeToTT_M-1500_W-15 btagDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+" &",
    #ZprimeToTT_M-1500_W-15 pdfUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+" &",
    #ZprimeToTT_M-1500_W-15 pdfDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+" &",
    #ZprimeToTT_M-1500_W-15 q2Up
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+" &",
    #ZprimeToTT_M-1500_W-15 q2Dn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+" ",


    #ZprimeToTT_M-1500_W-150 nom
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=0  --date="+options.date+" &",
    #ZprimeToTT_M-1500_W-150 jecUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+" &",
    #ZprimeToTT_M-1500_W-150 jecDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+" &",
    #ZprimeToTT_M-1500_W-150 jerUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+" &",
    #ZprimeToTT_M-1500_W-150 jerDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+" &",
    #ZprimeToTT_M-1500_W-150 btagUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+" &",
    #ZprimeToTT_M-1500_W-150 btagDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+" &",
    #ZprimeToTT_M-1500_W-150 pdfUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+" &",
    #ZprimeToTT_M-1500_W-150 pdfDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+" &",
    #ZprimeToTT_M-1500_W-150 q2Up
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+" &",
    #ZprimeToTT_M-1500_W-150 q2Dn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+" ",


    #ZprimeToTT_M-2500_W-25 nom
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=0  --date="+options.date+" &",
    #ZprimeToTT_M-2500_W-25 jecUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+" &",
    #ZprimeToTT_M-2500_W-25 jecDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+" &",
    #ZprimeToTT_M-2500_W-25 jerUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+" &",
    #ZprimeToTT_M-2500_W-25 jerDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+" &",
    #ZprimeToTT_M-2500_W-25 btagUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+" &",
    #ZprimeToTT_M-2500_W-25 btagDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+" &",
    #ZprimeToTT_M-2500_W-25 pdfUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+" &",
    #ZprimeToTT_M-2500_W-25 pdfdn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+" &",
    #ZprimeToTT_M-2500_W-25 q2Up
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+" &",
    #ZprimeToTT_M-2500_W-25 q2dn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+" ",


    #ZprimeToTT_M-2500_W-250 nom
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=0  --date="+options.date+" &",
    #ZprimeToTT_M-2500_W-250 jecUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+" &",
    #ZprimeToTT_M-2500_W-250 jecDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+" &",
    #ZprimeToTT_M-2500_W-250 jerUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+" &",
    #ZprimeToTT_M-2500_W-250 jerDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+" &",
    #ZprimeToTT_M-2500_W-250 btagUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+" &",
    #ZprimeToTT_M-2500_W-250 btagDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+" &",
    #ZprimeToTT_M-2500_W-250 pdfUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+" &",
    #ZprimeToTT_M-2500_W-250 pdfDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+" &",
    #ZprimeToTT_M-2500_W-250 q2Up
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+" &",
    #ZprimeToTT_M-2500_W-250 q2Dn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+" ",


    #ZprimeToTT_M-3500_W-35 nom
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=0  --date="+options.date+" &",
    #ZprimeToTT_M-3500_W-35 jecUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+" &",
    #ZprimeToTT_M-3500_W-35 jecDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+" &",
    #ZprimeToTT_M-3500_W-35 jerUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+" &",
    #ZprimeToTT_M-3500_W-35 jerDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+" &",
    #ZprimeToTT_M-3500_W-35 btagUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+" &",
    #ZprimeToTT_M-3500_W-35 btagDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+" &",
    #ZprimeToTT_M-3500_W-35 pdfUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+" &",
    #ZprimeToTT_M-3500_W-35 pdfDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+" &",
    #ZprimeToTT_M-3500_W-35 q2Up
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+" &",
    #ZprimeToTT_M-3500_W-35 q2Dn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+" ",


    #ZprimeToTT_M-3500_W-350 nom
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=0  --date="+options.date+" &",
    #ZprimeToTT_M-3500_W-350 jecUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+" &",
    #ZprimeToTT_M-3500_W-350 jecDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+" &",
    #ZprimeToTT_M-3500_W-350 jerUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+" &",
    #ZprimeToTT_M-3500_W-350 jerDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+" &",
    #ZprimeToTT_M-3500_W-350 btagUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+" &",
    #ZprimeToTT_M-3500_W-350 btagDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+" &",
    #ZprimeToTT_M-3500_W-350 pdfUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+" &",
    #ZprimeToTT_M-3500_W-350 pdfDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+" &",
    #ZprimeToTT_M-3500_W-350 q2Up
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+" &",
    #ZprimeToTT_M-3500_W-350 q2Dn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+" ",


    #ZprimeToTT_M-1000_W-300 nom
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=0  --date="+options.date+" &",
    #ZprimeToTT_M-1000_W-300 jecUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+" &",
    #ZprimeToTT_M-1000_W-300 jecDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+" &",
    #ZprimeToTT_M-1000_W-300 jerUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+" &",
    #ZprimeToTT_M-1000_W-300 jerDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+" &",
    #ZprimeToTT_M-1000_W-300 btagUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+" &",
    #ZprimeToTT_M-1000_W-300 btagDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+" &",
    #ZprimeToTT_M-1000_W-300 pdfUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+" &",
    #ZprimeToTT_M-1000_W-300 pdfDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+" &",
    #ZprimeToTT_M-1000_W-300 q2Up
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+" &",
    #ZprimeToTT_M-1000_W-300 q2Dn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+" ",


    #ZprimeToTT_M-1250_W-125 nom
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=0  --date="+options.date+" &",
    #ZprimeToTT_M-1250_W-125 jecUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+" &",
    #ZprimeToTT_M-1250_W-125 jecDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+" &",
    #ZprimeToTT_M-1250_W-125 jerUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+" &",
    #ZprimeToTT_M-1250_W-125 jerDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+" &",
    #ZprimeToTT_M-1250_W-125 btagUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+" &",
    #ZprimeToTT_M-1250_W-125 btagDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+" &",
    #ZprimeToTT_M-1250_W-125 pdfUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+" &",
    #ZprimeToTT_M-1250_W-125 pdfDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+" &",
    #ZprimeToTT_M-1250_W-125 q2Up
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+" &",
    #ZprimeToTT_M-1250_W-125 q2Dn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+" ",


    #ZprimeToTT_M-2000_W-600 nom
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=0  --date="+options.date+" &",
    #ZprimeToTT_M-2000_W-600 jecUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+" &",
    #ZprimeToTT_M-2000_W-600 jecDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+" &",
    #ZprimeToTT_M-2000_W-600 jerUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+" &",
    #ZprimeToTT_M-2000_W-600 jerDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+" &",
    #ZprimeToTT_M-2000_W-600 btagUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+" &",
    #ZprimeToTT_M-2000_W-600 btagDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+" &",
    #ZprimeToTT_M-2000_W-600 pdfUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+" &",
    #ZprimeToTT_M-2000_W-600 pdfDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+" &",
    #ZprimeToTT_M-2000_W-600 q2Up
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+" &",
    #ZprimeToTT_M-2000_W-600 q2Dn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+" ",


    #ZprimeToTT_M-3000_W-900 nom
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=0  --date="+options.date+" &",
    #ZprimeToTT_M-3000_W-900 jecUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+" &",
    #ZprimeToTT_M-3000_W-900 jecDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+" &",
    #ZprimeToTT_M-3000_W-900 jerUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+" &",
    #ZprimeToTT_M-3000_W-900 jerDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+" &",
    #ZprimeToTT_M-3000_W-900 btagUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+" &",
    #ZprimeToTT_M-3000_W-900 btagDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+" &",
    #ZprimeToTT_M-3000_W-900 pdfUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+" &",
    #ZprimeToTT_M-3000_W-900 pdfDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+" &",
    #ZprimeToTT_M-3000_W-900 q2Up
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+" &",
    #ZprimeToTT_M-3000_W-900 q2Dn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+" ",

 
    #ZprimeToTT_M-4000_W-1200 nom
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=0  --date="+options.date+" &",
    #ZprimeToTT_M-4000_W-1200 jecUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=+1 --date="+options.date+" &",
    #ZprimeToTT_M-4000_W-1200 jecDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+" &",
    #ZprimeToTT_M-4000_W-1200 jerUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=+2 --date="+options.date+" &",
    #ZprimeToTT_M-4000_W-1200 jerDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+" &",
    #ZprimeToTT_M-4000_W-1200 btagUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=+3 --date="+options.date+" &",
    #ZprimeToTT_M-4000_W-1200 btagDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=-3 --date="+options.date+" &",
    #ZprimeToTT_M-4000_W-1200 pdfUp
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=+4 --date="+options.date+" &",
    #ZprimeToTT_M-4000_W-1200 pdfDn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=-4 --date="+options.date+" &",
    #ZprimeToTT_M-4000_W-1200 q2Up
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=+5 --date="+options.date+" &",
    #ZprimeToTT_M-4000_W-1200 q2Dn
    #"python bkgdEst.py --file="+options.treedir+"tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=-5 --date="+options.date+"",


]


for s in path2 :
    print s
    subprocess.call( [s, ""], shell=True )
    print "Done!"
