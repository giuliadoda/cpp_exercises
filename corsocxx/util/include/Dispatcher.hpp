//#include "Dispatcher.h"
#include "ActiveObserver.h"
#include "LazyObserver.h"

#include <iostream>

template <class T>
const T* Dispatcher<T>::last = nullptr;

template <class T>
void Dispatcher<T>::  subscribe( ActiveObserver<T>* obs ) {
  activeObserverList()->insert( obs );
  return;
}

template <class T>
void Dispatcher<T>::unsubscribe( ActiveObserver<T>* obs ) {
  activeObserverList()->erase( obs );
  return;
}

template <class T>
void Dispatcher<T>::  subscribe( LazyObserver<T>* obs ) {
  lazyObserverList()->insert( obs );
  if ( last != nullptr ) obs->lazyUpdate( *last );
  return;
}

template <class T>
void Dispatcher<T>::unsubscribe(   LazyObserver<T>* obs ) {
  lazyObserverList()->erase( obs );
  return;
}

template <class T>
void Dispatcher<T>::notify( const T& x ) {

  last = &x;

  static auto lol =   lazyObserverList();
  for ( auto e: *lol ) e->lazyUpdate( x );

  static auto aol = activeObserverList();
  for ( auto e: *aol ) e->    update( x );

  return;

}

template <class T>
std::set<ActiveObserver<T>*>* Dispatcher<T>::activeObserverList() {
  static auto ptr = new std::set<ActiveObserver<T>*>;
  return ptr;
}

template <class T>
std::set<  LazyObserver<T>*>* Dispatcher<T>::  lazyObserverList() {
  static auto ptr = new std::set<  LazyObserver<T>*>;
  return ptr;
}

