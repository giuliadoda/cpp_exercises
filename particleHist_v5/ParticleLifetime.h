#ifndef ParticleLifetime_h
#define ParticleLifetime_h

#include "AnalysisSteering.h"
#include "TH1F.h"
#include "util/include/ActiveObserver.h"

#include <vector>

using namespace std;


class LifetimeFit;

class ParticleLifetime: public AnalysisSteering, 
                        public ActiveObserver<Event> {

    public:

        ParticleLifetime( const AnalysisInfo* info );
        // deleted copy constructor and assignment to prevent unadvertent copy
        ParticleLifetime           ( const ParticleLifetime& x ) = delete;
        ParticleLifetime& operator=( const ParticleLifetime& x ) = delete;

        ~ParticleLifetime() override;

        struct Particle {
            string pName;
            LifetimeFit* tptr;
            TH1F* h;
            };
        
        // function to be called at execution start
        void beginJob() override;
        // function to be called at execution end
        void   endJob() override;
        // function to be called for each event
        void update( const Event& ev ) override;

        // create a decay mode
        void pCreate(const string& name, const double min, const double max,
                        const double timeMin, const double timeMax, 
                        const double scanMin, const double scanMax,
                        const double scanStep);

    private:

        vector<Particle*> pList;
        
    };

#endif