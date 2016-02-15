from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'ZprimeAnaTrees_JetHT_Run2015D-05Oct2015-v1_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON_trigger'
config.General.workArea = 'ZprimeAnaRunII'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'PSet.py'
config.JobType.inputFiles = ['FrameworkJobReport.xml', 'execute_for_crab.py', 'NtupleReader_fwlite.py', 'leptonic_nu_z_component.py', 'JECs', 'ModMass_2015_09_22.root', 'MistagRateBigBins_JetHT_knash_crab_Run2015D_PromptReco_v3_Sep25_v74x_V7_25ns_All_2015_09_28.root', 'pileup_reweight.root']
config.JobType.outputFiles = ['outplots.root']
config.JobType.scriptExe = 'execute_for_crab_dataTrigger.sh'

config.section_("Data")
config.Data.inputDataset = '/JetHT/jdolen-Run2015D-05Oct2015-v1_B2GAnaFW_v74x_V8p4_25ns_Nov13silverJSON-ff3168b63d5cee365f49bf7ea3ba6ef3/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 2
config.Data.ignoreLocality = True
config.Data.publication = False
# This string is used to construct the output dataset name

config.section_("Site")
config.Site.storageSite = 'T3_US_FNALLPC'
#config.Site.whitelist = ["T2_HU_Budapest"]
