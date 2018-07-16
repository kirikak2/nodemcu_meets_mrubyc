/*
  libmrubyc_config.h
  Header file for Arduino application
  
  Copyright (c) 2018, katsuhiko kageyama All rights reserved.
*/
#ifndef __LIBMRUBYC_CONFIG_H__
#define __LIBMRUBYC_CONFIG_H__

#define ESP8266MRBC_VERSION "0.1.0"

/* Specific Devices */
//#define USE_GPS_NEO6M
//#define USE_RTC
//#define ENABLE_RMIRB

/* for debug */
#define ESP8266_DEBUG

#ifdef ESP8266_DEBUG
#define DEBUG_SERIAL_BAUDRATE 115200
#define DEBUG_PRINT(val) Serial.print(val)
#define DEBUG_PRINTLN(val) Serial.println(val)
#else
#define DEBUG_PRINT(val)
#define DEBUG_PRINTLN(val)
#endif

#endif