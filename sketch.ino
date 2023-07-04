
#include <LedControl.h>
// Atur pin hc-sr04
#define ECHO_PIN 2
#define TRIG_PIN 3
// Atur pin display sesuai dengan koneksi
const int DIN_PIN = 11;
const int CS_PIN = 10;
const int CLK_PIN = 13;


// Inisialisasi objek LedControl
LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);
// Read Jarak

// Data untuk emote senyum dengan mata terbuka
byte senyumEyeOpen[8] = {
  B00000000,
  B00100110,
  B01000110,
  B01000000,
  B01000000,
  B01000110,
  B00100110,
  B00000000
};

// Data untuk emote senyum dengan mata tertutup
byte senyumEyeClose[8] = {
    B00000000,
    B00100100,
    B01000100,
    B01000000,
    B01000000,
    B01000100,
    B00100100,
    B00000000
};

// Data untuk emote marah dengan mata tertutup
byte marahEyeOpen[8] = {
  B00000000,
  B10000110,
  B01000110,
  B01000000,
  B01000000,
  B01000110,
  B10000110,
  B00000000
};

// Data untuk emote marah dengan mata tertutup
byte marahEyeClose[8] = {
  B00000000,
  B10000100,
  B01000100,
  B01000000,
  B01000000,
  B01000100,
  B10000100,
  B00000000
};

byte datarEyeOpen[8] = {
  B00000000,
  B01000110,
  B01000110,
  B01000000,
  B01000000,
  B01000110,
  B01000110,
  B00000000
};

// Data untuk emote marah dengan mata tertutup
byte datarEyeClose[8] = {
  B00000000,
  B00000100,
  B00000100,
  B01110000,
  B01010000,
  B01110100,
  B00000100,
  B00000000
};
void senyum(){
  // Tampilkan emote senyum mata terbuka pada matriks LED
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, senyumEyeOpen[row]);
  }

  delay(200);  // Jeda 0.2 detik
 // lc.clearDisplay(0); 
 // Tampilkan emote senyum mata tertutup pada matriks LED
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, senyumEyeClose[row]);
  }
  delay(150); // Jeda 0.15 detik
}
void datar(){
  // Tampilkan emote marah mata terbuka pada matriks LED
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, datarEyeOpen[row]);
  }

  delay(200);  // Jeda 0.2 detik
 // lc.clearDisplay(0); 
 // Tampilkan emote marah mata tertutup pada matriks LED
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, datarEyeClose[row]);
  }
  delay(150); // Jeda 0.15 detik
}
void marah(){
  // Tampilkan emote marah mata terbuka pada matriks LED
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, datarEyeOpen[row]);
  }

  delay(200);  // Jeda 0.2 detik
 // lc.clearDisplay(0); 
 // Tampilkan emote marah mata tertutup pada matriks LED
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, marahEyeClose[row]);
  }
  delay(150); // Jeda 0.15 detik
}
void setup() {
  lc.shutdown(0, false);  // Aktifkan chip
  lc.setIntensity(0, 0); // Atur intensitas cahaya matriks (0-15)
  lc.clearDisplay(0);    // Hapus tampilan matriks
  Serial.begin(115200); // port serial
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}
float bacaJarakCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}
void loop() {
 float jarak = bacaJarakCM();

  if(jarak < 50){
  marah();
  }else if(jarak > 50 && jarak < 80){
  datar();
  }
  else{
  senyum();
  }

  Serial.print("Jarak benda Didepan: ");
  Serial.println(bacaJarakCM());

  delay(100);
}
