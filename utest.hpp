#pragma once

#include "util/assertion.hpp"
#include "util/exception.hpp"
#include "util/misc.hpp"
#include "util/ut.hpp"

struct uTestPackage {
    uTestPackage(std::function<void()> p) { p(); }
};

template<typename F>
void describe(std::string d, F f) { ut::describe(d, f); }

template<typename F>
void it(std::string d, F f) { ut::it(d, f); }

#define Warn(CONDITION)\
if (!(CONDITION)) {\
    std::cerr\
        << "[" << __FILE__ << "] "\
        << Color::YELLOW + "Warning: " + Color::DEFAULT\
        << Color::DEFAULT\
        << "\"" << (#CONDITION) << "\"" \
        << ut::lineNumber(__LINE__)\
        << std::endl;\
}

#define uTestRun() int main() {}
