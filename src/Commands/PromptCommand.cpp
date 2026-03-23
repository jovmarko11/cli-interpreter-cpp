#include "PromptCommand.h"

PromptCommand::PromptCommand(const std::string &newVal, ExecContext& ctx)
    :   m_ctx(ctx)
    ,   m_newPrompt(newVal)
{
    m_name = "prompt";
}

 void PromptCommand::execute() {
    m_ctx.promptRef = m_newPrompt;
}

/*

if (m_option == "x"){
    m_ctx.shotPrompt = newPrompt;
    m_ctx.oneShot = true;
}
else{
    m_ctx.promptRef = newPrompt;
}
*/