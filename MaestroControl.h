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
/**
 * @brief The MaestroControl class
 *
 * This class is used to control the Maestro Servo Controller.
 * It can be called in Python with the following code:
 * @code
 * import MaestroControl
 * mc = MaestroControl.MaestroControl("/dev/ttyACM0")
 * mc.setPosition(0, 4000)
 * mc.setPosition(1, 8000)
 * @endcode
 * @author MatchaOnMuffins
 * @date   06-22-2022
 **/

class MaestroControl {
private:
    int fd;
    const char *device;
public:

    /**
     * @brief Constructor for MaestroControl
     * @param dev device name (e.g. /dev/ttyACM0)
     */

    explicit MaestroControl(const char *dev) {
        device = dev;
        fd = open(device, O_RDWR | O_NOCTTY);
    }

    /**
     * @brief Reconnects if connection is lost
     *
     * Should only be used internally by the MaestroControl class itself.
     */

    void reconnect() {
        fd = open(device, O_RDWR | O_NOCTTY);
        perror("Reconnecting");
    }

    /**
     * @brief Returns the name of the serial port.
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
    * @param target servo position (4000-8000)
    * @return -1 if an error occurred, 0 if successful
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
     * @brief Gets position of connected servo on channel given
     *
     * Will only return a number from 4000-8000 or -1 if an error occurred.
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
     *
     * Disconnects from serial port
     */
    void destroy() const {
        close(fd);
    }

};