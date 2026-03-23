
#ifndef OOP1PROJEKAT_INPUTANDOUTPUTSTREAM_H
#define OOP1PROJEKAT_INPUTANDOUTPUTSTREAM_H
#include <string>


class InputStream {
public:
    virtual ~InputStream() = default;
    InputStream() = default;

    virtual bool hasNext() const = 0;

    virtual std::string nextToken() = 0;
    virtual std::string nextLine() = 0;
    virtual int get() = 0;
    virtual bool eof() const = 0;

    virtual void clear() = 0;

    virtual bool isConsole() = 0;

};

class OutputStream {
public:
    virtual ~OutputStream() = default;
    OutputStream() = default;

    virtual void write(const std::string& s) = 0;
    virtual void write(char c) = 0;
    virtual void writeLine(const std::string& s) = 0;

    // Overload za int
    void writeLine(int value) {
        writeLine(std::to_string(value));
    }
    /*
    void write(int value) {
        write(std::to_string(value));
    }
    */
};

inline OutputStream& operator << (OutputStream& out, const std::string& s) {
    out.write(s);
    return out;
}

inline OutputStream& operator << (OutputStream& out, const char* s) {
    out.write(std::string(s));
    return out;
}

inline OutputStream& operator << (OutputStream& out, char c) {
    out.write(std::string(1, c));
    return out;
}

inline OutputStream& operator << (OutputStream& out, int value) {
    out.write(std::to_string(value));
    return out;
}

#endif //OOP1PROJEKAT_INPUTANDOUTPUTSTREAM_H