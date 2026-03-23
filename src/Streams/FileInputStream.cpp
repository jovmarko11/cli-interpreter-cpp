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
    auto& mutableFile = const_cast<std::ifstream&>(m_file);

    return m_file.good() && mutableFile.peek() != std::char_traits<char>::eof();
}

std::string FileInputStream::nextToken() {
    std::string s;
    if (m_file >> std::ws >> s) {
        return s;
    }
    return "";
}

std::string FileInputStream::nextLine() {
    std::string s;

    if (std::getline(m_file, s)) {
        if (!s.empty() && s.back() == '\r') s.pop_back();
    }

    if (m_file.eof() && !s.empty()) {
        m_file.clear();
    }

    return s;
}

int FileInputStream::get() {
    int c = m_file.get();
    return c;
}

bool FileInputStream::eof() const {
    return m_file.eof();
}

void FileInputStream::clear() {
    m_file.clear();
}
