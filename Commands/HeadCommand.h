//
// Created by Marko Jovanovic on 21.2.26..
//

#ifndef OOP1PROJEKAT_HEADCOMMAND_H
#define OOP1PROJEKAT_HEADCOMMAND_H
#include "AbstractCommand/CommandBase.h"


class HeadCommand : public CommandBase {
public:
    explicit HeadCommand(int lineCount);

    void execute() override;

private:
    int m_lineCount = 0;
};


#endif //OOP1PROJEKAT_HEADCOMMAND_H