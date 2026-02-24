#include "ConsoleInputStream.h"
#include <iostream>

bool ConsoleInputStream::hasNext() const {
    return !std::cin.eof();
}

std::string ConsoleInputStream::nextToken() {
    std::string s;
    std::cin >> s;
    return s;
}

std::string ConsoleInputStream::nextLine() {
    std::string s;
    std::getline(std::cin, s);
    return s;
}

int ConsoleInputStream::get() {
    int c = std::cin.get();
    return c;
}

bool ConsoleInputStream::eof() const {
    return std::cin.eof();
}