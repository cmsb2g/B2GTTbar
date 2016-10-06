from CRABClient.UserUtilities import config, getUsernameFromSiteDB

config = config()
config.General.requestName = 'b2gtree_QCD_Pt_3200toInf_pythia8_RunIISpring16MiniAODv2_reHLT_V3'
config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'run_B2GTTbarTreeMaker_MC_Toolbox.py'
config.JobType.maxJobRuntimeMin = 2750
config.Data.inputDataset = '/QCD_Pt_3200toInf_TuneCUETP8M1_13TeV_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM'
config.Data.inputDBS = 'global'
config.JobType.inputFiles = [
'PUweight20160908.root',
'Spring16_25nsV6_MC_L1FastJet_AK8PFchs.txt',
'Spring16_25nsV6_MC_L2Relative_AK8PFchs.txt',
'Spring16_25nsV6_MC_L3Absolute_AK8PFchs.txt',
'Spring16_25nsV6_MC_L2L3Residual_AK8PFchs.txt',
'Spring16_25nsV6_MC_Uncertainty_AK8PFchs.txt',
'Spring16_25nsV6_MC_L1FastJet_AK4PFchs.txt',
'Spring16_25nsV6_MC_L2Relative_AK4PFchs.txt',
'Spring16_25nsV6_MC_L3Absolute_AK4PFchs.txt',
'Spring16_25nsV6_MC_L2L3Residual_AK4PFchs.txt',
'Spring16_25nsV6_MC_Uncertainty_AK4PFchs.txt',
'Spring16_25nsV6_MC_L1FastJet_AK8PFPuppi.txt',
'Spring16_25nsV6_MC_L2Relative_AK8PFPuppi.txt',
'Spring16_25nsV6_MC_L3Absolute_AK8PFPuppi.txt',
'Spring16_25nsV6_MC_L2L3Residual_AK8PFPuppi.txt',
'Spring16_25nsV6_MC_Uncertainty_AK8PFPuppi.txt',
'Spring16_25nsV6_MC_L1FastJet_AK4PFPuppi.txt',
'Spring16_25nsV6_MC_L2Relative_AK4PFPuppi.txt',
'Spring16_25nsV6_MC_L3Absolute_AK4PFPuppi.txt',
'Spring16_25nsV6_MC_L2L3Residual_AK4PFPuppi.txt',
'Spring16_25nsV6_MC_Uncertainty_AK4PFPuppi.txt',
'Spring16_25nsV6_MC_SF_AK8PFchs.txt'
]
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 3
config.Data.outLFNDirBase = '/store/user/jdolen/B2G2016/'
config.Data.publication = False
config.Site.storageSite = 'T3_US_FNALLPC'
