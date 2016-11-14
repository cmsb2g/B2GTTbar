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
process.GlobalTag.globaltag = '80X_dataRun2_2016SeptRepro_v4' #80X_dataRun2_ICHEP16_repro_v0'
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.options.allowUnscheduled = cms.untracked.bool(True)

isMC   = False

#----------------------------------------------------------------------------------------
### INPUT
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
      # 'file:root://cmsxrootd.fnal.gov///store/data/Run2016C/JetHT/MINIAOD/PromptReco-v2/000/275/603/00000/169B0A2E-8A3A-E611-A601-02163E011CD2.root', 
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/830/00000/A87F5827-AB4C-E611-8D49-FA163EE5C431.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/06AD57AB-5A4D-E611-80F2-02163E014448.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/081076B9-5A4D-E611-896E-FA163E30C29A.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/086A225E-194D-E611-A9AA-02163E014385.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/0AF951B1-5A4D-E611-BD3D-02163E0119AD.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/106167A5-244D-E611-A6ED-FA163EBD01E0.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/121C0636-294D-E611-A72D-02163E013686.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/12F601B6-5A4D-E611-A4F0-FA163E9754B4.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/1497E9B2-5A4D-E611-AB52-02163E013411.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/1632CD02-214D-E611-A694-02163E011864.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/16C695F0-084D-E611-822F-FA163E41764C.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/1865E8FF-234D-E611-8AA1-02163E0142C6.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/200A43B2-5A4D-E611-895F-02163E0146B3.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/20395494-104D-E611-BD5F-02163E01351B.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/2087F7A3-5A4D-E611-A692-FA163EF38E54.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/24C721FA-274D-E611-BCC9-FA163EC135D1.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/28131575-1E4D-E611-BECD-02163E011F9D.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/28E3BA7D-224D-E611-A12A-02163E01225C.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/2A240D8F-2B4D-E611-824D-02163E0134DE.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/2A937EA9-1C4D-E611-94E0-02163E0136FC.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/3040D49E-5A4D-E611-976F-02163E0138A6.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/30A1FC46-244D-E611-B39F-FA163E3457C7.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/328994A7-5A4D-E611-9DEF-FA163E684C10.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/32A5E41F-264D-E611-A18A-02163E01355F.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/3620CCB1-144D-E611-9197-FA163E3657CF.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/36E5A7AC-5A4D-E611-AED4-02163E011CB8.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/380E03B3-5A4D-E611-A325-02163E013505.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/38C96810-1E4D-E611-B2A3-FA163E3B387E.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/3E12C697-304D-E611-86C4-FA163E4B4C4F.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/3E8322A5-0A4D-E611-9556-02163E011D28.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/4A3CDC62-324D-E611-BAD3-02163E0144D1.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/4A6665D8-274D-E611-AE5B-02163E013599.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/4CA5121F-254D-E611-8BFA-02163E011F93.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/4E09320D-2A4D-E611-890A-02163E011F98.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/50938E16-064D-E611-B022-02163E013690.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/521D3461-204D-E611-9E4B-FA163E5777DE.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/5294517C-254D-E611-B69F-02163E014589.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/5456F1AB-5A4D-E611-985B-FA163EF58A09.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/5498E65C-274D-E611-A9ED-02163E011C74.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/56FD74B6-5A4D-E611-AE94-02163E0138FE.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/5CA826B3-5A4D-E611-98AD-02163E013830.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/62417FB7-224D-E611-A933-FA163E149A22.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/62E52DAF-5A4D-E611-8CC3-FA163E3B8FC0.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/6613B2A6-0C4D-E611-8CB7-02163E0129F1.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/6A9CE5B0-5A4D-E611-BBA6-02163E0145F4.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/6ABD1423-2F4D-E611-9B27-02163E01254C.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/6C790276-264D-E611-B42F-FA163E8B9596.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/6E3E1DB0-5A4D-E611-B8DC-FA163E2CD816.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/70BB06AC-5A4D-E611-93EF-FA163E57F7E2.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/7CFEF1DF-284D-E611-895E-02163E014208.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/801A1F8F-0E4D-E611-B33E-02163E011E11.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/8081559A-1F4D-E611-928C-02163E0128C4.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/869BD1A4-5A4D-E611-B2D4-FA163ED9E47B.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/884038FE-164D-E611-B5A2-02163E0145DB.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/88C8B167-1F4D-E611-BC44-FA163E58D795.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/8AC3A4D1-384D-E611-9A65-FA163E6B736E.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/8CABD3C2-154D-E611-A4E8-FA163E24B080.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/90554245-1C4D-E611-90A0-FA163EC5EF3E.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/92EF79E5-2A4D-E611-A7F1-02163E0143C4.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/94FC3BFC-1F4D-E611-B345-02163E012950.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/984754AA-5A4D-E611-BC6C-FA163E2607D7.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/9A0DB2A6-1F4D-E611-9A04-02163E0123B2.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/9AF7B8AF-1B4D-E611-A220-FA163E8359E6.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/9E547051-164D-E611-B3DA-02163E014617.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/A017F1EB-264D-E611-BF7E-02163E0143AA.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/AC0B75B1-5A4D-E611-80B9-02163E014226.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/B005CB2E-1B4D-E611-9125-FA163E2CD816.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/B03AF241-1A4D-E611-8432-02163E012312.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/B64457B0-134D-E611-9DAF-FA163E9E0104.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/BC6F4460-184D-E611-8026-02163E011C87.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/BCFFF0E3-344D-E611-BD6D-02163E014116.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/BE871CBC-1A4D-E611-B6C6-FA163E42E2B1.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/C0693E3C-124D-E611-B818-02163E0145A1.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/CA14B309-2F4D-E611-A22F-FA163ED1B7C7.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/CA9D63EA-4B4D-E611-92F2-02163E011A3C.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/D03E53A6-214D-E611-9B88-02163E0133B2.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/D0ED40B7-5A4D-E611-AEB7-02163E0142FF.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/D23762E8-254D-E611-A6F9-02163E012BAF.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/D81D89C3-234D-E611-87CE-02163E011C74.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/D8F259E8-1C4D-E611-B8FF-FA163EDD79DE.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/DC6A61A4-5A4D-E611-96DC-FA163ED1B7C7.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/E2DAA4F0-224D-E611-BF02-FA163ECF69B2.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/E2DC4168-2F4D-E611-B6A7-02163E01230C.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/E81C5C3C-2D4D-E611-9CFB-02163E0143E5.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/E8291EAE-5A4D-E611-854C-FA163EAB4C77.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/E85C9F50-1D4D-E611-A10C-02163E0119D1.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/ECE8CA44-2C4D-E611-AF91-FA163E5ED4C5.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/F6B60E6F-224D-E611-B50B-02163E01438F.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/FA0062A9-5A4D-E611-9F89-FA163EF838A9.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/832/00000/36604841-7D4D-E611-8716-02163E014498.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/832/00000/8C534D2F-7D4D-E611-B138-02163E01353D.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/834/00000/167A81E8-934D-E611-BF68-02163E011C12.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/834/00000/1C5EC8DF-934D-E611-9E31-FA163E88FBA3.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/834/00000/32E1DFE3-934D-E611-93AD-FA163E8EA755.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/834/00000/48F3F9F1-934D-E611-9A15-02163E01218E.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/834/00000/5ABBA4EA-934D-E611-80DB-FA163EAB4C77.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/834/00000/5AC881DD-934D-E611-BB43-FA163E9E84E3.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/834/00000/686CF6E8-934D-E611-A171-02163E013922.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/834/00000/6AA382EC-934D-E611-A0AB-02163E01374D.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/834/00000/6E92A8E2-934D-E611-8C20-FA163E703D75.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/834/00000/7AF982D6-934D-E611-94F1-02163E013704.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/834/00000/80275BE8-934D-E611-80A1-02163E0142E7.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/834/00000/821DEDEA-934D-E611-A014-02163E012924.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/834/00000/86900FDE-934D-E611-A590-02163E0141E3.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/834/00000/B2C33DE2-934D-E611-9740-FA163ED1B7C7.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/834/00000/B6C776EC-934D-E611-AA2A-02163E011D79.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/834/00000/B8B878E3-934D-E611-A755-FA163EBC8500.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/834/00000/E44F3CE9-934D-E611-9158-02163E011C55.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/834/00000/F48F91E4-934D-E611-926A-02163E014761.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/836/00000/B8E064B9-724D-E611-A3C7-02163E013485.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/837/00000/FC1BEAF7-754D-E611-BD81-FA163EF2EAD6.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/008B298D-414E-E611-B6ED-02163E01469E.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/00B75EAB-304E-E611-98FF-02163E014640.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/00C09985-174E-E611-B334-FA163E0D80C5.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/022A3F57-0C4E-E611-BF52-02163E0145B8.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/063342AB-164E-E611-9799-02163E0145F4.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/083220EA-0C4E-E611-A971-FA163E86921D.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/0ED46A78-2C4E-E611-A76C-FA163EED0836.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/14E70B92-084E-E611-810F-02163E0145C1.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/16EB5640-134E-E611-936E-02163E012AE1.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/180411D3-5F4E-E611-8757-02163E013498.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/18ADAB1F-0C4E-E611-BEF0-02163E013417.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/1E1D88A6-194E-E611-823E-02163E014569.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/1E535E94-1F4E-E611-9B1A-FA163E453A64.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/28F0847E-304E-E611-9455-02163E011B22.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/2CBE73E8-5F4E-E611-849D-02163E011A20.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/2E2EACBC-0E4E-E611-A9E8-02163E0146E5.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/301B8BEF-FE4D-E611-AB41-FA163E3F857B.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/32051879-334E-E611-93E3-FA163E8960C2.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/3443FF9E-224E-E611-B0DD-02163E01426A.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/34859CDC-5F4E-E611-A300-02163E0126D2.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/3A8A6DA3-1C4E-E611-B946-02163E014260.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/3A905AB1-254E-E611-A4E1-FA163EBBF319.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/3C9458B0-0E4E-E611-832A-FA163EA7D13A.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/3C96877B-034E-E611-BF20-02163E0141C8.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/3E67B322-084E-E611-A8B3-02163E01374D.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/422A299E-274E-E611-B9DD-FA163EB150D3.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/46300A45-314E-E611-BF1D-02163E014431.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/4800C822-144E-E611-987C-02163E013655.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/48C44D87-1A4E-E611-92FC-02163E011DD9.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/4C82F2A8-324E-E611-B94E-02163E0138F6.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/4E3CD6F7-1B4E-E611-8F93-02163E01414C.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/4ECD2DE0-184E-E611-B902-02163E014100.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/503D7369-FB4D-E611-B15C-02163E0141F2.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/5A6446CE-1E4E-E611-9051-02163E01424A.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/5C827ABA-FC4D-E611-8CFD-FA163E9E0104.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/5CE932E7-5F4E-E611-AB67-02163E012155.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/5E02F593-304E-E611-87F8-02163E0145BE.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/5E9D5384-2D4E-E611-8DA3-FA163EB7134C.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/5ED74FC0-014E-E611-A77A-02163E0141F2.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/6271F722-224E-E611-81A6-02163E014700.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/6275BCFD-054E-E611-B421-02163E011B57.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/64904B24-604E-E611-A361-02163E014512.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/68477920-F94D-E611-A9D5-02163E0141C8.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/6860F08B-114E-E611-BC72-FA163E86921D.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/6CFD23D7-5F4E-E611-B344-FA163E110010.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/6E3C2B42-204E-E611-9DBC-FA163EB4573D.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/70323BEF-1A4E-E611-9E45-FA163E453A64.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/72BB713D-104E-E611-AFF2-02163E012075.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/78565BD1-5F4E-E611-AF1B-02163E014414.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/78C4F6B0-1C4E-E611-A6AF-02163E0134F4.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/7AB3B13D-254E-E611-B5D7-FA163E0BB18C.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/7AF78F1A-124E-E611-B0A5-02163E0141EC.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/7CBAAAD3-5F4E-E611-87CB-02163E014605.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/7E4141D2-5F4E-E611-9556-02163E0133E0.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/7E6C7931-2A4E-E611-BD64-FA163EC5AD21.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/82CCCCDF-5F4E-E611-9F54-FA163E90E122.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/84814363-4A4E-E611-980F-02163E013547.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/84C3B107-1E4E-E611-83D3-02163E0141E1.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/86A46178-0B4E-E611-864D-FA163E63403C.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/86FF6399-144E-E611-93DC-FA163E3EFC13.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/8C52FA21-244E-E611-BD13-FA163ED57BE5.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/8CBFA79B-124E-E611-8CB4-02163E0146F7.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/8E6CEADE-5F4E-E611-AEFF-02163E011FA3.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/92EC3A89-094E-E611-9A70-FA163E10F0CE.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/942719D6-5F4E-E611-9E1A-FA163EC11C0E.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/943BE407-044E-E611-B97F-FA163EA8BC26.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/96DEFA86-0F4E-E611-944F-02163E011948.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/9C8D7FF6-104E-E611-BC3A-02163E012AD4.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/A20ED01B-0A4E-E611-8F40-FA163ED015F1.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/A275DBDA-5F4E-E611-B8A0-FA163EF38E54.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/A43F5D30-174E-E611-8FD4-02163E0136B3.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/A6352DAB-154E-E611-98DA-02163E014160.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/A6D2F70A-FE4D-E611-8270-02163E01372B.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/ACAC5DC5-FD4D-E611-AB2C-02163E013903.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/AEA00DFB-174E-E611-93FF-FA163E984F03.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/B04A24BB-264E-E611-B8AE-02163E0134F4.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/B6F0A239-234E-E611-B6C4-02163E0144B4.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/B83F5061-1B4E-E611-915F-02163E0143B1.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/C20E07D5-0D4E-E611-9742-FA163E2B487A.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/C451E4DD-1E4E-E611-A0E1-02163E011F3D.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/C495BD0B-014E-E611-B75A-02163E013892.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/C6205D8C-214E-E611-8A63-02163E01223E.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/C8685B49-264E-E611-9EF0-FA163EE3A14D.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/C8A313D6-5F4E-E611-92B0-02163E013708.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/CA40B1D6-044E-E611-B99D-FA163EB5275E.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/D0E7BBF2-3A4E-E611-AFD1-02163E01180A.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/D42D5421-344E-E611-8278-02163E012075.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/D4D7AA2C-144E-E611-9B35-FA163E1E9695.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/D6833ED0-064E-E611-A296-02163E01355F.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/D6A5F0FE-174E-E611-81E9-02163E0135B9.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/D8D059CB-5F4E-E611-87B6-02163E011FEC.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/DC952E5D-0D4E-E611-9B9C-02163E01186D.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/DCA807EF-204E-E611-9B94-02163E014499.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/E0F7585E-124E-E611-B8A6-02163E0141E3.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/E255CFDA-0A4E-E611-BA03-02163E0144C1.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/E4752641-2B4E-E611-AAE0-FA163EBF5AC8.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/E497900F-354E-E611-8AC7-FA163E663BAA.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/870/00000/E49DC930-024E-E611-B512-FA163EDD08C4.root',
      'file:root://cmsxrootd.fnal.gov///store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/935/00000/7824CBAB-604E-E611-8B5F-02163E0146E8.root'   
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
    'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV60_cff'
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
# process.load('CommonTools/PileupAlgos/Puppi_cff')
# process.puppi.candName = cms.InputTag('packedPFCandidates')
# process.puppi.vertexName = cms.InputTag('offlineSlimmedPrimaryVertices')
# process.puppi.useExistingWeights = cms.bool(True)
#process.puppiOnTheFly = process.puppi.clone()
#process.puppiOnTheFly.useExistingWeights = True

#----------------------------------------------------------------------------------------
### Toolbox (https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetToolbox)
from JMEAnalysis.JetToolbox.jetToolbox_cff import jetToolbox

ak8Cut = 'pt > 200 && abs(eta) < 2.5'
ak8pupCut = 'pt > 150 && abs(eta) < 2.5'


listBTagInfos = [
     'pfInclusiveSecondaryVertexFinderTagInfos',
]
listBtagDiscriminatorsAK8 = [ 
    'pfJetProbabilityBJetTags',
    'pfCombinedInclusiveSecondaryVertexV2BJetTags',
    'pfCombinedMVAV2BJetTags',
    # 'pfCombinedCvsLJetTags',
    # 'pfCombinedCvsBJetTags',
    'pfBoostedDoubleSecondaryVertexAK8BJetTags',
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
  subjetMaxTau = 4 )


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
  subjetMaxTau = 4 )

#----------------------------------------------------------------------------------------
### Analyzer

process.ana = cms.EDAnalyzer('B2GTTbarTreeMaker',
    useToolbox    = cms.bool(True),
    verbose       = cms.bool(False),
    verboseGen    = cms.bool(False),
    runGenLoop    = cms.bool(False),
    isZprime      = cms.bool(False),
    isttbar       = cms.bool(False),
    isRSG         = cms.bool(False),
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
    eleIdFullInfoMapToken_HEEP    = cms.InputTag("egmGsfElectronIDs:heepElectronID-HEEPV60"), 
    jecPayloadsAK8chs = cms.vstring([
                                    'Spring16_25nsV6_DATA_L1FastJet_AK8PFchs.txt',
                                    'Spring16_25nsV6_DATA_L2Relative_AK8PFchs.txt',
                                    'Spring16_25nsV6_DATA_L3Absolute_AK8PFchs.txt',
                                    'Spring16_25nsV6_DATA_L2L3Residual_AK8PFchs.txt',
                                    'Spring16_25nsV6_DATA_Uncertainty_AK8PFchs.txt'
                                    ]),
    jecPayloadsAK4chs = cms.vstring([
                                    'Spring16_25nsV6_DATA_L1FastJet_AK4PFchs.txt',
                                    'Spring16_25nsV6_DATA_L2Relative_AK4PFchs.txt',
                                    'Spring16_25nsV6_DATA_L3Absolute_AK4PFchs.txt',
                                    'Spring16_25nsV6_DATA_L2L3Residual_AK4PFchs.txt',
                                    'Spring16_25nsV6_DATA_Uncertainty_AK4PFchs.txt'
                                    ]),
    jecPayloadsAK8pup = cms.vstring([
                                    'Spring16_25nsV6_DATA_L1FastJet_AK8PFPuppi.txt',
                                    'Spring16_25nsV6_DATA_L2Relative_AK8PFPuppi.txt',
                                    'Spring16_25nsV6_DATA_L3Absolute_AK8PFPuppi.txt',
                                    'Spring16_25nsV6_DATA_L2L3Residual_AK8PFPuppi.txt',
                                    'Spring16_25nsV6_DATA_Uncertainty_AK8PFPuppi.txt'
                                    ]),
    jecPayloadsAK4pup = cms.vstring([
                                    'Spring16_25nsV6_DATA_L1FastJet_AK4PFPuppi.txt',
                                    'Spring16_25nsV6_DATA_L2Relative_AK4PFPuppi.txt',
                                    'Spring16_25nsV6_DATA_L3Absolute_AK4PFPuppi.txt',
                                    'Spring16_25nsV6_DATA_L2L3Residual_AK4PFPuppi.txt',
                                    'Spring16_25nsV6_DATA_Uncertainty_AK4PFPuppi.txt'
                                    ]),
    jerSFtext         = cms.string('Spring16_25nsV6_MC_SF_AK8PFchs.txt'
                                    )
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
      fileName = cms.string("treeData.root"),
      closeFileFast = cms.untracked.bool(True)
  )

process.p = cms.Path(
  process.BadChargedCandidateFilter*
  process.BadPFMuonFilter*
  process.egmGsfElectronIDSequence*
  process.fullPatMetSequence *
  process.ana
)

