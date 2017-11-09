// Emulator that takes RPC hits and produces CPPFDigis to send to EMTF
// Author Alejandro Segura -- Universidad de los Andes

#ifndef L1Trigger_L1TMuonCPPF_L1TMuonCPPFDigiProducer_h
#define L1Trigger_L1TMuonCPPF_L1TMuonCPPFDigiProducer_h

#include "L1Trigger/L1TMuonCPPF/interface/EmulateCPPF.h"

// System include files
#include <memory>

// User include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// Other includes (all needed? - AWB 27.07.17)
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/RPCDigi/interface/RPCDigiCollection.h"
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"

#include "CondFormats/RPCObjects/interface/RPCDeadStrips.h"
#include <assert.h>

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/MuonDetId/interface/RPCDetId.h"
#include "DataFormats/L1TMuon/interface/CPPFDigi.h"

#include "Geometry/RPCGeometry/interface/RPCRoll.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"

#include "L1Trigger/L1TMuonEndCap/interface/PrimitiveConversion.h"
#include "L1Trigger/L1TMuonEndCap/interface/SectorProcessorLUT.h"
#include "L1Trigger/L1TMuonEndCap/interface/TrackTools.h"

#include <Geometry/Records/interface/MuonGeometryRecord.h>

#include <string>
#include <fstream>
#include "TVector3.h"

// Class declaration
class L1TMuonCPPFDigiProducer : public edm::EDProducer {
  
 public:
  explicit L1TMuonCPPFDigiProducer(const edm::ParameterSet&);
  virtual ~L1TMuonCPPFDigiProducer();

 private:
  virtual void beginJob() override;
  virtual void produce(edm::Event& event, const edm::EventSetup& setup) override;
  virtual void endJob() override;
  
 private:
  std::unique_ptr<EmulateCPPF> cppf_emulator_;
       
};

#endif /* #define L1Trigger_L1TMuonCPPF_L1TMuonCPPFDigiProducer_h */