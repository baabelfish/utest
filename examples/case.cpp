#include "../sts.hpp"

SUITE() {
    // Reserve
    std::string* temp = new std::string("temp");

    // Test
    TEST("math?", [&] {
        WARN(1 == 1);
    });
    TEST("temp should be temp", [&] {
        ASSERT(*temp == "temp");
    });
    TEST("derp", [] {
        ASSERT(true);
    });

    // Cleanup
    delete temp;
}
