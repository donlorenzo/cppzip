#include "cppzip/cppzip.hpp"
#include <vector>
#include <cassert>
#include <iostream>
#include <string>

using std::vector;
using std::cout;
using std::endl;

int main() {
    vector<int> v1{1, 3, 5};
    vector<std::string> v2{"a", "b", "c"};
    for (const auto& zipped : cppzip::czip(v1, v2)) {
        cout << zipped.first << ", " << zipped.second << endl;
        assert (zipped.first % 2 == 1);
    }

    int a1[4] = {1,2,3,4};
    const float a2[4] = {-2.1, -4.1, -6.1, -8.1};
    for (auto zipped : cppzip::zip(a1, a2)) {
        cout << zipped.first << ", " << zipped.second << endl;
        assert (abs(zipped.second + (2 * zipped.first) + 0.1) < 1e-6);
        zipped.first *= 2;
    }
    cout << a1[0] << ", " << a1[1] << ", " << a1[2] << ", " << a1[3] << endl;
    return 0;
}
