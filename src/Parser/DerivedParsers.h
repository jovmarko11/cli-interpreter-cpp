#ifndef OOP1PROJEKAT_DERIVEDPARSERS_H
#define OOP1PROJEKAT_DERIVEDPARSERS_H
#include "ICommandLineParser.h"

// Parser za jednostavne komande (ime [argument])
class SimpleCommandParser : public ICommandLineParser {
public:
    ParsedCommand parseTokens(const std::vector<Token>& tokens) const override;
};

// Parser za komande sa opcijama (ime -opt [argument])
class OptionCommandParser : public ICommandLineParser {
public:
    ParsedCommand parseTokens(const std::vector<Token>& tokens) const override;
};

// Parser za tr komandu zbog specificne sintakse (tr [source] -"what" ["with"])
class TrCommandParser : public ICommandLineParser {
public:
    explicit TrCommandParser(Syntax syn = {}) : m_syn(std::move(syn)) {}

    ParsedCommand parseTokens(const std::vector<Token>& tokens) const override;

private:
    Syntax m_syn;
    bool parseWhat(const std::vector<Token>& tokens, size_t& idx, std::string& what, std::string& error) const;

    static bool parseWith(const std::vector<Token>& tokens, size_t& idx, std::string& with, std::string& error);
};


#endif //OOP1PROJEKAT_DERIVEDPARSERS_H