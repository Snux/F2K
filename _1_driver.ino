//   ####################################################################################################
//   # Flight 3000 written by Mark Sunnucks (Snux) Copyright 2016                                       #
//   #                                                                                                  #
//   # Based on and expanded from example code supplied with the myPinballs Custom Controller Boardset  #
//   #                                                                                                  #
//   # This code will not compile or run on its own. It requires the myPinballs Custom Controller       #
//   # Boardset hardware and frameworks, which are available here:                                      #
//   # http://mypinballs.co.uk/electronics/store.jsp                                                    #  
//   #                                                                                                  #
//   # Boardset, All Frameworks & Code Structure/Design are Copyright Orange Cloud Software Ltd         #
//   ####################################################################################################
//
//   This file is part of Flight 3000.
//
//   Flight 3000 is free software: you can redistribute it and/or modify it under the terms of the GNU General Public 
//   License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//   Flight 3000 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//    ___      _               ___       __ _      _ _   _          
//   |   \ _ _(_)_ _____ _ _  |   \ ___ / _(_)_ _ (_) |_(_)___ _ _  
//   | |) | '_| \ V / -_) '_| | |) / -_)  _| | ' \| |  _| / _ \ ' \ 
//   |___/|_| |_|\_/\___|_|   |___/\___|_| |_|_||_|_|\__|_\___/_||_|
//                                                                  

//----------------------------------------
//define includes
//----------------------------------------
#include "PinballDriver.h"
//----------------------------------------

//----------------------------------------
//define global variables
//----------------------------------------


static boolean driver_blank_flag = true;
static boolean driver_configured = false;

//Define all the data and enable lines and blank line here
const byte driver_d0 = D0;
const byte driver_d1 = D1;
const byte driver_d2 = D2;
const byte driver_d3 = D3;
const byte driver_d4 = D4;
const byte driver_d5 = D5;
const byte driver_d6 = D6;
const byte driver_d7 = D7;
const byte driver_blank = BLANKING;
const byte driver_enable1 = DRIVER_ENABLE1;
const byte driver_enable2 = DRIVER_ENABLE2;
const byte driver_enable3 = DRIVER_ENABLE3;
const byte driver_enable4 = DRIVER_ENABLE4;

//define the driver data storage arrays - all bits low to start using 74HCT574 latch ics
static int data_store0 = B00000000;
static int data_store1 = B00000000;
static int data_store2 = B00000000;

//define library drivers
PinballDriver top_left_slingshot_coil = PinballDriver(1, &data_store0);
PinballDriver top_right_slingshot_coil = PinballDriver(2, &data_store0);
PinballDriver bottom_jet_coil = PinballDriver(6, &data_store0);
PinballDriver left_target_reset_coil = PinballDriver(7, &data_store0);
PinballDriver bottom_left_slingshot_coil = PinballDriver(3, &data_store0);
PinballDriver bottom_right_slingshot_coil = PinballDriver(4, &data_store0);
PinballDriver top_jet_coil = PinballDriver(5, &data_store0);
PinballDriver target_5_coil = PinballDriver(8, &data_store0);

PinballDriver target_4_coil = PinballDriver(11, &data_store1);
PinballDriver target_3_coil = PinballDriver(12, &data_store1);
PinballDriver target_2_coil = PinballDriver(14, &data_store1);
PinballDriver target_1_coil = PinballDriver(13, &data_store1);
PinballDriver ball_launcher_coil = PinballDriver(10, &data_store1);
PinballDriver walker_coil = PinballDriver(9, &data_store1);
PinballDriver right_target_reset_coil = PinballDriver(15, &data_store1);

PinballDriver right_top_kicker_coil = PinballDriver(16, &data_store2);
PinballDriver left_top_kicker_coil = PinballDriver(18, &data_store2);
PinballDriver coin_lockout_coil = PinballDriver(17, &data_store2);

PinballDriver left_flipper_coil = PinballDriver(19, &data_store2);
PinballDriver right_flipper_coil = PinballDriver(20, &data_store2);

//-------------------------------------------------------
//methods
//-------------------------------------------------------

void setup_driver()
{
    //define driver outputs for config section - library deals with drives themselves
    pinMode(driver_d0, OUTPUT);
    pinMode(driver_d1, OUTPUT);
    pinMode(driver_d2, OUTPUT);
    pinMode(driver_d3, OUTPUT);
    pinMode(driver_d4, OUTPUT);
    pinMode(driver_d5, OUTPUT);
    pinMode(driver_d6, OUTPUT);
    pinMode(driver_d7, OUTPUT);
    pinMode(driver_blank, OUTPUT);
    pinMode(driver_enable1, OUTPUT);
    pinMode(driver_enable2, OUTPUT);
    pinMode(driver_enable3, OUTPUT);
    pinMode(driver_enable4, OUTPUT);
}

void enable_driver()
{
    //if flag is true blanking is enabled and driver board will be shutdown - HIGH on the pin
    if (driver_blank_flag)
    {
        digitalWrite(driver_blank, 1);
    }
    else
    {
        digitalWrite(driver_blank, 0);
    }
}

void config_driver()
{
    if (!driver_configured)
    {
        driver_blank_flag = false;
        enable_driver();
        digitalWrite(driver_d0, 0);
        digitalWrite(driver_d1, 0);
        digitalWrite(driver_d2, 0);
        digitalWrite(driver_d3, 0);
        digitalWrite(driver_d4, 0);
        digitalWrite(driver_d5, 0);
        digitalWrite(driver_d6, 0);
        digitalWrite(driver_d7, 0);
        digitalWrite(driver_enable1, 0);
        digitalWrite(driver_enable1, 1);
        digitalWrite(driver_enable2, 0);
        digitalWrite(driver_enable2, 1);
        digitalWrite(driver_enable3, 0);
        digitalWrite(driver_enable3, 1);
        digitalWrite(driver_enable4, 0);
        digitalWrite(driver_enable4, 1);
        driver_configured = true;
        Serial.println(F("Driver Configured"));
    }
}

void driver_loop()
{
    //add driver loop methods here
    top_right_slingshot_coil.loop();
    top_left_slingshot_coil.loop();
    bottom_jet_coil.loop();
    left_target_reset_coil.loop();
    bottom_left_slingshot_coil.loop();
    bottom_right_slingshot_coil.loop();
    left_flipper_coil.loop();
    right_flipper_coil.loop();
    top_jet_coil.loop();
    target_5_coil.loop();

    target_4_coil.loop();
    target_3_coil.loop();
    target_2_coil.loop();
    target_1_coil.loop();
    ball_launcher_coil.loop();
    walker_coil.loop();
    right_target_reset_coil.loop();

    right_top_kicker_coil.loop();
    left_top_kicker_coil.loop();
    coin_lockout_coil.loop();
}

// By default switch off the coil debug output

void driver_debug()
{
    //add driver loop methods here
    top_right_slingshot_coil.debug = false;
    top_left_slingshot_coil.debug = false;
    bottom_jet_coil.debug = false;
    left_target_reset_coil.debug = false;
    bottom_left_slingshot_coil.debug = false;
    bottom_right_slingshot_coil.debug = false;
    left_flipper_coil.debug = false;
    right_flipper_coil.debug = false;
    top_jet_coil.debug = false;
    target_5_coil.debug = false;

    target_4_coil.debug = false;
    target_3_coil.debug = false;
    target_2_coil.debug = false;
    target_1_coil.debug = false;
    ball_launcher_coil.debug = false;
    walker_coil.debug = false;
    right_target_reset_coil.debug = false;

    right_top_kicker_coil.debug = false;
    left_top_kicker_coil.debug = false;
    coin_lockout_coil.debug = false;
}