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
// $Id: B5EventAction.cc 87359 2014-12-01 16:04:27Z gcosmo $
//
/// \file B5EventAction.cc
/// \brief Implementation of the B5EventAction class

#include "B5EventAction.hh"
#include "ScintillatorHit.hh"
//#include "B5DriftChamberHit.hh"
//#include "DetectorConstruction.hh"
//#include "B5EmCalorimeterHit.hh"
//#include "B5HadCalorimeterHit.hh"
#include "B5Analysis.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include "Randomize.hh"
#include <math.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B5EventAction::B5EventAction() : G4UserEventAction()
{
  // set printing per each event
  G4RunManager::GetRunManager()->SetPrintProgress(10000);

  // Create the messenger file
  EvtMessenger = new B5EventActionMessenger(this);

 // analysed_events=0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B5EventAction::~B5EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B5EventAction::BeginOfEventAction(const G4Event* event)
{


//      B5DetectorConstruction* b5 = (B5DetectorConstruction*) G4RunManager::GetRunManager()->GetUserDetectorConstruction();
      // G4cout << "Event " << (int) b5->GetN() << G4endl;

//      fHH.clear();

//	G4cout << "HELLO!!!! " << b5->GetN() << G4endl;

//    for(int i=0;i<(int) b5->GetN();i++){
//
//      char char_sdname[20];
//      sprintf(char_sdname,"paddles1/det%d",i);
//      G4String sdname(char_sdname);
//
//      fHH.push_back(sdManager->GetCollectionID(sdname));
//
//    }

      // fHHC1ID = sdManager->GetCollectionID("paddle0/hodoscopeColl");
      // fHHC2ID = sdManager->GetCollectionID("paddle1/hodoscopeColl");
      // fHHC3ID = sdManager->GetCollectionID("paddle2/hodoscopeColl");

      // fDHC1ID = sdManager->GetCollectionID("chamber1/driftChamberColl");
      // fDHC2ID = sdManager->GetCollectionID("chamber2/driftChamberColl");
      // fECHCID = sdManager->GetCollectionID("EMcalorimeter/EMcalorimeterColl");
      // fHCHCID = sdManager->GetCollectionID("HadCalorimeter/HadCalorimeterColl");

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B5EventAction::EndOfEventAction(const G4Event* event)
{

    ScintillatorHitsCollection* h0 = (ScintillatorHitsCollection*) event->GetHCofThisEvent()->GetHC(0);

    ScintillatorHitsCollection* h1 = (ScintillatorHitsCollection*) event->GetHCofThisEvent()->GetHC(1);


    if (!h0 || !h1)
    {
        G4ExceptionDescription msg;
        msg << "No hits collection of this event found." << G4endl;
        G4Exception("B5EventAction::EndOfEventAction()",
                    "B5Code001", JustWarning, msg);
        return;
    }

    // Get analysis manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();



    //G4cout << "    " << hc->GetSize() << " hits stored in this event" << G4endl;
    G4double Etot0=0;
    G4double tav0=0;
    G4double theta_xz_av0 = 0;
    G4double theta_yz_av0 = 0;
    int nhits = (int)  h0->GetSize();
    for(int ihit=0;ihit<nhits; ihit++){
       // if(((*h0)[ihit]->GetParticlePDGEncoding()==13)||((*h0)[ihit]->GetParticlePDGEncoding()==-13)){
            Etot0+=(*h0)[ihit]->GetEdep()/MeV;
            tav0+=(*h0)[ihit]->GetTime()/ns;

            // Calculate the projected angle of incidence
            theta_xz_av0 += (*h0)[ihit]->GetThetaXZ();
            theta_yz_av0 += (*h0)[ihit]->GetThetaYZ();

        //}
    }
    tav0 /= ((G4double) h0->GetSize());
    theta_xz_av0 /= nhits;
    theta_yz_av0 /= nhits;

    G4double Etot1=0;
    G4double tav1=0;
    G4double theta_xz_av1 = 0;
    G4double theta_yz_av1 = 0;
    for(int ihit=0;ihit<(int)  h1->GetSize(); ihit++){
        //if(((*h1)[ihit]->GetParticlePDGEncoding()==13)||((*h1)[ihit]->GetParticlePDGEncoding()==-13)){
            Etot1+=(*h1)[ihit]->GetEdep()/MeV;
            tav1+=(*h1)[ihit]->GetTime()/ns;
            // Calculate the projected angle of incidence
            theta_xz_av1 += (*h1)[ihit]->GetThetaXZ();
            theta_yz_av1 += (*h1)[ihit]->GetThetaYZ();
        //}
    }
    tav1 /= ((G4double) h0->GetSize());
    theta_xz_av1 /= nhits;
    theta_yz_av1 /= nhits;


    if((Etot1>0.0)&&(Etot0>0.0)) {
        //analysed_events++;

        analysisManager->FillH1(0,Etot0);
        analysisManager->FillH1(1,Etot1);
        analysisManager->FillH1(2,tav1-tav0);
        analysisManager->FillH1(3,(theta_xz_av0));
        analysisManager->FillH1(4,(theta_xz_av1));

        analysisManager->FillH2(0,tav1-tav0,Etot0);
        analysisManager->FillH2(1,tav1-tav0,Etot1);

        analysisManager->FillH2(2,1.0/std::cos(theta_xz_av0),Etot0);
        analysisManager->FillH2(3,1.0/std::cos(theta_xz_av1),Etot1);

        analysisManager->FillNtupleDColumn(0,event->GetEventID());
        analysisManager->FillNtupleDColumn(1,Etot0);
        analysisManager->FillNtupleDColumn(2,tav0);
        analysisManager->FillNtupleDColumn(3,Etot1);
        analysisManager->FillNtupleDColumn(4,tav1);
        analysisManager->FillNtupleDColumn(5,tav1-tav0);

        analysisManager->AddNtupleRow();
    }

    /*if(event->GetEventID()%100==0){
        G4cout << "Analysed Events : " << analysed_events << G4endl;
    }*/


//    B5DetectorConstruction* b5 = (B5DetectorConstruction*) G4RunManager::GetRunManager()->GetUserDetectorConstruction();
//    G4double e=b5->GetEfficiency();
//
//    // Get hits collections
//    B5ScintillatorHitsCollection* hHC0 = static_cast<B5ScintillatorHitsCollection*>(hce->GetHC(fHH.at(0)));
//    B5ScintillatorHitsCollection* hHC1 = static_cast<B5ScintillatorHitsCollection*>(hce->GetHC(fHH.at(1)));
//    B5ScintillatorHitsCollection* hHC2 = static_cast<B5ScintillatorHitsCollection*>(hce->GetHC(fHH.at(2)));
//    B5ScintillatorHitsCollection* hHC3 = static_cast<B5ScintillatorHitsCollection*>(hce->GetHC(fHH.at(3)));
//    B5ScintillatorHitsCollection* hHC4 = static_cast<B5ScintillatorHitsCollection*>(hce->GetHC(fHH.at(4)));
//
//    std::vector<int> nhits;
//    nhits.push_back((int) hHC0->entries());
//    nhits.push_back((int) hHC1->entries());
//    nhits.push_back((int) hHC2->entries());
//    nhits.push_back((int) hHC3->entries());
//    nhits.push_back((int) hHC4->entries());
//
//    std::vector<G4double> timehits;         // time between paddle 1 and neutron or gamma detection
//
////        std::vector<G4double> realtimehits;     // real time (no delay)
////        std::vector<G4double> enehits;          // energy deposited by neutron or gamma
////        std::vector<G4double> particlehits;     // particle detected: muon, neutron or gamma. Muons should be vetoed but it might not always happen
////        std::vector<G4double> whichmuonhits;    // m+ or m- measured in the top paddles
////        std::vector<G4double> paddlehits;       // which paddle
////        std::vector<G4double> MuonEnergyhits;   // Energy of incoming muon
////        std::vector<G4double> MuonTimehits;     // Time between paddles 0 and 1 of incoming muon
////
//
//    B5ScintillatorHitsCollection* hitcoll;
//
//
//    //Find the earliest hit time
//    G4double time_origin=1e12;
//    for(int ipaddles=0; ipaddles<5; ipaddles++)
//    {
//        if(ipaddles==0){hitcoll=hHC0;}
//        else if(ipaddles==1){hitcoll=hHC1;}
//        else if(ipaddles==2){hitcoll=hHC2;}
//        else if(ipaddles==3){hitcoll=hHC3;}
//        else if(ipaddles==4){hitcoll=hHC4;}
//
//        for(int ihit=0; ihit<(int) nhits.at(ipaddles); ipaddles++)
//        {
//            B5ScintillatorHit* hit = (*hitcoll)[ihit];
//            if((hit->GetTime()/ns)<time_origin) time_origin=(hit->GetTime()/ns);
//        }
//    }
//
//    //Find the data
//    for(int ipaddles=0; ipaddles<5; ipaddles++)
//    {
//        if(ipaddles==0){hitcoll=hHC0;}
//        else if(ipaddles==1){hitcoll=hHC1;}
//        else if(ipaddles==2){hitcoll=hHC2;}
//        else if(ipaddles==3){hitcoll=hHC3;}
//        else if(ipaddles==4){hitcoll=hHC4;}
//
//        for(int ihit=0; ihit<(int) nhits.at(ipaddles); ipaddles++)
//        {
//            B5ScintillatorHit* hit = (*hitcoll)[ihit];
//             analysisManager->FillH1(1,(hit->GetTime()/ns)-time_origin);
//        }
//
//
//    }




    // Loop over the hits and populate the Ntuple



//     G4double edep = hit->GetEdep()/keV;
//     enehits.push_back(edep);


//
//    G4double r0=100.0*G4UniformRand();
//    G4double r1=100.0*G4UniformRand();
//    G4double r2=100.0*G4UniformRand();
//    G4double r3=100.0*G4UniformRand();
//    G4double r4=100.0*G4UniformRand();
//
//    /*
//    G4cout << "e " << e << G4endl;
//    G4cout << r0 << " " << r1 << " " << r2 << G4endl;
//    G4cout << hit0 << " "<< hit1 << " " << hit2 << G4endl;
//    */
//
//
//    if(r0>e) hit0=0;
//    if(r1>e) hit1=0;
//    if(r2>e) hit2=0;
//    if(r3>e) hit3=0;
//    if(r4>e) hit4=0;
//
//
///*
//    analysisManager->FillH1(0,hit0+hit1+hit2);
//    if(hit0>0) analysisManager->FillH1(1,hit0);
//    if(hit1>0) analysisManager->FillH1(2,hit1);
//    if(hit2>0) analysisManager->FillH1(3,hit2);
//*/
//
//    G4bool delays_on=fdelays_on;
//    G4cout << "delay: " << delays_on << G4endl;
//    G4bool use_mctruth=fuse_mctruth;
//    G4cout << "use mctruth: " << use_mctruth << G4endl;
//
//    G4double mintime = fmintime;
//    G4cout << "mintime: " << mintime << G4endl;
//    G4double minenergy = fminenergy;
//    G4cout << "minenergy: " << minenergy << G4endl;
//
//    G4bool trigger=false;
//
//    if( hit0>0 && hit1>0 )
//    {
//
//        trigger=true;
//        std::vector<G4double> timehits;         // time between paddle 1 and neutron or gamma detection
//        std::vector<G4double> realtimehits;     // real time (no delay)
//        std::vector<G4double> enehits;          // energy deposited by neutron or gamma
//        std::vector<G4double> particlehits;     // particle detected: muon, neutron or gamma. Muons should be vetoed but it might not always happen
//        std::vector<G4double> whichmuonhits;    // m+ or m- measured in the top paddles
//        std::vector<G4double> paddlehits;       // which paddle
//        std::vector<G4double> MuonEnergyhits;   // Energy of incoming muon
//        std::vector<G4double> MuonTimehits;     // Time between paddles 0 and 1 of incoming muon
//
//        G4int nmultiplicity = 0; // How many neutrons per capture
//        G4int gmultiplicity = 0; // How many gammas per capture
//        G4int pmultiplicity = 0; // protons
//        G4int elmultiplicity = 0; // electrons
//        G4int posmultiplicity = 0; // positrons
//        G4int totalmultiplicity = 0; // total
//
//        // G4cout << "a " << hit0 << " "<< hit1 << " " << hit2 << " " << hit3 << " " << hit4 << G4endl;
//
//    	//analysisManager->FillH1(4,1);
//        // each hit should have a random delay!
//
//        G4double timemean_mu = 15;  // muon trigger
//        G4double timesigma_mu = 5;
//        G4double timemean_pad = 5;  // single paddle delay
//        G4double timesigma_pad = 2;
//
//        B5HodoscopeHit* hitplate0 = (*hHC0)[0];
//        B5HodoscopeHit* hitplate1 = (*hHC1)[0];
//        G4double hit_time0;
//        G4double hit_time1;
//
//        if(delays_on) hit_time0 = hitplate0->GetTime()/ns + fabs(G4RandGauss::shoot(timemean_pad,timesigma_pad));
//        else hit_time0 = hitplate0->GetTime()/ns;
//
//        G4double real_hit_time1 = hitplate1->GetTime()/ns;
//
//        if(delays_on) hit_time1 = hitplate1->GetTime()/ns + fabs(G4RandGauss::shoot(timemean_mu,timesigma_mu));
//        else hit_time1 = real_hit_time1;
//
//        analysisManager->FillH1(1,hit_time1-hit_time0);
//
//        G4int muontype = hitplate0->GetType();
//        G4double MuonEnergy = hitplate0->GetKinE();
//
//        // if( (hit2==1 && hit3==0 && hit4==0) || (hit2==0 && hit3==1 && hit4==0) || (hit2==0 && hit3==0 && hit4==1))
//        // {
//        //     trigger=false;
//        //     G4cout << "not triggered" << G4endl;
//        // } // I don't think this works
//
//        // Check there is no muon hit in the side and bottom detectors, in order to trigger
//
//        G4double hitmintime = -400*ns;
//        G4double realhitmintime = -400*ns;
//
//        for(int ipaddles=0; ipaddles<3; ipaddles++)
//        {
//
//            G4int hitmax;
//            B5HodoscopeHitsCollection* hitcoll;
//
//            if(ipaddles==0)
//            {
//                hitmax=hit2;
//                hitcoll=hHC2;
//            }
//            else if(ipaddles==1)
//            {
//                hitmax=hit3;
//                hitcoll=hHC3;
//            }
//            else
//            {
//                hitmax=hit4;
//                hitcoll=hHC4;
//            }
//
//            G4int i=0;
//            while(i<hitmax && trigger) //bottom
//            {
//                B5HodoscopeHit* hit = (*hitcoll)[i];
//
//                G4double hit_time;
//                G4double real_hit_time;
//                real_hit_time = hit->GetTime()/ns-real_hit_time1;
//                if(delays_on) hit_time = hit->GetTime()/ns+fabs(G4RandGauss::shoot(timemean_pad,timesigma_pad))-hit_time1;
//                else hit_time = real_hit_time;
//
//                G4double edep = hit->GetEdep()/keV;
//
//                // couts for testing purposes
//
//                // G4cout << "edep = " << edep << " keV" << G4endl;
//
//                G4int type = hit->GetType();
//                // if(type==0 || type==1) G4cout << "muon" << G4endl;
//                // else if(type==2) G4cout << "neutron" << G4endl;
//                // else if(type==3) G4cout << "gamma" << G4endl;
//
//                if(use_mctruth && (type==0 || type==1))
//                {
//                    trigger=false;
//                    // G4cout << "not triggered (muon)" << G4endl;
//                }
//                else if(!use_mctruth && hit_time < hitmintime)
//                {
//                    trigger=false;
//                    // G4cout << "not triggered" << G4endl;
//                }
//                else if(edep>minenergy)
//                {
//                    timehits.push_back(hit_time);
//                    realtimehits.push_back(real_hit_time);
//                    enehits.push_back(edep);
//                    particlehits.push_back(type);
//                    whichmuonhits.push_back(muontype);
//                    paddlehits.push_back(ipaddles+2);
//                    MuonEnergyhits.push_back(MuonEnergy);
//                    MuonTimehits.push_back(hit_time1-hit_time0);
//                    // G4cout << "registered" << G4endl;
//
//                    if(type==2) nmultiplicity++;
//                    if(type==3) gmultiplicity++;
//                    if(type==4) pmultiplicity++;
//                    if(type==5) elmultiplicity++;
//                    if(type==6) posmultiplicity++;
//                    totalmultiplicity++;
//                    // G4cout << "type = " << type << G4endl;
//
//                    if(real_hit_time<hitmintime || realhitmintime==-400*ns) realhitmintime = real_hit_time;
//                    if(hit_time<hitmintime || hitmintime==-400*ns) hitmintime = hit_time;
//                }
//
//
//
//                // timehits.push_back(hit_time+time_delay);
//
//                i++;
//            }
//        }
//
//
//    	// Save the event time in the side and bottom detectors
//
//        G4int finalhits=timehits.size();
//
//        if(trigger && finalhits>0) // leave finalhits>0? why are there events with no hits, where trigger=true?
//        {
//            for(int itimes=0; itimes<finalhits; itimes++)
//            {
//                analysisManager->FillH1(0,timehits[itimes]);
//
//                analysisManager->FillNtupleDColumn(0,timehits[itimes]);
//                analysisManager->FillNtupleDColumn(1,realtimehits[itimes]);
//                analysisManager->FillNtupleDColumn(2,enehits[itimes]);
//                analysisManager->FillNtupleDColumn(3,particlehits[itimes]);
//                analysisManager->FillNtupleDColumn(4,whichmuonhits[itimes]);
//                analysisManager->FillNtupleDColumn(5,paddlehits[itimes]);
//                analysisManager->FillNtupleDColumn(6,MuonEnergyhits[itimes]);
//                analysisManager->FillNtupleDColumn(7,MuonTimehits[itimes]);
//                analysisManager->FillNtupleDColumn(8,event->GetEventID());
//                analysisManager->AddNtupleRow();
//            }
//
//            analysisManager->FillH1(2,nmultiplicity);
//            analysisManager->FillH1(3,gmultiplicity);
//
//            // G4cout << "nhits " << finalhits << G4endl;
//            // G4cout << "totalmultiplicity " << totalmultiplicity << G4endl;
//
//            analysisManager->FillNtupleDColumn(1,0,hitmintime);
//            analysisManager->FillNtupleDColumn(1,1,realhitmintime);
//            analysisManager->FillNtupleDColumn(1,2,nmultiplicity);
//            analysisManager->FillNtupleDColumn(1,3,gmultiplicity);
//            analysisManager->FillNtupleDColumn(1,4,pmultiplicity);
//            analysisManager->FillNtupleDColumn(1,5,elmultiplicity);
//            analysisManager->FillNtupleDColumn(1,6,posmultiplicity);
//            analysisManager->FillNtupleDColumn(1,7,totalmultiplicity);
//            analysisManager->FillNtupleDColumn(1,8,MuonEnergy);
//            analysisManager->FillNtupleDColumn(1,9,hit_time1-hit_time0);
//            analysisManager->AddNtupleRow(1);
//
//        }

        //   analysisManager->FillNtupleDColumn(0,eDep);
        //   hit = (*hHC2)[i];
        //   eDep = hit->GetEdep();
        //   analysisManager->FillNtupleDColumn(1,eDep);
        //   hit = (*hHC3)[i];
        //   eDep = hit->GetEdep();
        //   analysisManager->FillNtupleDColumn(2,eDep);
        // }


//	}
//    if((hit0>0)&&(hit1>0)&&(hit2>0)) analysisManager->FillH1(5,1);




    /*
    // loop over hits collections
    for(int i=0;i<(int) fHH.size();i++){

      // Get hits collections
      B5HodoscopeHitsCollection* hHC = static_cast<B5HodoscopeHitsCollection*>(hce->GetHC(fHH.at(i)));

      if ( !hHC )
	{
	  G4ExceptionDescription msg;
	  msg << "Some of hits collections of this event not found." << G4endl;
	  G4Exception("B5EventAction::EndOfEventAction()",
		      "B5Code001", JustWarning, msg);
	  return;
	}

      G4int n_hit = hHC->entries();
      int i2=i+1;

      //      G4cout<< "i2 " << i2 << " Nhits " << n_hit << " " << (int) fHH.size() << G4endl;


      if(n_hit>0) analysisManager->FillH1(i2, 1);

      if((n_hit>0)&&(i<2)) {
	anticoincidence++;
	coincidence++;
      }

      if((n_hit==0)&&(i>=2)) anticoincidence++;
      if((n_hit>0)&&(i>=2)) coincidence++;
      // G4cout << "Anti " << anticoincidence << G4endl;

      total_hits+=n_hit;

    }


    // G4cout << "index " << index << G4endl;

    if(anticoincidence>2) flag_anticoincidence = true;
    if(coincidence>2) flag_coincidence = true;
    */

    // Get hits collections
    // B5HodoscopeHitsCollection* hHC1
    //   = static_cast<B5HodoscopeHitsCollection*>(hce->GetHC(fHHC1ID));

    // B5HodoscopeHitsCollection* hHC2
    //   = static_cast<B5HodoscopeHitsCollection*>(hce->GetHC(fHHC2ID));

    // B5HodoscopeHitsCollection* hHC3
    //   = static_cast<B5HodoscopeHitsCollection*>(hce->GetHC(fHHC3ID));

    // B5DriftChamberHitsCollection* dHC1
    //   = static_cast<B5DriftChamberHitsCollection*>(hce->GetHC(fDHC1ID));

    // B5DriftChamberHitsCollection* dHC2
    //   = static_cast<B5DriftChamberHitsCollection*>(hce->GetHC(fDHC2ID));

    // B5EmCalorimeterHitsCollection* ecHC
    //   = static_cast<B5EmCalorimeterHitsCollection*>(hce->GetHC(fECHCID));

    // B5HadCalorimeterHitsCollection* hcHC
    //   = static_cast<B5HadCalorimeterHitsCollection*>(hce->GetHC(fHCHCID));

    // if ( (!hHC1) || (!hHC2) || (!dHC1) || (!dHC2) || (!ecHC) || (!hcHC) )
    // if ( (!hHC1) || (!hHC2) || (!hHC3) )
    // {
    //     G4ExceptionDescription msg;
    //     msg << "Some of hits collections of this event not found." << G4endl;
    //     G4Exception("B5EventAction::EndOfEventAction()",
    //                 "B5Code001", JustWarning, msg);
    //     return;
    // }

    //
    // Fill histograms & ntuple
    //

    // Get analysis manager
    // G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    // Fill histograms

    // G4int n_hit1 = hHC1->entries();
    // G4int n_hit2 = hHC2->entries();
    // G4int n_hit3 = hHC3->entries();
    // if(n_hit1>0) analysisManager->FillH1(1, n_hit1);
    // if(n_hit2>0) analysisManager->FillH1(2, n_hit2);
    // if(n_hit3>0) analysisManager->FillH1(3, n_hit3);

    // analysisManager->FillH1(0, n_hit1+n_hit2+n_hit3);

    // for (G4int i=0;i<n_hit;i++){
    //   B5HodoscopeHit* hit = (*hHC1)[i];
    //   G4double eDep = hit->GetEdep();
    //   analysisManager->FillNtupleDColumn(0,eDep);
    //   hit = (*hHC2)[i];
    //   eDep = hit->GetEdep();
    //   analysisManager->FillNtupleDColumn(1,eDep);
    //   hit = (*hHC3)[i];
    //   eDep = hit->GetEdep();
    //   analysisManager->FillNtupleDColumn(2,eDep);
    // }

    // for (G4int i=0;i<n_hit;i++)
    // {
    //    B5DriftChamberHit* hit = (*dHC1)[i];
    //    G4ThreeVector localPos = hit->GetLocalPos();
    //    analysisManager->FillH2(0, localPos.x(), localPos.y());
    // }

    // n_hit = dHC2->entries();
    // analysisManager->FillH1(1, n_hit);

    // for (G4int i=0;i<n_hit;i++)
    // {
    //    B5DriftChamberHit* hit = (*dHC2)[i];
    //    G4ThreeVector localPos = hit->GetLocalPos();
    //    analysisManager->FillH2(1, localPos.x(), localPos.y());
    // }


    // // Fill ntuple

    // // Dc1Hits
    // analysisManager->FillNtupleIColumn(0, dHC1->entries());
    // // Dc2Hits
    // analysisManager->FillNtupleIColumn(1, dHC1->entries());

    // // ECEnergy
    // G4int totalEmHit = 0;
    // G4double totalEmE = 0.;
    // for (G4int i=0;i<80;i++)
    // {
    //     B5EmCalorimeterHit* hit = (*ecHC)[i];
    //     G4double eDep = hit->GetEdep();
    //     if (eDep>0.)

    //     {
    //         totalEmHit++;
    //         totalEmE += eDep;
    //     }
    // }
    // analysisManager->FillNtupleDColumn(2, totalEmE);

    // // HCEnergy
    // G4int totalHadHit = 0;
    // G4double totalHadE = 0.;
    // for (G4int i=0;i<20;i++)
    // {
    //     B5HadCalorimeterHit* hit = (*hcHC)[i];
    //     G4double eDep = hit->GetEdep();
    //     if (eDep>0.)
    //     {
    //         totalHadHit++;
    //         totalHadE += eDep;
    //     }
    // }
    // analysisManager->FillNtupleDColumn(3, totalHadE);

    // Time 1
    // for (G4int i=0;i<hHC1->entries();i++)
    // {
    //   analysisManager->FillNtupleDColumn(2,(*hHC1)[i]->GetTime());
    // }

    // // Time 2
    // for (G4int i=0;i<hHC2->entries();i++)
    // {
    //   analysisManager->FillNtupleDColumn(3,(*hHC2)[i]->GetTime());
    // }

    // analysisManager->AddNtupleRow();

    //
    // Print diagnostics
    //

    G4int printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
    if ( printModulo==0 || event->GetEventID() % printModulo != 0) return;

    // G4PrimaryParticle* primary = event->GetPrimaryVertex(0)->GetPrimary(0);
    // G4cout << G4endl
    //        << ">>> Event " << event->GetEventID() << " >>> Simulation truth : "
    //        << primary->GetG4code()->GetParticleName()
    //        << " " << primary->GetMomentum() << G4endl;

    // // Hodoscope 1
    // n_hit1 = hHC1->entries();
    // G4cout << "Hodoscope 1 has " << n_hit1 << " hits." << G4endl;
    // for (G4int i=0;i<n_hit1;i++)
    // {
    //     B5HodoscopeHit* hit = (*hHC1)[i];
    //     hit->Print();
    // }

    // // Hodoscope 2
    // n_hit2 = hHC2->entries();
    // G4cout << "Hodoscope 2 has " << n_hit2 << " hits." << G4endl;
    // for (G4int i=0;i<n_hit2;i++)
    // {
    //     B5HodoscopeHit* hit = (*hHC2)[i];
    //     hit->Print();
    // }

    // // Drift chamber 1
    // n_hit = dHC1->entries();
    // G4cout << "Drift Chamber 1 has " << n_hit << " hits." << G4endl;
    // for (G4int i2=0;i2<5;i2++)
    // {
    //     for (G4int i=0;i<n_hit;i++)
    //     {
    //         B5DriftChamberHit* hit = (*dHC1)[i];
    //         if (hit->GetLayerID()==i2) hit->Print();
    //     }
    // }

    // // Drift chamber 2
    // n_hit = dHC2->entries();
    // G4cout << "Drift Chamber 2 has " << n_hit << " hits." << G4endl;
    // for (G4int i2=0;i2<5;i2++)
    // {
    //     for (G4int i=0;i<n_hit;i++)
    //     {
    //         B5DriftChamberHit* hit = (*dHC2)[i];
    //         if (hit->GetLayerID()==i2) hit->Print();
    //     }
    // }

    // // EM calorimeter
    // G4cout << "EM Calorimeter has " << totalEmHit << " hits. Total Edep is "
    // << totalEmE/MeV << " (MeV)" << G4endl;

    // // Had calorimeter
    // G4cout << "Hadron Calorimeter has " << totalHadHit << " hits. Total Edep is "
    // << totalHadE/MeV << " (MeV)" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
