#pragma once

#include <string>
#include <functional>
#include <iostream>
#include "exception.hpp"
#include "misc.hpp"
#include <chrono>

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
        if (e.type == Exception::Type::Error) { std::cerr << Color::RED << "Assertion"; }
        else if (e.type == Exception::Type::Timing) { std::cerr << Color::MAGENTA << "Timing"; }
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
            if (e.type != Exception::Type::Fatal) {
                printAssertion(e);
            } else {
                printAssertion(e);
                throw e;
            }
        }
    }

    template<typename F, typename G>
    static void fasterThan(std::string file, int line, std::string description, F f, G g) {
        const std::size_t Times = 100;
        it(description, [&]{
            std::chrono::steady_clock::time_point f_start(std::chrono::steady_clock::now());
            for (std::size_t i = 0; i < Times; ++i) {
                f();
            }
            std::chrono::steady_clock::time_point f_delta(std::chrono::steady_clock::now() - f_start);
            std::chrono::steady_clock::time_point g_start(std::chrono::steady_clock::now());
            for (std::size_t i = 0; i < Times; ++i) {
                g();
            }
            std::chrono::steady_clock::time_point g_delta(std::chrono::steady_clock::now() - g_start);
            if (f_delta > g_delta) {
                Exception e;
                e.type = Exception::Type::Timing;
                e.reason = "g is faster than f";
                e.file = file;
                e.line = line;
                throw e;
            }
        });
    }

};

int ut::Failed = 0;
std::string ut::CurrentDescription;
std::string ut::CurrentTest;
}
