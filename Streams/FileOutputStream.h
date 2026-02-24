#ifndef OOP1PROJEKAT_FILEOUTPUTSTREAM_H
#define OOP1PROJEKAT_FILEOUTPUTSTREAM_H
#include <fstream>
#include "InputAndOutputStream.h"


class FileOutputStream : public OutputStream {
public:

    enum class Mode {   Truncate, Append   };

    explicit FileOutputStream(const std::string& filename, Mode mode);
    ~FileOutputStream() override = default;

    using OutputStream::write;
    using OutputStream::writeLine;

    void write(const std::string& s) override;
    void write(char c) override;
    void writeLine(const std::string& s) override;

private:
    std::ofstream m_file;
};


#endif //OOP1PROJEKAT_FILEOUTPUTSTREAM_H