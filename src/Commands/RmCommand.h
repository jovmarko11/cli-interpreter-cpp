//
// Created by Marko Jovanovic on 7.2.26..
//

#ifndef OOP1PROJEKAT_RMCOMMAND_H
#define OOP1PROJEKAT_RMCOMMAND_H
#include "AbstractCommand/FileCommandBase.h"

// Komanda brise zadati fajl iz sistema

class RmCommand : public FileCommandBase {
public:

    explicit RmCommand(const std::string& filename);

    void execute() override;

    std::string usage() const override;

    std::string description() const override;

private:
    // baca izuzetak ukoliko fajl ne postoji
    void throwError() const override;

};

inline std::string RmCommand::usage() const {
    return "rm filename";
}

inline std::string RmCommand::description() const {
    return "Deletes the specified file from the file system";
}


#endif //OOP1PROJEKAT_RMCOMMAND_H