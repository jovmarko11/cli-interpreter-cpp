//
// Created by Marko Jovanovic on 14.2.26..
//

#ifndef OOP1PROJEKAT_SYNTAX_H
#define OOP1PROJEKAT_SYNTAX_H
#include <string>

struct Syntax {
    char pipe = '|';
    char quote = '"';
    char dash = '-';
    char redirIn = '<';
    char redirOut = '>';
    std::string redirAppend = ">>";

    bool isPipe(char c) const   {   return c == pipe;   }
    bool isQuote(char c) const  {   return c == quote;  }
    bool isDash(char c) const   {   return c == dash;   }
    bool isRedir(char c) const  {    return c == redirIn || c == redirOut;  }

    bool isAppendOp(const std::string& s) const         {   return s == redirAppend; }
    bool startsWithAppend(const std::string& s) const   {   return s.rfind(redirAppend, 0) == 0; }
    std::string pipeToken() const { return std::string(1, pipe); }

    std::string inToken() const  { return std::string(1, redirIn); }
    std::string outToken() const { return std::string(1, redirOut); }
    std::string appendToken() const { return redirAppend; }

    bool isRedirToken(const std::string& s) const {
        return s == inToken() || s == outToken() || s == appendToken();
    }

    bool isPipeToken(const std::string& s) const { return s == pipeToken(); }

};

#endif //OOP1PROJEKAT_SYNTAX_H