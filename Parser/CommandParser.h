
#ifndef OOP1PROJEKAT_COMMANDPARSER_H
#define OOP1PROJEKAT_COMMANDPARSER_H
#include <map>
#include <string>
#include <vector>
#include "ICommandLineParser.h"
#include "ParserStructs.h"
#include "../Reader/ReaderStructs.h"
#include "Parser/Tokenizer.h"

class CommandRegistry;
class ICommandLineParser;

/// CommandParser - parsira jednu komandu u ParsedCommand strukturu
class CommandParser {
public:
    // Prima registry kako bi znao koji parser komanda koristi
    explicit CommandParser(const CommandRegistry& registry);

    // Parsira vec tokenizovanu liniju u ParsedCommand - koristi se i iz PipelineParser-a
    ParsedCommand parseTokens(const std::vector<Token>& tokens) const;


private:

    // Daje odgovarajuci derived parser (ICommandLineParser) za komandu
    const CommandRegistry& m_registry;
};




#endif //OOP1PROJEKAT_COMMANDPARSER_H