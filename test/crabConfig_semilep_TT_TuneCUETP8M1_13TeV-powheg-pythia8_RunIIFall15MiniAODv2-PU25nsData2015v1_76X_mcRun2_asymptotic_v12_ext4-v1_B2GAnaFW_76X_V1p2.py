from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'SemiLepAnaTrees_TT_TuneCUETP8M1_13TeV-powheg-pythia8_B2GAnaFW_76X_V1p2'
config.General.workArea = 'ZprimeAnaRunIISemiLep'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'PSet.py'
config.JobType.inputFiles = ['FrameworkJobReport.xml', 'execute_for_crab.py', 'NtupleReader_fwlite.py', 'leptonic_nu_z_component.py', 'JECs', 'ModMass_2015_09_22.root', 'MistagRate_2015_09_25.root', 'PUweight20160316.root', 'MyDataPileupHistogram.root', 'MyDataPileupHistogramUP.root', 'MyDataPileupHistogramDN.root']
config.JobType.outputFiles = ['outplots.root']
config.JobType.scriptExe = 'execute_for_crab_semilep_ttbar.sh'

config.section_("Data")
config.Data.inputDataset = '/TT_TuneCUETP8M1_13TeV-powheg-pythia8/srappocc-B2GAnaFW_76X_V1p2-9b209586075fb162e747a1015dbd24f8/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 5
config.Data.ignoreLocality = True
config.Data.publication = False
# This string is used to construct the output dataset name

config.section_("Site")
config.Site.storageSite = 'T3_US_FNALLPC'
#config.Site.whitelist = ["T2_HU_Budapest"]
