#include "Program.h"

Program::Program()
    : m_prompt("$")
    , m_shotPrompt("$")
    , m_oneShot(false)
    , m_history(100)
    , m_registry()
    , m_parser(m_registry)
    , m_resolver()
    , m_engine(m_parser, m_registry, m_resolver)
    , m_ctx(m_prompt, m_shotPrompt,
        m_oneShot,
        m_engine,
        m_history,
        m_consoleIn,
        m_consoleIn,
        m_consoleOut,
        m_consoleErr,
        &m_registry
    )
    , m_reader(m_consoleIn)
    , m_interpreter(m_engine, m_ctx, m_reader)
{}

void Program::run() {
    m_interpreter.run();
};
