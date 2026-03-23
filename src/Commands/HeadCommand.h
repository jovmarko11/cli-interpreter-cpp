//
// Created by Marko Jovanovic on 21.2.26..
//

#ifndef OOP1PROJEKAT_HEADCOMMAND_H
#define OOP1PROJEKAT_HEADCOMMAND_H
#include "AbstractCommand/CommandBase.h"

// ispisuje prvih N linija sa ulaznog toka

class HeadCommand : public CommandBase {
public:
    explicit HeadCommand(int lineCount);

    void execute() override;

    std::string usage() const override;

    std::string description() const override;

private:
    int m_lineCount = 0; // broj linija koje komanda treba da ispise
};

inline std::string HeadCommand::usage() const {
    return "head -nN [argument]";
}

inline std::string HeadCommand::description() const {
    return "Outputs the first N lines from the input stream and ignores the remaining content. The number of lines N must follow the -n option directly.";
}


#endif //OOP1PROJEKAT_HEADCOMMAND_H