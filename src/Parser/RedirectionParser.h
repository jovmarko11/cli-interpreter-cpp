//
// Created by Marko Jovanovic on 16.2.26..
//

#ifndef OOP1PROJEKAT_REDIRECTIONPARSER_H
#define OOP1PROJEKAT_REDIRECTIONPARSER_H
#include "ParserStructs.h"
#include "Syntax.h"
/// RedirectionParser - skida redirekcije (<,>,>>) sa kraja segmenta
/// popunjava cmd.in i cmd.out iz RedirSpec
/// vraca core - tokene bez redirekcija (ciste argumente)
/// validacija - redirekcija mora biti na kraju i mora imati filename

class RedirectionParser {
public:
    struct Result {
        std::vector<Token> core;
        RedirSpec in;
        RedirSpec out;
    };

    explicit RedirectionParser(Syntax syn);

    Result extract(const std::vector<Token>& segment) const;

private:
    Syntax m_syn;

    bool isRedirOp(const Token& token) const;

    void ensureNoMidRedirs(const std::vector<Token> &core) const;

    void ensureValidFilename(const Token &filenameTok) const;

    void applyOneRedir(const Token &opTok, const Token &filenameTok, Result &r) const;

    Result parseTrailingRedirs(const std::vector<Token> &segment) const;

};


#endif //OOP1PROJEKAT_REDIRECTIONPARSER_H