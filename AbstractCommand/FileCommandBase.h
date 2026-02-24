//
// Created by Marko Jovanovic on 11.2.26..
//

#ifndef OOP1PROJEKAT_FILECOMMANDBASE_H
#define OOP1PROJEKAT_FILECOMMANDBASE_H
#include "CommandBase.h"
#include <fstream>


class FileCommandBase : public CommandBase {
public:
    explicit FileCommandBase(const std::string& filename)
        : m_filename(filename) {}

    const std::string& getFilename() const { return m_filename; }

protected:

    std::string m_filename;

    bool fileExists() const; // provera da li fajl postoji je ista za svaku komandu

    virtual void throwError() const = 0; // svaki ispisuje razlicitu gresku
};

inline bool FileCommandBase::fileExists() const {
    const std::ifstream f(m_filename);
    return f.good();
}

#endif //OOP1PROJEKAT_FILECOMMANDBASE_H