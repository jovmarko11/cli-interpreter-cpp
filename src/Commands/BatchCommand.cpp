#include "BatchCommand.h"

#include "Exceptions/Exception.h"
#include "Reader/CommandReader.h"
#include "Streams/FileInputStream.h"
#ifdef __APPLE__
#include <unistd.h> // Dodato za isatty i STDIN_FILENO
#endif

BatchCommand::BatchCommand(ExecContext& ctx)
    : m_globalCtx(ctx)
{
    m_name = "batch";
}

void BatchCommand::execute() {
    requireInput(m_name);
    requireOutput(m_name);
    requireError(m_name);

    // citac koji izvlaci linije sa Input Stream-a
    CommandReader reader(*s_input);

    ExecContext batchCtx = createBatchCtx();

    while (true) {
        ReadResult rr = reader.readLine();
        if (rr.eof) break; // izlazak iz petlje pri nailasku na EOF - kraj toka
        if (rr.line.empty()) continue; // prazne linije se ignorisu

        try {
            // izvrsavanje linije u batchCtx kontekstu
            m_globalCtx.executor.executeLine(rr.line, batchCtx);

            // ciscenje stanja globalne konzole ukoliko je neka komanda prijavila EOF
            if (m_globalCtx.consoleIn.eof()) {
                m_globalCtx.consoleIn.clear();
            }
        }
        catch (const Exception& e) {
            s_error->writeLine(e.what());
        }
        catch (const std::exception& e) {
            s_error->writeLine(std::string("Internal Error: ") + e.what());
        }
        catch (...) {
            s_error->writeLine("Internal Error");
        }
    }
}

ExecContext BatchCommand::createBatchCtx() {
    return ExecContext(
        m_globalCtx.promptRef,
        m_globalCtx.shotPrompt,
        m_globalCtx.oneShot,
        m_globalCtx.executor,
        m_globalCtx.history,
        m_globalCtx.consoleIn,  // defaultIn: konzola (za komande bez arg)
        m_globalCtx.consoleIn,  // consoleIn: sistemski ulaz
        *s_output,              // defaultOut - trenutni izlaz
        *s_error,               // defaultErr - trenutni error
        m_globalCtx.registry    // registry
        );

}
