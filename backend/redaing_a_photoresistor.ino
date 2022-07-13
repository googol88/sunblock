/*
  SparkFun Inventor's Kit
  Example sketch 07

  PHOTORESISTOR

  Read a photoresistor (light sensor) to detect "darkness" and turn on an LED when it
  is "dark" and turn back off again when it is "bright.

  This sketch was written by SparkFun Electronics,
  with lots of help from the Arduino community.
  This code is completely free for any use.
  Visit http://learn.sparkfun.com/products/2 for SIK information.
  Visit http://www.arduino.cc to learn about the Arduino.
*/


// As usual, we'll create constants to name the pins we're using.
// This will make it easier to follow the code below.
aREST rest = aREST();

const int sensorPin = 0;
const int ledPin = 9;

// We'll also set up some global variables for the light level a calibration value and
//and a raw light value
int lightCal;
int lightVal;
bool automatic = true;


void setup()
{
  // We'll set up the LED pin to be an output.
  pinMode(ledPin, OUTPUT);
  lightCal = analogRead(sensorPin);
  //we will take a single reading from the light sensor and store it in the lightCal
  //variable. This will give us a prelinary value to compare against in the loop
  Serial.begin(115200);
  // Register RGB function

  rest.function("mode", setLight);
  Serial.println("Try DHCP...");
  if (Ethernet.begin(macAdd) == 0) {
    Serial.println("DHCP FAIL...Static IP");
    Ethernet.begin(macAdd , ip, myDns, myGateway) ;
  }
  server.begin();
  Serial.print("server IP: ");
  Serial.println(Ethernet.localIP());
  pixels.begin();
  Serial.println("Setup complete.\n");
}

int setLight(String mode) {
  Serial.println("Mode: " + mode);
  automatic = false;
  if (mode == "on") {
    digitalWrite(9, HIGH);
  } else {
    digitalWrite(9, LOW);
  }
  // set single pixel color
  return 1;
}

void loop()
{
  //Take a reading using analogRead() on sensor pin and store it in lightVal
  lightVal = analogRead(sensorPin);
  rest.handle(client);

  //if lightVal is less than our initial reading (lightCal) minus 50 it is dark and
  //turn pin 9 HIGH. The (-50) part of the statement sets the sensitivity. The smaller
  //the number the more sensitive the circuit will be to variances in light.
  if (automatic == true) {
    if (lightVal < lightCal - 50)
    {
      digitalWrite(9, HIGH);
    }

    //else, it is bright, turn pin 9 LOW
    else
    {
      digitalWrite(9, LOW);
    }
  }
}
