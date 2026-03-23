//
// Created by Marko Jovanovic on 5.3.26..
//

#include "ExecCommand.h"

#include <iostream>
#include <ostream>

ExecCommand::ExecCommand() {
    m_name = "exec";
}

bool isOperator(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return true;
    return false;
}

void ExecCommand::execute() {
    requireInput(m_name);
    requireOutput(m_name);
    requireInput(m_name);

    clearBuffers();
    loadInput();

    std::string op1s;
    std::string op2s;
    bool seenOperator = false;
    for (auto c : m_inputText) {
        if (std::isspace(c))
            continue;
        if (isOperator(c)) {
            seenOperator = true;
            operat = c;
            continue;
        }
        if (!seenOperator)
            op1s += c;
        else
            op2s += c;
    }

    try {
        op1 = std::stod(op1s);
        op2 = std::stod(op2s);
    }
    catch (...) {
        throw Exception(ErrorType::CommandSemantic, m_name + ": Invalid operands");
    }

    if (operat == "+") {
        result = op1 + op2;
    }
    else if (operat == "-") {
        result = op1 - op2;
    }
    else if (operat == "*") {
        result = op1 * op2;
    }
    else if (operat == "/") {
        result = op1 / op2;
    }
    else
        throw Exception(ErrorType::CommandSemantic, m_name + ": Invalid operator");

    std::cout << "Res = " << result << std::endl;
    std::cout << "Op1 = " << op1 << std::endl;
    std::cout << "Op2 = " << op2 << std::endl;
    std::cout << "Operator = " << operat << std::endl;
    m_outputText = std::to_string(result);
    sendOutput();
}


