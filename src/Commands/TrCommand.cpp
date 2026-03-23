#include "TrCommand.h"

TrCommand::TrCommand(const std::string& what, const std::string& with)
    :   m_what (what)
    ,   m_with (with)
{
    m_name = "tr";
    if (m_what.empty())
        throw Exception(ErrorType::Syntax, m_name + ": what cannot be empty");
    m_hasWith = !m_with.empty();
}

void TrCommand::deleteText(std::string &text, const std::string& what) {
    if (what.empty()) return;

    size_t pos = 0;

    while ((pos = text.find(what, pos)) != std::string::npos) {
        text.erase(pos, what.length());
        // pos ostaje isti jer se string skratio
    }
}

void TrCommand::replaceText(std::string& text, const std::string& what, const std::string& replacement){
    if (what.empty()) return;

    size_t pos = 0;

    while ((pos = text.find(what, pos)) != std::string::npos) {
        text.replace(pos, what.length(), replacement);
        pos += replacement.length();
        // sprečava beskonacnu petlju ako replacement sadrži what
    }
}

void TrCommand::execute() {
    clearBuffers();
    loadInput();

    m_outputText = m_inputText;

    if (m_hasWith) {
        replaceText(m_outputText, m_what, m_with);
    }
    else {
        deleteText(m_outputText, m_what);
    }

    sendOutput();
}
