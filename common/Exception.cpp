#include "Exception.h"

Exception::Exception(const char* fmt, ...) noexcept{
  int _errno = errno;

  va_list args;
  va_start(args, fmt);
  int s = vsnprintf(this->msg, BUF_LEN, fmt, args);
  va_end(args);
  strncpy(msg + s, strerror(_errno), BUF_LEN - s);
  msg[BUF_LEN - 1] = 0;
}

const char* Exception::what() const noexcept{
  return this->msg;
}

Exception::~Exception() noexcept {}
