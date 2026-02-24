#include "LastCommand.h"

LastCommand::LastCommand(History& history, ILineExecutor& executor)
    : m_history(history)
    , m_executor(executor)
{
    m_name = "last";
}


void LastCommand::execute() {
    requireOutput(m_name);
    requireError(m_name);

    std::string previous = m_history.last();
    m_executor.executeLine(previous, *m_input, *m_output, *m_error);
}
