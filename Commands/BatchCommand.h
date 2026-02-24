//
// Created by Marko Jovanovic on 19.2.26..
//

#ifndef OOP1PROJEKAT_BATCHCOMMAND_H
#define OOP1PROJEKAT_BATCHCOMMAND_H
#include "AbstractCommand/CommandBase.h"
#include "Engine/Interpreter.h"


class BatchCommand : public CommandBase {
public:
    BatchCommand(ILineExecutor& exec, InputStream& consoleIn);

    void execute() override;

private:
    ILineExecutor& m_exec;
    InputStream&   m_consoleIn;
};


#endif //OOP1PROJEKAT_BATCHCOMMAND_H