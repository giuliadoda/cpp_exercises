#include "ParticleLifetime.h"
#include "AnalysisFramework/AnalysisInfo.h"
#include "AnalysisFramework/AnalysisFactory.h"
#include "AnalysisObjects/ProperTime.h"

#include "AnalysisObjects/LifetimeFit.h"
#include "TFile.h"

#include <iostream>
#include <fstream>


using namespace std;


class ParticleLifetimeFactory: public AnalysisFactory::AbsFactory {

    public:
        // assign plot as name
        ParticleLifetimeFactory(): AnalysisFactory::AbsFactory( "time" ) {}
        // create ParticleLifetime
        AnalysisSteering* create( const AnalysisInfo* info ) override {
            return new ParticleLifetime( info );
            }

};

// create a global ParticleLifetimeFactory, created and registered before execution start
static ParticleLifetimeFactory pl;

ParticleLifetime::ParticleLifetime( const AnalysisInfo* info ):
    AnalysisSteering( info ) {
    }

ParticleLifetime::~ParticleLifetime() {
        }

//  create and store the pointers to 2 "MassMean" objects 
//  for the 2 decay modes, using the same mass ranges as for previous versions
void ParticleLifetime::beginJob() {

    // fit range from txt file
    ifstream file(aInfo->value("time").c_str());
    string pName;

    double mMin;
    double mMax;
    double tMin;
    double tMax;
    double sMin;
    double sMax;
    double ts;

    while (file >> pName >> mMin >> mMax
                         >> tMin >> tMax
                         >> sMin >> sMax
                         >> ts ) {
        pCreate(pName, mMin, mMax, tMin, tMax, sMin, sMax, ts);
    }

    return;

}

//  loop over the "MassMean" objects and for each one 
//  compute mean and rms masses and print results
//  save histogram to file
void ParticleLifetime::endJob() {

    // save histogram to file 
    TDirectory* currentDir = gDirectory;
    TFile* file = new TFile(aInfo->value( "particleFitters" ).c_str(), "CREATE");

    for ( Particle* m: pList ) {

        // compute mean and rms
        m->tptr->compute();

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
void ParticleLifetime::update( const Event& ev ) {

    static ProperTime* propt = ProperTime::instance();

    for ( Particle* n: pList ) {
        
        // returns true if mass is in range
        bool c = n->tptr->add();
        
        // filling hist with decay time for the accepted event
        if (c) {
            double t = propt->decayTime(); 
            n->h->Fill(t);
            }

        }
    
    return;

    }

// create a decay mode --> called in begin job
void ParticleLifetime::pCreate( const string& name, const double min, const double max,
                                const double timeMin, const double timeMax, 
                                const double scanMin, const double scanMax,
                                const double scanStep ) {

    // create name for TH1F 
    string histName = "time" + name;
    const char* hName = histName.c_str();

    // bin number 
    int nBin = 100;

    // create TH1F
    Particle* pp = new Particle;
    pp->pName = name;
    pp->tptr = new LifetimeFit(min, max, timeMin, timeMax, scanMin, scanMax, scanStep);
    pp->h = new TH1F(hName, hName, nBin, timeMin, timeMax);
    pList.push_back(pp);

    return;

    }