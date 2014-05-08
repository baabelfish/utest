#pragma once

#include <string>
#include <exception>

struct Exception : std::exception {
    enum class Type {
        Fatal,
        Error
    };

    Type type;
    std::string reason;
    std::string file;
    int line;
};
