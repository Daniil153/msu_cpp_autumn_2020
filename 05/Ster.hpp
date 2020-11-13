#pragma once
#include <iostream>
#include <sstream>

enum class Error {
    NoError,
    CorruptedArchive
};

class Serializer {
    std::ostream& out;
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out_) : out(out_) {}

    template <class T>
    Error save(T& object) {
        return object.serialize(*this);
    }

    template<typename T>
    Error process(T& elem)
    {
        return Error::CorruptedArchive;
    }

    Error process(bool arg)
    {
        if (arg) {
            out << "true" << Separator;
        } else {
            out << "false" << Separator;
        }
        return Error::NoError;
    }

    Error process(uint64_t arg)
    {
        out << arg << Separator;
        return Error::NoError;
    }

    template <class T, class... ArgT>
    Error process(T&& arg, ArgT&&... args) {
        Error temp = process(std::forward<T>(arg));
        if (temp == Error::NoError) {
            return process(std::forward<ArgT>(args)...);
        } else {
            return temp;
        }
    }

    template <class... ArgsT>
    Error operator()(ArgsT &&... args) {
        return process(std::forward<ArgsT>(args)...);
    }
};

class Deserializer {
    std::istream& inp;
public:
    explicit Deserializer(std::istream& inp_) : inp(inp_) {}

    template <class T>
    Error process(T&& arg) {
        return Error::CorruptedArchive;
    }

    Error process(bool& arg) {
        std::string temp;
        inp >> temp;
        if (temp == "true") {
            arg = true;
        } else if (temp == "false") {
            arg = false;
        } else {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

    Error process(uint64_t& arg) {
        std::string temp;
        inp >> temp;
        try {
            arg = std::stoull(temp);
        } catch (std::logic_error&) {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

    template <class T, class... ArgT>
    Error process(T&& arg, ArgT&& ...args) {
        Error temp = process(std::forward<T>(arg));
        if (temp == Error::NoError) {
            return process(std::forward<ArgT>(args)...);
        } else {
            return temp;
        }
    }

    template <class T>
    Error load(T& object) {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT &&...args) {
        return process(std::forward<ArgsT>(args)...);
    }
};

