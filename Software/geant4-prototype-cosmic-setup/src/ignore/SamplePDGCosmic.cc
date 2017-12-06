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

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooAddPdf.h"
#include "RooChebychev.h"
#include "RooFitResult.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
#include "TFile.h"
#include "TStyle.h"
#include "TH2.h"
#include "TH3.h"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
SamplePDGCosmics::SamplePDGCosmics(){

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
SamplePDGCosmics::~SamplePDGCosmics(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Theta in radians
// E in GeV
// G4double B5PrimaryGeneratorAction::SamplePDGCosmics(G4double theta, G4double E)
// {

//   // Returns the PDG cosmic ray energy 
//   G4double tmp_prefactor = 0.14*(E**-2.7);
//   G4double tmp_invfactor1 = 1+((1.1*E*cos(theta))/115);
//   G4double tmp_invfactor2 = 1+((1.1*E*cos(theta))/850);

//   return (tmp_prefactor*((1.0/tmp_invfactor1)+(0.054/tmp_invfactor2)));

// }

void SamplePDGCosmics::()
{

  // Create a new workspace (not needed?)
  RooWorkspace* w = new RooWorkspace("myWS");
  w->factory("EXPR::PDGCosmics('0.14*(E**-2.7)*((1.0/(1+((1.1*E*cos(theta))/115)))+(0.054/(1+((1.1*E*cos(theta))/850))))',E[0.1,100],theta[0,1.22]");
  RooFit::RooDataSet* data = (w->pdf("PDGCosmics"))->generate(1);
  

  // Get variables
  fTheta = data->get(0)->getRealValue("theta");
  fParticleGun->SetParticleEnergy((data->get(0)->getRealValue("E"))*GeV);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(std::sin(fTheta),0.,std::cos(fTheta)));

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
