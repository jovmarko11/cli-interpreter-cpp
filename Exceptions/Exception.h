//
// Created by Marko Jovanovic on 19.2.26..
//

#ifndef OOP1PROJEKAT_EXCEPTION_H
#define OOP1PROJEKAT_EXCEPTION_H
#include <exception>
#include <string>

enum class ErrorType { Lexical, UnknownCommand, Syntax, StreamSemantic, CommandSemantic, System };

class Exception : public std::exception {
    ErrorType m_cat;
    std::string m_msg;
    int m_pos;

public:
    Exception(ErrorType cat, std::string msg, int pos = -1)
        : m_cat(cat), m_msg(std::move(msg)), m_pos(pos) {
    }

    const char *what() const noexcept override { return m_msg.c_str(); }

    ErrorType type() const noexcept { return m_cat; }

    int position() const noexcept { return m_pos; }
};


#endif //OOP1PROJEKAT_EXCEPTION_H
