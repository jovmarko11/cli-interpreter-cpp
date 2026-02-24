

#include "DerivedParsers.h"
#include "ParserStructs.h"
#include "Exceptions/Exception.h"

ParsedCommand SimpleCommandParser::parseTokens(const std::vector<Token>& tokens) const {
    if (tokens.empty())
        throw Exception(ErrorType::Syntax, "Empty command");

    ParsedCommand cmd;
    cmd.option = "";
    cmd.name = tokens[0].text;

    for (size_t i = 1; i < tokens.size(); ++i) {
        cmd.args.push_back(tokens[i]);
    }

    return cmd;
}
// Potencijalno da dodam Syntax
ParsedCommand OptionCommandParser::parseTokens(const std::vector<Token>& tokens) const {
    if (tokens.empty())
        throw Exception(ErrorType::Syntax, "Empty command");

    if (tokens.size() < 2)
        throw Exception(ErrorType::Syntax, "Missing option");

    ParsedCommand cmd;
    cmd.option.clear();
    cmd.args.clear();

    cmd.name = tokens[0].text;
    cmd.option = tokens[1].text;

    if (cmd.option.size() < 2 || cmd.option[0] != '-')
        throw Exception(ErrorType::Syntax, "Invalid option format");

    cmd.option = cmd.option.substr(1); // -w -> w bez  "-"

    for (size_t i = 2; i < tokens.size(); ++i) {
        cmd.args.push_back(tokens[i]);
    }

    return cmd;
}

ParsedCommand TrCommandParser::parseTokens(const std::vector<Token>& tokens) const {
    if (tokens.size() < 2)
        throw Exception(ErrorType::Syntax, R"(tr: expected format: tr -"what" ["with"])");

    ParsedCommand cmd;
    cmd.name = tokens[0].text;

    size_t idx = 1;
    std::string what;
    std::string with;
    std::string error;

    if (!parseWhat(tokens, idx, what, error))
        throw Exception(ErrorType::Syntax, error);

    if (!parseWith(tokens, idx, with, error))
        throw Exception(ErrorType::Syntax, error);

    if (idx != tokens.size())
        throw Exception(ErrorType::Syntax, R"(tr: too many arguments)");

    cmd.args.push_back(Token{what, true});
    if (!with.empty())
        cmd.args.push_back(Token{with, true});

    return cmd;
}

bool TrCommandParser::parseWhat(const std::vector<Token>& tokens, size_t& idx, std::string& what, std::string& error) const{
    const std::string dashTok(1, m_syn.dash);

    // format: tr - "what
    if (tokens[idx].text == dashTok) {
        if (idx + 1 >= tokens.size() || !tokens[idx + 1].quoted) {
            error = R"(tr: expected format: tr -"what" ["with"])";
            return false;
        }
        what = tokens[idx + 1].text;
        idx += 2; //
    }

    // format: tr -"what"
    else if (!tokens[idx].text.empty() && tokens[idx].text[0] == dashTok[0]) {
        std::string t = tokens[idx].text;

        if (t.size() < 3 || t[1] != m_syn.quote || t.back() != m_syn.quote) {
            error = R"(tr: expected format: tr -"what" ["with"])";
            return false;
        }
        // izvadi izmedju navodnika
        what = t.substr(2, t.size() - 3);
        idx += 1;
    }

    else {
        error = R"(tr: expected format: tr -"what" ["with"])";
        return false;
    }

    if (what.empty()) {
        error = "tr: what cannot be empty";
        return false;
    }
    return true;
}

bool TrCommandParser::parseWith(const std::vector<Token>& tokens, size_t& idx, std::string& with, std::string& error) {
    if (idx >= tokens.size())
        return true; // delete mode

    if (!tokens[idx].quoted) {
        error = R"(tr: with must be quoted)";
        return false;
    }

    with = tokens[idx].text;
    idx += 1;
    return true;
}

