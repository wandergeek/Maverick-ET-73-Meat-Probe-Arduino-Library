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


## To Do:
* re-write sampling funciton code so it doesn't block program while sampling
* Test Kelvin and Celcius
* Create Probe Buffer offset method for calibration
 
