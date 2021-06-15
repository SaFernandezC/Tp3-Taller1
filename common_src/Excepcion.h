#ifndef EXCEPCION_H
#define EXCEPCION_H

#include <iostream>
#include <errno.h>
#include <cstdio>
#include <typeinfo>
#include <cstdarg>
#include <string.h>

#define BUF_LEN 256

class Excepcion : public std::exception {
    protected:
        char msg[BUF_LEN];
    public:
        explicit Excepcion(const char* fmt, ...) noexcept;

        virtual const char *what() const noexcept;

        virtual ~Excepcion() noexcept;
};

#endif
