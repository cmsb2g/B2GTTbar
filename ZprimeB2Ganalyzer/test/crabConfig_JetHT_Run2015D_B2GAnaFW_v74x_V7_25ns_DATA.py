from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'ZprimeAnaTrees_Run2015D-PromptReco-v3_Sep25_v74x_V7_25ns_2015_10_05'
config.General.workArea = 'ZprimeAnaRunII'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ZprimeB2G_JetHT_Run2015D_B2GAnaFW_v74x_V7_25ns_DATA_cfg.py'
config.JobType.outputFiles = ['histo_DATA.root']

config.section_("Data")
config.Data.inputDataset = '/JetHT/knash-crab_Run2015D-PromptReco-v3_Sep25_v74x_V7_25ns-a32da5ec5dfae8851e50d18ebe4dfe7f/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 2
config.Data.ignoreLocality = True
config.Data.publication = False
# This string is used to construct the output dataset name

config.section_("Site")
config.Site.storageSite = 'T3_US_FNALLPC'
