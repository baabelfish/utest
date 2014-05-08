#pragma once

#include <string>
#include <exception>

struct Exception : std::exception {
    enum class Type {
        Fatal,
        Timing,
        Error
    };

    Type type;
    std::string reason;
    std::string file;
    int line;
};
