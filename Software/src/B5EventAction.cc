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
// $Id: B5EventAction.cc 87359 2014-12-01 16:04:27Z gcosmo $
//
/// \file B5EventAction.cc
/// \brief Implementation of the B5EventAction class

#include "B5EventAction.hh"
#include "ScintillatorHit.hh"
//#include "B5DriftChamberHit.hh"
//#include "DetectorConstruction.hh"
//#include "B5EmCalorimeterHit.hh"
//#include "B5HadCalorimeterHit.hh"
#include "B5Analysis.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include "Randomize.hh"
#include <math.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B5EventAction::B5EventAction() : G4UserEventAction()
{
  // set printing per each event
  G4RunManager::GetRunManager()->SetPrintProgress(10000);

  // Create the messenger file
  EvtMessenger = new B5EventActionMessenger(this);

 // analysed_events=0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B5EventAction::~B5EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B5EventAction::BeginOfEventAction(const G4Event* event)
{


//      B5DetectorConstruction* b5 = (B5DetectorConstruction*) G4RunManager::GetRunManager()->GetUserDetectorConstruction();
      // G4cout << "Event " << (int) b5->GetN() << G4endl;

//      fHH.clear();

//	G4cout << "HELLO!!!! " << b5->GetN() << G4endl;

//    for(int i=0;i<(int) b5->GetN();i++){
//
//      char char_sdname[20];
//      sprintf(char_sdname,"paddles1/det%d",i);
//      G4String sdname(char_sdname);
//
//      fHH.push_back(sdManager->GetCollectionID(sdname));
//
//    }

      // fHHC1ID = sdManager->GetCollectionID("paddle0/hodoscopeColl");
      // fHHC2ID = sdManager->GetCollectionID("paddle1/hodoscopeColl");
      // fHHC3ID = sdManager->GetCollectionID("paddle2/hodoscopeColl");

      // fDHC1ID = sdManager->GetCollectionID("chamber1/driftChamberColl");
      // fDHC2ID = sdManager->GetCollectionID("chamber2/driftChamberColl");
      // fECHCID = sdManager->GetCollectionID("EMcalorimeter/EMcalorimeterColl");
      // fHCHCID = sdManager->GetCollectionID("HadCalorimeter/HadCalorimeterColl");

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B5EventAction::EndOfEventAction(const G4Event* event)
{
    std::cout << "End of event " << event->GetEventID() << std::endl;

    std::vector<ScintillatorHitsCollection*> hc;
    G4bool hc_exists=true;
    for(int i=0;i<12;i++){
        hc.push_back((ScintillatorHitsCollection*) event->GetHCofThisEvent()->GetHC(i));
        if(!hc.back()) hc_exists=false;
    }

/*    ScintillatorHitsCollection* h00 = (ScintillatorHitsCollection*) event->GetHCofThisEvent()->GetHC(0);
    ScintillatorHitsCollection* h10 = (ScintillatorHitsCollection*) event->GetHCofThisEvent()->GetHC(1);

    ScintillatorHitsCollection* h01 = (ScintillatorHitsCollection*) event->GetHCofThisEvent()->GetHC(2);
    ScintillatorHitsCollection* h11 = (ScintillatorHitsCollection*) event->GetHCofThisEvent()->GetHC(3);

    ScintillatorHitsCollection* h02 = (ScintillatorHitsCollection*) event->GetHCofThisEvent()->GetHC(4);
    ScintillatorHitsCollection* h12 = (ScintillatorHitsCollection*) event->GetHCofThisEvent()->GetHC(5);

    ScintillatorHitsCollection* h03 = (ScintillatorHitsCollection*) event->GetHCofThisEvent()->GetHC(6);
    ScintillatorHitsCollection* h13 = (ScintillatorHitsCollection*) event->GetHCofThisEvent()->GetHC(7);

    ScintillatorHitsCollection* h04 = (ScintillatorHitsCollection*) event->GetHCofThisEvent()->GetHC(8);
    ScintillatorHitsCollection* h14 = (ScintillatorHitsCollection*) event->GetHCofThisEvent()->GetHC(9);

    ScintillatorHitsCollection* h05 = (ScintillatorHitsCollection*) event->GetHCofThisEvent()->GetHC(10);
    ScintillatorHitsCollection* h15 = (ScintillatorHitsCollection*) event->GetHCofThisEvent()->GetHC(11);
*/

    if (!hc_exists)
    {
        G4ExceptionDescription msg;
        msg << "No hits collection of this event found." << G4endl;
        G4Exception("B5EventAction::EndOfEventAction()",
                    "B5Code001", JustWarning, msg);
        return;
    }

    std::vector<G4double> Edeps;
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillNtupleDColumn(0,event->GetEventID());
    for(int i=0;i<12;i++){
        // Get the number of hits
        int nhits = (int)  (hc.at(i))->GetSize();

        // Initialise the average energy of the hits
        G4double ev=0.0;
        G4double tv=0.0;
        for(int ihit=0;ihit<nhits;ihit++){
            std::cout << " nhits " << nhits << " " << ihit << std::endl;

            ev+=( *(hc.at(i)) )[ihit]->GetEdep()/MeV;
            tv+=( *(hc.at(i)) )[ihit]->GetTime()/ns;
        }
        ev/=nhits;
        tv/=nhits;
        analysisManager->FillNtupleDColumn(2*i+1,ev);
        analysisManager->FillNtupleDColumn(2*i+2,tv);
    }
    analysisManager->AddNtupleRow();

    G4int printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
    if ( printModulo==0 || event->GetEventID() % printModulo != 0) return;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
