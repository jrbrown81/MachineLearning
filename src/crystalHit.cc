#include"crystalHit.hh"

crystalHit::crystalHit()
:nHits(0),
totalEnergy(0.)
{}

crystalHit::~crystalHit()
{}

void crystalHit::AddHit(){
	nHits++;
}

G4int crystalHit::GetNHits(){
	return nHits;
}

void crystalHit::AddVecX(G4double xPos){
	fXpos.push_back(xPos); 
}

void crystalHit::AddVecY(G4double yPos){
	fYpos.push_back(yPos); 
}

void crystalHit::AddVecZ(G4double zPos){
	fZpos.push_back(zPos); 
}

void crystalHit::AddProcess(G4int process){
	fProcess.push_back(process);
}	

void crystalHit::AddEdep(G4double edep){
	totalEnergy+=edep;
}

G4double crystalHit::GetTotalEnergy(){
	return(totalEnergy);
}

void crystalHit::Reset(){
	totalEnergy=0;
	nHits=0;
	
	fXpos.clear();
	fYpos.clear();
	fZpos.clear();
	fProcess.clear();
}