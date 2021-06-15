#include <iostream>
#include <syslog.h>
#include <string>
#include "Listener.h"

#define ARGS_ESPERADOS 2
#define IGUAL 0

int main(int argc, char const *argv[]) {
  if (argc != ARGS_ESPERADOS) {
    std::cout << "Para ejecutar --> ./server <port>" << std::endl;
    return -1;
  }

  std::string port(argv[1]);
  
  try{
    Listener listener(port);
    listener.start();

    std::string command = "";
    std::cin >> command;
    while (command.compare("q") != IGUAL) {
      std::cout << "Comando invalido" << std::endl;
      std::cin >> command;
    }
    listener.stop();
  } catch(const ExcepcionSocket& e){
    syslog(LOG_INFO, "Error: %s", e.what());
  }catch(const ExcepcionServer& e){
    syslog(LOG_INFO, "Error: %s", e.what());
  } catch(...){
    syslog(LOG_INFO, "Error desconocido");
  }

  closelog();
  return 0;
}
