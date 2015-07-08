  /////////////////////////////////////////////
  //
  // Fuel Pump Relay by B Levene
  // Designed to replicate Fuel Pump Relay functionality for Mercedes-Benz w126 and possibly other models
  // July 2015
  // Version: BUILD
  // GitHub: https://github.com/byronlevene/UniversalFPV/
  // Contact: byron.levene@gmail.com
  // 
  /////////////////////////////////////////////
  
// Libraries
  #include <LiquidCrystal.h> // Comment out display for now
  #include <EEPROM.h>

// Globals

// Send to EPROM
// revLimit
// VersionControl: gitRepoName, gitVersoinControl

boolean isPowered = false;

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

// Set Global Constants

  const boolean isSetupSaved = false;

  // Software Details
    const char* developerName = "B Levene";
    const char* gitRepoName = "UniversalFPV";
    const char* gitVersionControl = "https://github.com/byronlevene/UniversalFPV/";


  // Car Details  
    const boolean isEZL = false;
    const int numberCyl[] = {4, 6, 8};
    const char* engineCode[] = {"110", "102", "103", "104", "116", "117"};


// Set default pin values in volts unless specified
// Find defaults...

    int boxPinDefault01 = 0;
    int boxPinDefault02 = 0;
    int boxPinDefault03 = 0;
    int boxPinDefault04 = 0;
    int boxPinDefault05 = 0;
    int boxPinDefault06 = 0;
    int boxPinDefault07 = 0; // 
    int boxPinDefault08 = 12; // volts
    int boxPinDefault09 = 0;
    int boxPinDefault10 = 420; // Millisecond pulse
    int boxPinDefault11 = 0;
    int boxPinDefault12 = 0; // EZL Only

// Define Digital Pins (numbers made up, check with board)

  // INPUT pins
    int boxPin01 = 1;
    int boxPin02 = 2;
    int boxPin03 = 3;
    int boxPin04 = 4;
    int boxPin05 = 5;
    int boxPin06 = 6;
    int boxPin07 = 7; 
    int boxPin08 = 8;
    int boxPin09 = 9;
    int boxPin10 = 10;
    int boxPin11 = 11;
    int boxPin12 = 12; 

  //OUTPUT pins
    int powerLED = 13;
    int warmUpLED = 14;
    int idleLED = 15;
    int revLimitLED = 16;
    int tooHotLED = 17;

  // Other Globals
    int currentRPM = 0;
    int revLimit = 6000;

void setup() {

// Defines digital pin type

// INPUT
pinMode(boxPin01, INPUT);
pinMode(boxPin02, INPUT); // O2
pinMode(boxPin03, INPUT);
pinMode(boxPin04, INPUT);
pinMode(boxPin05, INPUT);
pinMode(boxPin06, INPUT);
pinMode(boxPin07, INPUT); // is output?
pinMode(boxPin08, INPUT);
pinMode(boxPin09, INPUT);
pinMode(boxPin10, INPUT);
pinMode(boxPin11, INPUT);
pinMode(boxPin12, INPUT);

// OUTPUT
pinMode(powerLED, OUTPUT);
pinMode(warmUpLED, OUTPUT);
pinMode(tooHotLED, OUTPUT);
pinMode(idleLED, OUTPUT);
pinMode(revLimitLED, OUTPUT);

// Name the pins in the fuse box

const char* boxPinName01 = "BoxPin01";
const char* boxPinName02 = "Temprature Input";
const char* boxPinName03 = "BoxPin03";
const char* boxPinName04 = "Cold Start Valve";
const char* boxPinName05 = "BoxPin05";
const char* boxPinName06 = "Kickdown01";
const char* boxPinName07 = "Pump control"; // Jump with BoxPin08 to activate fuel pump
const char* boxPinName08 = "ALWAYS HOT"; // listed as "ground" on EZL circut diagram
const char* boxPinName09 = "Kickdown02";
const char* boxPinName10 = "Idle Resonance Input";
const char* boxPinName11 = "GROUND";
const char* boxPinName12 = "Crank Input"; // EZL Only

// Other default variables for setup...

// END SETUP
}


// THE LOOP



void loop() {
  // put your main code here, to run repeatedly:

  // Power
    if (digitalRead(boxPin08) == HIGH){
      isPowered = !isPowered;
      digitalWrite(powerLED, HIGH);
    //  lcd.display();
    //  lcd.print("FPR by", developerName);
    }
    else {
      digitalWrite(powerLED, LOW);
    }

  // Calaberate voltage
    int voltageDifference = 0;
      if (digitalRead(boxPin08) <= boxPinDefault08){
        voltageDifference == -(boxPinDefault08 - boxPin08);
      //  lcd.print("Voltage Low");
      }
      
      if (digitalRead(boxPin08) >= boxPinDefault08){
        voltageDifference == +(boxPinDefault08 - boxPin08);
      //  lcd.print("Voltage High");
      }

// Idle
currentRPM = digitalRead(boxPin10);
  int idleRPM = 650;
    if (currentRPM < idleRPM) {
      currentRPM = 650;
      digitalWrite(idleLED, HIGH);
    //  lcd.print("Idle");
    }
    else {
      digitalWrite(idleLED, LOW);
    //  lcd.print(currentRPM);
    }
    
// Rev Limiter

if (currentRPM > 6000) {
  currentRPM = 6000;
  digitalWrite(revLimitLED, HIGH);
//  lcd.print("High RPM");
}

// Warm Up Regulator
  int currentTemp = boxPin02; // formula to convert pin signal to Celcius
    if (currentTemp < 40) {
      digitalWrite(warmUpLED, HIGH);
    }
    if (currentTemp > 140) {
      digitalWrite(tooHotLED, HIGH);
    //  lcd.print("Engine Hot");
    }
    else {
      digitalWrite(tooHotLED, LOW);
      digitalWrite(warmUpLED, LOW);
    //  lcd.print("Engine Temp", currentTemp);
    }


// Air Con adjustment


}
