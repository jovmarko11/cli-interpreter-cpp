#ifndef OOP1PROJEKAT_TOUCHCOMMAND_H
#define OOP1PROJEKAT_TOUCHCOMMAND_H
#include "AbstractCommand/FileCommandBase.h"


class TouchCommand : public FileCommandBase{
public:

    explicit TouchCommand(const std::string& filename)
        :   FileCommandBase(filename)   { m_name = "touch"; }

    void execute() override;

private:

    void throwError() const override;

    void createEmptyFile() const;
};




#endif //OOP1PROJEKAT_TOUCHCOMMAND_H