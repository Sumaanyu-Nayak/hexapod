#ifndef SERIAL_READER_H
#define SERIAL_READER_H

#include <string>
#include "Epoch.h"

class SerialReader {
public:
    SerialReader(const std::string &device, int baudrate = 9600);
    ~SerialReader();
    bool readLine(std::string &out);

private:
    int fd;
};

#endif
