@mainpage Commander-API library
![Build Status](https://github.com/dani007200964/Commander-API/actions/workflows/compile-examples.yml/badge.svg?branch=main)

__Version V2.1.0__

Commander-API is a simple-to-use parser library, and you can easily use it to process character-based commands and link them to a specified function. It is designed mainly to work with low memory capacity devices, for example, __small ARM or AVR processors__.

__Changes in V2.1.X__

* Response function changed to __Stream__ type. This way it supports almost anything in the Arduino ecosystem.
I believe it supports all platforms now.
* Pipe support enabled. To use it, check out the @ref what_is_piping "pipes guide".
* AVR PROGMEM support. This library was very resource-hungry in the previous versions of the AVR platform.
Strings are stored in the RAM area by default in the AVR controllers. There is a macro called PROGMEM to
store them in the FLASH, but you can't access them like a regular string. For this reason, a compatibility
layer was added inside Commander-API.
* Internal debug and status messages are automatically stored in PROGMEM on AVR. The overall memory consumption
reduced on UNO from 67% to 21% with the same example.
* @ref premade_commands "Premade terminal commands". It can be useful when you want to create a system from the ground up as quickly as
possible. For this reason, some premade terminal commands are available, you can add them to the API-tree with
a macro. Of course, you can select which one you need. This is totally optional you can implement your own versions.

__Video Tutorial__

\htmlonly


<iframe width="1024" height="786" src="https://www.youtube.com/embed/O2su8kXg1X8" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

\endhtmlonly

@note This video is made for the previous version. There are some minor changes. Please check the updated examples.

__Documentation__

The full documentation can be found [here](https://dani007200964.github.io/Commander-API/html/index.html).

__Contributing__
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## Donation
If this project help you reduce time to develop, you can give me a cup of coffee \emoji :coffee: \emoji :coffee: \emoji :coffee:

[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/donate?hosted_button_id=YFGZD78H6K2CS)

## License & copyright
© Daniel Hajnal

\emoji :email: hajnal.daniel96@gmail.com

Licensed under the MIT License
