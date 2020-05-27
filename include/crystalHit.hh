// header file: crystalHit.hh

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include <vector>

class crystalHit:public G4VHit {

	public:
		crystalHit();
		virtual ~crystalHit();

		void AddHit();
		void AddEdep(G4double energy);
		void Reset();

		G4int GetNHits();
		G4double GetTotalEnergy();
		G4double GetVecX(G4int i) { return fXpos[i] ; }
		G4double GetVecY(G4int i) { return fYpos[i] ; }
		G4double GetVecZ(G4int i) { return fZpos[i] ; }
		G4int GetProcess(G4int i) { return fProcess[i] ; }

		void AddVecX(G4double xPos);
		void AddVecY(G4double yPos);
		void AddVecZ(G4double zPos);
		void AddProcess(G4int process);
		
	private: 
		G4int nHits;
		G4double totalEnergy;
		
 		std::vector<G4double> fXpos;
 		std::vector<G4double> fYpos;
 		std::vector<G4double> fZpos;
 		std::vector<G4int> fProcess;
};

typedef G4THitsCollection<crystalHit> crystalHitsCollection;
