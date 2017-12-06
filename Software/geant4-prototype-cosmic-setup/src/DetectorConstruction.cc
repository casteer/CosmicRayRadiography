#include "DetectorConstruction.hh"

#include "G4VUserDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"

#include "ScintillatorSD.hh"
#include "ScintillatorPaddle.hh"

DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction()
{
    //ctor
}

DetectorConstruction::~DetectorConstruction()
{
    //dtor
}


G4VPhysicalVolume* DetectorConstruction::Construct(){

    G4bool checkOverlaps = true;


    // Create the materials
    G4NistManager* nistManager = G4NistManager::Instance();
    nistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    nistManager->FindOrBuildMaterial("G4_AIR");
    nistManager->FindOrBuildMaterial("G4_CONCRETE");

    // Get the materials
    G4Material* scintillator = G4Material::GetMaterial("G4_PLASTIC_SC_VINYLTOLUENE"); // density 1.032*g/cm^3
    G4Material* air = G4Material::GetMaterial("G4_AIR");
    G4Material* concrete = G4Material::GetMaterial("G4_CONCRETE");

    // Create a 10m by 10m by 1m world box
   G4VSolid* worldSolid = new G4Box("worldBox",6.*m,6.*m,0.6*m);

   // And a logical box
   G4LogicalVolume* worldLogical = new G4LogicalVolume(worldSolid,air,"worldLogical");

   // And a physical box
    G4VPhysicalVolume* worldPhysical = new G4PVPlacement(0,G4ThreeVector(0,0,0),worldLogical,"worldPhysical",0,false,100,checkOverlaps);

/*    // Create a wall box
   G4VSolid* wallSolid = new G4Box("wall",10.*cm,2.8*m,2.8*m);
   // And a logical box
   G4LogicalVolume* wallLogical = new G4LogicalVolume(wallSolid,concrete,"wallLogical");
   // And a physical box
    G4VPhysicalVolume* wallPhysical = new G4PVPlacement(0,G4ThreeVector(0.8*m,0,0),wallLogical,"wallPhysical",worldLogical,false,101,checkOverlaps);
*/
    // Create a detector
  //  for(int i=0;i<6;i++){
   //     detectors.push_back(new ScintillatorPaddle("paddle0",(G4int) 0,scintillator));
   // }

    detector00 = new ScintillatorPaddle("paddle00",(G4int) 0,scintillator);
    detector00->set_dimensions(G4ThreeVector(2.5*cm,80.*cm,15.*cm));
    detector00->set_position(G4ThreeVector(-0.6*m,0.0,0.0));
    worldPhysical = detector00->Construct(worldPhysical);

    detector01 = new ScintillatorPaddle("paddle01",(G4int) 1,scintillator);
    detector01->set_dimensions(G4ThreeVector(2.5*cm,80.*cm,15.*cm));
    detector01->set_position(G4ThreeVector(-0.6*m,0.0,15.1*cm));
    worldPhysical = detector01->Construct(worldPhysical);

    detector02 = new ScintillatorPaddle("paddle02",(G4int) 2,scintillator);
    detector02->set_dimensions(G4ThreeVector(2.5*cm,80.*cm,15.*cm));
    detector02->set_position(G4ThreeVector(-0.6*m,0.0,30.2*cm));
    worldPhysical = detector02->Construct(worldPhysical);

    detector03 = new ScintillatorPaddle("paddle03",(G4int) 3,scintillator);
    detector03->set_dimensions(G4ThreeVector(2.5*cm,80.*cm,15.*cm));
    detector03->set_position(G4ThreeVector(-0.6*m,0.0,45.3*cm));
    worldPhysical = detector03->Construct(worldPhysical);

    detector04 = new ScintillatorPaddle("paddle04",(G4int) 4,scintillator);
    detector04->set_dimensions(G4ThreeVector(2.5*cm,80.*cm,15.*cm));
    detector04->set_position(G4ThreeVector(-0.6*m,0.0,60.4*cm));
    worldPhysical = detector04->Construct(worldPhysical);

    detector05 = new ScintillatorPaddle("paddle05",(G4int) 5,scintillator);
    detector05->set_dimensions(G4ThreeVector(2.5*cm,80.*cm,15.*cm));
    detector05->set_position(G4ThreeVector(-0.6*m,0.0,75.5*cm));
    worldPhysical = detector05->Construct(worldPhysical);


    detector10 = new ScintillatorPaddle("paddle10",(G4int) 6,scintillator);
    detector10->set_dimensions(G4ThreeVector(2.5*cm,80.*cm,15.*cm));
    detector10->set_position(G4ThreeVector(-0.6*m,0.0,0.0));
    worldPhysical = detector10->Construct(worldPhysical);

    detector11 = new ScintillatorPaddle("paddle11",(G4int) 7,scintillator);
    detector11->set_dimensions(G4ThreeVector(2.5*cm,80.*cm,15.*cm));
    detector11->set_position(G4ThreeVector(-0.6*m,0.0,15.1*cm));
    worldPhysical = detector11->Construct(worldPhysical);

    detector12 = new ScintillatorPaddle("paddle12",(G4int) 8,scintillator);
    detector12->set_dimensions(G4ThreeVector(2.5*cm,80.*cm,15.*cm));
    detector12->set_position(G4ThreeVector(-0.6*m,0.0,30.2*cm));
    worldPhysical = detector12->Construct(worldPhysical);

    detector13 = new ScintillatorPaddle("paddle13",(G4int) 9,scintillator);
    detector13->set_dimensions(G4ThreeVector(2.5*cm,80.*cm,15.*cm));
    detector13->set_position(G4ThreeVector(-0.6*m,0.0,45.3*cm));
    worldPhysical = detector13->Construct(worldPhysical);

    detector14 = new ScintillatorPaddle("paddle14",(G4int) 10,scintillator);
    detector14->set_dimensions(G4ThreeVector(2.5*cm,80.*cm,15.*cm));
    detector14->set_position(G4ThreeVector(-0.6*m,0.0,60.4*cm));
    worldPhysical = detector14->Construct(worldPhysical);

    detector15 = new ScintillatorPaddle("paddle15",(G4int) 5,scintillator);
    detector15->set_dimensions(G4ThreeVector(2.5*cm,80.*cm,15.*cm));
    detector15->set_position(G4ThreeVector(-0.6*m,0.0,75.5*cm));
    worldPhysical = detector15->Construct(worldPhysical);


    // Create a detector
/*    detector1 = new ScintillatorPaddle("paddle1",(G4int) 1,scintillator);
    detector1->set_dimensions(G4ThreeVector(2.5*cm,80*cm,6.0*15.*cm));
    detector1->set_position(G4ThreeVector(0.6*m,0.0,0.0));
    worldPhysical = detector1->Construct(worldPhysical);
*/



   return worldPhysical;

}

void DetectorConstruction::ConstructSDandField()
{

// Create the sensitive detector
    ScintillatorSD* sensitive_detector0 = new ScintillatorSD(detector0->get_sensitive_name(), "TrackerHitsCollection0");
    ScintillatorSD* sensitive_detector1 = new ScintillatorSD(detector1->get_sensitive_name(), "TrackerHitsCollection1");

 // Make this detector sensitive
    G4SDManager* SDman = G4SDManager::GetSDMpointer();

    SDman->AddNewDetector(sensitive_detector0);
    SetSensitiveDetector(detector0->get_logical_volume(),sensitive_detector0);

    SDman->AddNewDetector(sensitive_detector1);
    SetSensitiveDetector(detector1->get_logical_volume(),sensitive_detector1);


}
