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
    // Add tests into it
    test([]{
        Warn(1 == 2); // Prints a warning and continues
        Assert(1 == 2); // Prints a failure and stops execution
    });
}
```
- Compile and run:
```bash
g++ -std=c++11 -o runner something_test.cpp && ./runner
```
- Run multiple tests:
```bash
for i in $(find *_test.cpp); do g++ -std=c++11 -o runner $i && ./runner; done
```

# Todo
- Add time complexity testing
- Support for container -> container testing
