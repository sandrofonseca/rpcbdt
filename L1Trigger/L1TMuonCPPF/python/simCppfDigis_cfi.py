import FWCore.ParameterSet.Config as cms

simCppfDigis = cms.EDProducer("L1TMuonCPPFDigiProducer",
    
    ## Input collection
    recHitLabel = cms.InputTag("rpcRecHits"),
    #cppfSource = cms.string('Geo'), #'File' for Look up table and 'Geo' for CMSSW Geometry 
    cppfSource = cms.string('File'), #'File' for Look up table and 'Geo' for CMSSW Geometry 

    cppfvecfile = cms.FileInPath('L1Trigger/L1TMuonCPPF/data/total.txt')                            
#    cppfvecfile = cms.FileInPath('L1Trigger/L1TMuonCPPF/data/angleScale_RPC_CPPFn1.txt')                            
#    cppfvecfile = cms.FileInPath('L1Trigger/L1TMuonCPPF/data/angleScale_RPC_CPPFn2.txt')                            
#    cppfvecfile = cms.FileInPath('L1Trigger/L1TMuonCPPF/data/angleScale_RPC_CPPFn3.txt')                            
#    cppfvecfile = cms.FileInPath('L1Trigger/L1TMuonCPPF/data/angleScale_RPC_CPPFn4.txt')                            
#    cppfvecfile = cms.FileInPath('L1Trigger/L1TMuonCPPF/data/angleScale_RPC_CPPFp1.txt')                            
#    cppfvecfile = cms.FileInPath('L1Trigger/L1TMuonCPPF/data/angleScale_RPC_CPPFp2.txt')                            
#    cppfvecfile = cms.FileInPath('L1Trigger/L1TMuonCPPF/data/angleScale_RPC_CPPFp3.txt')                            
#    cppfvecfile = cms.FileInPath('L1Trigger/L1TMuonCPPF/data/angleScale_RPC_CPPFp4.txt')                            
    )

