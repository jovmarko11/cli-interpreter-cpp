#ifndef OOP1PROJEKAT_PROGRAM_H
#define OOP1PROJEKAT_PROGRAM_H
#include "Engine.h"
#include "History.h"
#include "Parser/Parser.h"
#include "Reader/CommandReader.h"
#include "Streams/ConsoleInputStream.h"
#include "Streams/ConsoleOutputStream.h"
#include "Engine/ExecContext.h"
#include "Engine/Interpreter.h"

// Program - drzi sve resurse sistema po vrednosti

class Program {
public:
    Program();

    void run();

private:
    // I/O Streams
    ConsoleInputStream  m_consoleIn;
    ConsoleOutputStream m_consoleOut;
    ConsoleOutputStream m_consoleErr;

    // Core state
    std::string m_prompt;
    std::string m_shotPrompt;
    bool m_oneShot;

    // History
    History m_history;

    // Core engine components
    CommandRegistry m_registry;
    Parser m_parser;
    StreamResolverNew m_resolver;
    Engine m_engine;

    // Execution context
    ExecContext m_ctx;

    // Reader
    CommandReader m_reader;

    // Glavni Interpreter
    Interpreter m_interpreter;
};



#endif //OOP1PROJEKAT_PROGRAM_H