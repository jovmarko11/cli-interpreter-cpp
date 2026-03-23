
#ifndef OOP1PROJEKAT_TIMEANDDATECOMMANDS_H
#define OOP1PROJEKAT_TIMEANDDATECOMMANDS_H
#include "AbstractCommand/CommandBase.h"

// Komande za ispis trenutnog sistemskog vremena i datuma

class TimeCommand : public CommandBase {
public:
    explicit TimeCommand() {    m_name = "time";    }

    void execute() override;

    std::string usage() const override;

    std::string description() const override;

protected:

    static std::string getFormat() ;

};

class DateCommand : public CommandBase {
public:
    explicit DateCommand() {    m_name = "date";    }

    void execute() override;

    std::string usage() const override;

    std::string description() const override;

protected:

    static std::string getFormat();

};

inline std::string TimeCommand::usage() const {
    return "time";
}

inline std::string DateCommand::usage() const {
    return "date";
}

inline std::string TimeCommand::description() const {
    return "Prints the current system time to the output stream";
}

inline std::string DateCommand::description() const {
    return "Prints the current system date to the output stream";
}

#endif //OOP1PROJEKAT_TIMEANDDATECOMMANDS_H