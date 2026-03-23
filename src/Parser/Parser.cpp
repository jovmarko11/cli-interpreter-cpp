#include "Parser.h"

#include "Exceptions/Exception.h"

Parser::Parser(const CommandRegistry& registry, Syntax syn)
    : m_syn(std::move(syn))
    , m_tokenizer(m_syn)
    , m_cmdParser(registry)
    , m_redirParser(m_syn)
    , m_pipeParser(m_cmdParser, m_redirParser, m_syn) {}


ParsedPipeline Parser::parse(const std::string& line) const {
    TokenizeResult tr = m_tokenizer.tokenize(line);

    if (tr.tokens.empty())
        throw Exception(ErrorType::Syntax, "Empty command line");

    return m_pipeParser.parseTokens(tr.tokens);
}