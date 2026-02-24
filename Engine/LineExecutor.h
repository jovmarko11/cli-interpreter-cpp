//
// Created by Marko Jovanovic on 20.2.26..
//

#ifndef OOP1PROJEKAT_LINEEXECUTOR_H
#define OOP1PROJEKAT_LINEEXECUTOR_H
#include "ILineExecutor.h"
#include "StreamResolver.h"
#include "Parser/Parser.h"

class LineExecutor : public ILineExecutor {
public:
    LineExecutor(const CommandRegistry& registry, Parser& parser, StreamResolver& resolver, std::string& promptRef, History& h);

    void executeLine(
        const std::string& line,
        InputStream& defaultIn,
        OutputStream& defaultOut,
        OutputStream& defaultErr
    ) override;

private:
    const CommandRegistry& m_registry;
    Parser& m_parser;
    StreamResolver& m_resolver;
    std::string& m_promptRef;
    History& m_history;

    void executeOne(const ParsedCommand& spec, InputStream& defaultIn, OutputStream& defaultOut, OutputStream& defaultErr);
    void executePipeline(const ParsedPipeline& pl, InputStream& defaultIn, OutputStream& defaultOut, OutputStream& defaultErr);
};


#endif //OOP1PROJEKAT_LINEEXECUTOR_H