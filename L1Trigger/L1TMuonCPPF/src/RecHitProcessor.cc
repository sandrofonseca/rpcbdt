#include "L1Trigger/L1TMuonCPPF/interface/RecHitProcessor.h"

RecHitProcessor::RecHitProcessor() {
}

RecHitProcessor::~RecHitProcessor() {
}

void RecHitProcessor::processLook(
				  const edm::Event& iEvent,
				  const edm::EventSetup& iSetup,
				  const edm::EDGetToken& recHitToken,
				  std::vector<RecHitProcessor::CppfItem>& CppfVec1,
				  l1t::CPPFDigiCollection& cppfDigis
				  ) const {
  
  edm::Handle<RPCRecHitCollection> recHits;
  iEvent.getByToken(recHitToken, recHits);
  
  edm::ESHandle<RPCGeometry> rpcGeom;
  iSetup.get<MuonGeometryRecord>().get(rpcGeom);
 
  // Loop over ... what, exactly?
  for ( TrackingGeometry::DetContainer::const_iterator iDet = rpcGeom->dets().begin(); iDet < rpcGeom->dets().end(); iDet++ ) {
    
    // What does this do?  Check whether the chamber is an RPC chamber?
    if (dynamic_cast<const RPCChamber*>( *iDet ) == 0 ) continue;
    
    auto chamb = dynamic_cast<const RPCChamber* >( *iDet ); 
    std::vector<const RPCRoll*> rolls = (chamb->rolls());
    
    // Loop over rolls in the chamber
    for (std::vector<const RPCRoll*>::const_iterator iRoll = rolls.begin(); iRoll != rolls.end(); ++iRoll) {
      
      RPCDetId rpcId = (*iRoll)->id();	
      
      typedef std::pair<RPCRecHitCollection::const_iterator, RPCRecHitCollection::const_iterator> rangeRecHits;
      rangeRecHits recHitCollection =  recHits->get(rpcId);
      
      
      
      //Loop over the RPC digis
      for (RPCRecHitCollection::const_iterator rechit_it = recHitCollection.first; rechit_it != recHitCollection.second; rechit_it++) {	
	
	//const RPCDetId& rpcId = rechit_it->rpcId();
	int rawId = rpcId.rawId();
	int station = rpcId.station();
	int Bx = rechit_it->BunchX(); 
	int isValid = rechit_it->isValid();
	int firststrip = rechit_it->firstClusterStrip();
	int clustersize = rechit_it->clusterSize();
	LocalPoint lPos = rechit_it->localPosition();
	const RPCRoll* roll = rpcGeom->roll(rpcId);
	const BoundPlane& rollSurface = roll->surface();
	GlobalPoint gPos = rollSurface.toGlobal(lPos);
	float global_theta = emtf::rad_to_deg(gPos.theta().value());
	float global_phi   = emtf::rad_to_deg(gPos.phi().value());
	//::::::::::::::::::::::::::::
	//Establish the average position of the rechit    
	int rechitstrip = firststrip;
	if(clustersize > 1) {
	  int medium = 0;
	  if (clustersize % 2 == 0) medium = 0.5*(clustersize); 
	  else medium = 0.5*(clustersize-1);
	  rechitstrip += medium; 
	}
	//This is just for test CPPFDigis with the RPC Geometry, It must be "False" in the normal runs 
	bool Geo = true;
	////:::::::::::::::::::::::::::::::::::::::::::::::::
    //Set the EMTF Sector 	
	int EMTFsector1 = 0;	
	int EMTFsector2 = 0;
	
	//sector 1
	if ((global_phi > 15.) && (global_phi <= 16.3)) {
	  EMTFsector1 = 1;
	  EMTFsector2 = 6;
	}
	if ((global_phi > 16.3) && (global_phi <= 53.)) {
	  EMTFsector1 = 1;
	  EMTFsector2 = 0;
	}
	if ((global_phi > 53.) && (global_phi <= 75.)) {
	  EMTFsector1 = 1;
	  EMTFsector2 = 2;
	}
	//sector 2 
	if ((global_phi > 75.) && (global_phi <= 76.3)) {
	  EMTFsector1 = 1;
	  EMTFsector2 = 2;
	}
	if ((global_phi > 76.3) && (global_phi <= 113.)) {
	  EMTFsector1 = 2;
	  EMTFsector2 = 0;
	}
	if ((global_phi > 113.) && (global_phi <= 135.)) {
	  EMTFsector1 = 2;
	  EMTFsector2 = 3;
	}
	//sector 3
	//less than 180
	if ((global_phi > 135.) && (global_phi <= 136.3)) {
	  EMTFsector1 = 2;
	  EMTFsector2 = 3;
	}
	if ((global_phi > 136.3) && (global_phi <= 173.)) {
	  EMTFsector1 = 3;
	  EMTFsector2 = 0;
	}
	if ((global_phi > 173.) && (global_phi <= 180.)) {
	  EMTFsector1 = 3;
	  EMTFsector2 = 4;
	}
	//Greater than -180
	if ((global_phi < -165.) && (global_phi >= -180.)) {
	  EMTFsector1 = 3;
	  EMTFsector2 = 4;
	}
	//Fourth sector
	if ((global_phi > -165.) && (global_phi <= -163.7)) {
	  EMTFsector1 = 3;
	  EMTFsector2 = 4;
	}
	if ((global_phi > -163.7) && (global_phi <= -127.)) {
	  EMTFsector1 = 4;
	  EMTFsector2 = 0;
	}
	if ((global_phi > -127.) && (global_phi <= -105.)) {
	  EMTFsector1 = 4;
	  EMTFsector2 = 5;
	}
	//fifth sector
	if ((global_phi > -105.) && (global_phi <= -103.7)) {
	  EMTFsector1 = 4;
	  EMTFsector2 = 5;
	}
	if ((global_phi > -103.7) && (global_phi <= -67.)) {
	  EMTFsector1 = 5;
	  EMTFsector2 = 0;
	}
	if ((global_phi > -67.) && (global_phi <= -45.)) {
	  EMTFsector1 = 5;
	  EMTFsector2 = 6;
	} 
	//sixth sector
	if ((global_phi > -45.) && (global_phi <= -43.7)) {
	  EMTFsector1 = 5;
	  EMTFsector2 = 6;
	} 
	if ((global_phi > -43.7) && (global_phi <= -7.)) {
	  EMTFsector1 = 6;
	  EMTFsector2 = 0;
	}
	if ((global_phi > -7.) && (global_phi <= 15.)) {
	  EMTFsector1 = 6;
	  EMTFsector2 = 1;
	} 
	
	
	// std::vector<RecHitProcessor::CppfItem>::iterator it;
	// for(it = CppfVec1.begin(); it != CppfVec1.end(); it++){
	//	if( (*it).rawId == rawId) if(Geo_true) std::cout << (*it).rawId << "rawid" << rawId << std::endl;
	//	}
	//Loop over the look up table    
	for (auto& cppf : CppfVec1 ) {
	  //Condition to save the CPPFDigi
	  if((cppf.rawId == rawId) && (cppf.strip == rechitstrip)){
	    //Using the RPCGeometry	
	    if(Geo){
	//RecHitProcessor::print(cppf.int_phi, cppf.int_theta, global_phi, global_theta);
	      l1t::CPPFDigi* MainVariables1 = new l1t::CPPFDigi(rpcId, Bx , cppf.int_phi, cppf.int_theta, EMTFsector1, isValid, cppf.strip, clustersize, station, global_phi, global_theta);
	      l1t::CPPFDigi* MainVariables2 = new l1t::CPPFDigi(rpcId, Bx , cppf.int_phi, cppf.int_theta, EMTFsector2, isValid, cppf.strip, clustersize, station, global_phi, global_theta);
	      if ((EMTFsector1 > 0) && (EMTFsector2 == 0)){
		cppfDigis.push_back(*MainVariables1);
	      } 
	      if ((EMTFsector1 > 0) && (EMTFsector2 > 0)){
		cppfDigis.push_back(*MainVariables1);
		cppfDigis.push_back(*MainVariables2);
	      }
	      if ((EMTFsector1 == 0) && (EMTFsector2 == 0)) {
		continue; 
	      } 
	    } //Geo is true
	    else if (!Geo){
	      global_phi = 0.;
	      global_theta = 0.;
	      l1t::CPPFDigi* MainVariables1 = new l1t::CPPFDigi(rpcId, Bx , cppf.int_phi, cppf.int_theta, EMTFsector1, isValid, cppf.strip, clustersize,station, global_phi, global_theta);
	      l1t::CPPFDigi* MainVariables2 = new l1t::CPPFDigi(rpcId, Bx , cppf.int_phi, cppf.int_theta, EMTFsector2, isValid, cppf.strip, clustersize,station, global_phi, global_theta);
	      if ((EMTFsector1 > 0) && (EMTFsector2 == 0)){
		cppfDigis.push_back(*MainVariables1);
	      } 
	      if ((EMTFsector1 > 0) && (EMTFsector2 > 0)){
		cppfDigis.push_back(*MainVariables1);
		cppfDigis.push_back(*MainVariables2);
	      }
	      if ((EMTFsector1 == 0) && (EMTFsector2 == 0)) {
		continue;
	      } 
	    }
	  } //Condition to save the CPPFDigi 
	} //Loop over the LUTVector
      } //Loop over the recHits
    } // End loop: for (std::vector<const RPCRoll*>::const_iterator r = rolls.begin(); r != rolls.end(); ++r)
  } // End loop: for (TrackingGeometry::DetContainer::const_iterator iDet = rpcGeom->dets().begin(); iDet < rpcGeom->dets().end(); iDet++)  
  
}


void RecHitProcessor::process(
			      const edm::Event& iEvent,
			      const edm::EventSetup& iSetup,
			      const edm::EDGetToken& recHitToken,
			      l1t::CPPFDigiCollection& cppfDigis
			      ) const {
  
  // Get the RPC Geometry
  edm::ESHandle<RPCGeometry> rpcGeom;
  iSetup.get<MuonGeometryRecord>().get(rpcGeom);
  
  // Get the RecHits from the event
  edm::Handle<RPCRecHitCollection> recHits;
  iEvent.getByToken(recHitToken, recHits);
  
  
  // Loop over ... what, exactly?
  for ( TrackingGeometry::DetContainer::const_iterator iDet = rpcGeom->dets().begin(); iDet < rpcGeom->dets().end(); iDet++ ) {
    
    // What does this do?  Check whether the chamber is an RPC chamber?
    if (dynamic_cast<const RPCChamber*>( *iDet ) == 0 ) continue;
    
    auto chamb = dynamic_cast<const RPCChamber* >( *iDet ); 
    std::vector<const RPCRoll*> rolls = (chamb->rolls());
    
    // Loop over rolls in the chamber
    for (std::vector<const RPCRoll*>::const_iterator iRoll = rolls.begin(); iRoll != rolls.end(); ++iRoll) {
      
      RPCDetId rpcId = (*iRoll)->id();	
      
      typedef std::pair<RPCRecHitCollection::const_iterator, RPCRecHitCollection::const_iterator> rangeRecHits;
      rangeRecHits recHitCollection =  recHits->get(rpcId);
      
      
      for (RPCRecHitCollection::const_iterator rechit_it = recHitCollection.first; rechit_it != recHitCollection.second; rechit_it++) {	  
	
        //const RPCDetId& rpcId = rechit_it->rpcId();
        //int rawId = rpcId.rawId();
        int region = rpcId.region();
        int station = rpcId.station();
        int Bx = rechit_it->BunchX(); 
        int isValid = rechit_it->isValid();
        int firststrip = rechit_it->firstClusterStrip();
        int clustersize = rechit_it->clusterSize();
        LocalPoint lPos = rechit_it->localPosition();
        const RPCRoll* roll = rpcGeom->roll(rpcId);
        const BoundPlane& rollSurface = roll->surface();
        GlobalPoint gPos = rollSurface.toGlobal(lPos);
        float global_theta = emtf::rad_to_deg(gPos.theta().value());
        float global_phi   = emtf::rad_to_deg(gPos.phi().value());
        //Endcap region only
	
        if (region != 0) {
	  
	  int int_theta = (region == -1 ? 180. * 32. / 36.5 : 0.)
	    + (float)region * global_theta * 32. / 36.5   
	    - 8.5 * 32 / 36.5;
	  
	  if(region == 1) {
	    if(global_theta < 8.5) int_theta = 0;
	    if(global_theta > 45.) int_theta = 31;
	  } 
	  if(region == -1) {
	    if(global_theta < 135.) int_theta = 31;
	    if(global_theta > 171.5) int_theta = 0;
	  } 
	  
	  //Local EMTF
	  double local_phi = 0.;
	  int EMTFsector1 = 0;
	  int EMTFsector2 = 0;
	  
	  //sector 1
	  if ((global_phi > 15.) && (global_phi <= 16.3)) {
	    local_phi = global_phi-15.;
	    EMTFsector1 = 1;
	    EMTFsector2 = 6;
	  }
	  if ((global_phi > 16.3) && (global_phi <= 53.)) {
	    local_phi = global_phi-15.;
	    EMTFsector1 = 1;
	    EMTFsector2 = 0;
	  }
	  if ((global_phi > 53.) && (global_phi <= 75.)) {
	    local_phi = global_phi-15.;
	    EMTFsector1 = 1;
	    EMTFsector2 = 2;
	  }
	  //sector 2 
	  if ((global_phi > 75.) && (global_phi <= 76.3)) {
	    local_phi = global_phi-15.;
	    EMTFsector1 = 1;
	    EMTFsector2 = 2;
	  }
	  if ((global_phi > 76.3) && (global_phi <= 113.)) {
	    local_phi = global_phi-75.;
	    EMTFsector1 = 2;
	    EMTFsector2 = 0;
	  }
	  if ((global_phi > 113.) && (global_phi <= 135.)) {
	    local_phi = global_phi-75.;
	    EMTFsector1 = 2;
	    EMTFsector2 = 3;
	  }
	  //sector 3
	  //less than 180
	  if ((global_phi > 135.) && (global_phi <= 136.3)) {
	    local_phi = global_phi-75.;
	    EMTFsector1 = 2;
	    EMTFsector2 = 3;
	  }
	  if ((global_phi > 136.3) && (global_phi <= 173.)) {
	    local_phi = global_phi-135.;
	    EMTFsector1 = 3;
	    EMTFsector2 = 0;
	  }
	  if ((global_phi > 173.) && (global_phi <= 180.)) {
	    local_phi = global_phi-135.;
	    EMTFsector1 = 3;
	    EMTFsector2 = 4;
	  }
	  //Greater than -180
	  if ((global_phi < -165.) && (global_phi >= -180.)) {
	    local_phi = global_phi+225.;
	    EMTFsector1 = 3;
	    EMTFsector2 = 4;
	  }
	  //Fourth sector
	  if ((global_phi > -165.) && (global_phi <= -163.7)) {
	    local_phi = global_phi+225.;
	    EMTFsector1 = 3;
	    EMTFsector2 = 4;
	  }
	  if ((global_phi > -163.7) && (global_phi <= -127.)) {
	    local_phi = global_phi+165.;
	    EMTFsector1 = 4;
	    EMTFsector2 = 0;
	  }
	  if ((global_phi > -127.) && (global_phi <= -105.)) {
	    local_phi = global_phi+165.;
	    EMTFsector1 = 4;
	    EMTFsector2 = 5;
	  }
	  //fifth sector
	  if ((global_phi > -105.) && (global_phi <= -103.7)) {
	    local_phi = global_phi+165.;
	    EMTFsector1 = 4;
	    EMTFsector2 = 5;
	  }
	  if ((global_phi > -103.7) && (global_phi <= -67.)) {
	    local_phi = global_phi+105.;
	    EMTFsector1 = 5;
	    EMTFsector2 = 0;
	  }
	  if ((global_phi > -67.) && (global_phi <= -45.)) {
	    local_phi = global_phi+105.;
	    EMTFsector1 = 5;
	    EMTFsector2 = 6;
	  } 
	  //sixth sector
	  if ((global_phi > -45.) && (global_phi <= -43.7)) {
	    local_phi = global_phi+105.;
	    EMTFsector1 = 5;
	    EMTFsector2 = 6;
	  } 
	  if ((global_phi > -43.7) && (global_phi <= -7.)) {
	    local_phi = global_phi+45.;
	    EMTFsector1 = 6;
	    EMTFsector2 = 0;
	  }
	  if ((global_phi > -7.) && (global_phi <= 15.)) {
	    local_phi = global_phi+45.;
	    EMTFsector1 = 6;
	    EMTFsector2 = 1;
	  } 
	  
	  int int_phi = int((local_phi + 22.0 )*15. + .5); 
	  
	  //Invalid hit
	  if (isValid == 0) int_phi = 2047;	 
	  //Right integers range
	  assert(0 <= int_phi && int_phi < 1250);
	  assert(0 <= int_theta && int_theta < 32);
	  
	  l1t::CPPFDigi* MainVariables1 = new l1t::CPPFDigi(rpcId, Bx, int_phi, int_theta, EMTFsector1, isValid, firststrip, clustersize, station, global_phi, global_theta);
	  l1t::CPPFDigi* MainVariables2 = new l1t::CPPFDigi(rpcId, Bx, int_phi, int_theta, EMTFsector2, isValid, firststrip, clustersize, station, global_phi, global_theta);
	  if(int_theta == 31) continue;
          if ((EMTFsector1 > 0) && (EMTFsector2 == 0)){
	    cppfDigis.push_back(*MainVariables1);
	  } 
          if ((EMTFsector1 > 0) && (EMTFsector2 > 0)){
	    cppfDigis.push_back(*MainVariables1);
	    cppfDigis.push_back(*MainVariables2);
	  }
	  if ((EMTFsector1 == 0) && (EMTFsector2 == 0)){
	    continue;
	  } 
        } // No barrel rechits	
	
      } // End loop: for (RPCRecHitCollection::const_iterator recHit = recHitCollection.first; recHit != recHitCollection.second; recHit++)
      
    } // End loop: for (std::vector<const RPCRoll*>::const_iterator r = rolls.begin(); r != rolls.end(); ++r)
  } // End loop: for (TrackingGeometry::DetContainer::const_iterator iDet = rpcGeom->dets().begin(); iDet < rpcGeom->dets().end(); iDet++)
} // End function: void RecHitProcessor::process()


  


