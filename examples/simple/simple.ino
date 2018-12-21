/*
MIT License

Copyright (c) 2018 Jukka-Pekka Sarjanen

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <eventqueue.h>

typedef enum event_t{
  MSG_READY,
  BUTTON_PRESSED
}event_t;

const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte bounce = 0;
String inputString = "";

EventQueue<event_t> eQueue;


//debounce restles I/O
#define SETTLE_DOWN 5
#define BUFF_SIZE 100


void serialEvent()
{
  while (Serial.available()) {
    // get the new byte:
    char in = (char)Serial.read();
    // add it to the inputString:
    inputString += in;
   
    if (in == '\n') {
      eQueue.putQ(MSG_READY);
    }
  }
}

void irqFunc()
{
    if( !bounce ){
        eQueue.putQ(BUTTON_PRESSED);
        bounce = SETTLE_DOWN;
  }
    
}

void setup() {

    Serial.begin(115200);
    inputString.reserve(BUFF_SIZE);

    pinMode(ledPin, OUTPUT);
    pinMode(interruptPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interruptPin), irqFunc, LOW);
}

void loop() {
    
    event_t msg;
    if( eQueue.getQ(msg) ) {

        switch(msg){
        case MSG_READY:
          Serial.println(inputString);
          // clear the string:
          inputString = "";
        break;
        case BUTTON_PRESSED:
          Serial.println("Button pressed");
        break;
        }; 
    }

    if( bounce )
        bounce --;
}
