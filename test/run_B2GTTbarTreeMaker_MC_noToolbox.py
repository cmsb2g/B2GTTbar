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

#----------------------------------------------------------------------------------------
process.load('RecoMET.METFilters.BadChargedCandidateFilter_cfi')
process.load('RecoMET.METFilters.BadPFMuonFilter_cfi')
process.BadChargedCandidateFilter.muons = cms.InputTag("slimmedMuons")
process.BadChargedCandidateFilter.PFCandidates = cms.InputTag("packedPFCandidates")
process.BadChargedCandidateFilter.debug = cms.bool(False)
process.BadPFMuonFilter.muons = cms.InputTag("slimmedMuons")
process.BadPFMuonFilter.PFCandidates = cms.InputTag("packedPFCandidates")
process.BadPFMuonFilter.debug = cms.bool(False)

#----------------------------------------------------------------------------------------
# Puppi (https://twiki.cern.ch/twiki/bin/viewauth/CMS/PUPPI)
process.load('CommonTools/PileupAlgos/Puppi_cff')
process.puppi.candName = cms.InputTag('packedPFCandidates')
process.puppi.vertexName = cms.InputTag('offlineSlimmedPrimaryVertices')
process.puppi.useExistingWeights = cms.bool(True)
#process.puppiOnTheFly = process.puppi.clone()
#process.puppiOnTheFly.useExistingWeights = True

#----------------------------------------------------------------------------------------
# Toolbox (https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetToolbox)
# from JMEAnalysis.JetToolbox.jetToolbox_cff import jetToolbox

# ak8Cut='pt > 200 && abs(eta) < 2.4'
# runMC=True

# listBTagInfos = [
#      'pfInclusiveSecondaryVertexFinderTagInfos',
# ]
# listBtagDiscriminatorsAK8 = [ 
#     'pfJetProbabilityBJetTags',
#     'pfCombinedInclusiveSecondaryVertexV2BJetTags',
#     'pfCombinedMVAV2BJetTags',
#     'pfCombinedCvsLJetTags',
#     'pfCombinedCvsBJetTags',
#     'pfBoostedDoubleSecondaryVertexAK8BJetTags',
#     'pfBoostedDoubleSecondaryVertexCA15BJetTags',
# ]
# #selectedPatJetsAK8PFCHS
# jetToolbox( process, 'ak8', 'ak8JetSubs', 'out', runOnMC=runMC, addSoftDropSubjets=True, addTrimming=True, rFiltTrim=0.1, addPruning=True, addFiltering=True, addSoftDrop=True, addNsub=True, bTagInfos=listBTagInfos, bTagDiscriminators=listBtagDiscriminatorsAK8, addCMSTopTagger=True, Cut=ak8Cut , addNsubSubjets=True, subjetMaxTau=4 )

# #selectedPatJetsAK8PFPuppi
# jetToolbox( process, 'ak8', 'ak8JetSubs', 'out', runOnMC=runMC, PUMethod='Puppi', newPFCollection=True, nameNewPFCollection='puppi', addSoftDropSubjets=True, addTrimming=True, addPruning=True, addFiltering=True, addSoftDrop=True, addNsub=True, bTagInfos=listBTagInfos, bTagDiscriminators=listBtagDiscriminatorsAK8, addCMSTopTagger=True, Cut=ak8Cut, addNsubSubjets=True, subjetMaxTau=4 )



#----------------------------------------------------------------------------------------


process.ana = cms.EDAnalyzer('B2GTTbarTreeMaker',
    useToolbox    = cms.bool(False),
    verbose       = cms.bool(False),
    verboseGen    = cms.bool(False),
    runGenLoop    = cms.bool(True),
    ak8chsInput   = cms.InputTag("slimmedJetsAK8"),
    ak8puppiInput = cms.InputTag("slimmedJetsAK8"),
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

#----------------------------------------------------------------------------------------
process.TFileService = cms.Service("TFileService",
      fileName = cms.string("tree.root"),
      closeFileFast = cms.untracked.bool(True)
  )

process.p = cms.Path(
  process.BadChargedCandidateFilter*
  process.BadPFMuonFilter*
  process.ana
)
