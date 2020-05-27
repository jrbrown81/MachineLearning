// header file: sipmHit.hh

#include "G4VHit.hh"
#include "G4THitsCollection.hh"

class sipmHit:public G4VHit {

	public:
		sipmHit();
		virtual ~sipmHit();

		void SetEnergyDeposit(G4double energy); 
		void SetXpos(G4double xpos);
	  void SetYpos(G4double ypos);
	  void SetZpos(G4double zpos);
		void SetHitTime(G4double hitTime);
		void SetDetNo(G4int copyNo);
	
		G4double GetEnergyDeposit();
		G4double GetXpos();
		G4double GetYpos();
		G4double GetZpos();
		G4double GetHitTime();
		G4int GetDetNo();
	
	private: 
		G4double energyDeposit;
		G4double Xpos;
		G4double Ypos;
		G4double Zpos;
		G4double hTime;
		G4int detNo;

};

typedef G4THitsCollection<sipmHit> sipmHitsCollection;
