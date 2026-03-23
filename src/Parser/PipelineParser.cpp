#include "PipelineParser.h"

#include "Exceptions/Exception.h"

PipelineParser::PipelineParser(const CommandParser& cmdParser, const RedirectionParser& redirParser, Syntax syn)
    : m_cmdParser(cmdParser)
    , m_syn(std::move(syn))
    , m_redirParser(redirParser) {}


ParsedPipeline PipelineParser::parseTokens(const std::vector<Token>& tokens) const {
    if (tokens.empty())
        throw Exception(ErrorType::Syntax, "Empty command line");

    ParsedPipeline pl;                 // više ti ne treba pl.ok/pl.error
    std::vector<Token> segment;

    for (const auto& token : tokens) {
        if (!token.quoted && m_syn.isPipeToken(token.text)) {
            processSegment(segment, pl);
            segment.clear();
        } else {
            segment.push_back(token);
        }
    }

    processSegment(segment, pl);
    return pl;
}


// obrada jedne komande iz segmenta
void PipelineParser::processSegment(const std::vector<Token> &segment, ParsedPipeline &pl) const {
    // Prazan segment, dve cevi zaredom ili jedna na pocetku ili kraju
    if (segment.empty())
        throw Exception(ErrorType::Syntax, "Syntax error: empty command between pipes");

    // pozivanje RedirectionParsera
    auto rr = m_redirParser.extract(segment);
    // Pozivanje CommandParsera
    ParsedCommand cmd = m_cmdParser.parseTokens(rr.core);

    cmd.in = rr.in;
    cmd.out = rr.out;
    pl.commands.push_back(cmd);
}
