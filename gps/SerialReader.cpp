#include "SerialReader.h"
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <iostream>
#include <thread>
#include <chrono>

SerialReader::SerialReader(const std::string &device, int baudrate) {
    fd = open(device.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        perror("open");
        throw std::runtime_error("Failed to open serial port");
    }

    termios tty{};
    if (tcgetattr(fd, &tty) != 0) {
        perror("tcgetattr");
        close(fd);
        throw std::runtime_error("Failed to get termios");
    }

    speed_t br = B9600;
    if (baudrate == 115200) br = B115200;
    else if (baudrate == 4800) br = B4800;
    cfsetospeed(&tty, br);
    cfsetispeed(&tty, br);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_iflag &= ~IGNBRK;
    tty.c_lflag = 0;
    tty.c_oflag = 0;
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1;

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~(PARENB | PARODD);
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("tcsetattr");
        close(fd);
        throw std::runtime_error("Failed to set termios");
    }
}

SerialReader::~SerialReader() {
    if (fd >= 0) close(fd);
}

bool SerialReader::readLine(std::string &out) {
    char c;
    static std::string buffer;
    int n = read(fd, &c, 1);
    if (n > 0) {
        if (c == '\n') {
            out = buffer;
            buffer.clear();
            return true;
        } else if (c != '\r') {
            buffer.push_back(c);
        }
    } else {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return false;
}
