//
// Created by Marko Jovanovic on 12.2.26..
//

#ifndef OOP1PROJEKAT_PIPEFLOWCONTROLLER_H
#define OOP1PROJEKAT_PIPEFLOWCONTROLLER_H
#include "PipeStream.h"
#include "../Streams/InputAndOutputStream.h"

/// PipeFlowController - zaduzen za povezivanje komandi u cevovodu
/// Kreira PipeStream objekte i odredjuje koji izlaz ide u koji ulaz, ulancava
/// ulancava PipeStream-ove
/// Korisnik PipeFlowController-a je Intepreter - povezivanje komandi pre izvrsavanja

class PipeFlowController {
public:
    // Konektor za jednu komandu
    struct Link {
        InputStream* pipeIn = nullptr; // ulaz koji dolazi iz prethodne komande
        OutputStream* pipeOut = nullptr; // izlazi koji ide u sledecu komandu
    };

    // Kreira commandCount - 1 PipeStrem-ova (prva komanda bez pipeIn, poslednja bez pipeOut)
    std::vector<Link> buildLinks(int commandCount);

    // Oslobadja sve dinamicki alocirane PipeStream objekte
    ~PipeFlowController();

private:
    // Cuva kreirane PipeStream objekte kako bi mogao da ih dealocira nakon izvrsavanja
    std::vector<PipeStream*> m_pipes;

    void resetPipes(int commandCount);
};


#endif //OOP1PROJEKAT_PIPEFLOWCONTROLLER_H