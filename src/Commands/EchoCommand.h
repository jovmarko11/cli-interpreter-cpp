//
// Created by Marko Jovanovic on 6.2.26..
//

#ifndef OOP1PROJEKAT_ECHOCOMMAND_H
#define OOP1PROJEKAT_ECHOCOMMAND_H
#include "AbstractCommand/CommandBase.h"

// Komanda prosledjuje podatke sa ulaznog na izlazni tok bez izmena

class EchoCommand : public CommandBase {
public:
    EchoCommand();

    void execute() override;

    std::string reverseOutput();

    std::string usage() const override;

    std::string description() const override;
};

inline std::string EchoCommand::usage() const {
    return "echo [source]";
}

inline std::string EchoCommand::description() const {
    return "Prints input text to output";
}




#endif //OOP1PROJEKAT_ECHOCOMMAND_H