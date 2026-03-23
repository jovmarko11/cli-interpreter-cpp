//
// Created by Marko Jovanovic on 10.3.26..
//

#ifndef OOP1PROJEKAT_TAILCOMMAND_H
#define OOP1PROJEKAT_TAILCOMMAND_H
#include "AbstractCommand/CommandBase.h"


class TailCommand : public CommandBase {
public:

    TailCommand(int lineCount);

    void execute() override;

    std::string usage() const override;

    std::string description() const override;

private:
    int lineCount;
};

inline std::string TailCommand::usage() const {
    return "tail -nN [argument]";
}

inline std::string TailCommand::description() const {
    return "Outputs the last N lines from the input stream. "
           "Lines are printed starting from the end of the input.";
}


#endif //OOP1PROJEKAT_TAILCOMMAND_H