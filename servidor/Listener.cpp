#include "Listener.h"
// #include <syslog>

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
  } catch(std::exception& e){ //Puede ser socket o server exception
    std::cout << e.what() << std::endl;
    // syslog(LOG_INFO, "Error: %s", e.what());
  }
}

void Listener::stop(){
  accepter.shutdown(); //De aca sale el invalid_argument
  seguirAceptando = false;
}

Listener::~Listener(){
  accepter.close();
  this->join();
}
