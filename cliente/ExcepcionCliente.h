#ifndef EXCEPCION_CLIENTE_H
#define EXCEPCION_CLIENTE_H

#include "../common/Excepcion.h"

class ExcepcionCliente : public Excepcion {
    public:
        explicit ExcepcionCliente(const char* fmt, int found,
                            const char* file, int line) noexcept;

        explicit ExcepcionCliente(const char* fmt,
                            const char* file, int line) noexcept;

        explicit ExcepcionCliente(const char* fmt) noexcept;

        const char* what() const noexcept override;

        ~ExcepcionCliente() noexcept;
};

#endif
