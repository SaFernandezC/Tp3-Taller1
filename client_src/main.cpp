#include <iostream>
#include <string>
#include <syslog.h>
#include "Cliente.h"

#define ARGC_ESPERADOS 3

int main(int argc, char const *argv[]) {
  if (argc != ARGC_ESPERADOS) {
    std::cout << "Para ejecutar --> ./client <host> <port>" << std::endl;
    return -1;
  }

  std::string host(argv[1]);
  std::string port(argv[2]);

  try{
    Cliente cliente(host, port);
    cliente.run();
  } catch(const ExcepcionSocket& e){
    syslog(LOG_INFO, "Error: %s", e.what());
  } catch(std::exception& e){
    syslog(LOG_INFO, "Error: %s", e.what());
  } catch(...){
    syslog(LOG_INFO, "Error desconocido\n");
  }

  closelog();
  return 0;
}
