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
   G4VSolid* worldSolid = new G4Box("worldBox",6.*m,6.*m,1.0*m);

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

    detector00 = new ScintillatorPaddle("paddle00",(G4int) 1,scintillator);
    detector00->set_dimensions(G4ThreeVector(2.5*cm,80.*cm,15.*cm));
    detector00->set_position(G4ThreeVector(-0.6*m,0.0,0.0));
    worldPhysical = detector00->Construct(worldPhysical);

    detector01 = new ScintillatorPaddle("paddle01",(G4int) 2,scintillator);
    detector01->set_dimensions(G4ThreeVector(2.5*cm,80.*cm,15.*cm));
    detector01->set_position(G4ThreeVector(-0.6*m,0.0,15.1*cm));
    worldPhysical = detector01->Construct(worldPhysical);

    detector02 = new ScintillatorPaddle("paddle02",(G4int) 3,scintillator);
    detector02->set_dimensions(G4ThreeVector(2.5*cm,80.*cm,15.*cm));
    detector02->set_position(G4ThreeVector(-0.6*m,0.0,30.2*cm));
    worldPhysical = detector02->Construct(worldPhysical);

    detector03 = new ScintillatorPaddle("paddle03",(G4int) 4,scintillator);
    detector03->set_dimensions(G4ThreeVector(2.5*cm,80.*cm,15.*cm));
    detector03->set_position(G4ThreeVector(-0.6*m,0.0,45.3*cm));
    worldPhysical = detector03->Construct(worldPhysical);

    detector04 = new ScintillatorPaddle("paddle04",(G4int) 5,scintillator);
    detector04->set_dimensions(G4ThreeVector(2.5*cm,80.*cm,15.*cm));
    detector04->set_position(G4ThreeVector(-0.6*m,0.0,60.4*cm));
    worldPhysical = detector04->Construct(worldPhysical);

    detector05 = new ScintillatorPaddle("paddle05",(G4int) 6,scintillator);
    detector05->set_dimensions(G4ThreeVector(2.5*cm,80.*cm,15.*cm));
    detector05->set_position(G4ThreeVector(-0.6*m,0.0,75.5*cm));
    worldPhysical = detector05->Construct(worldPhysical);

    detector10 = new ScintillatorPaddle("paddle10",(G4int) 7,scintillator);
    detector10->set_dimensions(G4ThreeVector(2.5*cm,80.*cm,15.*cm));
    detector10->set_position(G4ThreeVector(0.6*m,0.0,0.0));
    worldPhysical = detector10->Construct(worldPhysical);

    detector11 = new ScintillatorPaddle("paddle11",(G4int) 8,scintillator);
    detector11->set_dimensions(G4ThreeVector(2.5*cm,80.*cm,15.*cm));
    detector11->set_position(G4ThreeVector(0.6*m,0.0,15.1*cm));
    worldPhysical = detector11->Construct(worldPhysical);

    detector12 = new ScintillatorPaddle("paddle12",(G4int) 9,scintillator);
    detector12->set_dimensions(G4ThreeVector(2.5*cm,80.*cm,15.*cm));
    detector12->set_position(G4ThreeVector(0.6*m,0.0,30.2*cm));
    worldPhysical = detector12->Construct(worldPhysical);

    detector13 = new ScintillatorPaddle("paddle13",(G4int) 10,scintillator);
    detector13->set_dimensions(G4ThreeVector(2.5*cm,80.*cm,15.*cm));
    detector13->set_position(G4ThreeVector(0.6*m,0.0,45.3*cm));
    worldPhysical = detector13->Construct(worldPhysical);

    detector14 = new ScintillatorPaddle("paddle14",(G4int) 11,scintillator);
    detector14->set_dimensions(G4ThreeVector(2.5*cm,80.*cm,15.*cm));
    detector14->set_position(G4ThreeVector(0.6*m,0.0,60.4*cm));
    worldPhysical = detector14->Construct(worldPhysical);

    detector15 = new ScintillatorPaddle("paddle15",(G4int) 12,scintillator);
    detector15->set_dimensions(G4ThreeVector(2.5*cm,80.*cm,15.*cm));
    detector15->set_position(G4ThreeVector(0.6*m,0.0,75.5*cm));
    worldPhysical = detector15->Construct(worldPhysical);


   return worldPhysical;

}

void DetectorConstruction::ConstructSDandField()
{

    // Create the sensitive detector - should insert these into a STL vector
    ScintillatorSD* sensitive_detector00 = new ScintillatorSD(detector00->get_sensitive_name(), "TrackerHitsCollection00");
    ScintillatorSD* sensitive_detector10 = new ScintillatorSD(detector10->get_sensitive_name(), "TrackerHitsCollection10");
    ScintillatorSD* sensitive_detector01 = new ScintillatorSD(detector01->get_sensitive_name(), "TrackerHitsCollection01");
    ScintillatorSD* sensitive_detector11 = new ScintillatorSD(detector11->get_sensitive_name(), "TrackerHitsCollection11");
    ScintillatorSD* sensitive_detector02 = new ScintillatorSD(detector02->get_sensitive_name(), "TrackerHitsCollection02");
    ScintillatorSD* sensitive_detector12 = new ScintillatorSD(detector12->get_sensitive_name(), "TrackerHitsCollection12");
    ScintillatorSD* sensitive_detector03 = new ScintillatorSD(detector03->get_sensitive_name(), "TrackerHitsCollection03");
    ScintillatorSD* sensitive_detector13 = new ScintillatorSD(detector13->get_sensitive_name(), "TrackerHitsCollection13");
    ScintillatorSD* sensitive_detector04 = new ScintillatorSD(detector04->get_sensitive_name(), "TrackerHitsCollection04");
    ScintillatorSD* sensitive_detector14 = new ScintillatorSD(detector14->get_sensitive_name(), "TrackerHitsCollection14");
    ScintillatorSD* sensitive_detector05 = new ScintillatorSD(detector05->get_sensitive_name(), "TrackerHitsCollection05");
    ScintillatorSD* sensitive_detector15 = new ScintillatorSD(detector15->get_sensitive_name(), "TrackerHitsCollection15");

    // Make this detector sensitive
    G4SDManager* SDman = G4SDManager::GetSDMpointer();

    SDman->AddNewDetector(sensitive_detector00);
    SetSensitiveDetector(detector00->get_logical_volume(),sensitive_detector00);
    SDman->AddNewDetector(sensitive_detector10);
    SetSensitiveDetector(detector10->get_logical_volume(),sensitive_detector10);

    SDman->AddNewDetector(sensitive_detector11);
    SetSensitiveDetector(detector11->get_logical_volume(),sensitive_detector11);
    SDman->AddNewDetector(sensitive_detector01);
    SetSensitiveDetector(detector01->get_logical_volume(),sensitive_detector01);

    SDman->AddNewDetector(sensitive_detector12);
    SetSensitiveDetector(detector12->get_logical_volume(),sensitive_detector12);
    SDman->AddNewDetector(sensitive_detector02);
    SetSensitiveDetector(detector02->get_logical_volume(),sensitive_detector02);

    SDman->AddNewDetector(sensitive_detector13);
    SetSensitiveDetector(detector13->get_logical_volume(),sensitive_detector13);
    SDman->AddNewDetector(sensitive_detector03);
    SetSensitiveDetector(detector03->get_logical_volume(),sensitive_detector03);

    SDman->AddNewDetector(sensitive_detector14);
    SetSensitiveDetector(detector14->get_logical_volume(),sensitive_detector14);
    SDman->AddNewDetector(sensitive_detector04);
    SetSensitiveDetector(detector04->get_logical_volume(),sensitive_detector04);

    SDman->AddNewDetector(sensitive_detector05);
    SetSensitiveDetector(detector05->get_logical_volume(),sensitive_detector05);
    SDman->AddNewDetector(sensitive_detector15);
    SetSensitiveDetector(detector15->get_logical_volume(),sensitive_detector15);


}
