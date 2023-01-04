#include <algorithm>
#include <functional>
#include <iostream>
#include <type_traits>
#include <vector>

#include "vector.hpp"

using namespace tuto;

bool test_default_constructor() {
    vector<int> v;
    return true;
}

bool test_data() {
    vector<int> v;
    return v.data() == nullptr;
}

bool test_pushback() {
    vector<int> v;
    
    v.push_back(2);
    
    return v.data()[0] == 2;
}

bool test_size() {
    vector<int> v;
    
    v.push_back(1);
    v.push_back(3);
    v.push_back(2);

    return v.size() == 3;
}

bool test_access() {
    vector<int> v;
    bool ok = true;

    v.push_back(42);
    ok &= v[0] == 42;
    
    v[0] = 2;
    ok &= v[0] == 2;

    auto const_check = [](const vector<int> &vv) {
        auto &i = vv[0]; // checks if there is a const operator[]
        return std::is_same<decltype(i), const int &>::value;
    };

    ok &= const_check(v);
    return ok;
}

bool test_at() {
    vector<int> v;
    bool ok = true;

    v.push_back(42);
    ok &= v.at(0) == 42;
    
    v.at(0) = 2;
    ok &= v.at(0) == 2;

    auto const_check = [](const vector<int> &vv) {
        auto &i = vv.at(0); // checks if there is a const operator[]
        return std::is_same<decltype(i), const int &>::value;
    };

    ok &= const_check(v);

    try {
        v.at(86543215);
    } catch (std::out_of_range) {
        // checking that we throw instead of crash
        return ok;
    }

    return false;
}

bool test_resize() {
    vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    
    v.resize(2);
    v.resize(4, -2);
    for (vector<int>::size_type i = 0; i < v.size(); ++i)
        if (i < 2) {
            if (v[i] != i + 1)
                return false;
        } else {
            if (v[i] != -2)
                return false;
        }

    return v.size() == 4;
}

bool test_sized_constructors() {
    vector<int> v(3);
    if (v.size() != 3)
        return false;
    
    //check if constructor is explicit
    return !std::is_convertible<int, vector<int>>::value;
}

bool test_sized_constructors_with_value() {
    const vector<std::string> v(3, "toto");
    if (v.size() != 3)
        return false;
    
    for (std::size_t i = 0; i < v.size(); ++i)
        if (v[i] != "toto")
            return false;
    
    return true;
}

bool test_equal() {
    vector<int> v1(3, 6);
    vector<int> v2(4, 6);
    bool ok = true;

    ok &= (v1 != v2);
    
    v1.push_back(42);
    v2[3] = 42;

    ok &= (v1 == v2);

    return ok;
}

std::vector<std::pair<std::string, std::function<bool()>>> test_functions{
    {"test_default_constructor", test_default_constructor},
    {"test_data", test_data},
    {"test_pushback", test_pushback},
    {"test_size", test_size},
    {"test_access", test_access},
    {"test_resize", test_resize},
    {"test_sized_constructors", test_sized_constructors},
    {"test_sized_constructors_with_value", test_sized_constructors_with_value},
    {"test_equal", test_equal},
};

std::size_t max_name_size = std::string("test_sized_constructors_with_value").size();

void test_all() {
    bool ok = true;

    for (auto &p : test_functions) {
        std::cout << p.first;
        for (std::size_t s = p.first.size(); s < max_name_size + 4; ++s)
            std::cout << " ";
        if (p.second())
            std::cout << "SUCCESS";
        else
            std::cout << "FAIL";
        std::cout << std::endl;
    }
}

int main(int, char**) {
    test_all();
    return 0;
}