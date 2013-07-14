import FWCore.ParameterSet.Config as cms

jetFilter = cms.EDFilter('JetFilter',
    JetsInputTag = cms.InputTag('ak5PFJets'),
    JetPtMin     = cms.double(300.),
    JetAbsEtaMax = cms.double(3.),
    JetsMin      = cms.int32(1),
    JetsMax      = cms.int32(-1),
    Enabled      = cms.bool(True)
)
