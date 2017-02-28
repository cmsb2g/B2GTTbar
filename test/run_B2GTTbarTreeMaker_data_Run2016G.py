# Run2016G data cfg for crab submission of B2GTTbarTreeMaker

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
process.GlobalTag.globaltag = '80X_dataRun2_2016SeptRepro_v7' 
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.options.allowUnscheduled = cms.untracked.bool(True)

isMC   = False

#----------------------------------------------------------------------------------------
### INPUT
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 5000

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/002429F8-A586-E611-ACF3-6C3BE5B5C0C0.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/0085E379-F887-E611-AF46-047D7B881D72.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/00BF76A7-8686-E611-8747-20CF305B04DA.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/00C3F2C5-E885-E611-8A2B-3417EBE64BF7.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/020197DC-6987-E611-8BCB-008CFA197C38.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/023A19A6-D389-E611-A37E-0025907DC9CC.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/02F956D3-CE87-E611-BCE0-008CFA56D764.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/04061D6B-B886-E611-B88B-0090FAA575B0.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/0443C5BF-3287-E611-AD2D-008CFA06477C.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/0474DFA7-448D-E611-B7A3-001E67E6F7D3.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/04A5B76D-3E8D-E611-8E96-001E677925CC.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/04C06977-2C87-E611-9782-001E67792592.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/04D48C09-0388-E611-851D-0CC47A4DEE92.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/04F1451E-368D-E611-BDA2-001E677926FC.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/06414B75-DA85-E611-9D27-E41D2D08DFF0.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/0673346B-9A87-E611-922A-44A842CF05E6.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/067E2666-9F85-E611-95B8-008CFAFBFCA8.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/069594B8-F38B-E611-B1BC-001E67E6F76A.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/06B9B731-AC86-E611-87E3-00259073E4E6.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/06E1FC5B-DC87-E611-B84F-848F69FD2931.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/06E8BFF3-E486-E611-9593-44A842CF057E.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/08003690-E987-E611-B679-7845C4F932B1.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/0A4DC605-188C-E611-A38D-002590A4FFA2.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/0A54CCAC-6387-E611-A17C-0CC47A7FC34E.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/0A5AF4FD-A287-E611-BD3C-0025907B501C.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/0AEA46FD-F787-E611-8AE4-008CFA1983E0.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/0C1548BB-A287-E611-A7B6-0CC47A1E0482.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/0C74F139-A887-E611-8254-44A842CF05D9.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/0CBFE4F7-0A88-E611-9977-002590A3711C.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/0CC863C3-1188-E611-8131-7845C4FC3635.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/0E465D97-328D-E611-BF5A-001E67E6F7CE.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/0E4E30FC-F886-E611-AB42-A0369F7F9DE0.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/0EB1F211-4087-E611-BE91-008CFA1660F8.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/102FF3D5-F68B-E611-ACD5-001E67E6F8B4.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/107FCA41-D385-E611-8EC2-D8D385B0EE2E.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/10942A81-BD87-E611-9ABF-001E67E7195C.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/10A82C33-4F88-E611-A017-001E67E5E8B6.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/10EE5725-068C-E611-A82F-002590A80DEA.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/10F252E9-4C87-E611-A1AF-008CFA05E898.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/125D7D89-DE86-E611-B368-001E67E6F819.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/12B5097E-7986-E611-A762-0CC47A1E0748.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/144736EE-3887-E611-8A02-001E67792494.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/1470AA12-308D-E611-A47B-001E67792888.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/147F7C9C-108D-E611-A4F6-001E67792496.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/14982D58-0E8C-E611-A4A8-001E67E6F52B.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/14D17A90-EA8C-E611-9C9D-001E67E71BFF.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/1638CEDD-7787-E611-A695-44A842CFD5F2.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/16699FDA-D88B-E611-ADA7-001E67E71BAA.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/16DE7F1B-7E87-E611-8344-A0369F7FCBA0.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/1AE1E47E-2C87-E611-B3FB-0CC47A1E0472.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/1C01A3F2-278D-E611-96CA-002590A371AA.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/1C08022C-7087-E611-96B7-7845C4F9CF06.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/1C1A05FA-8D86-E611-AE0C-44A842CFD65A.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/1C6AC0B2-5A87-E611-8254-008CFA06470C.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/1C8E9056-4087-E611-9F79-008CFA05E8F0.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/1CBD427B-7187-E611-905B-008CFA06477C.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/1CCCA25B-1387-E611-97CE-B499BAAC064E.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/1CD4410D-4787-E611-A437-008CFA197A5C.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/1CD497F6-8487-E611-AF41-008CFA1983E0.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/1E905E57-4087-E611-9D92-00266CFFBF80.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/1E947C5D-1387-E611-9000-0CC47A1E047C.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/1EC866E1-8487-E611-8A6F-F452149391B0.root',
      'file:root://cmsxrootd.fnal.gov////store/data/Run2016G/JetHT/MINIAOD/23Sep2016-v1/100000/20002919-A687-E611-B1FD-44A842CF05E6.root'     
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

ak8Cut    = 'pt > 30 && abs(eta) < 2.5'
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
  subjetMaxTau = 3 )

#----------------------------------------------------------------------------------------
### Analyzer

## LOCAL RUNNING
# JECtxtlocation = '../../../JMEAnalysis/JECDatabase/textFiles/Summer16_23Sep2016GV3_DATA/'
# JERtxtlocation = '../../../JMEAnalysis/JRDatabase/textFiles/Spring16_25nsV6_DATA/'
## CRAB SUBMIT
JECtxtlocation=''
JERtxtlocation=''

# Note: JER text files exist for multiple jet collections but at the moment they use the same numbers

process.ana = cms.EDAnalyzer('B2GTTbarTreeMaker',
   
    verbose              = cms.bool(False),
    verboseGen           = cms.bool(False),
    useToolbox           = cms.bool(True),

    runGenLoop           = cms.bool(False),
    runAllHadTree        = cms.bool(True),
    runSemiLeptTree      = cms.bool(True),

    isZprime             = cms.bool(False),
    isttbar              = cms.bool(False),
    isRSG                = cms.bool(False),
    isRun2016F           = cms.bool(False),

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
                                    JECtxtlocation+'Summer16_23Sep2016GV4_DATA_L1FastJet_AK8PFchs.txt',
                                    JECtxtlocation+'Summer16_23Sep2016GV4_DATA_L2Relative_AK8PFchs.txt',
                                    JECtxtlocation+'Summer16_23Sep2016GV4_DATA_L3Absolute_AK8PFchs.txt',
                                    JECtxtlocation+'Summer16_23Sep2016GV4_DATA_L2L3Residual_AK8PFchs.txt',
                                    JECtxtlocation+'Summer16_23Sep2016GV4_DATA_Uncertainty_AK8PFchs.txt'
                                    ]),
    jecPayloadsAK4chs = cms.vstring([
                                    JECtxtlocation+'Summer16_23Sep2016GV4_DATA_L1FastJet_AK4PFchs.txt',
                                    JECtxtlocation+'Summer16_23Sep2016GV4_DATA_L2Relative_AK4PFchs.txt',
                                    JECtxtlocation+'Summer16_23Sep2016GV4_DATA_L3Absolute_AK4PFchs.txt',
                                    JECtxtlocation+'Summer16_23Sep2016GV4_DATA_L2L3Residual_AK4PFchs.txt',
                                    JECtxtlocation+'Summer16_23Sep2016GV4_DATA_Uncertainty_AK4PFchs.txt'
                                    ]),
    jecPayloadsAK8pup = cms.vstring([
                                    JECtxtlocation+'Summer16_23Sep2016GV4_DATA_L1FastJet_AK8PFPuppi.txt',
                                    JECtxtlocation+'Summer16_23Sep2016GV4_DATA_L2Relative_AK8PFPuppi.txt',
                                    JECtxtlocation+'Summer16_23Sep2016GV4_DATA_L3Absolute_AK8PFPuppi.txt',
                                    JECtxtlocation+'Summer16_23Sep2016GV4_DATA_L2L3Residual_AK8PFPuppi.txt',
                                    JECtxtlocation+'Summer16_23Sep2016GV4_DATA_Uncertainty_AK8PFPuppi.txt'
                                    ]),
    jecPayloadsAK4pup = cms.vstring([
                                    JECtxtlocation+'Summer16_23Sep2016GV4_DATA_L1FastJet_AK4PFPuppi.txt',
                                    JECtxtlocation+'Summer16_23Sep2016GV4_DATA_L2Relative_AK4PFPuppi.txt',
                                    JECtxtlocation+'Summer16_23Sep2016GV4_DATA_L3Absolute_AK4PFPuppi.txt',
                                    JECtxtlocation+'Summer16_23Sep2016GV4_DATA_L2L3Residual_AK4PFPuppi.txt',
                                    JECtxtlocation+'Summer16_23Sep2016GV4_DATA_Uncertainty_AK4PFPuppi.txt'
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

    jertextAK4        = cms.string(JERtxtlocation+'Spring16_25nsV10_MC_PtResolution_AK4PFchs.txt'),    # no specific data txt for 25nsV10 but this will be updated soon                        
    jertextAK8        = cms.string(JERtxtlocation+'Spring16_25nsV10_MC_PtResolution_AK8PFchs.txt'),    # no specific data txt for 25nsV10 but this will be updated soon                        
    jerSFtext         = cms.string(JERtxtlocation+'Spring16_25nsV10_MC_SF_AK8PFchs.txt')               # no specific data txt for 25nsV10 but this will be updated soon             
 
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

# process.SimpleMemoryCheck=cms.Service("SimpleMemoryCheck",
#                                    ignoreTotal=cms.untracked.int32(1), #->start logging event N
#                                    oncePerEventMode=cms.untracked.bool(False), # true->report every event, false->report only high memory events 
#                                    moduleMemorySummary=cms.untracked.bool(True),
#                                    monitorPssAndPrivate=cms.untracked.bool(False)

# )

process.TFileService = cms.Service("TFileService",
      fileName = cms.string("b2gtreeV5_dataG.root"),
      closeFileFast = cms.untracked.bool(True)
  )

process.p = cms.Path(
  process.BadChargedCandidateFilter*
  process.BadPFMuonFilter*
  process.egmGsfElectronIDSequence*
  process.fullPatMetSequence *
  process.ana
)

