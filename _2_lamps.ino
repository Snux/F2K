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
//    _                      ___       __ _      _ _   _          
//   | |   __ _ _ __  _ __  |   \ ___ / _(_)_ _ (_) |_(_)___ _ _  
//   | |__/ _` | '  \| '_ \ | |) / -_)  _| | ' \| |  _| / _ \ ' \ 
//   |____\__,_|_|_|_| .__/ |___/\___|_| |_|_||_|_|\__|_\___/_||_|
//                   |_|                                          

//----------------------------------------
//define includes
//----------------------------------------
#include "SPI.h"
#include "PinballLamp.h"
#include "PinballLampEffect.h"
//----------------------------------------

//----------------------------------------
//define global variables
//----------------------------------------
const byte lamp_enable1 = 53;
const byte lamp_enable2 = 10;
const byte lamp_enable3 = 11;
const byte lamp_enable4 = 12;

static unsigned int data_lamp_store0 = 0; //all bits low to start
static unsigned int data_lamp_store1 = 0;
static unsigned int data_lamp_store2 = 0;
static unsigned int data_lamp_store3 = 0;

//----------------------------------------
//setup regularlamps
//----------------------------------------

PinballLamp lamp_bonus1K = PinballLamp(1, &data_lamp_store0);
PinballLamp lamp_bonus2K = PinballLamp(2, &data_lamp_store0);
PinballLamp lamp_bonus3K = PinballLamp(3, &data_lamp_store0);
PinballLamp lamp_bonus4K = PinballLamp(4, &data_lamp_store0);
PinballLamp lamp_bonus5K = PinballLamp(5, &data_lamp_store0);
PinballLamp lamp_bonus6K = PinballLamp(6, &data_lamp_store0);
PinballLamp lamp_bonus7K = PinballLamp(7, &data_lamp_store0);
PinballLamp lamp_bonus8K = PinballLamp(8, &data_lamp_store0);
PinballLamp lamp_bonus9K = PinballLamp(9, &data_lamp_store0);
PinballLamp lamp_bonus10K = PinballLamp(10, &data_lamp_store0);
PinballLamp lamp_release = PinballLamp(11, &data_lamp_store0);
PinballLamp lamp_mult1X = PinballLamp(12, &data_lamp_store0);
PinballLamp lamp_mult2X = PinballLamp(13, &data_lamp_store0);
PinballLamp lamp_mult3X = PinballLamp(14, &data_lamp_store0);
PinballLamp lamp_mult4X = PinballLamp(15, &data_lamp_store0);
PinballLamp lamp_mult5X = PinballLamp(16, &data_lamp_store0);
PinballLamp lamp_blastoff_rollover7 = PinballLamp(17, &data_lamp_store1);
PinballLamp lamp_blastoff_rollover8 = PinballLamp(18, &data_lamp_store1);
PinballLamp lamp_blastoff_rollover6 = PinballLamp(19, &data_lamp_store1);
PinballLamp lamp_blastoff_rollover5 = PinballLamp(20, &data_lamp_store1);
PinballLamp lamp_blastoff_rollover4 = PinballLamp(21, &data_lamp_store1);
PinballLamp lamp_blastoff_rollover3 = PinballLamp(22, &data_lamp_store1);
PinballLamp lamp_blastoff_rollover2 = PinballLamp(23, &data_lamp_store1);
PinballLamp lamp_blastoff_rollover1 = PinballLamp(24, &data_lamp_store1);
PinballLamp lamp_blastoff8 = PinballLamp(25, &data_lamp_store1);
PinballLamp lamp_blastoff7 = PinballLamp(26, &data_lamp_store1);
PinballLamp lamp_blastoff6 = PinballLamp(27, &data_lamp_store1);
PinballLamp lamp_blastoff5 = PinballLamp(28, &data_lamp_store1);
PinballLamp lamp_blastoff4 = PinballLamp(29, &data_lamp_store1);
PinballLamp lamp_blastoff3 = PinballLamp(30, &data_lamp_store1);
PinballLamp lamp_blastoff2 = PinballLamp(31, &data_lamp_store1);
PinballLamp lamp_blastoff1 = PinballLamp(32, &data_lamp_store1);
PinballLamp lamp_right_bank = PinballLamp(33, &data_lamp_store2);
PinballLamp lamp_left_spinner = PinballLamp(34, &data_lamp_store2);
PinballLamp lamp_spot_blast = PinballLamp(35, &data_lamp_store2);
PinballLamp lamp_drop1 = PinballLamp(36, &data_lamp_store2);
PinballLamp lamp_drop2 = PinballLamp(37, &data_lamp_store2);
PinballLamp lamp_drop3 = PinballLamp(38, &data_lamp_store2);
PinballLamp lamp_drop4 = PinballLamp(39, &data_lamp_store2);
PinballLamp lamp_drop5 = PinballLamp(40, &data_lamp_store2);
PinballLamp lamp_shoot_again = PinballLamp(41, &data_lamp_store2);
PinballLamp lamp_spinner500 = PinballLamp(42, &data_lamp_store2);
PinballLamp lamp_spinner1000 = PinballLamp(43, &data_lamp_store2);
PinballLamp lamp_spinner1500 = PinballLamp(44, &data_lamp_store2);
PinballLamp lamp_spinner2000 = PinballLamp(45, &data_lamp_store2);
PinballLamp lamp_all_go_top = PinballLamp(46, &data_lamp_store2);
PinballLamp lamp_stage2_go = PinballLamp(47, &data_lamp_store2);
PinballLamp lamp_stage1_go = PinballLamp(48, &data_lamp_store2);
PinballLamp lamp_hstd = PinballLamp(49, &data_lamp_store3);
PinballLamp lamp_top_special = PinballLamp(50, &data_lamp_store3);
PinballLamp lamp_game_over = PinballLamp(51, &data_lamp_store3);
PinballLamp lamp_tilt = PinballLamp(52, &data_lamp_store3);
PinballLamp lamp_special_lane = PinballLamp(53, &data_lamp_store3);
PinballLamp lamp_all_go_left = PinballLamp(54, &data_lamp_store3);
PinballLamp lamp_apollo2 = PinballLamp(55, &data_lamp_store3);
PinballLamp lamp_apollo1 = PinballLamp(56, &data_lamp_store3);
PinballLamp lamp_special_outlane_right = PinballLamp(57, &data_lamp_store3);
PinballLamp lamp_special_outlane_left = PinballLamp(58, &data_lamp_store3);
PinballLamp lamp_nu59 = PinballLamp(59, &data_lamp_store3);
PinballLamp lamp_match = PinballLamp(60, &data_lamp_store3);
PinballLamp lamp_nu61 = PinballLamp(61, &data_lamp_store3);
PinballLamp lamp_nu62 = PinballLamp(62, &data_lamp_store3);
PinballLamp lamp_nu63 = PinballLamp(63, &data_lamp_store3);
PinballLamp lamp_nu64 = PinballLamp(64, &data_lamp_store3);


//----------------------------------------
//setup lamp effects
//----------------------------------------
PinballLampEffect lamp_effect_set1 = PinballLampEffect(1, &data_lamp_store0);
PinballLampEffect lamp_effect_set2 = PinballLampEffect(2, &data_lamp_store1);
PinballLampEffect lamp_effect_set3 = PinballLampEffect(3, &data_lamp_store2);
PinballLampEffect lamp_effect_set4 = PinballLampEffect(4, &data_lamp_store3);

//----------------------------------------
//methods
//----------------------------------------

void setup_lamps()
{
    pinMode(lamp_enable1, OUTPUT);
    pinMode(lamp_enable2, OUTPUT);
    pinMode(lamp_enable3, OUTPUT);
    pinMode(lamp_enable4, OUTPUT);

    SPI.begin();
    SPI.setBitOrder(MSBFIRST);

    //set all enables low as default - board should have enables tied low, this can be removed
    digitalWrite(lamp_enable1, 0);
    digitalWrite(lamp_enable2, 0);
    digitalWrite(lamp_enable3, 0);
    digitalWrite(lamp_enable4, 0);
}

// Flash a specific lamp - call from the test code

void test_lamp(int lamp_number, int timer)
{
    Serial.print(F("Test lamp number : "));
    Serial.println(String(lamp_number));
    switch (lamp_number) {
        case 1: lamp_bonus1K.flash(timer, 0);
            break;
        case 2: lamp_bonus2K.flash(timer, 0);
            break;
        case 3: lamp_bonus3K.flash(timer, 0);
            break;
        case 4: lamp_bonus4K.flash(timer, 0);
            break;
        case 5: lamp_bonus5K.flash(timer, 0);
            break;
        case 6: lamp_bonus6K.flash(timer, 0);
            break;
        case 7: lamp_bonus7K.flash(timer, 0);
            break;
        case 8: lamp_bonus8K.flash(timer, 0);
            break;
        case 9: lamp_bonus9K.flash(timer, 0);
            break;
        case 10: lamp_bonus10K.flash(timer, 0);
            break;
        case 11: lamp_release.flash(timer, 0);
            break;
        case 12: lamp_mult1X.flash(timer, 0);
            break;
        case 13: lamp_mult2X.flash(timer, 0);
            break;
        case 14: lamp_mult3X.flash(timer, 0);
            break;
        case 15: lamp_mult4X.flash(timer, 0);
            break;
        case 16: lamp_mult5X.flash(timer, 0);
            break;
        case 17: lamp_blastoff_rollover7.flash(timer, 0);
            break;
        case 18: lamp_blastoff_rollover8.flash(timer, 0);
            break;
        case 19: lamp_blastoff_rollover6.flash(timer, 0);
            break;
        case 20: lamp_blastoff_rollover5.flash(timer, 0);
            break;
        case 21: lamp_blastoff_rollover4.flash(timer, 0);
            break;
        case 22: lamp_blastoff_rollover3.flash(timer, 0);
            break;
        case 23: lamp_blastoff_rollover2.flash(timer, 0);
            break;
        case 24: lamp_blastoff_rollover1.flash(timer, 0);
            break;
        case 25: lamp_blastoff8.flash(timer, 0);
            break;
        case 26: lamp_blastoff7.flash(timer, 0);
            break;
        case 27: lamp_blastoff6.flash(timer, 0);
            break;
        case 28: lamp_blastoff5.flash(timer, 0);
            break;
        case 29: lamp_blastoff4.flash(timer, 0);
            break;
        case 30: lamp_blastoff3.flash(timer, 0);
            break;
        case 31: lamp_blastoff2.flash(timer, 0);
            break;
        case 32: lamp_blastoff1.flash(timer, 0);
            break;
        case 33: lamp_right_bank.flash(timer, 0);
            break;
        case 34: lamp_left_spinner.flash(timer, 0);
            break;
        case 35: lamp_spot_blast.flash(timer, 0);
            break;
        case 36: lamp_drop1.flash(timer, 0);
            break;
        case 37: lamp_drop2.flash(timer, 0);
            break;
        case 38: lamp_drop3.flash(timer, 0);
            break;
        case 39: lamp_drop4.flash(timer, 0);
            break;
        case 40: lamp_drop5.flash(timer, 0);
            break;
        case 41: lamp_shoot_again.flash(timer, 0);
            break;
        case 42: lamp_spinner500.flash(timer, 0);
            break;
        case 43: lamp_spinner1000.flash(timer, 0);
            break;
        case 44: lamp_spinner1500.flash(timer, 0);
            break;
        case 45: lamp_spinner2000.flash(timer, 0);
            break;
        case 46: lamp_all_go_top.flash(timer, 0);
            break;
        case 47: lamp_stage2_go.flash(timer, 0);
            break;
        case 48: lamp_stage1_go.flash(timer, 0);
            break;
        case 49: lamp_hstd.flash(timer, 0);
            break;
        case 50: lamp_top_special.flash(timer, 0);
            break;
        case 51: lamp_game_over.flash(timer, 0);
            break;
        case 52: lamp_tilt.flash(timer, 0);
            break;
        case 53: lamp_special_lane.flash(timer, 0);
            break;
        case 54: lamp_all_go_left.flash(timer, 0);
            break;
        case 55: lamp_apollo2.flash(timer, 0);
            break;
        case 56: lamp_apollo1.flash(timer, 0);
            break;
        case 57: lamp_special_outlane_right.flash(timer, 0);
            break;
        case 58: lamp_special_outlane_left.flash(timer, 0);
            break;
        case 59: lamp_nu59.flash(timer, 0);
            break;
        case 60: lamp_match.flash(timer, 0);
            break;
        case 61: lamp_nu61.flash(timer, 0);
            break;
        case 62: lamp_nu62.flash(timer, 0);
            break;
        case 63: lamp_nu63.flash(timer, 0);
            break;
        case 64: lamp_nu64.flash(timer, 0);
            break;

    }
}

void reset_lamps()
{
    lamp_bonus1K.off();
    lamp_bonus2K.off();
    lamp_bonus3K.off();
    lamp_bonus4K.off();
    lamp_bonus5K.off();
    lamp_bonus6K.off();
    lamp_bonus7K.off();
    lamp_bonus8K.off();
    lamp_bonus9K.off();
    lamp_bonus10K.off();
    lamp_release.off();
    lamp_mult1X.off();
    lamp_mult2X.off();
    lamp_mult3X.off();
    lamp_mult4X.off();
    lamp_mult5X.off();
    lamp_blastoff_rollover7.off();
    lamp_blastoff_rollover8.off();
    lamp_blastoff_rollover6.off();
    lamp_blastoff_rollover5.off();
    lamp_blastoff_rollover4.off();
    lamp_blastoff_rollover3.off();
    lamp_blastoff_rollover2.off();
    lamp_blastoff_rollover1.off();
    lamp_blastoff8.off();
    lamp_blastoff7.off();
    lamp_blastoff6.off();
    lamp_blastoff5.off();
    lamp_blastoff4.off();
    lamp_blastoff3.off();
    lamp_blastoff2.off();
    lamp_blastoff1.off();
    lamp_right_bank.off();
    lamp_left_spinner.off();
    lamp_spot_blast.off();
    lamp_drop1.off();
    lamp_drop2.off();
    lamp_drop3.off();
    lamp_drop4.off();
    lamp_drop5.off();
    lamp_shoot_again.off();
    lamp_spinner500.off();
    lamp_spinner1000.off();
    lamp_spinner1500.off();
    lamp_spinner2000.off();
    lamp_all_go_top.off();
    lamp_stage2_go.off();
    lamp_stage1_go.off();
    lamp_hstd.off();
    lamp_top_special.off();
    lamp_game_over.off();
    lamp_tilt.off();
    lamp_special_lane.off();
    lamp_all_go_left.off();
    lamp_apollo2.off();
    lamp_apollo1.off();
    lamp_special_outlane_right.off();
    lamp_special_outlane_left.off();
    lamp_nu59.off();
    lamp_match.off();
    lamp_nu61.off();
    lamp_nu62.off();
    lamp_nu63.off();
    lamp_nu64.off();

}

void reset_lamp_effects()
{
    lamp_effect_set1.cancel();
    lamp_effect_set2.cancel();
    lamp_effect_set3.cancel();
    lamp_effect_set4.cancel();
}

void test_lamps(int timer)
{
    lamp_bonus1K.flash(timer, 0);
    lamp_bonus2K.flash(timer, 0);
    lamp_bonus3K.flash(timer, 0);
    lamp_bonus4K.flash(timer, 0);
    lamp_bonus5K.flash(timer, 0);
    lamp_bonus6K.flash(timer, 0);
    lamp_bonus7K.flash(timer, 0);
    lamp_bonus8K.flash(timer, 0);
    lamp_bonus9K.flash(timer, 0);
    lamp_bonus10K.flash(timer, 0);
    lamp_release.flash(timer, 0);
    lamp_mult1X.flash(timer, 0);
    lamp_mult2X.flash(timer, 0);
    lamp_mult3X.flash(timer, 0);
    lamp_mult4X.flash(timer, 0);
    lamp_mult5X.flash(timer, 0);
    lamp_blastoff_rollover7.flash(timer, 0);
    lamp_blastoff_rollover8.flash(timer, 0);
    lamp_blastoff_rollover6.flash(timer, 0);
    lamp_blastoff_rollover5.flash(timer, 0);
    lamp_blastoff_rollover4.flash(timer, 0);
    lamp_blastoff_rollover3.flash(timer, 0);
    lamp_blastoff_rollover2.flash(timer, 0);
    lamp_blastoff_rollover1.flash(timer, 0);
    lamp_blastoff8.flash(timer, 0);
    lamp_blastoff7.flash(timer, 0);
    lamp_blastoff6.flash(timer, 0);
    lamp_blastoff5.flash(timer, 0);
    lamp_blastoff4.flash(timer, 0);
    lamp_blastoff3.flash(timer, 0);
    lamp_blastoff2.flash(timer, 0);
    lamp_blastoff1.flash(timer, 0);
    lamp_right_bank.flash(timer, 0);
    lamp_left_spinner.flash(timer, 0);
    lamp_spot_blast.flash(timer, 0);
    lamp_drop1.flash(timer, 0);
    lamp_drop2.flash(timer, 0);
    lamp_drop3.flash(timer, 0);
    lamp_drop4.flash(timer, 0);
    lamp_drop5.flash(timer, 0);
    lamp_shoot_again.flash(timer, 0);
    lamp_spinner500.flash(timer, 0);
    lamp_spinner1000.flash(timer, 0);
    lamp_spinner1500.flash(timer, 0);
    lamp_spinner2000.flash(timer, 0);
    lamp_all_go_top.flash(timer, 0);
    lamp_stage2_go.flash(timer, 0);
    lamp_stage1_go.flash(timer, 0);
    lamp_hstd.flash(timer, 0);
    lamp_top_special.flash(timer, 0);
    lamp_game_over.flash(timer, 0);
    lamp_tilt.flash(timer, 0);
    lamp_special_lane.flash(timer, 0);
    lamp_all_go_left.flash(timer, 0);
    lamp_apollo2.flash(timer, 0);
    lamp_apollo1.flash(timer, 0);
    lamp_special_outlane_right.flash(timer, 0);
    lamp_special_outlane_left.flash(timer, 0);
    lamp_nu59.flash(timer, 0);
    lamp_match.flash(timer, 0);
    lamp_nu61.flash(timer, 0);
    lamp_nu62.flash(timer, 0);
    lamp_nu63.flash(timer, 0);
    lamp_nu64.flash(timer, 0);

}

void lamp_loop()
{
    //add lamp loop methods here
    lamp_bonus1K.loop();
    lamp_bonus2K.loop();
    lamp_bonus3K.loop();
    lamp_bonus4K.loop();
    lamp_bonus5K.loop();
    lamp_bonus6K.loop();
    lamp_bonus7K.loop();
    lamp_bonus8K.loop();
    lamp_bonus9K.loop();
    lamp_bonus10K.loop();
    lamp_release.loop();
    lamp_mult1X.loop();
    lamp_mult2X.loop();
    lamp_mult3X.loop();
    lamp_mult4X.loop();
    lamp_mult5X.loop();
    lamp_blastoff_rollover7.loop();
    lamp_blastoff_rollover8.loop();
    lamp_blastoff_rollover6.loop();
    lamp_blastoff_rollover5.loop();
    lamp_blastoff_rollover4.loop();
    lamp_blastoff_rollover3.loop();
    lamp_blastoff_rollover2.loop();
    lamp_blastoff_rollover1.loop();
    lamp_blastoff8.loop();
    lamp_blastoff7.loop();
    lamp_blastoff6.loop();
    lamp_blastoff5.loop();
    lamp_blastoff4.loop();
    lamp_blastoff3.loop();
    lamp_blastoff2.loop();
    lamp_blastoff1.loop();
    lamp_right_bank.loop();
    lamp_left_spinner.loop();
    lamp_spot_blast.loop();
    lamp_drop1.loop();
    lamp_drop2.loop();
    lamp_drop3.loop();
    lamp_drop4.loop();
    lamp_drop5.loop();
    lamp_shoot_again.loop();
    lamp_spinner500.loop();
    lamp_spinner1000.loop();
    lamp_spinner1500.loop();
    lamp_spinner2000.loop();
    lamp_all_go_top.loop();
    lamp_stage2_go.loop();
    lamp_stage1_go.loop();
    lamp_hstd.loop();
    lamp_top_special.loop();
    lamp_game_over.loop();
    lamp_tilt.loop();
    lamp_special_lane.loop();
    lamp_all_go_left.loop();
    lamp_apollo2.loop();
    lamp_apollo1.loop();
    lamp_special_outlane_right.loop();
    lamp_special_outlane_left.loop();
    lamp_nu59.loop();
    lamp_match.loop();
    lamp_nu61.loop();
    lamp_nu62.loop();
    lamp_nu63.loop();
    lamp_nu64.loop();

}

void lamp_effect_loop()
{
    lamp_effect_set1.loop();
    lamp_effect_set2.loop();
    lamp_effect_set3.loop();
    lamp_effect_set4.loop();
}

void lamp_debug()
{
    lamp_bonus1K.debug = false;
    lamp_bonus2K.debug = false;
    lamp_bonus3K.debug = false;
    lamp_bonus4K.debug = false;
    lamp_bonus5K.debug = false;
    lamp_bonus6K.debug = false;
    lamp_bonus7K.debug = false;
    lamp_bonus8K.debug = false;
    lamp_bonus9K.debug = false;
    lamp_bonus10K.debug = false;
    lamp_release.debug = false;
    lamp_mult1X.debug = false;
    lamp_mult2X.debug = false;
    lamp_mult3X.debug = false;
    lamp_mult4X.debug = false;
    lamp_mult5X.debug = false;
    lamp_blastoff_rollover7.debug = false;
    lamp_blastoff_rollover8.debug = false;
    lamp_blastoff_rollover6.debug = false;
    lamp_blastoff_rollover5.debug = false;
    lamp_blastoff_rollover4.debug = false;
    lamp_blastoff_rollover3.debug = false;
    lamp_blastoff_rollover2.debug = false;
    lamp_blastoff_rollover1.debug = false;
    lamp_blastoff8.debug = false;
    lamp_blastoff7.debug = false;
    lamp_blastoff6.debug = false;
    lamp_blastoff5.debug = false;
    lamp_blastoff4.debug = false;
    lamp_blastoff3.debug = false;
    lamp_blastoff2.debug = false;
    lamp_blastoff1.debug = false;
    lamp_right_bank.debug = false;
    lamp_left_spinner.debug = false;
    lamp_spot_blast.debug = false;
    lamp_drop1.debug = false;
    lamp_drop2.debug = false;
    lamp_drop3.debug = false;
    lamp_drop4.debug = false;
    lamp_drop5.debug = false;
    lamp_shoot_again.debug = false;
    lamp_spinner500.debug = false;
    lamp_spinner1000.debug = false;
    lamp_spinner1500.debug = false;
    lamp_spinner2000.debug = false;
    lamp_all_go_top.debug = false;
    lamp_stage2_go.debug = false;
    lamp_stage1_go.debug = false;
    lamp_hstd.debug = false;
    lamp_top_special.debug = false;
    lamp_game_over.debug = false;
    lamp_tilt.debug = false;
    lamp_special_lane.debug = false;
    lamp_all_go_left.debug = false;
    lamp_apollo2.debug = false;
    lamp_apollo1.debug = false;
    lamp_special_outlane_right.debug = false;
    lamp_special_outlane_left.debug = false;
    lamp_nu59.debug = false;
    lamp_match.debug = false;
    lamp_nu61.debug = false;
    lamp_nu62.debug = false;
    lamp_nu63.debug = false;
    lamp_nu64.debug = false;

}