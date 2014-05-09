#include "../ytest.hpp"

#include <vector>

yTestPackage basic([]{
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

yTestPackage MultipleChecks([]{
    describe("Multiple checks", []{
        it("Works with ()-operator", []{
            bomb([](int a, int b) -> std::string {
                return std::to_string(a + b);
            })
            ("5", 2, 3)
            ("10", 5, 5);
        });
        it("Works with member function", []{
            bomb([](int a, std::string b) -> int {
                return a + std::stoi(b);
            })
            .with(3, 1, "2")
            .with(10, 5, "5");
        });
        it("Works with validator function", []{
            bomb([](int a, std::string b) -> int {
                return a + std::stoi(b);
            })
            .validate([](int a) {
                return a < 5;
            }, 1, "2");
        });
    });
});

std::function<void()> createSummer(std::size_t amount) {
    return [=]{
        int sum = 0;
        for (std::size_t i = 0; i < amount; ++i) { sum += i; }
    };
}

yTestPackage timing([]{
    describe("fasterThan", []{
        it("can determine the faster one", [=]{
            isFasterThan("sum of 100 is faster than sum of 1000", createSummer(100), createSummer(1000));
        });
        it("works with a margin", [=]{
            isFasterThan("sum of 100 is faster than sum of 1000", createSummer(100), createSummer(1000), 0.5);
        });
    });
});

yTestPackage misc([]{
    describe("Warning", []{
        it("doesn't trigger fail with CI", []{
            Warn(1 == 2);
        });
    });
});

yTestRun();
