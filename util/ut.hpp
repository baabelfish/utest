#pragma once

#include <algorithm>
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
    template<typename F>
    struct Tester {
        std::string m_file;
        int m_line;
        std::size_t m_current;
        F m_f;

        Tester(std::string file, int line, F f):
            m_file(file),
            m_line(line),
            m_current(1),
            m_f(f) {}

        template<typename R, typename... Args>
        Tester<F>& operator()(R reval, Args... args) {
            if (m_f(args...) != reval) {
                throw Exception(Exception::Type::Error,
                        "Error with case " + std::to_string(m_current),
                        m_file,
                        m_line);
            }
            ++m_current;
            return *this;
        }

        template<typename R, typename... Args>
        Tester<F>& with(R reval, Args... args) {
            return (*this)(reval, args...);
        }
    };

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
        else if (e.type == Exception::Type::Logic) { std::cerr << Color::MAGENTA << Color::BOLD << Color::UNDERLINE << "Logic"; }
        else { std::cerr << Color::BOLD << Color::RED << "Fatal assertion"; }

        std::cerr << Color::DEFAULT;

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
            if (e.type != Exception::Type::Fatal && e.type != Exception::Type::Logic) {
                printAssertion(e);
            } else {
                printAssertion(e);
                throw e;
            }
        }
    }

    template<typename F>
    static Tester<F> bomb(std::string file, int line, F f) { return Tester<F>(file, line, f); }

    template<typename F, typename G>
    static void isFasterThan(std::string file, int line, std::string description, F f, G g, std::size_t times = 100) {
        it(description, [&]{
            std::chrono::steady_clock::time_point f_start(std::chrono::steady_clock::now());
            for (std::size_t i = 0; i < times; ++i) {
                f();
            }
            std::chrono::steady_clock::time_point f_delta(std::chrono::steady_clock::now() - f_start);
            std::chrono::steady_clock::time_point g_start(std::chrono::steady_clock::now());
            for (std::size_t i = 0; i < times; ++i) {
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
