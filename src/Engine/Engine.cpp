#include "Engine.h"

#include "ExecContext.h"
#include "Parser/Parser.h"
#include "Pipeline/PipeFlowController.h"
#include "StreamResolverNew.h"
#include "Streams/ConsoleOutputStream.h"

Engine::Engine(Parser &parser, const CommandRegistry &registry, StreamResolverNew &resolver)
    :   m_parser(parser)
    ,   m_registry(registry)
    ,   m_resolver(resolver) {}

void Engine::executeLine(const std::string& line, ExecContext &ctx) {
    // Parsiranje linije u sturkturu komandi i redirekcija
    ParsedPipeline pl = m_parser.parse(line);

    if (pl.commands.empty())
        return;

    // Odabir nacina izvrsavanja
    if (pl.commands.size() == 1) {
        executeSingle(pl.commands[0], ctx);
    }
    else {
        executePipeline(pl, ctx);
    }
}

void Engine::executeSingle(const ParsedCommand& spec, ExecContext& ctx) {
    executeCommand(spec, ctx, false,ctx.defaultIn,ctx.defaultOut);
}

void Engine::executePipeline(const ParsedPipeline& pl, ExecContext& ctx) {
    int count = (int) pl.commands.size();

    // Kontroler kreira sve neophodne PipeStream-ove izmedju komandi
    PipeFlowController controller;
    auto links = controller.buildLinks(count);

    for (int i = 0; i < count; ++i) {

        const ParsedCommand& spec = pl.commands[i];
        const auto* info = m_registry.getInfo(spec.name);

        if (!info)
            throw Exception(
                ErrorType::UnknownCommand,"Unknown command: " + spec.name);

        bool first = (i == 0);
        bool last  = (i == count - 1);

        validatePipelinePosition(spec, *info, first, last);

        // Odredjivanje default tokova
        InputStream&  defaultIn  = first ? ctx.defaultIn : *links[i].pipeIn;
        OutputStream& defaultOut = last  ? ctx.defaultOut : *links[i].pipeOut;

        bool inputFromPipe = !first;

        executeCommand(spec, ctx, inputFromPipe, defaultIn, defaultOut);
    }
}

void Engine::executeCommand(const ParsedCommand& spec, ExecContext& ctx, bool inputFromPipe, InputStream& defaultIn, OutputStream& defaultOut) {
    const auto* info = m_registry.getInfo(spec.name);

    if (!info)
        throw Exception(ErrorType::UnknownCommand,"Unknown command: " + spec.name);


    if (auto* cout = dynamic_cast<ConsoleOutputStream*>(&defaultOut)) {
        if (!cout->isAtLineStart())
            defaultOut.write('\n');
    }

    CommandBase* cmd = m_registry.create(spec, ctx);
    StreamResolverNew::Streams streams = m_resolver.resolve(spec, info->hasInput, info->hasOutput, info->takesSourceArgument, inputFromPipe, defaultIn, defaultOut);

    try {
        cmd->setStreams(streams.in, streams.out, &ctx.defaultErr);
        cmd->execute();
    }
    catch (...) {
        deleteStreams(streams);
        delete cmd;
        throw;
    }
    deleteStreams(streams);
    delete cmd;
}

void Engine::validatePipelinePosition(const ParsedCommand& spec, const CommandRegistry::CommandInfo& info, bool first, bool last) const {
    // Komanda mora da prima input ako nije prva
    if (!first && !info.hasInput)
        throw Exception(ErrorType::StreamSemantic, "Command " + spec.name + " cannot receive input from pipe");

    // Komanda mora da proizvodi output ako nije poslednja
    if (!last && !info.hasOutput)
        throw Exception(ErrorType::StreamSemantic, "Command " + spec.name + " cannot send output to pipe");

    // Zabranjena redirekcija inputa u sredini pipeline-a
    if (!first && spec.in.present)
        throw Exception(ErrorType::StreamSemantic, "Input redirection not allowed inside pipeline");

    // Zabranjena redirekcija outputa u sredini pipeline-a
    if (!last && spec.out.present)
        throw Exception(ErrorType::StreamSemantic,"Output redirection not allowed inside pipeline");
}


void Engine::deleteStreams(StreamResolverNew::Streams& s) {
    delete s.ownedIn;
    delete s.ownedOut;

    s.ownedIn = nullptr;
    s.ownedOut = nullptr;
}
