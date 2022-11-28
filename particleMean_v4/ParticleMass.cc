#include "ParticleMass.h"
#include "AnalysisSteering.h"
#include "MassMean.h"
#include <vector>
#include <iostream>

using namespace std;

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

    MassMean* K = new MassMean(mMinK, mMaxK);
    MassMean* L = new MassMean(mMinL, mMaxL);

    pList.push_back( K );
    pList.push_back( L );

}

//loop over the "MassMean" objects and for each one 
//compute mean and rms masses and print results
void ParticleMass::endJob() {

    for ( MassMean* m: pList) {

        // compute mean and rms
        m->compute();

        // print results
        cout << m->nEvent() << " " << m->mMean() << " " << m->mRMS() << endl;

        }
        
}

//loop over the "MassMean" objects and for each one 
//call the "add" function --> update sums 
void ParticleMass::process( const Event& ev ) {

    for ( MassMean* n: pList) {
        
        n->add(ev);}
    
}