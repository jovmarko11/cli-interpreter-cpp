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
    // 1. Preskoči beline
    while (m_pos < m_text.size() && std::isspace(static_cast<unsigned char>(m_text[m_pos]))) {
        m_pos++;
    }

    if (m_pos >= m_text.size()) return "";

    // 2. Uzmi token
    std::string tok;
    while (m_pos < m_text.size() && !std::isspace(static_cast<unsigned char>(m_text[m_pos]))) {
        tok.push_back(m_text[m_pos++]);
    }
    return tok;
}

bool StringInputStream::eof() const {
    return m_pos >= m_text.size();
}

void StringInputStream::clear() {
    m_text.clear();
}