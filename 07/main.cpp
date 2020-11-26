#include <iostream>
#include <cassert>
#include "Vector.hpp"

void test1() {
    Vector <int> vec;
    assert(vec.empty() == true);
    vec.push_back(10);
    vec.push_back(20);
    assert(vec[0] == 10);
    assert(vec[1] == 20);
    assert(vec.size() == 2);
    assert(vec.capacity() == 2);
    vec.push_back(30);
    assert(vec.size() == 3);
    assert(vec.capacity() == 4);
    vec.emplace_back(44);
    assert(vec.capacity() == 4);
    assert(vec.empty() == false);
    assert(vec.size() == 4);
    vec.clear();
    assert(vec.size() == 0);
    assert(vec.capacity() != 0);
    std::cout << "1 тест пройден!" << std::endl;
}
void test2() {
    Vector <int> vec;
    vec.reserve(10);
    assert(vec.size() == 0);
    assert(vec.capacity() == 10);
    vec.push_back(10);
    assert(vec.capacity() == 10);
    vec.push_back(20);
    assert(vec.capacity() == 10);
    vec.push_back(30);
    assert(vec.capacity() == 10);
    for (int i = 0; i < 8; ++i) {
        vec.push_back(i);
    }
    assert(vec.capacity() == 20);
    vec.resize(5);
    assert(vec.size() == 5);
    assert(vec.capacity() == 20);
    Vector <double> vec2;
    vec2.push_back(15);
    vec2.push_back(25);
    vec2.resize(100);
    assert(vec2.size() == 100);
    assert(vec2.capacity() == 100);
    std::cout << "2 тест пройден!" << std::endl;
}
void test3() {
    Vector <int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    auto it = vec.begin();
    int i = 0;
    while (it != vec.end()) {
        assert(*it == vec[i]);
        i++;
        it++;
    }
    it--;
    ++it;
    --it;
    it -= 1;
    it += 1;
    assert(*it == vec[2]);
    auto rit = vec.rbegin();
    i = (int)vec.size() - 1;
    while (rit != vec.rend()) {
        assert(*rit == vec[i]);
        rit++;
        i--;
    }
    std::cout << "3 тест пройден!" << std::endl;
}

int main() {
    test1();
    test2();
    test3();
    std::cout << "Все тесты пройдены!" << std::endl;
    return 0;
}
