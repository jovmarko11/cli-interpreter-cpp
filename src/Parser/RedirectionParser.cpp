#include "RedirectionParser.h"

#include "Exceptions/Exception.h"

RedirectionParser::RedirectionParser(Syntax syn)
    :   m_syn(std::move(syn)) {}


RedirectionParser::Result RedirectionParser::extract(const std::vector<Token>& segment) const {
    if (!segment.empty() && isRedirOp(segment.back()))
        throw Exception(ErrorType::Syntax, "Redirection missing filename");

    Result r = parseTrailingRedirs(segment);

    ensureNoMidRedirs(r.core);

    if (r.core.empty())
        throw Exception(ErrorType::Syntax, "Missing command before redirection");

    return r;
}

bool RedirectionParser::isRedirOp(const Token& token) const {
    if (token.quoted) return false;
    if (m_syn.isRedirToken(token.text))
        return true;
    return false;
}


void RedirectionParser::ensureNoMidRedirs(const std::vector<Token>& core) const {
    for (const auto& t : core) {
        if (isRedirOp(t))
            throw Exception(ErrorType::Syntax, "Redirection must appear at the end of the command");
    }
}


void RedirectionParser::ensureValidFilename(const Token &filenameTok) const {
    if (filenameTok.text.empty())
        throw Exception(ErrorType::Syntax, "Redirection missing filename");

    if (!filenameTok.quoted && m_syn.isPipeToken(filenameTok.text))
        throw Exception(ErrorType::Syntax, "Invalid redirection target");

    if (isRedirOp(filenameTok))
        throw Exception(ErrorType::Syntax, "Redirection missing filename");
}


void RedirectionParser::applyOneRedir(const Token& opTok, const Token& filenameTok, Result& r) const {
    if (opTok.text == m_syn.inToken()) { // <
        if (r.in.present)
            throw Exception(ErrorType::Syntax, "Multiple input redirections");

        r.in.present = true;
        r.in.filename = filenameTok.text;
        return;
    }

    if (opTok.text == m_syn.outToken()) { // >
        if (r.out.present)
            throw Exception(ErrorType::Syntax, "Multiple output redirections");

        r.out.present = true;
        r.out.filename = filenameTok.text;
        r.out.mode = OutMode::Truncate;
        return;
    }

    if (opTok.text == m_syn.appendToken()) { // >>
        if (r.out.present)
            throw Exception(ErrorType::Syntax, "Multiple output redirections");

        r.out.present = true;
        r.out.filename = filenameTok.text;
        r.out.mode = OutMode::Append;
        return;
    }

    throw Exception(ErrorType::System, "Internal error: unknown redirection operator");
}


RedirectionParser::Result RedirectionParser::parseTrailingRedirs(const std::vector<Token>& segment) const {
    Result r;
    r.core = segment;

    int i = (int)r.core.size() - 1;

    while (i >= 1) {
        const Token& filenameTok = r.core[i];
        const Token& opTok = r.core[i - 1];

        if (!isRedirOp(opTok))
            break;

        ensureValidFilename(filenameTok);
        applyOneRedir(opTok, filenameTok, r);

        r.core.erase(r.core.begin() + (i - 1), r.core.begin() + (i + 1));
        i = (int)r.core.size() - 1;
    }

    return r;
}