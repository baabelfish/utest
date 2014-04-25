#pragma once

#include "util/assertion.hpp"
#include "util/exception.hpp"
#include "util/misc.hpp"
#include "util/package.hpp"

#define uTestPackage(...) static Package pkg(__FILE__, __VA_ARGS__)
#define describe(...) uTest::_describe(__VA_ARGS__)
#define it(...) uTest::_it(__VA_ARGS__)

namespace {
    struct Description {
        std::string description;
        std::function<void()> func;
    };

class uTest {
    static int Failed;
    static std::string CurrentDescription;
    static std::string CurrentTest;

public:
    static std::string lineNumber(int number) {
        if (number > 0) { return " ( " + std::to_string(number) + ")"; }
        return "";
    }

    static void printHeader() {
        std::cerr
            << "[" << Package::CurrentFile << "] "
            << Color::WHITE
            << "(" << CurrentDescription
            << " | " << CurrentTest
            << ") ";
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

    static void _describe(std::string description, std::function<void()> f) {
        CurrentDescription = description;
        f();
    }

    static void _it(std::string description, std::function<void()> f) {
        CurrentTest = description;
        try {
            f();
        } catch (Exception& e) {
            ++Failed;
            if (e.type == Type::Error) {
                printAssertion(e);
            } else {
                printAssertion(e);
                throw e;
            }
        }
    }
};

int uTest::Failed = 0;
std::string uTest::CurrentDescription;
std::string uTest::CurrentTest;
}

#define Warn(CONDITION)\
if (!(CONDITION)) {\
    uTest::printHeader();\
    std::cerr\
        << Color::YELLOW + "Warning: " + Color::DEFAULT\
        << Color::DEFAULT\
        << "\"" << (#CONDITION) << "\"" \
        << uTest::lineNumber(__LINE__)\
        << std::endl;\
}

#define uTestRun() int main() {}
