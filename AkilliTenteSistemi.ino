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
 int analog_value = analogRead(rainlevel_sensor);
 int mapped_value = map(analog_value,0,250,0,1);
 Serial.println(mapped_value);

  if(mapped_value < 1){
    digitalWrite(led_blue,LOW);
    digitalWrite(led_red,HIGH);
  }

  else if(mapped_value > 0){
    digitalWrite(led_red,LOW);
    digitalWrite(led_blue,HIGH);
  }

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
