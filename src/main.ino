#include <MIDI.h>
#include <SoftwareSerial.h>
#define swrxPin 16
#define swtxPin 17
SoftwareSerial mySerial;
// #include <SoftwareSerial.h>

// SoftwareSerial softSerial(16,17);
// SoftwareSerial softSerial;


// Create and bind the MIDI interface to the default hardware Serial port
// MIDI_CREATE_DEFAULT_INSTANCE();
MIDI_CREATE_INSTANCE(SoftwareSerial, mySerial, MIDI);

void setup() {
  mySerial.begin(9600, SWSERIAL_8N1, swrxPin, swtxPin , false, 256);
  MIDI.begin();
//   Serial.begin(115200, SERIAL_8N1, 16, 17);// Grove
  // MIDI_CREATE_INSTANCE(SoftwareSerial, Serial2, midiInput);
  // softSerial.begin(9600, SWSERIAL_8N1, 16, 17, false, 256);
  // midiInput.begin(MIDI_CHANNEL_OMNI);  // Listen to all incoming messages
}

void loop() {
  if(mySerial.available()){
     MIDI.sendNoteOn(42,127,1);  // ノートオン(pitch 42, velo 127 on channel 1)
  }
//   MIDI.sendNoteOn(42,127,1);  // ノートオン(pitch 42, velo 127 on channel 1)
//   delay(1000);                // 1秒待機
//   MIDI.sendNoteOff(42,0,1);   // ノートオフ
//   delay(1000);                // 1秒待機
    // Send note 42 with velocity 127 on channel 1
//    midiInput.sendNoteOn(42, 127, 1);

    // Read incoming messages
//    midiInput.read();
}
