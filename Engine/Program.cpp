#include "Program.h"

Program::Program()
    : m_prompt("$")
    , m_parser(m_registry)
    , m_reader(m_in)
    , m_history(100)
    , m_executor(m_registry, m_parser, m_resolver, m_prompt, m_history)
    , m_interpreter(m_in, m_out, m_err, m_reader, m_executor, m_prompt, m_history)
{}

void Program::run() {
    m_interpreter.run();
}
