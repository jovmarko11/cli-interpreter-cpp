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
#include "../Factory/CommandRegistry.h"

// Parser - upravlja tokenizerom i specijalizovanim parserima za komande, cevovode i redirekcije

class Parser {
public:
    explicit Parser(const CommandRegistry& reg, Syntax syn = {});

    ParsedPipeline parse(const std::string& line) const;

private:
    Syntax m_syn; // definicija specijalnih simbola

    Tokenizer m_tokenizer;             // Razbija string na osnovne tokene
    CommandParser m_cmdParser;         // Parsira argumente i opcije pojedinacne komande
    RedirectionParser m_redirParser;   // Prepoznaje i obradjuje redirekcije
    PipelineParser m_pipeParser;       // Prepoznaje i obradjuje cevovode
};


#endif //OOP1PROJEKAT_PARSER_H