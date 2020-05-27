#include "sipmSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4VProcess.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4OpticalPhoton.hh"

sipmSD::sipmSD(const G4String& detectorUniqueName,
					 const G4String& hitsCollectionName)
		       :G4VSensitiveDetector(detectorUniqueName),
			fHitsCollection(NULL){

	collectionName.insert(hitsCollectionName);
}

sipmSD::~sipmSD()
{} 

//**********************************************************

void sipmSD::Initialize(G4HCofThisEvent* HCE){

	fHitsCollection = new sipmHitsCollection(SensitiveDetectorName,collectionName[0]);

	static G4int collectionID = -1;
	if(collectionID<0) collectionID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
//	G4int collectionID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);

	HCE->AddHitsCollection(collectionID,fHitsCollection); 

}

//*********************************************************

G4bool sipmSD::ProcessHits(G4Step* aStep
					,G4TouchableHistory*)
{

G4Track* track = aStep->GetTrack();

G4String ParticleName = track->GetDynamicParticle()->
                             GetParticleDefinition()->GetParticleName();

//Get the postpoint position
  G4StepPoint* thePostPoint = aStep->GetPostStepPoint();
//	G4TouchableHandle theTouchable = thePostPoint->GetTouchableHandle();
	G4int copyNo = aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();
	G4double edep = aStep->GetTotalEnergyDeposit();
  G4ThreeVector PostPointPos = thePostPoint->GetPosition();
 
// 	G4cout << PostPointPos.x() << " " << PostPointPos.y() << " " << copyNo << G4endl;
 
  if(edep >0. && ParticleName == "opticalphoton"){
 
  	sipmHit* newHit = new sipmHit();   
  	newHit->SetXpos(PostPointPos.x());
  	newHit->SetYpos(PostPointPos.y());
  	newHit->SetZpos(PostPointPos.z());
		newHit->SetHitTime(thePostPoint->GetGlobalTime());
		newHit->SetDetNo(copyNo);
 
  	newHit->SetEnergyDeposit(edep);
  	fHitsCollection->insert(newHit);

		return true;
	}
	else return false;
}

//***********************************************************

void sipmSD::EndOfEvent(G4HCofThisEvent* HCE)
{}

//**********************************************************
