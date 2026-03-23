//
// Created by Marko Jovanovic on 20.2.26..
//

#ifndef OOP1PROJEKAT_ILINEEXECUTOR_H
#define OOP1PROJEKAT_ILINEEXECUTOR_H
#include <string>
#include "ExecContext.h"

// ILineExecutor - apstraktni interface za izvrsavanje komandi
// prima liniju teksta i kontekst u kome treba da je izvrsi

struct ExecContext;

class ILineExecutor {
public:
    virtual ~ILineExecutor() = default;

    virtual void executeLine(const std::string& line, ExecContext& ctx) = 0;
};


#endif //OOP1PROJEKAT_ILINEEXECUTOR_H