#include <Servo.h>
#include <LiquidCrystal.h>

//ledler
int led_red = 2;
int led_blue = 4;

//Sensörler
int rainlevel_sensor = A0;

//Butonlar
int btn_mod1 = 7;
int btn_mod2 = 8;

//Durum değişkenleri
int terim = 255;
int sayac = 0;
int kontrol_edildi = 0;

//Motorlar
Servo x_servo;
Servo y_servo;

void setup(){
  Serial.begin(9600);

  //Ledlerin pin modları
  pinMode(led_red,OUTPUT);
  pinMode(led_blue,OUTPUT);

  //Butonların pin modları
  pinMode(btn_mod1,INPUT_PULLUP);
  pinMode(btn_mod2,INPUT_PULLUP);

  //Motorları ata
  x_servo.attach(9);
  y_servo.attach(10);

  x_servo.write(0);
  y_servo.write(0);

  x_servo.write(16);
  y_servo.write(16);

  //Test fonksiyonu başlat;
  Serial.println("Fonksiyon başlatılıyor");
  ledTestFunction();
}

void loop(){
  int analog_value = analogRead(rainlevel_sensor);
  int mapped_value = map(analog_value,0,250,0,1);

  if(mapped_value < 1){
    digitalWrite(led_blue,LOW);
    digitalWrite(led_red,HIGH);
  }
  else if(mapped_value > 0){
    digitalWrite(led_red,LOW);
    digitalWrite(led_blue,HIGH);
  }

  int btn_mod1_digital_state = digitalRead(btn_mod1);
  int btn_mod2_digital_state = digitalRead(btn_mod2);

  Serial.print("Durum-1: ");
  Serial.print(btn_mod1_digital_state);
  Serial.print("Durum-2: ");
  Serial.print(btn_mod2_digital_state);
  Serial.print("\n");

  if(btn_mod1_digital_state != 1 && btn_mod2_digital_state != 1){
    calibrate_servo();
    for(int nx = 0; nx < 2; nx ++){
      x_servo.write(60);
      y_servo.write(60);
      delay(500);
      x_servo.write(-60);
      y_servo.write(-60);
    }
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

void calibrate_servo(){
      int y_deg = y_servo.read();
      int x_deg = x_servo.read();

      y_servo.write(y_deg);
      x_servo.write(x_deg);
}
