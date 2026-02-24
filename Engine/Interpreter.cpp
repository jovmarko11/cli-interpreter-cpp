#include "Interpreter.h"
#include "Execution.h"
#include "../Streams/InputAndOutputStream.h"
#include "Exceptions/Exception.h"
#include "Reader/CommandReader.h"
#include "Parser/Parser.h"

Interpreter::Interpreter(InputStream& in,
                        OutputStream& out,
                        OutputStream& error,
                        CommandReader& reader,
                        LineExecutor& lineExecutor,
                        std::string& promptRef,
                        History& history)
    :   m_input(in)
    ,   m_output(out)
    ,   m_error(error)
    ,   m_reader(reader)
    ,   m_executor(lineExecutor)
    ,   m_prompt(promptRef)
    ,   m_history(history)
{}

void Interpreter::run() {
    while (true) {
        printPrompt();

        std::string line;
        if (!readCommandLine(line)) {
            break; // EOF
        }

        if (line.empty()) continue;

        processLine(line);
    }
}

bool Interpreter::readCommandLine(std::string& line) {
    auto rr = m_reader.readLine();
    if (rr.eof) return false;

    line = rr.line;
    return true;
}

void Interpreter::processLine(const std::string& line) {
    try {
        m_executor.executeLine(line, m_input, m_output, m_error);
        m_history.addExecuted(line);
    }
    catch (const Exception& e) {
        m_output.writeLine(e.what());

    }
    catch (const std::exception& e) {
        m_output.writeLine("Internal Error");
    }
}