@page premade_commands Premade Commands

There are some premade commands already to make your development easier. Please
read the documentation carefully, some commands are platform dependent.

@section how_to_add_premade_commands How To Add Premade Commands


@section system_commands System Commands

@subsection reboot_command reboot Command

* __Syntax:__ `reboot`
* __Arguments:__ none

This command reboots the device.

@subsection neofetch_command neofetch Command

* __Syntax:__ `neofetch`
* __Arguments:__ none

This command is inspired by the original [neofetch](https://github.com/dylanaraps/neofetch)
bash script. It is a visually pleasing system information tool.

![ neofetch Output ]( neofetch_output.png )

<hr>

@section timing_commands Timing Commands

@subsection micros_command micros Command

* __Syntax:__ `micros`
* __Arguments:__ none

This command returns the number of microseconds passed since the program started.

@subsection millis_command millis Command

* __Syntax:__ `millis`
* __Arguments:__ none

This command returns the number of milliseconds passed since the program started.

<hr>

@section digital_io_commands Digital I/O Commands

@subsection pinMode_command pinMode Command

* __Syntax:__ `pinMode`
* __Arguments:__
  * Pin Number
  * State
* __Example:__
  * `pinMode 2 1` -> Set pin 2 to output.
  * `pinMode 3 0` -> Set pin 3 to input.

This command sets the direction of any pin on the microcontroller.

@subsection digitalWrite_command digitalWrite Command

* __Syntax:__ `digitalWrite`
* __Arguments:__
  * Pin Number
  * State
* __Example:__
  * `digitalWrite 2 1` -> Set pin 2 output state to high.
  * `digitalWrite 3 0` -> Set pin 3 output state to low.

This command sets the state of any output pin.
@note To make it work, the specified pin has to be configured to be an output. Check @ref pinMode_command "pinMode comand".

@subsection digitalRead_command digitalRead Command

* __Syntax:__ `digitalRead`
* __Arguments:__
  * Pin Number
* __Example:__
  * `digitalRead 2` -> Read the state of pin 2.
  * `digitalRead 3` -> Read the state of pin 3.

This command reads the state of any input or output pin.

<hr>

@section analog_io_commands Analog I/O Commands

@subsection analogRead_command analogRead Command

* __Syntax:__ `analogRead`
* __Arguments:__
  * Pin Number
* __Example:__
  * `analogRead 0` -> Create an ADC measurement on analog pin 0
  * `analogRead 5` -> Create an ADC measurement on analog pin 5

This command creates an ADC measurement on any ADC pin.
@note On Arduino boards the ADC pins usually marked as A0, A1... etc. To select A0, you have to pass 0 as argument, to select A3, you have to pass 3 as argument and so on.

<hr>

@section wifi_specific_commands WiFi Specific Commands

@note These commands are made for ESP8266 and ESP32. They do not work on any other platforms!

@subsection ipconfig_command ipconfig Command

* __Syntax:__ `ipconfig`
* __Arguments:__ none

Displays current TCP/IP network configuration.

![ ipconfig Output ]( ipconfig_output.png )

@subsection wifiStat_command wifiStat Command

* __Syntax:__ `wifiStat`
* __Arguments:__ none

Displays WiFi mode, signal strength and MAC address.

![ wifiStat Output ]( wifiStat_output.png )

@subsection wifiScan_command wifiScan Command

* __Syntax:__ `wifiScan`
* __Arguments:__ none

Scans for the nearby WiFi networks and print them as a list.

![ wifiScan Output ]( wifiScan_output.png )

<hr>

@section math_commands Math Commands

@subsection sin_command sin Command

* __Syntax:__ `sin`
* __Arguments:__
  * rad -> Input number in __radians__.
* __Example:__
  * `sin 0` -> Returns __0.000000__
  * `sin 1.570796` -> Returns __1.000000__

Calculates the sine of an angle which is given in radians.
@note The output precision is 6 digit after the decimal point.

@subsection cos_command cos Command

* __Syntax:__ `cos`
* __Arguments:__
  * rad -> Input number in __radians__.
* __Example:__
  * `cos 0` -> Returns __1.000000__
  * `cos 1.570796` -> Returns __0.000000__

Calculates the cosine of an angle which is given in radians.
@note The output precision is 6 digit after the decimal point.

@subsection abs_command abs Command

* __Syntax:__ `abs`
* __Arguments:__
  * num -> Input float umber.
* __Example:__
  * `abs 10.5` -> Returns __10.500000__
  * `abs -6.3` -> Returns __6.300000__

Calculates the absolute value of an input number.
@note The output precision is 6 digit after the decimal point.

@subsection random_command random Command

* __Syntax:__ `random`
* __Arguments:__
  * min -> Lower integer bound
  * max -> Upper integer bound
* __Example:__
  * `random 1 5` -> Returns a random integer between 1 and 5( 5 is the upper limit, so actually 4 will be the largest number )

Generates a random number between the given bounds.

@subsection not_command not Command

* __Syntax:__ `not`
* __Arguments:__
  * state -> Input logical state
* __Example:__
  * `not 0` -> Returns 1
  * `not 1` -> Returns 0
  * `not 2` -> Returns 0

Generates a logical NOT from the input. It follows the C-like true-false logic, so 0 is false, everything else is true.
