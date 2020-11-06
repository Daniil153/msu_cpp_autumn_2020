#pragma once
#include <iostream>
#include <cmath>

const int base = 100000000;
const std::string mask{"00000000"};
const int Base = 8;


class BigInt {
    unsigned int *data;
    int sign = 1;
    size_t size{};
    size_t new_size{};
public:

    BigInt(int value=0) {
        if (value < 0) {
            sign = -1;
        }
        new_size = 1;
        data = new unsigned int [1];
        data[0] = value;
    }
    BigInt(const std::string &s, size_t ssize=0) {
        int t = 0;
        if (s[0] == '-') {
            t = 1;
            sign = -1;
        } else {
            sign = 1;
        }
        size = s.length();
        new_size = ceil(double(size - t) / Base);
        if (size == 0) {
            new_size = ssize;
            data = new unsigned int [new_size];
            return;
        }
        data = new unsigned int [new_size];
        int count = 0;
        for (int i = (int)size; i > 0; i -= Base) {
            if (i - t < Base) {
                data[count] = (atoi (s.substr (t, i-t).c_str()));
            } else {
                data[count] = (atoi (s.substr (i-Base, Base).c_str()));
            }
            count++;
        }
    }
    BigInt(const BigInt &m) {
        new_size = m.new_size;
        sign = m.sign;
        data = new unsigned int [new_size];
        for (size_t i = 0; i < new_size; ++i) {
            data[i] = m.data[i];
        }
    }
    BigInt(BigInt &&m) {
        data = m.data;
        sign = m.sign;
        new_size = m.new_size;
        m.data = nullptr;
        m.new_size = 0;
        m.sign = 1;
    }
    BigInt &operator= (BigInt &&m) {
        if (*this == m) {
            return *this;
        }
        delete [] data;
        data = m.data;
        sign = m.sign;
        new_size = m.new_size;
        m.data = nullptr;
        m.sign = 1;
        m.new_size = 0;
        return *this;
    }
    BigInt &operator= (const BigInt &m) {
        if (*this == m) {
            return *this;
        }
        delete [] data;
        sign = m.sign;
        new_size = m.new_size;
        data = new unsigned int [new_size];
        for (size_t i = 0; i < new_size; ++i) {
            data[i] = m.data[i];
        }
        return *this;
    }
    bool operator <(const BigInt &m) const {
        if (sign > m.sign) {
            return false;
        }
        if (sign < m.sign) {
            return true;
        }
        if (new_size > m.new_size) {
            return sign - 1;
        }
        if (new_size < m.new_size) {
            return sign + 1;
        }
        for (size_t i = 0; i < new_size; i++) {
            if (data[i] > m.data[i]) {
                return sign - 1;
            }
            if (data[i] < m.data[i]) {
                return sign + 1;
            }
        }
        return false;
    }
    bool operator >(const BigInt &m) const {
        if (sign > m.sign) {
            return true;
        }
        if (sign < m.sign) {
            return false;
        }
        if (new_size > m.new_size) {
            return sign + 1;
        }
        if (new_size < m.new_size) {
            return sign - 1;
        }
        for (size_t i = 0; i < new_size; i++) {
            if (data[i] > m.data[i]) {
                return sign + 1;
            }
            if (data[i] < m.data[i]) {
                return sign - 1;
            }
        }
        return false;
    }
    bool operator >=(const BigInt &m) const {
        return !(*this < m);
    }
    bool operator <=(const BigInt &m) const {
        return !(*this > m);
    }
    bool operator ==(const BigInt &m) const
    {
        return !(*this > m || *this < m);
    }
    bool operator !=(const BigInt &m) const
    {
        return !(*this == m);
    }

    BigInt operator+(const BigInt &m) const {
        if (m.sign != sign) {
            return *this - (-m);
        }
        BigInt temp("", std::max(new_size, m.new_size));
        temp.sign = sign;
        unsigned int ost = 0;
        for (size_t i = 0; i < temp.new_size; ++i) {
            unsigned int t = ost;
            if (i < new_size) {
                t += data[i];
            }
            if (i < m.new_size) {
                t += m.data[i];
            }
            temp.data[i] = t % base;
            ost = t / base;
        }
        if (ost == 1) {
            temp.new_size++;
            unsigned int *new_data = new unsigned int [temp.new_size];
            new_data[temp.new_size - 1] = ost;
            for (int i = 0; i < (int)temp.new_size - 1; ++i) {
                new_data[i] = temp.data[i];
            }
            delete [] temp.data;
            temp.data = new_data;

        }
        return temp;
    }

    BigInt operator-(const BigInt &m) const {
        if (sign != m.sign) {
            return *this + (-m);
        }
        if (*this == m) {
            return BigInt(0);
        } else if ((*this > m && sign == 1) || (*this < m && sign == -1)) {
            BigInt temp = f(*this, m);
            return temp;
        } else {
            BigInt temp = f(m, *this);
            temp.sign *= -1;
            return temp;
        }
    }
    BigInt f(const BigInt &self, const BigInt &m) const {
        BigInt temp(*self);
        unsigned int ost = 0;
        for (size_t i = 0; i < self.new_size; i++) {
            unsigned int p1 = 0;
            unsigned int p2 = 0;
            if (i < self.new_size) {
                p1 += self.data[i] - ost;
            }
            if (i < m.new_size) {
                p2 += m.data[i];
            }
            if (p1 >= p2) {
                temp.data[i] = p1 - p2;
                ost = 0;
            } else {
                temp.data[i] = p1 + base - p2;
                ost = 1;
            }
        }
        int count = 0;
        for (int i = (int)temp.new_size - 1; i >= 0; --i) {
            if (temp.data[i] != 0) {
                break;
            }
            count++;
        }
        temp.new_size = (int)temp.new_size - count;
        if (temp.new_size == 0) {
            temp.new_size = 1;
        }
        unsigned int *new_data = new unsigned int [temp.new_size];
        for (size_t i = 0; i < temp.new_size; ++i) {
            new_data[i] = temp.data[i];
        }
        delete [] temp.data;
        temp.data = new_data;
        return temp;
    }

    BigInt operator*(const BigInt &m) const {
        if (*this < m) {
            return m * *this;
        }
        BigInt temp(0);
        std::string zerosi{};
        for (size_t i = 0; i < new_size; ++i) {
            std::string zerosj{};
            for (size_t j = 0; j < m.new_size; ++j) {
                unsigned long long mul = (long long)(data[i]) * (long long)(m.data[j]);
                std::string str = std::to_string(mul);
                str += zerosi + zerosj;
                temp = temp + BigInt(str);
                zerosj += mask;
            }
            zerosi += mask;
        }
        temp.sign = sign * m.sign;

        int count = 0;
        for (int i = (int)temp.new_size - 1; i >= 0; --i) {
            if (temp.data[i] != 0) {
                break;
            }
            count++;
        }
        temp.new_size = (int)temp.new_size - count;
        if (temp.new_size == 0) {
            temp.new_size = 1;
        }
        unsigned int *new_data = new unsigned int [temp.new_size];
        for (size_t i = 0; i < temp.new_size; ++i) {
            new_data[i] = temp.data[i];
        }
        delete [] temp.data;
        temp.data = new_data;

        return temp;
    }
    BigInt operator-() const {
        BigInt temp(*this);
        temp.sign *= -1;
        return temp;
    }
    ~BigInt() {
        if (data != nullptr) {
            delete [] data;
        }
        new_size = 0;
        size = 0;
    }
    friend std::ostream& operator<<(std::ostream& out, const BigInt& m);
};
std::ostream& operator<<(std::ostream& out, const BigInt& m) {
    if (m.sign == -1) {
        if (m.new_size != 1 || m.data[0] != 0) {
            out << '-';
        }
    }
    out << m.data[m.new_size - 1];
    for (int i = (int)m.new_size - 2; i >= 0; --i) {
        unsigned int temp = m.data[i];
        if (temp == 0) {
            out << mask;
        } else {
            while (true) {
                temp *= 10;
                if (temp / base != 0) {
                    break;
                }
                out << '0';
            }
            out << m.data[i];
        }
    }
    return out;
}
