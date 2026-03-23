//
// Created by Marko Jovanovic on 6.2.26..
//

#ifndef OOP1PROJEKAT_CONSOLEOUTPUTSTREAM_H
#define OOP1PROJEKAT_CONSOLEOUTPUTSTREAM_H
#include <iostream>
#include "InputAndOutputStream.h"


class ConsoleOutputStream : public OutputStream {
public:
    ConsoleOutputStream() = default;
    ~ConsoleOutputStream() override = default;

    using OutputStream::write;
    using OutputStream::writeLine;

    void write(const std::string& s) override;
    void write(char c) override;
    void writeLine(const std::string& s) override;

    bool isAtLineStart() const { return m_atLineStart; }

    void setAtLineStart(bool b) { m_atLineStart = b; }

private:
    bool m_atLineStart = true;
};


#endif //OOP1PROJEKAT_CONSOLEOUTPUTSTREAM_H