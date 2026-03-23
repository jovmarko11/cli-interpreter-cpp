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
        s_input = in; s_output = out; s_error = err;
    }

    void setInputStream(InputStream* in)     { s_input = in; }
    void setOutputStream(OutputStream* out)  { s_output = out; }
    void setErrorStream(OutputStream* err)   { s_error = err; }

    InputStream*  getInput()  const { return s_input; }
    OutputStream* getOutput() const { return s_output; }
    OutputStream* getError()  const { return s_error; }

protected:
    InputStream*  s_input  {nullptr};
    OutputStream* s_output {nullptr};
    OutputStream* s_error  {nullptr};

    void requireInput(const std::string& name) const {
        if (!s_input) throw Exception(ErrorType::StreamSemantic,name + ": InputStream not set");
    }
    void requireOutput(const std::string& name) const {
        if (!s_output) throw Exception(ErrorType::StreamSemantic,name + ": OutputStream not set");
    }
    void requireError(const std::string& name) const {
        if (!s_error) throw Exception(ErrorType::StreamSemantic,name + ": ErrorStream not set");
    }
};
#endif //OOP1PROJEKAT_ISTREAMAWARE_H