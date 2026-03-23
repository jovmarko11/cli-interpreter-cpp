#include "CommandRegistry.h"
#include "../Parser/DerivedParsers.h"
#include "CommandFactories.h"

CommandRegistry::CommandRegistry() {
    registerCommand("time", new SimpleCommandParser(), createTime,
        false,false,false,false,true,false);

    registerCommand("date", new SimpleCommandParser(), createDate,
        false,false,false,false,true,false);

    registerCommand("echo", new SimpleCommandParser(), createEcho,
        false,true,false,true,true,true);

    registerCommand("prompt", new SimpleCommandParser(), createPrompt,
        true,true,false,true,true,false);

    registerCommand("wc", new OptionCommandParser(), createWc,
        false,true,true,true,true,true);

    registerCommand("touch", new SimpleCommandParser(), createTouch,
        true,true,false,true,true,false);

    registerCommand("rm", new SimpleCommandParser(), createRm,
        true,true,false,true,true,false);

    registerCommand("truncate", new SimpleCommandParser(), createTruncate,
        true,true,false,true,true,false);

    registerCommand("tr", new TrCommandParser(), createTr,
        false,true,false,true,true,true);

    registerCommand("batch", new SimpleCommandParser(), createBatch,
        true,true,false,true,true,true);

    registerCommand("head", new OptionCommandParser(), createHead,
        false,true,true,true,true,true);

    registerCommand("last", new SimpleCommandParser(), createLast,
        false,false,false,false,true,false);

    registerCommand("copy", new SimpleCommandParser(), createCopy,
        true,true,false,false,true,false);

    registerCommand("history", new SimpleCommandParser(), createHistory,
        false,false,false,false,true,false);

    registerCommand("dump", new OptionCommandParser(), createDump,
        false,true,true,false,false,false);

    registerCommand("exec", new SimpleCommandParser(), createExec,
        false,true,false,true,true,true);

    registerCommand("tail", new OptionCommandParser(), createTail,
        false,true,true,true,true,true);

    // Registracija help komande
    registerCommand("help", new SimpleCommandParser(), createHelp,
        false,true,false,false,true,false);
}


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

    // automatska provera uslova pre pozivanja factory funkcije
    validateCommand(spec, info);

    // pozivanje factory funkcije
    CommandBase* cmd =  info.factory(spec, ctx);

    if (!cmd)
        throw Exception(ErrorType::Syntax, "Error: invalid format for command: " + spec.name);
    return cmd;
}

void CommandRegistry::validateCommand(const ParsedCommand& spec, const CommandInfo& info) const {
    if (info.requiresArgument && spec.args.empty())
        throw Exception(ErrorType::Syntax, "Error: missing argument for command: " + spec.name);

    if (!info.acceptsArgument && !spec.args.empty())
        throw Exception(ErrorType::Syntax, "Error: command " + spec.name + " does not accept arguments");

    if (info.requiresOption && spec.option.empty())
        throw Exception(ErrorType::Syntax, "Error: missing option for command: " + spec.name);
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

std::vector<std::string> CommandRegistry::getCommandNames() const {
    std::vector<std::string> names;
    for (const auto& pair : m_commands) {
        names.push_back(pair.first);
    }
    return names;
}

CommandBase* CommandRegistry::createCommand(const std::string& name, ExecContext& ctx) const {
    const CommandInfo* info = getInfo(name);
    if (!info) return nullptr;

    ParsedCommand fakeSpec;
    fakeSpec.name = name;
    fakeSpec.option = "n1"; 
    fakeSpec.hasSource = false;
    
    if (name == "copy" || name == "tr") {
        fakeSpec.args.push_back({"f1", false}); 
        fakeSpec.args.push_back({"f2", false});
    } else {
        fakeSpec.args.push_back({"f1", true});
    }
    
    try {
        return info->factory(fakeSpec, ctx);
    } catch (...) {
        return nullptr;
    }
}

void CommandRegistry::registerCommand(const std::string& name, ICommandLineParser* parser, CommandBase* (*factory)(const ParsedCommand&, ExecContext&), bool requiresArgument, bool acceptsArgument, bool requiresOption, bool hasInput, bool hasOutput, bool takesSourceArgument) {
    m_commands[name] = {
        name,
        parser,
        factory,
        requiresArgument,
        acceptsArgument,
        requiresOption,
        hasInput,
        hasOutput,
        takesSourceArgument
    };
}
