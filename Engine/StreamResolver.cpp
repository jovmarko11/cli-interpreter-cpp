#include <fstream>
#include "StreamResolver.h"

#include "Exceptions/Exception.h"
#include "Streams/StringInputStream.h"
#include "Streams/FileInputStream.h"
#include "Parser/ParserStructs.h"
#include "Streams/FileOutputStream.h"


StreamResolver::Streams StreamResolver::resolve(const ParsedCommand& spec, bool takesSourceArgument, InputStream& defaultIn, OutputStream& defaultOut) const{
    Streams s;
    s.in = &defaultIn;
    s.out = &defaultOut;

    // Input iz argumenta
    applyArgumentInput(spec, s, takesSourceArgument);

    // Input redirection < file
    applyInputRedirection(spec, s);

    // Output redirection > file ili >> file
    applyOutputRedirection(spec, s);

    return s;
}

void StreamResolver::applyArgumentInput(const ParsedCommand& spec, Streams& s, bool takesSourceArgument) {
    if (spec.args.empty()) return;

    // Ako komanda ne prima source argument, argument ostaje obican argument
    if (!takesSourceArgument)
        return;

    if (!spec.args.empty() && spec.in.present)
        throw Exception(ErrorType::StreamSemantic,
            "Error: cannot use both argument input and < redirection in command: " + spec.name);

    if (spec.args.size() > 1)
        throw Exception(ErrorType::Syntax,
            "Error: too many arguments for command: " + spec.name);

    const Token& arg = spec.args[0];

    // quoted argument -> StringInputStream
    if (arg.quoted) {
        s.ownedIn = new StringInputStream(arg.text);
    }
    // unquoted argument -> FileInputStream
    else {
        try {
            s.ownedIn = new FileInputStream(arg.text);
        } catch (const std::exception& e) {
            throw Exception(ErrorType::System, spec.name + ": " + std::string(e.what()));
        }
    }

    s.in = s.ownedIn;
}

void StreamResolver::applyInputRedirection(const ParsedCommand& spec, Streams& s) {
    if (!spec.in.present) return;

    const std::string& fn = spec.in.filename;

    delete s.ownedIn;
    s.ownedIn = nullptr;

    try {
        s.ownedIn = new FileInputStream(fn);
    }
    catch (const std::exception& e) {
        throw Exception(ErrorType::System, spec.name + ": " + std::string(e.what()));
    }

    s.in = s.ownedIn;
}

void StreamResolver::applyOutputRedirection(const ParsedCommand& spec, Streams& s) {
    if (!spec.out.present) return;

    const std::string& fn = spec.out.filename;

    delete s.ownedOut;
    s.ownedOut = nullptr;

    FileOutputStream::Mode mode =
        (spec.out.mode == OutMode::Append)
            ? FileOutputStream::Mode::Append
            : FileOutputStream::Mode::Truncate;

    try {
        s.ownedOut = new FileOutputStream(fn, mode);
    }
    catch (const std::exception& e) {
        throw Exception(ErrorType::System, spec.name + ": " + std::string(e.what()));
    }
    s.out = s.ownedOut;

}