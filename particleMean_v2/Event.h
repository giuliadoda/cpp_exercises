#ifndef Event_h
#define Event_h

class Event {

 public:

  // constructor
  Event( int n, float x, float y, float z ); // create an event with number "n" (event id)
                                             // and decay point coordinates x, y, z
  // destructor
  ~Event();

  // composite object Particle to hold all information for each particle
  // ( electric charge and x,y,z momentum components )
  struct Particle {
    int charge; // particle charge
    double px;
    double py;
    double pz;  // particle momentum
  };
  typedef const Particle* part_ptr;

  // add a particle to the event
  void add( int charge, double px, double py, double pz );

  // get event id.
  int eventNumber() const;

  // get decay point coordinates (function)
  float X() const;
  float Y() const;
  float Z() const;

  // get number of particles (function)
  int nParticles() const;

  // get particle
  part_ptr particle( unsigned int i ) const; // returning the pointer to the 
                                             // corresponding particle (otherwise nullptr)



 private:

  // event-specific informations:
  int evNumber; // event id
  float x;      // decay point
  float y;
  float z;

  // particles: number and array of pointers
  int np; // particle number
  Particle** Ps; // array of pointers to particle struct

  int maxP; // maximum number of particles

};

#endif

