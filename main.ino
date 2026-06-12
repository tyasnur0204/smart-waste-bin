#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h> 
 
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
Servo servoTahap1; 
Servo servoTahap2; 
 
const int pinMetal = 2;       
const int pinMoisture = A0;   
const int pinServo1 = 9;  
const int pinServo2 = 10;   
const int pinTombol = 3;      
 
int batasKosong = 1000; 
int batasBasah = 300;   
 
const int s1_Standby = 80;   
const int s1_Logam = 125;      
const int s1_NonLogam = 35; 
 
const int s2_Standby = 100;   
const int s2_Kering = 55;     
const int s2_Basah = 145;    
 
int statusSekarang = 0;   
int statusSebelumnya = -1; 
 
void setup() {
  Serial.begin(9600);
  
  pinMode(pinMetal, INPUT);
  pinMode(pinTombol, INPUT_PULLUP); 
  
  servoTahap1.attach(pinServo1);
  servoTahap2.attach(pinServo2);
  
  servoTahap1.write(s1_Standby); 
  servoTahap2.write(s2_Standby);    
  
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("Sistem 2 Tahap");
  lcd.setCursor(0, 1);
  lcd.print("Siap Digunakan!");
  delay(3000);
  lcd.clear();
}
 
void loop() {
  int nilaiMetal = digitalRead(pinMetal); 
  int nilaiMoisture = analogRead(pinMoisture);
  bool tombolDitekan = (digitalRead(pinTombol) == LOW); 
 
  if (nilaiMetal == LOW) {
    statusSekarang = 1; 
  } 
  else if (nilaiMoisture < batasKosong) { 
    if (nilaiMoisture < batasBasah) {
      statusSekarang = 3; 
    } else {
      statusSekarang = 2; 
    }
  } 
  else {
    statusSekarang = 0; 
  }
 
  if (statusSekarang != statusSebelumnya) {
    lcd.clear();
    
    if (statusSekarang == 0) {
      lcd.setCursor(0, 0);
      lcd.print("Menunggu Sampah.");
      lcd.setCursor(0, 1);
      lcd.print("Status: Kosong");
    } 
    else if (statusSekarang == 1) {
      lcd.setCursor(0, 0);
      lcd.print("Deteksi: LOGAM");
      lcd.setCursor(0, 1);
      lcd.print("Tekan Tombol ->");
    } 
    else if (statusSekarang == 2) {
      lcd.setCursor(0, 0);
      lcd.print("Deteksi: KERING");
      lcd.setCursor(0, 1);
      lcd.print("Tekan Tombol ->");
    } 
    else if (statusSekarang == 3) {
      lcd.setCursor(0, 0);
      lcd.print("Deteksi: BASAH");
      lcd.setCursor(0, 1);
      lcd.print("Tekan Tombol ->");
    }
    
    statusSebelumnya = statusSekarang; 
  }
 
  if (statusSekarang != 0 && tombolDitekan) {
    if (statusSekarang == 1) {
      eksekusiLogam();
    } else if (statusSekarang == 2) {
      eksekusiNonLogam("KERING", s2_Kering, false); 
    } else if (statusSekarang == 3) {
      eksekusiNonLogam("BASAH", s2_Basah, false);  
    }
    
    statusSebelumnya = -1; 
  }
  
  delay(100); 
}
 
void eksekusiLogam() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Membuang: LOGAM");
  
  servoTahap1.write(s1_Logam);
  
  while (digitalRead(pinMetal) == LOW) {
    delay(100);
  }
  
  delay(1500); 
  
  servoTahap1.write(s1_Standby); 
  lcd.clear();
}
 
void eksekusiNonLogam(String jenis, int sudutTahap2, bool tahanPakaiSensor) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Membuang: ");
  lcd.print(jenis);
 
  servoTahap1.write(s1_NonLogam);
  delay(1500); 
  
  servoTahap1.write(s1_Standby); 
  delay(500); 
  
  servoTahap2.write(sudutTahap2);
 
  if (tahanPakaiSensor == true) {
    while (analogRead(pinMoisture) < batasKosong) {
      delay(100);
    }
    delay(1500); 
  } else {
    delay(2500); 
  }
 
  servoTahap2.write(s2_Standby);
  lcd.clear();
}
