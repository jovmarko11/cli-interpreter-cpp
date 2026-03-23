//
// Created by Marko Jovanovic on 7.2.26..
//

#ifndef OOP1PROJEKAT_ICOMMANDLINEPARSER_H
#define OOP1PROJEKAT_ICOMMANDLINEPARSER_H
#include "CommandParser.h"
#include "ParserStructs.h"

/// ICommandLineParser - interfejs za parsiranje pojedinacnih komandi

class ICommandLineParser {
public:
    // virtuelni destruktor - polimorfizam
    virtual ~ICommandLineParser() = default;

    // Parsira tokene konkretne komande - vraca ParsedCommand
    virtual ParsedCommand parseTokens(const std::vector<Token>& tokens) const = 0;
};

#endif //OOP1PROJEKAT_ICOMMANDLINEPARSER_H