#include "TimeAndDateCommands.h"

#include <iomanip>
#include <sstream>
// FORMATI ISPISA VREMENA I DATUMA
inline std::string TimeCommand::getFormat() { return "%H:%M:%S"; }

inline std::string DateCommand::getFormat() { return "%Y-%m-%d"; }


// std::time_t now - vreme u sekundama
// std::tm* timeInfo - vreme koje moze da se razlozi (konvertuje) tm->hour,min,sec,mday,mon,year
void TimeCommand::execute() {
    requireOutput(m_name);
    m_outputText.clear();

    std::time_t now = std::time(nullptr);
    std::tm* timeInfo = std::localtime(&now);

    int h = timeInfo->tm_hour;
    int m = timeInfo->tm_min;
    int s = timeInfo->tm_sec;

    std::ostringstream oss;
    oss << std::put_time(timeInfo, getFormat().c_str());

    m_outputText = oss.str();
    sendOutput();
}

void DateCommand::execute() {
    requireOutput(m_name);
    m_outputText.clear();

    std::time_t now = std::time(nullptr);
    std::tm* timeInfo = std::localtime(&now);

    int d = timeInfo->tm_mday;
    int m = timeInfo->tm_mon;
    int y = timeInfo->tm_year + 1900;

    std::ostringstream oss;
    oss << std::put_time(timeInfo, getFormat().c_str());

    m_outputText = oss.str();
    sendOutput();
}
