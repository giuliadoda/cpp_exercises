#ifndef TFileProxy_h
#define TFileProxy_h

#include "TFile.h"

#include <string>
#include <map>

class TFileProxy {

 public:

  // constructor
  TFileProxy( const std::string& name, const std::string& mode ):
   fName( name ) {
     // look for file in map
     static std::map<std::string,TFile*>& m = fMap();
     std::map<std::string,TFile*>::iterator iter = m.find( name );
     // if not found open with specified mode
     if ( iter == m.end() ) {
       m[name] = new TFile( name.c_str(), mode.c_str() );
     }
     // if found reopen the file
     else {
       // reopen file for writing
       if ( ( mode != "" ) && ( mode != "READ" ) )
            iter->second = new TFile( name.c_str(), "UPDATE" );
       // reopen readonly file
       else iter->second = new TFile( name.c_str() );
       // set current directory to file
       iter->second->cd();
     }
  }
  // deleted copy constructor and assignment to prevent unadvertent copy
  TFileProxy           ( const TFileProxy& x ) = delete;
  TFileProxy& operator=( const TFileProxy& x ) = delete;

  // destructor
  ~TFileProxy() {
    Close();
  }

  // forward functions

  bool cd() {
    static std::map<std::string,TFile*>& m = fMap();
    return m[fName]->cd();
  }

  void Close() {
    static std::map<std::string,TFile*>& m = fMap();
    TFile*& file = m[fName];
    if ( file == nullptr ) return;
    file->Close();
    delete file;
    file = nullptr;
    return;
  }

 private:

  // file name
  std::string fName;

  // map of names to TFile
  static std::map<std::string,TFile*>& fMap() {
    static std::map<std::string,TFile*> m;
    return m;
  }

};

#endif

