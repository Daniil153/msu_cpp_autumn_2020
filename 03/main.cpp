#include <cassert>
#include "matrix.hpp"

void test() {
    Matrix m1(3, 5);
    Matrix m2(3, 5);
    Matrix m3(3, 4);
    assert(m1.GetRows() == 3);
    assert(m1.GetColumns() == 5);
    m1[1][1] = 10;
    
    try {
        int temp = m1[4][1];
    } catch (...) {
        std::cout << "Поймана ошибка выхода заграницу при попытке достать 4 строку(всего 3 строки)" << std::endl;
    }
    try {
        int temp = m1[1][10];
    } catch (...) {
        std::cout << "Поймана ошибка выхода заграницу при попытке достать 10 элемент из 1 строки(всего 5 столбцов)" << std::endl;
    }
    try {
        Matrix temp = m1 + m3;
    } catch (...) {
        std::cout << "Поймана ошибка при сложении матриц разных размеров" << std::endl;
    }
    m1 *= 3;
    assert(m1 != m2);
    m2[1][1] = 30;
    assert(m1 == m2);
    std::cout << "Вывод матрицы на стандартный поток вывода" << std::endl;
    std::cout << m1;
    std::cout << "Должна получитсья матрица:\n0 0 0 0 0\n0 30 0 0 0\n0 0 0 0 0\n" << std::endl;
    
}

int main() {
    test();
    std::cout << std::endl << "Все тесты пройдены!" << std::endl;
}
