//
// Created by Marko Jovanovic on 23.2.26..
//

#ifndef OOP1PROJEKAT_LASTCOMMAND_H
#define OOP1PROJEKAT_LASTCOMMAND_H
#include "AbstractCommand/CommandBase.h"
#include "Engine/History.h"
#include "Engine/ILineExecutor.h"


class LastCommand : public CommandBase {
public:
    explicit LastCommand(ExecContext& ctx);

    void execute() override;

    ExecContext createLastCtx();

    std::string usage() const override;

    std::string description() const override;

private:
    ExecContext& m_ctx;
};

inline std::string LastCommand::usage() const {
    return "last";
}

inline std::string LastCommand::description() const {
    return "Re-executes the last command from history. "
           "The command 'last' itself cannot be repeated to prevent infinite recursion.";
}

#endif //OOP1PROJEKAT_LASTCOMMAND_H