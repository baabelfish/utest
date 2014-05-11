#pragma once

#include "globals.hpp"
#include <functional>

struct yTestPackage {
    yTestPackage(std::function<void()> p) {
        ++ytest::globals::results().total_packages;
        p();
    }
};
