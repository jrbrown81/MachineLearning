#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4VHit.hh"
#include "G4SystemOfUnits.hh"

#include "EventAction.hh"
#include "sipmHit.hh"
#include "crystalHit.hh"
#include "Analysis.hh"

//Define Inline functions
//Function to retrieve The HitCollection you want via its Unique name
sipmHitsCollection* GetSipmCollection(const G4Event* event, G4String name);
crystalHitsCollection* GetCrystalCollection(const G4Event* event, G4String name);

EventAction::EventAction()
: G4UserEventAction()
{}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{
	G4int evtNb = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
	if(evtNb%100==0) G4cout << ">>>>>> Beginning of Event " << evtNb << " <<<<<<" << G4endl;
}

void EventAction::EndOfEventAction(const G4Event* event){

	sipmHitsCollection* mycollection = GetSipmCollection(event,"photonHitsCollection");

// Instantiate analysisManager 
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

//Get the number of hits inside the 	
	G4int numberHits = mycollection->entries();
	G4int hits0=0, hits1=0, hits2=0, hits3=0, hits4=0, hits5=0;
 	analysisManager->FillNtupleIColumn(0,numberHits);
 	
// Loop over hits collection and fill vectors (which are linked to ntuple)
	for(int i=0;i<numberHits;i++){

		sipmHit* thisHit = (*mycollection)[i];
		fXpos.push_back(thisHit->GetXpos());
		fYpos.push_back(thisHit->GetYpos());
		fZpos.push_back(thisHit->GetZpos());
		fTime.push_back(thisHit->GetHitTime());
		fEnergy.push_back(thisHit->GetEnergyDeposit());
		fDetID.push_back(thisHit->GetDetNo());
	// Count hits in each sipm (if adding more sipm it should be here)
		if(thisHit->GetDetNo()==0) hits0++;
		if(thisHit->GetDetNo()==1) hits1++;
		if(thisHit->GetDetNo()==2) hits2++;
		if(thisHit->GetDetNo()==3) hits3++;
		if(thisHit->GetDetNo()==4) hits4++;
		if(thisHit->GetDetNo()==5) hits5++;
	}
	analysisManager->FillNtupleIColumn(13,hits0);
 	analysisManager->FillNtupleIColumn(14,hits1);
 	analysisManager->FillNtupleIColumn(15,hits2);
 	analysisManager->FillNtupleIColumn(16,hits3);
 	analysisManager->FillNtupleIColumn(17,hits4);
 	analysisManager->FillNtupleIColumn(18,hits5);
	
	crystalHitsCollection* myXtalCollection = GetCrystalCollection(event,"gammaHitsCollection");
	crystalHit* gammaHit = (*myXtalCollection)[0];
	G4double gammaEnergy = gammaHit->GetTotalEnergy();
	G4int nGammaHits = gammaHit->GetNHits();
	
	for(int i=0;i<nGammaHits;i++){
		fXposGamma.push_back(gammaHit->GetVecX(i));
		fYposGamma.push_back(gammaHit->GetVecY(i));
		fZposGamma.push_back(gammaHit->GetVecZ(i));
		fProcess.push_back(gammaHit->GetProcess(i));
	}
	
	analysisManager->FillNtupleDColumn(7,gammaEnergy);
	analysisManager->FillNtupleIColumn(8,nGammaHits);
	
	if(nGammaHits==0 && numberHits==0) G4cout << "No gamma or photon hits" << G4endl;
	else if(nGammaHits==0) G4cout << "No gamma hits" << G4endl;
	else if(numberHits==0) G4cout << "No photon hits" << G4endl;
	else analysisManager->AddNtupleRow();

	fXpos.clear();
	fYpos.clear();
	fZpos.clear();
	fTime.clear();
	fEnergy.clear();
	fDetID.clear();
	
	fXposGamma.clear();
	fYposGamma.clear();
	fZposGamma.clear();
	fProcess.clear();
		
	gammaHit->Reset();
	
}

sipmHitsCollection* GetSipmCollection(const G4Event* event,G4String name){

//Get instances of SensitiveDetector manager and Run Manager
  G4SDManager* fSDM = G4SDManager::GetSDMpointer();
//Get the collection ID of the type of Hits Collection you want 
  G4int collectionID = fSDM->GetCollectionID(name);
//Get the current event 
  G4HCofThisEvent* HCE = event->GetHCofThisEvent();
// Instantiate a new hitcollection = to the hitscollection of choice  (i.e. a new vector)
	sipmHitsCollection*  myCollection = (sipmHitsCollection*)(HCE->GetHC(collectionID));

	return(myCollection);

}

crystalHitsCollection* GetCrystalCollection(const G4Event* event,G4String name){

//Get instances of SensitiveDetector manager and Run Manager
  G4SDManager* fSDM = G4SDManager::GetSDMpointer();
//Get the collection ID of the type of Hits Collection you want 
  G4int collectionID = fSDM->GetCollectionID(name);
//Get the current event 
  G4HCofThisEvent* HCE = event->GetHCofThisEvent();
// Instantiate a new hitcollection = to the hitscollection of choice  (i.e. a new vector)
	crystalHitsCollection*  myCollection = (crystalHitsCollection*)(HCE->GetHC(collectionID));

	return(myCollection);

}
