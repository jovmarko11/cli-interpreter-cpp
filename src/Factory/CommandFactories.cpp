#include "Factory/CommandFactories.h"
#include "Commands/BatchCommand.h"
#include "Commands/EchoCommand.h"
#include "Commands/HeadCommand.h"
#include "Commands/PromptCommand.h"
#include "Commands/RmCommand.h"
#include "Commands/TimeAndDateCommands.h"
#include "Commands/TouchCommand.h"
#include "Commands/TrCommand.h"
#include "Commands/TruncateCommand.h"
#include "Commands/WcCommand.h"
#include "new/CopyCommand.h"
#include "new/DumpCommand.h"
#include "new/ExecCommand.h"
#include "new/HistoryCommand.h"
#include "new/LastCommand.h"
#include "new/TailCommand.h"
#include "new/HelpCommand.h"

// Time
CommandBase* createTime(const ParsedCommand& spec, ExecContext& ctx) { return new TimeCommand(); }

// Date
CommandBase* createDate(const ParsedCommand& spec, ExecContext& ctx) { return new DateCommand(); }

// Echo
CommandBase* createEcho(const ParsedCommand& spec, ExecContext& ctx) { return new EchoCommand(); }

// Prompt
CommandBase* createPrompt(const ParsedCommand& spec, ExecContext& ctx) {
    if (spec.args.size() != 1) return nullptr;
    if (!spec.args[0].quoted) {
        throw Exception(ErrorType::Syntax, "Prompt must be enclosed in quotes");
    }
    return new PromptCommand(spec.args[0].text, ctx);
}

// Wc
CommandBase* createWc(const ParsedCommand& spec, ExecContext& ctx) {
    if (spec.option.empty()) return nullptr;
    return new WcCommand(spec.option);
}

// Touch
CommandBase* createTouch(const ParsedCommand& spec, ExecContext& ctx) {
    if (spec.args.size() != 1) return nullptr;
    return new TouchCommand(spec.args[0].text);
}

// Rm
CommandBase* createRm(const ParsedCommand& spec, ExecContext& ctx) {
    if (spec.args.size() != 1) return nullptr;
    return new RmCommand(spec.args[0].text);
}

// Truncate
CommandBase* createTruncate(const ParsedCommand& spec, ExecContext& ctx) {
    if (spec.args.size() != 1) return nullptr;
    return new TruncateCommand(spec.args[0].text);
}

// Tr
CommandBase* createTr(const ParsedCommand& spec, ExecContext& ctx) {
    CommandBase* cmd = nullptr;

    auto& mutableSpec = const_cast<ParsedCommand&>(spec);

    if (!spec.hasSource) {
        // args[0] = what i args[1] = with (optional)
        std::string what = spec.args[0].text;
        std::string with = (spec.args.size() == 2) ? spec.args[1].text : "";

        cmd = new TrCommand(what, with);

        mutableSpec.args.clear();

    }
    else {
        // args : [0] = source [1] = what 2] = with (optional)
        std::string source = spec.args[0].text;
        std::string what = spec.args[1].text;
        std::string with = (spec.args.size() == 3) ? spec.args[2].text : "";

        cmd = new TrCommand(what, with);

        Token sourceToken = spec.args[0];
        mutableSpec.args.clear();
        mutableSpec.args.push_back(sourceToken);
    }

    return cmd;
}

// Batch
CommandBase* createBatch(const ParsedCommand& spec, ExecContext& ctx) {
    return new BatchCommand(ctx);
}

// Head
CommandBase* createHead(const ParsedCommand& spec, ExecContext& ctx) {
    const std::string& opt = spec.option;

    // mora da pocne sa 'n' i da ima bar jednu cifru posle
    if (opt.size() < 2) return nullptr;
    if (opt[0] != 'n') return nullptr;

    const std::string digits = opt.substr(1);
    if (digits.empty() || digits.size() > 5) return nullptr;

    int count = 0;
    for (char c : digits) {
        if (c < '0' || c > '9') return nullptr;
        count = count * 10 + (c - '0');
    }

    return new HeadCommand(count);
}
////////////
// Last
CommandBase* createLast(const ParsedCommand& spec, ExecContext& ctx) {
    return new LastCommand(ctx);
}
// Copy
CommandBase* createCopy(const ParsedCommand& spec, ExecContext& ctx) {
    if (spec.args.size() != 2) return nullptr;

    std::string fileFrom = spec.args[0].text;
    std::string fileTo = spec.args[1].text;

    auto& mutableSpec = const_cast<ParsedCommand&>(spec);
    mutableSpec.args.clear();

    return new CopyCommand(fileFrom, fileTo);
}
CommandBase* createHistory(const ParsedCommand& spec, ExecContext& ctx) {
    return new HistoryCommand(ctx);
}
// Dump
CommandBase* createDump(const ParsedCommand& spec, ExecContext& ctx) {
    // 1. Validacija opcije (mora postojati -k, npr -3)
    if (spec.option.empty()) {
        throw Exception(ErrorType::Syntax, "dump: missing index option (e.g., -3)");
    }

    // 2. Validacija argumenata (mora postojati fajl)
    if (spec.args.empty())
        throw Exception(ErrorType::Syntax, "dump: missing output file argument");

    if (spec.args.size() != 1)
        throw Exception(ErrorType::Syntax, "dump: invalid number of arguments");

    return new DumpCommand(ctx, spec.option, spec.args[0].text);
}

// Exec
CommandBase* createExec(const ParsedCommand& spec, ExecContext& ctx) {
    return new ExecCommand();
}

// Tail
CommandBase* createTail(const ParsedCommand& spec, ExecContext& ctx) {

    const std::string& opt = spec.option;

    // mora da pocne sa 'n' i da ima bar jednu cifru posle
    if (opt.size() < 2) return nullptr;
    if (opt[0] != 'n') return nullptr;

    const std::string digits = opt.substr(1);
    if (digits.empty() || digits.size() > 5) return nullptr;

    int count = 0;
    for (char c : digits) {
        if (c < '0' || c > '9') return nullptr;
        count = count * 10 + (c - '0');
    }

    return new TailCommand(count);
}

CommandBase* createHelp(const ParsedCommand& spec, ExecContext& ctx) {
    std::string target = spec.args.empty() ? "" : spec.args[0].text;
    return new HelpCommand(ctx, target);
}