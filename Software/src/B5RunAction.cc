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
// $Id: B5RunAction.cc 74204 2013-10-01 07:04:43Z ihrivnac $
//
/// \file B5RunAction.cc
/// \brief Implementation of the B5RunAction class

#include "B5RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "B5Analysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
//#include "B5DetectorConstruction.hh"
#include <math.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B5RunAction::B5RunAction()
 : G4UserRunAction()
{
  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in B5Analysis.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  //G4cout << "Using " << analysisManager->GetType() << G4endl;

  // Default settings
  analysisManager->SetVerboseLevel(0);
  analysisManager->SetFileName("cosmic_rays");

  // Book histograms, ntuple
  //

  // Creating 1D histograms

  /*
  analysisManager->CreateH1("Det0_Energies","Det0_Energies",200, 0., 20*MeV);
  analysisManager->CreateH1("Det1_Energies","Det1_Energies",200, 0., 20*MeV);
  analysisManager->CreateH1("TOF","TOF",250, -10*ns, 10*ns);
  analysisManager->CreateH1("AnglesXZ","ThetaXZ",200,0,M_PI);
  analysisManager->CreateH1("AnglesYZ","ThetaYZ",200,0,M_PI);
  */

/*
  analysisManager->CreateH2("Chamber1 Blob Plot","PH vs. TOF", 120, -10*ns, 10*ns, 40, 0., 20*MeV);
  analysisManager->CreateH2("Chamber2 Blob Plot","PH vs. TOF", 120, -10*ns, 10*ns,40, 0., 20*MeV);
  analysisManager->CreateH2("Chamber1 Angle-Energy Plot","Angle-Energy", 40,1.001,1.4, 40, 4., 10*MeV);
  analysisManager->CreateH2("Chamber2 Angle-Energy Plot","Angle-Energy", 40,1.001,1.4, 40, 4., 10*MeV);
*/

  analysisManager->CreateNtuple("cosmics", "Hits");          // NTuple Id = 0
  analysisManager->CreateNtupleDColumn("EventNumber");         // column Id = 0

  analysisManager->CreateNtupleDColumn("E00");         // column Id = 0
  analysisManager->CreateNtupleDColumn("T00");     // column Id = 1
  analysisManager->CreateNtupleDColumn("E01");         // column Id = 0
  analysisManager->CreateNtupleDColumn("T01");     // column Id = 1
  analysisManager->CreateNtupleDColumn("E02");         // column Id = 0
  analysisManager->CreateNtupleDColumn("T02");     // column Id = 1
  analysisManager->CreateNtupleDColumn("E03");         // column Id = 0
  analysisManager->CreateNtupleDColumn("T03");     // column Id = 1
  analysisManager->CreateNtupleDColumn("E04");         // column Id = 0
  analysisManager->CreateNtupleDColumn("T04");     // column Id = 1
  analysisManager->CreateNtupleDColumn("E05");         // column Id = 0
  analysisManager->CreateNtupleDColumn("T05");     // column Id = 1

  analysisManager->CreateNtupleDColumn("E10");         // column Id = 0
  analysisManager->CreateNtupleDColumn("T10");     // column Id = 1
  analysisManager->CreateNtupleDColumn("E11");         // column Id = 0
  analysisManager->CreateNtupleDColumn("T11");     // column Id = 1
  analysisManager->CreateNtupleDColumn("E12");         // column Id = 0
  analysisManager->CreateNtupleDColumn("T12");     // column Id = 1
  analysisManager->CreateNtupleDColumn("E13");         // column Id = 0
  analysisManager->CreateNtupleDColumn("T13");     // column Id = 1
  analysisManager->CreateNtupleDColumn("E14");         // column Id = 0
  analysisManager->CreateNtupleDColumn("T14");     // column Id = 1
  analysisManager->CreateNtupleDColumn("E15");         // column Id = 0
  analysisManager->CreateNtupleDColumn("T15");     // column Id = 1

  //analysisManager->CreateNtupleDColumn("Particle_PDG");         // column Id = 0
  analysisManager->FinishNtuple();

  //  analysisManager->CreateNtupleDColumn("EnergyDep");    // column Id = 2
  //  analysisManager->CreateNtupleDColumn("Particle");     // column Id = 3
  //  analysisManager->CreateNtupleDColumn("WichMuon");     // column Id = 4
  //  analysisManager->CreateNtupleDColumn("Paddle");       // column Id = 5
  //  analysisManager->CreateNtupleDColumn("MuonEnergy");   // column Id = 6
  //  analysisManager->CreateNtupleDColumn("MuonTime");     // column Id = 7
  //  analysisManager->CreateNtupleDColumn("EventNumber");  // column Id = 8
  //  analysisManager->FinishNtuple();



/*
  B5DetectorConstruction* b5 = (B5DetectorConstruction*) G4RunManager::GetRunManager()->GetUserDetectorConstruction();
  G4cout << "Event " << (int) b5->GetN() << G4endl;
  for(int i=0;i<(int) b5->GetN();i++){
      char char_sdname[20];
      sprintf(char_sdname,"Paddle %d",i);
      G4String name(char_sdname);
      sprintf(char_sdname,"Paddle %d Hits",i);
      G4String title(char_sdname);
      analysisManager->CreateH1(name,title, 5, 0., 4);
  }

  analysisManager->CreateH1("Anticoincidence","Anticoincidence Hits",5,0 ,4); // h1 Id = N
  analysisManager->CreateH1("Coincidence","Coincidence Hits",5,0 ,4); // h1 Id = N+1
  analysisManager->CreateH1("Stopped","Stopped",5,0 ,4); // h1 Id = N+2
*/

 // analysisManager->CreateH1("All_Hit_time","Time",1000,0*ns,500*ns);
  //analysisManager->CreateH1("Travel time","Time",1000,0*ns,20*ns);
  //analysisManager->CreateH1("Neutron Multiplicity","Neutron Multiplicity",6,0,5);
  //analysisManager->CreateH1("Gamma Multiplicity","Gamma Multiplicity",6,0,5);

  /*
  analysisManager->CreateH1("Anti Neutrons Multiplicity","Anti Neutron Multiplicity",5,0 ,4); // h1 Id = N+2
  analysisManager->CreateH1("Anti Neutrons Timing","Anti Neutron Timing",5,0 ,4); // h1 Id = N+3
  analysisManager->CreateH1("Anti Gamma Multiplicity","Anti Gamma Multiplicity",5,0 ,4); // h1 Id = N+2
  analysisManager->CreateH1("Anti Gamma Timing","Anti Gamma Timing",5,0 ,4); // h1 Id = N+3
  */






  // analysisManager->CreateH1("Paddle1","Paddle 1 # Hits", 5, 0., 4); // h1 Id = 1
  // analysisManager->CreateH1("Paddle2","Paddle 2 # Hits", 5, 0., 4); // h1 Id = 2
  // analysisManager->CreateH1("Paddle3","Paddle 3 # Hits", 5, 0., 4); // h1 Id = 3

  // analysisManager->CreateNtuple("B5", "EventsHits");
  // analysisManager->CreateNtupleIColumn("Paddle1 Edep");  // column Id = 0
  // analysisManager->CreateNtupleIColumn("Paddle2 Edep");  // column Id = 1
  // analysisManager->CreateNtupleIColumn("Paddle3 Edep");  // column Id = 2


  // Creating 2D histograms
  // analysisManager
  //   ->CreateH2("Chamber1 XY","Drift Chamber 1 X vs Y",           // h2 Id = 0
  //              50, -1000., 1000, 50, -300., 300.);
  // analysisManager
  //   ->CreateH2("Chamber2 XY","Drift Chamber 2 X vs Y",           // h2 Id = 1
  //              50, -1500., 1500, 50, -300., 300.);

  // Creating ntuple
  //
//  analysisManager->CreateNtuple("B5", "Hits");          // NTuple Id = 0
//  analysisManager->CreateNtupleDColumn("Time");         // column Id = 0
//  analysisManager->CreateNtupleDColumn("RealTime");     // column Id = 1
//  analysisManager->CreateNtupleDColumn("EnergyDep");    // column Id = 2
//  analysisManager->CreateNtupleDColumn("Particle");     // column Id = 3
//  analysisManager->CreateNtupleDColumn("WichMuon");     // column Id = 4
//  analysisManager->CreateNtupleDColumn("Paddle");       // column Id = 5
//  analysisManager->CreateNtupleDColumn("MuonEnergy");   // column Id = 6
//  analysisManager->CreateNtupleDColumn("MuonTime");     // column Id = 7
//  analysisManager->CreateNtupleDColumn("EventNumber");  // column Id = 8
//  analysisManager->FinishNtuple();
//
//  analysisManager->CreateNtuple("Events", "Events");            // NTuple Id = 1
//  analysisManager->CreateNtupleDColumn("MinTime");              // column Id = 0
//  analysisManager->CreateNtupleDColumn("RealMinTime");          // column Id = 1
//  analysisManager->CreateNtupleDColumn("NeutronMultiplicity");  // column Id = 2
//  analysisManager->CreateNtupleDColumn("GammaMultiplicity");    // column Id = 3
//  analysisManager->CreateNtupleDColumn("ProtonMultiplicity");   // column Id = 4
//  analysisManager->CreateNtupleDColumn("ElectronMultiplicity"); // column Id = 5
//  analysisManager->CreateNtupleDColumn("PositronMultiplicity"); // column Id = 6
//  analysisManager->CreateNtupleDColumn("TotalMultiplicity");    // column Id = 7
//  analysisManager->CreateNtupleDColumn("MuonEnergy");           // column Id = 8
//  analysisManager->CreateNtupleDColumn("MuonTime");             // column Id = 9
//  analysisManager->FinishNtuple();

  // analysisManager->CreateNtuple("SpHits", "SpHits");    // NTuple Id = 2
  // analysisManager->CreateNtupleDColumn("Time");         // column Id = 0
  // analysisManager->CreateNtupleDColumn("RealTime");     // column Id = 1
  // analysisManager->CreateNtupleDColumn("EnergyDep");    // column Id = 2
  // analysisManager->CreateNtupleDColumn("Particle");     // column Id = 3
  // analysisManager->CreateNtupleDColumn("WichMuon");     // column Id = 4
  // analysisManager->CreateNtupleDColumn("Paddle");       // column Id = 5
  // analysisManager->CreateNtupleDColumn("MuonEnergy");   // column Id = 6
  // analysisManager->CreateNtupleDColumn("MuonTime");     // column Id = 7
  // analysisManager->CreateNtupleDColumn("EventNumber");  // column Id = 8
  // analysisManager->FinishNtuple();

  // analysisManager->CreateNtuple("SpEvents", "SpEvents");        // NTuple Id = 3
  // analysisManager->CreateNtupleDColumn("MinTime");              // column Id = 0
  // analysisManager->CreateNtupleDColumn("RealMinTime");          // column Id = 1
  // analysisManager->CreateNtupleDColumn("NeutronMultiplicity");  // column Id = 2
  // analysisManager->CreateNtupleDColumn("GammaMultiplicity");    // column Id = 3
  // analysisManager->CreateNtupleDColumn("ProtonMultiplicity");   // column Id = 4
  // analysisManager->CreateNtupleDColumn("ElectronMultiplicity"); // column Id = 5
  // analysisManager->CreateNtupleDColumn("PositronMultiplicity"); // column Id = 6
  // analysisManager->CreateNtupleDColumn("TotalMultiplicity");    // column Id = 7
  // analysisManager->CreateNtupleDColumn("MuonEnergy");           // column Id = 8
  // analysisManager->CreateNtupleDColumn("MuonTime");             // column Id = 9
  // analysisManager->FinishNtuple();

  // analysisManager->CreateNtupleIColumn("Paddle0Hits");  // column Id = 0
  // analysisManager->CreateNtupleIColumn("Paddle1Hits");  // column Id = 1
  // analysisManager->CreateNtupleIColumn("Paddle2Hits");  // column Id = 2
  // analysisManager->CreateNtupleIColumn("Paddle3Hits");  // column Id = 3
  // analysisManager->CreateNtupleIColumn("Paddle4Hits");  // column Id = 4
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B5RunAction::~B5RunAction()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B5RunAction::BeginOfRunAction(const G4Run* /*run*/)
{
  //inform the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);

  // Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // analysisManager->CreateNtuple("B5", "Hits");
  // analysisManager->CreateNtupleDColumn("HCEnergy");
  // analysisManager->CreateNtupleDColumn("Time1");
  // analysisManager->FinishNtuple();

  // Open an output file
  // The default file name is set in B5RunAction::B5RunAction(),
  // it can be overwritten in a macro
  analysisManager->OpenFile();
  // analysisManager->CreateNtuple("B5", "Hits");
  // analysisManager->CreateNtupleDColumn("HCEnergy"); // column Id = 5
  // analysisManager->CreateNtupleDColumn("Time1");    // column Id = 6
  // analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B5RunAction::EndOfRunAction(const G4Run* run)
{
  // save histograms & ntuple
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
//  if(IsMaster()){

    // // Write out the final stats
    // B5DetectorConstruction* b5 = (B5DetectorConstruction*) G4RunManager::GetRunManager()->GetUserDetectorConstruction();

    // // Get the Pb thickness
    // G4double pb_thickness = b5->GetPbHeight();

    // // Get the muon energy
    // B5PrimaryGeneratorAction* b5_pg = (B5PrimaryGeneratorAction*) G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction();
    // G4cout << "OUTPUT" << G4endl;
    // G4double mom = b5_pg->GetMomentum();

    // G4cout << "\n\n ----> Total Histograms Statistic \n" << G4endl;
    // G4cout << mom;
    // G4cout << " " << pb_thickness;
    // G4int ind = (b5->GetN())+1;
    // G4cout << " " <<  analysisManager->GetH1(ind)->entries() ;
    // for(int i=1;i<=(int) b5->GetN();i++){
    //   G4cout << " " << analysisManager->GetH1(i)->entries();
    // }
    // G4cout << " " << analysisManager->GetH1(0)->entries() << G4endl;


/*
    std::cout.setf( std::ios_base::unitbuf );

    G4cout << "# LowerDetZ // NumberEvents // Paddle1Hits // Paddle2Hits // Paddle3Hits // Anticoincidence (1&2)&NOT(3) // Coincidence (1&2&3)" << G4endl;
    G4cout << " Run Stats :";

    // Output the Lower Detector Z
    // Write out the final stats
    B5DetectorConstruction* b5 = (B5DetectorConstruction*) G4RunManager::GetRunManager()->GetUserDetectorConstruction();
    G4cout << " " << b5->GetLowerDetZ()/cm;

    G4cout << " " << analysisManager->GetH1(0)->entries();
    // B5DetectorConstruction* b5 = (B5DetectorConstruction*) G4RunManager::GetRunManager()->GetUserDetectorConstruction();
    for(int i=1;i<=(int) b5->GetN();i++){
      G4cout << " " << analysisManager->GetH1(i)->entries();
    }
    G4int ind = (b5->GetN());
    G4cout << " " << analysisManager->GetH1(ind+1)->entries();
    G4cout << " " << analysisManager->GetH1(ind+2)->entries()   << G4endl;



    // G4cout << " Events = " << analysisManager->GetH1(0)->entries()   << G4endl;

    // B5DetectorConstruction* b5 = (B5DetectorConstruction*) G4RunManager::GetRunManager()->GetUserDetectorConstruction();
    // for(int i=1;i<=(int) b5->GetN();i++){
    //   G4cout << " Paddle" << i << " Hits = " << analysisManager->GetH1(i)->entries()   << G4endl;
    // }

    //   G4int ind = (b5->GetN())+1;
    //   G4cout << " Anticoincidence triggers = " << analysisManager->GetH1(ind)->entries()   << G4endl;
  }
*/
  // G4cout << "Ntuple: " << analysisManager->GetNtuple(0)->IsEmpty() << G4endl;


    //  if ( analysisManager->GetH1(1) ) {
    // ...
    // }


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
