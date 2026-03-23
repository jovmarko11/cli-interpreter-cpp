#ifndef OOP1PROJEKAT_INTERPRETER_H
#define OOP1PROJEKAT_INTERPRETER_H
#include <string>
#include "../Factory/CommandRegistry.h"
#include "ExecContext.h"
#include "History.h"
#include "../Parser/PipelineParser.h"
#include "Streams/ConsoleOutputStream.h"
#include "Engine/ExecContext.h"

// Interpreter - glavni upravljac sistema
// Read Evaluate Print Loop

class InputStream;
class OutputStream;
class CommandReader;
class Parser;

class ILineExecutor;

class Interpreter {
public:
    Interpreter(ILineExecutor& executor, ExecContext& ctx, CommandReader& reader);

    // Pokrece beskonacnu petlju za izvrsavanje komandi
    void run();

private:
    ILineExecutor& m_executor;
    ExecContext& m_ctx;
    CommandReader& m_reader;

    void printPrompt();

    void processLine(const std::string& line);
};


#endif //OOP1PROJEKAT_INTERPRETER_H