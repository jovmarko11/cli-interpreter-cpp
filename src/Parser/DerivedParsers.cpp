#include "DerivedParsers.h"
#include "ParserStructs.h"
#include "Exceptions/Exception.h"

// SimpleCommandParser
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

// OptionCommandParser
ParsedCommand OptionCommandParser::parseTokens(const std::vector<Token>& tokens) const {
    if (tokens.empty())
        throw Exception(ErrorType::Syntax, "Empty command");


    ParsedCommand cmd;
    cmd.option.clear();
    cmd.args.clear();

    cmd.name = tokens[0].text;
    size_t argStartIndex = 1;

    // Ako postoji drugi token i pocinje sa '-'
    if (tokens.size() > 1 && !tokens[1].text.empty() && tokens[1].text[0] == '-') {

        if (tokens[1].text.size() < 2)
            throw Exception(ErrorType::Syntax, "Invalid option format");

        cmd.option = tokens[1].text.substr(1); // skida '-'
        argStartIndex = 2;
    }

    // Sve posle toga su argumenti
    for (size_t i = argStartIndex; i < tokens.size(); ++i) {
        cmd.args.push_back(tokens[i]);
    }

    return cmd;
}

// TrCommandParser
ParsedCommand TrCommandParser::parseTokens(const std::vector<Token>& tokens) const {
    if (tokens.size() < 2)
        throw Exception(ErrorType::Syntax, R"(tr: expected format: tr [source] -"what" ["with"])");

    ParsedCommand cmd;
    cmd.name = tokens[0].text;

    size_t idx = 1;

    std::string source;
    std::string what;
    std::string with;
    std::string error;

    //  Proveri da li postoji source
    if (!tokens[idx].text.empty() && tokens[idx].text[0] != m_syn.dash) {
        source = tokens[idx].text;
        cmd.args.push_back(tokens[idx]);   // sačuvaj originalni token (quoted bitan!)
        cmd.hasSource = true;
        idx++;
    }

    // Parsiraj what
    if (idx >= tokens.size() || !parseWhat(tokens, idx, what, error))
        throw Exception(ErrorType::Syntax, error);

    // Parsiraj with
    if (!parseWith(tokens, idx, with, error))
        throw Exception(ErrorType::Syntax, error);

    // Ne sme biti više tokena
    if (idx != tokens.size())
        throw Exception(ErrorType::Syntax, R"(tr: too many arguments)");

    // Dodaj what i with
    cmd.args.push_back(Token{what, true});
    if (!with.empty())
        cmd.args.push_back(Token{with, true});

    return cmd;
}

bool TrCommandParser::parseWhat(const std::vector<Token>& tokens, size_t& idx, std::string& what, std::string& error) const{
    const std::string dashTok(1, m_syn.dash);

    // format: token[0] = "-", token[1] = "tekst" (quoted = true)
    if (tokens[idx].text == dashTok) {
        if (idx + 1 >= tokens.size() || !tokens[idx + 1].quoted) {
            error = R"(tr: expected format: tr -"what" ["with"])";
            return false;
        }
        what = tokens[idx + 1].text;
        idx += 2;
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


