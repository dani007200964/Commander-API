@page premade_commands Premade Commands

There are some premade commands already to make your development easier. Please
read the documentation carefully, some commands are platform dependent.

@section how_to_add_premade_commands How To Add Premade Commands


@section system_commands System Commands

@subsection reboot_command reboot Command

* __Syntax:__ `reboot`
* __Arguments:__ none

This command reboots the device.

@section timing_commands Timing Commands

@subsection micros_command micros Command

* __Syntax:__ `micros`
* __Arguments:__ none

This command returns the number of microseconds passed since the program started.

@subsection millis_command millis Command

* __Syntax:__ `millis`
* __Arguments:__ none

This command returns the number of milliseconds passed since the program started.

@subsection neofetch_command neofetch Command

* __Syntax:__ `neofetch`
* __Arguments:__ none

This command is inspired by the original [neofetch](https://github.com/dylanaraps/neofetch)
bash script. It is a visually pleasing system information tool.

@subsection pinMode_command pinMode Command

* __Syntax:__ `pinMode`
* __Arguments:__
  * Pin Number
  * State
* __Example:__
  * `pinMode 2 1` -> Set pin 2 to output.
  * `pinMode 3 0` -> Set pin 3 to input.

This command sets the direction of any pin on the microcontroller.
