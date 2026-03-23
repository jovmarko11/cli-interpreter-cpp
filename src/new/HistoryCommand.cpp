
#include "HistoryCommand.h"

#include "Engine/History.h"

HistoryCommand::HistoryCommand(ExecContext& ctx) : m_ctx(ctx) {m_name = "history";}

void HistoryCommand::execute() {
    requireOutput(m_name);
    clearBuffers();

    std::string result;
    size_t totalLines = m_ctx.history.size();

    if (totalLines == 0) {
        m_outputText = "History is empty.\n";
    } else {
        for (size_t i = 1; i <= totalLines; ++i) {
            // Koristimo tvoju getKth metodu koja baca Exception za nevalidan indeks
            std::string line = m_ctx.history.getKth(i);

            // Formatiranje: "indeks linija\n"
            result += std::to_string(i) + " " + line + "\n";
        }
        m_outputText = result;
    }

    sendOutput();
}
