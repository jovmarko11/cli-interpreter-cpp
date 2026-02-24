#include "Execution.h"

void Execution::createCommand(const ParsedCommand &spec, const CommandRegistry &registry, ExecContext& ctx) {
    cleanup();
    m_cmd = registry.create(spec, ctx);
}

void Execution::resolveStreams(const ParsedCommand& spec, const StreamResolver& resolver,
                                const CommandRegistry& registry,
                                InputStream& defaultIn,
                                OutputStream& defaultOut,
                                OutputStream& defaultErr){
    const auto* info = registry.getInfo(spec.name);
    if (!info)
        throw Exception(ErrorType::UnknownCommand, "Unknown command: " + spec.name);
    bool takesSourceArgument = info->takesSourceArgument;
    m_streams = resolver.resolve(spec, takesSourceArgument, defaultIn, defaultOut);
    m_defaultErr = &defaultErr;
}

void Execution::execute(InputStream* input, OutputStream* output, OutputStream* err) {
    InputStream* finalIn = input ? input : m_streams.in;
    OutputStream* finalOut = output ? output : m_streams.out;

    OutputStream* finalErr = err ? err : m_defaultErr;

    m_cmd->setStreams(finalIn, finalOut, finalErr);

    m_cmd->execute();
}

void Execution::cleanup() {
    delete m_streams.ownedIn;
    delete m_streams.ownedOut;
    delete m_cmd;

    m_streams.ownedIn = nullptr;
    m_streams.ownedOut = nullptr;
    m_cmd = nullptr;
    m_defaultErr = nullptr;
}



