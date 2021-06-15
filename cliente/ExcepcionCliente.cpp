#include "ExcepcionCliente.h"


ExcepcionCliente::ExcepcionCliente(const char* fmt, int found,
                  const char* file, int line) noexcept:
  Excepcion(fmt, found, file, line){}

ExcepcionCliente::ExcepcionCliente(const char* fmt,
                  const char* file, int line) noexcept:
  Excepcion(fmt, file, line){}

ExcepcionCliente::ExcepcionCliente(const char* fmt) noexcept :
  Excepcion(fmt){}

const char* ExcepcionCliente::what() const noexcept{
  return this->msg;
}

ExcepcionCliente::~ExcepcionCliente(){}
