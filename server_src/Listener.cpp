#include "Listener.h"
#include <syslog.h>
#include <string>
#include <utility>

Listener::Listener(const std::string& port){
  aceptador.bind(port);
  aceptador.listen();
  seguirAceptando = true;
}

void Listener::run(){
  try{
    while (seguirAceptando) {
      Socket cliente = aceptador.accept();
      organizador.agregarJugador(std::move(cliente));
    }
  } catch(const ExcepcionSocket& e){
    syslog(LOG_INFO, "Error: %s", e.what());
  }catch(const ExcepcionServer& e){
    syslog(LOG_INFO, "Error: %s", e.what());
  }
}

void Listener::stop(){
  aceptador.shutdown();
  seguirAceptando = false;
}

Listener::~Listener(){
  aceptador.close();
  this->join();
}
