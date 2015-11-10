from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'ZprimeAnaTrees_QCD_HT2000toInf_RunIISpring15DR74_25ns_version2_2015_10_29'
config.General.workArea = 'ZprimeAnaRunII'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ZprimeB2G_B2GAnaFW_cfg.py'
config.JobType.outputFiles = ['histo_DATA.root']

config.section_("Data")
config.Data.inputDataset = '/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/jkarancs-B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1-acabfdaa5b997f33302a13d996253c07/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 2
config.Data.ignoreLocality = True
config.Data.publication = False
# This string is used to construct the output dataset name

config.section_("Site")
config.Site.storageSite = 'T3_US_FNALLPC'
config.Site.whitelist = ["T2_HU_Budapest"]
