
#ifndef OOP1PROJEKAT_ICOMMAND_H
#define OOP1PROJEKAT_ICOMMAND_H
#include <string>

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute() = 0;
};

#endif //OOP1PROJEKAT_ICOMMAND_H