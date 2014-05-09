#pragma once

#include "util/assertion.hpp"
#include "util/exception.hpp"
#include "util/misc.hpp"
#include "util/ut.hpp"
#include <vector>

template<typename F>
void describe(std::string description, F f) { ut::describe(description, f); }

template<typename F>
void it(std::string description, F f) { ut::it(description, f); }

#define isFasterThan(...) ut::isFasterThan(__FILE__, __LINE__, __VA_ARGS__)

#define bomb(...) ut::bomb(__FILE__, __LINE__, __VA_ARGS__)

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

#define yTestRun() int main() {\
    ut::printTotals();\
}
