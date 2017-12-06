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

        ScintillatorPaddle* get_scintillator_paddle(){return detector0;}


        std::vector<ScintillatorPaddle*> detectors;
        ScintillatorPaddle* detector0;
        ScintillatorPaddle* detector1;

    protected:

    private:

};

#endif // DETECTORCONSTRUCTION_H
