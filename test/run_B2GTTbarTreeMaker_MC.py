import FWCore.ParameterSet.Config as cms

process = cms.Process("Ana")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
      'file:root://cmsxrootd.fnal.gov///store/user/jdolen/B2G2016/ZprimeToTT_M-3000_W-30_TuneCUETP8M1_13TeV-madgraphMLM_RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_MINIAOD.root'
      #'file:root://cmsxrootd.fnal.gov//store/mc/RunIISpring16MiniAODv2/ZprimeToTT_M-2000_W-20_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/90000/68594422-C039-E611-91D0-842B2B17F73D.root',
      #'file:root://cmsxrootd.fnal.gov//store/mc/RunIISpring16MiniAODv2/ZprimeToTT_M-2000_W-20_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/90000/78371B76-D439-E611-896B-B083FECF837B.root',
      #'file:root://cmsxrootd.fnal.gov//store/mc/RunIISpring16MiniAODv2/ZprimeToTT_M-2000_W-20_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/90000/847453B3-F739-E611-909C-90B11C0BCBC2.root',
      #'file:root://cmsxrootd.fnal.gov//store/mc/RunIISpring16MiniAODv2/ZprimeToTT_M-2000_W-20_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/90000/AA4C714B-B239-E611-8CF5-782BCB63EBF5.root',
      #'file:root://cmsxrootd.fnal.gov//store/mc/RunIISpring16MiniAODv2/ZprimeToTT_M-2000_W-20_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/90000/D85CC004-F839-E611-A153-B083FED429D6.root'    
    )
)

process.load('Configuration.StandardSequences.Services_cff')
process.load('RecoMET.METFilters.BadChargedCandidateFilter_cfi')
process.load('RecoMET.METFilters.BadPFMuonFilter_cfi')
## for miniAOD running
process.BadChargedCandidateFilter.muons = cms.InputTag("slimmedMuons")
process.BadChargedCandidateFilter.PFCandidates = cms.InputTag("packedPFCandidates")
process.BadChargedCandidateFilter.debug = cms.bool(False)
process.BadPFMuonFilter.muons = cms.InputTag("slimmedMuons")
process.BadPFMuonFilter.PFCandidates = cms.InputTag("packedPFCandidates")
process.BadPFMuonFilter.debug = cms.bool(False)



process.ana = cms.EDAnalyzer('B2GTTbarTreeMaker',
    jecPayloadsAK8chs = cms.vstring([
                                    'Spring16_25nsV6_MC_L1FastJet_AK8PFchs.txt',
                                    'Spring16_25nsV6_MC_L2Relative_AK8PFchs.txt',
                                    'Spring16_25nsV6_MC_L3Absolute_AK8PFchs.txt',
                                    'Spring16_25nsV6_MC_L2L3Residual_AK8PFchs.txt',
                                    'Spring16_25nsV6_MC_Uncertainty_AK8PFchs.txt'
                                    ]),
    jecPayloadsAK4chs = cms.vstring([
                                    'Spring16_25nsV6_MC_L1FastJet_AK4PFchs.txt',
                                    'Spring16_25nsV6_MC_L2Relative_AK4PFchs.txt',
                                    'Spring16_25nsV6_MC_L3Absolute_AK4PFchs.txt',
                                    'Spring16_25nsV6_MC_L2L3Residual_AK4PFchs.txt',
                                    'Spring16_25nsV6_MC_Uncertainty_AK4PFchs.txt'
                                    ]),
    jecPayloadsAK8pup = cms.vstring([
                                    'Spring16_25nsV6_MC_L1FastJet_AK8PFPuppi.txt',
                                    'Spring16_25nsV6_MC_L2Relative_AK8PFPuppi.txt',
                                    'Spring16_25nsV6_MC_L3Absolute_AK8PFPuppi.txt',
                                    'Spring16_25nsV6_MC_L2L3Residual_AK8PFPuppi.txt',
                                    'Spring16_25nsV6_MC_Uncertainty_AK8PFPuppi.txt'
                                    ]),
    jecPayloadsAK4pup = cms.vstring([
                                    'Spring16_25nsV6_MC_L1FastJet_AK4PFPuppi.txt',
                                    'Spring16_25nsV6_MC_L2Relative_AK4PFPuppi.txt',
                                    'Spring16_25nsV6_MC_L3Absolute_AK4PFPuppi.txt',
                                    'Spring16_25nsV6_MC_L2L3Residual_AK4PFPuppi.txt',
                                    'Spring16_25nsV6_MC_Uncertainty_AK4PFPuppi.txt'
                                    ]),
    jerSFtext         = cms.string('Spring16_25nsV6_MC_SF_AK8PFchs.txt'
                                    )
)

process.TFileService = cms.Service("TFileService",
      fileName = cms.string("tree.root"),
      closeFileFast = cms.untracked.bool(True)
  )

process.p = cms.Path(
  process.BadChargedCandidateFilter*
  process.BadPFMuonFilter*
  process.ana
)
