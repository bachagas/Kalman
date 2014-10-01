Kalman.h
========

A simplified one dimensional Kalman filter implementation for Arduino.<br>
It is based on: http://interactive-matter.eu/blog/2009/12/18/filtering-sensor-data-with-a-kalman-filter/ and is actually a low pass filter for one single variable (but still very useful ;-).

Installation
------------

Download the archive from GitHub, decompress it, and you will have two options:<br>

1) move the “Kalman” folder into the “libraries” subdirectory inside your Arduino sketchbook directory (you can view your sketchbook location by selecting File→Preferences in the Arduino environment; if there is not already a “libraries” folder in that location, you should create it yourself). Then import it with:

	#include <Kalman.h>;
	
2) move the “Kalman” folder to the sketchbook you want to use it and then import it with:

	#include "Kalman.h";
	
After installing the library, restart the Arduino environment so it can find the library.

Kalman Formulas
---------------

x = x<br>
p = p + q;<br>
k = p / (p + r);<br>
x = x + k * (measurement – x);<br>
p = (1 – k) * p;<br>
<br>
Where:<br>
q = process noise covariance<br>
r = measurement noise covariance<br>
x = value of interest<br>
p = estimation error covariance<br>
k = Kalman gain<br>

All you need to know to start using it right now
------------------------------------------------

The variables are x for the filtered value, q for the process noise, r for the sensor noise, p for the estimated error and k for the Kalman Gain. 
The state of the filter is defined by the values of these variables.
         
The initial values for p is not very important since it is adjusted during the process. It must be just high enough to narrow down.
The initial value for the readout is also not very important, since it is updated during the process.
But tweaking the values for the process noise and sensor noise is essential to get clear readouts.

Example
-------

For large noise reduction, you can try to start from (see http://interactive-matter.eu/blog/2009/12/18/filtering-sensor-data-with-a-kalman-filter/ for a better description on getting to these values):<br>
q = 0.125<br>
r = 32<br>
p = 1023 //"large enough to narrow down"

Hello World Kalman
------------------

	#include <Kalman.h>

	//Creates the variables:
	double measurement, filteredMeasurement;
	Kalman myFilter(0.125,32,1023,0); //suggested initial values for high noise filtering
	
	void loop() {

		//...
		
		//reads measurement and filter it
		measurement = (double) analogRead(A1); //read new value from sensor in analog pin A1, for example
		filteredMeasurement = myFilter.getFilteredValue(measurement);
		
		//...
	}

Other (maybe) useful stuff
--------------------------

    //Reset filter parameters:
	void setParameters(double process_noise, double sensor_noise, double estimated_error)

	//Get filter parameters:
    double getProcessNoise()    
    double getSensorNoise() 
    double getEstimatedError()
	
<br>
And that is it! ;-)

License Information
-------------------

This code is open source so please feel free to do anything you want with it; you buy me a beer if you use this and we meet someday ([Beerware license](http://en.wikipedia.org/wiki/Beerware)).

