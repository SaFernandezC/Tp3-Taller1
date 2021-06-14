#ifndef SOCKET_EXCEPTION_H
#define SOCKET_EXCEPTION_H

#include "Exception.h"

class SocketException : public Exception {
    public:
        explicit SocketException(const char* fmt, int found, const char* file, int line) noexcept;

        explicit SocketException(const char* fmt, const char* file, int line) noexcept;

        explicit SocketException(const char* fmt) noexcept;

        const char* what() const noexcept override;

        ~SocketException() noexcept;
};

#endif
