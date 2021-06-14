#include "ServerException.h"

ServerException::ServerException(const char* fmt, int found, const char* file, int line) noexcept:
  Exception(fmt, found, file, line){}

ServerException::ServerException(const char* fmt, const char* file, int line) noexcept:
  Exception(fmt, file, line){}

ServerException::ServerException(const char* fmt) noexcept :
  Exception(fmt){}

const char* ServerException::what() const noexcept{
  return this->msg;
}

ServerException::~ServerException(){}
