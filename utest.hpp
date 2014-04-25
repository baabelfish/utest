#pragma once

#include "assertion.hpp"
#include "exception.hpp"
#include "runner.hpp"
#include "misc.hpp"

static int _FAILED = 0;
static std::vector<Runner> _DESCRIPTIONS;
static std::string _TFILE = "";
static std::string _DESCRIPTION = "";

static std::string lineNumber(int number) {
    if (number > 0) { return " ( " + std::to_string(number) + ")"; }
    return "";
}

static void printHeader() {
    std::cerr
        << "[" << _TFILE << "] "
        << Color::WHITE
        << "(" << Runner::current();
    if (!_DESCRIPTION.empty()) { std::cerr << " | " << _DESCRIPTION; }
    std::cerr << ") ";
}

static void printAssertion(Exception& e) {
    printHeader();
    if (e.type == Type::Error) { std::cerr << Color::RED << "Assertion"; }
    else { std::cerr << Color::BOLD << Color::RED << "Fatal assertion"; }
    if (!e.reason.empty()) {
        std::cerr
            << ": "
            << Color::DEFAULT
            << e.reason;
    }
    std::cerr << lineNumber(e.line) << std::endl;
}

void describe(std::string description, std::function<void()> f) {
    _DESCRIPTIONS.emplace_back(description, f);
}

void it(std::string description, std::function<void()> f) {
    _DESCRIPTION = description;
    try {
        f();
    } catch (Exception& e) {
        ++_FAILED;
        if (e.type == Type::Error) {
            printAssertion(e);
        } else {
            printAssertion(e);
            throw e;
        }
    }
}

/**
 * @brief Prints a warning when untrue.
 *
 * @param CONDITION Expression to test.
 *
 * @return
 */
#define Warn(CONDITION)\
if (!(CONDITION)) {\
    printHeader();\
    std::cerr\
        << Color::YELLOW + "Warning: " + Color::DEFAULT\
        << Color::DEFAULT\
        << "\"" << (#CONDITION) << "\"" \
        << lineNumber(__LINE__)\
        << std::endl;\
}

/**
 * @brief An initializer for the test. Only one per file.
 *
 */
#define uTest()\
void _INITIALIZE();\
int main() {\
    _TFILE = __FILE__;\
    _INITIALIZE();\
    for (auto& x : _DESCRIPTIONS) {\
        if (!x.run()) return 1;\
    }\
    return _FAILED != 0;\
}\
void _INITIALIZE()
