


#include "B5EventActionMessenger.hh"

#include "B5EventAction.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"
// #include "G4UIcmdWithAString.hh"
// #include "G4UIcmdWithoutParameter.hh"
// #include "G4UIcmdWithADouble.hh"
#include "G4UIcommand.hh"
#include "G4SystemOfUnits.hh"

B5EventActionMessenger::B5EventActionMessenger(
                                          B5EventAction* EvtAction)
  :Action(EvtAction)
{
	EventDir = new G4UIdirectory("/event/");
  	EventDir->SetGuidance("EventAction commands.");

	delays_onCmd = new G4UIcmdWithABool("/event/delays_on",this);
	delays_onCmd->SetGuidance("Use time delay.");
	delays_onCmd->SetParameterName("delays",true);
	delays_onCmd->SetDefaultValue(false);
	delays_onCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

	use_mctruthCmd = new G4UIcmdWithABool("/event/use_mctruth",this);
	use_mctruthCmd->SetGuidance("Use MC truth (otherwise, trigger on time).");
	use_mctruthCmd->SetParameterName("MCTruth",true);
	use_mctruthCmd->SetDefaultValue(false);
	// use_mctruthCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

	mintimeCmd = new G4UIcmdWithADoubleAndUnit("/event/mintime",this);
	mintimeCmd->SetGuidance("Minimum time before trigger.");
	mintimeCmd->SetParameterName("MinTime",true);
	mintimeCmd->SetDefaultValue(3*ns);
	// mintimeCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

	minenergyCmd = new G4UIcmdWithADoubleAndUnit("/event/minenergy",this);
	minenergyCmd->SetGuidance("Minimum energy deposited to trigger.");
	minenergyCmd->SetParameterName("MinEnergy",true);
	minenergyCmd->SetDefaultValue(0*keV);
	// minenergyCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

B5EventActionMessenger::~B5EventActionMessenger()
{
  	delete EventDir;
	delete delays_onCmd;
	delete use_mctruthCmd;
	delete mintimeCmd;
	delete minenergyCmd;
}

void B5EventActionMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
	if( command == delays_onCmd )
	{ 
		// Action->SetDelaysBool(G4UIcommand::ConvertToBool(newValue));
		Action->SetDelaysBool(delays_onCmd->GetNewBoolValue(newValue));
	}

	if( command == use_mctruthCmd )
	{ 
		Action->SetMCTruthBool(G4UIcommand::ConvertToBool(newValue));
	}

	if( command == mintimeCmd )
	{
		Action->SetMinTime(G4UIcommand::ConvertToDouble(newValue));
	}

	if( command == minenergyCmd )
	{
		Action->SetMinEnergy(G4UIcommand::ConvertToDouble(newValue));
	}

}
