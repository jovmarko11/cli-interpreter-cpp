#ifndef OOP1PROJEKAT_ISTREAMAWARE_H
#define OOP1PROJEKAT_ISTREAMAWARE_H
#include "Exceptions/Exception.h"
#include "Streams/InputAndOutputStream.h"

/// MIXIN - omogucava svest komande o sopstvenim streamovima
/// Dodaje komandama I/O pokazivace

class StreamAware {
public:
    virtual ~StreamAware() = default;

    void setStreams(InputStream* in, OutputStream* out, OutputStream* err) {
        m_input = in; m_output = out; m_error = err;
    }

    void setInputStream(InputStream* in)     { m_input = in; }
    void setOutputStream(OutputStream* out)  { m_output = out; }
    void setErrorStream(OutputStream* err)   { m_error = err; }

    InputStream*  getInput()  const { return m_input; }
    OutputStream* getOutput() const { return m_output; }
    OutputStream* getError()  const { return m_error; }

protected:
    InputStream*  m_input  {nullptr};
    OutputStream* m_output {nullptr};
    OutputStream* m_error  {nullptr};

    void requireInput(const std::string& name) const {
        if (!m_input) throw Exception(ErrorType::StreamSemantic,name + ": InputStream not set");
    }
    void requireOutput(const std::string& name) const {
        if (!m_output) throw Exception(ErrorType::StreamSemantic,name + ": OutputStream not set");
    }
    void requireError(const std::string& name) const {
        if (!m_error) throw Exception(ErrorType::StreamSemantic,name + ": ErrorStream not set");
    }
};
#endif //OOP1PROJEKAT_ISTREAMAWARE_H