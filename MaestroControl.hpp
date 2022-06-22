#include <fcntl.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>

#ifdef _WIN32
#define O_NOCTTY 0
#include <Windows.h>
#else

#include <termios.h>

#endif

class MaestroControl {
private:
    int fd;
    const char *device;
public:

    /**
     * @brief MaestroControl constructor
     * @param dev device name (e.g. /dev/ttyACM0)
     */

    explicit MaestroControl(const char *dev) {
        device = dev;
        fd = open(device, O_RDWR | O_NOCTTY);
    }

    /**
     * @brief Reconnects if connection is lost
     */

    void reconnect() {
        fd = open(device, O_RDWR | O_NOCTTY);
        perror("Reconnecting");
    }

    /**
     * @brief Returns the serial port name
     * @return Serial port name (e.g. /dev/ttyACM0)
     */

    std::string getSerialPort() {
        std::ostringstream buffer;
        buffer << device;
        return buffer.str();
    }

    /**
    * @brief Sets position of servo to given value
    * @param channel channel number
    * @param position servo position (4000-8000)
    * @return -1 if an error occurred else 0 if successful
    */

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

    /**
     * @brief Gets position of servo
     * @param channel channel number
     * @return position of servo, or -1 if error
     */

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

    /**
     * @brief Destructor
     */
    void destroy() const {
        close(fd);
    }

};