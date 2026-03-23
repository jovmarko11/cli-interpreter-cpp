#ifndef OOP1PROJEKAT_TRCOMMAND_H
#define OOP1PROJEKAT_TRCOMMAND_H
#include "AbstractCommand/CommandBase.h"

// Komanda menja ili brise zadati podstring sa ulaznog toka

class TrCommand : public CommandBase {
public:
    // with je opcioni parametar - ako se izostavi, komanda radi u modu brisanja
    explicit TrCommand(const std::string& what, const std::string& with = "");

    void execute() override;

private:

    std::string m_what;
    std::string m_with; // prazan za delete mode

    bool m_hasWith = false; // flag koji odredjuje rezim rada komande

    // brise sva pojavljivanja podstringa what
    void deleteText(std::string& text, const std::string& what);

    // menja sva pojavljivanja podstringa what sa with
    void replaceText(std::string& text, const std::string& what, const std::string& replacement);
};




#endif //OOP1PROJEKAT_TRCOMMAND_H