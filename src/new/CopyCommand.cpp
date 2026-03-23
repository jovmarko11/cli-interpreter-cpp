#include "CopyCommand.h"

#include <fstream>

// std::ifstream = input file stream, opcije std::ios in, out, app (append), binary (oba)
void CopyCommand::execute() {
    requireError(m_name);

    std::ifstream in(m_from, std::ios::binary);
    if (!in.is_open())
        throw Exception(ErrorType::CommandSemantic,
            m_name + ": source file does not exist");

    std::ofstream out(m_to, std::ios::binary);
    if (!out.is_open())
        throw Exception(ErrorType::CommandSemantic,
            m_name + ": cannot create file: " + m_to);

    char c;
    while (in.get(c)) {
        out.put(c);
    }
}