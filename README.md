uTest
=====

This is a simple test "library" for lazy people why don't like writing unit tests.

# Usage
- Create a test `something\_test.cpp`:
```cpp
// Initializes everything (only one per file)
uTest() {
    // Add tests into it
    test([]{
        Warn(1 == 2); // Prints a warning and continues
        Assert(1 == 2); // Prints a failure and stops execution
    });
}
```
- Compile:
```bash
g++ -std=c++11 -o runner examples/case.cpp
```
- Run multiple tests:
```bash
for i in $(find *.hpp); do g++ -std=c++11 -o runner $i && ./runner; done
```

# Todo
- Add time complexity testing
- Support for container -> container testing
