#include "TouchCommand.h"
#include <fstream>
#include "Exceptions/Exception.h"

void TouchCommand::createEmptyFile() const {
    // pravi prazan fajl
    std::ofstream f(m_filename);
    if (!f) {
        throw Exception(ErrorType::System,
            m_name + ": cannot create file: " + m_filename);
    }
}

void TouchCommand::throwError() const {
    // fajl vec postoji
    throw Exception(ErrorType::CommandSemantic,
        "File: " + m_filename + " already exists.");
}

void TouchCommand::execute() {

    if (fileExists())
        throwError();

    createEmptyFile();
}