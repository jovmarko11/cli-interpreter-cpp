//
// Created by Marko Jovanovic on 7.2.26..
//

#ifndef OOP1PROJEKAT_RMCOMMAND_H
#define OOP1PROJEKAT_RMCOMMAND_H
#include "AbstractCommand/FileCommandBase.h"


class RmCommand : public FileCommandBase {
public:

    explicit RmCommand(const std::string& filename)
        :   FileCommandBase(filename)   { m_name = "Rm Command"; }

    void execute() override;

private:

    void throwError() const override;

    void deleteFile() const;
};


#endif //OOP1PROJEKAT_RMCOMMAND_H