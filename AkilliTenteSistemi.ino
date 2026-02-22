#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>

//LCD SCREEN
LiquidCrystal_I2C lcd(0x27,16,2);

//Buzzer
int buzzer = 5;

//lamps
int lamp_1 = 7;
int lamp_2 = 8;
int lamp_3 = 9;

//Servos
Servo servo_x;
Servo servo_y;

//Buttons
int button = 11;

//Sensors
int rainlevel_sensor = A0; 

//potansiometers
int pot = A1;

//Static&Dynamic vals
int maxval = 55;
bool closed = false;

int absoulte_deg_x = 0;
int absoulte_deg_y = 0;

void setup(){
  Serial.begin(9600);
  
  lcd.begin();
  lcd.print("TEST-----TEST");

  //PinModes
  pinMode(buzzer,OUTPUT);
  pinMode(lamp_1,OUTPUT);
  pinMode(lamp_2,OUTPUT);
  pinMode(lamp_3,OUTPUT);
  pinMode(rainlevel_sensor,INPUT);
  pinMode(pot,INPUT);
  pinMode(button,INPUT_PULLUP);

  //Servo attachs
  servo_x.attach(3);
  servo_x.attach(10);
  servo_x.write(0);
  servo_y.write(0);

  //Function calls
  testFunction();

}

void loop(){
  int analog_rainlevel_sensor_value = analogRead(rainlevel_sensor);
  int mapped_analog_sensor_val = map(analog_rainlevel_sensor_value,1023,0,100,0);
  Serial.println(digitalRead(button));
  
  if(digitalRead(button) == 0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ORAN AYARLA");
    lcd.setCursor(0,1);
    delay(1000);
    while(digitalRead(button) == 1){
      lcd.clear();
      maxval = map(analogRead(pot),960,0,100,0);
      lcd.print("maksimum: ");
      lcd.print("%");
      lcd.print(maxval);
      delay(50);
    }
    lcd.clear();
  }

  if(mapped_analog_sensor_val >= maxval){
    if(closed == false){
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
      for(int degre = 0; degre < 90; degre ++){
        servo_x.write(degre);
        servo_y.write(-degre);
        delay(50);
      }
    }
  }
  else{
    if(closed == true){
      
      for(int tx = 20; tx > 0; tx--){
        if(mapped_analog_sensor_val >= maxval){
          closed = "0xf";
          break;
        } 
        lcd.setCursor(0,0);
        lcd.print(tx);
        lcd.print(" Saniye sonra");
        lcd.setCursor(0,1);
        lcd.print("Tente acilacak"); 
        delay(1000);
      }

      if(closed == "0xf"){
        while(1){

        }
      }
      else{
        servo_x.write(absoulte_deg_x);
        servo_y.write(absoulte_deg_y);
        lcd.clear();
        closed = false;
      }

    }
    else{
      lcd.clear();
      lcd.print("islaklik: ");
      lcd.print(" %");
      lcd.print(mapped_analog_sensor_val);
      delay(50);
    }
    
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
  servo_x.write(90);
  servo_y.write(-90);
  delay(4000);
  digitalWrite(lamp_3,1);
  delay(150);
  digitalWrite(lamp_1,0);
  delay(150);
  digitalWrite(lamp_2,0);
  servo_x.write(0);
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
