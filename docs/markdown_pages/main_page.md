@mainpage Commander-API library
**Version V2.1.0**

Commander-API is a simple-to-use parser library, and you can easily use it to process character based commands and link them to a specified function. It is designed mainly to work with low memory capacity devices, for example, __small ARM or AVR processors__.

## Changes in V2

Version 2.X is a more refined version of the original Commander-API. The original was working well, but it was a bit flimsy when you had to work with a huge API list.
It also caused Hard-fault when the API tree was not created correctly. Besides that, if you wanted to add a new command, you had to change the header and the source
file as well. The biggest problem was, that it was a C-API, so no overloading, no C++ magic.

The new version is designed from ground up and the main motivation was to make it as reliable as the original, but make it much simpler to use.

__Key changes:__
* Full C++ API
* Arduino compatible without any modifications
* Platform-IO compatibility( still in progress )
* Simpler usage
* Better example
* Low memory consumption to make it compatible with lower end devices like Arduino UNO, Nano...
* Response function overload. Thanks to C++ the response function can be anything like Serial, WiFiClient...

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## Donation
If this project help you reduce time to develop, you can give me a cup of coffee \emoji :coffee: \emoji :coffee: \emoji :coffee:

[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/donate?hosted_button_id=YFGZD78H6K2CS)

## License & copyright
© Daniel Hajnal

\emoji :email: hajnal.daniel96@gmail.com

Licensed under the MIT License
