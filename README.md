# Digital Timer
 
Include your responses to the bold questions below. Include snippets of code that explain what you did. Deliverables are due next Tuesday. Post your lab reports as README.md pages on your GitHub, and post a link to that on your main class hub page.

## Part A. Solder your LCD panel

![LCD](https://github.com/dlydb/IDD-Fa19-Lab2/blob/master/lab2_parta.jpg)

## Part B. Writing to the LCD
 
**a. What voltage level do you need to power your display?**

5V

**b. What voltage level do you need to power the display backlight?**

3.3V
   
**c. What was one mistake you made when wiring up the display? How did you fix it?**

One of the pin is not soldered very well, so the LCD will not print anything. Resolder the LCD and make the connection between pin and board better.

**d. What line of code do you need to change to make it flash your name instead of "Hello World"?**

lcd.print("hello, world!"); -> lcd.print("Ziyu Liu");
 
**e. Include a copy of your Lowly Multimeter code in your lab write-up.**

[code](https://github.com/dlydb/IDD-Fa19-Lab2/blob/master/PartC.ino)


## Part C. Using a time-based digital sensor

[Encoder](https://youtu.be/qPxbwlh4aN0)


## Part D. Make your Arduino sing!

**a. How would you change the code to make the song play twice as fast?**

int noteDuration = 1000 / noteDurations[thisNote]; -> int noteDuration = 500 / noteDurations[thisNote];
 
**b. What song is playing?**

The star wars


## Part E. Make your own timer

I design a game that how fast can you push the button in a given period of time. The encoder is used to input the time from the user. LCD screen will display the whole process with current time, set time and speed. It will also record the fastest speed. Also a buzzer is used to play music when time is up.

[game video](https://www.youtube.com/watch?v=ZFcv7zr9n34)

[main code](https://github.com/dlydb/IDD-Fa19-Lab2/blob/master/PartE.ino)

[pitches h](https://github.com/dlydb/IDD-Fa19-Lab2/blob/master/pitches.h)
