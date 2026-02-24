#include "FileInputStream.h"
#include <stdexcept>
#include <fstream>

FileInputStream::FileInputStream(const std::string& filename) : m_file(filename)
{
    if (!m_file.is_open()) {
        throw std::runtime_error("Error opening file " + filename);
    }
}

bool FileInputStream::hasNext() const {
    return m_file.good() && !m_file.eof();
}

std::string FileInputStream::nextToken() {
    std::string s;
    m_file >> s;
    return s;
}

std::string FileInputStream::nextLine() {
    std::string s;
    std::getline(m_file, s);

    // windows crlf:
    if (!s.empty() && s.back() == '\r') s.pop_back();

    return s;
}

int FileInputStream::get() {
    int c = m_file.get();
    return c;
}

bool FileInputStream::eof() const {
    return m_file.eof();
}
