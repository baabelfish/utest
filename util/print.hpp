#pragma once

#include <string>
#include <iostream>
#include "exception.hpp"
#include "misc.hpp"
#include "globals.hpp"

namespace ytest {
namespace print {

static std::string lineNumber(int number) {
    if (number > 0) { return " ( " + std::to_string(number) + ")"; }
    return "";
}

static void header(std::string file, std::string description, std::string current_test) {
    std::cerr
        << "[" << file << "] "
        << Color::WHITE
        << "(" << description
        << " | " << current_test
        << ") ";
}

inline void assertion(Exception& e, std::string description, std::string test) {
    header(e.file, description, test);
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

inline void warning(std::string condition, std::string file, int line) {
    std::cerr
        << "[" << file << "] "
        << Color::YELLOW + "Warning: " + Color::DEFAULT
        << Color::DEFAULT
        << "\"" << condition << "\""
        << lineNumber(line)
        << std::endl;
}

inline void totals(ytest::globals::Result results) {
    if (results.failed_assertions == 0) { std::cerr << Color::GREEN; }
    else { std::cerr << Color::RED; }
    std::cerr<< "Tested "
        << results.total_packages << " packages with "
        << results.total_assertions - results.failed_assertions
        << "/" << results.total_assertions << " succesful assertions."
        << Color::DEFAULT
        << std::endl;
}

} // namespace print
} // namespace ytest

