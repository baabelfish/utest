#pragma once

#include <functional>
#include <string>
#include "exception.hpp"
#include "misc.hpp"

class Runner {
public:
    Runner(std::string task, std::function<void()> test):
        m_test(test),
        m_task(task) {}

    bool run() {
        s_current = m_task;
        try {
            m_test();
        } catch(...) {
            return false;
        }
        return true;
    }

    static std::string current() { return s_current; }

private:
    std::function<void()> m_test;
    std::string m_task;
    static std::string s_current;
};

std::string Runner::s_current;
