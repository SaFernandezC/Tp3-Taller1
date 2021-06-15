#ifndef EXCEPCION_SOCKET_H
#define EXCEPCION_SOCKET_H

#include "Excepcion.h"

class ExcepcionSocket : public Excepcion {
    public:
        explicit ExcepcionSocket(const char* fmt, int found,
                          const char* file, int line) noexcept;

        explicit ExcepcionSocket(const char* fmt,
                          const char* file, int line) noexcept;

        explicit ExcepcionSocket(const char* fmt) noexcept;

        const char* what() const noexcept override;

        ~ExcepcionSocket() noexcept;
};

#endif
