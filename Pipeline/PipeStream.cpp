#include "PipeStream.h"
#include <cctype>

int PipeStream::get() {
    if (eof())
        return EOF;
    return (unsigned char)  m_buffer[m_pos++];
}

std::string PipeStream::nextLine() {
    std::string line;

    while (hasNext()) {
        char c = m_buffer[m_pos++];
        if (c == '\n') break;
        line.push_back(c);
    }
    return line;
}

std::string PipeStream::nextToken() {
    std::string token;

    // preskakanje whitespace
    while (hasNext() && std::isspace(static_cast<unsigned char>(m_buffer[m_pos]))) {
        m_pos++;
    }

    // citanje do sledeceg whitespace
    while (hasNext() && !std::isspace(static_cast<unsigned char>(m_buffer[m_pos]))) {
        token.push_back(m_buffer[m_pos++]);
    }
    return token;
}
