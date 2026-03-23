
#ifndef OOP1PROJEKAT_COMMANDREADER_H
#define OOP1PROJEKAT_COMMANDREADER_H
#include <cstddef>
#include <iostream>
#include <string>
#include "ReaderStructs.h"

/// CommandReader - cita jednu liniju komande iz Input stream-a

class InputStream;

class CommandReader {
public:
    // Maksimalna dozvoljena duzina linije
    static constexpr std::size_t BUFFER_SIZE = 512;

    // Prima referencu na ulazni tok i koga cita
    explicit CommandReader(InputStream& inputStream);

    // Cita jednu liniju i vraca ReadResult
    ReadResult readLine();

private:
    // Ulazni tok iz kog se cita
    InputStream& m_inputstream;

    std::size_t m_maxLen{BUFFER_SIZE};
};


#endif //OOP1PROJEKAT_COMMANDREADER_H