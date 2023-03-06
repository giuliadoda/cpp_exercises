#ifndef ParticleMass_h
#define ParticleMass_h

#include "AnalysisSteering.h"

#include <vector>

using namespace std;


class MassMean;

class ParticleMass: public AnalysisSteering {

    public:

        ParticleMass();
        // deleted copy constructor and assignment to prevent unadvertent copy
        ParticleMass           ( const ParticleMass& x ) = delete;
        ParticleMass& operator=( const ParticleMass& x ) = delete;

        ~ParticleMass() override;

        // function to be called at execution start
        void beginJob() override;
        // function to be called at execution end
        void   endJob() override;
        // function to be called for each event
        void process( const Event& ev ) override;

    private:

        vector<MassMean*> pList;
        
    };

#endif