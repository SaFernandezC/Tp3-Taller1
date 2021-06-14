#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <errno.h>
#include <cstdio>
#include <typeinfo>
#include <cstdarg>
#include <string.h>

#define BUF_LEN 256

class Exception : public std::exception {
    protected:
        char msg[BUF_LEN];
    public:
        explicit Exception(const char* fmt, ...) noexcept;

        virtual const char *what() const noexcept;

        virtual ~Exception() noexcept;
};

#endif
