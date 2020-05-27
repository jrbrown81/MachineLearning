#include "G4VSensitiveDetector.hh"
#include "crystalHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;

class crystalSD:public G4VSensitiveDetector{

	public:
		crystalSD(const G4String& name,
			    const G4String& hitsCollectionName);
		virtual ~crystalSD();

		virtual void Initialize(G4HCofThisEvent*HCofEvent);
		virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory *ROhist);

 		virtual void EndOfEvent(G4HCofThisEvent* HCE);
 		
	private:
		crystalHitsCollection* fHitsCollection;
 				
};
