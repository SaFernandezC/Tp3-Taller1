#include <iostream>
#include "Cliente.h"

int main(int argc, char const *argv[]) {
  if (argc != 3) {
    std::cout << "Para ejecutar --> ./client <host> <port>" << std::endl;
    return -1;
  }

  std::string host(argv[1]);
  std::string port(argv[2]);

  try{
    Cliente cliente(host, port);
    cliente.run();
  }catch(std::exception& e){
    printf("Error en el cliente en linea");//Cambiar por syslog o exception
  }


  return 0;
}
