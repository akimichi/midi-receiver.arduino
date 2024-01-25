#include <M5Unified.h>
#include <WiFi.h>
#include <esp_now.h>
#include <MIDI.h>
#include <SoftwareSerial.h>
#define swrxPin 16
#define swtxPin 17

SoftwareSerial softSerial(swrxPin,swtxPin);


// Create and bind the MIDI interface to the default hardware Serial port
// MIDI_CREATE_DEFAULT_INSTANCE();
MIDI_CREATE_INSTANCE(SoftwareSerial, softSerial, MIDI);

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *payload, int data_len) {
  Serial.print("Received Data: ");
  String msg = String((char*) payload);
  Serial.println(msg);
};

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  M5.Display.setTextSize(3);               // テキストサイズを変更

  // ESP-NOW初期化
  WiFi.mode(WIFI_STA);
  M5.Display.print("MAC Address: ");
  M5.Display.println(WiFi.macAddress());
  WiFi.disconnect();
  if(esp_now_init() != ESP_OK) {
    M5.Display.println("ESP-Now Init Failed....");
    return;
  } 
  MIDI.begin();
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  M5.update();
//    MIDI.read();
  MIDI.sendNoteOn(42,127,1);  // ノートオン(pitch 42, velo 127 on channel 1)
   delay(1000);                // 1秒待機
//   MIDI.sendNoteOff(42,0,1);   // ノートオフ
}
