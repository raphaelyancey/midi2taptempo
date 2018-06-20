/* Sampled from https://github.com/sparkfun/MIDI_Shield/blob/V_1.5/Firmware/clock-recv/clock-recv.ino */

#include <SoftwareSerial.h>
#include <MsTimer2.h>
#include <MIDI.h>

#define PIN_LED_TEMPO 13

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);

void setup() 
{
  pinMode(PIN_LED_TEMPO, OUTPUT);
  digitalWrite(PIN_LED_TEMPO, HIGH);
  
#if 1
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.turnThruOff();
#endif  

}

void loop() 
{  
  // 1 MIDI beat = 6 ticks = 16th note
  // 1 "real" beat = 24 ticks
  static uint8_t  ticks = 0;
  if(MIDI.read() && MIDI.getType() == midi::Clock)
  {
        ticks++;
        if(ticks == 1) {
          // Do something
        }
        else if(ticks > 1 && ticks < 6)
        {
          digitalWrite(PIN_LED_TEMPO, HIGH);
        }
        else if(ticks == 6)
        {
          digitalWrite(PIN_LED_TEMPO, LOW);
        }
        else if(ticks >= 24)
        {
          ticks = 0;
        }
  }
}
