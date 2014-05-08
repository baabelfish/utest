#include "../utest.hpp"

#include <vector>

uTestPackage basic([]{
    describe("Assertion", []{
        it("can handle simple assertions", []{
            Assert()
                .isTrue(true)
                .isFalse(false)
                .isEqual(true, true)
                .isNotEqual(false, true);
        });
        it("can do invariants", []{
            auto vec = std::vector<int>{1,2,3,4};
            Assert()
                .forNone(vec, [](int i) { return i < 1 || i > 4; })
                .forSome(vec, [](int i) { return i == 2; })
                .forAll(vec, [](int i) { return i > 0 && i < 5; });
        });
    });
});

uTestPackage containerOverContainer([]{
    describe("Multiple input and output", []{
        it("can do basic checks", []{
             multiple(
                [](int a) -> int { return a * 2; },
                {1, 2, 3, 4},
                {2, 4, 6, 8});
        });
        it("can handle type change", []{
             multiple(
                [](int a) -> std::string { return std::to_string(a * 2); },
                {1, 2, 3, 4},
                {"2", "4", "6", "8"});
        });
    });
});

uTestPackage timing([]{
    describe("fasterThan", []{
        it("can determine the faster one", []{
            isFasterThan("sum of 100 is faster than sum of 1000",
            []{
                int sum = 0;
                for (std::size_t i = 0; i < 100; ++i) { sum += i; }
            },
            []{
                int sum = 0;
                for (std::size_t i = 0; i < 1000; ++i) { sum += i; }
            });
        });
    });
});

uTestRun();
