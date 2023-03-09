#include "ParticleMass.h"
#include "AnalysisInfo.h"
#include "AnalysisFactory.h"
#include "ParticleReco.h"

#include "MassMean.h"
#include "TFile.h"

#include <iostream>
#include <fstream>


using namespace std;


class ParticleMassFactory: public AnalysisFactory::AbsFactory {

    public:
        // assign plot as name
        ParticleMassFactory(): AnalysisFactory::AbsFactory( "plot" ) {}
        // create ParticleMass
        AnalysisSteering* create( const AnalysisInfo* info ) override {
            return new ParticleMass( info );
            }

};

// create a global ParticleMassFactory, created and registered before execution start
static ParticleMassFactory pm;

ParticleMass::ParticleMass( const AnalysisInfo* info ):
    AnalysisSteering( info ) {
    }

ParticleMass::~ParticleMass() {
    }

//  create and store the pointers to 2 "MassMean" objects 
//  for the 2 decay modes, using the same mass ranges as for previous versions
void ParticleMass::beginJob() {

    // read mass ranges from txt file
    ifstream file(aInfo->value("plot").c_str());
    string pName;

    double mMin;
    double mMax;

    while (file >> pName >> mMin >> mMax) {
        pCreate(pName, mMin, mMax);
    }

    return;

}

//  loop over the "MassMean" objects and for each one 
//  compute mean and rms masses and print results
//  save histogram to file
void ParticleMass::endJob() {

    // save histogram to file 
    TDirectory* currentDir = gDirectory;
    TFile* file = new TFile(aInfo->value( "massRanges" ).c_str(), "CREATE");

    for ( Particle* m: pList ) {

        // compute mean and rms
        m->mptr->compute();

        // print results
        cout << m->mptr->nEvent() << " " << m->mptr->mMean() << " " << m->mptr->mRMS() << endl;

        // fill file with histogram
        m->h->Write();

        }

    file->Close();
    delete file;
    currentDir->cd();

    return;
        
    }

// loop over the "MassMean" objects and for each one 
// call the "add" function --> update sums 
// and fill histogram
void ParticleMass::update( const Event& ev ) {

    static ParticleReco* part_r = ParticleReco::instance();

    for ( Particle* n: pList ) {
        
        // returns true if mass is in range
        bool c = n->mptr->add();
        
        // filling hist with invariant mass for the accepted event
        if (c) {
            double m = part_r->pMass(); 
            n->h->Fill(m);
            }

        }
    
    return;

    }

// create a decay mode --> called in begin job
void ParticleMass::pCreate( const string& name, const double min, const double max ) {

    // create name for TH1F 
    string histName = "mass" + name;
    const char* hName = histName.c_str();

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