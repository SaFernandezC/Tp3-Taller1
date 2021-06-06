#include "SocketException.h"


SocketException::SocketException(const char* fmt, int found, int line) noexcept:
  Exception(fmt, found, line){}

SocketException::SocketException(const char* fmt) noexcept :
  Exception(fmt){}

const char* SocketException::what() const noexcept{
  return this->msg;
}

SocketException::~SocketException(){}
