
#ifndef OOP1PROJEKAT_ICOMMAND_H
#define OOP1PROJEKAT_ICOMMAND_H
#include <string>

// Interface iz kog svaka komanda nasledjuje execute metodu

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute() = 0;
};

#endif //OOP1PROJEKAT_ICOMMAND_H