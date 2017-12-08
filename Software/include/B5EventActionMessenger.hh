


#ifndef B5EventActionMessenger_h
#define B5EventActionMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class B5EventAction;
class G4UIcmdWithABool;
class G4UIdirectory;
// class G4UIcmdWithAString;
// class G4UIcmdWithoutParameter;
class G4UIcmdWithADoubleAndUnit;
// class G4UIcmdWithADouble;



class B5EventActionMessenger: public G4UImessenger
{
  public:
    B5EventActionMessenger(B5EventAction*);
   ~B5EventActionMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    B5EventAction*               Action;
    G4UIdirectory*               EventDir;
    G4UIcmdWithABool*            delays_onCmd;
    G4UIcmdWithABool*            use_mctruthCmd;
    G4UIcmdWithADoubleAndUnit*   mintimeCmd;
    G4UIcmdWithADoubleAndUnit*   minenergyCmd;

    // G4UIcmdWithAString*          FileCmd; 
    // G4UIcmdWithAString*          InputCmd;
    // G4UIcmdWithoutParameter*     UpdateCmd;
    // std::string* MessInput;
    // G4UIcmdWithADouble*          BeamOnCmd;
};


#endif
