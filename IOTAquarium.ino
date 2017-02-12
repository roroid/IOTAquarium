/***************  IOTAquarium   *********************** 
  This is a project to help you manage your fish tank. Folowing functions are currently implemented:
      -fish feed
      -empty food tank allert
      -water temperature monitoring
      -light controler(using 5v neopixel)

Used pins:
28BYJ-48 motor/ULN2003A (IN1,IN2,IN3,IN4) <-> Smart7688 DUO(13,12,11,10)
DS18B20 (red,yellow,gray) <-> Smart7688 DUO(5V,D3,GND)+4,7k betwen 5V and DATA
LDR (VCC,data) <-> Smart7688 DUO(5V,A5)+10k betwen GND and DATA
 ******************************************************/ 

//******  Steper library   
//include stepper library for moving the feeder
#include <AccelStepper.h>
#define HALFSTEP 8

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper feeder(HALFSTEP, 13, 12, 11, 10);

//******  LDR   
int ldrPin=A5;//pin on wich is connected the LDR
int ldrValue=0;//initial value for the LDR value

//****** Temperature
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 3// Data wire is plugged into pin 2 on the Arduino
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600); //sets serial port for communication

  //Initialize the stepper motor. I prefer to start slowly so the food don't get trow all at once
  feeder.setSpeed(1000.0);
  feeder.setAcceleration(200.0);
  feeder.setSpeed(800);


    // Start up the library
  sensors.begin();
}

void loop() {
ldrValue = analogRead(ldrPin); // read the value from the sensor
Serial.println(ldrValue); //prints the values coming from the sensor on the screen
sensors.requestTemperatures(); // Send the command to get temperatures
Serial.println(sensors.getTempCByIndex(0)); // Why "byIndex"? 
delay(1000);
}




  /*//Change direction when the stepper reaches the target position
  if (stepper1.distanceToGo() == 0) {
    stepper1.moveTo(-stepper1.currentPosition());
  }
  stepper1.run();*/
