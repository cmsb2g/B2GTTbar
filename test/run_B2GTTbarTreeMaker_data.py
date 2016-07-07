import FWCore.ParameterSet.Config as cms

process = cms.Process("Ana")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016C/JetHT/MINIAOD/PromptReco-v2/000/275/603/00000/169B0A2E-8A3A-E611-A601-02163E011CD2.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016C/JetHT/MINIAOD/PromptReco-v2/000/275/656/00000/1CEF17DF-483B-E611-9D46-02163E0133DD.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016C/JetHT/MINIAOD/PromptReco-v2/000/275/657/00000/0ED91D8C-913B-E611-8C29-02163E0142F6.root'
    )
)

process.ana = cms.EDAnalyzer('B2GTTbarTreeMaker',
    jecPayloadsAK8chs = cms.vstring([
                                    'JECs/Spring16_25nsV6_DATA_L1FastJet_AK8PFchs.txt',
                                    'JECs/Spring16_25nsV6_DATA_L2Relative_AK8PFchs.txt',
                                    'JECs/Spring16_25nsV6_DATA_L3Absolute_AK8PFchs.txt',
                                    'JECs/Spring16_25nsV6_DATA_L2L3Residual_AK8PFchs.txt',
                                    'JECs/Spring16_25nsV6_DATA_Uncertainty_AK8PFchs.txt'
                                    ]),
    jecPayloadsAK4chs = cms.vstring([
                                    'JECs/Spring16_25nsV6_DATA_L1FastJet_AK4PFchs.txt',
                                    'JECs/Spring16_25nsV6_DATA_L2Relative_AK4PFchs.txt',
                                    'JECs/Spring16_25nsV6_DATA_L3Absolute_AK4PFchs.txt',
                                    'JECs/Spring16_25nsV6_DATA_L2L3Residual_AK4PFchs.txt',
                                    'JECs/Spring16_25nsV6_DATA_Uncertainty_AK4PFchs.txt'
                                    ]),
    jecPayloadsAK8pup = cms.vstring([
                                    'JECs/Spring16_25nsV6_DATA_L1FastJet_AK8PFPuppi.txt',
                                    'JECs/Spring16_25nsV6_DATA_L2Relative_AK8PFPuppi.txt',
                                    'JECs/Spring16_25nsV6_DATA_L3Absolute_AK8PFPuppi.txt',
                                    'JECs/Spring16_25nsV6_DATA_L2L3Residual_AK8PFPuppi.txt',
                                    'JECs/Spring16_25nsV6_DATA_Uncertainty_AK8PFPuppi.txt'
                                    ]),
    jecPayloadsAK4pup = cms.vstring([
                                    'JECs/Spring16_25nsV6_DATA_L1FastJet_AK4PFPuppi.txt',
                                    'JECs/Spring16_25nsV6_DATA_L2Relative_AK4PFPuppi.txt',
                                    'JECs/Spring16_25nsV6_DATA_L3Absolute_AK4PFPuppi.txt',
                                    'JECs/Spring16_25nsV6_DATA_L2L3Residual_AK4PFPuppi.txt',
                                    'JECs/Spring16_25nsV6_DATA_Uncertainty_AK4PFPuppi.txt'
                                    ]),
    jerSFtext         = cms.string('JERs/Spring16_25nsV6_MC_SF_AK8PFchs.txt'
                                    )
)

process.TFileService = cms.Service("TFileService",
      fileName = cms.string("tree_data.root"),
      closeFileFast = cms.untracked.bool(True)
  )

process.p = cms.Path(process.ana)
