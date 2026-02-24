//
// Created by Marko Jovanovic on 6.2.26..
//

#ifndef OOP1PROJEKAT_ECHOCOMMAND_H
#define OOP1PROJEKAT_ECHOCOMMAND_H
#include "AbstractCommand/CommandBase.h"


class EchoCommand : public CommandBase {
public:
    EchoCommand();

    void execute() override;

};


#endif //OOP1PROJEKAT_ECHOCOMMAND_H