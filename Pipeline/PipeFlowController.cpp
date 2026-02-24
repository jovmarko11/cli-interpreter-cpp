#include "PipeFlowController.h"

void PipeFlowController::resetPipes(int commandCount) {
    // obrisi stare
    for (auto* pipe : m_pipes)
        delete pipe;
    m_pipes.clear();

    // napravi novih commandCount - 1
    for (int i = 0; i < commandCount - 1; ++i) {
        m_pipes.push_back(new PipeStream());
    }
}

std::vector<PipeFlowController::Link> PipeFlowController::buildLinks(int commandCount){
    std::vector<Link> links(commandCount);
    if (commandCount <= 1) return links;

    resetPipes(commandCount);

    for (int i = 0; i < commandCount; i++) {
        // osim prvog
        if (i > 0) {
            links[i].pipeIn = m_pipes[i - 1];
        }

        // osim poslednjeg
        if (i < commandCount - 1) {
            links[i].pipeOut = m_pipes[i];
        }
    }

    return links;
}

PipeFlowController::~PipeFlowController() {
    for (auto p : m_pipes) {
        delete p;
    }
    m_pipes.clear();
}