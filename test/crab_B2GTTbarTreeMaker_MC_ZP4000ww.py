from CRABClient.UserUtilities import config, getUsernameFromSiteDB

config = config()
config.General.requestName = 'b2gtree_ZprimeToTT_M-4000_W-1200_RunIISpring16MiniAODv2-PUSpring16_reHLT'
config.General.transferOutputs = True
config.General.transferLogs = False
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'run_B2GTTbarTreeMaker_MC.py'
config.JobType.maxJobRuntimeMin = 2750
config.Data.inputDataset = '/ZprimeToTT_M-4000_W-1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM'
config.Data.inputDBS = 'global'
config.JobType.inputFiles = [
'/uscms_data/d2/jdolen/B2GAnaFW/CMSSW_8_0_13/src/Analysis/B2GTTbar/test/JECs/Spring16_25nsV6_MC_L1FastJet_AK8PFchs.txt',
'/uscms_data/d2/jdolen/B2GAnaFW/CMSSW_8_0_13/src/Analysis/B2GTTbar/test/JECs/Spring16_25nsV6_MC_L2Relative_AK8PFchs.txt',
'/uscms_data/d2/jdolen/B2GAnaFW/CMSSW_8_0_13/src/Analysis/B2GTTbar/test/JECs/Spring16_25nsV6_MC_L3Absolute_AK8PFchs.txt',
'/uscms_data/d2/jdolen/B2GAnaFW/CMSSW_8_0_13/src/Analysis/B2GTTbar/test/JECs/Spring16_25nsV6_MC_L2L3Residual_AK8PFchs.txt',
'/uscms_data/d2/jdolen/B2GAnaFW/CMSSW_8_0_13/src/Analysis/B2GTTbar/test/JECs/Spring16_25nsV6_MC_Uncertainty_AK8PFchs.txt',
'/uscms_data/d2/jdolen/B2GAnaFW/CMSSW_8_0_13/src/Analysis/B2GTTbar/test/JECs/Spring16_25nsV6_MC_L1FastJet_AK4PFchs.txt',
'/uscms_data/d2/jdolen/B2GAnaFW/CMSSW_8_0_13/src/Analysis/B2GTTbar/test/JECs/Spring16_25nsV6_MC_L2Relative_AK4PFchs.txt',
'/uscms_data/d2/jdolen/B2GAnaFW/CMSSW_8_0_13/src/Analysis/B2GTTbar/test/JECs/Spring16_25nsV6_MC_L3Absolute_AK4PFchs.txt',
'/uscms_data/d2/jdolen/B2GAnaFW/CMSSW_8_0_13/src/Analysis/B2GTTbar/test/JECs/Spring16_25nsV6_MC_L2L3Residual_AK4PFchs.txt',
'/uscms_data/d2/jdolen/B2GAnaFW/CMSSW_8_0_13/src/Analysis/B2GTTbar/test/JECs/Spring16_25nsV6_MC_Uncertainty_AK4PFchs.txt',
'/uscms_data/d2/jdolen/B2GAnaFW/CMSSW_8_0_13/src/Analysis/B2GTTbar/test/JECs/Spring16_25nsV6_MC_L1FastJet_AK8PFPuppi.txt',
'/uscms_data/d2/jdolen/B2GAnaFW/CMSSW_8_0_13/src/Analysis/B2GTTbar/test/JECs/Spring16_25nsV6_MC_L2Relative_AK8PFPuppi.txt',
'/uscms_data/d2/jdolen/B2GAnaFW/CMSSW_8_0_13/src/Analysis/B2GTTbar/test/JECs/Spring16_25nsV6_MC_L3Absolute_AK8PFPuppi.txt',
'/uscms_data/d2/jdolen/B2GAnaFW/CMSSW_8_0_13/src/Analysis/B2GTTbar/test/JECs/Spring16_25nsV6_MC_L2L3Residual_AK8PFPuppi.txt',
'/uscms_data/d2/jdolen/B2GAnaFW/CMSSW_8_0_13/src/Analysis/B2GTTbar/test/JECs/Spring16_25nsV6_MC_Uncertainty_AK8PFPuppi.txt',
'/uscms_data/d2/jdolen/B2GAnaFW/CMSSW_8_0_13/src/Analysis/B2GTTbar/test/JECs/Spring16_25nsV6_MC_L1FastJet_AK4PFPuppi.txt',
'/uscms_data/d2/jdolen/B2GAnaFW/CMSSW_8_0_13/src/Analysis/B2GTTbar/test/JECs/Spring16_25nsV6_MC_L2Relative_AK4PFPuppi.txt',
'/uscms_data/d2/jdolen/B2GAnaFW/CMSSW_8_0_13/src/Analysis/B2GTTbar/test/JECs/Spring16_25nsV6_MC_L3Absolute_AK4PFPuppi.txt',
'/uscms_data/d2/jdolen/B2GAnaFW/CMSSW_8_0_13/src/Analysis/B2GTTbar/test/JECs/Spring16_25nsV6_MC_L2L3Residual_AK4PFPuppi.txt',
'/uscms_data/d2/jdolen/B2GAnaFW/CMSSW_8_0_13/src/Analysis/B2GTTbar/test/JECs/Spring16_25nsV6_MC_Uncertainty_AK4PFPuppi.txt',
'/uscms_data/d2/jdolen/B2GAnaFW/CMSSW_8_0_13/src/Analysis/B2GTTbar/test/JERs/Spring16_25nsV6_MC_SF_AK8PFchs.txt'
]
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/jdolen/B2G2016/'
config.Data.publication = False
config.Site.storageSite = 'T3_US_FNALLPC'
