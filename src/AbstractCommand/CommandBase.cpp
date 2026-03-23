#include "CommandBase.h"
#include <iostream>
#include <ostream>
#include <sstream>

// citanje karaktera sa ulaznog toka sve do kraja fajla ili signala EOF
void CommandBase::loadInput() {
    requireInput(m_name);
    m_inputText.clear();

    std::string buffer;

    while (true) {
        int ch = s_input->get();

        if (ch == EOF) {
            s_input->clear();
            break;
        }
        buffer.push_back(static_cast<char>(ch));
    }

    m_inputText = buffer;
}

void CommandBase::clearBuffers() {
    m_inputText.clear();
    m_outputText.clear();
}

void CommandBase::sendOutput() {
    requireOutput(m_name);

    s_output->write(m_outputText);
}

std::vector<std::string> CommandBase::parseLines() const {
    std::vector<std::string> result;
    std::stringstream ss(m_inputText);
    std::string line;

    while (std::getline(ss, line))
        result.push_back(line);

    return result;
}

std::vector<std::string> CommandBase::parseWords() const {
    std::vector<std::string> words;
    std::string word;

    for (char c : m_inputText) {
        if (std::isspace(static_cast<unsigned char>(c))) {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }

    // dodaj poslednju rec ako postoji
    if (!word.empty())
        words.push_back(word);

    return words;
}

int CommandBase::countLines() const {
    int count = 0;

    for (char c : m_inputText) {
        if (c == '\n')
            count++;
    }
    return count;
}
