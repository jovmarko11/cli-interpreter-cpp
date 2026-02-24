
#ifndef OOP1PROJEKAT_TIMEANDDATECOMMANDS_H
#define OOP1PROJEKAT_TIMEANDDATECOMMANDS_H
#include "AbstractCommand/CommandBase.h"

/// Obe vremenske komande nasledjuju TimeDate klasu koja vrsi izvrsavanje
/// TimeCommand i DateCommand samo vracaju format ispisa vremena i datuma

class TimeCommand : public CommandBase {
public:
    explicit TimeCommand() {    m_name = "time";    }

    void execute() override;

protected:
    static std::string getFormat() ;

};

class DateCommand : public CommandBase {
public:
    explicit DateCommand() {    m_name = "date";    }

    void execute() override;

protected:
    static std::string getFormat();

};


#endif //OOP1PROJEKAT_TIMEANDDATECOMMANDS_H