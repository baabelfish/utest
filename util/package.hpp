#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include "misc.hpp"

namespace {
class Package {
public:
    static std::string CurrentFile;

    Package(std::string file, std::function<void()> p) {
        CurrentFile = file;
        p();
    }
};

std::string Package::CurrentFile;
}
