#include <iostream>
#include "SerialReader.h"
#include "NMEAParser.h"

int main() {
    try {
        SerialReader serial("/dev/ttyUSB0", 9600);  // adjust device if needed
        GNSS_Epoch epoch;
        std::string line;

        std::cout << "Reading GNSS data...\n";
        while (true) {
            if (serial.readLine(line)) {
                NMEAParser::parseLine(line, epoch);
            }
        }
    }
    catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
} 
