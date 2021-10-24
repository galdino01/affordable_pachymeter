/*
* Author: Lucas Galdino
* From: Paraná, Brazil
* Date: 24/10/2021
*
* Libraries in this project:
* 	- HCSR04 > Developed by: ejoyneering
*   - Talkie > Developed by: Joachimsmeyer
*
* Used equipments:
*	- Arduino Uno R3
*	- HCSR04 Ultrasonic Sensor
*	- 4 male/female cables
*   - 2 male/male cables
*	- 2 cables with alligator connectors on all ends
*   - Speaker with USB cable and P2 cable
*	- Some coffee...
*
* About:
*	This project is an idea to transform reading data into audio format 
*	so that people with low vision can understand what is transmitted. 
*	This code is completely open and can be modified and improved.
*	I just ask that if you are going to use it, say that the source is here. 
*	Thank you immensely.
*
* My Social Medias:
*	Github: https://github.com/galdino01
*	Linkedin: https://www.linkedin.com/in/galdino-01/
*/

// Here, we import the necessary libraries.
#include <Arduino.h>
#include <HCSR04.h>
#include <Talkie.h>
#include <Vocab_US_TI99.cpp>

// Here, we define the pins to be used by Arduino.
#define TRIGGER_PIN 6
#define ECHO_PIN 7
#define AMBIENT_TEMPERATURE 25
#define MAX_DISTANCE_IN_CM 200

// Here, we declare the initial state of the variable to be manipulated with the sensor.
float distance = 0;

// Here, we declare our objects, they are like a mold, so we define their initial states.
Talkie voice;
HCSR04 sonar(TRIGGER_PIN, ECHO_PIN, AMBIENT_TEMPERATURE, MAX_DISTANCE_IN_CM);

// Here, we declare a helper function that will be used later.
void test_value(int value);

// Here are the initial settings for the Arduino board, this block will only be executed once by the device.
void setup() {

	Serial.begin(115200); // Here, we start the serial monitor with a rate of 115200
	sonar.begin(); // Here, we start the ultrasonic sensor

}

// Here are our commands for Arduino, this block will run in a loop, until the device is turned off/restarted.
void loop() {

	distance = sonar.getDistance(); // Here, we take the distance read by the sensor

	// In this "if" section, we check if the sensor reading is within the specified limits, 
	// in this case, if the distance is greater than 99 centimeters and it is not out of range, 
	// it performs the block below.
	if (distance != HCSR04_OUT_OF_RANGE && distance > 99) {

		// In the three lines below this, we define variables to separate the digits from the 
		// distance read by the sensor, that is, if we have a reading of "153" centimeters, 
		// our code captures as if it were "1", "5", "3", with the separate digits.
		int one = distance / 100;
		int two = (distance / 10) - 10;
		int three = distance - ((one * 100) + (two * 10));

		// Here's why we need to separate the distance read by the sensor into separate numbers, 
		// the encoding that allows it to be transmitted in audio format, understanding only one 
		// number at a time, and it's in these next three lines that it happens.
		test_value(one);
		test_value(two);
		test_value(three);

		// Here, just for testing purposes, we show the values read by the sensor on the serial monitor.
		Serial.print("Distance: ");
		Serial.print(one);
		Serial.print(" // ");
		Serial.print(two);
		Serial.print(" // ");
		Serial.print(three);
		Serial.print(" cm.");
		Serial.println("");

	} else if (distance != HCSR04_OUT_OF_RANGE && distance < 100) { // Here, the functionality is the same as in the previous block, but here we deal with values that contain only two digits.

		int one = distance / 10;
		int two = distance - (one * 10);

		test_value(one);
		test_value(two);

		Serial.print("Distance: ");
		Serial.print(one);
		Serial.print(" // ");
		Serial.print(two);
		Serial.print(" cm.");
		Serial.println("");

	} else if (distance != HCSR04_OUT_OF_RANGE && distance < 10) { // Here, the functionality is the same as in the first block, but here we deal with values that contain only one digits.

		int value = distance;

		test_value(value);

		Serial.print("Distance: ");
		Serial.print(distance);
		Serial.print(" cm.");
		Serial.println("");
	}
}

// This is just a function that tests the value read by the sensor and returns the respective voice to be spoken.
void test_value(int value) {
	if (value == 0) { // If the value is equal to zero...
		voice.say(spt_ZERO); // our voice object, says the word "zero". [This explanation is for the other line below, just substituting the numbers.]
	}
	if (value == 1) {
		voice.say(spt_ONE);
	}
	if (value == 2) {
		voice.say(spt_TWO);
	}
	if (value == 3) {
		voice.say(spt_THREE);
	}
	if (value == 4) {
		voice.say(spt_FOUR);
	}
	if (value == 5) {
		voice.say(spt_FIVE);
	}
	if (value == 6) {
		voice.say(spt_SIX);
	}
	if (value == 7) {
		voice.say(spt_SEVEN);
	}
	if (value == 8) {
		voice.say(spt_EIGHT);
	}
	if (value == 9) {
		voice.say(spt_NINE);
	}
	delay(200);
}