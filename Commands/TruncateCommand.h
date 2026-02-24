#ifndef OOP1PROJEKAT_TRUNCATECOMMAND_H
#define OOP1PROJEKAT_TRUNCATECOMMAND_H
#include "AbstractCommand/FileCommandBase.h"


class TruncateCommand : public FileCommandBase {
public:

    explicit TruncateCommand(const std::string& filename)
        :   FileCommandBase(filename)   { m_name = "Truncate Command"; }

    void execute() override;

private:

    void throwError() const override;

    void deleteContent() const;
};


#endif //OOP1PROJEKAT_TRUNCATECOMMAND_H