#include <iostream>
#include <sstream>

unsigned int count(bool temp) {
    static unsigned int n = 0;
    if (temp) {
        n = 0;
        return n;
    } else {
        return n++;
    }
}

class format_exc: std::exception {
private:
    std::string exc;
public:
    explicit format_exc(std::string exc_): exc(std::move(exc_)) {}
    const char *what() const noexcept override
    {
        count(true);
        return exc.c_str();
    }
    friend std::ostream& operator<<(std::ostream& out, const format_exc& m);
};
std::ostream& operator<<(std::ostream& out, const format_exc& m) {
    out << m.what();
    return out;
}

unsigned int num(const std::string &s) {
    unsigned int res;
    try {
        res = std::stoul(s, nullptr, 10);
    } catch (const std::logic_error&) {
        throw format_exc("Неверный формат строки");
    }
    return res;
}

template <typename T>
std::string process(const std::string &s, T arg, unsigned int n) {
    std::ostringstream ans{};
    bool flag = false;
    for (int i = 0; i < int(s.length()); i++) {
        if (s[i] == '{') {
            std::string temp{};
            while (s[i] != '}') {
                i++;
                if (s[i] == '{' || i == int(s.length())) {
                    throw format_exc("Неверный формат строки");
                }
                temp += s[i];
            }
            if (n == num(temp)) {
                ans << arg;
                flag = true;
            } else {
                ans << ("{" + temp);
            }
        } else {
            ans << s[i];
        }
    }
    if (!flag) {
        throw format_exc("Неверный формат строки");
    }
    return ans.str();
}

template <typename T>
std::string format(const std::string &s, T arg) {
    std::string res;
    res = process(s, arg, count(false));
    for (auto c : res) {
        if (c == '{' or c == '}') {
            throw format_exc("Неверный формат строки");
        }
    }
    return res;
}

template <typename T, typename... ArgsT>
std::string format(const std::string &s, T arg, ArgsT... args) {
    std::string res;
    res = process(s, arg, count(false));
    return format(res, std::forward<ArgsT>(args)...);
}
