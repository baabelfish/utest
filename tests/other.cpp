#include "../ytest.hpp"

yTestPackage other([]{
    describe("Assertion", []{
        it("can handle simple assertions", []{
            Assert().isTrue(true);
        });
    });
});
