#include <MIDI.h>
#include <SoftwareSerial.h>
#define swrxPin 16
#define swtxPin 17

SoftwareSerial softSerial(swrxPin,swtxPin);


// Create and bind the MIDI interface to the default hardware Serial port
// MIDI_CREATE_DEFAULT_INSTANCE();
MIDI_CREATE_INSTANCE(SoftwareSerial, softSerial, MIDI);

void setup() {
  MIDI.begin();
}

void loop() {
//    MIDI.read();
  MIDI.sendNoteOn(42,127,1);  // ノートオン(pitch 42, velo 127 on channel 1)
   delay(1000);                // 1秒待機
//   MIDI.sendNoteOff(42,0,1);   // ノートオフ
}
