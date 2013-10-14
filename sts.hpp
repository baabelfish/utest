#include <iostream>
#include <functional>
#include <tuple>
#include <string>
#include <vector>

#define HCOMBINE(a,b) a ## b
#define COMBINE(a,b) HCOMBINE(a,b)
#define TNAME() COMBINE(a,__LINE__)
#define INAME() COMBINE(c,__LINE__)

#define SUITE()\
    static sts::TestRunner Sts(__FILE__);\
    int main()

#define TEST(NAME, FUNC)\
    Sts.run(NAME, FUNC)

#define WARN(CONDITION)\
    if (!(CONDITION)) Sts.warn(#CONDITION, __FILE__, __LINE__)

#define ASSERT(CONDITION)\
    if (!(CONDITION)) throw sts::Assertion(#CONDITION, __FILE__, __LINE__)


namespace sts {
namespace Color {
const std::string DEFAULT = "\033[0m";
const std::string BOLD = "\033[1m";
const std::string BLACK = "\033[30m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";
const std::string WHITE = "\033[37m";
const std::string BACKGROUND_BLACK = "\033[40m";
const std::string BACKGROUND_RED = "\033[41m";
const std::string BACKGROUND_GREEN = "\033[42m";
const std::string BACKGROUND_YELLOW = "\033[43m";
const std::string BACKGROUND_BLUE = "\033[44m";
const std::string BACKGROUND_MAGENTA = "\033[45m";
const std::string BACKGROUND_CYAN = "\033[46m";
const std::string BACKGROUND_WHITE = "\033[47m";
}

namespace Info {
const std::string WARN_TEXT = Color::YELLOW + " Warning " + Color::DEFAULT;
const std::string ASSERT_TEXT = Color::BOLD + Color::RED + " Failure " + Color::DEFAULT;
const std::string LEFT_NOTIFY = Color::WHITE + "» " + Color::DEFAULT;
const std::string RIGHT_NOTIFY = Color::WHITE + " «" + Color::DEFAULT;
} // namespace Info

struct Assertion : std::runtime_error {
    int m_line;
    std::string m_file;

    Assertion(std::string condition, std::string file, int line):
        std::runtime_error(condition),
        m_line(line),
        m_file(file) { }
};

class TestRunner {
public:
    TestRunner(std::string name):
        m_name(name),
        m_current_testfile(name),
        m_current_test(1),
        m_successful(0),
        m_fatal(0),
        m_errors(0),
        m_warnings(0) {
    }

    virtual ~TestRunner() {
        int total = m_successful + m_fatal + m_errors;
        std::cout << m_name;
        if (total == m_successful) {
            std::cout << Color::GREEN << " Success";
        } else {
            std::cout << " ("
                << Color::BOLD << Color::GREEN << m_successful
                << " " << Color::RED << m_fatal << Color::DEFAULT
                << " " << Color::RED << m_errors
                << " " << Color::YELLOW << m_warnings
                << Color::DEFAULT << ")";
            std::cout << Color::BOLD << Color::RED << " Fail";
        }
        std::cout << Color::DEFAULT << std::endl;
    }

    void run(std::string name, std::function<void()> func) {
        m_current_testfile = name;
        try {
            func();
            ++m_successful;
        }
        catch(Assertion e) {
            std::cout << e.m_file << "@" << name << ":" << e.m_line
                << Info::ASSERT_TEXT
                << Color::DEFAULT << Info::LEFT_NOTIFY << e.what() << Info::RIGHT_NOTIFY
                << Color::DEFAULT << std::endl;
            ++m_errors;
        }
        catch(...) {
            std::cout << "Unexpected error in " << name << "." << std::endl;
            ++m_fatal;
        }
        ++m_current_test;
    }

    void warn(std::string condition, std::string file, int line) {
        std::cout << file << "@" << m_current_testfile << ":" << line << Info::WARN_TEXT << Info::LEFT_NOTIFY << condition << Info::RIGHT_NOTIFY << std::endl;
        ++m_warnings;
    }

private:
    std::string m_name;
    std::string m_current_testfile;
    int m_current_test;
    int m_successful;
    int m_fatal;
    int m_errors;
    int m_warnings;
};
} // namespace sts
