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
// $Id: B5DetectorConstruction.hh 76474 2013-11-11 10:36:34Z gcosmo $
//
/// \file B5DetectorConstruction.hh
/// \brief Definition of the B5DetectorConstruction class

#ifndef B5DetectorConstruction_h
#define B5DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4RotationMatrix.hh"
#include "G4FieldManager.hh"
// #include "B5DetectorMessenger.hh"

#include <vector>

class B5MagneticField;

class G4VPhysicalVolume;
class G4Material;
class G4VSensitiveDetector;
class G4VisAttributes;
class G4GenericMessenger;

/// Detector construction

class B5DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    B5DetectorConstruction();
    // virtual ~B5DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
//    virtual void ConstructSDandField();

    void SetEfficiency(G4double val);
    G4double GetEfficiency(){
    return fEfficiency;
  }


    void SetArmAngle(G4double val);
    G4double GetArmAngle() { return fArmAngle; }

    void SetSizeX(G4double val);
    G4double GetSizeX() { return fsizex; }

    void SetSizeY(G4double val);
    G4double GetSizeY() { return fsizey; }

    void SetSizeZ(G4double val);
    G4double GetSizeZ() { return fsizez; }

    void SetPbZ(G4double val);
    G4double GetPbZ() { return fPbZ; }

    void SetUpperDetZ(G4double val);
    void SetMiddleDetZ(G4double val);
    void SetLowerDetZ(G4double val);

    G4double GetUpperDetZ(){return fPositions.at(0).z();}
    G4double GetMiddleDetZ(){return fPositions.at(1).z();}
    G4double GetLowerDetZ(){return fPositions.at(2).z();}

    void SetDetZ(G4double val, int det_choice);
    G4double GetDetZ() { return fDetZ; }

    void SetPbHeight(G4double val);
    G4double GetPbHeight() { return fPbHeight; }

    void SetN(G4int val);
    G4int GetN() { return fN; }

    std::vector<G4ThreeVector> GetPositions() { return fPositions; }

    void ConstructMaterials();

    // void SetBrickMaterialName( G4String mat ){ fBrickMatName = mat; }
    // void SetBrickMaterial( G4Material* mat ){ fBrickMat = mat; }
    // void SetBrickMaterial(G4String);
    // G4Material* GetBrickMaterial(){ return fBrickMat; }

private:
    void DefineCommands();

    G4GenericMessenger* fMessenger;
    G4GenericMessenger* fPaddleMessenger;

    static G4ThreadLocal B5MagneticField* fMagneticField;
    static G4ThreadLocal G4FieldManager* fFieldMgr;

    G4LogicalVolume* fWirePlane1Logical;
    G4LogicalVolume* fWirePlane2Logical;
    G4LogicalVolume* fCellLogical;
    G4LogicalVolume* fHadCalScintiLogical;
    G4LogicalVolume* fMagneticLogical;

    std::vector<G4VisAttributes*> fVisAttributes;

    G4double fArmAngle;
    G4RotationMatrix* fArmRotation;
    G4VPhysicalVolume* fSecondArmPhys;

    std::vector<G4LogicalVolume*> fPaddlesLogical;
    std::vector<G4VPhysicalVolume*> fPaddlesPhysical;

    G4double fEfficiency;
    G4double fsizex;
    G4double fsizey;
    G4double fsizez;
    G4double fPbZ;
    G4double fDetZ;



    G4LogicalVolume* fPbLogical;
    G4VPhysicalVolume* fPbPhysical;
    G4double fPbHeight;

    std::vector<G4ThreeVector> fPositions;

    G4int fN;// number of detectors

    // G4String fBrickMatName;
    // G4Material* fBrickMat;

    // B5DetectorMessenger* fDetMessenger;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
