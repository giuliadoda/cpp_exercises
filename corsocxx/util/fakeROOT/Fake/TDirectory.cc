#include "TDirectory.h"
//#include "TH1F.h"
#include <iostream>

using namespace std;

TDirectory::TDirectory(): fp( nullptr ) {
}


TDirectory::~TDirectory() {
}


bool TDirectory::cd() {
  gDirectory = this;
  return true;
}


std::ios* TDirectory::file() const {
  return fp;
}


TH1F* TDirectory::Get( const char* name ) {
  if ( hmap.empty() ) update();
  if ( hmap.empty() ) return nullptr;
  map<string,TH1F*>::iterator iter = hmap.find( name );
  map<string,TH1F*>::iterator iend = hmap.end();
  if ( iter != iend ) return iter->second;
  return nullptr;
}


std::vector<std::string> TDirectory::histoList() {
  TDirectory* currentDir = gDirectory;
  cd();
  std::vector<std::string> hl;
  if ( hmap.empty() ) update();
  if ( hmap.empty() ) return hl;
  hl.reserve( hmap.size() );
  for ( auto& e: hmap ) hl.push_back( e.first );
  currentDir->cd();
  return hl;
}


void TDirectory::update() {
  return;
}


TDirectory* gDirectory = new TDirectory;

