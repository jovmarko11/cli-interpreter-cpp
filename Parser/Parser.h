//
// Created by Marko Jovanovic on 17.2.26..
//

#ifndef OOP1PROJEKAT_PARSER_H
#define OOP1PROJEKAT_PARSER_H
#include "CommandParser.h"
#include "PipelineParser.h"
#include "RedirectionParser.h"
#include "Syntax.h"
#include "Tokenizer.h"
#include "Engine/CommandRegistry.h"


class Parser {
public:
    explicit Parser(const CommandRegistry& reg, Syntax syn = {});
    ParsedPipeline parse(const std::string& line) const;

private:
    Syntax m_syn;

    Tokenizer m_tokenizer;
    CommandParser m_cmdParser;
    RedirectionParser m_redirParser;
    PipelineParser m_pipeParser;
};


#endif //OOP1PROJEKAT_PARSER_H