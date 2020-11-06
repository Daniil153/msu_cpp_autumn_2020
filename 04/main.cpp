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

void test5() {
    BigInt a("999999999999999");
    BigInt ans1("999999999999994");
    BigInt ans2("-999999999999999");
    assert(a - 5 == ans1);
    std::cout << a - ans1 << std::endl;
    std::cout << -a << std::endl;
    BigInt q = -a;
    bool temp = q < ans2;
    assert(q == ans2);
    assert(-a == ans2);
}


void test6() {
    std::cout << "Test6():" << std::endl;
    BigInt a("999999999999");
    assert(-a == BigInt("-999999999999"));
    assert(BigInt(5) - a == BigInt("-999999999994"));
    assert(a-BigInt(5) == BigInt("999999999994"));
    assert(a+1 == BigInt("1000000000000"));
    assert(a-1 == BigInt("999999999998"));
    assert(BigInt(1)-a == BigInt("-999999999998"));
    std::cout << BigInt(1) + a << std::endl;
    assert(BigInt(1) + a == BigInt("1000000000000"));
    BigInt b = -a;
    assert(b == BigInt("-999999999999"));
    assert(b - 5 == BigInt("-1000000000004"));
    assert(b + 5 == BigInt("-999999999994"));
    assert(BigInt(5) + b == BigInt("-999999999994"));
    assert(BigInt(-5) + b == BigInt("-1000000000004"));
    assert(BigInt(5) - b == BigInt("1000000000004"));
    assert(BigInt(-5) - b == BigInt("999999999994"));
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    std::cout << "Все тесты пройдены" << std::endl;
    return 0;
}
