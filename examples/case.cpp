#include "../utest.hpp"

// One unit
UNIT() {
    // One method of the unit
    METHOD("init", {
        // One testcase for the method
        TEST("Not true", [] {
            ASSERT(true);
        });
    });
    METHOD("clear", {
        // Init
        std::string* test = new std::string("hello");

        // Test
        TEST("Is math", [&] {
            WARN(2 == 1);
        });
        TEST("Should be", [&] {
            ASSERT(*test == "hello");
        });
        TEST("Might not be", [] {
            ASSERT(false);
        });

        // Cleanup
        delete test;
    });
}
