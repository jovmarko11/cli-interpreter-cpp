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
        if (ci == EOF) {
            if (result.line.empty()) result.eof = true;
            break;
        }
        char ch = static_cast<char>(ci);
        if (ch == '\r') continue;
        if (ch == '\n') break;

        if (count < m_maxLen) {
            result.line.push_back(ch);
        }
        else {
            result.truncated = true;

            // natavlja se ciitanje iz inputa ali se ne pamti -
            while (true) {
                int ci2 = m_inputstream.get();
                if (ci2 == EOF) { result.eof = true; break; }
                if (static_cast<char>(ci2) == '\n') break;
            }
            break;
        }
        count++;
    }

    return result;
}