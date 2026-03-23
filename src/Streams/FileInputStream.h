//
// Created by Marko Jovanovic on 6.2.26..
//

#ifndef OOP1PROJEKAT_FILEINPUTSTREAM_H
#define OOP1PROJEKAT_FILEINPUTSTREAM_H
#include <fstream>
#include "InputAndOutputStream.h"


class FileInputStream : public InputStream {
public:
    explicit FileInputStream(const std::string& filename);
    ~FileInputStream() override = default;

    bool hasNext() const override;

    std::string nextToken() override;

    std::string nextLine() override;

    int get() override;

    bool eof() const override;

    void clear() override;

    bool isConsole() override { return false; }

private:
    std::ifstream m_file;
};


#endif //OOP1PROJEKAT_FILEINPUTSTREAM_H