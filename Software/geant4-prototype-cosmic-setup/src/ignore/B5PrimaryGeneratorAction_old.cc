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
// $Id: B5PrimaryGeneratorAction.cc 77781 2013-11-28 07:54:07Z gcosmo $
//
/// \file B5PrimaryGeneratorAction.cc
/// \brief Implementation of the B5PrimaryGeneratorAction class

#include "B5PrimaryGeneratorAction.hh"
#include "B5DetectorConstruction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4GenericMessenger.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "Randomize.hh"

// #include "RooRealVar.h"
// #include "RooDataSet.h"
// #include "RooGenericPdf.h"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B5PrimaryGeneratorAction::B5PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0), fMessenger(0),
  fPositron(0), fMuon(0), fPion(0), fKaon(0), fProton(0),
  fMomentum(0.*MeV),
  // fMomentum(3000.*MeV),
  fSigmaMomentum(50.*MeV),
  fSigmaAngle(2.*deg),
  fRandomizePrimary(false)
{


  costheta_bins=50;
  energy_decades=6;
  energy_divisions=50;


  InitSamplePDG();



    G4int n_particle = 1;
    fParticleGun  = new G4ParticleGun(n_particle);

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    fPositron = particleTable->FindParticle(particleName="e+");
    fPion = particleTable->FindParticle(particleName="pi+");
    fKaon = particleTable->FindParticle(particleName="kaon+");
    fProton = particleTable->FindParticle(particleName="proton");

    // ~55% positive muons and ~45% negative (there should be dependence on energy)
    G4double randomNumber = G4UniformRand();
    if (randomNumber > 0.55) fMuon = particleTable->FindParticle(particleName="mu-");
    else fMuon = particleTable->FindParticle(particleName="mu+");

    // default particle kinematics
    fParticleGun->SetParticleDefinition(fMuon);

    // define commands for this class
    DefineCommands();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B5PrimaryGeneratorAction::~B5PrimaryGeneratorAction()
{
    delete fParticleGun;
    delete fMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// E in GeV
G4double B5PrimaryGeneratorAction::PDGCosmics(G4double cos_theta, G4double E)
{

  // Returns the PDG cosmic ray energy
  // G4double tmp_prefactor = 0.14*(pow(E,-2.7));
  G4double tmp_prefactor0 = 1 + 3.64/E/pow(cos_theta,1.9);// Check where this comes from (taken from Steve's code)...
  G4double tmp_prefactor = 0.14*pow(E*tmp_prefactor0,-2.7);
  G4double tmp_invfactor1 = 1.0+((1.1*E*cos_theta)/115.0);
  G4double tmp_invfactor2 = 1.0+((1.1*E*cos_theta)/850.0);

  return (tmp_prefactor*((1.0/tmp_invfactor1)+(0.054/tmp_invfactor2)));

}

void B5PrimaryGeneratorAction::InitSamplePDG()
{
  G4cout << "InitSamplePDG():Start " << G4endl;

  E_scale.clear();
  costheta_scale.clear();
  costhetap_scale.clear();
  cosmics_integral.clear();

  // Need to find d(cos_theta) and dE, first
  G4double p[5] = {0.102573,-0.068287, 0.958633, 0.0407253,0.817285};

  // Loop over the cos_theta bins
  G4double dcostheta = 1.0/((G4double) costheta_bins);

  for(int ith=0;ith<(int) costheta_bins;ith++){
    costheta_scale.push_back(-1+((G4double) ith)/((G4double) costheta_bins));

    G4double tmp0 = 1 + p[0]*p[0] + p[1] + p[3];
    G4double tmp1 = sqrt(pow(costheta_scale.at(ith),2.0) + p[0]*p[0] + p[1]*pow(abs(costheta_scale.at(ith)),p[2]) + p[3]*pow(abs(costheta_scale.at(ith)),p[4]));
    costhetap_scale.push_back(tmp0/tmp1);
  }

  //
  E_bins=energy_decades*energy_divisions;

  G4double dlogE = energy_decades/((G4double) E_bins);
  G4double minE=log10(0.01);

  for(int iE=0;iE<(int) E_bins;iE++){
    E_scale.push_back(((G4double) iE)*dlogE + minE);
  }

  std::vector<G4double> E_scale_tmp(E_scale.begin(),E_scale.end());
  E_scale_tmp.push_back(E_bins*dlogE+minE);

  cosmics_integral.clear();
  G4double iintegral=0;

  for(int ith=0;ith<(int) costheta_bins;ith++){
    for(int iE=0;iE<(int) E_bins;iE++){
      G4double result = PDGCosmics(costhetap_scale.at(ith), pow(10.0,E_scale.at(iE)));
      G4double dE = pow(10.0,E_scale_tmp.at(iE+1)) - pow(10.0,E_scale_tmp.at(iE));
      cosmics_integral.push_back(iintegral);
      iintegral+=(result*dcostheta*dE);
    }
  }
  cosmics_integral.push_back(iintegral);

  G4cout << "InitSamplePDG():End " << G4endl;
}

void B5PrimaryGeneratorAction::SamplePDGCosmics()
{

  // G4cout << "SamplePDGCosmics():Start " << G4endl;
  G4double r = G4UniformRand()*cosmics_integral.back();
  G4int nbins = cosmics_integral.size();
  G4int zz=0;
  G4int zu,zm,zl;
  zl=-1;
  zu=nbins;


  while((zu-zl)>1){
    zm=(zu+zl)>>1;

    // G4cout << "zu " << zu << " zl " << zl << " zm " << zm << G4endl;
    // G4cout << "zu-zl " << zu-zl << G4endl;
    // G4cout << "r " << r << " cosmics " << cosmics_integral.at(zm) << G4endl;

    if(r>=cosmics_integral.at(zm)){
      zl=zm;
    }else{
      zu=zm;
    }

  }

  if(r==cosmics_integral.at(0)){
    zz=0;
  }else if(r==cosmics_integral.at(nbins-1)){
    zz=nbins-2;
  }else{
    zz=zl;
  }

  // G4cout << "zz " << zz << G4endl;
  // G4cout << "zz " << zz%E_bins << G4endl;

  G4double dE = energy_decades/((G4double) E_bins);
  fEnergy=pow(10,3+E_scale.at(zz%E_bins)+G4UniformRand()*dE);// Also converts to MeV from GeV

  G4double dcostheta = 1.0/((G4double) costheta_bins);
  fTheta=pow(10,costheta_scale.at(zz/E_bins)+G4UniformRand()*dcostheta);

  // G4cout << "SamplePDGCosmics():End " << G4endl;

}


// void B5PrimaryGeneratorAction::SamplePDGCosmics(
// {


//   RooRealVar Energy("E", "E",0.01, 100);
//   RooRealVar Theta("theta", "theta", 0.1, (70.0/180.0)*3.14159);
//   RooGenericPdf PDGCosmic("PDGCosmic", "PDGCosmic","0.14*(pow(E,-2.7))*((1.0/(1+((1.1*E*cos(theta))/115)))+(0.054/(1+((1.1*E*cos(theta))/850))))", RooArgSet(Energy,Theta));

//   G4double this_energy = (G4double) ( (PDGCosmic.generate(RooArgSet(Energy,Theta),1))->get(0))->getRealValue("E");
//   G4double this_angle = (G4double) ( (PDGCosmic.generate(RooArgSet(Energy,Theta),1))->get(0))->getRealValue("theta");

//   // Get variables
//   fTheta = this_angle;
//   fParticleGun->SetParticleEnergy(this_energy*GeV);
//   fParticleGun->SetParticleMomentumDirection(G4ThreeVector(std::sin(fTheta),0.,std::cos(fTheta)));

//   G4cout << "Momentum " << this_energy << " Angle " << this_angle*(180/3.14159) << G4endl;


// }


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B5PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    G4ParticleDefinition* particle;

    if (fRandomizePrimary)
    {
        G4int i = (int)(5.*G4UniformRand());
        switch(i)
        {
            case 0:
                particle = fPositron;
                break;
            case 1:
                particle = fMuon;
                break;
            case 2:
                particle = fPion;
                break;
            case 3:
                particle = fKaon;
                break;
            default:
                particle = fProton;
                break;
        }
        fParticleGun->SetParticleDefinition(particle);
    }
    else
    {
        particle = fParticleGun->GetParticleDefinition();
    }


    // Get the first detector from the detector construction
    B5DetectorConstruction* b5 = (B5DetectorConstruction*) G4RunManager::GetRunManager()->GetUserDetectorConstruction();
    std::vector<G4ThreeVector> det_pos = b5->GetPositions();
    G4double sx = b5->GetSizeX();
    G4double sy = b5->GetSizeY();
    // G4double sz = b5->GetSizeZ();

    G4double x = det_pos.at(0).x() + (G4UniformRand()-0.5)*sx;
    G4double y = det_pos.at(0).y() + (G4UniformRand()-0.5)*sy;
    //    G4double z = det_pos.at(0).z() - 0.5*sz - 0.1*cm;
    G4double z = det_pos.at(0).z() - 10*cm;//- 0.5*sz - 0.1*cm;

    // G4cout << x << " " << y << " " << z << " " << sx << " " << sy << " " << sz << G4endl;

    fParticleGun->SetParticlePosition(G4ThreeVector(x,y,z));
    // G4cout << "mom " << fMomentum << G4endl;

    if(fMomentum>0){
      G4double pp = fMomentum;
      // G4double pp = fMomentum + (G4UniformRand()-0.5)*fSigmaMomentum;
      G4double mass = particle->GetPDGMass();
      G4double Ekin = std::sqrt(pp*pp+mass*mass)-mass;
      fParticleGun->SetParticleEnergy(Ekin);

      G4double angle = (G4UniformRand()-0.5)*fSigmaAngle;
      fTheta=angle;
      fParticleGun->SetParticleMomentumDirection(G4ThreeVector(std::sin(angle),0.,std::cos(angle)));
    }else{
      SamplePDGCosmics();
      // G4cout << "Energy     " << fEnergy << G4endl;

      G4double Ekin = fEnergy;
      fParticleGun->SetParticleEnergy(Ekin);
      fParticleGun->SetParticleMomentumDirection(G4ThreeVector(sqrt(1-(fTheta*fTheta)),0.,fTheta) );

    }

    fParticleGun->GeneratePrimaryVertex(event);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B5PrimaryGeneratorAction::DefineCommands()
{
    // Define /B5/generator command directory using generic messenger class
    fMessenger
      = new G4GenericMessenger(this,
                               "/B5/generator/",
                               "Primary generator control");

    // momentum command
    G4GenericMessenger::Command& momentumCmd
      = fMessenger->DeclarePropertyWithUnit("momentum", "GeV", fMomentum,
                                    "Mean momentum of primaries.");
    momentumCmd.SetParameterName("p", true);
    //    momentumCmd.SetRange("p>=0.");
    momentumCmd.SetDefaultValue("1.");
    // ok
    //momentumCmd.SetParameterName("p", true);
    //momentumCmd.SetRange("p>=0.");

    // sigmaMomentum command
    G4GenericMessenger::Command& sigmaMomentumCmd
      = fMessenger->DeclarePropertyWithUnit("sigmaMomentum",
          "MeV", fSigmaMomentum, "Sigma momentum of primaries.");
    sigmaMomentumCmd.SetParameterName("sp", true);
    sigmaMomentumCmd.SetRange("sp>=0.");
    sigmaMomentumCmd.SetDefaultValue("50.");

    // sigmaAngle command
    G4GenericMessenger::Command& sigmaAngleCmd
      = fMessenger->DeclarePropertyWithUnit("sigmaAngle", "deg", fSigmaAngle,
                                    "Sigma angle divergence of primaries.");
    sigmaAngleCmd.SetParameterName("t", true);
    sigmaAngleCmd.SetRange("t>=0.");
    sigmaAngleCmd.SetDefaultValue("2.");

    // randomizePrimary command
    G4GenericMessenger::Command& randomCmd
      = fMessenger->DeclareProperty("randomizePrimary", fRandomizePrimary);
    G4String guidance
       = "Boolean flag for randomizing primary particle types.\n";
    guidance
       += "In case this flag is false, you can select the primary particle\n";
    guidance += "  with /gun/particle command.";
    randomCmd.SetGuidance(guidance);
    randomCmd.SetParameterName("flg", true);
    randomCmd.SetDefaultValue("true");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
