#include <cassert>
#include "allocator.hpp"

void test1() {
    Allocator temp;
    temp.makeAllocator(20);
    assert(nullptr != temp.alloc(10));
    assert(nullptr == temp.alloc(11));
    temp.reset();
    assert(nullptr != temp.alloc(5));
    assert(nullptr != temp.alloc(5));
    assert(nullptr != temp.alloc(5));
    assert(nullptr != temp.alloc(5));
    assert(nullptr == temp.alloc(1));
    temp.reset();
    assert(nullptr != temp.alloc(0));
    assert(nullptr != temp.alloc(20));
    temp.reset();
    assert(nullptr == temp.alloc(21));
    assert(nullptr != temp.alloc(19));
    assert(nullptr != temp.alloc(1));
}

void test2() {
    std::cout << "Вы можете протестировать сами. Если хотите введите yes, иначе no" << std::endl;
    std::string str;
    std::cin >> str;
    if (str == "yes") {
        size_t size = 0;
        std::cout << "Введите на сколько Вы хотите выделить память" << std::endl;
        std::cin >> size;
        std::cout << "Введите последовательность операций, которые вы хотите сделать. Если alloc, то просто на сколько(число), если reset, то 'reset', если хотите закончить, то 'end'" << std::endl;
        std::string s;
        std::cin >> s;
        unsigned long c = 0;
        Allocator temp;
        temp.makeAllocator(size);
        while (s != "end") {
            if (s == "reset"){
                temp.reset();
            } else {
                c = stoul(s, nullptr, 10);
                assert(nullptr != temp.alloc(c));
            }
            std::cin >> s;
        }
    } else {
        std::cout << "Окей :(";
    }
}

int main() {
    std::cout << "Мои тесты:" << std::endl;
    test1();
    std::cout << "Успешно" << std::endl;
    test2();
    return 0;
}
