//
// Created by Marko Jovanovic on 11.2.26..
//

#ifndef OOP1PROJEKAT_COMMANDBASE_H
#define OOP1PROJEKAT_COMMANDBASE_H
#include "ICommand.h"
#include "StreamAware.h"
#include "../Streams/InputAndOutputStream.h"
#include <stdexcept>
#include <cstdio>

/// Zajednicka baza za sve komande
/// Drzi ime komande i sve pomocne metode

class CommandBase : public ICommand, public StreamAware {
public:
    CommandBase() = default;

    std::string getCommandName() const  { return m_name; }

protected:
    std::string m_name;

    // pomocni bafer za ucitavanje teskta
    std::string m_inputText;
    // pomocni bafer za prosledjivanje podataka
    std::string m_outputText;

    void loadInput(); // ubacuje input u m_text iz InputStream* m_input
    void clearBuffers();
    void sendOutput();
};

#endif //OOP1PROJEKAT_COMMANDBASE_H