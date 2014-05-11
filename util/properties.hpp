#pragma once

#include <algorithm>
#include <string>
#include <functional>
#include <iostream>
#include <chrono>
#include "exception.hpp"
#include "misc.hpp"
#include "globals.hpp"
#include "print.hpp"
#include "bomb.hpp"
#include "package.hpp"

namespace ytest {

static std::string CurrentDescription;
static std::string CurrentTest;

inline int exec(int argc, char* argv[]) {
    for (auto& x : ytest::globals::tests()) {
        CurrentDescription = x.description;
        try { x.func(); }
        catch (Exception& e) {
            std::cerr << "Asserts should be inside it-blocks" << std::endl;
            return 2;
        }
    }
    ytest::print::totals(ytest::globals::results());
    return 0;
}

inline void describe(std::string description, std::function<void()> f) {
    ++ytest::globals::results().total_descriptions;
    ytest::globals::tests().emplace_back(description, f);
}

inline void it(std::string description, std::function<void()> f) {
    CurrentTest = description;
    ++ytest::globals::results().total_its;

    try {
        f();
    } catch (Exception& e) {
        ++ytest::globals::results().failed_assertions;
        ytest::print::assertion(e, CurrentDescription, CurrentTest);
        if (e.type == Exception::Type::Fatal || e.type == Exception::Type::Logic) { throw e; }
    }
}

template<typename F>
static ytest::Bomb<F> bomb(std::string file, int line, F f) { return ytest::Bomb<F>(file, line, f); }

template<typename F, typename G>
static void isFasterThan(std::string file, int line, std::string description, F f, G g, float margin = 1, std::size_t times = 100) {
    it(description, [&]{
        if (margin < 0) {
            throw Exception(Exception::Type::Logic,
                            "Margin should be positive" + std::to_string(margin),
                            file,
                            line);
        }

        using std::chrono::steady_clock;
        typedef steady_clock::time_point Timepoint;

        Timepoint f_start(steady_clock::now());
        for (std::size_t i = 0; i < times; ++i) {
            f();
        }
        steady_clock::duration f_delta(steady_clock::now() - f_start);

        Timepoint g_start(steady_clock::now());
        for (std::size_t i = 0; i < times; ++i) {
            g();
        }
        steady_clock::duration g_delta(steady_clock::now() - g_start);

        if ((float)f_delta.count() > (float)g_delta.count() * margin) {
            Exception e;
            e.type = Exception::Type::Timing;
            e.reason = "g is faster than f";
            e.file = file;
            e.line = line;
            throw e;
        }
    });
}

} // namespace ytest
