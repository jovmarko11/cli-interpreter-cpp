//
// Created by Marko Jovanovic on 6.2.26..
//

#ifndef OOP1PROJEKAT_PROMPTCOMMAND_H
#define OOP1PROJEKAT_PROMPTCOMMAND_H
#include "AbstractCommand/CommandBase.h"


class PromptCommand : public CommandBase {
private:
    std::string& promptReference;
    std::string newPrompt;


public:
    PromptCommand(const std::string& newVal, std::string& promptRef);

    void execute() override;

    std::string getPrompt() const;
};

inline PromptCommand::PromptCommand(const std::string &newVal, std::string &promptRef)
    :   promptReference(promptRef)
    ,   newPrompt(newVal)   { m_name = "prompt"; }

inline void PromptCommand::execute() {
    promptReference = newPrompt;
}

inline std::string PromptCommand::getPrompt() const {
    return promptReference;
}


#endif //OOP1PROJEKAT_PROMPTCOMMAND_H