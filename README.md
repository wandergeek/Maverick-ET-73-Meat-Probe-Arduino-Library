# Maverick-ET-73-Meat-Probe-Arduino-Library
An Arduino library for easily integrating the affordable and widely-available Maverick ET-73 meat and smoker probe

## Parts Needed:
* 1 - 5v Arduino
* 1 - Maverick ET-73 replacement Probes for meat or smoker(the only difference is the tip) Part Numbers PR-004 or PR-005
* 1 - 2.5mm mono PCB mount jack
* 1 - 22k Ohm Resistor
* A breadboard or another way to wire the components together


## Wiring the Probe to the arduino:
![Arduino Meat Probe Wiring](https://github.com/skyeperry1/Maverick-ET-73-Meat-Probe-Arduino-Library/blob/master/ET-73.Drawing.jpg)


Once the 2.5mm is wired up as shown, you can plug the meat probe into the jack. 

## Basic Usage:
     #include <ET73.h> // First we must include the ET73 Library found here
     
     #define MEAT_PROBE_PIN 2 //Now we define which analog pin we're going to read our probe from
     
     // Now we define an ET73 probe called meatProbe, and pass it the pin as the first argument, the rest of the arguments are optional
     // ET73( int probe pin, int Number of samples (optional, default:10) ,  int sample interval in ms (optional, default:10) , bool debug (optional, default:false) )
     ET73 meatProbe(MEAT_PROBE_PIN);  
     
     
     void setup() {
       Serial.begin(9600); //Start the Serial for testing purposes  
     }
     
     void loop() { 
       //When we call the meat probe getTemp_F method, by default the library takes 24 readings at a 10ms interval 
       float myTemp = meatProbe.getTemp_F();   
     
       //Print out our results to the serial monitor
       Serial.print("Temp: ");
       Serial.print(myTemp);
       Serial.print(" F\n");   
     
       //If we want to change the number of samples we're taking for each time we call the getTemp_*(),
       //we can change it by calling the setNumOfSamples() method
       meatProbe.setNumOfSamples(20); //Here we've set the probe to take the average of 20 samples each reading
     
       //If we want to change the interval between each sample reading when we call getTemp_*(),
       //we can change it by calling the setSampleInterval() method
       meatProbe.setSampleInterval(200); //Here we've set it to take a sample every 200 ms
     
       //Now when we call out getTemp_*() method we're going to take the average of 20 samples at a 200ms interval
       myTemp = meatProbe.getTemp_F();  
       
       //Print out our results to the serial monitor and notice how it slows down.
       Serial.print("Temp: ");
       Serial.print(myTemp);
       Serial.print(" F\n");  
       
     }

How To Read A Meat Probe With An Arduino

Overview:

In this project, we’re going to learn how to hook up a Maverick ET-73 replacement meat probe to an Arduino and use the Arduino to read the temperature from the probe. We’ll be walking through everything step by step, so don’t fret if you have minimal experience with Arduino or electronics. We’ll be covering all the basic principals and theory so by the end of this project you’ll not only have built a functional meat thermometer, but you’ll understand why it works.

Parts Needed:

1 – 5v or 3.3v Arduino w/ Power Supply (Any Model)
1 – Maverick ET-73 replacement Probe for meat or smoker(the only difference is the tip) Part Numbers PR-004 or PR-005
1 – 2.5mm mono PCB mount jack
1 – 22k Ohm Resistor
A breadboard or another way to wire the components together
How it Works:

Before we start wiring up our Arduino, let’s take a second to understand the principals behind what we’re trying to accomplish.

First we’ll take a look at how the meat probe works. The ET-73 meat probe is really just a special type of resistor called a thermistor. A thermistor is just a handy little resistor who’s resistance changes with the temperature.  By calculating the resistance of our thermistor(meat probe) with the Arduino, we can use the Steinhart-Hart equation to determine the temperature.

Step 1. Wiring the Arduino :

In order to measure the temperature of the thermistor, we’ll need to a way to measure the resistance of the meat probe. Unfortunately our Arduino doesn’t have the capability to read the resistance directly from an input pin. To accomplish this, what we’ll actually need to do is take an analog reading of the voltage and then use our measurements to calculate our resistance.

The first thing we need to do is add a resistor into the circuit in order to gain a constant variable to base our measurement off of. By measuring the voltage in the middle of the fixed resistor and the thermistor, we can use an equation to calculate the resistance of the thermistor using our known resistor value as a constant (for further reading check here).

Once everything is connected you can plug your ET-73 probe into the 2.5mm jack.

ET-73 Drawing

 

Step 2. The Code

Now, let’s head let head over to the computer and get the Arduino IDE and a browser loaded up. (TODO: Create Arduino Setup Tutorial)

A. Go to https://github.com/skyeperry1/Maverick-ET-73-Meat-Probe-Arduino-Library and download the ET-73 Arduino Library. Open a new sketch and load the library(TODO: Create loading library into IDE tutorail) into

B. Copy and paste the sample code below, or download the arduino .ino file here (TODO: Add .INO file to github).  This code demonstrates the basic setup and methods of the library. The code has been commented to explain what’s happening in each line. Once you’ve loaded the code into the IDE, read through the comments as the next step of this tutorial and continue reading below to see how the library works. 

#include <ET73.h> // First we must include the ET73 Library found here

 #define MEAT_PROBE_PIN 2 //Now we define which analog pin we're going to read our probe from

 // Now we define an ET73 probe called meatProbe, and pass it the pin as the first argument, the rest of the arguments are optional
 // ET73( int probe pin, int Number of samples (optional, default:10) ,  int sample interval in ms (optional, default:10) , bool debug (optional, default:false) )
 ET73 meatProbe(MEAT_PROBE_PIN);  


 void setup() {
   Serial.begin(9600); //Start the Serial for testing purposes  
 }

 void loop() { 
   //When we call the meat probe getTemp_F method, by default the library takes 24 readings at a 10ms interval 
   float myTemp = meatProbe.getTemp_F();   

   //Print out our results to the serial monitor
   Serial.print("Temp: ");
   Serial.print(myTemp);
   Serial.print(" F\n");   

   //If we want to change the number of samples we're taking for each time we call the getTemp_*(),
   //we can change it by calling the setNumOfSamples() method
   meatProbe.setNumOfSamples(20); //Here we've set the probe to take the average of 20 samples each reading

   //If we want to change the interval between each sample reading when we call getTemp_*(),
   //we can change it by calling the setSampleInterval() method
   meatProbe.setSampleInterval(200); //Here we've set it to take a sample every 200 ms

   //Now when we call out getTemp_*() method we're going to take the average of 20 samples at a 200ms interval
   myTemp = meatProbe.getTemp_F();  

   //Print out our results to the serial monitor and notice how it slows down.
   Serial.print("Temp: ");
   Serial.print(myTemp);
   Serial.print(" F\n");  

 }
Step 4. Understanding the code

The Steinhart-Hart Equation

At the heart of the ET-73 library is the Steinhart-Hart equation. This is what we’re using to calculate the temperature of the meat probe based on the resistance that we’ve read into the Arduino.

The Steinhart-Hart equation uses three know resistances of the thermistor measured at different temperatures. These values are known as the Steinhart-Hart coefficients and can typically be found on the manufacturer datasheets.

{1 \over T} = A + B \ln(R) + C [\ln(R)]^3 ,

Steinhart-Hart Equation

A,B & C  represent the different Steinhart-Hart coefficients
T represents temperature in Kelvin
R represents our measured resistance in ohms
Although it’s slightly more complex, the Steinhart-Hart equation gives us greater accuracy over a wider temperature range than using simple linear approximation.

To further increase the accuracy of our measurement the library takes an average reading based on the number of samples set for the ET-73 object. By default, when we call the getTemp method we take and average of the resistance of 10 samples at a 10 millisecond interval. This acts to buffer out any abnormalities we may occur when sampling the probes resistance.
## To Do:
* re-write sampling funciton code so it doesn't block program while sampling
* Test Kelvin and Celcius
* Create Probe Buffer offset method for calibration
 
