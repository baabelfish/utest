// Compile with: g++ -std=c++11 -o runner examples/case.cpp
// Run with ./runner

#include "../utest.hpp"
#include <algorithm>
#include <vector>
#include <deque>

template<typename T>
void abstract() {
    T vec;

    it("can be empty", [&]{
        Warn(1 == 2);
        Assert().isTrue(true);
    });

    it("can push back", [&]{
        vec.push_back(5);
        Assert()
            .isTrue(false)
            .isFalse(vec.empty())
            .isEqual(vec, {5});
    });
}

uTest() {
    describe("std::vector", abstract<std::vector<int>>);
    describe("std::deque", abstract<std::deque<int>>);

    describe("std::algorithm", [] {
        std::vector<int> vec{3, 2, 3, 4};

        it("works", [=]{
            Assert()
                .isEqual(vec.size(), (std::size_t)4)
                .forAll(vec, [](int a) { return a < 2; })
                .forSome(vec, [](int a) { return a == 2; })
                .forNone(vec, [](int a) { return a == 1; });

        });

        it("can transform", [=]{
            std::vector<float> fvec(vec.size());
            std::transform(vec.begin(), vec.end(), fvec.begin(), [](int) { return 1; });

            Assert()
                .isEqual(fvec.size(), (std::size_t)4)
                .forAll(fvec, [](int a) { return a == 1; });
        });
    });
}
