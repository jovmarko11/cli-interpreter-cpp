#ifndef OOP1PROJEKAT_TRUNCATECOMMAND_H
#define OOP1PROJEKAT_TRUNCATECOMMAND_H
#include "AbstractCommand/FileCommandBase.h"

// Komanda prazni sadrzaj postojeceg fajla

class TruncateCommand : public FileCommandBase {
public:

    explicit TruncateCommand(const std::string& filename);

    void execute() override;

    std::string usage() const override;

    std::string description() const override;

private:

    void throwError() const override;

    void deleteContent() const;
};

inline std::string TruncateCommand::usage() const {
    return "truncate filename";
}

inline std::string TruncateCommand::description() const {
    return "Clears the contents of the specified file without deleting the file itself";
}




#endif //OOP1PROJEKAT_TRUNCATECOMMAND_H