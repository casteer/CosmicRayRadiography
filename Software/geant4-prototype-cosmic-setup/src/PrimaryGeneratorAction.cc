//******************************************************************************
// PrimaryGeneratorAction.cc
//
// 1.00 JMV, LLNL, Jan-2007:  First version.
//******************************************************************************
//

#include <iomanip>
#include "PrimaryGeneratorAction.hh"
using namespace std;

#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "DetectorConstruction.hh"
#include "G4RunManager.hh"

//----------------------------------------------------------------------------//
PrimaryGeneratorAction::PrimaryGeneratorAction(const char *inputfile)
{

  // Read the cry input file
  std::ifstream inputFile;
  inputFile.open(inputfile,std::ios::in);
  char buffer[1000];

  if (inputFile.fail()) {
    if( *inputfile !=0)  //....only complain if a filename was given
      G4cout << "PrimaryGeneratorAction: Failed to open CRY input file= " << inputfile << G4endl;
    InputState=-1;
  }else{
    std::string setupString("");
    while ( !inputFile.getline(buffer,1000).eof()) {
      setupString.append(buffer);
      setupString.append(" ");
    }

    CRYSetup *setup=new CRYSetup(setupString,"./data");

    gen = new CRYGenerator(setup);

    // set random number generator
    RNGWrapper<CLHEP::HepRandomEngine>::set(CLHEP::HepRandom::getTheEngine(),&CLHEP::HepRandomEngine::flat);
    setup->setRandomFunction(RNGWrapper<CLHEP::HepRandomEngine>::rng);
    InputState=0;
  }

  // define a particle gun
  particleGun = new G4ParticleGun();

  // create a vector to store the CRY particle properties
  vect=new std::vector<CRYParticle*>;

  // Create the table containing all particle names
  particleTable = G4ParticleTable::GetParticleTable();

  // Create the messenger file
  gunMessenger = new PrimaryGeneratorMessenger(this);
}

//----------------------------------------------------------------------------//
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    //delete particleGun;
    //delete vect;
}



//----------------------------------------------------------------------------//
void PrimaryGeneratorAction::InputCRY()
{
  InputState=1;
}

//----------------------------------------------------------------------------//
void PrimaryGeneratorAction::UpdateCRY(std::string* MessInput)
{
  CRYSetup *setup=new CRYSetup(*MessInput,"./data");

  gen = new CRYGenerator(setup);

  // set random number generator
  RNGWrapper<CLHEP::HepRandomEngine>::set(CLHEP::HepRandom::getTheEngine(),&CLHEP::HepRandomEngine::flat);
  setup->setRandomFunction(RNGWrapper<CLHEP::HepRandomEngine>::rng);
  InputState=0;

}

//----------------------------------------------------------------------------//
void PrimaryGeneratorAction::CRYFromFile(G4String newValue)
{
  // Read the cry input file
  std::ifstream inputFile;
  inputFile.open(newValue,std::ios::in);
  char buffer[1000];

  if (inputFile.fail()) {
    G4cout << "Failed to open input file " << newValue << G4endl;
    G4cout << "Make sure to define the cry library on the command line" << G4endl;
    InputState=-1;
  }else{
    std::string setupString("");
    while ( !inputFile.getline(buffer,1000).eof()) {
      setupString.append(buffer);
      setupString.append(" ");
    }

    CRYSetup *setup=new CRYSetup(setupString,"./data");

    gen = new CRYGenerator(setup);

  // set random number generator
    RNGWrapper<CLHEP::HepRandomEngine>::set(CLHEP::HepRandom::getTheEngine(),&CLHEP::HepRandomEngine::flat);
    setup->setRandomFunction(RNGWrapper<CLHEP::HepRandomEngine>::rng);
    InputState=0;
  }
}

void PrimaryGeneratorAction::MakePrimaries(G4ThreeVector offset, G4int verbose){

    vect->erase(vect->begin(),vect->end());

    if (InputState != 0) {
      G4String* str = new G4String("CRY library was not successfully initialized");
      //G4Exception(*str);
      G4Exception("PrimaryGeneratorAction", "1",
                  RunMustBeAborted, *str);
    }
    G4String particleName;
    gen->genEvent(vect);

    //....debug output
    if(verbose>1){
        G4cout << " - CRY generated nparticles=" << vect->size()
            << G4endl;
    }

    unsigned int n = vect->size();
    for ( unsigned j=0; j<n; j++) {

        if(verbose>2)
        {
            particleName=CRYUtils::partName((*vect)[j]->id());
            G4cout << "  "          << particleName << " "
            << "charge="      << (*vect)[j]->charge() << " "
            << setprecision(4)
            << "energy (MeV)=" << (*vect)[j]->ke()*MeV << " "
            << "pos (m)"
            << G4ThreeVector((*vect)[j]->x(), (*vect)[j]->y(), (*vect)[j]->z())
            << " " << "direction cosines "
            << G4ThreeVector((*vect)[j]->u(), (*vect)[j]->v(), (*vect)[j]->w())
            << " " << G4endl;
           }

      CRY_particle_id.push_back((*vect)[j]->PDGid());
      CRY_energy.push_back((*vect)[j]->ke()*MeV);
      G4ThreeVector p( (*vect)[j]->x()*m, (*vect)[j]->y()*m, (*vect)[j]->z()*m);
      p+=offset;
      CRY_position.push_back(p);
      G4ThreeVector mom_dir((*vect)[j]->u(), (*vect)[j]->v(), (*vect)[j]->w());
      CRY_direction.push_back(mom_dir);
      CRY_time.push_back((*vect)[j]->t());

      //particleGun->SetParticleEnergy((*vect)[j]->ke()*MeV);
      //particleGun->SetParticleDefinition(particleTable->FindParticle((*vect)[j]->PDGid()));
      // particleGun->SetParticlePosition(p);
      //particleGun->SetParticleMomentumDirection(v);
      //particleGun->SetParticleTime();
      //particleGun->GeneratePrimaryVertex(anEvent);

    }

    //for ( unsigned j=0; j<n; j++) delete (*vect)[j];

}


//----------------------------------------------------------------------------//
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  if (InputState != 0) {
    G4String* str = new G4String("CRY library was not successfully initialized");
    //G4Exception(*str);
    G4Exception("PrimaryGeneratorAction", "1",
                RunMustBeAborted, *str);
  }

  G4int verbose = 0;


  // Check the intersection with the detector box
  G4Box b0 = G4Box("targetbox",0.75*m,0.5*m,0.45*m);
  G4ThreeVector box_pos(0,0,0*m);
  G4ThreeVector offset(0,0,0.5*m);

  bool stopped=false;
  do{

      if(verbose>1) G4cout << " Creating new event... " << G4endl;

      if(verbose>2) G4cout << " Sampling distributions... " << G4endl;
      MakePrimaries(offset,verbose);
      if(verbose>2) G4cout << " End Sampling distributions... " << G4endl;


      G4int nparticles = (G4int) CRY_position.size();

      for(G4int iparticle=0;iparticle<nparticles; iparticle++){

        if(verbose>2) G4cout << " Finding particle " << iparticle << " of " << nparticles << G4endl;

          // Is the particle heading towards the centre of the geometry?
          G4ThreeVector p = CRY_position.at(iparticle);
          if(verbose>2) G4cout << " Primary Vertex Position = " << p/m << G4endl;
          G4ThreeVector v = CRY_direction.at(iparticle);
          G4double d0 = b0.DistanceToIn(p,v);
          if(verbose>2) G4cout << " DistanceToIn = " << d0 << G4endl;

          if(d0<kInfinity)
          {
              particleGun->SetParticleEnergy(CRY_energy.at(iparticle));
              particleGun->SetParticleDefinition(particleTable->FindParticle(CRY_particle_id.at(iparticle)));
              particleGun->SetParticlePosition(CRY_position.at(iparticle));
              particleGun->SetParticleMomentumDirection(CRY_direction.at(iparticle));
              particleGun->SetParticleTime(CRY_time.at(iparticle));
              particleGun->GeneratePrimaryVertex(anEvent);
              //if(verbose) G4cout << " Intersection, running event" << G4endl;
              stopped=true;

             /* G4cout << " ParticleGun : " << G4endl;
              G4cout << "  - Definition: " << particleGun->GetParticleDefinition()->GetParticleName() << G4endl;
              G4cout << "  - Energy : " << particleGun->GetParticleEnergy() << G4endl;
              G4cout << "  - Position : " << particleGun->GetParticlePosition() << G4endl;
              G4cout << "  - Direction : " << particleGun->GetParticleMomentumDirection() << G4endl;
              G4cout << "  - Time : " << particleGun->GetParticleTime() << G4endl;
              */
          }

      }// End of loop

//      G4cout << " ParticleGun : " << G4endl;
      //    G4cout << "  - Definition: " << particleGun->GetParticleDefinition()->GetParticleName() << G4endl;
      //    G4cout << "  - Energy : " << particleGun->GetParticleEnergy() << G4endl;
      //    G4cout << "  - Direction : " << particleGun->GetParticleMomentumDirection() << G4endl;
      //    G4cout << "  - Time : " << particleGun->GetParticleTime() << G4endl;

      // Clear all of the CRY particle information
      CRY_energy.clear();
      CRY_position.clear();
      CRY_time.clear();
      CRY_direction.clear();
      CRY_particle_id.clear();

  } while(!stopped);

 // if(anEvent->GetEventID()%1000==0) G4cout << " - Running Event " << anEvent->GetEventID() << G4endl;

  return;



}
