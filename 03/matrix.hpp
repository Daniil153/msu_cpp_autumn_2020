#pragma once
#include <iostream>


class Matrix_Proxy {
    size_t size;
    int *mas;
public:
    Matrix_Proxy(int *matrix, size_t cols) {
        mas = matrix;
        size = cols;
    }
    int& operator[](size_t i)
    {
        if (i >= size) {
            throw std::out_of_range("Error [][]");
        }
        return mas[i];
    }
    const int& operator[](size_t i) const {
        if (i >= size) {
            throw std::out_of_range("Error [][]");
        }
        return mas[i];
    }

};

class Matrix {
    size_t Rows;
    size_t Columns;
    int** matrix;
public:
    Matrix(size_t rows, size_t cols) {
        Columns = cols;
        Rows = rows;
        matrix = new int*[rows];
        for (size_t i = 0; i < rows; ++i) {
            matrix[i] = new int[cols];
        }

    }
    Matrix_Proxy operator [] (size_t i) {
        if (i >= Rows) {
            throw std::out_of_range("Error []");
        }
        return Matrix_Proxy(matrix[i], Columns);
    }
    Matrix_Proxy operator [] (size_t i) const {
        if (i >= Rows) {
            throw std::out_of_range("Error []");
        }
        return Matrix_Proxy(matrix[i], Columns);
    }
    bool operator==(Matrix& m) const {
        if (m.Rows != Rows || m.Columns != Columns) {
            throw std::out_of_range("Error ==");
        }
        bool flag = true;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Columns; ++j) {
                if (matrix[i][j] != m[i][j]) {
                    flag = false;
                    break;
                }
            }
        }
        return flag;
    }
    bool operator!=(Matrix& m) const {
        if (m.Rows != Rows || m.Columns != Columns) {
            throw std::out_of_range("Error !=");
        }
        bool flag = false;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Columns; ++j) {
                if (matrix[i][j] != m[i][j]) {
                    flag = true;
                    break;
                }
            }
        }
        return flag;
    }
    Matrix operator+(Matrix& m) const {
        if (m.Rows != Rows || m.Columns != Columns) {
            throw std::out_of_range("Error +");
        }
        Matrix sum(Rows, Columns);
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Columns; ++j) {
                sum[i][j] = matrix[i][j] + m[i][j];
            }
        }
        return sum;
    }
    Matrix& operator *=(int a) {
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Columns; ++j) {
                matrix[i][j] *= a;
            }
        }
        return *this;
    }
    size_t GetRows() const {
        return Rows;
    }
    size_t GetColumns() const {
        return Columns;
    }
    friend std::ostream& operator<<(std::ostream& out, Matrix& m);
    ~Matrix() {
        for (size_t i = 0; i < Rows; ++i) {
            delete [] matrix[i];
        }
        delete [] matrix;
    }
};

std::ostream& operator<<(std::ostream& out, Matrix& m) {
    for (size_t i = 0; i < m.GetRows(); ++i) {
        for (size_t j = 0; j < m.GetColumns(); ++j) {
            out << m[i][j] << ' ';
        }
        out << std::endl;
    }
    return out;
}


