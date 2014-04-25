uTest
=====

A simple test "library" for lazy people who don't like writing tests.

# Usage
- Create a test `something_test.cpp`:

```cpp
// Include it
#include "utest.hpp"

// Initializes everything (only one per file)
uTest() {
    describe("Foo", []{
        int x = 5;
        std::vector<int> y{1, 2, 3};

        it("can Bar", [=]{
            x = 1;
            Warn(x == 1);
            Assert().isEqual(x, 1);
        })

        it("can Vec", [=]{
            Assert()
                .isTrue(y.empty())
                .isEqual(y.size(), (std::size_t)3))
                .forAll(y, [](int e) { return e < 4; });
        })
    });
}
```
- More comprehensive test: [case.cpp](/examples/case.cpp)
- Compile and run:
```bash
g++ -std=c++11 -o runner something_test.cpp && ./runner
```
- Run multiple tests:
```bash
for i in $(find *_test.cpp); do g++ -std=c++11 -o runner $i && ./runner; done
```

# Todo
- Add timeout
- Add timed comparisons
- Add time complexity testing
- Support for container -> container testing
