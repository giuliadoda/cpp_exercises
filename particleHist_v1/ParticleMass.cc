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

    const string k = "K mean";
    const string l = "L mean";

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

        // create name for file 
        const char* fName = (m->pName).c_str();

        // save histogram to file 
        TDirectory* currentDir = gDirectory;
        TFile* file = new TFile(fName, "NEW");
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
            double m = mass(ev); // check precision?
            n->h->Fill(m);
            }

        }
    
}

// create a decay mode --> called in begin job
void ParticleMass::pCreate(const string& name, const double min, const double max) {

    // create name for TH1F 
    const char* hName = name.c_str();

    // bin number --> check
    int nBin = 10;

    // create TH1F
    Particle* pp = new Particle;
    pp->pName = name;
    pp->mptr = new MassMean(min, max);
    pp->h = new TH1F(hName, hName, nBin, 0.5, nBin + 0.5);
    pList.push_back(pp);

    return;

}