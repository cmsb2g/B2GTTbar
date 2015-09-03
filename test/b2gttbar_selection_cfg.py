import FWCore.ParameterSet.Config as cms

process = cms.Process("b2gttbar")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.categories.append('HLTrigReport')
### Output Report
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
### Number of maximum events to process
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
### Source file
process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring(
            ['root://cmsxrootd.fnal.gov//store/user/oiorio/ttDM/samples/July2015/TT_TuneCUETP8M1_13TeV-powheg-pythia8/EDMNTUPLE_28July/150727_233639/0000/B2GEDMNtuple_140.root']
        )
)

process.ak8PtFilter = cms.EDFilter(
    'EDB2GTTbarVectorFilterFloat',
    src  = cms.InputTag("jetsAK8", "jetAK8Pt"),
    minVal = cms.double(200.),
    filter = cms.bool(True)
    )

process.seq = cms.Sequence( process.ak8PtFilter )
process.path = cms.Path( process.seq)

process.out = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('B2GEDMNtuple.root'),
    SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('path') ),
    outputCommands = cms.untracked.vstring("keep *")
    )

process.endPath = cms.EndPath(process.out)
process.schedule = cms.Schedule(process.path,process.endPath)
