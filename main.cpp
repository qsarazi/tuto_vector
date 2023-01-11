#include <algorithm>
#include <functional>
#include <iostream>
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
    //int *tab=v.data();
    //std::cout << "appelle " <<tab << ',' << tab[0]<< ','; 

    return v.data()[0] == 2;
    //return tab[0]==2;
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
    
    return ok;
}

std::vector<std::pair<std::string, std::function<bool()>>> test_functions{
    {"test_default_constructor", test_default_constructor},
    {"test_data", test_data},
    {"test_pushback", test_pushback},
    {"test_size", test_size},
    {"test_access", test_access}
};

std::size_t max_name_size = std::string("test_default_constructor").size();

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

    std::vector<float> vf;

    // for (std::vector<float>::iterator it = vf.begin(); )

    return 0;
}