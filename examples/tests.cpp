#include "../utest.hpp"

uTestPackage pkg([]{
    describe("asd", []{
        it("qwe", []{
            Assert()
                .isTrue(true)
                .isTrue(false)
                .isFalse(true)
                .isFalse(false)
                .isEqual(true, false);
        });
    });
});

uTestRun();
