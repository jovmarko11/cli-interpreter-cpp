//
// Created by Marko Jovanovic on 12.2.26..
//

#ifndef OOP1PROJEKAT_PIPELINEPARSER_H
#define OOP1PROJEKAT_PIPELINEPARSER_H
#include "CommandParser.h"
#include "RedirectionParser.h"
#include "Parser/ParserStructs.h"
#include "Parser/Syntax.h"

/// PipelineParser - klasa zaduzena za

class PipelineParser {
public:
    // koristi CommandParser za parsiranje svake komande (segmenta)
    explicit PipelineParser(const CommandParser& cmdParser, const RedirectionParser& redirParser, Syntax syn = {});

    ParsedPipeline parseTokens(const std::vector<Token>& tokens) const;

private:
    // Sintaksna pravila
    Syntax m_syn;

    // Parsiranje pojedinacnih komandi
    const CommandParser& m_cmdParser;
    const RedirectionParser& m_redirParser;

    void processSegment(const std::vector<Token>& segment, ParsedPipeline& pl) const;

};


#endif //OOP1PROJEKAT_PIPELINEPARSER_H