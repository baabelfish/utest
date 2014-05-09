yTest [![Build Status](https://travis-ci.org/baabelfish/ytest.svg?branch=master)](https://travis-ci.org/baabelfish/ytest) [![Coverage Status](https://coveralls.io/repos/baabelfish/ytest/badge.png)](https://coveralls.io/r/baabelfish/ytest)
=====

A simple test "library" for lazy (simple) people who don't like writing tests.


# Usage
## Creating tests

- File ``footests.cpp``
```cpp
#include "path/to/ytest.hpp"

yTestPackage pkg() {
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

- File ``runner.cpp``
```cpp
#include "path/to/ytest.hpp"
yTestRun();
```

- Compile:
```bash
g++ -std=c++11 -o runner footests.cpp runner.cpp
./runner
```

- Check tests for more examples: [tests.cpp](/tests/tests.cpp)

## Running tests
- Simple:
```bash
for i in $(find *_test.cpp); do g++ -std=c++11 -o runner $i && ./runner; done
```

- Checking changes in files:
```bash
while true; do
    make tests && clear && ./ytests
    if [[ $(which inotifywait) == "" ]]; then
        sleep 5
    else
        change=$(inotifywait -r -e close_write,moved_to,create . 2> /dev/null)
    fi
done
```

## Documentation

TODO
