#include <stdexcept>
#include <cctype>
#include "WcCommand.h"
#include <cstdio>
#include <sstream>

WcCommand::WcCommand(const std::string& opt) {
    m_option = opt;
    m_name = "wc";

    validateOption();
}

void WcCommand::execute() {
    clearBuffers();
    loadInput();

    int count = 0;

    if (m_option == "c")
        count = static_cast<int> (m_inputText.size());
    else if (m_option == "w")
        count = static_cast<int> (parseWords().size());

    m_outputText = std::to_string(count);
    m_outputText.push_back('\n');

    sendOutput();
}


///
int WcCommand::countChars(const std::string& s) {
    return static_cast<int>(s.size());
}

int WcCommand::countWords(const std::string& s) {
    int count = 0;
    bool inWord = false;

    for (unsigned char ch : s) {
        if (std::isspace(ch))
            inWord = false;
        else if (!inWord) {
            count++;
            inWord = true;
        }
    }
    return count;
}

// count sentences
int countSentences(const std::string& s) {
    int count = 0;
    bool inSentence = false;

    for (unsigned char ch : s) {
        if (ch == '.' || ch == '!' || ch == '?') {
            if (inSentence) {
                count++;
                inSentence = false;
            }
        }
        else if (!std::isspace(ch)) {
            inSentence = true;
        }
    }
    return count;
}

int longestWord(const std::string& s) {
    std::stringstream ss(s);
    std::string word;
    int maxLen = 0;

    while (ss >> word) {
        if (static_cast<int>(word.size()) > maxLen) {
            maxLen = static_cast<int>(word.size());
        }
    }
    return maxLen;
}

float averageWordLength(const std::string& s) {
    std::stringstream ss(s);
    std::string word;
    int totalCharsInWords = 0;
    int wordCount = 0;

    while (ss >> word) {
        totalCharsInWords += static_cast<int>(word.size());
        wordCount++;
    }

    if (wordCount == 0) return 0.0f;

    return static_cast<float>(totalCharsInWords) / static_cast<float>(wordCount);
}

/*
else if (m_option == "a") { // Prosek (formatiran na 2 decimale)
        char buf[32];
        std::sprintf(buf, "%.2f", averageWordLength(m_inputText));
        m_outputText = std::string(buf);
    }
*/
