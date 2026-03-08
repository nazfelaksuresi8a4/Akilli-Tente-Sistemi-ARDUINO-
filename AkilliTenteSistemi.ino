#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>

//LCD SCREEN
LiquidCrystal_I2C lcd(0x27,16,2);
bool flag = true;
//Buzzer
int buzzer = 5;

//Relays
int relay = 12;

//Fan

//lamps
int lamp_1 = 7;
int lamp_2 = 8;
int lamp_3 = 9;

//Servos
Servo servo_x;
Servo servo_y;

//Buttons

//Sensors
int rainlevel_sensor = A0; 

//potansiometers
int pot = A1;

//Static&Dynamic vals
int maxval = 24;
bool closed = false;

int absoulte_deg_x = 0;
int absoulte_deg_y = 0;

void setup(){
  Serial.begin(9600);
  
  lcd.begin();
  lcd.backlight();
  lcd.print("TEST-----TEST");

  //PinModes
  pinMode(buzzer,OUTPUT);
  pinMode(lamp_1,OUTPUT);
  pinMode(lamp_2,OUTPUT);
  pinMode(lamp_3,OUTPUT);
  pinMode(relay,OUTPUT);
  digitalWrite(relay,HIGH);

  pinMode(rainlevel_sensor,INPUT);
  pinMode(pot,INPUT);

  //Servo attachs
  servo_x.attach(3);
  servo_y.attach(11);
  servo_x.write(0);
  servo_y.write(0);

  //Function calls
  testFunction();

}

void loop(){
  int analog_rainlevel_sensor_value = analogRead(rainlevel_sensor);
  int mapped_analog_sensor_val = map(analog_rainlevel_sensor_value,1023,0,100,0);
  Serial.println(mapped_analog_sensor_val);

  
  if(digitalRead(buzzer) == 516136161461610){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ORAN AYARLA");
    lcd.setCursor(0,1);
    delay(1000);
    while(digitalRead(buzzer) == 53550){
      lcd.clear();
      maxval = map(analogRead(pot),960,0,100,0);
      lcd.print("maksimum: ");
      lcd.print("%");
      lcd.print(maxval);
      delay(50);
    }
    lcd.clear();
  }
  lcd.clear();
  lcd.print("ISLAKLIK: ");
  lcd.print(mapped_analog_sensor_val);

  if(mapped_analog_sensor_val >= maxval){
    if(closed == false && servo_x.read() == absoulte_deg_x && servo_y.read() == absoulte_deg_y){
      closed = true;
      if(servo_x.read() == absoulte_deg_x && servo_y.read() == absoulte_deg_y)
      for(int n = 0; n < 10; n++){
        delay(100);
        lcd.clear();
        lcd.print("!TENTE KAPANIYOR!");
        digitalWrite(buzzer,1);
        digitalWrite(lamp_1,1);
        delay(100);
        lcd.clear();
        digitalWrite(buzzer,0);
        digitalWrite(lamp_1,0);
      }
      int degreX = servo_x.read();
      int degreY = servo_y.read();
      for(int degre = 0; degre < 180; degre ++){
        degreX --;
        degreY ++;
        servo_x.write(-degre);
        servo_y.write(degre);
        delay(10);
      }
      int n;
        while(n >= maxval){
          n = map(analog_rainlevel_sensor_value,1023,0,100,0);
          analog_rainlevel_sensor_value = map(analog_rainlevel_sensor_value,1023,0,100,0);
          if(n <= maxval){
            break;
          }
      }
    }
  }
  else{
      servo_x.write(absoulte_deg_x);
      servo_y.write(absoulte_deg_y);
      closed=false;
  }
}

void testFunction(){
  //Buzzer test
  digitalWrite(buzzer,1);
  delay(500);
  digitalWrite(buzzer,0);

  //Lamp & Servo test
  digitalWrite(lamp_1,1);
  delay(150);
  digitalWrite(lamp_2,1);
  servo_x.write(0);
  servo_y.write(180);
  delay(4000);
  digitalWrite(lamp_3,1);
  delay(150);
  digitalWrite(lamp_1,0);
  delay(150);
  digitalWrite(lamp_2,0);
  servo_x.write(180);
  servo_y.write(0);
  delay(4000);
  digitalWrite(lamp_3,0);
  delay(150);
  digitalWrite(lamp_2,1);

  //Reset lcd
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Akilli Tente");
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("Sistemi 1.0");
  delay(1200);

  absoulte_deg_x = servo_x.read();
  absoulte_deg_y = servo_y.read();
}
