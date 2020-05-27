#include "G4VSensitiveDetector.hh"
#include "sipmHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;

class sipmSD:public G4VSensitiveDetector{

	public:
		sipmSD(const G4String& name,
			    const G4String& hitsCollectionName);
		virtual ~sipmSD();

		virtual void Initialize(G4HCofThisEvent*HCofEvent);
		virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory *ROhist);

 		virtual void EndOfEvent(G4HCofThisEvent* HCE);
 		
	private:
		sipmHitsCollection* fHitsCollection;
 				
};
