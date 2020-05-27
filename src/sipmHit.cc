#include"sipmHit.hh"

sipmHit::sipmHit()
{}

sipmHit::~sipmHit()
{}

void sipmHit::SetEnergyDeposit(G4double energy){
	energyDeposit = energy;
}

G4double sipmHit::GetEnergyDeposit(){
	return(energyDeposit);
}

void sipmHit::SetXpos(G4double xpos){
	Xpos = xpos;
}

G4double sipmHit::GetXpos(){
	return(Xpos);
}

void sipmHit::SetYpos(G4double ypos){
	Ypos=ypos;
}

G4double sipmHit::GetYpos(){
	return(Ypos);
}

void sipmHit::SetZpos(G4double zpos){
	Zpos=zpos;
}

G4double sipmHit::GetZpos(){
	return(Zpos);
}

void sipmHit::SetHitTime(G4double hitTime){
	hTime = hitTime;
}

G4double sipmHit::GetHitTime(){
	return(hTime);
}

void sipmHit::SetDetNo(G4int copyNo){
	detNo = copyNo;
}

G4int sipmHit::GetDetNo(){
	return(detNo);
}