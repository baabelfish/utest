#include "../utest.hpp"

uTestPackage([]{
    describe("asd", []{
        it("qwe", []{
            Assert().isEqual(true, false);
        });
    });
});

uTestRun();
