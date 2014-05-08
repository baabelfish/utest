uTest ![Travis](https://travis-ci.org/baabelfish/utest.svg)
=====

A simple test "library" for lazy (simple) people who don't like writing tests.


# Usage
- Create files

```cpp
// footests.cpp

// Include it
#include "utest.hpp"

// Initialize a package
uTestPackage pkg() {
    describe("Foo", []{
        int x = 5;
        std::vector<int> y{1, 2, 3};

        it("can Bar", [=]{
            x = 1;
            Warn(x == 2);
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

```cpp
// runner.cpp
uTestRun();
```

- Compile and run:
```bash
g++ -std=c++11 -o runner footests.cpp runner.cpp && ./runner
```
- Run all tests:
```bash
for i in $(find *_test.cpp); do g++ -std=c++11 -o runner $i && ./runner; done
```

- More complex example of a runner with automated check for changes
```bash
while true; do
    make tests && clear && ./utests
    if [[ $(which inotifywait) == "" ]]; then
        sleep 5
    else
        change=$(inotifywait -r -e close_write,moved_to,create . 2> /dev/null)
    fi
done
```

- More comprehensive test files: [case.cpp](/examples/tests.cpp) [case.cpp](/examples/case.cpp) (compiled with: `clang++ -std=c++11 -o runner examples/tests.cpp examples/case.cpp`)

# Todo
- Support for container -> container testing
