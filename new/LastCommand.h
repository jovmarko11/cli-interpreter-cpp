//
// Created by Marko Jovanovic on 23.2.26..
//

#ifndef OOP1PROJEKAT_LASTCOMMAND_H
#define OOP1PROJEKAT_LASTCOMMAND_H
#include "AbstractCommand/CommandBase.h"
#include "Engine/History.h"
#include "Engine/LineExecutor.h"


class LastCommand : public CommandBase {
public:
    LastCommand(History& history, ILineExecutor& executor);

    void execute() override;

private:
    History& m_history;
    ILineExecutor& m_executor;
};


#endif //OOP1PROJEKAT_LASTCOMMAND_H