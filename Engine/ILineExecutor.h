//
// Created by Marko Jovanovic on 20.2.26..
//

#ifndef OOP1PROJEKAT_ILINEEXECUTOR_H
#define OOP1PROJEKAT_ILINEEXECUTOR_H
#include <string>

#include "History.h"

class InputStream;
class OutputStream;

// ubaciti executeLine(std::string& line, ExecContext& ctx)
// sve spakovati u ExecContext& ctx potrebno za izvrsavanje komande
class ILineExecutor {
public:
    virtual ~ILineExecutor() = default;

    virtual void executeLine(
        const std::string& line,
        InputStream& defaultIn,
        OutputStream& defaultOut,
        OutputStream& defaultErr
    ) = 0;
};

struct ExecContext {
    std::string& promptRef;
    ILineExecutor& executor;
    InputStream& consoleIn;
    OutputStream& defaultErr;
    History& history;

    ExecContext(std::string& p, ILineExecutor& e, InputStream& in, OutputStream& err, History& h)
        : promptRef(p), executor(e), consoleIn(in), defaultErr(err), history(h) {}
};


#endif //OOP1PROJEKAT_ILINEEXECUTOR_H