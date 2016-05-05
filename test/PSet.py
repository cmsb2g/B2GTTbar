import FWCore.ParameterSet.Config as cms

process = cms.Process('NoSplit')

process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring([
    '/store/group/lpctlbsm/B2GAnaFW_76X_V2p1/TT_TuneCUETP8M1_13TeV-powheg-pythia8/B2GAnaFW_76X_V1p2/160503_021329/0000/B2GEDMNtuple_1.root'
            ]))
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(100))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
