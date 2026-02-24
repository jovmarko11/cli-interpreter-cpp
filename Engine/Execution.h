//
// Created by Marko Jovanovic on 17.2.26..
//

#ifndef OOP1PROJEKAT_EXECUTION_H
#define OOP1PROJEKAT_EXECUTION_H
#include "CommandRegistry.h"
#include "StreamResolver.h"
#include "Parser/ParserStructs.h"

class InputStream;
class OutputStream;

class Execution {
public:
    Execution() = default;
    ~Execution() { cleanup(); }

    Execution(const Execution&) = delete;
    Execution& operator=(const Execution&) = delete;


    void createCommand(const ParsedCommand& spec, const CommandRegistry& registry, ExecContext& ctx);

    void resolveStreams(const ParsedCommand& spec,
                    const StreamResolver& resolver,
                    const CommandRegistry& registry,
                    InputStream& defaultIn,
                    OutputStream& defaultOut,
                    OutputStream& defaultErr);

    void execute(InputStream* input, OutputStream* output, OutputStream* err);

private:
    CommandBase* m_cmd = nullptr;
    StreamResolver::Streams m_streams;
    OutputStream* m_defaultErr = nullptr;

    void cleanup();
};



#endif //OOP1PROJEKAT_EXECUTION_H