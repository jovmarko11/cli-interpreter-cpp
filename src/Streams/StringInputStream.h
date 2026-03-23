#ifndef OOP1PROJEKAT_STRINGINPUTSTREAM_H
#define OOP1PROJEKAT_STRINGINPUTSTREAM_H
#include <cctype>
#include "InputAndOutputStream.h"


class StringInputStream : public InputStream {
public:

    explicit StringInputStream(std::string text) : m_text(std::move(text)) {}
    ~StringInputStream() override = default;

    bool hasNext() const override;

    int get() override;

    std:: string nextLine() override;

    std::string nextToken() override;

    bool eof() const override;

    void clear() override;

    bool isConsole() override { return false; }

private:

    std::string m_text;
    size_t m_pos = 0;

};


#endif //OOP1PROJEKAT_STRINGINPUTSTREAM_H