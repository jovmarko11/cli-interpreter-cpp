#include "LastCommand.h"

LastCommand::LastCommand(ExecContext& ctx)
    :   m_ctx(ctx)
{
    m_name = "last";
}


void LastCommand::execute() {
    requireOutput(m_name);
    requireError(m_name);

    std::string previous = m_ctx.history.last();

    if (previous.empty())
        throw std::runtime_error("No last command has been found.");

    if (previous == "last") {
        s_error->writeLine("last: cannot repeat 'last' command");
        return;
    }


    ExecContext lastExecCtx = createLastCtx();

    try {
        m_ctx.executor.executeLine(previous, lastExecCtx);
    }
    catch (const Exception&) {
        s_error->writeLine("Error executing last command: " + previous);
    }
}

ExecContext LastCommand::createLastCtx() {
    return ExecContext(
        m_ctx.promptRef,
        m_ctx.shotPrompt,
        m_ctx.oneShot,
        m_ctx.executor,
        m_ctx.history,
        *s_input,
        m_ctx.consoleIn,    // sistemski consoleIn
        *s_output,          // defaultOut: ono što je dodeljeno last komandi
        *s_error,           // defaultErr: -||-
        m_ctx.registry
    );
}
