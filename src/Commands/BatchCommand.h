#ifndef OOP1PROJEKAT_BATCHCOMMAND_H
#define OOP1PROJEKAT_BATCHCOMMAND_H
#include "AbstractCommand/CommandBase.h"
#include "Engine/Interpreter.h"

// Komanda koja cita linije sa zadatog ulaznog toka i izvrsava ih jednu po jednu

class BatchCommand : public CommandBase {
public:
    explicit BatchCommand(ExecContext& ctx);

    void execute() override;

    std::string usage() const override;

    std::string description() const override;

private:
    ExecContext& m_globalCtx; // referenca na globalni kontekst izvrsavanja

    ExecContext createBatchCtx(); // kreira lokalni kontekst izvrsavanja unutar batch fajla
};

inline std::string BatchCommand::usage() const {
    return "batch filename";
}

inline std::string BatchCommand::description() const {
    return "Reads commands from the specified file and executes them sequentially as if they were entered in the console.";
}



#endif //OOP1PROJEKAT_BATCHCOMMAND_H