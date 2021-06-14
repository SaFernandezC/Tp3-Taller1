#include "Listener.h"

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
  } catch(std::exception& e){ //Ver si cambio exception por socketException
    std::cout << e.what() << std::endl; //Cambiar por un Syslog
  }
}

void Listener::stop(){
  accepter.shutdown();
  seguirAceptando = false;
}

Listener::~Listener(){
  accepter.close();
}
