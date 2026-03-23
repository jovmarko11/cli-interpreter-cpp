#include "RmCommand.h"
#include "Exceptions/Exception.h"
#include <fstream>
#include <filesystem>
RmCommand::RmCommand(const std::string& filename)
        :   FileCommandBase(filename)
{
    m_name = "rm";
}

void RmCommand::throwError() const {
    throw Exception(ErrorType::CommandSemantic,
    "File: " + m_filename + " does not exist.");
}

void RmCommand::execute() {

    if (!fileExists())
        throwError();

    try {
        bool deleted = std::filesystem::remove(m_filename); // vraca true ako je fajl izbrisan iz sistema

        if (!deleted)
            throw Exception(ErrorType::CommandSemantic, "Could not delete file: " + m_filename);
    }
    catch (const std::filesystem::filesystem_error& e) {
        // Ako operativni sistem ne da dozvolu za brisanje
        throw Exception(ErrorType::CommandSemantic, "Filesystem error: " + std::string(e.what()));
    }
}