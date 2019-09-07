#include "cppzip/cppzip.hpp"
#include <cassert>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

using std::cout;
using std::endl;
using std::is_const;
using std::remove_reference;
using std::vector;


int main() {
    vector<int> v1{1, 3, 5};
    vector<std::string> v2{"a", "b", "c"};
    for (auto zipped : cppzip::czip(v1, v2)) {
        //zipped.first *= 2;
        cout << v1[0] << endl;
        cout << zipped.first << ", " << zipped.second << endl;
        assert (zipped.first % 2 == 1);
        assert (is_const<typename remove_reference<decltype(zipped.first)>::type>::value);
        assert (is_const<typename remove_reference<decltype(zipped.second)>::type>::value);
    }

    int a1[4] = {1,2,3,4};
    const float a2[4] = {-2.1, -4.1, -6.1, -8.1};
    for (auto zipped : cppzip::zip(a1, a2)) {
        cout << zipped.first << ", " << zipped.second << endl;
        assert (abs(zipped.second + (2 * zipped.first) + 0.1) < 1e-6);
        assert (false == is_const<typename remove_reference<decltype(zipped.first)>::type>::value);
        assert (is_const<typename remove_reference<decltype(zipped.second)>::type>::value);
        zipped.first *= 2;
    }
    cout << a1[0] << ", " << a1[1] << ", " << a1[2] << ", " << a1[3] << endl;
    return 0;
}
