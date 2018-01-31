/*
 * Original code by Little-Scale
 * https://little-scale.blogspot.fr/2008/05/how-to-deal-with-midi-clock-signals-in.html
 */

byte midi_start = 0xfa;
byte midi_stop = 0xfc;
byte midi_clock = 0xf8;
byte midi_continue = 0xfb;
int play_flag = 0;
byte data;
int tick_counter = 0;
int quarter_note = 0;

void setup() {
  Serial.begin(31250);
}

void loop() {
  if(Serial.available() > 0) {
    
    data = Serial.read();
    
    if(data == midi_start) {
      play_flag = 1;
    }
    else if(data == midi_continue) {
      play_flag = 1;
    }
    else if(data == midi_stop) {
      play_flag = 0;
    }
    else if((data == midi_clock) && (play_flag == 1)) {

      tick_counter++;
      
      // A quarter note == 24 MIDI ticks
      if(tick_counter == 24) {
        quarter_note++;
        tick_counter = 0;
      }

      // 4 quarter notes = 1 beat
      if(quarter_note == 4) {
        beat();
        quarter_note = 0;
      }
    }
  }
}

void beat() {
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
}
