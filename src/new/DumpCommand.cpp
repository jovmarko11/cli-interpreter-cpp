#include "DumpCommand.h"

#include "Engine/History.h"
#include "Engine/ILineExecutor.h"
#include "Streams/FileOutputStream.h"

void DumpCommand::execute() {
    int k = std::stoi(m_option);
    size_t historySize = m_ctx.history.size();

    if (k <= 0 || (size_t)k > historySize)
        throw Exception(ErrorType::CommandSemantic, "Dump: Invalid history index");

    size_t target = historySize - k + 1;
    std::string commandLine = m_ctx.history.getKth(target);

    FileOutputStream fileOut(m_filename, FileOutputStream::Mode::Truncate);

    // PRAVIMO NOVI PRIVREMENI KONTEKST
    ExecContext subCtx(
        m_ctx.promptRef,
        m_ctx.shotPrompt,
        m_ctx.oneShot,
        m_ctx.executor,
        m_ctx.history,
        m_ctx.consoleIn,
        m_ctx.defaultIn,
        fileOut,              // ← samo ovo menjamo
        m_ctx.defaultErr,
        m_ctx.registry
    );

    m_ctx.executor.executeLine(commandLine, subCtx);
}

/*
void DumpCommand::execute() {
    if (m_ctx.history.size() == 0)
        throw Exception(ErrorType::CommandSemantic, "dump: history empty");

    std::string last = m_ctx.history.last();

    m_ctx.executor.executeLine(last, m_ctx);
}
*/