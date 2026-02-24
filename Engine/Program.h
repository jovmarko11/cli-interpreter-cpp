#ifndef OOP1PROJEKAT_PROGRAM_H
#define OOP1PROJEKAT_PROGRAM_H
#include "History.h"
#include "Interpreter.h"
#include "Parser/Parser.h"
#include "Reader/CommandReader.h"
#include "Streams/ConsoleInputStream.h"
#include "Streams/ConsoleOutputStream.h"

/// Program - klasa koja sadrzi sve objkete po vrednosti
/// Na osnovu tih objekata se konstruise Interpreter
/// run() metoda pokrece ceo program pozivanjem interpreter.run()

class Program {
public:
    Program();

    void run();

private:
    // I/O Streams
    ConsoleInputStream  m_in;
    ConsoleOutputStream m_out;
    ConsoleOutputStream m_err;

    // Core state
    std::string m_prompt;

    // Parsing i Reading
    CommandRegistry m_registry;
    Parser m_parser;
    CommandReader m_reader;

    // History
    History m_history;

    // Engine helpers
    StreamResolver m_resolver;
    LineExecutor m_executor;

    // Glavni Interpreter
    Interpreter m_interpreter;
};



#endif //OOP1PROJEKAT_PROGRAM_H