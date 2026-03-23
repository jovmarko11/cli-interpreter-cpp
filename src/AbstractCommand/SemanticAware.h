//
// Created by Marko Jovanovic on 16.3.26..
//

#ifndef OOP1PROJEKAT_SEMANTICAWARE_H
#define OOP1PROJEKAT_SEMANTICAWARE_H
#include <string>

#endif //OOP1PROJEKAT_SEMANTICAWARE_H

class SemanticAware {
public:
    virtual ~SemanticAware() = default;

    std::string name() const { return m_name; }
    virtual std::string usage() const = 0;
    virtual std::string description() const = 0;

protected:
    std::string m_name; // ime komande

};