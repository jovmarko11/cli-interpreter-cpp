//
// Created by Marko Jovanovic on 6.2.26..
//

#ifndef OOP1PROJEKAT_PROMPTCOMMAND_H
#define OOP1PROJEKAT_PROMPTCOMMAND_H
#include "AbstractCommand/CommandBase.h"
#include "Engine/ExecContext.h"

// Komanda menja izgled znaka za spremnost interpretera da primi novu komandnu liniju (prompt)

class PromptCommand : public CommandBase {
public:
    explicit PromptCommand(const std::string& newVal, ExecContext& ctx);

    void execute() override;

    std::string usage() const override;

    std::string description() const override;

private:
    ExecContext& m_ctx; // kontekst u kojem se menja trenutni prompt

    std::string m_newPrompt; // vrednost na koju prompt treba da se promeni
};


inline std::string PromptCommand::usage() const {
    return "prompt \"text\"";
}

inline std::string PromptCommand::description() const {
    return "Changes the command prompt to the specified text enclosed in quotes.";
}

#endif //OOP1PROJEKAT_PROMPTCOMMAND_H