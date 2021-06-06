#include "Accepter.h"


Accepter::Accepter(Socket& server_sock):server_socket(server_sock){
  this->keep_accepting = true;
}

void Accepter::run(){


  try{
    while (keep_accepting) {
      Socket client = server_socket.accept();
      organizador.addClient(std::move(client));
    }
  } catch(std::exception& e){ //Ver si cambio exception por socketException
    std::cout << e.what() << std::endl; //Cambiar por un Syslog
  }



}

void Accepter::stop(){
  keep_accepting = false;
}

Accepter::~Accepter(){

}
