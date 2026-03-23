#ifndef OOP1PROJEKAT_COMMANDREGISTRY_H
#define OOP1PROJEKAT_COMMANDREGISTRY_H
#include "AbstractCommand/CommandBase.h"
#include <map>
#include <string>

#include "../Engine/ILineExecutor.h"
#include "Parser/ParserStructs.h"

// Centralni registar sistema
// Povezuje ime komande sa njegovim parserom, factory funkcijom i definicijom njenih argumenata

class ICommandLineParser;

class CommandRegistry {
public:
    // Struktura koja cuva sve informacije za jednu komandu
    struct CommandInfo {
        std::string name;

        ICommandLineParser* parser;

        CommandBase* (*factory)(const ParsedCommand&, ExecContext&);

        bool requiresArgument;
        bool acceptsArgument;

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

    // Specijalna helper funkcija za instanciranje (npr za help komandu) bez argumenata 
    CommandBase* createCommand(const std::string& name, ExecContext& ctx) const;

    // Vraca parser koji radi parsiranje odredjene komande
    ICommandLineParser* getParser(const std::string& name) const;

    // Vraca pokazivac na kompletne informacije o komandi
    const CommandInfo *getInfo(const std::string &name) const;

    // Vraca vektor imena svih registrovanih komandi
    std::vector<std::string> getCommandNames() const;

private:
    // Mapa svih registrovanih komandi name -> CommandInfo
    std::map<std::string, CommandInfo> m_commands;

    // semanticka validacija komandne linije
    void validateCommand(const ParsedCommand& spec, const CommandInfo& info) const;

    // registracija komande
    void registerCommand(
        const std::string& name,
        ICommandLineParser* parser,
        CommandBase* (*factory)(const ParsedCommand&, ExecContext&),
        bool requiresArgument,
        bool acceptsArgument,
        bool requiresOption,
        bool hasInput,
        bool hasOutput,
        bool takesSourceArgument
    );

};

#endif //OOP1PROJEKAT_COMMANDREGISTRY_H