//
// Created by Marko Jovanovic on 6.2.26..
//

#include "EchoCommand.h"

EchoCommand::EchoCommand() { m_name = "echo"; }

void EchoCommand::execute() {
    requireInput(m_name);
    requireOutput(m_name);

    clearBuffers();

    loadInput();

    m_outputText = m_inputText;

    sendOutput();
}

