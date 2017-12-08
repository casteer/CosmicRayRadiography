#ifndef DETECTORCONSTRUCTION_H
#define DETECTORCONSTRUCTION_H


#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "ScintillatorPaddle.hh"

class G4VPhysicalVolume;
class G4Material;
class G4VSensitiveDetector;
class G4VisAttributes;
class G4GenericMessenger;

class DetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        DetectorConstruction();
        virtual ~DetectorConstruction();

        virtual G4VPhysicalVolume* Construct();
        void ConstructSDandField();

        // ScintillatorPaddle* get_scintillator_paddle(){return detector0;}
        std::vector<ScintillatorPaddle*> detectors;

        ScintillatorPaddle* detector00;
        ScintillatorPaddle* detector10;
        ScintillatorPaddle* detector01;
        ScintillatorPaddle* detector11;
        ScintillatorPaddle* detector02;
        ScintillatorPaddle* detector12;
        ScintillatorPaddle* detector03;
        ScintillatorPaddle* detector13;
        ScintillatorPaddle* detector04;
        ScintillatorPaddle* detector14;
        ScintillatorPaddle* detector05;
        ScintillatorPaddle* detector15;

    protected:

    private:

};

#endif // DETECTORCONSTRUCTION_H
