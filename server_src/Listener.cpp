#include "Listener.h"
#include <syslog.h>
#include <string>
#include <utility>

Listener::Listener(const std::string& port){
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
    syslog(LOG_INFO, "Error: %s", e.what());
  }catch(const ExcepcionServer& e){
    syslog(LOG_INFO, "Error: %s", e.what());
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
