from CRABClient.UserUtilities import config, getUsernameFromSiteDB

config = config()
config.General.requestName = 'b2gtree_SingleMuon_Run2016F-PromptReco-v1_JSONsept30_V3'
config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'run_B2GTTbarTreeMaker_data_Toolbox.py'
config.JobType.maxJobRuntimeMin = 2750
config.Data.inputDataset = '/SingleMuon/Run2016F-PromptReco-v1/MINIAOD'
config.Data.inputDBS = 'global'
config.JobType.inputFiles = [
'PUweight20160908.root',
'Spring16_25nsV6_DATA_L1FastJet_AK8PFchs.txt',
'Spring16_25nsV6_DATA_L2Relative_AK8PFchs.txt',
'Spring16_25nsV6_DATA_L3Absolute_AK8PFchs.txt',
'Spring16_25nsV6_DATA_L2L3Residual_AK8PFchs.txt',
'Spring16_25nsV6_DATA_Uncertainty_AK8PFchs.txt',
'Spring16_25nsV6_DATA_L1FastJet_AK4PFchs.txt',
'Spring16_25nsV6_DATA_L2Relative_AK4PFchs.txt',
'Spring16_25nsV6_DATA_L3Absolute_AK4PFchs.txt',
'Spring16_25nsV6_DATA_L2L3Residual_AK4PFchs.txt',
'Spring16_25nsV6_DATA_Uncertainty_AK4PFchs.txt',
'Spring16_25nsV6_DATA_L1FastJet_AK8PFPuppi.txt',
'Spring16_25nsV6_DATA_L2Relative_AK8PFPuppi.txt',
'Spring16_25nsV6_DATA_L3Absolute_AK8PFPuppi.txt',
'Spring16_25nsV6_DATA_L2L3Residual_AK8PFPuppi.txt',
'Spring16_25nsV6_DATA_Uncertainty_AK8PFPuppi.txt',
'Spring16_25nsV6_DATA_L1FastJet_AK4PFPuppi.txt',
'Spring16_25nsV6_DATA_L2Relative_AK4PFPuppi.txt',
'Spring16_25nsV6_DATA_L3Absolute_AK4PFPuppi.txt',
'Spring16_25nsV6_DATA_L2L3Residual_AK4PFPuppi.txt',
'Spring16_25nsV6_DATA_Uncertainty_AK4PFPuppi.txt',
'Spring16_25nsV6_MC_SF_AK8PFchs.txt'
]
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 20
config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV/Cert_271036-280385_13TeV_PromptReco_Collisions16_JSON_NoL1T_v2.txt'
#config.Data.runRange
config.Data.outLFNDirBase = '/store/user/jdolen/B2G2016/'
config.Data.publication = False
config.Site.storageSite = 'T3_US_FNALLPC'
