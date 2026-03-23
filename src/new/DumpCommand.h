//
// Created by Marko Jovanovic on 3.3.26..
//

#ifndef OOP1PROJEKAT_DUMPCOMMAND_H
#define OOP1PROJEKAT_DUMPCOMMAND_H
#include "AbstractCommand/OptionCommandBase.h"
#include "Engine/ExecContext.h"


class DumpCommand : public CommandBase {
public:
    explicit DumpCommand(ExecContext& ctx, const std::string& opt, const std::string& file)
        : m_ctx(ctx), m_filename(file) {
        m_option = opt;
        m_name = "dump";}

    void execute() override;

    std::string usage() const override;

    std::string description() const override;

private:
    std::string m_option;
    ExecContext& m_ctx;
    std::string m_filename;
};

inline std::string DumpCommand::usage() const {
    return "dump <k> <filename>";
}

inline std::string DumpCommand::description() const {
    return "Executes the k-th last command from history and writes its output "
           "to the specified file. The file is overwritten if it already exists.";
}



#endif //OOP1PROJEKAT_DUMPCOMMAND_H