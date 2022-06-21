# Maestro Control

A simple and easy to use python module for Maestro Servo Controllers.

## Building

CMake and Boost.Python are required for building this module.

### Install CMake

##### Ubuntu

```bash
sudo apt-get install cmake
```

##### MacOS

```bash
brew install cmake
```

##### Windows

Download Cmake from [here](https://cmake.org/download/).

### Install Boost.Python

##### Ubuntu

```bash
sudo apt-get install python-boost-python3
```

##### MacOS

```bash
brew install boost-python3
```

##### Windows

Download Boost.Python from [here](https://www.boost.org/users/download/).

(good luck with that)

### Build MaestroControl

```bash
mkdir build
cd build
cmake ..
make
```

## Using Pre-Built Binaries

Pre-built binaries are available for Linux and MacOS.
They can be downloaded from [here](https://www.youtube.com/watch?v=dQw4w9WgXcQ).

## Usage

```python
import time

from libMaestroControl import MaestroControl

# The Servo Controller must be connected to the computer via USB and set to "USB Dual Port" mode.
# Instructions can be found here: https://www.pololu.com/product/1356/resources
if __name__ == "__main__":
    # Create a new MaestroControl object and initialize it
    # The parameter is the serial port of the Servo Controller
    # This can be found by using the "ls /dev" command in the terminal
    # Usually /dev/cu.usbmodem001033281 on MacOS, /dev/ttyACM0 on Linux, and \\\\.\\COM6 on Windows
    # Sometimes, two serial ports can be found in the /dev/ folder, so you may need to try both and see which one works.
    control = MaestroControl("/dev/cu.usbmodem001033281")
    # A servo can be set to any position between 4000 and 8000
    # Syntax: control.setPosition(servo channel, position)
    control.setPosition(0, 4000)  # Set channel 0 servo position to 4000
    print(control.getPosition(0))  # prints the current position of the servo on channel 0 (4000)
    time.sleep(1)  # Wait for 1 second (required because the servo needs time to move to the new position)
    control.setPosition(0, 8000)  # Set channel 0 servo position to 8000
    print(control.getPosition(0))  # prints the current position of the servo on channel 0 (8000)
    control.getSerialPort()  # returns the serial port of the servo controller
    control.destroy()  # closes the connection to the servo controller
```

## License

The license is available [here](LICENSE).