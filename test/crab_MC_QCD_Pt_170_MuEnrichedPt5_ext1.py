from CRABClient.UserUtilities import config, getUsernameFromSiteDB
import os

config = config()
config.General.requestName = 'b2gtreeV5_QCD_Pt_170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2'
config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'run_B2GTTbarTreeMaker_MC_Toolbox.py'
config.JobType.maxJobRuntimeMin = 2750
config.Data.inputDataset = '/QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM'
config.Data.inputDBS = 'global'
config.JobType.inputFiles = [
'PUweight_FinalJSON2016_PileupJSONFeb2017_Xsec69200nominal_MCRunIISummer16MiniAODv2_PUMoriond17.root',

os.environ['CMSSW_BASE'] + '/src/JMEAnalysis/JECDatabase/textFiles/Summer16_23Sep2016V4_MC/Summer16_23Sep2016V4_MC_L1FastJet_AK8PFchs.txt'     ,
os.environ['CMSSW_BASE'] + '/src/JMEAnalysis/JECDatabase/textFiles/Summer16_23Sep2016V4_MC/Summer16_23Sep2016V4_MC_L2Relative_AK8PFchs.txt'    ,
os.environ['CMSSW_BASE'] + '/src/JMEAnalysis/JECDatabase/textFiles/Summer16_23Sep2016V4_MC/Summer16_23Sep2016V4_MC_L3Absolute_AK8PFchs.txt'    ,
os.environ['CMSSW_BASE'] + '/src/JMEAnalysis/JECDatabase/textFiles/Summer16_23Sep2016V4_MC/Summer16_23Sep2016V4_MC_L2L3Residual_AK8PFchs.txt'  ,
os.environ['CMSSW_BASE'] + '/src/JMEAnalysis/JECDatabase/textFiles/Summer16_23Sep2016V4_MC/Summer16_23Sep2016V4_MC_Uncertainty_AK8PFchs.txt'   ,
os.environ['CMSSW_BASE'] + '/src/JMEAnalysis/JECDatabase/textFiles/Summer16_23Sep2016V4_MC/Summer16_23Sep2016V4_MC_L1FastJet_AK4PFchs.txt'     ,
os.environ['CMSSW_BASE'] + '/src/JMEAnalysis/JECDatabase/textFiles/Summer16_23Sep2016V4_MC/Summer16_23Sep2016V4_MC_L2Relative_AK4PFchs.txt'    ,
os.environ['CMSSW_BASE'] + '/src/JMEAnalysis/JECDatabase/textFiles/Summer16_23Sep2016V4_MC/Summer16_23Sep2016V4_MC_L3Absolute_AK4PFchs.txt'    ,
os.environ['CMSSW_BASE'] + '/src/JMEAnalysis/JECDatabase/textFiles/Summer16_23Sep2016V4_MC/Summer16_23Sep2016V4_MC_L2L3Residual_AK4PFchs.txt'  ,
os.environ['CMSSW_BASE'] + '/src/JMEAnalysis/JECDatabase/textFiles/Summer16_23Sep2016V4_MC/Summer16_23Sep2016V4_MC_Uncertainty_AK4PFchs.txt'   ,
os.environ['CMSSW_BASE'] + '/src/JMEAnalysis/JECDatabase/textFiles/Summer16_23Sep2016V4_MC/Summer16_23Sep2016V4_MC_L1FastJet_AK8PFPuppi.txt'   ,
os.environ['CMSSW_BASE'] + '/src/JMEAnalysis/JECDatabase/textFiles/Summer16_23Sep2016V4_MC/Summer16_23Sep2016V4_MC_L2Relative_AK8PFPuppi.txt'  ,
os.environ['CMSSW_BASE'] + '/src/JMEAnalysis/JECDatabase/textFiles/Summer16_23Sep2016V4_MC/Summer16_23Sep2016V4_MC_L3Absolute_AK8PFPuppi.txt'  ,
os.environ['CMSSW_BASE'] + '/src/JMEAnalysis/JECDatabase/textFiles/Summer16_23Sep2016V4_MC/Summer16_23Sep2016V4_MC_L2L3Residual_AK8PFPuppi.txt',
os.environ['CMSSW_BASE'] + '/src/JMEAnalysis/JECDatabase/textFiles/Summer16_23Sep2016V4_MC/Summer16_23Sep2016V4_MC_Uncertainty_AK8PFPuppi.txt' ,
os.environ['CMSSW_BASE'] + '/src/JMEAnalysis/JECDatabase/textFiles/Summer16_23Sep2016V4_MC/Summer16_23Sep2016V4_MC_L1FastJet_AK4PFPuppi.txt'   ,
os.environ['CMSSW_BASE'] + '/src/JMEAnalysis/JECDatabase/textFiles/Summer16_23Sep2016V4_MC/Summer16_23Sep2016V4_MC_L2Relative_AK4PFPuppi.txt'  ,
os.environ['CMSSW_BASE'] + '/src/JMEAnalysis/JECDatabase/textFiles/Summer16_23Sep2016V4_MC/Summer16_23Sep2016V4_MC_L3Absolute_AK4PFPuppi.txt'  ,
os.environ['CMSSW_BASE'] + '/src/JMEAnalysis/JECDatabase/textFiles/Summer16_23Sep2016V4_MC/Summer16_23Sep2016V4_MC_L2L3Residual_AK4PFPuppi.txt',
os.environ['CMSSW_BASE'] + '/src/JMEAnalysis/JECDatabase/textFiles/Summer16_23Sep2016V4_MC/Summer16_23Sep2016V4_MC_Uncertainty_AK4PFPuppi.txt' ,

os.environ['CMSSW_BASE'] + '/src/JMEAnalysis/JRDatabase/textFiles/Spring16_25nsV10_MC/Spring16_25nsV10_MC_PtResolution_AK4PFchs.txt',
os.environ['CMSSW_BASE'] + '/src/JMEAnalysis/JRDatabase/textFiles/Spring16_25nsV10_MC/Spring16_25nsV10_MC_PtResolution_AK8PFchs.txt',
os.environ['CMSSW_BASE'] + '/src/JMEAnalysis/JRDatabase/textFiles/Spring16_25nsV10_MC/Spring16_25nsV10_MC_SF_AK8PFchs.txt'
]
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 2
config.Data.outLFNDirBase = '/store/user/jdolen/B2G2016/'
config.Data.publication = False
config.Site.storageSite = 'T3_US_FNALLPC'
