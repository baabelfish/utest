#pragma once

#include "util/assertion.hpp"
#include "util/exception.hpp"
#include "util/misc.hpp"
#include "util/properties.hpp"
#include <vector>

template<typename F>
void describe(std::string description, F f) { ytest::describe(description, f); }

template<typename F>
void it(std::string description, F f) { ytest::it(description, f); }

#define isFasterThan(...) ytest::isFasterThan(__FILE__, __LINE__, __VA_ARGS__)

#define bomb(...) ytest::bomb(__FILE__, __LINE__, __VA_ARGS__)

#define Warn(CONDITION)\
if (!(CONDITION)) { ytest::print::warning(#CONDITION, __FILE__, __LINE__); }

#define yTestExec()\
int main(int argc, char* argv[]) {\
    return ytest::exec(argc, argv);\
}
