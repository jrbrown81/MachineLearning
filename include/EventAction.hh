#include "G4UserEventAction.hh"
#include "globals.hh"
#include <vector>

class EventAction: public G4UserEventAction{

	public: 
		EventAction();
				~EventAction();	

	virtual void BeginOfEventAction(const G4Event*);
	virtual void EndOfEventAction(const G4Event* );

//	std::vector<G4double>& GetVecX() { return fXpos; }
//	std::vector<G4double>& GetVecY() { return fYpos; }
//	std::vector<G4double>& GetVecZ() { return fZpos; }
//	std::vector<G4double>& GetVecT() { return fTime; }
//	std::vector<G4double>& GetVecE() { return fEnergy; }
//	std::vector<G4int>& GetVecDetID() { return fDetID; }
	std::vector<G4int>& GetVecSipmHits() { return fSipmHits; }
	
	std::vector<G4double>& GetVecXGamma() { return fXposGamma; }
	std::vector<G4double>& GetVecYGamma() { return fYposGamma; }
	std::vector<G4double>& GetVecZGamma() { return fZposGamma; }
	std::vector<G4int>& GetProcess() { return fProcess; }


	private:
// 		std::vector<G4double> fXpos;
// 		std::vector<G4double> fYpos;
// 		std::vector<G4double> fZpos;
//		std::vector<G4double> fTime;
//		std::vector<G4double> fEnergy;
//		std::vector<G4int> fDetID;
		std::vector<G4int> fSipmHits;
	
 		std::vector<G4double> fXposGamma;
 		std::vector<G4double> fYposGamma;
 		std::vector<G4double> fZposGamma;
 		std::vector<G4int> fProcess;
};
