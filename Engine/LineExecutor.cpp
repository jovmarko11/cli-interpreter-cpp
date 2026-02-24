#include "LineExecutor.h"

#include "Execution.h"
#include "Exceptions/Exception.h"
#include "Pipeline/PipeFlowController.h"

LineExecutor::LineExecutor(const CommandRegistry& registry, Parser& parser,
                           StreamResolver& resolver, std::string& promptRef,
                           History& history)
    : m_registry(registry)
    , m_parser(parser)
    , m_resolver(resolver)
    , m_promptRef(promptRef)
    , m_history(history)
{}

void LineExecutor::executeLine(const std::string& line, InputStream& defaultIn, OutputStream& defaultOut, OutputStream& defaultErr)
{
    ParsedPipeline pl = m_parser.parse(line);

    if (pl.commands.size() == 1)
        executeOne(pl.commands[0], defaultIn, defaultOut, defaultErr);
    else
        executePipeline(pl, defaultIn, defaultOut, defaultErr);
}


void LineExecutor::executeOne(const ParsedCommand& spec, InputStream& defaultIn, OutputStream& defaultOut, OutputStream& defaultErr){
    ExecContext ctx(m_promptRef, *this, defaultIn, defaultErr, m_history);
    Execution execution;
    execution.createCommand(spec, m_registry, ctx);

    execution.resolveStreams(spec, m_resolver, m_registry, defaultIn, defaultOut, defaultErr);
    execution.execute(nullptr, nullptr, nullptr);
}


void LineExecutor::executePipeline(const ParsedPipeline& pl, InputStream& defaultIn, OutputStream& defaultOut, OutputStream& defaultErr){
    int count = (int)pl.commands.size();

    PipeFlowController controller;
    auto links = controller.buildLinks(count);

    ExecContext ctx(m_promptRef, *this, defaultIn, defaultErr, m_history);

    for (int i = 0; i < count; i++) {
        const ParsedCommand& spec = pl.commands[i];
        auto info = m_registry.getInfo(spec.name);

        if (!info)
            throw Exception(ErrorType::UnknownCommand, "Unknown command: " + spec.name);

        if (i > 0 && !info->hasInput)
            throw Exception(ErrorType::StreamSemantic,
                "Command " + spec.name + " cannot appear after a pipe (no input stream)");

        if (i < count - 1 && !info->hasOutput)
            throw Exception(ErrorType::StreamSemantic,
                "Command " + spec.name + " cannot be piped into another command (no output stream)");

        bool hasPipeIn  = (links[i].pipeIn  != nullptr);
        bool hasPipeOut = (links[i].pipeOut != nullptr);

        if (hasPipeIn && spec.in.present)
            throw Exception(ErrorType::StreamSemantic,
                "Input redirection not allowed in the middle of a pipeline");

        if (hasPipeOut && spec.out.present)
            throw Exception(ErrorType::StreamSemantic,
                "Output redirection not allowed in the middle of a pipeline");

        Execution execution;
        execution.createCommand(spec, m_registry, ctx);
        execution.resolveStreams(spec, m_resolver, m_registry, defaultIn, defaultOut, defaultErr);
        execution.execute(links[i].pipeIn, links[i].pipeOut, nullptr);
    }
}
