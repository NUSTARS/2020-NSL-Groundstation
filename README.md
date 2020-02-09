# 2020-NSL-Groundstation

## Overview 
two driver motors

two servos to lift up the ice 

limitations - loar radios have low bandwidth
* bytes per second
* scheme as small as possible, b/c amount of time block reading radio is proportional to length of packet, bit operations
* own data scheme for floating points
		fixed point
	interface -analog stick, two vals, stop turn and then go forward, -1 and 1 vals for input
	
	
	Byte for each motor
	Byte to represent each motor has power
		Send info every time
	
	Any language we want
	Send over serial to radio code, radio code will send to the motor
	
	Probably not autonomous 
	

### Decisions to make on 1/29/2020
	• Programming language
		○ C++
	• Data type
		○ To send stuff to rover
			§ Byte for each motor
		○ Checksum from rover to receive
	• How to control it
		○ Keyboard
			§ Direction indicated by the arrow keys
			§ Maybe volume like incrementation for speed if applicable
	• Interface to control it
		○ Look into the thing that already exists ?
		○ If we need to make it
			§ Maybe instructions for which keyboard keys control what
				□ Maybe car indicating what commands would do (animated)

### Structure of code
Functions
* Accepting in/out from keyboard (or mouse button later if interface has buttons)
	* Ex: hit the up arrow key direction should be forward
	* Ex: press a button to increase speed (?)
* Sending the data to the serial radio
	* Should be continuously sending things
		* If no change send previous message
* Serial radio
	* Should send the data to the car
* Check the checksum?
	○ Check the checksum received from rover as confirm for previous message. 


Structures
	• Byte data structure


Interface to control
	• Look into using python/flask api w/ c++ otherwise look into C++ interfaces
	• In the background it should set up a connection w/ the rover
		○ Has indication of if connection exists
	• Maybe print a message when change occurs and when rover confirms change
	
	
## Parts
* Hardware to communicate from groundstation to rover - Feather m0 rfm95w


## For next meeting
Questions
	• When we send data is it just power on or off or is there a speed (like 20% or something)
		○ i.e. what form is easiest
		
	* does the left/right side motors have a forward/backward function?
		* -> for turning is it easier to have right side forward or right side forward and left side backward for turning left


	


