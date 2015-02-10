# Monarch Control Code
For more information about the project take a look at [these pages](http://research.ocadu.ca/socialbody/project/prosthetic-technologies-of-being)

Reads EMG data, transforms it for Servo consumption.

# Setup &amp; Usage

Download and unzip this repository over your Arduino sketch folder. This will setup the required library.

When uploading, make sure you change the Monarch ID in `Monarch.ino` to the ID of the Monarch you are apploading to.

# Editing

Everything should be compatible with your favourite Arduino IDE. 

# Structure

What you might need each file for:

###`defaults.ino`

Contains Monarch-specific default values here. 

i.e. modify if you need to adjust the 'high' and 'low' servo position 
values for individual servos.

If more prototypes are created it should be possible to just add them by
following the set format:

```c
	//Monarch n
	Mn.leftHIGH  = 160;
	Mn.leftLOW   = 88;
	Mn.leftPIN   = 9;
	Mn.rightHIGH = 20;
	Mn.rightLOW  = 88;
	Mn.rightPIN  = 10;
	Mn.emgPIN = A0;
	Mn.calPIN = A1;
	Mn.modPIN = 7;
```

Where `n` is the prototype number. (currently there are 1,2,3 and 4)

###`Monarch.ino`

Sets up the core program storage structs. Should not be necessary to modify
unless you are extending functionality.

Contains all Input/Output functionality in one Protothread. Can be used to
massage some values.

Has the Debug loop, adjust that based on what you need to output when, and
don't forget to comment/uncomment it as you move from testing to 'production'.

###`modes.ino`

Contains the logic for the three available modes. Can be modified to tweak
each modes functionality.

###`helpers.ino`

Generally logic scavanged elsewhwere, two pieces that are good to fiddle
with:

```c
  int out[] = { 0, 20, 300, 800, 1200, 1600, 2000, 2000, 2000, 2000, 2000};
  int in[]  = { 0, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200}; 
```

`out` contains the value to be mapped to, this can control the normally
even distribution of the sensor value to a more parabolic one.

`in` adjust if the sensor is no longer mapped from 0 to 200.

# Copyright
Copyright &copy; 2013-2015 Social Body Lab