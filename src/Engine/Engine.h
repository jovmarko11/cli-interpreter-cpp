//
// Created by Marko Jovanovic on 25.2.26..
//

#ifndef OOP1PROJEKAT_ENGINE_H
#define OOP1PROJEKAT_ENGINE_H
#include "ILineExecutor.h"
#include "Parser/ParserStructs.h"
#include "StreamResolverNew.h"
#include "Engine/ExecContext.h"
#include "Factory/CommandRegistry.h"

// Engine - glavni pokretac sistema
// Povezuje parsiranje, proveru registara komandi, razresavanje tokova i poziva izvrsavanje komande

class Parser;
class StreamResolver;
class CommandRegistry;

class Engine : public ILineExecutor {
public:
    Engine(Parser &parser, const CommandRegistry &registry, StreamResolverNew &resolver);

    // Implementacija interface-a ILineExecutr - prima sirovu liniju teksta i pokrece obradu
    void executeLine(const std::string& line, ExecContext &ctx) override;

private:
    Parser& m_parser;
    const CommandRegistry& m_registry;
    StreamResolverNew& m_resolver;

    // Izvrsava liniju koja sadrzi samo jednu samostalnu komandu
    void executeSingle(const ParsedCommand &spec, ExecContext &ctx);

    // Izvrsava liniju koja sadrzi komande povezane u cevovod
    void executePipeline(const ParsedPipeline& pl, ExecContext& ctx);

    // Finalna metoda koja instancira, povezuje tokove, i poziva execute() izvrsavanje svake komande
    void executeCommand(const ParsedCommand& spec, ExecContext& ctx, bool inputFromPipe, InputStream& defaultIn, OutputStream& defaultOut);

    // Semanticka validacija pipeline-a
    void validatePipelinePosition(const ParsedCommand &spec, const CommandRegistry::CommandInfo &info, bool first, bool last) const;

    // Brisanje s.ownedIn i s.ownedOut streamova
    void deleteStreams(StreamResolverNew::Streams &s);
};


#endif //OOP1PROJEKAT_ENGINE_H