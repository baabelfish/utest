#include <iostream>
#include <functional>
#include <tuple>
#include <string>
#include <vector>

#define HCOMBINE(a,b) a ## b
#define COMBINE(a,b) HCOMBINE(a,b)
#define TNAME() COMBINE(a,__LINE__)
#define INAME() COMBINE(c,__LINE__)

#define UNIT()\
    static sts::Unit _UNIT(__FILE__);\
    int main()

#define METHOD(NAME, FUNC)\
    _UNIT.run(NAME, [&](sts::TestRunner& _TESTRUNNER) FUNC)

#define TEST(NAME, FUNC)\
    _TESTRUNNER.run(NAME, FUNC)

#define WARN(CONDITION)\
    if (!(CONDITION)) _TESTRUNNER.warn(#CONDITION)

#define ASSERT(CONDITION)\
    if (!(CONDITION)) throw sts::Assertion(#CONDITION)


namespace sts {
namespace Color {
const std::string DEFAULT = "\033[0m";
const std::string BOLD = "\033[1m";
const std::string UNDERLINE = "\033[4m";
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
const std::string WARN_TEXT = Color::YELLOW + "Warning " + Color::DEFAULT;
const std::string ASSERT_TEXT = Color::RED + "Failure " + Color::DEFAULT;
const std::string LEFT_NOTIFY = Color::WHITE + " » " + Color::DEFAULT;
const std::string RIGHT_NOTIFY = Color::WHITE + " «" + Color::DEFAULT;
const std::string LEFT_WARN = Color::YELLOW + " » " + Color::DEFAULT;
const std::string RIGHT_WARN = Color::YELLOW + " «" + Color::DEFAULT;
const std::string LEFT_FAIL = Color::RED + " » " + Color::DEFAULT;
const std::string RIGHT_FAIL = Color::RED + " «" + Color::DEFAULT;
const std::string TOTAL_SUCCESS = Color::GREEN + "SUCCESS" + Color::DEFAULT;
const std::string TOTAL_WARNING = Color::YELLOW + "WARNING" + Color::DEFAULT;
const std::string TOTAL_FAILURE = Color::BOLD + Color::RED + "FAILURE" + Color::DEFAULT;
const std::string SEPARATOR = Color::GREEN + " - " + Color::DEFAULT;
} // namespace Info

struct Assertion : std::runtime_error {
    Assertion(std::string condition):
        std::runtime_error(condition) { }
};

struct Stats {
    int successful;
    int fatal;
    int errors;
    int warnings;

    void operator+=(Stats stats) {
        successful += stats.successful;
        fatal += stats.fatal;
        errors += stats.errors;
        warnings += stats.warnings;
    }
};

void printAssertion(std::string method, std::string mcase, std::string condition) {
    std::cout
        << Info::ASSERT_TEXT
        << Color::BOLD << Color::MAGENTA << method
        << Info::SEPARATOR
        << Color::WHITE << mcase
        << Info::LEFT_FAIL << condition << Info::RIGHT_FAIL
        << std::endl;
}

void printWarning(std::string method, std::string mcase, std::string condition) {
    std::cout
        << Info::WARN_TEXT
        << Color::BOLD << Color::MAGENTA << method
        << Info::SEPARATOR
        << Color::WHITE << mcase
        << Info::LEFT_WARN << condition << Info::RIGHT_WARN
        << std::endl;
}

void printStart(std::string unit) {
    std::cout << Color::UNDERLINE << "Unit: "
        << Color::WHITE << Color::BOLD
        << unit << Color::DEFAULT << std::endl;
}

void printTotal(Stats stats) {
    int total = stats.errors + stats.successful + stats.fatal + stats.warnings;
    std::cout << "== ";
    if (stats.successful == total) {
        std::cout << Info::TOTAL_SUCCESS;
    } else if (stats.successful + stats.warnings == total) {
        std::cout << Info::TOTAL_WARNING;
    } else {
        std::cout << Info::TOTAL_FAILURE;
    }
    std::cout << " ==" << std::endl;
}

class TestRunner {
public:
    TestRunner(std::string name):
        m_method(name),
        m_case(""),
        m_current_test(1),
        m_successful(0),
        m_fatal(0),
        m_errors(0),
        m_warnings(0) {
    }

    virtual ~TestRunner() {
    }

    void run(std::string name, std::function<void()> func) {
        m_case = name;
        try {
            func();
            ++m_successful;
        }
        catch(Assertion e) {
            printAssertion(m_method, m_case, e.what());
            ++m_errors;
        }
        catch(...) {
            std::cout << "Unexpected error in " << name << "." << std::endl;
            ++m_fatal;
        }
        ++m_current_test;
    }

    void warn(std::string condition) {
        printWarning(m_method, m_case, condition);
        ++m_warnings;
    }

    Stats stats() const {
        return { m_successful, m_fatal, m_errors, m_warnings };
    }

private:
    std::string m_method;
    std::string m_case;
    int m_current_test;
    int m_successful;
    int m_fatal;
    int m_errors;
    int m_warnings;
};

class Unit {
public:
    Unit(std::string filename) {
        printStart(filename);
    }

    ~Unit() {
        printTotal(m_total);
    }

    void run(std::string method, std::function<void(TestRunner&)> func) {
        TestRunner runner(method);
        func(runner);
        m_total += runner.stats();
    }

private:
    Stats m_total;
};
} // namespace sts
