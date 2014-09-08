#pragma once

#include "exception.hpp"
#include "globals.hpp"

#define Assert() Assertion(false, __FILE__, __LINE__)
#define Fatal() Assertion(true, __FILE__, __LINE__)

class Assertion {
    bool m_fatal;
    std::string m_file;
    int m_line;

    auto throwEx(std::string type) {
        Exception ex;
        ex.type = m_fatal ? Exception::Type::Fatal : Exception::Type::Error;
        ex.file = m_file;
        ex.line = m_line;
        ex.reason = type;
        return ex;
    }

public:
    Assertion(bool fatal = false):
        Assertion(fatal, "", -1) {}

    Assertion(bool fatal, std::string file, int line):
        m_fatal(fatal),
        m_file(file),
        m_line(line) {
            ++ytest::globals::results().total_assertions;
        }

    virtual ~Assertion() {}

    template<typename C, typename T = typename C::value_type, typename F>
    Assertion& forNone(const C& c, F f) {
        for (auto& x : c) {
            if (f(x)) throw throwEx("forNone");
        }
        return *this;
    }

    template<typename C, typename F>
    Assertion& forSome(const C& c, F f) {
        for (auto& x : c) {
            if (f(x)) return *this;
        }
        throw throwEx("forSome");
        return *this;
    }

    template<typename C, typename F>
    Assertion& forAll(const C& c, F f) {
        for (auto& x : c) {
            if (!f(x)) throw throwEx("forAll");
        }
        return *this;
    }

    template<typename T>
    Assertion& isEqual(const T& a, const T& b) {
        if (a == b) return *this;
        throw throwEx("isEqual");
    }

    template<typename T>
    Assertion& isNotEqual(const T& a, const T& b) {
        if (a != b) return *this;
        throw throwEx("isNotEqual");
    }

    template<typename T, typename Y>
    Assertion& isLessThan(const T& a, const Y& b) {
        if (a < static_cast<T>(b)) return *this;
        throw throwEx("isLessThan");
    }

    template<typename T, typename Y>
    Assertion& isSameOrLessThan(const T& a, const Y& b) {
        if (a <= static_cast<T>(b)) return *this;
        throw throwEx("isSameOrLessThan");
    }

    template<typename T, typename Y>
    Assertion& isSameOrGreaterThan(const T& a, const Y& b) {
        if (a >= static_cast<T>(b)) return *this;
        throw throwEx("isSameOrGreaterThan");
    }

    template<typename T, typename Y>
    Assertion& isGreaterThan(const T& a, const Y& b) {
        if (a > static_cast<T>(b)) return *this;
        throw throwEx("isGreaterThan");
    }

    template<typename T, typename Y>
    Assertion& isEqual(const T& a, const Y& b) {
        if (a == static_cast<T>(b)) return *this;
        throw throwEx("isEqual");
    }

    template<typename T, typename Y>
    Assertion& isNotEqual(const T& a, const Y& b) {
        if (a != static_cast<T>(b)) return *this;
        throw throwEx("isNotEqual");
    }

    template<typename T>
    Assertion& isTrue(const T& a) {
        if (a == true) return *this;
        throw throwEx("isTrue");
    }

    template<typename T>
    Assertion& isFalse(const T& a) {
        if (a == false) return *this;
        throw throwEx("isFalse");
    }
};
