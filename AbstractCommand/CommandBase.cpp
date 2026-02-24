#include "CommandBase.h"

void CommandBase::loadInput() {
    requireInput(m_name);

    m_inputText.clear();

    while (m_input->hasNext()) {
        int ch = m_input->get();
        if (ch == EOF || ch < 0) break;
        m_inputText.push_back(static_cast<char>(ch));
    }

}

void CommandBase::clearBuffers() {
    m_inputText.clear();
    m_outputText.clear();
}

void CommandBase::sendOutput() {
    requireOutput(m_name);

    m_output->write(m_outputText);
}