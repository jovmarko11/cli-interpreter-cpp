
#include "Tokenizer.h"

#include "ParserStructs.h"
#include "Exceptions/Exception.h"

TokenizeResult Tokenizer::tokenize(const std::string &line) const {
    TokenizeResult result;

    std::size_t pos = 0;
    const std::size_t n = line.size();

    while (pos < n) {
        // preskakanje razmaka
        skipWhitespace(line, pos);
        if (pos >= n) break;

        // Pipe - poseban token ako je | van navodnika
        if (parsePipe(line, pos, result)) continue;

        if (parseRedir(line, pos, result)) continue;

        if (parseDashQuoted(line, pos, result)) continue;

        if (parseQuoted(line, pos, result)) continue;

        parseWord(line, pos, result);
    }

    return result;
}

void Tokenizer::skipWhitespace(const std::string& line, size_t& pos) {
    while (pos < line.size() &&
           std::isspace(static_cast<unsigned char>(line[pos]))) {
        pos++;
           }
}

bool Tokenizer::parsePipe(const std::string& line, size_t& pos, TokenizeResult& result) const {
    if (m_syn.isPipe(line[pos])) {
        result.tokens.push_back(Token{std::string(1, m_syn.pipe), false}); // dodavanje znaka za pipe
        pos++;
        return true;
    }
    return false;
}

bool Tokenizer::parseDashQuoted(const std::string& line, size_t& pos, TokenizeResult& result) const {
    const size_t n = line.size();

    if (line[pos] == m_syn.dash && pos + 1 < n && line[pos + 1] == m_syn.quote) {
        size_t start = pos;
        result.tokens.push_back(Token{std::string(1, m_syn.dash), false});
        pos++; // preskoci -
        pos++; // preskoci "

        std::string q;

        while (pos < n && line[pos] != m_syn.quote)  q += line[pos++];


        if (pos >= n)
            throw Exception(ErrorType::Lexical, "Unterminated string literal", (int)start);

        pos++; // preskoci zavrsni quote "
        result.tokens.push_back(Token{q, true});
        return true;
    }

    return false;
}

bool Tokenizer::parseQuoted(const std::string& line, size_t& pos, TokenizeResult& result) const {
    const size_t n = line.size();

    if (line[pos] == m_syn.quote) {
        size_t start = pos;
        pos++; // preskoci ulazni quote "
        std::string token;

        while (pos < n && line[pos] != m_syn.quote)  token += line[pos++];

        if (pos >= n)
            throw Exception(ErrorType::Lexical, "Unterminated string literal", (int)start);

        pos++; // preskoci zavrsni quote "
        result.tokens.push_back(Token{token, true});
        return true;
    }
    return false;
}

void Tokenizer::parseWord(const std::string& line, size_t& pos, TokenizeResult& result) const {
    const size_t n = line.size();
    std::string token;

    while (pos < n) {
        char c = line[pos];
        if (std::isspace(static_cast<unsigned char>(c)) || m_syn.isPipe(c) || m_syn.isRedir(c)) break;
        token += c;
        pos++;
    }
    if (!token.empty()) {
        result.tokens.push_back(Token{token, false});
    }
}

bool Tokenizer::parseRedir(const std::string& line, size_t& pos, TokenizeResult& result) const {
    const size_t n = line.size();
    char c = line[pos];

    if (c == m_syn.redirOut) {
        // >> append
        if (pos + 1 < n && line[pos + 1] == m_syn.redirOut) {
            result.tokens.push_back(Token{">>", false});
            pos += 2;
            return true;
        }

        // > truncate
        result.tokens.push_back(Token{">", false});
        pos++;
        return true;
    }

    if (c == m_syn.redirIn) {
        result.tokens.push_back(Token{"<", false});
        pos++;
        return true;
    }

    return false;
}