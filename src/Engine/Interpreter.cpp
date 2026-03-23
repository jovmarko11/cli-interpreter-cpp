#include "Interpreter.h"
#include "ExecContext.h"
#include "../Streams/InputAndOutputStream.h"
#include "Exceptions/Exception.h"
#include "Reader/CommandReader.h"
#include "Parser/Parser.h"

Interpreter::Interpreter(ILineExecutor& executor, ExecContext& ctx, CommandReader& reader)
    :   m_executor(executor)
    ,   m_ctx(ctx)
    ,   m_reader(reader)
{}

void Interpreter::run() {
    printPrompt(); // prvi prompt pre ulaska u petlju

    while (true) {
        // 1. Citanje linije sa ulaznog toka
        ReadResult rr = m_reader.readLine();

        if (m_ctx.defaultIn.isConsole()) {
            if (auto* cout = dynamic_cast<ConsoleOutputStream*>(&m_ctx.defaultOut)) {
                cout->setAtLineStart(true);
            }
        }

        if (rr.eof) {
            // Ako ulaz nije konzola (batch mod), EOF znači kraj fajla i prekidanje petlju
            if (!m_ctx.defaultIn.isConsole()) {
                break;
            }
            continue;
        }
        // 2. Preskakanje praznih unosa
        if (rr.line.empty()) {
            printPrompt();
            continue;
        }
        // 3. Obrada linije
        processLine(rr.line);

        // 4. Ispis prompta za sledeci unos komandne linije
        printPrompt();
    }
}

void Interpreter::processLine(const std::string& line) {
    try {
        // Prosledjivanje linije Engine-u na izvrsavanje
        m_executor.executeLine(line, m_ctx);

        // Ako je komanda uspesno izvrsena dodaje se u istoriju
        m_ctx.history.addExecuted(line);
    }
    catch (const Exception& e) {
        // Specificne greske sistema (Syntax, Lexical...)
        m_ctx.defaultErr.writeLine(e.what());
    }
    catch (const std::exception& e) {
        // Neocekivane greske
        m_ctx.defaultErr.writeLine("Internal Error: " + std::string(e.what()));
    }
    catch (...) {
        // Poslednja linija odbrane od greski
        m_ctx.defaultErr.writeLine("Unknown Internal Error");
    }
}

void Interpreter::printPrompt() {
    // Provera da li je trenutni izlaz konzola
    if (auto* cout = dynamic_cast<ConsoleOutputStream*>(&m_ctx.defaultOut)) {

        // Ako kursor nije na pocetku reda, prelazi se u novi red
        if (!cout->isAtLineStart())
            m_ctx.defaultOut.write('\n');
    }


    if (m_ctx.oneShot) {
        m_ctx.defaultOut.write(m_ctx.shotPrompt + " ");
        m_ctx.oneShot = false;
    }
    else {
        m_ctx.defaultOut.write(m_ctx.promptRef + " ");
    }
}