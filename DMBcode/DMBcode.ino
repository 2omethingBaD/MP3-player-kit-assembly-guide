#include <EEPROM.h>
#include <SoftwareSerial.h>
#include "DFRobotDFPlayerMini.h"
#include <avr/pgmspace.h>

#define sensor_low LOW
#define reed_sensor 1 // this is physical pin 6
#define vol_pin 0 // this is physical pin 5
#define led 2 // this is physical pin 7 (optional debug LED)
#define Rx 3 // this is physical pin 2 (connect to Tx on DFplayer mini)
#define Tx 4 // this is physical pin 3 (connect to Rx on DFplayer mini with 1K res)

int proximity;
bool has_ended = false;
bool is_playing = false;
bool was_vol_pressed = false;

int volumeLevels[] = {15, 20, 25, 30};  // Predefined volume levels
int currentVolumeIndex; // No initialization, we will load this from EEPROM

unsigned long volPressTime = 0;  // Time when vol_pin was first pressed
unsigned long volReleaseTime = 0;  // Time when vol_pin was released
const unsigned long resetThreshold = 2000;  // 2 seconds threshold for reset
const unsigned long debounceDelay = 50;  // Debounce time to ignore button noise

SoftwareSerial mySoftwareSerial(Rx, Tx);
DFRobotDFPlayerMini myDFPlayer;


void setup() 
{
  mySoftwareSerial.begin(9600);

  // optional debug LED
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  pinMode(reed_sensor, INPUT_PULLUP);
  pinMode(vol_pin, INPUT_PULLUP);

  // fast flash if shit is broken
  if (!myDFPlayer.begin(mySoftwareSerial))
  {  
    while (true) 
    {
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      delay(100);
    }
  }

  // Turn on LED if shit works
  digitalWrite(led, HIGH);

  // Load last saved volume index from EEPROM
  currentVolumeIndex = EEPROM.read(0);
  if (currentVolumeIndex < 0 || currentVolumeIndex > 3) 
  {
    currentVolumeIndex = 3; // Default to highest volume if EEPROM value is invalid
  }

  myDFPlayer.volume(volumeLevels[currentVolumeIndex]);
  
  // Add a delay to allow DFPlayer Mini to stabilize
  delay(1000);
}


void loop()
{  
  proximity = digitalRead(reed_sensor);
  bool vol_pressed = digitalRead(vol_pin) == LOW;

  // Handle button functions
  if (vol_pressed && !was_vol_pressed) 
  {
    // Button just pressed
    volPressTime = millis();  // Record the time when the button was pressed
    was_vol_pressed = true;
    delay(debounceDelay);  // Debounce delay
  } 
  else if (!vol_pressed && was_vol_pressed) 
  {
    // Button just released
    volReleaseTime = millis();
    if (volReleaseTime - volPressTime < resetThreshold) 
    {
      // Short press: Change volume
      currentVolumeIndex = (currentVolumeIndex + 1) % 4; // Cycle through volume levels
      myDFPlayer.volume(volumeLevels[currentVolumeIndex]);

      // Save the new volume index to EEPROM
      EEPROM.write(0, currentVolumeIndex);

      // Blink LED to indicate volume change
      digitalWrite(led, LOW);
      delay(100);
      digitalWrite(led, HIGH);
    }
    was_vol_pressed = false;  // Reset button press state
  }
  else if (vol_pressed && was_vol_pressed) 
  {
    // Button held down for a longer time
    if (millis() - volPressTime >= resetThreshold) 
    {
      // Long press: Reset the audio
      myDFPlayer.stop();
      is_playing = false;
      has_ended = false;
      myDFPlayer.play(1);  // Start playing from track 1
      is_playing = true;
      myDFPlayer.pause();
      is_playing = false;

      // Blink LED twice to indicate reset
      digitalWrite(led, LOW);
      delay(500);
      digitalWrite(led, HIGH);
      delay(500);
      digitalWrite(led, LOW);
      delay(500);
      digitalWrite(led, HIGH);

      volPressTime = millis();  // Reset the timer to avoid multiple triggers
      was_vol_pressed = false;  // Reset button press state
    }
  }

  // Check if audio has finished playing
  if (myDFPlayer.available())
  {
    if (myDFPlayer.readType() == DFPlayerPlayFinished)
    {
      myDFPlayer.stop();
      is_playing = false;
      has_ended = true;

      // Blink LED to indicate audio has ended
      digitalWrite(led, LOW);
      delay(500);
      digitalWrite(led, HIGH);
    }
  }

  // Handle reed sensor
  if (proximity == sensor_low && !is_playing && has_ended)
  {
    myDFPlayer.stop();
    is_playing = false;
    has_ended = false;
    myDFPlayer.play(1);  // Start playing from track 1
    is_playing = true;
    myDFPlayer.pause();
    is_playing = false;

    // Blink LED twice to indicate reset due to reed sensor
    digitalWrite(led, LOW);
    delay(500);
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
    digitalWrite(led, HIGH);
  }
  if (proximity == sensor_low)
  { 
    if (is_playing)
    {
      myDFPlayer.pause();
      is_playing = false;

      // Blink LED to indicate pause due to reed sensor
      digitalWrite(led, LOW);
      delay(100);
      digitalWrite(led, HIGH);
    }
  } 
  else
  {
    if (!is_playing && !has_ended)
    {
      myDFPlayer.start();
      is_playing = true;

      // Blink LED to indicate resume due to reed sensor
      digitalWrite(led, LOW);
      delay(100);
      digitalWrite(led, HIGH);
    }
  }
}