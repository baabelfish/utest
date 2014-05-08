#pragma once

#include <string>
#include <exception>

enum class Type {
    Fatal,
    Error
};

struct Exception : std::exception {
    Type type;
    std::string reason;
    std::string file;
    int line;
};
