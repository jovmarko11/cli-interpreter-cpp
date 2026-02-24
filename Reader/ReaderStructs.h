#ifndef OOP1PROJEKAT_PARSETYPES_H
#define OOP1PROJEKAT_PARSETYPES_H
#include <string>

struct ReadResult {
    std::string line;
    bool truncated = false;
    bool eof = false;
};

#endif //OOP1PROJEKAT_PARSETYPES_H