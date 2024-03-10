
# s21_containers
# Team members
- [theseChains](https://github.com/theseChains)
- [asya11001](https://github.com/Asya11001)

## Introduction
This project aims to implement a custom C++ library, `s21_containers`, which provides basic standard container classes similar to the Standard Template Library (STL). 
The library includes implementations of commonly used containers such as `list`, `map`, `queue`, `set_base`, `stack`, and `vector`, as well as additional containers like `array` and `multiset`.

## Motivation
Containers are fundamental data structures in programming, allowing for the storage and manipulation of collections of objects. By implementing our own container library, we gain a deeper understanding of data structures and algorithms while adhering to the logic and behavior of the STL.

## Features
- Header-only library: The container classes are implemented as header files, making it easy to include and use in various projects.
- Template classes: All container classes are templated, enabling flexibility in the types of objects they can store.
- Google style: The code follows the Google C++ Style Guide for consistency and readability.
- Unit tests: Comprehensive unit tests using the Google Test (GTest) library ensure the correctness of container implementations.
- Makefile: A Makefile is provided for building and testing the library with targets for cleaning and running tests.

## Usage
To use the `s21_containers` library in your project, include the desired header file(s) in your source code. For example, to use the `list` container:

```cpp
#include "s21_containers.h"

int main() {
    // Create a list of integers
    s21::list<int> my_list;

    // Add elements to the list
    my_list.push_back(10);
    my_list.push_back(20);
    my_list.push_back(30);

    // Iterate through the list
    for (const auto& elem : my_list) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

## Building and Testing
To build and test the `s21_containers` library, navigate to the project directory and run the following commands:

```bash
make clean  # Clean previous build artifacts
make test   # Build and run unit tests
```
