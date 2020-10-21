#include <cassert>
#include "parser.hpp"

void test1() {
    TokenParser temp("");
    temp.SetStartCallback([](){std::cout << "Начинаем парсинг" << std::endl;});
    temp.SetEndCallback([](){std::cout << "Заканчиваем парсинг" << std::endl;});
    temp.parse();
    assert(temp.get_data() == "");
    assert(temp.get_Digit_tokens().empty());
    assert(temp.get_String_tokens().empty());
}

void test2() {
    TokenParser temp("123 сегодня я гулял на 2ул дре3 33 круто 1");
    std::cout << "Исходный текст:" << std::endl << temp.get_data() << std::endl;
    temp.SetStartCallback([](){std::cout << "Начинаем парсинг" << std::endl;});
    temp.SetEndCallback([](){std::cout << "Заканчиваем парсинг" << std::endl;});
    temp.SetDigitTokenCallback([](uint64_t token){std::cout << token << ":    Число" << std::endl;});
    temp.SetStringTokenCallback([](std::string &token){std::cout << token << ":    Строка" << std::endl;});
    temp.parse();
    std::vector<std::pair<std::string, std::string>> v = temp.get_All_tokens();
    std::vector<std::string> check{"Digit", "String", "String", "String", "String", "String", "String", "Digit", "String", "Digit"};
    int i = 0;
    for (auto it = v.begin(); it != v.end(); ++it, ++i) {
        assert(it->second==check[i]);
    }
}

int main() {
    std::cout << "Проверка на моих тестах\n" << std::endl;
    test1(); //Текст пустого входа
    std::cout << "Тест №1 пройден!\n" << std::endl;
    test2(); // Еще один тест
    std::cout << "\nМои тесты прошли" << std::endl;
}