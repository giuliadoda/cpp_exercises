#include "ParticleMass.h"
#include "AnalysisSteering.h"
#include "MassMean.h"
#include <vector>
#include <iostream>
#include "TH1F.h"
#include "TFile.h"

using namespace std;

double mass(const Event& ev); // global function to compute invariant mass

ParticleMass::ParticleMass() {
}

ParticleMass::~ParticleMass() {
}

//create and store the pointers to 2 "MassMean" objects 
//for the 2 decay modes, using the same mass ranges as for previous versions
void ParticleMass::beginJob() {

    const double mMinK = 0.495;
    const double mMaxK = 0.500;

    const double mMinL = 1.115;
    const double mMaxL = 1.116;

    const string k = "kMean";
    const string l = "lMean";

    pCreate(k, mMinK, mMaxK);
    pCreate(l, mMinL, mMaxL);

}

//loop over the "MassMean" objects and for each one 
//compute mean and rms masses and print results
void ParticleMass::endJob() {

    for ( Particle* m: pList) {

        // compute mean and rms
        m->mptr->compute();

        // print results
        cout << m->mptr->nEvent() << " " << m->mptr->mMean() << " " << m->mptr->mRMS() << endl;

        // save histogram to file 
        TDirectory* currentDir = gDirectory;
        TFile* file = new TFile("partist.root", "UPDATE");
        m->h->Write();
        delete file;
        currentDir->cd();

        }
        
}

//loop over the "MassMean" objects and for each one 
//call the "add" function --> update sums 
// and fill histogram
void ParticleMass::process( const Event& ev ) {

    for ( Particle* n: pList) {
        
        // returns true if mass is in range
        bool c = n->mptr->add(ev);
        
        // filling hist w invariant mass for the accepted event
        if (c) {
            double m = mass(ev); 
            n->h->Fill(m);
            }

        }
    
}

// create a decay mode --> called in begin job
void ParticleMass::pCreate(const string& name, const double min, const double max) {

    // create name for TH1F 
    const char* hName = name.c_str();

    // bin number 
    int nBin = 100;

    // create TH1F
    Particle* pp = new Particle;
    pp->pName = name;
    pp->mptr = new MassMean(min, max);
    pp->h = new TH1F(hName, hName, nBin, min, max);
    pList.push_back(pp);

    return;

}