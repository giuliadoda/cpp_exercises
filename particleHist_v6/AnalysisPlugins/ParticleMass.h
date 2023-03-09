#ifndef ParticleMass_h
#define ParticleMass_h

#include "AnalysisFramework/AnalysisSteering.h"
#include "TH1F.h"
#include "util/include/ActiveObserver.h"

#include <vector>

using namespace std;


class MassMean;

class ParticleMass: public AnalysisSteering, public ActiveObserver<Event> {

    public:

        ParticleMass( const AnalysisInfo* info );
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
        void update( const Event& ev ) override;

        // create a decay mode
        void pCreate(const string& name, const double min, const double max);

    private:

        vector<Particle*> pList;
        
    };

#endif