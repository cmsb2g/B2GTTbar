#

import FWCore.ParameterSet.Config as cms

process = cms.Process("Ana")

#----------------------------------------------------------------------------------------
### SETUP
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("Configuration.EventContent.EventContent_cff")
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.GlobalTag.globaltag = '80X_mcRun2_asymptotic_2016_TrancheIV_v8'
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.options.allowUnscheduled = cms.untracked.bool(True)

isMC   = True

#----------------------------------------------------------------------------------------
### INPUT
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
      'root://cmsxrootd.fnal.gov///store/mc/RunIISummer16MiniAODv2/ZprimeToTT_M-3000_W-30_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/80000/46F4D728-78BE-E611-ABD3-0CC47A5FBE31.root'
      #'root://cmsxrootd.fnal.gov///store/mc/RunIISummer16MiniAODv2/ZprimeToTT_M-3000_W-30_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/80000/D6D620EF-73BE-E611-8BFB-B499BAA67780.root'  
    )
)

#----------------------------------------------------------------------------------------
### MET Filters
process.load('RecoMET.METFilters.BadChargedCandidateFilter_cfi')
process.load('RecoMET.METFilters.BadPFMuonFilter_cfi')
process.BadChargedCandidateFilter.muons = cms.InputTag("slimmedMuons")
process.BadChargedCandidateFilter.PFCandidates = cms.InputTag("packedPFCandidates")
process.BadChargedCandidateFilter.debug = cms.bool(False)
process.BadPFMuonFilter.muons = cms.InputTag("slimmedMuons")
process.BadPFMuonFilter.PFCandidates = cms.InputTag("packedPFCandidates")
process.BadPFMuonFilter.debug = cms.bool(False)


#----------------------------------------------------------------------------------------
### VID
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
dataFormat = DataFormat.MiniAOD
switchOnVIDElectronIdProducer(process, dataFormat)
my_id_modules = [
    'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronHLTPreselecition_Summer16_V1_cff',
    'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Summer16_80X_V1_cff',
    'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV70_cff'
]

for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

#----------------------------------------------------------------------------------------
### MET   //https://twiki.cern.ch/twiki/bin/view/CMS/MissingETUncertaintyPrescription
from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD

# If you only want to re-correct and get the proper uncertainties
runMetCorAndUncFromMiniAOD(process,
                       isData=not isMC,
                       )

# If you would like to re-cluster and get the proper uncertainties
# runMetCorAndUncFromMiniAOD(process,
#                        isData=True (or False),
#                        pfCandColl=cms.InputTag("packedPFCandidates"),
#                        recoMetFromPFCs=True,
#                        )

#----------------------------------------------------------------------------------------
### Puppi (https://twiki.cern.ch/twiki/bin/viewauth/CMS/PUPPI)
process.load('CommonTools/PileupAlgos/Puppi_cff')
process.puppi.candName = cms.InputTag('packedPFCandidates')
process.puppi.vertexName = cms.InputTag('offlineSlimmedPrimaryVertices')
process.puppi.useExistingWeights = cms.bool(True)
process.puppiOnTheFly = process.puppi.clone()
process.puppiOnTheFly.useExistingWeights = True


#----------------------------------------------------------------------------------------
### Toolbox (https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetToolbox)
from JMEAnalysis.JetToolbox.jetToolbox_cff import jetToolbox

ak8Cut    = 'pt > 170 && abs(eta) < 2.5'
ak8pupCut = 'pt > 140 && abs(eta) < 2.5'

listBTagInfos = [
     'pfInclusiveSecondaryVertexFinderTagInfos',
]
listBtagDiscriminatorsAK8 = [ 
    # 'pfJetProbabilityBJetTags',
    'pfCombinedInclusiveSecondaryVertexV2BJetTags',
    # 'pfCombinedMVAV2BJetTags',
    # 'pfCombinedCvsLJetTags',
    # 'pfCombinedCvsBJetTags',
    # 'pfBoostedDoubleSecondaryVertexAK8BJetTags',
    # 'pfBoostedDoubleSecondaryVertexCA15BJetTags',
]

# |---- jetToolBox: JETTOOLBOX RUNNING ON MiniAOD FOR AK8 JETS USING CHS
# |---- jetToolBox: Applying this corrections: ('AK8PFchs', ['L1FastJet', 'L2Relative', 'L3Absolute'], 'None')
# |---- jetToolBox: Running ak8PFJetsCHSSoftDropMass, selectedPatJetsAK8PFCHSSoftDropPacked, selectedPatJetsAK8PFCHSSoftDropSubjets, ak8PFJetsCHSPrunedMass, ak8PFJetsCHSTrimmedMass, ak8PFJetsCHSFilteredMass, NjettinessAK8CHS, NsubjettinessAK8PFCHSSoftDropSubjets.
# |---- jetToolBox: Creating selectedPatJetsAK8PFCHS collection.
# vector<pat::Jet>                      "selectedPatJetsAK8PFCHS"   ""               "Ana"     
# vector<pat::Jet>                      "selectedPatJetsAK8PFCHSSoftDropPacked"   ""               "Ana"     
# vector<pat::Jet>                      "selectedPatJetsAK8PFCHSSoftDropPacked"   "SubJets"        "Ana"     
# vector<reco::GenJet>                  "selectedPatJetsAK8PFCHS"   "genJets"        "Ana"     
# vector<reco::PFCandidate>             "selectedPatJetsAK8PFCHS"   "pfCandidates"   "Ana"    

jetToolbox( process, 'ak8', 'ak8JetSubs', 'out', 
  runOnMC = isMC, 
  PUMethod='CHS', 
  # updateCollection='slimmedJetsAK8', # can't run groomers on this yet
  # JETCorrPayload='AK8PFchs', # needed for update collection
  addSoftDropSubjets = True, 
  addTrimming = True, rFiltTrim=0.2, ptFrac=0.05,
  addPruning = True, 
  addFiltering = True, 
  addSoftDrop = True, 
  addNsub = True, 
  bTagInfos = listBTagInfos, 
  bTagDiscriminators = listBtagDiscriminatorsAK8, 
  addCMSTopTagger = False, 
  Cut = ak8Cut , 
  addNsubSubjets = True, 
  subjetMaxTau = 3 )


# |---- jetToolBox: JETTOOLBOX RUNNING ON MiniAOD FOR AK8 JETS USING Puppi
# |---- jetToolBox: Applying this corrections: ('AK8PFPuppi', ['L2Relative', 'L3Absolute'], 'None')
# |---- jetToolBox: Running ak8PFJetsPuppiSoftDropMass, selectedPatJetsAK8PFPuppiSoftDropPacked, selectedPatJetsAK8PFPuppiSoftDropSubjets, ak8PFJetsPuppiPrunedMass, ak8PFJetsPuppiTrimmedMass, ak8PFJetsPuppiFilteredMass, NjettinessAK8Puppi, NsubjettinessAK8PFPuppiSoftDropSubjets.
# |---- jetToolBox: Creating selectedPatJetsAK8PFPuppi collection.
# vector<pat::Jet>                      "selectedPatJetsAK8PFPuppi"   ""               "Ana"     
# vector<pat::Jet>                      "selectedPatJetsAK8PFPuppiSoftDropPacked"   ""               "Ana"  
# vector<pat::Jet>                      "selectedPatJetsAK8PFPuppiSoftDropPacked"   "SubJets"        "Ana"     
# vector<reco::GenJet>                  "selectedPatJetsAK8PFPuppi"   "genJets"        "Ana"     
# vector<reco::PFCandidate>             "selectedPatJetsAK8PFPuppi"   "pfCandidates"   "Ana"     


jetToolbox( process, 'ak8', 'ak8JetSubs', 'out', 
  runOnMC = isMC, 
  newPFCollection=True, 
  nameNewPFCollection='puppiOnTheFly',
  PUMethod='Puppi', 
  addSoftDropSubjets = True, 
  addTrimming = True,  rFiltTrim=0.2, ptFrac=0.05,
  addPruning = True, 
  addFiltering = True, 
  addSoftDrop = True, 
  addNsub = True, 
  bTagInfos = listBTagInfos, 
  bTagDiscriminators = listBtagDiscriminatorsAK8, 
  addCMSTopTagger = False, 
  Cut = ak8pupCut , 
  addNsubSubjets = True, 
  subjetMaxTau = 3 )

#----------------------------------------------------------------------------------------
### Analyzer

## LOCAL RUNNING
# JECtxtlocation = '../../../JMEAnalysis/JECDatabase/textFiles/Summer16_23Sep2016V3_MC/'
# JERtxtlocation = '../../../JMEAnalysis/JRDatabase/textFiles/Spring16_25nsV10_MC/'
## CRAB SUBMIT
JECtxtlocation=''
JERtxtlocation=''

process.ana = cms.EDAnalyzer('B2GTTbarTreeMaker',
    
    useToolbox    = cms.bool(True),
    verbose       = cms.bool(False),
    verboseGen    = cms.bool(False),
    runGenLoop    = cms.bool(True),
    
    isZprime      = cms.bool(True),
    isttbar       = cms.bool(False),
    isRSG         = cms.bool(False),
    isRun2016F    = cms.bool(False),

    ak8chsInput          = cms.InputTag("selectedPatJetsAK8PFCHS"),   
    ak8puppiInput        = cms.InputTag("selectedPatJetsAK8PFPuppi"),
    ak8chsSubjetsInput   = cms.InputTag("selectedPatJetsAK8PFCHSSoftDropPacked","SubJets"),
    ak8puppiSubjetsInput = cms.InputTag("selectedPatJetsAK8PFPuppiSoftDropPacked","SubJets"),
    triggerBits          = cms.InputTag("TriggerResults", "", "HLT"),
    lheSrc               = cms.InputTag("externalLHEProducer", "", "LHE"),
    eleIdFullInfoMapToken_HLTpre  = cms.InputTag("egmGsfElectronIDs:cutBasedElectronHLTPreselection-Summer16-V1"),
    eleIdFullInfoMapToken_Loose   = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-loose"),
    eleIdFullInfoMapToken_Medium  = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-medium"),
    eleIdFullInfoMapToken_Tight   = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-tight"),
    eleIdFullInfoMapToken_HEEP    = cms.InputTag("egmGsfElectronIDs:heepElectronID-HEEPV70"), 
    jecPayloadsAK8chs = cms.vstring([
                                    'Summer16_23Sep2016V4_MC_L1FastJet_AK8PFchs.txt',
                                    'Summer16_23Sep2016V4_MC_L2Relative_AK8PFchs.txt',
                                    'Summer16_23Sep2016V4_MC_L3Absolute_AK8PFchs.txt',
                                    'Summer16_23Sep2016V4_MC_L2L3Residual_AK8PFchs.txt',
                                    'Summer16_23Sep2016V4_MC_Uncertainty_AK8PFchs.txt'
                                    ]),
    jecPayloadsAK4chs = cms.vstring([
                                    'Summer16_23Sep2016V4_MC_L1FastJet_AK4PFchs.txt',
                                    'Summer16_23Sep2016V4_MC_L2Relative_AK4PFchs.txt',
                                    'Summer16_23Sep2016V4_MC_L3Absolute_AK4PFchs.txt',
                                    'Summer16_23Sep2016V4_MC_L2L3Residual_AK4PFchs.txt',
                                    'Summer16_23Sep2016V4_MC_Uncertainty_AK4PFchs.txt'
                                    ]),
    jecPayloadsAK8pup = cms.vstring([
                                    'Summer16_23Sep2016V4_MC_L1FastJet_AK8PFPuppi.txt',
                                    'Summer16_23Sep2016V4_MC_L2Relative_AK8PFPuppi.txt',
                                    'Summer16_23Sep2016V4_MC_L3Absolute_AK8PFPuppi.txt',
                                    'Summer16_23Sep2016V4_MC_L2L3Residual_AK8PFPuppi.txt',
                                    'Summer16_23Sep2016V4_MC_Uncertainty_AK8PFPuppi.txt'
                                    ]),
    jecPayloadsAK4pup = cms.vstring([
                                    'Summer16_23Sep2016V4_MC_L1FastJet_AK4PFPuppi.txt',
                                    'Summer16_23Sep2016V4_MC_L2Relative_AK4PFPuppi.txt',
                                    'Summer16_23Sep2016V4_MC_L3Absolute_AK4PFPuppi.txt',
                                    'Summer16_23Sep2016V4_MC_L2L3Residual_AK4PFPuppi.txt',
                                    'Summer16_23Sep2016V4_MC_Uncertainty_AK4PFPuppi.txt'
                                    ]),
    jecPayloadsAK8chsSecondary = cms.vstring([
                                    '',
                                    '',
                                    '',
                                    '',
                                    ''
                                    ]),
    jecPayloadsAK4chsSecondary = cms.vstring([
                                    '',
                                    '',
                                    '',
                                    '',
                                    ''
                                    ]),
    jecPayloadsAK8pupSecondary = cms.vstring([
                                    '',
                                    '',
                                    '',
                                    '',
                                    ''
                                    ]),
    jecPayloadsAK4pupSecondary = cms.vstring([
                                    '',
                                    '',
                                    '',
                                    '',
                                    ''
                                    ]),
    jertextAK4        = cms.string(JERtxtlocation+'Spring16_25nsV10_MC_PtResolution_AK4PFchs.txt'),
    jertextAK8        = cms.string(JERtxtlocation+'Spring16_25nsV10_MC_PtResolution_AK8PFchs.txt'),
    jerSFtext         = cms.string(JERtxtlocation+'Spring16_25nsV10_MC_SF_AK8PFchs.txt')
)


#----------------------------------------------------------------------------------------
### Out

# If you want to output the newly recoconstruted jets
# process.out = cms.OutputModule(
#     "PoolOutputModule",
#     fileName = cms.untracked.string('tool.root'),
#     outputCommands = cms.untracked.vstring(
#       "keep *_selectedPatJetsAK8PFCHS_*_*",
#       "keep *_selectedPatJetsAK8PFCHSSoftDropPacked_*_*",
#       "keep *_selectedPatJetsAK8PFPuppi_*_*",
#       "keep *_selectedPatJetsAK8PFPuppiSoftDropPacked_*_*"
#       )`
#     )
# process.endpath = cms.EndPath(process.out) 


process.TFileService = cms.Service("TFileService",
      fileName = cms.string("b2gtreeV5_MC_Zprime.root"),
      closeFileFast = cms.untracked.bool(True)
  )

process.p = cms.Path(
  process.BadChargedCandidateFilter*
  process.BadPFMuonFilter*
  process.egmGsfElectronIDSequence*
  process.fullPatMetSequence *
  process.ana
)

