#include "../ytest.hpp"

yTestPackage other([]{
    describe("multiple files", []{
        it("can handle multiple files", []{
            Assert().isTrue(true);
        });
    });
});
