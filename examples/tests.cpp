#include "../utest.hpp"

uTestPackage basic([]{
    describe("asd", []{
        it("qwe", []{
            Assert()
                .isTrue(true)
                .isTrue(false)
                .isFalse(true)
                .isFalse(false)
                .isEqual(true, true);
        });
    });
});

uTestRun();
