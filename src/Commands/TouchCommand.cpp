#include "TouchCommand.h"
#include <fstream>
#include "Exceptions/Exception.h"

TouchCommand::TouchCommand(const std::string& filename)
        :   FileCommandBase(filename)
{
    m_name = "touch";
}

void TouchCommand::createEmptyFile() const {
    // pravi prazan fajl
    std::ofstream f(m_filename);
    if (!f)
        throw Exception(ErrorType::System, m_name + ": cannot create file: " + m_filename);
}

void TouchCommand::throwError() const {
    // ukoliko fajl vec postoji prijavljuje gresku
    throw Exception(ErrorType::CommandSemantic, "File: " + m_filename + " already exists.");
}

void TouchCommand::execute() {
    if (fileExists())
        throwError();

    createEmptyFile();
}