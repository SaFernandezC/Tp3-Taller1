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
  } catch (const SocketException& e){
    std::cout << e.what() << std::endl;
  } catch (std::exception& e){
    std::cout << e.what() << std::endl;
  } catch (...){
    std::cout << "Error desconocido" << std::endl;
  }

  return 0;
}
