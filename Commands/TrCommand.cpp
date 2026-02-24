#include "TrCommand.h"

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
        // sprečava petlju ako replacement sadrži what
    }
}

void TrCommand::execute() {
    requireInput(m_name);
    requireOutput(m_name);

    m_inputText.clear();
    m_outputText.clear();

    loadInput();
    m_outputText = m_inputText;

    if (m_hasWith) {
        replaceText(m_outputText, m_what, m_with);
    } else {
        deleteText(m_outputText, m_what);
    }

    m_output->write(m_outputText);
}
