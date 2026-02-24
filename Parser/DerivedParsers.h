#ifndef OOP1PROJEKAT_DERIVEDPARSERS_H
#define OOP1PROJEKAT_DERIVEDPARSERS_H
#include "ICommandLineParser.h"

class SimpleCommandParser : public ICommandLineParser {
public:
    ParsedCommand parseTokens(const std::vector<Token>& tokens) const override;
};
// Potencijalno da dodam Syntax
class OptionCommandParser : public ICommandLineParser {
public:
    ParsedCommand parseTokens(const std::vector<Token>& tokens) const override;
};

class HeadCommandParser : public ICommandLineParser {
public:
    ParsedCommand parseTokens(const std::vector<Token>& tokens) const override;
};

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