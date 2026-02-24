#include "StringInputStream.h"
#include <cstdio>

bool StringInputStream::hasNext() const  { return m_pos < m_text.size(); }

int StringInputStream::get() {
    if (!hasNext()) return EOF;
    return static_cast<unsigned char> (m_text[m_pos++]);
}

std:: string StringInputStream::nextLine() {
    std::string line;
    while (hasNext()) {
        int c = get();
        if (c == EOF || c < 0) break;

        char ch = static_cast<char>(c);
        if (ch == '\n') break;
        line.push_back(ch);
    }
    return line;
}

std::string StringInputStream::nextToken() {
    // preskoci beline
    while (hasNext()) {
        auto c = static_cast<unsigned char>(m_text[m_pos]);
        if (!std::isspace(c)) break;
        m_pos++;
    }

    // uzmi token do sledece beline
    std::string tok;
    while (hasNext()) {
        auto c = static_cast<unsigned char>(m_text[m_pos]);
        if (std::isspace(c)) break;
        tok.push_back(static_cast<char>(m_text[m_pos]));
        m_pos++;
    }

    return tok; // vraca "" kad nema vise tokena
}

bool StringInputStream::eof() const {
    return m_pos >= m_text.size();
}