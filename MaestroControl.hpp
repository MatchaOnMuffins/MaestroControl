#include <fcntl.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>

#ifdef _WIN32
#define O_NOCTTY 0
#include <Windows.h>
#else

#include <unistd.h>

#endif

class MaestroControl {
private:
    int fd;
    const char *device;
public:
    void reconnect() {
        fd = open(device, O_RDWR | O_NOCTTY);
        perror("Reconnecting");
    }

    explicit MaestroControl(const char *dev) {
        device = dev;
        fd = open(device, O_RDWR | O_NOCTTY);
    }

    std::string getSerialPort() {
        std::ostringstream buffer;
        buffer << device;
        return buffer.str();
    }

    int setPosition(unsigned char channel, unsigned short target) {
        unsigned char command[] = {0x84, channel, static_cast<unsigned char>(target & 0x7F),
                                   static_cast<unsigned char>(target >> 7 & 0x7F)};
        if (write(fd, command, sizeof(command)) == -1) {
            reconnect();
            perror("Error writing");
            return -1;
        }
        return 0;
    }

    int getPosition(unsigned char channel) {
        unsigned char command[] = {0x90, channel};
        if (write(fd, command, sizeof(command)) == -1) {
            reconnect();
            perror("Error writing");
            return -1;
        }

        unsigned char response[2];
        if (read(fd, response, 2) != 2) {
            reconnect();
            perror("Error reading");
            return -1;
        }

        return response[0] + 256 * response[1];
    }

    void destroy() const {
        close(fd);
    }

};