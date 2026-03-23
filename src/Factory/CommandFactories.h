//
// Created by Marko Jovanovic on 3.3.26..
//

#ifndef OOP1PROJEKAT_COMMANDFACTORIES_H
#define OOP1PROJEKAT_COMMANDFACTORIES_H
#include "../Engine/ExecContext.h"
#include "AbstractCommand/CommandBase.h"
#include "Parser/ParserStructs.h"

// Deklaracije factory funkcija za instanciranje konkretnih komandi

CommandBase* createTime(const ParsedCommand& spec, ExecContext& ctx);
CommandBase* createDate(const ParsedCommand& spec, ExecContext& ctx);
CommandBase* createEcho(const ParsedCommand& spec, ExecContext& ctx);
CommandBase* createPrompt(const ParsedCommand& spec, ExecContext& ctx);
CommandBase* createWc(const ParsedCommand& spec, ExecContext& ctx);
CommandBase* createTouch(const ParsedCommand& spec, ExecContext& ctx);
CommandBase* createRm(const ParsedCommand& spec, ExecContext& ctx);
CommandBase* createTruncate(const ParsedCommand& spec, ExecContext& ctx);
CommandBase* createTr(const ParsedCommand& spec, ExecContext& ctx);
CommandBase* createBatch(const ParsedCommand& spec, ExecContext& ctx);
CommandBase* createHead(const ParsedCommand& spec, ExecContext& ctx);
CommandBase* createLast(const ParsedCommand& spec, ExecContext& ctx);
CommandBase* createCopy(const ParsedCommand& spec, ExecContext& ctx);
CommandBase* createHistory(const ParsedCommand& spec, ExecContext& ctx);
CommandBase* createDump(const ParsedCommand& spec, ExecContext& ctx);
CommandBase* createExec(const ParsedCommand& spec, ExecContext& ctx);
CommandBase* createTail(const ParsedCommand& spec, ExecContext& ctx);
CommandBase* createHelp(const ParsedCommand& spec, ExecContext& ctx);

#endif //OOP1PROJEKAT_COMMANDFACTORIES_H