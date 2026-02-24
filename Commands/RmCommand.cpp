#include "RmCommand.h"

#include <fstream>
#include <filesystem>

#include "Exceptions/Exception.h"

void RmCommand::throwError() const {
    throw Exception(ErrorType::CommandSemantic,
    "File: " + m_filename + " does not exist.");
}

void RmCommand::deleteFile() const {
    // brisanje fajla iz direktorijuma
    std::__fs::filesystem::remove(m_filename);
}

void RmCommand::execute() {

    if (!fileExists())
        throwError();

    deleteFile();
}