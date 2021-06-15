#include "ExcepcionServer.h"

ExcepcionServer::ExcepcionServer(const char* fmt, int found, const char* file, int line) noexcept:
  Excepcion(fmt, found, file, line){}

ExcepcionServer::ExcepcionServer(const char* fmt, const char* file, int line) noexcept:
  Excepcion(fmt, file, line){}

ExcepcionServer::ExcepcionServer(const char* fmt) noexcept :
  Excepcion(fmt){}

const char* ExcepcionServer::what() const noexcept{
  return this->msg;
}

ExcepcionServer::~ExcepcionServer(){}
