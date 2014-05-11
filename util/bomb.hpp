#pragma once

#include <string>
#include "exception.hpp"

namespace ytest {

template<typename F>
class Bomb {
    std::string m_file;
    int m_line;
    std::size_t m_current;
    F m_f;

public:
    Bomb(std::string file, int line, F f):
        m_file(file),
        m_line(line),
        m_current(1),
        m_f(f) {}

    template<typename R, typename... Args>
    Bomb<F>& operator()(R reval, Args... args) {
        if (m_f(args...) != reval) {
            throw Exception(Exception::Type::Error,
                            "Error with case " + std::to_string(m_current),
                            m_file,
                            m_line);
        }
        ++m_current;
        return *this;
    }

    template<typename G, typename... Args>
    Bomb<F>& validate(G validator, Args... args) {
        if (!validator(m_f(args...))) {
            throw Exception(Exception::Type::Error,
                            "Error with case " + std::to_string(m_current),
                            m_file,
                            m_line);
        }
        ++m_current;
        return *this;
    }

    template<typename R, typename... Args>
    Bomb<F>& with(R reval, Args... args) {
        return (*this)(reval, args...);
    }
};

} // namespace ytest
