//
// Created by Marko Jovanovic on 21.2.26..
//

#include "HeadCommand.h"


HeadCommand::HeadCommand(int lineCount)
    :   m_lineCount(lineCount)
{
    m_name = "head";
}

void HeadCommand::execute() {
    requireInput(m_name);
    requireOutput(m_name);
    requireError(m_name);

    if (m_lineCount < 0)
        throw Exception(ErrorType::Syntax,
            "Error: invalid count for command: " + m_name);

    int linesSeen = 0;

    while (true) {
        int c = m_input->get();
        if (c == EOF || c < 0) break;

        if (linesSeen < m_lineCount) {
            (*m_output) << static_cast<char>(c);
        }

        if (c == '\n') {
            linesSeen++;
            // posle N linija: nastavlja citanje ali ne ispisuje
        }
    }
}