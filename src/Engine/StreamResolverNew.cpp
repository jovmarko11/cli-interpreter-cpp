#include "StreamResolverNew.h"

#include "Exceptions/Exception.h"
#include "Parser/ParserStructs.h"
#include "Streams/ConsoleInputStream.h"
#include "Streams/FileInputStream.h"
#include "Streams/FileOutputStream.h"
#include "Streams/StringInputStream.h"

void StreamResolverNew::validateInput(const ParsedCommand& spec, bool hasInput, bool takesSourceArgument, bool inputFromPipe) {
    if (!hasInput && spec.in.present)
        throw Exception(ErrorType::StreamSemantic,"Command does not accept input redirection: " + spec.name);

    bool hasSourceArg = takesSourceArgument && !spec.args.empty();

    if (inputFromPipe) {
        if (spec.in.present || hasSourceArg)
            throw Exception(ErrorType::StreamSemantic, "Command cannot redefine input in pipeline: " + spec.name);
    }

    if (spec.in.present && takesSourceArgument && !spec.args.empty())
        throw Exception(ErrorType::StreamSemantic, "Cannot use both argument input and < redirection: " + spec.name);
}

void StreamResolverNew::validateOutput(const ParsedCommand& spec, bool hasOutput) {
    if (!hasOutput && spec.out.present)
        throw Exception(ErrorType::StreamSemantic, "Command does not produce output: " + spec.name);
}

void StreamResolverNew::resolveInput(const ParsedCommand& spec, Streams& s, bool hasInput, bool takesSourceArgument, bool inputFromPipe, InputStream& defaultIn) {
    if (!hasInput) {
        s.in = nullptr;
        return;
    }

    if (inputFromPipe) {
        s.in = &defaultIn;
        return;
    }

    if (spec.in.present) {
        try {
            s.ownedIn = new FileInputStream(spec.in.filename);
        }
        catch (const std::exception &e) {
            throw Exception(ErrorType::System, spec.name + ": " + std::string(e.what()));
        }
        s.in = s.ownedIn;
        return;
    }

    if (takesSourceArgument && !spec.args.empty()) {
        if (spec.args.size() > 1) {
            throw Exception(ErrorType::Syntax, "Too many arguments for command: " + spec.name);
        }
        const Token& arg = spec.args[0];

        try {
            if (arg.quoted)
                s.ownedIn = new StringInputStream(arg.text);
            else
                s.ownedIn = new FileInputStream(arg.text);
        }
        catch (const std::exception &e) {
            throw Exception(ErrorType::System, spec.name + ": " + std::string(e.what()));
        }
        s.in = s.ownedIn;
        return;
    }
    s.in = &defaultIn;
}

void StreamResolverNew::resolveOutput(const ParsedCommand& spec, Streams& s, bool hasOutput, OutputStream& defaultOut) {
    if (!hasOutput) {
        s.out = nullptr;
        return;
    }

    // 1. Ako nema redirekcije (> ili >>) koristi se podrazumevani izlaz
    if (!spec.out.present) {
        s.out = &defaultOut;
        return;
    }

    // 2. Fajl za izlaznu redirekciju
    FileOutputStream::Mode mode = (spec.out.mode == OutMode::Append) ? FileOutputStream::Mode::Append : FileOutputStream::Mode::Truncate;
    try {
        s.ownedOut = new FileOutputStream(spec.out.filename, mode);
    }
    catch (const std::exception& e) {
        throw Exception(ErrorType::System, spec.name + ": " + std::string(e.what()));
    }
    s.out = s.ownedOut;
}

StreamResolverNew::Streams StreamResolverNew::resolve(const ParsedCommand& spec, bool hasInput, bool hasOutput, bool takesSourceArgument, bool inputFromPipe, InputStream& defaultIn, OutputStream& defaultOut) {
    Streams s;

    validateInput(spec, hasInput, takesSourceArgument, inputFromPipe);
    validateOutput(spec, hasOutput);

    resolveInput(spec,s, hasInput, takesSourceArgument, inputFromPipe, defaultIn);
    resolveOutput(spec, s, hasOutput, defaultOut);

    return s;
}

