//
// Created by Marko Jovanovic on 25.2.26..
//

#ifndef OOP1PROJEKAT_EXECCONTEXT_H
#define OOP1PROJEKAT_EXECCONTEXT_H
#include <string>

// ExecContext - objedinjuje stanje potrebno za izvrsavanje i daje potrebne resurse komandama

class ILineExecutor;
class History;
class InputStream;
class OutputStream;
class CommandRegistry;

struct ExecContext {
    std::string& promptRef;
    std::string& shotPrompt;
    bool& oneShot;

    ILineExecutor& executor;
    History& history;

    InputStream& consoleIn; // primarni ulazni tok sa standardnog ulaza

    InputStream& defaultIn; // podrazumevani ulazni tok za komandu (console ili pipe)
    OutputStream& defaultOut; // podrazumevani izlaz za komandu
    OutputStream& defaultErr; // podrazumevani tok za ispis gresaka

    const CommandRegistry* registry;

    ExecContext(
        std::string& p,
        std::string& sp,
        bool& os,
        ILineExecutor& ex,
        History& h,
        InputStream& cin,
        InputStream& din,
        OutputStream& dout,
        OutputStream& derr,
        const CommandRegistry* reg = nullptr
    )
        : promptRef(p)
        , shotPrompt(sp)
        , oneShot(os)
        , executor(ex)
        , history(h)
        , consoleIn(cin)
        , defaultIn(din)
        , defaultOut(dout)
        , defaultErr(derr)
        , registry(reg)
    {}
};

#endif //OOP1PROJEKAT_EXECCONTEXT_H