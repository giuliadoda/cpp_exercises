#ifndef Writer_h
#define Writer_h

#include <iostream>
#include <fstream>
#include <string>

// interface classes to give uniform access to text and binary files
class Writer {
 public:
  // constructor and destructor
  Writer( std::ostream* op ): os( op ) {}
  Writer           ( const Writer& w ) = delete;
  Writer& operator=( const Writer& w ) = delete;
  virtual ~Writer() { delete os; }
  // output operator for ostream functions (e.g. "endl")
  Writer& operator<<( std::ostream& ( *pf )( std::ostream& ) ) {
    outStream() << pf;
    // return *this to allow output operators concatenation
    return *this;
  }
  // output operator for generic objects
  template <class T>
  Writer& operator<<( const T& t ) {
    Wrapper<T> w( t );
    write( w );
    // return *this to allow output operators concatenation
    return *this;
  }
  // cleaner class to filter output instructions not suited
  // for binary files
  class BaseCleaner {
   public:
    BaseCleaner() {}
    BaseCleaner             ( const BaseCleaner& c ) = delete;
    BaseCleaner& operator = ( const BaseCleaner& c ) = delete;
    virtual ~BaseCleaner() {}
    virtual bool write( Writer& w ) = 0;
  };
  class Cleaner {
   public:
    typedef std::ostream& ( *F )( std::ostream& );
    template <class T>
    Cleaner( const T& t ): p( new FormatCleaner<T>(  t ) ) {}
    Cleaner( F pf       ): p( new CallCleaner     ( pf ) ) {}
    Cleaner             ( const Cleaner& c ) = delete;
    Cleaner& operator = ( const Cleaner& c ) = delete;
    ~Cleaner() { delete p; }
    BaseCleaner* get() const { return p; }
   private:
    BaseCleaner* p;
  };
  Writer& operator<<( const Cleaner& c ) {
    write( *c.get() );
    // return *this to allow output operators concatenation
    return *this;
  }
  // type conversion
  operator bool() { return status; }
  // flush
  void flush() { outStream() << std::flush; }
 protected:
  // output stream
  std::ostream* os;
  bool status;
  // visitor wrapper base for output operations
  class BaseWrapper {
   public:
    BaseWrapper() {}
    BaseWrapper           ( const BaseWrapper& r ) = delete;
    BaseWrapper& operator=( const BaseWrapper& r ) = delete;
    virtual ~BaseWrapper() {}
    // cannot rely on overloading to select required write function,
    // concrete acceptors (i.e. writer) classes not yet defined
    virtual bool writeT( Writer* w ) = 0;
    virtual bool writeB( Writer* w ) = 0;
  };
 private:
  // Concrete visitor for generic output types
  template <class T>
  class Wrapper: public BaseWrapper {
   public:
    // constructor and output functions
    Wrapper( const T& t ): p( &t ) {}
    Wrapper           ( const Wrapper& r ) = delete;
    Wrapper& operator=( const Wrapper& r ) = delete;
    ~Wrapper() override {}
    bool writeT( Writer* w ) override {
      return static_cast<bool>( w->outStream() << *p );
    }
    bool writeB( Writer* w ) override {
      return static_cast<bool>( w->outStream().write(
                                   reinterpret_cast<const char*>( p ),
                                   sizeof( *p ) ) );
    }
   private:
    // output object pointer
    const T* p;
  };
  // Concrete cleaner for generic input types
  template <class T>
  class FormatCleaner: public BaseCleaner {
   public:
    FormatCleaner( const T& t ): p( &t ) {}
    FormatCleaner             ( const FormatCleaner& c ) = delete;
    FormatCleaner& operator = ( const FormatCleaner& c ) = delete;
    ~FormatCleaner() override {}
    bool write( Writer& w ) override { return w << *p; }
   private:
    const T* p;
  };
  // Concrete cleaner for ostream functions
  class CallCleaner: public BaseCleaner {
   public:
    CallCleaner( Cleaner::F x ): f( x ) {}
    CallCleaner             ( const CallCleaner& c ) = delete;
    CallCleaner& operator = ( const CallCleaner& c ) = delete;
    ~CallCleaner() override {}
    bool write( Writer& w ) override { return w << f; }
   private:
    Cleaner::F f;
  };
  // accept (write) function
  virtual void write( BaseWrapper& w ) = 0;
  virtual void write( BaseCleaner& c ) = 0;
  std::ostream& outStream() {
    return ( os == nullptr ? std::cout : *os );
  }
};

// concrete writer for text output files
class TxtWriter: public Writer {
 public:
  TxtWriter( std::ostream* op ): Writer( op ) {}
  TxtWriter           ( const TxtWriter& w ) = delete;
  TxtWriter& operator=( const TxtWriter& w ) = delete;
  ~TxtWriter() override {}
 private:
  void write( BaseWrapper& w ) override { status = w.writeT( this ); } 
  void write( BaseCleaner& c ) override { status = c.write( *this ); } 
};

// concrete writer for binary output files
class BinWriter: public Writer {
 public:
  BinWriter( std::ostream* op ): Writer( op ) {}
  BinWriter           ( const BinWriter& w ) = delete;
  BinWriter& operator=( const BinWriter& w ) = delete;
  ~BinWriter() override {}
 private:
  void write( BaseWrapper& w ) override { status = w.writeB( this ); } 
  void write( BaseCleaner& c ) override {} 
};

// writer factory
class WriterFactory {
 public:
  static Writer* create( const std::string& name,
                         std::ios::openmode mode = std::ios::out ) {
    std::ostream* os = ( name.empty() ?
                         nullptr :
                         new std::ofstream( name.c_str(), mode ) );
    if ( mode & std::ios::binary )
    return new BinWriter( os );
    return new TxtWriter( os );
  }
};

#endif

