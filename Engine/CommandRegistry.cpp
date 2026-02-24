#include "CommandRegistry.h"
#include "Commands/EchoCommand.h"
#include "Commands/PromptCommand.h"
#include "Commands/RmCommand.h"
#include "Commands/TimeAndDateCommands.h"
#include "Commands/TouchCommand.h"
#include "Commands/TrCommand.h"
#include "Commands/TruncateCommand.h"
#include "Commands/WcCommand.h"
#include "../Parser/DerivedParsers.h"
#include "Commands/BatchCommand.h"
#include "Commands/HeadCommand.h"
#include "Exceptions/Exception.h"
#include "new/LastCommand.h"

/// KOMANDE

// TIME
CommandBase* createTime(const ParsedCommand& spec, ExecContext& ctx) {
    return new TimeCommand();
}

// DATE
CommandBase* createDate(const ParsedCommand& spec, ExecContext& ctx) {
    return new DateCommand();
}

// ECHO
CommandBase* createEcho(const ParsedCommand& spec, ExecContext& ctx) {
    return new EchoCommand();
}

// PROMPT
CommandBase* createPrompt(const ParsedCommand& spec, ExecContext& ctx) {
    if (spec.args.size() != 1) return nullptr;
    return new PromptCommand(spec.args[0].text, ctx.promptRef);
}

// WC
CommandBase* createWc(const ParsedCommand& spec, ExecContext& ctx) {
    if (spec.option.empty()) return nullptr;
    return new WcCommand(spec.option);
}

// TOUCH
CommandBase* createTouch(const ParsedCommand& spec, ExecContext& ctx) {
    if (spec.args.size() != 1) return nullptr;
    return new TouchCommand(spec.args[0].text);
}

// RM
CommandBase* createRm(const ParsedCommand& spec, ExecContext& ctx) {
    if (spec.args.size() != 1) return nullptr;
    return new RmCommand(spec.args[0].text);
}

// TRUNCATE
CommandBase* createTruncate(const ParsedCommand& spec, ExecContext& ctx) {
    if (spec.args.size() != 1) return nullptr;
    return new TruncateCommand(spec.args[0].text);
}

// TR
CommandBase* createTr(const ParsedCommand& spec, ExecContext& ctx) {
    if (spec.args.size() == 1)
        return new TrCommand(spec.args[0].text);
    if (spec.args.size() == 2)
        return new TrCommand(spec.args[0].text, spec.args[1].text);
    return nullptr;
}

// BATCH
CommandBase* createBatch(const ParsedCommand& spec, ExecContext& ctx) {
    return new BatchCommand(ctx.executor, ctx.consoleIn);
}

// HEAD
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

// LAST
CommandBase* createLast(const ParsedCommand& spec, ExecContext& ctx) {
    return new LastCommand(ctx.history, ctx.executor);
}



/// KONSTRUKTOR

CommandRegistry::CommandRegistry() {
    m_commands["time"] = {
        "time",
        new SimpleCommandParser(),
        createTime,
        false,
        false,
        false,
        true,
        false
    };

    m_commands["date"] = {
        "date",
        new SimpleCommandParser(),
        createDate,
        false,
        false,
        false,
        true,
        false
    };

    m_commands["echo"] = {
        "echo",
        new SimpleCommandParser(),
        createEcho,
        false,
        false,
        true,
        true,
        true
    };

    m_commands["prompt"] = {
        "prompt",
        new SimpleCommandParser(),
        createPrompt,
        true,
        false,
        true,
        true,
        false
    };

    m_commands["wc"] = {
        "wc",
        new OptionCommandParser(),
        createWc,
        false,
        true,
        true,
        true,
        true
    };

    m_commands["touch"] = {
        "touch",
        new SimpleCommandParser(),
        createTouch,
        true,
        false,
        true,
        true,
        false
    };

    m_commands["rm"] = {
        "rm",
        new SimpleCommandParser(),
        createRm,
        true,
        false,
        true,
        true,
        false
    };

    m_commands["truncate"] = {
        "truncate",
        new SimpleCommandParser(),
        createTruncate,
        true,
        false,
        true,
        true,
        false
    };

    m_commands["tr"] = {
        "tr",
        new TrCommandParser(),
        createTr,
        true,
        false,
        true,
        true,
        false
    };

    m_commands["batch"] = {
        "batch",
        new SimpleCommandParser(),
        createBatch,
        true,
        false,
        true,
        true,
        true
    };

    m_commands["head"] = {
        "head",
        new OptionCommandParser(),
        createHead,
        false,
        true,
        true,
        true,
        true
    };

    m_commands["last"] ={
        "last",
        new SimpleCommandParser(),
        createLast,
        false,
        false,
        false,
        true,
        false
    };
}

/// Definicija
CommandRegistry::~CommandRegistry() {
    for (auto& info : m_commands) {
        delete info.second.parser;
    }
}

CommandBase* CommandRegistry::create(const ParsedCommand& spec,ExecContext& ctx) const {
    auto it = m_commands.find(spec.name);
    if (it == m_commands.end())
        throw Exception(ErrorType::UnknownCommand, "Unknown command: " + spec.name);

    const CommandInfo& info = it->second;

    if (info.requiresArgument && spec.args.empty())
        throw Exception(ErrorType::Syntax, "Error: missing argument for command: " + spec.name);

    if (info.requiresOption && spec.option.empty())
        throw Exception(ErrorType::Syntax, "Error: missing option for command: " + spec.name);

    CommandBase* cmd =  info.factory(spec, ctx);
    if (!cmd)
        throw Exception(ErrorType::Syntax, "Error: invalid format for command: " + spec.name);
    return cmd;
}

ICommandLineParser* CommandRegistry::getParser(const std::string& name) const {
    auto it = m_commands.find(name);

    if (it == m_commands.end()) return nullptr;

    return it->second.parser;
}

const CommandRegistry::CommandInfo* CommandRegistry::getInfo(const std::string& name) const {
    auto it = m_commands.find(name);
    if (it == m_commands.end()) return nullptr;
    return &it->second;
}
