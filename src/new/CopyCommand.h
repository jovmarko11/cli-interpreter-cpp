//
// Created by Marko Jovanovic on 23.2.26..
//

#ifndef OOP1PROJEKAT_COPYCOMMAND_H
#define OOP1PROJEKAT_COPYCOMMAND_H
#include "AbstractCommand/CommandBase.h"


class CopyCommand : public CommandBase {
public:
    CopyCommand(const std::string& from, const std::string& to) : m_from(from), m_to(to) { m_name = "copy"; };

    void execute() override;

    std::string usage() const override;

    std::string description() const override;

private:
    std::string m_from;
    std::string m_to;
};

inline std::string CopyCommand::usage() const {
    return "copy fileFrom fileTo";
}

inline std::string CopyCommand::description() const {
    return "Copies the contents of the source file to the destination file";
}


#endif //OOP1PROJEKAT_COPYCOMMAND_H