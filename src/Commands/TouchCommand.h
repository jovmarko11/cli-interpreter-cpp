#ifndef OOP1PROJEKAT_TOUCHCOMMAND_H
#define OOP1PROJEKAT_TOUCHCOMMAND_H
#include "AbstractCommand/FileCommandBase.h"

// Komanda kreira novi prazan fajl u sistemu

class TouchCommand : public FileCommandBase{
public:

    explicit TouchCommand(const std::string& filename);

    void execute() override;

    std::string usage() const override;

    std::string description() const override;

private:

    void throwError() const override;

    void createEmptyFile() const;
};

inline std::string TouchCommand::usage() const {
    return "touch filename";
}

inline std::string TouchCommand::description() const {
    return "Creates a new empty file with the specified name in the current directory. If the file already exists, an error is reported";
}






#endif //OOP1PROJEKAT_TOUCHCOMMAND_H