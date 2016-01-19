import subprocess

from optparse import OptionParser
parser = OptionParser()

# the command line is like: python runAll_bkgdEst.py --mistagFile=runs/run_121615/MistagRate_nbins_121615_8_ttbar_jec_nom__Substract_outAntiTag_JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65_121615_jec_nom.root --date=011516

parser.add_option('--mistagFile', type='string', action='store',
                  default='runs/run_121615/MistagRate_nbins_121615_8_ttbar_jec_nom__Substract_outAntiTag_JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65_121615_jec_nom.root',
                  dest='mistagFile',
                  help='MistagRate file')

parser.add_option('--date', type='string', action='store',
                  default='011516',
                  dest='date',
                  help='date')

(options, args) = parser.parse_args()
argv = []

path = [
    # data
    "python bkgdEst.py --file=/eos/uscms/store/user/jdolen/B2GAnaFW/Trees/JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_JetHT_BothParts_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_reader5a85e65 --Syst=0 --date="+options.date+"",
    
    
    # ttbar jerDn
    "python bkgdEst.py --file=/eos/uscms/store/user/jdolen/B2GAnaFW/Trees/tree_TTpowheg_B2Gv8p4_reader5a85e65_all.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all --Syst=-2 --date="+options.date+"",
    # ttbar jecDn
    "python bkgdEst.py --file=/eos/uscms/store/user/jdolen/B2GAnaFW/Trees/tree_TTpowheg_B2Gv8p4_reader5a85e65_all.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all --Syst=-1 --date="+options.date+"",    
    # ttbar nom
    "python bkgdEst.py --file=/eos/uscms/store/user/jdolen/B2GAnaFW/Trees/tree_TTpowheg_B2Gv8p4_reader5a85e65_all.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all --Syst=0 --date="+options.date+"",
    # ttbar jecUp
    "python bkgdEst.py --file=/eos/uscms/store/user/jdolen/B2GAnaFW/Trees/tree_TTpowheg_B2Gv8p4_reader5a85e65_all.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all --Syst=1 --date="+options.date+"",
    # ttbar jerUp
    "python bkgdEst.py --file=/eos/uscms/store/user/jdolen/B2GAnaFW/Trees/tree_TTpowheg_B2Gv8p4_reader5a85e65_all.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_TTpowheg_B2Gv8p4_reader5a85e65_all --Syst=2 --date="+options.date+""
    
    # ZprimeToTT_M-1000_W-10 jerDn
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"",
    # ZprimeToTT_M-1000_W-10 jecDn
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"",
    # ZprimeToTT_M-1000_W-10 nom
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=0 --date="+options.date+"",
    # ZprimeToTT_M-1000_W-10 jecUp
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=1 --date="+options.date+"",
    # ZprimeToTT_M-1000_W-10 jerUp
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e --Syst=2 --date="+options.date+"",


    # ZprimeToTT_M-2000_W-20 jerDn
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"",
    # ZprimeToTT_M-2000_W-20 jecDn
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"",
    # ZprimeToTT_M-2000_W-20 nom
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=0 --date="+options.date+"",
    # ZprimeToTT_M-2000_W-20 jecUp
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=1 --date="+options.date+"",
    # ZprimeToTT_M-2000_W-20 jerUp
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e --Syst=2 --date="+options.date+"",


    # ZprimeToTT_M-3000_W-30 jerDn
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"",
    # ZprimeToTT_M-3000_W-30 jecDn
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"",
    # ZprimeToTT_M-3000_W-30 nom
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=0 --date="+options.date+"",
    # ZprimeToTT_M-3000_W-30 jecUp
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=1 --date="+options.date+"",
    # ZprimeToTT_M-3000_W-30 jerUp
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e --Syst=2 --date="+options.date+"",


    # ZprimeToTT_M-4000_W-40 jerDn
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"",
    # ZprimeToTT_M-4000_W-40 jecDn
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"",
    # ZprimeToTT_M-4000_W-40 nom
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=0 --date="+options.date+"",
    # ZprimeToTT_M-4000_W-40 jecUp
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=1 --date="+options.date+"",
    # ZprimeToTT_M-4000_W-40 jerUp
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e --Syst=2 --date="+options.date+"",


    #ZprimeToTT_M-1000_W-100 jerDn
    "python bkgdEst.py --file=/eos/uscms/store/user/pilot/tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"",
    #ZprimeToTT_M-1000_W-100 jecDn
    "python bkgdEst.py --file=/eos/uscms/store/user/pilot/tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"",
    #ZprimeToTT_M-1000_W-100 nom
    "python bkgdEst.py --file=/eos/uscms/store/user/pilot/tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=0 --date="+options.date+"",
    #ZprimeToTT_M-1000_W-100 jecUp
    "python bkgdEst.py --file=/eos/uscms/store/user/pilot/tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=1 --date="+options.date+"",
    #ZprimeToTT_M-1000_W-100 jerUp
    "python bkgdEst.py --file=/eos/uscms/store/user/pilot/tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e --Syst=2 --date="+options.date+"",


    #ZprimeToTT_M-2000_W-200 jerDn
    "python bkgdEst.py --file=/eos/uscms/store/user/pilot/tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"",
    #ZprimeToTT_M-2000_W-200 jecDn
    "python bkgdEst.py --file=/eos/uscms/store/user/pilot/tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"",
    #ZprimeToTT_M-2000_W-200 nom
    "python bkgdEst.py --file=/eos/uscms/store/user/pilot/tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=0 --date="+options.date+"",
    #ZprimeToTT_M-2000_W-200 jecUp
    "python bkgdEst.py --file=/eos/uscms/store/user/pilot/tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=1 --date="+options.date+"",
    #ZprimeToTT_M-2000_W-200 jerUp
    "python bkgdEst.py --file=/eos/uscms/store/user/pilot/tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e --Syst=2 --date="+options.date+"",


    #ZprimeToTT_M-3000_W-300 jerDn
    "python bkgdEst.py --file=/eos/uscms/store/user/pilot/tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"",
    #ZprimeToTT_M-3000_W-300 jecDn
    "python bkgdEst.py --file=/eos/uscms/store/user/pilot/tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"",
    #ZprimeToTT_M-3000_W-300 nom
    "python bkgdEst.py --file=/eos/uscms/store/user/pilot/tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=0 --date="+options.date+"",
    #ZprimeToTT_M-3000_W-300 jecUp
    "python bkgdEst.py --file=/eos/uscms/store/user/pilot/tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=1 --date="+options.date+"",
    #ZprimeToTT_M-3000_W-300 jerUp
    "python bkgdEst.py --file=/eos/uscms/store/user/pilot/tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e --Syst=2 --date="+options.date+"",


    #ZprimeToTT_M-4000_W-400 jerDn
    "python bkgdEst.py --file=/eos/uscms/store/user/pilot/tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"",
    #ZprimeToTT_M-4000_W-400 jecDn
    "python bkgdEst.py --file=/eos/uscms/store/user/pilot/tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"",
    #ZprimeToTT_M-4000_W-400 nom
    "python bkgdEst.py --file=/eos/uscms/store/user/pilot/tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=0 --date="+options.date+"",
    #ZprimeToTT_M-4000_W-400 jecUp
    "python bkgdEst.py --file=/eos/uscms/store/user/pilot/tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=1 --date="+options.date+"",
    #ZprimeToTT_M-4000_W-400 jerUp
    "python bkgdEst.py --file=/eos/uscms/store/user/pilot/tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e --Syst=2 --date="+options.date+"",


    #ZprimeToTT_M-1500_W-15 jerDn
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"",
    #ZprimeToTT_M-1500_W-15 jecDn
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"",
    #ZprimeToTT_M-1500_W-15 nom
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=0 --date="+options.date+"",
    #ZprimeToTT_M-1500_W-15 jecUp
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=1 --date="+options.date+"",
    #ZprimeToTT_M-1500_W-15 jerUp
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e --Syst=2 --date="+options.date+"",


    #ZprimeToTT_M-1500_W-150 jerDn
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"",
    #ZprimeToTT_M-1500_W-150 jecDn
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"",
    #ZprimeToTT_M-1500_W-150 nom
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=0 --date="+options.date+"",
    #ZprimeToTT_M-1500_W-150 jecUp
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=1 --date="+options.date+"",
    #ZprimeToTT_M-1500_W-150 jerUp
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e --Syst=2 --date="+options.date+"",


    #ZprimeToTT_M-2500_W-25 jerDn
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"",
    #ZprimeToTT_M-2500_W-25 jecDn
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"",
    #ZprimeToTT_M-2500_W-25 nom
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=0 --date="+options.date+"",
    #ZprimeToTT_M-2500_W-25 jecUp
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=1 --date="+options.date+"",
    #ZprimeToTT_M-2500_W-25 jerUp
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e --Syst=2 --date="+options.date+"",


    #ZprimeToTT_M-2500_W-250 jerDn
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"",
    #ZprimeToTT_M-2500_W-250 jecDn
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"",
    #ZprimeToTT_M-2500_W-250 nom
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=0 --date="+options.date+"",
    #ZprimeToTT_M-2500_W-250 jecUp
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"",
    #ZprimeToTT_M-2500_W-250 jerUp
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e --Syst=2 --date="+options.date+"",


    #ZprimeToTT_M-3500_W-35 jerDn
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"",
    #ZprimeToTT_M-3500_W-35 jecDn
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"",
    #ZprimeToTT_M-3500_W-35 nom
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=0 --date="+options.date+"",
    #ZprimeToTT_M-3500_W-35 jecUp
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=1 --date="+options.date+"",
    #ZprimeToTT_M-3500_W-35 jerUp
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e --Syst=2 --date="+options.date+"",


    #ZprimeToTT_M-3500_W-350 jerDn
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"",
    #ZprimeToTT_M-3500_W-350 jecDn
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"",
    #ZprimeToTT_M-3500_W-350 nom
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=0 --date="+options.date+"",
    #ZprimeToTT_M-3500_W-350 jecUp
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=1 --date="+options.date+"",
    #ZprimeToTT_M-3500_W-350 jerUp
    "python bkgdEst.py --file=/eos/uscms/store/user/maral87/B2GAnaFW/Trees/tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e --Syst=2 --date="+options.date+"",


    #ZprimeToTT_M-1000_W-300 jerDn
    "python bkgdEst.py --file=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"",
    #ZprimeToTT_M-1000_W-300 jecDn
    "python bkgdEst.py --file=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"",
    #ZprimeToTT_M-1000_W-300 nom
    "python bkgdEst.py --file=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=0 --date="+options.date+"",
    #ZprimeToTT_M-1000_W-300 jecUp
    "python bkgdEst.py --file=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=1 --date="+options.date+"",
    #ZprimeToTT_M-1000_W-300 jerUp
    "python bkgdEst.py --file=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e --Syst=2 --date="+options.date+"",


    #ZprimeToTT_M-1250_W-125 jerDn
    "python bkgdEst.py --file=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"",
    #ZprimeToTT_M-1250_W-125 jecDn
    "python bkgdEst.py --file=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"",
    #ZprimeToTT_M-1250_W-125 nom
    "python bkgdEst.py --file=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=0 --date="+options.date+"",
    #ZprimeToTT_M-1250_W-125 jecUp
    "python bkgdEst.py --file=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=1 --date="+options.date+"",
    #ZprimeToTT_M-1250_W-125 jerUp
    "python bkgdEst.py --file=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e --Syst=2 --date="+options.date+"",


    #ZprimeToTT_M-2000_W-600 jerDn
    "python bkgdEst.py --file=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"",
    #ZprimeToTT_M-2000_W-600 jecDn
    "python bkgdEst.py --file=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"",
    #ZprimeToTT_M-2000_W-600 nom
    "python bkgdEst.py --file=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=0 --date="+options.date+"",
    #ZprimeToTT_M-2000_W-600 jecUp
    "python bkgdEst.py --file=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=1 --date="+options.date+"",
    #ZprimeToTT_M-2000_W-600 jerUp
    "python bkgdEst.py --file=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e --Syst=2 --date="+options.date+"",


    #ZprimeToTT_M-3000_W-900 jerDn
    "python bkgdEst.py --file=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"",
    #ZprimeToTT_M-3000_W-900 jecDn
    "python bkgdEst.py --file=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"",
    #ZprimeToTT_M-3000_W-900 nom
    "python bkgdEst.py --file=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=0 --date="+options.date+"",
    #ZprimeToTT_M-3000_W-900 jecUp
    "python bkgdEst.py --file=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=1 --date="+options.date+"",
    #ZprimeToTT_M-3000_W-900 jerUp
    "python bkgdEst.py --file=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e --Syst=2 --date="+options.date+"",

 
    #ZprimeToTT_M-4000_W-1200 jerDn
    "python bkgdEst.py --file=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=-2 --date="+options.date+"",
    #ZprimeToTT_M-4000_W-1200 jecDn
    "python bkgdEst.py --file=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=-1 --date="+options.date+"",
    #ZprimeToTT_M-4000_W-1200 nom
    "python bkgdEst.py --file=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=0 --date="+options.date+"",
    #ZprimeToTT_M-4000_W-1200 jecUp
    "python bkgdEst.py --file=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=1 --date="+options.date+"",
    #ZprimeToTT_M-4000_W-1200 jerUp
    "python bkgdEst.py --file=/eos/uscms/store/user/camclean/B2GAnaFW/Trees/tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root --mistagFile="+options.mistagFile+" --outname=outBkgdEst_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e --Syst=2 --date="+options.date+""


]

for s in path :
    print s
    subprocess.call( [s, ""], shell=True )
    print "Done!"
