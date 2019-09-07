# cppzip
Python's zip functionality for C++

For-each loops are great.
However, there are many situations where they cannot be used.
One of those cases is when you want to iterate over two containers simultaneously.
In that case one has to resort to either a regular index based for-loop:
```cpp
for(size_t i = 0; i < containerA.size() && i < containerB.size(); ++i) {
  auto& valueA = containerA[i];
  auto& valueB = containerB[i];
  ...
}
```
or if both containers have the same type a iterator based approach might look like this:
```cpp
for(auto aIt = begin(containerA), bIt = begin(containerB);
    aIt != end(containerA) && bIt != end(containerB);
    ++aIt, ++bIt) {
  auto& valueA = *aIt;
  auto& valueB = *bIt;
  ...
}
```
but what we really want is a for-each-loop.

Enter cppzip.
Inspired by [Pyhton's zip function](https://docs.python.org/3/library/functions.html#zip) it support the following syntax:
```cpp
for(auto valuePair : cppzip::zip(containerA, containerB)) {
  auto& valueA = valuePair.first;
  auto& valueB = valuePair.second;
  ...
}
```


## Usage
* Include the header: `#include <cppzip/cppzip.hpp>`
* `cppzip::zip` for getting pairs of value references. If a container is const the respective value reference will also be const.
* `cppzip::czip` for getting pairs of const value references.

## Example Usage
```cpp
#include <cppzip/cppzip.hpp>

void array_example() {
  int iArray[5] {1, 2, 3, 5, 8};
  double timesOneAndAHalf[5] {1.5, 3.0, 4.5, 7.5, 12.0};
  for(auto& values : cppzip::czip(iArray, timesOneAndAHalf) {
    assert(values.first * 1.5 == values.second);
  }
}

void vector_example() {
  vector<int> iVector {1, 2, 3, 5, 8};
  vector<double> timesOneAndAHalf {1.5, 3.0, 4.5, 7.5, 12.0};
  for(auto& values : cppzip::czip(iVector, timesOneAndAHalf) {
    assert(values.first * 1.5 == values.second);
  }
}

void timesTwo() {
  const vector<int> inputVector {1, 2, 3, 5, 8};
  vector<int> timesTwo {0, 0, 0, 0, 0};
  for(auto& values : cppzip::zip(inputVector, timesTow) {
    values.second = values.first * 2;
  }
}

```
