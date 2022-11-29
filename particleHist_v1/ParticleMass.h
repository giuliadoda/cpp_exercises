#ifndef ParticleMass_h
#define ParticleMass_h

#include "AnalysisSteering.h"
#include <vector>
#include "TH1F.h"

using namespace std;

class MassMean;

class ParticleMass: public AnalysisSteering {

    public:

        ParticleMass();
        // deleted copy constructor and assignment to prevent unadvertent copy
        ParticleMass           ( const ParticleMass& x ) = delete;
        ParticleMass& operator=( const ParticleMass& x ) = delete;

        ~ParticleMass() override;

        struct Particle {
            string pName;
            MassMean* mptr;
            TH1F* h;
            };
        
        // function to be called at execution start
        void beginJob() override;
        // function to be called at execution end
        void   endJob() override;
        // function to be called for each event
        void process( const Event& ev ) override;

        // create a decay mode
        void pCreate(const string& name, const double min, const double max);

    private:

        vector<Particle*> pList;
};

#endif