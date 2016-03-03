
//************************************************************************
//ARDUINO ET-73 MEAT & PIT PROBE LIBRARY 
//By: Skye Perry
//Version 1.0.2  Last Modified: 216-03-02
//This Library is licensed under a GPLv3 License
//Tested with Maverick Smoker Probes for the ET73. PN: PR-004(smoker probe) & PR-005(meat probe)
//************************************************************************

#ifndef ET73_h
#define ET73_h
#define LIBRARY_VERSION 1.1.1

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class ET73 {
    private:
      //Constants for the ET-73 and Wiring Schematic            
      const  long double STEINHART_HART_COEF_A = 2.3067434E-4;
      const  long double STEINHART_HART_COEF_B = 2.3696596E-4;
      const  long double STEINHART_HART_COEF_C = 1.2636414E-7;
      const int RESISTOR_VALUE = 22000;

      //Samples and time Attributes
      int PIN;
      int num_samples;
      int sample_interval;
      int timenow;
      int timelastreading;
      bool serial_debug;

      //Private Methods
      bool shouldWeSample(int, int);
      float getAverageReading();

    public:
      //Constructor      
      ET73(int mypin, int mynumsamples = 10, int mysampleinterval = 10,bool debug = false); //Optional arguments must only be defined in the header or prototype
      
      //Public Methods
      float getTemp_F();
      float getTemp_C();
      float getTemp_K();
      void setNumOfSamples(int);
      void setSampleInterval(int);
};

#endif

