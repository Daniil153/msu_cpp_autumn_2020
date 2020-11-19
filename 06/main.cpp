#include "format.hpp"
#include <cassert>

void test() {
    auto text = format("{1}+{1} = {0}", 2, "one");
    assert(text == "one+one = 2");
    
    try {
        auto text = format("{1}+{1} = {0} + {2}", 2, "one");
    } catch (const format_exc& a) {
        std::cout << a << std::endl;
    }
    
    try {
        auto text = format("{1}+{1}+{2} = {0}", 2, "one");
    } catch (const format_exc& a) {
        std::cout << a << std::endl;
    }
    
    try {
        auto text = format("{1}+{1} = {0}", 2, "one", 10);
    } catch (const format_exc& a) {
        std::cout << a << std::endl;
    }
    std::cout << "Все ошибки в тесте пойманы!" << std::endl;
}

int main() {
    test();
    std::cout << "Все тесты пройдены" << std::endl;
    return 0;
}
