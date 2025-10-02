#include "NMEAParser.h"
#include <sstream>
#include <iostream>

std::vector<std::string> NMEAParser::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

void NMEAParser::parseLine(const std::string &line, GNSS_Epoch &epoch) {
    if (line.empty() || line[0] != '$') return;

    if (line.find("$GNRMC") == 0) {
        if (epoch.isComplete()) {
            std::cout << "\n===== Complete GNSS Epoch =====\n";
            std::cout << "RMC: " << epoch.RMC << "\n";
            std::cout << "VTG: " << epoch.VTG << "\n";
            std::cout << "GGA: " << epoch.GGA << "\n";
            for (auto &s : epoch.GSA) std::cout << "GSA: " << s << "\n";
            for (auto &s : epoch.GSV) std::cout << "GSV: " << s << "\n";
            std::cout << "GLL: " << epoch.GLL << "\n";
            std::cout << "================================\n";
            epoch.clear();
        }
        epoch.RMC = line;
    }
    else if (line.find("$GNVTG") == 0) epoch.VTG = line;
    else if (line.find("$GNGGA") == 0) epoch.GGA = line;
    else if (line.find("$GNGSA") == 0) epoch.GSA.push_back(line);
    else if (line.find("$GPGSV") == 0 || line.find("$GLGSV") == 0) epoch.GSV.push_back(line);
    else if (line.find("$GNGLL") == 0) epoch.GLL = line;
}
