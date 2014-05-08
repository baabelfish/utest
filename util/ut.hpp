#pragma once

#include <string>
#include <functional>
#include <iostream>
#include "exception.hpp"
#include "misc.hpp"

namespace {
    struct Description {
        std::string description;
        std::function<void()> func;
    };

class ut {
    static int Failed;
    static std::string CurrentDescription;
    static std::string CurrentTest;

public:
    static std::string lineNumber(int number) {
        if (number > 0) { return " ( " + std::to_string(number) + ")"; }
        return "";
    }

    static void printHeader(std::string file, std::string description, std::string current_test) {
        std::cerr
            << "[" << file << "] "
            << Color::WHITE
            << "(" << description
            << " | " << current_test
            << ") ";
    }

    static void printAssertion(Exception& e) {
        printHeader(e.file, CurrentDescription, CurrentTest);
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

    static void describe(std::string description, std::function<void()> f) {
        CurrentDescription = description;
        f();
    }

    static void it(std::string description, std::function<void()> f) {
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

int ut::Failed = 0;
std::string ut::CurrentDescription;
std::string ut::CurrentTest;
}
