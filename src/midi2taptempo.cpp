/* Sampled from https://github.com/sparkfun/MIDI_Shield/blob/V_1.5/Firmware/clock-recv/clock-recv.ino */

#include <MIDI.h>
#include <Automaton.h>

#define PIN_LED_TEMPO 13
#define PIN_SWITCH 2
#define PIN_DIVIDER_1 5 
#define PIN_DIVIDER_2 7 
#define PIN_DIVIDER_3 9 
#define PIN_DIVIDER_4 11 
#define PIN_MULTIPLIER_1 6 
#define PIN_MULTIPLIER_2 8 
#define PIN_MULTIPLIER_3 10 
#define PIN_MULTIPLIER_4 12

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);

unsigned int ticks = 0;
unsigned int midiBeat = 0;
unsigned int midibeatToBeat = 16;

bool shouldTap = true;

Atm_led beatLED;
Atm_led tapSwitch;

Atm_digital divider1;
Atm_digital multiplier1;
Atm_digital divider2;
Atm_digital multiplier2;
Atm_digital divider3;
Atm_digital multiplier3;
Atm_digital divider4;
Atm_digital multiplier4;


void doubleMIDIBeatsToBeat(int idx, int v, int up) {
  midibeatToBeat *= 2;
}

void halveMIDIBeatsToBeat(int idx, int v, int up) {
  midibeatToBeat /= 2;
}

void tap() {
  beatLED.trigger(beatLED.EVT_BLINK);
  tapSwitch.trigger(tapSwitch.EVT_BLINK);
}

void midiClockHandler() {
  if(!shouldTap) return;
  
  ticks++;
  
  if(ticks == 3) {
    midiBeat += 2;
    ticks = 0;
  } else {
    return;
  }
  
  if(midiBeat >= midibeatToBeat) {
    midiBeat = 0;
    tap();
  }
}

void midiStartHandler() {
  ticks = 0;
  midiBeat = 0;
  shouldTap = true;
  tap();
}

void midiStopHandler() {
  shouldTap = false;
}

void setup() 
{  
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.turnThruOff();
  MIDI.setHandleClock(midiClockHandler);
  MIDI.setHandleStart(midiStartHandler);
  MIDI.setHandleStop(midiStopHandler);

  // Setup machines 
  beatLED.begin(LED_BUILTIN).blink(25, 0, 1);
  tapSwitch.begin(PIN_SWITCH).blink(100, 100, 1);

  divider1.begin(PIN_DIVIDER_1, 20, true, true).onChange(LOW, halveMIDIBeatsToBeat);
  divider1.begin(PIN_DIVIDER_1, 20, true, true).onChange(HIGH, doubleMIDIBeatsToBeat);

  multiplier1.begin(PIN_MULTIPLIER_1, 20, true, true).onChange(LOW, doubleMIDIBeatsToBeat);
  multiplier1.begin(PIN_MULTIPLIER_1, 20, true, true).onChange(HIGH, halveMIDIBeatsToBeat);

  divider2.begin(PIN_DIVIDER_2, 20, true, true).onChange(LOW, halveMIDIBeatsToBeat);
  divider2.begin(PIN_DIVIDER_2, 20, true, true).onChange(HIGH, doubleMIDIBeatsToBeat);

  multiplier2.begin(PIN_MULTIPLIER_2, 20, true, true).onChange(LOW, doubleMIDIBeatsToBeat);
  multiplier2.begin(PIN_MULTIPLIER_2, 20, true, true).onChange(HIGH, halveMIDIBeatsToBeat);

  divider3.begin(PIN_DIVIDER_3, 20, true, true).onChange(LOW, halveMIDIBeatsToBeat);
  divider3.begin(PIN_DIVIDER_3, 20, true, true).onChange(HIGH, doubleMIDIBeatsToBeat);

  multiplier3.begin(PIN_MULTIPLIER_3, 20, true, true).onChange(LOW, doubleMIDIBeatsToBeat);
  multiplier3.begin(PIN_MULTIPLIER_3, 20, true, true).onChange(HIGH, halveMIDIBeatsToBeat);

  divider4.begin(PIN_DIVIDER_4, 20, true, true).onChange(LOW, halveMIDIBeatsToBeat);
  divider4.begin(PIN_DIVIDER_4, 20, true, true).onChange(HIGH, doubleMIDIBeatsToBeat);

  multiplier4.begin(PIN_MULTIPLIER_4, 20, true, true).onChange(LOW, doubleMIDIBeatsToBeat);
  multiplier4.begin(PIN_MULTIPLIER_4, 20, true, true).onChange(HIGH, halveMIDIBeatsToBeat);
}

void loop() 
{
  MIDI.read();
  automaton.run();
}
