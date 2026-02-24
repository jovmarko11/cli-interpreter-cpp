#ifndef OOP1PROJEKAT_COMMANDREGISTRY_H
#define OOP1PROJEKAT_COMMANDREGISTRY_H
#include "AbstractCommand/CommandBase.h"
#include <map>
#include <string>

#include "ILineExecutor.h"
#include "Parser/ParserStructs.h"
/// CommandRegistry - klasa za registraciju svih parsera i factory funkcija

class ICommandLineParser;

class CommandRegistry {
public:
    // Struktura koja cuva sve informacije za jednu komandu
    struct CommandInfo {
        std::string name;

        ICommandLineParser* parser;

        CommandBase* (*factory)(const ParsedCommand&, ExecContext&);

        bool requiresArgument;
        bool requiresOption;

        bool hasInput;
        bool hasOutput;

        bool takesSourceArgument;
    };
    // Konstruktor registruje sve komande
    CommandRegistry();

    // Oslobadja dinamicki alocirane parser objekte
    ~CommandRegistry();

    // Kreira konkretnu komandu na osnovu ParsedCommand
    CommandBase* create(const ParsedCommand& spec, ExecContext& ctx) const;

    // Vraca parser koji radi parsiranje odredjene komande
    ICommandLineParser* getParser(const std::string& name) const;

    const CommandRegistry::CommandInfo *getInfo(const std::string &name) const;

private:
    // Mapa svih registrovanih komandi name -> CommandInfo
    std::map<std::string, CommandInfo> m_commands;

};

#endif //OOP1PROJEKAT_COMMANDREGISTRY_H