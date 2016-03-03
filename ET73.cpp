#include <ET73.h>
    //Constructor
    ET73::ET73(int mypin, int mynumsamples, int mysampleinterval,bool debug ){          
          ET73::num_samples = mynumsamples;
          ET73::sample_interval = mysampleinterval;
          ET73::timelastreading = millis();
          ET73::PIN = mypin;
          pinMode(ET73::PIN, INPUT);
          //DEBUG
          if(debug){
            Serial.begin(9600);
            serial_debug = true;
          }
      }
    //***************************************************************
    //shouldWeSample(int timenow, int timelastreading)
    //Checks to see if the sample_interval has passed
    //
    //***************************************************************
    bool ET73::shouldWeSample(int timenow, int timelastreading){
      if(timenow - timelastreading > ET73::sample_interval)
        return true;
      else
        return false;
    };

    //***************************************************************
    //getAverageReading(int)
    //reads the ET73 pin for num_samples every sample_interval milliseconds
    //Returns an average of the samples 
    //***************************************************************
    float ET73::getAverageReading(){
       float average = 0;
       int samples_gathered;
       
       int sample_array[ET73::num_samples];

       for (int i=0; i< ET73::num_samples; i++) {
          ET73::timenow = millis(); //Reset our timenow to current time
          while( !shouldWeSample(ET73::timenow,ET73::timelastreading) ){ // Check to see if time passed is greater than our ET73::sample_interval.
              ET73::timenow = millis();           // if an interval hasn't yet passed, keep updating out ET73::timenow attribute the time until it does.
          }                      
          sample_array[i] = analogRead(ET73::PIN); // Once an interval has passed lets take a sample and put it into our array.
          ET73::timelastreading = timenow; //Reset the last timelastreading variable to now becuase we've taken a reading.

          //DEBUG OUTPUT
          if(ET73::serial_debug) 
          {
           Serial.print("Sampling! SampleTime: ");
           Serial.print(ET73::timenow);                       
           Serial.print("\nSample Reading: ");
           Serial.print(sample_array[i]);
           Serial.print("\n\n");
          } //END DEBUG
        }

        for (int i=0; i< ET73::num_samples; i++) {
          average += sample_array[i]; //Now we temporarily use the average variable to  total the values of our array.
        }

        average = average / ET73::num_samples; //Calculate the average analog reading and set the value to the average variable

        //DEBUG OUTPUT
        if(ET73::serial_debug) {
         Serial.print("Average Analog Reading: ");
         Serial.print(average);
         Serial.print("\n");
        } //END DEBUG

        return average;
    };

    //***************************************************************
    //ET73::getTemp_F()
    //Returns the temp in Farenheit after averaging the samples
    //*************************************************************** 

      float ET73::getTemp_F(){
        double R, T;
        float average = getAverageReading(); //returns an average reading

        R = log((1 / ((1024 / (double) average) - 1)) * (double) ET73::RESISTOR_VALUE);
       // Compute degrees C
        T = (1 / ((ET73::STEINHART_HART_COEF_A) + (ET73::STEINHART_HART_COEF_B) * R + (ET73::STEINHART_HART_COEF_C) * R * R * R)) - 273.25;
       // return in degrees F
        return ((float) ((T * 9.0) / 5.0 + 32.0));
      };

    //***************************************************************
    //ET73::getTemp_C()
    //Returns the temp in Celcius after averaging the samples
    //*************************************************************** 
      float ET73::getTemp_C() {
        double R, T;
        float average = getAverageReading(); //returns an average reading

        R = log((1 / ((1024 / (double) average) - 1)) * (double) ET73::RESISTOR_VALUE);
       // Compute degrees C
        T = (1 / ((ET73::STEINHART_HART_COEF_A) + (ET73::STEINHART_HART_COEF_B) * R + (ET73::STEINHART_HART_COEF_C) * R * R * R)) - 273.25;
       // return in degrees C
        return float(T);
      };

    //***************************************************************
    //ET73::getTemp_K()
    //Returns the temp in Kelvins after averaging the samples
    //*************************************************************** 
      float ET73::getTemp_K(){
        double R, T;
        float average = getAverageReading(); //returns an average reading

        R = log((1 / ((1024 / (double) average) - 1)) * (double) ET73::RESISTOR_VALUE);
       // Compute degrees K
        T = (1 / ((ET73::STEINHART_HART_COEF_A) + (ET73::STEINHART_HART_COEF_B) * R + (ET73::STEINHART_HART_COEF_C) * R * R * R));
       // return in degrees K
        return float(T);
      };

      //***************************************************************
      //setNumOfSamples(int mysamples)
      //Sets the number of samples to average every time the getTemp_*() function is called
      //*************************************************************** 
      void ET73::setNumOfSamples(int mysamples){        
              ET73::num_samples = mysamples;
      };

      //***************************************************************
      //setSampleInterval(int myinterval)
      //Sets the interval in between each 
      //*************************************************************** 
      void ET73::setSampleInterval(int myinterval){
        ET73::sample_interval = sample_interval;
      };