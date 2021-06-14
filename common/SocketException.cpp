#include "SocketException.h"


SocketException::SocketException(const char* fmt, int found, const char* file, int line) noexcept:
  Exception(fmt, found, file, line){}

SocketException::SocketException(const char* fmt, const char* file, int line) noexcept:
  Exception(fmt, file, line){}

SocketException::SocketException(const char* fmt) noexcept :
  Exception(fmt){}

const char* SocketException::what() const noexcept{
  return this->msg;
}

SocketException::~SocketException(){}
