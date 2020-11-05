#include <cassert>
#include "BigInt.hpp"

void test1() {
    BigInt a = 1;
    BigInt b("123456789012345678901234567890");
    BigInt c = a * b + 2;
    BigInt d;
    d = std::move(c);
    a = d + b;
    std::cout << a << std::endl;
}

void test2() {
    BigInt a("111111111111");
    BigInt b("111111111111");
    BigInt ans1("222222222222");
    BigInt ans2("0");
    BigInt ans3("12345679012320987654321");
    BigInt c = a + b;
    BigInt d = a - b;
    BigInt m = a * b;
    assert(c == ans1);
    assert(d == ans2);
    assert(m == ans3);
}

void test3() {
    BigInt a("111111111111");
    BigInt b("111111111111");
    a = a - 1;
    BigInt c = a - b;
    assert(c == BigInt("-1"));
    a = a + 2;
    BigInt d = a - b;
    assert(d == BigInt("1"));
    a = a - 1; //111111111111
    BigInt u("21111111111");
    BigInt res = a - u;
    assert(res == BigInt("90000000000"));
}

void test4() {
    BigInt a("-111111111111");
    BigInt b("111111111111");
    BigInt c = a + b;
    assert(c >= BigInt(0));
    assert(c <= BigInt(0));
    assert(c < BigInt(1));
    assert(c > BigInt(-1));
    assert(a != b);
    assert(-a == b);
    a = a + 1;
    BigInt d = a + b;
    assert(d == BigInt("1"));
    BigInt d2 = a - b;
    assert(d2 == BigInt("-222222222221"));
}

int main() {
    test1();
    test2();
    test3();
    test4();
    std::cout << "Все тесты пройдены" << std::endl;
    return 0;
}
