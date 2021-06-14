#ifndef SERVER_EXCEPTION_H
#define SERVER_EXCEPTION_H

#include "../common/Exception.h"

class ServerException : public Exception {
    public:
        explicit ServerException(const char* fmt, int found, const char* file, int line) noexcept;

        explicit ServerException(const char* fmt, const char* file, int line) noexcept;

        explicit ServerException(const char* fmt) noexcept;

        const char* what() const noexcept override;

        ~ServerException() noexcept;
};

#endif
