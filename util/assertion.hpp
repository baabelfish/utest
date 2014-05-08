#pragma once

#include "exception.hpp"

#define Assert() Assertion(false, __FILE__, __LINE__)
#define Fatal() Assertion(true, __FILE__, __LINE__)

class Assertion {
    bool m_fatal;
    std::string m_file;
    int m_line;

    void throwEx(std::string type) {
        Exception ex;
        ex.type = m_fatal ? Exception::Type::Fatal : Exception::Type::Error;
        ex.file = m_file;
        ex.line = m_line;
        ex.reason = type;
        throw ex;
    }

public:
    Assertion(bool fatal = false):
        Assertion(fatal, "", -1) {}

    Assertion(bool fatal, std::string file, int line):
        m_fatal(fatal),
        m_file(file),
        m_line(line) {}

    virtual ~Assertion() {}

    template<typename C, typename T = typename C::value_type, typename F>
    Assertion& forNone(const C& c, F f) {
        for (auto& x : c) {
            if (f(x)) throwEx("forNone");
        }
        return *this;
    }

    template<typename C, typename F>
    Assertion& forSome(const C& c, F f) {
        for (auto& x : c) {
            if (f(x)) return *this;
        }
        throwEx("forSome");
        return *this;
    }

    template<typename C, typename F>
    Assertion& forAll(const C& c, F f) {
        for (auto& x : c) {
            if (!f(x)) throwEx("forAll");
        }
        return *this;
    }

    template<typename T>
    Assertion& isEqual(const T& a, const T& b) {
        if (a != b) { throwEx("isEqual"); }
        return *this;
    }

    template<typename T>
    Assertion& isNotEqual(const T& a, const T& b) {
        if (a == b) { throwEx("isNotEqual"); }
        return *this;
    }

    template<typename T>
    Assertion& isTrue(const T& a) {
        if (a == false) { throwEx("isTrue"); }
        return *this;
    }

    template<typename T>
    Assertion& isFalse(const T& a) {
        if (a == true) { throwEx("isFalse"); }
        return *this;
    }
};
