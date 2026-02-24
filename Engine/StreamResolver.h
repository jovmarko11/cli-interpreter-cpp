#ifndef OOP1PROJEKAT_STREAMRESOLVER_H
#define OOP1PROJEKAT_STREAMRESOLVER_H
#include "../Streams/InputAndOutputStream.h"

/// StreamResolver - odredjuje I/O tok komande (console, file, string)

struct ParsedCommand;

class StreamResolver {
public:

    // Struktura koja sadrzi ulazni i izlazni tok za komandu
    struct Streams {
        InputStream* in = nullptr;
        OutputStream* out = nullptr;

        // Dinamicki alociran I/O koji treba dealocirati - redirekcije
        InputStream* ownedIn = nullptr;
        OutputStream* ownedOut = nullptr;
    };

    // Na osnovu ParsedCommand odredjuje tokove
    Streams resolve(const ParsedCommand& spec,
                        bool takesSourceArgument,
                        InputStream& defaultIn,
                        OutputStream& defaultOut) const;
private:
    // Ako postoji < filename pregazi ulazni tok i postavi FileInputStream - Ima prioritet nad argument inputom
    static void applyInputRedirection(const ParsedCommand& spec, Streams& s);

    // Ako postoji > filename ili >> filename postavlja FileOutputStream(truncate ili append) - pregazi podrazumevani izlazni tok (console ili pipe)
    static void applyOutputRedirection(const ParsedCommand& spec, Streams& s);

    // Ulazni tok na osnovu argumenta (StringInput ili FileInput Stream)
    static void applyArgumentInput(const ParsedCommand& spec, Streams& s, bool takesSourceArgument);

};


#endif //OOP1PROJEKAT_STREAMRESOLVER_H