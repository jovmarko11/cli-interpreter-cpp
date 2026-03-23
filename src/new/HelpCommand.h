//
// Created by Marko Jovanovic on 16.3.26..
//

#ifndef OOP1PROJEKAT_HELPCOMMAND_H
#define OOP1PROJEKAT_HELPCOMMAND_H
#include "AbstractCommand/CommandBase.h"
#include "Engine/ExecContext.h"
#include <string>
#include "Factory/CommandRegistry.h"


class HelpCommand : public CommandBase {
public:
    HelpCommand(ExecContext& ctx, const std::string& target = "");

    void execute() override;

    std::string usage() const override;
    std::string description() const override;

private:
    ExecContext& m_ctx;
    std::string m_target;
};

inline std::string HelpCommand::usage() const {
    return "help [command]";
}

inline std::string HelpCommand::description() const {
    return "Displays usage information for all commands or detailed help for a specific command.";
}


#endif //OOP1PROJEKAT_HELPCOMMAND_H