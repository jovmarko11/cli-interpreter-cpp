#include "HelpCommand.h"
#include "Exceptions/Exception.h"
#include <algorithm>
#include <sstream>

HelpCommand::HelpCommand(ExecContext& ctx, const std::string& target) 
    : m_ctx(ctx), m_target(target) {
    m_name = "help";
}

void HelpCommand::execute() {
    requireOutput(m_name);
    clearBuffers();

    if (!m_ctx.registry) {
        throw Exception(ErrorType::CommandSemantic, "help: registry not found in context");
    }

    std::ostringstream out;

    if (m_target.empty()) {
        // help → samo usage za sve komande
        std::vector<std::string> names = m_ctx.registry->getCommandNames();
        std::sort(names.begin(), names.end());

        for (const auto& name : names) {
            CommandBase* cmd = m_ctx.registry->createCommand(name, m_ctx);
            if (cmd) {
                out << cmd->usage() << "\n";
                delete cmd;
            }
        }
    } else {
        // help command → usage + description
        CommandBase* cmd = m_ctx.registry->createCommand(m_target, m_ctx);
        if (!cmd) {
            throw Exception(ErrorType::CommandSemantic, "help: unknown command '" + m_target + "'");
        }

        out << cmd->usage() << "\n    " << cmd->description() << "\n";
        delete cmd;
    }

    m_outputText = out.str();
    sendOutput();
}
