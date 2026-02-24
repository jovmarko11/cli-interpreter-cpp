//
// Created by Marko Jovanovic on 13.2.26..
//

#ifndef OOP1PROJEKAT_TOKENIZER_H
#define OOP1PROJEKAT_TOKENIZER_H
#include <utility>

#include "ParserStructs.h"
#include "Reader/ReaderStructs.h"
#include "Parser/Syntax.h"

/// Tokenizer - razbija liniju na tokene (komande, argumenti, pipe, quoted stringovi)
///
class Tokenizer {
public:
    explicit Tokenizer(Syntax syn = {}) : m_syn(std::move(syn)) {}
    // Glavna metoda koja parsira celu liniju u niz tokena
    TokenizeResult tokenize(const std::string& line) const;

private:
    // Sintaksna pravila
    Syntax m_syn;

    // Preskace whitespace
    static void skipWhitespace(const std::string &line, size_t &pos) ;

    // Prepoznaje pipe |
    bool parsePipe(const std::string &line, size_t &pos, TokenizeResult &result) const;

    // Prepoznaje format za TrCommand -"what"
    bool parseDashQuoted(const std::string &line, size_t &pos, TokenizeResult &result) const;

    // Prepoznaje quoted string "..."
    bool parseQuoted(const std::string &line, size_t &pos, TokenizeResult &result) const;

    // Parsira obican token (bez navodnika i bez operatora)
    void parseWord(const std::string &line, size_t &pos, TokenizeResult &result) const;

    bool parseRedir(const std::string &line, size_t &pos, TokenizeResult &result) const;
};

#endif //OOP1PROJEKAT_TOKENIZER_H