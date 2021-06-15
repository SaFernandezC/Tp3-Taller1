#include "Listener.h"
#include <syslog.h>

Listener::Listener(std::string& port){
  accepter.bind(port);
  accepter.listen();
  seguirAceptando = true;
}

void Listener::run(){
  try{
    while (seguirAceptando) {
      Socket cliente = accepter.accept();
      organizador.agregarJugador(std::move(cliente));
    }
  } catch(const ExcepcionSocket& e){
    throw;
  }catch(const ExcepcionServer& e){
    throw;
  }
}

void Listener::stop(){
  accepter.shutdown();
  seguirAceptando = false;
}

Listener::~Listener(){
  accepter.close();
  this->join();
}
