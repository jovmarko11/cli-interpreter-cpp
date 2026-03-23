#include "HeadCommand.h"


HeadCommand::HeadCommand(int lineCount)
    :   m_lineCount(lineCount)
{
    m_name = "head";

    if (m_lineCount < 0)
        throw Exception(ErrorType::Syntax, "Error: invalid count for command: " + m_name);
}

void HeadCommand::execute() {

    clearBuffers();
    loadInput();

    size_t pos = m_inputText.size();

    int linesFound = 0;
    std::string result;

    // iteriranje kroz ucitani tekst i brojanje prelazaka u novi red
    for (char c : m_inputText) {
        if (linesFound >= m_lineCount) break;

        result.push_back(c);

        if (c == '\n')
            linesFound++;
    }
    m_outputText = result;
    sendOutput();
}