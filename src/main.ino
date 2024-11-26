#include <M5Unified.h>
#include <WiFi.h>
#include <esp_now.h>
#include <MIDI.h>
#include <SoftwareSerial.h>
#include "common.h"
#define swrxPin 16
#define swtxPin 17

SoftwareSerial softSerial(swrxPin,swtxPin);

// Create and bind the MIDI interface to the default hardware Serial port
// MIDI_CREATE_DEFAULT_INSTANCE();
MIDI_CREATE_INSTANCE(SoftwareSerial, softSerial, MIDI);

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *payload, int data_len) {
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
      mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println();
  Serial.printf("Last Packet Recv from: %s\n", macStr);
  Serial.printf("Last Packet Recv Data(%d): ", data_len);
  for (int i = 0; i < data_len; i++) {
    Serial.print(payload[i]);
    Serial.print(" ");
  }
  switch(payload[0])      // Get the type of the message we caught
  {
    case MidiType::InvalidType: // 全音を消音する
      MIDI.sendControlChange(123,0,1);
      break;
    case MidiType::NoteOn:
      Serial.println("NoteOn");
      // payload: command chan note velocity
      MIDI.sendNoteOn(payload[2],payload[3],payload[1]);  // ノートオン(pitch 42, velo 127 on channel 1)
      break;
    case MidiType::NoteOff:
      Serial.println("NoteOff");
      MIDI.sendNoteOff(payload[2],payload[3],payload[1]);  // 
      break;
    case MidiType::ProgramChange:
      Serial.println("ProgramChange");
      MIDI.sendProgramChange(payload[2], 1);  // 
      break;
    case MidiType::PitchBend:
      Serial.println("PitchBend");
      MIDI.sendPitchBend(payload[2]*100, 1);
      break;
    case MidiType::AfterTouchChannel:
      break;
    case MidiType::AfterTouchPoly:
      break;
    case MidiType::ControlChange:
      Serial.println("ControlChange");
      MIDI.sendControlChange(payload[1], payload[3], 1);  // 
      break;
    default:
      break;
  }
  

};

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  M5.Display.setTextSize(3);               // テキストサイズを変更

  MIDI.begin();
  // ESP-NOW初期化
  M5.Display.println("MAC Address: ");
  M5.Display.println(WiFi.macAddress());
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  if(esp_now_init() != ESP_OK) {
    M5.Display.println("ESP-Now Init Failed....");
    return;
  } 
  esp_now_register_recv_cb(OnDataRecv);

  Serial.println("setup completed");
  MIDI.sendProgramChange(1, 1);  // 
}

int program_number = 1;

void loop() {
  M5.update();
}
