#include "Listener.h"


Listener::Listener(std::string& port){
  accepter.bind(port);
  accepter.listen();
  keep_accepting = true;
}

void Listener::run(){
  try{
    while (keep_accepting) {
      Socket client = accepter.accept();
      organizador.addPlayer(std::move(client));
    }
  } catch(std::exception& e){ //Ver si cambio exception por socketException
    std::cout << e.what() << std::endl; //Cambiar por un Syslog
  }
}

void Listener::stop(){
  accepter.shutdown(); //Falta implementar
  keep_accepting = false;
}

Listener::~Listener(){
  //Aca deberia hacer el close?
  accepter.close();
}
