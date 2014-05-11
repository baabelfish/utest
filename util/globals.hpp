#pragma once

#include <vector>
#include <functional>
#include <string>

namespace ytest {
namespace globals {

struct Description {
    std::string description;
    std::function<void()> func;

    Description(std::string description, std::function<void()> func):
        description(description),
        func(func) {}
};

struct Result {
    std::size_t total_packages;
    std::size_t total_descriptions;
    std::size_t total_its;
    std::size_t total_assertions;
    std::size_t failed_assertions;
};

inline std::vector<Description>& tests() {
    static std::vector<Description> t;
    return t;
}

inline Result& results() {
    static Result t;
    return t;
}

} // namespace globals
} // namespace ytest

