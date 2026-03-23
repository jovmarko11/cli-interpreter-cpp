#ifndef OOP1PROJEKAT_FILECOMMANDBASE_H
#define OOP1PROJEKAT_FILECOMMANDBASE_H
#include "CommandBase.h"
#include <fstream>
#include <string>

// Bazna klasa za komande koje direktno upravljaju fajlovima (touch, truncate, rm)
// Obezbedjuje zajednicko stanje (ime fajla) i metode za sistemsku proveru

class FileCommandBase : public CommandBase {
public:
    explicit FileCommandBase(const std::string& filename)
        : m_filename(filename) {}

    const std::string& getFilename() const { return m_filename; }

protected:

    std::string m_filename; // ime fajla nad kojim se izvrsavaju komande

    bool fileExists() const; // provera da li fajl postoji

    virtual void throwError() const = 0; // svaka izvedena klasa  definise svoju poruku o gresci
};

// vraca true ako je fajl uspesno otvoren
inline bool FileCommandBase::fileExists() const {
    const std::ifstream f(m_filename);
    return f.good();
}

#endif //OOP1PROJEKAT_FILECOMMANDBASE_H