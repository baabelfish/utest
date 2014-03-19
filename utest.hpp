#pragma once

#include "misc.hpp"
#include "runner.hpp"

static std::vector<Runner> _RUNNERS;

void test(std::function<void()> f) {
    _RUNNERS.emplace_back("", f);
}

static const std::string _PREFIX = "[" + std::string(__FILE__) + "]";

void printLine(std::size_t line, std::string condition, std::string effect) {
    std::cout << _PREFIX << ":" << line << ": \"" << Color::BOLD << Color::GREEN << condition << Color::DEFAULT << "\" -> " << effect << Color::DEFAULT << std::endl;
}

#define Assert(CONDITION)\
if (!(CONDITION)) {\
    printLine(__LINE__, (#CONDITION), Color::RED + Color::BOLD + "FAILURE");\
    throw sts::Fatal(#CONDITION);\
}

#define Warn(CONDITION)\
if (!(CONDITION)) {\
    printLine(__LINE__, (#CONDITION), Color::YELLOW + Color::BOLD + "WARNING");\
}

#define Utest()\
void _INITIALIZE();\
int main() {\
    Runner::Status status{0, 0};\
    _INITIALIZE();\
    for (auto& x : _RUNNERS) {\
        if (!x.run()) return 1;\
        status = status + x.status();\
    }\
    std::cout << std::endl;\
    return 0;\
}\
void _INITIALIZE()
