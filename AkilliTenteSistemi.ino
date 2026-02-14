#include <Servo.h>
#include <LiquidCrystal.h>

//ledler
int led_red = 2;
int led_blue = 4;

//Sensörler
int rainlevel_sensor = A0;

//Durum değişkenleri
int terim = 255;
int sayac = 0;
int kontrol_edildi = 0;

void setup(){
  Serial.begin(9600);
  pinMode(led_red,OUTPUT);
  pinMode(led_blue,OUTPUT);
  Serial.println('Fonksiyon başlatılıyor');
  ledTestFunction();
}

void loop(){
 Serial.println("01");
}

//Led Test fonksiyonu(ILK BAŞTA ÇALIŞACAK OLAN)
void ledTestFunction(){
  while(terim >= 255){
    if(sayac < 4){
      Serial.println(terim);
      digitalWrite(led_red,HIGH);
      delay(100);
      digitalWrite(led_red,LOW);
      delay(100);
      digitalWrite(led_blue,HIGH);
      delay(100);
      digitalWrite(led_blue,LOW);
      delay(100);
      Serial.println(sayac);
      
      sayac ++;
    }
    else{
      terim = -255;
      sayac = 0;
      Serial.println(terim,sayac);
      break;
      loop();
    }
  }
}
