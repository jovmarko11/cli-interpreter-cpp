//
// Created by Marko Jovanovic on 6.2.26..
//

#ifndef OOP1PROJEKAT_WCCOMMAND_H
#define OOP1PROJEKAT_WCCOMMAND_H
#include <string>
#include "AbstractCommand/OptionCommandBase.h"

// Komanda prebrojava karaktere ili reci sa ulaznog toka

class WcCommand : public OptionCommandBase {
public:

    // prima opciju koja odredjuje rezim rada
    explicit WcCommand(const std::string& opt);

    static int countChars(const std::string& s);
    static int countWords(const std::string& s);

    void execute() override;

    std::string usage() const override;

    std::string description() const override;

protected:

    bool isValidOption(const std::string& opt) const override;

};

inline bool WcCommand::isValidOption(const std::string &opt) const {
    if (opt == "w" || opt == "c")
        return true;
    return false;
}

inline std::string WcCommand::usage() const {
    return "wc -w|-c [argument]";
}

inline std::string WcCommand::description() const {
    return "Counts words (-w) or characters (-c) from the input stream and prints the result";
}



#endif //OOP1PROJEKAT_WCCOMMAND_H