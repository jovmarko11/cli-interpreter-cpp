#include "TailCommand.h"

#include <iostream>

TailCommand::TailCommand(int Count) {
    lineCount = Count;
    m_name = "tail";
}

void TailCommand::execute() {
    requireInput(m_name);
    requireOutput(m_name);
    requireError(m_name);

    clearBuffers();
    loadInput();

    std::vector<std::string> lines = parseLines();

    size_t size = lines.size();


    for (int i = 0; i < lineCount; i++) {
        m_outputText += lines[size - i - 1];
        m_outputText += "\n";
    }

    sendOutput();
}
