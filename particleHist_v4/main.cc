#include "AnalysisInfo.h"
#include "EventSource.h"
#include "SourceFactory.h"
#include "AnalysisSteering.h"
#include "EventDump.h"
#include "ParticleMass.h"
#include "ParticleLifetime.h"
#include "AnalysisFactory.h"


#include <vector>
#include <string>
#include <sstream>


using namespace std;

int main( int argc, char* argv[] ) {

  // store command line parameters
  AnalysisInfo* info = new AnalysisInfo( argc, argv );

  // create data source
  EventSource* es = SourceFactory::create( info );

  // create a list of analyzers
  vector<AnalysisSteering*> aList = AnalysisFactory::create( info );

  // initialize all analyzers
  for ( auto as: aList ) as->beginJob();

  // loop over events
  es->run();

  // finalize all analyzers: compute mean and rms and print 
  for ( auto as: aList ) as->endJob();

  delete es;

  return 0;

}