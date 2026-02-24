#include "History.h"

#include "Exceptions/Exception.h"

void History::addExecuted(const std::string& line) {
    if (line.empty()) return;
    if (m_capacity == 0) return;

    if (m_lines.size() == m_capacity) {
        m_lines.erase(m_lines.begin());
    }
    m_lines.push_back(line);
}

std::string History::last() const {
    if (m_lines.empty())
        throw Exception(ErrorType::System,
            "History: empty");

    return m_lines.back();
}

std::string History::getLast(size_t index) const {
    if (index == 0 || index > m_lines.size())
        throw Exception(ErrorType::CommandSemantic,
            "History: invalid index");

    return m_lines[index - 1];
}