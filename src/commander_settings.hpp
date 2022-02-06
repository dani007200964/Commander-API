/*
 * Created on June 18 2020
 *
 * Copyright (c) 2020 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2022.02.06
*/

#ifndef COMMANDER_API_SRC_COMMANDER_SETTINGS_HPP_
#define COMMANDER_API_SRC_COMMANDER_SETTINGS_HPP_

#ifdef ARDUINO
#ifndef COMMANDER_USE_ARDUINO_SERIAL_RESPONSE
#define COMMANDER_USE_ARDUINO_SERIAL_RESPONSE
#endif
#endif

//#define COMMANDER_USE_SERIAL_RESPONSE
//#define COMMANDER_USE_WIFI_CLIENT_RESPONSE

/// Maximum length of the terminal command.
#define COMMANDER_MAX_COMMAND_SIZE 30

#define COMMAND_PRINTF_BUFF_LEN 100


#endif /* COMMANDER_API_SRC_COMMANDER_SETTINGS_HPP_ */
