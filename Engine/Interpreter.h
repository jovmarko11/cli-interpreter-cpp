#ifndef OOP1PROJEKAT_INTERPRETER_H
#define OOP1PROJEKAT_INTERPRETER_H
#include <string>
#include "CommandRegistry.h"
#include "History.h"
#include "LineExecutor.h"
#include "StreamResolver.h"
#include "../Parser/PipelineParser.h"
#include "Streams/ConsoleOutputStream.h"

/// Interpreter - Glavni deo sistema - cita komande, parsira ih i izvrsava

class InputStream;
class OutputStream;
class CommandReader;
class Parser;

class Interpreter {
public:
    // Konstruktor prima sve klase koje procesiraju komande
    Interpreter(InputStream& in, OutputStream& out, OutputStream& error, CommandReader& reader, LineExecutor& lineExecutor, std::string& promptRef, History& history);

    // Glavna petlja programa
    void run();
    // Menja prompt tokom rada
    void setPrompt(const std::string& prompt);
    const std::string& getPrompt() const;

private:
    InputStream& m_input;
    OutputStream& m_output;
    OutputStream& m_error;
    CommandReader& m_reader;
    LineExecutor& m_executor;
    History& m_history;

    std::string& m_prompt; // U konstruktoru se vrsi inicjalizacija na $

    // Printuje prompt kao signal za spremnost interpretera da ucita nove komandne linije
    void printPrompt() const;
    bool readCommandLine(std::string &line);
    void processLine(const std::string &line);

    bool isFromHistory(const std::string& line) const;

};



inline void Interpreter::setPrompt(const std::string& prompt) { m_prompt = prompt; }

inline const std::string& Interpreter::getPrompt() const { return m_prompt; }

inline void Interpreter::printPrompt() const {

    if (auto* cout = dynamic_cast<ConsoleOutputStream*>(&m_output)) {
        if (!cout->isAtLineStart())
            m_output.write('\n');
    }
    m_output.write(m_prompt + " ");
}


#endif //OOP1PROJEKAT_INTERPRETER_H