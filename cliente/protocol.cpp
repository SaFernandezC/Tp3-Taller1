#include "Protocol.h"


Protocol::Protocol(const std::string& host, const std::string& port){
  try{
    client_socket.connect(host, port);
  } catch(std::exception& e){ //Ver si cambio exception por socketException
    std::cout << e.what() << std::endl; //Cambiar por un Syslog
  }
}


void Protocol::run(){
  
}



Protocol::~Protocol(){
  client_socket.shutdown();
  client_socket.close();
}
