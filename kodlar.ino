#include<Keypad.h>  // Keypad kütüphanesi
#include <LiquidCrystal.h> // LCD kütüphanesi
#include<Servo.h> // Servo motor kütüphanesi

Servo servo; // Servo motor nesnesi

#define yled 5   // Yeşil LED pin numarası
#define kled 6   // Kırmızı LED pin numarası
#define buzzer 4 // Buzzer pin numarası

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
// LCD ekran bağlantıları LiquidCrystal(rs, enable, d4, d5, d6, d7)
// ( vss:GND ,VDD:+5V,VO:POT ,RW:GND,A:+5V,K:GND)

const byte satir = 4;  // Satır sayısı
const byte sutun = 4;  // Sütun sayısı

// Varsayılan şifre, isteğe bağlı değiştirilebilir
char sifre[4] = {'1', '2', '3', '4'}; 

char sifre1[4];  // Tuş takımından girilen şifre
char tus;   // Tuş değeri 
int i = 0;  // İndeks değeri
char tus_takimi[4][4] = {  // Tuş takımı düzeni
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte satir_pins[4] = {A0, A1, A2, A3};  // Satır pin bağlantıları
byte sutun_pins[4] = {A4, A5, 3, 2};    // Sütun pin bağlantıları

Keypad tuss_takimi = Keypad(makeKeymap(tus_takimi), satir_pins, sutun_pins, 4, 4);  // Tuş takımı nesnesi

// LCD ekran için özel karakterler
byte customChar9[8] = {  
  0b11111, 
  0b11111,
  0b11111,   
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
byte customChar8[8] = {
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110
};
byte customChar7[8] = {
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100
};
byte customChar6[8] = {
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000
};
byte customChar5[8] = {
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000
};
byte customChar4[8] = {
  0b00001,
  0b00011,
  0b00011,
  0b00111,
  0b00111,
  0b01111,
  0b01111,
  0b11111
};
byte customChar3[8] = {
  0b00000,
  0b00010,
  0b00010,
  0b00110,
  0b00110,
  0b01110,
  0b01110,
  0b11110
};
byte customChar2[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00100,
  0b00100,
  0b01100,
  0b01100,
  0b11100
};
byte customChar1[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b01000,
  0b01000,
  0b11000
};

byte customChar0[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10000
};

void setup() {
  
  servo.attach(13); // Servo motor pinine bağlanıyor
  pinMode(yled, OUTPUT);  // Yeşil LED pininin çıkış olarak belirlenmesi
  pinMode(buzzer, OUTPUT); // Buzzer pininin çıkış olarak belirlenmesi
  pinMode(kled, OUTPUT); // Kırmızı LED pininin çıkış olarak belirlenmesi
  lcd.createChar(0, customChar0); // Özel karakterlerin oluşturulması
  lcd.createChar(1, customChar1);
  lcd.createChar(2, customChar2);
  lcd.createChar(3, customChar3);
  lcd.createChar(4, customChar4);
  lcd.createChar(5, customChar5);
  lcd.createChar(6, customChar6);
  lcd.createChar(7, customChar7);
  lcd.createChar(8, customChar8);
  lcd.createChar(9, customChar9);
  lcd.begin(16, 2); // LCD başlatılıyor
  lcd.clear();  // Ekran temizleniyor
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Sistem Aciliyor"); // Başlangıç mesajı
  for (int i = 1; i <= 13; i++)  // Yükleniyor animasyonu oluşturuluyor
  {
    for (int k = 6; k <= 9; k++)
    {
      lcd.setCursor(i, 1); lcd.write((uint8_t)k);
      delay(100);
    }
  }
  lcd.clear(); // Ekran temizleniyor
  lcd.setCursor(0, 0); 
  lcd.print("Arduino");
  lcd.setCursor(0, 1);
  lcd.print("*SIFRELI KAPI*");   // Kilitli kapı sistemi başlığı
  delay(2000);
  lcd.clear();  
  lcd.setCursor(0, 0); 
  lcd.print("SIFREYI GIRINIZ:");    // Şifre giriniz mesajı
  Serial.begin(9600);
  Serial.println("Hos geldiniz");   // Hoş geldiniz mesajı
  Serial.println("Sifreyi giriniz");  
}

void loop() {
  servo.write(0); // Servo motor pozisyonu sıfırlanıyor
  digitalWrite(kled,LOW); // Kırmızı LED pasif hale getiriliyor
  digitalWrite(yled,LOW); // Yeşil LED pasif hale getiriliyor
  tus = tuss_takimi.getKey();  // Tuş takımından bir tuşa basılıp basılmadığı kontrol ediliyor

  if (tus)   // Eğer bir tuşa basıldıysa
  {
    sifre1[i++] = tus;  // Tuş takımından alınan değer şifre1 dizisine ekleniyor
    lcd.setCursor(i, 1); 
    lcd.print("*");   // Şifrenin ekrana yıldız (*) olarak basılması
    digitalWrite(buzzer,HIGH); // Buzzer aktive ediliyor
    delay(100);
    digitalWrite(buzzer,LOW); // Buzzer kapatılıyor
  }

  if (i == 4)
  { 
    delay(200);
    char sifre[4] = {'0', '0', '0', '0'}; // Şifre değiştirme bölümü
  
    if ((strncmp(sifre1, sifre, 4) == 0))   // Girilen şifre kontrol ediliyor
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      servo.write(90);
      lcd.print("SIFRE DOGRU!"); // Şifrenin doğru olduğu mesajı
      digitalWrite(yled, HIGH); // Yeşil LED aktive ediliyor
      digitalWrite(kled, LOW); // Kırmızı LED pasif hale getiriliyor
      digitalWrite(buzzer, HIGH); // Buzzer aktive ediliyor
      delay(100);
      digitalWrite(buzzer, LOW); // Buzzer kapatılıyor
      delay(100);
      digitalWrite(buzzer, HIGH); // Buzzer aktive ediliyor
      delay(100);
      digitalWrite(buzzer, LOW); // Buzzer kapatılıyor
      delay(1000); // 1 saniye bekleme
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("SIFREYI GIRINIZ");  // Şifre giriniz mesajı 
      i = 0; // İndis sıfırlanıyor
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("SIFRE YANLIS!!!");  // Yanlış şifre mesajı
      digitalWrite(yled, LOW); // Yeşil LED pasif hale getiriliyor
      digitalWrite(kled, HIGH); // Kırmızı LED aktive ediliyor
      digitalWrite(buzzer, HIGH); // Buzzer aktive ediliyor
      delay(1000); // 1 saniye bekleme
      digitalWrite(buzzer, LOW); // Buzzer kapatılıyor
      delay(1000); // 1 saniye bekleme
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("SIFREYI GIRINIZ"); // Şifre giriniz mesajı
      i = 0; // İndis sıfırlanıyor
    }
  }
}