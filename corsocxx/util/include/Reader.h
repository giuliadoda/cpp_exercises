#ifndef Reader_h
#define Reader_h

#include <iostream>
#include <fstream>
#include <string>

// interface classes to give uniform access to text and binary files
class Reader {
 public:
  // constructor and destructor
  Reader( std::istream* ip ): is( ip ) {}
  Reader           ( const Reader& r ) = delete;
  Reader& operator=( const Reader& r ) = delete;
  virtual ~Reader() { delete is; }
  // input operator for generic objects
  template <class T>
  Reader& operator>>( T& x ) {
    // create wrapper and do input operation
    Wrapper<T> w( x );
    read( w );
    // return *this to allow input operators concatenation
    return *this;
  }
  // type conversion
  operator bool() { return status; }
 protected:
  // input stream and status
  std::istream* is;
  bool status;
  // visitor wrapper base for input operations
  class BaseWrapper {
   public:
    BaseWrapper() {}
    BaseWrapper           ( const BaseWrapper& r ) = delete;
    BaseWrapper& operator=( const BaseWrapper& r ) = delete;
    virtual ~BaseWrapper() {}
    // cannot rely on overloading to select required read function,
    // concrete acceptors (i.e. reader) classes not yet defined
    virtual bool readT( Reader* r ) = 0; // read from text   file
    virtual bool readB( Reader* r ) = 0; // read from binary file
  };
 private:
  // Concrete visitor for generic input types
  template <class T>
  class Wrapper: public BaseWrapper {
   public:
    // constructor and input functions
    Wrapper( T& x ): p( &x ) {}
    Wrapper           ( const Wrapper& r ) = delete;
    Wrapper& operator=( const Wrapper& r ) = delete;
    ~Wrapper() override {}
    bool readT( Reader* r ) override {
      return static_cast<bool>( r->inStream() >> *p );
    }
    bool readB( Reader* r ) override {
      return static_cast<bool>( r->inStream().read(
                                   reinterpret_cast<char*>( p ),
                                   sizeof( *p ) ) );
    }
   private:
    // input object pointer
    T* p;
  };
  // accept (read) function
  virtual void read( BaseWrapper& w ) = 0;
  std::istream& inStream() {
    return ( is == nullptr ? std::cin : *is );
  }
};

// concrete reader for text input files
class TxtReader: public Reader {
 public:
  TxtReader( std::istream* ip ): Reader( ip ) {}
  TxtReader           ( const TxtReader& r ) = delete;
  TxtReader& operator=( const TxtReader& r ) = delete;
  ~TxtReader() override {}
 private:
  void read( BaseWrapper& w ) override { status = w.readT( this ); } 
};

// concrete reader for binary input files
class BinReader: public Reader {
 public:
  BinReader( std::istream* ip ): Reader( ip ) {}
  BinReader           ( const BinReader& r ) = delete;
  BinReader& operator=( const BinReader& r ) = delete;
  ~BinReader() override {}
 private:
  void read( BaseWrapper& w ) override { status = w.readB( this ); } 
};

// reader factory
class ReaderFactory {
 public:
  static Reader* create( const std::string& name,
                         std::ios::openmode mode = std::ios::in ) {
    std::istream* is = ( name.empty() ?
                         nullptr :
                         new std::ifstream( name.c_str(), mode ) );
    if ( mode & std::ios::binary )
    return new BinReader( is );
    return new TxtReader( is );
  }
};

#endif

