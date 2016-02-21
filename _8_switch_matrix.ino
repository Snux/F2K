//   ####################################################################################################
//   # Flight 3000 written by Mark Sunnucks (Snux)                                                      #
//   #                                                                                                  #
//   # Based on and expanded from example code supplied with the myPinballs Custom Controller Boardset  #
//   #                                                                                                  #
//   # This code will not compile or run on its own. It requires the myPinballs Custom Controller       #
//   # Boardset hardware and frameworks, which are available here:                                      #
//   # http://mypinballs.co.uk/electronics/store.jsp                                                    #  
//   #                                                                                                  #
//   # Boardset and Framework are Copyright Orange Cloud Software Ltd                                   #
//   ####################################################################################################
//
//   Flight 3000 Copyright 2016 Mark Sunnucks
//   This file is part of Flight 3000.
//   Flight 3000 is free software: you can redistribute it and/or modify it under the terms of the GNU General Public 
//   License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//   Flight 3000 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//
//    ___        _ _      _      ___       __ _      _ _   _
//   / __|_ __ _(_) |_ __| |_   |   \ ___ / _(_)_ _ (_) |_(_)___ _ _
//   \__ \ V  V / |  _/ _| ' \  | |) / -_)  _| | ' \| |  _| / _ \ ' \
//   |___/\_/\_/|_|\__\__|_||_| |___/\___|_| |_|_||_|_|\__|_\___/_||_|
//
//----------------------------------------
//define includes
//----------------------------------------
#include "PinballSwitch.h"
#include "PinballDirectSwitch.h"
#include "Keypad.h"
//----------------------------------------

//----------------------------------------
//define global variables
//----------------------------------------
const byte sw_rows = 8;
const byte sw_cols = 8;
const char switches[sw_rows][sw_cols] = {
    {11, 12, 13, 14, 15, 16, 17, 18},
    {21, 22, 23, 24, 25, 26, 27, 28},
    {31, 32, 33, 34, 35, 36, 37, 38},
    {41, 42, 43, 44, 45, 46, 47, 48},
    {51, 52, 53, 54, 55, 56, 57, 58},
    {61, 62, 63, 64, 65, 66, 67, 68},
    {71, 72, 73, 74, 75, 76, 77, 78},
    {81, 82, 83, 84, 85, 86, 87, 88}
};

/*
String switch_descriptions[sw_rows][sw_cols]={
{"Drop Target E","Drop Target D","Drop Target C","Drop Target B","Drop Target A","Start Button","Tilt","Outhole"},
{"Coin 3","Coin 1","Coin 2","Top Rollover Button","Drop Target Rebound","Right Outlane","Left Outlane","Sam Tilt"},
{"Spinner","5 Target","4 Target","3 Target","2 Target","1 Target","Lite Feeder Lanes","Saucer"},
{"","5 Star","4 Star","3 Star","2 Star","1 Star","Right Slingshot","Left Slingshot"},
{"Bottom Bumper","5 Left Rollover","4 Left Rollover","3 Left Rollover","2 Left Rollover","1 Left Rollover","Right Bumper","Left Bumper"},
{"Left Flipper","Right Flipper","","","","","",""},
{"","","","","","","",""},
{"","","","","","","",""},
};
 */

byte switch_num = 1;
byte row_pins[sw_rows] = {22, 24, 26, 28, 30, 32, 34, 36}; //connect to the row pinouts of the switch matrix
byte col_pins[sw_cols] = {23, 25, 27, 29, 31, 33, 35, 37}; //connect to the column pinouts of the switch matrix

Keypad switch_matrix = Keypad(makeKeymap(switches), row_pins, col_pins, sw_rows, sw_cols);

//-------------------------------------------------------
//define matrix switches
//-----------------------------------------------
//row1
PinballSwitch sw_coin1 = PinballSwitch(add_credit);
PinballSwitch sw_coin2 = PinballSwitch(add_credit);
PinballSwitch sw_coin3 = PinballSwitch(add_credit);
PinballSwitch sw_spinnerL = PinballSwitch(left_spinner);
PinballSwitch sw_spinnerR = PinballSwitch(right_spinner);
PinballSwitch sw_start = PinballSwitch(start_game);
PinballSwitch sw_tilt = PinballSwitch(tilt);
PinballSwitch sw_slamtilt = PinballSwitch(tilt);
//row2
PinballSwitch sw_left_top_sling = PinballSwitch(left_top_sling);
PinballSwitch sw_right_top_sling = PinballSwitch(right_top_sling);
PinballSwitch sw_left_bottom_sling = PinballSwitch(left_bottom_sling);
PinballSwitch sw_right_bottom_sling = PinballSwitch(right_bottom_sling);
PinballSwitch sw_top_jet = PinballSwitch(top_jet);
PinballSwitch sw_bottom_jet = PinballSwitch(bottom_jet);
PinballSwitch sw_left_kicker = PinballSwitch(left_kicker);
PinballSwitch sw_right_kicker = PinballSwitch(right_kicker);
//row3
PinballSwitch sw_blastoff1 = PinballSwitch(spot_blastoff1);
PinballSwitch sw_blastoff2 = PinballSwitch(spot_blastoff2);
PinballSwitch sw_blastoff3 = PinballSwitch(spot_blastoff3);
PinballSwitch sw_blastoff4 = PinballSwitch(spot_blastoff4);
PinballSwitch sw_blastoff5 = PinballSwitch(spot_blastoff5);
PinballSwitch sw_blastoff6 = PinballSwitch(spot_blastoff6);
PinballSwitch sw_blastoff7 = PinballSwitch(spot_blastoff7);
PinballSwitch sw_blastoff8 = PinballSwitch(spot_blastoff8);
//row4
PinballSwitch sw_right_top_drop = PinballSwitch(right_drop);
PinballSwitch sw_right_middle_drop = PinballSwitch(right_drop);
PinballSwitch sw_right_bottom_drop = PinballSwitch(right_drop);
PinballSwitch sw_1drop = PinballSwitch(drop1);
PinballSwitch sw_2drop = PinballSwitch(drop2);
PinballSwitch sw_3drop = PinballSwitch(drop3);
PinballSwitch sw_4drop = PinballSwitch(drop4);
PinballSwitch sw_5drop = PinballSwitch(drop5);
//row5
PinballSwitch sw_right_trough = PinballSwitch(trough_switch_handler, trough_switch_handler);
PinballSwitch sw_middle_trough = PinballSwitch(trough_switch_handler, trough_switch_handler);
PinballSwitch sw_left_trough = PinballSwitch(trough_switch_handler, trough_switch_handler);
PinballSwitch sw_left_outlane = PinballSwitch(outlane);
PinballSwitch sw_right_outlane = PinballSwitch(outlane);
PinballSwitch sw_spot_blast = PinballSwitch(spot_blast);
PinballSwitch sw_ball_launch = PinballSwitch(ball_launch);
PinballSwitch sw_release_rocket = PinballSwitch(release_rocket);

//define direct switches
PinballDirectSwitch test_sw = PinballDirectSwitch(1, test);
PinballDirectSwitch test_sw2 = PinballDirectSwitch(2, game_status);
PinballDirectSwitch sw_left_flipper = PinballDirectSwitch(3, left_flipper_cancel, left_flipper); //active low
PinballDirectSwitch sw_right_flipper = PinballDirectSwitch(4, right_flipper_cancel, right_flipper); //active low
//-----------------------------------------------



//-------------------------------------------------------
//methods
//-------------------------------------------------------

void setup_switches()
{
    switch_matrix.setDebounceTime(3);
    //switch_matrix.setHoldTime(500);
    switch_matrix.addEventListener(switchEvent);
    Serial.println(F("Switch Matrix Setup"));
}

boolean getSwitchState(byte row, byte col)
{
    return bitRead(switch_matrix.bitMap[row - 1], col - 1);
}

void switchEvent(KeypadEvent key)
{
    byte key_id = switch_matrix.findInList(key); //find the key in the list and get the id
    byte switch_state = switch_matrix.key[key_id].kstate; //switch_matrix.getState();

    //byte row = (key / 10) - 1;
    //byte col = (key % 10) - 1;
    /*
      Serial.print(F("Key Pressed:"));
      Serial.print(F("Key: S")); Serial.print(key, DEC);
      Serial.print(F("  key_id: ")); Serial.print(key_id, DEC);
      //Serial.print(F(" "));
      //Serial.print(F("Name:"));Serial.print(switch_descriptions[row][col]);
      Serial.print(F(" "));
      Serial.print(F("State:")); Serial.println(switch_state);
     */

    // If the ball search is active, then we only want to respond to the top kicker switches
    // and the trough switches; everything else can be ignored
    if (ball_search)
    {
        if (!(key == 27 || key == 28 || key == 51 || key == 52 || key == 53))
            key = 0; // Key 0 won't get processed
    }
    // If the switch test routine is active, instead of processing the switch call, just display
    // the number on one of the displays.
    if (test_active && test_id == 4)
    {
        byte disp_key = key;
        set_display(2, String(disp_key));
    }
    else
        switch (key) {
                //row1
            case 11:
                sw_coin1.read(switch_state);
                return;
            case 12:
                sw_coin2.read(switch_state);
                return;
            case 13:
                sw_coin3.read(switch_state);
                return;
            case 14:
                sw_spinnerL.read(switch_state);
                return;
            case 15:
                sw_spinnerR.read(switch_state);
                return;
            case 16:
                sw_start.readHold(switch_state);
                return;
            case 17:
                sw_tilt.read(switch_state);
                return;
            case 18:
                sw_slamtilt.read(switch_state);
                return;
                //row2
            case 21:
                sw_left_top_sling.read(switch_state);
                return;
            case 22:
                sw_right_top_sling.read(switch_state);
                return;
            case 23:
                sw_left_bottom_sling.read(switch_state);
                return;
            case 24:
                sw_right_bottom_sling.read(switch_state);
                return;
            case 25:
                sw_top_jet.read(switch_state);
                return;
            case 26:
                sw_bottom_jet.read(switch_state);
                return;
            case 27:
                sw_left_kicker.readHold(switch_state);
                return;
            case 28:
                sw_right_kicker.readHold(switch_state);
                return;

                //row3
            case 31:
                sw_blastoff1.read(switch_state);
                return;
            case 32:
                sw_blastoff2.read(switch_state);
                return;
            case 33:
                sw_blastoff3.read(switch_state);
                return;
            case 34:
                sw_blastoff4.read(switch_state);
                return;
            case 35:
                sw_blastoff5.read(switch_state);
                return;
            case 36:
                sw_blastoff6.read(switch_state);
                return;
            case 37:
                sw_blastoff8.read(switch_state);
                return;
            case 38:
                sw_blastoff7.read(switch_state);
                return;
                //row4
            case 41:
                sw_right_top_drop.read(switch_state);
                return;
            case 42:
                sw_right_middle_drop.read(switch_state);
                return;
            case 43:
                sw_right_bottom_drop.read(switch_state);
                return;
            case 44:
                sw_1drop.read(switch_state);
                return;
            case 45:
                sw_2drop.read(switch_state);
                return;
            case 46:
                sw_3drop.read(switch_state);
                return;
            case 47:
                sw_4drop.read(switch_state);
                return;
            case 48:
                sw_5drop.read(switch_state);
                return;

                //row5
            case 51:
                sw_right_trough.readHold(switch_state);
                return;
            case 52:
                sw_middle_trough.readHold(switch_state);
                return;
            case 53:
                sw_left_trough.readHold(switch_state);
                return;
            case 54:
                sw_left_outlane.read(switch_state);
                return;
            case 55:
                sw_right_outlane.read(switch_state);
                return;
            case 56:
                sw_spot_blast.read(switch_state);
                return;
            case 57:
                sw_ball_launch.readHold(switch_state);
                return;
            case 58:
                sw_release_rocket.read(switch_state);
                return;
        }

}

void check_switches()
{
    char key = switch_matrix.getKeys();

    read_direct_switches();
}

void read_direct_switches()
{
    // Only allow test mode to start if game is not running.
    if (!game_started) test_sw.read();
    test_sw2.read();
    if (num_of_players > 0 || test_active) //only check these switches during active game play or during test mode
    {
        sw_left_flipper.read();
        sw_right_flipper.read();
    }
}

