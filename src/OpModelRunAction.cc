//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Make this appear first!
#include "G4Timer.hh"
#include "Analysis.hh"
#include "OpModelRunAction.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Run.hh"

#include "EventAction.hh"
#include "G4RunManager.hh"

#include <sstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpModelRunAction::OpModelRunAction()
 : G4UserRunAction(),
   fTimer(0)
{
  fTimer = new G4Timer;

// Create analysis manager
  G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
//	analysisManager->SetNtupleMerging(true);
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFirstHistoId(1);
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpModelRunAction::~OpModelRunAction()
{
  delete fTimer;
  delete G4AnalysisManager::Instance(); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OpModelRunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
  fTimer->Start();

   G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
   analysisManager->OpenFile("RootOut");

 // Creating ntuple
 //
  analysisManager->CreateNtuple("photonList", "Photon Energy and Position List");

// Get event action
  const EventAction* constEventAction
       = static_cast<const EventAction*>(G4RunManager::GetRunManager()
         ->GetUserEventAction());
  EventAction* eventAction = const_cast<EventAction*>(constEventAction);

  analysisManager->CreateNtupleIColumn("hits");	// Column ID 0;
// Vectors of photon hits
//  analysisManager->CreateNtupleDColumn("x",eventAction->GetVecX());
//	analysisManager->CreateNtupleDColumn("y",eventAction->GetVecY());
//	analysisManager->CreateNtupleDColumn("z",eventAction->GetVecZ());
//	analysisManager->CreateNtupleDColumn("t",eventAction->GetVecT());
//	analysisManager->CreateNtupleDColumn("E",eventAction->GetVecE());	// Column ID 5;
//	analysisManager->CreateNtupleIColumn("sipmID",eventAction->GetVecDetID());
// Energy deposited by gamma ray
	analysisManager->CreateNtupleDColumn("Egam"); // Column ID 1
	analysisManager->CreateNtupleIColumn("gammaHits"); // Column 2
// Vectors of gamma hits
	analysisManager->CreateNtupleIColumn("process",eventAction->GetProcess());
  analysisManager->CreateNtupleDColumn("xGam",eventAction->GetVecXGamma());	// Column ID 4
  analysisManager->CreateNtupleDColumn("yGam",eventAction->GetVecYGamma());
  analysisManager->CreateNtupleDColumn("zGam",eventAction->GetVecZGamma());	// Column ID 6
  
  analysisManager->CreateNtupleIColumn("sipmHits",eventAction->GetVecSipmHits());	// Column ID 6

// Hits per SiPM
//  analysisManager->CreateNtupleIColumn("hits0"); // Column 13
//  analysisManager->CreateNtupleIColumn("hits1"); // Colunm 14
//  analysisManager->CreateNtupleIColumn("hits2"); // Column 15
//  analysisManager->CreateNtupleIColumn("hits3"); // Colunm 16
//  analysisManager->CreateNtupleIColumn("hits4"); // Column 17
//  analysisManager->CreateNtupleIColumn("hits5"); // Colunm 18
// Hits per SiPM if using array of 64 pixels
//	G4String detectorString;
//	std::stringstream ss;
//  for(G4int i=0;i<64;i++) {
//		ss.str("");
//		ss << "sipm" << i;
//		detectorString = ss.str();
//		analysisManager->CreateNtupleIColumn(detectorString); // Colunm 7 to 71
//	}
	
  analysisManager->FinishNtuple();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OpModelRunAction::EndOfRunAction(const G4Run* aRun)
{

  // Define stuff for Analysis manager
  G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();  

  fTimer->Stop();
  G4cout << "Total number of events = " << aRun->GetNumberOfEvent() << G4endl
         << "Elapsed time: " << *fTimer << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
