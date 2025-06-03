String trame, text, valeurvit;
#include "Servo.h"
#include <SoftwareSerial.h>
SoftwareSerial hcSerial(6, 7);  // RX, TX
//declaration variables moteur
int vitesse = 50;
int vitessemot;
//broche du shield motor
int directionPin = 12;
int pwmPin = 3;
int brakePin = 9;
int directionPin2 = 13;
int pwmPin2 = 11;
int brakePin2 = 8;
Servo servo;

void traitement() {
  if (trame.startsWith("o")) {
    text = trame;
  } else {
    valeurvit = trame;
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  // hardware serial for the USB-PC
  hcSerial.begin(9600);
  //define pins motor shield
  pinMode(directionPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(brakePin, OUTPUT);
  pinMode(directionPin2, OUTPUT);
  pinMode(pwmPin2, OUTPUT);
  pinMode(brakePin2, OUTPUT);
  servo.attach(2);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (hcSerial.available()) {
    trame = String("");
    while (hcSerial.available()) {
      trame = trame + char(hcSerial.read());
      delay(1);
    }
    traitement();
  }
  Serial.print("trame:");
  Serial.println(trame);
  Serial.println("text:" + text);
  Serial.print("vitesse:");
  Serial.println(vitesse);
  Serial.print("vitesse mot :");
  Serial.println(vitessemot);
  if (trame == "0") {
    Serial.println("rotation vitesse moyenne");
    //moteur1 & 2 avant
    digitalWrite(directionPin, HIGH);
    //release breaks
    digitalWrite(brakePin, LOW);
    //moteur à fond
    analogWrite(pwmPin, vitesse);
    trame = "54";
  }
  if (trame == "1") {
    Serial.println("augmentation");
    digitalWrite(directionPin, HIGH);
    //release breaks
    digitalWrite(brakePin, LOW);
    vitesse = vitesse + 5;
    analogWrite(pwmPin, vitesse);
    trame = "54";
  }
  if (trame == "2") {
    Serial.println("arret");
    digitalWrite(brakePin, HIGH);
    analogWrite(pwmPin, 0);
    trame = "54";
  }
  if (trame == "3") {
    Serial.println("diminution");
    digitalWrite(directionPin, HIGH);
    //release breaks
    digitalWrite(brakePin, LOW);
    vitesse = vitesse - 5;
    analogWrite(pwmPin, vitesse);
    trame = "54";
  }
    if (trame == "5") {
    Serial.println("rotation vitesse moyenne");
    //moteur1 & 2 avant
    digitalWrite(directionPin2, HIGH);
    //release breaks
    digitalWrite(brakePin2, LOW);
    //moteur à fond
    analogWrite(pwmPin2, vitesse);
    trame = "54";
    }
      if (trame == "6") {
    Serial.println("augmentation");
    digitalWrite(directionPin2, HIGH);
    //release breaks
    digitalWrite(brakePin2, LOW);
    vitesse = vitesse + 5;
    analogWrite(pwmPin2, vitesse);
    trame = "54";
      }
        if (trame == "7") {
    Serial.println("arret");
    digitalWrite(brakePin2, HIGH);
    analogWrite(pwmPin2, 0);
    trame = "54";
        }
          if (trame == "8") {
    Serial.println("diminution");
    digitalWrite(directionPin2, HIGH);
    //release breaks
    digitalWrite(brakePin2, LOW);
    vitesse = vitesse - 5;
    analogWrite(pwmPin2, vitesse);
    trame = "54";
  }
   if (trame == "10") {
    Serial.println("dix");
    digitalWrite(directionPin, HIGH);
    //release breaks
    digitalWrite(brakePin, LOW);
    vitesse = 100 ;
    analogWrite(pwmPin, vitesse);
    trame = "54";
   }
      if (trame == "11") {
    Serial.println("dix");
    digitalWrite(directionPin, HIGH);
    //release breaks
    digitalWrite(brakePin, LOW);
    vitesse = 125 ;
    analogWrite(pwmPin, vitesse);
    trame = "54";
   }
      if (trame == "12") {
    Serial.println("dix");
    digitalWrite(directionPin, HIGH);
    //release breaks
    digitalWrite(brakePin, LOW);
    vitesse = 150 ;
    analogWrite(pwmPin, vitesse);
    trame = "54";
   }
      if (trame == "13") {
    Serial.println("dix");
    digitalWrite(directionPin, HIGH);
    //release breaks
    digitalWrite(brakePin, LOW);
    vitesse = 175 ;
    analogWrite(pwmPin, vitesse);
    trame = "54";
   }
      if (trame == "14") {
    Serial.println("dix");
    digitalWrite(directionPin, HIGH);
    //release breaks
    digitalWrite(brakePin, LOW);
    vitesse = 200 ;
    analogWrite(pwmPin, vitesse);
    trame = "54";
   }
      if (trame == "15") {
    Serial.println("dix");
    digitalWrite(directionPin, HIGH);
    //release breaks
    digitalWrite(brakePin, LOW);
    vitesse = 225 ;
    analogWrite(pwmPin, vitesse);
    trame = "54";
   }
    if (trame == "20") {
      for (int i = 0; i < 15; ++i) {
      Serial.println("servo");
      servo.write(0);
      delay(5000);
      servo.write(15);
      }
      trame = "54";
    }
     if (trame == "21") {
      for (int i = 0; i < 15; ++i) {
      Serial.println("servo");
      servo.write(0);
      delay(5000);
      servo.write(30);
      }
      trame = "54";
    }
        if (trame == "22") {
          for (int i = 0; i < 15; ++i) {
      Serial.println("servo");
      servo.write(30);
      delay(5000);
      servo.write(15);
          }
      trame = "54";
    }
        if (trame == "23") {
          for (int i = 0; i < 15; ++i) {
      Serial.println("servo");
      servo.write(30);
      delay(5000);
      servo.write(0);
          }
      trame = "54";
    }
        if (trame == "24") {
      Serial.println("servo");
      servo.write(0);
      trame = "54";
    }
}
