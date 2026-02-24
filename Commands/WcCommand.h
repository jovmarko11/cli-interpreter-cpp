//
// Created by Marko Jovanovic on 6.2.26..
//

#ifndef OOP1PROJEKAT_WCCOMMAND_H
#define OOP1PROJEKAT_WCCOMMAND_H
#include <string>
#include "AbstractCommand/OptionCommandBase.h"


class WcCommand : public OptionCommandBase {
public:

    explicit WcCommand(const std::string& opt);

    static int countChars(const std::string& s);

    static int countWords(const std::string& s);

    void execute() override;

protected:

    bool isValidOption(const std::string& opt) const override;

};

// mozda da se doda ispis lose komande
inline bool WcCommand::isValidOption(const std::string &opt) const {
    if (opt == "w" || opt == "c")
        return true;
    return false;
}



#endif //OOP1PROJEKAT_WCCOMMAND_H