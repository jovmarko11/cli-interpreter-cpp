//
// Created by Marko Jovanovic on 5.3.26..
//

#ifndef OOP1PROJEKAT_EXECCOMMAND_H
#define OOP1PROJEKAT_EXECCOMMAND_H
#include "AbstractCommand/CommandBase.h"


class ExecCommand : public CommandBase {
public:
    ExecCommand();

    void execute() override;

    std::string usage() const override;

    std::string description() const override;

private:
    double op1;
    double op2;
    std::string operat;
    double result;
};

inline std::string ExecCommand::usage() const {
    return "exec <operand1> <operator> <operand2>";
}

inline std::string ExecCommand::description() const {
    return "Performs a basic arithmetic operation between two operands. "
           "Supported operators include +, -, *, and /. "
           "Prints the result to the output stream.";
}
#endif //OOP1PROJEKAT_EXECCOMMAND_H