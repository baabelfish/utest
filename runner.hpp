#pragma once

#include "ds.hpp"
#include <vector>
#include <string>

class Runner {
public:
    struct Status {
        std::size_t warnings;
        std::size_t succesful;
        Status operator+(const Status& other) {
            return {warnings + other.warnings, succesful + other.succesful};
        }
    };

    Runner(std::string task, std::function<void()> test):
        m_status({0, 0}),
        m_test(test),
        m_task(task) {}

    bool run() {
        try {
            m_test();
        } catch(std::runtime_error& e) {
            return false;
        }
        ++m_status.succesful;
        return true;
    }

    Status status() const {
        return m_status;
    }

private:
    Status m_status;
    std::function<void()> m_test;
    std::string m_task;
};
