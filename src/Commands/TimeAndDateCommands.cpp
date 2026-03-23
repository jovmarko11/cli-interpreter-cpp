#include "TimeAndDateCommands.h"

#include <iomanip>
#include <sstream>
// formati ispisa vremena i datuma
std::string TimeCommand::getFormat() { return "%H:%M:%S"; }

std::string DateCommand::getFormat() { return "%Y-%m-%d"; }

void TimeCommand::execute() {
    requireOutput(m_name);
    m_outputText.clear();

    std::time_t now = std::time(nullptr);
    std::tm* timeInfo = std::localtime(&now);

    // int h = timeInfo->tm_hour; int m = timeInfo->tm_min; int s = timeInfo->tm_sec;

    std::ostringstream oss;
    oss << std::put_time(timeInfo, getFormat().c_str());

    m_outputText = oss.str() + '\n';
    sendOutput();
}

void DateCommand::execute() {
    requireOutput(m_name);
    m_outputText.clear();

    std::time_t now = std::time(nullptr);
    std::tm* timeInfo = std::localtime(&now);

    // int d = timeInfo->tm_mday; int m = timeInfo->tm_mon; int y = timeInfo->tm_year + 1900;

    std::ostringstream oss;
    oss << std::put_time(timeInfo, getFormat().c_str());

    m_outputText = oss.str() + '\n';
    sendOutput();
}

// std::time_t now - vreme u sekundama
// std::tm* timeInfo - vreme koje moze da se razlozi (konvertuje) tm->hour,min,sec,mday,mon,year

/*
std::string TimeCommand::getFormat() {
    if (m_option == "h") return "%H";
    if (m_option == "m") return "%M";
    if (m_option == "s") return "%S";
    return "%H:%M:%S";
}

std::string DateCommand::getFormat() {
    if (m_option == "d") return "%d";        // dan (01–31)
    if (m_option == "m") return "%m";        // mesec (01–12)
    if (m_option == "y") return "%Y";        // godina (4 cifre)
    return "%Y-%m-%d";
}
 */