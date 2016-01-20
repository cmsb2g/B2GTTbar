from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'ZprimeAnaTrees_Run2015D_v74x_V8p2_25ns_version2_2015_10_27'
config.General.workArea = 'ZprimeAnaRunII'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ZprimeB2G_B2GAnaFW_cfg.py'
config.JobType.outputFiles = ['histo_DATA.root']

config.section_("Data")
config.Data.inputDataset = '/JetHT/jdolen-B2GAnaFW_v74x_V8p2_25ns-2a65c0511f59dc4370ba0d069e474e54/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 2
config.Data.ignoreLocality = True
config.Data.publication = False
# This string is used to construct the output dataset name

config.section_("Site")
config.Site.storageSite = 'T3_US_FNALLPC'
#config.Site.whitelist = ["T2_US*"]
