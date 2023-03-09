#ifndef AnalysisSteering_h
#define AnalysisSteering_h

#include "AnalysisInfo.h"
#include "util/include/ActiveObserver.h"

class Event;

class AnalysisSteering: public ActiveObserver<AnalysisInfo::AnalysisStatus> {

 public:

  AnalysisSteering( const AnalysisInfo* info );
  // deleted copy constructor and assignment to prevent unadvertent copy
  AnalysisSteering           ( const AnalysisSteering& x ) = delete;
  AnalysisSteering& operator=( const AnalysisSteering& x ) = delete;

  ~AnalysisSteering() override;

  // function to be called at execution start / end
  void update( const AnalysisInfo::AnalysisStatus& status ) override;

 protected:

  const AnalysisInfo* aInfo;

 private:

  // function to be called at execution start
  virtual void beginJob() = 0;
  // function to be called at execution end
  virtual void   endJob() = 0;

};

#endif

