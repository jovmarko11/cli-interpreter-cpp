#ifndef OOP1PROJEKAT_STREAMRESOLVERNEW_H
#define OOP1PROJEKAT_STREAMRESOLVERNEW_H
#include "Streams/InputAndOutputStream.h"

// StreamResolver - zaduzen za povezivanje komande sa konkretnim Inuput i Output Streamovima
// Razresava argumente kao izvore (string, file, console), redirekcije i cevovode
struct ParsedCommand;

class StreamResolverNew {
public:
    struct Streams {
        InputStream* in = nullptr;      // Aktivni ulazni tok
        OutputStream* out = nullptr;    // Aktivni izlazni tok
        // Memorija kojom upravlja resolver
        InputStream* ownedIn = nullptr;
        OutputStream* ownedOut = nullptr;
    };

    // glavna metoda koja vraca tokove za zadatu komandu
    Streams resolve(const ParsedCommand& spec, bool hasInput, bool hasOutput, bool takesSourceArgument, bool inputFromPipe, InputStream& defaultIn, OutputStream& defaultOut);

private:
    // Pomocne metode za odvojeno razresavanje ulaza i izlaza
    void resolveInput(const ParsedCommand &spec, Streams &s, bool hasInput, bool takesSourceArgument, bool inputFromPipe, InputStream &defaultIn);

    void resolveOutput(const ParsedCommand& spec, Streams& s, bool hasOutput, OutputStream& defaultOut);

    void validateInput(const ParsedCommand &spec, bool hasInput, bool takesSourceArgument, bool inputFromPipe);

    void validateOutput(const ParsedCommand& spec, bool hasOutput);
};



#endif //OOP1PROJEKAT_STREAMRESOLVERNEW_H