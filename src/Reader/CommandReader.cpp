#include "CommandReader.h"
#include "../Streams/InputAndOutputStream.h"

CommandReader::CommandReader(InputStream& inputstream) : m_inputstream(inputstream) {}

ReadResult CommandReader::readLine() {
    ReadResult result;

    result.line.clear();
    result.line.reserve(m_maxLen);
    result.truncated = false;
    result.eof = false;

    std::size_t count = 0;

    while (true) {
        int ci = m_inputstream.get();

        if (m_inputstream.eof()) {
            if (m_inputstream.isConsole()) {
                m_inputstream.clear();
            }
            if (result.line.empty()) {
                result.eof = true;
            }
            break;
        }

        char ch = static_cast<char>(ci);
        if (ch == '\r') continue;
        if (ch == '\n') break;

        if (count < m_maxLen) {
            result.line.push_back(ch);
            count++;
        } else {
            result.truncated = true;
            // Preskačemo ostatak preduge linije
            while (true) {
                int next = m_inputstream.get();
                if (next == EOF || static_cast<char>(next) == '\n') break;
            }
            break;
        }
    }

    return result;
}