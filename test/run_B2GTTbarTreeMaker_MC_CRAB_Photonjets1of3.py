
# cfg for local testing of B2GTTbarTreeMaker

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
process.GlobalTag.globaltag = '80X_mcRun2_asymptotic_2016_TrancheIV_v6'
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(False), SkipEvent = cms.untracked.vstring('ProductNotFound') )
process.options.allowUnscheduled = cms.untracked.bool(True)
#process.options = SkipEvent = cms.untracked.vstring('ProductNotFound')
isMC   = True


#----------------------------------------------------------------------------------------
### INPUT
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(2000) )
process.MessageLogger.cerr.FwkReport.reportEvery = 200

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
'file:root://cmsxrootd.fnal.gov///store/mc/RunIISummer16MiniAODv2/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/120000/0245ACCA-BBC5-E611-940C-001E674FB24D.root'
#'file:root://cmsxrootd.fnal.gov///store/mc/RunIISummer16MiniAODv2/ZJetsToMuMu_Mll40To150_PtHat15_DPS/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/110000/00F2C0F0-8C5E-E711-A935-7845C4F8AF24.root',
#'file:root://cmsxrootd.fnal.gov///store/mc/RunIISpring16MiniAODv2/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/34A3AE49-0E1C-E611-8F29-38EAA7A0EEF8.root'
#      'file:root://cmsxrootd.fnal.gov////store/mc/RunIISummer16MiniAODv2/ZprimeToTT_M-2000_W-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/80000/32C9A239-47BC-E611-9C93-0CC47AD98CF8.root',
#      'file:root://cmsxrootd.fnal.gov////store/mc/RunIISummer16MiniAODv2/ZprimeToTT_M-2000_W-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/80000/58DDD5CE-3FBC-E611-BEBC-782BCB161F1B.root',
#      'file:root://cmsxrootd.fnal.gov////store/mc/RunIISummer16MiniAODv2/ZprimeToTT_M-2000_W-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/80000/AA863283-47BC-E611-A2C5-0CC47A009E22.root',
#      'file:root://cmsxrootd.fnal.gov////store/mc/RunIISummer16MiniAODv2/ZprimeToTT_M-2000_W-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/80000/AC9610E2-43BC-E611-98AD-842B2B7680D5.root'
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
### Puppi (https://twiki.cern.ch/twiki/bin/viewauth/CMS/PUPPI)

process.load('CommonTools/PileupAlgos/Puppi_cff')
process.puppi.candName = cms.InputTag('packedPFCandidates')
process.puppi.vertexName = cms.InputTag('offlineSlimmedPrimaryVertices')
process.puppi.useExistingWeights = cms.bool(True)
process.puppiOnTheFly = process.puppi.clone()
process.puppiOnTheFly.useExistingWeights = True

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
### Toolbox (https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetToolbox)
from JMEAnalysis.JetToolbox.jetToolbox_cff import jetToolbox

ak8Cut    = 'pt > 200 && abs(eta) < 2.5'
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
  JETCorrLevels = [ 'None' ],
  subJETCorrLevels = [ 'None' ],
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
  JETCorrLevels = [ 'None' ],
  subJETCorrLevels = [ 'None' ],
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
  subjetMaxTau = 3, 
  addEnergyCorrFunc=True, ecfBeta = 1.0, maxECF=3 )


### AK8GenJetsSoftDrop ###
from RecoJets.Configuration.RecoGenJets_cff import ak4GenJets
from RecoJets.JetProducers.SubJetParameters_cfi import SubJetParameters

process.ak8GenJetsSoftDrop = ak4GenJets.clone(
                               SubJetParameters,
                               src = cms.InputTag("packedGenParticlesForJetsNoNu"),
                               useSoftDrop = cms.bool(True),
                               rParam = cms.double(0.8),
                               useExplicitGhosts=cms.bool(True),
                               R0= cms.double(0.8),
                               beta=cms.double(0.0),
                               writeCompound = cms.bool(True),
                               jetCollInstanceName=cms.string("SubJets")
                             )

#----------------------------------------------------------------------------------------
### Analyzer

## LOCAL RUNNING
#JECtxtlocation = '../../../JMEAnalysis/JECDatabase/textFiles/Summer16_23Sep2016V4_MC/'
#JERtxtlocation = '../../../JMEAnalysis/JRDatabase/textFiles/Spring16_25nsV10_MC/'
## CRAB SUBMIT
JECtxtlocation=''
JERtxtlocation=''

process.ana = cms.EDAnalyzer('B2GTTbarTreeMaker',

    verbose         = cms.bool(False),
    verboseGen      = cms.bool(False),
    useToolbox      = cms.bool(True),

    runGenLoop      = cms.bool(True),
    runAllHadTree   = cms.bool(False),
    runSemiLeptTree = cms.bool(True),
    
    isZprime        = cms.bool(False),
    isttbar         = cms.bool(False),
    isRSG           = cms.bool(False),
    isRun2016F      = cms.bool(False),
    isPhoton        = cms.bool(True),
    isW             = cms.bool(False),
    isZ             = cms.bool(False),
    isDown          = cms.bool(False),



    ak8GenJetsSoftDropInput = cms.InputTag("ak8GenJetsSoftDrop", "SubJets"),
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
                                    JECtxtlocation+'Summer16_23Sep2016V4_MC_L1FastJet_AK8PFchs.txt',
                                    JECtxtlocation+'Summer16_23Sep2016V4_MC_L2Relative_AK8PFchs.txt',
                                    JECtxtlocation+'Summer16_23Sep2016V4_MC_L3Absolute_AK8PFchs.txt',
                                    JECtxtlocation+'Summer16_23Sep2016V4_MC_L2L3Residual_AK8PFchs.txt',
                                    JECtxtlocation+'Summer16_23Sep2016V4_MC_Uncertainty_AK8PFchs.txt'
                                    ]),
    jecPayloadsAK4chs = cms.vstring([
                                    JECtxtlocation+'Summer16_23Sep2016V4_MC_L1FastJet_AK4PFchs.txt',
                                    JECtxtlocation+'Summer16_23Sep2016V4_MC_L2Relative_AK4PFchs.txt',
                                    JECtxtlocation+'Summer16_23Sep2016V4_MC_L3Absolute_AK4PFchs.txt',
                                    JECtxtlocation+'Summer16_23Sep2016V4_MC_L2L3Residual_AK4PFchs.txt',
                                    JECtxtlocation+'Summer16_23Sep2016V4_MC_Uncertainty_AK4PFchs.txt'
                                    ]),
    jecPayloadsAK8pup = cms.vstring([
                                    JECtxtlocation+'Summer16_23Sep2016V4_MC_L1FastJet_AK8PFPuppi.txt',
                                    JECtxtlocation+'Summer16_23Sep2016V4_MC_L2Relative_AK8PFPuppi.txt',
                                    JECtxtlocation+'Summer16_23Sep2016V4_MC_L3Absolute_AK8PFPuppi.txt',
                                    JECtxtlocation+'Summer16_23Sep2016V4_MC_L2L3Residual_AK8PFPuppi.txt',
                                    JECtxtlocation+'Summer16_23Sep2016V4_MC_Uncertainty_AK8PFPuppi.txt'
                                    ]),
    jecPayloadsAK4pup = cms.vstring([
                                    JECtxtlocation+'Summer16_23Sep2016V4_MC_L1FastJet_AK4PFPuppi.txt',
                                    JECtxtlocation+'Summer16_23Sep2016V4_MC_L2Relative_AK4PFPuppi.txt',
                                    JECtxtlocation+'Summer16_23Sep2016V4_MC_L3Absolute_AK4PFPuppi.txt',
                                    JECtxtlocation+'Summer16_23Sep2016V4_MC_L2L3Residual_AK4PFPuppi.txt',
                                    JECtxtlocation+'Summer16_23Sep2016V4_MC_Uncertainty_AK4PFPuppi.txt'
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
#       )
#     )
# process.endpath = cms.EndPath(process.out) 


process.TFileService = cms.Service("TFileService",
      fileName = cms.string("b2gtreeV5_MC_WjetstolNu.root"),
      closeFileFast = cms.untracked.bool(True)
  )


#Adding SimpleMemoryCheck service:
#process.SimpleMemoryCheck=cms.Service("SimpleMemoryCheck",
#                                   ignoreTotal=cms.untracked.int32(0),
#                                   oncePerEventMode=cms.untracked.bool(True)
#)

#process.Timing = cms.Service("Timing"
##    ,summaryOnly = cms.untracked.bool(True)
#)

#process.ProfilerService = cms.Service("ProfilerService",
#    lastEvent = cms.untracked.int32(10),
#    firstEvent = cms.untracked.int32(1),
#    paths = cms.untracked.vstring('p')
#)
 

process.p = cms.Path(
  process.BadChargedCandidateFilter*
  process.BadPFMuonFilter*
  process.egmGsfElectronIDSequence*
  process.fullPatMetSequence *
  process.ak8GenJetsSoftDrop *
  process.ana
)

