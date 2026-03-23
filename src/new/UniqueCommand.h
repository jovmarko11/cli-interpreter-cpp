//
// Created by Marko Jovanovic on 5.3.26..
//

#ifndef OOP1PROJEKAT_UNIQUECOMMAND_H
#define OOP1PROJEKAT_UNIQUECOMMAND_H
#include "AbstractCommand/OptionCommandBase.h"


class UniqueCommand : public OptionCommandBase{
public:
    UniqueCommand(std::string& opt);

    void execute() override;

    std::string usage() const override;

    std::string description() const override;

private:
    std::vector<std::string> m_UniqueLines;
    std::vector<int> m_LineCounter;
    int m_LineNumber;

    std::vector<std::string> loadLines();

    bool isInSet(std::string &l, std::vector<std::string> &lines);

    bool isValidOption(const std::string &opt) const override;
};


inline bool UniqueCommand::isValidOption(const std::string &opt) const {
    if (opt == "u" || opt == "")
        return true;
    return false;
}

inline std::string UniqueCommand::usage() const {
    return "unique [-u] [argument]";
}

inline std::string UniqueCommand::description() const {
    return "Removes duplicate lines from the input stream. "
           "By default, outputs all unique lines. "
           "With option -u, outputs only lines that appear exactly once.";
}

#endif //OOP1PROJEKAT_UNIQUECOMMAND_H