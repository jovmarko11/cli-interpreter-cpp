#include "TruncateCommand.h"
#include <fstream>

#include "Exceptions/Exception.h"
TruncateCommand::TruncateCommand(const std::string& filename)
        :   FileCommandBase(filename)
{
    m_name = "truncate";
}


void TruncateCommand::throwError() const {
    throw Exception(ErrorType::CommandSemantic, "File: " + m_filename + " does not exist.");
}

void TruncateCommand::deleteContent() const {
    // otvaranje fajla sa std::ios::trunc automatski brise njegov celokupan sadrzaj
    std::ofstream ofs(m_filename, std::ios::trunc);

    if (!ofs) {
        throw Exception(ErrorType::System, m_name + ": cannot truncate file: " + m_filename);
    }
}

void TruncateCommand::execute() {
    if (!fileExists())
        throwError();

    deleteContent();
}