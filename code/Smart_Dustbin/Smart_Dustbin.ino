#include <Servo.h>
Servo myServo;

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define echoPin 2
#define trigPin 3

const int led =13;
long duration;
long distance;

void setup(){
  myServo.attach(7);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led,OUTPUT);
  Serial.begin(115200);

}

void loop(){
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  digitalWrite(trigPin,LOW);
  delay(2);

  digitalWrite(trigPin,HIGH);
  delay(10);
  digitalWrite(trigPin,LOW);

  duration = pulseIn(echoPin,HIGH);

  distance = duration*0.034/2;
  if (distance<=10){
  digitalWrite(led,HIGH);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(25, 20);
  display.println("Dustbin");
  display.display();
  display.setCursor(25,40);
  display.println("Opened");
  display.display();
  
  
  delay(100);
  display.clearDisplay();
    
    myServo.write(40);
    delay(2000);

  }
  else{
    digitalWrite(led,LOW); 
    display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(25, 20);
  display.println("Dustbin");
  display.display();
  display.setCursor(25,40);
  display.println("Closed");
  display.display();
    myServo.write(0);
    delay(200);
  }
  Serial.print("Distance:");
  Serial.println(distance);
}
