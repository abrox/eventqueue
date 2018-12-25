# eventqueue
Simple thread safe eventqueue implementation for arduino.
Motivation for this project was create simple, template based 
event queue that can be used to handle communication between main loop and interuphandlers in thread safe manner e.g. Timer callback with [ESP8266 Ticker](https://arduino-esp8266.readthedocs.io/en/latest/libraries.html#ticker).

## Usage 
See [ Example](https://github.com/abrox/eventqueue/blob/master/examples/simple/simple.ino).

## Build and run tests in host
Require that You have [Unittest++ ](https://github.com/unittest-cpp/unittest-cpp) installed.Tested with Ubuntu 16.04
```
mkdir buid
cd build
cmake ../```
make
./tests/tests
```
## Documentation
Doxygen can be built with command:
```
make docs
```
## Similar Projects
- [QueueArray](https://github.com/interactive-matter/QueueArray)
- [ArduinoRingBuffer](https://github.com/wizard97/ArduinoRingBuffer)
