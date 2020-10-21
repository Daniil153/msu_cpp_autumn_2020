#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <string>

//DigitVec - вектор числовых токенов
//StringVec - вектор строковых токенов
//AllTokens - вектор всех токенов в исходном порядке
//Т.к. мы бьем текст на токены, логично, что они нам потом понадобятся(может для создания словаря или чего-то подобного)
//Поэтому мне показалось уместным сделать такие штуки.

class TokenParser {
    std::string data;
    std::vector <uint64_t> DigitVec;
    std::vector <std::string> StringVec;
    std::vector <std::pair<std::string, std::string>> AllTokens; //Тут пары (токен - тип токена)
    std::function<void (uint64_t token)> fDigit;
    std::function<void (std::string &token)> fString;
    std::function<void ()> start;
    std::function<void ()> end;
public:
    TokenParser(const std::string &data_) : data(data_) {}
    void SetStartCallback(const std::function<void ()> &f) {
        start = f;
    }
    void SetDigitTokenCallback(const std::function<void (uint64_t token)> &f) {
        fDigit = f;
    }
    void SetStringTokenCallback(const std::function<void (std::string &token)> &f) {
        fString = f;
    }
    void SetEndCallback(const std::function<void ()> &f) {
        end = f;
    }
    std::vector<uint64_t> get_Digit_tokens() {
        return DigitVec;
    }
    std::vector<std::string> get_String_tokens() {
        return StringVec;
    }
    std::vector<std::pair<std::string, std::string>> get_All_tokens() {
        return AllTokens;
    }
    std::string get_data() {
        return data;
    }
    void parse() {
        start();
        bool flag_dig = true;
        std::string temp;
        if (data.empty()) {
            end();
            return;
        }
        for (u_char c : data + ' ') {
            if (!std::isspace(c)) {
                temp += c;
                if (flag_dig) {
                    if (!std::isdigit(c)) {
                        flag_dig = false;
                    }
                }
            } else {
                if (flag_dig) {
                    DigitVec.push_back(std::stoull(temp));
                    fDigit(std::stoull(temp));
                } else {
                    StringVec.push_back(temp);
                    fString(temp);
                }
                std::string type;
                if (flag_dig) {
                    type = "Digit";
                } else {
                    type = "String";
                }
                AllTokens.push_back((std::pair<std::string, std::string>(temp, type)));
                flag_dig = true;
                temp.clear();
            }
        }
        end();
    }
};
