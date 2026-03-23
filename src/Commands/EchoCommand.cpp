#include "EchoCommand.h"
#include <iostream>
#include <algorithm>
#include <sstream>

EchoCommand::EchoCommand() {    m_name = "echo";    }


void EchoCommand::execute() {

    clearBuffers();
    loadInput();

    // m_outputText = reverseText(m_inputText)
    // std::string prviRed = s_input->nextLine();

    m_outputText = m_inputText;

    sendOutput();
}




/*
std::string reverseText(const std::string& input) {
    std::string result = input;
    std::reverse(result.begin(), result.end());
    return result;
}

std::string reverseWords(const std::string& input) {
    std::stringstream ss(input);
    std::string word;
    std::vector<std::string> words;

    while (ss >> word) {
        words.push_back(word);
    }

    std::reverse(words.begin(), words.end());

    std::string result;
    for (size_t i = 0; i < words.size(); ++i) {
        result += words[i] + (i == words.size() - 1 ? "" : " ");
    }
    return result;
}

std::string toUpper(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c){ return std::toupper(c); });
    return result;
}

std::string toLower(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return result;
}

std::string sendK(const std::string& input, int k) {
    if (k <= 0) return input;

    std::stringstream ss(input);
    std::string word;
    std::string result;
    int count = 0;

    while (ss >> word) {
        count++;
        if (count % k == 0) {
            if (!result.empty()) result += " ";
            result += word;
        }
    }
    return result;

}
*/