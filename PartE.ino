/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>

#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
unsigned int start_mill;
signed int counter = 0;
signed int number = 0, but_st = 0, last_st = 0, highest_score = 0;
float spd = 0;

#define ENC_A 6 //these need to be digital input pins
#define ENC_B 7
#define pb 9
#define pb2 10

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  pinMode(pb, INPUT);
  pinMode(pb2, INPUT);

    /* Setup encoder pins as inputs */
  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.clear();
  lcd.display();
  lcd.print("Please set a");
  lcd.setCursor(0, 1);
  lcd.print("timer");
  delay(2000);
  lcd.clear();
  
  lcd.display();
  lcd.print("Timer: 0");
  while (digitalRead(pb) == 0){
    static unsigned int counter4x = 0;      //the SparkFun encoders jump by 4 states from detent to detent
    static unsigned int prevCounter = 0;
    int tmpdata;
    tmpdata = read_encoder();
    if( tmpdata) {
      counter4x += tmpdata;
      counter = counter4x/4;
      if (prevCounter != counter){
        lcd.clear();
        lcd.display();
        lcd.print("Timer: ");
        lcd.print(counter);
        lcd.print("s");
      }
    }
    prevCounter = counter;
  }
  signed int start_time = millis()/1000;
  signed int cur_time = millis()/1000 - start_time;
  while (cur_time <= counter){
    but_st = digitalRead(pb2);
    if (but_st != last_st){
      if (but_st == 1){
        number++;
      }
    }
    last_st = but_st;
    delay(50);
    if (cur_time != millis()/1000 - start_time){
      cur_time = millis()/1000 - start_time;
      lcd.clear();
      lcd.display();
      lcd.print(counter - cur_time);
      lcd.print("s ");
      if (counter - cur_time <= 3){
        lcd.print("!!");
        if (counter - cur_time <= 2){
          lcd.print("!!");
          if (counter - cur_time <= 1){
            lcd.print("!!");
            if (counter - cur_time <= 0){
              lcd.print("!!");
            }
          }
        }
      }
    }
  }
  
  /*
  while (counter >= 0){
    lcd.clear();
    lcd.display();
    lcd.print(counter);
    lcd.print("s ");
    if (counter <= 3){
      lcd.print("!!");
      if (counter <= 2){
        lcd.print("!!");
        if (counter <= 1){
          lcd.print("!!");
          if (counter == 0){
            lcd.print("!!");
          }
        }
      }
    }
    counter -= 1;
    delay(1000);
  }*/
  lcd.clear();
  lcd.display();
  lcd.print("Time is up!");
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
  float cur_spd = float(number)/float(counter);
  if (cur_spd > spd){
    spd = cur_spd;
    highest_score = number;
    lcd.clear();
    lcd.display();
    lcd.print("New record!");
    delay(1000);
    lcd.clear();
    lcd.display();
    lcd.print("You have pushed");
    lcd.setCursor(0, 1);
    lcd.print(number);
    lcd.print(" times");
    delay(1000);
    lcd.clear();
    lcd.display();
    lcd.print("Your speed is");
    lcd.setCursor(0, 1);
    lcd.print(spd);
    lcd.print("/s");
    delay(3000);
  }
  else{
    lcd.clear();
    lcd.display();
    lcd.print("You have pushed");
    lcd.setCursor(0, 1);
    lcd.print(number);
    lcd.print(" times");
    delay(1000);
    lcd.clear();
    lcd.display();
    lcd.print("Try harder");
    lcd.setCursor(0, 1);
    lcd.print("next time!");
    delay(3000);
  }
  number = 0;
}


/* returns change in encoder state (-1,0,1) */
int read_encoder()
{
  static int enc_states[] = {
    0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0  };
  static byte ABab = 0;
  ABab *= 4;                   //shift the old values over 2 bits
  ABab = ABab%16;      //keeps only bits 0-3
  ABab += 2*digitalRead(ENC_A)+digitalRead(ENC_B); //adds enc_a and enc_b values to bits 1 and 0
  return ( enc_states[ABab]);
 
 
}

