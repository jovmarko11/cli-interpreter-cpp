#include <stdexcept>
#include <cctype>
#include "WcCommand.h"
#include <cstdio>

WcCommand::WcCommand(const std::string& opt) {
    m_option = opt;
    m_name = "wc";

    validateOption();
}

int WcCommand::countChars(const std::string& s) {
    return static_cast<int>(s.size());
}

int WcCommand::countWords(const std::string& s) {
    int count = 0;
    bool inWord = false;

    for (unsigned char ch : s) {
        if (std::isspace(ch)) inWord = false;
        else if (!inWord) {
            count++;
            inWord = true;
        }
    }
    return count;
}


void WcCommand::execute() {
    requireInput(m_name);
    requireOutput(m_name);

    // validiraj opciju w ili c
    validateOption();

    clearBuffers();
    loadInput();

    int count = 0;

    if (m_option == "c")
        count = countChars(m_inputText);
    else if (m_option == "w")
        count = countWords(m_inputText);

    m_outputText = std::to_string(count);
    m_outputText.push_back('\n');

    sendOutput();
}
