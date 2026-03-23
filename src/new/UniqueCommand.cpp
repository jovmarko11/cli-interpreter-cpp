//
// Created by Marko Jovanovic on 5.3.26..
//

#include "UniqueCommand.h"

UniqueCommand::UniqueCommand(std::string& opt) {
    m_option = opt;
    m_name = "unique";

    validateOption();
}

void UniqueCommand::execute() {
    requireInput(m_name);
    requireInput(m_name);
    requireError(m_name);

    clearBuffers();
    loadInput();

    std::vector<std::string> lines = loadLines();

    for (int i = 0; i < lines.size(); i++) {
        if (!isInSet(lines[i], m_UniqueLines)) {
            m_UniqueLines.push_back(lines[i]);
        }
    }

    if (m_option == "u") {

    }

}

std::vector<std::string> UniqueCommand::loadLines() {
    m_LineNumber = 0;
    std::vector<std::string> lines;
    std::string line;
    for (auto c : m_inputText) {
        line.clear();
        if (c == '\n') {
            lines.push_back(line);
        }
        line += c;
    }
    return lines;
}

bool UniqueCommand::isInSet(std::string& l, std::vector<std::string>& lines) {
    for (auto line : lines) {
        if (l == line)
            return true;
    }
    return false;
}