
// Include Libraries
#include "Arduino.h"
#include "Buzzer.h"
#include "NewPing.h"
#include "LED.h"


// Pin Definitions
#define BUZZER_PIN_SIG	2
#define HCSR04_PIN_TRIG	4
#define HCSR04_PIN_ECHO	3
#define IRFLAME_5V_PIN_AOUT	A3
#define LED_PIN_VIN	5
#define MQ5_5V_PIN_AOUT	A1



// Global variables and defines

// object initialization
Buzzer buzzer(BUZZER_PIN_SIG);
NewPing hcsr04(HCSR04_PIN_TRIG,HCSR04_PIN_ECHO);
LED led(LED_PIN_VIN);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // Buzzer - Test Code
    // The buzzer will turn on and off for 500ms (0.5 sec)
    buzzer.on();       // 1. turns on
    delay(500);             // 2. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    buzzer.off();      // 3. turns off.
    delay(500);             // 4. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }
    else if(menuOption == '2') {
    // Ultrasonic Sensor - HC-SR04 - Test Code
    // Read distance measurment from UltraSonic sensor           
    int hcsr04Dist = hcsr04.ping_cm();
    delay(10);
    Serial.print(F("Distance: ")); Serial.print(hcsr04Dist); Serial.println(F("[cm]"));

    }
    else if(menuOption == '3')
    {
    // Disclaimer: The Infrared Flame Detection Sensor is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '4') {
    // Basic Ultraviolet LED 5mm - Test Code
    // The LED will turn on and fade till it is off
    for(int i=255 ; i> 0 ; i -= 5)
    {
    led.dim(i);                      // 1. Dim Led 
    delay(15);                               // 2. waits 5 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }                                          
    led.off();                        // 3. turns off
    }
    else if(menuOption == '5')
    {
    // Disclaimer: The LPG, Natural and Coal Gas Sensor - MQ-5 is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) Buzzer"));
    Serial.println(F("(2) Ultrasonic Sensor - HC-SR04"));
    Serial.println(F("(3) Infrared Flame Detection Sensor"));
    Serial.println(F("(4) Basic Ultraviolet LED 5mm"));
    Serial.println(F("(5) LPG, Natural and Coal Gas Sensor - MQ-5"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing Buzzer"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing Ultrasonic Sensor - HC-SR04"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing Infrared Flame Detection Sensor - note that this component doesn't have a test code"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing Basic Ultraviolet LED 5mm"));
    		else if(c == '5') 
    			Serial.println(F("Now Testing LPG, Natural and Coal Gas Sensor - MQ-5 - note that this component doesn't have a test code"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}
