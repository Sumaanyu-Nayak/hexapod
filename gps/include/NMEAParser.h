#ifndef NMEA_PARSER_H
#define NMEA_PARSER_H

#include <string>
#include <vector>
#include "Epoch.h"

class NMEAParser {
public:
    static void parseLine(const std::string &line, GNSS_Epoch &epoch);

private:
    static std::vector<std::string> split(const std::string &s, char delim);
};

#endif
