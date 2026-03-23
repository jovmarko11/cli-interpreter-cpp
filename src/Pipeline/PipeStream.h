//
// Created by Marko Jovanovic on 12.2.26..
//

#ifndef OOP1PROJEKAT_PIPESTREAM_H
#define OOP1PROJEKAT_PIPESTREAM_H
#include "../Streams/InputAndOutputStream.h"

/// PipeStream - veza izmedju I/O toka dve komande
/// Predstavlja cev izmedju dve komande

class PipeStream : public InputStream, public OutputStream {
public:
    /// OutputStream deo
    void write(const std::string& str) override     {   m_buffer += str;    }
    void write(char c) override     {   m_buffer.push_back(c);  }
    void writeLine(const std::string& str) override      {   m_buffer += str; m_buffer.push_back('\n');     }

    /// InputStream deo
    int get() override;

    bool eof() const override   {   return m_pos >= m_buffer.size();    }

    bool hasNext() const override {   return m_pos < m_buffer.size();   }

    void clear() override {   m_buffer.clear();   }

    bool isConsole() override { return false; }

    std::string nextLine() override;

    std::string nextToken() override;

private:
    // bafer za razmenu podataka izmedju komandi
    std::string m_buffer;
    // trenutna pozicija citanja u baferu
    size_t m_pos = 0;
};


#endif //OOP1PROJEKAT_PIPESTREAM_H