//
// Created by Marko Jovanovic on 19.2.26..
//

#include "BatchCommand.h"

#include "Exceptions/Exception.h"
#include "Reader/CommandReader.h"
#include "Streams/FileInputStream.h"

BatchCommand::BatchCommand(ILineExecutor& exec, InputStream& consoleIn)
    : m_exec(exec), m_consoleIn(consoleIn)
{
    m_name = "batch";
}

void BatchCommand::execute() {
    requireInput(m_name);
    requireOutput(m_name);
    requireError(m_name);

    CommandReader reader(*m_input);

    while (true) {
        ReadResult rr = reader.readLine();
        if (rr.eof) break;
        if (rr.line.empty()) continue;

        try {
            m_exec.executeLine(rr.line, m_consoleIn, *m_output, *m_error);
        }
        catch (const Exception& e) {
            m_error->writeLine(e.what());
        }
        catch (const std::exception& e) {
            m_error->writeLine(std::string("Internal Error: ") + e.what());
        }
        catch (...) {
            m_error->writeLine("Internal Error");
        }
    }
}
