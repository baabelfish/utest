#pragma once

#include <string>
#include <exception>

struct Exception : std::exception {
    enum class Type {
        Logic,
        Fatal,
        Timing,
        Error
    };

    Type type;
    std::string reason;
    std::string file;
    int line;

    Exception():
        Exception(Type::Logic, "", "", -1) {}

    Exception(Type t, std::string r):
        Exception(t, r, "", -1) {}

    Exception(Type t, std::string r, std::string f, int l):
        type(t),
        reason(r),
        file(f),
        line(l) {}
};
