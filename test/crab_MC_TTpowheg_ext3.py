from CRABClient.UserUtilities import config, getUsernameFromSiteDB

config = config()
config.General.requestName = 'b2gtreeV4_TT_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISpring16MiniAODv2-PUSpring16_reHLT_ext3_try2'
config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'run_B2GTTbarTreeMaker_MC_Toolbox.py'
config.JobType.maxJobRuntimeMin = 2750
config.Data.inputDataset = '/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext3-v1/MINIAODSIM'
config.Data.inputDBS = 'global'
config.JobType.inputFiles = [
'PUweight_Nov4JSON_Nov6PiileupJSON_Xsec72383_MCRunIISpring16MiniAODv2.root',
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
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/jdolen/B2G2016/'
config.Data.publication = False
config.Site.storageSite = 'T3_US_FNALLPC'
