#include "CommandParser.h"

#include "ParserStructs.h"
#include "../Factory/CommandRegistry.h"
#include "Exceptions/Exception.h"

CommandParser::CommandParser(const CommandRegistry &registry) : m_registry(registry) {}

ParsedCommand CommandParser::parseTokens(const std::vector<Token>& tokens) const {
    if (tokens.empty())
        throw Exception(ErrorType::Syntax, "Empty command");


    const std::string& name = tokens[0].text;
    ICommandLineParser* parser = m_registry.getParser(name);

    if (!parser)
        throw Exception(ErrorType::UnknownCommand, "Unknown command: " + name);

    return parser->parseTokens(tokens);
}