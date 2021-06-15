#ifndef EXCEPCION_SERVER_H
#define EXCEPCION_SERVER_H

#include "../common/Excepcion.h"

class ExcepcionServer : public Excepcion {
    public:
        explicit ExcepcionServer(const char* fmt, int found, const char* file, int line) noexcept;

        explicit ExcepcionServer(const char* fmt, const char* file, int line) noexcept;

        explicit ExcepcionServer(const char* fmt) noexcept;

        const char* what() const noexcept override;

        ~ExcepcionServer() noexcept;
};

#endif
