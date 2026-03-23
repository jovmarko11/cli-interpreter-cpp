//
// Created by Marko Jovanovic on 3.3.26..
//

#ifndef OOP1PROJEKAT_HISTORYCOMMAND_H
#define OOP1PROJEKAT_HISTORYCOMMAND_H
#include "AbstractCommand/CommandBase.h"
#include "Engine/ExecContext.h"


class HistoryCommand : public CommandBase {
public:
    explicit HistoryCommand(ExecContext& ctx);

    void execute() override;

    std::string usage() const override;

    std::string description() const override;

private:
    ExecContext& m_ctx;
};

inline std::string HistoryCommand::usage() const {
    return "history";
}

inline std::string HistoryCommand::description() const {
    return "Displays the list of previously executed commands with their indices. "
           "Commands are ordered from oldest to newest.";
}


#endif //OOP1PROJEKAT_HISTORYCOMMAND_H