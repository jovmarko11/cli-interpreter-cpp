//
// Created by Marko Jovanovic on 6.2.26..
//

#include "ConsoleOutputStream.h"

void ConsoleOutputStream::write(const std::string &s) {
    if (s.empty()) return;

    std::cout << s << std::flush;

    m_atLineStart = (s.back() == '\n');
    /*
    std::cout << s;
    if (!s.empty()) {
        m_atLineStart = (s.back() == '\n');
    }
    */
}

void ConsoleOutputStream::writeLine(const std::string &s) {
    std::cout << s << std::endl;
    m_atLineStart = true;
}

void ConsoleOutputStream::write(char c) {
    std::cout << c << std::flush;
    m_atLineStart = (c == '\n');
}
