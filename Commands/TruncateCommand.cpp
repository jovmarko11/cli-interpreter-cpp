#include "TruncateCommand.h"
#include <fstream>

#include "Exceptions/Exception.h"

void TruncateCommand::throwError() const {
    throw Exception(ErrorType::CommandSemantic,
    "File: " + m_filename + " does not exist.");
}

void TruncateCommand::deleteContent() const {
    std::ofstream ofs(m_filename, std::ios::trunc);

    if (!ofs) {
        throw Exception(ErrorType::System,
        m_name + ": cannot truncate file: " + m_filename);
    }
}

void TruncateCommand::execute() {

    if (!fileExists())
        throwError();

    deleteContent();
}