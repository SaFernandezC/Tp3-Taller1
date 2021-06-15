#include "ExcepcionSocket.h"


ExcepcionSocket::ExcepcionSocket(const char* fmt, int found,
                  const char* file, int line) noexcept:
  Excepcion(fmt, found, file, line){}

ExcepcionSocket::ExcepcionSocket(const char* fmt,
                  const char* file, int line) noexcept:
  Excepcion(fmt, file, line){}

ExcepcionSocket::ExcepcionSocket(const char* fmt) noexcept :
  Excepcion(fmt){}

const char* ExcepcionSocket::what() const noexcept{
  return this->msg;
}

ExcepcionSocket::~ExcepcionSocket(){}
