//
// Created by Marko Jovanovic on 11.2.26..
//

#ifndef OOP1PROJEKAT_OPTIONCOMMANDBASE_H
#define OOP1PROJEKAT_OPTIONCOMMANDBASE_H
#include "CommandBase.h"
#include "Exceptions/Exception.h"

class OptionCommandBase : public CommandBase {
public:
    void setOption(const std::string& opt)  { m_option = opt; }

protected:
    std::string m_option;

    virtual bool isValidOption(const std::string& opt) const = 0;

    void validateOption() const;

};

inline void OptionCommandBase::validateOption() const {
    if (!isValidOption(m_option)) {
        throw Exception(ErrorType::CommandSemantic,"Invalid option for " + m_name);
    }
}


#endif //OOP1PROJEKAT_OPTIONCOMMANDBASE_H