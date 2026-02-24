#ifndef OOP1PROJEKAT_TRCOMMAND_H
#define OOP1PROJEKAT_TRCOMMAND_H
#include "AbstractCommand/CommandBase.h"


class TrCommand : public CommandBase {
public:
    // with je opcioni - brisanje ako je prazan
    explicit TrCommand(const std::string& what, const std::string& with = "");

    void execute() override;

private:

    std::string m_what;
    std::string m_with; // prazan za delete mode
    bool m_hasWith = false;

    // vraca true ako tekst postoji i izbrisan je
    void deleteText(std::string& text, const std::string& what);
    // vraca true ako tekst postoji i zamenjen je
    void replaceText(std::string& text, const std::string& what, const std::string& replacement);

};


inline TrCommand::TrCommand(const std::string& what, const std::string& with)
    :   m_what (what)
    ,   m_with (with)
{
    m_name = "tr";
    if (m_what.empty())
        throw std::runtime_error("tr: what cannot be empty");

    m_hasWith = !m_with.empty();
}


#endif //OOP1PROJEKAT_TRCOMMAND_H