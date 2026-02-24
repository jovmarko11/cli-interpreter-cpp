
#include "FileOutputStream.h"

FileOutputStream::FileOutputStream(const std::string& filename, Mode mode){
    if (mode == Mode::Append) {
        m_file.open(filename, std::ios::out | std::ios::app); // append mod
    }
    else {
        m_file.open(filename, std::ios::out | std::ios::trunc); // truncate mod
    }

    if (!m_file)
        throw std::runtime_error("Could not open file: " + filename);
}

void FileOutputStream::write(const std::string& s) {
    m_file << s;
}

void FileOutputStream::writeLine(const std::string& s) {
    m_file << s << '\n';
}

void FileOutputStream::write(char c) {
    m_file << c;
}