yTest [![Build Status](https://travis-ci.org/baabelfish/ytest.svg?branch=master)](https://travis-ci.org/baabelfish/ytest) [![Coverage Status](https://coveralls.io/repos/baabelfish/ytest/badge.png?branch=master)](https://coveralls.io/r/baabelfish/ytest?branch=master)
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
        it("can Bar", [=]{
            x = 1;
            Assert().isEqual(x, 1);
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

# Documentation

TODO
