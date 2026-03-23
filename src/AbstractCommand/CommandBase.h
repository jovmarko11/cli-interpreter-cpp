
#ifndef OOP1PROJEKAT_COMMANDBASE_H
#define OOP1PROJEKAT_COMMANDBASE_H
#include "ICommand.h"
#include "StreamAware.h"
#include "../Streams/InputAndOutputStream.h"
#include <stdexcept>
#include <cstdio>

#include "SemanticAware.h"

/// Zajednicka baza za sve komande
/// Sadrzi ime komande i zajednicke bafere / metode za rad sa tokovima

class CommandBase : public ICommand, public StreamAware, public SemanticAware {
public:
    CommandBase() = default;
    virtual ~CommandBase() = default;

    virtual std::string usage() const { return m_name + " [args]"; }
    virtual std::string description() const { return "No description available."; }

protected:
    std::string m_inputText; // pomocni bafer za ucitavanje teskta
    std::string m_outputText; // pomocni bafer za prosledjivanje podataka

    void loadInput(); // ucitava sve dostupne podatke sa ulaznog toka u m_inputText
    void clearBuffers(); // prazni interne bafere pre obrade
    void sendOutput(); // salje sadrzaj m_outputText bafera na izlazni tok

    std::vector<std::string> parseLines() const; // vraca vektor isparsiranih linija
    std::vector<std::string> parseWords() const; // vraca vektor isparsiranih reci
    int countLines() const; // vraca broj linija u ucitanom baferu
};

#endif //OOP1PROJEKAT_COMMANDBASE_H