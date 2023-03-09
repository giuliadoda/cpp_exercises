#ifndef TDirectory_h
#define TDirectory_h

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

class TH1F;

class TDirectory {

  friend class TH1F;

 public:

  // constructor
  TDirectory();
  // deleted copy constructor and assignment to prevent unadvertent copy
  TDirectory           ( const TDirectory& x ) = delete;
  TDirectory& operator=( const TDirectory& x ) = delete;

  // destructor
  virtual ~TDirectory();

  bool cd();
  std::ios* file() const;

  TH1F* Get( const char* name );
  std::vector<std::string> histoList();

 protected:

  std::ios* fp;
  std::map<std::string,TH1F*> hmap;

 private:

  virtual void update();

};

extern TDirectory* gDirectory;

#endif

