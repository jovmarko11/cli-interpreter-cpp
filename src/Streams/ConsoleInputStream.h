//
// Created by Marko Jovanovic on 6.2.26..
//

#ifndef OOP1PROJEKAT_CONSOLEINPUTSTREAM_H
#define OOP1PROJEKAT_CONSOLEINPUTSTREAM_H
#include "InputAndOutputStream.h"


class ConsoleInputStream : public InputStream {
public:
    ConsoleInputStream() = default;
    ~ConsoleInputStream() override = default;

    bool hasNext() const override;
    std::string nextToken() override;
    std::string nextLine() override;
    int get() override;
    bool eof() const override;

    void clear() override;

    bool isConsole() override { return true; }
};


#endif //OOP1PROJEKAT_CONSOLEINPUTSTREAM_H