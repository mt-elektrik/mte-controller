/*
  MteCore - Library For MTE Controller

  Muara Teknik Elektrik
  https://github.com/mt-elektrik/MteCore


  Copyright 2020 Muara Teknik Elektrik

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#ifndef _MTE_CORE_H
#define _MTE_CORE_H
#include "Arduino.h"
#if defined(INPUT_DEBUG) ||  defined(OUTPUT_DEBUG)
  //pin mapping for MTE-miniController V.2.0
  String PIN_TO_LABEL(uint8_t pin){
    switch (pin)
    {
    case 2:
      return "IN1";
      break;
    case 3:
      return "IN2";
      break;
    case 4:
      return "IN3";
      break;
    case 5:
      return "IN4";
      break;
    case 11:
      return "IN5";
      break;
    case 12:
      return "IN6";
      break;
    case 13:
      return "IN7";
      break;
    case 10:
      return "IN8";
      break;
    case A7:
      return "IN9";
      break;
    case 9:
      return "IN10";
      break;
    case A6:
      return "IN11";
      break;
    case A4:
      return "IN12";
      break;
      //output
    case A3:
      return "OUT1";
      break;
    case A2:
      return "OUT2";
      break;
    case A1:
      return "OUT3";
      break;
    case A0:
      return "OUT4";
      break;
    case 6:
      return "OUT5";
      break;
    case 7:
      return "OUT6";
      break;
    case 8:
      return "OUT7";
      break;
    
    default:
      break;
    }
  }
#endif

#include "util/InputCore.h"
#include "util/OutputCore.h"
#include "util/TimerCore.h"
#include "util/CounterCore.h"
#if defined(_ENABLE_F3_ANALOG) || defined(_ENABLE_F4_ANALOG) || defined(_ENABLE_F5_ANALOG) || defined(_ENABLE_F7_ANALOG)
  #include "util/AnalogCore.h"
#endif
#ifndef _DISABLE_IN1
  InputCore IN1(2);
#endif
#ifndef _DISABLE_IN2
  InputCore IN2(3);
#endif
#ifndef _DISABLE_IN3
  InputCore IN3(4);
#endif
#ifndef _DISABLE_IN4
  InputCore IN4(5);
#endif
#ifndef _DISABLE_IN5
  InputCore IN5(11);
#endif
#ifndef _DISABLE_IN6
  InputCore IN6(12);
#endif
#ifndef _DISABLE_IN7
  InputCore IN7(13);
#endif
//Settings IN8
#ifdef _ENABLE_F8_PWM
#elif defined(_ENABLE_F8_UART)
#else
  #ifndef _DISABLE_IN8
    InputCore IN8(10);
  #endif
#endif
//end Settings
//Settings IN9
#ifdef _ENABLE_F7_ANALOG
  AnalogCore F7(A7); //enable F7 as Analog
#else 
  #ifndef _DISABLE_IN9
    InputCore IN9(A7);
  #endif
#endif
//end Settings
//Settings IN10
#ifdef _ENABLE_F6_PWM
#elif defined(_ENABLE_F6_UART)
#else
  #ifndef _DISABLE_IN10
    InputCore IN10(9);
  #endif
#endif
//end Settings
//Settings IN11
#ifdef _ENABLE_F5_ANALOG
  AnalogCore F5(A6); //enable F5 as Analog
#else
  #ifndef _DISABLE_IN11
    InputCore IN11(A6);
  #endif
#endif
//end Settings

//Settings IN12
#ifdef _ENABLE_F3_ANALOG
        AnalogCore F3(A4); //enable F3 as Analog
#elif defined(_ENABLE_F3_I2C)
  #ifndef _ENABLE_F4_I2C
    #error "Cannot enable F3 when F4 as I2C is disable!"
  #else
    //enable i2c F3
  #endif
#else
  #ifndef _DISABLE_IN12
    InputCore IN12(A4); //enable IN12
  #endif
#endif
//end Settings IN12

#ifdef _ENABLE_F4_ANALOG
    AnalogCore F4(A5); //enable F4 as Analog
#elif defined(_ENABLE_F4_I2C)
  #ifndef _ENABLE_F3_I2C
    #error "Cannot enable F4 when F3 as I2C is disable!"
  #else
    //enable i2c F4
  #endif
#endif
//OUTPUT
#ifndef _DISABLE_OUT1
  OutputCore OUT1(A3);
#endif
#ifndef _DISABLE_OUT2
  OutputCore OUT2(A2);
#endif
#ifndef _DISABLE_OUT3
  OutputCore OUT3(A1);
#endif
#ifndef _DISABLE_OUT4
  OutputCore OUT4(A0);
#endif
#ifndef _DISABLE_OUT5
  OutputCore OUT5(6);
#endif
#ifndef _DISABLE_OUT6
  OutputCore OUT6(7);
#endif
#ifndef _DISABLE_OUT7
  OutputCore OUT7(8);
#endif

void process(){
  unsigned long now = millis();
#ifndef _DISABLE_IN1
  IN1.process(now);
#endif
#ifndef _DISABLE_IN2
  IN2.process(now);
#endif
#ifndef _DISABLE_IN3
  IN3.process(now);
#endif
#ifndef _DISABLE_IN4
  IN4.process(now);
#endif
#ifndef _DISABLE_IN5
  IN5.process(now);
#endif
#ifndef _DISABLE_IN6
  IN6.process(now);
#endif
#ifndef _DISABLE_IN7
  IN7.process(now);
#endif
#ifndef _DISABLE_IN8
  IN8.process(now);
#endif
  #ifndef _ENABLE_F7_ANALOG
    #ifndef _DISABLE_IN9
      IN9.process(now);
    #endif
  #else
    F7.process(now); //F7 analog process
  #endif
#ifndef _DISABLE_IN10
  IN10.process(now);
#endif
  #ifndef _ENABLE_F5_ANALOG
    #ifndef _DISABLE_IN11
      IN11.process(now);
    #endif
  #else
    F5.process(now); //F5 analog process
  #endif

  #ifdef _ENABLE_F4_ANALOG
    F4.process(now); //F4 analog process
  #endif

  #ifndef _ENABLE_F3_ANALOG
    #ifndef _DISABLE_IN10
      IN12.process(now);
    #endif
  #else
    F3.process(now); //F3 Analog process
  #endif
  //-----------OUTPUT process
  #ifndef _DISABLE_OUT1
    OUT1.process(now);
  #endif
  #ifndef _DISABLE_OUT2
    OUT2.process(now);
  #endif
  #ifndef _DISABLE_OUT3
    OUT3.process(now);
  #endif
  #ifndef _DISABLE_OUT4
    OUT4.process(now);
  #endif
  #ifndef _DISABLE_OUT5
    OUT5.process(now);
  #endif
  #ifndef _DISABLE_OUT6
    OUT6.process(now);
  #endif
  #ifndef _DISABLE_OUT7
    OUT7.process(now);
  #endif
}
#endif