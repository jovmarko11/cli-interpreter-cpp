#ifndef OOP1PROJEKAT_PARSERSTRUCTS_H
#define OOP1PROJEKAT_PARSERSTRUCTS_H
#include <string>
#include <vector>

struct Token {
    std::string text;
    bool quoted = false;
};

enum class OutMode {    Truncate, Append    };

struct RedirSpec {
    bool present = false;
    std::string filename;
    OutMode mode = OutMode::Truncate; // koristi se samo za out
};

struct ParsedCommand {
    std::string name;
    std::string option;
    std::vector<Token> args; // Token{ text, quoted }

    // redirekcije
    RedirSpec in;
    RedirSpec out;

    bool hasSource = false;

};

struct TokenizeResult {
    std::vector<Token> tokens;
};

struct ParsedPipeline {
    std::vector<ParsedCommand> commands;

};
#endif //OOP1PROJEKAT_PARSERSTRUCTS_H