#include "crystalSD.hh"
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

crystalSD::crystalSD(const G4String& detectorUniqueName,
					 const G4String& hitsCollectionName)
		       :G4VSensitiveDetector(detectorUniqueName),
			fHitsCollection(NULL){

	collectionName.insert(hitsCollectionName);
}

crystalSD::~crystalSD()
{} 

//**********************************************************

void crystalSD::Initialize(G4HCofThisEvent* HCE){

	fHitsCollection = new crystalHitsCollection(SensitiveDetectorName,collectionName[0]);

	static G4int collectionID = -1;
	if(collectionID<0) collectionID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
//	G4int collectionID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);

	HCE->AddHitsCollection(collectionID,fHitsCollection);
	
	fHitsCollection->insert(new crystalHit());

}

//*********************************************************

G4bool crystalSD::ProcessHits(G4Step* aStep
					,G4TouchableHistory*)
{

	G4Track* track = aStep->GetTrack();

	G4String ParticleName = track->GetDynamicParticle()->
                             GetParticleDefinition()->GetParticleName();
	
	G4String processName;

//Get the postpoint position 
  G4StepPoint* thePostPoint = aStep->GetPostStepPoint();
  processName = thePostPoint->GetProcessDefinedStep()->GetProcessName();

	if(ParticleName != "opticalphoton"){

	  G4double edep = aStep->GetTotalEnergyDeposit();
	  G4ThreeVector PostPointPos = thePostPoint->GetPosition();

		crystalHit* gammaHit = (*fHitsCollection)[0];
		gammaHit->AddEdep(edep);

		G4double deltaEnergy = aStep->GetDeltaEnergy();

		if(ParticleName == "gamma" && deltaEnergy<0){
			gammaHit->AddHit();
			gammaHit->AddVecX(PostPointPos.getX());
			gammaHit->AddVecY(PostPointPos.getY());
			gammaHit->AddVecZ(PostPointPos.getZ());
			if(processName=="phot") gammaHit->AddProcess(1);
			else if(processName=="compt") gammaHit->AddProcess(2);
			else if(processName=="conv") gammaHit->AddProcess(3);
			else gammaHit->AddProcess(0);
		}

		return true;
 	}
	else return false;

}

//***********************************************************

void crystalSD::EndOfEvent(G4HCofThisEvent* HCE){
}

//**********************************************************
