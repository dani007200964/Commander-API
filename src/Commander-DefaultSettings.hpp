/*
 * Created on June 18 2020
 *
 * Copyright (c) 2020 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2022.02.06
*/

/*
MIT License

Copyright (c) 2020 Daniel Hajnal

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#ifndef COMMANDER_API_SRC_COMMANDER_SETTINGS_HPP_
#define COMMANDER_API_SRC_COMMANDER_SETTINGS_HPP_

#ifdef __has_include
    #if __has_include ("Commander-Settings.hpp")
        #include "Commander-Settings.hpp"
    #endif
#endif

#ifdef ESP32

  #ifndef COMMANDER_USE_WIFI_CLIENT_RESPONSE
    #define COMMANDER_USE_WIFI_CLIENT_RESPONSE
  #endif

  #ifndef COMMANDER_ENABLE_PIPE_MODULE
    #define COMMANDER_ENABLE_PIPE_MODULE
  #endif

  #ifndef COMMANDER_MAX_COMMAND_SIZE
    #define COMMANDER_MAX_COMMAND_SIZE 50
  #endif

#endif

#ifdef ESP8266

  #ifndef COMMANDER_USE_WIFI_CLIENT_RESPONSE
    #define COMMANDER_USE_WIFI_CLIENT_RESPONSE
  #endif

  #ifndef COMMANDER_ENABLE_PIPE_MODULE
    #define COMMANDER_ENABLE_PIPE_MODULE
  #endif

  #ifndef COMMANDER_MAX_COMMAND_SIZE
    #define COMMANDER_MAX_COMMAND_SIZE 50
  #endif

#endif

// Enable the Pipe module by default
#define COMMANDER_ENABLE_PIPE_MODULE

/// Maximum length of the terminal command.
#ifndef COMMANDER_MAX_COMMAND_SIZE
  #define COMMANDER_MAX_COMMAND_SIZE 100
#endif

/// This macro can be used create a buffer for piping.
/// @note The pipe buffer has to be a char type and the size of the buffer has to be as big as this define.
#define COMMANDER_PIPE_BUFFER_SIZE ( COMMANDER_MAX_COMMAND_SIZE + 1 )

#endif /* COMMANDER_API_SRC_COMMANDER_SETTINGS_HPP_ */
