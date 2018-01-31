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
      Sync();
    }
  }
}

void Sync() {
  digitalWrite(13, HIGH);
  delay(10);
  digitalWrite(13, LOW);
  delay(10);
}
